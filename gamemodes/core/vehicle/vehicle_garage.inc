#if defined _inc_vehicle_garage_system
	#endinput
#endif
#define _inc_vehicle_garage_system true

#define MAX_VEHICLES_GARAGE         2

#include <YSI_Coding\y_hooks>

enum GARAGE_ENUM 
{
    garageOrgID,
    Float:garagePosX,
    Float:garagePosY,
    Float:garagePosZ,
};
static const GARAGE_ORG_LOCATIONS[][GARAGE_ENUM] =
{
    // [org, x, y, z]
    {0, 1687.0225, -2262.7241, 13.4882},
    {1, 1526.3005, -1672.8358, 6.2188},
    {2, 321.6765, -1521.9979, 36.0391},
    {3, -1342.1554, 479.7415, 7.1875},
    {5, 1694.6508, -2105.2849, 13.5469},
    {7, 1486.4154, -1781.7687, 13.5400},
    {8, 2283.4663, -2358.8721, 13.5469},
    {9, 735.9317, -1352.1420, 13.5000},
    {11, 1131.0366, -2032.5271, 69.0078},
    {12, 284.7223, -1380.2494, 13.9491},
    {13, 672.4579, -1280.1206, 13.6345},
    {14, 2592.6924, -1507.7889, 15.4831},
    {15, -585.4615, -1059.1954, 23.5380},
    {16, 917.7950, -1245.6920, 15.6641},
    {17, -198.0341, -1083.0156, 24.6700},
    {18, 2814.3394, -1187.5198, 25.2505},
    {19, 1604.8344, -736.9290, 64.2054},
    {20, -319.8124, 1535.8915, 75.5625},
    {21, 1319.4996, -3031.2949, 8.1655},
    {22, 2769.4141, -1624.7522, 10.9272},
    {25, 2492.2415, 81.3627, 26.5184},
    {28, 668.3403, -473.4622, 16.3359},
    {24, 481.8570, -1527.8220, 19.7924},
    {33, 1653.6532, -1342.8861, 17.4297},
    {34, -31.4450, -294.3437, 5.4297}
};

static VehiclePlayer[MAX_PLAYERS][MAX_VEHICLES_GARAGE];
static player_world[MAX_PLAYERS];

hook OnGameModeInit()
{
    new 
        Float:x, 
        Float:y, 
        Float:z;

    for (new i = 0; i < sizeof(GARAGE_ORG_LOCATIONS); i++) {
        x = GARAGE_ORG_LOCATIONS[i][garagePosX];
        y = GARAGE_ORG_LOCATIONS[i][garagePosY];
        z = GARAGE_ORG_LOCATIONS[i][garagePosZ];

        CreateDynamicPickup(19607, 0, x, y, z - 2.1);
        CreateDynamic3DTextLabel("[GARAGEM]\n\n"C_WHITE"Pressione "C_LIGHTBLUE"Y "C_WHITE"para pegar um veiculo", COLOR_LIGHTBLUE, x, y, z, 20.0);
    }
    return 1;
}

hook OnPlayerResetVars(playerid)
{
    VehiclePlayer[playerid][0] = INVALID_VEHICLE_ID;
    VehiclePlayer[playerid][1] = INVALID_VEHICLE_ID;
}

hook OnVehicleDeath(vehicleid, killerid)
{
    for(new vehicle; vehicle != 15; vehicle++) if (CarrosAdmin[vehicle] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosConce); vehicle++) if (CarrosConce[vehicle][ConceID] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosLixeiros); vehicle++) if (CarrosLixeiros[vehicle] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosPilotos); vehicle++) if (CarrosPilotos[vehicle] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosMedicos); vehicle++) if (CarrosMedicos[vehicle] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosMecanicos); vehicle++) if (CarrosMecanicos[vehicle] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosFazendeiros); vehicle++) if (CarrosFazendeiros[vehicle] == vehicleid) return 1;

    foreach(new playerid : Player)  {
	    if (Player_Logado(playerid)) {
            if (PlayerCaminhao[playerid][caminhaoId] == vehicleid)
                return 1;
                
            foreach(new v : IterPlayerVehicles[playerid]) {
				if (vehicleid == PlayerVehicleInfo[playerid][v][pvID]) {
					return 1;
		   		}
            }
	    }
	}
    VehiclePlayer_Destroy(vehicleid);
    return 1;
}

