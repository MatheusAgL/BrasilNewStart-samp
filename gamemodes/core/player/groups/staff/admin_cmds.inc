// flags:infoadmins(ESTAGIARIO)
CMD:infoadmins(playerid)
{
	if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	return Admin_List(playerid);
}

// flags:limparadmin(MASTER)
CMD:limparadmin(playerid) 
{
	if (Admin_GetNivel(playerid) < MASTER)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	return Admin_List(playerid, 1);
}

CMD:criaradmin(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MASTER && !IsServerCreator(playerid))
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    new idplayer, level, function[20];
	if (sscanf(params, "uds[20]", idplayer, level, function)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /criaradmin (id do jogador) (nível 1 ao 7)");

    if (!Player_Logado(idplayer))
        return SendClientMessage(playerid, -1, "Esse jogador não está logado/conectado no servidor.");

	if (AdminNivel:level >= Admin_GetNivel(playerid) && !IsServerCreator(playerid)) 
        return SendClientMessage(playerid, -1, "Você só pode criar admins abaixo do seu cargo.");

	if (Admin_GetNivel(idplayer) < ESTAGIARIO && !Group_GetVacancy(idplayer, level, GROUP_ADMIN, function) && level != 0)
		return SendClientMessage(playerid, -1, "Não há mais vagas na equipe admin, use: /limparadmin.");

	new log_str[128];

	if (level == 0) {
		SendMsgF(playerid, COLOR_LIGHTBLUE, "Você retirou o nível de admin de %s.", PlayerName[idplayer]);
		SendMsgF(idplayer, COLOR_LIGHTRED, "Você foi retirado por %s de %s da Equipe Admin.", PlayerName[playerid], Staff_GetPositionName(idplayer));

		format(log_str, sizeof(log_str), "[EQUIPE ADMIN]: %s retirou %s do cargo de %s.", PlayerName[playerid], PlayerName[idplayer], Staff_GetPositionName(idplayer));
	
		Admin_SetNivel(idplayer, NOT_ADMIN);
		Staff_SetWorking(idplayer, false);
		SetPlayerToTeamColor(idplayer);
		SetPlayerHealth(idplayer, 100);
		Group_Dismiss(Player_GetAccountID(idplayer), GROUP_ADMIN);
		Discord_SetStaff(idplayer, 0);
	} else {
		if (Admin_GetNivel(idplayer)) {
			Group_UpdateVacancy(idplayer, GROUP_ADMIN, level, function);
		} else {
			Admin_SetNivel(idplayer, AdminNivel:level);
			Discord_SetStaff(idplayer, level);
		}
		SendMsgF(playerid, COLOR_LIGHTBLUE, "Você promoveu %s para %s da Equipe Admin.", PlayerName[idplayer], Staff_GetPositionName(idplayer));
		SendMsgF(idplayer, COLOR_LIGHTBLUE, "Você foi promovido por %s para %s da Equipe Admin.", PlayerName[playerid], Staff_GetPositionName(idplayer));
	
		format(log_str, sizeof(log_str), "[EQUIPE ADMIN]: %s promoveu %s para o cargo de %s.", PlayerName[playerid], PlayerName[idplayer], Staff_GetPositionName(idplayer));
	}
	server_log("admins", log_str);

	return 1;
}
alias:criaradmin("daradmin", "setadmin", "discord", "painel", "forum")

// Comandos para ver a equipe online
CMD:admins(playerid)
{
	new string[128],
        count = 0;

	MEGAString[0] = EOS;
	strcat(MEGAString, "id        nome\tcargo	funcao\tstatus\n");

	foreach(new admins : Character) {
	    if (Admin_GetNivel(admins) && !Staff_GetSecret(admins)) { //  && GetPlayerEscTime(admins) < 10 * 60
			format(string, sizeof(string), "%02d  %s\t"C_ADMIND"%s	"C_GRAY"%s\t%s\n", admins, PlayerName[admins], Staff_GetPositionName(admins), Staff_GetFunction(admins), Staff_GetStatus(admins));
            strcat(MEGAString, string);

			List_SetPlayers(playerid, count, admins);
            count++;
		}
	}
	format(string, sizeof(string), ""C_WHITE"Administração online ("C_GREEN"%d"C_WHITE")", count);

	if (!count) {
		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Fechar", "");
	} else {
		inline D_AdminsOn(pid, dialogid, response, listitem, string:inputtext[]) {
			#pragma unused pid, dialogid, inputtext

			if (!response)
				return 1;

			new playersend = List_GetPlayers(playerid, listitem);

			if (!Player_Logado(playersend))
				return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

			Dialog_SendMessagePrivate(playerid, playersend);
		}
		Dialog_ShowCallback(playerid, using inline D_AdminsOn,
			DIALOG_STYLE_TABLIST_HEADERS,
			string, MEGAString, "Particular", "Fechar"
		);
	}
	return 1;
}

