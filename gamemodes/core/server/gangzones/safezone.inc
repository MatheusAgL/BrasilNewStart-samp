#if defined _inc_safezones
	#endinput
#endif
#define _inc_safezones true

#include <YSI_Coding\y_hooks>

#define COLOR_SAFEZONE 		0x9AFBD890
#define C_SAFEZONE 			"{9AFBD8}"
#define MAX_SAFE_ZONES		10

enum ENUM_SAFE_ZONE {
	safeID,
	safeGZ,
	safeArea,
	safeName[35],
	Float:safeMinX,
	Float:safeMinY,
	Float:safeMaxX,
	Float:safeMaxY,
	gzInt,
	gzWorld,
};
static SafeZone[MAX_SAFE_ZONES][ENUM_SAFE_ZONE];
static bool:playerInSafeZone[MAX_PLAYERS];
static Timer:timer_safe_set[MAX_PLAYERS];

stock SafeZone_GetID(safe)
	return SafeZone[safe][safeID];

stock SafeZone_SetID(safe, id)
	SafeZone[safe][safeID] = id;

stock SafeZone_SetName(safe, const name[])
	format(SafeZone[safe][safeName], 35, name);

stock SafeZone_SetMinX(safe, Float:min_x)
	SafeZone[safe][safeMinX] = min_x;

stock SafeZone_SetMinY(safe, Float:min_y)
	SafeZone[safe][safeMinY] = min_y;

stock SafeZone_SetMaxX(safe, Float:max_x)
	SafeZone[safe][safeMaxX] = max_x;

stock SafeZone_SetMaxY(safe, Float:max_y)
	SafeZone[safe][safeMaxY] = max_y;

stock SafeZone_SetInterior(safe, interior)
	SafeZone[safe][gzInt] = interior;

stock SafeZone_SetWorld(safe, world)
	SafeZone[safe][gzWorld] = world;

stock IsPlayerInSafeZone(playerid)
	return playerInSafeZone[playerid];

// ------------------------ Sistema de Zona segura ------------------------
new Iterator: SafeZones<MAX_SAFE_ZONES>;

static 
		Statement: stmt_insertSafeZone,
		Statement: stmt_selectSafeZone,
		Statement: stmt_deleteSafeZone;

hook OnMySQLConnected() 
{
	static const query_insertSafeZone[] = 
		"INSERT INTO `safe_zone` (`id`, `name`, `min_x`, `min_y`, `max_x`, `max_y`, `interior`, `world`) VALUES (NULL, ?, ?, ?, ?, ?, ?, ?)"
	;
	stmt_insertSafeZone = MySQL_PrepareStatement(MySQL_Handle, query_insertSafeZone);

	static const query_selectSafeZone[] = 
		"SELECT id, name, min_x, min_y, max_x, max_y, interior, world FROM `safe_zone` LIMIT ?"
	;
	stmt_selectSafeZone = MySQL_PrepareStatement(MySQL_Handle, query_selectSafeZone);

	static const query_deleteSafeZone[] = 
		"DELETE FROM `safe_zone` WHERE `id` = ?"
	;
	stmt_deleteSafeZone = MySQL_PrepareStatement(MySQL_Handle, query_deleteSafeZone);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	playerInSafeZone[playerid] = false;
	return 1;
}

timer Timer_SetPlayerSafeZone[1000 * 60](playerid) {
	SendClientMessage(playerid, -1, "Você foi definido como protegido por area neutra");
	return playerInSafeZone[playerid] = true;
}

hook OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart)
{
	if (IsPlayerInSafeZone(playerid)) {
		if (issuerid != INVALID_PLAYER_ID && 
			(GoChase[issuerid] != playerid &&
			GoChase[playerid] != issuerid)) {
	    	ShowPlayerDialog(issuerid, 0, DIALOG_STYLE_MSGBOX, "SafeZone", ""C_LIGHTWHITE"Voce nao pode causar "C_RED"DANO "C_LIGHTWHITE"em jogadores que estao em uma "C_SAFEZONE"SafeZone", "OK","");
	    	return 0;
		}
	}

	if (issuerid != INVALID_PLAYER_ID) {
		if (IsPlayerInSafeZone(issuerid)) {
			ShowPlayerDialog(issuerid, 0, DIALOG_STYLE_MSGBOX, "SafeZone", ""C_LIGHTWHITE"Voce nao pode causar "C_RED"DANO "C_LIGHTWHITE"pois esta em uma "C_SAFEZONE"SafeZone", "OK","");
		}
	}

	return 1;
}

hook OnPlayerEnterDynamicArea(playerid, areaid) 
{
	foreach (new safe : SafeZones) {
		if (areaid == SafeZone[safe][safeArea]) {
			ShowPlayerBaloonInfo(playerid, "Voce entrou em uma ~g~area segura~w~, em 1 minuto estara ~g~~h~protegido.", 5000);
			timer_safe_set[playerid] = defer Timer_SetPlayerSafeZone(playerid);
		}
	}
	return 1;
}

