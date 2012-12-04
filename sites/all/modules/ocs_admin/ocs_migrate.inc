<?php

global $carrier_info;


function ocs_migrate_fce_carrier($form, &$form_state)
{
	db_set_active('fce');

	$query = db_select('carrier', 'c');
	$result = $query->fields('c', array(
		'ruleName',
		'prefix'
	))->execute();

	$output = '<thead><tr><td>Carrier</td><td>Prefix</td></tr></thead>';
	$output .= '<tbody>';
	$records = array();
	while ($record = $result->fetchAssoc()) {
		$records[] = array(
			'carrier' => $record['ruleName'],
			'prefix' => $record['prefix']
		);
		$output .= '<tr><td>' . $record['ruleName'] . '</td><td>' . $record['prefix'] . '</td></tr>';
	}
	$output .= '</tbody>';

	$form['#carrier'] = $records;

	db_set_active('default');

	$form['carrier'] = array(
		'#type' => 'fieldset',
		'#title' => 'Carrier',
		'#collapsible' => TRUE,
	);

	// $form['carrier']['remove'] = array(
	// '#type' => 'radios',
	// '#title' => 'remove all existing data',
	// '#options' => array( 'No', 'Yes'),
	// '#default_value' => '1'
	// );
	//
	$form['carrier']['data'] = array(
		'#type' => 'markup',
		'#markup' => '<table>' . $output . '</table>'
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

function ocs_migrate_fce_carrier_submit($form, &$form_state)
{
	$values = $form_state['values'];
	if ($values['op'] == 'Save') {
		dpm($values, 'values');

		// if ( $values['remove'] == '1') {
		// dpm( 'remove all mobile carrier instances.');
		//
		// // remove all existing values
		// $items = entity_load( 'node', FALSE, array( 'type' => 'carrier_mobile'));
		// foreach( array_keys( $items) as $nid) {
		// node_delete( $nid);
		// }
		// }

		// add entities
		foreach ($form['#carrier'] as $carrier) {
			$node = ocs_admin_get_new_node('carrier_mobile');
			$node->title = $carrier['carrier'];
			$prefix = entity_create('field_collection_item', array('field_name' => 'field_prefix_collection'));
			$prefix->setHostEntity('node', $node);

			$prefix->field_prefix = array('und' => array('0' => array('value' => $carrier['prefix'], )));

			$prefix->save();
			node_save($node);
		}
	}
}

function _get_area_code( $category)
{
	db_set_active('fce');

    $info = array(
        'voice' => array( 'table' => 'area', 
            'field' => array(
                'carrier',
                'ruleName',
                'second_prefix',
                'region_code',
                'rating_group'
                ),
            'order' => 'carrier'),
        'intl voice' => array( 'table' => 'intl_area',
            'field' => array( 'ruleName', 'intl_carrier', 'prefix', 'country_code', 'NPA_prefix',
                'country_prefix', 'rating_group'),
            'order' => 'intl_carrier'),
    );

	$query = db_select( $info[$category]['table'], 'a');
	$result = $query->fields('a', $info[$category]['field'])
        ->orderBy( $info[$category]['order'])
        ->execute();

	$output = '<thead><tr>';
    foreach( $info[$category]['field'] as $f) {
        $output .= '<td>'. $f . '</td>';
    }
	$output .= '</tr></thead>>';
	$output .= '<tbody>';
	$records = array();
	while ($record = $result->fetchAssoc()) {
		$records[] = $record;

		$output .= '<tr>';
		foreach (array_keys( $record) as $key) {
			$output .= '<td>' . $record[$key] . '</td>';
		}
		$output .= '</tr>';
	}
	$output .= '</tbody>';

	db_set_active('default');

    return array( $records, $output);
}


function ocs_migrate_fce_area($form, &$form_state)
{
    $category = ( isset( $form_state['values']['category']) ? $form_state['values']['category'] : 'voice');

    list( $records, $output ) = _get_area_code( $category);

	$form['#area'] = $records;
	$form['#attributes'] = array('class' => array('myform'));


    $form['info'] = array(
        '#type' => 'markup',
        '#markup' => 'Migrate area table',
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
		'#type' => 'markup',
		'#markup' => '<table>' . $output . '</table>',
        '#prefix' => '<div id="ocs_ajax_select_area_code_category_div">',
        '#suffix' => '</div>',
	);

	return $form;
}

function ocs_ajax_select_area_code_category( $form, &$form_state)
{
    return $form['data'];
}

function ocs_migrate_fce_area_submit($form, &$form_state)
{
	$values = $form_state['values'];
	if ($values['op'] == 'Save') {
		dpm($values, 'values');

        if ( $values['remove'] == '1') {
            dpm( 'remove all idd_ratinggroup instances.');
        
            // remove all existing values
            $type = ( $values['category'] == 'intl voice') ? 'idd_ratinggroup' : 'area_code';
            $items = entity_load( 'node', FALSE, array( 'type' => $type));
            foreach( array_keys( $items) as $nid) {
                dpm( 'node '.$nid.' deleted.');
                node_delete( $nid);
            }
        }

        if ( $values['category'] == 'intl voice') {
            _update_area_code_for_intl_voice( $form['#area'], $values['check'] == '1');
            return;
        }

		// add entities
		foreach ($form['#area'] as $r) {
			$node = ocs_admin_get_new_node('area_code');
			$node->title = $r['ruleName'];
			$node->field_prefix['und'][0]['value'] = $r['second_prefix'];
			$node->field_area_code['und'][0]['value'] = $r['region_code'];

			$items = entity_load('node', FALSE, array(
				'type' => 'carrier_mobile',
				'title' => $r['carrier']
			));
			if (count($items) == 1) {
				$nids = array_keys($items);
				$node->field_ref_carrier_mobile['und'][0]['nid'] = $nids[0];
			}
			else {
				dpm('Carrier not found: ' . $r['carrier']);
			}
			node_save($node);
		}
	}
}

function _update_area_code_for_intl_voice( $records, $check_only)
{
    // get country code
   	db_set_active('fce');

	$query = db_select('intl_country_code', 'c');
	$result = $query->fields('c', array(
		'ruleName',
		'country_prefix',
        ))->execute();

	$country_code = array();
	while ($record = $result->fetchAssoc()) {
		$country_code[ $record['ruleName']] = $record['country_prefix'];
    }
	db_set_active('default');

    // find 'FCE IDD Numbering Plan'
    $plan = 'FCE IDD Numbering Plan 2';
    $np = _get_first_node_by_title('numberingplan_idd', $plan);
    if (empty($np)) {
        dpm('numbering plan not found: ' . $plan);
        return;
    }

	global $carrier_info;
	
	if ( empty($carrier_info)) {
		$carrier_info = ocs_load_all_carrier();
		dpm( $carrier_info, 'carrier info reloaded.');
	}		

	// find rating group list
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'idd_ratinggroup')
		->fieldCondition( 'field_ref_numberingplan_idd', 'nid', $np->nid)
		->execute();
		
	$rating_group_list = array();
	if ( count( $result) > 0) {		// find the ratinggroup first
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			$rating_group_list[$node->field_prefix['und'][0]['value']] = $nid;
		}
	}
	dpm( $rating_group_list, 'rating group list');	
	dpm( $np, 'IDD numbering plan');
		
    foreach ($records as $r) {
        $prefix = ( isset( $country_code[ $r['country_code']])) ?  
            ($country_code[ $r['country_code']] . $r['NPA_prefix']) : 
            ($r['prefix'] . $r['NPA_prefix']);


        if ( isset( $rating_group_list[$prefix])) {
            dpm( t('existing prefix : carrier=@c prefix=@p name=!n', array( '@c' => $r['intl_carrier'],
                '@p' => $prefix, '!n' => $r['ruleName'])));

            $nid = $rating_group_list[$prefix];
            $c = node_load( $nid);
            _set_idd_ratinggroup( $carrier_info, $c, $np, $r, $prefix);
            //dpm( $c, 'idd_ratinggroup');

            if ( ! $check_only) {
                node_save( $c);
            }
        }
        else {
            dpm( t('new prefix : carrier=@c prefix=@p name=!n', array( '@c' => $r['intl_carrier'],
                '@p' => $prefix, '!n' => $r['ruleName'])));

            $c = ocs_admin_get_new_node('idd_ratinggroup');
            _set_idd_ratinggroup( $carrier_info, $c, $np, $r, $prefix);
            //dpm( $c, 'idd_ratinggroup');

            if ( ! $check_only) {
                node_save( $c);
                $np->field_ref_idd_ratinggroup['und'][] = array('nid' => $c->nid);
            }
        }
    }

	if ( ! $check_only) node_save($np);
}

