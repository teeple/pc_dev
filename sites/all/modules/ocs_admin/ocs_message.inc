<?php

define('OCS_MESSAGE_PARAMETER', 0);
define('OCS_MESSAGE_COUNTER', 1);
define('OCS_MESSAGE_COUNTER_GROUP' , 2);
define('OCS_MESSAGE_SCRIPT' , 3);

global $param_type_options;
$param_type_options = array(
	OCS_PARAM_TYPE_DATE => array(
		'%Y/%m/%d' => '2012/12/31',
		'%m/%d/%Y' => '12/31/2013',
		'%Y/%b/%d' => '2012/Dec/31',
		'%b/%d/%Y' => 'Dec/31/2013',
		'%d/%b/%Y' => '31/Dec/2013',
		'%m/%d' => '12/31',
		'%b/%d' => 'Dec/31',
		'%d/%b' => '31/Dec',
		'%Y/%m/%d %a' => '2012/12/31 Wed',
		'%m/%d/%Y %a' => '12/31/2013 Wed',
		'%Y/%b/%d %a' => '2012/Dec/31 Wed',
		'%b/%d/%Y %a' => 'Dec/31/2013 Wed',
		'%d/%b/%Y %a' => '31/Dec/2013 Wed',
	),
	OCS_PARAM_TYPE_TIME => array(
		'%X' => '23:48:10',
		'%H:%M' => '23:48',
		'%p %I:%M' => 'pm 11:48',
	),
);

global $param_types;
$param_types = array(
	OCS_MESSAGE_PARAMETER => 'Parameter',
	OCS_MESSAGE_COUNTER => 'Counter',
	OCS_MESSAGE_COUNTER_GROUP => 'Counter Group',
	OCS_MESSAGE_SCRIPT => 'Script'
);

global $supported_lang;
$supported_lang = array( 'MNG', 'ENG');


