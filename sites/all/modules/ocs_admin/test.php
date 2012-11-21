<?php
$format = '%1 %2 %3 %111 format';
$reg = preg_match_all( '/%\d+/', $format, $matches);
print "MATCH:".$reg;
print print_r( $matches, TRUE);
