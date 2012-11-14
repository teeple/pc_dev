
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
      $('input.form-submit:not(.multiselect-processed)', context).addClass('multiselect-processed').click( $.fn.eventSetSelectAll );
      
      $('#multiselect_custom_button').click($.fn.eventSetSelectAll);
            
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
	jQuery('select.multiselect_sel').selectAll();
	
	$(".product_catalog_tree").mask("Adding...");
			$.ajax({
				url : selectItemUrl,
				type: "post",
		        data: {'product_nid': rootId, 'parent_nid': parent.attr('id'), 'child_nid': selectedItemNid, 'rel_type': parent.attr('rel'),'max_weight':max_weight, 'min_weight':min_weight,'parent_title':parent.children('a').text()},
				success : function(data) {
					var output = $.parseJSON(data);
					
					var product_catalog_ajax_result = output[0].settings.product_catalog_ajax_result;
					
					// 만약 기존에 달려있는 children을 지워주어야 할 경우에는 
					if(product_catalog_ajax_result.data.replace_or_append == 'replace') {
						var parentObj = $('.product_catalog_tree').jstree('get_json', parent)[0];
						var children = $.fn.getChildrenNotSelf(parentObj);
						for(var i=0;i<children.length;i++){
							$('.product_catalog_tree').jstree('delete_node', $('#'+children[i]));
						}
					}
					
					$.fn.addUnNestedMultipleChildren(product_catalog_ajax_result);
					
					var message = '<div style="display:block;"><div class="messages status"><h2 class="element-invisible">Status message</h2>'
						+ product_catalog_ajax_result.data.parent_title + ' has been changed.</div></div>';
					
					$.fn.clearTreeContentDiv(message);
					$(".product_catalog_tree").unmask();
				}
			});
			
}

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