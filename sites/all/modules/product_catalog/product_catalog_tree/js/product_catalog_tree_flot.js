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
