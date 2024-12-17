#include    < YSI_Coding\y_hooks >

#define		MAX_ITENS_LOJA			50

// ---------------------------------------- Loja de cash ----------------------------------------

enum dCash
{
	// Sócio Bronze
	Cash_SocioComum,

    // Sócio Diamante
	Cash_SocioPremium,

    // Sócio Platina
	Cash_SocioSupreme,

    // Sócio Ultimate
	Cash_SocioExtreme,

    // Itens (Geral)
    Cash_Item,
	Cash_SairPrisao,
	Cash_RemoverCadeias10,
	Cash_ComprarPasse
}

enum CashEnum
{
	Cash_ID,
	Cash_Nome[128],
	Cash_Grupo,
	Cash_Tipo, // 1 = item configurado / 2 = item pelo complemento
	Cash_Ordem,
	Cash_Custo,
	Cash_Moeda,
	Cash_Quantidade,
	Cash_Complemento[100],
	bool:Cash_Carregado
}

new CashInfo[MAX_ITENS_LOJA][CashEnum]; 

stock CarregarLojaCash()
{
	for(new i = 0; i < MAX_ITENS_LOJA; i++)
		CashInfo[i][Cash_Carregado] = false;

    new rows;

	mysql_query(MySQL_Handle, "SELECT * FROM loja_itens WHERE ativo = 1 ORDER BY ordem ASC");
	cache_get_row_count(rows);

	for(new id = 0; id < rows; id++) {
		CashInfo[id][Cash_ID] = MYSQL_GetInt(id, "id");
		format(CashInfo[id][Cash_Nome], 128, MYSQL_GetString(id, "nome"));
		CashInfo[id][Cash_Grupo] = MYSQL_GetInt(id, "grupo");
		CashInfo[id][Cash_Tipo] = MYSQL_GetInt(id, "tipo");
		CashInfo[id][Cash_Ordem] = MYSQL_GetInt(id, "ordem");
		CashInfo[id][Cash_Custo] = MYSQL_GetInt(id, "custo");
		CashInfo[id][Cash_Moeda] = MYSQL_GetInt(id, "moeda");
		CashInfo[id][Cash_Quantidade] = MYSQL_GetInt(id, "quantidade");
		format(CashInfo[id][Cash_Complemento], 100, MYSQL_GetString(id, "complemento"));
		CashInfo[id][Cash_Carregado] = true;
	}

	return rows;
}

stock SalvarItemLoja(id) {
	new query[228];
	mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE loja_itens SET quantidade = %d WHERE id = %d", CashInfo[id][Cash_Quantidade], CashInfo[id][Cash_ID]);
	mysql_tquery(MySQL_Handle, query);
}

stock GetCashCurrency(id, addColor=0) {
	new currency[20];
	if(CashInfo[id][Cash_Moeda] == 0) {
		format(currency, sizeof(currency), "%s%s", (addColor == 1) ? ("{00BFFF}") : (""), ("Cash"));
	}
	else if (CashInfo[id][Cash_Moeda] == 1) {
		format(currency, sizeof(currency), "%s%s", (addColor == 1) ? ("{DBED15}") : (""), ("Ouros"));
	}
	else if (CashInfo[id][Cash_Moeda] == 2) {
		format(currency, sizeof(currency), "%s%s", (addColor == 1) ? ("{00AA00}") : (""), ("Dinheiro"));
	}
	return currency;
}

stock Player_GetMoneyByItem(playerid, itemid) {
	new playerMoney;
	if(CashInfo[itemid][Cash_Moeda] == 0) {
		playerMoney = Player_GetCash(playerid);
	}
	else if (CashInfo[itemid][Cash_Moeda] == 1) {
		playerMoney = PlayerInfo[playerid][pOuros];
	}
	else if (CashInfo[itemid][Cash_Moeda] == 2) {
		playerMoney = Player_GetMoney(playerid);
	}
	return playerMoney;
}

new PlayerCashId[MAX_PLAYERS];

// -------------------------------------------------------------------

