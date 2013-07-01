<?php

function _array_ocs_config($nid = NULL) {
  $jsonData = array();

  //fetch data
  $viewResult = views_get_view_result('list_ocs_config', 'json', $nid);
  //dpm( $viewResult, 'ocs global config');

  foreach ($viewResult as $record) {
    //dsm($record,'record');
    $jsonData['MAX_AMOUNT_OF_REMAINS'] = $record -> field_field_max_amount_of_remains[0]['raw']['value'];
    //$jsonData['MAX_AMOUNT_OF_SMS'] = $record -> field_field_max_amount_of_sms[0]['raw']['value'];
    $jsonData['ROAMING_SMS_MONEY'] = $record -> field_field_roaming_sms_money[0]['raw']['value'];
    $jsonData['ROAMING_BOTH_MONEY'] = $record -> field_field_roaming_both_money[0]['raw']['value'];
    $jsonData['PPS_SHORT_CALL_TIME'] = $record -> field_field_pps_short_call_time[0]['raw']['value'];
    $jsonData['POST_SHORT_CALL_TIME'] = $record -> field_field_post_short_call_time[0]['raw']['value'];
    $jsonData['HYB_SHORT_CALL_TIME'] = $record -> field_field_hyb_short_call_time[0]['raw']['value'];
    $jsonData['MAX_POST_LASTCALL_OVERPRICE'] = $record -> field_field_maxpost_lastcall_overprice[0]['raw']['value'];
    $jsonData['DEFAULT_PACKET_RATING_GROUP'] = $record -> field_field_default_packet_rating_grou[0]['raw']['value'];
    $jsonData['DEFAULT_PACKET_VOLUME'] = $record -> field_field_default_packet_volume[0]['raw']['value'];
    $jsonData['DEFAULT_PACKET_CHARGING_VOLUME'] = $record -> field_field_default_packet_charging_vo[0]['raw']['value'];
    $jsonData['DEFAULT_PACKET_TIME'] = $record -> field_field_default_packet_time[0]['raw']['value'];
    $jsonData['DEFAULT_PACKET_CHARGING_TIME'] = $record -> field_field_default_packet_charging_ti[0]['raw']['value'];
    $jsonData['DEFAULT_PACKET_FINAL_UNIT_ACTION'] = $record -> field_field_default_packet_final_unit_[0]['raw']['value'];
    $jsonData['DEFAULT_PACKET_REDIRECT_SERVER_URL'] = $record -> field_field_default_packet_redirec_ser[0]['raw']['safe_value'];
    $jsonData['DEFAULT_ENTRY_VOUCHER_TYPE'] = $record -> field_field_default_entry_voucher_type[0]['raw']['safe_value'];
    break;
  }
  $retData['ocs_global_config']['config'] = $jsonData;

  //fetch data
  $viewResult = views_get_view_result('list_ussd_code', 'json', $nid);
  //dpm( $viewResult, 'ocs global config');

  $jsonData = array();
  foreach ($viewResult as $record) {
    //dsm($record,'record');
    $jsonData[] = array(
        'access_code' => $record->node_title,
        'desc' => 'PREPAID_BALANCE_QUERY',
        'action' => array(
            'parameters' => array( 'dest' => 'CALLING', 
                'message' => $record->field_field_notification_message[0]['raw']['nid'])));
  }
  $retData['ocs_global_config']['ussd_access_code'] = $jsonData;
  $retData['ifvalues']['resources'] = array();

  return $retData;
}

function _json_ocs_config($nid = NULL) {
  $retArray = array();
  $jsonData = _array_ocs_config($nid);
  // $retArray['lifecycle_scheme'] = $jsonData;
  $retArray = $jsonData;

  $enc = ($nid != NULL) ? json_encode($jsonData) : json_encode($retArray);

  // write to file
  try {
    $fd = fopen('/tmp/export_ocs_config.json', 'w');
    fwrite($fd, $enc);
    fclose($fd);
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
  } catch( Exception $e) {
    drupal_set_message($e -> getMessage(), 'warning');
  }

  return $enc;
}
