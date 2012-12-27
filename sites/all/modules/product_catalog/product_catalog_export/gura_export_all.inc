<?php
function rating_rules_export_all()
{
	$jsonData = rating_rules_export_by_content_type('rating_rule_export',  array());

    return json_encode($jsonData);
}

function rating_rules_export_by_content_type_loaded($export_list, $nid=NULL, $vars = array(), &$export_item_cache = array())
{
	$jsonData = array();
    foreach($export_list as $export_item)
	{
        if(property_exists($export_item , "field_export_disabled") && count($export_item->field_export_disabled)>0)
        {
            if($export_item->field_export_disabled['und'][0]['value'] == '1')
                continue;
            //dsm($export_item->field_export_disabled);
		}

        if(property_exists($export_item, "field_source_view_name") && count($export_item->field_source_view_name)>0)
        {
            $data = rating_rules_export_from_view_has_nid_reference($export_item->title, $export_item, $export_item->field_source_view_name['und'][0]['value'] , $export_item->field_source_display_name['und'][0]['value'] , $export_item->field_result_ruleset_name['und'][0]['value'], $vars, $export_item_cache);
            foreach($data as $d)
            {
                if(array_key_exists('object_name', $d))
                {
                    $obj_name = $d["object_name"];
                    unset($d["object_name"]);
                    $jsonData[$obj_name] = $d;
                }
                else
                {
                    $jsonData[] = $d;
                }
            }
        }
        else
        {
            $ruleset_name = $export_item->title;
            if(count($export_item->field_result_ruleset_name)>0)
            {
                $ruleset_name = $export_item->field_result_ruleset_name['und'][0]['value'];
            }
            $d = rating_rule_export($ruleset_name, $export_item, $nid, $vars, $export_item_cache);
            if(array_key_exists('object_name', $d))
            {
                $obj_name = $d["object_name"];
                unset($d["object_name"]);
                $jsonData[$obj_name] = $d;
            }
            else
            {
                $jsonData[] = $d;
            }
        }
    }

    return $jsonData;
}

function rating_rules_export_by_content_type_and_item_name($type_name, $item_name, $nid=NULL, $vars = array(), &$export_item_cache = array())
{
	if(array_key_exists($type_name , $export_item_cache))
	{
		$export_list = $export_item_cache[$type_name];
	}
	else
	{
		$export_list = node_load_multiple(array(), array('type' => $type_name));
		$export_item_cache[$type_name] = $export_list;
	}

	$item_list = array();
	foreach($export_list as $export_item)
	{
		if($export_item->title == $item_name)
		{
			$item_list[] = $export_item;
		}
	}
	return rating_rules_export_by_content_type_loaded($item_list , $nid, $vars, $export_item_cache);
}

function rating_rules_export_by_content_type($type_name, $nid=NULL, $vars = array(), &$export_item_cache = array())
{

	if(array_key_exists($type_name , $export_item_cache))
	{
		$export_list = $export_item_cache[$type_name];
	}
	else
	{
		$export_list = node_load_multiple(array(), array('type' => $type_name));
		$export_item_cache[$type_name] = $export_list;
	}
	return rating_rules_export_by_content_type_loaded($export_list , $nid, $vars, $export_item_cache);
}