CMD:par(playerid, params[])
{
	new idplayer, result[128];
	if (sscanf(params, "us[128]", idplayer, result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /par (id do player) (texto)");

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	new string[128];

	new bool:destIsAdmin = (Admin_GetNivel(idplayer) || Helper_GetNivel(idplayer)),
		bool:origIsAdmin = (Admin_GetNivel(playerid) || Helper_GetNivel(playerid));

	if (!origIsAdmin && gettime() < GetPVarInt(playerid, #varFlood_par)) 
		return SendClientMessage(playerid, COLOR_GRAD, "Você está usando esse comando com muita frequência.");

	if (!origIsAdmin && !destIsAdmin)
		return SendClientMessage(playerid, -1, "Você pode enviar particular apenas para administradores.");

	if (destIsAdmin) {
		if (Staff_GetConfig(idplayer, "particulares")) 
			return SendClientMessage(playerid, COLOR_GRAD, "Esse administrador está com o particular bloqueado.");
		else if(Founders_GetList(idplayer))
			goto skip_founder_particular;
		else if (!Staff_GetWorking(idplayer))
			return SendClientMessage(playerid,  COLOR_GRAD, "Esse administrador não está em serviço. (/admins)");
		else if (Staff_GetAFK(idplayer)) 
			return SendMsgF(playerid, COLOR_GRAD, "Esse administrador está ausente, motivo: %s.", Staff_GetReasonAFK(idplayer));
		else if (IsPlayerESC(idplayer)) 
			return SendMsgF(playerid, COLOR_GRAD, "Esse administrador está de ESC há %s.", ConvertTime(GetPlayerEscTime(idplayer)));
		else if (Player_GetTimerAFK(playerid) > 0) 
			return SendMsgF(playerid, COLOR_GRAD, "Esse administrador está inativo há %s.", ConvertTime(gettime() - Player_GetTimerAFK(idplayer)));
	}

	skip_founder_particular:
	if (origIsAdmin) {
		foreach(new admins : Player) {
			if (Admin_GetNivel(admins) > MASTER && SpyGet_Particulares(admins)) {
				format(string, sizeof string, "%s: particular para %s: %s", PlayerName[playerid], PlayerName[idplayer], result);
				SendClientMessage(admins, COLOR_YELLOW, string);
			}
		}

		format(string, sizeof(string), "Particular enviado para %s: (%s)", PlayerName[idplayer], result);
		SendClientMessage(playerid,  COLOR_LIGHTBLUE, string);

		format(string, sizeof(string), "Particular: %s para %s: %s.", PlayerName[playerid], PlayerName[idplayer], (result));
		server_log("particular", string);

		format(string, sizeof(string), "%s: %s(%d) particular: %s", Staff_GetPositionName(playerid), PlayerName[playerid], playerid, (result));
	}
	else {
		format(string, sizeof(string), "Particular enviado para %s: (%s)", PlayerName[idplayer], result);
		SendClientMessage(playerid,  COLOR_LIGHTBLUE, string);

		format(string, sizeof(string), "Player: %s(%d) particular: %s", PlayerName[playerid], playerid, (result));
	}

	SendClientMessage(idplayer, COLOR_YELLOW, string);
	return SetPVarInt(playerid, #varFlood_par, gettime() + 5);
}

// ----------------------------------------------------------------------------------------------
// Comandos apenas administrativos:

CMD:aa(playerid)
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Admin_GetNivel(playerid) > DIRETOR)
		goto skip_founder_comandosadm;

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você precisa estar em modo trabalho para ver os comandos admin.");

	skip_founder_comandosadm:

	MEGAString[0] = EOS;

	strcat(MEGAString,""C_YELLOW"TELEPORTES: "C_WHITE"/ls /sf /lv /fim /praia /clubao /irhospital /irestadio3\n");
	strcat(MEGAString,"/esconderijo /esconderijo2 /aviao /irstad2\n\n");

	if (Admin_GetNivel(playerid) >= ESTAGIARIO) {
		/* ---------------------------------------------------------------------------
			ESTAGIÁRIO: */

		strcat(MEGAString, ""C_ADMIND"» ESTAGIÁRIO:\n\n");

		strcat(MEGAString,""C_WHITE"/jogar /afk /a /av /mup /up /dn /lt /rt /ir /trazer /voar /infoconta\n");
		strcat(MEGAString,"/par /infoconta /infoban /infobanip /removeratendimento /removerreport\n");
		strcat(MEGAString,"/setar /nickindevido /limparchat /m /kick /vercarteira /empregos\n");
		strcat(MEGAString,"/versenhaadmin /orelhagrande /desbugar /tapa /infoarmas /infoplayer\n");
		strcat(MEGAString,"/marcarmapa /setworld /setint\n");

		strcat(MEGAString, ""C_ADMIND"----------------------------------------------------------------------------------------\n");
	} else {
		strcat(MEGAString, ""C_HELPERD"» HELPER:\n\n");

		strcat(MEGAString,""C_WHITE"/jogar /afk /meavalie /a /av /par /ir /tv /blocknoob /desblocknoob /desbugar\n");
		strcat(MEGAString,"/mup /up /dn /lt /rt\n");

		strcat(MEGAString, ""C_HELPERD"----------------------------------------------------------------------------------------\n");
	}

	if (Admin_GetNivel(playerid) >= MODERADOR) {

		/* ---------------------------------------------------------------------------
			Moderador:
		-

		*/

		strcat(MEGAString,"\n"C_ADMIND"» MODERADOR\n");
		strcat(MEGAString,""C_WHITE"/ban /agendarban /banimentos /ultimosbanimentos /cadeia /agendarcadeia /retirarcadeia\n");
		strcat(MEGAString,"/respawncarros /respawnp /setarp /removercones /removerbarreiras /removerbloqueios /respawnid\n");
		strcat(MEGAString,"/lbc /cdes{FFFFFF}\n\n");

		strcat(MEGAString, ""C_ADMIND"----------------------------------------------------------------------------------------\n");
	}

	if (Admin_GetNivel(playerid) >= ADMINISTRADOR) {

		/* ---------------------------------------------------------------------------
			Administrador:
		-

		*/

		strcat(MEGAString,"\n"C_ADMIND"» ADMINISTRADOR\n");
		strcat(MEGAString,""C_WHITE"/settempocadeia /banimentos /ultimosbanidos /ircarro /irestadio /contagem /contagempro\n");
		strcat(MEGAString,"/iniciarloteria /onibus /entrarcarro /matar /terminarguerra\n");
		strcat(MEGAString,"/aviao /trazerx1 /destruirveiculos /terminarsequestro /versms /verlogs /puxartv{FFFFFF}\n\n");

		strcat(MEGAString, ""C_ADMIND"----------------------------------------------------------------------------------------\n");
	}
	if (Admin_GetNivel(playerid) >= ENCARREGADO) {

		/* ---------------------------------------------------------------------------
			ENCARREGADO:
		-

		*/

		strcat(MEGAString,"\n{B459FF}» ENCARREGADO\n");
		strcat(MEGAString,""C_WHITE"/iniciarhay /destruirhay /votacao /encerrarvotacao\n");
	   	strcat(MEGAString,"/trazerveiculo /carroantigo /dararma /limparcasamento /skydive /darvida /darcolete\n");
	   	strcat(MEGAString,"/criarsurvival /iniciarsurvival /destruirsurvival /criarfall /iniciarfall /destruirfall\n");
	   	strcat(MEGAString,"/trazertodos /congelar /darfome /darsede\n");
	   	strcat(MEGAString,"/ip /irtunning /veh /settempocadeia{FFFFFF}\n\n");

		strcat(MEGAString, ""C_GRAY"----------------------------------------------------------------------------------------\n");
	}
	if (Admin_GetNivel(playerid) >= SUPERVISOR) {

		/* ---------------------------------------------------------------------------
			Supervisor:
		-

		*/

		strcat(MEGAString,"{fb9b04}» SUPERVISOR\n");
	    strcat(MEGAString,""C_WHITE"/irprop /pegaratividade /lider /darlider /limparlider /avorg\n");
	    strcat(MEGAString,"/criarhelper /abastecervip /repararvip{FFFFFF}\n\n");

		strcat(MEGAString, ""C_GRAY"----------------------------------------------------------------------------------------\n");
	}
	if (Admin_GetNivel(playerid) >= MASTER)
	{
		/* ---------------------------------------------------------------------------
			Gerente:
		-
		*/

		strcat(MEGAString,"{6B86A4}» MASTER\n");
	    strcat(MEGAString,""C_WHITE"/am /editar /versms /guerramorro /tirarsu /irpos /clubeam /orelhagrande /desbanip /aviso\n");
		strcat(MEGAString,"/rtitulo /aemail /sethora /setemprego /criaradmin /limparadmin /limparhelper\n\n");

		strcat(MEGAString, ""C_GRAY"----------------------------------------------------------------------------------------\n");
	}
	if (Admin_GetNivel(playerid) >= GERENTE)
	{
		/* ---------------------------------------------------------------------------
			Gerente:
		-
		*/

		strcat(MEGAString,"{32CD32}» GERENTE\n");
	    strcat(MEGAString,""C_WHITE"/setorgvip /retirarorgvip /consertarcaixas /retiraravisos{FFFFFF}\n");

		strcat(MEGAString, ""C_GRAY"----------------------------------------------------------------------------------------\n");
	}
	if (Admin_GetNivel(playerid) >= DIRETOR)
	{
		/* ---------------------------------------------------------------------------
			Diretor:
		-
		*/

		strcat(MEGAString,"{9C8371}» DIRETOR "C_WHITE"/ {00BFFF}SUB-DONO\n");
	    strcat(MEGAString,""C_WHITE"/admsecreto /gmx /testetempo /menu /verinventario /setmateriais /retirarorgvip /bau ir{FFFFFF}\n\n");

		strcat(MEGAString, ""C_GRAY"----------------------------------------------------------------------------------------\n");
	}
	if (Admin_GetNivel(playerid) >= DONO)
	{
		/* ---------------------------------------------------------------------------
			Dono:
		-

		*/

		strcat(MEGAString,"\n{26F722}» DONO\n");
		strcat(MEGAString,""C_WHITE"/verparticulares /pdm /mudarsenhaadmin /admvfazenda /hardbanip /harddesbanip /sbantemp\n\n");

		strcat(MEGAString, ""C_GRAY"----------------------------------------------------------------------------------------\n");
	}

    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, ""C_GRAY"Comandos administrativos", MEGAString, ""C_YELLOW"Fechar","");

	return 1;
}

CMD:jogar(playerid, const params[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Admin_GetNivel(playerid) < MASTER && gettime() < GetPVarInt(playerid, #varFlood_admin))
		return SendClientMessage(playerid, COLOR_GRAD, "Você está usando comandos com muita frequência.");

	if (Staff_GetWorking(playerid)) 
	{
		Staff_SetWorking(playerid, false);
		SetPlayerHealth(playerid, 100);
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "Você entrou em modo jogo.");
	} else {
		Staff_SetWorking(playerid, true);
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "Você entrou em modo trabalho.");
	}
	SetPlayerToTeamColor(playerid);

	new string[128];

	if (!Staff_GetSecret(playerid)) {
		format(string, 128, "AdmAviso: %s %s", 
		PlayerName[playerid], Staff_GetWorking(playerid) ? "entrou em modo serviço, solicite um /atendimento." : "saiu do modo serviço, agora está livre para jogar.");
		SendClientMessageToAll(COLOR_LIGHTGREEN, string);
	}
	ServerLog::("admin", string);
	SetPVarInt(playerid, #varFlood_admin, gettime() + 30);
	return 1;
}

CMD:afk(playerid, params[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	new motivo[21];
	sscanf(params, "s[21]", motivo);

	if (!Staff_GetAFK(playerid)) {
		if (strlen(motivo) < 3 ||  strlen(motivo) > 20)
			return SendClientMessage(playerid, -1, "O motivo deve estar entre 3 a 20 caracteres, abrevie.");
		
		Staff_SetAFK(playerid, true);
		Staff_SetReasonAFK(playerid, motivo);

		SendMsgAllF(COLOR_LIGHTGREEN, "AdmAviso: O %s %s está ausente, motivo: %s.", Admin_GetNivel(playerid) ? "admin" : "helper", PlayerName[playerid], motivo);
		
	} else {
		Staff_SetAFK(playerid, false);

		SendMsgAllF(COLOR_LIGHTGREEN, "AdmAviso: O %s %s não está mais ausente.", Admin_GetNivel(playerid) ? "admin" : "helper", PlayerName[playerid]);
	}
	return 1;
}

CMD:a(playerid, result[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Admin_GetNivel(playerid) >= DONO) {
		goto skip_dono_chatadmin;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você precisa estar em modo trabalho para falar no chat admin.");

	skip_dono_chatadmin:

	if (isnull(result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /a (texto para o chat admin)");

	new string[128];
	format(string, sizeof(string), "** Chat Staff: %s, %s: %s **", Staff_GetPositionName(playerid), PlayerName[playerid], result);
	Staff_ChatToAll(COLOR_CHAT_STAFF, string); 

	server_log("chat_admin", string);

	return 1;
}

CMD:am(playerid, result[])
{
	if (Admin_GetNivel(playerid) < MASTER) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (isnull(result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /am (texto para o chat gerentes+)");

	new string[128];
	format(string, sizeof(string), "** Chat Gestores: %s, %s: %s **", Staff_GetPositionName(playerid), PlayerName[playerid], result);
	Staff_ChatToAll(COLOR_CHAT_GESTAO, string, MASTER); 

	server_log("chat_gestor", string);

	return 1;
}

CMD:ad(playerid, result[])
{
	if (Admin_GetNivel(playerid) < BETA_TESTER) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (isnull(result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /ad (texto para o chat Equipe Dev)");

	new string[128];
	format(string, sizeof(string), "** Chat Equipe Dev: %s, %s: %s **", Staff_GetPositionName(playerid), PlayerName[playerid], result);
	Staff_ChatToAll(COLOR_DES, string, BETA_TESTER); 

	return 1;
}

CMD:av(playerid, result[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando");

	if (Admin_GetNivel(playerid) > DIRETOR)
		goto skip_founder_av;

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_av:
	if (isnull(result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /av (texto)");

	if (strlen(result) < 16 || strlen(result) > 110) 
		return SendClientMessage(playerid, -1, "O aviso administrativo deve conter entre 16 a 110 caracteres.");

	if (Admin_GetNivel(playerid) < ESTAGIARIO) {
		SendClientMessageToAll(COLOR_HELPER, "| ___________________________________________________________________________");
		SendMsgAllF(COLOR_HELPER, "| "C_WHITE"Aviso helper de: %s", PlayerName[playerid]);
		SendMsgAllF(COLOR_HELPER, "| %s", result);
	} else {
		SendClientMessageToAll(COLOR_ADMIN, "| ___________________________________________________________________________");
		SendMsgAllF(COLOR_ADMIN, "| "C_WHITE"Aviso administrativo de: %s, %s", Staff_GetPositionName(playerid), PlayerName[playerid]);
		SendMsgAllF(COLOR_ADMIN, "| %s", result);
	}

	#if defined _inc_discord_connector
		new string[128];

		if (Admin_GetNivel(playerid) > MASTER) {
			format(string, sizeof(string), ":globe_with_meridians: **Administração:** %s, %s: %s.", Staff_GetPositionName(playerid), PlayerName[playerid], result);
			Discord_SendMessage(string, Channel_BatePapo);
		}
	#endif

	return 1;
}

CMD:avdev(playerid, result[])
{
	if (Admin_GetNivel(playerid) < BETA_TESTER)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	if (isnull(result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /avdev (texto)");

	if (strlen(result) < 16 || strlen(result) > 110) 
		return SendClientMessage(playerid, -1, "O aviso administrativo da Equipe Dev deve conter entre 16 a 110 caracteres.");

	if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
		SendClientMessageToAll(COLOR_DES, "| ___________________________________________________________________________");
		SendMsgAllF(COLOR_DES, "| "C_WHITE"AVISO DA EQUIPE DE DESENVOLVIMENTO: %s, %s", Staff_GetPositionName(playerid), PlayerName[playerid]);
		SendMsgAllF(COLOR_DES, "| %s", result);
	} 

	#if defined _inc_discord_connector
		new string[128];

		if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
			format(string, sizeof(string), ":tools: **Equipe Dev:** %s, %s: %s.", Staff_GetPositionName(playerid), PlayerName[playerid], result);
			Discord_SendMessage(string, Channel_BatePapo);
		}
	#endif

	return 1;
}

CMD:avsom(playerid, result[])
{
	if (Dev_GetNivel(playerid) < DEV_ALPHA) 
		return SendClientMessage(playerid, -1, "Este comando administrativo é destinado para a Equipe de Desenvolvimento.");

	if (Admin_GetNivel(playerid) > DIRETOR) {
		goto skip_founder_avsom;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_avsom:
	if (isnull(result)) {
		SendClientMessage(playerid, -1, "Modo de uso: /avsom (link da música/som)");
		return SendClientMessage(playerid, -1, "Lembre-se de colocar com o link da música com .mp3");
	}

	if (strlen(result) < 8 || strlen(result) > 150) 
		return SendClientMessage(playerid, -1, "O link deve ser colocado corretamente, ou excede o limite de caracteres.");

	if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
		SendClientMessageToAll(COLOR_YELLOW, "| ___________________________________________________________________________");
		SendMsgAllF(COLOR_WHITE, "| "C_WHITE"MÚSICA/SOM DADA PELO: %s, %s", Staff_GetPositionName(playerid), PlayerName[playerid]);

		foreach(new x : Player)
	    PlayAudioStreamForPlayer(x, result);
	} 

	return 1;
}

CMD:pararavsom(playerid, result[])
{
	if (Dev_GetNivel(playerid) < DEV_ALPHA) 
		return SendClientMessage(playerid, -1, "Este comando administrativo é destinado para a Equipe de Desenvolvimento.");

	if (Admin_GetNivel(playerid) > DIRETOR)
		goto skip_founder_avsom;

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_avsom:

	if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
		new string[128];

		format(string, sizeof(string), "EQUIPE DEV: {FFFFFF}%s, %s parou a música/som para todos os jogadores.", Staff_GetPositionName(playerid), PlayerName[playerid]);
		SendClientMessageToAll(COLOR_DES, string);

		foreach(new x : Player)
	    	StopAudioStreamForPlayer(x);
	} 

	return 1;
}


// Variáveis do Aviso
new avisomoderno = 1; // Variável global para determinar como a mensagem será enviada (preferência: 1 - Moderno, para alterar a variável inicial ao iniciar o servidor, deve tirar o 1)

CMD:alterarmodoaviso(playerid, result[])
{
	if (Admin_GetNivel(playerid) < DONO)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	if (Admin_GetNivel(playerid) > DIRETOR) {
		goto skip_founder_modoaviso;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");
	
	skip_founder_modoaviso:
	MEGAString[0] = EOS;

	strcat(MEGAString, ""C_WHITE"Qual o modo de aviso que você deseja que o jogador veja?");

	ShowPlayerDialog(playerid, 10052, DIALOG_STYLE_MSGBOX, ""C_GRAY"Alteração do Modo de Aviso", MEGAString, ""C_GRAY"Moderno", ""C_GRAY"Simples");

	return 1;
}

CMD:aviso(playerid, result[])
{
	if (Admin_GetNivel(playerid) < MASTER) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	if (Admin_GetNivel(playerid) > DIRETOR) {
		goto skip_founder_aviso;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_aviso:
	new idplayer;

	if (sscanf(result, "us[36]", idplayer, result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /aviso (id/nick do jogador) (motivo)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "O jogador ainda não logou na conta.");

	if (Admin_GetNivel(playerid) >= FUNDADOR)
		goto skip_coder_avisotest;
	
	if (Admin_GetNivel(idplayer) >= DONO)
		return SendClientMessage(playerid, -1, "Você não pode dar aviso na conta de um Admin Dono+.");

	skip_coder_avisotest:
	new string[128];

	format(string, sizeof(string), "AdmCmd: %s, %s aplicou um aviso na conta do jogador %s", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer]);
	Staff_ChatToAll(COLOR_LIGHTRED, string);

	PlayerInfo[idplayer][pWarns]++;

	MEGAString[0] = EOS;
	new motivoString[128];

	if (avisomoderno == 1) {
		format(MEGAString, sizeof(MEGAString), "Você acabou de receber um aviso na sua conta pelo %s, %s\n\n", Staff_GetPositionName(playerid), PlayerName[playerid]);
		strcat(MEGAString, ""C_WHITE"A notificação presente tem o dever de notificar ao jogador de alguma {FF0000}infração {FFFFFF}cometida contra as regras do servidor.\n");
		strcat(MEGAString, ""C_WHITE"Seja ciente que mesmo sem cometer nenhuma infração ou desrespeito das regras do servidor, sua conduta poderá ser inapropriada mediante do que poderá ter feito.\n");
		strcat(MEGAString, ""C_WHITE"Qualquer tipo de desvio de conduta, má fé e entre outros fatores que poderão prejudicar o servidor, tem suas devidas {FF0000}consequências {FFFFFF}e {FF0000}punições{FFFFFF}.\n\n");

		format(motivoString, sizeof(motivoString), "O aviso dado pelo Administrador(a) foi pelo motivo: {FFE600}%s\n\n", result);

		strcat(MEGAString, motivoString);
		strcat(MEGAString, ""C_WHITE"Se achar que foi algum erro administrativo, poderá recorrer aos superiores ou mesmo denunciar o Administrador pelo nosso painel do servidor.");
	
		ShowPlayerDialog(idplayer, 0, DIALOG_STYLE_MSGBOX, ""C_GRAY"Notificação de Aviso", MEGAString, ""C_GRAY"Entendido", "");
	}
	else {
		format(string, sizeof(string), "Você acabou de receber um aviso na sua conta pelo {FFFFFF}%s, %s", Staff_GetPositionName(playerid), PlayerName[playerid]);
		SendClientMessage(playerid, COLOR_LIGHTRED, string);

		format(string, sizeof(string), "Motivo: %s", result);
		SendClientMessage(playerid, COLOR_LIGHTRED, string);

		format(string, sizeof(string), "Se achar que foi algum erro administrativo, poderá recorrer aos superiores...");
		SendClientMessage(playerid, COLOR_LIGHTRED, string);

		format(string, sizeof(string), "ou mesmo denunciar o Administrador pelo nosso painel do servidor.");
		SendClientMessage(playerid, COLOR_LIGHTRED, string);
	}

	if (PlayerInfo[idplayer][pWarns] >= 3) {
		SendClientMessage(idplayer, COLOR_PURPLE, "Sua conta atingiu o limite de avisos, portanto você está automaticamente banido pelo sistema.");

		format(string, sizeof(string), "STAFF: %s foi banido por (%d dias) automaticamente, motivo: %s",PlayerName[idplayer], PlayerInfo[idplayer][pWarns], PlayerInfo[idplayer][pMotivoAgendou]);
	    SendClientMessageToAll(COLOR_LIGHTRED, string);

		Banned_Player(Player_GetAccountID(idplayer), 0, PlayerIP[idplayer], "Limite de 3 avisos", (PlayerInfo[idplayer][pWarns] * 3));
	    PlayerInfo[idplayer][pWarns] = 0;

		KickEx(idplayer);
		return 1;
	}

	format(string, sizeof(string), "%s, %s aplicou aviso na conta de %s com motivo: %s", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer], result);
	server_log("avisos", string);

	return 1;
}

// Função para obter o último timestamp de saque associado ao administrador
forward GetAdminLastMoneyPickup(playerid);

// Função para definir o último timestamp de saque associado ao administrador
forward SetAdminLastMoneyPickup(playerid, timestamp);

CMD:dinheiroevento(playerid)
{
    if (Admin_GetNivel(playerid) < ENCARREGADO)
        return SendClientMessage(playerid, -1, "Você não tem permissão para usar este comando.");

    if (Admin_GetNivel(playerid) > DIRETOR) {
        goto skip_founder_moneyevento;
    }

    if (!Staff_GetWorking(playerid))
        return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

    skip_founder_moneyevento:
    new currentTimestamp = gettime();
    new playerName[MAX_PLAYER_NAME];

    if ((currentTimestamp - GetAdminLastMoneyPickup(playerid)) < (24 * 60 * 60))
        return SendClientMessage(playerid, -1, "Você já pegou dinheiro administrativo hoje. Tente novamente amanhã.");

    new eventomoney = 3000000;
    new string[128];

    if (CofreEvento < eventomoney)
        return SendClientMessage(playerid, -1, "O cofre de eventos não tem dinheiro suficiente para esta distribuição.");

	Player_AddMoney(playerid, eventomoney);
    GetPlayerName(playerid, playerName, sizeof(playerName));

	CofreEvento -= eventomoney;
    SaveStuff();

    format(string, sizeof(string), "Você recebeu {006400}$%s{FFA500} para realizar eventos, gaste tudo até amanhã.", getFormatText(eventomoney));
    SendClientMessage(playerid, COLOR_ORANGE, string);

    SetAdminLastMoneyPickup(playerid, currentTimestamp);

	format(string, sizeof(string), "{FFA500}EVENTO: {FA4747}%s, %s pegou $3.000.000 do cofre administrativo.", Staff_GetPositionName(playerid), PlayerName[playerid]);
    Staff_ChatToAll(COLOR_LIGHTRED, string);

    format(string, sizeof(string), "%s, %s pegou $%s do cofre de eventos", Staff_GetPositionName(playerid), PlayerName[playerid], getFormatText(eventomoney));
    server_log("cofreadmin", string);

    return 1;
}

// Sistema de Contagem para Administradores
forward Countdown10(x);
forward Countdown9(x);
forward Countdown8(x);
forward Countdown7(x);
forward Countdown6(x);
forward Countdown5(x);
forward Countdown4(x);
forward Countdown3(x);
forward Countdown2(x);
forward Countdown1(x);
forward CountdownGo(x);

CMD:contagem(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ADMINISTRADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	if (Admin_GetNivel(playerid) > DIRETOR)
		goto skip_founder_contagem;

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_contagem:

	new string[128];
	new startCountdown;
	new countdownFunction[32];

	if(sscanf(params, "d", startCountdown)) {
		if(startCountdown < 3 || startCountdown > 10) {
			SendClientMessage(playerid, -1, "Uso correto: /contagem [3-10]");
			return SendClientMessage(playerid, -1, "Número inválido. Escolha um número entre 3 e 10.");
		}
	}
	
	format(string, sizeof(string), "{FFFF00}CONTAGEM:{FFFFFF} %s, %s iniciou uma contagem de %d segundos.", Staff_GetPositionName(playerid), PlayerName[playerid], startCountdown);
	SendClientMessageToAll(COLOR_YELLOW, string);

	format(countdownFunction, sizeof(countdownFunction), "Countdown%d", startCountdown);

	foreach (new x : Player)
	{
		GameTextForPlayer(x, "~g~Iniciando contagem...", 3000, 3);
		PlayerPlaySound(x, 1056, 0.0, 0.0, 0.0);
		SetTimerEx(countdownFunction, 3000, false, "i", x);
	}

	return 1;
}

public Countdown10(x)
{
	GameTextForPlayer(x,"~r~10", 1000, 6);
	PlayerPlaySound(x, 1056, 0.0, 0.0, 0.0);
	SetTimerEx("Countdown9", 1000, false, "i", x);
}

public Countdown9(x)
{
	GameTextForPlayer(x,"~r~9", 1000, 6);
	PlayerPlaySound(x, 1056, 0.0, 0.0, 0.0);
	SetTimerEx("Countdown8", 1000, false, "i", x);
}

public Countdown8(x)
{
	GameTextForPlayer(x,"~r~8", 1000, 6);
	PlayerPlaySound(x, 1056, 0.0, 0.0, 0.0);
	SetTimerEx("Countdown7", 1000, false, "i", x);
}

public Countdown7(x)
{
	GameTextForPlayer(x,"~r~7", 1000, 6);
	PlayerPlaySound(x, 1056, 0.0, 0.0, 0.0);
	SetTimerEx("Countdown6", 1000, false, "i", x);
}

public Countdown6(x)
{
	GameTextForPlayer(x,"~r~6", 1000, 6);
	PlayerPlaySound(x, 1056, 0.0, 0.0, 0.0);
	SetTimerEx("Countdown5", 1000, false, "i", x);
}

public Countdown5(x)
{
	GameTextForPlayer(x,"~r~5", 1000, 6);
	PlayerPlaySound(x, 1056, 0.0, 0.0, 0.0);
	SetTimerEx("Countdown4", 1000, false, "i", x);
}
public Countdown4(x)
{
	GameTextForPlayer(x,"~r~4", 1000, 6);
	PlayerPlaySound(x, 1056, 0.0, 0.0, 0.0);
	SetTimerEx("Countdown3", 1000, false, "i", x);
}
public Countdown3(x)
{
	GameTextForPlayer(x, "~r~3", 1000, 6);
	PlayerPlaySound(x, 1056, 0.0, 0.0, 0.0);
	SetTimerEx("Countdown2", 1000, false, "i", x);
}

public Countdown2(x)
{
	GameTextForPlayer(x, "~r~2", 1000, 6);
	PlayerPlaySound(x, 1056, 0.0, 0.0, 0.0);
	SetTimerEx("Countdown1", 1000, false, "i", x);
}

public Countdown1(x)
{
	GameTextForPlayer(x, "~r~1", 1000, 6);
	PlayerPlaySound(x, 1056, 0.0, 0.0, 0.0);
	SetTimerEx("CountdownGo", 1000, false, "i", x);
}

public CountdownGo(x)
{
	GameTextForPlayer(x, "~y~GO!", 1000, 6);
	PlayerPlaySound(x, 1057, 0.0, 0.0, 0.0);
}

CMD:trollsocio(playerid, const result[])
{
	if (Admin_GetNivel(playerid) < DONO)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	new idPlayer;

	if (sscanf(result, "us[36]", idPlayer, result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /trollsocio (id/nick do jogador) (texto no chat sócio)");

	if (Founders_GetList(playerid)) {
		goto skip_founder_fakesocio;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho!");

	if (!PlayerInfo[idPlayer][pVIP]) 
		return SendClientMessage(playerid, -1, "O jogador não possui Sócio ativo.");

	skip_founder_fakesocio:
	new string[128];
	new stringlog[128];

	//if (!PlayerInfo[idPlayer][pChatVip]) return SendClientMessage(playerid, -1, "O chat-scio do jogador est desligado."); Ignorado por agora...

	if (gettime() < GetPVarInt(playerid, #varFlood_chat)) return SendClientMessage(playerid, COLOR_GRAD, #Voc no pode usar este comando com tanta frequencia);

	SetPVarInt(playerid, #varFlood_chat, gettime() + 5);

	format(string, sizeof(string), "Você trollou %s com o uso do chat sócio.", PlayerName[idPlayer]);
	SendClientMessage(playerid, COLOR_WHITE, string);

	format(string, sizeof(string), "[%s{33FF00}] %s: %s", GetDonateRank(idPlayer), PlayerName[idPlayer], result);

	format(stringlog, sizeof(stringlog), "%s, %s trollou %s com a mensagem: %s", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idPlayer], result);
	server_log("trollsocio", stringlog);

	#if defined _CENSORED_protection
		censored_word_detected(string);
	#endif

	SendVIPMessage(0x33FF00FF, string);

	return true;
}

CMD:gmx(playerid, params[])
{
	// Nível de admin necessário para usar o comando
	if (Admin_GetNivel(playerid) < DIRETOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new motivo[30];
	if (sscanf(params, "s[30]", motivo))
		return SendClientMessage(playerid, -1, "Modo de uso: /gmx [motivo]");

	if (strlen(motivo) > 30)
		return SendClientMessage(playerid, -1, "O motivo de seu GMX deve ter no máximo 30 caracteres.");

	GMX(PlayerName[playerid], motivo);
	
	return 1;
}

CMD:ir(playerid, params[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid))) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) goto skip_founder_ir;

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_ir:
	new idplayer;
	if (sscanf(params, "u", idplayer)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /ir (id do jogador)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (SpectadorInfo[idplayer][spectadorID] != INVALID_PLAYER_ID) 
		return SendClientMessage(playerid, -1, "O administrador está em modo tv.");

	if (Admin_GetNivel(idplayer) >= Admin_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para ir nesse administrador.");

	if (Admin_GetNivel(idplayer) > ESTAGIARIO && !Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para ir até um administrador.");

	if (idplayer == playerid)
		return SendClientMessage(playerid, -1, "Você não pode ir a você mesmo.");

	new 
		Float:playerPos[3];

	GetPlayerPos(idplayer, playerPos[0], playerPos[1], playerPos[2]);

	SetPlayerInterior(playerid, GetPlayerInterior(idplayer));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(idplayer));
	
	if (Player_GetInHouse(idplayer) != -1)
		Player_SetInHouse(playerid, Player_GetInHouse(idplayer));
	
	if (GetPlayerCurrentInt(idplayer) != -1)
		SetPlayerCurrentInt(playerid, GetPlayerCurrentInt(idplayer));
	 
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		SetVehiclePos(GetPlayerVehicleID(playerid), playerPos[0], playerPos[1] + 2.0, playerPos[2]);
	} else {
		SetPlayerPos(playerid, playerPos[0], playerPos[1] + 2.0, playerPos[2]);
	}

	new string[128];

	if (Admin_GetNivel(playerid) <= MASTER)
	{
		format(string, sizeof(string), "[VIGILANTE] %s, %s foi até ao jogador %s (%d).", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer], idplayer);
		Staff_ChatToAll(COLOR_LIGHTRED, string, MASTER);
	}
	else if (Admin_GetNivel(playerid) <= DONO)
	{
		format(string, sizeof(string), "[VIGILANTE] %s, %s foi até ao jogador %s (%d).", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer], idplayer);
		Staff_ChatToAll(COLOR_LIGHTRED, string, DONO);
	}

	SendMsgF(idplayer, COLOR_LIGHTGREEN, "%s: %s veio até sua posição!", Admin_GetNivel(playerid) ? ("Admin") : ("Helper"), PlayerName[playerid]);
	SendMsgF(playerid, COLOR_LIGHTGREEN, "Você foi até a posição do jogador: %s.", PlayerName[idplayer]);

	return 1;
}

CMD:respawnp(playerid, params[])
{
	new string[121],
		Float:distancia,
		contagem_vehicles = 0,
		Float:x, Float:y, Float:z
	;

	if(sscanf(params, "f", distancia))
		return SendClientMessage(playerid, -1, "Modo de uso: /respawnp (Distância)");

	if (Admin_GetNivel(playerid) < MODERADOR)
		return SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_respawnp;
	}

	if (Admin_GetNivel(playerid) < DONO && !Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_respawnp:

	for (new vid; vid != MAX_VEHICLES; vid++) {

		GetVehiclePos(vid, x, y, z);

		if (PlayerToPoint(distancia, playerid, x, y, z))
		{
			if (!IsTruckCarJob(vid))
			{
				contagem_vehicles++;
				SetVehicleToRespawn(vid);
			}
		}
	}

	if (contagem_vehicles > 0) {
		format(string, sizeof(string), "AdmAviso: %s deu respawn de veículos próximos. (Distância: %.2f | Total de veículos: %d).", PlayerName[playerid], distancia, contagem_vehicles);
		Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
	} else {
		return SendClientMessage(playerid, -1, "Não há veículos próximo a esta distância!");
	}
	return true;
}

CMD:respawnid(playerid, params[]) {

	new string[72];

	if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não tem autorização a usar este comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_respawnid;
	}

	if (Admin_GetNivel(playerid) < DONO && !Staff_GetWorking(playerid)) return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_respawnid:

	if (!IsPlayerInAnyVehicle(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em um veículo.");

	format(string, sizeof(string), "AdmAviso: %s deu respawn no veículo ID: %d.", PlayerName[playerid], GetPlayerVehicleID(playerid));
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

	SetVehicleToRespawn(GetPlayerVehicleID(playerid));
	return true;
}

CMD:respawncarros(playerid, params[])
{
	new string[84];

	if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando !");

	if (Founders_GetList(playerid)) {
		goto skip_founder_respawncarros;
	}

	if (Admin_GetNivel(playerid) < DONO && !Staff_GetWorking(playerid)) return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_respawncarros:

	format(string, sizeof(string), "AdmAviso: %s deu respawn em todos os veículos do servidor.", PlayerName[playerid]);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

	gIniciarRespawn(); 
	server_log("respawncarros", string);

	return true;
}

CMD:explodir(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MODERADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /explodir (id do jogador)");

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (Admin_GetNivel(playerid) >= CO_FUNDADOR) {
		goto skip_founder_explodir;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

	skip_founder_explodir:
	new 
		string[128],
		Float:px,
		Float:py, 
		Float:pz;

	GetPlayerPos(idplayer, px, py, pz);
	CreateExplosion(px, py, pz + 3, 1, 3);

	format(string, sizeof(string), "AdmCmd: %s explodiu %s.", PlayerName[playerid], PlayerName[idplayer]);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
	server_log("comandosadmin", string);

	return 1;
}

CMD:trazer(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ESTAGIARIO) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /trazer (id do jogador)");
		
	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (Player_GetJailed(idplayer))
		return SendClientMessage(playerid, -1, "Este jogador está preso você não pode puxa-lo");

	if (Player_InMenu(idplayer))
		return SendClientMessage(playerid, -1, "O jogador está em um menu, aguarde para traze-lo.");

	if (SpectadorInfo[idplayer][spectadorID] != INVALID_PLAYER_ID) 
		return SendClientMessage(playerid, -1, "O administrador está em modo tv.");

	if (Founders_GetList(playerid) || Admin_GetNivel(playerid) >= SUB_DONO)
		goto skip_founder_trazer;

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	if (Admin_GetNivel(idplayer) > Admin_GetNivel(playerid))
		return SendClientMessage(playerid, COLOR_GRAD, "Você não tem autorização para trazer esse admin.");

	skip_founder_trazer:

	new 
		Float:pos[3],
		interior = GetPlayerInterior(playerid),
		world = GetPlayerVirtualWorld(playerid),
		string[128];

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	SetPlayerInterior(idplayer, interior);
	SetPlayerCurrentInt(idplayer, interior);
	SetPlayerVirtualWorld(idplayer, world);

	format(string, sizeof(string), "** %s, %s levou %s", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer]);
	SendClientMessageInRange(30.0, idplayer, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

	if (GetPlayerState(idplayer) == PLAYER_STATE_DRIVER) {
		new vehicleid = GetPlayerVehicleID(idplayer);
		LinkVehicleToInterior(vehicleid, interior);
		SetVehiclePos(vehicleid, pos[0], pos[1] + 4.0, pos[2]);
	} else {
		SetPlayerPos(idplayer, pos[0], pos[1] + 2.0, pos[2]);
	}

	format(string, sizeof(string), "** %s, %s trouxe %s", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer]);
	SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

	return 1;
}

CMD:trazer2(playerid, params[])
{
	new plo;
	if(sscanf(params, "u", plo))
	{
		SendClientMessage(playerid, -1, "Use: /trazer2 [id/nick] - Trazer sem armas");
		return 1;
	}
	new Float:plocx,Float:plocy,Float:plocz;
	new string[128];
	if (IsPlayerConnected(plo))
	{
		if (SpectadorInfo[plo][spectadorID] != INVALID_PLAYER_ID) 
		return SendClientMessage(playerid, -1, "O administrador está em modo tv.");

		if(Player_GetJailed(playerid))
		{
			SendClientMessage(playerid, -1, "Este jogador está preso você não pode puxa-lo");
			return 1;
		}
		if(plo != INVALID_PLAYER_ID)
		{
			if (Founders_GetList(playerid)) {
				goto skip_founder_trazersemarmas;
			}
			if (Admin_GetNivel(playerid) >= ESTAGIARIO)
			{
				if(!Staff_GetWorking(playerid))
				{
					return SendClientMessage(playerid, -1, "Você não está em modo trabalho!");
				}
				if(!Admin_GetNivel(playerid) && Admin_GetNivel(plo))
				{
					return SendClientMessage(playerid, -1, "Você não pode trazer um admin, peça para ele ir até você !");
				}
				if(Admin_GetNivel(playerid) && !Staff_GetWorking(playerid) && Admin_GetNivel(playerid) < DONO)
					return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

				skip_founder_trazersemarmas:
				GetPlayerPos(playerid, plocx, plocy, plocz);
				if (GetPlayerInterior(playerid))
				{
					SetPlayerInterior(plo, GetPlayerInterior(playerid));
				}
				if (!GetPlayerInterior(playerid))
				{
					SetPlayerInterior(plo, 0);
				}
				if(plocz > 930.0 && !GetPlayerInterior(playerid)) //the highest land point in sa = 526.8
				{
					SetPlayerInterior(plo, 1);
				}
				if (GetPlayerState(plo) == PLAYER_STATE_DRIVER)
				{
					SetPlayerInterior(plo, GetPlayerInterior(playerid));
					SetPlayerVirtualWorld(plo,GetPlayerVirtualWorld(playerid));
					new tmpcar = GetPlayerVehicleID(plo);
					SetVehiclePos(tmpcar, plocx, plocy+4, plocz);
				}
				else
				{
					SetPlayerInterior(plo, GetPlayerInterior(playerid));
					SetPlayerVirtualWorld(plo,GetPlayerVirtualWorld(playerid));
					SetPlayerPos(plo,plocx,plocy+2, plocz);
				}
				ResetPlayerWeapons(playerid);
				SetPlayerHealth(plo, 100.0);
				SetPlayerArmour(plo, 100.0);
				if(Admin_GetNivel(playerid))
				{
					format(string, sizeof(string), "*Admin %s levou %s", PlayerName[playerid],PlayerName[plo]);
					SendClientMessageInRange(30.0, plo, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
					format(string, sizeof(string), "*Admin %s trouxe %s", PlayerName[playerid],PlayerName[plo]);
					SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				}
				else
				{
					format(string, sizeof(string), "*Helper %s levou %s", PlayerName[playerid],PlayerName[plo]);
					SendClientMessageInRange(30.0, plo, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
					format(string, sizeof(string), "*Helper %s trouxe %s", PlayerName[playerid],PlayerName[plo]);
					SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				}
			}
			else
			{
				SendClientMessage(playerid, -1, "Você precisa ser admin para usar este comando.");
			}
		}
	}
	else
	{
		format(string, sizeof(string), "   %d não é um jogador ativo.", plo);
		SendClientMessage(playerid, COLOR_GRAD, string);
	}
	return 1;
}

// Criação das variáveis globais necessárias para o comando Trazer Todos
new Float:tzt[3]; // Variável da posição do Administrador
new tztinterior; // Variável do Interior do Administrador
new tztworld; // Variável do Mundo do Administrador

CMD:trazertodos(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ADMINISTRADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");
	
	if (Founders_GetList(playerid)) {
		goto skip_founder_trazertodos;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_trazertodos:

	// Declaração dos valores das variáveis
	GetPlayerPos(playerid, tzt[0], tzt[1], tzt[2]);
	tztinterior = GetPlayerInterior(playerid);
	tztworld = GetPlayerVirtualWorld(playerid);

	MEGAString[0] = EOS;

	strcat(MEGAString, ""C_GRAY"Você está prestes a fazer uma chamada a todos os jogadores do servidor para vir até sua localização.\n\n");
	strcat(MEGAString, ""C_YELLOW"Tem a certeza que deseja prosseguir com o comando?");

	ShowPlayerDialog(playerid, 10048, DIALOG_STYLE_MSGBOX, ""C_GRAY"Confirmação do Comando", MEGAString, ""C_GRAY"Sim", ""C_GRAY"Não");

	return 1;
}
alias:trazertodos("tzt")

// Variáveis - Confirmação Vida/Colete - Trazer Todos
new confirmacaovida; // Variável global para confirmar vida com ou sem colete

stock ConfirmacaoVidaColete(playerid) {

	MEGAString[0] = EOS;

	strcat(MEGAString, ""C_WHITE"Trazer todos os jogadores sem colete ou com colete?\n\n");
	strcat(MEGAString, ""C_WHITE"Qual das opções deseja trazer todos os jogadores?");

	ShowPlayerDialog(playerid, 10049, DIALOG_STYLE_MSGBOX, ""C_GRAY"Confirmação de Vida e Colete - Trazer Todos", MEGAString, ""C_WHITE"Sem", ""C_WHITE"Com");
}

// Função - Chamada Trazer Todos (vai ser chamada pelo dialogid ao confirmar o comando)
stock ChamadaTrazerTodos(playerid) {

	foreach(new i : Player) {

		MEGAString[0] = EOS;

		if (PlayerInfo[playerid][pSex] == 2) {
			format(MEGAString, sizeof(MEGAString), "A %s, %s está levando todos à sua localização, deseja ir?\n\n", Staff_GetPositionName(playerid), PlayerName[playerid]);
			strcat(MEGAString, ""C_WHITE"Clique no botão '{00FF00}Sim{FFFFFF}' caso deseja ir até a localização da Administradora.\n");
			strcat(MEGAString, ""C_WHITE"Caso não deseja ir, clique no botão '{FF0000}Não{FFFFFF}'.");

			ShowPlayerDialog(i, 10050, DIALOG_STYLE_MSGBOX, ""C_GRAY"Chamada da Administradora", MEGAString, ""C_WHITE"Sim", ""C_WHITE"Não");
		}
		else {
			format(MEGAString, sizeof(MEGAString), "O %s, %s está levando todos à sua localização, deseja ir?\n\n", Staff_GetPositionName(playerid), PlayerName[playerid]);
			strcat(MEGAString, ""C_WHITE"Clique no botão '{00FF00}Sim{FFFFFF}' caso deseja ir até a localização do Administrador.\n");
			strcat(MEGAString, ""C_WHITE"Caso não deseja ir, clique no botão '{FF0000}Não{FFFFFF}'.");

			ShowPlayerDialog(i, 10050, DIALOG_STYLE_MSGBOX, ""C_GRAY"Chamada do Administrador", MEGAString, ""C_WHITE"Sim", ""C_WHITE"Não");
		}
	}
}

CMD:trazerx1(playerid, params[])
{
	new idPlayer;

	if (Admin_GetNivel(playerid) < ADMINISTRADOR) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_trazerxum;
	}

	if (Admin_GetNivel(playerid) < MASTER && !Staff_GetWorking(playerid)) return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_trazerxum:

	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /trazerx1 (id do jogador)");

	if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (SpectadorInfo[idPlayer][spectadorID] != INVALID_PLAYER_ID) 
		return SendClientMessage(playerid, -1, "O administrador está em modo tv.");

	new Float:playerPos[3], string[128];

	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);

	if (GetPlayerInterior(playerid)) {
		SetPlayerInterior(idPlayer, GetPlayerInterior(playerid));
	}
	else SetPlayerInterior(idPlayer, 0);

	if (playerPos[2] > 930.0 && !GetPlayerInterior(playerid)) SetPlayerInterior(idPlayer, 1);

	SetPlayerInterior(idPlayer, GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(idPlayer, GetPlayerVirtualWorld(playerid));

	ResetPlayerWeapons(playerid);
	SetPlayerHealth(idPlayer, 100);
	SetPlayerArmour(idPlayer, 100);
	GivePlayerWeapon(idPlayer, WEAPON_DEAGLE, 9999);
	GivePlayerWeapon(idPlayer, WEAPON_SHOTGUN, 9999);

	if (GetPlayerState(idPlayer) == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(idPlayer);
		SetVehiclePos(vehicleid, playerPos[0], playerPos[1] + 4, playerPos[2]);
	}
	else SetPlayerPos(idPlayer, playerPos[0], playerPos[1] + 2, playerPos[2]);

	format(string, sizeof(string), "Administrador: %s, levou o jogador %s para o evento x1!", PlayerName[playerid], PlayerName[idPlayer]);
	SendClientMessageInRange(30.0, idPlayer, string, 0xFFDEADFF, 0xFFDEADFF, 0xFFDEADFF, 0xFFDEADFF, 0xFFDEADFF);

	format(string, sizeof(string), "Administrador: %s, trouxe o jogador %s para o evento x1!", PlayerName[playerid], PlayerName[idPlayer]);
	SendClientMessageInRange(30.0, playerid, string, 0xFFDEADFF, 0xFFDEADFF, 0xFFDEADFF, 0xFFDEADFF, 0xFFDEADFF);

	return true;
}


CMD:trazerveiculo(playerid, params[])
{
		new plo;
		if(sscanf(params, "d", plo))
		{
			SendClientMessage(playerid, -1, "Use: /trazerveiculo [carro id]");
			return true;
		}
		new Float:plocx,Float:plocy,Float:plocz;
		if (Admin_GetNivel(playerid) >= ADMINISTRADOR)
		{
			if (Founders_GetList(playerid)) {
				goto skip_founder_trazerveiculo;
			}
			if(!Staff_GetWorking(playerid))
				return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

			skip_founder_trazerveiculo:
			GetPlayerPos(playerid, plocx, plocy, plocz);
			SetVehiclePos(plo,plocx,plocy+4, plocz);
			LinkVehicleToInterior(plo, 0);
		}
		else
		{
			SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
		}
		return true;
}

CMD:secsetcash(playerid, params[])
{
	if (Dev_GetNivel(playerid) < DEV_OMEGA) 
		return SendClientMessage(playerid, -1, "Você não tem permissão para usar esse comando.");

	if (!Dev_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Seu nick não tem permissão para usar este comando.");

	new namePlayer[MAX_PLAYER_NAME], quantidade, metodo;
    if (sscanf(params, "s[24]dd", namePlayer, quantidade, metodo)) return SendClientMessage(playerid, -1, "Modo de usar: /darcash (nick do jogador) (quantidade) (metodo do pagamento)");

	if (metodo == 50)
		goto skip_pagamento_map;

	if (metodo < 1 || metodo > 17) 
		return SendClientMessage(playerid, -1, "O método de pagamento deve estar entre 1 a 17.");

	skip_pagamento_map:

	if (!DoesPlayerExists(namePlayer)) 
		return SendClientMessage(playerid, -1, "Erro: Conta não registrada!");

	AtivarCash(PlayerName[playerid], namePlayer, quantidade, metodo);

    return 1;
}

// CMD:alterarmodo(playerid) 
// {
// 	if (Dev_GetNivel(playerid) < DEV_ALPHA)
// 		return SendClientMessage(playerid, -1, "Você não possui autorização para usar esse comando.");

// 	new mobile = GetPVarInt(playerid, "NotAndroid");

// 	if (mobile)
// 		SetPVarInt(playerid, "NotAndroid", 0);
// 	else
// 		SetPVarInt(playerid, "NotAndroid", 1);

// 	SendMsgF(playerid, COLOR_LIGHTGREEN, "Você mudou para o modo %s", mobile ? "Android" : "PC");

// 	return 1;
// }

CMD:updateskate(playerid, params[]) 
{
	if (Dev_GetNivel(playerid) < DEV_ALPHA)
		return SendClientMessage(playerid, -1, "Você não pode usar este comando !");

	new limite;

	if (sscanf(params, "d", limite))
		return SendClientMessage(playerid, -1, "Modo de uso: /updateskate [20 - 1000] "C_CYAN"Recomendado: Maior que 70.");

	if (limite < 20 || limite > 1000)
		return SendClientMessage(playerid, -1, "Observação: Você deve definir um valor de 20 á 1000");

	update_rate_skate = limite;

	SendMsgF(playerid, COLOR_LIGHTRED, "AdmCmd: Você setou a velocidade de update do skate para %d.", update_rate_skate);

	return 1;
}

CMD:logchat(playerid)
{
	if (Dev_GetNivel(playerid) < DEV_ALPHA)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");
	
	if (!Admin_GetLogChat())
		Admin_SetLogChat(true);
	else
		Admin_SetLogChat(false);

	new string[69];

	format(string, sizeof string, "AdmAviso: %s %s o log de chat local.", PlayerName[playerid], Admin_GetLogChat() ? "ativou" : "desativou");
	Staff_ChatToAll(COLOR_LIGHTRED, string, DESENVOLVEDOR);

	server_log("admin", string);

	return 1;
}

CMD:testeanim(playerid) 
{
	if (Dev_GetNivel(playerid) < DEV_ALPHA) 
		return SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando.");

	if (GetPlayerAnimationIndex(playerid)) {
        new
            animLib[32],
            animName[32],
            msg[128];

        GetAnimationName(GetPlayerAnimationIndex(playerid), animLib, sizeof animLib, animName, sizeof animName);
        format(msg, sizeof msg, "Running anim: %s %s %d", animLib, animName, GetPlayerAnimationIndex(playerid));
        SendClientMessage(playerid, -1, msg);
    }
	return 1;
}

CMD:atualizarranks(playerid)
{
	if (Admin_GetNivel(playerid) < DIRETOR)
	    return SendClientMessage(playerid, -1, "Você não pode usar este comando !");

	SendMsgAllF(COLOR_LIGHTRED, "AdmAviso: %s atualizou manualmente os ranks.", PlayerName[playerid]);

	foreach (new id : Player)
	   	AtualizarRank(id);

	return 1;
}

CMD:resetarranks(playerid)
{
	if (Dev_GetNivel(playerid) < DEV_ALPHA) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	SendMsgAllF(COLOR_LIGHTRED, "AdmAviso: %s resetou todos os ranks.", PlayerName[playerid]);

    mysql_tquery(MySQL_Handle, "DELETE FROM `ranks`");

	return 1;
}

CMD:resetativo(playerid) 
{
	if (Dev_GetNivel(playerid) < DEV_ALPHA)
	    return SendClientMessage(playerid, -1, "Você não pode usar este comando !");

	SendMsgAllF(COLOR_LIGHTRED, "AdmAviso: %s resetou o rank ''Ativo do dia''", PlayerName[playerid]);

    mysql_tquery(MySQL_Handle, "UPDATE `ranks` SET `jogoudia` = '0'");
	
	return 1;
}

CMD:rcaixasequipamento(playerid)
{
	if (Dev_GetNivel(playerid) < DEV_ALPHA) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new 
		count = destroyAllGunBoxes(), 
		string[128]
	;

	format(string, sizeof(string), "AdmCmd: %s, %s removeu todas as caixas de equipamento do servidor | total: %d.", Staff_GetPositionName(playerid), PlayerName[playerid], count);
	Staff_ChatToAll(COLOR_LIGHTRED, string);

	return 1;
}

// ---------------------------------------------------------------------------------------
// Dono:

CMD:mudarsenhaadmin(playerid, params[])
{
	if (Admin_GetNivel(playerid) < DONO)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (sscanf(params, "s[128]", params))
		return SendClientMessage(playerid, -1, "Modo de uso: /mudarsenhaadmin (nova senha)");

	format(SenhaAdministracao, 128, params);
	SalvarSenhaAdmin();

	new string[128];
	format(string, sizeof string, "AdminAviso: %s mudou a senha da administração para: %s.", PlayerName[playerid], params);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

	return 1;
}

CMD:verparticulares(playerid, params[])
{
	if (Admin_GetNivel(playerid) < DONO)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!SpyGet_Particulares(playerid)) {
		SpySet_Particulares(playerid, true);
	} else {
		SpySet_Particulares(playerid, false);
	}
	SendMsgF(playerid, COLOR_GRAD, "Você %s o modo SPY: particulares (/par).", SpyGet_Particulares(playerid) ? "ativou" : "desativou");

	return 1;
}

CMD:admsecreto(playerid)
{
	if (Admin_GetNivel(playerid) < DIRETOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");
	
	if (Staff_GetSecret(playerid)) {
		Staff_SetSecret(playerid, false);
	} else {
		Staff_SetSecret(playerid, true);
	}

	SendMsgF(playerid, COLOR_GRAD, "Você %s de modo secreto.", Staff_GetSecret(playerid) ? "entrou" : "saiu");
	SetPlayerToTeamColor(playerid);
	
	return 1;
}

CMD:versms(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MASTER)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_versms;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_versms:
	
	if (!SpyGet_Messages(playerid)) {
		SpySet_Messages(playerid, true);
	} else {
		SpySet_Messages(playerid, false);
	}

	SendMsgF(playerid, COLOR_GRAD, "Você %s o modo SPY: mensagens (/sms).", SpyGet_Messages(playerid) ? "ativou" : "desativou");

	return 1;
}

CMD:settempocadeia(playerid, params[])
{
    if (Admin_GetNivel(playerid) < ADMINISTRADOR)
        return SendClientMessage(playerid, -1, "Você não pode usar este comando.");

    if (Founders_GetList(playerid)) {
        goto skip_founder_settempocadeia;
    }

    if (!Staff_GetWorking(playerid)) 
        return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

    skip_founder_settempocadeia:

    new presoid;
	new tempominutos;
	new temposegundos;

    if (sscanf(params, "uud", presoid, tempominutos))
        return SendClientMessage(playerid, -1, "Modo de uso: /settempocadeia (id do jogador) (tempo [em minutos])");

    // Conversão para segundos
    temposegundos = tempominutos * 60;

    if (!Player_Logado(presoid)) 
        return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

    if (!Player_GetJailed(presoid))
        return SendClientMessage(playerid, -1, "O jogador não está preso.");
        
    new string[128];
    format(string, sizeof(string), "(Cadeia): %s setou o tempo de cadeia de %s para %d minutos.", PlayerName[playerid], PlayerName[presoid], tempominutos);
    Staff_ChatToAll(COLOR_LIGHTRED, string);

    Jail_SetTime(presoid, temposegundos);

    return 1;
}

CMD:logsplayer(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MASTER) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_logsplayer;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_logsplayer:
	new namelog[75], nameplayerid[MAX_PLAYER_NAME];

	if (sscanf(params, "s[75]s[24]", namelog, nameplayerid)) return SendClientMessage(playerid, -1, "Modo de uso: /logsplayer (nome do log) (nome do player)");

    if (!strcmp(namelog, "ip", true) && Admin_GetNivel(playerid) < MASTER) return SendClientMessage(playerid, -1, "Esse log não é permitido para o seu cargo.");

	if (!strcmp(nameplayerid, "Theus_Crazzy", true) || !strcmp(nameplayerid, "iHollyZinhO", true) || !strcmp(nameplayerid, "Joao_Revolts", true)) return SendClientMessage(playerid, -1, "Você não pode ver logs de um programador.");

	if (!strcmp(namelog, "Observacao", true)) return SendClientMessage(playerid, -1, "Esse log não é permitido para o seu cargo.");

	if (!strcmp(namelog, "chat_gestor", true) && Dev_GetNivel(playerid) < DEV_ALPHA) return SendClientMessage(playerid, -1, "Esse log não é permitido para o seu cargo.");

	if (!strcmp(namelog, "senhastrocadas", true) && Admin_GetNivel(playerid) < DONO) return SendClientMessage(playerid, -1, "Esse log não é permitido para o seu cargo.");

    show_server_log_pl(playerid, nameplayerid, namelog);

	return true;
}

CMD:banimentos(playerid, params[]) 
{
	if (Admin_GetNivel(playerid) < MODERADOR)
	    return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_banimentos;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_banimentos:

	if (sscanf(params, "s[24]", params))
		return SendClientMessage(playerid, -1, "Modo de uso: /banimentos (nick do admin)");

	show_list_bans_admin(playerid, params);

	return 1;
}

CMD:ultimosbanidos(playerid, params[]) 
{
	if (Admin_GetNivel(playerid) < MODERADOR)
	    return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_ultimosbanimentos;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_ultimosbanimentos:

	show_list_bans_ultimos(playerid);

	return 1;
}

CMD:setar(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ESTAGIARIO) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer;

	if (sscanf(params, "u", idplayer)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /setar (id do jogador)");

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_settime;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	if (Founders_GetList(idplayer))
		return SendClientMessage(playerid, -1, "Você não pode setar esse administrador.");

	skip_founder_settime:
	SpawnPlayer(idplayer);

	SendMsgF(idplayer, COLOR_LIGHTBLUE, "%s setou você em seu spawn. Caso queira trocar use: /mudarlocal.", PlayerName[playerid]);
	PlayerPlaySound(idplayer, 1068, 0.0, 0.0, 0.0);

	defer stopMusic(idplayer);

	new string[128];
	format(string, sizeof string, "AdmAviso: %s setou %s pra seu local de spawn.", PlayerName[playerid], PlayerName[idplayer]);
	Staff_ChatToAll(COLOR_LIGHTRED, string);

	return 1;
}

CMD:agendarcadeia(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MODERADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_agendarcadeia;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_agendarcadeia:
	new reason[64], jailedPlayer[MAX_PLAYER_NAME], denunciator[MAX_PLAYER_NAME];
	if (sscanf(params, "s[24]s[24]s[15]", jailedPlayer, denunciator, reason)) {
		SendClientMessage(playerid, -1, "Modo de uso: /agendarcadeia (nick do jogador) (nick do denunciante) (motivo)");
		SendClientMessage(playerid, -1, "Tempo: O tempo de cadeia é calculado automaticamente");
		return true;
	}

	if (strlen(reason) < 3 || strlen(reason) > 14)
		return SendClientMessage(playerid, -1, "O motivo deve conter de 3 a 14 caracteres, crie abreviação.");

	new idplayer = GetPlayerID(jailedPlayer);

	if (Player_Logado(idplayer)) {
		SendClientMessage(playerid, -1, "O jogador está online, será automaticamente dado cadeia admin.");
		return callcmd::cadeia(playerid, params);
	}

	if (!DoesPlayerExists(jailedPlayer))
		return SendClientMessage(playerid, -1, "Não existe um jogador com esse nick para ser punido.");

	if (!DoesPlayerExists(denunciator))
		return SendClientMessage(playerid, -1, "Não existe um jogador com esse nick para ser o denunciante.");
		
	AgendarCadeia(PlayerName[playerid], jailedPlayer, denunciator, reason);

	return 1;
}

CMD:cadeia(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ESTAGIARIO)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_cadeia;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_cadeia:
	new idplayer, reason[64], denunciator[MAX_PLAYER_NAME];
	if (sscanf(params, "us[24]s[15]", idplayer, denunciator, reason)) {
		SendClientMessage(playerid, -1, "Modo de uso: /cadeia (nick do jogador) (nick do denunciante) (motivo)");
		SendClientMessage(playerid, -1, "Tempo: O tempo de cadeia é calculado automaticamente.");
		return 1;
	}

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (strlen(reason) < 3 || strlen(reason) > 14) 
		return SendClientMessage(playerid, -1, "O motivo deve conter de 3 a 14 caracteres, crie abreviação.");

	if ((idplayer == playerid) && Admin_GetNivel(playerid) < MASTER) 
		return SendClientMessage(playerid, -1, "Você não pode se auto prender.");

	/*if (Admin_GetNivel(idplayer) > MASTER) {
		return SendClientMessage(playerid, -1, "Você não pode prender um Gerente+");
	}*/

	Cadeia(PlayerName[playerid], idplayer, denunciator, reason);

	return 1;
}

CMD:retirarcadeia(playerid, params[])
{
	if (!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Você não está logado.");

	if (Admin_GetNivel(playerid) < MODERADOR) 
		return SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_retirarcadeia;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_retirarcadeia:
	new idplayer, rprisao, result[64];
	if (sscanf(params, "uds[64]", idplayer, rprisao, result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /retirarcadeia (id do jogador) (retirar prisões admin?) (motivo)");

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (rprisao < 0 || rprisao > 1)
		return SendClientMessage(playerid, -1, "Retirar prisões administrativas: ('1' para SIM | '0' para NÃO)");

	if (rprisao == 1) {
		new prisoes = Player_GetJailsAdmin(idplayer);
	
		if (prisoes) {
			prisoes--;
			Player_SetJailsAdmin(idplayer, prisoes);
		}
	}

	Player_SetCadeia(idplayer, 0, 0, "Nenhum", "Nenhum", 998);
	HidePlayerTimer(idplayer);
	SpawnPlayer(idplayer);

	new string[128];

	format(string, sizeof(string), "[Cadeia admin] %s, %s retirou %s da cadeia, motivo: %s", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer], result);
	SendClientMessageToAll(COLOR_LIGHTRED, string);
	
	server_log("cadeia", string);

	return 1;
}

CMD:verlogs(playerid) 
{
	if (!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Você não está logado.");

	if (Admin_GetNivel(playerid) < ADMINISTRADOR)
	    return SendClientMessage(playerid, -1, "Você não tem permissão para usar este comando !");

	if (Founders_GetList(playerid)) {
		goto skip_founder_verlogs;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");
	
	skip_founder_verlogs:
	MEGAString[0] = EOS;

	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Casas\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Empresas\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Fazendas\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Cash\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Conexões\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Ban\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Kick\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Cadeia\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Anuncios\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Contratos\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Criar Admin\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Criar Helper\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Limpar Admin\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Limpar Helper\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Senha Admin\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}GMX\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Líderes\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Atendimentos\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Xiters\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Sms\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Mudar Nick\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Chat Admin\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Comandos Admin\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}/anorg\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}/su\n");
	strcat(MEGAString, "{00FFFF}Ver logs: {FFFFFF}Chat Gestor\n");

	ShowPlayerDialog(playerid, 8714, DIALOG_STYLE_LIST, "Escolha uma das opções", MEGAString, "Visualizar", "Fechar");

	return 1;
}

CMD:setarp(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MODERADOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_setar;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_setar:
	foreach(new x : Player) {
	
		if (x == playerid || Admin_GetNivel(x) > MASTER || Founders_GetList(x)) 
			continue;

		if (ProxDetectorS(30.0, playerid, x)) 
		{
			SpawnPlayer(x);
		
			SendMsgF(x, -1, "Você foi setado para sua HQ pelo administrador %s.", PlayerName[playerid]);
			PlayerPlaySound(x, 1068, 0.0, 0.0, 0.0);

			defer stopMusic(x);
		}
	}

	new 
		MapZone:zone = GetPlayerMapZone(playerid),
		zone_name[MAX_MAP_ZONE_NAME],
		string[75]
	;

	GetMapZoneName(zone, zone_name);

	format(string, sizeof string, "AdmAviso: %s setou todos jogadores próximos á %s.", PlayerName[playerid], zone_name);
	Staff_ChatToAll(COLOR_LIGHTRED, string);

	server_log("admin", string);

	return 1;
}

CMD:infoban(playerid, params[]) 
{
	if (Admin_GetNivel(playerid) < ESTAGIARIO)
	    return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_infoban;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_infoban:

	if (sscanf(params, "s[24]", params))
		return SendClientMessage(playerid, -1, "Modo de uso: /infoban (nick do jogador)");

	show_nick_ban(playerid, params);

	return 1;
}

CMD:infobanip(playerid, params[]) 
{
	if (Admin_GetNivel(playerid) < ESTAGIARIO)
	    return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_infobanip;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_infobanip:

	if (sscanf(params, "s[24]", params))
		return SendClientMessage(playerid, -1, "Modo de uso: /infobanip (IP)");

	show_ip_ban(playerid, params);

	return 1;
}

CMD:vercarteira(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ESTAGIARIO)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_vercarteira;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_vercarteira:

	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /vercarteira (id do jogador)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");
	
	ShowStats(playerid, idplayer);
	return 1;
}

CMD:teamviewer(playerid, params[])
{
	if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Voce não esta autorizado a usar este comando!");

	new string[128];

	if (GetPVarInt(playerid, "varTeamViewer"))
	{
		SetPVarInt(playerid, "varTeamViewer", 0);

		format(string, sizeof(string), "[TeamViewer]: O %s, %s não está mais passando TeamViewer (TV).", Staff_GetPositionName(playerid), PlayerName[playerid]);
		SendClientMessageToAll(0xAAAAAAFF, string);

		return true;
	}

	SetPVarInt(playerid, "varTeamViewer", 1);

	format(string, sizeof(string), "[TeamViewer]: O %s, %s agora está ausente, pois está passando TeamViewer (TV).", Staff_GetPositionName(playerid), PlayerName[playerid]);
	SendClientMessageToAll(0xAAAAAAFF, string);

	return true;
}

CMD:darfome(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ADMINISTRADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_darfome;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_darfome:
	new idplayer, Float:value;
	if (sscanf(params, "uf", idplayer, value))
		return SendClientMessage(playerid, -1, "Modo de uso: /darfome (id) (valor de 1 á 100)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "Esse jogador não está conectado/logado no servidor.");

	if (value < 1.0 || value > 100.0)
		return SendClientMessage(playerid, -1, "O valor deve estar de 1 á 100.");

	Player_SetFome(idplayer, value);

	new string[128];

	format(string, sizeof(string), "AdmAviso: %s, %s setou %.0f de fome para %s (%d).", Staff_GetPositionName(playerid), PlayerName[playerid], value, PlayerName[idplayer], idplayer);
	Staff_ChatToAll(COLOR_LIGHTRED, string);

	return 1;
}

CMD:darsede(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ADMINISTRADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_darsede;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_darsede:
	new idplayer, Float:value;
	if (sscanf(params, "uf", idplayer, value))
		return SendClientMessage(playerid, -1, "Modo de uso: /darfome (id) (valor de 1 á 100)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "Esse jogador não está conectado/logado no servidor.");

	if (value < 1.0 || value > 100.0)
		return SendClientMessage(playerid, -1, "O valor deve estar de 1 á 100.");

	Player_SetSede(idplayer, value);

	new string[128];

	format(string, sizeof(string), "AdmAviso: %s, %s setou %.0f de sede para %s (%d).", Staff_GetPositionName(playerid), PlayerName[playerid], value, PlayerName[idplayer], idplayer);
	Staff_ChatToAll(COLOR_LIGHTRED, string);

	return 1;
}

CMD:darvida(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ADMINISTRADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_darvida;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_darvida:
	new idplayer, Float:value;
	if (sscanf(params, "uf", idplayer, value))
		return SendClientMessage(playerid, -1, "Modo de uso: /darvida (id) (valor de 1 á 100)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "Esse jogador não está conectado/logado no servidor.");

	if (value < 1.0 || value > 100.0)
		return SendClientMessage(playerid, -1, "O valor deve estar de 1 á 100.");

	SetPlayerHealth(idplayer, value);

	new string[128];

	format(string, sizeof(string), "AdmAviso: %s, %s setou %.0f de saúde (HP) para %s (%d).", Staff_GetPositionName(playerid), PlayerName[playerid], value, PlayerName[idplayer], idplayer);
	Staff_ChatToAll(COLOR_LIGHTRED, string);

	return 1;
}

CMD:matar(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ADMINISTRADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_matar;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_matar:
	new idplayer;

	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /matar (id do jogador)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "Esse jogador não está conectado/logado no servidor.");

	if (Founders_GetList(idplayer))
		return SendClientMessage(playerid, -1, "Você não pode matar este administrador.");

	if (Founders_GetList(playerid))
		goto skip_founder_matardois;

	if (Admin_GetNivel(idplayer) && Helper_GetNivel(idplayer))
		return SendClientMessage(playerid, -1, "Você não pode matar um Administrador/Helper.");

	skip_founder_matardois:

	SetPlayerHealth(idplayer, 0);

	new string[128];

	format(string, sizeof(string), "AdmAviso: %s, %s matou o jogador %s.", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer]);
	Staff_ChatToAll(COLOR_LIGHTRED, string);

	format(string, sizeof(string), "Você foi morto forçadamente pelo %s, %s.", Staff_GetPositionName(playerid), PlayerName[playerid]);
	SendClientMessage(idplayer, COLOR_GRAD, string);

	format(string, sizeof(string), "%s, %s matou o jogador %s", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer]);
	server_log("kill", string);

	return 1;
}

CMD:darcolete(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ADMINISTRADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_darcolete;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_darcolete:
	new idplayer, Float:value;
	if (sscanf(params, "uf", idplayer, value))
		return SendClientMessage(playerid, -1, "Modo de uso: /darcolete (id) (valor de 1 á 100)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "Esse jogador não está conectado/logado no servidor.");

	if (value < 1.0 || value > 100.0)
		return SendClientMessage(playerid, -1, "O valor deve estar de 1 á 100.");

	SetPlayerArmour(idplayer, value);

	new string[128];

	format(string, sizeof(string), "AdmAviso: %s, %s setou %.0f de colete para %s (%d).", Staff_GetPositionName(playerid), PlayerName[playerid], value, PlayerName[idplayer], idplayer);
	Staff_ChatToAll(COLOR_LIGHTRED, string);

	return 1;
}

CMD:marcarmapa(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MODERADOR)
		return SendClientMessage(playerid, -1, "Você não pode usar este comando!");

	if (Founders_GetList(playerid)) {
		goto skip_founder_marcarmapa;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

	skip_founder_marcarmapa:
	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Use: /marcarmapa [id]");

	if (Player_Logado(idplayer))
	{
		SendMsgF(playerid, COLOR_LIGHTBLUE, "Modo mapa ativo. Marque no mapa o local que deseja marcar para o jogador %s.", PlayerName[idplayer]);
		SetPVarInt(playerid, "mapaMarcar", 1);
		SetPVarInt(playerid, "mapaPlayer", idplayer);
	}
	return 1;
}

CMD:dn(playerid, params[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new 
		Float:slx, 
		Float:sly, 
		Float:slz
	;

	GetPlayerPos(playerid, slx, sly, slz);
	SetPlayerPos(playerid, slx, sly, slz - 2.0);

	return 1;
}

CMD:up(playerid, params[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");
		
	new 
		Float:slx, Float:sly, Float:slz;

	GetPlayerPos(playerid, slx, sly, slz);

	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		new tmpcar = GetPlayerVehicleID(playerid);
		GetVehiclePos(tmpcar, slx, sly, slz);
		SetVehiclePos(tmpcar, slx, sly, slz + 5.0);
	} else {
		SetPlayerPos(playerid, slx, sly, slz + 5.0);
	}
	return 1;
}

CMD:mup(playerid)
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new 
		Float:slx, Float:sly, Float:slz;

	GetPlayerPos(playerid, slx, sly, slz);

	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		new tmpcar = 
			GetPlayerVehicleID(playerid);

		GetVehiclePos(tmpcar, slx, sly, slz);
		SetVehiclePos(tmpcar, slx, sly, slz + 30.0);
	} else {
		SetPlayerPos(playerid, slx, sly, slz + 30.0);
	}
	return 1;
}

CMD:lt(playerid)
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new 
		Float:slx, Float:sly, Float:slz;

	GetPlayerPos(playerid, slx, sly, slz);
	SetPlayerPos(playerid, slx, sly + 2.0, slz);

	return 1;
}


CMD:rt(playerid)
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new 
		Float:slx, Float:sly, Float:slz;

	GetPlayerPos(playerid, slx, sly, slz);
	SetPlayerPos(playerid, slx + 2.0, sly, slz);

	return 1;
}

CMD:voar(playerid, params[])
{
    if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    if (!Staff_GetWorking(playerid) && Admin_GetNivel(playerid) < MODERADOR) 
		return SendClientMessage(playerid, -1, "Você não pode usar este comando em modo jogo.");

	new 
		Float:pX, Float:pY, Float:pZ;

	GetPlayerPos(playerid, pX, pY, pZ);
	GetXYInFrontOfPlayer(playerid, pX, pY, 20.0);
	SetPlayerPos(playerid, pX, pY, pZ + 12.0);

	return 1;
}

CMD:infoconta(playerid, params[]) 
{
	if (!Admin_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new nick[MAX_PLAYER_NAME];
	if (sscanf(params, "s[24]", nick))
		return SendClientMessage(playerid, -1, "Modo de uso: /infoconta (nick)");

	new query[185];
	mysql_format(MySQL_Handle, query, sizeof query, "SELECT * FROM `player` WHERE nome = '%e' LIMIT 1", nick);
	mysql_tquery(MySQL_Handle, query, "OnInfoConta", "i", playerid);

	ShowLoadingDialog(playerid);

	return 1;
}

CMD:orelhagrandeorg(playerid, params[])
{
	if (Admin_GetNivel(playerid) < SUPERVISOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new orelhagorg = GetPVarInt(playerid, "OrelhaGrandeOrg");

	if (!orelhagorg) {
		SetPVarInt(playerid, "OrelhaGrandeOrg", 1);
	} else {
		SetPVarInt(playerid, "OrelhaGrandeOrg", 0);
	}
	SendMsgF(playerid, COLOR_LIGHTGREEN, "Você %s o modo 'Orelha Grande: Organizações'", orelhagorg ? "desativou" : "ativou");

	return 1;
}

// -----------------------------------------------------------------------------------------------------------
// Estagiários:

CMD:verkills(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ESTAGIARIO) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /verkills (id do jogador)");

	if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	showLogKills(idPlayer, playerid);

	return true;
}

CMD:ls(playerid)
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_teleportls;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está trabalhando.");

	skip_founder_teleportls:

	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		new vehicleID = GetPlayerVehicleID(playerid);
		SetVehiclePos(vehicleID, 1731.2814,-2242.6458,13.2438);
		SetVehicleZAngle(vehicleID, 180.0684);
	} else {
		SetPlayerPos(playerid, 1697.1370,-2242.9248,13.5396);
		SetPlayerFacingAngle(playerid, 89.7928);
	}
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);

	SendClientMessage(playerid, COLOR_LIGHTGREEN, "Você se teleportou até Los Santos.");

	return 1;
}

CMD:sf(playerid)
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_teleportsf;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está trabalhando.");

	skip_founder_teleportsf:

	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		new vehicleID = GetPlayerVehicleID(playerid);
		SetVehiclePos(vehicleID, -2724.3208, -314.6010, 7.1862);
	} else {
		SetPlayerPos(playerid, -2724.3208,-314.6010,7.1862);
	}
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);

	SendClientMessage(playerid, COLOR_LIGHTGREEN, "Você se teleportou até San Fierro.");

	return 1;
}

CMD:lv(playerid, params[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_teleportlv;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está trabalhando.");

	skip_founder_teleportlv:	

	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		new vehicleID = GetPlayerVehicleID(playerid);
		SetVehiclePos(vehicleID, 1699.2, 1435.1, 10.7);
	} else {
		SetPlayerPos(playerid, 1699.2, 1435.1, 10.7);
	}
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);

	SendClientMessage(playerid, COLOR_LIGHTGREEN, "Você se teleportou até Las Venturas.");

	return 1;
}

CMD:fim(playerid, params[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_teleportarfim;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está trabalhando.");

	skip_founder_teleportarfim:
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		new vehicleID = GetPlayerVehicleID(playerid);
		SetVehiclePos(vehicleID, -2415.3999, 2219.0083, 4.9844);
	} else {
		SetPlayerPos(playerid, -2415.3999, 2219.0083, 4.9844), SetPlayerFacingAngle(playerid, 226.0);
	}
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);

	SendClientMessage(playerid, COLOR_LIGHTGREEN, "Você se teleportou até o Fim.");

	return 1;
}

CMD:irhospital(playerid, params[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_irhospital;
	}

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está trabalhando.");

	skip_founder_irhospital:
	SetPlayerPos(playerid, 1173.4684, -1328.2646, -44.2763);
	SetPlayerInterior(playerid, 10);
	SetPlayerVirtualWorld(playerid, 0);

	SendClientMessage(playerid, COLOR_LIGHTGREEN, "Você se teleportou até o Hospital.");

	return 1;
}

CMD:orelhagrande(playerid, params[])
{
	if (!Admin_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!SpyGet_ChatLocal(playerid)) {
		SpySet_ChatLocal(playerid, true);
	} else {
		SpySet_ChatLocal(playerid, false);
	}

	SendMsgF(playerid, COLOR_LIGHTGREEN, "Você %s o modo espião para: Chat local.", SpyGet_ChatLocal(playerid) ? "ativou" : "desativou");

	return 1;
}

CMD:online(playerid, params[])
{
	new on_string[200];

	if (Admin_GetNivel(playerid) < MASTER) 
		return SendClientMessage(playerid, -1, "Você não tem permissão para usar esse comando.");

	new AndroidPlayer, PCPlayer;

	foreach(new i : Character)
	{
		if (IsAndroidPlayer(i)) AndroidPlayer++;
		else PCPlayer++;
	}

	format(on_string, sizeof(on_string), "SERVIDOR: {FFFFFF}(%d/%d) onlines (Android: %d | PC: %d).", ContarJogadores(), (MAX_PLAYERS - Iter_Count(Bot)), AndroidPlayer, PCPlayer);
	SendClientMessageToAll(COLOR_LIGHTBLUE, on_string);

	#if defined _inc_discord_connector
		format(on_string, sizeof(on_string), ":video_game: **"SERVER_NAME"** Estamos com %d/%d jogadores online!. Curta nossa página: "SERVER_FACEBOOK"", ContarJogadores(), (MAX_PLAYERS - Iter_Count(Bot)));
		Discord_SendMessage(on_string, Channel_BatePapo);
	#endif

	return true;
}

//------------------------------------------------------------------------------------------------------

stock CancelPlayerSpectate(playerid)
{
	TogglePlayerSpectating(playerid, false);

	SpectadorInfo[playerid][spectadorID] = INVALID_PLAYER_ID;

	SendClientMessage(playerid, COLOR_SAMP, "Você saiu de modo /tv.");
	PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);

	PlayerTextDrawHide(playerid, spectadorText[playerid]);

	SpawnPlayer(playerid);

	return 1;
}

CMD:tv(playerid, params[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer;
  	// if (sscanf(params, "u", idplayer)) {
	// 	if (GetPlayerSpectateType(playerid)) {
	// 		TogglePlayerSpectating(playerid, false);

	// 		PlayerTextDrawHide(playerid, spectadorText[playerid]);

	// 		GameTextForPlayer(playerid, "~w~                TV~n~~r~~h~                DESCONECTADO", 3500, 6);
	// 		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);

	// 		SpawnPlayer(playerid);
	// 	}
	// 	return SendClientMessage(playerid, -1, "Modo de uso: /tv (id do jogador) | Use 'off' para sair do modo TV.");
	// }
	if(sscanf(params, "u", idplayer))
	{
		if (SpectadorInfo[playerid][spectadorID] != INVALID_PLAYER_ID)
		{
		    CancelPlayerSpectate(playerid);
			return true;
		}
		return SendClientMessage(playerid, -1, "Modo de uso: /tv (id do jogador) | Use 'off' para sair do modo TV.");
	}

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (Founders_GetList(playerid))
		goto skip_founder_tv;

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	if (Admin_GetNivel(idplayer) > PROGRAMADOR)
		return SendClientMessage(playerid, -1, "Você não pode observar um programador.");

	skip_founder_tv:

	if (Admin_GetNivel(playerid) >= SUPERVISOR)
		goto skip_admin_tv;

	if (Admin_GetNivel(playerid) < Admin_GetNivel(idplayer))
		return SendClientMessage(playerid, -1, "Você não pode usar o /tv em um cargo maior que o seu.");

	skip_admin_tv:

	if (SpectadorInfo[idplayer][spectadorID] != INVALID_PLAYER_ID) 
		return SendClientMessage(playerid, -1, "O administrador está em modo tv.");

	new 
		world = GetPlayerVirtualWorld(idplayer),
		interior = GetPlayerInterior(idplayer),
		vehicleid = GetPlayerVehicleID(idplayer);

	TogglePlayerSpectating(playerid, true);

	if (IsPlayerInAnyVehicle(idplayer)) 
		PlayerSpectateVehicle(playerid, vehicleid);
	else 
		PlayerSpectatePlayer(playerid, idplayer);

	SetPlayerInterior(playerid, interior);
	SetPlayerVirtualWorld(playerid, world);

	SpectadorInfo[playerid][spectadorID] = idplayer;

	new string[128];
	if (Admin_GetNivel(playerid) < DONO) {
		format(string, sizeof(string), "Admin: %s está de /tv no jogador: %s (%d).", PlayerName[playerid], PlayerName[idplayer], idplayer);
		Staff_ChatToAll(COLOR_LIGHTRED, string, MASTER);
	}
	format(string, sizeof(string), "Você entrou de modo TV em: %s (%d) (Use: /tv para sair)", PlayerName[idplayer], idplayer);
	SendClientMessage(playerid, COLOR_GREEN, string);

	return 1;
}

CMD:distribuircontratos(playerid, params[]) {

	if (Dev_GetNivel(playerid) < DEV_ALPHA) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new org, players, valorMin, valorMax;

	if (sscanf(params, "dddd", org, players, valorMin, valorMax)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /distribuircontratos (org) (players) (valor mínimo) (valor máximo)");

	else if(org != 8 && org != 22)
		return SendClientMessage(playerid, -1, "ORG inválida");

	else if(valorMin > valorMax || valorMax < valorMin) 
		return SendClientMessage(playerid, -1, "O valor mínimo não pode ser maior que o valor máximo.");

	else if(players < 0 || players > MAX_PLAYERS)
		return SendClientMessage(playerid, -1, "Quantidade de jogadores inválida");

	else if(valorMin < 0 || valorMax < 0)
		return SendClientMessage(playerid, -1, "Valores inválidos. Reveja!");

	new Iterator:IterPlayers<MAX_PLAYERS>;
    new string[128];

	new count = 0,
		total = 0,
		totalResp = 0;

    foreach(new x : Player)
	{
        if (Player_Logado(x) && GetPlayerOrg(x) != 8 && GetPlayerOrg(x) != 22 && PlayerInfo[x][pConnectTime] > 10)
		{
			if ((Admin_GetNivel(x) || Staff_GetWorking(x) && Staff_GetWorking(x)) || 
				PlayerInfo[x][pHeadValue] > 0 || PlayerInfo[x][pHeadValueT] > 0 || GetPlayerVirtualWorld(x) == 10061) 
				continue;

			Iter_Add(IterPlayers, x);
			count ++;
        }
    }

    if (Iter_Count(IterPlayers))
	{
		foreach(new x : IterPlayers) {
			if(count == 0 || players == 0)
				break;

			new valor = valorMin + random(valorMax - valorMin);
			total += valor;

			if(org == 22) {
				PlayerInfo[x][pHeadValueT] += valor;
				PlayerInfo[x][pHeadRespectT] = random(3);
				format(string, sizeof(string), "(Agência): Contrato automático disponível em %s(%d), valor: $%s e %d respeitos.",PlayerName[x], x, getFormatText(valor), PlayerInfo[x][pHeadRespectT]);
				SendMembersMessage(22, COLOR_YELLOW, string);

				totalResp += PlayerInfo[x][pHeadRespectT];
			}

			else if(org == 8) {
				PlayerInfo[x][pHeadValue] += valor;
				PlayerInfo[x][pHeadRespect] = random(3);
				format(string, sizeof(string), "(Agência): Contrato automático disponível em %s(%d), valor: $%s e %d respeitos.",PlayerName[x], x, getFormatText(valor), PlayerInfo[x][pHeadRespect]);
				SendMembersMessage(8, COLOR_YELLOW, string);

				totalResp += PlayerInfo[x][pHeadRespect];
			}

			count --;
			players --;
		}
    }
	if(total == 0) {
		SendClientMessage(playerid, COLOR_WHITE, "Insuficiência de jogadores para distribuir contratos.");
	}
	else {
		removerDinheiroGoverno(total);
		SendMsgF(playerid, COLOR_LIGHTGREEN, "Foram distribuídos %d contratos e um valor total de $%s e %d respeitos.", Iter_Count(IterPlayers), getFormatText(total), totalResp);

		format(string, sizeof(string), "SERVIDOR: %s, %s distribuiu contratos automáticos para organização %s.", Staff_GetPositionName(playerid), PlayerName[playerid], GetOrgName(org));
		SendClientMessageToAll(COLOR_LIGHTRED, string);
	}
	return 1;
}

CMD:sethora(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MASTER) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new setarHora,
		string[86];

	if (sscanf(params, "d", setarHora)) return SendClientMessage(playerid, -1, "Modo de uso: /sethora (hora do dia | 0 - 23)");

	SetWorldTime(setarHora);
	format(string, sizeof(string), "AdmAviso: %s alterou o horário do servidor para %d horas.", PlayerName[playerid], setarHora);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

	return true;
}

CMD:iniciarloteria(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ADMINISTRADOR) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new string[128], rand = random(99) + 1;

	format(string, sizeof(string), "Loteria: A loteria iniciou-se."); OOCNews(-1, string);

	return Lotto(rand);
}

CMD:editar(playerid, params[])
{
	if (Admin_GetNivel(playerid) < SUB_DONO)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new namePlayer[MAX_PLAYER_NAME], stats, value;
	if (sscanf(params, "s[24]dd", namePlayer, stats, value)) {
		SendClientMessage(playerid, -1, "Modo de uso: /editar (nome do jogador) (id do status) (quantidade)");
		SendClientMessage(playerid, COLOR_GRAD, "1. Level				|7. Cash		|13. Contratos   	|19. Skill Detetive");
		SendClientMessage(playerid, COLOR_GRAD, "2. Respeitos				|8. Nível Sócio		|14. Apreensoes 	|20. Skill Advogados");
		SendClientMessage(playerid, COLOR_GRAD, "3. Horas Jogadas		|9. Assassinatos			|15. Nº celular 		|21. Avisos");
		SendClientMessage(playerid, COLOR_GRAD, "4. Dinheiro        |10. Mortes		|16. Maconha		|22. Prisoes Admin");
		SendClientMessage(playerid, COLOR_GRAD, "5. Dinheiro Banco      |11. Skin		|17. Cocaina		|23. Trocas de nick");
		SendClientMessage(playerid, COLOR_GRAD, "6. Ouros  	|12. Sexo       |18. Crack       |21. Crack");
		return true;
	}

	if (Player_Edit(playerid, DCC_INVALID_USER, namePlayer, EditPlayer:stats, value)) {
        SendClientMessage(playerid, -1, "A edição do jogador foi um sucesso!");
    } else {
        SendClientMessage(playerid, -1, "A edição do jogador houve uma falha!");
    }
	return 1;
}

CMD:tirarsu(playerid, params[])
{
	if (Admin_GetNivel(playerid) >= MASTER)
	{
		new idplayer;
		if(sscanf(params, "u", idplayer))
		{
			SendClientMessage(playerid, -1, "Use: (/tirarsu) [id]");
			return true;
		}

		if (Founders_GetList(playerid)) {
			goto skip_founder_tirarsu;
		}

		if(!Staff_GetWorking(playerid))
			return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

		skip_founder_tirarsu:
		if(IsPlayerConnected(idplayer))
		{
			if (Admin_GetNivel(playerid) < ESTAGIARIO)
				return SendClientMessage(playerid, -1, "Você só pode usar este comando em admins !");

			Player_SetWanted(idplayer, 0);

			new string[90];
			format(string, sizeof(string), "Admin: %s limpou os níveis de procurado de %s",PlayerName[playerid], PlayerName[idplayer]);
			Staff_ChatToAll(COLOR_LIGHTRED, string, DONO);
			server_log("limparsu", string);
			return true;
		}
		else
		{
			SendClientMessage(playerid, -1, "Esse jogador não está conectado.");
			return true;
		}
	}
	return true;
}

CMD:ip(playerid, params[])
{
	if (!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Você não está logado.");

	if (Admin_GetNivel(playerid) < MASTER) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!Staff_GetWorking(playerid) && Admin_GetNivel(playerid) < MASTER) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /ip (id do jogador)");

	if (!IsPlayerConnected(idPlayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	new string[92];

	if (Founders_GetList(idPlayer))
	{
		format(string, sizeof(string), "AdmCmd: %s, %s está tentando pegar seu IP.", Staff_GetPositionName(playerid), PlayerName[playerid]);
		SendClientMessage(idPlayer, COLOR_LIGHTRED, string);

		format(string, sizeof(string), "Você não pode pegar o IP deste administrador.");
		SendClientMessage(playerid, COLOR_WHITE, string);
	}
	else {
		format(string, sizeof(string), "-| Jogador %s - IP: %s |-", PlayerName[idPlayer], PlayerIP[idPlayer]);
		SendClientMessage(playerid,COLOR_LIGHTBLUE, string);
	}
	
	return true;
}

new Float:player_pos[4];

timer SetLocalAnterior[1500](playerid)
{
	Player_SetMuted(playerid, false);

	SetPlayerPos(playerid, player_pos[0], player_pos[1], player_pos[2]);
	SetPlayerFacingAngle(playerid, player_pos[3]);
}

CMD:desbugar(playerid, params[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid))) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (gettime() < GetPVarInt(playerid, #varFlood_desbugplayer)) 
		return SendClientMessage(playerid, -1, "Você não pode usar este comando com tanta frequencia");

	new idplayer;
	if (sscanf(params, "u", idplayer)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /desbugar (id do jogador)");

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	// SyncPlayer(idplayer);
	PlayerPlaySound(idplayer, 1068, 0.0, 0.0, 0.0);

	GetPlayerPos(idplayer, player_pos[0], player_pos[1], player_pos[2]);
	GetPlayerFacingAngle(idplayer, player_pos[3]);

	SpawnPlayer(idplayer);
	defer SetLocalAnterior(idplayer);
	defer stopMusic(idplayer);

	new string[128];
	format(string, sizeof(string), "AdmAviso: %s, %s desbugou o jogador %s", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer]);
	Staff_ChatToAll(COLOR_LIGHTRED, string);

	return SetPVarInt(playerid, #varFlood_desbugplayer, gettime() + 2);
}

//----------------------------------[Comandos Setar]------------------------------------------------
CMD:setemprego(playerid, params[])
{
	new para1, jobid;
	if(sscanf(params, "ud", para1, jobid))
	{
		SendClientMessage(playerid, -1, "Use: /setemprego [playerid/ParteDoNome] [empregoid)]");
		return true;
	}
	if (Admin_GetNivel(playerid) >= MASTER)
	{
		if (Founders_GetList(playerid)) {
			goto skip_founder_setemprego;
		}
		if(!Staff_GetWorking(playerid))
			return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

		skip_founder_setemprego:
		if(IsPlayerConnected(para1))
		{
			if(para1 != INVALID_PLAYER_ID)
			{
				PlayerInfo[para1][pEmprego] = jobid;
				SendMsgF(playerid, COLOR_LIGHTBLUE, "Você setou o emprego de %s [%d] para o jogador %s.", GetJobName(jobid), jobid, PlayerName[para1]);
			}
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não pode usar este comando!");
	}
	return true;
}

CMD:avorg(playerid, params[])
{
	if(Admin_GetNivel(playerid) >= SUPERVISOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando");

	new texto[128], orgid;

	if (sscanf(params, "ds[128]", orgid, texto)) return SendClientMessage(playerid, -1, "Modo de uso: /avorg (id da organização) (texto)");

	if (orgid < 1 || orgid > 33) return SendClientMessage(playerid, -1, "A organização precisa estar entre 1 a 33.");

	new string[144];

	foreach(new x : Player)
	{
		if (GetPlayerOrg(x) == orgid || x == playerid)
		{
			format(string, sizeof string, "× × {F856E8}AVISO ADMINISTRATIVO | PARA A ORGANIZAÇÃO: %s {FFFFFF} × ×", GetOrgName(orgid));
			SendClientMessage(x, -1, string);

			format(string, sizeof(string), "%s, {F856E8}%s{FFFFFF}: %s", Staff_GetPositionName(playerid), PlayerName[playerid], texto);
			SendClientMessage(x, -1, string);
		}
	}
	return true;
}

CMD:limparchat(playerid, result[])
{
	if(!Admin_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não é um administrador!");

	if(isnull(result))
		return SendClientMessage(playerid, -1, "Use: /limparchat [motivo]");

	for(new i; i < 100; ++i)
	{
		SendClientMessageToAll(-1, " ");
	}
	new string[128];
	format(string, sizeof(string), "O admin %s limpou o chat, motivo: %s", PlayerName[playerid], result);
	SendClientMessageToAll(-1, string);
	return true;
}

//----------------------------------[Wisper]-----------------------------------------------

CMD:esconderijo(playerid, params[])
{
	if (Admin_GetNivel(playerid))
	{
		if (!Staff_GetWorking(playerid))
		{
			SendClientMessage(playerid, -1, "Você não está em modo Admin USE: /jogar");
			return true;
		}
		else
		{
			//SetPlayerPos(playerid, 1783.7594, -1775.9401, 1057.0547); Antigo mapa do esconderijo mapeado
			SetPlayerPos(playerid, 1407.7523,3.1782,1201.0270); // Esconderijo do Play Start
			SetPlayerInterior(playerid, 3);
		}
		SendClientMessage(playerid, COLOR_GRAD, "   Você Foi Teleportado!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando!");
	}
	return true;
}

CMD:esconderijo2(playerid, params[])
{
	if (Admin_GetNivel(playerid))
	{
		if (!Staff_GetWorking(playerid))
		{
			SendClientMessage(playerid, -1, "Você não está em modo Admin USE: /jogar");
			return true;
		}
		else
		{
			SetPlayerPos(playerid, 1783.7594, -1775.9401, 1057.0547);
		}
		SendClientMessage(playerid, COLOR_GRAD, "   Você Foi Teleportado!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando!");
	}
	return true;
}

CMD:lbc(playerid, params[])
{
	if (Admin_GetNivel(playerid) >= MODERADOR)
	{
		if (!Staff_GetWorking(playerid))
		{
			SendClientMessage(playerid, -1, "Você não está em modo Admin USE: /jogar");
			return true;
		}
		else
		{
			SetPlayerPos(playerid, -783.4194,493.1628,1376.1953); // Liberty City
			SetPlayerInterior(playerid, 1);
			SetPlayerFacingAngle(playerid, 359.4467);
		}
		SendClientMessage(playerid, COLOR_GRAD, "   Você Foi Teleportado!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando!");
	}
	return true;
}

CMD:clube(playerid, params[])
{
	if (Admin_GetNivel(playerid) >= MODERADOR)
	{
		if (!Staff_GetWorking(playerid))
		{
			SendClientMessage(playerid, -1, "Você não está em modo Admin USE: /jogar");
			return true;
		}
		else
		{
			SetPlayerPos(playerid, -2640.0386,1406.6324,906.4609); // Clube do Jizzy
			SetPlayerInterior(playerid, 3);
			SetPlayerFacingAngle(playerid, 88.8185);
		}
		SendClientMessage(playerid, COLOR_GRAD, "   Você Foi Teleportado!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando!");
	}
	return true;
}

CMD:clubao(playerid, params[])
{
	if (Admin_GetNivel(playerid) >= ESTAGIARIO)
	{
		if (!Staff_GetWorking(playerid))
		{
			SendClientMessage(playerid, -1, "Você não está em modo Admin USE: /jogar");
			return true;
		}
		else
		{
			SetPlayerPos(playerid, 745.6591,1439.1343,1102.7031); // Clube da Putaria (HQ Staff)
			SetPlayerInterior(playerid, 6);
			SetPlayerFacingAngle(playerid, 0.1053);
			SetPlayerVirtualWorld(playerid, 1337);
		}
		SendClientMessage(playerid, COLOR_GRAD, "   Você Foi Teleportado!");
		SendClientMessage(playerid, COLOR_ADMIN, "Bem vindo à HQ Staff!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando!");
	}
	return true;
}

CMD:cdes(playerid, params[])
{
	if (Admin_GetNivel(playerid) >= MODERADOR)
	{
		if (!Staff_GetWorking(playerid))
		{
			SendClientMessage(playerid, -1, "Você não está em modo Admin USE: /jogar");
			return true;
		}
		else
		{
			SetPlayerPos(playerid, 2348.8606,-1180.8468,1027.9766); // Casa destruída
			SetPlayerInterior(playerid, 5);
			SetPlayerFacingAngle(playerid, 90.4158);
		}
		SendClientMessage(playerid, COLOR_GRAD, "   Você Foi Teleportado!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando!");
	}
	return true;
}

CMD:clubeam(playerid, params[])
{
	if (Admin_GetNivel(playerid) >= MASTER)
	{
		if (!Staff_GetWorking(playerid))
		{
			SendClientMessage(playerid, -1, "Você não está em modo Admin USE: /jogar");
			return true;
		}
		else
		{
			SetPlayerPos(playerid, 965.5512,-53.1500,1001.1246); // Clube Secreto do Alto Escalão
			SetPlayerInterior(playerid, 3);
			SetPlayerFacingAngle(playerid, 89.1064);
		}
		SendClientMessage(playerid, COLOR_GRAD, "   Você Foi Teleportado!");
		SendClientMessage(playerid, COLOR_PURPLE, "Bem-vindo Gestor! Lembre-se que este teleport é para Alto Escalão!");
		SendClientMessage(playerid, COLOR_PURPLE, "Poderá usar para conversar com certas pessoas, ou com outros membros do alto escalão.");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando!");
	}
	return true;
}

CMD:irestadio3(playerid, params[])
{
	if (Admin_GetNivel(playerid))
	{
		if (!Staff_GetWorking(playerid))
		{
			SendClientMessage(playerid, -1, "Você não está em modo Admin USE: /jogar");
			return true;
		}
		else
		{
			SetPlayerPos(playerid,-1464.7593,1558.5948,1052.5313); // Estádio de Motos LV
			SetPlayerInterior(playerid, 14);
			SetPlayerFacingAngle(playerid, 0.5858);
		}
		SendClientMessage(playerid, COLOR_GRAD, "   Você Foi Teleportado!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando!");
	}
	return true;
}

CMD:onibus(playerid, params[])
{
	if(Admin_GetNivel(playerid) >= ADMINISTRADOR)
	{
		if(!Staff_GetWorking(playerid))
			return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, 1759.2711,-1849.1093,13.5781);
			LinkVehicleToInterior(tmpcar, 0);
		}
		else
		{
			SetPlayerPos(playerid, 1759.2711,-1849.1093,13.5781);
		}
		SendClientMessage(playerid, COLOR_GRAD, "Você foi teleportado pelo Admin!");
		SetPlayerInterior(playerid, 0);
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está autorizado a usar o comando!");
	}
	return true;
}

CMD:entrarcarro(playerid, params[])
{
	new testcar;
	if(sscanf(params, "d", testcar))
	{
		SendClientMessage(playerid, -1, "Use: /entrarcarro [carro id]");
		return true;
	}
	if (Admin_GetNivel(playerid) >= ADMINISTRADOR)
	{
		if (Founders_GetList(playerid)) {
			goto skip_founder_entrarcarro;
		}
		if(!Staff_GetWorking(playerid))
			return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

		skip_founder_entrarcarro:
		PutPlayerInVehicle(playerid, testcar, 1);
		SendClientMessage(playerid, COLOR_GRAD, "Você foi teleportado pelo Admin!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
	}
	return true;
}

CMD:ircarro(playerid, params[])
{
	new testcar;
	if(sscanf(params, "d", testcar))
	{
		SendClientMessage(playerid, -1, "Use: /ircarro [carro id]");
		return true;
	}
	if (Admin_GetNivel(playerid) >= ADMINISTRADOR)
	{
		if (Founders_GetList(playerid)) {
			goto skip_founder_ircarro;
		}
		if (!Staff_GetWorking(playerid))
		{
			SendClientMessage(playerid, -1, "Você não está em modo Admin USE: /jogar");
			return true;
		}
		skip_founder_ircarro:
		new Float:cwx2,Float:cwy2,Float:cwz2;
		GetVehiclePos(testcar, cwx2, cwy2, cwz2);
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, cwx2, cwy2, cwz2);
			LinkVehicleToInterior(tmpcar, 0);
		}
		else
		{
			SetPlayerPos(playerid, cwx2, cwy2, cwz2);
		}
		SendClientMessage(playerid, COLOR_GRAD, "Você foi teleportado pelo Admin!");
		SetPlayerInterior(playerid, 0);
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
	}
	return true;
}
alias:ircarro("irveiculo")

CMD:mark(playerid, params[])
{
	if (Admin_GetNivel(playerid) >= ESTAGIARIO)
	{
		new Float:pos[3];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		SetPVarFloat(playerid, "DestX", pos[0]);
		SetPVarFloat(playerid, "DestY", pos[1]);
		SetPVarFloat(playerid, "DestZ", pos[2]);
		SetPVarInt(playerid, "DestInt", GetPlayerInterior(playerid));
		SetPVarInt(playerid, "DestWorld", GetPlayerVirtualWorld(playerid));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você marcou o local para o teleporte no /irmark");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
	}
	return true;
}

CMD:irmark(playerid, params[])
{
	if (Admin_GetNivel(playerid) >= ESTAGIARIO)
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, GetPVarFloat(playerid, "DestX"),GetPVarFloat(playerid, "DestY"),GetPVarFloat(playerid, "DestZ"));
			LinkVehicleToInterior(tmpcar, GetPVarInt(playerid, "DestInt"));
    		SetVehicleVirtualWorld(tmpcar, GetPVarInt(playerid, "DestWorld"));
		}
		else
		{
			SetPlayerPos(playerid, GetPVarFloat(playerid, "DestX"),GetPVarFloat(playerid, "DestY"),GetPVarFloat(playerid, "DestZ"));
		}
		SendClientMessage(playerid, COLOR_GRAD, "Você foi teleportado para onde você marcou!");
		SetPlayerInterior(playerid, GetPVarInt(playerid, "DestInt"));
		SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "DestWorld"));
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
	}
	return true;
}

CMD:irestadio(playerid, params[])
{
	if (Admin_GetNivel(playerid) >= ADMINISTRADOR)
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, -1435.75, -652.664, 1054.94);
			LinkVehicleToInterior(tmpcar, 0);
		}
		else
		{
			SetPlayerPos(playerid, -1435.75, -652.664, 1054.94);
		}
		SetPlayerInterior(playerid, 4);
		SendClientMessage(playerid, COLOR_GRAD, "Você foi teleportado pelo Admin!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
	}
	return true;
}

CMD:irevento(playerid, params[])
{
	if (!GetPVarInt(playerid, "conviteEvento")) return SendClientMessage(playerid, -1, "O convite para o evento já expirou!");

	if (Evento == 1) 
	{
		if (Player_GetJailed(playerid) != 0)
		{
			SendClientMessage(playerid, -1, "Você não pode ir ao evento pois está preso ou na arena de treinamento.");
			return true;
		}
		SetPlayerInterior(playerid, inta);
		SetPlayerVirtualWorld(playerid, vwa);
		SendClientMessage(playerid, 0xFFDEADFF, "Você compareceu ao evento!");
		SetPlayerPos(playerid,ex,ey,ez);

		BlockPlayerTempWeapons(playerid);

		ResetPlayerWeapons(playerid);

		SetPlayerArmour(playerid, 100), SetPlayerHealth(playerid, 100);

	} 
	else if (Evento == 2) 
	{

		if (Player_GetJailed(playerid) != 0)
		{
			SendClientMessage(playerid, -1, "Você não pode ir ao evento pois está preso ou na arena de treinamento.");
			return true;
		}
		SetPlayerInterior(playerid, inta);
		SetPlayerVirtualWorld(playerid, vwa);
		SendClientMessage(playerid, 0xFFDEADFF, "Você compareceu ao evento de DM!");
		SetPlayerPos(playerid,ex,ey,ez);

		BlockPlayerTempWeapons(playerid);
		ResetPlayerWeapons(playerid);

		SetPlayerHealth(playerid, 100.0);
		SetPlayerArmour(playerid, 100.0);

		GivePlayerWeapon(playerid, WEAPON_DEAGLE, 9999);
		GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 9999);
		GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 9999);
	}

	return 1;
}

