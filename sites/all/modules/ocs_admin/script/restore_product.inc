<?php
global $update_flag;
global $buffer, $line;
global $dst_term, $src_term;
global $field_list_to_update;


// get global variables
$buffer = '';
$dst_term = ocs_get_all_terms();
$field_list_to_update = array( 'field_ref_service_feature_code');

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

$prd_field = field_info_instances( 'node', 'simpleproductoffering');

$line = 1;
$child = array();
while( ($data = get_content($fp)) !== NULL) {
	list( $type, $subtype) = explode( ':', $data[0]);
	//printf( ">> %s %s:%s\n", $data[0], $type, $subtype);

	$obj = unserialize( $data[1]);

	if ( $type == 'term') {
		$src_term = $obj;

		foreach( $src_term as $key => $data) {
			$src_term[$key]['reverse'] = array_flip( $data);
		}
	}
	else if ( $obj->type === 'simpleproductoffering') {
		check_product( $obj, $prd_field, $child);
		$child = array();
	}
	else {
		$child[$type][$subtype] = $obj;
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
	global $update_flag;

	// find the product
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'simpleproductoffering')
		->propertyCondition('title', $p->title)
		->execute();

	if ( empty( $result)) {
		printf( "New Product : %s id: %s\n", $p->title, $p->field_product_id['und'][0]['value']);
		add_product( $p, $child);
	}
	else {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			printf( "Existing Product : %s id: %s\n", $p->title, $p->field_product_id['und'][0]['value']);

			$diff = _compare_content( $field, $p, $node);
			if ( !empty( $diff)) {
				print_r( $diff);
				if ( $update_flag ) {
					foreach( $diff as $label => $attr) {
						println( '  Update ' . $label . ' : ' . $attr[0]);
						$node->$attr[2] = $p->$attr[2];
					}
					//node_save( $node);
				}
			}
		}
	}
}

function add_product( $src, $child)
{
	global $user;

	$productNode = $src;
	$productNode->uid = $user->uid;
	_unset_unused_field_of_cloned_node($productNode);
	unset($productNode->field_weight_for_ratingpriority);
	unset($productNode->field_weight_for_hierarchy);
	node_save($productNode);

	printf( "Save product id: %s\n", $productNode->field_product_id['und'][0]['value']);

	$idx = 0;
	foreach( $child as $key => $data) {
		$src = $data['data'];

		$childNode = get_attribute( $key, $productNode->nid, $src);
		node_save($childNode);
		printf( ">>  %s %s\n", $childNode->type, $chlidNode->title);

		/*
		if(isset($targetChildNode->field_charge_collection)){
			_clone_field_collection('node',$targetChildNode,$childNode,'field_charge_collection');
		}
		if(isset($targetChildNode->field_discount_collection)){
			_clone_field_collection('node',$targetChildNode,$childNode,'field_discount_collection');
		}
		_clone_nested_child_node($targetChildNode,$childNode);
		*/

		foreach( $data as $k2 => $obj) {
			if ( $k2 != 'data') {
				$actionSetNode = $obj;
				$actionSetNode->uid = $user->uid;
				$actionSetNode->field_ref_source_action['und'][0]['nid'] = $childNode->nid;
				_unset_unused_field_of_cloned_node($actionSetNode);
				node_save($actionSetNode);

				printf( ">>>>  %s:%s %s\n", $childNode->type, $actionSetNode->type, $actionSetNode->title);
			}
		}
		//if ( $idx ++ == 1) break;
	}

	exit;
}

function println( $str = '')
{
	print $str . "\n";
}


function get_attribute( $type, $nid, $src)
{
	global $field_list_to_update;

	// actionpriceallowanceonetime
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->fieldCondition('field_ref_product', 'nid', $nid);

	if ( isset( $src->field_ref_tree_tid)) {
		$tid = get_target_tid( $src->field_ref_tree_tid['und'][0]['value']);
		$query->fieldCondition('field_ref_tree_tid', 'value', $tid);
	}

	$result = $query->execute();

	if ( empty( $result)) {
		printf( "not found type=%s nid=%d tid=%d\n", $type, $nid, $tid);

		$p = $src;
		$p->field_ref_product['und'][0]['nid'] = $nid;
		$p->field_ref_tree_tid['und'][0]['value'] = $tid;
		_unset_unused_field_of_cloned_node($p);

		/*
		$p = ocs_admin_get_new_node( $type);

		// set ref product 
		$p->field_ref_product['und'][0]['nid'] = $nid;

		// set tree tid
		$p->field_ref_tree_tid['und'][0]['value'] = $tid;

		$field = field_info_instances( 'node', $type);
		$diff = _compare_content( $field, $src, $p);
		if ( !empty( $diff)) {
			//print_r( $diff);
			foreach( $diff as $label => $attr) {
				if ( array_search( $attr[2], $field_list_to_update) !== FALSE) {
					println( '  Update ' . $label . ' : ' . $attr[0]);
					$p->$attr[2] = $src->$attr[2];
				}
			}
		}
		*/
	}
	else {
		$nid = array_pop( array_keys( $result['node']));
		$p = node_load( $nid);

		printf( "found type=%s %s nid=%d \n", $type, $p->title, $p->nid);
	}
	return $p;
}

function get_target_tid( $srcTid)
{
	global $src_term, $dst_term;

	// first get term name
	$name = $src_term['tpl_default_tree_mobile']['reverse'][$srcTid];
	$tid = $dst_term['tpl_default_tree_mobile'][$name];
	printf( "%s:%d => %d\n", $name, $srcTid, $tid);

	return $tid;
}

/*
function _unset_unused_field_of_cloned_node($node)
{
	unset($node->vid);
	unset($node->nid);
	unset($node->log);
	unset($node->status);
	unset($node->comment);
	unset($node->promote);
	unset($node->sticky);
	unset($node->created);
	unset($node->changed);
	unset($node->tnid);
	unset($node->translate);
	unset($node->revision_timestamp);
	unset($node->revision_uid);
	unset($node->rdf_mapping);
	unset($node->cid);
	unset($node->last_comment_timestamp);
	unset($node->last_comment_name);
	unset($node->last_comment_uid);
	unset($node->comment_count);
	unset($node->name);
	unset($node->picture);
	unset($node->data);    

	return $node;
}

*/
