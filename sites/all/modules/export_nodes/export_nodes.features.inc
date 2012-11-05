<?php
/**
 * @file
 * export_nodes.features.inc
 */

/**
 * Implements hook_node_info().
 */
function export_nodes_node_info() {
  $items = array(
    'ocs_account_state' => array(
      'name' => t('OCS Account State'),
      'base' => 'node_content',
      'description' => t('OCS Accounts State'),
      'has_title' => '1',
      'title_label' => t('State Name'),
      'help' => '',
    ),
    'ocs_actions' => array(
      'name' => t('OCS Actions'),
      'base' => 'node_content',
      'description' => t('Actions available in each system'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'ocs_campaign_action' => array(
      'name' => t('OCS Campaign Action'),
      'base' => 'node_content',
      'description' => t('Actions for Campaign'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'ocs_event_subscription' => array(
      'name' => t('OCS Event Subscription'),
      'base' => 'node_content',
      'description' => t('Event subscription status of each system'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'ocs_events' => array(
      'name' => t('OCS Events'),
      'base' => 'node_content',
      'description' => t('OCS System Event Types'),
      'has_title' => '1',
      'title_label' => t('Event Name'),
      'help' => '',
    ),
    'ocs_messages' => array(
      'name' => t('OCS Messages'),
      'base' => 'node_content',
      'description' => t('Notification Messages'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'ocs_param' => array(
      'name' => t('OCS Param'),
      'base' => 'node_content',
      'description' => t('Parameters that OCS provides for Events and Actions'),
      'has_title' => '1',
      'title_label' => t('name'),
      'help' => '',
    ),
    'ocs_state_machine' => array(
      'name' => t('OCS State Machine'),
      'base' => 'node_content',
      'description' => t('OCS State Machine'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'ocs_svc_perm' => array(
      'name' => t('OCS Svc Perm'),
      'base' => 'node_content',
      'description' => t('OCS Service Permission'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
