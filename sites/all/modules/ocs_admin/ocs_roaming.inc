<?php
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
		'#title' => 'Delete all existing data',
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
			'timeout'=>5));
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
			$query = new EntityFieldQuery();
			$tariff_plan_nids = $query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'simpleproductoffering')
				->fieldCondition('field_product_type', 'tid', $product_type['Main'])
				->fieldCondition('field_service_type_of_provider', 'tid', $service_domain['Mobile'])
				->execute();
			$form_state['#tariff_plan_nids'] = $tariff_plan_nids;
		}

		if ( count( $tariff_plan_nids) > 0) {
			$prd_list = array();
			foreach(  array_keys( $tariff_plan_nids['node']) as $nid) {
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

			$num = count( array_get_value( $form['#start_date_list'], FALSE));
			if ( $num != count( $form['#tariff_plan_list'])) {
				form_set_error( 'product', t('The product <em>@name</em> has not enough tariff plans. It must have at least @num plans.',
					array( '@name' => $form['product']['#options'][$values['product']], '@num' => $num)));
			}

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
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'tariffplan')
		->fieldCondition('field_ref_product', 'nid', $product_nid)
		->execute();

	$tariff_plan_list = array();

	if ( count( $result) > 0) {
		/* get terms */
		$tree_tid = ocs_get_terms_tid('TPL_DEFAULT_TREE_MOBILE');

		foreach( array_keys( $result['node']) as $nid) {
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

// return array of nodes
function _ocs_roaming_get_partner( $partner_code)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'roaming_carrier')
		->fieldCondition('field_partner_code', 'value', $partner_code)
		->execute();

	if ( count( $result) > 0) {
		$nids = array_keys( $result['node']);
		$node = node_load( $nids[0]);
		return $node;
	}

	return NULL;
}

function _ocs_roaming_get_country_nid( $country_code)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'roaming_country')
		->fieldCondition('field_country_code_3', 'value', $country_code)
		->execute();

	if ( count( $result) > 0) {
		$nids = array_keys( $result['node']);
		return $nids[0];
	}

	return NULL;
}


function _ocs_roaming_save_partner( $delete, $reset, $json)
{
	if ( $delete) {
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'roaming_carrier')
			->execute();

		if ( count( $result) > 0) {
			foreach( array_keys( $result['node']) as $nid) {
				dpm( $nid, 'delete node : ');
				node_delete( $nid);
			}
		}
	}

	$partner_list = json_decode( $json, TRUE);

	foreach( $partner_list as $key => $partner) {
		// get special number plan for this category
		$rm = _ocs_roaming_get_partner( $key);
		$new_node = FALSE;
		if ( empty( $rm)) {
			$rm = ocs_admin_get_new_node( 'roaming_carrier');

			dpm( 'New roaming partner ', $key);

			$new_node = TRUE;
			//$rm->field_prefix_multiple['und'][0]['value'] = $partner['intl_PREFIX'];
		}
		else {
			dpm( 'Existing roaming partner : ' . $rm->title, $key );

			//print_r( array_get_value( $splan->field_prefix_multiple, FALSE));
			/*
			if ( ! array_search( $partner['intl_PREFIX'], array_get_value( $rm->field_prefix_multiple, FALSE))) {
				$rm->field_prefix_multiple['und'][] = array( 'value' => implode( '', explode(' ',$partner['intl_PREFIX'])));
	//			$rm->field_exit_code['und'][] = array( 'value' => $rm['ruleName']);
				print 'Add additional prefix : ' . $partner['intl_PREFIX'] . $nl;
			}
			*/
		}

		if ( $new_node || $reset) {
			$rm->title = $partner['PARTNER_ID'];
			$rm->field_partner_code['und'][0]['value'] = $partner['PARTNER_ID'];
			$rm->field_description['und'][0]['value'] = $partner['DESCR'];
			$rm->field_ref_roaming_country['und'][0]['nid'] = _ocs_roaming_get_country_nid( substr($partner['TADIG'], 0, 3));

			node_save( $rm);
		}
	}

	return TRUE;
}




