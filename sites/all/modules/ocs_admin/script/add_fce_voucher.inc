<?php


$h = array_flip( explode( ',', 'Cardtype,type,Selling Price,Remains,Data,Active Days,Grace Days,Categories,Explanation,FREE_TIME,FREE_SMS,FREE_MMS,FREE_CRBT,FREE_GPRS,SEND_YN,SERVICE_TYPE,USE_AREA,FREE_VCALL_TIME,PACKET_PACKAGE,Promotion'));

$data = array(
	'1|Recharge|2000|2000||20|14|NPSYGUHQMR|Normal 2000|||||||||||Loyalty Point Bonus',
	'2|Recharge|5000|1000||7|14|BCE|Dopin 5000 New Card|||||||||||',
	'3|Recharge|500|500||0|0|AZBXCDEFYGUHPNSQMWR|Normal old 500|||||||||||1 minute (until 00:00 of the recharge day)',
	'4|Recharge|3000|3000||30|14|NPSYGUHQMR|Normal 3000|||||||||||"If Admin recharges, 3 FreeSmsFF to FF members (Valid for 3 days); Loyalty Point Bonus"',
	'5|Recharge|5000|5000||50|14|NPSYGUHQMR|Normal 5000|||||||||||"If Admin recharges, 5 FreeSmsFF to FF members (Valid for 3 days); Loyalty Point Bonus"',
	'6|Recharge|1000|1000||0|0|AZBXCDEFYGUHPNSQMWR|Normal old 1000|||||||||||3 minute (until 00:00 of the recharge day)',
	'7|Recharge|10000|10000||100|14|NPSYGUHQMR|Normal 10000|||||||||||" If Admin recharges, 10 FreeSmsFF to FF members (Valid for 3 days); Loyalty Point Bonus"',
	'8|Recharge|2000|2000||0|0|AZBXCDFEW|Normal Dopin 2000|||||||||||Loyalty Point Bonus',
	'9|Recharge|15000|5000||30|14|BCEF|Normal Dopin 15000|||||||||||" If Admin recharges, 15 FreeSmsFF to FF members (Valid for 3 days); Loyalty Point Bonus"',
	'10|Recharge|6000|6000||0|0|AZBXCDFEW|Normal Dopin 6000|||||||||||"600 Remains;  If Admin recharges, 6 FreeSmsFF to FF members (Valid for 3 days); Loyalty Point Bonus"',
	'11|Recharge|1000|1000||0|0|IJK|Univision 1000|||||||||||',
	'12|Recharge|6000|6000||30|14|YGUHNSMR|Special Rural 6000 2011Promo|||||||||||',
	'13|Recharge|5000|5000||0|0|C|Cdopin 5000|||||||||||',
	'14|Recharge|2000|2000||0|0|IJK|Univision 2000|||||||||||',
	'15|Recharge|3000|3000||0|0|IJK|Univision 3000|||||||||||',
	'17|Recharge|10000|3000||14|14|BCE|Dopin 10000 New Card|||||||||||',
	'18|Recharge|500|500||0|0|AZBXCDEFYGUHPNSQMWR|Normal 500|||||||||||1 minute (until 00:00 of the recharge day)',
	'19|Recharge|1000|1000||0|0|AZBXCDEFYGUHPNSQMWR|Normal 1000|||||||||||3 minute (until 00:00 of the recharge day)',
	'20|Recharge|120000|10000||365|14|BCEF|Normal Dopin 120000|||||||||||Loyalty Point Bonus',
	'23|Recharge||2000||30|14|IJK|Univision 2000 хоногтой|||||||||||',
	'25|Recharge||10000||30|14|IJK|Univision 10000 хоногтой|||||||||||',
	'28|Recharge||20000||90|14|IJK|Univision 20000 хоногтой|||||||||||',
	'35|Recharge|10000|5000||0|0|AZBXCDEFYGUHPNSQMWR|201212 New Year 31 Бэлэгтэй Карт|||||||||||',
	'36|Recharge||0|50MB|30|365|P|201211 Songuuliin Khoroo Modem Card|||||||||||',
	'38|Recharge|5000|3000||50|14|NYGSUHMR|"Special 5000 (50, 3000)"|||||||||||',
	'39|Recharge|500|500||0|0|ABCEFGMNSWXYZQR|2013 Цагаан Сар 500|||||||||||',
	'40|Recharge|1000|1000||0|0|ABCEFGMNSWXYZQR|2013 Цагаан Сар 1000|||||||||||',
	'41|Recharge|2000|2000||0|0|ABCEFGMNSWXYZQR|2013 Цагаан Сар 2000|||||||||||',
	'43|Recharge|500|500||0|0|BCNSYGUHZAXQEFMWR|2012 Цагаан Сар 500 NOW Normal 500|||||||||||1 minute (until 00:00 of the recharge day)',
	'44|Recharge|1000|1000||0|0|BCNSYGUHZAXQEFMWR|2012 Цагаан Сар 1000 NOW Normal 1000|||||||||||3 minute (until 00:00 of the recharge day)',
	'45|Recharge||70000||180|14|IJK|Univision 70000|||||||||||',
	'46|Recharge|15000|5000||30|14|CF|Cdopin 15000 201205|||||||||||" If Admin recharges, 15 FreeSmsFF to FF members (Valid for 3 days); Loyalty Point Bonus"',
	'47|Recharge|120000|10000||365|14|CF|Cdopin Dopin 120000 201205|||||||||||Loyalty Point Bonus',
	'70|Recharge||150000||365|14|IJK|Univision 150000|||||||||||',
	'75|Recharge||5000||60|14|IJK|Univision New 10000 хоногтой|||||||||||',
	'76|Recharge||5000||0|14|IJK|Univision New 5000|||||||||||',
	'81|Entry|1000000|50000||30|14|B|DOPIN BRILL 8XAAAAAA|0|0|0|0|0|0|12|U|0|0|',
	'82|Entry|100000|10000||30|14|B|"DOPIN Gold for MCS20-100000,10000,30 20130522-0630"|0|0|0|0|0|1|12|U|0|0|',
	'83|Entry|10000|6000||120|14|N|Happy normal 10000|0|0|0|0|0|1|1|U|0|0|',
	'85|Entry|100000|20000||120|14|N|"HAPPY SILV 8Xab8Xab,8Xaa8Xaa,8Xaaaa8X,aabb,abab"|0|0|0|0|0|0|1|U|0|0|',
	'87|Entry|500000|20000||30|14|B|"Dopin GOLD 8XXA-AAAA, 8XXX-AAAA"|0|0|0|3|0|0|12|U|0|0|',
	'88|Entry|100000|20000||30|14|B|"Dopin SILV 8Xab8Xab,8Xaa8Xaa,8Xaaaa8X,aabb,abab"|0|0|0|0|0|0|12|U|0|0|',
	'89|Entry|500000|20000||120|14|N|"HAPPY GOLD 8XXA-AAAA, 8XXX-AAAA"|0|0|0|0|0|0|1|U|0|0|',
	'93|Entry|10000|6000||120|14|M|"Happy-90days Normal 10000,6000,120"|0|0|0|0|0|1|27|U|0|0|',
	'94|Entry|3500|2000||90|14|N|"HappyLife MCS-3Khos 3500,2000, 20130522-0630"|0|0|0|0|0|1|1|U|0|0|',
	'95|Entry|20000|0||30|14|P|PPS Live 3GB 20000 2011.08.22~|0|0|0|0|0|1|16|U|0|3145728|',
	'98|Entry|50000|10000||30|14|Z|CorpPPS 51-ees deesh AABB ABAB 20120523151932|0|0|0|0|0|0|40|U|0|0|',
	'99|Entry|13000|8000||30|14|Z|"CorpPPS 5-20, 13000"|0|0|0|0|0|1|40|U|0|0|',
	'101|Entry|0|0||90|14|P|PPS Live 150000 365 DAY|0|0|0|0|0|1|16|U|0|1048576|',
	'105|Entry|1000000|50000||120|14|N|HAPPY BRILL 8XAAAAAA|0|0|0|0|0|0|1|U|0|0|',
	'106|Entry|3000|500||60|14|M|Happy-90days MobileDealer 3000.500.60|0|0|0|0|0|1|27|U|0|0|',
	'107|Entry|3000|2000||90|14|N|"HappyLife MCS-3Khos 3000,2000, 20130522-0630"|0|0|0|0|0|1|1|U|0|0|',
	'108|Entry|10000|5000||30|14|B|"Dopin MCS-3Khos 10000,5000,30 20130522-0630"|0|0|0|0|0|1|12|U|0|0|',
	'109|Entry|0|0||90|14|N|Happy Life New.Gereet 20110926~|0|0|0|0|0|1|1|U|0|0|',
	'113|Entry|14900|10000||30|14|N|HappyLife-Normal_Roaming|0|0|0|0|0|1|1|U|0|0|',
	'114|Entry|2000|1000||30|14|N|Standart for Neg angiinhan 20121220-20130630|0|0|0|0|0|1|1|U|0|0|',
	'115|Entry|12500|5000||30|14|B|"Dopin MCS-2Khos 12500,5000,30 20130522-0630"|0|0|0|0|0|0|12|U|0|0|',
	'116|Entry|30000|5000||30|14|B|"DOPIN SILV for MCS20-30000,5000,30 20130522-0630"|0|0|0|0|0|1|12|U|0|0|',
	'118|Entry|2500|1000||100|14|N|ShineSumd HappyLife-2 2500 2011.10.03-12.31|0|0|0|0|0|1|1|U|0|0|',
	'119|Entry|15000|5000||30|14|C|CDOPIN Engiin |0|0|0|0|0|1|61|U|0|0|',
	'120|Entry|3000|500||60|14|N|HappyLife for MobileDealer 2011.12.08|0|0|0|0|0|1|1|U|0|0|',
	'125|Entry|5000|2000||90|14|M|Happy-90days Normal for new subs 0301-0430|0|0|0|0|0|1|27|U|0|0|',
	'126|Entry|20000|5000||30|14|E|"Dopin-90days Normal 20000,5000,30"|0|0|0|0|0|1|34|U|0|0|',
	'127|Entry|15000|5000||30|14|E|Dopin-90days Normal for new subs 0301-0430|0|0|0|0|0|1|34|U|0|0|',
	'129|Entry|5000|1000||7|14|B|"Dopin New Subs Normal 5000, 1000,7 - 0415-0630"|0|0|0|0|0|1|12|U|0|0|',
	'132|Entry|88000|10000||365|14|B|"Dopin New Subs Normal 88000, 10000,365 - 0415-0630"|0|0|0|0|0|1|12|U|0|0|',
	'133|Entry|1088000|50000||365|14|B|"Dopin New Subs Brill 1088000, 50000,365-0415-0630"|0|0|0|0|0|1|12|U|0|0|',
	'134|Entry|588000|20000||365|14|B|"Dopin New Subs Gold 588000, 20000,365-0415-0630"|0|0|0|0|0|1|12|U|0|0|',
	'135|Entry|4000|2000||90|14|N|"HappyLife MCS-2Khos 8000,2000,90 20130522-0630"|0|0|0|0|0|1|1|U|0|0|',
	'136|Entry|188000|20000||365|14|B|"Dopin New Subs SILV 188000, 20000,365-0415-0630"|0|0|0|0|0|1|12|U|0|0|',
	'137|Entry|88000|10000||365|14|E|"Dopin-90days New Subs 88000, 10000,365-0415-0630"|0|0|0|0|0|1|34|U|0|0|',
	'138|Entry|108000|5000||365|14|B|"Dopin + Stone handset 108000, 2012.08.20-12.31"|0|0|0|0|0|0|12|U|0|0|',
	'139|Entry|5000|1000||7|14|E|"Dopin-90days New Subs 5000, 1000,7-0415-0630"|0|0|0|0|0|1|34|U|0|0|',
	'142|Entry|0|0||1|0|N|Standart Lucky - SCPgrace for CRM-0415-0702|0|0|0|0|0|0|1|U|0|0|',
	'143|Entry|18000|5000||30|14|B|"Dopin for Eunitel 18000,5000,30"|0|0|0|0|0|1|12|U|0|0|',
	'144|Entry|9000|6000||120|14|N|Standart for Eunitel 9000.6000.120|0|0|0|0|0|1|1|U|0|0|',
	'151|Entry|100000|20000||30|14|C|"CDOPIN 88AAAA88,8XA(A)B8XA(A)B, AABB,ABAB,Silver"|0|0|0|0|0|0|61|U|0|0|',
	'152|Entry|500000|20000||30|14|C|"CDOPIN 8XxAAAAA , 8XAAAAAx, 8XxxAAAA Gold"|0|0|0|0|0|1|61|U|0|0|',
	'153|Entry|1000000|50000||30|14|C|"CDOPIN 88,89AAAAAA  Brilliant"|0|0|0|0|0|1|61|U|0|0|',
	'156|Entry|20000|5000||30|14|B|"Dopin 20000,5000,30"|0|0|0|0|0|1|12|U|0|0|',
	'158|Entry|10000|500||60|14|N|"Happy life for greet 10000,500,30 20121115-1215"|0|0|0|0|0|1|1|U|0|0|',
	'159|Entry|2000|2000||90|14|N|Happy Chain beleg 2000.2000.90 - 130422-512|0|0|0|0|0|1|1|U|0|0|',
	'160|Entry|1000|1000||30|14|N|"Standart for Dopin 1 year 1000, 1000, 30 ~20121231"|0|0|0|0|0|1|1|U|0|0|',
	'165|Entry|0|0||1|0|B|Dopin Lucky - SCPgrace for CRM-0415-0702|0|0|0|0|0|1|12|U|0|0|',
	'168|Entry|5000|2000||90|14|N|"Standart Normal MCS20 5000,2000,90 0422-0531"|0|0|0|0|0|0|1|U|0|0|',
	'169|Recharge|3000|3000||30|14|NPSYGUHMQR|Rural 3000 + 1500|||||||||||"1500 FreeRemains; If Admin recharges, 3 FreeSmsFF to FF members (Valid for 3 days); Loyalty Point Bonus"',
	'170|Recharge|5000|5000||50|14|NPSYGUHMQR|Rural 5000 + 2500|||||||||||"2500 FreeRemains; If Admin recharges, 5 FreeSmsFF to FF members (Valid for 3 days); Loyalty Point Bonus"',
	'171|Recharge|120000|10000||365|14|AZBXCDFEW|Rural Dopin 120000 + GG/2|||||||||||Loyalty Point Bonus will be added 2 times lower than usual 120000 card (20)',
	'172|Recharge|10000|10000||100|14|NPSYGUHMQR|Rural 10000 + 5000|||||||||||"5000 FreeRemains;  If Admin recharges, 10 FreeSmsFF to FF members (Valid for 3 days); Loyalty Point Bonus"',
	'173|Entry|15000|5000||30|14|B|Dopin Normal  NewSubs & MCS20 20130630hurtel|0|0|0|0|0|0|12|U|0|0|',
	'174|Entry|1060000|50000||365|14|B|Dopin MCS20 BRILL 1060000.50000.365- 130422-0531|0|0|0|0|0|1|12|U|0|0|',
	'175|Entry|560000|20000||365|14|B|Dopin MCS20 Gold 560000.20000.365- 130422-0531|0|0|0|0|0|1|12|U|0|0|',
	'176|Entry|160000|20000||365|14|B|Dopin MCS20 Silv 160000.20000.365- 130422-0531|0|0|0|0|0|1|12|U|0|0|',
	'177|Entry|5000|1000||7|14|C|CDopin New Subs Normal 5000.1000.7 - 0419-0630|0|0|0|0|0|1|61|U|0|0|',
	'178|Entry|88000|10000||365|14|C|"CDopin New Subs Normal 88000, 10000,365 -0419-0630"|0|0|0|0|0|1|61|U|0|0|',
	'180|Entry|10000|5000||30|14|Q|"PackageSim 10000,5000,30"|0|0|0|0|0|1|33|U|0|0|',
	'186|Entry|60000|2000||180|14|C|"CDOPIN Normal-Nomads 60000,2000,180 0501~"|0|0|0|0|0|1|61|U|0|0|',
	'188|Entry|160000|20000||180|14|C|"CDOPIN SILV-Nomads 160000,20000,180 0501~"|0|0|0|0|0|1|61|U|0|0|',
	'189|Entry|1060000|50000||180|14|C|"CDOPIN BRILL-Nomads 1060000,50000,180 0501~"|0|0|0|0|0|1|61|U|0|0|',
	'191|Entry|560000|20000||180|14|C|"CDOPIN GOLD-Nomads 560000,20000,180 0501~"|0|0|0|0|0|1|61|U|0|0|',
	'197|Entry|60000|10000||365|14|B|Dopin MCS20 normal 60000.10000.365- 130422-0531|0|0|0|0|0|1|12|U|0|0|',
	'198|Entry|20000|5000||30|14|C|"CDOPIN 20000,5000,30 "|0|0|0|0|0|0|61|U|0|0|',
	'202|Entry|60000|5000||365|14|B|"Dopin 60000,5000,365 20120820~20121231"|0|0|0|0|0|0|12|U|0|0|',
	'203|Entry|88000|5000||365|14|B|"Dopin 88000,5000,365 20120820~20121231"|0|0|0|0|0|0|12|U|0|0|',
	'210|Entry|15000|5000||30|14|B|"Dopin Chain 15000,5000,30 130422-0512"|0|0|0|0|0|1|12|U|0|0|',
	'211|Entry|10000|8000||30|14|Z|"CorpPPS  20-50,10000"|0|0|0|0|0|1|40|U|0|0|',
	'212|Entry|10000|10000|30|14|Z|CorpPPS 51-s deesh 10000|0|0|0|0|0|1|40|U|0|0|',
	'213|Entry|1000000|50000||120|14|Z|"CorpPPS 88,89AAAAAA  Brilliant "|0|0|0|0|0|1|40|U|0|0|',
	'214|Entry|500000|20000||120|14|Z|"CorpPPS 8xxAAAAA , 8xAAAAAx, 8xxxAAAA Gold"|0|0|0|0|0|1|40|U|0|0|',
	'215|Entry|100000|20000||120|14|Z|"CorpPPS 88AAAA88,8XA(A)B8XA(A)B, AABB,ABAB,Silver"|0|0|0|0|0|0|40|U|0|0|',
	'216|Entry|100000|20000||120|14|Z|"CorpPPS 8XABBA8X,8XXXABBA,AAAB,BAAA "|0|0|0|0|0|1|40|U|0|0|',
	'217|Entry|50000|20000||30|14|N|"HAPPY 88XXAABA, 89XXAABA, 88XXABAA, 89XXABAA"|0|0|0|0|0|1|1|U|0|0|',
	'219|Entry|0|0||180|14|P|30GB for iPad3|0|0|0|0|0|1|16|U|0|31457280|',
	'220|Entry|188000|20000||365|14|C|"CDopin New Subs Gold 188000, 20000,365-0419-0630"|0|0|0|0|0|1|61|U|0|0|',
	'221|Entry|588000|20000||365|14|C|"CDopin New Subs Gold 588000, 20000,365-0419-0630"|0|0|0|0|0|1|61|U|0|0|',
	'222|Entry|1088000|50000||365|14|C|"CDopin New Subs Brill 1088000, 50000,365-0419-0630"|0|0|0|0|0|1|61|U|0|0|',
	'224|Entry|10000|5000||120|14|N|MSC Electronix Promo|0|0|0|0|0|1|1|U|0|0|',
	'228|Entry|10000|5000||120|14|R|Second NORMAL 10 000|0|0|0|0|0|1|28|U|0|0|',
	'229|Entry|100000|20000||120|14|R|Second SILVER 100 000|0|0|0|0|0|1|28|U|0|0|',
	'230|Entry|500000|20000||120|14|R|Second GOLD 500 000|0|0|0|0|0|1|28|U|0|0|',
	'231|Entry|1000000|50000||120|14|R|Second BRILLIANT 1 000 000|0|0|0|0|0|1|28|U|0|0|',
	'232|Entry|6500|0||60|365|P|PPSLive-CEX-6500MNT-Free-200MB-A60-G365|0|0|0|0|0|1|16|U|0|204800|',
	'233|Entry|5000|2000||90|14|N|PresidentElection-5000MNT-2000MNT-90D|0|0|0|0|0|1|1|U|0|0|',
	'234|Entry|5000|2000||90|14|N|Pattern Standart Single 0601-0631|0|0|0|0|0|1|1|U|0|0|',
	'235|Entry|15000|5000||30|14|B|Pattern Dopin Single 0601-0631|0|0|0|0|0|1|12|U|0|0|',
	'236|Entry|4000|2000||90|14|N|Pattern Standart Double 0601-0631|0|0|0|0|0|1|1|U|0|0|',
	'237|Entry|12500|2000||30|14|B|Pattern Dopin Double 0601-0631|0|0|0|0|0|1|12|U|0|0|',
	'238|Entry|3000|2000||90|14|N|Pattern Standart Triple A 0601-0631|0|0|0|0|0|1|1|U|0|0|',
	'239|Entry|4000|2000||90|14|N|Pattern Standart Triple B 0601-0631|0|0|0|0|0|1|1|U|0|0|',
	'240|Entry|10000|2000||30|14|B|Pattern Dopin Triple 0601-0631|0|0|0|0|0|1|12|U|0|0|',
	);

