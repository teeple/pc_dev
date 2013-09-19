<?php
define( 'RoamingIntlVoice', '1011');
define( 'RoamingIntlSMS', '1010');

define( 'RoamingHCC', '1031');
define( 'RoamingIVC', '1032');
define( 'RoamingLVC', '1033');

define( 'RoamingSMS', '1036');
define( 'RoamingRSMS', '1037');
define( 'RoamingGPRS', '1038');

define( 'RATE_UNIT_COUNT', '202');
define( 'RATE_UNIT_SECOND', '303');
define( 'RATE_UNIT_GB', '403');

define( 'RATE_APLY_DV_CD_STEP', '2');

function ocs_roaming_import( $form, &$form_state, $type)
{
	$selected_product_nid = isset($form_state['values']['product']) ? $form_state['values']['product'] : 0;
	if ( $selected_product_nid) $tariff_plan_list = _ocs_roaming_get_tariff_plan( $selected_product_nid);

	$response_data = isset($form_state['values']['response']) ? $form_state['values']['response'] : NULL;

	$form['#config_type'] = $type;

    $form['ocs'] = array(
        '#type' => 'fieldset',
        '#title' => 'RMS(Roaming Management System) API',
        '#description' => t('RMS API Settings. It can be changed ').
            l( t('here'), 'admin/config/system/ocs_admin'),
        '#collapsible' => TRUE, 
        '#collapsed' => FALSE,
    );

    $method = variable_get('ocs_admin_roaming_api_method', 'Administrative Warning');
    $url = variable_get('ocs_admin_roaming_api_'.$type, 'Administrative Warning');

    $form['ocs']['url'] = array(
        '#type' => 'item',
        '#title' => 'URL to get roaming configuration from RMS',
        '#markup' => '<br><p>' . $method . ' ' . $url . '</p>',
    );

	$form['delete'] = array(
		'#type' => 'radios', 
		'#title' => 'Delete unused data',
		'#options' => array( 0 => 'No', 1 => 'Yes'),
		'#default_value' => 0,
	);

	$form['reset'] = array(
		'#type' => 'radios', 
		'#title' => 'Reset all existing data',
		'#options' => array( 0 => 'No', 1 => 'Yes'),
		'#default_value' => 0,
	);

	if ( empty( $response_data)) {
		$response = drupal_http_request( $url, array(
			'method' => $method,
			'headers' => array('Content-Type' => 'application/json', 'Accept' => 'application/json'),
			'timeout'=>60));
		dpm( $url, 'url');
		dpm( $response, 'response');
		if ( $response->code == 200) {
			$response_data = $response->data;
		}
		else {
			drupal_set_message( 'API Return Result : ' . $response->error, 'error');
		}
	}

	if ( $type == 'tariff') {
		$product_type = ( isset( $form_state['#product_type'])) ? $form_state['#product_type'] : NULL;
		if ( empty($product_type)) {
			$product_type = ocs_get_terms_tid( 'PrdType');
			$form_state['#product_type'] = $product_type;
		}

		$service_domain = ( isset( $form_state['#service_domain'])) ? $form_state['#service_domain'] : NULL;
		if ( empty( $service_domain)) {
			$service_domain = ocs_get_terms_tid( 'SvcDomain');
			$form_state['#service_domain'] = $service_domain;
		}

		// find tariff plans
		$tariff_plan_nids = ( isset( $form_state['#tariff_plan_nids'])) ? $form_state['#tariff_plan_nids'] : NULL;
		if ( empty( $tariff_plan_nids)) {
			$tariff_plan_nids = ocs_get_nids_by_cond( 'simpleproductoffering', array(
				array('field_product_type', 'tid', $product_type['Main']),
				array('field_service_type_of_provider', 'tid', $service_domain['Mobile'])));
			$form_state['#tariff_plan_nids'] = $tariff_plan_nids;
		}

		if ( ! empty( $tariff_plan_nids)) {
			$prd_list = array();
			foreach(  $tariff_plan_nids as $nid) {
				// find the product which as roaming tariff plan
				$tariff_plan = _ocs_roaming_get_tariff_plan( $nid);
				if ( count( $tariff_plan) > 0) {
					$node = node_load( $nid);
					$prd_list[$nid] = $node->title;
					if ( $selected_product_nid == 0) {
						$selected_product_nid = $nid;
						$tariff_plan_list = $tariff_plan;
					}
				}
			}

			$form['product'] = array(
				'#type' => 'select',
				'#title' => 'Product',
				'#options' => $prd_list,
				'#default_value' => $selected_product_nid,
				'#attributes' => array('class' => array('myform')),
				'#ajax' => array(
					'callback' => 'ocs_ajax_select_roaming_product',
					'wrapper' => 'ocs_ajax_select_roaming_product_div',
					),
			);
		}

		// get start date list from API result
		$start_date_list = array();
		$tariff_list = json_decode( $response_data, TRUE);
		foreach( $tariff_list as $partner => $tariffs) {
			foreach( $tariffs as $tariff) {
				list( $plmn, $calltype) = _ocs_roaming_get_plmn_calltype( $tariff);
				$type = ( strstr( $calltype, 'SMS')) ? 'SMS' : 'VOICE';
				$dt = $tariff['VALD_STRT_DT'];
				if ( !isset( $start_date_list[$dt]) || array_search( $type, $start_date_list[ $dt]) === FALSE)  {
					$start_date_list[ $dt][] = $type;
				}
			}
		}
		//dpm( $start_date_list, 'start date list');

		$form['#start_date_list'] = $start_date_list;

		dpm( $tariff_plan_list, 'tariff plan list');
		$form['#tariff_plan_list'] = $tariff_plan_list;

		$form['tariff_plan'] = array(
			'#type' => 'fieldset',
			'#title' => 'Roaming Tariff Plans ',
			'#prefix' => '<div id="ocs_ajax_select_roaming_product_div">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('myform')),
			'#tree' => TRUE,
		);

		$selected_tariff_plan = array_keys( $tariff_plan_list);
		foreach( $start_date_list as $date => $values) {

			foreach( $values as $calltype) {
				$title = $calltype . '|' . $date;
				$form['tariff_plan'][$title] = array(
					'#type' => 'select',
					'#title' => $title,
					'#options' => $tariff_plan_list,
//					'#default_value' => $selected_tariff_plan[0],
				);
				$form['#date_list'][] = $title;
			}

			$form['tariff_plan']['markup:'.$date] = array(
				'#markup' => '<br>',
			);
		}

		//dpm( $form['#tariff_plan'], 'tariff plan');
		//dpm( $start_date_list, 'start date list');

	}

	/*
	global $json_country;
	global $json_partner;
	global $json_rate;

	$json = array( 'country' => $json_country, 'partner' => $json_partner, 'tariff' => $json_rate);
	*/

    $form['actions'] = array('#type' => 'actions');

	if ( ! empty( $response_data)) {
		$form['data'] = array(
			'#type' => 'fieldset',
			'#title' => 'API Return Result',
			'#collapsible' => TRUE, 
			'#collapsed' => FALSE,
		);

		$form['data']['response'] = array(
			'#type' => 'textarea',
			'#rows' => 20,
			'#default_value' => $response->data,
	//		'#default_value' => $json[$type],
		);

		$form['actions']['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Update Configuration'),
		);

	}

    $form['actions']['cancel'] = array(
        '#type' => 'submit',
        '#value' => t('Cancel'),
    );


    return $form;
}