function ocs_admin_message_form($form, &$form_state, $nid = NULL, $op = NULL)
{
	$num_values = isset($form_state['values']['num_values']) ? $form_state['values']['num_values'] : 0;

	$title = '';
	$format = array( 'MNG' => 'Mongolian Notification Text', 'ENG' => 'English Notification Text');
	if ($op == 'edit') {
		$node = node_load($nid);
		//	dpm( $node, 'node');
		if ($node) {
			$title = $node->title;
			$format['MNG'] = $node->field_ocs_format['und'][0]['value'];
			$format['ENG'] = isset( $node->field_ocs_format['und'][1]) ? $node->field_ocs_format['und'][1]['value'] : '';
			if (!isset($form_state['values']['num_values'])) {
				if(!empty($node->field_ocs_value)) {
					$num_values = count($node->field_ocs_value['und']);
				}
			}
		}
	}

	// get parameter list of action '_ocs_noti_param_list'
	$params = &drupal_static(__FUNCTION__, NULL);
	if (empty($params)) {
		// get nid of the action: '_ocs_noti_param_list'
		$items = entity_load('node', FALSE, array(
			'type' => 'ocs_actions',
			'title' => '_ocs_noti_param_list'
		));
		if (count($items) != 1) {
			drupal_set_message(t('Action "_ocs_noti_param_list" is not defined.'), 'error');
			return $form;
		}
		$action_nid = array_keys($items);
		$params = new OcsParam;
		$params->load($action_nid[0], NULL);
	}

	$form['#nid'] = $nid;
	$form['#op'] = $op;
	$form['#attributes'] = array('class' => array('myform'));

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => 'Message Name',
		'#default_value' => $title,
	);

	global $supported_lang;

	foreach( $supported_lang as $lang) {
		$form['format' . $lang] = array(
			'#type' => 'textarea',
			'#title' => t( 'Format (@lang)', array( '@lang' => $lang)),
			'#default_value' => $format[$lang],
			'#description' => 'Enter message format in "printf" style. Use "%1, %2" to substitue numeric value.' . 
				'<br>Ex) "You have remains %1 won."',
		);
	}

	if(isset($node)){//edit
		$delivery_date = isset($node->field_value['und'][0]['value'])?$node->field_value['und'][0]['value']:3;	
		$delivery_time = isset($node->field_valid_date_hour['und'][0]['value'])?$node->field_valid_date_hour['und'][0]['value']:"00";
		if(!isset($form_state['values'])){//when first rendering
			$scheduled = isset($node->field_scheduled_delivery['und'][0]['value'])?$node->field_scheduled_delivery['und'][0]['value']:0;
		}else{
			$scheduled = isset($form_state['values']['flag']) ? $form_state['values']['flag'] : 0;
		}
	}else{//create
		$scheduled = isset($form_state['values']['flag']) ? $form_state['values']['flag'] : 0;
		$delivery_date = 3;
		$delivery_time = "00";
	}
	
	$form['scheduled'] = array(
		'#type' => 'fieldset',
		'#prefix' => '<div id="message_scheduled_div">',
		'#suffix' => '</div>',
	);

	$form['scheduled']['flag'] = array(
		'#type' => 'radios',
		'#title' => 'Scheduled Delivery',
		'#default_value' => $scheduled,
		'#options' => array( 0 => 'No', 1 => 'Yes'),
		'#ajax' => array(
			'callback' => 'ocs_admin_ajax_message_scheduled_callback',
			'wrapper' => 'message_scheduled_div',
		)
	);

	if ( $scheduled ) {
		if(isset($node)){
			$delivery_date = $node->field_value['und'][0]['value'];	
			$delivery_time = $node->field_valid_date_hour['und'][0]['value'];
		}
		
		$form['scheduled']['delivery_date'] = array(
			'#type' => 'textfield',
			'#title' => 'Date ',
			'#default_value' => $delivery_date,
			'#field_prefix' => 'After ',
			'#field_suffix' => 'Days ',
		);

		$time_list = array(
			"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11",
			"12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23",
		);

		$form['scheduled']['delivery_time'] = array(
			'#type' => 'select',
			'#title' => 'Time',
			'#options' => drupal_map_assoc( $time_list),
			'#default_value' => $delivery_time
		);
	}

	$form['valueset'] = array(
		'#type' => 'fieldset',
		'#title' => 'Variables',
		//'#description' => 'Use following counter names to build the message string. :
		// '. implode( ', ', array_keys( $counters)),
		'#prefix' => '<div id="message_format_div">',
		'#suffix' => '</div>',
	);

	$form['valueset']['num_values'] = array(
		'#type' => 'select',
		'#title' => 'Number of Variables',
		'#options' => array(0,1,2,3,4,5,6,7,8,9,10),
		'#default_value' => $num_values,
		'#ajax' => array(
			'callback' => 'ocs_admin_ajax_message_form_callback',
			'wrapper' => 'message_format_div',
		),
		'#prefix' => '<div class="inner-box-1">',
		'#suffix' => '</div>',
	);

	// get parameter list
	$param_list = $params->keylist();
	$param_options = array();
	foreach ($param_list as $key) {
		$param_options[$key] = $params->get_title($key);
	}

	// Notification Message parameters consist of following three types
	global $param_types;

	// get option list for each type
	$options[OCS_MESSAGE_PARAMETER] = $param_options;
	$options[OCS_MESSAGE_COUNTER] = ocs_admin_get_counter_id_list();
	$options[OCS_MESSAGE_COUNTER_GROUP] = ocs_admin_get_counter_group_list();
	$form['#options'] = $options;

	for ($i = 1; $i <= $num_values; $i++) {
		$type = isset($form_state['values']['type:' . $i]) ? $form_state['values']['type:' . $i] : 
			(($op == 'edit') ? $node->field_ocs_value_type['und'][$i - 1]['value'] : 0);

		$form['valueset'][$i] = array(
			'#type' => 'fieldset',
			'#title' => 'Variable %' . $i,
			'#prefix' => '<div class="inner-box-1">',
			'#suffix' => '</div>',
		);
		
		// select one from (Parameter, Counter, Counter Group)
		$form['valueset'][$i]['type:' . $i] = array(
			'#type' => 'select',
			'#title' => 'Type',
			'#options' => $param_types,
			'#default_value' => $type,
			'#prefix' => '<div class="inner-box-2">',
			'#suffix' => '</div>',
			// 해당 variable type만 바꾸는 경우 예기치 않은 에러가 발생해서, $form['valueset'] 전체를 바꾸는 것으로 변경함
			// '#ajax' => array(
				// 'callback' => 'ocs_admin_ajax_variable_type_callback',
				// 'wrapper' => 'ocs_variable_type_div' . $i,
			// ),
			
			'#ajax' => array(
				'callback' => 'ocs_admin_ajax_message_form_callback',
				'wrapper' => 'message_format_div',
			),
		);

		$form['valueset'][$i]['valueset' . $i] = array(
			'#type' => 'fieldset',
			'#prefix' => t('<div id="ocs_variable_type_div@i" class="inner-box-2">', array('@i' => $i)),
			'#suffix' => '</div>',
		);

		/*
		$form['valueset'][$i]['valueset' . $i]['markup'] = array(
			'#type' => 'markup',
			'#markup' => print_r( $form_state['values'], TRUE) . 
				' isset:' . $i . ':' . isset($form_state['values']['type:' . $i]) . ':' . $type, 
		);
		*/
		
		$selected_value = isset($form_state['values']['value:' . $i]) ? $form_state['values']['value:' . $i] : 
			(($op == 'edit') ? $node->field_ocs_value['und'][$i - 1]['value'] : '');
			
		if ( $type == OCS_MESSAGE_SCRIPT) {
			$form['valueset'][$i]['valueset' . $i]['value:' . $i] = array(
				'#type' => 'textarea',
				'#title' => $param_types[$type],
				'#default_value' => $selected_value,
				'#description' => 'Enter LUA script <br>' .
				 	'<ol>' . 
					'<li> Variables : COUNTER[], COUNTER_GROUP[]</li>' .
					'<li> arithmetic operation : '.
				  	'<ul><li>return COUNTER_GROUP[6].balance - math.floor(COUNTER[2].counter_tbl.counter_value/COUNTER[2].countername_tbl.counter_scale) </li></ul>' .
					'</li>' .
			   		'<li> date format : '.
					    '<ul><li>return os.date("%Y%m%d", os.time() + 60 * 86400)</li>' .
						'<li>return os.date("%Y%m%d", COUNTER[2].counter_tbl.counter_expire + 14 * 86400)</li></ul>'.
					'</li>' .
				  	'<li> conditional operation : ' .
				  		'<ul><li>if (  COUNTER_GROUP[6].balance == 0) then return "";</li>'. 
					   	'<li>else return string.format("FREE_SMS=%s", COUNTER_GROUP[6].balance);</li></ul>'.
					   	'<li>end</li>'.
					'</li></ol>' 
			);
		}
		else {
			// select parameter such as (today, act_date) if it's Parameter type
			// select counter id if it's Counter type
			// select counter group if it's Counter Group type
			$form['valueset'][$i]['valueset' . $i]['value:' . $i] = array(
				'#type' => 'select',
				'#title' => $param_types[$type],
				'#options' => $options[$type],
				'#default_value' => $selected_value,
			);

			$format_value = isset($form_state['values']['format:' . $i]) ? $form_state['values']['format:' . $i] : 
				(($op == 'edit') ? $node->field_ocs_value_format['und'][$i - 1]['value'] : '');

			if ($type == OCS_MESSAGE_PARAMETER) {
				// add ajax handler to change format if it's parameter such as (today, active_date) 
				$form['valueset'][$i]['valueset' . $i]['value:' . $i]['#ajax'] = array(
					'callback' => 'ocs_admin_ajax_variable_type_format_callback',
					'wrapper' => 'ocs_variable_type_format_div' . $i,
				);
				
				$selected_param_type = $params->type($selected_value);
				global $param_type_options;
							
				if ($selected_param_type == OCS_PARAM_TYPE_DATE || $selected_param_type == OCS_PARAM_TYPE_TIME) {
					$form['valueset'][$i]['valueset' . $i]['format:' . $i] = array(
						'#type' => 'select',
						'#title' => 'Format',
						'#options' => $param_type_options[$selected_param_type],
					);
				}
				else {
					$form['valueset'][$i]['valueset' . $i]['format:' . $i] = array(
						'#type' => 'textfield',
						'#title' => 'Format',
						'#size' => 30,
						'#default_value' => $format_value,
					);
				}
				
				$form['valueset'][$i]['valueset' . $i]['format:' . $i]['#prefix'] = 
					t('<div id="ocs_variable_type_format_div@idx">', array( '@idx' => $i));
				$form['valueset'][$i]['valueset' . $i]['format:' . $i]['#suffix'] = '</div>';
									
			}
			else if ($type == OCS_MESSAGE_COUNTER) {
				$form['valueset'][$i]['valueset' . $i]['format:' . $i] = array(
					'#type' => 'select',
					'#title' => 'Format',
					'#options' => array(
						'_value' => 'Value',
						'_expire' => 'Expire Date',
						'_delta_value' => 'Delta Value'
					),
					'#default_value' => $format_value,
				);
			}
		}
	}
	$form['actions'] = array('#type' => 'actions');

	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);

	if(isset($node)){//edit
		$form['actions']['delete'] = array(
			'#type' => 'submit',
			'#value' => t('Delete'),
		);
	}
	
	/*
	$form_state['rebuild'] = TRUE;
	$form_state['redirect'] = array('<front>');
	*/
	
	return $form;
}

