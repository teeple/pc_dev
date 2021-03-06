<?php

function product_priority_form_submit($form, &$form_state) {
  $values = $form_state['values']; //All form values
  
  $weight_values = array();
	
	foreach($values['products'] as $product){
		$weight_values[$product['weight']][] = $product['id'];
	}
	ksort($weight_values);
	
	$weight = 0;
	foreach($weight_values as $same_weight_products){
		foreach($same_weight_products as $product_id){
			$result = db_select("field_data_field_weight_for_ratingpriority","r")->fields("r",array("entity_id"))->condition("entity_id",$product_id,"=")->execute()->fetchAssoc();
							 
	    if(!empty($result)){
	    	//db_query("UPDATE {field_data_field_weight_for_ratingpriority} SET field_weight_for_ratingpriority_value = :weight  WHERE entity_id = :id"
	    	//, array(':weight' => $product['weight'], ':id' =>$product['id']));
	    	db_update('field_data_field_weight_for_ratingpriority')
		    ->expression('field_weight_for_ratingpriority_value', ':weight', array(':weight' => $weight))
		    ->condition('entity_id', $product_id)
		    ->execute();
	    }else{
	    	$node = node_load($product_id);
	  	  $node->field_weight_for_ratingpriority['und'][0]['value'] = $weight;
	      node_save($node);
	    }
			$weight++;
		}
	}
	/*
	foreach($weight_values as $weight => $nid){
		$result = db_select("field_data_field_weight_for_ratingpriority","r")->fields("r",array("entity_id"))->condition("entity_id",$nid,"=")->execute()->fetchAssoc();
						 
    if(!empty($result)){
    	//db_query("UPDATE {field_data_field_weight_for_ratingpriority} SET field_weight_for_ratingpriority_value = :weight  WHERE entity_id = :id"
    	//, array(':weight' => $product['weight'], ':id' =>$product['id']));
    	db_update('field_data_field_weight_for_ratingpriority')
	    ->expression('field_weight_for_ratingpriority_value', ':weight', array(':weight' => $weight))
	    ->condition('entity_id', $nid)
	    ->execute();
    }else{
    	$node = node_load($nid);
  	  $node->field_weight_for_ratingpriority['und'][0]['value'] = $weight;
      node_save($node);
    }
	}
	*/
	drupal_goto(current_path(), array('fragment' => 'quickset-relation_manager=4'));
}

function _clone_object_handler($form){
	product_catalog_ajax_clone_object($form['#node']->nid);
}

function node_save_handler_to_touch_product($node) {
	if (session_get('TOUCH_PRODUCT', TRUE)) {
		$productNode = find_parent_product($node);
		if ($productNode != NULL) {
			_touch_product($productNode -> nid);
		}
	}
};

function product_catalog_form_node_submit($node, $form, &$form_state) {
	global $user;
	global $base_url;

	$form_id = $form['form_id']['#value'];

	switch($form_id) {
		case 'ocs_ussd_code_node_form':
			if ($form_state['values']['op'] == 'Save') {
				node_save($node);
				$path = 'config/ocs/ussd/'.$node->nid;
				$options = array();
				$options['fragment'] = 'quickset-ocs_quick_tab=2';
				unset($_GET['destination']);
				drupal_goto($path, $options);
			}
			break;
		case 'prodoffernonusagesubitem_node_form' :
		case 'actionpricefactors_node_form' :
			$node -> uid = $user -> uid;
			break;
		case 'actionpricechargerecurring_node_form' :
		case 'actionpricechargerecurringdefaul_node_form' :
			if (empty($form_state['values']['nid'])) {
				$product = node_load($form_state['root_nid']);

				/*
				 $form_state['values']['field_recurring_charge_id']['und'][0]['value'] = '_' . $form_state['values']['field_price_amount_float']['und'][0]['value'];

				 $node->field_recurring_charge_id['und'][0]['value'] = $product->field_product_id['und'][0]['value'] . '_' . $form_state['values']['field_price_amount_float']['und'][0]['value'];
				 node_save($node);
				 */

			}
			break;
		case 'vouchercardtype_node_form' :
			if ($form_state['values']['field_valid_date_ymd_w_enddate']['und'][0]['show_todate'] == 0) {
				$validEnd = "9999-12-31 23:59:59";
				$node -> field_valid_date_ymd_w_enddate['und'][0]['value2'] = $validEnd;
				node_save($node);
			}
			break;
	}
}

function timetable_submit_handler(&$form, &$form_state) {
	global $user;

	//create timetablefactorsslot
	$timetableNid = $form_state['values']['nid'];

	$totalDays = 8;
	//Holiday, mon, tue, wed, thu, fri, sat, sun
	$totalHours = 24;

	for ($i = 0; $i < $totalDays; $i++) {
		for ($j = 0; $j < $totalHours; $j++) {
			$node = new StdClass();
			$node -> type = 'timetablefactorsslot';
			$node -> language = 'und';
			$node -> uid = $user -> uid;
			$node -> field_day_of_week['und'][0]['value'] = $i;
			$node -> field_hour_slot['und'][0]['value'] = $j;
			$node -> field_ref_timetable['und'][0]['nid'] = $timetableNid;
			node_save($node);
		}
	}
}

