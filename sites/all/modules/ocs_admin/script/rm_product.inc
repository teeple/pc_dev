<?php
require_once( 'script_common.inc');

// check argument
$prd_id = NULL;
$prd_id = drush_shift();
/*
while( $arg = drush_shift()) {
	if ( $arg == 'f') 
}
*/

if ( $prd_id == NULL) {
	printf( "Usage: <product id>\n");
	return;
}

printf( "Remove product : %s\n", $prd_id);

rm_product( $prd_id);

