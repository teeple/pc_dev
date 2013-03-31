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
		}
	}


	return $output;
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

		if ( $value['field_name'] == 'field_ref_tree_tid')
			continue;

		$v = $node->$value['field_name'];
		$label = $value['label'];

		$value_str = '';
		if ( isset( $value['display']['default']['module']) && $value['display']['default']['module'] == 'field_collection') {
			foreach( $v['und'] as $field_collection) {
				$field_node = entity_load_single( 'field_collection_item', $field_collection['value']);
				$items[] = array(
					'data' => _ocs_report_get_fields( field_info_instances('field_collection_item', $value['field_name']), $field_node),
				);
			}
		}
		else {
			if ( isset( $v['und'][0]['value'])) {
				$value_str = $v['und'][0]['value'];
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