function _offering_submit_characteristic_handler(&$form, &$form_state, &$spec_characters, &$productSpecification) {
	global $user;

	// attached valueuse delete (field_r_prodspeccharvalueuse)
	//
	if (isset($form['#node'] -> field_r_prodspeccharvalueuse)) {
		$valueUseList = $form['#node'] -> field_r_prodspeccharvalueuse['und'];
		$valueUseNidList = array();
		foreach ($valueUseList as $value) {
			$valueUseNidList[] = $value['nid'];
		}
		node_delete_multiple($valueUseNidList);
	}

	// product characteristic value use 저장
	//
	$characteristics = $form_state['values']['characteristic'];

	foreach ($characteristics as $char) {
		$ref_value = array();

		// valueuse save
		//
		$charUseSaveFlag = TRUE;

		if (!empty($form_state['values'][$char['title']])) {
			switch($char['type']) {
				case 'textarea' :
					$ref_value[] = $form_state['values'][$char['title']];
					$charUseSaveFlag = FALSE;
					break;
				case 'checkboxes' :
					$ref_value = array_values(array_diff($form_state['values'][$char['title']], array(0)));

					break;
				case 'select' :
					$ref_value[] = $form_state['values'][$char['title']];
					break;
			}

			// in case charuse save is needed
			//
			$charuse = new StdClass();

			if ($charUseSaveFlag) {

				$charuse -> title = $char['title'];
				$charuse -> type = 'productspeccharuse';
				$charuse -> language = 'und';
				$charuse -> field_r_productspecchar['und'][0]['nid'] = $char['nid'];
				$charuse -> uid = $user -> uid;
				node_save($charuse);
				$spec_characters['charuse'][] = array('nid' => $charuse -> nid);
			}

			foreach ($ref_value as $use) {
				$valueuse = new StdClass();
				$valueuse -> title = $char['title'];
				$valueuse -> type = 'prodspeccharvalueuse';
				$valueuse -> language = 'und';
				$valueuse -> uid = $user -> uid;

				if (isset($charuse -> nid)) {
					$valueuse -> field_r_productspeccharuse['und'][0]['nid'] = $charuse -> nid;
					$valueuse -> field_r_prodspeccharvalue['und'][0]['nid'] = $use;
				} else {
					$valueuse -> field_custom_value['und'][0]['value'] = $use;
					$valueuse -> field_custom_value['und'][0]['format'] = NULL;
					$valueuse -> field_custom_value['und'][0]['safe_value'] = $use;
				}
				$valueuse -> field_r_productspecchar['und'][0]['nid'] = $char['nid'];

				node_save($valueuse);
				$spec_characters['valueuse'][] = array('nid' => $valueuse -> nid);
			}
		}

	}

	// product specification 저장
	//
	if (!isset($form['nid']['#value'])) {//create
		$productSpecification = new StdClass();
	} else {
		$productSpecification = node_load($form['#node'] -> field_r_productspecification['und'][0]['nid']);
		$charUseList = $productSpecification -> field_r_productspeccharuse['und'];
		$charUseNidList = array();
		foreach ($charUseList as $value) {
			$charUseNidList[] = $value['nid'];
		}
		node_delete_multiple($charUseNidList);
	}

	$productSpecification -> uid = $user -> uid;
	$productSpecification -> type = 'atomicproductspecification';
	$productSpecification -> title = isset($form_state['values']['title']) ? $form_state['values']['title'] : '';
	$productSpecification -> language = 'und';
	$productSpecification -> field_description = $form_state['values']['field_description'];

	$productSpecification -> field_valid_for['und'][0]['value'] = $form_state['values']['field_valid_for'];
	$productSpecification -> field_valid_for['und'][0]['value2'] = $form_state['values']['field_valid_for_2'];
	$productSpecification -> field_valid_for['und'][0]['timezone'] = date_default_timezone_get();
	$productSpecification -> field_valid_for['und'][0]['timezone_db'] = 'UTC';
	$productSpecification -> field_valid_for['und'][0]['date_type'] = 'datetime';

	$productSpecification -> field_product_number = $form_state['values']['field_id'];
	$productSpecification -> field_r_productspeccharuse['und'] = $spec_characters['charuse'];
	node_save($productSpecification);

}

function _node_save_handler_for_add_js_settings_after_node_save(&$form, &$form_state) {
	$rootNode = node_load($form_state['values']['nid']);
	if ($rootNode -> type == 'tariffplan') {
		$product = node_load($rootNode -> field_ref_product['und'][0]['nid']);
		$prdTypeTerm = taxonomy_term_load($product -> field_product_type['und'][0]['tid']);

		if ($prdTypeTerm -> name === 'CUG') {
			_create_default_cugdiscountfactors_in_tariffplan($rootNode);
		}
	}

	add_js_settings_after_node_save($rootNode);
}

function create_default_tree_node_submit_handler(&$form, &$form_state) {
	$rootNode = node_load($form_state['values']['nid']);

	_create_default_tree_node($form_state['voca_name'], $rootNode -> nid);

	add_js_settings_after_node_save($rootNode);
}

