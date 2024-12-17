
#include <YSI_Coding\y_hooks>

#include <weapon_entry>
#include <weapon_cmds>
#include <weapon_headshot>

CMD:salvarjogador(playerid, params[])
{
	new idPlayer;
	if (sscanf(params, "d", idPlayer)) SendClientMessage(playerid, -1, "Modo de uso: /salvarjogador (id do jogador)");

	if (playerid == idPlayer) return true;

	new Float:playerPos[3];

	GetPlayerPos(idPlayer, playerPos[0], playerPos[1], playerPos[2]);

	if (!IsPlayerInRangeOfPoint(playerid, 2.0, playerPos[0], playerPos[1], playerPos[2]))
		return SendClientMessage(playerid, -1, "Você não está próximo ao jogador!");

	if (!DanoInfo[idPlayer][danoKilled])
		return SendClientMessage(playerid, -1, "Este jogador não está ferido!");

	if (GetPVarInt(playerid, "reanimando") != -1)
	    return SendClientMessage(playerid, -1, "Você já está reanimando algum jogador.");

	if (IsPlayerHaveItem(playerid, ITEM_TYPE_REMEDIO)) 
	{
	    // Setar o angulo do player para o ferido
	    SetPlayerFaceToPoint(playerid, playerPos[0], playerPos[1]);

	    // Aplicar animação de médico
	    ApplyAnimation(playerid,"MEDIC","CPR", 4.1, false, false, false, false, 0, SYNC_ALL);

	    // Timer para reanimar
	    SetPVarInt(playerid, "reanimando", idPlayer);
		SetPVarInt(playerid, "reanimartimer", SetTimerEx("reanimarJogador", 7000, false, "d", playerid));

		// Mensagem
		new string[75];
		format(string, sizeof string, "Você está tentando reanimar o jogador %s...", PlayerName[idPlayer]);
		SendClientMessage(playerid, -1, string);
	}
	else
	{
	    SendClientMessage(playerid, -1, "Você precisa ter um remédio na mochila para reanimar este jogador.");
	}
	return true;
}

CALLBACK: reanimarJogador(playerid)
{
	new killed = GetPVarInt(playerid, "reanimando");

    SetPVarInt(playerid, "reanimando", -1);

	if (!IsPlayerConnected(killed)) {
	    SendClientMessage(playerid, -1, "O jogador que você estava reanimando não está mais online.");
	    return 0;
	}

	if (!DanoInfo[killed][danoKilled]) {
	    SendClientMessage(playerid, -1, "O jogador que você estava reanimando não está mais ferido ou morreu.");
	    return 0;
	}

	if (!IsPlayerHaveItem(playerid, ITEM_TYPE_REMEDIO)) {
	    SendClientMessage(playerid, -1, "Você precisa ter um remédio na mochila para reanimar este jogador.");
	    return 0;
	}

   	// Variáveis
    static Float:x, Float:y, Float:z;

    // Pegar a posição do jogador ferido
    GetPlayerPos(killed, x, y, z);

    if (!IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z)) {
        SendClientMessage(playerid, -1, "Você não está mais perto do jogador que estava reanimando.");
        return 0;
    }

	reanimarPlayer(killed, playerid);

	return 1;
}

