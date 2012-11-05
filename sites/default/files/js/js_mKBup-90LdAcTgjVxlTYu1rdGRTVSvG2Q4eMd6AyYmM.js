(function ($) {

/**
 * Attaches double-click behavior to toggle full path of Krumo elements.
 */
Drupal.behaviors.devel = {
  attach: function (context, settings) {

    // Add hint to footnote
    $('.krumo-footnote .krumo-call').before('<img style="vertical-align: middle;" title="Click to expand. Double-click to show path." src="' + Drupal.settings.basePath + 'misc/help.png"/>');

    var krumo_name = [];
    var krumo_type = [];

    function krumo_traverse(el) {
      krumo_name.push($(el).html());
      krumo_type.push($(el).siblings('em').html().match(/\w*/)[0]);

      if ($(el).closest('.krumo-nest').length > 0) {
        krumo_traverse($(el).closest('.krumo-nest').prev().find('.krumo-name'));
      }
    }

    $('.krumo-child > div:first-child', context).dblclick(
      function(e) {
        if ($(this).find('> .krumo-php-path').length > 0) {
          // Remove path if shown.
          $(this).find('> .krumo-php-path').remove();
        }
        else {
          // Get elements.
          krumo_traverse($(this).find('> a.krumo-name'));

          // Create path.
          var krumo_path_string = '';
          for (var i = krumo_name.length - 1; i >= 0; --i) {
            // Start element.
            if ((krumo_name.length - 1) == i)
              krumo_path_string += '$' + krumo_name[i];

            if (typeof krumo_name[(i-1)] !== 'undefined') {
              if (krumo_type[i] == 'Array') {
                krumo_path_string += "[";
                if (!/^\d*$/.test(krumo_name[(i-1)]))
                  krumo_path_string += "'";
                krumo_path_string += krumo_name[(i-1)];
                if (!/^\d*$/.test(krumo_name[(i-1)]))
                  krumo_path_string += "'";
                krumo_path_string += "]";
              }
              if (krumo_type[i] == 'Object')
                krumo_path_string += '->' + krumo_name[(i-1)];
            }
          }
          $(this).append('<div class="krumo-php-path" style="font-family: Courier, monospace; font-weight: bold;">' + krumo_path_string + '</div>');

          // Reset arrays.
          krumo_name = [];
          krumo_type = [];
        }
      }
    );
  }
};

})(jQuery);
;
/**
 * Extend Drupal.states.Dependent.comparisons. With this extension condition
 * states can be set as array:
 * JQUERY_SELECTOR => array('value' => array('value_1', 'value_2', ....)),
 */

