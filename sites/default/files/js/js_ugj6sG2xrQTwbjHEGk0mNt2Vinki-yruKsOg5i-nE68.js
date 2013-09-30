(function($) {
  Drupal.behaviors.accordion_blocks = {
	  attach: function() {
	    $('.accordion_blocks_container').accordion({header: "h2", autoHeight: false});
	  }
  };
})(jQuery);


;

(function ($) {
  Drupal.Panels = {};

  Drupal.Panels.autoAttach = function() {
    if ($.browser.msie) {
      // If IE, attach a hover event so we can see our admin links.
      $("div.panel-pane").hover(
        function() {
          $('div.panel-hide', this).addClass("panel-hide-hover"); return true;
        },
        function() {
          $('div.panel-hide', this).removeClass("panel-hide-hover"); return true;
        }
      );
      $("div.admin-links").hover(
        function() {
          $(this).addClass("admin-links-hover"); return true;
        },
        function(){
          $(this).removeClass("admin-links-hover"); return true;
        }
      );
    }
  };

  $(Drupal.Panels.autoAttach);
})(jQuery);
;
/**
* hoverIntent r6 // 2011.02.26 // jQuery 1.5.1+
* <http://cherne.net/brian/resources/jquery.hoverIntent.html>
* 
* @param  f  onMouseOver function || An object with configuration options
* @param  g  onMouseOut function  || Nothing (use configuration options object)
* @author    Brian Cherne brian(at)cherne(dot)net
*/
(function($){$.fn.hoverIntent=function(f,g){var cfg={sensitivity:7,interval:100,timeout:0};cfg=$.extend(cfg,g?{over:f,out:g}:f);var cX,cY,pX,pY;var track=function(ev){cX=ev.pageX;cY=ev.pageY};var compare=function(ev,ob){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t);if((Math.abs(pX-cX)+Math.abs(pY-cY))<cfg.sensitivity){$(ob).unbind("mousemove",track);ob.hoverIntent_s=1;return cfg.over.apply(ob,[ev])}else{pX=cX;pY=cY;ob.hoverIntent_t=setTimeout(function(){compare(ev,ob)},cfg.interval)}};var delay=function(ev,ob){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t);ob.hoverIntent_s=0;return cfg.out.apply(ob,[ev])};var handleHover=function(e){var ev=jQuery.extend({},e);var ob=this;if(ob.hoverIntent_t){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t)}if(e.type=="mouseenter"){pX=ev.pageX;pY=ev.pageY;$(ob).bind("mousemove",track);if(ob.hoverIntent_s!=1){ob.hoverIntent_t=setTimeout(function(){compare(ev,ob)},cfg.interval)}}else{$(ob).unbind("mousemove",track);if(ob.hoverIntent_s==1){ob.hoverIntent_t=setTimeout(function(){delay(ev,ob)},cfg.timeout)}}};return this.bind('mouseenter',handleHover).bind('mouseleave',handleHover)}})(jQuery);;
/* Copyright (c) 2010 Brandon Aaron (http://brandonaaron.net)
 * Licensed under the MIT License (LICENSE.txt).
 *
 * Version 2.1.2
 */
(function(a){a.fn.bgiframe=(a.browser.msie&&/msie 6\.0/i.test(navigator.userAgent)?function(d){d=a.extend({top:"auto",left:"auto",width:"auto",height:"auto",opacity:true,src:"javascript:false;"},d);var c='<iframe class="bgiframe"frameborder="0"tabindex="-1"src="'+d.src+'"style="display:block;position:absolute;z-index:-1;'+(d.opacity!==false?"filter:Alpha(Opacity='0');":"")+"top:"+(d.top=="auto"?"expression(((parseInt(this.parentNode.currentStyle.borderTopWidth)||0)*-1)+'px')":b(d.top))+";left:"+(d.left=="auto"?"expression(((parseInt(this.parentNode.currentStyle.borderLeftWidth)||0)*-1)+'px')":b(d.left))+";width:"+(d.width=="auto"?"expression(this.parentNode.offsetWidth+'px')":b(d.width))+";height:"+(d.height=="auto"?"expression(this.parentNode.offsetHeight+'px')":b(d.height))+';"/>';return this.each(function(){if(a(this).children("iframe.bgiframe").length===0){this.insertBefore(document.createElement(c),this.firstChild)}})}:function(){return this});a.fn.bgIframe=a.fn.bgiframe;function b(c){return c&&c.constructor===Number?c+"px":c}})(jQuery);;
/*
 * Superfish v1.4.8 - jQuery menu widget
 * Copyright (c) 2008 Joel Birch
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 *
 * CHANGELOG: http://users.tpg.com.au/j_birch/plugins/superfish/changelog.txt
 */
/*
 * This is not the original jQuery Supersubs plugin.
 * Please refer to the README for more information.
 */

(function($){
  $.fn.superfish = function(op){
    var sf = $.fn.superfish,
      c = sf.c,
      $arrow = $(['<span class="',c.arrowClass,'"> &#187;</span>'].join('')),
      over = function(){
        var $$ = $(this), menu = getMenu($$);
        clearTimeout(menu.sfTimer);
        $$.showSuperfishUl().siblings().hideSuperfishUl();
      },
      out = function(){
        var $$ = $(this), menu = getMenu($$), o = sf.op;
        clearTimeout(menu.sfTimer);
        menu.sfTimer=setTimeout(function(){
          o.retainPath=($.inArray($$[0],o.$path)>-1);
          $$.hideSuperfishUl();
          if (o.$path.length && $$.parents(['li.',o.hoverClass].join('')).length<1){over.call(o.$path);}
        },o.delay);
      },
      getMenu = function($menu){
        var menu = $menu.parents(['ul.',c.menuClass,':first'].join(''))[0];
        sf.op = sf.o[menu.serial];
        return menu;
      },
      addArrow = function($a){ $a.addClass(c.anchorClass).append($arrow.clone()); };

    return this.each(function() {
      var s = this.serial = sf.o.length;
      var o = $.extend({},sf.defaults,op);
      o.$path = $('li.'+o.pathClass,this).slice(0,o.pathLevels).each(function(){
        $(this).addClass([o.hoverClass,c.bcClass].join(' '))
          .filter('li:has(ul)').removeClass(o.pathClass);
      });
      sf.o[s] = sf.op = o;

      $('li:has(ul)',this)[($.fn.hoverIntent && !o.disableHI) ? 'hoverIntent' : 'hover'](over,out).each(function() {
        if (o.autoArrows) addArrow( $('>a:first-child',this) );
      })
      .not('.'+c.bcClass)
        .hideSuperfishUl();

      var $a = $('a',this);
      $a.each(function(i){
        var $li = $a.eq(i).parents('li');
        $a.eq(i).focus(function(){over.call($li);}).blur(function(){out.call($li);});
      });
      o.onInit.call(this);

    }).each(function() {
      var menuClasses = [c.menuClass];
      if (sf.op.dropShadows  && !($.browser.msie && $.browser.version < 7)) menuClasses.push(c.shadowClass);
      $(this).addClass(menuClasses.join(' '));
    });
  };

  var sf = $.fn.superfish;
  sf.o = [];
  sf.op = {};
  sf.IE7fix = function(){
    var o = sf.op;
    if ($.browser.msie && $.browser.version > 6 && o.dropShadows && o.animation.opacity!=undefined)
      this.toggleClass(sf.c.shadowClass+'-off');
    };
  sf.c = {
    bcClass: 'sf-breadcrumb',
    menuClass: 'sf-js-enabled',
    anchorClass: 'sf-with-ul',
    arrowClass: 'sf-sub-indicator',
    shadowClass: 'sf-shadow'
  };
  sf.defaults = {
    hoverClass: 'sfHover',
    pathClass: 'overideThisToUse',
    pathLevels: 1,
    delay: 800,
    animation: {opacity:'show'},
    speed: 'normal',
    autoArrows: true,
    dropShadows: true,
    disableHI: false, // true disables hoverIntent detection
    onInit: function(){}, // callback functions
    onBeforeShow: function(){},
    onShow: function(){},
    onHide: function(){}
  };
  $.fn.extend({
    hideSuperfishUl : function(){
      var o = sf.op,
        not = (o.retainPath===true) ? o.$path : '';
      o.retainPath = false;
      var $ul = $(['li.',o.hoverClass].join(''),this).add(this).not(not).removeClass(o.hoverClass)
          .find('>ul').css({top: '-99999em'}).addClass('sf-hidden');
      o.onHide.call($ul);
      return this;
    },
    showSuperfishUl : function(){
      var o = sf.op,
        sh = sf.c.shadowClass+'-off',
        $ul = this.addClass(o.hoverClass)
          .find('>ul.sf-hidden').css({display: 'none', top: ''}).removeClass('sf-hidden');
      sf.IE7fix.call($ul);
      o.onBeforeShow.call($ul);
      $ul.animate(o.animation,o.speed,function(){ sf.IE7fix.call($ul); o.onShow.call($ul); });
      return this;
    }
  });
})(jQuery);;
/*
 * Supersubs v0.2b - jQuery plugin
 * Copyright (c) 2008 Joel Birch
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 *
 * This plugin automatically adjusts submenu widths of suckerfish-style menus to that of
 * their longest list item children. If you use this, please expect bugs and report them
 * to the jQuery Google Group with the word 'Superfish' in the subject line.
 *
 */
/*
 * This is not the original jQuery Supersubs plugin.
 * Please refer to the README for more information.
 */

(function($){ // $ will refer to jQuery within this closure
  $.fn.supersubs = function(options){
    var opts = $.extend({}, $.fn.supersubs.defaults, options);
    // return original object to support chaining
    return this.each(function() {
      // cache selections
      var $$ = $(this);
      // support metadata
      var o = $.meta ? $.extend({}, opts, $$.data()) : opts;
      // get the font size of menu.
      // .css('fontSize') returns various results cross-browser, so measure an em dash instead
      var fontsize = $('<li id="menu-fontsize">&#8212;</li>').css({
        'padding' : 0,
        'position' : 'absolute',
        'top' : '-99999em',
        'width' : 'auto'
      }).appendTo($$).width(); //clientWidth is faster, but was incorrect here
      // remove em dash
      $('#menu-fontsize').remove();

      // Jump on level if it's a "NavBar"
      if ($$.hasClass('sf-navbar')) {
        $$ = $('li > ul', $$);
      }
      // cache all ul elements 
      $ULs = $$.find('ul:not(.sf-megamenu)');
      // loop through each ul in menu
      $ULs.each(function(i) {
        // cache this ul
        var $ul = $ULs.eq(i);
        // get all (li) children of this ul
        var $LIs = $ul.children();
        // get all anchor grand-children
        var $As = $LIs.children('a');
        // force content to one line and save current float property
        var liFloat = $LIs.css('white-space','nowrap').css('float');
        // remove width restrictions and floats so elements remain vertically stacked
        var emWidth = $ul.add($LIs).add($As).css({
          'float' : 'none',
          'width'  : 'auto'
        })
        // this ul will now be shrink-wrapped to longest li due to position:absolute
        // so save its width as ems. Clientwidth is 2 times faster than .width() - thanks Dan Switzer
        .end().end()[0].clientWidth / fontsize;
        // add more width to ensure lines don't turn over at certain sizes in various browsers
        emWidth += o.extraWidth;
        // restrict to at least minWidth and at most maxWidth
        if (emWidth > o.maxWidth)    { emWidth = o.maxWidth; }
        else if (emWidth < o.minWidth)  { emWidth = o.minWidth; }
        emWidth += 'em';
        // set ul to width in ems
        $ul.css('width',emWidth);
        // restore li floats to avoid IE bugs
        // set li width to full width of this ul
        // revert white-space to normal
        $LIs.css({
          'float' : liFloat,
          'width' : '100%',
          'white-space' : 'normal'
        })
        // update offset position of descendant ul to reflect new width of parent
        .each(function(){
          var $childUl = $('>ul',this);
          var offsetDirection = $childUl.css('left')!==undefined ? 'left' : 'right';
          $childUl.css(offsetDirection,emWidth);
        });
      });
    });
  };
  // expose defaults
  $.fn.supersubs.defaults = {
    minWidth: 9, // requires em unit.
    maxWidth: 25, // requires em unit.
    extraWidth: 0 // extra width can ensure lines don't sometimes turn over due to slight browser differences in how they round-off values
  };
})(jQuery); // plugin code ends;
/*
 * Supposition v0.2 - an optional enhancer for Superfish jQuery menu widget.
 *
 * Copyright (c) 2008 Joel Birch - based mostly on work by Jesse Klaasse and credit goes largely to him.
 * Special thanks to Karl Swedberg for valuable input.
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 */
/*
 * This is not the original jQuery Supersubs plugin.
 * Please refer to the README for more information.
 */

(function($){
  $.fn.supposition = function(){
    var $w = $(window), /*do this once instead of every onBeforeShow call*/
    _offset = function(dir) {
      return window[dir == 'y' ? 'pageYOffset' : 'pageXOffset']
      || document.documentElement && document.documentElement[dir=='y' ? 'scrollTop' : 'scrollLeft']
      || document.body[dir=='y' ? 'scrollTop' : 'scrollLeft'];
    },
    onHide = function(){
      this.css({bottom:''});
    },
    onBeforeShow = function(){
      this.each(function(){
        var $u = $(this);
        $u.css('display','block');
        var menuWidth = $u.width(),
        menuParentWidth = $u.closest('li').outerWidth(true),
        menuParentLeft = $u.closest('li').offset().left,
        totalRight = $w.width() + _offset('x'),
        menuRight = $u.offset().left + menuWidth,
        exactMenuWidth = (menuRight > (menuParentWidth + menuParentLeft)) ? menuWidth - (menuRight - (menuParentWidth + menuParentLeft)) : menuWidth;  
        if ($u.parents('.sf-js-enabled').hasClass('rtl')) {
          if (menuParentLeft < exactMenuWidth) {
            $u.css('left', menuParentWidth + 'px');
            $u.css('right', 'auto');
          }
        }
        else {
          if (menuRight > totalRight && menuParentLeft > menuWidth) {
            $u.css('right', menuParentWidth + 'px');
            $u.css('left', 'auto');
          }
        }
        var windowHeight = $w.height(),
        offsetTop = $u.offset().top,
        menuParentShadow = ($u.closest('.sf-menu').hasClass('sf-shadow') && $u.css('padding-bottom').length > 0) ? parseInt($u.css('padding-bottom').slice(0,-2)) : 0,
        menuParentHeight = ($u.closest('.sf-menu').hasClass('sf-vertical')) ? '-' + menuParentShadow : $u.parent().outerHeight(true) - menuParentShadow,
        menuHeight = $u.height(),
        baseline = windowHeight + _offset('y');
        var expandUp = ((offsetTop + menuHeight > baseline) && (offsetTop > menuHeight));
        if (expandUp) {
          $u.css('bottom', menuParentHeight + 'px');
          $u.css('top', 'auto');
        }
        $u.css('display','none');
      });
    };

    return this.each(function() {
      var o = $.fn.superfish.o[this.serial]; /* get this menu's options */

      /* if callbacks already set, store them */
      var _onBeforeShow = o.onBeforeShow,
      _onHide = o.onHide;

      $.extend($.fn.superfish.o[this.serial],{
        onBeforeShow: function() {
          onBeforeShow.call(this); /* fire our Supposition callback */
          _onBeforeShow.call(this); /* fire stored callbacks */
        },
        onHide: function() {
          onHide.call(this); /* fire our Supposition callback */
          _onHide.call(this); /* fire stored callbacks */
        }
      });
    });
  };
})(jQuery);;
/*
 * sf-Touchscreen v1.0b - Provides touchscreen compatibility for the jQuery Superfish plugin.
 *
 * Developer's note:
 * Built as a part of the Superfish project for Drupal (http://drupal.org/project/superfish) 
 * Found any bug? have any cool ideas? contact me right away! http://drupal.org/user/619294/contact
 *
 * jQuery version: 1.3.x or higher.
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 */

(function($){
  $.fn.sftouchscreen = function() {
    // Return original object to support chaining.
    return this.each( function() {
      // Select hyperlinks from parent menu items.
      $(this).find('li > ul').closest('li').children('a').each( function() {
        var $item = $(this);
        // No .toggle() here as it's not possible to reset it.
        $item.click( function(event){
          // Already clicked? proceed to the URI.
          if ($item.hasClass('sf-clicked')) {
            var $uri = $item.attr('href');
            window.location = $uri;
          }
          else {
            event.preventDefault();
            $item.addClass('sf-clicked');
          }
        }).closest('li').mouseleave( function(){
          // So, we reset everything.
          $item.removeClass('sf-clicked');
        });
      });
    });
  };
})(jQuery);;
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
(function($) {
	$.fn.drawFlotLinkInit = function(){
		/*
		if ($("#flot_div").length > 0) {
			$.fn.makeCollectionItemAttributes();
			var showChartLink = $("#chart_show");
			showChartLink.bind('click',function(){$.fn.drawFlot();});
			$.fn.drawFlot();
		}
		*/
	};	

	$.fn.makeCollectionItemAttributes = function (){
		/*
		var rowNum = 0;
		$("#field-charge-collection-values").find('tbody').find('tr').each(
			function(){
				//$(this).find('input').attr('rownum',rowNum);
				$(this).find('input').attr('collection_rownum',rowNum);				
				rowNum++;
				$(this).find('.field-name-field-range-start').find('input').attr('collection_field','range_start');
				$(this).find('.field-name-field-range-end').find('input').attr('collection_field','range_end');
				$(this).find('.field-name-field-uom-amount').find('input').attr('collection_field','uom_amount');
				$(this).find('.field-name-field-price-amount-float').find('input').attr('collection_field','price_amount');
			}
		);
		*/
	};
	
	$.fn.createDrawRawData = function(){
		/*
		var settings = {};
		//('[collection_rownum=0]')
		
		//set xaxis ticks
		var rangeStart = new Array();
		$('[collection_field="range_start"]').each(
			function (){
				var tmpRangeStart = $(this).val();
				if(tmpRangeStart.length > 0){
					rangeStart.push(tmpRangeStart);
				}
			}
		);
		var rangeEnd = new Array();
		var minRangeStart = 0;
		var maxRangeEnd = 0;
		$('[collection_field="range_end"]').each(
			function (){
				var tmpRangeEnd = $(this).val();
				if(tmpRangeEnd.length > 0){
					rangeEnd.push(tmpRangeEnd);
				}
			}
		);
		if(rangeEnd.length == 0){
			maxRangeEnd = 0;
		}else{
			maxRangeEnd = Math.max.apply( Math, rangeEnd );
		}
		if(rangeStart.length == 0){
			minRangeStart = 0;
		}else{
			minRangeStart = Math.min.apply( Math, rangeStart);
		}
		
		var hasToCreateInfinity = true;
	
		var xaxisTicks = new Array();
	    for(var i=0;i<=maxRangeEnd+1;i++){
	    	if(i == maxRangeEnd+1){
	    		//xaxisTicks.push(new Array(i,'∞'));	
	    		xaxisTicks.push(new Array(i,'Infinity'));	
	    	}else{
	    		xaxisTicks.push(new Array(i,i.toString()));	    
	    	}
	    }
	    
	    settings.xaxis = {
	    	ticks: xaxisTicks
	    };
	   	    
	    //set data series
	    settings.dataSeries = new Array();
	    var numOfColumn = 4;
	    var numOfRows = $('[collection_field]').length / numOfColumn;
	    for(var i=0;i<numOfRows;i++){
	    	var rangeStart = $('[collection_field=range_start][collection_rownum='+i+']').val();  	
	    	var rangeEnd = $('[collection_field=range_end][collection_rownum='+i+']').val();
	    	var uomAmount = $('[collection_field=uom_amount][collection_rownum='+i+']').val();
	    	var priceAmount = $('[collection_field=price_amount][collection_rownum='+i+']').val();
	    	
	    	if(uomAmount != '' && priceAmount != ''){
	    		var dataSet = {
    	    		data: [],
    	    		bars:{
    		            show: true,
    		            fill: true,
    		            barWidth: 1,
    		            //fillColor: "red"
    		        }
    	    	};
	    		
	    		var tmpPrice = priceAmount/uomAmount;
	    		if(rangeStart == ''){
	    			rangeStart = 0;
	    			minRangeStart = 0;
	    		}
	    		if(rangeEnd == ''){
	    			rangeEnd = maxRangeEnd+1;
	    			hasToCreateInfinity = false;
	    		}else{
		    		if(typeof rangeStart == 'string'){
		    			rangeStart = parseInt(rangeStart);
		    		}
		    		if(typeof rangeEnd == 'string'){
		    			rangeEnd = parseInt(rangeEnd);
		    		}
	    		}
	    		for(var j=rangeStart;;j++){	    			
	    			if(j == rangeEnd) break;	    			
		    		dataSet.data.push(new Array(j,tmpPrice));
	    		}	    		
	    		settings.dataSeries.push(dataSet);
	    		
	    	}
	    }
	    
	    if(minRangeStart > 0){
	    	var dataSet = {
	    		data: [],
	    		bars:{
		            show: true,
		            fill: true,
		            barWidth: 1,
		        }
	    	};
	    	for(var k=0;k<minRangeStart;k++){
	    		dataSet.data.push(new Array(k,0));
	    	}
	    	settings.dataSeries.push(dataSet);
	    }
	    
	    if(hasToCreateInfinity){
	    	var dataSet = {
	    		data: [],
	    		bars:{
		            show: true,
		            fill: true,
		            barWidth: 1,
		        }
	    	};
	    	
	    	dataSet.data.push(new Array(maxRangeEnd,0));
	    	
	    	settings.dataSeries.push(dataSet);
	    }    
	    
		return settings;
		*/
	};
	
	$.fn.drawFlot = function(){
		/*
		if ($("#flot_div").length > 0) {
			//init data		
			$.fn.makeCollectionItemAttributes();
			var settings = $.fn.createDrawRawData();
			
			//draw flot
			$.plot($("#flot_div"),settings.dataSeries,
			 {
			   xaxis: settings.xaxis,	
			   series: {
	               bars:{
	                   show: true,
	                   fill: true
	               }
		       },
		       grid: {
	               hoverable: true,
	               clickable: true
		       },
		       //yaxis: { ticks: 50 }
			 }		 
			);
		}		
		*/
	};
	
})(jQuery);
;
/*! Javascript plotting library for jQuery, v. 0.7.
 *
 * Released under the MIT license by IOLA, December 2007.
 *
 */

// first an inline dependency, jquery.colorhelpers.js, we inline it here
// for convenience

/* Plugin for jQuery for working with colors.
 * 
 * Version 1.1.
 * 
 * Inspiration from jQuery color animation plugin by John Resig.
 *
 * Released under the MIT license by Ole Laursen, October 2009.
 *
 * Examples:
 *
 *   $.color.parse("#fff").scale('rgb', 0.25).add('a', -0.5).toString()
 *   var c = $.color.extract($("#mydiv"), 'background-color');
 *   console.log(c.r, c.g, c.b, c.a);
 *   $.color.make(100, 50, 25, 0.4).toString() // returns "rgba(100,50,25,0.4)"
 *
 * Note that .scale() and .add() return the same modified object
 * instead of making a new one.
 *
 * V. 1.1: Fix error handling so e.g. parsing an empty string does
 * produce a color rather than just crashing.
 */ 
(function(B){B.color={};B.color.make=function(F,E,C,D){var G={};G.r=F||0;G.g=E||0;G.b=C||0;G.a=D!=null?D:1;G.add=function(J,I){for(var H=0;H<J.length;++H){G[J.charAt(H)]+=I}return G.normalize()};G.scale=function(J,I){for(var H=0;H<J.length;++H){G[J.charAt(H)]*=I}return G.normalize()};G.toString=function(){if(G.a>=1){return"rgb("+[G.r,G.g,G.b].join(",")+")"}else{return"rgba("+[G.r,G.g,G.b,G.a].join(",")+")"}};G.normalize=function(){function H(J,K,I){return K<J?J:(K>I?I:K)}G.r=H(0,parseInt(G.r),255);G.g=H(0,parseInt(G.g),255);G.b=H(0,parseInt(G.b),255);G.a=H(0,G.a,1);return G};G.clone=function(){return B.color.make(G.r,G.b,G.g,G.a)};return G.normalize()};B.color.extract=function(D,C){var E;do{E=D.css(C).toLowerCase();if(E!=""&&E!="transparent"){break}D=D.parent()}while(!B.nodeName(D.get(0),"body"));if(E=="rgba(0, 0, 0, 0)"){E="transparent"}return B.color.parse(E)};B.color.parse=function(F){var E,C=B.color.make;if(E=/rgb\(\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*\)/.exec(F)){return C(parseInt(E[1],10),parseInt(E[2],10),parseInt(E[3],10))}if(E=/rgba\(\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*,\s*([0-9]+(?:\.[0-9]+)?)\s*\)/.exec(F)){return C(parseInt(E[1],10),parseInt(E[2],10),parseInt(E[3],10),parseFloat(E[4]))}if(E=/rgb\(\s*([0-9]+(?:\.[0-9]+)?)\%\s*,\s*([0-9]+(?:\.[0-9]+)?)\%\s*,\s*([0-9]+(?:\.[0-9]+)?)\%\s*\)/.exec(F)){return C(parseFloat(E[1])*2.55,parseFloat(E[2])*2.55,parseFloat(E[3])*2.55)}if(E=/rgba\(\s*([0-9]+(?:\.[0-9]+)?)\%\s*,\s*([0-9]+(?:\.[0-9]+)?)\%\s*,\s*([0-9]+(?:\.[0-9]+)?)\%\s*,\s*([0-9]+(?:\.[0-9]+)?)\s*\)/.exec(F)){return C(parseFloat(E[1])*2.55,parseFloat(E[2])*2.55,parseFloat(E[3])*2.55,parseFloat(E[4]))}if(E=/#([a-fA-F0-9]{2})([a-fA-F0-9]{2})([a-fA-F0-9]{2})/.exec(F)){return C(parseInt(E[1],16),parseInt(E[2],16),parseInt(E[3],16))}if(E=/#([a-fA-F0-9])([a-fA-F0-9])([a-fA-F0-9])/.exec(F)){return C(parseInt(E[1]+E[1],16),parseInt(E[2]+E[2],16),parseInt(E[3]+E[3],16))}var D=B.trim(F).toLowerCase();if(D=="transparent"){return C(255,255,255,0)}else{E=A[D]||[0,0,0];return C(E[0],E[1],E[2])}};var A={aqua:[0,255,255],azure:[240,255,255],beige:[245,245,220],black:[0,0,0],blue:[0,0,255],brown:[165,42,42],cyan:[0,255,255],darkblue:[0,0,139],darkcyan:[0,139,139],darkgrey:[169,169,169],darkgreen:[0,100,0],darkkhaki:[189,183,107],darkmagenta:[139,0,139],darkolivegreen:[85,107,47],darkorange:[255,140,0],darkorchid:[153,50,204],darkred:[139,0,0],darksalmon:[233,150,122],darkviolet:[148,0,211],fuchsia:[255,0,255],gold:[255,215,0],green:[0,128,0],indigo:[75,0,130],khaki:[240,230,140],lightblue:[173,216,230],lightcyan:[224,255,255],lightgreen:[144,238,144],lightgrey:[211,211,211],lightpink:[255,182,193],lightyellow:[255,255,224],lime:[0,255,0],magenta:[255,0,255],maroon:[128,0,0],navy:[0,0,128],olive:[128,128,0],orange:[255,165,0],pink:[255,192,203],purple:[128,0,128],violet:[128,0,128],red:[255,0,0],silver:[192,192,192],white:[255,255,255],yellow:[255,255,0]}})(jQuery);

// the actual Flot code
(function($) {
    function Plot(placeholder, data_, options_, plugins) {
        // data is on the form:
        //   [ series1, series2 ... ]
        // where series is either just the data as [ [x1, y1], [x2, y2], ... ]
        // or { data: [ [x1, y1], [x2, y2], ... ], label: "some label", ... }
        
        var series = [],
            options = {
                // the color theme used for graphs
                colors: ["#edc240", "#afd8f8", "#cb4b4b", "#4da74d", "#9440ed"],
                legend: {
                    show: true,
                    noColumns: 1, // number of colums in legend table
                    labelFormatter: null, // fn: string -> string
                    labelBoxBorderColor: "#ccc", // border color for the little label boxes
                    container: null, // container (as jQuery object) to put legend in, null means default on top of graph
                    position: "ne", // position of default legend container within plot
                    margin: 5, // distance from grid edge to default legend container within plot
                    backgroundColor: null, // null means auto-detect
                    backgroundOpacity: 0.85 // set to 0 to avoid background
                },
                xaxis: {
                    show: null, // null = auto-detect, true = always, false = never
                    position: "bottom", // or "top"
                    mode: null, // null or "time"
                    color: null, // base color, labels, ticks
                    tickColor: null, // possibly different color of ticks, e.g. "rgba(0,0,0,0.15)"
                    transform: null, // null or f: number -> number to transform axis
                    inverseTransform: null, // if transform is set, this should be the inverse function
                    min: null, // min. value to show, null means set automatically
                    max: null, // max. value to show, null means set automatically
                    autoscaleMargin: null, // margin in % to add if auto-setting min/max
                    ticks: null, // either [1, 3] or [[1, "a"], 3] or (fn: axis info -> ticks) or app. number of ticks for auto-ticks
                    tickFormatter: null, // fn: number -> string
                    labelWidth: null, // size of tick labels in pixels
                    labelHeight: null,
                    reserveSpace: null, // whether to reserve space even if axis isn't shown
                    tickLength: null, // size in pixels of ticks, or "full" for whole line
                    alignTicksWithAxis: null, // axis number or null for no sync
                    
                    // mode specific options
                    tickDecimals: null, // no. of decimals, null means auto
                    tickSize: null, // number or [number, "unit"]
                    minTickSize: null, // number or [number, "unit"]
                    monthNames: null, // list of names of months
                    timeformat: null, // format string to use
                    twelveHourClock: false // 12 or 24 time in time mode
                },
                yaxis: {
                    autoscaleMargin: 0.02,
                    position: "left" // or "right"
                },
                xaxes: [],
                yaxes: [],
                series: {
                    points: {
                        show: false,
                        radius: 3,
                        lineWidth: 2, // in pixels
                        fill: true,
                        fillColor: "#ffffff",
                        symbol: "circle" // or callback
                    },
                    lines: {
                        // we don't put in show: false so we can see
                        // whether lines were actively disabled 
                        lineWidth: 2, // in pixels
                        fill: false,
                        fillColor: null,
                        steps: false
                    },
                    bars: {
                        show: false,
                        lineWidth: 2, // in pixels
                        barWidth: 1, // in units of the x axis
                        fill: true,
                        fillColor: null,
                        align: "left", // or "center" 
                        horizontal: false
                    },
                    shadowSize: 3
                },
                grid: {
                    show: true,
                    aboveData: false,
                    color: "#545454", // primary color used for outline and labels
                    backgroundColor: null, // null for transparent, else color
                    borderColor: null, // set if different from the grid color
                    tickColor: null, // color for the ticks, e.g. "rgba(0,0,0,0.15)"
                    labelMargin: 5, // in pixels
                    axisMargin: 8, // in pixels
                    borderWidth: 2, // in pixels
                    minBorderMargin: null, // in pixels, null means taken from points radius
                    markings: null, // array of ranges or fn: axes -> array of ranges
                    markingsColor: "#f4f4f4",
                    markingsLineWidth: 2,
                    // interactive stuff
                    clickable: false,
                    hoverable: false,
                    autoHighlight: true, // highlight in case mouse is near
                    mouseActiveRadius: 10 // how far the mouse can be away to activate an item
                },
                hooks: {}
            },
        canvas = null,      // the canvas for the plot itself
        overlay = null,     // canvas for interactive stuff on top of plot
        eventHolder = null, // jQuery object that events should be bound to
        ctx = null, octx = null,
        xaxes = [], yaxes = [],
        plotOffset = { left: 0, right: 0, top: 0, bottom: 0},
        canvasWidth = 0, canvasHeight = 0,
        plotWidth = 0, plotHeight = 0,
        hooks = {
            processOptions: [],
            processRawData: [],
            processDatapoints: [],
            drawSeries: [],
            draw: [],
            bindEvents: [],
            drawOverlay: [],
            shutdown: []
        },
        plot = this;

        // public functions
        plot.setData = setData;
        plot.setupGrid = setupGrid;
        plot.draw = draw;
        plot.getPlaceholder = function() { return placeholder; };
        plot.getCanvas = function() { return canvas; };
        plot.getPlotOffset = function() { return plotOffset; };
        plot.width = function () { return plotWidth; };
        plot.height = function () { return plotHeight; };
        plot.offset = function () {
            var o = eventHolder.offset();
            o.left += plotOffset.left;
            o.top += plotOffset.top;
            return o;
        };
        plot.getData = function () { return series; };
        plot.getAxes = function () {
            var res = {}, i;
            $.each(xaxes.concat(yaxes), function (_, axis) {
                if (axis)
                    res[axis.direction + (axis.n != 1 ? axis.n : "") + "axis"] = axis;
            });
            return res;
        };
        plot.getXAxes = function () { return xaxes; };
        plot.getYAxes = function () { return yaxes; };
        plot.c2p = canvasToAxisCoords;
        plot.p2c = axisToCanvasCoords;
        plot.getOptions = function () { return options; };
        plot.highlight = highlight;
        plot.unhighlight = unhighlight;
        plot.triggerRedrawOverlay = triggerRedrawOverlay;
        plot.pointOffset = function(point) {
            return {
                left: parseInt(xaxes[axisNumber(point, "x") - 1].p2c(+point.x) + plotOffset.left),
                top: parseInt(yaxes[axisNumber(point, "y") - 1].p2c(+point.y) + plotOffset.top)
            };
        };
        plot.shutdown = shutdown;
        plot.resize = function () {
            getCanvasDimensions();
            resizeCanvas(canvas);
            resizeCanvas(overlay);
        };

        // public attributes
        plot.hooks = hooks;
        
        // initialize
        initPlugins(plot);
        parseOptions(options_);
        setupCanvases();
        setData(data_);
        setupGrid();
        draw();
        bindEvents();


        function executeHooks(hook, args) {
            args = [plot].concat(args);
            for (var i = 0; i < hook.length; ++i)
                hook[i].apply(this, args);
        }

        function initPlugins() {
            for (var i = 0; i < plugins.length; ++i) {
                var p = plugins[i];
                p.init(plot);
                if (p.options)
                    $.extend(true, options, p.options);
            }
        }
        
        function parseOptions(opts) {
            var i;
            
            $.extend(true, options, opts);
            
            if (options.xaxis.color == null)
                options.xaxis.color = options.grid.color;
            if (options.yaxis.color == null)
                options.yaxis.color = options.grid.color;
            
            if (options.xaxis.tickColor == null) // backwards-compatibility
                options.xaxis.tickColor = options.grid.tickColor;
            if (options.yaxis.tickColor == null) // backwards-compatibility
                options.yaxis.tickColor = options.grid.tickColor;

            if (options.grid.borderColor == null)
                options.grid.borderColor = options.grid.color;
            if (options.grid.tickColor == null)
                options.grid.tickColor = $.color.parse(options.grid.color).scale('a', 0.22).toString();
            
            // fill in defaults in axes, copy at least always the
            // first as the rest of the code assumes it'll be there
            for (i = 0; i < Math.max(1, options.xaxes.length); ++i)
                options.xaxes[i] = $.extend(true, {}, options.xaxis, options.xaxes[i]);
            for (i = 0; i < Math.max(1, options.yaxes.length); ++i)
                options.yaxes[i] = $.extend(true, {}, options.yaxis, options.yaxes[i]);

            // backwards compatibility, to be removed in future
            if (options.xaxis.noTicks && options.xaxis.ticks == null)
                options.xaxis.ticks = options.xaxis.noTicks;
            if (options.yaxis.noTicks && options.yaxis.ticks == null)
                options.yaxis.ticks = options.yaxis.noTicks;
            if (options.x2axis) {
                options.xaxes[1] = $.extend(true, {}, options.xaxis, options.x2axis);
                options.xaxes[1].position = "top";
            }
            if (options.y2axis) {
                options.yaxes[1] = $.extend(true, {}, options.yaxis, options.y2axis);
                options.yaxes[1].position = "right";
            }
            if (options.grid.coloredAreas)
                options.grid.markings = options.grid.coloredAreas;
            if (options.grid.coloredAreasColor)
                options.grid.markingsColor = options.grid.coloredAreasColor;
            if (options.lines)
                $.extend(true, options.series.lines, options.lines);
            if (options.points)
                $.extend(true, options.series.points, options.points);
            if (options.bars)
                $.extend(true, options.series.bars, options.bars);
            if (options.shadowSize != null)
                options.series.shadowSize = options.shadowSize;

            // save options on axes for future reference
            for (i = 0; i < options.xaxes.length; ++i)
                getOrCreateAxis(xaxes, i + 1).options = options.xaxes[i];
            for (i = 0; i < options.yaxes.length; ++i)
                getOrCreateAxis(yaxes, i + 1).options = options.yaxes[i];

            // add hooks from options
            for (var n in hooks)
                if (options.hooks[n] && options.hooks[n].length)
                    hooks[n] = hooks[n].concat(options.hooks[n]);

            executeHooks(hooks.processOptions, [options]);
        }

        function setData(d) {
            series = parseData(d);
            fillInSeriesOptions();
            processData();
        }
        
        function parseData(d) {
            var res = [];
            for (var i = 0; i < d.length; ++i) {
                var s = $.extend(true, {}, options.series);

                if (d[i].data != null) {
                    s.data = d[i].data; // move the data instead of deep-copy
                    delete d[i].data;

                    $.extend(true, s, d[i]);

                    d[i].data = s.data;
                }
                else
                    s.data = d[i];
                res.push(s);
            }

            return res;
        }
        
        function axisNumber(obj, coord) {
            var a = obj[coord + "axis"];
            if (typeof a == "object") // if we got a real axis, extract number
                a = a.n;
            if (typeof a != "number")
                a = 1; // default to first axis
            return a;
        }

        function allAxes() {
            // return flat array without annoying null entries
            return $.grep(xaxes.concat(yaxes), function (a) { return a; });
        }
        
        function canvasToAxisCoords(pos) {
            // return an object with x/y corresponding to all used axes 
            var res = {}, i, axis;
            for (i = 0; i < xaxes.length; ++i) {
                axis = xaxes[i];
                if (axis && axis.used)
                    res["x" + axis.n] = axis.c2p(pos.left);
            }

            for (i = 0; i < yaxes.length; ++i) {
                axis = yaxes[i];
                if (axis && axis.used)
                    res["y" + axis.n] = axis.c2p(pos.top);
            }
            
            if (res.x1 !== undefined)
                res.x = res.x1;
            if (res.y1 !== undefined)
                res.y = res.y1;

            return res;
        }
        
        function axisToCanvasCoords(pos) {
            // get canvas coords from the first pair of x/y found in pos
            var res = {}, i, axis, key;

            for (i = 0; i < xaxes.length; ++i) {
                axis = xaxes[i];
                if (axis && axis.used) {
                    key = "x" + axis.n;
                    if (pos[key] == null && axis.n == 1)
                        key = "x";

                    if (pos[key] != null) {
                        res.left = axis.p2c(pos[key]);
                        break;
                    }
                }
            }
            
            for (i = 0; i < yaxes.length; ++i) {
                axis = yaxes[i];
                if (axis && axis.used) {
                    key = "y" + axis.n;
                    if (pos[key] == null && axis.n == 1)
                        key = "y";

                    if (pos[key] != null) {
                        res.top = axis.p2c(pos[key]);
                        break;
                    }
                }
            }
            
            return res;
        }
        
        function getOrCreateAxis(axes, number) {
            if (!axes[number - 1])
                axes[number - 1] = {
                    n: number, // save the number for future reference
                    direction: axes == xaxes ? "x" : "y",
                    options: $.extend(true, {}, axes == xaxes ? options.xaxis : options.yaxis)
                };
                
            return axes[number - 1];
        }

        function fillInSeriesOptions() {
            var i;
            
            // collect what we already got of colors
            var neededColors = series.length,
                usedColors = [],
                assignedColors = [];
            for (i = 0; i < series.length; ++i) {
                var sc = series[i].color;
                if (sc != null) {
                    --neededColors;
                    if (typeof sc == "number")
                        assignedColors.push(sc);
                    else
                        usedColors.push($.color.parse(series[i].color));
                }
            }
            
            // we might need to generate more colors if higher indices
            // are assigned
            for (i = 0; i < assignedColors.length; ++i) {
                neededColors = Math.max(neededColors, assignedColors[i] + 1);
            }

            // produce colors as needed
            var colors = [], variation = 0;
            i = 0;
            while (colors.length < neededColors) {
                var c;
                if (options.colors.length == i) // check degenerate case
                    c = $.color.make(100, 100, 100);
                else
                    c = $.color.parse(options.colors[i]);

                // vary color if needed
                var sign = variation % 2 == 1 ? -1 : 1;
                c.scale('rgb', 1 + sign * Math.ceil(variation / 2) * 0.2)

                // FIXME: if we're getting to close to something else,
                // we should probably skip this one
                colors.push(c);
                
                ++i;
                if (i >= options.colors.length) {
                    i = 0;
                    ++variation;
                }
            }

            // fill in the options
            var colori = 0, s;
            for (i = 0; i < series.length; ++i) {
                s = series[i];
                
                // assign colors
                if (s.color == null) {
                    s.color = colors[colori].toString();
                    ++colori;
                }
                else if (typeof s.color == "number")
                    s.color = colors[s.color].toString();

                // turn on lines automatically in case nothing is set
                if (s.lines.show == null) {
                    var v, show = true;
                    for (v in s)
                        if (s[v] && s[v].show) {
                            show = false;
                            break;
                        }
                    if (show)
                        s.lines.show = true;
                }

                // setup axes
                s.xaxis = getOrCreateAxis(xaxes, axisNumber(s, "x"));
                s.yaxis = getOrCreateAxis(yaxes, axisNumber(s, "y"));
            }
        }
        
        function processData() {
            var topSentry = Number.POSITIVE_INFINITY,
                bottomSentry = Number.NEGATIVE_INFINITY,
                fakeInfinity = Number.MAX_VALUE,
                i, j, k, m, length,
                s, points, ps, x, y, axis, val, f, p;

            function updateAxis(axis, min, max) {
                if (min < axis.datamin && min != -fakeInfinity)
                    axis.datamin = min;
                if (max > axis.datamax && max != fakeInfinity)
                    axis.datamax = max;
            }

            $.each(allAxes(), function (_, axis) {
                // init axis
                axis.datamin = topSentry;
                axis.datamax = bottomSentry;
                axis.used = false;
            });
            
            for (i = 0; i < series.length; ++i) {
                s = series[i];
                s.datapoints = { points: [] };
                
                executeHooks(hooks.processRawData, [ s, s.data, s.datapoints ]);
            }
            
            // first pass: clean and copy data
            for (i = 0; i < series.length; ++i) {
                s = series[i];

                var data = s.data, format = s.datapoints.format;

                if (!format) {
                    format = [];
                    // find out how to copy
                    format.push({ x: true, number: true, required: true });
                    format.push({ y: true, number: true, required: true });

                    if (s.bars.show || (s.lines.show && s.lines.fill)) {
                        format.push({ y: true, number: true, required: false, defaultValue: 0 });
                        if (s.bars.horizontal) {
                            delete format[format.length - 1].y;
                            format[format.length - 1].x = true;
                        }
                    }
                    
                    s.datapoints.format = format;
                }

                if (s.datapoints.pointsize != null)
                    continue; // already filled in

                s.datapoints.pointsize = format.length;
                
                ps = s.datapoints.pointsize;
                points = s.datapoints.points;

                insertSteps = s.lines.show && s.lines.steps;
                s.xaxis.used = s.yaxis.used = true;
                
                for (j = k = 0; j < data.length; ++j, k += ps) {
                    p = data[j];

                    var nullify = p == null;
                    if (!nullify) {
                        for (m = 0; m < ps; ++m) {
                            val = p[m];
                            f = format[m];

                            if (f) {
                                if (f.number && val != null) {
                                    val = +val; // convert to number
                                    if (isNaN(val))
                                        val = null;
                                    else if (val == Infinity)
                                        val = fakeInfinity;
                                    else if (val == -Infinity)
                                        val = -fakeInfinity;
                                }

                                if (val == null) {
                                    if (f.required)
                                        nullify = true;
                                    
                                    if (f.defaultValue != null)
                                        val = f.defaultValue;
                                }
                            }
                            
                            points[k + m] = val;
                        }
                    }
                    
                    if (nullify) {
                        for (m = 0; m < ps; ++m) {
                            val = points[k + m];
                            if (val != null) {
                                f = format[m];
                                // extract min/max info
                                if (f.x)
                                    updateAxis(s.xaxis, val, val);
                                if (f.y)
                                    updateAxis(s.yaxis, val, val);
                            }
                            points[k + m] = null;
                        }
                    }
                    else {
                        // a little bit of line specific stuff that
                        // perhaps shouldn't be here, but lacking
                        // better means...
                        if (insertSteps && k > 0
                            && points[k - ps] != null
                            && points[k - ps] != points[k]
                            && points[k - ps + 1] != points[k + 1]) {
                            // copy the point to make room for a middle point
                            for (m = 0; m < ps; ++m)
                                points[k + ps + m] = points[k + m];

                            // middle point has same y
                            points[k + 1] = points[k - ps + 1];

                            // we've added a point, better reflect that
                            k += ps;
                        }
                    }
                }
            }

            // give the hooks a chance to run
            for (i = 0; i < series.length; ++i) {
                s = series[i];
                
                executeHooks(hooks.processDatapoints, [ s, s.datapoints]);
            }

            // second pass: find datamax/datamin for auto-scaling
            for (i = 0; i < series.length; ++i) {
                s = series[i];
                points = s.datapoints.points,
                ps = s.datapoints.pointsize;

                var xmin = topSentry, ymin = topSentry,
                    xmax = bottomSentry, ymax = bottomSentry;
                
                for (j = 0; j < points.length; j += ps) {
                    if (points[j] == null)
                        continue;

                    for (m = 0; m < ps; ++m) {
                        val = points[j + m];
                        f = format[m];
                        if (!f || val == fakeInfinity || val == -fakeInfinity)
                            continue;
                        
                        if (f.x) {
                            if (val < xmin)
                                xmin = val;
                            if (val > xmax)
                                xmax = val;
                        }
                        if (f.y) {
                            if (val < ymin)
                                ymin = val;
                            if (val > ymax)
                                ymax = val;
                        }
                    }
                }
                
                if (s.bars.show) {
                    // make sure we got room for the bar on the dancing floor
                    var delta = s.bars.align == "left" ? 0 : -s.bars.barWidth/2;
                    if (s.bars.horizontal) {
                        ymin += delta;
                        ymax += delta + s.bars.barWidth;
                    }
                    else {
                        xmin += delta;
                        xmax += delta + s.bars.barWidth;
                    }
                }
                
                updateAxis(s.xaxis, xmin, xmax);
                updateAxis(s.yaxis, ymin, ymax);
            }

            $.each(allAxes(), function (_, axis) {
                if (axis.datamin == topSentry)
                    axis.datamin = null;
                if (axis.datamax == bottomSentry)
                    axis.datamax = null;
            });
        }

        function makeCanvas(skipPositioning, cls) {
            var c = document.createElement('canvas');
            c.className = cls;
            c.width = canvasWidth;
            c.height = canvasHeight;
                    
            if (!skipPositioning)
                $(c).css({ position: 'absolute', left: 0, top: 0 });
                
            $(c).appendTo(placeholder);
                
            if (!c.getContext) // excanvas hack
                c = window.G_vmlCanvasManager.initElement(c);

            // used for resetting in case we get replotted
            c.getContext("2d").save();
            
            return c;
        }

        function getCanvasDimensions() {
            canvasWidth = placeholder.width();
            canvasHeight = placeholder.height();
            
            if (canvasWidth <= 0 || canvasHeight <= 0)
                throw "Invalid dimensions for plot, width = " + canvasWidth + ", height = " + canvasHeight;
        }

        function resizeCanvas(c) {
            // resizing should reset the state (excanvas seems to be
            // buggy though)
            if (c.width != canvasWidth)
                c.width = canvasWidth;

            if (c.height != canvasHeight)
                c.height = canvasHeight;

            // so try to get back to the initial state (even if it's
            // gone now, this should be safe according to the spec)
            var cctx = c.getContext("2d");
            cctx.restore();

            // and save again
            cctx.save();
        }
        
        function setupCanvases() {
            var reused,
                existingCanvas = placeholder.children("canvas.base"),
                existingOverlay = placeholder.children("canvas.overlay");

            if (existingCanvas.length == 0 || existingOverlay == 0) {
                // init everything
                
                placeholder.html(""); // make sure placeholder is clear
            
                placeholder.css({ padding: 0 }); // padding messes up the positioning
                
                if (placeholder.css("position") == 'static')
                    placeholder.css("position", "relative"); // for positioning labels and overlay

                getCanvasDimensions();
                
                canvas = makeCanvas(true, "base");
                overlay = makeCanvas(false, "overlay"); // overlay canvas for interactive features

                reused = false;
            }
            else {
                // reuse existing elements

                canvas = existingCanvas.get(0);
                overlay = existingOverlay.get(0);

                reused = true;
            }

            ctx = canvas.getContext("2d");
            octx = overlay.getContext("2d");

            // we include the canvas in the event holder too, because IE 7
            // sometimes has trouble with the stacking order
            eventHolder = $([overlay, canvas]);

            if (reused) {
                // run shutdown in the old plot object
                placeholder.data("plot").shutdown();

                // reset reused canvases
                plot.resize();
                
                // make sure overlay pixels are cleared (canvas is cleared when we redraw)
                octx.clearRect(0, 0, canvasWidth, canvasHeight);
                
                // then whack any remaining obvious garbage left
                eventHolder.unbind();
                placeholder.children().not([canvas, overlay]).remove();
            }

            // save in case we get replotted
            placeholder.data("plot", plot);
        }

        function bindEvents() {
            // bind events
            if (options.grid.hoverable) {
                eventHolder.mousemove(onMouseMove);
                eventHolder.mouseleave(onMouseLeave);
            }

            if (options.grid.clickable)
                eventHolder.click(onClick);

            executeHooks(hooks.bindEvents, [eventHolder]);
        }

        function shutdown() {
            if (redrawTimeout)
                clearTimeout(redrawTimeout);
            
            eventHolder.unbind("mousemove", onMouseMove);
            eventHolder.unbind("mouseleave", onMouseLeave);
            eventHolder.unbind("click", onClick);
            
            executeHooks(hooks.shutdown, [eventHolder]);
        }

        function setTransformationHelpers(axis) {
            // set helper functions on the axis, assumes plot area
            // has been computed already
            
            function identity(x) { return x; }
            
            var s, m, t = axis.options.transform || identity,
                it = axis.options.inverseTransform;
            
            // precompute how much the axis is scaling a point
            // in canvas space
            if (axis.direction == "x") {
                s = axis.scale = plotWidth / Math.abs(t(axis.max) - t(axis.min));
                m = Math.min(t(axis.max), t(axis.min));
            }
            else {
                s = axis.scale = plotHeight / Math.abs(t(axis.max) - t(axis.min));
                s = -s;
                m = Math.max(t(axis.max), t(axis.min));
            }

            // data point to canvas coordinate
            if (t == identity) // slight optimization
                axis.p2c = function (p) { return (p - m) * s; };
            else
                axis.p2c = function (p) { return (t(p) - m) * s; };
            // canvas coordinate to data point
            if (!it)
                axis.c2p = function (c) { return m + c / s; };
            else
                axis.c2p = function (c) { return it(m + c / s); };
        }

        function measureTickLabels(axis) {
            var opts = axis.options, i, ticks = axis.ticks || [], labels = [],
                l, w = opts.labelWidth, h = opts.labelHeight, dummyDiv;

            function makeDummyDiv(labels, width) {
                return $('<div style="position:absolute;top:-10000px;' + width + 'font-size:smaller">' +
                         '<div class="' + axis.direction + 'Axis ' + axis.direction + axis.n + 'Axis">'
                         + labels.join("") + '</div></div>')
                    .appendTo(placeholder);
            }
            
            if (axis.direction == "x") {
                // to avoid measuring the widths of the labels (it's slow), we
                // construct fixed-size boxes and put the labels inside
                // them, we don't need the exact figures and the
                // fixed-size box content is easy to center
                if (w == null)
                    w = Math.floor(canvasWidth / (ticks.length > 0 ? ticks.length : 1));

                // measure x label heights
                if (h == null) {
                    labels = [];
                    for (i = 0; i < ticks.length; ++i) {
                        l = ticks[i].label;
                        if (l)
                            labels.push('<div class="tickLabel" style="float:left;width:' + w + 'px">' + l + '</div>');
                    }

                    if (labels.length > 0) {
                        // stick them all in the same div and measure
                        // collective height
                        labels.push('<div style="clear:left"></div>');
                        dummyDiv = makeDummyDiv(labels, "width:10000px;");
                        h = dummyDiv.height();
                        dummyDiv.remove();
                    }
                }
            }
            else if (w == null || h == null) {
                // calculate y label dimensions
                for (i = 0; i < ticks.length; ++i) {
                    l = ticks[i].label;
                    if (l)
                        labels.push('<div class="tickLabel">' + l + '</div>');
                }
                
                if (labels.length > 0) {
                    dummyDiv = makeDummyDiv(labels, "");
                    if (w == null)
                        w = dummyDiv.children().width();
                    if (h == null)
                        h = dummyDiv.find("div.tickLabel").height();
                    dummyDiv.remove();
                }
            }

            if (w == null)
                w = 0;
            if (h == null)
                h = 0;

            axis.labelWidth = w;
            axis.labelHeight = h;
        }

        function allocateAxisBoxFirstPhase(axis) {
            // find the bounding box of the axis by looking at label
            // widths/heights and ticks, make room by diminishing the
            // plotOffset

            var lw = axis.labelWidth,
                lh = axis.labelHeight,
                pos = axis.options.position,
                tickLength = axis.options.tickLength,
                axismargin = options.grid.axisMargin,
                padding = options.grid.labelMargin,
                all = axis.direction == "x" ? xaxes : yaxes,
                index;

            // determine axis margin
            var samePosition = $.grep(all, function (a) {
                return a && a.options.position == pos && a.reserveSpace;
            });
            if ($.inArray(axis, samePosition) == samePosition.length - 1)
                axismargin = 0; // outermost

            // determine tick length - if we're innermost, we can use "full"
            if (tickLength == null)
                tickLength = "full";

            var sameDirection = $.grep(all, function (a) {
                return a && a.reserveSpace;
            });

            var innermost = $.inArray(axis, sameDirection) == 0;
            if (!innermost && tickLength == "full")
                tickLength = 5;
                
            if (!isNaN(+tickLength))
                padding += +tickLength;

            // compute box
            if (axis.direction == "x") {
                lh += padding;
                
                if (pos == "bottom") {
                    plotOffset.bottom += lh + axismargin;
                    axis.box = { top: canvasHeight - plotOffset.bottom, height: lh };
                }
                else {
                    axis.box = { top: plotOffset.top + axismargin, height: lh };
                    plotOffset.top += lh + axismargin;
                }
            }
            else {
                lw += padding;
                
                if (pos == "left") {
                    axis.box = { left: plotOffset.left + axismargin, width: lw };
                    plotOffset.left += lw + axismargin;
                }
                else {
                    plotOffset.right += lw + axismargin;
                    axis.box = { left: canvasWidth - plotOffset.right, width: lw };
                }
            }

             // save for future reference
            axis.position = pos;
            axis.tickLength = tickLength;
            axis.box.padding = padding;
            axis.innermost = innermost;
        }

        function allocateAxisBoxSecondPhase(axis) {
            // set remaining bounding box coordinates
            if (axis.direction == "x") {
                axis.box.left = plotOffset.left;
                axis.box.width = plotWidth;
            }
            else {
                axis.box.top = plotOffset.top;
                axis.box.height = plotHeight;
            }
        }
        
        function setupGrid() {
            var i, axes = allAxes();

            // first calculate the plot and axis box dimensions

            $.each(axes, function (_, axis) {
                axis.show = axis.options.show;
                if (axis.show == null)
                    axis.show = axis.used; // by default an axis is visible if it's got data
                
                axis.reserveSpace = axis.show || axis.options.reserveSpace;

                setRange(axis);
            });

            allocatedAxes = $.grep(axes, function (axis) { return axis.reserveSpace; });

            plotOffset.left = plotOffset.right = plotOffset.top = plotOffset.bottom = 0;
            if (options.grid.show) {
                $.each(allocatedAxes, function (_, axis) {
                    // make the ticks
                    setupTickGeneration(axis);
                    setTicks(axis);
                    snapRangeToTicks(axis, axis.ticks);

                    // find labelWidth/Height for axis
                    measureTickLabels(axis);
                });

                // with all dimensions in house, we can compute the
                // axis boxes, start from the outside (reverse order)
                for (i = allocatedAxes.length - 1; i >= 0; --i)
                    allocateAxisBoxFirstPhase(allocatedAxes[i]);

                // make sure we've got enough space for things that
                // might stick out
                var minMargin = options.grid.minBorderMargin;
                if (minMargin == null) {
                    minMargin = 0;
                    for (i = 0; i < series.length; ++i)
                        minMargin = Math.max(minMargin, series[i].points.radius + series[i].points.lineWidth/2);
                }
                    
                for (var a in plotOffset) {
                    plotOffset[a] += options.grid.borderWidth;
                    plotOffset[a] = Math.max(minMargin, plotOffset[a]);
                }
            }
            
            plotWidth = canvasWidth - plotOffset.left - plotOffset.right;
            plotHeight = canvasHeight - plotOffset.bottom - plotOffset.top;

            // now we got the proper plotWidth/Height, we can compute the scaling
            $.each(axes, function (_, axis) {
                setTransformationHelpers(axis);
            });

            if (options.grid.show) {
                $.each(allocatedAxes, function (_, axis) {
                    allocateAxisBoxSecondPhase(axis);
                });

                insertAxisLabels();
            }
            
            insertLegend();
        }
        
        function setRange(axis) {
            var opts = axis.options,
                min = +(opts.min != null ? opts.min : axis.datamin),
                max = +(opts.max != null ? opts.max : axis.datamax),
                delta = max - min;

            if (delta == 0.0) {
                // degenerate case
                var widen = max == 0 ? 1 : 0.01;

                if (opts.min == null)
                    min -= widen;
                // always widen max if we couldn't widen min to ensure we
                // don't fall into min == max which doesn't work
                if (opts.max == null || opts.min != null)
                    max += widen;
            }
            else {
                // consider autoscaling
                var margin = opts.autoscaleMargin;
                if (margin != null) {
                    if (opts.min == null) {
                        min -= delta * margin;
                        // make sure we don't go below zero if all values
                        // are positive
                        if (min < 0 && axis.datamin != null && axis.datamin >= 0)
                            min = 0;
                    }
                    if (opts.max == null) {
                        max += delta * margin;
                        if (max > 0 && axis.datamax != null && axis.datamax <= 0)
                            max = 0;
                    }
                }
            }
            axis.min = min;
            axis.max = max;
        }

        function setupTickGeneration(axis) {
            var opts = axis.options;
                
            // estimate number of ticks
            var noTicks;
            if (typeof opts.ticks == "number" && opts.ticks > 0)
                noTicks = opts.ticks;
            else
                // heuristic based on the model a*sqrt(x) fitted to
                // some data points that seemed reasonable
                noTicks = 0.3 * Math.sqrt(axis.direction == "x" ? canvasWidth : canvasHeight);

            var delta = (axis.max - axis.min) / noTicks,
                size, generator, unit, formatter, i, magn, norm;

            if (opts.mode == "time") {
                // pretty handling of time
                
                // map of app. size of time units in milliseconds
                var timeUnitSize = {
                    "second": 1000,
                    "minute": 60 * 1000,
                    "hour": 60 * 60 * 1000,
                    "day": 24 * 60 * 60 * 1000,
                    "month": 30 * 24 * 60 * 60 * 1000,
                    "year": 365.2425 * 24 * 60 * 60 * 1000
                };


                // the allowed tick sizes, after 1 year we use
                // an integer algorithm
                var spec = [
                    [1, "second"], [2, "second"], [5, "second"], [10, "second"],
                    [30, "second"], 
                    [1, "minute"], [2, "minute"], [5, "minute"], [10, "minute"],
                    [30, "minute"], 
                    [1, "hour"], [2, "hour"], [4, "hour"],
                    [8, "hour"], [12, "hour"],
                    [1, "day"], [2, "day"], [3, "day"],
                    [0.25, "month"], [0.5, "month"], [1, "month"],
                    [2, "month"], [3, "month"], [6, "month"],
                    [1, "year"]
                ];

                var minSize = 0;
                if (opts.minTickSize != null) {
                    if (typeof opts.tickSize == "number")
                        minSize = opts.tickSize;
                    else
                        minSize = opts.minTickSize[0] * timeUnitSize[opts.minTickSize[1]];
                }

                for (var i = 0; i < spec.length - 1; ++i)
                    if (delta < (spec[i][0] * timeUnitSize[spec[i][1]]
                                 + spec[i + 1][0] * timeUnitSize[spec[i + 1][1]]) / 2
                       && spec[i][0] * timeUnitSize[spec[i][1]] >= minSize)
                        break;
                size = spec[i][0];
                unit = spec[i][1];
                
                // special-case the possibility of several years
                if (unit == "year") {
                    magn = Math.pow(10, Math.floor(Math.log(delta / timeUnitSize.year) / Math.LN10));
                    norm = (delta / timeUnitSize.year) / magn;
                    if (norm < 1.5)
                        size = 1;
                    else if (norm < 3)
                        size = 2;
                    else if (norm < 7.5)
                        size = 5;
                    else
                        size = 10;

                    size *= magn;
                }

                axis.tickSize = opts.tickSize || [size, unit];
                
                generator = function(axis) {
                    var ticks = [],
                        tickSize = axis.tickSize[0], unit = axis.tickSize[1],
                        d = new Date(axis.min);
                    
                    var step = tickSize * timeUnitSize[unit];

                    if (unit == "second")
                        d.setUTCSeconds(floorInBase(d.getUTCSeconds(), tickSize));
                    if (unit == "minute")
                        d.setUTCMinutes(floorInBase(d.getUTCMinutes(), tickSize));
                    if (unit == "hour")
                        d.setUTCHours(floorInBase(d.getUTCHours(), tickSize));
                    if (unit == "month")
                        d.setUTCMonth(floorInBase(d.getUTCMonth(), tickSize));
                    if (unit == "year")
                        d.setUTCFullYear(floorInBase(d.getUTCFullYear(), tickSize));
                    
                    // reset smaller components
                    d.setUTCMilliseconds(0);
                    if (step >= timeUnitSize.minute)
                        d.setUTCSeconds(0);
                    if (step >= timeUnitSize.hour)
                        d.setUTCMinutes(0);
                    if (step >= timeUnitSize.day)
                        d.setUTCHours(0);
                    if (step >= timeUnitSize.day * 4)
                        d.setUTCDate(1);
                    if (step >= timeUnitSize.year)
                        d.setUTCMonth(0);


                    var carry = 0, v = Number.NaN, prev;
                    do {
                        prev = v;
                        v = d.getTime();
                        ticks.push(v);
                        if (unit == "month") {
                            if (tickSize < 1) {
                                // a bit complicated - we'll divide the month
                                // up but we need to take care of fractions
                                // so we don't end up in the middle of a day
                                d.setUTCDate(1);
                                var start = d.getTime();
                                d.setUTCMonth(d.getUTCMonth() + 1);
                                var end = d.getTime();
                                d.setTime(v + carry * timeUnitSize.hour + (end - start) * tickSize);
                                carry = d.getUTCHours();
                                d.setUTCHours(0);
                            }
                            else
                                d.setUTCMonth(d.getUTCMonth() + tickSize);
                        }
                        else if (unit == "year") {
                            d.setUTCFullYear(d.getUTCFullYear() + tickSize);
                        }
                        else
                            d.setTime(v + step);
                    } while (v < axis.max && v != prev);

                    return ticks;
                };

                formatter = function (v, axis) {
                    var d = new Date(v);

                    // first check global format
                    if (opts.timeformat != null)
                        return $.plot.formatDate(d, opts.timeformat, opts.monthNames);
                    
                    var t = axis.tickSize[0] * timeUnitSize[axis.tickSize[1]];
                    var span = axis.max - axis.min;
                    var suffix = (opts.twelveHourClock) ? " %p" : "";
                    
                    if (t < timeUnitSize.minute)
                        fmt = "%h:%M:%S" + suffix;
                    else if (t < timeUnitSize.day) {
                        if (span < 2 * timeUnitSize.day)
                            fmt = "%h:%M" + suffix;
                        else
                            fmt = "%b %d %h:%M" + suffix;
                    }
                    else if (t < timeUnitSize.month)
                        fmt = "%b %d";
                    else if (t < timeUnitSize.year) {
                        if (span < timeUnitSize.year)
                            fmt = "%b";
                        else
                            fmt = "%b %y";
                    }
                    else
                        fmt = "%y";
                    
                    return $.plot.formatDate(d, fmt, opts.monthNames);
                };
            }
            else {
                // pretty rounding of base-10 numbers
                var maxDec = opts.tickDecimals;
                var dec = -Math.floor(Math.log(delta) / Math.LN10);
                if (maxDec != null && dec > maxDec)
                    dec = maxDec;

                magn = Math.pow(10, -dec);
                norm = delta / magn; // norm is between 1.0 and 10.0
                
                if (norm < 1.5)
                    size = 1;
                else if (norm < 3) {
                    size = 2;
                    // special case for 2.5, requires an extra decimal
                    if (norm > 2.25 && (maxDec == null || dec + 1 <= maxDec)) {
                        size = 2.5;
                        ++dec;
                    }
                }
                else if (norm < 7.5)
                    size = 5;
                else
                    size = 10;

                size *= magn;
                
                if (opts.minTickSize != null && size < opts.minTickSize)
                    size = opts.minTickSize;

                axis.tickDecimals = Math.max(0, maxDec != null ? maxDec : dec);
                axis.tickSize = opts.tickSize || size;

                generator = function (axis) {
                    var ticks = [];

                    // spew out all possible ticks
                    var start = floorInBase(axis.min, axis.tickSize),
                        i = 0, v = Number.NaN, prev;
                    do {
                        prev = v;
                        v = start + i * axis.tickSize;
                        ticks.push(v);
                        ++i;
                    } while (v < axis.max && v != prev);
                    return ticks;
                };

                formatter = function (v, axis) {
                    return v.toFixed(axis.tickDecimals);
                };
            }

            if (opts.alignTicksWithAxis != null) {
                var otherAxis = (axis.direction == "x" ? xaxes : yaxes)[opts.alignTicksWithAxis - 1];
                if (otherAxis && otherAxis.used && otherAxis != axis) {
                    // consider snapping min/max to outermost nice ticks
                    var niceTicks = generator(axis);
                    if (niceTicks.length > 0) {
                        if (opts.min == null)
                            axis.min = Math.min(axis.min, niceTicks[0]);
                        if (opts.max == null && niceTicks.length > 1)
                            axis.max = Math.max(axis.max, niceTicks[niceTicks.length - 1]);
                    }
                    
                    generator = function (axis) {
                        // copy ticks, scaled to this axis
                        var ticks = [], v, i;
                        for (i = 0; i < otherAxis.ticks.length; ++i) {
                            v = (otherAxis.ticks[i].v - otherAxis.min) / (otherAxis.max - otherAxis.min);
                            v = axis.min + v * (axis.max - axis.min);
                            ticks.push(v);
                        }
                        return ticks;
                    };
                    
                    // we might need an extra decimal since forced
                    // ticks don't necessarily fit naturally
                    if (axis.mode != "time" && opts.tickDecimals == null) {
                        var extraDec = Math.max(0, -Math.floor(Math.log(delta) / Math.LN10) + 1),
                            ts = generator(axis);

                        // only proceed if the tick interval rounded
                        // with an extra decimal doesn't give us a
                        // zero at end
                        if (!(ts.length > 1 && /\..*0$/.test((ts[1] - ts[0]).toFixed(extraDec))))
                            axis.tickDecimals = extraDec;
                    }
                }
            }

            axis.tickGenerator = generator;
            if ($.isFunction(opts.tickFormatter))
                axis.tickFormatter = function (v, axis) { return "" + opts.tickFormatter(v, axis); };
            else
                axis.tickFormatter = formatter;
        }
        
        function setTicks(axis) {
            var oticks = axis.options.ticks, ticks = [];
            if (oticks == null || (typeof oticks == "number" && oticks > 0))
                ticks = axis.tickGenerator(axis);
            else if (oticks) {
                if ($.isFunction(oticks))
                    // generate the ticks
                    ticks = oticks({ min: axis.min, max: axis.max });
                else
                    ticks = oticks;
            }

            // clean up/labelify the supplied ticks, copy them over
            var i, v;
            axis.ticks = [];
            for (i = 0; i < ticks.length; ++i) {
                var label = null;
                var t = ticks[i];
                if (typeof t == "object") {
                    v = +t[0];
                    if (t.length > 1)
                        label = t[1];
                }
                else
                    v = +t;
                if (label == null)
                    label = axis.tickFormatter(v, axis);
                if (!isNaN(v))
                    axis.ticks.push({ v: v, label: label });
            }
        }

        function snapRangeToTicks(axis, ticks) {
            if (axis.options.autoscaleMargin && ticks.length > 0) {
                // snap to ticks
                if (axis.options.min == null)
                    axis.min = Math.min(axis.min, ticks[0].v);
                if (axis.options.max == null && ticks.length > 1)
                    axis.max = Math.max(axis.max, ticks[ticks.length - 1].v);
            }
        }
      
        function draw() {
            ctx.clearRect(0, 0, canvasWidth, canvasHeight);

            var grid = options.grid;

            // draw background, if any
            if (grid.show && grid.backgroundColor)
                drawBackground();
            
            if (grid.show && !grid.aboveData)
                drawGrid();

            for (var i = 0; i < series.length; ++i) {
                executeHooks(hooks.drawSeries, [ctx, series[i]]);
                drawSeries(series[i]);
            }

            executeHooks(hooks.draw, [ctx]);
            
            if (grid.show && grid.aboveData)
                drawGrid();
        }

        function extractRange(ranges, coord) {
            var axis, from, to, key, axes = allAxes();

            for (i = 0; i < axes.length; ++i) {
                axis = axes[i];
                if (axis.direction == coord) {
                    key = coord + axis.n + "axis";
                    if (!ranges[key] && axis.n == 1)
                        key = coord + "axis"; // support x1axis as xaxis
                    if (ranges[key]) {
                        from = ranges[key].from;
                        to = ranges[key].to;
                        break;
                    }
                }
            }

            // backwards-compat stuff - to be removed in future
            if (!ranges[key]) {
                axis = coord == "x" ? xaxes[0] : yaxes[0];
                from = ranges[coord + "1"];
                to = ranges[coord + "2"];
            }

            // auto-reverse as an added bonus
            if (from != null && to != null && from > to) {
                var tmp = from;
                from = to;
                to = tmp;
            }
            
            return { from: from, to: to, axis: axis };
        }
        
        function drawBackground() {
            ctx.save();
            ctx.translate(plotOffset.left, plotOffset.top);

            ctx.fillStyle = getColorOrGradient(options.grid.backgroundColor, plotHeight, 0, "rgba(255, 255, 255, 0)");
            ctx.fillRect(0, 0, plotWidth, plotHeight);
            ctx.restore();
        }

        function drawGrid() {
            var i;
            
            ctx.save();
            ctx.translate(plotOffset.left, plotOffset.top);

            // draw markings
            var markings = options.grid.markings;
            if (markings) {
                if ($.isFunction(markings)) {
                    var axes = plot.getAxes();
                    // xmin etc. is backwards compatibility, to be
                    // removed in the future
                    axes.xmin = axes.xaxis.min;
                    axes.xmax = axes.xaxis.max;
                    axes.ymin = axes.yaxis.min;
                    axes.ymax = axes.yaxis.max;
                    
                    markings = markings(axes);
                }

                for (i = 0; i < markings.length; ++i) {
                    var m = markings[i],
                        xrange = extractRange(m, "x"),
                        yrange = extractRange(m, "y");

                    // fill in missing
                    if (xrange.from == null)
                        xrange.from = xrange.axis.min;
                    if (xrange.to == null)
                        xrange.to = xrange.axis.max;
                    if (yrange.from == null)
                        yrange.from = yrange.axis.min;
                    if (yrange.to == null)
                        yrange.to = yrange.axis.max;

                    // clip
                    if (xrange.to < xrange.axis.min || xrange.from > xrange.axis.max ||
                        yrange.to < yrange.axis.min || yrange.from > yrange.axis.max)
                        continue;

                    xrange.from = Math.max(xrange.from, xrange.axis.min);
                    xrange.to = Math.min(xrange.to, xrange.axis.max);
                    yrange.from = Math.max(yrange.from, yrange.axis.min);
                    yrange.to = Math.min(yrange.to, yrange.axis.max);

                    if (xrange.from == xrange.to && yrange.from == yrange.to)
                        continue;

                    // then draw
                    xrange.from = xrange.axis.p2c(xrange.from);
                    xrange.to = xrange.axis.p2c(xrange.to);
                    yrange.from = yrange.axis.p2c(yrange.from);
                    yrange.to = yrange.axis.p2c(yrange.to);
                    
                    if (xrange.from == xrange.to || yrange.from == yrange.to) {
                        // draw line
                        ctx.beginPath();
                        ctx.strokeStyle = m.color || options.grid.markingsColor;
                        ctx.lineWidth = m.lineWidth || options.grid.markingsLineWidth;
                        ctx.moveTo(xrange.from, yrange.from);
                        ctx.lineTo(xrange.to, yrange.to);
                        ctx.stroke();
                    }
                    else {
                        // fill area
                        ctx.fillStyle = m.color || options.grid.markingsColor;
                        ctx.fillRect(xrange.from, yrange.to,
                                     xrange.to - xrange.from,
                                     yrange.from - yrange.to);
                    }
                }
            }
            
            // draw the ticks
            var axes = allAxes(), bw = options.grid.borderWidth;

            for (var j = 0; j < axes.length; ++j) {
                var axis = axes[j], box = axis.box,
                    t = axis.tickLength, x, y, xoff, yoff;
                if (!axis.show || axis.ticks.length == 0)
                    continue;
                
                ctx.strokeStyle = axis.options.tickColor || $.color.parse(axis.options.color).scale('a', 0.22).toString();
                ctx.lineWidth = 1;

                // find the edges
                if (axis.direction == "x") {
                    x = 0;
                    if (t == "full")
                        y = (axis.position == "top" ? 0 : plotHeight);
                    else
                        y = box.top - plotOffset.top + (axis.position == "top" ? box.height : 0);
                }
                else {
                    y = 0;
                    if (t == "full")
                        x = (axis.position == "left" ? 0 : plotWidth);
                    else
                        x = box.left - plotOffset.left + (axis.position == "left" ? box.width : 0);
                }
                
                // draw tick bar
                if (!axis.innermost) {
                    ctx.beginPath();
                    xoff = yoff = 0;
                    if (axis.direction == "x")
                        xoff = plotWidth;
                    else
                        yoff = plotHeight;
                    
                    if (ctx.lineWidth == 1) {
                        x = Math.floor(x) + 0.5;
                        y = Math.floor(y) + 0.5;
                    }

                    ctx.moveTo(x, y);
                    ctx.lineTo(x + xoff, y + yoff);
                    ctx.stroke();
                }

                // draw ticks
                ctx.beginPath();
                for (i = 0; i < axis.ticks.length; ++i) {
                    var v = axis.ticks[i].v;
                    
                    xoff = yoff = 0;

                    if (v < axis.min || v > axis.max
                        // skip those lying on the axes if we got a border
                        || (t == "full" && bw > 0
                            && (v == axis.min || v == axis.max)))
                        continue;

                    if (axis.direction == "x") {
                        x = axis.p2c(v);
                        yoff = t == "full" ? -plotHeight : t;
                        
                        if (axis.position == "top")
                            yoff = -yoff;
                    }
                    else {
                        y = axis.p2c(v);
                        xoff = t == "full" ? -plotWidth : t;
                        
                        if (axis.position == "left")
                            xoff = -xoff;
                    }

                    if (ctx.lineWidth == 1) {
                        if (axis.direction == "x")
                            x = Math.floor(x) + 0.5;
                        else
                            y = Math.floor(y) + 0.5;
                    }

                    ctx.moveTo(x, y);
                    ctx.lineTo(x + xoff, y + yoff);
                }
                
                ctx.stroke();
            }
            
            
            // draw border
            if (bw) {
                ctx.lineWidth = bw;
                ctx.strokeStyle = options.grid.borderColor;
                ctx.strokeRect(-bw/2, -bw/2, plotWidth + bw, plotHeight + bw);
            }

            ctx.restore();
        }

        function insertAxisLabels() {
            placeholder.find(".tickLabels").remove();
            
            var html = ['<div class="tickLabels" style="font-size:smaller">'];

            var axes = allAxes();
            for (var j = 0; j < axes.length; ++j) {
                var axis = axes[j], box = axis.box;
                if (!axis.show)
                    continue;
                //debug: html.push('<div style="position:absolute;opacity:0.10;background-color:red;left:' + box.left + 'px;top:' + box.top + 'px;width:' + box.width +  'px;height:' + box.height + 'px"></div>')
                html.push('<div class="' + axis.direction + 'Axis ' + axis.direction + axis.n + 'Axis" style="color:' + axis.options.color + '">');
                for (var i = 0; i < axis.ticks.length; ++i) {
                    var tick = axis.ticks[i];
                    if (!tick.label || tick.v < axis.min || tick.v > axis.max)
                        continue;

                    var pos = {}, align;
                    
                    if (axis.direction == "x") {
                        align = "center";
                        pos.left = Math.round(plotOffset.left + axis.p2c(tick.v) - axis.labelWidth/2);
                        if (axis.position == "bottom")
                            pos.top = box.top + box.padding;
                        else
                            pos.bottom = canvasHeight - (box.top + box.height - box.padding);
                    }
                    else {
                        pos.top = Math.round(plotOffset.top + axis.p2c(tick.v) - axis.labelHeight/2);
                        if (axis.position == "left") {
                            pos.right = canvasWidth - (box.left + box.width - box.padding)
                            align = "right";
                        }
                        else {
                            pos.left = box.left + box.padding;
                            align = "left";
                        }
                    }

                    pos.width = axis.labelWidth;

                    var style = ["position:absolute", "text-align:" + align ];
                    for (var a in pos)
                        style.push(a + ":" + pos[a] + "px")
                    
                    html.push('<div class="tickLabel" style="' + style.join(';') + '">' + tick.label + '</div>');
                }
                html.push('</div>');
            }

            html.push('</div>');

            placeholder.append(html.join(""));
        }

        function drawSeries(series) {
            if (series.lines.show)
                drawSeriesLines(series);
            if (series.bars.show)
                drawSeriesBars(series);
            if (series.points.show)
                drawSeriesPoints(series);
        }
        
        function drawSeriesLines(series) {
            function plotLine(datapoints, xoffset, yoffset, axisx, axisy) {
                var points = datapoints.points,
                    ps = datapoints.pointsize,
                    prevx = null, prevy = null;
                
                ctx.beginPath();
                for (var i = ps; i < points.length; i += ps) {
                    var x1 = points[i - ps], y1 = points[i - ps + 1],
                        x2 = points[i], y2 = points[i + 1];
                    
                    if (x1 == null || x2 == null)
                        continue;

                    // clip with ymin
                    if (y1 <= y2 && y1 < axisy.min) {
                        if (y2 < axisy.min)
                            continue;   // line segment is outside
                        // compute new intersection point
                        x1 = (axisy.min - y1) / (y2 - y1) * (x2 - x1) + x1;
                        y1 = axisy.min;
                    }
                    else if (y2 <= y1 && y2 < axisy.min) {
                        if (y1 < axisy.min)
                            continue;
                        x2 = (axisy.min - y1) / (y2 - y1) * (x2 - x1) + x1;
                        y2 = axisy.min;
                    }

                    // clip with ymax
                    if (y1 >= y2 && y1 > axisy.max) {
                        if (y2 > axisy.max)
                            continue;
                        x1 = (axisy.max - y1) / (y2 - y1) * (x2 - x1) + x1;
                        y1 = axisy.max;
                    }
                    else if (y2 >= y1 && y2 > axisy.max) {
                        if (y1 > axisy.max)
                            continue;
                        x2 = (axisy.max - y1) / (y2 - y1) * (x2 - x1) + x1;
                        y2 = axisy.max;
                    }

                    // clip with xmin
                    if (x1 <= x2 && x1 < axisx.min) {
                        if (x2 < axisx.min)
                            continue;
                        y1 = (axisx.min - x1) / (x2 - x1) * (y2 - y1) + y1;
                        x1 = axisx.min;
                    }
                    else if (x2 <= x1 && x2 < axisx.min) {
                        if (x1 < axisx.min)
                            continue;
                        y2 = (axisx.min - x1) / (x2 - x1) * (y2 - y1) + y1;
                        x2 = axisx.min;
                    }

                    // clip with xmax
                    if (x1 >= x2 && x1 > axisx.max) {
                        if (x2 > axisx.max)
                            continue;
                        y1 = (axisx.max - x1) / (x2 - x1) * (y2 - y1) + y1;
                        x1 = axisx.max;
                    }
                    else if (x2 >= x1 && x2 > axisx.max) {
                        if (x1 > axisx.max)
                            continue;
                        y2 = (axisx.max - x1) / (x2 - x1) * (y2 - y1) + y1;
                        x2 = axisx.max;
                    }

                    if (x1 != prevx || y1 != prevy)
                        ctx.moveTo(axisx.p2c(x1) + xoffset, axisy.p2c(y1) + yoffset);
                    
                    prevx = x2;
                    prevy = y2;
                    ctx.lineTo(axisx.p2c(x2) + xoffset, axisy.p2c(y2) + yoffset);
                }
                ctx.stroke();
            }

            function plotLineArea(datapoints, axisx, axisy) {
                var points = datapoints.points,
                    ps = datapoints.pointsize,
                    bottom = Math.min(Math.max(0, axisy.min), axisy.max),
                    i = 0, top, areaOpen = false,
                    ypos = 1, segmentStart = 0, segmentEnd = 0;

                // we process each segment in two turns, first forward
                // direction to sketch out top, then once we hit the
                // end we go backwards to sketch the bottom
                while (true) {
                    if (ps > 0 && i > points.length + ps)
                        break;

                    i += ps; // ps is negative if going backwards

                    var x1 = points[i - ps],
                        y1 = points[i - ps + ypos],
                        x2 = points[i], y2 = points[i + ypos];

                    if (areaOpen) {
                        if (ps > 0 && x1 != null && x2 == null) {
                            // at turning point
                            segmentEnd = i;
                            ps = -ps;
                            ypos = 2;
                            continue;
                        }

                        if (ps < 0 && i == segmentStart + ps) {
                            // done with the reverse sweep
                            ctx.fill();
                            areaOpen = false;
                            ps = -ps;
                            ypos = 1;
                            i = segmentStart = segmentEnd + ps;
                            continue;
                        }
                    }

                    if (x1 == null || x2 == null)
                        continue;

                    // clip x values
                    
                    // clip with xmin
                    if (x1 <= x2 && x1 < axisx.min) {
                        if (x2 < axisx.min)
                            continue;
                        y1 = (axisx.min - x1) / (x2 - x1) * (y2 - y1) + y1;
                        x1 = axisx.min;
                    }
                    else if (x2 <= x1 && x2 < axisx.min) {
                        if (x1 < axisx.min)
                            continue;
                        y2 = (axisx.min - x1) / (x2 - x1) * (y2 - y1) + y1;
                        x2 = axisx.min;
                    }

                    // clip with xmax
                    if (x1 >= x2 && x1 > axisx.max) {
                        if (x2 > axisx.max)
                            continue;
                        y1 = (axisx.max - x1) / (x2 - x1) * (y2 - y1) + y1;
                        x1 = axisx.max;
                    }
                    else if (x2 >= x1 && x2 > axisx.max) {
                        if (x1 > axisx.max)
                            continue;
                        y2 = (axisx.max - x1) / (x2 - x1) * (y2 - y1) + y1;
                        x2 = axisx.max;
                    }

                    if (!areaOpen) {
                        // open area
                        ctx.beginPath();
                        ctx.moveTo(axisx.p2c(x1), axisy.p2c(bottom));
                        areaOpen = true;
                    }
                    
                    // now first check the case where both is outside
                    if (y1 >= axisy.max && y2 >= axisy.max) {
                        ctx.lineTo(axisx.p2c(x1), axisy.p2c(axisy.max));
                        ctx.lineTo(axisx.p2c(x2), axisy.p2c(axisy.max));
                        continue;
                    }
                    else if (y1 <= axisy.min && y2 <= axisy.min) {
                        ctx.lineTo(axisx.p2c(x1), axisy.p2c(axisy.min));
                        ctx.lineTo(axisx.p2c(x2), axisy.p2c(axisy.min));
                        continue;
                    }
                    
                    // else it's a bit more complicated, there might
                    // be a flat maxed out rectangle first, then a
                    // triangular cutout or reverse; to find these
                    // keep track of the current x values
                    var x1old = x1, x2old = x2;

                    // clip the y values, without shortcutting, we
                    // go through all cases in turn
                    
                    // clip with ymin
                    if (y1 <= y2 && y1 < axisy.min && y2 >= axisy.min) {
                        x1 = (axisy.min - y1) / (y2 - y1) * (x2 - x1) + x1;
                        y1 = axisy.min;
                    }
                    else if (y2 <= y1 && y2 < axisy.min && y1 >= axisy.min) {
                        x2 = (axisy.min - y1) / (y2 - y1) * (x2 - x1) + x1;
                        y2 = axisy.min;
                    }

                    // clip with ymax
                    if (y1 >= y2 && y1 > axisy.max && y2 <= axisy.max) {
                        x1 = (axisy.max - y1) / (y2 - y1) * (x2 - x1) + x1;
                        y1 = axisy.max;
                    }
                    else if (y2 >= y1 && y2 > axisy.max && y1 <= axisy.max) {
                        x2 = (axisy.max - y1) / (y2 - y1) * (x2 - x1) + x1;
                        y2 = axisy.max;
                    }

                    // if the x value was changed we got a rectangle
                    // to fill
                    if (x1 != x1old) {
                        ctx.lineTo(axisx.p2c(x1old), axisy.p2c(y1));
                        // it goes to (x1, y1), but we fill that below
                    }
                    
                    // fill triangular section, this sometimes result
                    // in redundant points if (x1, y1) hasn't changed
                    // from previous line to, but we just ignore that
                    ctx.lineTo(axisx.p2c(x1), axisy.p2c(y1));
                    ctx.lineTo(axisx.p2c(x2), axisy.p2c(y2));

                    // fill the other rectangle if it's there
                    if (x2 != x2old) {
                        ctx.lineTo(axisx.p2c(x2), axisy.p2c(y2));
                        ctx.lineTo(axisx.p2c(x2old), axisy.p2c(y2));
                    }
                }
            }

            ctx.save();
            ctx.translate(plotOffset.left, plotOffset.top);
            ctx.lineJoin = "round";

            var lw = series.lines.lineWidth,
                sw = series.shadowSize;
            // FIXME: consider another form of shadow when filling is turned on
            if (lw > 0 && sw > 0) {
                // draw shadow as a thick and thin line with transparency
                ctx.lineWidth = sw;
                ctx.strokeStyle = "rgba(0,0,0,0.1)";
                // position shadow at angle from the mid of line
                var angle = Math.PI/18;
                plotLine(series.datapoints, Math.sin(angle) * (lw/2 + sw/2), Math.cos(angle) * (lw/2 + sw/2), series.xaxis, series.yaxis);
                ctx.lineWidth = sw/2;
                plotLine(series.datapoints, Math.sin(angle) * (lw/2 + sw/4), Math.cos(angle) * (lw/2 + sw/4), series.xaxis, series.yaxis);
            }

            ctx.lineWidth = lw;
            ctx.strokeStyle = series.color;
            var fillStyle = getFillStyle(series.lines, series.color, 0, plotHeight);
            if (fillStyle) {
                ctx.fillStyle = fillStyle;
                plotLineArea(series.datapoints, series.xaxis, series.yaxis);
            }

            if (lw > 0)
                plotLine(series.datapoints, 0, 0, series.xaxis, series.yaxis);
            ctx.restore();
        }

        function drawSeriesPoints(series) {
            function plotPoints(datapoints, radius, fillStyle, offset, shadow, axisx, axisy, symbol) {
                var points = datapoints.points, ps = datapoints.pointsize;

                for (var i = 0; i < points.length; i += ps) {
                    var x = points[i], y = points[i + 1];
                    if (x == null || x < axisx.min || x > axisx.max || y < axisy.min || y > axisy.max)
                        continue;
                    
                    ctx.beginPath();
                    x = axisx.p2c(x);
                    y = axisy.p2c(y) + offset;
                    if (symbol == "circle")
                        ctx.arc(x, y, radius, 0, shadow ? Math.PI : Math.PI * 2, false);
                    else
                        symbol(ctx, x, y, radius, shadow);
                    ctx.closePath();
                    
                    if (fillStyle) {
                        ctx.fillStyle = fillStyle;
                        ctx.fill();
                    }
                    ctx.stroke();
                }
            }
            
            ctx.save();
            ctx.translate(plotOffset.left, plotOffset.top);

            var lw = series.points.lineWidth,
                sw = series.shadowSize,
                radius = series.points.radius,
                symbol = series.points.symbol;
            if (lw > 0 && sw > 0) {
                // draw shadow in two steps
                var w = sw / 2;
                ctx.lineWidth = w;
                ctx.strokeStyle = "rgba(0,0,0,0.1)";
                plotPoints(series.datapoints, radius, null, w + w/2, true,
                           series.xaxis, series.yaxis, symbol);

                ctx.strokeStyle = "rgba(0,0,0,0.2)";
                plotPoints(series.datapoints, radius, null, w/2, true,
                           series.xaxis, series.yaxis, symbol);
            }

            ctx.lineWidth = lw;
            ctx.strokeStyle = series.color;
            plotPoints(series.datapoints, radius,
                       getFillStyle(series.points, series.color), 0, false,
                       series.xaxis, series.yaxis, symbol);
            ctx.restore();
        }

        function drawBar(x, y, b, barLeft, barRight, offset, fillStyleCallback, axisx, axisy, c, horizontal, lineWidth) {
            var left, right, bottom, top,
                drawLeft, drawRight, drawTop, drawBottom,
                tmp;

            // in horizontal mode, we start the bar from the left
            // instead of from the bottom so it appears to be
            // horizontal rather than vertical
            if (horizontal) {
                drawBottom = drawRight = drawTop = true;
                drawLeft = false;
                left = b;
                right = x;
                top = y + barLeft;
                bottom = y + barRight;

                // account for negative bars
                if (right < left) {
                    tmp = right;
                    right = left;
                    left = tmp;
                    drawLeft = true;
                    drawRight = false;
                }
            }
            else {
                drawLeft = drawRight = drawTop = true;
                drawBottom = false;
                left = x + barLeft;
                right = x + barRight;
                bottom = b;
                top = y;

                // account for negative bars
                if (top < bottom) {
                    tmp = top;
                    top = bottom;
                    bottom = tmp;
                    drawBottom = true;
                    drawTop = false;
                }
            }
           
            // clip
            if (right < axisx.min || left > axisx.max ||
                top < axisy.min || bottom > axisy.max)
                return;
            
            if (left < axisx.min) {
                left = axisx.min;
                drawLeft = false;
            }

            if (right > axisx.max) {
                right = axisx.max;
                drawRight = false;
            }

            if (bottom < axisy.min) {
                bottom = axisy.min;
                drawBottom = false;
            }
            
            if (top > axisy.max) {
                top = axisy.max;
                drawTop = false;
            }

            left = axisx.p2c(left);
            bottom = axisy.p2c(bottom);
            right = axisx.p2c(right);
            top = axisy.p2c(top);
            
            // fill the bar
            if (fillStyleCallback) {
                c.beginPath();
                c.moveTo(left, bottom);
                c.lineTo(left, top);
                c.lineTo(right, top);
                c.lineTo(right, bottom);
                c.fillStyle = fillStyleCallback(bottom, top);
                c.fill();
            }

            // draw outline
            if (lineWidth > 0 && (drawLeft || drawRight || drawTop || drawBottom)) {
                c.beginPath();

                // FIXME: inline moveTo is buggy with excanvas
                c.moveTo(left, bottom + offset);
                if (drawLeft)
                    c.lineTo(left, top + offset);
                else
                    c.moveTo(left, top + offset);
                if (drawTop)
                    c.lineTo(right, top + offset);
                else
                    c.moveTo(right, top + offset);
                if (drawRight)
                    c.lineTo(right, bottom + offset);
                else
                    c.moveTo(right, bottom + offset);
                if (drawBottom)
                    c.lineTo(left, bottom + offset);
                else
                    c.moveTo(left, bottom + offset);
                c.stroke();
            }
        }
        
        function drawSeriesBars(series) {
            function plotBars(datapoints, barLeft, barRight, offset, fillStyleCallback, axisx, axisy) {
                var points = datapoints.points, ps = datapoints.pointsize;
                
                for (var i = 0; i < points.length; i += ps) {
                    if (points[i] == null)
                        continue;
                    drawBar(points[i], points[i + 1], points[i + 2], barLeft, barRight, offset, fillStyleCallback, axisx, axisy, ctx, series.bars.horizontal, series.bars.lineWidth);
                }
            }

            ctx.save();
            ctx.translate(plotOffset.left, plotOffset.top);

            // FIXME: figure out a way to add shadows (for instance along the right edge)
            ctx.lineWidth = series.bars.lineWidth;
            ctx.strokeStyle = series.color;
            var barLeft = series.bars.align == "left" ? 0 : -series.bars.barWidth/2;
            var fillStyleCallback = series.bars.fill ? function (bottom, top) { return getFillStyle(series.bars, series.color, bottom, top); } : null;
            plotBars(series.datapoints, barLeft, barLeft + series.bars.barWidth, 0, fillStyleCallback, series.xaxis, series.yaxis);
            ctx.restore();
        }

        function getFillStyle(filloptions, seriesColor, bottom, top) {
            var fill = filloptions.fill;
            if (!fill)
                return null;

            if (filloptions.fillColor)
                return getColorOrGradient(filloptions.fillColor, bottom, top, seriesColor);
            
            var c = $.color.parse(seriesColor);
            c.a = typeof fill == "number" ? fill : 0.4;
            c.normalize();
            return c.toString();
        }
        
        function insertLegend() {
            placeholder.find(".legend").remove();

            if (!options.legend.show)
                return;
            
            var fragments = [], rowStarted = false,
                lf = options.legend.labelFormatter, s, label;
            for (var i = 0; i < series.length; ++i) {
                s = series[i];
                label = s.label;
                if (!label)
                    continue;
                
                if (i % options.legend.noColumns == 0) {
                    if (rowStarted)
                        fragments.push('</tr>');
                    fragments.push('<tr>');
                    rowStarted = true;
                }

                if (lf)
                    label = lf(label, s);
                
                fragments.push(
                    '<td class="legendColorBox"><div style="border:1px solid ' + options.legend.labelBoxBorderColor + ';padding:1px"><div style="width:4px;height:0;border:5px solid ' + s.color + ';overflow:hidden"></div></div></td>' +
                    '<td class="legendLabel">' + label + '</td>');
            }
            if (rowStarted)
                fragments.push('</tr>');
            
            if (fragments.length == 0)
                return;

            var table = '<table style="font-size:smaller;color:' + options.grid.color + '">' + fragments.join("") + '</table>';
            if (options.legend.container != null)
                $(options.legend.container).html(table);
            else {
                var pos = "",
                    p = options.legend.position,
                    m = options.legend.margin;
                if (m[0] == null)
                    m = [m, m];
                if (p.charAt(0) == "n")
                    pos += 'top:' + (m[1] + plotOffset.top) + 'px;';
                else if (p.charAt(0) == "s")
                    pos += 'bottom:' + (m[1] + plotOffset.bottom) + 'px;';
                if (p.charAt(1) == "e")
                    pos += 'right:' + (m[0] + plotOffset.right) + 'px;';
                else if (p.charAt(1) == "w")
                    pos += 'left:' + (m[0] + plotOffset.left) + 'px;';
                var legend = $('<div class="legend">' + table.replace('style="', 'style="position:absolute;' + pos +';') + '</div>').appendTo(placeholder);
                if (options.legend.backgroundOpacity != 0.0) {
                    // put in the transparent background
                    // separately to avoid blended labels and
                    // label boxes
                    var c = options.legend.backgroundColor;
                    if (c == null) {
                        c = options.grid.backgroundColor;
                        if (c && typeof c == "string")
                            c = $.color.parse(c);
                        else
                            c = $.color.extract(legend, 'background-color');
                        c.a = 1;
                        c = c.toString();
                    }
                    var div = legend.children();
                    $('<div style="position:absolute;width:' + div.width() + 'px;height:' + div.height() + 'px;' + pos +'background-color:' + c + ';"> </div>').prependTo(legend).css('opacity', options.legend.backgroundOpacity);
                }
            }
        }


        // interactive features
        
        var highlights = [],
            redrawTimeout = null;
        
        // returns the data item the mouse is over, or null if none is found
        function findNearbyItem(mouseX, mouseY, seriesFilter) {
            var maxDistance = options.grid.mouseActiveRadius,
                smallestDistance = maxDistance * maxDistance + 1,
                item = null, foundPoint = false, i, j;

            for (i = series.length - 1; i >= 0; --i) {
                if (!seriesFilter(series[i]))
                    continue;
                
                var s = series[i],
                    axisx = s.xaxis,
                    axisy = s.yaxis,
                    points = s.datapoints.points,
                    ps = s.datapoints.pointsize,
                    mx = axisx.c2p(mouseX), // precompute some stuff to make the loop faster
                    my = axisy.c2p(mouseY),
                    maxx = maxDistance / axisx.scale,
                    maxy = maxDistance / axisy.scale;

                // with inverse transforms, we can't use the maxx/maxy
                // optimization, sadly
                if (axisx.options.inverseTransform)
                    maxx = Number.MAX_VALUE;
                if (axisy.options.inverseTransform)
                    maxy = Number.MAX_VALUE;
                
                if (s.lines.show || s.points.show) {
                    for (j = 0; j < points.length; j += ps) {
                        var x = points[j], y = points[j + 1];
                        if (x == null)
                            continue;
                        
                        // For points and lines, the cursor must be within a
                        // certain distance to the data point
                        if (x - mx > maxx || x - mx < -maxx ||
                            y - my > maxy || y - my < -maxy)
                            continue;

                        // We have to calculate distances in pixels, not in
                        // data units, because the scales of the axes may be different
                        var dx = Math.abs(axisx.p2c(x) - mouseX),
                            dy = Math.abs(axisy.p2c(y) - mouseY),
                            dist = dx * dx + dy * dy; // we save the sqrt

                        // use <= to ensure last point takes precedence
                        // (last generally means on top of)
                        if (dist < smallestDistance) {
                            smallestDistance = dist;
                            item = [i, j / ps];
                        }
                    }
                }
                    
                if (s.bars.show && !item) { // no other point can be nearby
                    var barLeft = s.bars.align == "left" ? 0 : -s.bars.barWidth/2,
                        barRight = barLeft + s.bars.barWidth;
                    
                    for (j = 0; j < points.length; j += ps) {
                        var x = points[j], y = points[j + 1], b = points[j + 2];
                        if (x == null)
                            continue;
  
                        // for a bar graph, the cursor must be inside the bar
                        if (series[i].bars.horizontal ? 
                            (mx <= Math.max(b, x) && mx >= Math.min(b, x) && 
                             my >= y + barLeft && my <= y + barRight) :
                            (mx >= x + barLeft && mx <= x + barRight &&
                             my >= Math.min(b, y) && my <= Math.max(b, y)))
                                item = [i, j / ps];
                    }
                }
            }

            if (item) {
                i = item[0];
                j = item[1];
                ps = series[i].datapoints.pointsize;
                
                return { datapoint: series[i].datapoints.points.slice(j * ps, (j + 1) * ps),
                         dataIndex: j,
                         series: series[i],
                         seriesIndex: i };
            }
            
            return null;
        }

        function onMouseMove(e) {
            if (options.grid.hoverable)
                triggerClickHoverEvent("plothover", e,
                                       function (s) { return s["hoverable"] != false; });
        }

        function onMouseLeave(e) {
            if (options.grid.hoverable)
                triggerClickHoverEvent("plothover", e,
                                       function (s) { return false; });
        }

        function onClick(e) {
            triggerClickHoverEvent("plotclick", e,
                                   function (s) { return s["clickable"] != false; });
        }

        // trigger click or hover event (they send the same parameters
        // so we share their code)
        function triggerClickHoverEvent(eventname, event, seriesFilter) {
            var offset = eventHolder.offset(),
                canvasX = event.pageX - offset.left - plotOffset.left,
                canvasY = event.pageY - offset.top - plotOffset.top,
            pos = canvasToAxisCoords({ left: canvasX, top: canvasY });

            pos.pageX = event.pageX;
            pos.pageY = event.pageY;

            var item = findNearbyItem(canvasX, canvasY, seriesFilter);

            if (item) {
                // fill in mouse pos for any listeners out there
                item.pageX = parseInt(item.series.xaxis.p2c(item.datapoint[0]) + offset.left + plotOffset.left);
                item.pageY = parseInt(item.series.yaxis.p2c(item.datapoint[1]) + offset.top + plotOffset.top);
            }

            if (options.grid.autoHighlight) {
                // clear auto-highlights
                for (var i = 0; i < highlights.length; ++i) {
                    var h = highlights[i];
                    if (h.auto == eventname &&
                        !(item && h.series == item.series &&
                          h.point[0] == item.datapoint[0] &&
                          h.point[1] == item.datapoint[1]))
                        unhighlight(h.series, h.point);
                }
                
                if (item)
                    highlight(item.series, item.datapoint, eventname);
            }
            
            placeholder.trigger(eventname, [ pos, item ]);
        }

        function triggerRedrawOverlay() {
            if (!redrawTimeout)
                redrawTimeout = setTimeout(drawOverlay, 30);
        }

        function drawOverlay() {
            redrawTimeout = null;

            // draw highlights
            octx.save();
            octx.clearRect(0, 0, canvasWidth, canvasHeight);
            octx.translate(plotOffset.left, plotOffset.top);
            
            var i, hi;
            for (i = 0; i < highlights.length; ++i) {
                hi = highlights[i];

                if (hi.series.bars.show)
                    drawBarHighlight(hi.series, hi.point);
                else
                    drawPointHighlight(hi.series, hi.point);
            }
            octx.restore();
            
            executeHooks(hooks.drawOverlay, [octx]);
        }
        
        function highlight(s, point, auto) {
            if (typeof s == "number")
                s = series[s];

            if (typeof point == "number") {
                var ps = s.datapoints.pointsize;
                point = s.datapoints.points.slice(ps * point, ps * (point + 1));
            }

            var i = indexOfHighlight(s, point);
            if (i == -1) {
                highlights.push({ series: s, point: point, auto: auto });

                triggerRedrawOverlay();
            }
            else if (!auto)
                highlights[i].auto = false;
        }
            
        function unhighlight(s, point) {
            if (s == null && point == null) {
                highlights = [];
                triggerRedrawOverlay();
            }
            
            if (typeof s == "number")
                s = series[s];

            if (typeof point == "number")
                point = s.data[point];

            var i = indexOfHighlight(s, point);
            if (i != -1) {
                highlights.splice(i, 1);

                triggerRedrawOverlay();
            }
        }
        
        function indexOfHighlight(s, p) {
            for (var i = 0; i < highlights.length; ++i) {
                var h = highlights[i];
                if (h.series == s && h.point[0] == p[0]
                    && h.point[1] == p[1])
                    return i;
            }
            return -1;
        }
        
        function drawPointHighlight(series, point) {
            var x = point[0], y = point[1],
                axisx = series.xaxis, axisy = series.yaxis;
            
            if (x < axisx.min || x > axisx.max || y < axisy.min || y > axisy.max)
                return;
            
            var pointRadius = series.points.radius + series.points.lineWidth / 2;
            octx.lineWidth = pointRadius;
            octx.strokeStyle = $.color.parse(series.color).scale('a', 0.5).toString();
            var radius = 1.5 * pointRadius,
                x = axisx.p2c(x),
                y = axisy.p2c(y);
            
            octx.beginPath();
            if (series.points.symbol == "circle")
                octx.arc(x, y, radius, 0, 2 * Math.PI, false);
            else
                series.points.symbol(octx, x, y, radius, false);
            octx.closePath();
            octx.stroke();
        }

        function drawBarHighlight(series, point) {
            octx.lineWidth = series.bars.lineWidth;
            octx.strokeStyle = $.color.parse(series.color).scale('a', 0.5).toString();
            var fillStyle = $.color.parse(series.color).scale('a', 0.5).toString();
            var barLeft = series.bars.align == "left" ? 0 : -series.bars.barWidth/2;
            drawBar(point[0], point[1], point[2] || 0, barLeft, barLeft + series.bars.barWidth,
                    0, function () { return fillStyle; }, series.xaxis, series.yaxis, octx, series.bars.horizontal, series.bars.lineWidth);
        }

        function getColorOrGradient(spec, bottom, top, defaultColor) {
            if (typeof spec == "string")
                return spec;
            else {
                // assume this is a gradient spec; IE currently only
                // supports a simple vertical gradient properly, so that's
                // what we support too
                var gradient = ctx.createLinearGradient(0, top, 0, bottom);
                
                for (var i = 0, l = spec.colors.length; i < l; ++i) {
                    var c = spec.colors[i];
                    if (typeof c != "string") {
                        var co = $.color.parse(defaultColor);
                        if (c.brightness != null)
                            co = co.scale('rgb', c.brightness)
                        if (c.opacity != null)
                            co.a *= c.opacity;
                        c = co.toString();
                    }
                    gradient.addColorStop(i / (l - 1), c);
                }
                
                return gradient;
            }
        }
    }

    $.plot = function(placeholder, data, options) {
        //var t0 = new Date();
        var plot = new Plot($(placeholder), data, options, $.plot.plugins);
        //(window.console ? console.log : alert)("time used (msecs): " + ((new Date()).getTime() - t0.getTime()));
        return plot;
    };

    $.plot.version = "0.7";
    
    $.plot.plugins = [];

    // returns a string with the date d formatted according to fmt
    $.plot.formatDate = function(d, fmt, monthNames) {
        var leftPad = function(n) {
            n = "" + n;
            return n.length == 1 ? "0" + n : n;
        };
        
        var r = [];
        var escape = false, padNext = false;
        var hours = d.getUTCHours();
        var isAM = hours < 12;
        if (monthNames == null)
            monthNames = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];

        if (fmt.search(/%p|%P/) != -1) {
            if (hours > 12) {
                hours = hours - 12;
            } else if (hours == 0) {
                hours = 12;
            }
        }
        for (var i = 0; i < fmt.length; ++i) {
            var c = fmt.charAt(i);
            
            if (escape) {
                switch (c) {
                case 'h': c = "" + hours; break;
                case 'H': c = leftPad(hours); break;
                case 'M': c = leftPad(d.getUTCMinutes()); break;
                case 'S': c = leftPad(d.getUTCSeconds()); break;
                case 'd': c = "" + d.getUTCDate(); break;
                case 'm': c = "" + (d.getUTCMonth() + 1); break;
                case 'y': c = "" + d.getUTCFullYear(); break;
                case 'b': c = "" + monthNames[d.getUTCMonth()]; break;
                case 'p': c = (isAM) ? ("" + "am") : ("" + "pm"); break;
                case 'P': c = (isAM) ? ("" + "AM") : ("" + "PM"); break;
                case '0': c = ""; padNext = true; break;
                }
                if (c && padNext) {
                    c = leftPad(c);
                    padNext = false;
                }
                r.push(c);
                if (!padNext)
                    escape = false;
            }
            else {
                if (c == "%")
                    escape = true;
                else
                    r.push(c);
            }
        }
        return r.join("");
    };
    
    // round to nearby lower multiple of base
    function floorInBase(n, base) {
        return base * Math.floor(n / base);
    }
    
})(jQuery);
;
/**
 * Copyright (c) 2009 Sergiy Kovalchuk (serg472@gmail.com)
 * 
 * Dual licensed under the MIT (http://www.opensource.org/licenses/mit-license.php)
 * and GPL (http://www.opensource.org/licenses/gpl-license.php) licenses.
 *  
 * Following code is based on Element.mask() implementation from ExtJS framework (http://extjs.com/)
 *
 */
(function(a){a.fn.mask=function(c,b){a(this).each(function(){if(b!==undefined&&b>0){var d=a(this);d.data("_mask_timeout",setTimeout(function(){a.maskElement(d,c)},b))}else{a.maskElement(a(this),c)}})};a.fn.unmask=function(){a(this).each(function(){a.unmaskElement(a(this))})};a.fn.isMasked=function(){return this.hasClass("masked")};a.maskElement=function(d,c){if(d.data("_mask_timeout")!==undefined){clearTimeout(d.data("_mask_timeout"));d.removeData("_mask_timeout")}if(d.isMasked()){a.unmaskElement(d)}if(d.css("position")=="static"){d.addClass("masked-relative")}d.addClass("masked");var e=a('<div class="loadmask"></div>');if(navigator.userAgent.toLowerCase().indexOf("msie")>-1){e.height(d.height()+parseInt(d.css("padding-top"))+parseInt(d.css("padding-bottom")));e.width(d.width()+parseInt(d.css("padding-left"))+parseInt(d.css("padding-right")))}if(navigator.userAgent.toLowerCase().indexOf("msie 6")>-1){d.find("select").addClass("masked-hidden")}d.append(e);if(c!==undefined){var b=a('<div class="loadmask-msg" style="display:none;"></div>');b.append("<div>"+c+"</div>");d.append(b);b.css("top",Math.round(d.height()/2-(b.height()-parseInt(b.css("padding-top"))-parseInt(b.css("padding-bottom")))/2)+"px");b.css("left",Math.round(d.width()/2-(b.width()-parseInt(b.css("padding-left"))-parseInt(b.css("padding-right")))/2)+"px");b.show()}};a.unmaskElement=function(b){if(b.data("_mask_timeout")!==undefined){clearTimeout(b.data("_mask_timeout"));b.removeData("_mask_timeout")}b.find(".loadmask-msg,.loadmask").remove();b.removeClass("masked");b.removeClass("masked-relative");b.find("select").removeClass("masked-hidden")}})(jQuery);;
/*
 * jsTree 1.0-rc3
 * http://jstree.com/
 *
 * Copyright (c) 2010 Ivan Bozhanov (vakata.com)
 *
 * Licensed same as jquery - under the terms of either the MIT License or the GPL Version 2 License
 *   http://www.opensource.org/licenses/mit-license.php
 *   http://www.gnu.org/licenses/gpl.html
 *
 * $Date: 2011-02-09 01:17:14 +0200 (ср, 09 февр 2011) $
 * $Revision: 236 $
 */

/*jslint browser: true, onevar: true, undef: true, bitwise: true, strict: true */
/*global window : false, clearInterval: false, clearTimeout: false, document: false, setInterval: false, setTimeout: false, jQuery: false, navigator: false, XSLTProcessor: false, DOMParser: false, XMLSerializer: false*/

"use strict";

// top wrapper to prevent multiple inclusion (is this OK?)
(function () { if(jQuery && jQuery.jstree) { return; }
	var is_ie6 = false, is_ie7 = false, is_ff2 = false;

/* 
 * jsTree core
 */
(function ($) {
	// Common functions not related to jsTree 
	// decided to move them to a `vakata` "namespace"
	$.vakata = {};
	// CSS related functions
	$.vakata.css = {
		get_css : function(rule_name, delete_flag, sheet) {
			rule_name = rule_name.toLowerCase();
			var css_rules = sheet.cssRules || sheet.rules,
				j = 0;
			do {
				if(css_rules.length && j > css_rules.length + 5) { return false; }
				if(css_rules[j].selectorText && css_rules[j].selectorText.toLowerCase() == rule_name) {
					if(delete_flag === true) {
						if(sheet.removeRule) { sheet.removeRule(j); }
						if(sheet.deleteRule) { sheet.deleteRule(j); }
						return true;
					}
					else { return css_rules[j]; }
				}
			}
			while (css_rules[++j]);
			return false;
		},
		add_css : function(rule_name, sheet) {
			if($.jstree.css.get_css(rule_name, false, sheet)) { return false; }
			if(sheet.insertRule) { sheet.insertRule(rule_name + ' { }', 0); } else { sheet.addRule(rule_name, null, 0); }
			return $.vakata.css.get_css(rule_name);
		},
		remove_css : function(rule_name, sheet) { 
			return $.vakata.css.get_css(rule_name, true, sheet); 
		},
		add_sheet : function(opts) {
			var tmp = false, is_new = true;
			if(opts.str) {
				if(opts.title) { tmp = $("style[id='" + opts.title + "-stylesheet']")[0]; }
				if(tmp) { is_new = false; }
				else {
					tmp = document.createElement("style");
					tmp.setAttribute('type',"text/css");
					if(opts.title) { tmp.setAttribute("id", opts.title + "-stylesheet"); }
				}
				if(tmp.styleSheet) {
					if(is_new) { 
						document.getElementsByTagName("head")[0].appendChild(tmp); 
						tmp.styleSheet.cssText = opts.str; 
					}
					else {
						tmp.styleSheet.cssText = tmp.styleSheet.cssText + " " + opts.str; 
					}
				}
				else {
					tmp.appendChild(document.createTextNode(opts.str));
					document.getElementsByTagName("head")[0].appendChild(tmp);
				}
				return tmp.sheet || tmp.styleSheet;
			}
			if(opts.url) {
				if(document.createStyleSheet) {
					try { tmp = document.createStyleSheet(opts.url); } catch (e) { }
				}
				else {
					tmp			= document.createElement('link');
					tmp.rel		= 'stylesheet';
					tmp.type	= 'text/css';
					tmp.media	= "all";
					tmp.href	= opts.url;
					document.getElementsByTagName("head")[0].appendChild(tmp);
					return tmp.styleSheet;
				}
			}
		}
	};

	// private variables 
	var instances = [],			// instance array (used by $.jstree.reference/create/focused)
		focused_instance = -1,	// the index in the instance array of the currently focused instance
		plugins = {},			// list of included plugins
		prepared_move = {};		// for the move_node function

	// jQuery plugin wrapper (thanks to jquery UI widget function)
	$.fn.jstree = function (settings) {
		var isMethodCall = (typeof settings == 'string'), // is this a method call like $().jstree("open_node")
			args = Array.prototype.slice.call(arguments, 1), 
			returnValue = this;

		// if a method call execute the method on all selected instances
		if(isMethodCall) {
			if(settings.substring(0, 1) == '_') { return returnValue; }
			this.each(function() {
				var instance = instances[$.data(this, "jstree_instance_id")],
					methodValue = (instance && $.isFunction(instance[settings])) ? instance[settings].apply(instance, args) : instance;
					if(typeof methodValue !== "undefined" && (settings.indexOf("is_") === 0 || (methodValue !== true && methodValue !== false))) { returnValue = methodValue; return false; }
			});
		}
		else {
			this.each(function() {
				// extend settings and allow for multiple hashes and $.data
				var instance_id = $.data(this, "jstree_instance_id"),
					a = [],
					b = settings ? $.extend({}, true, settings) : {},
					c = $(this), 
					s = false, 
					t = [];
				a = a.concat(args);
				if(c.data("jstree")) { a.push(c.data("jstree")); }
				b = a.length ? $.extend.apply(null, [true, b].concat(a)) : b;

				// if an instance already exists, destroy it first
				if(typeof instance_id !== "undefined" && instances[instance_id]) { instances[instance_id].destroy(); }
				// push a new empty object to the instances array
				instance_id = parseInt(instances.push({}),10) - 1;
				// store the jstree instance id to the container element
				$.data(this, "jstree_instance_id", instance_id);
				// clean up all plugins
				b.plugins = $.isArray(b.plugins) ? b.plugins : $.jstree.defaults.plugins.slice();
				b.plugins.unshift("core");
				// only unique plugins
				b.plugins = b.plugins.sort().join(",,").replace(/(,|^)([^,]+)(,,\2)+(,|$)/g,"$1$2$4").replace(/,,+/g,",").replace(/,$/,"").split(",");

				// extend defaults with passed data
				s = $.extend(true, {}, $.jstree.defaults, b);
				s.plugins = b.plugins;
				$.each(plugins, function (i, val) { 
					if($.inArray(i, s.plugins) === -1) { s[i] = null; delete s[i]; } 
					else { t.push(i); }
				});
				s.plugins = t;

				// push the new object to the instances array (at the same time set the default classes to the container) and init
				instances[instance_id] = new $.jstree._instance(instance_id, $(this).addClass("jstree jstree-" + instance_id), s); 
				// init all activated plugins for this instance
				$.each(instances[instance_id]._get_settings().plugins, function (i, val) { instances[instance_id].data[val] = {}; });
				$.each(instances[instance_id]._get_settings().plugins, function (i, val) { if(plugins[val]) { plugins[val].__init.apply(instances[instance_id]); } });
				// initialize the instance
				setTimeout(function() { if(instances[instance_id]) { instances[instance_id].init(); } }, 0);
			});
		}
		// return the jquery selection (or if it was a method call that returned a value - the returned value)
		return returnValue;
	};
	// object to store exposed functions and objects
	$.jstree = {
		defaults : {
			plugins : []
		},
		_focused : function () { return instances[focused_instance] || null; },
		_reference : function (needle) { 
			// get by instance id
			if(instances[needle]) { return instances[needle]; }
			// get by DOM (if still no luck - return null
			var o = $(needle); 
			if(!o.length && typeof needle === "string") { o = $("#" + needle); }
			if(!o.length) { return null; }
			return instances[o.closest(".jstree").data("jstree_instance_id")] || null; 
		},
		_instance : function (index, container, settings) { 
			// for plugins to store data in
			this.data = { core : {} };
			this.get_settings	= function () { return $.extend(true, {}, settings); };
			this._get_settings	= function () { return settings; };
			this.get_index		= function () { return index; };
			this.get_container	= function () { return container; };
			this.get_container_ul = function () { return container.children("ul:eq(0)"); };
			this._set_settings	= function (s) { 
				settings = $.extend(true, {}, settings, s);
			};
		},
		_fn : { },
		plugin : function (pname, pdata) {
			pdata = $.extend({}, {
				__init		: $.noop, 
				__destroy	: $.noop,
				_fn			: {},
				defaults	: false
			}, pdata);
			plugins[pname] = pdata;

			$.jstree.defaults[pname] = pdata.defaults;
			$.each(pdata._fn, function (i, val) {
				val.plugin		= pname;
				val.old			= $.jstree._fn[i];
				$.jstree._fn[i] = function () {
					var rslt,
						func = val,
						args = Array.prototype.slice.call(arguments),
						evnt = new $.Event("before.jstree"),
						rlbk = false;

					if(this.data.core.locked === true && i !== "unlock" && i !== "is_locked") { return; }

					// Check if function belongs to the included plugins of this instance
					do {
						if(func && func.plugin && $.inArray(func.plugin, this._get_settings().plugins) !== -1) { break; }
						func = func.old;
					} while(func);
					if(!func) { return; }

					// context and function to trigger events, then finally call the function
					if(i.indexOf("_") === 0) {
						rslt = func.apply(this, args);
					}
					else {
						rslt = this.get_container().triggerHandler(evnt, { "func" : i, "inst" : this, "args" : args, "plugin" : func.plugin });
						if(rslt === false) { return; }
						if(typeof rslt !== "undefined") { args = rslt; }

						rslt = func.apply(
							$.extend({}, this, { 
								__callback : function (data) { 
									this.get_container().triggerHandler( i + '.jstree', { "inst" : this, "args" : args, "rslt" : data, "rlbk" : rlbk });
								},
								__rollback : function () { 
									rlbk = this.get_rollback();
									return rlbk;
								},
								__call_old : function (replace_arguments) {
									return func.old.apply(this, (replace_arguments ? Array.prototype.slice.call(arguments, 1) : args ) );
								}
							}), args);
					}

					// return the result
					return rslt;
				};
				$.jstree._fn[i].old = val.old;
				$.jstree._fn[i].plugin = pname;
			});
		},
		rollback : function (rb) {
			if(rb) {
				if(!$.isArray(rb)) { rb = [ rb ]; }
				$.each(rb, function (i, val) {
					instances[val.i].set_rollback(val.h, val.d);
				});
			}
		}
	};
	// set the prototype for all instances
	$.jstree._fn = $.jstree._instance.prototype = {};

	// load the css when DOM is ready
	$(function() {
		// code is copied from jQuery ($.browser is deprecated + there is a bug in IE)
		var u = navigator.userAgent.toLowerCase(),
			v = (u.match( /.+?(?:rv|it|ra|ie)[\/: ]([\d.]+)/ ) || [0,'0'])[1],
			css_string = '' + 
				'.jstree ul, .jstree li { display:block; margin:0 0 0 0; padding:0 0 0 0; list-style-type:none; } ' + 
				'.jstree li { display:block; min-height:18px; line-height:18px; white-space:nowrap; margin-left:18px; min-width:18px; } ' + 
				'.jstree-rtl li { margin-left:0; margin-right:18px; } ' + 
				'.jstree > ul > li { margin-left:0px; } ' + 
				'.jstree-rtl > ul > li { margin-right:0px; } ' + 
				'.jstree ins { display:inline-block; text-decoration:none; width:18px; height:18px; margin:0 0 0 0; padding:0; } ' + 
				'.jstree a { display:inline-block; line-height:16px; height:16px; color:black; white-space:nowrap; text-decoration:none; padding:1px 2px; margin:0; } ' + 
				'.jstree a:focus { outline: none; } ' + 
				'.jstree a > ins { height:16px; width:16px; } ' + 
				'.jstree a > .jstree-icon { margin-right:3px; } ' + 
				'.jstree-rtl a > .jstree-icon { margin-left:3px; margin-right:0; } ' + 
				'li.jstree-open > ul { display:block; } ' + 
				'li.jstree-closed > ul { display:none; } ';
		// Correct IE 6 (does not support the > CSS selector)
		if(/msie/.test(u) && parseInt(v, 10) == 6) { 
			is_ie6 = true;

			// fix image flicker and lack of caching
			try {
				document.execCommand("BackgroundImageCache", false, true);
			} catch (err) { }

			css_string += '' + 
				'.jstree li { height:18px; margin-left:0; margin-right:0; } ' + 
				'.jstree li li { margin-left:18px; } ' + 
				'.jstree-rtl li li { margin-left:0px; margin-right:18px; } ' + 
				'li.jstree-open ul { display:block; } ' + 
				'li.jstree-closed ul { display:none !important; } ' + 
				'.jstree li a { display:inline; border-width:0 !important; padding:0px 2px !important; } ' + 
				'.jstree li a ins { height:16px; width:16px; margin-right:3px; } ' + 
				'.jstree-rtl li a ins { margin-right:0px; margin-left:3px; } ';
		}
		// Correct IE 7 (shifts anchor nodes onhover)
		if(/msie/.test(u) && parseInt(v, 10) == 7) { 
			is_ie7 = true;
			css_string += '.jstree li a { border-width:0 !important; padding:0px 2px !important; } ';
		}
		// correct ff2 lack of display:inline-block
		if(!/compatible/.test(u) && /mozilla/.test(u) && parseFloat(v, 10) < 1.9) {
			is_ff2 = true;
			css_string += '' + 
				'.jstree ins { display:-moz-inline-box; } ' + 
				'.jstree li { line-height:12px; } ' + // WHY??
				'.jstree a { display:-moz-inline-box; } ' + 
				'.jstree .jstree-no-icons .jstree-checkbox { display:-moz-inline-stack !important; } ';
				/* this shouldn't be here as it is theme specific */
		}
		// the default stylesheet
		$.vakata.css.add_sheet({ str : css_string, title : "jstree" });
	});

	// core functions (open, close, create, update, delete)
	$.jstree.plugin("core", {
		__init : function () {
			this.data.core.locked = false;
			this.data.core.to_open = this.get_settings().core.initially_open;
			this.data.core.to_load = this.get_settings().core.initially_load;
		},
		defaults : { 
			html_titles	: false,
			animation	: 500,
			initially_open : [],
			initially_load : [],
			open_parents : true,
			notify_plugins : true,
			rtl			: false,
			load_open	: false,
			strings		: {
				loading		: "Loading ...",
				new_node	: "New node",
				multiple_selection : "Multiple selection"
			}
		},
		_fn : { 
			init	: function () { 
				this.set_focus(); 
				if(this._get_settings().core.rtl) {
					this.get_container().addClass("jstree-rtl").css("direction", "rtl");
				}
				this.get_container().html("<ul><li class='jstree-last jstree-leaf'><ins></ins><a class='jstree-loading' href='#'><ins class='jstree-icon'>&#160;</ins>" + this._get_string("loading") + "</a></li></ul>");
				this.data.core.li_height = this.get_container_ul().find("li.jstree-closed, li.jstree-leaf").eq(0).height() || 18;

				this.get_container()
					.delegate("li > ins", "click.jstree", $.proxy(function (event) {
							var trgt = $(event.target);
							// if(trgt.is("ins") && event.pageY - trgt.offset().top < this.data.core.li_height) { this.toggle_node(trgt); }
							this.toggle_node(trgt);
						}, this))
					.bind("mousedown.jstree", $.proxy(function () { 
							this.set_focus(); // This used to be setTimeout(set_focus,0) - why?
						}, this))
					.bind("dblclick.jstree", function (event) { 
						var sel;
						if(document.selection && document.selection.empty) { document.selection.empty(); }
						else {
							if(window.getSelection) {
								sel = window.getSelection();
								try { 
									sel.removeAllRanges();
									sel.collapse();
								} catch (err) { }
							}
						}
					});
				if(this._get_settings().core.notify_plugins) {
					this.get_container()
						.bind("load_node.jstree", $.proxy(function (e, data) { 
								var o = this._get_node(data.rslt.obj),
									t = this;
								if(o === -1) { o = this.get_container_ul(); }
								if(!o.length) { return; }
								o.find("li").each(function () {
									var th = $(this);
									if(th.data("jstree")) {
										$.each(th.data("jstree"), function (plugin, values) {
											if(t.data[plugin] && $.isFunction(t["_" + plugin + "_notify"])) {
												t["_" + plugin + "_notify"].call(t, th, values);
											}
										});
									}
								});
							}, this));
				}
				if(this._get_settings().core.load_open) {
					this.get_container()
						.bind("load_node.jstree", $.proxy(function (e, data) { 
								var o = this._get_node(data.rslt.obj),
									t = this;
								if(o === -1) { o = this.get_container_ul(); }
								if(!o.length) { return; }
								o.find("li.jstree-open:not(:has(ul))").each(function () {
									t.load_node(this, $.noop, $.noop);
								});
							}, this));
				}
				this.__callback();
				this.load_node(-1, function () { this.loaded(); this.reload_nodes(); });
			},
			destroy	: function () { 
				var i,
					n = this.get_index(),
					s = this._get_settings(),
					_this = this;

				$.each(s.plugins, function (i, val) {
					try { plugins[val].__destroy.apply(_this); } catch(err) { }
				});
				this.__callback();
				// set focus to another instance if this one is focused
				if(this.is_focused()) { 
					for(i in instances) { 
						if(instances.hasOwnProperty(i) && i != n) { 
							instances[i].set_focus(); 
							break; 
						} 
					}
				}
				// if no other instance found
				if(n === focused_instance) { focused_instance = -1; }
				// remove all traces of jstree in the DOM (only the ones set using jstree*) and cleans all events
				this.get_container()
					.unbind(".jstree")
					.undelegate(".jstree")
					.removeData("jstree_instance_id")
					.find("[class^='jstree']")
						.andSelf()
						.attr("class", function () { return this.className.replace(/jstree[^ ]*|$/ig,''); });
				$(document)
					.unbind(".jstree-" + n)
					.undelegate(".jstree-" + n);
				// remove the actual data
				instances[n] = null;
				delete instances[n];
			},

			_core_notify : function (n, data) {
				if(data.opened) {
					this.open_node(n, false, true);
				}
			},

			lock : function () {
				this.data.core.locked = true;
				this.get_container().children("ul").addClass("jstree-locked").css("opacity","0.7");
				this.__callback({});
			},
			unlock : function () {
				this.data.core.locked = false;
				this.get_container().children("ul").removeClass("jstree-locked").css("opacity","1");
				this.__callback({});
			},
			is_locked : function () { return this.data.core.locked; },
			save_opened : function () {
				var _this = this;
				this.data.core.to_open = [];
				this.get_container_ul().find("li.jstree-open").each(function () { 
					if(this.id) { _this.data.core.to_open.push("#" + this.id.toString().replace(/^#/,"").replace(/\\\//g,"/").replace(/\//g,"\\\/").replace(/\\\./g,".").replace(/\./g,"\\.").replace(/\:/g,"\\:")); }
				});
				this.__callback(_this.data.core.to_open);
			},
			save_loaded : function () { },
			reload_nodes : function (is_callback) {
				var _this = this,
					done = true,
					current = [],
					remaining = [];
				if(!is_callback) { 
					this.data.core.reopen = false; 
					this.data.core.refreshing = true; 
					this.data.core.to_open = $.map($.makeArray(this.data.core.to_open), function (n) { return "#" + n.toString().replace(/^#/,"").replace(/\\\//g,"/").replace(/\//g,"\\\/").replace(/\\\./g,".").replace(/\./g,"\\.").replace(/\:/g,"\\:"); });
					this.data.core.to_load = $.map($.makeArray(this.data.core.to_load), function (n) { return "#" + n.toString().replace(/^#/,"").replace(/\\\//g,"/").replace(/\//g,"\\\/").replace(/\\\./g,".").replace(/\./g,"\\.").replace(/\:/g,"\\:"); });
					if(this.data.core.to_open.length) {
						this.data.core.to_load = this.data.core.to_load.concat(this.data.core.to_open);
					}
				}
				if(this.data.core.to_load.length) {
					$.each(this.data.core.to_load, function (i, val) {
						if(val == "#") { return true; }
						if($(val).length) { current.push(val); }
						else { remaining.push(val); }
					});
					if(current.length) {
						this.data.core.to_load = remaining;
						$.each(current, function (i, val) { 
							if(!_this._is_loaded(val)) {
								_this.load_node(val, function () { _this.reload_nodes(true); }, function () { _this.reload_nodes(true); });
								done = false;
							}
						});
					}
				}
				if(this.data.core.to_open.length) {
					$.each(this.data.core.to_open, function (i, val) {
						_this.open_node(val, false, true); 
					});
				}
				if(done) { 
					// TODO: find a more elegant approach to syncronizing returning requests
					if(this.data.core.reopen) { clearTimeout(this.data.core.reopen); }
					this.data.core.reopen = setTimeout(function () { _this.__callback({}, _this); }, 50);
					this.data.core.refreshing = false;
					this.reopen();
				}
			},
			reopen : function () {
				var _this = this;
				if(this.data.core.to_open.length) {
					$.each(this.data.core.to_open, function (i, val) {
						_this.open_node(val, false, true); 
					});
				}
				this.__callback({});
			},
			refresh : function (obj) {
				var _this = this;
				this.save_opened();
				if(!obj) { obj = -1; }
				obj = this._get_node(obj);
				if(!obj) { obj = -1; }
				if(obj !== -1) { obj.children("UL").remove(); }
				else { this.get_container_ul().empty(); }
				this.load_node(obj, function () { _this.__callback({ "obj" : obj}); _this.reload_nodes(); });
			},
			// Dummy function to fire after the first load (so that there is a jstree.loaded event)
			loaded	: function () { 
				this.__callback(); 
			},
			// deal with focus
			set_focus	: function () { 
				if(this.is_focused()) { return; }
				var f = $.jstree._focused();
				if(f) { f.unset_focus(); }

				this.get_container().addClass("jstree-focused"); 
				focused_instance = this.get_index(); 
				this.__callback();
			},
			is_focused	: function () { 
				return focused_instance == this.get_index(); 
			},
			unset_focus	: function () {
				if(this.is_focused()) {
					this.get_container().removeClass("jstree-focused"); 
					focused_instance = -1; 
				}
				this.__callback();
			},

			// traverse
			_get_node		: function (obj) { 
				var $obj = $(obj, this.get_container()); 
				if($obj.is(".jstree") || obj == -1) { return -1; } 
				$obj = $obj.closest("li", this.get_container()); 
				return $obj.length ? $obj : false; 
			},
			_get_next		: function (obj, strict) {
				obj = this._get_node(obj);
				if(obj === -1) { return this.get_container().find("> ul > li:first-child"); }
				if(!obj.length) { return false; }
				if(strict) { return (obj.nextAll("li").size() > 0) ? obj.nextAll("li:eq(0)") : false; }

				if(obj.hasClass("jstree-open")) { return obj.find("li:eq(0)"); }
				else if(obj.nextAll("li").size() > 0) { return obj.nextAll("li:eq(0)"); }
				else { return obj.parentsUntil(".jstree","li").next("li").eq(0); }
			},
			_get_prev		: function (obj, strict) {
				obj = this._get_node(obj);
				if(obj === -1) { return this.get_container().find("> ul > li:last-child"); }
				if(!obj.length) { return false; }
				if(strict) { return (obj.prevAll("li").length > 0) ? obj.prevAll("li:eq(0)") : false; }

				if(obj.prev("li").length) {
					obj = obj.prev("li").eq(0);
					while(obj.hasClass("jstree-open")) { obj = obj.children("ul:eq(0)").children("li:last"); }
					return obj;
				}
				else { var o = obj.parentsUntil(".jstree","li:eq(0)"); return o.length ? o : false; }
			},
			_get_parent		: function (obj) {
				obj = this._get_node(obj);
				if(obj == -1 || !obj.length) { return false; }
				var o = obj.parentsUntil(".jstree", "li:eq(0)");
				return o.length ? o : -1;
			},
			_get_children	: function (obj) {
				obj = this._get_node(obj);
				if(obj === -1) { return this.get_container().children("ul:eq(0)").children("li"); }
				if(!obj.length) { return false; }
				return obj.children("ul:eq(0)").children("li");
			},
			get_path		: function (obj, id_mode) {
				var p = [],
					_this = this;
				obj = this._get_node(obj);
				if(obj === -1 || !obj || !obj.length) { return false; }
				obj.parentsUntil(".jstree", "li").each(function () {
					p.push( id_mode ? this.id : _this.get_text(this) );
				});
				p.reverse();
				p.push( id_mode ? obj.attr("id") : this.get_text(obj) );
				return p;
			},

			// string functions
			_get_string : function (key) {
				return this._get_settings().core.strings[key] || key;
			},

			is_open		: function (obj) { obj = this._get_node(obj); return obj && obj !== -1 && obj.hasClass("jstree-open"); },
			is_closed	: function (obj) { obj = this._get_node(obj); return obj && obj !== -1 && obj.hasClass("jstree-closed"); },
			is_leaf		: function (obj) { obj = this._get_node(obj); return obj && obj !== -1 && obj.hasClass("jstree-leaf"); },
			correct_state	: function (obj) {
				obj = this._get_node(obj);
				if(!obj || obj === -1) { return false; }
				obj.removeClass("jstree-closed jstree-open").addClass("jstree-leaf").children("ul").remove();
				this.__callback({ "obj" : obj });
			},
			// open/close
			open_node	: function (obj, callback, skip_animation) {
				obj = this._get_node(obj);
				if(!obj.length) { return false; }
				if(!obj.hasClass("jstree-closed")) { if(callback) { callback.call(); } return false; }
				var s = skip_animation || is_ie6 ? 0 : this._get_settings().core.animation,
					t = this;
				if(!this._is_loaded(obj)) {
					obj.children("a").addClass("jstree-loading");
					this.load_node(obj, function () { t.open_node(obj, callback, skip_animation); }, callback);
				}
				else {
					if(this._get_settings().core.open_parents) {
						obj.parentsUntil(".jstree",".jstree-closed").each(function () {
							t.open_node(this, false, true);
						});
					}
					if(s) { obj.children("ul").css("display","none"); }
					obj.removeClass("jstree-closed").addClass("jstree-open").children("a").removeClass("jstree-loading");
					if(s) { obj.children("ul").stop(true, true).slideDown(s, function () { this.style.display = ""; t.after_open(obj); }); }
					else { t.after_open(obj); }
					this.__callback({ "obj" : obj });
					if(callback) { callback.call(); }
				}
			},
			after_open	: function (obj) { this.__callback({ "obj" : obj }); },
			close_node	: function (obj, skip_animation) {
				obj = this._get_node(obj);
				var s = skip_animation || is_ie6 ? 0 : this._get_settings().core.animation,
					t = this;
				if(!obj.length || !obj.hasClass("jstree-open")) { return false; }
				if(s) { obj.children("ul").attr("style","display:block !important"); }
				obj.removeClass("jstree-open").addClass("jstree-closed");
				if(s) { obj.children("ul").stop(true, true).slideUp(s, function () { this.style.display = ""; t.after_close(obj); }); }
				else { t.after_close(obj); }
				this.__callback({ "obj" : obj });
			},
			after_close	: function (obj) { this.__callback({ "obj" : obj }); },
			toggle_node	: function (obj) {
				obj = this._get_node(obj);
				if(obj.hasClass("jstree-closed")) { return this.open_node(obj); }
				if(obj.hasClass("jstree-open")) { return this.close_node(obj); }
			},
			open_all	: function (obj, do_animation, original_obj) {
				obj = obj ? this._get_node(obj) : -1;
				if(!obj || obj === -1) { obj = this.get_container_ul(); }
				if(original_obj) { 
					obj = obj.find("li.jstree-closed");
				}
				else {
					original_obj = obj;
					if(obj.is(".jstree-closed")) { obj = obj.find("li.jstree-closed").andSelf(); }
					else { obj = obj.find("li.jstree-closed"); }
				}
				var _this = this;
				obj.each(function () { 
					var __this = this; 
					if(!_this._is_loaded(this)) { _this.open_node(this, function() { _this.open_all(__this, do_animation, original_obj); }, !do_animation); }
					else { _this.open_node(this, false, !do_animation); }
				});
				// so that callback is fired AFTER all nodes are open
				if(original_obj.find('li.jstree-closed').length === 0) { this.__callback({ "obj" : original_obj }); }
			},
			close_all	: function (obj, do_animation) {
				var _this = this;
				obj = obj ? this._get_node(obj) : this.get_container();
				if(!obj || obj === -1) { obj = this.get_container_ul(); }
				obj.find("li.jstree-open").andSelf().each(function () { _this.close_node(this, !do_animation); });
				this.__callback({ "obj" : obj });
			},
			clean_node	: function (obj) {
				obj = obj && obj != -1 ? $(obj) : this.get_container_ul();
				obj = obj.is("li") ? obj.find("li").andSelf() : obj.find("li");
				obj.removeClass("jstree-last")
					.filter("li:last-child").addClass("jstree-last").end()
					.filter(":has(li)")
						.not(".jstree-open").removeClass("jstree-leaf").addClass("jstree-closed");
				obj.not(".jstree-open, .jstree-closed").addClass("jstree-leaf").children("ul").remove();
				this.__callback({ "obj" : obj });
			},
			// rollback
			get_rollback : function () { 
				this.__callback();
				return { i : this.get_index(), h : this.get_container().children("ul").clone(true), d : this.data }; 
			},
			set_rollback : function (html, data) {
				this.get_container().empty().append(html);
				this.data = data;
				this.__callback();
			},
			// Dummy functions to be overwritten by any datastore plugin included
			load_node	: function (obj, s_call, e_call) { this.__callback({ "obj" : obj }); },
			_is_loaded	: function (obj) { return true; },

			// Basic operations: create
			create_node	: function (obj, position, js, callback, is_loaded) {
				obj = this._get_node(obj);
				position = typeof position === "undefined" ? "last" : position;
				var d = $("<li />"),
					s = this._get_settings().core,
					tmp;

				if(obj !== -1 && !obj.length) { return false; }
				if(!is_loaded && !this._is_loaded(obj)) { this.load_node(obj, function () { this.create_node(obj, position, js, callback, true); }); return false; }

				this.__rollback();

				if(typeof js === "string") { js = { "data" : js }; }
				if(!js) { js = {}; }
				if(js.attr) { d.attr(js.attr); }
				if(js.metadata) { d.data(js.metadata); }
				if(js.state) { d.addClass("jstree-" + js.state); }
				if(!js.data) { js.data = this._get_string("new_node"); }
				if(!$.isArray(js.data)) { tmp = js.data; js.data = []; js.data.push(tmp); }
				$.each(js.data, function (i, m) {
					tmp = $("<a />");
					if($.isFunction(m)) { m = m.call(this, js); }
					if(typeof m == "string") { tmp.attr('href','#')[ s.html_titles ? "html" : "text" ](m); }
					else {
						if(!m.attr) { m.attr = {}; }
						if(!m.attr.href) { m.attr.href = '#'; }
						tmp.attr(m.attr)[ s.html_titles ? "html" : "text" ](m.title);
						if(m.language) { tmp.addClass(m.language); }
					}
					tmp.prepend("<ins class='jstree-icon'>&#160;</ins>");
					if(!m.icon && js.icon) { m.icon = js.icon; }
					if(m.icon) { 
						if(m.icon.indexOf("/") === -1) { tmp.children("ins").addClass(m.icon); }
						else { tmp.children("ins").css("background","url('" + m.icon + "') center center no-repeat"); }
					}
					d.append(tmp);
				});
				d.prepend("<ins class='jstree-icon'>&#160;</ins>");
				if(obj === -1) {
					obj = this.get_container();
					if(position === "before") { position = "first"; }
					if(position === "after") { position = "last"; }
				}
				switch(position) {
					case "before": obj.before(d); tmp = this._get_parent(obj); break;
					case "after" : obj.after(d);  tmp = this._get_parent(obj); break;
					case "inside":
					case "first" :
						if(!obj.children("ul").length) { obj.append("<ul />"); }
						obj.children("ul").prepend(d);
						tmp = obj;
						break;
					case "last":
						if(!obj.children("ul").length) { obj.append("<ul />"); }
						obj.children("ul").append(d);
						tmp = obj;
						break;
					default:
						if(!obj.children("ul").length) { obj.append("<ul />"); }
						if(!position) { position = 0; }
						tmp = obj.children("ul").children("li").eq(position);
						if(tmp.length) { tmp.before(d); }
						else { obj.children("ul").append(d); }
						tmp = obj;
						break;
				}
				if(tmp === -1 || tmp.get(0) === this.get_container().get(0)) { tmp = -1; }
				this.clean_node(tmp);
				this.__callback({ "obj" : d, "parent" : tmp });
				if(callback) { callback.call(this, d); }
				return d;
			},
			// Basic operations: rename (deal with text)
			get_text	: function (obj) {
				obj = this._get_node(obj);
				if(!obj.length) { return false; }
				var s = this._get_settings().core.html_titles;
				obj = obj.children("a:eq(0)");
				if(s) {
					obj = obj.clone();
					obj.children("INS").remove();
					return obj.html();
				}
				else {
					obj = obj.contents().filter(function() { return this.nodeType == 3; })[0];
					return obj.nodeValue;
				}
			},
			set_text	: function (obj, val) {
				obj = this._get_node(obj);
				if(!obj.length) { return false; }
				obj = obj.children("a:eq(0)");
				if(this._get_settings().core.html_titles) {
					var tmp = obj.children("INS").clone();
					obj.html(val).prepend(tmp);
					this.__callback({ "obj" : obj, "name" : val });
					return true;
				}
				else {
					obj = obj.contents().filter(function() { return this.nodeType == 3; })[0];
					this.__callback({ "obj" : obj, "name" : val });
					return (obj.nodeValue = val);
				}
			},
			rename_node : function (obj, val) {
				obj = this._get_node(obj);
				this.__rollback();
				if(obj && obj.length && this.set_text.apply(this, Array.prototype.slice.call(arguments))) { this.__callback({ "obj" : obj, "name" : val }); }
			},
			// Basic operations: deleting nodes
			delete_node : function (obj) {
				obj = this._get_node(obj);
				if(!obj.length) { return false; }
				this.__rollback();
				var p = this._get_parent(obj), prev = $([]), t = this;
				obj.each(function () {
					prev = prev.add(t._get_prev(this));
				});
				obj = obj.detach();
				if(p !== -1 && p.find("> ul > li").length === 0) {
					p.removeClass("jstree-open jstree-closed").addClass("jstree-leaf");
				}
				this.clean_node(p);
				this.__callback({ "obj" : obj, "prev" : prev, "parent" : p });
				return obj;
			},
			prepare_move : function (o, r, pos, cb, is_cb) {
				var p = {};

				p.ot = $.jstree._reference(o) || this;
				p.o = p.ot._get_node(o);
				p.r = r === - 1 ? -1 : this._get_node(r);
				p.p = (typeof pos === "undefined" || pos === false) ? "last" : pos; // TODO: move to a setting
				if(!is_cb && prepared_move.o && prepared_move.o[0] === p.o[0] && prepared_move.r[0] === p.r[0] && prepared_move.p === p.p) {
					this.__callback(prepared_move);
					if(cb) { cb.call(this, prepared_move); }
					return;
				}
				p.ot = $.jstree._reference(p.o) || this;
				p.rt = $.jstree._reference(p.r) || this; // r === -1 ? p.ot : $.jstree._reference(p.r) || this
				if(p.r === -1 || !p.r) {
					p.cr = -1;
					switch(p.p) {
						case "first":
						case "before":
						case "inside":
							p.cp = 0; 
							break;
						case "after":
						case "last":
							p.cp = p.rt.get_container().find(" > ul > li").length; 
							break;
						default:
							p.cp = p.p;
							break;
					}
				}
				else {
					if(!/^(before|after)$/.test(p.p) && !this._is_loaded(p.r)) {
						return this.load_node(p.r, function () { this.prepare_move(o, r, pos, cb, true); });
					}
					switch(p.p) {
						case "before":
							p.cp = p.r.index();
							p.cr = p.rt._get_parent(p.r);
							break;
						case "after":
							p.cp = p.r.index() + 1;
							p.cr = p.rt._get_parent(p.r);
							break;
						case "inside":
						case "first":
							p.cp = 0;
							p.cr = p.r;
							break;
						case "last":
							p.cp = p.r.find(" > ul > li").length; 
							p.cr = p.r;
							break;
						default: 
							p.cp = p.p;
							p.cr = p.r;
							break;
					}
				}
				p.np = p.cr == -1 ? p.rt.get_container() : p.cr;
				p.op = p.ot._get_parent(p.o);
				p.cop = p.o.index();
				if(p.op === -1) { p.op = p.ot ? p.ot.get_container() : this.get_container(); }
				if(!/^(before|after)$/.test(p.p) && p.op && p.np && p.op[0] === p.np[0] && p.o.index() < p.cp) { p.cp++; }
				//if(p.p === "before" && p.op && p.np && p.op[0] === p.np[0] && p.o.index() < p.cp) { p.cp--; }
				p.or = p.np.find(" > ul > li:nth-child(" + (p.cp + 1) + ")");
				prepared_move = p;
				this.__callback(prepared_move);
				if(cb) { cb.call(this, prepared_move); }
			},
			check_move : function () {
				var obj = prepared_move, ret = true, r = obj.r === -1 ? this.get_container() : obj.r;
				if(!obj || !obj.o || obj.or[0] === obj.o[0]) { return false; }
				if(obj.op && obj.np && obj.op[0] === obj.np[0] && obj.cp - 1 === obj.o.index()) { return false; }
				obj.o.each(function () { 
					if(r.parentsUntil(".jstree", "li").andSelf().index(this) !== -1) { ret = false; return false; }
				});
				return ret;
			},
			move_node : function (obj, ref, position, is_copy, is_prepared, skip_check) {
				if(!is_prepared) { 
					return this.prepare_move(obj, ref, position, function (p) {
						this.move_node(p, false, false, is_copy, true, skip_check);
					});
				}
				if(is_copy) { 
					prepared_move.cy = true;
				}
				if(!skip_check && !this.check_move()) { return false; }

				this.__rollback();
				var o = false;
				if(is_copy) {
					o = obj.o.clone(true);
					o.find("*[id]").andSelf().each(function () {
						if(this.id) { this.id = "copy_" + this.id; }
					});
				}
				else { o = obj.o; }

				if(obj.or.length) { obj.or.before(o); }
				else { 
					if(!obj.np.children("ul").length) { $("<ul />").appendTo(obj.np); }
					obj.np.children("ul:eq(0)").append(o); 
				}

				try { 
					obj.ot.clean_node(obj.op);
					obj.rt.clean_node(obj.np);
					if(!obj.op.find("> ul > li").length) {
						obj.op.removeClass("jstree-open jstree-closed").addClass("jstree-leaf").children("ul").remove();
					}
				} catch (e) { }

				if(is_copy) { 
					prepared_move.cy = true;
					prepared_move.oc = o; 
				}
				this.__callback(prepared_move);
				return prepared_move;
			},
			_get_move : function () { return prepared_move; }
		}
	});
})(jQuery);
//*/

/* 
 * jsTree ui plugin
 * This plugins handles selecting/deselecting/hovering/dehovering nodes
 */
(function ($) {
	var scrollbar_width, e1, e2;
	$(function() {
		if (/msie/.test(navigator.userAgent.toLowerCase())) {
			e1 = $('<textarea cols="10" rows="2"></textarea>').css({ position: 'absolute', top: -1000, left: 0 }).appendTo('body');
			e2 = $('<textarea cols="10" rows="2" style="overflow: hidden;"></textarea>').css({ position: 'absolute', top: -1000, left: 0 }).appendTo('body');
			scrollbar_width = e1.width() - e2.width();
			e1.add(e2).remove();
		} 
		else {
			e1 = $('<div />').css({ width: 100, height: 100, overflow: 'auto', position: 'absolute', top: -1000, left: 0 })
					.prependTo('body').append('<div />').find('div').css({ width: '100%', height: 200 });
			scrollbar_width = 100 - e1.width();
			e1.parent().remove();
		}
	});
	$.jstree.plugin("ui", {
		__init : function () { 
			this.data.ui.selected = $(); 
			this.data.ui.last_selected = false; 
			this.data.ui.hovered = null;
			this.data.ui.to_select = this.get_settings().ui.initially_select;

			this.get_container()
				.delegate("a", "click.jstree", $.proxy(function (event) {
						event.preventDefault();
						event.currentTarget.blur();
						if(!$(event.currentTarget).hasClass("jstree-loading")) {
							this.select_node(event.currentTarget, true, event);
						}
					}, this))
				.delegate("a", "mouseenter.jstree", $.proxy(function (event) {
						if(!$(event.currentTarget).hasClass("jstree-loading")) {
							this.hover_node(event.target);
						}
					}, this))
				.delegate("a", "mouseleave.jstree", $.proxy(function (event) {
						if(!$(event.currentTarget).hasClass("jstree-loading")) {
							this.dehover_node(event.target);
						}
					}, this))
				.bind("reopen.jstree", $.proxy(function () { 
						this.reselect();
					}, this))
				.bind("get_rollback.jstree", $.proxy(function () { 
						this.dehover_node();
						this.save_selected();
					}, this))
				.bind("set_rollback.jstree", $.proxy(function () { 
						this.reselect();
					}, this))
				.bind("close_node.jstree", $.proxy(function (event, data) { 
						var s = this._get_settings().ui,
							obj = this._get_node(data.rslt.obj),
							clk = (obj && obj.length) ? obj.children("ul").find("a.jstree-clicked") : $(),
							_this = this;
						if(s.selected_parent_close === false || !clk.length) { return; }
						clk.each(function () { 
							_this.deselect_node(this);
							if(s.selected_parent_close === "select_parent") { _this.select_node(obj); }
						});
					}, this))
				.bind("delete_node.jstree", $.proxy(function (event, data) { 
						var s = this._get_settings().ui.select_prev_on_delete,
							obj = this._get_node(data.rslt.obj),
							clk = (obj && obj.length) ? obj.find("a.jstree-clicked") : [],
							_this = this;
						clk.each(function () { _this.deselect_node(this); });
						if(s && clk.length) { 
							data.rslt.prev.each(function () { 
								if(this.parentNode) { _this.select_node(this); return false; /* if return false is removed all prev nodes will be selected */}
							});
						}
					}, this))
				.bind("move_node.jstree", $.proxy(function (event, data) { 
						if(data.rslt.cy) { 
							data.rslt.oc.find("a.jstree-clicked").removeClass("jstree-clicked");
						}
					}, this));
		},
		defaults : {
			select_limit : -1, // 0, 1, 2 ... or -1 for unlimited
			select_multiple_modifier : "ctrl", // on, or ctrl, shift, alt
			select_range_modifier : "shift",
			selected_parent_close : "select_parent", // false, "deselect", "select_parent"
			selected_parent_open : true,
			select_prev_on_delete : true,
			disable_selecting_children : false,
			initially_select : []
		},
		_fn : { 
			_get_node : function (obj, allow_multiple) {
				if(typeof obj === "undefined" || obj === null) { return allow_multiple ? this.data.ui.selected : this.data.ui.last_selected; }
				var $obj = $(obj, this.get_container()); 
				if($obj.is(".jstree") || obj == -1) { return -1; } 
				$obj = $obj.closest("li", this.get_container()); 
				return $obj.length ? $obj : false; 
			},
			_ui_notify : function (n, data) {
				if(data.selected) {
					this.select_node(n, false);
				}
			},
			save_selected : function () {
				var _this = this;
				this.data.ui.to_select = [];
				this.data.ui.selected.each(function () { if(this.id) { _this.data.ui.to_select.push("#" + this.id.toString().replace(/^#/,"").replace(/\\\//g,"/").replace(/\//g,"\\\/").replace(/\\\./g,".").replace(/\./g,"\\.").replace(/\:/g,"\\:")); } });
				this.__callback(this.data.ui.to_select);
			},
			reselect : function () {
				var _this = this,
					s = this.data.ui.to_select;
				s = $.map($.makeArray(s), function (n) { return "#" + n.toString().replace(/^#/,"").replace(/\\\//g,"/").replace(/\//g,"\\\/").replace(/\\\./g,".").replace(/\./g,"\\.").replace(/\:/g,"\\:"); });
				// this.deselect_all(); WHY deselect, breaks plugin state notifier?
				$.each(s, function (i, val) { if(val && val !== "#") { _this.select_node(val); } });
				this.data.ui.selected = this.data.ui.selected.filter(function () { return this.parentNode; });
				this.__callback();
			},
			refresh : function (obj) {
				this.save_selected();
				return this.__call_old();
			},
			hover_node : function (obj) {
				obj = this._get_node(obj);
				if(!obj.length) { return false; }
				//if(this.data.ui.hovered && obj.get(0) === this.data.ui.hovered.get(0)) { return; }
				if(!obj.hasClass("jstree-hovered")) { this.dehover_node(); }
				this.data.ui.hovered = obj.children("a").addClass("jstree-hovered").parent();
				this._fix_scroll(obj);
				this.__callback({ "obj" : obj });
			},
			dehover_node : function () {
				var obj = this.data.ui.hovered, p;
				if(!obj || !obj.length) { return false; }
				p = obj.children("a").removeClass("jstree-hovered").parent();
				if(this.data.ui.hovered[0] === p[0]) { this.data.ui.hovered = null; }
				this.__callback({ "obj" : obj });
			},
			select_node : function (obj, check, e) {
				obj = this._get_node(obj);
				if(obj == -1 || !obj || !obj.length) { return false; }
				var s = this._get_settings().ui,
					is_multiple = (s.select_multiple_modifier == "on" || (s.select_multiple_modifier !== false && e && e[s.select_multiple_modifier + "Key"])),
					is_range = (s.select_range_modifier !== false && e && e[s.select_range_modifier + "Key"] && this.data.ui.last_selected && this.data.ui.last_selected[0] !== obj[0] && this.data.ui.last_selected.parent()[0] === obj.parent()[0]),
					is_selected = this.is_selected(obj),
					proceed = true,
					t = this;
				if(check) {
					if(s.disable_selecting_children && is_multiple && 
						(
							(obj.parentsUntil(".jstree","li").children("a.jstree-clicked").length) ||
							(obj.children("ul").find("a.jstree-clicked:eq(0)").length)
						)
					) {
						return false;
					}
					proceed = false;
					switch(!0) {
						case (is_range):
							this.data.ui.last_selected.addClass("jstree-last-selected");
							obj = obj[ obj.index() < this.data.ui.last_selected.index() ? "nextUntil" : "prevUntil" ](".jstree-last-selected").andSelf();
							if(s.select_limit == -1 || obj.length < s.select_limit) {
								this.data.ui.last_selected.removeClass("jstree-last-selected");
								this.data.ui.selected.each(function () {
									if(this !== t.data.ui.last_selected[0]) { t.deselect_node(this); }
								});
								is_selected = false;
								proceed = true;
							}
							else {
								proceed = false;
							}
							break;
						case (is_selected && !is_multiple): 
							this.deselect_all();
							is_selected = false;
							proceed = true;
							break;
						case (!is_selected && !is_multiple): 
							if(s.select_limit == -1 || s.select_limit > 0) {
								this.deselect_all();
								proceed = true;
							}
							break;
						case (is_selected && is_multiple): 
							this.deselect_node(obj);
							break;
						case (!is_selected && is_multiple): 
							if(s.select_limit == -1 || this.data.ui.selected.length + 1 <= s.select_limit) { 
								proceed = true;
							}
							break;
					}
				}
				if(proceed && !is_selected) {
					if(!is_range) { this.data.ui.last_selected = obj; }
					obj.children("a").addClass("jstree-clicked");
					if(s.selected_parent_open) {
						obj.parents(".jstree-closed").each(function () { t.open_node(this, false, true); });
					}
					this.data.ui.selected = this.data.ui.selected.add(obj);
					this._fix_scroll(obj.eq(0));
					this.__callback({ "obj" : obj, "e" : e });
				}
			},
			_fix_scroll : function (obj) {
				var c = this.get_container()[0], t;
				if(c.scrollHeight > c.offsetHeight) {
					obj = this._get_node(obj);
					if(!obj || obj === -1 || !obj.length || !obj.is(":visible")) { return; }
					t = obj.offset().top - this.get_container().offset().top;
					if(t < 0) { 
						c.scrollTop = c.scrollTop + t - 1; 
					}
					if(t + this.data.core.li_height + (c.scrollWidth > c.offsetWidth ? scrollbar_width : 0) > c.offsetHeight) { 
						c.scrollTop = c.scrollTop + (t - c.offsetHeight + this.data.core.li_height + 1 + (c.scrollWidth > c.offsetWidth ? scrollbar_width : 0)); 
					}
				}
			},
			deselect_node : function (obj) {
				obj = this._get_node(obj);
				if(!obj.length) { return false; }
				if(this.is_selected(obj)) {
					obj.children("a").removeClass("jstree-clicked");
					this.data.ui.selected = this.data.ui.selected.not(obj);
					if(this.data.ui.last_selected.get(0) === obj.get(0)) { this.data.ui.last_selected = this.data.ui.selected.eq(0); }
					this.__callback({ "obj" : obj });
				}
			},
			toggle_select : function (obj) {
				obj = this._get_node(obj);
				if(!obj.length) { return false; }
				if(this.is_selected(obj)) { this.deselect_node(obj); }
				else { this.select_node(obj); }
			},
			is_selected : function (obj) { return this.data.ui.selected.index(this._get_node(obj)) >= 0; },
			get_selected : function (context) { 
				return context ? $(context).find("a.jstree-clicked").parent() : this.data.ui.selected; 
			},
			deselect_all : function (context) {
				var ret = context ? $(context).find("a.jstree-clicked").parent() : this.get_container().find("a.jstree-clicked").parent();
				ret.children("a.jstree-clicked").removeClass("jstree-clicked");
				this.data.ui.selected = $([]);
				this.data.ui.last_selected = false;
				this.__callback({ "obj" : ret });
			}
		}
	});
	// include the selection plugin by default
	$.jstree.defaults.plugins.push("ui");
})(jQuery);
//*/

/* 
 * jsTree CRRM plugin
 * Handles creating/renaming/removing/moving nodes by user interaction.
 */
(function ($) {
	$.jstree.plugin("crrm", { 
		__init : function () {
			this.get_container()
				.bind("move_node.jstree", $.proxy(function (e, data) {
					if(this._get_settings().crrm.move.open_onmove) {
						var t = this;
						data.rslt.np.parentsUntil(".jstree").andSelf().filter(".jstree-closed").each(function () {
							t.open_node(this, false, true);
						});
					}
				}, this));
		},
		defaults : {
			input_width_limit : 200,
			move : {
				always_copy			: false, // false, true or "multitree"
				open_onmove			: true,
				default_position	: "last",
				check_move			: function (m) { return true; }
			}
		},
		_fn : {
			_show_input : function (obj, callback) {
				obj = this._get_node(obj);
				var rtl = this._get_settings().core.rtl,
					w = this._get_settings().crrm.input_width_limit,
					w1 = obj.children("ins").width(),
					w2 = obj.find("> a:visible > ins").width() * obj.find("> a:visible > ins").length,
					t = this.get_text(obj),
					h1 = $("<div />", { css : { "position" : "absolute", "top" : "-200px", "left" : (rtl ? "0px" : "-1000px"), "visibility" : "hidden" } }).appendTo("body"),
					h2 = obj.css("position","relative").append(
					$("<input />", { 
						"value" : t,
						"class" : "jstree-rename-input",
						// "size" : t.length,
						"css" : {
							"padding" : "0",
							"border" : "1px solid silver",
							"position" : "absolute",
							"left"  : (rtl ? "auto" : (w1 + w2 + 4) + "px"),
							"right" : (rtl ? (w1 + w2 + 4) + "px" : "auto"),
							"top" : "0px",
							"height" : (this.data.core.li_height - 2) + "px",
							"lineHeight" : (this.data.core.li_height - 2) + "px",
							"width" : "150px" // will be set a bit further down
						},
						"blur" : $.proxy(function () {
							var i = obj.children(".jstree-rename-input"),
								v = i.val();
							if(v === "") { v = t; }
							h1.remove();
							i.remove(); // rollback purposes
							this.set_text(obj,t); // rollback purposes
							this.rename_node(obj, v);
							callback.call(this, obj, v, t);
							obj.css("position","");
						}, this),
						"keyup" : function (event) {
							var key = event.keyCode || event.which;
							if(key == 27) { this.value = t; this.blur(); return; }
							else if(key == 13) { this.blur(); return; }
							else {
								h2.width(Math.min(h1.text("pW" + this.value).width(),w));
							}
						},
						"keypress" : function(event) {
							var key = event.keyCode || event.which;
							if(key == 13) { return false; }
						}
					})
				).children(".jstree-rename-input"); 
				this.set_text(obj, "");
				h1.css({
						fontFamily		: h2.css('fontFamily')		|| '',
						fontSize		: h2.css('fontSize')		|| '',
						fontWeight		: h2.css('fontWeight')		|| '',
						fontStyle		: h2.css('fontStyle')		|| '',
						fontStretch		: h2.css('fontStretch')		|| '',
						fontVariant		: h2.css('fontVariant')		|| '',
						letterSpacing	: h2.css('letterSpacing')	|| '',
						wordSpacing		: h2.css('wordSpacing')		|| ''
				});
				h2.width(Math.min(h1.text("pW" + h2[0].value).width(),w))[0].select();
			},
			rename : function (obj) {
				obj = this._get_node(obj);
				this.__rollback();
				var f = this.__callback;
				this._show_input(obj, function (obj, new_name, old_name) { 
					f.call(this, { "obj" : obj, "new_name" : new_name, "old_name" : old_name });
				});
			},
			create : function (obj, position, js, callback, skip_rename) {
				var t, _this = this;
				obj = this._get_node(obj);
				if(!obj) { obj = -1; }
				this.__rollback();
				t = this.create_node(obj, position, js, function (t) {
					var p = this._get_parent(t),
						pos = $(t).index();
					if(callback) { callback.call(this, t); }
					if(p.length && p.hasClass("jstree-closed")) { this.open_node(p, false, true); }
					if(!skip_rename) { 
						this._show_input(t, function (obj, new_name, old_name) { 
							_this.__callback({ "obj" : obj, "name" : new_name, "parent" : p, "position" : pos });
						});
					}
					else { _this.__callback({ "obj" : t, "name" : this.get_text(t), "parent" : p, "position" : pos }); }
				});
				return t;
			},
			remove : function (obj) {
				obj = this._get_node(obj, true);
				var p = this._get_parent(obj), prev = this._get_prev(obj);
				this.__rollback();
				obj = this.delete_node(obj);
				if(obj !== false) { this.__callback({ "obj" : obj, "prev" : prev, "parent" : p }); }
			},
			check_move : function () {
				if(!this.__call_old()) { return false; }
				var s = this._get_settings().crrm.move;
				if(!s.check_move.call(this, this._get_move())) { return false; }
				return true;
			},
			move_node : function (obj, ref, position, is_copy, is_prepared, skip_check) {
				var s = this._get_settings().crrm.move;
				if(!is_prepared) { 
					if(typeof position === "undefined") { position = s.default_position; }
					if(position === "inside" && !s.default_position.match(/^(before|after)$/)) { position = s.default_position; }
					return this.__call_old(true, obj, ref, position, is_copy, false, skip_check);
				}
				// if the move is already prepared
				if(s.always_copy === true || (s.always_copy === "multitree" && obj.rt.get_index() !== obj.ot.get_index() )) {
					is_copy = true;
				}
				this.__call_old(true, obj, ref, position, is_copy, true, skip_check);
			},

			cut : function (obj) {
				obj = this._get_node(obj, true);
				if(!obj || !obj.length) { return false; }
				this.data.crrm.cp_nodes = false;
				this.data.crrm.ct_nodes = obj;
				this.__callback({ "obj" : obj });
			},
			copy : function (obj) {
				obj = this._get_node(obj, true);
				if(!obj || !obj.length) { return false; }
				this.data.crrm.ct_nodes = false;
				this.data.crrm.cp_nodes = obj;
				this.__callback({ "obj" : obj });
			},
			paste : function (obj) { 
				obj = this._get_node(obj);
				if(!obj || !obj.length) { return false; }
				var nodes = this.data.crrm.ct_nodes ? this.data.crrm.ct_nodes : this.data.crrm.cp_nodes;
				if(!this.data.crrm.ct_nodes && !this.data.crrm.cp_nodes) { return false; }
				if(this.data.crrm.ct_nodes) { this.move_node(this.data.crrm.ct_nodes, obj); this.data.crrm.ct_nodes = false; }
				if(this.data.crrm.cp_nodes) { this.move_node(this.data.crrm.cp_nodes, obj, false, true); }
				this.__callback({ "obj" : obj, "nodes" : nodes });
			}
		}
	});
	// include the crr plugin by default
	// $.jstree.defaults.plugins.push("crrm");
})(jQuery);
//*/

/* 
 * jsTree themes plugin
 * Handles loading and setting themes, as well as detecting path to themes, etc.
 */
(function ($) {
	var themes_loaded = [];
	// this variable stores the path to the themes folder - if left as false - it will be autodetected
	$.jstree._themes = false;
	$.jstree.plugin("themes", {
		__init : function () { 
			this.get_container()
				.bind("init.jstree", $.proxy(function () {
						var s = this._get_settings().themes;
						this.data.themes.dots = s.dots; 
						this.data.themes.icons = s.icons; 
						this.set_theme(s.theme, s.url);
					}, this))
				.bind("loaded.jstree", $.proxy(function () {
						// bound here too, as simple HTML tree's won't honor dots & icons otherwise
						if(!this.data.themes.dots) { this.hide_dots(); }
						else { this.show_dots(); }
						if(!this.data.themes.icons) { this.hide_icons(); }
						else { this.show_icons(); }
					}, this));
		},
		defaults : { 
			theme : "default", 
			url : false,
			dots : true,
			icons : true
		},
		_fn : {
			set_theme : function (theme_name, theme_url) {
				if(!theme_name) { return false; }
				if(!theme_url) { theme_url = $.jstree._themes + theme_name + '/style.css'; }
				if($.inArray(theme_url, themes_loaded) == -1) {
					$.vakata.css.add_sheet({ "url" : theme_url });
					themes_loaded.push(theme_url);
				}
				if(this.data.themes.theme != theme_name) {
					this.get_container().removeClass('jstree-' + this.data.themes.theme);
					this.data.themes.theme = theme_name;
				}
				this.get_container().addClass('jstree-' + theme_name);
				if(!this.data.themes.dots) { this.hide_dots(); }
				else { this.show_dots(); }
				if(!this.data.themes.icons) { this.hide_icons(); }
				else { this.show_icons(); }
				this.__callback();
			},
			get_theme	: function () { return this.data.themes.theme; },

			show_dots	: function () { this.data.themes.dots = true; this.get_container().children("ul").removeClass("jstree-no-dots"); },
			hide_dots	: function () { this.data.themes.dots = false; this.get_container().children("ul").addClass("jstree-no-dots"); },
			toggle_dots	: function () { if(this.data.themes.dots) { this.hide_dots(); } else { this.show_dots(); } },

			show_icons	: function () { this.data.themes.icons = true; this.get_container().children("ul").removeClass("jstree-no-icons"); },
			hide_icons	: function () { this.data.themes.icons = false; this.get_container().children("ul").addClass("jstree-no-icons"); },
			toggle_icons: function () { if(this.data.themes.icons) { this.hide_icons(); } else { this.show_icons(); } }
		}
	});
	// autodetect themes path
	$(function () {
		if($.jstree._themes === false) {
			$("script").each(function () { 
				if(this.src.toString().match(/jquery\.jstree[^\/]*?\.js(\?.*)?$/)) { 
					$.jstree._themes = this.src.toString().replace(/jquery\.jstree[^\/]*?\.js(\?.*)?$/, "") + 'themes/'; 
					return false; 
				}
			});
		}
		if($.jstree._themes === false) { $.jstree._themes = "themes/"; }
	});
	// include the themes plugin by default
	$.jstree.defaults.plugins.push("themes");
})(jQuery);
//*/

/*
 * jsTree hotkeys plugin
 * Enables keyboard navigation for all tree instances
 * Depends on the jstree ui & jquery hotkeys plugins
 */
(function ($) {
	var bound = [];
	function exec(i, event) {
		var f = $.jstree._focused(), tmp;
		if(f && f.data && f.data.hotkeys && f.data.hotkeys.enabled) { 
			tmp = f._get_settings().hotkeys[i];
			if(tmp) { return tmp.call(f, event); }
		}
	}
	$.jstree.plugin("hotkeys", {
		__init : function () {
			if(typeof $.hotkeys === "undefined") { throw "jsTree hotkeys: jQuery hotkeys plugin not included."; }
			if(!this.data.ui) { throw "jsTree hotkeys: jsTree UI plugin not included."; }
			$.each(this._get_settings().hotkeys, function (i, v) {
				if(v !== false && $.inArray(i, bound) == -1) {
					$(document).bind("keydown", i, function (event) { return exec(i, event); });
					bound.push(i);
				}
			});
			this.get_container()
				.bind("lock.jstree", $.proxy(function () {
						if(this.data.hotkeys.enabled) { this.data.hotkeys.enabled = false; this.data.hotkeys.revert = true; }
					}, this))
				.bind("unlock.jstree", $.proxy(function () {
						if(this.data.hotkeys.revert) { this.data.hotkeys.enabled = true; }
					}, this));
			this.enable_hotkeys();
		},
		defaults : {
			"up" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected || -1;
				this.hover_node(this._get_prev(o));
				return false; 
			},
			"ctrl+up" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected || -1;
				this.hover_node(this._get_prev(o));
				return false; 
			},
			"shift+up" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected || -1;
				this.hover_node(this._get_prev(o));
				return false; 
			},
			"down" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected || -1;
				this.hover_node(this._get_next(o));
				return false;
			},
			"ctrl+down" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected || -1;
				this.hover_node(this._get_next(o));
				return false;
			},
			"shift+down" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected || -1;
				this.hover_node(this._get_next(o));
				return false;
			},
			"left" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected;
				if(o) {
					if(o.hasClass("jstree-open")) { this.close_node(o); }
					else { this.hover_node(this._get_prev(o)); }
				}
				return false;
			},
			"ctrl+left" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected;
				if(o) {
					if(o.hasClass("jstree-open")) { this.close_node(o); }
					else { this.hover_node(this._get_prev(o)); }
				}
				return false;
			},
			"shift+left" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected;
				if(o) {
					if(o.hasClass("jstree-open")) { this.close_node(o); }
					else { this.hover_node(this._get_prev(o)); }
				}
				return false;
			},
			"right" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected;
				if(o && o.length) {
					if(o.hasClass("jstree-closed")) { this.open_node(o); }
					else { this.hover_node(this._get_next(o)); }
				}
				return false;
			},
			"ctrl+right" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected;
				if(o && o.length) {
					if(o.hasClass("jstree-closed")) { this.open_node(o); }
					else { this.hover_node(this._get_next(o)); }
				}
				return false;
			},
			"shift+right" : function () { 
				var o = this.data.ui.hovered || this.data.ui.last_selected;
				if(o && o.length) {
					if(o.hasClass("jstree-closed")) { this.open_node(o); }
					else { this.hover_node(this._get_next(o)); }
				}
				return false;
			},
			"space" : function () { 
				if(this.data.ui.hovered) { this.data.ui.hovered.children("a:eq(0)").click(); } 
				return false; 
			},
			"ctrl+space" : function (event) { 
				event.type = "click";
				if(this.data.ui.hovered) { this.data.ui.hovered.children("a:eq(0)").trigger(event); } 
				return false; 
			},
			"shift+space" : function (event) { 
				event.type = "click";
				if(this.data.ui.hovered) { this.data.ui.hovered.children("a:eq(0)").trigger(event); } 
				return false; 
			},
			"f2" : function () { this.rename(this.data.ui.hovered || this.data.ui.last_selected); },
			"del" : function () { this.remove(this.data.ui.hovered || this._get_node(null)); }
		},
		_fn : {
			enable_hotkeys : function () {
				this.data.hotkeys.enabled = true;
			},
			disable_hotkeys : function () {
				this.data.hotkeys.enabled = false;
			}
		}
	});
})(jQuery);
//*/

/* 
 * jsTree JSON plugin
 * The JSON data store. Datastores are build by overriding the `load_node` and `_is_loaded` functions.
 */
(function ($) {
	$.jstree.plugin("json_data", {
		__init : function() {
			var s = this._get_settings().json_data;
			if(s.progressive_unload) {
				this.get_container().bind("after_close.jstree", function (e, data) {
					data.rslt.obj.children("ul").remove();
				});
			}
		},
		defaults : { 
			// `data` can be a function:
			//  * accepts two arguments - node being loaded and a callback to pass the result to
			//  * will be executed in the current tree's scope & ajax won't be supported
			data : false, 
			ajax : false,
			correct_state : true,
			progressive_render : false,
			progressive_unload : false
		},
		_fn : {
			load_node : function (obj, s_call, e_call) { var _this = this; this.load_node_json(obj, function () { _this.__callback({ "obj" : _this._get_node(obj) }); s_call.call(this); }, e_call); },
			_is_loaded : function (obj) { 
				var s = this._get_settings().json_data;
				obj = this._get_node(obj); 
				return obj == -1 || !obj || (!s.ajax && !s.progressive_render && !$.isFunction(s.data)) || obj.is(".jstree-open, .jstree-leaf") || obj.children("ul").children("li").length > 0;
			},
			refresh : function (obj) {
				obj = this._get_node(obj);
				var s = this._get_settings().json_data;
				if(obj && obj !== -1 && s.progressive_unload && ($.isFunction(s.data) || !!s.ajax)) {
					obj.removeData("jstree_children");
				}
				return this.__call_old();
			},
			load_node_json : function (obj, s_call, e_call) {
				var s = this.get_settings().json_data, d,
					error_func = function () {},
					success_func = function () {};
				obj = this._get_node(obj);

				if(obj && obj !== -1 && (s.progressive_render || s.progressive_unload) && !obj.is(".jstree-open, .jstree-leaf") && obj.children("ul").children("li").length === 0 && obj.data("jstree_children")) {
					d = this._parse_json(obj.data("jstree_children"), obj);
					if(d) {
						obj.append(d);
						if(!s.progressive_unload) { obj.removeData("jstree_children"); }
					}
					this.clean_node(obj);
					if(s_call) { s_call.call(this); }
					return;
				}

				if(obj && obj !== -1) {
					if(obj.data("jstree_is_loading")) { return; }
					else { obj.data("jstree_is_loading",true); }
				}
				switch(!0) {
					case (!s.data && !s.ajax): throw "Neither data nor ajax settings supplied.";
					// function option added here for easier model integration (also supporting async - see callback)
					case ($.isFunction(s.data)):
						s.data.call(this, obj, $.proxy(function (d) {
							d = this._parse_json(d, obj);
							if(!d) { 
								if(obj === -1 || !obj) {
									if(s.correct_state) { this.get_container().children("ul").empty(); }
								}
								else {
									obj.children("a.jstree-loading").removeClass("jstree-loading");
									obj.removeData("jstree_is_loading");
									if(s.correct_state) { this.correct_state(obj); }
								}
								if(e_call) { e_call.call(this); }
							}
							else {
								if(obj === -1 || !obj) { this.get_container().children("ul").empty().append(d.children()); }
								else { obj.append(d).children("a.jstree-loading").removeClass("jstree-loading"); obj.removeData("jstree_is_loading"); }
								this.clean_node(obj);
								if(s_call) { s_call.call(this); }
							}
						}, this));
						break;
					case (!!s.data && !s.ajax) || (!!s.data && !!s.ajax && (!obj || obj === -1)):
						if(!obj || obj == -1) {
							d = this._parse_json(s.data, obj);
							if(d) {
								this.get_container().children("ul").empty().append(d.children());
								this.clean_node();
							}
							else { 
								if(s.correct_state) { this.get_container().children("ul").empty(); }
							}
						}
						if(s_call) { s_call.call(this); }
						break;
					case (!s.data && !!s.ajax) || (!!s.data && !!s.ajax && obj && obj !== -1):
						error_func = function (x, t, e) {
							var ef = this.get_settings().json_data.ajax.error; 
							if(ef) { ef.call(this, x, t, e); }
							if(obj != -1 && obj.length) {
								obj.children("a.jstree-loading").removeClass("jstree-loading");
								obj.removeData("jstree_is_loading");
								if(t === "success" && s.correct_state) { this.correct_state(obj); }
							}
							else {
								if(t === "success" && s.correct_state) { this.get_container().children("ul").empty(); }
							}
							if(e_call) { e_call.call(this); }
						};
						success_func = function (d, t, x) {
							var sf = this.get_settings().json_data.ajax.success; 
							if(sf) { d = sf.call(this,d,t,x) || d; }
							if(d === "" || (d && d.toString && d.toString().replace(/^[\s\n]+$/,"") === "") || (!$.isArray(d) && !$.isPlainObject(d))) {
								return error_func.call(this, x, t, "");
							}
							d = this._parse_json(d, obj);
							if(d) {
								if(obj === -1 || !obj) { this.get_container().children("ul").empty().append(d.children()); }
								else { obj.append(d).children("a.jstree-loading").removeClass("jstree-loading"); obj.removeData("jstree_is_loading"); }
								this.clean_node(obj);
								if(s_call) { s_call.call(this); }
							}
							else {
								if(obj === -1 || !obj) {
									if(s.correct_state) { 
										this.get_container().children("ul").empty(); 
										if(s_call) { s_call.call(this); }
									}
								}
								else {
									obj.children("a.jstree-loading").removeClass("jstree-loading");
									obj.removeData("jstree_is_loading");
									if(s.correct_state) { 
										this.correct_state(obj);
										if(s_call) { s_call.call(this); } 
									}
								}
							}
						};
						s.ajax.context = this;
						s.ajax.error = error_func;
						s.ajax.success = success_func;
						if(!s.ajax.dataType) { s.ajax.dataType = "json"; }
						if($.isFunction(s.ajax.url)) { s.ajax.url = s.ajax.url.call(this, obj); }
						if($.isFunction(s.ajax.data)) { s.ajax.data = s.ajax.data.call(this, obj); }
						$.ajax(s.ajax);
						break;
				}
			},
			_parse_json : function (js, obj, is_callback) {
				var d = false, 
					p = this._get_settings(),
					s = p.json_data,
					t = p.core.html_titles,
					tmp, i, j, ul1, ul2;

				if(!js) { return d; }
				if(s.progressive_unload && obj && obj !== -1) { 
					obj.data("jstree_children", d);
				}
				if($.isArray(js)) {
					d = $();
					if(!js.length) { return false; }
					for(i = 0, j = js.length; i < j; i++) {
						tmp = this._parse_json(js[i], obj, true);
						if(tmp.length) { d = d.add(tmp); }
					}
				}
				else {
					if(typeof js == "string") { js = { data : js }; }
					if(!js.data && js.data !== "") { return d; }
					d = $("<li />");
					if(js.attr) { d.attr(js.attr); }
					if(js.metadata) { d.data(js.metadata); }
					if(js.state) { d.addClass("jstree-" + js.state); }
					if(!$.isArray(js.data)) { tmp = js.data; js.data = []; js.data.push(tmp); }
					$.each(js.data, function (i, m) {
						tmp = $("<a />");
						if($.isFunction(m)) { m = m.call(this, js); }
						if(typeof m == "string") { tmp.attr('href','#')[ t ? "html" : "text" ](m); }
						else {
							if(!m.attr) { m.attr = {}; }
							if(!m.attr.href) { m.attr.href = '#'; }
							tmp.attr(m.attr)[ t ? "html" : "text" ](m.title);
							if(m.language) { tmp.addClass(m.language); }
						}
						tmp.prepend("<ins class='jstree-icon'>&#160;</ins>");
						if(!m.icon && js.icon) { m.icon = js.icon; }
						if(m.icon) { 
							if(m.icon.indexOf("/") === -1) { tmp.children("ins").addClass(m.icon); }
							else { tmp.children("ins").css("background","url('" + m.icon + "') center center no-repeat"); }
						}
						d.append(tmp);
					});
					d.prepend("<ins class='jstree-icon'>&#160;</ins>");
					if(js.children) { 
						if(s.progressive_render && js.state !== "open") {
							d.addClass("jstree-closed").data("jstree_children", js.children);
						}
						else {
							if(s.progressive_unload) { d.data("jstree_children", js.children); }
							if($.isArray(js.children) && js.children.length) {
								tmp = this._parse_json(js.children, obj, true);
								if(tmp.length) {
									ul2 = $("<ul />");
									ul2.append(tmp);
									d.append(ul2);
								}
							}
						}
					}
				}
				if(!is_callback) {
					ul1 = $("<ul />");
					ul1.append(d);
					d = ul1;
				}
				return d;
			},
			get_json : function (obj, li_attr, a_attr, is_callback) {
				var result = [], 
					s = this._get_settings(), 
					_this = this,
					tmp1, tmp2, li, a, t, lang;
				obj = this._get_node(obj);
				if(!obj || obj === -1) { obj = this.get_container().find("> ul > li"); }
				li_attr = $.isArray(li_attr) ? li_attr : [ "id", "class" ];
				if(!is_callback && this.data.types) { li_attr.push(s.types.type_attr); }
				a_attr = $.isArray(a_attr) ? a_attr : [ ];

				obj.each(function () {
					li = $(this);
					tmp1 = { data : [] };
					if(li_attr.length) { tmp1.attr = { }; }
					$.each(li_attr, function (i, v) { 
						tmp2 = li.attr(v); 
						if(tmp2 && tmp2.length && tmp2.replace(/jstree[^ ]*/ig,'').length) {
							tmp1.attr[v] = (" " + tmp2).replace(/ jstree[^ ]*/ig,'').replace(/\s+$/ig," ").replace(/^ /,"").replace(/ $/,""); 
						}
					});
					if(li.hasClass("jstree-open")) { tmp1.state = "open"; }
					if(li.hasClass("jstree-closed")) { tmp1.state = "closed"; }
					if(li.data()) { tmp1.metadata = li.data(); }
					a = li.children("a");
					a.each(function () {
						t = $(this);
						if(
							a_attr.length || 
							$.inArray("languages", s.plugins) !== -1 || 
							t.children("ins").get(0).style.backgroundImage.length || 
							(t.children("ins").get(0).className && t.children("ins").get(0).className.replace(/jstree[^ ]*|$/ig,'').length)
						) { 
							lang = false;
							if($.inArray("languages", s.plugins) !== -1 && $.isArray(s.languages) && s.languages.length) {
								$.each(s.languages, function (l, lv) {
									if(t.hasClass(lv)) {
										lang = lv;
										return false;
									}
								});
							}
							tmp2 = { attr : { }, title : _this.get_text(t, lang) }; 
							$.each(a_attr, function (k, z) {
								tmp2.attr[z] = (" " + (t.attr(z) || "")).replace(/ jstree[^ ]*/ig,'').replace(/\s+$/ig," ").replace(/^ /,"").replace(/ $/,"");
							});
							if($.inArray("languages", s.plugins) !== -1 && $.isArray(s.languages) && s.languages.length) {
								$.each(s.languages, function (k, z) {
									if(t.hasClass(z)) { tmp2.language = z; return true; }
								});
							}
							if(t.children("ins").get(0).className.replace(/jstree[^ ]*|$/ig,'').replace(/^\s+$/ig,"").length) {
								tmp2.icon = t.children("ins").get(0).className.replace(/jstree[^ ]*|$/ig,'').replace(/\s+$/ig," ").replace(/^ /,"").replace(/ $/,"");
							}
							if(t.children("ins").get(0).style.backgroundImage.length) {
								tmp2.icon = t.children("ins").get(0).style.backgroundImage.replace("url(","").replace(")","");
							}
						}
						else {
							tmp2 = _this.get_text(t);
						}
						if(a.length > 1) { tmp1.data.push(tmp2); }
						else { tmp1.data = tmp2; }
					});
					li = li.find("> ul > li");
					if(li.length) { tmp1.children = _this.get_json(li, li_attr, a_attr, true); }
					result.push(tmp1);
				});
				return result;
			}
		}
	});
})(jQuery);
//*/

/* 
 * jsTree languages plugin
 * Adds support for multiple language versions in one tree
 * This basically allows for many titles coexisting in one node, but only one of them being visible at any given time
 * This is useful for maintaining the same structure in many languages (hence the name of the plugin)
 */
(function ($) {
	$.jstree.plugin("languages", {
		__init : function () { this._load_css();  },
		defaults : [],
		_fn : {
			set_lang : function (i) { 
				var langs = this._get_settings().languages,
					st = false,
					selector = ".jstree-" + this.get_index() + ' a';
				if(!$.isArray(langs) || langs.length === 0) { return false; }
				if($.inArray(i,langs) == -1) {
					if(!!langs[i]) { i = langs[i]; }
					else { return false; }
				}
				if(i == this.data.languages.current_language) { return true; }
				st = $.vakata.css.get_css(selector + "." + this.data.languages.current_language, false, this.data.languages.language_css);
				if(st !== false) { st.style.display = "none"; }
				st = $.vakata.css.get_css(selector + "." + i, false, this.data.languages.language_css);
				if(st !== false) { st.style.display = ""; }
				this.data.languages.current_language = i;
				this.__callback(i);
				return true;
			},
			get_lang : function () {
				return this.data.languages.current_language;
			},
			_get_string : function (key, lang) {
				var langs = this._get_settings().languages,
					s = this._get_settings().core.strings;
				if($.isArray(langs) && langs.length) {
					lang = (lang && $.inArray(lang,langs) != -1) ? lang : this.data.languages.current_language;
				}
				if(s[lang] && s[lang][key]) { return s[lang][key]; }
				if(s[key]) { return s[key]; }
				return key;
			},
			get_text : function (obj, lang) {
				obj = this._get_node(obj) || this.data.ui.last_selected;
				if(!obj.size()) { return false; }
				var langs = this._get_settings().languages,
					s = this._get_settings().core.html_titles;
				if($.isArray(langs) && langs.length) {
					lang = (lang && $.inArray(lang,langs) != -1) ? lang : this.data.languages.current_language;
					obj = obj.children("a." + lang);
				}
				else { obj = obj.children("a:eq(0)"); }
				if(s) {
					obj = obj.clone();
					obj.children("INS").remove();
					return obj.html();
				}
				else {
					obj = obj.contents().filter(function() { return this.nodeType == 3; })[0];
					return obj.nodeValue;
				}
			},
			set_text : function (obj, val, lang) {
				obj = this._get_node(obj) || this.data.ui.last_selected;
				if(!obj.size()) { return false; }
				var langs = this._get_settings().languages,
					s = this._get_settings().core.html_titles,
					tmp;
				if($.isArray(langs) && langs.length) {
					lang = (lang && $.inArray(lang,langs) != -1) ? lang : this.data.languages.current_language;
					obj = obj.children("a." + lang);
				}
				else { obj = obj.children("a:eq(0)"); }
				if(s) {
					tmp = obj.children("INS").clone();
					obj.html(val).prepend(tmp);
					this.__callback({ "obj" : obj, "name" : val, "lang" : lang });
					return true;
				}
				else {
					obj = obj.contents().filter(function() { return this.nodeType == 3; })[0];
					this.__callback({ "obj" : obj, "name" : val, "lang" : lang });
					return (obj.nodeValue = val);
				}
			},
			_load_css : function () {
				var langs = this._get_settings().languages,
					str = "/* languages css */",
					selector = ".jstree-" + this.get_index() + ' a',
					ln;
				if($.isArray(langs) && langs.length) {
					this.data.languages.current_language = langs[0];
					for(ln = 0; ln < langs.length; ln++) {
						str += selector + "." + langs[ln] + " {";
						if(langs[ln] != this.data.languages.current_language) { str += " display:none; "; }
						str += " } ";
					}
					this.data.languages.language_css = $.vakata.css.add_sheet({ 'str' : str, 'title' : "jstree-languages" });
				}
			},
			create_node : function (obj, position, js, callback) {
				var t = this.__call_old(true, obj, position, js, function (t) {
					var langs = this._get_settings().languages,
						a = t.children("a"),
						ln;
					if($.isArray(langs) && langs.length) {
						for(ln = 0; ln < langs.length; ln++) {
							if(!a.is("." + langs[ln])) {
								t.append(a.eq(0).clone().removeClass(langs.join(" ")).addClass(langs[ln]));
							}
						}
						a.not("." + langs.join(", .")).remove();
					}
					if(callback) { callback.call(this, t); }
				});
				return t;
			}
		}
	});
})(jQuery);
//*/

/*
 * jsTree cookies plugin
 * Stores the currently opened/selected nodes in a cookie and then restores them
 * Depends on the jquery.cookie plugin
 */
(function ($) {
	$.jstree.plugin("cookies", {
		__init : function () {
			if(typeof $.cookie === "undefined") { throw "jsTree cookie: jQuery cookie plugin not included."; }

			var s = this._get_settings().cookies,
				tmp;
			if(!!s.save_loaded) {
				tmp = $.cookie(s.save_loaded);
				if(tmp && tmp.length) { this.data.core.to_load = tmp.split(","); }
			}
			if(!!s.save_opened) {
				tmp = $.cookie(s.save_opened);
				if(tmp && tmp.length) { this.data.core.to_open = tmp.split(","); }
			}
			if(!!s.save_selected) {
				tmp = $.cookie(s.save_selected);
				if(tmp && tmp.length && this.data.ui) { this.data.ui.to_select = tmp.split(","); }
			}
			this.get_container()
				.one( ( this.data.ui ? "reselect" : "reopen" ) + ".jstree", $.proxy(function () {
					this.get_container()
						.bind("open_node.jstree close_node.jstree select_node.jstree deselect_node.jstree", $.proxy(function (e) { 
								if(this._get_settings().cookies.auto_save) { this.save_cookie((e.handleObj.namespace + e.handleObj.type).replace("jstree","")); }
							}, this));
				}, this));
		},
		defaults : {
			save_loaded		: "jstree_load",
			save_opened		: "jstree_open",
			save_selected	: "jstree_select",
			auto_save		: true,
			cookie_options	: {}
		},
		_fn : {
			save_cookie : function (c) {
				if(this.data.core.refreshing) { return; }
				var s = this._get_settings().cookies;
				if(!c) { // if called manually and not by event
					if(s.save_loaded) {
						this.save_loaded();
						$.cookie(s.save_loaded, this.data.core.to_load.join(","), s.cookie_options);
					}
					if(s.save_opened) {
						this.save_opened();
						$.cookie(s.save_opened, this.data.core.to_open.join(","), s.cookie_options);
					}
					if(s.save_selected && this.data.ui) {
						this.save_selected();
						$.cookie(s.save_selected, this.data.ui.to_select.join(","), s.cookie_options);
					}
					return;
				}
				switch(c) {
					case "open_node":
					case "close_node":
						if(!!s.save_opened) { 
							this.save_opened(); 
							$.cookie(s.save_opened, this.data.core.to_open.join(","), s.cookie_options); 
						}
						if(!!s.save_loaded) { 
							this.save_loaded(); 
							$.cookie(s.save_loaded, this.data.core.to_load.join(","), s.cookie_options); 
						}
						break;
					case "select_node":
					case "deselect_node":
						if(!!s.save_selected && this.data.ui) { 
							this.save_selected(); 
							$.cookie(s.save_selected, this.data.ui.to_select.join(","), s.cookie_options); 
						}
						break;
				}
			}
		}
	});
	// include cookies by default
	// $.jstree.defaults.plugins.push("cookies");
})(jQuery);
//*/

/*
 * jsTree sort plugin
 * Sorts items alphabetically (or using any other function)
 */
(function ($) {
	$.jstree.plugin("sort", {
		__init : function () {
			this.get_container()
				.bind("load_node.jstree", $.proxy(function (e, data) {
						var obj = this._get_node(data.rslt.obj);
						obj = obj === -1 ? this.get_container().children("ul") : obj.children("ul");
						this.sort(obj);
					}, this))
				.bind("rename_node.jstree create_node.jstree create.jstree", $.proxy(function (e, data) {
						this.sort(data.rslt.obj.parent());
					}, this))
				.bind("move_node.jstree", $.proxy(function (e, data) {
						var m = data.rslt.np == -1 ? this.get_container() : data.rslt.np;
						this.sort(m.children("ul"));
					}, this));
		},
		defaults : function (a, b) { return this.get_text(a) > this.get_text(b) ? 1 : -1; },
		_fn : {
			sort : function (obj) {
				var s = this._get_settings().sort,
					t = this;
				obj.append($.makeArray(obj.children("li")).sort($.proxy(s, t)));
				obj.find("> li > ul").each(function() { t.sort($(this)); });
				this.clean_node(obj);
			}
		}
	});
})(jQuery);
//*/

/*
 * jsTree DND plugin
 * Drag and drop plugin for moving/copying nodes
 */
(function ($) {
	var o = false,
		r = false,
		m = false,
		ml = false,
		sli = false,
		sti = false,
		dir1 = false,
		dir2 = false,
		last_pos = false;
	$.vakata.dnd = {
		is_down : false,
		is_drag : false,
		helper : false,
		scroll_spd : 10,
		init_x : 0,
		init_y : 0,
		threshold : 5,
		helper_left : 5,
		helper_top : 10,
		user_data : {},

		drag_start : function (e, data, html) { 
			if($.vakata.dnd.is_drag) { $.vakata.drag_stop({}); }
			try {
				e.currentTarget.unselectable = "on";
				e.currentTarget.onselectstart = function() { return false; };
				if(e.currentTarget.style) { e.currentTarget.style.MozUserSelect = "none"; }
			} catch(err) { }
			$.vakata.dnd.init_x = e.pageX;
			$.vakata.dnd.init_y = e.pageY;
			$.vakata.dnd.user_data = data;
			$.vakata.dnd.is_down = true;
			$.vakata.dnd.helper = $("<div id='vakata-dragged' />").html(html); //.fadeTo(10,0.25);
			$(document).bind("mousemove", $.vakata.dnd.drag);
			$(document).bind("mouseup", $.vakata.dnd.drag_stop);
			return false;
		},
		drag : function (e) { 
			if(!$.vakata.dnd.is_down) { return; }
			if(!$.vakata.dnd.is_drag) {
				if(Math.abs(e.pageX - $.vakata.dnd.init_x) > 5 || Math.abs(e.pageY - $.vakata.dnd.init_y) > 5) { 
					$.vakata.dnd.helper.appendTo("body");
					$.vakata.dnd.is_drag = true;
					$(document).triggerHandler("drag_start.vakata", { "event" : e, "data" : $.vakata.dnd.user_data });
				}
				else { return; }
			}

			// maybe use a scrolling parent element instead of document?
			if(e.type === "mousemove") { // thought of adding scroll in order to move the helper, but mouse poisition is n/a
				var d = $(document), t = d.scrollTop(), l = d.scrollLeft();
				if(e.pageY - t < 20) { 
					if(sti && dir1 === "down") { clearInterval(sti); sti = false; }
					if(!sti) { dir1 = "up"; sti = setInterval(function () { $(document).scrollTop($(document).scrollTop() - $.vakata.dnd.scroll_spd); }, 150); }
				}
				else { 
					if(sti && dir1 === "up") { clearInterval(sti); sti = false; }
				}
				if($(window).height() - (e.pageY - t) < 20) {
					if(sti && dir1 === "up") { clearInterval(sti); sti = false; }
					if(!sti) { dir1 = "down"; sti = setInterval(function () { $(document).scrollTop($(document).scrollTop() + $.vakata.dnd.scroll_spd); }, 150); }
				}
				else { 
					if(sti && dir1 === "down") { clearInterval(sti); sti = false; }
				}

				if(e.pageX - l < 20) {
					if(sli && dir2 === "right") { clearInterval(sli); sli = false; }
					if(!sli) { dir2 = "left"; sli = setInterval(function () { $(document).scrollLeft($(document).scrollLeft() - $.vakata.dnd.scroll_spd); }, 150); }
				}
				else { 
					if(sli && dir2 === "left") { clearInterval(sli); sli = false; }
				}
				if($(window).width() - (e.pageX - l) < 20) {
					if(sli && dir2 === "left") { clearInterval(sli); sli = false; }
					if(!sli) { dir2 = "right"; sli = setInterval(function () { $(document).scrollLeft($(document).scrollLeft() + $.vakata.dnd.scroll_spd); }, 150); }
				}
				else { 
					if(sli && dir2 === "right") { clearInterval(sli); sli = false; }
				}
			}

			$.vakata.dnd.helper.css({ left : (e.pageX + $.vakata.dnd.helper_left) + "px", top : (e.pageY + $.vakata.dnd.helper_top) + "px" });
			$(document).triggerHandler("drag.vakata", { "event" : e, "data" : $.vakata.dnd.user_data });
		},
		drag_stop : function (e) {
			if(sli) { clearInterval(sli); }
			if(sti) { clearInterval(sti); }
			$(document).unbind("mousemove", $.vakata.dnd.drag);
			$(document).unbind("mouseup", $.vakata.dnd.drag_stop);
			$(document).triggerHandler("drag_stop.vakata", { "event" : e, "data" : $.vakata.dnd.user_data });
			$.vakata.dnd.helper.remove();
			$.vakata.dnd.init_x = 0;
			$.vakata.dnd.init_y = 0;
			$.vakata.dnd.user_data = {};
			$.vakata.dnd.is_down = false;
			$.vakata.dnd.is_drag = false;
		}
	};
	$(function() {
		var css_string = '#vakata-dragged { display:block; margin:0 0 0 0; padding:4px 4px 4px 24px; position:absolute; top:-2000px; line-height:16px; z-index:10000; } ';
		$.vakata.css.add_sheet({ str : css_string, title : "vakata" });
	});

	$.jstree.plugin("dnd", {
		__init : function () {
			this.data.dnd = {
				active : false,
				after : false,
				inside : false,
				before : false,
				off : false,
				prepared : false,
				w : 0,
				to1 : false,
				to2 : false,
				cof : false,
				cw : false,
				ch : false,
				i1 : false,
				i2 : false,
				mto : false
			};
			this.get_container()
				.bind("mouseenter.jstree", $.proxy(function (e) {
						if($.vakata.dnd.is_drag && $.vakata.dnd.user_data.jstree) {
							if(this.data.themes) {
								m.attr("class", "jstree-" + this.data.themes.theme); 
								if(ml) { ml.attr("class", "jstree-" + this.data.themes.theme); }
								$.vakata.dnd.helper.attr("class", "jstree-dnd-helper jstree-" + this.data.themes.theme);
							}
							//if($(e.currentTarget).find("> ul > li").length === 0) {
							if(e.currentTarget === e.target && $.vakata.dnd.user_data.obj && $($.vakata.dnd.user_data.obj).length && $($.vakata.dnd.user_data.obj).parents(".jstree:eq(0)")[0] !== e.target) { // node should not be from the same tree
								var tr = $.jstree._reference(e.target), dc;
								if(tr.data.dnd.foreign) {
									dc = tr._get_settings().dnd.drag_check.call(this, { "o" : o, "r" : tr.get_container(), is_root : true });
									if(dc === true || dc.inside === true || dc.before === true || dc.after === true) {
										$.vakata.dnd.helper.children("ins").attr("class","jstree-ok");
									}
								}
								else {
									tr.prepare_move(o, tr.get_container(), "last");
									if(tr.check_move()) {
										$.vakata.dnd.helper.children("ins").attr("class","jstree-ok");
									}
								}
							}
						}
					}, this))
				.bind("mouseup.jstree", $.proxy(function (e) {
						//if($.vakata.dnd.is_drag && $.vakata.dnd.user_data.jstree && $(e.currentTarget).find("> ul > li").length === 0) {
						if($.vakata.dnd.is_drag && $.vakata.dnd.user_data.jstree && e.currentTarget === e.target && $.vakata.dnd.user_data.obj && $($.vakata.dnd.user_data.obj).length && $($.vakata.dnd.user_data.obj).parents(".jstree:eq(0)")[0] !== e.target) { // node should not be from the same tree
							var tr = $.jstree._reference(e.currentTarget), dc;
							if(tr.data.dnd.foreign) {
								dc = tr._get_settings().dnd.drag_check.call(this, { "o" : o, "r" : tr.get_container(), is_root : true });
								if(dc === true || dc.inside === true || dc.before === true || dc.after === true) {
									tr._get_settings().dnd.drag_finish.call(this, { "o" : o, "r" : tr.get_container(), is_root : true });
								}
							}
							else {
								tr.move_node(o, tr.get_container(), "last", e[tr._get_settings().dnd.copy_modifier + "Key"]);
							}
						}
					}, this))
				.bind("mouseleave.jstree", $.proxy(function (e) {
						if(e.relatedTarget && e.relatedTarget.id && e.relatedTarget.id === "jstree-marker-line") {
							return false; 
						}
						if($.vakata.dnd.is_drag && $.vakata.dnd.user_data.jstree) {
							if(this.data.dnd.i1) { clearInterval(this.data.dnd.i1); }
							if(this.data.dnd.i2) { clearInterval(this.data.dnd.i2); }
							if(this.data.dnd.to1) { clearTimeout(this.data.dnd.to1); }
							if(this.data.dnd.to2) { clearTimeout(this.data.dnd.to2); }
							if($.vakata.dnd.helper.children("ins").hasClass("jstree-ok")) {
								$.vakata.dnd.helper.children("ins").attr("class","jstree-invalid");
							}
						}
					}, this))
				.bind("mousemove.jstree", $.proxy(function (e) {
						if($.vakata.dnd.is_drag && $.vakata.dnd.user_data.jstree) {
							var cnt = this.get_container()[0];

							// Horizontal scroll
							if(e.pageX + 24 > this.data.dnd.cof.left + this.data.dnd.cw) {
								if(this.data.dnd.i1) { clearInterval(this.data.dnd.i1); }
								this.data.dnd.i1 = setInterval($.proxy(function () { this.scrollLeft += $.vakata.dnd.scroll_spd; }, cnt), 100);
							}
							else if(e.pageX - 24 < this.data.dnd.cof.left) {
								if(this.data.dnd.i1) { clearInterval(this.data.dnd.i1); }
								this.data.dnd.i1 = setInterval($.proxy(function () { this.scrollLeft -= $.vakata.dnd.scroll_spd; }, cnt), 100);
							}
							else {
								if(this.data.dnd.i1) { clearInterval(this.data.dnd.i1); }
							}

							// Vertical scroll
							if(e.pageY + 24 > this.data.dnd.cof.top + this.data.dnd.ch) {
								if(this.data.dnd.i2) { clearInterval(this.data.dnd.i2); }
								this.data.dnd.i2 = setInterval($.proxy(function () { this.scrollTop += $.vakata.dnd.scroll_spd; }, cnt), 100);
							}
							else if(e.pageY - 24 < this.data.dnd.cof.top) {
								if(this.data.dnd.i2) { clearInterval(this.data.dnd.i2); }
								this.data.dnd.i2 = setInterval($.proxy(function () { this.scrollTop -= $.vakata.dnd.scroll_spd; }, cnt), 100);
							}
							else {
								if(this.data.dnd.i2) { clearInterval(this.data.dnd.i2); }
							}

						}
					}, this))
				.bind("scroll.jstree", $.proxy(function (e) { 
						if($.vakata.dnd.is_drag && $.vakata.dnd.user_data.jstree && m && ml) {
							m.hide();
							ml.hide();
						}
					}, this))
				.delegate("a", "mousedown.jstree", $.proxy(function (e) { 
						if(e.which === 1) {
							this.start_drag(e.currentTarget, e);
							return false;
						}
					}, this))
				.delegate("a", "mouseenter.jstree", $.proxy(function (e) { 
						if($.vakata.dnd.is_drag && $.vakata.dnd.user_data.jstree) {
							this.dnd_enter(e.currentTarget);
						}
					}, this))
				.delegate("a", "mousemove.jstree", $.proxy(function (e) { 
						if($.vakata.dnd.is_drag && $.vakata.dnd.user_data.jstree) {
							if(!r || !r.length || r.children("a")[0] !== e.currentTarget) {
								this.dnd_enter(e.currentTarget);
							}
							if(typeof this.data.dnd.off.top === "undefined") { this.data.dnd.off = $(e.target).offset(); }
							this.data.dnd.w = (e.pageY - (this.data.dnd.off.top || 0)) % this.data.core.li_height;
							if(this.data.dnd.w < 0) { this.data.dnd.w += this.data.core.li_height; }
							this.dnd_show();
						}
					}, this))
				.delegate("a", "mouseleave.jstree", $.proxy(function (e) { 
						if($.vakata.dnd.is_drag && $.vakata.dnd.user_data.jstree) {
							if(e.relatedTarget && e.relatedTarget.id && e.relatedTarget.id === "jstree-marker-line") {
								return false; 
							}
								if(m) { m.hide(); }
								if(ml) { ml.hide(); }
							/*
							var ec = $(e.currentTarget).closest("li"), 
								er = $(e.relatedTarget).closest("li");
							if(er[0] !== ec.prev()[0] && er[0] !== ec.next()[0]) {
								if(m) { m.hide(); }
								if(ml) { ml.hide(); }
							}
							*/
							this.data.dnd.mto = setTimeout( 
								(function (t) { return function () { t.dnd_leave(e); }; })(this),
							0);
						}
					}, this))
				.delegate("a", "mouseup.jstree", $.proxy(function (e) { 
						if($.vakata.dnd.is_drag && $.vakata.dnd.user_data.jstree) {
							this.dnd_finish(e);
						}
					}, this));

			$(document)
				.bind("drag_stop.vakata", $.proxy(function () {
						if(this.data.dnd.to1) { clearTimeout(this.data.dnd.to1); }
						if(this.data.dnd.to2) { clearTimeout(this.data.dnd.to2); }
						if(this.data.dnd.i1) { clearInterval(this.data.dnd.i1); }
						if(this.data.dnd.i2) { clearInterval(this.data.dnd.i2); }
						this.data.dnd.after		= false;
						this.data.dnd.before	= false;
						this.data.dnd.inside	= false;
						this.data.dnd.off		= false;
						this.data.dnd.prepared	= false;
						this.data.dnd.w			= false;
						this.data.dnd.to1		= false;
						this.data.dnd.to2		= false;
						this.data.dnd.i1		= false;
						this.data.dnd.i2		= false;
						this.data.dnd.active	= false;
						this.data.dnd.foreign	= false;
						if(m) { m.css({ "top" : "-2000px" }); }
						if(ml) { ml.css({ "top" : "-2000px" }); }
					}, this))
				.bind("drag_start.vakata", $.proxy(function (e, data) {
						if(data.data.jstree) { 
							var et = $(data.event.target);
							if(et.closest(".jstree").hasClass("jstree-" + this.get_index())) {
								this.dnd_enter(et);
							}
						}
					}, this));
				/*
				.bind("keydown.jstree-" + this.get_index() + " keyup.jstree-" + this.get_index(), $.proxy(function(e) {
						if($.vakata.dnd.is_drag && $.vakata.dnd.user_data.jstree && !this.data.dnd.foreign) {
							var h = $.vakata.dnd.helper.children("ins");
							if(e[this._get_settings().dnd.copy_modifier + "Key"] && h.hasClass("jstree-ok")) {
								h.parent().html(h.parent().html().replace(/ \(Copy\)$/, "") + " (Copy)");
							} 
							else {
								h.parent().html(h.parent().html().replace(/ \(Copy\)$/, ""));
							}
						}
					}, this)); */



			var s = this._get_settings().dnd;
			if(s.drag_target) {
				$(document)
					.delegate(s.drag_target, "mousedown.jstree-" + this.get_index(), $.proxy(function (e) {
						o = e.target;
						$.vakata.dnd.drag_start(e, { jstree : true, obj : e.target }, "<ins class='jstree-icon'></ins>" + $(e.target).text() );
						if(this.data.themes) { 
							if(m) { m.attr("class", "jstree-" + this.data.themes.theme); }
							if(ml) { ml.attr("class", "jstree-" + this.data.themes.theme); }
							$.vakata.dnd.helper.attr("class", "jstree-dnd-helper jstree-" + this.data.themes.theme); 
						}
						$.vakata.dnd.helper.children("ins").attr("class","jstree-invalid");
						var cnt = this.get_container();
						this.data.dnd.cof = cnt.offset();
						this.data.dnd.cw = parseInt(cnt.width(),10);
						this.data.dnd.ch = parseInt(cnt.height(),10);
						this.data.dnd.foreign = true;
						e.preventDefault();
					}, this));
			}
			if(s.drop_target) {
				$(document)
					.delegate(s.drop_target, "mouseenter.jstree-" + this.get_index(), $.proxy(function (e) {
							if(this.data.dnd.active && this._get_settings().dnd.drop_check.call(this, { "o" : o, "r" : $(e.target), "e" : e })) {
								$.vakata.dnd.helper.children("ins").attr("class","jstree-ok");
							}
						}, this))
					.delegate(s.drop_target, "mouseleave.jstree-" + this.get_index(), $.proxy(function (e) {
							if(this.data.dnd.active) {
								$.vakata.dnd.helper.children("ins").attr("class","jstree-invalid");
							}
						}, this))
					.delegate(s.drop_target, "mouseup.jstree-" + this.get_index(), $.proxy(function (e) {
							if(this.data.dnd.active && $.vakata.dnd.helper.children("ins").hasClass("jstree-ok")) {
								this._get_settings().dnd.drop_finish.call(this, { "o" : o, "r" : $(e.target), "e" : e });
							}
						}, this));
			}
		},
		defaults : {
			copy_modifier	: "ctrl",
			check_timeout	: 100,
			open_timeout	: 500,
			drop_target		: ".jstree-drop",
			drop_check		: function (data) { return true; },
			drop_finish		: $.noop,
			drag_target		: ".jstree-draggable",
			drag_finish		: $.noop,
			drag_check		: function (data) { return { after : false, before : false, inside : true }; }
		},
		_fn : {
			dnd_prepare : function () {
				if(!r || !r.length) { return; }
				this.data.dnd.off = r.offset();
				if(this._get_settings().core.rtl) {
					this.data.dnd.off.right = this.data.dnd.off.left + r.width();
				}
				if(this.data.dnd.foreign) {
					var a = this._get_settings().dnd.drag_check.call(this, { "o" : o, "r" : r });
					this.data.dnd.after = a.after;
					this.data.dnd.before = a.before;
					this.data.dnd.inside = a.inside;
					this.data.dnd.prepared = true;
					return this.dnd_show();
				}
				this.prepare_move(o, r, "before");
				this.data.dnd.before = this.check_move();
				this.prepare_move(o, r, "after");
				this.data.dnd.after = this.check_move();
				if(this._is_loaded(r)) {
					this.prepare_move(o, r, "inside");
					this.data.dnd.inside = this.check_move();
				}
				else {
					this.data.dnd.inside = false;
				}
				this.data.dnd.prepared = true;
				return this.dnd_show();
			},
			dnd_show : function () {
				if(!this.data.dnd.prepared) { return; }
				var o = ["before","inside","after"],
					r = false,
					rtl = this._get_settings().core.rtl,
					pos;
				if(this.data.dnd.w < this.data.core.li_height/3) { o = ["before","inside","after"]; }
				else if(this.data.dnd.w <= this.data.core.li_height*2/3) {
					o = this.data.dnd.w < this.data.core.li_height/2 ? ["inside","before","after"] : ["inside","after","before"];
				}
				else { o = ["after","inside","before"]; }
				$.each(o, $.proxy(function (i, val) { 
					if(this.data.dnd[val]) {
						$.vakata.dnd.helper.children("ins").attr("class","jstree-ok");
						r = val;
						return false;
					}
				}, this));
				if(r === false) { $.vakata.dnd.helper.children("ins").attr("class","jstree-invalid"); }
				
				pos = rtl ? (this.data.dnd.off.right - 18) : (this.data.dnd.off.left + 10);
				switch(r) {
					case "before":
						m.css({ "left" : pos + "px", "top" : (this.data.dnd.off.top - 6) + "px" }).show();
						if(ml) { ml.css({ "left" : (pos + 8) + "px", "top" : (this.data.dnd.off.top - 1) + "px" }).show(); }
						break;
					case "after":
						m.css({ "left" : pos + "px", "top" : (this.data.dnd.off.top + this.data.core.li_height - 6) + "px" }).show();
						if(ml) { ml.css({ "left" : (pos + 8) + "px", "top" : (this.data.dnd.off.top + this.data.core.li_height - 1) + "px" }).show(); }
						break;
					case "inside":
						m.css({ "left" : pos + ( rtl ? -4 : 4) + "px", "top" : (this.data.dnd.off.top + this.data.core.li_height/2 - 5) + "px" }).show();
						if(ml) { ml.hide(); }
						break;
					default:
						m.hide();
						if(ml) { ml.hide(); }
						break;
				}
				last_pos = r;
				return r;
			},
			dnd_open : function () {
				this.data.dnd.to2 = false;
				this.open_node(r, $.proxy(this.dnd_prepare,this), true);
			},
			dnd_finish : function (e) {
				if(this.data.dnd.foreign) {
					if(this.data.dnd.after || this.data.dnd.before || this.data.dnd.inside) {
						this._get_settings().dnd.drag_finish.call(this, { "o" : o, "r" : r, "p" : last_pos });
					}
				}
				else {
					this.dnd_prepare();
					this.move_node(o, r, last_pos, e[this._get_settings().dnd.copy_modifier + "Key"]);
				}
				o = false;
				r = false;
				m.hide();
				if(ml) { ml.hide(); }
			},
			dnd_enter : function (obj) {
				if(this.data.dnd.mto) { 
					clearTimeout(this.data.dnd.mto);
					this.data.dnd.mto = false;
				}
				var s = this._get_settings().dnd;
				this.data.dnd.prepared = false;
				r = this._get_node(obj);
				if(s.check_timeout) { 
					// do the calculations after a minimal timeout (users tend to drag quickly to the desired location)
					if(this.data.dnd.to1) { clearTimeout(this.data.dnd.to1); }
					this.data.dnd.to1 = setTimeout($.proxy(this.dnd_prepare, this), s.check_timeout); 
				}
				else { 
					this.dnd_prepare(); 
				}
				if(s.open_timeout) { 
					if(this.data.dnd.to2) { clearTimeout(this.data.dnd.to2); }
					if(r && r.length && r.hasClass("jstree-closed")) { 
						// if the node is closed - open it, then recalculate
						this.data.dnd.to2 = setTimeout($.proxy(this.dnd_open, this), s.open_timeout);
					}
				}
				else {
					if(r && r.length && r.hasClass("jstree-closed")) { 
						this.dnd_open();
					}
				}
			},
			dnd_leave : function (e) {
				this.data.dnd.after		= false;
				this.data.dnd.before	= false;
				this.data.dnd.inside	= false;
				$.vakata.dnd.helper.children("ins").attr("class","jstree-invalid");
				m.hide();
				if(ml) { ml.hide(); }
				if(r && r[0] === e.target.parentNode) {
					if(this.data.dnd.to1) {
						clearTimeout(this.data.dnd.to1);
						this.data.dnd.to1 = false;
					}
					if(this.data.dnd.to2) {
						clearTimeout(this.data.dnd.to2);
						this.data.dnd.to2 = false;
					}
				}
			},
			start_drag : function (obj, e) {
				o = this._get_node(obj);
				if(this.data.ui && this.is_selected(o)) { o = this._get_node(null, true); }
				var dt = o.length > 1 ? this._get_string("multiple_selection") : this.get_text(o),
					cnt = this.get_container();
				if(!this._get_settings().core.html_titles) { dt = dt.replace(/</ig,"&lt;").replace(/>/ig,"&gt;"); }
				$.vakata.dnd.drag_start(e, { jstree : true, obj : o }, "<ins class='jstree-icon'></ins>" + dt );
				if(this.data.themes) { 
					if(m) { m.attr("class", "jstree-" + this.data.themes.theme); }
					if(ml) { ml.attr("class", "jstree-" + this.data.themes.theme); }
					$.vakata.dnd.helper.attr("class", "jstree-dnd-helper jstree-" + this.data.themes.theme); 
				}
				this.data.dnd.cof = cnt.offset();
				this.data.dnd.cw = parseInt(cnt.width(),10);
				this.data.dnd.ch = parseInt(cnt.height(),10);
				this.data.dnd.active = true;
			}
		}
	});
	$(function() {
		var css_string = '' + 
			'#vakata-dragged ins { display:block; text-decoration:none; width:16px; height:16px; margin:0 0 0 0; padding:0; position:absolute; top:4px; left:4px; ' + 
			' -moz-border-radius:4px; border-radius:4px; -webkit-border-radius:4px; ' +
			'} ' + 
			'#vakata-dragged .jstree-ok { background:green; } ' + 
			'#vakata-dragged .jstree-invalid { background:red; } ' + 
			'#jstree-marker { padding:0; margin:0; font-size:12px; overflow:hidden; height:12px; width:8px; position:absolute; top:-30px; z-index:10001; background-repeat:no-repeat; display:none; background-color:transparent; text-shadow:1px 1px 1px white; color:black; line-height:10px; } ' + 
			'#jstree-marker-line { padding:0; margin:0; line-height:0%; font-size:1px; overflow:hidden; height:1px; width:100px; position:absolute; top:-30px; z-index:10000; background-repeat:no-repeat; display:none; background-color:#456c43; ' + 
			' cursor:pointer; border:1px solid #eeeeee; border-left:0; -moz-box-shadow: 0px 0px 2px #666; -webkit-box-shadow: 0px 0px 2px #666; box-shadow: 0px 0px 2px #666; ' + 
			' -moz-border-radius:1px; border-radius:1px; -webkit-border-radius:1px; ' +
			'}' + 
			'';
		$.vakata.css.add_sheet({ str : css_string, title : "jstree" });
		m = $("<div />").attr({ id : "jstree-marker" }).hide().html("&raquo;")
			.bind("mouseleave mouseenter", function (e) { 
				m.hide();
				ml.hide();
				e.preventDefault(); 
				e.stopImmediatePropagation(); 
				return false; 
			})
			.appendTo("body");
		ml = $("<div />").attr({ id : "jstree-marker-line" }).hide()
			.bind("mouseup", function (e) { 
				if(r && r.length) { 
					r.children("a").trigger(e); 
					e.preventDefault(); 
					e.stopImmediatePropagation(); 
					return false; 
				} 
			})
			.bind("mouseleave", function (e) { 
				var rt = $(e.relatedTarget);
				if(rt.is(".jstree") || rt.closest(".jstree").length === 0) {
					if(r && r.length) { 
						r.children("a").trigger(e); 
						m.hide();
						ml.hide();
						e.preventDefault(); 
						e.stopImmediatePropagation(); 
						return false; 
					}
				}
			})
			.appendTo("body");
		$(document).bind("drag_start.vakata", function (e, data) {
			if(data.data.jstree) { m.show(); if(ml) { ml.show(); } }
		});
		$(document).bind("drag_stop.vakata", function (e, data) {
			if(data.data.jstree) { m.hide(); if(ml) { ml.hide(); } }
		});
	});
})(jQuery);
//*/

/*
 * jsTree checkbox plugin
 * Inserts checkboxes in front of every node
 * Depends on the ui plugin
 * DOES NOT WORK NICELY WITH MULTITREE DRAG'N'DROP
 */
(function ($) {
	$.jstree.plugin("checkbox", {
		__init : function () {
			this.data.checkbox.noui = this._get_settings().checkbox.override_ui;
			if(this.data.ui && this.data.checkbox.noui) {
				this.select_node = this.deselect_node = this.deselect_all = $.noop;
				this.get_selected = this.get_checked;
			}

			this.get_container()
				.bind("open_node.jstree create_node.jstree clean_node.jstree refresh.jstree", $.proxy(function (e, data) { 
						this._prepare_checkboxes(data.rslt.obj);
					}, this))
				.bind("loaded.jstree", $.proxy(function (e) {
						this._prepare_checkboxes();
					}, this))
				.delegate( (this.data.ui && this.data.checkbox.noui ? "a" : "ins.jstree-checkbox") , "click.jstree", $.proxy(function (e) {
						e.preventDefault();
						if(this._get_node(e.target).hasClass("jstree-checked")) { this.uncheck_node(e.target); }
						else { this.check_node(e.target); }
						if(this.data.ui && this.data.checkbox.noui) {
							this.save_selected();
							if(this.data.cookies) { this.save_cookie("select_node"); }
						}
						else {
							e.stopImmediatePropagation();
							return false;
						}
					}, this));
		},
		defaults : {
			override_ui : false,
			two_state : false,
			real_checkboxes : false,
			checked_parent_open : true,
			real_checkboxes_names : function (n) { return [ ("check_" + (n[0].id || Math.ceil(Math.random() * 10000))) , 1]; }
		},
		__destroy : function () {
			this.get_container()
				.find("input.jstree-real-checkbox").removeClass("jstree-real-checkbox").end()
				.find("ins.jstree-checkbox").remove();
		},
		_fn : {
			_checkbox_notify : function (n, data) {
				if(data.checked) {
					this.check_node(n, false);
				}
			},
			_prepare_checkboxes : function (obj) {
				obj = !obj || obj == -1 ? this.get_container().find("> ul > li") : this._get_node(obj);
				if(obj === false) { return; } // added for removing root nodes
				var c, _this = this, t, ts = this._get_settings().checkbox.two_state, rc = this._get_settings().checkbox.real_checkboxes, rcn = this._get_settings().checkbox.real_checkboxes_names;
				obj.each(function () {
					t = $(this);
					c = t.is("li") && (t.hasClass("jstree-checked") || (rc && t.children(":checked").length)) ? "jstree-checked" : "jstree-unchecked";
					t.find("li").andSelf().each(function () {
						var $t = $(this), nm;
						$t.children("a" + (_this.data.languages ? "" : ":eq(0)") ).not(":has(.jstree-checkbox)").prepend("<ins class='jstree-checkbox'>&#160;</ins>").parent().not(".jstree-checked, .jstree-unchecked").addClass( ts ? "jstree-unchecked" : c );
						if(rc) {
							if(!$t.children(":checkbox").length) {
								nm = rcn.call(_this, $t);
								$t.prepend("<input type='checkbox' class='jstree-real-checkbox' id='" + nm[0] + "' name='" + nm[0] + "' value='" + nm[1] + "' />");
							}
							else {
								$t.children(":checkbox").addClass("jstree-real-checkbox");
							}
						}
						if(!ts) {
							if(c === "jstree-checked" || $t.hasClass("jstree-checked") || $t.children(':checked').length) {
								$t.find("li").andSelf().addClass("jstree-checked").children(":checkbox").prop("checked", true);
							}
						}
						else {
							if($t.hasClass("jstree-checked") || $t.children(':checked').length) {
								$t.addClass("jstree-checked").children(":checkbox").prop("checked", true);
							}
						}
					});
				});
				if(!ts) {
					obj.find(".jstree-checked").parent().parent().each(function () { _this._repair_state(this); }); 
				}
			},
			change_state : function (obj, state) {
				obj = this._get_node(obj);
				var coll = false, rc = this._get_settings().checkbox.real_checkboxes;
				if(!obj || obj === -1) { return false; }
				state = (state === false || state === true) ? state : obj.hasClass("jstree-checked");
				if(this._get_settings().checkbox.two_state) {
					if(state) { 
						obj.removeClass("jstree-checked").addClass("jstree-unchecked"); 
						if(rc) { obj.children(":checkbox").prop("checked", false); }
					}
					else { 
						obj.removeClass("jstree-unchecked").addClass("jstree-checked"); 
						if(rc) { obj.children(":checkbox").prop("checked", true); }
					}
				}
				else {
					if(state) { 
						coll = obj.find("li").andSelf();
						if(!coll.filter(".jstree-checked, .jstree-undetermined").length) { return false; }
						coll.removeClass("jstree-checked jstree-undetermined").addClass("jstree-unchecked"); 
						if(rc) { coll.children(":checkbox").prop("checked", false); }
					}
					else { 
						coll = obj.find("li").andSelf();
						if(!coll.filter(".jstree-unchecked, .jstree-undetermined").length) { return false; }
						coll.removeClass("jstree-unchecked jstree-undetermined").addClass("jstree-checked"); 
						if(rc) { coll.children(":checkbox").prop("checked", true); }
						if(this.data.ui) { this.data.ui.last_selected = obj; }
						this.data.checkbox.last_selected = obj;
					}
					obj.parentsUntil(".jstree", "li").each(function () {
						var $this = $(this);
						if(state) {
							if($this.children("ul").children("li.jstree-checked, li.jstree-undetermined").length) {
								$this.parentsUntil(".jstree", "li").andSelf().removeClass("jstree-checked jstree-unchecked").addClass("jstree-undetermined");
								if(rc) { $this.parentsUntil(".jstree", "li").andSelf().children(":checkbox").prop("checked", false); }
								return false;
							}
							else {
								$this.removeClass("jstree-checked jstree-undetermined").addClass("jstree-unchecked");
								if(rc) { $this.children(":checkbox").prop("checked", false); }
							}
						}
						else {
							if($this.children("ul").children("li.jstree-unchecked, li.jstree-undetermined").length) {
								$this.parentsUntil(".jstree", "li").andSelf().removeClass("jstree-checked jstree-unchecked").addClass("jstree-undetermined");
								if(rc) { $this.parentsUntil(".jstree", "li").andSelf().children(":checkbox").prop("checked", false); }
								return false;
							}
							else {
								$this.removeClass("jstree-unchecked jstree-undetermined").addClass("jstree-checked");
								if(rc) { $this.children(":checkbox").prop("checked", true); }
							}
						}
					});
				}
				if(this.data.ui && this.data.checkbox.noui) { this.data.ui.selected = this.get_checked(); }
				this.__callback(obj);
				return true;
			},
			check_node : function (obj) {
				if(this.change_state(obj, false)) { 
					obj = this._get_node(obj);
					if(this._get_settings().checkbox.checked_parent_open) {
						var t = this;
						obj.parents(".jstree-closed").each(function () { t.open_node(this, false, true); });
					}
					this.__callback({ "obj" : obj }); 
				}
			},
			uncheck_node : function (obj) {
				if(this.change_state(obj, true)) { this.__callback({ "obj" : this._get_node(obj) }); }
			},
			check_all : function () {
				var _this = this, 
					coll = this._get_settings().checkbox.two_state ? this.get_container_ul().find("li") : this.get_container_ul().children("li");
				coll.each(function () {
					_this.change_state(this, false);
				});
				this.__callback();
			},
			uncheck_all : function () {
				var _this = this,
					coll = this._get_settings().checkbox.two_state ? this.get_container_ul().find("li") : this.get_container_ul().children("li");
				coll.each(function () {
					_this.change_state(this, true);
				});
				this.__callback();
			},

			is_checked : function(obj) {
				obj = this._get_node(obj);
				return obj.length ? obj.is(".jstree-checked") : false;
			},
			get_checked : function (obj, get_all) {
				obj = !obj || obj === -1 ? this.get_container() : this._get_node(obj);
				return get_all || this._get_settings().checkbox.two_state ? obj.find(".jstree-checked") : obj.find("> ul > .jstree-checked, .jstree-undetermined > ul > .jstree-checked");
			},
			get_unchecked : function (obj, get_all) { 
				obj = !obj || obj === -1 ? this.get_container() : this._get_node(obj);
				return get_all || this._get_settings().checkbox.two_state ? obj.find(".jstree-unchecked") : obj.find("> ul > .jstree-unchecked, .jstree-undetermined > ul > .jstree-unchecked");
			},

			show_checkboxes : function () { this.get_container().children("ul").removeClass("jstree-no-checkboxes"); },
			hide_checkboxes : function () { this.get_container().children("ul").addClass("jstree-no-checkboxes"); },

			_repair_state : function (obj) {
				obj = this._get_node(obj);
				if(!obj.length) { return; }
				if(this._get_settings().checkbox.two_state) {
					obj.find('li').andSelf().not('.jstree-checked').removeClass('jstree-undetermined').addClass('jstree-unchecked').children(':checkbox').prop('checked', true);
					return;
				}
				var rc = this._get_settings().checkbox.real_checkboxes,
					a = obj.find("> ul > .jstree-checked").length,
					b = obj.find("> ul > .jstree-undetermined").length,
					c = obj.find("> ul > li").length;
				if(c === 0) { if(obj.hasClass("jstree-undetermined")) { this.change_state(obj, false); } }
				else if(a === 0 && b === 0) { this.change_state(obj, true); }
				else if(a === c) { this.change_state(obj, false); }
				else { 
					obj.parentsUntil(".jstree","li").andSelf().removeClass("jstree-checked jstree-unchecked").addClass("jstree-undetermined");
					if(rc) { obj.parentsUntil(".jstree", "li").andSelf().children(":checkbox").prop("checked", false); }
				}
			},
			reselect : function () {
				if(this.data.ui && this.data.checkbox.noui) { 
					var _this = this,
						s = this.data.ui.to_select;
					s = $.map($.makeArray(s), function (n) { return "#" + n.toString().replace(/^#/,"").replace(/\\\//g,"/").replace(/\//g,"\\\/").replace(/\\\./g,".").replace(/\./g,"\\.").replace(/\:/g,"\\:"); });
					this.deselect_all();
					$.each(s, function (i, val) { _this.check_node(val); });
					this.__callback();
				}
				else { 
					this.__call_old(); 
				}
			},
			save_loaded : function () {
				var _this = this;
				this.data.core.to_load = [];
				this.get_container_ul().find("li.jstree-closed.jstree-undetermined").each(function () {
					if(this.id) { _this.data.core.to_load.push("#" + this.id); }
				});
			}
		}
	});
	$(function() {
		var css_string = '.jstree .jstree-real-checkbox { display:none; } ';
		$.vakata.css.add_sheet({ str : css_string, title : "jstree" });
	});
})(jQuery);
//*/

/* 
 * jsTree XML plugin
 * The XML data store. Datastores are build by overriding the `load_node` and `_is_loaded` functions.
 */
(function ($) {
	$.vakata.xslt = function (xml, xsl, callback) {
		var rs = "", xm, xs, processor, support;
		// TODO: IE9 no XSLTProcessor, no document.recalc
		if(document.recalc) {
			xm = document.createElement('xml');
			xs = document.createElement('xml');
			xm.innerHTML = xml;
			xs.innerHTML = xsl;
			$("body").append(xm).append(xs);
			setTimeout( (function (xm, xs, callback) {
				return function () {
					callback.call(null, xm.transformNode(xs.XMLDocument));
					setTimeout( (function (xm, xs) { return function () { $(xm).remove(); $(xs).remove(); }; })(xm, xs), 200);
				};
			})(xm, xs, callback), 100);
			return true;
		}
		if(typeof window.DOMParser !== "undefined" && typeof window.XMLHttpRequest !== "undefined" && typeof window.XSLTProcessor === "undefined") {
			xml = new DOMParser().parseFromString(xml, "text/xml");
			xsl = new DOMParser().parseFromString(xsl, "text/xml");
			// alert(xml.transformNode());
			// callback.call(null, new XMLSerializer().serializeToString(rs));
			
		}
		if(typeof window.DOMParser !== "undefined" && typeof window.XMLHttpRequest !== "undefined" && typeof window.XSLTProcessor !== "undefined") {
			processor = new XSLTProcessor();
			support = $.isFunction(processor.transformDocument) ? (typeof window.XMLSerializer !== "undefined") : true;
			if(!support) { return false; }
			xml = new DOMParser().parseFromString(xml, "text/xml");
			xsl = new DOMParser().parseFromString(xsl, "text/xml");
			if($.isFunction(processor.transformDocument)) {
				rs = document.implementation.createDocument("", "", null);
				processor.transformDocument(xml, xsl, rs, null);
				callback.call(null, new XMLSerializer().serializeToString(rs));
				return true;
			}
			else {
				processor.importStylesheet(xsl);
				rs = processor.transformToFragment(xml, document);
				callback.call(null, $("<div />").append(rs).html());
				return true;
			}
		}
		return false;
	};
	var xsl = {
		'nest' : '<' + '?xml version="1.0" encoding="utf-8" ?>' + 
			'<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >' + 
			'<xsl:output method="html" encoding="utf-8" omit-xml-declaration="yes" standalone="no" indent="no" media-type="text/html" />' + 
			'<xsl:template match="/">' + 
			'	<xsl:call-template name="nodes">' + 
			'		<xsl:with-param name="node" select="/root" />' + 
			'	</xsl:call-template>' + 
			'</xsl:template>' + 
			'<xsl:template name="nodes">' + 
			'	<xsl:param name="node" />' + 
			'	<ul>' + 
			'	<xsl:for-each select="$node/item">' + 
			'		<xsl:variable name="children" select="count(./item) &gt; 0" />' + 
			'		<li>' + 
			'			<xsl:attribute name="class">' + 
			'				<xsl:if test="position() = last()">jstree-last </xsl:if>' + 
			'				<xsl:choose>' + 
			'					<xsl:when test="@state = \'open\'">jstree-open </xsl:when>' + 
			'					<xsl:when test="$children or @hasChildren or @state = \'closed\'">jstree-closed </xsl:when>' + 
			'					<xsl:otherwise>jstree-leaf </xsl:otherwise>' + 
			'				</xsl:choose>' + 
			'				<xsl:value-of select="@class" />' + 
			'			</xsl:attribute>' + 
			'			<xsl:for-each select="@*">' + 
			'				<xsl:if test="name() != \'class\' and name() != \'state\' and name() != \'hasChildren\'">' + 
			'					<xsl:attribute name="{name()}"><xsl:value-of select="." /></xsl:attribute>' + 
			'				</xsl:if>' + 
			'			</xsl:for-each>' + 
			'	<ins class="jstree-icon"><xsl:text>&#xa0;</xsl:text></ins>' + 
			'			<xsl:for-each select="content/name">' + 
			'				<a>' + 
			'				<xsl:attribute name="href">' + 
			'					<xsl:choose>' + 
			'					<xsl:when test="@href"><xsl:value-of select="@href" /></xsl:when>' + 
			'					<xsl:otherwise>#</xsl:otherwise>' + 
			'					</xsl:choose>' + 
			'				</xsl:attribute>' + 
			'				<xsl:attribute name="class"><xsl:value-of select="@lang" /> <xsl:value-of select="@class" /></xsl:attribute>' + 
			'				<xsl:attribute name="style"><xsl:value-of select="@style" /></xsl:attribute>' + 
			'				<xsl:for-each select="@*">' + 
			'					<xsl:if test="name() != \'style\' and name() != \'class\' and name() != \'href\'">' + 
			'						<xsl:attribute name="{name()}"><xsl:value-of select="." /></xsl:attribute>' + 
			'					</xsl:if>' + 
			'				</xsl:for-each>' + 
			'					<ins>' + 
			'						<xsl:attribute name="class">jstree-icon ' + 
			'							<xsl:if test="string-length(attribute::icon) > 0 and not(contains(@icon,\'/\'))"><xsl:value-of select="@icon" /></xsl:if>' + 
			'						</xsl:attribute>' + 
			'						<xsl:if test="string-length(attribute::icon) > 0 and contains(@icon,\'/\')"><xsl:attribute name="style">background:url(<xsl:value-of select="@icon" />) center center no-repeat;</xsl:attribute></xsl:if>' + 
			'						<xsl:text>&#xa0;</xsl:text>' + 
			'					</ins>' + 
			'					<xsl:copy-of select="./child::node()" />' + 
			'				</a>' + 
			'			</xsl:for-each>' + 
			'			<xsl:if test="$children or @hasChildren"><xsl:call-template name="nodes"><xsl:with-param name="node" select="current()" /></xsl:call-template></xsl:if>' + 
			'		</li>' + 
			'	</xsl:for-each>' + 
			'	</ul>' + 
			'</xsl:template>' + 
			'</xsl:stylesheet>',

		'flat' : '<' + '?xml version="1.0" encoding="utf-8" ?>' + 
			'<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >' + 
			'<xsl:output method="html" encoding="utf-8" omit-xml-declaration="yes" standalone="no" indent="no" media-type="text/xml" />' + 
			'<xsl:template match="/">' + 
			'	<ul>' + 
			'	<xsl:for-each select="//item[not(@parent_id) or @parent_id=0 or not(@parent_id = //item/@id)]">' + /* the last `or` may be removed */
			'		<xsl:call-template name="nodes">' + 
			'			<xsl:with-param name="node" select="." />' + 
			'			<xsl:with-param name="is_last" select="number(position() = last())" />' + 
			'		</xsl:call-template>' + 
			'	</xsl:for-each>' + 
			'	</ul>' + 
			'</xsl:template>' + 
			'<xsl:template name="nodes">' + 
			'	<xsl:param name="node" />' + 
			'	<xsl:param name="is_last" />' + 
			'	<xsl:variable name="children" select="count(//item[@parent_id=$node/attribute::id]) &gt; 0" />' + 
			'	<li>' + 
			'	<xsl:attribute name="class">' + 
			'		<xsl:if test="$is_last = true()">jstree-last </xsl:if>' + 
			'		<xsl:choose>' + 
			'			<xsl:when test="@state = \'open\'">jstree-open </xsl:when>' + 
			'			<xsl:when test="$children or @hasChildren or @state = \'closed\'">jstree-closed </xsl:when>' + 
			'			<xsl:otherwise>jstree-leaf </xsl:otherwise>' + 
			'		</xsl:choose>' + 
			'		<xsl:value-of select="@class" />' + 
			'	</xsl:attribute>' + 
			'	<xsl:for-each select="@*">' + 
			'		<xsl:if test="name() != \'parent_id\' and name() != \'hasChildren\' and name() != \'class\' and name() != \'state\'">' + 
			'		<xsl:attribute name="{name()}"><xsl:value-of select="." /></xsl:attribute>' + 
			'		</xsl:if>' + 
			'	</xsl:for-each>' + 
			'	<ins class="jstree-icon"><xsl:text>&#xa0;</xsl:text></ins>' + 
			'	<xsl:for-each select="content/name">' + 
			'		<a>' + 
			'		<xsl:attribute name="href">' + 
			'			<xsl:choose>' + 
			'			<xsl:when test="@href"><xsl:value-of select="@href" /></xsl:when>' + 
			'			<xsl:otherwise>#</xsl:otherwise>' + 
			'			</xsl:choose>' + 
			'		</xsl:attribute>' + 
			'		<xsl:attribute name="class"><xsl:value-of select="@lang" /> <xsl:value-of select="@class" /></xsl:attribute>' + 
			'		<xsl:attribute name="style"><xsl:value-of select="@style" /></xsl:attribute>' + 
			'		<xsl:for-each select="@*">' + 
			'			<xsl:if test="name() != \'style\' and name() != \'class\' and name() != \'href\'">' + 
			'				<xsl:attribute name="{name()}"><xsl:value-of select="." /></xsl:attribute>' + 
			'			</xsl:if>' + 
			'		</xsl:for-each>' + 
			'			<ins>' + 
			'				<xsl:attribute name="class">jstree-icon ' + 
			'					<xsl:if test="string-length(attribute::icon) > 0 and not(contains(@icon,\'/\'))"><xsl:value-of select="@icon" /></xsl:if>' + 
			'				</xsl:attribute>' + 
			'				<xsl:if test="string-length(attribute::icon) > 0 and contains(@icon,\'/\')"><xsl:attribute name="style">background:url(<xsl:value-of select="@icon" />) center center no-repeat;</xsl:attribute></xsl:if>' + 
			'				<xsl:text>&#xa0;</xsl:text>' + 
			'			</ins>' + 
			'			<xsl:copy-of select="./child::node()" />' + 
			'		</a>' + 
			'	</xsl:for-each>' + 
			'	<xsl:if test="$children">' + 
			'		<ul>' + 
			'		<xsl:for-each select="//item[@parent_id=$node/attribute::id]">' + 
			'			<xsl:call-template name="nodes">' + 
			'				<xsl:with-param name="node" select="." />' + 
			'				<xsl:with-param name="is_last" select="number(position() = last())" />' + 
			'			</xsl:call-template>' + 
			'		</xsl:for-each>' + 
			'		</ul>' + 
			'	</xsl:if>' + 
			'	</li>' + 
			'</xsl:template>' + 
			'</xsl:stylesheet>'
	},
	escape_xml = function(string) {
		return string
			.toString()
			.replace(/&/g, '&amp;')
			.replace(/</g, '&lt;')
			.replace(/>/g, '&gt;')
			.replace(/"/g, '&quot;')
			.replace(/'/g, '&apos;');
	};
	$.jstree.plugin("xml_data", {
		defaults : { 
			data : false,
			ajax : false,
			xsl : "flat",
			clean_node : false,
			correct_state : true,
			get_skip_empty : false,
			get_include_preamble : true
		},
		_fn : {
			load_node : function (obj, s_call, e_call) { var _this = this; this.load_node_xml(obj, function () { _this.__callback({ "obj" : _this._get_node(obj) }); s_call.call(this); }, e_call); },
			_is_loaded : function (obj) { 
				var s = this._get_settings().xml_data;
				obj = this._get_node(obj);
				return obj == -1 || !obj || (!s.ajax && !$.isFunction(s.data)) || obj.is(".jstree-open, .jstree-leaf") || obj.children("ul").children("li").size() > 0;
			},
			load_node_xml : function (obj, s_call, e_call) {
				var s = this.get_settings().xml_data,
					error_func = function () {},
					success_func = function () {};

				obj = this._get_node(obj);
				if(obj && obj !== -1) {
					if(obj.data("jstree_is_loading")) { return; }
					else { obj.data("jstree_is_loading",true); }
				}
				switch(!0) {
					case (!s.data && !s.ajax): throw "Neither data nor ajax settings supplied.";
					case ($.isFunction(s.data)):
						s.data.call(this, obj, $.proxy(function (d) {
							this.parse_xml(d, $.proxy(function (d) {
								if(d) {
									d = d.replace(/ ?xmlns="[^"]*"/ig, "");
									if(d.length > 10) {
										d = $(d);
										if(obj === -1 || !obj) { this.get_container().children("ul").empty().append(d.children()); }
										else { obj.children("a.jstree-loading").removeClass("jstree-loading"); obj.append(d); obj.removeData("jstree_is_loading"); }
										if(s.clean_node) { this.clean_node(obj); }
										if(s_call) { s_call.call(this); }
									}
									else {
										if(obj && obj !== -1) { 
											obj.children("a.jstree-loading").removeClass("jstree-loading");
											obj.removeData("jstree_is_loading");
											if(s.correct_state) { 
												this.correct_state(obj);
												if(s_call) { s_call.call(this); } 
											}
										}
										else {
											if(s.correct_state) { 
												this.get_container().children("ul").empty();
												if(s_call) { s_call.call(this); } 
											}
										}
									}
								}
							}, this));
						}, this));
						break;
					case (!!s.data && !s.ajax) || (!!s.data && !!s.ajax && (!obj || obj === -1)):
						if(!obj || obj == -1) {
							this.parse_xml(s.data, $.proxy(function (d) {
								if(d) {
									d = d.replace(/ ?xmlns="[^"]*"/ig, "");
									if(d.length > 10) {
										d = $(d);
										this.get_container().children("ul").empty().append(d.children());
										if(s.clean_node) { this.clean_node(obj); }
										if(s_call) { s_call.call(this); }
									}
								}
								else { 
									if(s.correct_state) { 
										this.get_container().children("ul").empty(); 
										if(s_call) { s_call.call(this); }
									}
								}
							}, this));
						}
						break;
					case (!s.data && !!s.ajax) || (!!s.data && !!s.ajax && obj && obj !== -1):
						error_func = function (x, t, e) {
							var ef = this.get_settings().xml_data.ajax.error; 
							if(ef) { ef.call(this, x, t, e); }
							if(obj !== -1 && obj.length) {
								obj.children("a.jstree-loading").removeClass("jstree-loading");
								obj.removeData("jstree_is_loading");
								if(t === "success" && s.correct_state) { this.correct_state(obj); }
							}
							else {
								if(t === "success" && s.correct_state) { this.get_container().children("ul").empty(); }
							}
							if(e_call) { e_call.call(this); }
						};
						success_func = function (d, t, x) {
							d = x.responseText;
							var sf = this.get_settings().xml_data.ajax.success; 
							if(sf) { d = sf.call(this,d,t,x) || d; }
							if(d === "" || (d && d.toString && d.toString().replace(/^[\s\n]+$/,"") === "")) {
								return error_func.call(this, x, t, "");
							}
							this.parse_xml(d, $.proxy(function (d) {
								if(d) {
									d = d.replace(/ ?xmlns="[^"]*"/ig, "");
									if(d.length > 10) {
										d = $(d);
										if(obj === -1 || !obj) { this.get_container().children("ul").empty().append(d.children()); }
										else { obj.children("a.jstree-loading").removeClass("jstree-loading"); obj.append(d); obj.removeData("jstree_is_loading"); }
										if(s.clean_node) { this.clean_node(obj); }
										if(s_call) { s_call.call(this); }
									}
									else {
										if(obj && obj !== -1) { 
											obj.children("a.jstree-loading").removeClass("jstree-loading");
											obj.removeData("jstree_is_loading");
											if(s.correct_state) { 
												this.correct_state(obj);
												if(s_call) { s_call.call(this); } 
											}
										}
										else {
											if(s.correct_state) { 
												this.get_container().children("ul").empty();
												if(s_call) { s_call.call(this); } 
											}
										}
									}
								}
							}, this));
						};
						s.ajax.context = this;
						s.ajax.error = error_func;
						s.ajax.success = success_func;
						if(!s.ajax.dataType) { s.ajax.dataType = "xml"; }
						if($.isFunction(s.ajax.url)) { s.ajax.url = s.ajax.url.call(this, obj); }
						if($.isFunction(s.ajax.data)) { s.ajax.data = s.ajax.data.call(this, obj); }
						$.ajax(s.ajax);
						break;
				}
			},
			parse_xml : function (xml, callback) {
				var s = this._get_settings().xml_data;
				$.vakata.xslt(xml, xsl[s.xsl], callback);
			},
			get_xml : function (tp, obj, li_attr, a_attr, is_callback) {
				var result = "", 
					s = this._get_settings(), 
					_this = this,
					tmp1, tmp2, li, a, lang;
				if(!tp) { tp = "flat"; }
				if(!is_callback) { is_callback = 0; }
				obj = this._get_node(obj);
				if(!obj || obj === -1) { obj = this.get_container().find("> ul > li"); }
				li_attr = $.isArray(li_attr) ? li_attr : [ "id", "class" ];
				if(!is_callback && this.data.types && $.inArray(s.types.type_attr, li_attr) === -1) { li_attr.push(s.types.type_attr); }

				a_attr = $.isArray(a_attr) ? a_attr : [ ];

				if(!is_callback) { 
					if(s.xml_data.get_include_preamble) { 
						result += '<' + '?xml version="1.0" encoding="UTF-8"?' + '>'; 
					}
					result += "<root>"; 
				}
				obj.each(function () {
					result += "<item";
					li = $(this);
					$.each(li_attr, function (i, v) { 
						var t = li.attr(v);
						if(!s.xml_data.get_skip_empty || typeof t !== "undefined") {
							result += " " + v + "=\"" + escape_xml((" " + (t || "")).replace(/ jstree[^ ]*/ig,'').replace(/\s+$/ig," ").replace(/^ /,"").replace(/ $/,"")) + "\""; 
						}
					});
					if(li.hasClass("jstree-open")) { result += " state=\"open\""; }
					if(li.hasClass("jstree-closed")) { result += " state=\"closed\""; }
					if(tp === "flat") { result += " parent_id=\"" + escape_xml(is_callback) + "\""; }
					result += ">";
					result += "<content>";
					a = li.children("a");
					a.each(function () {
						tmp1 = $(this);
						lang = false;
						result += "<name";
						if($.inArray("languages", s.plugins) !== -1) {
							$.each(s.languages, function (k, z) {
								if(tmp1.hasClass(z)) { result += " lang=\"" + escape_xml(z) + "\""; lang = z; return false; }
							});
						}
						if(a_attr.length) { 
							$.each(a_attr, function (k, z) {
								var t = tmp1.attr(z);
								if(!s.xml_data.get_skip_empty || typeof t !== "undefined") {
									result += " " + z + "=\"" + escape_xml((" " + t || "").replace(/ jstree[^ ]*/ig,'').replace(/\s+$/ig," ").replace(/^ /,"").replace(/ $/,"")) + "\"";
								}
							});
						}
						if(tmp1.children("ins").get(0).className.replace(/jstree[^ ]*|$/ig,'').replace(/^\s+$/ig,"").length) {
							result += ' icon="' + escape_xml(tmp1.children("ins").get(0).className.replace(/jstree[^ ]*|$/ig,'').replace(/\s+$/ig," ").replace(/^ /,"").replace(/ $/,"")) + '"';
						}
						if(tmp1.children("ins").get(0).style.backgroundImage.length) {
							result += ' icon="' + escape_xml(tmp1.children("ins").get(0).style.backgroundImage.replace("url(","").replace(")","").replace(/'/ig,"").replace(/"/ig,"")) + '"';
						}
						result += ">";
						result += "<![CDATA[" + _this.get_text(tmp1, lang) + "]]>";
						result += "</name>";
					});
					result += "</content>";
					tmp2 = li[0].id || true;
					li = li.find("> ul > li");
					if(li.length) { tmp2 = _this.get_xml(tp, li, li_attr, a_attr, tmp2); }
					else { tmp2 = ""; }
					if(tp == "nest") { result += tmp2; }
					result += "</item>";
					if(tp == "flat") { result += tmp2; }
				});
				if(!is_callback) { result += "</root>"; }
				return result;
			}
		}
	});
})(jQuery);
//*/

/*
 * jsTree search plugin
 * Enables both sync and async search on the tree
 * DOES NOT WORK WITH JSON PROGRESSIVE RENDER
 */
(function ($) {
	$.expr[':'].jstree_contains = function(a,i,m){
		return (a.textContent || a.innerText || "").toLowerCase().indexOf(m[3].toLowerCase())>=0;
	};
	$.expr[':'].jstree_title_contains = function(a,i,m) {
		return (a.getAttribute("title") || "").toLowerCase().indexOf(m[3].toLowerCase())>=0;
	};
	$.jstree.plugin("search", {
		__init : function () {
			this.data.search.str = "";
			this.data.search.result = $();
			if(this._get_settings().search.show_only_matches) {
				this.get_container()
					.bind("search.jstree", function (e, data) {
						$(this).children("ul").find("li").hide().removeClass("jstree-last");
						data.rslt.nodes.parentsUntil(".jstree").andSelf().show()
							.filter("ul").each(function () { $(this).children("li:visible").eq(-1).addClass("jstree-last"); });
					})
					.bind("clear_search.jstree", function () {
						$(this).children("ul").find("li").css("display","").end().end().jstree("clean_node", -1);
					});
			}
		},
		defaults : {
			ajax : false,
			search_method : "jstree_contains", // for case insensitive - jstree_contains
			show_only_matches : false
		},
		_fn : {
			search : function (str, skip_async) {
				if($.trim(str) === "") { this.clear_search(); return; }
				var s = this.get_settings().search, 
					t = this,
					error_func = function () { },
					success_func = function () { };
				this.data.search.str = str;

				if(!skip_async && s.ajax !== false && this.get_container_ul().find("li.jstree-closed:not(:has(ul)):eq(0)").length > 0) {
					this.search.supress_callback = true;
					error_func = function () { };
					success_func = function (d, t, x) {
						var sf = this.get_settings().search.ajax.success; 
						if(sf) { d = sf.call(this,d,t,x) || d; }
						this.data.search.to_open = d;
						this._search_open();
					};
					s.ajax.context = this;
					s.ajax.error = error_func;
					s.ajax.success = success_func;
					if($.isFunction(s.ajax.url)) { s.ajax.url = s.ajax.url.call(this, str); }
					if($.isFunction(s.ajax.data)) { s.ajax.data = s.ajax.data.call(this, str); }
					if(!s.ajax.data) { s.ajax.data = { "search_string" : str }; }
					if(!s.ajax.dataType || /^json/.exec(s.ajax.dataType)) { s.ajax.dataType = "json"; }
					$.ajax(s.ajax);
					return;
				}
				if(this.data.search.result.length) { this.clear_search(); }
				this.data.search.result = this.get_container().find("a" + (this.data.languages ? "." + this.get_lang() : "" ) + ":" + (s.search_method) + "(" + this.data.search.str + ")");
				this.data.search.result.addClass("jstree-search").parent().parents(".jstree-closed").each(function () {
					t.open_node(this, false, true);
				});
				this.__callback({ nodes : this.data.search.result, str : str });
			},
			clear_search : function (str) {
				this.data.search.result.removeClass("jstree-search");
				this.__callback(this.data.search.result);
				this.data.search.result = $();
			},
			_search_open : function (is_callback) {
				var _this = this,
					done = true,
					current = [],
					remaining = [];
				if(this.data.search.to_open.length) {
					$.each(this.data.search.to_open, function (i, val) {
						if(val == "#") { return true; }
						if($(val).length && $(val).is(".jstree-closed")) { current.push(val); }
						else { remaining.push(val); }
					});
					if(current.length) {
						this.data.search.to_open = remaining;
						$.each(current, function (i, val) { 
							_this.open_node(val, function () { _this._search_open(true); }); 
						});
						done = false;
					}
				}
				if(done) { this.search(this.data.search.str, true); }
			}
		}
	});
})(jQuery);
//*/

/* 
 * jsTree contextmenu plugin
 */
(function ($) {
	$.vakata.context = {
		hide_on_mouseleave : false,

		cnt		: $("<div id='vakata-contextmenu' />"),
		vis		: false,
		tgt		: false,
		par		: false,
		func	: false,
		data	: false,
		rtl		: false,
		show	: function (s, t, x, y, d, p, rtl) {
			$.vakata.context.rtl = !!rtl;
			var html = $.vakata.context.parse(s), h, w;
			if(!html) { return; }
			$.vakata.context.vis = true;
			$.vakata.context.tgt = t;
			$.vakata.context.par = p || t || null;
			$.vakata.context.data = d || null;
			$.vakata.context.cnt
				.html(html)
				.css({ "visibility" : "hidden", "display" : "block", "left" : 0, "top" : 0 });

			if($.vakata.context.hide_on_mouseleave) {
				$.vakata.context.cnt
					.one("mouseleave", function(e) { $.vakata.context.hide(); });
			}

			h = $.vakata.context.cnt.height();
			w = $.vakata.context.cnt.width();
			if(x + w > $(document).width()) { 
				x = $(document).width() - (w + 5); 
				$.vakata.context.cnt.find("li > ul").addClass("right"); 
			}
			if(y + h > $(document).height()) { 
				y = y - (h + t[0].offsetHeight); 
				$.vakata.context.cnt.find("li > ul").addClass("bottom"); 
			}

			$.vakata.context.cnt
				.css({ "left" : x, "top" : y })
				.find("li:has(ul)")
					.bind("mouseenter", function (e) { 
						var w = $(document).width(),
							h = $(document).height(),
							ul = $(this).children("ul").show(); 
						if(w !== $(document).width()) { ul.toggleClass("right"); }
						if(h !== $(document).height()) { ul.toggleClass("bottom"); }
					})
					.bind("mouseleave", function (e) { 
						$(this).children("ul").hide(); 
					})
					.end()
				.css({ "visibility" : "visible" })
				.show();
			$(document).triggerHandler("context_show.vakata");
		},
		hide	: function () {
			$.vakata.context.vis = false;
			$.vakata.context.cnt.attr("class","").css({ "visibility" : "hidden" });
			$(document).triggerHandler("context_hide.vakata");
		},
		parse	: function (s, is_callback) {
			if(!s) { return false; }
			var str = "",
				tmp = false,
				was_sep = true;
			if(!is_callback) { $.vakata.context.func = {}; }
			str += "<ul>";
			$.each(s, function (i, val) {
				if(!val) { return true; }
				$.vakata.context.func[i] = val.action;
				if(!was_sep && val.separator_before) {
					str += "<li class='vakata-separator vakata-separator-before'></li>";
				}
				was_sep = false;
				str += "<li class='" + (val._class || "") + (val._disabled ? " jstree-contextmenu-disabled " : "") + "'><ins ";
				if(val.icon && val.icon.indexOf("/") === -1) { str += " class='" + val.icon + "' "; }
				if(val.icon && val.icon.indexOf("/") !== -1) { str += " style='background:url(" + val.icon + ") center center no-repeat;' "; }
				str += ">&#160;</ins><a href='#' rel='" + i + "'>";
				if(val.submenu) {
					str += "<span style='float:" + ($.vakata.context.rtl ? "left" : "right") + ";'>&raquo;</span>";
				}
				str += val.label + "</a>";
				if(val.submenu) {
					tmp = $.vakata.context.parse(val.submenu, true);
					if(tmp) { str += tmp; }
				}
				str += "</li>";
				if(val.separator_after) {
					str += "<li class='vakata-separator vakata-separator-after'></li>";
					was_sep = true;
				}
			});
			str = str.replace(/<li class\='vakata-separator vakata-separator-after'\><\/li\>$/,"");
			str += "</ul>";
			$(document).triggerHandler("context_parse.vakata");
			return str.length > 10 ? str : false;
		},
		exec	: function (i) {
			if($.isFunction($.vakata.context.func[i])) {
				// if is string - eval and call it!
				$.vakata.context.func[i].call($.vakata.context.data, $.vakata.context.par);
				return true;
			}
			else { return false; }
		}
	};
	$(function () {
		var css_string = '' + 
			'#vakata-contextmenu { display:block; visibility:hidden; left:0; top:-200px; position:absolute; margin:0; padding:0; min-width:180px; background:#ebebeb; border:1px solid silver; z-index:10000; *width:180px; } ' + 
			'#vakata-contextmenu ul { min-width:180px; *width:180px; } ' + 
			'#vakata-contextmenu ul, #vakata-contextmenu li { margin:0; padding:0; list-style-type:none; display:block; } ' + 
			/*'#vakata-contextmenu li { line-height:20px; min-height:20px; position:relative; padding:0px; } ' */ + 
			'#vakata-contextmenu li a { padding:1px 6px; line-height:17px; display:block; text-decoration:none; margin:1px 1px 0 1px; } ' + 
			'#vakata-contextmenu li a:hover, #vakata-contextmenu li.vakata-hover > a { background:gray; color:white; } ' + 
			'#vakata-contextmenu li ul { display:none; position:absolute; top:-2px; left:100%; background:#ebebeb; border:1px solid gray; } ' + 
			'#vakata-contextmenu .right { right:100%; left:auto; } ' + 
			'#vakata-contextmenu .bottom { bottom:-1px; top:auto; } ' + 
			'#vakata-contextmenu li.vakata-separator { min-height:0; height:1px; line-height:1px; font-size:1px; overflow:hidden; margin:0 2px; background:silver; /* border-top:1px solid #fefefe; */ padding:0; } ';
		$.vakata.css.add_sheet({ str : css_string, title : "vakata" });
		$.vakata.context.cnt
			.delegate("a","click", function (e) { e.preventDefault(); })
			.delegate("a","mouseup", function (e) {
				if(!$(this).parent().hasClass("jstree-contextmenu-disabled") && $.vakata.context.exec($(this).attr("rel"))) {
					$.vakata.context.hide();
				}
				else { $(this).blur(); }
			})
			.delegate("a","mouseover", function () {
				$.vakata.context.cnt.find(".vakata-hover").removeClass("vakata-hover");
			})
			.appendTo("body");
		$(document).bind("mousedown", function (e) { if($.vakata.context.vis && !$.contains($.vakata.context.cnt[0], e.target)) { $.vakata.context.hide(); } });
		if(typeof $.hotkeys !== "undefined") {
			$(document)
				.bind("keydown", "up", function (e) { 
					if($.vakata.context.vis) { 
						var o = $.vakata.context.cnt.find("ul:visible").last().children(".vakata-hover").removeClass("vakata-hover").prevAll("li:not(.vakata-separator)").first();
						if(!o.length) { o = $.vakata.context.cnt.find("ul:visible").last().children("li:not(.vakata-separator)").last(); }
						o.addClass("vakata-hover");
						e.stopImmediatePropagation(); 
						e.preventDefault();
					} 
				})
				.bind("keydown", "down", function (e) { 
					if($.vakata.context.vis) { 
						var o = $.vakata.context.cnt.find("ul:visible").last().children(".vakata-hover").removeClass("vakata-hover").nextAll("li:not(.vakata-separator)").first();
						if(!o.length) { o = $.vakata.context.cnt.find("ul:visible").last().children("li:not(.vakata-separator)").first(); }
						o.addClass("vakata-hover");
						e.stopImmediatePropagation(); 
						e.preventDefault();
					} 
				})
				.bind("keydown", "right", function (e) { 
					if($.vakata.context.vis) { 
						$.vakata.context.cnt.find(".vakata-hover").children("ul").show().children("li:not(.vakata-separator)").removeClass("vakata-hover").first().addClass("vakata-hover");
						e.stopImmediatePropagation(); 
						e.preventDefault();
					} 
				})
				.bind("keydown", "left", function (e) { 
					if($.vakata.context.vis) { 
						$.vakata.context.cnt.find(".vakata-hover").children("ul").hide().children(".vakata-separator").removeClass("vakata-hover");
						e.stopImmediatePropagation(); 
						e.preventDefault();
					} 
				})
				.bind("keydown", "esc", function (e) { 
					$.vakata.context.hide(); 
					e.preventDefault();
				})
				.bind("keydown", "space", function (e) { 
					$.vakata.context.cnt.find(".vakata-hover").last().children("a").click();
					e.preventDefault();
				});
		}
	});

	$.jstree.plugin("contextmenu", {
		__init : function () {
			this.get_container()
				.delegate("a", "contextmenu.jstree", $.proxy(function (e) {
						e.preventDefault();
						if(!$(e.currentTarget).hasClass("jstree-loading")) {
							this.show_contextmenu(e.currentTarget, e.pageX, e.pageY);
						}
					}, this))
				.delegate("a", "click.jstree", $.proxy(function (e) {
						if(this.data.contextmenu) {
							$.vakata.context.hide();
						}
					}, this))
				.bind("destroy.jstree", $.proxy(function () {
						// TODO: move this to descruct method
						if(this.data.contextmenu) {
							$.vakata.context.hide();
						}
					}, this));
			$(document).bind("context_hide.vakata", $.proxy(function () { this.data.contextmenu = false; }, this));
		},
		defaults : { 
			select_node : false, // requires UI plugin
			show_at_node : true,
			items : { // Could be a function that should return an object like this one
				"create" : {
					"separator_before"	: false,
					"separator_after"	: true,
					"label"				: "Create",
					"action"			: function (obj) { this.create(obj); }
				},
				"rename" : {
					"separator_before"	: false,
					"separator_after"	: false,
					"label"				: "Rename",
					"action"			: function (obj) { this.rename(obj); }
				},
				"remove" : {
					"separator_before"	: false,
					"icon"				: false,
					"separator_after"	: false,
					"label"				: "Delete",
					"action"			: function (obj) { if(this.is_selected(obj)) { this.remove(); } else { this.remove(obj); } }
				},
				"ccp" : {
					"separator_before"	: true,
					"icon"				: false,
					"separator_after"	: false,
					"label"				: "Edit",
					"action"			: false,
					"submenu" : { 
						"cut" : {
							"separator_before"	: false,
							"separator_after"	: false,
							"label"				: "Cut",
							"action"			: function (obj) { this.cut(obj); }
						},
						"copy" : {
							"separator_before"	: false,
							"icon"				: false,
							"separator_after"	: false,
							"label"				: "Copy",
							"action"			: function (obj) { this.copy(obj); }
						},
						"paste" : {
							"separator_before"	: false,
							"icon"				: false,
							"separator_after"	: false,
							"label"				: "Paste",
							"action"			: function (obj) { this.paste(obj); }
						}
					}
				}
			}
		},
		_fn : {
			show_contextmenu : function (obj, x, y) {
				obj = this._get_node(obj);
				var s = this.get_settings().contextmenu,
					a = obj.children("a:visible:eq(0)"),
					o = false,
					i = false;
				if(s.select_node && this.data.ui && !this.is_selected(obj)) {
					this.deselect_all();
					this.select_node(obj, true);
				}
				if(s.show_at_node || typeof x === "undefined" || typeof y === "undefined") {
					o = a.offset();
					x = o.left;
					y = o.top + this.data.core.li_height;
				}
				i = obj.data("jstree") && obj.data("jstree").contextmenu ? obj.data("jstree").contextmenu : s.items;
				if($.isFunction(i)) { i = i.call(this, obj); }
				this.data.contextmenu = true;
				$.vakata.context.show(i, a, x, y, this, obj, this._get_settings().core.rtl);
				if(this.data.themes) { $.vakata.context.cnt.attr("class", "jstree-" + this.data.themes.theme + "-context"); }
			}
		}
	});
})(jQuery);
//*/

/* 
 * jsTree types plugin
 * Adds support types of nodes
 * You can set an attribute on each li node, that represents its type.
 * According to the type setting the node may get custom icon/validation rules
 */
(function ($) {
	$.jstree.plugin("types", {
		__init : function () {
			var s = this._get_settings().types;
			this.data.types.attach_to = [];
			this.get_container()
				.bind("init.jstree", $.proxy(function () { 
						var types = s.types, 
							attr  = s.type_attr, 
							icons_css = "", 
							_this = this;

						$.each(types, function (i, tp) {
							$.each(tp, function (k, v) { 
								if(!/^(max_depth|max_children|icon|valid_children)$/.test(k)) { _this.data.types.attach_to.push(k); }
							});
							if(!tp.icon) { return true; }
							if( tp.icon.image || tp.icon.position) {
								if(i == "default")	{ icons_css += '.jstree-' + _this.get_index() + ' a > .jstree-icon { '; }
								else				{ icons_css += '.jstree-' + _this.get_index() + ' li[' + attr + '="' + i + '"] > a > .jstree-icon { '; }
								if(tp.icon.image)	{ icons_css += ' background-image:url(' + tp.icon.image + '); '; }
								if(tp.icon.position){ icons_css += ' background-position:' + tp.icon.position + '; '; }
								else				{ icons_css += ' background-position:0 0; '; }
								icons_css += '} ';
							}
						});
						if(icons_css !== "") { $.vakata.css.add_sheet({ 'str' : icons_css, title : "jstree-types" }); }
					}, this))
				.bind("before.jstree", $.proxy(function (e, data) { 
						var s, t, 
							o = this._get_settings().types.use_data ? this._get_node(data.args[0]) : false, 
							d = o && o !== -1 && o.length ? o.data("jstree") : false;
						if(d && d.types && d.types[data.func] === false) { e.stopImmediatePropagation(); return false; }
						if($.inArray(data.func, this.data.types.attach_to) !== -1) {
							if(!data.args[0] || (!data.args[0].tagName && !data.args[0].jquery)) { return; }
							s = this._get_settings().types.types;
							t = this._get_type(data.args[0]);
							if(
								( 
									(s[t] && typeof s[t][data.func] !== "undefined") || 
									(s["default"] && typeof s["default"][data.func] !== "undefined") 
								) && this._check(data.func, data.args[0]) === false
							) {
								e.stopImmediatePropagation();
								return false;
							}
						}
					}, this));
			if(is_ie6) {
				this.get_container()
					.bind("load_node.jstree set_type.jstree", $.proxy(function (e, data) {
							var r = data && data.rslt && data.rslt.obj && data.rslt.obj !== -1 ? this._get_node(data.rslt.obj).parent() : this.get_container_ul(),
								c = false,
								s = this._get_settings().types;
							$.each(s.types, function (i, tp) {
								if(tp.icon && (tp.icon.image || tp.icon.position)) {
									c = i === "default" ? r.find("li > a > .jstree-icon") : r.find("li[" + s.type_attr + "='" + i + "'] > a > .jstree-icon");
									if(tp.icon.image) { c.css("backgroundImage","url(" + tp.icon.image + ")"); }
									c.css("backgroundPosition", tp.icon.position || "0 0");
								}
							});
						}, this));
			}
		},
		defaults : {
			// defines maximum number of root nodes (-1 means unlimited, -2 means disable max_children checking)
			max_children		: -1,
			// defines the maximum depth of the tree (-1 means unlimited, -2 means disable max_depth checking)
			max_depth			: -1,
			// defines valid node types for the root nodes
			valid_children		: "all",

			// whether to use $.data
			use_data : false, 
			// where is the type stores (the rel attribute of the LI element)
			type_attr : "rel",
			// a list of types
			types : {
				// the default type
				"default" : {
					"max_children"	: -1,
					"max_depth"		: -1,
					"valid_children": "all"

					// Bound functions - you can bind any other function here (using boolean or function)
					//"select_node"	: true
				}
			}
		},
		_fn : {
			_types_notify : function (n, data) {
				if(data.type && this._get_settings().types.use_data) {
					this.set_type(data.type, n);
				}
			},
			_get_type : function (obj) {
				obj = this._get_node(obj);
				return (!obj || !obj.length) ? false : obj.attr(this._get_settings().types.type_attr) || "default";
			},
			set_type : function (str, obj) {
				obj = this._get_node(obj);
				var ret = (!obj.length || !str) ? false : obj.attr(this._get_settings().types.type_attr, str);
				if(ret) { this.__callback({ obj : obj, type : str}); }
				return ret;
			},
			_check : function (rule, obj, opts) {
				obj = this._get_node(obj);
				var v = false, t = this._get_type(obj), d = 0, _this = this, s = this._get_settings().types, data = false;
				if(obj === -1) { 
					if(!!s[rule]) { v = s[rule]; }
					else { return; }
				}
				else {
					if(t === false) { return; }
					data = s.use_data ? obj.data("jstree") : false;
					if(data && data.types && typeof data.types[rule] !== "undefined") { v = data.types[rule]; }
					else if(!!s.types[t] && typeof s.types[t][rule] !== "undefined") { v = s.types[t][rule]; }
					else if(!!s.types["default"] && typeof s.types["default"][rule] !== "undefined") { v = s.types["default"][rule]; }
				}
				if($.isFunction(v)) { v = v.call(this, obj); }
				if(rule === "max_depth" && obj !== -1 && opts !== false && s.max_depth !== -2 && v !== 0) {
					// also include the node itself - otherwise if root node it is not checked
					obj.children("a:eq(0)").parentsUntil(".jstree","li").each(function (i) {
						// check if current depth already exceeds global tree depth
						if(s.max_depth !== -1 && s.max_depth - (i + 1) <= 0) { v = 0; return false; }
						d = (i === 0) ? v : _this._check(rule, this, false);
						// check if current node max depth is already matched or exceeded
						if(d !== -1 && d - (i + 1) <= 0) { v = 0; return false; }
						// otherwise - set the max depth to the current value minus current depth
						if(d >= 0 && (d - (i + 1) < v || v < 0) ) { v = d - (i + 1); }
						// if the global tree depth exists and it minus the nodes calculated so far is less than `v` or `v` is unlimited
						if(s.max_depth >= 0 && (s.max_depth - (i + 1) < v || v < 0) ) { v = s.max_depth - (i + 1); }
					});
				}
				return v;
			},
			check_move : function () {
				if(!this.__call_old()) { return false; }
				var m  = this._get_move(),
					s  = m.rt._get_settings().types,
					mc = m.rt._check("max_children", m.cr),
					md = m.rt._check("max_depth", m.cr),
					vc = m.rt._check("valid_children", m.cr),
					ch = 0, d = 1, t;

				if(vc === "none") { return false; } 
				if($.isArray(vc) && m.ot && m.ot._get_type) {
					m.o.each(function () {
						if($.inArray(m.ot._get_type(this), vc) === -1) { d = false; return false; }
					});
					if(d === false) { return false; }
				}
				if(s.max_children !== -2 && mc !== -1) {
					ch = m.cr === -1 ? this.get_container().find("> ul > li").not(m.o).length : m.cr.find("> ul > li").not(m.o).length;
					if(ch + m.o.length > mc) { return false; }
				}
				if(s.max_depth !== -2 && md !== -1) {
					d = 0;
					if(md === 0) { return false; }
					if(typeof m.o.d === "undefined") {
						// TODO: deal with progressive rendering and async when checking max_depth (how to know the depth of the moved node)
						t = m.o;
						while(t.length > 0) {
							t = t.find("> ul > li");
							d ++;
						}
						m.o.d = d;
					}
					if(md - m.o.d < 0) { return false; }
				}
				return true;
			},
			create_node : function (obj, position, js, callback, is_loaded, skip_check) {
				if(!skip_check && (is_loaded || this._is_loaded(obj))) {
					var p  = (typeof position == "string" && position.match(/^before|after$/i) && obj !== -1) ? this._get_parent(obj) : this._get_node(obj),
						s  = this._get_settings().types,
						mc = this._check("max_children", p),
						md = this._check("max_depth", p),
						vc = this._check("valid_children", p),
						ch;
					if(typeof js === "string") { js = { data : js }; }
					if(!js) { js = {}; }
					if(vc === "none") { return false; } 
					if($.isArray(vc)) {
						if(!js.attr || !js.attr[s.type_attr]) { 
							if(!js.attr) { js.attr = {}; }
							js.attr[s.type_attr] = vc[0]; 
						}
						else {
							if($.inArray(js.attr[s.type_attr], vc) === -1) { return false; }
						}
					}
					if(s.max_children !== -2 && mc !== -1) {
						ch = p === -1 ? this.get_container().find("> ul > li").length : p.find("> ul > li").length;
						if(ch + 1 > mc) { return false; }
					}
					if(s.max_depth !== -2 && md !== -1 && (md - 1) < 0) { return false; }
				}
				return this.__call_old(true, obj, position, js, callback, is_loaded, skip_check);
			}
		}
	});
})(jQuery);
//*/

/* 
 * jsTree HTML plugin
 * The HTML data store. Datastores are build by replacing the `load_node` and `_is_loaded` functions.
 */
(function ($) {
	$.jstree.plugin("html_data", {
		__init : function () { 
			// this used to use html() and clean the whitespace, but this way any attached data was lost
			this.data.html_data.original_container_html = this.get_container().find(" > ul > li").clone(true);
			// remove white space from LI node - otherwise nodes appear a bit to the right
			this.data.html_data.original_container_html.find("li").andSelf().contents().filter(function() { return this.nodeType == 3; }).remove();
		},
		defaults : { 
			data : false,
			ajax : false,
			correct_state : true
		},
		_fn : {
			load_node : function (obj, s_call, e_call) { var _this = this; this.load_node_html(obj, function () { _this.__callback({ "obj" : _this._get_node(obj) }); s_call.call(this); }, e_call); },
			_is_loaded : function (obj) { 
				obj = this._get_node(obj); 
				return obj == -1 || !obj || (!this._get_settings().html_data.ajax && !$.isFunction(this._get_settings().html_data.data)) || obj.is(".jstree-open, .jstree-leaf") || obj.children("ul").children("li").size() > 0;
			},
			load_node_html : function (obj, s_call, e_call) {
				var d,
					s = this.get_settings().html_data,
					error_func = function () {},
					success_func = function () {};
				obj = this._get_node(obj);
				if(obj && obj !== -1) {
					if(obj.data("jstree_is_loading")) { return; }
					else { obj.data("jstree_is_loading",true); }
				}
				switch(!0) {
					case ($.isFunction(s.data)):
						s.data.call(this, obj, $.proxy(function (d) {
							if(d && d !== "" && d.toString && d.toString().replace(/^[\s\n]+$/,"") !== "") {
								d = $(d);
								if(!d.is("ul")) { d = $("<ul />").append(d); }
								if(obj == -1 || !obj) { this.get_container().children("ul").empty().append(d.children()).find("li, a").filter(function () { return !this.firstChild || !this.firstChild.tagName || this.firstChild.tagName !== "INS"; }).prepend("<ins class='jstree-icon'>&#160;</ins>").end().filter("a").children("ins:first-child").not(".jstree-icon").addClass("jstree-icon"); }
								else { obj.children("a.jstree-loading").removeClass("jstree-loading"); obj.append(d).children("ul").find("li, a").filter(function () { return !this.firstChild || !this.firstChild.tagName || this.firstChild.tagName !== "INS"; }).prepend("<ins class='jstree-icon'>&#160;</ins>").end().filter("a").children("ins:first-child").not(".jstree-icon").addClass("jstree-icon"); obj.removeData("jstree_is_loading"); }
								this.clean_node(obj);
								if(s_call) { s_call.call(this); }
							}
							else {
								if(obj && obj !== -1) {
									obj.children("a.jstree-loading").removeClass("jstree-loading");
									obj.removeData("jstree_is_loading");
									if(s.correct_state) { 
										this.correct_state(obj);
										if(s_call) { s_call.call(this); } 
									}
								}
								else {
									if(s.correct_state) { 
										this.get_container().children("ul").empty();
										if(s_call) { s_call.call(this); } 
									}
								}
							}
						}, this));
						break;
					case (!s.data && !s.ajax):
						if(!obj || obj == -1) {
							this.get_container()
								.children("ul").empty()
								.append(this.data.html_data.original_container_html)
								.find("li, a").filter(function () { return !this.firstChild || !this.firstChild.tagName || this.firstChild.tagName !== "INS"; }).prepend("<ins class='jstree-icon'>&#160;</ins>").end()
								.filter("a").children("ins:first-child").not(".jstree-icon").addClass("jstree-icon");
							this.clean_node();
						}
						if(s_call) { s_call.call(this); }
						break;
					case (!!s.data && !s.ajax) || (!!s.data && !!s.ajax && (!obj || obj === -1)):
						if(!obj || obj == -1) {
							d = $(s.data);
							if(!d.is("ul")) { d = $("<ul />").append(d); }
							this.get_container()
								.children("ul").empty().append(d.children())
								.find("li, a").filter(function () { return !this.firstChild || !this.firstChild.tagName || this.firstChild.tagName !== "INS"; }).prepend("<ins class='jstree-icon'>&#160;</ins>").end()
								.filter("a").children("ins:first-child").not(".jstree-icon").addClass("jstree-icon");
							this.clean_node();
						}
						if(s_call) { s_call.call(this); }
						break;
					case (!s.data && !!s.ajax) || (!!s.data && !!s.ajax && obj && obj !== -1):
						obj = this._get_node(obj);
						error_func = function (x, t, e) {
							var ef = this.get_settings().html_data.ajax.error; 
							if(ef) { ef.call(this, x, t, e); }
							if(obj != -1 && obj.length) {
								obj.children("a.jstree-loading").removeClass("jstree-loading");
								obj.removeData("jstree_is_loading");
								if(t === "success" && s.correct_state) { this.correct_state(obj); }
							}
							else {
								if(t === "success" && s.correct_state) { this.get_container().children("ul").empty(); }
							}
							if(e_call) { e_call.call(this); }
						};
						success_func = function (d, t, x) {
							var sf = this.get_settings().html_data.ajax.success; 
							if(sf) { d = sf.call(this,d,t,x) || d; }
							if(d === "" || (d && d.toString && d.toString().replace(/^[\s\n]+$/,"") === "")) {
								return error_func.call(this, x, t, "");
							}
							if(d) {
								d = $(d);
								if(!d.is("ul")) { d = $("<ul />").append(d); }
								if(obj == -1 || !obj) { this.get_container().children("ul").empty().append(d.children()).find("li, a").filter(function () { return !this.firstChild || !this.firstChild.tagName || this.firstChild.tagName !== "INS"; }).prepend("<ins class='jstree-icon'>&#160;</ins>").end().filter("a").children("ins:first-child").not(".jstree-icon").addClass("jstree-icon"); }
								else { obj.children("a.jstree-loading").removeClass("jstree-loading"); obj.append(d).children("ul").find("li, a").filter(function () { return !this.firstChild || !this.firstChild.tagName || this.firstChild.tagName !== "INS"; }).prepend("<ins class='jstree-icon'>&#160;</ins>").end().filter("a").children("ins:first-child").not(".jstree-icon").addClass("jstree-icon"); obj.removeData("jstree_is_loading"); }
								this.clean_node(obj);
								if(s_call) { s_call.call(this); }
							}
							else {
								if(obj && obj !== -1) {
									obj.children("a.jstree-loading").removeClass("jstree-loading");
									obj.removeData("jstree_is_loading");
									if(s.correct_state) { 
										this.correct_state(obj);
										if(s_call) { s_call.call(this); } 
									}
								}
								else {
									if(s.correct_state) { 
										this.get_container().children("ul").empty();
										if(s_call) { s_call.call(this); } 
									}
								}
							}
						};
						s.ajax.context = this;
						s.ajax.error = error_func;
						s.ajax.success = success_func;
						if(!s.ajax.dataType) { s.ajax.dataType = "html"; }
						if($.isFunction(s.ajax.url)) { s.ajax.url = s.ajax.url.call(this, obj); }
						if($.isFunction(s.ajax.data)) { s.ajax.data = s.ajax.data.call(this, obj); }
						$.ajax(s.ajax);
						break;
				}
			}
		}
	});
	// include the HTML data plugin by default
	$.jstree.defaults.plugins.push("html_data");
})(jQuery);
//*/

/* 
 * jsTree themeroller plugin
 * Adds support for jQuery UI themes. Include this at the end of your plugins list, also make sure "themes" is not included.
 */
(function ($) {
	$.jstree.plugin("themeroller", {
		__init : function () {
			var s = this._get_settings().themeroller;
			this.get_container()
				.addClass("ui-widget-content")
				.addClass("jstree-themeroller")
				.delegate("a","mouseenter.jstree", function (e) {
					if(!$(e.currentTarget).hasClass("jstree-loading")) {
						$(this).addClass(s.item_h);
					}
				})
				.delegate("a","mouseleave.jstree", function () {
					$(this).removeClass(s.item_h);
				})
				.bind("init.jstree", $.proxy(function (e, data) { 
						data.inst.get_container().find("> ul > li > .jstree-loading > ins").addClass("ui-icon-refresh");
						this._themeroller(data.inst.get_container().find("> ul > li"));
					}, this))
				.bind("open_node.jstree create_node.jstree", $.proxy(function (e, data) { 
						this._themeroller(data.rslt.obj);
					}, this))
				.bind("loaded.jstree refresh.jstree", $.proxy(function (e) {
						this._themeroller();
					}, this))
				.bind("close_node.jstree", $.proxy(function (e, data) {
						this._themeroller(data.rslt.obj);
					}, this))
				.bind("delete_node.jstree", $.proxy(function (e, data) {
						this._themeroller(data.rslt.parent);
					}, this))
				.bind("correct_state.jstree", $.proxy(function (e, data) {
						data.rslt.obj
							.children("ins.jstree-icon").removeClass(s.opened + " " + s.closed + " ui-icon").end()
							.find("> a > ins.ui-icon")
								.filter(function() { 
									return this.className.toString()
										.replace(s.item_clsd,"").replace(s.item_open,"").replace(s.item_leaf,"")
										.indexOf("ui-icon-") === -1; 
								}).removeClass(s.item_open + " " + s.item_clsd).addClass(s.item_leaf || "jstree-no-icon");
					}, this))
				.bind("select_node.jstree", $.proxy(function (e, data) {
						data.rslt.obj.children("a").addClass(s.item_a);
					}, this))
				.bind("deselect_node.jstree deselect_all.jstree", $.proxy(function (e, data) {
						this.get_container()
							.find("a." + s.item_a).removeClass(s.item_a).end()
							.find("a.jstree-clicked").addClass(s.item_a);
					}, this))
				.bind("dehover_node.jstree", $.proxy(function (e, data) {
						data.rslt.obj.children("a").removeClass(s.item_h);
					}, this))
				.bind("hover_node.jstree", $.proxy(function (e, data) {
						this.get_container()
							.find("a." + s.item_h).not(data.rslt.obj).removeClass(s.item_h);
						data.rslt.obj.children("a").addClass(s.item_h);
					}, this))
				.bind("move_node.jstree", $.proxy(function (e, data) {
						this._themeroller(data.rslt.o);
						this._themeroller(data.rslt.op);
					}, this));
		},
		__destroy : function () {
			var s = this._get_settings().themeroller,
				c = [ "ui-icon" ];
			$.each(s, function (i, v) {
				v = v.split(" ");
				if(v.length) { c = c.concat(v); }
			});
			this.get_container()
				.removeClass("ui-widget-content")
				.find("." + c.join(", .")).removeClass(c.join(" "));
		},
		_fn : {
			_themeroller : function (obj) {
				var s = this._get_settings().themeroller;
				obj = !obj || obj == -1 ? this.get_container_ul() : this._get_node(obj).parent();
				obj
					.find("li.jstree-closed")
						.children("ins.jstree-icon").removeClass(s.opened).addClass("ui-icon " + s.closed).end()
						.children("a").addClass(s.item)
							.children("ins.jstree-icon").addClass("ui-icon")
								.filter(function() { 
									return this.className.toString()
										.replace(s.item_clsd,"").replace(s.item_open,"").replace(s.item_leaf,"")
										.indexOf("ui-icon-") === -1; 
								}).removeClass(s.item_leaf + " " + s.item_open).addClass(s.item_clsd || "jstree-no-icon")
								.end()
							.end()
						.end()
					.end()
					.find("li.jstree-open")
						.children("ins.jstree-icon").removeClass(s.closed).addClass("ui-icon " + s.opened).end()
						.children("a").addClass(s.item)
							.children("ins.jstree-icon").addClass("ui-icon")
								.filter(function() { 
									return this.className.toString()
										.replace(s.item_clsd,"").replace(s.item_open,"").replace(s.item_leaf,"")
										.indexOf("ui-icon-") === -1; 
								}).removeClass(s.item_leaf + " " + s.item_clsd).addClass(s.item_open || "jstree-no-icon")
								.end()
							.end()
						.end()
					.end()
					.find("li.jstree-leaf")
						.children("ins.jstree-icon").removeClass(s.closed + " ui-icon " + s.opened).end()
						.children("a").addClass(s.item)
							.children("ins.jstree-icon").addClass("ui-icon")
								.filter(function() { 
									return this.className.toString()
										.replace(s.item_clsd,"").replace(s.item_open,"").replace(s.item_leaf,"")
										.indexOf("ui-icon-") === -1; 
								}).removeClass(s.item_clsd + " " + s.item_open).addClass(s.item_leaf || "jstree-no-icon");
			}
		},
		defaults : {
			"opened"	: "ui-icon-triangle-1-se",
			"closed"	: "ui-icon-triangle-1-e",
			"item"		: "ui-state-default",
			"item_h"	: "ui-state-hover",
			"item_a"	: "ui-state-active",
			"item_open"	: "ui-icon-folder-open",
			"item_clsd"	: "ui-icon-folder-collapsed",
			"item_leaf"	: "ui-icon-document"
		}
	});
	$(function() {
		var css_string = '' + 
			'.jstree-themeroller .ui-icon { overflow:visible; } ' + 
			'.jstree-themeroller a { padding:0 2px; } ' + 
			'.jstree-themeroller .jstree-no-icon { display:none; }';
		$.vakata.css.add_sheet({ str : css_string, title : "jstree" });
	});
})(jQuery);
//*/

/* 
 * jsTree unique plugin
 * Forces different names amongst siblings (still a bit experimental)
 * NOTE: does not check language versions (it will not be possible to have nodes with the same title, even in different languages)
 */
(function ($) {
	$.jstree.plugin("unique", {
		__init : function () {
			this.get_container()
				.bind("before.jstree", $.proxy(function (e, data) { 
						var nms = [], res = true, p, t;
						if(data.func == "move_node") {
							// obj, ref, position, is_copy, is_prepared, skip_check
							if(data.args[4] === true) {
								if(data.args[0].o && data.args[0].o.length) {
									data.args[0].o.children("a").each(function () { nms.push($(this).text().replace(/^\s+/g,"")); });
									res = this._check_unique(nms, data.args[0].np.find("> ul > li").not(data.args[0].o), "move_node");
								}
							}
						}
						if(data.func == "create_node") {
							// obj, position, js, callback, is_loaded
							if(data.args[4] || this._is_loaded(data.args[0])) {
								p = this._get_node(data.args[0]);
								if(data.args[1] && (data.args[1] === "before" || data.args[1] === "after")) {
									p = this._get_parent(data.args[0]);
									if(!p || p === -1) { p = this.get_container(); }
								}
								if(typeof data.args[2] === "string") { nms.push(data.args[2]); }
								else if(!data.args[2] || !data.args[2].data) { nms.push(this._get_string("new_node")); }
								else { nms.push(data.args[2].data); }
								res = this._check_unique(nms, p.find("> ul > li"), "create_node");
							}
						}
						if(data.func == "rename_node") {
							// obj, val
							nms.push(data.args[1]);
							t = this._get_node(data.args[0]);
							p = this._get_parent(t);
							if(!p || p === -1) { p = this.get_container(); }
							res = this._check_unique(nms, p.find("> ul > li").not(t), "rename_node");
						}
						if(!res) {
							e.stopPropagation();
							return false;
						}
					}, this));
		},
		defaults : { 
			error_callback : $.noop
		},
		_fn : { 
			_check_unique : function (nms, p, func) {
				var cnms = [];
				p.children("a").each(function () { cnms.push($(this).text().replace(/^\s+/g,"")); });
				if(!cnms.length || !nms.length) { return true; }
				cnms = cnms.sort().join(",,").replace(/(,|^)([^,]+)(,,\2)+(,|$)/g,"$1$2$4").replace(/,,+/g,",").replace(/,$/,"").split(",");
				if((cnms.length + nms.length) != cnms.concat(nms).sort().join(",,").replace(/(,|^)([^,]+)(,,\2)+(,|$)/g,"$1$2$4").replace(/,,+/g,",").replace(/,$/,"").split(",").length) {
					this._get_settings().unique.error_callback.call(null, nms, p, func);
					return false;
				}
				return true;
			},
			check_move : function () {
				if(!this.__call_old()) { return false; }
				var p = this._get_move(), nms = [];
				if(p.o && p.o.length) {
					p.o.children("a").each(function () { nms.push($(this).text().replace(/^\s+/g,"")); });
					return this._check_unique(nms, p.np.find("> ul > li").not(p.o), "check_move");
				}
				return true;
			}
		}
	});
})(jQuery);
//*/

/*
 * jsTree wholerow plugin
 * Makes select and hover work on the entire width of the node
 * MAY BE HEAVY IN LARGE DOM
 */
(function ($) {
	$.jstree.plugin("wholerow", {
		__init : function () {
			if(!this.data.ui) { throw "jsTree wholerow: jsTree UI plugin not included."; }
			this.data.wholerow.html = false;
			this.data.wholerow.to = false;
			this.get_container()
				.bind("init.jstree", $.proxy(function (e, data) { 
						this._get_settings().core.animation = 0;
					}, this))
				.bind("open_node.jstree create_node.jstree clean_node.jstree loaded.jstree", $.proxy(function (e, data) { 
						this._prepare_wholerow_span( data && data.rslt && data.rslt.obj ? data.rslt.obj : -1 );
					}, this))
				.bind("search.jstree clear_search.jstree reopen.jstree after_open.jstree after_close.jstree create_node.jstree delete_node.jstree clean_node.jstree", $.proxy(function (e, data) { 
						if(this.data.to) { clearTimeout(this.data.to); }
						this.data.to = setTimeout( (function (t, o) { return function() { t._prepare_wholerow_ul(o); }; })(this,  data && data.rslt && data.rslt.obj ? data.rslt.obj : -1), 0);
					}, this))
				.bind("deselect_all.jstree", $.proxy(function (e, data) { 
						this.get_container().find(" > .jstree-wholerow .jstree-clicked").removeClass("jstree-clicked " + (this.data.themeroller ? this._get_settings().themeroller.item_a : "" ));
					}, this))
				.bind("select_node.jstree deselect_node.jstree ", $.proxy(function (e, data) { 
						data.rslt.obj.each(function () { 
							var ref = data.inst.get_container().find(" > .jstree-wholerow li:visible:eq(" + ( parseInt((($(this).offset().top - data.inst.get_container().offset().top + data.inst.get_container()[0].scrollTop) / data.inst.data.core.li_height),10)) + ")");
							// ref.children("a")[e.type === "select_node" ? "addClass" : "removeClass"]("jstree-clicked");
							ref.children("a").attr("class",data.rslt.obj.children("a").attr("class"));
						});
					}, this))
				.bind("hover_node.jstree dehover_node.jstree", $.proxy(function (e, data) { 
						this.get_container().find(" > .jstree-wholerow .jstree-hovered").removeClass("jstree-hovered " + (this.data.themeroller ? this._get_settings().themeroller.item_h : "" ));
						if(e.type === "hover_node") {
							var ref = this.get_container().find(" > .jstree-wholerow li:visible:eq(" + ( parseInt(((data.rslt.obj.offset().top - this.get_container().offset().top + this.get_container()[0].scrollTop) / this.data.core.li_height),10)) + ")");
							// ref.children("a").addClass("jstree-hovered");
							ref.children("a").attr("class",data.rslt.obj.children(".jstree-hovered").attr("class"));
						}
					}, this))
				.delegate(".jstree-wholerow-span, ins.jstree-icon, li", "click.jstree", function (e) {
						var n = $(e.currentTarget);
						if(e.target.tagName === "A" || (e.target.tagName === "INS" && n.closest("li").is(".jstree-open, .jstree-closed"))) { return; }
						n.closest("li").children("a:visible:eq(0)").click();
						e.stopImmediatePropagation();
					})
				.delegate("li", "mouseover.jstree", $.proxy(function (e) {
						e.stopImmediatePropagation();
						if($(e.currentTarget).children(".jstree-hovered, .jstree-clicked").length) { return false; }
						this.hover_node(e.currentTarget);
						return false;
					}, this))
				.delegate("li", "mouseleave.jstree", $.proxy(function (e) {
						if($(e.currentTarget).children("a").hasClass("jstree-hovered").length) { return; }
						this.dehover_node(e.currentTarget);
					}, this));
			if(is_ie7 || is_ie6) {
				$.vakata.css.add_sheet({ str : ".jstree-" + this.get_index() + " { position:relative; } ", title : "jstree" });
			}
		},
		defaults : {
		},
		__destroy : function () {
			this.get_container().children(".jstree-wholerow").remove();
			this.get_container().find(".jstree-wholerow-span").remove();
		},
		_fn : {
			_prepare_wholerow_span : function (obj) {
				obj = !obj || obj == -1 ? this.get_container().find("> ul > li") : this._get_node(obj);
				if(obj === false) { return; } // added for removing root nodes
				obj.each(function () {
					$(this).find("li").andSelf().each(function () {
						var $t = $(this);
						if($t.children(".jstree-wholerow-span").length) { return true; }
						$t.prepend("<span class='jstree-wholerow-span' style='width:" + ($t.parentsUntil(".jstree","li").length * 18) + "px;'>&#160;</span>");
					});
				});
			},
			_prepare_wholerow_ul : function () {
				var o = this.get_container().children("ul").eq(0), h = o.html();
				o.addClass("jstree-wholerow-real");
				if(this.data.wholerow.last_html !== h) {
					this.data.wholerow.last_html = h;
					this.get_container().children(".jstree-wholerow").remove();
					this.get_container().append(
						o.clone().removeClass("jstree-wholerow-real")
							.wrapAll("<div class='jstree-wholerow' />").parent()
							.width(o.parent()[0].scrollWidth)
							.css("top", (o.height() + ( is_ie7 ? 5 : 0)) * -1 )
							.find("li[id]").each(function () { this.removeAttribute("id"); }).end()
					);
				}
			}
		}
	});
	$(function() {
		var css_string = '' + 
			'.jstree .jstree-wholerow-real { position:relative; z-index:1; } ' + 
			'.jstree .jstree-wholerow-real li { cursor:pointer; } ' + 
			'.jstree .jstree-wholerow-real a { border-left-color:transparent !important; border-right-color:transparent !important; } ' + 
			'.jstree .jstree-wholerow { position:relative; z-index:0; height:0; } ' + 
			'.jstree .jstree-wholerow ul, .jstree .jstree-wholerow li { width:100%; } ' + 
			'.jstree .jstree-wholerow, .jstree .jstree-wholerow ul, .jstree .jstree-wholerow li, .jstree .jstree-wholerow a { margin:0 !important; padding:0 !important; } ' + 
			'.jstree .jstree-wholerow, .jstree .jstree-wholerow ul, .jstree .jstree-wholerow li { background:transparent !important; }' + 
			'.jstree .jstree-wholerow ins, .jstree .jstree-wholerow span, .jstree .jstree-wholerow input { display:none !important; }' + 
			'.jstree .jstree-wholerow a, .jstree .jstree-wholerow a:hover { text-indent:-9999px; !important; width:100%; padding:0 !important; border-right-width:0px !important; border-left-width:0px !important; } ' + 
			'.jstree .jstree-wholerow-span { position:absolute; left:0; margin:0px; padding:0; height:18px; border-width:0; padding:0; z-index:0; }';
		if(is_ff2) {
			css_string += '' + 
				'.jstree .jstree-wholerow a { display:block; height:18px; margin:0; padding:0; border:0; } ' + 
				'.jstree .jstree-wholerow-real a { border-color:transparent !important; } ';
		}
		if(is_ie7 || is_ie6) {
			css_string += '' + 
				'.jstree .jstree-wholerow, .jstree .jstree-wholerow li, .jstree .jstree-wholerow ul, .jstree .jstree-wholerow a { margin:0; padding:0; line-height:18px; } ' + 
				'.jstree .jstree-wholerow a { display:block; height:18px; line-height:18px; overflow:hidden; } ';
		}
		$.vakata.css.add_sheet({ str : css_string, title : "jstree" });
	});
})(jQuery);
//*/

/*
* jsTree model plugin
* This plugin gets jstree to use a class model to retrieve data, creating great dynamism
*/
(function ($) {
	var nodeInterface = ["getChildren","getChildrenCount","getAttr","getName","getProps"],
		validateInterface = function(obj, inter) {
			var valid = true;
			obj = obj || {};
			inter = [].concat(inter);
			$.each(inter, function (i, v) {
				if(!$.isFunction(obj[v])) { valid = false; return false; }
			});
			return valid;
		};
	$.jstree.plugin("model", {
		__init : function () {
			if(!this.data.json_data) { throw "jsTree model: jsTree json_data plugin not included."; }
			this._get_settings().json_data.data = function (n, b) {
				var obj = (n == -1) ? this._get_settings().model.object : n.data("jstree_model");
				if(!validateInterface(obj, nodeInterface)) { return b.call(null, false); }
				if(this._get_settings().model.async) {
					obj.getChildren($.proxy(function (data) {
						this.model_done(data, b);
					}, this));
				}
				else {
					this.model_done(obj.getChildren(), b);
				}
			};
		},
		defaults : {
			object : false,
			id_prefix : false,
			async : false
		},
		_fn : {
			model_done : function (data, callback) {
				var ret = [], 
					s = this._get_settings(),
					_this = this;

				if(!$.isArray(data)) { data = [data]; }
				$.each(data, function (i, nd) {
					var r = nd.getProps() || {};
					r.attr = nd.getAttr() || {};
					if(nd.getChildrenCount()) { r.state = "closed"; }
					r.data = nd.getName();
					if(!$.isArray(r.data)) { r.data = [r.data]; }
					if(_this.data.types && $.isFunction(nd.getType)) {
						r.attr[s.types.type_attr] = nd.getType();
					}
					if(r.attr.id && s.model.id_prefix) { r.attr.id = s.model.id_prefix + r.attr.id; }
					if(!r.metadata) { r.metadata = { }; }
					r.metadata.jstree_model = nd;
					ret.push(r);
				});
				callback.call(null, ret);
			}
		}
	});
})(jQuery);
//*/

})();
;
/**
 * @file
 * Javascript required for a simple collapsible div.
 *
 * Creating a collapsible div with this doesn't take too much. There are
 * three classes necessary:
 *
 * - ctools-collapsible-container: This is the overall container that will be
 *   collapsible. This must be a div.
 * - ctools-collapsible-handle: This is the title area, and is what will be
 *   visible when it is collapsed. This can be any block element, such as div
 *   or h2.
 * - ctools-collapsible-content: This is the ocntent area and will only be
 *   visible when expanded. This must be a div.
 *
 * Adding 'ctools-collapsible-remember' to the container class will cause the
 * state of the container to be stored in a cookie, and remembered from page
 * load to page load. This will only work if the container has a unique ID, so
 * very carefully add IDs to your containers.
 *
 * If the class 'ctools-no-container' is placed on the container, the container
 * will be the handle. The content will be found by appending '-content' to the
 * id of the handle. The ctools-collapsible-handle and
 * ctools-collapsible-content classes will not be required in that case, and no
 * restrictions on what of data the container is are placed. Like
 * ctools-collapsible-remember this requires an id to eist.
 *
 * The content will be 'open' unless the container class has 'ctools-collapsed'
 * as a class, which will cause the container to draw collapsed.
 */

(function ($) {
  // All CTools tools begin with this if they need to use the CTools namespace.
  if (!Drupal.CTools) {
    Drupal.CTools = {};
  }

  /**
   * Object to store state.
   *
   * This object will remember the state of collapsible containers. The first
   * time a state is requested, it will check the cookie and set up the variable.
   * If a state has been changed, when the window is unloaded the state will be
   * saved.
   */
  Drupal.CTools.Collapsible = {
    state: {},
    stateLoaded: false,
    stateChanged: false,
    cookieString: 'ctools-collapsible-state=',

    /**
     * Get the current collapsed state of a container.
     *
     * If set to 1, the container is open. If set to -1, the container is
     * collapsed. If unset the state is unknown, and the default state should
     * be used.
     */
    getState: function (id) {
      if (!this.stateLoaded) {
        this.loadCookie();
      }

      return this.state[id];
    },

    /**
     * Set the collapsed state of a container for subsequent page loads.
     *
     * Set the state to 1 for open, -1 for collapsed.
     */
    setState: function (id, state) {
      if (!this.stateLoaded) {
        this.loadCookie();
      }

      this.state[id] = state;

      if (!this.stateChanged) {
        this.stateChanged = true;
        $(window).unload(this.unload);
      }
    },

    /**
     * Check the cookie and load the state variable.
     */
    loadCookie: function () {
      // If there is a previous instance of this cookie
      if (document.cookie.length > 0) {
        // Get the number of characters that have the list of values
        // from our string index.
        offset = document.cookie.indexOf(this.cookieString);

        // If its positive, there is a list!
        if (offset != -1) {
          offset += this.cookieString.length;
          var end = document.cookie.indexOf(';', offset);
          if (end == -1) {
            end = document.cookie.length;
          }

          // Get a list of all values that are saved on our string
          var cookie = unescape(document.cookie.substring(offset, end));

          if (cookie != '') {
            var cookieList = cookie.split(',');
            for (var i = 0; i < cookieList.length; i++) {
              var info = cookieList[i].split(':');
              this.state[info[0]] = info[1];
            }
          }
        }
      }

      this.stateLoaded = true;
    },

    /**
     * Turn the state variable into a string and store it in the cookie.
     */
    storeCookie: function () {
      var cookie = '';

      // Get a list of IDs, saparated by comma
      for (i in this.state) {
        if (cookie != '') {
          cookie += ',';
        }
        cookie += i + ':' + this.state[i];
      }

      // Save this values on the cookie
      document.cookie = this.cookieString + escape(cookie) + ';path=/';
    },

    /**
     * Respond to the unload event by storing the current state.
     */
    unload: function() {
      Drupal.CTools.Collapsible.storeCookie();
    }
  };

  // Set up an array for callbacks.
  Drupal.CTools.CollapsibleCallbacks = [];
  Drupal.CTools.CollapsibleCallbacksAfterToggle = [];

  /**
   * Bind collapsible behavior to a given container.
   */
  Drupal.CTools.bindCollapsible = function () {
    var $container = $(this);

    // Allow the specification of the 'no container' class, which means the
    // handle and the container can be completely independent.
    if ($container.hasClass('ctools-no-container') && $container.attr('id')) {
      // In this case, the container *is* the handle and the content is found
      // by adding '-content' to the id. Obviously, an id is required.
      var handle = $container;
      var content = $('#' + $container.attr('id') + '-content');
    }
    else {
      var handle = $container.children('.ctools-collapsible-handle');
      var content = $container.children('div.ctools-collapsible-content');
    }

    if (content.length) {
      // Create the toggle item and place it in front of the toggle.
      var toggle = $('<span class="ctools-toggle"></span>');
      handle.before(toggle);

      // If the remember class is set, check to see if we have a remembered
      // state stored.
      if ($container.hasClass('ctools-collapsible-remember') && $container.attr('id')) {
        var state = Drupal.CTools.Collapsible.getState($container.attr('id'));
        if (state == 1) {
          $container.removeClass('ctools-collapsed');
        }
        else if (state == -1) {
          $container.addClass('ctools-collapsed');
        }
      }

      // If we should start collapsed, do so:
      if ($container.hasClass('ctools-collapsed')) {
        toggle.toggleClass('ctools-toggle-collapsed');
        content.hide();
      }

      var afterToggle = function () {
        if (Drupal.CTools.CollapsibleCallbacksAfterToggle) {
          for (i in Drupal.CTools.CollapsibleCallbacksAfterToggle) {
            Drupal.CTools.CollapsibleCallbacksAfterToggle[i]($container, handle, content, toggle);
          }
        }
      }

      var clickMe = function () {
        if (Drupal.CTools.CollapsibleCallbacks) {
          for (i in Drupal.CTools.CollapsibleCallbacks) {
            Drupal.CTools.CollapsibleCallbacks[i]($container, handle, content, toggle);
          }
        }

        // If the container is a table element slideToggle does not do what
        // we want, so use toggle() instead.
        if ($container.is('table')) {
          content.toggle(0, afterToggle);
        }
        else {
          content.slideToggle(100, afterToggle);
        }

        toggle.toggleClass('ctools-toggle-collapsed');

        // If we're supposed to remember the state of this class, do so.
        if ($container.hasClass('ctools-collapsible-remember') && $container.attr('id')) {
          var state = toggle.hasClass('ctools-toggle-collapsed') ? -1 : 1;
          Drupal.CTools.Collapsible.setState($container.attr('id'), state);
        }

        return false;
      }

      // Let both the toggle and the handle be clickable.
      toggle.click(clickMe);
      handle.click(clickMe);
    }
  };

  /**
   * Support Drupal's 'behaviors' system for binding.
   */
  Drupal.behaviors.CToolsCollapsible = {
    attach: function(context) {
      $('.ctools-collapsible-container', context).once('ctools-collapsible', Drupal.CTools.bindCollapsible);
    }
  }
})(jQuery);
;
/*
 * jQuery UI Multiselect
 *
 * Authors:
 *  Michael Aufreiter (quasipartikel.at)
 *  Yanick Rochon (yanick.rochon[at]gmail[dot]com)
 *
 * Dual licensed under the MIT (MIT-LICENSE.txt)
 * and GPL (GPL-LICENSE.txt) licenses.
 *
 * http://www.quasipartikel.at/multiselect/
 *
 *
 * Depends:
 *	ui.core.js
 *	ui.sortable.js
 *
 * Optional:
 * localization (http://plugins.jquery.com/project/localisation)
 * scrollTo (http://plugins.jquery.com/project/ScrollTo)
 *
 * Todo:
 *  Make batch actions faster
 *  Implement dynamic insertion through remote calls
 */


(function($) {

$.widget("ui.multiselect", {
	options: {
		sortable: true,
		dragToAdd: true,
		searchable: true,
		doubleClickable: true,
		animated: 'fast',
		show: 'slideDown',
		hide: 'slideUp',
		dividerLocation: 0.6,
		selectedContainerOnLeft: true,
		width: null, 
		height: null,
		single: false,
		nodeComparator: function(node1,node2) {
			var text1 = node1.text(),
			    text2 = node2.text();
			return text1 == text2 ? 0 : (text1 < text2 ? -1 : 1);
		},
		includeRemoveAll: true,
		includeAddAll: true,
		pressEnterKeyToAddAll: false
	},
	_create: function() {
		this.element.hide();
		this.id = this.element.attr("id");
		this.container = $('<div class="ui-multiselect ui-helper-clearfix ui-widget"></div>').insertAfter(this.element);
		this.container.css('clear','both');
		this.count = 0; // number of currently selected options
		this.selectedContainer = $('<div class="selected"></div>');
		if (this.options.selectedContainerOnLeft) {
			this.selectedContainer.appendTo(this.container);
			this.availableContainer = $('<div class="available"></div>').appendTo(this.container);
			this.availableContainer.addClass('right-column');
		} else {
			this.availableContainer = $('<div class="available"></div>').appendTo(this.container);
			this.selectedContainer.appendTo(this.container);
			this.selectedContainer.addClass('right-column');
		}
		this.selectedActions = $('<div class="actions ui-widget-header ui-helper-clearfix"><span class="count">0 '+$.ui.multiselect.locale.itemsCount+'</span>'+(this.options.includeRemoveAll?'<a href="#" class="remove-all">'+$.ui.multiselect.locale.removeAll+'</a>':'<span class="remove-all">&nbsp;</span>')+'</div>').appendTo(this.selectedContainer);
		this.availableActions = $('<div class="actions ui-widget-header ui-helper-clearfix"><input type="text" class="search empty ui-widget-content ui-corner-all"/>'+(this.options.includeAddAll?'<a href="#" class="add-all">'+$.ui.multiselect.locale.addAll+'</a>':'<span class="add-all">&nbsp;</span>')+'</div>').appendTo(this.availableContainer);
		this.selectedList = $('<ul class="selected connected-list"><li class="ui-helper-hidden-accessible"></li></ul>').bind('selectstart', function(){return false;}).appendTo(this.selectedContainer);
		this.availableList = $('<ul class="available connected-list"><li class="ui-helper-hidden-accessible"></li></ul>').bind('selectstart', function(){return false;}).appendTo(this.availableContainer);
		
		var that = this;

		var width = this.options.width + 1;
		if (!width) {
			width = this.element.width();
		}
		var height = this.options.height;
		if (!height) {
			height = this.element.height();
		}

		// set dimensions
		this.container.width(width-2);
		if (this.options.selectedContainerOnLeft) {
			this.selectedContainer.width(Math.floor(width*this.options.dividerLocation)-1);
			this.availableContainer.width(Math.floor(width*(1-this.options.dividerLocation))-2);
		} else {
			this.selectedContainer.width(Math.floor(width*this.options.dividerLocation)-2);
			this.availableContainer.width(Math.floor(width*(1-this.options.dividerLocation))-1);
		}

		// fix list height to match <option> depending on their individual header's heights
		this.selectedList.height(Math.max(height-this.selectedActions.height(),1));
		this.availableList.height(Math.max(height-this.availableActions.height(),1));

		if ( !this.options.animated ) {
			this.options.show = 'show';
			this.options.hide = 'hide';
		}

		// init lists
		this._populateLists(this.element.find('option'));

		// make selection sortable
		if (this.options.sortable) {
			this.selectedList.sortable({
				placeholder: 'ui-state-highlight',
				axis: 'y',
				update: function(event, ui) {
					// apply the new sort order to the original selectbox
					that.selectedList.find('li').each(function() {
						if ($(this).data('optionLink'))
							$(this).data('optionLink').remove().appendTo(that.element);
					});
				},
				receive: function(event, ui) {
					var draggedItem = that.selectedList.children('.ui-draggable');

					// set selected attribute on linked option element
					ui.item.data('optionLink').attr('selected', true);

					// set item data, classes, and events
					draggedItem.data({
						'optionLink': ui.item.data('optionLink'),
						'idx': ui.item.data('idx')
					}).removeClass('ui-draggable');
					that._applyItemState(draggedItem, true);

					// update count
					that.count += 1;
					that._updateCount();

					// 1 ms workaround according to http://dev.jqueryui.com/ticket/4088
					setTimeout(function() { ui.item.remove(); }, 1);
				},
				stop: function(event, ui) { that.element.change(); }
			});
		}

		// set up livesearch
		if (this.options.searchable) {
			this._registerSearchEvents(this.availableContainer.find('input.search'));
		} else {
			$('.search').hide();
		}

		// batch actions
		this.container.find(".remove-all").click(function() {
			that._populateLists(that.element.find('option').removeAttr('selected'));
			that.element.trigger('change');
			return false;
		});

		this.container.find(".add-all").click(function() {
			var options = that.element.find('option').not(":selected");
			if (that.availableList.children('li:hidden').length > 1) {
				that.availableList.children('li').each(function(i) {
					if ($(this).is(":visible")) $(options[i-1]).attr('selected', 'selected');
				});
			} else {
				options.attr('selected', 'selected');
			}
			that._populateLists(that.element.find('option'));
			that.element.trigger('change');
			if (that.options.pressEnterKeyToAddAll) {
				//clear input after add all
				$('input.search').val("");
			}

			return false;
		});
	},
	destroy: function() {
		this.element.show();
		this.container.remove();

		$.Widget.prototype.destroy.apply(this, arguments);
	},
	addOption: function(option) {
		// Append the option
		option = $(option);
		var select = this.element;
		select.append(option);

		var item = this._getOptionNode(option).appendTo(option.attr('selected') ? this.selectedList : this.availableList).show();

		if (option.attr('selected')) {
			this.count += 1;
		}
		this._applyItemState(item, option.attr('selected'));
		item.data('idx', this.count);

		// update count
		this._updateCount();
		this._filter.apply(this.availableContainer.find('input.search'), [this.availableList]);
	},
	// Redisplay the lists of selected/available options.
	// Call this after you've selected/unselected some options programmatically.
	// GRIPE This is O(n) where n is the length of the list - seems like
	// there must be a smarter way of doing this, but I have not been able
	// to come up with one. I see no way to detect programmatic setting of
	// the option's selected property, and without that, it seems like we
	// can't have a general-case listener that does its thing every time an
	// option is selected.
	refresh: function() {
		// Redisplay our lists.
		this._populateLists(this.element.find('option'));
	},
	_populateLists: function(options) {
		this.selectedList.children('.ui-element').remove();
		this.availableList.children('.ui-element').remove();
		this.count = 0;

		var that = this;
		var groups = $(this.element).find("optgroup").map(function(i) {
			return that._getOptionGroup($(this));
		});
		groups.appendTo(this.selectedList.add(this.availableList));

		var items = $(options.map(function(i) {
			var item = that._getOptionNode(this).appendTo(that._getOptionList(this)).show();

			if (this.selected) that.count += 1;
			that._applyItemState(item, this.selected);
			item.data('idx', i);
			return item[0];
		}));

		// update count
		this._updateCount();
		that._filter.apply(this.availableContainer.find('input.search'), [that.availableList]);
	},
	_getOptionList: function(option) {
		var selected = option.selected;
		option = $(option);
		var $list = selected ? this.selectedList : this.availableList;
		var $group = option.closest("optgroup");
		if ($group.length === 0) {
			return $list;
		} else {
			var $groupList = $list.find("ul[title='" + $group.attr("label") + "']");
			if ($groupList.length === 0) {
				$groupList = $("<ul class='ui-state-default ui-element available' title='" + $group.attr("label") + "'>" + $group.attr("label") + "</ul>").appendTo($list);
			}
			$groupList.show();
			return $groupList;
		}
	},
	_getOptionGroup : function(optgroup) {
		var groupNode = $("<ul class='ui-state-default ui-element available' title='" + optgroup.attr("label") + "'>" + optgroup.attr("label") + "</ul>").hide();
		return groupNode[0];
	},
	_updateCount: function() {
		this.selectedContainer.find('span.count').text(this.count+" "+$.ui.multiselect.locale.itemsCount);
	},
	_getOptionNode: function(option) {
		option = $(option);
		var node = $('<li class="ui-state-default ui-element" title="'+option.text()+'"><span class="ui-icon"/>'+option.text()+'<a href="#" class="action"><span class="ui-corner-all ui-icon"/></a></li>').hide();
		node.data('optionLink', option);
		return node;
	},
	// clones an item with associated data
	// didn't find a smarter away around this
	_cloneWithData: function(clonee) {
		var clone = clonee.clone(false,false);
		clone.data('optionLink', clonee.data('optionLink'));
		clone.data('idx', clonee.data('idx'));
		return clone;
	},
	_setSelected: function(item, selected) {
		if(selected == true && this.options.single == true){
			if(this.selectedList.children('.ui-element').length > 0){
				alert('Only 1 Item is allowed!');
				return false;
			}
		}
		var temp = item.data('optionLink').attr('selected', selected);
		var parent = temp.parent();
		temp.detach().appendTo(parent);
		this.element.trigger('change');

		if (selected) {
			var selectedItem = this._cloneWithData(item);
			item[this.options.hide](this.options.animated, function() {
				if (item.siblings().length === 0) {
					item.closest("ul[title]").hide();
				}
				$(this).remove();
			});
			// get group to add it to...
			var $list = this._getOptionList(selectedItem.data("optionLink")[0]);
			selectedItem.appendTo($list).hide()[this.options.show](this.options.animated);

			this._applyItemState(selectedItem, true);
			return selectedItem;
		} else {

			// look for successor based on initial option index
			var items = this.availableList.find('li'), comparator = this.options.nodeComparator;
			var succ = null, i = item.data('idx'), direction = comparator(item, $(items[i]));

			// TODO: test needed for dynamic list populating
			if ( direction ) {
				while (i>=0 && i<items.length) {
					direction > 0 ? i++ : i--;
					if ( direction != comparator(item, $(items[i])) ) {
						// going up, go back one item down, otherwise leave as is
						succ = items[direction > 0 ? i : i+1];
						var group1 = item.closest("ul[title]"),
						    group2 = $(succ).closest("ul[title]");
						if (group1.length !== 0 && group2.length !== 0) {
							if (group1.attr("title") !== group2.attr("title")) {
								succ = null;
							}
						}
						break;
					}
				}
			} else {
				succ = items[i];
			}

			var availableItem = this._cloneWithData(item);
			var $list = this._getOptionList(availableItem.data("optionLink")[0]);
			succ ? availableItem.insertBefore($(succ)) : availableItem.appendTo($list);
			item[this.options.hide](this.options.animated, function() {
				if (item.siblings().length === 0) {
					item.closest("ul[title]").hide();
				}
				$(this).remove();
			});
			availableItem.hide()[this.options.show](this.options.animated);

			this._applyItemState(availableItem, false);
			return availableItem;
		}
	},
	_applyItemState: function(item, selected) {
		if (selected) {
			if (this.options.sortable)
				item.children('span').addClass('ui-icon-arrowthick-2-n-s').removeClass('ui-helper-hidden').addClass('ui-icon');
			else
				item.children('span').removeClass('ui-icon-arrowthick-2-n-s').addClass('ui-helper-hidden').removeClass('ui-icon');
			item.find('a.action span').addClass('ui-icon-minus').removeClass('ui-icon-plus');
			this._registerRemoveEvents(item.find('a.action'));

		} else {
			item.children('span').removeClass('ui-icon-arrowthick-2-n-s').addClass('ui-helper-hidden').removeClass('ui-icon');
			item.find('a.action span').addClass('ui-icon-plus').removeClass('ui-icon-minus');
			this._registerAddEvents(item.find('a.action'));
		}

		this._registerDoubleClickEvents(item);
		this._registerHoverEvents(item);
	},
	// taken from John Resig's liveUpdate script
	_filter: function(list) {
		var input = $(this);
		var rows = list.find('li'),
			cache = rows.map(function(){

				return $(this).text().toLowerCase();
			});

		var term = $.trim(input.val().toLowerCase()), scores = [];

		if (!term) {
			rows.show();
		} else {
			rows.hide();

			cache.each(function(i) {
				if (this.indexOf(term)>-1) { scores.push(i); }
			});

			$.each(scores, function() {
				$(rows[this]).show();
			});
		}
	},
	_registerDoubleClickEvents: function(elements) {
		if (!this.options.doubleClickable) return;
		elements.dblclick(function() {
			elements.find('a.action').click();
		});
	},
	_registerHoverEvents: function(elements) {
		elements.removeClass('ui-state-hover');
		elements.mouseover(function() {
			$(this).addClass('ui-state-hover');
		});
		elements.mouseout(function() {
			$(this).removeClass('ui-state-hover');
		});
	},
	_registerAddEvents: function(elements) {
		var that = this;
		elements.click(function() {
			var item = that._setSelected($(this).parent().removeClass('ui-draggable'), true);
			if(item != false){
				that.count += 1;
				that._updateCount();
	
				// Prevent extra clicks from triggering bogus add events, if a user
				// tries clicking during the removal process.
				$(this).unbind('click');
			}
			return false;
		});

		// make draggable
		if (this.options.sortable && this.options.dragToAdd) {
			elements.each(function() {
				$(this).parent().draggable({
					connectToSortable: that.selectedList,
					helper: function() {
						var selectedItem = that._cloneWithData($(this)).width($(this).width() - 50);
						selectedItem.width($(this).width());
						return selectedItem;
					},
					appendTo: that.container,
					containment: that.container,
					revert: 'invalid'
				});
			});
		}
	},
	_registerRemoveEvents: function(elements) {
		var that = this;
		elements.click(function() {
			that._setSelected($(this).parent(), false);
			that.count -= 1;
			that._updateCount();

			// Prevent extra clicks from triggering bogus remove events, if a
			// user tries clicking during the removal process.
			$(this).unbind('click');

			return false;
		});
	},
	_registerSearchEvents: function(input) {
		var that = this;

		input.focus(function() {
			$(this).addClass('ui-state-active');
		})
		.blur(function() {
			$(this).removeClass('ui-state-active');
		})
		.keypress(function(e) {
			if (e.keyCode == 13) {
				if (that.options.pressEnterKeyToAddAll) {
					//on Enter, if a filter is present add all, then clear the input
					var str = $('input.search').val();
					if (str !== undefined && str !== null && str !== "") {
						$('a.add-all').click();
						$('input.search').val("");
					}
				}
				return false;
			}
		})
		.keyup(function() {
			that._filter.apply(this, [that.availableList]);
		});
	}
});

$.extend($.ui.multiselect, {
	locale: {
		addAll:'Add all',
		removeAll:'Remove all',
		itemsCount:'items selected'
	}
});


})(jQuery);
;
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
;
/**
 * @file Attaches the jQuery UI Multiselect widget.
 */
(function($) {
  Drupal.behaviors.jQueryUIMultiselect = {
    attach: function(context, settings) {
      $('select.jquery-ui-multiselect', context).each(function(index) {
        var multiselectSettings = $.parseJSON($(this).attr('data-jquery-ui-multiselect'));
        //console.log(multiselectSettings);
        $(this).multiselect(multiselectSettings);
        
      });
    }
  }
})(jQuery);
;
(function ($) {
Drupal.behaviors.editablefields_submit = {
  attach: function (context) {
	$('.editablefield-item').once('editablefield', function() {
      var $this = $(this);

      // There is only one editable field in that form, we can hide the submit
      // button.
      if ($this.find('input[type=text],textarea,select').length == 1) {
        $this.find('input.form-submit').hide();
        $this.find('input[type=text],textarea,select').change(function() {
          $this.find('input.form-submit').triggerHandler('click');
        });
      }
    });
  }
};

/**
 * Overridden from Drupal core autocomplete.js
 * Hides the autocomplete suggestions.
 */
 /*
Drupal.jsAC.prototype.hidePopup = function (keycode) {
  // Select item if the right key or mousebutton was pressed.
  if (this.selected && ((keycode && keycode != 46 && keycode != 8 && keycode != 27) || !keycode)) {
    this.input.value = $(this.selected).data('autocompleteValue');
    $(this.input).trigger('change');
  }
  // Hide popup.
  var popup = this.popup;
  if (popup) {
    this.popup = null;
    $(popup).fadeOut('fast', function () { $(popup).remove(); });
  }
  this.selected = false;
  $(this.ariaLive).empty();
};
*/

})(jQuery);

;
(function ($) {
  Drupal.behaviors.vbo = {
    attach: function(context) {
      $('.vbo-views-form', context).each(function() {
        Drupal.vbo.initTableBehaviors(this);
        Drupal.vbo.initGenericBehaviors(this);
      });
    }
  }

  Drupal.vbo = Drupal.vbo || {};
  Drupal.vbo.initTableBehaviors = function(form) {
    // If the table is not grouped, "Select all on this page / all pages"
    // markup gets inserted below the table header.
    var selectAllMarkup = $('.vbo-table-select-all-markup', form);
    if (selectAllMarkup.length) {
      $('tbody', form).prepend('<tr class="views-table-row-select-all even">></tr>');
      var colspan = $('table th', form).length;
      $('.views-table-row-select-all', form).html('<td colspan="' + colspan + '">' + selectAllMarkup.html() + '</td>');

      $('.vbo-table-select-all-pages', form).click(function() {
        Drupal.vbo.tableSelectAllPages(form);
        return false;
      });
      $('.vbo-table-select-this-page', form).click(function() {
        Drupal.vbo.tableSelectThisPage(form);
        return false;
      });
    }

    $('.vbo-table-select-all', form).show();
    // This is the "select all" checkbox in (each) table header.
    $('.vbo-table-select-all', form).click(function() {
      var table = $(this).closest('table')[0];
      $('input[id^="edit-views-bulk-operations"]:not(:disabled)', table).attr('checked', this.checked);

      // Toggle the visibility of the "select all" row (if any).
      if (this.checked) {
        $('.views-table-row-select-all', table).show();
      }
      else {
        $('.views-table-row-select-all', table).hide();
        // Disable "select all across pages".
        Drupal.vbo.tableSelectThisPage(form);
      }
    });

    // Set up the ability to click anywhere on the row to select it.
    $('.views-table tbody tr', form).click(function(event) {
      if (event.target.tagName.toLowerCase() != 'input' && event.target.tagName.toLowerCase() != 'a') {
        $('input[id^="edit-views-bulk-operations"]:not(:disabled)', this).each(function() {
          var checked = this.checked;
          // trigger() toggles the checkmark *after* the event is set,
          // whereas manually clicking the checkbox toggles it *beforehand*.
          // that's why we manually set the checkmark first, then trigger the
          // event (so that listeners get notified), then re-set the checkmark
          // which the trigger will have toggled. yuck!
          this.checked = !checked;
          $(this).trigger('click');
          this.checked = !checked;
        });
      }
    });
  }

  Drupal.vbo.tableSelectAllPages = function(form) {
    $('.vbo-table-this-page', form).hide();
    $('.vbo-table-all-pages', form).show();
    // Modify the value of the hidden form field.
    $('.select-all-rows', form).val('1');
  }
  Drupal.vbo.tableSelectThisPage = function(form) {
    $('.vbo-table-all-pages', form).hide();
    $('.vbo-table-this-page', form).show();
    // Modify the value of the hidden form field.
    $('.select-all-rows', form).val('0');
  }

  Drupal.vbo.initGenericBehaviors = function(form) {
    // Show the "select all" fieldset.
    $('.vbo-select-all-markup', form).show();

    $('.vbo-select-this-page', form).click(function() {
      $('input[id^="edit-views-bulk-operations"]', form).attr('checked', this.checked);
      $('.vbo-select-all-pages', form).attr('checked', false);

      // Toggle the "select all" checkbox in grouped tables (if any).
      $('.vbo-table-select-all', form).attr('checked', this.checked);
    });
    $('.vbo-select-all-pages', form).click(function() {
      $('input[id^="edit-views-bulk-operations"]', form).attr('checked', this.checked);
      $('.vbo-select-this-page', form).attr('checked', false);

      // Toggle the "select all" checkbox in grouped tables (if any).
      $('.vbo-table-select-all', form).attr('checked', this.checked);

      // Modify the value of the hidden form field.
      $('.select-all-rows', form).val(this.checked);
    });

    $('.vbo-select', form).click(function() {
      // If a checkbox was deselected, uncheck any "select all" checkboxes.
      if (!this.checked) {
        $('.vbo-select-this-page', form).attr('checked', false);
        $('.vbo-select-all-pages', form).attr('checked', false);
        // Modify the value of the hidden form field.
        $('.select-all-rows', form).val('0')

        var table = $(this).closest('table')[0];
        if (table) {
          // Uncheck the "select all" checkbox in the table header.
          $('.vbo-table-select-all', table).attr('checked', false);

          // If there's a "select all" row, hide it.
          if ($('.vbo-table-select-this-page', table).length) {
            $('.views-table-row-select-all', table).hide();
            // Disable "select all across pages".
            Drupal.vbo.tableSelectThisPage(form);
          }
        }
      }
    });
  }

})(jQuery);
;
(function ($) {
Drupal.settings.views = Drupal.settings.views || {'ajax_path': '/views/ajax'};

Drupal.quicktabs = Drupal.quicktabs || {};

Drupal.quicktabs.getQTName = function (el) {
  return el.id.substring(el.id.indexOf('-') +1);
}

Drupal.behaviors.quicktabs = {
  attach: function (context, settings) {
    $.extend(true, Drupal.settings, settings);
    $('.quicktabs-wrapper', context).once(function(){
      Drupal.quicktabs.prepare(this);
    });
  }
}

// Setting up the inital behaviours
Drupal.quicktabs.prepare = function(el) {
  // el.id format: "quicktabs-$name"
  var qt_name = Drupal.quicktabs.getQTName(el);
  var $ul = $(el).find('ul.quicktabs-tabs:first');
  $ul.find('li a').each(function(i, element){
    element.myTabIndex = i;
    element.qt_name = qt_name;
    var tab = new Drupal.quicktabs.tab(element);
    var parent_li = $(element).parents('li').get(0);
    if ($(parent_li).hasClass('active')) {
      $(element).addClass('quicktabs-loaded');
    }
    $(element).once(function() {$(this).bind('click', {tab: tab}, Drupal.quicktabs.clickHandler);});
  });
}

Drupal.quicktabs.clickHandler = function(event) {
  var tab = event.data.tab;
  var element = this;
  // Set clicked tab to active.
  $(this).parents('li').siblings().removeClass('active');
  $(this).parents('li').addClass('active');

  // Hide all tabpages.
  tab.container.children().addClass('quicktabs-hide');
  
  if (!tab.tabpage.hasClass("quicktabs-tabpage")) {
    tab = new Drupal.quicktabs.tab(element);
  }

  tab.tabpage.removeClass('quicktabs-hide');
  return false;
}

// Constructor for an individual tab
Drupal.quicktabs.tab = function (el) {
  this.element = el;
  this.tabIndex = el.myTabIndex;
  var qtKey = 'qt_' + el.qt_name;
  var i = 0;
  for (var key in Drupal.settings.quicktabs[qtKey].tabs) {
    if (i == this.tabIndex) {
      this.tabObj = Drupal.settings.quicktabs[qtKey].tabs[key];
      this.tabKey = key;
    }
    i++;
  }
  this.tabpage_id = 'quicktabs-tabpage-' + el.qt_name + '-' + this.tabKey;
  this.container = $('#quicktabs-container-' + el.qt_name);
  this.tabpage = this.container.find('#' + this.tabpage_id);
}

if (Drupal.ajax) {
  /**
   * Handle an event that triggers an AJAX response.
   *
   * We unfortunately need to override this function, which originally comes from
   * misc/ajax.js, in order to be able to cache loaded tabs, i.e. once a tab
   * content has loaded it should not need to be loaded again.
   *
   * I have removed all comments that were in the original core function, so that
   * the only comments inside this function relate to the Quicktabs modification
   * of it.
   */
  Drupal.ajax.prototype.eventResponse = function (element, event) {
    var ajax = this;

    if (ajax.ajaxing) {
      return false;
    }
  
    try {
      if (ajax.form) {
        if (ajax.setClick) {
          element.form.clk = element;
        }
  
        ajax.form.ajaxSubmit(ajax.options);
      }
      else {
        // Do not perform an ajax request for already loaded Quicktabs content.
        if (!$(element).hasClass('quicktabs-loaded')) {
          ajax.beforeSerialize(ajax.element, ajax.options);
          $.ajax(ajax.options);
          if ($(element).parents('ul').hasClass('quicktabs-tabs')) {
            $(element).addClass('quicktabs-loaded');
          }
        }
      }
    }
    catch (e) {
      ajax.ajaxing = false;
      alert("An error occurred while attempting to process " + ajax.options.url + ": " + e.message);
    }
    return false;
  };
}


})(jQuery);
;
;
;
/**
 * Attaches the calendar behavior to all required fields
 */
(function ($) {
Drupal.behaviors.date_popup = {
  attach: function (context) {
  	
  for (var id in Drupal.settings.datePopup) {
    $('#'+ id).bind('focus', Drupal.settings.datePopup[id], function(e) {
      if (!$(this).hasClass('date-popup-init')) {
        var datePopup = e.data;
        // Explicitely filter the methods we accept.
        switch (datePopup.func) {
          case 'datepicker':
            $(this)
              .datepicker(datePopup.settings)
              .addClass('date-popup-init')
            $(this).click(function(){
              $(this).focus();
            });
            break;

          case 'timeEntry':
            $(this)
              .timeEntry(datePopup.settings)
              .addClass('date-popup-init')
            $(this).click(function(){
              $(this).focus();
            });
            break;
          case 'timepicker':
            // Translate the PHP date format into the style the timepicker uses.
            datePopup.settings.timeFormat = datePopup.settings.timeFormat
              // 12-hour, leading zero,
              .replace('h', 'hh')
              // 12-hour, no leading zero.
              .replace('g', 'h')
              // 24-hour, leading zero.
              .replace('H', 'HH')
              // 24-hour, no leading zero.
              .replace('G', 'H')
              // AM/PM.
              .replace('A', 'p')
              // Minutes with leading zero.
              .replace('i', 'mm')
              // Seconds with leading zero.
              .replace('s', 'ss');

            datePopup.settings.startTime = new Date(datePopup.settings.startTime);
            $(this)
              .timepicker(datePopup.settings)
              .addClass('date-popup-init');
            $(this).click(function(){
              $(this).focus();
            });
            break;
        }
      }
    });
  }
  }
};
})(jQuery);
;
// $Id$


// Some global variables we will need...
var arrangeFieldsStartupHeight;
var arrangeFieldsGreatestHeight;
var arrangeFieldsDragging;
var arrangeFieldsDialogConfigField;
var arrangeFieldsDialogConfigFieldId;
var arrangeFieldsDialogConfigFieldType;
var arrangeFieldsDialogMarkupId;
var arrangeFieldsDialogConfigObj = new Object();  // we will use this later like a 2d assoc array, for keeping up with dialog settings for fields.
var arrangeFieldsDialogMarkupObj = new Object();  // we will use this later like a 2d assoc array, for keeping up with dialog settings for markup elements.


Drupal.behaviors.arrangeFieldsStartup = {
 attach: function (context, settings) {
 
  // If we have any dialog config settings saved from a previous session,
  // let's load them.
  if (Drupal.settings.arrangeFieldsDialogConfigObj != null) {
    arrangeFieldsDialogConfigObj = Drupal.settings.arrangeFieldsDialogConfigObj;
  }
  if (Drupal.settings.arrangeFieldsDialogMarkupObj != null) {
    arrangeFieldsDialogMarkupObj = Drupal.settings.arrangeFieldsDialogMarkupObj;
  }
  
    
  // This section of code makes the "handle" appear for draggable items, which users
  // may use to drag the item, or for important links to appear there.
  jQuery(".arrange-fields-container .draggable-form-item").bind("mouseenter", function(event) {
    var hand = jQuery(this).find(".arrange-fields-control-handle");
    if (arrangeFieldsDragging != true) {
      jQuery(hand).show();
    }
  });

  jQuery(".arrange-fields-container .draggable-form-item").bind("mouseleave", function(event) {
    var hand = jQuery(this).find(".arrange-fields-control-handle");
    if (arrangeFieldsDragging != true) {
      jQuery(hand).hide();
    }
  });
  

  // Figure out what the gridWidth should be  (10,10 is default).
  var gridWidth = 10;
  if (Drupal.settings.arrangeFieldsGridWidth != null) {
    gridWidth = Drupal.settings.arrangeFieldsGridWidth;
  }
  if (gridWidth < 1) gridWidth = 10;  
  
  // This actually makes the draggable items draggable.
  jQuery(".arrange-fields-container .draggable-form-item").draggable({
    stop: function(event, ui) { arrangeFieldsRepositionToGrid(false); },
    containment: ".arrange-fields-container", 
    scroll: true,
    grid : [gridWidth,gridWidth],
    start: function(event, ui) {arrangeFieldsDragging = true;},
    stop:  function(event, ui) {arrangeFieldsDragging = false;}
  });

  
  arrangeFieldsStartupHeight = 0;
  arrangeFieldsGreatestHeight = 0; 

  
  jQuery(".arrange-fields-container .draggable-form-item:not(.draggable-form-item-fieldset, .arrange-fields-vertical-tabs-wrapper) textarea").resizable();
  jQuery(".arrange-fields-container .draggable-form-item:not(.draggable-form-item-fieldset, .arrange-fields-vertical-tabs-wrapper) .form-text").resizable({
        handles: 'e'
  });  
  jQuery(".arrange-fields-container .arrange-fields-draggable-markup").resizable();

  
  // We do the "true" if this is a totally fresh new form, with no
  // position data already saved.  
  var startup = true;
  
  try {
    if (Drupal.settings.arrangeFieldsNotNewForm == true) {
      startup = false;
    }
  }
  catch (exception) {}
  
  // Make sure everything starts off on a grid line.
  arrangeFieldsRepositionToGrid(startup); 
  
 }
}


/**
  * Repositions all the draggable elements to the grid lines.
  */
function arrangeFieldsRepositionToGrid(startup) {

  // Figure out what the gridWidth should be  (10,10 is default).
  var gridWidth = 10;
  if (Drupal.settings.arrangeFieldsGridWidth != null) {
    gridWidth = Drupal.settings.arrangeFieldsGridWidth;
  }
  if (gridWidth < 1) gridWidth = 10;
    
  jQuery(".arrange-fields-container .draggable-form-item").each(function (index, element) {
    var postop = jQuery(element).css("top");
    var posleft = jQuery(element).css("left");

    postop = jQuery(element).css("top").replace("px", "");
    posleft = jQuery(element).css("left").replace("px", "");
    
    if (postop == "auto") postop = 0; 
    if (posleft == "auto") posleft = 0;
    
    if (startup == true && postop == 0) {
      // Since this is a new form, with values not set yet,
      // let's assign the postop based on the running startupHeight
      // value.
      postop = arrangeFieldsStartupHeight;
      arrangeFieldsStartupHeight += jQuery(element).height() + 20; 
    }
      
    if (parseInt(postop) > parseInt(arrangeFieldsGreatestHeight)) {
      arrangeFieldsGreatestHeight = parseInt(postop);
    }
    
    // We want to round the top and left positions to the nearest X (gridWidth)
    var newTop = Math.round(postop/gridWidth) * gridWidth;
    var newLeft = Math.round(posleft/gridWidth) * gridWidth;
    
    var diffLeft = "-" + (posleft - newLeft);
    var diffTop = "-" + (postop - newTop);
    
    if (posleft < newLeft) { diffLeft = newLeft - posleft; }
    if (postop < newTop) { diffTop = newTop - postop; }

    if (newTop < 0) newTop = 0;
    if (newLeft < 0) newLeft = 0;
    
   jQuery(element).css("top", newTop + "px");
   jQuery(element).css("left", newLeft + "px");

   // We want to resize the container as we go to make sure we don't run out of
   // room, and to make sure the user can always drag things below the rest of
   // the items on the form.
   jQuery(".arrange-fields-container").css("height", (parseInt(arrangeFieldsGreatestHeight) + 500) + "px");
 
  });
  
}

/**
  * This method will save the position, width, and height, and other important
  * information of the draggable items on the page.
  *
  */
function arrangeFieldsSavePositions() {
  
  var dataString = "";
  var maxBottom = 0;
  
  jQuery(".arrange-fields-container .draggable-form-item").each(function (index, element) {
   var id = jQuery(element)[0].id;
   var top = jQuery(element).css("top");
   var left = jQuery(element).css("left");
   
   // Now, we want to find the element inside...
   var inner_element_type = "";
   var inner_element_id = "";
   
   var width = 0;
   var height = 0;
   
   // Attempt to find either a text area or a textfield...
   // But, only do this if we are NOT within a fieldset!
   if (jQuery(element).hasClass("draggable-form-item-fieldset") == false) {
     var test = jQuery(element).find("textarea");
     width = jQuery(test).width();
     height = jQuery(test).height();
     if (width != null) inner_element_type = "textarea";
     
     if (width == null) {
       test = jQuery(element).find("input:text");       
       width = jQuery(test).width();
       height = jQuery(test).height();
       if (width != null) inner_element_type = "input";
     }
     
     // Attempt to get the inner element's CSS id, if we can.
     try {
       inner_element_id = test[0].id;
     } catch (e) {}
          
   }

   if (width == null) {
     width = height = 0;
   }   
   
   dataString += id + "," + top + "," + left + "," + inner_element_type + "," +inner_element_id + "," + width + "px," + height + "px,";
   
   // Do we have any extra data for this element?  Perhaps data from the config dialog?
   if (arrangeFieldsDialogConfigObj[id] != null) {
     dataString += arrangeFieldsDialogConfigObj[id]["wrapperWidth"] + ",";
     dataString += arrangeFieldsDialogConfigObj[id]["wrapperHeight"] + ",";
     dataString += arrangeFieldsDialogConfigObj[id]["labelDisplay"] + ",";
     dataString += arrangeFieldsDialogConfigObj[id]["labelVerticalAlign"] + ",";
   }
   
   // Is this field a piece of custom markup which the user has added?  If so,
   // add whatever information we can about it from the object.
   if (arrangeFieldsDialogMarkupObj[id] != null) {
     dataString += "~~markup_element~~,";
     dataString += jQuery(element).width() + "px,";
     dataString += jQuery(element).height() + "px,";
     dataString += arrangeFieldsDialogMarkupObj[id]["markupBody"] + ",";
     dataString += arrangeFieldsDialogMarkupObj[id]["wrapperStyle"] + ",";
     dataString += arrangeFieldsDialogMarkupObj[id]["zIndex"] + ",";
   }
   
   dataString += ";";
   
   var bottom = parseInt(top) + jQuery(element).height();
   if (bottom > maxBottom) {
     maxBottom = bottom;
   }
   
  });
   
  // This maxBottom value tells us how tall the container needs to be on the node/edit page
  // for this form.
  dataString += "~~maxBottom~~," + maxBottom + "px";
  //console.log(dataString);
  //return false;
  jQuery("#edit-arrange-fields-position-data").val(dataString);

}

function arrangeFieldsConfirmReset() {
  var x = confirm("Are you sure you want to reset the position data for these fields?  This action cannot be undone.");
  return x;
}

function arrangeFieldsPopupEditField(type, field) {
  // Using the ?q= syntax is better, as it works for people
  // who do not have clean URLs enabled, as well as those who do.
  var popup_url = Drupal.settings.basePath + "?q=arrange-fields/popup-edit-field&type_name=" + type + "&field=" + field;
  var win_title = "myPopupWin";
  var win_options = "height=700,width=700,scrollbars=yes";
  
  var myWin = window.open(popup_url, win_title, win_options);
  myWin.focus();

}

function arrangeFieldsClosePopup() {
  // Closes the popup and saves the form in the opener window.
  opener.arrangeFieldsSavePositions();
  opener.document.getElementById("arrange-fields-position-form").submit();
  window.close();
}



;
/**
 * @file
 * Handles AJAX fetching of views, including filter submission and response.
 */
(function ($) {

/**
 * Attaches the AJAX behavior to Views exposed filter forms and key View links.
 */
Drupal.behaviors.ViewsAjaxView = {};
Drupal.behaviors.ViewsAjaxView.attach = function() {
  if (Drupal.settings && Drupal.settings.views && Drupal.settings.views.ajaxViews) {
    $.each(Drupal.settings.views.ajaxViews, function(i, settings) {
      // @todo: Figure out where to store the object.
      new Drupal.views.ajaxView(settings);
    });
  }
};

Drupal.views = {};

/**
 * Javascript object for a certain view.
 */
Drupal.views.ajaxView = function(settings) {
  var selector = '.view-dom-id-' + settings.view_dom_id;
  this.$view = $(selector);

  // Retrieve the path to use for views' ajax.
  var ajax_path = Drupal.settings.views.ajax_path;

  // If there are multiple views this might've ended up showing up multiple times.
  if (ajax_path.constructor.toString().indexOf("Array") != -1) {
    ajax_path = ajax_path[0];
  }

  // Check if there are any GET parameters to send to views.
  var queryString = window.location.search || '';
  if (queryString !== '') {
    // Remove the question mark and Drupal path component if any.
    var queryString = queryString.slice(1).replace(/q=[^&]+&?|&?render=[^&]+/, '');
    if (queryString !== '') {
      // If there is a '?' in ajax_path, clean url are on and & should be used to add parameters.
      queryString = ((/\?/.test(ajax_path)) ? '&' : '?') + queryString;
    }
  }

  this.element_settings = {
    url: ajax_path + queryString,
    submit: settings,
    setClick: true,
    event: 'click',
    selector: selector,
    progress: { type: 'throbber' }
  };

  this.settings = settings;

  // Add the ajax to exposed forms.
  this.$exposed_form = $('form#views-exposed-form-'+ settings.view_name.replace(/_/g, '-') + '-' + settings.view_display_id.replace(/_/g, '-'));
  this.$exposed_form.once(jQuery.proxy(this.attachExposedFormAjax, this));

  // Add the ajax to pagers.
  this.$view
    // Don't attach to nested views. Doing so would attach multiple behaviors
    // to a given element.
    .filter(jQuery.proxy(this.filterNestedViews, this))
    .once(jQuery.proxy(this.attachPagerAjax, this));
};

Drupal.views.ajaxView.prototype.attachExposedFormAjax = function() {
  var button = $('input[type=submit], input[type=image]', this.$exposed_form);
  button = button[0];

  this.exposedFormAjax = new Drupal.ajax($(button).attr('id'), button, this.element_settings);
};

Drupal.views.ajaxView.prototype.filterNestedViews= function() {
  // If there is at least one parent with a view class, this view
  // is nested (e.g., an attachment). Bail.
  return !this.$view.parents('.view').size();
};

/**
 * Attach the ajax behavior to each link.
 */
Drupal.views.ajaxView.prototype.attachPagerAjax = function() {
  this.$view.find('ul.pager > li > a, th.views-field a, .attachment .views-summary a')
  .each(jQuery.proxy(this.attachPagerLinkAjax, this));
};

/**
 * Attach the ajax behavior to a singe link.
 */
Drupal.views.ajaxView.prototype.attachPagerLinkAjax = function(id, link) {
  var $link = $(link);
  var viewData = {};
  var href = $link.attr('href');
  // Construct an object using the settings defaults and then overriding
  // with data specific to the link.
  $.extend(
    viewData,
    this.settings,
    Drupal.Views.parseQueryString(href),
    // Extract argument data from the URL.
    Drupal.Views.parseViewArgs(href, this.settings.view_base_path)
  );

  // For anchor tags, these will go to the target of the anchor rather
  // than the usual location.
  $.extend(viewData, Drupal.Views.parseViewArgs(href, this.settings.view_base_path));

  this.element_settings.submit = viewData;
  this.pagerAjax = new Drupal.ajax(false, $link, this.element_settings);
};

Drupal.ajax.prototype.commands.viewsScrollTop = function (ajax, response, status) {
  // Scroll to the top of the view. This will allow users
  // to browse newly loaded content after e.g. clicking a pager
  // link.
  var offset = $(response.selector).offset();
  // We can't guarantee that the scrollable object should be
  // the body, as the view could be embedded in something
  // more complex such as a modal popup. Recurse up the DOM
  // and scroll the first element that has a non-zero top.
  var scrollTarget = response.selector;
  while ($(scrollTarget).scrollTop() == 0 && $(scrollTarget).parent()) {
    scrollTarget = $(scrollTarget).parent();
  } 
  // Only scroll upward
  if(offset != null) { 
	  if (offset.top - 10 < $(scrollTarget).scrollTop()) {
	    $(scrollTarget).animate({scrollTop: (offset.top - 10)}, 500);
	  }
  }
};

})(jQuery);
;
;
(function($){
/**
 * To make a form auto submit, all you have to do is 3 things:
 *
 * ctools_add_js('auto-submit');
 *
 * On gadgets you want to auto-submit when changed, add the ctools-auto-submit
 * class. With FAPI, add:
 * @code
 *  '#attributes' => array('class' => array('ctools-auto-submit')),
 * @endcode
 *
 * If you want to have auto-submit for every form element,
 * add the ctools-auto-submit-full-form to the form. With FAPI, add:
 * @code
 *   '#attributes' => array('class' => array('ctools-auto-submit-full-form')),
 * @endcode
 *
 * Finally, you have to identify which button you want clicked for autosubmit.
 * The behavior of this button will be honored if it's ajaxy or not:
 * @code
 *  '#attributes' => array('class' => array('ctools-use-ajax', 'ctools-auto-submit-click')),
 * @endcode
 *
 * Currently only 'select', 'radio', 'checkbox' and 'textfield' types are supported. We probably
 * could use additional support for HTML5 input types.
 */

Drupal.behaviors.CToolsAutoSubmit = {
  attach: function(context) {
    // 'this' references the form element
    function triggerSubmit (e) {
      var $this = $(this);
      if (!$this.hasClass('ctools-ajaxing')) {
        $this.find('.ctools-auto-submit-click').click();
      }
    }

    // the change event bubbles so we only need to bind it to the outer form
    $('form.ctools-auto-submit-full-form', context)
      .add('.ctools-auto-submit', context)
      .filter('form, select, input:not(:text, :submit)')
      .once('ctools-auto-submit')
      .change(function (e) {
        // don't trigger on text change for full-form
        if ($(e.target).is(':not(:text, :submit)')) {
          triggerSubmit.call(e.target.form);
        }
      });

    // e.keyCode: key
    var discardKeyCode = [
      16, // shift
      17, // ctrl
      18, // alt
      20, // caps lock
      33, // page up
      34, // page down
      35, // end
      36, // home
      37, // left arrow
      38, // up arrow
      39, // right arrow
      40, // down arrow
       9, // tab
      13, // enter
      27  // esc
    ];
    // Don't wait for change event on textfields
    $('.ctools-auto-submit-full-form input:text, input:text.ctools-auto-submit', context)
      .once('ctools-auto-submit', function () {
        // each textinput element has his own timeout
        var timeoutID = 0;
        $(this)
          .bind('keydown keyup', function (e) {
            if ($.inArray(e.keyCode, discardKeyCode) === -1) {
              timeoutID && clearTimeout(timeoutID);
            }
          })
          .keyup(function(e) {
            if ($.inArray(e.keyCode, discardKeyCode) === -1) {
              timeoutID = setTimeout($.proxy(triggerSubmit, this.form), 500);
            }
          });
      });
  }
}
})(jQuery);
;
(function ($) {

/**
 * Toggle the visibility of a fieldset using smooth animations.
 */
Drupal.toggleFieldset = function (fieldset) {
  var $fieldset = $(fieldset);
  if ($fieldset.is('.collapsed')) {
    var $content = $('> .fieldset-wrapper', fieldset).hide();
    $fieldset
      .removeClass('collapsed')
      .trigger({ type: 'collapsed', value: false })
      .find('> legend span.fieldset-legend-prefix').html(Drupal.t('Hide'));
    $content.slideDown({
      duration: 'fast',
      easing: 'linear',
      complete: function () {
        Drupal.collapseScrollIntoView(fieldset);
        fieldset.animating = false;
      },
      step: function () {
        // Scroll the fieldset into view.
        Drupal.collapseScrollIntoView(fieldset);
      }
    });
  }
  else {
    $fieldset.trigger({ type: 'collapsed', value: true });
    $('> .fieldset-wrapper', fieldset).slideUp('fast', function () {
      $fieldset
        .addClass('collapsed')
        .find('> legend span.fieldset-legend-prefix').html(Drupal.t('Show'));
      fieldset.animating = false;
    });
  }
};

/**
 * Scroll a given fieldset into view as much as possible.
 */
Drupal.collapseScrollIntoView = function (node) {
  var h = document.documentElement.clientHeight || document.body.clientHeight || 0;
  var offset = document.documentElement.scrollTop || document.body.scrollTop || 0;
  var posY = $(node).offset().top;
  var fudge = 55;
  if (posY + node.offsetHeight + fudge > h + offset) {
    if (node.offsetHeight > h) {
      window.scrollTo(0, posY);
    }
    else {
      window.scrollTo(0, posY + node.offsetHeight - h + fudge);
    }
  }
};

Drupal.behaviors.collapse = {
  attach: function (context, settings) {
    $('fieldset.collapsible', context).once('collapse', function () {
      var $fieldset = $(this);
      // Expand fieldset if there are errors inside, or if it contains an
      // element that is targeted by the uri fragment identifier. 
      var anchor = location.hash && location.hash != '#' ? ', ' + location.hash : '';
      if ($('.error' + anchor, $fieldset).length) {
        $fieldset.removeClass('collapsed');
      }

      var summary = $('<span class="summary"></span>');
      $fieldset.
        bind('summaryUpdated', function () {
          var text = $.trim($fieldset.drupalGetSummary());
          summary.html(text ? ' (' + text + ')' : '');
        })
        .trigger('summaryUpdated');

      // Turn the legend into a clickable link, but retain span.fieldset-legend
      // for CSS positioning.
      var $legend = $('> legend .fieldset-legend', this);

      $('<span class="fieldset-legend-prefix element-invisible"></span>')
        .append($fieldset.hasClass('collapsed') ? Drupal.t('Show') : Drupal.t('Hide'))
        .prependTo($legend)
        .after(' ');

      // .wrapInner() does not retain bound events.
      var $link = $('<a class="fieldset-title" href="#"></a>')
        .prepend($legend.contents())
        .appendTo($legend)
        .click(function () {
          var fieldset = $fieldset.get(0);
          // Don't animate multiple times.
          if (!fieldset.animating) {
            fieldset.animating = true;
            Drupal.toggleFieldset(fieldset);
          }
          return false;
        });

      $legend.append(summary);
    });
  }
};

})(jQuery);
;
(function ($) {

/**
 * Attaches sticky table headers.
 */
Drupal.behaviors.tableHeader = {
  attach: function (context, settings) {
    if (!$.support.positionFixed) {
      return;
    }

    if($.isFunction( $('table.sticky-enabled', context).once)){
	    $('table.sticky-enabled', context).once('tableheader', function () {
	      $(this).data("drupal-tableheader", new Drupal.tableHeader(this));
	    });
    }
  }
};

/**
 * Constructor for the tableHeader object. Provides sticky table headers.
 *
 * @param table
 *   DOM object for the table to add a sticky header to.
 */
Drupal.tableHeader = function (table) {
  var self = this;

  this.originalTable = $(table);
  this.originalHeader = $(table).children('thead');
  this.originalHeaderCells = this.originalHeader.find('> tr > th');
  this.displayWeight = null;

  // React to columns change to avoid making checks in the scroll callback.
  this.originalTable.bind('columnschange', function (e, display) {
    // This will force header size to be calculated on scroll.
    self.widthCalculated = (self.displayWeight !== null && self.displayWeight === display);
    self.displayWeight = display;
  });

  // Clone the table header so it inherits original jQuery properties. Hide
  // the table to avoid a flash of the header clone upon page load.
  this.stickyTable = $('<table class="sticky-header"/>')
    .insertBefore(this.originalTable)
    .css({ position: 'fixed', top: '0px' });
  this.stickyHeader = this.originalHeader.clone(true)
    .hide()
    .appendTo(this.stickyTable);
  this.stickyHeaderCells = this.stickyHeader.find('> tr > th');

  this.originalTable.addClass('sticky-table');
  $(window)
    .bind('scroll.drupal-tableheader', $.proxy(this, 'eventhandlerRecalculateStickyHeader'))
    .bind('resize.drupal-tableheader', { calculateWidth: true }, $.proxy(this, 'eventhandlerRecalculateStickyHeader'))
    // Make sure the anchor being scrolled into view is not hidden beneath the
    // sticky table header. Adjust the scrollTop if it does.
    .bind('drupalDisplaceAnchor.drupal-tableheader', function () {
      window.scrollBy(0, -self.stickyTable.outerHeight());
    })
    // Make sure the element being focused is not hidden beneath the sticky
    // table header. Adjust the scrollTop if it does.
    .bind('drupalDisplaceFocus.drupal-tableheader', function (event) {
      if (self.stickyVisible && event.clientY < (self.stickyOffsetTop + self.stickyTable.outerHeight()) && event.$target.closest('sticky-header').length === 0) {
        window.scrollBy(0, -self.stickyTable.outerHeight());
      }
    })
    .triggerHandler('resize.drupal-tableheader');

  // We hid the header to avoid it showing up erroneously on page load;
  // we need to unhide it now so that it will show up when expected.
  this.stickyHeader.show();
};

/**
 * Event handler: recalculates position of the sticky table header.
 *
 * @param event
 *   Event being triggered.
 */
Drupal.tableHeader.prototype.eventhandlerRecalculateStickyHeader = function (event) {
  var self = this;
  var calculateWidth = event.data && event.data.calculateWidth;

  // Reset top position of sticky table headers to the current top offset.
  this.stickyOffsetTop = Drupal.settings.tableHeaderOffset ? eval(Drupal.settings.tableHeaderOffset + '()') : 0;
  this.stickyTable.css('top', this.stickyOffsetTop + 'px');

  // Save positioning data.
  var viewHeight = document.documentElement.scrollHeight || document.body.scrollHeight;
  if (calculateWidth || this.viewHeight !== viewHeight) {
    this.viewHeight = viewHeight;
    this.vPosition = this.originalTable.offset().top - 4 - this.stickyOffsetTop;
    this.hPosition = this.originalTable.offset().left;
    this.vLength = this.originalTable[0].clientHeight - 100;
    calculateWidth = true;
  }

  // Track horizontal positioning relative to the viewport and set visibility.
  var hScroll = document.documentElement.scrollLeft || document.body.scrollLeft;
  var vOffset = (document.documentElement.scrollTop || document.body.scrollTop) - this.vPosition;
  this.stickyVisible = vOffset > 0 && vOffset < this.vLength;
  this.stickyTable.css({ left: (-hScroll + this.hPosition) + 'px', visibility: this.stickyVisible ? 'visible' : 'hidden' });

  // Only perform expensive calculations if the sticky header is actually
  // visible or when forced.
  if (this.stickyVisible && (calculateWidth || !this.widthCalculated)) {
    this.widthCalculated = true;
    var $that = null;
    var $stickyCell = null;
    var display = null;
    var cellWidth = null;
    // Resize header and its cell widths.
    // Only apply width to visible table cells. This prevents the header from
    // displaying incorrectly when the sticky header is no longer visible.
    for (var i = 0, il = this.originalHeaderCells.length; i < il; i += 1) {
      $that = $(this.originalHeaderCells[i]);
      $stickyCell = this.stickyHeaderCells.eq($that.index());
      display = $that.css('display');
      if (display !== 'none') {
        cellWidth = $that.css('width');
        // Exception for IE7.
        if (cellWidth === 'auto') {
          cellWidth = $that[0].clientWidth + 'px';
        }
        $stickyCell.css({'width': cellWidth, 'display': display});
      }
      else {
        $stickyCell.css('display', 'none');
      }
    }
    this.stickyTable.css('width', this.originalTable.css('width'));
  }
};

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
(function($) {
	$.fn.getFixedMenu = function(menus, relType) {
		switch(relType) {
			case "treenodevouchercardforproduct":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("TransferBonus", "actionbonustransfer");
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				break;
			case "packaged_mandatory":
			case "packaged_product":
			case "packaged_optional":
			case "packaged_hidden":
			case "available_product":
			case "member_product":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Product");
				break;
			case "attribute_featurecode":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select FeatureCode");
				break;
			case "tree_node_counter_main_basic_prepaid":
			case "tree_node_counter_main_basic_postpaid":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Condition Set", "conditioncommonand");
				/*
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				*/
				break;
			case "tree_node_counter_main_basic_prepaid_removable":
			case "tree_node_counter_main_basic_postpaid_removable":
			case 'tree_node_counter_main_rollover_prepaid':
			case 'tree_node_counter_main_rollover_postpaid':
			case "tree_node_counter_main_optional_prepaid":
			case "tree_node_counter_main_optional_postpaid":
			case 'actionblockfactors':
			case 'tree_node_counter_accumulated_optional_prepaid':
			case 'tree_node_counter_accumulated_optional_postpaid':
			case 'tree_node_counter_accumulated_rollover_prepaid':
			case 'tree_node_counter_accumulated_rollover_postpaid':
			case "actionpriceallowancerecurring":
			case "actionpriceallowance":
			case "actionpricechargefactors":
			case "actionpricediscountfactors":
			case "actionpriceallowancefactors":
			case 'treenodepacketpredefined':
			case 'treenodepacketdynamic':
			case 'treenodepacketdefaultqos':
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Condition Set", "conditioncommonand");
				break;
				/*
			case "treeNodeCugDiscount":
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Action Price Discount", "actionpricecugdiscountfactors");
				break;
				*/
			case "actionpricecugdiscountfactors":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Condition Set", "conditioncommonand");
				break;
			case "counter_main":
			case "counter_shared":
			case "counter_accumulated":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Counter");
				break;
			case "nonusage_deposit":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Deposit Scheme");
				break;
			case 'nonusage_otheronetimecharge':
			case 'nonusage_otheronetimecharge_discount_on_main':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Other Onetime Charge");
				break;
			case 'nonusage_bonus_transfer':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Voucher Card Type");
				break;
			case "nonusage_threshold":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Threshold Scheme");
				break;
			case "nonusage_unittransfer_scheme":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Unit Transfer Scheme");
				break;
			case "attribute_subscriber_lifecycle_scheme":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Select Lifecycle Scheme");
				break;
			case 'nonusage_rollover':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("RollOver", "prdnonusagerollover");
				break;
			case "treeNodeCustomCharge":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Charge Factors", "actionpricechargefactors");
				break;
			case "treeNodeCustomDiscount":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Discount Factors", "actionpricediscountfactors");
				break;
			case "treeNodeCustomBlock":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Block Service Factors", "actionblockfactors");
				break;
			case "treeNodeCustomAllowance":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Allowance Factors", "actionpriceallowancefactors");
				break;
			case 'nonusage_fee_onetime':
			
			case "nonusage_unsubscription_charge":
			case "nonusage_unsubscription_penalty":
			case "nonusage_unittransfer_charge":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Charge Item", "actionpricechargeonetime");
				break;
			case "nonusage_subscription_charge":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Charge Item", "actionpricechargeonetime");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
				};
				break;
			case 'nonusage_fee_recurring_custom':
			//case 'nonusage_recurring_charge':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Charge Item", "actionpricechargerecurring");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
				};
				break;
			case "nonusage_subscription_bonus":
			case "nonusage_activation_bonus":
			case "nonusage_recharge_bonus":
			case "nonusage_usageend_bonus":
			case "nonusage_recurring_bonus":
			case "nonusage_group_bonus_bonus":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Bonus Item", "actionpriceallowanceonetime");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
				};
				break;
			case "nonusage_unittransfer_discount":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Discount", "actionpricediscount");
				break;
			case "nonusage_unsubscription_discount":
			case "nonusage_recurring_discount_on_main":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Discount", "actionpricediscount");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
				};
				break;
			case "nonusage_subscription_discount":
			case "nonusage_recurring_discount":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Discount", "actionpricediscount");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
				};
				break;
			case "conditionwhatqos":
			case "conditionwhaturlgroupfactors":
			case "conditionwhatcounter":
			case "conditionwhatcustomfactors":
			case "conditionwhatusagetypefactors":
			case "conditionwhatnonusagetypefactors":
			case "conditionwhendayfactors":
			case "conditionwhendurationfactors":
			case "conditionwhenholidayfactors":
			case "conditionwhendayofmonth":
			case "conditionwhenstatechangedate":
			case "conditionwhenbillingdate":
			case "conditionwhenactivedays":
			case "conditionwhentimeslotfactors":
			// case "conditionwhencallingzonetime":
			case "conditionwhenweekfactors":
			case "conditionwherecountryfactors":
			case "conditionwherenetworkfactors":
			case "conditionwherecallerzone":
			case "conditionwherecalleezone":
			case "conditionwherecustomfactors":
			case "conditionwhereclientip":
			case "conditionwheremacaddress":
			case "conditionwheredevicetype":
			case "conditionwhereserviceid":
			case "conditionwehreapn":
			case "conditionwhomemberfactors":
			case "conditionwhonumberfactors":
			case "conditionwhosubscribermdn":
			case "conditionwhosubscriberstatus":
			case "conditionwhoprefixfactors":
			case "conditionwhocustom":
			case "conditionwhocustomerlevel":
			case 'conditionwhatcardtype':
			case 'conditionwhereissamezone':
			case 'conditionwherezonefactors':
			case 'conditionwhocalledcarrier':
			case 'actionbonustransfer':
			case "prdattributeprefixrangeallowed":
			case "prdnonusagerollover":
			case "treenodespecialnumberscheme":
			case "prdattributeprefixrangenotallowe":
			case 'prdattributefeaturecode':
			case 'prdattributepackaged':
			//case "simpleproductoffering":
			case 'treenodeotheronetimecharge':
			case 'treenodedepositscheme':
			case 'treenodethresholdscheme':
			case 'treenodeunittransferscheme':
			case 'treenodelifecyclescheme':
			case 'conditionwhatincomingcall':
			case 'conditionwhatisvideo':
			case 'conditionwhatisgroupcall':
			case 'conditionwhatmainproduct':
			case 'conditionwhatmainproductforpeer':
			case 'conditionwhensubscriptionday':
			case 'conditionwhentodaysubscriptionda':
			case 'conditionwhenactivationday':
			// case 'conditionwhencompanybirthday':
			case 'conditionwhencustomerbirthday':
			case 'conditionwhenstatechangedate':
			case 'conditionwhenbillingdate':
			case "prdattributerequireddevice":
			case "prdattributenumbersaving":
			case "prdattributeavailablechannel":
			case "prdattributeallowedmodel":
			case 'basicrate_data':
			case 'conditionwhoroamingcarrier':
			case 'conditionwhereroamingcountry':
			case 'conditionwhereroamingzone':
			case 'conditionwhatroamingtype':
			case 'conditionwhererattype':
			case 'conditionwheresgsn':
			case 'conditionwheresgsnip':
			case 'conditionwhereapn':
			case 'conditionwhatservicedomain':
			case 'conditionwhatcontentprice':
			case 'conditionwhatcalltype':
			case 'conditionwhatbilltype':
			case 'conditionwhatfeaturecode':
			case 'conditionwhatisredirected':
			// case 'conditionwhenvaliddate':
			case 'treenodeotheronetimechargediscou':
			case 'conditionwhocugadminstatus' :
			case 'conditionwhocugadminproductstatu' :
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				break;
			case "usage_voice":
			case "mobile_usage_voice":
			case "cross_mobile_usage_voice":
			case "cross_voip_usage_voice":
			case "voip_usage_voice":
			case "usage_sms":
			case "mobile_usage_sms":
			case "cross_mobile_usage_sms":
			case "voip_usage_sms":
			case "cross_voip_usage_sms":
			case "usage_data":
			case "mobile_usage_data":
			case "cross_mobile_usage_data":
			case "usage_mms":
			case "mobile_usage_mms":
			case "cross_mobile_usage_mms":
			case "usage_crbt":
			case "mobile_usage_crbt":
			case "cross_mobile_usage_crbt":
			case "usage_vod":
			case "mobile_usage_vod":
			case "cross_mobile_usage_vod":
			case "iptv_usage_vod":
			case "cross_iptv_usage_vod":
			case "usage_loyaltypoint":
			case "mobile_usage_loyaltypoint":
			case "iptv_usage_loyaltypoint":
			case "voip_usage_loyaltypoint":
			case "broadband_usage_loyaltypoint":
			case "satellite_usage_loyaltypoint":
			case "dummy_usage_loyaltypoint":
			case "cross_mobile_usage_loyaltypoint":
			case "cross_voip_usage_loyaltypoint":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Tariff Plan", "tariffplan");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
				};
				break;
			case "attribute_required_device":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Required Device");
				break;
			case "attribute_available_channel":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Available Channel");
				break;
			case "voice_tariffplan_specialnumber":
			case "sms_tariffplan_specialnumber":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select SpecialNumberScheme");
				break;
			case "attribute_allowed_device":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Allowed Device");
				break;
			case "data_tariffplan_predefined":
			case "cross_mobile_data_tariffplan_predefined":
			case "data_tariffplan_dynamic":
			case "cross_mobile_data_tariffplan_dynamic":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Rule");
				break;
			case "data_tariffplan_qos":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Default QoS", "treenodepacketdefaultqos");
				break;
			case 'data_tariffplan_basicrate':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("BasicRate", "basicrate_data");
				break;
			case "tariffplan":
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				menus.custom_copy._disabled = false;
				menus.custom_copy.action = function(node) {
					$.fn.copyNode(node);
				};
			  break;
			case "actionpricechargeonetime":
			case "actionpricediscount":
			case "actionpriceallowanceonetime":
			case "actionpricechargerecurring":
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				menus.custom_create._disabled = false;
     		menus.custom_create.submenu = $.fn.getSubMenuAddNode("Condition Set", "conditioncommonand");
 				menus.custom_copy._disabled = false;
				menus.custom_copy.action = function(node) {
					$.fn.copyNode(node);
				};
				break;
			case "conditioncommonand_usage_voice":
			case "conditioncommonand_usage_sms":
				var who = $.fn.getConditionWhoType1();
				var where = $.fn.getConditionWhereType2();
				var what = $.fn.getConditionWhatType5();
				var when = $.fn.getConditionWhenType1();
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"who_" : {
						"label" : "Who",
						"submenu" : who
					},
					"where_" : {
						"label" : "Where",
						"submenu" : where
					},
					"what" : {
						"label" : "What",
						"submenu" : what
					},
					"when" : {
						"label" : "When",
						"submenu" : when
					},
				};
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				break;
			case "conditioncommonand_usage_data":
				var who = $.fn.getConditionWhoType2();
				var where = $.fn.getConditionWhereType3();
				var what = $.fn.getConditionWhatType3();
				var when = $.fn.getConditionWhenType1();
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"who_" : {
						"label" : "Who",
						"submenu" : who
					},
					"where_" : {
						"label" : "Where",
						"submenu" : where
					},
					"what" : {
						"label" : "What",
						"submenu" : what
					},
					"when" : {
						"label" : "When",
						"submenu" : when
					},
				};
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				break;
			case "conditioncommonand_usage_mms":
			case "conditioncommonand_usage_vod":
			case "conditioncommonand_usage_crbt":
			case "conditioncommonand_usage_loyalty_point_deduct":
				var who = $.fn.getConditionWhoType2();
				var where = $.fn.getConditionWhereType4();
				var what = $.fn.getConditionWhatType3();
				var when = $.fn.getConditionWhenType1();
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"who_" : {
						"label" : "Who",
						"submenu" : who
					},
					"where_" : {
						"label" : "Where",
						"submenu" : where
					},
					"what" : {
						"label" : "What",
						"submenu" : what
					},
					"when" : {
						"label" : "When",
						"submenu" : when
					},
				};
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				break;
			default:
				menus.custom_create = null;
				menus.custom_copy = null;
				menus.custom_paste = null;
				menus.custom_delete = null;
				break;
		}
		return menus;
	};

	$.fn.getSubMenuAddNode = function(label, childContentType) {
		var obj = {
			"addNodeObject" : {
				"label" : label,
				"action" : function(node) {
					$.fn.addNode(node, {
						'childContentType' : childContentType
					});
				}
			}
		};
		return obj;
	};

	$.fn.getSubMenuAddNodeWithoutWrapper = function(label, childContentType) {
		var obj = {
			"label" : label,
			"action" : function(node) {
				$.fn.addNode(node, {
					'childContentType' : childContentType
				});
			}
		};
		return obj;
	};

	$.fn.getSubMenuLoadSelectForm = function(label) {
		var obj = {
			"loadSelectFormObject" : {
				"label" : label,
				"action" : function(node) {
					$.fn.loadSelectForm(node);
				}
			}
		};
		return obj;
	};

	$.fn.getConditionWhoType1 = function() {
		var obj = {
			"Subscriber MDN" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber MDN", "conditionwhosubscribermdn"),
			"Subscriber Status" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber Status", "conditionwhosubscriberstatus"),
			"Called Number" : $.fn.getSubMenuAddNodeWithoutWrapper("Called Number", "conditionwhoprefixfactors"),
			"Carrier (Called)" : $.fn.getSubMenuAddNodeWithoutWrapper("Carrier (Called)", "conditionwhocalledcarrier"),
			"Customer Level" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Level", "conditionwhocustomerlevel"),
			"Roaming Carrier" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Carrier", "conditionwhoroamingcarrier"),
			"CUG Admin Status" : $.fn.getSubMenuAddNodeWithoutWrapper("CUG Admin Status", "conditionwhocugadminstatus"),
			"CUG Admin Product Status" : $.fn.getSubMenuAddNodeWithoutWrapper("CUG Admin Product Status", "conditionwhocugadminproductstatu"),
		};
		return obj;
	};

	$.fn.getConditionWhoType2 = function() {
		var obj = {
			"Subscriber MDN" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber MDN", "conditionwhosubscribermdn"),
			"Subscriber Status" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber Status", "conditionwhosubscriberstatus"),
			"Customer Level" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Level", "conditionwhocustomerlevel"),
		};
		return obj;
	};

	$.fn.getConditionWhoType3 = function() {
		var obj = {
			"Subscriber Status" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber Status", "conditionwhosubscriberstatus"),
			"Customer Level" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Level", "conditionwhocustomerlevel"),
		};
		return obj;
	};

	$.fn.getConditionWhereType1 = function() {
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone", "conditionwherecallerzone"),
			"Callee Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee Zone", "conditionwherecalleezone"),
			"Caller/Callee in SameZone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller/Callee in SameZone", "conditionwhereissamezone"),
			"Client IP" : $.fn.getSubMenuAddNodeWithoutWrapper("Client IP", "conditionwhereclientip"),
			"Client MAC Address" : $.fn.getSubMenuAddNodeWithoutWrapper("Client MAC Address", "conditionwheremacaddress"),
			"Client Device Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Client Device Type", "conditionwheredevicetype"),
			"Service ID" : $.fn.getSubMenuAddNodeWithoutWrapper("Service ID", "conditionwhereserviceid"),
			"Roaming Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Zone", "conditionwhereroamingzone"),
			"Roaming Country" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Country", "conditionwhereroamingcountry"),
			"RAT Type" : $.fn.getSubMenuAddNodeWithoutWrapper("RAT Type", "conditionwhererattype"),
			"SGSN" : $.fn.getSubMenuAddNodeWithoutWrapper("SGSN", "conditionwheresgsn"),
			"SGSN IP" : $.fn.getSubMenuAddNodeWithoutWrapper("SGSN IP", "conditionwheresgsnip"),
			"APN" : $.fn.getSubMenuAddNodeWithoutWrapper("APN", "conditionwhereapn"),			
		};
		return obj;
	};

	$.fn.getConditionWhereType2 = function() {
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone", "conditionwherecallerzone"),
			"Callee Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee Zone", "conditionwherecalleezone"),
			"Caller/Callee in SameZone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller/Callee in SameZone", "conditionwhereissamezone"),
			"Roaming Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Zone", "conditionwhereroamingzone"),
			"Roaming Country" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Country", "conditionwhereroamingcountry"),
		}
		return obj;
	};

	$.fn.getConditionWhereType3 = function() {
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone", "conditionwherecallerzone"),
			"Client IP" : $.fn.getSubMenuAddNodeWithoutWrapper("Client IP", "conditionwhereclientip"),
			"Client MAC Address" : $.fn.getSubMenuAddNodeWithoutWrapper("Client MAC Address", "conditionwheremacaddress"),
			"Client Device Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Client Device Type", "conditionwheredevicetype"),
			"Service ID" : $.fn.getSubMenuAddNodeWithoutWrapper("Service ID", "conditionwhereserviceid"),
			"RAT Type" : $.fn.getSubMenuAddNodeWithoutWrapper("RAT Type", "conditionwhererattype"),
			"SGSN" : $.fn.getSubMenuAddNodeWithoutWrapper("SGSN", "conditionwheresgsn"),
			"SGSN IP" : $.fn.getSubMenuAddNodeWithoutWrapper("SGSN IP", "conditionwheresgsnip"),
			"APN" : $.fn.getSubMenuAddNodeWithoutWrapper("APN", "conditionwhereapn"),			
		};
		return obj;
	};

	$.fn.getConditionWhereType4 = function() {
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone", "conditionwherecallerzone")
		};
		return obj;
	};

	$.fn.getConditionWhereType5 = function() {
		var obj = {
			"Client IP" : $.fn.getSubMenuAddNodeWithoutWrapper("Client IP", "conditionwhereclientip"),
			"Client MAC Address" : $.fn.getSubMenuAddNodeWithoutWrapper("Client MAC Address", "conditionwheremacaddress"),
			"Client Device Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Client Device Type", "conditionwheredevicetype"),
		};
		return obj;
	};

	$.fn.getConditionWhatType1 = function() {
		var obj = {
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"NonUsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("NonUsageType", "conditionwhatnonusagetypefactors"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),			
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),	
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),			
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Rating Group" : $.fn.getSubMenuAddNodeWithoutWrapper("Rating Group", "conditionwhatratinggroup"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};

	$.fn.getConditionWhatType2 = function() {
		var obj = {
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer"),
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),
		};
		return obj;
	};

	$.fn.getConditionWhatType3 = function() {
		var obj = {
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),	
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer"),
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),			
			"Content Price" : $.fn.getSubMenuAddNodeWithoutWrapper("Content Price", "conditionwhatcontentprice"),
			"Rating Group" : $.fn.getSubMenuAddNodeWithoutWrapper("Rating Group", "conditionwhatratinggroup"),
		};
		return obj;
	};

	$.fn.getConditionWhatType4 = function() {
		var obj = {
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),			
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),			
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),	
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};

	$.fn.getConditionWhatType5 = function() {
		var obj = {
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),						
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),			
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),	
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};

	$.fn.getConditionWhatType6 = function() {
		var obj = {
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"NonUsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("NonUsageType", "conditionwhatnonusagetypefactors"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};

	$.fn.getConditionWhatType7 = function() {
		var obj = {
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType8 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"NonUsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("NonUsageType", "conditionwhatnonusagetypefactors"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),						
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),			
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),					
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),	
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Rating Group" : $.fn.getSubMenuAddNodeWithoutWrapper("Rating Group", "conditionwhatratinggroup"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType9 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType10 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType11 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),						
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),			
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),					
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),		
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType12 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),						
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),			
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),					
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),			
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Rating Group" : $.fn.getSubMenuAddNodeWithoutWrapper("Rating Group", "conditionwhatratinggroup"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType13 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),		
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};
	
	$.fn.getConditionWhatType14 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),						
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),			
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),					
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),		
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};
	
	$.fn.getConditionWhatType15 = function() {
		var obj = {
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"NonUsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("NonUsageType", "conditionwhatnonusagetypefactors"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Content Price" : $.fn.getSubMenuAddNodeWithoutWrapper("Content Price", "conditionwhatcontentprice"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};
	
	$.fn.getConditionWhatType16 = function() {
		var obj = {
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Content Price" : $.fn.getSubMenuAddNodeWithoutWrapper("Content Price", "conditionwhatcontentprice"),
		};
		return obj;
	};

	$.fn.getConditionWhenType1 = function() {
		var obj = {
			"Day" : $.fn.getSubMenuAddNodeWithoutWrapper("Day", "conditionwhendayfactors"),
			"Day of Month" : $.fn.getSubMenuAddNodeWithoutWrapper("Day of Month", "conditionwhendayofmonth"),
			"Bill Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Bill Date", "conditionwhenbillingdate"),
			"Subscription Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscription Date", "conditionwhensubscriptionday"),
			"Today Is Subscription Day" : $.fn.getSubMenuAddNodeWithoutWrapper("Today is SubscriptionDay", "conditionwhentodaysubscriptionda"),
			"Activation Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Activation Date", "conditionwhenactivationday"),
			"Active Days" : $.fn.getSubMenuAddNodeWithoutWrapper("Active Days", "conditionwhenactivedays"),
			"Customer Birthday" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Birthday", "conditionwhencustomerbirthday"),
			// "Company Anniversary" : $.fn.getSubMenuAddNodeWithoutWrapper("Company Anniversary", "conditionwhencompanybirthday"),
			"Duration" : $.fn.getSubMenuAddNodeWithoutWrapper("Duration", "conditionwhendurationfactors"),
			"Holiday" : $.fn.getSubMenuAddNodeWithoutWrapper("Holiday", "conditionwhenholidayfactors"),
			"Timeslot" : $.fn.getSubMenuAddNodeWithoutWrapper("Timeslot", "conditionwhentimeslotfactors"),
			"Week" : $.fn.getSubMenuAddNodeWithoutWrapper("Week", "conditionwhenweekfactors"),
			// "Calling Zone Time" : $.fn.getSubMenuAddNodeWithoutWrapper("Calling Zone Time", "conditionwhencallingzonetime"),
			// "Valid Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Valid Date", "conditionwhenvaliddate")
		};
		return obj;
	};

	$.fn.getConditionWhenType2 = function() {
		var obj = {
			"Day" : $.fn.getSubMenuAddNodeWithoutWrapper("Day", "conditionwhendayfactors"),
			"Day of Month" : $.fn.getSubMenuAddNodeWithoutWrapper("Day of Month", "conditionwhendayofmonth"),
			"Bill Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Bill Date", "conditionwhenbillingdate"),
			"Subscription Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscription Date", "conditionwhensubscriptionday"),
			"Today Is Subscription Day" : $.fn.getSubMenuAddNodeWithoutWrapper("Today is SubscriptionDay", "conditionwhentodaysubscriptionda"),
			"Activation Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Activation Date", "conditionwhenactivationday"),
			"Active Days" : $.fn.getSubMenuAddNodeWithoutWrapper("Active Days", "conditionwhenactivedays"),
			"Customer Birthday" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Birthday", "conditionwhencustomerbirthday"),
			// "Company Anniversary" : $.fn.getSubMenuAddNodeWithoutWrapper("Company Anniversary", "conditionwhencompanybirthday"),
			"Duration" : $.fn.getSubMenuAddNodeWithoutWrapper("Duration", "conditionwhendurationfactors"),
			"Holiday" : $.fn.getSubMenuAddNodeWithoutWrapper("Holiday", "conditionwhenholidayfactors"),
			"Timeslot" : $.fn.getSubMenuAddNodeWithoutWrapper("Timeslot", "conditionwhentimeslotfactors"),
			"Week" : $.fn.getSubMenuAddNodeWithoutWrapper("Week", "conditionwhenweekfactors"),
			// "Valid Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Valid Date", "conditionwhenvaliddate")
		};
		return obj;
	};
})(jQuery);
;
(function($) {
	$.fn.getTreeTypeSetting = function(treeType) {
	var types = {};
	switch (treeType) {
	case 'product_tree':
		types = {
			"types" : {
            	"simpleproductoffering": {
            		"valid_children" : "none",
            		"icon" : {
                		// "image" : "/sites/default/files/applications.png"
                		"image" : "/sites/default/files/icons/service_domain_mobile.png"
                	},
				},
				
				// Attribute
				///////////////////////////////////////////////////////////////
				"attribute": {
					"valid_children" : "none",
							"icon" : {
                		"image" : "/sites/default/files/icons/attribute.png"
                	},
				},
				
				'attribute_featurecode': {
					"valid_children" : ["prdattributefeaturecode"],
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				"prdattributefeaturecode" : {
					"valid_children" : "none",
				  "icon" : {
							"image" : "/sites/default/files/file.png"
				  }
				},
				'attribute_allowed_prefix': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				 
				'attribute_benefits': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				
				'attribute_prerequisite_deposit_condition': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				
				'attribute_number_saving': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				
				'attribute_deposit_amount': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				
				'attribute_available_channel': {
					"valid_children" : ["prdattributeavailablechannel"],
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				
				'attribute_allowed_device': {
					"valid_children" : ["prdattributeallowedmodel"],
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
						'prdattributeallowedmodel': {
							"valid_children" : "none",
							  		"icon" : {
							      		"image" : "/sites/default/files/icons/device.png"
							      	},
						},
						
				'attribute_required_device': {
					"valid_children" : ["prdattributerequireddevice"],
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
							'prdattributerequireddevice': {
								"valid_children" : "none",
								  		"icon" : {
								      		"image" : "/sites/default/files/icons/device.png"
								      	},
							},
							
				'attribute_subscriber_lifecycle_scheme': {
					"valid_children" : ["treenodelifecyclescheme"],
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
						'treenodelifecyclescheme': {
							"valid_children" : "none",
							  		"icon" : {
							      		"image" : "/sites/default/files/icons/scheme.png"
							      	},
						},
				"prdattributeprefixrangeallowed" :{
						"valid_children" : "none",
				    "icon" : {
							"image" : "/sites/default/files/file.png"
				    }
				},
				"prdattributeprefixrangenotallowe" : {
					"valid_children" : "none",
				  "icon" : {
							"image" : "/sites/default/files/file.png"
				  }
				},
					
				// Auto Join Product
				///////////////////////////////////////////////
				"attribute_packaged" : {
					"valid_children" : "none",
					"icon" : {
                		"image" : "/sites/default/files/icons4use/puzzle.png"
                	},
				},
				"packaged_mandatory" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/tick-octagon.png"
                	},
				},
				"packaged_optional" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/octagon-plus.png"
                	},
				},
				"packaged_hidden" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/lock.png"
                	},
				},
				"packaged_product" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/octagon-plus.png"
                	},
				},
				"prdattributepackaged" : {
							"valid_children" : "none",
							"icon" : {
									"image" : "/sites/default/files/icons/file.png"
								},
				},
				"member_product" : {
							"valid_children" : "prdattributepackaged",
							"icon" : {
									"image" : "/sites/default/files/icons/tick-octagon.png"
								},
				},
				
	
				// COUNTER
				///////////////////////////////////////////////////////
				"counter" : {
					"valid_children" : "none",
					"icon" : {
				        		"image" : "/sites/default/files/icons/battery.png"
				        	},
				},
				"counter_main" : {
					"valid_children" : ["tree_node_counter_main_basic_prepaid", 									
															"tree_node_counter_main_basic_postpaid",
															"tree_node_counter_main_basic_prepaid_removable", 									
															"tree_node_counter_main_basic_postpaid_removable",
															"tree_node_counter_main_optional_prepaid",
															"tree_node_counter_main_optional_postpaid",
				            					"tree_node_counter_main_rollover_prepaid",
				            					"tree_node_counter_main_rollover_postpaid"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
				},
				"counter_accumulated": {
						"valid_children" : ["tree_node_counter_accumulated_optional_prepaid",
																"tree_node_counter_accumulated_optional_postpaid",
																"tree_node_counter_accumulated_rollover_prepaid",
																"tree_node_counter_accumulated_rollover_prepaid"],
				        	"icon" : {
				        			"image" : "/sites/default/files/icons/inbox-document.png"
				        		},
				},
				"counter_shared": {
						"valid_children" : ["tree_node_counter_main_basic_prepaid", 									
																"tree_node_counter_main_basic_postpaid",
																"tree_node_counter_main_basic_prepaid_removable", 									
																"tree_node_counter_main_basic_postpaid_removable",
																"tree_node_counter_main_optional_prepaid",
																"tree_node_counter_main_optional_postpaid",
						          					"tree_node_counter_main_rollover_prepaid",
						          					"tree_node_counter_main_rollover_postpaid"],
				        	"icon" : {
				        			"image" : "/sites/default/files/icons/inbox-document.png"
				        		},
				},
				"treenodecounter" :{
						"valid_children" : ["conditioncommonand"],
				    "icon" : {
							"image" : "/sites/default/files/file.png"
				            }
				},
				"tree_node_counter_main_basic_prepaid" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Basic_Prepaid.png"
				            }
				},
				"tree_node_counter_main_basic_postpaid" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Basic_Postpaid.png"
				            }
				},
				
				"tree_node_counter_main_basic_prepaid_removable" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Basic_Prepaid.png"
				            }
				},
				"tree_node_counter_main_basic_postpaid_removable" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Basic_Postpaid.png"
				            }
				},
				
				
				"tree_node_counter_main_optional_prepaid" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Optional_Prepaid.png"
				            }
				        },
				"tree_node_counter_main_optional_postpaid" : {
					"valid_children" : [ "conditioncommonand" ],
						    "icon" : {
						"image" : "/sites/default/files/icons/Optional_Postpaid.png"
				    }
				},
				"tree_node_counter_main_rollover_prepaid" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Rollover_Prepaid.png"
				            }
				        },
				"tree_node_counter_main_rollover_postpaid" : {
					"valid_children" : [ "conditioncommonand" ],
						    "icon" : {
						"image" : "/sites/default/files/icons/Rollover_Postpaid.png"
				    }
				},
												
				"tree_node_counter_accumulated_optional_prepaid" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Optional_Prepaid.png"
				            }
				},
				"tree_node_counter_accumulated_optional_postpaid" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Optional_Postpaid.png"
				            }
				        },
				        
				"tree_node_counter_accumulated_rollover_prepaid" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Rollover_Prepaid.png"
				            }
				},
				"tree_node_counter_accumulated_rollover_postpaid" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Rollover_Postpaid.png"
				            }
				        },

				// NON USAGE
				//////////////////////////////////////////////
				"nonusage" : {
					"valid_children" : "none",
					"icon" : {
							"image" : "/sites/default/files/icons/wheel.png"
					},
				},
				"nonusage_subscription" : {
					"valid_children" : "none",
					"icon" : {
					"image" : "/sites/default/files/icons/ui-menu.png"
					        },
				},
				"nonusage_subscription_charge" : {
					"valid_children" : ["actionpricechargeonetime"],
					"icon" : {
					"image" : "/sites/default/files/icons/money.png"
					        }
				},
				"nonusage_subscription_discount" : {
					"valid_children" : ["actionpricediscount"],
					"icon" : {
					"image" : "/sites/default/files/icons/discount.png"
					}
				},
				"nonusage_subscription_bonus" : {
					"valid_children" : ["actionpriceallowanceonetime"],
				"icon" : {
						"image" : "/sites/default/files/icons/point.png"
					},
				},
				
				// Activation
				"nonusage_activation" : {
					"valid_children" : "none",
					"icon" : {
					"image" : "/sites/default/files/icons/ui-menu.png"
					        }
				},
				"nonusage_activation_bonus" : {
					"valid_children" : ["actionpriceallowanceonetime"],
				"icon" : {
						"image" : "/sites/default/files/icons/point.png"
					},
				},
				
				// Group Bonus
				"nonusage_group_bonus" : {
					"valid_children" : "none",
					"icon" : {
					"image" : "/sites/default/files/icons/ui-menu.png"
					        }
				},
				"nonusage_group_bonus_bonus" : {
					"valid_children" : ["actionpriceallowanceonetime"],
					"icon" : {
						"image" : "/sites/default/files/icons/point.png"
					},
				},
				
				// UnSubscription
				"nonusage_unsubscription" : {
					"valid_children" : "none",
					"icon" : {
					"image" : "/sites/default/files/icons/ui-menu.png"
					        }
				},
				"nonusage_unsubscription_charge" : {
					"valid_children" : ["actionpricechargeonetime"],
					"icon" : {
					"image" : "/sites/default/files/icons/money.png"
					        }
				},
				"nonusage_unsubscription_discount" : {
					"valid_children" : ["actionpricediscount"],
					"icon" : {
					"image" : "/sites/default/files/icons/discount.png"
					        }
				},
				"nonusage_unsubscription_penalty" : {
					"valid_children" : ["actionpricechargeonetime"],
					"icon" : {
					"image" : "/sites/default/files/icons/money.png"
					        }
				},
				
				// Recharge
				"nonusage_recharge" : {
					"valid_children" : "none",
					"icon" : {
					"image" : "/sites/default/files/icons/ui-menu.png"
					        }
				},
				"nonusage_voucher" : {
					"valid_children" : "none",
							"icon" : {
									"image" : "/sites/default/files/icons/voucher.png"
								},
						},
				"nonusage_recharge_voucher" : {
					"valid_children" : "none",
							"icon" : {
									"image" : "/sites/default/files/icons/voucher.png"
								},
						},
        "nonusage_recharge_bonus" : {
        	"valid_children" : ["actionpriceallowanceonetime"],
		        "icon" : {
    	    		"image" : "/sites/default/files/icons/point.png"
      	  	},
        },
        
        // Usage end
        "nonusage_usageend" : {
        	"valid_children" : "none",
        	"icon" : {
        	"image" : "/sites/default/files/icons/ui-menu.png"
        	        }
        },
        "nonusage_usageend_bonus" : {
        	"valid_children" : ["actionpriceallowanceonetime"],
        "icon" : {
        		"image" : "/sites/default/files/icons/point.png"
        	},
        },
        
        // Recurring
        "nonusage_recurring" : {
        	"valid_children" : "none",
        	"icon" : {
        	"image" : "/sites/default/files/icons/ui-menu.png"
        	        }
        },
        
        "nonusage_fee_recurring_custom" : {
        	"valid_children" : ["actionpricechargerecurring"],
        	"icon" : {
        	"image" : "/sites/default/files/icons/money.png"
        	        }
        },
        "nonusage_fee_recurring_default" : {
        	"valid_children" : ["actionpricechargerecurringdefaul"],
        	"icon" : {
        	"image" : "/sites/default/files/icons/money.png"
        	        }
        },
        "nonusage_fee_recurring_by_cs" : {
        	"valid_children" : ["actionpricechargerecurringbycs"],
        	"icon" : {
        	"image" : "/sites/default/files/icons/money.png"
        	        }
        },
        "actionpricechargerecurringbycs" : {
		        "valid_children" : [],
    		    	"icon" : {
        		"image" : "/sites/default/files/icons/money.png"
            }
        },
        "actionpricechargerecurring" : {
		        "valid_children" : [ "conditioncommonand",
		                             "conditioncommonand_nonusage_recurring"],
    		    	"icon" : {
        		"image" : "/sites/default/files/icons/money.png"
            }
        },
        "actionpricechargerecurringdefaul" : {
		        "valid_children" : [],
    		    	"icon" : {
        		"image" : "/sites/default/files/icons/money.png"
            }
        },
        "nonusage_recurring_charge" : {
        	"valid_children" : ["actionpricechargerecurring"],
        	"icon" : {
        	"image" : "/sites/default/files/icons/money.png"
        	        }
        },
        "nonusage_recurring_discount" : {
        	"valid_children" : ["actionpricediscount"],
        	"icon" : {
        	"image" : "/sites/default/files/icons/discount.png"
        	        }
        },
        "nonusage_recurring_discount_on_main" : {
        	"valid_children" : ["actionpricediscount"],
        	"icon" : {
        	"image" : "/sites/default/files/icons/discount.png"
        	        }
        },
        "nonusage_recurring_bonus" : {
        	"valid_children" : ["actionpriceallowanceonetime"],
        "icon" : {
        		"image" : "/sites/default/files/icons/point.png"
        	},
        },
        
        // Unit Transfer
        "nonusage_unittransfer" : {
        	"valid_children" : ["nonusage_unittransfer_scheme"],
        	"icon" : {
        	"image" : "/sites/default/files/icons/ui-menu.png"
        	        }
        },
        "nonusage_unittransfer_scheme" : {
        	"valid_children" : ["treenodeunittransferscheme"],
        	"icon" : {
        			"image" : "/sites/default/files/icons/scheme.png"
        		},
        },
        "treenodeunittransferscheme" : {
        	"valid_children" : "none",
        	"icon" : {
        			"image" : "/sites/default/files/icons/file.png"
        		},
        },
        "nonusage_deposit" : {
        	"valid_children" : ["treenodedepositscheme"],
        "icon" : {
        		"image" : "/sites/default/files/icons4use/user.png"
        	},
        },
		        "treenodedepositscheme" : {
		        	"valid_children" : "none",
		        	"icon" : {
		        		"image" : "/sites/default/files/file.png"
		        	}
		        },
        "nonusage_threshold" : {
        	"valid_children" : ["treenodethresholdscheme"],
        	"icon" : {
        		"image" : "/sites/default/files/icons/threshold.png"
        	}
        },
		        "treenodethresholdscheme" : {
			      	"valid_children" : "none",
			      	"icon" : {
			      		"image" : "/sites/default/files/file.png"
			      	}
			      },
			  "nonusage_otheronetimecharge" : {
        	"icon" : {
        	"image" : "/sites/default/files/icons/ui-menu.png"
        	        }
        },
        "nonusage_otheronetimecharge_discount_on_main" : {
        	"icon" : {
        	"image" : "/sites/default/files/icons/discount.png"
        	        }
        },
            "treenodeotheronetimecharge" : {
		        	"valid_children" : "none",
		        	"icon" : {
		        	"image" : "/sites/default/files/icons/money.png"
		        	        }	
		        },
		     "treenodeotheronetimechargediscou" : {
		     	"valid_children" : "none",
		     	"icon" : {
		     	"image" : "/sites/default/files/icons/discount.png"
		     	        }	
		     },   
		    "actionpriceallowanceonetime" : {
		    	"valid_children" : [					"conditioncommonand",
		    											"conditioncommonand_nonusage_subscription",
		    											"conditioncommonand_nonusage_unsubscription",
		    											"conditioncommonand_nonusage_activation",
		    											"conditioncommonand_nonusage_recharge",
		    											"conditioncommonand_nonusage_usageend",
		    											"conditioncommonand_nonusage_recurring"],
		    	"icon" : {
		    	"image" : "/sites/default/files/icons/file.png"
		    	        }
		    },
		        
				
				// USAGE
				///////////////////////////////////////////////////
				// Usage
				"usage" : {
					"valid_children" : "none",
					"icon" : {
								"image" : "/sites/default/files/icons/system-monitor.png"
					}
				},
				"usage_mms" : {
        	"valid_children" : ["tariffplan"],
        	"icon" : {
        		"image" : "/sites/default/files/icons/MMS.png"
        	}
        },
				"usage_crbt" : {
					"valid_children" : ["tariffplan"],
					"icon" : {
						"image" : "/sites/default/files/icons/CRBT.png"
					}
				},
				"usage_loyaltypoint" : {
					"valid_children" : ["tariffplan"],
					"icon" : {
						"image" : "/sites/default/files/icons/Loyalty_Point.png"
					}
				},
				"usage_vod" : {
					"valid_children" : ["tariffplan"],
					"icon" : {
						"image" : "/sites/default/files/icons/VOD.png"
					}
				},
				
				"usage_voice" : {
        	"valid_children" : ["tariffplan"],
        	"icon" : {
        		"image" : "/sites/default/files/icons/Voice.png"
        	}
        },
                
        "usage_sms" : {
        	"valid_children" : ["tariffplan"],
        	"icon" : {
        		"image" : "/sites/default/files/icons/SMS.png"
        	}
        },
        "usage_data" : {
          	"valid_children" : ["tariffplan"],
          	"icon" : {
          		"image" : "/sites/default/files/icons/Data02.png"
          	}
          },
          
				"tariffplan" :{
						"valid_children" : "none",
				    "icon" : {
						"image" : "/sites/default/files/icons/plan.png"
				    }
				},
				"treenodenumberingplandomestic" :{
				    "valid_children" : "none",
				    "icon" : {
						"image" : "/sites/default/files/file.png"
				            }
				},
				 "treenodenumberingplanidd" :{
				 "valid_children" : "none",
				 		"icon" : {
						"image" : "/sites/default/files/file.png"
				            }
					},
				
				"treeNodeBasicRateIDD" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/icons/basic_rate.png"
					},
				},
							"voice_tariffplan_domestic" : {
								"valid_children" : "none",
								"icon" : {
									"image" : "/sites/default/files/icons/basic_rate.png"
								},
							},
							"voice_tariffplan_international" : {
								"valid_children" : "none",
								"icon" : {
									"image" : "/sites/default/files/icons/basic_rate.png"
								}
							},
							"voice_tariffplan_roaming" : {
								"valid_children" : "none",
								"icon" : {
									"image" : "/sites/default/files/icons/basic_rate.png"
								}
							},
							"voice_tariffplan_specialnumber" : {
								"valid_children" : ["treenodespecialnumberscheme"],
								"icon" : {
									"image" : "/sites/default/files/icons/basic_rate.png"
								}
							},
										"treenodespecialnumberscheme" : {
											"valid_children" : "none",
											"icon" : {
												"image" : "/sites/default/files/icons/scheme.png"
											}
										},
				
				// Custom Rate
				"treeNodePlanCustom" : {
					"valid_children" : "none",
						"icon" : {
									"image" : "/sites/default/files/icons/custom_rate.png"
					  },
				},
				"treeNodeCustomCharge" : {
					"valid_children" : ["actionpricechargefactors"],
					"icon" : {
					"image" : "/sites/default/files/icons/money.png"
					        }
				},
							"actionpricechargefactors" : {
								"valid_children" : [
																		"conditioncommonand",
																		"conditioncommonand_usage_voice",
																		"conditioncommonand_usage_sms",
																		"conditioncommonand_usage_data",
																		"conditioncommonand_usage_mms",
																		"conditioncommonand_usage_crbt",
																		"conditioncommonand_usage_vod",
																		"conditioncommonand_usage_loyalty_point_deduct",
								],
								"icon" : {
									"image" : "/sites/default/files/icons/file.png"
								}
							},
				
				"treeNodeCustomDiscount" : {
					"valid_children" : ["actionpricediscountfactors"],
					"icon" : {
							"image" : "/sites/default/files/icons/discount.png"
					        }
				},
				
				"treeNodeCugDiscount" : {
					"valid_children" : ["actionpricecugdiscountfactors"],
					"icon" : {
							"image" : "/sites/default/files/icons/discount.png"
					        }
				},
				
							"actionpricediscountfactors" : {
								"valid_children" : [
																		"conditioncommonand",
																		"conditioncommonand_usage_voice",
																		"conditioncommonand_usage_sms",
																		"conditioncommonand_usage_data",
																		"conditioncommonand_usage_mms",
																		"conditioncommonand_usage_crbt",
																		"conditioncommonand_usage_vod",
																		"conditioncommonand_usage_loyalty_point_deduct",
								],
								"icon" : {
									"image" : "/sites/default/files/icons/file.png"
								}

							},

							"actionpricecugdiscountfactors" : {
								"valid_children" : [
																		"conditioncommonand",
																		"conditioncommonand_usage_voice",
																		"conditioncommonand_usage_sms",
								],
								"icon" : {
									"image" : "/sites/default/files/icons/file.png"
								}
							},
							
				"treeNodeCustomBlock" : {
					"valid_children" : ["actionblockfactors"],
					"icon" : {
						"image" : "/sites/default/files/icons/custom_block.png"
					        }
				},
							"actionblockfactors" : {
								"valid_children" : ["conditioncommonand_usage_voice",
																		"conditioncommonand_usage_sms",
																		"conditioncommonand_usage_data",
																		"conditioncommonand_usage_mms",
																		"conditioncommonand_usage_crbt",
																		"conditioncommonand_usage_vod",
																		"conditioncommonand_usage_loyalty_point_deduct",
								],
								"icon" : {
									"image" : "/sites/default/files/icons/file.png"
								}
							},
							
				"data_tariffplan_predefined" : {
					"valid_children" : ["treenodepacketpredefined"],
					"icon" : {
						"image" : "/sites/default/files/icons/basic_rate.png"
					 }
				},
							"treenodepacketpredefined" : {
								"valid_children" : ["conditioncommonand_usage_data"],
								"icon" : {
									"image" : "/sites/default/files/icons/file.png"
								}
							},
							
				"data_tariffplan_dynamic" : {
					"valid_children" : ["treenodepacketdynamic"],
					"icon" : {
						"image" : "/sites/default/files/icons/basic_rate.png"
					 }
				},
				"data_tariffplan_qos" : {
					"valid_children" : ["treenodepacketdefaultqos"],
					"icon" : {
						"image" : "/sites/default/files/icons/basic_rate.png"
					 }
				},
							"treenodepacketdefaultqos" : {
								"valid_children" : ["conditioncommonand_usage_data"],
								"icon" : {
									"image" : "/sites/default/files/icons/file.png"
								}
							},
							
				"data_tariffplan_rates" : {
					"valid_children" : "none",
					"icon" : {
							"image" : "/sites/default/files/icons/basic_rate.png"
					}
				},
							"data_tariffplan_basicrate" : {
									"valid_children" : ["basicrate_data"],					
									"icon" : {
											"image" : "/sites/default/files/icons/basic_rate.png"
									        }
							},
							"basicrate_data" : {
									"valid_children" : "none",
									"icon" : {
											"image" : "/sites/default/files/icons/basic_rate.png"
									 },
							},
				
				// Action Charge Discount 
				"conditioncommonand_nonusage_subscription" : {
        			"valid_children" : "none",
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        
        "conditioncommonand_nonusage_recurring" : {
                			"valid_children" : "none",
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_nonusage_usageend" : {
                			"valid_children" : "none",
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_nonusage_recharge" : {
                			"valid_children" : "none",
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_nonusage_unsubscription" : {
                			"valid_children" : "none",
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_nonusage_activation" : {
                			"valid_children" : "none",
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },

				"conditioncommonand_usage_sms" : {
				            "icon" : {
						"image" : "/sites/default/files/icons/conditioncommonand.png"
				            }
				        },

        "conditioncommonand_usage_voice" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_usage_data" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_usage_mms" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_usage_crbt" : {
        			"valid_children" : ["tariffplan"],
        				      "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_usage_loyalty_point_deduct" : {
        			"valid_children" : ["tariffplan"],
 							"icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_usage_vod" : {
        			"valid_children" : ["tariffplan"],
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
                
				"conditionwhendayfactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhatmainproduct" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhatmainproductforpeer" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhendurationfactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhenholidayfactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhentimeslotfactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhenweekfactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhenstatechangedate" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhenbilldate" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhenvaliddate" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherecountryfactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherenetworkfactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherezonefactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherecustomfactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhomemberfactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhonumberfactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhoprefixfactors" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhocustom" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhocustomerlevel" : {
					"valid_children" : "none",
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				
			}
		};
		break;
		
	case 'vouchercardtype_tree':
		types = {
			"types" : {
            	"vouchercardtype": {
            		"valid_children" : ["voucher_domain_specific", "voucher_product_specific"],
            		"icon" : {
                		"image" : "/sites/default/files/applications.png"
                	},
				},
				"voucher_domain_specific": {
					"valid_children" : ["voucher_domain_specific_mobile", "voucher_domain_specific_iptv", "voucher_domain_specific_broadband", "voucher_domain_specific_voip","voucher_domain_specific_satellite","voucher_domain_specific_dummy"],
					"icon" : {
						"image" : "/sites/default/files/folder.png"
					},
				},
				"voucher_product_specific": {
					"valid_children" : ["treenodeproductforvoucher"],
					//"icon" : {
					//	"image" : "/sites/default/files/folder.png"
					//},
				},
				"discount_voucher_product_specific": {
					"valid_children" : ["treenodeproductfordisvoucher"],
					"icon" : {
						"image" : "/sites/default/files/folder.png"
					},
				},
				
				"treenodeproductforvoucher" : {
					"valid_children" : ["none"],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				}
			}
		};
		break;
	} // switch
	
	return types;
};
})(jQuery);
;
(function($) {	
	$.fn.cloneProduct = function(){
		var productId = $('.product_catalog_tree > ul:first > li:first').attr('id');
		var cloneLink = '/product_catalog_ajax/clone_product/' + productId;
		$.fn.masking("Cloning...");
		$.ajax({
			url : cloneLink,
			success : function(data) {
				var output = $.parseJSON(data);				
				//console.log(output);
				$.fn.unmasking();
				$(location).attr('href',output);
			}
		});
	};
	
	$.fn.pasteNode = function(node){
		var nodeId = node.attr('id');
		var productId = $('.product_catalog_tree > ul:first > li:first').attr('id');
		var max_weight = node.children('ul').children('li').first().attr('weight');
		if(max_weight == undefined) max_weight = 0;
		var pasteLink = '/product_catalog_ajax/paste_node/' + nodeId + '/' + productId + '/' + max_weight;
		$.fn.masking("Pasting...");
		$.ajax({
			url : pasteLink,
			success : function(data) {
				var output = $.parseJSON(data);				
				//console.log(output);
				//console.log(output.success);
				if(output.success){
						$.fn.addNestedMultipleChildren(output.product_catalog_ajax_result);
				}else{
					alert(output.reason);
				}
				$.fn.unmasking();
			}
		});
	};
	
	$.fn.copyNode = function(node){
		var nodeId = node.attr('id');
		var copyLink = '/product_catalog_ajax/copy_node/' + nodeId;
		$.fn.masking("Copying...");
		$.ajax({
			url : copyLink,
			success : function(data) {
				var output = $.parseJSON(data);				
				//console.log(output);
				$.fn.unmasking();
			}
		});
	};
	
	$.fn.loadSelectForm = function(node){
		var nodeId = node.attr('id');
		var rootId = $('.product_catalog_tree > ul:first > li:first').attr('id');
		var loadLink = '/product_catalog_ajax/load_select_form/' + nodeId + '/' + 'right_click' + '/' + rootId + '/' + node.attr('rel');
		$.fn.masking("Loading...");
		//console.log(loadLink);
		$.ajax({
			url : loadLink,
			success : function(data) {
				//console.log('loadSelectForm');
	    		//console.log(data);
				var output = $.parseJSON(data);
				//console.log(output);
				var settings = output[0].settings;
				var context = output[1];
				$('#tree_content_div').replaceWith(context);
				//console.log(output);
				if( typeof settings.views != 'undefined') {
					$.extend(Drupal.settings.views.ajaxViews,settings.views.ajaxViews);
				}
				
				$.fn.behaviorAttach(settings);
				
				$isNotEmpty = $('#tree_content_div').find('.view');
				console.log('isEmpty');
				console.log($isNotEmpty);
				
				if($isNotEmpty.length != 0) {
					$('#tree_content_div').append('<div style="clear:both;"><input id="vbo-select-button" type="button" value="Select"/></div>');
					$('#vbo-select-button').bind('click',{rootId:rootId, node: node},$.fn.selectItemHandler);
				}
				
				$.fn.unmasking();
			}
		});
	};
	
	$.fn.selectModalButtonBinding = function(renderOutput, nid, defaultTabIndex, refTreeTid) {		
		
		// $.fn.behaviorAttach(renderOutput);
		
		$('#vbo-message-select-button').bind('click', {nid:nid, defaultTabIndex:defaultTabIndex, refTreeTid:refTreeTid}, $.fn.selectMessageItemHandler);
		
	};

	/*	
	$.fn.bindCounterTypeValidator = function() {
		$('#edit-field-ref-counter-und').bind('change', $.fn.counterTypeChangeHandler);
	};
	*/
	
	$.fn.counterTypeChangeHandler = function(event){
	
		var counterId = event.currentTarget.value;
		
		var ajaxLink = '/product_catalog_ajax/check_rollover_type/' + counterId;
		$.fn.masking("Waiting...");
		$.ajax({
			url : ajaxLink,
			success : function(data) {
				var output = $.parseJSON(data);
				//if(output == true) $('#node_actionsetcounter_form_group_end_date').hide();
				$.fn.unmasking();
			}
		});
		
		// $('#node_actionsetcounter_form_group_end_date').hide();
	};
		
	$.fn.selectMessageItemHandler = function(event) {
		var loadLink = '/product_catalog_ajax/select_modal_item/actionsetnotification';
		
		var inputItems = $('input[name^=views_bulk_operations]:checked');
		if(inputItems.length == 0) {
			// �ν� Drupal message ���濡�蹂�꼍??
			alert('No Item Selected!');
			
		}else{
			var selectedItemNid = new Array();
			for(var i=0;i<inputItems.length;i++) {
				selectedItemNid[i] = inputItems[i].value;
			}
		}
		
		$.fn.modalMasking('Selecting ...');
		$.ajax({
			url : loadLink,
			type: "post",
			data: {'nids': selectedItemNid, 'source_nid': event.data.nid, 'default_tab_index': event.data.defaultTabIndex, 'ref_tree_tid': event.data.refTreeTid},
			success : function(data) {
				$.fn.modalUnmasking();
				Drupal.CTools.Modal.dismiss();
				
				if( event.data.refTreeTid != null ) {
					node = $('[id^="term_' + event.data.refTreeTid +'"]');
				} else {
					node = $('#node_' + event.data.nid);
				}
				
				//console.log('selectedItemNid');
				//console.log(selectedItemNid);
				//console.log('source action nid');
				//console.log(event.data.nid);
				
				$.fn.loadForm(node,null,event.data.defaultTabIndex);
			}
		});
	};
	
	// select_load_form -> selectItemHandler
	//
	$.fn.selectItemHandler = function(event){
		
	var parent = event.data.node; 
    var rootId = event.data.rootId;
		//jQuery('input[name=views_bulk_operations]:checked')		
		var inputItems = $('input[name^=views_bulk_operations]:checked');
		
		if(inputItems.length == 0) {
			alert('No Item Selected!');
			
		}else{
			var selectedItemNid = new Array();
			for(var i=0;i<inputItems.length;i++) {
				selectedItemNid[i] = inputItems[i].value;
			}
			
		    var max_weight = parent.children('ul').children('li').first().attr('weight');
		    if(max_weight == 'undefined') max_weight = 0;
		    var min_weight = parent.children('ul').children('li').last().attr('weight');
		    if(min_weight == 'undefined') min_weight = 0;
		    
			var selectItemUrl = '/product_catalog_ajax/select_item';
			$.fn.masking("Adding...");
			$.ajax({
				url : selectItemUrl,
				type: "post",
		        data: {'product_nid': rootId, 'parent_nid': parent.attr('id'), 'child_nid': selectedItemNid, 'rel_type': parent.attr('rel'),'max_weight':max_weight, 'min_weight':min_weight,'parent_title':parent.children('a').text()},
				success : function(data) {
					//console.log('selectItemHandler');
					//console.log(data);
					var output = $.parseJSON(data);
					
					var product_catalog_ajax_result = output[0].settings.product_catalog_ajax_result;
					
					// 留�� 湲곗〈���щ���� children��吏��二쇱�����寃쎌���� 
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
					$.fn.unmasking();
				}
			});
			
		}		
	};
	
	$.fn.clearTreeContentDiv = function(message){
		$('#tree_content_div').replaceWith('<div id="tree_content_div" style="overflow:scroll;height:700px;"></div>');
		if(message != 'undefined') $('#tree_content_div').prepend(message);
	};
	
	$.fn.deleteFromView = function(parent_id,id,content_type){
		var deleteUrl = '/product_catalog_ajax/delete_from_view/' + id;
		var parentNode = $('#'+parent_id);
		$.fn.masking("Deleting...");
		$.ajax({
			url : deleteUrl,
			success : function(data) {
				switch(content_type){
				case 'basicrate_domestic':
					$.fn.loadForm(parentNode,null);
					break;
				case 'basicrate_idd':
					$.fn.loadForm(parentNode,null);
					break;
				}
				$.fn.unmasking();
				//$.fn.loadForm(parent_id,content_type);
			}
		});	
	};
	
	$.fn.loadForm = function(node,collapsedIndex,defaultTabIndex){
		
		var id = node.attr("id");
        var content_type = node.attr("node_type");
        var rel_type = node.attr("rel");
        
		var needToLoadEdit = true; 
        var needToLoadDetail = true;
        var needToBindCustomSubmitButtons = false;
        
        switch(content_type){
            case 'treenodecounter':
            case 'treenodedepositscheme':
            case 'treenodethresholdscheme':
            case 'treeNodeBasicRateIDD':
            case 'treenodevouchercardforproduct':
            case 'prdattributepackaged':
            case "treenodeproductforvoucher":
            case "treenodeproductfordisvoucher":
            case 'treenodeunittransferscheme':
            case 'actionpricechargeonetime':
            case 'actionpriceallowanceonetime':
            case 'actionpricechargerecurring':
            case 'actionpricechargerecurringdefaul':
            case 'actionpriceallowancerecurring':
            case 'prdnonusagerollover':
            case 'treenodelifecyclescheme':
               	needToLoadEdit = false;
                break; 
            case 'usage':
            case 'conditioncommonor':
            case 'conditioncommonand':
            case 'defaulttreenode':
            case 'treenodepacketpredefined': 
            case 'prdattributeallowedmodel':
            case 'prdattributeavailablechannel':
            case 'prdattributefeaturecode':
            case 'actionpricecugdiscountfactors':
            	needToLoadEdit = false;
            	needToLoadDetail = false;
            	break; 
            case 'treenodespecialnumberscheme':
            	needToLoadEdit = false;
            	break;
            case 'treenodewithnodereference':
            	switch(rel_type){
            	case 'treenode_timetable':
            		needToLoadDetail = false;
            		break;
                case 'treenode_simpleproductoffering':
                    needToLoadEdit = false;
                    break;
            	default:
            		needToLoadEdit = false;
            		break;
            	}
            	break;
            case 'number_special':
            	needToLoadDetail = false;
            	break;
            case 'term':
            	switch(rel_type){
            	case 'voice_tariffplan_domestic':
            	case 'voice_tariffplan_international':   
            	case 'voice_tariffplan_roaming':
            	case 'sms_tariffplan_domestic':
            	case 'sms_tariffplan_international': 
            	case 'sms_tariffplan_roaming':
            	case 'mobile_counter':
            	case 'mobile_nonusage_rollover':
            		needToLoadEdit = false;
            		needToBindCustomSubmitButtons = true;
            		break;
            	}
            	
            	case 'allowed':
            		needToLoadEdit = false;
            		break;
            	break; 
            	           
            case 'treenodecounterforvoucherprd':
            	needToLoadEdit = false;
        		needToBindCustomSubmitButtons = true;
        		break;
            default :
            	needToLoadDetail = false;
            	break;
        }
        
        // �대� content type��edit form�������
        if(needToLoadEdit){
            var editLink = '/product_catalog_ajax/nojs/edit/' + content_type + '/' + id;
            $.fn.masking("Loading...");
    		$.ajax({
    			url : editLink,
    			success : function(data) {
    				var output = $.parseJSON(data);
    				var settings = output[0].settings;
    				var context = output[1];
    				$('#tree_content_div').replaceWith(context);
    				$.fn.behaviorAttach(settings);
    				//bind product clone button
    				$('#product_clone_button').bind('click',$.fn.cloneProduct);
    				$.fn.unmasking();
    			}
    		});
        }
        
        if(needToLoadDetail){
        	var rootId = $('.product_catalog_tree > ul:first > li:first').attr('id');
        	var detailLink = '/product_catalog_ajax/load_select_form/' + id + '/' + 'click' + '/' + rootId + '/' + rel_type;
        	
        	if(defaultTabIndex > 0) {
        		detailLink = detailLink + '/' + defaultTabIndex;
        	}
    		
        	$.fn.masking("Loading...");
    		$.ajax({
    			url : detailLink,
    			success : function(data) {
    				
    				//console.log('loadForm');
    				//console.log(data);
    				
    				var output = $.parseJSON(data);
    				var settings = output[0].settings;
    				var context = output[1];
    				$('#tree_content_div').replaceWith(context);
    				$.fn.behaviorAttach(settings);
    				
    				//for basicrate
    				if(needToBindCustomSubmitButtons){
    					var tariffplanNid = $('#tariffplanNid').attr('value');
    					var refTreeTid = $('#refTreeTid').attr('value');
    					
    					$('#select_numberingplan_domestic').bind('click',
    							{'type':'select_numberingplan_domestic'
    							,'node':node
    							,'tariffplanNid':tariffplanNid
    							,'refTreeTid':refTreeTid}
    					   ,$.fn.customSubmitButtonHandler);
    					$('#select_timetable_domestic').bind('click',
    							{'type':'select_timetable_domestic'
    							,'node':node
    							,'tariffplanNid':tariffplanNid
    							,'refTreeTid':refTreeTid}
    					   ,$.fn.customSubmitButtonHandler);
    					$('#select_numberingplan_domestic_incoming').bind('click',
    							{'type':'select_numberingplan_domestic_incoming'
    							,'node':node
    							,'tariffplanNid':tariffplanNid
    							,'refTreeTid':refTreeTid}
    					   ,$.fn.customSubmitButtonHandler);
    					$('#select_timetable_domestic_incoming').bind('click',
    							{'type':'select_timetable_domestic_incoming'
    							,'node':node
    							,'tariffplanNid':tariffplanNid
    							,'refTreeTid':refTreeTid}
    					   ,$.fn.customSubmitButtonHandler);
    					$('#select_numberingplan_idd').bind('click',
    							{'type':'select_numberingplan_idd'
    							,'node':node
    							,'tariffplanNid':tariffplanNid
    							,'refTreeTid':refTreeTid}
    					   ,$.fn.customSubmitButtonHandler);
    					$('#select_timetable_idd').bind('click',
    							{'type':'select_timetable_idd'
    							,'node':node
    							,'tariffplanNid':tariffplanNid
    							,'refTreeTid':refTreeTid}
    					   ,$.fn.customSubmitButtonHandler);
    					$('#select_roamingplan').bind('click',
    							{'type':'select_roamingplan'
    							,'node':node
    							,'tariffplanNid':tariffplanNid
    							,'refTreeTid':refTreeTid} 
    					   ,$.fn.customSubmitButtonHandler);
    				}    		
    				
    				//selected region
    				if(collapsedIndex != null){
    					$.fn.setFocuseSelectedRegion(collapsedIndex);
    				}
    				
    				$.fn.unmasking();
    			} 
    		});
        }
	};
	
	$.fn.setFocuseSelectedRegion = function(collapsedIndex){
		var regions = $('#tree_content_div').find('.ctools-toggle');
		
		for(var i=0;i<regions.length;i++){	
			if($.inArray(i, collapsedIndex) > -1){				
				$('#tree_content_div').find('.ctools-toggle:eq('+i+')').addClass('ctools-toggle-collapsed');
				$('#tree_content_div').find('.ctools-collapsible-content:eq('+i+')').attr('style','display:none');
			}else{
				$('#tree_content_div').find('.ctools-toggle:eq('+i+')').removeClass('ctools-toggle-collapsed');
				$('#tree_content_div').find('.ctools-collapsible-content:eq('+i+')').attr('style','display:block');
			}				
		}		
	};
	
	$.fn.customSubmitButtonHandler = function(event){		
		var isSelect = false;
		var data = event.data;		
		
		switch(data.type){
		case 'select_numberingplan_domestic':			
		case 'select_numberingplan_domestic_incoming':			
		case 'select_numberingplan_idd':			
		case 'select_timetable_domestic':
		case 'select_timetable_domestic_incoming':
		case 'select_timetable_idd':
		case 'select_roamingplan':
			isSelect = true;
			break;
		}
		
		if(isSelect){
			var findStr = '\'.' + data.type + '_rows > div > input[name^=views_bulk_operations]:checked\'';			
			var inputItems = $(findStr);
			
			if(inputItems.length == 0){
				// �ν� Drupal message ���濡�蹂�꼍??
				alert('No Item Selected!');
			}else{
				$.fn.masking('Progress..');
				var selectedItemNid = new Array();
				for(var i=0;i<inputItems.length;i++){
					selectedItemNid[i] = inputItems[i].value;
				}
				
				var customSubmitUrl = '/product_catalog_ajax/custom_submit';				
				$.ajax({
					url : customSubmitUrl,
					type: "post",
			        data: {'type': data.type, 'tariffplanNid': data.tariffplanNid, 'refTreeTid': data.refTreeTid, 'selected_nid': selectedItemNid},
					success : function(result) {
						$.fn.reloadTreeContentDiv(data.node);			
					}
				});
				
			}
		}
		
	};
	
	$.fn.reloadTreeContentDiv = function(node, tabIndex){
		//for setFocusRegion
		var regions = $('#tree_content_div').find('.ctools-toggle');
		var collapsedIndex = new Array();
		for(var i=0;i<regions.length;i++){	
			if($('#tree_content_div').find('.ctools-toggle:eq('+i+')').hasClass('ctools-toggle-collapsed')){
				collapsedIndex.push(i);
			}
		}
		$.fn.loadForm(node,collapsedIndex, tabIndex);	
	};
	
	/*
	$.fn.reloadTreeContentDivFromDrupal = function(nodeId, tabIndex){
		var node = $('#' + nodeId);
		console.log('here');
		console.log(tabIndex);
		$.fn.reloadTreeContentDiv(node);
	};
	*/
	
	$.fn.reloadTreeContentDivFromDrupal = function(nodeId, tabIndex){
		var node = $('#' + nodeId);
		
		$.fn.reloadTreeContentDiv(node, tabIndex);
	};
	
	$.fn.addNestedMultipleChildren = function(product_catalog_ajax_result){		
		var parentNode;
		var returnData;
		var tree = $.jstree._reference(".product_catalog_tree");
		//console.log(product_catalog_ajax_result);
		var parentNid = product_catalog_ajax_result.parent_nid;
		if( parentNid instanceof Array) {
			var parent_id = null;
			for(var i=0;i<parentNid.length;i++){
				if(product_catalog_ajax_result.parent_nid[i] != null){
					parent_id = product_catalog_ajax_result.parent_nid[i];
					break;
				}
			}
			
			parentNode = $('#'+parent_id);
		}else{
			parentNode = $('#'+product_catalog_ajax_result.parent_nid);
		}
		returnData = tree._parse_json(product_catalog_ajax_result.data);
		
        var attachChild = returnData.children("li");
        if(!parentNode.children("ul").length) { parentNode.append("<ul />"); }
        parentNode.children("ul").prepend(attachChild);
        tree.clean_node(parentNode);
        $(".product_catalog_tree").jstree("open_node", attachChild , function (){} , false);        
		
	};
	
	$.fn.addUnNestedMultipleChildren = function(product_catalog_ajax_result){		
		var parentNode;		
		parentNode = $('#'+product_catalog_ajax_result.data.parent_nid);		
		
		for(var i=0;i<product_catalog_ajax_result.data.children.length;i++){
			$(".product_catalog_tree").jstree("create", parentNode,product_catalog_ajax_result.data.append_to
				,{"data" : product_catalog_ajax_result.data.children[i].data
				,"attr" : {"id" : product_catalog_ajax_result.data.children[i].attr.id
						  ,"node_type" : product_catalog_ajax_result.data.children[i].attr.node_type
						  ,"rel" : product_catalog_ajax_result.data.children[i].attr.rel
						  ,"weight" : product_catalog_ajax_result.data.children[i].attr.weight}}, function() {}, true);	
				
		}		
	};
	
	$.fn.behaviorAttach = function(settings){	
		//console.log('mutiselect_behavior set');
		delete Drupal.settings.views.ajaxViews;
		Drupal.behaviors.quicktabs.attach(document,settings);
		Drupal.behaviors.ViewsAjaxView.attach();		
		//Drupal.behaviors.multiselect.attach(document);		
		Drupal.behaviors.AJAX.attach(document, settings);
		Drupal.settings.datePopup = settings.datePopup;
		Drupal.behaviors.date_popup.attach(document);
		Drupal.behaviors.tableDrag.attach(document, settings);
		Drupal.behaviors.tableHeader.attach(document, settings);	
		Drupal.behaviors.states.attach(document,settings);	
		Drupal.behaviors.vbo.attach(document);
		Drupal.behaviors.ZZCToolsModal.attach(document);
		Drupal.behaviors.editablefields_submit.attach(document);
		Drupal.behaviors.CToolsAutoSubmit.attach(document);
    //Drupal.behaviors.bef_live_filter.attach(document);
		
    Drupal.behaviors.CToolsCollapsible.attach(document);
    Drupal.behaviors.jQueryUIMultiselect.attach(document,settings);
    //Drupal.behaviors.jquery_ui_multiselect_widget.attach(document,settings);
    //Drupal.behaviors.qt_accordion.attach($('#tree_content_div'),settings);
    //Drupal.behaviors.qt_ui_tabs.attach(document,settings);
    
    //$.fn.drawFlotLinkInit();
    
    //resizable
    /*
    var leftPane = $(".panels-flexible-region-first").last();
    var rightPane = $(".panels-flexible-region-last").last();
    var maximumLeftWidth = $("#content").width();
    var leftHeight = leftPane.height();
    
    leftPane.resizable({
			maxWidth: maximumLeftWidth,
			minHeight: leftHeight,
			maxHeight: leftHeight
		});
		
		leftPane.resize(function() {
			rightPane.width($("#content").width() - leftPane.width());
		});
		*/
  };
	
	
	
	/*
	$.fn.getParentIdWithRelType = function(node,relType){
		var parentId = node.attr('parent_nid');
		var parentNode = $('#'+parentId);
		var parentRelType = parentNode.attr('rel');
		
		if(relType == parentRelType) {
			return parentId;
		} 
		else {
			return $.fn.getParentIdWithRelType(parentNode,relType);
		}
	};
	*/
	
	$.fn.addNode = function(parentNode, param) {
		$("#tree_node_op").val('add');
		//console.log(childContentType);
		var parentNodeId = parentNode.attr('id');
		var max_weight = parentNode.children('ul').children('li').first().attr('weight');
		if(max_weight == undefined) max_weight = 0;
		var rootId = $('.product_catalog_tree > ul:first > li:first').attr('id');
        var addLink = '/product_catalog_ajax/nojs/add/';
        
        var ajaxParam = {'root_id': rootId, 'parent_id': parentNodeId, 'child_content_type': param.childContentType
	        	, 'max_weight': max_weight, 'usage_type' : param.usageType, 'nonusage_type' : param.nonUsageType};
        
        /*
        switch(parentNode.attr('rel')){
	        case 'voice_tariffplan_domestic':
	        case 'voice_tariffplan_international':
	        case 'voice_tariffplan_specialnumbers':
	        case 'treeNodeCustomCharge':
	        case 'treeNodeCustomDiscount':
	        case 'treeNodeCustomAllowance':
	        	var tariffPlanId = $.fn.getParentIdWithRelType(parentNode,'tariffplan');
	        	
	        	ajaxParam.tariffplan_id = tariffPlanId;
	        	break;
        }
        */
        
        $.fn.masking("Adding...");
		$.ajax({
			url : addLink,
			type: "post",
	        data: ajaxParam,
			success : function(data) {
				var output = $.parseJSON(data);			
				if(output != null){
					if(output instanceof Array == false){
						$.fn.addTreeItemCallback(output.parent_id, output.child_id,output.title, output.node_type, output.weight, output.rel_type);
					}else{
						var settings = output[0].settings;
						var context = output[1];
						$('#tree_content_div').replaceWith(context);
						$.fn.behaviorAttach(settings);
					}
				}
				$.fn.unmasking();
			}
		});
	};
	
	$.fn.getChildrenNotSelf = function(node) {
		
		var children = new Array();
		
		var parent = $('.product_catalog_tree').jstree('get_json', parent)[0];
		
		if (node.children != null) {
			for ( var index = 0; index < node.children.length; index++) {
				$.merge(children, $.fn.getChildren(node.children[index]));
			}
		} else if ((node.metadata != null)
				&& (node.metadata.jstree_children != null)) {
			for ( var index = 0; index < node.metadata.jstree_children.length; index++) {
				$.merge(children,$.fn.getChildren(node.metadata.jstree_children[index]));
			}
		}

		if (children.length > 0) {
			return children;
		} else {
			return children;
		}
	};
	
	$.fn.getChildren = function(node) {
		var children = new Array();

		children.push(node.attr.id);

		if (node.children != null) {
			for ( var index = 0; index < node.children.length; index++) {
				$.merge(children, $.fn.getChildren(node.children[index]));
			}
		} else if ((node.metadata != null)
				&& (node.metadata.jstree_children != null)) {
			for ( var index = 0; index < node.metadata.jstree_children.length; index++) {
				$.merge(children,$.fn.getChildren(node.metadata.jstree_children[index]));
			}
		}

		if (children.length > 0) {
			return children;
		} else {
			return;
		}
	};

	$.fn.deleteNode = function(node) {
		$.fn.masking("Deleting...");
		var jsonData = $(".product_catalog_tree").jstree("get_json", node);
		var children = $.fn.getChildren(jsonData[0]);
		//console.log(jsonData[0]);
		var delLink = '/product_catalog_ajax/nojs/delete_from_tree';

		$.ajax({
			url : delLink,
			type : 'POST',
			dataType : 'json',
			data : {
				"nodes" : children
			},
			success : function(data) {
				var rel_type = node.attr("rel");
				$.jstree._focused().delete_node(node);
				$.fn.clearTreeContentDiv();
				$.fn.unmasking();
				
				switch(rel_type) {
					case 'simpleproductoffering':
					case 'number_special':
					case 'vouchercardtype':
					case 'unittransfer':
						$(location).attr('href', data.urlpath);
						break;
				}
				
				/*
				if(rel_type === 'simpleproductoffering'){
					$(location).attr('href',"/product_designer/Mobile#quickset-products=2");
				}else if(rel_type === 'number_special'){
					$(location).attr('href',"/common/vouchercardtype#quickset-qtabs_common_data=6");
				}else if(rel_type === 'vouchercardtype'){
					$(location).attr('href',"/common/vouchercardtype");
				}*/
									
			}
		});
        //history.go(0);
	};	
	 
	$.fn.addTreeItemCallback = function(parentId, childId, title,contentType, weight, relType) {
		$.fn.masking("Adding...");
		$(".product_catalog_tree").jstree("create", $('#' + parentId),"inside", {"data" : title,"attr" : {"id" : childId,"node_type" : contentType,"rel" : relType,"weight" : weight}}, function() {}, true);
		$.fn.unmasking();
	};
	
	$.fn.masking = function(message){ 
		$("#content").mask(message);
	};
	$.fn.unmasking = function(){
		$("#content").unmask();
	}
	
	$.fn.modalMasking = function(message){
		$("#modal-content").mask(message);
	};
	$.fn.modalUnmasking = function(){
		$("#modal-content").unmask();
	};
	
	//operation
	$.fn.treeOpExpand = function(){
		var nodeId = $('.product_catalog_tree').jstree('get_selected').attr('id');
		var node = $('#'+nodeId);
		$('.product_catalog_tree').jstree('open_all',node,0);
	}
	$.fn.treeOpClose = function(){
		var nodeId = $('.product_catalog_tree').jstree('get_selected').attr('id');
		var node = $('#'+nodeId);
		$('.product_catalog_tree').jstree('close_all',node,0);
	}
	$.fn.treeOpSearch = function(){
		$searchText = $('#tree_op_search_input').val();
		$('.product_catalog_tree').jstree('search',$searchText);
	}
	$.fn.treeOpSearchClear = function(){
		$('#tree_op_search_input').val('');
		$('.product_catalog_tree').jstree('clear_search');
	}

})(jQuery);
;
(function($) {
	Drupal.behaviors.ProductCatalogTreeBehavior = {
		attach : function(context, settings) {
			$('#dummy-link').hide();
			$.jstree._themes = settings.themes_dir;
			//console.log(context);
			//console.log(settings);

			//bind ajax success callback. changes tree node's title		
				
			$(document).ajaxSuccess(function(event,request, settings) {	
				//console.log(settings.url);
				if(settings.url === '/system/ajax'){
					//console.log(event);
					//console.log(request);
					//console.log(settings);
					var triggeringElement = settings.extraData._triggering_element_name;
					//console.log(triggeringElement);
					if(triggeringElement.match('submit-field_ref_timetable_idd') != null){
						//refresh if tariffplan_idd_carrier has changed its timetable.
						var nodeId = $('.product_catalog_tree').jstree('get_selected').attr('id');
						var node = $('#'+nodeId);
						$.fn.reloadTreeContentDiv(node, 0);						
					}else if(triggeringElement === 'op' && 
							settings.extraData._triggering_element_value === 'Save'){
						var op = $("#tree_node_op").val();
						
						var responseText = request.responseText; 
						var responseJson = $.parseJSON(responseText);
						//console.log(responseJson);
						var product_catalog_ajax_result = responseJson[0].settings.product_catalog_ajax_result;
					
						//console.log(product_catalog_ajax_result);
						//console.log(responseJson);
						if(typeof product_catalog_ajax_result != 'undefined'){
							if(op === 'edit'){		
								// counter list를 보여주고자 할 때에는 변경된 부분을 보이기 위해 전체 tree를 refresh한다.
								var needToReloadAll = false;		
								if(product_catalog_ajax_result.need_to_reload_all instanceof Array){
									for(var i=0;i<product_catalog_ajax_result.need_to_reload_all.length;i++){
										if(needToReloadAll == true) break;
										needToReloadAll = product_catalog_ajax_result.need_to_reload_all[i];
									}
								}else{
									needToReloadAll = product_catalog_ajax_result.need_to_reload_all;
								}
								
								var needToRefreshNode = false;
								if(product_catalog_ajax_result.need_to_refresh_node instanceof Array){
									for(var i=0;i<product_catalog_ajax_result.need_to_refresh_node.length;i++){
										if(needToRefreshNode == true) break;
										needToRefreshNode = product_catalog_ajax_result.need_to_refresh_node[i];
									}
								}else{
									needToRefreshNode = product_catalog_ajax_result.need_to_refresh_node;
								}
								
								if(needToReloadAll){
									var treeData = $.parseJSON(product_catalog_ajax_result.data[0]);
					
									$.jstree._focused()._get_settings().json_data.data = treeData;
									$.jstree._focused().refresh(-1);
				
									$.fn.unmasking();
				
									$(".product_catalog_tree").jstree('open_all');
								}
								else if(needToRefreshNode){
									var nodeId = null;
									if(product_catalog_ajax_result.reload_node_id instanceof Array){
										for(var i=0;i<product_catalog_ajax_result.reload_node_id.length;i++){
											if(nodeId != null) break;
											nodeId = product_catalog_ajax_result.reload_node_id[i];
										}
									}else{
										nodeId = product_catalog_ajax_result.reload_node_id;
									}
									var node = $('#' + nodeId);
									$.fn.reloadTreeContentDiv(node);
								}
								else{
									if( product_catalog_ajax_result.data.nid instanceof Array) {
										$(".product_catalog_tree").jstree("set_text", $('#' + product_catalog_ajax_result.data.nid[0]), product_catalog_ajax_result.data.title[0]);
									}else{
										$(".product_catalog_tree").jstree("set_text", $('#' + product_catalog_ajax_result.data.nid), product_catalog_ajax_result.data.title);
									}
								}
							}else if(op === 'add'){
								$.fn.addNestedMultipleChildren(product_catalog_ajax_result);
								$("#form_content > form").replaceWith('<br/>');								
							}
						}						
					}
				} else if (settings.url == '/product_catalog_ajax/set_rollover') {
					
					// var selectTreeTid = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.select_tree_id;
					var parentId = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.parentId;
					var childId = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.childId;
					var title = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.title;
					var contentType = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.contentType;
					var weight = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.weight;
					
					if( $('#'+childId).length >0 ) {
						$(".product_catalog_tree").jstree("set_text", $('#' + childId), title);
						$('#'+childId).trigger('click');
					} else {
						$.fn.addTreeItemCallback(parentId, childId, title,contentType, weight);
						$('#'+childId).trigger('click');	
					}
					
				} else if (settings.url == '/product_catalog_ajax/set_cardtype') {
					var parentId = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.parentId;
					var childId = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.childId;
					var title = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.title;
					var contentType = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.contentType;
					var weight = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.weight;
					
					// In case Edit
					if( $('#'+childId).length >0 ) {
						if( title instanceof Array) {
							title = title[0];
						}
						$(".product_catalog_tree").jstree("set_text", $('#' + childId), title);
						// $('#'+childId).trigger('click');
					// In case Create
					} else {
						$.fn.addTreeItemCallback(parentId, childId, title, contentType, weight);
						$('#'+childId).trigger('click');	
					}
				} else {
				}
			});
			
			//initialize tree
			var treeType = settings.product_catalog_tree_type;
			var types = $.fn.getTreeTypeSetting(treeType);
			
			if(settings.product_catalog_tree_data){
				$(".product_catalog_tree").jstree({
					"core" : {},
					"json_data" : {
						"data" : settings.product_catalog_tree_data,
						"progressive_render" : true,
					},
					"plugins" : [ "types", "themes", "json_data",
							"ui", "contextmenu", "crrm", "dnd" ,"search"],
					"ui" : {
						"select_multiple_modifier" : false,
						"initially_select" : [ settings.product_catalog_tree_data[0].attr.root_nid ],
						"select_limit" : 1
					},
					"crrm" : {
					        "move" : {
					            "check_move" : function (m) {
					            		if(m.o.attr('rel') == 'tree_node_counter_main_basic_prepaid' 
					            			|| m.o.attr('rel') == 'tree_node_counter_main_basic_postpaid'
					            			|| m.o.attr('rel') == 'tree_node_counter_main_basic_prepaid_removable' 
					            			|| m.o.attr('rel') == 'tree_node_counter_main_basic_postpaid_removable'
					            			|| m.o.attr('rel') == 'tree_node_counter_main_optional_prepaid' 
					            			|| m.o.attr('rel') == 'tree_node_counter_main_optional_postpaid' 
					            			|| m.o.attr('rel') == 'tree_node_counter_main_rollover_prepaid' 
					            			|| m.o.attr('rel') == 'tree_node_counter_main_rollover_postpaid' 
					            			|| m.o.attr('rel') == 'actionpriceallowanceonetime'
					            			|| m.o.attr('rel') == 'actionpricechargerecurring'
					            			) {
					            			
						            			if(m.op.attr('rel') == m.np.attr('rel') ) {
						            				return true;
															} else {
						            					return false;
						            			}
						            			
					            		} else {
					            			return false;
					            		}
					            }
					        }
					},
					"types" : types,
					"contextmenu" : {
						"select_node": true,
						"items" : function(obj) {
							var menus = $.fn.getTreeContextMenuSetting(treeType,obj);
							return menus;
						},
					},
				});
			}
		
			//bind load event for loading data from the server.
			$(".product_catalog_tree").bind("loaded.jstree",function(e, data) {
					$.fn.masking('Loading...');
	
					var rootNid = settings.product_catalog_tree_data[0].attr.root_nid;
					var ajaxUrl = '/product_catalog_ajax/nojs/loadTree/' + rootNid;
	
					$.ajax({
						url : ajaxUrl,
						dataType : 'json',
						success : function(data) {
							//console.log('haha');
							$.jstree._focused()._get_settings().json_data.data = data;
							$.jstree._focused().refresh(-1);
 
							$.fn.unmasking();
							
							//console.log(data);
							
							// 임시로 모두 오픈
							$(".product_catalog_tree").jstree('open_all');
							
							var params = {};
							if (location.search) {
							    var parts = location.search.substring(1).split('&');
							
							    for (var i = 0; i < parts.length; i++) {
							        var nv = parts[i].split('=');
							        if (!nv[0]) continue;
							        params[nv[0]] = nv[1] || true;
							    }
							}
							
							// Now you can get the parameters you want like so:
							var abc = params.tree_item_id;
							if(abc) {
								var foundItem = $('#'+abc);
								console.log(foundItem);
								if(foundItem) {
									$(".product_catalog_tree").jstree('close_all');
									$(".product_catalog_tree").jstree("select_node", "#"+abc);
									foundItem.trigger('click');
								}
							}
						},
						error: function(jqXHR, textStatus, errorThrown){
							//console.log('ajax error');
							//console.log(jqXHR, textStatus, errorThrown);
						}
					});
			});
			
			//bind click event for loading form
			$(".product_catalog_tree").bind("click.jstree", function (e, data) {
				var node = $(e.target).closest("li");
	            $("#tree_node_op").val('edit');
	            $.fn.loadForm(node,null);
	        });
			
			//bind move event
			$(".product_catalog_tree").bind(
				"move_node.jstree",
				function(e, data) {
					/*
					 * data.rslt contains: .o - the node being moved
					 * .r - the reference node in the move .ot - the
					 * origin tree instance .rt - the reference tree
					 * instance .p - the position to move to (may be
					 * a string - "last", "first", etc) .cp - the
					 * calculated position to move to (always a
					 * number) .np - the new parent .oc - the
					 * original node (if there was a copy) .cy -
					 * boolen indicating if the move was a copy .cr -
					 * same as np, but if a root node is created
					 * this is -1 .op - the former parent .or - the
					 * node that was previously in the position of
					 * the moved node
					 */
					var children = Array();
	
					var childNid = data.rslt.o[0].attributes[0].value;
					var weightStep = 100;
	
					var nextSiblingWeight = (data.rslt.o[0].nextSibling == null) ? -1 : data.rslt.o[0].nextSibling.attributes[3].value;
					var prevSiblingWeight = (data.rslt.o[0].previousSibling == null) ? -1 : data.rslt.o[0].previousSibling.attributes[3].value;
	
					var parentNid = data.rslt.np[0].attributes[0].value;
					var oldParentNid = data.rslt.op[0].attributes[0].value;
	
					var parent = {
						'changed' : (parentNid == oldParentNid) ? false : true,
						'nid' : parentNid,
					};
	
					children[0] = {
						'nid' : childNid,
					};
	
					if (prevSiblingWeight == -1 && nextSiblingWeight == -1) {
						children[0].weight = 0;
					} else if (prevSiblingWeight == -1) {
						children[0].weight = parseInt(nextSiblingWeight) + weightStep;
					} else if (nextSiblingWeight == -1) {
						children[0].weight = parseInt(prevSiblingWeight) - weightStep;
					} else {
						var pivot = parseInt((parseInt(nextSiblingWeight) + parseInt(prevSiblingWeight)) / 2);
						if (pivot == 0) {// 전체..
							children[0].weight = parseInt(nextSiblingWeight) + weightStep;
							var prevNode = data.rslt.o[0].previousSibling;
							var index = 1;
							while (prevNode != null) {
								children[index] = {
									'nid' : prevNode.attributes[0].value,
									'weight' : children[index - 1].weight + weightStep
								};
								prevNode = prevNode.previousSibling;
								index++;
							}
						} else {
							children[0].weight = pivot;
						}
					}
	
					for ( var i = 0; i < children.length; i++) {
						var node = $("#" + children[i].child_nid);
					}
	
					// send to server
					editLink = '/product_catalog_ajax/nojs/move_node';
	
					$.fn.masking('Progress');
					$.ajax({
						url : editLink,
						type : 'POST',
						dataType : 'json',
						data : {
							"nodes" : children,
							"parent" : parent
						},
						success : function(data) {
							for ( var i = 0; i < children.length; i++) {
								node = $('#' + children[i].nid);
								node.attr('weight',children[i].weight);
							}
							$.fn.unmasking();
						},
						error : function() {
							$.jstree._focused().rollback(data.rlbk);
							$.fn.unmasking();
						}
					});

			});

			/*
			$(".product_catalog_tree").bind("rename.jstree", function(e, data) { // $.jstree.rollback(data.rlbk);
				// console.log('rename');
				console.log(e);
				console.log(data);
			});
			$(".product_catalog_tree").bind("remove.jstree", function(e, data) {
				console.log('remove');
				console.log(e);
				console.log(data);
			});
			$(".product_catalog_tree").bind("create.jstree", function(e, data) { // $('#dialog').text('Do
				// you
				// want
				// to
				// delete');
				// $('#dialog').dialog('open'); console.log('create');
				console.log(e);
				console.log(data);
			});
			$(".product_catalog_tree").bind("move_node.jstree",
				function(e, data) {
					console.log('move_node');
					console.log(e);
					console.log(data);
			});
			*/
			// Drupal.detachBehaviors(productCatalogTreeBehavior);
			
			//operations
			$('#tree_op_expand').bind('click',{},$.fn.treeOpExpand);
			$('#tree_op_close').bind('click',{},$.fn.treeOpClose);
			$('#tree_op_search_button').bind('click',{},$.fn.treeOpSearch);
			$('#tree_op_search_clear').bind('click',{},$.fn.treeOpSearchClear);
			delete Drupal.behaviors.ProductCatalogTreeBehavior;
		}
	};
})(jQuery);
;
