<?php
function _json_timetablefactors(){
	$stringMaxLength = 60;
	$jsonData = array();
	
	//timetable	
	$timetableView = views_get_view('list_timetable');
	$timetableView->execute();
	$timetables = $timetableView->result;
	foreach($timetables as $timetableItem){
		$timetale = array(
			'timetable_name' => $timetableItem->node_title
		);
		
		//timetablefactors
		$timetablefactorsView = views_get_view('list_timetablefactors');
		$timetablefactorsView->set_display('panel_pane_1');
		$timetablefactorsView->set_arguments(array(0=>$timetableItem->nid));
		$timetablefactorsView->execute();
		$timetablefactors = $timetablefactorsView->result;
		foreach($timetablefactors as $timetablefactorItem){
			$timetablefactor = array();
			$weekValue = array();
			if($timetablefactorItem->field_field_week_mon[0]['raw']['value']) $weekValue[] = 'MON';
			if($timetablefactorItem->field_field_week_tue[0]['raw']['value']) $weekValue[] = 'TUE';
			if($timetablefactorItem->field_field_week_wed[0]['raw']['value']) $weekValue[] = 'WED';
			if($timetablefactorItem->field_field_week_thu[0]['raw']['value']) $weekValue[] = 'THU';
			if($timetablefactorItem->field_field_week_fri[0]['raw']['value']) $weekValue[] = 'FRI';
			if($timetablefactorItem->field_field_week_sat[0]['raw']['value']) $weekValue[] = 'SAT';
			if($timetablefactorItem->field_field_week_sun[0]['raw']['value']) $weekValue[] = 'SUN';
			$holiday = $timetablefactorItem->field_field_holiday[0]['raw']['value'];
			if($holiday === 'HOLIDAY'){
				$weekValue[] = 'HOLIDAY';
			}
			
			$timetablefactor = array(
				'timetablefactor_name' => $timetablefactorItem->node_field_data_field_ref_timetablefactors_title,			
				'timetablefactors_week'  => $weekValue,	
				'timetablefactors_timeslot'  => $timetablefactorItem->field_field_timeslot_from_hour[0]['raw']['value'].':'.$timetablefactorItem->field_field_timeslot_from_minutes[0]['raw']['value']
												.'~'.$timetablefactorItem->field_field_timeslot_to_hour[0]['raw']['value'].':'.$timetablefactorItem->field_field_timeslot_to_minutes[0]['raw']['value']
			);
			
			$timetale['timetablefactors'][] = $timetablefactor;
		}		
		
		$jsonData['Timetable'][] = $timetale;
	}
	
	
	return json_encode($jsonData);
}