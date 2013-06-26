<?php

function validate_voucher($voucher_nid) {
  $result = array('is_valid' => TRUE );
	$voucher_node = node_load($voucher_nid);
	
  $voucher_type_term = taxonomy_term_load($voucher_node->field_ref_voucher_type['und'][0]['tid']);
	$voucher_type = $voucher_type_term->field_common_code['und'][0]['value'];
	
	if($voucher_type == 1){//Entry Type일 때만 체크. Common Code 1 이 Entry
		$list_mobile_domain_remains = views_get_view_result('list_counter_for_vouchercardtype', 'panel_pane_5', $voucher_nid);
		if(empty($list_mobile_domain_remains)){//if mobile domains does not have remains, than go further to find remains of product specific
			$list_mobile_product = views_get_view_result('list_treenodeproductforvoucher', 'panel_pane_3', $voucher_nid);
			if(empty($list_mobile_product)){
				$result['is_valid'] = FALSE;
	      $result['base_type'] = 'Vouhcer Card Type';
	      $result['title'] = $voucher_node -> title;
	      $result['reason'] = 'There is no remains set of Remains Counter Group for the mobile domain';
			}else{
				foreach($list_mobile_product as $tree_node_product){
					$tree_node_product_nid = $tree_node_product->nid;	
					$amount_result = views_get_view_result('list_treenodecounterforvoucherprd', 'panel_pane_4', $tree_node_product_nid);	
					if(empty($amount_result)){
						$result['is_valid'] = FALSE;
			      $result['base_type'] = 'Vouhcer Card Type';
			      $result['title'] = $voucher_node -> title;
			      $result['reason'] = 'There is no remains set of Remains Counter Group for '.$tree_node_product->node_title. ' product';
						break;
					}
				}
			}
		}
	}
	
	return $result;

}

function validate_product_group($productGroupNid) {
  $result = array('is_valid' => TRUE, );

  $productGroup = node_load($productGroupNid);
  $viewResultMainSelected = views_get_view_result('list_product_group_main_selected', 'panel_pane_4', $productGroupNid);

  if (count($viewResultMainSelected) == 0) {
    $result['is_valid'] = FALSE;
    $result['base_type'] = 'PRODUCT GROUP';

    $result['id'] = $productGroupNid;
    $result['title'] = $productGroup -> field_product_group_id['und'][0]['value'];
    $result['reason'] = 'No products which belongs to this product group';
  }

  return $result;
}

function validate_product($productNid) {
  $result = array('is_valid' => TRUE, );
  $productNode = node_load($productNid);

  //main 상품일 경우에만 lifecycle scheme check, Bundle은 제외
  $productTypeTerm = taxonomy_term_load($productNode -> field_product_type['und'][0]['tid']);
  $serviceDomainTerm = taxonomy_term_load($productNode -> field_service_type_of_provider['und'][0]['tid']);

  if ($productTypeTerm -> name == 'Main' && $serviceDomainTerm -> name != 'Cross') {
    $lifecycleSchemeNid = _get_lifecyclescheme($productNid);
    if (!isset($lifecycleSchemeNid)) {
      $result['is_valid'] = FALSE;

      $result['base_type'] = 'PRODUCT';
      $result['id'] = $productNode -> nid;
      $result['title'] = $productNode -> title;
      $result['reason'] = 'Lifecycle Scheme is not defined yet';
    }
  }

  if (($serviceDomainTerm -> name == 'Mobile' || $serviceDomainTerm -> name == 'VoIP') && $productTypeTerm -> name == 'Main') {

    $viewResult = views_get_view_result('list_product_child_node', 'panel_pane_2', $productNid, 'prdattributeprefixrangeallowed');

    if (count($viewResult) > 0) {
      $allowedPrefixNode = node_load(current($viewResult) -> nid);

      if (empty($allowedPrefixNode -> field_prefix_range) || (count($allowedPrefixNode -> field_prefix_range['und']) == 0)) {
        $result['is_valid'] = FALSE;

        $result['base_type'] = 'PRODUCT';
        $result['id'] = $productNode -> nid;
        $result['title'] = $productNode -> title;
        $result['reason'] = 'Allowed Prefix should be defined before deploy';
      };
    }
  }

  return $result;

}

function _is_condition_duplicated($args) {
  $view = views_get_view('list_conditions_for_duplicate_check');
  $view -> set_display('panel_pane_1');
  $view -> set_arguments($args);
  $view -> execute();

  if (!empty($view -> result))
    return TRUE;
  return FALSE;
};

function is_machine_name($argStr) {
  // if (preg_match('/[^0-9a-zA-Z_]/', $argStr)) {
  if (preg_match('/[^0-9a-z_]/', $argStr)) {
    return FALSE;
  }
  return TRUE;
}

