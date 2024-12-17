

#include    < YSI_Coding\y_hooks >

#define   		MAX_PLAYER_CARROS  			(5)
#define         VEHICLES_IMPOSTOS           200

enum ConceEnum
{
    ConceModel,
	Float:ConceX,
	Float:ConceY,
	Float:ConceZ,
	Float:ConceA,
	ConceValue,
	ConceNivel,
	ConceID,
	Text3D:ConceText,
};

enum pTuneEnum {
	tune_String[128]
}

new SelectCarros[MAX_PLAYERS][MAX_PLAYER_CARROS];

stock const CarrosConce[72][ConceEnum] = {

/* -----------------------------------------------------------------------------------
	Posicoes X,    Y,     Z                      	Preço		Nivel
------------------------------------------------------------------------------------*/
//		Veículos antigos

{458, 2100.7659, 1398.2219, 10.7149, 179.9433,      13800,			1},     // Solair
{404, 2103.9221, 1398.0724, 10.5528, 179.7357,		14000,			1}, 	// Perrenial
{542, 2107.1726, 1397.9839, 10.5647, 180.7978, 		14500,			1},		// Clover
{475, 2110.4480, 1398.3063, 10.6852, 179.2074,		15000,			1}, 	// Sabre
{549, 2113.3955, 1398.2926, 10.5164, 179.8240, 		16000,			2},		// Tampa
{419, 2116.7278, 1397.9645, 10.6154, 177.6052, 		16000,			2},		// Esperanto
{518, 2119.8831, 1398.2247, 10.5184, 178.4085, 		16000,   	 	2},		// Buccaneer
{600, 2123.1663, 1398.0103, 10.5555, 178.7384, 		16200,			2},     // Picador
{546, 2100.7769, 1409.0353, 10.5834, 359.8293, 		17000,   	 	2},     // Intruder
{551, 2104.0432, 1409.1400, 10.5572, 358.7938, 		17000,   	 	2},     // Merit
{467, 2107.1790, 1409.0186, 10.5466, 357.3871, 		18000,    		3},     // Glendale
{466, 2110.4038, 1409.5569, 10.6552, 358.2449, 		18000,			3},     // Oceanic
{439, 2113.6177, 1408.7955, 10.5555, 359.6653, 		19000,			3},     // Stallion
{555, 2116.7542, 1408.6930, 10.8079, 359.4096, 		19500,			3},     // Windsor

//		Veículos Lowriders

{575, 2793.1421, -2015.4592, 13.1599, 90.6564, 		40000,		4},     // Broadway
{533, 2792.9849, -2023.2671, 13.2884, 89.3896, 		50000,		6},     // Feltzer
{567, 2793.1990, -2027.8062, 13.4366, 90.1464, 		42000,		4},     // Savanna
{576, 2784.0320, -2025.8546, 13.1711, 359.5783, 	42000,		4},     // Tornado
{412, 2778.7756, -2025.4181, 13.3931, 358.5348, 	42000,		4},     // Voodoo
{535, 2792.8066, -2010.8942, 13.2929, 89.8468, 		45000,		4},     // Slamvan

//		Veículos Comuns

{496, 563.4955, -1291.7169, 17.3412, 0.0557, 		42000,   		5},     // Blista Compact
{540, 559.5847, -1291.5670, 17.0282, 359.4653, 		42300,    	5},     // Vincent
{445, 555.2963, -1291.2805, 17.1240, 0.0565, 		42800,   		5},     // Admiral
{436, 551.3427, -1291.7578, 16.8735, 2.5284,        43000,   		5},     // Previon
{426, 547.1512, -1291.1670, 17.0435, 0.4396,        43200,   		5},     // Premier
{527, 542.6901, -1291.0326, 17.1245, 359.4103, 		44000,    	5},     // Cadrona
{526, 538.3904, -1291.3256, 16.9860, 358.0856, 		45000,   		5},     // Fortune
{550, 534.3075, -1291.4918, 16.9704, 1.1371, 		46000,    	5},     // Sunrise
{422, 529.9590, -1291.3453, 17.1182, 359.8897, 		50000,    	6},     // Bobcat
{543, 525.8326, -1291.2067, 17.1212, 359.8129, 		55000,    	6},     // Sadler
{554, 521.3904, -1291.3840, 17.0456, 359.0502, 		57000,    	6},     // Yosemite

//		Veículos Raros

{477, -1944.5189, 271.8423, 35.2197, 91.4775, 		1500000,   	8},     // ZR-350
{506, -1944.2797, 267.6606, 35.1830, 89.9079, 		1600000, 	 	9},     // Super GT
{415, -1944.5481, 262.6183, 35.8406, 90.0162, 		1800000, 	 	9},     // Cheetah
{587, -1949.0083, 255.7704, 35.3655, 1.0391, 		1500000,		8},     // Euros
{480, -1953.2994, 255.2253, 35.4306, 0.0396, 		1700000,		8},     // Comet
{411, -1952.9633, 302.3289, 35.3006, 90.0861,		3500000,		10},    // Infernus
{451, -1952.7002, 298.1731, 35.1722, 90.0970, 		3000000,		10},    // Turismo
{541, -1952.6168, 294.1173, 35.2432, 87.7470, 		2800000,		10},    // Bullet
{560, -1952.5569, 300.7938, 40.7519, 90.0058, 		2300000,		8},     // Sultan
{559, -1952.4966, 296.9530, 40.7046, 90.0822, 		2400000,		8},     // Jester
{562, -1952.5229, 292.6486, 40.7049, 90.0415, 		2500000,  	8},     // Elegy
{429, -1962.1078, 255.7819, 35.1536, 359.3818, 		900000,		8},		// Banshee
{558, -1944.8705, 271.7657, 40.8223, 89.8842, 		1550000,		8},     // Uranus
{602, -1957.8320, 255.8909, 35.2748, 359.6870,		1500000,		8},		// Alpha
{561, -1945.3975, 266.9124, 40.8052, 89.8527, 		1200000,		8},     // Stratum
{565, -1944.7286, 261.8693, 40.7528, 89.8919, 		1550000,		8},     // Flash
{500, -1951.3040, 255.6534, 41.4028, 357.1226, 		350000,		9},		// Huntley
{495, -1955.6171, 256.4042, 40.9426, 359.9280, 		2200000,		9},		// Sandking

//		Motos

{461, 2052.5403, -1903.1292, 13.1311, 180.1508,		35000,		7},     // PCJ-600
{462, 2055.9663, -1902.9272, 13.1438, 180.2716, 	5000,		1},     // Faggio
{463, 2059.3679, -1903.0912, 13.0856, 179.2848, 	60000,		4},     // Freeway
{468, 2062.4329, -1902.8633, 13.2135, 178.2903, 	80000,		5},     // Sanchez
{471, 2065.6621, -1902.6117, 13.0275, 178.8957, 	50000,		2},     // Quadbike
{586, 2068.8547, -1902.8824, 13.0659, 181.7116, 	55000,		2},     // Wayfarer
{581, 2068.5535, -1920.4275, 13.1407, 358.7596, 	150000,		7},     // BF-400
{521, 2065.3369, -1920.4176, 13.1157, 358.3766, 	350000,		7},     // FCR-900
{522, 2062.2524, -1920.5125, 13.1150, 358.8589, 	750000,		8},     // NRG-500

//		Helicopteros

{487, 1961.1685, -2649.6619, 13.7236, 177.3681, 	30000000,		15},	// Maverick
{469, 1951.9694, -2650.5269, 13.5577, 176.5612, 	20000000,		20},	// Sparrow
{447, 1943.5647, -2650.9128, 13.5585, 178.9068, 	60000000,		25},	// Leviathan

//		Barcos

{454, 946.4114, -1933.0040, 0.1824, 98.4674, 		6000000, 		7},
{453, 952.7479, -1945.1925, -0.2818, 95.8043, 		3000000, 		7},
{446, 955.2260, -1956.3900, -0.4926, 88.6910, 		3000000, 		7},
{452, 960.5487, -1966.9545, -0.5179, 90.5287, 		800000, 		7},

//		Bicicletas

{481, 2283.2004, -2025.0323, 13.0613, 87.7247, 		1500,     	1},
{509, 2283.2266, -2027.9891, 13.0588, 89.8092, 		1800,     	1},
{510, 2283.1831, -2031.1410, 13.1544, 91.5225, 		1300,    	1},

//		Aviões

{519, 1907.7467, -2263.4807, 14.4664, 267.8832,		50000000,		40},    // Shamal
{593, 1905.4946, -2283.1785, 13.9764, 266.9393,		20000000,		30},    // Dodo
{512, 1905.2129, -2296.5698, 14.0808, 264.9257,		12000000,		30},	// Cropduster
{511, 1904.9795, -2314.7234, 14.9199, 267.3584,		12000000,		35}    // Beagle
// Caminhão
//{578, 2523.1475, -2074.1450, 14.1714, 179.5641,		650000,		15}
};

