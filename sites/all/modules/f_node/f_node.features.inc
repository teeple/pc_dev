<?php
/**
 * @file
 * f_node.features.inc
 */

/**
 * Implements hook_node_info().
 */
function f_node_node_info() {
  $items = array(
    'basicrate_domestic_incoming' => array(
      'name' => t('BasicRate_Domestic_Incoming'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('name'),
      'help' => '',
    ),
    'conditionwhereapn' => array(
      'name' => t('ConditionWhereAPN'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'mapbasicratedomesticincoming' => array(
      'name' => t('MapBasicRateDomesticIncoming'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
