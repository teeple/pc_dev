<?php

function deploy_all( $type, $prd_list, $target)
{
	$_SESSION['http_request_count'] = 0; // reset counter for debug information.

	$operations = array();
	foreach( $prd_list as $nid => $prd) {
		$operations[] = array('batch_deploy_product_op', array( $type, $nid, $prd, $target));
	}

	$batch = array(
		'operations' => $operations,
		'finished' => 'batch_deploy_product_finished',
		'title' => t('Deploy @type', array( '@type' => $type)),
		'init_message' => t('Starting ... '),
		'progress_message' => t('Processed @current out of @total.'),
		'error_message' => t('Batch procedure has encountered an error.'),
	);
	batch_set($batch);
}


function batch_deploy_product_op( $type, $nid, $obj, $target, &$context) 
{
	$result = export_deploy( $type, array( $nid => $obj), $target, FALSE);

	$resultData = json_decode( $result[0]->data);
	$context['results'][] = t('Result : @result<br>'.
			'<ul><li>OCS : @ocs (@ocs_r)</li>'.
			'<li>CS : @cs (@cs_r)</li>'.
			'<li>CRM : @crm (@crm_r)</li></ul>',
			array( 
				'@result' => ($result[0]->code === '200') ? 'SUCCESS' : 'FAIL',
				'@ocs' => isset($resultData->OCS->result_code) ? $resultData->OCS->result_code : '',
				'@ocs_r' => isset($resultData->OCS->result_reason) ? $resultData->OCS->result_reason : '',
				'@cs' => isset($resultData->CS->result_code) ? $resultData->CS->result_code : '',
				'@cs_r' => isset($resultData->CS->result_reason) ? $resultData->CS->result_reason : '',
				'@crm' => isset($resultData->CRM->result_code) ? $resultData->CRM->result_code : '',
				'@crm_r' => isset($resultData->CRM->result_reason) ? $resultData->CRM->result_reason : ''));

	$context['message'] = t('Deploy @type "@title" <br>', 
		array( '@type' => $type, '@title' => check_plain($obj->title))) . end($context['results']);

	_batch_update_http_requests();
}

function batch_deploy_product_finished($success, $results, $operations) 
{
	if ($success) {
		// Here we could do something meaningful with the results.
		// We just display the number of nodes we processed...
		drupal_set_message(t('@count results processed in @requests HTTP requests.', 
			array('@count' => count($results), 
				'@requests' => _batch_get_http_requests())));
		drupal_set_message(t('The final result was '. end($results)));
	}
	else {
		// An error occurred.
		// $operations contains the operations that remained unprocessed.
		$error_operation = reset($operations);
		drupal_set_message(t('An error occurred while processing @operation with arguments : @args', 
			array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
	}
}


/*
function _batch_update_http_requests() 
{
	  $_SESSION['http_request_count']++;
}

function _batch_get_http_requests() 
{
	  return !empty($_SESSION['http_request_count']) ? $_SESSION['http_request_count'] : 0;
}
*/
