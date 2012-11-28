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
		$format = $record->field_field_ocs_format[0]['rendered']['#markup'];
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

	$jsonData['group'] = array_values($msg);

	return $jsonData;
}

function _json_message($nid = NULL)
{
	$retArray = array();
	$jsonData = _array_message($nid);
	$retArray = $jsonData;

	if ($nid != NULL) {
		return json_encode($jsonData);
	}
	else {
		return json_encode($retArray);
	}
}