CMD:irstad2(playerid, params[])
{
	if (Admin_GetNivel(playerid) >= ADMINISTRADOR)
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, -1376.5557,-743.2819,1051.6790);
			LinkVehicleToInterior(tmpcar, 0);
		}
		else
		{
			SetPlayerPos(playerid, -1376.5557,-743.2819,1051.6790);
		}
		SetPlayerInterior(playerid, 4);
		SendClientMessage(playerid, COLOR_GRAD, "Você foi teleportado pelo Admin!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
	}
	return true;
}

CMD:aviao(playerid, params[])
{
	if (Admin_GetNivel(playerid))
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, 1.71875, 30.4062, 1200.34); LinkVehicleToInterior(tmpcar, 0);
		}
		else
		{
			SetPlayerPos(playerid, 1.71875, 30.4062, 1200.34);
		}
		SetPlayerInterior(playerid, 1);
		SendClientMessage(playerid, COLOR_GRAD, "Você foi teleportado pelo Admin!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
	}
	return true;
}

CMD:irpos(playerid, params[])
{
	if (Admin_GetNivel(playerid) < SUPERVISOR) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new Float:posicaoIr[3];

	if (sscanf(params, "fff", posicaoIr[0], posicaoIr[1], posicaoIr[2]))
		return SendClientMessage(playerid, -1, "Modo de uso: /irpos (posição X) (posição Y) (posição Z)");

	SetPlayerPos(playerid, posicaoIr[0], posicaoIr[1], posicaoIr[2]);
	SendClientMessage(playerid, COLOR_GRAD, "Você foi até a posição marcada.");

	return true;
}

