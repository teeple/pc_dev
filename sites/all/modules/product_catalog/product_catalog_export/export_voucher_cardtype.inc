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
        
		$listProduct = views_get_view_result('list_product_by_vouchercardtype', 'panel_pane_1', $record->nid);

		$ret_product = array();
		foreach($listProduct as $product) {
			$ret_product['product_id'] = $product->node_field_data_field_ref_node_nid;
			$ret_product['product_name'] = $product->node_field_data_field_ref_node_title;

			$listCounter = views_get_view_result('list_treenodecounterforvoucher', 'panel_pane_1', $product->nid);
			foreach($listCounter as $counter) {
				$ret_counter = array();
				$ret_counter['counter_id'] = $counter->node_field_data_field_ref_counter_nid;
				$ret_counter['counter_name'] = $counter->node_field_data_field_ref_counter_title;
				$ret_counter['amount'] = !empty($counter->field_field_amount_1)? $counter->field_field_amount_1[0]['rendered']['#markup']: null;

				$ret_product['counters'][] = $ret_counter;
			}
			if(empty($ret_counter)) {
				$ret_product['counters'] = null;
			}
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
	$retArray['vouchers'] = $jsonData;

	if($nid != NULL) {
		return json_encode($jsonData);
	} else {
		return json_encode($retArray);
	}
}
