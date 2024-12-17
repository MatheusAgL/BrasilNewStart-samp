/**--------------------------------------------------------------------------**\
 ______ ______  ______     __  ______  ______  ______     ______  __  ______ __  __
/\  == /\  == \/\  __ \   /\ \/\  ___\/\  ___\/\__  _\   /\  ___\/\ \/\__  _/\ \_\ \
\ \  _-\ \  __<\ \ \/\ \ _\_\ \ \  __\\ \ \___\/_/\ \/   \ \ \___\ \ \/_/\ \\ \____ \
 \ \_\  \ \_\ \_\ \_____/\_____\ \_____\ \_____\ \ \_\    \ \_____\ \_\ \ \_\\/\_____\
  \/_/   \/_/ /_/\/_____\/_____/\/_____/\/_____/  \/_/     \/_____/\/_/  \/_/ \/_____/

						 ==========================
		                    Brasil Play Start
                              ® 2013 - 2017
                        Módulo: Spray tags - pixações
						 ==========================

\**--------------------------------------------------------------------------**/

#define MAX_SPRAYS_TAGS     (100)

hook OnPlayerLogin(playerid) {
	BarSprayTag[playerid] = CreatePlayerProgressBar(playerid, 221.00, 269.00, 194.50, 5.20, 0xFFFFFFFF, 100.0, BAR_DIRECTION_RIGHT);
}

enum e_SpraysTagsEnum {
	spray_owner,
	spray_color,
	spray_pixador[MAX_PLAYER_NAME],
	Text3D:spray_text,
}

//  [ Tags Variavel ]
new sprayTags[MAX_SPRAYS_TAGS][e_SpraysTagsEnum];

// [ Player Variavel ]
new Float:pixSprayTag[MAX_PLAYERS];

new Float:g_SprayTagsPos[MAX_SPRAYS_TAGS][3] = {
	{2046.4062, -1635.8438, 13.5859375},
	{2066.4297, -1652.4766, 14.28125},
	{2102.1953, -1648.7578, 13.5859375},
	{2162.7812, -1786.0703, 14.1875},
	{2034.3984, -1801.6719, 14.546875},
	{1910.1641, -1779.6641, 18.75},
	{1837.1953, -1814.1875, 4.3359375},
	{1837.6641, -1640.3828, 13.7578125},
	{1959.3984, -1577.7578, 13.7578125},
	{2074.1798, -1579.1484, 14.03125},
	{2182.2344, -1467.8984, 25.554688},
	{2132.2344, -1258.0938, 24.054688},
	{2233.9531, -1367.6172, 24.53125},
	{2224.7656, -1193.0625, 25.835938},
	{2119.2031, -1196.6172, 24.632812},
	{1974.0853, -1351.1641, 24.5625},
	{2093.7578, -1413.4453, 24.117188},
	{1969.5938, -1289.6953, 24.5625},
	{1966.9453, -1174.7266, 20.039062},
	{1911.8672, -1064.3984, 25.1875},
	{2281.461, -1118.9609, 27.007812},
	{2239.7812, -999.75, 59.757812},
	{2122.6875, -1060.8984, 25.390625},
	{2062.7188, -996.46094, 48.265625},
	{2076.7266, -1071.1328, 27.609375},
	{2399.414, -1552.0312, 28.75},
	{2353.539, -1508.2109, 24.75},
	{2394.1016, -1468.3672, 24.78125},
	{2841.3672, -1312.9609, 18.820312},
	{2820.3438, -1190.9766, 25.671875},
	{2766.086, -1197.1497, 69.07031},
	{2756.0078, -1388.125, 39.460938},
	{2821.2344, -1465.0938, 16.539062},
	{2767.7812, -1621.1875, 11.234375},
	{2767.7578, -1819.9453, 12.2265625},
	{2667.8906, -1469.1328, 31.679688},
	{2612.9297, -1390.7734, 35.429688},
	{2536.2188, -1352.7656, 31.085938},
	{2580.9453, -1274.0938, 46.59375},
	{2603.1562, -1197.8125, 60.992188},
	{2542.9531, -1363.2422, 31.765625},
	{2462.2656, -1541.4141, 25.421875},
	{2522.461, -1478.7422, 24.164062},
	{2346.5156, -1350.7812, 24.28125},
	{2322.4531, -1254.4141, 22.921875},
	{2273.0156, -1687.4297, 14.96875},
	{2422.9022, -1682.2969, 13.9921875},
	{2576.8203, -1143.2734, 48.203125},
	{2621.5078, -1092.2031, 69.796875},
	{2797.9219, -1097.6953, 31.0625},
	{1549.8906, -1714.5234, 15.1015625},
	{1332.1328, -1722.3047, 14.1875},
	{1724.7344, -1741.5, 14.1015625},
	{1767.2109, -1617.5391, 15.0390625},
	{1799.1328, -1708.7656, 14.1015625},
	{1498.6328, -1207.3516, 24.679688},
	{1448.2344, -1755.8984, 14.5234375},
	{1732.7344, -963.0781, 41.4375},
	{1746.75, -1359.7734, 16.210938},
	{1519.4219, -1010.9453, 24.609375},
	{1687.2266, -1239.125, 15.8125},
	{1783.9688, -2156.539, 14.3125},
	{1574.7190, -2691.8828, 13.6015625},
	{1118.9062, -2008.2422, 75.02344},
	{1850.0078, -1876.8359, 14.359375},
	{1889.2422, -1982.5078, 15.7578125},
	{1950.6172, -2034.3984, 14.09375},
	{1936.8828, -2134.9062, 14.21875},
	{1808.3438, -2092.2656, 14.21875},
	{1624.625, -2296.2422, 14.3125},
	{1071.1406, -1864.7891, 14.09375},
	{2065.4375, -1897.2344, 13.609375},
	{2763.0, -2012.1094, 14.1328125},
	{2379.3203, -2166.2188, 24.945312},
	{2134.3281, -2011.2031, 10.515625},
	{2392.3594, -1914.5703, 14.7421875},
	{2430.3281, -1997.9062, 14.7421875},
	{2587.3203, -2063.5234, 4.609375},
	{2704.1953, -1966.6875, 13.7578125},
	{2489.2422, -1959.0703, 13.7578125},
	{2273.8984, -2265.8047, 14.5425},
	{2173.5938, -2165.1875, 15.3046875},
	{2273.1953, -2529.1172, 8.515625},
	{2704.2266, -2144.3047, 11.8203125},
	{2794.5312, -1906.8125, 14.671875},
	{2812.9375, -1942.0703, 11.0625},
	{2874.5, -1909.3828, 8.390625},
	{1295.1797, -1465.2188, 10.28125},
	{1271.4844, -1662.3203, 20.25},
	{810.5703, -1797.5703, 13.6171875},
	{730.4453, -1482.0078, 2.25},
	{947.4844, -1466.7166, 17.242188},
	{482.625, -1761.5859, 5.9140625},
	{399.0078, -2066.8828, 11.234375},
	{466.97656, -1283.0234, 16.320312},
	{583.46094, -1502.1094, 16.0},
	{944.27344, -985.8203, 39.296875},
	{1072.9062, -1012.7969, 35.515625},
	{1206.25, -1162.0, 23.875},
	{1098.8125, -1292.5469, 17.140625}
};