// update roaming country information
function _ocs_roaming_save_country( $delete, $reset, $json)
{
	if ( $delete) {
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'roaming_country')
			->execute();

		if ( count( $result) > 0) {
			foreach( array_keys( $result['node']) as $nid) {
				dpm( $nid, 'delete node : ');
				node_delete( $nid);
			}
		}
	}

	$country_list = json_decode( $json, TRUE);

	foreach( $country_list as $key => $country) {
		// get special number plan for this category
		$rm = _ocs_roaming_get_country( $key);
		$new_node = FALSE;
		if ( empty( $rm)) {
			$rm = ocs_admin_get_new_node( 'roaming_country');
			$rm->title = $country['COUNTRY_NAME'];

			dpm( 'New roaming country : ' . $rm->title);

			$rm->field_prefix_multiple['und'][0]['value'] = $country['INTL_PREFIX'];
			$rm->field_exit_code['und'][0]['value'] = '';
			$new_node = TRUE;
		}
		else {
			dpm( 'Existing roaming country : ' . $rm->title);
			//unset( $rm->field_prefix_multiple['und']);
			$rm->field_prefix_multiple['und'][0]['value'] = implode( '', explode(' ',$country['INTL_PREFIX']));

			/*
			if ( FALSE === array_search( $country['intl_PREFIX'], array_get_value( $rm->field_prefix_multiple, FALSE))) {
//				$rm->field_prefix_multiple['und'][] = array( 'value' => implode( '', explode(' ',$country['intl_PREFIX'])));
	//			$rm->field_exit_code['und'][] = array( 'value' => $rm['ruleName']);
				dpm( 'Add additional prefix : ' . $country['intl_PREFIX']);
			}
			*/
		}

		if ( $new_node || $reset) {
			$rm->field_country_code['und'][0]['value'] = $country['ISO_COUNTRY_CD'];
			$rm->field_country_code_3['und'][0]['value'] = $country['COUNTRY_CD'];
			$rm->field_time_zone['und'][0]['value'] = $country['GMT_OFFSET'];
			node_save( $rm);
		}
	}

	return TRUE;
}

// return array of nodes
function _ocs_roaming_get_country( $country_code)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'roaming_country')
		->fieldCondition('field_country_code', 'value', $country_code)
		->execute();

	if ( count( $result) > 0) {
		$nids = array_keys( $result['node']);
		$node = node_load( $nids[0]);
		return $node;
	}

	return NULL;
}

function _ocs_roaming_save_tariff( $delete, $reset, $json, $plan_list)
{
	dpm( $plan_list, 'plan_list');


	/* get terms */
	$roaming_type = ocs_get_terms_tid('roaming_type');
	dpm( $roaming_type, 'roaming type');

	/* get terms: calltype */
	$call_type = ocs_get_terms_tid('calltype');
	dpm( $call_type, 'call type');

	// get terms : unit_of_measure 
	$unit_measure = ocs_get_terms_tid('unit_of_measure');

	// get terms : unif_of_range
	$unit_range = ocs_get_terms_tid('unit_of_range');

	// get terms : usagetargetdomain
	$domain = ocs_get_terms_tid('usagetargetdomain');

	// get terms : tpl_tariffplan_voice
	$tree_tid = array();
	foreach( array( 'voice', 'sms') as $type) {
		$terms = ocs_get_terms('tpl_tariffplan_' . $type);
		foreach( $terms as $tid => $term) {
			if ( $term->name == 'Basic Rate' && $term->field_ref_usage_target_domain['und'][0]['tid'] == $domain['roaming']) {
				$tree_tid[$type] = $tid;
				break;
			}
		}
	}

	$tariff_plan_list = array();
	foreach( $plan_list as $k => $v) {
		$node = node_load($v);
		$tariff_plan_list[$k] = array( 'tariff' => $node, 
				'roaming' => node_load( $node->field_ref_roaming_plan['und'][0]['nid']));

		list( $type, $start_date) = explode( '|', $k);
		$node->field_valid_date_ymd['und'][0]['value'] = $start_date;
		dpm( $node, $node->title);
		node_save( $node);
	}

	$env = array( 
		'tariff_plan' => $tariff_plan_list,
		'roaming_type' => $roaming_type,
		'call_type' => $call_type,
		'unit_measure' => $unit_measure,
		'unit_range' => $unit_range,
		'domain' => $domain,
		'tree_tid' => $tree_tid,
		'reset' => $reset,
	);

	dpm( $env, 'env');

	$_SESSION['http_request_count'] = 0;

	$rate_list = json_decode( $json, TRUE);
	//dpm( $rate_list, 'rate list');

	$operations = array();

	if ( $delete) {
		foreach( $plan_list as $plan_nid) {
			// remove rate
			$query = new EntityFieldQuery();
			$result = $query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'rate')
				->fieldCondition('field_ref_tariffplan', 'nid', $plan_nid)
				->execute();

			if ( count( $result) > 0) {
				foreach( array_keys( $result['node']) as $nid) {
					$operations[] = array( '_batch_build_delete_node', array( $nid, t( 'Delete rate ')));
				}
			}

			// remove ratinggroup
			$t = node_load( $plan_nid);
			$query = new EntityFieldQuery();
			$result = $query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'roaming_ratinggroup')
				->fieldCondition('field_ref_roaming_plan', 'nid', $t->field_ref_roaming_plan['und'][0]['nid'])
				->execute();

			if ( count( $result) > 0) {
				foreach( array_keys( $result['node']) as $nid) {
					$operations[] = array( '_batch_build_delete_node', array( $nid, t( 'Delete rating group ')));
				}
			}

			$query = new EntityFieldQuery();
			$result = $query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'basicrate_roaming')
				->fieldCondition('field_ref_tariffplan', 'nid', $plan_nid)
				->execute();

			if ( count( $result) > 0) {
				foreach( array_keys( $result['node']) as $nid) {
					$operations[] = array( '_batch_build_reset_basicrate', array( $nid, t( 'Reset rate mapping ')));
				}
			}
		}
	}

	foreach( $plan_list as $plan => $plan_nid) {
		list( $tariff_type, $start_date) = explode( '|', $plan);

		foreach( $rate_list as $key => $records) {
			if ( strstr( $key, 'Customer') == NULL) {
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
					|| ($tariff_type == 'VOICE' && strstr( $calltype, 'SMS') === FALSE)) { 	// SMS call type
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
				$operations[] = array( '_batch_build_save_roaming_tariff_op', array( $env, $plan, $plan_nid, $key, $tariffs, 
							t( 'Start date : @tm, Partner : @p', array( '@tm' => $plan, '@p' => $key))));
				//dpm( $tariffs, $key);
			}
		}
	}

	drupal_set_message( t('Creating an array of @num tariffs', array( '@num' => count( $operations))));

	$batch = array(
		'operations' => $operations,
		'finished' => '_batch_build_save_roaming_tariff_finished',
		'title' => t('Import roaming tariffs'),
		'init_message' => t('Starting.'),
		'progress_message' => t('Processed @current out of @total.'),
		'error_message' => t('Batch procedure has encountered an error.'),
	);
	batch_set($batch);

	//dpm( $batch, 'batch op');

	return TRUE;
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
	$plan_ptr =& $env['tariff_plan'][$plan]['roaming'];

