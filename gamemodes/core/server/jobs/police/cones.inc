/*

    Sistema de cones

    Última modificação: 28/11/2020
    Responsável: Theus_Crazzy

*/

#define     MAX_CONE                30              // Máximo de cones no servidor
#define     OBJECT_TYPE_CONE        1               // Tipo do objeto
#define     _SYSTEM_CONE_on         true            // Garantindo o sistema ativo

enum coneInfo
{
	coneObject,
	Float:conePos[3],
	coneOwner[MAX_PLAYER_NAME],
};

new
	ConeInfo[MAX_CONE][coneInfo],
	Iterator:IterCone<MAX_CONE>
;

stock destroyCone(id)
{
    if (Iter_Contains(IterCone, id))
	{
		Iter_Remove(IterCone, id);

		DestroyDynamicObject(ConeInfo[id][coneObject]);
	}
}

stock countPlayerCones(playerid)
{
	new count;

	foreach(new id : IterCone)
	{
	    if (Iter_Contains(IterCone, id))
		{
			if (!strcmp(PlayerName[playerid], ConeInfo[id][coneOwner])) count++;
		}
	}
	return count;
}

stock IsPlayerOwnerCone(playerid, coneid)
{
	if (Admin_GetNivel(playerid) || !strcmp(PlayerName[playerid], ConeInfo[coneid][coneOwner]) || GetPlayerOrg(playerid) == ID_ORG_GOVERNO)
		return true;

	return false;
}

stock createPlayerCone(playerid, modelid = 1237)
{
	new Float:x,
		Float:y,
		Float:z,
		Float:a;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	new id = Iter_Free(IterCone),
	    string[124];

	if (id != -1)
	{
    	Iter_Add(IterCone, id);

    	ConeInfo[id][conePos][0] = x;
    	ConeInfo[id][conePos][1] = y;
    	ConeInfo[id][conePos][2] = z;

    	GameTextForPlayer(playerid, "~g~~h~Voce colocou um cone", 5000, 5);

    	SendClientMessage(playerid, -1, "Você colocou um cone, para remover use: /rcone próximo ao cone.");

		new MapZone:zone = GetMapZoneAtPoint2D(x, y);
		new zone_name[MAX_MAP_ZONE_NAME];
		GetMapZoneName(zone, zone_name);

    	format(string, sizeof(string), "<< COPOM >> %s: %s, %s colocou um cone em %s.", NomeORG(playerid), GetPlayerCargo(playerid), PlayerName[playerid], zone_name);
    	SendCopMessage(COLOR_LIGHTRED, string);

        ConeInfo[id][coneObject] = CreateDynamicObject(modelid, x, y, z - 1.0, 0.0, 0.0, a, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

        format(ConeInfo[id][coneOwner], MAX_PLAYER_NAME, PlayerName[playerid]);
	}
	return id;
}

CMD:cone(playerid)
{
	if (!IsACop(playerid)) return SendClientMessage(playerid, -1, "Você não tem autoridade para usar esse comando.");

    if (countPlayerCones(playerid) >= 5 && PlayerInfo[playerid][pVIP] < 8)
		return SendClientMessage(playerid, -1, "Você poderá colocar 10 cones caso for Sócio Extreme.");

	if (countPlayerCones(playerid) >= 10) return SendClientMessage(playerid, -1, "Você atingiu o limite de 10 cones.");

	if (createPlayerCone(playerid) == -1) return SendClientMessage(playerid, -1, "O servidor está com o máximo de cones criados (50)...");

	return true;
}

CMD:rcone(playerid)
{
    new coneid = getPositionObject(playerid, OBJECT_TYPE_CONE);
       
    if (coneid == -1) return SendClientMessage(playerid, -1, "Você não está próximo de um cone.");
    
    if (!IsPlayerOwnerCone(playerid, coneid)) return SendClientMessage(playerid, -1, "Você não tem autorização para remover esse cone.");

	new string[128];

	new MapZone:zone = GetMapZoneAtPoint2D(ConeInfo[coneid][conePos][0], ConeInfo[coneid][conePos][1]);
	new zone_name[MAX_MAP_ZONE_NAME];
	GetMapZoneName(zone, zone_name);

    format(string, sizeof(string), "<< COPOM >> %s, %s removeu o cone de %s em %s.", GetPlayerCargo(playerid), PlayerName[playerid],
	ConeInfo[coneid][coneOwner], zone_name);
   	SendCopMessage(COLOR_LIGHTRED, string);

	destroyCone(coneid);

	return true;
}

CMD:removercones(playerid)
{
    if (Admin_GetNivel(playerid) < MODERADOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    new count = DestroyAllCones();

    new string[92];

    format(string, sizeof(string), "AdmCmd: %s, %s removeu todos os cones do servidor | Total: %d.", Staff_GetPositionName(playerid), PlayerName[playerid], count);
    Staff_ChatToAll(COLOR_LIGHTRED, string);

    return true;
}

DestroyAllCones()
{
    new i = 0, c = 0;

    while (i < MAX_CONE)
    {
        if (Iter_Contains(IterCone, i))
        {
            Iter_Remove(IterCone, i);

            DestroyDynamicObject(ConeInfo[i][coneObject]);

            ++c;
        }
        i++;
    }
    return c;
}