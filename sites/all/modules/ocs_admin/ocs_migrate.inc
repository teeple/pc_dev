<?php

require_once('ocs_migrate_timetable.inc');
require_once('ocs_migrate_tariff.inc');
require_once('ocs_migrate_numberingplan.inc');
require_once('ocs_migrate_rate.inc');


function ocs_migrate_fce_product($form, &$form_state)
{
	db_set_active('fce');

	$fields = array(
		'user_category',
	);
	$table = 'voice_tariff_decision';

	$query = db_select( $table, 'v');
	$result = $query->fields( 'v', $fields)->distinct()
        ->orderBy( 'user_category')
		->execute();

	$output = '<thead><tr>';
    foreach( $fields as $f) {
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

	$form['#rules'] = $records;
	$form['#attributes'] = array('class' => array('myform'));

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
		'#type' => 'fieldset',
		'#title' => 'Carrier',
		'#collapsible' => TRUE,
	);

	$form['data']['list'] = array(
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

/*
   $type : idd or domestic
   */
function _load_all_products()
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'simpleproductoffering')
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



function ocs_migrate_fce_product_submit($form, &$form_state)
{
	$values = $form_state['values'];
	if ($values['op'] == 'Save') {
		dpm($values, 'values');

		if ( $values['remove'] == '1') {
			// remove all existing values
			drupal_set_message( 'not implemented', 'error');
		}

		$product_list = _load_all_products();
		dpm( $product_list, 'product list');

		// add entities
		foreach ($form['#rules'] as $r) {
			if ( empty( $r['user_category'])) continue;

            $category = $r['user_category'];
			$product_name = 'Prepaid ' . $category;

			if ( isset( $product_list[$product_name])) {
				dpm( t( 'existing product=@p ', array( '@p' => $product_name)));
				$product = node_load( $product_list[$product_name]);
			}
			else {
				dpm( t( '>>> new product=@p', array( '@p' => $product_name)));
				$product = ocs_admin_get_new_node('simpleproductoffering');
			}

			if ( $values['check'] == '0') {
				$product->title = $product_name;
				$product->field_description['und'][0]['value'] = 'FCE Product for Category '. $category;
				$product->field_offering_status['und'][0]['tid'] = 19;	//editing
				$product->field_product_type['und'][0]['tid'] = 479;
				$product->field_product_id['und'][0]['value'] = 'fce_prepaid_'.$category;
				$product->field_customer_type['und'][0]['tid'] = 1636;
				node_save($product);
			}

			$tariffplan_list = array( 
					array( 'name' => 'voice_plan_'.$category, 'tid' => 664, 'voca' => 'tpl_tariffplan_mobile_voice'),
					array( 'name' => 'sms_plan_'.$category, 'tid' => 665, 'voca' => 'tpl_tariffplan_mobile_sms'));

			// check if it has tariff plan
			foreach( $tariffplan_list as $plan) {
				$query = new EntityFieldQuery();
				$result = $query->entityCondition('entity_type', 'node')
					->entityCondition('bundle', 'tariffplan')
					->propertyCondition('title', $plan['name'])
					->execute();

				if ( count( $result) == 0) {
					// add new tariff plan
					$p = ocs_admin_get_new_node('tariffplan');
					$p->title = $plan['name'];
					$p->field_ref_product['und'][0]['nid'] = $product->nid;
					$p->field_ref_tree_tid['und'][0]['value'] = $plan['tid'];
					$p->field_tree_child_voca_name['und'][0]['value'] = $plan['voca'];
					node_save( $p);

					dpm( '>>> new tariff plan : '. $plan['name']);
				}
			}

		}
	}
}


function ocs_migrate_fce_carrier($form, &$form_state)
{
	db_set_active('fce');

	$fields = array(
		'ruleName',
		'prefix',
		'regionFlag'
	);
	$query = db_select('carrier', 'c');
	$result = $query->fields('c', $fields)->execute();


	$output = '<thead><tr>';
    foreach( $fields as $f) {
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

	$form['#carrier'] = $records;
	$form['#attributes'] = array('class' => array('myform'));

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
		'#type' => 'fieldset',
		'#title' => 'Carrier',
		'#collapsible' => TRUE,
	);

	$form['data']['list'] = array(
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

		$carrier_info = ocs_load_all_carrier();
		dpm( $carrier_info, 'carrier info');

		if ( $values['remove'] == '1') {
		
			// remove all existing values
			$items = entity_load( 'node', FALSE, array( 'type' => 'carrier_mobile'));
			foreach( array_keys( $items) as $nid) {
				node_delete( $nid);
				dpm( 'remove carrier nid='.$nid);
			}
		}

        $prefix_type['domestic'] = array_keys( taxonomy_get_term_by_name( 'domestic', 'prefix_type'));

		// add entities
		foreach ($form['#carrier'] as $r) {
            $carrier_name = $r['ruleName'];
			if ( isset( $carrier_info[$carrier_name])) {
				dpm( t( 'existing carrier=@c prefix=@p', array( '@c' => $carrier_name, '@p' => $r['prefix'])));
				if ( ! isset( $carrier_info[$carrier_name]['nid'])) {
					dpm( t( 'carrier info not exist for "@c" prefix=@p', array( '@c' => $carrier_name, '@p' => $r['prefix'])));
					continue;
				}
				$node = node_load( $carrier_info[$carrier_name]['nid']);
			}
			else {
				dpm( t( '>>> new carrier=@c prefix=@p', array( '@c' => $arrier_name, '@p' => $r['prefix'])));
				$node = ocs_admin_get_new_node('carrier_mobile');
			}

			if ( $values['check'] == '0') {
                $node->title = $carrier_name;
                $node->field_ref_prefix_type['und'][0]['tid'] = $prefix_type['domestic'][0];
                $node->field_prefix_multiple['und'][0]['value'] = $r['prefix'];

				node_save($node);
			}
		}
	}
}

function _get_area_code( $type)
{
	db_set_active('fce');

	if ( $type == 'domestic:voice') {
		$table = 'area'; 
		$field = array(
			'carrier',
			'ruleName',
			'second_prefix',
			'region_code',
			'rating_group'
			);
		$order = 'carrier';
	}
	else if ( $type == 'intl:voice') {
		$table = 'intl_area';
		$field = array( 'ruleName', 'intl_carrier', 'prefix', 'country_code', 'NPA_prefix', 'country_prefix', 'rating_group');
		$order = 'intl_carrier';
	}
	else {
		drupal_set_message( 'Invalid configuration. ', 'error');
		return array();
	}

	$query = db_select( $table, 'a');
	$result = $query->fields('a', $field)
        ->orderBy( $order)
        ->execute();

	$output = '<thead><tr>';
    foreach( $field as $f) {
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


/*
   $type : idd or domestic
   */
function _load_all_numbering_plan( $type)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->execute();

	$list = array();
	if ( count( $result) > 0) {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			$list[$nid] = $node->title;
		}
	}

	return $list;
}

	
function ocs_migrate_fce_area($form, &$form_state, $domestic_or_intl = 'domestic', $calltype = 'voice')
{
	$type = $domestic_or_intl . ':' . $calltype;
    list( $records, $output ) = _get_area_code( $type);

	$form['#area'] = $records;
	$form['#attributes'] = array('class' => array('myform'));

    $form['info'] = array(
        '#type' => 'markup',
        '#markup' => t( 'Migrate area table of Domestic Numbering Plan.'),
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
		'#type' => 'fieldset',
		'#title' => 'Migration data',
		'#collapsible' => TRUE,
		'#prefix' => '<div id="ocs_ajax_user_category_div">',
		'#suffix' => '</div>',
	);

	$form['data']['list'] = array(
		'#type' => 'markup',
		'#markup' => '<table>' . $output . '</table>',
	);

	return $form;
}


function ocs_migrate_fce_area_submit($form, &$form_state)
{
	$values = $form_state['values'];
	if ($values['op'] == 'Save') {
		dpm($values, 'values');

		$carrier_info = ocs_load_all_carrier();
		dpm( $carrier_info, 'carrier info reloaded.');

		_update_area_code_for_domestic_voice( $carrier_info, $form['#area'], $values['check'] == '1');
	}
}

function _update_area_code_for_domestic_voice( $carrier_info, $records, $check_only)
{
	// add entities
	foreach ($records as $r) {

		if ( ! isset( $carrier_info[$r['carrier']])) {
			dpm('Carrier not found: ' . $r['carrier']);
			continue;
		}

		if ( !isset( $carrier_info[$r['carrier']]['nid'])) {
			dpm('Carrier nid not found: ' . $r['carrier']);
			continue;
		}
		$carrier_nid = $carrier_info[$r['carrier']]['nid'];
		
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'area_code')
			->propertyCondition( 'title', $r['ruleName'])
			->fieldCondition( 'field_ref_carrier_mobile', 'nid', $carrier_nid)
			->fieldCondition( 'field_prefix', 'value', $r['second_prefix'])
			->execute();

		if ( count( $result) > 0) {
			foreach( array_keys( $result['node']) as $nid) {
				$node = node_load( $nid);
				if ( $node->field_area_code['und'][0]['value'] != $r['region_code'] ) {
					dpm( t('Area code is updated for @carrier prefix:@prefix. Region code: @a=>@b', 
						array( '@carrier' => $r['carrier'], '@prefix' => $r['second_prefix'],
							'@a' => $node->field_area_code['und'][0]['value'], '@b' => $r['region_code'])));
						
					$node->field_area_code['und'][0]['value'] = $r['region_code'];
				}
				else {
					dpm( t('Existing Area code of @carrier prefix:@prefix. Region code: @a', 
						array( '@carrier' => $r['carrier'], '@prefix' => $r['second_prefix'],
							'@a' => $node->field_area_code['und'][0]['value'] )));
				}
			}
		}
		else {
			$node = ocs_admin_get_new_node('area_code');
			$node->title = $r['ruleName'];
			$node->field_prefix['und'][0]['value'] = $r['second_prefix'];
			$node->field_area_code['und'][0]['value'] = $r['region_code'];
			$node->field_ref_carrier_mobile['und'][0]['nid'] = $carrier_nid;

			dpm( t('Add New area code for @carrier prefix:@prefix. Region code: @b', 
				array( '@carrier' => $r['carrier'], '@prefix' => $r['second_prefix'],
					'@b' => $r['region_code'])));
		}
		
		if ( ! $check_only) node_save($node);
	}

}

