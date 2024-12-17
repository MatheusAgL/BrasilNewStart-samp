

stock Player_LevelUp(playerid)
{
    new gstring			[128];
	new nxtlevel 		= PlayerInfo[playerid][pLevel]+1;
	new expquantidade   = nxtlevel*8;

    PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);
	Player_SetNivel(playerid, Player_GetNivel(playerid) + 1);
    PlayerInfo[playerid][pExp] 		 -= expquantidade;

    CheckConquista(playerid, Conquista_Nivel);

	format(gstring, sizeof(gstring), "~g~Nivel adquirido~n~~w~Agora seu Nivel e %d", nxtlevel);
	GameTextForPlayer(playerid, gstring, 5000, 1);

	SendClientMessage(playerid, -1, "| ****************** {00AA00}NÍVEL ADQUIRIDO {FFFFFF}******************");

	format(gstring, 128, "| Você agora é nível: {00AA00}%d", PlayerInfo[playerid][pLevel]);
	SendClientMessage(playerid, -1, gstring);

	SendClientMessage(playerid, -1, "| ****************** {00AA00}NÍVEL ADQUIRIDO {FFFFFF}******************");
}

stock Player_SetCadeia(playerid, jailid, jailtime, const respCadeia[], const motivoCadeia[], orgid) {
	Player_SetWanted(playerid, 0);

	ResetPlayerWeapons(playerid);

	Jail_SetJailed(playerid, jailid);
	Jail_SetTime(playerid, jailtime);

	Jail_SetAjusted(playerid, false);
	AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;

	// Informações da prisão
	Jail_SetResp(playerid, respCadeia);
	Jail_SetDate(playerid, GetCurrentDateHour(ONLY_CURRENT_ALL));
	Jail_SetReason(playerid, motivoCadeia);

	Jail_SetOrg(playerid, orgid);
}