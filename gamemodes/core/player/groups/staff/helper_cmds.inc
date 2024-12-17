CMD:infohelpers(playerid)
{
	if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	return Helper_List(playerid);
}

CMD:limparhelper(playerid) 
{
	if (Admin_GetNivel(playerid) < GERENTE)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	return Helper_List(playerid, 1);
}

CMD:criarhelper(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MASTER && !IsServerCreator(playerid))
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    new idplayer, level;
	if (sscanf(params, "ud", idplayer, level)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /criarhelper (id do jogador) (nível 1 ao 7)");

    if (!Player_Logado(idplayer))
        return SendClientMessage(playerid, -1, "Esse jogador não está logado/conectado no servidor.");

	if (Helper_GetNivel(idplayer) < 1 && !Group_GetVacancy(idplayer, level, GROUP_HELPER) && level != 0)
		return SendClientMessage(playerid, -1, "Não há mais vagas na equipe helper, use: /limparhelper.");

	new log_str[128];

	if (level == 0) {
		SendMsgF(playerid, COLOR_LIGHTBLUE, "Você retirou o nível de helper de %s.", PlayerName[idplayer]);
		SendMsgF(idplayer, COLOR_LIGHTRED, "Você foi retirado por %s da Equipe Helper.", PlayerName[playerid]);

		format(log_str, sizeof(log_str), "[EQUIPE HELPER]: %s retirou %s do cargo de Helper.", PlayerName[playerid], PlayerName[idplayer]);
	
		Helper_SetNivel(idplayer, 0);
		Staff_SetWorking(idplayer, false);
		SetPlayerToTeamColor(idplayer);
		SetPlayerHealth(idplayer, 100);
		Group_Dismiss(Player_GetAccountID(idplayer), GROUP_HELPER);
	} else {
		if (Helper_GetNivel(idplayer))
			Group_UpdateVacancy(idplayer, GROUP_HELPER, level);
		else
			Helper_SetNivel(idplayer, level);

		SendMsgF(playerid, COLOR_LIGHTBLUE, "Você promoveu %s para nivel %d de Helper.", PlayerName[idplayer], Helper_GetNivel(idplayer));
		SendMsgF(idplayer, COLOR_LIGHTBLUE, "Você foi promovido por %s para nivel %d de Helper.", PlayerName[playerid], Helper_GetNivel(idplayer));
	
		format(log_str, sizeof(log_str), "[EQUIPE HELPER]: %s promoveu %s para o nivel %d de Helper.", PlayerName[playerid], PlayerName[idplayer], Helper_GetNivel(idplayer));
	}
	server_log("helpers", log_str);

	return 1;
}
alias:criarhelper("darhelper", "sethelper")

CMD:helpers(playerid)
{
	new string[128],
        count = 0;

	MEGAString[0] = EOS;
	strcat(MEGAString, "id        nome\tnivel\tstatus\n");

	foreach(new helpers : Character) {
	    if (Helper_GetNivel(helpers)) {
			format(string, sizeof(string), "%02d  %s\t"C_HELPERD"%d\t%s\n", helpers, PlayerName[helpers], Helper_GetNivel(helpers), Staff_GetStatus(helpers));
            strcat(MEGAString, string);

			List_SetPlayers(playerid, count, helpers);
            count++;
		}
	}
	format(string, sizeof(string), ""C_WHITE"Helpers online ("C_GREEN"%d"C_WHITE")", count);

	if (!count) {
		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Fechar", "");
	} else {
		inline D_HelpersOn(pid, dialogid, response, listitem, string:inputtext[]) {
			#pragma unused pid, dialogid, inputtext

			if (!response)
				return 1;

			new playersend = List_GetPlayers(playerid, listitem);

			if (!Player_Logado(playersend))
				return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

			Dialog_SendMessagePrivate(playerid, playersend);
		}
		Dialog_ShowCallback(playerid, using inline D_HelpersOn,
			DIALOG_STYLE_TABLIST_HEADERS,
			string, MEGAString, "Particular", "Fechar"
		);
	}
	return 1;
}

CMD:meavalie(playerid, params[])
{
	if (!Helper_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não é um Helper.");

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /meavalie (id do jogador)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (idplayer == playerid) return 1;

	if (AssessHelper_GetTimer(idplayer) > gettime())
		return SendClientMessage(playerid, -1, "Esse jogador avaliou um Helper a menos de 2 minutos.");
	
	AssessHelper_Set(idplayer, playerid);
	AssessHelper_SetTimer(idplayer, gettime() + 120);
	SendMsgF(playerid, COLOR_LIGHTBLUE, "Você enviou pedido de avaliacao do seu atendimento ao %s(%d).", PlayerName[idplayer], idplayer);

	MEGAString[0] = EOS;
	format(MEGAString, sizeof(MEGAString), 
		""C_HELPER"Helper %s "C_WHITE"pediu avaliacao de seu atendimento.\n\n\
		Escolha uma das opcoes: \n\
		\tAperte "C_GREEN"SIM "C_WHITE"para uma avaliacao positiva.\n\
		\tAperte "C_RED"NAO "C_WHITE"para uma avaliacao negativa:", PlayerName[playerid]);

	inline D_AssessHelper(did, ddialogid, dresponse, dlistitem, string:dtext[])
	{
		#pragma unused did, ddialogid, dtext, dlistitem

		new helperid = AssessHelper_Get(idplayer),
			helper_nivel = Helper_GetNivel(playerid);

		if (helperid == INVALID_PLAYER_ID)
			return SendClientMessage(playerid, -1, "O helper deslogou do servidor.");

		if (dresponse) {
			helper_nivel++;
			CheckConquista(playerid, Conquista_Ajudante);
			SendMsgF(idplayer, -1, "Você deu avaliação "C_GREEN"POSITIVA "C_WHITE"ao Helper %s.", PlayerName[playerid]);
			SendMsgF(playerid, -1, "Você recebeu uma avaliação "C_GREEN"POSITIVA "C_WHITE"do jogador %s.", PlayerName[idplayer]);
		} else {
			helper_nivel--;
			SendMsgF(idplayer, -1, "Você deu avaliação "C_RED"NEGATIVA "C_WHITE"ao Helper %s.", PlayerName[playerid]);
			SendMsgF(playerid, -1, "Você recebeu uma avaliação "C_RED"NEGATIVA "C_WHITE"do jogador %s.", PlayerName[idplayer]);
		}
		if (helper_nivel > 0)
			Helper_SetNivel(playerid, helper_nivel);

		AssessHelper_Set(playerid, INVALID_PLAYER_ID);
	}
	Dialog_ShowCallback(idplayer, using inline D_AssessHelper, DIALOG_STYLE_MSGBOX, ""C_HELPER"Avaliacao Helper", MEGAString, "SIM", "NAO");

	new string[128];
	format(string, sizeof(string), "Helper, %s: pediu para %s lhe avaliar.", PlayerName[playerid], PlayerName[idplayer]);
	Staff_ChatToAll(COLOR_LIGHTRED, string, MASTER);
	ServerLog::("helpers", string);

	return 1;
}