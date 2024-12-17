#include <YSI_Coding\y_hooks>

CALLBACK:VozDePrisaoo(playerid, copid)
{
	if (!ProxDetectorS(50.0, playerid, copid))
	{
		KillTimer(PrisionVoiceTimer[playerid]);
		if(VozDePrisao[playerid] == 1)
		{
			SendClientMessage(playerid, COLOR_LIGHTRED, "***O policial que lhe deu voz de prisão perdeu você de vista, agora você está livre!");
			VozDePrisao[playerid] = 0;
		}
	}
	return true;
}

CALLBACK:Abordagem(playerid, success) 
{
	if (IsPlayerConnected(playerid)) {

		for(new x; x != 4; x++) {
			PlayerTextDrawHide(playerid, textAbordagem[x][playerid]);
		}

		SetPVarInt(playerid, "Abordado", 0);
		SetPVarInt(playerid, "TimerAbordagem", -1);

		new copid = GetPVarInt(playerid, "OficialAbordagem");
		SetPVarInt(copid, "Abordou", 0);

		if (!IsPlayerConnected(copid)) {
			return 0;
		}

		new string[128];

		switch (success) {

			case 0: {
				format(string, sizeof string, "Atenção: O oficial %s iniciou uma perseguição a %s por não obedecer a abordagem!", PlayerName[copid], PlayerName[playerid]);
				SendClientMessageToAll(COLOR_LIGHTRED, string);

				SendClientMessage(copid, COLOR_LIGHTRED, "* O meliante não aceitou sua abordagem e agora está foragido!");
				SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não aceitou a abordagem do oficial e agora está sendo procurado pela polícia!");

				if(gettime() >= GetPVarInt(playerid, #varFlood_SuAbordado)) {
					SetPlayerCriminal(playerid, copid, "Desobediência a ordem Policial, Art. 195º");
					SetPVarInt(playerid, #varFlood_SuAbordado, gettime() + (60 * 10));
				}

				SetPVarInt(playerid, "EmAbordagem", 0);
				ShowPlayerMessage(playerid, "Voce esta sendo ~r~~h~~h~perseguido ~w~pela policia e podera ser preso", 6000);
			}
			default: {

				ShowPlayerMessage(playerid, "Voce aceitou a ~y~ordem de parada~w~. Aguarde os procedimentos do oficial.", 6000);

				format(string, sizeof string, "* %s aceitou sua abordagem!", PlayerName[playerid]);
				ShowPlayerMessage(copid, string, 6000);

				SetPVarInt(copid, "Abordou", 1);
				SetPVarInt(playerid, "EmAbordagem", 1);

				if (IsPlayerInAnyVehicle(playerid)) {
					RemovePlayerFromVehicle(playerid);
					SetTimerEx("useHandsup", 3000, false, "i", playerid);
					//TogglePlayerControllable(playerid, false);
				} else {

					ApplyAnimation(playerid,"PED", "handsup", 4.1, false, true, true, true, 0, SYNC_ALL);
					SetTimerEx("useHandsup", 500, false, "i", playerid);
					//TogglePlayerControllable(playerid, false);
				}

				format(string, sizeof string, "Voce esta abordando %s, use ~y~/revistar ~w~e escolha uma opcao abaixo", PlayerName[playerid]);
				PlayerTextDrawSetString(copid, textAbordagem[2][copid], string);
				PlayerTextDrawSetString(copid, textAbordagem[3][copid], "OPCOES:~n~~g~Y ~w~= Para liberar o meliante~n~~r~~h~N ~w~= Para dar a voz de prisao");
				for(new x; x != 4; x++) {
					PlayerTextDrawShow(copid, textAbordagem[x][copid]);
				}
			}
		}
	}
	return 1;
}

CALLBACK: useHandsup(playerid) {
	ApplyAnimation(playerid,"PED", "handsup", 4.1, false, true, true, true, 0, SYNC_ALL);
	SetTimerEx("reapplyHandsup", 500, false, "i", playerid);
	TogglePlayerControllable(playerid, false);
}

CALLBACK: reapplyHandsup(playerid) {
	ApplyAnimation(playerid,"PED", "handsup", 4.1, false, true, true, true, 0, SYNC_ALL);
}

hook OnPlayerDamageDone(playerid, Float:amount, issuerid, weapon, bodypart) {
	if(GetPVarInt(issuerid, "Abordado") == 1 && GetPVarInt(issuerid, "OficialAbordagem") == playerid) {
		KillTimer(GetPVarInt(issuerid, "TimerAbordagem"));
		Abordagem(issuerid, 0);
	}
}

hook OnPlayerLogin(playerid) {
	removeWantedPoints[playerid] = gettime() + 600;
}

stock SetPlayerCriminal(playerid, declare, const reason[], estrelas = 1)
{
	if (!IsACop(playerid) && GetPlayerOrg(playerid) != 7) {

	    new gstring[128],
			turner[100];

		new wantedpoints = Player_GetWanted(playerid);
		wantedpoints += estrelas;

	    Player_SetWanted(playerid, wantedpoints);
		CheckConquista(playerid, Conquista_12Estrelas);

		strmid(PlayerCrime[playerid][pAccusedof], reason, 0, strlen(reason), 255);
		PlayerInfo[playerid][pCrimes] ++;

		if (declare == 255) {

		    format(turner, sizeof(turner), "Câmeras de segurança");
			strmid(PlayerCrime[playerid][pVictim], turner, 0, strlen(turner), 255);

		} else {

		    if (IsPlayerConnected(declare))
			{
				GetPlayerName(declare, turner, sizeof(turner));
				strmid(PlayerCrime[playerid][pVictim], turner, 0, strlen(turner), 255);
				strmid(PlayerCrime[declare][pBplayer], PlayerName[playerid], 0, strlen(PlayerName[playerid]), 255);
				strmid(PlayerCrime[declare][pAccusing], reason, 0, strlen(reason), 255);
			}
		}

		// Modo agressivo
		if (!PlayerInfo[playerid][mAgressivo])
			SetPlayerAgressivo(playerid);
		// -----------------------------------------

		format(gstring, sizeof(gstring), "Você cometeu um crime ( %s ). acusador: %s. Nível de procurado %d", reason, turner, Player_GetWanted(playerid));
		SendClientMessage(playerid, COLOR_LIGHTRED, gstring);

		Player_SetWanted(playerid, Player_GetWanted(playerid));

		SetPVarInt(playerid, #varFlood_Suspeito, gettime() + 3);
		removeWantedPoints[playerid] = gettime() + 900;

		new MapZone:zone = GetPlayerMapZone(playerid);
		new zone_name[MAX_MAP_ZONE_NAME];

		GetMapZoneName(zone, zone_name);

		foreach(new i : Player)
		{
			if (IsACop(i) && OnDuty[i] == 1)
			{
				format(gstring, sizeof(gstring), "<< COPOM: Todas as unidades, alerta em %s >>", zone_name);
				SendClientMessage(i, TEAM_BLUE_COLOR, gstring);
				format(gstring, sizeof(gstring), "<< COPOM: Crime {FF0000}%s{8D8DFF}, Suspeito %s, Denunciante %s >>", reason, PlayerName[playerid],turner);
				SendClientMessage(i, TEAM_BLUE_COLOR, gstring);
			}
		}
	}
	return 0;
}