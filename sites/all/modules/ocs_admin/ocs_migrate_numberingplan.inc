<?php

//define( 'TID_MOBILE', 406);

function ocs_migrate_fce_numberingplan($form, &$form_state, $domestic_or_intl, $call_type)
{
	$category = isset($form_state['values']['category']) ? $form_state['values']['category'] : 'A';

	dpm( $category, 'category:');
	// dpm( $form_state['values'], 'values');
	$type = $domestic_or_intl. ':' . $call_type;

	if ( $type == 'intl:voice')  {
		list($records, $output) = _get_area_code( $type);
		$carrier = ocs_load_all_carrier();
	}
	else if ( $type == 'domestic:voice' || $type == 'domestic:sms')  {
		list($records, $output, $carrier) = _get_voice_tariff($type, $category);
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
    }
	
    if ( $domestic_or_intl == 'domestic') {
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
	$service_domain = ocs_get_terms_tid( 'SvcDomain');

	$values = $form_state['values'];
	dpm($values, 'values');

	if ($values['op'] == 'Save') {

		$carrier_info = $form['#carrier'];

        if ( $form['#category'] == 'intl:voice') {
            if ( $values['remove'] == '1') {

                // find rating group list
                $query = new EntityFieldQuery();
                $result = $query->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', 'idd_ratinggroup')
                    ->fieldCondition( 'field_ref_numberingplan_idd', 'nid', $values['target'])
                    ->execute();
                    
                foreach( array_keys( $result['node']) as $nid) {
                    node_delete( $nid);
                    dpm( 'idd_ratinggroup instance is deleted. nid='. $nid);
                }

				// load numbering plan
				$np = node_load( $values['target']);
				unset($np->field_ref_idd_ratinggroup['und']);
				node_save( $np);
            }
             _update_numberingplan_for_intl_voice( $carrier_info, $values['target'], $form['#rule'], $values['check'] == '1');
        }
		else if ( $form['#category'] == 'domestic:voice') {
            if ( $values['remove'] == '1') {
                _remove_existing_data( $values['target']);
            }
            _update_numberingplan_for_domestic_voice( $carrier_info, $values['target'], $form['#rule'], $values['check'] == '1');

		}
        else if ( $form['#category'] == 'domestic:sms') {
            if ( $values['remove'] == '1') {
                _remove_existing_data( $values['target']);
            }
            _update_numberingplan_for_domestic_sms( $carrier_info, $values['target'], $form['#rule'], $values['check'] == '1');
        }
		else {
			drupal_set_message( 'Undefined type: ' . $form['#category']);
		}

	}

}

function _remove_existing_data( $target_nid)
{
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
                $node->field_ref_numberingplan_domestic['und'][0]['nid'] == $target_nid) {
                    node_delete( $nid);
                    dpm( 'dangling entity is removed: '. $nid);
                }
        }
    }

    $np = node_load( $target_nid);
    unset($np->field_ref_domestic_ratinggroup);
    node_save( $np);
}

function _load_all_call_type_terms()
{
    /* get vocabulary name */
    $vid = taxonomy_vocabulary_machine_name_load( 'calltype');
    $query = new EntityFieldQuery;
    $result = $query->entityCondition('entity_type', 'taxonomy_term')
        ->propertyCondition('vid', $vid->vid)
        ->execute();

    $terms = taxonomy_term_load_multiple( array_keys( $result['taxonomy_term']));
    $list = array();
    foreach( $terms as $t) {
        $list[$t->name] = $t->tid;
    }

    return $list;
}

