(function ($) {
    // Disable overlay for creating the "tear" node.
    Drupal.behaviors.testModule = {
        attach: function (context, settings) {
            var $tear_link = $('a[href*="node/add/tear"]'),
            tear_link_href = $tear_link.attr('href');
            if( $tear_link.length > 0 ) {
                // we want to avoid opening the content adding for "tear" content type in the overlay
                // so we open it in the current window
                $tear_link.unbind();
                $tear_link.click(function(e){
                    window.open(tear_link_href,'_self',false);
                    e.stopPropagation();
                })
            }    
        };
    }
})(jQuery);

