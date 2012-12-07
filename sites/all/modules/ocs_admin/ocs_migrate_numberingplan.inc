<?php

function ocs_migrate_fce_numberingplan($form, &$form_state, $domestic_or_intl, $call_type)
{
	$category = isset($form_state['values']['category']) ? $form_state['values']['category'] : 'A';

	dpm( $category, 'category:');
	// dpm( $form_state['values'], 'values');
	$type = $domestic_or_intl. ':' . $call_type;

	if ( $type == 'domestic:voice')  {
		list($records, $output, $carrier) = _get_voice_tariff($type, $category);
	}
	else if ( $type == 'intl:voice')  {
		list($records, $output) = _get_area_code( $type);
		$carrier = ocs_load_all_carrier();
	}
	else {
		drupal_set_message( 'Invalid configuration. ', 'error');
		return ;
	}


	$form['#carrier'] = $carrier;
	$form['#attributes'] = array('class' => array('myform'));

	$form['#rule'] = $records;
	$form['#category'] = $type;
	
	if ( $type == 'domestic:voice') {
		$form['description'] = array(
			'#type' => 'markup',
			'#markup' => '<h2>Migration Rules</h2><br>'.
				'<p><ol><li>User Category가 없는 tariff의 경우 각 Carrier, Rating Group 별로 Numbering Plan을 하나씩 등록하고,'. 
				'<Carrier>_<Rating Group>을 이름으로 하는 Rating Group을 등록한다.</li>'.
				'<li>User Category가 있는 경우 각 Rule Name을 Rating Group으로 등록한다.</li>'.
				'</ol></p><br>'.
				'<h3>Changes</h3>'.
				'<p><ol><li>GobilInfo의 region_code 변경: TuvdengiinBorIntlLLC, 기존:1 => 신규:2</li>'.
				'<ol><li>update area set region_code=2 where carrier="GobiInfo" and rating_group = 2;</li></ol>'.
				
				'<li>INFO_10의 경우 area에는 rating group이 4,5만 존재하는데, tariff에는 1,2,3,4,5가 모두 있음. 이 경우 1,2,3은 사용되지 않으므로 삭제함</li>'.
				'<ol><li>select ruleName, isDDD, called_carrier, rating_group, user_category from voice_tariff_decision where called_carrier="INFO_1" and rating_group in (1,2,3);</li>'.
				'<li>delete from RuleList where rule_id in (4925, 4930, 4924, 4928, 4929, 4927)</li>'.
				'<li> update area set region_code = "5" where carrier="INFO_10" and rating_group="5";</li></ol>'.
				
				'<li>info_123의 경우에도 동일한 region code 1에 대해 서로 다른 rating group 1,2,3이 존재함. 수정 필요<ii>'.
				"<ol><li>select ruleName, carrier, rating_group, region_code from area where carrier = 'info_123';</li>".
				"<li>update area set region_code'3' where carrier = 'info_123' and rating_group = '3';</li>".
				"<li>update area set region_code='3' where carrier = 'info_123' and rating_group = '3';'</li></ol>".

				'<li>INFO_14</li>'.
                "<ol><li>select ruleName, carrier, second_prefix, rating_group, region_code from area where carrier = 'INFO_14';</li>".
                "<li>update area set region_code = '1' where carrier='INFO_14' and rating_group = '1';</li>".
                "<li>update area set region_code = '2' where carrier='INFO_14' and rating_group = '2';</li></ol>".

				'<li>INFO_3</li>'.
                "<ol><li>select ruleName, carrier, second_prefix, rating_group, region_code from area where carrier = 'INFO_3';</li>".
                "<li>update area set region_code = '3' where carrier = 'INFO_3' and rating_group = '3';</li></ol>".

				'<li>INFO_5</li>'.
                "<ol><li>select ruleName, carrier, second_prefix, rating_group, region_code from area where carrier = 'INFO_5';</li>".
                "<li>update area set region_code = '1' where carrier = 'INFO_5' and rating_group = '1';</li>".
                "<li>update area set region_code = '2' where carrier = 'INFO_5' and rating_group = '2';</li></ol>".

				'<li>INFO_8</li>'.
                "<ol><li>select ruleName, carrier, second_prefix, rating_group, region_code from area where carrier = 'INFO_8';</li>".
                "<li>update area set region_code = '2' where carrier = 'INFO_8' and rating_group = '2';</li></ol>".
				'</ol></p><br>'
			,
		);
	
		$form['category'] = array(
			'#type' => 'select',
			'#title' => 'User Category to migrate',
			'#options' => drupal_map_assoc(array(
				//'All',
				'A',
				'B',
				'C',
				'D',
				'E',
				'F',
				'G',
				'I',
				'J',
				'K',
				'M',
				'N',
				'O',
				'P',
				'Q',
				'S',
				'W',
				'X',
				'Y',
				'Z',
			)),
			'#default_value' => $category,
			'#ajax' => array(
				'callback' => 'ocs_ajax_select_user_category',
				'wrapper' => 'ocs_ajax_user_category_div',
			),
		);
	}

	$form['remove'] = array(
		'#type' => 'radios',
		'#options' => array(
			'No',
			'Yes'
		),
		'#default_value' => '0',
		'#title' => 'Remove all existing data',
	);

	$form['check'] = array(
		'#type' => 'radios',
		'#options' => array(
			'No',
			'Yes'
		),
		'#default_value' => '1',
		'#title' => 'Check Only',
	);


	$numbering_plan_list = _load_all_numbering_plan( $domestic_or_intl == 'intl' ? 'numberingplan_idd' : 'numberingplan_domestic');
    $form['data'] = array(
		'#type' => 'fieldset',
		'#title' => 'Migration Data',
		'#collapsible' => TRUE,
        '#prefix' => '<div id="ocs_ajax_user_category_div">',
        '#suffix' => '</div>',
	);
	
	$form['data']['target'] = array(
        '#type' => 'select',
		'#title' => 'Target numbering plan',
		'#options' => $numbering_plan_list,
    );

	$form['data']['list'] = array(
		'#type' => 'markup',
		'#markup' => '<table>' . $output . '</table>',
	);

	$form['actions'] = array('#type' => 'actions');
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);

	$form['actions']['cancel'] = array(
		'#type' => 'submit',
		'#value' => t('Cancel'),
	);

	return $form;
}

