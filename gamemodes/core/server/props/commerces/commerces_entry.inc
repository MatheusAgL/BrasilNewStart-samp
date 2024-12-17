

#define 		MAX_PROPERTIES  			(1000)
#define 		PROP_VW    					(10000)
#define 		MAX_INTERIORS				(151)
#define 		MAX_TYPES       			(3)
#define 		TYPE_EMPTY      			(0)
#define 		TYPE_HOUSE 					(1)
#define 		TYPE_BUSINESS				(2)
#define 		TYPE_BANK   				(3)
#define 		TYPE_COPS        			(4)
#define         BUSINESS_IMPOSTOS           1800
#define         INVALID_PROP_ID             -1
#define	        PROP_TYPE_MARKET            1
#define         TRADE_TYPE_PARKING          4

enum // Property Type Enum
	E_P_TYPES
	{
		tIcon,
		tName[32]
	}

enum // Uniq Interiors Enum
	E_INTERIORS
	{
		inIntID,
		Float:inExit_X,
		Float:inExit_Y,
		Float:inExit_Z,
		Float:inExitA,
		inName[64]
	};

enum // Properties Enum
	E_PROPERTIES
	{
		eIcon,
		eType,
		eMapIcon,
		Float:eEntX,
		Float:eEntY,
		Float:eEntZ,
		Float:eEntA,
		eUniqIntId
	};

enum // Properties Info enum
	E_PROPERTIES_INFO
	{
		eOwnerID,
	    eOwner[MAX_PLAYER_NAME],
		ePname[64],
	    eTill,
	    ePrice,
        prop_type,
	    eDate,
		Timestamp:eVencimento,
	    eDespesas,
	    eLock,
	    eRobbed,
		eMoneyRobbed,
		eDoor,

		eInsumos,
		ePrecoInsumo,
		eMaxInsumos,
		eInsumosReq,

		propType,
		bool:eDoorOpen,
		bool:eAlarm,
		eDoorTimer,
		eDoorDestroyed,
		bool:eLaser,
		bool:eLoaded,
		eTimerLaser,
		eLasers[13],
		Text3D:eText,
	};

//  [ uniq property id ]
new	unid;

//  [ Info empresas ]
new PropInfo[MAX_PROPERTIES][E_PROPERTIES_INFO];

stock Property_SetDate(propid, Days:days) {
	PropInfo[propid][eVencimento] = Now() + Days:days;
}

stock Property_AddMoney(propid, value) {
	PropInfo[propid][eTill] += value;
}

stock Property_RemoveMoney(propid, value) {
	PropInfo[propid][eTill] -= value;
}

stock Property_GetName(propid) {
	new name[64];

	format(name, sizeof(name), PropInfo[propid][ePname]);
	return name;
}

