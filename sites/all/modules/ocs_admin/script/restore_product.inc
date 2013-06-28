<?php

require_once( 'script_common.inc');

global $update_flag;
global $buffer, $line;
global $dst_term, $src_term;
global $update_field_list;
global $reset_flag;
global $yes_flag;
global $src_node;
global $check_this;
global $node_list;
global $fp;
global $child_info;
global $child_node;
global $nid_field_list;
global $no_title_attribute_list;    // list of attribute which has no title condition


// get global variables
$reset_flag = FALSE;
$buffer = '';
$dst_term = array();
$update_field_list = array( 
    'tid' => array( 
        'field_ref_service_feature_code' => 'featurecode', 
        'field_service_type_of_provider' => 'svcdomain',
        'field_ref_type_of_call' => 'calltype',
        'field_product_type' => 'prdtype',
        'field_billing_type' => 'billtype',
        'field_service_operator' => 'svcoperator',
        'field_customer_type' => 'custdvcd',
        'field_customer_group_type' => 'custkdcd',
        'field_price_units' => 'currency',
        'field_roaming_allowed' => 'roamingallowed',
        'field_scale' => 'scale_type',
        'field_counter_type' => 'countertype',
        'field_service_domain' => 'svcdomain',
        'field_billing_type_counter' => 'billtypecounter',
        'field_counter_unit_type' => 'counterunit',
        'field_counter_group' => 'countergroup',
        'field_default_usage_type' => 'usagetype',
        'field_ref_otherontimecharge' => 'onetimecharge',
        'field_service_permission' => 'calltype',
        'field_nonusage_permission' => 'nonusagetype',
        ),
    'nid' => array(
        'field_ref_carrier_mobile' => 'carrier_mobile',
        'field_ref_numberingplan_domestic' => 'numberingplan_domestic',
        'field_ref_numberingplan_idd' => 'numberingplan_idd',
        'field_ref_timetable_domestic' => 'timetable',
        'field_ref_tariffplan_idd_carrier' => 'tariffplan_idd_carrier',
        'field_ref_unittransfer' => 'unittransfer',
        'field_ref_counter_for_total_ut' => 'counter',
        'field_lifecycle_states' => 'ocs_account_state',
        'field_lifecycle_state' => 'ocs_account_state',
        'field_lifecycle_scheme' => 'lifecyclescheme',
        'field_ocs_message_list' => 'ocs_messages',
        'field_ocs_action' => 'ocs_actions',
        'field_ocs_transition' => 'ocs_state_machine',
        'field_ref_counter' => 'counter',
        'field_counter' => 'counter',
        'field_ref_connected_product' => 'simpleproductoffering',
        ),
    'target_id' => array(
        'field_ocs_from_state' => 'ocs_account_state',
        'field_ocs_to_state' => 'ocs_account_state',
        'field_ocs_trigger_events' => 'ocs_events',
        ),
    );

$no_title_attribute_list = array(     // list of attribute which has no title condition
    'actionpricechargerecurringdefaul' => FALSE
    );

$src_node = array();
$check_this = array();
$node_list = array();
$child_info = array(
    'numberingplan_domestic' => array( array( 
        'child_type' => 'domestic_ratinggroup', 
        'ref_field' => 'field_ref_domestic_ratinggroup',
        'rev_ref_field' => 'field_ref_numberingplan_domestic',
        )),
    'timetable' => array( array(
        'child_type' => 'timetablefactors',
        'ref_field' => 'field_ref_timetablefactors',
        )),
    'timetablefactors' => array( array(
        'child_type' => 'timetablefactorsslot',
        'ref_field' => 'field_ref_timetablefactorsslot',
        )),
    'unittransfer' => array( array(
        'child_type' => 'unittransferfactor',
        'ref_field' => 'field_ref_unittransferfactors',
        'rev_ref_field' => 'field_parent_node',
    )),
    'lifecyclescheme' => array( 
        array( 'child_type' => 'ocs_state_machine',
            'rev_ref_field' => 'field_lifecycle_scheme',),
        array( 'child_type' => 'ocs_svc_perm',
            'rev_ref_field' => 'field_lifecycle_scheme',),
        ),
    'ocs_state_machine' => array( array(
        'child_type' => 'ocs_transition_actions',
        'rev_ref_field' => 'field_ocs_transition',
        )),
);


