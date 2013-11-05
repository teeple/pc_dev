<?php

$nids = ocs_get_nids_by_cond( 'simpleproductoffering', array(
		array('field_billing_type', 'tid', '679'),
		array('field_product_type', 'tid', '479'),
		array('field_service_operator', 'tid', '763')
			));
printf("Found : %d\n", count( $nids));
foreach( $nids as $nid)
{
	$prd = node_load( $nid);
	printf("%d %s\n", $nid, $prd->title);

	$counter_nids = ocs_get_nids_by_cond( 'treenodecounter', array(
//		array( 'field_ref_counter', 'nid', 117269),		// FreeSMS - 
//		array( 'field_ref_counter', 'nid', 117268),		// FreeVideoCall
//		array( 'field_ref_counter', 'nid', 117267),		// FreeCallTime
		array( 'field_ref_counter', 'nid', 117264),		// FreeRemains
		array( 'field_ref_tree_tid', 'value', 6539),		
		array( 'field_ref_product', 'nid', $prd->nid),		
		));
	if ( count( $counter_nids) == 1) {
		$cond_nids = ocs_get_nids_by_cond( 'conditioncommonand', array(
				array( 'field_parent_node', 'nid', $counter_nids[0])));
		if ( count( $cond_nids) == 0) {
			// add condition set
			$cond = ocs_admin_get_new_node( 'conditioncommonand');
			$cond->field_parent_node['und'][0]['nid'] = $counter_nids[0];
			node_save( $cond);

			// add condition usage_type
			$c1 = ocs_admin_get_new_node( 'conditionwhatusagetypefactors');
			$c1->field_parent_node['und'][0]['nid'] = $cond->nid;
			$c1->field_ref_usage_type['und'][0]['tid'] = 2035;
			$c1->field_ref_usage_type['und'][1]['tid'] = 2034;
			$c1->field_ref_usage_type['und'][2]['tid'] = 2036;
			node_save( $c1);

			$cond = ocs_admin_get_new_node( 'conditioncommonand');
			$cond->field_parent_node['und'][0]['nid'] = $counter_nids[0];
			node_save( $cond);

			// add condition usage_domain
			$c1 = ocs_admin_get_new_node( 'conditionwhatnonusagetypefactors');
			$c1->field_parent_node['und'][0]['nid'] = $cond->nid;
			$c1->field_ref_nonusage_type['und'][0]['tid'] = 2019;
			$c1->field_ref_nonusage_type['und'][1]['tid'] = 8048;
			node_save( $c1);

			$cond = ocs_admin_get_new_node( 'conditioncommonand');
			$cond->field_parent_node['und'][0]['nid'] = $counter_nids[0];
			node_save( $cond);

			// add condition usage_domain
			$c1 = ocs_admin_get_new_node( 'conditionwhatusagedomain');
			$c1->field_parent_node['und'][0]['nid'] = $cond->nid;
			$c1->field_usage_domain['und'][0]['tid'] = 8011;
			node_save( $c1);

			// add condition incoming_call
			$c2 = ocs_admin_get_new_node( 'conditionwhatincomingcall');
			$c2->field_parent_node['und'][0]['nid'] = $cond->nid;
			$c2->field_is_incoming_call['und'][0]['value'] = '0';
			node_save( $c2);

			// add condition usage_type
			$c3 = ocs_admin_get_new_node( 'conditionwhatusagetypefactors');
			$c3->field_parent_node['und'][0]['nid'] = $cond->nid;
			$c3->field_ref_usage_type['und'][0]['tid'] = 2032;
			$c3->field_ref_usage_type['und'][2]['tid'] = 2033;
			node_save( $c3);

			// add condition conditionwhatisvideo
			/*
			$c3 = ocs_admin_get_new_node( 'conditionwhatisvideo');
			$c3->field_parent_node['und'][0]['nid'] = $cond->nid;
			$c3->field_is_video['und'][0]['value'] = '1';
			node_save( $c3);
			*/

			printf("  Condition added\n");
		}
		else {
			printf("  Condition exist\n");
		}
	}
	else {
		printf("  Invalid counter : %d\n", count( $counter_nids));
	}
}
