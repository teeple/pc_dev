<?php
function _json_numberingplan_idd($nid=NULL){
	$stringMaxLength = 60;
	$jsonData = array();

	//fetch data	
	$planView = views_get_view('list_numberingplan_idd_lifecycle');
	$planView->set_arguments(array('0'=>$nid));
	$planView->execute();
	
	$plans = $planView->result;
	
	foreach($plans as $planItem){
		$plan = array();
		$plan['numberingplan_idd_name'] = $planItem->node_title;
		//Exit Code
		$plan['ExitCode'] = array();
		_create_export_meta_data_by_content_type(null,$plan['ExitCode'],'idd_exit');
		
		$exitCodeView = views_get_view('list_numberingplan_idd_exit');
		$exitCodeView->set_arguments(array('0'=>$planItem->nid));
		$exitCodeView->execute();
		$exitCodes = $exitCodeView->result;
		foreach($exitCodes as $exitCodeItem){
			$exitCode = array(
				'service_type' => $exitCodeItem->field_field_service_of_usage[0]['raw']['taxonomy_term']->name,
				'carrier_idd_name' => $exitCodeItem->field_field_carrier_idd[0]['raw']['taxonomy_term']->name,
				'exit_prefix' => $exitCodeItem->field_field_prefix[0]['raw']['safe_value'],
				'exit_toc' => $exitCodeItem->field_field_new_type_of_call[0]['raw']['safe_value']				
			);			
			$plan['ExitCode']['data'][] = $exitCode;
		}
		
		//Country Code
		$plan['Country'] = array();
		_create_export_meta_data_by_content_type(null,$plan['Country'],'idd_country');
		
		$countryView = views_get_view('list_numberingplan_idd_country');
		$countryView->set_arguments(array('0'=>$planItem->nid));
		$countryView->execute();
		$countries = $countryView->result;
		foreach($countries as $countryItem){
			$country = array(
				'country_toc' => $countryItem->field_field_type_of_call[0]['raw']['safe_value'],
				'country_prefix' => $countryItem->field_field_prefix[0]['raw']['safe_value'],
				'country_code' => $countryItem->field_field_country_code[0]['raw']['safe_value'], 
				'country_new_toc' => $countryItem->field_field_new_type_of_call[0]['raw']['safe_value']
				
			);			
			$plan['Country']['data'][] = $country;
		}
		
		//Rating group
		$plan['RatingGroup'] = array();
		_create_export_meta_data_by_content_type(null,$plan['RatingGroup'],'idd_ratinggroup');
		
		$ratingGroupView = views_get_view('list_numberingplan_idd_ratinggroup');
		$ratingGroupView->set_arguments(array('0'=>$planItem->nid));
		$ratingGroupView->execute();
		$ratingGroups = $ratingGroupView->result;
		foreach($ratingGroups as $ratingGroupItem){
			$ratingGroup = array(
				'ratinggroup_toc' => $ratingGroupItem->field_field_type_of_call[0]['raw']['safe_value'],
				'ratinggroup_prefix' => $ratingGroupItem->field_field_prefix[0]['raw']['safe_value'],
				'area_code' => $ratingGroupItem->field_field_area_code[0]['raw']['safe_value'],
				'RatingGroup' => $ratingGroupItem->field_field_rating_group[0]['raw']['value']
				
			);
			
			$plan['RatingGroup']['data'][] = $ratingGroup;
		}
				
		//add plan to array
		$jsonData['NumberingplanIDD'][] = $plan;
	}
	
//	dsm($jsonData,'before json');
	//dsm(json_encode($jsonData),'after json');
	
	return json_encode($jsonData);
}