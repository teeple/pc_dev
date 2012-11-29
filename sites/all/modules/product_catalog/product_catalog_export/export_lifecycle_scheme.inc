<?php

function _array_lifecycle_scheme($nid=NULL){
    $jsonData = array();

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
				// dpm( $view_actions, 'view actions');
				
				$rule['actions'] = array();
				foreach( $view_actions as $node) {
					$action = array();
					$action['action'] = $node->field_field_ocs_action[0]['rendered']['#markup'];
					$action['parameters'] = _decode_action_param_values( $node->field_field_ocs_action_param_values);

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

// string fomat : Array( [0]=>13033:12191=0212355,[1]=>13033:12184=0, 13033:12186=12336)
function _decode_action_param_values( $param_list)
{
	$output = array();
	foreach( $param_list as $param) {
		list($k,$v) = explode( '=', $param['rendered']['#markup']);
		list($action_nid,$param_nid) = explode( ':', $k);

		$param = node_load( $param_nid);

		if ( $param->field_ocs_param_type['und'][0]['value'] == OCS_PARAM_TYPE_ENUM) {
			$options = array_flip( json_decode( $param->field_ocs_param_value['und'][0]['value'], TRUE));
			$v = $options[$v];
        }
		
		$output[$param->title] = $v;
	}

	return $output;
}



function _json_lifecycle_scheme($nid=NULL) {
    $retArray = array();
    $jsonData  = _array_lifecycle_scheme($nid);
    $retArray['lifecycle_scheme'] = $jsonData;

    $enc = ($nid != NULL) ? json_encode($jsonData) : json_encode($retArray);
    
	// write to file
    try{
        $fd = fopen( '/tmp/export_lifecycle.json', 'w');
        fwrite( $fd, $enc);
        fclose( $fd);
// 
        // $ip_address = variable_get('ocs_admin_ip_address', 'Administrative Warning');
        // $user = variable_get('ocs_admin_user_account', 'Administrative Warning');
        // $passwd = variable_get('ocs_admin_user_password', 'Administrative Warning');
        // $dir = variable_get('ocs_admin_config_directory', 'Administrative Warning');
// 
        // // ftp to host
        // if ( ocs_admin_ftp_put( $ip_address, $user, $passwd, $dir, $file_name)) {
            // drupal_set_message( t('Configuration file "@name" is uploaded to the OCS',
                // array( '@name' => $file_name)));
        // }
    }
    catch( Exception $e) {
        drupal_set_message( $e->getMessage(), 'warning');       
    }
    
    return $enc;
}
