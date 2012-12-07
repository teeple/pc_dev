<?php

module_load_include( 'inc', 'ocs_admin', 'product_catalog_ajax');


function ocs_migrate_fce_tariff($form, &$form_state, $domestic_or_intl = 'domestic', $calltype = 'voice')
{
	$category = isset($form_state['values']['category']) ? $form_state['values']['category'] : 'A';

	$call_type = $domestic_or_intl . ':' . $calltype;

	list($records, $output) = _get_voice_tariff( $call_type, $category);
	dpm( $records, 'tariff decision');

	$form['#rule'] = $records;
	$form['#call_type'] = $call_type;
	
	$form['#attributes'] = array('class' => array('myform'));

    $form['info'] = array(
        '#type' => 'markup',
        '#markup' => 'Migrate tariff_decision table',
    );

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

function ocs_migrate_fce_tariff_submit($form, &$form_state)
{
	$values = $form_state['values'];
	if ($values['op'] == 'Save') {
		dpm($values, 'values');

        $ratinggroup_list = _load_all_ratinggroup( ($form['#call_type'] == 'intl:voice') ? 'idd_ratinggroup' : 'domestic_ratinggroup');
		dpm( $ratinggroup_list, 'rating group list');

		if ( $form['#call_type'] == 'intl:voice') {
			_update_idd_tariff( $form['#rule'], $values['target'], $ratinggroup_list, $timetable_list, $rate_list, $values['check'] == '1');
		}
		else if ( $form['#call_type'] == 'domestic:voice') {
			$plan_node = node_load( $values['target']);
			dpm( $plan_node, 'plan node');

			$rate_list = _load_all_rate( $plan_node->nid);
			dpm( $rate_list, 'rate list');

			// find time table
			$timetable = node_load( $plan_node->field_ref_timetable_domestic['und'][0]['nid']);

			_update_domestic_tariff( $form['#rule'], $values['target'], $ratinggroup_list, $timetable, $rate_list, $values['check'] == '1');
		}

	}
}


function _update_domestic_tariff( $rule_list, $plan_nid, $ratinggroup_list, $timetable, $rate_list, $check_only)
{
	// we have two time table factors: normal & discount
	$timetable_factor = array();
	for( $idx =0; $idx< 2; $idx++) {
		$tt = node_load( $timetable->field_ref_timetablefactors['und'][$idx]['nid']);
		$timetable_factor[$tt->title] = $tt->nid;
	}

	$mapping = array();
	foreach( $rule_list as $r) {
		$rating_group = $r['called_carrier'] . ':' . $r['rating_group'] . ':';
		$rating_group .= ( empty($r['user_category'])) ? $r['ruleName'] : '';
		// if time_id is null, mapping shall be 'normal'
		$mapping[$rating_group][($r['time_id'] == '2') ? 'discount' : 'normal'] = $r['ruleName'];
	}

	dpm( $mapping, 'mapping');

	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'basicrate_domestic')
		->fieldCondition('field_ref_tariffplan', 'nid', $plan_nid)
		->execute();

	if ( count( $result) > 0) {

        foreach( array_keys( $result['node']) as $nid) {
            $basicrate= node_load( $nid);

			//dpm( $basicrate, 'basic rate');

			// check if the rating group exist
			$rg = $basicrate->field_rating_group['und'][0]['value'];
			if ( ! isset( $ratinggroup_list[$rg])) {
				dpm( 'undefined rating group : '. $rg);
				continue;
			}

			$tt = node_load( $basicrate->field_ref_timetablefactors['und'][0]['nid']);

			if ( isset( $mapping[$rg][$tt->title])) {
				$mapping_decision = $mapping[$rg][$tt->title] ; 
			}
			else if ( isset( $mapping[$rg]['normal'])) {
				$mapping_decision = $mapping[$rg]['normal'];
			}
			else {
				drupal_set_message('unable to map rating group:'. $rg . ' time:' . $tt->title, 'error');
				continue;
			}

			dpm( t( 'mapping @rg -> @tt: @map, nid=@n', array( 
					'@rg' => $rg, '@tt' => $tt->title, '@map' => $mapping_decision, '@n' => $rate_list[$mapping_decision])));

			if ( ! isset( $rate_list[$mapping_decision])) {
				dpm( 'Rate not found for : '. $mapping_decision);
			}
			else if ( ! $check_only) {
				$basicrate->field_ref_rate['und'][0]['nid'] = $rate_list[$mapping_decision];
				node_save( $basicrate);
				//dpm( $basicrate, 'basic rate');
			}
        }
    }
	else {
		drupal_set_message( 'Basic rates are not found', 'error');
	}
}


