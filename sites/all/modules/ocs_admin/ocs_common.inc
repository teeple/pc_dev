<?php

define( 'OCS_PARAM_TYPE_STRING', '1');
define( 'OCS_PARAM_TYPE_INTEGER', '2');
define( 'OCS_PARAM_TYPE_ENUM', '3');
define( 'OCS_PARAM_TYPE_ACCOUNT_KEY', '4');
define( 'OCS_PARAM_TYPE_DATE', '5');
define( 'OCS_PARAM_TYPE_TIME', '6');
define( 'OCS_PARAM_TYPE_PRODUCT_KEY', '7');
define( 'OCS_PARAM_TYPE_COUNTER', '8');
define( 'OCS_PARAM_TYPE_MESSAGE', '9');
define( 'OCS_PARAM_TYPE_FUNCTION', '10');
define( 'OCS_PARAM_TYPE_ACCOUNT_STATUS', '11');
define( 'OCS_PARAM_TYPE_PIVOT_DATE', '12');
define( 'OCS_PARAM_TYPE_DAYS_TO_ADD', '13');
define( 'OCS_PARAM_TYPE_DAYS_LIST', '14');
define( 'OCS_PARAM_TYPE_MONTH_LIST', '15');
define( 'OCS_PARAM_TYPE_OPERATOR_LIST', '16');

function ocs_admin_get_param_type( $name)
{
    $optype = array(
        'string' => OCS_PARAM_TYPE_STRING,
        'integer' => OCS_PARAM_TYPE_INTEGER,
        'enum' => OCS_PARAM_TYPE_ENUM,
        'account_key' => OCS_PARAM_TYPE_ACCOUNT_KEY,
        'date' => OCS_PARAM_TYPE_DATE,
        'time' => OCS_PARAM_TYPE_TIME,
        'product_key' => OCS_PARAM_TYPE_PRODUCT_KEY,
        'counter' => OCS_PARAM_TYPE_COUNTER,
        'message' => OCS_PARAM_TYPE_MESSAGE,
        'function' => OCS_PARAM_TYPE_FUNCTION,
        'account_status' => OCS_PARAM_TYPE_ACCOUNT_STATUS,
        'pivot_date' => OCS_PARAM_TYPE_PIVOT_DATE,
        'days_to_add' => OCS_PARAM_TYPE_DAYS_TO_ADD,
    );

    if (isset( $optype[$name])) return $optype[$name];
        
    drupal_set_message( t( 'Undefined Open Parameter Type "@name". It shall be registered as STRING type.', 
        array( '@name' => $name)), 'warning');

    return OCS_PARAM_TYPE_STRING;
}


function ocs_admin_table_theme( $form, $header)
{

  drupal_add_tabledrag('menu-overview', 'order', 'sibling', 'menu-weight');

  $rows = array();
//  dpm( $form, 'table form');
  foreach ($form['#records'] as $key => $item) {
      $element = &$form['#records'][$key];
      $operations = array();
      foreach( element_children( $element['operations']) as $op) {
          $operations[] = array( 'data' => drupal_render($element['operations'][$op]),
            'class' => array('menu-operations'));
      }

      // Add special classes to be used for tabledrag.js.
      $element['weight']['#attributes']['class'] = array('menu-weight');

      $row = array();
      $row[] = theme( 'ocs_admin_group_overview', 
            array( 'title' => $element['title'],
                'name' => $element['name'],
                'description' => $element['description']));

      $row[] = drupal_render($element['weight']);
      $row = array_merge( $row, $operations);

      $row = array_merge(array('data' => $row), $element['#attributes']);
      $row['class'][] = 'draggable';
      $rows[] = $row;
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => $form['#empty_text'], 'colspan' => '7'));
  }
  $footer = ( isset($form['#footer'])) ?  array(array('data' => $form['#footer'], 'colspan' => '7')) : NULL;

  $output = '<br>';
  if ( isset( $form['#caption'])) {
      $output .= '<h3>' . $form['#caption'] . '</h3>';
  }
  $output .= theme('table', array('header' => $header, 'footer' => $footer, 'rows' => $rows, 'attributes' => array('id' => 'menu-overview')));
  return $output;
}