function rating_rule_export($ruleset_template , $export_item,  $nid=NULL, $vars = array(), &$export_item_cache = array())
{
    $ruleset_name = $ruleset_template;
    foreach($vars as $var_name => $value)
    {
        $ruleset_name = str_replace('$(' . $var_name . ')' , $value , $ruleset_name);
    }


    if(property_exists($export_item, "field_children_node_type") && count($export_item->field_children_node_type)>0)
    {
        $export_type = 'group';
        if(property_exists($export_item, "field_children_export_type") && count($export_item->field_children_export_type)>0)
        {
            $export_type = $export_item->field_children_export_type['und'][0]['value'];
        }
        $jsonData = array('type' => $export_type , 'title' => $ruleset_name, 'object_name' => $ruleset_name);
        /*
        if($nid!=NULL)
        {
            $jsonData['nid'] = $nid;
        }
        */
        foreach($vars as $var_name => $value)
        {
            $jsonData[$var_name] = $value;
        }
        
        $children = rating_rules_export_by_content_type($export_item->field_children_node_type['und'][0]['value'], $nid, $vars, $export_item_cache);
        foreach($children as $title => $child)
        {
            $jsonData[$title] = $child;
        }
		//$jsonData['data'] = rating_rules_export_by_content_type($export_item->field_children_node_type['und'][0]['value'], $nid, $vars);
        return $jsonData;
    }
    else
    {
        if(count($export_item->field_view_name)>0)
        {
			$individual_ruleset = true;
			if(property_exists($export_item , 'field_individual_ruleset') && count($export_item->field_individual_ruleset)>0)
			{
				if($export_item->field_individual_ruleset['und'][0]['value'] == '0')
					$individual_ruleset = false;
			}

            $display_name = NULL;
            if(count($export_item->field_display_name)>0)
            {
                $display_name = $export_item->field_display_name['und'][0]['value'];
            }
            $data = rating_rules_export_from_view($ruleset_name, $export_item->field_view_name['und'][0]['value'] , $display_name, $nid);
			$data['individual_ruleset'] = $individual_ruleset;
			if(property_exists($export_item , 'field_export_target') && count($export_item->field_export_target)>0)
			{
				$data['export_target'] = $export_item->field_export_target['und'][0]['value'];
			}
			return $data;
		}
		return NULL;
    }
}


function rating_rules_export_from_view_has_nid_reference($title , $export_item , $source_view_name , $source_display_name , $ruleset_template, $vars = array(), &$export_item_cache = array())
{
    $ret = array();
    $view = views_get_view($source_view_name);
    $view->set_display($source_display_name);
    $view->execute();
    //dsm($view);
    foreach($view->field as $field_name => $field_handler)
    {
        $field = $field_handler->options;
        $splits = preg_split('/,/', $field['label']);
        $factor_name = trim($splits[0]);
        $field_name_map[$field_name] = $factor_name;
    }

    foreach($view->result as $row_id => $record)
    {
        $nid = -1;
        $sub_vars = array();
        foreach($vars as $var_name => $value)
        {
            $sub_vars[$var_name] = $value;
        }
        foreach($view->field as $field_name => $field_handler)
        {
			$value = view_get_field_value($view , $field_name , $record);
			if($field_name == 'nid')
			{
				$nid = $value;
			}
            $sub_vars[$field_name_map[$field_name]] = $value;
        }

        $data = rating_rule_export($ruleset_template , $export_item , $nid, $sub_vars, $export_item_cache);
        $ret[] = $data;
    }
    return $ret;
}

function array_to_paren_comma_list($arr)
{
	if(count($arr) > 1)
	{
		return '(' . join(',',$arr) . ')';
	}
	else
	{
		return join(',',$arr);
	}
}

function to_rating_conditions($value , $user_data)
{
	return $user_data['factor_name'] . ' '  . $user_data['op'] . ' ' . $value;
}

function array_apply(&$arr , $funcname, $user_data = NULL)
{
	foreach($arr as $k => $v)
	{
		$arr[$k] = $funcname($v, $user_data);	
	}
}
function dash_date_to_nondash_date_string($d)
{
	return substr($d, 0,4). substr($d , 5 , 2) . substr($d , 8 , 2);
}

function to_rating_rule_string($value)
{
	if(strstr($value, ' ') != FALSE)
	{
		return '\'' . $value . '\'';
	}
	else if(strstr($value, ':') != FALSE)
	{
		return '\'' . $value . '\'';
	}
	return $value;
}

