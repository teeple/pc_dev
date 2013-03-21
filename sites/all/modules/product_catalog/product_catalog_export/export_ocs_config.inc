<?php

function _array_ocs_config($nid=NULL){
    $jsonData = array();

    //fetch data    
    $viewResult = views_get_view_result('list_ocs_config', 'json', $nid);
	//dpm( $viewResult, 'ocs global config');
	
	foreach( $viewResult as $record) {
	    dsm($record,'record');
		$jsonData['MAX_AMOUNT_OF_REMAINS'] = $record->field_field_max_amount_of_remains[0]['raw']['value'];
		$jsonData['MAX_AMOUNT_OF_SMS'] = $record->field_field_max_amount_of_sms[0]['raw']['value'];
		$jsonData['ROAMING_SMS_MONEY'] = $record->field_field_roaming_sms_money[0]['raw']['value'];
		$jsonData['ROAMING_BOTH_MONEY'] = $record->field_field_roaming_both_money[0]['raw']['value'];
		$jsonData['PPS_SHORT_CALL_TIME'] = $record->field_field_pps_short_call_time[0]['raw']['value'];
		$jsonData['MAX_POST_LASTCALL_OVERPRICE'] = $record->field_field_maxpost_lastcall_overprice[0]['raw']['value'];
		$jsonData['DEFAULT_PACKET_RATING_GROUP'] = $record->field_default_packet_rating_grou[0]['raw']['value'];
        $jsonData['DEFAULT_PACKET_VOLUME'] = $record->field_default_packet_volume[0]['raw']['value'];
        $jsonData['DEFAULT_PACKET_CHARGING_VOLUME'] = $record->field_default_packet_charging_vo[0]['raw']['value'];
        $jsonData['DEFAULT_PACKET_TIME'] = $record->field_default_packet_time[0]['raw']['value'];
        $jsonData['DEFAULT_PACKET_CHARGING_TIME'] = $record->field_default_packet_charging_ti[0]['raw']['value'];
        
		break;
	}
	$retData['ifvalues']['resources'] = array();
	$retData['ocs_global_config'] = $jsonData;

    return $retData;   
}


function _json_ocs_config($nid=NULL) {
    $retArray = array();
    $jsonData  = _array_ocs_config($nid);
    // $retArray['lifecycle_scheme'] = $jsonData;
    $retArray = $jsonData;

    $enc = ($nid != NULL) ? json_encode($jsonData) : json_encode($retArray);
    
	// write to file
    try{
        $fd = fopen( '/tmp/export_ocs_config.json', 'w');
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
