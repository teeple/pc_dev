<?php

function ocs_report( $nid)
{
	$output = '';

	$node = node_load( $nid);
	if ( $node->type == 'simpleproductoffering') {
		$output .= _ocs_report_product( $node);
	}

	return $output;
}		

function _ocs_report_product( $node)
{
	$output = '';

	// product description
	$field = field_info_instances( 'node', $node->type);
	$output .= t('<h3>Description</h3>');
	$output .= _ocs_report_get_fields( $field, $node);

	$tree_info = _load_tree_item_mixed_with_node_and_term( $node);
	//dpm( $tree_info, 'tree info');

	// for each attribute

	foreach( $tree_info['children'] as $child) {
		//$output .= t('<h2>%name</h2>', array( '%name' => $child['data']));
		$output .= _ocs_report_children( $child, 2);
	}

	return $output;
}	

function _ocs_report_children( $node, $depth=0)
{
	$output = '';

	$output .= $node['data'];

	if ( isset( $node['children'])) {

		$items = array();
		foreach( $node['children'] as $child) {
			$items[] = array(
				'data' => _ocs_report_children( $child, $depth+1),
			);
		}

		$output .= theme( 'item_list', array( 'items' => $items));
	}
	else {

		if ( $node['attr']['node_type'] == 'term') {
			$id = explode( '_', $node['attr']['id']);
			$term = taxonomy_term_load( $id[1]);
			//dpm( $term, $node['data']);

			if ( isset( $term->field_default_contenttype['und'][0]['value'])) {
				$query = new EntityFieldQuery();
				$result = $query->entityCondition('entity_type', 'node')
					->entityCondition('bundle', $term->field_default_contenttype['und'][0]['value'])
					->fieldCondition( 'field_ref_product', 'nid', $id[2])
					->fieldCondition( 'field_ref_tree_tid', 'value', $id[1])
					->execute();

				if ( count( $result) >0) {
					$nid = array_keys( $result['node']);
					$node = node_load( $nid[0]);
					$field = field_info_instances( 'node', $node->type);
					$output .= _ocs_report_get_fields( $field, $node);
				}
			}
			else if ( $node['attr']['rel'] == 'voice_tariffplan_domestic' ||
				$node['attr']['rel'] == 'sms_tariffplan_domestic' ) {
				$output .= _ocs_report_tariffplan( $id[2]);
			}
			else if ( $node['attr']['rel'] == 'voice_tariffplan_international' ) {
				$output .= _ocs_report_tariffplan_intl( $id[2]);
			}
			else {
//				dpm( $node['attr']['rel'], 'attr');
			}
		}
	}


	return $output;
}

function _ocs_report_tariffplan_intl( $tariffplanNid)
{
	$output = '';
	$node = node_load( $tariffplanNid);
	dpm( $node, $node->title);
	$field = field_info_instances( 'node', $node->type);
	$output .= _ocs_report_get_fields( $field, $node);

	if ( isset($node->field_ref_numberingplan_idd['und'][0]['nid'])) {
		// list time table
		//$output .= _ocs_report_timetable( $node->field_ref_timetable_domestic['und'][0]['nid']);

		// list numbering plan
		$output .= _ocs_report_numberingplan_intl( $tariffplanNid, $node->field_ref_numberingplan_idd['und'][0]['nid']);

		// list tariff
		//$output .= _ocs_report_tariff_mapping( $tariffplanNid);
	}
	return $output;
}

function _ocs_report_tariffplan( $tariffplanNid)
{
	$output = '';
	$node = node_load( $tariffplanNid);
	//dpm( $node, $node->title);
	$field = field_info_instances( 'node', $node->type);
	$output .= _ocs_report_get_fields( $field, $node);

	if ( isset($node->field_ref_numberingplan_domestic['und'][0]['nid'])) {
		/*
		$view = views_get_view('list_numberingplan_domestic_ratinggroup');
		$view->set_display('panel_displayall');
		$view->set_arguments(array( $node->field_ref_numberingplan_domestic['und'][0]['nid'], $tariffplanNid));
		$output .= $view->render();
		*/
		// list time table
		$output .= _ocs_report_timetable( $node->field_ref_timetable_domestic['und'][0]['nid']);

		// list numbering plan
		$output .= _ocs_report_numberingplan( $tariffplanNid, $node->field_ref_numberingplan_domestic['und'][0]['nid']);

		// list tariff
		//$output .= _ocs_report_tariff_mapping( $tariffplanNid);
	}
	return $output;
}