//	[ Array of all the property interior info ]
new const interiorInfo[][E_INTERIORS] = {
	{ 11, 2003.1178, 1015.1948, 33.008, 351.5789, "Four Dragons' Managerial Suite" },
	{ 5, 772.2394, -4.7490, 1000.7287, 184.3459, "Ganton Ginasio" },
	{ 3, 974.0177, -9.5937, 1001.1484, 22.6045, "Brothel" },
	{ 3, 961.9308, -51.9071, 1001.1172, 95.5381, "Brothel2" },
	{ 3, 834.0798, 7.397700, 1004.1870, 267.2197, "Lotérica" },
	{ 3, 1037.8276, 0.397, 1001.2845, 353.9335, "Blastin' Fools Records" },
	{ 3, 1212.1489, -28.5388, 1000.9531, 170.5692, "The Big Spread Ranch" },
	{ 18, 1290.4106, 1.9512, 1001.0201, 179.9419, "Warehouse 1" },
	{ 1, 1412.1472, -2.2836, 1000.9241, 114.661, "Warehouse 2" },
	{ 3, 1527.0468, -12.0236, 1002.0971, 350.0013, "B Dup's Apartment" },
	{ 2, 1523.5098, -47.8211, 1002.2699, 262.7038, "B Dup's Crack Palace" },
	{ 3, 612.2191, -123.9028, 997.9922, 266.5704, "Wheel Arch Angels" },
	{ 3, 512.9291, -11.6929, 1001.5653, 198.7669, "OG Loc's House" },
	{ 3, 418.4666, -80.4595, 1001.8047, 343.2358, "Barbeiro" },
	{ 3, 386.5259, 173.6381, 1008.3828, 63.7399, "Planning Department" },
	{ 3, 288.4723, 170.0647, 1007.1794, 22.0477, "Las Venturas Police Department" },
	{ 3, 206.4627, -137.7076, 1003.0938, 10.9347, "Pro-Laps" },
	{ 3, -100.2674, -22.9376, 1000.7188, 17.285, "Sex Shop" },
	{ 3, -201.2236, -43.2465, 1002.2734, 45.8613, "Las Venturas Tattoo parlor" },
	{ 17, -202.9381, -6.7006, 1002.2734, 204.2693, "Lost San Fierro Tattoo parlor" },
	{ 17, -25.7220, -187.8216, 1003.5469, 5.0760, "24/7" },
	{ 5, 454.9853, -107.2548, 999.4376, 309.0195, "Diner 1" },
	{ 5, 372.5565, -131.3607, 1001.4922, 354.2285, "Pizza Stack" },
	{ 17, 378.026, -190.5155, 1000.6328, 141.0245, "Rusty Brown's Donuts" },
	{ 7, 315.244, -140.8858, 999.6016, 7.4226, "Ammu-nation" },
	{ 5, 225.0306, -9.1838, 1002.218, 85.5322, "Victim" },
	{ 2, 611.3536, -77.5574, 997.9995, 320.9263, "Loco Low Co" },
	{ 10, 246.0688, 108.9703, 1003.2188, 0.2922, "Departamento de Policia de San Fierro" },
	{ 10, 6.0856, -28.8966, 1003.5494, 5.0365, "24/7 (version 2 - large)" },
	{ 7, 773.7318, -74.6957, 1000.6542, 5.2304, "Below The Belt Gym" },
	{ 1, 621.4528, -23.7289, 1000.9219, 15.6789, "Transfenders" },
	{ 1, 445.6003, -6.9823, 1000.7344, 172.2105, "World of Coq" },
	{ 1, 285.4075, -41.7505, 1001.5156, 181.3310, "Ammu-nation" },
	{ 1, 204.1174, -46.8047, 1001.8047, 357.5777, "SubUrban" },
	{ 1, 245.2307, 304.7632, 999.1484, 273.4364, "Denise's Bedroom" },
	{ 3, 290.623, 309.0622, 999.1484, 89.9164, "Helena's Barn" },
	{ 5, 322.5014, 303.6906, 999.1484, 8.1747, "Barbara's Love nest" },
	{ 1, -2041.2334, 178.3969, 28.8465, 156.2153, "San Fierro Garage" },
	{ 1, -1402.6613, 106.3897, 1032.2734, 105.1356, "Oval Stadium" },
	{ 7, -1403.0116, -250.4526, 1043.5341, 355.8576, "8-Track Stadium" },
	{ 2, 1204.6689, -13.5429, 1000.9219, 350.0204, "The Pig Pen (strip club)" },
	{ 10, 2016.1156, 1017.1541, 996.875, 88.0055, "Four Dragons" },
	{ 1, -741.8495, 493.0036, 1371.9766, 71.7782, "Liberty City" },
	{ 2, 2447.8704, -1704.4509, 1013.5078, 314.5253, "Ryder's House" },
	{ 1, 2527.0176, -1679.2076, 1015.4986, 260.9709, "Sweet's House" },
	{ 10, -1129.8909, 1057.5424, 1346.4141, 274.5268, "RC Battlefield" },
	{ 3, 2496.0549, -1695.1749, 1014.7422, 179.2174, "The Johnson House" },
	{ 10, 366.0248, -73.3478, 1001.5078, 292.0084, "Burger shot" },
	{ 1, 2233.9363, 1711.8038, 1011.6312, 184.3891, "Caligula's Casino" },
	{ 2, 269.6405, 305.9512, 999.1484, 215.6625, "Katie's Lovenest" },
	{ 2, 414.2987, -18.8044, 1001.8047, 41.4265, "Barber Shop 2 (Reece's)" },
	{ 2, 1.1853, -3.2387, 999.4284, 87.5718, "Angel Pine Trailer" },
	{ 18, -30.9875, -89.6806, 1003.5469, 359.8401, "Mercado 24/7" },
	{ 18, 161.4048, -94.2416, 1001.8047, 0.7938, "Zip" },
	{ 3, -2638.8232, 1407.3395, 906.4609, 94.6794, "The Pleasure Domes" },
	{ 5, 1267.8407, -776.9587, 1091.9063, 231.3418, "Madd Dogg's Mansion" },
	{ 2, 2536.5322, -1294.8425, 1044.125, 254.9548, "Big Smoke's Crack Palace" },
	{ 5, 2350.1597, -1181.0658, 1027.9766, 99.1864, "Burning Desire Building" },
	{ 1, -2158.6731, 642.09, 1052.375, 86.5402, "Wu-Zi Mu's" },
	{ 10, 419.8936, 2537.1155, 10.00, 67.6537, "Abandoned AC tower" },
	{ 14, 256.9047, -41.6537, 1002.0234, 85.8774, "Wardrobe/Changing room" },
	{ 14, 204.1658, -165.7678, 1000.5234, 181.7583, "Didier Sachs" },
	{ 12, 1133.35, -7.8462, 1000.6797, 165.8482, "Casino (Redsands West)" },
	{ 14, -1420.4277, 1616.9221, 1052.5313, 159.1255, "Kickstart Stadium" },
	{ 17, 493.1443, -24.2607, 1000.6797, 356.9864, "Alhambra" },
	{ 18, 1727.2853, -1642.9451, 20.2254, 172.4193, "Atrium" },
	{ 16, -202.842, -24.0325, 1002.2734, 252.8154, "Los Santos Tattoo Parlor" },
	{ 5, 2233.6919, -1112.8107, 1050.8828, 8.6483, "Safe House group 1" },
	{ 6, 2194.7900, -1204.3500, 1049.0234, 90.0000, "Safe House group 2" },
	{ 9, 2319.1272, -1023.9562, 1050.2109, 167.3959, "Safe House group 3" },
	{ 10, 2261.0977, -1137.8833, 1050.6328, 266.88, "Safe House group 4" },
	{ 17, -959.6453, 1956.4626, 9.0000, 180.0000, "Fábrica de Materiais" },
	{ 16, -26.1856, -140.9164, 1003.5469, 2.9087, "Mercado 24/7" },
	{ 15, 2217.281, -1150.5349, 1025.7969, 273.7328, "Jefferson Motel" },
	{ 1, 1.5491, 23.3183, 1199.5938, 359.9054, "Jet Interior" },
	{ 1, 681.6216, -451.8933, -25.6172, 166.166, "The Welcome Pump" },
	{ 3, 234.6087, 1187.8195, 1080.2578, 349.4844, "Burglary House X1" },
	{ 2, 225.5707, 1240.0643, 1082.1406, 96.2852, "Burglary House X2" },
	{ 1, 224.288, 1289.1907, 1082.1406, 359.868, "Burglary House X3" },
	{ 5, 239.2819, 1114.1991, 1080.9922, 270.2654, "Burglary House X4" },
	{ 15, 207.5219, -109.7448, 1005.1328, 358.62, "Binco" },
	{ 15, 295.1391, 1473.3719, 1080.2578, 352.9526, "4 Burglary houses" },
	{ 15, -1417.8927, 932.4482, 1041.5313, 0.7013, "Blood Bowl Stadium" },
	{ 12, 446.3247, 509.9662, 1001.4195, 330.5671, "Budget Inn Motel Room" },
	{ 0, 2306.3826, -15.2365, 26.7496, 274.49, "Palamino Bank" },
	{ 0, 2331.8984, 6.7816, 26.5032, 100.2357, "Palamino Diner" },
	{ 0, 663.0588, -573.6274, 16.3359, 264.9829, "Dillimore Gas Station" },
	{ 18, -227.5703, 1401.5544, 27.7656, 269.2978, "Lil' Probe Inn" },
	{ 0, -688.1496, 942.0826, 13.6328, 177.6574, "Torreno's Ranch" },
	{ 0, -1916.1268, 714.8617, 46.5625, 152.2839, "Zombotech - lobby area" },
	{ 0, 818.7714, -1102.8689, 25.794, 91.1439, "Crypt in LS cemetery (temple)" },
	{ 0, 255.2083, -59.6753, 1.5703, 1.4645, "Blueberry Liquor Store" },
	{ 2, 446.626, 1397.738, 1084.3047, 343.9647, "Pair of Burglary Houses" },
	{ 5, 318.5645, 1118.2079, 1083.8828, 0.0000, "Crack Den" },
	{ 5, 227.7559, 1114.3844, 1080.9922, 266.2624, "Burglary House X11" },
	{ 4, 261.1165, 1287.2197, 1080.2578, 178.9149, "Burglary House X12" },
	{ 4, 286.1490, -84.5633, 1001.5156, 319.5923, "Ammu-nation" },
	{ 4, 449.0172, -88.9894, 999.5547, 89.6608, "Jay's Diner" },
	{ 4, -27.844, -26.6737, 1003.5573, 184.3118, "Mercado 24/7" },
	{ 0, 2135.2004, -2276.2815, 20.6719, 318.59, "Warehouse 3" },
	{ 4, 306.1966, 307.819, 1003.3047, 203.1354, "Michelle's Love Nest*" },
	{ 10, 24.3769, 1341.1829, 1084.375, 8.3305, "Burglary House X14" },
	{ 1, 963.0586, 2159.7563, 1011.0303, 175.313, "Sindacco Abatoir" },
	{ 0, 2548.4807, 2823.7429, 10.8203, 270.6003, "K.A.C.C. Military Fuels Depot" },
	{ 0, 215.1515, 1874.0579, 13.1406, 177.5538, "Area 69" },
	{ 4, 221.6766, 1142.4962, 1082.6094, 184.9618, "Burglary House X13" },
	{ 12, 2323.7063, -1147.6509, 1050.7101, 206.5352, "Unused Safe House" },
	{ 6, 344.9984, 307.1824, 999.1557, 193.643, "Millie's Bedroom" },
	{ 12, 411.9707, -51.9217, 1001.8984, 173.3449, "Barber Shop" },
	{ 4, -1421.5618, -663.8262, 1059.5569, 170.9341, "Dirtbike Stadium" },
	{ 6, 773.8887, -47.7698, 1000.5859, 10.7161, "Cobra Gym" },
	{ 6, 246.6695, 65.8039, 1003.6406, 7.9562, "Los Santos Police Department" },
	{ 14, -1864.9434, 55.7325, 1055.5276, 85.8541, "Los Santos Airport" },
	{ 4, -262.1759, 1456.6158, 1084.3672, 82.459, "Burglary House X15" },
	{ 5, 22.861, 1404.9165, 1084.4297, 349.6158, "Burglary House X16" },
	{ 5, 140.3679, 1367.8837, 1083.8621, 349.2372, "Burglary House X17" },
	{ 3, 1494.8589, 1306.48, 1093.2953, 196.065, "Bike School" },
	{ 14, -1813.213, -58.012, 1058.9641, 335.3199, "Francis International Airport" },
	{ 16, -1401.067, 1265.3706, 1039.8672, 178.6483, "Vice Stadium" },
	{ 6, 234.2826, 1065.229, 1084.2101, 4.3864, "Burglary House X18" },
	{ 6, -68.5145, 1353.8485, 1080.2109, 3.5742, "Burglary House X19" },
	{ 6, -2240.1028, 136.973, 1035.4141, 269.0954, "Zero's RC Shop" },
	{ 6, 297.144, -109.8702, 1001.5156, 20.2254, "Ammu-nation" },
	{ 6, 316.5025, -167.6272, 999.5938, 10.3031, "Ammu-nation" },
	{ 15, -285.2511, 1471.197, 1084.375, 85.6547, "Burglary House X20" },
	{ 6, -26.8339, -55.5846, 1003.5469, 3.9528, "Mercado 24/7" },
	{ 6, 442.1295, -52.4782, 999.7167, 177.9394, "Secret Valley Diner" },
	{ 2, 2182.2017, 1628.5848, 1043.8723, 224.8601, "Rosenberg's Office in Caligulas" },
	{ 6, 748.4623, 1438.2378, 1102.9531, 0.6069, "Fanny Batter's Whore House" },
	{ 8, 2807.3604, -1171.7048, 1025.5703, 193.7117, "Colonel Furhberger's" },
	{ 9, 366.0002, -9.4338, 1001.8516, 160.528, "Cluckin' Bell" },
	{ 1, 2216.1282, -1076.3052, 1050.4844, 86.428, "The Camel's Toe Safehouse" },
	{ 1, 2268.5156, 1647.7682, 1084.2344, 99.7331, "Caligula's Roof" },
	{ 2, 2236.6997, -1078.9478, 1049.0234, 2.5706, "Old Venturas Strip Casino" },
	{ 3, -2031.1196, -115.8287, 1035.1719, 190.1877, "Driving School" },
	{ 8, 2365.1089, -1133.0795, 1050.875, 177.3947, "Verdant Bluffs Safehouse" },
	{ 0, 1168.512, 1360.1145, 10.9293, 196.5933, "Bike School" },
	{ 10, 164.0054, -165.9578, 1009.6730, 269.8852, "Loja de Acessórios" },
	{ 10, 1893.0731, 1017.8958, 31.8828, 86.1044, "Four Dragons' Janitor's Office" },
	{ 11, 501.9019, -67.7362, 998.7578, 171.5706, "Bar" },
	{ 8, -42.5267, 1408.23, 1084.4297, 172.068, "Burglary House X21" },
	{ 11, 2282.9099, -1138.2900, 1050.8984, 0.0000, "Willowfield Safehouse" },
	{ 9, 84.9244, 1324.2983, 1083.8594, 159.5582, "Burglary House X22" },
	{ 9, 260.7421, 1238.2261, 1084.2578, 84.3084, "Burglary House X23" },
	{ 0, -1658.1656, 1215.0002, 7.25, 103.9074, "Otto's Autos" },
	{ 0, -1961.6281, 295.2378, 35.4688, 264.4891, "Wang Cars" },
	{ 3, -2026.9164, -104.0480, 1035.1719, 1.0119, "Centro de licenças" },
	{ 10, 603.01910, -606.49470, 985.68600, 95.3052, "Farmácia 24'Horas" },
	{ 10, 1163.4124, 1355.82480, 673.38180, 2.2678, "Revendedora & Seguradora" },
	{ 1, 933.208900, 2150.40190, 1011.0234, 91.0553, "Mercado Negro" },
	{ 1, 1390.39820, -32.057100, 1000.9177, 0.00000, "Mercado 24/7" }
};

