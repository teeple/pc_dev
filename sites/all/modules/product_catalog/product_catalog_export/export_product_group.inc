<?php

function _product_group_for_export($exportItemNids = NULL, $isExternalAPI = FALSE) {
    $retData = array();
    $retDataTmp = array();
    $productNids = array();

    if (count($exportItemNids) == 1) {
        $exportItemNids = array($exportItemNids);
    }
    
    $viewResult = views_get_view_result('list_product_group', 'panel_pane_4', join(',', $exportItemNids));
    
    foreach ($viewResult as $record) {
        $productGroup = array();
        $productGroup['product_group_id'] = $record->field_field_product_group_id[0]['raw']['value'];
        $productGroup['service_domain'] = _get_common_code($record->field_field_service_domain[0]['raw']['taxonomy_term']);
		$productGroup['billing_type'] = _get_common_code($record->field_field_billing_type[0]['raw']['taxonomy_term']);
		
		$viewResultMainSelected = views_get_view_result('list_product_group_main_selected', 'panel_pane_4', $record->nid);
		foreach($viewResultMainSelected as $mainProduct) {
			$productGroupMain[] = array('product_id' => $mainProduct->field_field_product_id[0]['raw']['value']);
		}
		
		$productGroup['selected_products'] = $productGroupMain;
		
        $retDataTmp[] = $productGroup;
    }
    
    if(!$isExternalAPI) {
	    if (!empty($exportItemNids)) {
	        $retData['ifvalues']['resources'] = array_values($exportItemNids);
	    } else {
	        $retData['ifvalues']['resources'] = '';
	    }
	  }
	  
    $retData['product_groups'] = $retDataTmp;

    return $retData;
}
