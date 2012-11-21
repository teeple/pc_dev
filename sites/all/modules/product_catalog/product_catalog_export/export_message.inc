<?php

function _array_lifecycle_scheme($nid=NULL){
    $jsonData = array();

/*
	$query = new EntityFieldQuery();

	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'lifecyclescheme')
		->execute();
		
	foreach( array_keys($result['node']) as $nid) {
		// read lifecycle scheme node
		$node = node_load( $nid);
		
		$scheme = array(
			'name' => $node->title,
			'service domain' => $node
 		);
	}
 *
 */
	
    //fetch data    
    $viewResult = views_get_view_result('list_lifecycle_scheme', 'panel_json', $nid);
	//dpm( $viewResult, 'lifecycle scheme');
	
	foreach( $viewResult as $record) {
		$scheme['id'] = isset( $record->nid) ? $record->nid : null;
		$scheme['title'] = isset( $record->node_title) ? $record->node_title : null;
		$scheme['domain'] = isset( $record->field_field_service_domain) ? $record->field_field_service_domain[0]['rendered']['#title'] : null;
		
		// state list
		$states = array();
		foreach( $record->field_field_lifecycle_states as $state) {
			$states[] = $state['rendered']['#title'];
		}
		
		$scheme['states'] = $states;
		
		if ( $record->nid) {
			// get permissions
			$view_perm = views_get_view_result('ocs_svc_perm', 'panel_json', $record->nid);
			
			$perm = array();
			foreach( $view_perm as $node) {
				if ( !empty( $node->field_field_service_permission))
					$perm[ $node->field_field_lifecycle_state[0]['rendered']['#markup']][] = 
						$node->field_field_service_permission[0]['rendered']['#markup'];
			}
			
			$scheme['permission'] = $perm;
			
			// get state transition rules
			$view_transition = views_get_view_result('ocs_state_machine', 'panel_json', $record->nid);
			//dpm( $view_transition, 'transition');
			
			$transition = array();
			foreach( $view_transition as $node) {
				$rule['from'] = $node->field_field_ocs_from_state[0]['rendered']['#markup'];
				$rule['to'] = $node->field_field_ocs_to_state[0]['rendered']['#markup'];
				
				foreach( $node->field_field_ocs_trigger_events as $event) {
					$rule['event'][] = $event['rendered']['#markup'];
				}
				
				// get transition actions
				$view_actions = views_get_view_result('ocs_list_transition_actions', 'panel_json', $node->nid);
				
				$rule['actions'] = array();
				foreach( $view_actions as $node) {
					$action['action'] = $node->field_field_ocs_action[0]['rendered']['#markup'];
				
					foreach( $node->field_field_ocs_action_param_values as $value) {
						$action['parameters'][] = $value['rendered']['#markup'];
					}
					$rule['actions'][] = $action;
				}
				
				$transition[] = $rule;
			}
			
			$scheme['transition'] = $transition;
		}
		
		
		$jsonData[] = $scheme;
	}

    return $jsonData;   
}

function _json_lifecycle_scheme($nid=NULL) {
    $retArray = array();
    $jsonData  = _array_lifecycle_scheme($nid);
    $retArray['lifecycle_scheme'] = $jsonData;

    if($nid != NULL) {
        return json_encode($jsonData);
    } else {
        return json_encode($retArray);
    }
}
