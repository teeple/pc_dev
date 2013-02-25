<?php
function _is_condition_duplicated($args) {
	$view = views_get_view('list_conditions_for_duplicate_check');
	$view->set_display('panel_pane_1');
	$view->set_arguments($args);
	$view->execute();
	
	if(!empty($view->result)) return TRUE;
	return FALSE;
};

function is_machine_name($argStr) {
	if(preg_match('/[^0-9a-zA-Z_]/', $argStr)) {
		return FALSE;
	}
	return TRUE;
}

function product_catalog_form_node_validate($node, $form, &$form_state){

	switch($form['form_id']['#value']){
        case 'packetdynamicl4_node_form':
            //dsm($node,'$node');
            //check ip address is valid or not.
            $ipValues = $node->field_ip['und'];
            unset($ipValues['add_more']);
            $isInvalidIP = FALSE;
            $isInvalidPort = FALSE;
            
            foreach($ipValues as $item){
                $ipStr = $item['value'];
                if(strlen($ipStr) > 0){
                    //check '/'
                    $ipStr = explode('/',$ipStr);
                    if(count($ipStr) != 2){
                        $isInvalidIP = TRUE;
                        break;
                    }
                    //check .
                    $ip = explode('.',$ipStr[0]);
                    if(count($ip) != 4){
                        $isInvalidIP = TRUE;
                        break;
                    }
                    //check ip numeric
                    foreach($ip as $digit){
                        //check digit
                        if(!is_numeric($digit)){
                            $isInvalidIP = TRUE;
                            break 2;
                        }
                        //check ip range
                        if($digit < 0 || $digit > 255){
                             $isInvalidIP = TRUE;
                            break 2;
                        }
                    }
                    //check network mask
                    if(!is_numeric($ipStr[1])){
                        $isInvalidIP = TRUE;
                        break;
                    }
                    //check network mask range
                    if($ipStr[1] < 0 || $ipStr[1] > 25){
                        $isInvalidIP = TRUE;
                        break;
                    }
                }
            }

            $portValues = $node->field_port['und'];
            unset($portValues['add_more']);
            foreach($portValues as $item){
                $portStr = $item['value'];
                if(strlen($portStr)){
                    //check digit
                    if(!is_numeric($portStr)){
                        $isInvalidPort = TRUE;
                        break;
                    }
                    if($portStr < 0){
                        $isInvalidPort = TRUE;
                        break;
                    }
                }
            }
            
            if($isInvalidIP){
                form_set_error('field_ip','Invalid IP format');
            }
            if($isInvalidPort){
                form_set_error('field_port','Invalid Port');
            }
            break;
		case 'conditionwheremacaddress_node_form':
			if(is_macaddress($form_state['values']['field_mac_address']['und'][0]['value']) == FALSE) {
				drupal_set_message("Only 3 bytes of Mac Address Format is allowed", 'error');
				form_set_error('Only 3 bytes of Mac Address Format is allowed');			
			}
			break;
		case 'conditionwheremacaddress_node_form':
			break;
		case 'timetablefactors_node_form':
			if($form_state['values']['field_timeslot_from_hour']['und'][0]['value'] > $form_state['values']['field_timeslot_to_hour']['und'][0]['value']){
				form_set_error('Reference','FROM is greater than TO');
			}else if($form_state['values']['field_timeslot_from_hour']['und'][0]['value'] == $form_state['values']['field_timeslot_to_hour']['und'][0]['value']){
				if($form_state['values']['field_timeslot_from_minutes']['und'][0]['value'] > $form_state['values']['field_timeslot_to_minutes']['und'][0]['value']){
					form_set_error('Reference','FROM is greater than TO');
				}
				if($form_state['values']['field_timeslot_from_minutes']['und'][0]['value'] == $form_state['values']['field_timeslot_to_minutes']['und'][0]['value']){
					form_set_error('Reference','FROM and TO has same value');
				}
			}else if($form_state['values']['field_timeslot_to_hour']['und'][0]['value'] === '24' && $form_state['values']['field_timeslot_to_minutes']['und'][0]['value'] > 0){
				form_set_error('Reference','TO Hour(24) should have minute value 0');
			}else if($form_state['values']['field_timeslot_from_hour']['und'][0]['value'] === '24'){
				form_set_error('Reference','FROM Hour(24) is not allowed');
			}

		case 'conditionwhensubscriptionday_node_form':
			$operationTerm = taxonomy_term_load($form_state['values']['field_rating_operation_for_date']['und'][0]['tid']);
			if($operationTerm->name == 'Is between' && 
				($form_state['values']['field_start_date']['und'][0]['value'] > $form_state['values']['field_end_date']['und'][0]['value'])) {
				drupal_set_message("Start date should be less than End Date", "error");
				form_set_error('Start date should be less than End Date');
			}
			break;
		case 'conditionwhenactivedays_node_form':
			$operationTerm = taxonomy_term_load($form_state['values']['field_rating_operation_for_date']['und'][0]['tid']);
			if($operationTerm->name == 'Is between' && 
				$form_state['values']['field_activedays_start']['und'][0]['value'] > $form_state['values']['field_activedays_end']['und'][0]['value']) {
				drupal_set_message("Start days should be less than End days", "error");
				form_set_error('Start days should be less than End days');
			}
			break;
		case 'counter_node_form':
			// In case Delete Confirmation
			// 
			if($form_state['values']['op'] == 'Delete') {
				$view = views_get_view('list_reverse_reference_items');
				$view->set_display('panel_pane_1');
				$view->set_arguments(array('0' => $form['nid']['#value']));
				$view->execute();
				
				if(!empty($view->result)) {
					drupal_set_message("You should remove the items referencing this counter FIRST! ",'error');
					form_set_error("You should remove the items referencing this counter FIRST!");
					drupal_goto('Common/counter/edit/Optional/53409');
				}
				return;
			}
			
			// counter id range validataion
			$counterType = taxonomy_term_load($form_state['values']['field_counter_type']['und'][0]['tid']);
			$counterId = $form_state['values']['field_counter_id']['und'][0]['value'];
			if($counterType->name == 'Rollover') {
				if($counterId < 1000000 && $counterId > 2000000) {
					drupal_set_message("rollover counter id should be between 1000000 and 2000000",'error');
					form_set_error('rollover counter id should be between 1000000 and 2000000');
				}
				$counterGroupTerm = taxonomy_term_load($form_state['values']['field_counter_group']['und'][0]['tid']);
				if($counterGroupTerm->name == 'REMAINS') {
					drupal_set_message("Rollover Counter cannot be the 'REMAINS' counter group",'error');
					form_set_error("Rollover Counter cannot be the 'REMAINS' counter group");
				}
				
			} else {
				$counterGroupTerm = taxonomy_term_load($form_state['values']['field_counter_group']['und'][0]['tid']);
				$counterUnitTerm = taxonomy_term_load($form_state['values']['field_counter_unit_type']['und'][0]['tid']);
				if( ($counterGroupTerm->name == 'REMAINS') && ($counterUnitTerm->name != 'Money') ) {
					drupal_set_message("Only 'Money' type counter can be 'REMAINS' counter group",'error');
					form_set_error("Only 'Money' type counter can be 'REMAINS' counter group");
				}
				
				if($counterId >= 1000000) {
					drupal_set_message('counter id should be less than 1000000');
					form_set_error('counter id should be less than 1000000');
				}
			}
			break;
		
		case 'counter_node_form':
			if(!is_machine_name($form_state['values']['field_counter_id']['und'][0]['value'])) {
					drupal_set_message("Only letters and underscore is allowed for counter id",'error');
					form_set_error("Only letters and underscore is allowed for counter id");
				}
			break;
			
		case 'vouchercardtype_node_form':
			if(!is_machine_name($form_state['values']['field_voucher_id']['und'][0]['value'])) {
				drupal_set_message("Only letters and underscore is allowed for voucher card type  id",'error');
				form_set_error("Only letters and underscore is allowed for voucher card type id");
			}
			break;
			
		case 'simpleproductoffering_node_form':
			if(!is_machine_name($form_state['values']['field_product_id']['und'][0]['value'])) {
				drupal_set_message("Only letters and underscore is allowed for product id",'error');
				form_set_error("Only letters and underscore is allowed for product id");
			}
			break;
			
   	case 'depositschemefactors_node_form':
		  // create
		  if(!isset($form['nid']['#value'])){
				$ref_depositscheme = $form_state['build_info']['args'][0]->field_ref_depositscheme['und'][0]['nid'];
				$title = $form_state['input']['title'];
				
				$view = views_get_view('list_depositschemefactors');
				$view->set_display('panel_pane_6');
		    $view->set_arguments(array('0' => $ref_depositscheme,
		    													'1' => $title));
	  	  $view->execute();
	
				if(!empty($view->result) ) {
						 drupal_set_message("Deposit factors name should be unique");
			       form_set_error('Deposit factors name should be unique');
			  }
			}
			break;
	}
	
	// condition 중복 체크. 동일한 condition set에 같은 type의 condition이 있는지를 확인하여 봄.
	if(strncmp($form['form_id']['#value'], 'conditionwh', 11) ==  0) {
	
		// counter 관련 조건은 중복 추가 가능함.
		if($form['form_id']['#value'] == 'conditionwhatcounter_node_form') return;
		
		// create일 때마 체크하도록 함
		if(!isset($form['nid']['#value']) ) {
			
			if(!empty($form_state['build_info']['args'][0]->field_parent_node)) {
				$args = array( '0' => $form_state['build_info']['args'][0]->type,
											'1' => $form_state['build_info']['args'][0]->field_parent_node['und'][0]['nid']);
				// $args = array('0' => $form_state['build_info']['args'][0]->
				$isDuplicated = _is_condition_duplicated($args);
				
				if($isDuplicated > 0) {
					drupal_set_message("Same condition type exists in condition set", "error");
					form_set_error('Same condition type exists in condition set');
				}
			}
		} // only in create
	}
	//dsm($form_state,'node validate formstate');
}

