  
(function ($) {
      
    $(document).ready(function(){
          
        //fix tabs
        $('.tabs.primary a').click(function(){
            return TRUE;
        });
  
        
        $('.our-latest-post').flexslider({
            animation: "slide",
            animationLoop: false,
            itemWidth: 460,
            itemMargin: 0,
            minItems: 1,
            maxItems: 2,
            // Primary Controls
            controlNav: false,               //Boolean: Create navigation for paging control of each clide? Note: Leave true for manualControls usage
            directionNav: true,             //Boolean: Create navigation for previous/next navigation? (true/false)
            prevText: "Previous",           //String: Set the text for the "previous" directionNav item
            nextText: "Next"
        });
        
        
        //recent-projects
        
  
        $('.recent-projects').flexslider({
            animation: "slide",
            animationLoop: false,
            itemWidth: 300,
            itemMargin: 0,
            minItems: 1,
            maxItems: 3,
            // Primary Controls
            controlNav: false,               //Boolean: Create navigation for paging control of each clide? Note: Leave true for manualControls usage
            directionNav: true,             //Boolean: Create navigation for previous/next navigation? (true/false)
            prevText: "Previous",           //String: Set the text for the "previous" directionNav item
            nextText: "Next"
        });
        
       
  
        //our-partners
        $('.our-partners').flexslider({
            animation: "slide",
            animationLoop: false,
            itemWidth: 160,
            itemMargin: 0,
            minItems: 1,
            maxItems: 6,
            // Primary Controls
            controlNav: false,               //Boolean: Create navigation for paging control of each clide? Note: Leave true for manualControls usage
            directionNav: true,             //Boolean: Create navigation for previous/next navigation? (true/false)
            prevText: "Previous",           //String: Set the text for the "previous" directionNav item
            nextText: "Next"
        });
    
    
        $('.blogsingleimage a').attr('title', $('#page-title').text()).attr('rel', 'lightbox');
    
    
        $('.blogimage .field-type-image .field-items,.blogsingleimage .field-type-image .field-items').addClass('slides');
        $('.blogimage .field-type-image .field-items .field-item,.blogsingleimage .field-type-image .field-items .field-item').wrap('<li></li>');
        $('.blogimage .field-type-image, .blogsingleimage .field-type-image').addClass('flexslider').flexslider({
            controlNav: false
        });
    
    
        /** portfolio */
    
  
 
      
        $('.view-portfolio .views-row').each(function(){
        
            $(this).addClass($(this).find('.term-class').html());
       
        });
        $('.bef-select-as-links .form-item .form-item a:last').addClass('last');
        $('#edit-field-portfolio-category-tid-all').html('<a id="filter-all" class="active" data-filter="*" href="/portfolio">Show All</a>');
        $('.bef-select-as-links .form-item .form-item').each(function(){
           
            $this = $(this);
           
            if(($this.children('a').attr('id') !== 'filter-all')){
                $(this).find('a').attr('data-filter', '.'+$(this).attr('id')).addClass('catlink');
            }
            
            if(!($this.children('a').hasClass('last'))){
                $this.children('a').append('<span class="aftersortingword"> /</span>');
            }
        });
      
        
    
        var $container = $('.view-portfolio .view-content');
        // initialize isotope
        $container.isotope({
            // options...
            });
      
 
        $('.bef-select-as-links').attr('id', 'remove');
        // filter items when filter link is clicked
        $('.bef-select-as-links a').click(function(){
            var selector = $(this).attr('data-filter');
            $('.bef-select-as-links a').removeClass('active');
            $(this).addClass('active');
            $container.isotope({
                filter: selector
            });
            return false;
        });


        // end portfolio
  
  
  
        $('.sidebar .block h2').after($('<div class="titleborder"></div>'));
  
  
  
  
        /*----------------------------------------------------*/
        /*	Responsive Menu
/*----------------------------------------------------*/

        // Create the dropdown bases
        $("<select />").appendTo(".menu-header");
			
        // Create default option "Go to..."
        $("<option />", {
            "selected": "selected",
            "value"   : "",
            "text"    : "Menu"
        }).appendTo(".menu-header select");
			
				
        // Populate dropdowns with the first menu items
        $(".menu-header .content li a").each(function() {
      
            var el = $(this);
      
            depth   = el.parents('ul').length - 1,
            indent  = '';
            if( depth ) {
                while( depth > 0 ) {
                    indent += ' - ';
                    depth--;
                }
            }
      
            $("<option />", {
                "value"   : el.attr("href"),
                "text"    : indent+ ' '+el.text()
            }).appendTo(".menu-header select");
        });
			
				
        //make responsive dropdown menu actually work			
        $(".menu-header select").change(function() {
            window.location = $(this).find("option:selected").val();
        });
  
    
    
    });
  
        
  
})(jQuery);