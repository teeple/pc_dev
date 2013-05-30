<?php
require( 'script_common.inc');

global $update_flag;


// check argument
$fname = NULL;
$update_flag = FALSE;
while( $arg = drush_shift()) {
	if ( $arg == 'file') $fname = drush_shift();
	if ( $arg == 'update') $update_flag = TRUE;
}

if ( $fname == NULL) {
	println( 'Usage: [update] [file <file name>]');
	return;
}

println( 'Restore from file:'. $fname);

// open file
$fp = fopen( $fname, 'r');
if ( $fp === FALSE) {
	println( 'Fail to read file '. $fname);
	return;
}

$buf = fgets( $fp);
fclose( $fp);

$voca = unserialize( $buf);
foreach( $voca as $key => $term_list) {
	println( 'Check ' . $key);

	$term = ocs_get_terms( $key);

	foreach( $term_list as $tid => $obj) {
		$t = $term[$tid];

		if ( $t->name !== $obj->name) {
			printf( "Term mismatch voce=%s name=%s src=%d this=%d\n", $key, $obj->name, $obj->tid, $term[$obj->name]);
		}
		unset( $term[$tid]);
	}

	if ( ! empty( $term)) {
		foreach( $term as $tid => $t) {
			printf( "Term not found voce=%s name=%s this=%d\n", $key, $t->name, $t->tid);
		}
	}
}
