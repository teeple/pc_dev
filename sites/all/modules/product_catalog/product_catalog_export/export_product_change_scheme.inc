<?php

function _product_change_scheme_for_export($exportItemNids = NULL, $isExternalAPI = FALSE) {
    $retData = array();
    $retDataTmp = array();
    $productNids = array();
    $productSchemeIds = array();
    
    if (!is_array($exportItemNids)) {
        $exportItemNids = array($exportItemNids);
    }
    
    $viewResult = views_get_view_result('list_product_change', 'panel_pane_3', join(',', $exportItemNids));
    
	foreach ($viewResult as $record) {
		$productChange = array();
		
		$productChange['product_change_scheme_id'] = $record->field_field_product_change_id[0]['raw']['value'];
		
		$productChange['product_change_scheme_name'] = $record->node_title;
		$productChange['service_domain'] = _get_common_code($record->field_field_service_domain[0]['raw']['taxonomy_term']);
		$productChange['billing_type'] = _get_common_code($record->field_field_billing_type[0]['raw']['taxonomy_term']);
		
		foreach($record->field_field_from_product_group as $fromProductGroup) {
			$productChange['from_product_groups'][] = array('product_group_id' => $fromProductGroup['rendered']['#options']['entity']->field_product_group_id['und'][0]['value']);
		}
		
		foreach($record->field_field_to_product_group as $toProductGroup) {
			$productChange['to_product_groups'][] = array('product_group_id' => $toProductGroup['rendered']['#options']['entity']->field_product_group_id['und'][0]['value']);
		}
		
		$productChange['product_change_fee'] = isset($record->field_field_product_change_fee[0]['raw']['value']) ? $record->field_field_product_change_fee[0]['raw']['value'] : NULL;
		
		if($record->field_field_first_change_fee_free_[0]['raw']['value'] == 0) {
			$productChange['first_change_fee_free'] = FALSE;
		} else {
			$productChange['first_change_fee_free'] = TRUE;		
		}
		
		// Grace Date Setting
		$graceDate = array();
		$graceDate['options'] = isset($record->field_field_gracedate_options[0]['rendered']['#title'])? $record->field_field_gracedate_options[0]['rendered']['#title']: NULL;
		
		if($record->field_field_gracedate_options[0]['rendered']['#options']['entity']->name != 'Fixed Date') {
			$graceDate['ndays'] = isset($record->field_field_gracedate_ndays[0]['raw']['value'])? $record->field_field_gracedate_ndays[0]['raw']['value']: NULL;
			$graceDate['fixed_date'] = NULL;
		} else {
			$graceDate['ndays'] = NULL;
			$graceDate['fixed_date'] = isset($record->field_field_gracedate_fixeddate[0]['raw']['value'])? $record->field_field_gracedate_fixeddate[0]['raw']['value']: NULL;
		}
		
		// Expire Date Setting
		$expireDate = array();
		$expireDate['options'] = isset($record->field_field_expiredate_options[0]['rendered']['#title'])? $record->field_field_expiredate_options[0]['rendered']['#title']: NULL;
		
		if($record->field_field_expiredate_options[0]['rendered']['#options']['entity']->name != 'Fixed Date') {
			$expireDate['ndays'] = isset($record->field_field_expiredate_ndays[0]['raw']['value'])? $record->field_field_expiredate_ndays[0]['raw']['value']: NULL;
			$expireDate['fixed_date'] = NULL;			
		} else {
			$expireDate['ndays'] = NULL;		
			$expireDate['fixed_date'] = isset($record->field_field_expiredate_fixeddate[0]['raw']['value'])? $record->field_field_expiredate_fixeddate[0]['raw']['value']: NULL;
		}
		$productChange['active_date'] = $expireDate;
		$productChange['grace_date'] = $graceDate;
		
		$viewResultSubSelected = views_get_view_result('list_product_change_sub_selected', 'panel_pane_4', $record->nid);
		$subProducts = array();
		foreach($viewResultSubSelected as $item) {
			$subProducts[] = array('product_id' => $item->field_field_product_id[0]['raw']['value']);
		}
		$productChange['transferable_sub_products'] = $subProducts;
		
		$viewResultCounterSelected = views_get_view_result('list_product_change_counter_selected', 'panel_pane_4', $record->nid);
		
		$selctedCounters = array();
		foreach($viewResultCounterSelected as $item) {
			$selctedCounters[] = array('counter_id' => $item->field_field_counter_id[0]['raw']['value']);
		}
		$productChange['transferable_counters'] = $selctedCounters;
		
	    $retDataTmp[] = $productChange;
	    
	    $productSchemeIds[] = $productChange['product_change_scheme_id'];
	}
	
    if(!$isExternalAPI) {
	    if (!empty($exportItemNids)) {
	        $retData['ifvalues']['resources'] = $productSchemeIds;
	    } else {
	        $retData['ifvalues']['resources'] = '';
	    }
	  }
	  
    $retData['product_change_scheme'] = $retDataTmp;

    return $retData;
}