// ajax handlers

function ocs_admin_ajax_message_scheduled_callback($form, &$form_state)
{
	return $form['scheduled'];
}

function ocs_admin_ajax_message_form_callback($form, &$form_state)
{
	return $form['valueset'];
}

function ocs_admin_ajax_variable_type_callback($form, &$form_state)
{
	//return $form_state['triggering_element']['#name'] . print_r( $form_state['values'], TRUE);
	list($name, $idx) = explode(':', $form_state['triggering_element']['#name']);
	return $form['valueset'][$idx]['valueset' . $idx];
}

function ocs_admin_ajax_variable_type_format_callback( $form, &$form_state)
{
	list($name, $idx) = explode(':', $form_state['triggering_element']['#name']);
	return $form['valueset'][$idx]['valueset' . $idx]['format:'.$idx];
}

function ocs_admin_message_form_validate($form, &$form_state)
{
	$values = $form_state['values'];

	if ($values['op'] == 'Save') {
		if (empty($values['title'])) {
			form_set_error('title', $form['title']['#title'] . ' is empty');
		}

		if ( $values['flag'] == 1 ) {
			if ( intval( $values['delivery_date']) < 0) {
				form_set_error('delivery_date', 'Invalid delivery date');
			}
		}

		global $supported_lang;

		foreach ( $supported_lang as $lang) {

			if (empty($values[ 'format' . $lang])) {
				form_set_error( 'format'.$lang, $form[ 'format' . $lang]['#title'] . ' is empty');
			}

			// check format string
			$format = str_word_count( $values['format'.$lang], 1, '%0123456789');
			foreach ($format as $fmt) {
				if (substr($fmt, 0, 1) == '%') {
					// check the variable number
					if (substr($fmt, 1) > $values['num_values']) {
						form_set_error('format'.$lang, t('Invalid variable "@v" in format string.', array('@v' => $fmt)));
					}
				}
			}
		}
	}else if ($values['op'] == 'Delete'){
		$view_result = views_get_view_result('list_message_reference', 'panel_pane_1', $form['#nid']);
		if (count($view_result) > 0) {
			form_set_error('title', "You should remove the items referencing this message!");
		}
		$view_result = views_get_view_result('list_message_reference_from_field_collection', 'panel_pane_1', $form['#nid']);
		if (count($view_result) > 0) {
			form_set_error('title', "You should remove the items referencing this message!");
		}
	}
}