$category_data = array(
	'X,CPPS Fam90,cpps_fam90,Group,Prepaid,c1',
	'W,CPPS 86,cpps_86,Group,Prepaid,c2',
	'O,Okta Experience Zone O,okta_experience_zone_o,Personal,Prepaid,o1',
	'I,Univision I,univision_i,Personal,Prepaid,u1',
	'G,ID Offnet 40SMS,id_offnet_40sms,Personal,Prepaid,i1',
	'F,DOPIN 86C,dopin_86c,Personal,Prepaid,d1',
	'D,DOPIN Old,dopin_old,Personal,Prepaid,d2',
	'A,CPPS Onnet Free,cpps_onnet_free,Group,Prepaid,c3',
	'C,CDOPIN,cdopin,Group,Prepaid,c4',
	'Z,CPPS,cpps,Group,Prepaid,c5',
	'K,VoIP 77 -2,voip_77_2,Personal,Prepaid,v1',
	'J,VoIP 77-1,voip_77_1,Personal,Prepaid,v2',
	'R,Second Tariff,second_tariff,Personal,Prepaid,s1',
	'P,PPS Live Modem,pps_live_modem,Personal,Prepaid,p1',
	'Q,Easy Tour,easy_tour,Personal,Prepaid,e1',
	'S,New Life,new_life,Personal,Prepaid,n1',
	'Y,ID,id,Personal,Prepaid,i2',
	'E,DOPIN Valid 90 Days,dopin_90_days,Personal,Prepaid,d3',
	'B,DOPIN,dopin,Personal,Prepaid,d4',
	'M,Happy Life Valid 90 Days,happy_life_90_days,Personal,Prepaid,h1',
	'N,Happy Life,happy_life,Personal,Prepaid,h2',
	);
	
