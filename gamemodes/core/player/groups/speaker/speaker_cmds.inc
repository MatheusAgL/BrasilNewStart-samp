CMD:locutores(playerid)
{
	new string[128],
		status[21],
        count = 0;

	MEGAString[0] = EOS;
	strcat(MEGAString, "id        nome\tcargo\tstatus\n");

	foreach(new speakers : Character) {
	    if (Speaker_GetNivel(speakers)) {
            if (Speaker_GetTender(speakers)) {
                status = ""C_SPEAKER"LOCUTANDO";
            } else if (GetPlayerEscTime(speakers) > 5) {
                status = ""C_RED"INDISPONÍVEL";
            } else {
                status = ""C_GREEN"DISPONÍVEL";
            }

			format(string, sizeof(string), "%02d  %s\t"C_SPEAKERD"%s\t%s\n", speakers, PlayerName[speakers], Speaker_GetPositionName(Speaker_GetNivel(speakers)), status);
            strcat(MEGAString, string);

            count++;
		}
	}
	format(string, sizeof string, ""C_WHITE"Equipe da rádio onlines: ("C_GREEN"%d"C_WHITE")", count);
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Fechar", "");
	return 1;
}

CMD:pedidos(playerid) 
    return RadioOrders_List(playerid);

CMD:pedirmusica(playerid) 
    return Radio_DialogAskMusic(playerid);