function ocs_admin_message_form_submit($form, &$form_state)
{
	ctools_include('node.pages', 'node', '');
	ctools_include('ajax');
	
	$values = $form_state['values'];
	$isNew = FALSE;
	// dpm($values, 'submit values');
	// dpm( $form, 'form');

	if ($values['op'] == 'Save') {
		if ($form['#op'] == 'edit') {
			$node = node_load($form['#nid']);
		}
		else {
			$node = ocs_admin_get_new_node('ocs_messages');
			$isNew = TRUE;
		}
		$node->title = $values['title'];

		$node->field_scheduled_delivery['und'][0]['value'] = $values['flag'];
		$node->field_value['und'][0]['value'] = isset($values['delivery_date'])? $values['delivery_date']:3;
		$node->field_valid_date_hour['und'][0]['value'] = isset($values['delivery_time'])? $values['delivery_time']:'00';
		
		$delivery_time = isset($node->field_valid_date_hour['und'][0]['value'])?$node->field_valid_date_hour['und'][0]['value']:"00";
		
		$options = $form['#options'];
		// flatten $options[1], counter
		$options[1] = array_get_value($options[1]);
		dsm($values['num_values'], 'num_values');
		
		for ($i = 1; $i <= $values['num_values']; $i++) {
			$type = $values['type:' . $i];
			$node->field_ocs_value_type['und'][$i - 1]['value'] = $type;
			$node->field_ocs_value['und'][$i - 1]['value'] = $values['value:' . $i];
			$node->field_ocs_value_format['und'][$i - 1]['value'] = isset($values['format:' . $i]) ? $values['format:' . $i] : '';

			if ( $type == OCS_MESSAGE_SCRIPT) {
				$node->field_ocs_value_str['und'][$i - 1]['value'] = $values['value:' . $i];
			}
			else {
				$node->field_ocs_value_str['und'][$i - 1]['value'] = $options[$type][$values['value:' . $i]];
			}
		}

		global $supported_lang;
		$lang_idx = 0;
		foreach( $supported_lang as $lang) {
			$node->field_ocs_format['und'][$lang_idx]['value'] = $values['format'.$lang];

			// get parameter list from message format
			if (preg_match_all('/%\d+/', $values['format'.$lang], $matches) > 0) {
				foreach ($matches[0] as $pivot) {

					// pivot : %1 => idx:1
					$idx = substr($pivot, 1);
					$type = $values['type:' . $idx];
					if ($type == OCS_MESSAGE_PARAMETER) {// parameter
						$value_str = $options[$type][$values['value:' . $idx]] . 
							(isset($values['format:' . $idx]) ? ',' . $values['format:' . $idx] : '');
					}
					else if ($type == OCS_MESSAGE_COUNTER) {// counter
						$value_str = 'counter' . $values['format:'.$idx] . ',' . $values['value:' . $idx];
					}
					else if ($type == OCS_MESSAGE_COUNTER_GROUP) {// counter group
						$value_str = 'counter_group,' . $values['value:' . $idx];
					}
					else if ($type == OCS_MESSAGE_SCRIPT) {
						$value_str = 'script,' . $values['value:' . $idx];
					}
					else {
						dsm('Undefined message type : '. $type, 'error');
						continue;
					}
					$node->field_ocs_export_format['und'][$idx - 1]['value'] = $value_str;
				}
			}
			$lang_idx ++;
		}
		dsm($node, 'node');
		node_save($node);
		$msg_create_or_update = ($isNew == TRUE)? 'created.':'updated.';
		drupal_set_message($node->type. ' ' . $node->title . ' has been '. $msg_create_or_update);
		
		$path = 'config/ocs/message/'.$node->nid.'/edit';
		$options = array();
		$options['fragment'] = 'quickset-ocs_quick_tab=1';
		unset($_GET['destination']);
		drupal_goto($path, $options);
	}else if ($values['op'] == 'Delete') {
		node_delete($form['#nid']);
	}
	return;
}

