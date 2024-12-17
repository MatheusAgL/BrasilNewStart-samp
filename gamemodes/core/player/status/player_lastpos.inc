#include <YSI_Coding\y_hooks>

hook OnPlayerLogin(playerid)
{
	SetPVarInt(playerid, "varLastPos", gettime() + 20);

	SendClientMessage(playerid, COLOR_LIGHTRED, "Você pode voltar para a última posição que desconectou, use: /cpos.");
	SendClientMessage(playerid, COLOR_LIGHTRED, "Após 20 segundos você não poderá mais usar esse comando!");

	return 1;
}

stock saveLastPlayerPos(playerid)
{
	// Caso o servidor tiver dando GMX, não salvar a posição...
	if (Server_IsRestarting()) 
        return 1;

    // Caso estiver preso...
	if (Player_GetJailed(playerid) > 0 || Player_InEvent(playerid))
		return 1;

	new Float:playerPos[4],
		virtual_world = GetPlayerVirtualWorld(playerid),
		player_interior = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
	GetPlayerFacingAngle(playerid, playerPos[3]);

	if (IsPlayerInAnyVehicle(playerid))
		playerPos[1] += 0.3;

#if _inc_paintball_system
	if (Player_GetPaintball(playerid) != INVALID_PAINTBALL_ID)
		playerPos[0] = 0.00;
#endif
	
	format(LastPosInfo[playerid][lastPosString], 200, "%f|%f|%f|%f|%d|%d|%d|%d", playerPos[0], playerPos[1], playerPos[2], playerPos[3], player_interior, 
		virtual_world, Player_GetInHouse(playerid), GetPlayerCurrentInt(playerid));

	return true;
}

stock Load_LastPlayerPos(playerid)
{
	if (Player_GetJailed(playerid) > 0 || GetPVarInt(playerid, "LastPosLoadded") == 1)
		return false;

	new
		Float:player_save_pos[4],
		player_save_interior,
		player_save_vw,
		player_save_int_house,
		player_save_int_business;

	sscanf(LastPosInfo[playerid][lastPosString], "P< | >ffffiiii", player_save_pos[0], player_save_pos[1], player_save_pos[2], player_save_pos[3],
	player_save_interior, player_save_vw, player_save_int_house, player_save_int_business);

	LastPosInfo[playerid][lastPos][0]		= player_save_pos[0];
	LastPosInfo[playerid][lastPos][1] 		= player_save_pos[1];
	LastPosInfo[playerid][lastPos][2]		= player_save_pos[2];
	LastPosInfo[playerid][lastPos][3]		= player_save_pos[3];
	LastPosInfo[playerid][lastInterior]		= player_save_interior;
	LastPosInfo[playerid][lastVirtual] 		= player_save_vw;
	LastPosInfo[playerid][lastHouseEntered]	= player_save_int_house;
	LastPosInfo[playerid][lastStoreEntered]	= player_save_int_business;

	if (LastPosInfo[playerid][lastPos][0] == 0.0) 
		return false;

	SetPlayerInterior(playerid, LastPosInfo[playerid][lastInterior]);
	SetPlayerPos(playerid, LastPosInfo[playerid][lastPos][0],LastPosInfo[playerid][lastPos][1],LastPosInfo[playerid][lastPos][2]);
	SetPlayerFacingAngle(playerid, LastPosInfo[playerid][lastPos][3]);
	SetPlayerVirtualWorld(playerid, LastPosInfo[playerid][lastVirtual]);
	Player_SetInHouse(playerid, LastPosInfo[playerid][lastHouseEntered]);
    SetPlayerCurrentInt(playerid, LastPosInfo[playerid][lastStoreEntered]);
	SetCameraBehindPlayer(playerid);

	// Cartão batido
	if (IsACop(playerid))
	{
		PlayerInfo[playerid][pSkinServico] = 280;
		OnDuty[playerid] = 1;
		EmpregoDuty[playerid] = 2;
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkinServico]);
		SetPlayerToTeamColor(playerid);
	}

	if (LastPosInfo[playerid][lastInterior] > 0) FreezeThePlayer(playerid);
	else TogglePlayerControllable(playerid, true);

	SetPVarInt(playerid, "LastPosLoadded", 1);
	SetPVarInt(playerid, "varLastPos", 0);
	ShowPlayerMessage(playerid, "~w~Sua ultima posicao foi ~g~~h~carregada~w~...", 5000);
	
	return true;
}

CMD:cpos(playerid) 
{
	if (gettime() > GetPVarInt(playerid, "varLastPos") || GetPVarInt(playerid, "varLastPos") == 0)
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "Você já carregou sua posição ou o tempo expirou.");

	Load_LastPlayerPos(playerid);
	return 1;
}