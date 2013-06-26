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
			case "numberspecial_tree":
				var relType = obj.attr("rel");
				switch (relType) {
					//case "number_special":
					case 'numberspecialrate':
					case "conditioncommonratinggroup":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "Rates":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Rate","numberspecialrate");
						break;
					case "actionpricechargefactors":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Rating Group","conditioncommonratinggroup");
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
				}
				break;
			case "unittransfer_tree":
				var relType = obj.attr("rel");
				switch (relType) {
					case "unittransfer":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Counter Group");
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
					break;
					case "unittransferfactor":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
					break;
				}
				break;
			case "vouchercardtype_tree":
				var relType = obj.attr("rel");
				switch (relType) {
					case "vouchercardtype":
					case "treenodeproductfordisvoucher":
					case "treenodeproductforvoucher":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
					case "voucher_domain_specific":
					case "voucher_domain_specific_mobile":
					case "voucher_domain_specific_iptv":
					case "voucher_domain_specific_broadband":
					case "voucher_domain_specific_voip":
					case "voucher_domain_specific_satellite":
					case "voucher_domain_specific_dummy":
						break;
					case "voucher_product_specific":
					case "discount_voucher_product_specific":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Product");
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
