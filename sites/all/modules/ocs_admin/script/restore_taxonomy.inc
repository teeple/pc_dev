<?php
require( 'script_common.inc');

global $buffer, $line;
global $update_flag;
global $src_node;

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

// check argument
$fname = NULL;
$update_flag = FALSE;
while( $arg = drush_shift()) {
	if ( $arg == 'file') $fname = drush_shift();
	if ( $arg == 'update') $update_flag = TRUE;
}

if ( $fname == NULL) {
	printf( "Usage: [update] [file <file name>]\n");
	return;
}

if ( substr( $fname, 0, 1) != '/') {
    printf("Input absolute directory address for file name: %s\n", $fname);
    return;
}

printf( "Restore from file %s\n", $fname);

// open file
$fp = fopen( $fname, 'r');
if ( $fp === FALSE) {
	printf( "Fail to read file %s\n", $fname);
	return;
}

$src_term = read_taxonomy( $fp);
$src_node = read_node( $fp);

// read all the taxonomy
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'taxonomy_term');
$result = $query->execute();

$idx = 0;
$taxonomy = array_combine(array_keys( $result['taxonomy_term']), array_keys( $result['taxonomy_term']) ); 

/*

$buf = fgets( $fp);
fclose( $fp);

$src_taxo = unserialize( $buf);
*/

// get this system's usage target domain
$domain_tid = ocs_get_terms_tid('usagetargetdomain');
$usage_target_domain = array_flip( $domain_tid);

// get saved 'usage target domain'
$src_usage_target_domain = array();
foreach( $src_term['usagetargetdomain'] as $tid => $obj) {
    $src_usage_target_domain[$tid] = $obj->name;
}
print_r( $usage_target_domain);
print_r( $src_usage_target_domain);

foreach( $src_term as $key => $term_list) {
	printf( "Check %s\n", $key);

    if( $key == 'reverse') continue;

	$terms = ocs_get_terms( $key);
<<<<<<< HEAD
=======
	if ( empty( $terms)) {
		printf("\n>> FATAL ERROR : vocabulary not found : %s\n", $key);
		continue;
	}

>>>>>>> 7ebcc2a15d9a5e6fd5bf227c050e92f97a154ed0
    $taxo_field = field_info_instances( 'taxonomy_term', $key);

    // build index
    $index = array();
    foreach( $terms as $tid => $term) {
        $target_domain = (isset($term->field_ref_usage_target_domain['und'])) ? $usage_target_domain[$term->field_ref_usage_target_domain['und'][0]['tid']] : '';
        $rel_type = (isset($term->field_rel_type['und'])) ? $term->field_rel_type['und'][0]['value'] : '';
        $name = $target_domain . ':' . $rel_type . ':' . $term->name;
        $index[$name][] = $term;
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
                $t = clone $obj;
                unset($t->tid);

                foreach( $taxo_field as $field_name => $info) {
                    if ( $info['display']['default']['module'] == 'field_collection' && isset($obj->{$field_name}['und'])) {
                        $id = $obj->{$field_name}['und'][0]['value'];
                        if ( isset( $src_node[$field_name][$id])) {
                            unset( $t->{$field_name}['und']);
                            $org = $src_node[$field_name][$id];

                            $field_info = field_info_instances( 'field_collection_item', $field_name);
                            $p = entity_create('field_collection_item', array('field_name' => $field_name));
                            $p->setHostEntity( 'taxonomy_term', $t);
                            foreach( array_keys( $field_info) as $key) {
                                $p->$key = $org->$key;
                            }
                            $p->save();
                            printf("  add field %s\n", $field_name);
                        }
                        else {
                            printf( "  field %s not found. value=%d\n", $field_name, $id);
                        }
                    }
                }
<<<<<<< HEAD
=======
				if ( isset( $t->field_ref_usage_target_domain)) {
					$t->field_ref_usage_target_domain['und'][0]['tid'] = $domain_tid[$target_domain];
				}

>>>>>>> 7ebcc2a15d9a5e6fd5bf227c050e92f97a154ed0
                $result = taxonomy_term_save( $t);
                printf( "--> %s new term: voca=%s name=%s new tid=%d\n", ($result == SAVED_NEW) ? "Saved" : ($result == SAVED_UPDATED) ? "Updated" : "Failed", $key, $name, $t->tid);
            }
        }
        else {
<<<<<<< HEAD
            $tid = $index[$name][0];
            if ( $tid != $obj->tid) {
                printf( ">> Term mismatch voca=%s name=%s src=%d this=%d\n", $key, $name, $obj->tid, $tid);
            }

=======
            $t = $index[$name][0];
			$diff = _compare_content( $taxo_field, $obj, $t);
			if ( !empty( $diff) || $t->tid != $obj->tid) {
                printf( ">> Term mismatch voca=%s name=%s src=%d this=%d\n", $key, $name, $obj->tid, $t->tid);
				foreach( $diff as $label => $attr) {
					if ( ! isset( $ignore_list[$attr[2]])) {
						printf("  %s (%s)\n", $label, $attr[2]);
						printf("    src  : '%s'\n", json_encode( $attr[0], TRUE));
						printf("    this : '%s'\n", json_encode( $attr[1], TRUE));
					}
				}
			}

					/*
>>>>>>> 7ebcc2a15d9a5e6fd5bf227c050e92f97a154ed0
            if ( $update_flag) {
                $t = taxonomy_term_load( $tid);
                foreach( $taxo_field as $field_name => $info) {
                    $t->$field_name = $obj->$field_name;

                    if ( $info['display']['default']['module'] == 'field_collection' && isset($obj->{$field_name}['und'])) {
                        $id = $obj->{$field_name}['und'][0]['value'];
                        if ( isset( $src_node[$field_name][$id])) {
                            $org = $src_node[$field_name][$id];

                            $field_info = field_info_instances( 'field_collection_item', $field_name);
                            $p = entity_load_single( 'field_collection_item', $t->{$field_name}['und'][0]['value']);
                            foreach( array_keys( $field_info) as $key) {
                                $p->$key = $org->$key;
                            }
                            $p->save();
                            printf("  update field %s\n", $field_name);
                        }
                        else {
                            printf( "  field %s not found. value=%d\n", $field_name, $id);
                        }
                    }
                }
                $result = taxonomy_term_save( $t);
                printf( "--> %s update term: voca=%s name=%s new tid=%d\n", ($result == SAVED_NEW) ? "Saved" : ($result == SAVED_UPDATED) ? "Updated" : "Failed", $key, $name, $t->tid);
            }
<<<<<<< HEAD

        
            if ( count( $index[$name]) > 1) {
                printf(">> ERROR : Multiple name defined name=%s %s\n", $name, print_r( $index[$name], TRUE));
=======
			*/

            if ( count( $index[$name]) > 1) {
                printf(">> ERROR : Multiple name defined name=%s %s\n", $name, json_encode( $index[$name]));
				/*
>>>>>>> 7ebcc2a15d9a5e6fd5bf227c050e92f97a154ed0
                if ( $update_flag) {
                    for( $i=1; $i < count($index[$name]); $i++) {
                        taxonomy_term_delete( $index[$name][$i]);
                        printf("  delete term tid=%d\n", $index[$name][$i]);
                    }
                }
<<<<<<< HEAD

                return;
=======
				*/

>>>>>>> 7ebcc2a15d9a5e6fd5bf227c050e92f97a154ed0
            }

            unset( $index[$name]);
		}
	}

	if ( ! empty( $index)) {
		foreach( $index as $name => $t) {
			printf( ">> WARNING : New term defined in this system voca=%s name=%s tid=%d\n", $key, $name, $t->tid);
		}
	}
}

