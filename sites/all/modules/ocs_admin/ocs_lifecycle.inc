<?php

function array_get_value( $a, $f=array()) 
{
	if ( ! $a || ! is_array($a)) return array();
	foreach( $a as $k => $v) {
		if ( is_array( $v)) $f = array_get_value( $v, $f);
		else $f[] = $v;
	}
	return $f;
} 

function ocs_admin_check_lifecycle_scheme( $node, $node_unchanged)
{
// 	dpm( $node, 'node');
// 	dpm( $node_unchanged, 'unchanged');
	
	$after = array_get_value( $node->field_lifecycle_states);
	$before = array_get_value( $node_unchanged->field_lifecycle_states);
	
// 	dpm( $after, 'after');
// 	dpm( $before, 'before');
	
	$intersect = array_intersect( $before, $after);
	$removed = array_diff( $before, $intersect);
	$added = array_diff( $after, $intersect);
	
	//dpm( $added. 'nodes to add');
	//dpm( $removed, 'nodes to remove');
	//dpm( $intersect, 'node intersect');
	
	// check ocs_svc_perm
	// ocs_svc_perm에는 title이 node->nid인 instance 들이 저장되어 있다.
	// 이중에서 state 값이 added, removed에 속한 것을 추가/삭제한다.
	$items = entity_load( 'node', FALSE, array( 'type' => 'ocs_svc_perm', 'title' => $node->nid));
	// add lifecycle states
	
	// remove lifecycle states
	
	foreach ( $items as $item) {
		//dpm( $item, 'state item');
		$state_nid = $item->field_lifecycle_state['und'][0]['nid'];
		if ( ($key = array_search( $state_nid, $intersect)) !== FALSE) {
			// intersect, 교집합에 들어가므로 패스
			//dpm( $item->nid, 'belongs to intersect');
			unset($intersect[$key]); 
		}
		else if ( ($key = array_search( $state_nid, $added)) !== FALSE) {
			//dpm( $item->nid, 'belongs to add list');
			unset( $added[$key]);
		}
		else {
			// 그외의 경우는 모두 삭제
			//dpm( $item->nid, 'remove state');
			node_delete( $item->nid);
		}
	}
	
	//dpm( $added, 'nodes to add');
	//dpm( $intersect, 'node not exist');
	$added = array_merge( $added, $intersect);
	
	// add lifecycle states
	foreach( $added as $add_node_nid) {
		$new_node = ocs_admin_get_new_node( 'ocs_svc_perm');
		$new_node->title = $node->nid;
		$new_node->field_lifecycle_state['und'][0]['nid'] = $add_node_nid;
		$new_node->field_lifecycle_scheme['und'][0]['nid'] = $node->nid;
		node_save( $new_node);
		
		//dpm( $new_node, 'add node');
	}
	
	// check ocs_state_machine
	$items = entity_load( 'node', FALSE, array( 'type' => 'ocs_state_machine', 'title' => $node->nid));
	foreach ( $items as $item) {
// 		dpm( $item, 'state machine');
		if ( array_search( $item->field_ocs_from_state['und'][0]['target_id'], $after) === FALSE ||
				array_search( $item->field_ocs_to_state['und'][0]['target_id'], $after) === FALSE) {
// 			dpm( $item->nid, 'remove state machine');
			node_delete( $item->nid);
		}
	}
	
}

function ocs_lifecycle_node_form( &$form, &$form_state, $form_id)
{

	// get lifecycle scheme nid
	$lifecycle_nid = $form['field_lifecycle_scheme']['und']['#default_value'][0];
	$scheme = node_load( $lifecycle_nid);
	
	$states = array();
	foreach( $scheme->field_lifecycle_states['und'] as $key => $value)	{
		$states[] = $value['nid'];
	}
	
	//dpm( $states, 'state list');
	
	foreach( $form['field_ocs_from_state']['und']['#options'] as $key => $value) {
		if ( array_search( $key, $states) === FALSE) {
			//dpm( $key, 'not exist');
			unset( $form['field_ocs_from_state']['und']['#options'][$key]);
		}
	}
	
	foreach( $form['field_ocs_to_state']['und']['#options'] as $key => $value) {
		if ( array_search( $key, $states) === FALSE) {
			//dpm( $key, 'not exist');
			unset( $form['field_ocs_to_state']['und']['#options'][$key]);
		}
	}
	
	unset($form['field_ocs_actions_ref']);
	unset($form['field_ocs_action_param']);
	unset($form['field_ocs_action_rule_id']);
	
	$form['field_lifecycle_scheme']['#type'] = 'hidden';
	$form['title']['#type'] = 'hidden';
	
	// ajax handler for from & to state
	/*
	$form['field_ocs_from_state']['#ajax'] = array(
			'callback' => 'ocs_lifecycle_state_callback',
			'wrapper' => 'replace_to_state_div',
	);
	
	$form['field_ocs_to_state']['#prefix'] = '<div id="replace_to_state_div">';
	$form['field_ocs_to_state']['#suffix'] = '</div>';
	*/
	
}

/*
function ocs_lifecycle_state_callback( $form, $form_state)
{
	return $form['field_ocs_to_state'];
}
*/

function ocs_lifecycle_node_form_validate( $node, $form, $form_state)
{
	// from, to state가 같은 값이면 에러
	$from_state = $node->field_ocs_from_state['und'][0]['target_id'];
	$to_state = $node->field_ocs_to_state['und'][0]['target_id'];
	if ( $from_state == $to_state ) {
		form_set_error( 'field_ocs_to_state', t('Invalid state : same as "from state"'));
	}
	
	if ( ! $form['#node_edit_form']) {
		dpm( $form, 'form');
		// from, to state가 이미 존재하면 에러
		$scheme_nid = $form['field_lifecycle_scheme']['und']['#default_value'][0];
		$query = new EntityFieldQuery();
		$items = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'ocs_state_machine')
		->fieldCondition('field_lifecycle_scheme', 'nid', $scheme_nid)
		->execute();
		
		foreach( array_keys($items['node']) as $nid) {
			$item = node_load( $nid);
			if ( $item->field_ocs_from_state['und'][0]['target_id'] == $from_state &&
					$item->field_ocs_to_state['und'][0]['target_id'] == $to_state) {
				form_set_error( 'field_ocs_from_state', t('Invalid state : transition rule exists already.'));
				form_set_error( 'field_ocs_to_state', t('Invalid state : transition rule exists already.'));
			}
		}
		
	}
}