function _ocs_report_numberingplan_intl( $tariffplan_nid, $numberingplan_nid)
{
	$node = node_load( $numberingplan_nid);
	dpm( $node, $node->title);

	$np = array();
	foreach( $node->field_ref_idd_ratinggroup['und'] as $rg_nid) {
		$rg = node_load( $rg_nid['nid']);
		if ( empty( $rg)) continue;
		//dpm( $rg, $rg->title);

		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'basicrate_idd')
			->fieldCondition( 'field_ref_tariffplan', 'nid', $tariffplan_nid)
			->fieldCondition( 'field_rating_group', 'value', $rg->field_rating_group['und'][0]['value'])
		//	->fieldCondition( 'field_ref_tariffplan_idd_carrier', 'nid', $rg->field_ref_carrier_mobile['und'][0]['nid'])
			->execute();

		//dpm( $result, 'result');

		if ( count( $result) > 0) {
			$map = array();
			foreach( array_keys( $result['node']) as $rate_nid) {
				$basicrate = node_load( $rate_nid);
				if ( ! isset( $basicrate->field_ref_rate['und'][0]['nid'])) continue;

				list( $timefactor, $rate_value) = _ocs_report_get_rate_value( $basicrate);

				$map[$rg->field_ref_carrier_mobile['und'][0]['nid'] . ',' . $timefactor] = $rate_value;
			}
			ksort( $map);
			//dpm( $map, 'map');

			$np[json_encode( $map)][] = $rg_nid['nid'];
		}
	}

	dpm( $np, 'map');

	$field_list = array( 'field_ref_carrier_mobile', 'field_prefix', 'field_area_name', 'field_ref_type_of_call', 'field_rating_group');
	return _ocs_report_carrier_rating( $np, $field_list);
}

function _ocs_report_carrier_rating( $np, $field_list)
{
	$rows = array();
	$rg_field = null;
	$rg_header = array();
	foreach( $np as $key => $rg_list) {
		$rg_output = '';
		$rg_rows = array();
		foreach( $rg_list as $rg_nid) {
			$rg = node_load( $rg_nid);
			if ( $rg_field == null) {
				$rg_field = field_info_instances( 'node', $rg->type);
				//dpm( $rg_field, 'rg field');
			}

			$rg_rows[] = _ocs_report_get_selected_fields_list( $rg, $field_list);
		}

		if ( empty( $rg_header )) {
			foreach( $field_list as $name) {
				$rg_header[] = $rg_field[$name]['label'];
			}
		}

		// set rate 
		//
		$rate_rows = array();
		$rate_key = json_decode( $key, TRUE);
		$rate_field = null;
		foreach( $rate_key as $key => $rate) {
			$str = explode( ',', $rate);
			$node = node_load( $str[0]);
			if ( $rate_field == null) $rate_field = field_info_instances( 'node', $node->type);
			$keys = explode( ',', $key);
			if ( count( $keys) > 1) {		// international numbering plan 
				$carrier = node_load( $keys[0]);
				$rate_rows[] = array( 'data' => t( '<div class="myform report"><label>%label</label><div class="myform report value">%value</div></div>',
							array( '%label' => $carrier->title, '%value' => $keys[1])));
			}
			else {
				$rate_rows[] = array( 'data' => $key);
			}
			$rate_rows[] = array( 'data' => _ocs_report_get_fields( $rate_field, $node));
		}
		if ( empty( $rate_rows)) {
			$rate_rows = array( 'data' => 'No rate is defined');
		}

		$rows[] = array( theme( 'table', array( 'header' => $rg_header, 'rows' => $rg_rows)), 
				theme('item_list', array( 'items' => $rate_rows)));
	}

	return theme( 'table', array( 'rows' => $rows, 'header' => array( 'Carriers and Rating Group', 'Rate')));
}

