#if defined _inc_merceZonezones
	#endinput
#endif
#define _inc_merceZonezones true

#include <YSI_Coding\y_hooks>

#define COLOR_MERCENARYZONE 		0x9AFBD890
#define C_MERCENARYZONE 			"{9AFBD8}"

#define MAX_MERCE_ZONES				10

enum ENUM_MERCE_ZONE {
	merceZoneID,
	gangZoneType,
	merceZoneGZ,
	merceZoneOwner,
	merceZoneName[35],
	merceZoneInt,
	merceZoneWorld,
	merceZoneMoney,
	Text3D:merceZoneLabel,
	
	merceZoneTimer,
	merceZoneCooldown,
	merceZonePoints[MAX_ORGS],
};
static MercenaryZone[MAX_MERCE_ZONES][ENUM_MERCE_ZONE];
static Timer:timer_mercenary_zone[MAX_PLAYERS];

stock MerceZone_GetID(merceZone)
	return MercenaryZone[merceZone][merceZoneID];

stock MerceZone_SetID(merceZone, id)
	MercenaryZone[merceZone][merceZoneID] = id;

stock MerceZone_GetName(merceZone) {
	new name[35];
	format(name, sizeof(name), MercenaryZone[merceZone][merceZoneName]);
	return name;
}

stock MerceZone_SetName(merceZone, const name[])
	format(MercenaryZone[merceZone][merceZoneName], 35, name);

stock MerceZone_GetOwner(merceZone)
	return MercenaryZone[merceZone][merceZoneOwner];

stock MerceZone_SetOwner(merceZone, id)
	MercenaryZone[merceZone][merceZoneOwner] = id;

stock MerceZone_GetInterior(merceZone)
	return MercenaryZone[merceZone][merceZoneInt];

stock MerceZone_SetInterior(merceZone, interior)
	MercenaryZone[merceZone][merceZoneInt] = interior;

stock MerceZone_GetWorld(merceZone)
	return MercenaryZone[merceZone][merceZoneWorld];

stock MerceZone_SetWorld(merceZone, world)
	MercenaryZone[merceZone][merceZoneWorld] = world;

stock MerceZone_GetPoints(merceZone, org)
	return MercenaryZone[merceZone][merceZonePoints][org];

stock MerceZone_SetPoints(merceZone, org, points)
	MercenaryZone[merceZone][merceZonePoints][org] = points;

stock MerceZone_GetFinishTimer(merceZone)
	return MercenaryZone[merceZone][merceZoneTimer];

stock MerceZone_SetFinishTimer(merceZone, timer)
	MercenaryZone[merceZone][merceZoneTimer] = timer;

stock MerceZone_GetTimer(merceZone)
	return MercenaryZone[merceZone][merceZoneCooldown];

stock MerceZone_SetTimer(merceZone, timer)
	MercenaryZone[merceZone][merceZoneCooldown] = timer;

stock MerceZone_GetMoney(merceZone)
	return MercenaryZone[merceZone][merceZoneMoney];

stock MerceZone_SetMoney(merceZone, money)
	MercenaryZone[merceZone][merceZoneMoney] = money;

// ------------------------ Sistema de dominação mercenários ------------------------
new Iterator: MercenaryZones<MAX_MERCE_ZONES>;

static 
		Statement: stmt_insertMercenaryZone,
		Statement: stmt_selectMercenaryZone,
		Statement: stmt_deleteMercenaryZone;

hook OnMySQLConnected() 
{
	static const query_insertMercenaryZone[] = 
		"INSERT INTO `merce_zone` (`id`, `name`, `owner`, `interior`, `world`) VALUES (NULL, ?, ?, ?, ?)"
	;
	stmt_insertMercenaryZone = MySQL_PrepareStatement(MySQL_Handle, query_insertMercenaryZone);

	static const query_selectMercenaryZone[] = 
		"SELECT id, name, owner, interior, world FROM `merce_zone` LIMIT ?"
	;
	stmt_selectMercenaryZone = MySQL_PrepareStatement(MySQL_Handle, query_selectMercenaryZone);

	static const query_deleteMercenaryZone[] = 
		"DELETE FROM `merce_zone` WHERE `id` = ?"
	;
	stmt_deleteMercenaryZone = MySQL_PrepareStatement(MySQL_Handle, query_deleteMercenaryZone);
	return 1;
}