stock loadCarrosConce()
{
	for(new x; x != sizeof CarrosConce; x++)
	{
	    CarrosConce[x][ConceID] = AddStaticVehicleEx(CarrosConce[x][ConceModel], CarrosConce[x][ConceX], CarrosConce[x][ConceY], CarrosConce[x][ConceZ], CarrosConce[x][ConceA], -1, -1, -1);

		CarrosConce[x][ConceModel] = CarrosConce[x][ConceModel];
		CarrosConce[x][ConceX] = CarrosConce[x][ConceX];
		CarrosConce[x][ConceY] = CarrosConce[x][ConceY];
		CarrosConce[x][ConceZ] = CarrosConce[x][ConceZ];
		CarrosConce[x][ConceA] = CarrosConce[x][ConceA];
		CarrosConce[x][ConceValue]  = CarrosConce[x][ConceValue];
		CarrosConce[x][ConceNivel]  = CarrosConce[x][ConceNivel];

		new vehicleid = CarrosConce[x][ConceID];
		VehicleInfo[vehicleid][vhType] = VH_TYPE_SALE;
		VehicleInfo[vehicleid][vhInfoID] = 0;

		new string_conce[148];
		new vehicle_name[30];
		GetModelStaticNameFromId(GetVehicleModel(CarrosConce[x][ConceID]), vehicle_name);

		format(string_conce, sizeof (string_conce),
		"{00FFFF}%s\n\
		{FFFFFF}Custo: {00AA00}$%s\n\
		{FFFFFF}Nível necessário: {00AA00}%d\n\n\
		{FFFFFF}Use {00FFFF}/veiculo comprar {FFFFFF}para comprar", vehicle_name, getFormatText(CarrosConce[x][ConceValue]), CarrosConce[x][ConceNivel]);
		CarrosConce[x][ConceText] = CreateDynamic3DTextLabel(string_conce, 0xFFFFFFFF, 0.0, 0.0, 0.8, 10.0, INVALID_PLAYER_ID, CarrosConce[x][ConceID], 0, 0, 0, -1, 10.0);
	}
	return sizeof CarrosConce;
}