function _ocs_report_numberingplan( $tariffplan_nid, $numberingplan_nid)
{
	$output = '';
	$node = node_load( $numberingplan_nid);
	dpm( $node, $node->title);

	$np = array();
	$field_list = array( 'field_range_units', 'field_uom_units', 'field_charge_collection', 'field_price');
	foreach( $node->field_ref_domestic_ratinggroup['und'] as $rg_nid) {
		$rg = node_load( $rg_nid['nid']);
		if ( empty( $rg)) continue;
		//dpm( $rg, $rg->title);

		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'basicrate_domestic')
			->fieldCondition( 'field_ref_tariffplan', 'nid', $tariffplan_nid)
			->fieldCondition( 'field_rating_group', 'value', $rg->field_rating_group['und'][0]['value'])
			->execute();

		if ( count( $result) > 0) {
			$map = array();
			foreach( array_keys( $result['node']) as $rate_nid) {
				$basicrate = node_load( $rate_nid);
				if ( ! isset( $basicrate->field_ref_rate['und'][0]['nid'])) continue;

				list( $timefactor, $rate_value) = _ocs_report_get_rate_value( $basicrate);

				$map[ $timefactor] = $rate_value;
			}
			ksort( $map);
			$np[json_encode( $map)][] = $rg_nid['nid'];
		}
	}

	//dpm( $np, 'map');

	$field_list = array( 'field_ref_carrier_mobile', 'field_is_samezone', 'field_area_code_of_the_callee', 'field_is_video_', 'field_rating_group');
	return _ocs_report_carrier_rating( $np, $field_list);
}

/*
function __a()
{
	$rows = array();
	$rg_field = null;
	$rg_header = array();
	foreach( $np as $key => $rg_list) {
		$rg_output = '';
		$rg_rows = array();
		foreach( $rg_list as $rg_nid) {
			$rg = node_load( $rg_nid);
			if ( $rg_field == null) {
				$rg_field = field_info_instances( 'node', $rg->type);
				//dpm( $rg_field, 'rg field');
			}

			$rg_rows[] = _ocs_report_get_selected_fields_list( $rg, $field_list);
		}

		if ( empty( $rg_header )) {
			foreach( $field_list as $name) {
				$rg_header[] = $rg_field[$name]['label'];
			}
		}

		// set rate 
		//
		$rate_key = json_decode( $key, TRUE);
		$rate_field = null;
		$rate_rows = array();
		foreach( $rate_key as $key => $rate) {
			$node = node_load( $rate['nid']);
			if ( $rate_field == null) $rate_field = field_info_instances( 'node', $node->type);
			$rate_rows[] = array( 'data' => $key);
			$rate_rows[] = array( 'data' => _ocs_report_get_fields( $rate_field, $node));
		}
		if ( empty( $rate_rows)) {
			$rate_rows = array( 'data' => 'No rate is defined');
		}

		$rows[] = array( theme( 'table', array( 'header' => $rg_header, 'rows' => $rg_rows)), 
				theme('item_list', array( 'items' => $rate_rows)));
	}

	$output .= theme( 'table', array( 'rows' => $rows, 'header' => array( 'Carriers and Rating Group', 'Rate')));

	return $output;

}
*/


function _ocs_report_get_rate_value( $basicrate)
{
	$rate = node_load( $basicrate->field_ref_rate['und'][0]['nid']);

	$timefactor = node_load( $basicrate->field_ref_timetablefactors['und'][0]['nid']);

	// get charge collection
	$rate_value = $rate->nid . ',' . ( isset($rate->field_range_units['und'][0]['tid']) ? $rate->field_range_units['und'][0]['tid'] : ' ') . ',' . 
		( isset($rate->field_uom_units['und'][0]['tid']) ? $rate->field_uom_units['und'][0]['tid'] : ' ') . ',' .
		( isset($rate->field_price['und'][0]['value']) ? $rate->field_price['und'][0]['value'] : ' ') ;

	if ( isset( $rate->field_charge_collection['und'])) {
		foreach( $rate->field_charge_collection['und'] as $charge) {
			$charge_node = entity_load_single( 'field_collection_item', $charge['value']);
			foreach( array( 'field_range_start', 'field_range_end', 'field_uom_amount', 'field_price_amount_float') as $f) {
				$v = $charge_node->$f;
				$rate_value .= (isset($v['und'][0]['value']) ? $v['und'][0]['value'] : ' ' ) . ',';
			}
		}
	}

	return array( $timefactor->title, $rate_value);
}