function _create_default_items_by_voca($product, $voca_name) {
	global $user;

	$notAllowedCombinationStr = _get_invisible_combination_string($product);
	
	$voca = taxonomy_vocabulary_machine_name_load($voca_name);
	$terms = taxonomy_get_tree($voca -> vid);
	$skipParents = array();
	$ridHistory = array();
	
	foreach ($terms as $term) {
		$treeTerm = taxonomy_term_load($term -> tid);
		if (!empty($treeTerm -> field_default_contenttype) && !empty($treeTerm -> field_default_contenttype['und'][0]['value'])) {
			//check parent is already removed from tree
			if (isset($treeTerm -> parents[0])) {
				if (in_array($treeTerm -> parents[0], $skipParents)) {
					$skipParents[] = $treeTerm -> tid;
					continue;
				}
			}
	
			//check combination is not allowed
			$notAllowedCombination = array();
			if (isset($treeTerm -> field_not_visible['und'])) {
				foreach ($treeTerm->field_not_visible['und'] as $notAllowed) {
					$notAllowedCombination[] = $notAllowed['value'];
				}
				if (in_array($notAllowedCombinationStr, $notAllowedCombination)) {
					$skipParents[] = $treeTerm -> tid;
					continue;
				}
			}
			
			$contentType = $treeTerm -> field_default_contenttype['und'][0]['value'];

			switch($contentType) {
				case 'treenodecounter' :
					$productTypeTerm = taxonomy_term_load($product -> field_product_type['und'][0]['tid']);
					if ($productTypeTerm -> name === 'Main') {
						_create_default_basic_counters($product -> nid, $treeTerm -> tid);
					}
					break;
				default :
					$node = new StdClass();
					$node -> uid = $user -> uid;
					$node -> type = $treeTerm -> field_default_contenttype['und'][0]['value'];
					$node -> language = 'und';
					$node -> field_ref_product['und'][0]['nid'] = $product -> nid;
					if (!empty($treeTerm -> field_default_fieldset)) {
						foreach ($treeTerm->field_default_fieldset['und'] as $field) {
							$fieldSet = field_collection_item_load($field['value']);
							$fieldName = $fieldSet -> field_field_name['und'][0]['value'];
							$fieldValue = $fieldSet -> field_field_value['und'][0]['value'];

							if ($fieldValue == '$productNid') {
								$fieldValue = $product -> nid;
							} else if ($fieldValue == '$refTreeTid') {
								$fieldValue = $term -> tid;
							} else if ($fieldValue == '$rid') {
								$now = time();
								if(in_array($now,$ridHistory)){
									$now++;
								}
								$fieldValue = '\'' . $product -> field_product_id['und'][0]['value'] . '_' . $now . '\'';
								$ridHistory[] = $now;
							} else if ($fieldValue == '$productBillType') {
								$fieldValue = $product -> field_billing_type['und'][0]['tid'];
							} 
							$command = '$node->' . $fieldName . '=' . $fieldValue . ';';
							eval($command);
						}
					}// foreach
					node_save($node);
					break;
			} //if
		}
	}
}

function _create_default_cugdiscountfactors_in_tariffplan($tariffplan) {
	global $user;

	$voca_name = $tariffplan -> field_tree_child_voca_name['und'][0]['value'];
	$cugDiscountTerm = taxonomy_get_term_by_name('CUG Discount by CS', $voca_name);
	$refTreeTid =  current($cugDiscountTerm) -> tid;

	$product = node_load($tariffplan -> field_ref_product['und'][0]['nid']);

	$node = new StdClass();
	$node -> uid = $user -> uid;
	$node -> type = 'actionpricecugdiscountfactors';
	$node -> language = 'und';

	$node -> field_weight = array('und' => array(0 => array('value' => 100)));
	$node -> field_ref_product = array('und' => array(0 => array('nid' => $product -> nid)));
	$node -> field_ref_tree_tid = array('und' => array(0 => array('value' => $refTreeTid)));
	$node -> field_ref_tree_nid = array('und' => array(0 => array('nid' => $tariffplan -> nid)));

	node_save($node);

}

function _create_default_items_in_product($product) {
	session_set('TOUCH_PRODUCT', FALSE);
	dsm(session_get('TOUCH_PRODUCT'));
	if (!empty($product -> field_is_cloned) && $product -> field_is_cloned['und'][0]['value'] == 0) {

		$voca_name = _get_vocabulary_name('simpleproductoffering', $product);
		_create_default_items_by_voca($product, $voca_name);
	}
	session_set('TOUCH_PRODUCT', TRUE);
}

function _create_default_items_in_product_old($product) {

	if (!empty($product -> field_is_cloned) && $product -> field_is_cloned['und'][0]['value'] == 0) {

		//main counter create
		$voca_name = _get_vocabulary_name('simpleproductoffering', $product);

		$serviceDomainTerm = taxonomy_term_load($product -> field_service_type_of_provider['und'][0]['tid']);

		if ($serviceDomainTerm -> name == 'Cross') {
			_create_default_items_by_voca($product, $voca_name);
			return;
		}

		$mainTerm = taxonomy_get_term_by_name('Charging', $voca_name);
		$prdTypeTerm = taxonomy_term_load($product -> field_product_type['und'][0]['tid']);

		// main 상품을 생성하는 경우가 아니면 basic counter를 초기에 생성시켜줄 필요가 없다.
		// vocabulary에서 'Main' counter에 해당하는 부분에 basic counter를 자동으로 생성하게 해준다.
		if (!empty($mainTerm) && ($prdTypeTerm -> name == 'Main')) {
			_create_default_basic_counters($product -> nid,  current($mainTerm) -> tid);
			_create_default_recharge_block_item($product, $voca_name);
		}

		_create_default_prdattributes($product, $voca_name);

		// _create_default_prdattribute_relations($offering, $voca_name);
		_create_default_prdnonusage($product, $voca_name);

		// product basic counter setting
		_create_default_prdcounterlist($product, $voca_name);
	}
}

