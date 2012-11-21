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
    
    $counters = ocs_admin_get_counter_id_list();
    $counter_name_to_id = array_flip( array_get_value( $counters));
    $form['#counters']  = $counters;

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

    for( $i =1; $i<= $num_values; $i++) {
        $form['valueset']['value'.$i] = array(
            '#type' => 'select',
            '#title' => 'Variable %'.$i,
        	'#options' => $counters,
        	'#default_value' => isset( $node) ? $counter_name_to_id[$node->field_ocs_value['und'][$i-1]['value']] : '',
       		'#prefix' => '<div class="inner-box-1">',
       		'#suffix' => '</div>',
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

// ajax handlers

function ocs_admin_ajax_message_form_callback( $form, &$form_state)
{
    return $form['valueset'];
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
	// dpm( $values, 'submit values');
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

        $counters = array_get_value( $form['#counters']);
        // dpm( $counters, 'counters');
        
        for( $i=1; $i <= $values['num_values']; $i++) {
            $node->field_ocs_value['und'][$i-1]['value'] = $counters[$values['value'.$i]];
        }

        // get parameter list from message format
        $value_str = array();
        if ( preg_match_all( '/%\d+/', $values['format'], $matches) > 0) {
          	foreach( $matches[0] as $pivot) {
          		// pivot : %1 => idx:1
           		$idx = substr( $pivot, 1);
           		$value_str[] = t( '"counter_value(@idx)"', array( '@idx' => $values['value'.$idx]));
           	}
        }
        $node->field_ocs_value_str['und'][0]['value'] = implode( ', ' , $value_str);
        
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
 
         unset( $node->field_ocs_message_list);
         for( $i=1; $i <= $values['num_values']; $i++) {
            $node->field_ocs_message_list['und'][$i-1]['nid'] = $values['value'.$i];  
        }
        
        node_save( $node);
	}
}