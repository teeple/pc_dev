<?php

function _array_lifecycle_status($exportItemNids = NULL)
{
	$jsonData = array();

	$query = new EntityFieldQuery;
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'ocs_account_state')
		->execute();

	if ( count( $result) > 0) {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			$jsonData[] = array( 'state' => $node->title, 'id' => $node->field_ocs_state_id['und'][0]['value']);
		}
	}

    return $jsonData;
}

function _json_lifecycle_status($exportItemNids = NULL)
{
	$retArray = array();
	$jsonData = _array_lifecycle_status($exportItemNids);
    
	$retArray = $jsonData;

	$enc = ($exportItemNids != NULL) ? json_encode($jsonData) : json_encode($retArray);
    //remove carrage return and line feed
    $enc = str_replace('\r\n','', $enc);
    
    return $enc;
}
