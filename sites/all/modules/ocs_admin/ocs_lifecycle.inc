<?php

function ocs_admin_check_lifecycle_scheme( $node, $node_unchanged)
{

	$after = array();
	foreach( $node->field_lifecycle_states['und'] as $key => $value)	{
		$after[] = $value['nid'];
	}
	
	$before = array();
	foreach( $node_unchanged->field_lifecycle_states['und'] as $key => $value) {
		$before[] = $value['nid'];
	}
	
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
		else if ( array_search( $state_nid, $removed ) !== FALSE) {
			// 삭제할 대상에 들어가면, 해당 노드 삭제
			//dpm( $item->nid, 'remove state');
			node_delete( $item->nid);
		}
		else if ( ($key = array_search( $state_nid, $added)) !== FALSE) {
			//dpm( $item->nid, 'belongs to add list');
			unset( $added[$key]);
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
		node_save( $new_node);
		
		//dpm( $new_node, 'add node');
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

function ocs_lifecycle_service_permission()
{
	$nid = 0;
	dpm( current_path(), 'current path');
	
	$view = views_get_view( 'ocs_svc_perm');
	$view->execute_display( 'service_perm_table', $nid);
	$output = $view->render();
	
	print $output;
}