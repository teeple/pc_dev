<?php

function _array_message($nid = NULL)
{
	$jsonData = array();

	//fetch data
	$viewResult = views_get_view_result('ocs_messages', 'panel_json', $nid);
	// dpm( $viewResult, 'messages');

	foreach ($viewResult as $record) {
		$msg = array();
		$msg['message_id'] = isset($record->nid) ? $record->nid : null;
		$format = $record->field_field_ocs_format[0]['raw']['value'];
		$msg['name'] = $record->node_title;
		$msg['format'] = preg_replace('/%\d+/', '%s', $format);
		foreach( $record->field_field_ocs_export_format as $export) {
			$msg['ui_param'][] = $export['rendered']['#markup'];
		}
		
		$jsonData['messages'][] = $msg;
	}

	$viewResult = views_get_view_result('ocs_message_group', 'panel_json', $nid);
	// dpm( $viewResult, 'messages');

	$msg = array();
	foreach ($viewResult as $record) {
		$msg_nid = $record->field_field_ocs_message_list[0]['rendered']['#markup'];
		if ( node_load( $msg_nid)) {
			// check if the node exist
			$msg[$record->nid]['message_id'] = isset($record->nid) ? $record->nid : null;
			$msg[$record->nid]['name'] = $record->node_title;
			$msg[$record->nid]['composed_messages'][] = $msg_nid;
		}
	}
	
	$jsonData['messages'] = array_merge( $jsonData['messages'], array_values( $msg));
	
	return $jsonData;
}

function _json_message($nid = NULL)
{
	$retArray = array();
	$jsonData = _array_message($nid);
	$retArray = $jsonData;

	$enc = ($nid != NULL) ? json_encode($jsonData) : json_encode($retArray);
		
	// write to file
    try{
        $fd = fopen( '/tmp/export_message.json', 'w');
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