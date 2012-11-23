<?php

function ocs_admin_message_form( $form, &$form_state, $nid = NULL, $op = NULL)
{
    $num_values = isset( $form_state['values']['num_values']) ? $form_state['values']['num_values'] : 0;

    $title = '';
    $format = '';
    if ( $op == 'edit') {
        $node = node_load( $nid);
//        dpm( $node, 'node');
        if ( $node) {
            $title = $node->title;
            $format = $node->field_ocs_format['und'][0]['value'];
            if ( ! isset( $form_state['values']['num_values'])) {
                $num_values = count( $node->field_ocs_value['und']);
            }
        }
    }

    $form['#nid'] = $nid;
    $form['#op'] = $op;
    $form['#attributes'] = array( 'class' => array( 'myform'));
    
    $form['title'] = array(
        '#type' => 'textfield',
        '#title' => 'Message Name',
        '#default_value' => $title,
    );

    $form['format'] = array(
        '#type' => 'textarea',
        '#title' => 'Format',
        '#default_value' => $format,
        '#description' => 'Enter message format in "printf" style. Use "%1, %2" to substitue numeric value.'.
            '<br>Ex) "You have remains %1 won."',
    );
    
    $form['valueset'] = array(
        '#type' => 'fieldset',
        '#title' => 'Variables',
        //'#description' => 'Use following counter names to build the message string. : '. implode( ', ', array_keys( $counters)),
        '#prefix' => '<div id="message_format_div">',
        '#suffix' => '</div>',
    );

    $form['valueset']['num_values'] = array(
        '#type' => 'select',
        '#title' => 'Number of Variables',
        '#options' => array( 0, 1,2,3,4,5,6,7,8,9,10),
        '#default_value' => $num_values,
        '#ajax' => array(
            'callback' => 'ocs_admin_ajax_message_form_callback',
            'wrapper' => 'message_format_div',
        ),
    	'#prefix' => '<div class="inner-box-1">',
    	'#suffix' => '</div>',
    );


	// get parameter list of action '_ocs_notification_message'
	$params = new OcsParam;
	$params->load( 18485, NULL);

	// get parameter list
	$param_list = $params->keylist();
	$param_options = array();
	foreach( $param_list as $key) {
		$param_options[$key] = $params->get_title($key);
	}
	
	// Notification Message parameters consist of following three types
    $param_types = array( 'Parameter', 'Counter', 'Counter Group' );

    // get option list for each type	
	$options[0] = $param_options;
	$options[1] = ocs_admin_get_counter_id_list();
   	$options[2] = ocs_admin_get_counter_group_list();
   	$form['#options'] = $options;
    	
	for( $i =1; $i<= $num_values; $i++) {
		$type = isset( $form_state['values']['type:'.$i]) ? $form_state['values']['type:'.$i] : 
			( ($op == 'edit') ? $node->field_ocs_value_type['und'][$i-1]['value']: 0);
			
        $form['valueset'][$i] = array(
            '#type' => 'fieldset',
        	'#title' => 'Variable %'.$i,
       		'#prefix' => '<div class="inner-box-1">',
       		'#suffix' => '</div>',
        );
        $form['valueset'][$i]['type:'.$i] = array(
            '#type' => 'select',
            '#title' => 'Type',
        	'#options' => $param_types,
        	'#default_value' => $type,
       		'#prefix' => '<div class="inner-box-2">',
       		'#suffix' => '</div>',
            '#ajax' => array(
                'callback' => 'ocs_admin_ajax_variable_type_callback',
                'wrapper' => 'ocs_variable_type_div'.$i,
            ),
        );

        $form['valueset'][$i]['valueset'.$i] = array(            
        	'#type' => 'fieldset',
       		'#prefix' => t('<div id="ocs_variable_type_div@i" class="inner-box-2">', array( '@i' => $i)),
       		'#suffix' => '</div>',
       	);
                
        $form['valueset'][$i]['valueset'.$i]['value'.$i] = array(
            '#type' => 'select',
            '#title' => $param_types[$type],
        	'#options' => $options[$type],
        	'#default_value' => isset( $form_state['values']['value'.$i]) ? $form_state['values']['value'.$i] : 
        		( ($op == 'edit') ? $node->field_ocs_value['und'][$i-1]['value'] : ''),
        );
        
        if ( $type == 0) {
            $form['valueset'][$i]['valueset'.$i]['format:'.$i] = array(
                '#type' => 'textfield',
                '#title' => 'Format',
                '#size' => 30,
                '#default_value' => isset( $form_state['values']['value'.$i]) ? $form_state['values']['value'.$i] :
                	(($op == 'edit') ? $node->field_ocs_value_format['und'][$i-1]['value'] : ''),
            );
         }
    }
    

    $form['actions'] = array('#type' => 'actions');

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );

    $form['actions']['cancel'] = array(
        '#type' => 'submit',
        '#value' => t('Cancel'),
    );

    return $form;
}

