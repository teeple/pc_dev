<?php

require_once( 'script_common.inc');

global $update_flag;
global $buffer, $line;
global $dst_term, $src_term;
global $tid_field_list;
global $reset_flag;
global $yes_flag;


// get global variables
$reset_flag = FALSE;
$buffer = '';
$dst_term = array();
$tid_field_list = array( 'field_ref_service_feature_code' => 'featurecode');

// check argument
$fname = NULL;
$update_flag = FALSE;
$yes_flag = FALSE;
$product_id = NULL;
while( $arg = drush_shift()) {
	if ( $arg == 'file') $fname = drush_shift();
	else if ( $arg == 'update') $update_flag = TRUE;
	else if ( $arg == 'reset') $reset_flag = TRUE;
	else if ( $arg == 'yes') $yes_flag = TRUE;
	else $product_id = $arg;
}

if ( $fname == NULL) {
	printf( "Usage: [update] [reset] [yes] [file <file name>] [product_id]\n");
	return;
}

printf( "Restore from file:%s\n", $fname);

// open file
$fp = fopen( $fname, 'r');
if ( $fp === FALSE) {
	printf( "Fail to read file:%s\n", $fname);
	return;
}

$prd_field = field_info_instances( 'node', 'simpleproductoffering');

$line = 1;
$child = array();
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
	}
	else if ( $obj->type === 'simpleproductoffering') {
        if ( $reset_flag ) {
            // remove product
            rm_product( $obj->field_product_id['und'][0]['value']);
        }
        else if ( empty( $product_id) || $product_id == $obj->field_product_id['und'][0]['value']) {
            check_product( $obj, $prd_field, $child);
        }
		$child = array();
	}
	else {
		$child[$type][$id][] = $obj;
	}
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

function check_product( $p, $field, $child)
{
	global $update_flag, $yes_flag;

    $svcdomain = get_src_term_name( $p->field_service_type_of_provider['und'][0]['tid']); 
    $prdtype = get_src_term_name( $p->field_product_type['und'][0]['tid']);

	// find the product
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'simpleproductoffering')
		->propertyCondition('title', $p->title)
		->execute();

	if ( empty( $result)) {
		printf( "\nNew %s %s Product : %s id: %s\n", $svcdomain, $prdtype, $p->title, $p->field_product_id['und'][0]['value']);
		if ( $update_flag) {
            if ( check_user_confirm()) {
                add_product( $p, $child);
            }
        }
	}
	else {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			printf( "\nExisting %s %s Product : %s id: %s\n", $svcdomain, $prdtype, $p->title, $p->field_product_id['und'][0]['value']);

			$diff = _compare_content( $field, $p, $node);
			if ( !empty( $diff)) {
                foreach( $diff as $label => $attr) {
                    printf("  %s (%s)\n", $label, $attr[2]);
                    printf("    src  : '%s'\n", json_encode( $attr[0], TRUE));
                    printf("    this : '%s'\n", json_encode( $attr[1], TRUE));
                    if ( $update_flag && !empty($attr[0])) {
                        printf( "  >>> Update %s: '%s'=>'%s'\n", $attr[2], print_r( $node->$attr[2], TRUE), print_r( $p->$attr[2], TRUE));
                        $node->$attr[2] = $p->$attr[2];
                    }
                }
                if ( $update_flag) node_save( $node);
			}
		}
	}
}

