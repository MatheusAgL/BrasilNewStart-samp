//-----------------------------------------

new Float:AreaSeguraOrg[MAX_ORGS][4] = {
	{0.0000,0.0000,0.0000,0.0000},
	{1523.8119,-1721.5165,1611.7308,-1602.0750}, // pm - min x, min y 1
	{284.6048,-1554.0007,375.2052,-1479.1616}, // rota min x min y 2
	{-1527.6348,290.8291,-1218.3865,522.8195}, // exerc min x min y 3
	{0.0000,0.0000,0.0000,0.0000}, // 4
	{1658.4454,-2154.4346,1728.4171,-2080.0933}, // aztec min x min y 5
	{0.0000,0.0000,0.0000,0.0000}, // 6
	{1410.7466,-1841.8036,1550.5868,-1742.4976}, // gov min x min y 7
	{2239.5461,-2393.7759,2323.6665,-2324.0867}, // hit min x min y 8
	{718.9508,-1384.1144,787.2522,-1330.4933}, // report min x min y 9
	{0.0000,0.0000,0.0000,0.0000}, // 10
	{1103.9110,-2080.4241,1283.4061,-2003.5499}, // pf min x min y 11
	{191.8291,-1473.4901,292.9357,-1356.8059}, // russ min x min y 12
	{648.5413,-1308.7638,718.5140,-1239.1038}, // yak min x min y 13
	{2443.6848,-1721.9268,2541.3545,-1634.1069}, // groove min x min y 14
	{-628.5129,-1089.6508,-497.7702,-1003.1295}, // farc min x min y 15
	{803.6131,-1317.7037,929.4780,-1157.4913}, // prf min x min y 16
	{2441.4961,-1563.9080,2496.7688,-1514.4957}, // ballas max x max y 17
	{2785.2576,-1211.7186,2863.4060,-1158.4613}, // vagos min x min y 18
	{2129.1816,-1210.9178,2164.7776,-1141.3579}, // 19 - C.V
	{-399.6885,1494.9127,-259.6729,1593.2446}, // EI min x min y 20
	{2206.8049,-1476.8264,2278.6931,-1394.1588}, // PCC min x min y 21
	{2728.6487,-1656.4609,2826.6453,-1572.7949}, // triad min x min y 22
	{0.0000,0.0000,0.0000,0.0000}, // 23
	{465.0863,-1576.5061,507.0816,-1450.1678}, // CN min x min y 24
	{2466.0330,46.6351,2524.3198,104.5241}, // Sons min x min y 25
	{0.0000,0.0000,0.0000,0.0000}, // 26
	{0.0000,0.0000,0.0000,0.0000}, // 27
	{650.0812,-479.5851,725.8665,-438.6147}, // warlocks min x min y 28
	{0.0000,0.0000,0.0000,0.0000}, // 29
	{0.0000,0.0000,0.0000,0.0000}, // 30
	{0.0000,0.0000,0.0000,0.0000}, // 31
	{0.0000,0.0000,0.0000,0.0000}, // 32
	{1621.4852,-1386.4565,1707.7137,-1314.3687}, // PC min x min y 33
	{-80.7684,-397.3397,17.7846,-216.0517} // CORE 34
};

new CoresOrg[MAX_ORGS] = {0xFFFFFFAA, 0x605DFFAA, 0x737373AA, 0x00660CAA, 0xFFFFFFAA, 0x2641FEAA, 0xFFFFFFAA, 0x0095FFAA,
	0xBDBDBDAA, 0xDFB77BAA, 0xFFFFFFAA, 0x917662AA, 0xD85300AA, 0x18C09FAA, 0x177517AA, 0x1B1B1BAA, 0xFFFF44AA, 0x99311EAA,
	0x010701AA, 0xF80505AA, 0xEE2323AA, 0x7F994CAA, 0xA4D1FFAA, 0x024566AA, 0x33FFFFAA, 0x576176AA, 0xFFFF99AA, 0xFFFFFFAA,
	0xA3283DAA, 0xFFFFFFAA, 0xFFFFFFAA, 0xFFFFFFAA, 0xFFFFFFAA, 0x996600AA, 0x333300AA};

new GZOrg[MAX_ORGS];

stock CreateServerHQZones()
{
	for(new org; org < MAX_ORGS; org++)
	{
		if(AreaSeguraOrg[org][0] == 0.00) {
			GZOrg[org] = -1;
			continue;
		}
	    GZOrg[org] = GangZoneCreate(AreaSeguraOrg[org][0], AreaSeguraOrg[org][1], AreaSeguraOrg[org][2], AreaSeguraOrg[org][3]);
	}
}

stock ShowPlayerHQZones(playerid)
{
	for(new org; org < MAX_ORGS; org++)
		if(GZOrg[org] != -1)
	    	GangZoneShowForPlayer(playerid, GZOrg[org], CoresOrg[org] - 0x60);
}

stock CanPlayerDriveVehicleOrg(playerid, vehicleid, orgid = -1) {
	if(orgid == -1)
		orgid = GetVehicleOrgID(vehicleid);

	if(orgid == -1 || GetPlayerOrg(playerid) == orgid)
		return true;

	new Float:pos[3];
	GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
	
	return !(pos[0] >= AreaSeguraOrg[orgid][0] && pos[0] <= AreaSeguraOrg[orgid][2] && pos[1] >= AreaSeguraOrg[orgid][1] && pos[1] <= AreaSeguraOrg[orgid][3]);
}

hook OnPlayerDeathFinished(playerid) {

	new playerorg = GetPlayerOrg(playerid);
	if(CofreOrg[playerorg][TrainingOrg] > 0 && IsPlayerInAreaSeguraOrg(playerid, playerorg)) 
		return 1;

	return 1;
}

stock IsPlayerInAreaSeguraOrg(playerid, orgid) {
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	
	return orgid != -1 && pos[0] >= AreaSeguraOrg[orgid][0] && pos[0] <= AreaSeguraOrg[orgid][2] && pos[1] >= AreaSeguraOrg[orgid][1] && pos[1] <= AreaSeguraOrg[orgid][3];
}

stock GetVehicleOrgID(vehicleid) {
	if (VehicleInfo[vehicleid][vhType] == VH_TYPE_ORG)
		return VehicleInfo[vehicleid][vhInfoID];

	return -1;
}

stock IsVehicleInAreaSeguraOrg(vehicleid) {
	new orgid = GetVehicleOrgID(vehicleid);
	if(orgid == -1)
		return false;

	new Float:pos[3];
	GetVehiclePos(playerid, pos[0], pos[1], pos[2]);
	
	return pos[0] >= AreaSeguraOrg[orgid][0] && pos[0] <= AreaSeguraOrg[orgid][2] && pos[1] >= AreaSeguraOrg[orgid][1] && pos[1] <= AreaSeguraOrg[orgid][3];
}