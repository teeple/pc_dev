<?php

function _array_voucher_cardtype($nid=NULL){
	$jsonData = array();

	//fetch data	
	$viewResult = views_get_view_result('list_vouchercardtype', 'panel_pane_2', $nid);

    foreach($viewResult as $record) {

        $jsonCounter['id'] = isset($record->nid) ? $record->nid: null;
        $jsonCounter['title'] = isset($record->node_title) ? $record->node_title: null;
        $jsonCounter['active_period'] = !empty($record->field_field_active_period) ? $record->field_field_active_period[0]['rendered']['#markup']: null;
        $jsonCounter['grace_period'] = !empty($record->field_field_grace_period) ? $record->field_field_grace_period[0]['rendered']['#markup']: null;
        $jsonCounter['price'] = !empty($record->field_field_price_amount) ? $record->field_field_price_amount[0]['rendered']['#markup']: null;
        $jsonCounter['voucher_type'] = _add_commoncode($record->field_field_ref_voucher_type);
        $jsonCounter['description'] = !empty($record->field_field_description_long) ? $record->field_field_description_long[0]['rendered']['#markup']: null;
        
		// domain별 counter처리
		// $listProduct = views_get_view_result('list_product_by_vouchercardtype', 'panel_pane_1', $record->nid);
		
		// product별 counter처리
		//$listProduct = views_get_view_result('list_product_by_vouchercardtype', 'panel_pane_1', $record->nid);
		$listProduct = views_get_view_result('list_treenodeproductforvoucher', 'panel_pane_1', $record->nid);

		$ret_product = array();
		foreach($listProduct as $product) {
			
			$tmpProduct['product_id'] = $product->node_field_data_field_ref_product_nid;
			$tmpProduct['product_name'] = $product->node_title;
			
			$ret_product[] = $tmpProduct;
			/*
			$listCounter = views_get_view_result('list_treenodecounterforvoucherprd', 'panel_pane_2', $product->nid);
			
			foreach($listCounter as $counter) {
				if(isset($counter->node_field_data_field_ref_counter_nid)) {
					$ret_counter = array();
					$ret_counter['counter_id'] = $counter->field_field_counter_id[0]['raw']['value'];
					$ret_counter['amount'] = !empty($counter->field_field_amount)? $counter->field_field_amount[0]['rendered']['#markup']: null;

					$ret_product['counters'][] = $ret_counter;
					
				}
			
			}
			if(empty($ret_counter)) {
				$ret_product['counters'] = null;
			}*/
			
		}

		if(empty($ret_product)) {
			$jsonCounter['products'] = null;

		} else {
			$jsonCounter['products'] = $ret_product;
		}

        $jsonData[] = $jsonCounter;
    }
    
	return $jsonData;
}

function _json_voucher_cardtype($nid=NULL) {
	$retArray = array();
	$jsonData  = _array_voucher_cardtype($nid);
    $retArray['ifvalues']['resources'] = '';
    
	$retArray['vouchers'] = $jsonData;
	$retArray['rating_rules'] = array();

	$arr = array();
	$arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "list_vouchercardtype");
	$arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "list_counter_for_vouchercardtype");
	$arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "list_loyaltypointfactors");
	foreach($arr as $a)
	{
		foreach($a as $t => $v)
		{
			$retArray['rating_rules'][$t] = $v;
		}
	}

	if($nid != NULL) {
		return json_encode($jsonData);
	} else {
		return json_encode($retArray);
	}
}
