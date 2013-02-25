<?php
function _json_exclusiveness($exportItemNids=NULL){
	$jsonData = array();
	$productIds = array();
	
	if(!empty($exportItemNids) && count($exportItemNids) > 1) {
		$exportItemNids = join('+', $exportItemNids);
	}
	
	$viewResult = views_get_view_result('list_exclusiveness', 'panel_pane_1', $exportItemNids);
	
	foreach($viewResult as $record) {
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
		
		$productIds[] = $product['product_id'];
	}
	
	if(!empty($productIds)) {
		$jsonData['ifvalues']['resources'] = $productIds;
		} else {
		$jsonData['ifvalues']['resources'] = array();
	}
	
	return json_encode($jsonData);
}