hook OnPlayerLeaveDynamicArea(playerid, areaid) 
{
	foreach (new safe : SafeZones) {
		if (areaid == SafeZone[safe][safeArea]) {
			stop timer_safe_set[playerid];
			ShowPlayerBaloonInfo(playerid, "Voce saiu de uma ~g~area segura", 5000);
			playerInSafeZone[playerid] = false;
		}
	}
	return 1;
}

stock OnLoadSafeZones()
{
	inline const OnLoadSafeZones_MySQL() 
	{
		new id,
			name[35],
			Float:min_x,
			Float:min_y,
			Float:max_x,
			Float:max_y,
			interior,
			world;

		MySQL_BindResultInt(stmt_selectSafeZone, 0, id);
		MySQL_BindResult(stmt_selectSafeZone, 1, name);
		MySQL_BindResultFloat(stmt_selectSafeZone, 2, min_x);
		MySQL_BindResultFloat(stmt_selectSafeZone, 3, min_y);
		MySQL_BindResultFloat(stmt_selectSafeZone, 4, max_x);
		MySQL_BindResultFloat(stmt_selectSafeZone, 5, max_y);
		MySQL_BindResultInt(stmt_selectSafeZone, 6, interior);
		MySQL_BindResultInt(stmt_selectSafeZone, 7, world);

		while (MySQL_Statement_FetchRow(stmt_selectSafeZone)) {
			SafeZone_Create(id, name, min_x, min_y, max_x, max_y, interior, world);
		}

		new count = Iter_Count(SafeZones);
		printf("[SafeZones]: %d carregadas...", count);
	}
	MySQL_BindInt(stmt_selectSafeZone, 0, MAX_SAFE_ZONES);
	MySQL_ExecuteParallel_Inline(stmt_selectSafeZone, using inline OnLoadSafeZones_MySQL);
	return 1;
}

stock OnDestroySafeZones()
{
	foreach (new safe : SafeZones) {
		GangZoneDestroy(SafeZone[safe][safeGZ]);
		DestroyDynamicArea(SafeZone[safe][safeArea]);
	}
	return 1;
}

stock SafeZone_Insert(const name[], Float: min_x, Float: min_y, Float: max_x, Float: max_y, interior, world) {
	
	inline const OnInsertSafeZone() {
		new id = cache_insert_id();
		SafeZone_Create(id, name, min_x, min_y, max_x, max_y, interior, world);
	}
	MySQL_Bind(stmt_insertSafeZone, 0, name);
	MySQL_BindFloat(stmt_insertSafeZone, 1, min_x);
	MySQL_BindFloat(stmt_insertSafeZone, 2, min_y);
	MySQL_BindFloat(stmt_insertSafeZone, 3, max_x);
	MySQL_BindFloat(stmt_insertSafeZone, 4, max_y);
	MySQL_BindInt(stmt_insertSafeZone, 5, interior);
	MySQL_BindInt(stmt_insertSafeZone, 6, world);
	MySQL_ExecuteThreaded_Inline(stmt_insertSafeZone, using inline OnInsertSafeZone);
}

stock SafeZone_Create(id, const name[], Float:min_x, Float:min_y, Float:max_x, Float:max_y, interior = 0, world = 0) {
	new safe = Iter_Free(SafeZones);

	if (safe != INVALID_ITERATOR_SLOT) {
		Iter_Add(SafeZones, safe);

		SafeZone_SetID(safe, id);
		SafeZone_SetName(safe, name);
		SafeZone_SetMinX(safe, min_x);
		SafeZone_SetMinY(safe, min_y);
		SafeZone_SetMaxX(safe, max_x);
		SafeZone_SetMaxY(safe, max_y);
		SafeZone_SetInterior(safe, interior);
		SafeZone_SetWorld(safe, world);

		if (interior == 0)
			SafeZone[safe][safeGZ] = GangZoneCreate(min_x, min_y, max_x, max_y);

		GangZoneShowForAll(SafeZone[safe][safeGZ], COLOR_SAFEZONE);
		SafeZone[safe][safeArea] = CreateDynamicRectangle(min_x, min_y, max_x, max_y, world, interior);

		return 1;
	}
	return 0;
}

stock SafeZone_Destroy(safe) {
	new bool:created = Iter_Contains(SafeZones, safe);

	if (created) {
		Iter_Remove(SafeZones, safe);
		GangZoneDestroy(SafeZone[safe][safeGZ]);
		DestroyDynamicArea(SafeZone[safe][safeArea]);

		MySQL_BindInt(stmt_deleteSafeZone, 0, SafeZone_GetID(safe));
		MySQL_ExecuteThreaded(stmt_deleteSafeZone);
	}
}

stock SafeZone_IsPlayerIn(playerid) {
	foreach (new safe : SafeZones) if (IsPlayerInDynamicArea(playerid, SafeZone[safe][safeArea])) return safe;
	
	return -1;
}

stock SafeZones_ShowForPlayer(playerid) {
	foreach (new safe : SafeZones) GangZoneShowForPlayer(playerid, SafeZone[safe][safeGZ], COLOR_SAFEZONE);
}