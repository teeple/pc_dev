<?php

function _array_tvchannel($nid=NULL){
    $output = array();

    //fetch data    
    $viewResult = views_get_view_result('list_tvchannel', 'panel_pane_5', $nid);
    
    foreach($viewResult as $record) {
        $channelInfo = array();
        $tvChannelNode = node_load($record->nid);
        
        $channelInfo['code'] = $tvChannelNode->field_channel_code['und'][0]['safe_value'];
        $channelInfo['name'] = $tvChannelNode->title;
        $channelInfo['number'] = $tvChannelNode->field_channel_number['und'][0]['value'];        
        $qualityTerm = taxonomy_term_load($tvChannelNode->field_ref_video_quality['und'][0]['tid']);
        $channelInfo['quality'] = _get_common_code($qualityTerm);
        $gradeTerm = taxonomy_term_load($tvChannelNode->field_ref_video_grade['und'][0]['tid']);
        $channelInfo['grade'] = _get_common_code($gradeTerm);
        $channelInfo['monthly_fee'] = isset($tvChannelNode->field_monthly_fee['und'][0]['value'])?$tvChannelNode->field_monthly_fee['und'][0]['value']:0;
        $statusTerm = taxonomy_term_load($tvChannelNode->field_ref_channel_status['und'][0]['tid']);
        $channelInfo['status'] = _get_common_code($statusTerm);
       
        $output[] = $channelInfo;
    }
    
    return $output;   
}

function _json_tvchannel($nid=NULL) {
    $retArray = array();
    $jsonData  = _array_tvchannel($nid);
    $retArray['tv_channel'] = $jsonData;

    if($nid != NULL) {
        return json_encode($jsonData);
    } else {
        return json_encode($retArray);
    }
}
