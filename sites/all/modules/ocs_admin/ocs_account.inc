<?php

/*
** generate for for ocs_account/add page

    3 possible implementation

    ocs_admin_account_add_form_popup : popup version
    ocs_admin_account_add_form_panel : panel version
    ocs_admin_account_add_form_innertable : inner table version
*/
function ocs_admin_account_add_page( $impl = NULL, $arg = NULL, $init = TRUE) 
{
    if ( ! isset($_SESSION['ocs_admin_account_add'])) {
        $_SESSION['ocs_admin_account_add'] = array();
    }

    $_SESSION['ocs_admin_account_add'] = array_merge( $_SESSION['ocs_admin_account_add'], $_GET);

    $form = drupal_get_form('ocs_admin_account_add_form_wizard', $_SESSION['ocs_admin_account_add']);
    $output = '<div id="ocs_admin_account_add_form_div">' . drupal_render( $form) . '</div>';

    return $output;
}


/*
** PHP function that shall be called in the view block
*/
function ocs_admin_account_select_row( $args)
{
    //ctools_include('ajax'); // Module  include the dependence it needs for ajax.
    drupal_add_library('system', 'drupal.ajax');
    $dest = current_path() . '/nojs'. (is_array( $args) ? '' : $arg);
    return l( t('select'), $dest, array('html' => TRUE, 
        'attributes' => array('class' => array('use-ajax')),
        'query' => (is_array($args) ? $args : NULL)
        ));
}

/*
**  ajax select button in account & product table
    impl: _panel, _popup, and etc
*/
function ocs_account_select( $impl, $js = NULL, $type = 'customer', $id = NULL, $name = NULL)
{
    $arg = array( 
        $type . '_id' => $id, 
        $type . '_name' => $name,
    ); 

    $output = ocs_admin_account_add_page( $impl, $arg);

    if ( $js) {
        ctools_include('ajax');
        $commands = array();
        $commands[] = ajax_command_replace( '#ocs_admin_account_add_form_div', $output);
        print ajax_render( $commands);
        exit;
    }
    else {
        return $output;
    }
}



   /* table example
   $header = array(
        array(
            'data' => 'Attributes',
            'width' => 100,
        ),
        array(
            'data' => 'Values',
            'colspan' => 2,
        ),
    );

   $rows = array(
        array(
            array( 'data' => 'Customer', 'rowspan' => 2),
            array( 'data' => 'ID', 'width' => 100), 
            $customer_id,
        ),
        array( 'Name', 
            $customer_name
            ),
   );

    $form['table'] = array(
        '#type' => 'markup',
        '#markup' => theme( 'table', array( 'header' => $header, 'rows' => $rows)),
        '#prefix' => '<div id="ocs_admin_account_customer_form_div">',
        '#suffix' => '</div>',
    );
    */

function ocs_admin_account_add_form_panel( $form, &$form_state, $arg=NULL)
{
    $form = array();

    $form['customer'] = array(
        '#type' => 'fieldset',
        '#title' => t('Customer'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#prefix' => '<div id="ocs_admin_account_customer_form_div">',
        '#suffix' => '</div>',
    );

    $form['customer']['customer_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Customer ID'),
        '#default_value' => isset($arg['customer_id']) ? $arg['customer_id'] : '',
        '#required' => TRUE,
        '#description' => t('<a href="#@link">Select a customer</a> to add an account', 
            array( '@link' => 'select_customer')),
        '#size' => '30',
    );

    $form['customer']['customer_name'] = array(
        '#type' => 'item',
        '#title' => t('Name : @name', 
            array('@name' => isset($arg['customer_name']) ? $arg['customer_name'] : '')),
    );

    $form['product'] = array(
        '#type' => 'fieldset',
        '#title' => t('Product'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#prefix' => '<div id="ocs_admin_account_product_form_div">',
        '#suffix' => '</div>',
    );

    $form['product']['product_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Product ID'),
        '#default_value' => isset($arg['product_id']) ? $arg['product_id'] : '',
        '#required' => TRUE,
        '#description' => t('<a href="#@link">Select a product</a> to assign', 
            array( '@link' => 'select_product')),
        '#size' => '30',
    );

    $form['product']['product_name'] = array(
        '#type' => 'item',
        '#title' => t('Name : @name', 
            array('@name' => isset($arg['product_name']) ? $arg['product_name'] : '')),
    );

    $form['account_key'] = array(
        '#type' => 'fieldset',
        '#title' => t('Account Key (MSISDN)'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#prefix' => '<div id="ocs_admin_account_key_form_div">',
        '#suffix' => '</div>',
    );

    $form['account_key']['account_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Account Key'),
        '#description' => t('Key of Account such as MSISDN or User Name'),
        '#default_value' => isset($arg['key_id']) ? $arg['key_id'] : '',
        '#required' => TRUE,
        '#description' => t('<a href="#@link">Select an account key</a> to assign', 
            array( '@link' => 'select_key')),
        '#size' => '30',
    );

    $form['account_key']['key_type'] = array(
        '#type' => 'item',
        '#title' => t('Account Type : @name', 
            array('@name' => isset($arg['key_name']) ? $arg['key_name'] : '')),
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Confirm'),
        '#submit' => array('ocs_admin_account_add_form_panel_submit'),
    );

    $form['cancel'] = array(
        '#type' => 'submit',
        '#value' => t('Cancel'),
        '#submit' => array('ocs_admin_account_add_form_panel_submit'),
    );

//    dpm( $form_state, 'form state: ');
//    ddebug_backtrace();

    return $form;
}