//----------------------------------[Dar Arma]------------------------------------------------
CMD:dararma(playerid, params[])
{
	new playa;
	new WEAPON:gun;
	new ammo;

	if(sscanf(params, "udd", playa, gun, ammo))
		return SendClientMessage(playerid, -1, "Use: /dararma [id] [arma id(ex. 24 = Eagle)] [munição]");

	new string[128];

	if (Founders_GetList(playerid)) {
		goto skip_founder_ammo;
	}

	if(ammo < 1 || ammo > 999)
		return SendClientMessage(playerid, -1, "O minimo de munição é 1 e o máximo é 999!");

	skip_founder_ammo:

	if(gun < WEAPON_FIST || gun > WEAPON_PARACHUTE)
		return SendClientMessage(playerid, -1, "ID de arma inválido!");

	if (Admin_GetNivel(playerid) >= MASTER) {
		goto skip_master_armas;
	}

	skip_master_armas:
	if (Admin_GetNivel(playerid) >= ENCARREGADO)
	{
		if (Founders_GetList(playerid)) {
			goto skip_founder_dararma;
		}
		if (!Staff_GetWorking(playerid))
			return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

		skip_founder_dararma:
		if(IsPlayerConnected(playa))
		{
			new weapon_name[25];
			GetWeaponName(gun, weapon_name);
			GivePlayerWeapon(playa, gun, ammo);

			format(string, sizeof(string), "Admin: %s deu arma (%s com %d balas) para %s", PlayerName[playerid], weapon_name, ammo, PlayerName[playa]);
			Staff_ChatToAll(COLOR_LIGHTGREEN, string, ESTAGIARIO);

			format(string, sizeof(string), "Admin: %s deu arma (%s com %d balas) para %s", PlayerName[playerid], weapon_name, ammo, PlayerName[playa]);
			server_log("dararma", string);
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando!");
	}
	return true;
}

CMD:dararmap(playerid, params[])
{
	new Float:distance, WEAPON:gun, ammo;
	if(sscanf(params, "fdd", distance, gun, ammo))
		return SendClientMessage(playerid, COLOR_GRAD, "USE: /dararmap [distancia] [arma id(ex. 24 = Eagle)] [munição]");

   	new string[128];

	if (Founders_GetList(playerid)) {
		goto skip_founder_ammop;
	}

	if(ammo < 1 || ammo > 999)
		return SendClientMessage(playerid, COLOR_GRAD, "O mínimo de munição é 1 e o máximo é 999!");

	skip_founder_ammop:

	if(gun < WEAPON_FIST || gun > WEAPON_PARACHUTE)
		return SendClientMessage(playerid, -1, "ID de arma inválido!");

	if (Admin_GetNivel(playerid) >= MASTER) {
		goto skip_master_armasp;
	}

	skip_master_armasp:
	if (Admin_GetNivel(playerid) >= ENCARREGADO)
	{
		new Str[125];
		new countPlayers;
		new Float:x, Float:y, Float:z;
       	GetPlayerPos(playerid, x, y, z);

		new weapon_name[25];
		GetWeaponName(gun, weapon_name);

		new encontrado = false;
		foreach(new i : Player)
		{
	        if (IsPlayerInRangeOfPoint(i, distance, x, y, z))
			{
				countPlayers++;
				GivePlayerWeapon(i,  gun, ammo);

			    format(Str, sizeof Str, "> {FFFFFF}Você recebeu uma arma (%s com %d balas) pelo administrador %s", weapon_name, ammo, PlayerName[playerid]);
				SendClientMessage(i, 0xFF0000AA, Str);
				encontrado = true;
	        }
	    }

		if(encontrado) 
		{
			format(string, sizeof(string), "AdmAviso: %s deu arma %s com %d balas para os jogadores próximos. (Distância: %.2f | Total de Players: %d).", PlayerName[playerid], weapon_name, ammo, distance, countPlayers);
			Staff_ChatToAll(COLOR_LIGHTRED, string, ENCARREGADO);
			server_log("dararmap", string);
		}
		else {
			SendClientMessage(playerid, COLOR_GRAD, "Não há ninguém por perto.");
			Inventory_SetOpen(playerid, false);
		}
	}
	else
		SendClientMessage(playerid, COLOR_GRAD, "   Você não esta autorizado a usar este comando!");
	
	return true;
}

CMD:rarmasp(playerid, params[])
{
	new Float:distance, seconds;
	if(sscanf(params, "fd", distance, seconds))
	{
		SendClientMessage(playerid, COLOR_GRAD, "USE: /rarmasp [distancia] [segundos (0-300)]");
		return true;
	}
   	new string[256];
	if(seconds < 0 || seconds > 300)
	{
		SendClientMessage(playerid, COLOR_GRAD, "   O mínimo de tempo é 0 e o tempo é 300!");
		return true;
	}

	if (Admin_GetNivel(playerid) >= ENCARREGADO)
	{
		new Str[128];
		new countPlayers;
		new Float:x, Float:y, Float:z;
       	GetPlayerPos(playerid, x, y, z);

		new encontrado = false;
		foreach(new i : Player)
		{
	        if(IsPlayerInRangeOfPoint(i, distance, x, y, z) && i != playerid)
			{
				countPlayers++;
			    ResetPlayerWeapons(i);
				SetPVarInt(i, "ArmasRestringidas", gettime()+seconds);

			    format(Str, sizeof Str, "> {FFFFFF}Suas armas foram retiradas pelo administrador %s e restringidas por %d segundos.", PlayerName[playerid], seconds);
				SendClientMessage(i, 0xFF0000AA, Str);
				encontrado = true;
	        }
	    }

		if(encontrado) 
		{
			format(string, sizeof(string), "AdmAviso: %s retirou as armas dos jogadores próximos e restringiu por %d segundos. (Distância: %.2f | Total de Players: %d).", PlayerName[playerid], seconds, distance, countPlayers);
			Staff_ChatToAll(COLOR_LIGHTRED,string, ENCARREGADO);
		}
		else {
			SendClientMessage(playerid, COLOR_GRAD, "   Não há ninguém por perto");
			Inventory_SetOpen(playerid, false);
		}
	}
	else
		SendClientMessage(playerid, COLOR_GRAD, "   Você não esta autorizado a usar este comando!");
	
	return true;
}

enum vl_enum {
	vtQuestion[80],
	vtVotes[6],
	vtWin,
	vtHigher,
	vtQuestions,
	vtStarted
};
new VoteList[vl_enum],
	VoteListAnswers[6][80];

stock VoteList_SetQuestion(const string[], size=sizeof(string)) {
	format(VoteList[vtQuestion], size, "%s", string);
}

stock VoteList_SetAnswer(idanswer, const string[], size=sizeof(string)) {
	format(VoteListAnswers[idanswer], size, "%s", string);
}

stock VoteList_Start(playerid) {
	VoteList[vtWin] = -1;
	VoteList[vtHigher] = 0;
	VoteList[vtStarted] = 1;

	for(new i; i != 6; i++)
		VoteList[vtVotes][i] = 0;

	for(new i; i < MAX_PLAYERS; i++)
		votou[i] = false;

	SendClientMessageToAll(COLOR_DBLUE, "___________________________________________________________________________________________");

	SendMsgAllF(-1, "[Pergunta de %s: %s]", PlayerName[playerid], VoteList[vtQuestion]);

	for(new i = 0; i < VoteList[vtQuestions]; i++) {
		SendMsgAllF(COLOR_DBLUE, "*Opção %d: {33CCFF}%s", i+1, VoteListAnswers[i]);
	}
	SendMsgAllF(COLOR_DBLUE, "* Basta digitar {33CCFF}/opcao [1 - %d] {2641FE}para votar em uma delas!", VoteList[vtQuestions]);

	SendClientMessageToAll(COLOR_DBLUE, "___________________________________________________________________________________________");
}

stock Dialog_VoteList(playerid, change) {
	if(change > 1 && strlen(VoteListAnswers[change-2]) < 3) {
		SendMsgF(playerid, -1, "Preecha a opção %d antes de preencher esta opção.", change-1);
		return callcmd::votacao(playerid);
	}

	inline DialogVoteList(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused pid, dialogid, inputtext, listitem

		if (!response)
			return callcmd::votacao(playerid);
		else if (strlen(inputtext) < 3) {
			SendClientMessage(playerid, -1, "O texto deve conter mais que 3 caracteres.");
		}
		else if(change == 0) {
			VoteList_SetQuestion(inputtext);
		}
		else if(change > 0 && change < 7) {
			if(change > 1 && strlen(VoteListAnswers[change-2]) == 0) {
				SendMsgF(playerid, -1, "Preecha a opção %d antes de preencher esta opção.", change);
			}
			else {
				VoteList_SetAnswer(change-1, inputtext);
			}
		}

		new questions = 0;
		for(new i = 0; i < 6; i++) {
			if(strlen(VoteListAnswers[i]) >= 3) {
				questions += 1;
			}
		}
		VoteList[vtQuestions] = questions;

		return callcmd::votacao(playerid);
	}
	new part[30];
	if(change == 0)
		format(part, 30, "pergunta");
	else 
		format(part, 30, "opção %d", change);

	format(MEGAString, sizeof(MEGAString), "Informe um texto para ser a %s", part);
	Dialog_ShowCallback(playerid, using inline DialogVoteList,
		DIALOG_STYLE_INPUT,
		"Edição de votação", 
		MEGAString, 
		"Confirmar", "Voltar"
	);
	return 1;
}

CMD:votacao(playerid) 
{
	if (Admin_GetNivel(playerid) < ENCARREGADO)
		return SendClientMessage(playerid, -1, "Você não autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_votacao;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");
	
	skip_founder_votacao:

	if (VoteList[vtStarted])
		return SendClientMessage(playerid, -1, "Já existe uma votação em andamento, use /encerrarvotacao para finalizar.");

	MEGAString[0] = EOS;

	new string[128], vquestion[80];
	format(vquestion, 80, VoteList[vtQuestion]);

	format(
		string, sizeof(string), 
		""C_WHITE"Pergunta:\t"C_CYAN"%s\n", 
		(strlen(vquestion) < 3 ?  ""C_GRAY"Clique para editar a pergunta »" : vquestion)
	);
	strcat(MEGAString, string);

	for(new i = 0; i < 6; i++) {
		format(
			string, sizeof string, 
			""C_WHITE"Opção [%d]:\t"C_CYAN"%s\n", 
			i+1, strlen(VoteListAnswers[i]) < 3 ? ""C_GRAY"Clique para editar a resposta 1 »" : VoteListAnswers[i]
		);
		strcat(MEGAString, string);
	}

	strcat(MEGAString, ""C_GREEN"Iniciar a votação »");

	inline DialogList(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused pid, dialogid, inputtext

		if(!response) {
			return 1;
		}
		else if(listitem >= 0 && listitem <= 6) {
			Dialog_VoteList(playerid, listitem);
		}
		else {
			VoteList_Start(playerid);
		}
		return 1;
	}
	Dialog_ShowCallback(playerid, using inline DialogList,
		DIALOG_STYLE_TABLIST,
		string, MEGAString, "Editar", "Cancelar"
	);

	return 1;
}

CMD:opcao(playerid, params[])
{
	if(!VoteList[vtStarted])
		return SendClientMessage(playerid, -1, "Não há uma votação em andamento");
	else if(votou[playerid])
		return SendClientMessage(playerid, -1, "Você já registrou seu voto nessa votação.");
		
	new vtid, string[128];
	if(sscanf(params, "d", vtid) || vtid < 1 || vtid > VoteList[vtQuestions])
		return SendMsgF(playerid, -1, "USE: /opcao [1 - %d]", VoteList[vtQuestions]);

	VoteList[vtVotes][vtid-1]++;

	if(VoteList[vtVotes][vtid-1] == VoteList[vtHigher]){
		VoteList[vtWin] = -1;
	}
	else if(VoteList[vtVotes][vtid-1] > VoteList[vtHigher]){
		VoteList[vtWin] = vtid-1;
		VoteList[vtHigher] = VoteList[vtVotes][vtid-1];
	}

	format(string, sizeof string, "Você votou na opção %d: ''%s''", vtid, VoteListAnswers[vtid-1]);
	SendClientMessage(playerid, -1, string);

	votou[playerid] = true;
	return 1;
}

CMD:encerrarvotacao(playerid)
{
	if(Admin_GetNivel(playerid) < ENCARREGADO)
		return SendClientMessage(playerid, -1, "Você não autorização para usar esse comando.");
	else if(!VoteList[vtStarted])
		return SendClientMessage(playerid, -1, "Não há uma votação em andamento.");
	
	new string[128];
	SendClientMessageToAll(COLOR_LIGHTBLUE, "___________________________________________________________________________________________");
	SendMsgAllF(-1, "[Pergunta: %s]", VoteList[vtQuestion]);

	for(new i = 0; i < VoteList[vtQuestions]; i++) {
		format(string, 128, "(%d Votos) Opção %d: {33CCFF}%s", VoteList[vtVotes][i], i+1, VoteListAnswers[i]);
		SendClientMessageToAll(-1, string);
	}

	if(VoteList[vtWin] == -1) {
		SendClientMessageToAll(COLOR_LIGHTBLUE, "* Houve um empate entre algumas opções acima, nenhuma delas foi a mais votada!");
	}
	else {
		format(string, 128, ">> A opção mais votada foi a nº %d: {33CCFF}''%s'' !", VoteList[vtWin]+1, VoteListAnswers[VoteList[vtWin]]);
		SendClientMessageToAll(COLOR_DBLUE, string);
	}

	SendClientMessageToAll(COLOR_LIGHTBLUE, "___________________________________________________________________________________________");
	VoteList[vtStarted] = 0;
	return 1;
}


CMD:destruirveiculos(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MODERADOR) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_destruirveiculos;
	}

	if (Admin_GetNivel(playerid) < DONO && !Staff_GetWorking(playerid)) return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");
	
	skip_founder_destruirveiculos:

	for(new x; x != 15; x++) {
		if ( CarrosAdmin[x] > 0 ) {
			DestroyVehicle(CarrosAdmin[x]);
			CarrosAdmin[x] = 0;
		}
	}

	new string[100];

	format(string, sizeof(string), "AdmCmd: %s(%d) destruiu os veículos criados por administradores.", PlayerName[playerid], playerid);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

	return true;
}