function _create_default_recharge_block_item($product, $voca_name) {
	global $user;

	$term = taxonomy_get_term_by_name('Recharge', $voca_name);

	if (!empty($term)) {
		$node = new StdClass();
		$node -> uid = $user -> uid;
		$node -> type = 'prdnonusagerechargeblock';
		$node -> language = 'und';
		$node -> field_ref_product['und'][0]['nid'] = $product -> nid;
		$node -> field_ref_tree_tid['und'][0]['value'] =  current($term) -> tid;
		node_save($node);
	}
}

function _create_default_prdnonusage($product, $voca_name) {
	global $user;

	$contentTypes = array('prdnonusagerecurringchargescheme', 'prdnonusagerecurringbonusscheme');

	foreach ($contentTypes as $contentType) {
		$node = new StdClass();
		$node -> uid = $user -> uid;
		$node -> type = $contentType;
		$node -> language = 'und';
		$node -> field_ref_product['und'][0]['nid'] = $product -> nid;
		// $node->field_ref_tree_tid['und'][0]['value'] = $term->tid;
		node_save($node);
	}
}

function _create_default_prdcounterlist($product, $voca_name) {
	global $user;

	$node = new stdClass();
	$node -> uid = $user -> uid;
	$node -> type = 'prdcounterlist';
	$node -> language = 'und';

	$term = taxonomy_get_term_by_name('Counter', $voca_name);

	$node -> field_ref_tree_tid['und'][0]['value'] =  current($term) -> tid;
	$node -> field_ref_product['und'][0]['nid'] = $product -> nid;
	node_save($node);
}

function _create_default_prdattribute_relations($product, $voca_name) {
	global $user;

	$treeTerm = array();
	$treeTermNames = array('Mandatory', 'Optional', 'Hidden');

	foreach ($treeTermNames as $termName) {
		$cmdTmp = '$treeTerm["' . $termName . '"] = taxonomy_get_term_by_name("' . $termName . '","' . $voca_name . '");';
		eval($cmdTmp);
	}

	$vocabulary = taxonomy_vocabulary_machine_name_load('prdrelationtype');
	$relationTerms = taxonomy_get_tree($vocabulary -> vid);

	foreach ($relationTerms as $relationTerm) {

		$node = new StdClass();
		$node -> uid = $user -> uid;
		$node -> type = 'prdattributepackaged';
		$node -> language = 'und';
		$node -> field_ref_product['und'][0]['nid'] = $product -> nid;

		if (strpos($relationTerm -> name, 'Mandatory') !== FALSE) {
			$node -> field_ref_tree_tid['und'][0]['value'] =  current($treeTerm['Mandatory']) -> tid;
		} else if (strpos($relationTerm -> name, 'Optional') !== FALSE) {
			$node -> field_ref_tree_tid['und'][0]['value'] =  current($treeTerm['Optional']) -> tid;
		} else if (strpos($relationTerm -> name, 'Hidden') !== FALSE) {
			$node -> field_ref_tree_tid['und'][0]['value'] =  current($treeTerm['Hidden']) -> tid;
		}

		$node -> field_ref_prdrelationtype['und'][0]['tid'] = $relationTerm -> tid;
		node_save($node);

	}
}

function _create_default_prdattributes($product, $voca_name) {
	global $user;

	$defaultContentTypes = array('prdattributebenefit' => 'Benefits',
	//'prdattributefeaturecode' => 'Service Feature Code'
	);

	$service_domain = taxonomy_term_load($product -> field_service_type_of_provider['und'][0]['tid']);
	if ($service_domain != 'Cross') {
		$defaultContentTypes['prdattributebenefit'] = 'Benefits';
	}

	$product_type = taxonomy_term_load($product -> field_product_type['und'][0]['tid']);
	if ($product_type -> name != 'Package') {
		$defaultContentTypes['prdattributefeaturecode'] = 'Service Feature Code';
	}
	if (($service_domain -> name == 'Mobile' || $service_domain -> name == 'VoIP') && $product_type -> name == 'Main') {

		$defaultContentTypes['prdattributeprefixrangeallowed'] = 'Allowed Prefix';
	};

	foreach ($defaultContentTypes as $contentType => $treeTermName) {
		$node = new StdClass();
		$node -> uid = $user -> uid;
		$node -> type = $contentType;
		$node -> language = 'und';
		$node -> field_ref_product['und'][0]['nid'] = $product -> nid;
		$cmdTmp = '$treeTerm = taxonomy_get_term_by_name("' . $treeTermName . '","' . $voca_name . '");';
		eval($cmdTmp);

		$node -> field_ref_tree_tid['und'][0]['value'] =  current($treeTerm) -> tid;
		node_save($node);
	}
}