//{1448.2344, -1755.8984, 14.5234375}, // Spray Tag - HQ Governo

stock GetSprayTagPos(sprayid, &Float:x, &Float:y, &Float:z) {
	if (sprayid >= 0 && sprayid < sizeof (g_SprayTagsPos)) {
		x = g_SprayTagsPos[sprayid][0];
		y = g_SprayTagsPos[sprayid][1];
		z = g_SprayTagsPos[sprayid][2];
	}
	return 1;
}

stock saveSpraysTag(sprayid) {
	new string[128];
	mysql_format(MySQL_Handle, string, sizeof (string), "UPDATE sprays SET `owner` = '%d', `color` = '%d', `pixador` = '%s' WHERE `id` = '%d'",
	sprayTags[sprayid][spray_owner], sprayTags[sprayid][spray_color], sprayTags[sprayid][spray_pixador], sprayid);
	mysql_tquery(MySQL_Handle, string);
}

stock loadSpraysTags() {
    new rows;

	mysql_query(MySQL_Handle, "SELECT * FROM sprays ORDER BY `id` ASC");
	cache_get_row_count(rows);

	if(rows > 0) {
	    for(new i = 0; i < rows; i++) {
			onLoadSprayTag(i);
		}
	}
    printf("[SPRAY]: %d spray tags foram carregadas...", rows);
}

stock SetSprayTagOwner( id, pixador[], orgid, color) {
    sprayTags[id][spray_owner] = orgid;
    sprayTags[id][spray_color] = color;
    format(sprayTags[id][spray_pixador], MAX_PLAYER_NAME, pixador);
    
    saveSpraysTag( id );
    
	new string[128];
	format(string, sizeof string, "Spray Tag\nPichador: %s\nOrganização dona: {%06x}%s", pixador, (color >>> 8), GetOrgName(orgid));
	UpdateDynamic3DTextLabelText(sprayTags[id][spray_text], 0xFFFFFF99, string);
}