function ocs_migrate_fce_numberingplan_submit($form, &$form_state)
{
	$values = $form_state['values'];
	dpm($values, 'values');

	if ($values['op'] == 'Save') {

		$carrier_info = $form['#carrier'];

        if ( $form['#category'] == 'intl:voice') {
            _update_numberingplan_for_intl_voice( $carrier_info, $values['target'], $form['#rule'], 
					$values['check'] == '1', $values['remove'] == '1');
        }
		else if ( $form['#category'] == 'domestic:voice') {
            _update_numberingplan_for_domestic_voice( $carrier_info, $values['target'], $form['#rule'], 
					$values['check'] == '1', $values['remove'] == '1');

		}
		else {
			drupal_set_message( 'Undefined type: ' . $form['#category']);
		}

	}

}

function _update_numberingplan_for_domestic_voice( $carrier_info, $target_nid, $rule_list, $check_only, $remove_flag = FALSE)
{
	/*
		if ($values['remove'] == '1') {
			// remove all ratinggroup fields
			foreach ($np->field_ref_domestic_ratinggroup['und'] as $nid) {
				node_delete($nid['nid']);
				dpm(t('Domestic rating group @id is removed', array('@id' => $nid['nid'])));
			}
		}
			*/

	// load numbering plan
	$np = node_load( $target_nid);
	dpm( $np, 'numbering plan');

	if ( $remove_flag) {

		// find dangling entity
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'domestic_ratinggroup')
			->execute();
	
		if ( count( $result) > 0) {		// find the ratinggroup first
			foreach( array_keys( $result['node']) as $nid) {
				$node = node_load( $nid);
				//dpm( $node, 'node:'.$nid);
				if ( ! isset($node->field_ref_numberingplan_domestic['und']) || 
					$node->field_ref_numberingplan_domestic['und'][0]['nid'] == 0 ||
					$node->field_ref_numberingplan_domestic['und'][0]['nid'] == $np->nid) {
						node_delete( $nid);
						dpm( 'dangling entity is removed: '. $nid);
					}
			}
		}

		unset($np->field_ref_domestic_ratinggroup);

		node_save( $np);
	}
		

	// find rating group list
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'domestic_ratinggroup')
		->fieldCondition( 'field_ref_numberingplan_domestic', 'nid', $target_nid)
		->execute();
		
	$rating_group_list = array();
	if ( count( $result) > 0) {		// find the ratinggroup first
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			list( $carrier, $rg, $name) = explode( ':', $node->field_rating_group['und'][0]['value']);
			$area_code = (isset($node->field_area_code_of_the_callee['und'])) ? $node->field_area_code_of_the_callee['und'][0]['value'] : '0';
			$rating_group_list[$carrier][$rg][$area_code] = $node;
		}
	}
	dpm( $rating_group_list, 'rating group list');	
				
	// for each user category, check if all the conditions are same
	// category별로 분석하기 위해 잠시 사용한 코드 
	/*
	$rule_by_category = array();
	$count_by_category = array();
	foreach ($rule_list as $r) {
		if ( empty($r['user_category'])) continue;

		if ( isset( $rule_by_carrier[$r['called_carrier']][$r['rating_group']])) {
			$old = $rule_by_carrier[$r['called_carrier']][$r['rating_group']];

			if ( $old['isDDD'] != $r['isDDD'] ) {
				dpm( $old, 'mismatch old value');
				dpm( $r, 'mismatch new value');
			}
		}
		else if ( $r['user_category'] != 'A') {
			dpm( $r, 'new rating group');
		}

		$rule_by_carrier[ $r['called_carrier']][$r['rating_group']] = $r;

		if ( isset( $count_by_category[$r['user_category']]))
			$count_by_category[$r['user_category']] += 1;
		else
			$count_by_category[$r['user_category']] = 0;
	}

	$count_list = array_keys( $count_by_category);
	foreach( $count_list as $c) {
		if ( $count_by_category[$count_list[0]] != $count_by_category[$c]) {
			dpm( 'mismatch:'. $c);
		}
		dpm( 'count ' . $c . ' => ' . $count_by_category[$c]);
	}

	// 시험 결과
	count A => 59
	count B => 59
	count C => 59
	count D => 59
	count E => 59
	count F => 59
	count G => 59
	mismatch:I
	count I => 34
	mismatch:J
	count J => 34
	mismatch:K
	count K => 32
	mismatch:M
	count M => 60
	count N => 59
	mismatch:O
	count O => 5
	count P => 59
	count Q => 59
	count S => 59
	mismatch:W
	count W => 58
	count X => 59
	count Y => 59
	count Z => 59
	*/

	// 분석 결과 다음 각 category 별로 나눠서 numbering plan을 만들어야 한다.

	/*
		Numbering Plan 1 - A, B, C, D, E, F, G, N, P, Q, S, X, Y, Z
		Numbering Plan 2 - I, 
		Numbering Plan 3 - J, 
		Numbering Plan 4 - K, 
		Numbering Plan 5 - M, 
		Numbering Plan 6 - O, 
		Numbering Plan 7W
	*/
	
	foreach ($rule_list as $rule) {
		$carrier_name = $rule['called_carrier'];

		if ( ! isset( $carrier_info[$carrier_name]['rating_group'][$rule['rating_group']])) {
			drupal_set_message( t( 'Undefined rating group @r for carrier @c', 
						array( '@r' => $rule['rating_group'], '@c' => $carrier_name)), 'error');
			continue;
		}
		
		// set callee's area code
		$need_area_code = _need_area_code( $carrier_info, $carrier_name);
		$area_code = array( null);
		if ( $need_area_code) {
			dpm( 'Need area code: carrier='.$carrier_name.' rating_group='.$rule['rating_group']);
			
			if ( ! isset($carrier_info[$carrier_name]['rating_group'][$rule['rating_group']]) ) {
				drupal_set_message( t('Rating group not found. Carrier=@c RatingGroup=@r,@ra', 
					array( '@c' => $carrier_name, '@r' => $rule['rating_group'], '@ra' => $rule['ruleName'])),
					'error');
				continue;				
			}
			else {
				$area_code = array_keys( $carrier_info[$carrier_name]['rating_group'][$rule['rating_group']]);
				dpm( 'area code list : '. implode( ',', $area_code));
			}
		}
				
		if ( ! isset( $carrier_info[$carrier_name]['nid'])) {
			dpm( 'nid not found for carrier:'. $carrier_name);
			continue;
		}

		$rating_group_name = $carrier_name . ':' . $rule['rating_group'] . ':';
		$rating_group_name .= ( empty($rule['user_category'])) ? $rule['ruleName'] : '';

		$carrier_nid = $carrier_info[$carrier_name]['nid'];

		if ( isset($rating_group_list[$carrier_name][$rule['rating_group']])) {
			// rating group exist already
			
			$result = $rating_group_list[$carrier_name][$rule['rating_group']];
			if ( $need_area_code && (count( $result) != count( $area_code))) {
				dpm( $result, 'mismatch with area code');
				dpm( $area_code, 'mismatch with area code');
			}
			//dpm( $result, 'rating group');
			$i = 0;
			foreach( $result as $r ) {
					
				dpm( t('existing rating group: carrier=@c rating_group=@r,@ra area=@a final_rating_group=@f', 
                    array( '@c' => $rule['called_carrier'],
					    '@r' => $rule['rating_group'], 
                        '@ra' => $rule['ruleName'], 
                        '@a' => implode( ',', $area_code),
						'@f' => $rating_group_name)));
				
				_set_domestic_ratinggroup( $carrier_info, $r, $np, $rule, $need_area_code ? $area_code[$i++] : null, $rating_group_name);

				if ( ! $check_only) {
					node_save( $r);
					$nid_list = array_get_value( $np->field_ref_domestic_ratinggroup, FALSE);

					if ( array_search( $r->nid, $nid_list) === FALSE) {
						dpm( $nid_list, 'update numbering plan. add nid:'.$r->nid);
						$np->field_ref_domestic_ratinggroup['und'][] = array( 'nid' => $r->nid);
						node_save( $np);
					}
				}
			}
		}
		else {
			foreach( $area_code as $code ) {
				dpm( t('>>> new rating group "@nr": carrier=@c rating_group=@r area=@a final_rating_group=@f', 
					array( '@nr' => $rating_group_name, '@c' => $rule['called_carrier'],
					'@r' => $rule['rating_group'], '@a' => $code, '@f' => $rating_group_name)));
				// make new rating group
				$r = ocs_admin_get_new_node('domestic_ratinggroup');

				_set_domestic_ratinggroup( $carrier_info, $r, $np, $rule, $code, $rating_group_name);

				if ( ! $check_only) {
					node_save( $r);
				
					$np->field_ref_domestic_ratinggroup['und'][] = array('nid' => $r->nid);
					node_save( $np);
									// update rating_group_list
					$rating_group_list[$carrier_name][$rule['rating_group']][$code] = $r;
				}
			}
		}
	}
}

