
#include <YSI_Coding\y_hooks>

// #include <vip_entry>
#include <vip_functions>
#include <vip_cmds>

stock Bonus_SetVIP(playerid, socio_nivel, dias)
{
	if (!PlayerInfo[playerid][pPegouVIP]) 
	{
		GiveVipPresente(playerid, socio_nivel, dias);

		new vip_nivel = Player_GetVIP(playerid);

		if (vip_nivel) {
			SendMsgF(playerid, SERVER_COLOR_PRIMARY, "[BONUS]: "C_WHITE"%s, adicionamos "C_GREEN"%d "C_WHITE"dias de {%s}%s "C_WHITE"em sua conta! "C_CYAN"/vip.", PlayerName[playerid], dias, GetVipColor(playerid), VIP_GetName(vip_nivel));
		} else {
			SendMsgF(playerid, SERVER_COLOR_PRIMARY, "[BONUS CADASTRO]: "C_WHITE"%s, ativamos "C_GREEN"%d "C_WHITE"dias de {%s}%s "C_WHITE"em sua conta! "C_CYAN"/vip.", PlayerName[playerid], dias, GetVipColor(playerid), VIP_GetName(vip_nivel));
		}
		PlayerInfo[playerid][pPegouVIP] = true;

		new log_query[128];
		mysql_format(MySQL_Handle, log_query, sizeof(log_query), "UPDATE `player` SET `vip_pegou` = '1' WHERE id = %d", Player_GetAccountID(playerid));
		mysql_tquery(MySQL_Handle, log_query);
	}
}

