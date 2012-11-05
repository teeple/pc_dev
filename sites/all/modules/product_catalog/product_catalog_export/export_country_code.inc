<?php
function _json_country_code(){
	$stringMaxLength = 60;
	$jsonData = array();
	
	//fetch data
	/*
	$jsonData['CountryCode']['meta'] = array(
		array('name' => 'country_code','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
		array('name' => 'country_name','condition' => false, 'type' => 'string','maxlength' => $stringMaxLength),
	);
	*/
	$countryCodeView = views_get_view('list_country_code_lifecycle');
	$countryCodeView->execute();
	
	$countryCodes = $countryCodeView->result;
	
	foreach($countryCodes as $countryCodeItem){
		$countryCode = array(
			'country_code' => $countryCodeItem->field_field_country_code[0]['raw']['safe_value'],
			'country_name' => $countryCodeItem->node_title,
		);
		
		//add countrycode to array
		$jsonData['CountryCode'][] = $countryCode;
	}
	
	//dsm($jsonData,'before json');
	//dsm(json_encode($jsonData),'after json');
	
	return json_encode($jsonData);
}