//	dpm( $tariff_ptr, $tariff_ptr->title);
//	dpm( $plan_ptr, $plan_ptr->title);

	$partner = _ocs_roaming_get_partner( $partner_code);
	if ( ! empty( $partner) || strstr( $partner_code, 'DEFAULT')) {
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
			$query = new EntityFieldQuery();
			$result = $query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'rate')
				->propertyCondition('title', $tariff)
				->fieldCondition('field_ref_tariffplan', 'nid', $tariff_ptr->nid)
				->execute();

			$new_node = FALSE;
			if ( count( $result) == 0) {
				$rate = ocs_admin_get_new_node( 'rate');
				$rate->title = $tariff;
				dpm( $partner_code . ') New roaming rate : ' . $tariff );

				$new_node = TRUE;
			}
			else {
				dpm( $partner_code . ') Existing roaming rate : ' . $tariff );
				$nids = array_keys( $result['node']);
				$rate = node_load( $nids[0]);
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
			$rm = _ocs_roaming_get_rate( $tariff);
			$new_node = FALSE;
			if ( empty( $rm)) {
				$rm = ocs_admin_get_new_node( 'roaming_ratinggroup');

				$rm->title = $tariff;
				$rm->field_rating_group['und'][0]['value'] = $tariff;
				dpm( 'New roaming group : ' . $tariff);

				$new_node = TURE;
			}
			else {
				dpm( $partner_code . ') Existing roaming group : ' . $tariff . ' ratinggroup:' . $rm->nid);
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
			$query = new EntityFieldQuery();
			$result = $query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'basicrate_roaming')
				->fieldCondition('field_ref_tariffplan', 'nid', $tariff_ptr->nid)
				->fieldCondition('field_rating_group', 'value', $tariff)
				->execute();

			if ( count( $result) == 1) {
				$nids = array_keys( $result['node']);
				$node = node_load( $nids[0]);
				$node->field_ref_rate['und'][0]['nid'] = $rate->nid;

				node_save( $node);
			}
			else if ( count($result) == 0) { 
				$mapping = ocs_admin_get_new_node( 'basicrate_roaming');
				$mapping->field_ref_tariffplan['und'][0]['nid'] = $tariff_ptr->nid;
				$mapping->field_ref_rate['und'][0]['nid'] = $rate->nid;
				$mapping->field_rating_group['und'][0]['value'] = $tariff;

				node_save( $mapping);
			}
			else {	// too many mapping
				drupal_set_message( 'Invalid tariff mapping ', 'error');
				continue;
			}
		}

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



// return array of nodes
function _ocs_roaming_get_rate( $rate_code)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'roaming_ratinggroup')
		->fieldCondition('field_rating_group', 'value', $rate_code)
		->execute();

	if ( count( $result) > 0) {
		$nids = array_keys( $result['node']);
		$node = node_load( $nids[0]);
		return $node;
	}

	return NULL;
}

// ajax handler
function ocs_ajax_select_roaming_product($form, &$form_state)
{
	    return $form['tariff_plan'];
}