stock showDialogGiveSocio(playerid, meses, levelAtivado, dinheiroAtivado)
{
	new string[128];
    MEGAString[0] = EOS;

	new vip_nivel = Player_GetVIP(playerid);

    format(string, sizeof string, "\n{7D8084}Você ativou os benefícios de:		{%s}%s\n", GetVipColor(playerid), VIP_GetName(vip_nivel)), strcat(MEGAString, string);

	strcat(MEGAString, "\n{FFBB00}Ativação:\n\n");

    format(string, sizeof string, "{7D8084}Ativou			{00FF00}%d mês(es)\n", meses), strcat(MEGAString, string);
    format(string, sizeof string, "{7D8084}Recebeu			{DBDCE0}%d níveis\n", levelAtivado), strcat(MEGAString, string);
    format(string, sizeof string, "{7D8084}Recebeu			{00AA00}$%s\n", getFormatText(dinheiroAtivado)), strcat(MEGAString, string);

	switch (Player_GetVIP(playerid))
	{
		case 1:
		{
			strcat(MEGAString, "\n{FFBB00}Permissões e direitos:\n");

			strcat(MEGAString, "{7D8084}Compra de fazendas		{49E468}1\n");
			strcat(MEGAString, "{7D8084}Compra de veículos		{49E468}2\n");
			strcat(MEGAString, "{7D8084}Usar chat-sócio			{DBDCE0}Comando /s\n");
			strcat(MEGAString, "{7D8084}Usar menu sócio		{DBDCE0}Comando /menu\n");
		}
		case 2, 5, 6:
		{
			strcat(MEGAString, "{7D8084}Recebeu			{FEE73A}Caixa Surpresa Gold {9C9C9C}(1 unidade)\n");

			strcat(MEGAString, "\n{FFBB00}Ganhos por pagamento horário (Payday):\n\n");

	  		strcat(MEGAString, "{7D8084}Respeitos Payday		{49E468}3\n");

			strcat(MEGAString, "\n{FFBB00}Permissões e direitos:\n");

			strcat(MEGAString, "{7D8084}Compra de fazendas		{49E468}1\n");
			strcat(MEGAString, "{7D8084}Compra de veículos		{49E468}3\n");
			strcat(MEGAString, "{7D8084}Compra de casas		{49E468}3\n");
			strcat(MEGAString, "{7D8084}Compra de comércio		{49E468}3\n");
			strcat(MEGAString, "{7D8084}Montar caixas de itens		{49E468}3\n");
			strcat(MEGAString, "{7D8084}Usar kit-socio			{DBDCE0}Qualquer local\n");
			strcat(MEGAString, "{7D8084}Usar chat-vip			{DBDCE0}Comando /v\n");
			strcat(MEGAString, "{7D8084}Usar chat-sócio			{DBDCE0}Comando /s\n");
			strcat(MEGAString, "{7D8084}Não precisa de nível		{DBDCE0}Para comprar casa\n");
			strcat(MEGAString, "{7D8084}Usar menu sócio		{DBDCE0}Comando /menu\n");
			strcat(MEGAString, "{7D8084}Usar jetpack			{DBDCE0}Comando /jetpack\n");
			strcat(MEGAString, "{7D8084}Usar /repararvip		{DBDCE0}Qualquer local\n");
			strcat(MEGAString, "{7D8084}Usar /abastecervip		{DBDCE0}Qualquer local\n");
			strcat(MEGAString, "{7D8084}Chat local			{DBDCE0}Cor diferenciada\n");
		}
		case 7:
		{
		    strcat(MEGAString, "{7D8084}Recebeu			{017bff}Caixa Surpresa Supreme {9C9C9C}(1 unidade)\n");

			strcat(MEGAString, "\n{FFBB00}Ganhos por pagamento horário (Payday):\n\n");

	      	strcat(MEGAString, "{7D8084}Respeitos Payday		{49E468}4\n");

			strcat(MEGAString, "\n{FFBB00}Permissões e direitos:\n");

			strcat(MEGAString, "{7D8084}Compra de fazendas		{49E468}2\n");
			strcat(MEGAString, "{7D8084}Compra de veículos		{49E468}4\n");
			strcat(MEGAString, "{7D8084}Compra de casas		{49E468}4\n");
			strcat(MEGAString, "{7D8084}Compra de comércio		{49E468}4\n");
			strcat(MEGAString, "{7D8084}Montar caixas de itens		{49E468}4\n");
			strcat(MEGAString, "{7D8084}Usar kit-socio			{DBDCE0}Qualquer local\n");
			strcat(MEGAString, "{7D8084}Usar chat-vip			{DBDCE0}Comando /v\n");
			strcat(MEGAString, "{7D8084}Usar chat-sócio			{DBDCE0}Comando /s\n");
			strcat(MEGAString, "{7D8084}Não precisa de nível		{DBDCE0}Para comprar casa\n");
			strcat(MEGAString, "{7D8084}Usar menu sócio		{DBDCE0}Comando /menu\n");
			strcat(MEGAString, "{7D8084}Usar jetpack			{DBDCE0}Comando /jetpack\n");
			strcat(MEGAString, "{7D8084}Usar /repararvip		{DBDCE0}Qualquer local\n");
			strcat(MEGAString, "{7D8084}Usar /abastecervip		{DBDCE0}Qualquer local\n");
			strcat(MEGAString, "{7D8084}Usar /caixinha			{DBDCE0}Qualquer local\n");
			strcat(MEGAString, "{7D8084}Usar /an personalizado		{DBDCE0}Menor pausa de flood\n");
			strcat(MEGAString, "{7D8084}Usar /titulos			{DBDCE0}Exclusivo e o personalizado\n");
			strcat(MEGAString, "{7D8084}Chat local			{DBDCE0}Cor diferenciada\n");
			strcat(MEGAString, "{7D8084}Caixinha Exclusiva		{DBDCE0}Nos presentes (Caixa Surpresa Supreme)\n");
		}
		case 8:
		{
		    //strcat(MEGAString, "{7D8084}Recebeu			{00FF00}Sacola Extreme {9C9C9C}(1 unidade)\n");

			strcat(MEGAString, "\n{FFBB00}Ganhos por pagamento horário (Payday):\n\n");

	     	strcat(MEGAString, "{7D8084}Respeitos Payday		{49E468}5\n");
			strcat(MEGAString, "{7D8084}Juros bancário			{49E468}(receberá o dobro do normal)\n");

			strcat(MEGAString, "\n{FFBB00}Permissões e direitos:\n");

			strcat(MEGAString, "{7D8084}Compra de fazendas		{49E468}2\n");
			strcat(MEGAString, "{7D8084}Compra de veículos		{49E468}4\n");
			strcat(MEGAString, "{7D8084}Compra de casas		{49E468}4\n");
			strcat(MEGAString, "{7D8084}Compra de comércio		{49E468}4\n");
			strcat(MEGAString, "{7D8084}Montar caixas de itens		{49E468}4\n");
			strcat(MEGAString, "{7D8084}Usar kit-socio			{DBDCE0}Qualquer local\n");
			strcat(MEGAString, "{7D8084}Usar chat-vip			{DBDCE0}Comando /v\n");
			strcat(MEGAString, "{7D8084}Usar chat-sócio			{DBDCE0}Comando /s\n");
			strcat(MEGAString, "{7D8084}Não precisa de nível		{DBDCE0}Para comprar casa\n");
			strcat(MEGAString, "{7D8084}Usar menu sócio		{DBDCE0}Comando /menu\n");
			strcat(MEGAString, "{7D8084}Usar jetpack			{DBDCE0}Comando /jetpack\n");
			strcat(MEGAString, "{7D8084}Usar /repararvip		{DBDCE0}Qualquer local\n");
			strcat(MEGAString, "{7D8084}Usar /abastecervip		{DBDCE0}Qualquer local\n");
			strcat(MEGAString, "{7D8084}Usar /caixinha			{DBDCE0}Qualquer local\n");
			strcat(MEGAString, "{7D8084}Usar /an personalizado		{DBDCE0}Menor pausa de flood\n");
			strcat(MEGAString, "{7D8084}Usar /titulos			{DBDCE0}Exclusivo e o personalizado\n");
			strcat(MEGAString, "{7D8084}Chat local			{DBDCE0}Cor diferenciada\n");
			strcat(MEGAString, "{7D8084}Caixinha Exclusiva		{DBDCE0}Nos presentes (Caixa Surpresa Supreme)\n");
			strcat(MEGAString, "{7D8084}2 empregos			{DBDCE0}Pode ter 2 empregos\n");
			strcat(MEGAString, "{7D8084}Caixinha Automatica		{DBDCE0}Pega automatico todo payday\n");
			strcat(MEGAString, "{7D8084}Resistencia			{DBDCE0}Demora o dobro de tempo para ficar com fome/sede\n");
  		}
	}

    format(string, sizeof string, "\n{%s}============================================================\n", GetVipColor(playerid)), strcat(MEGAString, string);

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Ativação de benefícios", MEGAString, "Fechar", "");
}