CMD:destruirveiculo(playerid, params[])
{
	new
		vehicleid,
		string[128], 
		destruido = 0
	;

	if (Admin_GetNivel(playerid) < ADMINISTRADOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_desvei;
	}

	if (Admin_GetNivel(playerid) < DONO && !Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_desvei:

	if(sscanf(params, "d", vehicleid)) return SendClientMessage(playerid, -1, "Modo de uso: /destruirveiculo (id)");

	if(vehicleid <= 0) return SendClientMessage(playerid, -1, "ID de veículo inválido.");

	for(new x; x != 15; x++) {
		if(CarrosAdmin[x] == vehicleid) {
			DestroyVehicle(CarrosAdmin[x]);
			CarrosAdmin[x] = 0;
			destruido = 1;
		}
	}

	if(destruido)
	{
		format(string, sizeof(string), "AdmCmd: %s(%d) destruiu o veículo ID: %d.", PlayerName[playerid], playerid, vehicleid);
		Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO), server_log("comandosadmin", string);
	}
	else
		SendClientMessage(playerid, -1, "Não existe veículo criado com esse ID.");

	return true;
}

CMD:veh(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MODERADOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_veh;
	}

	if (Admin_GetNivel(playerid) < DONO && !Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_veh:
	new
		modelVehicle,
		ColorVehicle1,
		ColorVehicle2
	;

	if(sscanf(params, "ddd", modelVehicle, ColorVehicle1, ColorVehicle2)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /veh (id do modelo) (cor 1) (cor 2)");

	new string[128];

	if (modelVehicle < 400 || modelVehicle > 611) return SendClientMessage(playerid, -1, "Modelo do veículo (entre 400 a 611)");
	if (ColorVehicle1 < 0 || ColorVehicle1 > 255) return SendClientMessage(playerid, -1, "Cor do veículo (entre 0 a 255)");
	if (ColorVehicle2 < 0 || ColorVehicle2 > 255) return SendClientMessage(playerid, -1, "Cor do veículo (entre 0 a 255)");


	new Float:X,Float:Y,Float:Z;
	GetPlayerPos(playerid, X,Y,Z);

	new max_veiculos;

	for(new vehicleid; vehicleid != 15; vehicleid++) {
		if ( !CarrosAdmin[vehicleid] ) {
			CarrosAdmin[vehicleid] = CreateVehicle(modelVehicle, X,Y+2,Z, 0.0, ColorVehicle1, ColorVehicle2, -1);
			max_veiculos = CarrosAdmin[vehicleid];
			break;
		}
	}

	if (!max_veiculos) return SendClientMessage(playerid, -1, "Há muitos veículos criados no servidor, use: /destruirveiculos.");

	VehicleInfo[max_veiculos][vehicleCombustivel] = 99;

	StartVehicleEngine(max_veiculos);

	if (IsVehicleLocked(max_veiculos))
		UnlockVehicleDoors(max_veiculos);

	format(string, sizeof(string), "AdmCmd: %s(%d) criou o veículo - ID: %d, Modelo: %d.", PlayerName[playerid], playerid, max_veiculos, modelVehicle);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO), server_log("comandosadmin", string);

	return true;
}