/* 
   validate 
*/
function ocs_roaming_import_validate( $form, &$form_state)
{
	$values = $form_state['values'];
    if ( $values['op'] == 'Update Configuration') {
		if ( $form['#config_type'] == 'tariff') {

			/* bhtak 13/08/15
			   do not check number of tariff plans
			$num = count( array_get_value( $form['#start_date_list'], FALSE));
			if ( $num != count( $form['#tariff_plan_list'])) {
				form_set_error( 'product', t('The product <em>@name</em> has not enough tariff plans. It must have at least @num plans.',
					array( '@name' => $form['product']['#options'][$values['product']], '@num' => $num)));
			}
			*/

			foreach( $values['tariff_plan'] as $k => $v) {
				$node = node_load( $v);
				if ( ! isset( $node->field_ref_roaming_plan['und'][0]['nid'])) {
					form_set_error( $k, t('No roaming plan is selected for tariff plan <em>@name</em>', 
						array( '@name' => $k)));
				}
			}
		}
	}
}

function _ocs_roaming_get_tariff_plan( $product_nid)
{
	// check if it has tariff plan
	$result = ocs_get_nids_by_cond( 'tariffplan', array(
		array('field_ref_product', 'nid', $product_nid)));

	$tariff_plan_list = array();

	if ( ! empty( $result)) {
		/* get terms */
		$tree_tid = ocs_get_terms_tid('TPL_DEFAULT_TREE_MOBILE');

		foreach( $result as $nid) {
			$tp = node_load( $nid);
			if ( $tp->field_ref_tree_tid['und'][0]['value'] == $tree_tid['Voice'] 
				 || $tp->field_ref_tree_tid['und'][0]['value'] == $tree_tid['SMS'] ) {
				$tariff_plan_list[$nid] = $tp->title;
			}
		}
	}

	return $tariff_plan_list;

}

/*
    submit OCS configuration
*/
function ocs_roaming_import_submit( $form, &$form_state)
{
	$values = $form_state['values'];

    if ( $values['op'] == 'Update Configuration') {
        if ( $form['#config_type'] == 'country') {
        	$result = _ocs_roaming_save_country( $values['delete'], $values['reset'], $values['response']);
			$form_state['redirect'] = 'common/roaming/country/list';
		}
		else if ( $form['#config_type'] == 'partner') {
        	$result = _ocs_roaming_save_partner( $values['delete'], $values['reset'], $values['response']);
			$form_state['redirect'] = 'common/roaming/carrier/list';
		}
		else if ( $form['#config_type'] == 'tariff') {
			$tariff_plan_list = array();
			foreach( $form['#date_list'] as $t) {
				$tariff_plan_list[$t] = $values['tariff_plan'][$t];
			}
        	$result = _ocs_roaming_save_tariff( $values['delete'], $values['reset'], $values['response'], $tariff_plan_list);
			$form_state['redirect'] = 'common/roaming/plan/list';
		}
		else {
			return;
		}

		if ( $result === TRUE) {
            drupal_set_message( t('Roaming Configuration is updated.'));
        }
        else {
            drupal_set_message( t('Failed to update roaming configuration.'), 'warning');
        }
    }

}



