<?php

$tmp_field = '_field_data';
$term_class = '';
if (isset($row->{$tmp_field}['nid']['entity']->field_portfolio_category[LANGUAGE_NONE])) {
  $term = $row->{$tmp_field}['nid']['entity']->field_portfolio_category[LANGUAGE_NONE];

  if (!empty($term)) {
    foreach ($term as $t) {
      if ($term_class == '') {
        $term_class .= 'edit-field-portfolio-category-tid-' . $t['tid'];
      } else {
        $term_class .= ' edit-field-portfolio-category-tid-' . $t['tid'];
      }
    }
  }
}
?>
<?php print '<div class="term-class">' . $term_class . '</div>'; ?>