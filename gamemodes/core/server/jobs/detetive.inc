
#include <YSI_Coding\y_hooks>





new TempoProc[MAX_PLAYERS];

stock Search_GetTime(playerid)
    return TempoProc[playerid];



timer timerProcurar[150](playerid, procuradoid)
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(procuradoid, x, y, z);

	new Float:
		dist = GetPlayerDistanceFromPoint(playerid, x, y, z);

    if (gettime() >= TempoProc[playerid] || (GetPVarInt(playerid, "MecanicoCliente") == procuradoid && dist <= 3.0) || GetPVarInt(procuradoid, "EfeitoHeroina"))
    {
        SetPVarInt(playerid, "Searching", 0);
        stop timer_procurar[playerid];
        HidePlayerSearch(playerid);
        SetPVarInt(playerid, "varProcura", INVALID_PLAYER_ID);

        DestroyDynamicObject(GetPVarInt(playerid, "objectProcurar"));
        SetPVarInt(playerid, "objectProcurar", -1);
        RemovePlayerMapIcon(playerid, 99);

        if (GetPVarInt(playerid, "MecanicoEmCorrida") && GetPVarInt(playerid, "MecanicoCliente") == procuradoid && dist <= 3.0)
        {
            new money = GetPVarInt(playerid, "MecanicoCorrida");
			Player_RemoveMoney(procuradoid, money);
			Player_AddMoney(playerid, money);
            SendMsgF(playerid, COLOR_LIGHTBLUE, "Você chegou ao cliente %s e recebeu $%s para atendê-lo.", PlayerName[procuradoid], getFormatText(money));
            SendMsgF(procuradoid, COLOR_LIGHTBLUE, "O mecânico %s chegou ao local para atender você.", PlayerName[playerid]);

            LimparDadosMecanico(playerid);
            LimparDadosMecanico(procuradoid);
        }
        return 1;
    }

    if (!Inventory_IsOpen(playerid))
    {
        ShowPlayerSearch(playerid, procuradoid);
    }

    DestroyDynamicObject(GetPVarInt(playerid, "objectProcurar"));
    new Float:distLimit = GetPVarFloat(playerid, "SearchDistanceLimit");
    if (dist < distLimit)
    {
        SetPVarInt(playerid, "objectProcurar", CreateDynamicObject(19607, x, y, z + 3.0, 0.0, 0.0, 0.0, -1, -1, playerid));
        SetPlayerMapIcon(playerid, 99, x, y, z, 0, 0x0000FFFF, MAPICON_GLOBAL);
        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
    }
    else
    {
        SetPVarInt(playerid, "objectProcurar", -1);
        RemovePlayerMapIcon(playerid, 99);
    }
    return 1;
}

hook OnPlayerEnterCheckpoint(playerid) {
    if (GetPlayerCP(playerid) == 597)
	{
		new id = GetPVarInt(playerid, "varProcura");
		if (id != INVALID_PLAYER_ID) {
			HidePlayerSearch(playerid);
			DisablePlayerCheckpoint(playerid);

            new string[128];

			format(string, sizeof string, "* Você encontrou %s ORG: %s", PlayerName[id], GetOrgName(GetPlayerOrg(id)));
			SendClientMessage(playerid, TEAM_BALLAS_COLOR, string);

			// Cancelando /procurar
			stop timer_procurar[playerid];
			SetPVarInt(playerid, "varProcura", INVALID_PLAYER_ID);
			SetPlayerCP(playerid, CP_NULL);
		}
	}
    return 1;
}

CMD:procurar(playerid, params[])
{
    if (!PlayerIsDetetive(playerid) && !IsACop(playerid) && GetPlayerOrg(playerid) != 8 && GetPlayerOrg(playerid) != 22)
		return SendClientMessage(playerid, -1, "Você não é um detetive, policial ou assassino.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /procurar (id do jogador)");

	if (gettime() < GetPVarInt(playerid, #VarFlood12) && PlayerInfo[playerid][pDetSkill] < 401)
	    return SendClientMessage(playerid, COLOR_GRAD, #Você só poderá usar o comando novamente após 20 segundos!);

    if (!Player_Logado(idPlayer)) 
		return SendClientMessage(playerid, -1, "Este jogador não está conectado no servidor.");

	if ((Admin_GetNivel(idPlayer) || Helper_GetNivel(idPlayer)) && Staff_GetWorking(idPlayer))
		return SendClientMessage(playerid, -1, "Você não pode procurar staffs em modo trabalho.");

	if (idPlayer == playerid) 
		return true;

	if (GetPlayerInterior(idPlayer) > 0)
		return SendClientMessage(playerid, COLOR_YELLOW, "Este player está em um interior!");

	if(GetPVarInt(idPlayer, "EfeitoHeroina"))
		return SendClientMessage(playerid, -1, "Esse jogador está sob efeito de heroína e não pode ser localizado");

	new Float:distLimit = 550.0;
	if(PlayerInfo[playerid][pDetSkill] <= 50)
	{
		TempoProc[playerid] = gettime() + 01*60;
		distLimit += 15.0;
	}
	else if(PlayerInfo[playerid][pDetSkill] <= 100) {
		TempoProc[playerid] = gettime() + 03*60;
		distLimit += 30.0;
	}
	else if(PlayerInfo[playerid][pDetSkill] <= 200) {
		TempoProc[playerid] = gettime() + 09*60;
		distLimit += 45.0;
	}
	else if(PlayerInfo[playerid][pDetSkill] <= 400) {
		TempoProc[playerid] = gettime() + 15*60;
		distLimit += 60.0;
	} else {
		TempoProc[playerid] = gettime() + 15*60;
		distLimit += 60.0;
	}

	SetPVarInt(playerid, #VarFlood12, gettime() + 20);
	SetPVarInt(playerid, "varProcura", idPlayer);
	SetPVarInt(playerid, "Searching", 1);
	SetPVarFloat(playerid, "SearchDistanceLimit", distLimit);

	stop timer_procurar[playerid];
	timer_procurar[playerid] = repeat timerProcurar[Timer:150](playerid, idPlayer);
	SetPlayerCP(playerid, 597);

	new string[75];
	format(string, sizeof string, "* Você está procurando %s ORG: %s", PlayerName[idPlayer], GetOrgName(GetPlayerOrg(idPlayer)));
	SendClientMessage(playerid, TEAM_BALLAS_COLOR, string);

	format(string, sizeof string, "%s esta procurando %s", PlayerName[playerid], PlayerName[idPlayer]);
	server_log("procurar", string);

	PlayerInfo[playerid][pDetSkill] ++;

	if (PlayerInfo[playerid][pDetSkill] == 50)
		return SendClientMessage(playerid, COLOR_YELLOW, "* Seu nível de detetive agora é 2, Você pode procurar e encontrar mais rápido e achar a maior distância.");

	else if (PlayerInfo[playerid][pDetSkill] == 100)
 		return SendClientMessage(playerid, COLOR_YELLOW, "* Seu nível de detetive agora é 3, Você pode procurar e encontrar mais rápido e achar a maior distância.");

	else if (PlayerInfo[playerid][pDetSkill] == 200)
		return SendClientMessage(playerid, COLOR_YELLOW, "* Seu nível de detetive agora é 4, Você pode procurar e encontrar mais rápido e achar a maior distância.");

	else if (PlayerInfo[playerid][pDetSkill] == 400)
		return SendClientMessage(playerid, COLOR_YELLOW, "* Seu nível de detetive agora é 5, Você pode procurar e encontrar mais rápido e achar a maior distância.");

	return true;
}
alias:procurar("p")