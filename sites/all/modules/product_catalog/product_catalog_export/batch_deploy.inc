<?php

function deploy_all( $type, $prd_list, $target, $redirectFlag = TRUE)
{
	$_SESSION['http_request_count'] = 0; // reset counter for debug information.
	if ( isset( $redirectFlag)) {
		$_SESSION['redirect_after_batch'] = 'lifecycles/history/'.$type;
	}
	else {
		unset( $_SESSION['redirect_after_batch']);
	}

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

	$result[0]['title'] = $obj->title;
	$context['results'][] = $result[0];
	$context['message'] = t('<br>Deploy @type "@title" <br>', 
		array( '@type' => $type, '@title' => check_plain($obj->title))) . batch_deploy_result( end($context['results']));

	_batch_update_http_requests();
}

function batch_deploy_result( $param)
{
	$result = $param['result'];

	$rows = array();
	$rows[] = array( 'Name', $param['title']);
	$rows[] = array( 'URL', $param['url']);
	$rows[] = array( 'RESULT', $result->code . ' ' . $result->status_message);

	$resultData = json_decode( $result->data, TRUE);
	$r = array();
	foreach( array( 'OCS', 'CS', 'CRM') as $sys) {
		if ( isset($resultData[$sys])) {
			$r[] = array( $sys, $resultData[$sys]['result_code'], $resultData[$sys]['result_reason']);
		}
	}
	$rows[] = array( '', theme( 'table', array( 'rows' => $r)));

	return theme( 'table', array( 'rows' => $rows));
}

function batch_deploy_product_finished($success, $results, $operations) 
{
	if ($success) {
		// Here we could do something meaningful with the results.
		// We just display the number of nodes we processed...
		drupal_set_message(t('@count results processed in @requests HTTP requests.', 
			array('@count' => count($results), 
				'@requests' => _batch_get_http_requests())));

		$idx = 1;
		foreach( $results as $r) {
			drupal_set_message( t( 'Request : @i', array( '@i' => $idx++)) . batch_deploy_result( $r));
		}
	}
	else {
		// An error occurred.
		// $operations contains the operations that remained unprocessed.
		$error_operation = reset($operations);
		drupal_set_message(t('An error occurred while processing @operation with arguments : @args', 
			array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
	}

	if ( isset($_SESSION['redirect_after_batch'])) {
		drupal_goto($_SESSION['redirect_after_batch']);
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
