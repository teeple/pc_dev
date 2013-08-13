<?php
$account = user_load(1);
$permissions = user_role_permissions($account->roles);

$admin_permissions = $permissions[3];
$grant_permissions = array();
$revoke_permissions = array();
foreach($admin_permissions as $key => $value) {
	   /*
	   if( strpos($key, 'terms in') > 0) continue;
	   if( (strpos($key, 'create') > 0) 
			   || (strpos($key, 'delete') >0)
			   || (strpos($key, 'edit') >0) ) {
	      $grant_permissions[$key] = $value;
	   }
	   */
	   if( strpos($key, 'terms in') > 0) $reoke_permissions[$key] = $value;
}
// user_role_grant_permissions(6,$grant_permissions);
user_role_revoke_permissions(6, array_keys($revoke_permissions));

$account = user_load(1391);
$permissions = user_role_permissions($account->roles);

?>
