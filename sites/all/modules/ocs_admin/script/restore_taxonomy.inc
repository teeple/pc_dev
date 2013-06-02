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

if ( substr( $fname, 0, 1) != '/') {
    printf("Input absolute directory address for file name: %s\n", $fname);
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

$src_taxo = unserialize( $buf);

// get this system's usage target domain
$usage_target_domain = array_flip( ocs_get_terms_tid('usagetargetdomain'));

// get saved 'usage target domain'
$src_usage_target_domain = array();
foreach( $src_taxo['usagetargetdomain'] as $tid => $obj) {
    $src_usage_target_domain[$tid] = $obj->name;
}
//print_r( $src_usage_target_domain);

foreach( $src_taxo as $key => $term_list) {
	println( 'Check ' . $key);

	$terms = ocs_get_terms( $key);

    // build index
    $index = array();
    foreach( $terms as $tid => $term) {
        $target_domain = (isset($term->field_ref_usage_target_domain['und'])) ? $usage_target_domain[$term->field_ref_usage_target_domain['und'][0]['tid']] : '';
        $rel_type = (isset($term->field_rel_type['und'])) ? $term->field_rel_type['und'][0]['value'] : '';
        $name = $target_domain . ':' . $rel_type . ':' . $term->name;
        $index[$name][] = $tid;
        /*
        if (isset($term->field_ref_usage_target_domain['und'])) {
            printf(">>>> %s %s\n", $term->field_ref_usage_target_domain['und'][0]['tid'], $name);
            print_r( $term);
        }
        */
    }

	foreach( $term_list as $tid => $obj) {
        $target_domain = (isset($obj->field_ref_usage_target_domain['und'])) ? $src_usage_target_domain[$obj->field_ref_usage_target_domain['und'][0]['tid']] : '';
        $rel_type = (isset($obj->field_rel_type['und'])) ? $obj->field_rel_type['und'][0]['value'] : '';
        $name = $target_domain . ':' . $rel_type . ':' . $obj->name;

        if ( ! isset( $index[$name])) {
			printf( ">> ERROR : Term not found voca=%s name=%s src=%d \n", $key, $name, $obj->tid);

            // add new term
            if ( $update_flag) {
                unset( $obj->tid);
                $result = taxonomy_term_save( $obj);
                printf( "--> %s new term: voca=%s name=%s new tid=%d\n", ($result == SAVED_NEW) ? "Saved" : ($result == SAVED_UPDATED) ? "Updated" : "Failed", $key, $name, $obj->tid);
            }
        }
        else {
            if ( count( $index[$name]) > 1) {
                printf(">> ERROR : Multiple name defined name=%s %s\n", $name, print_r( $index[$name], TRUE));
            }
            else {
                $tid = $index[$name][0];
                if ( $tid != $obj->tid) {
                    printf( ">> Term mismatch voca=%s name=%s src=%d this=%d\n", $key, $name, $obj->tid, $tid);
                }
                unset( $index[$name]);
            }
		}
	}

	if ( ! empty( $index)) {
		foreach( $index as $name => $tid) {
			printf( ">> WARNING : New term defined in this system voca=%s name=%s tid=%d\n", $key, $name, $tid);
		}
	}
}
