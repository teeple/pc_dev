<?php

$file = '/Users/bhtak/Sites/pc_dev/sites/all/modules/ocs_admin/script/d2';
$fp = fopen( $file, "r");
$content = '';
while( ! feof( $fp)) {
	$content .= fread( $fp, 8192);
}
fclose( $fp);

//print count($content);

$old_fields = unserialize( $content);

$fields = field_info_instances();
$nl = '
';

foreach( $old_fields as $type => $name) {
	if ( $type == 'comment') continue;

	foreach( $name as $k => $v) {
		if ( ! isset( $fields[$type][$k])) {
			print 'A> New ' . $type . ' : ' . $k . $nl;
			continue;
		}

		foreach( $v as $k1 => $v1) {
			/*
			print $type . ':' . $k . ':' . $k1 . $nl;
			print_r( $v1);
			*/

			if ( ! isset( $fields[$type][$k][$k1])) {
				print 'A> New field : ' . $type . ' : ' . $k . ':' . $k1 . $nl;
			}
			else {
				unset( $fields[$type][$k][$k1]);
			}
		}

		foreach( $fields[$type][$k] as $k1 => $v1) {
			print 'B> New field : ' . $type . ' : ' . $k . ':' . $k1 . $nl;
		}

		unset( $fields[$type][$k]);
	}

	foreach( $fields[$type] as $k => $v) {
		print 'B> New ' . $type . ' : ' . $k . $nl;
	}
}