function check_same_type_of_call_exist($form, $form_state){
	//dsm($form);
	//dsm($form_state);
	$nodeType = $form['type']['#value'];
	$value = $form['field_new_type_of_call']['und'][0]['value']['#default_value'];

	$isAnotherValueExist = _check_same_type_of_call_exist($nodeType,$value);

	if($isAnotherValueExist !== NULL){
		if($isAnotherValueExist === FALSE){// 바뀌기 전 값을 가지고 있는 TOC가 없을 경우 child 에 대해 TOC 같이 변경해주어야 함
			switch($nodeType){
				case 'idd_exit':
					$view = views_get_view('query_numberingplan_idd_country_by_toc');
					$view->set_arguments(array('0'=>$form_state['numberingplan_idd_nid'],'1'=>$value));
					$view->execute();
					foreach($view->result as $item){
						$country_node = node_load($item->node_field_data_field_ref_idd_country_nid);
						$country_node->field_type_of_call['und'][0]['safe_value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
						$country_node->field_type_of_call['und'][0]['value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
						node_save($country_node);
					}
					break;
				case 'idd_country':
					$view = views_get_view('query_numberingplan_idd_ratinggroup_by_toc');
					$view->set_arguments(array('0'=>$form_state['numberingplan_idd_nid'],'1'=>$value));
					$view->execute();
					foreach($view->result as $item){
						$ratinggroup_node = node_load($item->node_field_data_field_ref_idd_ratinggroup_nid);
						$ratinggroup_node->field_type_of_call['und'][0]['safe_value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
						$ratinggroup_node->field_type_of_call['und'][0]['value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
						node_save($ratinggroup_node);
					}
					break;
				case 'domestic_npa':
					$view = views_get_view('query_numberingplan_domestic_area_by_toc');
					$view->set_arguments(array('0'=>$form_state['numberingplan_domestic_nid'],'1'=>$value));
					$view->execute();
					foreach($view->result as $item){
						$area_node = node_load($item->node_field_data_field_ref_domestic_area_nid);
						$area_node->field_type_of_call['und'][0]['safe_value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
						$area_node->field_type_of_call['und'][0]['value'] = $form_state['values']['field_new_type_of_call']['und'][0]['value'];
						node_save($area_node);
					}
					break;
			}


		}
	}
}

function _check_same_type_of_call_exist($nodeType,$value){
	if(!isset($nodeType)){
		drupal_set_message($message = 'Can not find nodeType.', $type = 'error');
		return NULL;
	}
	if(!isset($value)){
		drupal_set_message($message = 'Can not find TOC value.', $type = 'error');
		return NULL;
	}

	switch($nodeType){
		case 'idd_exit':
			$viewName = 'query_numberingplan_idd_exit_by_new_toc';
			break;
		case 'idd_country':
			$viewName = 'query_numberingplan_idd_country_by_new_toc';
			break;
		case 'domestic_npa':
			$viewName = 'query_numberingplan_domestic_npa_by_new_toc';
			break;
	}

	if(!isset($viewName)) return NULL;

	$view = views_get_view($viewName);
	$view->set_arguments(array('0'=>$value));
	$view->execute();

	if(count($view->result) > 0){
		return TRUE;
	}

	return FALSE;
}

function _make_timeslot_for_validate_timetable($nid,$dayDelimiter,$hourRange,$minuteRange,$minuteScale){
	
	
	//set default timeslot for validation checking
	$timeslot = array();
	foreach($dayDelimiter as $day){
		$timeslot[$day] = array();
		for($i=0;$i<$hourRange;$i++){
			$timeslot[$day][$i] = array();
			for($j=0;$j<$minuteRange;$j=$j+$minuteScale){
				$timeslot[$day][$i][$j] = FALSE;
			}
		}
	}
	
	//load all timetablefactors
	$view = views_get_view('list_timetablefactors');
	$view->set_display('panel_pane_2');
	$view->set_arguments(array('0'=>$nid));
	$view->execute();
	
	foreach($view->result as $item){

		$fromHour = $item->field_field_timeslot_from_hour[0]['raw']['value'];
		$fromMinute = $item->field_field_timeslot_from_minutes[0]['raw']['value'];
		$toHour = $item->field_field_timeslot_to_hour[0]['raw']['value'];
		$toMinute = $item->field_field_timeslot_to_minutes[0]['raw']['value'];
		if($item->field_field_holiday[0]['raw']['value'] == 'HOLIDAY'){
			_make_timeslot_for_validate_timetable_sub($timeslot['HOLIDAY'],$fromHour,$fromMinute,$toHour,$toMinute,$minuteRange,$minuteScale,$hourRange);
		}else{
			if($item->field_field_week_mon[0]['raw']['value']){
				_make_timeslot_for_validate_timetable_sub($timeslot['MON'],$fromHour,$fromMinute,$toHour,$toMinute,$minuteRange,$minuteScale,$hourRange);
			}
			if($item->field_field_week_tue[0]['raw']['value']){
				_make_timeslot_for_validate_timetable_sub($timeslot['TUE'],$fromHour,$fromMinute,$toHour,$toMinute,$minuteRange,$minuteScale,$hourRange);
			}
			if($item->field_field_week_wed[0]['raw']['value']){
				_make_timeslot_for_validate_timetable_sub($timeslot['WED'],$fromHour,$fromMinute,$toHour,$toMinute,$minuteRange,$minuteScale,$hourRange);
			}
			if($item->field_field_week_thu[0]['raw']['value']){
				_make_timeslot_for_validate_timetable_sub($timeslot['THU'],$fromHour,$fromMinute,$toHour,$toMinute,$minuteRange,$minuteScale,$hourRange);
			}
			if($item->field_field_week_fri[0]['raw']['value']){
				_make_timeslot_for_validate_timetable_sub($timeslot['FRI'],$fromHour,$fromMinute,$toHour,$toMinute,$minuteRange,$minuteScale,$hourRange);
			}
			if($item->field_field_week_sat[0]['raw']['value']){
				_make_timeslot_for_validate_timetable_sub($timeslot['SAT'],$fromHour,$fromMinute,$toHour,$toMinute,$minuteRange,$minuteScale,$hourRange);
			}
			if($item->field_field_week_sun[0]['raw']['value']){
				_make_timeslot_for_validate_timetable_sub($timeslot['SUN'],$fromHour,$fromMinute,$toHour,$toMinute,$minuteRange,$minuteScale,$hourRange);
			}
		}
	}	
	//dsm($timeslot);
	return $timeslot;
}

function _make_timeslot_for_validate_timetable_sub(&$timeslotDay,$fromHour,$fromMinute,$toHour,$toMinute,$minuteRange,$minuteScale,$hourRange){
	for($hour = $fromHour ; $hour <= $toHour; $hour++){
		$startMinute = 0;
		$endMinute = $minuteRange;
		//if($fromHour == 0 && $toHour == 0 && $fromMinute == 0 && $toMinute == 0){
		//	$toHour = $hourRange;
		//}else{
			if($hour == $fromHour) $startMinute = $fromMinute;
			if($hour == $toHour) $endMinute = $toMinute;
		//}
		for($minute = $startMinute; $minute < $endMinute; $minute = $minute + $minuteScale){
			if($timeslotDay[$hour][$minute]){
				$timeslotDay[$hour][$minute] = 'duplicated';
			}else{
				$timeslotDay[$hour][$minute] = TRUE;	
			}
		}
	}
}

function validate_timetable_form($form, &$form_state){
	$dayDelimiter = array('MON','TUE','WED','THU','FRI','SAT','SUN','HOLIDAY');
	$hourRange = 24;
	$minuteRange = 60;
	$minuteScale = 10;
	
	$timeslot = _make_timeslot_for_validate_timetable($form_state['build_info']['args'][0],$dayDelimiter,$hourRange,$minuteRange,$minuteScale);
	//dsm($timeslot);
	
	$form['duplicated'] = array(
		'#type' => 'fieldset',
		'#title' => 'Duplicated', 
	    '#weight' => 1, 
	    '#collapsible' => TRUE, 
		'#collapsed' => FALSE,
	);
	$form['empty'] = array(
		'#type' => 'fieldset',
		'#title' => 'Not Defined', 
	    '#weight' => 2, 
	    '#collapsible' => TRUE, 
		'#collapsed' => FALSE,
	);
	
	$header = array(
    	array('data' => 'Day'),
        array('data' => 'Hour'),
        array('data' => 'Minute'),
    );
    
    $emptyRows = array();
    $duplicatedRows = array();

    $countDays = count($dayDelimiter);
    
    //dsm($timeslot);
    for($i=0;$i<$countDays;$i++){
    	for($j=0;$j<$hourRange;$j++){
    		for($k=0;$k<$minuteRange;$k=$k+$minuteScale){
    			if($timeslot[$dayDelimiter[$i]][$j][$k] === 'duplicated'){
    				$duplicatedRows[] = array($dayDelimiter[$i],$j,$k.'-'.($k+9));
    			}else if($timeslot[$dayDelimiter[$i]][$j][$k] === FALSE){
    				$emptyRows[] = array($dayDelimiter[$i],$j,$k.'-'.($k+9));
    			}
    		}
    	}
    }
    //dsm($duplicatedRows);
    //dsm($duplicatedRows,'dup');
    //dsm($emptyRows,'emp');
    $duplicatedTableArgs = array(
	    'header' => $header,
	    'rows' => $duplicatedRows,
	    'sticky' => 'sticky',
	    'empty' => 'There are no duplicated',
	    'attributes' => array(),
	    'colgroups' => array(),
	    'caption' => NULL,
    );    
    $duplicatedTableThemeResult = theme_table($duplicatedTableArgs);
    
    $emptyTableArgs = array(
	    'header' => $header,
	    'rows' => $emptyRows,
	    'sticky' => 'sticky',
	    'empty' => 'There are no empty',
	    'attributes' => array(),
	    'colgroups' => array(),
	    'caption' => NULL,
    );    
    $emptyTableThemeResult = theme_table($emptyTableArgs);
    
    $form['duplicated']['rows'] = array(
	    '#type' => 'markup',
	    '#markup' => $duplicatedTableThemeResult
    );
    
    $form['empty']['rows'] = array(
	    '#type' => 'markup',
	    '#markup' => $emptyTableThemeResult
    );
    
    $duplicatedRowCount = count($duplicatedRows);
    $emptyRowCount = count($emptyRows);
    $msg = '<div id="messages">';
    if($duplicatedRowCount > 0 || $emptyRowCount > 0){
    	$msg .= '<div class="messages error"><h2 class="element-invisible">Error message</h2><ul>';
    	if($duplicatedRowCount > 0) $msg .= '<li>Duplicated timetablefactors exist</li>';
    	if($emptyRowCount > 0) $msg .= '<li>Not defined timetablefactors exist</li>';
    	$msg .= '</ul></div></div>';
    }else if($duplicatedRowCount == 0 && $emptyRowCount == 0){
    	$msg .= '<div class="messages status"><h2 class="element-invisible">Status message</h2>Validation Test Passed!</div></div>';
    }
    
    $form['message'] = array(
    	'#type' => 'markup',
    	'#markup' => $msg,
    	'#weight' => 0,
    );
	return $form;
}
