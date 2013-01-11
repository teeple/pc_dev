<?php

function ocs_build_all_test_case( $form, &$form_state, $product_nid)
{
	$node = node_load( $product_nid);

	/* get list of test cases */
	$query = new EntityFieldQuery();
	$result = $query->entityCondition( 'entity_type', 'node')
		->entityCondition( 'bundle', 'test_case_online_charging')
		->execute();

	if ( count( $result) > 0) {
		$msg = t( 'Build All Test Cases for the product <em>"@name"</em>.'.
				'<br>Total @num new test cases shall be generated.',
			array( '@name' => $node->title, '@num' => count( $result['node'])));
	}
	else {
		$msg = t( 'No test cases are found in the content type <em>"test_case_online_charging"</em>');
	}

	$form['markup'] = array(
		'#type' => 'markup',
		'#markup' => $msg,
	);


	$form['actions'] = array( '#type' => 'actions');
	if ( count( $result) > 0) {
		$form['actions']['submit'] = array(
			'#type' => 'submit',
			'#value' => t('OK'),
		);
	}

	$form['actions']['cancel'] = array(
		'#type' => 'submit',
		'#value' => t('Cancel'),
	);

	$form['#product'] = $product_nid;

	return $form;
}


function ocs_build_all_test_case_submit($form, &$form_state) 
{
	$values = $form_state['values'];

	if ( $values['op'] == 'OK') {
		$_SESSION['http_request_count'] = 0; // reset counter for debug information.

		$batch = batch_build_test_case( $form['#product']);
		batch_set($batch);
	}
}

function batch_build_test_case( $product_nid = 0) 
{
	/* get list of test cases */
	$query = new EntityFieldQuery();
	$result = $query->entityCondition( 'entity_type', 'node')
		->entityCondition( 'bundle', 'test_case_online_charging')
		->execute();

	drupal_set_message(t('Creating an array of @num operations', array('@num' => count( $result['node']))));

	$operations = array();
// Each operation in the operations array means at least one new HTTP request,
// running Drupal from scratch to accomplish the operation. If the operation
// returns with $context['finished'] != TRUE, then it will be called again.
// In this example, $context['finished'] is always TRUE.

	$product = node_load( $product_nid);

	foreach( array_keys( $result['node']) as $nid) {
		$node = node_load( $nid);

		// Each operation is an array consisting of
		// - the function to call
		// - An array of arguments to that function
		$operations[] = array('batch_build_test_case_op', array($product_nid, $nid, 
				t('Test case @nid for product "@title"', array( '@nid' => $nid, '@title' => check_plain($product->title)))));
	}

	$batch = array(
		'operations' => $operations,
		'finished' => 'batch_build_test_case_finished',
		'title' => t('Generate Test Cases'),
		'init_message' => t('Starting.'),
		'progress_message' => t('Processed @current out of @total.'),
		'error_message' => t('Batch procedure has encountered an error.'),
	);
	return $batch;
}


function batch_build_test_case_op( $product_nid, $tc_nid, $operation_details, &$context) 
{
	/* get list of test cases */
	$query = new EntityFieldQuery();
	$result = $query->entityCondition( 'entity_type', 'node')
		->entityCondition( 'bundle', 'test_result_online_charging')
		->fieldCondition( 'field_ts_product', 'nid', $product_nid)
		->fieldCondition( 'field_ts_test_case', 'nid', $tc_nid)
		->execute();

	$tc = node_load( $tc_nid);

	if ( count( $result) == 0) {
		// add new test case
		$node = ocs_admin_get_new_node( 'test_result_online_charging');
		$node->field_ts_test_case = array( 'und' => array( 0 => array( 'nid' => $tc_nid)));
		$node->field_ts_product = array( 'und' => array( 0 => array( 'nid' => $product_nid)));
		$node->field_ts_expected_charge = array( 'und' => array( 0 => array( 'value' => $tc->field_ts_default_charge['und'][0]['value'])));
		$node->title = $operation_details;

		node_save( $node);

		$context['results'][] = 'Add new test case : ' . $node->nid . ' (' . $node->title . ')';
	}
	else {
		$nids = array_keys( $result['node']);
		$node = node_load( $nids[0]);
		$node->title =  $operation_details;
		$node->field_ts_expected_charge['und'][0]['value'] = $tc->field_ts_default_charge['und'][0]['value'];
		node_save( $node);

		$context['results'][] = 'Existing test case : ' . ( $operation_details );
	}

	// Store some result for post-processing in the finished callback.

	// Optional message displayed under the progressbar.
	$context['message'] = 'Adding test case : ' . $operation_details;

	_batch_update_http_requests();
}

function batch_build_test_case_finished($success, $results, $operations) 
{
	if ($success) {
		// Here we could do something meaningful with the results.
		// We just display the number of nodes we processed...
		drupal_set_message(t('@count results processed in @requests HTTP requests.', 
			array('@count' => count($results), 
				'@requests' => _batch_get_http_requests())));
		drupal_set_message(t('The final result was "%final"', array('%final' => end($results))));
	}
	else {
		// An error occurred.
		// $operations contains the operations that remained unprocessed.
		$error_operation = reset($operations);
		drupal_set_message(t('An error occurred while processing @operation with arguments : @args', 
			array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
	}
}


function _batch_update_http_requests() 
{
	  $_SESSION['http_request_count']++;
}

function _batch_get_http_requests() 
{
	  return !empty($_SESSION['http_request_count']) ? $_SESSION['http_request_count'] : 0;
}
