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

function _array_export_counter($exportItemNids=NULL){
	$jsonData = array();
	$jsonData_counters = array();
	$jsonData_common = array();
	
	//fetch data
	$view = views_get_view('list_counter');
	if(!empty($exportItemNids) && count($exportItemNids) > 1) {
		$exportItemNids = join('+', $exportItemNids);
	} 
	$viewResult = views_get_view_result('list_counter', 'panel_pane_5', $exportItemNids);
	$counterIds = array();
	
  foreach($viewResult as $record) {
    $jsonCounter = array();
    $jsonCounter['counter_id'] = $record->field_field_counter_id[0]['raw']['value'];
    $jsonCounter['counter_name'] = isset($record->node_title) ? $record->node_title: null;
		$jsonCounter['service_domain'] = _add_commoncode($record->field_field_service_domain);
		$jsonCounter['counter_group'] = _add_commoncode($record->field_field_counter_group);
		$jsonCounter['bill_type'] = _add_commoncode($record->field_field_billing_type_counter);
    $jsonCounter['counter_unit_type'] = _add_commoncode($record->field_field_counter_unit_type);
    $jsonCounter['counter_type'] = _add_commoncode($record->field_field_counter_type);
    $counterTypeTerm = $record->field_field_counter_type[0]['raw']['taxonomy_term'];
    
    if($counterTypeTerm->name === 'Rollover'){
    		dsm($record, 'record');
    		$jsonCounter['rollover_month'] = $record->field_field_rollover_months[0]['raw']['value'];
    }
    $jsonCounter['description'] = !empty($record->field_field_description) ? $record->field_field_description[0]['rendered']['#markup']: null;
    $jsonCounter['scale'] = !empty($record->field_field_scale) ? $record->field_field_scale[0]['rendered']['#title']: null;

    $jsonData_counters[] = $jsonCounter;
		
		$counterIds[] = $record->field_field_counter_id[0]['raw']['value'];
  }

  if($exportItemNids!=NULL) {
  	$jsonData_common['resources'] = $counterIds;
	} else {
    $jsonData_common['resources'] = array();
	}
	
	$jsonData['ifvalues'] = $jsonData_common;
	$jsonData['counters'] = $jsonData_counters;

	$arr = array();
	$arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "rating_counter_info", $exportItemNids);
	foreach($arr as $a)
	{
		foreach($a as $t => $v)
		{
			$jsonData['rating_rules'][$t] = $v;
		}   
	}
	
	return $jsonData;
}

function _json_counter($exportItemNids=NULL) {
	$retArray = array();
	
	$jsonData  = _array_export_counter($exportItemNids);

	return json_encode($jsonData);
}

