<?php
global $nl;
$nl = '
';

while( $args[] = drush_shift());

print_r( $args);

if ( count( $args) < 2) {
	print 'Usage: drush php-script numbering_plan.inc <options> <arg>'. $nl . $nl;
	print '  <options>'. $nl;
	print '  list : list '. $nl;
	print '  del : delete'. $nl;
}
else {
	switch ( $args[1]) {
	case 'list' : 
		_list_numbering_plan( $args[2]);
		break;
	case 'del' : 
		_delete_numbering_plan( $args[2]);
		break;
	case 'list-tariffplan':
		_list_tariff_plan( $args[2]);
		break;
	default:
		print 'Unknown option: ' . $args[1]. $nl;
	}
}


function _load_by_title( $type, $title)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->propertyCondition( 'title', $title)
		->execute();

	if ( count( $result) > 0) {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			return $node;
		}
	}

	return NULL;
}

function _list_numbering_plan( $title) 
{
	global $nl;

	$np = _load_by_title( 'numberingplan_idd', $title);
	if ( empty( $np)) {
		print 'Numbering plan not found : '. $title . $nl;
		return;
	}

	//find idd_ratinggroup nodes
	if(!empty($np->field_ref_idd_ratinggroup)){
		foreach($np->field_ref_idd_ratinggroup['und'] as $child){
			$node = node_load( $child['nid']);
			print 'rating group :' .$node->title . '  ' . $node->field_rating_group['und'][0]['value'] . $nl;
		}
	}

}

function _list_tariff_plan( $title)
{
	global $nl;

	$np = _load_by_title( 'tariffplan', $title);
	if ( empty( $np)) {
		print 'Tariff plan not found : '. $title . $nl;
		return;
	}

	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'basicrate_idd')
		->fieldCondition('field_ref_tariffplan', 'nid', $np->nid)
		->execute();

	if ( count( $result) > 0) {
		foreach( array_keys( $result['node']) as $nid) {
			$basicrate = node_load( $nid);
			print 'basic rate :' . $basicrate->title . ' rg=' . $basicrate->field_rating_group['und'][0]['value'] . $nl;
		}
	}
}

/*
list all numbering plan
*/
function _delete_numbering_plan( $title)
{
	global $nl;

	$np = _load_by_title( 'numberingplan_idd', $title);
	if ( empty( $np)) {
		print 'Numbering plan not found : '. $title . $nl;
		return;
	}

	//find idd_ratinggroup nodes
	if(!empty($np->field_ref_idd_ratinggroup)){
		foreach($np->field_ref_idd_ratinggroup['und'] as $child){
			$node = node_load( $child['nid']);
			print 'remove child node title:' .$node->title . ' nid:'. $child['nid'] . $nl;
			node_delete( $child['nid']);
		}
	}

	print 'remove numbering plan node:' . $title . ' nid:'.$np->nid . $nl;
	node_delete( $nid);
}


