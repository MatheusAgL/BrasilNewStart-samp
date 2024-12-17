#include <YSI_Coding\y_hooks>

hook OnCreateObject()
{
	new mapobj_arraia[3];
	CreateDynamicObject(842, 317.7877, -1849.9069, 2.3584, 3.2000, 0.0000, 0.0000, .drawdistance = 350.0); //DEAD_TREE_14
	mapobj_arraia[0] = CreateDynamicObject(18761, 340.8053, -1869.7285, 7.6913, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //RaceFinishLine1
	SetObjectMaterial(mapobj_arraia[0], 0, -1, "none", "none", 0xFFFF8C00);
	CreateDynamicObject(19158, 340.9022, -1865.3557, -0.2014, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //MetalLightBars2
	CreateDynamicObject(19129, 340.8826, -1865.3300, 3.3599, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DanceFloor2
	CreateDynamicObject(16366, 340.8346, -1870.9582, 6.5930, 0.0000, 0.0000, 89.0000, .drawdistance = 350.0); //des_substat_37
	CreateDynamicObject(18650, 349.9594, -1855.0803, 3.2551, 0.0000, 0.0000, 90.0999, .drawdistance = 350.0); //YellowNeonTube1
	mapobj_arraia[1] = CreateDynamicObject(18766, 340.7696, -1871.9964, 5.5038, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //Concrete10mx1mx5m
	SetObjectMaterial(mapobj_arraia[1], 0, 19058, "xmasboxes", "wrappingpaper1", 0x00000000);
	CreateDynamicObject(2232, 346.1196, -1871.3536, 4.0505, 0.0000, 0.0000, 178.7999, .drawdistance = 350.0); //MED_SPEAKER_4
	CreateDynamicObject(2232, 346.1196, -1871.3536, 5.2605, 0.0000, 0.0000, 178.7999, .drawdistance = 350.0); //MED_SPEAKER_4
	CreateDynamicObject(2232, 346.1196, -1871.3536, 6.4605, 0.0000, 0.0000, 178.7999, .drawdistance = 350.0); //MED_SPEAKER_4
	CreateDynamicObject(2232, 346.1196, -1871.3536, 7.6305, 0.0000, 0.0000, 178.7999, .drawdistance = 350.0); //MED_SPEAKER_4
	CreateDynamicObject(2232, 335.4320, -1871.1298, 4.0505, 0.0000, 0.0000, 178.7999, .drawdistance = 350.0); //MED_SPEAKER_4
	CreateDynamicObject(2232, 335.4320, -1871.1298, 4.0505, 0.0000, 0.0000, 178.7999, .drawdistance = 350.0); //MED_SPEAKER_4
	CreateDynamicObject(2232, 335.4320, -1871.1298, 5.2405, 0.0000, 0.0000, 178.7999, .drawdistance = 350.0); //MED_SPEAKER_4
	CreateDynamicObject(2232, 335.4320, -1871.1298, 6.4305, 0.0000, 0.0000, 178.7999, .drawdistance = 350.0); //MED_SPEAKER_4
	CreateDynamicObject(2232, 335.4320, -1871.1298, 7.6305, 0.0000, 0.0000, 178.7999, .drawdistance = 350.0); //MED_SPEAKER_4
	CreateDynamicObject(1463, 319.2709, -1848.2983, 2.6960, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 317.6510, -1848.2983, 2.6960, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 320.9811, -1848.2983, 2.6960, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 320.9811, -1852.1386, 2.6960, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 319.3210, -1852.1386, 2.6960, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 317.6710, -1852.1386, 2.6960, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 318.0576, -1852.6235, 3.3060, 0.0000, 0.0000, 90.7999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 318.0382, -1851.2237, 3.3060, 0.0000, 0.0000, 90.7999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 318.0183, -1849.7941, 3.3060, 0.0000, 0.0000, 90.7999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 317.9982, -1848.3641, 3.3060, 0.0000, 0.0000, 90.7999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 317.9865, -1847.5338, 3.3060, 0.0000, 0.0000, 90.7999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 320.6763, -1847.4960, 3.3060, 0.0000, 0.0000, 90.7999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 320.6963, -1848.9356, 3.3060, 0.0000, 0.0000, 90.7999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 320.7161, -1850.3557, 3.3060, 0.0000, 0.0000, 90.7999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 320.7349, -1851.7252, 3.3060, 0.0000, 0.0000, 90.7999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 320.7489, -1852.7253, 3.3060, 0.0000, 0.0000, 90.7999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 321.1224, -1850.7861, 3.9260, 0.0000, 0.0000, 1.2999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 319.6927, -1850.8187, 3.9260, 0.0000, 0.0000, 1.2999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 318.2833, -1850.8502, 3.9260, 0.0000, 0.0000, 1.2999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 318.2390, -1848.9112, 3.9260, 0.0000, 0.0000, 1.2999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 319.6086, -1848.8802, 3.9260, 0.0000, 0.0000, 1.2999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 321.0180, -1848.8486, 3.9260, 0.0000, 0.0000, 1.2999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(1463, 319.6771, -1849.8249, 4.4760, 0.0000, 0.0000, 91.0999, .drawdistance = 350.0); //DYN_WOODPILE2
	CreateDynamicObject(842, 319.8877, -1849.9104, 2.4183, 3.2000, 0.0000, 0.0000, .drawdistance = 350.0); //DEAD_TREE_14
	CreateDynamicObject(842, 321.5677, -1849.9104, 2.4183, 3.2000, 0.0000, 0.0000, .drawdistance = 350.0); //DEAD_TREE_14
	CreateDynamicObject(842, 320.3577, -1849.9136, 2.4782, 3.2000, 0.0000, 0.0000, .drawdistance = 350.0); //DEAD_TREE_14
	CreateDynamicObject(837, 319.3098, -1850.3034, 2.6343, 0.0000, 0.0000, -16.3999, .drawdistance = 350.0); //DEAD_TREE_1
	CreateDynamicObject(839, 318.7133, -1850.1629, 3.8221, 0.0000, 0.0000, -47.2999, .drawdistance = 350.0); //DEAD_TREE_11
	CreateDynamicObject(846, 312.9270, -1841.0030, 3.0789, 1.5999, 0.4000, -0.2999, .drawdistance = 350.0); //DEAD_TREE_18
	CreateDynamicObject(846, 312.9848, -1829.9476, 3.3877, 1.5999, 0.4000, -0.2999, .drawdistance = 350.0); //DEAD_TREE_18
	CreateDynamicObject(18691, 319.4424, -1850.0554, 1.3085, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //fire_large[Remover se Possivel Crash's]
	CreateDynamicObject(19083, 330.6783, -1855.1702, 3.3493, -19.5000, -93.3000, 2.4999, .drawdistance = 350.0); //LaserPointer5
	CreateDynamicObject(18090, 359.0124, -1826.9910, 5.5212, 0.3999, 0.0000, 0.0000, .drawdistance = 350.0); //Bar_BAR1
	CreateDynamicObject(1432, 352.3001, -1823.0981, 3.2342, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DYN_TABLE_2
	CreateDynamicObject(1432, 352.3001, -1827.0280, 3.2342, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DYN_TABLE_2
	CreateDynamicObject(1432, 351.7200, -1830.8081, 3.2342, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DYN_TABLE_2
	CreateDynamicObject(1432, 348.4400, -1827.5781, 3.2342, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DYN_TABLE_2
	CreateDynamicObject(1432, 348.4400, -1824.3779, 3.2342, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //DYN_TABLE_2
	CreateDynamicObject(18650, 347.7794, -1855.0841, 3.2551, 0.0000, 0.0000, 90.0999, .drawdistance = 350.0); //YellowNeonTube1
	CreateDynamicObject(18650, 345.6295, -1855.0880, 3.2551, 0.0000, 0.0000, 90.0999, .drawdistance = 350.0); //YellowNeonTube1
	CreateDynamicObject(18650, 343.4895, -1855.0919, 3.2551, 0.0000, 0.0000, 90.0999, .drawdistance = 350.0); //YellowNeonTube1
	CreateDynamicObject(18650, 341.2695, -1855.0960, 3.2551, 0.0000, 0.0000, 90.0999, .drawdistance = 350.0); //YellowNeonTube1
	CreateDynamicObject(18650, 339.0695, -1855.0999, 3.2551, 0.0000, 0.0000, 90.0999, .drawdistance = 350.0); //YellowNeonTube1
	CreateDynamicObject(18650, 336.8795, -1855.1030, 3.2551, 0.0000, 0.0000, 90.0999, .drawdistance = 350.0); //YellowNeonTube1
	CreateDynamicObject(18650, 334.6894, -1855.1069, 3.2551, 0.0000, 0.0000, 90.0999, .drawdistance = 350.0); //YellowNeonTube1
	CreateDynamicObject(18650, 332.3095, -1855.1113, 3.2551, 0.0000, 0.0000, 90.0999, .drawdistance = 350.0); //YellowNeonTube1
	CreateDynamicObject(18647, 344.8444, -1871.4752, 7.9855, 0.0000, 0.0000, 90.4000, .drawdistance = 350.0); //RedNeonTube1
	CreateDynamicObject(18647, 342.7044, -1871.4906, 7.9855, 0.0000, 0.0000, 90.4000, .drawdistance = 350.0); //RedNeonTube1
	CreateDynamicObject(18647, 340.5745, -1871.5054, 7.9855, 0.0000, 0.0000, 90.4000, .drawdistance = 350.0); //RedNeonTube1
	CreateDynamicObject(18647, 338.3846, -1871.5208, 7.9855, 0.0000, 0.0000, 90.4000, .drawdistance = 350.0); //RedNeonTube1
	CreateDynamicObject(18647, 336.6647, -1871.5323, 7.9855, 0.0000, 0.0000, 90.4000, .drawdistance = 350.0); //RedNeonTube1
	CreateDynamicObject(18647, 341.0544, -1871.5025, 7.9855, 0.0000, 0.0000, 90.4000, .drawdistance = 350.0); //RedNeonTube1
	CreateDynamicObject(19083, 330.8876, -1855.1572, 3.3607, -19.5000, -93.3000, 2.4999, .drawdistance = 350.0); //LaserPointer5
	CreateDynamicObject(19083, 351.0886, -1855.1697, 3.3500, -19.5000, -93.3000, 2.4999, .drawdistance = 350.0); //LaserPointer5
	CreateDynamicObject(19083, 350.9490, -1855.1783, 3.3424, -19.5000, -93.3000, 2.4999, .drawdistance = 350.0); //LaserPointer5
	CreateDynamicObject(19080, 350.7228, -1855.1420, 3.3341, -16.1000, -92.1999, 1.4000, .drawdistance = 350.0); //LaserPointer2
	CreateDynamicObject(19080, 350.4731, -1855.1512, 3.3248, -16.1000, -92.1999, 1.4000, .drawdistance = 350.0); //LaserPointer2
	CreateDynamicObject(19080, 331.0452, -1855.1488, 3.3898, -17.1000, -89.8999, 1.4000, .drawdistance = 350.0); //LaserPointer2
	CreateDynamicObject(19080, 331.3551, -1855.1414, 3.3893, -17.1000, -89.8999, 1.4000, .drawdistance = 350.0); //LaserPointer2
	CreateDynamicObject(19608, 340.8558, -1869.3020, 3.4040, 0.0000, 0.0000, -179.9999, .drawdistance = 350.0); //WoodenStage1
	CreateDynamicObject(19609, 339.7731, -1868.5180, 3.4198, 0.0000, 0.0000, 148.8999, .drawdistance = 350.0); //DrumKit1
	CreateDynamicObject(19611, 342.1221, -1860.8425, 3.4102, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //MicrophoneStand1
	CreateDynamicObject(19610, 342.1221, -1860.8425, 5.0402, 21.7000, 0.0000, -172.8000, .drawdistance = 350.0); //Microphone1
	CreateDynamicObject(19632, 355.6443, -1821.5898, 3.1178, 0.0000, 0.0000, 41.7999, .drawdistance = 350.0); //FireWood1
	CreateDynamicObject(19632, 355.8643, -1821.8358, 3.1178, 0.0000, 0.0000, 41.7999, .drawdistance = 350.0); //FireWood1
	CreateDynamicObject(19632, 355.7598, -1821.7060, 3.2578, 0.0000, 0.0000, 129.8997, .drawdistance = 350.0); //FireWood1/Fogueira
	CreateDynamicObject(1342, 354.3486, -1839.0263, 3.6991, 0.0000, 0.0000, 177.4000, .drawdistance = 350.0); //noodlecart_prop
	CreateDynamicObject(1341, 354.2340, -1841.8850, 3.6049, 0.0000, 0.0000, 174.9000, .drawdistance = 350.0); //icescart_prop
	CreateDynamicObject(1340, 354.0326, -1844.3032, 3.5377, 0.0000, 0.0000, 177.1999, .drawdistance = 350.0); //chillidogcart
	CreateDynamicObject(1290, 333.8652, -1817.6124, 9.0465, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //lamppost2
	CreateDynamicObject(1290, 333.8652, -1826.8024, 8.8565, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //lamppost2
	CreateDynamicObject(1290, 333.8652, -1836.3226, 8.6765, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //lamppost2
	CreateDynamicObject(1290, 349.1052, -1833.3126, 8.4865, 0.0000, 0.0000, 0.0000, .drawdistance = 350.0); //lamppost2

    printf("[MAPA %d]: Arraia (praia) loaded...", gm_count[COUNT_CREATEMAP]);
    gm_count[COUNT_CREATEMAP]++;
}

hook OnRemoveBuilding(playerid) 
{
	RemoveBuildingForPlayer(playerid, 3615, 337.4530, -1875.0000, 3.4062, 0.10);
	RemoveBuildingForPlayer(playerid, 3778, 337.4530, -1875.0000, 3.4062, 0.10);
    return 1;
}