function _update_idd_tariff( $rule_list, $plan_nid, $ratinggroup_list, $timetable_list, $rate_list, $check_only)
{
	// add rating group records
	foreach ($rule_list as $r) {
		$rating_group = $r['intl_carrier'] . '_' . $r['rating_group'];

		if ( ! isset( $ratinggroup_list[$rating_group])) {
			dpm( 'rating group not found: '. $rating_group);
			continue;
		}

		if ( ! isset( $timetable_list[$r['intl_carrier']])) {
			dpm( 'time table not found: '. $r['intl_carrier']);
			continue;
		}

		$tt = $timetable_list[$r['intl_carrier']];
		dpm( $tt, 'time table');

		$idx = $r['intl_time_id'] - 1;
		if ( ! isset( $tt->field_ref_timetablefactors['und'][$idx])) {
			dpm( 'time table factor not found for time_id:'. $r['intl_time_id']);
			continue;
		}

		if ( ! isset( $rate_list[$r['ruleName']])) {
			dpm( 'rate not found: '. $r['ruleName']);
			continue;
		}

		dpm( 'rating group:'.$rating_group);

		_set_tariff($plan_nid, 
			$rating_group, 
			$tt->field_ref_timetablefactors['und'][$idx]['nid'],
			$rate_list[$r['ruleName']],
			$check_only);
	}
}

function _set_tariff( $plan_nid, $ratinggroup, $tt_nid, $rate_nid, $check_only)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'basicrate_idd')
		->fieldCondition('field_ref_tariffplan', 'nid', $plan_nid)
		->fieldCondition('field_basicrate_ratinggroup', 'value', $ratinggroup)
		//->fieldCondition('field_ref_timetablefactors', 'nid', $tt_nid)
		->execute();

	if ( count( $result) > 0) {
        dpm( $result, 'result');
        dpm( $tt_nid, 'tt_nid');

        foreach( array_keys( $result['node']) as $nid) {
            dpm( node_load( $nid), 'node');
        }

        return;

        $nids = array_keys( $result['node']);
        $node = node_load( $nids[0]);
	
    /*
	$node->title = 'basicrate_idd';
	$node->field_ref_tariffplan['und'][0]['nid'] = $plan_nid;
	$node->field_basicrate_ratinggroup['und'][0]['nid'] = $ratinggroup_nid;
	$node->field_ref_timetablefactors['und'][0]['nid'] = $tt_nid;
    */
        $node->field_ref_rate['und'][0]['nid'] = $rate_nid;
        node_save( $node);
    }
    else {
        dpm('rating not found');
    }

}

/*
   $type : idd or domestic
   */
function _load_all_time_table()
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'timetable')
		->execute();

	$list = array();
	if ( count( $result) > 0) {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			$list[$node->title] = $node;
		}
	}

	return $list;
}

function _load_all_ratinggroup( $type)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->execute();

	$list = array();
	if ( count( $result) > 0) {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			$list[$node->field_rating_group['und'][0]['value']] = $nid;
		}
	}

	return $list;
}

function _load_all_rate( $plan_nid)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'rate')
		->fieldCondition('field_ref_tariffplan', 'nid', $plan_nid)
		->execute();

	$list = array();
	if ( count( $result) > 0) {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			$list[$node->title] = $nid;
		}
	}

	return $list;
}
