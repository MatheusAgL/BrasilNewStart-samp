#include <YSI_Coding\y_hooks>

hook OnPlayerUpdate(playerid) 
{
	// Jogador está se movendo sem logar.
	if (!Player_Logado(playerid)) {
		if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
			KickEx(playerid);

		return 1;
	}

	if (GetPVarInt(playerid, "Desmaiado")) {
		if (!IsPlayerInAnyVehicle(playerid)) 
			ApplyAnimation(playerid,"CRACK","crckidle1",4.1,1,1,1,0,0);
	}

	new specID = SpectadorInfo[playerid][spectadorID];
	if (specID != INVALID_PLAYER_ID)
	{
	    if (!Player_Logado(specID)) {
	 		SpectadorInfo[playerid][spectadorID] = INVALID_PLAYER_ID;
	 		TogglePlayerSpectating(playerid, false);

			GameTextForPlayer(playerid, "~w~                TV~n~~r~~h~                DESCONECTADO", 5000, 6);
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);

			PlayerTextDrawHide(playerid, spectadorText[playerid]);
		}
		else
		{
			new procurandoPlayer = GetPVarInt(specID, "varProcura");

			static
				spec_string[450],
				clientVersion[12],
				Float:healthPlayer,
				Float:armourPlayer
			;

			GetPlayerHealth(specID, healthPlayer);
			GetPlayerArmour(specID, armourPlayer);
			GetPlayerVersion(specID, clientVersion, 12);

			new Float:speed = GetPlayerSpeedEx(specID) * 1.0;
			if(IsPlayerInAnyVehicle(specID))
				speed = GetVehicleSpeed(GetPlayerVehicleID(specID));

			format(spec_string,sizeof(spec_string),
			"~g~~h~ID:~w~ %d~n~\
			~g~~h~NICK:~w~ %s~n~\
			~g~~h~VIDA:~w~ %.1f~n~\
			~g~~h~COLETE:~w~ %.1f~n~\
			~g~~h~VELOCIDADE:~w~ %.0f~n~\
			~g~~h~ARMA:~w~ %s~n~\
			~g~~h~MUNICAO:~w~ %d~n~\
			~g~~h~PING:~w~ %d~n~\
			~g~~h~PACKET LOSS:~w~ %.1f~n~\
			~g~~h~PROCURANDO:~w~ %s~n~\
			~g~~h~ARMAS BLOQ:~w~ %s~n~\
			~g~~h~SAMP-CLIENT:~w~ %s", specID, PlayerName[specID], healthPlayer, armourPlayer, speed,
			ReturnWeaponName(GetPlayerWeapon(specID)), GetPlayerAmmo(specID), GetPlayerPing(specID), NetStats_PacketLossPercent(specID), 
			procurandoPlayer != INVALID_PLAYER_ID ? (PlayerName[procurandoPlayer]) : ("Ninguem"),
			PlayerInfo[specID][pAllowWeapons] > 0 ? ("SIM") : ("NAO"), IsAndroidPlayer(specID) ? ("Android") : clientVersion);

			PlayerTextDrawSetString(playerid, spectadorText[playerid], spec_string);
			PlayerTextDrawShow(playerid, spectadorText[playerid]);

			if (GetPlayerInterior(specID) != GetPlayerInterior(playerid)) {
				SetPlayerInterior(playerid, GetPlayerInterior(specID));
			}
			if (GetPlayerVirtualWorld(specID) != GetPlayerVirtualWorld(playerid))
			{
				SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(specID));
			}
			if (GetCameraDistancePlayers(playerid, specID) > 100.0)
			{
				SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(specID));
				PlayerSpectatePlayer(playerid, specID);
			}
		}
   	}

	// Verificando ausencia
	static string[128];

	if (GetPlayerEscTime(playerid) > 4)
	{
		format(string, sizeof string, "Ausente há %s", ConvertTime(GetPlayerEscTime(playerid)));
		SetPlayerChatBubble(playerid, string, 0x96959580, 10.0, 10500);
	}
	else if (Player_GetTimerAFK(playerid) > 0)
	{
	    //format(string, sizeof string, "Inativo há %s", ConvertTime(gettime() - Player_GetTimerAFK(playerid))); (Necessário corrigir com o Sistema de Atividades)
		//SetPlayerChatBubble(playerid, string, 0x96959580, 10.0, 10500);
	}

	// if (GetPlayerSpectateType(playerid) != 0) {

	// 	static
	// 		spec_string[450],
	// 		clientVersion[12],
	// 		Float:healthPlayer,
	// 		Float:armourPlayer,
	// 		weapon_name[25]
	// 	;

	// 	if (GetPlayerSpectateType(playerid) == 1) {
	// 		// speed = GetVehicleSpeed(spectateid);
	// 		PlayerTextDrawHide(playerid, spectadorText[playerid]);
	// 	}
	// 	else if (GetPlayerSpectateType(playerid) == 2) {
	// 		new spectateid = GetPlayerSpectateID(playerid);
	// 		new procurandoPlayer = GetPVarInt(spectateid, "varProcura");
	// 		new speed = GetPlayerSpeedEx(spectateid);

	// 		GetPlayerHealth(spectateid, healthPlayer);
	// 		GetPlayerArmour(spectateid, armourPlayer);
	// 		GetPlayerVersion(spectateid, clientVersion, 12);

	// 		GetWeaponName(GetPlayerWeapon(spectateid), weapon_name);

	// 		format(spec_string,sizeof(spec_string),
	// 		"~g~~h~ID:~w~ %d~n~\
	// 		~g~~h~NICK:~w~ %s~n~\
	// 		~g~~h~VIDA:~w~ %.1f~n~\
	// 		~g~~h~COLETE:~w~ %.1f~n~\
	// 		~g~~h~VELOCIDADE:~w~ %.0f~n~\
	// 		~g~~h~ARMA:~w~ %s~n~\
	// 		~g~~h~MUNICAO:~w~ %d~n~\
	// 		~g~~h~PING:~w~ %d~n~\
	// 		~g~~h~PACKET LOSS:~w~ %.1f~n~\
	// 		~g~~h~PROCURANDO:~w~ %s~n~\
	// 		~g~~h~ARMAS BLOQ:~w~ %s~n~\
	// 		~g~~h~SAMP-CLIENT:~w~ %s", spectateid, PlayerName[spectateid], healthPlayer, armourPlayer, speed,
	// 		weapon_name, GetPlayerAmmo(spectateid), GetPlayerPing(spectateid), NetStats_PacketLossPercent(spectateid), 
	// 		procurandoPlayer != INVALID_PLAYER_ID ? (PlayerName[procurandoPlayer]) : ("Ninguem"),
	// 		PlayerInfo[spectateid][pAllowWeapons] > 0 ? ("SIM") : ("NAO"), IsAndroidPlayer(spectateid) ? ("Android") : clientVersion);

	// 		PlayerTextDrawSetString(playerid, spectadorText[playerid], spec_string);
	// 		PlayerTextDrawShow(playerid, spectadorText[playerid]);

	// 		if (GetPlayerInterior(spectateid) != GetPlayerInterior(playerid)) {
	// 			SetPlayerInterior(playerid, GetPlayerInterior(spectateid));
	// 		}
	// 		if (GetPlayerVirtualWorld(spectateid) != GetPlayerVirtualWorld(playerid))
	// 		{
	// 			SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(spectateid));
	// 		}
	// 		if (GetCameraDistancePlayers(playerid, spectateid) > 100.0)
	// 		{
	// 			SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(spectateid));
	// 			PlayerSpectatePlayer(playerid, spectateid);
	// 		}
	// 	}
	// }
	return 1;
}