stock giveSocioComum(para1, meses)
{
 	new string[200],
		levelAtivado = (2 * meses),
		dinheiroAtivado = (PRICE_UP_SOCIOCOMUM * meses)
	;
	Player_SetNivel(para1, Player_GetNivel(para1) + levelAtivado);
	Player_AddMoney(para1, dinheiroAtivado);

	removerDinheiroGoverno(dinheiroAtivado);

	CheckConquista(para1, Conquista_Socio);
	PlayerInfo[para1][pChatVip] = true;

	new query[185];
	mysql_format(MySQL_Handle, string, sizeof string, "SELECT * FROM `player` WHERE `id` = '%d' AND `vip_vencimento` > CURRENT_TIMESTAMP() LIMIT 1", Player_GetAccountID(para1));
	new Cache:serverCache = mysql_query(MySQL_Handle, string);

	new row_count;
	cache_get_row_count(row_count);
	if (row_count && PlayerInfo[para1][pVIP] == SOCIO_COMUM)
	{
	    new rowstring[75];
	    cache_get_value_name(0, "vip_vencimento", rowstring);
	    mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `player` SET `vip_vencimento` = TIMESTAMPADD(MONTH, %d, '%s') WHERE `id` = '%d'", meses, rowstring, Player_GetAccountID(para1));
	}
	else
	{
    	mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `player` SET `vip_vencimento` = TIMESTAMPADD(MONTH, %d, CURRENT_TIMESTAMP()) WHERE `id` = '%d'", meses, Player_GetAccountID(para1));
	}
	cache_delete(serverCache), mysql_tquery(MySQL_Handle, query);

	PlayerInfo[para1][pVIP] = SOCIO_COMUM, showDialogGiveSocio(para1, meses, levelAtivado, dinheiroAtivado);
	CallLocalFunction("OnPlayerSocioActivate", "ii", para1, SOCIO_COMUM);
	ServerLog::("socio", "%s [%d] ativou %s | Meses: %d", PlayerName[para1], Player_GetAccountID(para1), GetDonateRank(para1), meses);
}

