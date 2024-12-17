#if defined _inc_gangzones
	#endinput
#endif
#define _inc_gangzones true

#include <gangzone_entry>
#include <gangzone_textdraws>
#include <safezone>
#include <mercenaryzone>

hook OnGameModeInit()
{
	OnLoadSafeZones();
	OnLoadMercenaryZones();

	return 1;
}

hook OnGameModeExit() 
{
	OnDestroySafeZones();

	return 1;
}

CMD:ajustargz(playerid, params[])
{
	if (Dev_GetNivel(playerid) < DEV_DELTA)
		return SendClientMessage(playerid, -1, "Você não é da equipe de desenvolvimento.");

	new Float:pos[4];
	if (sscanf(params, "ffff", pos[0], pos[1], pos[2], pos[3]))
		return SendClientMessage(playerid, -1, "Modo de uso: /ajustargz (minX) (minY) (maxX) (maxY)");

	new 
		Float:x,
		Float:y,
		Float:z;

	GetPlayerPos(playerid, x, y, z);

	GangZoneDestroy(GZ_GetID());
	GZ_Create(x - pos[0], y - pos[1], x + pos[2], y + pos[3]);
    GZ_SetMinX(x - pos[0]);
    GZ_SetMinY(y - pos[1]);
    GZ_SetMaxX(x + pos[2]);
    GZ_SetMaxY(y + pos[3]);
    GangZoneShowForPlayer(playerid, GZ_GetID(), COLOR_GRAY);

	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você ajustou a GZ, continue ajustando ou salve /salvargz.");
	return 1;
}

CMD:salvargz(playerid, params[])
{
	if (Dev_GetNivel(playerid) < DEV_DELTA)
		return SendClientMessage(playerid, -1, "Você não é da equipe de desenvolvimento.");

	new type, type_name[30], name[35];
	if (sscanf(params, "ds[35]", type, name)) {
		SendClientMessage(playerid, -1, "Modo de uso: /salvagz (tipo da GZ) (nome da GZ)");
		SendClientMessage(playerid, COLOR_GRAY, "TIPOS: 1 (SafeZone) || 2 (MercenaryZone)");
		return 1;
	}

	if (GZ_GetID() == -1)
		return SendClientMessage(playerid, -1, "Você não está ajustando nenhuma gangzone (/ajustargz).");

	new interior = GetPlayerInterior(playerid),
		world = GetPlayerVirtualWorld(playerid);

	switch (type) {
		case GZ_TYPE_SAFEZONE: {
			format(type_name, sizeof(type_name), ""C_SAFEZONE"SafeZone");
			SafeZone_Insert(name, GZ_GetMinX(), GZ_GetMinY(), GZ_GetMaxX(), GZ_GetMaxY(), interior, world);
		}
		case GZ_TYPE_MERCENARYZONE: {
			format(type_name, sizeof(type_name), ""C_MERCENARYZONE"MercenaryZone");
			MerceZone_Insert(name, -1, interior, world);
		}
		default: return SendClientMessage(playerid, -1, "Você digitou um tipo inválido.");
	}

	GangZoneDestroy(GZ_GetID());
	GZ_SetID(-1);

	new string[128];
	format(string, sizeof(string), "DevCmd: %s criou uma %s"C_LIGHTGREEN" com o nome de %s.", PlayerName[playerid], type_name, name);
	Staff_ChatToAll(COLOR_LIGHTGREEN, string, DONO);
	return 1;
}

CMD:destruirgz(playerid, params[]) 
{
	if (Dev_GetNivel(playerid) < DEV_DELTA)
		return SendClientMessage(playerid, -1, "Você não é da equipe de desenvolvimento.");

	new type;
	if (sscanf(params, "d", type)) {
		SendClientMessage(playerid, -1, "Modo de uso: /destruirgz (tipo da GZ)");
		SendClientMessage(playerid, COLOR_GRAY, "TIPOS: 1 (SafeZone) || 2 (MercenaryZone)");
		return 1;
	}

	switch (type) {
		case GZ_TYPE_SAFEZONE: 
		{
			new safe = SafeZone_IsPlayerIn(playerid);
			if (safe == -1)
				return SendClientMessage(playerid, -1, "Você não está em nenhuma SafeZone.");

			SafeZone_Destroy(safe);
		}
		case GZ_TYPE_MERCENARYZONE: 
		{
			new mercenaryzone = MerceZone_IsPlayerIn(playerid);
			if (mercenaryzone == -1)
				return SendClientMessage(playerid, -1, "Você não está em nenhuma MercenaryZone.");

			MerceZone_Destroy(mercenaryzone);
		}
		default: return SendClientMessage(playerid, -1, "Você digitou um tipo inválido.");
	}
	return 1;
}