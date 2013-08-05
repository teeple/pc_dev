<?php

function _array_priority_hierarchy($exportItemNids = NULL)
{
	$jsonData = array();
	$relations = array();
	$productNids = array();
	
	//fetch data
	$viewResult = views_get_view_result('list_export_product', 'panel_pane_2');
	
	foreach ($viewResult as $record) {
		$relation = array();
		$relation['priority'] = !empty($record->field_field_weight_for_ratingpriority)
						?$record->field_field_weight_for_ratingpriority[0]['raw']['value']:NULL;
		$relation['hierarchy'] = !empty($record->field_field_weight_for_hierarchy)
						?$record->field_field_weight_for_hierarchy[0]['raw']['value']:NULL;
		$relations[] = $relation;
	}

	$jsonData['ifvalues']['resources'] = array();
	$jsonData['relations'] = $relations;
	
    return $jsonData;
}

function _json_priority_hierarchy($exportItemNids=NULL) {
  $retArray = array();
  /*
  $jsonData  = _array_priority_hierarchy($exportItemNids);
  $retArray = $jsonData;
  */
  
  $arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export_product", "list_product_lifecycle");
  foreach($arr as $a)
  {
	foreach($a as $t => $v)
	{
		$retArray['rating_rules'][$t] = $v;
	}
  }

  return json_encode($retArray);
}
