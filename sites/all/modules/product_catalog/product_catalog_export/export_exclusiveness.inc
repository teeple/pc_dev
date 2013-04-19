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
		
        //exclusiveness
        foreach($record->field_field_exclusiveness as $item){
            $exclusive_product_ids[] = $item['raw']['node']->field_product_id['und'][0]['safe_value'];
        }
        //exclusiveness others
        foreach($record->field_field_exclusiveness_others as $item){
            $exclusive_product_other_ids[] = $item['raw']['node']->field_product_id['und'][0]['safe_value'];
        }
        //downgrade penalty
        $downgradePenaltyViewResult = views_get_view_result('list_product_downgrade_penalty', 'panel_pane_2', $record->nid);
        foreach($downgradePenaltyViewResult as $item){
            $downgrade[] = array('product_id' => $item->field_field_ref_target_product[0]['raw']['node']->field_product_id['und'][0]['safe_value'],
                                 'penalty_amount' => $item->field_field_amount[0]['raw']['value']);
        }
        
		$product['product_id'] = $record->field_field_product_id[0]['raw']['value'];
		$product['exclusiveness'] = $exclusive_product_ids;
        $product['exclusiveness_other'] = $exclusive_product_other_ids;
        $product['downgrade_penalty'] = $downgrade;
        
		$jsonData['ProductRelationship'][] = $product;
		
		$productIds[] = $product['product_id'];
	}
	
	if(!empty($productIds)) {
		$jsonData['ifvalues']['resources'] = $productIds;
	} else {
	   $jsonData['ifvalues']['resources'] = array();
	}
	
    return json_encode($jsonData);
}
