// -----------------------------------------------------------------------------------------
// Módulo de actores -
// -----------------------------------------------------------------------------------------

#include <YSI_Coding\y_hooks>

enum ActorsEnum {
	Actor_Skin,
	Float:Actor_x,
	Float:Actor_y,
	Float:Actor_z,
	Float:Actor_a,
	Actor_World,
	Actor_AnimLib[25],
	Actor_AnimName[35],
}

new g_Actors[][ActorsEnum] = {
    {80, 767.752,14.236,1000.699,280.379, 10035, "GYMNASIUM", "GYMSHADOWBOX"},
    {81, 772.181,14.624,1000.695,103.368, 10035, "GYMNASIUM", "GYM_SHADOWBOX"},
    {96, 761.963,10.317,1001.163,48.139, 10035, "GYMNASIUM", "GYMSHADOWBOX"},
    {81, 760.875,10.820,1001.163,240.528, 10035, "GYMNASIUM", "GYM_SHADOWBOX"},
    {26, 760.303,6.453,1000.707,0.512, 10035, "ON_LOOKERS", "PANIC_POINT"},
    {12, 762.169,5.946,1000.711,9.077, 10035, "ON_LOOKERS", "SHOUT_01"},
    {80, 756.229,8.584,1000.700,68.483, 10035, "COP_AMBIENT", "COPBROWSE_NOD"},
    {2, 762.951,3.677,1000.712,4.562, 10035, "SMOKING", "M_SMKLEAN_LOOP"},
    {18, 766.162,-3.260,1000.716,272.151, 10035, "GYMNASIUM", "GYMSHADOWBOX"},
    {163, 1836.906,-1687.364,13.328,91.525, 0, "DEALER", "DEALER_IDLE"},
    {164, 1836.891,-1677.238,13.329,113.249, 0, "DEALER", "DEALER_IDLE"},
    {211, 501.832,-20.647,1000.679,92.262, 10007, "DEALER", "DEALER_IDLE_01"},
    {43, 499.825,-20.700,1000.679,272.326, 10007, "DEALER", "SHOP_PAY"},
    {69, 501.522,-11.183,1000.679,0.895, 10007, "DEALER", "SHOP_PAY"},
    {178, 489.218,-2.040,1002.382,181.295, 10007, "STRIP", "STR_LOOP_C"},
    {246, 486.487,-2.192,1002.382,269.320, 10007, "STRIP", "STR_C2"},
    {2, 476.060,-14.997,1003.695,272.534, 10007, "DANCING", "DAN_LEFT_A"},
    {87, 487.011,-26.196,1003.594,91.217, 10007, "BEACH", "BATHER"},
    {3, 486.690,-7.542,1000.671,356.508, 10007, "STRIP", "PUN_CASH"},
    {20, 488.255,-7.500,1000.671,6.952, 10007, "STRIP", "PUN_HOLLER"},
    {22, 485.572,-15.127,1000.679,282.978, 10007, "DANCING", "DAN_LOOP_A"},
    {46, 485.788,-21.531,1003.109,4.655, 10007, "STRIP", "PUN_LOOP"},
    {48, 482.279,-23.952,1003.109,196.080, 10007, "PED", "SEAT_IDLE"},
    {55, 482.028,-26.222,1003.594,6.407, 10007, "BEACH", "PARKSIT_W_LOOP"},
    {56, 488.104,-21.533,1003.109,2.983, 10007, "DANCING", "DAN_DOWN_A"},
    {163, 477.740,-19.253,1000.679,273.224, 10007, "DEALER", "DEALER_IDLE"},
    {59, 487.726,-24.892,1003.109,70.791, 10007, "PED", "SEAT_IDLE"},
    {91, 483.287,-25.716,1003.109,3.592, 10007, "PED", "SEAT_IDLE"},
    {164, 476.287,-21.730,1003.109,182.484, 10007, "DEALER", "DEALER_IDLE"},
    {93, 486.599,-14.415,1000.679,120.507, 10007, "DANCING", "DAN_RIGHT_A"},
    {95, 488.002,-11.493,1000.679,163.957, 10007, "DANCING", "DANCE_LOOP"},
    {98, 488.582,-14.202,1000.679,109.018, 10007, "DANCING", "DNCE_M_A"},
    {101, 490.072,-11.126,1000.679,172.730, 10007, "DANCING", "DNCE_M_B"},
    {216, 489.960,-17.246,1000.679,41.547, 10007, "DANCING", "DAN_UP_A"},
    {141, 487.691,-15.798,1000.679,268.066, 10007, "DANCING", "DAN_DOWN_A"},
    {147, 490.838,-15.248,1000.679,60.974, 10007, "RUNNINGMAN", "DANCE_LOOP"},
    {150, 489.982,-12.820,1000.679,115.703, 10007, "STRIP", "STRIP_A"},
    {151, 485.885,-11.628,1000.679,126.148, 10007, "STRIP", "STR_LOOP_C"},
    {152, 483.837,-12.409,1000.679,249.184, 10007, "STRIP", "STR_LOOP_B"},
    {169, 494.761,-11.419,1000.679,270.363, 10007, "PED", "SEAT_IDLE"},
    {101, 506.198,-1.607,1000.679,276.421, 10007, "FOOD", "EAT_VOMIT_P"},
    {163, 490.688,-24.331,1000.679,358.324, 10007, "DEALER", "DEALER_IDLE"},
    {147, 354.603,173.841,1008.382,92.760, 0, "COP_AMBIENT", "COPBROWSE_LOOP"},
    {187, 356.267,178.340,1008.376,286.692, 0, "OTB", "BETSLP_LOOP"},
    {221, -2021.632,-116.739,1035.171,93.084, 10008, "GANGS", "PRTIAL_GNGTLKB"},
    {1, -2026.010,-116.485,1035.171,270.433, 10008, "PED", "SEAT_IDLE"},
    {2, -2026.008,-115.780,1035.171,270.851, 10008, "PED", "SEAT_IDLE"},
    {3, -2024.517,-117.643,1035.171,271.895, 10008, "PED", "SEAT_IDLE"},
    {4, -2024.550,-116.416,1035.171,271.895, 10008, "PED", "SEAT_IDLE"},
    {17, -2027.293,-115.772,1035.171,268.425, 10008, "PED", "SEAT_IDLE"},
    {29, -2027.205,-117.008,1035.171,270.932, 10008, "PED", "SEAT_IDLE"},
    {12, -2022.884,-116.512,1035.171,270.804, 10008, "PED", "SEAT_IDLE"},
    {208, -2032.890,-118.695,1035.171,1.335, 10008, "PED", "SEAT_IDLE"},
    {217, 253.922,69.716,1003.640,268.633, 0, "INT_OFFICE", "OFF_SIT_BORED_LOOP"},
    {281, 256.606,64.630,1003.640,271.349, 0, "COP_AMBIENT", "COPBROWSE_SHAKE"},
    {283, 251.256,67.956,1003.640,90.995, 0, "COP_AMBIENT", "COPLOOK_SHAKE"},
    {230, 263.433,78.746,1001.039,26.320, 0, "CRACK", "BBALBAT_IDLE_02"},
    {29, 264.286,75.897,1001.039,359.147, 0, "SMOKING", "M_SMKLEAN_LOOP"},
    {299, 481.693,-20.540,1000.671,2.907, 10007, "KISSING", "PLAYA_KISS_02"},
    {216, 481.645,-19.633,1000.671,182.280, 10007, "KISSING", "GRLFRD_KISS_02"},
    {105, 2303.035,-1650.941,14.569,90.898, 0, "GANGS", "PRTIAL_GNGTLKB"},
    {106, 2300.930,-1649.744,14.673,233.315, 0, "GANGS", "INVITE_NO"},
    {107, 2300.249,-1651.411,14.687,288.752, 0, "GANGS", "HNDSHKFA"},
    {19, 2301.095,-1651.009,14.664,118.297, 0, "GANGS", "HNDSHKFA"},
    {29, 2301.924,-1652.247,14.637,324.136, 0, "GANGS", "PRTIAL_GNGTLKB"},
    {271, 2461.038,-1691.118,13.521,2.781, 0, "SMOKING", "M_SMKLEAN_LOOP"},
    {270, 2521.994,-1679.094,15.496,85.775, 0, "SMOKING", "M_SMK_IN"},
    {105, 2464.227,-1667.514,13.477,70.462, 0, "GANGS", "DRNKBR_PRTL"},
    {106, 2463.377,-1666.244,13.474,178.459, 0, "GANGS", "PRTIAL_GNGTLKD"},
    {107, 2463.349,-1668.181,13.480,314.446, 0, "GANGS", "PRTIAL_GNGTLKB"},
    {22, 2462.720,-1667.026,13.476,211.254, 0, "SMOKING", "M_SMK_IN"},
    {22, 2512.565,-1649.366,14.355,138.866, 0, "SMOKING", "M_SMK_DRAG"},
    {211, 208.673,-98.702,1005.257,184.422, 10070, "OTB", "BETSLP_TNK"},
    {12, 204.569,-107.937,1005.132,271.320, 10070, "COP_AMBIENT", "COPBROWSE_LOOP"},
    {1, 211.924,-105.483,1005.140,180.243, 10070, "COP_AMBIENT", "COPBROWSE_NOD"},
    {2, 208.727,-107.986,1005.132,273.827, 10070, "COP_AMBIENT", "COPBROWSE_LOOP"},
    {3, 206.470,-107.174,1005.132,88.332, 10070, "COP_AMBIENT", "COPBROWSE_NOD"},
    {3, 1831.704,-1676.749,13.545,182.994, 0, "GANGS", "PRTIAL_GNGTLKB"},
    {11, 1831.717,-1677.530,13.545,3.267, 0, "GANGS", "PRTIAL_GNGTLKD"},
    {240, 1831.194,-1686.886,13.546,306.031, 0, "GANGS", "DRNKBR_PRTL"},
    {216, 1832.014,-1686.049,13.532,126.385, 0, "GANGS", "PRTIAL_GNGTLKA"},
    {19, 1145.682,-1212.228,18.770,82.270, 0, "GANGS", "HNDSHKAA"},
    {18, 1144.714,-1212.248,18.784,267.974, 0, "GANGS", "HNDSHKAA"},
    {108, 2854.690,-1164.796,24.840,157.082, 0, "GANGS", "PRTIAL_GNGTLKB"},
    {109, 2854.710,-1165.832,24.832,47.415, 0, "GANGS", "PRTIAL_GNGTLKA"},
    {110, 2853.206,-1164.878,24.842,258.684, 0, "GANGS", "PRTIAL_GNGTLKD"},
    {29, 2853.591,-1166.257,24.831,347.254, 0, "SMOKING", "M_SMK_IN"},
    {114, 1709.721,-2104.612,13.546,249.146, 0, "GANGS", "PRTIAL_GNGTLKA"},
    {115, 1711.256,-2104.200,13.546,114.412, 0, "GANGS", "PRTIAL_GNGTLKD"},
    {116, 1710.697,-2105.460,13.546,16.233, 0, "GANGS", "PRTIAL_GNGTLKB"},
    {2, 1710.013,-2101.237,14.021,185.002, 0, "SMOKING", "M_SMKLEAN_LOOP"},
    {284, 1544.563,-1631.849,13.382,92.528, 0, "DEALER", "DEALER_IDLE_01"},
    {283, 1610.642,-1719.027,6.218,274.971, 0, "GYMNASIUM", "GYMSHADOWBOX"},
    {29, 1611.724,-1718.717,6.218,91.147, 0, "PED", "DUCK_COWER"},
    // {14, 1162.377,-1317.833,-44.276,172.117, 0, "PED", "SEAT_IDLE"},
    // {38, 1163.681,-1317.825,-44.276,182.416, 0, "PED", "SEAT_IDLE"},
    // {70, 1151.447,-1324.785,-44.283,213.187, 0, "DEALER", "DEALER_IDLE"},
    // {70, 1166.183,-1326.943,-44.283,266.535, 0, "PED", "SEAT_IDLE"},
    // {76, 1164.846,-1325.006,-44.283,359.909, 0, "PED", "SEAT_IDLE"},
    // {77, 1173.074,-1330.380,-44.283,359.428, 0, "PED", "SEAT_IDLE"},
    // {78, 1175.003,-1330.394,-44.283,357.965, 0, "PED", "SEAT_IDLE"},
    // {89, 1175.435,-1328.567,-44.276,3.396, 0, "PED", "SEAT_IDLE"},
    // {90, 1173.959,-1341.473,-44.283,0.048, 0, "PED", "SEAT_IDLE"},
    // {91, 1174.863,-1340.730,-44.283,89.459, 0, "PED", "SEAT_IDLE"},
    // {93, 1173.880,-1336.724,-44.283,359.074, 0, "BAR", "DNK_STNDF_LOOP"},
    // {12, 1161.620,-1339.437,-44.283,6.303, 0, "COP_AMBIENT", "COPLOOK_NOD"},
    // {308, 1163.507,-1327.186,-44.283,182.770, 0, "COP_AMBIENT", "COPBROWSE_NOD"},
    // {240, 1161.868,-1326.150,-44.283,88.769, 0, "BAR", "DNK_STNDF_LOOP"},
    // {232, 1151.385,-1313.207,-43.385,93.782, 0, "CRACK", "CRCKIDLE2"},
    // {222, 1150.320,-1310.583,-43.385,90.858, 0, "CRACK", "CRCKDETH2"},
    // {220, 1149.983,-1313.035,-43.385,263.152, 0, "CRACK", "CRCKIDLE1"},
    // {308, 1170.453,-1314.966,-44.283,182.514, 0, "PED", "SEAT_IDLE"},
    // {141, 1172.903,-1314.993,-44.283,179.799, 0, "PED", "SEAT_IDLE"},
    // {150, 1175.042,-1314.967,-44.283,175.621, 0, "PED", "SEAT_IDLE"},
    // {150, 1174.721,-1312.639,-44.283,90.393, 0, "COP_AMBIENT", "COPBROWSE_LOOP"},
    // {147, 1170.616,-1307.158,-44.064,167.346, 0, "COP_AMBIENT", "COPBROWSE_NOD"},
    // {216, 1170.655,-1316.864,-44.283,1.406, 0, "GANGS", "PRTIAL_GNGTLKA"},
    // {219, 1165.759,-1329.847,-43.643,96.451, 0, "CRACK", "CRCKIDLE2"},
    // {70, 1163.729,-1329.590,-44.283,2.032, 0, "COP_AMBIENT", "COPBROWSE_SHAKE"},
    // {70, 1162.489,-1329.688,-44.283,1.824, 0, "COP_AMBIENT", "COPBROWSE_LOOP"},
    // {240, 1160.609,-1330.072,-43.643,87.887, 0, "CRACK", "CRCKIDLE2"},
    {211, 820.187,-0.276,1004.179,272.303, 10021, "COP_AMBIENT", "COPLOOK_NOD"},
    {76, 820.185,1.888,1004.179,270.214, 10021, "OTB", "BETSLP_LOOP"},
    {150, 820.183,4.060,1004.179,272.303, 10021, "OTB", "BETSLP_TNK"},
    {187, 820.185,6.298,1004.179,271.676, 10021, "PED", "IDLE_STANCE"},
    {147, 1168.864,1344.696,673.374,270.225, 10017, "OTB", "BETSLP_LOOP"},
    {148, 1167.963,1340.492,673.374,1.093, 10017, "OTB", "WTCHRACE_LOOP"},
    {150, 1164.551,1341.099,673.374,92.378, 10017, "COP_AMBIENT", "COPBROWSE_NOD"},
    {305, 1168.944,1348.202,673.374,91.334, 10017, "COP_AMBIENT", "COPLOOK_LOOP"},
    {240, -2025.731,-117.723,1035.171,273.203, 10008, "PED", "SEAT_IDLE"},
    {163, 286.215,-1615.826,33.071,188.202, 0, "DEALER", "DEALER_IDLE"},
    {137, 1337.249,-1772.565,13.546,317.579, 0, "CRACK", "CRCKIDLE1"},
    {8, 1362.837,-6.005,1000.921,93.193, 99, "PED", "PHONE_TALK"},
    {71, 1362.987,-10.601,1000.921,266.637, 99, "DEALER", "DEALER_IDLE"},
    {71, 1800.518,-1575.408,14.062,247.001, 0, "DEALER", "DEALER_IDLE"},
    {268, 1375.093,-41.917,1000.920,179.675, 99, "BAR", "DNK_STNDF_LOOP"},
    {268, 1391.854,-26.755,1004.397,0.510, 99, "SMOKING", "M_SMKLEAN_LOOP"},
    // {275, 1152.127,-1312.682,-44.283,97.763, 0, "OTB", "BETSLP_LOOP"},
    // {276, 1172.669,-1329.807,-44.283,249.290, 0, "GANGS", "PRTIAL_GNGTLKA"},
    // {274, 1162.186,-1337.775,-44.283,158.632, 0, "GANGS", "PRTIAL_GNGTLKB"},
    // {162, 1160.517,-1312.765,-43.228,0.083, 0, "CRACK", "CRCKIDLE2"},
    // {70, 1160.761,-1313.454,-44.283,355.488, 0, "OTB", "BETSLP_LOOP"},
    // {308, 1163.201,-1314.158,-44.283,289.479, 0, "OTB", "BETSLP_LOOP"},
    // {274, 1161.568,-1313.460,-44.283,40.609, 0, "COP_AMBIENT", "COPLOOK_THINK"},
    // {275, 1159.934,-1313.453,-44.283,341.284, 0, "CASINO", "ROULETTE_LOOP"},
    {93, -27.068,-91.660,1003.546,3.473, 10078, "OTB", "BETSLP_TNK"},
    {93, -26.955,-91.622,1003.546,1.093, 10079, "OTB", "BETSLP_TNK"},
    {93, -26.988,-91.622,1003.546,359.840, 10058, "OTB", "BETSLP_TNK"},
    {287, -1332.221,495.203,11.195,38.123, 0, "COP_AMBIENT", "COPBROWSE_NOD"},
    {287, -1338.841,486.443,11.180,220.983, 0, "DEALER", "DEALER_IDLE"},
    {287, -1359.510,493.292,29.944,283.987, 0, "OTB", "BETSLP_LOOP"},
    {287, -1360.944,494.252,29.944,50.366, 0, "ON_LOOKERS", "LKUP_LOOP"},
    {287, -1394.808,494.779,19.500,179.752, 0, "COP_AMBIENT", "COPBROWSE_NOD"},
    {287, -1254.136,459.084,7.187,89.861, 0, "DEALER", "DEALER_IDLE"},
    {287, -1254.062,435.047,7.180,81.714, 0, "DEALER", "DEALER_IDLE"},
    {287, -1346.496,490.594,11.202,2.351, 0, "PED", "SEAT_IDLE"},
    {287, -1347.947,491.300,11.195,132.169, 0, "COP_AMBIENT", "COPBROWSE_SHAKE"},
    {287, -1350.031,497.886,11.195,282.426, 0, "DEALER", "DEALER_IDLE_01"},
    {287, -1305.501,510.023,11.195,343.021, 0, "COP_AMBIENT", "COPBROWSE_SHAKE"},
    {29, 945.760,2177.674,1011.023,149.115, 10020, "DEALER", "DEALER_IDLE"},
    {28, 938.282,2177.480,1011.023,209.566, 10020, "DEALER", "DEALER_IDLE"},
    {137, 932.838,2159.211,1011.030,318.961, 10020, "CRACK", "CRCKIDLE1"},
    {135, 951.551,2148.295,1011.023,54.842, 10020, "CRACK", "BBALBAT_IDLE_02"},
    {64, 951.587,2156.792,1011.023,273.486, 10020, "CRACK", "CRCKIDLE2"},
    {19, 934.492,2172.558,1011.023,273.086, 10020, "SMOKING", "M_SMK_IN"},
    {22, 939.708,2148.268,1011.023,357.977, 10020, "DEALER", "DEALER_IDLE"},
    {22, -1636.1615,1422.2684,7.1875,174.5025, 800, "DEALER", "DEALER_IDLE"}, // NPC Observar
    {23, -1626.2994,1417.8669,7.1853,44.7590, 800, "ped", "IDLE_chat"}, // NPC Conversar
    {2, -1627.2279,1418.5006,7.1855,228.3617, 800, "ped", "IDLE_chat"}, // NPC Conversar 2
    {15, -1628.7152,1424.8567,7.1831,134.2993, 800, "MISC", "Seat_talk_01"}, // NPC Banco
    {60, -1621.9380,1421.8147,7.1734,318.4272, 800, "ped", "roadcross"}, // NPC Olhar pro mar
    {15, -1630.4758,1413.6913,7.1875,82.5084, 800, "FIGHT_C", "FightC_IDLE"}, // NPC Praticar Ninja
    {104, -1633.3802,1419.8446,7.1875,226.8850, 800, "GYMNASIUM", "gym_shadowbox"}, // NPC Lutar 1
    {107, -1632.5934,1419.2578,7.1875,47.9516, 800, "GYMNASIUM", "gym_shadowbox"}, // NPC Lutar 2
    {217, 1676.5328,-2263.4382,13.5360,0.2980, 0, "DEALER", "DEALER_IDLE"}, // NPC - Staff Respawn Civil Masculino
    {211, 1689.3104,-2263.4380,13.4783,0.0000, 0, "DEALER", "DEALER_IDLE"}, // NPC - Staff Respawn Civil Feminino
    {163, 1473.8011,-1783.5957,13.5400,358.5996, 0, "DEALER", "DEALER_IDLE"},
    {164, 1483.5608,-1783.4651,13.5400,2.4408, 0, "DEALER", "DEALER_IDLE"},
    {281, 221.5007,111.8539,1010.2118,0.000, 1000, "COP_AMBIENT", "COPLOOK_SHAKE"},
    {52, -2819.752685, 1146.054077, 20.274333, 329.583190, 800, "GANGS","leanIDLE"},
    {54, -2804.617431, 1145.119628, 20.273437, 47.933517, 800, "GANGS", "PRTIAL_GNGTLKA"},
    {53, -2805.317626, 1145.123535, 20.273437, 358.073791, 800, "GANGS", "PRTIAL_GNGTLKA"},
    {252, -2807.462890, 1162.407836, 20.312500, 28.157781, 800, "RIOT","RIOT_FUKU"},
    {258, -2824.001464, 1163.334594, 20.419719, 276.214538, 800, "MISC","Seat_talk_01"},
    {262, -2824.079345, 1161.227294, 20.429927, 271.201354, 800, "MISC","Seat_talk_01"},
    {266, -2818.365966, 1176.470214, 20.273437, 216.054595, 800, "RIOT","RIOT_ANGRY"},
    {271, -2792.500488, 1161.677734, 20.273437, 357.118591, 800, "GANGS","prtial_gngtlkH"},
    {107, -2791.385009, 1162.456542, 20.273437, 85.667343, 800, "GANGS", "PRTIAL_GNGTLKA"},
    {106, -2792.196777, 1163.630249, 20.273437, 172.273376, 800, "GANGS", "PRTIAL_GNGTLKA"},
    {187, 1368.5126,-1760.9615,13.7182,267.3436, 0, "PED", "SEAT_idle"},
    {147, 1371.9995,-1751.2605,13.6598,177.0875, 0, "PED", "SEAT_idle"},
    {17, 1375.1105,-1762.3038,13.6598,85.1907, 0, "PED", "SEAT_idle"},
    {227, 1368.8197,-1755.4982,13.6598,264.1222, 0, "DEALER", "DEALER_IDLE"}
};

