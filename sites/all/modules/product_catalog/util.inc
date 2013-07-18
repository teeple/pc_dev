<?php

function find_parent_product($childNode) {
	if (isset($childNode -> field_ref_product['und'][0]['nid'])) {
		return node_load($childNode -> field_ref_product['und'][0]['nid']);
		//_touch_product($childNode->field_ref_product['und'][0]['nid']);
	} else {
		if ($childNode -> type != 'simpleproductoffering') {
			$parentNode = NULL;

			if (isset($childNode -> field_ref_tariffplan['und'][0]['nid'])) {
				$parentNode = node_load($childNode -> field_ref_tariffplan['und'][0]['nid']);
			} else if (isset($childNode -> field_parent_node['und'][0]['nid'])) {
				$parentNode = node_load($childNode -> field_parent_node['und'][0]['nid']);
			} else if (isset($childNode -> field_ref_source_action['und'][0]['nid'])) {
				$parentNode = node_load($childNode -> field_ref_source_action['und'][0]['nid']);
			} else if (isset($childNode -> field_ref_nonusagerollover['und'][0]['nid'])) {
				$parentNode = node_load($childNode -> field_ref_nonusagerollover['und'][0]['nid']);
			}

			if ($parentNode != NULL) {
				return find_parent_product($parentNode);
			}
		}
	}

	return NULL;
}

function is_macaddress($val) {
	return (bool)preg_match('/^([0-9a-fA-F][0-9a-fA-F]:){2}([0-9a-fA-F][0-9a-fA-F])$/', $val);
}

function _clone_field_collection($type, $orgEntity, $newEntity, $collectionName) {
	$evalStr = '$orgCollections = $orgEntity->' . $collectionName . ';';
	eval($evalStr);

	if (isset($orgCollections['und'][0]['value'])) {
		$evalStr = 'unset($newEntity->' . $collectionName . ');';
		eval($evalStr);
		$fieldsetCount = count($orgCollections['und']);

		for ($i = 0; $i < $fieldsetCount; $i++) {
			$evalStr = '$orgCollectionInfo = field_collection_item_load($orgEntity->' . $collectionName . '[\'und\'][' . $i . '][\'value\']);';
			eval($evalStr);
			$newCollectionInfo = entity_create('field_collection_item', array('field_name' => $collectionName));
			$newCollectionInfo -> setHostEntity($type, $newEntity);
			//$orgCollectionInfo = field_collection_item_load($orgEntity->$collectionName['und'][$i]['value']);

			switch($collectionName) {
				case 'field_charge_collection' :
					$newCollectionInfo -> field_range_start = $orgCollectionInfo -> field_range_start;
					$newCollectionInfo -> field_range_end = $orgCollectionInfo -> field_range_end;
					$newCollectionInfo -> field_uom_amount = $orgCollectionInfo -> field_uom_amount;
					$newCollectionInfo -> field_price_amount_float = $orgCollectionInfo -> field_price_amount_float;
					break;
				case 'field_discount_collection' :
					$newCollectionInfo -> field_range_start = $orgCollectionInfo -> field_range_start;
					$newCollectionInfo -> field_range_end = $orgCollectionInfo -> field_range_end;
					$newCollectionInfo -> field_discount_ = $orgCollectionInfo -> field_discount_;
					break;
			}
			$newCollectionInfo -> save();
			$evalStr = '$newEntity->' . $collectionName . '[\'und\'][' . $i . '][\'value\'] = $newCollectionInfo->item_id;';
			eval($evalStr);
			//$newEntity->$collectionName['und'][$i]['value'] = $newCollectionInfo->item_id;
		}

	}

	switch($type) {
		case 'taxonomy_term' :
			taxonomy_term_save($newEntity);
			break;
		case 'node' :
			node_save($newEntity);
			break;
	}
}