// get new content node
function ocs_admin_get_new_node( $type)
{
	global $user;

    $node = new stdClass();
    $node->type = $type;
    $node->uid = 0;
    $node->created = strtotime("now");
    $node->changed = strtotime("now");
    $node->status = 1;
    $node->comment = 0;
    $node->promote = 0;
    $node->moderate = 0;
    $node->sticky = 0;
    $node->language = LANGUAGE_NONE;

	$node->uid = $user->uid;

    node_object_prepare($node);

    return $node;
}


function ocs_admin_get_counter_name_list()
{
	$counters = &drupal_static( __FUNCTION__, array());
	if ( empty( $counters)) {
        // get counter name list
        /* bhtak 20121024 use content type 'counter' 
        module_load_include( 'inc', 'ocs_admin', 'ocs_counter');
        $counter_list = ocs_admin_counter_name_load_all();
        foreach( $counter_list as $value) {
            $counters[ $value['counter_name']] = $value['counter_name'];
        }
        */
        $items = entity_load( 'node', FALSE, array( 'type' => 'Counter'));
        foreach( $items as $item) {
            $counters[$item->title] = $item->title;
        }
    }

    return $counters;
}


function ocs_admin_get_message_list()
{
    $messages = &drupal_static( __FUNCTION__, array());
    if ( empty( $messages)) {   
        $items = entity_load( 'node', FALSE, array( 'type' => 'ocs_messages'));
        foreach( $items as $item) {
            $messages[$item->nid] = $item->title . ' : ' . $item->field_ocs_format['und'][0]['value'];
        }
    }

    return $messages;
}

function ocs_admin_get_message_group_list()
{
    $messages = &drupal_static( __FUNCTION__, array());
    if ( empty( $messages)) {   
        $items = entity_load( 'node', FALSE, array( 'type' => 'ocs_message_group'));
        foreach( $items as $item) {
            $messages[$item->nid] = $item->title ;
        }
    }

    return $messages;
}

function ocs_admin_get_account_state_list()
{
	$list = &drupal_static( __FUNCTION__, array());
	if ( empty( $list)) {
        $items = entity_load( 'node', FALSE, array( 'type' => 'ocs_account_state'));
        foreach( $items as $item) {
            $list[$item->nid] = $item->title ;
        }
	}
	return $list;
}


function ocs_admin_get_counter_id_list()
{
    $counter_id = &drupal_static( __FUNCTION__, array());
    if ( empty( $counter_id)) {
        /* bhtak 20121024 
        module_load_include( 'inc', 'ocs_admin', 'ocs_counter');
        $counter_list = ocs_admin_counter_name_load_all();
        foreach( $counter_list as $counter) {
            $counter_id[ $counter['counter_name']] = $counter['counter_id'];
        }
        */

        /* get vocabulary name */
		/*
        $vid = taxonomy_vocabulary_machine_name_load( 'countergroup');
        $query = new EntityFieldQuery;
        $result = $query->entityCondition('entity_type', 'taxonomy_term')
            ->propertyCondition('vid', $vid->vid)
            ->execute();

        $terms = taxonomy_term_load_multiple( array_keys( $result['taxonomy_term']));
		*/
        $terms = ocs_get_terms( 'countergroup');
//        dpm( $terms, 'term');

        $items = entity_load( 'node', FALSE, array( 'type' => 'counter'));
        foreach( $items as $item) {
//            dpm( $item, 'counter');
            $tid = $item->field_counter_group['und'][0]['tid'];
			if ( isset($terms[$tid])) {
				$group = $terms[$tid]->name;
				$counter_id[$group][$item->field_counter_id['und'][0]['value']] = $item->title;
			}
        }
    }

//    dpm( $counter_id, 'counter id list');

    return $counter_id;
}

function ocs_admin_get_counter_group_list()
{
    $counter_group = &drupal_static( __FUNCTION__, array());
    if ( empty( $counter_group)) {

        /* get vocabulary name */
		/*
        $vid = taxonomy_vocabulary_machine_name_load( 'countergroup');
        $query = new EntityFieldQuery;
        $result = $query->entityCondition('entity_type', 'taxonomy_term')
            ->propertyCondition('vid', $vid->vid)
            ->execute();

        $terms = taxonomy_term_load_multiple( array_keys( $result['taxonomy_term']));
		*/
        $terms = ocs_get_terms( 'countergroup');
       	foreach( $terms as $term) {
       		if ( !empty( $term->field_common_code))
       			$counter_group[$term->field_common_code['und'][0]['value']] = $term->name;
       	}
    }

//    dpm( $counter_group, 'counter id list');

    return $counter_group;
}


