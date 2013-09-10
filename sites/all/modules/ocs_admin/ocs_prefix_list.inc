<?php
function ocs_prefix_list()
{
	$prefix_list = _ocs_prefix_list_all();

	$rows = array();
	foreach( $prefix_list as $k => $v) {
		$rows[] = array( 
				array( 'data' => $k), 
				array( 'data' => $v[0]), 
				array( 'data' => $v[1]), 
				array( 'data' => $v[2]));
	}

	/*
	$header = array( 'Prefix' => array( 'data' => 'Prefix', 'field' => '0'), 
					'Opeartor' => array( 'data' => 'Operator', 'field' => '1'), 
					'Name' => array( 'data' => 'Name', 'field' => '2'), 
					'Comment');
					*/

	$header = array( 'Prefix', 'Opeartor', 'Name', 'Comment');

	return theme( 'table', array( 'rows' => $rows, 'header' => $header));

}

function _ocs_prefix_list_all()
{
	$prefix_list = array();

	// get list of countries
	$country = array();
	$nids = ocs_get_nids_by_cond( 'roaming_country', array());
	foreach( $nids as $nid) {
		$prd = node_load( $nid);

		foreach( $prd->field_prefix_multiple['und'] as $v) {
			if ( strlen( $v['value']) == 0) {
				// invalid prefix
			}
			else {
				$country[$v['value']] = $prd->title;
			}
		}
	}

	// get list of domestic prefix
	$nids = ocs_get_nids_by_cond( 'carrier_mobile', array());

	foreach( $nids as $nid) {
		$prd = node_load( $nid);

		$prefix = array();
		foreach( $prd->field_prefix_multiple['und'] as $v) {
			if ( $prd->field_ref_prefix_type['und'][0]['tid'] == 768) {	// Domestic
				$p = $v['value'];
				if ( isset( $prefix_list[$p])) {
						$prefix_list[$p][2] .= t( 'Duplicated wth @t <br>', 
								array( '@t' => $prd->title));
				}
				else {
					$prefix_list[$p] = array( $prd->title, '', '');
				}
			}
		}
	}

	// get list of IDD prefix
	$nids = ocs_get_nids_by_cond( 'idd_ratinggroup', array());

	foreach( $nids as $nid) {
		$prd = node_load( $nid);

		$carrier = node_load( $prd->field_ref_carrier_mobile['und'][0]['nid']);
		foreach( $carrier->field_prefix_multiple['und'] as $pfx) {
			$prefix = array();
			foreach( $prd->field_prefix['und'] as $v) {
				$p = $pfx['value'] . $v['value'];
				if ( isset( $prefix_list[$p])) {
					$prefix_list[$p][2] .= t( 'Duplicated wth @t <br>', 
						array( '@t' => $prd->field_area_name['und'][0]['value']));
				}
				else {
					$prefix_list[$p] = array( $prd->field_area_name['und'][0]['value'], 
							isset( $country[$v['value']]) ? $country[$v['value']] : 'UNKNOWN', '');
				}
			}
		}
	}

	// get list of voice special number
	$nids = ocs_get_nids_by_cond( 'numberspecialfactors', array());

	foreach( $nids as $nid) {
		$prd = node_load( $nid);

		$prefix = array();
		foreach( $prd->field_prefix['und'] as $v) {
			$ns = isset( $prd->field_ref_numberspecial['und'][0]['nid']) ? node_load( $prd->field_ref_numberspecial['und'][0]['nid']) : NULL;
			if ( ! empty( $ns)) {
				$p = $v['value'];
				//printf("%s %s %s\n", $p, $ns->title, $prd->title);

				if ( isset( $prefix_list[$p])) { // Duplicated
					$prefix_list[$p][2] .= t( 'Duplicated wth @t @n <br>', 
							array( '@t' => $ns->title, '@n' => $prd->title));
				}
				else {
					$prefix_list[$p] = array( $ns->title, $prd->title, '');
				}
			}
			else {
		//		dsm("invalid number special factors nid=%d\n", $nid);
			}
		}
	}

	ksort( $prefix_list);
	return $prefix_list;
}
