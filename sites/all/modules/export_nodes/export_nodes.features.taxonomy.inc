<?php
/**
 * @file
 * export_nodes.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function export_nodes_taxonomy_default_vocabularies() {
  return array(
    'ocs_client_id' => array(
      'name' => 'OCS Client ID',
      'machine_name' => 'ocs_client_id',
      'description' => 'System Client ID',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
