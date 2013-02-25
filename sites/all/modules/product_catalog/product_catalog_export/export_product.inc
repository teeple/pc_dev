<?php

function _product_for_export($exportItemNids=NULL){
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
    if(count($exportItemNids) == 1) {
    	$exportItemNids = array($exportItemNids);
    }
    
		foreach($exportItemNids as $nid) {
			$node = node_load($nid);
			
    	//Basic Attributes
      $product = array();
      $product['type'] = 'product';
		
	    $product['attribute'] = _get_attribute($node);
		
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
        // $product['package_product'] = $packagedProducts;
        $product['auto_join_product'] = $packagedProducts;
        
        // Counter
        // 상품에서 사용하는 counter list만 정의함. Charging용인지 Accumulating용인지는 구분할 필요 없음.
        // 
        $product['counters'] = _get_counter_list($node);
		
        //nonusage
        $nonUsage = array();
		
		$nonUsage['threshold_scheme'] = _get_thresdhold_scheme($node);
		$nonUsage['deposit_scheme'] = _get_deposit_scheme($node);
        $nonUsage['recurring_scheme'] = _get_recurring_scheme($node->nid);
		$nonUsage['onetime_charge'] = _get_onetime_charge($node->nid);
		
        $product['nonusage'] = $nonUsage;
		$product['usage'] = array();

		// $product['rating_rules'] = rating_rules_export_by_content_type('rating_rule_export_product' ,  $products[$i]->nid);
		$product['rating_rules'] = rating_rules_export_by_content_type('rating_rule_export_product' ,  $node->nid);

		$productNids[] = $node->field_product_id['und'][0]['value'];
		
		$retDataTmp[] = $product;        
    }
    
    if(!empty($productNids)) {
    	$retData['ifvalues']['resources'] = array_values($productNids);
   	} else {
    	$retData['ifvalues']['resources'] = '';
	  }
	  
	$retData['products'] = $retDataTmp;
	
	return $retData;
}

function _get_deposit_scheme($product) {
	
	$scheme = array();
    $view = views_get_view('list_depositscheme');
    $view->set_display('panel_pane_4');
    $view->set_arguments(array('0' => $product->nid));
    $view->execute();
    if(!empty($view->result)){
        $scheme['deposit_scheme_id'] = $view->result[0]->node_field_data_field_ref_depositscheme_nid;    
    }else{
        $scheme = NULL;
    }
	return $scheme;
	
}

function _get_counter_list($product) {
    $counters = array(); 
    $view = views_get_view('list_prdcounterlist');
    $view->set_display('panel_pane_3');
    $view->set_arguments(array('0' => $product->nid));
    $view->execute();
    $counters = array();
    foreach($view->result as $item){
    	$counters[] = array('counter_id'=> $item->field_data_field_counter_list_field_counter_list_nid);
    }
	return $counters;
}

function _get_thresdhold_scheme($product) {
	
	$scheme = array();
	//threshold scheme
    $view = views_get_view('list_thresholdscheme');
    $view->set_display('panel_pane_3');
    $view->set_arguments(array('0' => $product->nid));
    $view->execute();
    if(!empty($view->result)){
        $schemeNode = node_load($view->result[0]->nid);
        $scheme['threshold_scheme_id'] = $schemeNode->field_ref_thresholdscheme['und'][0]['nid'];    
    }else{
        $scheme = NULL;
    }
	return $scheme;
}
		

