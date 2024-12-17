CMD:abordar(playerid, params[])
{
	if (!IsACop(playerid)) return SendClientMessage(playerid, -1, "Você não é um policial!");

	if (OnDuty[playerid] != 1) return SendClientMessage(playerid, -1, "Você não Bateu o cartão!");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Use: /(ab)ordar [playerid]");

	if(!Player_Logado(idPlayer))
		return SendClientMessage(playerid, -1, "O jogador não está logado no servidor.");

	if (GetPlayerSpecialAction(idPlayer) == SPECIAL_ACTION_USEJETPACK)
		return SendClientMessage(playerid, -1, "Você não pode usar esse comando em um jogador de JetPack.");

	if (IsPlayerInSafeZone(idPlayer)) 
		return SendClientMessage(playerid, -1, "Você não pode fazer isso em uma Área Segura.");

	if (Staff_GetWorking(idPlayer))
		return SendClientMessage(playerid, -1, "Não é permitido abordar um administrador em modo trabalho");

	new string[128];
	if (gettime() < GetPVarInt(idPlayer, #varFlood_Abordado))
	{
		format(string, sizeof (string), "O jogador foi abordado há pouco tempo, aguarde %s para usar novamente.", ConvertTempo(GetPVarInt(idPlayer, #varFlood_Abordado) - gettime()));
		return SendClientMessage(playerid, -1, string);
	}

	if (!Player_Logado(idPlayer))
		return SendClientMessage(playerid, -1, "O jogador não está logado no servidor!");

	if (!ProxDetectorS(25.0, playerid, idPlayer))
		return SendClientMessage(playerid, -1, "Esse jogador está longe de você!");
			
	if (GetPVarInt(idPlayer, "Abordado"))
		return SendClientMessage(playerid, -1, "Algum oficial já está abordando esta pessoa !");

	if (IsACop(idPlayer) && OnDuty[idPlayer] != 0) 
		return SendClientMessage(playerid, -1, "Você não pode abordar um policial fardado.");

	if(Player_GetJailed(idPlayer))
		return SendClientMessage(playerid, -1, "Este jogador já está preso!");

	if(IsPlayerESC(idPlayer))
		return SendClientMessage(playerid, -1, "Não é permitido abordar jogadores ausentes!");

	new complemento[64] = "ACEITE AS ORDENS OU SERÁ DETIDO!";
	if(IsPlayerInAnyVehicle(idPlayer))
		complemento = "DESÇA DO VEÍCULO E ACEITE AS ORDENS!";

	format(
		string, sizeof(string), 
		"((Megafone)) << %s, %s diz: PARADO! ESSA É UMA ABORDAGEM POLICIAL, %s >>", 
		GetPlayerCargo(playerid), PlayerName[playerid], complemento
	);
	SendClientMessageInRange(60.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
	SendClientMessageInRange(60.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);

	format(string, sizeof string, "* O oficial %s está abordando você, escolha uma opção!", PlayerName[playerid]);
	SendClientMessage(idPlayer, COLOR_LIGHTRED, string);
	format(string, sizeof string, "* Você está abordando %s, aguarde o mesmo escolher uma opção!", PlayerName[idPlayer]);
	SendClientMessage(playerid, COLOR_LIGHTRED, string);

	format(string, sizeof(string), "* O oficial %s está abordando %s.", PlayerName[playerid], PlayerName[idPlayer]);
	SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	format(string, sizeof(string), "(Abordar): %s abordou o jogador %s ID: %d", PlayerName[playerid], PlayerName[idPlayer], idPlayer);
	server_log("abordar", string);

	SetPVarInt(idPlayer, "VarDano", gettime() + 60);
	SetPVarInt(idPlayer, "Abordado", 1);
	SetPVarInt(idPlayer, #varFlood_Abordado, gettime() + (60 * 2));
	SetPVarInt(idPlayer, "OficialAbordagem", playerid);
	SetPVarInt(idPlayer, "TimerAbordagem", SetTimerEx("Abordagem", 15000, false, "ii", idPlayer, 0));
	SetPVarInt(playerid, "Abordando", idPlayer);
	SetPVarInt(playerid, "Abordou", 1);

	removeWantedPoints[idPlayer] = gettime() + 900;

	PlayerTextDrawSetString(playerid, textAbordagem[1][playerid], "~y~~h~ABORDAGEM POLICIAL");
	PlayerTextDrawSetString(idPlayer, textAbordagem[1][idPlayer], "~y~~h~ABORDAGEM POLICIAL");
	PlayerTextDrawSetString(idPlayer, textAbordagem[2][idPlayer], "Voce esta sendo abordado pelos policiais, voce tem ~r~~h~~h~15 segundos ~w~para escolher uma opcao");
	PlayerTextDrawSetString(idPlayer, textAbordagem[3][idPlayer], "OPCOES:~n~~g~Y ~w~= Aceitar a abordagem~n~~r~~h~~h~N ~w~= Recusar a abordagem");
	for(new x; x != 4; x++) {
		PlayerTextDrawShow(idPlayer, textAbordagem[x][idPlayer]);
	}

	format(string, sizeof(string), "Voce esta ~y~abordando ~w~o cidadao %s", PlayerName[idPlayer]);
	ShowPlayerMessage(playerid, string, 8000);

	return true;
}
alias:abordar("ab")

CMD:imo(playerid, params[])
{
	if (!IsACop(playerid) && GetPlayerOrg(playerid) != 7) return SendClientMessage(playerid, -1, "Você precisa ser uma autoridade para usar esse comando.");

	if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "Não é possível imobilizar dentro de um veículo.");

	new suspect;
	if(sscanf(params, "u", suspect))
		return SendClientMessage(playerid, -1, "Use: /imo [id]");

	if (!Player_Logado(suspect)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (IsPlayerInAnyVehicle(suspect)) return SendClientMessage(playerid, -1, "O suspeito está dentro de um veículo, aguarde o mesmo sair.");

	if (GetPlayerWeapon(suspect) > WEAPON:21) return SendClientMessage(playerid, -1, "O suspeito precisa estar desarmado.");

	if (GetDistanceForPlayer(playerid, suspect) > 3) return SendClientMessage(playerid, -1, "Você está longe do suspeito.");

	if (IsACop(suspect)) return SendClientMessage(playerid, -1, "Você não pode imobilizar um oficial.");

	new string[96];

	format(string, sizeof(string), "* Você foi imobilizado por %s por 20 segundos.", PlayerName[playerid]);
	SendClientMessage(suspect, COLOR_LIGHTBLUE, string);

	format(string, sizeof(string), "* Você imobilizou o(a) %s por 20 segundos.", PlayerName[suspect]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

	format(string, sizeof(string), "* %s imobilizou %s, para não fugir.", PlayerName[playerid], PlayerName[suspect]);
	SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	GameTextForPlayer(suspect, "~r~Imobilizado", 2500, 3), TogglePlayerControllable(suspect, false);
	ApplyAnimation(suspect, "CRACK", "crckdeth2", 4.0, true, false, false, false, 0, SYNC_NONE);

	if (GetPVarInt(suspect, "varFugitivo"))
	{
		SetPVarInt(suspect, "varFugitivo", 0);
		SpawnPlayer(suspect);
		KillTimer(GetPVarInt(suspect, "varTimerFugitivo"));
		SetPVarInt(suspect, "varTimerFugitivo", -1);
		SendClientMessage(suspect, COLOR_LIGHTRED, "* Você não conseguiu escapar, os policiais te pegaram e você voltou pra cadeia !");
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você capturou esse fugitivo, o mesmo voltou pra cadeia !");
	}
	return true;
}

CMD:algemar(playerid, params[])
{
	if (Founders_GetList(playerid)) {
		goto skip_founder_algemar;
	}

	if (Admin_GetNivel(playerid) >= SUPERVISOR && Staff_GetWorking(playerid)) {
		goto skip_admin_algemar;
	}

	if (!IsACop(playerid) && GetPlayerOrg(playerid) != 7) 
		return SendClientMessage(playerid, -1, "Você não é um policial.");

	if (OnDuty[playerid] != 1) 
		return SendClientMessage(playerid, -1, "Você não bateu o cartão.");

	if (IsPlayerInCombat(playerid)) 
		return SendClientMessage(playerid, -1, "Você está em modo combate, aguarde 1 minuto para usar o comando novamente.");

	skip_founder_algemar:
	skip_admin_algemar:

	new idplayer;

	if (sscanf(params, "u", idplayer)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /algemar (id do jogador)");

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (IsPlayerInAnyVehicle(idplayer) || IsPlayerInAnyVehicle(playerid)) 
		return SendClientMessage(playerid, -1, "Você não pode algemar um jogador em um veículo.");

	if (!ProxDetectorS(8.0, playerid, idplayer)) 
		return SendClientMessage(playerid, -1, "Você precisa estar próximo ao jogador.");

	if (IsACop(idplayer) && OnDuty[idplayer] != 0) 
		return SendClientMessage(playerid, -1, "Você não pode algemar um policial fardado.");

	if (GetPlayerWeapon(idplayer) > WEAPON:1 || GetPlayerHoldingExplosive(playerid)) 
		return SendClientMessage(playerid, -1, "Você não pode algemar um jogador segurando uma arma.");

	if (idplayer == playerid) 
		return 1;

	new string[128];

	if (Admin_GetNivel(playerid) >= SUPERVISOR && Admin_GetNivel(playerid) < DONO && Staff_GetWorking(playerid)) {
		format(string, sizeof(string), "(( %s, %s %s %s ))", Staff_GetPositionName(playerid), PlayerName[playerid], !IsPlayerCuffed(idplayer) ? "algemou" : "desalgemou", PlayerName[idplayer]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
	}
	else if (Admin_GetNivel(playerid) >= DONO) {
		format(string, sizeof(string), "(( %s, %s %s %s ))", Staff_GetPositionName(playerid), PlayerName[playerid], !IsPlayerCuffed(idplayer) ? "algemou" : "desalgemou", PlayerName[idplayer]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
	}
	else {
		format(string, sizeof(string), "(( %s, %s %s %s ))", GetPlayerCargo(playerid), PlayerName[playerid], !IsPlayerCuffed(idplayer) ? "algemou" : "desalgemou", PlayerName[idplayer]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
	}

	//format(string, sizeof(string), "(( %s, %s %s %s ))", GetPlayerCargo(playerid), PlayerName[playerid], !IsPlayerCuffed(idplayer) ? "algemou" : "desalgemou", PlayerName[idplayer]);
	//SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

	if (Admin_GetNivel(playerid) >= SUPERVISOR) {
		if (IsPlayerCuffed(idplayer)) {
			ShowPlayerMessage(idplayer, "Voce foi ~g~~h~desalgemado ~w~pelo ~p~admin", 4000);
			Player_SetHandcuffed(idplayer, false);
		} else {
			ShowPlayerMessage(idplayer, "Voce foi ~r~~h~algemado ~w~pelo ~p~admin", 4000);
			Player_SetHandcuffed(idplayer, true);
		}
	} else {
		if (IsPlayerCuffed(idplayer)) {
			ShowPlayerMessage(idplayer, "Voce foi ~g~~h~desalgemado ~w~pelo policial", 4000);
			Player_SetHandcuffed(idplayer, false);
		} else {
			ShowPlayerMessage(idplayer, "Voce foi ~r~~h~algemado ~w~pelo policial", 4000);
			Player_SetHandcuffed(idplayer, true);
		}
	}
	return 1;
}
alias:algemar("desalgemar")

CMD:d(playerid, params[])
{
	if(isnull(params))return SendClientMessage(playerid, -1, "Use: (/d)epartamento [texto]");

	new org = GetPlayerOrg(playerid);
	if(org != 1 && org != 2 && org != 3 && org != 4 && org != 7 && org != 11
		&& org != 33 && org != 34 && org != 16 && org != 29 && org != 35)
	{
		return SendClientMessage(playerid, -1, "Você não pode usar este comando");
	}
		
	//Anti Divulguer
	new gstring[128];

	if(gettime() < GetPVarInt(playerid, #VarFlood4))
		return SendClientMessage(playerid, COLOR_GRAD, #Você não pode usar este comando com tanta frequencia);
	SetPVarInt(playerid, #VarFlood4, gettime()+5);

	format(gstring, sizeof(gstring), "* %s falou algo no radio.", PlayerName[playerid]);
	SendClientMessageInRange(20.0, playerid, gstring, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	format(gstring, sizeof gstring, "** %s %s: %s **", GetOrgName(org), PlayerName[playerid], params);
	if (org == 7 && PlayerInfo[playerid][pCargo] > 2) {
		format(gstring, sizeof gstring, "** %s %s: %s **", GetPlayerCargo(playerid), PlayerName[playerid], params);
	}

	#if defined _CENSORED_protection
		censored_word_detected(gstring);
	#endif

	SendCopMessageAll(COLOR_LIGHTRED, gstring);
	SendMembersMessage(7, COLOR_LIGHTRED, gstring);

	return true;
}
alias:d("departamento")

CMD:m(playerid, result[])
{
    if (gettime() < GetPVarInt(playerid, #varFlood_megafone)) return SendClientMessage(playerid, -1, "Você não pode usar este comando com tanta frequencia");

    if (!IsACop(playerid) && !Admin_GetNivel(playerid) && GetPlayerOrg(playerid) != 16 && GetPlayerOrg(playerid) != 7)
        return SendClientMessage(playerid, -1, "Você não tem permissão para usar este comando.");

    if (OnDuty[playerid] != 1 && !Admin_GetNivel(playerid) && GetPlayerOrg(playerid) != 16 && GetPlayerOrg(playerid) != 7)
        return SendClientMessage(playerid, -1, "Você precisa bater o cartão para usar este comando.");

    if (isnull(result)) return SendClientMessage(playerid, -1, "Modo de uso: /m (texto no megafone)");

    new string[128];

    if (Admin_GetNivel(playerid) && Staff_GetWorking(playerid)) {
        format(string, sizeof(string), "((Megafone)) << %s diz: %s >>", PlayerName[playerid], result);
        SendClientMessageInRange(60.0, playerid, string, COLOR_ADMIN, COLOR_ADMIN, COLOR_ADMIN, COLOR_ADMIN, COLOR_ADMIN);
    } else {
        format(string, sizeof(string), "((Megafone)) << %s, %s diz: %s >>", GetPlayerCargo(playerid), PlayerName[playerid], result);
        SendClientMessageInRange(60.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
        SendClientMessageInRange(60.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    }

	#if defined _CENSORED_protection
		censored_word_detected(string);
	#endif
    
    format(string, sizeof(string), "(Megafone): %s[%d] usou o megafone", PlayerName[playerid], playerid);
    server_log("megafone", string);

    return SetPVarInt(playerid, #varFlood_megafone, gettime() + 2);
}

CMD:r(playerid, params[])
{
	if(isnull(params))return SendClientMessage(playerid, -1, "Use: (/r)adio [texto]");

	new gstring[128];
	new org = GetPlayerOrg(playerid);
	if(org != 1 && org != 2 && org != 3 && org != 4 && org != 7 && org != 11
	&& org != 33 && org != 34 && org != 16 && org != 29 && org != 35)
	{
		return SendClientMessage(playerid, -1, "Você não pode falar no rádio de uma organização");
	}
	//Anti Divulguer
	format(gstring, sizeof(gstring), "* %s falou algo no radio.", PlayerName[playerid]);

	#if defined _CENSORED_protection
		censored_word_detected(gstring);
	#endif

	SendClientMessageInRange(20.0, playerid, gstring, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	format(gstring, sizeof gstring, "** %s %s: %s **", GetPlayerCargo(playerid), PlayerName[playerid], params);
	SendMembersMessage(org, 0x6666CCFF, gstring);
	return true;
}

CMD:grampear(playerid, params[])
{
	if (GetPlayerOrg(playerid) != 33 && GetPlayerOrg(playerid) != 11) 
		return SendClientMessage(playerid, -1, "Você não pode usar o comando, pois não é da Polícia Civil ou da Polícia Federal.");
	if (OnDuty[playerid] != 1)
		return SendClientMessage(playerid, -1, "Você não bateu o cartão.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /grampear (id do jogador)");
	if (!Player_Logado(idPlayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");
	if (idPlayer == playerid) return true;

	SendMsgF(playerid, COLOR_LIGHTRED, "Você está grampeando o jogador %s. Para cancelar, use /desgrampear", PlayerName[idPlayer]);
	SetPVarInt(playerid, "grampoPlayer", idPlayer);
	SetPVarInt(playerid, "grampoModo", 1);
	return 1;
}

CMD:desgrampear(playerid)
{
	if (GetPlayerOrg(playerid) != 33 && GetPlayerOrg(playerid) != 11) 
		return SendClientMessage(playerid, -1, "Você não pode usar o comando, pois não é da Polícia Civil ou da Polícia Federal.");

	SetPVarInt(playerid, "grampoModo", 0);
	SendMsgF(playerid, COLOR_GRAD, "Você parou de grampear %s.", PlayerName[GetPVarInt(playerid, "grampoPlayer")]);
	return 1;
}

CMD:revistar(playerid, params[])
{
	if (!IsACop(playerid))
		return SendClientMessage(playerid, -1, "Você não é policial.");

	if (OnDuty[playerid] != 1)
		return SendClientMessage(playerid, -1, "Você não bateu o cartão.");

	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /revistar (ID do jogador)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "O jogador não está conectado no servidor.");

	if (!ProxDetectorS(8.0, playerid, idplayer))
		return SendClientMessage(playerid, -1, "O jogador está longe de você.");

    if (!IsPlayerWithHandsUp(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador precisa se render (/handsup) para você revistá-lo.");

	if (idplayer == playerid)
		return SendClientMessage(playerid, -1, "Você não pode se revistar.");

	MEGAString[0] = EOS;

	new drugNames[5][30] = {"Maconha", "Cocaína", "Crack", "Heroína", "Metanfetamina"},
		types[5] = {ITEM_TYPE_MACONHA, ITEM_TYPE_COCAINA, ITEM_TYPE_CRACK, ITEM_TYPE_HEROINA, ITEM_TYPE_METANFETAMINA},
		count = 0;

	strcat(MEGAString, "{FF6347}---------------------- Revista de Ilegalidades ----------------------\n{FFFFFF}");

	for(new i = 0; i < 5; i++) {
		new qtd = GetPlayerItemTypeAmount(idplayer, types[i]);
		if(qtd > 0) {
			FormatCat(MEGAString, "- %d gramas de %s\n", qtd, drugNames[i]);
			count += 1;
		}
	}

	new saldoMateriais = GetPlayerItemTypeAmount(idplayer, ITEM_TYPE_MATERIAL);
	if (saldoMateriais > 0) {
		FormatCat(MEGAString, "- %d materiais para fabricação de armamento\n", saldoMateriais);
		count += 1;
	}

	if(count == 0)
		strcat(MEGAString, "{B7B7B7}- Nada consta\n");

	strcat(MEGAString, "\n{FF6347}------------------------- Revista de Armas ---------------------------\n{FFFFFF}");
	
	count = 0;

	new WEAPON:weapon, ammo,
		weapon_name[25];

	for(new i = 1; i <= 11; i++) {
		if(i == 10)
			continue;

		GetWeaponName(weapon, weapon_name);
		GetPlayerWeaponData(idplayer, WEAPON_SLOT:i, weapon, ammo);

		if(ammo > 0) {
			FormatCat(MEGAString, "- %s com %d de munição\n", weapon_name, ammo);
			count += 1;
		}
	}

	if(count == 0)
		strcat(MEGAString, "{B7B7B7}- Nada consta\n");


	strcat(MEGAString, "\n{FF6347}------------------------ Revista de Licenças ------------------------\n{FFFFFF}");

	FormatCat(MEGAString, "{FFFFFF}- Motorista: %s\n", IsPlayerHaveItem(idplayer, ITEM_TYPE_MOTORISTA) ? ("{00AA00}Positivo") : ("{FF0000}Negativo"));
	FormatCat(MEGAString, "{FFFFFF}- Piloto: %s\n", IsPlayerHaveItem(idplayer, ITEM_TYPE_PILOTO) ? ("{00AA00}Positivo") : ("{FF0000}Negativo"));
	FormatCat(MEGAString, "{FFFFFF}- Marujo: %s\n", IsPlayerHaveItem(idplayer, ITEM_TYPE_MARUJO) ? ("{00AA00}Positivo") : ("{FF0000}Negativo"));
	strcat(MEGAString, "{FFFFFF}- Pescador: {00AA00}Positivo\n");
	FormatCat(MEGAString, "{FFFFFF}- Armas: %s\n", PlayerInfo[idplayer][pGunLic] ? ("{00AA00}Positivo") : ("{FF0000}Negativo"));

	new string[128];
	
	format(string, sizeof(string), "(( %s revistou %s para ver se tem qualquer item ilegal ))", PlayerName[playerid], PlayerName[idplayer]);
	SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT,COR_ACAOCHAT,COR_ACAOCHAT,COR_ACAOCHAT,COR_ACAOCHAT);

	format(string, sizeof(string), "Revista de %s", PlayerName[idplayer]);
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, string, MEGAString, "Fechar", "");
	
	return 1;
}

CMD:procurados(playerid, params[])
{
	if (!IsACop(playerid) && GetPlayerOrg(playerid) != 7)
		return SendClientMessage(playerid, -1, "Você não é um policial.");

	MEGAString[0] = EOS;

	strcat(MEGAString, "ID\tNick\tNível de procura\tOrganização\n");

	new string[128],
		countprocurados;

	foreach(new i : Player) {
		if (Player_GetWanted(i) && (!Admin_GetNivel(i) || !Staff_GetWorking(i))) {
			format(string, sizeof string, "{FFFFFF}%d\t%s\t%d\t{%s}%s\n", i, PlayerName[i], Player_GetWanted(i), GetOrgColor(GetPlayerOrg(i)), NomeORG(i));
			strcat(MEGAString, string);

			List_SetPlayers(playerid, countprocurados, i);
            countprocurados ++;
		}
	}

	if (!countprocurados)
		return SendClientMessage(playerid, -1, "Não há procurados online."); 

	inline DialogList(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused pid, dialogid, inputtext

		if (response) {
			new playersend = List_GetPlayers(playerid, listitem);

			if (!Player_Logado(playersend))
				return SendClientMessage(playerid, -1, "O jogador não está mais conectado/logado no servidor.");

			format(string, sizeof(string), "%d", playersend);
			callcmd::procurar(playerid, string);
		}
	}
	Dialog_ShowCallback(playerid, using inline DialogList,
		DIALOG_STYLE_TABLIST_HEADERS,
		""C_WHITE"Suspeitos online", MEGAString, "Procurar", "Fechar"
	);

	return 1;
}

static IsPlayerInLimparFicha(playerid) 
{
	if (IsPlayerInRangeOfPoint(playerid, 3.0, 253.9279,69.0127,1003.6406) 	||	// Departamento de policia | Interior (6)
	    IsPlayerInRangeOfPoint(playerid, 2.0, 234.8419,111.2194,1003.2257) 	||  // Departamento da policia | Interior (10)
	    IsPlayerInRangeOfPoint(playerid, 2.0, 198.9671,168.1982,1003.0234))	{	// Departamento da policia | Interior (3)
		return true;
	}

	return false;
}

CMD:limparficha(playerid, params[])
{
	if (PlayerIsMafia(playerid)) return SendClientMessage(playerid, -1, "Você é um mafioso, use: /invadirfichas (id do jogador) (valor).");

	if (!IsACop(playerid)) return SendClientMessage(playerid, -1, "Você precisa ser autoridade policial para usar esse comando.");

	if (PlayerInfo[playerid][pCargo] < 4) return SendClientMessage(playerid, -1, "Você precisa ser cargo 4 ou superior para usar esse comando.");

	if (OnDuty[playerid] != 1) return SendClientMessage(playerid, -1, "Você precisa bater o cartão para usar esse comando.");

	if (!IsPlayerInLimparFicha(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está no local para limpar fichas.");

	new result[18], idplayer;
	if (sscanf(params, "us[18]", idplayer, result)) return SendClientMessage(playerid, -1, "Modo de uso: /limparficha (id do jogador) (motivo)");

	if (idplayer == playerid) return SendClientMessage(playerid, -1, "Você não pode limpar sua própria ficha de crimes.");

	if (strlen(result) < 5 || strlen(result) > 17) return SendClientMessage(playerid, -1, "O motivo deve conter de 5 a 17 caracteres!");

	if (!Player_Logado(idplayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	new string[128];

   	format(string, sizeof(string), "<< COPOM: %s, %s limpou a ficha criminal de %s, motivo: %s >>", GetPlayerCargo(playerid), PlayerName[playerid], PlayerName[idplayer], result);
	SendCopMessage(TEAM_BLUE_COLOR, string);

	format(string, sizeof(string), "* %s, %s da(o) %s limpou sua ficha criminal, motivo: %s.", GetPlayerCargo(playerid), PlayerName[playerid], NomeORG(playerid), result);
	SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);

	Player_SetWanted(idplayer, 0); 
	ClearCrime(idplayer);

	return true;
}

stock IsPlayerInPrender(playerid) {

	if (IsPlayerInRangeOfPoint(playerid, 5.0, 1545.3387,-1607.8325,13.3828) ||		//  HQ Policia Militar
		IsPlayerInRangeOfPoint(playerid, 5.0, 354.1136,-1506.8484,32.9804)	||		//	HQ BOPE
		IsPlayerInRangeOfPoint(playerid, 5.0, 1706.9711,-1332.8363,13.5469)	||		//	HQ Policia Civil
		IsPlayerInRangeOfPoint(playerid, 5.0, 1754.9194,-1564.7217,10.0820) ||		//	Prisão La Sante
		IsPlayerInRangeOfPoint(playerid, 5.0, -82.5581,-363.3431,1.4297) ||     	//	HQ CORE
	    IsPlayerInRangeOfPoint(playerid, 5.0, 1284.7302,-2048.9648,58.9519)) {		//  HQ Policia Federal
		return true;
	}

	return false;
}

CMD:prender(playerid, params[])
{
    if (!IsACop(playerid)) return SendClientMessage(playerid, -1, "Você não é um policial.");

    if (OnDuty[playerid] != 1) return SendClientMessage(playerid, -1, "Você não está fardado.");

	new idplayer;
	if (sscanf(params, "u", idplayer)) {
		return (
			CallRemoteFunction("CheckAndArrestDealer", "d", playerid) ||
			SendClientMessage(playerid, -1, "Modo de uso: /prender (id do jogador) ou /prender próximo a um traficante.")
		);
	}

	if (!Player_Logado(idplayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (GetDistanceForPlayer(playerid, idplayer) > 14) return SendClientMessage(playerid, -1, "Você tem que estar próximo ao jogador para prende-lo.");

	if (!Player_GetWanted(idplayer)) return SendClientMessage(playerid, -1, "O jogador deve ter no mínimo 1 nível de procurado.");

	if (Player_GetJailed(idplayer)) return SendClientMessage(playerid, -1, "O jogador já está preso.");

	if (!IsPlayerInPrender(playerid)) return SendClientMessage(playerid, -1, "Você não está no local de prender.");

	new string[128], wantedLevel = Player_GetWanted(idplayer), pricePrisao = (3000 * wantedLevel);

	format(string, sizeof(string), "** %s prendeu o jogador %s com %d níveis de procurado.", PlayerName[playerid], PlayerName[idplayer], wantedLevel);
	SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

	GameTextForPlayer(idplayer, "~r~Condenado...", 5000, 5);

	VozDePrisao[idplayer] = 0;
	PlayerInfo[playerid][pMinhasApreensoes]++;
	ResetPlayerWeapons(idplayer);

	new lucro = 10000;	// Paga a Taxa ao Governo
	format(string, sizeof(string), "<< COPOM >>: %s efetuou uma prisão, recebeu $%s no cofre.", NomeORG(playerid), getFormatText(lucro));
	SendMembersMessage(GetPlayerOrg(playerid), COLOR_LIGHTRED, string), SendMembersMessage(7, COLOR_LIGHTRED, string);

	Player_RemoveMoney(idplayer, pricePrisao);
	OrgInfo_SetMoney(GetPlayerOrg(playerid), OrgInfo_GetMoney(GetPlayerOrg(playerid)) + lucro);

	Player_SetCadeia(idplayer, 24, (wantedLevel * 60), PlayerName[playerid], PlayerCrime[idplayer][pAccusedof], GetPlayerOrg(playerid));

	if(PlayerInfo[playerid][pVIP] == 1)
		PlayerInfo[playerid][pJailTime] -= floatround(PlayerInfo[playerid][pJailTime] * 0.05);
	else if(PlayerInfo[playerid][pVIP] > 1 && PlayerInfo[playerid][pVIP] <= 6)
		PlayerInfo[playerid][pJailTime] -= floatround(PlayerInfo[playerid][pJailTime] * 0.10);
	else if(PlayerInfo[playerid][pVIP] == 7)
		PlayerInfo[playerid][pJailTime] -= floatround(PlayerInfo[playerid][pJailTime] * 0.20);
	else if(PlayerInfo[playerid][pVIP] == 8)
		PlayerInfo[playerid][pJailTime] -= floatround(PlayerInfo[playerid][pJailTime] * 0.30);

	format(string, sizeof(string), "Você foi condenado a %s de prisão com %d níveis de procurado, sem direito a fiança.", ConvertTempo(PlayerInfo[idplayer][pJailTime]), wantedLevel);
	SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);

	SpawnPlayer(idplayer);
	Player_SetMuted(idplayer, false);

	TogglePlayerControllable(idplayer, true);

	Player_SetHandcuffed(idplayer, false);

	return true;
}

CMD:apreender(playerid, params[])
{
    if ((!IsACop(playerid) && OnDuty[playerid] != 1) && GetPlayerOrg(playerid) != 7) 
		return SendClientMessage(playerid, -1, "Você não é um policial ou não está fardado.");

	if (sscanf(params, "s[128]", params))
	{
	    SendClientMessage(playerid, -1, "Modo de uso: /retirar (nome) (id do jogador)");
	    SendClientMessage(playerid, COLOR_GRAD, "NOMES: armas | drogas | materiais");
		SendClientMessage(playerid, COLOR_GRAD, "NOMES: ilicitos (sementes de maconha, explosivos, drogas, materiais, armas)");
 		SendClientMessage(playerid, COLOR_GRAD, "_________________________________________________");
		return true;
	}

	new string[128], null[25], idPlayer;

    if (strfind(params, "armas", true) != -1)
    {
		if (sscanf(params, "s[25]d", null, idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /retirar armas (id do jogador)");

		if (!ProxDetectorS(8.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Você não está próximo ao jogador.");

        format(string, sizeof(string), "* %s, %s retirou as armas de %s.", GetPlayerCargo(playerid), PlayerName[playerid], PlayerName[idPlayer]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		ResetPlayerWeapons(idPlayer);
	}
	else if (strfind(params, "drogas", true) != -1)
    {
    	if (sscanf(params, "s[25]d", null, idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /retirar drogas (id do jogador)");

    	if (!ProxDetectorS(8.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Você não está próximo ao jogador.");

        format(string, sizeof(string), "* %s, %s retirou as drogas de %s.", GetPlayerCargo(playerid), PlayerName[playerid], PlayerName[idPlayer]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		ResetAllItensType(idPlayer, ITEM_TYPE_MACONHA);
		ResetAllItensType(idPlayer, ITEM_TYPE_COCAINA);
		ResetAllItensType(idPlayer, ITEM_TYPE_CRACK);
		ResetAllItensType(idPlayer, ITEM_TYPE_HEROINA);
		ResetAllItensType(idPlayer, ITEM_TYPE_METANFETAMINA);
	}
	else if (strfind(params, "materiais", true) != -1)
    {
 		if (sscanf(params, "s[25]d", null, idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /retirar materiais (id do jogador)");

 		if (!ProxDetectorS(8.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Você não está próximo ao jogador.");

        format(string, sizeof(string), "* %s, %s retirou os materiais de %s.", GetPlayerCargo(playerid), PlayerName[playerid], PlayerName[idPlayer]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		ResetAllItensType(idPlayer, ITEM_TYPE_MATERIAL);
	}
	else if (strfind(params, "ilicitos", true) != -1)
    {
		if (sscanf(params, "s[25]d", null, idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /retirar ilicitos (id do jogador)");

		if (!ProxDetectorS(8.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Você não está próximo ao jogador.");

        format(string, sizeof(string), "* %s, %s retirou todos os itens ilicitos de %s.", GetPlayerCargo(playerid), PlayerName[playerid], PlayerName[idPlayer]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		// Drogas 
		ResetAllItensType(idPlayer, ITEM_TYPE_MACONHA);
		ResetAllItensType(idPlayer, ITEM_TYPE_COCAINA);
		ResetAllItensType(idPlayer, ITEM_TYPE_CRACK);
		ResetAllItensType(idPlayer, ITEM_TYPE_HEROINA);
		ResetAllItensType(idPlayer, ITEM_TYPE_METANFETAMINA);

		// Materiais
		ResetAllItensType(idPlayer, ITEM_TYPE_MATERIAL);

		// Armas
		if(PlayerInfo[idPlayer][pGunLic])
			ResetPlayerWeapons(idPlayer);
	

		// Explosivos
		PlayerInfo[idPlayer][pExplosives] = 0;

		// Sementes
		ResetAllItensType(idPlayer, ITEM_TYPE_SEMENTE);
	}
	else
	{
		SendClientMessage(playerid, -1, "Modo de uso: /retirar (nome) (id do jogador)");
	    SendClientMessage(playerid, COLOR_GRAD, "NOMES: motorista | piloto | marujo | portearmas | armas | drogas | materiais | ilicitos");
 		SendClientMessage(playerid, COLOR_GRAD, "_________________________________________________");
	}
	return true;
}
alias:apreender("retirar")

hook DealWithPlayerInPosition(playerid) {
	callcmd::batercartao(playerid);
	return 1;
}

CMD:taser(playerid, params[])
{
	if (IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, -1, "Você não pode usar este comando dentro de um veículo !");

	if (IsPlayerInCombat(playerid)) return SendClientMessage(playerid, -1, "Você está em modo combate, aguarde 1 minuto para usar o comando novamente.");

	if(IsACop(playerid) or GetPlayerOrg(playerid) == 16 or GetPlayerOrg(playerid) == 7)
	{
		new string[128];
		if(InTaser[playerid] == true)
		{
			GivePlayerWeapon(playerid, WEAPON_DEAGLE, 999);
			InTaser[playerid] = false;
			format(string, sizeof(string), "*%s guardou seu taser", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			return true;
		}
		if(InTaser[playerid] == false)
		{
			if(gettime() < GetPVarInt(playerid, #VarFlood9))
				return SendClientMessage(playerid, -1, "O Taser esta recarregando, espere 15 segundos para pegar novamente.");
			SetPVarInt(playerid, #VarFlood9, gettime()+15);

			InTaser[playerid] = true;
			GivePlayerWeapon(playerid, WEAPON_SILENCED, 1);
			format(string, sizeof(string), "*%s pegou seu taser", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			return true;
		}
	}
	else
	{
		SendClientMessage(playerid,-1,"Você não pode usar este comando.");
	}
	return true;
}

CMD:batercartao(playerid)
{
	new string[83], playerOrg = GetPlayerOrg(playerid);

	if (IsACop(playerid))
	{
		if(PlayerToPoint(2,playerid,1530.3060,-1702.4915,6.2252) || PlayerToPoint(2,playerid,326.6374,307.1123,999.1484) || PlayerToPoint(2,playerid,240.6516,112.8062,1003.2188) 
		|| PlayerToPoint(2,playerid,255.1123,77.4241,1003.6406) || PlayerToPoint(2,playerid,229.8059,164.7830,1003.0234) || PlayerToPoint(2,playerid,-1346.8774,491.9250,11.2027) 
		|| PlayerToPoint(2,playerid,712.7550,-554.5677,-3.5950) || PlayerToPoint(2,playerid,359.1856,211.4973,1008.3828) || PlayerToPoint(2,playerid,226.2034,121.5204,1010.2188) 
		|| PlayerToPoint(2,playerid,1585.3612,-1692.0748,-21.0025))
		{
			if (OnDuty[playerid] == 0)
			{
				ShowModelSelectionMenu(playerid, (GetPlayerOrg(playerid) == 3 ? SkinsCopListSimple : SkinsCopsList), "Escolha seu uniforme", 200, 0x000000AA);
				return true;
			}
			else
			{
				format(string, sizeof(string), "<< %s: %s %s retirou sua farda. >>", GetOrgName(playerOrg), GetPlayerCargo(playerid), PlayerName[playerid]);
				SendCopMessage(0xFF8282AA, string);

				SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);

				OnDuty[playerid] = 0;
				EmpregoDuty[playerid] = 0;

				SetPlayerToTeamColor(playerid);
			}
		}
	}
	return true;
}

CMD:cops(playerid)
{

	new string[128];
	new count = 0;

	MEGAString[0] = EOS;

	strcat(MEGAString, "Id        Nome\tCargo\tTelefone\tOrganização\n");

	foreach(new players : Character) {

	    if (IsACop(players)) {

			format(string, sizeof string, "%02d  %s\tCOP\t%d\t{%06x}%s\n", players, PlayerName[players], PlayerInfo[players][numeroCelular], (GetPlayerColor(players) >>> 8), GetOrgName(GetPlayerOrg(players)));
            strcat(MEGAString, string);

            List_SetPlayers(playerid, count, players);
            count ++;
		}
	}

    format(string, sizeof string, " {FFFFFF}Policiais Online ({00FF00}%d{FFFFFF})", count);

	ShowPlayerDialog(playerid, 4275, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Enviar SMS", "Fechar");

    return 1;
}
alias:cops("policiais")

CMD:su(playerid, params[])
{
	if (!IsACop(playerid) && GetPlayerOrg(playerid) != 7 && GetPlayerOrg(playerid) != 16)
		return SendClientMessage(playerid, -1, "Você não tem autoridade para usar o comando.");

	if (OnDuty[playerid] != 1 && GetPlayerOrg(playerid) != 7 && GetPlayerOrg(playerid) != 16)
		return SendClientMessage(playerid, -1, "Você precisa bater cartão para usar esse comando.");

	new crimeid = -1, idPlayer, result[20];
	if (sscanf(params, "us[15]", idPlayer, result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /su (id do jogador) (descrição do crime)");

	if (strlen(result) > 20)
		return SendClientMessage(playerid, -1, "Você precisa digitar um crime de até 20 caracteres.");

	if (!Player_Logado(idPlayer)) 
		return SendClientMessage(playerid, -1, "Este jogador não está conectado/logado.");

	if (!ProxDetectorS(30.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Você não está próximo desse suspeito.");

	if(PlayerInfo[playerid][pLevel] < 2)
		return SendClientMessage(playerid, -1, "Você precisa ter no mínimo nível 2 para usar esse comando.");

	new string[100];

	if (gettime() < GetPVarInt(idPlayer, #varFlood_Suspeito))
	{
		format(string, sizeof (string), "O jogador levou /su a pouco tempo, aguarde %s para usar novamente.", ConvertTempo(GetPVarInt(idPlayer, #varFlood_Suspeito) - gettime()));
		return SendClientMessage(playerid, -1, string);
	}

	for(new x; x != sizeof CrimesValidos; x++)
	{
		if(!strcmp(result, CrimesValidos[x][SuTag], true))
		{
			crimeid = x; break;
		}
	}

	if (crimeid == -1)
	{
		MEGAString[0] = EOS;

		strcat(MEGAString, "{FF0000}Você só poderá usar um dos crimes abaixo:\n\n");

		for(new x; x != sizeof CrimesValidos; x++)
		{
			format(string, sizeof string, "{FFFFFF}%s: \t{999999}%s\n", CrimesValidos[x][SuTag], CrimesValidos[x][SuDesc]);
			strcat(MEGAString, string);
		}

		ShowPlayerDialog(playerid, 8724, DIALOG_STYLE_MSGBOX, "Crimes válidos", MEGAString, "Fechar","");
		return 1;
	}

	if (GetPlayerOrg(idPlayer) == 7) return SendClientMessage(playerid, -1, "Você não pode aplicar o comando em autoridades do governo.");

	if (IsACop(idPlayer) && OnDuty[idPlayer] != 0) return SendClientMessage(playerid, -1, "Você não pode usar em um policial fardado.");

	//if (GoChase[idPlayer] < 999) return SendClientMessage(playerid, -1, "Você não pode aplicar o comando em assassinos com contrato.");

	SetPlayerCriminal(idPlayer, playerid, CrimesValidos[crimeid][SuDesc]);
	ServerLog::("su", "Suspeito: %s, Denunciante: %s, Crime: %s", PlayerName[idPlayer], PlayerName[playerid], CrimesValidos[crimeid][SuDesc]);
	return true;
}

CMD:supainel(playerid, params[])
{
	if (!IsACop(playerid) && GetPlayerOrg(playerid) != 7 && GetPlayerOrg(playerid) != 16)
		return SendClientMessage(playerid, -1, "Você não tem autoridade para usar o comando.");

	if (OnDuty[playerid] != 1 && GetPlayerOrg(playerid) != 7 && GetPlayerOrg(playerid) != 16)
		return SendClientMessage(playerid, -1, "Você precisa bater cartão para usar esse comando.");

	show_server_log(playerid, "", "su", 1);
	return true;
}

CMD:intimacao(playerid, params[])
{
	if (!IsACop(playerid)) {
		return SendClientMessage(playerid, -1, "Você não é um policial!");
	}
	if (!IsLeaderOrg(playerid)) {
		return SendClientMessage(playerid, -1, "Você não é um delegado!");
	}

	new idplayer;
	if(sscanf(params, "u", idplayer)) {
		return SendClientMessage(playerid, -1, "Use: /intimacao [playerid]");
	}

	if (!IsPlayerConnected(idplayer)) {
		return SendClientMessage(playerid, -1, "Jogador offline !");
	}

	if (gettime() < GetPVarInt(idplayer, "varIntimacao")) {
		return SendClientMessage(playerid, -1, "Este jogador já foi intimado a poucos minutos !");
	}

	new string[144];

	format(string, sizeof string, "[INTIMAÇÃO] Delegado(a) %s intimou o(a) %s para comparecer a delegacia.", PlayerName[playerid], PlayerName[idplayer]);
	SendClientMessageToAll(COLOR_DBLUE, string);

	MEGAString[0] = EOS;

	strcat(MEGAString, "INTIMAÇÃO:\n");
	strcat(MEGAString, "O bacharel em Direito e delegado in fine assinado, ora designado para o departamento atributivo\n");
	strcat(MEGAString, "abaixo discriminado, INTIMA Vossa Senhoria para comparecer em data e local abaixo descritos,\n");
	strcat(MEGAString, "munido de documento de identidade (RG), CPF e desta intimação, onde deverá prestar\n");
	strcat(MEGAString, "esclarecimentos do interesse da Justiça Pública, conforme caracterização convergente nesta, com o\n");
	strcat(MEGAString, "fim de prestar esclarecimentos em procedimento investigativo para apurar possível prática de infração\n");
	strcat(MEGAString, "penal. O(a) convocado(a), ausente na oitiva, depois de novamente intimado(a), não comparecer, sem\n");
	strcat(MEGAString, "motivo justificado, consoante os arts. 3º, 201, § 1º, 218 e 260, do Código de Processo Penal, será\n");
	strcat(MEGAString, "passível de condução coercitiva até a presença da Autoridade Policial, mediante Mandado escrito e\n");
	strcat(MEGAString, "incorrerá, em tese, na prática de CRIMES DE PREVARICAÇÃO E/OU DESOBEDIÊNCIA, ínsito nos arts.\n");
	strcat(MEGAString, "319 e 330, ambos do Código Penal. Havendo recusa em receber esta intimação, a mesma será\n");
	strcat(MEGAString, "concluída na presença de 02 (duas) testemunhas presentes ao fato, onde será verbalizada a intimação\n");
	strcat(MEGAString, "e assinada por todos. Havendo recusa de prestar testemunho, as pessoas requisitadas renitentes\n");
	strcat(MEGAString, "deverão informar suas qualificações e intimadas imediatamente a comparecer na delegacia. Havendo\n");
	strcat(MEGAString, "recusa em informar suas qualificações, serão conduzidas coercitivamente até a delegacia pela prática,\n");
	strcat(MEGAString, "em tese, do art. 68, do Decreto-Lei nº 3.688/1941 – Lei das Contravenções Penais – recusa de dados\n");
	strcat(MEGAString, "sobre a própria identificação ou qualificação.\n\n");

	format(string, sizeof string, "INTIMADO(A): %s\n", PlayerName[idplayer]);
	strcat(MEGAString, string);
	format(string, sizeof string, "ENDEREÇO: HQ %s\n", GetOrgName(GetPlayerOrg(playerid)));
	strcat(MEGAString, string);
	strcat(MEGAString, "DATA: Hoje\n");
	strcat(MEGAString, "LOCAL PARA APRESENTAÇÃO: Recepção\n");
	format(string, sizeof string, "DELEGADO: %s\n", PlayerName[playerid]);
	strcat(MEGAString, string);

	ShowPlayerDialog(idplayer, 8724, DIALOG_STYLE_MSGBOX, "INTIMAÇÃO", MEGAString, "OK","");

	SetPVarInt(idplayer, "varIntimacao", gettime() + 10*60);
	return 1;
}

CMD:dp(playerid, params[])
{
	if(IsACop(playerid))
	{
		SendClientMessage(playerid, COLOR_GRAD, "*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* Ajuda do Departamento *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*");

		SendClientMessage(playerid, COLOR_GRAD,"*** COMANDOS *** (/r)adio (/d)epartmento (/m)egafone (/su)speito /ficha /prender /batercartao /procurados /algemar");
		SendClientMessage(playerid, COLOR_GRAD,"*** COMANDOS *** /desalgemar /revistar /apreender /multar (/gov)erno /arrombar /tr /br /rbr");
		SendClientMessage(playerid, COLOR_GRAD,"*** COMANDOS *** (/imo)bilizar /equipar  /arrastar /desarmarbomba /consertarcaixa /intimacao");
		SendClientMessage(playerid, COLOR_GRAD,"*** COMANDOS *** /copom /(ab)ordar /arrombarportao /imo /grampear /desgrampear /limparficha");
		SendClientMessage(playerid, COLOR_GRAD,"*** COMANDOS *** /retirar /consertarcaixa /taser /supainel /reforco /vozdeprisao /vdp /supainel");
		SendClientMessage(playerid, COLOR_GRAD,"*** COMANDOS *** /refemsalvar /desamarrar");
		SendClientMessage(playerid, COLOR_GRAD,"*** COMANDOS *** /sequestros | Usado para ver as vitimas de sequestro, valor do resgate e tempo sequestrado.");
		if(GetPlayerOrg(playerid) == 16){
			SendClientMessage(playerid, COLOR_GRAD,"*** PRF *** /multarveiculo /apreenderveiculo /verplaca /verificar placa /verificar patio");
		}
		if(GetPlayerOrg(playerid) == 2){
			SendClientMessage(playerid, COLOR_GRAD,"*** PORTÕES *** /prota /prota2");
		}
		if(GetPlayerOrg(playerid) == 1){
			SendClientMessage(playerid, COLOR_GRAD,"*** PORTÕES *** /pp /pv /pr /pg /pe");
		}
		if(GetPlayerOrg(playerid) == 3){
			SendClientMessage(playerid, COLOR_GRAD,"*** PORTÕES *** /abrirgn");
		}
		if(GetPlayerOrg(playerid) == 33){
			SendClientMessage(playerid, COLOR_GRAD,"*** PORTÕES *** /ppc1 /ppc2");
			SendClientMessage(playerid, COLOR_GRAD,"*** OUTROS *** /radares /ajustarradar");
		}
		if(GetPlayerOrg(playerid) == 34){
			SendClientMessage(playerid, COLOR_GRAD,"*** PORTÕES *** /pbope");
		}
		SendClientMessage(playerid, COLOR_GRAD,"*** OUTROS *** /continencia - Comando para bater continência");
		
		SendClientMessage(playerid, COLOR_GRAD, "*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*");
	}
	return 1;
}

CMD:ficha(playerid, params[])
{
	if(!IsACop(playerid))
	{
		SendClientMessage(playerid, -1, "Você não é um policial!");
		return true;
	}
	if(OnDuty[playerid] != 1)
	{
		SendClientMessage(playerid, -1, "Você não Bateu o cartão!");
		return true;
	}
	new idplayer;
	if(sscanf(params, "u", idplayer))
	{
		SendClientMessage(playerid, -1, "Use: /ficha [id]");
		return true;
	}
	if (PlayerToPoint(60.0, playerid,232.8069,164.0555,1003.0234) || 
		PlayerToPoint(60.0, playerid,232.2051,117.3912,1003.2188) ||
		PlayerToPoint(20.0, playerid,322.4880,309.1409,999.1484) || 
		PlayerToPoint(40.0, playerid,246.1936,69.8609,1003.6406))
	{
		if(IsPlayerConnected(idplayer))
		{
			new string[75];
			if (Player_GetWanted(playerid))
			{
				SendClientMessage(playerid, -1, "|______________ Ficha Na Policia ______________|");
				format(string, sizeof(string), "Nome: %s", PlayerName[idplayer]);
				SendClientMessage(playerid, -1,string);
				format(string, sizeof(string), "Crime: %s", PlayerCrime[idplayer][pAccusedof]);
				SendClientMessage(playerid, COLOR_GRAD,string);
				format(string, sizeof(string), "Acusador: %s", PlayerCrime[idplayer][pVictim]);
				SendClientMessage(playerid, COLOR_GRAD,string);
			}
			else
			{
				SendClientMessage(playerid, -1, "|______________ Ficha Na Policia ______________|");
				format(string, sizeof(string), "Nome: %s", PlayerName[idplayer]);
				SendClientMessage(playerid, -1,string);
				format(string, sizeof(string), "Crime: ********");
				SendClientMessage(playerid, COLOR_GRAD,string);
				format(string, sizeof(string), "Acusador: ********");
				SendClientMessage(playerid, COLOR_GRAD,string);
			}
		}
		else
		{
			SendClientMessage(playerid, -1, "O Jogador Está Offline !");
			return true;
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "Você tem que estar em um carro da policia ou em alguma HQ da policia!");
		return true;
	}
	return true;
}

CMD:arrastar(playerid, params[])
{
	if (!IsACop(playerid)) 
		return SendClientMessage(playerid, -1, "Você não pode usar o comando, pois não é uma autoridade.");

	if (OnDuty[playerid] != 1 && GetPlayerOrg(playerid) != 7) 
		return SendClientMessage(playerid, -1, "Você não bateu o cartão.");

	if (IsPlayerInCombat(playerid)) 
		return SendClientMessage(playerid, -1, "Você está em modo combate, aguarde 1 minuto para usar o comando novamente.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /arrastar (id do jogador)");

	if (!IsPlayerConnected(idPlayer)) return SendClientMessage(playerid, -1, "Esse jogador não está conectado.");

	if (IsPlayerInAnyVehicle(idPlayer)) return SendClientMessage(playerid, -1, "Não é possível arrastar um jogador de dentro de um veículo.");

	if (!ProxDetectorS(15.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Você precisa estar próximo ao jogador.");

	if (IsACop(idPlayer) && OnDuty[idPlayer] != 0) return SendClientMessage(playerid, -1, "Você não pode arrastar um policial fardado.");

	new vehicleid = GetPlayerVehicleID(playerid), count;
	if (vehicleid == GetPlayerVehicleID(idPlayer))
		return SendClientMessage(playerid, -1, "Esse jogador já está em seu veículo.");

	for (new seat = 3; seat < 4; seat++) {
		if (!IsVehicleSeatOccupied(vehicleid, seat)) PutPlayerInVehicle(playerid, vehicleid, seat); count++; break;
	}

	if (count < 1)
		return SendClientMessage(playerid, -1, "Não ha espaço vazio nos bancos de tras.");

	if(Player_GetTimerAFK(playerid) > 0)
		return SendClientMessage(playerid, -1, "Não é permitido abordar jogadores ausentes!");

	new string[128];

	format(string, sizeof(string), "* Você foi arrastado pelo: %s.", PlayerName[playerid]);
	SendClientMessage(idPlayer, COLOR_LIGHTBLUE, string);
	format(string, sizeof(string), "* Você arrastou %s.", PlayerName[idPlayer]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	format(string, sizeof(string), "* %s arrastou %s para dentro de seu veículo.", PlayerName[playerid] ,PlayerName[idPlayer]);
	SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	GameTextForPlayer(idPlayer, "~r~Arrastado", 2500, 3);

	TogglePlayerControllable(idPlayer, false);
	return true;
}

CMD:vdp(playerid, params[])
{
	if(!IsACop(playerid))
	{
		SendClientMessage(playerid, -1, "Você não é um policial!");
		return true;
	}
	if(OnDuty[playerid] != 1)
	{
		SendClientMessage(playerid, -1, "Você não Bateu o cartão!");
		return true;
	}
	new idplayer;
	if(sscanf(params, "u", idplayer))
	{
		SendClientMessage(playerid, -1, "Use: /vozdeprisao [id] (/vdp [id])");
		return true;
	}
	if(IsPlayerConnected(idplayer))
	{
		if(idplayer != INVALID_PLAYER_ID)
		{
			if(Player_GetWanted(idplayer) == 0)
			{
				SendClientMessage(playerid, -1, "Este jogador não está sendo procurado!");
				return true;
			}
			if(VozDePrisao[idplayer] == 1)
			{
				SendClientMessage(playerid, -1, "Alguem ja deu voz de prisao a este Jogador!");
				return true;
			}

			if(Player_GetJailed(idplayer))
			{
				SendClientMessage(playerid, -1, "Este jogador já está preso!");
				return true;
			}
			if (Admin_GetNivel(idplayer) && Staff_GetWorking(idplayer))
				return SendClientMessage(playerid, -1, "Você não pode dar voz de prisão em um administrador em modo trabalho.");

			if (ProxDetectorS(9.0, playerid, idplayer))
			{
				new string[128];
				format(string, sizeof(string), "*Oficial %s diz: Parado! Você é procurado pela justiça, renda-se agora!", PlayerName[playerid]);
				SendClientMessage(idplayer, COLOR_YELLOW, string);
				format(string, sizeof(string), "Se você desconectar agora, será preso automaticamente, faça com que o policial perca-o de vista!!!", PlayerName[playerid]);
				SendClientMessage(idplayer, COLOR_YELLOW, string);
				format(string, sizeof(string), "*Você deu voz de prisao a %s.", PlayerName[idplayer]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				format(string, sizeof(string), "Se o jogador se desconectar agora, será preso automaticamente, não perca-o de vista!!!", PlayerName[idplayer]);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				PrisionVoiceTimer[idplayer] = SetTimerEx("VozDePrisaoo", 1000, true, "ii", idplayer, playerid);
				VozDePrisao[idplayer] = 1;
			}
			else
			{
				SendClientMessage(playerid, -1, "O Jogador está longe de Você !");
				return true;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "O Jogador Está Offline !");
		return true;
	}
	return true;
}
alias:vdp("vozdeprisao")

//----------------------------------{Portoes DP}--------------------------------------------
CMD:pp(playerid)
{
	if ((IsACop(playerid) || PlayerIsAdvogado(playerid))
	&& PlayerToPoint(5.0, playerid, 247.005905, 72.448440, 1003.640625)
	|| PlayerToPoint(5.0, playerid, 245.3463, 73.8183, 1003.6406))
	{ //GateInteriorCela
		MoveDynamicObject( PDDOORa, 247.005905 , 72.448440 , 1006.912902,3,0.0,0.0,1260.0);
		GameTextForPlayer(playerid, "~w~Porta das Celas ~n~~b~Aberto", 4000, 3);
		SetTimer("GaragemDpClosed", 4000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está perto do portão ou não é um Oficial ");
  	}
	return true;
}

//----------------------------------{Portoes DP2}----------------------------------------
CMD:pr(playerid)
{
	if ((IsACop(playerid)) && PlayerToPoint(15.0, playerid, 250.774871 , 60.822799 , 1003.640625))
	{ //GateGaragem
		MoveDynamicObject( PDDOORb, 250.774871 , 60.822799 , 1006.862670,3,0.0,0.0,5130.0);
		GameTextForPlayer(playerid, "~w~Porta da Recepcao ~n~~b~Aberto", 5000, 3);
		SetTimer("GaragemDpClosed2", 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está perto do portão ou não é um Oficial ");
	}
	return true;
}

//----------------------------------{Portoes DP3}----------------------------------------
CMD:pv(playerid)
{
	if ((IsACop(playerid)) && PlayerToPoint(15.0, playerid, 248.142105 , 78.125961 , 1003.640625))
	{ //GateGaragem
		MoveDynamicObject( PDDOORc, 248.142105 , 78.125961 , 1007.248718,3,0.0,0.0,12690.0);
		GameTextForPlayer(playerid, "~w~Porta do Vestiario ~n~~b~Aberto", 5000, 3);
		SetTimer("pd1", 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está perto do portão ou não é um Oficial ");
	}
	return true;
}

//----------------------------------{Portoes LS}----------------------------------------
CMD:pe(playerid)
{
	if ((IsACop(playerid)) && PlayerToPoint(15.0, playerid, 1546.8681640625, -1627.3585205078, 15.156204223633))
	{ //GateGaragem
		MoveDynamicObject( PDPMLS, 1546.86816, -1627.35852, 7.15620,3.0,0.0,0.0,90.0);
		GameTextForPlayer(playerid, "~w~Garagem Externa ~n~~b~Aberta", 4200, 3);
		SetTimer("pd2", 4200, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}

CMD:pdpsf2(playerid)
{
	if((IsACop(playerid)) && PlayerToPoint(20.0, playerid, -1571.4054,661.2745,7.1875))
	{ //GateGaragem
		MoveDynamicObject( PortaoPMSF, -1572, 672.90002441406, 6.6999998092651,3,0.0, 0.0, 90.00000);
		SetTimer("PTPMSF", 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}

CMD:pdetran(playerid)
{
	if ((GetPlayerOrg(playerid) == 16) && PlayerToPoint(20.0, playerid, 2271.17578, -122.50561, 27.07960))
	{
		MoveDynamicObject(portaoDetran1, 2271.17578, -122.50561, 27.07960 - 10.0, 3, 0.00000, 0.00000, 90.65700);
        MoveDynamicObject(portaoDetran2, 2270.97070, -113.03745, 27.13612 - 10.0, 3, 0.00000, 0.00000, 90.65700);
		SetTimer(#MovePortaoDetran, 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}

CALLBACK:MovePortaoDetran()
{
	MoveDynamicObject(portaoDetran1, 2271.17578, -122.50561, 27.07960,3, 0.00000, 0.00000, 90.65700);
    MoveDynamicObject(portaoDetran2, 2270.97070, -113.03745, 27.13612,3, 0.00000, 0.00000, 90.65700);
    return true;
}

CMD:ppc1(playerid)
{
	if ((GetPlayerOrg(playerid) == 33) && PlayerToPoint(20.0, playerid, 1622.12415, -1322.47363, 19.18700))
	{
		MoveDynamicObject(portaoPC, 1622.12415, -1322.47363, 19.18700 - 10.0, 3, 0.00000, 0.00000, 90.00000);
		SetTimer(#MovePortaoPC1, 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}

CALLBACK:MovePortaoPC1()
{
	MoveDynamicObject(portaoPC, 1622.12415, -1322.47363, 19.18700,3, 0.00000, 0.00000, 90.00000);
    return true;
}

CMD:ppc2(playerid)
{
	if ((GetPlayerOrg(playerid) == 33) && PlayerToPoint(20.0, playerid, 1658.79480, -1365.14771, 19.18700))
	{
		MoveDynamicObject(portaoPC2, 1658.79480, -1365.14771, 19.18700 - 10.0, 3, 0.00000, 0.00000, 90.00000);
		SetTimer(#MovePortaoPC2, 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}

CALLBACK:MovePortaoPC2()
{
	MoveDynamicObject(portaoPC2, 1658.79480, -1365.14771, 19.18700,3, 0.00000, 0.00000, 90.00000);
    return true;
}

CMD:pexe(playerid)
{
	if ((GetPlayerOrg(playerid) == 3) && PlayerToPoint(30.0, playerid, -1527.77454, 482.17676, 8.99428))
	{
		MoveDynamicObject(PortaoGN, -1527.77454, 482.17676, 8.99428 - 10.0, 3, 0.00000, 0.00000, -1.02000);
		SetTimer(#MovePortaoGN, 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}

CALLBACK:MovePortaoGN()
{
	MoveDynamicObject(PortaoGN, -1527.77454, 482.17676, 8.99428,3, 0.00000, 0.00000, -1.02000);
    return true;
}

/*CMD:ppf(playerid)
{
	if ((GetPlayerOrg(playerid) == 11) && PlayerToPoint(30.0, playerid, 907.35028, -1655.07056, 15.15449))
	{
		MoveDynamicObject(PortaoPF, 907.35028, -1655.07056, 15.15449 - 10.0, 3, 0.00000, 0.00000, -89.70000);
		SetTimer(#MovePortaoPF, 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}*/

/*CALLBACK:MovePortaoPF()
{
	MoveDynamicObject(PortaoPF, 907.35028, -1655.07056, 15.15449,3, 0.00000, 0.00000, -89.70000);
    return true;
}*/

CMD:pbope(playerid)
{
	if ((GetPlayerOrg(playerid) == 34) && PlayerToPoint(30.0, playerid, -79.86600, -352.73331, 3.21830))
	{
		MoveDynamicObject(PortaoBPEV, -79.86600, -352.73331, 3.21830 - 10.0, 3, 0.00000, 0.00000, 90.00000);
		SetTimer(#MovePortaoBPEV1, 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}

CALLBACK:MovePortaoBPEV1()
{
	MoveDynamicObject(PortaoBPEV, -79.86600, -352.73331, 3.21830, 3, 0.00000, 0.00000, 90.00000);
    return true;
}

// Ajeitar os portões para nova HQ BOPE
CMD:prota(playerid)
{
	if ((GetPlayerOrg(playerid) == 2) && PlayerToPoint(30.0, playerid, 283.38159, -1542.82373, 25.92710))
	{
		MoveDynamicObject(PortaoBOPE, 283.38159, -1542.82373, 25.92710 - 10.0, 3, 0.00000, 0.00000, -35.00000);
		SetTimer(#MovePortaoBOPE, 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}

CALLBACK:MovePortaoBOPE()
{
	MoveDynamicObject(PortaoBOPE, 283.38159, -1542.82373, 25.92710, 3, 0.00000, 0.00000, -35.00000);
    return true;
}

// Ajeitar os portões para nova HQ BOPE
CMD:prota2(playerid)
{
	if ((GetPlayerOrg(playerid) == 2) && PlayerToPoint(30.0, playerid, 321.12421, -1488.35999, 25.92710))
	{
		MoveDynamicObject(PortaoBOPE2, 321.12421, -1488.35999, 25.92710 - 10.0, 3, 0.00000, 0.00000, 145.00000);
		SetTimer(#MovePortaoBOPE2, 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}

CALLBACK:MovePortaoBOPE2()
{
	MoveDynamicObject(PortaoBOPE2, 321.12421, -1488.35999, 25.92710, 3, 0.00000, 0.00000, 145.00000);
    return true;
}