function _clone_vocabulary($baseVocaName, $targetVocaName, $param = array()) {
	$baseVocaMachineName = strtolower($baseVocaName);
	$baseVoca = taxonomy_vocabulary_machine_name_load($baseVocaMachineName);

	$targetVocaMachineName = strtolower($targetVocaName);
	$targetVoca = taxonomy_vocabulary_machine_name_load($targetVocaMachineName);

	//check target vocabulary
	if ($targetVoca == NULL) {
		$targetVoca = clone $baseVoca;
		unset($targetVoca -> vid);
		$targetVoca -> name = $targetVocaName;
		$targetVoca -> description = $targetVocaName;
		$targetVoca -> machine_name = $targetVocaMachineName;
		taxonomy_vocabulary_save($targetVoca);
	} else {
		$deleteTerms = taxonomy_get_tree($targetVoca -> vid);
		foreach ($deleteTerms as $deletTerm) {
			taxonomy_term_delete($deletTerm -> tid);
		}
	}

	//field instance information
	$fieldParam = array();
	$fieldParam['bundle'] = $baseVocaMachineName;
	$fieldInstances = field_read_instances($fieldParam);

	foreach ($fieldInstances as $field) {
		$checkParam = array();
		$checkParam['bundle'] = $targetVocaMachineName;
		$checkParam['field_name'] = $field['field_name'];
		$checkFieldInfo = field_read_instances($checkParam);

		if (empty($checkFieldInfo)) {
			$field_instance = array('field_name' => $field['field_name'], 'entity_type' => 'taxonomy_term', 'bundle' => $targetVocaMachineName, 'label' => $field['label'], 'description' => $field['description'], 'widget' => $field['widget'], );
			field_create_instance($field_instance);
		}
	}

	//get base terms
	$terms = taxonomy_get_tree($baseVoca -> vid);
	$tids = array();
	foreach ($terms as $term) {
		$tids[] = $term -> tid;
	}
	$baseTerms = taxonomy_term_load_multiple($tids);
	$tidMap = array();

	//duplicates terms
	foreach ($baseTerms as $baseTerm) {
		$targetTerm = clone $baseTerm;
		$targetTerm -> vid = $targetVoca -> vid;
		unset($targetTerm -> tid);

		$tempParent = taxonomy_get_parents($baseTerm -> tid);
		if (!empty($tempParent)) {
			$targetTerm -> parent = $tidMap[current($tempParent) -> tid];
		}

		//check rel_type params
		if (isset($param['rel_type']) && isset($targetTerm -> field_rel_type['und'][0]['value'])) {
			$baseRelTypeStr = $targetTerm -> field_rel_type['und'][0]['value'];
			$baseRelTypeArr = explode('_', $baseRelTypeStr);

			$reltypes = array('mobile', 'iptv', 'satellite', 'broadband', 'bundle', 'voip', 'cross');

			$matched = array_intersect($reltypes, $baseRelTypeArr);

			$newRelTypeStr = str_replace($matched, $param['rel_type'], $baseRelTypeStr);
			$targetTerm -> field_rel_type['und'][0]['value'] = $newRelTypeStr;
			$targetTerm -> field_rel_type['und'][0]['safe_value'] = $newRelTypeStr;
		}

		taxonomy_term_save($targetTerm);
		$tidMap[$baseTerm -> tid] = $targetTerm -> tid;

		$targetTerm = taxonomy_term_load($targetTerm -> tid);
		//field_collection items
		//field_qtabs_loading
		if (isset($baseTerm -> field_qtabs_loading['und'][0]['value'])) {
			unset($targetTerm -> field_qtabs_loading);
			$baseCollectionInfo = field_collection_item_load($baseTerm -> field_qtabs_loading['und'][0]['value']);
			$targetCollectionInfo = entity_create('field_collection_item', array('field_name' => 'field_qtabs_loading'));
			$targetCollectionInfo -> setHostEntity('taxonomy_term', $targetTerm);
			$targetCollectionInfo -> field_tab_type = $baseCollectionInfo -> field_tab_type;
			$targetCollectionInfo -> field_tab_content = $baseCollectionInfo -> field_tab_content;
			$targetCollectionInfo -> field_view_display = $baseCollectionInfo -> field_view_display;
			$targetCollectionInfo -> field_view_arguments = $baseCollectionInfo -> field_view_arguments;
			$targetCollectionInfo -> save();
			$targetTerm -> field_qtabs_loading['und'][0]['value'] = $targetCollectionInfo -> item_id;
		}
		//field_qtabs_click
		if (isset($baseTerm -> field_qtabs_click['und'][0]['value'])) {
			unset($targetTerm -> field_qtabs_click);
			$baseCollectionInfo = field_collection_item_load($baseTerm -> field_qtabs_click['und'][0]['value']);
			$targetCollectionInfo = entity_create('field_collection_item', array('field_name' => 'field_qtabs_click'));
			$targetCollectionInfo -> setHostEntity('taxonomy_term', $targetTerm);
			$targetCollectionInfo -> field_tab_type = $baseCollectionInfo -> field_tab_type;
			$targetCollectionInfo -> field_tab_content = $baseCollectionInfo -> field_tab_content;
			$targetCollectionInfo -> field_view_display = $baseCollectionInfo -> field_view_display;
			$targetCollectionInfo -> field_view_arguments = $baseCollectionInfo -> field_view_arguments;
			$targetCollectionInfo -> field_tab_title = $baseCollectionInfo -> field_tab_title;
			$targetCollectionInfo -> save();
			$targetTerm -> field_qtabs_click['und'][0]['value'] = $targetCollectionInfo -> item_id;
		}
		//field_qtabs_right_click
		if (isset($baseTerm -> field_qtabs_right_click['und'][0]['value'])) {
			unset($targetTerm -> field_qtabs_right_click);
			$baseCollectionInfo = field_collection_item_load($baseTerm -> field_qtabs_right_click['und'][0]['value']);
			$targetCollectionInfo = entity_create('field_collection_item', array('field_name' => 'field_qtabs_right_click'));
			$targetCollectionInfo -> setHostEntity('taxonomy_term', $targetTerm);
			$targetCollectionInfo -> field_tab_type = $baseCollectionInfo -> field_tab_type;
			$targetCollectionInfo -> field_tab_content = $baseCollectionInfo -> field_tab_content;
			$targetCollectionInfo -> field_view_display = $baseCollectionInfo -> field_view_display;
			$targetCollectionInfo -> field_view_arguments = $baseCollectionInfo -> field_view_arguments;
			$targetCollectionInfo -> field_tab_title = $baseCollectionInfo -> field_tab_title;
			$targetCollectionInfo -> save();
			$targetTerm -> field_qtabs_right_click['und'][0]['value'] = $targetCollectionInfo -> item_id;
		}
		//field_qtabs_right_click_exclude
		if (isset($baseTerm -> field_qtabs_right_click_exclude['und'][0]['value'])) {
			unset($targetTerm -> field_qtabs_right_click_exclude);
			$baseCollectionInfo = field_collection_item_load($baseTerm -> field_qtabs_right_click_exclude['und'][0]['value']);
			$targetCollectionInfo = entity_create('field_collection_item', array('field_name' => 'field_qtabs_right_click_exclude'));
			$targetCollectionInfo -> setHostEntity('taxonomy_term', $targetTerm);
			$targetCollectionInfo -> field_tab_type = $baseCollectionInfo -> field_tab_type;
			$targetCollectionInfo -> field_tab_content = $baseCollectionInfo -> field_tab_content;
			$targetCollectionInfo -> field_view_display = $baseCollectionInfo -> field_view_display;
			$targetCollectionInfo -> field_view_arguments = $baseCollectionInfo -> field_view_arguments;
			$targetCollectionInfo -> save();
			$targetTerm -> field_qtabs_right_click_exclude['und'][0]['value'] = $targetCollectionInfo -> item_id;
		}
		//field_qtabs_right_click_include
		if (isset($baseTerm -> field_qtabs_right_click_include['und'][0]['value'])) {
			unset($targetTerm -> field_qtabs_right_click_include);
			$baseCollectionInfo = field_collection_item_load($baseTerm -> field_qtabs_right_click_include['und'][0]['value']);
			$targetCollectionInfo = entity_create('field_collection_item', array('field_name' => 'field_qtabs_right_click_include'));
			$targetCollectionInfo -> setHostEntity('taxonomy_term', $targetTerm);
			$targetCollectionInfo -> field_tab_type = $baseCollectionInfo -> field_tab_type;
			$targetCollectionInfo -> field_tab_content = $baseCollectionInfo -> field_tab_content;
			$targetCollectionInfo -> field_view_display = $baseCollectionInfo -> field_view_display;
			$targetCollectionInfo -> field_view_arguments = $baseCollectionInfo -> field_view_arguments;
			$targetCollectionInfo -> save();
			$targetTerm -> field_qtabs_right_click_include['und'][0]['value'] = $targetCollectionInfo -> item_id;
		}
		//field_qtabs_click_arguments
		if (isset($baseTerm -> field_qtabs_click_arguments['und'][0]['value'])) {
			unset($targetTerm -> field_qtabs_click_arguments);
			$baseCollectionInfo = field_collection_item_load($baseTerm -> field_qtabs_click_arguments['und'][0]['value']);
			$targetCollectionInfo = entity_create('field_collection_item', array('field_name' => 'field_qtabs_click_arguments'));
			$targetCollectionInfo -> setHostEntity('taxonomy_term', $targetTerm);
			$targetCollectionInfo -> field_tab_type = $baseCollectionInfo -> field_tab_type;
			$targetCollectionInfo -> field_tab_content = $baseCollectionInfo -> field_tab_content;
			$targetCollectionInfo -> field_view_display = $baseCollectionInfo -> field_view_display;
			$targetCollectionInfo -> field_view_arguments = $baseCollectionInfo -> field_view_arguments;
			$targetCollectionInfo -> save();
			$targetTerm -> field_qtabs_click_arguments['und'][0]['value'] = $targetCollectionInfo -> item_id;
		}
		//field_default_fieldset
		if (isset($baseTerm -> field_default_fieldset['und'][0]['value'])) {
			unset($targetTerm -> field_default_fieldset);
			$fieldsetCount = count($baseTerm -> field_default_fieldset['und']);
			for ($i = 0; $i < $fieldsetCount; $i++) {
				$baseCollectionInfo = field_collection_item_load($baseTerm -> field_default_fieldset['und'][$i]['value']);
				$targetCollectionInfo = entity_create('field_collection_item', array('field_name' => 'field_default_fieldset'));
				$targetCollectionInfo -> setHostEntity('taxonomy_term', $targetTerm);
				$targetCollectionInfo -> field_field_name = $baseCollectionInfo -> field_field_name;
				$targetCollectionInfo -> field_field_value = $baseCollectionInfo -> field_field_value;
				$targetCollectionInfo -> save();
				$targetTerm -> field_default_fieldset['und'][$i]['value'] = $targetCollectionInfo -> item_id;
			}
		}
		taxonomy_term_save($targetTerm);
	}
}