function _ocs_migrate_type_of_call( $service_type, $carrier)
{
	if ( $service_type == 'SMS') {
		$mapping = array(
			'G-Mobile' => 'SMS_G_MOBILE',
			'G_Mobile' => 'SMS_G_MOBILE',
			'G_Mobile_53' => 'SMS_G_MOBILE',
			'G_Mobile_97' => 'SMS_G_MOBILE',
			'MOBICOM' => 'SMS_MOBICOM',
			'MOBI_NEW' => 'SMS_MOBICOM',
			'MOBI_WLL' => 'SMS_MOBICOM',
			'MTC_WLLnew' => 'SMS_MTC',
			'SKYTEL' => 'SMS_SKYTEL',
			'SKY_WLL' => 'SMS_SKYTEL',
			'UNITEL' => 'SMS_UNITEL',
			'UNITEL_new' => 'SMS_UNITEL',
			'UNITEL_VOIP' => 'SMS_UNITEL',
			);

		if ( isset( $mapping[$carrier])) return $mapping[$carrier];
		dpm( $carrier, 'Undefined carrier');
		return 'SMS_PREMIUM';
	}
	else if ( $service_type == 'VOICE') {
		$mapping = array(
				'AIRPORT' => 'MOBILE_DDD',
				'Dornodzuuch' => 'MOBILE_DDD',
				'eeverich' => 'MOBILE_DDD',
				'G-Mobile' => 'MOBILE_DDD',
				'Ganaa_Test' => 'MOBILE_DDD',
				'Garts_1' => 'MOBILE_DDD',
				'Garts_12' => 'MOBILE_DDD',
				'Garts_2' => 'MOBILE_DDD',
				'Garts_3' => 'MOBILE_DDD',
				'Garts_4' => 'MOBILE_DDD',
				'Garts_5' => 'MOBILE_DDD',
				'Garts_6' => 'MOBILE_DDD',
				'GobiInfo' => 'MOBILE_DDD',
				'Goviin_javkhaa' => 'MOBILE_DDD',
				'GVRMNT1' => 'MOBILE_DDD',
				'GVRMNT2' => 'MOBILE_DDD',
				'GVRMNT3' => 'MOBILE_DDD',
				'G_Mobile' => 'MOBILE_DDD',
				'G_Mobile_53' => 'MOBILE_DDD',
				'G_Mobile_78' => 'MOBILE_DDD',
				'G_Mobile_97' => 'MOBILE_DDD',
				'INFO_10' => 'MOBILE_DDD',
				'INFO_111' => 'MOBILE_DDD',
				'INFO_12' => 'MOBILE_DDD',
				'info_123' => 'MOBILE_DDD',
				'INFO_12_70' => 'MOBILE_DDD',
				'INFO_13' => 'MOBILE_DDD',
				'INFO_14' => 'MOBILE_DDD',
				'INFO_15' => 'MOBILE_DDD',
				'Info_17' => 'MOBILE_DDD',
				'Info_180' => 'MOBILE_DDD',
				'INFO_191' => 'MOBILE_DDD',
				'INFO_193' => 'MOBILE_DDD',
				'INFO_195' => 'MOBILE_DDD',
				'Info_199' => 'MOBILE_DDD',
				'INFO_2' => 'MOBILE_DDD',
				'INFO_3' => 'MOBILE_DDD',
				'INFO_5' => 'MOBILE_DDD',
				'INFO_6' => 'MOBILE_DDD',
				'INFO_7' => 'MOBILE_DDD',
				'INFO_8' => 'MOBILE_DDD',
				'Info_Baganuur' => 'MOBILE_DDD',
				'Info_Darhan' => 'MOBILE_DDD',
				'Info_Darhan_Upd' => 'MOBILE_DDD',
				'INFO_Darkhan_19' => 'MOBILE_DDD',
				'Info_Dorngovi' => 'MOBILE_DDD',
				'INFO_Dornod' => 'MOBILE_DDD',
				'INFO_Dund_govi' => 'MOBILE_DDD',
				'Info_Uvurhangai' => 'MOBILE_DDD',
				'Inkomnet' => 'MOBILE_DDD',
				'Inkomnet_1' => 'MOBILE_DDD',
				'Khubsgul_in' => 'MOBILE_DDD',
				'MOBICOM' => 'MOBILE_DDD',
				'MOBINET' => 'MOBILE_DDD',
				'MOBI_DIAL' => 'MOBILE_DDD',
				'MOBI_INT' => 'MOBILE_IDD',
				'MOBI_NEW' => 'MOBILE_DDD',
				'MOBI_WLL' => 'MOBILE_DDD',
				'MOBI_WLLnew' => 'MOBILE_DDD',
				'MONGOLCOM' => 'MOBILE_DDD',
				'MonSat' => 'MOBILE_DDD',
				'MTC_DDD' => 'MOBILE_DDD',
				'MTC_INFO' => 'MOBILE_DDD',
				'MTC_INT' => 'MOBILE_IDD',
				'MTC_NGN' => 'MOBILE_DDD',
				'MTC_UB' => 'MOBILE_DDD',
				'MTC_WLL' => 'MOBILE_DDD',
				'MTC_WLLnew' => 'MOBILE_DDD',
				'MTD_LLC' => 'MOBILE_DDD',
				'Nalaih' => 'MOBILE_DDD',
				'nalaih_in' => 'MOBILE_DDD',
				'Orkhon_Asgat' => 'MOBILE_DDD',
				'Orkhon_Asgat_70' => 'MOBILE_DDD',
				'Popularcom' => 'MOBILE_DDD',
				'RAILWAY' => 'MOBILE_DDD',
				'RAILWAY_UB' => 'MOBILE_DDD',
				'RAY_INT' => 'MOBILE_IDD',
				'selenge_in' => 'MOBILE_DDD',
				'Selenge_Info' => 'MOBILE_DDD',
				'Skynetwork' => 'MOBILE_DDD',
				'SKYTEL' => 'MOBILE_DDD',
				'SKY_INT' => 'MOBILE_IDD',
				'Sky_Voip' => 'MOBILE_DDD',
				'SKY_WLL' => 'MOBILE_DDD',
				'TEST' => 'MOBILE_DDD',
				'UNITEL' => 'MOBILE_DDD',
				'Unitel_Ayalguu' => 'MOBILE_LOCAL',
				'UNITEL_new' => 'MOBILE_LOCAL',
				'UNITEL_VOIP' => 'MOBILE_LOCAL',
				'UNI_INT' => 'MOBILE_IDD',
				'ZuunKharaa_in' => 'MOBILE_DDD',
			);

		if ( isset( $mapping[$carrier])) return $mapping[$carrier];
		dpm( $carrier, 'Undefined carrier');
		return 'MOBILE_LOCAL';
	}

	return NULL;
}


