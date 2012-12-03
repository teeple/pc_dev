<?php

function _add_commoncode($field) {
	$retData = array();

	if(!empty($field)) {
		$vocabulary = taxonomy_vocabulary_load($field[0]['rendered']['#options']['entity']->vid);
		if(!empty($vocabulary)) {
			$retData['codeGroup'] = !empty($vocabulary) ? $vocabulary->name : null;
			$retData['code'] = !empty($field[0]['rendered']['#options']['entity']->field_common_code) ? $field[0]['rendered']['#options']['entity']->field_common_code['und'][0]['value']: null;
			$retData['meaning'] = !empty($field[0]['rendered']['#title']) ? $field[0]['rendered']['#title'] : null;
			return $retData;
		}
	}

	return $retData = null;
}

function _array_export_counter($nid=NULL){
	$jsonData = array();
	$jsonData_counters = array();
	$jsonData_common = array();
	
	//fetch data
	$view = views_get_view('list_counter');
	//$view->set_display('panel_pane_5');

	$viewResult = views_get_view_result('list_counter', 'panel_pane_5', $nid);
	
	$counterNids = array();
	
    foreach($viewResult as $record) {

        // $jsonCounter['ID'] = !empty($record->field_field_code[0]['raw']['value']) ? $record->field_field_code[0]['raw']['value'] : null;
        $jsonCounter['counter_id'] = $record->nid;
        $jsonCounter['counter_name'] = isset($record->node_title) ? $record->node_title: null;

		$jsonCounter['service_domain'] = _add_commoncode($record->field_field_service_domain);
		$jsonCounter['counter_group'] = _add_commoncode($record->field_field_counter_group);
		$jsonCounter['bill_type'] = _add_commoncode($record->field_field_billing_type_counter);
        $jsonCounter['counter_unit_type'] = _add_commoncode($record->field_field_counter_unit_type);
        $jsonCounter['counter_type'] = _add_commoncode($record->field_field_counter_type);
        // $jsonCounter['main_or_accumulated'] = _add_commoncode($record->field_field_main_or_accumulated);

        $jsonCounter['description'] = !empty($record->field_field_description) ? $record->field_field_description[0]['rendered']['#markup']: null;
        $jsonCounter['scale'] = !empty($record->field_field_scale) ? $record->field_field_scale[0]['rendered']['#title']: null;

        $jsonData_counters['counters'][] = $jsonCounter;
		
		$counterNids[] = $record->nid;
    }

    if($nid!=NULL) {
    	$jsonData_common['ifvalues']['resources'] = array(array_values($counterNids));
	} else {
    	$jsonData_common['ifvalues']['resources'] = array();
	}
	
	/*
	$options = array();
	$options['method'] = 'POST';
	$options['headers']['content-type']= 'application/json';
	$options['data'] = json_encode($jsonData);
	$result = drupal_http_request('http://192.168.1.105:99/crm/counter/deploy', $options);
	*/
	$jsonData[] = array_merge($jsonData_common, $jsonData_counters);
	
	return $jsonData;

}

function _json_counter($nid=NULL) {

	$retArray = array();
	$jsonData  = _array_export_counter($nid);
	// $retArray['counters'] = $jsonData;
	
	if($nid != NULL) {
		return json_encode($jsonData);
	} else {
		return json_encode($jsonData);
	}
	return json_encode($jsonData);
}

