<?php

function _array_tvchannel($exportItemNids=NULL){
    $output = array();
    $channelNames = array();
    $jsonData = array();
    $jsonData_common = array();
    
    if(!empty($exportItemNids) && count($exportItemNids) > 1) {
    	$exportItemNids = join('+', $exportItemNids);
    }
    
    //fetch data
    $viewResult = views_get_view_result('list_tvchannel', 'panel_pane_5', $exportItemNids);
    
    foreach($viewResult as $record) {
        $channelInfo = array();
        $tvChannelNode = node_load($record->nid);
        
//        $channelInfo['code'] = $tvChannelNode->field_channel_code['und'][0]['safe_value'];
        $channelInfo['channel_name'] = $tvChannelNode->title;
        $channelInfo['channel_number'] = $tvChannelNode->field_channel_number['und'][0]['value'];        
        $gradeTerm = taxonomy_term_load($tvChannelNode->field_ref_video_grade['und'][0]['tid']);
        $channelInfo['grade'] = _get_common_code($gradeTerm);
				$channelInfo['channel_code'] = $tvChannelNode->field_channel_code['und'][0]['value'];
        $qualityTerm = taxonomy_term_load($tvChannelNode->field_ref_video_quality['und'][0]['tid']);
        $channelInfo['quality'] = _get_common_code($qualityTerm);
        $channelInfo['monthly_fee'] = isset($tvChannelNode->field_monthly_fee['und'][0]['value'])?$tvChannelNode->field_monthly_fee['und'][0]['value']:0;
//        $statusTerm = taxonomy_term_load($tvChannelNode->field_ref_channel_status['und'][0]['tid']);
//        $channelInfo['status'] = _get_common_code($statusTerm);
       
        $output[] = $channelInfo;
//        $channelCodes[] = $channelInfo['code'];
        $channelNames[] = $channelInfo['channel_name'];
    }
    
    if(!empty($exportItemNids)) {
    	$jsonData_common['resources'] = $channelNames;
    } else {
      $jsonData_common['resources'] = array();
    }
    
    $jsonData['ifvalues'] = $jsonData_common;
    $jsonData['tv_channel'] = $output;
    
    return $jsonData;   
}

function _json_tvchannel($exportItemNids=NULL) {
    $retArray = array();
    $jsonData  = _array_tvchannel($exportItemNids);
    
    return json_encode($jsonData);
    /*
    $retArray['ifvalues']['resources'] = array();
    $retArray['tv_channel'] = $jsonData;
    
    if($nid != NULL) {
        return json_encode($jsonData);
    } else {
        return json_encode($retArray);
    }
    */
}
