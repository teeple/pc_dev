<?php

function _product_for_export($nid=NULL){
    $retData = array();
	$retDataTmp = array();
	$productNids = array();
	
    $productView = views_get_view('query_product_export');
    $productView->set_arguments(array('0'=>$nid));
    $productView->execute();

    $products = $productView->result;

    $productsCount = count($products);
    for($i=0;$i<$productsCount;$i++) {
        
        $product = array();
        
        //Basic Attributes
        $node = node_load($products[$i]->nid);

        $billingTypeTerm = taxonomy_term_load($node->field_billing_type['und'][0]['tid']);
        //dsm($billingTypeTerm,'$billingTypeTerm');

        $product['type'] = 'product';

        $attribute = array();
        $attribute['product_id'] = $node->field_product_id['und'][0]['safe_value'];
        $attribute['product_name'] = $node->title;
		
		if(!empty($node->field_is_bundle)){
        	$attribute['is_bundle'] = $node->field_is_bundle['und'][0]['value'];
		}else{
			$attribute['is_bundle'] = '0';
		}
		
        $productTypeTerm = taxonomy_term_load($node->field_product_type['und'][0]['tid']);      
        $attribute['product_type'] = _get_common_code($productTypeTerm);
        
        $validForStr;
        if(isset($node->field_validfor_product['und'][0]['value'])){
            $validForStr = $node->field_validfor_product['und'][0]['value'];
        }else{
            $validForStr = '0001-01-01 00:00:00';
        }
        $validForStr .= ' ~ ';
        if(isset($node->field_validfor_product['und'][0]['value2'])){
            $validForStr .= $node->field_validfor_product['und'][0]['value2'];
        }else{
            $validForStr .= '9999-12-31 23:59:59';
        }
        
        $attribute['valid_for'] = $validForStr;

        $serviceTypeTerm = taxonomy_term_load($node->field_service_type_of_provider['und'][0]['tid']);
        $attribute['service_domain'] = _get_common_code($serviceTypeTerm);
        $billTypeTerm = taxonomy_term_load($node->field_billing_type['und'][0]['tid']);
        $attribute['bill_type'] = _get_common_code($billTypeTerm);
        
        $statusTerm = taxonomy_term_load($node->field_offering_status['und'][0]['tid']);
        $attribute['status'] = _get_common_code($statusTerm);
        if(!empty($node->field_description['und'][0]['safe_value'])){
            $attribute['description'] = $node->field_description['und'][0]['safe_value'];
        }else{
            $attribute['description'] = NULL;
        }
        if(!empty($node->field_parent_node_for_rp['und'][0]['nid'])){
            $parentNode = node_load($node->field_parent_node_for_rp['und'][0]['nid']);
            $attribute['parent_product_id'] = $parentNode->field_product_id['und'][0]['safe_value'];
        }else{
            $attribute['parent_product_id'] = NULL;
        }

        $attribute['version'] = $node->field_version['und'][0]['value'];
        if(!empty($node->field_billing_cycle['und'][0]['value'])){
            $attribute['billing_cycle'] = $node->field_billing_cycle['und'][0]['value'];
        }else{
            $attribute['billing_cycle'] = NULL;
        }

        $customerTypeTerm = taxonomy_term_load($node->field_customer_type['und'][0]['tid']);
        $attribute['customer_type'] = _get_common_code($customerTypeTerm);

        if(!empty($node->field_customer_group_type['und'])){
            $customerGroupType = taxonomy_term_load($node->field_customer_group_type['und'][0]['tid']);
            $attribute['customer_group_type'] = _get_common_code($customerGroupType);
        }

        $view = views_get_view('list_product_child_node');
        $view->set_display('panel_pane_2');
        $view->set_arguments(array('0' => $node->nid, '1' => 'prdattributeprefixrangeallowed'));
        $view->execute();
        if(count($view->result) > 0){
            $allowedPrefixNode = node_load(current($view->result)->nid);
            $allowedPrefix = array();
            if(!empty($allowedPrefixNode->field_prefix_single['und'])){
                foreach($allowedPrefixNode->field_prefix_single['und'] as $item){
                    $allowedPrefix[] = $item['value'];
                }
            }
            $attribute['prefix_allowed'] = $allowedPrefix;
        }
                
        $operator = array();
        foreach($node->field_service_operator['und'] as $item){
            $operatorTerm = taxonomy_term_load($item['tid']);
            $operator[] = _get_common_code($operatorTerm);
        }
        $attribute['service_operator'] = $operator;
        
        $view = views_get_view('list_product_child_node');
        $view->set_display('panel_pane_2');
        $view->set_arguments(array('0' => $node->nid, '1' => 'prdattributefeaturecode'));
        $view->execute();
        if(count($view->result) > 0){
            $serviceFeatureCodeNode = node_load(current($view->result)->nid);
            $serviceFeatureCodes = array();
            foreach($serviceFeatureCodeNode->field_ref_featurecode['und'] as $item){
                $codeTerm = taxonomy_term_load($item['tid']);   
                $serviceFeatureCodes[] = _get_common_code($codeTerm);
            }
            $attribute['service_feature_code'] = $serviceFeatureCodes;
        }
        $view = views_get_view('list_product_child_node');
        $view->set_display('panel_pane_2');
        $view->set_arguments(array('0' => $node->nid, '1' => 'prdattributebenefit'));
        $view->execute();
        $benefitNode = node_load(current($view->result)->nid);
        $benefit = array();
        if(!empty($benefitNode->field_attribute_discount['und'][0]['safe_value'])){
            $benefit['discount'] = $benefitNode->field_attribute_discount['und'][0]['safe_value'];
        }else{
            $benefit['discount'] = NULL;
        }
        if(!empty($benefitNode->field_attribute_bonus['und'][0]['safe_value'])){
            $benefit['bonus'] = $benefitNode->field_attribute_bonus['und'][0]['safe_value'];
        }else{
            $benefit['bonus'] = NULL;
        }
        $attribute['benefit'] = $benefit;
		
		// subscriber's lifecycle scheme과 연결
		$attribute['lifecyclescheme'] = _get_lifecyclescheme($node->nid);
		
		$product['attribute'] = $attribute;
        
        //Packaged Products
        $packagedProducts = Array();
        $view = views_get_view('list_product_child_node');
        $view->set_display('panel_pane_2');
        $view->set_arguments(array('0' => $node->nid, '1' => 'prdattributepackaged'));
        $view->execute();
        foreach($view->result as $item){
            $packageProduct = Array();
            $packageNode = node_load($item->nid);
			$connectedProduct = node_load($packageNode->field_ref_connected_product['und'][0]['nid']);
			$packageProduct['package_product_id'] = $connectedProduct->field_product_id['und'][0]['value'];
			$packageTypeTerm = taxonomy_term_load($packageNode->field_ref_prdrelationtype['und'][0]['tid']);
            $packageProduct['relation_type'] = _get_common_code($packageTypeTerm);
            $packagedProducts [] = $packageProduct;
        }
        $product['package_product'] = $packagedProducts;
        
        // Counter
        // 상품에서 사용하는 counter list만 정의함. Charging용인지 Accumulating용인지는 구분할 필요 없음.
        // 
        $counters = array(); 
        $view = views_get_view('list_prdcounterlist');
        $view->set_display('panel_pane_3');
        $view->set_arguments(array('0' => $node->nid));
        $view->execute();
        
		$counters = array();
        foreach($view->result as $item){
        	$counters[] = array('counter_id'=> $item->field_data_field_counter_list_field_counter_list_nid);
        }       
        $product['counters'] = $counters;

        //nonusage
        $nonUsage = array();
		
		//one time fee
		// $nonUsage['onetime_charge'] = _get_onetime_charge($productNid);
		
        //threshold scheme
        $view = views_get_view('list_thresholdscheme');
        $view->set_display('panel_pane_3');
        $view->set_arguments(array('0' => $node->nid));
        $view->execute();
        if(!empty($view->result)){
            $nonUsage['threshold_scheme_id'] = $view->result[0]->nid;    
        }
        
        //deposit scheme
        $view = views_get_view('list_depositscheme');
        $view->set_display('panel_pane_4');
        $view->set_arguments(array('0' => $node->nid));
        $view->execute();
        if(!empty($view->result)){
            $nonUsage['deposit_scheme_id'] = $view->result[0]->node_field_data_field_ref_depositscheme_nid;    
        }
		$nonUsage['recurring_charge'] = _get_recurring_charge($node->nid);
		
        $product['nonusage'] = $nonUsage;

		$product['usage'] = array();

		$product['rating_rules'] = rating_rules_export_by_content_type('rating_rule_export_product' ,  $products[$i]->nid);

		$productNids[] = $attribute['product_id'];
		$retDataTmp[] = $product;        
    }
    
    // return json_encode($jsonData);
    //if($nid==NULL) return $retData['products'][0];
    //else return $retData;
        
    if($nid!=NULL) {
    	$retData['ifvalues']['resources'] = array_values($productNids);
	} else {
    	$retData['ifvalues']['resources'] = '';
	}
	$retData['products'] = $retDataTmp;
	//dsm(json_encode($retData),'after json');
	
	return $retData;
}