/**
 * Searches haystack for needle and returns an array of the key path if it is found in the (multidimensional) array, FALSE otherwise.
 *
 * mixed array_searchRecursive ( mixed needle, array haystack [, bool strict[, array path]] )
 */
function array_searchRecursive_get_key_path($needle, $haystack, $strict = false, $path = array()) {
	if (!is_array($haystack)) {
		return false;
	}

	foreach ($haystack as $key => $val) {
		if (is_array($val) && $subPath = array_searchRecursive_get_key_path($needle, $val, $strict, $path)) {
			$path = array_merge($path, array($key), $subPath);
			return $path;
		} elseif ((!$strict && $val == $needle) || ($strict && $val === $needle)) {
			$path[] = $key;
			return $path;
		}
	}
	return false;
}

function array_flatten($array) {
	if (!is_array($array)) {
		return FALSE;
	}
	$result = array();
	foreach ($array as $key => $value) {
		if (is_array($value)) {
			$result = array_merge($result, array_flatten($value));
		} else {
			$result[$key] = $value;
		}
	}
	return $result;
}

function objectToArray($d) {
	if (is_object($d)) {
		// Gets the properties of the given object
		// with get_object_vars function
		$d = get_object_vars($d);
	}

	if (is_array($d)) {
		/*
		 * Return array converted to object
		 * Using __FUNCTION__ (Magic constant)
		 * for recursive call
		 */
		return array_map(__FUNCTION__, $d);
	} else {
		// Return array
		return $d;
	}
}

