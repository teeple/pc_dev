<?php

require_once( 'ocs_campaign_action.inc');
require_once( 'ocs_campaign_event.inc');
require_once( 'ocs_campaign_cond.inc');
require_once( 'ocs_campaign_export.inc');

require_once( 'ocs_rule_campaign.inc');

/*
** campaign rules form
*/
function ocs_admin_campaign_rule_form( $form, &$form_state, $campaign_id = NULL)
{
	$form['#attached']['css'] = array(drupal_get_path('module', 'ocs_admin') . '/ocs_admin.css');
	$form['#description'] = '<p>Edit Campaign Rules</p>';
	$form['#campaign_id'] = $campaign_id;

    drupal_add_library( 'system', 'drupal.ajax');

  //****************************
  // get all events
  //****************************
	$form['#campaign'] = ocs_admin_campaign_load( $campaign_id);

    $campaign = new OcsCampaignRules;
    $campaign->load( $campaign_id);

	foreach( $campaign->rules() as $rule_id => $rule) {
        $event_id = $rule->event_id();
        if ( ! isset( $form['#event'][$event_id])) {
            // add new event
            $node = node_load( $event_id);
            $client = taxonomy_term_load( $node->field_ocs_client_id['und'][0]['tid']);

            $info = array(
                'title' => $node->title,
                'name' => $client->name,
                'description' => t( '<em>%event</em> event generated by the system <em>%client</em>',
                    array( '%event' => $node->title, '%client' => $client->name)),
                '#attributes' => array( 'class' => array('menu-enabled')),
                'weight' => array(
                    '#type' => 'weight',
                    '#delta' => 50,
        //        '#default_value' => $item['weight'],
                    '#default_value' => 50,
                    '#title_display' => 'invisible',
                    '#title' => t('Weight for @title', array('@title' => $node->title)),
              ),
            );

            $form['#event'][$event_id] = $info;
            $form['#event'][$event_id]['#event_name'] = $node->title;

            // Build a list of operations
            $operations = array();
            $t_arg = array( '@campaign' => $rule->campaign_id(), '@event' => $rule->event_id());
            $q_arg = array( 'query' => array( 'event_name' => $node->title));

            $operations['add'] = array( 
                '#type' => 'link',
                '#title' => t('Add'),
                '#href' => t( 'campaign/@campaign/event/add', $t_arg),
            );

            $operations['delete'] = array( 
              '#type' => 'link',
              '#title' => t('Delete'),
              '#href' => t( 'campaign/@campaign/event/@event/delete', $t_arg),
              '#options' => $q_arg,
              );

            $operations['edit'] = array( 
                '#type' => 'item',
            );

            $form['#event'][$event_id]['operations'] = $operations;
        }

        // add rules
		// Build a list of operations for rules
        $form['#event'][$event_id]['rule'][$rule_id] = $rule;
	}

	$form['#caption'] = '<h3>Events</h3>';
	$form['#empty_text'] = t('There are no events yet. <a href="@url">Add Event.</a>',
        array( '@url' => url( t('campaign/@campaign/event/add', array( '@campaign' => $campaign_id)), 
            array( 'query' => array('redirect' => current_path())))));
	$form['#no_rule'] = t('There are no rules yet. ');

    return $form;
}