hook OnVehicleSpawn(vehicleid)
{
    for(new vehicle; vehicle != 15; vehicle++) if (CarrosAdmin[vehicle] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosConce); vehicle++) if (CarrosConce[vehicle][ConceID] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosLixeiros); vehicle++) if (CarrosLixeiros[vehicle] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosPilotos); vehicle++) if (CarrosPilotos[vehicle] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosMedicos); vehicle++) if (CarrosMedicos[vehicle] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosMecanicos); vehicle++) if (CarrosMecanicos[vehicle] == vehicleid) return 1;
    for(new vehicle; vehicle != sizeof(CarrosFazendeiros); vehicle++) if (CarrosFazendeiros[vehicle] == vehicleid) return 1;

    foreach(new playerid : Player)
    {
	    if (Player_Logado(playerid)) {
            if (PlayerCaminhao[playerid][caminhaoId] == vehicleid)
                return 1;

            foreach(new v : IterPlayerVehicles[playerid]) {
				if (vehicleid == PlayerVehicleInfo[playerid][v][pvID]) {
					return 1;
		   		}
            }
	    }
	}
    DestroyVehicle(vehicleid);
    return 1;
}

stock IsVehicleGarageOwner(playerid, vehicleid)
{
    if (vehicleid == VehiclePlayer[playerid][0] || vehicleid == VehiclePlayer[playerid][1])
        return true;

    return false;
}

timer returnPlayerFreeze[1000](playerid)
{
    TogglePlayerControllable(playerid, true);
    SetPlayerVirtualWorld(playerid, player_world[playerid]);

    return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    if (IsVehicleOccupied(vehicleid) && !ispassenger && (!IsVehicleGarageOwner(playerid, vehicleid))) {
        ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, ""C_RED"AVISO", ""C_LIGHTWHITE"Voce nao pode "C_RED"ROUBAR "C_LIGHTWHITE"esse veiculo com o dono dentro.", "OK","");
        player_world[playerid] = GetPlayerVirtualWorld(playerid);
        SetPlayerVirtualWorld(playerid, 999999);
        TogglePlayerControllable(playerid, false);
        ClearAnimations(playerid, true);
        defer returnPlayerFreeze(playerid);
    }
    return 1;
}

