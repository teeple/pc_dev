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

	$response = drupal_http_request( $url, array(
		'method' => $method,
		'headers' => array('Content-Type' => 'application/json', 'Accept' => 'application/json'),
		'timeout'=>5));
	dpm( $url, 'url');
	dpm( $response, 'response');

	if ( $type == 'tariff') {
		$terms = ocs_get_terms('PrdType');
		$product_type = array();
		foreach( $terms as $tid => $term) {
			$product_type[$term->name] = $tid;
		}

		$terms = ocs_get_terms('SvcDomain');
		$service_domain = array();
		foreach( $terms as $tid => $term) {
			$service_domain[$term->name] = $tid;
		}

		// find tariff plans
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'simpleproductoffering')
			->fieldCondition('field_product_type', 'tid', $product_type['Main'])
			->fieldCondition('field_service_type_of_provider', 'tid', $service_domain['Mobile'])
			->execute();

		if ( count( $result) > 0) {
			$prd_list = array();
			foreach(  array_keys( $result['node']) as $nid) {
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
		$tariff_list = json_decode( $response->data, TRUE);
		foreach( $tariff_list as $partner => $tariffs) {
			foreach( $tariffs as $tariff) {
				list( $plmn, $calltype) = _ocs_roaming_get_plmn_calltype( $tariff);
				$start_date_list[ $tariff['VALD_STRT_DT']][] = t('@a:@b:@c', array( '@a' => $partner, '@b' => $plmn, '@c' => $calltype));
			}
		}
		dpm( $start_date_list, 'start date list');

		dpm( $tariff_plan_list, 'tariff plan list');

		$form['tariff_plan'] = array(
			'#type' => 'fieldset',
			'#title' => 'Roaming Tariff Plans ',
			'#prefix' => '<div id="ocs_ajax_select_roaming_product_div">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('myform')),
		);

		foreach( array_keys( $start_date_list) as $date) {
			$form['tariff_plan']['VOICE:'.$date] = array(
				'#type' => 'select',
				'#title' => 'VOICE '.$date,
				'#options' => $tariff_plan_list,
//				'#description' => 'Tariff plan shall be applied from ' . $date,
			);
			$form['tariff_plan']['SMS:'.$date] = array(
				'#type' => 'select',
				'#title' => 'SMS '.$date,
				'#options' => $tariff_plan_list,
			);
			$form['tariff_plan']['markup:'.$date] = array(
				'#markup' => '<br>',
			);
		}

	}

	/*
	global $json_country;
	global $json_partner;
	global $json_rate;

	$json = array( 'country' => $json_country, 'partner' => $json_partner, 'tariff' => $json_rate);
	*/

    $form['actions'] = array('#type' => 'actions');

	if ( $response->code == 200) {
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
	else {
		drupal_set_message( 'API Return Result : ' . $response->error, 'error');
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


			if ( ! isset( $form_state['#voice_tariffplan'])) 
				form_set_error( 'product', 'Voice tariff plan is not defined.');

			if ( ! isset( $form_state['#sms_tariffplan'])) 
				form_set_error( 'product', 'SMS tariff plan is not defined.');
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
		$terms = ocs_get_terms('TPL_DEFAULT_TREE_MOBILE');
		$tree_tid = array();
		foreach( $terms as $tid => $term) {
			$tree_tid[$term->name] = $tid;
		}

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
        	$result = _ocs_roaming_save_tariff( $values['delete'], $values['reset'], $values['response'], 
					$form_state['#voice_tariffplan'], $form_state['#sms_tariffplan']);
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

function _ocs_roaming_save_tariff( $delete, $reset, $json, $tariff, $sms_tariff)
{
	if ( $delete) {
		foreach( array( $tariff, $sms_tariff) as $t) {
			// remove rate
			$query = new EntityFieldQuery();
			$result = $query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'rate')
				->fieldCondition('field_ref_tariffplan', 'nid', $t->nid)
				->execute();

			if ( count( $result) > 0) {
				foreach( array_keys( $result['node']) as $nid) {
					dpm( 'delete rate: '. $nid);
					node_delete( $nid);
				}
			}

			// remove ratinggroup
			$query = new EntityFieldQuery();
			$result = $query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'roaming_ratinggroup')
				->fieldCondition('field_ref_roaming_plan', 'nid', $t->field_ref_roaming_plna['und'][0]['nid'])
				->execute();

			if ( count( $result) > 0) {
				foreach( array_keys( $result['node']) as $nid) {
					dpm( 'Delete rating group : '. $nid);
					node_delete( $nid);
				}
			}

			$query = new EntityFieldQuery();
			$result = $query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'basicrate_roaming')
				->fieldCondition('field_ref_tariffplan', 'nid', $t->nid)
				->execute();

			if ( count( $result) > 0) {
				foreach( array_keys( $result['node']) as $nid) {
					$node = node_load( $nid);
					unset( $node->field_ref_rate['und']);
					unset( $node->field_rating_group['und']);
					dpm( 'Reset rating mapping : '. $nid);
					node_save( $node);
				}
			}
		}
	}

	/* get terms */
	$terms = ocs_get_terms('roaming_type');
	$roaming_type = array();
	foreach( $terms as $tid => $term) {
		$roaming_type[$term->name] = $tid;
	}

	/* get terms: calltype */
	$terms = ocs_get_terms('calltype');
	$call_type = array();
	foreach( $terms as $tid => $term) {
		$call_type[$term->name] = $tid;
	}

	// get terms : unit_of_measure 
	$terms = ocs_get_terms('unit_of_measure');
	$unit_measure = array();
	foreach( $terms as $tid => $term) {
		$unit_measure[$term->name] = $tid;
	}

	// get terms : unif_of_range
	$terms = ocs_get_terms('unit_of_range');
	$unit_range = array();
	foreach( $terms as $tid => $term) {
		$unit_range[$term->name] = $tid;
	}

	// get terms : usagetargetdomain
	$terms = ocs_get_terms('usagetargetdomain');
	$domain = array();
	foreach( $terms as $tid => $term) {
		$domain[$term->name] = $tid;
	}

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

	$env = array( 
		'tariff' => $tariff,
		'sms_tariff' => $sms_tariff,
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

	drupal_set_message( t('Creating an array of @num tariffs', array( '@num' => count( $rate_list))));

	$operations = array();

	foreach( $rate_list as $key => $records) {
		if ( strstr( $key, 'Customer') == NULL) {
			continue;
		}

		$operations[] = array( '_batch_build_save_roaming_tariff_op', array( $env, $key, $records, 'Import tariff of ' . $key));
	}


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
			$calltype = 'ROAMING_SMS_RECEIVE';
		}
		else {
			$plmn = 'Incoming';
			$calltype = 'ROAMING_RECEIVE_CALL';
		}
	}
	else {
		if ( $rec['FTR_CD'] == RoamingHCC ) {
			$plmn = 'HPLMN';
			$calltype = 'ROAMING_HOME_CALL';
		}
		else if ( $rec['FTR_CD'] == RoamingIVC ) {
			$plmn = 'Other PLMN';
			$calltype = 'ROAMING_OTHER_COUNTRY';
		}
		else if ( $rec['FTR_CD'] == RoamingLVC ) {
			$plmn = 'VPLMN';
			$calltype = 'ROAMING_CALL_TO_NATIONAL';
		}
		else if ( $rec['FTR_CD'] == RoamingRSMS ) {
			$plmn = 'Incoming';
			$calltype = 'ROAMING_SMS_RECEIVE';
		}
		else if ( $rec['FTR_CD'] == RoamingSMS ) {
			$plmn = 'Outgoing SMS';
			$calltype = 'ROAMING_SMS_SENT';
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

function _batch_build_save_roaming_tariff_op( $env, $key, $records, $operation_details, &$context)
{
	$stop = FALSE;

	// customer tariff has key with format '<Partner Name>_Customer'
	//dpm( $records, 'Import tariff');
	$nid = $env['tariff']->field_ref_roaming_plan['und'][0]['nid'];
	$plan = node_load( $nid);

	$nid = $env['sms_tariff']->field_ref_roaming_plan['und'][0]['nid'];
	$sms_plan = node_load( $nid);

	$list = explode( '_', $key);
	$partner_code = $list[0];

	$partner = _ocs_roaming_get_partner( $partner_code);
	if ( ! empty( $partner) || strstr( $partner_code, 'DEFAULT')) {
		foreach( $records as $rec) {
			if ( $rec['RATE_APLY_DV_CD'] != RATE_APLY_DV_CD_STEP)  {
				drupal_set_message( 'Invalid rate type : ' . $rec['RATE_APLY_DV_CD'], 'error');
				$stop = TRUE;
				continue;
			}

			list( $plmn, $calltype) = _ocs_roaming_get_plmn_calltype( $rec);
			if ( empty( $plmn)) continue;

			//dpm( $plmn);

			$tariff = $rec['RATE_APLY_UNIT'] . '_' . $rec['RATE'];
			if ( !empty( $rec['INIT_RATE_APLY_UNIT']))
				$tariff .= $rec['INIT_RATE_APLY_UNIT'] . '_' . $rec['INIT_RATE'];

			if ( strstr( $calltype, 'SMS')) {
				$tariff_ptr =& $env['sms_tariff'];
				$plan_ptr =& $sms_plan;
				$tariff = 'ROAMING_SMS_' . $tariff;

				if ( $rec['RATE_APLY_UNIT_CD'] != RATE_UNIT_COUNT) {
					drupal_set_message( 'Error : Invalid rate unit for SMS:' . $rec['RATE_APLY_UNIT_CD'], 'error');
					$stop = TRUE;
					continue;
				}
			}
			else {
				$tariff_ptr =& $env['tariff'];
				$plan_ptr =& $plan;
				$tariff = 'ROAMING_VOICE_' . $tariff;

				if ( $rec['RATE_APLY_UNIT_CD'] != RATE_UNIT_SECOND) {
					drupal_set_message( 'Error : Invalid rate unit for Voice:' . $rec['RATE_APLY_UNIT_CD'], 'error');
					dpm( $rec, 'rec');
					dpm( $plmn, 'plmn');
					$stop = TRUE;
					continue;
				}
			}

			// add tariff
			$nids = ocs_get_nodes_by_title( 'rate', $tariff);
			$new_node = FALSE;
			if ( empty( $nids)) {
				$rate = ocs_admin_get_new_node( 'rate');
				$rate->title = $tariff;
				dpm( 'New roaming rate : ' . $tariff );

				$new_node = TRUE;
			}
			else {
				dpm( 'Existing roaming rate : ' . $tariff );
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
				dpm( 'Existing roaming group : ' . $tariff . ' ratinggroup:' . $rm->nid);
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

		node_save( $plan);
		node_save( $sms_plan);
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