function _get_recurring_scheme($productNid) {
	$retArray = array();
	
	$view_name = 'list_child_item_for_product';
	$display = 'panel_pane_1';
	$args = array(
		'0' => $productNid,
		'1' => 'prdnonusagerecurringchargescheme'
	);
	$records = _get_nids_from_views($view_name, $display, $args);
	$chargeScheme = node_load(current($records));
	
	$retArray['charge_scheme'] = array(
		'rcrr_insff_balance_charge' 
			=> !empty($chargeScheme->field_rcrr_insff_balance_charge)? $chargeScheme->field_rcrr_insff_balance_charge['und'][0]['value']: NULL,
		'rcrr_use_charging_day'		
			=> !empty($chargeScheme->field_rcrr_insff_balance_charge)? $chargeScheme->field_rcrr_insff_balance_charge['und'][0]['value']: NULL,
		'rcrr_charge_first_or_later'   
			=> !empty($chargeScheme->field_rcrr_charging_type)? $chargeScheme->field_rcrr_charging_type['und'][0]['value']: NULL,
		'rcrr_period_value'			
			=> !empty($chargeScheme->field_charging_cycle)? $chargeScheme->field_charging_cycle['und'][0]['value']: NULL,
		'rcrr_period_type'			 
			=> !empty($chargeScheme->field_charging_cycle_type)? $chargeScheme->field_charging_cycle_type['und'][0]['value']: NULL,
		'rcrr_charging_day_month'   
			=> !empty($chargeScheme->field_rcrr_charging_day_month)? $chargeScheme->field_rcrr_charging_day_month['und'][0]['value']: NULL,
		'rcrr_charging_day_week'	
			=> !empty($chargeScheme->field_rcrr_charging_day_week)? $chargeScheme->field_rcrr_charging_day_week['und'][0]['value']: NULL,
		'rcrr_charging_day_weekOrMonth' 
			=> !empty($chargeScheme->field_charging_day_type)? $chargeScheme->field_charging_day_type['und'][0]['value']: NULL,
	);
	
	$args[1] = 'prdnonusagerecurringbonusscheme';
	$records = _get_nids_from_views($view_name, $display, $args);
	$bonusScheme = node_load(current($records));
	
	$retArray['bonus_scheme'] = array(
		'rcrr_use_charging_day'		
			=> !empty($bonusScheme->field_rcrr_insff_balance_charge)? $bonusScheme->field_rcrr_insff_balance_charge['und'][0]['value']: NULL,
		'rcrr_period_value'			
			=> !empty($bonusScheme->field_charging_cycle)? $bonusScheme->field_charging_cycle['und'][0]['value']: NULL,
		'rcrr_period_type'			 
			=> !empty($bonusScheme->field_charging_cycle_type)? $bonusScheme->field_charging_cycle_type['und'][0]['value']: NULL,
		'rcrr_charging_day_month'   
			=> !empty($bonusScheme->field_rcrr_charging_day_month)? $bonusScheme->field_rcrr_charging_day_month['und'][0]['value']: NULL,
		'rcrr_charging_day_week'	
			=> !empty($bonusScheme->field_rcrr_charging_day_week)? $bonusScheme->field_rcrr_charging_day_week['und'][0]['value']: NULL,
		'rcrr_charging_day_weekOrMonth' 
			=> !empty($bonusScheme->field_charging_day_type)? $bonusScheme->field_charging_day_type['und'][0]['value']: NULL,
	);

	return $retArray;
}

/*
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
 */
 
function _get_nonusage_rollover($productNid) {
	
}

function _get_lifecyclescheme($productNid) {
	$view_name = 'list_tree_term_child_node_for_product';
	$display = 'panel_pane_1';
	$args = array('0' => $productNid);
	
	$contentType = 'simpleproductoffering';
	$productNode = node_load($productNid);
	$vocaName = _get_vocabulary_name($contentType, $productNode);
	
	$term = taxonomy_get_term_by_name('Subscriber Lifecycle Scheme', $vocaName);
	if(!empty($term)) {
		$args[] = current($term)->tid;
	}
	
	$req_labels = array(
		'lifecyclescheme_id' => 'Nid',
	);
	$records = _get_records_from_views_by_label($view_name, $display, $args, $req_labels);
	
	if(!empty($records)) {
	    $schemeNode = node_load($records[0]['lifecyclescheme_id']);
        return $schemeNode->field_lifecycle_scheme['und'][0]['nid'];
	} else {
		return NULL;	
	}
	
}

function _get_recurring_bonus($productNid) {
   
}

function _get_onetime_charge($productNid) {
    $view = views_get_view('list_other_onetime_charge_by_product_id');
    $view->set_display('panel_pane_1');
    $view->set_arguments(array('0' => $productNid));
    $view->execute();
    $charges = array();
    
    foreach($view->result as $item){
        $onetimeChargeTerm = taxonomy_term_load($item->taxonomy_term_data_field_data_field_ref_otherontimecharge_ti);
        $onetimeChargeNode = node_load($item->nid);
        $chargeType = _get_common_code($onetimeChargeTerm);
        if(isset($onetimeChargeNode->field_price_amount['und'][0]['value'])){
            $price = $onetimeChargeNode->field_price_amount['und'][0]['value'];
        }else{
            $price = NULL;
        }
        $charge = array(
            'charge_type' => $chargeType,
            'price' => $price
        );
        
        $charges[] = $charge; 
    }
    return $charges; 
}