function ocs_admin_account_add_form_panel_validate( $form, &$form_state)
{
//    dpm( $form_state, 'validate: ');

    // check parameters
    $account_key = ocs_admin_account_key_load( $form_state['values']['account_key']);
    if ( ! $account_key) {
        form_set_error( 'account_key', 'Invalid account key');
    }

    $customer_id = ocs_admin_customer_load( $form_state['values']['customer_id']);
    if ( ! $customer_id) {
        form_set_error( 'customer_id', 'Invalid customer ID');
    }

    $product_id = ocs_admin_product_load( $form_state['values']['product_id']);
    if ( ! $product_id) {
        form_set_error( 'product_id', 'Invalid product ID');
    }
}

function ocs_admin_account_add_form_panel_submit( $form, &$form_state)
{
    $form_state['redirect'] = 'account';
    dpm( $form_state, 'submit: ');

    if ( $form_state['values']['op'] == 'Confirm') {
        // save to DB
        dsm( 'confirmed: ');
        if ( ocs_admin_account_add( $form_state['values'])) {
            drupal_set_message( 'A new account is created.');
        }
    }
}


function ocs_admin_form_ocs_admin_account_add_form_panel_alter( &$form, &$form_state, $form_id) 
{
    $form['#action'] = url('account/add/_panel');
}

/*
** save to DB
*/
/*
function ocs_admin_db_account_add( $values) 
{
    db_set_active('ocsdb');

    $txn = db_transaction();

    $fields = array(
        'customer_id' => $values['customer_id'],
        'product_id' => $values['product_id'],
    );

    try {
        $id = db_insert('ocs_account')
            ->fields( $fields)
            ->execute();
        dpm( $id, 'db insert');

        return $id;
    }
    catch( Exception $e) {
        $txn->rollback();
        // Log the exception to watchdog.
        watchdog_exception('type', $e);
        dpm( $e, 'db insert failed');
    }

    db_set_active('default');
 }
 */

/* 
** build form for adding account
** wizard table version
*/

