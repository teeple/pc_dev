<?php
$node = new stdClass();
$node->title = 'idd_ratinggroup';
$node->type = 'idd_ratinggroup';
$node->language = 'und';
$node->uid = 1;
$node->field_ref_numberingplan_idd['und'][0]['nid'] = 115749;
$node->field_rating_group['und'][0]['value'] = 'cc';

$prefixs = explode('|', '596|594|689|241|220|995|233|350|30|299|1473|590|1671|502|224|592|509|504|354|98|964|1876|962|254|686|965|996|856|961|266|231|218|423|370|352|389|265|223|356|692|222|230|262|52|691|1808|373|377|382|1664|212|258|95|264|977|599|1869|687|505|227|234|683|850|1670|968|92|680|970|507|675|595|51|1787|1939|250|290|1758|508|1784|685|378|966|221|381|421|386|677|252|94|249|211|597|268|963|992|255|228|690|676|1868|216|993|1649|688|1340|256|971|598|998|678|58|808|967|260|263|960|243|239|237|225|261|248|245|976');

$prefixTemp = array();
foreach($prefixs as $prefix) {
	$prefixTemp[] = array('value' => $prefix);
}
print_r($prefixTemp);
$node->field_prefix['und'] = $prefixTemp;

node_save($node);

$numberingplan_idd = node_load(115749);
$numberingplan_idd->field_ref_idd_ratinggroup['und'][] = array('nid' => $node->nid);
node_save($numberingplan_idd);
?>