function _indent_json_string($json) {

	$result = '';
	$pos = 0;
	$strLen = strlen($json);
	//$indentStr   = '  ';
	$indentStr = '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
	//$newLine     = "\n";
	$newLine = "<br/>";
	$prevChar = '';
	$outOfQuotes = true;

	for ($i = 0; $i <= $strLen; $i++) {

		// Grab the next character in the string.
		$char = substr($json, $i, 1);

		// Are we inside a quoted string?
		if ($char == '"' && $prevChar != '\\') {
			$outOfQuotes = !$outOfQuotes;

			// If this character is the end of an element,
			// output a new line and indent the next line.
		} else if (($char == '}' || $char == ']') && $outOfQuotes) {
			$result .= $newLine;
			$pos--;
			for ($j = 0; $j < $pos; $j++) {
				$result .= $indentStr;
			}
		}

		// Add the character to the result string.
		$result .= $char;

		// If the last character was the beginning of an element,
		// output a new line and indent the next line.
		if (($char == ',' || $char == '{' || $char == '[') && $outOfQuotes) {
			$result .= $newLine;
			if ($char == '{' || $char == '[') {
				$pos++;
			}

			for ($j = 0; $j < $pos; $j++) {
				$result .= $indentStr;
			}
		}

		$prevChar = $char;
	}

	return $result;
}

function _fill_blank_string_for_timeslot($str) {
	$value = intval($str);
	if ($value / 10 < 1) {
		$str = '0' . $str;
	}
	return $str;
}

function generate_jstree() {

	require_once ('Smarty.class.php');
	$smarty = new Smarty();
	$smarty -> setTemplateDir('/var/www/pc_dev/sites/default/files/Smarty/templates/');
	$smarty -> setCompileDir('/var/www/pc_dev/sites/default/files/Smarty/templates_c/');
	$smarty -> setConfigDir('/var/www/pc_dev/sites/default/files/Smarty/configs/');
	$smarty -> setConfigDir('/var/www/pc_dev/sites/default/files/Smarty/cache/');
	$smarty -> assign('name', 'Ned');
	$smarty -> fetch('index.tpl');
}

function build_navigation_bar() {
	global $user;

	$path = current_path();
	//dpm( $path, 'current path');
	// test, test
	$menu = array('dash' => array('href' => '/', 'icon' => 'dash', 'prefix' => 'node', 'title' => 'Home'), 'product' => array('href' => '/product_designer/Mobile', 'icon' => 'gal', 'prefix' => 'product_designer', 'title' => 'Product Designer', 'role' => 'product designer', 'sub' => array( array('/product_designer/Mobile', 'Mobile'), array('/product_designer/IPTV', 'IPTV'), array('/product_designer/Broadband', 'Broadband'), array('/product_designer/VoIP', 'VoIP'), array('/product_designer/Satellite', 'Satellite'), array('/product_designer/Dummy', 'Dummy'), array('/product_designer/Cross', 'Bundle'))), 'relation' => array('href' => '/relation/product/hierarchy/Mobile', 'icon' => 'widgets', 'prefix' => 'relation', 'title' => 'Relation Manager', 'role' => 'relation manager', ), 'lifecycle' => array('href' => '/lifecycles/deploy/PRODUCT', 'icon' => 'anlt', 'prefix' => 'lifecycles', 'title' => 'Lifecycle', 'role' => 'lifecycle manager'), 'common' => array('href' => '/common/numberingplan/domestic/list', 'icon' => 'typ', 'prefix' => 'common', 'title' => 'Common Data', 'role' => 'common data manager', 'sub' => array( array('/common/counter/list', 'Counters'), array('/common/numberingplan/domestic/list', 'Numbering Plan'), array('/common/roaming/country/list', 'Roaming Plan'), array('/common/packet/predefined/charging_rule/list', 'Packet'), array('/common/vouchercardtype', 'ETC'), )), 'simulator' => array('href' => '/simulator/test/voice', 'icon' => 'grid', 'prefix' => 'simulator/', 'title' => 'Simulator', 'role' => 'simulator', ), 'ocs' => array('href' => '/config/ocs', 'icon' => 'tb', 'prefix' => 'config/ocs', 'title' => 'OCS', 'role' => 'ocs manager'), );

	$output = '';
	foreach ($menu as $item) {

		if (!in_array('administrator', $user -> roles)) {
			if (isset($item['role']) && !in_array($item['role'], $user -> roles))
				continue;
		}

		$image = '/sites/default/files/images/nav/' . $item['icon'];
		//dpm( $item['prefix']);
		if (strpos($path, $item['prefix'], 0) === 0)
			$image .= '-active.png';
		else
			$image .= '.png';

		$sub_menu = '';
		if (array_key_exists('sub', $item)) {
			foreach ($item['sub'] as $title) {
				$sub_menu .= t('<li><a href="@href">@title</a></li>', array('@href' => $title[0], '@title' => $title[1]));
			}
			$sub_menu = '<ul class="sub-nav">' . $sub_menu . '</ul>';
		}

		$output .= t('<li class="nav-item"><a href="@href"><img src="@image" alt="" /><p>@title</p></a>!sub</li>', array('@href' => $item['href'], '@image' => $image, '@title' => $item['title'], '!sub' => $sub_menu));
	}

	print '<div class="top-bar"><ul id="nav">' . $output . '</ul></div>';
}

