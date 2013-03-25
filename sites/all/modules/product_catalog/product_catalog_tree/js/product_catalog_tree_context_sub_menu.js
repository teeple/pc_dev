(function($) {
	$.fn.getSubMenuAddNode = function(label,childContentType){
		var obj = {
			"addNodeObject":{
				"label" : label,
				"action" : function(node){
					$.fn.addNode(node,{'childContentType' : childContentType});
				}	
			}
		};
	  return obj;
	};
	
	$.fn.getSubMenuAddNodeWithoutWrapper = function(label,childContentType){
		var obj = {
				"label" : label,
				"action" : function(node){
					$.fn.addNode(node,{'childContentType' : childContentType});
				}	
		};
	  return obj;
	};
	
	$.fn.getSubMenuLoadSelectForm = function(label){
		var obj = {
			"loadSelectFormObject":{
				"label" : label,
				"action" : function(node){
					$.fn.loadSelectForm(node);
				}	
			}
		};
	  return obj;
	};
	
	$.fn.getConditionWhoType1 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber MDN","conditionwhosubscribermdn");
		obj[1] = $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber Status","conditionwhosubscriberstatus");
		obj[2] = $.fn.getSubMenuAddNodeWithoutWrapper("Called Number","conditionwhoprefixfactors");
		obj[3] = $.fn.getSubMenuAddNodeWithoutWrapper("Carrier (Called)","conditionwhocalledcarrier");
		obj[4] = $.fn.getSubMenuAddNodeWithoutWrapper("Customer Level","conditionwhocustomerlevel");
		return obj;
	};
	
	$.fn.getConditionWhoType2 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("Customer level","conditionwhocustomerlevel");
		obj[1] = $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber MDN","conditionwhosubscribermdn");
		obj[2] = $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber Status","conditionwhosubscriberstatus");
		return obj;
	};

	$.fn.getConditionWhereType1 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone","conditionwherecallerzone");
		obj[1] = $.fn.getSubMenuAddNodeWithoutWrapper("Callee Zone","conditionwherecalleezone");
		obj[2] = $.fn.getSubMenuAddNodeWithoutWrapper("Caller/Callee in SameZone","conditionwhereissamezone");
		obj[3] = $.fn.getSubMenuAddNodeWithoutWrapper("Client IP","conditionwhereclientip");
		obj[4] = $.fn.getSubMenuAddNodeWithoutWrapper("Client MAC Address","conditionwheremacaddress");
		obj[5] = $.fn.getSubMenuAddNodeWithoutWrapper("Client Device Type","conditionwheredevicetype");
		obj[6] = $.fn.getSubMenuAddNodeWithoutWrapper("Service ID","conditionwhereserviceid");
		return obj;
	};
	
	$.fn.getConditionWhereType2 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone","conditionwherecallerzone");
		obj[1] = $.fn.getSubMenuAddNodeWithoutWrapper("Callee Zone","conditionwherecalleezone");
		obj[2] = $.fn.getSubMenuAddNodeWithoutWrapper("Caller/Callee in SameZone","conditionwhereissamezone");
		return obj;
	};
	
	$.fn.getConditionWhereType3 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone","conditionwherecallerzone");
		obj[1] = $.fn.getSubMenuAddNodeWithoutWrapper("Client IP","conditionwhereclientip");
		obj[2] = $.fn.getSubMenuAddNodeWithoutWrapper("Client MAC Address","conditionwheremacaddress");
		obj[3] = $.fn.getSubMenuAddNodeWithoutWrapper("Client Device Type","conditionwheredevicetype");
		obj[4] = $.fn.getSubMenuAddNodeWithoutWrapper("Service ID","conditionwhereserviceid");
		return obj;
	};
	
	$.fn.getConditionWhereType4 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone","conditionwherecallerzone");
		return obj;
	};
	
	$.fn.getConditionWhatType1 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("UsageType","conditionwhatusagetypefactors");
		obj[1] = $.fn.getSubMenuAddNodeWithoutWrapper("NonUsageType","conditionwhatnonusagetypefactors");
		obj[2] = $.fn.getSubMenuAddNodeWithoutWrapper("Card Types","conditionwhatcardtype");
		obj[3] = $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call","conditionwhatincomingcall");
		obj[4] = $.fn.getSubMenuAddNodeWithoutWrapper("Call Type","conditionwhatcalltype");
		obj[5] = $.fn.getSubMenuAddNodeWithoutWrapper("Counter","conditionwhatcounter");
		obj[6] = $.fn.getSubMenuAddNodeWithoutWrapper("Rating Group","conditionwhatratinggroup");
		obj[7] = $.fn.getSubMenuAddNodeWithoutWrapper("Main Product","conditionwhatmainproduct");
		return obj;
	};
	
	$.fn.getConditionWhatType2 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("Card Types","conditionwhatcardtype");
		obj[1] = $.fn.getSubMenuAddNodeWithoutWrapper("Counter","conditionwhatcounter");
		obj[2] = $.fn.getSubMenuAddNodeWithoutWrapper("Main Product","conditionwhatmainproduct");
		return obj;
	};
	
	$.fn.getConditionWhatType3 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("Counter","conditionwhatcounter");
		obj[1] = $.fn.getSubMenuAddNodeWithoutWrapper("Call Type","conditionwhatcalltype");
		obj[2] = $.fn.getSubMenuAddNodeWithoutWrapper("Main Product","conditionwhatmainproduct");
		return obj;
	};
	
	$.fn.getConditionWhatType4 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("UsageType","conditionwhatusagetypefactors");
		obj[1] = $.fn.getSubMenuAddNodeWithoutWrapper("Card Types","conditionwhatcardtype");
		obj[2] = $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call","conditionwhatincomingcall");
		obj[3] = $.fn.getSubMenuAddNodeWithoutWrapper("Call Type","conditionwhatcalltype");
		obj[4] = $.fn.getSubMenuAddNodeWithoutWrapper("Counter","conditionwhatcounter");
		obj[5] = $.fn.getSubMenuAddNodeWithoutWrapper("Main Product","conditionwhatmainproduct");
		return obj;
	};
	
	$.fn.getConditionWhatType5 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call","conditionwhatincomingcall");
		obj[1] = $.fn.getSubMenuAddNodeWithoutWrapper("Call Type","conditionwhatcalltype");
		obj[2] = $.fn.getSubMenuAddNodeWithoutWrapper("Counter","conditionwhatcounter");
		obj[3] = $.fn.getSubMenuAddNodeWithoutWrapper("Main Product","conditionwhatmainproduct");
		return obj;
	};
	
	$.fn.getConditionWhenType1 = function(){
		var obj = new Object;
		obj[0] = $.fn.getSubMenuAddNodeWithoutWrapper("Day","conditionwhendayfactors");
		obj[1] = $.fn.getSubMenuAddNodeWithoutWrapper("Day of Month","conditionwhendayofmonth");
		obj[2] = $.fn.getSubMenuAddNodeWithoutWrapper("Bill Date","conditionwhenbillingdate");
		obj[3] = $.fn.getSubMenuAddNodeWithoutWrapper("Subscription Date","conditionwhensubscriptionday");
		obj[4] = $.fn.getSubMenuAddNodeWithoutWrapper("Activation Date","conditionwhenactivationday");
		obj[5] = $.fn.getSubMenuAddNodeWithoutWrapper("Active Days","conditionwhenactivedays");
		obj[6] = $.fn.getSubMenuAddNodeWithoutWrapper("Customer Birthday","conditionwhencustomerbirthday");
		obj[7] = $.fn.getSubMenuAddNodeWithoutWrapper("Company Anniversary","conditionwhencompanybirthday");
		obj[8] = $.fn.getSubMenuAddNodeWithoutWrapper("Duration","conditionwhendurationfactors");
		obj[9] = $.fn.getSubMenuAddNodeWithoutWrapper("Holiday","conditionwhenholidayfactors");
		obj[10] = $.fn.getSubMenuAddNodeWithoutWrapper("Timeslot","conditionwhentimeslotfactors");
		obj[11] = $.fn.getSubMenuAddNodeWithoutWrapper("Week","conditionwhenweekfactors");
		obj[12] = $.fn.getSubMenuAddNodeWithoutWrapper("First Month","conditionwhenfirstmonth");
		return obj;
	};
})(jQuery);