// check argument
$fname = NULL;
$update_flag = FALSE;
$yes_flag = FALSE;
$product_id = NULL;
while( $arg = drush_shift()) {
	if ( $arg == 'file') $fname = drush_shift();
	else if ( $arg == 'update') $update_flag = TRUE;
	else if ( $arg == 'product') $product_id = drush_shift();
}

if ( $fname == NULL) {
	printf( "Usage: [file <file name>] [product <product_id>] [update]\n");
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

read_taxonomy();
read_node();

if ( $product_id) {

	foreach( $src_node['simpleproductoffering'] as $nid => $obj) {
		if ( $obj->field_product_id['und'][0]['value'] == $product_id) {
			check_node( FALSE, $obj);
			if ( $update_flag) {
				printf("\nUpdate ... \n");
				check_node( TRUE, $obj);
			}
			break;
		}
	}
}
else {
	interactive_mode();
}

return;

/* not used
if ( $reset_flag)  remove_all_node_of_specific_type( $node_list);

// read taxonomy first
read_taxonomy();

$line = 1;
$child = array();
while( ($data = get_content($fp)) !== NULL) {
	list( $type, $id, $subtype) = explode( ':', $data[0]);
	//printf( ">> %s %s:%s\n", $data[0], $type, $subtype);

	$obj = unserialize( $data[1]);
    if ( $obj == 'begin' || $obj == 'end') continue;

    if ( $type == 'node') {
        $child[$obj->type][$obj->nid] = $obj;

        check_node( FALSE, $obj);
    }
	else if ( $obj->type === 'simpleproductoffering') {
        check_node_exist_in_this( $src_node[$obj->type], $obj->type);

        if ( $reset_flag && array_search( $obj->type, $node_list) !== FALSE) {
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
*/

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
		if ( $update_flag && check_user_confirm()) {
            add_product( $p, $child);
        }
	}
	else {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			printf( "\nExisting %s %s Product : %s id: %s\n", $svcdomain, $prdtype, $p->title, $p->field_product_id['und'][0]['value']);

            check_diff( $update_flag, $field, $p, $node);
		}
	}
}

function check_diff_product( $src, $child, $productNode)
{
	global $user, $src_term;

	$idx = 0;
    //print_r( $child['action']);
    $parentRefNodeList = array();
	foreach( $child['tree_tid'] as $tid => $data_list) {
        foreach( $data_list as $data) {

            $org_nid = $data->nid;

            $childNode = get_attribute( $productNode, $data);
			if ( $childNode === NULL) continue;

			if ( isset( $childNode->nid)) {
				$field = field_info_instances( 'node', $src->type);
				check_diff( FALSE, $field, $data, $childNode);
			}

            /*
            if(isset($targetChildNode->field_charge_collection)){
                _clone_field_collection('node',$targetChildNode,$childNode,'field_charge_collection');
            }
            if(isset($targetChildNode->field_discount_collection)){
                _clone_field_collection('node',$targetChildNode,$childNode,'field_discount_collection');
            }
            _clone_nested_child_node($targetChildNode,$childNode);
            */

           if ( $childNode->type == 'tariffplan') {
           //    saveTariffPlan( $child, $org_nid);
           }
           else if ( isset($child['action'][$org_nid])) {
                printf("Action for %s\n", $data->title);

                foreach( $child['action'][$org_nid] as $obj) {
					$actionNode = get_attr_cond( $obj->type, $obj->title, array(
								array( 'field_ref_source_action', 'nid', $childNode->nid)
								));
					check_diff( FALSE, field_info_instances( 'node', $obj->type), $obj, $actionNode);
                }
            }
        }
	}

}