// function ocs_admin_account_add_form_wizard( $form, &$form_state, $arg = NULL)
function ocs_admin_account_add_form_wizard( $form, &$form_state, $type, $arg = NULL)
{
    if (($type == 'add') && (count($_GET) == 1))
        $_SESSION['ocs_admin_account_add'] = array();    
    else
        $_SESSION['ocs_admin_account_add'] = array_merge( $_SESSION['ocs_admin_account_add'], $_GET);

	ctools_include( 'ajax');
	ctools_include( 'modal');

	ctools_modal_add_js();

	// Create our own javascript that will be used to theme a modal.
	$sample_style = array(
		'ctools-sample-style' => array(
			'modalSize' => array(
				'type' => 'fixed',
				'width' => 800,
				'height' => 400,
				'addWidth' => 20,
				'addHeight' => 15,
			),
			'modalOptions' => array(
				'opacity' => .5,
				'background-color' => '#000',
			),
			'animation' => 'fadeIn',
			'modalTheme' => 'CToolsSampleModal',
			'throbber' => theme('image', array('path' => ctools_image_path('ajax-loader.gif', 'ctools_ajax_sample'), 'alt' => t('Loading...'), 'title' => t('Loading'))),
		),
	);

	drupal_add_js($sample_style, 'setting');

	// Since we have our js, css and images in well-known named directories,
	// CTools makes it easy for us to just use them without worrying about
	// using drupal_get_path() and all that ugliness.
	ctools_add_js('ctools-ajax-sample', 'ocs_admin');
	ctools_add_css('ctools-ajax-sample', 'ocs_admin');
/*
	$customer_button = ctools_modal_text_button( t('Search'), 
			'ocs/nojs/select/customer', 'Search Customer', 'ctools-modal-ctools-sample-style');
	$product_button = ctools_modal_text_button( t('Search'), 
			'ocs/nojs/select/product', 'Search Product', 'ctools-modal-ctools-sample-style');
	$key_button = ctools_modal_text_button( t('Search'), 
			'ocs/nojs/select/account_key', 'Search Account Key', 'ctools-modal-ctools-sample-style');
*/
    
    $customer_button = l(t('Search'), 'ocs/nojs/select/customer',
        array('html' => TRUE,
            'attributes' => array('class' => array('use-ajax', 'ctools-modal-ctools-sample-style'),
                                  'title' => 'Search Customer'),
             )
    );

    $product_button = l(t('Search'), 'ocs/nojs/select/product',
        array('html' => TRUE,
            'attributes' => array('class' => array('use-ajax', 'ctools-modal-ctools-sample-style'),
                                  'title' => 'Search Product'),
             )
    );

    $key_button = l(t('Search'), 'ocs/nojs/select/account_key',
        array('html' => TRUE,
            'attributes' => array('class' => array('use-ajax', 'ctools-modal-ctools-sample-style'),
                                  'title' => 'Search Account Key'),
             )
    );
    ///////////////////////// customer list
    $form = array();
    $form['section'] = array(
        '#type' => 'fieldset',
        '#description' => 'Input parameters to create an account.',
    );

	$form['section']['reset'] = array(
		'#type' => 'submit',
		'#value' => 'Reset',
	);

    $form['customer'] = array(
        '#type' => 'fieldset',
        '#title' => t('Customer'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#description' => t( 'Click the <em>!btn</em> button to find a customer.', 
			array( '!btn' => $customer_button)),
    );

    $form['customer']['container'] = array(
		'#prefix' => '<div class="container-inline form-item">',
		'#suffix' => '</div>',
	);

    $form['customer']['container']['customer_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Customer ID'),
        '#size' => '30',
        '#default_value' => isset( $_SESSION['ocs_admin_account_add']['customer_id']) ? 
                                   $_SESSION['ocs_admin_account_add']['customer_id'] : NULL, 
    );

    $form['customer']['container']['customer_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Customer Name'),
        '#size' => '30',
        '#default_value' => isset( $_SESSION['ocs_admin_account_add']['customer_name']) ? 
                                   $_SESSION['ocs_admin_account_add']['customer_name'] : NULL, 
    );

    $form['customer']['container']['customer_search'] = array(
        '#type' => 'markup',
        '#markup' => $customer_button,
    );

    ////////// product list

    $form['product'] = array(
        '#type' => 'fieldset',
        '#title' => t('Product'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#description' => t( 'Click the <em>!btn</em> button to find a product.',
			array( '!btn' => $product_button)),
//        '#attributes' => array( 'class' => array( 'column')),
    );

    $form['product']['container'] = array(
		'#prefix' => '<div class="container-inline form-item">',
		'#suffix' => '</div>',
	);

    $form['product']['container']['product_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Product ID'),
        '#size' => '30',
        '#default_value' => isset( $_SESSION['ocs_admin_account_add']['product_id']) ? 
                                   $_SESSION['ocs_admin_account_add']['product_id'] : NULL, 
    );

    $form['product']['container']['product_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Product Name'),
        '#size' => '30',
        '#default_value' => isset( $_SESSION['ocs_admin_account_add']['product_name']) ? 
                                   $_SESSION['ocs_admin_account_add']['product_name'] : NULL, 
    );

    $form['product']['container']['product_search'] = array(
        '#type' => 'markup',
        '#markup' => $product_button,
    );


    ////////// account key : MSISDN

    $form['account'] = array(
        '#type' => 'fieldset',
        '#title' => t('Account Key'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#description' => t('Click the <em>!btn</em> button to find an empty account key.',
			array( '!btn' => $key_button)),
    );

    $form['account']['container'] = array(
		'#prefix' => '<div class="container-inline form-item">',
		'#suffix' => '</div>',
	);

    $form['account']['container']['account_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Account Key'),
        '#size' => '30',
        '#default_value' => isset( $_SESSION['ocs_admin_account_add']['account_key']) ? 
                                   $_SESSION['ocs_admin_account_add']['account_key'] : NULL, 
    );

    $form['account']['container']['account_key_name'] = array(
        '#type' => 'select',
        '#title' => t('Key Type'),
        '#options' => array(
            'Gold(Mobile)' => 'Gold(Mobile)',
            'Bronze(Mobile)' => 'Bronze(Mobile)',
        ),
        '#default_value' => isset( $_SESSION['ocs_admin_account_add']['key_type']) ? 
                                   $_SESSION['ocs_admin_account_add']['key_type'] : NULL, 
     );

    $form['account']['container']['account_search'] = array(
        '#type' => 'markup',
        '#markup' => $key_button,
    );

    $form['actions'] = array( '#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Confirm'),
    );

    $form['actions']['cancel'] = array(
        '#type' => 'submit',
        '#value' => t('Cancel'),
    );


    return $form;
}


