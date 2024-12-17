#include <fly>

// ----------------------------------------------------------
stock Help_StaffCommands(playerid) {
    if (Admin_GetNivel(playerid))
        SendClientMessage(playerid, COLOR_ADMIN, "** Staff: "C_WHITE"/aa (Comandos gerais) /a (Chat administrativo) /jogar (Entrar/sair modo serviço)");

    else if (Helper_GetNivel(playerid))
        SendClientMessage(playerid, COLOR_HELPER, "** Helper: "C_WHITE"/aa (Comandos gerais) /a (Chat administrativo) /jogar (Entrar/sair modo serviço)");
}

stock GetMetodoDonate(metodo)
{
	new InfoMetodoDonate[25];

	switch (metodo)
	{
		case 1: 	InfoMetodoDonate = "{31A0F4}Caixa Econômica";
		case 2: 	InfoMetodoDonate = "{02BD5A}Sicredi";
		case 3: 	InfoMetodoDonate = "{D81504}Santander";
		case 4: 	InfoMetodoDonate = "{1A7805}PagSeguro";
		case 5: 	InfoMetodoDonate = "{1E45D7}PayPal";
		case 6: 	InfoMetodoDonate = "{38A8CE}Mercado Pago";
		case 7: 	InfoMetodoDonate = "{33D87A}PicPay";
		case 9: 	InfoMetodoDonate = "{EF9013}BitCoin";
		case 10: 	InfoMetodoDonate = "{FFF000}Banco do Brasil";
		case 11: 	InfoMetodoDonate = "{A93C3C}Pagamento";
		case 12: 	InfoMetodoDonate = "{33CCFF}Pix";
		case 13:	InfoMetodoDonate = "{00FFFF}PaySafeCard";
		case 14:	InfoMetodoDonate = "{C0C0C0}Revolut";
		case 15:	InfoMetodoDonate = "{B22222}MB Way";
		case 16:	InfoMetodoDonate = "{00FF00}Google Pay";
		case 17:	InfoMetodoDonate = "{DED356}Sorteio";

		case 50:	InfoMetodoDonate = "{3CB371}Mapper";

		default: 	InfoMetodoDonate = "{DED356}Sorteio";
	}
	return InfoMetodoDonate;
}

new Cash_Promo;

stock Cash_GetPromo()
	return Cash_Promo;

stock Cash_SetPromo(value)
	Cash_Promo = value;

