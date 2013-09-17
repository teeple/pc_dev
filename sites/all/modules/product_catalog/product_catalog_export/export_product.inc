<?php

function _product_for_export($exportItemNids = NULL, $isExternalAPI = FALSE, $target=NULL) {
    $retData = array();
    $retDataTmp = array();
    $productNids = array();
    
    if (!is_array($exportItemNids)) {
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
        $product['counters'] = _get_counter_list($node);

        //nonusage
        $nonUsage = array();

        // $nonUsage['threshold_scheme'] = _get_thresdhold_scheme($node);
        $nonUsage['deposit_scheme'] = _get_deposit_scheme($node, $target);
        $nonUsage['recurring_scheme'] = _get_recurring_scheme($node -> nid);
        $recurringScheme = $nonUsage['recurring_scheme'];
        
        $recurringTypes = array(1 => 'Daily', 3 => '1/3 Monthly', 4 => 'Monthly');
        
        if( isset($recurringScheme) ) {
        	$nonUsage['recurring_charge'] = _get_recurring_amount($node->nid, $recurringScheme);
        } else {
        	$nonUsage['recurring_charge'] = NULL;
        }
        
        //custom recurring charge by CS
        $recurring_by_cs_view_result = views_get_view_result('list_actionpricechargerecurring', 'panel_pane_5', $node->nid);
        if(!empty($recurring_by_cs_view_result)){
			$recurring_by_cs = current($recurring_by_cs_view_result);
			$nonUsage['recurring_scheme']['charge_by_cs_scheme']['use'] = isset($recurring_by_cs->field_field_set_use[0]['raw']['value'])?$recurring_by_cs->field_field_set_use[0]['raw']['value']:"0";
			if(isset($recurring_by_cs->field_field_charging_cycle_type[0]['raw']['value'])){
				$nonUsage['recurring_scheme']['charge_by_cs_scheme']['rcrr_period_type'] = $recurring_by_cs->field_field_charging_cycle_type[0]['raw']['value'];
			}else{
				$nonUsage['recurring_scheme']['charge_by_cs_scheme']['rcrr_period_type'] = NULL;
			}
			foreach($recurring_by_cs->field_field_subscriber_status as $status) {
				$nonUsage['recurring_scheme']['charge_by_cs_scheme']['subscriber_status'][] = $status['rendered']['#title'];
			}
			
		} else {
			$nonUsage['recurring_scheme']['charge_by_cs_scheme'] = NULL;
		}
			  
        $nonUsage['onetime_charge'] = _get_onetime_charge($node -> nid);
        $nonUsage['onetime_charge_discount_on_main'] = _get_onetime_charge_discount($node -> nid);

		// bhtak add group bonus
        $nonUsage['group_bonus'] = _get_group_bonus($node -> nid);

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

function _get_product_relationship($nid){
    $viewResult = views_get_view_result('list_exclusiveness', 'panel_pane_1', $nid);
    $relationship = array(); 
    
    foreach($viewResult as $record) {
    
        //exclusiveness
        foreach($record->field_field_exclusiveness as $item){
            $exclusive_product_ids[] = $item['raw']['node']->field_product_id['und'][0]['safe_value'];
        }
        
        //exclusiveness ot1rs
        foreach($record->field_field_exclusiveness_others as $item){
            $exclusive_product_other_ids[] = $item['raw']['node']->field_product_id['und'][0]['safe_value'];
        }
        
        // prerequisite products
        foreach($record->field_field_prerequisite_products as $item){
        	$prerequisite_product_ids[] = $item['raw']['node']->field_product_id['und'][0]['safe_value'];
        }
        
        //downgrade penalty
        $downgradePenaltyViewResult = views_get_view_result('list_product_downgrade_penalty', 'panel_pane_2', $record->nid);
        foreach($downgradePenaltyViewResult as $item){
            $downgrade[] = array('product_id' => $item->field_field_ref_target_product[0]['raw']['node']->field_product_id['und'][0]['safe_value'],
                                 'penalty_amount' => $item->field_field_amount[0]['raw']['value']);
        }
        
        //$relationship['product_id'] = $record->field_field_product_id[0]['raw']['value'];
        if(isset($exclusive_product_ids)) $relationship['exclusiveness'] = $exclusive_product_ids;
        if(isset($exclusive_product_other_ids)) $relationship['exclusiveness_other'] = $exclusive_product_other_ids;
        if(isset($prerequisite_product_ids)) $relationship['prerequisite'] = $prerequisite_product_ids;        
        if(isset($downgrade)) $relationship['downgrade_penalty'] = $downgrade;
    }
    return $relationship;
}

function _get_deposit_scheme($product,$target=NULL) {
	$depositScheme = array();

	$productTypeTerm = taxonomy_term_load($product->field_product_type['und'][0]['tid']);
	$billingTypeTerm = taxonomy_term_load($product->field_billing_type['und'][0]['tid']);
	
	$scheme = NULL;
	
	// Additional / Postpaid type product
	if( ($productTypeTerm->name == 'VAS') && ($billingTypeTerm->name == 'Postpaid') ) {
		
		// get deposit amount
		$viewResult = views_get_view_result('list_prdattributedeposit', 'panel_pane_1', $product->nid);
		if( count($viewResult) >  0 ) { 
			
			$prdAttributeDeposit = current($viewResult);
			$depositAmount = !empty($prdAttributeDeposit->field_field_deposit_amount)? $prdAttributeDeposit->field_field_deposit_amount[0]['raw']['value']: NULL;
			
			$thresholdCounterNid = !empty($prdAttributeDeposit->field_field_threshold_counter)? $prdAttributeDeposit->field_field_threshold_counter[0]['raw']['nid']: NULL;
			
			if(!empty($prdAttributeDeposit->field_field_deposit_group_code)) {
					$depositGroupCodeTid = $prdAttributeDeposit->field_field_deposit_group_code[0]['raw']['tid'];
				} else {
					$depositGroupCodeTid = NULL;
			}
			
			if($thresholdCounterNid > 0) {
				$treeNodeCounter = node_load($thresholdCounterNid);
				
				// $thresholdLimit = $treeNodeCounter->field_field_threshold_on_counter[0]['raw']['value'];
				$thresholdLimit = $treeNodeCounter->field_threshold_limit_amount['und'][0]['value'];
				
				// create threshold scheme
				$thresholdScheme = _create_threshold_scheme($treeNodeCounter);
			
				// create deposit scheme
				$depositScheme = _create_deposit_scheme($treeNodeCounter, $depositAmount, $thresholdLimit, $thresholdScheme,$depositGroupCodeTid);
			
				if(isset($target)) {
					$redirectFlag = FALSE;
					// 해당 threshold scheme을 deploy한다.
					export_deploy('THRESHOLD_SCHEME', array($thresholdScheme->nid => $thresholdScheme), $target, $redirectFlag);
				
					// 해당 deposit scheme을 deploy한다.
					export_deploy('DEPOSIT_SCHEME', array($depositScheme->nid => $depositScheme), $target, $redirectFlag);
				}
				node_delete($depositScheme->nid);
				node_delete($thresholdScheme->nid);
				
				$scheme['deposit_scheme_id'] = $depositScheme->nid;
			}
		}
		
	} else {
	
	    $view = views_get_view('list_depositscheme');
	    $view -> set_display('panel_pane_4');
	    $view -> set_arguments(array('0' => $product -> nid));
	    $view -> execute();
	    
	    if (!empty($view -> result)) {
	        $scheme['deposit_scheme_id'] = $view -> result[0] -> node_field_data_field_ref_depositscheme_nid;
	        
	    } else {
	        $scheme = NULL;
	        
	    }
	}
	
	return $scheme;
}

function _create_threshold_scheme($treeNodeCounter) {
	global $user;
	
	// thresholdscheme save
	$scheme = new stdClass();
	$scheme->type = 'thresholdscheme';
	$scheme->title = 'thresholdscheme_tmp';
	$scheme->language = 'und';
	$scheme->status = 1;
	$scheme->sticky = 1;
	$scheme->uid = $user->uid;
	node_save($scheme);
	
	// threshold scheme factors
	$factor = new stdClass();
	$factor->type = 'thresholdschemefactors';
	node_object_prepare($factor);
	$factor->title = 'ThresholdSchemeFactors';
	$factor->language = LANGUAGE_NONE;
	$factor->status = 1;
	$factor->sticky = 1;
	$factor->uid = $user->uid;
	$factor->field_limittothreshold['und'][0]['value'] = 100;
	$factor->field_ref_thresholdscheme['und'][0]['nid'] = $scheme->nid;
	node_save($factor);
	
	$tmpViewResult = views_get_view_result('list_actionsetonthreshold', 'panel_pane_2', $treeNodeCounter->nid);
	
	if( count($tmpViewResult) > 0 ) {
		$actionSetThreshold = current($tmpViewResult);
		
		// Create and save field collection for node
		$field_collection_item = entity_create('field_collection_item', array('field_name' => 'field_threshold_action_set'));
		$field_collection_item->setHostEntity('node', $factor);
		$field_collection_item->field_action_type[LANGUAGE_NONE][]['tid'] = $actionSetThreshold->field_field_threshold_action_wo_block[0]['raw']['tid'];
		$field_collection_item->field_message_orig[LANGUAGE_NONE][]['value'] = $actionSetThreshold->field_field_message_orig[0]['raw']['value'];
		$field_collection_item->field_message_dest[LANGUAGE_NONE][]['tid'] = $actionSetThreshold->field_field_message_dest[0]['raw']['tid'];
		$field_collection_item->field_ref_messages[LANGUAGE_NONE][]['nid'] = $actionSetThreshold->field_field_ref_messages[0]['raw']['nid'];
		$field_collection_item->save();
	}
	
	return $scheme;
}

function _create_deposit_scheme($treeNodeCounter, $depositAmount, $thresholdLimit, $thresholdScheme,$depositGroupCodeTid) {
	global $user;
	
	$product = node_load($treeNodeCounter->field_ref_product['und'][0]['nid']);
	
	// thresholdscheme save
	$scheme = new stdClass();
	$scheme->type = 'depositscheme';
	$scheme->title = 'depositscheme_tmp';
	$scheme->language = LANGUAGE_NONE;
	$scheme->status = 1;
	$scheme->sticky = 1;
	$scheme->uid = $user->uid;
	$scheme->field_service_domain['und'][0]['tid'] = $product->field_service_type_of_provider['und'][0]['tid'];
	node_save($scheme);
	
	// thresholdschemefactors save
	$factor = new stdClass();
	$factor->type = 'depositschemefactors';
	node_object_prepare($factor);
	$factor->title = 'depositschemefactors_tmp';
	$factor->language = LANGUAGE_NONE;
	$factor->status = 1;
	$factor->sticky = 1;
	$factor->uid = $user->uid;
	$factor->field_ref_depositscheme['und'][0]['nid'] = $scheme->nid;
	$factor->field_ref_thres_counter_acc['und'][0]['nid'] = $treeNodeCounter->field_ref_counter['und'][0]['nid'];
	$factor->field_ref_thres_counter_limit['und'][0]['nid'] = $treeNodeCounter->field_ref_counter['und'][0]['nid'];
	$factor->field_is_default_factor['und'][0]['value'] = 0;
	$factor->field_ref_thresholdscheme['und'][0]['nid'] = $thresholdScheme->nid;
	$factor->field_deposit_group_code['und'][0]['tid'] = $depositGroupCodeTid;
	$factor->field_thismonth_accu_counter = NULL;
	$factor->field_ref_type_of_call_mul = NULL;
	$factor->field_counter_unit_type['und'][0]['tid'] = 696; // Money type fixed
	node_save($factor);
	
	// field_deposit_amount_collection
	
	// Create and save field collection for node
	$field_collection_item = entity_create('field_collection_item', array('field_name' => 'field_deposit_amount_collection'));
	$field_collection_item->setHostEntity('node', $factor);
	$field_collection_item->field_deposit_amount[LANGUAGE_NONE][]['value'] = $depositAmount;
	$field_collection_item->field_threshold_amount[LANGUAGE_NONE][]['value'] = $thresholdLimit;
	$field_collection_item->field_threshold_amount_max[LANGUAGE_NONE][]['value'] = $thresholdLimit;
	$field_collection_item->save();
	
	return $scheme;
}

function _get_counter_list($product) {

    $productType = taxonomy_term_load($product -> field_product_type['und'][0]['tid']);
    $voca_name = _get_vocabulary_name('simpleproductoffering', $product);
    
    $counters = array();
    $optionalCounters = array();
    if ($productType -> name == 'CUG') {
        $sharedBalanceTerm = taxonomy_get_term_by_name('Shared Balance', $voca_name);
        $refTreeTid =  current($sharedBalanceTerm) -> tid;

        $view = views_get_view('list_tree_term_child_node_for_product');
        $view -> set_display('panel_pane_1');
        $view -> set_arguments(array('0' => $product -> nid, '1' => $refTreeTid));
        $view -> execute();
        $counterNids = array();

        foreach ($view->result as $item) {
            $counterNids[] = $item -> nid;
        }

        $viewResult = views_get_view_result('list_counter_all', 'panel_pane_3', join('+', $counterNids));

        foreach ($viewResult as $item) {
            $optionalCounters[] = array('counter_id' => $item -> field_field_counter_id[0]['raw']['value']);
        }

    } else {
        $view = views_get_view('list_prdcounterlist');
        $view -> set_display('panel_pane_3');
        $view -> set_arguments(array('0' => $product -> nid));
        $view -> execute();
        $counters = array();
        foreach ($view->result as $item) {
            $counterNids[] = $item -> field_data_field_counter_list_field_counter_list_nid;
        }
        
        $viewResult = views_get_view_result('list_counter_all', 'panel_pane_2', join('+', $counterNids));

        foreach ($viewResult as $item) {
            $optionalCounters[] = array('counter_id' => $item -> field_field_counter_id[0]['raw']['value']);
        }
    }
    
    
    // json of counter for charging 
    $viewResult = views_get_view_result('list_treenodecounter', 'panel_pane_9', $product->nid);
    
    $chargingCounters = array();
    foreach($viewResult as $item) {
    	$chargingCounter = array();
    	$chargingCounter['counter_id'] = $item->field_field_counter_id[0]['raw']['value'];
    	
    	$billingTypeName = $item->field_field_billing_type_counter[0]['rendered']['#markup'];
    	$counterSubUnitType = !empty($item->field_field_counter_sub_unit_type)? $item->field_field_counter_sub_unit_type[0]['rendered']['#markup']: null;
    	$conversionUnit = !empty($item->field_field_counter_sub_unit_type[0]['raw']['taxonomy_term']->field_converting_rule['und'])?
    				$item->field_field_counter_sub_unit_type[0]['raw']['taxonomy_term']->field_converting_rule['und'][0]['value']: null;
    				
		$limitAmount = null;
    	if($billingTypeName == 'Prepaid') {
    		$limitAmount = !empty($item->field_field_amount_corresponding) ? $item->field_field_amount_corresponding[0]['raw']['value']: null;
    		
    	} else {
    		$unlimitedOption = ($item->field_field_unlimited_threshold[0]['raw']['value'] == 1)? 'unlimited': 'limited';
    		$limitAmount = !empty($item->field_field_threshold_limit_amount) ? $item->field_field_threshold_limit_amount[0]['raw']['value']: null;
    	}
    	
    	$chargingCounter['amount_to_action'] = isset($limitAmount)? $limitAmount * $conversionUnit: null;
    	
    	$actions = array();
    	if( isset($limitAmount) ){
    		$actionResults = views_get_view_result('list_actionsetonthreshold', 'panel_pane_2', $item->nid);
    		
    		foreach($actionResults as $actionItem) {
    			$action = array();
    			$action['action'] = $actionItem->field_field_threshold_action_wo_block[0]['rendered']['#markup'];
				$action['parameters']['orig'] = !empty($actionItem->field_field_message_orig)? $actionItem->field_field_message_orig[0]['raw']['value']: null;
				$action['parameters']['dest'] = !empty($actionItem->field_field_message_dest)? $actionItem->field_field_message_dest[0]['raw']['taxonomy_term']->name:null;
				$action['parameters']['message'] = !empty($actionItem->field_field_ref_messages)? $actionItem->field_field_ref_messages[0]['raw']['nid']: null;
				
				$actions[] = $action;
    		}
    	}
    	if(!empty($actions) ) {
			$chargingCounter['actions'] = $actions;
    	}
    	
    	$chargingCounters[] = $chargingCounter;
    }
    
    $counters['optional_counters'] = $optionalCounters;
    $counters['charging_counters'] = $chargingCounters;
    
    return $counters;
}

function _get_thresdhold_scheme($product) {

    $scheme = array();
    //threshold scheme
    $view = views_get_view('list_thresholdscheme');
    $view -> set_display('panel_pane_3');
    $view -> set_arguments(array('0' => $product -> nid));
    $view -> execute();
    if (!empty($view -> result)) {
        $schemeNode = node_load($view -> result[0] -> nid);
        $scheme['threshold_scheme_id'] = $schemeNode -> field_ref_thresholdscheme['und'][0]['nid'];
    } else {
        $scheme = NULL;
    }
    return $scheme;
}

function _get_recurring_amount($productNid, $recurringSchemes) {
    $retArray = array();
    $recurringCharges = array();
    $defaultBillTypes = array();
    
    $recurring_period_type = array( '1' => 'Daily', '3' => '1/3 Monthly', '4' => 'Monthly');
    
    $view = views_get_view('list_actionpricechargerecurring');
    $view -> set_display('panel_pane_4');
    $view -> set_arguments(array('0' => $productNid));
    $view -> execute();
    
 	foreach($view->result as $chargingItem){
        $charge = array();
        $billingType = !empty($chargingItem->field_field_billing_type)? $chargingItem->field_field_billing_type[0]['rendered']['#markup']: NULL;
        $charge['amount'] = $chargingItem->field_field_price_amount_float[0]['raw']['value'];
        $charge['on'] = $chargingItem->field_field_pricing_cycle_type[0]['rendered']['#markup'];
        $defaultItems[$billingType] = $charge;
        $defaultBillTypes[] = $billingType;
    }
    
    foreach($defaultBillTypes as $billType) {
    	
    	$recurringCharge = array();
    	$recurringCharge['billing_type'] = $billType;
    	foreach($recurringSchemes['charge_scheme'] as $recurringScheme) {
    		if($recurringScheme['billing_type'] == $billType) {
    			$recurringCharge['period_type'] = $recurring_period_type[$recurringScheme['rcrr_period_type']];
    		}
    	}
    	$recurringCharge['charge_items']['default'] = $defaultItems[$billType];
    	
    	$view = views_get_view('list_actionpricechargerecurring');
	    $view -> set_display('panel_pane_3');
	    $view -> set_arguments(array('0' => $productNid));
	    $view -> execute();
	    
	    foreach($view->result as $chargingItem){
	        $charge = array();
	        $charge['amount'] = $chargingItem->field_field_price_amount_float[0]['raw']['value'];
	        $charge['on'] = $chargingItem->field_field_pricing_cycle_type[0]['rendered']['#markup'];
	        $charge['conditions'] = array();
	        
	        $conditionSets = get_children($chargingItem->nid);
	        foreach($conditionSets['children'] as $set){
	            $conditionSet = array();
	            $conditionCount = count($set['children']);
	            
	            foreach($set['children'] as $condition){
	                $conditionSet[] = $condition['data'];
	            }
	            $charge['conditions'][] = $conditionSet;
	        }
	        
	       $recurringCharge['custom'] = $charge;
	    }
	    
	    $recurringCharges[] = $recurringCharge;
	}
	
    return $recurringCharges;
}

function _get_recurring_scheme($productNid) {
    $retArray = array();
    
    $view_name = 'list_child_item_for_product';
    $display = 'panel_pane_1';
    $args = array('0' => $productNid, '1' => 'prdnonusagerecurringchargescheme');
    $records = _get_nids_from_views($view_name, $display, $args);
    $chargeScheme = node_load(current($records));
    
    $product = node_load($productNid);
    $productType = taxonomy_term_load($product->field_product_type['und'][0]['tid']);
    $productBillType = taxonomy_term_load($product->field_billing_type['und'][0]['tid']);
    
    // $charging_cycle_type = !empty($chargeScheme -> field_charging_cycle_type) ? $chargeScheme -> field_charging_cycle_type['und'][0]['value'] : NULL;
    $charge_recurring_cycle['Prepaid'] = !empty($chargeScheme -> field_recurring_cycle_pps_) ? $chargeScheme -> field_recurring_cycle_pps_['und'][0]['value'] : NULL;
    $charge_recurring_cycle['Postpaid'] = !empty($chargeScheme -> field_recurring_cycle_postpaid_) ? $chargeScheme -> field_recurring_cycle_postpaid_['und'][0]['value'] : NULL;
    
    if($charge_recurring_cycle['Prepaid'] == NULL && $charge_recurring_cycle['Postpaid'] == NULL ) {
    	$retArray['charge_scheme'] = NULL;
    } else {
    
    	switch($productType->name) {
	    	case 'CUG':
		    	foreach($charge_recurring_cycle as $key=>$value) {
			        if (!empty($value)) {
				        $retArray['charge_scheme'][] = array('billing_type'=> $key, 'rcrr_period_type' => $value);
				    }
			    }
			    break;
			default:
				$retArray['charge_scheme'][] = array('billing_type' => $productBillType->name, 'rcrr_period_type' => $charge_recurring_cycle[$productBillType->name]);
				break;
		}
    }
    
    $args[1] = 'prdnonusagerecurringbonusscheme';
    $records = _get_nids_from_views($view_name, $display, $args);
    $bonusScheme = node_load(current($records));

    $bonus_cycle_type['Prepaid'] = !empty($bonusScheme -> field_cycle_type_pps_) ? $bonusScheme -> field_cycle_type_pps_['und'][0]['value'] : NULL;
    $bonus_cycle_type['Postpaid'] = !empty($bonusScheme -> field_cycle_type_postpaid_) ? $bonusScheme -> field_cycle_type_postpaid_['und'][0]['value'] : NULL;
    
    if($bonus_cycle_type['Prepaid'] == NULL && $bonus_cycle_type['Postpaid'] == NULL ) {
        $retArray['bonus_scheme'] = NULL;
    } else {
    
    	switch($productType->name) {
	       	case 'CUG':
		       	foreach($bonus_cycle_type as $key=>$value) {
		    		if($key == 'Prepaid' && !empty($value)) {
					 	$rcrr_charging_day_arr = array('1' => NULL, '2' => !empty($bonusScheme -> field_day_of_week_pps) ? $bonusScheme -> field_day_of_week_pps['und'][0]['value'] : NULL, '3' => NULL, '4' => !empty($bonusScheme -> field_day_of_month_pps) ? $bonusScheme -> field_day_of_month_pps['und'][0]['value'] : NULL);
				        $rcrr_charging_day = $rcrr_charging_day_arr[$value];
				        $retArray['bonus_scheme'][] = array('billing_type' => $key, 'rcrr_period_type' => $value, 'rcrr_charging_day' => $rcrr_charging_day);
				        
		    		} else if ($key == 'Postpaid' && !empty($value)) {
					 	$rcrr_charging_day_arr = array('1' => NULL, '2' => !empty($bonusScheme -> field_day_of_week_postpaid) ? $bonusScheme -> field_day_of_week_postpaid['und'][0]['value'] : NULL, '3' => NULL, '4' => !empty($bonusScheme -> field_day_of_month_postpaid) ? $bonusScheme -> field_day_of_month_postpaid['und'][0]['value'] : NULL);
				
				        $rcrr_charging_day = $rcrr_charging_day_arr[$value];
				        $retArray['bonus_scheme'][] = array('billing_type' => $key, 'rcrr_period_type' => $value, 'rcrr_charging_day' => $rcrr_charging_day);
		    		}
		    	}
		    	break;
		    default:
	    		$cycle_type = $bonus_cycle_type[$productBillType->name];
		    	if($productBillType->name == 'Prepaid') {
					$rcrr_charging_day_arr = array('1' => NULL, '2' => !empty($bonusScheme -> field_day_of_week_pps) ? $bonusScheme -> field_day_of_week_pps['und'][0]['value'] : NULL, '3' => NULL, '4' => !empty($bonusScheme -> field_day_of_month_pps) ? $bonusScheme -> field_day_of_month_pps['und'][0]['value'] : NULL);
					$rcrr_charging_day = $rcrr_charging_day_arr[$cycle_type];
					$retArray['bonus_scheme'][] = array('billing_type' => $productBillType->name, 'rcrr_period_type' => $cycle_type, 'rcrr_charging_day' => $rcrr_charging_day);
		    		
				} else {
				 	$rcrr_charging_day_arr = array('1' => NULL, '2' => !empty($bonusScheme -> field_day_of_week_postpaid) ? $bonusScheme -> field_day_of_week_postpaid['und'][0]['value'] : NULL, '3' => NULL, '4' => !empty($bonusScheme -> field_day_of_month_postpaid) ? $bonusScheme -> field_day_of_month_postpaid['und'][0]['value'] : NULL);
			
			        $rcrr_charging_day = $rcrr_charging_day_arr[$cycle_type];
			        $retArray['bonus_scheme'][] = array('billing_type' => $productBillType->name, 'rcrr_period_type' => $cycle_type, 'rcrr_charging_day' => $rcrr_charging_day);
				}
				break;
		}
    }

    return $retArray;
}

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
    if (!empty($term)) {
        $args[] =  current($term) -> tid;
    }

    $req_labels = array('lifecyclescheme_id' => 'Nid', );
    $records = _get_records_from_views_by_label($view_name, $display, $args, $req_labels);

    if (!empty($records)) {
        $schemeNode = node_load($records[0]['lifecyclescheme_id']);
        return $schemeNode -> field_lifecycle_scheme['und'][0]['nid'];
    } else {
        return NULL;
    }

}

function _get_recurring_bonus($productNid) {

}

function _get_onetime_charge($productNid) {
    $view = views_get_view('list_other_onetime_charge_by_product_id');
    $view -> set_display('panel_pane_1');
    $view -> set_arguments(array('0' => $productNid));
    $view -> execute();
    $charges = array();

    foreach ($view->result as $item) {
        $onetimeChargeTerm = taxonomy_term_load($item -> taxonomy_term_data_field_data_field_ref_otherontimecharge_ti);
        $onetimeChargeNode = node_load($item -> nid);
        $chargeType = _get_common_code($onetimeChargeTerm);
				
        if (isset($onetimeChargeNode -> field_price_amount_decimal['und'][0]['value'])) {
            $price = $onetimeChargeNode -> field_price_amount_decimal['und'][0]['value'];
        } else {
            $price = NULL;
        }
        $charge = array('charge_type' => $chargeType, 'price' => $price);
        
        $attribute = array();
        foreach($item->field_field_attribute_key_value as $fieldCollectionItem) {
        	$renderedItem = current($fieldCollectionItem['rendered']['entity']['field_collection_item']);
        	$key = $renderedItem['field_ref_productattributekey']['#object']->field_ref_productattributekey['und'][0]['taxonomy_term']->name;
        	$commonCode = $renderedItem['field_ref_productattributekey']['#object']->field_ref_productattributekey['und'][0]['taxonomy_term']->field_common_code['und'][0]['value'];
        	$value = $renderedItem['field_ref_productattributekey']['#object']->field_attribute_value['und'][0]['value'];
        	$attribute[] = array('key' => 
        								array('codeGroup' => 'ProductAttributeKey', 'code' => $commonCode, 'meaning' => $key),
        						'value' => $value
        						);
        }
        $charge['attribute'] = $attribute;
        $charges[] = $charge;
    }
    return $charges;
}

function _get_onetime_charge_discount($productNid) {
    $view = views_get_view('list_other_onetime_charge_discount');
    $view -> set_display('panel_pane_2');
    $view -> set_arguments(array('0' => $productNid));
    $view -> execute();
    $charges = array();

    foreach ($view->result as $item) {
        $onetimeChargeTerm = taxonomy_term_load($item -> taxonomy_term_data_field_data_field_ref_otherontimecharge_ti);
        $onetimeChargeNode = node_load($item -> nid);
        $chargeType = _get_common_code($onetimeChargeTerm);

        // Discont by Amount Flag , 1 = Discount by Amount, 0 = Discount by Percentage
        if ($item -> field_field_discount_by_amount_flag[0]['raw']['value'] == 1) {
            $term = current(taxonomy_get_term_by_name('Amount', 'discounttype'));
            $discountRate = $item -> field_field_discount_amount[0]['raw']['value'];

        } else {
            $term = current(taxonomy_get_term_by_name('Percentage', 'discounttype'));
            $discountRate = $item -> field_field_discount_percentage[0]['raw']['value'];
        }
        $discountType = _get_common_code($term);

        $charge = array('charge_type' => $chargeType, 'discount_type' => $discountType, 'discount_rate' => $discountRate,
        // 'price' => $price
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
                      "product_id" => array("through_common_code" => FALSE, "field" => "field_product_id", "field_value" => "field_product_id['und'][0]['value']", "field_default" => NULL), 
                      "short_code" => array("through_common_code" => FALSE, "field" => "field_short_code", "field_value" => "field_short_code['und'][0]['value']", "field_default" => NULL), 
                      "product_name" => array("through_common_code" => FALSE, "field" => "title", "field_value" => "title", "field_value_default" => ""), 
                      'deferred_changing' => array('through_common_code' => FALSE, 'field' => 'field_field_deferred_subscriptio', 'field_value' => "field_field_deferred_subscriptio['und'][0]['value']", 'field_value_default' => '0'), 
                      'description' => array('through_common_code' => FALSE, 'field' => 'field_description', 'field_value' => "field_description['und'][0]['safe_value']", 'field_value_default' => NULL), 
                      'billing_cycle' => array('through_common_code' => FALSE, 'field' => 'field_billing_cycle', 'field_value' => "field_billing_cycle['und'][0]['value']", 'field_value_default' => NULL), 
                      'bill_type' => array('through_common_code' => TRUE, 'field' => 'field_billing_type', 'field_value' => "field_billing_type['und'][0]['tid']", 'field_value_default' => NULL), 
                      'product_type' => array('through_common_code' => TRUE, 'field' => 'field_product_type', 'field_value' => "field_product_type['und'][0]['tid']", 'field_value_default' => NULL), 
                      'product_sub_type' => array('through_common_code' => TRUE, 'field' => 'field_product_sub_type', 'field_value' => "field_product_sub_type['und'][0]['tid']", 'field_value_default' => NULL), 
                      'product_detail_type' => array('through_common_code' => TRUE, 'field' => 'field_product_detail_type', 'field_value' => "field_product_detail_type['und'][0]['tid']", 'field_value_default' => NULL), 
                      'service_domain' => array('through_common_code' => TRUE, 'field' => 'field_service_type_of_provider', 'field_value' => "field_service_type_of_provider['und'][0]['tid']", 'field_value_default' => NULL), 
                      'customer_type' => array('through_common_code' => TRUE, 'field' => 'field_custdvcd4prod', 'field_value' => "field_custdvcd4prod['und'][0]['tid']", 'field_value_default' => NULL), 
                      'customer_group_type' => array('through_common_code' => TRUE, 'field' => 'field_customer_group_type', 'field_value' => "field_customer_group_type['und'][0]['tid']", 'field_value_default' => NULL), 
                      'cug_member_counter' => array('through_common_code' => FALSE, 'field' => 'field_cug_member_counter', 'field_value' => "field_cug_member_counter['und'][0]['value']", 'field_value_default' => NULL, ), 
                      'cug_group_type' => array('through_common_code' => TRUE, 'field' => 'field_cug_group_type', 'field_value' => "field_cug_group_type['und'][0]['tid']", 'field_value_default' => NULL, ), 
                      'cug_customer_type' => array('through_common_code' => TRUE, 'field' => 'field_cug_customer_type', 'field_value' => "field_cug_customer_type['und'][0]['tid']", 'field_value_default' => NULL, ), 
                      'cug_need_member_product' => array('through_common_code' => FALSE, 'field' => 'field_cug_need_member_product', 'field_value' => "field_cug_need_member_product['und'][0]['value']", 'field_value_default' => NULL, ), 
                      'treatment_day' => array('through_common_code' => FALSE, 'field' => 'field_treatment_day', 'field_value' => "field_treatment_day['und'][0]['value']", 'field_value_default' => NULL), 
                      'treatment_price' => array('through_common_code' => FALSE, 'field' => 'field_treatment_price_amount', 'field_value' => "field_treatment_price_amount['und'][0]['value']", 'field_value_default' => 0), 
                      'field_point_for_subscription' => array('through_common_code' => FALSE, 'field' => 'field_point_for_subscription', 'field_value' => "field_point_for_subscription['und'][0]['value']", 'field_value_default' => 0), 
                      'contract_period' => array('through_common_code' => FALSE, 'field' => 'field_contract_period‎', 'field_value' => "field_contract_period‎['und'][0]['value']", 'field_value_default' => 0),
//                      'expire_date' => array('through_common_code' => FALSE, 'field' => 'field_expire_date', 'field_value' => "field_expire_date['und'][0]['value']", 'field_value_default' => 0), 
                      'weight_for_priority' => array('through_common_code' => FALSE, 'field' => 'field_weight_for_ratingpriority', 'field_value' => "field_weight_for_ratingpriority['und'][0]['value']", 'field_value_default' => 0),
                      'expire_date_type' => array('through_common_code' => TRUE, 'field' => 'field_expire_date_type', 'field_value' => "field_expire_date_type['und'][0]['tid']", 'field_value_default' => NULL), 
                      'resubscription_flag' => array('through_common_code' => FALSE, 'field' => 'field_resubscription_flag', 'field_value' => "field_resubscription_flag['und'][0]['value']", 'field_value_default' => 0), 
                      'currency' => array('through_common_code' => TRUE, 'field' => 'field_price_units', 'field_value' => "field_price_units['und'][0]['tid']", 'field_value_default' => NULL), 
                );

    $result_attribute_general = _get_result($reqArray, $product);
    $result_attrbitue_exception = _get_attribute_exceptions($product);
    
    //$result_attribute_exception = null;

    $result = array_merge($result_attribute_general, $result_attrbitue_exception);

    return $result;
}

function _get_result($reqArray, $product) {
    $retArray = array();
    foreach ($reqArray as $key => $item) {
        if ($item['through_common_code']) {
            $command = '$field = isset($product->' . $item['field'] . ')?$product->' . $item['field'] . ':0' . ';';
            eval($command);

            if (!empty($field)) {
                $command = '$tempTerm = taxonomy_term_load($product->' . $item['field_value'] . ');';
                eval($command);
                $retItem = _get_common_code($tempTerm);
            } else {
                $retItem = $item['field_value_default'];
            }

        } else {
            //$command = '$field = $product->'.$item['field'].';';
            $command = '$field = isset($product->' . $item['field'] . ')? $product->' . $item['field'] . ' :0' . ';';
            eval($command);

            // Exception for Contract Period
            if ($key == 'contract_period') {
                $field = isset($product -> field_contract_period) ? $product -> field_contract_period : 0;

                if (!empty($field)) {
                    $retItem = $product -> field_contract_period['und'][0]['value'];
                } else {
                    $retItem = $item['field_value_default'];
                }

            } else {
                if (!empty($field)) {

                    $command = '$retItem = $product->' . $item['field_value'] . ';';
                    eval($command);

                } else {
                    $retItem = $item['field_value_default'];
                }
            }
        }
        $retArray[$key] = $retItem;
    }
    return $retArray;
}

function _get_attribute_exceptions($product) {

    $retArray = array();
    
    $validStart = isset($product -> field_validfor_product['und'][0]['value']) ? $product -> field_validfor_product['und'][0]['value'] : '2013-01-01 00:00:00';

    $validEnd = isset($product -> field_validfor_product['und'][0]['value2']) ? $product -> field_validfor_product['und'][0]['value2'] : '2013-01-01 00:00:00';
    
    if ($validStart === $validEnd) {
    	$validEnd = '9999-12-31 23:59:59';
    } else {
        if (!empty($product -> field_validfor_product)) {
            $tempArr = explode(' ', $product -> field_validfor_product['und'][0]['value2']);
            // $validEnd = $tempArr[0] . ' 23:59:59';
            $validEnd = $tempArr[0] . ' ' . $tempArr[1];
        } else {
            $validEnd = '9999-12-31 23:59:59';
        }
    }
    
    $validForStr = $validStart . ' ~ ' . $validEnd;

    $retArray['valid_for'] = $validForStr;

    if (!empty($product -> field_parent_node_for_rp['und'][0]['nid'])) {
        $parentNode = node_load($product -> field_parent_node_for_rp['und'][0]['nid']);
        $retArray['parent_product_id'] = $parentNode -> field_product_id['und'][0]['safe_value'];
    } else {
        $retArray['parent_product_id'] = NULL;
    }

    $view = views_get_view('list_product_child_node');
    $view -> set_display('panel_pane_2');
    $view -> set_arguments(array('0' => $product -> nid, '1' => 'prdattributeprefixrangeallowed'));
    $view -> execute();
    
    if (count($view -> result) > 0) {
        $allowedPrefixNode = node_load(current($view -> result) -> nid);
        
        $allowedPrefix = array();
        if(isset($allowedPrefixNode->field_prefix_range['und'])){
            foreach($allowedPrefixNode->field_prefix_range['und'] as $item){
	            $rangeCollection = field_collection_item_load($item['value']);
	            
	            $base = $rangeCollection->field_base_prefix['und'][0]['value'];
	            $start = $rangeCollection->field_prefix_range_start['und'][0]['value'];
	            $end = $rangeCollection->field_prefix_range_end['und'][0]['value'];
	            
        		$allowedPrefix[] = array(
        		    'base_prefix' => $base,
        		    'range_start' => $start,
        		    'range_end' => $end
        		);
        	}
           $retArray['prefix_allowed'] = $allowedPrefix;
        }
    }

    $operator = array();
    foreach ($product->field_service_operator['und'] as $item) {
        $operatorTerm = taxonomy_term_load($item['tid']);
        $operator[] = _get_common_code($operatorTerm);
    }
    $retArray['service_operator'] = $operator;

    $view = views_get_view('list_product_child_node');
    $view -> set_display('panel_pane_2');
    $view -> set_arguments(array('0' => $product -> nid, '1' => 'prdattributefeaturecode'));
    $view -> execute();
    if (count($view -> result) > 0) {
        $serviceFeatureCodes = array();
        foreach ($view->result as $item) {
            $prdFeatureCodeNode = node_load($item -> nid);
            $featureTerm = taxonomy_term_load($prdFeatureCodeNode -> field_ref_service_feature_code['und'][0]['tid']);
            $serviceFeatureCodes[] = _get_common_code($featureTerm);
        }
        $retArray['service_feature_code'] = $serviceFeatureCodes;
    }
    $view = views_get_view('list_product_child_node');
    $view -> set_display('panel_pane_2');
    $view -> set_arguments(array('0' => $product -> nid, '1' => 'prdattributebenefit'));
    $view -> execute();
    $benefit = array();

    if (!empty($view -> result)) {
        $benefitNode = node_load(current($view -> result) -> nid);
        if (!empty($benefitNode -> field_attribute_discount['und'][0]['safe_value'])) {
            $benefit['discount'] = $benefitNode -> field_attribute_discount['und'][0]['safe_value'];
        } else {
            $benefit['discount'] = NULL;
        }
        if (!empty($benefitNode -> field_attribute_bonus['und'][0]['safe_value'])) {
            $benefit['bonus'] = $benefitNode -> field_attribute_bonus['und'][0]['safe_value'];
        } else {
            $benefit['bonus'] = NULL;
        }
				if (!empty($benefitNode -> field_recommend_vas['und'][0]['safe_value'])) {
            $benefit['recommend_vas'] = $benefitNode -> field_recommend_vas['und'][0]['safe_value'];
        } else {
            $benefit['recommend_vas'] = NULL;
        }
				
        $retArray['benefit'] = $benefit;
    }

    // subscriber's lifecycle scheme과 연결
    $retArray['lifecyclescheme'] = _get_lifecyclescheme($product -> nid);

    //required device
    $view = views_get_view('list_product_child_node');
    $view -> set_display('panel_pane_2');
    $view -> set_arguments(array('0' => $product -> nid, '1' => 'prdattributerequireddevice'));
    $view -> execute();
    $requiredDevice = array();

    if (!empty($view -> result)) {
        foreach ($view->result as $record) {
            $requiredDeviceNode = node_load($record -> nid);
            $requiredDeviceInfo = array();
            $deviceClassTerm = taxonomy_term_load($requiredDeviceNode -> field_ref_device_class['und'][0]['tid']);
            $requiredDeviceInfo['device'] = _get_common_code($deviceClassTerm);
            if(isset($requiredDeviceNode->field_required_device['und'])){
                $amount = array();
                foreach($requiredDeviceNode->field_required_device['und'] as $item){
                    $collectionInfo = field_collection_item_load($item['value']);
                    $amount[] = array(
                        'amount' => $collectionInfo->field_amount['und'][0]['value'],
                        'price' => $collectionInfo->field_deposit_price['und'][0]['value']
                    );
                }
                $requiredDeviceInfo['deposit'] = $amount;
            }
            $requiredDevice[] = $requiredDeviceInfo;
        }
        $retArray['required_device'] = $requiredDevice;
    }

    //number saving
    $view = views_get_view('list_product_child_node');
    $view -> set_display('panel_pane_2');
    $view -> set_arguments(array('0' => $product -> nid, '1' => 'prdattributenumbersaving'));
    $view -> execute();
    $numberSavings = array();

    if (!empty($view -> result)) {
        $retArray['number_saving'] = null;
		foreach ($view->result as $record) {
			$serviceSavingNode = node_load($record->nid);
			$serviceSavingInfo = array();
			$serviceSavingInfo['saving_fee'] = isset($serviceSavingNode -> field_price['und'][0]['value']) ? $serviceSavingNode -> field_price['und'][0]['value'] : 0;
			$serviceSavingInfo['minimum_period'] = isset($serviceSavingNode -> field_minimum_period['und'][0]['value'])? $serviceSavingNode -> field_minimum_period['und'][0]['value'] : 0;
			$serviceSavingInfo['free_month'] = isset($serviceSavingNode -> field_free_of_charge_month['und'][0]['value'])? $serviceSavingNode -> field_free_of_charge_month['und'][0]['value'] : 0;
			$serviceSavingInfo['maximum_period'] = isset($serviceSavingNode -> field_maximum_period_1st_['und'][0]['value'])? $serviceSavingNode -> field_maximum_period_1st_['und'][0]['value'] : 0;
			$serviceSavingInfo['maximum_extend_period'] = isset($serviceSavingNode -> field_maximum_period_2nd_['und'][0]['value'])? $serviceSavingNode -> field_maximum_period_2nd_['und'][0]['value'] : 0;
			$serviceSavingInfo['using_condition'] = isset($serviceSavingNode -> field_using_condition['und'][0]['value'])? $serviceSavingNode -> field_using_condition['und'][0]['value'] : 0;
		}
		$retArray['service_saving'] = empty($serviceSavingInfo)? NULL: $serviceSavingInfo;        
    }
    
    //allowed device
    $view = views_get_view('list_product_child_node');
    $view -> set_display('panel_pane_2');
    $view -> set_arguments(array('0' => $product -> nid, '1' => 'prdattributeallowedmodel'));
    $view -> execute();
    $allowedDevice = array();

    if (!empty($view -> result)) {
        foreach ($view->result as $record) {
            $allowedDeviceNode = node_load($record -> nid);
            $deviceModelNode = node_load($allowedDeviceNode -> field_ref_device_model['und'][0]['nid']);
            $allowedDevice[] = array('device_name' => $deviceModelNode -> name, 'device_code' => $deviceModelNode -> field_model_code['und'][0]['safe_value'], 'device_class_name' => $deviceModelNode -> field_model_class['und'][0]['safe_value'], 'device_class_code' => $deviceModelNode -> field_model_class_code['und'][0]['safe_value']);
        }
        $retArray['allowed_device'] = $allowedDevice;
    }
    
    //available Channel
    $view = views_get_view('list_product_child_node');
    $view -> set_display('panel_pane_2');
    $view -> set_arguments(array('0' => $product -> nid, '1' => 'prdattributeavailablechannel'));
    $view -> execute();
    
    $availableChannel = array();

    if (!empty($view -> result)) {
        foreach ($view->result as $record) {
        	$availableChannelNode = node_load($record -> nid);
        	if(!empty($availableChanneNode)) {
	        	foreach( $availableChannelNode->field_ref_tvchannel['und'] as $item) {
	        		$channel = node_load($item['nid']);
	        		$availableChannel[] = array('channel_name' => $channel->title);
	        	}
	        }
        }
        $retArray['available_channel'] = !empty($availableChannel)? $availableChannel: NULL;
    }
    
    $expireDateTypeTerm = isset($product->field_expire_date_type['und'][0]['tid']) ? taxonomy_term_load($product->field_expire_date_type['und'][0]['tid']) : NULL;
    
    if(!empty($expireDateTypeTerm)) {
    
    	switch($expireDateTypeTerm->field_common_code['und'][0]['value']) {
    		case '3': //Hour
    			$retArray['expire_date'] = isset($product->field_expire_date['und'][0]['value'])? $product->field_expire_date['und'][0]['value']: NULL;
				break;
    		case '1': //Day
    		case '2': //Month
    			$retArray['expire_date'] = isset($product->field_expire_date['und'][0]['value'])? $product->field_expire_date['und'][0]['value']: NULL;
    			$retArray['expire_date_hour'] = isset($product->field_valid_date_hour['und'][0]['value'])? $product->field_valid_date_hour['und'][0]['value'].":00": NULL;
    			break;
    		case '5': //End of This Week
    		case '6': //End of This Month
    			break;
    		case '4': //SpecificDate
    			$specificHour = $product->field_valid_date_hour['und'][0]['value'].":00:00";
    			$tmpDates = explode(' ', $product->field_specific_date['und'][0]['value']);
					$specificDate = $tmpDates[0].' '.$specificHour;
    			$retArray['expire_date'] = $specificDate;
					//2013-05-12 16:00:00
    			break;
    	}
    	
    	$nextJoinConfirmTerm = isset($product->field_next_join_confirm['und'][0]['tid'])? taxonomy_term_load($product->field_next_join_confirm['und'][0]['tid']) : NULL;
    	
    	if( isset($nextJoinConfirmTerm) ) {
			$retArray['next_join_confirm'] = ($nextJoinConfirmTerm->name == 'REQUIRED')? 1: 0;
			
			if(!empty($product->field_next_join_product)
		    	&& !empty($product->field_next_join_product['und']) 
		    	&& !empty($product->field_next_join_product['und'][0])
		    	&& !empty($product->field_next_join_product['und'][0]['nid'])
		    	
		     ) {
		     	$nextJoinProduct = node_load($product->field_next_join_product['und'][0]['nid']);
				$retArray['next_join_product'] = $nextJoinProduct->field_product_id['und'][0]['value'];
		    }
			    
		} else {
			$retArray['next_join_confirm'] = NULL;
			$retArray['next_join_product'] = NULL;
		}
		    
	} else {
		$retArray['next_join_product'] = NULL;
		$retArray['next_join_confirm'] = NULL;
		$retArray['expire_date'] = NULL;
	}
	
	// VAS이면서, PostPaid, Hybrid일 경우에 deposit condition을 적용.
	$productTypeTerm = taxonomy_term_load($product->field_product_type['und'][0]['tid']);
	$billingTypeTerm = taxonomy_term_load($product->field_billing_type['und'][0]['tid']);
	if( ($productTypeTerm->name == 'VAS')
		&& ( ($billingTypeTerm->name == 'Postpaid') || ($billingTypeTerm->name == 'Hybrid')) ) {
		
		$viewResult = views_get_view_result('list_prdattributedepositcondition', 'panel_pane_1', $product->nid);
		$temp = current($viewResult);
		$prdAttributeDepositCondition = node_load($temp->nid);
		
		$conditionLists = array();
		$depositGroupCodeTerm = taxonomy_term_load($prdAttributeDepositCondition->field_deposit_group_code['und'][0]['tid']);
		$minimumDeposit = $prdAttributeDepositCondition->field_minimum_deposit['und'][0]['value'];
		$conditionLists['default']['deposit_group_code'] = _get_common_code($depositGroupCodeTerm);
		$conditionLists['default']['minimum_deposit'] = $minimumDeposit;
		
		$preRequisiteConditions = array();
		
		$viewResult = views_get_view_result('list_actiondepositcondition', 'panel_pane_2', $prdAttributeDepositCondition->nid);
		foreach($viewResult as $item) {
			$depositCondition = array();
			$productId = $item->field_field_product_id[0]['raw']['value'];
			$groupCode = _get_common_code($item->field_field_deposit_group_code[0]['raw']['taxonomy_term']);
			$minimumDeposit = $item->field_field_minimum_deposit[0]['raw']['value'];

			$preRequisiteConditions[]= array($productId => array('deposit_group_code' => $groupCode, 'minimum_deposit' => $minimumDeposit));
		}
		$conditionLists['custom'] = $preRequisiteConditions;
		$retArray['prerequisite_deposit_condition'] = $conditionLists;
		
	} else {
		$retArray['prerequisite_deposit_condition'] = NULL;
	}
	
    return $retArray;
}

function _get_common_code($term) {
    $data = array();

    $voca = taxonomy_vocabulary_machine_name_load($term -> vocabulary_machine_name);
    $data['codeGroup'] = $voca -> name;
    $data['code'] = isset($term -> field_common_code['und'][0]['safe_value']) ? $term -> field_common_code['und'][0]['safe_value'] : $term -> name;
    $data['meaning'] = $term -> name;
    return $data;
}

function _get_group_bonus( $nid) 
{
	$data = array( 'adm_message' => null);

	$nids = ocs_get_nids_by_cond( 'prdnonusagegroupbonusblock', array(
				array('field_ref_product', 'nid', $nid),
				// TODO : check tree_tid ?
//				array('field_ref_tree_tid', 'value', $nid),
				));

	if ( empty( $nids)) {
		return $data;
	}

	$attr = node_load( $nids[0]);
	$data['adm_message'] = array( 'message_id' => $attr->field_ref_messages['und'][0]['nid']);

	return $data;
}