// 해당 상품 type의 basic counter를 return 한다.
function _get_default_basic_counters_without_receive($productNid) {
	global $user;
	$retArray = array();

	$product = node_load($productNid);

	$term_service_domain_tid = $product -> field_service_type_of_provider['und'][0]['tid'];
	$term_counter_type = taxonomy_get_term_by_name('Basic', 'countertype');
	$term_bill_type_product = taxonomy_term_load($product -> field_billing_type['und'][0]['tid']);

	$args = array();
	$args[0] =  current($term_counter_type) -> tid;
	$args[1] = $term_service_domain_tid;

	switch($term_bill_type_product->name) {
		case 'Prepaid' :
		case 'Postpaid' :
			$term_bill_type_counter = taxonomy_get_term_by_name($term_bill_type_product -> name, 'billtypecounter');
			$billTypeCounter = current($term_bill_type_counter);
			$args[2] = $billTypeCounter -> tid;
			break;
		case 'Hybrid' :
			$args[2] = 'all';
			break;
	}

	// 예) POSTPAID/MOBILE로 view검색
	$view = views_get_view('query_list_counter');
	$view -> set_display('panel_pane_7');
	$view -> set_arguments($args);
	$view -> execute();

	$retArray = array();
	foreach ($view->result as $record) {
		$retArray[$record -> nid] = view_get_field_value_by_label($view, 'PHP', $record);
	}

	// 후불 상품에서는 선불 basic counter에 FREE_, POINT를 포함한다.
	if ($term_bill_type_product -> name == 'Postpaid') {
		$term_bill_type_counter = taxonomy_get_term_by_name('Prepaid', 'billtypecounter');
		$billTypeCounter = current($term_bill_type_counter);
		$args[2] = $billTypeCounter -> tid;
	}
	$viewResult = views_get_view_result('query_list_counter', 'panel_pane_6', $args[0], $args[1], $args[2]);
	foreach ($viewResult as $record) {
		$retArray[$record -> nid] = view_get_field_value_by_label($view, 'PHP', $record);
	}

	return $retArray;
	// return $view->result;
}

// 해당 상품 type의 basic counter를 return 한다.
function _get_default_basic_counters($productNid) {
	global $user;
	$retArray = array();

	$product = node_load($productNid);

	$term_service_domain_tid = $product -> field_service_type_of_provider['und'][0]['tid'];
	$term_counter_type = taxonomy_get_term_by_name('Basic', 'countertype');
	$term_bill_type_product = taxonomy_term_load($product -> field_billing_type['und'][0]['tid']);

	$args = array();
	$args[0] =  current($term_counter_type) -> tid;
	$args[1] = $term_service_domain_tid;

	switch($term_bill_type_product->name) {
		case 'Prepaid' :
		case 'Postpaid' :
			$term_bill_type_counter = taxonomy_get_term_by_name($term_bill_type_product -> name, 'billtypecounter');
			$billTypeCounter = current($term_bill_type_counter);
			$args[2] = $billTypeCounter -> tid;
			break;
		case 'Hybrid' :
			$args[2] = 'all';
			break;
	}

	// 예) POSTPAID/MOBILE로 view검색
	$view = views_get_view('query_list_counter');
	$view -> set_display('panel_pane_1');
	$view -> set_arguments($args);
	$view -> execute();

	$retArray = array();
	foreach ($view->result as $record) {
		$retArray[$record -> nid] = view_get_field_value_by_label($view, 'PHP', $record);
	}

	// 후불 상품에서는 선불 basic counter에 FREE_, POINT를 포함한다.
	if ($term_bill_type_product -> name == 'Postpaid') {
		$term_bill_type_counter = taxonomy_get_term_by_name('Prepaid', 'billtypecounter');
		$billTypeCounter = current($term_bill_type_counter);
		$args[2] = $billTypeCounter -> tid;
	}
	$viewResult = views_get_view_result('query_list_counter', 'panel_pane_5', $args[0], $args[1], $args[2]);
	foreach ($viewResult as $record) {
		$retArray[$record -> nid] = view_get_field_value_by_label($view, 'PHP', $record);
	}

	return $retArray;
	// return $view->result;
}

function _get_taxonomy_term_name_by_svcdomain($svcDomain) {

	$vocaNameDefaultTpl = array('Cross' => 'tpl_default_tree_cross_main', 'IPTV' => 'tpl_default_tree_iptv', 'Mobile' => 'tpl_default_tree_mobile', 'Broadband' => 'tpl_default_tree_broadband', 'VoIP' => 'tpl_default_tree_voip', 'Satellite' => 'tpl_default_tree_satellite', 'Dummy' => 'tpl_default_tree_dummy', );

	return $vocaNameDefaultTpl[$svcDomain];
}