CMD:clima(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MASTER)
	{
		SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando!");
		return true;
	}
	new weather, hora;
	if(sscanf(params, "dd", hora, weather))
	{
		SendClientMessage(playerid, -1, "Use: /clima [hora (0 - 24)] [tempo]");
		return true;
	}
	new string[128];
	SetWeather(weather);
	SetWorldTime(hora);
	format(string, sizeof(string), "CLIMA: Admin %s setou a hora para: %d, e o tempo para: %d", PlayerName[playerid], hora, weather);
	SendClientMessageToAll(COLOR_LIGHTGREEN, string);

	return true;
}

CMD:infouniverso(playerid)
{
	if (!Admin_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	new string[70];

	format(string, sizeof(string), "Mundo virtual atual: {00FF00}%d", GetPlayerVirtualWorld(playerid));
	SendClientMessage(playerid, COLOR_GRAD, string);

	format(string, sizeof(string), "Interior atual: {00FF00}%d", GetPlayerInterior(playerid));
	SendClientMessage(playerid, COLOR_GRAD, string);

	return 1;
}

CMD:setskin(playerid, params[])
{
	new para1, level;
	if(sscanf(params, "ud", para1, level))
	{
		SendClientMessage(playerid, -1, "Use: /setskin [playerid] [skin id]");
		return true;
	}
	if((level > 311 || level < 0))
	{
		SendClientMessage(playerid, -1, "id desconhecido!");
		return true;
	}
	new string[128];
	if (Admin_GetNivel(playerid) >= MASTER)
	{
		if (Founders_GetList(playerid)) {
			goto skip_founder_setskin;
		}
		if(!Staff_GetWorking(playerid))
			return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

		skip_founder_setskin:
		if(IsPlayerConnected(para1))
		{
			if(para1 != INVALID_PLAYER_ID)
			{
				if(!Admin_GetNivel(para1) && !Helper_GetNivel(para1))
					return SendClientMessage(playerid, -1, "Você só pode usar este comando em admins !");

				PlayerInfo[para1][pSkin] = level;
				format(string, sizeof(string), "Sua skin foi trocada!", PlayerName[playerid],level);
				SendClientMessage(para1, COLOR_LIGHTRED, string);
				format(string, sizeof(string), "Você mudou a skin de %s para %d.", PlayerName[para1],level);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				SetPlayerSkin(para1, PlayerInfo[para1][pSkin]);
				format(string, sizeof(string), "%s setou a skin id: %d em %s", PlayerName[playerid], level, PlayerName[para1]);
				server_log("comandosadmin", string);
			}
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não tem permissão para usar esse comando!");
	}
	return true;
}

CMD:secreto(playerid)
{
	if(GetPlayerOrg(playerid) != 8 && GetPlayerOrg(playerid) != 22 && GetPlayerOrg(playerid) != 25)
		return SendClientMessage(playerid, -1, "Você não é um assassino!");
	if(GoChase[playerid] == INVALID_PLAYER_ID) return SendClientMessage(playerid, -1, "Você não possui um contrato");

	if(GetPlayerSeeNick(playerid))
	{
		foreach(new i : Player)
		{
			ShowPlayerNameTagForPlayer(i, playerid, false);
		}
		SetPlayerSeeNick(playerid, false);
		SendClientMessage(playerid, COLOR_GRAD, "(( Você agora está jogando em modo secreto ))");
	}
	else if (!GetPlayerSeeNick(playerid))
	{
		foreach(new i : Player)
		{
			ShowPlayerNameTagForPlayer(i, playerid, true);
		}
		SetPlayerSeeNick(playerid, true);
		SendClientMessage(playerid, COLOR_GRAD, "(( Você agora está jogando em modo normal ))");
	}
	return true;
}

//-----------------------------------[Slap]-----------------------------------------------
CMD:tapa(playerid, params[])
{
	new playa;
	if(sscanf(params, "u", playa))
	{
		SendClientMessage(playerid, -1, "Use: /tapa [id]");
		return true;
	}
	new Float:slx, Float:sly, Float:slz;
	new string[128];
	if (Admin_GetNivel(playerid) || Helper_GetNivel(playerid))
	{
		if (!strcmp(PlayerName[playa], "Theus_Crazzy") || !strcmp(PlayerName[playa], "iHollyZinhO") || !strcmp(PlayerName[playa], "Joao_Revolts")) 
			return SendClientMessage(playerid, -1, "Você não pode dar tapa neste administrador.");

		if (Founders_GetList(playerid))
			goto skip_founder_tapa;

		if(!Staff_GetWorking(playerid))
			return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

		skip_founder_tapa:
		if(IsPlayerConnected(playa))
		{
			if(playa != INVALID_PLAYER_ID)
			{
				GetPlayerPos(playa, slx, sly, slz);
				SetPlayerPos(playa, slx, sly, slz+15);
				PlayerPlaySound(playa, 1190, slx, sly, slz+12);

				format(string, sizeof(string), "AdmCmd: %s ganhou um tapa de: %s", PlayerName[playa], PlayerName[playerid]);
				Staff_ChatToAll(COLOR_LIGHTRED,string);
				server_log("comandosadmin", string);
			}
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "	Você não pode usar este comando!");
	}
	return true;
}

CMD:rpv(playerid, params[])
{
	new idPlayer;
	if(sscanf(params, "u", idPlayer)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /rpv (id do jogador)");

	new string[128];

	if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!Player_Logado(idPlayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (!IsPlayerInAnyVehicle(idPlayer)) SendClientMessage(playerid,-1, "O jogador não está em um veículo");

	format(string, sizeof(string), "AdmCmd: %s, %s removeu %s de seu veículo.", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idPlayer]);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

	RemovePlayerFromVehicle(idPlayer);

	return true;
}

CMD:desativarnoob(playerid)
{
	new string [63];
	if (Admin_GetNivel(playerid) >= DIRETOR)
	{
		if(NoobDesativado == 0)
		{
	    	NoobDesativado = 1;
	    	format(string, sizeof string, "AdmCmd: Admin %s desativou o Canal Noob.", PlayerName[playerid]);
	    	Staff_ChatToAll(COLOR_LIGHTRED,string, ESTAGIARIO);
		} 
		else 
		{
			NoobDesativado = 0;
	    	format(string, sizeof string, "AdmCmd: Admin %s ativou o Canal Noob.", PlayerName[playerid]);
	    	Staff_ChatToAll(COLOR_LIGHTRED,string, ESTAGIARIO);
		}
	}
	return 1;
}

CMD:gmxautomatico(playerid)
{
	new string [63];
	if (Admin_GetNivel(playerid) >= DONO)
	{
		if(gmxAutomatico == 0)
		{
	    	gmxAutomatico = 1;
	    	format(string, sizeof string, "AdmCmd: Admin %s ativou o GMX automático.", PlayerName[playerid]);
	    	Staff_ChatToAll(COLOR_LIGHTRED,string, ESTAGIARIO);
		} 
		else 
		{
			gmxAutomatico = 0;
	    	format(string, sizeof string, "AdmCmd: Admin %s desativou o GMX automático.", PlayerName[playerid]);
	    	Staff_ChatToAll(COLOR_LIGHTRED,string, ESTAGIARIO);
		}
	}
	return 1;
}

CMD:eventoaleatorio(playerid)
{
	new string [63];
	if (Admin_GetNivel(playerid) >= SUB_DONO)
	{
		if(eventoAleatorio == 0)
		{
	    	eventoAleatorio = 1;
	    	format(string, sizeof string, "AdmCmd: Admin %s ativou os Eventos Aleatórios.", PlayerName[playerid]);
	    	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
		} 
		else 
		{
			eventoAleatorio = 0;
	    	format(string, sizeof string, "AdmCmd: Admin %s desativou os Eventos Aleatórios.", PlayerName[playerid]);
	    	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
		}
	}
	return 1;
}

CMD:limparcasamento(playerid, params[])
{
	new string[90];

	new idplayer;
	if(sscanf(params, "u", idplayer)) {
		return SendClientMessage(playerid, -1, "Use: /limparcasamento [ID]");
	}
	if (Admin_GetNivel(playerid) >= ADMINISTRADOR) {

		if(IsPlayerConnected(idplayer)) {

			if(idplayer != INVALID_PLAYER_ID) {

				ClearMarriage(idplayer);
				SendClientMessage(idplayer, COLOR_LIGHTRED,"	Você foi divorciado por algum administrador!");
				format(string, sizeof(string), "AdmAviso: %s limpou o casamento de %s.", PlayerName[playerid], PlayerName[idplayer]);
				Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
			}
		}
	}
	else {
		SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
	}
	return true;
}

CMD:rarmas(playerid, params[])
{
	new string[90];

	new idplayer;
	if(sscanf(params, "u", idplayer)) {
		return SendClientMessage(playerid, -1, "Use: /retirararmas [ID]");
	}

	if (Admin_GetNivel(playerid)) {

		if (Founders_GetList(playerid)) {
			goto skip_founder_rarmas;
		}
		if(!Staff_GetWorking(playerid))
			return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

		skip_founder_rarmas:
		if(IsPlayerConnected(idplayer))
		{
			if(idplayer != INVALID_PLAYER_ID)
			{
				ResetPlayerWeapons(idplayer);
				format(string, sizeof(string), "AdmAviso: %s retirou as armas de %s.", PlayerName[playerid], PlayerName[idplayer]);
				Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
			}
		} else {
			SendClientMessage(playerid, -1, "O jogador não está conectado no servidor.");
		}
	}
	else {
		SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
	}
	return true;
}

CMD:calar(playerid, params[])
{
	if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /calar (id do jogador)");

	if (Founders_GetList(playerid))
		goto skip_founder_calar;

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

	skip_founder_calar:
	if (Admin_GetNivel(idplayer) > DONO && Admin_GetNivel(playerid) < PROGRAMADOR)
		return SendClientMessage(playerid, -1, "Você não pode usar esse comando em um Dono/Fundador.");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "Esse jogador não está logado/conectado no servidor."); 

	new string[100];

	if (!Player_GetMuted(playerid)) {
		Player_SetMuted(playerid, true);
		format(string, sizeof(string), "AdmCmd: %s foi calado pelo administrador: %s.", PlayerName[idplayer], PlayerName[playerid]);
	} else {
		Player_SetMuted(playerid, false);
		format(string, sizeof(string), "AdmCmd: %s foi descalado pelo administrador: %s.",PlayerName[idplayer], PlayerName[playerid]);
	}
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
	server_log("cmd_calar", string);

	return true;
}

// infoarmas , infoplayer , infoxiter
CMD:infoarmas(playerid, params[])
{
	if (!Admin_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando");

	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /infoarmas (id do jogador)");

	if (!Player_Logado(idplayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	new WEAPON:weapons[13],
		ammo[13];
	SendMsgF(playerid, TEAM_BALLAS_COLOR, "EXIBINDO AS INFORMAÇÕES DAS ARMAS DE: %s", PlayerName[idplayer]);
	
	new weapon_name[25];

	for(new weapon = 1; weapon < sizeof(weapons); weapon++) {
		GetWeaponName(weapons[weapon], weapon_name);

		GetPlayerWeaponData(idplayer, WEAPON_SLOT:weapon, weapons[weapon], ammo[weapon]);
		SendMsgF(playerid, COLOR_WHITE, "Arma: %s, Munição: %d", weapon_name, ammo[weapon]);
	}

	return 1;
}

CMD:infoplayer(playerid, params[]) {

	new ClientVersion[32],
		string[128],
		Float:Health,
		Float:Armour;

	new idplayer;

	if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está autorizado a usar esse comando!");

	if(sscanf(params, "u", idplayer)) 
		return SendClientMessage(playerid, -1, "Use: /infoplayer [id do player]");

	if(IsPlayerConnected(idplayer)) {
		if(idplayer != INVALID_PLAYER_ID) {

			GetPlayerArmour(idplayer, Armour);
			GetPlayerHealth(idplayer, Health);
			GetPlayerVersion(idplayer, ClientVersion, 32);

			SendClientMessage(playerid, -1, "> Informações do jogador:");

			format(string, sizeof(string), "NICK: %s | PING: %d | SA-MP: %s | SKIN %d (%d)", PlayerName[idplayer], GetPlayerPing(idplayer), ClientVersion, 
				PlayerInfo[idplayer][pSkin], GetPlayerSkin(idplayer));
			SendClientMessage(playerid, -1, string);

			format(string, sizeof(string), "VIDA: %1f | COLETE: %1f", Health, Armour);
			SendClientMessage(playerid, -1, string);
			new weapon_name[25];

			for(new i_slot = 0, WEAPON:gun, ammo; i_slot != 12; i_slot++)
			{
				GetPlayerWeaponData(playerid, WEAPON_SLOT:i_slot, gun, ammo);
				GetWeaponName(gun, weapon_name);

				switch(gun){

					case 16, 18, 26, 28, 36, 37, 40:
							SendClientMessage(playerid, 0xFF0000AA, "( Jogador com arma suspeita | use /tv para verifica-lo )");
				}

				format(string, sizeof(string), "( SLOT: %d | Arma: %s | Munição: %d )", i_slot, weapon_name, ammo);
				SendClientMessage(playerid, COLOR_GRAD, string);
			}
		}
	} else {
		return SendClientMessage(playerid, -1, "Não foi encontrado nenhum jogador.");
	}
	return true;
}

CMD:skydive(playerid, params[])
{
	if (Admin_GetNivel(playerid) >= ENCARREGADO)
	{
		new Float:slx, Float:sly, Float:slz;
		GetPlayerPos(playerid, slx, sly, slz);
		if (IsPlayerConnected(playerid))
		{
			SetPlayerPos(playerid,slx, sly, slz+2500);
			SendClientMessage(playerid, COLOR_LIGHTRED, "UUUUP!!!");
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não esta autorizado a usar este comando!");
	}
	return 1;
}

CMD:testetempo(playerid, params[])
{
	if (Admin_GetNivel(playerid) < DIRETOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new weather;

	if(sscanf(params, "d", weather)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /testetempo (WeatherID)");

	if (weather < 0 || weather > 45) 
		return SendClientMessage(playerid, -1, "Você precisa escolher entre 0 a 45 weatherid.");

	SetPlayerWeather(playerid, weather);
	SendClientMessage(playerid, 0xDBED15FF, "Você está testando o tempo. (Apenas para você)");

	return true;
}

CMD:setgravidade(playerid, params[])
{
	if (Dev_GetNivel(playerid) < DEV_DELTA) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new Float:gravidadeFloat;
	if (sscanf(params, "f", gravidadeFloat)) return SendClientMessage(playerid, -1, "Modo de uso: /setgravidade (gravidade)");

	if (gravidadeFloat < 0.0 || gravidadeFloat > 100.0) return SendClientMessage(playerid, -1, "Você precisa escolher entre 0.0 a 100.00 a gravidade.");

	SetGravity(gravidadeFloat);

	new string[128];
	format(string, sizeof string, "AdmAviso: %s, %s setou a gravidade de todos para (%f).", Staff_GetPositionName(playerid), PlayerName[playerid], gravidadeFloat);

	return SendClientMessageToAll(COLOR_LIGHTRED, string);
}

CMD:kick(playerid, reason[])
{
	new idplayer;
	if(sscanf(reason, "us[60]", idplayer, reason))
		return SendClientMessage(playerid, -1, "Modo de uso: /kick (id do jogador) (motivo).");

	if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando");

	if (!IsPlayerConnected(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado no servidor.");

	if (strcmp(PlayerName[idplayer], "Theus_Crazzy") == 0 && Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "Você não pode kickar esse administrador.");

	PlayerKick(playerid, DCC_INVALID_USER, idplayer, reason);
	return 1;
}

CMD:rtitulo(playerid, params[])
{
	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Use: /rtitulo [id do jogador]");

	new string[128];
	if (Admin_GetNivel(playerid) >= MASTER)
	{
		if (IsPlayerConnected(idplayer))
		{
			SendClientMessage(idplayer, 0xFFDEADFF, "Algum administrador removeu seu titulo.");

			PlayerTitle_Set(playerid, "");

			format(string, sizeof(string), "AdmAviso: %s removeu o titulo de %s", PlayerName[playerid], PlayerName[idplayer]);
			Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
			server_log("comandosadmin", string);
			return true;
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando!");
	}
	return true;
}

CMD:blocknoob(playerid, params[])
{
	if (!Admin_GetNivel(playerid) && !Helper_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_blocknoob;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você precisa estar em modo trabalho para usar o comando.");

	skip_founder_blocknoob:
	new idplayer;

	if(sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: {FF0000}/blocknoob {FFFFFF}[{FF0000}id do jogador{FFFFFF}]");
	
	if (!IsPlayerConnected(idplayer))
		return SendClientMessage(playerid, COLOR_GRAD, "Jogador não encontrado ou não está online.");

	new string[128];

	format(string, sizeof(string), "%s foi proibido de usar (/n) por um admin, motivo: Uso indevido.", PlayerName[idplayer]);
	SendClientMessageToAll(COLOR_LIGHTRED, string);

	PlayerInfo[idplayer][pToggleNoob] = gettime() + (240 * 60);
	Player_RemoveMoney(idplayer, 10000);

	SendClientMessage(idplayer, 0xA21818FF, "Você foi proibido de usar o canal /n e perdeu $10.000");
	SendClientMessage(idplayer, COLOR_LIGHTRED, "Na próxima vez, use o canal noob em caso de dúvidas relacionadas com a GameMode.");

	format(string, sizeof(string), "%s foi proibido de usar (/n) por um %s, motivo: Uso indevido.", PlayerName[idplayer], PlayerName[playerid]);
	server_log("blocknoob", string);

	return 1;
} 

CMD:desblocknoob(playerid, params[])
{
	if (!Admin_GetNivel(playerid) && !Helper_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_desbnoob;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você precisa estar em modo trabalho para usar o comando.");

	skip_founder_desbnoob:
	new idplayer;

	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Use: /desblocknoob [id do jogador]");

	if(!IsPlayerConnected(idplayer))
		return SendClientMessage(playerid, COLOR_GRAD, "Jogador não encontrado ou não está online.");

	new string[128];

	PlayerInfo[idplayer][pToggleNoob] = 0;

	format(string, sizeof(string), "AdmCmd: %s liberou o chat (/noob) para %s.", PlayerName[playerid], PlayerName[idplayer]);
	SendClientMessageToAll(COLOR_LIGHTRED, string);

	format(string, sizeof(string), "Você foi liberado de usar o /noob pelo %s, %s", Staff_GetPositionName(playerid), PlayerName[playerid]);
	SendClientMessage(idplayer, COLOR_LIGHTRED, string);

	server_log("noob", string);

	return 1;
}

CMD:pdm(playerid, params[])
{
	if (Admin_GetNivel(playerid) < DONO) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	foreach(new i : Player)
		PagarPayday(i);

	new string[128];

	format(string, sizeof(string), "(Payday Manual): %s, %s(%d) deu um payday manual.", Staff_GetPositionName(playerid), PlayerName[playerid], playerid);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
	server_log("paydaymanual", string);

	return 1;
}

CMD:descongelar(playerid) return SendClientMessage(playerid, -1, "Use o comando /congelar para congelar e descongelar.");
CMD:congelar(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ENCARREGADO) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid))
		goto skip_founder_congelar;

   	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você precisa estar em modo trabalho.");

	skip_founder_congelar:
   	new idPlayer;
	if (sscanf(params, "u", idPlayer)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /congelar (id do jogador)");

	if (!Player_Logado(idPlayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (Admin_GetNivel(idPlayer) >= DONO && Admin_GetNivel(playerid) < DONO) 
		return SendClientMessage(playerid, -1, "Você não pode usar esse comando nesse jogador.");

	new string[103],
		bool:congelado = GetPVarInt(idPlayer, "Congelado");

	format(string, sizeof(string), "AdmCmd: %s[%d] foi %s pelo %s, %s.", PlayerName[idPlayer], idPlayer, congelado ? ("descongelado") : ("congelado"), Staff_GetPositionName(playerid), PlayerName[playerid]);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
	
	TogglePlayerControllable(idPlayer, congelado); 
	SetPVarInt(idPlayer, "Congelado", !congelado);

	return 1;
}

CMD:gasparzinho(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MASTER)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer;

	if(sscanf(params, "us[80]", idplayer, params))
		return SendClientMessage(playerid, -1, "Modo de uso: /gasparzinho (id/nick do jogador) (mensagem)");

	if (IsPlayerNPC(idplayer)) 
		return SendClientMessage(playerid, -1, "Você não pode enviar uma mensagem a um NPC.");

	new string[256];

	format(string, sizeof(string), "SMS: %s, enviou: Gasparzinho (000)", params);
	SendClientMessage(idplayer, COLOR_YELLOW, string);
	PlayerPlaySound(idplayer, 3600, 0.0, 0.0, 0.0);

	format(string, sizeof(string), "A mensagem do Gasparzinho foi enviada ao destinatário.");
	SendClientMessage(playerid, COLOR_GRAD, string);

	format(string, sizeof(string), "Mensagem enviada: {33CCFF}(%s)", params);
	SendClientMessage(playerid, COLOR_YELLOW, string);
	
	format(string, sizeof(string), "%s, %s enviou Gasparzinho a %s: %s", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer], params);
	server_log("gasparzinho", string);

	return 1;
}

CMD:pagarstaff(playerid, params[])
{
	if (Admin_GetNivel(playerid) < GERENTE)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer, quantity;
	if (sscanf(params, "udd", idplayer, quantity))
		return SendClientMessage(playerid, -1, "Modo de uso: /pagarstaff (id do jogador) (quantia)");

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (!Admin_GetNivel(idplayer))
		return SendClientMessage(playerid, -1, "O jogador não faz parte da Administração do Servidor.");

	if (isInventoryFull(idplayer))
	    return SendClientMessage(playerid, -1, "O inventário do administrador está cheio.");

	if (Admin_GetNivel(playerid) > DONO)
		goto skip_founder_pagarstaff;

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

	skip_founder_pagarstaff:
	new string[128];

	format(string, sizeof(string), "Salário Staff » %s, %s pagou o salário staff ao %s.", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer]);
	Staff_ChatToAll(COLOR_WHITE, string, ESTAGIARIO);
	
	Player_AddCash(idplayer, quantity);
	format(string, sizeof(string), "Você recebeu %s cash de salário staff pelo "C_WHITE"%s, %s.", getFormatText(quantity), Staff_GetPositionName(playerid), PlayerName[playerid]);
	SendClientMessage(idplayer, COLOR_ORANGE, string);

	format(string, sizeof(string), "%s pagou salário staff de %s em cash ao %s, %s.", PlayerName[playerid], getFormatText(quantity), Staff_GetPositionName(idplayer), PlayerName[idplayer]);
	server_log("pagar_staff", string);

	return 1;
}

CMD:pagarhelper(playerid, params[])
{
	if (Admin_GetNivel(playerid) < GERENTE)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /pagarhelper (id do jogador)");

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (!Helper_GetNivel(idplayer))
		return SendClientMessage(playerid, -1, "O jogador não faz parte da lista de helpers.");

	if (isInventoryFull(idplayer))
	    return SendClientMessage(playerid, -1, "O inventário do helper está cheio.");

	if (Admin_GetNivel(playerid) > DONO)
		goto skip_founder_pagarhelper;

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

	skip_founder_pagarhelper:
	new string[128];

	format(string, sizeof(string), "Salário Helper » %s, %s pagou o salário helper ao %s.", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer]);
	Staff_ChatToAll(COLOR_WHITE, string, ESTAGIARIO);
	givePlayerItem(idplayer, ITEM_TYPE_DINHEIRO, 1212, 1500000, "Salario Helper");

	format(string, sizeof(string), "Você recebeu o salário helper pelo {FFFFFF}%s, %s.", Staff_GetPositionName(playerid), PlayerName[playerid]);
	SendClientMessage(idplayer, COLOR_ORANGE, string);
	
	format(string, sizeof(string), "%s pagou salário helper ao %s", PlayerName[playerid], PlayerName[idplayer]);
	server_log("pagar_helper", string);

	return 1;
}

CMD:darlicencas(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MASTER)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /darlicencas (id do jogador)");

	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (Founders_GetList(playerid)) goto skip;

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

	skip:
	if (isInventoryFull(idplayer))
	    return SendClientMessage(playerid, -1, "O inventário do jogador está cheio.");

	if (IsPlayerHaveItem(idplayer, ITEM_TYPE_MOTORISTA && ITEM_TYPE_PILOTO && ITEM_TYPE_MARUJO))
		return SendClientMessage(playerid, -1, "O jogador já possui todas as licenças.");

	if (!IsPlayerHaveItem(idplayer, ITEM_TYPE_MOTORISTA))
		givePlayerItem(idplayer, ITEM_TYPE_MOTORISTA, 1581, 1, "Carteira de Motorista");

	if (!IsPlayerHaveItem(idplayer, ITEM_TYPE_PILOTO))
		givePlayerItem(idplayer, ITEM_TYPE_PILOTO, 1581, 1, "Licenca de Piloto");

	if (!IsPlayerHaveItem(idplayer, ITEM_TYPE_MARUJO))
		givePlayerItem(idplayer, ITEM_TYPE_MARUJO, 1581, 1, "Licenca Nautica");

	new string[128];
	format(string, sizeof(string), "AdmCmd: %s, %s deu todas as licenças ao jogador: %s.", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer]);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

	format(string, sizeof(string), "Você recebeu todas as licenças pelo {FFFFFF}%s, %s.", Staff_GetPositionName(playerid), PlayerName[playerid]);
	SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);
	
	format(string, sizeof(string), "%s, %s deu todas as licenças ao %s", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer]);
	server_log("darlicencas", string);

	return 1;
}

CMD:setworld(playerid, params[])
{
	if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid,-1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) goto skip;
	
	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip:
    new worldid;
	if (sscanf(params, "d", worldid)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /setword (id do world)");

	SendMsgF(playerid, COLOR_SAMP, "Set virtual world: %d.", worldid);
	SetPlayerVirtualWorld(playerid, worldid);
	return 1;
}

CMD:setint(playerid, params[])
{
	if (!Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid,-1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid))
		goto skip_founder_setint;
	
	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_setint:

    new intid;
	if (sscanf(params, "d", intid)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /setint (id do interior)");

	new string[32];

	format(string, sizeof(string), "Set interior: %d.", intid);
	SendClientMessage(playerid, COLOR_SAMP, string);

	SetPlayerInterior(playerid, intid);
	return 1;
}

CMD:setorgvip(playerid, params[])
{
    if (Admin_GetNivel(playerid) < MASTER) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idOrg, result[16];
	if (sscanf(params, "ds[15]", idOrg, result)) 
		return SendClientMessage(playerid,-1, "Modo de uso: /setorgvip (id da organização) (motivo)");

	if (strlen(result) < 3 || strlen(result) > 15) 
		return SendClientMessage(playerid, -1, "O motivo deve conter de 3 a 15 caracteres!");

    if (idOrg > 34 || idOrg < 1) 
		return SendClientMessage(playerid, -1, "A organização deve estar entre 1 a 34.");

    new string[128];

	format(string, sizeof(string), "× (ORG-VIP) {FFFFFF}%s setou {00BFFF}+30 dias {FFFFFF}para %s, motivo: %s", PlayerName[playerid], GetOrgName(idOrg), (result));
	SendClientMessageToAll(0xFFF000AA, string); server_log("orgvip", string);
	
	OrgInfo_SetVIP(playerid, idOrg, 1);
	return true;
}

CMD:retirarorgvip(playerid, params[])
{
    if (Admin_GetNivel(playerid) < MASTER) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idOrg, result[16];
	if (sscanf(params, "ds[15]", idOrg, result)) 
		return SendClientMessage(playerid,-1, "Modo de uso: /retirarorgvip (id da organização) (motivo)");

	if (strlen(result) < 3 || strlen(result) > 15) 
		return SendClientMessage(playerid, -1, "O motivo deve conter de 3 a 15 caracteres!");

    if (idOrg < 1 || idOrg > 34) 
		return SendClientMessage(playerid, -1, "A organização deve estar entre 1 a 34.");

    new string[128];

	format(string, sizeof(string), "× (ORG-VIP) {FFFFFF}%s retirou a org-vip da %s, motivo: {F84646}%s", PlayerName[playerid], GetOrgName(idOrg), (result));
	SendClientMessageToAll(0xFFF000AA, string); 
	server_log("orgvip", string);

	OrgInfo_SetVIP(playerid, idOrg, 0);

	return 1;
}

CMD:puxartv(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ADMINISTRADOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /puxartv (id do jogador)");

	if (!Player_Logado(idPlayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	carryPlayerTeamViewer(playerid, idPlayer);

	return 1;
}

CMD:nickindevido(playerid, params[])
{
	if (Admin_GetNivel(playerid) < ESTAGIARIO) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Admin_GetNivel(playerid) >= DONO)
		goto skip_founder_nickindevido;

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_nickindevido:

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /nickindevido (id do jogador)");

	else if (!Player_Logado(idPlayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	else if (PlayerInfo[idPlayer][pLevel] > 5) 
		return SendClientMessage(playerid, -1, "O jogador possui um nível maior que 5 e não é possível solicitar a troca.");

	new string[112];

	format(string, sizeof(string), "AdmAviso: %s notificou %s(%d) por estar usando nick indevido.", PlayerName[playerid], PlayerName[idPlayer], idPlayer);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO); 

	ShowAlertInvalidNick(idPlayer, playerid);
	return 1;
}

// Desativar Sócio - Variáveis
new chatsocio = 1; // Predefinido - Ativado (0 - Desativado || 1 - Ativado)

CMD:desativarsocio(playerid, result[])
{
	if (Admin_GetNivel(playerid) < DIRETOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	if (Founders_GetList(playerid)) {
		goto skip_founder_dessocio;
	}

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip_founder_dessocio:
	new string[128];

	if (chatsocio == 1)
	{
		chatsocio = 0;
		format(string, sizeof(string), "AdmCmd: %s, %s desativou o Chat Sócio.", Staff_GetPositionName(playerid), PlayerName[playerid]);
		Staff_ChatToAll(COLOR_LIGHTRED, string);
	}
	else if (chatsocio == 0)
	{
		chatsocio = 1;
		format(string, sizeof(string), "AdmCmd: %s, %s ativou o Chat Sócio.", Staff_GetPositionName(playerid), PlayerName[playerid]);
		Staff_ChatToAll(COLOR_LIGHTRED, string);
	}
	else {
		chatsocio = 1;
		format(string, sizeof(string), "AdmCmd: %s, %s ativou o Chat Sócio.", Staff_GetPositionName(playerid), PlayerName[playerid]);
		Staff_ChatToAll(COLOR_LIGHTRED, string);
	}

	return 1;
}

CMD:executaroperacoes(playerid)
{
    if (Admin_GetNivel(playerid) < DONO) 
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    new string[128];
    if (Operations_LoadPending()) 
    {
        format(string, sizeof(string), "AdmAviso: %s executou todas as operações pendentes manualmente.", PlayerName[playerid]);
        Staff_ChatToAll(COLOR_LIGHTRED, string, SUB_DONO);
    } else {
        SendClientMessage(playerid, -1, "Não existem operações pendentes de serem executadas!");
    }
	return 1;
}

CMD:atualizarpasse(playerid) {
    if (Admin_GetNivel(playerid) >= DONO)
	{
        new string[128];
        format(string, sizeof(string), "AdmAviso: %s atualizou o passe atual.", PlayerName[playerid]);
        Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
		
        LoadWeeklyPass();
	}
    else
        SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    return 1;
}

// ---------------------------------------------------------------------
// Punições

CMD:skick(playerid, params[])
{
	new idplayer;
	if(sscanf(params, "u", idplayer))
	{
		SendClientMessage(playerid, -1, "Use: /skick [Id Do Jogador]");
		return true;
	}
	if (Admin_GetNivel(playerid) >= MASTER)
	{
		if (Founders_GetList(playerid)) {
			goto skip_founder_skick;
		}
		if(!Staff_GetWorking(playerid))
			return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

		skip_founder_skick:
		if(IsPlayerConnected(idplayer))
		{
			if(idplayer != INVALID_PLAYER_ID)
			{
				if(IsPlayerNPC(idplayer))
					return SendClientMessage(playerid, COLOR_YELLOW, "SMS: Se você usar este comando em um de nossos robôs, você irá sofrer as consequências!, enviou: Gasparzinho (000)");
				new string[80];
				KickEx(idplayer);
				printf("%s foi kickado por skick", PlayerName[idplayer]);
				SendClientMessage(playerid, COLOR_GRAD, "Player kickado com sucesso.");
				PlayerPlaySound(idplayer, 31202, 0.0, 0.0, 0.0);
				format(string, sizeof(string), "SKICK: %s foi kickado secreto pelo admin %s.", PlayerName[idplayer], PlayerName[playerid]);
				server_log("ban", string);
				return true;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "	Você não pode usar este comando!");
	}
	return 1;
}

CMD:ban(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MODERADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	if (Founders_GetList(playerid)) goto skip;

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip:
	new target_player[MAX_PLAYER_NAME], days, reason[34];
	if (sscanf(params, "s[24]ds[34]", target_player, days, reason)) {
        SendClientMessage(playerid, -1, "Modo de uso: /ban (nick do jogador) (dias) (motivo)");
        return SendClientMessage(playerid, COLOR_GRAY, "Obs: Para banir permanente em dias coloque -1.");
	}

	if (strlen(reason) > sizeof(reason))
		return SendClientMessage(playerid, -1, "Você precisa digitar no máximo 34 caracteres no motivo.");

	new idgplayer = Player_GetAccountIDByNick(target_player);
	if (!idgplayer)
		return SendClientMessage(playerid, -1, "Esse jogador não existe.");

	if (check_ban_nick(target_player))
		return SendMsgF(playerid, -1, "O jogador %s ja esta banido.", target_player);

	PlayerBan(playerid, DCC_INVALID_USER, target_player, reason, days);

	return 1;
}
alias:ban("agendarban")

// CMD:agendarbanip(playerid, params[]) return cmd_banip(playerid, params);
// CMD:banip(playerid, params[])
// {
// 	if (Admin_GetNivel(playerid) < MASTER)
// 		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

// 	if (Founders_GetList(playerid)) goto skip;

// 	if (!Staff_GetWorking(playerid))
// 		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

// 	skip:
// 	new target_ip[MAX_PLAYER_IP], days, reason[34];
// 	if (sscanf(params, "s[24]ds[128]", target_ip, days, reason)) {
//         SendClientMessage(playerid, -1, "Modo de uso: /banip (IP) (dias) (motivo)");
//         return SendClientMessage(playerid, COLOR_GRAY, "Obs: Para banir permanente em dias coloque -1.");
// 	}

// 	if (strlen(reason) > sizeof(reason))
// 		return SendClientMessage(playerid, -1, "Você precisa digitar no máximo 34 caracteres no motivo.");

// 	if (check_ban_ip(target_ip))
// 		return SendMsgF(playerid, -1, "O IP %s ja esta banido.", target_ip);

// 	PlayerBan(playerid, DCC_INVALID_USER, 0, reason, days);
// 	return 1;
// }

CMD:sban(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MODERADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	if (Founders_GetList(playerid)) goto skip;

	if (!Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip:
	new target_player[MAX_PLAYER_NAME], days, reason[34];
	if (sscanf(params, "s[24]ds[34]", target_player, days, reason)) {
        SendClientMessage(playerid, -1, "Modo de uso: /sban (nick do jogador) (dias) (motivo)");
        return SendClientMessage(playerid, COLOR_GRAY, "Obs: Para banir permanente em dias coloque -1.");
	}

	if (strlen(reason) > sizeof(reason))
		return SendClientMessage(playerid, -1, "Você precisa digitar no máximo 34 caracteres no motivo.");

	new idgplayer = Player_GetAccountIDByNick(target_player);
	if (!idgplayer)
		return SendClientMessage(playerid, -1, "Esse jogador não existe.");

	if (check_ban_nick(target_player))
		return SendMsgF(playerid, -1, "O jogador %s ja esta banido.", target_player);

	PlayerBan(playerid, DCC_INVALID_USER, target_player, reason, days, true);
	
	return 1;
}

CMD:hardbanip(playerid, params[])
{
	if (Admin_GetNivel(playerid) < DIRETOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer;
	if(sscanf(params, "us[64]", idplayer, params)) return SendClientMessage(playerid, -1, "Modo de uso: /hardbanip (id do jogador) (motivo)");

	if (!IsPlayerConnected(idplayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (!strcmp(PlayerName[idplayer], "Theus_Crazzy") || 
		!strcmp(PlayerName[idplayer], "iHollyZinhO") || 
		!strcmp(PlayerName[idplayer], "Joao_Revolts")) 
		return SendClientMessage(playerid, -1, "Você não pode hard ban ip num programador.");

	if (IsPlayerNPC(idplayer)) return SendClientMessage(playerid, -1, "Você não pode banir um NPC.");

	new string[128];

	format(string, sizeof(string), "AdmCmd: %s, %s deu hard ban no IP %s, motivo: %s.", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerIP[idplayer], params);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO), server_log("ban", string);

	HardBanIP(PlayerIP[idplayer]);

    foreach(new x : Player) {
        if (!strcmp(PlayerIP[idplayer], PlayerIP[x]))  {
			SendMsgF(x, COLOR_LIGHTRED, "Seu IP foi banido pelo administrador %s pelo motivo: %s.", PlayerName[playerid], params);
			PlayerPlaySound(idplayer, 31202, 0.0, 0.0, 0.0);
			KickEx(x);
		}
    }
	return true;
}

CMD:harddesbanip(playerid, params[])
{
	if (Admin_GetNivel(playerid) < DIRETOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (sscanf(params, "s[32]", params)) 
		return SendClientMessage(playerid,-1, "Use: /harddesbanip [IP]");

	new string[74];

	format(string, 128, "DESBAN: O admin %s deu um hard desban no ip %s", PlayerName[playerid], params);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

	HardUnbanIP(params);

	server_log("desban", string);
	return 1;
}

CMD:desbanconta(playerid, params[])
{
	if (Admin_GetNivel(playerid) < MASTER) 
		return SendClientMessage(playerid,-1, "Você não tem autorização para usar esse comando.");

	new namePlayer[MAX_PLAYER_NAME], result[24];
	if (sscanf(params, "s[24]s[23]", namePlayer, result)) 
		return SendClientMessage(playerid,-1, "Use: /desbanconta [nick] [motivo]");

	if (strlen(result) < 3 || strlen(result) > 23) 
		return SendClientMessage(playerid, -1, "O motivo deve conter de 3 a 23 caracteres!");

	new string[150];

	if (check_ban_nick(namePlayer))
	{
		new gid = Player_GetAccountIDByNick(namePlayer);

		format(string, sizeof(string), "STAFF: {FFFFFF}%s, %s desbaniu %s, motivo: {82E789}%s.", Staff_GetPositionName(playerid), PlayerName[playerid], namePlayer, (result));
		SendClientMessageToAll(0xBA2E30FF, string);

		Unbanned_Player(gid);
		server_log("desban", string);
	}
	else SendClientMessage(playerid, -1, "A conta não está banida ou não foi encontrada no banco de dados.");

	return true;
}

CMD:desbanip(playerid, params[])
{
	new string[74];

	if (Admin_GetNivel(playerid) >= MASTER) {

		if(sscanf(params, "s[32]", params)) {
			return SendClientMessage(playerid,-1, "Use: /desbanip [IP]");
		}
		if(check_ban_ip(params)) {
			format(string, 128, "DESBAN: O admin %s desbaniu o ip %s", PlayerName[playerid], params);
			Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

			desban_ip(params);

			server_log("desban", string);
		} else {
			SendClientMessage(playerid, -1, "IP não encontrado no banco de dados.");
		}
	} else {
		return SendClientMessage(playerid,-1, "Você não tem autorização para usar esse comando.");
	}
	return 1;
}

// ----------------------------------------------
// Atendimento & Report

CMD:atendimento(playerid, params[])
{
	if (isnull(params)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /atendimento (assunto)");
	
	if (!Player_Logado(playerid)) 
		return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não está logado no servidor.");

	if (Attendance_GetPlayer(playerid) != INVALID_PLAYER_ID) 
		return SendClientMessage(playerid, -1, "Você está sendo atendido. Use /terminar atendimento.");
	
	if (Admin_GetNivel(playerid) || Helper_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não pode solicitar atendimento!");
	
	if (Report_GetValid(playerid) || Attendance_GetValid(playerid)) 
		return SendClientMessage(playerid, -1, "Você fez uma solicitação de report ou atendimento aguarde atenderem.");

	format(MEGAString, sizeof MEGAString,
		""C_WHITE"Você está prestes a solicitar um atendimento administrativo\n\n\
		Seu nick: "C_GRAY"%s\n\
		"C_WHITE"Assunto do atendimento: "C_BURNED_YELLOW"%s\n\n\
		"C_RED"OBS: "C_GRAY"Solicite atendimento para assuntos sérios, para emergências use /emergencia ou /reportar,\n\
		caso contrario você será devidamente punido pela administração do servidor.",
	PlayerName[playerid], params);

	inline D_RequestAttendance(did, ddialogid, dresponse, dlistitem, string:dtext[])
	{
		#pragma unused did, ddialogid, dlistitem

		if (!dresponse)
			return 1;

		if (strlen(dtext) < 5 || strlen(dtext) > 32)
			return SendClientMessage(playerid, -1, "O assunto deve conter de 5 a 32 caracteres!");

		if (gettime() < GetPVarInt(playerid, #VarFlood14))
			return SendClientMessage(playerid, -1, #Você precisa esperar 15 segundos para solicitar atendimento novamente);

		SetPVarInt(playerid, #VarFlood14, gettime() + 15);
		Attendance_Open(playerid, dtext);

		return 1;
	}
	Dialog_ShowCallback(playerid, using inline D_RequestAttendance, DIALOG_STYLE_INPUT, ""C_GRAY"Solicitar atendimento", MEGAString, "Continuar", "Cancelar");

	return 1;
}
alias:("sos", "relato", "relatorio", "duvida")

CMD:atender(playerid, params[])
{
	if (!(Admin_GetNivel(playerid) || Helper_GetNivel(playerid)))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) goto skip;

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip:
	new idplayer;
	if (sscanf(params, "u", idplayer)) {
	    Attendance_List(playerid);
		return SendClientMessage(playerid, -1, "Modo de uso: /atender (id do jogador) | Escolha um jogador da lista.");
	}
	
	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (!Attendance_GetValid(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não solicitou nenhum atendimento.");

	if (Attendance_GetPlayer(idplayer) != INVALID_PLAYER_ID) 
		return SendClientMessage(playerid, -1, "O jogador selecionado já está sendo atendido.");
	
	if (Report_GetValid(playerid) || Attendance_GetValid(playerid))
		return SendClientMessage(playerid, -1, "Você já está em atendimento, use /terminar (report ou atendimento).");

	if (idplayer == playerid) 
		return SendClientMessage(playerid, -1, "Você não pode atender você mesmo!");
  	
	Attendance_ToMeet(playerid, idplayer);
	return 1;
}

CMD:reportar(playerid, params[])
{
	new idplayer, reason[32];
	if (sscanf(params, "us[32]", idplayer, reason)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /reportar (id do acusado) (motivo)");

	if (strlen(params) < 5 || strlen(params) > 32)
		return SendClientMessage(playerid, -1, "O motivo deve conter de 5 a 32 caracteres!");
	
	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O acusado não está conectado ou logado no servidor.");

	if (Attendance_GetPlayer(playerid) != INVALID_PLAYER_ID) 
		return SendClientMessage(playerid, -1, "Você está sendo atendido.");

	if (Report_GetPlayer(playerid) != INVALID_PLAYER_ID) 
		return SendClientMessage(playerid, -1, "Você está sendo atendido em um report.");
	
	if (Report_GetValid(playerid) || Attendance_GetValid(playerid))
		return SendClientMessage(playerid, -1, "Você fez uma solicitação de report ou atendimento aguarde atenderem.");

	if (Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Você não pode fazer um report.");

	Report_Open(playerid, idplayer, reason);

	return true;
}
alias:reportar("report")

CMD:areport(playerid, params[])
{
	if (!Admin_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (Founders_GetList(playerid)) goto skip;

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	skip:
	new idplayer;
	if (sscanf(params, "u", idplayer)) {
	    Report_List(playerid);
		return SendClientMessage(playerid, -1, "Modo de uso: /areport (id do jogador) | Escolha um jogador da lista.");
	}
	
	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O denunciante não está conectado/logado no servidor.");

	if (!Report_GetValid(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não fez nenhum report ou já foi atendido.");

	if (Report_GetPlayer(idplayer) != INVALID_PLAYER_ID) 
		return SendClientMessage(playerid, -1, "O report selecionado já está sendo atendido.");

	if (Report_GetValid(playerid) || Attendance_GetValid(playerid))
	    return SendClientMessage(playerid, -1, "Você já está em atendimento, use: /terminar (report ou atendimento).");

	if (idplayer == playerid)
		return SendClientMessage(playerid, -1, "Você não pode atender você mesmo!");

	Report_ToMeet(playerid, idplayer);
	return 1;
}

CMD:terminar(playerid, params[])
{
	if (isnull (params)) {
	    SendClientMessage(playerid, -1, "Modo de uso: /terminar (nome)");
		return SendClientMessage(playerid, COLOR_GRAY, "NOMES DISPONIVEIS: atendimento, report");
	}
	if (!strcmp(params, "atendimento", true)) {
		new idplayer = Attendance_GetPlayer(playerid);
		if (idplayer != INVALID_PLAYER_ID)
			Attendance_Finish(playerid, idplayer);
	}
	else if (!strcmp(params, "report", true)) {
		new idplayer = Report_GetPlayer(playerid);
		if (idplayer != INVALID_PLAYER_ID)
			Report_Finish(playerid, idplayer);
	}
	return 1;
}

CMD:removeratendimento(playerid, params[])
{
	if (!Admin_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer, result[30];
	if (sscanf(params, "us[30]", idplayer, result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /removeratendimento (id/nick do jogador) (motivo)");
		
	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (strlen(result) < 3 || strlen(result) > 30) 
		return SendClientMessage(playerid, -1, "O motivo deve conter de 3 a 30 caracteres, crie abreviação.");

	if (!Attendance_GetValid(idplayer))
		return SendClientMessage(playerid, -1, "Este jogador não solicitou um atendimento ou já está sendo atendido.");

	Attendance_SetValid(idplayer, false);
	SendMsgF(idplayer, COLOR_ATENDIMENTO, "<< Atendimento >> %s, %s cancelou sua solicitação pelo motivo: %s.", Staff_GetPositionName(playerid), PlayerName[playerid], result);
	
	new string[128];
	format(string, sizeof(string), "AdmCmd: %s cancelou o atendimento de %s. Motivo: %s", PlayerName[playerid], PlayerName[idplayer], result);
	Staff_ChatToAll(COLOR_LIGHTRED, string);
	Discord_SendMessage(string, Channel_Attendance);
	return 1;
}
alias:removeratendimento("ratendimento")

CMD:removerreport(playerid, params[])
{
	if (!Admin_GetNivel(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idplayer, result[30];
	if (sscanf(params, "us[30]", idplayer, result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /removerreport (id/nick do jogador) (motivo)");
		
	if (!Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (strlen(result) < 3 || strlen(result) > 30) 
		return SendClientMessage(playerid, -1, "O motivo deve conter de 3 a 30 caracteres, crie abreviação.");

	if (!Report_GetValid(idplayer))
		return SendClientMessage(playerid, -1, "Este jogador não solicitou um report ou já está sendo atendido.");
	
	Report_SetValid(idplayer, false);
	SendMsgF(idplayer, COLOR_REPORT, "<< Report >> %s, %s cancelou sua solicitação pelo motivo: %s.", Staff_GetPositionName(playerid), PlayerName[playerid], result);
	
	new string[128];
	format(string, sizeof(string), "[REPORT]: %s, %s cancelou o report de %s. Motivo: %s", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[idplayer], result);
	Staff_ChatToAll(COLOR_LIGHTRED, string);
	Discord_SendMessage(string, Channel_Attendance);
	return 1;
}
alias:removerreport("rreport")