//	[ Pickup array with property id assigned via array slot ( pickupid ) ]
new propPickups[MAX_PROPERTIES] = {0};

//	[ Handles for 3D text displayed at property entrances ]
new Text3D:propTextInfo[MAX_PROPERTIES];

// 	[ Mass array of all the properties and info about them ]
/*
		eIcon,
		eType,
		eMapIcon,
		Float:eEntX,
		Float:eEntY,
		Float:eEntZ,
		Float:eEntA,
		eUniqIntId,
		ePname[64]
	*/
new properties[84][E_PROPERTIES] = {
	{ 19592, 2, 17, 1315.389648, -898.885803, 39.578125, 352.437835, 52 }, // 24/7 LS (damo)
	{ 1275, 2, 23, -2552.3452, 55.2264, 16.4219, 4.3920, 149 }, // Mercado Negro SF
	{ 19811, 2, 10, 1199.693847, -919.824829, 43.107589, 359.216644, 47 }, // burger shot LS (damo)
	{ 2768, 2, 14, 927.423706, -1352.795166, 13.376624, 264.936157, 130 }, // Cluckin Bell South LS Beach (Kye)
	{ 2768, 2, 14, 2421.620361, -1509.163085, 23.992208, 88.295097, 130 }, // Cluckin Bell South LS Grove (Kye)
	{ 1272, 2, 49, 2309.676757, -1644.051757, 14.827047, 333.614624, 139 }, // Ten Green Bottles Bar LS (Kye)
	{ 1272, 2, 21, 2421.507324, -1219.351928, 25.554723, 0.673891, 40 }, // pig pen strip club edit interior pos ( damo )
	{ 1272, 2, 48, 1835.677490, -1682.488403, 13.379734, 274.638153, 64 }, // Alahambra (Kye)
	{ 1272, 2, 36, 1412.650300, -1700.466600, 13.539500, 48.6386, 146 }, // Driving school (dimmy)
	{ 1272, 2, 43, 2020.498535, 1007.743408, 10.820312, 91.738945, 41 }, // Four dragons LV (Kye)
	{ 1272, 2, 44, 2195.840087, 1677.150512, 12.367187, 270.124633, 48 }, // Caligula's Casino LV (Kye)
	{ 1582, 2, 29, 2083.363037, 2223.861572, 11.023437, 4.465465, 22 }, // LV Pizza (Damian)
	{ 19811, 2, 10, 1872.878784, 2071.857666, 11.062500, 54.375713, 47 }, // Burgershot LV (Kye)
	{ 11738, 2, 22, 1126.284400, -1370.18620, 13.984400, 0.675700, 147 }, // Farmácia (dimmy)
	{ 11738, 2, 22, 1582.183100, -1169.91090, 24.078100, 183.7451, 147 }, // Farmacia2 (dimmy)
	{ 11738, 2, 22, 2081.234400, -1205.17810, 23.933400, 268.7167, 147 }, // farmacia3 (dimmy)
	{ 11738, 2, 22, 951.313000, -1278.450000, 15.111500, 270.4691, 147 }, // farmacia4 (dimmy)
	{ 1272, 2, 38, 2131.79350, -1150.88540, 24.108000, 185.72110, 148 }, // Revendedora & Seguradora (dimmy)
	{ 1272, 2, 38, 595.32630, -1250.12990, 18.271900, 214.219900, 148 }, // Revendedora & Seguradora (dimmy)
	{ 1272, 2, 38, -1784.9319, 575.864200, 35.164100, 301.77990, 148 }, // Revendedora & Seguradora (dimmy)
	{ 1254, 2, 23, 1607.60360, -1560.16580, 14.178900, 191.9844, 149 }, // Mercado negro (dimmy)
	{ 1274, 2, 56, 1398.70560, -1881.44900, 13.546900, 179.80290, 4 }, // Lotérica (dimmy)
	{ 1274, 2, 56, 1015.42790, -1537.26140, 13.525500, 90.579300, 4 }, // Lotérica (dimmy)
	{ 1272, 2, 36, 2507.153076, 2121.128173, 10.840013, 170.379791, 40 }, // Strip club central LV (Kye)
	{ 2768, 2, 14, 2637.511718, 1671.698120, 11.023437, 272.170532, 130 }, // Cluckin Bell East LV (kye)
	{ 2768, 2, 14, -2672.043945, 258.937194, 4.632812, 189.680572, 130 }, // Cluckin Bell mid SF beach (Kye)
	{ 2768, 2, 14, -1816.763427, 617.589660, 35.171875, 353.020690, 130 }, // Cluckin Bell SF (dugi)
	{ 1582, 2, 29, -1721.932250, 1359.860717, 7.185316, 268.479644, 22 }, // Pizza stack shore SF (kye)
	{ 2768, 2, 14, -2154.623535, -2460.848876, 30.851562, 48.116821, 130 }, // Cluckin Bell Angel Pine (dugi)
	{ 2768, 2, 14, 172.669723, 1176.409179, 14.764543, 328.506103, 130 }, // Cluckin Bell Fort Carson (dugi)
	{ 1582, 2, 29, 1367.071044, 248.593109, 19.566932, 245.808715, 22 }, // Pizza Montgomery (dugi)
	{ 19811, 2, 10, 810.959289, -1616.228393, 13.546875, 84.417098, 47 }, // Burger Shot LS
	{ 2768, 2, 14, 2846.259521, 2414.882568, 11.068956, 43.913692, 130 }, // Cluckin Bell LV (dugi)
	{ 1582, 2, 29, 2756.376708, 2476.747314, 11.062500, 319.626251, 22 }, // Pizza LV (dugi)
	{ 19592, 2, 17, -2442.768310, 754.327941, 35.171875, 0.069979, 52 }, // 24/7 SF (dugi)
	{ 1272, 2, 54, 2229.121100, -1722.06200, 13.562500, 315.1371, 1 }, // Ginásio LS (dimmy)
	{ 19811, 2, 10, 1158.547973, 2072.261474, 11.062500, 89.872474, 47 }, // Burger Shot LV (dugi)
	{ 19811, 2, 10, 2170.229003, 2795.691894, 10.820312, 85.485740, 47 }, // Burger Shot LV (dugi)
	{ 1582, 2, 29, 2330.606201, 2532.529785, 10.820312, 359.255584, 22 }, // Pizza LV (dugi)
	{ 1275, 2, 45, 2802.501220, 2430.280273, 11.062500, 318.185119, 25 }, // Victim LV (dugi)
	{ 1275, 2, 45, 2779.359375, 2453.658691, 11.062500, 314.425018, 33 }, // Suburban LV (dugi)
	{ 2768, 2, 14, 2102.554687, 2228.759033, 11.023437, 97.608024, 130 }, // Cluckin Bell LV (dugi)
	{ 1275, 2, 45, 2102.572265, 2257.474365, 11.023437, 93.221321, 80 }, // Binco LV (dugi)
	{ 19592, 2, 17, 2097.767578, 2223.978515, 11.023437, 3.920505, 52 }, // 24/7 LV (dugi)
	{ 1275, 2, 45, 1097.7123, -1370.0302, 13.9844, 0.5538, 53 }, // Zip LS (dimmy)
	{ 19592, 2, 17, 2194.563720, 1991.017944, 12.296875, 270.419586, 52 }, // 24/7 LV (dugi)
	{ 19592, 2, 17, 2452.393310, 2064.608154, 10.820312, 0.861728, 52 }, // 24/7 LV (dugi)
	{ 1275, 2, 45, -2492.282470, -29.028230, 25.765625, 267.565582, 33 }, // SubUrban SF (dugi)
	{ 1275, 2, 45, -1883.063476, 865.582031, 35.172843, 321.459350, 53 }, // Zip SF (dugi)
	{ 1275, 2, 45, -1693.950805, 950.370056, 24.890625, 317.699249, 25 }, // Victim SF (dugi)
	{ 1275, 2, 45, -2374.904052, 910.287475, 45.445312, 260.865631, 80 }, // Binco SF (dugi)
	{ 1582, 2, 29, 2104.495605, -1806.595214, 13.554687, 271.855743, 22 }, // Pizza LS (dugi)
	{ 1275, 2, 45, 453.227142, -1478.244018, 30.812078, 289.547210, 61 }, // Didier Sachs LS (dugi)
	{ 356, 2, 6, 1368.388671, -1279.795898, 13.546875, 273.337646, 32 }, // ammunation LS (damo)
	{ 2768, 2, 14, 2397.941406, -1898.133666, 13.546875, 182.602310, 130 }, // cluckin' bell
	{ 19592, 2, 17, -1561.987426, -2733.466552, 48.743457, 55.909801, 52 }, // 24/7 dugi
	{ 1272, 2, 53, 2781.348144, -1814.231079, 11.843750, 218.271469, 39 }, // Los Santos Stadium
	{ 356, 2, 6, -2093.248046, -2464.454589, 30.625000, 141.188079, 32 }, // ammunation dugi
	{ 19592, 2, 17, 1832.444946, -1842.604736, 13.578125, 271.837738, 52 }, // 24/7
	{ 356, 2, 6, 2158.767333, 943.083129, 10.820312, 108.761138, 32 }, // Ammunation LV G-sTyLeZzZ
	{ 1582, 2, 29, 2638.084228, 1849.809326, 11.023437, 272.709197, 22 }, // Pizza Stack dugi
	{ 1272, 2, 18, 2847.6321, 983.5542, 10.7500, 90.0000, 71 }, // Fábrica de Materiais
	{ 19592, 2, 17, 1937.173583, 2307.304931, 10.820312, 5.076000, 52 }, // 24/7 G-sTyLeZzZ
	{ 356, 2, 6, -1508.861572, 2609.611572, 55.835937, 1.487694, 32 }, // ammunation dugi
	{ 19592, 2, 17, 2247.947509, 2397.572998, 10.820312, 3.952800, 52 }, // 24/7 G-sTyLeZzZ(kenny01)
	{ 356, 2, 6, 2538.900878, 2084.042968, 10.820312, 268.005279, 32 }, // ammunation dugi
	{ 1272, 2, 49, -2551.652832, 193.638565, 6.190325, 284.976623, 139 }, // bar dugi
	{ 1275, 2, 45, 1070.058349, -1221.396118, 16.890625, 265.590789, 16 }, // Clothing Shop in Market (KingJ)
	{ 1275, 2, 45, 499.961059, -1359.307128, 16.257724, 164.398086, 16 }, // Pro-Laps in Rodeo (kenny01)
	{ 1275, 2, 45, 460.946624, -1500.953002, 31.058170, 280.210174, 25 }, // Victim in Rodeo (kenny01)
	{ 1275, 2, 45, 2244.590820, -1664.513061, 15.476562, 167.776901, 80 }, // Binco in Ganton (kenny01)
	{ 1272, 2, 49, 2354.133056, -1512.185668, 24.000000, 320.673034, 139 }, // Mexican Inn (kenny01)
	{ 356, 2, 6, -2626.432128, 209.431488, 4.601754, 0.752900, 32 }, // Ammu SF Kye
	{ 356, 2, 6, 2400.531738, -1980.582885, 13.546875, 175.231292, 32 }, // ammu south LS Kye
	{ 356, 2, 6, 778.146789, 1871.564575, 4.907619, 90.455406, 32 }, // ammu bone Kye
	{ 356, 2, 6, -314.774688, 829.901977, 14.242187, 95.132049, 32 }, // ammu bone Kye
	{ 356, 2, 6, 241.099655, -178.363815, 1.578125, 265.502624, 32 }, // Ammu blueberry Kye
	{ 356, 2, 6, 2334.055664, 61.541301, 26.484687, 177.983642, 32 }, // Ammu Kye
	{ 19592, 2, 17, 1352.342800, -1759.0037, 13.507800, 182.619000, 150 }, // 24/7 (dimmy)
	{ 19592, 2, 17, 1928.973300, -1776.2805, 13.546900, 90.9158, 52 }, // 24/7 (dimmy)
	{ 19592, 2, 17, -78.679400, -1169.80760, 2.1432000, 246.6672, 52 }, // 24/7 (dimmy)
	{ 1274, 3, 52, 1460.6580,-1135.4980,24.0016, 42.7366, 84 }, // Main LS Bank (Kye)
	{ 1274, 3, 52, 2363.286376, 2377.655029, 10.820312, 256.108428, 84 }, // LV Bank (Kye)
	{ 1274, 3, 52, -1581.240600, 903.586364, 7.695312, 177.860778, 84 } // SF bank (Kye)
	//{ 1274, 3, 1442.3978, -1468.2538, 13.5295, 80.0672, 150 } // Estacionamento dos presentes
};