// display popup window to list customers
// show ocs_account views' block2 display
function ocs_admin_popup_select( $form, &$form_state, $js, $target)
{
	if ( $js) {
		ctools_include( 'modal');
		ctools_include( 'ajax');
	}

	if ( $target == 'customer') {
		$output = module_invoke( 'views', 'block_view', 'ocs_account-select_account');
		$form_state['title'] = t('Choose a Customer');
	}
	else if ( $target == 'product') {
		$output = module_invoke( 'views', 'block_view', 'ocs_product-block_select');
		$form_state['title'] = t('Choose a Product');
	}
	else if ( $target == 'account_key') {
		$output = module_invoke( 'views', 'block_view', 'ocs_account_key-select_account');
		$form_state['title'] = t('Choose an Account Key');
	}

	if ( $js) {		// ajax form
		$commands = ctools_modal_form_render($form_state, $output);
		print ajax_render($commands);
		exit;
	}

	// non ajax form
	$form['view'] = array(
		'#type' => 'markup',
		'#markup' => drupal_render( $output),
	);

	return $form;
}


function ocs_admin_account_add_form_wizard_validate( $form, &$form_state)
{
    // check parameters
    if ( $form_state['values']['op'] == 'Confirm') {
        dpm( $form_state, 'validate: ');

        $account_key = ocs_admin_account_key_load( $form_state['values']['account_key']);
        if ( ! $account_key) {
            form_set_error( 'account_key', 'Invalid account key');
        }

        $customer_id = ocs_admin_customer_load( $form_state['values']['customer_id']);
        if ( ! $customer_id) {
            form_set_error( 'customer_id', 'Invalid customer ID');
        }

        $product_id = ocs_admin_product_load( $form_state['values']['product_id']);
        if ( ! $product_id) {
            form_set_error( 'product_id', 'Invalid product ID');
        }
    }
}

function ocs_admin_account_add_form_wizard_submit( $form, &$form_state)
{
    $values = $form_state['values'];
    if ( $values['op'] == 'Search Customer') {
        $query = array(
            'customer_id' => $values['customer_id'],
            'customer_name' => $values['customer_name'],
        );
        drupal_goto( 'customer/select', array( 'query' => $query));
    }
    else if ( $values['op'] == 'Search Product') {
        $query = array(
            'product_id' => $values['product_id'],
            'product_name' => $values['product_name'],
        );
        drupal_goto( 'product/select', array( 'query' => $query));
    }
    else if ( $values['op'] == 'Search Account Key') {
        $query = array(
            'account_key' => $values['account_key'],
            'account_key_name' => $values['account_key_name'],
        );
        drupal_goto( 'resource/key/select', array( 'query' => $query));
    }
    else {
        $form_state['redirect'] = 'account';
        dpm( $form_state, 'submit: ');

        if ( $values['op'] == 'Confirm') {
            // save to DB
            dsm( 'confirmed: ');
            if ( ocs_admin_account_add( $values)) {
                drupal_set_message( 'A new account is created.');
            }
        }
    }
}

