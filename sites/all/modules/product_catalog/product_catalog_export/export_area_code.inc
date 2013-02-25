<?php
function _json_area_code(){
	$stringMaxLength = 60;
	$jsonData = array();

	//fetch data
	$areaCodeView = views_get_view('list_area_code_lifecycle');
	$areaCodeView->execute();
	
	$areaCodes = $areaCodeView->result;
	foreach($areaCodes as $areaCodeItem){
		$areaCode = array(
			'area_code' => $areaCodeItem->field_field_area_code[0]['raw']['safe_value'],
			'area_name' => $areaCodeItem->node_title,
		);
		
		//add areacode to array
		$jsonData['AreaCode'][] = $areaCode;
	}
	
	return json_encode($jsonData);
}