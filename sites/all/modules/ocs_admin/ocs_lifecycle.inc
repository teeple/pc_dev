<?php

function array_get_value( $a, $f=array()) 
{
	if ( ! $a || ! is_array($a)) return array();
	foreach( $a as $k => $v) {
		if ( is_array( $v)) $f = array_get_value( $v, $f);
		else $f[] = $v;
	}
	return $f;
} 

function ocs_admin_check_lifecycle_scheme( $node, $node_unchanged)
{
// 	dpm( $node, 'node');
// 	dpm( $node_unchanged, 'unchanged');
	
	$after = array_get_value( $node->field_lifecycle_states);
	$before = array_get_value( $node_unchanged->field_lifecycle_states);
	
// 	dpm( $after, 'after');
// 	dpm( $before, 'before');
	
	$intersect = array_intersect( $before, $after);
	$removed = array_diff( $before, $intersect);
	$added = array_diff( $after, $intersect);
	
	//dpm( $added. 'nodes to add');
	//dpm( $removed, 'nodes to remove');
	//dpm( $intersect, 'node intersect');
	
	// check ocs_svc_perm
	// ocs_svc_perm에는 title이 node->nid인 instance 들이 저장되어 있다.
	// 이중에서 state 값이 added, removed에 속한 것을 추가/삭제한다.
	$items = entity_load( 'node', FALSE, array( 'type' => 'ocs_svc_perm', 'title' => $node->nid));
	// add lifecycle states
	
	// remove lifecycle states
	
	foreach ( $items as $item) {
		//dpm( $item, 'state item');
		$state_nid = $item->field_lifecycle_state['und'][0]['nid'];
		if ( ($key = array_search( $state_nid, $intersect)) !== FALSE) {
			// intersect, 교집합에 들어가므로 패스
			//dpm( $item->nid, 'belongs to intersect');
			unset($intersect[$key]); 
		}
		else if ( ($key = array_search( $state_nid, $added)) !== FALSE) {
			//dpm( $item->nid, 'belongs to add list');
			unset( $added[$key]);
		}
		else {
			// 그외의 경우는 모두 삭제
			//dpm( $item->nid, 'remove state');
			node_delete( $item->nid);
		}
	}
	
	//dpm( $added, 'nodes to add');
	//dpm( $intersect, 'node not exist');
	$added = array_merge( $added, $intersect);
	
	// add lifecycle states
	foreach( $added as $add_node_nid) {
		$new_node = ocs_admin_get_new_node( 'ocs_svc_perm');
		$new_node->title = $node->nid;
		$new_node->field_lifecycle_state['und'][0]['nid'] = $add_node_nid;
		$new_node->field_lifecycle_scheme['und'][0]['nid'] = $node->nid;
		node_save( $new_node);
		
		//dpm( $new_node, 'add node');
	}
	
	// check ocs_state_machine
	$items = entity_load( 'node', FALSE, array( 'type' => 'ocs_state_machine', 'title' => $node->nid));
	foreach ( $items as $item) {
// 		dpm( $item, 'state machine');
		if ( array_search( $item->field_ocs_from_state['und'][0]['target_id'], $after) === FALSE ||
				array_search( $item->field_ocs_to_state['und'][0]['target_id'], $after) === FALSE) {
// 			dpm( $item->nid, 'remove state machine');
			node_delete( $item->nid);
		}
	}
	
}

function ocs_lifecycle_node_form( &$form, &$form_state, $form_id)
{

	// get lifecycle scheme nid
	$lifecycle_nid = $form['field_lifecycle_scheme']['und']['#default_value'][0];
	$scheme = node_load( $lifecycle_nid);
	
	$states = array();
	foreach( $scheme->field_lifecycle_states['und'] as $key => $value)	{
		$states[] = $value['nid'];
	}
	
	//dpm( $states, 'state list');
	
	foreach( $form['field_ocs_from_state']['und']['#options'] as $key => $value) {
		if ( array_search( $key, $states) === FALSE) {
			//dpm( $key, 'not exist');
			unset( $form['field_ocs_from_state']['und']['#options'][$key]);
		}
	}
	
	foreach( $form['field_ocs_to_state']['und']['#options'] as $key => $value) {
		if ( array_search( $key, $states) === FALSE) {
			//dpm( $key, 'not exist');
			unset( $form['field_ocs_to_state']['und']['#options'][$key]);
		}
	}
	
	unset($form['field_ocs_actions_ref']);
	unset($form['field_ocs_action_param']);
	unset($form['field_ocs_action_rule_id']);
	
	$form['field_lifecycle_scheme']['#type'] = 'hidden';
	$form['title']['#type'] = 'hidden';
	
	// ajax handler for from & to state
	/*
	$form['field_ocs_from_state']['#ajax'] = array(
			'callback' => 'ocs_lifecycle_state_callback',
			'wrapper' => 'replace_to_state_div',
	);
	
	$form['field_ocs_to_state']['#prefix'] = '<div id="replace_to_state_div">';
	$form['field_ocs_to_state']['#suffix'] = '</div>';
	*/
	
}

