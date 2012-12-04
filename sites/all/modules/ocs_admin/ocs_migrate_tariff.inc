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

		foreach( $plan_list as $plan_name) {
			$plan_node = _get_first_node_by_title( 'tariffplan', $plan_name);

			// add rating group records
			foreach ($form['#rule'] as $rule) {

			//dpm( $rate_list, 'rate list:'.$rule['ruleName']);
			//_set_tariff($plan_node->nid, $rule['ruleName'], $rate_list, $tid, $values['check'] == '1');
			}
		}
	}
}

function _set_tariff( $plan_nid)
{
	$node = ocs_admin_get_new_node( 'basicrate_idd');

	$node->title = 'basicrate_idd';
	$node->field_ref_tariffplan['und'][0]['nid'] = $plan_nid;
	$node->field_basicrate_ratinggroup = '';
	$node->field_ref_timetablefactors = '';
	$node->field_ref_rate = '';

}

/*
   $type : idd or domestic
   */
function _load_all_time_table( $type)
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