function get_attr_cond( $type, $title, $field_cond)
{
	// find the attribute
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type);

	if ( $field_cond) {
		foreach( $field_cond as $cond) {
			$query->fieldCondition( $cond[0], $cond[1], $cond[2]);
		}
	}
	$result = $query->execute();

	if ( empty( $result)) {
		$node = ocs_admin_get_new_node( $type);
		printf("  New attribute type=%s title=%s\n", $type, $title);
	}
	else {
		$node = node_load( array_pop( array_keys( $result['node'])));
	}

	return $node;
}


function add_product( $src, $child)
{
	global $user, $src_term;

	$productNode = clone $src;
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
			if ( $childNode === NULL) continue;

            node_save($childNode);

            printf( "    save child : org_nid=%d nid=%d type=%s title=%s\n", 
                $org_nid, $childNode->nid, $childNode->type, $childNode->title);
            $child['tree_tid'][$org_nid]['new_node'] = $childNode->nid;
        //readline("Enter to continue ...");

			if ( isset( $childNode->field_prefix_range)) {
				update_prefix_range( $childNode, 'field_prefix_range');
			}
            /*
            if(isset($targetChildNode->field_charge_collection)){
                _clone_field_collection('node',$targetChildNode,$childNode,'field_charge_collection');
            }
            if(isset($targetChildNode->field_discount_collection)){
                _clone_field_collection('node',$targetChildNode,$childNode,'field_discount_collection');
            }
            _clone_nested_child_node($targetChildNode,$childNode);
            */

           if ( $childNode->type == 'tariffplan') {
               saveTariffPlan( $child, $childNode, $org_nid);
           }
           else if ( isset($childNode->field_parent_node['und'])) {
               $parentRefNodeList[] = $childNode->nid;
           }
           else if ( isset($child['action'][$org_nid])) {
                printf("Action for %s\n", $data->title);

                foreach( $child['action'][$org_nid] as $obj) {
                    $actionSetNode = clone $obj;
                    $actionSetNode->uid = $user->uid;
                    $actionSetNode->field_ref_source_action['und'][0]['nid'] = $childNode->nid;
                    _unset_unused_field_of_cloned_node($actionSetNode);
                    node_save($actionSetNode);

                    printf( "        save action: nid=%d type=%s:%s title=%s\n", $childSetNode->nid, $childNode->type, $actionSetNode->type, $actionSetNode->title);
        //readline("Enter to continue ...");
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

            $parentNode = clone $parentNodes[0];
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

function update_prefix_range( $node, $field_name)
{
	global $src_node;

	$nids = array_get_value( $node->$field_name, FALSE);
	unset( $node->{$field_name}['und']);

	$field_info = field_info_instances('field_collection_item', $field_name);
	foreach( $nids as $nid) {
		// field_collection_item
		$p = entity_create( 'field_collection_item', array( 'field_name' => $field_name));
		$p->setHostEntity( 'node', $node);

		$org = $src_node[$field_name][$nid];
		foreach( array_keys( $field_info) as $key) {
			$p->$key = $org->$key;
		}
		$p->save();

		printf("    set idx=%d %s\n", count( $node->{$field_name}['und']), $field_name);
	}
	node_save( $node);
}


function checkField( &$child)
{
    global $src_node;

    $list = array( 
        'field_ref_numberingplan_domestic',
        'field_ref_numberingplan_idd',
        'field_ref_timetable_domestic',
        'field_ref_tariffplan_idd_carrier',
        );

    foreach( $list as $field_name) {
        $field = $child->$field_name;
        if ( isset($field['und'])) {
            $nid = $field['und'][0]['nid'];
            if ( isset( $src_node[$child->type][$nid])) {
                $src_obj = $src_node[$child->type][$nid];

                // find the node in this system
                $objs = ocs_get_nodes_by_title( $src_obj->type, $src_obj->title);
                if ( count( $objs) == 0) {
                    printf(">> ERROR : ref node of type '%s' is not found in this system. nid=%d title=%s\n", $field_name, $nid, $src_obj->title);
                }
                else if ( count( $objs) > 1) {
                    printf(">> ERROR : %d ref node of type '%s' exist in this system. nid=%d\n", count($objs), $field_name, $nid);
                }
                else {
                    $child->$field_name = array( 'und' => array( 0 => array( 'nid' => $objs[0])));
                    printf("  nid of ref field of type '%s' is changed to %d\n", $objs[0]);
                }
            }
            else {
				print_r( $src_node[$child->type]);
                printf(">> ERROR : ref field '%s' not found in the backup file. nid=%d\n", $field_name, $nid);
            }
        }
    }
}

// TODO : check numbering plan and time table
function saveTariffPlan( $child, $childNode, $org_nid)
{
    global $user, $src_node;

    $rateList = array();
    // save rate type first
    foreach( $child['tariff'] as $nid => $objs) {
       $obj = $objs[0];
       if ( $obj->type == 'rate' && $obj->field_ref_tariffplan['und'][0]['nid'] == $org_nid) {

           // save rate 
           $tariffChild = clone $obj;
           $tariffChild->uid = $user->uid;
           $tariffChild->field_ref_tariffplan['und'][0]['nid'] = $childNode->nid;
            _unset_unused_field_of_cloned_node($tariffChild);

			if ( isset($tariffChild->field_charge_collection)) {
				if ( isset( $src_node['field_charge_collection'][$tariffChild->field_charge_collection['und'][0]['value']])) {
					$field_info = field_info_instances( 'field_collection_item', 'field_charge_collection');
					$org = $src_node['field_charge_collection'][$tariffChild->field_charge_collection['und'][0]['value']];
					$p = entity_create('field_collection_item', array('field_name' => 'field_charge_collection'));
					$p->setHostEntity( 'node', $tariffChild);
					foreach( array_keys( $field_info) as $key) {
						$p->$key = $org->$key;
					}
					$p->save();
					printf("    save field_charge_collection\n");
				}
			}

            node_save($tariffChild);

           printf( "    save rate nid=%d type=%s title=%s\n", $tariffChild->nid, $tariffChild->type, $tariffChild->title);

           $rateList[$nid] = $tariffChild->nid;
       }
    }

    // save basicrate
    foreach( $child['tariff'] as $objs) {
       $obj = $objs[0];
       if ( $obj->type != 'rate' && $obj->field_ref_tariffplan['und'][0]['nid'] == $org_nid) {

           // save
           $tariffChild = clone $obj;
           $tariffChild->uid = $user->uid;
           $tariffChild->field_ref_tariffplan['und'][0]['nid'] = $childNode->nid;
           $tariffChild->field_ref_rate['und'][0]['nid'] = $rateList[$tariffChild->field_ref_rate['und'][0]['nid']];
            _unset_unused_field_of_cloned_node($tariffChild);
            node_save($tariffChild);

           printf( "    save type=%s title=%s\n", $tariffChild->type, $tariffChild->title);
       }
    }
}

function get_attribute( $productNode, $src)
{
    global $update_field_list, $no_title_attribute_list;
    //print_r( $src);

	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $src->type)
		->fieldCondition('field_ref_product', 'nid', $productNode->nid);

    if ( ! isset( $no_title_attribute_list[$src->type])) {
        $query->propertyCondition( 'title', $src->title);
    }

    $tid = 0;
	if ( isset( $src->field_ref_tree_tid['und'])) {
		$srcTid = $src->field_ref_tree_tid['und'][0]['value'];
		if ( !empty( $srcTid)) {
			$tid = get_target_tid( get_src_term_voca($srcTid), $src->field_ref_tree_tid['und'][0]['value']);
			$query->fieldCondition('field_ref_tree_tid', 'value', $tid);
		}
		else {
			printf(">> WARNING : invalid value field_ref_tree_tid\n");
		}
	}

	$result = $query->execute();

	if ( empty( $result)) {
		printf( "  attribute not found type=%s product_nid=%d tid=%d\n", $src->type, $productNode->nid, $tid);

		$p = clone $src;
		$p->field_ref_product['und'][0]['nid'] = $productNode->nid;
		$p->field_ref_tree_tid['und'][0]['value'] = $tid;
		_unset_unused_field_of_cloned_node($p);
	}
	else {
		$nid = array_pop( array_keys( $result['node']));
		$p = node_load( $nid);

		$field_info = field_info_instances( 'node', $src->type);
		foreach( array_keys( $field_info) as $key) {
			// update other fields if it's not included in the list
			if ( array_search( $key, array( 'field_ref_product', 'field_ref_tree_tid')) === FALSE) {
				$p->$key = $src->$key;
			}
		}

		printf( "  attribute found type=%s %s nid=%d \n", $p->type, $p->title, $p->nid);
	}

	if ( check_field( $p) === FALSE)
		return NULL;

	return $p;
}

function get_target_tid( $voca, $srcTid)
{
	global $src_term, $dst_term;

    //print_r( $src_term[$voca]);

	// first get term name
    $tid = NULL;
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
	else {
		printf( ">> WARNING: invalid term id=%d voca=%s\n", $srcTid, $voca);
	}

	return $tid;
}

function get_src_term_name( $tid)
{
    global $src_term;

    $name = $src_term['reverse'][$tid];
    if ( empty( $name)) {
		printf(">> ERROR: term not found tid=%d\n", $tid);
		debug_print_backtrace();
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
		debug_print_backtrace();
        return NULL;
    }

    return $name['voca'];
}                

function check_user_confirm()
{
    global $yes_flag;

    if ( $yes_flag == TRUE) return TRUE;

    $line = readline("> Update ? [Y/n/a] ");
    if ( $line == 'a') {
        $yes_flag = TRUE;
        return TRUE;
    }

    if ( $line == 'n') return FALSE;
    return TRUE;
}


function check_node( $update_flag, $src)
{
    global $user, $child_info, $src_node, $child_node;

    // check by title
    $objs = ocs_get_nodes_by_title( $src->type, $src->title);
    $org_nid = $src->nid;

    if ( count($objs) > 0) {
        printf("(%d) Existing %s : %s \t nid=%d org=%d\n", count($objs), $src->type, $src->title, $objs[0], $org_nid);

        if ( $update_flag) {
            // delete node
            $node = node_load( $objs[0]);
            printf("Delete %s %s nid=%d\n", $node->type, $node->title, $node->nid);

            if ( $node->type == 'simpleproductoffering') {
                rm_product( $node->field_product_id['und'][0]['value']);
            }
            else {
                if ( isset($child_info[$node->type])) {
                    foreach( $child_info[$node->type] as $ref) {
                        print_r( $ref);
                        if ( isset( $node->$ref['ref_field'])) {
                            print_r( array_get_value( $node->$ref['ref_field'], FALSE));
                            remove_node_list( $ref['child_type'], array_get_value( $node->$ref['ref_field'], FALSE));
                        }
                        remove_all_node_of_specific_type( $ref['child_type'], $ref['rev_ref_field'], 'nid', $node->nid);
                    }
                }

                node_delete( $node->nid);
            }
        }
        else {
            $node = node_load( $objs[0]);

            $field = field_info_instances( 'node', $src->type);
            check_diff( $update_flag, $field, $src, $node);

			if ( $src->type == 'simpleproductoffering') {
				check_diff_product( $src, $child_node[$src->type][$src->nid], $node);
			}

            return;
        }
    }

    // new carrier, numbering plan and etc
    printf("New %s : %s org=%d\n", $src->type, $src->title, $org_nid);

    $node = clone $src;
    $node->uid = $user->uid;
    _unset_unused_field_of_cloned_node($node);
    
    if ( $update_flag && check_user_confirm()) {
        printf("Check fields\n");
        check_field( $node);

        switch ( $src->type ) {
        case 'timetable':
            node_save( $node);
            update_timetable( $node);
            break;
        case 'simpleproductoffering':
            $svcdomain = get_src_term_name( $src->field_service_type_of_provider['und'][0]['tid']);
            $prdtype = get_src_term_name( $src->field_product_type['und'][0]['tid']);   
            printf("Add %s %s product\n", $svcdomain, $prdtype);

            unset( $node->field_next_join_confirm);
            add_product( $node, $child_node[$src->type][$src->nid]);
            break;
        default:
            if ( isset($child_info[$node->type])) {
                foreach( $child_info[$node->type] as $ref) {
                    if ( isset( $node->$ref['ref_field']))
                        unset( $node->$ref['ref_field']);
                }
            }
            node_save( $node);

            printf("Check child nodes\n");
            check_child_node( $node, $org_nid);
            break;
        }
    }

}			

function update_timetable( $src)
{
    global $src_node, $user;

    // update timetablefactors
    $table_list = array();
    foreach( $src->field_ref_timetablefactors['und'] as $nid) {
        $table = clone $src_node['timetablefactors'][$nid['nid']];
        $table->uid = $user->uid;
        _unset_unused_field_of_cloned_node($table);
        node_save( $table);
        printf("  add time table factor : %s\n", $table->title);

        $table_list[] = $table->nid;

        $slot_list = array();
        foreach( $table->field_ref_timetablefactorsslot['und'] as $slot_nid) {
            $slot = clone $src_node['timetablefactorsslot'][$slot_nid['nid']];
            $slot->uid = $user->uid;
            _unset_unused_field_of_cloned_node($slot);

            $slot->field_ref_timetablefactors['und'][0]['nid'] = $table->nid;
            $slot->field_ref_timetable['und'][0]['nid'] = $src->nid;
            node_save( $slot);

            $slot_list[] = $slot->nid;
        }

        unset( $table->field_ref_timetablefactorsslot);
        foreach( $slot_list as $nid) {
            $table->field_ref_timetablefactorsslot['und'][] = array( 'nid' => $nid);
        }
        node_save( $table);
    }

    unset( $src->field_ref_timetablefactors);
    foreach( $table_list as $nid) {
        $src->field_ref_timetablefactors['und'][] = array( 'nid' => $nid);
    }
    node_save( $src);
}

function check_field( $node)
{
    global $update_field_list, $src_node, $update_flag;

    foreach( $update_field_list as $type => $list) {
        // $type is 'tid', 'nid' or 'target_id'
        foreach( $list as $field_name => $voca) {
            if ( isset( $node->{$field_name}['und'])) {
                printf("  check %s  voca=%s\n", $field_name, $voca);
                $field = &$node->$field_name;

				foreach( $field['und'] as $idx => $nid) {
					$id = ( $type == 'tid') ? get_target_tid( $voca, $field['und'][$idx][$type]) : 
						get_target_nid( $field_name, $voca, $field['und'][$idx][$type]);

					if ( $id == NULL) {
						printf(">> Stop checking fields\n");
						return FALSE;
					}
					else if ( ! empty( $id)) {
						$field['und'][$idx][$type] = $id;

						if ( $field['und'][$idx][$type] != $id)
							printf( ">> WARNING: Change field %s[%d] %d=>%d\n", 
								$field_name, $idx, $field['und'][$idx][$type], $id);
					}
                }
            }
        }
    }

	return TRUE;
}

function get_target_nid( $field_name, $type, $org_nid)
{
    global $src_node;

    if ( isset( $src_node[$type][$org_nid])) {
        $src_obj = $src_node[$type][$org_nid];

        // find the node in this system
        $objs = ocs_get_nodes_by_title( $src_obj->type, $src_obj->title);
        if ( count( $objs) == 0) {
            printf(">> ERROR : ref field '%s' is not found in this system. nid=%d title=%s\n", $field_name, $org_nid, $src_obj->title);
        }
        else if ( count( $objs) > 1) {
            printf(">> ERROR : %d ref field '%s' exist in this system. nid=%d\n", count($objs), $field_name, $org_nid);
        }
        else {
            printf("  nid of ref field '%s' is changed to %d\n", $field_name, $objs[0]);
            return $objs[0];
        }
    }
    else {
        printf(">> ERROR : ref field '%s' not found in the backup file. type=%s nid=%d\n", $field_name, $type, $org_nid);
        //print_r( $src_node[$type]);
    }

    return NULL;
}

function check_child_node( $parent, $org_parent_nid)
{
    global $child_info, $src_node, $user;

    if ( isset( $child_info[$parent->type])) {
        foreach( $child_info[$parent->type] as $ref) {

            if ( $ref['child_type'] == 'ocs_svc_perm') {
                // ocs_svc_perm nodes are created automatically when lifecyclescheme is created.
                // remove them all 
                remove_all_node_of_specific_type( $ref['child_type'], $ref['rev_ref_field'], 'nid', $parent->nid);
            }

            $child_src = $src_node[$ref['child_type']];

            // this node has child
            printf("Update child nodes type=%s\n", $ref['child_type']);

            //printf("org nid=%d\n", $org_parent_nid);
            // clone chlid node from 'child_src' if the 'rev_ref_field' has org_parent_nid
            printf("  # of child nodes : %d\n", count( $child_src));
            if ( count( $child_src) > 0 ) {
                foreach( $child_src as $child_nid => $child_obj) {
                    $ref_field = $child_obj->$ref['rev_ref_field'];
                    //printf("ref nid=%d\n", $ref_field['und'][0]['nid']);

                    if ( $ref_field['und'][0]['nid'] == $org_parent_nid) {
                        // this child obj reference orginal node

                        $child = clone $child_obj;
                        $child->uid = $user->uid;
                        _unset_unused_field_of_cloned_node($child);

                        printf("Check fields.\n");
                        $ret = check_field( $child);
						if ( $ret === FALSE) continue;

                        // set node reference
                        $child->$ref['rev_ref_field'] = array( 'und' => array( 0 => array( 'nid' => $parent->nid)));

                        node_save( $child);

                        printf("  Save child node nid=%d title=%s\n", $child->nid, $child->title);

                        if ( isset( $ref['ref_field'])) {
                            // add child reference
                            $field = &$parent->$ref['ref_field'];
                            $field['und'][] = array( 'nid' => $child->nid);

                            node_save( $parent);
                            printf("Update parent field\n");
                        }

                        if ( isset($child_info[$child->type])) {
                            check_child_node( $child, $child_obj->nid);
                        }
                    }
                }
            }
        }
    }
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
}

function check_node_exist_in_this( $node_list, $type)
{
    global $check_this;

    if ( isset($check_this[$type])) return;

    $src_list = array();
    foreach( $node_list as $obj) {
        $src_list[$obj->title] = $obj->nid;
    }

	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
        ->execute();
	
    if ( ! empty( $result)) {
        foreach( array_keys( $result['node']) as $nid) {
            // node of this system
            $node = node_load( $nid);

            if ( ! isset( $src_list[$node->title])) {
                printf(">> WARNING : node of type=%s title='%s' exist only in this system\n", $type, $node->title);
            }
        }
    }

    $check_this[$type] = TRUE;
}

function remove_all_node_of_specific_type( $type, $field = NULL, $param=0, $value=0)
{
    printf("Remove all nodes of type %s\n", $type);

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', $type);

    if ( !empty($field)) {
        printf("  with condition : %s:%s = %s\n", $field, $nid, $value);
        $query->fieldCondition( $field, $param, $value);
    }

    $result = $query->execute();

    if ( ! empty( $result)) {
        foreach( array_keys( $result['node']) as $nid) {
            $node = node_load( $nid);
            printf("Delete %s %s\n", $type, $node->title);
            node_delete( $nid);
        }
    }
    else {
        printf("  No nodes are found.\n");
    }
}

// remove specific type of nodes
function remove_node_list( $type, $nids)
{
    foreach( $nids as $nid) {
        $node = node_load( $nid);
        if ( $node->type == $type) {
            printf("Delete %s %s nid=%d\n", $node->type, $node->title, $node->nid);
            node_delete( $nid);
        }
    }
}

function interactive_mode()
{
    $menu = array( array( 'title' => 'Carrier', 'type' => 'carrier_mobile'),
        array( 'title' => 'Domestic Numbering Plan', 'type' => 'numberingplan_domestic'),
        array( 'title' => 'Time Table', 'type' => 'timetable'),
        array( 'title' => 'Counter', 'type' => 'counter'),
        array( 'title' => 'OCS Message', 'type' => 'ocs_messages'),
        array( 'title' => 'OCS Message Group', 'type' => 'ocs_message_group'),
        array( 'title' => 'Unit Transfer', 'type' => 'unittransfer'),
        array( 'title' => 'Account States', 'type' => 'ocs_account_state'),
        array( 'title' => 'Lifecycle Scheme', 'type' => 'lifecyclescheme'),
        array( 'title' => 'Product', 'type' => 'simpleproductoffering'),
        );

    while( true) {
        printf("\nRestore Products \n", $fname);
        foreach( $menu as $idx => $item) {
            printf("[%2d] %s\n", $idx, $item['title']);
        }
        printf("[ q] Quit\n");

        $input = readline("> Input command : ");
        $input = trim( $input);
        if ( $input == '' || $input == 'q') return;
        else if ( is_numeric( $input) && $input >= 0 && $input < count($menu)) {
            restore_node( $menu[$input]['type']);
        }
    }
}

function restore_node( $node_type)
{
    global $src_node;

    while( true) {
        $idx = 0;
        $list = array();
        printf("\n");
        foreach( $src_node[$node_type] as $nid => $obj) {
            printf( "[%2d] ", $idx++);
            check_node( FALSE, $obj);
            $list[] = $obj;
        }
        check_node_exist_in_this( array_values( $src_node[$node_type]), $node_type);

        $input = readline( "\n> Input number or title, a (All) or q(quit) : ");
        $input = trim( $input);

        if ( $input == '' || $input == 'q' || $input == 'quit') {
            $update_flag = FALSE;
            break;
        }
        else if ( $input == 'a' || $input == 'all') {
			if ( $update_flag === FALSE) {
				remove_all_node_of_specific_type( $node_type);
			}

            foreach( $list as $obj) {
                check_node( TRUE, $obj);
            }
        }
        else if ( is_numeric( $input) && $input >= 0 && $input < $idx) {
            check_node( TRUE, $list[$input]);
        }
        else {
            // find by title
            foreach( $src_node[$node_type] as $nid => $obj) {
                if ( $obj->title == $input) {
                    check_node( TRUE, $obj);
                    break;
                }
            }
        }

        readline("Enter to continue ...");
    }

     return;
}

function read_taxonomy()
{
    global $fp, $src_term;

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

function read_node()
{
    global $fp, $src_node, $child_node;

    $child = array();
    rewind( $fp);
    while( ($data = get_content($fp)) !== NULL) {
        list( $type, $id, $subtype) = explode( ':', $data[0]);
//	printf( ">> %s %s:%s\n", $data[0], $type, $subtype);

        $obj = unserialize( $data[1]);
        if ( $obj == 'begin' || $obj == 'end') continue;

        if ( $type == 'node' ) {
            $src_node[$obj->type][$obj->nid] = $obj;
        }
		else if ( $type == 'field_collection_item') {
            $src_node[$subtype][$id] = $obj;
		}
        else if ( $type == 'simpleproductoffering') {
            $src_node[$obj->type][$obj->nid] = $obj;
            $child_node[$obj->type][$obj->nid] = $child;
            $child = array();
        }
        else {
            $child[$type][$id][] = $obj;
        }
    }

}