function _set_idd_ratinggroup( $carrier_info, &$r, $np, $rule, $prefix)
{
	$carrier_name = $rule['intl_carrier'];

	$r->title = 'idd_ratinggroup';
	$r->field_ref_numberingplan_idd['und'][0]['nid'] = $np->nid;
	$r->field_service_type_of_provider['und'][0]['tid'] = 406;		// Mobile
	$r->field_ref_carrier_mobile['und'][0]['nid'] = $carrier_info[$carrier_name]['nid'];
	$r->field_prefix['und'][0]['value'] = $prefix;
	$r->field_area_name['und'][0]['value'] = $rule['ruleName'];
	$r->field_rating_group['und'][0]['value'] = $carrier_name . '_' . $rule['rating_group'];
	
	// set type of call
    // outgoing international voice call
    $r->field_ref_type_of_call['und'][0]['tid'] = 1514;
}

function ocs_migrate_fce_timetable($form, &$form_state)
{
	db_set_active('fce');

	$query = db_select('voice_time_table', 'a');
	$result = $query->fields('a', array(
		'carrier',
		'ruleName',
		'holiday',
		'week',
		'timeLower',
		'timeUpper'
	))->orderBy('carrier')->orderBy('ruleName')->execute();

	$output = '<thead><tr><td>Carrier</td><td>Name</td><td>Holiday</td><td>Week</td><td>From</td><td>To</td></tr></thead>';
	$output .= '<tbody>';
	$records = array();
	while ($record = $result->fetchAssoc()) {
		$records[] = $record;

		$output .= '<tr>';
		foreach (array_keys( $record) as $key) {
			$output .= '<td>' . $record[$key] . '</td>';
		}
		$output .= '</tr>';
	}
	$output .= '</tbody>';

	$form['#timetable'] = $records;

	db_set_active('default');

	$form['actions'] = array('#type' => 'actions');

	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);

	$form['actions']['cancel'] = array(
		'#type' => 'submit',
		'#value' => t('Cancel'),
	);

	$form['carrier'] = array(
		'#type' => 'fieldset',
		'#title' => 'Area',
		'#collapsible' => TRUE,
	);

	// $form['carrier']['remove'] = array(
	// '#type' => 'radios',
	// '#title' => 'remove all existing data',
	// '#options' => array( 'No', 'Yes'),
	// '#default_value' => '1',
	// );

	$form['carrier']['data'] = array(
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

		// if ( $values['remove'] == '1') {
		// dpm( 'remove all area instances.');
		//
		// // remove all existing values
		// $items = entity_load( 'node', FALSE, array( 'type' => 'area_code'));
		// foreach( array_keys( $items) as $nid) {
		// dpm( 'node '.$nid.' deleted.');
		// node_delete( $nid);
		// }
		// }

		// add entities
		// manual migration
	}
}