function _ocs_roaming_save_partner( $delete, $reset, $json)
{
    $result = ocs_get_nids_by_cond( 'roaming_carrier');
    $plist = array();

    if ( !empty( $result)) {
        foreach( $result as $nid) {
            $plist[$nid] = TRUE;
        }
	}

	$partner_list = json_decode( $json, TRUE);

	foreach( $partner_list as $key => $partner) {
		// get special number plan for this category
		$rm = ocs_get_node_by_cond( 'roaming_carrier', $partner['PARTNER_ID'], array(
			array('field_partner_code', 'value', $key)));
		$new_node = FALSE;
		if ( ! isset( $rm->nid)) {
			dpm( 'New roaming partner ', $key);
			$new_node = TRUE;
			//$rm->field_prefix_multiple['und'][0]['value'] = $partner['intl_PREFIX'];
		}
		else {
			dpm( 'Existing roaming partner : ' . $rm->title, $key );
            $plist[$rm->nid] = FALSE;
		}

		if ( $new_node || $reset) {
			$rm->title = $partner['PARTNER_ID'];
			$rm->field_partner_code['und'][0]['value'] = $partner['PARTNER_ID'];
			$rm->field_description['und'][0]['value'] = $partner['DESCR'];
			$country = ocs_get_node_by_cond( 'roaming_country', NULL, array(
				array('field_country_code_3', 'value', substr($partner['TADIG'], 0, 3))));
			$rm->field_ref_roaming_country['und'][0]['nid'] = isset($country->nid) ? $country->nid : NULL;

			node_save( $rm);
		}
	}

    if ( $delete) {
        foreach( $plist as $nid => $status ) {
            if ( $status === TRUE) {
                $node = node_load( $nid);
                dpm( 'Remove undefined roaming partner : ' . $node->title);
                node_delete( $nid);
            }
        }
    }

	return TRUE;
}




// update roaming country information
function _ocs_roaming_save_country( $delete, $reset, $json)
{
    $result = ocs_get_nids_by_cond( 'roaming_country');
    $clist = array();

    if ( !empty( $result)) {
        foreach( $result as $nid) {
            $clist[$nid] = TRUE;
            if ( $reset) { // reset exist code
                $node = node_load( $nid);
                unset( $node->field_exit_code['und']);
                node_save( $node);
            }
        }
	}

	$country_list = json_decode( $json, TRUE);

	foreach( $country_list as $country) {
		// get special number plan for this category
		$rm = ocs_get_node_by_cond( 'roaming_country', $country['COUNTRY_NAME'], array(
					array('field_country_code_3', 'value', $country['COUNTRY_CD'])));
		$rm->field_prefix_multiple['und'][0]['value'] = implode( '', explode(' ',$country['INTL_PREFIX']));
		$new_node = FALSE;
		if ( ! isset( $rm->nid)) {
			$rm->title = $country['COUNTRY_NAME'];
			dpm( 'New roaming country : ' . $rm->title);
			$new_node = TRUE;
		}
		else {
			dpm( 'Existing roaming country : ' . $rm->title);
            $clist[$rm->nid] = FALSE;
		}

		if ( $new_node || $reset) {
			$rm->field_country_code_3['und'][0]['value'] = $country['COUNTRY_CD'];
			$rm->field_time_zone['und'][0]['value'] = $country['GMT_OFFSET'];

			if ( ! empty( $country['PPS_EXIT_CD']) && array_search( $country['PPS_EXIT_CD'], array_get_value( $rm->field_exit_code, FALSE)) === FALSE) {
				$rm->field_exit_code['und'][] = array( 'value' => $country['PPS_EXIT_CD']); 
			}
			node_save( $rm);
		}
	}

    if ( $delete) {
        foreach( $clist as $nid => $status) {
            if ( $status === TRUE) {
                $node = node_load( $nid);
                dpm( 'Remove country : '. $node->title);
                node_delete( $nid);
            }
        }
    }

	return TRUE;
}