function _attach_basic_counter($counter, $svcDomain) {
	global $user;

	$weightStep = 100;

	$vocaNameDefaultTpl = _get_taxonomy_term_name_by_svcdomain($svcDomain);

	$billingTypeCounterTerm = taxonomy_term_load($counter -> field_billing_type_counter['und'][0]['tid']);
	$prdBillingTypes = array('0' => 'Hybrid', '1' => $billingTypeCounterTerm -> name);

	// get refTreeTid
	$refTreeTerm = taxonomy_get_term_by_name('Charging', $vocaNameDefaultTpl);
	$refTreeTid =  current($refTreeTerm) -> tid;

	// get main product list
	$args_1 = array('0' => $svcDomain, '1' => join('+', $prdBillingTypes));

	// $viewResult = views_get_view_result('list_product', 'panel_pane_1', array('0' => $svcDomain, '1' => join('+', $prdBillingTypes)));
	$view = views_get_view('list_product');
	$view -> set_display('panel_pane_1');
	$view -> set_arguments($args_1);
	$view -> execute();
	$viewResult = $view -> result;

	$args = array('0' => $refTreeTid);
	foreach ($viewResult as $record) {
		$args[1] = $record -> nid;

		// $viewResultMinWeight = views_get_view_result('query_min_weight_in_treenodecounter', 'panel_pane_1', $args);
		$viewMinWeight = views_get_view('query_min_weight_in_treenodecounter');
		$viewMinWeight -> set_display('panel_pane_1');
		$viewMinWeight -> set_arguments($args);
		$viewMinWeight -> execute();

		$currentView = $viewMinWeight -> result;

		if (!empty($currentView)) {
			$minWeight = $currentView[0] -> field_data_field_weight_field_weight_value;
		} else {
			$minWeight = 0;
		}

		$treeNodeCounter = new StdClass();
		$treeNodeCounter -> uid = $user -> uid;
		$treeNodeCounter -> type = 'treenodecounter';
		$treeNodeCounter -> language = 'und';

		$treeNodeCounter -> field_ref_counter['und'][0]['nid'] = $counter -> nid;
		$treeNodeCounter -> field_weight['und'][0]['value'] = $minWeight - $weightStep;
		$treeNodeCounter -> field_ref_tree_tid['und'][0]['value'] = $refTreeTid;
		$treeNodeCounter -> field_ref_product['und'][0]['nid'] = $record -> nid;
		$treeNodeCounter -> field_main_or_accumulated['und'][0]['tid'] = 689;
		// Main(Charging) main or accmulating

		node_save($treeNodeCounter);
	}

	return;
}

// 상품 생성시 global에 있는 basic counter는
//
function _create_default_basic_counters($productNid, $refTreeTid) {
	global $user;

	$basicCounters = _get_default_basic_counters($productNid);

	$weightStep = 100;
	$weight = 0;

	foreach ($basicCounters as $key => $value) {
		$dtn_basic_counter = new StdClass();
		$dtn_basic_counter -> uid = $user -> uid;
		$dtn_basic_counter -> type = 'treenodecounter';
		$dtn_basic_counter -> language = 'und';

		$dtn_basic_counter -> field_ref_counter['und'][0]['nid'] = $key;
		$dtn_basic_counter -> field_weight['und'][0]['value'] = $weight * $weightStep;

		$term_tree = taxonomy_get_term_by_name('Main', 'countermainoraccu');

		$dtn_basic_counter -> field_main_or_accumulated['und'][0]['tid'] =  current($term_tree) -> tid;
		$dtn_basic_counter -> field_ref_tree_tid['und'][0]['value'] = $refTreeTid;
		$dtn_basic_counter -> field_ref_product['und'][0]['nid'] = $productNid;
		node_save($dtn_basic_counter);

		$weight += 1;
	}

	return;
}

function _create_default_tree_node($voca_name, $rootNid) {
	global $user;
	$vocabulary = taxonomy_vocabulary_machine_name_load($voca_name);

	$tree = taxonomy_get_tree($vocabulary -> vid);

	$weightStep = -100;

	$treeNodeNid = array();
	$treeNodeParent = array();

	foreach ($tree as $term) {

		$defaultTreeNode = new StdClass();
		$defaultTreeNode -> uid = $user -> uid;
		$defaultTreeNode -> type = 'defaulttreenode';
		$defaultTreeNode -> language = 'und';
		$defaultTreeNode -> field_ref_tree_node_tid['und'][0]['value'] = $term -> tid;
		$defaultTreeNode -> field_weight['und'][0]['value'] = $term -> weight * $weightStep;
		node_save($defaultTreeNode);
		$treeNodeNid[$term -> tid] = $defaultTreeNode -> nid;
		$treeNodeParent[$defaultTreeNode -> nid] = $term -> parents[0];

		// MAIN counter의 defaulttreenode 생성 시
		// product의 bill_type에 따라 basic counter를 생성한다.
		//
		$tmpTerm = taxonomy_term_load($term -> tid);
		if (!empty($tmpTerm -> field_rel_type) && strstr($tmpTerm -> field_rel_type['und'][0]['value'], '_counter_main')) {
			_create_default_basic_counters($rootNid, $defaultTreeNode -> nid);
		}
	}

	foreach ($treeNodeNid as $item) {
		$node = node_load($item);
		if ($treeNodeParent[$item] == '0') {
			$node -> field_parent_node['und'][0]['nid'] = $rootNid;
		} else {
			$parentTid = $treeNodeParent[$node -> nid];
			$parentNid = $treeNodeNid[$parentTid];
			$node -> field_parent_node['und'][0]['nid'] = $parentNid;
		}
		node_save($node);
	}
}

function _condition_submit_handler($form, &$form_state) {

	if (isset($form_state['rule_nid'])) {
		$rule = node_load($form_state['rule_nid']);

		$rule -> field_ref_condition_factors['und'][] = array('nid' => $form_state['values']['nid']);
		node_save($rule);
	}
}

function _basicrate_idd_link_to_usage(&$form, &$form_state) {

	// link basicrate_idd to usage
	//
	if (isset($form_state['parent_nid'])) {
		$usage = node_load($form_state['parent_nid']);

		// dsm($usage);
		$usage -> field_ref_basicrate_idd['und'][] = array('nid' => $form_state['values']['nid']);
		node_save($usage);
	}
}