function read_taxonomy( $fp)
{
    $src_term = array();

    rewind( $fp);
    while( ($data = get_content($fp)) !== NULL) {
        list( $type, $id, $subtype) = explode( ':', $data[0]);
	//printf( ">> %s %s:%s\n", $data[0], $type, $subtype);

        $obj = unserialize( $data[1]);

        if ( $type == 'taxonomy') {
            $src_term = $obj;

            $index = array();
            foreach( $src_term as $key => $terms) {
                foreach( $terms as $tid => $term) {
                    $index[$tid] = array( 'voca' => $term->vocabulary_machine_name, 'name' => get_taxo_term_name( $term));
                }
            }
            $src_term['reverse'] = $index;
            break;
        }
    } 

    return $src_term;
}

function read_node( $fp)
{
    $src_node = array();

    $child = array();
    rewind( $fp);
    while( ($data = get_content($fp)) !== NULL) {
        list( $type, $id, $subtype) = explode( ':', $data[0]);
//	printf( ">> %s %s:%s\n", $data[0], $type, $subtype);

        $obj = unserialize( $data[1]);
        if ( $obj == 'begin' || $obj == 'end') continue;

		if ( $type == 'field_collection_item') {
            $src_node[$subtype][$id] = $obj;
		}
    }

    return $src_node;
}

function get_content( $fp)
{
	global $buffer, $line;

	if ( empty( $buffer)) {
		$header = fgets( $fp);		// read one more line
		$line ++;
	}
	else {
		$header = $buffer;
	}

	if ( empty( $header)) return NULL;
	if ( substr( $header, 0, 2) !== '# ') {
		printf( "Invalid file format at line %d : %s", $line, $header);
		return NULL;
	}

	$obj = '';
	while( $buffer = fgets( $fp)) {
		$line ++;
		if ( substr( $buffer, 0, 2) == '# ') {
			break;
		}
		$obj .= $buffer;
	}

	return array( substr( $header, 2, strlen( $header)-3), $obj);
}

function check_diff( $update_flag, $field, $src, $node)
{
	$ignore_list = array( 
			'field_ref_product' => TRUE,
			'field_weight' => TRUE);

    $diff = _compare_content( $field, $src, $node);
    if ( !empty( $diff)) {
        foreach( $diff as $label => $attr) {
			if ( ! isset( $ignore_list[$attr[2]])) {
				printf("  %s (%s)\n", $label, $attr[2]);
				printf("    src  : '%s'\n", json_encode( $attr[0], TRUE));
				printf("    this : '%s'\n", json_encode( $attr[1], TRUE));
				if ( $update_flag && !empty($attr[0])) {
					printf( "  >>> Update %s: '%s'=>'%s'\n", 
							$attr[2], json_encode( $node->$attr[2], TRUE), 
							json_encode( $src->$attr[2], TRUE));
					$node->$attr[2] = $src->$attr[2];
				}
			}
        }
        if ( $update_flag) node_save( $node);
    }
<<<<<<< HEAD
=======
	return $diff;
>>>>>>> 7ebcc2a15d9a5e6fd5bf227c050e92f97a154ed0
}
