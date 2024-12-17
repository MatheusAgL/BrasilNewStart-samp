    

stock Player_SpawnInOrg(playerid) {

    switch (GetPlayerOrg(playerid)) {
        case 1: {
            SetPlayerVirtualWorld(playerid, 0);
            SetPlayerInterior(playerid, 6);
            SetPlayerPos(playerid, 262.1967, 71.1788, 1003.2422);
            SetPlayerFacingAngle(playerid, 217.4001);
            Player_SetWanted(playerid, 0);
        }
        case 2:	{
            SetPlayerVirtualWorld(playerid, 0);
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, 328.1634,-1512.4167,36.0325);
            SetPlayerFacingAngle(playerid,51.1759);
            Player_SetWanted(playerid, 0);
        }
        case 3: {
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, -1346.8774,491.9250,11.2027);
            SetPlayerFacingAngle(playerid, 94.0289);
            Player_SetWanted(playerid, 0);
        }
        case 4: {
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 10);
            SetPlayerPos(playerid, 1164.6228,-1326.4603,-44.2836);
            SetPlayerFacingAngle(playerid,272.3499);
        }
        case 5: {
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, 1684.8771,-2098.8760,13.8343);
            SetPlayerFacingAngle(playerid,1.3213);
        }
        case 7: {
            SetPlayerVirtualWorld(playerid, 0);
            SetPlayerPos(playerid, 357.9465,173.5125,1008.3893);
            SetPlayerFacingAngle(playerid, 270.0905);
            SetPlayerInterior(playerid, 3);
        }
        case 8: {
            SetPlayerPos(playerid, 2281.2393,-2364.8765,13.5469);
            SetPlayerFacingAngle(playerid,135.4544);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
        }
        case 9: //Repórters Nascimento
        {
            SetPlayerPos(playerid, 745.6586,-1359.1908,13.5000);
            SetPlayerVirtualWorld(playerid,0);
            GivePlayerWeapon(playerid, WEAPON_CAMERA, 30);
            SetPlayerInterior(playerid, 0);
        }
        case 10: //Iluminati
        {
            SetPlayerPos(playerid, 1926.1920,-1573.9274,13.5833);
            SetPlayerFacingAngle(playerid, 358.8287);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
        }
        case 11://Policia Federal Nascimento
        {
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, 1124.7544,-2036.9777,69.8833);
            SetPlayerFacingAngle(playerid, 270.6968);
            SetPlayerVirtualWorld(playerid, 0);
            Player_SetWanted(playerid, 0);
        }
        case 12: //Mafia Italiana Nascimento
        {
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, 290.7737, -1376.5931, 13.9940);
            SetPlayerFacingAngle(playerid, 200.6792);
        }
        case 13://Yakuza Nascimento
        {
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, 689.8130,-1275.9388,13.5594);
            SetPlayerFacingAngle(playerid,270.8986);
        }
        case 14: //Groove Nascimento
        {
            SetPlayerPos(playerid, 2596.4023, -1486.7993, 16.5071);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
        }
        case 15: //Estado Islamico Nascimento
        {
            SetPlayerPos(playerid, -586.4482,-1060.9926,23.4999);
            SetPlayerFacingAngle(playerid, 235.6187);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
        }
        case 16: //P.R.F Nascimento
        {
            SetPlayerPos(playerid, 221.7815,111.4316,1010.2118);
            SetPlayerFacingAngle(playerid, 180.000);
            SetPlayerVirtualWorld(playerid, 16);
            SetPlayerInterior(playerid, 10);
        }
        case 17: //Familia do Norte Membros  Nascimento
        {
            SetPlayerPos(playerid, -201.4692, -1092.9031, 25.2115);
            SetPlayerFacingAngle(playerid, 87.7350);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
        }
        case 18: //BAIRRO-13 Nascimento
        {
            SetPlayerPos(playerid, 2808.3562,-1176.4606,25.3687);
            SetPlayerFacingAngle(playerid, 178.1808);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
        }
        case 19: //C.V Nascimento
        {
            SetPlayerPos(playerid, 1594.5566, -723.8428, 65.6841);
            SetPlayerFacingAngle(playerid, 270.0895);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
        }
        case 20: //Al-Qaeda Nascimento
        {
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, -329.7025,1536.6123,76.6117);
            SetPlayerFacingAngle(playerid,357.3199);
            SetPlayerVirtualWorld(playerid,0);
        }
        case 21: //P.C.C Nascimento
        {
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, 1325.5382, -3031.5596, 8.5836);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerFacingAngle(playerid,352.1631);
        }
        case 22: //Triads Nascimento
        {
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, 2770.6521,-1628.1273,12.1775);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerFacingAngle(playerid,179.4098);
        }
        case 24: //Máfia Cosa Nostra
        {
            SetPlayerPos(playerid, 479.5927,-1538.4657,19.3843);
            SetPlayerFacingAngle(playerid,117.8966);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
        }
        case 25: //Anarchy Nascimento
        {
            SetPlayerPos(playerid, 2485.6860,89.4010,26.7737);
            SetPlayerFacingAngle(playerid,174.3997);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
        }
        case 28: //Warlocks spawn
        {
            SetPlayerPos(playerid, 681.6184,-474.1958,16.5363);
            SetPlayerFacingAngle(playerid,1.5626);
            SetPlayerVirtualWorld(playerid,0);
            SetPlayerInterior(playerid, 0);
        }
        case 33://Policia Civil
        {
            SetPlayerVirtualWorld(playerid, 0);
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, 1684.5236,- 1343.3313, 17.4368);
            SetPlayerFacingAngle(playerid,359.0599);
        }
        case 34:	//CORE
        {
            SetPlayerVirtualWorld(playerid, 0);
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, -50.0843,-298.3511,5.4297);
            SetPlayerFacingAngle(playerid,359.0599);
        }
        // Cívil:
        default: {
            SetPlayerPos(playerid, 1685.7766,-2241.0327,13.5469); // Alterar o Spawn Civil
            SetPlayerFacingAngle(playerid, 180.4025);
            SetPlayerVirtualWorld(playerid, 0);
            SetPlayerInterior(playerid, 0);
        }
    }
    SetCameraBehindPlayer(playerid);
}