/*
function ocs_admin_message_delete_confirm($form, &$form_state, $nid)
{
	$name = isset($_GET['name']) ? strip_tags($_GET['name']) : 'Message ID:' . $nid;

	$form['#nid'] = $nid;
	$form['#name'] = $name;

	$caption = t('<strong>Warning:</strong> Message <em>"@name"</em> will be deleted.<br>', array('@name' => $name));

	// check if the message belongs to any message group
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'ocs_message_group')
		->fieldCondition('field_ocs_message_list', 'nid', $nid)->execute();

	if (count($result) > 0) {
		$caption .= 'The Message is also included in the following message group.<br><br><ul>';
		foreach (array_keys( $result['node']) as $msg_nid) {
			$msg = node_load($msg_nid);
			$caption .= '<li>' . $msg->title . '</li>';
		}
		$caption .= '</ul>';
	}

	//    $caption .= '<p>'. t('This action cannot be undone.') . '</p>';

	return confirm_form($form, t('Are you sure to delete the message ?'), 'config/ocs/message/', $caption, t('Delete'));
}

function ocs_admin_message_delete_confirm_submit($form, &$form_state)
{
	$nid = $form['#nid'];
	node_delete($nid);

	drupal_set_message(t('The message "@name" has been delete.', array('@name' => $form['#name'])));
}
*/

