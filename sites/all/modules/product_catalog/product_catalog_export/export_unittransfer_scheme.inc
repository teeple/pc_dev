<?php

function _array_unittransfer_scheme($exportItemNids=NULL){
	$jsonData = array();
	$jsonData_schemes = array();
	$jsonData_common = array();
	
	//fetch data	
	if(!empty($exportItemNids) && count($exportItemNids) > 1) {
		$exportItemNids = join('+', $exportItemNids);
	}
	
	$viewResult = views_get_view_result('list_unittransfer', 'panel_pane_5', $exportItemNids);
	
	foreach($viewResult as $record) {
		$jsonRecord['id'] = isset($record->nid)? $record->nid: null;
		$jsonRecord['title'] = isset($record->node_title) ? $record->node_title: null;
		$jsonRecord['price_amount'] = isset($record->field_field_price_amount_float) ? $record->field_field_price_amount_float[0]['raw']['value']: null;
		$jsonRecord['maximum_amount'] = !empty($record->field_field_maximum_amount) ? $record->field_field_maximum_amount[0]['raw']['value']: null;
    $jsonRecord['maximum_counter'] = !empty($record->field_field_maximum_counter_) ? $record->field_field_maximum_counter_[0]['raw']['value']: null;
    $jsonRecord['maximum_amount'] = !empty($record->field_field_maximum_total_amount) ? $record->field_field_maximum_total_amount[0]['raw']['value']: null;
    $jsonRecord['minimum_amount'] = !empty($record->field_field_minimum_amount) ? $record->field_field_minimum_amount[0]['raw']['value']: null;
    
    $validStart = isset($record->field_field_valid_date_ymd_w_enddate[0]['raw']['value'])? 
     				$record->field_field_valid_date_ymd_w_enddate[0]['raw']['value']: '0001-01-01 00:00:00';
		$validStart = isset($record->field_field_valid_date_ymd_w_enddate[0]['raw']['value2'])? 
							$record->field_field_valid_date_ymd_w_enddate[0]['raw']['value2']: '9999-12-31 23:59:59';

    if(!empty($record->field_field_valid_date_ymd_w_enddate)) {
			$tempArr = explode(' ', $record->field_field_valid_date_ymd_w_enddate[0]['raw']['value']);
			$validEnd = $tempArr[0].' 23:59:59';
		} else {
		  $validEnd = '9999-12-31 23:59:59';
		}
		$validFor = $validStart . ' ~ '. $validEnd;
		$jsonRecord['valid_for'] = $validFor;

		$factorNids = array();
		foreach($record->field_field_ref_unittransferfactors as $unittransferfactor) {
			$factorNids[] = $unittransferfactor	['raw']['nid'];
		}
		
		if(!empty($factorNids)) {
			$subViewResult = views_get_view_result('list_unittransfer_factors', 'panel_pane_1', join('+',$factorNids));
			
			foreach($subViewResult as $factor) {
				$jsonFactor['counter_id'] = !empty($factor->field_field_counter_id)? $factor->field_field_counter_id[0]['raw']['value']: null;
				$jsonFactor['counter_title'] = !empty($factor->node_field_data_field_ref_counter_title)? $factor->node_field_data_field_ref_counter_title: null;
				$jsonFactor['rate'] = $factor->field_field_rate[0]['raw']['value'];
				$jsonRecord['factors'][] = $jsonFactor;
			}
		}
		
		$jsonRecord_schemes[] = $jsonRecord;
		$schemeIds[] = $jsonRecord['id'];
	}
    
  if(!empty($exportItemNids)) {
  	$jsonData_common['resources'] = array_values($schemeIds);
  } else {
    $jsonData_common['resources'] = array();
  }
  
  $jsonData['ifvalues'] = $jsonData_common;
  $jsonData['unittransfer_scheme'] = $jsonRecord_schemes;
  
	return $jsonData;
}

function _json_unittransfer_scheme($exportItemNids=NULL) {
	$jsonData  = _array_unittransfer_scheme($exportItemNids);
	
  return json_encode($jsonData);
}
