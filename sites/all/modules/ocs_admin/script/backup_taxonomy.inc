<?php

// check argument
$fname = NULL;
$fname = drush_shift();
$taxonomy = drush_shift();

if ( $fname == NULL) {
	printf( "Usage: <file name> [taxonomy]\n");
	return;
}

printf( "Backup to file:%s/%s\n", DRUPAL_ROOT, $fname);

// open file
$fp = fopen( $fname, 'w+');
if ( $fp === FALSE) {
	printf( "Fail to write file %s\n", $fname);
	return;
}


$entity_list = array(
	'field_default_fieldset',
	'field_qtabs_click',
	'field_qtabs_click_arguments',
	'field_qtabs_default',
	'field_qtabs_exclude',
	'field_qtabs_include',
	'field_qtabs_loading',
	'field_qtabs_right_click',
	'field_qtabs_right_click_exclude',
	'field_qtabs_right_click_include',
	);

foreach( $entity_list as $type) {
	backupEntity( $fp, $type);
}


backupTaxonomy( $fp);

fclose($fp);

printf( "Backup file is created at %s/%s\n", DRUPAL_ROOT, $fname);

function backupTaxonomy( $fp)
{
	// backup taxonomy
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'taxonomy_term');
	$result = $query->execute();

	printf( "\nBackup Taxonomy\n");
	$voca = array();
	foreach( array_keys( $result['taxonomy_term']) as $tid) {
		$p = taxonomy_term_load( $tid);
		$voca[ $p->vocabulary_machine_name][$p->tid] = $p;
	}
	fprintf( $fp, "# taxonomy\n");
	fprintf( $fp, "%s\n", serialize( $voca));
}

function backupEntity( $fp, $type)
{
	printf("\nBackup field_collection_item type %s\n", $type);

	fprintf( $fp, "# field_collection_item:0:%s\n", $type);
	fprintf( $fp, "%s\n", serialize("begin"));

	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'field_collection_item', '=')
		->propertyCondition( 'field_name', $type);

	$result = $query->execute();

	$idx = 0;
	if ( !empty( $result)) {

		foreach( array_keys( $result['field_collection_item']) as $nid) {
			$node = entity_load_single( 'field_collection_item', $nid);

			printf( "  %s : %s\n", $type, $node->item_id);
			fprintf( $fp, "# field_collection_item:%d:%s\n", $nid, $type);
			fprintf( $fp, "%s\n", serialize( $node));

		$idx ++;
		}
	}

	fprintf( $fp, "# field_collection_item:0:%s\n", $type);
	fprintf( $fp, "%s\n", serialize("end"));

	printf("field_collection_item type:%s backuped entities:%d\n", $type, $idx);
}

