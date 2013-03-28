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
		var obj = {
			"Subscriber MDN" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber MDN","conditionwhosubscribermdn"),
			"Subscriber Status" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber Status","conditionwhosubscriberstatus"),
			"Called Number" : $.fn.getSubMenuAddNodeWithoutWrapper("Called Number","conditionwhoprefixfactors"),
			"Carrier (Called)" : $.fn.getSubMenuAddNodeWithoutWrapper("Carrier (Called)","conditionwhocalledcarrier"),
			"Customer Level" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Level","conditionwhocustomerlevel"),
			"Roaming Carrier": $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Carrier","conditionwhoroamingcarrier"),
		};
		return obj;
	};
	
	$.fn.getConditionWhoType2 = function(){
		var obj = {
			"Customer Level" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Level","conditionwhocustomerlevel"),
			"Subscriber MDN" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber MDN","conditionwhosubscribermdn"),
			"Subscriber Status" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber Status","conditionwhosubscriberstatus")
		};
		return obj;
	};

	$.fn.getConditionWhereType1 = function(){
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone","conditionwherecallerzone"),
			"Callee Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee Zone","conditionwherecalleezone"),
			"Caller/Callee in SameZone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller/Callee in SameZone","conditionwhereissamezone"),
			"Client IP" : $.fn.getSubMenuAddNodeWithoutWrapper("Client IP","conditionwhereclientip"),
			"Client MAC Address" : $.fn.getSubMenuAddNodeWithoutWrapper("Client MAC Address","conditionwheremacaddress"),
			"Client Device Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Client Device Type","conditionwheredevicetype"),
			"Service ID" : $.fn.getSubMenuAddNodeWithoutWrapper("Service ID","conditionwhereserviceid"),
			"Roaming Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Zone","conditionwhenroamingzone"),
			"Roaming Country" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Country","conditionwhenroamingcountry"),
		};
		return obj;
	};
	
	$.fn.getConditionWhereType2 = function(){
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone","conditionwherecallerzone"),
			"Callee Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee Zone","conditionwherecalleezone"),
			"Caller/Callee in SameZone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller/Callee in SameZone","conditionwhereissamezone"),
			"Roaming Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Zone","conditionwhenroamingzone"),
			"Roaming Country" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Country","conditionwhenroamingcountry"),
		}
		return obj;
	};
	
	$.fn.getConditionWhereType3 = function(){
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone","conditionwherecallerzone"),
			"Client IP" : $.fn.getSubMenuAddNodeWithoutWrapper("Client IP","conditionwhereclientip"),
			"Client MAC Address" : $.fn.getSubMenuAddNodeWithoutWrapper("Client MAC Address","conditionwheremacaddress"),
			"Client Device Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Client Device Type","conditionwheredevicetype"),
			"Service ID" : $.fn.getSubMenuAddNodeWithoutWrapper("Service ID","conditionwhereserviceid")
		};
		return obj;
	};
	
	$.fn.getConditionWhereType4 = function(){
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone","conditionwherecallerzone")
		};
		return obj;
	};
	
	$.fn.getConditionWhatType1 = function(){
		var obj = {
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType","conditionwhatusagetypefactors"),
			"NonUsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("NonUsageType","conditionwhatnonusagetypefactors"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType","conditionwhatroamingtype"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types","conditionwhatcardtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call","conditionwhatincomingcall"),
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type","conditionwhatcalltype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter","conditionwhatcounter"),
			"Rating Group" : $.fn.getSubMenuAddNodeWithoutWrapper("Rating Group","conditionwhatratinggroup"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product","conditionwhatmainproduct")
		};
		return obj;
	};
	
	$.fn.getConditionWhatType2 = function(){
		var obj = {
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types","conditionwhatcardtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter","conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product","conditionwhatmainproduct")
		};
		return obj;
	};
	
	$.fn.getConditionWhatType3 = function(){
		var obj = {
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter","conditionwhatcounter"),
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type","conditionwhatcalltype"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product","conditionwhatmainproduct")
		};
		return obj;
	};
	
	$.fn.getConditionWhatType4 = function(){
		var obj = {
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType","conditionwhatusagetypefactors"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types","conditionwhatcardtype"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType","conditionwhatroamingtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call","conditionwhatincomingcall"),
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type","conditionwhatcalltype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter","conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product","conditionwhatmainproduct")
		};
		return obj;
	};
	
	$.fn.getConditionWhatType5 = function(){
		var obj = {
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call","conditionwhatincomingcall"),
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type","conditionwhatcalltype"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType","conditionwhatroamingtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter","conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product","conditionwhatmainproduct")
		};
		return obj;
	};
	
	$.fn.getConditionWhenType1 = function(){
		var obj = {
			"Day" : $.fn.getSubMenuAddNodeWithoutWrapper("Day","conditionwhendayfactors"),
			"Day of Month" : $.fn.getSubMenuAddNodeWithoutWrapper("Day of Month","conditionwhendayofmonth"),
			"Bill Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Bill Date","conditionwhenbillingdate"),
			"Subscription Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscription Date","conditionwhensubscriptionday"),
			"Activation Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Activation Date","conditionwhenactivationday"),
			"Active Days" : $.fn.getSubMenuAddNodeWithoutWrapper("Active Days","conditionwhenactivedays"),
			"Customer Birthday" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Birthday","conditionwhencustomerbirthday"),
			"Company Anniversary" : $.fn.getSubMenuAddNodeWithoutWrapper("Company Anniversary","conditionwhencompanybirthday"),
			"Duration" : $.fn.getSubMenuAddNodeWithoutWrapper("Duration","conditionwhendurationfactors"),
			"Holiday" : $.fn.getSubMenuAddNodeWithoutWrapper("Holiday","conditionwhenholidayfactors"),
			"Timeslot" : $.fn.getSubMenuAddNodeWithoutWrapper("Timeslot","conditionwhentimeslotfactors"),
			"Week" : $.fn.getSubMenuAddNodeWithoutWrapper("Week","conditionwhenweekfactors"),
			"First Month" : $.fn.getSubMenuAddNodeWithoutWrapper("First Month","conditionwhenfirstmonth")
		};
		return obj;
	};
})(jQuery);