function ocs_admin_message_group_form_validate($form, &$form_state){
	if ($form_state['values']['op'] == 'Delete') {
		$view_result = views_get_view_result('list_message_reference', 'panel_pane_1', $form['#nid']);
		if (count($view_result) > 0) {
			form_set_error('title', "You should remove the items referencing this message!");
		}
		$view_result = views_get_view_result('list_message_reference_from_field_collection', 'panel_pane_1', $form['#nid']);
		if (count($view_result) > 0) {
			form_set_error('title', "You should remove the items referencing this message!");
		}
	}
}

// add or edit message group
function ocs_admin_message_group_form($form, &$form_state, $nid = NULL, $op = NULL)
{
	$num_values = isset($form_state['values']['num_values']) ? $form_state['values']['num_values'] : 0;

	$title = '';
	$format = '';
	if ($op == 'edit') {
		$node = node_load($nid);
		//        dpm( $node, 'node');
		if ($node) {
			$title = $node->title;
			if (!isset($form_state['values']['num_values'])) {
				if(isset($node->field_ocs_message_list['und'])){
					$num_values = count($node->field_ocs_message_list['und']);
				}else{
					$num_values = 0;
				}
			}
		}
	}

	$form['#nid'] = $nid;
	$form['#op'] = $op;
	$form['#attributes'] = array('class' => array('myform'));

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => 'Message Name',
		'#default_value' => $title,
		'#required' => TRUE,
	);

	$form['valueset'] = array(
		'#type' => 'fieldset',
		'#title' => 'Messages',
		'#prefix' => '<div id="message_format_div">',
		'#suffix' => '</div>',
	);

	$form['valueset']['num_values'] = array(
		'#type' => 'select',
		'#title' => 'Number of Messages',
		'#options' => array(
			0,
			1,
			2,
			3,
			4,
			5,
			6,
			7,
			8,
			9,
			10
		),
		'#default_value' => $num_values,
		'#ajax' => array(
			'callback' => 'ocs_admin_ajax_message_form_callback',
			'wrapper' => 'message_format_div',
		),
		'#prefix' => '<div class="inner-box-1">',
		'#suffix' => '</div>',
	);

	$options = ocs_admin_get_message_list();

	for ($i = 1; $i <= $num_values; $i++) {
		$form['valueset']['value' . $i] = array(
			'#type' => 'select',
			'#title' => 'Message %' . $i,
			'#options' => $options,
			'#default_value' => isset($node) ? $node->field_ocs_message_list['und'][$i - 1]['nid'] : '',
			'#prefix' => '<div class="inner-box-1">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('long_field')),
		);
	}

	$form['actions'] = array('#type' => 'actions');

	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);

	if ($op == 'edit') {
		$form['actions']['delete'] = array(
			'#type' => 'submit',
			'#value' => t('Delete'),
		);
	}

	return $form;
}

