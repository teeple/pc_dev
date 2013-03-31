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
	dpm( $tree_info, 'tree info');

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
			else if ( $node['attr']['rel'] == 'voice_tariffplan_domestic') {
				$output .= _ocs_report_tariffplan( $id[2]);
			}
		}
	}


	return $output;
}

function _ocs_report_tariffplan( $tariffplanNid)
{
	$output = '';
	$node = node_load( $tariffplanNid);
	dpm( $node, $node->title);
	$field = field_info_instances( 'node', $node->type);
	$output .= _ocs_report_get_fields( $field, $node);

	if ( isset($node->field_ref_numberingplan_domestic['und'][0]['nid'])) {
		// list tariff plan
		$view = views_get_view('list_numberingplan_domestic_ratinggroup');
		$view->set_display('panel_displayall');
		$view->set_arguments(array( $node->field_ref_numberingplan_domestic['und'][0]['nid'], $tariffplanNid));
		$output .= $view->render();

		// list time table
		$output .= _ocs_report_timetable( $node->field_ref_timetable_domestic['und'][0]['nid']);

		// list tariff
		//$output .= _ocs_report_tariff_mapping( $tariffplanNid);
	}
	return $output;
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

function _ocs_report_timetable( $nid)
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
		if ( isset( $value['display']['default']['module']) && $value['display']['default']['module'] == 'field_collection') {
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
