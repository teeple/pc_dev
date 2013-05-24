<?php

function _product_change_scheme_for_export($exportItemNids = NULL, $isExternalAPI = FALSE) {
    $retData = array();
    $retDataTmp = array();
    $productNids = array();

    /*
     if(!empty($exportItemNids) && count($exportItemNids) > 1) {
     $exportItemNids = join('+', $exportItemNids);
     }

     $productView = views_get_view('query_product_export');
     $productView->set_arguments(array('0'=>$export_item_list));
     $productView->execute();
     $products = $productView->result;
     $productsCount = count($products);

     $viewResult = views_get_view_result('query_product_export', 'panel_pane_5', $exportItemNids);

     foreach($viewResult as $record) {
     */

    if (count($exportItemNids) == 1) {
        $exportItemNids = array($exportItemNids);
    }

    foreach ($exportItemNids as $nid) {
        $node = node_load($nid);

        //Basic Attributes
        $product = array();
        $product['type'] = 'product';

        $product['attribute'] = _get_attribute($node);

        //Packaged Products
        $packagedProducts = Array();
        $view = views_get_view('list_product_child_node');
        $view -> set_display('panel_pane_2');
        $view -> set_arguments(array('0' => $node -> nid, '1' => 'prdattributepackaged'));
        $view -> execute();
        foreach ($view->result as $item) {
            $packageProduct = Array();
            $packageNode = node_load($item -> nid);
            $connectedProduct = node_load($packageNode -> field_ref_connected_product['und'][0]['nid']);
            $packageProduct['package_product_id'] = $connectedProduct -> field_product_id['und'][0]['value'];
            $packageTypeTerm = taxonomy_term_load($packageNode -> field_ref_prdrelationtype['und'][0]['tid']);
            $packageProduct['relation_type'] = _get_common_code($packageTypeTerm);
            $packagedProducts[] = $packageProduct;
        }
        // $product['package_product'] = $packagedProducts;
        $product['auto_join_product'] = $packagedProducts;

        // Counter
        // 상품에서 사용하는 counter list만 정의함. Charging용인지 Accumulating용인지는 구분할 필요 없음.
        //
        $product['counters'] = _get_counter_list($node);

        //nonusage
        $nonUsage = array();

        // $nonUsage['threshold_scheme'] = _get_thresdhold_scheme($node);
        $nonUsage['deposit_scheme'] = _get_deposit_scheme($node);
        $nonUsage['recurring_scheme'] = _get_recurring_scheme($node -> nid);
        
        $recurringTypes = array(1 => 'Daily', 3 => '1/3 Monthly', 4 => 'Monthly');
        $nonUsage['recurring_charge']['period_type'] = $recurringTypes[$nonUsage['recurring_scheme']['charge_scheme']['rcrr_period_type']];;
        $nonUsage['recurring_charge']['charge_items'] = _get_recurring_amount($node->nid);
        $nonUsage['onetime_charge'] = _get_onetime_charge($node -> nid);
        $nonUsage['onetime_charge_discount_on_main'] = _get_onetime_charge_discount($node -> nid);

        $product['nonusage'] = $nonUsage;
        $product['usage'] = array();

        //relationship
        $product['relationship'] = _get_product_relationship($nid);
        
        // $product['rating_rules'] = rating_rules_export_by_content_type('rating_rule_export_product' ,  $products[$i]->nid);
        if(!$isExternalAPI) {
           $product['rating_rules'] = rating_rules_export_by_content_type('rating_rule_export_product', $node -> nid);
        }
        
        $productNids[] = $node -> field_product_id['und'][0]['value'];

        $retDataTmp[] = $product;
    }
    
    if(!$isExternalAPI) {
	    if (!empty($productNids)) {
	        $retData['ifvalues']['resources'] = array_values($productNids);
	    } else {
	        $retData['ifvalues']['resources'] = '';
	    }
	  }
	  
    $retData['products'] = $retDataTmp;

    return $retData;
}
