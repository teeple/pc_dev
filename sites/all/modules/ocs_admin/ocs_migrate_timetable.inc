<?php

function ocs_migrate_fce_timetable($form, &$form_state)
{
	$type = ( isset( $form_state['values']['type'])) ? $form_state['values']['type'] : 'domestic:voice';

	list( $records, $output) = _get_time_table( $type);

	$form['#rule'] = $records;
	$form['#attributes'] = array('class' => array('myform'));

	$form['type'] = array(
		'#type' => 'select',
		'#title' => 'Type',
		'#options' => array( 'domestic:voice' => 'Domestic Voice', 'intl:voice' => 'International Voice'),
		'#default_value' => $type,
		'#ajax' => array(
			'callback' => 'ocs_ajax_select_user_category',
			'wrapper' => 'ocs_ajax_user_category_div',
		),
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

	$form['data'] = array(
		'#type' => 'fieldset',
		'#title' => 'Timetable data',
		'#collapsible' => TRUE,
		'#prefix' => '<div id="ocs_ajax_user_category_div">',
		'#suffix' => '</div>',
	);

	$form['data']['list'] = array(
		'#type' => 'markup',
		'#markup' => '<table>' . $output . '</table>'
	);

	return $form;
}

function ocs_migrate_fce_timetable_submit($form, &$form_state)
{
	$values = $form_state['values'];
	if ($values['op'] == 'Save') {
		dpm($values, 'values');

		if ( $values['type'] == 'domestic:voice') {
		}
		else if ( $values['type'] == 'intl:voice') {
			//not used
			//_update_intl_voice_timetable( $form['#rule']);
		}
	}
}


function _update_intl_voice_timetable( $rule_list, $check_only)
{
	$table_list = array();
	foreach( $rule_list as $r) {
		if ( isset( $table_list[$r['intl_carrier']])) {
			$node = $table_list[$r['intl_carrier']];
		}
		else {
			// find timetable
			$query = new EntityFieldQuery();
			$result = $query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'timetable')
				->propertyCondition('title', $r['intl_carrier'])
				->execute();

			if ( count( $result) == 1) {
				$nids = array_keys( $result['node']);
				$node = node_load( $nids[0]);
				$table_list[$r['intl_carrier']] = $node;

				dpm( 'exiting time table : '. $r['intl_carrier']);
			}
			else if ( count( $result) == 0) {
				$node = ocs_admin_get_new_node( 'timetable');
				$node->title = $r['intl_carrier'];
				if ( ! $check_only) node_save( $node);

				$table_list[$r['intl_carrier']] = $node;

				dpm( 'new time table : ' . $r['intl_carrier']);
			}
			else {
				dpm( 'Too many time tables are found : '. $r['intl_carrier']);
				return;
			}
		}
	}
}

