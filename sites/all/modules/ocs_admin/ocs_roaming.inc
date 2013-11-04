<?php
define( 'RoamingIntlVoice', '1011');
define( 'RoamingIntlSMS', '1010');

define( 'RoamingHCC', '1031');
define( 'RoamingIVC', '1032');
define( 'RoamingLVC', '1033');
define( 'RoamingIncomingVC', '1035');

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
					if ( $selected_product_nid == 0 || $node->field_product_id['und'][0]['value'] == 'default_pps') {
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
			'#default_value' => $response_data,
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
	global $user;

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

			$_SESSION['http_request_count'] = 0; // reset counter for debug information.
			$_SESSION['redirect_after_batch'] = 'common/roaming/plan/list';
			$_SESSION['import_roaming_tariff'][$user->uid] = array();

        	$batch = _ocs_roaming_save_tariff( $values['delete'], $values['reset'], $values['response'], $tariff_plan_list);
			batch_set( $batch);

			return;
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
	global $user;

	dpm( $plan_list, 'plan_list');

	/* get terms */
	$terms = array();
	foreach( array('roaming_type', 'calltype', 'unit_of_measure', 'unit_of_range', 
				'usagetargetdomain', 'tpl_tariffplan_voice', 'tpl_tariffplan_sms') as $name) {
		$terms[$name] = ocs_get_terms_tid( $name);
	}

    dpm( $terms, 'terms');

	$_SESSION['import_roaming_tariff'][$user->uid]['terms'] = $terms;

	$tariff_plan_list = array();
	foreach( $plan_list as $k => $v) {
		list( $tariff_type, $start_date) = explode( '|', $k);
        if ( ! isset( $tariff_plan_list[$v])) {
            $tariff_plan_list[$v] = array( 
				'tariff' => node_load($v),
				'tariff_type' => $tariff_type,
				'start_date' => $start_date,
                );
        }

		/* bhtak 13/08/15 do not update start date of tariff plan
		list( $type, $start_date) = explode( '|', $k);
		$node->field_valid_date_ymd['und'][0]['value'] = $start_date;
		dpm( $node, $node->title);
		node_save( $node);
		*/
	}

    dpm( $tariff_plan_list, 'tariff_plan_list');

	$rate_list = json_decode( $json, TRUE);
	//dpm( $rate_list, 'rate list');

    $old_list = array();

	foreach( $tariff_plan_list as $plan) {
        $plan_ptr = $plan['tariff'];
		if ( $delete ) {
			// remove rate
			$rate_nids = ocs_get_nids_by_cond( 'rate', array(
				array('field_ref_tariffplan', 'nid', $plan_ptr->nid),
				array('field_ref_tree_tid', 'value', $terms['tpl_tariffplan_voice']['voice_tariffplan_roaming'])));

			if ( ! empty( $rate_nids)) {
				foreach( $rate_nids as $nid) {
                    $old_list[$plan_ptr->nid]['Rate'][$nid] = TRUE;
				}
			}

			$rate_nids = ocs_get_nids_by_cond( 'rate', array(
				array('field_ref_tariffplan', 'nid', $plan_ptr->nid),
				array('field_ref_tree_tid', 'value', $terms['tpl_tariffplan_sms']['sms_tariffplan_roaming'])));

			if ( ! empty( $rate_nids)) {
				foreach( $rate_nids as $nid) {
                    $old_list[$plan_ptr->nid]['Rate'][$nid] = TRUE;
				}
			}

			// remove ratinggroup
			$rg_nids = ocs_get_nids_by_cond( 'roaming_ratinggroup', array(
				array('field_ref_roaming_plan', 'nid', $plan_ptr->field_ref_roaming_plan['und'][0]['nid'])));

			if ( ! empty( $rg_nids)) {
				foreach( $rg_nids as $nid) {
                    $old_list[$plan_ptr->nid]['Rating Group'][$nid] = TRUE;
				}
			}

			// remove basicrate roaming
			$rate_nids = ocs_get_nids_by_cond( 'basicrate_roaming', array(
				array('field_ref_tariffplan', 'nid', $plan_ptr->nid)));

			if ( ! empty( $rate_nids)) {
				foreach( $rate_nids as $nid) {
                    $old_list[$plan_ptr->nid]['Basic Rate'][$nid] = TRUE;
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

	// store old_list
	$_SESSION['import_roaming_tariff'][$user->uid]['old_list'] = $old_list;

	// store country code
	$country_list = array();
	$nids = ocs_get_nids_by_cond( 'roaming_country', array());
	foreach( $nids as $nid) {
		$node = node_load( $nid);
		$country_list[$node->field_country_code_3['und'][0]['value']] = $nid;
	}
	$_SESSION['import_roaming_tariff'][$user->uid]['country_list'] = $country_list;

	// store partner code
	$partner_list = array();
	$nids = ocs_get_nids_by_cond( 'roaming_carrier', array());
	foreach( $nids as $nid) {
		$node = node_load( $nid);
		$partner_list[$node->field_partner_code['und'][0]['value']] = $nid;
	}
	$_SESSION['import_roaming_tariff'][$user->uid]['partner_list'] = $partner_list;

	$operations = array();
	$tariffs = array();
	$rating_group = array();
	foreach( $tariff_plan_list as $v) {
		$tariff_type = $v['tariff_type'];
        $plan_ptr = $v['tariff'];

        $rg_list = array();
        // get all the roaming rating group
        $nids = ocs_get_nids_by_cond( 'roaming_ratinggroup', array(
			array('field_ref_roaming_plan', 'nid', $plan_ptr->field_ref_roaming_plan['und'][0]['nid'])));
        foreach( $nids as $nid) {
            $rg = node_load( $nid);
            $rg_list[$rg->field_rating_group['und'][0]['value']][$rg->field_ref_type_of_call['und'][0]['tid']][] = $rg->nid;
        }
        dpm( $rg_list, 'rg_list');

        $old_rate_list = array();
        $nids = ocs_get_nids_by_cond( 'rate', array(
            array('field_ref_tariffplan', 'nid', $plan_ptr->nid),
            array('field_ref_tree_tid', 'value', 
                $terms['tpl_tariffplan_'.strtolower($tariff_type)][strtolower($tariff_type).'_tariffplan_roaming'])));
        foreach( $nids as $nid) {
            $node = node_load( $nid);
            $old_rate_list[$node->title] = $nid;
        }

		foreach( $rate_list as $key => $records) {
			$list = explode( '_', $key);
			if ( $list[1] == 'Cus' || $list[0] == 'IDD') {
				$operations[] = array('batch_save_roaming_intl_zone', array( $reset, $terms, $records));
                //dpm( 'save roaming intl zone');
			}
			else if ( $list[1] != 'Customer') {
				dpm( 'Invalid key ' . $key);
				continue;
			}

			foreach( $records as $rec) {
				if ( $rec['RATE_APLY_DV_CD'] != RATE_APLY_DV_CD_STEP)  {
					drupal_set_message( 'Invalid rate type : ' . $rec['RATE_APLY_DV_CD'], 'error');
					$stop = TRUE;
					continue;
				}

				list( $plmn, $calltype) = _ocs_roaming_get_plmn_calltype( $rec);
				if ( empty( $plmn)) {
                    dpm( t('Invalid plmn:@p calltype=@c key=@k', array( '@p' => $plmn, '@c' => $calltype, '@k' => $key)));
                    continue;
                }

				if ( ($tariff_type == 'SMS' && strstr( $calltype, 'SMS')) 	// SMS call type
					|| ($tariff_type == 'VOICE' && strstr( $calltype, 'SMS') === FALSE)) { 	// Voice call type
					if ( ($tariff_type == 'SMS' && $rec['RATE_APLY_UNIT_CD'] != RATE_UNIT_COUNT) ||
						($tariff_type == 'VOICE' && $rec['RATE_APLY_UNIT_CD'] != RATE_UNIT_SECOND)) {
						drupal_set_message( t('Error : Invalid rate unit for @t:@u', 
								array( '@t' => $tariff_type, '@u' => $rec['RATE_APLY_UNIT_CD'])), 'error');
					}
					else {

                        $tariff = '';
                        if ( !empty( $rec['INIT_RATE_APLY_UNIT']))
                            $tariff = $rec['INIT_RATE_APLY_UNIT'] . '_' . $rec['INIT_RATE'] . '_';
                        $tariff .= $rec['RATE_APLY_UNIT'] . '_' . $rec['RATE'];
                        $tariff = $tariff_type . '_' . $tariff;

                        $tariffs[$tariff] = array(
                                'tariff_type' => $tariff_type, 
                                'plan' => $plan_ptr->nid, 
                                'rec' => $rec);

                        $k = $key . ':' . $plmn . ':' . $calltype;
                        $rg = $list[0] . '_' . $tariff;
                        if ( ! isset( $rating_group[$k]) ||
                            $rating_group[$k]['VALD_STRT_DT'] < $rec['VALD_STRT_DT']) {
                        // save the tariff if it's not saved or its VALD_STRT_DT is later than saved one

                            $rg_nids = array();
                            if ( isset( $rg_list[$rg][$terms['calltype'][$calltype]])) {
                                $rg_nids[] = $rg_list[$rg][$terms['calltype'][$calltype]];
                            }

                            $rate_nid = isset( $old_rate_list[$tariff]) ?  $old_rate_list[$tariff] : NULL;

                            $rating_group[$k] = array( 'rg' => $rg, 
                                'rg_nids' => array_get_value( $rg_nids, FALSE),
                                'plan' => $plan_ptr->nid,
                                'key' => $key,
                                'plmn' => $plmn,
                                'call_type' => $calltype,
                                'tariff' => $tariff, 
                                'rate_nid' => $rate_nid, 
                                'tariff_type' => $tariff_type,
                                'VALD_STRT_DT' => $rec['VALD_STRT_DT']);

                            dpm( t( '@key) save rating group:@rg plmn=@p calltype=@c tariff=@t (@tt) rg_nids=@nids',
                                array( '@rg' => $rg, '@key' => $key, '@p' => $plmn, '@c' => $calltype,
                                    '@t' => $tariff, '@tt' => $tariff_type, 
                                    '@nids' => implode( ',', array_get_value( $rg_nids, FALSE)))));
                        }
                        else {
                            /*
                            dpm( t( '@key) skip tariff (@k) @a:@b', 
                                array( '@key' => $key, '@k' => $k,
                                '@a' => $rating_group[$k]['VALD_STRT_DT'], 
                                '@b' => $rec['VALD_STRT_DT'])));
                                */
                        }
					}
				}
                else {
                    /*
                    dpm( t( '@k) skip record. tariff_type=@t calltype=@c', 
                        array( '@k' => $key, '@t' => $tariff_type, '@c' => $calltype)));
                        */
                }
			}

		}
	}

    /*
    dpm( $tariffs, 'tariff');
    dpm( $rating_group, 'rating group');

    return;
    */

	foreach( $tariffs as $k => $v) {
        $tid = $terms['tpl_tariffplan_'.strtolower($v['tariff_type'])][strtolower($v['tariff_type']).'_tariffplan_roaming'];
		$operations[] = array('batch_save_roaming_tariff', array( $k, $v['plan'], $tid, 
            $terms['unit_of_range']['Seconds'], $terms['unit_of_measure']['Seconds'], $v['rec']));
	}


    foreach( $rating_group as $rg) {
        $operations[] = array( 'batch_save_rating_group', array( $rg['rg'], $rg['rg_nids'], $rg['key'], 
            $rg['plan'], $rg['call_type'], $rg['plmn'], $rg['tariff'], $rg['rate_nid'],
            $terms['tpl_tariffplan_'.strtolower($rg['tariff_type'])][strtolower($rg['tariff_type']).'_tariffplan_roaming']));
    }

    if ( $delete) {
		foreach( $old_list as $plan_nid => $old_list_by_plan) {
			foreach( $old_list_by_plan as $type => $list) {
				foreach( $list as $nid => $status) {
					$operations[] = array('batch_delete_unused_tariff', array( $plan_nid, $type, $nid));
				}
			}
		}
	}

	foreach( $tariff_plan_list as $v) {
        $plan_ptr = $v['tariff'];
		$operations[] = array('batch_update_roaming_plan', array( $plan_ptr->nid));
    }

	$batch = array(
		'operations' => $operations,
		'finished' => 'batch_import_roaming_tariff_finished',
		'title' => t('Import Roaming Tariff '),
		'init_message' => t('Starting ... '),
		'progress_message' => t('Processed @current out of @total.'),
		'error_message' => t('Batch procedure has encountered an error.'),
	);

	return $batch;
}

function batch_update_roaming_plan( $plan_nid, &$context)
{
    $plan = node_load( $plan_nid);
	if ( isset( $plan->field_ref_roaming_plan['und'][0]['nid'])) {
		$roaming_plan = node_load( $plan->field_ref_roaming_plan['und'][0]['nid']);

		$nids = ocs_get_nids_by_cond( 'roaming_ratinggroup', array(
			array('field_ref_roaming_plan', 'nid', $roaming_plan->nid)));

		unset( $roaming_plan->field_ref_roaming_ratinggroup['und']);
		foreach( $nids as $nid) {
			$rg = node_load( $nid);
			$msg[] = array( 'info', t( 'Insert to rating group list of the plan:@p nid=@n rg=@rg', 
				array( '@p' => $roaming_plan->title, '@n' => $nid, '@rg' => $rg->field_rating_group['und'][0]['value'] )));
			$roaming_plan->field_ref_roaming_ratinggroup['und'][] = array( 'nid' => $nid);
		}
		node_save( $roaming_plan);
	}
	else {
		$msg[] = array( 'error', t( 'Invalid plan nid=@nid', array( '@nid' => $plan_nid)));
	}

	foreach( $msg as $m) {
		drupal_set_message( $m[1], $m[0]);
		$context['message'] .= '<br>' . $m[1];
	}

    _batch_update_http_requests();
}


function batch_save_rating_group( $rg, $rg_nids, $key, $plan_nid, $calltype, $plmn, $tariff, $rate_nid, $tid, &$context)
{
    global $user;

	$terms_ptr = &$_SESSION['import_roaming_tariff'][$user->uid]['terms'];
	$partner_ptr = &$_SESSION['import_roaming_tariff'][$user->uid]['partner_list'];
	$old_list_ptr = &$_SESSION['import_roaming_tariff'][$user->uid]['old_list'];

	// customer tariff has key with format '<Partner Name>_Customer'
	$list = explode( '_', $key);
	$partner_code = $list[0];
	$roaming_intl_zone_nid = 0;
	if ($list[1] == 'Cus' || $list[0] == 'IDD') {
		// add condition for romaing_intl_zone
		$nids = ocs_get_nids_by_cond( 'roaming_zone', array( array('property', 'title', $key)));
		if ( count( $nids) > 1 || count( $nids) == 0) {
			drupal_set_message( t('Invalid Roaming INTL Zone <em>@name</em>. @n items are found.',
				array( '@name' => $key, '@n' => count($nids))), 'error');
			return;
		}
		$roaming_intl_zone_nid = $nids[0];
	}

    $partner =  (isset( $partner_ptr[$partner_code])) ? node_load( $partner_ptr[$partner_code]) : NULL;  
	$plan_ptr = node_load( $plan_nid);

    if ( count( $rg_nids) == 0) {
        $cond = array(
            array('field_rating_group', 'value', $rg),
			array('field_ref_roaming_plan', 'nid', $plan_ptr->field_ref_roaming_plan['und'][0]['nid']),
            array('field_ref_type_of_call', 'tid', $terms_ptr['calltype'][$calltype]));
        if ( $roaming_intl_zone_nid > 0) {
            $cond[] = array( 'field_roaming_zone', 'nid', $roaming_intl_zone_nid);
        }
        $rg_nids = ocs_get_nids_by_cond( 'roaming_ratinggroup', $cond);
    }

    $update = FALSE;
    if ( count( $rg_nids ) >= 1) {
        if ( count( $rg_nids ) > 1) {
            $msg[] = array( 'errro', t('@code)  duplicated rating group rg=@rg nid=@nid',
                    array( '@code' => $partner_code, '@rg' => $rg, '@nid' => implode( ',', $rg_nid))));
        }

        // just one rating group
        //dpm( $rg_nids[0], 'rating group node');
        $rm = node_load( $rg_nids[0]);
        $msg[] = array( 'info', t( '@code) @key Existing roaming group : @rg ratinggroup:@nid calltype=@ct plmn=@pl ',
            array( '@code' => $partner_code, '@key' => $key, '@rg' => $rg, 
                '@nid' => $rm->nid, '@ct' => $calltype, '@pl' => $plmn)));
        $old_list_ptr[$plan_nid]['Rating Group'][$rm->nid] = FALSE;

    }
    else {
        $rm = ocs_admin_get_new_node( 'roaming_ratinggroup');
        $rm->title = $rg;
        $rm->field_rating_group['und'][0]['value'] = $rg;
        $msg[] = array( 'info', t( '@code) @key New roaming group : @rg ratinggroup: calltype=@ct plmn=@pl ',
            array( '@code' => $partner_code, '@key' => $key, '@rg' => $rg, 
                '@ct' => $calltype, '@pl' => $plmn)));
		$update = TRUE;
    }

    if ( empty( $partner)) {
        if ( isset( $rm->field_ref_roaming_country['und'][0]['nid'])) {
            unset( $rm->field_ref_roaming_country['und']);
            $update = TRUE;
            $msg[] = array( 'info', 'roaming_country unset');
        }
        if ( isset( $rm->field_ref_roaming_carrier['und'][0]['nid'])) {
            unset( $rm->field_ref_roaming_carrier['und']);
            $update = TRUE;
            $msg[] = array( 'info', 'roaming_carrier unset');
        }
    }
    else {
        if ( $rm->field_ref_roaming_country['und'][0]['nid'] != 
            $partner->field_ref_roaming_country['und'][0]['nid']) {
            $rm->field_ref_roaming_country['und'][0]['nid'] = $partner->field_ref_roaming_country['und'][0]['nid'];
            $update = TRUE;
            $msg[] = array( 'info', 'roaming_country nid');
        }

        if ( substr( $partner->title, 3) == '**') { // default carrier
            if ( isset( $rm->field_ref_roaming_carrier['und'][0]['nid'])) {
                unset( $rm->field_ref_roaming_carrier['und']);
                $update = TRUE;
                $msg[] = array( 'info', 'roaming carrier unset');
            }
        }
        else {
            if ( $rm->field_ref_roaming_carrier['und'][0]['nid'] != $partner->nid) {
                $rm->field_ref_roaming_carrier['und'][0]['nid'] = $partner->nid;
                $update = TRUE;
                $msg[] = array( 'info', 'roaming carrier nid');
            }
        }
    }
    if ($rm->field_ref_type_of_call['und'][0]['tid'] != $terms_ptr['calltype'][$calltype]) {
        $msg[] = array( 'info', 'roaming calltype tid');
        $rm->field_ref_type_of_call['und'][0]['tid'] = $terms_ptr['calltype'][$calltype];
        $update = TRUE;
    }

    if ( $rm->field_ref_roaming_plan['und'][0]['nid'] != $plan_ptr->field_ref_roaming_plan['und'][0]['nid']) {
        $rm->field_ref_roaming_plan['und'][0]['nid'] = $plan_ptr->field_ref_roaming_plan['und'][0]['nid'];
        $update = TRUE;
        $msg[] = array( 'info', 'roaming plan nid');
    }

    if ($plmn == 'Outgoing SMS')  {
        if ( isset( $rm->field_ref_roaming_type['und'][0]['tid'])) {		// set a NULL for outgoing SMS
            unset( $rm->field_ref_roaming_type['und']);		// set a NULL for outgoing SMS
            $update = TRUE;
            $msg[] = array( 'info', 'roaming type unset');
        }
    }
    else  {
        if ( $rm->field_ref_roaming_type['und'][0]['tid'] != $terms_ptr['roaming_type'][$plmn]) {
            $rm->field_ref_roaming_type['und'][0]['tid'] = $terms_ptr['roaming_type'][$plmn];
            $update = TRUE;
            $msg[] = array( 'info', 'roaming type tid');
        }
    }

    if ( $roaming_intl_zone_nid > 0) {
        if ( $rm->field_roaming_zone['und'][0]['nid'] != $roaming_intl_zone_nid) {
            $rm->field_roaming_zone['und'][0]['nid'] = $roaming_intl_zone_nid;
            $update = TRUE;
            $msg[] = array( 'info', 'roaming zone nid');
        }
    }

    if ( $update ) {
        $msg[] = array( 'info', 'Save rating group '. $rm->title);
        node_save( $rm);
    }


	// find rate
    if ( $rate_nid === NULL) {
        $rate_nids = ocs_get_nids_by_cond( 'rate', array(
            array('property', 'title', $tariff),
            array('field_ref_tariffplan', 'nid', $plan_nid),
            array('field_ref_tree_tid', 'value', $tid)));

        if ( count( $rate_nids) == 0 || count($rate_nids) > 1) {
            $msg[] = array( 'error', t('Invalid rate <em>@t</em>  nid=@p, tid=@tid. @n rates are found', 
                array('@t' => $tariff, '@n' => count( $rate_nids),
                '@p' => $plan_nid, '@tid' => $tid)));
        }
        else {
            $rate_nid = $rate_nids[0];
        }
    }

    if ( $rate_nid !== NULL) {
        // add mapping
        // tariff mapping
        $result = ocs_get_nids_by_cond( 'basicrate_roaming', array(
            array('field_ref_tariffplan', 'nid', $plan_nid),
            array('field_rating_group', 'value', $rg)));

        if ( empty($result)) {
            $mapping = ocs_admin_get_new_node( 'basicrate_roaming');
            $mapping->field_ref_tariffplan['und'][0]['nid'] = $plan_nid;
            $mapping->field_ref_rate['und'][0]['nid'] = $rate_nid;
            $mapping->field_rating_group['und'][0]['value'] = $rg;

            node_save( $mapping);
        }
        else if ( count( $result) == 1) {
            $node = node_load( $result[0]);
            if ( $node->field_ref_rate['und'][0]['nid'] != $rate_nid) {
                $node->field_ref_rate['und'][0]['nid'] = $rate_nid;
                node_save( $node);
            }

            $old_list_ptr[$plan_nid]['Basic Rate'][$result[0]] = FALSE;
        }
        else {	// too many mapping
            $msg[] = array( 'error', 'Invalid tariff mapping ');
        }
    }

    $context['message'] = t( 'Save Rating Group <em>@r</em> to plan @p', 
        array( '@r' => $rg, '@p' => $plan_nid));

    foreach( $msg as $m) {
        drupal_set_message( $m[1], $m[0]);
        $context['message'] .= '<br>' . $m[1];
    }

	_batch_update_http_requests();
}

function batch_delete_unused_tariff( $plan_nid, $type, $nid, &$context)
{
	global $user;

	$old_list_ptr = &$_SESSION['import_roaming_tariff'][$user->uid]['old_list'];
	$msg = array();

	if ( isset( $old_list_ptr[$plan_nid][$type][$nid])) {
		if ( $old_list_ptr[$plan_nid][$type][$nid] === TRUE) {
			$node = node_load( $nid);
			$plan = node_load( $plan_nid);
			$msg[] = array( 'info', t('Remove unused @type : nid=@nid, "@title" from plan @p', 
				array( '@type' => $type, '@nid' => $nid, '@p' => $plan_nid . ' ' . $plan->title,
					'@title' => ($type == 'Rating Group') ?  $node->field_rating_group['und'][0]['value'] : $node->title)));
			node_delete( $nid);
		}
    }

    $context['message'] = t( 'Delete unused tariffs');

    foreach( $msg as $m) {
        drupal_set_message( $m[1], $m[0]);
        $context['message'] .= '<br>' . $m[1];
    }


	_batch_update_http_requests();
}

function batch_save_roaming_tariff( $tariff, $nid, $tid, $tid_range, $tid_uom, $rec, &$context)
{
	global $user;

	$old_list_ptr = &$_SESSION['import_roaming_tariff'][$user->uid]['old_list'];
	$partner_ptr = &$_SESSION['import_roaming_tariff'][$user->uid]['partner_list'];

    $msg = array();

	// add tariff
	$rate_nids = ocs_get_nids_by_cond( 'rate', array(
		array('property', 'title', $tariff),
		array('field_ref_tariffplan', 'nid', $nid),
		array('field_ref_tree_tid', 'value', $tid)));

    if ( count( $rate_nids) == 0) {
        $rate = ocs_admin_get_new_node( 'rate');
		$rate->title = $tariff;
		$msg[] = array( 'info', t( 'New roaming rate : @t', array( '@t' => $tariff)));

		$rate->field_range_units['und'][0]['tid'] = $tid_range;
		$rate->field_uom_units['und'][0]['tid'] = $tid_uom;
		if ( strstr( $tariff, 'SMS')) {

			$rate->field_ref_tariffplan['und'][0]['nid'] = $nid;
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

			$rate->field_ref_tariffplan['und'][0]['nid'] = $nid;
			$rate->field_ref_tree_tid['und'][0]['value'] = $tid;
		}

		node_save( $rate);
	}
	else {
        $rate = node_load( $rate_nids[0]);
		$old_list_ptr[$nid]['Rate'][$rate->nid] = FALSE;
		$msg[] = array( 'info', t( 'Existing roaming rate : @t', array( '@t' => $tariff)));

        // remove unused rates
        foreach( $rate_nids as $idx => $nid) {
            if ( $idx > 0) {
                $node = node_load( $nid);
                $msg[] = array( 'info', 'Remove rate : '. $node->title);
                node_delete( $nid);
            }
        }
	}


	$context['message'] = 'Save Rate';
    foreach( $msg as $m) {
        $context['message'] .= '<br>' . $m[1];
    }

	_batch_update_http_requests();
}



function _ocs_roaming_get_plmn_calltype( $rec)
{
	$plmn = $calltype = NULL;

	if ( $rec['IOCLL_DV_CD'] == '2') { // incoming call
		if ( $rec['FTR_CD'] == RoamingRSMS || $rec['FTR_CD'] == RoamingSMS) {
			$plmn = 'Incoming';
			$calltype = 'SMS_ROAMING_RECEIVE';
		}
		else if ( $rec['FTR_CD'] == RoamingIncomingVC) {
			$plmn = 'Incoming';
			$calltype = 'MOBILE_ROAMING_RECEIVE_CALL';
		}
        else {
			drupal_set_message( 'Warning : invalid FTR_CD ' . $rec['FTR_CD'], 'error');
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
		else if ( $rec['FTR_CD'] == RoamingSMS || $rec['FTR_CD'] == RoamingIntlSMS) {
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



// ajax handler
function ocs_ajax_select_roaming_product($form, &$form_state)
{
	return $form['tariff_plan'];
}
 

function batch_save_roaming_intl_zone( $reset, $terms, $records, &$context)
{
	global $user;

	//dpm( $records);
	$msg = array();
	$country_ptr = &$_SESSION['import_roaming_tariff'][$user->uid]['country_list'];
	$partner_ptr = &$_SESSION['import_roaming_tariff'][$user->uid]['partner_list'];

	foreach( $records as $record) {
		// find roaming zone by title
		$name = $record['PROD_CD'];
		$nids = ocs_get_nids_by_cond( 'roaming_zone', array(
					array( 'property', 'title', $name)
						));
		if ( count( $nids) > 1) {
			// error
			$msg[] = array( 'error', t('Multiple Roaming INTL Zone is found for @name', array( '@name' => $name)));
		}
		else {
            $country_list = array();
			if ( count( $nids) == 0) {
				$zone = ocs_admin_get_new_node( 'roaming_zone');
				$zone->title = $name;
				$msg[] = array( 'info', 'New Roaming INTL Zone : ' . $name);
			}
			else {
				$zone = node_load( $nids[0]);
				$msg[] = array( 'info', 'Existing Roaming INTL Zone : ' . $name);
			}

			// add country list
            $update = FALSE;
			foreach( $record['COUNTRY_CD'] as $country) {
				if ( isset( $country_ptr[$country])) {
                    $count = 0;
                    foreach( $zone->field_roaming_countries['und'] as $idx => $v) {
                        if ( $v['nid'] == $country_ptr[$country]) {
                            // existing country code
                            $count ++;
                            if ( $count > 1) {
                                unset( $zone->field_roaming_countries['und'][$idx]);
                                $update = TRUE;
                            }
                        }
                    }

                    if ( $count == 0) {
                        // not exist. add new one
                        $zone->field_roaming_countries['und'][] = array( 'nid' => $country_ptr[$country]);
                        $update = TRUE;
                    }
				}
				else {
					$msg[] = array( 'error', t('Invalid Roaming Country <em>@name</em>.',
						array( '@name' => $country)));
					continue;
				}
			}

			// find roaming partner nid
			// name format : <Partner Name>_Cus_??
			$list = explode( '_', $name);
			if ( isset( $partner_ptr[$list[0]])) {
				if ( $zone->field_roaming_carrier['und'][0]['nid'] != $partner_ptr[$list[0]]) {
                    $zone->field_roaming_carrier['und'][0]['nid'] = $partner_ptr[$list[0]];
                    $update = TRUE;
                }
			}
            else if ( $list[0] == 'IDD') {
                // default IDD
                if ( isset( $zone->field_roaming_carrier['und'][0]['nid'])) {
                    unset( $zone->field_roaming_carrier['und']);
                    $update = TRUE;
                }
            }
			else {
				$msg[] = array( 'error', t('Invalid Roaming Carrier <em>@name</em>',
					array( '@name' => $list[0])));
                continue;
			}

            if ( $update) {
                node_save( $zone);
                $msg[] = array( 'info', t('Save Roaming Carrier <em>@name</em>',
                    array( '@name' => $list[0])));
            }
		}
	}

	$context['message'] = 'Update Roaming Intl Zone';
	foreach( $msg as $m) {
		if ( $m[0] == 'error')
			drupal_set_message( $m[1], 'error');
		$context['message'] .= '<br>' . $m[1];
	}

	_batch_update_http_requests();
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

function batch_import_roaming_tariff_finished($success, $results, $operations)
{
	global $user;
	dpm( $_SESSION['import_roaming_tariff'][$user->uid], 'context');

	if ($success) {
		// Here we could do something meaningful with the results.
		// We just display the number of nodes we processed...
		drupal_set_message(t('@count results processed in @requests HTTP requests.',
			array('@count' => count($results),
			'@requests' => _batch_get_http_requests())));

		$idx = 1;
		foreach( $results as $r) {
			drupal_set_message( t( 'Request : @i', array( '@i' => $idx++)) . batch_deploy_result( $r));
		}
	}
	else {
		// An error occurred.
		// $operations contains the operations that remained unprocessed.
		$error_operation = reset($operations);
		drupal_set_message(t('An error occurred while processing @operation with arguments : @args',
			array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
	}

	if ( isset($_SESSION['redirect_after_batch'])) {
		drupal_goto($_SESSION['redirect_after_batch']);
	}
}