CALLBACK: onLoadSprayTag(row)
{
    new get_owner, get_color, sprayid;
	cache_get_value_int(row, "id", sprayid);

	cache_get_value_name_int(row, "owner", get_owner);
	cache_get_value_name_int(row, "color", get_color);

    sprayTags[sprayid][spray_owner] = get_owner;
    sprayTags[sprayid][spray_color] = get_color;
    new pixador[24];
    cache_get_value_name(row, "pixador", pixador);
    format(sprayTags[sprayid][spray_pixador], 24, pixador);

	new string[128];
	new Float:x, Float:y, Float:z;
	format(string, sizeof string, "Spray Tag\nPichador: %s\nOrganização dona: {%06x}%s", sprayTags[sprayid][spray_pixador], (sprayTags[sprayid][spray_color] >>> 8), GetOrgName(sprayTags[sprayid][spray_owner]));

    GetSprayTagPos(sprayid, x, y, z);
	sprayTags[sprayid][spray_text] = CreateDynamic3DTextLabel(string, 0xFFFFFF99, x, y, z, 12.0);
}

stock GetPlayerSprayTag(playerid) {

	new Float:x, Float:y, Float:z;
	new Float:tx, Float:ty, Float:tz;
	for (new spray; spray != sizeof (g_SprayTagsPos); spray++) {

		GetPlayerPos( playerid, x, y, z);
		GetXYInFrontOfPlayer( playerid, x, y, 1.6 ) ;
		GetSprayTagPos( spray, tx, ty, tz ) ;
		
		if ( GetPointDistanceToPoint(x, y, z, tx, ty, tz) < 1.6 ) {
		    return spray ;
		}
	}
	return -1;
}

stock GetOrgSprayTags(orgid) {

	new count;
	for (new spray; spray != sizeof (g_SprayTagsPos); spray++) {
		if ( sprayTags[spray][spray_owner] == orgid) {
			count++;
		}
	}
	return count;
}

processSpraysTags(playerid) {

	new KEY:keys, KEY:ud, KEY:lr;
	GetPlayerKeys(playerid, keys, ud, lr);
	if (GetPlayerWeapon(playerid) == WEAPON:41 && GetPlayerAmmo(playerid) && keys & KEY_FIRE && keys & KEY_HANDBRAKE) {
	
	    new sprayid = GetPlayerSprayTag(playerid);
	    
	    if (sprayid == -1) {
	        return 0;
	    }
	    new orgid = GetPlayerOrg(playerid);
	    
	    if (sprayTags[sprayid][spray_owner] == orgid) {
	        return 0;
	    }
	    
	    if (pixSprayTag[playerid] < 5.0) {
	    	SetPlayerProgressBarValue(playerid, BarSprayTag[playerid], 0.0);
	    	ShowPlayerProgressBar(playerid, BarSprayTag[playerid]);
		}
	    
	    if ( GetPlayerAmmo(playerid) < GetPVarInt(playerid, "ammoSpray")) {
	    	pixSprayTag[playerid] += 15.0;
		}
	    SetPlayerProgressBarValue(playerid, BarSprayTag[playerid], pixSprayTag[playerid]);
	    SetPVarInt(playerid, "ammoSpray", GetPlayerAmmo(playerid));
	    
	    if (pixSprayTag[playerid] >= 100.0) {
	        new string[128];

	        new MapZone:zone = GetPlayerMapZone(playerid);
			new zone_name[MAX_MAP_ZONE_NAME];

			GetMapZoneName(zone, zone_name);

	        format(string, sizeof string, "~w~O jogador ~g~~h~%s ~w~pichou uma parede dos ~r~%s~w~ na regiao de %s!", PlayerName[playerid], GetOrgName(sprayTags[sprayid][spray_owner]), zone_name);
	        SendFamilyTextMessage(orgid, string, 7000);
	        format(string, sizeof string, "~w~O jogador ~r~~h~%s ~w~pichou uma parede de voces na regiao de %s!", PlayerName[playerid], zone_name);
	        SendFamilyTextMessage(sprayTags[sprayid][spray_owner], string, 7000);
	    
	        SetSprayTagOwner( sprayid, PlayerName[playerid], orgid, GetPlayerColor(playerid));
	        pixSprayTag[playerid] = 0.0;
	        format(string, sizeof string, "i~n~i~n~i~n~~p~%s~n~~n~~b~~h~%d ~w~de ~b~~h~%d ~w~Pichadas~n~~g~$100",
			GetOrgName(orgid), GetOrgSprayTags(orgid), MAX_SPRAYS_TAGS);
			GameTextForPlayer(playerid, string, 5000, 3);
			
			Player_RemoveMoney(playerid, 100);
			PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
			HidePlayerProgressBar(playerid, BarSprayTag[playerid]);
			
			// Rank Pixador
			PlayerInfo[playerid][pPixador] ++;
	    }
	} else {
	    if (pixSprayTag[playerid] > 0.0) {
	        HidePlayerProgressBar(playerid, BarSprayTag[playerid]);
	    }
        pixSprayTag[playerid] = 0.0;
	}
	return 1;
}






