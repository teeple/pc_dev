<?php

function product_catalog_form_node_validate($node, $form, &$form_state){
// dsm($form, 'form');
// dsm($form_state, 'form_state');
// dsm($node, 'node');
	
	switch($form['form_id']['#value']){		
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
		case 'counter_node_form';
			break;        
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