function _get_attribute($product) {
	
	$result = array();
	$result_attribute_general = array();
	$result_attrbitue_exception = array();
	
	$reqArray = array(
		'product_id' => array(
			'through_common_code' => FALSE,
			'field' => 'field_product_id',
			'field_value' => "field_product_id['und'][0]['value']",
			'field_default' => NULL
		),
		'product_name' => array(
			'through_common_code' => FALSE,
			'field' => 'title',
			'field_value' => 'title',
			'field_value_default' => '',
		),
		'is_bundle' => array(
			'through_common_code' => FALSE,
			'field' => 'field_is_bundle',
			'field_value' => "field_is_bundle['und'][0]['value']",
			'field_value_default' => '0'
		),
		'deferred_change' => array(
			'through_common_code' => FALSE,
			'field' => 'field_deferred_subscription_flag',
			'field_value' => "field_deferred_subscription_flag['und'][0]['value']",
			'field_value_default' => '0' 
		),
		'description' => array(
			'through_common_code' => FALSE,
			'field' => 'field_description',
			'field_value' => "field_description['und'][0]['safe_value']",
			'field_value_default' => ''
		),
		'version' => array(
			'through_common_code' => FALSE,
			'field' => 'field_version',
			'field_value' => "field_version['und'][0]['value']",
			'field_value_default' => '1.0'
		),
		'billing_cycle' => array(
			'through_common_code' => FALSE,
			'field' => 'field_billing_cycle',
			'field_value' => "field_billing_cycle['und'][0]['value']",
			'field_value_default' => '1.0'
		),
		'bill_type' => array(
			'through_common_code' => TRUE,
			'field' => 'field_billing_type',
			'field_value' => "field_billing_type['und'][0]['tid']",
			'field_value_default' => NULL
		),
		'product_type' => array(
			'through_common_code' => TRUE,
			'field' => 'field_product_type',
			'field_value' => "field_product_type['und'][0]['tid']",
			'field_value_default' => NULL
		),
		'service_domain' => array(
			'through_common_code' => TRUE,
			'field' => 'field_service_type_of_provider',
			'field_value' => "field_service_type_of_provider['und'][0]['tid']",
			'field_value_default' => NULL
		),
		'status' => array(
			'through_common_code' => TRUE,
			'field' => 'field_offering_status',
			'field_value' => "field_offering_status['und'][0]['tid']",
			'field_value_default' => NULL
		),
		'customer_type' => array(
			'through_common_code' => TRUE,
			'field' => 'field_customer_type',
			'field_value' => "field_customer_type['und'][0]['tid']",
			'field_value_default' => NULL
		),
		'customer_group_type' => array(
			'through_common_code' => TRUE,
			'field' => 'field_customer_group_type',
			'field_value' => "field_customer_group_type['und'][0]['tid']",
			'field_value_default' => NULL
		),
		'treatment_day' => array(
            'through_common_code' => FALSE,
            'field' => 'field_treatment_day',
            'field_value' => "field_treatment_day['und'][0]['value']",
            'field_value_default' => NULL
        ),
        'treatment_price' => array(
            'through_common_code' => FALSE,
            'field' => 'field_treatment_price_amount',
            'field_value' => "field_treatment_price_amount['und'][0]['value']",
            'field_value_default' => 0
        ),
        'contract_period' => array(
            'through_common_code' => FALSE,
            'field' => 'field_contract_period‎',
            'field_value' => "field_contract_period‎['und'][0]['value']",
            'field_value_default' => 0
        ),   
        'roaming_allowed' => array(
            'through_common_code' => TRUE,
            'field' => 'field_roaming_allowed',
            'field_value' => "field_roaming_allowed['und'][0]['tid']",
            'field_value_default' => array('codeGroup' => 'RoamingAllwoed',
                                           'code' => '0',
                                           'meaning' => 'Not Allowed')
        ),     
	);
	
	$result_attribute_general = _get_result($reqArray, $product);
	$result_attrbitue_exception = _get_attribute_exceptions($product);
	//$result_attribute_exception = null;
	
	$result = array_merge($result_attribute_general, $result_attrbitue_exception);
	
	return $result;
}

function _get_result($reqArray, $product) {
	$retArray = array();
	foreach($reqArray as $key => $item) {
		if($item['through_common_code']) {
			$command = '$field = isset($product->'.$item['field'].')?$product->'.$item['field'].':0'.';';
			eval($command);
			
			if(!empty($field)) {
				$command = '$tempTerm = taxonomy_term_load($product->'.$item['field_value'].');';
				eval($command);
				$retItem =  _get_common_code($tempTerm);
			} else {
				$retItem = $item['field_value_default'];
			}
			
		} else {
			//$command = '$field = $product->'.$item['field'].';';
      $command = '$field = isset($product->'.$item['field'].')?$product->'.$item['field'].':0'.';';
			eval($command);
			
			if(!empty($field)) {
				$command = '$retItem = $product->'.$item['field_value'].';';
				eval($command);
				
			} else {
				$retItem = $item['field_value_default'];
			}
		}
		$retArray[$key] = $retItem;
	}
	return $retArray;
}