function _analyze_tariff_plan( $carrier)
{
	foreach( $carrier as $c) {
		if ( count( $c['rating_group']) == 1) {
			// only one rating group
			dpm( t('One rating : '.$c['ruleName']));
		}
		else {
			dpm( t('Multi rating : '.$c['ruleName']));
			foreach( $c['rating_group'] as $k => $r) {
				dpm( t('  group:@group -> @n', 
					array( '@group' => $k, '@n' => count($r))));
			}
		}
	}
} 

function _get_voice_tariff($category = 'A')
{
	global $carrier_info;
	
	if ( empty($carrier_info)) {
		$carrier_info = ocs_load_all_carrier();
		dpm( $carrier_info, 'carrier info reloaded.');
	}		
		
	
	//dpm( $carrier, 'carrier');
	
	//_analyze_tariff_plan( $carrier);
	
	db_set_active('fce');

	$fields = array(
		'user_category',
		'called_carrier',
		'ruleName',
		'isDDD',
		'rating_group',
		'time_id',
		'is_video',
		'second_prefix'
	);
	$query = db_select('voice_tariff_decision', 'v');
	$query->fields('v', $fields);

	if ($category == 'All') {
		$query->orderBy('v.user_category');
	}
	else if ( $category == 'null') {
		$query->where('user_category is null');
	}
	else {
		$query->where('user_category = :category', array(':category' => $category));
	}

	$result = $query->orderBy('v.called_carrier')->orderBy('v.user_category')->orderBy('v.ruleName')->execute();

	$output = '<thead><tr>';
	foreach ($fields as $field) {
		$output .= '<td>' . $field . '</td>';
	}
	$output .= '<td>Region Flag</td>';
	$output .= '<td>Rating Groups</td>';
	$output .= '</tr></thead>';
	$output .= '<tbody>';
	$records = array();
	while ($record = $result->fetchAssoc()) {

		$output .= '<tr>';
		foreach (array_keys( $record) as $key) {
			$output .= '<td>' . $record[$key] . '</td>';
		}
		$c = $record['called_carrier'];
		$output .= '<td>' . $carrier_info[$c]['regionFlag'] . '</td>';
		$output .= '<td>' . implode(',', array_keys($carrier_info[$c]['rating_group'])) . '</td>';
		$output .= '</tr>';

		// $record['regionFlag'] = $carrier_info[$c]['regionFlag'];
		$records[] = $record;
	}
	$output .= '</tbody>';

	db_set_active('default');

	return array(
		$records,
		$output,
		$carrier_info,
	);
}