function _set_domestic_ratinggroup( $carrier_info, &$r, $np, $rule, $area_code, $name)
{
	$carrier_name = $rule['called_carrier'];

	if ( isset( $r->field_ref_numberingplan_domestic['und'])) {
		if ( $r->field_ref_numberingplan_domestic['und'][0]['nid'] != $np->nid )
			dpm( 'mismatch ref numbering plan : ' . $r->field_ref_numberingplan_domestic['und'][0]['nid'] . ' : ' . $np->nid);
		if ( $r->field_ref_carrier_mobile['und'][0]['nid'] != $carrier_info[$carrier_name]['nid'] )
			dpm( 'mismatch ref carrier: ' . $r->field_ref_carrier_mobile['und'][0]['nid'] . ' : ' . $carrier_info[$carrier_name]['nid']);
		if ( $r->field_rating_group['und'][0]['value'] != $name)
			dpm( 'mismatch rating group name: ' . $r->field_rating_group['und'][0]['value'] . ' : ' . $name );
	}
		
	$r->title = 'domestic_ratinggroup';
	$r->field_ref_numberingplan_domestic['und'][0]['nid'] = $np->nid;
	$r->field_service_type_of_provider['und'][0]['tid'] = 406;		// Mobile
	$r->field_ref_carrier_mobile['und'][0]['nid'] = $carrier_info[$carrier_name]['nid'];
	$r->field_is_samezone['und'][0]['tid'] = 1988;		// All
	$r->field_rating_group['und'][0]['value'] = $name;
	
	// set type of call
	if (strcasecmp(substr($carrier_name, 0, 6), 'UNITEL') == 0) {
		$r->field_ref_type_of_call['und'][0]['tid'] = 725;
		// outgoing on net voice call
	}
	else if (substr($carrier_name, -1, 4) == '_INT') {
		$r->field_ref_type_of_call['und'][0]['tid'] = 1514;
		// outgoing international voice call
	}
	else {
		// 1513 outgoing off net voice call
		$r->field_ref_type_of_call['und'][0]['tid'] = 1513;
	}

	// reset area_code_to
	if ( ! empty( $area_code)) {
		$r->field_area_code_of_the_callee['und'][0]['value'] = $area_code;
	}
}

