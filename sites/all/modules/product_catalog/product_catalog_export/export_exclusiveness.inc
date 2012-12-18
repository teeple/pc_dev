<?php

function _json_exclusiveness($nid=NULL){
	$jsonData = array();

	//fetch data		
	$$view_exclusiveness = views_get_view('list_exclusiveness');
	$view_exclusiveness->execute();
	
	$productExclusiveness = $view_exclusiveness->result;
	
	foreach($productExclusiveness as $record) {
		
		dsm($record, 'record');
		
		$jsonData['Exclusiveness'][] = $plan;
	}
	
	return json_encode($jsonData);
}
