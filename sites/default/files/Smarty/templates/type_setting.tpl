(function($) {
	$.fn.getTreeTypeSetting = function(treeType) {
	var types = {};
	switch (treeType) {
	case 'product_tree':
		types = {
			"types" : {
            	"simpleproductoffering": {
              		"icon" : {
                		"image" : "/sites/default/files/applications.png"
                	},
				},
                "dtn_mobile_counter_main" : {
                    "valid_children" : [],
                    "icon" : {
						"image" : "/sites/default/files/inbox-document.png"
                    }
                },
                "conditioncommonor" : {
                    "icon" : {
						"image" : "/sites/default/files/inbox-document.png"
                    }
                },
                "conditioncommonand" : {
                    "icon" : {
						"image" : "/sites/default/files/inbox-document.png"
                    }
                },
                "treenode_counter_main_basic" : {
					"valid_children" : [ "conditioncommonor" ],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "treenode_counter_main_optional" : {
					"valid_children" : [ "conditioncommonor" ],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "treenode_counter_accumulated_optional" : {
					"valid_children" : [ "conditioncommonor" ],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
				"usage" : {
					"valid_children" : [ "actionpricecharge",
							"actionpricediscount", "actionpriceallowance" ],
					"icon" : {
						"image" : "/sites/default/files/applications.png"
					}
				},
				"actionpricecharge" : {
					"valid_children" : [ "actionpricechargefactors" ],
					"icon" : {
						"image" : "/sites/default/files/inbox-document.png"
					}
				},
				"actionpricediscount" : {
					"valid_children" : [ "actionpricediscountfactors" ],
					"icon" : {
						"image" : "/sites/default/files/inbox-document.png"
					}
				},
				"actionpriceallowance" : {
					"valid_children" : [ "actionpriceallowancefactors" ],
					"icon" : {
						"image" : "/sites/default/files/inbox-document.png"
					}
				},
				"actionpricecharge":{
					"valid_children" : [ "conditioncommonor" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					},
				},
				"actionpricediscount":{
					"valid_children" : [ "conditioncommonor" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					},
				},
				"actionpriceallowance":{
					"valid_children" : [ "conditioncommonor" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					},
				},
				"actionpricechargefactors" : {
					"valid_children" : [ "conditioncommonor" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					},
				},
				"actionpricediscountfactors" : {
					"valid_children" : [ "conditioncommonor" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"actionpriceallowancefactors" : {
					"valid_children" : [ "conditioncommonor" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhatqos" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhaturlgroupfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhatcustomfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhendayfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhendurationfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhenholidayfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhentimeslotfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhenweekfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherecountryfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherenetworkfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherezonefactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherecustomfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhomemberfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhonumberfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhoprefixfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhocustom" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
                "tariffplan" :{
                    "valid_children" : [],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "treenodenumberingplandomestic" :{
                    "valid_children" : [],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "treenodenumberingplanidd" :{
                    "valid_children" : [],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "treenodecounter" :{
                    "valid_children" : ["all"],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "prdattributeprefixrangeallowed" :{
                    "valid_children" : ["all"],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "prdattributeprefixrangenotallowe" : {
                    "valid_children" : [],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                }
			}
		};
		break;
	}
	return types;
};
})(jQuery);