function _need_area_code( $carrier_info, $name)
{
	// return TRUE if the carrier need area code to build rating group
	if ( isset( $carrier_info[$name])) {
		if ( count( $carrier_info[$name]['rating_group']) == 1)
			return FALSE;
		
		if ( count( $carrier_info[$name]['region_code']) == 1)
			return FALSE;
			
		return TRUE;
	}
	
	dpm( 'Invalid carrier info: ' . $name);
	
	return FALSE;
}

function _update_numberingplan_for_intl_voice( $carrier_info, $target_nid, $records, $check_only, $remove_existing_data = FALSE)
{
    // get country code
   	db_set_active('fce');

	$query = db_select('intl_country_code', 'c');
	$result = $query->fields('c', array(
		'ruleName',
		'country_prefix',
        ))->execute();

	$country_code = array();
	while ($record = $result->fetchAssoc()) {
		$country_code[ $record['ruleName']] = $record['country_prefix'];
    }
	db_set_active('default');

	// read numbering plan
	$np = node_load( $target_nid);
	dpm( $np, 'target numbering plan');

	// find rating group list
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'idd_ratinggroup')
		->fieldCondition( 'field_ref_numberingplan_idd', 'nid', $np->nid)
		->execute();
		
	$rating_group_list = array();
	if ( count( $result) > 0) {		// find the ratinggroup first
		foreach( array_keys( $result['node']) as $nid) {
			if ( $remove_existing_data) {
				node_delete( $nid);
				dpm( 'idd_ratinggroup instance is deleted. nid='. $nid);
			}
			else {
				$node = node_load( $nid);
				$prefix = $node->field_prefix['und'][0]['value'];
				if ( isset( $rating_group_list[$prefix])) {
					dpm( 'Rating group exist already: prefix=' . $prefix);
				}
				$rating_group_list[$node->field_prefix['und'][0]['value']] = $nid;
			}
		}
	}
	dpm( $rating_group_list, 'rating group list');	
	dpm( $np, 'IDD numbering plan');
		
    foreach ($records as $r) {
        $prefix = ( isset( $country_code[ $r['country_code']])) ?  
            ($country_code[ $r['country_code']] . $r['NPA_prefix']) : 
            ($r['prefix'] . $r['NPA_prefix']);


        if ( isset( $rating_group_list[$prefix])) {
            dpm( t('existing prefix : carrier=@c prefix=@p name=!n', array( '@c' => $r['intl_carrier'],
                '@p' => $prefix, '!n' => $r['ruleName'])));

            $nid = $rating_group_list[$prefix];
            $c = node_load( $nid);
            _set_idd_ratinggroup( $carrier_info, $c, $np, $r, $prefix);
            //dpm( $c, 'idd_ratinggroup');

            if ( ! $check_only) {
                node_save( $c);
            }
        }
        else {
            dpm( t('new prefix : carrier=@c prefix=@p name=!n', array( '@c' => $r['intl_carrier'],
                '@p' => $prefix, '!n' => $r['ruleName'])));

            $c = ocs_admin_get_new_node('idd_ratinggroup');
            _set_idd_ratinggroup( $carrier_info, $c, $np, $r, $prefix);
            //dpm( $c, 'idd_ratinggroup');

            if ( ! $check_only) {
                node_save( $c);
                $np->field_ref_idd_ratinggroup['und'][] = array('nid' => $c->nid);
            }
        }
    }

	if ( ! $check_only) node_save($np);
}

function _set_idd_ratinggroup( $carrier_info, &$r, $np, $rule, $prefix)
{
	$carrier_name = $rule['intl_carrier'];

	$r->title = 'idd_ratinggroup';
	$r->field_ref_numberingplan_idd['und'][0]['nid'] = $np->nid;
	$r->field_service_type_of_provider['und'][0]['tid'] = 406;		// Mobile
	$r->field_ref_carrier_mobile['und'][0]['nid'] = $carrier_info[$carrier_name]['nid'];
	$r->field_prefix['und'][0]['value'] = $prefix;
	$r->field_area_name['und'][0]['value'] = $rule['ruleName'];
	$r->field_rating_group['und'][0]['value'] = $carrier_name . '_' . $rule['rating_group'];
	
	// set type of call
    // outgoing international voice call
    $r->field_ref_type_of_call['und'][0]['tid'] = 1514;
}


