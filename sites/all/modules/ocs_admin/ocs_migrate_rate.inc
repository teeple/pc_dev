<?php

function ocs_migrate_fce_rate($form, &$form_state, $domestic_or_intl = 'domestic', $calltype = 'voice')
{
	$category = isset($form_state['values']['category']) ? $form_state['values']['category'] : 'A';

	$call_type = $domestic_or_intl . ':' . $calltype;
	list($records, $output) = _get_voice_tariff( $call_type, $category);

	dpm( $records, 'tariff decision');

	$form['#rule'] = $records;
	$form['#call_type'] = $call_type;
	
	$rate = ocs_load_all_rate();
	dpm($rate, 'rate');
	$form['#rate'] = $rate;
	$form['#attributes'] = array('class' => array('myform'));

    $form['info'] = array(
        '#type' => 'markup',
        '#markup' => 'Migrate Rate table',
    );

	if ( $call_type == 'domestic:voice') {
		$form['category'] = array(
			'#type' => 'select',
			'#title' => 'User Category to migrate',
			'#options' => drupal_map_assoc(array(
				'All',
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

	// $form['carrier'] = array(
	// '#type' => 'fieldset',
	// '#title' => 'Area',
	// '#prefix' => '<div id="ocs_ajax_user_category_div">',
	// '#suffix' => '</div>',
	// );

	$form['data'] = array(
		'#type' => 'fieldset',
		'#title' => 'Migration data',
		'#collapsible' => TRUE,
		'#prefix' => '<div id="ocs_ajax_user_category_div">',
		'#suffix' => '</div>',
	);


	$form['data']['target'] = array(
        '#type' => 'select',
		'#title' => 'Target plan name',
		'#options' => _load_all_tariffplan()
    );

	$form['data']['list'] = array(
		'#type' => 'markup',
		'#title' => 'Rule data',
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

function _get_rate_list($rate, $name)
{
	$list = array();
	while (!empty($name)) {
		$r = $rate[$name];
		$list[] = $r;

		$name = $r['nextTariffName'];
	}
	return $list;
}

function ocs_migrate_fce_rate_submit($form, &$form_state)
{
	$values = $form_state['values'];
	if ($values['op'] == 'Save') {
		dpm($values, 'values');

		// get tree tid 
		$term_name = ( substr( $form['#call_type'], 0, 4) == 'intl') ? 'International' : 'Domestic' ;
		$nids = array_keys( taxonomy_get_term_by_name( $term_name, 'tpl_tariffplan_mobile_voice'));

		// tid list
		$tid = array( 'tree_tid' => $nids[0]);

		$processed_rate_list = array();

		// add rating group records
		foreach ($form['#rule'] as $r) {
			//dpm( $rule, 'rule');
			$name = $r['ruleName'];
			$rate_list = _get_rate_list($form['#rate'], $name);

			//dpm( $rate_list, 'rate list:'.$rule['ruleName']);
			if ( !isset( $processed_rate_list[$name])) {
				_set_rate($values['target'], $name, $rate_list, $tid, $values['check'] == '1');
				$processed_rate_list[$name] = TRUE;
			}
			else {
				dpm( t('Rate @n already updated', array( '@n' => $name)));
			}
		}
	}
}

function _set_rate($plan_nid, $name, $rate_list, $tid, $check_only = TRUE)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'rate')
		->propertyCondition('title', $name)
		->fieldCondition( 'field_ref_tariffplan', 'nid', $plan_nid)
		->execute();

	if (count($result) > 1) {
		drupal_set_message( 'Duplicated rate in the same tariff plan:'. $name);
		return;
	}

	if (count($result) == 1) {
		$rate_nids = array_keys($result['node']);
		$new_rate = node_load($rate_nids[0]);

		// get the current rate
		$old_rate_list = array_get_value( $new_rate->field_charge_collection, FALSE);
		//dpm( $old_rate_list, 'old rate list');

		$idx = 0;
		$start = 0;

		// add new rate
		foreach ($rate_list as $rate) {
			if ( $idx < count( $old_rate_list)) {
				$charge = entity_load_single( 'field_collection_item', $old_rate_list[$idx]);
				//dpm( $charge, 'load rate collection:'. $old_rate_list[$idx]);
			}
			else {
				$charge = entity_create('field_collection_item', array('field_name' => 'field_charge_collection'));
				$charge->setHostEntity('node', $new_rate);
			}

			$range_end = ( $idx + 1 < count( $rate_list)) ?  ($start + $rate['e2']) : '*';
			_set_single_rate( $charge, $start, $range_end, $rate['e1'], $rate['e2']);

			dpm( t( 'update rate @n start=@s end=@e amount=@a price=@p', array( '@n' => $name, '@s' => $start, '@e' => $range_end,
				'@a' => $rate['e2'], '@p' => $rate['e1'])));

			//dpm( $charge, 'updated');

			$start += $rate['e2'];
			$idx ++;
		}

		// delete not used rate
		while ( $idx < count( $old_rate_list)) {
			dpm( 'remove unused rate');
			unset( $new_rate->field_charge_collection['und'][$idx]);
			entity_delete( 'field_collection_item', $old_rate_list[$idx++]);
		}

		node_save( $new_rate);
	}
	else {
		$new_rate = ocs_admin_get_new_node('rate');

		// add new rate
		$start = 0;
		$idx = 0;
		foreach ($rate_list as $rate) {
			if ( ! $check_only) {
				$charge = entity_create('field_collection_item', array('field_name' => 'field_charge_collection'));
				$charge->setHostEntity('node', $new_rate);

				$range_end = ( $idx + 1 < count( $rate_list)) ?  ($start + $rate['e2']) : '*';
				_set_single_rate( $charge, $start, $range_end, $rate['e1'], $rate['e2']);

				dpm( t( 'add new rate @n start=@s end=@e amount=@a price=@p', array( '@n' => $name, '@s' => $start, 
								'@e' => $range_end, '@a' => $rate['e2'], '@p' => $rate['e1'])));
				$start += $rate['e2'];
				$idx ++;
			}
		}
	}

	$new_rate->title = $name;
	// seconds
	$new_rate->field_range_units['und'][0]['tid'] = 390;
	// MNT
	$new_rate->field_price_units['und'][0]['tid'] = 450;
	// seconds
	$new_rate->field_uom_units['und'][0]['tid'] = 451;
	$new_rate->field_ref_tariffplan['und'][0]['nid'] = $plan_nid;
	$new_rate->field_ref_tree_tid['und'][0]['value'] = $tid['tree_tid'];

	if ( ! $check_only) {
		node_save($new_rate);
	}
}

function _set_single_rate( &$charge, $start, $end, $e1, $e2)
{
	$charge->field_range_start['und'][0]['value'] = $start;
	if ( $end == '*') {
		unset( $charge->field_range_end['und']);
	}
	else {
		$charge->field_range_end['und'][0]['value'] = $end;
	}

	$charge->field_uom_amount['und'][0]['value'] = $e2;
	$charge->field_price_amount_float['und'][0]['value'] = $e1;
	$charge->save();
}

function _load_all_tariffplan()
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'tariffplan')
		->propertyOrderBy('title')
		->execute();

	$list = array();

	if (count($result) > 0) {
		foreach( array_keys($result['node']) as $nid ) {
			$node = node_load( $nid);
			$list[$nid] = $node->title;
		}
	}

	return $list;
}
