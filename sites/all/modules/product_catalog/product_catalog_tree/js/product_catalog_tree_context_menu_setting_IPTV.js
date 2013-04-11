(function($) {
	$.fn.getTreeContextMenuSetting = function(treeType, obj) {
		var menus = {
			"rename" : false,
			"remove" : false,
			"create" : false,
			"ccp" : false,
			"custom_create" : {
				"label" : "Add",
				"action" : null,
				"submenu" : null,
				"_disabled" : true,
			},
			"custom_copy" : {
				"label" : "Copy",
				"action" : null,
				"submenu" : null,
				"_disabled" : true,
			},
			"custom_paste" : {
				"label" : "Paste",
				"action" : null,
				"submenu" : null,
				"_disabled" : true,
			},
			"custom_delete" : {
				"label" : "Delete",
				"action" : null,
				"submenu" : null,
				"_disabled" : true,
			},
		};

		switch (treeType) {
			case "product_tree":
				var relType = obj.attr("rel");
				console.log('relType');
				console.log(relType);
				switch (relType) {
					case "conditioncommonand":
						var who = $.fn.getConditionWhoType3();
						var where = $.fn.getConditionWhereType5();
						var what = $.fn.getConditionWhatType15();
						var when = $.fn.getConditionWhenType2();
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"who" : {
								"label" : "Who",
								"submenu" : who
							},
							"where" : {
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
					case "conditioncommonand_nonusage_subscription":
					case "conditioncommonand_nonusage_activation":
					case "conditioncommonand_nonusage_recharge":
						var who = $.fn.getConditionWhoType3();
						var what = $.fn.getConditionWhatType2();
						var when = $.fn.getConditionWhenType2();
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"who" : {
								"label" : "Who",
								"submenu" : who
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
					case "conditioncommonand_nonusage_unsubscription":
					case "conditioncommonand_nonusage_recurring":
						var who = $.fn.getConditionWhoType2();
						var what = $.fn.getConditionWhatType7();
						var when = $.fn.getConditionWhenType2();
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"who_" : {
								"label" : "Who",
								"submenu" : who
							},
							"what" : {
								"label" : "What",
								"submenu" : what
							},
							"when" : {
								"label" : "When",
								"submenu" : when
							}

						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "conditioncommonand_nonusage_usageend":
						var who = $.fn.getConditionWhoType3();
						var what = $.fn.getConditionWhatType16();
						var when = $.fn.getConditionWhenType2();
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"who_" : {
								"label" : "Who",
								"submenu" : who
							},
							"what" : {
								"label" : "What",
								"submenu" : what
							},
							"when" : {
								"label" : "When",
								"submenu" : when
							}
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					default:
						menus = $.fn.getFixedMenu(menus, relType);
						break;
				}
				break;
			default:
				menus.custom_create = null;
				menus.custom_copy = null;
				menus.custom_paste = null;
				menus.custom_delete = null;
		};// switch
		return menus;
	};
})(jQuery);