function ocs_migrate_fce_voiceplan($form, &$form_state)
{

	$category = isset($form_state['values']['category']) ? $form_state['values']['category'] : 'null';

	// dpm( $category, 'category:');
	// dpm( $form_state['values'], 'values');
	list($records, $output, $carrier) = _get_voice_tariff($category);

	$form['#carrier'] = $carrier;
	$form['#attributes'] = array('class' => array('myform'));

	$form['#rule'] = $records;
	
	$form['category'] = array(
		'#type' => 'select',
		'#title' => 'User Category to migrate',
		'#options' => drupal_map_assoc(array(
			'All',
			'null',
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

	$form['data'] = array(
		'#type' => 'markup',
		'#title' => 'Rule data',
		'#markup' => '<table>' . $output . '</table>',
		'#prefix' => '<div id="ocs_ajax_user_category_div">',
		'#suffix' => '</div>',
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

function ocs_ajax_select_user_category($form, &$form_state)
{
	return $form['data'];
}

function _get_first_node_by_title($type, $title)
{
	$items = entity_load('node', FALSE, array(
		'type' => $type,
		'title' => $title
	));
	if (count($items) > 0) {
		$nids = array_keys($items);
		return $items[$nids[0]];
	}

	return NULL;
}

function ocs_migrate_fce_voiceplan_submit($form, &$form_state)
{
	$values = $form_state['values'];
	if ($values['op'] == 'Save') {
		
		dpm($values, 'values');

		// find 'FCE Numbering Plan'
		$plan = 'FCE Numbering Plan';
		$np = _get_first_node_by_title('numberingplan_domestic', $plan);
		if (empty($np)) {
			dpm('numbering plan not found: ' . $plan);
			return;
		}

		if ($values['remove'] == '1') {
			// remove all ratinggroup fields
			foreach ($np->field_ref_domestic_ratinggroup['und'] as $nid) {
				node_delete($nid['nid']);
				dpm(t('Domestic rating group @id is removed', array('@id' => $nid['nid'])));
			}

			
			// find dangling entity
			$query = new EntityFieldQuery();
			$result = $query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', 'domestic_ratinggroup')
				->execute();
		
			if ( count( $result) > 0) {		// find the ratinggroup first
				foreach( array_keys( $result['node']) as $nid) {
					$node = node_load( $nid);
					dpm( $node, 'node:'.$nid);
					if ( ! isset($node->field_ref_numberingplan_domestic['und']) || 
						$node->field_ref_numberingplan_domestic['und'][0]['nid'] == 0 ||
						$node->field_ref_numberingplan_domestic['und'][0]['nid'] == $np->nid) {
							node_delete( $nid);
							dpm( 'dangling entity is removed: '. $nid);
						}
				}
			}
	
			unset($np->field_ref_domestic_ratinggroup);
		}
		
		// $rating_group_list = array();
		// foreach ($form['#rule'] as $rule) {
			// $rating_group_list[$rule['ruleName']][$rule['called_carrier']][] = $rule;
		// }
		//dpm($rating_group_list, 'rating group list');
		
		// foreach( $rating_group_list as $k => $v) {
			// dpm( t('@r: @c @n', array( '@r' => $k, 
				// '@c' => implode( ',', array_keys($v)), 
				// '@n' => count( array_values($v)) 
				// )));
		// }

		_update_numbering_plan($np, $form['#rule'], $form['#carrier'], $values['check'] == '0');
	}

}

function _update_numbering_plan($np, $rule_list, $carrier_info, $update_flag)
{
	// find rating group list
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'domestic_ratinggroup')
		->fieldCondition( 'field_ref_numberingplan_domestic', 'nid', $np->nid)
		->execute();
		
	$rating_group_list = array();
	if ( count( $result) > 0) {		// find the ratinggroup first
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			$rating_group_list[$node->field_rating_group['und'][0]['value']][$node->field_ref_carrier_mobile['und'][0]['nid']][] = $nid;
		}
	}
	//dpm( $rating_group_list, 'rating group list');	
				
	foreach ($rule_list as $rule) {
		$carrier_name = $rule['called_carrier'];
		
		// set callee's area code
		$need_area_code = _need_area_code( $carrier_info, $carrier_name);
		$area_code = array( null);
		if ( $need_area_code) {
			dpm( 'Need area code: carrier='.$carrier_name.' rating_group='.$rule['rating_group']);
			
			if ( ! isset($carrier_info[$carrier_name]['rating_group'][$rule['rating_group']]) ) {
				drupal_set_message( t('Rating group not found. Carrier=@c RatingGroup=@r,@ra', 
					array( '@c' => $carrier_name, '@r' => $rule['rating_group'], '@ra' => $rule['ruleName'])),
					'error');
				continue;				
			}
			else {
				$area_code = array_keys( $carrier_info[$carrier_name]['rating_group'][$rule['rating_group']]);
				//dpm( $carrier_info[$carrier_name], 'carrier');
			}
		}
				
		if ( ! isset( $carrier_info[$carrier_name]['nid'])) {
			dpm( 'nid not found for carrier:'. $carrier_name);
			continue;
		}
		
		$carrier_nid = $carrier_info[$carrier_name]['nid'];
		if ( isset($rating_group_list[$rule['ruleName']][$carrier_nid])) {
			// rating group exist already
			
			$result = $rating_group_list[$rule['ruleName']][$carrier_nid];
			if ( $need_area_code && (count( $result) != count( $area_code))) {
				dpm( $result, 'mismatch with area code');
				dpm( $area_code, 'mismatch with area code');
			}
			//dpm( $result, 'rating group');
			$i = 0;
			foreach( $result as $nid ) {
					
				dpm( t('existing rating group: carrier=@c rating_group=@r,@ra area=@a', 
                    array( '@c' => $rule['called_carrier'],
					    '@r' => $rule['rating_group'], 
                        '@ra' => $rule['ruleName'], 
                        '@a' => implode( ',', $area_code))));
				
				$r = node_load( $nid);
				//dpm( $r, 'rating group');
				_set_domestic_ratinggroup( $carrier_info, $r, $np, $rule, $need_area_code ? $area_code[$i++] : null);
				if ( $update_flag) node_save( $r);
			}
		}
		else {
			foreach( $area_code as $code ) {
				dpm( t('new rating group: carrier=@c rating_group=@r area=@a', array( '@c' => $rule['called_carrier'],
					'@r' => $rule['ruleName'], '@a' => $code)));
				// make new rating group
				$r = ocs_admin_get_new_node('domestic_ratinggroup');
				_set_domestic_ratinggroup( $carrier_info, $r, $np, $rule, $code);
				if ( $update_flag) {
					node_save( $r);
				
					$np->field_ref_domestic_ratinggroup['und'][] = array('nid' => $r->nid);
									// update rating_group_list
					$rating_group_list[$r->field_rating_group['und'][0]['value']][$r->field_ref_carrier_mobile['und'][0]['nid']][] = $r->nid;
				}
			}
		}
		
	}

	if ( $update_flag) node_save($np);

}

function _set_domestic_ratinggroup( $carrier_info, &$r, $np, $rule, $area_code)
{
	$carrier_name = $rule['called_carrier'];

	if ( isset( $r->field_ref_numberingplan_domestic['und'])) {
		if ( $r->field_ref_numberingplan_domestic['und'][0]['nid'] != $np->nid )
			dpm( 'mismatch: ' . $r->field_ref_numberingplan_domestic['und'][0]['nid'] . ' : ' . $np->nid);
		if ( $r->field_ref_carrier_mobile['und'][0]['nid'] != $carrier_info[$carrier_name]['nid'] )
			dpm( 'mismatch: ' . $r->field_ref_carrier_mobile['und'][0]['nid'] . ' : ' . $carrier_info[$carrier_name]['nid']);
		if ( $r->field_rating_group['und'][0]['value'] != $rule['ruleName'] )
			dpm( 'mismatch: ' . $r->field_rating_group['und'][0]['value'] . ' : ' . $rule['ruleName'] );
	}
		
	$r->title = 'domestic_ratinggroup';
	$r->field_ref_numberingplan_domestic['und'][0]['nid'] = $np->nid;
	$r->field_service_type_of_provider['und'][0]['tid'] = 406;		// Mobile
	$r->field_ref_carrier_mobile['und'][0]['nid'] = $carrier_info[$carrier_name]['nid'];
	$r->field_is_samezone['und'][0]['tid'] = 1988;		// All
	$r->field_rating_group['und'][0]['value'] = $rule['ruleName'];
	
	// set type of call
	if (strcasecmp(substr($carrier_name, 0, 6), 'UNITEL') == 0) {
		$r->field_ref_type_of_call['und'][0]['tid'] = 725;
		// outgoing on net voice call
	}
	else if (substr($carrier_name, -1, 4) == '_INT') {
		$r->field_ref_type_of_call['und'][0]['tid'] = 1514;
		// outgoing international voice call
	}
	else {
		// 1513 outgoing off net voice call
		$r->field_ref_type_of_call['und'][0]['tid'] = 1513;
	}

	// reset area_code_to
	if ( ! empty( $area_code)) {
		// find area code nid
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'area_code')
			->fieldCondition( 'field_ref_carrier_mobile', 'nid', $carrier_info[$carrier_name]['nid'])
			->fieldCondition( 'field_area_code', 'value', $area_code)
			->execute();

			// TODO : area_code 1개와 매핑되는게 아님.. area_code_to를 text로 바꿔야 함
		if ( count( $result) > 0) {
			$nids = array_keys( $result['node']);
			$r->field_ref_area_code_to['und'][0]['nid'] = $nids[0];
		}
	}
}

function _need_area_code( $carrier_info, $name)
{
	// return TRUE if the carrier need area code to build rating group
	if ( isset( $carrier_info[$name])) {
		if ( count( $carrier_info[$name]['rating_group']) == 1)
			return FALSE;
		
		if ( count( $carrier_info[$name]['region_code']) == 1)
			return FALSE;
			
		return TRUE;
	}
	
	dpm( 'Invalid carrier info: ' . $name);
	
	return FALSE;
}

function ocs_load_all_carrier()
{
	$carrier = &drupal_static(__FUNCTION__, NULL);
	if (empty($carrier)) {
		db_set_active('fce');

		$fields = array(
			'ruleName',
			'prefix',
			'regionFlag'
		);
		$query = db_select('carrier', 'c');
		$result = $query->fields('c', $fields)->orderBy('ruleName')->execute();

		$carrier = array();
		while ($record = $result->fetchAssoc()) {
			$carrier[$record['ruleName']] = $record;
		}

		$fields = array(
			'ruleName',
			'carrier',
			'second_prefix',
			'rating_group',
			'region_code'
		);
		$query = db_select('area', 'a');
		$result = $query->fields('a', $fields)->orderBy('ruleName')->execute();

		$area = array();
		while ($record = $result->fetchAssoc()) {
			$carrier[$record['carrier']]['rating_group'][$record['rating_group']][$record['region_code']][] = $record['second_prefix'];
			$carrier[$record['carrier']]['region_code'][$record['region_code']][] = $record['second_prefix'];
		}

		db_set_active('default');

        // get nid of carrier 		
        $query = new EntityFieldQuery();
        $result = $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'carrier_mobile')
            ->execute();

        foreach( array_keys( $result['node']) as $nid) {
            $node = node_load( $nid);
            $carrier[$node->title]['nid'] = $nid;
        }
            
        //dpm( $carrier, 'carrier info');
	}

	return $carrier;

}

function ocs_load_all_rate()
{
	$rate = &drupal_static(__FUNCTION__, NULL);
	if (empty($rate)) {
		db_set_active('fce');

		$query = db_select('sub_tariff_data', 'c');
		$result = $query->fields('c')->execute();

		$rate = array();
		while ($record = $result->fetchAssoc()) {
			$rate[$record['sub_tariff_name']] = $record;
		}

		db_set_active('default');
	}

	return $rate;
}

function ocs_migrate_fce_voice_tariff($form, &$form_state)
{
	$category = isset($form_state['values']['category']) ? $form_state['values']['category'] : 'A';

	// dpm( $category, 'category:');
	// dpm( $form_state['values'], 'values');
	list($records, $output) = _get_voice_tariff($category);
	$form['#rule'] = $records;
	
	$rate = ocs_load_all_rate();
	dpm($rate, 'rate');
	$form['#rate'] = $rate;

	$form['#attributes'] = array('class' => array('myform'));

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
		'#type' => 'markup',
		'#title' => 'Rule data',
		'#markup' => '<table>' . $output . '</table>',
		'#prefix' => '<div id="ocs_ajax_user_category_div">',
		'#suffix' => '</div>',
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

function ocs_migrate_fce_voice_tariff_submit($form, &$form_state)
{
	$values = $form_state['values'];
	if ($values['op'] == 'Save') {
		dpm($values, 'values');

		// find 'voice_plan_a'
		$plan = node_load(24081);
		// 'Prepaid A'; //24072
		dpm($plan, 'Prepaid A > voice_plan_a');

		// add rating group records
		foreach ($form['#rule'] as $rule) {
			//dpm( $rule, 'rule');
			$rate_list = _get_rate_list($form['#rate'], $rule['ruleName']);
			//dpm( $rate_list, 'rate list:'.$rule['ruleName']);
			_set_rate($plan->nid, $rule['ruleName'], $rate_list);
		}

	}
}

function _set_rate($plan_nid, $name, $rate_list)
{
	$list = entity_load('node', FALSE, array(
		'type' => 'rate',
		'title' => $name
	));
	if (count($list) >= 1) {
		$rate_nids = array_keys($list);
		$new_rate = node_load($rate_nids[0]);
	}
	else {
		$new_rate = ocs_admin_get_new_node('rate');
	}

	$new_rate->title = $name;
	$new_rate->field_range_units['und'][0]['tid'] = 390;
	// seconds
	$new_rate->field_price_units['und'][0]['tid'] = 450;
	// MNT
	$new_rate->field_uom_units['und'][0]['tid'] = 451;
	// seconds
	$new_rate->field_ref_tariffplan['und'][0]['nid'] = $plan_nid;
	$new_rate->field_ref_tree_tid['und'][0]['value'] = 494;

	$start = 0;
	foreach ($rate_list as $rate) {
		$charge = entity_create('field_collection_item', array('field_name' => 'field_charge_collection'));
		$charge->setHostEntity('node', $new_rate);
		$charge->field_range_start = array('und' => array('0' => array('value' => $start, )));
		$charge->field_range_end = array('und' => array('0' => array('value' => $start + $rate['e2'], )));
		$charge->field_uom_amount = array('und' => array('0' => array('value' => $rate['e2'], )));
		$charge->field_price_amount_float = array('und' => array('0' => array('value' => $rate['e1'], )));
		$charge->save();
		$start += $rate['e2'];
	}

	node_save($new_rate);
}