function _get_nids_from_views($view_name, $display, $args) {
	$retArray = array();

	$view = views_get_view($view_name);
	$view -> set_display($display);
	$view -> set_arguments($args);
	$view -> execute();

	foreach ($view->result as $record) {
		$retArray[] = $record -> nid;
	}
	return $retArray;
}

function _get_records_from_views($view_name, $display, $args) {

	$view = views_get_view($view_name);
	$view -> set_display($display);
	$view -> set_arguments($args);
	$view -> execute();

	return $view -> result;
}

function _get_records_from_views_by_label($view_name, $display, $args, $req_labels) {
	$retArray = array();

	$view = views_get_view($view_name);
	$view -> set_display($display);
	$view -> set_arguments($args);
	$view -> execute();

	foreach ($view->result as $record) {
		$tmpRecord = array();
		foreach ($req_labels as $key => $value) {
			$tmpRecord[$key] = view_get_field_value_by_label($view, $value, $record);
		}
		$retArray[] = $tmpRecord;
	}
	return $retArray;
}

function session_get($session_name, $default = NULL) {
	if (isset($_SESSION[$session_name])) {
		return $_SESSION[$session_name];
	}
	return $default;
}

function session_set($session_name, $session_value) {
	$_SESSION[$session_name] = $session_value;
}

function field_instance_copy() {
	$field = field_info_instance('taxonomy_term', 'field_default_fieldset', 'tpl_default_tree_mobile_main_prepaid');
	$voca_names = taxonomy_vocabulary_get_names();
	foreach ($voca_names as $key => $value) {
		if (strncmp($key, 'tpl_default_tree', 16) == 0) {

			if (($key != 'tpl_default_tree_mobile_main_prepaid') && ($key != 'tpl_default_tree_mobile_main_postpaid') && ($key != 'tpl_default_tree_cross_main')) {
				$field_instance = array('field_name' => $field['field_name'], 'entity_type' => 'taxonomy_term', 'bundle' => $key, 'label' => $field['label'], 'description' => $field['description'], 'widget' => $field['widget'], );
				field_create_instance($field_instance);
			}
		}
	}
}

function get_voca_list_machine_names() {
	$voca_list = taxonomy_get_vocabularies();

	$temp = array();
	foreach ($voca_list as $voca) {
		if (strncasecmp($voca -> name, "tpl_default", 11) == 0) {
			$temp[] = strtolower($voca -> name);
		}
	}
	return $temp;
}

function remove_service_domain_from_voca() {

	$tpl_list = get_voca_list_machine_names();

	$domain_list = array('mobile', 'broadband', 'iptv', 'voip', 'cross', 'satellite', 'dummy');

	foreach ($tpl_list as $tpl) {
		$voca = taxonomy_vocabulary_machine_name_load($tpl);
		$terms = taxonomy_get_tree($voca -> vid);

		foreach ($terms as $term) {
			$termDetail = taxonomy_term_load($term -> tid);
			if (!empty($termDetail -> field_rel_type)) {

				if ($termDetail -> field_rel_type['und'][0]['value'] == 'nonusage_fee_recurring') {
					$termDetail -> field_rel_type['und'][0]['value'] == 'nonusage_recurring_charge';
					field_attach_update('taxonomy_term', $termDetail);
					// taxonomy_term_save($termDetail);
				}

				if ($termDetail -> field_rel_type['und'][0]['value'] == 'nonusage_voucher') {
					$termDetail -> field_rel_type['und'][0]['value'] == 'nonusage_recharge_voucher';
					field_attach_update('taxonomy_term', $termDetail);

					// taxonomy_term_save($termDetail);
				}

				/*
				 $typeDetail = explode('_', $termDetail->field_rel_type['und'][0]['value']);
				 if( in_array($typeDetail[0], $domain_list )) {
				 array_shift($typeDetail);
				 }
				 $termDetail->field_rel_type['und'][0]['value'] = join('_', $typeDetail);
				 taxonomy_term_save($termDetail);
				 */

			}
		}
	}
}

function _get_redirect_url_in_list_all($content_type, $params) {
	$url = array();
	$url = _get_redirect_url_in_create_n_list('list', $content_type, $params);

	return $url;
}

function _get_redirect_url_in_create($content_type, $params) {
	$url = array();

	$url = _get_redirect_url_in_create_n_list('add', $content_type, $params);

	return $url;
}

function _get_redirect_url_in_delete($node) {
	$url = array();
	$url = _get_redirect_url_in_view_n_delete('del', $node);
	return $url;
}

function _get_custom_page_in_pcatalog($node) {
	$url = array();
	$url = _get_redirect_url_in_view_n_delete('view', $node);
	return $url;
}

