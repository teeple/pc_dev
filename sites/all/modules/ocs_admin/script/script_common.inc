<?php


function get_taxo_term_name( $term)
{
    $name = (isset($term->field_rel_type['und'])) ? $term->field_rel_type['und'][0]['value'].':' : '';
    $name .= $term->name;
    return $name;
}

function rm_product( $prd_id) 
{
    // find the product
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'simpleproductoffering')
        ->fieldCondition('field_product_id', 'value', $prd_id)
        ->execute();

    if ( empty( $result)) {
        printf( "Product not found: %s\n", $prd_id);
        return;
    }

    $idx = 0;
    foreach( array_keys( $result['node']) as $nid) {
        $p = node_load( $nid);
        printf( "Product Name : %s\n", $p->title);

        // dump all of its child node
        $view = views_get_view('list_product_child_node');
        $view->set_display('panel_pane_3');
        $view->set_arguments(array('0' => $p->nid));
        $view->execute();

        foreach($view->result as $record){
            $childNode = node_load($record->nid);

            switch( $childNode->type) {
                case 'tariffplan' :
                    break;
                default:
                    delChildAction( $childNode);
                    break;
            }

            node_delete( $record->nid);
            printf( "  %s  %s\n", $childNode->type, $childNode->title);
        }

        node_delete( $p->nid);
    }

}

function delChildAction( $child)
{
	$actionSetView = views_get_view('query_actionset_children');
	$actionSetView->set_display('panel_pane_1');
	$actionSetView->set_arguments(array('0' => $child->nid));
	$actionSetView->execute();

	foreach($actionSetView->result as $actionSetRecord){
		$targetActionSetNode = node_load($actionSetRecord->nid);

		$type = $child->type . ':' . $targetActionSetNode->type;
		printf( "  %s  %s\n", $type, $childNode->title);
		
		node_delete( $actionSetRecord->nid);
	}
}