/* 
** build form for adding account
** inner table version
*/
function ocs_admin_account_add_form_innertable( $form, &$form_state)
{
    ///////////////////////// customer list

    $form = array();
    $form['customer'] = array(
        '#type' => 'fieldset',
        '#title' => t('Customer'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
    );

    $form['customer']['customer_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Customer ID'),
        '#ajax' => array(
            'callback' => 'ocs_admin_db_customer_callback',
            'wrapper' => 'replace_customer_list_div',
            'keypress' => TRUE,
        ),
    );

    $form['customer']['customer_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Customer Name'),
        '#ajax' => array(
            'callback' => 'ocs_admin_db_customer_callback',
            'wrapper' => 'replace_customer_list_div',
            'keypress' => TRUE,
        ),
    );

    $form['customer']['customer_list'] = ocs_admin_get_table_form( 'customer');

    ////////// product list

    $form['product'] = array(
        '#type' => 'fieldset',
        '#title' => t('Product'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
    );

    $form['product']['product_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Product ID'),
        '#ajax' => array(
            'callback' => 'ocs_admin_db_product_callback',
            'wrapper' => 'replace_product_list_div',
            'keypress' => TRUE,
        ),
     );

    $form['product']['product_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Product Name'),
        '#ajax' => array(
            'callback' => 'ocs_admin_db_product_callback',
            'wrapper' => 'replace_product_list_div',
            'keypress' => TRUE,
        ),
    );

    $form['product']['product_list'] = ocs_admin_get_table_form( 'product');

    ////////// account key : MSISDN

    $form['account'] = array(
        '#type' => 'fieldset',
        '#title' => t('Account'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
    );

    $form['account']['account_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Account Key'),
        '#ajax' => array(
            'callback' => 'ocs_admin_db_account_callback',
            'wrapper' => 'replace_account_list_div',
            'keypress' => TRUE,
        ),
     );

    $form['account']['account_list'] = ocs_admin_get_table_form( 'account');

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#submit' => array( 'ocs_admin_account_add_submit'),
    );

    if ( !empty( $form_state['values']['customer_name']) || ! empty( $form_state['values']['customer_id'])) {
        $arg = array(
            'name' => $form_state['values']['customer_name'],
            'id' => $form_state['values']['customer_id'],
            );
        $form['customer']['customer_list'] = ocs_admin_get_table_form( 'customer', $arg);
    }

    if ( !empty( $form_state['values']['product_name']) || ! empty( $form_state['values']['product_id'])) {
        $arg = array(
            'name' => $form_state['values']['product_name'],
            'id' => $form_state['values']['product_id'],
            );
        $form['product']['product_list'] = ocs_admin_get_table_form( 'product', $arg);
    }

    if ( !empty( $form_state['values']['account_key'])) {
        $arg = array(
            'key' => $form_state['values']['account_key'],
            );
        $form['account']['account_list'] = ocs_admin_get_table_form( 'account', $arg);
    }

    return $form;
}

function ocs_admin_get_table_form( $type, $arg = NULL)
{
    if ( $type == 'customer') {
        $header = array(
            'customer_id' => 'ID',
            'customer_name' => 'Name',
        );
        $records = ocs_admin_get_customer( $arg);

        $form =  array(
            '#type' => 'tableselect',
            '#header' => $header,
            '#options' => $records,
            '#empty' => t('No content available.'),
            '#prefix' => '<div id="replace_customer_list_div">',
            '#suffix' => '</div>',
        );
    }
    else if ( $type == 'product') {
         $header = array(
            'product_id' => 'ID',
            'product_name' => 'Name',
        );
        $records = ocs_admin_get_product( $arg);

        $form = array(
            '#type' => 'tableselect',
            '#header' => $header,
            '#options' => $records,
            '#empty' => t('No content available.'),
            '#prefix' => '<div id="replace_product_list_div">',
            '#suffix' => '</div>',
        );
   }
   else if ( $type == 'account') {
         $header = array(
            'account_key' => 'Key',
        );
        $records = ocs_admin_get_account( $arg);

        $form = array(
            '#type' => 'tableselect',
            '#header' => $header,
            '#options' => $records,
            '#empty' => t('No content available.'),
            '#prefix' => '<div id="replace_account_list_div">',
            '#suffix' => '</div>',
        );   
    }

    return $form;
}

