<?php
//module_load( 'inc', 'product_catalog_form', 'product_catalog_form');

$node = node_load( 98388);
$voca = _get_vocabulary_name( 'simpleproductoffering', $node);
print_r( $voca);

$vid = taxonomy_vocabulary_machine_name_load( $voca);
$query = new EntityFieldQuery;
$result = $query->entityCondition('entity_type', 'taxonomy_term')
	->propertyCondition('vid', $vid->vid)
	->execute();

$terms = taxonomy_term_load_multiple( array_keys( $result['taxonomy_term']));
print_r( $terms);
