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
															"tree_node_counter_main_optional_prepaid",
															"tree_node_counter_main_optional_postpaid",
				            					"tree_node_counter_main_rollover_prepaid",
				            					"tree_node_counter_main_rollover_postpaid"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
				},
				"counter_accumulated": {
						"valid_children" : ['tree_node_counter_accumulated_optional_prepaid',
																"tree_node_counter_accumulated_optional_postpaid",
																'tree_node_counter_accumulated_rollover_prepaid',
																'tree_node_counter_accumulated_rollover_prepaid'],
				        	"icon" : {
				        			"image" : "/sites/default/files/icons/inbox-document.png"
				        		},
				},
				"counter_shared": {
						"valid_children" : ["tree_node_counter_main_basic_prepaid", 									
																"tree_node_counter_main_basic_postpaid",
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
		    	"valid_children" : ["conditioncommonand_nonusage_subscription",
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
					"icon" : {
						"image" : "/sites/default/files/folder.png"
					},
				},
				"discount_voucher_product_specific": {
					"valid_children" : ["treenodeproductfordisvoucher"],
					"icon" : {
						"image" : "/sites/default/files/folder.png"
					},
				},
				"voucher_loyalty_point": {
					"valid_children" : ["none"],
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
