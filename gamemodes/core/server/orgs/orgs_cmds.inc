CMD:lideres(playerid) {

	new string[128];
	new count = 0;

	MEGAString[0] = EOS;

	strcat(MEGAString, "Id        Nome\tCargo\tTelefone\tOrganiza��o\n");

	foreach(new players : Character) {

	    if (IsLeaderOrg(players)) {

			format(string, sizeof string, "%02d  %s\tL�der\t%d\t{%06x}%s\n", players, PlayerName[players], PlayerInfo[players][numeroCelular], (GetPlayerColor(players) >>> 8), GetOrgName(GetPlayerOrg(players)));
            strcat(MEGAString, string);

            List_SetPlayers(playerid, count, players);
            count ++;
		}
	}

    format(string, sizeof string, " {FFFFFF}L�deres Online ({00FF00}%d{FFFFFF})", count);

	ShowPlayerDialog(playerid, 4275, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Enviar SMS", "Fechar");

    return 1;
}

CMD:sublideres(playerid) {

	new string[128];
	new count = 0;

	MEGAString[0] = EOS;

	strcat(MEGAString, "Id        Nome\tCargo\tTelefone\tOrganiza��o\n");

	foreach(new players : Character) {

	    if (PlayerInfo[players][pCargo] == SUB_LIDER_1 || PlayerInfo[players][pCargo] == SUB_LIDER_2) {

			format(string, sizeof string, "%02d  %s\tSub-Lider\t%d\t{%06x}%s\n", players, PlayerName[players], PlayerInfo[players][numeroCelular], (GetPlayerColor(players) >>> 8), GetOrgName(GetPlayerOrg(players)));
            strcat(MEGAString, string);

            List_SetPlayers(playerid, count, players);
            count ++;
		}
	}

    format(string, sizeof string, " {FFFFFF}Sub-Lideres Online ({00FF00}%d{FFFFFF})", count);

	ShowPlayerDialog(playerid, 4275, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Enviar SMS", "Fechar");

    return 1;
}

CMD:pedircontas(playerid)
{
	if (!GetPlayerOrg(playerid))
        return SendClientMessage(playerid, COLOR_WHITE, "Voc� n�o faz parte de uma organiza��o.");

	if (IsPlayerInCombat(playerid)) 
        return SendClientMessage(playerid, -1, "Voc� n�o pode usar esse comando em combate.");

	SendMsgF(playerid, COLOR_LIGHTBLUE, "Voc� pediu as contas e n�o faz mais parte da organiza��o %s", NomeORG(playerid));
    DismissPlayerOrg(GetPlayerOrg(playerid), PlayerInfo[playerid][pID]);

    if (IsLeaderOrg(playerid)) {
		new string[95];

        format(string, sizeof(string), "<< L�deres >>: %s pediu as contas de l�der da organiza��o %s.", PlayerName[playerid], NomeORG(playerid));
	    Staff_ChatToAll(COLOR_LIGHTGREEN, string, ESTAGIARIO); 

        server_log("contaslider", string);
    }
	return 1;
}
alias:pedircontas("contaslider", "sairorg")

CMD:demitir(playerid, params[])
{
    // D�bito: Criar configura��o de cargos permitidos para o comando demitir.
    if (PlayerInfo[playerid][pCargo] < SUB_LIDER_2) {
        return SendClientMessage(playerid, COLOR_WHITE, "Voc� n�o tem cargo para usar o comando.");
    }

	new motivo[60], 
        idplayer
    ;

	if (sscanf(params, "us[60]", idplayer, motivo)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /demitir (id do jogador) (motivo da demiss�o)");

	if (!Player_Logado(idplayer))
        return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

	if (GetPlayerOrg(idplayer) != GetPlayerOrg(playerid)) 
        return SendClientMessage(playerid, -1, "Voc� s� pode demitir membros da sua organiza��o.");

	if (IsLeaderOrg(idplayer)) 
        return SendClientMessage(playerid, -1, "Voc� n�o pode demitir esse jogador.");

    DismissPlayerOrg(GetPlayerOrg(idplayer), Player_GetAccountID(idplayer));

	SendMsgF(playerid, COLOR_WHITE, "Voc� demitiu %s %s, de sua organiza��o. Motivo: %s.", GetPlayerCargo(idplayer), PlayerName[idplayer], motivo);

	return 1;
}

CMD:limparlider(playerid, params[])
{
	if (Admin_GetNivel(playerid) < SUPERVISOR)
		return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para usar esse comando.");

	new orgid, 
		motivo[40]
	;

	if (sscanf(params, "ds[40]", orgid, motivo)) {
		return SendClientMessage(playerid, -1, "Modo de uso: /limparlider (id org) (motivo)");
	}

	if (orgid < 1 || orgid > MAX_ORGS) {
		return SendClientMessage(playerid, -1, "O id org deve estar entre 1 � 35.");
	}

	if (strlen(motivo) < 5 || strlen(motivo) > sizeof(motivo)) {
		return SendClientMessage(playerid, -1, "O motivo deve estar entre 5 � 40 caracteres.");
	}

	// Obsoleto
	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Voc� precisa estar em modo trabalho para usar esse comando.");

	new string[128];
	format(string, sizeof(string), "AdmAviso: %s retirou lideran�a da %s, de: %s.", PlayerName[playerid], GetOrgName(orgid), OrgMembros[orgid][SLOT_LIDER][MemberName]);
	Staff_ChatToAll(COLOR_LIGHTGREEN, string, SUPERVISOR), server_log("lideres", string);

	// slotid: 0 (L�der)
	DismissPlayerOrg(orgid, OrgMembros[orgid][SLOT_LIDER][MemberID]);

	return 1;
}

CMD:promover(playerid, params[])
{
	if (!IsLeaderOrg(playerid))
        return SendClientMessage(playerid, -1, "Voc� n�o � um l�der.");

	new idplayer, 
        idcargo
    ;

	if (sscanf(params, "ud", idplayer, idcargo)) {
		return SendClientMessage(playerid, -1, "Modo de uso: /promover (id do jogador) (id do cargo)");
	}

	if (idcargo == 20 || idplayer == playerid) 
        return 1;

	if (!Player_Logado(idplayer))
        return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

    if (idcargo < 1 && idcargo > 19)
        return SendClientMessage(playerid, -1, "O id do cargo deve estar entre 1 � 19.");

	if (GetPlayerOrg(idplayer) != GetPlayerOrg(playerid)) 
        return SendClientMessage(playerid, -1, "Voc� s� pode promover membros da sua organiza��o.");

	SetPlayerCargo(idplayer, GetPlayerOrg(idplayer), idcargo);

	SendMsgF(idplayer, COLOR_LIGHTBLUE, "Voc� foi promovido a %s pelo l�der %s.", GetPlayerCargo(idplayer), PlayerName[playerid]);

    SendMsgF(playerid, COLOR_LIGHTBLUE, "Voc� promoveu %s para %s.", PlayerName[idplayer], GetPlayerCargo(idplayer));

    #if defined _CONQUEST_SYSTEM_ON
		if (idcargo > 15 && idcargo < 20) {
			CheckConquista(idPlayer, Conquista_SubLider);
		}
    #endif

	return 1;
}

CMD:convidar(playerid, params[])
{
	if (!GetPlayerOrg(playerid)) {
		return SendClientMessage(playerid, -1, "Voc� n�o faz parte de uma organiza��o.");
	}

	if (PlayerInfo[playerid][pCargo] < SUB_LIDER_2)
		return SendClientMessage(playerid, -1, "Voc� precisa ser Sub-Lider+ para usar esse comando.");

	new idplayer;

	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /convidar (id do jogador)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

	if (GetPlayerOrg(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador j� faz parte de uma organiza��o.");

	if (PlayerInfo[idplayer][pLevel] < 2)
		return SendClientMessage(idplayer, -1, "O jogador precisa ser n�vel 2 para entrar em organiza��o.");

	if (!GetSlotsInOrg(GetPlayerOrg(playerid))) {
		return SendClientMessage(playerid, COLOR_WHITE, "A organiza��o est� sem vagas.");
	}

	InviteOffer[idplayer] = playerid;
	InviteJob[idplayer] = GetPlayerOrg(playerid);

	SendMsgF(playerid, COLOR_LIGHTBLUE, "* Voc� convidou %s para sua organiza��o: %s.", PlayerName[idplayer], NomeORG(playerid));

	SetPVarInt(idplayer, "varConvite", gettime() + (3) * 60);

	new data[6];
	getdate(data[2], data[1], data[0]);
	gettime(data[3], data[4], data[5]);

	format(MEGAString, sizeof MEGAString,
	"{FFFFFF}Voc� acaba de ser convidado para uma organiza��o\n\n\
	{FFFFFF}Nome da organiza��o: \t{00FFFF}%s\n\
	{FFFFFF}Convidado pelo l�der: \t{00FFFF}%s\n\
	{FFFFFF}Data que foi convidado: \t{00FFFF}%d/%d/%d �s %d:%d:%d\n\
	{FFFFFF}O convite expira em: \t{00FFFF}3 minutos\n\n\
	{FFFFFF}Para aceitar clique em ''{00FFFF}Aceitar{FFFFFF}'' e para recusar clique em ''{00FFFF}Recusar{FFFFFF}''",
	NomeORG(playerid), PlayerName[playerid], data[0], data[1], data[2], data[3], data[4], data[5]);

	ShowPlayerDialog(idplayer, 7463, DIALOG_STYLE_MSGBOX, "Organiza��o: Convite", MEGAString, "Aceitar", "Recusar");

	new string[128];

	format(string, sizeof(string), "%s convidou %s para ORG %s", PlayerName[playerid], PlayerName[idplayer], NomeORG(playerid));
	server_log("convidar", string);

	return 1;
}

CMD:darlider(playerid, params[])
{
	if (Admin_GetNivel(playerid) < SUPERVISOR) {
		return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para usar esse comando.");
	}

	new idplayer, idorg;
	if (sscanf(params, "ud", idplayer, idorg)) return SendClientMessage(playerid, -1, "Modo de uso: /darlider (id do jogador) (organiza��o 1 a 33)");

	if (1 < idorg > MAX_ORGS)
		return SendClientMessage(playerid, -1, "A organiza��o deve estar entre 1 a 34.");

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

	if (PlayerInfo[idplayer][pPrisaoAdmin] > 19) 
		return SendClientMessage(playerid, -1, "O jogador deve ter menos que 20 pris�es administrativas para ser L�der.");

	if (Admin_GetNivel(idplayer)) {
		PlayerInfo[idplayer][pMembro] = idorg;
		PlayerInfo[idplayer][pCargo] = LIDER;
	} else {	
		if (GetPlayerOrg(idplayer))
			return SendClientMessage(playerid, -1, "Esse jogador j� faz parte de uma organiza��o.");

		if (HaveLeaderInOrg(idorg))
			return SendClientMessage(playerid, -1, "A organiza��o j� possui um l�der, use: /limparlider.");

		SetPlayerCargo(idplayer, idorg, LIDER);
	}

	SpawnPlayer(idplayer);
	printf("CMD:lider(playerid, params[]): %d", idplayer);
	SetPlayerToTeamColor(idplayer);

	SendMsgF(idplayer, COLOR_LIGHTBLUE, "** Voc� foi promovido a l�der da %s pelo admin %s **", NomeORG(idplayer), PlayerName[playerid]);

	SendMsgF(playerid, COLOR_LIGHTBLUE, "Voc� promoveu %s para lideran�a da %s.", PlayerName[idplayer], NomeORG(idplayer));

	new string[99];
	format(string, sizeof(string), "<< Lideres: (Admin: %s, Organiza��o: %s, Novo L�der: %s).", PlayerName[playerid], NomeORG(idplayer), PlayerName[idplayer]);
	server_log("lideres", string);

	// Conquista:
	CheckConquista(idplayer, Conquista_Lider);

	return 1;
}
alias:darlider("lider")

CMD:l(playerid, params[])
{
	if (!IsLeaderOrg(playerid))
		return SendClientMessage(playerid, -1, "Voc� n�o � um l�der.");

	if (isnull(params))
		return SendClientMessage(playerid, -1, "Modo de uso: /l (texto)");

	new gstring[128];

	format(gstring, sizeof gstring, "* [Lider %s] %s: %s", GetOrgName(GetPlayerOrg(playerid)), PlayerName[playerid], params);

	foreach(new lideridx : Player) 
	{
	    if (IsLeaderOrg(lideridx)) {
	        SendClientMessage(lideridx, COLOR_PEACH, gstring);
	    }
	}
	return 1;
}

CMD:entrarorg(playerid, params[])
{
	if (PlayerInfo[playerid][pVIP] < SOCIO_EXTREME)
		return SendClientMessage(playerid, -1, "Voc� n�o � um player S�CIO-EXTREME.");

	if (GetPlayerOrg(playerid)) 
		return SendClientMessage(playerid, -1, "Voc� faz parte de uma organiza��o.");

	new orgid;
	if (sscanf(params, "d", orgid))
		return SendClientMessage(playerid, -1, "Modo de uso: /entrarorg (id da org)");

	if (orgid < 1 || orgid > MAX_ORGS-1) 
		return SendClientMessage(playerid, -1, "Voc� pode escolher entre a organiza��o 1 � 34.");

	if (GetPVarInt(playerid, "timeEntrarOrg") > gettime())
		return SendMsgF(playerid, -1, "Aguarde %s para poder usar o comando novamente.", ConvertTime(GetPVarInt(playerid, "timeEntrarOrg") - gettime()));

	if (IsPlayerInCombat(playerid)) 
		return SendClientMessage(playerid, -1, "Voc� est� em modo combate, aguarde 1 minuto ap�s tomar dano.");

	if ((IsACopOrg(orgid) || orgid == 7) && Player_GetWanted(playerid)) 
		return SendClientMessage(playerid, -1, "Voc� est� procurado, n�o pode entrar em uma organiza��o governamental.");

	switch (orgid) {
		case 4, 6, 10, 23, 26, 27, 29, 30, 31, 32: 
		return SendClientMessage(playerid, -1, "N�o � poss�vel entrar nessa organiza��o.");

		case 19, 34: 
		return SendClientMessage(playerid, -1, "Esta organiza��o paga est� restrita para entrada de S�cio.");

		// case 12: 
		// SendClientMessage(playerid, -1, "Esta organiza��o � uma organiza��o paga, por�m est� permitido acesso a S�cios.");
	}

	if (CofreOrg[orgid][InvasaoTempo] > 0)
		return SendClientMessage(playerid, -1, "N�o � permitido entrar em uma organiza��o durante invas�o de HQ.");
		
	if (CofreOrg[orgid][TrainingTime] > 0)
		return SendClientMessage(playerid, -1, "N�o � permitido entrar em uma organiza��o durante treinamento.");
	
	SetPVarInt(playerid, "timeEntrarOrg", gettime() + 180);

	PlayerInfo[playerid][pMembro] = orgid;
	PlayerInfo[playerid][pCargo] = 1;

	new string[120];
	format(string, sizeof string, "{910A0A}[SOCIO] %s entrou na organiza��o:{FFFFFF} %s", PlayerName[playerid], GetNomeOrg(orgid));
	SendClientMessageToAll(playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

	SpawnPlayer(playerid);
	printf("CMD:entrarorg(playerid, params[]): %d", playerid);

	new stringlog[128];

	format(stringlog, sizeof stringlog, "%s entrou na organiza��o: %s[%d]", PlayerName[playerid], GetNomeOrg(orgid), orgid);
	server_log("entrarorg", stringlog);

	return 1;
}

CMD:setmateriais(playerid, params[])
{
	if (Dev_GetNivel(playerid) < DEV_ALPHA) 
		return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para usar esse comando.");

	new orgid, value;
	if (sscanf(params, "orgid", orgid, value)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /setmateriais (id da organiza��o) (quantidade)");

	SendMsgAllF(COLOR_DEV, "DevCmd: %s, %s setou %s materiais para organiza��o: %s", Staff_GetPositionName(playerid), PlayerName[playerid], value, GetOrgName(orgid));
    OrgInfo_SetMaterials(orgid, value);
    
	return 1;
}
alias:setmateriais("setarmat", "setmat", "defmat")