stock reanimarPlayer(playerid, salvador)
{
	// Limpar as animações
	ApplyAnimation(playerid,"PED","getup_front",4.1, false, false, false, false, 0, SYNC_ALL);

	// Esconder as textdraws
	//hidePlayerTextAccDano(playerid);

	// Setar variaveis
	DanoInfo[playerid][danoKilled] = false;

	// Vida que será restaurada
	PlayerInfo[playerid][pRestoreLife] += 60.0;

	// Destruir 3d label
   	DestroyDynamic3DTextLabel(DanoInfo[playerid][danoText]);

	// Remover um remedio
	RemoveQuantiaItem(salvador, ITEM_TYPE_REMEDIO);

	// Mensagens
	new string[75];
	format(string, sizeof string, "* Você conseguiu curar as feridas do jogador %s.", PlayerName[playerid]);
	SendClientMessage(salvador, COLOR_LIGHTBLUE, string);
	format(string, sizeof string, "* O jogador %s conseguiu curar seus ferimentos.", PlayerName[salvador]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
}

stock IsPlayerInCombat(playerid)
{
	if (Staff_GetWorking(playerid) && Admin_GetNivel(playerid) >= MODERADOR) 
		return false;
	
	return gettime() < GetPVarInt(playerid, "VarDano");
}

stock GetPlayerInCombatTime(playerid) {
	return GetPVarInt(playerid, "VarDano") - gettime();
}

CALLBACK: updatePlayerDano(playerid)
{
	if (DanoInfo[playerid][danoKilled])
	{
	    if (DanoInfo[playerid][danoTime] > 1)
		{
	        DanoInfo[playerid][danoTime] --;

	        new string[75];
	        format(string, sizeof string, "Morrendo em %d segundos...", DanoInfo[playerid][danoTime]);
	        PlayerTextDrawSetString(playerid, textPlayerMorteAcc[playerid], string);

	        // Animação
	        ApplyAnimation(playerid,"SWAT","gnstwall_injurd", 4.1, true, false, false, false, 0, SYNC_ALL);
	    }
		else
		{
	        //playerDesistir(playerid);
	    }
	}
}

public OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart)
{
	if (!Player_Logado(playerid)) 
		return 0;

	// Impedindo danos em administradores modo trabalho
	if ((Admin_GetNivel(playerid) || Helper_GetNivel(playerid)) && Staff_GetWorking(playerid)) 
		return 0;

	if (issuerid != INVALID_PLAYER_ID) 
	{
		if (!Player_Logado(issuerid)) 
			return 0;

		if (!Founders_GetList(issuerid)) {

			if (Player_GetJailed(issuerid) || Player_GetJailed(playerid)) 
				return 0;

			if (GetPVarInt(playerid, "Invincible") || GetPVarInt(playerid, "AntiSpawnKill"))
				return SendClientMessage(issuerid, COLOR_LIGHTRED, "ANTI-SPAWNKILL: Aguarde para atingir esse jogador, ele acabou de spawnar..."), 0;
			
			else if(GetPVarInt(issuerid, "Invincible") || GetPVarInt(issuerid, "AntiSpawnKill"))
				return SendClientMessage(issuerid, COLOR_LIGHTRED, "ANTI-SPAWNKILL: Você acabou de spawnar, aguarde para causar dano em outro jogador..."), 0;
		}

		if (!CheckPlayerPacifico(playerid, issuerid)) 
			return 0;

		if (!GetPVarInt(issuerid, "InHeadShot")) {
			if (weapon == WEAPON_SNIPER) 
			{
				if (!ProxDetectorS(70.0, issuerid, playerid)) {
					if (bodypart == 9) {
						if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
							// 20% de chance de não receber HS com metanfetamina
							if(GetPVarInt(playerid, "EfeitoMetanfetamina") == 0 || random(10) < 8) {
								InitHeadShot(issuerid, playerid);
								if(!DMSystem[issuerid][playerid] && !DMSystem[playerid][issuerid])
									AddCombate(issuerid, playerid);

								return 0;
							}
							else {
								PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0);
								PlayerPlaySound(issuerid, 1055, 0.0, 0.0, 0.0);
							}
						}
					}
					amount = 50.0;
				}
				else amount = 35.0;
			}
		}

		#if _inc_paintball_system
		if (!DMSystem[issuerid][playerid] && !DMSystem[playerid][issuerid] && Player_GetPaintball(issuerid) == INVALID_PAINTBALL_ID)
		#else
		if (!DMSystem[issuerid][playerid] && !DMSystem[playerid][issuerid])
		#endif
		{
			AddCombate(issuerid, playerid);
		}
		if (!DMSystem[playerid][issuerid])
			DMSystem[issuerid][playerid] = true;
		
		else if(!DMSystem[issuerid][playerid]) 
		{
			DMSystem[playerid][issuerid] = true;
			UpdatePlayersCombate(issuerid, playerid);
		}
		#if _inc_paintball_system
		if (GetPlayerOrg(issuerid) != GetPlayerOrg(playerid) && Player_GetPaintball(issuerid) == INVALID_PAINTBALL_ID)
		#else
		if (GetPlayerOrg(issuerid) != GetPlayerOrg(playerid))
		#endif
		{
			SetPVarInt(playerid, "varPlayerCombate",   gettime() + 25);
			SetPVarInt(playerid, "varPlayerCombateId", playerid);
		}
		
		switch (weapon)
		{
			case 23:
			{
				if (ProxDetectorS(10.0, issuerid, playerid) &&
					InTaser[issuerid]) {
						
					new string[128];

					if (IsPlayerInCombat(issuerid)) {
						format(string, sizeof(string), "(( %s, %s acertou %s com o TASER, falhou em modo combate ))", GetPlayerCargo(playerid), PlayerName[issuerid], PlayerName[playerid]);
					} else {
						format(string, sizeof(string), "(( %s, %s acertou %s com o TASER ))", GetPlayerCargo(playerid), PlayerName[issuerid], PlayerName[playerid]);
						
						GameTextForPlayer(playerid, "~r~~h~Inconsciente", 2500, 3);
						TogglePlayerControllable(playerid, false);
						
						ApplyAnimation(playerid, "CRACK", "crckdeth2",  4.0, true, false, false, false, 0, SYNC_NONE);
					}
					SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
					InTaser[issuerid] = false;

					return 0;
				}
			}
			case 28, 29, 32:
			{
				if (IsPlayerInAnyVehicle(playerid) && 
					GetPlayerState(issuerid) == PLAYER_STATE_ONFOOT) {
					SetPlayerArmedWeapon(playerid, WEAPON_FIST);
					return 0;
				}
			}
		}
	}

	new Float:amount2 = amount;

	// Reduz o dano recebido se a vítima estiver sob efeito de maconha
	if(GetPVarInt(playerid, "EfeitoMaconha")) {
		new rand = random(10);
		if(rand < 2) {
			amount2 -= amount * 0.6;
		}
		else if(rand < 7) {
			amount2 -= amount * 0.4;
		}
	}

	if (issuerid != INVALID_PLAYER_ID) {
		// Reduz o dano causado se o agressor estiver sob efeito de maconha
		if(GetPVarInt(issuerid, "EfeitoMaconha")) {
			new rand = random(10);
			if(rand < 4) {
				amount2 -= amount * 0.15;
			}
		}

		// Aumenta o dano se o agressor estiver sob efeito de cocaína
		if(GetPVarInt(issuerid, "EfeitoCocaina")) {
			new rand = random(10);
			if(rand < 8) {
				amount2 += amount * random(31)/100.0;
			}
		}
	}

	// Zera o dano se a vítima estiver sob efeito de crack
	if(GetPVarInt(playerid, "EfeitoCrack")) {
		new rand = random(10);
		if(rand < 9) {
			new Float:health,
				limit = GetPVarInt(playerid, "LimiteCrack");

			GetPlayerHealth(playerid, health);
			if(health <= 7.0 && limit > 0) {
				amount2 = 0.1;
				PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0);
				PlayerPlaySound(issuerid, 1055, 0.0, 0.0, 0.0);
			}
		}
	}

	if (GetPVarInt(playerid, "EfeitoMetanfetamina")) 
	{
		if(weapon == 54)
			amount2 = 2.0;
		else if(weapon == 37)
			amount2 = 0.02;
	}

	amount = amount2;

	if (issuerid != INVALID_PLAYER_ID) {
		
		// Não deixar equipar em combate
		SetPVarInt(playerid, "VarDano", gettime() + 60);

		if (GetPVarInt(issuerid, "gPlayerHitMark_DB"))
			createPlayerHitMark(issuerid, amount, weapon, 0xF49595BB);

		checkDanoForPlayer(issuerid, playerid, amount, weapon);

		wLastShooter[issuerid] = playerid;
	}
	return 1;
}