function _get_redirect_url_in_view_n_delete($viewOrDel, $node) {
	$url = array();
	switch($node->type) {
		case 'simpleproductoffering' :
			$serviceDomain = taxonomy_term_load($node -> field_service_type_of_provider['und'][0]['tid']);
			$productType = taxonomy_term_load($node -> field_product_type['und'][0]['tid']);

			if ($viewOrDel == 'view') {
				$url['path'] = 'product_designer/' . $serviceDomain -> name . '/' . $productType -> name . '/edit/' . $node -> nid;
			} else {
				$url['path'] = 'product_designer/' . $serviceDomain -> name . '/' . $productType -> name . '/list';
			}

			$fragment = array('Mobile' => array('Main' => '', 'Additional' => 'quickset-products_with_cug=1', 'VAS' => 'quickset-products_with_cug=2', 'Package' => 'quickset-products_with_cug=3', 'CUG' => 'quickset-products_with_cug=4'), 'IPTV' => array('Main' => '', 'Additional' => 'quickset-products=1', 'VAS' => 'quickset-products=2', 'Package' => 'quickset-products=3'), 'Broadband' => array('Main' => '', 'Additional' => 'quickset-products=1', 'VAS' => 'quickset-products=2', 'Package' => 'quickset-products=3'), 'VoIP' => array('Main' => '', 'Additional' => 'quickset-products_with_cug=1', 'VAS' => 'quickset-products_with_cug=2', 'Package' => 'quickset-products_with_cug=3', 'CUG' => 'quickset-products_with_cug=4'), 'Satellite' => array('Main' => '', 'Additional' => 'quickset-products=1', 'VAS' => 'quickset-products=2', 'Package' => 'quickset-products=3'), 'Dummy' => array('Main' => '', 'Additional' => 'quickset-products=1', 'VAS' => 'quickset-products=2', 'Package' => 'quickset-products=3'), 'Cross' => array('Main' => '', 'Additional' => 'quickset-products=1', 'VAS' => 'quickset-products=2', 'Package' => 'quickset-products=3'), );
			$url['fragment'] = $fragment[$serviceDomain -> name][$productType -> name];

			break;

		case 'counter' :
			$counterType = taxonomy_term_load($node -> field_counter_type['und'][0]['tid']);

			if ($viewOrDel == 'view') {
				$url['path'] = 'common/counter/edit/' . $counterType -> name . '/' . $node -> nid;
			} else {
				$url['path'] = 'common/counter/' . $counterType -> name . '/list';
			}

			$fragment = array('Basic' => '', 'Optional' => 'quickset-counters=1', 'Rollover' => 'quickset-counters=2');
			$url['fragment'] = $fragment[$counterType -> name];
			break;

		case 'numberingplan_domestic' :
			if ($viewOrDel == 'view') {
				$url['path'] = 'common/numberingplan/domestic/' . $node -> nid . '/ratinggroup';
			} else {
				$url['path'] = 'common/numberingplan/domestic/list';
			}
			$url['fragment'] = '';
			break;

		case 'number_special' :
			if ($viewOrDel == 'view') {
				$url['path'] = 'common/numberingplan/' . $node -> type . '/' . $node -> nid;
			} else {
				$url['path'] = 'common/numberingplan/' . $node -> type . '/list';
			}
			$url['fragment'] = 'quickset-numbering_plan=3';
			break;

		case 'numberingplan_idd' :
			if ($viewOrDel == 'view') {
				$url['path'] = 'common/numberingplan/idd/' . $node -> nid . '/ratinggroup';
			} else {
				$url['path'] = 'common/numberingplan/idd/list';
			}
			$url['fragment'] = 'quickset-numbering_plan=1';
			break;

		case 'vouchercardtype' :
			if ($viewOrDel == 'view') {
				$url['path'] = 'common/vouchercardtype/edit/' . $node -> nid;
			} else {
				$url['path'] = 'common/vouchercardtype/list';
			}
			$url['fragment'] = '';
			break;

		case 'timetable' :
			if ($viewOrDel == 'view') {
				$url['path'] = 'common/numberingplan/' . $node -> type . '/' . $node -> nid . '/timetablefactors';
			} else {
				$url['path'] = 'common/numberingplan/' . $node -> type . '/list';
			}
			$url['fragment'] = 'quickset-numbering_plan=2';
			break;

		case 'carrier_mobile' :
			if ($viewOrDel == 'view') {
				$url['path'] = 'common/numberingplan/' . $node -> type . '/' . $node -> nid;
			} else {
				$url['path'] = 'common/numberingplan/' . $node -> type . '/list';
			}
			$url['fragment'] = 'quickset-numbering_plan=4';
			break;

		case 'area_code' :
			if ($viewOrDel == 'view') {
				$url['path'] = 'common/numberingplan/' . $node -> type . '/' . $node -> nid;
			} else {
				$url['path'] = 'common/numberingplan/' . $node -> type . '/list';
			}
			$url['fragment'] = 'quickset-numbering_plan=5';
			break;

		case 'productgroup' :
			if ($viewOrDel == 'view') {
				$url['path'] = 'relation/' . $node -> type . '/edit/' . $node -> nid . '/0';
			} else {
				$url['path'] = 'relation/' . $node -> type . '/list';
			}
			$url['fragment'] = 'quickset-relation_manager=5';
			break;

		case 'productchange' :
			if ($viewOrDel == 'view') {
				$url['path'] = 'relation/' . $node -> type . '/edit/' . $node -> nid . '/0';
			} else {
				$url['path'] = 'relation/' . $node -> type . '/list';
			}
			$url['fragment'] = 'quickset-relation_manager=6';
			break;

		case 'roaming_country' :
		case 'roaming_carrier' :
		case 'roaming_plan' :
		case 'roaming_zone':
			$fragments = array('roaming_country' => '', 'roaming_carrier' => 'quickset-roaming=1','roaming_zone' => 'quickset-roaming=2', 'roaming_plan' => 'quickset-roaming=3');

			$tempArr = explode('_', $node -> type);
			if ($viewOrDel == 'view') {
				$url['path'] = 'common/' . join('/', $tempArr) . '/' . $node -> nid;
				if ($node -> type == 'roaming_plan')
					$url['path'] .= '/ratinggroup';

			} else {
				$url['path'] = 'common/' . join('/', $tempArr) . '/list';
			}
			$url['fragment'] = $fragments[$node -> type];
			break;

		case 'depositscheme' :
		case 'thresholdscheme' :
		case 'unittransfer' :
			$fragments = array('depositscheme' => 'quickset-qtabs_common_data=2', 'thresholdscheme' => 'quickset-qtabs_common_data=3', 'unittransfer' => 'quickset-qtabs_common_data=1');

			if ($viewOrDel == 'view') {
				$url['path'] = 'common/' . $node -> type . '/' . $node -> nid;
			} else {
				$url['path'] = 'common/' . $node -> type . '/list';
			}
			$url['fragment'] = $fragments[$node -> type];
			break;

		case 'packetpredefinedchargingrule' :
		case 'packetdynamicchargingrule' :
		case 'packetdynamicl4' :
		case 'packetsgsn' :
		case 'packetsgsnip' :
			$paths = array('packetpredefinedchargingrule' => 'packet/predefined/charging_rule', 'packetdynamicchargingrule' => 'packet/dynamic/charging_rule', 'packetdynamicl4' => 'packet/dynamic/l4', 'packetsgsn' => 'packet/sgsn', 'packetsgsnip' => 'packet/sgsnip');
			$fragments = array('packetpredefinedchargingrule' => '', 'packetdynamicchargingrule' => 'quickset-packet=1', 'packetdynamicl4' => 'quickset-packet=2', 'packetsgsn' => 'quickset-packet=3', 'packetsgsnip' => 'quickset-packet=4');

			if ($viewOrDel == 'view') {
				$url['path'] = 'common/' . $paths[$node -> type] . '/' . $node -> nid;
			} else {
				$url['path'] = 'common/' . $paths[$node -> type] . '/list';
			}
			$url['fragment'] = $fragments[$node -> type];
			break;
	}

	return $url;
}

