<?php


function println( $str = '')
{
	print $str . "\n";
}

function fwriteln( $fp, $str)
{
	$str .= "\n";
	if ( fwrite( $fp, $str) === FALSE) {
		println( 'fwrite failed');
	}
}