//	[ The last pickup the player went through so they can do /enter command ]
new lastPickup[MAX_PLAYERS] = {999};

stock Propertie_SetLastPickup(playerid, pickup)
	lastPickup[playerid] = pickup;

//  [ Localizar empresa ]
new SelectEmpresa[MAX_PLAYERS][150];

//	[Propriedade atual Interior exclusivo em que o jogador está .. o padrão é -1 quando não estiver em nenhuma propriedade]
new currentInt[MAX_PLAYERS] = -1;

stock GetPlayerCurrentInt(playerid) {
	return currentInt[playerid];
}

stock SetPlayerCurrentInt(playerid, currentid) {
	currentInt[playerid] = currentid;
}

stock GetPropertyName(propid) {
	new name[64];
	format(name, 64, PropInfo[propid][ePname]);
	return name;
}

stock Float:GetPropEntranceX(propid) {
	return properties[propid][eEntX];
}

stock Float:GetPropEntranceY(propid) {
	return properties[propid][eEntY];
}

stock Float:GetPropEntranceZ(propid) {
	return properties[propid][eEntZ];
}

stock Float:GetPropertyEntrance(id, &Float:x, &Float:y, &Float:z)
{
	if (id > MAX_PROPERTIES) return 0.0;
	x = properties[id][eEntX];
	y = properties[id][eEntY];
	z = properties[id][eEntZ];
	return properties[id][eEntA];
}