CMD:menu(playerid)
{
	if (!Player_Logado(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está logado no servidor.");

	DialogShow_MenuPlayer(playerid);
	return 1;
}
alias:menu("desligarcel", "menuvip", "lojacash", "menucash", "trocaremail", "menucheater")

CMD:hud(playerid)
{
	if (!Player_Logado(playerid)) return SendClientMessage(playerid, -1, "Você não está logado no servidor.");

	if(GetPVarInt(playerid, "hudInativo")) {
		HUD_ShowForPlayer(playerid);
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "Você ativou o HUD. Use /hud para desativar.");
		SetPVarInt(playerid, "hudInativo", 0);
	}
	else {
		HideTextDrawHUD(playerid);
		SendClientMessage(playerid, COLOR_LIGHTRED, "Você desativou o HUD. Use /hud para ativar novamente.");
		SetPVarInt(playerid, "hudInativo", 1);
	}
	return 1;
}

stock DialogShow_MenuPlayer(playerid)
{
	new string[128];
	MEGAString[0] = EOS;

	format(string, sizeof(string), ""C_WHITE"001. "C_LIGHTBLUE"Configuracoes\t"C_GRAY"Gerais do jogador\n");
    strcat(MEGAString, string);
    format(string, sizeof(string), ""C_WHITE"002. "C_LIGHTBLUE"Menu\t"C_YELLOW"VIP/SOCIO\n");
    strcat(MEGAString, string);
    format(string, sizeof(string), ""C_WHITE"002. "C_LIGHTBLUE"Menu\t"C_YELLOW"Compras\n");
    strcat(MEGAString, string);
    
    if (Admin_GetNivel(playerid) >= DIRETOR) {
    	format(string, sizeof(string), ""C_WHITE"010. "C_LIGHTBLUE"Menu\t"C_ADMIND"Conselho\n");
    	strcat(MEGAString, string);
	}
	format(string, sizeof(string), "Menu principal de %s", PlayerName[playerid]);
	ShowPlayerDialog(playerid, 1950, DIALOG_STYLE_TABLIST, string, MEGAString, "Prosseguir", "Cancelar");
}

stock showDialogMenuConfig(playerid)
{
	new
		string[128],
		infosHit[32],
		infosMsgMorro[21],
		infosAutoCaixinha[21],
		infosMostrarRG[26],
		infosChatEmprego[26]
	;

	if (PlayerInfo[playerid][pHitSound][0] == 1 && PlayerInfo[playerid][pHitSound][1] == 0) infosHit = "{00FF00}Acertar tiros";
	else if (PlayerInfo[playerid][pHitSound][0] == 0 && PlayerInfo[playerid][pHitSound][1] == 1) infosHit = "{00FF00}Levar tiros";
	else if (PlayerInfo[playerid][pHitSound][0] == 1 && PlayerInfo[playerid][pHitSound][1] == 1) infosHit = "{00FF00}Acertar e levar tiros";
	else if (PlayerInfo[playerid][pHitSound][0] == 0 && PlayerInfo[playerid][pHitSound][1] == 0) infosHit = "{FF0000}Desativado";
	
	if (PlayerInfo[playerid][pChatMorro]) infosMsgMorro = "{00FF00}Ativada";
	else if (!PlayerInfo[playerid][pChatMorro]) infosMsgMorro = "{FF0000}Desativada";
	
	if (PlayerInfo[playerid][pAutoCaixinha] && PlayerInfo[playerid][pVIP] > 7) infosAutoCaixinha = "{00FF00}Ativada";
	else infosAutoCaixinha = "{FF0000}Desativada";

	if (PlayerInfo[playerid][style_view_rg] == MODEL_VIEW_MESSAGE) infosMostrarRG = "{00BFFF}Mensagem no chat";
	else infosMostrarRG = "{00BFFF}Dialog";

	if(GetPVarInt(playerid, "ChatEmpregoDesativado") == 0) infosChatEmprego = "{00FF00}Ativado";
	else infosChatEmprego = "{FF0000}Desativado";

	MEGAString[0] = EOS;

	format(string, 128, "{7D8084}Mudar som de dano\t{DFD136}%d\n", PlayerInfo[playerid][pHitSoundID]);
   	strcat(MEGAString, string);
 	format(string, 128, "{7D8084}Ouvir o sino de dano ao:\t%s\n", infosHit);
   	strcat(MEGAString, string);
	format(string, 128, "{7D8084}Mensagens da guerra do morro:\t%s\n", infosMsgMorro);
	strcat(MEGAString, string);
	format(string, 128, "{7D8084}Mostrar RG:\t%s\n", infosMostrarRG);
	strcat(MEGAString, string);
	format(string, 128, "{7D8084}Pegar caixinha automaticamente:\t%s\n", infosAutoCaixinha);
	strcat(MEGAString, string);
	format(string, 128, "{7D8084}Chat de emprego:\t%s\n", infosChatEmprego);
	strcat(MEGAString, string);
	#if SERVER_ID == 3
		format(string, 128, "{7D8084}Sistema de fome e sede:\t%s\n", Consumable_GetActive(playerid) == 1 ? "{00FF00}ativo" : "{FF0000}inativo");
		strcat(MEGAString, string);
	#endif
   	strcat(MEGAString, "{7D8084}Modificar meu: \t{DBDCE0}E-mail\n");
   	strcat(MEGAString, "{7D8084}Modificar minha: \t{DBDCE0}Senha\n");

	ShowPlayerDialog(playerid, 1951, DIALOG_STYLE_TABLIST, "Menu do jogador", MEGAString, "Modificar", "Retornar");
}

stock showDialogMenuVIPConfig(playerid)
{
	new
		string[128],
		infosCelOff[21],
		infosChatvOff[21]
	;

	if (!PhoneOnline[playerid]) infosCelOff = "{00FF00}Ativado";
	else if (PhoneOnline[playerid]) infosCelOff = "{FF0000}Desativado";
	
	if (PlayerInfo[playerid][pChatVip]) infosChatvOff = "{00FF00}Ativado";
	else if (!PlayerInfo[playerid][pChatVip]) infosChatvOff = "{FF0000}Desativado";

	MEGAString[0] = EOS;

 	format(string, 128, "{7D8084}Meu celular: \t{DBDCE0}%s\n", infosCelOff);
   	strcat(MEGAString, string);
 	format(string, 128, "{7D8084}Chat VIP (/v): \t{DBDCE0}%s\n", infosChatvOff);
   	strcat(MEGAString, string);

	ShowPlayerDialog(playerid, 1958, DIALOG_STYLE_TABLIST, "Menu Vip/Sócio", MEGAString, "Modificar", "Retornar");
}

stock showDialogTrocarEmail(playerid)
{
	new string[210 + MAX_PLAYER_NAME];

    format(string, sizeof(string),
	"{FFFFFF}Bem vindo {00BFFF}%s{FFFFFF}, digite seu e-mail {00FF00}CORRETAMENTE\n\
	{FFFFFF}Você vai usar ele para recuperar sua senha, não esqueça o e-mail!\n\n", PlayerName[playerid]);
	
	ShowPlayerDialog(playerid, 29, DIALOG_STYLE_INPUT, "E-mail", string, "Confirmar", "");
}

stock showDialogMenuConselho(playerid)
{
	if (Admin_GetNivel(playerid) < DIRETOR) 
		return true;

	new string[128],
		info[32];
	
	if (!PlayerInfo[playerid][pHidePar]) info = "{00FF00}Ativado";
	else if (PlayerInfo[playerid][pHidePar]) info = "{FF0000}Desativado";

	MEGAString[0] = EOS;

 	format(string, 128, "{7D8084}Particular (/par): \t{DBDCE0}%s\n", info);
	strcat(MEGAString, string);

	if (!NoobDesativado) info = "{00FF00}Ativado";
	else info = "{FF0000}Desativado";

	format(string, 128, "{7D8084}Chat Noob: \t{DBDCE0}%s\n", info);
	strcat(MEGAString, string);

	if (gmxAutomatico) info = "{00FF00}Ativado";
	else info = "{FF0000}Desativado";

	format(string, 128, "{7D8084}GMX Automático: \t{DBDCE0}%s\n", info);
	strcat(MEGAString, string);

	if (Admin_GetLogChat()) info = "{00FF00}Ativado";
	else info = "{FF0000}Desativado";

	format(string, 128, "{7D8084}Log de Chat: \t{DBDCE0}%s\n", info);
	strcat(MEGAString, string);

	if (eventoAleatorio) info = "{00FF00}Ativado";
	else info = "{FF0000}Desativado";

	format(string, 128, "{7D8084}Eventos Aleatórios: \t{DBDCE0}%s\n", info);
	strcat(MEGAString, string);

	if (logDeComandos) info = "{00FF00}Ativado";
	else info = "{FF0000}Desativado";

	format(string, 128, "{7D8084}Log de Comandos: \t{DBDCE0}%s\n", info);
	strcat(MEGAString, string);

	ShowPlayerDialog(playerid, 1959, DIALOG_STYLE_TABLIST, "Menu do conselho", MEGAString, "Modificar", "Retornar");

	return true;
}

// ----------------------------------------------------------------- Loja Cash -----------------------------------------------------------------

stock showDialogCash(playerid)
{
	new string[128];
	
	MEGAString[0] = EOS;

    strcat(MEGAString, "{74F6F8}Loja Cash » {7D8084}Ativar\t{A4CCC3}Sócio Comum\n");
    strcat(MEGAString, "{74F6F8}Loja Cash » {7D8084}Ativar\t{DBB960}Sócio Premium\n");
    strcat(MEGAString, "{74F6F8}Loja Cash » {7D8084}Ativar\t{017bff}Sócio Supreme\n");
    strcat(MEGAString, "{74F6F8}Loja Cash » {7D8084}Ativar\t{DC0139}Sócio Extreme\n");
    strcat(MEGAString, "{74F6F8}Loja Cash » {7D8084}Comprar\t{00FF00}Itens\n");
    
	new vip_nivel = Player_GetVIP(playerid);

    if (vip_nivel > 0)
    {
    	format(string, sizeof(string), "{74F6F8}Loja Cash » {7D8084}Reembolsar\t{FFFFFF}Meu {%s}%s\n", GetVipColor(playerid), VIP_GetName(vip_nivel));
	    strcat(MEGAString, string);
    }
    else 
		strcat(MEGAString, "{74F6F8}Loja Cash » {7D8084}Reembolsar\t{FFFFFF}Meu sócio\n");
    
    strcat(MEGAString, "{74F6F8}Loja Cash » {7D8084}Transferir\t{DBDCE0}Cash\n");
    strcat(MEGAString, "{74F6F8}Loja Cash » {7D8084}Comprar\t{DBDCE0}Cash\n");
    strcat(MEGAString, "{74F6F8}Loja Cash » {7D8084}Beneficios\t{DBDCE0}Cash\n");
    strcat(MEGAString, "{74F6F8}Loja Cash » {7D8084}Utilizar\t{DBDCE0}Cupom\n");

	ShowPlayerDialog(playerid, 4252, DIALOG_STYLE_TABLIST, "{00CCFF}Loja de Cash", MEGAString, "Acessar", "Retornar");
}

// comprar Cash

stock OnPlayerRequestBuyCash(playerid, itemid, custo)
{
	SetPVarInt(playerid, "ItemCash", itemid);

	new string[128];

	MEGAString[0] = EOS;

	format(string, sizeof(string), "{34CFE7}× Loja Cash » {DBDCE0} Você está comprando o item: {7D8084}%s\n\n", CashInfo[itemid][Cash_Nome]);
	strcat(MEGAString, string);

	format(string, sizeof(string), "{7D8084}Custo do item: {DBDCE0}%s %s\n\n", getFormatText(CashInfo[itemid][Cash_Custo]), GetCashCurrency(itemid, 1));
	strcat(MEGAString, string);

	new playerMoney = Player_GetMoneyByItem(playerid, itemid);
	if ((playerMoney - custo) >= 0) {
		format(string, sizeof(string), "{7D8084}%s que você possui: {DBDCE0}%s %s\n", GetCashCurrency(itemid), getFormatText(playerMoney), GetCashCurrency(itemid, 1));
		strcat(MEGAString, string);
		format(string, sizeof(string), "{7D8084}%s depois da compra: {DBDCE0}%s %s\n\n", GetCashCurrency(itemid), getFormatText(playerMoney - custo), GetCashCurrency(itemid, 1));
		strcat(MEGAString, string);
	} 
	else {
		format(string, sizeof(string), "{FF0000}Você não tem %s suficientes para fazer essa compra.\n\n", GetCashCurrency(itemid));
		strcat(MEGAString, string);
	}

    strcat(MEGAString, "{FFFFFF}Para concluir a compra, digite: {00FF00}CONFIRMAR{DBDCE0} (na caixa de texto abaixo)\n\n");
 	strcat(MEGAString, "{FF6347}Observação: {7D8084}Não reembolsamos valores se você se arrepender da compra.\n");

	ShowPlayerDialog(playerid, 9527, DIALOG_STYLE_INPUT, "{34CFE7}Loja Cash: {FFFFFF}Confirmar Compra", MEGAString, "Comprar", "Cancelar");
}

stock OnPlayerBuyCash(playerid, itemid, custo)
{
	new playerMoney = Player_GetMoneyByItem(playerid, itemid);
	if (playerMoney < custo) return SendMsgF(playerid, -1, "Você não tem esse valor em %s.", GetCashCurrency(itemid));
	else if(CashInfo[itemid][Cash_Quantidade] != -1 && CashInfo[itemid][Cash_Quantidade] == 0)
		return SendClientMessage(playerid, -1, "Não existem mais unidades desse item.");

	if(CashInfo[itemid][Cash_Quantidade] != -1) {
		CashInfo[itemid][Cash_Quantidade] -= 1;
	}

	new string[165];
	switch (CashInfo[itemid][Cash_Tipo])
	{
		case Cash_SocioComum: {
			giveSocioComum(playerid, strval(CashInfo[itemid][Cash_Complemento]));
		}
		case Cash_SocioPremium: {
			giveSocioPremium(playerid, strval(CashInfo[itemid][Cash_Complemento]));
		}
		case Cash_SocioSupreme: {
			giveSocioSupreme(playerid, strval(CashInfo[itemid][Cash_Complemento]));
		}
		case Cash_SocioExtreme: {
			giveSocioExtreme(playerid, strval(CashInfo[itemid][Cash_Complemento]));
		}
		case Cash_Item:
		{
			if (isInventoryFull(playerid))
	    		return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

			new itemnome[75], itemtype, modelid, quantidade, cor1, cor2;
			SplitItem(CashInfo[itemid][Cash_Complemento], itemnome, itemtype, modelid, quantidade, cor1, cor2);

			givePlayerItem(playerid, itemtype, modelid, quantidade, itemnome, cor1, cor2); 
        }
		case Cash_SairPrisao:
		{
			if (Player_GetJailed(playerid) == 9) return SendClientMessage(playerid, -1, "Você não pode sair da prisão administrativa.");
			if (!Player_GetJailed(playerid)) return SendClientMessage(playerid, -1, "Você não está na prisão.");
			PlayerInfo[playerid][pJailTime] = 0;
		}
		case Cash_RemoverCadeias10:
		{
			if(PlayerInfo[playerid][pPrisaoAdmin] == 0) return SendClientMessage(playerid, -1, "Você não possui cadeias admin!");

			PlayerInfo[playerid][pPrisaoAdmin] -= 10;
			if(PlayerInfo[playerid][pPrisaoAdmin] < 0)
				PlayerInfo[playerid][pPrisaoAdmin] = 0;
		}
		case Cash_ComprarPasse:
		{
			if(!WeeklyPassInfo[wpInProgress])
				return SendClientMessage(playerid, -1, "Não há um passe disponível para compra no momento.");
			else if(!WeeklyPassInfo[wpPaid])
				return SendClientMessage(playerid, -1, "O passe atual é gratuito e não pode ser comprado.");
			else if(WeeklyPassPlayerInfo[playerid][wppAvailable])
				return SendClientMessage(playerid, -1, "Você já comprou esse passe e não pode comprar novamente.");

			new startDate[16], endDate[16];
			TimeFormat(WeeklyPassInfo[wpStartDate], "%d/%m/%Y", startDate);
			TimeFormat(WeeklyPassInfo[wpEndDate], "%d/%m/%Y", endDate);

			SendMsgF(playerid, 0xDBDCE0FF, "PARABÉNS! Você comprou o passe {DC0139}%s {DBDCE0}e estará disponível de %s a %s.", CashInfo[itemid][Cash_Nome], startDate, endDate);
			SendClientMessage(playerid, 0xDBDCE0FF, "Para ver as informações do passe, use /infopasse.");
			WeeklyPassPlayerInfo[playerid][wppAvailable] = 1;
		}
 	}
	SalvarItemLoja(itemid);
	
	format(
		string, sizeof(string), 
		"(Loja Cash) » {FFFFFF}%s comprou o item {7D8084}%s{FFFFFF} por {00FF00}%s {FFFFFF}%s.", 
		PlayerName[playerid], CashInfo[itemid][Cash_Nome], getFormatText(custo), GetCashCurrency(itemid)
	);
	SendClientMessageToAll(0x34CFE7FF, string);

	new remaining;
	if(CashInfo[itemid][Cash_Moeda] == 0) {
		Player_RemoveCash(playerid, custo);
		remaining = Player_GetCash(playerid);
	}
	else if(CashInfo[itemid][Cash_Moeda] == 1) {
		PlayerInfo[playerid][pOuros] -= custo;
		remaining = PlayerInfo[playerid][pOuros];
	}

	MEGAString[0] = EOS;

	format(
		string, sizeof(string), 
		"{34CFE7}× Loja de Cash: {DBDCE0}Você comprou o item: {7D8084}%s\n\n", 
		CashInfo[itemid][Cash_Nome]
	);
	strcat(MEGAString, string);

	format(
		string, sizeof(string), 
		"{DBDCE0}Custo do item: {DBDCE0}%s %s\n", 
		getFormatText(custo), GetCashCurrency(itemid, 1)
	);
	strcat(MEGAString, string);

	format(
		string, sizeof(string), 
		"{DBDCE0}%s restante: {DBDCE0}%s %s\n\n", 
		GetCashCurrency(itemid), getFormatText(remaining), GetCashCurrency(itemid, 1)
	);
	strcat(MEGAString, string);

	strcat(MEGAString, "{FF6347}Observação: {7D8084}O item que você acaba de comprar não é reembolsavel.\n");

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{34CFE7}Loja Cash: {FFFFFF}Compra Concluida", MEGAString, "Fechar", "");

	format(
		string, sizeof(string), 
		"CASH: %s comprou o item %s{9ACD32} por %s de %s.", 
		PlayerName[playerid], CashInfo[itemid][Cash_Nome], getFormatText(custo), GetCashCurrency(itemid)
	);
 	Staff_ChatToAll(COLOR_LIGHTGREEN, string, ESTAGIARIO);
	server_log("cash", string);
	
	return true;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {

	new string[256];
	if (dialogid == 4252) {
	    if (!response)
			return callcmd::menu(playerid);

		MEGAString[0] = EOS;

		switch (listitem) {

			case 0..4: {
				strcat(MEGAString, "Nome do item\tUnidades\tCusto\n");

				PlayerCashId[playerid] = listitem;

				for (new i = 0; i < MAX_ITENS_LOJA; i++) {

					if (CashInfo[i][Cash_Carregado] && CashInfo[i][Cash_Grupo] == PlayerCashId[playerid]) {
						new qtd[16];
						if (CashInfo[i][Cash_Quantidade] >= 0)
							format(qtd, 64, "%d", CashInfo[i][Cash_Quantidade]);
						else
							format(qtd, 64, "Ilimitada");

						format(
							string, sizeof(string), 
							"{DBDCE0}%s\t{9BE374}%s\t{FFFFFF}%s %s\n", 
							CashInfo[i][Cash_Nome], qtd, getFormatText(CashInfo[i][Cash_Custo]), GetCashCurrency(i, 1)
						);
						strcat(MEGAString, string);
					}
				}
				ShowPlayerDialog(playerid, 4872, DIALOG_STYLE_TABLIST_HEADERS, inputtext, MEGAString, "Prosseguir", "Voltar");
				return 1;
			}
			case 5: {
				if (Player_GetVIP(playerid) < 1)
					return SendClientMessage(playerid, -1, "Você não é um jogador SÓCIO.");

				return Dialog_RefundSocio(playerid);
			}
			case 6: {
				MEGAString[0] = EOS;

				strcat(MEGAString, "{FFFFFF} » {00FF00}CASH » {FFFFFF} Você está prestes a transferir Cash\n\n");

				format(string, sizeof(string), "{FFFFFF}* Digite o ID para quem irá transferir Cash:\n\n");
				strcat(MEGAString, string);

				strcat(MEGAString, "{FF6347}OBS: {B4B5B7}O jogador tem que estar conectado e logado para receber a transferência.\n");

				ShowPlayerDialog(playerid, 9832, DIALOG_STYLE_INPUT, "{FFFFFF} » {00FFFF}CASH » {FFFFFF}Transferir Cash", MEGAString, "Continuar", "Retornar");
				
				return 1;
			}
			case 7: {
				callcmd::comprarcash(playerid);
				return 1;
			}
			case 8: {
				callcmd::vip(playerid);
				return 1;
			}
			case 9: {
				Cupom_ShowDialog(playerid);
				return 1;
			}
		}

	    return 1;
	}

	else if (dialogid == 4872)
	{
	    if (response) {
			new count = 0;
			for(new i = 0; i < MAX_ITENS_LOJA; i++) {
				if(CashInfo[i][Cash_Carregado] && CashInfo[i][Cash_Grupo] == PlayerCashId[playerid]) {
					count += 1;

					if(count == listitem + 1) {
						OnPlayerRequestBuyCash(playerid, i, CashInfo[i][Cash_Custo]);
						break;
					}
				}
			}
	        
	    } else {
	        callcmd::menu(playerid);
	    }
	    return 1;
	}

	else if (dialogid == 9527) {

	    if (response) {

			if (!strlen(inputtext)) {
			    return SendClientMessage(playerid, COLOR_LIGHTRED, " Você não escreveu ''CONFIRMAR'' e a compra foi cancelada !");
			}

	        if (!strcmp(inputtext, "confirmar", true)) {
	            new custo = CashInfo[GetPVarInt(playerid, "ItemCash")][Cash_Custo];
	            OnPlayerBuyCash(playerid, GetPVarInt(playerid, "ItemCash"), custo);
	        } else {
	            SendClientMessage(playerid, COLOR_LIGHTRED, " Você não escreveu ''CONFIRMAR'' e a compra foi cancelada !");
	        }
	    }
	    return 1;
	}
	return 1;
}


CMD:ulojacash(playerid, params[])
{
	if (!Founders_GetList(playerid)) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new iditem, unidade,
		string[128];

	if (sscanf(params, "dd", iditem, unidade)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /ulojacash (iditem) (unidade).");

	if (iditem > MAX_ITENS_LOJA || iditem < 0) 
		return SendClientMessage(playerid, -1, "O iditem deve estar entre 0 a 49.");

	if(!CashInfo[iditem][Cash_Carregado]) 
		return SendClientMessage(playerid, -1, "Item da loja não existente.");

	CashInfo[iditem][Cash_Quantidade] = unidade;

	format(string, sizeof(string), "AdmAviso: %s atualizou as unidades do item %s {FF6347}[%d] para %d.", PlayerName[playerid], CashInfo[iditem][Cash_Nome], iditem, unidade);
	Staff_ChatToAll(COLOR_LIGHTRED, string, SUB_DONO);

	ServerLog::("ulojacash", string);
	return true;
}
