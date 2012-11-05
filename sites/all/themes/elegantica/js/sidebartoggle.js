jQuery().ready(function(){
	
	var sidebar_toggle_trigger = jQuery('#sidebar_toggle_trigger');
	var sidebar_second = jQuery('#sidebar-second');
	var content = jQuery('#content');
	
	/*
	sidebar_toggle_trigger.height(sidebar_second.find('.content').height() -5);
		
	sidebar_second.bind('resize',function(e){
		alert('resize');
		sidebar_toggle_trigger.height(sidebar_second.find('.content').height() -5);
	});
	*/
	
	sidebar_toggle_trigger.click(function() {			
		if(sidebar_toggle_trigger.attr('collapsed') == undefined){
			sidebar_toggle_trigger.attr('collapsed',true);
			sidebar_toggle_trigger.text('>');
			
			sidebar_second.animate({
			    width: 'toggle'
			  }, 300, function() {
			    // Animation complete.
			  });
			content.animate({
			    width: '100%'
			  }, 300, function() {
			    // Animation complete.
			  });
		}else{			
			sidebar_toggle_trigger.removeAttr('collapsed');
			sidebar_toggle_trigger.text('<');
			
			sidebar_second.animate({
			    width: 'toggle'
			  }, 300, function() {
			    // Animation complete.
			  });
			content.animate({
			    width: '70%'
			  }, 300, function() {
			    // Animation complete.
			  });
		}					
		
	});

});