new map_favela_obj[30];

stock CreateMap_Favela_1()
{
    CreateDynamicObject(3698, -127.6511, -1109.9980, 5.9829, -1.6999, 2.0999, -11.1000); //barrio3B_LAe
    CreateDynamicObject(7577, -134.8325, -1123.2198, 10.8315, 0.0000, 0.0000, 80.7994); //vegastwires15
    CreateDynamicObject(16285, -137.4595, -1108.4549, 3.8176, 0.0000, 0.0000, -9.1996); //des_westrn7_03
    CreateDynamicObject(3655, -132.3238, -1129.9481, 5.2487, 0.0000, 0.0000, 77.6996); //ganghous03_LAx
    CreateDynamicObject(12957, -132.7333, -1256.1153, 2.7402, 0.0000, 0.0000, -116.2994); //sw_pickupwreck01
    CreateDynamicObject(1362, -132.5249, -1253.4289, 2.7163, 0.0000, 0.0000, 0.0000); //CJ_FIREBIN_(L0)
    CreateDynamicObject(3174, -129.7026, -1251.0384, 1.9586, 0.0000, 0.0000, 163.8999); //sm_airstrm_sml_
    CreateDynamicObject(1440, -125.9430, -1251.1081, 2.4749, 0.0000, -3.2999, -52.8997); //DYN_BOX_PILE_3
    CreateDynamicObject(1362, -127.1744, -1248.5489, 2.6263, 0.0000, 0.0000, 0.0000); //CJ_FIREBIN_(L0)
    CreateDynamicObject(11433, -83.2481, -1237.8392, 3.0885, 0.0000, -2.2999, 32.4000); //adobe_hoose2
    CreateDynamicObject(3285, -108.6015, -1266.0122, 3.3071, -2.7999, 0.0000, -169.0997); //conhoos4
    CreateDynamicObject(3242, -112.5847, -1249.4814, 3.7806, 0.0000, 0.0000, 15.6000); //conhoos1
    CreateDynamicObject(3283, -64.3610, -1245.3391, 3.3914, 7.8997, -5.3997, -61.7999); //conhoos3
    CreateDynamicObject(3655, -120.5988, -1132.5041, 5.2487, 0.0000, 0.0000, 77.6996); //ganghous03_LAx
    map_favela_obj[0] = CreateDynamicObject(3253, -100.2173, -1245.3978, 1.6663, 0.0000, 0.0000, 22.3999); //des_westrn11_
    SetDynamicObjectMaterial(map_favela_obj[0], 0, 5710, "cemetery_law", "brickgrey", 0x00000000);
    SetDynamicObjectMaterial(map_favela_obj[0], 3, 9514, "711_sfw", "brick", 0x00000000);
    SetDynamicObjectMaterial(map_favela_obj[0], 7, 17508, "barrio1_lae2", "brickred", 0x00000000);
    CreateDynamicObject(11501, -99.6930, -1263.9255, 1.3299, 0.0000, 0.0000, -168.3000); //des_westrn9_03
    CreateDynamicObject(3241, -89.3022, -1258.6777, 1.2553, -3.2999, 0.0000, -65.5000); //conhoos2
    CreateDynamicObject(3698, -113.7244, -1112.5432, 4.8048, -1.6999, 6.9998, -11.1000); //barrio3B_LAe
    CreateDynamicObject(3250, -95.7720, -1240.2519, 1.0405, 0.0000, 0.0000, 22.2999); //des_westrn9_
    CreateDynamicObject(3702, -94.2468, -1076.6926, 13.3507, 3.0999, 0.0000, -6.3000); //barrio6B_LAe2
    CreateDynamicObject(5450, -35.0349, -1230.8868, 7.2824, 0.0000, 0.0000, -128.8999); //laeChicano06
    map_favela_obj[1] = CreateDynamicObject(3655, -125.3591, -1240.2497, 4.6887, 0.0000, 0.0000, -12.3999); //ganghous03_LAx
    SetDynamicObjectMaterial(map_favela_obj[1], 9, 5710, "cemetery_law", "brickgrey", 0x00000000);
    map_favela_obj[2] = CreateDynamicObject(3655, -121.7593, -1228.7003, 4.6887, 0.0000, 0.0000, 166.9998); //ganghous03_LAx
    SetDynamicObjectMaterial(map_favela_obj[2], 9, 5710, "cemetery_law", "brickgrey", 0x00000000);
    map_favela_obj[3] = CreateDynamicObject(3698, -212.6976, -1098.8885, 26.4139, -1.6999, -0.2001, -113.8998); //barrio3B_LAe
    SetDynamicObjectMaterial(map_favela_obj[3], 6, 9514, "711_sfw", "brick", 0x00000000);
    map_favela_obj[4] = CreateDynamicObject(3655, -119.1912, -1217.0162, 4.6887, 0.0000, 0.0000, 167.5997); //ganghous03_LAx
    SetDynamicObjectMaterial(map_favela_obj[4], 9, 9514, "711_sfw", "brick", 0x00000000);
    map_favela_obj[5] = CreateDynamicObject(3655, -126.8283, -1156.1717, 4.9685, 0.0000, 0.0000, -20.3999); //ganghous03_LAx
    SetDynamicObjectMaterial(map_favela_obj[5], 9, 5710, "cemetery_law", "brickgrey", 0x00000000);
    map_favela_obj[6] = CreateDynamicObject(3655, -122.7462, -1144.7458, 3.7288, 0.0000, 0.0000, -20.7999); //ganghous03_LAx
    SetDynamicObjectMaterial(map_favela_obj[6], 9, 9514, "711_sfw", "brick", 0x00000000);
    map_favela_obj[7] = CreateDynamicObject(3677, -119.4598, -1274.7027, 7.2579, 0.0000, 0.0000, -172.5995); //lawnhousegreyLS
    SetDynamicObjectMaterial(map_favela_obj[7], 4, 9514, "711_sfw", "brick", 0x00000000);
    SetDynamicObjectMaterial(map_favela_obj[7], 8, 9514, "711_sfw", "brick", 0x00000000);
    map_favela_obj[8] = CreateDynamicObject(3655, -100.3404, -1103.3066, 5.9088, 0.0000, 0.0000, -7.5000); //ganghous03_LAx
    SetDynamicObjectMaterial(map_favela_obj[8], 9, 9514, "711_sfw", "brick", 0x00000000);
    CreateDynamicObject(3174, -123.6909, -1250.3940, 1.9586, 0.0000, 0.0000, -136.8000); //sm_airstrm_sml_
    CreateObject(9552, -246.7774, -1089.3658, 34.9818, 0.0000, 0.0000, 169.5000, 600.0); //sandbch_sfw03 (ESTATICO)
    CreateDynamicObject(12957, -125.5251, -1269.0793, 2.5501, 0.0000, 0.0000, -54.4999); //sw_pickupwreck01
    CreateObject(16133, -160.5350, -1007.2625, 3.9237, 0.0000, 0.0000, 41.1999, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateDynamicObject(3655, -121.6986, -1089.0185, 10.5534, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateObject(16133, -162.2713, -1011.2183, 15.8738, 0.0000, 0.0000, 66.2994, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateDynamicObject(1440, -114.2388, -1263.7674, 2.3048, 0.0000, 0.0000, -87.4000); //DYN_BOX_PILE_3
    CreateDynamicObject(1362, -132.8948, -1259.7491, 2.5964, 0.0000, 0.0000, 0.0000); //CJ_FIREBIN_(L0)
    CreateDynamicObject(1362, -132.9299, -1262.4925, 2.5964, 0.0000, 0.0000, 54.5998); //CJ_FIREBIN_(L0)
    CreateObject(16133, -196.7086, -1017.6140, 20.5237, 0.0000, 0.0000, 123.4000, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateDynamicObject(1440, -102.0735, -1248.0405, 2.0016, 0.0000, 0.0000, -65.6996); //DYN_BOX_PILE_3
    CreateObject(16133, -200.6004, -1011.7116, 10.0338, 0.0000, 0.0000, 123.4000, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateDynamicObject(5822, -194.7601, -1097.7740, 18.4048, 0.0000, 0.0000, 165.1999); //lhroofst14
    CreateObject(16133, -215.7575, -985.2191, 14.3416, 24.5000, 0.0000, 74.5998, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -211.6893, -990.1259, 25.8073, 24.5000, 0.0000, 74.5998, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -249.3755, -995.9683, 28.4356, 5.4000, 0.0000, 142.0000, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -271.2554, -1035.7008, 32.6687, 5.4000, 0.0000, 142.0000, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16055, -182.8065, -1131.6214, 24.2693, 0.0000, 0.0000, 161.1000, 600.0); //quarry_bit04 (ESTATICO)
    CreateDynamicObject(3066, -81.4140, -1256.7479, 1.7618, -6.5000, 0.0000, 25.6000); //ammotrn_obj
    CreateDynamicObject(16667, -147.8341, -1024.4680, 26.6005, 0.0000, 0.0000, -49.9000); //des_rockgp2_14
    CreateObject(16133, -127.4095, -1058.4930, 4.7937, 0.0000, 0.0000, 19.8999, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -284.3468, -1074.4184, 35.9117, 5.4000, 0.0000, 144.5001, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -302.6694, -1121.6488, 40.5521, 5.4000, 0.0000, 144.5001, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -300.9425, -1158.7497, 30.9951, -14.1997, 0.0000, -149.1999, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -288.0432, -1181.0970, 24.5680, -14.1997, 0.0000, -129.1999, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -275.0252, -1183.4416, 35.3180, -14.1997, 0.0000, -129.1999, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -272.4052, -1195.5976, 10.4671, -10.0000, 0.0000, -128.4998, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -252.2120, -1192.7740, 18.9468, -10.0000, 0.0000, -128.4998, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -227.0702, -1210.3039, 0.3264, -10.0000, 0.0000, -104.2994, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -202.7326, -1229.6141, 8.6651, -10.0000, 0.0000, -75.9999, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -218.1768, -1220.8375, -0.1386, -10.0000, 0.0000, -104.2994, 600.0); //des_rockgp2_18 (ESTATICO)
    map_favela_obj[9] = CreateDynamicObject(3698, -194.9483, -1109.8181, 14.5860, -1.6999, 2.0999, 70.1996); //barrio3B_LAe
    SetDynamicObjectMaterial(map_favela_obj[9], 6, 9514, "711_sfw", "brick", 0x00000000);
    map_favela_obj[10] = CreateDynamicObject(3698, -199.2239, -1108.0538, 19.9277, -1.6999, 1.7998, 70.1996); //barrio3B_LAe
    SetDynamicObjectMaterial(map_favela_obj[10], 6, 9514, "711_sfw", "brick", 0x00000000);
    CreateDynamicObject(3698, -170.0066, -1100.6960, 6.3470, -1.6999, -0.5001, 61.0000); //barrio3B_LAe
    CreateDynamicObject(3698, -172.4544, -1098.9117, 11.5537, -1.6999, -0.5001, 61.0000); //barrio3B_LAe
    map_favela_obj[11] = CreateDynamicObject(3655, -175.2021, -1112.5454, 6.6487, 0.0000, 0.0000, 151.3999); //ganghous03_LAx
    SetDynamicObjectMaterial(map_favela_obj[11], 9, 9514, "711_sfw", "brick", 0x00000000);
    CreateDynamicObject(3702, -203.7460, -1137.2690, 8.1273, 2.0999, 0.0000, -8.6997); //barrio6B_LAe2
    map_favela_obj[12] = CreateDynamicObject(3655, -140.2810, -1149.9770, 5.5485, 0.0000, 0.0000, 69.8999); //ganghous03_LAx
    SetDynamicObjectMaterial(map_favela_obj[12], 9, 5710, "cemetery_law", "brickgrey", 0x00000000);
    CreateDynamicObject(5822, -199.6515, -1215.4654, 18.4048, 0.0000, 0.0000, -153.6997); //lhroofst14
    CreateDynamicObject(5822, -215.1725, -1229.5074, 31.6947, 0.0000, 0.0000, -161.7998); //lhroofst14
    CreateDynamicObject(5822, -198.2666, -1064.6075, 28.9248, 0.0000, 0.0000, 146.1002); //lhroofst14
    CreateDynamicObject(3655, -208.1746, -1184.5649, 15.1287, 0.0000, 0.0000, 13.0999); //ganghous03_LAx
    CreateDynamicObject(3655, -205.4956, -1196.0766, 15.1287, 0.0000, 0.0000, 13.0999); //ganghous03_LAx
    CreateDynamicObject(3655, -209.5576, -1184.8862, 21.6287, 0.0000, 0.0000, 12.7999); //ganghous03_LAx
    CreateDynamicObject(3655, -206.9620, -1196.3557, 21.6287, 0.0000, 0.0000, 12.7999); //ganghous03_LAx
    map_favela_obj[13] = CreateDynamicObject(3698, -214.7801, -1097.9156, 31.8299, -1.6999, -0.2001, 64.4001); //barrio3B_LAe
    SetDynamicObjectMaterial(map_favela_obj[13], 6, 9514, "711_sfw", "brick", 0x00000000);
    map_favela_obj[14] = CreateDynamicObject(3655, -206.9201, -1087.2458, 26.6287, 0.0000, 0.0000, 156.6999); //ganghous03_LAx
    SetDynamicObjectMaterial(map_favela_obj[14], 9, 9514, "711_sfw", "brick", 0x00000000);
    CreateObject(16133, -245.0108, -1236.6821, 3.8334, -10.0000, 0.0000, -87.8999, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -242.2389, -1238.9222, 19.0783, -10.0000, 0.0000, -87.8999, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateObject(16133, -244.7704, -1226.5495, 33.0396, -10.0000, 0.0000, -154.5997, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateDynamicObject(11496, -200.9761, -1074.9028, 24.1194, 0.0000, 0.0000, -23.7999); //des_wjetty
    CreateDynamicObject(1432, -199.6475, -1070.6062, 24.3971, 0.0000, 0.0000, -21.5998); //DYN_TABLE_2
    CreateDynamicObject(1432, -196.9792, -1071.6623, 24.3971, 0.0000, 0.0000, -21.5998); //DYN_TABLE_2
    CreateDynamicObject(1432, -199.7232, -1073.4045, 24.3971, 0.0000, 0.0000, -21.5998); //DYN_TABLE_2
    CreateDynamicObject(1432, -198.6275, -1075.5808, 24.3971, 0.0000, 0.0000, -21.5998); //DYN_TABLE_2
    CreateDynamicObject(671, -182.3289, -1051.4958, 23.5368, 0.0000, 0.0000, 0.0000); //sm_bushytree
    CreateDynamicObject(671, -160.7492, -1036.9399, 26.5468, 0.0000, 0.0000, 34.0000); //sm_bushytree
    CreateDynamicObject(671, -216.2308, -1109.8017, 23.7369, 0.0000, 0.0000, 34.0000); //sm_bushytree
    CreateDynamicObject(3655, -160.5119, -1090.2451, 6.9633, 0.0000, 0.0000, -15.1997); //ganghous03_LAx
    CreateDynamicObject(3655, -140.6779, -1056.0456, 19.5534, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(688, -220.3397, -1209.2623, 23.3194, 0.0000, 0.0000, -87.5998); //sm_fir_scabg
    CreateDynamicObject(16061, -250.6835, -1083.5782, 47.3596, 0.0000, 0.0000, -28.8999); //des_treeline2
    CreateDynamicObject(18688, -132.8567, -1259.8619, 1.6023, 0.0000, 0.0000, 0.0000); //fire
    CreateDynamicObject(18688, -132.8567, -1262.6820, 1.6023, 0.0000, 0.0000, 0.0000); //fire
    CreateObject(16133, -238.2747, -1248.9531, 3.8945, 6.0998, 0.0000, -87.8999, 600.0); //des_rockgp2_18 (ESTATICO)
    CreateDynamicObject(16667, -237.7026, -1230.5124, 50.2905, 0.0000, 0.0000, -64.6996); //des_rockgp2_14
    CreateDynamicObject(19972, -139.8916, -1120.9964, 2.4735, 0.0000, 0.0000, 78.4999); //SAMPRoadSign25
    CreateDynamicObject(3459, -106.9503, -1127.7259, 7.4141, 0.0000, 0.0000, -99.2994); //vgntelepole1
    CreateDynamicObject(3459, -137.8834, -1122.6307, 5.8839, 0.0000, 0.0000, -99.2994); //vgntelepole1
    CreateDynamicObject(3459, -150.2487, -1120.6058, 6.2241, 0.0000, 0.0000, -99.2994); //vgntelepole1
    CreateDynamicObject(7577, -185.5164, -1114.1551, 26.4062, 33.2999, 0.0000, 79.1996); //vegastwires15
    CreateDynamicObject(3246, -143.8069, -1107.6247, 4.0138, 0.6000, 3.5000, -10.1997); //des_westrn7_
    CreateDynamicObject(3459, -175.3634, -1115.9106, 15.0438, 0.0000, 0.0000, -107.3999); //vgntelepole1
    CreateDynamicObject(3459, -197.5016, -1111.7397, 30.1940, 0.0000, 0.0000, -102.4999); //vgntelepole1
    CreateDynamicObject(3459, -208.6611, -1109.3774, 27.7040, 0.0000, 0.0000, -100.8999); //vgntelepole1
    CreateDynamicObject(7577, -207.7324, -1108.2275, 42.9155, 4.0998, 0.0000, 169.5997); //vegastwires15
    CreateDynamicObject(1265, -179.0140, -1118.1982, 3.8728, 0.0000, 0.0000, 0.0000); //BlackBag2
    CreateDynamicObject(1344, -180.0867, -1119.2790, 4.0268, 0.0000, 0.0000, 69.0998); //CJ_Dumpster2
    map_favela_obj[15] = CreateDynamicObject(11447, -182.3350, -1080.8684, 12.3893, 0.0000, 0.0000, -121.9000); //des_pueblo08
    SetDynamicObjectMaterial(map_favela_obj[15], 0, -1, "none", "none", 0xFFBC8F8F);
    CreateDynamicObject(3459, -161.8746, -1118.3977, 7.5341, 0.0000, 0.0000, -99.2994); //vgntelepole1
    CreateDynamicObject(1264, -179.0332, -1119.1726, 3.7627, 0.0000, 0.0000, 0.0000); //BlackBag1
    CreateDynamicObject(1439, -198.3343, -1148.2635, 4.6763, 0.0000, 0.1000, 175.1999); //DYN_DUMPSTER_1
    CreateDynamicObject(11447, -174.9494, -1074.0716, 12.3717, 0.0000, 0.0000, -37.9999); //des_pueblo08
    CreateDynamicObject(3459, -208.6611, -1109.3774, 37.9239, 0.0000, 0.0000, -17.4999); //vgntelepole1
    map_favela_obj[16] = CreateDynamicObject(11426, -171.3551, -1068.6975, 12.3570, 0.0000, 0.0000, -37.9999); //des_adobe03
    SetDynamicObjectMaterial(map_favela_obj[16], 0, 9514, "711_sfw", "brick", 0x00000000);
    map_favela_obj[17] = CreateDynamicObject(11447, -183.1676, -1082.2927, 15.4895, 0.0000, 0.0000, -32.7000); //des_pueblo08
    SetDynamicObjectMaterial(map_favela_obj[17], 0, -1, "none", "none", 0xFFBC8F8F);
    map_favela_obj[18] = CreateDynamicObject(11447, -178.4297, -1083.2994, 12.3893, 0.0000, 0.0000, -121.9000); //des_pueblo08
    SetDynamicObjectMaterial(map_favela_obj[18], 0, -1, "none", "none", 0xFFBC8F8F);
    CreateDynamicObject(3171, -150.6181, -1067.1827, 12.3093, 0.0000, 0.0000, -13.0999); //trailer5_01
    map_favela_obj[19] = CreateDynamicObject(11443, -142.5352, -1061.3332, 12.4666, 0.0000, 0.0000, 24.5998); //des_pueblo4
    SetDynamicObjectMaterial(map_favela_obj[19], 0, 9514, "711_sfw", "brick", 0x00000000);
    CreateDynamicObject(3655, -135.6360, -1096.7762, 7.4713, 1.6999, 0.0000, -13.1000); //ganghous03_LAx
    CreateDynamicObject(3655, -131.5294, -1085.0554, 10.7734, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(3655, -111.4252, -1103.0909, 6.2034, 0.0000, 0.0000, -8.5999); //ganghous03_LAx
    CreateDynamicObject(12957, -178.4776, -1125.0505, 4.1402, 0.0000, 0.0000, -170.6999); //sw_pickupwreck01
    CreateDynamicObject(3655, -130.2785, -1073.7281, 15.3332, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    map_favela_obj[20] = CreateDynamicObject(11457, -164.2077, -1063.0766, 12.0263, 0.0000, 0.0000, 134.7998); //des_pueblo09
    SetDynamicObjectMaterial(map_favela_obj[20], 0, -1, "none", "none", 0xFFF08080);
    CreateDynamicObject(3655, -123.5230, -1100.1507, 6.7533, 0.0000, 0.0000, -9.5000); //ganghous03_LAx
    CreateDynamicObject(5838, -171.1139, -1024.9643, 41.2224, 0.0000, 0.0000, -38.7999); //ci_watertank01
    CreateDynamicObject(16630, -174.7731, -1081.6484, 12.9259, 0.0000, 0.0000, 57.1999); //des_ghotfenc04
    CreateDynamicObject(950, -177.0162, -1086.0483, 12.9082, 0.0000, 0.0000, 57.7999); //Plant_Pot_12
    CreateDynamicObject(950, -174.9488, -1082.7651, 12.9082, 0.0000, 0.0000, 57.7999); //Plant_Pot_12
    CreateDynamicObject(3655, -107.5706, -1091.6485, 10.1834, 0.0000, 0.0000, -12.4996); //ganghous03_LAx
    CreateDynamicObject(1362, -189.8495, -1142.7369, 5.1834, 0.0000, 0.0000, 0.0000); //CJ_FIREBIN_(L0)
    CreateDynamicObject(3655, -104.9776, -1079.9531, 15.0733, 0.0000, 0.0000, -12.4996); //ganghous03_LAx
    CreateDynamicObject(3655, -118.1425, -1077.2386, 15.2833, 0.0000, 0.0000, -12.4996); //ganghous03_LAx
    CreateDynamicObject(3655, -131.2012, -1073.0118, 6.6332, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(3655, -144.9255, -1082.3121, 6.4734, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(3655, -142.3049, -1070.9610, 6.4734, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(3655, -147.4721, -1093.3420, 6.9633, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(3655, -173.7422, -1086.6512, 6.9633, 0.0000, 0.0000, -15.1997); //ganghous03_LAx
    CreateDynamicObject(3655, -158.4176, -1079.0936, 6.4232, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(3655, -102.4972, -1068.7628, 15.0733, 0.0000, 0.0000, -12.4996); //ganghous03_LAx
    CreateDynamicObject(3655, -115.7845, -1065.8177, 15.3034, 0.0000, 0.0000, -12.4996); //ganghous03_LAx
    CreateDynamicObject(3655, -142.3049, -1070.9610, 13.3134, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(3655, -141.8621, -1058.9519, 14.9334, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(3655, -128.0484, -1062.7790, 19.3432, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(3655, -140.5437, -1051.2403, 14.5934, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(7577, -217.1349, -1161.0747, 38.0466, 14.8000, 0.0000, -6.9000); //vegastwires15
    CreateDynamicObject(3655, -155.7879, -1067.7032, 6.4232, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(3459, -220.4306, -1189.1699, 27.7040, 0.0000, 0.0000, -7.1999); //vgntelepole1
    CreateDynamicObject(3655, -144.9255, -1082.3121, 10.6632, 0.0000, 0.0000, -13.0000); //ganghous03_LAx
    CreateDynamicObject(2972, -121.1222, -1142.9558, 7.2929, 0.0000, 0.0000, 70.0998); //k_cargo4
    CreateDynamicObject(2972, -125.3973, -1154.7656, 8.4926, 0.0000, 0.0000, 70.0998); //k_cargo4
    CreateDynamicObject(2972, -122.6361, -1130.9216, 8.7826, 0.0000, 0.0000, 70.0998); //k_cargo4
    CreateDynamicObject(2972, -134.9783, -1127.5273, 8.7826, 0.0000, 0.0000, 70.0998); //k_cargo4
    CreateDynamicObject(3031, -122.0746, -1145.3033, 8.9364, 0.0000, 0.0000, -65.5998); //wong_dish
    CreateDynamicObject(3031, -125.3767, -1156.8813, 9.7264, 0.0000, 0.0000, -52.5998); //wong_dish
    CreateDynamicObject(3031, -120.9914, -1130.9620, 10.4397, 0.0000, 0.0000, -68.7994); //wong_dish
    CreateDynamicObject(2972, -174.1087, -1074.7873, 15.2110, 0.0000, 0.0000, -128.8999); //k_cargo4
    CreateDynamicObject(2972, -170.4848, -1067.5732, 15.2910, 0.0000, 0.0000, -128.8999); //k_cargo4
    CreateDynamicObject(2972, -160.6239, -1057.5024, 18.1212, 0.0000, 0.0000, -133.3000); //k_cargo4
    CreateDynamicObject(2972, -159.5977, -1058.4693, 18.1212, 0.0000, 0.0000, -133.3000); //k_cargo4
    CreateDynamicObject(17036, -291.0697, -1125.3697, 40.2024, 0.0000, 0.0000, 3.7999); //cuntw_carport1_
    CreateDynamicObject(2972, -152.6929, -1142.6820, 8.9610, 0.0000, 0.0000, -109.3998); //k_cargo4
    CreateDynamicObject(2972, -206.7964, -1089.5858, 30.2063, 0.0000, 0.0000, 66.3000); //k_cargo4
    CreateDynamicObject(1294, -103.0827, -1127.0257, 4.3715, 0.0000, 0.0000, -104.3999); //mlamppost
    CreateDynamicObject(1294, -117.2507, -1123.7810, 5.5815, 0.0000, 0.0000, -104.3999); //mlamppost
    CreateDynamicObject(1294, -132.7552, -1120.5539, 6.7013, 0.0000, 0.0000, -104.3999); //mlamppost
    CreateDynamicObject(1294, -141.1996, -1119.6245, 7.3014, 0.0000, 0.0000, -96.4999); //mlamppost
    CreateDynamicObject(1294, -157.4049, -1121.8446, 8.1513, 0.0000, 0.0000, -96.4999); //mlamppost
    CreateDynamicObject(1294, -171.1770, -1123.4321, 8.1513, 0.0000, 0.0000, -132.8999); //mlamppost
    CreateDynamicObject(1294, -179.5090, -1121.0393, 7.5914, 0.0000, 0.0000, 160.3000); //mlamppost
    CreateDynamicObject(1294, -183.3011, -1132.0450, 7.6015, 0.0000, 0.0000, 160.3000); //mlamppost
    CreateDynamicObject(1294, -187.8388, -1142.7308, 9.0415, 0.0000, 0.0000, 160.3000); //mlamppost
    CreateDynamicObject(1294, -190.8318, -1141.7147, 9.2115, 0.0000, 0.0000, -19.6998); //mlamppost
    CreateDynamicObject(1294, -188.3598, -1130.1838, 13.4511, 0.0000, 0.0000, -19.6998); //mlamppost
    CreateDynamicObject(1294, -184.7375, -1115.9730, 16.6814, 0.0000, 0.0000, -19.6998); //mlamppost
    CreateDynamicObject(1294, -180.3182, -1103.6307, 16.6814, 0.0000, 0.0000, -19.6998); //mlamppost
    CreateDynamicObject(1294, -169.3896, -1085.9814, 16.6814, 0.0000, 0.0000, -29.1998); //mlamppost
    CreateDynamicObject(1294, -156.4745, -1072.9576, 16.6814, 0.0000, 0.0000, -38.4999); //mlamppost
    CreateDynamicObject(1294, -199.6864, -1096.2281, 28.1615, 0.0000, 0.0000, -19.6998); //mlamppost
    CreateDynamicObject(1294, -207.4532, -1117.9200, 27.4314, 0.0000, 0.0000, -19.6998); //mlamppost
    CreateDynamicObject(1294, -209.0433, -1130.3414, 32.5415, 0.0000, 0.0000, -19.6998); //mlamppost
    CreateDynamicObject(1294, -210.9857, -1141.0830, 34.3115, 0.0000, 0.0000, -13.1997); //mlamppost
    CreateDynamicObject(1294, -211.5193, -1151.7220, 34.3115, 0.0000, 0.0000, -13.1997); //mlamppost
    CreateDynamicObject(1294, -212.1327, -1158.8907, 34.3115, 0.0000, 0.0000, -7.4998); //mlamppost
    CreateDynamicObject(1294, -212.1083, -1166.8044, 31.8915, 0.0000, 0.0000, -15.3999); //mlamppost
    CreateDynamicObject(1294, -211.6215, -1177.6761, 28.3313, 0.0000, 0.0000, -11.9996); //mlamppost
    CreateDynamicObject(1294, -215.1038, -1199.7336, 28.3313, 0.0000, 0.0000, -11.9996); //mlamppost
    CreateDynamicObject(1294, -207.5473, -1211.3702, 28.0314, 0.0000, 0.0000, 9.8999); //mlamppost
    CreateDynamicObject(1294, -227.1372, -1214.2309, 41.3013, 0.0000, 0.0000, 9.8999); //mlamppost
    CreateDynamicObject(1294, -229.9535, -1198.0943, 41.3013, 0.0000, 0.0000, 14.3999); //mlamppost
    CreateDynamicObject(1294, -217.7967, -1088.7435, 41.2014, 0.0000, 0.0000, -23.5998); //mlamppost
    CreateDynamicObject(1294, -208.6439, -1071.1252, 39.5614, 0.0000, 0.0000, -38.5998); //mlamppost
    CreateDynamicObject(1294, -195.6652, -1052.4785, 36.2714, 0.0000, 0.0000, -47.4998); //mlamppost
    CreateDynamicObject(1294, -179.0292, -1041.2220, 33.1413, 0.0000, 0.0000, -47.4998); //mlamppost
    CreateDynamicObject(1294, -189.4788, -1076.9250, 28.1615, 0.0000, 0.0000, -33.1999); //mlamppost
    CreateDynamicObject(1294, -175.2946, -1059.6678, 28.1615, 0.0000, 0.0000, -40.4999); //mlamppost
    CreateDynamicObject(1294, -150.1719, -1046.0815, 28.1615, 0.0000, 0.0000, -78.3999); //mlamppost
    CreateDynamicObject(1451, -152.5451, -1065.2657, 13.0410, 0.0000, 0.0000, -101.9000); //DYN_COUP
    CreateDynamicObject(1451, -167.6837, -1108.6031, 4.2711, 0.0000, 0.0000, 150.8999); //DYN_COUP
    CreateDynamicObject(1408, -165.1372, -1108.2751, 4.2368, 0.0000, 0.0000, 60.7999); //DYN_F_WOOD_2
    CreateDynamicObject(1408, -199.4877, -1148.7176, 5.0486, 0.0000, 0.0000, -4.4000); //DYN_F_WOOD_2
    CreateDynamicObject(14467, -168.2742, -1110.9742, 12.6688, 0.0000, 0.0000, 61.3997); //carter_statue
    CreateDynamicObject(14467, -172.5585, -1118.8321, 12.6688, 0.0000, 0.0000, 61.3997); //carter_statue
    CreateDynamicObject(16405, -291.8081, -1152.1706, 41.3917, 6.5000, -7.0998, -8.0999); //desn2_hutskel03
    CreateDynamicObject(16405, -290.1871, -1141.8159, 42.0713, 0.0000, -4.8000, -8.0999); //desn2_hutskel03
    CreateDynamicObject(16405, -290.9743, -1147.1986, 41.8907, 0.0000, 0.0000, -8.0999); //desn2_hutskel03
    CreateDynamicObject(1482, -199.9467, -1080.0012, 25.6744, 0.0000, 0.0000, 156.2998); //DYN_GARRAGE1
    CreateDynamicObject(17036, -290.5407, -1133.3326, 40.2024, 0.0000, 0.0000, 3.7999); //cuntw_carport1_
    CreateDynamicObject(1737, -169.8739, -1113.3728, 10.2102, 0.0000, 0.0000, 61.4000); //MED_DINNING_5
    CreateDynamicObject(1482, -197.2447, -1073.8708, 25.6744, 0.0000, 0.0000, 156.2998); //DYN_GARRAGE1
    CreateDynamicObject(1482, -200.7250, -1072.4399, 25.6744, 0.0000, 0.0000, -24.2000); //DYN_GARRAGE1
    CreateDynamicObject(1482, -203.3706, -1078.5544, 25.6744, 0.0000, 0.0000, -23.0000); //DYN_GARRAGE1
    CreateDynamicObject(2456, -194.3435, -1070.8839, 24.3010, 0.0000, 0.0000, -113.4999); //CJ_FF_STAND02
    CreateDynamicObject(2692, -171.5617, -1110.9112, 10.9371, 0.0000, 0.0000, 14.6997); //CJ_BANNER10
    CreateDynamicObject(2693, -172.6820, -1114.7607, 10.8863, 0.0000, 0.0000, 97.3000); //CJ_BANNER11
    CreateDynamicObject(2919, -180.1840, -1114.9232, 10.6357, 0.0000, -1.3997, 0.0000); //kmb_holdall
    CreateDynamicObject(1758, -170.7624, -1110.2767, 10.2264, 0.0000, -0.1999, 0.0000); //LOW_SINGLE_4
    CreateDynamicObject(1647, -175.9676, -1118.2004, 10.3479, 0.0000, 0.0000, 60.8997); //lounge_wood_dn
    CreateDynamicObject(2531, -205.3576, -1080.2867, 24.2772, 0.0000, 0.0000, 65.0998); //CJ_OFF2_LIC_1_M
    CreateDynamicObject(2114, -153.6125, -1045.4104, 23.7922, 0.0000, 0.0000, 0.0000); //basketball
    CreateDynamicObject(947, -150.1790, -1043.7447, 25.8847, 0.0000, 0.0000, 108.0000); //bskballhub_lax01
    CreateDynamicObject(947, -162.0971, -1045.7712, 25.8145, 0.0000, 0.0000, -83.0998); //bskballhub_lax01
    CreateDynamicObject(19158, -226.1477, -1146.8424, 27.0151, 0.0000, 0.0000, -4.2999); //MetalLightBars2
    CreateDynamicObject(1653, -150.9467, -1048.2873, 24.3229, 0.0000, 0.0000, 12.2999); //fencehaitism
    CreateDynamicObject(1653, -162.5540, -1053.1982, 24.3229, 0.0000, 0.0000, 33.2999); //fencehaitism
    CreateDynamicObject(1653, -178.5234, -1065.8625, 24.3630, 0.0000, 0.0000, 49.0998); //fencehaitism
    CreateDynamicObject(1653, -192.1656, -1085.3276, 24.3567, 0.0996, 0.0000, 60.0998); //fencehaitism
    CreateDynamicObject(1653, -201.3773, -1106.3270, 24.3535, 0.0996, 0.0000, 70.4998); //fencehaitism
    map_favela_obj[21] = CreateDynamicObject(18762, -227.7044, -1151.6302, 33.0750, 0.0000, 0.0000, -6.7999); //Concrete1mx1mx5m
    SetDynamicObjectMaterial(map_favela_obj[21], 0, 19058, "xmasboxes", "wrappingpaper20", 0x00000000);
    CreateDynamicObject(19129, -225.9474, -1146.8784, 30.5683, 0.0000, 0.0000, -4.1999); //DanceFloor2
    CreateDynamicObject(3274, -227.7118, -1152.7285, 30.3295, 0.0000, 0.0000, 85.6996); //substa_grid_
    CreateDynamicObject(3274, -223.6777, -1140.9289, 30.3295, 0.0000, 0.0000, -94.8000); //substa_grid_
    map_favela_obj[22] = CreateDynamicObject(18766, -227.7312, -1146.6667, 32.8883, 0.0000, 0.0000, 85.6996); //Concrete10mx1mx5m
    SetDynamicObjectMaterial(map_favela_obj[22], 0, 19129, "dancefloors", "dancefloor1", 0x00000000);
    CreateDynamicObject(16088, -225.5661, -1146.8452, 30.3957, 0.0000, 0.0000, -4.8000); //des_pipestrut01
    map_favela_obj[23] = CreateDynamicObject(18762, -226.9091, -1141.8354, 33.0750, 0.0000, 0.0000, -6.7999); //Concrete1mx1mx5m
    SetDynamicObjectMaterial(map_favela_obj[23], 0, 19058, "xmasboxes", "wrappingpaper20", 0x00000000);
    CreateDynamicObject(19149, -224.2250, -1148.1239, 35.1016, 0.0000, 0.0000, -52.2999); //PinSpotLight7
    CreateDynamicObject(19149, -223.9855, -1144.8668, 35.1016, 0.0000, 0.0000, -108.8999); //PinSpotLight7
    CreateDynamicObject(19152, -224.3576, -1149.4182, 35.1128, 0.0000, 0.0000, -62.7999); //PinSpotLight10
    CreateDynamicObject(19152, -224.0950, -1146.1949, 35.1128, 0.0000, 0.0000, -91.9999); //PinSpotLight10
    CreateDynamicObject(19144, -224.2518, -1148.7949, 35.1343, 0.0000, 0.0000, -101.7995); //PinSpotLight2
    CreateDynamicObject(19144, -224.2418, -1147.1745, 35.0844, 0.0000, 0.0000, -95.6996); //PinSpotLight2
    CreateDynamicObject(19145, -224.1383, -1145.4891, 35.0872, 0.0000, 0.0000, -113.6996); //PinSpotLight3
    CreateDynamicObject(19296, -227.5440, -1149.8349, 34.8428, 0.0000, 0.0000, -3.1998); //PointLight16
    CreateDynamicObject(19298, -226.8470, -1143.7871, 34.9780, 0.0000, 0.0000, 0.0000); //PointLight18
    CreateDynamicObject(19608, -225.0596, -1146.9355, 30.5718, 0.0000, 0.0000, 85.5998); //WoodenStage1
    CreateDynamicObject(1341, -211.9420, -1147.1153, 30.8220, 0.0000, 0.0000, -4.4998); //icescart_prop
    CreateDynamicObject(1342, -212.5088, -1152.0000, 30.9120, 0.0000, 0.0000, 178.8999); //noodlecart_prop
    CreateDynamicObject(1457, -203.8094, -1162.8907, 8.1597, 10.0000, 0.0000, 115.5998); //DYN_OUTHOUSE_2
    CreateDynamicObject(1571, -224.3771, -1135.0410, 31.1727, 0.0000, 0.0000, 83.6996); //CJ_NOODLE_1
    CreateDynamicObject(3861, -226.7436, -1181.2386, 24.7565, 0.0000, 0.0000, 82.3999); //marketstall01_SFXRF
    CreateDynamicObject(3928, -209.2615, -1184.7386, 25.2877, 0.0000, 0.0000, 13.8000); //helipad
    CreateDynamicObject(8856, -210.4049, -1148.3559, 29.9519, 0.0000, 0.0000, -3.4999); //vgEplntr06_lvs
    CreateDynamicObject(1653, -209.6768, -1147.9969, 30.8262, 0.0996, 0.0000, -93.3002); //fencehaitism
    CreateDynamicObject(17969, -222.8977, -1120.4946, 29.4561, 0.0000, 6.9998, 163.1999); //hub_graffitti
    CreateDynamicObject(5401, -200.4042, -1036.9637, 33.0032, 0.0000, 7.7999, 52.2999); //laegarages1nw
    CreateDynamicObject(18451, -201.1743, -1155.1561, 5.7600, 0.0000, 9.1997, 92.5998); //cs_oldcarjmp
    CreateDynamicObject(3655, -151.6159, -1145.8291, 5.5485, 0.0000, 0.0000, 69.8999); //ganghous03_LAx
    CreateDynamicObject(16667, -140.4407, -1028.2956, 16.9904, 0.0000, 0.0000, -49.9000); //des_rockgp2_14
    CreateDynamicObject(3655, -170.3502, -1180.8415, 7.6883, 0.0000, 0.0000, -101.9000); //ganghous03_LAx
    CreateDynamicObject(3655, -158.7646, -1183.2829, 7.1585, 0.0000, 0.0000, -101.9000); //ganghous03_LAx
    CreateDynamicObject(3655, -146.7191, -1185.8214, 6.1985, 0.0000, 0.0000, -101.9000); //ganghous03_LAx
    CreateDynamicObject(3655, -142.6398, -1166.4554, 6.0885, 0.0000, 0.0000, -105.5998); //ganghous03_LAx
    CreateDynamicObject(3655, -153.9584, -1162.5594, 6.0984, 0.0000, 0.0000, -105.5998); //ganghous03_LAx
    CreateDynamicObject(3655, -165.2823, -1159.0124, 5.2884, 0.0000, 0.0000, -105.5998); //ganghous03_LAx
    CreateDynamicObject(3655, -162.1257, -1199.2325, 7.1585, 0.0000, 0.0000, -101.9000); //ganghous03_LAx
    CreateDynamicObject(3655, -150.4620, -1201.6904, 6.1385, 0.0000, 0.0000, -101.9000); //ganghous03_LAx
    CreateDynamicObject(3655, -174.0832, -1196.7131, 7.9685, 0.0000, 0.0000, -101.9000); //ganghous03_LAx
    CreateDynamicObject(3655, -161.4754, -1200.0356, 13.8184, 0.0000, 0.0000, -11.8000); //ganghous03_LAx
    CreateDynamicObject(3459, -203.0910, -1082.5582, 37.1739, 0.0000, 0.0000, 174.6999); //vgntelepole1
    CreateDynamicObject(1483, -204.8244, -1153.7668, 8.4427, 0.0000, 0.0000, 173.7998); //DYN_GARRAGE2
    CreateDynamicObject(1737, -292.1469, -1132.5085, 40.2472, 0.0000, 0.0000, 93.4999); //MED_DINNING_5
    CreateDynamicObject(3458, -157.7053, -1170.5019, 1.6713, -4.0998, 2.4000, -14.4996); //vgncarshade1
    CreateDynamicObject(3458, -158.9745, -1175.4492, 2.0369, -4.0998, 2.4000, -14.4996); //vgncarshade1
    CreateDynamicObject(3458, -158.6844, -1192.2800, 2.4721, -5.2999, 3.9000, -14.4996); //vgncarshade1
    CreateDynamicObject(3458, -138.4378, -1186.4471, 1.1418, 4.5000, 1.2998, 77.0998); //vgncarshade1
    CreateDynamicObject(19942, -292.5715, -1132.8039, 41.1497, 0.0000, 0.0000, 89.8999); //PoliceRadio1
    CreateDynamicObject(3458, -140.9897, -1157.8758, 0.5242, -3.5999, 0.8999, -19.3999); //vgncarshade1
    CreateDynamicObject(1737, -292.2666, -1130.5527, 40.2472, 0.0000, 0.0000, 93.4999); //MED_DINNING_5
    CreateDynamicObject(2115, -219.5133, -1147.8603, 30.5729, 0.0000, 0.0000, 86.8000); //LOW_DINNING_1
    CreateDynamicObject(14820, -219.4741, -1147.3608, 31.4528, 0.0000, 0.0000, 86.2996); //dj_stuff
    CreateDynamicObject(2901, -292.1875, -1131.9392, 40.5611, 0.0000, 0.0000, 91.0998); //kmb_marijuana
    CreateDynamicObject(2901, -292.2741, -1130.0300, 40.5611, 0.0000, 0.0000, 91.0998); //kmb_marijuana
    CreateDynamicObject(19941, -292.3692, -1132.7939, 41.0367, 0.0000, 0.0000, 0.0000); //GoldBar1
    CreateDynamicObject(19941, -292.3692, -1132.7241, 41.0367, 0.0000, 0.0000, 0.0000); //GoldBar1
    CreateDynamicObject(19941, -292.3692, -1132.6440, 41.0367, 0.0000, 0.0000, 0.0000); //GoldBar1
    CreateDynamicObject(19941, -292.3692, -1132.7440, 41.0867, 0.0000, 0.0000, 0.0000); //GoldBar1
    CreateDynamicObject(19941, -292.3692, -1132.6739, 41.0867, 0.0000, 0.0000, 0.0000); //GoldBar1
    CreateDynamicObject(1575, -292.4248, -1131.3382, 41.0148, 0.0000, 0.0000, 1.7999); //drug_white
    CreateDynamicObject(19942, -292.5714, -1132.7237, 41.1497, 0.0000, 0.0000, 89.8999); //PoliceRadio1
    CreateDynamicObject(2044, -291.9843, -1132.7547, 41.0797, 0.0000, 0.0000, 54.2000); //CJ_MP5K
    CreateDynamicObject(2891, -292.4356, -1132.3071, 40.9953, 0.0000, 0.0000, 1.3997); //kmb_packet
    CreateDynamicObject(2891, -292.4479, -1131.8072, 40.9953, 0.0000, 0.0000, 1.3997); //kmb_packet
    CreateDynamicObject(1252, -292.0346, -1132.3072, 41.1184, -88.1996, 0.2998, 0.0000); //barrelexpos
    CreateDynamicObject(2035, -169.8800, -1113.4532, 11.0179, 0.0000, 0.0000, 0.0000); //CJ_M16
    CreateDynamicObject(1575, -292.4446, -1130.7082, 41.0148, 0.0000, 0.0000, 1.7999); //drug_white
    CreateDynamicObject(1575, -292.0046, -1130.6947, 41.0148, 0.0000, 0.0000, 91.1996); //drug_white
    CreateDynamicObject(1575, -291.9920, -1131.2950, 41.0148, 0.0000, 0.0000, 91.1996); //drug_white
    CreateDynamicObject(1578, -292.4891, -1130.3353, 41.0036, 0.0000, 0.0000, 0.0000); //drug_green
    CreateDynamicObject(1578, -292.4891, -1129.9453, 41.0036, 0.0000, 0.0000, 0.0000); //drug_green
    CreateDynamicObject(1578, -292.4891, -1129.5550, 41.0036, 0.0000, 0.0000, 0.0000); //drug_green
    CreateDynamicObject(2035, -292.0816, -1129.7303, 41.0419, 0.0000, 0.0000, 93.0998); //CJ_M16
    CreateDynamicObject(1279, -169.5287, -1112.5758, 10.9996, 0.0000, 0.0000, 59.1999); //craigpackage
    CreateDynamicObject(1550, -292.6176, -1128.8785, 40.6268, 0.0000, 0.0000, 0.0000); //CJ_MONEY_BAG
    CreateDynamicObject(1550, -292.6176, -1128.3581, 40.6268, 0.0000, 0.0000, 0.0000); //CJ_MONEY_BAG
    CreateDynamicObject(1550, -292.6976, -1127.8380, 40.6268, 0.0000, 0.0000, 0.0000); //CJ_MONEY_BAG
    CreateDynamicObject(1319, -116.5121, -1117.2602, 2.7853, 0.0000, 0.0000, -10.5999); //ws_ref_bollard
    CreateDynamicObject(1319, -117.0587, -1120.1794, 2.4251, 0.0000, 0.0000, -10.5999); //ws_ref_bollard
    CreateDynamicObject(1319, -117.6694, -1123.4433, 1.8552, 0.0000, 0.0000, -10.5999); //ws_ref_bollard
    CreateDynamicObject(933, -115.5108, -1117.3857, 2.2723, 3.3998, 8.6000, 0.0000); //CJ_CABLEROLL
    CreateDynamicObject(2985, -170.8807, -1116.4449, 10.2131, 0.0000, 0.0000, -35.3997); //minigun_base
    CreateDynamicObject(951, -210.8885, -1159.7773, 30.5440, 0.0000, 0.0000, 86.1997); //CJ_VIEW_TELE2
    CreateDynamicObject(951, -210.9255, -1160.3363, 30.3740, 0.0000, 0.0000, 86.1997); //CJ_VIEW_TELE2
    CreateDynamicObject(1472, -228.9306, -1156.7447, 30.1877, 0.0000, 0.0000, -5.0000); //DYN_PORCH_1
    CreateDynamicObject(1472, -227.4461, -1156.8746, 30.1877, 0.0000, 0.0000, -5.0000); //DYN_PORCH_1
    CreateDynamicObject(1358, -204.3242, -1166.2259, 7.9457, 0.0000, 1.1000, 22.3999); //CJ_SKIP_Rubbish
    CreateDynamicObject(850, -201.4725, -1160.8852, 6.0567, -5.9000, 5.1999, 0.0000); //CJ_urb_rub_1
    CreateDynamicObject(355, -226.2839, -1182.1218, 24.3721, 79.1997, -22.1000, 72.8999); //ak47
    CreateDynamicObject(3409, -290.6466, -1142.2315, 40.1115, 0.0000, -5.7999, -10.1998); //grassplant
    CreateDynamicObject(3655, -31.3178, -1191.5499, 7.9383, 0.0000, 0.0000, -36.5997); //ganghous03_LAx
    CreateDynamicObject(803, -227.2440, -1189.4980, 24.4608, 0.0000, 0.0000, -109.0000); //genVEG_bush09
    CreateDynamicObject(3409, -291.6206, -1147.6441, 40.1115, 0.0000, -5.7999, -10.1998); //grassplant
    CreateDynamicObject(3920, -209.5471, -1148.4317, 28.9176, 16.2999, 0.0000, -94.8999); //lib_veg3
    CreateDynamicObject(3948, -172.2369, -1049.9636, 32.3813, 0.0000, 0.0000, -109.7998); //bistrogarden
    CreateDynamicObject(711, -204.7913, -1160.1966, 12.0291, 0.0000, 0.0000, 0.0000); //vgs_palm02
    CreateDynamicObject(3655, -63.2341, -1207.9605, 5.8783, 0.0000, 0.0000, 53.0001); //ganghous03_LAx
    CreateDynamicObject(3655, -71.5332, -1218.9738, 5.0083, 0.0000, 0.0000, -126.8996); //ganghous03_LAx
    CreateDynamicObject(711, -204.8813, -1176.3360, 16.1191, 0.0000, 0.0000, 0.0000); //vgs_palm02
    CreateDynamicObject(711, -205.4011, -1170.2967, 13.8690, 0.0000, 0.0000, 0.0000); //vgs_palm02
    CreateDynamicObject(3655, -40.0181, -1202.1418, 7.2484, 0.0000, 0.0000, -36.5997); //ganghous03_LAx
    CreateDynamicObject(3655, -52.8709, -1194.2082, 6.0184, 0.0000, 0.0000, 53.0001); //ganghous03_LAx
    CreateDynamicObject(3655, -42.2725, -1179.8940, 6.2983, 0.0000, 0.0000, -126.8996); //ganghous03_LAx
    CreateDynamicObject(1440, -56.3311, -1210.1258, 3.2318, 0.0000, 0.0000, 49.7999); //DYN_BOX_PILE_3
    CreateDynamicObject(12951, -101.5348, -1112.1176, 0.5558, -3.9000, 0.0000, -105.2999); //sw_shopflat01
    CreateDynamicObject(1216, -113.9107, -1126.3887, 1.6407, 0.0000, 0.0000, 166.4999); //phonebooth1
    CreateDynamicObject(1216, -147.5162, -1110.7912, 4.8739, 0.0000, 0.0000, -10.7999); //phonebooth1
    CreateDynamicObject(1216, -168.4581, -1173.8691, 4.7422, 0.0000, 0.0000, 167.3001); //phonebooth1
    CreateDynamicObject(1216, -209.5556, -1137.3906, 30.6080, 0.0000, 0.0000, -95.7999); //phonebooth1
    CreateDynamicObject(1490, -216.7891, -1184.1833, 24.6718, 0.0000, 0.0000, 13.1000); //tag_01

    printf("[MAPA %d]: Favela 1 loaded...", gm_count[COUNT_CREATEMAP]);
    gm_count[COUNT_CREATEMAP]++;
}

stock RemoveBuilding_MapFavela1(playerid)
{
    RemoveBuildingForPlayer(playerid, 3276, -182.9530, -1146.2900, 4.1640, 0.10); // cxreffencesld
    RemoveBuildingForPlayer(playerid, 3276, -172.2339, -1149.7700, 3.9609, 0.10); // cxreffencesld
    RemoveBuildingForPlayer(playerid, 3276, -241.5079, -965.3670, 28.2500, 0.10); // cxreffencesld
    RemoveBuildingForPlayer(playerid, 3276, -132.8130, -1191.6700, 2.7265, 0.10); // cxreffencesld
    RemoveBuildingForPlayer(playerid, 3276, -128.7109, -1181.2299, 2.7265, 0.10); // cxreffencesld
    RemoveBuildingForPlayer(playerid, 791, -54.8358, -1201.0500, 0.2187, 0.10); // vbg_fir_copse
    RemoveBuildingForPlayer(playerid, 785, -54.8358, -1201.0500, 0.2187, 0.10); // LOD Model of vbg_fir_copse
    RemoveBuildingForPlayer(playerid, 3276, -124.3519, -1171.6300, 2.7265, 0.10); // cxreffencesld
    RemoveBuildingForPlayer(playerid, 3276, -127.9059, -1164.8699, 2.7265, 0.10); // cxreffencesld
    RemoveBuildingForPlayer(playerid, 3276, -139.1170, -1161.0899, 2.7734, 0.10); // cxreffencesld

    return 1;
}