CMD:cr(playerid, result[])
{
	if (Speaker_GetNivel(playerid) < ESTAGIARIO_RADIO) 
        return SendClientMessage(playerid, -1, "Você não tem permissão para usar este comando.");

	if (isnull(result)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /cr (texto para o chat locutor)");

	new string[128];
    format(string, sizeof(string), "** [%s] %s: %s **", Speaker_GetPositionName(Speaker_GetNivel(playerid)), PlayerName[playerid], result);
    Speaker_ChatToAll(COLOR_SPEAKER, string);
	server_log("chat_locutor", string);

	return 1;
}

CMD:avr(playerid, result[])
{
	if (Speaker_GetNivel(playerid) < LOCUTOR_RADIO)
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (isnull(result)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /avr (texto)");

	new string[144];
	format(string, sizeof(string), "o< (( %s, %s: "C_WHITE"%s "C_SPEAKER"))", Speaker_GetPositionName(Speaker_GetNivel(playerid)), PlayerName[playerid], result);
	SendClientMessageToAll(COLOR_SPEAKER, string);

	return 1;
}

CMD:locutando(playerid, params[])
{
	if (Speaker_GetNivel(playerid) < LOCUTOR_RADIO) 
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!Speaker_GetTender(playerid)) {
		Speaker_SetTender(playerid, true);

		new string[80];
		format(string, sizeof(string), "~b~~h~Locutor ~n~~w~%s~n~~g~~h~locutando agora...", PlayerName[playerid]);

		foreach(new i : Player) {
			GameTextForPlayer(i, string, 5000, 1);
		}
	} else {
		SendClientMessage(playerid, -1, "Você parou de locutar.");

		Speaker_SetTender(playerid, false);
	}
	return 1;
}

CMD:radio(playerid)
{
    MEGAString [0] = EOS;

	strcat(MEGAString, "{00FFFF}  • {00FF00}Ligar rádio\n");
	strcat(MEGAString, "{00FFFF}  • {00FFFF}Pedir música\n");
	strcat(MEGAString, "{00FFFF}  • {0000FF}Locutores online\n");
	strcat(MEGAString, "{00FFFF}  • {FFFF00}Lista de locutores\n");
	strcat(MEGAString, "{00FFFF}  • {FFAA00}Últimos pedidos\n");
	strcat(MEGAString, "{00FFFF}  • {AAAAAA}Outras músicas\n");
	strcat(MEGAString, "{00FFFF}  • {576176}Desligar rádio\n");

   	ShowPlayerDialog(playerid, 4321, DIALOG_STYLE_LIST, "{00FFFF} • {FFFFFF}Menu Rádio BPS", MEGAString, "Selecionar", "Fechar");
	return 1;
}

CMD:infolocutores(playerid)
	return Speaker_List(playerid);

CMD:limparlocutor(playerid) {

	if (Speaker_GetNivel(playerid) < DIRETOR_RADIO && Admin_GetNivel(playerid) < SUB_DONO)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	return Speaker_List(playerid, 1);
}

CMD:criarlocutor(playerid, params[])
{
	if (Speaker_GetNivel(playerid) < GERENTE_RADIO && 
        Admin_GetNivel(playerid) < SUB_DONO)
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    new idplayer, level;
	if (sscanf(params, "ud", idplayer, level)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /criarlocutor (id do jogador) (nível 1 ao 7)");

    if (!Player_Logado(idplayer))
        return SendClientMessage(playerid, -1, "Esse jogador não está logado/conectado no servidor.");

	if (SpeakerNivel:level >= Speaker_GetNivel(playerid) &&
        Admin_GetNivel(playerid) < DONO) 
        return SendClientMessage(playerid, -1, "Você só pode criar locutores abaixo do seu cargo.");

	if (Speaker_GetNivel(idplayer) < ESTAGIARIO_RADIO && !Group_GetVacancy(idplayer, level, GROUP_SPEAKER) && level != 0)
		return SendClientMessage(playerid, -1, "Não há mais vagas na equipe da rádio, use: /limparlocutor.");

	new log_str[128];

	if (level == 0) {
		SendMsgF(playerid, COLOR_LIGHTBLUE, "Você retirou o nível de locutor de %s.", PlayerName[idplayer]);
		SendMsgF(idplayer, COLOR_LIGHTRED, "Você foi retirado por %s de %s da Equipe da Rádio.", PlayerName[playerid], Speaker_GetPositionName(Speaker_GetNivel(idplayer)));

		format(log_str, sizeof(log_str), "[EQUIPE RÁDIO]: %s retirou %s do cargo de %s.", PlayerName[playerid], PlayerName[idplayer], Speaker_GetPositionName(Speaker_GetNivel(idplayer)));
	
		Speaker_SetNivel(idplayer, SpeakerNivel:level);
		Speaker_SetTender(playerid, false);
		Group_Dismiss(Player_GetAccountID(idplayer), GROUP_SPEAKER);
	} else {
		if (Speaker_GetNivel(idplayer))
			Group_UpdateVacancy(idplayer, GROUP_SPEAKER, level);
		else
			Speaker_SetNivel(idplayer, SpeakerNivel:level);

		SendMsgF(playerid, COLOR_LIGHTBLUE, "Você promoveu %s para %s da Equipe da Rádio.", PlayerName[idplayer], Speaker_GetPositionName(Speaker_GetNivel(idplayer)));
		SendMsgF(idplayer, COLOR_LIGHTBLUE, "Você foi promovido por %s para %s da Equipe da Rádio.", PlayerName[playerid], Speaker_GetPositionName(Speaker_GetNivel(idplayer)));
	
		format(log_str, sizeof(log_str), "[EQUIPE RÁDIO]: %s promoveu %s para o cargo de %s.", PlayerName[playerid], PlayerName[idplayer], Speaker_GetPositionName(Speaker_GetNivel(idplayer)));
	}
	server_log("equipe_radio", log_str);

	return 1;
}

CMD:ajudalocutor(playerid)
{
	MEGAString[0] = EOS;

	strcat(MEGAString, "\n\n{F5DEB3}________________________| AJUDA LOCUTOR |________________________\n");

	strcat(MEGAString, "\n{8B8A8A}Comandos disponíveis:\n");

	strcat(MEGAString, "\n{FFFFFF}> /cr 				{8B8A8A}(Chat dos locutores para se comunicar)\n");
	strcat(MEGAString, "{FFFFFF}> /avr 		{8B8A8A}(Para fazer um anúncio para todos jogadores online)\n");
	strcat(MEGAString, "{FFFFFF}> /infolocutores 			{8B8A8A}(Para ver quem são os locutores do servidor)\n");
	strcat(MEGAString, "{FFFFFF}> /radio 			{8B8A8A}(Para controlar os comandos da rádio)\n");
	strcat(MEGAString, "{FFFFFF}> /pedidos 			{8B8A8A}(Para verificar o pedido dos jogadores)\n");
	strcat(MEGAString, "{FFFFFF}> /locutores 				{8B8A8A}(Para verificar os locutores online)");

	if (Speaker_GetNivel(playerid) > GERENTE_RADIO) {

		strcat(MEGAString, "\n{8B8A8A}Comandos para o gerenciamento:\n");

		strcat(MEGAString, "\n{FFFFFF}> /criarlocutor 		{8B8A8A}(Para promover algum locutor no cargo)\n");
		strcat(MEGAString, "{FFFFFF}> /limparlocutor 		{8B8A8A}(Para retirar algum locutor do cargo)");
	}

	strcat(MEGAString, "\n\n{F5DEB3}_________________________________________________________________\n\n");

	return 1;
}