function ocs_admin_ftp_put( $ip_address, $user, $passwd, $dir, $file)
{
    $error_msg = NULL;

    // put file to the OCS server by ftp

    $ftp = ftp_connect( $ip_address);
    if ( $ftp) {
        $result = ftp_login( $ftp, $user, $passwd);
        if ( $result ) {
            if ( ftp_chdir( $ftp, $dir)) {
                if ( ! ftp_put( $ftp, $file, '/tmp/'.$file, FTP_ASCII)) {
                    $error_msg = t('Fail to put file %file to the server %addr at %dir.',
                        array( '%file' => $file, '%addr' => $ip_address, '%dir' => $dir));
                }
            }
            else {
                $error_msg = t('Fail to change directory to %dir', array( '%dir' => $dir));
            }
            ftp_close( $ftp);
        }
        else {
            $error_msg = t('Fail to login to the server %addr with user id "%user".',
                array( '%addr' => $ip_address, '%user' => $user));
        }
    }
    else {
        $error_msg = t('Fail to connect the server %addr',
            array( '%addr' => $ip_address));
    }

    if ( $error_msg) {
        drupal_set_message( $error_msg, 'warning');
        return FALSE;
    }


    return TRUE;
}

function ocs_admin_update_configuration( $file_name, $content)
{
    // write to file
    try{
        $fd = fopen( '/tmp/'. $file_name, 'w');
        fwrite( $fd, $content);
        fclose( $fd);

        $ip_address = variable_get('ocs_admin_ip_address', 'Administrative Warning');
        $user = variable_get('ocs_admin_user_account', 'Administrative Warning');
        $passwd = variable_get('ocs_admin_user_password', 'Administrative Warning');
        $dir = variable_get('ocs_admin_config_directory', 'Administrative Warning');

        // ftp to host
        if ( ocs_admin_ftp_put( $ip_address, $user, $passwd, $dir, $file_name)) {
            drupal_set_message( t('Configuration file "@name" is uploaded to the OCS',
                array( '@name' => $file_name)));
        }
    }
    catch( Exception $e) {
        drupal_set_message( $e->getMessage(), 'warning');       
    }
}

function ocs_node_title( $nid)
{
	$node = node_load( $nid);
	if ( $node) return $node->title;
	return "";
}

function array_get_value( $a, $withKey=TRUE, $f=array())
{
	if ( ! $a || ! is_array($a)) return array();
	foreach( $a as $k => $v) {
		if ( is_array( $v)) $f = array_get_value( $v, $withKey, $f);
		else {
			if ( $withKey) $f[$k] = $v;
			else $f[] = $v;
		}
	}
	return $f;
}

// return array of nodes
function ocs_get_nodes_by_node_ref( $type, $field, $key)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->fieldCondition( $field, 'nid', $key)
		->execute();
	
	return ( count($result) > 0) ? array_keys( $result['node']) : array();
}

// return array of nodes
function ocs_get_nodes_by_title( $type, $title)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->propertyCondition('title', $title)
		->execute();
	
	return ( count($result) > 0) ? array_keys( $result['node']) : array();
}

function ocs_get_node_by_cond( $type, $title, $field_cond)
{
	// find the attribute
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type);

	if ( $field_cond) {
		foreach( $field_cond as $cond) {
            if ( $cond[0] == 'property')
                $query->propertyCondition( $cond[1], $cond[2]);
            else
                $query->fieldCondition( $cond[0], $cond[1], $cond[2]);
		}
	}
	$result = $query->execute();

	if ( empty( $result)) {
		$node = ocs_admin_get_new_node( $type);
		$node->title = $title;
	}
	else {
		$node = node_load( array_pop( array_keys( $result['node'])));
	}

	return $node;
}

function ocs_get_nids_by_cond( $type, $field_cond = NULL)
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

	return empty($result) ? NULL : array_keys( $result['node']);
}