function _ocs_report_tariff_mapping( $nid)
{
	$output = '';

	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'basicrate_domestic')
		->fieldCondition( 'field_ref_tariffplan', 'nid', $nid)
		->execute();

	if ( count( $result) > 0) {
		$map = array();
		foreach( array_keys( $result['node']) as $rate_nid) {
			$rate = node_load( $rate_nid);
			$timefactor = node_load( $rate->field_ref_timetablefactors['und'][0]['nid']);
			$map[ $rate->field_rating_group['und'][0]['value']][ $timefactor->title] = $rate->field_ref_rate['und'][0]['nid'];
		}

		$items = array();
		foreach( $map as $rating_group => $rate_list) {
			$items[] = array( 'data' => $rating_group);
			$items[] = array( 'data' => _ocs_report_time_rate( $rate_list));
		}
		$output .= theme( 'item_list', array( 'items' => $items));
	}

	return $output;

}

function ocs_report_time_rate( $type, $rating_group, $tariffplan_nid)
{
	$output = '';

	$node = node_load( $rating_group);
	//dpm( $node, 'rating group');

	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'basicrate_domestic')
		->fieldCondition( 'field_ref_tariffplan', 'nid', $tariffplan_nid)
		->fieldCondition( 'field_rating_group', 'value', $node->field_rating_group['und'][0]['value'])
		->execute();

	//dpm( $rating_group_nid, 'rating group');

	if ( count( $result) > 0) {
		$map = array();
		foreach( array_keys( $result['node']) as $rate_nid) {
			$rate = node_load( $rate_nid);
			$timefactor = node_load( $rate->field_ref_timetablefactors['und'][0]['nid']);
			$map[ $timefactor->title] = $rate->field_ref_rate['und'][0]['nid'];
		}

		if ( ! empty( $map)) {
			$output .= _ocs_report_time_rate( $map);
			//dpm( $map, 'map');
		}
	}

	return $output;
}

function _ocs_report_time_rate( $rate_list)
{
	$output = '';
	$rate_items = array();
	foreach( $rate_list as $time => $rate) {
		if ( ! empty( $rate))  {
//					$rate_items[] = array( 'data' => t( '<div class="myform report"><label>%label</label><div class="myform report value">%value</div></div>',
//								array( '%label' => $time, '%value' => _ocs_report_rate($rate))));
			$node = node_load( $rate);
			$field = field_info_instances( 'node', $node->type);
			$rate_items[] = array( 'data' => t( '<h4>%label</h4>', array( '%label' => $time)));
			$rate_items[] = array( 'data' =>  _ocs_report_get_fields( $field, $node));
		}
	}
	if ( ! empty( $rate_items)) {
		$output .= theme( 'item_list', array( 'items' => $rate_items));
	}
	return $output;
}

function _ocs_report_timetable_table( $nid)
{
	$timetable = array();
	$node = node_load( $nid);
	foreach( $node->field_ref_timetablefactors['und'] as $factor) {
		$factor = node_load( $factor['nid']);
		foreach( $factor->field_ref_timetablefactorsslot['und'] as $slot) {
			$slot = node_load( $slot['nid']);
			$timetable[$slot->field_day_of_week['und'][0]['value']][$slot->field_hour_slot['und'][0]['value']] = $factor->title;
		}
	}

	$rows = array();
	for( $time=0; $time < 24; $time++) {
		$rec = array();
		$rec[] = array( 'data' => $time);
		for( $day=0; $day < 8; $day++) {
			$rec[] = array( 'data' => $timetable[$day][$time]);
		}
		$rows[] = $rec;
	}
	$header = array( 'time', 'Holiday', 'Mon', 'Tue', 'Wed', 'Thr', 'Fri', 'Sat', 'Sun');
	return theme( 'table', array( 'header' => $header, 'rows' => $rows));

//	dpm( $timetable,'timetable');
}