stock OnLoadMercenaryZones()
{
	inline const OnLoadMercenaryZones_MySQL() 
	{
		new 
			id,
			name[35],
			owner,
			Float:min_x,
			Float:min_y,
			Float:max_x,
			Float:max_y,
			interior,
			world;

		MySQL_BindResultInt(stmt_selectMercenaryZone, 0, id);
		MySQL_BindResult(stmt_selectMercenaryZone, 1, name);
		MySQL_BindResultInt(stmt_selectMercenaryZone, 2, owner);
		MySQL_BindResultFloat(stmt_selectMercenaryZone, 3, min_x);
		MySQL_BindResultFloat(stmt_selectMercenaryZone, 4, min_y);
		MySQL_BindResultFloat(stmt_selectMercenaryZone, 5, max_x);
		MySQL_BindResultFloat(stmt_selectMercenaryZone, 6, max_y);
		MySQL_BindResultInt(stmt_selectMercenaryZone, 7, interior);
		MySQL_BindResultInt(stmt_selectMercenaryZone, 8, world);

		while (MySQL_Statement_FetchRow(stmt_selectMercenaryZone)) {
			MerceZone_Create(id, name, owner, interior, world);
		}

		new count = Iter_Count(MercenaryZones);
		printf("[TerritoryZones]: %d loaded...", count);
	}
	MySQL_BindInt(stmt_selectMercenaryZone, 0, MAX_MERCE_ZONES);
	MySQL_ExecuteParallel_Inline(stmt_selectMercenaryZone, using inline OnLoadMercenaryZones_MySQL);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	new orgs[3] = {25, 28, 33},
		player_merceZone = MerceZone_IsPlayerIn(playerid);

	if (player_merceZone != -1 && 
		PlayerIsMercenario(playerid)) {

		new string[128],
			// bodypart = DanoInfo[playerid][danoBodypart],
			player_org = GetPlayerOrg(playerid),
			points = MerceZone_GetPoints(player_merceZone, player_org);

		points = points + 10;
		MerceZone_SetPoints(player_merceZone, player_org, points);
		MercenaryZone_VaultAdd(playerid, random(300) + 100);

		format(string, sizeof(string), "[%s]: %s foi morto por %s | +10 ponto(s) para %s.", 
		MerceZone_GetName(player_merceZone), PlayerName[playerid], PlayerName[killerid], points, GetOrgName(player_org));

		for(new org; org < sizeof(orgs); org++)
			SendMembersMessage(orgs[org], COLOR_LIGHTBLUE, string); 
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (newkeys & KEY_YES)
	{
		if (PlayerToPoint(2.0, playerid, 503.2586, -74.9241, 998.7651))
		{
			new merceZone = MerceZone_IsPlayerIn(playerid);

			if (merceZone != INVALID_ITERATOR_SLOT) 
			{
				new string[128];
				format(string, sizeof(string), "%s", MerceZone_GetName(merceZone));

				inline D_MercenaryZone(did, ddialogid, dresponse, dlistitem, string:dtext[]) {
					#pragma unused did, ddialogid, dtext

					if (!dresponse)
						return 1;

					switch (dlistitem)
					{
						case 0: MerceZone_Donimate(playerid);
						case 1: {
							if (GetPlayerOrg(playerid) != MerceZone_GetOwner(merceZone))
								return SendClientMessage(playerid, COLOR_GRAD, "Sua organização precisa dominar esse bar para os membros recolher dinheiro.");

							if (gettime() < GetPVarInt(playerid, #varFlood_MerceZone)) 
								return SendClientMessage(playerid, COLOR_GRAD, "Aguarde 2 minutos para recolher dinheiro novamente.");

							SetPVarInt(playerid, #varFlood_MerceZone, gettime() + (2 * 60));

							new money = random(3000) + 1000;

							SendMsgF(playerid, -1, "Você pegou $%s em dinheiro no %s", getFormatText(money), MerceZone_GetName(merceZone));

							MercenaryZone_VaultRemove(playerid, money);
							Player_AddMoney(playerid, money);
						}
					}
				}

				Dialog_ShowCallback(
					playerid, using inline D_MercenaryZone, DIALOG_STYLE_LIST, string, "Dominar o bar\nPegar dinheiro", "Selecionar", "Fechar"
				);
			}
		}
	}
	return 1;
}

stock MerceZone_Insert(const name[], owner, interior, world) {
	
	inline const OnInsertMercenaryZone() {
		new id = cache_insert_id();
		MerceZone_Create(id, name, owner, interior, world);
	}
	MySQL_Bind(stmt_insertMercenaryZone, 0, name);
	MySQL_BindInt(stmt_insertMercenaryZone, 1, owner);
	MySQL_BindInt(stmt_insertMercenaryZone, 2, interior);
	MySQL_BindInt(stmt_insertMercenaryZone, 3, world);
	MySQL_ExecuteThreaded_Inline(stmt_insertMercenaryZone, using inline OnInsertMercenaryZone);
}

stock MerceZone_Create(id, const name[], owner = -1, interior = 0, world = 0) {
	new merceZone = Iter_Free(MercenaryZones);

	if (merceZone != INVALID_ITERATOR_SLOT) {
		Iter_Add(MercenaryZones, merceZone);

		MerceZone_SetID(merceZone, id);
		MerceZone_SetName(merceZone, name);
		MerceZone_SetOwner(merceZone, owner);
		MerceZone_SetInterior(merceZone, interior);
		MerceZone_SetWorld(merceZone, world);

		MercenaryZone[merceZone][merceZoneLabel] = 
			CreateDynamic3DTextLabel("_", -1, 503.2586, -74.9241, 998.7651, 20.0, .worldid = world);

		MerceZone_UpdateLabel(merceZone);

		return 1;
	}
	return 0;
}

stock MerceZone_Destroy(merceZone) {
	new bool:created = Iter_Contains(MercenaryZones, merceZone);

	if (created) {
		Iter_Remove(MercenaryZones, merceZone);

		MySQL_BindInt(stmt_deleteMercenaryZone, 0, MerceZone_GetID(merceZone));
		MySQL_ExecuteThreaded(stmt_deleteMercenaryZone);
	}
}

stock MerceZone_UpdateLabel(merceZone)
{
	new string[128],
		owner = MerceZone_GetOwner(merceZone),
		money = MerceZone_GetMoney(merceZone);

	format(string, sizeof(string), "%s\n%s\n"C_MONEY"$%s",
			MerceZone_GetName(merceZone),
			GetOrgName(owner),
			getFormatText(money));
			
	UpdateDynamic3DTextLabelText(MercenaryZone[merceZone][merceZoneLabel], -1, string);
	return 1;
}

stock MerceZone_GetWinner(merceZone)
{
	new orgs[3] = {25, 28, 33},
		points,
		winner;

	for(new org; org < sizeof(orgs); org++) {
		if (points > points || points == 0) {
			points = MerceZone_GetPoints(merceZone, orgs[org]);
			winner = orgs[org];
		}
	}
	return winner;
}

stock MerceZone_IsPlayerIn(playerid) {
	new world = GetPlayerVirtualWorld(playerid);

	foreach (new merceZone : MercenaryZones) {
		if (world == MerceZone_GetWorld(merceZone)) return merceZone;
	}
	return INVALID_ITERATOR_SLOT;
}

stock MerceZones_HasWar() {
	new timer;

	foreach (new merceZone : MercenaryZones) {
		timer = MerceZone_GetFinishTimer(merceZone);

		if (timer > 0)
			return true;
	}
	return false;
}

timer Timer_UpdateMercenaryZone[1000](merceZone)
{
	new player_merceZone,
		player_org,
		points,
		finish_timer = MerceZone_GetFinishTimer(merceZone),
		gz_name[35];

	format(gz_name, sizeof(gz_name), MerceZone_GetName(merceZone));

	foreach (new playerid : Player) 
	{
		player_merceZone = 	MerceZone_IsPlayerIn(playerid);
		player_org = 		GetPlayerOrg(playerid);

		if (player_merceZone == merceZone && 
			PlayerIsMercenario(playerid) &&
			finish_timer > 0) {

			points = MerceZone_GetPoints(player_merceZone, player_org);
			points = points + 1;

			MerceZone_SetPoints(player_merceZone, player_org, points);
			MercenaryZone_VaultAdd(player_merceZone, 50);

			MerceZone_UpdateLabel(merceZone);
			GZ_ShowTextDraws(playerid, player_merceZone, GZ_TYPE_MERCENARYZONE, gz_name, finish_timer);
		} else {
			GZ_HideTextDraws(playerid);
		}
	}

	finish_timer = finish_timer - 1;
	MerceZone_SetFinishTimer(merceZone, finish_timer);

	if (finish_timer < 1) {
		new winner = MerceZone_GetWinner(merceZone),
			owner = MerceZone_GetOwner(merceZone);

		SendMsgAllF(GetOrgHexColor(winner), "<< %s tomaram o territorio %s de %s >>", GetOrgName(winner), MerceZone_GetName(merceZone), GetOrgName(owner));

		foreach (new playerid : Player) 
		{
			player_merceZone = 	MerceZone_IsPlayerIn(playerid);
			player_org = 		GetPlayerOrg(playerid);

			if (player_merceZone == merceZone && 
				PlayerIsMercenario(playerid)) {
				GZ_HideTextDraws(playerid);
			}
		}
		MerceZone_SetOwner(merceZone, winner);
		MerceZone_SetTimer(merceZone, gettime() + (60 * 10));
		MerceZone_UpdateLabel(merceZone);
		stop timer_mercenary_zone[merceZone];
	}
}

stock MerceZone_TakeTerritory(playerid, merceZone) 
{
	new 
		player_org = GetPlayerOrg(playerid),
		owner = MerceZone_GetOwner(merceZone);

	SendMsgAllF(GetPlayerColor(playerid), "<< %s e os %s esta tentando dominar o %s de %s >>", 
	PlayerName[playerid], GetOrgName(player_org), MerceZone_GetName(merceZone), GetOrgName(owner));

	timer_mercenary_zone[merceZone] = repeat Timer_UpdateMercenaryZone(merceZone);
	return 1;
}

stock MerceZone_Donimate(playerid) 
{
	new merceZone = MerceZone_IsPlayerIn(playerid);

	if (!PlayerIsMercenario(playerid))
		return SendClientMessage(playerid, -1, "Você não é um mercenário ou policial civil.");
		
	if (merceZone == INVALID_ITERATOR_SLOT)
		return SendClientMessage(playerid, -1, "Você não está em um bar de mercenário");

	new merceZone_time = MerceZone_GetTimer(merceZone);
	if (gettime() < merceZone_time)
		return SendClientMessage(playerid, -1, "Houve uma tomada de territorio recente, aguarde para dominar novamente.");

	if (MerceZones_HasWar())
		return SendClientMessage(playerid, -1, "Está tendo uma tomada de territorio no momento.");

	MerceZone_SetFinishTimer(merceZone, 180);
	MerceZone_TakeTerritory(playerid, merceZone);
	
	return 1;
}

stock MercenaryZone_VaultAdd(playerid, value)
{
	new merceZone = MerceZone_IsPlayerIn(playerid);
	
	if (merceZone != INVALID_ITERATOR_SLOT) {
		new merceZone_Money = MerceZone_GetMoney(merceZone);
		MerceZone_SetMoney(merceZone, merceZone_Money + value);

		MerceZone_UpdateLabel(merceZone);
	}
}

stock MercenaryZone_VaultRemove(playerid, value)
{
	new merceZone = MerceZone_IsPlayerIn(playerid);
	
	if (merceZone != INVALID_ITERATOR_SLOT) {
		new merceZone_Money = MerceZone_GetMoney(merceZone);
		MerceZone_SetMoney(merceZone, merceZone_Money - value);

		MerceZone_UpdateLabel(merceZone);
	}
}