$voucher_id = drush_shift();
	
$term = array();
$term['vouchertype'] = ocs_get_terms_tid( 'vouchertype');
$term['countersubunit'] = ocs_get_terms_tid( 'countersubunit');
print_r( $term);
foreach( ocs_get_terms( 'tpl_vouchercardtype') as $t) {
	$term['tpl_vouchercardtype'][$t->field_rel_type['und'][0]['value']] = $t->tid;
}

$prd_category = array();
foreach( $category_data as $item) {
	$d = explode( ',', $item);
	$prd_category[$d[0]] = $d[1];
}

foreach( $data as $item) {
	$d = explode( '|', $item);

	if ( ! empty( $voucher_id) && $d[$h['Cardtype']] != $voucher_id) {
		continue;
	}


	$name = 'fce_voucher_' . $d[$h['Cardtype']];
	$nids = ocs_get_nodes_by_title( 'vouchercardtype', $name);
	if ( empty( $nids)) {
		$voucher = ocs_admin_get_new_node('vouchercardtype');
		printf("New voucher name=%s\n", $name);
		$voucher->title = $name;
		$new_voucher = TRUE;
	}
	else {
		$voucher = node_load( $nids[0]);
		printf("Existing voucher name=%s\n", $name);
	}

	/*
	{
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'treenodeproductforvoucher')
			->fieldCondition( 'field_ref_vouchercardtype', 'nid', $voucher->nid)
			->execute();

		if ( ! empty( $result)) {
			foreach( array_keys( $result['node']) as $nid) {
				printf("  nid=%d\n", $nid);
			}
		}
		return;
	}
	*/


	/*
	$price = empty( $d[$h['Selling Price']]) ? '0' : $d[$h['Selling Price']];
	$voucher->field_price_amount_float['und'][0]['value'] = $price;
	$voucher->field_active_period['und'][0]['value'] = $d[$h['Active Days']];
	$voucher->field_grace_period['und'][0]['value'] = $d[$h['Grace Days']];
	$voucher->field_ref_voucher_type['und'][0]['tid'] = $term['vouchertype'][$d[$h['type']]];
	$voucher->field_voucher_id['und'][0]['value'] = $d[$h['Cardtype']];
	$voucher->field_description_long['und'][0]['value'] = t( 'FCE voucher (@id) !desc !promo', 
			array( '@id' => $d[$h['Cardtype']], 
				'!desc' => $d[$h['Explanation']],
				'!promo' => $d[$h['Promotion']]));
	
	$voucher->field_use_area['und'][0]['value'] = 'U';
	$voucher->field_use_area['und'][1]['value'] = 'C';
	$voucher->field_valid_date_ymd_w_enddate['und'][0] = array(
			'value' => '2013-01-01 00:00:00',
			'value2' => '9999-12-31 23:59:59',
			'timezone' => 'Asia/Ulaanbaatar',
			'timezone_db' => 'Asia/Ulaanbaatar',
			'date_type' => 'datetime'
			);
	$voucher->field_tree_child_voca_name['und'][0]['value'] = 'tpl_vouchercardtype';

	node_save( $voucher);
	*/
//	printf("voucher type saved\n");

	// 자동으로 voucher를 위한 counter를 생성시킨다.
	$allCounters = views_get_view_result('list_counter_for_vouchercardtype', 'panel_pane_1');
	foreach($allCounters as $counter) {
		$counter = node_load( $counter->nid);
		$node = get_voucher_attr( $voucher, 'treenodecounterforvoucher', $counter);
		unset( $node->field_amount['und']);

		$mapping = array( 
			'Remains' => array( 'Remains', 'Money'),
			'FreeCallTime' => array( 'FREE_TIME', 'Sec'),
			'FreeSms' => array( 'FREE_SMS', 'Count'),
			'FreeMms' => array( 'FREE_MMS', 'Count'),
			'FreeCrbt' => array( 'FREE_CRBT', 'Count'),
			'FreeGprs' => array( 'FREE_GPRS', 'Byte'),
			'FreeVideoCallTime' => array( 'FREE_VCALL_TIME', 'Sec'),
			'PacketPackage' => array( 'PACKET_PACKAGE', 'KByte'),
			);

		// set remains
		if ( isset( $mapping[$counter->title]) ) {
			if ( !empty( $d[$h[$mapping[$counter->title][0]]])) {
				$node->field_amount['und'][0]['value'] = $d[$h[$mapping[$counter->title][0]]];
				printf("  %s : %d\n", $counter->title, $node->field_amount['und'][0]['value']);
			}
			$node->field_counter_sub_unit_type['und'][0]['tid'] = $term['countersubunit'][$mapping[$counter->title][1]];
		}
		$node->field_ref_tree_tid['und'][0]['tid'] = 796;

		node_save($node);
	}

	continue;

	// loyaltypoint content type을 자동으로 생성해준다.
	$node = get_voucher_attr( $voucher, 'loyaltypoint');
	node_save($node);

	// link products 
	$category = $d[$h['Categories']];
	for( $i=0; $i < strlen( $category); $i++) {
		$c = substr( $category, $i, 1);
		if ( ! isset( $prd_category[$c])) {
			printf( ">> WARNING : Unknown category %s\n", $c);
			continue;
		}

		$name = $prd_category[$c];
		printf("  Link voucher to product : (%s) %s\n", $c, $name);

		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'treenodeproductforvoucher')
			->propertyCondition( 'title', $name)
			->fieldCondition( 'field_ref_vouchercardtype', 'nid', $voucher->nid)
			->execute();

		if ( empty( $result)) {
			$product_link = ocs_admin_get_new_node( 'treenodeproductforvoucher');
			$product_link->title = $name;
			printf("  New Product link : %s\n", $name);
		}
		else if ( count( $result['node']) == 1) {
			printf("  Existing Product link : %s\n", $name);
			$product_link = node_load( array_pop( array_keys( $result['node'])));
		}
		else {
			printf(">> ERROR too same product %s for the voucher %d\n", $name, count( $result['node']));
			continue;
		}

		$product_link->field_ref_vouchercardtype['und'][0]['nid'] = $voucher->nid;
		$nids = ocs_get_nodes_by_title( 'simpleproductoffering', $name);
		if ( empty( $nids)) {
			printf("  Product not found : %s\n", $name);
		}
		else {
			$product = node_load( $nids[0]);
			$product_link->title = $product->title;
			$product_link->field_ref_product['und'][0]['nid'] = $product->nid;
			$product_link->field_ref_tree_tid['und'][0]['value'] = $term['tpl_vouchercardtype']['voucher_product_specific'];
			$product_link->field_active_period['und'][0]['value'] = $d[$h['Active Days']];
			$product_link->field_grace_period['und'][0]['value'] = $d[$h['Grace Days']];

			node_save( $product_link);
			create_counter_for_voucherprd($product_link, $product->nid);
		}
	}
}


