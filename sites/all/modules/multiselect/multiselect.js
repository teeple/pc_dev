
/**
 * The JavaScript behavior that goes with the Multiselect form element.
 */
(function ($) {
  Drupal.behaviors.multiselect = {
    attach: function(context) {
    	
      // Remove the items that haven't been selected from the select box.
	  $('select.multiselect_unsel:not(.multiselect-processed)', context).addClass('multiselect-processed').each(function() {
      		unselclass = '.' + this.id + '_unsel';
        	selclass = '.' + this.id + '_sel';
        	$(unselclass).removeContentsFrom($(selclass));
      });
  
      // Note: Doesn't matter what sort of submit button it is really (preview or submit)
      // Selects all the items in the selected box (so they are actually selected) when submitted
	  $('input.form-submit:not(.multiselect-processed)', context).addClass('multiselect-processed').click(function() {
		  $('select.multiselect_sel').selectAll();
	  });
      
      $('#multiselect_custom_button').click($.fn.eventSetSelectAll);
      
      $('#multiselect_custom_button_rollover').click($.fn.eventSetSelectAllRollover);
      
      $('#multiselect_custom_button_cardtype').click($.fn.eventSetSelectAllCardType);
      
      //$('#multiselect_custom_button_trackingcounter').click($.fn.eventSetSelectAllTrackingCounter);
            
      // Moves selection if it's double clicked to selected box
      $('select.multiselect_unsel:not(.multiselect-unsel-processed)', context).addClass('multiselect-unsel-processed').dblclick(function() {
        unselclass = '.' + this.id + '_unsel';
        selclass = '.' + this.id + '_sel';
        $(unselclass).moveSelectionTo($(selclass));
      });
  
      // Moves selection if it's double clicked to unselected box
      $('select.multiselect_sel:not(.multiselect-sel-processed)', context).addClass('multiselect-sel-processed').dblclick(function() {
        unselclass = '.' + this.id + '_unsel';
        selclass = '.' + this.id + '_sel';
        $(selclass).moveSelectionTo($(unselclass));
      });
  
      // Moves selection if add is clicked to selected box
      $('li.multiselect_add:not(.multiselect-add-processed)', context).addClass('multiselect-add-processed').click(function() {
        unselclass = '.' + this.id + '_unsel';
        selclass = '.' + this.id + '_sel';
        $(unselclass).moveSelectionTo($(selclass));
      });
  
      // Moves selection if remove is clicked to selected box
      $('li.multiselect_remove:not(.multiselect-remove-processed)', context).addClass('multiselect-remove-processed').click(function() {
        unselclass = '.' + this.id + '_unsel';
        selclass = '.' + this.id + '_sel';
        $(selclass).moveSelectionTo($(unselclass));
      });
    }
  };
})(jQuery);

jQuery.fn.eventSetSelectAll = function() {
	
	jQuery(".product_catalog_tree").mask("Selecting...");
	
	var multiselect_sel = jQuery('select.multiselect_sel');
	multiselect_sel.selectAll();
	
	var selectCounters = new Array();
	multiselect_sel.each(function(index, element) {
		for (var x=0;x<element.options.length;x++) {
			selectCounters[x] = element.options[x].value;
		};
	});
	
	var rootId = jQuery('.product_catalog_tree > ul:first > li:first').attr('id');
	var counterListUrl = '/product_catalog_ajax/counter_list';
	
	jQuery.ajax({
		url : counterListUrl,
		type: "post",
		data: {'product_nid': rootId, 'counter_nids':selectCounters},
		success : function(data) {
			jQuery(".product_catalog_tree").unmask();
		},
	});
}

jQuery.fn.eventSetSelectAllRollover = function() {
	
	jQuery(".product_catalog_tree").mask("Selecting...");
	
	var multiselect_sel = jQuery('select.multiselect_sel');
	multiselect_sel.selectAll();
	
	var selectCounters = new Array();
	multiselect_sel.each(function(index, element) {
		for (var x=0;x<element.options.length;x++) {
			selectCounters[x] = element.options[x].value;
		};
	});
	
	var rootId = jQuery('.product_catalog_tree > ul:first > li:first').attr('id');
	var rolloverSetUrl = '/product_catalog_ajax/set_rollover';
	
	var rolloverNid = jQuery('#rollover_nid').attr('value');
	var rolloverWeight = jQuery('#rollover_weight').attr('value');
	var rolloverRefProduct = jQuery('#rollover_ref_product').attr('value');
	var rolloverRefTreeNid = jQuery('#rollover_ref_tree_nid').attr('value');
	var rolloverRefTreeTid = jQuery('#rollover_ref_tree_tid').attr('value');
	
	var rolloverFlag = jQuery('#edit-field-used-for-rollover-und input[checked=checked]').attr('value');
	var happens = jQuery('#edit-field-happens option[selected=selected]').attr('value');
	var addOrReplace = jQuery('#edit-field-rollover-add-or-replace-und input[checked=checked]').attr('value');
		
	jQuery.ajax({
		url : rolloverSetUrl,
		type: "post",
		data: {'product_nid': rootId, 'rollover_nid': rolloverNid, 'rollover_weight': rolloverWeight 
			,'rollover_ref_product': rolloverRefProduct, 'rollover_ref_tree_nid':rolloverRefTreeNid, 'rollover_ref_tree_tid': rolloverRefTreeTid
			,'counter_nids':selectCounters, 'rollover_flag': rolloverFlag, 'happens': happens, 'add_or_replace': addOrReplace},
		success : function(data) {
			jQuery(".product_catalog_tree").unmask();
		},
	});
}