function product_catalog_form_node_validate($node, $form, &$form_state) {
	if ($form_state['values']['op'] == 'Delete') {
    switch($form['form_id']['#value']) {
      case 'carrier_mobile_node_form' :
        $view_result = views_get_view_result('list_carrier_mobile_reference', 'panel_pane_1', $node -> nid);
        if (count($view_result) > 0) {
          form_set_error('title', "You should remove the items referencing this carrier in numbering plan first!");
        }
        break;
      case 'roaming_country_node_form' :
        $view_result = views_get_view_result('list_roaming_country_reference', 'panel_pane_1', $node -> nid);
        if (count($view_result) > 0) {
          form_set_error('title', "You should remove the items referencing this country in roaming plan or roaming carrier first!");
        }
        break;
      case 'roaming_carrier_node_form' :
        $view_result = views_get_view_result('list_roaming_carrier_reference', 'panel_pane_1', $node -> nid);
        if (count($view_result) > 0) {
          form_set_error('title', "You should remove the items referencing this carrier in roaming plan first!");
        }
        break;
			case 'counter_node_form' :
				$view_result = views_get_view_result('list_counter_refereces', 'panel_pane_1', $node -> nid);
        if (count($view_result) > 0) {
          form_set_error('field_counter_id', "You should remove the items referencing this counter first!");
        }
        break;
			case 'timetable_node_form' :
				$view_result = views_get_view_result('list_timetable_reference', 'panel_pane_2', $node -> nid);
        if (count($view_result) > 0) {
          form_set_error('title', "You should remove the items referencing this timetable first!");
        }
        break;
      case 'number_special_node_form' :
				$view_result = views_get_view_result('list_number_special_reference', 'panel_pane_1', $node -> nid);
				if (count($view_result) > 0) {
          form_set_error('title', "You should remove the product referencing this special number scheme first!");
        }
        break;
    }
  } else {
    switch($form['form_id']['#value']) {
    	case 'conditionwhatcounter_node_form':
				$is_valid = TRUE;
				
				//value check. only integer is available
				if($is_valid){
					$value_count = count($form_state['values']['field_value']['und']);
					$is_empty = TRUE;
					for($i=0;$i<$value_count;$i++){
						$value = $form_state['values']['field_value']['und'][$i]['value'];
						if(!empty($value)){
							$is_empty = FALSE;
							break;
						}
					}
					if($is_empty){
						$target_element = 'field_value';
						$is_valid = FALSE;
						$fail_rasion = 'Value is required';
					}
				}
				
				if($is_valid){
					for($i=0;$i<$value_count;$i++){
						$value = $form_state['values']['field_value']['und'][$i]['value'];
						$target_element = 'field_value][und]['. $i .'][value';
						if(!empty($value) && !is_integer_string($value)){
							$is_valid = FALSE;
							$fail_rasion = 'Only Integer value is allowed';
							break;
						}else{
							$is_in_range = is_integer_between_range($value);
							if($is_in_range < 0){
								$is_valid = FALSE;
								$fail_rasion = 'It is less than Minimum Value -10000000000';
								break;
							}elseif($is_in_range > 0){
								$is_valid = FALSE;
								$fail_rasion = 'It is greater than Maximum Value 10000000000';
								break;
							}
						}
					}
				}
				
				$counter = node_load($form_state['values']['field_ref_counter']['und'][0]['nid']);
				$inputCounterSubUnitTypeTid = $form_state['values']['field_counter_sub_unit_type']['und'][0]['tid'];
				$counterUnitTypeTerm = taxonomy_term_load($counter->field_counter_unit_type['und'][0]['tid']);
				$counterSubUnitTypes = $counterUnitTypeTerm->field_ref_counter_sub_unit_type['und'];
				
				$foundFlag = FALSE;
				foreach($counterSubUnitTypes as $key => $value) {
				if( $value['tid'] == $inputCounterSubUnitTypeTid ) {
						$foundFlag = TRUE;
						break;
					}
				}
				if(!$foundFlag) {
					$target_element = 'field_counter_sub_unit_type';
					$is_valid = FALSE;
					$fail_rasion = "Unit Type should be matched to counter's unit type";
				}
				
				if(!$is_valid){
					form_set_error($target_element, $fail_rasion);
				}
				break;
				
	  case 'actionsetcounter_node_form':
	  case 'actionsetcounteronbonus_node_form':
	  case 'actionsetbonusonrecurringcharge_node_form':
	  	$counter = node_load($form_state['values']['field_ref_counter']['und'][0]['nid']);
	  	
	  	$inputCounterSubUnitTypeTid = $form_state['values']['field_counter_sub_unit_type']['und'][0]['tid'];
	  	$counterUnitTypeTerm = taxonomy_term_load($counter->field_counter_unit_type['und'][0]['tid']);
	  	$counterSubUnitTypes = $counterUnitTypeTerm->field_ref_counter_sub_unit_type['und'];
	  	
		$foundFlag = FALSE;
		foreach($counterSubUnitTypes as $key => $value) {
			if( $value['tid'] == $inputCounterSubUnitTypeTid ) {
	  			$foundFlag = TRUE;
	  		}
	  	}
	  	
	  	if(!$foundFlag) {
	  		form_set_error('field_counter_sub_unit_type', "Unit Type should be matched to counter's unit type");
	  	}
	  	
	  	break;
      case 'ocs_ussd_code_node_form' :
        // check USSD code format
        $valid_code = TRUE;
        $code = $form_state['values']['title'];
        if (substr($code, 0, 1) == '*' && substr($code, -1) == '#') {
          for ($i = 1; $i < strlen($code) - 1; $i++) {
            $c = substr($code, $i, 1);
            if (!(is_numeric($c) || $c == '*')) {
              $valid_code = FALSE;
              break;
            }
          }
        } else {
          $valid_code = FALSE;
        }

        if ($valid_code === FALSE) {
          form_set_error('title', t('Invalid USSD code format'));
        }

        // check if the ussd code exist already
        /*
        $query = new EntityFieldQuery();
        $result = $query -> entityCondition('entity_type', 'node') -> entityCondition('bundle', 'ocs_ussd_code') -> propertyCondition('title', $form_state['values']['title']) -> execute();
        
        if (!empty($result)) {
        
          // Create
          if(!isset($form['nid']['#value'])) {
          	form_set_error('title', t('USSD code @code exist already', array('@code' => $form_state['values']['title'])));
          } 
        }
        */
        break;
      case 'roaming_zone_node_form' :
        $isValid = TRUE;
        $targetElement = 'field_roaming_countries';

        $selectedCountries = array();
        foreach ($form_state['values']['field_roaming_countries']['und'] as $item) {
          if (isset($item['nid']))
            $selectedCountries[] = $item['nid'];
        }
        if (empty($selectedCountries)) {
          $failReason = 'Country is required information';
          $isValid = FALSE;
        } else {
          //check duplicated in other zone
          $view = views_get_view('list_roaming_zone');
          $view -> set_display('panel_pane_1');
          $selectedCountries = join('+', $selectedCountries);
          $args = array('0' => $selectedCountries);

          if (isset($form['nid']['#value'])) {
            $args['1'] = $form['nid']['#value'];
          }
          $view -> set_arguments($args);
          $view -> execute();
          if (count($view -> result) > 0) {
            $failReason = 'Selected countries is already taken by another zone';
            $isValid = FALSE;
          }
        }

        if (!$isValid) {
          form_set_error($targetElement, $failReason);
        }
        break;
      case 'prdattributeprefixrangeallowed_node_form' :
        $isValid = TRUE;
        $targetElement = 'field_prefix_range][und][';
        $totalRow = count($form_state['input']['field_prefix_range']['und']);

        $allowedPrefix = array();
        for ($i = 0; $i < $totalRow; $i++) {
          $base = $form_state['input']['field_prefix_range']['und'][$i]['field_base_prefix']['und'][0]['value'];
          $start = $form_state['input']['field_prefix_range']['und'][$i]['field_prefix_range_start']['und'][0]['value'];
          $end = $form_state['input']['field_prefix_range']['und'][$i]['field_prefix_range_end']['und'][0]['value'];

          if (empty($start) && empty($end)) {
            continue;
          }

          if (strlen($start) < 6) {
            $targetElement .= $i . '][field_prefix_range_start';
            $isValid = FALSE;
            $failReason = 'Rang Start should be 6 digits';
            break;
          }

          if (strlen($end) < 6) {
            $targetElement .= $i . '][field_prefix_range_end';
            $isValid = FALSE;
            $failReason = 'Rang End should be 6 digits';
            break;
          }

          if (intval($start) >= intval($end)) {
            $targetElement .= $i . '][field_prefix_range_start';
            $isValid = FALSE;
            $failReason = 'Rang Start should be smaller than Range End';
            break;
          }
          $allowedPrefix[$i] = array('start' => (string)$base . $start, 'end' => (string)$base . $end);
        }

        if ($isValid) {
          $targetElement = 'field_prefix_range][und][';

          for ($i = 0; $i < $totalRow; $i++) {
            $start = $allowedPrefix[$i]['start'];
            $end = $allowedPrefix[$i]['end'];

            for ($j = 0; $j < $totalRow; $j++) {

              if ($i == $j)
                continue;

              if ($start >= $allowedPrefix[$j]['start'] && $start <= $allowedPrefix[$j]['end']) {
                $targetElement .= $i . '][field_prefix_range_start';
                $isValid = FALSE;
                $failReason = 'Range Start should not be on other prefix record range';
                break;
              }

              if ($end >= $allowedPrefix[$j]['start'] && $end <= $allowedPrefix[$j]['end']) {
                $targetElement .= $i . '][field_prefix_range_end';
                $isValid = FALSE;
                $failReason = 'Range End should not be on other prefix record range';
                break;
              }
            }
            if (!$isValid)
              break;
          }
        }

        if (!$isValid) {
          form_set_error($targetElement, $failReason);
        }

        break;
      case 'numberspecialfactors_node_form' :
        $isDuplicatedPrefix = FALSE;
        //check duplicated in the form
        $prefixs = array();
        foreach ($form_state['input']['field_prefix']['und'] as $item) {
          if (strlen($item['value'] > 0)) {
            $prefixs[] = $item['value'];
          }
        }

        $countPrefixs = array_count_values($prefixs);
        foreach ($countPrefixs as $item) {
          if ($item > 1) {
            $isDuplicatedPrefix = TRUE;
            break;
          }
        }

        //check duplicated in other carrier
        if (!$isDuplicatedPrefix) {
          $view = views_get_view('list_numberspecial_child_node');
          $view -> set_display('panel_pane_8');
          $prefixArgs = join('+', $prefixs);
          $args = array('0' => $form['#node'] -> field_ref_numberspecial['und'][0]['nid'], '1' => $prefixArgs);

          if (isset($form['nid']['#value'])) {
            $args['2'] = $form['nid']['#value'];
          }
          $view -> set_arguments($args);
          $view -> execute();
          if (count($view -> result) > 0) {
            $isDuplicatedPrefix = TRUE;
          }
        }

        //set error msg to form if duplicated prefix found.
        if ($isDuplicatedPrefix) {
          form_set_error('field_prefix', 'Duplicated Prefix found!');
        }
        break;

      case 'idd_ratinggroup_node_form' :
				$isDuplicatedPrefix = FALSE;
        //check duplicated in the form
        $prefixs = array();
        foreach ($form_state['input']['field_prefix']['und'] as $item) {
          if (strlen($item['value'] > 0)) {
            $prefixs[] = $item['value'];
          }
        }

        $countPrefixs = array_count_values($prefixs);
        foreach ($countPrefixs as $item) {
          if ($item > 1) {
            $isDuplicatedPrefix = TRUE;
            break;
          }
        }

        //check duplicated in the carrier
        if (!$isDuplicatedPrefix) {
          $view = views_get_view('list_numberingplan_idd_ratinggroup');
          $view -> set_display('panel_pane_4');
          $prefixArgs = join('+', $prefixs);
          $args = array('0' => $form['#node'] -> field_ref_numberingplan_idd['und'][0]['nid'], '1' => $prefixArgs,
          	'2' => $form_state['values']['field_ref_carrier_mobile']['und'][0]['nid']);

          if (isset($form['nid']['#value'])) {
            $args['3'] = $form['nid']['#value'];
          }
          $view -> set_arguments($args);
          $view -> execute();
          if (count($view -> result) > 0) {
            $isDuplicatedPrefix = TRUE;
          }
        }

        //set error msg to form if duplicated prefix found.
        if ($isDuplicatedPrefix) {
          form_set_error('field_prefix', 'Duplicated Prefix found!');
        }
        break;
        
      case 'carrier_mobile_node_form' :
        $isDuplicated = FALSE;
        $failReason = '';
        //check duplicated in the form
        $prefixs = array();
        foreach ($form_state['input']['field_prefix_multiple']['und'] as $item) {
          if (strlen($item['value'] > 0)) {
            $prefixs[] = $item['value'];
          }
        }

        $countPrefixs = array_count_values($prefixs);
        foreach ($countPrefixs as $item) {
          if ($item > 1) {
            $isDuplicated = TRUE;
            $failReason = 'Duplicated Prefix found';
            break;
          }
        }

        //check duplicated in other carrier
        if (!$isDuplicated) {
          $view = views_get_view('list_carrier_mobile');
          $view -> set_display('panel_pane_4');
          $prefixArgs = join('+', $prefixs);
          $args = array('0' => $prefixArgs);
          if (isset($form['nid']['#value'])) {
            $args['1'] = $form['nid']['#value'];
          }
          $view -> set_arguments($args);
          $view -> execute();

          if (count($view -> result) > 0) {
            $isDuplicated = TRUE;

            $otherCarrierPrefix = array();
            foreach ($view->result[0]->field_field_prefix_multiple as $item) {
              $otherCarrierPrefix[] = $item['raw']['safe_value'];
            }
            $duplicatedPrefix = array_intersect($prefixs, $otherCarrierPrefix);
            $failReason = 'Duplicated Prefix ' . current($duplicatedPrefix) . ' found on another carrier ' . $view -> result[0] -> node_title;
          }
        }

        //set error msg to form if duplicated found.
        if ($isDuplicated) {
          form_set_error('field_prefix_multiple', $failReason);
        }
        break;
     
      case 'locationfactor_node_form' :
      	dsm($form_state['values'], 'values');
      	
      	break;
      case 'packetdynamicl4_node_form' :
        //check ip address is valid or not.
        $ipValues = $node -> field_ip['und'];
        unset($ipValues['add_more']);
        $isInvalidIP = FALSE;
        $isInvalidPort = FALSE;

        foreach ($ipValues as $item) {
          $ipStr = $item['value'];
          if (strlen($ipStr) > 0) {
            //check '/'
            $ipStr = explode('/', $ipStr);
            if (count($ipStr) != 2) {
              $isInvalidIP = TRUE;
              break;
            }
            //check .
            $ip = explode('.', $ipStr[0]);
            if (count($ip) != 4) {
              $isInvalidIP = TRUE;
              break;
            }
            //check ip numeric
            foreach ($ip as $digit) {
              //check digit
              if (!is_numeric($digit)) {
                $isInvalidIP = TRUE;
                break 2;
              }
              //check ip range
              if ($digit < 0 || $digit > 255) {
                $isInvalidIP = TRUE;
                break 2;
              }
            }
            //check network mask
            if (!is_numeric($ipStr[1])) {
              $isInvalidIP = TRUE;
              break;
            }
            //check network mask range
            if ($ipStr[1] < 0 || $ipStr[1] > 25) {
              $isInvalidIP = TRUE;
              break;
            }
          }
        }

        $portValues = $node -> field_port['und'];
        unset($portValues['add_more']);
        foreach ($portValues as $item) {
          $portStr = $item['value'];
          if (strlen($portStr)) {
            //check digit
            if (!is_numeric($portStr)) {
              $isInvalidPort = TRUE;
              break;
            }
            if ($portStr < 0) {
              $isInvalidPort = TRUE;
              break;
            }
          }
        }

        if ($isInvalidIP) {
          form_set_error('field_ip', 'Invalid IP format');
        }
        if ($isInvalidPort) {
          form_set_error('field_port', 'Invalid Port');
        }
        break;

      case 'conditionwheremacaddress_node_form' :
        if (is_macaddress($form_state['values']['field_mac_address']['und'][0]['value']) == FALSE) {
          drupal_set_message("Only 3 bytes of Mac Address Format is allowed", 'error');
          form_set_error('Only 3 bytes of Mac Address Format is allowed');
        }
        break;

      case 'conditionwheremacaddress_node_form' :
        break;

      case 'timetablefactors_node_form' :
        if ($form_state['values']['field_timeslot_from_hour']['und'][0]['value'] > $form_state['values']['field_timeslot_to_hour']['und'][0]['value']) {
          form_set_error('Reference', 'FROM is greater than TO');
        } else if ($form_state['values']['field_timeslot_from_hour']['und'][0]['value'] == $form_state['values']['field_timeslot_to_hour']['und'][0]['value']) {
          if ($form_state['values']['field_timeslot_from_minutes']['und'][0]['value'] > $form_state['values']['field_timeslot_to_minutes']['und'][0]['value']) {
            form_set_error('Reference', 'FROM is greater than TO');
          }
          if ($form_state['values']['field_timeslot_from_minutes']['und'][0]['value'] == $form_state['values']['field_timeslot_to_minutes']['und'][0]['value']) {
            form_set_error('Reference', 'FROM and TO has same value');
          }
        } else if ($form_state['values']['field_timeslot_to_hour']['und'][0]['value'] === '24' && $form_state['values']['field_timeslot_to_minutes']['und'][0]['value'] > 0) {
          form_set_error('Reference', 'TO Hour(24) should have minute value 0');
        } else if ($form_state['values']['field_timeslot_from_hour']['und'][0]['value'] === '24') {
          form_set_error('Reference', 'FROM Hour(24) is not allowed');
        }
        break;

      case 'conditionwhensubscriptionday_node_form' :
        $operationTerm = taxonomy_term_load($form_state['values']['field_rating_operation_for_date']['und'][0]['tid']);
        if ($operationTerm -> name == 'Is between' && ($form_state['values']['field_start_date']['und'][0]['value'] > $form_state['values']['field_end_date']['und'][0]['value'])) {
          drupal_set_message("Start date should be less than End Date", "error");
          form_set_error('Start date should be less than End Date');
        }
        break;

      case 'conditionwhenactivedays_node_form' :
        $operationTerm = taxonomy_term_load($form_state['values']['field_rating_operation_for_date']['und'][0]['tid']);
        if ($operationTerm -> name == 'Is between' && $form_state['values']['field_activedays_start']['und'][0]['value'] > $form_state['values']['field_activedays_end']['und'][0]['value']) {
          drupal_set_message("Start days should be less than End days", "error");
          form_set_error('Start days should be less than End days');
        }
        break;

      case 'actionpricechargerecurring_node_form' :

        // Create일 경우,  time_t로 unique를 체크.
        // Edit일 경우, 기존에 존재하는 것이 있는지를 확인하여 unique체크
        if (isset($form['nid']['#value'])) {
          $nodeNid = $form['nid']['#value'];
          $recurringId = $form_state['values']['field_recurring_charge_id']['und'][0]['value'];

          $params = array('0' => $nodeNid, '1' => $recurringId);
          $viewResult = views_get_view_result('list_actionpricechargerecurring', 'panel_pane_2', $params);

          if (!empty($viewResult)) {
            drupal_set_message("Recurring ID should be unique", "error");
            form_set_error('Recurring ID should be unique');
          }
          if (!is_machine_name($recurringId)) {
            drupal_set_message("Only letters and underscore is allowed for recurring id", 'error');
            form_set_error("Only letters and underscore is allowed for recurring id");
          }
        }
        break;

      case 'productgroup_node_form' :
        $productGroupId = $form_state['values']['field_product_group_id']['und'][0]['value'];

        // Create
        if (!isset($form['nid']['#value'])) {
          if (!is_machine_name($productGroupId)) {
            form_set_error('field_product_group_id', "Only letters and underscore is allowed for product group id");
          }
        }
        break;

      case 'productchange_node_form' :
        $productChangeId = $form_state['values']['field_product_change_id']['und'][0]['value'];

        // Create
        if (!isset($form['nid']['#value'])) {
          if (!is_machine_name($productChangeId)) {
            form_set_error('field_product_change_id', "Only letters and underscore is allowed for product change scheme id");
          }
        }
        break;

      case 'counter_node_form' :
        if (!is_machine_name($form_state['values']['field_counter_id']['und'][0]['value'])) {
          form_set_error('field_counter_id', "Only letters and underscore is allowed for counter id");
        }

        // counter id range validataion
        $counterType = taxonomy_term_load($form_state['values']['field_counter_type']['und'][0]['tid']);
        $counterId = $form_state['values']['field_counter_id']['und'][0]['value'];
        if ($counterType -> name == 'Rollover') {
          if ($counterId < 1000000 && $counterId > 2000000) {
            drupal_set_message("rollover counter id should be between 1000000 and 2000000", 'error');
            form_set_error('rollover counter id should be between 1000000 and 2000000');
          }
          $counterGroupTerm = taxonomy_term_load($form_state['values']['field_counter_group']['und'][0]['tid']);
          /*
           if($counterGroupTerm->name == 'REMAINS') {
           drupal_set_message("Rollover Counter cannot be the 'REMAINS' counter group",'error');
           form_set_error("Rollover Counter cannot be the 'REMAINS' counter group");
           }
           */

        } else {
          $counterGroupTerm = taxonomy_term_load($form_state['values']['field_counter_group']['und'][0]['tid']);
          $counterUnitTerm = taxonomy_term_load($form_state['values']['field_counter_unit_type']['und'][0]['tid']);
          if (($counterGroupTerm -> name == 'REMAINS') && ($counterUnitTerm -> name != 'Money')) {
            // drupal_set_message("Only 'Money' type counter can be 'REMAINS' counter group", 'error');
            form_set_error('field_counter_group', "Only 'Money' type counter can be 'REMAINS' counter group");
          }

          if ($counterId >= 1000000) {
            // drupal_set_message('counter id should be less than 1000000');
            form_set_error('field_counter_id', 'counter id should be less than 1000000');
          }
        }
        break;

      case 'vouchercardtype_node_form' :
        if (!is_machine_name($form_state['values']['field_voucher_id']['und'][0]['value'])) {
          form_set_error('field_voucher_id', "Only letters and underscore is allowed for voucher card type id");
        }

        if (!is_numeric($form_state['values']['field_voucher_id']['und'][0]['value'])) {
          form_set_error('field_voucher_id', "Only Number is allowed for ID");
        }

        $voucherCardTypeTerm = taxonomy_term_load($form_state['values']['field_ref_voucher_type']['und'][0]['tid']);

        if ($voucherCardTypeTerm -> name == 'Discount') {
          if (empty($form_state['values']['field_ref_product_for_disvoucher']) || empty($form_state['values']['field_ref_product_for_disvoucher']['und']) || empty($form_state['values']['field_ref_product_for_disvoucher']['und'][0]) || empty($form_state['values']['field_ref_product_for_disvoucher']['und'][0]['nid'])) {
            form_set_error('field_ref_product_for_disvoucher', "You should select the product mapped by the discount coupon");
          } else {
            if (count($form_state['values']['field_ref_product_for_disvoucher']['und']) > 1) {
              form_set_error('field_ref_product_for_disvoucher', "You should select only one mapping product");
            }
          }

        }
        break;

      case 'simpleproductoffering_node_form' :
        if (!is_machine_name($form_state['values']['field_product_id']['und'][0]['value'])) {
          form_set_error('field_product_id', "Only lowercase letter, number and underscore are allowed for product id");
        }

        $fieldShortCode = $form_state['values']['field_short_code']['und'][0]['value'];
        if (!is_machine_name($fieldShortCode)) {
          form_set_error('field_short_code', "Only lowercase letter, number and underscore are allowed for short code");
        }

        $fieldBillingTypeTid = $form_state['values']['field_billing_type']['und'][0]['tid'];

        // create 시에만 확인
        if (!isset($form['nid']['#value'])) {
          $viewResult = views_get_view_result('list_product', 'panel_pane_2', $fieldBillingTypeTid, $fieldShortCode);

          if (count($viewResult) > 0) {
            form_set_error('field_short_code', "this short code value is already used. Try different ");
          }
        }

        $prdTypeTerm = taxonomy_term_load($form_state['values']['field_product_type']['und'][0]['tid']);
        if (empty($prdTypeTerm)) {
          $paths = explode('/', $_SERVER['HTTP_REFERER']);
          $prdTypeTerm = current(taxonomy_get_term_by_name($paths[5], 'prdtype'));
        }

        if ($prdTypeTerm -> name == 'CUG') {
          if (empty($form_state['values']['field_cug_group_type']) || empty($form_state['values']['field_cug_group_type']['und']) || empty($form_state['values']['field_cug_group_type']['und'][0]) || empty($form_state['values']['field_cug_group_type']['und'][0]['tid'])) {
            form_set_error('field_cug_group_type', "CUG Group Type is required");
          }

          if (empty($form_state['values']['field_cug_customer_type']) || empty($form_state['values']['field_cug_customer_type']['und']) || empty($form_state['values']['field_cug_customer_type']['und'][0]) || empty($form_state['values']['field_cug_customer_type']['und'][0]['tid'])) {
            form_set_error('field_cug_customer_type', "CUG Customer Type field is required");
          }
        }

        // expire date type이 설정되어있는데, expire date값이 없으면 에러
        $expireDateTypeTerm = isset($form_state['values']['field_expire_date_type']['und'][0]['tid']) ? taxonomy_term_load($form_state['values']['field_expire_date_type']['und'][0]['tid']) : NULL;

        if (isset($expireDateTypeTerm)) {

          if ($expireDateTypeTerm -> name == 'Hour') {

            if (empty($form_state['values']['field_expire_date_for_hour']['und'][0]['value'])) {
              form_set_error('field_expire_date_for_hour', "Expire Time Value is required");
            }

          } else {

            if (empty($form_state['values']['field_expire_date']['und'][0]['value'])) {
              form_set_error('field_expire_date', "Expire Time Value is required");
            }
          }
        }
        // next join confirm이 설정되어있는데, next join product값이 없으면 에러

        //check exclusivessness and downgrade penalty
        if (isset($form_state['values']['field_exclusiveness']['und'])) {
          $isExist = FALSE;
          $downgradePenaltyViewResult = views_get_view_result('list_product_downgrade_penalty', 'panel_pane_2', $form['#node'] -> nid);

          foreach ($form_state['values']['field_exclusiveness']['und'] as $item) {
            $selectedNids[] = $item['nid'];
          }

          foreach ($downgradePenaltyViewResult as $item) {
            if (in_array($item -> field_field_ref_target_product[0]['raw']['nid'], $selectedNids)) {
              $isExist = TRUE;
              $existName = $item -> field_field_ref_target_product[0]['raw']['node'] -> title;
              break;
            }
          }

          if ($isExist) {
            drupal_set_message($existName . " is defined in Product Downgrade Penlaty", 'error');
            form_set_error("hhh");
          }
        }

        break;
      case 'prdnonusagerecurringbonusscheme_node_form' :
        $bonus_cycle_types = array('0' => 'None', '1' => 'Daily', '2' => 'Weekly', '4' => 'Monthly');

        $bonus_cycle_type = $bonus_cycle_types[$form_state['values']['field_bonus_cycle_type']['und'][0]['value']];

        switch($bonus_cycle_type) {
          case 'Weekly' :
            $charging_day_week = $form_state['values']['field_rcrr_charging_day_week'];
            if (empty($charging_day_week) || empty($charging_day_week['und'][0]['value'])) {
              // drupal_set_message("Day of week should be selected", 'error');
              form_set_error('field_rcrr_charging_day_week', "Day of week should be selected");
            }

            break;

          case 'Monthly' :
            $charging_day_month = $form_state['values']['field_rcrr_charging_day_monthly'];
            if (empty($charging_day_month) || empty($charging_day_month['und'][0]['value'])) {
              form_set_error('field_rcrr_charging_day_monthly', "Day of Monthl should be selected");
            }

            break;
        }
        break;

      case 'depositschemefactors_node_form' :

        // create
        if (!isset($form['nid']['#value'])) {
          $ref_depositscheme = $form_state['build_info']['args'][0] -> field_ref_depositscheme['und'][0]['nid'];
          $title = $form_state['input']['title'];

          $view = views_get_view('list_depositschemefactors');
          $view -> set_display('panel_pane_6');
          $view -> set_arguments(array('0' => $ref_depositscheme, '1' => $title));
          $view -> execute();

          if (!empty($view -> result)) {
            drupal_set_message("Deposit factors name should be unique");
            form_set_error('Deposit factors name should be unique');
          }
        }

        if ($form_state['values']['field_ref_thres_counter_acc']['und'][0]['nid'] == $form_state['values']['field_ref_thres_counter_limit']['und'][0]['nid']) {
          // drupal_set_message("Accumulating and Limit Counter should be different");
          form_set_error('field_ref_thres_counter_acc', 'Accumulating and Limit Counter should be different');
        }

        $counterUnitTypeTid = $form_state['values']['field_counter_unit_type']['und'][0]['tid'];
        $accCounterNode = node_load($form_state['values']['field_ref_thres_counter_acc']['und'][0]['nid']);
        $limitCounterNode = node_load($form_state['values']['field_ref_thres_counter_limit']['und'][0]['nid']);

        if ($counterUnitTypeTid != $accCounterNode -> field_counter_unit_type['und'][0]['tid']) {
          form_set_error('field_ref_thres_counter_acc', 'Accumulated Counter Unit is different');
        }
        if ($counterUnitTypeTid != $limitCounterNode -> field_counter_unit_type['und'][0]['tid']) {
          form_set_error('field_ref_thres_counter_limit', 'Limit Counter Unit is different');
        }
        break;
    }

    // condition 중복 체크. 동일한 condition set에 같은 type의 condition이 있는지를 확인하여 봄.
    if (strncmp($form['form_id']['#value'], 'conditionwh', 11) == 0) {

      // counter 관련 조건은 중복 추가 가능함.
      if ($form['form_id']['#value'] == 'conditionwhatcounter_node_form')
        return;

      // create일 때, 중복 체크
      if (!isset($form['nid']['#value'])) {

        if (!empty($form_state['build_info']['args'][0] -> field_parent_node)) {
          $args = array('0' => $form_state['build_info']['args'][0] -> type, '1' => $form_state['build_info']['args'][0] -> field_parent_node['und'][0]['nid']);
          // $args = array('0' => $form_state['build_info']['args'][0]->
          $isDuplicated = _is_condition_duplicated($args);

          if ($isDuplicated > 0) {
            drupal_set_message("Same condition type exists in condition set", "error");
            form_set_error('Same condition type exists in condition set');
          }
        }
      } // only in create
    }

  }
}