function get_rating_factor_values_from_drupal_field($obj , $field_name_arr)
{
	$ret = array();
	foreach($field_name_arr as $field_name)
	{
		$temp = $obj->$field_name;
		foreach($temp['und'] as $und)
		{
			$value = NULL;
			if(array_key_exists('nid' , $und))
			{
				$nid = $und['nid'];
				$value = $nid;
			}
			else if(array_key_exists('tid' , $und))
			{
				$tid = $und['tid'];
				$taxo = taxonomy_term_load($tid);
				$value = $taxo->name;
				if(property_exists($taxo , 'field_common_code'))
				{
					dsm($taxo);
					$temp = get_drupal_field_values($taxo , 'field_common_code');
					$value = $temp[0];
					dsm($value);
				}
				if(property_exists($taxo , 'field_rating_operation_code'))
				{
					$temp = get_drupal_field_values($taxo , 'field_rating_operation_code');
					$value = $temp[0];
				}
			}
			else
			{
				$value = $und['value'];
			}
			if(array_key_exists('date_type', $und) && $und['date_type'] =='datetime' )
			{
				$value = dash_date_to_nondash_date_string($und['value']);
			}
			if($value!=NULL)
			{
				$ret[] = $value;
			}
		}
	}
	return $ret;
}

function get_drupal_field_values($obj , $field_name)
{
	$ret = array();
	$temp = $obj->$field_name;
	foreach($temp['und'] as $und)
	{
		$ret[] = $und['value'];
	}
	return $ret;
}

function get_drupal_field_refs($obj , $field_name)
{
	$ret = array();
	$temp = $obj->$field_name;
	if(array_key_exists('und' , $temp))
	{
		foreach($temp['und'] as $und)
		{
			if(array_key_exists('nid' , $und))
			{
				$nid = $und['nid'];
				$ret[] = node_load($nid);
			}
			else
			{
				$nid = $und['raw']['nid'];
				if(array_key_exists('node' , $und['raw']))
				{
					$ret[] = $und['raw']['node'];
				}
				else
				{
					$ret[] = node_load($nid);
				}
			}
		}
	}
	else
	{
		foreach($temp as $und)
		{
			if(array_key_exists('nid' , $und))
			{
				$nid = $und['nid'];
				$ret[] = node_load($nid);
			}
			else
			{
				$nid = $und['raw']['nid'];
				if(array_key_exists('node' , $und['raw']))
				{
					$ret[] = $und['raw']['node'];
				}
				else
				{
					$ret[] = node_load($nid);
				}
			}
		}
	}
	return $ret;
}

function get_drupal_field_tids($obj , $field_name)
{
	$ret = array();
	$temp = $obj->$field_name;
	//dsm($field_name);
	//dsm($temp);
	foreach($temp['und'] as $und)
	{
		$tid = $und['tid'];
		$ret[] = taxonomy_term_load($tid);
	}
	return $ret;
}

function generate_condition_json_by_condition_node($nid)
{
	$ret = array();
    $node = node_load($nid);
	$types = node_load_multiple(array(), array('type' => 'rating_factor_conversion' , 'title'=>$node->type)); 
	if(count($types)>0)
	{
		foreach($types as $type)
		{
			$newfunc = create_function('$data', $type->field_conversion_php_code['und'][0]['value'] );
			$value = $newfunc($node);
			$ret[$type->field_rating_factor_name['und'][0]['value']] = array('op' => $type->field_rating_factor_op['und'][0]['value'] , 'value' => $value);
		}
	}
	return $ret;
	//return 'unkown node type '.$node->type;
}


function generate_condition_json_from_or_node($nid)
{
    $node = node_load($nid);
	$ret = array();
	if($node->type=='conditioncommonor')
	{
		$ret['op'] = 'or';
		$ret['conditions'] = array();
	}
	else if($node->type == 'conditioncommonand')
	{
		$ret['op'] = 'and';
		$ret['conditions'] = array();
	}
	$viewData = get_viewdata('query_tree_by_root_nid', $nid);
	foreach($viewData as $record)
	{
		if($node->type=='conditioncommonor')
		{
			$temp = generate_condition_json_from_or_node($record['nid']);
			if(count($temp)>0)
			{
				$ret['conditions'][] = $temp;
			}
		}
		else if($node->type == 'conditioncommonand')
		{
			$temp = generate_condition_json_by_condition_node($record['nid']);
			if(count($temp)>0)
			{
				$ret['conditions'][] = $temp;
			}
		}
		else
		{
			$ret = generate_condition_json_by_condition_node($record['nid']);
		}
	}
	if($node->type=='conditioncommonor' || $node->type == 'conditioncommonand')
	{
		if(count($ret['conditions'])>0)
			return $ret;
		return array();
	}
	return $ret;
}