function _update_numberingplan_for_domestic_sms( $carrier_info, $target_nid, $rule_list, $check_only)
{
	$service_domain = ocs_get_terms_tid( 'SvcDomain');

    dpm( $carrier_info, 'carrier info');

	// load numbering plan
	$np = node_load( $target_nid);
	dpm( $np, 'numbering plan');

    $rating_group_list = _load_all_rating_group( $target_nid, 'domestic:sms');	

    $type_of_call_terms = _load_all_call_type_terms();
	dpm( $type_of_call_terms, 'call types');

	foreach ($rule_list as $rule) {

        if ( empty( $rule['called_carrier'])) {
            continue;
        }

		$carrier_name = $rule['called_carrier'];
		if ( $carrier_name == 'UNITEL_new') $carrier_name = 'UNITEL';	// same carrier
		$rating_group_name = $carrier_name . ':' . $rule['ruleName'];

        if ( ! isset( $carrier_info[$carrier_name]['nid'])) {
            dpm( 'Carrier nid not found: '. $carrier_name);
            continue;
        }
		$carrier_nid = $carrier_info[$carrier_name]['nid'];

        // set type of call
		$calltype = _ocs_migrate_type_of_call( 'SMS', $carrier_name);
		if ( ! isset( $type_of_call_terms[$calltype])) {
			drupal_set_message( 'Undefined call type : '. $calltype, 'error');
			continue;
		}

		$type_of_call = $type_of_call_terms[$calltype];
		if ( isset($rating_group_list[$carrier_name][$rule['ruleName']])) {
			// rating group exist already
            $r = $rating_group_list[$carrier_name][$rule['ruleName']];

            dpm( t('existing rating group: carrier=@c rating group=@ra final_rating_group=@f', 
                array( '@c' => $rule['called_carrier'],
                    '@ra' => $rule['ruleName'], 
                    '@f' => $rating_group_name)));
            
            _set_domestic_ratinggroup( $carrier_info, $r, $np, $rule, null, $rating_group_name, $type_of_call, $service_domain['Mobile']);

            if ( ! $check_only) {
				//dpm( $r, $r->title);
                node_save( $r);
                $nid_list = array_get_value( $np->field_ref_domestic_ratinggroup, FALSE);

                if ( array_search( $r->nid, $nid_list) === FALSE) {
                    dpm( $nid_list, 'update numbering plan. add nid:'.$r->nid);
                    $np->field_ref_domestic_ratinggroup['und'][] = array( 'nid' => $r->nid);
                    node_save( $np);
                }
			}
		}
		else {
            dpm( t('>>> new rating group "@nr": carrier=@c final_rating_group=@f', 
                array( '@nr' => $rating_group_name, '@c' => $rule['called_carrier'], '@f' => $rating_group_name)));
            // make new rating group
            $r = ocs_admin_get_new_node('domestic_ratinggroup');

            _set_domestic_ratinggroup( $carrier_info, $r, $np, $rule, null, $rating_group_name, $type_of_call, $service_domain['Mobile']);

            if ( ! $check_only) {
                node_save( $r);
            
                $np->field_ref_domestic_ratinggroup['und'][] = array('nid' => $r->nid);
                node_save( $np);
                                // update rating_group_list
                $rating_group_list[$carrier_name][$rule['ruleName']] = $r;
			}
		}
	}
}

function _load_all_rating_group( $target_nid, $type = 'domestic:voice')
{
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
            if ( $type == 'domestic:sms') {
                list( $carrier, $rg) = explode( ':', $node->field_rating_group['und'][0]['value']);
                $rating_group_list[$carrier][$rg] = $node;
            }
            else {
                list( $carrier, $rg, $name) = explode( ':', $node->field_rating_group['und'][0]['value']);
                $area_code = (isset($node->field_area_code_of_the_callee['und'])) ? $node->field_area_code_of_the_callee['und'][0]['value'] : '0';
                $rating_group_list[$carrier][$rg][$area_code] = $node;
            }
		}
	}
	dpm( $rating_group_list, 'rating group list');	

    return $rating_group_list;
}
	
