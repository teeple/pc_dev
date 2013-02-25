<?php
function _json_numberingplan_domestic($nid=NULL){
	$stringMaxLength = 60;
	$jsonData = array();

	//fetch data		
	$planView = views_get_view('list_numberingplan_domestic_lifecycle');
	$planView->set_arguments(array('0'=>$nid));
	$planView->execute();
	
	$plans = $planView->result;
	
	foreach($plans as $planItem){
		$plan = array();
		$plan['numberingplan_domestic_name'] = $planItem->node_title;
		
		//NPA
		$plan['NPA'] = array();
		_create_export_meta_data_by_content_type(null,$plan['NPA'],'domestic_npa');

		$npaView = views_get_view('list_numberingplan_domestic_npa');
		$npaView->set_arguments(array('0'=>$planItem->nid));
		$npaView->execute();
		$npas = $npaView->result;
		foreach($npas as $npaItem){
			$npa = array(
				'service_type' => $npaItem->field_field_service_of_usage[0]['raw']['taxonomy_term']->name,
				'carrier_domestic_name' =>  $npaItem->field_field_carrier_domestic[0]['raw']['taxonomy_term']->name,
				'npa_prefix' => $npaItem->field_field_prefix[0]['raw']['safe_value'],
				'npa_toc' => $npaItem->field_field_new_type_of_call[0]['raw']['safe_value']
			);
			
			$plan['NPA']['data'][] = $npa;
		}
		
		//Area Code
		$plan['Area'] = array();
		_create_export_meta_data_by_content_type(null,$plan['Area'],'domestic_area');
		
		$areaView = views_get_view('list_numberingplan_domestic_area');
		$areaView->set_arguments(array('0'=>$planItem->nid));
		$areaView->execute();
		$areas = $areaView->result;
		foreach($areas as $areaItem){
			$area = array(				
				'area_toc' => $areaItem->field_field_type_of_call[0]['raw']['safe_value'],
				'area_prefix' => $areaItem->field_field_prefix[0]['raw']['safe_value'],	
				'area_code' => $areaItem->field_field_area_code[0]['raw']['safe_value']				
			);	
										
			$plan['Area']['data'][] = $area;
		}
		
		//Rating group
		$plan['RatingGroup'] = array();
		_create_export_meta_data_by_content_type(null,$plan['RatingGroup'],'domestic_ratinggroup');

		$ratingGroupView = views_get_view('list_numberingplan_domestic_ratinggroup');
		$ratingGroupView->set_arguments(array('0'=>$planItem->nid));
		$ratingGroupView->execute();
		$ratingGroups = $ratingGroupView->result;
		foreach($ratingGroups as $ratingGroupItem){			
			$ratingGroup = array(
				'carrier_domestic_name' => $ratingGroupItem->field_field_carrier_domestic[0]['raw']['taxonomy_term']->name,
				'same_zone' => $ratingGroupItem->field_field_is_samezone[0]['raw']['value']?'true':'false',
				'from_area_code' => $ratingGroupItem->field_field_area_code[0]['raw']['safe_value'],
				'to_area_code' => $ratingGroupItem->field_field_area_code_1[0]['raw']['safe_value'],
				'ratinggroup' => $ratingGroupItem->field_field_rating_group[0]['raw']['value']
			);
			
			$plan['RatingGroup']['data'][] = $ratingGroup;
		}
		
		//add plan to array
		$jsonData['NumberingplanDomestic'][] = $plan;
	}
	
	return json_encode($jsonData);
}