function generate_condition_json_from_tree_node($nid)
{
    $node = node_load($nid);
	$ret = array();
	$ret['op'] = 'or';
	$ret['conditions'] = array();
	$viewData = get_viewdata('query_tree_by_root_nid', $nid);
	foreach($viewData as $record)
	{
		$temp = generate_condition_json_from_or_node($record['nid']);
		if(count($temp)>0)
		{
			$ret['conditions'][] = $temp;
		}
	}
	if(count($ret['conditions'])>0)
		return $ret;
	return null;
}

function generate_condition_string_by_condition_node($nid, &$factor_list )
{
    $node = node_load($nid);
	$types = node_load_multiple(array(), array('type' => 'rating_factor_conversion' , 'title'=>$node->type)); 
	if(count($types)>0)
	{
		foreach($types as $type)
		{
			if(array_key_exists('und' , $type->field_rating_factor_name) && count($type->field_rating_factor_name['und'])>0)
			{
				$factor_list[$type->field_rating_factor_name['und'][0]['value']] = $type;
				$value = NULL;

				if(array_key_exists('und' , $type->field_value) && count($type->field_value['und'])>0)
				{
					$drupal_field_name = get_drupal_field_values($type , "field_value");
					//dsm($node);
					$value = get_rating_factor_values_from_drupal_field($node , $drupal_field_name);
				}
				else
				{
					$newfunc = create_function('$data', $type->field_conversion_php_code['und'][0]['value'] );

					if($newfunc == NULL)
					{
						dsm($type->field_conversion_php_code['und'][0]['value']);
						return NULL;
					}
					$value = $newfunc($node);
				}

				if(is_array($value))
				{
					$o = '';
					$factor_name = $type->field_rating_factor_name['und'][0]['value'];

					$op = '=';

					if(property_exists($node, 'field_rating_operation'))
					{
						$temp = get_drupal_field_tids($node , 'field_rating_operation');
						$tid_node = $temp[0];
						$temp = get_drupal_field_values($tid_node , 'field_rating_operation_code');
						$op = $temp[0];
					}
					else if(property_exists($node, 'field_rating_operation_for_date'))
					{
						$temp = get_drupal_field_tids($node , 'field_rating_operation_for_date');
						$tid_node = $temp[0];
						$temp = get_drupal_field_values($tid_node , 'field_rating_operation_code');
						$op = $temp[0];
					}
					else
					{
						$op = $type->field_rating_factor_op['und'][0]['value'];
					}
					if($op == '=' || $op == 'starts' || $op == 'ends')
					{
						array_apply($value , 'to_rating_rule_string');
						return $factor_name . ' ' . $op . ' ' . join(',' , $value);
					}
					else if($op == 'between')
					{
						/*
						array_apply($value , 'to_rating_rule_string');
						return $factor_name . ' ' . $op . ' ' . join(',' , $value);
						 */
						if(count($value) == 2)
						{
							array_apply($value , 'to_rating_rule_string');
							return $factor_name . ' ' . $op . ' ' . join(',' , $value);
						}
						else if(count($value) >=4)
						{
							array_apply($value , 'to_rating_rule_string');
							$condstr = "(";
							for($i = 0;$i<count($value);$i=$i+2)
							{
								if($i!=0)
									$condstr = $condstr . " or ";
								$condstr = $condstr . $factor_name . ' ' . $op . ' ' . $value[$i] . ',' . $value[$i+1];
							}
							return $condstr . ")";
						}
					}
					else
					{
						if(count($value)==1)
						{
							array_apply($value , 'to_rating_rule_string');
							return $factor_name . ' ' . $op . ' ' . join(',' , $value);
						}
						else
						{
							array_apply($value , 'to_rating_conditions', array("factor_name" => $factor_name , "op" => $op) );

							return '(' . join(' or ', $value) . ')' ;
						}
					}
				}
				else
				{
					$op = '=';

					if(property_exists($node, 'field_rating_operation'))
					{
						$temp = get_drupal_field_tids($node , 'field_rating_operation');
						$tid_node = $temp[0];
						$temp = get_drupal_field_values($tid_node , 'field_rating_operation_code');
						$op = $temp[0];
					}
					else
					{
						$op = $type->field_rating_factor_op['und'][0]['value'];
					}

					$value = to_rating_rule_string($value);
					return $type->field_rating_factor_name['und'][0]['value'] . ' ' . $op . ' ' . $value;
				}
			}
			else
			{
				//$factor_list[$type->field_rating_factor_name['und'][0]['value']] = $type;
				$newfunc = create_function('$data', $type->field_conversion_php_code['und'][0]['value'] );
				if($newfunc!=NULL)
				{
					$value = $newfunc($node);

					$factor_list[$value[0]['label']] = $value[0];
					return $value[1];
				}
				else
				{
					dsm($type->field_conversion_php_code['und'][0]['value']);
				}
				return NULL;
			}
		}
	}
    dsm($node);
	return 'unknown node type '.$node->type;
}