function _update_numberingplan_for_domestic_voice( $carrier_info, $target_nid, $rule_list, $check_only)
{
	// load numbering plan
	$np = node_load( $target_nid);
	dpm( $np, 'numbering plan');

    $rating_group_list = _load_all_rating_group( $target_nid, 'domestic:voice');	

	$service_domain = ocs_get_terms_tid( 'SvcDomain');
    $type_of_call_terms = _load_all_call_type_terms();
	dpm( $type_of_call_terms, 'call types');
			
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

		$calltype = _ocs_migrate_type_of_call( 'VOICE', $carrier_name);
		if ( ! isset( $type_of_call_terms[$calltype])) {
			drupal_set_message( 'Undefined call type : '. $calltype, 'error');
			continue;
		}   
				            
		$type_of_call = $type_of_call_terms[$calltype];

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
				
				_set_domestic_ratinggroup( $carrier_info, $r, $np, $rule, $need_area_code ? $area_code[$i++] : null, $rating_group_name, $type_of_call, $service_domain['Mobile']);

				if ( ! $check_only) {
					//dpm( $r, $r->title);
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

				_set_domestic_ratinggroup( $carrier_info, $r, $np, $rule, $code, $rating_group_name, $type_of_call, $service_domain['Mobile']);

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

function _set_domestic_ratinggroup( $carrier_info, &$r, $np, $rule, $area_code, $name, $type_of_call, $mobile_tid)
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
	$r->field_service_type_of_provider['und'][0]['tid'] = $mobile_tid;		// Mobile
	$r->field_ref_carrier_mobile['und'][0]['nid'] = $carrier_info[$carrier_name]['nid'];
    $r->field_ref_type_of_call['und'][0]['tid'] = $type_of_call;
	
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

function _update_numberingplan_for_intl_voice( $carrier_info, $target_nid, $records, $check_only)
{
	$service_domain = ocs_get_terms_tid('SvcDomain');
	dpm( $service_domain, 'service domain');
	$type_of_call = ocs_get_terms_tid('CallType');

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

    $terms = _load_all_call_type_terms();
	dpm( $terms, 'Call Types');
	$idd_type_of_call = $terms['MOBILE_IDD'];

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
            $node = node_load( $nid);
            $prefix = $node->field_prefix['und'][0]['value'];
            if ( isset( $rating_group_list[$prefix])) {
                dpm( 'Rating group exist already: prefix=' . $prefix);
            }
            $rating_group_list[$prefix] = $nid;
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
            _set_idd_ratinggroup( $carrier_info, $c, $np, $r, $prefix, $idd_type_of_call, $service_domain['Mobile']);
            dpm( 'idd_ratinggroup nid='.$nid. ' rg='.$c->field_rating_group['und'][0]['value']);

            if ( ! $check_only) {
                node_save( $c);
            }
        }
        else {
            dpm( t('new prefix : carrier=@c prefix=@p name=!n', array( '@c' => $r['intl_carrier'],
                '@p' => $prefix, '!n' => $r['ruleName'])));

            $c = ocs_admin_get_new_node('idd_ratinggroup');
            _set_idd_ratinggroup( $carrier_info, $c, $np, $r, $prefix, $idd_type_of_call, $service_domain['Mobile']);
            //dpm( $c, 'idd_ratinggroup');

            if ( ! $check_only) {
                node_save( $c);
                $np->field_ref_idd_ratinggroup['und'][] = array('nid' => $c->nid);
            }
        }
    }

	if ( ! $check_only) node_save($np);
}

function _set_idd_ratinggroup( $carrier_info, &$r, $np, $rule, $prefix, $type_of_call, $tid_mobile)
{
	$carrier_name = $rule['intl_carrier'];

	$r->title = 'idd_ratinggroup';
	$r->field_ref_numberingplan_idd['und'][0]['nid'] = $np->nid;
	$r->field_service_type_of_provider['und'][0]['tid'] = $tid_mobile;		// Mobile
	$r->field_ref_carrier_mobile['und'][0]['nid'] = $carrier_info[$carrier_name]['nid'];
	$r->field_prefix['und'][0]['value'] = $prefix;
	$r->field_area_name['und'][0]['value'] = $rule['ruleName'];
	$r->field_rating_group['und'][0]['value'] = $carrier_name . ':' . $rule['rating_group'];
	
	// set type of call
    // outgoing international voice call
    $r->field_ref_type_of_call['und'][0]['tid'] = $type_of_call;
}