stock Float:GetInteriorExit(id, &Float:x, &Float:y, &Float:z)
{
	if( id > MAX_INTERIORS ) return 0.0;
	else {
	    x = interiorInfo[id][inExit_X];
	    y = interiorInfo[id][inExit_Y];
	    z = interiorInfo[id][inExit_Z];
		return interiorInfo[id][inExitA];
	}
}

// Obtém informações de saída interna do ID interno da uniq. Retorna InteriorId ou -1 se interior não existir
stock GetInteriorExitInfo(uniqIntId, &Float:Exit_X, &Float:Exit_Y, &Float:Exit_Z, &Float:exitA)
{
	if (uniqIntId < MAX_INTERIORS)
	{
	    Exit_X = interiorInfo[uniqIntId][inExit_X];
	    Exit_Y = interiorInfo[uniqIntId][inExit_Y];
	    Exit_Z = interiorInfo[uniqIntId][inExit_Z];
	    exitA = interiorInfo[uniqIntId][inExitA];
		return interiorInfo[uniqIntId][inIntID];
	}
	return -1;
}


stock GetInteriorIntID(id)
{ // Gets the interior id of a uniq Interior Id :S
	if(id > MAX_INTERIORS) return -1;
	else return interiorInfo[id][inIntID];
}

stock GetInteriorName( id )
{
	new tmp[64];
	if( id > MAX_PROPERTIES ) return tmp;

	else
	{
  		format( tmp, 64, "%s", interiorInfo[id][inName] );
		return tmp;
	}
}

