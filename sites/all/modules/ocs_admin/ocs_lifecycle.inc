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


/*
    scheme_nid : lifecycle scheme nid
    action_nid : transition rule nid
*/
function ocs_lifecycle_action_form( $form, &$form_state, $scheme_nid, $action_nid = NULL)
{
	$selected_action = isset( $form_state['values']['ocs_action_id']) ? $form_state['values']['ocs_action_id'] : NULL;

    if ( $action_nid != NULL) {
        // edit mode            
        $form['#op'] = 'edit';
    }
    else {
        $form['#op'] = 'add';
    }
    $form['#action_nid'] = $action_nid;
    $form['#scheme_nid'] = $scheme_nid;
    $form['#action_list'] = NULL;
    $form['#tree'] = TRUE;
    $form['#attributes'] = array( 'class' => array( 'myform'));
    
 	$form['redirect'] = array(
        '#type' => 'hidden',
        '#value' => isset( $_GET['redirect']) ? $_GET['redirect'] : $form_state['values']['redirect'],
    );

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
//    dpm( $events, 'events');
    
    $form['event'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Event'),
        '#options' => $events,
        '#required' => TRUE,
    );

    // edit mode
    $action_node = NULL;
    if ( $action_nid ) {
        $action_node = node_load( $action_nid);
//        dpm( $node, 'edit node');

        $form['from_state']['#default_value'] = $action_node->field_ocs_from_state['und'][0]['target_id'];
        $form['to_state']['#default_value'] = $action_node->field_ocs_to_state['und'][0]['target_id'];
        $events = array_get_value( $action_node->field_ocs_trigger_events);
        $form['event']['#default_value'] = $events;

        // load related actions
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'ocs_transition_actions')
            ->fieldCondition('field_ocs_transition', 'nid', $action_nid)
            ->execute();

        // action_list = array of nid of actions
        $action_list = array();
        if ( count($result) > 0) {
            foreach( array_keys( $result['node']) as $nid) {
                $action_list[] = node_load( $nid);
            }
        }
        
        $form['#action_list'] = $action_list;
    }
	 
    $form['action_list'] = array(
        '#type' => 'fieldset',
        '#title' => 'Actions',
        '#prefix' => '<div id="ocs_lifecycle_actions_div">',
        '#suffix' => '</div>',
    );

  
    $form['action_list']['add_action'] = array(
//    		'#id' => 'add-action-button',
        '#type' => 'button',
        '#value' => t('Add Action'),
        '#name' => 'add_more',
        '#submit' => array('ocs_lifecycle_add_one_action'),
        '#ajax' => array(
            'callback' => 'ocs_lifecycle_add_action',
            'wrapper' => 'ocs_lifecycle_actions_div',
         ),
        '#attributes' => array( 'class' => array( 'inner-box-1')),
    );
    
    if ( $form['#op'] == 'edit') {
        // set number of actions
        $form_state['num_actions'] = count( $action_list);
    }
    else {
        // set num_actions (AJAX)
        if (empty($form_state['num_actions'])) {
            $form_state['num_actions'] = 1;
        }
        else if ( $form_state['triggering_element']['#name'] == 'add_more') {
            $form_state['num_actions'] ++;
        }

    }


    $actions = new OcsAction;
//     dpm( $actions->select_options(), 'select options');

    $options = $actions->select_options();
//    dpm( $options, 'actions');
    
    for( $i=1; $i <= $form_state['num_actions']; $i++) {
        $form['action_list'][$i] = array(
            '#type' => 'fieldset',
            '#attributes' => array( 'class' => array( 'inner-box-1')),
        );
        
        // get selected action
        if ( $form['#op'] == 'edit') {
            // edit mode
//            dpm( $action_list, 'action list to edit');
            $selected_action = $action_list[$i-1]->field_ocs_action['und'][0]['nid'];
        }
        else {
            $selected_action = ( isset( $form_state['values'])) ? 
                $form_state['values']['action_list'][$i]['action_'.$i] : 0;
        }

//        dpm( $selected_action, 'sel');
//        dpm( $options, 'options');

     	$form['action_list'][$i]['action_'.$i] = array(
    		'#type' => 'select',
    		'#title' => t('Action #' . $i),
    		'#options' => $options,
            '#default_value' => $selected_action,
     		'#ajax' => array(
                // change parameters if the selected action is changed
     			'callback' => 'ocs_lifecycle_select_action',
     			'wrapper' => 'ocs_lifecycle_actions_' . $i . '_div',
     			//'wrapper' => 'ocs_lifecycle_actions_div',
     		),
            '#prefix' => '<div class="inner-box-header">',
            '#suffix' => '</div>',
    	);

        $form['action_list'][$i]['param_'.$i] = array(
            '#type' => 'fieldset',
            '#attributes' => array( 'class' => array( 'inner-box-2')),
            '#prefix' => '<div id="ocs_lifecycle_actions_' . $i . '_div">',
            '#suffix' => '</div>',
        );

        if ( $selected_action) {
            $params = new OcsParam;
            $params->load( $selected_action, $scheme_nid);

            // keylist() return an array with values: Array ( [0] => 13033:12192 [1] => 13033:12183 )
            foreach( $params->keylist() as $key) {
                $form['action_list'][$i]['param_'.$i][$key] = $params->get_form( $key);
            }

            // set parameter values
            //dpm( $action_list[$i-1], 'action list');
            if ( $form['#op'] == 'edit' && ! empty( $action_list[$i-1]->field_ocs_action_param_values)) {
                foreach( $action_list[$i-1]->field_ocs_action_param_values['und'] as $value) {
                    list($k,$v) = explode( '=', $value['value']);
                    //dpm( $value, 'value'); 
                    $form['action_list'][$i]['param_'.$i][$k]['#default_value'] = $v;
                }
            }
        }
        else {
            $form['action_list'][$i]['param_'.$i]['no_action'] = array(
                '#type' => 'markup',
                '#markup' => '<p>No Parameters</p>',
            );
        }
    }
    