function _ocs_roaming_save_tariff( $delete, $reset, $json, $plan_list)
{
	dpm( $plan_list, 'plan_list');


	/* get terms */
	$terms = array();
	foreach( array('roaming_type', 'calltype', 'unit_of_measure', 'unit_of_range', 
				'usagetargetdomain', 'tpl_tariffplan_voice', 'tpl_tariffplan_sms') as $name) {
		$terms[$name] = ocs_get_terms_tid( $name);
	}

    dpm( $terms, 'terms');

	$tariff_plan_list = array();
	foreach( $plan_list as $k => $v) {
		$node = node_load($v);
		$tariff_plan_list[$k] = array( 
				'tariff' => $node, 
				'roaming' => node_load( $node->field_ref_roaming_plan['und'][0]['nid']));

		/* bhtak 13/08/15 do not update start date of tariff plan
		list( $type, $start_date) = explode( '|', $k);
		$node->field_valid_date_ymd['und'][0]['value'] = $start_date;
		dpm( $node, $node->title);
		node_save( $node);
		*/
	}

	$rate_list = json_decode( $json, TRUE);
	//dpm( $rate_list, 'rate list');

    $old_list = array();

	foreach( $plan_list as $plan_nid) {
		if ( $delete ) {
			// remove rate
			$rate_nids = ocs_get_nids_by_cond( 'rate', array(
				array('field_ref_tariffplan', 'nid', $plan_nid),
				array('field_ref_tree_tid', 'value', $terms['tpl_tariffplan_voice']['voice_tariffplan_roaming'])));

			if ( ! empty( $rate_nids)) {
				foreach( $rate_nids as $nid) {
                    $old_list['Rate'][$nid] = TRUE;
				}
			}

			$rate_nids = ocs_get_nids_by_cond( 'rate', array(
				array('field_ref_tariffplan', 'nid', $plan_nid),
				array('field_ref_tree_tid', 'value', $terms['tpl_tariffplan_sms']['sms_tariffplan_roaming'])));

			if ( ! empty( $rate_nids)) {
				foreach( $rate_nids as $nid) {
                    $old_list['Rate'][$nid] = TRUE;
				}
			}

			// remove ratinggroup
			$t = node_load( $plan_nid);
			$rg_nids = ocs_get_nids_by_cond( 'roaming_ratinggroup', array(
				array('field_ref_roaming_plan', 'nid', $t->field_ref_roaming_plan['und'][0]['nid'])));

			if ( ! empty( $rg_nids)) {
				foreach( $rg_nids as $nid) {
                    $old_list['Rating Group'][$nid] = TRUE;
				}
			}

			// remove basicrate roaming
			$rate_nids = ocs_get_nids_by_cond( 'basicrate_roaming', array(
				array('field_ref_tariffplan', 'nid', $plan_nid)));

			if ( ! empty( $rate_nids)) {
				foreach( $rate_nids as $nid) {
                    $old_list['Basic Rate'][$nid] = TRUE;
				}
			}
		}

		// initialize roaming plan
		/*
		$t = node_load( $plan_nid);
		$plan = node_load( $t->field_ref_roaming_plan['und'][0]['nid']);
		unset( $plan->field_ref_roaming_ratinggroup['und']);
		node_save( $plan);
		*/
	}

	foreach( $plan_list as $plan => $plan_nid) {
		list( $tariff_type, $start_date) = explode( '|', $plan);

		foreach( $rate_list as $key => $records) {
			$list = explode( '_', $key);
			if ( $list[1] == 'Cus' || $list[0] == 'IDD') {
				_save_roaming_intl_zone( $reset, $terms, $records);
			}
			else if ( $list[1] != 'Customer') {
				dpm( 'Invalid key ' . $key);
				continue;
			}

			$tariffs = array();
			foreach( $records as $rec) {
				if ( $rec['RATE_APLY_DV_CD'] != RATE_APLY_DV_CD_STEP)  {
					drupal_set_message( 'Invalid rate type : ' . $rec['RATE_APLY_DV_CD'], 'error');
					$stop = TRUE;
					continue;
				}

				list( $plmn, $calltype) = _ocs_roaming_get_plmn_calltype( $rec);
				if ( empty( $plmn)) continue;

				if ( ($tariff_type == 'SMS' && strstr( $calltype, 'SMS')) 	// SMS call type
					|| ($tariff_type == 'VOICE' && strstr( $calltype, 'SMS') === FALSE)) { 	// Voice call type
					$k = $tariff_type.':'.$plmn.':'.$calltype;
					if ($start_date >= $rec['VALD_STRT_DT'] ) {
						if ( ! isset( $tariffs[$k]) || $tariffs[$k]['VALD_STRT_DT'] < $rec['VALD_STRT_DT']) {
							// save the tariff if it's not saved or its VALD_STRT_DT is later than saved one
							$tariffs[$k] = $rec;
						}
					}
				}
			}

			if ( ! empty( $tariffs)) {
				_save_roaming_tariff_op( $reset, $terms, $plan, $plan_nid, $key, $tariffs, $tariff_plan_list, $old_list);
                dpm( t( 'Start date : @tm, Partner : @p', array( '@tm' => $plan, '@p' => $key)));
			}
		}
	}

    if ( $delete) {
        dpm( $old_list, 'old list');
        foreach( $old_list as $type => $list) {
            foreach( $list as $nid => $status) {
                if ( $status === TRUE) {
                    $node = node_load( $nid);
                    dpm( t('Remove unused @type : @title ', 
                        array( '@type' => $type, '@title' => $node->title)));
                    node_delete( $nid);
                }
            }
        }

		$t = node_load( $plan_nid);
		$plan = node_load( $t->field_ref_roaming_plan['und'][0]['nid']);
		unset( $plan->field_ref_roaming_ratinggroup['und']);
		foreach( $old_list['Rating Group'] as $nid => $remove_flag) {
			if ( $remove_flag == FALSE) {
				$plan->field_ref_roaming_ratinggroup['und'][] = array( 'nid' => $nid);
			}
		}
		node_save( $plan);
	}

	return TRUE;
}

