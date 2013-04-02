<?php

global $unit_range;
global $unit_measure;
global $tree_tid;

function _load_all_price()
{
	$rate = &drupal_static(__FUNCTION__, NULL);
	if (empty($rate)) {
		db_set_active('fce');

		$query = db_select('price_data', 'c');
		$result = $query->fields('c')->execute();

		$rate = array();
		while ($record = $result->fetchAssoc()) {
			$rate[$record['price_name']] = $record['price'];
		}

		db_set_active('default');
	}

	return $rate;
}

function ocs_migrate_fce_rate($form, &$form_state, $domestic_or_intl = 'domestic', $calltype = 'voice')
{
	$category = isset($form_state['values']['category']) ? $form_state['values']['category'] : 'A';

	$call_type = $domestic_or_intl . ':' . $calltype;
	list($records, $output) = _get_voice_tariff( $call_type, $category);

	dpm( $records, 'tariff decision');

	$form['#rule'] = $records;
	$form['#call_type'] = $call_type;
	
	$rate = ($call_type == 'domestic:sms') ? _load_all_price() : ocs_load_all_rate();
	dpm($rate, 'rate');
	$form['#rate'] = $rate;
	$form['#attributes'] = array('class' => array('myform'));

    $form['info'] = array(
        '#type' => 'markup',
        '#markup' => 'Migrate Rate table',
    );

	if ( $domestic_or_intl == 'domestic') {
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

function _get_terms()
{
	global $unit_measure;
	global $unit_range;
	global $tree_tid;

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

	$tree_tid = array();
	foreach( array( 'voice', 'sms') as $type) {
		$vid = taxonomy_vocabulary_machine_name_load('tpl_tariffplan_' . $type);
		$tree = taxonomy_get_tree( $vid->vid, 0, 1);
		foreach( $tree as $node) {
			$children = taxonomy_get_tree( $vid->vid, $node->tid, 1);
			foreach( $children as $child) {
				//dpm( $child, $node->name);
				if ( $child->name == 'Basic Rate') {
					$tree_tid[$type][$node->name] = $child->tid;
				}
			}
		}
	}
	//dpm( $tree_tid, 'tree tid');
}

function ocs_migrate_fce_rate_submit($form, &$form_state)
{
	// tid list
	global $tree_tid;

	_get_terms();

	$values = $form_state['values'];
	if ($values['op'] == 'Save') {
		dpm($values, 'values');

		// get tree tid 
        // $a:intl or domestic, $b:voice or sms
        list( $a, $b) = explode( ':', $form['#call_type']);
		/*
		$nids = array_keys( taxonomy_get_term_by_name( 
            ($a == 'intl') ? 'International' : 'Domestic',
            ($b == 'voice') ? 'tpl_tariffplan_voice' : 'tpl_tariffplan_sms'));

		//dpm( $nids, 'taxonomy_get_term_by_name');
		*/

		$tid = $tree_tid[$b][($a == 'intl') ? 'International' : 'Domestic'];
		dpm( $tree_tid, 'tree_tid');
		dpm( $tid, 'tree_tid');

		$processed_rate_list = array();

        if ( $form['#call_type'] == 'domestic:sms') {
            $price_list = $form['#rate'];
            foreach ($form['#rule'] as $r) {
                $name = $r['ruleName'];

                if ( ! isset( $price_list[$name])) {
                    drual_set_message( 'price not found for '. $name);
                    continue;
                }

                $price = $price_list[$name];

                //dpm( $rate_list, 'rate list:'.$rule['ruleName']);
                if ( !isset( $processed_rate_list[$name])) {
                    _set_price($values['target'], $name, $price, $tid, $values['check'] == '1');
                    $processed_rate_list[$name] = TRUE;
                }
                else {
                    dpm( t('Rate @n already updated', array( '@n' => $name)));
                }
            }
        }
        else {
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
}

function _set_price($plan_nid, $name, $price, $tid, $check_only = TRUE)
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
		$old_rate_list = array_get_value( $new_rate->field_charge_collection, FALSE);

        $charge = entity_load_single( 'field_collection_item', $old_rate_list[0]);
        $charge->field_uom_amount['und'][0]['value'] = '1';
        $charge->field_price_amount_float['und'][0]['value'] = $price;
        $charge->save();

		node_save( $new_rate);
	}
	else {
		$new_rate = ocs_admin_get_new_node('rate');

		// add new rate
        if ( ! $check_only) {
            $charge = entity_create('field_collection_item', array('field_name' => 'field_charge_collection'));
            $charge->setHostEntity('node', $new_rate);

            $charge->field_uom_amount['und'][0]['value'] = '1';
            $charge->field_price_amount_float['und'][0]['value'] = $price;
            $charge->save();

            dpm( t( 'add new price @n amount=1 price=@p', array( '@n' => $name, '@p' => $price)));
		}
	}

	global $unit_measure;

	$new_rate->title = $name;
    // count
	$new_rate->field_uom_units['und'][0]['tid'] = $unit_measure['Seconds'];     
	$new_rate->field_ref_tariffplan['und'][0]['nid'] = $plan_nid;
	$new_rate->field_ref_tree_tid['und'][0]['value'] = $tid;
	$new_rate->field_price['und'][0]['value'] = $price;

	if ( ! $check_only) {
		node_save($new_rate);
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
            $range_end = ( $idx + 1 < count( $rate_list)) ?  ($start + $rate['e2']) : '*';

			if ( ! $check_only) {
				$charge = entity_create('field_collection_item', array('field_name' => 'field_charge_collection'));
				$charge->setHostEntity('node', $new_rate);

				_set_single_rate( $charge, $start, $range_end, $rate['e1'], $rate['e2']);
            }

            dpm( t( 'add new rate @n start=@s end=@e amount=@a price=@p', array( '@n' => $name, '@s' => $start, 
                '@e' => $range_end, '@a' => $rate['e2'], '@p' => $rate['e1'])));
            $start += $rate['e2'];
            $idx ++;
		}
	}

	global $unit_range, $unit_measure;

	$new_rate->title = $name;
	// seconds
	$new_rate->field_range_units['und'][0]['tid'] = $unit_range['Seconds'];
	// seconds
	$new_rate->field_uom_units['und'][0]['tid'] = $unit_measure['Seconds'];
	$new_rate->field_ref_tariffplan['und'][0]['nid'] = $plan_nid;
	$new_rate->field_ref_tree_tid['und'][0]['value'] = $tid;

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
