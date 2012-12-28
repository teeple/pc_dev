<?php

	$nl = '
';

	$type = 'test_case_subscriber';

	$query = new EntityFieldQuery();	
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->execute();

	if ( count( $result) > 0) {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			print $nid . $node->title . $nl;
			if ( $nid != 16639)
				node_delete( $nid);
		}
	}
	else {
		print 'Not found'.$nl;
	}

