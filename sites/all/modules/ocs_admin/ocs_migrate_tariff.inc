<?php

function ocs_migrate_fce_tariff($form, &$form_state, $domestic_or_intl = 'domestic', $calltype = 'voice')
{
	$category = isset($form_state['values']['category']) ? $form_state['values']['category'] : 'All';

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
        '#title' => 'Category',
		'#options' => drupal_map_assoc(array( 'voice', 'intl voice', 'sms', 'intl sms')),
        '#default_value' => $category,
        '#ajax' => array(
            'callback' => 'ocs_ajax_select_area_code_category',
            'wrapper' => 'ocs_ajax_select_area_code_category_div',
        ),
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

	$numbering_plan_list['IDD'] = _load_all_numbering_plan( 'numberingplan_idd');
	$numbering_plan_list['Domestic'] = _load_all_numbering_plan( 'numberingplan_domestic');

	$form['data']['target'] = array(
        '#type' => 'select',
		'#title' => 'Target numbering plan',
		'#options' => $numbering_plan_list,
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

		$plan_list = array( 'voice_plan_a');

		$timetable_list = _load_all_time_table();
        dpm( $timetable_list, 'time table');

        $idd_ratinggroup = _load_all_idd_ratinggroup();


		foreach( $plan_list as $plan_name) {
			$plan_node = _get_first_node_by_title( 'tariffplan', $plan_name);

            $rate_list = _load_all_rate( $plan_node->nid);
            dpm( $rate_list, 'rate list');

			// add rating group records
			foreach ($form['#rule'] as $r) {
                $rating_group = $r['intl_carrier'] . '_' . $r['rating_group'];

                if ( ! isset( $idd_ratinggroup[$rating_group])) {
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

			    _set_tariff($plan_node->nid, 
                    $rating_group, 
                    $tt->field_ref_timetablefactors['und'][$idx]['nid'],
                    $rate_list[$r['ruleName']],
                    $values['check'] == '1');
			}
		}
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

function _load_all_idd_ratinggroup()
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'idd_ratinggroup')
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