ptask OnUpdatePayDay[1000](playerid)
{
	if (Player_GetTimerAFK(playerid) < 1) {
		if (PlayerInfo[playerid][pPayDay] > 0) {
			PlayerInfo[playerid][pPayDay] --;
		} else {
			PagarPayday(playerid);
			PlayerInfo[playerid][pPayDay] = 30 * 60;
			SavePlayerAccount(playerid);
		}
	}
}

ptask OnPlayerAtualizador[1000](playerid)
{
	CallLocalFunction("OnUpdateMedKit", "d", playerid);
	CallLocalFunction("OnUpdateTerritories", "d", playerid);

	if (Consumable_GetActive(playerid) != 2)
		UpdatePlayerFomeSede(playerid);

	if (Staff_GetWorking(playerid)) {

		SetPlayerHealth(playerid, 99999);

		if (Helper_GetNivel(playerid))
			ResetPlayerWeapons(playerid);
	}
	
	else if(PlayerInfo[playerid][pHospital] || Player_GetJailed(playerid))
	{
	    if (!GetPVarInt(playerid, "varFugitivo")) {
	    	ResetPlayerWeapons(playerid);
			SetPlayerHealth(playerid, 99999);
		}
	}

   	new actorid = GetPlayerTargetActor(playerid);

	if (actorid != INVALID_ACTOR_ID)
	{
	    if (!ActorInfo[actorid][actrendido] && !ActorInfo[actorid][actmorto])
	    {
			new weaponid = GetPlayerWeapon(playerid);

			if (weaponid >= 22 && weaponid <= 38 && ProxDetectorActor(5.0, playerid, actorid))
			{
				ActorInfo[actorid][actrendido] = true;
			    ApplyActorAnimation(actorid, "ROB_BANK","SHP_HandsUp_Scr", 4.1, false, true, true, true, 0);

				// Voltar ao normal
			    ActorInfo[actorid][actTimer] = SetTimerEx("acalmarActor", 10000, false, "d", actorid);

			    SetPVarInt(playerid, "mirandoActor", 1);

			    // Roubar o actor
			    PlayerTextDrawSetString(playerid, textAbordagem[1][playerid], "ARMA DE FOGO");
				PlayerTextDrawSetString(playerid, textAbordagem[2][playerid], "Voce esta apontando uma arma para este cidadao, escolha uma opcao");
		        PlayerTextDrawSetString(playerid, textAbordagem[3][playerid], "OPCOES:~n~Y = ASSALTAR~n~N = Mandar Agachar");

				for(new x; x != 4; x++) 
					PlayerTextDrawShow(playerid, textAbordagem[x][playerid]);
			}
		}
	}

	new
		string[128],
		orgPlayer = GetPlayerOrg(playerid)
	;

	if ((orgPlayer == 25 || orgPlayer == 28) && GetPVarInt(playerid, "MercORG") && GetPVarInt(playerid, "acordoID") < 999)
	{
		format(string, sizeof string, "Ajudando: [%s]", GetOrgName(GetPVarInt(playerid, "MercORG")));
		SetPlayerChatBubble(playerid, string, 0xFFFF00FF, 50.0, 2000);
	}

	if (gGuerraMorro && OrgMorro(orgPlayer) && (!Admin_GetNivel(playerid) || !Staff_GetWorking(playerid)))
	{
		if (gPlayerInGuerra(playerid) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0) {
			if (!GetPVarInt(playerid, "morroStatus"))
			{
				format(string, sizeof string, "* %s acaba de entrar na zona de guerra!", PlayerName[playerid]);
				gSendMessage(GetPlayerColor(playerid), string, 1);

				SetPVarInt(playerid, "morroEntrou", gettime());
				SetPVarInt(playerid, "morroSaiu", gettime());
				SetPVarInt(playerid, "morroStatus", 1);
				SetPVarInt(playerid, "morroBonus", 1);
			}
		} else {
			if ( GetPVarInt(playerid, "morroStatus") )
			{
				format(string, sizeof string, "* %s acaba de deixar a zona de guerra!", PlayerName[playerid]);
				gSendMessage(GetPlayerColor(playerid), string, 1);

				SetPVarInt(playerid, "morroSaiu", gettime());
				SetPVarInt(playerid, "morroStatus", 0);
			}
		}

		if(GetPVarInt(playerid, "morroStatus") == 0) {
			// Se o bônus estiver ativo...
			if(GetPVarInt(playerid, "morroBonus") == 1) {
				// Tempo fora do morro = 6 minutos = perda de bonus
				if(gettime() - GetPVarInt(playerid, "morroSaiu") > 360) {
					SendClientMessage(playerid, COLOR_LIGHTRED, "Você está fora o morro há mais de 6 minutos. Volte para não perder o bônus!");
					SetPVarInt(playerid, "morroBonus", 0);
				}
			}
		}
	}

	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
	{
		if(PlayerInfo[playerid][pVIP] < 5 && !IsPlayerHaveItem(playerid, ITEM_TYPE_JETPACK) && !Founders_GetList(playerid))
		{
			SendClientMessage(playerid, COLOR_GRAD, " Você não pode usar o jetpack.");
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		}
	}
	if (TempoAn[playerid] > 0)
		TempoAn[playerid] --;

	if (actorid == INVALID_ACTOR_ID && GetPVarInt(playerid, "mirandoActor") != 0)
	{
		for(new x; x != 4; x++) PlayerTextDrawHide(playerid, textAbordagem[x][playerid]);

		SetPVarInt(playerid, "mirandoActor", 0);
	}

   	if (PlayerInfo[playerid][pAllowWeapons] > 0)
        PlayerInfo[playerid][pAllowWeapons] --;


	// Mirando de sniper
	static
		KEY:newkeys,
		KEY:ud,
		KEY:lr;

	GetPlayerKeys(playerid, newkeys, ud, lr);

	//----- Sistema de Patins ----
	new time = GetTickCount();
	if(patinss[playerid] && time > timejump[playerid])
	{
		if(ud & KEY:KEY_UP || ud & KEY:KEY_DOWN || lr & KEY:KEY_LEFT || lr & KEY:KEY_RIGHT)
		{
			if(newkeys & KEY_WALK)
				ApplyAnimation(playerid,"SKATE","skate_run",4.1,1,1,1,1,1);
			else
				ApplyAnimation(playerid,"SKATE","skate_sprint",4.1,1,1,1,1,1);
		}
		else
		{
			ApplyAnimation(playerid,"SKATE","skate_idle",4.1,1,1,1,1,1);
		}
	}

	// Área neutra
	if (IsPlayerInRangeOfPoint(playerid, 30.0, 1479.1299,-1631.8226,14.7433)) {

		// Resetar as armas
		SetPlayerArmedWeapon(playerid, WEAPON_FIST);
	}

	// Drone
	if (IsPlayerInDrone(playerid))
	{
		static Float:health;
		GetVehicleHealth(PlayerDrone[playerid][droneId], health);

		if (health < 600.0) {
			CancelPlayerDrone(playerid);
			new money = 700 + random(800);
			Player_RemoveMoney(playerid, money);
			SendMsgF(playerid, COLOR_LIGHTRED, "* Seu veículo de inventário estragou e a seguradora cobrou $%d para repará-lo.", money);
		}
	}

	if (PlayerCaminhao[playerid][caminhaoValid])
	{
		static Float:health;
		GetVehicleHealth(PlayerCaminhao[playerid][caminhaoId], health);

		if (health < 300.0)
		{
			DestroyPlayerCaminhao(playerid);
			SendClientMessage(playerid, COLOR_LIGHTRED, "O seu caminhão foi destruido por algum motivo...");
		}
	}

	destroyPlayerHitMarks(playerid);

	// Pixação
	if ( PlayerIsGang( playerid ) ) {
		processSpraysTags( playerid );
	}

	CheckSoundProx(playerid);

	if (SkateInfo[playerid][s_Andando] && IsPlayerInMar(playerid)) {
		SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode andar de skate aqui !");
		StopPlayerSkate(playerid);
	}

	else if (PlayerToPoint(3, playerid, -1077.9645,713.4493,630.0579))
	{
		GameTextForPlayer(playerid, "~y~Casamento ~n~~r~Digite ~w~/casar", 5000, 3);
	}
	else if (PlayerToPoint(3.0, playerid, 1769.5328,-1863.3152,13.5752))
	{
		GameTextForPlayer(playerid, "~b~Voce esta na empresa de eventos~n~digite ~w~/entrarevento ~b~para participar", 5000, 3);
	}

	if (PlayerInfo[playerid][pRestoreLife] >= 200.0)
		PlayerInfo[playerid][pRestoreLife] = 200.0;

	if (PlayerInfo[playerid][pRestoreLife] >= 2.0)
	{
		givePlayerLife(playerid, 2.0);
		PlayerInfo[playerid][pRestoreLife] -= 2.0;
	}

	if ((orgPlayer == 25 || orgPlayer == 28) && GetPVarInt(playerid, "MercORG") && GetPVarInt(playerid, "acordoID") < 999)
	{
		format(string, sizeof string, "Ajudando: [%s]", GetOrgName(GetPVarInt(playerid, "MercORG")));
		SetPlayerChatBubble(playerid, string, 0xFFFF00FF, 50.0, 2000);
	}

	if (GetPVarInt(playerid, "Desmaiado"))
	{
		if (!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid,"CRACK","crckidle1",4.1,1,1,1,0,0);
	}

	if(
		IsPlayerCuffed(playerid) && 
		GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_ENTER_VEHICLE && 
		GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_EXIT_VEHICLE
	) {
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CUFFED);
	}

	if (gGuerraMorro && OrgMorro(orgPlayer) && (!Admin_GetNivel(playerid) || !Staff_GetWorking(playerid)))
	{
		if(!IsACop(playerid) || OnDuty[playerid] != 0) {
			if (gPlayerInGuerra(playerid) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0) {
				if (!GetPVarInt(playerid, "morroStatus"))
				{
					format(string, sizeof string, "* %s acaba de entrar na zona de guerra!", PlayerName[playerid]);
					gSendMessage(GetPlayerColor(playerid), string, 1);

					SetPVarInt(playerid, "morroEntrou", gettime());
					SetPVarInt(playerid, "morroSaiu", gettime());
					SetPVarInt(playerid, "morroStatus", 1);
					SetPVarInt(playerid, "morroBonus", 1);
				}
			} else {
				if ( GetPVarInt(playerid, "morroStatus") )
				{
					format(string, sizeof string, "* %s acaba de deixar a zona de guerra!", PlayerName[playerid]);
					gSendMessage(GetPlayerColor(playerid), string, 1);

					SetPVarInt(playerid, "morroSaiu", gettime());
					SetPVarInt(playerid, "morroStatus", 0);
				}
			}
		}
	}

	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
	{
		if(PlayerInfo[playerid][pVIP] < 2 && !IsPlayerHaveItem(playerid, ITEM_TYPE_JETPACK) && !Founders_GetList(playerid))
		{
			SendClientMessage(playerid, COLOR_GRAD, " Você não pode usar o jetpack .");
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		}
	}
	if (TempoAn[playerid] > 0)
		TempoAn[playerid] --;

	if (PlayerInfo[playerid][pHospital])
	{
		new
			estado[25]
		;

		if(PlayerInfo[playerid][pTempoHospital] > 40/2)estado = "~r~EM COMA";
		else if(PlayerInfo[playerid][pTempoHospital] > 40/3)estado = "~r~~h~DESACORDADO";
		else if(PlayerInfo[playerid][pTempoHospital] > 40/4)estado = "~y~ACORDANDO";
		else if(PlayerInfo[playerid][pTempoHospital] > 40/5)estado = "~p~CONFUSO";
		else if(PlayerInfo[playerid][pTempoHospital] > 40/6)estado = "~g~~h~CONSCIENTE";
		else estado = "~r~~h~~h~em observacao";

		SetPlayerHealth(playerid, 99999);

		format(string, sizeof string, "~w~Receber alta em: ~g~~h~%ds~n~~w~Estado: %s",
		PlayerInfo[playerid][pTempoHospital], estado);
		PlayerTextDrawSetString(playerid, TextHospital[playerid], string);
		PlayerTextDrawShow(playerid, TextHospital[playerid]);
		ApplyAnimation(playerid,"CRACK","crckidle2",4.1,0,1,1,1,0);

		// if ( GetPlayerState ( playerid ) != PLAYER_STATE_WASTED ) {
		// 	SetPlayerCameraPos( playerid, 1141.4489, -1743.0889, 17.5619) ;
		// 	SetPlayerCameraLookAt( playerid, 1136.0024, -1741.1626, 13.7707) ;
		// }

		if(PlayerInfo[playerid][pTempoHospital] > 0) {
			PlayerInfo[playerid][pTempoHospital] --;
		} else  {
			SairHospital(playerid);
		}
	}

	new orgid = GetPlayerOrg(playerid);
	if(orgid > 0) {
		if(CofreOrg[orgid][TrainingTime] > 0) {
			if(CofreOrg[orgid][TrainingTime] >= gettime()) {
				PlayerTextDrawShow(playerid, textTraining[playerid]);

				format(string, sizeof string, "Tempo: ~h~%s", ConvertTime(CofreOrg[orgid][TrainingTime] - gettime()));
				PlayerTextDrawSetString(playerid, textTraining[playerid], string);
			}
			else {
				PlayerTextDrawHide(playerid, textTraining[playerid]);
			}
		}
	}

	if (Player_GetJailed(playerid) > 0 && !PlayerInfo[playerid][pHospital])
    {
		if (PlayerInfo[playerid][pJailTime] > 0 && !GetPVarInt(playerid, "varFugitivo"))
		{
		    SetPlayerHealth(playerid, 99999);
			ShowPlayerTimer(playerid, GetDelegaciaName(playerid), "TEMPO RESTANTE DE PRISAO", PlayerInfo[playerid][pJailTime]);

		    if (Player_GetJailed(playerid) == 9)
			{
		        if (PlayerInfo[playerid][pLevel] > 10 && !IsPlayerESC(playerid)) 
					PlayerInfo[playerid][pJailTime]--;
	   			else 
					PlayerInfo[playerid][pJailTime]--;
			}
			else PlayerInfo[playerid][pJailTime]--;
		} 
		else if (PlayerInfo[playerid][pJailTime] < 1) {
			PlayerInfo[playerid][pJailTime] = 0;

			if (Player_GetJailed(playerid) == 24)
			{
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid,1803.0222,-1576.6367,13.4102);
				SetPlayerFacingAngle(playerid, 276.0733);
			}
			else
			{
				SpawnPlayer(playerid);
			}

			Player_SetMuted(playerid, false);

			SetPlayerHealth(playerid, 100.0);
			SetPlayerArmour(playerid, 0);

			GameTextForPlayer(playerid, "~g~Livre", 5000, 1);
			HidePlayerTimer(playerid);

			SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);

			ClearCrime(playerid);
			AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;
			SetPlayerToTeamColor(playerid);

			Player_SetCadeia(playerid, 0, 0, "Nenhum", "Nenhum", 998);
			Player_SetHandcuffed(playerid, false);

			CheckConquista(playerid, Conquista_Solto);
		}

	    if (Player_GetJailed(playerid) == 9 && !IsPlayerInRangeOfPoint(playerid, 50.0, 322.2597,306.0850,999.1484)) {
	        if (Player_IsSpawned(playerid)) {
				SpawnPlayer(playerid);
			}
		}
	}

	if (!IsPlayerHaveRespect(playerid)) 
		return 1;

	Player_LevelUp(playerid);

	return 1;
}