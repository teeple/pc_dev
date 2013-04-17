<?php
/**
 * @file
 * data_content_type_move.features.inc
 */

/**
 * Implements hook_node_info().
 */
function data_content_type_move_node_info() {
  $items = array(
    'conditionwhererattype' => array(
      'name' => t('ConditionWhereRatType'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'conditionwheresgsn' => array(
      'name' => t('ConditionWhereSGSN'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('name'),
      'help' => '',
    ),
    'packetsgsn' => array(
      'name' => t('PacketSGSN'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
