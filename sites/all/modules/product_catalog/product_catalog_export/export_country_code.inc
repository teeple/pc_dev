<?php
function _json_country_code(){
	$stringMaxLength = 60;
	$jsonData = array();
	
	//fetch data
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
	
	return json_encode($jsonData);
}