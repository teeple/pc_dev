<?php
require_once( 'script_common.inc');

// check argument
$id = NULL;
$id = drush_shift();

if ( $id == NULL) {
	printf( "Usage: <voucher id>\n");
	return;
}

if ( $id == 'all') {
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'vouchercardtype')
		->execute();

	if ( empty( $result)) {
		printf("No vouchers are found\n");
	}
	else {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			printf( "Remove voucher : %s\n", $node->title);
			rm_voucher( $node->field_voucher_id['und'][0]['value']);
		}
	}
}
else {
	printf( "Remove voucher : %s\n", $id);
	rm_voucher( $id);
}

function rm_voucher( $id)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'vouchercardtype')
		->fieldCondition('field_voucher_id', 'value', $id)
		->execute();

	if ( empty( $result)) {
		printf("Voucher not found id=%s\n", $id);
		return;
	}
	else {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			printf("Remove voucher title=%s\n", $node->title);
			node_delete( $nid);

			// remove treenodecounterforvoucher
			delete_voucher_attr( 'treenodecounterforvoucher', 'field_ref_vouchercardtype', $nid);
			delete_voucher_attr( 'loyaltypoint', 'field_ref_vouchercardtype', $nid);
			delete_voucher_attr( 'treenodeproductforvoucher', 'field_ref_vouchercardtype', $nid);
		}
	}
}	

function delete_voucher_attr( $type, $ref_field, $nid)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->fieldCondition( $ref_field, 'nid', $nid)
		->execute();

	if ( empty( $result)) {
		printf("  No %s are attached to the voucher\n", $type);
		return;
	}

	foreach( array_keys( $result['node']) as $nid) {
		$node = node_load( $nid);
		printf("  Delete %s '%s' attached to the voucher\n", $type, $node->title);
		node_delete( $nid);

		if ( $type == 'treenodeproductforvoucher') {
			delete_voucher_attr( 'treenodecounterforvoucherprd', 'field_ref_treenodeproductforvouc', $nid);
		}
	}
}