enum actenum {
	bool:actrendido,
	bool:actmorto,
	assaltotempo,
	actTimer,
	actanimLib[35],
	actanimName[35],
}
new ActorInfo[MAX_ACTORS][actenum];

static s_AnimationLibraries[][] = {
        !"AIRPORT",    !"ATTRACTORS",   !"BAR",                 !"BASEBALL",
        !"BD_FIRE",    !"BEACH",            !"BENCHPRESS",  !"BF_INJECTION",
        !"BIKED",      !"BIKEH",        !"BIKELEAP",        !"BIKES",
        !"BIKEV",      !"BIKE_DBZ",     !"BMX",             !"BOMBER",
        !"BOX",        !"BSKTBALL",     !"BUDDY",           !"BUS",
        !"CAMERA",     !"CAR",          !"CARRY",           !"CAR_CHAT",
        !"CASINO",     !"CHAINSAW",     !"CHOPPA",          !"CLOTHES",
        !"COACH",      !"COLT45",       !"COP_AMBIENT", !"COP_DVBYZ",
        !"CRACK",      !"CRIB",         !"DAM_JUMP",         !"DANCING",
        !"DEALER",     !"DILDO",        !"DODGE",            !"DOZER",
        !"DRIVEBYS",   !"FAT",          !"FIGHT_B",      !"FIGHT_C",
        !"FIGHT_D",    !"FIGHT_E",      !"FINALE",               !"FINALE2",
        !"FLAME",      !"FLOWERS",      !"FOOD",                 !"FREEWEIGHTS",
        !"GANGS",      !"GHANDS",       !"GHETTO_DB",    !"GOGGLES",
        !"GRAFFITI",   !"GRAVEYARD",    !"GRENADE",      !"GYMNASIUM",
        !"HAIRCUTS",   !"HEIST9",       !"INT_HOUSE",    !"INT_OFFICE",
        !"INT_SHOP",   !"JST_BUISNESS", !"KART",                 !"KISSING",
        !"KNIFE",      !"LAPDAN1",              !"LAPDAN2",      !"LAPDAN3",
        !"LOWRIDER",   !"MD_CHASE",     !"MD_END",               !"MEDIC",
        !"MISC",       !"MTB",                  !"MUSCULAR",     !"NEVADA",
        !"ON_LOOKERS", !"OTB",                  !"PARACHUTE",    !"PARK",
        !"PAULNMAC",   !"PED",                  !"PLAYER_DVBYS", !"PLAYIDLES",
        !"POLICE",     !"POOL",                 !"POOR",                 !"PYTHON",
        !"QUAD",       !"QUAD_DBZ",     !"RAPPING",      !"RIFLE",
        !"RIOT",       !"ROB_BANK",     !"ROCKET",               !"RUSTLER",
        !"RYDER",      !"SCRATCHING",   !"SHAMAL",               !"SHOP",
        !"SHOTGUN",    !"SILENCED",     !"SKATE",                !"SMOKING",
        !"SNIPER",     !"SPRAYCAN",     !"STRIP",                !"SUNBATHE",
        !"SWAT",       !"SWEET",                !"SWIM",                 !"SWORD",
        !"TANK",       !"TATTOOS",              !"TEC",                  !"TRAIN",
        !"TRUCK",      !"UZI",                  !"VAN",                  !"VENDING",
        !"VORTEX",     !"WAYFARER",     !"WEAPONS",      !"WUZI",
        !"WOP",        !"GFUNK",                !"RUNNINGMAN"
};