// $createOrList = 'add', 'list'
//
function _get_redirect_url_in_create_n_list($addOrList, $content_type, $params) {
	$url = array();

	switch($content_type) {
		case 'simpleproductoffering' :
			$tempArray = explode('/', $params);

			$url['path'] = 'product_designer/' . join('/', $tempArray) . '/' . $addOrList;

			$serviceDomain = $tempArray[0];
			$productType = $tempArray[1];

			$fragment = array('Mobile' => array('Main' => '', 'Additional' => 'quickset-products_with_cug=1', 'VAS' => 'quickset-products_with_cug=2', 'Package' => 'quickset-products_with_cug=3', 'CUG' => 'quickset-products_with_cug=4'), 'IPTV' => array('Main' => '', 'Additional' => 'quickset-products=1', 'VAS' => 'quickset-products=2', 'Package' => 'quickset-products=3'), 'Broadband' => array('Main' => '', 'Additional' => 'quickset-products=1', 'VAS' => 'quickset-products=2', 'Package' => 'quickset-products=3'), 'VoIP' => array('Main' => '', 'Additional' => 'quickset-products_with_cug=1', 'VAS' => 'quickset-products_with_cug=2', 'Package' => 'quickset-products_with_cug=3', 'CUG' => 'quickset-products_with_cug=4'), 'Satellite' => array('Main' => '', 'Additional' => 'quickset-products=1', 'VAS' => 'quickset-products=2', 'Package' => 'quickset-products=3'), 'Dummy' => array('Main' => '', 'Additional' => 'quickset-products=1', 'VAS' => 'quickset-products=2', 'Package' => 'quickset-products=3'), 'Bundle' => array('Main' => '', 'Additional' => 'quickset-products=1', 'VAS' => 'quickset-products=2', 'Package' => 'quickset-products=3'), );

			$url['fragment'] = $fragment[$serviceDomain][$productType];
			break;
		case 'counter' :
			$url['path'] = 'common/counter/' . $addOrList . '/' . $params;
			$fragment = array('Basic' => '', 'Optional' => 'quickset-counters=1', 'Rollover' => 'quickset-counters=2');
			$url['fragment'] = $fragment[$params];
			break;
		case 'numberingplan_domestic' :
			$url['path'] = 'common/numberingplan/domestic/' . $addOrList;
			$url['fragment'] = '';
			break;
		case 'numberingplan_idd' :
			$url['path'] = 'common/numberingplan/idd/' . $addOrList;
			$url['fragment'] = 'quickset-numbering_plan=1';
			break;

		case 'timetable' :
		case 'number_special' :
		case 'carrier_mobile' :
		case 'area_code' :
			$fragments = array('timetable' => 'quickset-numbering_plan=2', 'number_special' => 'quickset-numbering_plan=3', 'carrier_mobile' => 'quickset-numbering_plan=4', 'area_code' => 'quickset-numbering_plan=5', );
			$url['path'] = 'common/numberingplan/' . $content_type . '/' . $addOrList;
			$url['fragment'] = $fragments[$content_type];
			break;

		case 'thresholdscheme' :
		case 'depositscheme' :
		case 'vouchercardtype' :
		case 'unittransfer' :
			$fragments = array('vouchercardtype' => '', 'unittransfer' => 'quickset-qtabs_common_data=1', 'depositscheme' => 'quickset-qtabs_common_data=2', 'thresholdscheme' => 'quickset-qtabs_common_data=3');
			$url['path'] = 'common/' . $content_type . '/' . $addOrList;
			$url['fragment'] = $fragments[$content_type];
			break;

		case 'roaming_country' :
		case 'roaming_carrier' :
		case 'roaming_plan' :
    case 'roaming_zone':
			$fragments = array('roaming_country' => '', 'roaming_carrier' => 'quickset-roaming=1', 'roaming_zone' => 'quickset-roaming=2', 'roaming_plan' => 'quickset-roaming=3');

			$tempArr = explode('_', $content_type);
			$url['path'] = 'common/' . join('/', $tempArr) . '/' . $addOrList;
			$url['fragment'] = $fragments[$content_type];
			break;

		case 'productgroup' :
			$fragments = array('productgroup' => 'quickset-relation_manager=5');
			$url['path'] = 'relation/' . $content_type . '/' . $addOrList;
			$url['fragment'] = $fragments[$content_type];
			break;

		case 'productchange' :
			$fragments = array('productchange' => 'quickset-relation_manager=6');
			$url['path'] = 'relation/' . $content_type . '/' . $addOrList;
			$url['fragment'] = $fragments[$content_type];
			break;

		case 'packetpredefinedchargingrule' :
		case 'packetdynamicchargingrule' :
		case 'packetdynamicl4' :
		case 'packetsgsn' :
		case 'packetsgsnip' :
			$paths = array('packetpredefinedchargingrule' => 'packet/predefined/charging_rule', 'packetdynamicchargingrule' => 'packet/dynamic/charging_rule', 'packetdynamicl4' => 'packet/dynamic/l4', 'packetsgsn' => 'packet/sgsn', 'packetsgsnip' => 'packet/sgsnip');
			$fragments = array('packetpredefinedchargingrule' => '', 'packetdynamicchargingrule' => 'quickset-packet=1', 'packetdynamicl4' => 'quickset-packet=2', 'packetsgsn' => 'quickset-packet=3', 'packetsgsnip' => 'quickset-packet=4');

			$url['path'] = 'common/' . $paths[$content_type] . '/' . $addOrList;
			$url['fragment'] = $fragments[$content_type];
			break;
	}
	//dsm($url, 'url create n list');
	return $url;
}

