(function($) {
	Drupal.behaviors.ProductCatalogSelectableBehavior = {
		attach : function(context, settings) {	
			$("#selectable").selectable();
			
			$("#selectable_add_button").bind('click',$.fn.selectableAddHandler);			
	    }
	};
	
	$.fn.selectableAddHandler = function(){
		var timetableNid = $("#timetable_nid").attr('value');		
		var addTitle = $("#selectable_add_title").attr('value');
		var selected = null;
		
		if(addTitle.length > 0){
			selected = $.fn.findSelectableSelected();			
			if(selected.length == 0){
				alert('Select Timeslot');
			}else{
				$.fn.masking("Processing...");
				$.ajax({
					url : '/product_catalog_selectable/timetablefactorsslot/add',
					type: "post",
			        data: {'timetable_nid': timetableNid, 'add_title': addTitle, 'selected': selected},
					success : function(data) {
						$.fn.unmasking();
						var output = $.parseJSON(data);
						$(location).attr('href',output[1].url);						
					}
				});
			}
		}else{
			alert('Name field is empty');
		}
	};
	
	$.fn.findSelectableSelected = function(){
		var selected = new Array();
		
		$("#selectable").find('.ui-selected').not('.selectable_exclude').each(
				function(){
					var nid = $(this).attr('nid');
					selected.push(nid);
				}
		);
		
		return selected;
		
	};
	
	$.fn.disableSelectable = function(){
		$("#selectable").selectable('disable');
	};
})(jQuery);