stock GetVehicleModelLevel(modelid) {

	for(new x; x != sizeof CarrosConce; x++){

		if (CarrosConce[x][ConceModel] == modelid) {
		    return CarrosConce[x][ConceNivel];
		}
	}
	return 5;
}

CALLBACK:restoreCar(carid)
{
	CarrosConce[carid][ConceID] = CreateVehicle(CarrosConce[carid][ConceModel], CarrosConce[carid][ConceX], CarrosConce[carid][ConceY], CarrosConce[carid][ConceZ], CarrosConce[carid][ConceA], -1, -1, -1);

	new vehicleid = CarrosConce[carid][ConceID];
	VehicleInfo[vehicleid][vhType] = VH_TYPE_SALE;
	VehicleInfo[vehicleid][vhInfoID] = 0;

	new string_conce[148];
	new vehicle_name[30];
	GetModelStaticNameFromId(GetVehicleModel(CarrosConce[carid][ConceID]), vehicle_name);

	format(string_conce, sizeof (string_conce),
	"{00FFFF}%s\n\
	{FFFFFF}Custo: {00AA00}$%s\n\
	{FFFFFF}Nível necessário: {00AA00}%d\n\n\
	{FFFFFF}Use {00FFFF}/veiculo comprar {FFFFFF}para comprar", vehicle_name, getFormatText(CarrosConce[carid][ConceValue]), CarrosConce[carid][ConceNivel]);
	CarrosConce[carid][ConceText] = CreateDynamic3DTextLabel(string_conce, 0xFFFFFFFF, 0.0, 0.0, 0.8, 10.0, INVALID_PLAYER_ID, CarrosConce[carid][ConceID], 0, 0, 0, -1, 10.0);

	if (IsVehicleLocked(CarrosConce[carid][ConceID]))
		UnlockVehicleDoors(CarrosConce[carid][ConceID]);
}

stock checkCarsPositions() {

	for(new x; x != sizeof CarrosConce; x++) {
		if (CarrosConce[x][ConceID] != INVALID_VEHICLE_ID && GetVehicleDistanceFromPoint(CarrosConce[x][ConceID], CarrosConce[x][ConceX], CarrosConce[x][ConceY], CarrosConce[x][ConceZ]) > 3.0)  {
  			SetVehicleToRespawn(CarrosConce[x][ConceID]);
		}
	}
}
/*
// Salvar carros conce
stock registerPlayerConce(playerid) {
	new query[75];
	mysql_format(MySQL_Handle, query, sizeof (query), "INSERT INTO player (`nome`) VALUE ('%s')", PlayerName[playerid]);
	mysql_tquery(MySQL_Handle, query);
}

stock registerNickConce(playerid, nick[]) {
	#pragma unused playerid
	
	new query[75];
	mysql_format(MySQL_Handle, query, sizeof (query), "INSERT INTO player (`nome`) VALUE ('%s')", nick);
	mysql_tquery(MySQL_Handle, query);
}
*/