hook OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, WEAPON:weaponid, bodypart)
{
	foreach(new player : Player) 
	{
	    if ( GetPVarInt(player, "assaltando") == damaged_actorid ) 
		{
       		HidePlayerProgressBar(player, BarSprayTag[player]);

			KillTimer(GetPVarInt(player, "timerassalto"));

    		SendClientMessage(player, COLOR_LIGHTRED, "* A pessoa que você estava assaltando foi morta!");
            ApplyActorAnimation(damaged_actorid, "PED", "KO_shot_stom", 4.1, false, true, true, true, false);

			for(new x; x != 4; x++) {
				PlayerTextDrawHide(player, textAbordagem[x][player]);
		  	}
			SetPVarInt(player, "assaltando", INVALID_ACTOR_ID);
			return 1;
	    }
	}

	if ( !ActorInfo[damaged_actorid][actmorto] ) {

        ActorInfo[damaged_actorid][actmorto] = true;

		ApplyActorAnimation(damaged_actorid, "PED", "KO_shot_stom", 4.1, false, true, true, true, false);
		if ( ActorInfo[damaged_actorid][actTimer] != -1) {
		    KillTimer(ActorInfo[damaged_actorid][actTimer]);
		}
		ActorInfo[damaged_actorid][actTimer] = SetTimerEx("acalmarActor", 55000, false, "d", damaged_actorid);
	}
	return 1;
}