function ocs_admin_get_customer( $arg = NULL)
{
    db_set_active('ocsdb');
    
    $header = array( 'customer_id', 'customer_name');
    $query = db_select( 'ocs_customer', 'c');
    if ( isset( $arg['name'])) {
        $query->condition( 'c.customer_name', '%'.$arg['name'].'%', 'like');
    }
    if ( isset( $arg['id'])) {
        $query->condition( 'c.customer_id', $arg['id'], '=');
    }
    $query
        ->fields( 'c', $header)
        ->range( 0, 10);

    $result = $query->execute();
    $records = array();
    while( $record = $result->fetchAssoc()) {
        $records[$record['customer_id']] = $record;
    }

    db_set_active('default');

    return $records;
}

function ocs_admin_get_product( $arg = NULL)
{
    db_set_active('ocsdb');
    
    $header = array( 'product_id', 'product_name');
    $query = db_select( 'product', 'p');
    if ( isset( $arg['name'])) {
        $query->condition( 'p.product_name', '%'.$arg['name'].'%', 'like');
    }
    if ( isset( $arg['id'])) {
        $query->condition( 'p.product_id', $arg['id'], '=');
    }
    $query
        ->fields( 'p', $header)
        ->range( 0, 10);

    $result = $query->execute();
    $records = array();
    while( $record = $result->fetchAssoc()) {
        $records[$record['product_id']] = $record;
    }

    db_set_active('default');

    return $records;
}

function ocs_admin_get_account( $arg = NULL)
{
    db_set_active('ocsdb');
    
    $header = array( 'customer_id', 'customer_name');
    $query = db_select( 'ocs_customer', 'c');
    if ( isset( $arg['name'])) {
        $query->condition( 'c.customer_name', '%'.$arg['name'].'%', 'like');
    }
    if ( isset( $arg['id'])) {
        $query->condition( 'c.customer_id', $arg['id'], '=');
    }
    $query
        ->fields( 'c', $header)
        ->range( 0, 10);

    $result = $query->execute();
    $records = array();
    while( $record = $result->fetchAssoc()) {
        $records[$record['customer_id']] = $record;
    }

    db_set_active('default');

    return $records;
}


/*
** ajax callback 
*/
function ocs_admin_db_customer_callback( $form, $form_state)
{
    return $form['customer']['customer_list'];
}

function ocs_admin_db_product_callback( $form, $form_state)
{
    return $form['product']['product_list'];
}

function ocs_admin_db_account_callback( $form, $form_state)
{
    return $form['account']['account_list'];
}

/*
** submit 'account/add'
*/
function ocs_admin_account_add_submit( $form, &$form_state)
{
    dsm( $form_state['values']);
}

function ocs_admin_account_add_form_submit( $form, &$form_state) 
{
    kpr( $form_state, TRUE);
}

/*
** delete an account
*/
function ocs_admin_account_delete_confirm( $form, &$form_state, $account_key)
{
    $form['#account_key'] = $account_key;
    $caption = '<p>' . 
            t('<strong>Warning:</strong> The account "%key" will be deleted.',
                array( '%key' => $account_key)) .
            '</p>';

    $caption .= '<p>'. t('This action cannot be undone.') . '</p>';

    return confirm_form( $form, t('Are you sure to delete the account "%key"?',
        array( '%key' => $account_key)),
        'account',
        $caption, t('Delete'));
}