/**
 * Returns HTML for the campaign rules  form into a table.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function theme_ocs_admin_campaign_rule_form($variables) 
{
    $form = $variables['form'];
    $output = ocs_admin_campaign_rule_theme( $form);

	return $output;
}

function ocs_admin_campaign_rule_theme( $form)
{

    $header = array(
        t('Rules'),
        array( 'data' => t('Items'), ),
        array( 'data' => t('Description')),
        array( 'data' => t('Operations'), 'colspan' => '3'),
    );

    $rows = array();
    //  dpm( $form, 'table form');
    if ( isset( $form['#event'])) {
        foreach ($form['#event'] as $event_id => $item) {
            $element = &$form['#event'][$event_id];

            // add event row

            $row = array();
            $row[] = array( 'data' => $element['description'], 'colspan' => '3', 
              'class' => array('event-name', 'bd-top'));
            $row = array_merge( $row, _operation_list( $element['operations']));
            $rows[] = $row;

            // list conditions and actions of each rule
            foreach( $form['#event'][$event_id]['rule'] as $rule) {

                $prefix = t( 'campaign/@id/', array( '@id' => $rule->campaign_id()));
                $rows = array_merge( $rows, $rule->table_rows( $prefix));
            }
        }
    }

    if (empty($rows)) {
        $rows[] = array(array('data' => $form['#empty_text'], 'colspan' => '7'));
    }
    $footer = array(array('data' => isset($form['#footer']) ? $form['#footer'] : '', 
        'colspan' => '7', 'class' => array( 'bd-top')));

    $output = t("<br><p>Target Campaign : <strong>@name</strong></p><br>", array( '@name' => $form['#campaign']['campaign_name']));

    $output .= '<div id="ocs_admin_campaign_rule_div">' ;
    $output .= theme('table', array('header' => $header, 'footer' => $footer, 'rows' => $rows, 'attributes' => array('id' => 'menu-overview')));
    $output .= '</div>';

    return $output;
}

function _operation_list( $list, $class = array())
{
    $operations = array();
    foreach( $list as $op) {
      $operations[] = array( 'data' => drupal_render($op),
        'class' => array_merge( array('menu-operations'), $class));
    }

    return $operations;
}


/*
** Add/Edit campaign rules
*/
function ocs_admin_campaign_rule_edit_form( $form, &$form_state, $type, $campaign_id)
{
    if ( $type == 'edit') {
        // load campaign data
        $campaign = NULL;
    }

    $form['campaign_id'] = array(
        '#type' => 'hidden',
        '#value' => $campaign_id,
    );

    $form['cond_id'] = array(
        '#type' => 'hidden',
        '#value' => isset( $campaign) ? $campaign['cond_id'] : 0,
    );

    $form['parent_id'] = array(
        '#type' => 'hidden',
        '#value' => isset( $campaign) ? $campaign['parent_id'] : 0,
    );

    $form['cond_name'] = array(
        '#type' => 'textfield',
        '#title' => 'Rule Name',
        '#description' => t('Enter Rule Name'),
        '#default_value' => isset( $campaign) ? $campaign['cond_name'] : NULL,
    );

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );

    return $form;
}

function ocs_admin_campaign_rule_edit_form_submit( $form, &$form_state)
{
    $campaign = $form_state['values'];
    dpm( $campaign, 'submit campaign');
    ocs_admin_campaign_rule_save($campaign);

    drupal_set_message( t('Your configuration has been saved.'));

    $form_state['redirect'] = 'campaign/' . $campaign['campaign_id'];
}


