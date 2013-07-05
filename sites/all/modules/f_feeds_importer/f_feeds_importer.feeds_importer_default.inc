<?php
/**
 * @file
 * f_feeds_importer.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function f_feeds_importer_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_pcrf_rule_export_';
  $feeds_importer->config = array(
    'name' => 'import (pcrf_rule_export)',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
        'directory' => 'private://feeds',
        'allowed_schemes' => array(
          0 => 'public',
          1 => 'private',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => '|',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'display_name',
            'target' => 'field_display_name',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'export_disabled',
            'target' => 'field_export_disabled',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'result_ruleset_name',
            'target' => 'field_result_ruleset_name',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'view_name',
            'target' => 'field_view_name',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'pcrf_rule_export',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_pcrf_rule_export_'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_rating_rule_export_';
  $feeds_importer->config = array(
    'name' => 'import (rating_rule_export)',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
        'directory' => 'private://feeds',
        'allowed_schemes' => array(
          0 => 'public',
          1 => 'private',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => '|',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'children_export_type',
            'target' => 'field_children_export_type',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'children_node_type',
            'target' => 'field_children_node_type',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'display_name',
            'target' => 'field_display_name',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'export_disabled',
            'target' => 'field_export_disabled',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'result_ruleset_name',
            'target' => 'field_result_ruleset_name',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'source_display_name',
            'target' => 'field_source_display_name',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'source_view_name',
            'target' => 'field_source_view_name',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'view_name',
            'target' => 'field_view_name',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'rating_rule_export',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_rating_rule_export_'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_rating_rule_export_factor_conversion_';
  $feeds_importer->config = array(
    'name' => 'import (rating_rule_export_factor_conversion)',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
        'directory' => 'private://feeds',
        'allowed_schemes' => array(
          0 => 'public',
          1 => 'private',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => '|',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'conversion_php_code',
            'target' => 'field_conversion_php_code',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'rating_factor_name',
            'target' => 'field_rating_factor_name',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'rating_factor_op',
            'target' => 'field_rating_factor_op',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'rating_factor_size',
            'target' => 'field_rating_factor_size',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'rating_factor_tags',
            'target' => 'field_rating_factor_tags',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'rating_factor_type',
            'target' => 'field_rating_factor_type',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'drupal_field_name',
            'target' => 'field_value',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'rating_factor_conversion',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_rating_rule_export_factor_conversion_'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_rating_rule_export_product_';
  $feeds_importer->config = array(
    'name' => 'import (rating_rule_export_product)',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
        'directory' => 'private://feeds',
        'allowed_schemes' => array(
          0 => 'public',
          1 => 'private',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => '|',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'display_name',
            'target' => 'field_display_name',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'export_disabled',
            'target' => 'field_export_disabled',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'export_target',
            'target' => 'field_export_target',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'individual_ruleset',
            'target' => 'field_individual_ruleset',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'result_ruleset_name',
            'target' => 'field_result_ruleset_name',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'view_name',
            'target' => 'field_view_name',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'rating_rule_export_product',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_rating_rule_export_product_'] = $feeds_importer;

  return $export;
}