function ocs_admin_account_edit_form( $form, &$form_state, $account_key)
{
    $form['account_key_markup'] = array(
        '#type' => 'item',
        '#title' => 'Account Key',
        '#markup' => $account_key,
    );

    $form['account_key'] = array(
        '#type' => 'hidden',
        '#value' => $account_key,
    );

    $account = ocs_admin_subscription_load( $account_key);

    $form['subscription_key'] = array(
        '#type' => 'hidden',
        '#value' => $account['subscription_key'],
    );

    $subs = ocs_admin_subscription_load( $account['subscription_key']);
    $form['#subscription'] = $subs;

    $form['subscription_type'] = array(
        '#type' => 'select',
        '#title' => 'Subscription Type',
        '#description' => 'Enter the subscription type',
        '#options' => ocs_admin_get_term_list( 'subscription_type'),
        '#default_value' => $subs['subscription_type'],
    );

    $options = ocs_admin_get_term_list( 'charging_type');

    $form['charging_type'] = array(
        '#type' => 'select',
        '#title' => 'Charging Type',
        '#description' => 'Enter the charging type',
        '#options' => ocs_admin_get_term_list( 'charging_type'),
        '#default_value' => $subs['charging_type'],
    );

    $form['active_expire_date'] = array(
        '#type' => 'date',
        '#title' => 'Active Status Expire Date',
        '#description' => 'Enter the new expiration date',
        '#default_value' => date_parse( $subs['active_expire_date']),
    );

    $form['grace_expire_date'] = array(
        '#type' => 'date',
        '#title' => 'Grace Status Expire Date',
        '#description' => 'Enter the new expiration date',
        '#default_value' => date_parse( $subs['grace_expire_date']),
    );

    $form['notification_flag_set'] = array(
        '#type' => 'select',
        '#title' => 'Notification Flag',
        '#description' => 'Enter the new Notification Flag',
        '#options' => ocs_admin_get_term_list( 'notification_flag_set'),
        '#default_value' => $subs['notification_flag_set'],
    );

    $form['preferred_language'] = array(
        '#type' => 'select',
        '#title' => 'Preferred Language',
        '#description' => 'Select preferred language type',
        '#options' => ocs_admin_get_term_list( 'preferred_language'),
        '#default_value' => $subs['preferred_language'],
    );

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


/*
    submit account info
*/
function ocs_admin_account_edit_form_submit( $form, &$form_state) 
{
    if ( $form_state['values']['op'] == 'Save') {
        $subs = $form['#subscription'];

        // update changed value
        foreach( $form_state['values'] as $key => $value) {
            if ( isset( $subs[ $key ])) {
                if ( $form[ $key]['#type'] == 'date') {
                    // date format
                    $subs[ $key] = sprintf( '%04d-%02d-%02d', $value['year'], $value['month'], $value['day']);
                }
                else {
                    $subs[ $key] = $value;
                }
            }
        }

        ocs_admin_subscription_save( $subs);
    }
    
    $form_state['redirect'] = 'account/all/' . $form_state['values']['account_key'];
}

/*
load counter
*/
function ocs_admin_subscription_load( $subscription_key)
{
    db_set_active('ocsdb');

    $query = db_select( 'ocs_subscription', 'a');
    $result = $query->fields( 'a')
                    ->condition( 'subscription_key', $subscription_key, '=')
                    ->execute()
                    ->fetchAssoc();
   
    db_set_active('default');

    return $result;
}

/*
save counter
*/
function ocs_admin_subscription_save( $data)
{
    db_set_active('ocsdb');

    $result = db_update( 'ocs_subscription')
        ->fields( $data)
        ->condition( 'subscription_key', $data['subscription_key'], '=')
        ->execute();
    dpm( $result, 'db_update ocs_counter result');

    db_set_active('default');
    
    return $result;
}


/*
    save OCS Customer Account
*/
function ocs_admin_account_add( $account)
{
    dpm( debug_backtrace(), 'backtrace');

    if ( ! isset($account['account_key']) || ! isset($account['customer_id'])  ||
        ! isset($account['product_id'])) {
        drupal_set_message( 'Insufficient parameters to create an account', 'warning');
        return FALSE;
    }

    db_set_active( 'ocsdb');

    $txn = db_transaction();
    try {
        // insert record in ocs_subscription table
        $default_value = array(
            'subscription_key' => $account['account_key'],
            'subscription_type' => 0,
            'charging_type' => 0,
            'status' => 0,
            'create_date' => time(),
            'home_info' => '',
            'preferred_language' => 0,
            'notification_flag_set' => 0,
        );

        $result = db_merge( 'ocs_subscription')
            ->key( array( 'subscription_key' => $account['account_key']))
            ->fields( $default_value)
            ->execute();
        dpm( $result, 'db_insert ocs_subscription result');

        // insert record in ocs_account table
        $fields = array( 
            'account_key' => $account['account_key'],
            'status' => 0,
            'subscription_key' => $account['account_key'],
            'customer_id' => $account['customer_id'],
            'product_id' => $account['product_id'],
            );

        $status = db_merge( 'ocs_account')
            ->key( array( 'account_key' => $account['account_key']))
            ->fields( $fields)
            ->execute();
        dpm( $status, 'db_insert ocs_account result');

        // insert record in abmf_account
        $result = db_merge( 'abmf_account')
            ->key( array( 'subscription_key' => $account['account_key']))
            ->fields( array(
                'subscription_key' => $account['account_key'],
            ))
            ->execute();
        dpm( $result, 'db_insert abmf_account result');

        // insert record in ocs_counter_tbl
        // set account_key as used
        $result = _ocs_admin_account_key_save( $account['account_key'], array(
                'sales_flag' => '1',
            ));

    } 
    catch( Exception $e) {
        $txn->rollback();

        dpm( $e, 'DB transaction failed');
        watchdog_exception( 'ocs_admin', $e);
    }

    db_set_active( 'default');
}

function _ocs_admin_account_key_save( $account_key, $fields)
{
    // update account key as used
    $result = db_update( 'ocs_account_key')
        ->fields( $fields)
        ->condition( 'account_key', $account_key, '=')
        ->execute();
    dpm( $result, 'db_update ocs_account_key result');
}

function ocs_admin_account_delete_confirm_submit( $form, &$form_state)
{
    $account_key = $form['#account_key'];
    $group_id = ocs_admin_account_delete($account_key);

    if (is_null($group_id)) {
        $t_args = array( '%key' => $account_key);
        drupal_set_message( t('The account %key has been deleted.', $t_args));
        watchdog( 'ocs_admin', 'Deleted the account %key.', $t_args, WATCHDOG_NOTICE);

        $form_state['redirect'] = 'account';
    } else {  
        $form_state['redirect'] = 'group/' . $group_id . '/edit';
    }
}

/*
    delete account
*/
function ocs_admin_account_delete( $account_key)
{
    db_set_active( 'ocsdb');

    // check the group master number
    $result = db_select('ocs_group', 'g')
        ->fields('g', array('group_id'))
        ->condition('master_number', $account_key, '=')
        ->execute()
        ->fetchAssoc();
        
    if (is_null($result['group_id'])) {
        // delete group member
        $txn = db_transaction();

        try {
            // delete ocs_account
            $result = db_delete( 'ocs_account')
                ->condition( 'account_key', $account_key, '=')
                ->execute();
            dpm( $result, 'ocs_account result');

            $result = db_delete( 'ocs_subscription')
                ->condition( 'subscription_key', $account_key, '=')
                ->execute();
            dpm( $result, 'ocs_subscription result');

            // set account_key as unused
            $result = _ocs_admin_account_key_save( $account_key, array(
                                                   'sales_flag' => '0',
            ));
            // delete group member
            $result = db_delete('ocs_group_member')
                ->condition('account_key', $account_key, '=')
                ->execute();
        } 
            catch( Exception $e) {
                $txn->rollback();

            watchdog_exception( 'ocs_admin', $e);
        }
    } else {
        drupal_set_message( t('You have to change master number[group id:%group_id].', 
                            array('%group_id' => $result['group_id'])));   
    }
    
    db_set_active( 'default');
    
    return $result['group_id'];

}

/*
    load account 
*/
function ocs_admin_account_load( $account_key)
{
    db_set_active('ocsdb');

    $query = db_select( 'ocs_account', 'a');
    $result = $query->fields( 'a')
                    ->condition( 'account_key', $account_key, '=')
                    ->execute()
                    ->fetchAssoc();
   
    db_set_active('default');

    return $result;
}


/*
    load customer info
*/
function ocs_admin_customer_load( $customer_id)
{
   db_set_active('ocsdb');

   $query = db_select( 'ocs_customer', 'g');
   $result = $query->fields( 'g')
        ->condition( 'customer_id', $customer_id, '=')
        ->execute() 
        ->fetchAssoc();
//    dpm( $result, 'fetched customer');

    db_set_active('default');

    return $result;
}

/*
    load account key info
*/
function ocs_admin_account_key_load( $account_key)
{
   db_set_active('ocsdb');

   $query = db_select( 'ocs_account_key', 'g');
   $result = $query->fields( 'g')
        ->condition( 'account_key', $account_key, '=')
        ->execute()
        ->fetchAssoc();
//    dpm( $result, 'fetched account key');

    db_set_active('default');

    return $result;
}