function _get_attribute_exceptions($product) {
		
	$retArray = array();
	
  $validStart = isset($product->field_validfor_product['und'][0]['value'])? 
          $product->field_validfor_product['und'][0]['value']: '0001-01-01 00:00:00';

	$validEnd = isset($product->field_validfor_product['und'][0]['value2'])? 
        $product->field_validfor_product['und'][0]['value2']: '0001-01-01 00:00:00';
          
	if($validStart == $validEnd){
	    $validEnd = '9999-12-31 23:59:59';
	} else {
		if(!empty($record->field_validfor_product)) {
	  	$tempArr = explode(' ', $record->field_validfor_product['und'][0]['value2']);
	  	$validEnd = $tempArr[0].' 23:59:59';
	  } else {
	    $validEnd = '9999-12-31 23:59:59';
	  }
	}
	$validForStr = $validStart . ' ~ '. $validEnd;
	
	$retArray['valid_for'] = $validForStr;
	
	if(!empty($product->field_parent_node_for_rp['und'][0]['nid'])){
        $parentNode = node_load($product->field_parent_node_for_rp['und'][0]['nid']);
        $retArray['parent_product_id'] = $parentNode->field_product_id['und'][0]['safe_value'];
    }else{
        $retArray['parent_product_id'] = NULL;
    }
	
	$view = views_get_view('list_product_child_node');
    $view->set_display('panel_pane_2');
    $view->set_arguments(array('0' => $product->nid, '1' => 'prdattributeprefixrangeallowed'));
    $view->execute();
    if(count($view->result) > 0){
        $allowedPrefixNode = node_load(current($view->result)->nid);
        $allowedPrefix = array();
        if(!empty($allowedPrefixNode->field_prefix_single['und'])){
            foreach($allowedPrefixNode->field_prefix_single['und'] as $item){
                $allowedPrefix[] = $item['value'];
            }
        }
        $retArray['prefix_allowed'] = $allowedPrefix;
    }
            
    $operator = array();
    foreach($product->field_service_operator['und'] as $item){
        $operatorTerm = taxonomy_term_load($item['tid']);
        $operator[] = _get_common_code($operatorTerm);
    }
    $retArray['service_operator'] = $operator;
    
    $view = views_get_view('list_product_child_node');
    $view->set_display('panel_pane_2');
    $view->set_arguments(array('0' => $product->nid, '1' => 'prdattributefeaturecode'));
    $view->execute();
    if(count($view->result) > 0){
        $prdFeatureCodeNode = node_load(current($view->result)->nid);
        foreach($prdFeatureCodeNode->field_ref_service_feature_code['und'] as $item){
            $serviceFeatureCodeNode = node_load($item['nid']);
            $serviceFeatureCodes[] = $serviceFeatureCodeNode->title;
        }
        /*
        $serviceFeatureCodeNode = node_load(current($view->result)->nid);
        $serviceFeatureCodes = array();
        foreach($serviceFeatureCodeNode->field_ref_featurecode['und'] as $item){
            $codeTerm = taxonomy_term_load($item['tid']);   
            $serviceFeatureCodes[] = _get_common_code($codeTerm);
        }
         * 
         */
        $retArray['service_feature_code'] = $serviceFeatureCodes;
    }
    $view = views_get_view('list_product_child_node');
    $view->set_display('panel_pane_2');
    $view->set_arguments(array('0' => $product->nid, '1' => 'prdattributebenefit'));
    $view->execute();
    $benefit = array();
	
	if(!empty($view->result)) {
	    $benefitNode = node_load(current($view->result)->nid);
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
		$benefit['cug_flag'] = $benefitNode->field_cug_flag['und'][0]['value'];
		$benefit['cug_discount'] = array();
		if(!empty($benefitNode->field_discount_for_cug)) {
			foreach($benefitNode->field_discount_for_cug['und'] as $discount_value) {
				$benefit['cug_discount'][] = $discount_value['value'];
			}
		}
		$retArray['benefit'] = $benefit;
	}
		
	// subscriber's lifecycle scheme과 연결
	$retArray['lifecyclescheme'] = _get_lifecyclescheme($product->nid);
    
    //required device
    $view = views_get_view('list_product_child_node');
    $view->set_display('panel_pane_2');
    $view->set_arguments(array('0' => $product->nid, '1' => 'prdattributerequireddevice'));
    $view->execute();
    $requiredDevice = array();
    
    if(!empty($view->result)) {        
        foreach($view->result as $record){
            $requiredDeviceNode = node_load($record->nid);
            $requiredDeviceInfo = array();            
            $deviceClassTerm = taxonomy_term_load($requiredDeviceNode->field_ref_device_class['und'][0]['tid']);
            $requiredDeviceInfo['device'] = _get_common_code($deviceClassTerm);
            $requiredDeviceInfo['amount'] = isset($requiredDeviceNode->field_amount['und'][0]['value'])?$requiredDeviceNode->field_amount['und'][0]['value']:0;
            $requiredDeviceInfo['deposit_price'] = isset($requiredDeviceNode->field_deposit_price['und'][0]['value'])?$requiredDeviceNode->field_deposit_price['und'][0]['value']:0;
            $requiredDevice [] = $requiredDeviceInfo;
        }
        $retArray['required_device'] = $requiredDevice;
    }
    
    //number saving
    $view = views_get_view('list_product_child_node');
    $view->set_display('panel_pane_2');
    $view->set_arguments(array('0' => $product->nid, '1' => 'prdattributenumbersaving'));
    $view->execute();
    $numberSavings = array();
    
    if(!empty($view->result)) {        
        foreach($view->result as $record){
            $numberSavingNode = node_load($record->nid);
            $numberSavingInfo = array();            
            $numberSavingInfo['saving_period'] = isset($numberSavingNode->field_saving_period['und'][0]['value'])?$numberSavingNode->field_saving_period['und'][0]['value']:0;
            $savingPeriodType = taxonomy_term_load($numberSavingNode->field_period_type['und'][0]['tid']);
            $numberSavingInfo['period_type'] = $savingPeriodType->name;
            $numberSavingInfo['deposit_price'] = isset($numberSavingNode->field_deposit_price['und'][0]['value'])?$numberSavingNode->field_deposit_price['und'][0]['value']:0;
            $numberSavings [] = $numberSavingInfo;
        }
        $retArray['number_saving'] = $numberSavings;
    }
    
    //allowed device
    $view = views_get_view('list_product_child_node');
    $view->set_display('panel_pane_2');
    $view->set_arguments(array('0' => $product->nid, '1' => 'prdattributeallowedmodel'));
    $view->execute();
    $allowedDevice = array();
    
    if(!empty($view->result)) {        
        foreach($view->result as $record){
            $allowedDeviceNode = node_load($record->nid);
            $deviceModelNode = node_load($allowedDeviceNode->field_ref_device_model['und'][0]['nid']);
            $allowedDevice[] = array(
                'device_name' => $deviceModelNode->name,
                'device_code' => $deviceModelNode->field_model_code['und'][0]['safe_value'],
                'device_class_name' => $deviceModelNode->field_model_class['und'][0]['safe_value'],
                'device_class_code' => $deviceModelNode->field_model_class_code['und'][0]['safe_value']
            );           
        }      
        $retArray['allowed_device'] = $allowedDevice;  
    }
    
    //available Channel
    $view = views_get_view('list_product_child_node');
    $view->set_display('panel_pane_2');
    $view->set_arguments(array('0' => $product->nid, '1' => 'prdattributeavailablechannel'));
    $view->execute();
    $availableChannel = array();
    
    if(!empty($view->result)) {        
        foreach($view->result as $record){
            $availableChannelNode = node_load($record->nid);
            $tvChannelNode = node_load($availableChannelNode->field_ref_tvchannel['und'][0]['nid']);
            $availableChannel[] = array(
                'channel_code' => $tvChannelNode->field_channel_code['und'][0]['safe_value'],                
            );           
        }      
        $retArray['available_channel'] = $availableChannel;  
    }
	
	return $retArray;
}

function _get_common_code($term){
	$data = array();

	
	$voca = taxonomy_vocabulary_machine_name_load($term->vocabulary_machine_name);
	$data['codeGroup'] = $voca->name;
	$data['code'] = isset($term->field_common_code['und'][0]['safe_value'])?$term->field_common_code['und'][0]['safe_value']:$term->name;
	$data['meaning'] = $term->name;
	return $data;
}