function _get_recurring_charge($productNid) {
	$view_name = 'list_actionpricechargerecurring';
	$display = 'panel_pane_1';
	$args = array( '0'=> $productNid );
	
	$req_labels = array(
		'rcrr_insff_balance_charge' => 'Insufficient Balance Charge',
		'price_amount' 				=> 'Price_amount',
		'price_unit' 				=> 'Price_units',
		'valid_for' 				=> 'validFor',
		'cycle_pricing' 			=> 'Pricing Cycle',
		'cycle_type_pricing' 		=> 'Pricing Cycle Type',
		'rcrr_use_charging_day'		=> 'Related to Invoice Date',
		'rcrr_insff_balance_charge' => 'Charging First or Later',
		'rcrr_period_type'			=> 'Charging Cycle Type', 
		'rcrr_period_value'			=> 'Charging Cycle',
		'rcrr_charging_day_month'   => 'Charging Day_Day of Month',
		'rcrr_charging_day_week'	=> 'Charging Day_Day of Week',
		'rcrr_charging_day_weekOrMonth' => 'Charging Day_Week or Month',
		'pricing_cycle'				=> 'Pricing Cycle',
		'pricing_cycle_type'		=> 'Pricing Cycle Type',
		'charging_cycle'			=> 'Charging Cycle',
		'charging_cycle_type'		=> 'Charging Cycle Type'
	);
	$records = _get_records_from_views_by_label($view_name, $display, $args, $req_labels);
	
	return $records;
}