function ocs_get_terms( $voca)
{
	/* get vocabulary name */
	$vid = taxonomy_vocabulary_machine_name_load( $voca);
	$query = new EntityFieldQuery;
	$result = $query->entityCondition('entity_type', 'taxonomy_term')
		->propertyCondition('vid', $vid->vid)
		->execute();

	$terms = taxonomy_term_load_multiple( array_keys( $result['taxonomy_term']));
//        dpm( $terms, 'term');
	return $terms;
}

function ocs_ctools_link($title, $url, $opt)
{
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();

	$link_class = 'ctools-use-modal ctools-modal-add-item-modal-style';
	$delete_output = l($title, $url, array_merge( $opt, array('attributes' => array('class' => array('use-ajax')))));

	$link_string = '<div>'.$delete_output.'</div>';
	echo $link_string;
}


function ocs_log_changes( $before, $after)
{
	// dpm( $before, 'before');

	if ( get_class( $before) == 'FieldCollectionItemEntity') {
		// field_collection 
		$field = field_info_instances('field_collection_item', $before->field_name);
		$type = 'FieldCollectionItemEntity:' . $before->field_name;
		$id = 'item_id=' . $before->item_id;
	}
	else {
		$field = field_info_instances( 'node', $before->type);
		$type = $before->type;
		$id = 'nid=' . $before->nid;
	}

	$diff = _compare_content( $field, $before, $after);
	if ( ! empty( $diff)) {
		//dpm( $diff, 'diff');
		watchdog( 'change log', 'Content %type (%id) changed %data', array( '%type' => $type, '%id' => $id, '%data' => json_encode( $diff)), WATCHDOG_NOTICE); 
	}
}

function _compare_content( $field, $before, $after)
{
	$diff = array();
	foreach( $field as $key => $value) {
		$v1 = $before->$key;
		$v2 = $after->$key;
		$label = $value['label'];

		/*
		dpm( $key, 'key');
		dpm( $v1, 'v1');
		dpm( $value, 'value');
		*/

		if ( is_array( $v1)) {
			// field type
			$v1 = isset($v1['und']) ? $v1['und'] : NULL;
			$v2 = isset($v2['und']) ? $v2['und'] : NULL;
			for( $i=0; $i< max( count($v1), count( $v2)); $i++) {
				$vv1 = _get_field_value( $v1, $i);
				$vv2 = _get_field_value( $v2, $i);
				if ( $vv1 !== $vv2) {
					$diff[$label] = array( $vv1, $vv2, $key);
				}
			}
		}
		else {
			if ( $v1 !== $v2) {
				$diff[$label] = array( $v1, $v2, $key);
			}
		}
	}

	return $diff;
}

function _get_field_value( $v, $idx)
{
	if ( isset($v[$idx])) {
		$vv = $v[$idx];
		if ( isset( $vv['nid'])) return $vv['nid'];
		if ( isset( $vv['value'])) return $vv['value'];
		if ( isset( $vv['tid'])) {
			$term = taxonomy_term_load( $vv['tid']);
			return $term->name;
		}
		return $vv;
	}
	return NULL;
}

function ocs_get_terms_tid( $term_name)
{
	$result = array();
	$terms = ocs_get_terms( $term_name);
	foreach( $terms as $tid => $term) {
		$result[$term->name] = $tid;
		if ( isset( $term->field_rel_type))
			$result[$term->field_rel_type['und'][0]['value']] = $tid;
	}

	return $result;
}

function ocs_get_all_terms()
{
// get voca terms
	$term = array();
	foreach( array( 'PrdType', 'BillType', 'PrdSubType', 'CustKdCd', 'PrdExpireDate', 
				'tpl_default_tree_mobile', 'counterset_addorreplace') as $voca) {
		$term[$voca] = ocs_get_terms_tid( $voca);
	}

	$term['day_option'] = array(
			'start' => ocs_get_terms_tid( 'specialdateoptions'),
			'end' => ocs_get_terms_tid( 'specialenddateoptions'),
			'unit' => ocs_get_terms_tid( 'unitofmeasure_enddate'));

	//print_r( $term_day_option);
	return $term;
}