// ajax handlers

function ocs_admin_ajax_message_form_callback( $form, &$form_state)
{
    return $form['valueset'];
}

function ocs_admin_ajax_variable_type_callback( $form, &$form_state)
{
    list( $name, $idx) = explode(':', $form_state['triggering_element']['#name']);
    return $form['valueset'][$idx]['valueset'.$idx];
}

function ocs_admin_message_form_validate( $form, &$form_state)
{
    $values = $form_state['values'];

    if ( $values['op'] == 'Save') {
        foreach( array( 'title', 'format') as $key) {
            if ( empty( $values[$key])) {
                form_set_error( $key, $form[$key]['#title']. ' is empty'); 
            }
        }

        // check format string
        $format = str_word_count( $values['format'], 1, '%0123456789');
        foreach( $format as $fmt) {
            if ( substr( $fmt, 0, 1) == '%') {
                // check the variable number
                if ( substr( $fmt, 1) > $values['num_values']) {
                    form_set_error( 'format', t( 'Invalid variable "@v" in format string.', array( '@v' => $fmt)));
                }
            }
        }
    }
}


function ocs_admin_message_form_submit( $form, &$form_state)
{
    $values = $form_state['values'];
	dpm( $values, 'submit values');
	// dpm( $form, 'form');
	
    if ( $values['op'] == 'Save') {   
        if ( $form['#op'] == 'edit') {
            $node = node_load( $form['#nid']);
        }
        else {
            $node = ocs_admin_get_new_node( 'ocs_messages');
        }
        $node->title = $values['title'];
        $node->field_ocs_format['und'][0]['value'] = $values['format'];

        $options = $form['#options'];
        // flatten $options[1], counter
        $options[1] = array_get_value( $options[1]);
        dpm( $options, 'options'); 
        
        for( $i=1; $i <= $values['num_values']; $i++) {
            $type = $values['type:'.$i];
            $node->field_ocs_value_type['und'][$i-1]['value'] = $type; 
            $node->field_ocs_value['und'][$i-1]['value'] = $options[$type][$values['value'.$i]];
            $node->field_ocs_value_format['und'][$i-1]['value'] = isset($values['format:'.$i]) ? $values['format:'.$i] : '';
        }

        // get parameter list from message format
        if ( preg_match_all( '/%\d+/', $values['format'], $matches) > 0) {
          	foreach( $matches[0] as $pivot) {
          		
          		// pivot : %1 => idx:1
           		$idx = substr( $pivot, 1);
           		$type = $values['type:'.$idx];
           		if ( $type == 0) {	// parameter
           			$value_str = $node->field_ocs_value['und'][$idx-1]['value'] .
           				( isset( $values['format:'.$idx]) ? ','.$values['format:'.$idx] : '');
           		}
				else if ( $type == 1) {	// counter
           			$value_str = 'counter_value,'. $values['value'.$idx];
           		}
				else {	// counter group
					$value_str = 'counter_group,' . $values['value'.$idx];
				}
           		$node->field_ocs_value_str['und'][$idx-1]['value'] = $value_str;
			}
        }
        
        node_save( $node);
    }
}