function set_permissions_all_checked() {
	$allRoles = array('product designer', 'relation manager', 'lifecycle manager', 'common data manager', 'simulator', 'ocs manager', 'account manager');

	foreach ($allRoles as $role) {
		$user = user_role_load_by_name($role);
		user_role_grant_permissions($user -> rid, array_keys(module_invoke_all('permission')));
	}
}

function _tmp_create_prdattributedepositamount($productNid) {
	global $user;

	$productNode = node_load($productNid);
	$vocaName = _get_vocabulary_name('simpleproductoffering', $productNode);
	$term = current(taxonomy_get_term_by_name('Deposit Amount', $vocaName));

	$node = new StdClass();
	$node -> uid = $user -> uid;
	$node -> language = 'und';
	$node -> type = 'prdattributedeposit';
	$node -> field_ref_tree_tid['und'][0]['value'] = $term -> tid;
	$node -> field_ref_product['und'][0]['nid'] = $productNid;

	node_save($node);
}

function is_integer_string($value) {
	if (!is_numeric($value)) {
		return FALSE;
	}

	$value2 = (int)$value;
	if ($value2 != $value) {
		return FALSE;
	}
	return TRUE;
}

function is_integer_between_range($value) {
	$MAX_INT_VALUE = 1000000000;
	$MIN_INT_VALUE = -10000000000;

	if ($value < $MIN_INT_VALUE) {
		return -1;
	} elseif ($value > $MAX_INT_VALUE) {
		return 1;
	} else {
		return 0;
	}

}

// 특정 아이템을 bulk로 입력함.
function _tmp_create_prdattributepackaged($productNid) {
	global $user;

	$productNode = node_load($productNid);

	$node = new StdClass();
	$node -> uid = $user -> uid;
	$node -> language = 'und';
	$node -> type = 'prdattributepackaged';
	$node -> field_ref_product['und'][0]['nid'] = $productNid;
	$node -> field_ref_tree_tid['und'][0]['value'] = 6537;
	// hidden
	$node -> field_ref_prdrelationtype['und'][0]['tid'] = 788;
	// packaged hidden
	$node -> field_ref_connected_product['und'][0]['nid'] = 130504;
	// Bonud On Recharge

	node_save($node);
}

//field 삭제
function delete_field($fields) {
	foreach ($fields as $field_name) {
		field_delete_field($field_name);
	}

	/*
	 $fields = array('field_can_be_overidden',
	 'field_char_relationship_type',
	 'field_char_spec_seq',
	 'field_custom_value',
	 'field_default',
	 'field_derivation_formula',
	 'field_extensible',
	 'field_id',
	 'field_is_group_call',
	 'field_lower_limit',
	 'field_max_amount_of_sms',
	 'field_max_cardinality',
	 'field_min_cardinality',
	 'field_offering_rel_type',
	 'field_package',
	 'field_r_bundledprodofferoption',
	 'field_r_prodcharvalueref',
	 'field_r_prodspeccharrelationship',
	 'field_r_prodspeccharvalue',
	 'field_r_prodspeccharvaluerel',
	 'field_r_productofferingprice',
	 'field_r_productspecchar',
	 'field_range_interval',
	 'field_ref_productattribute',
	 'field_start_date',
	 'field_unique',
	 'field_unit_of_measure',
	 'field_upper_limit',
	 'field_value_from',
	 'field_value_to',
	 'field_value_type');
	 */
}