function _get_time_table( $call_type)
{
	db_set_active('fce');

	if ( $call_type == 'domestic:voice') {
		$fields = array(
			'carrier',
			'ruleName',
			'holiday',
			'week',
			'timeLower',
			'timeUpper'
		);
		$table = 'voice_time_table';
		$order = array('carrier', 'ruleName');
	}
	else if ( $call_type == 'intl:voice') {
		$fields = array(
			'intl_carrier', 
			'holiday', 'week', 'timeLower', 'timeUpper',
			'ruleName', 
		);
		$table = 'intl_voice_time_table';
		$order = array( 'intl_carrier', 'week');
	}
	else {
		dpm( 'Unknown call type : '. $call_type);
		return array();
	}

	$query = db_select( $table, 'v');
	$query->fields('v', $fields);

	foreach( $order as $o) {
		$query->orderBy( $o);
	}
	$result = $query->execute();

	$output = '<thead><tr>';
	foreach ($fields as $field) {
		$output .= '<td>' . $field . '</td>';
	}

	$output .= '</tr></thead>';
	$output .= '<tbody>';
	$records = array();
	while ($record = $result->fetchAssoc()) {

		$output .= '<tr>';
		foreach (array_keys( $record) as $key) {
			$output .= '<td>' . $record[$key] . '</td>';
		}

		$output .= '</tr>';

		// $record['regionFlag'] = $carrier_info[$c]['regionFlag'];
		$records[] = $record;
	}
	$output .= '</tbody>';

	db_set_active('default');

	return array( $records, $output);
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

function _get_voice_tariff( $call_type, $category='All', $condition='user_category')
{
	$carrier_info = ocs_load_all_carrier();
	dpm( $carrier_info, 'carrier info reloaded.');
	
	db_set_active('fce');

	if ( $call_type == 'domestic:voice') {
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
		$table = 'voice_tariff_decision';
		$order = ($condition == 'user_category') ? 
				array('v.user_category', 'v.called_carrier', 'v.ruleName'):
				array('v.called_carrier', 'v.user_category', 'v.ruleName');
	}
	else if ( $call_type == 'intl:voice') {
		$fields = array(
			'user_category', 
			'intl_carrier', 
			'country_code', 
			'ruleName', 
			'intl_time_id', 
			'intl_call_type', 
			'isDDD', 
			'called', 
			'rating_group', 
		);
		$table = 'intl_voice_tariff_decision';
		$order = array( 'intl_carrier');
	}
    else if ( $call_type == 'domestic:sms') {
        $fields = array( 'ruleName', 'call_type', 'called_carrier' ,'user_category', 'time_id', 'intl_time_id');
        $table = 'sms_price_decision';
        $order = array( 'user_category', 'called_carrier');
    }
	else {
		dpm( 'Unknown call type : '. $call_type);
		return array();
	}

	$query = db_select( $table, 'v');
	$query->fields('v', $fields);

	if ( $condition == 'user_category') {
		$query->where('user_category is null or user_category = :category', array(':category' => $category));
	}
	else if ( $condition == 'carrier') {
		$query->where( 'called_carrier = :category', array(':category' => $category));
	}

	foreach( $order as $o) {
		$query->orderBy( $o);
	}
	$result = $query->execute();

	$output = '<thead><tr>';
	foreach ($fields as $field) {
		$output .= '<td>' . $field . '</td>';
	}

	if ( $call_type == 'domestic:voice') {
		$output .= '<td>Region Flag</td>';
		$output .= '<td>Rating Groups</td>';
	}
	$output .= '</tr></thead>';
	$output .= '<tbody>';
	$records = array();
	while ($record = $result->fetchAssoc()) {

		$output .= '<tr>';
		foreach (array_keys( $record) as $key) {
			$output .= '<td>' . $record[$key] . '</td>';
		}

		if ( $call_type == 'domestic:voice') {
			$c = $record['called_carrier'];
			$output .= '<td>' . $carrier_info[$c]['regionFlag'] . '</td>';
			$output .= '<td>' . implode(',', array_keys($carrier_info[$c]['rating_group'])) . '</td>';
		}

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


function ocs_fce_tariffplan($form, &$form_state, $condition='carrier')
{

	$category = isset($form_state['values']['category']) ? $form_state['values']['category'] : 'Unitel';

	// dpm( $category, 'category:');
	// dpm( $form_state['values'], 'values');
	list($records, $output, $carrier) = _get_voice_tariff( 'domestic:voice', $category, $condition);

	$form['#carrier'] = $carrier;
	$form['#attributes'] = array('class' => array('myform'));
	
	$form['category'] = array(
		'#type' => 'select',
		'#title' => 'Category to browse',
		'#options' => drupal_map_assoc(array_keys($carrier)),
		'#default_value' => $category,
		'#ajax' => array(
			'callback' => 'ocs_ajax_select_user_category',
			'wrapper' => 'ocs_ajax_user_category_div',
		),
	);

	$form['data'] = array(
		'#type' => 'markup',
		'#title' => 'Rule data',
		'#markup' => '<table>' . $output . '</table>',
		'#prefix' => '<div id="ocs_ajax_user_category_div">',
		'#suffix' => '</div>',
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