function add_product( $src, $child)
{
	global $user, $src_term;

	$productNode = $src;
	$productNode->uid = $user->uid;
	_unset_unused_field_of_cloned_node($productNode);
	unset($productNode->field_weight_for_ratingpriority);
	unset($productNode->field_weight_for_hierarchy);
	node_save($productNode);

	printf( "Save product id: %s\n", $productNode->field_product_id['und'][0]['value']);

	$idx = 0;
    //print_r( $child['action']);
    $parentRefNodeList = array();
	foreach( $child['tree_tid'] as $tid => $data_list) {
        foreach( $data_list as $data) {

            $org_nid = $data->nid;

            $childNode = get_attribute( $productNode, $data);
            node_save($childNode);
            printf( "    save child(%d): nid=%d type=%s title=%s\n", $org_nid, $childNode->nid, $childNode->type, $chlidNode->title);
            $child['tree_tid'][$org_nid]['new_node'] = $childNode->nid;

            /*
            if(isset($targetChildNode->field_charge_collection)){
                _clone_field_collection('node',$targetChildNode,$childNode,'field_charge_collection');
            }
            if(isset($targetChildNode->field_discount_collection)){
                _clone_field_collection('node',$targetChildNode,$childNode,'field_discount_collection');
            }
            _clone_nested_child_node($targetChildNode,$childNode);
            */

           if ( isset($childNode->field_parent_node['und'])) {
               $parentRefNodeList[] = $childNode->nid;
           }
           else if ( isset($child['action'][$org_nid])) {
                printf("Action for %s\n", $data->title);

                foreach( $child['action'][$org_nid] as $obj) {
                    $actionSetNode = $obj;
                    $actionSetNode->uid = $user->uid;
                    $actionSetNode->field_ref_source_action['und'][0]['nid'] = $childNode->nid;
                    _unset_unused_field_of_cloned_node($actionSetNode);
                    node_save($actionSetNode);

                    printf( "        save action: nid=%d type=%s:%s title=%s\n", $childSetNode->nid, $childNode->type, $actionSetNode->type, $actionSetNode->title);
                }
            }
            //if ( $idx ++ == 1) break;
        }
	}

    // load parent node ptr
    foreach( $parentRefNodeList as $nid) {
        // look for parent node
        $childNode = node_load( $nid);
        $prevNid = $childNode->nid;
        $parentNid = $childNode->field_parent_node['und'][0]['nid'];
        while( $parentNodes = $child['parent'][$parentNid]) {

            if ( count( $parentNodes) > 1) {
                printf(">> ERROR : Too many parent nodes\n");
                break;
            }

            $parentNode = $parentNodes[0];
            $parentNode->uid = $user->uid;
            _unset_unused_field_of_cloned_node($parentNode);
            node_save($parentNode); 

            // modify parent node nid
            $prevNode = node_load( $prevNid);
            $prevNode->field_parent_node['und'][0]['nid'] = $parentNode->nid;
            node_save( $prevNode);

            printf( "        save parent: nid=%d type=%s:%s title=%s\n", $parentNode->nid, $parentNode->type, $parentNode->type, $parentNode->title);

            $prevNid = $parentNid;
            $parentNid = $parentNode->field_parent_node['und'][0]['nid'];
        }

        if ( isset($child['tree_tid'][$parentNid])) {
            $parentNode->field_parent_node['und'][0]['nid'] = $child['tree_tid'][$parentNid]['new_node'];
            node_save( $parentNode);
        }
        else {
            printf(">> ERROR : Node not found nid=%d\n", $parentNid);
        }
    }
}


function get_attribute( $productNode, $src)
{
	global $tid_field_list;

    //print_r( $src);

	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $src->type)
		->fieldCondition('field_ref_product', 'nid', $productNode->nid);

    $tid = 0;
	if ( isset( $src->field_ref_tree_tid['und'])) {
		$srcTid = $src->field_ref_tree_tid['und'][0]['value'];
		$tid = get_target_tid( get_src_term_voca($srcTid), $src->field_ref_tree_tid['und'][0]['value']);
		$query->fieldCondition('field_ref_tree_tid', 'value', $tid);
	}

	$result = $query->execute();

	if ( empty( $result)) {
		printf( "not found type=%s product_nid=%d tid=%d\n", $src->type, $productNode->nid, $tid);

		$p = $src;
		$p->field_ref_product['und'][0]['nid'] = $productNode->nid;
		$p->field_ref_tree_tid['und'][0]['value'] = $tid;
		_unset_unused_field_of_cloned_node($p);

		foreach( $tid_field_list as $field_name => $voca ) {
			if ( isset( $p->$field_name)) {
				$field = $p->$field_name;
				$tid = get_target_tid( $voca, $field['und'][0]['tid']);
				$p->$field_name = array( 'und' => array( 0 => array( 'tid' => $tid)));

				if ( $field['und'][0]['tid'] != $tid)
					printf( ">> WARNING: Change field %s %d=>%d\n", $field_name, $field['und'][0]['tid'], $tid);
			}
		}
	}
	else {
		$nid = array_pop( array_keys( $result['node']));
		$p = node_load( $nid);

		//printf( "found type=%s %s nid=%d \n", $type, $p->title, $p->nid);
	}
	return $p;
}

function get_target_tid( $voca, $srcTid)
{
	global $src_term, $dst_term;

    //print_r( $src_term[$voca]);

	// first get term name
    $tid = 0;
    $name = get_src_term_name( $srcTid);
	if ( ! empty( $name)) {
		if ( !isset( $dst_term[$voca])) {
            $terms = ocs_get_terms( $voca);
            foreach( $terms as $tid => $term) {
                $n = get_taxo_term_name( $term);
                $dst_term[$voca][$n] = $tid;
            }
		}

		$tid = $dst_term[$voca][$name];

		if ( $srcTid != $tid) 
			printf( ">> WARNING: term id changed %s:%d => %d\n", $name, $srcTid, $tid);
	}

	return $tid;
}

function get_src_term_name( $tid)
{
    global $src_term;

    $name = $src_term['reverse'][$tid];
    if ( empty( $name)) {
		printf(">> ERROR: term not found tid=%d\n", $tid);
        return NULL;
    }

    return $name['name'];
}

function get_src_term_voca( $tid)
{
    global $src_term;

    $name = $src_term['reverse'][$tid];
    if ( empty( $name)) {
		printf(">> ERROR: term not found tid=%d\n", $tid);
        return NULL;
    }

    return $name['voca'];
}                

function check_user_confirm()
{
    global $yes_flag;

    if ( $yes_flag == TRUE) return TRUE;

    $line = readline("> Add new product ? [Y/n/a]");
    if ( $line == 'a') {
        $yes_flag = TRUE;
        return TRUE;
    }

    if ( $line == 'n') return FALSE;
    return TRUE;
}