CMD:ativarpromocao(playerid, params[])
{
	if (!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Você não está logado.");
		
	if (!Founders_GetList(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new percent,
		string[200];

	if (sscanf(params, "d", percent))
		return SendClientMessage(playerid, -1, "Modo de uso: /ativarpromocao (porcentagem)");

	if (percent < 0 || percent > 100)
		return SendClientMessage(playerid, -1, "Você deve digitar uma porcentagem de 0 á 100, onde 0 é para desativar.");

	if (percent == 0) {
		#if defined _inc_discord_connector
			format(string, sizeof(string), ":money_bag: **PROMOÇÃO DE CASH!** -> Finalizada!! Ohhhhnnnnnnn ;( ;[ :money_bag:");
			Discord_SendMessage(string, Channel_BatePapo);
		#endif

		format(string, sizeof(string), "CASH:{FFFFFF} %s, %s {FF0000}desativou{FFFFFF} um desconto nas compras de cash.", Staff_GetPositionName(playerid), PlayerName[playerid], percent);
	} else {
		#if defined _inc_discord_connector
			format(string, sizeof(string), ":money_bag: **PROMOÇÃO DE CASH!** -> BÔNUS DE %d EM COMPRAS DE CASH :money_bag: Acesse: "SERVER_SITE" @everyone @here");
			Discord_SendMessage(string, Channel_BatePapo);
		#endif

		format(string, sizeof(string), "CASH:{FFFFFF} %s, %s {00FF00}ativou{FFFFFF} um desconto de +%d por cento na compra de cash.", Staff_GetPositionName(playerid), PlayerName[playerid], percent);
	}
	SendClientMessageToAll(COLOR_GREEN, string);

	Cash_Promo = percent;

	return 1;
}

stock AtivarCash(const ativador[], const cliente[], quantity, metodo)
{
	new additional = Cash_GetPromo();
	if (additional > 0) {
		additional = floatround(floatmul(floatdiv(additional, 100.0), quantity));
	}

	new value = (quantity + additional);

	new idPlayer = GetPlayerID(cliente);
	if (Player_Logado(idPlayer)) 
	{
		if (Admin_GetNivel(idPlayer))
			additional += floatround(floatmul(floatdiv(30.0, 100.0), quantity));

		value = Player_GetCash(idPlayer);
		value += (quantity + additional);

		Player_SetCash(idPlayer, value);
	} else {
		new query[200];

		mysql_format(MySQL_Handle, query, sizeof query, "UPDATE `player` SET `cash` = `cash` + %d WHERE `nome` = '%e'", value, cliente);
		mysql_tquery(MySQL_Handle, query);
	}

	new string[200];

	if (metodo == 50) {
		format(string, sizeof string, "%s » {FBFAFA}%s %s {FBFAFA}recebeu pagamento de Mapper ({548EEB}%s {FBFAFA}cash).", GetMetodoDonate(metodo), cliente, Player_Logado(idPlayer) ? ("{38D78F}[online]") : ("{ED4550}[offline]"), getFormatText(quantity + additional));
		Staff_ChatToAll(-1, string);
	}
	else if (metodo != 99) {
		format(string, sizeof string, "%s » {FBFAFA}%s %s {FBFAFA}recebeu ativação ({548EEB}%s {FBFAFA}cash).", GetMetodoDonate(metodo), cliente, Player_Logado(idPlayer) ? ("{38D78F}[online]") : ("{ED4550}[offline]"), getFormatText(quantity + additional));
		SendClientMessageToAll(-1, string);

		#if defined _inc_discord_connector
			format(string, sizeof(string), ":gem: **%s** recebeu ativação de **%s** cash. Compre cash pelo painel: "SERVER_SITE"", cliente, getFormatText(quantity + additional));
			Discord_SendMessage(string, Channel_BatePapo);
		#endif
	} else {
		format(string, sizeof string, "SORTEIO DISCORD » {FBFAFA}%s %s {FBFAFA}recebeu ({548EEB}%s {FBFAFA}cash) por ter sido sorteado.", cliente, Player_Logado(idPlayer) ? ("{38D78F}[online]") : ("{ED4550}[offline]"), getFormatText(quantity + additional));
		SendClientMessageToAll(COLOR_DISCORD, string);

		#if defined _inc_discord_connector
			format(string, sizeof(string), ":gem: **%s** recebeu **%s** cash. Através do Sorteio de Cash pelo Discord. #vincule-discord.", cliente, getFormatText(quantity + additional));
			Discord_SendMessage(string, Channel_BatePapo);
		#endif
	}

	format(string, sizeof string, "(Cash): %s ativou $%s cash para %s | método: %d", ativador, getFormatText(quantity + additional), cliente, metodo);
	server_log("cashativacao", string);
}

// ----------------------------------------------------------
stock Dialog_SendMessagePrivate(playerid, idplayer) {
	inline DialogMessagePrivate(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, listitem

		if (response) {
			if (!Player_Logado(idplayer)) 
				return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

			new string[128];

			format(string,sizeof(string),"%d %s", idplayer, inputtext);
			callcmd::par(playerid, string);

			return 1;
		}
    }
	Dialog_ShowCallback(playerid, using inline DialogMessagePrivate,
        DIALOG_STYLE_INPUT, "Enviando mensagem privada...", "Digite seu texto abaixo:", "Enviar", "Cancelar"
    );
	return 1;
}

CALLBACK:OnInfoConta(playerid) 
{
	new row_count = MYSQL_GetRowsCount(), string[90];
	if (row_count == 0)
		return SendClientMessage(playerid, -1, "Essa conta não está registrada no servidor !");

	MEGAString[0] = EOS;

	format(string, sizeof(string), "Informações da conta: %s\n\n", MYSQL_GetString(0, "nome"));
	strcat(MEGAString, string);
	format(string, sizeof(string), "Nível: %d\n", MYSQL_GetInt(0, "level"));
	strcat(MEGAString, string);
	format(string, sizeof(string), "Nível de admin: %d\n", MYSQL_GetInt(0, "admin_nivel"));
	strcat(MEGAString, string);
	format(string, sizeof(string), "Nível de helper: %d\n", MYSQL_GetInt(0, "helper_nivel"));
	strcat(MEGAString, string);
	format(string, sizeof(string), "E-mail: %s\n", MYSQL_GetString(0, "e-mail"));
	strcat(MEGAString, string);
	format(string, sizeof(string), "VIP: %d\n", MYSQL_GetInt(0, "vip_nivel"));
	strcat(MEGAString, string);
	format(string, sizeof(string), "Horas jogadas: %d\n", MYSQL_GetInt(0, "horas_jogadas"));
	strcat(MEGAString, string);
	format(string, sizeof(string), "Dinheiro: %s\n", getFormatText(MYSQL_GetInt(0, "dinheiro")));
	strcat(MEGAString, string);
	format(string, sizeof(string), "Banco: %s\n", getFormatText(MYSQL_GetInt(0, "dinheiro_banco")));
	strcat(MEGAString, string);
	format(string, sizeof(string), "Ouros: %s\n", getFormatText(MYSQL_GetInt(0, "ouros")));
	strcat(MEGAString, string);
	format(string, sizeof(string), "Cash: %s\n", getFormatText(MYSQL_GetInt(0, "cash")));
	strcat(MEGAString, string);
	format(string, sizeof(string), "Ultimo Login: %s\n", MYSQL_GetString(0, "ultimo_login"));
	strcat(MEGAString, string);

	ShowPlayerDialog(playerid, 8724, DIALOG_STYLE_MSGBOX, "Informações da conta", MEGAString, "OK","");
	return 1;
}

stock carryPlayerTeamViewer(playerid, idPlayer)
{
    new Float:playerPos[3];

	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
	SetPlayerPos(idPlayer, playerPos[0], playerPos[1], playerPos[2]);

    new string[132];

	format(string, sizeof(string), "AdmCmd: %s puxou o jogador %s para passar TeamViewer.", PlayerName[playerid], PlayerName[idPlayer]);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

	format(string, 128, "* %s foi puxado para passar TeamViewer.", PlayerName[idPlayer]);
	SendClientMessageInRange(30.0, idPlayer, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

	MEGAString[0] = EOS;

	strcat(MEGAString, "						  {E04848}LEIA COM ATENÇÃO\n");

	format(string, 128, "\t\t{FFFFFF}Você foi puxado pelo {009AD6}Administrador %s {FFFFFF}para ter seu computador {E04848}analisado.\n\n", PlayerName[playerid]);
	strcat(MEGAString, string);

	strcat(MEGAString, "{FFFFFF}Você deve passar seu ID e Senha do {009ad6}TeamViewer {FFFFFF}para o Administrador dentro de {E04848}5 minutos.\n\n\n");

	strcat(MEGAString, "{e04848}* Caso você desconecte do jogo, seja para relogar ou qualquer motivo, será banido imediatamente.\n\n\n");

	strcat(MEGAString, "{FFFFFF}Caso você não tenha o {009AD6}TeamViewer, {FFFFFF}instale-o acessando o site {009AD6}www.teamviewer.com\n");

	strcat(MEGAString, "{FFFFFF}Após baixar e instalar, abra-o, você terá seu {009AD6}ID e Senha, {FFFFFF}quais você deve passar pelo chat para o {009AD6}Administrador.\n");

	strcat(MEGAString, "{E04848}* Você deve baixar a última versão, gratuita e de uso pessoal.");

	ShowPlayerDialog(idPlayer, 0, DIALOG_STYLE_MSGBOX, "{009ad6}» Análise de Hack's", MEGAString, "OK", "");
}

CALLBACK:OnPlayerInventoryFound(playerid, const nickname[]) {
	new slots[MAX_ITENS_INVENTARIO],
		string[128],
		num = MYSQL_GetRowsCount();

	for(new i = 0; i < MAX_ITENS_INVENTARIO; i++)
		slots[i] = -1;

	for(new i = 0; i < num; i++) {
		slots[MYSQL_GetInt(i, "slot")] = i;
	}

	MEGAString[0] = EOS;
	strcat(MEGAString, "ID Nome do item\tQuantidade\n");

	for(new i = 0; i < MAX_ITENS_INVENTARIO; i++) {
		if(slots[i] != -1)
			FormatCat(MEGAString, "%02d %s\t%d\n", i, MYSQL_GetString(slots[i], "nome"), MYSQL_GetInt(slots[i], "quantidade"));
		else
			FormatCat(MEGAString, "{AAAAAA}%02d [ Vazio ]\n", i);
	}

	format(string, sizeof string, "Lista de itens de: %s [%d/%d]", nickname, num, MAX_ITENS_INVENTARIO);

	if(Dev_GetNivel(playerid))
		ShowPlayerDialog(playerid, 11254, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Gerenciar", "Fechar");
	else
		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Fechar", "");

	return 1;
}


stock ShowAlertInvalidNick(playerid, adminid, const errorMessage[] = "") {
	new string[128];

	format(
		MEGAString, sizeof(MEGAString),
		"{FFFFFF}Você está sendo notificado pelo administrador "C_ADMIN"%s {FFFFFF}por estar usando um {FF0000}NICK INDEVIDO{FFFFFF}.\n\n\
		Selecione um nick legível, como:\n\
		- BatmanRX, matheus64, tiago_oliveira, Seu_Madruga.\n\n\
		São {FF0000}proibidos {FFFFFF}nicks:\n\
		- que contenham somente números, símbolos ou flood.\n\
		- que sejam ofensivos ou difamatórios.\n\
		- que contenham nome de famílias criadas no servidor sem ser membro.\n\
		- que contenham Staff ou Helper.\n\n\
		Informe o seu {00AA00}novo nick {FFFFFF}para trocá-lo agora.",
		PlayerName[adminid]
	);

	// if (IsAndroidPlayer(playerid)) {
	// 	RemoveAccents(MEGAString);
	// }

	if(strlen(errorMessage) > 0) {
		strcat(MEGAString, "\n\n{FF0000}ERRO: {FFFFFF}");
		strcat(MEGAString, errorMessage);
	}

	inline D_InvalidNick(dlid, dldialogid, dlresponse, dllistitem, string:dltext[])
	{
		#pragma unused dlid, dldialogid, dltext, dllistitem
		if (!dlresponse) 
			return true;

		else if (!PlayerIsNickValid(dltext)) {
			ShowAlertInvalidNick(dlid, adminid, "Você digitou um nick inválido, tente outro, use entre 5 a 20 caracteres.");
			return 1;
		}

		else if (strcmp(PlayerName[dlid], dltext, true) == 0) {
			ShowAlertInvalidNick(dlid, adminid, "Você precisa usar um nick diferente do atual.");
			return 1;
		}

		else if (DoesPlayerExists(dltext)) {
			ShowAlertInvalidNick(dlid, adminid, "O nick que você escolheu não está disponível.");
			return 1;
		}

		format(string, sizeof(string), "AdmAviso: %s(%d) mudou o nick indevido para %s, notificado por %s.", PlayerName[dlid], dlid, dltext, PlayerName[adminid]);
		Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO); 
		server_log("mudarnick", string);

		SendMsgF(dlid, COLOR_LIGHTBLUE, "Você alterou seu nick para %s.", dltext);

		ChangePlayerNick(dlid, dltext);
		return 1;
	}
    Dialog_ShowCallback(playerid, using inline D_InvalidNick, DIALOG_STYLE_INPUT, ""C_GRAY"Alerta de nick indevido", MEGAString, "Salvar", "");
	return 1;
}

// ----------------------------------------------------------------------------------
// Função: Senha administrativa

stock SalvarSenhaAdmin() {
	SaveConfig("SENHA_ADMIN", SenhaAdministracao);
}

stock LoadSenhaAdmin() {
	format(SenhaAdministracao, sizeof(SenhaAdministracao), LoadConfig("SENHA_ADMIN"));
	return SenhaAdministracao;
}

// ----------------------------------------------------------------------------------
// Função: Música de login

static linkMusicLogin[255];
stock Login_PlayMusic(playerid) {
    if (strlen(linkMusicLogin) > 5)
        PlayAudioStreamForPlayer(playerid, linkMusicLogin);
}

stock Login_SetMusic(const url[]) {
    format(linkMusicLogin, sizeof(linkMusicLogin), url);
    Login_SaveMusic();
}

static Login_SaveMusic() {
    SaveConfig("MUSICA_LOGIN", linkMusicLogin);
}

stock Login_LoadMusic() {
    format(linkMusicLogin, sizeof(linkMusicLogin), LoadConfig("MUSICA_LOGIN"));
}

// ----------------------------------------------------------------------------------
// Função: Cadeia administrativa

stock AgendarCadeia(admin[], jailedPlayer[], denunciator[], reason[])
{
	new query[300];

	/* GET JAILED PLAYER INFO (prisao_admin, jailed_time, jail_time_agended, dinheiro_banco) */
    mysql_format(MySQL_Handle, query, sizeof query, "SELECT prisao_admin, jailed_time, jail_time_agended, dinheiro_banco FROM `player` WHERE nome='%s' LIMIT 1;", jailedPlayer);
    mysql_query(MySQL_Handle, query); 

	/* check if row exists */
	if (cache_num_rows()){
		new qtdJails, jailTime, jailTimeAgended, bankAmount;
		cache_get_value_int(0, "prisao_admin", qtdJails);
		cache_get_value_int(0, "jailed_time", jailTime);
		cache_get_value_int(0, "jail_time_agended", jailTimeAgended);
		cache_get_value_int(0, "dinheiro_banco", bankAmount);

		new multiplierTime = 11;
			
		new
			allTimeJailed = jailTime + jailTimeAgended, /* GET CURRENT JAIL_TIME AND JAIL_TIME_AGENDED */
			gravityTime = (qtdJails*multiplierTime) + 10,
			setTimeJailed = allTimeJailed += gravityTime * 60, /* SET TIME JAIL */
			finePaid = floatround((bankAmount * 0.02) * qtdJails),  /* GET FINE PAID */
			string[255]
		;
		
		format(string, sizeof(string), "(Cadeia Admin): %s agendou +%d min de cadeia para %s, denunciante %s, motivo: %s.", admin, gravityTime, jailedPlayer, denunciator, reason);
		SendClientMessageToAll(COLOR_LIGHTRED, string);

		format(string, sizeof(string), "%s agendou +%d min para %s, denunciante %s, motivo: %s [$%d]", admin, gravityTime, jailedPlayer, denunciator, reason, finePaid);
		server_log("cadeia", string);
			
		new sql_string[320];
		mysql_format(MySQL_Handle, sql_string, sizeof(sql_string), "UPDATE player SET prisao_admin=prisao_admin+1, dinheiro_banco=dinheiro_banco-%d, jailed_id=9, jailed_time=%d, jail_time_agended=%d, jail_agended=1, jail_agendou='%s', jail_motivo='%s' WHERE nome='%s'",
			finePaid, setTimeJailed, setTimeJailed, admin, reason, jailedPlayer);
		mysql_tquery(MySQL_Handle, sql_string);

		SumConfigInt("COFRE_ADMIN", finePaid);
	}
}

stock Cadeia(admin[], jailedPlayerID, denunciator[], reason[])
{
	new prisoesadmin = Player_GetJailsAdmin(jailedPlayerID);

	prisoesadmin++;

	Player_SetJailsAdmin(jailedPlayerID, prisoesadmin);

	new multiplierTime;
		
	if (Player_GetJailsAdmin(jailedPlayerID) <= 10) {
		multiplierTime = 11;
	} else {
		multiplierTime = 22;
	}
	
	new
		moneybank = Player_GetMoneyBank(jailedPlayerID),
		gravityTime = (prisoesadmin*multiplierTime) + 10,
		setTimeJailed = Player_GetJailTime(jailedPlayerID),
		finePaid = floatround((moneybank * 0.01) * prisoesadmin),
		string[255]
	;

	setTimeJailed += gravityTime * 60;

	format(string, sizeof(string), "(Cadeia Admin): %s puniu %s por %d min, denunciante %s, motivo: %s.", admin, PlayerName[jailedPlayerID], gravityTime, denunciator, reason);
	SendClientMessageToAll(COLOR_LIGHTRED, string);

	format(string, sizeof(string), "%s puniu %s por %d min, denunciante %s, motivo: %s [$%d]", admin, PlayerName[jailedPlayerID], gravityTime, denunciator, reason, finePaid);
	server_log("cadeia", string);

	MEGAString[0] = EOS;

	strcat(MEGAString, "\n		{FF6347}CADEIA ADMINISTRATIVA\n\n");

	format(string, 128, "{7D8084}Você foi condenado pelo administrador: {F64CCA}%s\n", admin);
	strcat(MEGAString, string);
	format(string, 128, "{7D8084}O seu tempo de punição é de {7D8084}%d {7D8084}minutos\n", gravityTime);
	strcat(MEGAString, string);
	format(string, 128, "{7D8084}Você pagou multa de {00AA00}$%s {7D8084}para o jogador: {7D8084}%s\n", getFormatText(finePaid), denunciator);
	strcat(MEGAString, string);
	format(string, 128, "{7D8084}Você tem {FF0000}%d {7D8084}cadeias, a partir de 20 você começa levar banimentos\n", prisoesadmin, denunciator);
	strcat(MEGAString, string);

	strcat(MEGAString, "\n		{FEE73A}DÚVIDAS FREQUENTES\n");

	strcat(MEGAString, "\n{7D8084}PERGUNTA: {DBDCE0}Como eu vejo as regras do servidor?\n");
	strcat(MEGAString, "{49E468}RESPOSTA: {DBDCE0}Acesse o fórum: "SERVER_SITE"\n");

	strcat(MEGAString, "\n{7D8084}PERGUNTA: {DBDCE0}Eu fui punido injustamente, como proceder?\n");
	strcat(MEGAString, "{49E468}RESPOSTA: {DBDCE0}Abra uma denúncia no painel com o nome do administrador que te puniu\n");

	strcat(MEGAString, "\n{7D8084}PERGUNTA: {DBDCE0}Como funciona o tempo de punição?\n");
	strcat(MEGAString, "{49E468}RESPOSTA: {DBDCE0}O tempo é de acordo com a quantidade de cadeias em seu (/rg)\n");

	strcat(MEGAString, "\n{DBDCE0}Quando terminar de ler digite {00FF00}ENTENDI {DBDCE0}para fechar.\n");

	ShowPlayerDialog(jailedPlayerID, 450, DIALOG_STYLE_INPUT, "{7D8084}Informações da cadeia administrativa", MEGAString, "Confirmar", "");

	Player_SetCadeia(jailedPlayerID, 9, setTimeJailed, admin, reason, 999);

	moneybank -= finePaid;
	Player_SetMoneyBank(jailedPlayerID, moneybank);

	ResetPlayerWeapons(jailedPlayerID);

	SpawnPlayer(jailedPlayerID);
	PlayerPlaySound(jailedPlayerID, 31202, 0.0, 0.0, 0.0);

	SumConfigInt("COFRE_ADMIN", finePaid);
}