hook OnPlayerModelSelection(playerid, response, listid, modelid)
{
    if (listid == VehiclesOrg_Police || listid == VehiclesOrg_Mercenario || listid == VehiclesOrg_Gangster || listid == VehiclesOrg_Civil || listid == VehiclesOrg_Terrorista || 
        listid == VehiclesOrg_Mafiosa || listid == VehiclesOrg_Governo || listid == VehiclesOrg_SanNews || listid == VehiclesOrg_Assassina) 
    {
        new org = GetPlayerOrg(playerid),
            Float:vehicleX,
            Float:vehicleY,
            Float:vehicleZ,
            Float:vehicleRot,
            color_1,
            color_2,
            bool:siren;

        if (VehiclePlayer[playerid][0] != INVALID_VEHICLE_ID && 
            VehiclePlayer[playerid][1] != INVALID_VEHICLE_ID)
            return SendClientMessage(playerid, -1, "Você já usou seus 2 veículos, você precisa aguardar que ele spawne ou exploda.");

        switch (org)
        {
            // Policiais
            case 1, 2, 11, 16, 33, 34:
            {
                if (modelid == 522 || modelid == 523) 
                {       // Motos
                    if (org == 1) {
                        vehicleX = 1578.5582, vehicleY = -1711.2583, vehicleZ = 5.4584, vehicleRot = 1.3252, color_1 = 2, color_2 = 1;
                    } else if (org == 2) {
                        vehicleX = 303.7064, vehicleY = -1498.0476, vehicleZ = 24.1727, vehicleRot = 234.1292, color_1 = 251, color_2 = 251;
                    } else if (org == 11) {
                        vehicleX = 1245.7728, vehicleY = -2018.7922, vehicleZ = 59.4001, vehicleRot = 270.7115, color_1 = 127, color_2 = 194;
                    } else if (org == 33) {
                        vehicleX = 1657.1812, vehicleY = -1354.0870, vehicleZ = 16.8977, vehicleRot = 90.0000, color_1 = 0, color_2 = 6;
                    } else if (org == 34) {
                        vehicleX = -62.7112, vehicleY = -304.0436, vehicleZ = 5.0010, vehicleRot = 268.5619, color_1 = 0, color_2 = 1;
                    } else return 1;
                }
                else if (modelid == 490 || modelid == 427 || modelid == 601 || modelid == 560) 
                {       // Carros
                    if (org == 1) {
                        vehicleX = 1551.7961, vehicleY = -1615.2848, vehicleZ = 13.1177, vehicleRot = 0.0000, color_1 = 2, color_2 = 1;
                    } else if (org == 2) {
                        vehicleX = 300.2293, vehicleY = -1490.4607, vehicleZ = 24.7221, vehicleRot = 234.2408, color_1 = 251, color_2 = 251;
                    } else if (org == 11) {
                        vehicleX = 1276.8116, vehicleY = -2025.8763, vehicleZ = 58.6894, vehicleRot = 90.2120, color_1 = 127, color_2 = 194;
                    } else if (org == 33) {
                        vehicleX = 1628.7916, vehicleY = -1333.8092, vehicleZ = 17.3711, vehicleRot = -90.0000, color_1 = 0, color_2 = 6;
                    } else if (org == 34) {
                        vehicleX = -0.1532, vehicleY = -301.1766, vehicleZ = 5.5562, vehicleRot = 90.0865, color_1 = 0, color_2 = 1;
                    } else return 1;
                }
                else if (modelid == 497) 
                {      // Helicoptero
                    if (org == 1) {
                        vehicleX = 1561.1349, vehicleY = -1648.2125, vehicleZ = 28.5786, vehicleRot = 0.0000, color_1 = 2, color_2 = 1;
                    } else if (org == 2) {
                        vehicleX = 323.5184, vehicleY = -1501.9465, vehicleZ = 76.7161, vehicleRot = 227.5169, color_1 = 251, color_2 = 251;
                    } else if (org == 11) {
                        vehicleX = 1260.6078, vehicleY = -2008.9368, vehicleZ = 59.5798, vehicleRot = 178.8965, color_1 = 127, color_2 = 194;
                    } else if (org == 33) {
                        vehicleX = 1677.6902, vehicleY = -1343.8157, vehicleZ = 158.5378, vehicleRot = 0.0000, color_1 = 0, color_2 = 6;
                    } else if (org == 34) {
                        vehicleX = 3.9392, vehicleY = -247.9610, vehicleZ = 5.5398, vehicleRot = 0.0000, color_1 = -1, color_2 = -1;
                    } else return 1;
                }
                siren = true;
            }
            case 7:
            {
                if (modelid == 560 || modelid == 411 || modelid == 490 || modelid == 409) {
                    vehicleX = 1508.7583, vehicleY = -1745.6870, vehicleZ = 13.2450, vehicleRot = 178.7048, color_1 = 101, color_2 = 101;
                } 
                else if (modelid == 522) {
                    vehicleX = 1465.3228, vehicleY = -1765.2928, vehicleZ = 13.1086, vehicleRot = 357.9369, color_1 = 101, color_2 = 101;
                } 
                else if (modelid == 487) {
                    vehicleX = 1439.4299, vehicleY = -1756.5989, vehicleZ = 13.7148, vehicleRot = 1.3926, color_1 = 101, color_2 = 101;
                }
            }
            case 9:
            {
                if (modelid == 560 || modelid == 411 || modelid == 582) {
                    vehicleX = 740.8412000, vehicleY = -1332.9830000, vehicleZ = 13.2024000, vehicleRot = 181.1289000, color_1 = 219, color_2 = 219;
                } 
                else if (modelid == 522) {
                    vehicleX = 766.2198000, vehicleY = -1331.9656000, vehicleZ = 13.0175000, vehicleRot = 178.9295000, color_1 = 219, color_2 = 15;
                } 
                else if (modelid == 488) {
                    vehicleX = 740.8604000, vehicleY = -1370.0519000, vehicleZ = 25.6641000, vehicleRot = 179.9989000, color_1 = 219, color_2 = 15;
                }
            }
            case 25, 28:
            {
                if (modelid == 522 || modelid == 586) 
                {
                    if (org == 25) 
                    {
                        vehicleX = 2477.1587, vehicleY = 85.6747, vehicleZ = 26.0499, vehicleRot = 180.0000, color_1 = 0, color_2 = 0;
                    } 
                    else if (org == 28) 
                    {
                        vehicleX = 709.7986000, vehicleY = -453.1188000, vehicleZ = 15.7980000, vehicleRot = 90.2595000, color_1 = 230, color_2 = 230;
                    } else return 1;
                } 
                else if (modelid == 560 || modelid == 459 || modelid == 579 || modelid == 422) 
                {
                    if (org == 25) 
                    {
                        vehicleX = 2488.4207, vehicleY = 63.1801, vehicleZ = 26.0614, vehicleRot = 0.0000, color_1 = 0, color_2 = 0;
                    } 
                    else if (org == 28) 
                    {
                        vehicleX = 695.3759000, vehicleY = -463.9583000, vehicleZ = 16.0013000, vehicleRot = 270.1659000, color_1 = 230, color_2 = 230;
                    } else return 1;
                } 
                else if (modelid == 487) 
                {
                    if (org == 25) 
                    {
                        vehicleX = 2496.6567, vehicleY = 63.1801, vehicleZ = 26.0614, vehicleRot = 0.0000, color_1 = 0, color_2 = 0;
                    } 
                    else if (org == 28) 
                    {
                        vehicleX = 684.8444, vehicleY = -462.4325, vehicleZ = 22.7470, vehicleRot = 180.4255, color_1 = 230, color_2 = 230;
                    } else return 1;
                }
            }
            case 5, 14, 17, 18, 19, 21:
            {
                if (modelid == 560 || modelid == 411 || modelid == 522) 
                {
                    // Veículos específicos para modelid 560 ou 411 (Carros)
                    if (org == 5) 
                    {
                        vehicleX = 1679.2, vehicleY = -2118.5, vehicleZ = 13.4, vehicleRot = 292, color_1 = 79, color_2 = 79;
                    } 
                    else if (org == 14) 
                    {
                        vehicleX = 2596.1428, vehicleY = -1535.7484, vehicleZ = 12.2787, vehicleRot = 162.9143, color_1 = 128, color_2 = 128;
                    } 
                    else if (org == 17) 
                    {
                        vehicleX = -192.2977, vehicleY = -1150.8102, vehicleZ = 5.4370, vehicleRot = 299.8364, color_1 = 222, color_2 = 222;
                    } 
                    else if (org == 18) 
                    {
                        vehicleX = 2820.5835, vehicleY = -1178.6016, vehicleZ = 24.8120, vehicleRot = 184.8555, color_1 = 6, color_2 = 6;
                    } 
                    else if (org == 19) 
                    {
                        vehicleX = 1610.7739, vehicleY = -747.3593, vehicleZ = 62.6594, vehicleRot = 249.2691, color_1 = 3, color_2 = 3;
                    } 
                    else if (org == 21) 
                    {
                        vehicleX = 1324.3918, vehicleY = -3011.6992, vehicleZ = 7.9161, vehicleRot = 346.3861, color_1 = 191, color_2 = 191;
                    }
                } 
                else if (modelid == 487) 
                {
                    // Veículos específicos para modelid 487 (Outro tipo)
                    if (org == 5) 
                    {
                        vehicleX = 1671.3755, vehicleY = -2146.7307, vehicleZ = 13.7032, vehicleRot = 265.5884, color_1 = 79, color_2 = 79;
                    } 
                    else if (org == 14)
                    {
                        vehicleX = 2614.9709, vehicleY = -1524.2666, vehicleZ = 20.7364, vehicleRot = 86.6403, color_1 = 128, color_2 = 128;
                    } 
                    else if (org == 17) 
                    {
                        vehicleX = -209.6336, vehicleY = -1057.9830, vehicleZ = 35.1265, vehicleRot = 133.7277, color_1 = 222, color_2 = 222;
                    } 
                    else if (org == 18) 
                    {
                        vehicleX = 2807.5088, vehicleY = -1183.4384, vehicleZ = 25.5562, vehicleRot = 268.6282, color_1 = 6, color_2 = 6;
                    } 
                    else if (org == 19) 
                    {
                        vehicleX = 1584.8800, vehicleY = -751.7026, vehicleZ = 67.3125, vehicleRot = 338.0001, color_1 = 3, color_2 = 3;
                    } 
                    else if (org == 21) 
                    {
                        vehicleX = 1365.0757, vehicleY = -3039.6743, vehicleZ = 8.4936, vehicleRot = 167.8909, color_1 = 191, color_2 = 191;
                    }
                }
            }
            case 8, 22:
            {
                if (modelid == 560 || modelid == 411) 
                {
                    // Veículos específicos para modelid 560 ou 411 (Carros)
                    if (org == 8) {
                        vehicleX = 2281.1001, vehicleY = -2352.7, vehicleZ = 13.4, vehicleRot = 224, color_1 = 25, color_2 = 25;
                    } 
                    else if (org == 22) {
                        vehicleX = 2769.9463, vehicleY = -1604.3276, vehicleZ = 10.6517, vehicleRot = 271.8721, color_1 = 32, color_2 = 32;
                    }
                } 
                else if (modelid == 522) 
                {
                    // Veículos específicos para modelid 522 (Motos)
                    if (org == 8) {
                        vehicleX = 2311.5, vehicleY = -2365.8, vehicleZ = 13.2, vehicleRot = 45, color_1 = 25, color_2 = 25;
                    } 
                    else if (org == 22) {
                        vehicleX = 2769.0474, vehicleY = -1619.3678, vehicleZ = 10.4875, vehicleRot = 269.5751, color_1 = 32, color_2 = 32;
                    }
                } 
                else if (modelid == 487) 
                {
                    // Veículos específicos para modelid 487 (Outro tipo)
                    if (org == 8) {
                        vehicleX = 2305.3, vehicleY = -2377.1001, vehicleZ = 13.8, vehicleRot = 0, color_1 = 25, color_2 = 25;
                    } 
                    else if (org == 22) {
                        vehicleX = 2783.3689, vehicleY = -1604.2909, vehicleZ = 11.0998, vehicleRot = 93.5053, color_1 = 32, color_2 = 32;
                    }
                }
            }
            case 12, 13, 24:
            {
                if (modelid == 560 || modelid == 411) 
                {
                    // Veículos específicos para modelid 560 ou 411 (Carros)
                    if (org == 12) 
                    {
                        vehicleX = 202.4419, vehicleY = -1442.0989, vehicleZ = 12.6431, vehicleRot = -401.5199, color_1 = 182, color_2 = 182;
                    } 
                    else if (org == 13) 
                    {
                        vehicleX = 656.5429, vehicleY = -1292.1849, vehicleZ = 13.3399, vehicleRot = 359.7515, color_1 = 4, color_2 = 4;
                    }
                    else if (org == 24) 
                    {
                        vehicleX = 482.8841, vehicleY = -1494.9019, vehicleZ = 19.7726, vehicleRot = 267.2075, color_1 = 166, color_2 = 166;
                    } 
                } 
                else if (modelid == 522) 
                {
                    // Veículos específicos para modelid 522 (Motos)
                    if (org == 12) 
                    {
                        vehicleX = 247.1503, vehicleY = -1413.5404, vehicleZ = 12.9441, vehicleRot = -327.1200, color_1 = 182, color_2 = 182;
                    } 
                    else if (org == 13) 
                    {
                        vehicleX = 656.5402, vehicleY = -1284.8342, vehicleZ = 13.1990, vehicleRot = 270.5237, color_1 = 4, color_2 = 4;
                    }
                    else if (org == 24) 
                    {
                        vehicleX = 482.8841, vehicleY = -1494.9019, vehicleZ = 19.7726, vehicleRot = 267.2075, color_1 = 166, color_2 = 166;
                    } 
                } 
                else if (modelid == 487) 
                {
                    // Veículos específicos para modelid 487 (Outro tipo)
                    if (org == 12) 
                    {
                        vehicleX = 197.5730, vehicleY = -1447.7797, vehicleZ = 12.1457, vehicleRot = -138.6600, color_1 = 182, color_2 = 182;
                    }
                    else if (org == 13) 
                    {
                        vehicleX = 656.8552, vehicleY = -1268.3540, vehicleZ = 13.8088, vehicleRot = 177.6409, color_1 = 4, color_2 = 4;
                    }
                    else if (org == 24) 
                    {
                        vehicleX = 489.6942, vehicleY = -1471.5468, vehicleZ = 19.0367, vehicleRot = 154.8111, color_1 = 166, color_2 = 166;
                    } 
                }
            }
            case 3, 15, 20:
            {
                if (org == 3) 
                {
                    // Veículos específicos para modelid 432, 470, 522, 425, 520, 560 ou 487
                    if (modelid == 432) 
                        vehicleX = -1234.7814, vehicleY = 447.8586, vehicleZ = 7.2718, vehicleRot = 90.0000, color_1 = 86, color_2 = 86;
                    else if (modelid == 470) 
                        vehicleX = -1301.8667, vehicleY = 437.5779, vehicleZ = 6.9820, vehicleRot = 0.0000, color_1 = 86, color_2 = 86;
                    else if (modelid == 522) 
                        vehicleX = -1334.4530, vehicleY = 437.7837, vehicleZ = 7.0112, vehicleRot = -90.0000, color_1 = 86, color_2 = 86;
                    else if (modelid == 425 || modelid == 433 || modelid == 487) 
                        vehicleX = -1269.9858, vehicleY = 494.6463, vehicleZ = 19.0236, vehicleRot = 293.5130, color_1 = 86, color_2 = 86;
                    else if (modelid == 520) 
                        vehicleX = -1408.3185, vehicleY = 494.1841, vehicleZ = 19.3869, vehicleRot = 323.2405, color_1 = 86, color_2 = 86;
                    else if (modelid == 560) 
                        vehicleX = -1285.8884, vehicleY = 437.8298, vehicleZ = 6.8865, vehicleRot = 0.0000, color_1 = 86, color_2 = 86;
                } 
                else if (org == 15) 
                {
                    // Veículos específicos para modelid 432, 470, 522, 425, 520, 560 ou 487
                    if (modelid == 432) 
                        vehicleX = -547.9016, vehicleY = -1013.4655, vehicleZ = 24.1339, vehicleRot = 237.5177, color_1 = 127, color_2 = 127;
                    else if (modelid == 470) 
                        vehicleX = -594.4136, vehicleY = -1084.6335, vehicleZ = 23.5743, vehicleRot = 238.4840, color_1 = 127, color_2 = 127;
                    else if (modelid == 522) 
                        vehicleX = -596.8322, vehicleY = -1087.7369, vehicleZ = 23.2149, vehicleRot = 238.3088, color_1 = 127, color_2 = 127;
                    else if (modelid == 425 || modelid == 433 || modelid == 487) 
                        vehicleX = -609.3846, vehicleY = -1086.3259, vehicleZ = 24.0293, vehicleRot = 198.8931, color_1 = 127, color_2 = 127;
                    else if (modelid == 520) 
                        vehicleX = -538.1840, vehicleY = -987.9913, vehicleZ = 25.1267, vehicleRot = 137.4882, color_1 = 127, color_2 = 127;
                    else if (modelid == 560) 
                        vehicleX = -584.4794, vehicleY = -1069.0209, vehicleZ = 23.0622, vehicleRot = 235.6891, color_1 = 127, color_2 = 127;
                } 
                else if (org == 20) 
                {
                    // Veículos específicos para modelid 432, 470, 522, 425, 520, 560 ou 487
                    if (modelid == 432) 
                        vehicleX = -344.5000000, vehicleY = 1514.7002000, vehicleZ = 75.5000000, vehicleRot = 0.0000000, color_1 = 40, color_2 = 40;
                    else if (modelid == 470) 
                        vehicleX = -355.7002000, vehicleY = 1519.5996000, vehicleZ = 75.7000000, vehicleRot = 0.0000000, color_1 = 40, color_2 = 40;
                    else if (modelid == 522) 
                        vehicleX = -333.7000100, vehicleY = 1535.6000000, vehicleZ = 75.2000000, vehicleRot = 179.9890000, color_1 = 40, color_2 = 40;
                    else if (modelid == 425 || modelid == 433 || modelid == 487) 
                        vehicleX = -335.0000000, vehicleY = 1555.5000000, vehicleZ = 76.4000000, vehicleRot = 225.2470000, color_1 = 40, color_2 = 40;
                    else if (modelid == 520) 
                        vehicleX = -353.9003900, vehicleY = 1542.4004000, vehicleZ = 76.5000000, vehicleRot = 171.9910000, color_1 = 40, color_2 = 40;
                    else if (modelid == 560) 
                        vehicleX = -372.9003900, vehicleY = 1519.5996000, vehicleZ = 75.4000000, vehicleRot = 0.0000000, color_1 = 40, color_2 = 40;
                }
            }
            default:
            {
                if (modelid == 462 || modelid == 510)
                {
                    vehicleX = 1690.3407, vehicleY = -2261.9456, vehicleZ = 13.0991, vehicleRot = 1.2544, color_1 = 1, color_2 = 1;
                }
                else return 1;
            }
        }
        if (!IsVehicleOccupied(VehiclePlayer[playerid][0])) {
            DestroyVehicle(VehiclePlayer[playerid][0]);
            VehiclePlayer[playerid][0] = INVALID_VEHICLE_ID;
        }
        else if (!IsVehicleOccupied(VehiclePlayer[playerid][1])) {
            DestroyVehicle(VehiclePlayer[playerid][1]);
            VehiclePlayer[playerid][1] = INVALID_VEHICLE_ID;
        }

        if (VehiclePlayer[playerid][0] == INVALID_VEHICLE_ID) {
            VehiclePlayer[playerid][0] = CreateVehicle(modelid, vehicleX, vehicleY, vehicleZ, vehicleRot, color_1, color_2, (60*1000*2), siren);
            UnlockVehicleDoors(VehiclePlayer[playerid][0]);
            PutPlayerInVehicle(playerid, VehiclePlayer[playerid][0], 0);
        }
        else if (VehiclePlayer[playerid][1] == INVALID_VEHICLE_ID) {
            VehiclePlayer[playerid][1] = CreateVehicle(modelid, vehicleX, vehicleY, vehicleZ, vehicleRot, color_1, color_2, (60*1000*2), siren);
            UnlockVehicleDoors(VehiclePlayer[playerid][1]);
            PutPlayerInVehicle(playerid, VehiclePlayer[playerid][1], 0);
        } else {
            DestroyVehicle(VehiclePlayer[playerid][0]);
        }
    }
    return 1;
}