hook OnPlayerDamageDone(playerid, Float:amount, issuerid, weapon, bodypart)
{
	if (!Player_Logado(playerid) || 
		!Player_Logado(issuerid) || 
		issuerid == INVALID_PLAYER_ID)
		return 1;

	DanoInfo[playerid][danoDamager] = issuerid;
	DanoInfo[playerid][danoWeapon] = weapon;

	if (weapon == 4) 
		DanoInfo[playerid][danoBodypart] = 10;
	else
		DanoInfo[playerid][danoBodypart] = bodypart;

	return 1;
}

hook OnPlayerPrepareDeath(playerid, animlib[32], animname[32], &anim_lock, &respawn_time) {
	return 1;
}

// Quando a animação da morte terminar e o jogador for enviado para reaparecer
hook OnPlayerDeathFinished(playerid)
{
    JoinedHay[playerid] = false;
	
	setarhospital(playerid);

	SetPVarInt(playerid, "EfeitoMaconha", 0);
	SetPVarInt(playerid, "EfeitoCocaina", 0);
	SetPVarInt(playerid, "EfeitoCrack", 0);
	SetPVarInt(playerid, "Cuffed", 0);
    return 1;
}

CALLBACK: hideTextDeath(playerid) {
	return TextDrawHideForPlayer(playerid, textDeath);
}

