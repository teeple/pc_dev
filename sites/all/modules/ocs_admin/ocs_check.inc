<?php

function ocs_check_before_save( $node, $node_unchanged)
{
	/*
	dpm( $node, 'node');
	dpm( $node_unchanged, 'node_unchanged');
	*/
	dpm( 'now:'. date( 'H:i:s', time()));
	dpm( 'before:'. date( 'H:i:s', $node_unchanged->changed));
	dpm( 'after:'. date( 'H:i:s', $node->changed));
	$saved = node_load( $node->nid);
	dpm( 'DB:'. date( 'H:i:s', $saved->changed));
}
