<?php

function _array_message($nid=NULL){
    $jsonData = array();
	
    //fetch data    
    $viewResult = views_get_view_result('ocs_messages', 'panel_json', $nid);
	// dpm( $viewResult, 'messages');
	
	foreach( $viewResult as $record) {
		$msg['message_id'] = isset( $record->nid) ? $record->nid : null;
		$format = $record->field_field_ocs_format[0]['rendered']['#markup'];
		$msg['name'] = $record->node_title;
		$msg['format'] = preg_replace( '/%\d+/', '%s', $format);
		$msg['ui_param'] = $record->field_field_ocs_value_str[0]['rendered']['#markup'];
		
		$jsonData['messages'][] = $msg;
	}

	$viewResult = views_get_view_result('ocs_message_group', 'panel_json', $nid);
	// dpm( $viewResult, 'messages');
	
	$msg = array();
	foreach( $viewResult as $record) {
		$msg[$record->nid]['message_id'] = isset( $record->nid) ? $record->nid : null;
		$msg[$record->nid]['name'] = $record->node_title;
		$msg[$record->nid]['ui_param'][] = $record->field_field_ocs_message_list[0]['rendered']['#markup'];
	}
		
	$jsonData['group'] = array_values( $msg);
		
    return $jsonData;   
}

function _json_message($nid=NULL) {
    $retArray = array();
    $jsonData  = _array_message($nid);
    $retArray = $jsonData;

    if($nid != NULL) {
        return json_encode($jsonData);
    } else {
        return json_encode($retArray);
    }
}
