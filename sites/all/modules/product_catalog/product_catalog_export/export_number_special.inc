<?php
function _json_number_special(){
	$stringMaxLength = 60;
	$jsonData = array();

	//fetch data
	$jsonData['NumberSpecial'] = array();
	_create_export_meta_data_by_content_type(null,$jsonData['NumberSpecial'],'numberspecial');
	
	$numberSpecialView = views_get_view('list_number_special');
	$numberSpecialView->execute();
	
	$numberSpecials = $numberSpecialView->result;
	
	foreach($numberSpecials as $numberSpecialItem){
		//number special
		//$numberSpecial = get_children_for_export($numberSpecialItem->nid);
		$numberSpecial = array(
			'type' => 'numberspecial',
			'number_special_name' => $numberSpecialItem->node_title
		);
		
		//number special factor
		$numberSpecialFactorsView = views_get_view('list_number_special_for_tree_detail');
		$numberSpecialFactorsView->set_display('panel_pane_1');
		$numberSpecialFactorsView->set_arguments(array(0=>$numberSpecialItem->nid));
		$numberSpecialFactorsView->execute();
		$numberSpecialFactors = $numberSpecialFactorsView->result;
		
		foreach($numberSpecialFactors as $numberSpecialFactorItem){
			$numberSpecial['children']['data'][] = array(
				'type' => 'numberspecialfactor',
				'ns_factor_prefix' => $numberSpecialFactorItem->field_field_prefix[0]['raw']['safe_value'],
				'charge_ratinggroup' => $numberSpecialFactorItem->field_field_rating_group[0]['raw']['value'],
			);
		}
		
     	//number special rate
		$numberSpecialRatesView = views_get_view('list_number_special_for_tree_detail');
		$numberSpecialRatesView->set_display('panel_pane_2');
		$numberSpecialRatesView->set_arguments(array(0=>$numberSpecialItem->nid));
		$numberSpecialRatesView->execute();
		$numberSpecialRates = $numberSpecialRatesView->result;
		
		foreach($numberSpecialRates as $numberSpecialRateItem){
			$ratinggroup = array();
			foreach($numberSpecialRateItem->field_field_rating_group as $ratinggroupItem){
				$ratinggroup[] = $ratinggroupItem['raw']['value'];
			}
			foreach($numberSpecialRateItem->field_field_charge_collection[0]['rendered']['#rows'] as $chargeCollectionItem){
				//dsm($chargeCollectionItem);
				$numberSpecial['children']['data'][] = array(
					'type' => 'numberspecialrate',
					'ns_rate_ratinggroup' => $ratinggroup,
					'range_unit' => $numberSpecialRateItem->field_field_range_units[0]['raw']['taxonomy_term']->name,
					'price_unit' => $numberSpecialRateItem->field_field_price_units[0]['raw']['taxonomy_term']->name,
					'uom_unit' => $numberSpecialRateItem->field_field_uom_units[0]['raw']['taxonomy_term']->name,
				
					'range_start' => $chargeCollectionItem['data'][0]['data']['#items'][0]['value'],
					'range_end' => $chargeCollectionItem['data'][1]['data']['#items'][0]['value'],
					'price_amount' => $chargeCollectionItem['data'][2]['data']['#items'][0]['value'],
					'uom_amount' => $chargeCollectionItem['data'][3]['data']['#items'][0]['value'],				
				);
			}
		}
		//add areacode to array
		$jsonData['NumberSpecial']['data'][] = $numberSpecial;
	}
	
	//dsm($jsonData,'before json');
	//dsm(json_encode($jsonData),'after json');
	
	return json_encode($jsonData);
}