public OnPlayerDeath(playerid, killerid, reason)
{
	new string[190];

	new weapon_name[25];
	GetWeaponName(reason, weapon_name);

	if (killerid != INVALID_PLAYER_ID)
	{
		SetPVarInt(playerid, "InHeadShot", 0);
		SetPVarInt(killerid, "InHeadShot", 0);

		#if _inc_paintball_system
		if (Player_GetPaintball(playerid) != INVALID_PAINTBALL_ID ||
			Player_GetPaintball(killerid) != INVALID_PAINTBALL_ID)
			return 1;
		#endif
		
		addPlayerLastKill(killerid, playerid, reason);

		TextDrawShowForPlayer(killerid, textDeath);
		SetTimerEx("hideTextDeath", 80, false, "i", killerid);

		new killerorg = GetPlayerOrg(killerid),
			playerorg = GetPlayerOrg(playerid);

		if(playerorg == killerorg && IsOrgTraining(killerorg)) {
			if(IsPlayerInAreaSeguraOrg(killerid, killerorg) && IsPlayerInAreaSeguraOrg(playerid, playerorg)) {
				
				new Float:life[2];

				GetPlayerHealth(killerid, life [0]);
				GetPlayerArmour(killerid, life [1]);
				format(string, sizeof string, "* Você foi morto por {FFFFFF}%s (%s) {33CCFF}com a arma: {FFFFFF}[%s]{33CCFF} em treinamento | Vida: {FFFFFF}%.0f", PlayerName[killerid], GetOrgName(GetPlayerOrg(killerid)), weapon_name, life [0] + life [1]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

				GetPlayerHealth(killerid, life[0]);
				GetPlayerArmour(killerid, life[1]);
				format(string, sizeof string, "* Você matou {FFFFFF}%s (%s) {33CCFF}com a arma: {FFFFFF}[%s]{33CCFF} em treinamento | Vida: {FFFFFF}%.0f", PlayerName[playerid], GetOrgName(GetPlayerOrg(playerid)), weapon_name, life [0] + life [1]);
				SendClientMessage(killerid, COLOR_LIGHTBLUE, string);

				SendDeathMessageOrgTraining(killerid, playerid, reason);
				return 1;
			}
		}

		// Guerra terrorista
		warCheckKill(playerid, killerid);
		
		CheckPontosTr(playerid, killerid);

		if (!warIsPlayerIn(killerid) && GoChase[killerid] != playerid && !Zone_IsPlayerIn(killerid) && !gPlayerInGuerra(killerid) && GetPlayerVirtualWorld(killerid) != 10020 && GetPlayerVirtualWorld(killerid) != 10061)
		{
			if (DMSystem[playerid][killerid] && !DMSystem[killerid][playerid])
			{
				PlayerPlaySound(killerid, 1138, 0.0, 0.0, 0.0);
				SendClientMessage(killerid, 0xFFCCCCFF, "Você cometeu um assassinato em legitima defesa e não pegou nível de procurado!");
			} else {
				SetPlayerCriminal(killerid, 255, "Assassinato", 1);
				PlayerPlaySound(killerid, 1138, 0.0, 0.0, 0.0);
			}
		}

		if (reason == WEAPON_SNIPER)
			PlayerInfo[killerid][pMatouSniper] ++;

		new Float:life[2];

		GetPlayerHealth(killerid, life [0]);
		GetPlayerArmour(killerid, life [1]);

		if ( GoChase[killerid] == playerid ) {

			format(string, sizeof string, "* Você foi morto por {FFFFFF}Assassino de aluguel (%s) {33CCFF}com a arma: {FFFFFF}[%s]{33CCFF} | Vida: {FFFFFF}%.0f", GetOrgName(GetPlayerOrg(killerid)), weapon_name, life [0] + life [1]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
		}
		else {

			format(string, sizeof string, "* Você foi morto por {FFFFFF}%s (%s) {33CCFF}com a arma: {FFFFFF}[%s]{33CCFF} | Vida: {FFFFFF}%.0f", PlayerName[killerid], GetOrgName(GetPlayerOrg(killerid)), weapon_name, life [0] + life [1]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			
			SendDeathMessage(killerid, playerid, reason);
		}

		GetPlayerHealth(killerid, life[0]);
		GetPlayerArmour(killerid, life[1]);

		format(string, sizeof string, "* Você matou {FFFFFF}%s (%s) {33CCFF}com a arma: {FFFFFF}[%s]{33CCFF} | Vida: {FFFFFF}%.0f", PlayerName[playerid], GetOrgName(GetPlayerOrg(playerid)), weapon_name, life [0] + life [1]);
		SendClientMessage(killerid, COLOR_LIGHTBLUE, string);
		PlayerInfo[killerid][pKills] ++;

		if (!GetPlayerOrg(playerid) && PlayerInfo[playerid][pLevel] >= 3 && !DMSystem[playerid][killerid]) {
			if (GoChase[killerid] == playerid) {
				SendClientMessage(playerid, 0xFFCCCCFF, "Você foi morto por um assassino de aluguel, não foi considerado DM.");
			}
		}

		new assaltado = GetPVarInt(playerid, "assaltado"), assaltante = GetPVarInt(playerid, "assaltante"), comparsa = GetPVarInt(assaltante, "Comparsa");
		new tempoMinimo = GetPVarInt(playerid, "assaltoTempoMinimo");
		customorte[playerid] = 100;
		if(assaltado && killerid == assaltante) {
			if(gettime() < tempoMinimo) {
				SendClientMessage(killerid, COLOR_LIGHTRED, "Você matou a vítima antes do tempo mínimo de assalto e não recebeu nada.");
				SetPlayerCriminal(assaltante, 255, "Assalto", 10);
				PlayerInfo[playerid][pTempoHospital] = 5;
			}
			else {
				PlayerInfo[playerid][pTempoHospital] = 300;
				customorte[playerid] = 2500;

				new valor = Player_GetMoney(playerid) / 2;

				format(string, sizeof(string), "* Você matou a vítima %s e recebeu $%s.", PlayerName[playerid], getFormatText(valor));
				SendClientMessage(assaltante, COLOR_LIGHTRED, string);
				Player_AddMoney(assaltante, valor);
				Player_AddMoney(comparsa, valor);
				Player_RemoveMoney(playerid, Player_GetMoney(playerid));
				SetPlayerCriminal(assaltante, 255, "Assalto", 8);
				SetPVarInt(playerid, "assaltado", 0);
			}
		}

		if(PlayerInfo[playerid][pTempoHospital] > 0) {
			PlayerInfo[playerid][pHospital] = true;
			PlayerInfo[playerid][pHAjustado] = false;
			
			if(assaltado) {
				SendClientMessage(playerid, TEAM_BALLAS_COLOR, "Você reagiu ao assalto e morreu, perdendo todo o dinheiro =(");
				SendClientMessage(playerid, TEAM_BALLAS_COLOR, "Você morreu e será internado no hospital regional mais proximo de você.");
				SendClientMessage(playerid, TEAM_BALLAS_COLOR, "Uma equipe médica ira cuidar de você até que você se recupere totalmente.");
				format(string, sizeof string, "Você receberá alta do hospital regional de Los Santos em %d segundos, custo: $%d", PlayerInfo[playerid][pTempoHospital], customorte[playerid]);
				SendClientMessage(playerid, TEAM_BALLAS_COLOR, string);
			}
		}

		new wantedpoints = Player_GetWanted(playerid);

		if (wantedpoints && !warIsPlayerIn(playerid) && (!IsACop(playerid) && OnDuty[playerid] != 1) && !gPlayerInGuerra(playerid) && !Zone_IsPlayerIn(playerid))
		{
			new org = GetPlayerOrg(killerid), 
				pricePrisao = (3000 * wantedpoints);

			if (killerid != INVALID_PLAYER_ID && IsACop(killerid) && OnDuty[killerid] == 1)
			{
				Player_RemoveMoney(playerid, pricePrisao);
				Jail_SetJailed(playerid, 24);
				new jailtime = PlayerInfo[playerid][pJailTime];

				jailtime = (wantedpoints * 180);

				switch (Player_GetVIP(playerid)) {

					case SOCIO_COMUM: 		jailtime -= floatround(jailtime * 0.05);
					case SOCIO_PREMIUM: 		jailtime -= floatround(jailtime * 0.10);
					case SOCIO_SUPREME:		jailtime -= floatround(jailtime * 0.20);
					case SOCIO_EXTREME:  	jailtime -= floatround(jailtime * 0.30);
				}

				Player_SetCadeia(playerid, 24, jailtime, PlayerName[killerid], PlayerCrime[playerid][pAccusedof], GetPlayerOrg(killerid));
				OrgInfo_SetMoney(org, OrgInfo_GetMoney(org) + pricePrisao);

				format(string, sizeof(string), "* Você está preso por %d segundos na (Prisão La Sante), e pagou $%s de multa por não se render.", PlayerInfo[playerid][pJailTime], getFormatText(pricePrisao));
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				
				format(string, sizeof(string), "<< COPOM >>: %s efetuou uma prisão, recebeu $%s.", NomeORG(killerid), getFormatText(pricePrisao));
				SendMembersMessage(GetPlayerOrg(killerid), COLOR_LIGHTRED, string), SendMembersMessage(7, COLOR_LIGHTRED, string);
				
				PlayerInfo[killerid][pMorteSuspeito] ++;
				
				CheckConquista(playerid, Conquista_Prisao);

				foreach(new i : Player)
				{
					if (IsACop(i) && ProxDetectorS(40.0, playerid, killerid))
					{
						format(string, sizeof string, "~w~Suspeito ~r~~h~%s ~w~morto", PlayerName[playerid]); 
						ShowPlayerMessage(i, string, 5000);

						if (GetPlayerState(i) == PLAYER_STATE_DRIVER) PlayerPlaySound(i, 2134, 0.0, 0.0, 0.0);
						else PlayerPlaySound(i, 1039, 0.0, 0.0, 0.0);
					}
				}
			}
		}

		if (GoChase[killerid] == playerid)
		{
			if (GetPlayerOrg(killerid) == 8)
			{
				Player_AddMoney(killerid, PlayerInfo[playerid][pHeadValue]/2);
				OrgInfo_SetMoney(8, OrgInfo_GetMoney(8) + PlayerInfo[playerid][pHeadValue]/2);
				PlayerInfo[killerid][pExp] += PlayerInfo[playerid][pHeadRespect];

				format(string,sizeof string,"! {FFF000}Um hitman cumpriu contrato em %s(%d) | valor $%s e %d respeitos.", PlayerName[playerid], playerid,
				getFormatText(PlayerInfo[playerid][pHeadValue]), PlayerInfo[playerid][pHeadRespect]);
				SendClientMessageToAll(0xFF0000AA, string);

				format(string,sizeof string,"-*** O hitman: %s(%d) matou você por um contrato de $%s e %d respeitos.", PlayerName[killerid], killerid,
				getFormatText(PlayerInfo[playerid][pHeadValue]), PlayerInfo[playerid][pHeadRespect]);
				SendClientMessage(playerid, -1, string);

				CheckConquista(killerid, Conquista_Contrato);

				format(string,sizeof string,"Agência | %s cumpriu contrato em: %s, recebeu $%s e %d respeitos (org recebeu $%s).",PlayerName[killerid],PlayerName[playerid],
				getFormatText(PlayerInfo[playerid][pHeadValue]/2), PlayerInfo[playerid][pHeadRespect], getFormatText(PlayerInfo[playerid][pHeadValue]/2));
				SendMembersMessage(8, COLOR_YELLOW, string);

				format(string, sizeof(string), "~g~~h~~h~+$%s", getFormatText(PlayerInfo[playerid][pHeadValue]));
				ShowPlayerPopupHUD(playerid, "CONTRATO CUMPRIDO", string, 6000);

				if(PlayerInfo[playerid][pHeadRespect]) {
					format(string, sizeof(string), "~r~~h~~h~+%d ~w~Respeito", PlayerInfo[playerid][pHeadRespect]);
					ShowPlayerPopupHUD(playerid, "CONTRATO CUMPRIDO", string, 6000);
				}

				PlayerInfo[playerid][pHeadValue] = 0;
				PlayerInfo[playerid][pHeadRespect] = 0;
				PlayerInfo[playerid][pLastContrato] = gettime() + (60 * 30);
				GotHit[playerid] = 0;
				GetChased[playerid] = INVALID_PLAYER_ID;
				GoChase[killerid] = INVALID_PLAYER_ID;
			}
			else if (GetPlayerOrg(killerid) == 22)
			{
				Player_AddMoney(killerid, PlayerInfo[playerid][pHeadValueT]/2);
				OrgInfo_SetMoney(22, OrgInfo_GetMoney(22) + PlayerInfo[playerid][pHeadValueT]/2);
				PlayerInfo[killerid][pExp] += PlayerInfo[playerid][pHeadRespectT];

				format(string,sizeof string,"! {FFF000}Um triad cumpriu contrato em %s(%d) | valor $%s e %d respeitos.", PlayerName[playerid], playerid,
				getFormatText(PlayerInfo[playerid][pHeadValueT]), PlayerInfo[playerid][pHeadRespectT]);
				SendClientMessageToAll(0xFF0000AA, string);

				format(string,sizeof string,"-*** O triad: %s(%d) matou você por um contrato de $%s e %d respeitos.", PlayerName[killerid], killerid,
				getFormatText(PlayerInfo[playerid][pHeadValueT]), PlayerInfo[playerid][pHeadRespectT]);
				SendClientMessage(playerid, -1, string);

				CheckConquista(killerid, Conquista_Contrato);

				format(string,sizeof string,"Agência | %s cumpriu contrato em: %s, recebeu $%s e %d respeitos (org recebeu $%s).", PlayerName[killerid], PlayerName[playerid],
				getFormatText(PlayerInfo[playerid][pHeadValueT]/2), PlayerInfo[playerid][pHeadRespectT], getFormatText(PlayerInfo[playerid][pHeadValueT]/2));
				SendMembersMessage(22, COLOR_YELLOW, string);

				format(string, sizeof(string), "~g~~h~~h~+$%s", getFormatText(PlayerInfo[playerid][pHeadValueT]));
				ShowPlayerPopupHUD(playerid, "CONTRATO CUMPRIDO", string, 6000);

				if(PlayerInfo[playerid][pHeadRespect]) {
					format(string, sizeof(string), "~r~~h~~h~+%d ~w~Respeito", PlayerInfo[playerid][pHeadRespectT]);
					ShowPlayerPopupHUD(playerid, "CONTRATO CUMPRIDO", string, 6000);
				}

				PlayerInfo[playerid][pHeadValueT] = 0;
				PlayerInfo[playerid][pHeadRespectT] = 0;
				PlayerInfo[playerid][pLastContrato] = gettime() + (60 * 30);
				GotTri[playerid] = 0;
				GetChased[playerid] = INVALID_PLAYER_ID;
				GoChase[killerid] = INVALID_PLAYER_ID;
			}
			PlayerInfo[killerid][pContratos]++;

			SetPlayerToTeamColor(killerid);
			if (!GetPlayerSeeNick(playerid))
			{
				SetPlayerSeeNick(playerid, true);
				SendClientMessage(killerid, COLOR_GRAD, "(( Você agora não está mais em modo secreto ))");
				
				foreach(new i : Player)
					ShowPlayerNameTagForPlayer(i, killerid, true);
			}
		}
		else if (GoChase[playerid] == killerid)
		{
			if (GetPlayerOrg(playerid) == 8)
			{
				format(string,sizeof string,"* O assassino %s morreu e perdeu um contrato em: %s.", PlayerName[playerid], PlayerName[killerid]);
				SendMembersMessage(8, COLOR_YELLOW, string);
					
				format(string,sizeof string,"<< Um assassino morreu e perdeu o contrato em %s [%d], pelo preço de: $%s >>", PlayerName[killerid], playerid, getFormatText(PlayerInfo[killerid][pHeadValue]));
				SendClientMessageToAll(COLOR_YELLOW, string);

				format(string,sizeof string,"<< O assassino %s [%d] morreu para você e perdeu o contrato de: $%s >>", PlayerName[playerid], playerid, getFormatText(PlayerInfo[killerid][pHeadValue]));
				SendClientMessage(killerid, COLOR_LIGHTRED, string);

				PlayerInfo[killerid][pHeadValue] = 0;
				PlayerInfo[playerid][pHeadRespect] = 0;
				GotHit[killerid] = 0;
				GetChased[killerid] = INVALID_PLAYER_ID;
				GoChase[playerid] = INVALID_PLAYER_ID;
			}
			else if(GetPlayerOrg(playerid) == 22)
			{
				format(string,sizeof string,"* O assassino %s morreu e perdeu um contrato em: %s.",PlayerName[playerid], PlayerName[killerid]);
				SendMembersMessage(22, COLOR_YELLOW, string);

				format(string,sizeof string,"<< Um assassino morreu e perdeu o contrato em %s [%d], pelo preço de: $%s >>", PlayerName[killerid], playerid, getFormatText(PlayerInfo[killerid][pHeadValueT]));
				SendClientMessageToAll(COLOR_YELLOW, string);

				format(string,sizeof string,"<< O assassino %s [%d] morreu para você e perdeu o contrato de: $%s >>", PlayerName[playerid], playerid, getFormatText(PlayerInfo[killerid][pHeadValueT]));
				SendClientMessage(killerid, COLOR_LIGHTRED, string);

				PlayerInfo[killerid][pHeadValueT] = 0;
				PlayerInfo[playerid][pHeadRespectT] = 0;
				GotTri[killerid] = 0;
				GetChased[killerid] = INVALID_PLAYER_ID;
				GoChase[playerid] = INVALID_PLAYER_ID;
			}
		}
	}

	warCheckDeath(playerid);

	StopPlayerSkate(playerid);
	SetPVarInt(playerid, "varDead", 1);

	SetPVarInt(playerid, "varPlayerCombate",   0);
	SetPVarInt(playerid, "varPlayerCombateId", INVALID_PLAYER_ID);

	foreach(new players : Player) {
		if (GetPVarInt(players, "varPlayerCombateId") == playerid) {
			SetPVarInt(players, "varPlayerCombate",   0);
			SetPVarInt(players, "varPlayerCombateId", INVALID_PLAYER_ID);
		}
	}
	
	dropAllItensType(playerid, ITEM_TYPE_ORGAO);
	
	if (PlayerInfo[playerid][pExplosives])
	{
		dropItem(playerid, ITEM_TYPE_EXPLOSIVO, 1654, 1, "Explosivo");

		PlayerInfo[playerid][pExplosives] = 0;
	}

	// Armas dropadas no chão
	new weapon[13];
	new ammo[13];

	for(new wslot; wslot != 13; wslot++)
	{
		GetPlayerWeaponData(playerid, wslot, weapon[wslot], ammo[wslot]);
		GetWeaponName(weapon[wslot], weapon_name);

		if (weapon[wslot] > 0 && ammo[wslot] != 0) {
			dropItem(playerid, ITEM_TYPE_WEAPON, weapon[wslot], ammo[wslot], weapon_name);
		}
	}
	// ------------------------------------

	if (PlayerInfo[playerid][pDrogas] > 0)
	{
		dropItem(playerid, ITEM_TYPE_MACONHA, 2891, PlayerInfo[playerid][pDrogas], "Maconha");
		PlayerInfo[playerid][pDrogas] = 0;
	}
	if (PlayerInfo[playerid][pDrogas2] > 0)
	{
		dropItem(playerid, ITEM_TYPE_COCAINA, 2891, PlayerInfo[playerid][pDrogas2], "Cocaina");
		PlayerInfo[playerid][pDrogas2] = 0;
	}
	if (PlayerInfo[playerid][pDrogas3] > 0)
	{
		dropItem(playerid, ITEM_TYPE_CRACK, 2891, PlayerInfo[playerid][pDrogas3], "Crack");
		PlayerInfo[playerid][pDrogas3] = 0;
	}

	if (Player_GetWanted(playerid)) {
		new valorMorte = Player_GetWanted(playerid) * 200;

		format(string, sizeof(string), "((Hospital)) {FFFFFF}Você pagou $%s pelos serviços e por ser procurado nível: %d.", getFormatText(valorMorte), Player_GetWanted(playerid));
		SendClientMessage(playerid, 0xED8484FF, string);
		Player_RemoveMoney(playerid, valorMorte);

		adicionarDinheiroGoverno(valorMorte);
	}

	SetPVarInt(playerid, "VarDano", 0);

	if (Inventory_IsOpen(playerid))
		Inventory_HideForPlayer(playerid);

	playerCancelTrade(playerid);

	if (GetPVarInt(playerid, "playerInTrashCan"))
		removePlayerTrashCan(GetPVarInt(playerid, "playerInTrashCan"));
	
	if (FabricandoMateriais[playerid]) 
	{
		format(string, sizeof(string), "* %s cancelou a fabricação de materiais.", PlayerName[playerid]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		TogglePlayerControllable(playerid, true); FabricandoMateriais[playerid] = false;

		ClearAnimations(playerid);

		DestroyDynamicObject(GetPVarInt(playerid, "objectCreateMateriais")); DeletePVar(playerid, "objectCreateMateriais");

		DestroyDynamic3DTextLabel(textFabricandoMat[playerid]); KillTimer(GetPVarInt(playerid, "timerTrabalho_Fabricante"));
	}

	if (!Staff_GetWorking(playerid))
	{
		new tempohospital = Player_GetTempoHospital(playerid);

		// Se tiver morrido em guerra / no morro, recebe somente 5 segundos de hospital
		if(warIsPlayerIn(playerid) || gPlayerInGuerra(playerid))
			Player_SetTempoHospital(playerid, 5);
		// Se for COP com cartão batido e tiver morrido fora de guerra / morro, recebe de 2 min a 3 min de hospital
		else if(IsACop(playerid) && OnDuty[playerid] == 1)
			Player_SetTempoHospital(playerid, 60);
		else
			Player_SetTempoHospital(playerid, 40);

		if (PlayerInfo[playerid][pVIP] == 1)
			Player_SetTempoHospital(playerid, tempohospital - floatround(tempohospital * 40));
		else if(PlayerInfo[playerid][pVIP] > 1 && PlayerInfo[playerid][pVIP] <= 6)
			Player_SetTempoHospital(playerid, tempohospital - floatround(tempohospital * 60));
		else if(PlayerInfo[playerid][pVIP] == 7)
			Player_SetTempoHospital(playerid, tempohospital - floatround(tempohospital * 70));
		else if(PlayerInfo[playerid][pVIP] == 8)
			Player_SetTempoHospital(playerid, tempohospital - floatround(tempohospital * 80));

		if (tempohospital > 0) {
			PlayerInfo[playerid][pHospital] = true;
			PlayerInfo[playerid][pHAjustado] = false;
		}
	}

	PlayerInfo[playerid][pDeaths] ++;

	if (SkateInfo[playerid][s_Setado])
	{
		if (isInventoryFull(playerid)) {
			SendClientMessage(playerid, COLOR_LIGHTRED, "Você morreu usando um skate, como está sem espaço no inventário, use: /guardarskate!");
			SendClientMessage(playerid, COLOR_LIGHTRED, "Guarde antes de se reconectar ou poderá perder seu item!");
			return 1;
		}
		StopPlayerSkate(playerid);
		RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);
		SkateInfo[playerid][s_Setado] = false;
		givePlayerItem(playerid, ITEM_TYPE_SKATE, 19878, 1, "Skate");
	}

	new onlineCall = MobileInfo[playerid][mobileCall];
	if (onlineCall != MAX_PLAYERS+5)
	{
		SendClientMessage(onlineCall, -1, "((Chamada de voz)) Ligação encerrada.");
		MobileInfo[onlineCall][mobileCall] = MAX_PLAYERS+5, MobileInfo[playerid][mobileCall] = MAX_PLAYERS+5;
	}

	ClearCrime(playerid);

	SetPlayerToTeamColor(playerid);

	if (!GetPlayerSeeNick(playerid) && !GetPVarInt(playerid, "EfeitoHeroina"))
	{
		SetPlayerSeeNick(playerid, true);
		SendClientMessage(playerid, COLOR_GRAD, "(( Você agora não está mais em modo secreto ))");
		
		foreach(new i : Player)
			ShowPlayerNameTagForPlayer(i, playerid, true);
	}

	SetPVarInt(playerid, "TimeMaconha", 0);
	SetPVarInt(playerid, "TimeCocaina", 0);
	SetPVarInt(playerid, "TimeCrack", 0);
	SetPVarInt(playerid, "TimeHeroina", 0);
	SetPVarInt(playerid, "TimeMetanfetamina", 0);
	return 1;
}

CALLBACK: hideDamageGive(playerid)
{
	playerCombo[0][playerid] = 0.0;
	PlayerTextDrawHide(playerid, textPlayerDamager[0][playerid]);
	PlayerTextDrawHide(playerid, textPlayerDamager[1][playerid]);
	SetPVarInt(playerid, "varDamageGive", 0);

	return 1;
}

CALLBACK: hideDamageTake(playerid)
{
	playerCombo[1][playerid] = 0.0;
	PlayerTextDrawHide(playerid, textPlayerDamaged[0][playerid]);
	PlayerTextDrawHide(playerid, textPlayerDamaged[1][playerid]);
	SetPVarInt(playerid, "varDamageTake", 0);

	return 1;
}

//public  OnRejectedHit (playerid, hit [E_REJECTED_HIT])
stock checkDanoForPlayer(playerid, damagedid, Float:amount, WEAPON:weaponid)
{
	new string[128], 
		weapon_name[25];

	GetWeaponName(weaponid, weapon_name);

    playerCombo[0][playerid] += amount;

	format(string, sizeof string, "dano em %s~n~%s~n~", PlayerName[damagedid], weapon_name);
	PlayerTextDrawSetString(playerid, textPlayerDamager[0][playerid], string);
	PlayerTextDrawShow(playerid, textPlayerDamager[0][playerid]);

	format(string, sizeof string, "+%.0f", playerCombo[0][playerid]);
	PlayerTextDrawSetString(playerid, textPlayerDamager[1][playerid], string);
	PlayerTextDrawShow(playerid, textPlayerDamager[1][playerid]);

	if (GetPVarInt(playerid, "varDamageGive"))
	{
	    KillTimer(GetPVarInt(playerid, "varDamageGive"));
	}
	SetPVarInt(playerid, "varDamageGive", SetTimerEx("hideDamageGive", 5000, false, "i", playerid));

	playerCombo[1][damagedid] += amount;

	format(string, sizeof string, "dano de %s~n~%s~n~", PlayerName[playerid], weapon_name);
	PlayerTextDrawSetString(damagedid, textPlayerDamaged[0][damagedid], string);
	PlayerTextDrawShow(damagedid, textPlayerDamaged[0][damagedid]);

	format(string, sizeof string, "+%.0f", playerCombo[1][damagedid]);
	PlayerTextDrawSetString(damagedid, textPlayerDamaged[1][damagedid], string);
	PlayerTextDrawShow(damagedid, textPlayerDamaged[1][damagedid]);
	
	if (GetPVarInt(damagedid, "varDamageTake"))
	    KillTimer(GetPVarInt(damagedid, "varDamageTake"));

	SetPVarInt(damagedid, "varDamageTake", SetTimerEx("hideDamageTake", 5000, false, "i", damagedid));
}

CMD:hitmark(playerid) 
{
	if (GetPVarInt(playerid, "gPlayerHitMark_DB")) 
	{
	    SendClientMessage(playerid, COLOR_GREY, "Você desligou o hitmark.");
	    SetPVarInt(playerid, "gPlayerHitMark_DB", 0);
	} 
	else 
	{
	    SendClientMessage(playerid, COLOR_GREY, "Você ligou o hitmark.");
	    SetPVarInt(playerid, "gPlayerHitMark_DB", 1);
	}
	return 1;
}

#define MAX_HIT_MARKS  (35)

enum hitMarkEnum 
{
	bool:
		hitValid,

	PlayerText3D:
		hitText,
		hitTick,
}
static playerHitMark[MAX_PLAYERS][MAX_HIT_MARKS][hitMarkEnum];

stock createPlayerHitMark(playerid, Float:amount, weaponid, color = 0xFFFFFF40)
{
	// Checar se é arma de fogo
	if (weaponid < 21 or weaponid > 38) return false;

	// Variáveis
	static
		Float:x,
		Float:y,
		Float:z,
		Float:fx,
		Float:fy,
		Float:fz
	;

	// Pegar posição do último tiro
	GetPlayerLastShotVectors(playerid, fx, fy, fz, x, y, z);

	// Loop
	for(new index; index < MAX_HIT_MARKS; index++) 
	{
	    if (!playerHitMark[playerid][index][hitValid]) 
		{
	        // Validar
	        playerHitMark[playerid][index][hitValid] = true;
	    
	        // Tempo para destruir
	        playerHitMark[playerid][index][hitTick]  = GetTickCount() + 1000;
	    
	        // Criar 3d texts
	        new string[10];
	        format(string, sizeof (string), "%.0f", amount);
	        playerHitMark[playerid][index][hitText] = CreatePlayer3DTextLabel(playerid, string, color, x, y, z, 180.0);
	    
	        return 1;
	    }
	}
	return 0;
}

stock destroyPlayerHitMarks(playerid) 
{
	for(new index; index < MAX_HIT_MARKS; index++) {
	    if (playerHitMark[playerid][index][hitValid] && GetTickCount() > playerHitMark[playerid][index][hitTick]) {
	        // Invalidar
	        playerHitMark[playerid][index][hitValid] = false;

	        // Destruir 3d text
	        DeletePlayer3DTextLabel(playerid, playerHitMark[playerid][index][hitText]);
	    }
	}
	return 1;
}

stock resetPlayerHitMarks(playerid) 
{
	for(new index; index < MAX_HIT_MARKS; index++) {
	    playerHitMark[playerid][index][hitValid] = false;
	}
	return 1;
}

//----------------------------------------------------------

new WEAPON:weapon_blocked[MAX_PLAYERS][13];
new ammo_blocked[MAX_PLAYERS][13];

stock BlockPlayerTempWeapons(playerid)
{
	block_temp_weapons[playerid] = true;

	for(new slot; slot != 13; slot++) {
		GetPlayerWeaponData(playerid, WEAPON_SLOT:slot, WEAPON:weapon_blocked[playerid][slot], ammo_blocked[playerid][slot]);
	}
	SaveLastWeapons(playerid);

	return ResetPlayerWeapons(playerid);
}

stock GivePlayerTempWeapons(playerid)
{
	if (Admin_GetNivel(playerid) < ENCARREGADO && Staff_GetWorking(playerid))
		return false;

	block_temp_weapons[playerid] = false;

	for(new slot; slot != 13; slot++) {
		GivePlayerWeapon(playerid, weapon_blocked[playerid][slot], ammo_blocked[playerid][slot]);
	}
	return true;
}

stock SaveLastWeapons(playerid)
{
	new WEAPON:weapon[13];
	new ammo[13];

	for(new wslot; wslot != 13; wslot++) {
		GetPlayerWeaponData(playerid, WEAPON_SLOT:wslot, weapon[wslot], ammo[wslot]);
	}

	format(PlayerInfo[playerid][pLastWeapons], 250, "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d", weapon[0], weapon[1], 
		weapon[2], weapon[3], weapon[4], weapon[5], weapon[6], weapon[7], weapon[8], weapon[9], weapon[10], weapon[11], weapon[12], ammo[0], ammo[1], 
		ammo[2], ammo[3], ammo[4], ammo[5], ammo[6], ammo[7], ammo[8], ammo[9], ammo[10], ammo[11], ammo[12]);
}

CALLBACK:LoadLastWeapons(playerid)
{
	new WEAPON:weapon[13], ammo[13];

	sscanf(PlayerInfo[playerid][pLastWeapons], "P< | >iiiiiiiiiiiiiiiiiiiiiiiiii", weapon[0], weapon[1], weapon[2], weapon[3], weapon[4], weapon[5], weapon[6], weapon[7], 
		weapon[8], weapon[9], weapon[10], weapon[11], weapon[12], ammo[0], ammo[1], ammo[2], ammo[3], ammo[4], ammo[5], ammo[6], ammo[7], ammo[8], ammo[9], ammo[10],
		ammo[11], ammo[12]);

	for(new wslot; wslot != 13; wslot++) {
		GivePlayerWeapon(playerid, weapon[wslot], ammo[wslot]);
		GetPlayerWeaponData(playerid, WEAPON_SLOT:wslot, weapon_blocked[playerid][wslot], ammo_blocked[playerid][wslot]);
	}

	SetPVarInt(playerid, "LastWeaponsLoadded", 1);
	return true;
}

hook OnPlayerWeaponShot(playerid, weaponid, BULLET_HIT_TYPE:hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if ((hittype == BULLET_HIT_TYPE_VEHICLE) && (22 <= weaponid <= 38)) {
	    CallLocalFunction("OnPlayerShootVehicle", "iii", playerid, hitid, weaponid);
	}
	return 1;
}