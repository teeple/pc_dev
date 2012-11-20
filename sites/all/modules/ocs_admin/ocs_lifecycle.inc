<?php


/* this function shall be called after saving a new lifecycle scheme */
function ocs_admin_check_lifecycle_scheme( $node, $node_unchanged)
{
// 	dpm( $node, 'node');
// 	dpm( $node_unchanged, 'unchanged');
	
	$after = array_get_value( $node->field_lifecycle_states, FALSE);
	$before = array_get_value( $node_unchanged->field_lifecycle_states, FALSE);
	
 	dpm( $after, 'after');
 	dpm( $before, 'before');
	
	$intersect = array_intersect( $before, $after);
	$removed = array_diff( $before, $intersect);
	$added = array_diff( $after, $intersect);
	
	dpm( $added. 'nodes to add');
	dpm( $removed, 'nodes to remove');
	dpm( $intersect, 'node intersect');
	
	// check ocs_svc_perm
	// ocs_svc_perm에는 title이 node->nid인 instance 들이 저장되어 있다.
	// 이중에서 state 값이 added, removed에 속한 것을 추가/삭제한다.
	$node_list = ocs_get_nodes_by_node_ref( 'ocs_svc_perm', 'field_lifecycle_scheme', $node->nid);
	
	// action_list = array of nid of actions
	$action_list = array();
	foreach ( $node_list as $nid) {
		$item = node_load( $nid);

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
		$new_node->title = 'Service permission for state:' . $add_node_nid . ' scheme:' . $node->nid;
		$new_node->field_lifecycle_state['und'][0]['nid'] = $add_node_nid;
		$new_node->field_lifecycle_scheme['und'][0]['nid'] = $node->nid;
		node_save( $new_node);
		
		//dpm( $new_node, 'add node');
	}
	
	// check ocs_state_machine
	$node_list = ocs_get_nodes_by_node_ref('ocs_state_machine', 'field_lifecycle_scheme', $node->nid);
	foreach ( $node_list as $nid) {
		$item = node_load( $nid);
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
}



/*
    scheme_nid : lifecycle scheme nid
    transition_nid : transition rule nid
*/
function ocs_lifecycle_transition_form( $form, &$form_state, $scheme_nid, $transition_nid = NULL)
{
	if ( $transition_nid != NULL) {
        // edit mode            
        $form['#op'] = 'edit';
    }
    else {
        $form['#op'] = 'add';
    }
    $form['#action_nid'] = $transition_nid;
    $form['#scheme_nid'] = $scheme_nid;
    $form['#action_list'] = NULL;
    $form['#tree'] = TRUE;
    $form['#attributes'] = array( 'class' => array( 'myform'));
    
    // get available lifecycle states from the scheme
    $scheme = node_load( $scheme_nid);
    if ( ! $scheme || $scheme->type != 'lifecyclescheme') {
    	$form['body'] = array(
    		'#type' => 'markup', 
    		'#markup' => t('Invalid lifecycle scheme')
    	);
    	return $form;
    }
    
    $state_nids = array_get_value( $scheme->field_lifecycle_states, FALSE);
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
    if ( $transition_nid ) {
        $action_node = node_load( $transition_nid);
//        dpm( $node, 'edit node');

        $form['from_state']['#default_value'] = $action_node->field_ocs_from_state['und'][0]['target_id'];
        $form['to_state']['#default_value'] = $action_node->field_ocs_to_state['und'][0]['target_id'];
        $events = array_get_value( $action_node->field_ocs_trigger_events);
        $form['event']['#default_value'] = $events;

        // load related actions
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'ocs_transition_actions')
            ->fieldCondition('field_ocs_transition', 'nid', $transition_nid)
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
    
    // set num_actions (AJAX)
    if ( !isset($form_state['num_actions'])) {
    	$form_state['num_actions'] = ( $form['#op'] == 'edit') ? count( $action_list) : 1;
    }
    else if ( isset( $form_state['triggering_element']) && $form_state['triggering_element']['#name'] == 'add_more') {
    	$form_state['num_actions'] ++;
    }
    dpm( $form_state['num_actions'], 'num_actions');
    
    $actions = new OcsAction;
//     dpm( $actions->select_options(), 'select options');

    $options = $actions->select_options();
//    dpm( $options, 'actions');
    
    for( $i=1; $i <= $form_state['num_actions']; $i++) {
        $form['action_list'][$i] = array(
            '#type' => 'fieldset',
            '#attributes' => array( 'class' => array( 'inner-box-1 border')),
        );
        
        // get selected action
        $selected_action = ( isset( $form_state['values'])) ?
        	$form_state['values']['action_list'][$i]['action_'.$i] :
        		(( $form['#op'] == 'edit') ?                            // edit mode
        		$action_list[$i-1]->field_ocs_action['und'][0]['nid'] : 0);
    
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
            '#attributes' => array( 'class' => array( 'inner-box-2 border')),
            '#prefix' => '<div id="ocs_lifecycle_actions_' . $i . '_div">',
            '#suffix' => '</div>',
        );

        if ( $selected_action) {
            $params = new OcsParam;
            $params->load( $selected_action);

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

function ocs_lifecycle_transition_form_validate( $form, &$form_state)
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

function ocs_lifecycle_transition_form_submit( $form, &$form_state)
{
    $values = $form_state['values'];
//     dpm( $values, 'submit values');

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
            if ( is_numeric( $key)) {
            	
                if ( $key <= count($form['#action_list'])) {
                    // old action
                    $action = $form['#action_list'][$key-1];
                }
                else {
            		if ( empty($value['action_'.$key])) {
            			continue;	// if the key values is empty, it's 'No Action'
            		}
                    // new action
                    $action = ocs_admin_get_new_node( 'ocs_transition_actions');
                    $action->title = 'action for transition ' . $node->nid;
                }

                if ( $value['action_'.$key] == 0) {
                	// delete node, if it's 'No Action'
					node_delete( $action->nid);                	
                }
                else {
                	// update the contents otherwise
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

    }
}

/*
 ** delete action
*/
function ocs_lifecycle_transition_delete_form( $form, &$form_state, $scheme_nid, $transition_nid)
{
	$node = node_load( $transition_nid);
	
	$events = array_get_value( $node->field_ocs_trigger_events);
	$event_list = '';
	foreach( $events as $nid ) {
		$event_list .= '<li>' . ocs_node_title( $nid) . '</li>';
	}
	
	$caption = t('<strong>Warning:</strong> The transition from <em>@from_state</em> to <em>@to_state</em> in following events will be deleted.
		<ul class="form-item">!list</ul>', 
			array( '@from_state' => ocs_node_title($node->field_ocs_from_state['und'][0]['target_id']),
					'@to_state' => ocs_node_title( $node->field_ocs_to_state['und'][0]['target_id']),
					'!list' => $event_list
					));

	dpm( $_GET, 'get');
	
	$form['#transition_nid'] = $transition_nid;
	
	dpm( $form, 'form');
	
	return confirm_form( $form, t('Are you sure to delete the transition rule ?'), NULL, $caption, t('Delete'));
}

function ocs_lifecycle_transition_delete_form_submit( $form, &$form_state)
{
	$transition_nid = $form['#transition_nid'];
	node_delete( $transition_nid);
	
	// remove all actions
	ocs_delete_all_actions_of_transition( $transition_nid);
	
	drupal_set_message( t('The transition has been deleted.'));
}

function ocs_delete_all_actions_of_transition( $transition)
{	
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
	->entityCondition('bundle', 'ocs_transition_actions')
	->fieldCondition('field_ocs_transition', 'nid', $transition)
	->execute();
	
	if ( ! empty( $result)) {
		foreach( array_keys($result['node']) as $nid) {
			drupal_set_message( t('Action ' . $nid . ' deleted'));
			node_delete( $nid);		// delete action
		}
	}
}