/*
function ocs_lifecycle_state_callback( $form, $form_state)
{
	return $form['field_ocs_to_state'];
}
*/

function ocs_lifecycle_node_form_validate( $node, $form, $form_state)
{
	// from, to state가 같은 값이면 에러
	/*
	$from_state = $node->field_ocs_from_state['und'][0]['target_id'];
	$to_state = $node->field_ocs_to_state['und'][0]['target_id'];
	if ( $from_state == $to_state ) {
		form_set_error( 'field_ocs_to_state', t('Invalid state : same as "from state"'));
	}
	*/
	
	/*
	if ( ! $form['#node_edit_form']) {
		// from, to state가 이미 존재하면 에러
		$scheme_nid = $form['field_lifecycle_scheme']['und']['#default_value'][0];
		$query = new EntityFieldQuery();
		$items = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'ocs_state_machine')
		->fieldCondition('field_lifecycle_scheme', 'nid', $scheme_nid)
		->execute();
		
		foreach( array_keys($items['node']) as $nid) {
			$item = node_load( $nid);
			if ( $item->field_ocs_from_state['und'][0]['target_id'] == $from_state &&
					$item->field_ocs_to_state['und'][0]['target_id'] == $to_state) {
				form_set_error( 'field_ocs_from_state', t('Invalid state : transition rule exists already.'));
				form_set_error( 'field_ocs_to_state', t('Invalid state : transition rule exists already.'));
			}
		}
		
	}
	*/
}