// return the format string of a message group
function ocs_message_group_format($nid)
{
	$node = node_load($nid);

	$format = '';
	if (isset($node->field_ocs_message_list['und'])) {
		foreach ($node->field_ocs_message_list['und'] as $msg) {
			$msg_node = node_load($msg['nid']);
			if (!empty($msg_node))
				$format .= $msg_node->field_ocs_format['und'][0]['value'] . "\n" ;
		}
	}
	return $format;
}

function ocs_admin_message_group_form_submit($form, &$form_state)
{
	$values = $form_state['values'];
	//dpm($values, 'submit values');
	//dpm($form, 'form');

	if ($values['op'] == 'Save') {
		if ($form['#op'] == 'edit') {
			$node = node_load($form['#nid']);
			if(isset($node->field_ocs_message_list['und'])){
      	$totalList = $node->field_ocs_message_list['und'];
				$remains = array_slice($totalList,0,$values['num_values']);
      	$node->field_ocs_message_list['und'] = $remains;
			}
		}
		else {
			$node = ocs_admin_get_new_node('ocs_message_group');
		}
		$node->title = $values['title'];

		for ($i = 1; $i <= $values['num_values']; $i++) {
			$node->field_ocs_message_list['und'][$i - 1]['nid'] = $values['value' . $i];
		}
		node_save($node);
		
		$path = 'config/ocs/message/group/'.$node->nid.'/edit';
		$options = array();
		$options['fragment'] = 'quickset-ocs_quick_tab=1';
		unset($_GET['destination']);
		drupal_goto($path, $options);
	}else if ($values['op'] == 'Delete') {
		node_delete($form['#nid']);
	}
}

/*
function ocs_ussd_code_form( &$form, &$form_state)
{
    $options = array();
    foreach( array_keys($form['field_notification_message']['und']['#options']) as $nid) {
        $node = node_load( $nid);
        if ( ! empty( $node)) {
            $options[$node->type][$nid] = $node->title;
            if ( $node->type == 'ocs_messages') {
                $options[$node->type][$nid] .= ' : ' . $node->field_ocs_format['und'][0]['value'];
            }
            else {
                $text = '';
                foreach( $node->field_ocs_message_list['und'] as $idx => $msg_nid) {
                    $msg = node_load( $msg_nid);
                    $text .= $msg->field_ocs_format['und'][0]['value'] . ' ' ;
                }
                $options[$node->type][$nid] .= ' : ' . $text;
            }
        }
    }
    
    unset($form['actions']['delete']);
    
    $form['field_notification_message']['und']['#options'] = $options;
    $form['field_notification_message']['#attributes'] = array('class' => array( 'long_field'));
}

function ocs_ussd_code_node_form_validate( $form, &$form_state)
{
	// only check unique in case 'CREATE'	
	if(!isset($form['nid']['#value'])) {
		// check USSD code format 
		$valid_code = TRUE;
		$code = $form_state['values']['title'];
		if ( substr( $code, 0, 1) == '*' && substr( $code, -1 ) == '#') {
			for( $i=1; $i < strlen($code)-1; $i++) {
				$c = substr( $code, $i, 1);
				if ( ! (is_numeric( $c) || $c == '*')) {
					$valid_code = FALSE;
					break;
				}
			}
		}
		else {
			$valid_code = FALSE;
		}

		if ( $valid_code === FALSE) {
	        form_set_error('title', t( 'Invalid USSD code format'));
			return;
		}

		// check if the ussd code exist already
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'ocs_ussd_code')
			->propertyCondition('title', $form_state['values']['title'])
	        ->execute();
	
	    if ( ! empty( $result) )  {
	        form_set_error('title', t( 'USSD code @code exist already', array( '@code' => $form_state['values']['title'])));
	    }
	}
}
*/