function _save_roaming_tariff_op( $reset, $terms, $plan, $plan_nid, $key, $tariffs, $tariff_plan, &$old_list)
{
	// customer tariff has key with format '<Partner Name>_Customer'
	$list = explode( '_', $key);
	$partner_code = $list[0];
	$roaming_intl_zone_nid = 0;
	if ($list[1] == 'Cus' || $list[0] == 'IDD') {
		// add condition for romaing_intl_zone
		$nids = ocs_get_nids_by_cond( 'roaming_zone', array(
					array('property', 'title', $key)));
		if ( count( $nids) > 1 || count( $nids) == 0) {
			drupal_set_message( t('Invalid Roaming INTL Zone <em>@name</em>. @n items are found.', 
					array( '@name' => $key, '@n' => count($nids))), 'error');
			return;
		}
		$roaming_intl_zone_nid = $nids[0];
	}

	$tariff_ptr = $tariff_plan[$plan]['tariff'];

	$t = node_load( $plan_nid);
	$plan_ptr = node_load( $t->field_ref_roaming_plan['und'][0]['nid']);

//	dpm( $tariff_ptr, $tariff_ptr->title);
	//dpm( $plan_ptr, $plan_ptr->title);

	$partner = ocs_get_node_by_cond( 'roaming_carrier', NULL, array(
		array('field_partner_code', 'value', $partner_code)));
	if ( isset( $partner->nid) || strstr( $partner_code, 'DEFAULT')  || 
			substr( $partner_code, 0, 3) == 'IDD') {
		$partner_name = isset( $partner->nid) ? $partner->title : $partner_code;
		foreach( $tariffs as $plmn_calltype => $rec) {
			list( $tariff_type, $plmn, $calltype) = explode( ':', $plmn_calltype);

			$tariff = '';
			if ( !empty( $rec['INIT_RATE_APLY_UNIT']))
				$tariff = $rec['INIT_RATE_APLY_UNIT'] . '_' . $rec['INIT_RATE'] . '_';
			$tariff .= $rec['RATE_APLY_UNIT'] . '_' . $rec['RATE'];

			if ( ($tariff_type == 'SMS' && $rec['RATE_APLY_UNIT_CD'] != RATE_UNIT_COUNT) ||
				($tariff_type == 'VOICE' && $rec['RATE_APLY_UNIT_CD'] != RATE_UNIT_SECOND)) {
				drupal_set_message( t('Error : Invalid rate unit for @t:@u', array( '@t' => $tariff_type, '@u' => $rec['RATE_APLY_UNIT_CD'])), 'error');
				$stop = TRUE;
				continue;
			}

			$tariff = $tariff_type . '_' . $tariff;
            $tid = $terms['tpl_tariffplan_'.strtolower($tariff_type)][strtolower($tariff_type).'_tariffplan_roaming'];

			// add tariff
			$rate = ocs_get_node_by_cond( 'rate', $tariff, array(
				array('property', 'title', $tariff),
				array('field_ref_tariffplan', 'nid', $tariff_ptr->nid),
				array('field_ref_tree_tid', 'value', $tid)));
			$new_node = FALSE;
			if ( ! isset( $rate->nid)) {
				$rate->title = $tariff;
				dpm( t( '@p) New roaming rate : @t', array( '@p' => $partner_code, '@t' => $tariff)));
				$new_node = TRUE;
			}
			else {
				dpm( t( '@p) Existing roaming rate : @t', array( '@p' => $partner_code, '@t' => $tariff)));
                $old_list['Rate'][$rate->nid] = FALSE;
			}

			if ( $new_node || $reset) {
				$rate->field_range_units['und'][0]['tid'] = $terms['unit_of_range']['Seconds'];
				$rate->field_uom_units['und'][0]['tid'] = $terms['unit_of_measure']['Seconds'];
				if ( strstr( $calltype, 'SMS')) {

					$rate->field_ref_tariffplan['und'][0]['nid'] = $tariff_ptr->nid;
					$rate->field_ref_tree_tid['und'][0]['value'] = $tid;
					$rate->field_price['und'][0]['value'] = floatval($rec['RATE']);
				}
				else {
					if ( ! empty( $rec['INIT_RATE_APLY_UNIT'])) {
						_save_charge( $rate, 0, 0, $rec['INIT_RATE_APLY_UNIT'], $rec['INIT_RATE_APLY_UNIT'], $rec['INIT_RATE']);
						_save_charge( $rate, 1, $rec['INIT_RATE_APLY_UNIT'], null, $rec['RATE_APLY_UNIT'], $rec['RATE']);
					}
					else {
						_save_charge( $rate, 0, 0, null, $rec['RATE_APLY_UNIT'], $rec['RATE']);
					}

					$rate->field_ref_tariffplan['und'][0]['nid'] = $tariff_ptr->nid;
					$rate->field_ref_tree_tid['und'][0]['value'] = $tid;
				}

				node_save( $rate);
			}

			//print_r( $rec);


			// get rating group
			$rg = $partner_name . '_' . $tariff;
			$cond = array(
				array('field_rating_group', 'value', $rg),
				array('field_ref_roaming_plan', 'nid', $plan_ptr->nid),
				array('field_ref_type_of_call', 'tid', $terms['calltype'][$calltype]));
			if ( $roaming_intl_zone_nid > 0) {
				$cond[] = array( 'field_roaming_zone', 'nid', $roaming_intl_zone_nid);
			}
			$rm = ocs_get_node_by_cond( 'roaming_ratinggroup', $rg, $cond);
			$new_node = FALSE;
			if ( ! isset( $rm->nid)) {
				$rm->title = $rg;
				$rm->field_rating_group['und'][0]['value'] = $rg;
				dpm( 'New roaming group : ' . $rg);

				$new_node = TRUE;
			}
			else {
				dpm( t( '@code) Existing roaming group : @rg ratinggroup:@nid',
					array( '@code' => $partner_code, '@rg' => $rg, '@nid' => $rm->nid)));
                $old_list['Rating Group'][$rm->nid] = FALSE;
			}

			if ( $new_node || $reset) {
				if ( empty( $partner)) {
					unset( $rm->field_ref_roaming_country['und']);
					unset( $rm->field_ref_roaming_carrier['und']);
				}
				else {
					$rm->field_ref_roaming_country['und'][0]['nid'] = $partner->field_ref_roaming_country['und'][0]['nid'];
					$rm->field_ref_roaming_carrier['und'][0]['nid'] = $partner->nid;
				}
				$rm->field_ref_type_of_call['und'][0]['tid'] = $terms['calltype'][$calltype];
				$rm->field_ref_roaming_plan['und'][0]['nid'] = $plan_ptr->nid;

				if ($plmn == 'Outgoing SMS') 
					unset( $rm->field_ref_roaming_type['und']);		// set a NULL for outgoing SMS
				else 
					$rm->field_ref_roaming_type['und'][0]['tid'] = $terms['roaming_type'][$plmn];

				if ( $roaming_intl_zone_nid > 0) {
					$rm->field_roaming_zone['und'][0]['nid'] = $roaming_intl_zone_nid;
				}

				//dpm( $rm, $rm->title);
				node_save( $rm);
			}


			if ( FALSE === array_search( $rm->nid, array_get_value( $plan_ptr->field_ref_roaming_ratinggroup, FALSE))) {
				dpm( 'Insert to rating group list of the plan:'. $rm->nid );
				//print_r( array_get_value( $plan->field_ref_roaming_ratinggroup, FALSE));
				$plan_ptr->field_ref_roaming_ratinggroup['und'][] = array( 'nid' => $rm->nid);
				//dpm( $plan, 'plan');
			}
		
			// add mapping
			// tariff mapping
			$result = ocs_get_nids_by_cond( 'basicrate_roaming', array(
				array('field_ref_tariffplan', 'nid', $tariff_ptr->nid),
				array('field_rating_group', 'value', $rg)));

			if ( empty($result)) {
				$mapping = ocs_admin_get_new_node( 'basicrate_roaming');
				$mapping->field_ref_tariffplan['und'][0]['nid'] = $tariff_ptr->nid;
				$mapping->field_ref_rate['und'][0]['nid'] = $rate->nid;
				$mapping->field_rating_group['und'][0]['value'] = $rg;

				node_save( $mapping);
			}
			else if ( count( $result) == 1) {
				$node = node_load( $result[0]);
				$node->field_ref_rate['und'][0]['nid'] = $rate->nid;

				node_save( $node);

                $old_list['Basic Rate'][$result[0]] = FALSE;
			}
			else {	// too many mapping
				drupal_set_message( 'Invalid tariff mapping ', 'error');
				continue;
			}
		}

		//dpm( $plan_ptr, 'update plan');
		node_save( $plan_ptr);
	}
	else {
		drupal_set_message( 'Invalid Partner : ' . $key, 'error');
	}

}

