<?php

function _array_lifecycle_scheme($exportItemNids=NULL){
		$jsonData = array();
		$jsonData_schemes = array();
    $schemeIds = array();
    
	if(!empty($exportItemNids) && count($exportItemNids) > 1) {
		$exportItemNids = join('+', $exportItemNids);
	}
		
    //fetch data    
    $viewResult = views_get_view_result('list_lifecycle_scheme', 'panel_json', $exportItemNids);
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
			dpm( $view_perm, 'view perm');
			
			$state_period = array();
			$state_noti_before = array();
			$perm = array();
			foreach( $view_perm as $node) {
				$state_name = $node->field_field_lifecycle_state[0]['rendered']['#markup'];
				if (!empty( $node->field_field_service_permission))
					foreach($node->field_field_service_permission as $item) {
						$perm['service_permission'][ $state_name][] = $item['rendered']['#markup'];
					}
				if (!empty( $node->field_field_nonusage_permission))
					foreach($node->field_field_nonusage_permission as  $item) {
						$perm['nonusage_permission'][ $state_name][] = $item['rendered']['#title'];	
					}
				if (!empty( $node->field_field_feature_codes))
					foreach($node->field_field_feature_codes as  $item) {
						$perm['feature_code'][ $state_name][] = $item['rendered']['#markup'];	
					}
				if ( !empty( $node->field_field_max_duration)) {
					$state_period[ $state_name] = intval( $node->field_field_max_duration[0]['raw']['value']);
				}
				if ( !empty( $node->field_field_notification_before)) {
					$state_noti_before[ $state_name] = intval( $node->field_field_notification_before[0]['raw']['value']);
				}
				if ( !empty( $node->field_field_notification_by)) {
					$state_noti_by[ $state_name] = $node->field_field_notification_by[0]['rendered']['#title'];	
				}
			}
			
			$scheme['permission'] = $perm;
			$scheme['state_period'] = $state_period;
			$scheme['noti_before'] = $state_noti_before;
			$scheme['noti_by'] = $state_noti_by;
			
			// get state transition rules
			$view_transition = views_get_view_result('ocs_state_machine', 'panel_json', $record->nid);
			//dpm( $view_transition, 'transition');
			
			$transition = array();
			foreach( $view_transition as $tr) {
				$rule = array();
				$rule['from'] = $tr->field_field_ocs_from_state[0]['rendered']['#markup'];
				$rule['to'] = $tr->field_field_ocs_to_state[0]['rendered']['#markup'];

				// get transition actions
				$view_actions = views_get_view_result('ocs_list_transition_actions', 'panel_json', $tr->nid);
				// dpm( $view_actions, 'view actions');
				
				$rule['actions'] = array();
				foreach( $view_actions as $a) {
					$action = array();
					$action['action'] = $a->field_field_ocs_action[0]['rendered']['#markup'];
					$action['parameters'] = _decode_action_param_values( $a->field_field_ocs_action_param_values);

					$rule['actions'][] = $action;
				}
				
								
				foreach( $tr->field_field_ocs_trigger_events as $event) {
					$rule['event'] = $event['rendered']['#markup'];
					
					// 각 event 별로 transition rule을 넣기 위해 아래와 같이 처리함 
					$transition[] = $rule;
				}
			}
			
			$scheme['transition'] = $transition;
		}
		$jsonData_schemes[] = $scheme;
		$schemeIds[] = $scheme['id'];
	}
	
	if($exportItemNids!=NULL) {
		$jsonData_common['resources'] = $schemeIds;
	} else {
	  $jsonData_common['resources'] = array();
	}
	  $jsonData_common['resources'] = array();
	
	$jsonData['ifvalues'] = $jsonData_common;
	$jsonData['lifecycle_scheme'] = $jsonData_schemes;

	$arr = array();
	$arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "rating_status_permission", $exportItemNids);
	foreach($arr as $a)
	{
		foreach($a as $t => $v)
		{
			$jsonData['rating_rules'][$t] = $v;
		}
	}
	
    return $jsonData;   
}

// string fomat : Array( [0]=>13033:12191=0212355,[1]=>13033:12184=0, 13033:12186=12336)
function _decode_action_param_values( $param_list)
{
	$output = array();
	foreach( $param_list as $param) {
		list($k,$v) = explode( '=', $param['rendered']['#markup'], 2);
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



function _json_lifecycle_scheme($exportItemNids=NULL) {
    $retArray = array();
    $jsonData  = _array_lifecycle_scheme($exportItemNids);
    // $retArray['lifecycle_scheme'] = $jsonData;
    $retArray = $jsonData;

    // $enc = ($exportItemNids != NULL) ? json_encode($jsonData) : json_encode($retArray);
    $enc = json_encode($retArray);
    
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