function _rule_actionprice_submit_handler($form, &$form_state) {

	if (!isset($form['nid']['#value'])) {//Create
		if (isset($form_state['rule_nid'])) {
			$rule = node_load($form_state['rule_nid']);

			switch($form_state['price_type']) {
				case  'CHARGE' :
					$rule -> field_ref_action_charge['und'][] = array('nid' => $form_state['values']['nid']);
					break;
				case  'DISCOUNT' :
					$rule -> field_ref_action_discount['und'][] = array('nid' => $form_state['values']['nid']);
					break;
				case  'ALLOWANCE' :
					$rule -> field_ref_action_allowance['und'][] = array('nid' => $form_state['values']['nid']);
					break;
			}
			node_save($rule);
		}
	}
}

function _create_actionpricefactors_node_form($param) {
	global $user;
	module_load_include('inc', 'node', 'node.pages');

	$priceType = $param['price_type'];

	$node = new StdClass();
	$node -> uid = $user -> uid;
	$node -> type = 'actionpricefactors';
	$node -> language = 'und';
	$termId =  current(taxonomy_get_term_by_name($priceType, 'action_price_factor_type')) -> tid;
	$node -> field_action_price_factor_type['und'][0]['tid'] = $termId;

	node_object_prepare($node);

	$formName = 'actionpricefactors_node_form';
	$form_state = array();
	$form_state['rule_nid'] = $param['rule_nid'];
	$form_state['build_info']['args'] = array($node);
	$form_state['price_type'] = $priceType;

	$form = drupal_build_form($formName, $form_state);
	$output = drupal_render($form);

	return $output;
}