function _get_lifecyclescheme($productNid) {
	
	$view_name = 'list_tree_term_child_node_for_product';
	$display = 'panel_pane_1';
	$args = array('0' => $productNid);
	
	$contentType = 'simpleproductoffering';
	$productNode = node_load($productNid);
	$vocaName = _get_vocabulary_name($contentType, $productNode);
	
	dsm($vocaName, 'vocaName');
	
	$term = taxonomy_get_term_by_name('Subscriber Lifecycle Scheme', $vocaName);
	$args[] = current($term)->tid;
	
	$req_labels = array(
		'lifecyclescheme_id' => 'Nid',
	);
	$records = _get_records_from_views_by_label($view_name, $display, $args, $req_labels);
	
	return $records[0];
}

function _get_recurring_bonus($productNid) {
   
}

function _get_onetime_charge($productNid) {

        $view = views_get_view('list_product_child_node');
        $view->set_display('panel_pane_2');
        $view->set_arguments(array('0' => $node->nid, '1' => 'actionpricechargeonetime'));
        $view->execute();
        foreach($view->result as $item){
            $onetimeFeeNode = node_load($item->nid);
            $feeTerm = taxonomy_term_load($onetimeFeeNode->field_ref_tree_tid['und'][0]['value']);
            $priceUnitTerm = taxonomy_term_load($onetimeFeeNode->field_price_units['und'][0]['tid']);
            
            $fee = array(
                'fee_type' => $feeTerm->name,
                'price_unit' => _get_common_code($priceUnitTerm),
                'price_amount' => $onetimeFeeNode->field_price_amount['und'][0]['value'],
                'valid_for' => $onetimeFeeNode->field_valid_for['und'][0]['value'].' ~ '.$onetimeFeeNode->field_valid_for['und'][0]['value2'],     
            );
            
            $fees[] = $fee;               
        }
        $nonUsage['fees'] = $fees;
}

function _get_common_code($term){
	$data = array();
	$voca = taxonomy_vocabulary_machine_name_load($term->vocabulary_machine_name);
	$data['codeGroup'] = $voca->name;
	$data['code'] = isset($term->field_common_code['und'][0]['safe_value'])?$term->field_common_code['und'][0]['safe_value']:$term->name;
	$data['meaning'] = $term->name;
	return $data;
}