stock Float:GetPropertyExit(id, &Float:x, &Float:y, &Float:z)
{
	if (id > MAX_PROPERTIES) return 0.0;
	return GetInteriorExit(properties[id][eUniqIntId], x, y, z);
}

stock GetPropertyInteriorFileId(id)
{
	if (id > MAX_PROPERTIES) return false;
	else return properties[id][eUniqIntId];
}

stock GetPropertyInteriorId(id)
{
	if (id > MAX_PROPERTIES) return false;
	else return GetInteriorIntID(properties[id][eUniqIntId]);
}

stock GetPropertyPrice(id)
{
	if (id > MAX_PROPERTIES) return -1;
	else return PropInfo[id][ePrice];
}

stock GetPropertyOwner(id)
{
	new tmp[MAX_PLAYER_NAME];
	if (id > MAX_PROPERTIES) return tmp;
	else
	{
  		format(tmp, MAX_PLAYER_NAME, "%s", PropInfo[id][eOwner]);
		return tmp;
	}
}

stock SetPropertyOwner(id, playerid) {
	if(playerid == -1) {
		PropInfo[id][eOwnerID] = -1;
		format(PropInfo[id][eOwner], MAX_PLAYER_NAME, "Ninguém");
	}
	else {
		PropInfo[id][eOwnerID] = PlayerInfo[playerid][pID];
		format(PropInfo[id][eOwner], MAX_PLAYER_NAME, PlayerName[playerid]);
	}
}

