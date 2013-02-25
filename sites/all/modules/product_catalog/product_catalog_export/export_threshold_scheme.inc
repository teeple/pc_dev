<?php

function _array_threshold_scheme($exportItemNids=NULL){
    $jsonData = array();
    $jsonData_schemes = array();
    $schemeIds = array();
    
    if(!empty($exportItemNids) && count($exportItemNids) > 1) {
    	$exportItemNids = join('+', $exportItemNids);
    }
    
    //fetch data    
    $viewResult = views_get_view_result('list_thresholdscheme', 'panel_pane_4', $exportItemNids);

    foreach($viewResult as $record) {

        $thresholdScheme['id'] = isset($record->nid) ? $record->nid: null;
        $thresholdScheme['title'] = isset($record->node_title) ? $record->node_title: null;
        if(isset($record->nid)){
            //scheme factors
            $thresholdSchemeFactorsList = views_get_view_result('list_thresholdschemefactors', 'panel_pane_4', $record->nid);
            
            $factorArray = array();
            foreach($thresholdSchemeFactorsList as $item){
                $factorNode = node_load($item->nid);
                
                $factor = array();
                $factor['id'] = $factorNode->nid;
                
                //limit
                if(!empty($factorNode->field_limittothreshold['und'])){
                    foreach($factorNode->field_limittothreshold['und'] as $item){
                        $factor['limit_to_threshold'] = $item['value'];
                    }   
                }else{
                    $factor['limit_to_threshold'] = NULL;
                }
                       
                //action
                if(!empty($factorNode->field_field_ref_thresholdaction['und'])){
                    foreach($factorNode->field_field_ref_thresholdaction['und'] as $item){
                        $actionTerm = taxonomy_term_load($item['tid']);
                        $actionInfo = _get_common_code($actionTerm);
                        if($actionInfo['meaning'] == 'Notification' && isset($factorNode->field_message_select['und'])){
                            foreach($factorNode->field_message_select['und'] as $messageItem){
                                $actionInfo['message_id'][] = $messageItem['nid'];
                            } 
                        }
                        //$factor['threshold_action'][] = _get_common_code($actionTerm);
                        $factor['threshold_action'][] = $actionInfo;
                    } 
                }else{
                    $factor['threshold_action'] = NULL;
                }      
                $factorArray[] = $factor;
            }
            $thresholdScheme['factors'] = $factorArray;            
        }
        $jsonData_schemes[] = $thresholdScheme;
        $schemeIds[] = $thresholdScheme['id'];
    }
    if($exportItemNids!=NULL) {
    	$jsonData_common['resources'] = $schemeIds;
    } else {
      $jsonData_common['resources'] = array();
    }
    
    $jsonData['ifvalues'] = $jsonData_common;
    $jsonData['threshold_scheme'] = $jsonData_schemes;
    
    return $jsonData;   
}

function _json_threshold_scheme($exportItemNids=NULL) {
  $retArray = array();
  $jsonData  = _array_threshold_scheme($exportItemNids);

  if($exportItemNids != NULL) {
  	return json_encode($jsonData);
  } else {
  	return json_encode($retArray);
  }
}