function _ocs_report_timetable( $nid)
{
	$timetable = array();
	$node = node_load( $nid);
	foreach( $node->field_ref_timetablefactors['und'] as $factor) {
		$factor = node_load( $factor['nid']);
		foreach( $factor->field_ref_timetablefactorsslot['und'] as $slot) {
			$slot = node_load( $slot['nid']);
			$timetable[$factor->title][$slot->field_day_of_week['und'][0]['value']][] = $slot->field_hour_slot['und'][0]['value'];
		}
	}

	$header = array( 'Holiday', 'Mon', 'Tue', 'Wed', 'Thr', 'Fri', 'Sat', 'Sun');
	$rows = array();
	foreach( $timetable as $key => $time_list) {
		$slot_list = array();
		foreach( $time_list as $day => $timeslot) {
			sort( $timeslot);
			$idx = 0;
			$str = array( 'From '. $timeslot[0]);
			for( $i=0; $i < count($timeslot)-1; $i++) {
				if ( ($timeslot[$i] +1) != $timeslot[$i+1]) {
					$str[$idx++] .= ' to '. ($timeslot[$i]+1);
					$str[$idx] = 'From '. $timeslot[$i+1];
				}
			}
			$str[$idx] .= ' to '. ($timeslot[$i]+1);
			$slot_list[implode(', ', $str)][] = $header[$day];
		}

		$idx = 0;
		foreach( $slot_list as $slot => $day) {
			if ( $idx ++ == 0) 
				$rows[] = array( array( 'data' => $key, 'rowspan' => count($slot_list)), implode( ', ', $day), $slot);
			else
				$rows[] = array( implode( ', ', $day), $slot);
		}
	}

	return theme( 'table', array( 'rows' => $rows, 'header' => array('Timeband', 'Weekdays', 'Time Slots')));
}

function _ocs_report_field_cmp( $a, $b) 
{
	return $a['widget']['weight'] - $b['widget']['weight'];
}

function _ocs_report_get_fields( $field, $node)
{
	//dpm( $node, $node->title);

	$output = '';

	// sort field by weight
	usort( $field, "_ocs_report_field_cmp");

	$items = array();
	foreach( $field as $value) {
		//dpm( $value, $value['field_name']);

		if ( $value['field_name'] == 'field_ref_tree_tid' ||
			$value['field_name'] == 'field_weight' ||
			$value['field_name'] == 'field_tree_child_voca_name' )
			continue;

		$v = $node->$value['field_name'];
		$label = $value['label'];

		$value_str = '';
		if ( isset( $v['und']) && isset( $value['display']['default']['module']) && $value['display']['default']['module'] == 'field_collection') {
			$field_info = field_info_instances('field_collection_item', $value['field_name']);
			//dpm( $field_info, $value['field_name']);
			$field_table = array();
			foreach( $v['und'] as $field_collection) {
				$field_node = entity_load_single( 'field_collection_item', $field_collection['value']);
				//dpm( $field_node, 'field node');
				$field_value = array();
				foreach( $field_info as $info) {
					$v1 = $field_node->$info['field_name'];
					$field_value[$info['label']] = isset( $v1['und'][0]['value']) ? $v1['und'][0]['value'] : NULL ;
				}
				$field_table[] = $field_value;
			}

			$items[] = array(
					'data' => theme( 'table', array( 'header' => array_keys( $field_value), 'rows' => $field_table)),
			);
		}
		else {
			if ( isset( $v['und'][0]['value'])) {
				$value_str = $v['und'][0]['value'];
			}
			else if ( isset( $v['und'][0]['nid'])) {
				$field_node = node_load( $v['und'][0]['nid']);
				$value_str = $field_node->title;
			}
			else if ( isset( $v['und'][0]['tid'])) {
				$term = taxonomy_term_load( $v['und'][0]['tid']);
				$value_str = $term->name;
			}
			else {
				continue;
			}

			$items[] = array(
				'data' => t( '<div class="myform report"><label>%label</label><div class="myform report value">%value</div></div>', 
					array( '%key' => $value['field_name'], '%label' => $label, '%value' => $value_str)),
			);
		}
	}
	$output .= theme( 'item_list', array( 'items' => $items));

	return $output;
}

function _ocs_report_get_selected_fields_list( $node, $select_list, $load_value = FALSE)
{
	$list = array();

	foreach( $select_list as $field_name) {
		$v = $node->$field_name;

		$value = array();
		if ( isset( $v['und'])) {
			foreach( $v['und'] as $v1) {
				if ( isset( $v1['value'])) {
					$value[] = $v1['value'];
				}
				else if ( isset( $v1['nid'])) {
					if ( $load_value) {
						$field_node = node_load( $v1['nid']);
						$value[] = $field_node->title;
					}
					else {
						$value[] = $v1['nid'];
					}
				}
				else if ( isset( $v1['tid'])) {
					if ( $load_value) {
						$term = taxonomy_term_load( $v1['tid']);
						$value[] = $term->name;
					}
					else {
						$value[] = $v1['tid'];
					}
				}
			}
		}

		$list[] = implode( ',', $value);
	}

	return $list;
}