function _ocs_roaming_get_plmn_calltype( $rec)
{
	$plmn = $calltype = NULL;

	if ( $rec['IOCLL_DV_CD'] == '2') { // incoming call
		if ( $rec['FTR_CD'] == RoamingRSMS || $rec['FTR_CD'] == RoamingSMS) {
			$plmn = 'Incoming';
			$calltype = 'SMS_ROAMING_RECEIVE';
		}
		else {
			$plmn = 'Incoming';
			$calltype = 'MOBILE_ROAMING_RECEIVE_CALL';
		}
	}
	else {
		if ( $rec['FTR_CD'] == RoamingHCC ) {
			$plmn = 'HPLMN';
			$calltype = 'MOBILE_ROAMING_HOME';
		}
		else if ( $rec['FTR_CD'] == RoamingIVC ) {
			$plmn = 'Other PLMN';
			$calltype = 'MOBILE_ROAMING_OTHER_COUNTRY';
		}
		else if ( $rec['FTR_CD'] == RoamingLVC ) {
			$plmn = 'VPLMN';
			$calltype = 'MOBILE_ROAMING_TO_NATIONAL';
		}
		else if ( $rec['FTR_CD'] == RoamingRSMS ) {
			$plmn = 'Incoming';
			$calltype = 'SMS_ROAMING_RECEIVE';
		}
		else if ( $rec['FTR_CD'] == RoamingSMS ) {
			$plmn = 'Outgoing SMS';
			$calltype = 'SMS_ROAMING_SENT';
		}
		else if ( $rec['FTR_CD'] == RoamingGPRS ) {
			// TODO implement roaming GPRS
//			drupal_set_message( 'Roaming GPRS : Not implmented ', 'error');
		}
		else if ( $rec['FTR_CD'] == RoamingIntlVoice) {
			$plmn = 'Other PLMN';
			$calltype = 'MOBILE_ROAMING_OTHER_COUNTRY';
		}
		else {
			drupal_set_message( 'Warning : invalid FTR_CD ' . $rec['FTR_CD'], 'error');
		}
	}

	return array( $plmn, $calltype);
}

function _batch_build_delete_node( $nid, $operation_details, &$context)
{
	node_delete( $nid);

	// Optional message displayed under the progressbar.
	$context['message'] = $operation_details . ':' . $nid;

	_batch_update_http_requests();
}

function _batch_build_reset_basicrate( $nid, $operation_details, &$context)
{
	$node = node_load( $nid);
	unset( $node->field_ref_rate['und']);
	unset( $node->field_rating_group['und']);
	node_save( $node);

	// Optional message displayed under the progressbar.
	$context['message'] = $operation_details . ':' . $nid;

	_batch_update_http_requests();
}

