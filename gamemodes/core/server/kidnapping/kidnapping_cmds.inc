CMD:sequestros(playerid)
{
	if (!IsACop(playerid) && !Admin_GetNivel(playerid)) return SendClientMessage(playerid, -1, "Voc� precisa ser policial para usar esse comando.");

	new string[128];
	new count = 0;

	MEGAString[0] = EOS;

	strcat(MEGAString, "ID/Nome\tResgate\n");

	foreach(new players : Character)
	{
	    if (GetPlayerBeingAbducted(players))
		{
			format(string, sizeof string, "%02d %s\t{00AA00}%s\n", players, PlayerName[players], getFormatText(resgateValor[players]));
            strcat(MEGAString, string);

			List_SetPlayers(playerid, count, players);
            count ++;
		}
	}

    format(string, sizeof string, " {FFFFFF}Sequestros ({FF0000}%d{FFFFFF})", count);

	ShowPlayerDialog(playerid, 8814, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Localizar", "Fechar");

    return 1;
}

CMD:cativeiros(playerid)
{
    if (!IsACop(playerid) && !isOrgSeq(playerid)) return SendClientMessage(playerid, -1, "Voc� precisa ser sequestrador ou policial para usar esse comando.");

	MEGAString[0] = EOS;

	strcat(MEGAString, "Cativeiro\tCidade\n");

	strcat(MEGAString, "{7D8084}Cativeiro I\t{FFFFFF}Las venturas\n");
	strcat(MEGAString, "{7D8084}Cativeiro II\t{FFFFFF}Las venturas\n");
	strcat(MEGAString, "{7D8084}Cativeiro III\t{FFFFFF}Las venturas\n");

    ShowPlayerDialog(playerid, 8813, DIALOG_STYLE_TABLIST_HEADERS, "Cativeiros para sequestros", MEGAString, "Localizar", "Fechar");
	return 1;
}

CMD:sequestrar(playerid, params[])
{
	new idPlayer, valorSequestro;
	if (sscanf(params, "ud", idPlayer, valorSequestro)) return SendClientMessage(playerid, -1, "Modo de uso: /sequestrar (id do jogador) (valor do resgate)");

	if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

	if (valorSequestro < 3000 || valorSequestro > 1500000) return SendClientMessage(playerid, -1, "O valor do resgate deve estar entre $3.000 � $1.500.000");

	if (!isOrgSeq(playerid)) return SendClientMessage(playerid, -1, "Voc� n�o � de alguma organiza��o com permiss�o para sequestros.");

	if (PlayerInfo[playerid][pCargo] < 3) return SendClientMessage(playerid, -1, "Voc� precisa ser cargo 3 ou mais para sequestrar.");

	if(PlayerInfo[playerid][pLevel] < 2)
		return SendClientMessage(playerid, -1, "Voc? precisa ter no m?nimo n?vel 2 para usar esse comando.");

	new org = GetPlayerOrg(playerid),
		car = GetPlayerVehicleID(playerid),
	    string[128];

	if (IsPlayerInSafeZone(idPlayer)) 
		return SendClientMessage(playerid, -1, "Voc� n�o pode fazer isso em uma �rea Segura.");

	if (GetPlayerBeingAbducted(idPlayer)) return SendClientMessage(playerid, -1, "O jogador j� est� sendo sequestrado.");

	if (idPlayer == playerid) return SendClientMessage(playerid, -1, "Voc� n�o pode se auto sequestrar.");

   	if (orgKidnapping[org] == true) return SendClientMessage(playerid, -1, "Sua organiza��o pode fazer apenas 1 sequestro por payday.");

   	if (sequestrosAtivo > 0 && CountCops() < 15) {
		SendClientMessage(playerid, -1, "Est� ocorrendo um sequestro, � necess�rio ter mais de 15 policiais onlines...");
		SendClientMessage(playerid, -1, "...para fazer um segundo sequestro, aguarde mais policiais ou o sequestro acabar.");
	}

	if (sequestrosAtivo > 1) return SendClientMessage(playerid, -1, "Est� tendo 2 sequestros no momento, aguarde acabar para sequestrar algu�m.");

	if (!ProxDetectorS(8.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Voc� n�o est� pr�ximo a vitima.");

	if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInVehicle(idPlayer, car)) {

		format(string, sizeof(string), "(Sequestro): %s, %s da(o) %s est� sequestrando %s, resgate: $%s.", GetPlayerCargo(playerid), PlayerName[playerid], GetOrgName(org), PlayerName[idPlayer], getFormatText(valorSequestro));
	    SendClientMessageToAll(COLOR_LIGHTRED, string);

		format(string, sizeof(string), "** %s sequestrou %s.", PlayerName[playerid], PlayerName[idPlayer]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

		SendClientMessage(playerid, 0xFF0000AA, "Leve a vitima para um cativeiro, digite: /cativeiros para ver os locais de cativeiro.");
		SendClientMessage(playerid, 0xFF0000AA, "Amarre a v�tima /amarrar, desamarre apenas quando chegar ao cativeiro.");

		TogglePlayerControllable(idPlayer, false);
		SetPlayerBeingAbducted(idPlayer, true);
		SetPlayerArmour(idPlayer, 100);
		SetPlayerHealth(idPlayer, 100);
	 	Player_SetMuted(idPlayer, false);
		resgateValor[idPlayer] = valorSequestro;
		orgKidnapping[org] = true, sequestrosAtivo++;

	} else {
		return SendClientMessage(playerid, -1, "O jogador n�o est� em seu ve�culo ou voc� n�o � o motorista.");
	}
	return true;
}

CMD:retirarorgaos(playerid, params[])
{
    if (!isOrgSeq(playerid)) return SendClientMessage(playerid, -1, "Voc� n�o � de alguma organiza��o com permiss�o para sequestros.");

    if (PlayerInfo[playerid][pCargo] < 5) return SendClientMessage(playerid, -1, "Voc� precisa ser cargo 5+ para retirar �rg�os.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /retirarorgaos (id do jogador)");

	if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

	if (!IsPlayerInRangeOfPoint(playerid, 3.0, 2561.0088,-1290.1510,1031.4219)) return SendClientMessage(playerid, -1, "Voc� n�o est� no local de retirar �rg�os.");

	if (!GetPlayerBeingAbducted(idPlayer)) return SendClientMessage(playerid, -1, "Esse jogador n�o est� sequestrado.");

 	if (!ProxDetectorS(2.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Voc� n�o est� pr�ximo a vitima.");

	new string[128], usoCativeiro;

    foreach(new i : Player) {
		if (usandoCativeiro[i] == GetPlayerVirtualWorld(playerid)) usoCativeiro++;
	}

	if (usoCativeiro > 0) return SendClientMessage(playerid, -1, "Esse cativeiro est� em uso.");

	// Anima��es e posi��o da v�tima
	SetPlayerPos(idPlayer, 2556.0110,-1290.1171,1032.4509);
	SetPlayerFacingAngle(idPlayer, 91.0550);
	ApplyAnimation(idPlayer, "CRACK", "crckdeth3", 4.1, false, true, true, true, 1, SYNC_ALL);
	TogglePlayerControllable(idPlayer, false);
	retirandoOrgaos[idPlayer] = true;
	SetPlayerCameraPos(idPlayer, 2556.0093,-1289.1479,1032.4509 - 0.3);
	SetPlayerCameraLookAt(idPlayer, 2555.8774,-1299.5475,1031.4219 + 1.0);

	// Anima��es e posi��o do respons�vel por retirar os �rg�os
	SetPlayerPos(playerid, 2556.7039,-1289.7200,1031.4219);
	SetPlayerFacingAngle(playerid, 90.6503);
	ApplyAnimation(playerid, "OTB", "betslp_in", 4.1, false, true, true, true, 1, SYNC_ALL);
	ApplyAnimation(playerid, "OTB", "betslp_in", 4.1, false, true, true, true, 1, SYNC_ALL);
	TogglePlayerControllable(playerid, false);
	retirandoOrgaos[playerid] = true;
	SetPlayerCameraPos(playerid, 2553.6091, -1290.9683, 1031.4219 + 3.0);
	SetPlayerCameraLookAt(playerid, 2555.2087, -1289.2042, 1032.4509);
	SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, 11716, 6, 0.0809, 0.0519, -0.0120, 109.6000, -3.1000, 176.8000, 1.0000, 1.0000, 1.0000); // Faca na m�o

	// Iniciando o timer para retirada de �rg�os
	format(string, sizeof string, "Retirando �rg�os... %i%", 0);
	textRipOrgan[playerid] = CreateDynamic3DTextLabel(string, 0x9D3A3AF9, 2556.0110, -1290.1171, 1032.4509 - 1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GetPlayerVirtualWorld(playerid));

	SetPVarInt(playerid, "timerRipOrgan_Start", SetTimerEx("ripOrgan_Start", 1700, false, "iii", playerid, idPlayer, 0));

	usandoCativeiro[playerid] = GetPlayerVirtualWorld(playerid);

	format(string, sizeof(string), "** %s est� retirando os �rg�os de %s.", PlayerName[playerid], PlayerName[idPlayer]);
	SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

	SendClientMessage(idPlayer, 0xFF0000AA, "Est�o retirando seus �rg�os... Em alguns minutos, voc� morrer�.");
	SendClientMessage(playerid, 0xFF0000AA, "Para cancelar caso algu�m pague o resgate use: /cancelarorgaos (id do jogador).");

	format(string, sizeof(string), "(SEQUESTRO): %s, %s come�ou a retirar �rg�os de %s.", GetPlayerCargo(playerid), PlayerName[playerid], PlayerName[idPlayer]);
	SendClientMessageToAll(COLOR_LIGHTRED, string);


    /*foreach(new x : Player)
	{
		if (IsPlayerInRangeOfPoint(playerid, 3.0, 2561.0088,-1290.1510,1031.4219))
			PlayAudioStreamForPlayer(x, ""SERVER_SITE"/gritos.mp3", 2556.0110, -1290.1171, 1032.4509, 20.0, 1);
	}*/
	return true;
}
alias:retirarorgaos("rorgaos")

CMD:cancelarorgaos(playerid, params[])
{
	new idPlayer;
    if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /cancelarorgaos (id do jogador)");

    if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

    if (idPlayer == playerid) return false;

	if (!retirandoOrgaos[playerid]) return SendClientMessage(playerid, -1, "Voc� n�o est� retirando �rg�os de Ninguem.");

	new string[128];

    usandoCativeiro[playerid] = 0;

	if (!GetPlayerBeingAbducted(idPlayer)) return SendClientMessage(playerid, -1, "Esse jogador n�o est� sequestrado.");

	TogglePlayerControllable(playerid, true);
	retirandoOrgaos[playerid] = false;
	SetCameraBehindPlayer(playerid);
	ClearAnimations(playerid);

	TogglePlayerControllable(idPlayer, true);
	retirandoOrgaos[idPlayer] = false;
	SetCameraBehindPlayer(idPlayer);
	ClearAnimations(idPlayer);

	format(string, sizeof(string), "** %s cancelou a retirada de �rg�os da v�tima: %s.", PlayerName[playerid], PlayerName[idPlayer]);
   	SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	KillTimer(GetPVarInt(playerid, "timerRipOrgan_Start"));
	DestroyDynamic3DTextLabel(textRipOrgan[playerid]); 
	SetPVarInt(playerid, "timerRipOrgan_Start", -1);
	return true;
}

CMD:refemliberar(playerid, params[])
{
    if (!isOrgSeq(playerid)) return SendClientMessage(playerid, -1, "Voc� n�o � de alguma organiza��o com permiss�o para sequestros.");

	new idPlayer;
    if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /refemliberar (id do jogador)");

    if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

    if (retirandoOrgaos[playerid]) return SendClientMessage(playerid, -1, "O jogador est� na mesa de cirurgia retirando os �rg�os, /cancelarorgaos.");

	if (!GetPlayerBeingAbducted(idPlayer)) return SendClientMessage(playerid, -1, "Esse jogador n�o est� sequestrado.");

   	if (!ProxDetectorS(5.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Voc� n�o est� pr�ximo a vitima.");

    if (idPlayer == playerid) return SendClientMessage(playerid, -1, "Voc� n�o pode se auto liberar.");

	new string[128];

   	format(string, sizeof(string), "(Sequestro): A v�tima do sequestro: %s, foi liberada pelo sequestrador %s. Sequestro finalizado!",PlayerName[idPlayer],PlayerName[playerid]);
	SendClientMessageToAll(COLOR_LIGHTRED, string);

	format(string, sizeof(string), "** %s liberou a v�tima do sequestro: %s.", PlayerName[playerid], PlayerName[idPlayer]);
   	SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

  	SetPlayerBeingAbducted(idPlayer, false);
	  
	sequestrosAtivo--;
	
	Player_SetMuted(idPlayer, false);
   	
	TogglePlayerControllable(idPlayer, true);

	return true;
}
alias:refemliberar("refliberar")

CMD:arrastarrefem(playerid, params[])
{
    if (!isOrgSeq(playerid)) return SendClientMessage(playerid, -1, "Voc� n�o � de alguma organiza��o com permiss�o para sequestros.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /arrastarrefem (id do jogador)");

	if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, -1, "Voc� precisa ser o motorista do ve�culo que a v�tima est�.");

	if (!IsPlayerInRangeOfPoint(playerid, 25.0, 2919.8228,2117.9873,17.8955) && !IsPlayerInRangeOfPoint(playerid, 25.0, 2811.0066,2919.7876,36.5046) && !IsPlayerInRangeOfPoint(playerid, 25.0, 2007.0468,2910.1699,47.8231))
		return SendClientMessage(playerid, -1, "Voc� n�o est� pr�ximo � um cativeiro (/cativeiros).");

	if (!GetPlayerBeingAbducted(idPlayer)) return SendClientMessage(playerid, -1, "Esse jogador n�o est� sequestrado.");

 	if (!ProxDetectorS(2.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Voc� n�o est� pr�ximo a vitima.");

	new string[128];

	format(string, sizeof(string), "** %s arrastou a vitima %s para dentro do cativeiro.", PlayerName[playerid], PlayerName[idPlayer]);
	SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

	if (IsPlayerInRangeOfPoint(playerid, 25.0, 2919.8228,2117.9873,17.8955))
	{
	    SetPlayerVirtualWorld(idPlayer, 1001);
		SetPlayerVirtualWorld(playerid, 1001);
 	}
 	else if (IsPlayerInRangeOfPoint(playerid, 25.0, 2811.0066,2919.7876,36.5046))
 	{
 	    SetPlayerVirtualWorld(idPlayer, 1002);
		SetPlayerVirtualWorld(playerid, 1002);
 	}
	else if (IsPlayerInRangeOfPoint(playerid, 25.0, 2007.0468,2910.1699,47.8231))
	{
	    SetPlayerVirtualWorld(idPlayer, 1003);
		SetPlayerVirtualWorld(playerid, 1003);
	}

	// Posi��o da v�tima
	SetPlayerPos(idPlayer, 2561.0088, -1290.1510, 1031.4219);
	SetPlayerFacingAngle(idPlayer, 91.0550);
	SetPlayerInterior(idPlayer, 2);
	TogglePlayerControllable(idPlayer, false);

	// Posi��o do respons�vel por retirar os �rg�os
	SetPlayerPos(playerid, 2561.0088, -1290.1510 + 1, 1031.4219);
	SetPlayerFacingAngle(playerid, 90.6503);
	SetPlayerInterior(playerid, 2);
	return true;
}
alias:arrastarrefem("arefem")

CMD:terminarsequestro(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ADMINISTRADOR) return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para usar esse comando.");

	new string[78];
	new sequestrosOn = 0;

	foreach(new i : Player)
	{
		if (GetPlayerBeingAbducted(i))
		{
		    sequestrosOn++, sequestrosAtivo--;

   			SetPlayerBeingAbducted(i, false);

			usandoCativeiro[i] = 0;
		}
	}
	if (sequestrosOn >= 1)
	{
		format(string, sizeof(string), "AdmAviso: %s, %s finalizou todos os sequestros.", Staff_GetPositionName(playerid), PlayerName[playerid]);
		SendClientMessageToAll(COLOR_DBLUE, string);
	} else {
		SendClientMessage(playerid, -1, "N�o h� nenhum sequestro acontecendo nesse momento.");
	}
	return true;
}

CMD:refemsalvar(playerid, params[])
{
	if (!IsACop(playerid) && OnDuty[playerid] != 1) return SendClientMessage(playerid, -1, "Voc� n�o � um policial ou n�o est� fardado.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /refemsalvar (id do jogador)");

	if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

	if (!GetPlayerBeingAbducted(idPlayer)) return SendClientMessage(playerid, -1, "O jogador n�o est� sequestrado.");

	if (!ProxDetectorS(8.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Voc� n�o est� pr�ximo ao jogador.");

	if (idPlayer == playerid) return SendClientMessage(playerid, -1, "Voc� n�o pode se auto salvar.");

	new string[128];

	format(string, sizeof(string), "** Voc� foi salvo pelo %s, %s da %s.", GetPlayerCargo(playerid), PlayerName[playerid], NomeORG(playerid));
	SendClientMessage(idPlayer, COLOR_LIGHTBLUE, string);

	format(string, sizeof(string), "(Sequestro): A v�tima: %s, foi salva pelo %s, %s da %s. Sequestro finalizado!", PlayerName[idPlayer], GetPlayerCargo(playerid), PlayerName[playerid], NomeORG(playerid));
	SendClientMessageToAll(COLOR_LIGHTRED, string);

	format(string, sizeof(string), "Voc� salvou a v�tima do sequestro %s.", PlayerName[idPlayer]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	GameTextForPlayer(idPlayer, "~g~~h~Libertado", 2500, 3);

	TogglePlayerControllable(idPlayer, true);

	SetPlayerBeingAbducted(idPlayer, false); 

	sequestrosAtivo--;

	Player_SetMuted(idPlayer, false);

	return true;
}

CMD:desamarrar(playerid, params[])
{
	if (!isOrgSeq(playerid) && !IsACop(playerid)) return SendClientMessage(playerid, -1, "Voc� precisa ser policial ou sequestrador.");

	if (PlayerInfo[playerid][pCargo] < 2) return SendClientMessage(playerid, -1, "Voc� precisa ser cargo 2+ para desamarrar.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /desamarrar (id do jogador)");

	if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

	if (!ProxDetectorS(8.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Voc� n�o est� pr�ximo ao jogador.");

	if (idPlayer == playerid) return SendClientMessage(playerid, -1, "Voc� n�o pode desamarrar � si mesmo.");

	if (!GetPlayerBeingAbducted(idPlayer)) return SendClientMessage(playerid, -1, "Esse jogador n�o est� sequestrado.");

	new string[78];

	format(string, sizeof(string), "** Voc� foi desamarrado pelo jogador %s[%d].", PlayerName[playerid], playerid);
	SendClientMessage(idPlayer, COLOR_LIGHTBLUE, string);

	format(string, sizeof(string), "** Voc� desamarrou o jogador %s[%d].", PlayerName[idPlayer], idPlayer);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

	TogglePlayerControllable(idPlayer, true);
	Player_SetMuted(idPlayer, false);

	return true;
}

CMD:amarrar(playerid, params[])
{
	if (!isOrgSeq(playerid)) return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para usar esse comando.");

	if (PlayerInfo[playerid][pCargo] < 2) return SendClientMessage(playerid, -1, "Voc� precisa ser cargo 2+ para amarrar.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /amarrar (id do jogador)");

	if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

	if (!IsPlayerInVehicle(idPlayer, GetPlayerVehicleID(playerid))) return SendClientMessage(playerid, -1, "O jogador precisa estar dentro do seu ve�culo.");

	if (idPlayer == playerid) return true;

	if (IsPlayerInSafeZone(idPlayer)) 
		return SendClientMessage(playerid, -1, "Voc� n�o pode fazer isso em uma �rea Segura.");

	new string[73];

	format(string, sizeof(string), "* %s amarrou %s", PlayerName[playerid], PlayerName[idPlayer]);
	SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

	GameTextForPlayer(idPlayer, "~r~Amarrado", 2500, 3);
	TogglePlayerControllable(idPlayer, false);
	Player_SetMuted(idPlayer, false);

	return true;
}