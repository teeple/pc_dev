<?php
/**
 * @file
 * f_field_group.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function f_field_group_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_charging_cycle|node|prdnonusagerecurringbonusscheme|form';
  $field_group->group_name = 'group_charging_cycle';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'prdnonusagerecurringbonusscheme';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Charging Cycle',
    'weight' => '1',
    'children' => array(
      0 => 'field_rcrr_charging_day_monthly',
      1 => 'field_rcrr_charging_day_week',
      2 => 'field_bonus_cycle_type',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_charging_cycle|node|prdnonusagerecurringbonusscheme|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_commission|node|unittransferfactor|form';
  $field_group->group_name = 'group_commission';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'unittransferfactor';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Commission',
    'weight' => '9',
    'children' => array(
      0 => 'field_commission_collection',
      1 => 'field_commision_type',
      2 => 'field_commission_price',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_commission|node|unittransferfactor|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_commission|node|unittransfer|form';
  $field_group->group_name = 'group_commission';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'unittransfer';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Commission',
    'weight' => '5',
    'children' => array(
      0 => 'field_commission_price',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_commission|node|unittransfer|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_condition|node|basicrate_idd|default';
  $field_group->group_name = 'group_condition';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'basicrate_idd';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Condition',
    'weight' => '1',
    'children' => array(
      0 => 'field_ref_condition_idd',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_condition|node|basicrate_idd|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_condition|node|domestic_ratinggroup|form';
  $field_group->group_name = 'group_condition';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'domestic_ratinggroup';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Conditions',
    'weight' => '2',
    'children' => array(
      0 => 'field_service_type_of_provider',
      1 => 'field_ref_carrier_mobile',
      2 => 'field_is_samezone',
      3 => 'field_area_code_of_the_caller',
      4 => 'field_area_code_of_the_callee',
      5 => 'field_is_video_',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_condition|node|domestic_ratinggroup|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_condition|node|idd_ratinggroup|form';
  $field_group->group_name = 'group_condition';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'idd_ratinggroup';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Conditions',
    'weight' => '2',
    'children' => array(
      0 => 'field_prefix',
      1 => 'field_area_name',
      2 => 'field_service_type_of_provider',
      3 => 'field_ref_carrier_mobile',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_condition|node|idd_ratinggroup|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_connection|node|actionpricechargefactors|form';
  $field_group->group_name = 'group_connection';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'actionpricechargefactors';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Connection',
    'weight' => '18',
    'children' => array(
      0 => 'field_connection_fee',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_connection|node|actionpricechargefactors|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_connection|node|numberspecialrate|form';
  $field_group->group_name = 'group_connection';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'numberspecialrate';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Connection',
    'weight' => '5',
    'children' => array(
      0 => 'field_connection_fee',
      1 => 'field_grace_seconds',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_connection|node|numberspecialrate|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_connection|node|rate|form';
  $field_group->group_name = 'group_connection';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'rate';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Connection',
    'weight' => '12',
    'children' => array(
      0 => 'field_connection_fee',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_connection|node|rate|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contraints|node|simpleproductoffering|form';
  $field_group->group_name = 'group_contraints';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'simpleproductoffering';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Subscription Contraints',
    'weight' => '36',
    'children' => array(
      0 => 'field_contract_period',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_contraints|node|simpleproductoffering|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cug|node|simpleproductoffering|form';
  $field_group->group_name = 'group_cug';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'simpleproductoffering';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Closed User Group',
    'weight' => '34',
    'children' => array(
      0 => 'field_cug_member_counter',
      1 => 'field_cug_customer_type',
      2 => 'field_cug_group_type',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_cug|node|simpleproductoffering|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_default_usage_type|node|counter|form';
  $field_group->group_name = 'group_default_usage_type';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'counter';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Default Usage Type',
    'weight' => '11',
    'children' => array(
      0 => 'field_default_usage_type',
      1 => 'field_select_all_or_not',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_default_usage_type|node|counter|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_domestic|node|usage|form';
  $field_group->group_name = 'group_domestic';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'usage';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Domestic',
    'weight' => '2',
    'children' => array(
      0 => 'field_ref_numberingplan_domestic',
      1 => 'field_ref_basicrate_domestic',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_domestic|node|usage|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_expire_date|node|productchange|form';
  $field_group->group_name = 'group_expire_date';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'productchange';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Active Date',
    'weight' => '8',
    'children' => array(
      0 => 'field_expiredate_options',
      1 => 'field_expiredate_ndays',
      2 => 'field_expiredate_fixeddate',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Active Date',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_expire_date|node|productchange|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_expire_date|node|treenodecounter|form';
  $field_group->group_name = 'group_expire_date';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'treenodecounter';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Expire Date',
    'weight' => '10',
    'children' => array(
      0 => 'field_startdate_option1',
      1 => 'field_enddate_option1',
      2 => 'field_enddate_option2',
      3 => 'field_enddate_option3',
      4 => 'field_enddate_option4',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_expire_date|node|treenodecounter|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_expire_date|node|unittransferfactor|form';
  $field_group->group_name = 'group_expire_date';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'unittransferfactor';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Expire Date',
    'weight' => '6',
    'children' => array(
      0 => 'field_enddate_option1',
      1 => 'field_enddate_option2',
      2 => 'field_enddate_option3',
      3 => 'field_enddate_option4',
      4 => 'field_startdate_option1',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_expire_date|node|unittransferfactor|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_grace_date|node|productchange|form';
  $field_group->group_name = 'group_grace_date';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'productchange';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Grace Date',
    'weight' => '9',
    'children' => array(
      0 => 'field_gracedate_options',
      1 => 'field_gracedate_ndays',
      2 => 'field_gracedate_fixeddate',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Grace Date',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_grace_date|node|productchange|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_international|node|usage|form';
  $field_group->group_name = 'group_international';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'usage';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'International',
    'weight' => '3',
    'children' => array(
      0 => 'field_ref_numberingplan_idd',
      1 => 'field_ref_basicrate_idd',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_international|node|usage|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_limit_per_period|node|unittransferfactor|form';
  $field_group->group_name = 'group_limit_per_period';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'unittransferfactor';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Limitation Per Period',
    'weight' => '8',
    'children' => array(
      0 => 'field_maximum_counter_',
      1 => 'field_total_valid_type',
      2 => 'field_accumulated_counter_for_ut',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_limit_per_period|node|unittransferfactor|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_limit_per_transaction|node|unittransferfactor|form';
  $field_group->group_name = 'group_limit_per_transaction';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'unittransferfactor';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Limitation Per Transaction',
    'weight' => '7',
    'children' => array(
      0 => 'field_minimum_amount',
      1 => 'field_maximum_amount',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_limit_per_transaction|node|unittransferfactor|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_max_amount_per_day|node|prdnonusagerechargeblock|form';
  $field_group->group_name = 'group_max_amount_per_day';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'prdnonusagerechargeblock';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Max Recharge Amount Per Day',
    'weight' => '4',
    'children' => array(
      0 => 'field_max_amount_per_day',
      1 => 'field_counter_for_max_amount',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_max_amount_per_day|node|prdnonusagerechargeblock|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_max_count_per_day|node|prdnonusagerechargeblock|form';
  $field_group->group_name = 'group_max_count_per_day';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'prdnonusagerechargeblock';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Max Recharge Count Per Day',
    'weight' => '3',
    'children' => array(
      0 => 'field_max_counter_per_day',
      1 => 'field_counter_for_max_count',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_max_count_per_day|node|prdnonusagerechargeblock|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_numberingplan|node|tariffplan|form';
  $field_group->group_name = 'group_numberingplan';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'tariffplan';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Numbering Plan',
    'weight' => '8',
    'children' => array(
      0 => 'field_ref_numberingplan_domestic',
      1 => 'field_ref_numberingplan_idd',
      2 => 'field_ref_roaming_plan',
      3 => 'field_numberingplan_d_incoming',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_numberingplan|node|tariffplan|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_per_transaction|node|unittransfer|form';
  $field_group->group_name = 'group_per_transaction';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'unittransfer';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Limitation Per Transaction',
    'weight' => '2',
    'children' => array(
      0 => 'field_minimum_amount',
      1 => 'field_maximum_amount',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Limitation Per Transaction',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_per_transaction|node|unittransfer|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_period_set|node|actionpriceallowanceonetime|form';
  $field_group->group_name = 'group_period_set';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'actionpriceallowanceonetime';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Set Active/Grace Period',
    'weight' => '6',
    'children' => array(
      0 => 'field_active_period',
      1 => 'field_grace_period',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_period_set|node|actionpriceallowanceonetime|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_period_set|node|actionpricechargeonetime|form';
  $field_group->group_name = 'group_period_set';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'actionpricechargeonetime';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Set Active/Grace Period',
    'weight' => '6',
    'children' => array(
      0 => 'field_active_period',
      1 => 'field_grace_period',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_period_set|node|actionpricechargeonetime|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_period_set|node|actionpricechargerecurringdefaul|form';
  $field_group->group_name = 'group_period_set';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'actionpricechargerecurringdefaul';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Set Active/Grace Period',
    'weight' => '17',
    'children' => array(
      0 => 'field_active_period',
      1 => 'field_grace_period',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_period_set|node|actionpricechargerecurringdefaul|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_period_set|node|actionpricechargerecurring|form';
  $field_group->group_name = 'group_period_set';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'actionpricechargerecurring';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Set Active/Grace Period',
    'weight' => '7',
    'children' => array(
      0 => 'field_active_period',
      1 => 'field_grace_period',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_period_set|node|actionpricechargerecurring|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_price|node|basicrate|form';
  $field_group->group_name = 'group_price';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'basicrate';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Price',
    'weight' => '3',
    'children' => array(
      0 => 'field_price_amount',
      1 => 'field_uom_amount',
      2 => 'field_uom_units',
      3 => 'field_price_amount_float',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_price|node|basicrate|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pricing|node|actionpricechargerecurring|form';
  $field_group->group_name = 'group_pricing';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'actionpricechargerecurring';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Pricing',
    'weight' => '2',
    'children' => array(
      0 => 'field_pricing_cycle_type',
      1 => 'field_price_amount_float',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_pricing|node|actionpricechargerecurring|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_attribute|node|treenodeotheronetimecharge|form';
  $field_group->group_name = 'group_product_attribute';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'treenodeotheronetimecharge';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Product Attribute',
    'weight' => '6',
    'children' => array(
      0 => 'field_attribute_key_value',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_product_attribute|node|treenodeotheronetimecharge|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_expire_date|node|simpleproductoffering|form';
  $field_group->group_name = 'group_product_expire_date';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'simpleproductoffering';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Product Expire',
    'weight' => '37',
    'children' => array(
      0 => 'field_next_join_product',
      1 => 'field_expire_date_type',
      2 => 'field_expire_date',
      3 => 'field_resubscription_flag',
      4 => 'field_expire_date_for_hour',
      5 => 'field_next_join_confirm',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_product_expire_date|node|simpleproductoffering|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_promotional|node|usage|form';
  $field_group->group_name = 'group_promotional';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'usage';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Promotional',
    'weight' => '5',
    'children' => array(
      0 => 'field_ref_rule',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_promotional|node|usage|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_range|node|numberspecialrate|form';
  $field_group->group_name = 'group_range';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'numberspecialrate';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Range',
    'weight' => '2',
    'children' => array(
      0 => 'field_range_units',
      1 => 'field_uom_units',
      2 => 'field_charge_collection',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_range|node|numberspecialrate|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_rate|node|basicrate_idd|default';
  $field_group->group_name = 'group_rate';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'basicrate_idd';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Rate',
    'weight' => '10',
    'children' => array(
      0 => 'field_price_amount',
      1 => 'field_uom_amount',
      2 => 'field_uom_units',
      3 => 'field_price_units',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_rate|node|basicrate_idd|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_result|node|domestic_ratinggroup|form';
  $field_group->group_name = 'group_result';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'domestic_ratinggroup';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Results',
    'weight' => '12',
    'children' => array(
      0 => 'field_ref_type_of_call',
      1 => 'field_rating_group',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_result|node|domestic_ratinggroup|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_result|node|idd_ratinggroup|form';
  $field_group->group_name = 'group_result';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'idd_ratinggroup';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Results',
    'weight' => '7',
    'children' => array(
      0 => 'field_ref_type_of_call',
      1 => 'field_rating_group',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_result|node|idd_ratinggroup|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_start_date|node|actionsetcounteronbonus|form';
  $field_group->group_name = 'group_start_date';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'actionsetcounteronbonus';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Expire date setting',
    'weight' => '6',
    'children' => array(
      0 => 'field_startdate_option1',
      1 => 'field_enddate_option1',
      2 => 'field_enddate_option2',
      3 => 'field_enddate_option3',
      4 => 'field_enddate_option4',
      5 => 'field_valid_date_hour',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Expire date setting',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_start_date|node|actionsetcounteronbonus|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_timetable|node|tariffplan|form';
  $field_group->group_name = 'group_timetable';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'tariffplan';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'TimeTable',
    'weight' => '9',
    'children' => array(
      0 => 'field_ref_timetable_domestic',
      1 => 'field_ref_timetable_domestic_inc',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_timetable|node|tariffplan|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_total_transfered_amount|node|unittransfer|form';
  $field_group->group_name = 'group_total_transfered_amount';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'unittransfer';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Limitation per Month',
    'weight' => '4',
    'children' => array(
      0 => 'field_ref_counter_for_total_ut',
      1 => 'field_limit_amount',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Limitation per Month',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_total_transfered_amount|node|unittransfer|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_total|node|unittransfer|form';
  $field_group->group_name = 'group_total';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'unittransfer';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Limitation Per Period',
    'weight' => '3',
    'children' => array(
      0 => 'field_maximum_counter_',
      1 => 'field_total_valid_type',
      2 => 'field_accumulated_counter_for_ut',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Limitation Per Period',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_total|node|unittransfer|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tracking_counters|node|treenodecounter|form';
  $field_group->group_name = 'group_tracking_counters';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'treenodecounter';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tracking Counters',
    'weight' => '9',
    'children' => array(
      0 => 'field_counter',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_tracking_counters|node|treenodecounter|form'] = $field_group;

  return $export;
}