(function ($) {
  if (Drupal.states) {
    var states = Drupal.states.Dependent.comparisons;
    var trigger = false;

    var arrayState = {
      'Array': function (reference, value) {
        // in case of boolean Single on/off checkbox - when field is unchecked value is empty
        if (value == '') {
		  value = 0;
		}
      	var conditionType = reference.condition_type;
	      if (value instanceof Array) {
	        if (conditionType == 'or') {
	          var found = false;
	          $.each(reference, function(index, val) {
		        for (var i = 0; i < value.length; ++i) {
	              if (value[i] == val) {
	                found = true;
	                return false;
	              }
	            }
	          });
	          
	          if ($('.date-conditional-state').length != 0) {
	            date_field_handler(found);
              }
	          return found;
			}
            else {   // conditionType is and
	          var not_found = false;
		        $.each(reference, function(index, val) {
		          for (var i = 0; i < value.length; ++i) {
	                if (value[i] == val) {
	                  return;
                    }
	              }
	              not_found = true;
	              return false;
	            });
	            if ($('.date-conditional-state').length != 0) {
	              date_field_handler(!not_found);
                }
	            return !not_found;
	        }
	      }
	      else {
	        for (var i = 0; i < reference.length; ++i) {
	          if (reference[i] == value) {
	            date_field_handler(true);
	            return true;
	          }
	        }
	        if ($('.date-conditional-state').length != 0) {
	          date_field_handler(false);
          }
	        return false;
  	    }
      }
    };

    var extendStates = $.extend(true, states, arrayState);
    Drupal.states.Dependent.comparisons = extendStates;
    // needed for IE7, IE8
    Drupal.states.Dependent.prototype.compare =
      function (reference, selector, state) {
        var value = this.values[selector][state.name];
        var name = reference.constructor.name;
        if (!name) {
          name = reference.constructor.toString().match(/function +([a-zA-Z0-9_]+) *\(/)[1];
        }
        if (name in Drupal.states.Dependent.comparisons) {
          // Use a custom compare function for certain reference value types.
          return Drupal.states.Dependent.comparisons[name](reference, value);
        }
        else {
          // Do a plain comparison otherwise.
          return compare(reference, value);
        }
    };

    Drupal.states.Trigger.states.value.change = function () {
      var values = this.val();
      if (values instanceof Array) {
        return values;
      }
      else {
        if (this.is('input')) {
          return this.filter(':checked').map(function() {
            return $(this).val();
          }).get();
        }
        else {
          return $(this).val();
        }
      }
    }
  }

  if (Drupal.behaviors.states) {
    var old_hook = Drupal.behaviors.states.attach;
    // Pull combination type down into the value
    // This is a bit of a hack which is needed because states.js
    // _only_ passes the values to our comparison function, but
    // we need additional info. So we just hack that additional
    // info into the value :)
    Drupal.behaviors.states.attach = function(context, settings) {
      for (var k in Drupal.settings.states) {
    	  var triggered_field = Drupal.settings.states[k];
        for (var t in triggered_field) {
          var state_type = triggered_field[t];
          for (var c in state_type) {
            var control_field = state_type[c];
            if (control_field.value) {
              control_field.value.condition_type = control_field.condition_type;
            }
            delete control_field.condition_type;
          }
        }
      }
      old_hook(context, settings); // Invoke the original handler after we're done
    };
  }

  // hack for date fields
  function date_field_handler(trigger) {
    var state = $('.date-conditional-state').attr('state');

    if ((trigger && state == 'enabled') || (!trigger && state == 'disabled')) {
      $('.date-conditional-state :input').removeAttr('disabled');
    }
    else if (trigger && state == 'disabled' || (!trigger && state == 'enabled')) {
      $('.date-conditional-state :input').attr('disabled', true);
    }

  }

  function compare (a, b) {
    return (a === b) ? (a === undefined ? a : true) : (a === undefined || b === undefined);
  }

})(jQuery);
;
/**
 * Add behavior for required condition.
 */

(function ($) {
  $(document).bind('state:required', function(e) {
   	var label = $(e.target).closest('.form-item, .form-submit, .form-wrapper').find("label").first();
   	var required = '<span title="This field is required." class="form-required">*</span>';
    $(e.target).closest('.form-item, .form-submit, .form-wrapper').removeClass('form-required');

    var none_input =  $(e.target).find('input[value=_none]');
    var none_option = $(e.target).find('option[value=_none]');
    if (e.trigger) {
      if (e.value) {
        // Check for multivalue field - if textfield has more than one value
        // form elements are displayed in table header of the table (hidden) is
        // also on the top of the page then we need to add required class for
        // all the labels for this field.
        if ($(e.target).find("span.form-required").first().length == 0 && $(e.target).find("table").length == 0) {
          label.append(required);
        }
        else if ($(e.target).find("span.form-required").length == 0 && $(e.target).find("table").length){
          $(e.target).find("table th").find("label").append(required);
        }
        none_option.hide();
        none_input.parent().hide();
      }
      else {
        none_option.show();
        none_input.parent().show();
        label.find("span.form-required").remove();
        $(e.target).find("table th").find("label").find("span.form-required").remove();
      }
    }
  });
})(jQuery);
;
(function ($) {

Drupal.toolbar = Drupal.toolbar || {};

/**
 * Attach toggling behavior and notify the overlay of the toolbar.
 */
Drupal.behaviors.toolbar = {
  attach: function(context) {

    // Set the initial state of the toolbar.
    $('#toolbar', context).once('toolbar', Drupal.toolbar.init);

    // Toggling toolbar drawer.
    $('#toolbar a.toggle', context).once('toolbar-toggle').click(function(e) {
      Drupal.toolbar.toggle();
      // Allow resize event handlers to recalculate sizes/positions.
      $(window).triggerHandler('resize');
      return false;
    });
  }
};

/**
 * Retrieve last saved cookie settings and set up the initial toolbar state.
 */
Drupal.toolbar.init = function() {
  // Retrieve the collapsed status from a stored cookie.
  var collapsed = $.cookie('Drupal.toolbar.collapsed');

  // Expand or collapse the toolbar based on the cookie value.
  if (collapsed == 1) {
    Drupal.toolbar.collapse();
  }
  else {
    Drupal.toolbar.expand();
  }
};

/**
 * Collapse the toolbar.
 */
Drupal.toolbar.collapse = function() {
  var toggle_text = Drupal.t('Show shortcuts');
  $('#toolbar div.toolbar-drawer').addClass('collapsed');
  $('#toolbar a.toggle')
    .removeClass('toggle-active')
    .attr('title',  toggle_text)
    .html(toggle_text);
  $('body').removeClass('toolbar-drawer').css('paddingTop', Drupal.toolbar.height());
  $.cookie(
    'Drupal.toolbar.collapsed',
    1,
    {
      path: Drupal.settings.basePath,
      // The cookie should "never" expire.
      expires: 36500
    }
  );
};

/**
 * Expand the toolbar.
 */
Drupal.toolbar.expand = function() {
  var toggle_text = Drupal.t('Hide shortcuts');
  $('#toolbar div.toolbar-drawer').removeClass('collapsed');
  $('#toolbar a.toggle')
    .addClass('toggle-active')
    .attr('title',  toggle_text)
    .html(toggle_text);
  $('body').addClass('toolbar-drawer').css('paddingTop', Drupal.toolbar.height());
  $.cookie(
    'Drupal.toolbar.collapsed',
    0,
    {
      path: Drupal.settings.basePath,
      // The cookie should "never" expire.
      expires: 36500
    }
  );
};

/**
 * Toggle the toolbar.
 */
Drupal.toolbar.toggle = function() {
  if ($('#toolbar div.toolbar-drawer').hasClass('collapsed')) {
    Drupal.toolbar.expand();
  }
  else {
    Drupal.toolbar.collapse();
  }
};

Drupal.toolbar.height = function() {
  var $toolbar = $('#toolbar');
  var height = $toolbar.outerHeight();
  // In modern browsers (including IE9), when box-shadow is defined, use the
  // normal height.
  var cssBoxShadowValue = $toolbar.css('box-shadow');
  var boxShadow = (typeof cssBoxShadowValue !== 'undefined' && cssBoxShadowValue !== 'none');
  // In IE8 and below, we use the shadow filter to apply box-shadow styles to
  // the toolbar. It adds some extra height that we need to remove.
  if (!boxShadow && /DXImageTransform\.Microsoft\.Shadow/.test($toolbar.css('filter'))) {
    height -= $toolbar[0].filters.item("DXImageTransform.Microsoft.Shadow").strength;
  }
  return height;
};

})(jQuery);
;
