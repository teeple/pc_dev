<?php
function _json_area_code(){
	$stringMaxLength = 60;
	$jsonData = array();

	//fetch data
	/*
	$jsonData['AreaCode']['meta'] = array(
		array('name' => 'area_code','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
		array('name' => 'area_name','condition' => false, 'type' => 'string','maxlength' => $stringMaxLength),
	);
	*/
	$areaCodeView = views_get_view('list_area_code_lifecycle');
	$areaCodeView->execute();
	
	$areaCodes = $areaCodeView->result;
	//dsm($areaCodes);
	foreach($areaCodes as $areaCodeItem){
		$areaCode = array(
			'area_code' => $areaCodeItem->field_field_area_code[0]['raw']['safe_value'],
			'area_name' => $areaCodeItem->node_title,
		);
		
		//add areacode to array
		$jsonData['AreaCode'][] = $areaCode;
	}
	
	//dsm($jsonData,'before json');
	//dsm(json_encode($jsonData),'after json');
	
	return json_encode($jsonData);
}