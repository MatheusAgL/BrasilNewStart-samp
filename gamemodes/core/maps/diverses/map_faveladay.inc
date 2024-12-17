
stock CreateMap_Favela_Day()
{
    CreateDynamicObject(3655, 149.22501, -1402.19678, 48.66870,   6.00000, -2.00000, 45.00000, .drawdistance = 150.0);
    CreateDynamicObject(13687, 7935.86084, 5058.55078, 1136.84216,   0.00000, 0.00000, 0.00000, .drawdistance = 150.0);
    CreateDynamicObject(3601, 159.04610, -1366.97302, 56.70630,   0.00000, 0.00000, -54.00000, .drawdistance = 150.0);
    CreateDynamicObject(3601, 142.75575, -1391.70264, 48.42780,   6.00000, -2.00000, 47.00000, .drawdistance = 150.0);
    CreateDynamicObject(1358, 10119.41504, -3707.34668, 38.34982,   0.00000, 0.00000, 0.00000, .drawdistance = 150.0);
    CreateDynamicObject(1358, 10119.41504, -3707.34668, 38.34982,   0.00000, 0.00000, 0.00000, .drawdistance = 150.0);
    CreateDynamicObject(1358, 158.81860, -1399.21729, 47.64940,   6.00000, -3.00000, 46.00000, .drawdistance = 150.0);
    CreateDynamicObject(3655, 170.10225, -1382.18396, 51.23810,   0.00000, 4.00000, -135.00000, .drawdistance = 150.0);
    CreateDynamicObject(1358, -7104.67676, 4647.04053, 3635.93945,   0.00000, 0.00000, 0.00000, .drawdistance = 150.0);
    CreateDynamicObject(1358, -7104.67676, 4647.04053, 3635.93945,   0.00000, 0.00000, 0.00000, .drawdistance = 150.0);
    CreateDynamicObject(1358, -7104.67676, 4647.04053, 3635.93945,   0.00000, 0.00000, 0.00000, .drawdistance = 150.0);
    CreateDynamicObject(3655, 164.09990, -1374.98132, 51.99080,   -1.00000, 4.00000, 217.00000, .drawdistance = 150.0);
    CreateDynamicObject(1358, 9171.19141, 792.98828, 6570.06348,   0.00000, 0.00000, 0.00000, .drawdistance = 150.0);
    CreateDynamicObject(1358, 165.70578, -1389.77612, 48.50000,   0.00000, 0.00000, 52.00000, .drawdistance = 150.0);
    CreateDynamicObject(3655, 167.48100, -1378.44653, 57.84150,   4.00000, 0.00000, -45.00000, .drawdistance = 150.0);
    CreateDynamicObject(3655, 154.19440, -1357.29297, 51.53570,   -1.00000, 0.00000, 25.00000, .drawdistance = 150.0);
    CreateDynamicObject(3655, 132.03712, -1382.11438, 51.76880,   0.00000, 0.00000, 37.00000, .drawdistance = 150.0);
    CreateDynamicObject(3655, 125.21240, -1370.07410, 51.74740,   0.00000, 0.00000, 22.00000, .drawdistance = 150.0);
    CreateDynamicObject(3655, 151.01683, -1347.39111, 51.47770,   0.00000, 0.00000, 12.00000, .drawdistance = 150.0);
    CreateDynamicObject(3655, 121.04960, -1358.56409, 51.75140,   0.00000, 0.00000, 18.00000, .drawdistance = 150.0);
    CreateDynamicObject(3601, 117.95464, -1343.37585, 55.91230,   0.00000, 0.00000, 96.00000, .drawdistance = 150.0);
    CreateDynamicObject(3655, 117.18418, -1330.17310, 51.04600,   0.00000, 0.00000, 2.00000, .drawdistance = 150.0);
    CreateDynamicObject(5836, 149.78819, -1352.39294, 48.56460,   0.00000, 0.00000, 0.00000, .drawdistance = 150.0);
    CreateDynamicObject(3655, 148.91110, -1336.58960, 50.02170,   0.00000, 0.00000, 182.00000, .drawdistance = 150.0);
    CreateDynamicObject(3655, 148.58849, -1324.83313, 49.92910,   0.00000, 0.00000, 180.00000, .drawdistance = 150.0);
    CreateDynamicObject(116, 156.28030, -1398.80530, 47.82330,   90.00000, 0.00000, 130.00000, .drawdistance = 150.0);
    CreateDynamicObject(3593, 166.47479, -1392.80908, 47.87360,   3.94000, 25.08000, -42.00000, .drawdistance = 150.0);
    CreateDynamicObject(1358, 163.54630, -1392.54285, 48.35440,   0.00000, 0.00000, 52.00000, .drawdistance = 150.0);
    CreateDynamicObject(3749, 131.84540, -1316.63342, 51.46000,   0.00000, 0.00000, 0.00000, .drawdistance = 150.0);
    CreateDynamicObject(3171, 123.33898, -1322.29565, 47.48634,   0.00000, 0.00000, 0.00000, .drawdistance = 150.0);

    printf("[MAPA %d]: Favela Family Day loaded...", gm_count[COUNT_CREATEMAP]);
    gm_count[COUNT_CREATEMAP]++;
}

stock RemoveBuilding_MapFavelaDay(playerid)
{
    RemoveBuildingForPlayer(playerid, 13863, 201.2891, -1389.4141, 41.2188, 0.25);
    RemoveBuildingForPlayer(playerid, 707, 148.7734, -1407.0703, 43.2422, 0.25);
    RemoveBuildingForPlayer(playerid, 620, 116.8516, -1349.0313, 44.8594, 0.25);
    RemoveBuildingForPlayer(playerid, 620, 119.7500, -1361.7813, 46.3281, 0.25);
    RemoveBuildingForPlayer(playerid, 1308, 124.3438, -1339.1094, 48.0078, 0.25);
    RemoveBuildingForPlayer(playerid, 620, 130.1797, -1379.3594, 46.3281, 0.25);
    RemoveBuildingForPlayer(playerid, 700, 174.1953, -1383.9688, 48.7188, 0.25);
    RemoveBuildingForPlayer(playerid, 1308, 170.7266, -1388.0391, 48.1328, 0.25);
    
    return 1;
}