function generate_condition_string_from_or_node($nid, &$factor_list)
{
    $node = node_load($nid);
	$viewData = get_viewdata('query_tree_by_root_nid', $nid);
	if($node->type=='conditioncommonor')
	{
		$ret=array();
		foreach($viewData as $record)
		{
			$temp = generate_condition_string_from_or_node($record['nid'], $factor_list);
			if($temp!=null && $temp!='')
			{
				$ret[] = $temp;
			}
		}
		return $ret;
	}
	else if($node->type == 'conditioncommonand')
	{
		$ret = '';
		foreach($viewData as $record)
		{
			$temp = generate_condition_string_by_condition_node($record['nid'], $factor_list);
			if($temp!=null && $temp!='')
			{
				if($ret == '')
					$ret = $temp;
				else
					$ret = $ret . " and " . $temp;
			}
		}
		return $ret;
	}
	else
	{
		$ret=array();
		foreach($viewData as $record)
		{
			$temp = generate_condition_string_by_condition_node($record['nid'], $factor_list);
			if($temp!=null && $temp!='')
			{
				$ret[] = $temp;
			}
		}
		return $ret;
	}
	return null;
}

function generate_condition_string_from_tree_node($nid)
{
    $node = node_load($nid);
	$ret = array();
    $factor_list = array();
	$viewData = get_viewdata('query_tree_by_root_nid', $nid);
	foreach($viewData as $record)
	{
		$temp = generate_condition_string_from_or_node($record['nid'], $factor_list);
		if($temp!=null && $temp!='')
		{
			$ret[] = $temp;
		}
	}
	if(count($ret)>0)
    {
        $j = array();
        $j['factors'] = array();
        foreach($factor_list as $factor_name => $factor)
        {
            $j['factors'][] = $factor_name;
        }
        $j['condition'] = $ret;
		return $j;
    }
	return null;
}

function view_get_field_value_by_label($view , $label , $record)
{
    foreach($view->field as $field_name => $field_handler)
    {
		$field = $field_handler->options;
		$splits = preg_split('/,/', $field['label']);
		$factor_name = trim($splits[0]);
		if($label == $factor_name)
		{
			return view_get_field_value($view , $field_name , $record);
		}
    }
}

function get_field_type_string($field_name)
{
    $field_info = field_info_field($field_name);
    if($field_info!=NULL)
    {
        return $field_info['type'];
    }
    return "unknown";
}

function date_to_iso8601_date_str($value)
{
	return strftime('%Y-%m-%dT%H:%M', strtotime($value));
}