stock IsPlayerOwnerPropertie(playerid, id)
{
	if (id < 0) return false;

    if (id > MAX_PROPERTIES) return false;

    if (PropInfo[id][eOwnerID] == PlayerInfo[playerid][pID]) 
        return true;

    return false;
}

stock Bank_OpenVault(playerid)
{
	if (IsPlayerInRangeOfPoint(playerid, 3.0, 1447.1038, -1123.0455, 23.9590))
	{
		if (PropInfo[81][eOwnerID] != Player_GetAccountID(playerid))
			return SendClientMessage(playerid, -1, "Você não é o proprietário do banco.");

		if(vaultState)
		{
			//Close Vault
			vaultState = false;
			MoveDynamicObject(vaultDoor, 1444.822631, -1124.319946, 24.488027-0.0001, 0.0001, 0.000000, 0.000000, 579.799987);
		}
		else
		{
			//Open Vault
			vaultState = true;
			MoveDynamicObject(vaultDoor, 1444.822631, -1124.319946, 24.488027+0.0001, 0.0001, 0.000000, 0.000000, 127.799964);
		}
	}
	return 1;
}

stock GetPlayerCofreProp(playerid) 
{
	if (IsPlayerInRangeOfPoint(playerid, 3.0, 1442.4266, -1119.4700, 24.9146))
		return 81;

	if (IsPlayerInRangeOfPoint(playerid, 3.0, 2148.2170,1648.1301,835.3793)) {
	    return GetPVarInt(playerid, "propId");
	}
	return -1;
}

stock IsPropertyOwner( id ) {
    if( id > MAX_PROPERTIES ) return 1;

    if (PropInfo[id][eOwnerID] == -1) {
        return 0;
    }
    return 1;
}