jQuery.fn.eventSetSelectAllCardType = function() {
	
	jQuery(".product_catalog_tree").mask("Selecting...");
	
	var multiselect_sel = jQuery('select.multiselect_sel');
	multiselect_sel.selectAll();
	
	var selectCards = new Array();
	multiselect_sel.each(function(index, element) {
		for (var x=0;x<element.options.length;x++) {
			selectCards[x] = element.options[x].value;
		};
	});
	
	var parentNid = jQuery('#cardtype_parent_nid').attr('value');
	
	var rootId = jQuery('.product_catalog_tree > ul:first > li:first').attr('id');
	var cardtypeSetUrl = '/product_catalog_ajax/set_cardtype';
	
	jQuery.ajax({
		url : cardtypeSetUrl,
		type: "post",
		data: {'product_nid': rootId, 'parent_nid': parentNid, 'cardtype_nids': selectCards},
		success : function(data) {
			jQuery(".product_catalog_tree").unmask();
		},
	});
}

/*
jQuery.fn.eventSetSelectAllTrackingCounter = function() {
	
	jQuery(".product_catalog_tree").mask("Selecting...");
	
	var multiselect_sel = jQuery('select.multiselect_sel');
	multiselect_sel.selectAll();
	
	var selectCounters = new Array();
	multiselect_sel.each(function(index, element) {
		for (var x=0;x<element.options.length;x++) {
			selectCounters[x] = element.options[x].value;
		};
	});
	
	var rootId = jQuery('.product_catalog_tree > ul:first > li:first').attr('id');
	var counterListUrl = '/product_catalog_ajax/trackingcounter_list';
	
	jQuery.ajax({
		url : counterListUrl,
		type: "post",
		data: {'product_nid': rootId, 'counter_nids':selectCounters},
		success : function(data) {
			jQuery(".product_catalog_tree").unmask();
		},
	});
}
*/


// Selects all the items in the select box it is called from.
// usage $('nameofselectbox').selectAll();
jQuery.fn.selectAll = function() {
  this.each(function() {
    for (var x=0;x<this.options.length;x++) {
      option = this.options[x];
      option.selected = true;   
    }
  });
}

// Removes the content of this select box from the target
// usage $('nameofselectbox').removeContentsFrom(target_selectbox)
jQuery.fn.removeContentsFrom = function() {
  dest = arguments[0];
  this.each(function() {
    for (var x=this.options.length-1;x>=0;x--) {
      dest.removeOption(this.options[x].value);
    }
  });
}

// Moves the selection to the select box specified
// usage $('nameofselectbox').moveSelectionTo(destination_selectbox)
jQuery.fn.moveSelectionTo = function() {
  dest = arguments[0];
  this.each(function() {
    for (var x=0; x < this.options.length; x++) {
      option = this.options[x];
      if (option.selected) {
        dest.addOption(option);
        this.remove(x);
        //$(this).triggerHandler('option-removed', option);
        x--; // Move x back one so that we'll successfully check again to see if it's selected.
      }
    }
  });
}

// Adds an option to a select box
// usage $('nameofselectbox').addOption(optiontoadd);
jQuery.fn.addOption = function() {
  option = arguments[0];
  this.each(function() {
    //had to alter code to this to make it work in IE
    anOption = document.createElement('option');
    anOption.text = option.text;
    anOption.value = option.value;
    this.options[this.options.length] = anOption;
    //$(this).triggerHandler('option-added', anOption);
    return false;
  });
}

// Removes an option from a select box
// usage $('nameofselectbox').removeOption(valueOfOptionToRemove);
jQuery.fn.removeOption = function() {
  targOption = arguments[0];
  this.each(function() {
    for (var x=this.options.length-1;x>=0;x--) {
      option = this.options[x];
      if (option.value==targOption) {
        this.remove(x);
        //$(this).triggerHandler('option-removed', option);
      }
    }
  });
}
