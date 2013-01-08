<?php

function _array_deposit_scheme($nid=NULL){
    $jsonData = array();

    //fetch data    
    $viewResult = views_get_view_result('list_depositscheme', 'panel_pane_5', $nid);
    
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
                
                //toc
                if(!empty($factorNode->field_ref_type_of_call_multiple['und'])){
                    foreach($factorNode->field_ref_type_of_call_multiple['und'] as $collectionItem){
                        $collectionInfo = field_collection_item_load($collectionItem['value']);
                        $factor['type_of_call'][] = _get_common_code($collectionInfo->field_ref_type_of_call['und'][0]['taxonomy_term']);
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
                            'threshold_amount' => $collectionInfo->field_threshold_amount['und'][0]['value']
                        );
                    }   
                }else{
                    $factor['amount'] = NULL;
                }
                
                //accumulated counter
                if(isset($factorNode->field_ref_thres_counter_acc['und'][0]['nid'])){
                    $accCounterNode = node_load($factorNode->field_ref_thres_counter_acc['und'][0]['nid']);
                    $factor['counter_accumulated'] = array(
                        'counter_id' => $accCounterNode->field_counter_id['und'][0]['value'],
                        'counter_name' => $accCounterNode->title
                    );
                }else{
                    $factor['counter_accumulated'] = NULL;
                }
                
                //limit counter
                if(isset($factorNode->field_ref_thres_counter_limit['und'][0]['nid'])){
                    $limitCounterNode = node_load($factorNode->field_ref_thres_counter_limit['und'][0]['nid']);
                    $factor['counter_limit'] = array(
                        'counter_id' => $limitCounterNode->field_counter_id['und'][0]['value'],
                        'counter_name' => $limitCounterNode->title
                    );
                }else{
                    $factor['counter_limit'] = NULL;
                }
                
                $factorArray[] = $factor;
            }
            $depositScheme['factors'] = $factorArray;
            
            
             //adjustment
            $adjustmentList = views_get_view_result('list_depositschemeadjustment', 'panel_pane_4', $record->nid);
            
            $adjustmentArray = array();
            
            foreach($adjustmentList as $item){
                $adjustment = array();
                $adjustment['id'] = $item->nid;
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
        $jsonData[] = $depositScheme;
    }
    
    return $jsonData;   
}

function _json_deposit_scheme($nid=NULL) {
    $retArray = array();
    $jsonData  = _array_deposit_scheme($nid);
	$retArray['deposit_scheme'] = $jsonData;

	$arr = array();
	$arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "rating_deposit_scheme");
	foreach($arr as $a)
	{
		foreach($a as $t => $v)
		{
			$retArray['rating_rules'][$t] = $v;
		}
	}

    if($nid != NULL) {
        return json_encode($jsonData);
    } else {
        return json_encode($retArray);
    }
}