function ocs_admin_message_delete_confirm( $form, &$form_state, $nid)
{
	$name = isset( $_GET['name']) ? strip_tags($_GET['name']) : 'Message ID:' . $nid;

    $form['#nid'] = $nid;
    $form['#name'] = $name;

    $caption = t('<strong>Warning:</strong> Message <em>"@name"</em> will be deleted.',
        array( '@name' => $name));

//    $caption .= '<p>'. t('This action cannot be undone.') . '</p>';

    return confirm_form( $form, t('Are you sure to delete the message ?'),
        'config/ocs/message/', $caption, t('Delete'));
}

function ocs_admin_message_delete_confirm_submit( $form, &$form_state)
{
    $nid = $form['#nid'];
    node_delete( $nid);

    drupal_set_message( t('The message "@name" has been delete.', array( '@name' => $form['#name'])));
}

// add or edit message group
function ocs_admin_message_group_form( $form, &$form_state, $nid = NULL, $op = NULL)
{
    $num_values = isset( $form_state['values']['num_values']) ? $form_state['values']['num_values'] : 0;

    $title = '';
    $format = '';
    if ( $op == 'edit') {
        $node = node_load( $nid);
//        dpm( $node, 'node');
        if ( $node) {
            $title = $node->title;
            if ( ! isset( $form_state['values']['num_values'])) {
                $num_values = count( $node->field_ocs_message_list['und']);
            }
        }
    }

    $form['#nid'] = $nid;
    $form['#op'] = $op;
    $form['#attributes'] = array( 'class' => array( 'myform'));
    
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
        '#options' => array( 0, 1,2,3,4,5,6,7,8,9,10),
        '#default_value' => $num_values,
        '#ajax' => array(
            'callback' => 'ocs_admin_ajax_message_form_callback',
            'wrapper' => 'message_format_div',
        ),
    	'#prefix' => '<div class="inner-box-1">',
    	'#suffix' => '</div>',
    );

	$options = ocs_admin_get_message_list();
            
    for( $i =1; $i<= $num_values; $i++) {
        $form['valueset']['value'.$i] = array(
            '#type' => 'select',
            '#title' => 'Message %'.$i,
        	'#options' => $options,
        	'#default_value' => isset( $node) ? $node->field_ocs_message_list['und'][$i-1]['nid'] : '',
       		'#prefix' => '<div class="inner-box-1">',
       		'#suffix' => '</div>',
       		'#attributes' => array( 'style' => 'width:400px;'),
        );
    }
    

    $form['actions'] = array('#type' => 'actions');

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );

    $form['actions']['cancel'] = array(
        '#type' => 'submit',
        '#value' => t('Cancel'),
    );

    return $form;
}

// return the format string of a message group
function ocs_message_group_format( $nid)
{
	$node = node_load( $nid);
	
	$format = array();
	if ( isset( $node->field_ocs_message_list['und'])) {
		foreach( $node->field_ocs_message_list['und'] as $msg) {
			$msg_node = node_load( $msg['nid']);
			$format[] = $msg_node->field_ocs_format['und'][0]['value'];
		}
	}
	return implode( ' ', $format);
}

function ocs_admin_message_group_form_submit( $form, &$form_state)
{
    $values = $form_state['values'];
	dpm( $values, 'submit values');
	dpm( $form, 'form');
	
    if ( $values['op'] == 'Save') {   
        if ( $form['#op'] == 'edit') {
            $node = node_load( $form['#nid']);
        }
		 else {
            $node = ocs_admin_get_new_node( 'ocs_message_group');
        }
        $node->title = $values['title'];
 
        for( $i=1; $i <= $values['num_values']; $i++) {
            $node->field_ocs_message_list['und'][$i-1]['nid'] = $values['value'.$i];  
        }
        
        node_save( $node);
	}
}