/*
** Add/Edit campaign properties
*/
function ocs_admin_campaign_edit_form( $form, &$form_state, $op, $campaign_id = NULL)
{
	$campaign = ocs_admin_campaign_load( $campaign_id);

    $form['campaign_id'] = array(
        '#type' => 'hidden',
        '#value' => $campaign_id,
    );

    $form['campaign_name'] = array(
        '#type' => 'textfield',
        '#title' => 'Name',
        '#default_value' => $campaign['campaign_name'],
    );

    $form['description'] = array(
        '#type' => 'textfield',
        '#title' => 'Description',
        '#default_value' => $campaign['description'],
    );

    $form['status'] = array(
        '#type' => 'select',
        '#title' => 'Status',
        '#options' => array(
			'0' => 'Disabled',
			'1' => 'Enabled',
			),
        '#default_value' => $campaign['status'],
    );

	$date_str = isset($campaign['start_date']) ? $campaign['start_date'] : date( 'Y-m-d', time());
	dpm( $date_str, 'date str');
	$form['start_date'] = array(
		'#type' => 'date',
		'#title' => 'Start Date',
		'#default_value' => date_parse( $date_str),
	);

	$date_str = isset($campaign['end_date']) ? $campaign['end_date'] : date( 'Y-m-d', time());
	$form['end_date'] = array(
		'#type' => 'date',
		'#title' => 'End Date',
		'#default_value' => date_parse( $date_str),
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


function ocs_admin_campaign_edit_form_validate( $form, &$form_state)
{
    $values = $form_state['values'];
	if ( $values['op'] != 'Cancel') {
		// TODO: check start & end date
		$start_date = new DateTime( sprintf( '%04d-%02d-%02d', $values['start_date']['year'] , 
				$values['start_date']['month'] , $values['start_date']['day']));
		$end_date = new DateTime( sprintf( '%04d-%02d-%02d', $values['end_date']['year'] , 
				$values['end_date']['month'] , $values['end_date']['day']));

        if ( $start_date >= $end_date) {
            form_set_error( 'end_date', 'Invalid End Date. It should be later than Start Date.');
        }
	}
}


function ocs_admin_campaign_edit_form_submit( $form, &$form_state)
{
    $values = $form_state['values'];
	if ( $values['op'] != 'Cancel') {
		$values['start_date'] = sprintf( '%04d-%02d-%02d', $values['start_date']['year'] , 
				$values['start_date']['month'] , $values['start_date']['day']);
		$values['end_date'] = sprintf( '%04d-%02d-%02d', $values['end_date']['year'] , 
				$values['end_date']['month'] , $values['end_date']['day']);

		ocs_admin_campaign_save($values);

		drupal_set_message( t('Your configuration has been saved.'));
	}

    $form_state['redirect'] = 'campaign/';
}


function ocs_admin_campaign_load( $campaign_id)
{
    db_set_active('ocsdb');

    // get group information
    $query = db_select( 'ocs_campaign', 'c');
    $result = $query->condition( 'c.campaign_id', $campaign_id, '=')
        ->fields( 'c')
        ->execute()
        ->fetchAssoc( 'event_id', PDO::FETCH_ASSOC);
    
    db_set_active( 'default');

    return $result;
}

function ocs_admin_campaign_save( $campaign)
{
    db_set_active('ocsdb');

	$data = array();
	foreach( array( 'campaign_name', 'description', 'status', 'start_date', 'end_date') as $key) {
		$data[ $key] = $campaign[ $key];
	}

	$result = db_merge( 'ocs_campaign')
		->key( array( 'campaign_id' => $campaign['campaign_id']))
		->fields( $data)
		->execute();

    db_set_active( 'default');

    return $result;
}


/*
** delete campaign
*/
function ocs_admin_campaign_delete_form( $form, &$form_state, $campaign_id)
{
    if ( ! isset( $_GET['name'])) {
        $campaign = ocs_admin_campaign_load( $campaign_id);
        $form['#campaign_name'] = $campaign['campaign_name'];
    }
    else {
        $form['#campaign_name'] = $_GET['name'];
    }
    $form['#campaign_id'] = $campaign_id;

    $caption = '<p>'. 
            t('<strong>Warning:</strong> The Campaign "@name" will be deleted.',
                array( '@name' => $form['#campaign_name'])) .
        '</p>';

    return confirm_form( $form, t('Are you sure to delete the campaign ?'), 
			'campaign/list', $caption, t('Delete'));
}

function ocs_admin_campaign_delete_form_submit( $form, &$form_state)
{
    $campaign_id = $form['#campaign_id'];

	ocs_admin_campaign_delete( $campaign_id);

    $t_args = array( '%name' => $form['#campaign_name']);
    drupal_set_message( t('The campaign %name has been deleted.', $t_args));
    watchdog( 'ocs_admin', 'Deleted campaign %name.', $t_args, WATCHDOG_NOTICE);

	$form_state['redirect'] = 'campaign/list';
}

function ocs_admin_campaign_delete( $campaign_id)
{
    db_set_active( 'ocsdb');

    // delete the group and all subgroups
    $status = db_delete( 'ocs_campaign')
        ->condition( 'campaign_id', $campaign_id)
        ->execute();
    dpm( $status, 'db_delete result');

    db_set_active( 'default');
}