function _batch_build_save_roaming_tariff_op( $env, $plan, $plan_nid, $key, $records, $operation_details, &$context)
{
	$stop = FALSE;

	// customer tariff has key with format '<Partner Name>_Customer'
	//dpm( $records, 'Import tariff');
	/*
	$nid = $env['tariff']->field_ref_roaming_plan['und'][0]['nid'];
	$plan = node_load( $nid);

	$nid = $env['sms_tariff']->field_ref_roaming_plan['und'][0]['nid'];
	$sms_plan = node_load( $nid);
	*/
	$list = explode( '_', $key);
	$partner_code = $list[0];

	$tariff_ptr =& $env['tariff_plan'][$plan]['tariff'];

	$t = node_load( $plan_nid);
	$plan_ptr = node_load( $t->field_ref_roaming_plan['und'][0]['nid']);

//	dpm( $tariff_ptr, $tariff_ptr->title);
	//dpm( $plan_ptr, $plan_ptr->title);

	$partner = ocs_get_node_by_cond( 'roaming_carrier', NULL, array(
		array('field_partner_code', 'value', $partner_code)));
	if ( isset( $partner->nid) || strstr( $partner_code, 'DEFAULT')) {
		foreach( $records as $plmn_calltype => $rec) {
			list( $tariff_type, $plmn, $calltype) = explode( ':', $plmn_calltype);

			$tariff = $rec['RATE_APLY_UNIT'] . '_' . $rec['RATE'];
			if ( !empty( $rec['INIT_RATE_APLY_UNIT']))
				$tariff .= $rec['INIT_RATE_APLY_UNIT'] . '_' . $rec['INIT_RATE'];

			if ( ($tariff_type == 'SMS' && $rec['RATE_APLY_UNIT_CD'] != RATE_UNIT_COUNT) ||
				($tariff_type == 'VOICE' && $rec['RATE_APLY_UNIT_CD'] != RATE_UNIT_SECOND)) {
				drupal_set_message( t('Error : Invalid rate unit for @t:@u', array( '@t' => $tariff_type, '@u' => $rec['RATE_APLY_UNIT_CD'])), 'error');
				$stop = TRUE;
				continue;
			}

			$tariff = 'ROAMING_' . $tariff_type . '_' . $tariff;

			// add tariff
			$rate = ocs_get_node_by_cond( 'rate', $tariff, array(
				array('field_ref_tariffplan', 'nid', $tariff_ptr->nid)));
			$new_node = FALSE;
			if ( ! isset( $rate->nid)) {
				$rate->title = $tariff;
				dpm( t( '@p) New roaming rate : @t', array( '@p' => $partner_code, '@t' => $tariff)));
				$new_node = TRUE;
			}
			else {
				dpm( t( '@p) Existing roaming rate : @t', array( '@p' => $partner_code, '@t' => $tariff)));
			}

			if ( $new_node || $env['reset']) {
				$rate->field_range_units['und'][0]['tid'] = $env['unit_range']['Seconds'];
				$rate->field_uom_units['und'][0]['tid'] = $env['unit_measure']['Seconds'];
				if ( strstr( $calltype, 'SMS')) {

					$rate->field_ref_tariffplan['und'][0]['nid'] = $tariff_ptr->nid;
					$rate->field_ref_tree_tid['und'][0]['value'] = $env['tree_tid']['sms'];
					$rate->field_price['und'][0]['value'] = floatval($rec['RATE']);
				}
				else {
					if ( isset( $rate->field_charge_collection['und'][0]['value'])) {
						$vs = entity_load_single( 'field_collection_item', $rate->field_charge_collection['und'][0]['value']);
					}
					else {
						$vs = entity_create('field_collection_item', array('field_name' => 'field_charge_collection'));
						$vs->setHostEntity( 'node', $rate);
					}

					$idx = 0;
					$vs->field_range_start['und'][$idx]['value'] = 0;
					if ( ! empty( $rec['INIT_RATE_APLY_UNIT'])) {
						$vs->field_uom_amount['und'][$idx]['value'] = $rec['INIT_RATE_APLY_UNIT'];
						$vs->field_price_amount_float['und'][$idx]['value'] = floatval($rec['INIT_RATE']);
						$idx ++;
						$vs->field_range_start['und'][$idx]['value'] = $rec['INIT_RATE_APLY_UNIT'];
					}

					$vs->field_uom_amount['und'][$idx]['value'] = $rec['RATE_APLY_UNIT'];
					$vs->field_price_amount_float['und'][$idx]['value'] = floatval($rec['RATE']);

					$vs->save();

					$rate->field_ref_tariffplan['und'][0]['nid'] = $tariff_ptr->nid;
					$rate->field_ref_tree_tid['und'][0]['value'] = $env['tree_tid']['voice'];
				}

				node_save( $rate);
			}

			//print_r( $rec);


			// get special number plan for this category
			//$rate_code = str_replace( ' ', '_', $partner_code . '_' . $plmn);
			$rm = ocs_get_node_by_cond( 'roaming_ratinggroup', $tariff, array(
				array('field_rating_group', 'value', $tariff),
				array('field_ref_roaming_plan', 'nid', $plan_ptr->nid),
				array('field_ref_type_of_call', 'tid', $env['call_type'][$calltype])));
			$new_node = FALSE;
			if ( ! isset( $rm->nid)) {

				$rm->title = $tariff;
				$rm->field_rating_group['und'][0]['value'] = $tariff;
				dpm( 'New roaming group : ' . $tariff);

				$new_node = TRUE;
			}
			else {
				dpm( t( '@code) Existing roaming group : @tariff ratinggroup:@nid',
					array( '@code' => $partner_code, '@tariff' => $tariff, '@nid' => $rm->nid)));
			}

			if ( $new_node || $env['reset']) {
				if ( empty( $partner)) {
					unset( $rm->field_ref_roaming_country['und']);
					unset( $rm->field_ref_roaming_carrier['und']);
				}
				else {
					$rm->field_ref_roaming_country['und'][0]['nid'] = $partner->field_ref_roaming_country['und'][0]['nid'];
					$rm->field_ref_roaming_carrier['und'][0]['nid'] = $partner->nid;
				}
				$rm->field_ref_type_of_call['und'][0]['tid'] = $env['call_type'][$calltype];
				$rm->field_ref_roaming_plan['und'][0]['nid'] = $plan_ptr->nid;

				if ($plmn == 'Outgoing SMS') 
					unset( $rm->field_ref_roaming_type['und']);		// set a NULL for outgoing SMS
				else 
					$rm->field_ref_roaming_type['und'][0]['tid'] = $env['roaming_type'][$plmn];

				//dpm( $rm, $rm->title);
				node_save( $rm);
			}


			if ( FALSE === array_search( $rm->nid, array_get_value( $plan_ptr->field_ref_roaming_ratinggroup, FALSE))) {
				dpm( 'Insert to rating group list of the plan:'. $rm->nid );
				//print_r( array_get_value( $plan->field_ref_roaming_ratinggroup, FALSE));
				$plan_ptr->field_ref_roaming_ratinggroup['und'][] = array( 'nid' => $rm->nid);
				//dpm( $plan, 'plan');
			}
		
			// add mapping
			// tariff mapping
			$result = ocs_get_nids_by_cond( 'basicrate_roaming', array(
				array('field_ref_tariffplan', 'nid', $tariff_ptr->nid),
				array('field_rating_group', 'value', $tariff)));

			if ( empty($result)) {
				$mapping = ocs_admin_get_new_node( 'basicrate_roaming');
				$mapping->field_ref_tariffplan['und'][0]['nid'] = $tariff_ptr->nid;
				$mapping->field_ref_rate['und'][0]['nid'] = $rate->nid;
				$mapping->field_rating_group['und'][0]['value'] = $tariff;

				node_save( $mapping);
			}
			else if ( count( $result) == 1) {
				$node = node_load( $result[0]);
				$node->field_ref_rate['und'][0]['nid'] = $rate->nid;

				node_save( $node);
			}
			else {	// too many mapping
				drupal_set_message( 'Invalid tariff mapping ', 'error');
				continue;
			}
		}

		//dpm( $plan_ptr, 'update plan');
		node_save( $plan_ptr);
	}
	else {
		drupal_set_message( 'Invalid Partner : ' . $key, 'error');
	}

	if ( $stop === TRUE) {
		dpm( $records, 'Invalid roaming tariff');
		$result = array('status' => FALSE, 'data' => 'Invalid Roaming Tariff');
	  	die(json_encode($result));
	}

	// Store some result for post-processing in the finished callback.

	// Optional message displayed under the progressbar.
	$context['message'] = 'Importing roaming tariff : ' . $operation_details;
	//if ( $stop === TRUE ) $context['finished'] = 1;

	_batch_update_http_requests();
}