// 	// get list of parameters
// 	$form['param'] = array(
// 		'#type' => 'fieldset',
// 		'#title' => 'Parameters',
// 		'#prefix' => '<div id="campaign_action_param_div">',
// 		'#suffix' => '</div>',
// 		);

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

function ocs_lifecycle_select_action( $form, $form_state)
{
    /*
    return array(
        '#type' => 'markup',
        '#markup' => print_r( $form_state['triggering_element'], TRUE), 
    );
    */
    // #name has format 'action_list[1][action_1]'
    $element = preg_split( '/[\[\]]/', $form_state['triggering_element']['#name']);
    $idx = $element[1];
    return $form['action_list'][$idx]['param_'.$idx];
}

function ocs_lifecycle_action_form_validate( $form, &$form_state)
{
    $values = $form_state['values'];

    if ( $values['op'] != 'Cancel') {
        if ( $values['from_state'] == $values['to_state'] ) {
            form_set_error( 'to_state', t('Invalid state : same as "from state"'));
        }

		// from, to state가 이미 존재하면 에러
		$scheme_nid = $form['#scheme_nid'];

		$query = new EntityFieldQuery();
		$items = $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'ocs_state_machine')
            ->fieldCondition('field_lifecycle_scheme', 'nid', $scheme_nid)
            ->execute();
		
        if ( count( $items) > 0) {
            $conflict = array();
            $new_events = array_get_value( $values['event']);
            foreach( array_keys($items['node']) as $nid) {
                if ( $nid == $form['#action_nid']) continue;    // skip this node
                $item = node_load( $nid);
                if ( $item->field_ocs_from_state['und'][0]['target_id'] == $values['from_state'] &&
                        $item->field_ocs_to_state['und'][0]['target_id'] == $values['to_state']) {

                    $old_events = array_get_value( $item->field_ocs_trigger_events);
                    $intersect = array_intersect( $old_events, $new_events);

                    if ( count( $intersect) > 0) {
                        foreach( $intersect as $nid ) {
                            $node = node_load( $nid);
                            $conflict[] = $node->title;
                        }
                    }
                }
            }
            if ( count( $conflict) > 0) {
                form_set_error( 'event', t('Invalid events : transition rule exists already for the events: @list.', 
                    array( '@list' => implode(', ', $conflict))));
            }
		}
    }
}

function ocs_lifecycle_action_form_submit( $form, &$form_state)
{
    $values = $form_state['values'];

    if ( $values['op'] != 'Cancel') {
        // save ocs_state_machine
        if ( $form['#op'] == 'add') {
            $node = ocs_admin_get_new_node('ocs_state_machine');
            $node->field_lifecycle_scheme['und'][0]['nid'] = $form['#scheme_nid'];
            $node->title = 'transition for schemem '. $form['#scheme_nid'];
        }
        else {
            $node = node_load( $form['#action_nid']);
        }

        // set from & to state
        $node->field_ocs_from_state['und'][0]['target_id'] = $values['from_state'];
        $node->field_ocs_to_state['und'][0]['target_id'] = $values['to_state'];

        // set trigger events
        unset( $node->field_ocs_trigger_events['und']);
        foreach( array_values( $values['event']) as $event) {
            if ( $event) $node->field_ocs_trigger_events['und'][] = array( 'target_id' => $event);
        }

        node_save( $node);

        // store actions
        // format of $values['action_list']  
        //      $values['action_list'][$i]['action_'.$i]
        foreach( $values['action_list'] as $key => $value) {
            if ( is_numeric( $key) && ! empty($value['action_'.$key])) {
                if ( $key <= count($form['#action_list'])) {
                    // old action
                    $action = $form['#action_list'][$key-1];
                }
                else {
                    // new action
                    $action = ocs_admin_get_new_node( 'ocs_transition_actions');
                    $action->title = 'action for transition ' . $node->nid;
                }

                $action->field_ocs_transition['und'][0]['nid'] = $node->nid;
                $action->field_ocs_action['und'][0]['nid'] = $value['action_'.$key];

                // store parameter values
                if ( isset( $value['param_'.$key])) {
                    $idx = 0;
                    foreach( $value['param_'.$key] as $p => $v ) {
                        // store parameter name and value
                        $action->field_ocs_action_param_values['und'][$idx++] = array( 'value' => $p . '=' . $v);
                    }
                }

                node_save( $action);
            }
        }

    }

    if ( isset( $values['redirect'])) $form_state['redirect'] = $values['redirect'];
}