hook OnGameModeInit() 
{
    // Criando os actores;
    Actors_Create();

    return 1;
}

CALLBACK: assaltoActor(playerid, actorid) {

	if (GetPlayerTargetActor(playerid) != actorid || !ProxDetectorActor(7.0, playerid, actorid)) {

		if (IsPlayerConnected(playerid)) {

			SetPVarInt(playerid, "assaltando", INVALID_ACTOR_ID);
			HidePlayerProgressBar(playerid, BarSprayTag[playerid]);

			for(new x; x != 4; x++) {
				PlayerTextDrawHide(playerid, textAbordagem[x][playerid]);
		  	}
		}

		ApplyActorAnimation(actorid, "PED", "DUCK_cower", 4.1, true, false, false, false, false);
		if ( ActorInfo[actorid][actTimer] != -1) {
		    KillTimer(ActorInfo[actorid][actTimer]);
		}
		ActorInfo[actorid][actTimer] = SetTimerEx("acalmarActor", 55000, false, "d", actorid);
		return 0;
	}

	new Float:percent = GetPVarFloat(playerid, "percent")+0.3;
	SetPVarFloat(playerid, "percent", percent);
	SetPlayerProgressBarValue(playerid, BarSprayTag[playerid], percent);
	ShowPlayerProgressBar(playerid, BarSprayTag[playerid]);

	if ( percent > 99.0) {

		if ( gettime() < ActorInfo[actorid][assaltotempo] ) {
		    return SendClientMessage(playerid, -1, "Este cidadão já foi assaltado a poucos minutos!");
		}
	    // Sucesso no assalto
	    HidePlayerProgressBar(playerid, BarSprayTag[playerid]);

		for(new x; x != 4; x++) {
			PlayerTextDrawHide(playerid, textAbordagem[x][playerid]);
		}

	    // Dar dinheiro
	    // dropItem(playerid, ITEM_TYPE_DINHEIRO, 1212, (200 + random(400)), "Dinheiro", false);

		ActorInfo[actorid][assaltotempo] = gettime() + (5 * 60);
		SetPVarInt(playerid, "assaltou", gettime() + 120);
		SetPVarInt(playerid, "assaltando", INVALID_ACTOR_ID);

		SendClientMessage(playerid, -1, "Assalto concluido!! Pegue o dinheiro no chão e saia do local, pois a polícia já foi avisada!");

		ApplyActorAnimation(actorid, "PED", "DUCK_cower", 4.1, true, false, false, false, false);
		if ( ActorInfo[actorid][actTimer] != -1) {
		    KillTimer(ActorInfo[actorid][actTimer]);
		}
		ActorInfo[actorid][actTimer] = SetTimerEx("acalmarActor", 55000, false, "d", actorid);

	} else {
        SetPVarInt(playerid, "timerassalto", SetTimerEx("assaltoActor", 100, false, "dd", playerid, actorid));
	}
	return 1;
}