stock giveSocioPremium(para1, meses)
{
	new
	 	string[200],
	 	levelAtivado = (4 * meses),
	 	dinheiroAtivado = (PRICE_UP_SOCIOPREMIUM * meses)
	;

	Player_SetNivel(para1, Player_GetNivel(para1) + levelAtivado);
	Player_AddMoney(para1, dinheiroAtivado);

	removerDinheiroGoverno(dinheiroAtivado);

	CheckConquista(para1, Conquista_SocioPremium);
	PlayerInfo[para1][pChatVip] = true;

	new query[185];
	mysql_format(MySQL_Handle, string, sizeof string, "SELECT * FROM `player` WHERE `id` = '%d' AND `vip_vencimento` > CURRENT_TIMESTAMP() LIMIT 1", Player_GetAccountID(para1));
	new Cache:serverCache = mysql_query(MySQL_Handle, string);

    new row_count;
    cache_get_row_count(row_count);
	if (row_count && PlayerInfo[para1][pVIP] == SOCIO_PREMIUM)
	{
	    new rowstring[75];
		cache_get_value_name(0, "vip_vencimento", rowstring);
		mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `player` SET `vip_vencimento` = TIMESTAMPADD(MONTH, %d, '%s') WHERE `id` = '%d'", meses, rowstring, Player_GetAccountID(para1));
	}
	else
	{
		mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `player` SET `vip_vencimento` = TIMESTAMPADD(MONTH, %d, CURRENT_TIMESTAMP()) WHERE `id` = '%d'", meses, Player_GetAccountID(para1));
	}
	cache_delete(serverCache), mysql_tquery(MySQL_Handle, query);

	PlayerInfo[para1][pVIP] = SOCIO_PREMIUM, showDialogGiveSocio(para1, meses, levelAtivado, dinheiroAtivado);
	CallLocalFunction("OnPlayerSocioActivate", "ii", para1, SOCIO_PREMIUM);
	ServerLog::("socio", "%s [%d] ativou %s | Meses: %d", PlayerName[para1], Player_GetAccountID(para1), GetDonateRank(para1), meses);
}