function view_get_field_value($view , $field_name , $record)
{
    /*
    if($view->executed == FALSE)
    {
        $view->_post_execute();
        $view->executed = TRUE;
    }
    */
	$field_handler = $view->field[$field_name];
    $field_handler->pre_render($record);

	if ($field_handler->allow_advanced_render() && method_exists($field_handler, 'render_item')) {
		$raw_items = $field_handler->get_items($record);
		if(count($raw_items)>0)
		{
            //dsm($field_handler);
			//dsm($raw_items);

			$arr = array();
			foreach($raw_items as $raw_item)
			{
				if(array_key_exists('raw', $raw_item))
				{
					if(array_key_exists('value' , $raw_item['raw']))
					{
						$value = $raw_item['raw']['value'];
						if(array_key_exists('date_type', $raw_item['raw']) && $raw_item['raw']['date_type'] =='datetime' )
						{
							$format_str = '%Y%m%d';
							//dsm($field_handler->field_info['settings']['granularity']);	
							if($field_handler->field_info['settings']['granularity']['minute'] !== 0)
							{
								$format_str = '%Y-%m-%dT%H:%M';
								$value = '\''. strftime($format_str, strtotime($value)) . '\'';
							}
							else
							{
								$value = strftime($format_str, strtotime($value));
							}
						}

						if(get_field_type_string($field_name) == 'list_integer')
						{
							$value = $field_handler->field_info['settings']['allowed_values'][$value];
						}


						if(array_key_exists('value2' , $raw_item['raw']))
						{
							$value2 = $raw_item['raw']['value2'];
							if(array_key_exists('date_type', $raw_item['raw']) && $raw_item['raw']['date_type'] =='datetime' )
							{
								$format_str = '%Y%m%d';
								if($field_handler->field_info['settings']['granularity']['minute'] !== 0)
								{
									$format_str = '%Y-%m-%dT%H:%M';
									$value2 = '\'' . strftime($format_str, strtotime($value2)) . '\'' ;
								}
								else
								{
									$value2 = strftime($format_str, strtotime($value2));
								}
							}

							if($value2 != $value)
							{
								// $field_handler->options["settings"]["fromto"]=="both"
								//dsm($raw_items);
								return 'between ' . $value . ',' . $value2;
							}
							else
							{
								return '>= ' . $value;
							}
						}
						$arr[]= $value;
					}
					else if(array_key_exists('taxonomy_term' , $raw_item['raw']))
					{
						//dsm($raw_items);
						$t = $raw_item['raw']['taxonomy_term'];
						if(property_exists($t , "field_rating_operation_code"))
							$arr[]=$t->field_rating_operation_code['und'][0]['value'];
						else
							$arr[]= $raw_item['raw']['taxonomy_term']->name;
					}
					else if(array_key_exists('nid' , $raw_item['raw']) && array_key_exists('node' , $raw_item['raw']))
					{
						//dsm($raw_items[0]['raw']['node']);
						$arr[]= $raw_item['raw']['node']->title;
					}
					else
					{
						// dsm($raw_items);
						$arr[] = $raw_item['rendered']['#markup'];
						// return "unknown";
					}
				}
				else
				{
					dsm($raw_items);
					return "unknown";
				}
			}
			return join(',' , $arr);
		}
		//dsm($field_name);
		//dsm($record);
		return null;
	}
	else
	{
        $value = $field_handler->render($record);
        return $value;
	}
}

function string_startsWith($haystack, $needle)
{
	return strpos($haystack, $needle) === 0;
}

function string_endsWith($haystack, $needle)
{
    return substr($haystack, -strlen($needle)) == $needle;
}

/*
function rating_rules_export_from_view_has_nid_reference($title , $view_name , $display_name , $source_view_name , $source_display_name , $ruleset_template)
{
    $ret = array();
    $view = views_get_view($source_view_name);
    $view->set_display($source_display_name);
    $view->execute();
    foreach($view->field as $field_name => $field_handler)
    {
        $field = $field_handler->options;
        $splits = preg_split('/,/', $field['label']);
        $factor_name = trim($splits[0]);
        $field_name_map[$field_name] = $factor_name;
    }

    foreach($view->result as $row_id => $record)
    {
        $nid = -1;
        $ruleset_name = $ruleset_template;
        foreach($view->field as $field_name => $field_handler)
        {
			$value = view_get_field_value($view , $field_name , $record);
			if($field_name == 'nid')
			{
				$nid = $value;
			}
			$ruleset_name = str_replace('$(' . $field_name_map[$field_name] . ')' , $value , $ruleset_name);
        }
        $data = rating_rules_export_from_view($ruleset_name , $view_name , $display_name , $nid);
        $ret[] = $data;
    }
    return $ret;
}
*/