function ocs_lifecycle_action_form( $form, &$form_state, $scheme_nid, $action_id = NULL, $op = NULL)
{
	$selected_action = isset( $form_state['values']['ocs_action_id']) ? $form_state['values']['ocs_action_id'] : NULL;
	
//     if ( $op == 'edit') {
//         $edit_action = ocs_admin_rule_action_load( $action_id);
//         if ( ! isset( $selected_action)) $selected_action = $edit_action['ocs_action_id'];
//         dpm( $edit_action, 'edit');
//     }

    $form['#op'] = $op;
    $form['#action_id'] = $action_id;
    $form['#tree'] = TRUE;
    $form['#attributes'] = array( 'class' => array( 'myform'));
    
/* 	$form['redirect'] = array(
        '#type' => 'hidden',
        '#value' => isset( $_GET['redirect']) ? $_GET['redirect'] : $form_state['values']['redirect'],
    );
 */
//     $form['body'] = array(
//         '#type' => 'markup',
//         '#markup' => t( 'Select the action to add.'),
//     );

    // get available lifecycle states from the scheme
    $scheme = node_load( $scheme_nid);
    if ( ! $scheme || $scheme->type != 'lifecyclescheme') {
    	$form['body'] = array(
    		'#type' => 'markup', 
    		'#markup' => t('Invalid lifecycle scheme')
    	);
    	return $form;
    }
    
    $state_nids = array_get_value( $scheme->field_lifecycle_states);
    $options = array();
    foreach( $state_nids as $state) {
    	$node = node_load( $state);
    	$options[$state] = $node->title;
    } 
	
    // From State
    $form['to_state'] = $form['from_state'] = array(
    		'#type' => 'select',
    		'#title' => t('From State'),
    		'#options' => $options,
//     		'#required' => TRUE,
    		//    		'#description' => t('The Action shall be applied to the system.'),
    		'#ajax' => array(
    				'callback' => 'ocs_admin_ajax_action_param',
    				'wrapper' => 'campaign_action_param_div',
    		),
    );
    // To State
    $form['to_state']['#title'] = t('To State');
    
    // get all OCS events
    $events = &drupal_static( __FUNCTION__, array());
    if ( empty($events)) {
    	$items = entity_load( 'node', FALSE, array( 'type' => 'ocs_events'));
    	foreach( $items as $item) {
    		$events[$item->nid] = $item->title;
    	}
    }
    dpm( $events, 'events');
    
    $form['event'] = array(
    		'#type' => 'checkboxes',
    		'#title' => t('Event'),
    		'#options' => $events,
    		'#ajax' => array(
    				'callback' => 'ocs_admin_ajax_action_param',
    				'wrapper' => 'campaign_action_param_div',
    		),
    );
    
//     $params = new OcsParam;
//     $params->load( $selected_action, $rule_id);
    
//     foreach( $params->keylist() as $key) {
//     	$form['param'][$key] = $params->get_form( $key);
//     	if ( isset($edit_action) && isset( $edit_action['param'][$key]))  {
//     		$form['param'][$key]['#default_value'] = $edit_action['param'][$key]['value'];
//     	}
//     }
    
    
    $actions = new OcsAction;
//     dpm( $actions->select_options(), 'select options');

    $form['action_list'] = array(
    		'#type' => 'fieldset',
     		'#title' => 'Actions',
    		'#prefix' => '<div id="ocs_lifecycle_actions_div">',
    		'#suffix' => '</div>',
    );
    
    // set num_actions (AJAX)
//     if (empty($form_state['num_actions'])) {
//     	$form_state['num_actions'] = 1;
//     }
//     else if ( $form_state['triggering_element']['#name'] == 'add_more') {
//     	$form_state['num_actions'] ++;
//     }
    
    $form['action_list']['add_action'] = array(
    		'#id' => 'add-action-button',
    		'#type' => 'button',
    		'#value' => t('Add Action'),
    		'#name' => 'add_more',
    		// 		'#submit' => array('ocs_lifecycle_add_one_action'),
    // 		'#ajax' => array(
    		// 			'callback' => 'ocs_lifecycle_add_action',
    		// 			'wrapper' => 'ocs_lifecycle_actions_div',
    		// 		)
    );
    
    
    $options = $actions->select_options();
    
    for( $i=0; $i < 10; $i++) {
    	$form['action_list']['action_'.$i] = array(
    		'#type' => 'select',
    		'#title' => t('Action ' . ($i+1)),
    		'#options' => $options,
    			// 		'#default_value' => $selected_action,
//     			'#description' => t('The Action shall be applied to the system.'),
//     		'#ajax' => array(
//     			'callback' => 'ocs_admin_ajax_action_param',
//     			'wrapper' => 'campaign_action_param_div',
//     		),
    		'#prefix' => t('<div class="hide action-@i">', array( '@i' => $i)),
    		'#suffix' => '</div>',
    	);
    }
    
//     unset( $form['action_list']['action_0']['#prefix']);
//     unset( $form['action_list']['action_0']['#suffix']);

    $form['num_action'] = array(
    	'#type' => 'hidden',
    	'#value' => '0',
    );
    
	
// 	// get list of parameters
// 	$form['param'] = array(
// 		'#type' => 'fieldset',
// 		'#title' => 'Parameters',
// 		'#prefix' => '<div id="campaign_action_param_div">',
// 		'#suffix' => '</div>',
// 		);

//     $params = new OcsParam;
//     $params->load( $selected_action, $rule_id);

//     foreach( $params->keylist() as $key) {
//         $form['param'][$key] = $params->get_form( $key);
//         if ( isset($edit_action) && isset( $edit_action['param'][$key]))  {
//             $form['param'][$key]['#default_value'] = $edit_action['param'][$key]['value'];
//         }
//     }

// 	$form['#param_name_list'] = $params->keylist();

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );

    $form['actions']['cancel'] = array(
        '#type' => 'submit',
        '#value' => t('Cancel'),
    );
	
    return $form;
}

function ocs_lifecycle_add_action( $form, &$form_state)
{
// 	dpm( $form, 'callback - form');
// 	dpm( $form_state, 'callback - form_state');
	
	return $form['action_list'];
}

/**
 * Submit handler for the "add-one-more" button.
 *
 * Increments the max counter and causes a rebuild.
 */
function ocs_lifecycle_add_one_action($form, &$form_state) 
{
// 	dpm( $form_state['num_actions'], 'num actions');
	
	$form_state['num_actions']++;
	$form_state['rebuild'] = TRUE;
}

function ocs_lifecycle_action_form_submit( $form, &$form_state)
{
	dpm( $form, 'submit form');
	dpm( $form_state, 'submit form_state');
}