stock giveSocioSupreme(para1, meses)
{
	new
	 	string[200],
	 	levelAtivado = (6 * meses),
	 	dinheiroAtivado = (PRICE_UP_SOCIOSUPREME * meses)
	;

	Player_SetNivel(para1, Player_GetNivel(para1) + levelAtivado);
	Player_AddMoney(para1, dinheiroAtivado);

	removerDinheiroGoverno(dinheiroAtivado);

	CheckConquista(para1, Conquista_SocioPremium);
	PlayerInfo[para1][pChatVip] = true;

	new query[185];
	mysql_format(MySQL_Handle, string, sizeof string, "SELECT * FROM `player` WHERE `id` = '%d' AND `vip_vencimento` > CURRENT_TIMESTAMP() LIMIT 1", Player_GetAccountID(para1));
	new Cache:serverCache = mysql_query(MySQL_Handle, string);

	new row_count;
	cache_get_row_count(row_count);
	if (row_count && PlayerInfo[para1][pVIP] == SOCIO_SUPREME) {

	    new rowstring[75];
	    cache_get_value_name(0, "vip_vencimento", rowstring);
	    mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `player` SET `vip_vencimento` = TIMESTAMPADD(MONTH, %d, '%s') WHERE `id` = '%d'", meses, rowstring, Player_GetAccountID(para1));
	} else {
	    mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `player` SET `vip_vencimento` = TIMESTAMPADD(MONTH, %d, CURRENT_TIMESTAMP()) WHERE `id` = '%d'", meses, Player_GetAccountID(para1));
	}
	cache_delete(serverCache), mysql_tquery(MySQL_Handle, query);

	PlayerInfo[para1][pVIP] = SOCIO_SUPREME, showDialogGiveSocio(para1, meses, levelAtivado, dinheiroAtivado);
	CallLocalFunction("OnPlayerSocioActivate", "ii", para1, SOCIO_SUPREME);
	ServerLog::("socio", "%s [%d] ativou %s | Meses: %d", PlayerName[para1], Player_GetAccountID(para1), GetDonateRank(para1), meses);
}

stock giveSocioExtreme(para1, meses)
{
 	new
	 	string[200],
	 	levelAtivado = (8 * meses),
	 	dinheiroAtivado = (PRICE_UP_SOCIOEXTREME * meses)
	;

	format(string, sizeof string, "Você ativou %d mês(es) de {DC0139}Sócio Extreme {DBDCE0}com {00AA00}$%s {DBDCE0}e {7D8084}%d níveis", meses, getFormatText(dinheiroAtivado), levelAtivado);
	SendClientMessage(para1, 0xDBDCE0FF, string);

	Player_SetNivel(para1, Player_GetNivel(para1) + levelAtivado);
	Player_AddMoney(para1, dinheiroAtivado);

	removerDinheiroGoverno(dinheiroAtivado);

	CheckConquista(para1, Conquista_SocioPremium);
	PlayerInfo[para1][pChatVip] = true;

	new query[185];
	mysql_format(MySQL_Handle, string, sizeof string, "SELECT * FROM `player` WHERE `id` = '%d' AND `vip_vencimento` > CURRENT_TIMESTAMP() LIMIT 1", Player_GetAccountID(para1));
	new Cache:serverCache = mysql_query(MySQL_Handle, string);

    new row_count;
    cache_get_row_count(row_count);
	if (row_count && PlayerInfo[para1][pVIP] == SOCIO_EXTREME)
	{
	    new rowstring[75];
	    cache_get_value_name(0, "vip_vencimento", rowstring);
		mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `player` SET `vip_vencimento` = TIMESTAMPADD(MONTH, %d, '%s') WHERE `id` = '%d'", meses, rowstring, Player_GetAccountID(para1));
	}
	else
	{
	    mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `player` SET `vip_vencimento` = TIMESTAMPADD(MONTH, %d, CURRENT_TIMESTAMP()) WHERE `id` = '%d'", meses, Player_GetAccountID(para1));
	}
	cache_delete(serverCache), mysql_tquery(MySQL_Handle, query);

	PlayerInfo[para1][pVIP] = SOCIO_EXTREME, showDialogGiveSocio(para1, meses, levelAtivado, dinheiroAtivado);
	CallLocalFunction("OnPlayerSocioActivate", "ii", para1, SOCIO_EXTREME);
	ServerLog::("socio", "%s [%d] ativou %s | Meses: %d", PlayerName[para1], Player_GetAccountID(para1), GetDonateRank(para1), meses);
}

