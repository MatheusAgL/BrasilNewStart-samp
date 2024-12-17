CMD:youtubers(playerid)
{
	new string[128],
		status[21],
        count = 0;

	MEGAString[0] = EOS;
	strcat(MEGAString, "id        nome\tcargo\tstatus\n");

	foreach(new youtubers : Character) {
	    if (Youtuber_GetNivel(youtubers)) {
            if (Youtuber_GetRec(youtubers)) {
                status = ""C_YOUTUBER"GRAVANDO";
            } else if (GetPlayerEscTime(youtubers) > 5) {
                status = ""C_RED"INDISPONÍVEL";
            } else {
                status = ""C_GREEN"DISPONÍVEL";
            }

			format(string, sizeof(string), "%02d  %s\t"C_YOUTUBERD"%s\t%s\n", youtubers, PlayerName[youtubers], Youtuber_GetPositionName(Youtuber_GetNivel(youtubers)), status);
            strcat(MEGAString, string);

            count++;
		}
	}
	format(string, sizeof(string), ""C_WHITE"Youtubers Online: ("C_GREEN"%d"C_WHITE")", count);
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Fechar", "");
	return 1;
}

CMD:cy(playerid, result[])
{
	if (Youtuber_GetNivel(playerid) < YOUTUBER_INICIANTE) 
        return SendClientMessage(playerid, -1, "Você não tem permissão para usar este comando.");

	if (isnull(result)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /cy (texto para o chat youtubers)");

	new string[128];
    format(string, sizeof(string), "** [%s] %s: %s **", Youtuber_GetPositionName(Youtuber_GetNivel(playerid)), PlayerName[playerid], result);
    Youtuber_ChatToAll(COLOR_YOUTUBER, string);
	server_log("chat_youtubers", string);

	return 1;
}

CMD:avy(playerid, result[])
{
	if (Youtuber_GetNivel(playerid) < YOUTUBER_INICIANTE)
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (isnull(result)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /avy (texto)");

	new string[144];
	format(string, sizeof(string), "o< (( %s, %s: "C_WHITE"%s "C_YOUTUBER"))", Youtuber_GetPositionName(Youtuber_GetNivel(playerid)), PlayerName[playerid], result);
	SendClientMessageToAll(COLOR_YOUTUBER, string);

	return 1;
}

CMD:gravando(playerid, params[])
{
	if (Youtuber_GetNivel(playerid) < YOUTUBER_INICIANTE) 
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!Youtuber_GetRec(playerid)) {
		Youtuber_SetRec(playerid, true);

		new string[80];
		format(string, sizeof(string), "~r~Youtuber ~n~~w~%s~n~~g~~h~gravando...", PlayerName[playerid]);

		foreach(new i : Player) {
			GameTextForPlayer(i, string, 5000, 1);
		}
	} else {
		SendClientMessage(playerid, -1, "Você parou de gravar.");
		Youtuber_SetRec(playerid, false);
	}
	return 1;
}

CMD:infoyoutubers(playerid)
	return Youtuber_List(playerid);

CMD:limparyoutuber(playerid) {

	if (Youtuber_GetNivel(playerid) < RESPONSAVEL_YOUTUBER && Admin_GetNivel(playerid) < SUB_DONO)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	return Youtuber_List(playerid, 1);
}

CMD:criaryoutuber(playerid, params[])
{
	if (Youtuber_GetNivel(playerid) < RESPONSAVEL_YOUTUBER && 
        Admin_GetNivel(playerid) < SUB_DONO)
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    new idplayer, level;
	if (sscanf(params, "ud", idplayer, level)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /criaryoutuber (id do jogador) (nível 1 ao 8)");

    if (!Player_Logado(idplayer))
        return SendClientMessage(playerid, -1, "Esse jogador não está logado/conectado no servidor.");

	if (YoutuberNivel:level >= Youtuber_GetNivel(playerid) &&
        Admin_GetNivel(playerid) < DONO) 
        return SendClientMessage(playerid, -1, "Você só pode criar youtubers abaixo do seu cargo.");

	if (Youtuber_GetNivel(idplayer) < YOUTUBER_INICIANTE && !Group_GetVacancy(idplayer, level, GROUP_YOUTUBER) && level != 0)
		return SendClientMessage(playerid, -1, "Não há mais vagas de youtubers, use: /limparyoutuber.");

	new log_str[128];

	if (level == 0) {
        SendMsgF(playerid, COLOR_LIGHTBLUE, "Você retirou %s do cargo de %s.", PlayerName[idplayer], Youtuber_GetPositionName(Youtuber_GetNivel(idplayer)));
		SendMsgF(idplayer, COLOR_LIGHTRED, "Você foi retirado por %s de %s.", PlayerName[playerid], Youtuber_GetPositionName(Youtuber_GetNivel(idplayer)));

		format(log_str, sizeof(log_str), "[YOUTUBERS]: %s retirou %s do cargo de %s.", PlayerName[playerid], PlayerName[idplayer], Youtuber_GetPositionName(Youtuber_GetNivel(idplayer)));
	
		Youtuber_SetRec(idplayer, false);
		Youtuber_SetNivel(idplayer, YoutuberNivel:level);
		Group_Dismiss(Player_GetAccountID(idplayer), GROUP_YOUTUBER);
	} else {
		if (Youtuber_GetNivel(idplayer))
			Group_UpdateVacancy(idplayer, GROUP_YOUTUBER, level);
		else
			Youtuber_SetNivel(idplayer, YoutuberNivel:level);

		SendMsgF(playerid, COLOR_LIGHTBLUE, "Você promoveu %s para %s.", PlayerName[idplayer], Youtuber_GetPositionName(Youtuber_GetNivel(idplayer)));
		SendMsgF(idplayer, COLOR_LIGHTBLUE, "Você foi promovido por %s para %s.", PlayerName[playerid], Youtuber_GetPositionName(Youtuber_GetNivel(idplayer)));
	
		format(log_str, sizeof(log_str), "[YOUTUBERS]: %s promoveu %s para o cargo de %s.", PlayerName[playerid], PlayerName[idplayer], Youtuber_GetPositionName(Youtuber_GetNivel(idplayer)));
	}
	server_log("youtubers", log_str);

	return 1;
}

CMD:ajudayoutuber(playerid) {

    MEGAString[0] = EOS;

    strcat(MEGAString, "\n\n        "C_LIGHTBLUE"(?) "C_YOUTUBER"AJUDA YOUTUBER\n");

    strcat(MEGAString, "\n"C_WHITE"Comandos:\n");

    strcat(MEGAString, "\n"C_WHITE"      /cy 				"C_GRAY"| chat dos youtubers\n");
    strcat(MEGAString, ""C_WHITE"       /avy 		"C_GRAY"| Anuncio para todos (exclusivo para Youtubers)\n");
    strcat(MEGAString, ""C_WHITE"       /infoyoutubers 			"C_GRAY"| Informações dos Youtubers\n");
    strcat(MEGAString, ""C_WHITE"       /gravando 			"C_GRAY"| Para informar que está gravando agora\n");
    strcat(MEGAString, ""C_WHITE"       /youtubers 				"C_GRAY"| Verificar os Youtubers Online");

    if (Speaker_GetNivel(playerid) > GERENTE_RADIO) {

        strcat(MEGAString, "\n"C_WHITE"Comandos de gerenciamento:\n");

        strcat(MEGAString, "\n"C_WHITE"     /criaryoutuber 		"C_GRAY"| Para promover ou adicionar alguém como Youtuber\n");
        strcat(MEGAString, ""C_WHITE"       /limparyoutuber 		"C_GRAY"| Para retirar algum locutor do cargo)");
    }

    strcat(MEGAString, "\n\n"C_YOUTUBER"_____________________________________________________________________________________\n\n");

	return 1;
}