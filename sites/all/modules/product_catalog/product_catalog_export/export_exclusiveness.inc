<?php

function _json_exclusiveness($nid=NULL){
	$jsonData = array();

	//fetch data		
	$viewExclusiveness = views_get_view('list_exclusiveness');
	$viewExclusiveness->set_display('panel_pane_1');
	$viewExclusiveness->execute();
	
	$productExclusiveness = $viewExclusiveness->result;
	
	foreach($productExclusiveness as $record) {
		$product = array();
		$exclusive_product_nids = array();
		
		foreach($record->field_field_exclusiveness as $exclusiveIds) {
			$exclusive_product_nids[] = $exclusiveIds['raw']['nid'];
		}
		
		$view = views_get_view('list_exclusiveness');
		$view->set_display('panel_pane_2');
		$view->set_arguments(array('0' => join('+',$exclusive_product_nids)));
		$view->execute();
		
		foreach($view->result as $item) {
			$exclusive_product_ids[] = $item->field_field_product_id[0]['rendered']['#markup'];
		}
		
		$product['product_id'] = $record->field_field_product_id[0]['raw']['value'];
		$product['exclusiveness'] = $exclusive_product_ids;
		$jsonData['ProductExclusiveness'][] = $product;
	}
	
	return json_encode($jsonData);
}
