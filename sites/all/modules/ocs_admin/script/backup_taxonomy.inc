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


// find the product
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'taxonomy_term');

if ( ! empty( $taxonomy)) {
	$vid = taxonomy_vocabulary_machine_name_load( $taxonomy);
	$query->propertyCondition('vid', $vid->vid);
}

$result = $query->execute();

$idx = 0;
$voca = array();
foreach( array_keys( $result['taxonomy_term']) as $tid) {
	$p = taxonomy_term_load( $tid);
	$voca[ $p->vocabulary_machine_name][$p->tid] = $p;
}
fwrite( $fp, serialize( $voca));

fclose($fp);

printf( "Backup file is created at %s/%s\n", DRUPAL_ROOT, $fname);