stock PreloadActorAnimations(actorid) {
    for(new i = 0; i < sizeof(s_AnimationLibraries); i ++)
        ApplyDynamicActorAnimation(actorid, s_AnimationLibraries[i], "null", 0.0, 0, 0, 0, 0, 0);
}

stock Actors_Create() {

	new actorid;

	for(new actor; actor != sizeof (g_Actors); actor++) {

		actorid = CreateDynamicActor(g_Actors[actor][Actor_Skin], g_Actors[actor][Actor_x], g_Actors[actor][Actor_y], g_Actors[actor][Actor_z], g_Actors[actor][Actor_a], false, 100.0, g_Actors[actor][Actor_World]);
		PreloadActorAnimations(actorid);
		ApplyDynamicActorAnimation(actorid, g_Actors[actor][Actor_AnimLib], g_Actors[actor][Actor_AnimName], 4.1, 1, 0, 0, 0, 0);
		ApplyDynamicActorAnimation(actorid, g_Actors[actor][Actor_AnimLib], g_Actors[actor][Actor_AnimName], 4.1, 1, 0, 0, 0, 0);
		
		// Set Into
        format(ActorInfo[actorid][actanimLib], 35, g_Actors[actor][Actor_AnimLib]);
        format(ActorInfo[actorid][actanimName], 35, g_Actors[actor][Actor_AnimName]);
  		ActorInfo[actorid][actrendido] = false;
        ActorInfo[actorid][actmorto] = false;
        ActorInfo[actorid][actTimer] = -1;
	}
}