function get_voucher_attr( $voucher, $type, $counter = NULL)
{
	// find the attribute
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->fieldCondition('field_ref_vouchercardtype', 'nid', $voucher->nid);

	if ( ! empty( $counter)) {
		$query->fieldCondition('field_ref_counter', 'nid', $counter->nid);
	}
	$result = $query->execute();

	if ( empty( $result)) {
		$node = ocs_admin_get_new_node( $type);
		$node->field_ref_vouchercardtype['und'][0]['nid'] = $voucher->nid;
		if ( ! empty( $counter)) {
			$node->field_ref_counter['und'][0]['nid'] = $counter->nid;
		}
		printf("  New attribute type=%s ", $type);
	}
	else {
		$node = node_load( array_pop( array_keys( $result['node'])));
		printf("  Existing attribute type=%s ", $type);
	}

	if ( ! empty( $counter)) {
		$node->title = $counter->title;
	}
	else {
		$node->title = $type;
	}
	printf("title=%s\n", $node->title);

	return $node;
}

function create_counter_for_voucherprd($treenodeproductforvoucher, $productNid)
{
	global $user;

	/* delete existing counter list for thos voucher product *
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'treenodecounterforvoucherprd')
		->fieldCondition( 'field_ref_treenodeproductforvouc', 'nid', $treenodeproductforvoucher->nid)
		->execute();

	if ( empty( $result)) {
	}
	else {
		foreach( array_keys( $result['node']) as $nid) {
			node_delete( $nid);
		}
	}
	return;
	   */
	
	// 해당 상품의 optional counter를 가져옴.
	$params = array('0' => $productNid);
	$view = views_get_view('list_prdcounterlist');
	$view->set_display('panel_pane_2');
	$view->set_arguments($params);
	$view->execute();
	
	$counterNids = array();
	foreach($view->result as $record) {
		//$counterList[] = view_get_field_value_by_label($view, 'qtabConfigNid', $record);
		$counterNids[] = view_get_field_value_by_label($view, 'qtabConfigNid', $record);
	}
	
	// Prepaid면서 Basic , Optional인 counter만 걸러낸다.
	$params = array('0' => join('+',$counterNids));
	$view = views_get_view('query_list_counter');
		$view->set_display('panel_pane_4');
	$view->set_arguments($params);
	$view->execute();
	$counterList = array();
	foreach($view->result as $record) {
		$counterList[] = $record->nid;
	}
	
	// 해당 상품의 basic counter를 가져옴.
	// $product = node_load($productNid);
	$counter_list = _get_default_basic_counters($productNid);
    foreach($counter_list as $key => $value) {
		$counterList[] = $key;
	}
	
	foreach($counterList as $record) {
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'treenodecounterforvoucherprd')
			->fieldCondition( 'field_ref_counter', 'nid', $record)
			->fieldCondition( 'field_ref_treenodeproductforvouc', 'nid', $treenodeproductforvoucher->nid)
			->execute();

		if ( empty( $result)) {
			$counter = node_load( $record);

			$treenodecounterforvoucherprd = ocs_admin_get_new_node( 'treenodecounterforvoucherprd');
			$treenodecounterforvoucherprd->field_ref_counter['und'][0]['nid'] = $record;
			$treenodecounterforvoucherprd->field_ref_treenodeproductforvouc['und'][0]['nid'] = $treenodeproductforvoucher->nid;
			$treenodecounterforvoucherprd->title = $counter->title;
			node_save($treenodecounterforvoucherprd);

			printf("    add new counter %s\n", $counter->title);
		}
		else {
			$treenodecounterforvoucherprd = node_load( array_pop( array_keys( $result['node'])));

			$counter = node_load( $treenodecounterforvoucherprd->field_ref_counter['und'][0]['nid']);
			printf("    %d existing counter %s\n", count( $result['node']), $counter->title);
		}
	}
}