stock GiveVipPresente(para1, levelvip, dias)
{
	if (!dias) return false;

	if (PlayerInfo[para1][pVIP] && PlayerInfo[para1][pVIP] != levelvip) {
	    levelvip = PlayerInfo[para1][pVIP];
	}

	new
		string[200],
		query[185]
 	;

	mysql_format(MySQL_Handle, string, sizeof string, "SELECT * FROM `player` WHERE `id` = '%d' AND `vip_vencimento` > CURRENT_TIMESTAMP() LIMIT 1", Player_GetAccountID(para1));
	new Cache:serverCache = mysql_query(MySQL_Handle, string);

    new row_count;
    cache_get_row_count(row_count);
	if (row_count && PlayerInfo[para1][pVIP])
	{
		new rowstring[75];
		cache_get_value_name(0, "vip_vencimento", rowstring);
		mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `player` SET `vip_vencimento` = TIMESTAMPADD(DAY, %d, '%s') WHERE `id` = '%d'", dias, rowstring, Player_GetAccountID(para1));
	}
	else
	{
		mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `player` SET `vip_vencimento` = TIMESTAMPADD(DAY, %d, CURRENT_TIMESTAMP()) WHERE `id` = '%d'", dias, Player_GetAccountID(para1));
	}
	cache_delete(serverCache), mysql_tquery(MySQL_Handle, query);

	PlayerInfo[para1][pVIP] = levelvip;
	PlayerInfo[para1][pChatVip] = true;

	return true;
}

stock Dialog_RefundSocio(playerid)
{
	new vip_days = GetPlayerVipDays(playerid),
		vip_nivel = Player_GetVIP(playerid),
		refund_value,
		days_value;

	switch (Player_GetVIP(playerid)) {
		case SOCIO_COMUM: 		days_value = 100;
		case SOCIO_PREMIUM: 	days_value = 200;
		case SOCIO_SUPREME: 	days_value = 400;
		case SOCIO_EXTREME: 	days_value = 500;
		default: 				days_value = 200;
	}

	MEGAString[0] = EOS;

	if (vip_days >= 7) {
		refund_value = (vip_days * days_value);

		FormatCat(MEGAString, ""C_WHITE"Você irá reembolsar os "C_YELLOW"%d "C_WHITE"dias de {%s}%s\n", GetPlayerVipDays(playerid), GetVipColor(playerid), VIP_GetName(vip_nivel));
		FormatCat(MEGAString, "Valor reembolso (em dias): "C_CASH"%d cash\n", getFormatText(days_value));
		FormatCat(MEGAString, "Valor reembolso (no total): "C_CASH"%s cash\n\n", getFormatText(refund_value));

		strcat(MEGAString, ""C_WHITE"Você precisa escrever "C_GREEN"CONFIRMAR "C_WHITE"para concluir a ação:");
	} else {
		refund_value = 0;
		days_value = 0;

		FormatCat(MEGAString, ""C_WHITE"Você irá reembolsar os "C_YELLOW"%d "C_WHITE"dias de {%s}%s\n", GetPlayerVipDays(playerid), GetVipColor(playerid), VIP_GetName(playerid));
		FormatCat(MEGAString, "Valor reembolso (em dias): "C_CASH"%d cash\n", getFormatText(days_value));
		FormatCat(MEGAString, "Valor reembolso (no total): "C_CASH"%s cash\n\n", getFormatText(refund_value));

		strcat(MEGAString, ""C_RED"- Obs: "C_WHITE"Abaixo de 7 dias não fazemos reembolso, apenas removemos seu SÓCIO.\n");
		strcat(MEGAString, ""C_WHITE"Você precisa escrever "C_GREEN"CONFIRMAR "C_WHITE"para concluir a ação:");
	}

	inline D_RefundSocio(did, ddialogid, dresponse, dlistitem, string:dtext[])
	{
		#pragma unused did, ddialogid, dlistitem
		if (!dresponse)
			return callcmd::menu(playerid);

		if (strcmp(dtext, "CONFIRMAR", true)) 
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você precisa digitar 'CONFIRMAR' para reembolsar seu sócio.");

		new string[128];
		format(string, sizeof(string), "* Você recebeu $%s de cash por reembolsar %d dias de %s.", getFormatText(refund_value), vip_days, VIP_GetName(vip_nivel));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

		format(string, sizeof string, "[SOCIO-REEMBOLSO]: %s recebeu $%s de cash por reembolsar %d dias de %s.", PlayerName[playerid], getFormatText(refund_value), vip_days, VIP_GetName(vip_nivel));
		server_log("cash", string);

		Player_SetVIP(playerid, 0);
		Player_AddCash(playerid, refund_value);

		mysql_format(
			MySQL_Handle, string, sizeof string, 
			"UPDATE `player` SET `vip_vencimento` = TIMESTAMPADD(DAY, %d, vip_vencimento) WHERE `id` = '%d'", 
			-vip_days, Player_GetAccountID(playerid));
		mysql_tquery(MySQL_Handle, string);
	}
	Dialog_ShowCallback(playerid, using inline D_RefundSocio, DIALOG_STYLE_INPUT, "Reembolse seu socio", MEGAString, "Confirmar", "Sair");
	return 1;
}