stock VehiclePlayer_Destroy(vehicleid)
{
    foreach (new playerid : Player) {
        for (new vehicle; vehicle < MAX_VEHICLES_GARAGE; vehicle++) {
            if (vehicleid == VehiclePlayer[playerid][vehicle]) {
                VehiclePlayer[playerid][vehicle] = INVALID_VEHICLE_ID;
                DestroyVehicle(vehicleid);
            }
        }
    }
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (newkeys & KEY_YES)
	{
        new 
            org = GetPlayerOrg(playerid),
            Float:x, 
            Float:y, 
            Float:z;

        for (new i; i < sizeof(GARAGE_ORG_LOCATIONS); i++) 
        {
            new 
                loc_org = GARAGE_ORG_LOCATIONS[i][garageOrgID];

            x = GARAGE_ORG_LOCATIONS[i][garagePosX];
            y = GARAGE_ORG_LOCATIONS[i][garagePosY];
            z = GARAGE_ORG_LOCATIONS[i][garagePosZ];

            if (IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z))
            {
                if (org != loc_org)
                    return SendClientMessage(playerid, -1, "Você não faz parte dessa organização.");
                else
                {
                    switch(org)
                    {
                        case 0: 
                            ShowModelSelectionMenu(playerid, VehiclesOrg_Civil, "selecione um veiculo");
                        case 1, 2, 11, 16, 33, 34:
                            ShowModelSelectionMenu(playerid, VehiclesOrg_Police, "selecione um veiculo");
                        case 3, 15, 20:
                            ShowModelSelectionMenu(playerid, VehiclesOrg_Terrorista, "selecione um veiculo");
                        case 5, 14, 17, 18, 19, 21:
                            ShowModelSelectionMenu(playerid, VehiclesOrg_Gangster, "selecione um veiculo");
                        case 7:
                            ShowModelSelectionMenu(playerid, VehiclesOrg_Governo, "selecione um veiculo");
                        case 9:
                            ShowModelSelectionMenu(playerid, VehiclesOrg_SanNews, "selecione um veiculo");
                        case 12, 13, 24:
                            ShowModelSelectionMenu(playerid, VehiclesOrg_Mafiosa, "selecione um veiculo");
                        case 8, 22:
                            ShowModelSelectionMenu(playerid, VehiclesOrg_Assassina, "selecione um veiculo");
                        case 25, 28:
                            ShowModelSelectionMenu(playerid, VehiclesOrg_Mercenario, "selecione um veiculo");
                    }
                }
            }
        }
	}
    return 1;
}