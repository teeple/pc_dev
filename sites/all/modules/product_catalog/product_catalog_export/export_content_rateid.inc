<?php
function _json_content_rateid($nid=NULL){
	$jsonData = array();

	//fetch data	
	$viewResult = views_get_view_result('list_rateid', 'panel_pane_2');

    foreach($viewResult as $record) {

		$jsonCounter['RateId'] = !empty($record->field_field_rateid) ? $record->field_field_rateid[0]['raw']['value'] : null;
        $jsonCounter['RateName'] = isset($record->node_title) ? $record->node_title: null;
        
        $jsonCounter['Price'] = !empty($record->field_field_price) ? $record->field_field_price[0]['raw']['value'] : null;

        $jsonData[] = $jsonCounter;
    }

	return json_encode($jsonData);
}