CALLBACK: onPlayerVipCheck(playerid)
{
	new string[255];
	new row_count;
	cache_get_row_count(row_count);

	SetPVarInt(playerid, "ViewingVipInfo", 1);

	if (!row_count) {
		format(string, sizeof string, "%s seu sócio venceu.", PlayerName[playerid]);
		SendClientMessage(playerid, COLOR_LIGHTRED, string);

        PlayerInfo[playerid][pVIP] = 0;
	} else {
		new serverRow[75];
		cache_get_value_name(0, "vip_vencimento", serverRow);

		format(string, sizeof string, "%s o seu sócio vence em %s", PlayerName[playerid], serverRow);
		SendClientMessage(playerid, COLOR_LIGHTGREEN, string);
	}
}

CMD:vips(playerid)
{
	new string[128];
	new count = 0;
	MEGAString[0] = EOS;
	new vip_nivel;
	
	strcat(MEGAString, "ID\tNome\tTitulo\tRank\n");

	foreach(new players : Character)
	{
		vip_nivel = Player_GetVIP(playerid);
	    if (vip_nivel > 0)
	    {
            format(string, sizeof(string), ""C_GRAY"%02d\t"C_WHITE"%s\t%s\t%s\n", players, PlayerName[players], PlayerTitle_Get(players), VIP_GetName(vip_nivel));
            strcat(MEGAString, string);
            List_SetPlayers(playerid, count, players);
            count ++;
		}
	}
    format(string, sizeof string, ""C_WHITE"VIPs Online ("C_GREEN"%d"C_WHITE")", count);
	ShowPlayerDialog(playerid, 4275, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Enviar SMS", "Fechar");
    return 1;
}

stock GetPlayerVipDays(playerid)
{
	new sql_query[200];

	mysql_format(MySQL_Handle, sql_query, sizeof sql_query, "SELECT UNIX_TIMESTAMP(`vip_vencimento`) FROM `player` WHERE `id` = '%d'", PlayerInfo[playerid][pID]);
	new Cache:p_result = mysql_query(MySQL_Handle, sql_query);

    new unix_date, row_count, int_dest;

    cache_get_row_count(row_count);

	if (row_count)
	{
	    cache_get_value_index_int(0, 0, int_dest);
		unix_date = (int_dest - gettime()) / 86400;
	}
	cache_delete(p_result);

	if (unix_date < 0) return false;

	return unix_date;
}

stock GetVIPInfo(playerid, const type[])
{
	new string[45];

	string = "NADA CONSTA";

	if(!strcmp(type, "VipTipo", true))
	{
	    switch(PlayerInfo[playerid][pVIP])
	    {
	        case 1: string = "Socio Comum";
	        case 2, 5, 6: string = "Socio Premium";
	        case 7: string = "Socio Supreme";
	        case 8: string = "Socio Extreme";
	        default: string = "NADA CONSTA";
	    }
	    return string;
	}
	return string;
}