function _ratinggroup_link_to_numberingplan_idd($form, $form_state) {
	$numberingplan_idd = node_load($form_state['numberingplan_idd_nid']);
	$numberingplan_idd -> field_ref_idd_ratinggroup['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($numberingplan_idd);
}

function _ratinggroup_link_to_roaming_plan($form, $form_state) {
	$roamingplanNode = node_load($form_state['roamingplan_nid']);
	$roamingplanNode -> field_ref_roaming_ratinggroup['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($roamingplanNode);
}

function _country_link_to_numberingplan_idd($form, $form_state) {
	$numberingplan_idd = node_load($form_state['numberingplan_idd_nid']);
	$numberingplan_idd -> field_ref_idd_country['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($numberingplan_idd);
}

function _exit_link_to_numberingplan_idd($form, $form_state) {
	$numberingplan_idd = node_load($form_state['numberingplan_idd_nid']);
	$numberingplan_idd -> field_ref_idd_exit['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($numberingplan_idd);
}

function _npa_link_to_numberingplan_domestic($form, $form_state) {
	$numberingplan_domestic = node_load($form_state['numberingplan_domestic_nid']);
	$numberingplan_domestic -> field_ref_domestic_npa['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($numberingplan_domestic);
}

function _area_link_to_numberingplan_domestic($form, $form_state) {
	$numberingplan_domestic = node_load($form_state['numberingplan_domestic_nid']);
	$numberingplan_domestic -> field_ref_domestic_area['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($numberingplan_domestic);
}

function _timetablefactors_link_to_timetable($form, $form_state) {
	$timetable = node_load($form_state['timetable_nid']);
	$timetable -> field_ref_timetablefactors['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($timetable);
}

function _ratinggroup_link_to_numberingplan_domestic($form, $form_state) {
	$numberingplan_domestic = node_load($form_state['numberingplan_domestic_nid']);
	$numberingplan_domestic -> field_ref_domestic_ratinggroup['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($numberingplan_domestic);
}

function _prefix_link_to_carrier($form, $form_state) {
	$carrier = node_load($form_state['carrier_nid']);
	$carrier -> field_ref_prefix['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($carrier);
}

function _ratinggroup_link_to_carrier($form, $form_state) {
	$carrier = node_load($form_state['carrier_nid']);
	$carrier -> field_ref_rating_group['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($carrier);
}

function _basicrate_link_to_usage($form, $form_state) {
	$usage = node_load($form_state['usage_nid']);
	$usage -> field_ref_basicrate['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($usage);
}

function _rule_link_to_rattinggroup($form, $form_state) {
	$ratingGroup = node_load($form_state['ratinggroup_nid']);
	$ratingGroup -> field_ref_rule['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($ratingGroup);
}

function _rule_link_to_nonusage($form, $form_state) {
	$nonusage = node_load($form_state['nonusage_nid']);
	$nonusage -> field_ref_rule['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($nonusage);
}

function _rule_link_to_usage($form, $form_state) {
	$usage = node_load($form_state['usage_nid']);
	$usage -> field_ref_rule['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($usage);
}

function _rule_link_to_counter($form, $form_state) {
	$counter = node_load($form_state['counter_nid']);
	$counter -> field_ref_rule['und'][] = array('nid' => $form_state['values']['nid']);
	node_save($counter);
}

function _link_to_parent($form, $form_state) {
	$parentNode = node_load($form_state['parent_nid']);
	$targetFieldName = null;

	switch($parentNode->type) {
		case 'basicrate_idd' :
			switch($form['#node']->type) {
				case 'conditioncommoncarrieridd' :
				case 'conditioncommoncarrierdomestic' :
				case 'conditioncommonratinggroup' :
				case 'conditioncommontimetablefactors' :
					$targetFieldName = 'field_ref_condition_idd';
					break;
			}
			break;
	}

	$evalString = '$parentNode->' . $targetFieldName . '[\'und\'][][\'nid\'] = $form_state[\'nid\'];';

	eval($evalString);
	node_save($parentNode);
}

function _unittransfer_submit_handler($form, $form_state) {
	global $user;
	module_load_include('inc', 'node', 'node.pages');

	$unitTransferNode = node_load($form_state['values']['nid']);

	//create unittransferfactor
	$viewResult = views_get_view_result('list_counter_group_for_unittransfer', 'panel_pane_1');

	foreach ($viewResult as $item) {
		$node = new StdClass();
		$node -> uid = $user -> uid;
		$node -> type = 'unittransferfactor';
		$node -> language = 'und';
		$node -> field_counter_group['und'][0]['tid'] = $item -> tid;
		$node -> field_parent_node['und'][0]['nid'] = $unitTransferNode -> nid;
		node_save($node);
		$unitTransferNode -> field_ref_unittransferfactors['und'][] = array('nid' => $node -> nid);
	}

	node_save($unitTransferNode);
}

function _common_counter_submit_handler($form, $form_state) {
	global $user;
	module_load_include('inc', 'node', 'node.pages');
	$weightStep = 100;

	$counterNode = node_load($form_state['values']['nid']);
	// $mainOrAccumulatedTerm = taxonomy_term_load($counterNode->field_main_or_accumulated['und'][0]['tid']);
	$counterTypeTerm = taxonomy_term_load($counterNode -> field_counter_type['und'][0]['tid']);

}

function _vouchercardtype_submit_handler($form, $form_state) {

	global $user;

	$node = node_load($form_state['build_info']['args'][0] -> nid);
	$voucherCardType = taxonomy_term_load($node -> field_ref_voucher_type['und'][0]['tid']);

	if ($voucherCardType -> name == 'Discount') {
		$node -> field_tree_child_voca_name['und'][0] = array('value' => 'tpl_vouchercardtype_discount');
	} else {
		$node -> field_tree_child_voca_name['und'][0] = array('value' => 'tpl_vouchercardtype');
	}
	node_save($node);

	// taxonomy_get_tree
	$voca = taxonomy_vocabulary_machine_name_load('tpl_vouchercardtype');
	$terms = taxonomy_get_tree($voca -> vid);
	foreach ($terms as $domainTerm) {
		if ($domainTerm -> name == 'Loyalty Point') {
			$loyaltyPoint = new StdClass();
			$loyaltyPoint -> type = 'loyaltypoint';
			$loyaltyPoint -> language = 'und';
			$loyaltyPoint -> uid = $user -> uid;
			$loyaltyPoint -> field_ref_vouchercardtype['und'][0]['nid'] = $node -> nid;
			$loyaltyPoint -> field_ref_tree_tid['und'][0]['value'] = $domainTerm -> tid;
			node_save($loyaltyPoint);
		}
	}

}

function set_unlimited_in_treenodecounter($node) {

	if (isset($node -> field_unlimited_threshold)) {
		$unlimitedOption = $node -> field_unlimited_threshold['und'][0]['value'];
		if ($unlimitedOption == 1) {
			$node -> field_threshold_limit_amount['und'][0]['value'] = 999999999999;
		}
	}
}

function set_exclusiveness_check($node_unchanged, $node_changed) {
	$productNid = $node_changed -> nid;

	$list_unchanged = array();
	$list_changed = array();

	if (isset($node_unchanged -> field_exclusiveness) && (!empty($node_unchanged -> field_exclusiveness['und']))) {
		foreach ($node_unchanged->field_exclusiveness['und'] as $record) {
			$list_unchanged[] = $record['nid'];
		}
	}

	if (isset($node_changed -> field_exclusiveness) && (!empty($node_changed -> field_exclusiveness['und']))) {
		foreach ($node_changed->field_exclusiveness['und'] as $record) {
			$list_changed[] = $record['nid'];
		}
	}

	$addList = array_diff($list_changed, $list_unchanged);
	$deleteList = array_diff($list_unchanged, $list_changed);

	foreach ($addList as $item) {
		$productForAdd = node_load($item);
		$productForAdd -> field_exclusiveness['und'][] = array('nid' => $productNid);
		node_save($productForAdd);
	}

	foreach ($deleteList as $item) {
		$productForDelete = node_load($item);
		$index = 0;

		foreach ($productForDelete->field_exclusiveness['und'] as $record) {
			if ($record['nid'] == $productNid) {
				unset($productForDelete -> field_exclusiveness['und'][$index]);
				node_save($productForDelete);
				break;
			};
			$index++;
		}
	}
}

function set_numbersaving() {
	global $user;
	$node = new StdClass();
	$node -> uid = $user -> uid;
	$node -> type = 'prdattributenumbersaving';
	$node -> language = 'und';
	$node -> field_ref_product['und'][0]['nid'] = $entity -> nid;
	$node -> field_ref_tree_tid['und'][0]['value'] = 6771;
	node_save($node);

	global $user;
	$node = new StdClass();
	$node -> uid = $user -> uid;
	$node -> type = 'prdattributeavailablechannel';
	$node -> language = 'und';
	$node -> field_ref_product['und'][0]['nid'] = $entity -> nid;
	$node -> field_ref_tree_tid['und'][0]['value'] = 7035;
	node_save($node);

}
