<?php

function _array_deposit_scheme($exportItemNids=NULL){
    $jsonData_schemes = array();
    
    if(!empty($exportItemNids) && count($exportItemNids) > 1) {
    	$exportItemNids = join('+', $exportItemNids);
    }

    //fetch data    
    $viewResult = views_get_view_result('list_depositscheme', 'panel_pane_5', $exportItemNids);
    
    foreach($viewResult as $record) {

        $depositScheme['id'] = isset($record->nid) ? $record->nid: null;
        $depositScheme['title'] = isset($record->node_title) ? $record->node_title: null;
        if(isset($record->nid)){
            //scheme factors
            $depositSchemeFactorsList = views_get_view_result('list_depositschemefactors', 'panel_pane_5', $record->nid);
            
            $factorArray = array();
            foreach($depositSchemeFactorsList as $item){
            		$factorNode = node_load($item->nid);
              
                $factor = array();
                $factor['id'] = $factorNode->nid;
                $factor['title'] = $factorNode->title;
                
                // threshold unit type
                $factor['threshold_unit_type'] = _add_commoncode($item->field_field_counter_unit_type);
                
                //toc
                if(!empty($item->field_field_ref_type_of_call_mul)){
                    foreach($item->field_field_ref_type_of_call_mul as $toc){
												$tempArray = array($toc);
												dsm($tempArray, 'tempArray');
												$factor['type_of_call'][] = _add_commoncode($tempArray);
                    }   
                }else{
                    $factor['type_of_call'] = NULL;
                }
                
                //amount
                if(!empty($factorNode->field_deposit_amount_collection['und'])){
                    foreach($factorNode->field_deposit_amount_collection['und'] as $collectionItem){
                        $collectionInfo = field_collection_item_load($collectionItem['value']);
                        $factor['amount'][] = array(
                            'deposit_amount' => $collectionInfo->field_deposit_amount['und'][0]['value'],
                            'threshold_amount' => $collectionInfo->field_threshold_amount['und'][0]['value'],
                            'threshold_amount_max' => $collectionInfo->field_threshold_amount_max['und'][0]['value'],
                        );
                    }
                  }else{
                    $factor['amount'] = NULL;
                }
                
                //accumulated counter
                if(isset($factorNode->field_ref_thres_counter_acc['und'][0]['nid'])){
                    $accCounterNode = node_load($factorNode->field_ref_thres_counter_acc['und'][0]['nid']);
                    if(!empty($accCounterNode)){
	                    $factor['counter_accumulated'] = array(
	                        'counter_id' => $accCounterNode->field_counter_id['und'][0]['value'],
	                        'counter_name' => $accCounterNode->title
	                    );
	                  };
                }else{
                    $factor['counter_accumulated'] = NULL;
                }
                
                // monthly accumulating counter
                if(isset($factorNode->field_thismonth_accu_counter['und'][0]['nid'])){
                    $accCounterNode = node_load($factorNode->field_thismonth_accu_counter['und'][0]['nid']);
                    if(!empty($accCounterNode)){
	                    $factor['counter_accumulated_monthly'] = array(
	                        'counter_id' => $accCounterNode->field_counter_id['und'][0]['value'],
	                        'counter_name' => $accCounterNode->title
	                    );
	                  };
                }else{
                    $factor['counter_accumulated_monthly'] = NULL;
                }
                
                //limit counter
                if(isset($factorNode->field_ref_thres_counter_limit['und'][0]['nid'])){
                    $limitCounterNode = node_load($factorNode->field_ref_thres_counter_limit['und'][0]['nid']);
                    if(!empty($limitCounterNode)){
	                    $factor['counter_limit'] = array(
	                        'counter_id' => $limitCounterNode->field_counter_id['und'][0]['value'],
	                        'counter_name' => $limitCounterNode->title
	                    );
                    }
                }else{
                    $factor['counter_limit'] = NULL;
                }
                
                // ref threshold scheme
                if(isset($factorNode->field_ref_thresholdscheme['und'][0]['nid'])){
                    $thresholdscheme = node_load($factorNode->field_ref_thresholdscheme['und'][0]['nid']);
                    if(!empty($thresholdscheme)){
                      $factor['thresholdscheme_id'] = $factorNode->field_ref_thresholdscheme['und'][0]['nid'];
                    }
                }else{
                    $factor['thresholdscheme_id'] = NULL;
                }
                
                $factorArray[] = $factor;
            }
            $depositScheme['factors'] = $factorArray;
            
            //adjustment
            $adjustmentList = views_get_view_result('list_depositschemeadjustment', 'panel_pane_4', $record->nid);
            
            $adjustmentArray = array();
            
            foreach($adjustmentList as $item){
                $adjustment = array();
                // $adjustment['id'] = $item->nid;
                if(isset($item->field_field_ref_customer_level[0]['raw']['taxonomy_term'])){
                    $adjustment['customer_level'] = _get_common_code($item->field_field_ref_customer_level[0]['raw']['taxonomy_term']);
                }else{
                    $adjustment['customer_level'] = NULL;
                }              
                if(isset($item->field_field_threshold_adjustment_amoun[0]['raw']['value'])){
                    $adjustment['amount'] = $item->field_field_threshold_adjustment_amoun[0]['raw']['value'];
                }else{
                    $adjustment['amount'] = NULL;
                }
                $adjustmentArray[] = $adjustment;                
            }
            $depositScheme['adjustment'] = $adjustmentArray;
        }
        $jsonData_schemes[] = $depositScheme;
        $depositSchemeIds[] = $depositScheme['id'];
    }
    
    if($exportItemNids!=NULL) {
    	$jsonData_common['resources'] = $depositSchemeIds;
  	} else {
      $jsonData_common['resources'] = array();
  	}
  	
  	$jsonData['ifvalues'] = $jsonData_common;
  	$jsonData['deposit_scheme'] = $jsonData_schemes;
    
    return $jsonData;   
}

function _json_deposit_scheme($exportItemNids=NULL) {
  $retArray = array();
  $jsonData  = _array_deposit_scheme($exportItemNids);
  
  $retArray = $jsonData;
  
	$arr = array();
    if(!empty($exportItemNids) && count($exportItemNids) > 1) {
    	$exportItemNids = join('+', $exportItemNids);
    }
	$arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "rating_deposit_scheme", $exportItemNids);
	foreach($arr as $a)
	{
		foreach($a as $t => $v)
		{
			$retArray['rating_rules'][$t] = $v;
		}
	}

	return json_encode($retArray);
}
