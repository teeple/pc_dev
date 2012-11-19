(function($){
  Drupal.behaviors.product_catalog = {
    attach: function(context, settings) {
        console.log('util.js is loaded.');
        $('#nav li').hover(
          function() {
              $('ul',this).slideDown(100);
          },
          function() {
              $('ul',this).slideUp(100);
          }
        ); /* for dropdown sub-nav */
    }
  };

})(jQuery);