function _batch_build_save_roaming_tariff_finished($success, $results, $operations) 
{
	// remove NULL rating group
	/*
	for( $i=0; $i < count($plan->field_ref_roaming_ratinggroup['und']); $i++) {
		if ( empty( $plan->field_ref_roaming_ratinggroup['und'][$i]['nid']))
			unset( $plan->field_ref_roaming_ratinggroup['und'][$i]);
	}

	for( $i=0; $i < count($sms_plan->field_ref_roaming_ratinggroup['und']); $i++) {
		if ( empty( $sms_plan->field_ref_roaming_ratinggroup['und'][$i]['nid']))
			unset( $sms_plan->field_ref_roaming_ratinggroup['und'][$i]);
	}
	*/

	if ($success) {
		// Here we could do something meaningful with the results.
		// We just display the number of nodes we processed...
		drupal_set_message(t('@count results processed in @requests HTTP requests.', 
			array('@count' => count($results), 
				'@requests' => _batch_get_http_requests())));
		drupal_set_message(t('The final result was "%final"', array('%final' => end($results))));
	}
	else {
		// An error occurred.
		// $operations contains the operations that remained unprocessed.
		$error_operation = reset($operations);
		drupal_set_message(t('An error occurred while processing @operation with arguments : @args', 
			array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
	}

	return TRUE;
}



// ajax handler
function ocs_ajax_select_roaming_product($form, &$form_state)
{
	return $form['tariff_plan'];
}

function _save_roaming_intl_zone( $reset, $terms, $records)
{
	//dpm( $records);
	foreach( $records as $record) {
		// find roaming zone by title
		$name = $record['PROD_CD'];
		$nids = ocs_get_nids_by_cond( 'roaming_zone', array(
					array( 'property', 'title', $name)
						));
		if ( count( $nids) > 1) {
			// error
			drupal_set_message( t('Multiple Roaming INTL Zone is found for @name', array( '@name' => $name)), 'error');
		}
		else {
			if ( count( $nids) == 0) {
				$zone = ocs_admin_get_new_node( 'roaming_zone');
				$zone->title = $name;
				dpm( 'New Roaming INTL Zone : ' . $name);
			}
			else {
				$zone = node_load( $nids[0]);
				unset( $zone->field_roaming_countries['und']);
				dpm( 'Existing Roaming INTL Zone : ' . $name);
			}

			// add country list
			foreach( $record['COUNTRY_CD'] as $country) {
				$country_nids = ocs_get_nids_by_cond( 'roaming_country', array(
							array( 'field_country_code_3', 'value', $country)
							));
				if ( count($country_nids) > 1 || count( $country_nids) == 0) {
					drupal_set_message( t('Invalid Roaming Country <em>@name</em>. @n items found.', 
						array( '@name' => $country, '@n' => count( $country_nids))), 'error');
					continue;
				}
				else {
					$zone->field_roaming_countries['und'][] = array( 'nid' => $country_nids[0]);
				}
			}

			// find roaming partner nid
			// name format : <Partner Name>_Cus_??
			$list = explode( '_', $name);
			$partner_nid = ocs_get_nids_by_cond( 'roaming_carrier', array(
						array( 'field_partner_code', 'value', $list[0])
						));
			if ( count( $partner_nid) > 1 ) {
				drupal_set_message( t('Invalid Roaming Carrier <em>@name</em>. @n items found.', 
					array( '@name' => $list[0], '@n' => count( $partner_nid))), 'error');
				continue;
			}
			else {
				$zone->field_roaming_carrier['und'][0]['nid'] = $partner_nid[0];
			}

			node_save( $zone);
		}
	}
}

function _save_charge( $rate, $idx, $start, $end, $uom_amount, $price) 
{
	if ( isset( $rate->field_charge_collection['und'][$idx]['value'])) {
		$vs = entity_load_single( 'field_collection_item', $rate->field_charge_collection['und'][$idx]['value']);
	}
	else {
		$vs = entity_create('field_collection_item', array('field_name' => 'field_charge_collection'));
		$vs->setHostEntity( 'node', $rate);      
	}

	$vs->field_range_start['und'][0]['value'] = $start;
	if ( ! empty( $end)) $vs->field_range_end['und'][0]['value'] = $end;
	$vs->field_uom_amount['und'][0]['value'] = $uom_amount;
	$vs->field_price_amount_float['und'][0]['value'] = floatval($price);
	$vs->save();
}

