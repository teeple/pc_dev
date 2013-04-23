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
            
            		$factor = array();
                $factor['id'] = $item->nid;
                
                dsm($item->field_field_limittothreshold, 'limit to threshold');
                $factor['limit_to_threshold'] = isset($item->field_field_limittothreshold[0]['raw']['value'])? $item->field_field_limittothreshold[0]['raw']['value'] : NULL;
                
                /*
								"actions":[
												{
												     "action":"send_sms_notification",
												     "parameters":{
												          "orig":"9761414",
												          "dest":"CALLING",
												          "message":"61799"
												     }
												},
								],
                */
                
                $actionSetList = array();
                foreach($item->field_field_threshold_action_set as $item) {
                	$actionSet = array();
                	$fieldCollection = current($item['rendered']['entity']['field_collection_item']);
                	$actionSet['action'] = $fieldCollection['field_action_type']['#object']->field_action_type['und'][0]['taxonomy_term']->name;
                	
                	$message_orig = isset($fieldCollection['field_action_type']['#object']->field_message_orig['und'][0]['value'])? $fieldCollection['field_action_type']['#object']->field_message_orig['und'][0]['value']: NULL;
                	$message_dest = isset($fieldCollection['field_action_type']['#object']->field_message_dest['und'][0]['taxonomy_term']->name)? $fieldCollection['field_action_type']['#object']->field_message_dest['und'][0]['taxonomy_term']->name: NULL;
                	$message_id = isset($fieldCollection['field_action_type']['#object']->field_ref_messages['und'][0]['nid'])? $fieldCollection['field_action_type']['#object']->field_ref_messages['und'][0]['nid']: NULL;
                	
                	if(isset($message_id)) {
                		$actionSet['parameters'] = array('orig' => $message_orig,
                																		'dest' => $message_dest,
                																		'message' => $message_id);
                	} else {
                		$actionSet['parameters'] = NULL;
                	}
                	
                	
                	$actionSetList[] = $actionSet;
                }
                $factor['actions'] = $actionSetList;
            }
            $thresholdScheme['factors'] = $factor;            
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

	$arr = array();
    if(!empty($exportItemNids) && count($exportItemNids) > 1) {
    	$exportItemNids = join('+', $exportItemNids);
    }
	$arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "rating_deposit_threshold", $exportItemNids);
	foreach($arr as $a)
	{
		foreach($a as $t => $v)
		{
			$jsonData['rating_rules'][$t] = $v;
		}
	}

  if($exportItemNids != NULL) {
  	return json_encode($jsonData);
  } else {
  	return json_encode($retArray);
  }
}