function check_same_type_of_call_exist($form, $form_state) {
  $nodeType = $form['type']['#value'];
  $value = $form['field_new_type_of_call']['und'][0]['value']['#default_value'];

  $isAnotherValueExist = _check_same_type_of_call_exist($nodeType, $value);

  if ($isAnotherValueExist !== NULL) {
    if ($isAnotherValueExist === FALSE) {// 바뀌기 전 값을 가지고 있는 TOC가 없을 경우 child 에 대해 TOC 같이 변경해주어야 함
      switch($nodeType) {
        case 'idd_exit' :
          $view = views_get_view('query_numberingplan_idd_country_by_toc');
          $view -> set_arguments(array('0' => $form_state['numberingplan_idd_nid'], '1' => $value));
          $view -> execute();
          foreach ($view->result as $item) {
            $country_node = node_load($item -> node_field_data_field_ref_idd_country_nid);
            $country_node -> field_type_of_call['und'][0]['safe_value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
            $country_node -> field_type_of_call['und'][0]['value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
            node_save($country_node);
          }
          break;
        case 'idd_country' :
          $view = views_get_view('query_numberingplan_idd_ratinggroup_by_toc');
          $view -> set_arguments(array('0' => $form_state['numberingplan_idd_nid'], '1' => $value));
          $view -> execute();
          foreach ($view->result as $item) {
            $ratinggroup_node = node_load($item -> node_field_data_field_ref_idd_ratinggroup_nid);
            $ratinggroup_node -> field_type_of_call['und'][0]['safe_value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
            $ratinggroup_node -> field_type_of_call['und'][0]['value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
            node_save($ratinggroup_node);
          }
          break;
        case 'domestic_npa' :
          $view = views_get_view('query_numberingplan_domestic_area_by_toc');
          $view -> set_arguments(array('0' => $form_state['numberingplan_domestic_nid'], '1' => $value));
          $view -> execute();
          foreach ($view->result as $item) {
            $area_node = node_load($item -> node_field_data_field_ref_domestic_area_nid);
            $area_node -> field_type_of_call['und'][0]['safe_value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
            $area_node -> field_type_of_call['und'][0]['value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
            node_save($area_node);
          }
          break;
      }

    }
  }
}

function _check_same_type_of_call_exist($nodeType, $value) {
  if (!isset($nodeType)) {
    drupal_set_message($message = 'Can not find nodeType.', $type = 'error');
    return NULL;
  }
  if (!isset($value)) {
    drupal_set_message($message = 'Can not find TOC value.', $type = 'error');
    return NULL;
  }

  switch($nodeType) {
    case 'idd_exit' :
      $viewName = 'query_numberingplan_idd_exit_by_new_toc';
      break;
    case 'idd_country' :
      $viewName = 'query_numberingplan_idd_country_by_new_toc';
      break;
    case 'domestic_npa' :
      $viewName = 'query_numberingplan_domestic_npa_by_new_toc';
      break;
  }

  if (!isset($viewName))
    return NULL;

  $view = views_get_view($viewName);
  $view -> set_arguments(array('0' => $value));
  $view -> execute();

  if (count($view -> result) > 0) {
    return TRUE;
  }

  return FALSE;
}

function _make_timeslot_for_validate_timetable($nid, $dayDelimiter, $hourRange, $minuteRange, $minuteScale) {

  //set default timeslot for validation checking
  $timeslot = array();
  foreach ($dayDelimiter as $day) {
    $timeslot[$day] = array();
    for ($i = 0; $i < $hourRange; $i++) {
      $timeslot[$day][$i] = array();
      for ($j = 0; $j < $minuteRange; $j = $j + $minuteScale) {
        $timeslot[$day][$i][$j] = FALSE;
      }
    }
  }

  //load all timetablefactors
  $view = views_get_view('list_timetablefactors');
  $view -> set_display('panel_pane_2');
  $view -> set_arguments(array('0' => $nid));
  $view -> execute();

  foreach ($view->result as $item) {

    $fromHour = $item -> field_field_timeslot_from_hour[0]['raw']['value'];
    $fromMinute = $item -> field_field_timeslot_from_minutes[0]['raw']['value'];
    $toHour = $item -> field_field_timeslot_to_hour[0]['raw']['value'];
    $toMinute = $item -> field_field_timeslot_to_minutes[0]['raw']['value'];
    if ($item -> field_field_holiday[0]['raw']['value'] == 'HOLIDAY') {
      _make_timeslot_for_validate_timetable_sub($timeslot['HOLIDAY'], $fromHour, $fromMinute, $toHour, $toMinute, $minuteRange, $minuteScale, $hourRange);
    } else {
      if ($item -> field_field_week_mon[0]['raw']['value']) {
        _make_timeslot_for_validate_timetable_sub($timeslot['MON'], $fromHour, $fromMinute, $toHour, $toMinute, $minuteRange, $minuteScale, $hourRange);
      }
      if ($item -> field_field_week_tue[0]['raw']['value']) {
        _make_timeslot_for_validate_timetable_sub($timeslot['TUE'], $fromHour, $fromMinute, $toHour, $toMinute, $minuteRange, $minuteScale, $hourRange);
      }
      if ($item -> field_field_week_wed[0]['raw']['value']) {
        _make_timeslot_for_validate_timetable_sub($timeslot['WED'], $fromHour, $fromMinute, $toHour, $toMinute, $minuteRange, $minuteScale, $hourRange);
      }
      if ($item -> field_field_week_thu[0]['raw']['value']) {
        _make_timeslot_for_validate_timetable_sub($timeslot['THU'], $fromHour, $fromMinute, $toHour, $toMinute, $minuteRange, $minuteScale, $hourRange);
      }
      if ($item -> field_field_week_fri[0]['raw']['value']) {
        _make_timeslot_for_validate_timetable_sub($timeslot['FRI'], $fromHour, $fromMinute, $toHour, $toMinute, $minuteRange, $minuteScale, $hourRange);
      }
      if ($item -> field_field_week_sat[0]['raw']['value']) {
        _make_timeslot_for_validate_timetable_sub($timeslot['SAT'], $fromHour, $fromMinute, $toHour, $toMinute, $minuteRange, $minuteScale, $hourRange);
      }
      if ($item -> field_field_week_sun[0]['raw']['value']) {
        _make_timeslot_for_validate_timetable_sub($timeslot['SUN'], $fromHour, $fromMinute, $toHour, $toMinute, $minuteRange, $minuteScale, $hourRange);
      }
    }
  }
  return $timeslot;
}

function _make_timeslot_for_validate_timetable_sub(&$timeslotDay, $fromHour, $fromMinute, $toHour, $toMinute, $minuteRange, $minuteScale, $hourRange) {
  for ($hour = $fromHour; $hour <= $toHour; $hour++) {
    $startMinute = 0;
    $endMinute = $minuteRange;
    //if($fromHour == 0 && $toHour == 0 && $fromMinute == 0 && $toMinute == 0){
    //	$toHour = $hourRange;
    //}else{
    if ($hour == $fromHour)
      $startMinute = $fromMinute;
    if ($hour == $toHour)
      $endMinute = $toMinute;
    //}
    for ($minute = $startMinute; $minute < $endMinute; $minute = $minute + $minuteScale) {
      if ($timeslotDay[$hour][$minute]) {
        $timeslotDay[$hour][$minute] = 'duplicated';
      } else {
        $timeslotDay[$hour][$minute] = TRUE;
      }
    }
  }
}

function validate_timetable_form($form, &$form_state) {
  $dayDelimiter = array('MON', 'TUE', 'WED', 'THU', 'FRI', 'SAT', 'SUN', 'HOLIDAY');
  $hourRange = 24;
  $minuteRange = 60;
  $minuteScale = 10;

  $timeslot = _make_timeslot_for_validate_timetable($form_state['build_info']['args'][0], $dayDelimiter, $hourRange, $minuteRange, $minuteScale);

  $form['duplicated'] = array('#type' => 'fieldset', '#title' => 'Duplicated', '#weight' => 1, '#collapsible' => TRUE, '#collapsed' => FALSE, );
  $form['empty'] = array('#type' => 'fieldset', '#title' => 'Not Defined', '#weight' => 2, '#collapsible' => TRUE, '#collapsed' => FALSE, );

  $header = array( array('data' => 'Day'), array('data' => 'Hour'), array('data' => 'Minute'), );

  $emptyRows = array();
  $duplicatedRows = array();

  $countDays = count($dayDelimiter);

  for ($i = 0; $i < $countDays; $i++) {
    for ($j = 0; $j < $hourRange; $j++) {
      for ($k = 0; $k < $minuteRange; $k = $k + $minuteScale) {
        if ($timeslot[$dayDelimiter[$i]][$j][$k] === 'duplicated') {
          $duplicatedRows[] = array($dayDelimiter[$i], $j, $k . '-' . ($k + 9));
        } else if ($timeslot[$dayDelimiter[$i]][$j][$k] === FALSE) {
          $emptyRows[] = array($dayDelimiter[$i], $j, $k . '-' . ($k + 9));
        }
      }
    }
  }
  $duplicatedTableArgs = array('header' => $header, 'rows' => $duplicatedRows, 'sticky' => 'sticky', 'empty' => 'There are no duplicated', 'attributes' => array(), 'colgroups' => array(), 'caption' => NULL, );
  $duplicatedTableThemeResult = theme_table($duplicatedTableArgs);

  $emptyTableArgs = array('header' => $header, 'rows' => $emptyRows, 'sticky' => 'sticky', 'empty' => 'There are no empty', 'attributes' => array(), 'colgroups' => array(), 'caption' => NULL, );
  $emptyTableThemeResult = theme_table($emptyTableArgs);

  $form['duplicated']['rows'] = array('#type' => 'markup', '#markup' => $duplicatedTableThemeResult);

  $form['empty']['rows'] = array('#type' => 'markup', '#markup' => $emptyTableThemeResult);

  $duplicatedRowCount = count($duplicatedRows);
  $emptyRowCount = count($emptyRows);
  $msg = '<div id="messages">';
  if ($duplicatedRowCount > 0 || $emptyRowCount > 0) {
    $msg .= '<div class="messages error"><h2 class="element-invisible">Error message</h2><ul>';
    if ($duplicatedRowCount > 0)
      $msg .= '<li>Duplicated timetablefactors exist</li>';
    if ($emptyRowCount > 0)
      $msg .= '<li>Not defined timetablefactors exist</li>';
    $msg .= '</ul></div></div>';
  } else if ($duplicatedRowCount == 0 && $emptyRowCount == 0) {
    $msg .= '<div class="messages status"><h2 class="element-invisible">Status message</h2>Validation Test Passed!</div></div>';
  }

  $form['message'] = array('#type' => 'markup', '#markup' => $msg, '#weight' => 0, );
  return $form;
}
