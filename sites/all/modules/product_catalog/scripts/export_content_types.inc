<?php

function _export_data($entity_name = NULL, $bundle_name = NULL) {
	$export_data = array();
	$export_data['entity_name'] = 'user';
	$export_data['bundle_name'] = 'user';
	$instances = field_info_instances($export_data['entity_name'], $export_data['bundle_name']);

	dsm($instances, 'instances');

	foreach ($instances as $field_name => $field) {
		$export_data['data'][] = array(
			'field' => field_info_field($field_name),
			'instance' => field_info_instance($export_data['entity_name'], $field_name, $export_data['bundle_name']),
		);
	}
	// dsm($export_data, 'export_data');

	return $export_data;
}
?>