function get_rating_factor_info($rating_factor_name)
{
     $query = new EntityFieldQuery();
     $query->entityCondition('entity_type','node');
     $query->propertyCondition('type','rating_factor_conversion');
     $query->fieldCondition('field_rating_factor_name' , 'value' , $rating_factor_name , '=');
     $result = $query->execute();

     if (!empty($result['node'])) {
        $nodes = entity_load('node', array_keys($result['node']));
        foreach($nodes as $node)
        {
            $ret = array();
            $ret["label"] = $rating_factor_name;
            $ret["default_op"] = $node->field_rating_factor_op['und'][0]['value'];
            $ret["size"] = $node->field_rating_factor_size['und'][0]['value'];
            $ret["type"] = $node->field_rating_factor_type['und'][0]['value'];
            return $ret;
        }
	 }
	 else if(string_startsWith($rating_factor_name , "counter_"))
	 {
		$ret = array();
		$ret["label"] = $rating_factor_name;
		$ret["default_op"] = "=";
		$ret["size"] = 0;
		$ret["type"] = "double";
		return $ret;
	 }
	 return NULL;
}

function has_same_sub_factor($arr , $factor_name)
{
    foreach($arr as $sub_factor)
    {
        if($sub_factor['label'] == $factor_name)
            return TRUE;
    }
    return FALSE;
}
function rating_rules_export_from_view($title, $view_name, $display_name, $nid=NULL)
{
    $view_name=trim($view_name);
    $view = views_get_view($view_name);
    if($view!=NULL)
    {
        $jsonData = array('type' => 'rules' , 'title'=>$title, 'object_name' => $title, 'view_name'=>$view_name);
        if($display_name!=NULL && $display_name!="")
        {
            $view->set_display($display_name);
        }
        if($nid!=NULL)
        {
            $view->set_arguments(array('0'=>$nid));
        }
        $jsonMeta = array();
        $field_name_map = array();
        $factor_meta_map = array();
        $view->execute();
        foreach($view->field as $field_name => $field_handler)
        {
            $field = $field_handler->options;
            $splits = preg_split('/,/', $field['label']);
            $factor_name = trim($splits[0]);
            $field_name_map[$field_name] = $factor_name;
            if($field['exclude']!=1)
            {
                $factorMeta = array('label' => $factor_name);
                foreach($splits as $index => $token)
                {
                    if($index > 0)
                    {
                        $s = trim($token);	
                        if($s == 'result')
                        {
                            $factorMeta['is_result'] = 'true';
                        }
                        else
						{
							$pos = strpos($s , '=');
							if($pos!==false)
							{
								$key = substr($s , 0 , $pos);
								$value = substr($s , $pos+1 );
								$factorMeta[trim($key)]=trim($value);
							}
                        }
                    }
                }
                if($factor_name!='rule_id' && $factor_name!='rule_name' && !string_endsWith($factor_name , '_op'))
                {
                    if(!array_key_exists('type', $factorMeta))
                    {
                        if($field['field'] == 'title')
                        {
                            $factorMeta['type'] = 'string';
                            $factorMeta['size'] = '64';
                        }
                        else if($field_handler->handler_type == 'field')
                        {
                            $field_info = field_info_field($field['field']);
                            if($field_info!=NULL)
                            {
                                $factorMeta['drupal_type'] = $field_info['type'];
                                if($field_info['type']=='datetime')
                                {
                                    $factorMeta['type'] = 'string';
                                    $factorMeta['size'] = '16';
                                }
                                else if($field_info['type'] == 'node_reference')
                                {
                                    $factorMeta['type'] = 'string';
                                    $factorMeta['size'] = '128';
                                }
                                else if($field_info['type'] == 'number_integer')
                                {
                                    $factorMeta['type'] = 'int';
                                    //$factorMeta['size'] = 0;
                                }
                                else if($field_info['type'] == 'list_boolean')
                                {
                                    $factorMeta['type'] = 'int';
                                    //$factorMeta['size'] = 0;
                                }
                                else if($field_info['type'] == 'list_text')
                                {
                                    // max foreach(['settings']['allowed_values'])
                                    $factorMeta['type'] = 'string';
                                    $factorMeta['size'] = '128';
                                }
                                else if($field_info['type'] == 'list_integer')
                                {
                                    // max foreach(['settings']['allowed_values'])
                                    $factorMeta['type'] = 'string';
                                    $factorMeta['size'] = '128';
                                }
                                else if($field_info['type'] == 'taxonomy_term_reference')
                                {
                                    $factorMeta['type'] = 'string';
                                    $factorMeta['size'] = '64';
                                }
                                else if(array_key_exists('settings' , $field_info))
                                {
                                    if(array_key_exists('max_length' , $field_info['settings']))
                                    {
                                        $factorMeta['type'] = $field_info['type'];
                                        $factorMeta['size'] = $field_info['settings']['max_length'];
                                    }
                                    else
                                    {
                                        //taxonomy_term
                                        $factorMeta['type'] = 'string';
                                        $factorMeta['size'] = '64';
                                        //$factorMeta['type'] = $field_info['type'];
                                       // dsm($factor_name);
                                        //dsm($field_info);
                                    }
                                }
                                else
                                {
                                    dsm($factor_name);
                                    dsm($field_info);
                                }
                            }
                            else
                            {
                                // php
                                //dsm($field_handler);
                                $factorMeta['type'] = 'string';
                                $factorMeta['size'] = '64';
                            }
                        }
                        else
                        {
                            $factorMeta['type'] = 'string';
                            $factorMeta['size'] = '64';
                        }
                    }
                    else
                    {
                        if($factorMeta['type'] == 'json_condition')
                        {
                            $factorMeta['sub_rule_factors'] = array();
                        }
                    }
                    $factorMeta['order'] = $field_handler->position;
                    $factor_meta_map[$factor_name] = $factorMeta;
                    $jsonMeta[]=&$factor_meta_map[$factor_name];
                }
            }
        }
        $rules = array();
        foreach($view->result as $row_id => $record)
        {
            $rule = array();
            foreach($view->field as $field_name => $field_handler)
            {
                if($field_handler->options['exclude']!=1)
                {
                    $factor_name = $field_name_map[$field_name];
                    if(array_key_exists($factor_name, $factor_meta_map) && $factor_meta_map[$factor_name]['type'] == 'json_condition')
                    {
                        //dsm(view_get_field_value($view , $field_name , $record));
                        //$rule[$factor_name] = json_decode(view_get_field_value($view , $field_name , $record));
                        $condition = json_decode(view_get_field_value($view , $field_name , $record));
                        if($condition != NULL)
                        {
                            $count = 0;
                            foreach($condition->factors as $rating_factor)
                            {
                                //dsm($rating_factor);
                                $sub_factor = get_rating_factor_info($rating_factor);;
                                if(!has_same_sub_factor( $factor_meta_map[$factor_name]['sub_rule_factors'] , $sub_factor['label']))
                                {
                                    $sub_factor['order'] = $count++;
                                    $factor_meta_map[$factor_name]['sub_rule_factors'][$rating_factor] = $sub_factor;
                                }
                            }
                            $rule[$factor_name] = $condition->condition;
                        }


                    }
                    else
                    {
                        $rule[$factor_name] = view_get_field_value($view , $field_name , $record);
                    }
                }
            }
            $rules[] = $rule;
        }
        $jsonData['field'] = $factor_meta_map;
        $jsonData['data'] = $rules;
        return $jsonData;
	}
	else
	{
		dsm("execute view query failed :" . $view_name. ".");
	}
    return null;
}
