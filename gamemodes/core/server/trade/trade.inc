#include <YSI_Coding\y_hooks>

#include <trade_entry>
#include <trade_textdraws>

CALLBACK: playerResetTrade(playerid)
{
	playerTrade[playerid][p_trade_playerid] = INVALID_PLAYER_ID;
	playerTrade[playerid][p_trade_ready]    = 0;
	playerTrade[playerid][p_trade_money]    = 0;
	playerTrade[playerid][p_trade_ouros]    = 0;
	playerTrade[playerid][p_trade_cash]     = 0;

	for(new index; index < MAX_PLAYER_TRADE_ITENS; index++)
	{
	    playerTradeItens[playerid][index][p_trade_valid] 	 = 0;
	    playerTradeItens[playerid][index][p_trade_type]      = TRADE_TYPE_INVALID;
	    playerTradeItens[playerid][index][p_trade_unique_id] = INVALID_UNIQUE_ID;
	}
}

stock playerShowTrade(playerid, withplayerid)
{
	// resetar playerid
    playerResetTrade(playerid);

    // resetar outro jogador
    playerResetTrade(withplayerid);

    playerTrade[playerid][p_trade_playerid] = withplayerid;
    playerTrade[withplayerid][p_trade_playerid] = playerid;

    Inventory_HideForPlayer(playerid, .cancelselect = 0);
    Inventory_HideForPlayer(withplayerid, .cancelselect = 0);

	playerShowTradeTextdraws(playerid);
	playerShowTradeTextdraws(withplayerid);

    playerUpdateTradeTextdraws(playerid);
    playerUpdateTradeTextdraws(withplayerid);

    SetPVarInt(playerid, "p_intrade", 1);
    SetPVarInt(withplayerid, "p_intrade", 1);

    // Nick
    PlayerTextDrawSetString(playerid, playerTradeText[playerid][4], PlayerName[withplayerid]);
    PlayerTextDrawSetString(withplayerid, playerTradeText[withplayerid][4], PlayerName[playerid]);
}

stock playerAddTradeItem(playerid, type, uniqueid)
{
	for(new index; index < MAX_PLAYER_TRADE_ITENS; index++)
	{
		if (strfind(InventarioInfo[playerid][uniqueid][item_nome], "INE", false) != -1)
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Não é possível negociar esse item!");

	    if (playerTradeItens[playerid][index][p_trade_type] == type && playerTradeItens[playerid][index][p_trade_unique_id] == uniqueid)
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você está tentando adicionar algo que já está na lista.");

        if (GetPVarInt(playerid, "p_intrade") == 0)
			return SendClientMessage(playerid, COLOR_LIGHTRED, "A negociação foi cancelada!");

	    if (playerTradeItens[playerid][index][p_trade_valid]) continue;

	    playerTradeItens[playerid][index][p_trade_valid] 	 = 1;
	    playerTradeItens[playerid][index][p_trade_type]      = type;
	    playerTradeItens[playerid][index][p_trade_unique_id] = uniqueid;

    	playerUpdateTradeTextdraws(playerid);
    	playerUpdateTradeTextdraws(playerTrade[playerid][p_trade_playerid]);

	    return 1;
	}

	return 0;
}

stock playerResetTradeItens(playerid)
{
	for(new index; index < MAX_PLAYER_TRADE_ITENS; index++)
	{
	    playerTradeItens[playerid][index][p_trade_valid] 	 = 0;
	    playerTradeItens[playerid][index][p_trade_type]      = TRADE_TYPE_INVALID;
	    playerTradeItens[playerid][index][p_trade_unique_id] = INVALID_UNIQUE_ID;
	}

   	if (playerTrade[playerTrade[playerid][p_trade_playerid]][p_trade_ready])
   	{
   	    playerTrade[playerTrade[playerid][p_trade_playerid]][p_trade_ready] = 0;

   	    SendClientMessage(playerTrade[playerid][p_trade_playerid], COLOR_GREY, "Houve uma alteração nos valores, você deve confirmar novamente.");
   	}

   	playerUpdateTradeTextdraws(playerid);
   	playerUpdateTradeTextdraws(playerTrade[playerid][p_trade_playerid]);
}

stock playerCancelTrade(playerid)
{
	if (GetPVarInt(playerid, "p_intrade") == 0)
	    return 0;

    playerHideTradeTextdraws(playerid);

    playerHideTradeTextdraws(playerTrade[playerid][p_trade_playerid]);

	SendClientMessage(playerid, COLOR_LIGHTRED, "* A negociação foi cancelada.");
	SendClientMessage(playerTrade[playerid][p_trade_playerid], COLOR_LIGHTRED, "* A negociação foi cancelada.");

    return 1;
}

stock playerListInventoryItens(playerid)
{
  	MEGAString[0] = EOS;

    new string_add[128];

    strcat(MEGAString, "Nome do item\tQuantidade\n");

    for (new item; item < MAX_ITENS_INVENTARIO; item++) {

		if (InventarioInfo[playerid][item][item_valid]) {

			format(string_add, sizeof (string_add), "%s\t%d\n", InventarioInfo[playerid][item][item_nome], InvItem_GetQuantity(playerid, item));
   		} else {

			format(string_add, sizeof (string_add), "{AAAAAA}Nenhum\n");
   		}
     	strcat(MEGAString, string_add);
	}

	ShowPlayerDialog(playerid, 11000, DIALOG_STYLE_TABLIST_HEADERS, " Escolha um item para guardar na caixa", MEGAString, "Adicionar", "Cancelar");

	return 1;
}

stock playerListVehicles(playerid)
{
	new string[95];
	MEGAString [0] = EOS;
	strcat(MEGAString, "ID Carro\tPlaca\n");

	new vehicle_name[30];

	for(new carro; carro < MAX_PLAYER_CARROS; carro++) {
	    if (PlayerVehicleInfo[playerid][carro][pvDBID] != 0) {
			GetModelStaticNameFromId(GetVehicleModel(PlayerVehicleInfo[playerid][carro][pvID]), vehicle_name);

	       	format(string, sizeof string, "%02d %s\t%s\n", carro, vehicle_name, PlayerVehicleInfo[playerid][carro][pvPlate]);
			strcat(MEGAString, string);
	    } else {
	        strcat(MEGAString, "{AAAAAA}Vazio\n");
	    }
	}
	ShowPlayerDialog(playerid, 12007, DIALOG_STYLE_TABLIST_HEADERS, "Escolha uma das opções", MEGAString, "Localizar", "Fechar");
}

stock playerShowTradeDialog(playerid)
{
	ShowPlayerDialog(playerid, 12000, DIALOG_STYLE_LIST, "Selecione uma das opções", "Adicionar item do inventário\nAdicionar casas\nAdicionar fazendas\nAdicionar propriedades\nAdicionar veículos", "Selecionar", "Fechar");
}

stock playerUpdateTradeTextdraws(playerid)
{
	new string[155];

	new wplayerid = playerTrade[playerid][p_trade_playerid];

	for(new index; index < MAX_PLAYER_TRADE_ITENS; index++)
	{
	    new wuniqueid = playerTradeItens[wplayerid][index][p_trade_unique_id];
	    new puniqueid = playerTradeItens[playerid][index][p_trade_unique_id];

	    if (playerTradeItens[playerid][index][p_trade_valid]) {
	        PlayerTextDrawSetPreviewModel(playerid, playerTradeText[playerid][index + 5], playerGetTradeModel(playerid, index));

            if (playerTradeItens[playerid][index][p_trade_valid] && playerTradeItens[playerid][index][p_trade_type] == TRADE_TYPE_ITEM) {
				PlayerTextDrawSetPreviewVehCol(playerid, playerTradeText[playerid][index + 5], InventarioInfo[playerid][puniqueid][item_cor1], InventarioInfo[playerid][puniqueid][item_cor2]);
			}

			PlayerTextDrawShow(playerid, playerTradeText[playerid][index + 5]);
		} else {
	        PlayerTextDrawHide(playerid, playerTradeText[playerid][index + 5]);
		}

	    if (playerTradeItens[wplayerid][index][p_trade_valid]) {
            PlayerTextDrawSetPreviewModel(playerid, playerTradeText[playerid][index + 9], playerGetTradeModel(wplayerid, index));

            if (playerTradeItens[wplayerid][index][p_trade_valid] && playerTradeItens[wplayerid][index][p_trade_type] == TRADE_TYPE_ITEM) {
				PlayerTextDrawSetPreviewVehCol(playerid, playerTradeText[playerid][index + 9], InventarioInfo[wplayerid][wuniqueid][item_cor1], InventarioInfo[wplayerid][wuniqueid][item_cor2]);
			}
			PlayerTextDrawShow(playerid, playerTradeText[playerid][index + 9]);
     	} else {
	        PlayerTextDrawHide(playerid, playerTradeText[playerid][index + 9]);
      	}
	}

	// Custo dos itens
	format(string, sizeof string, "~w~$%s / Cash %s / Ouros %s", getFormatText(playerTrade[playerid][p_trade_money]), getFormatText(playerTrade[playerid][p_trade_cash]), getFormatText(playerTrade[playerid][p_trade_ouros]));
    PlayerTextDrawSetString(playerid, playerTradeText[playerid][17], string);

	format(string, sizeof string, "~w~$%s / Cash %s / Ouros %s", getFormatText(playerTrade[wplayerid][p_trade_money]), getFormatText(playerTrade[wplayerid][p_trade_cash]), getFormatText(playerTrade[wplayerid][p_trade_ouros]));
    PlayerTextDrawSetString(playerid, playerTradeText[playerid][18], string);

	// Nome dos itens
	format(string, sizeof string, "%s~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~%s", playerGetTradeName(playerid, 0), playerGetTradeName(playerid, 2));
	PlayerTextDrawSetString(playerid, playerTradeText[playerid][13], string);

	format(string, sizeof string, "%s~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~%s", playerGetTradeName(playerid, 1), playerGetTradeName(playerid, 3));
	PlayerTextDrawSetString(playerid, playerTradeText[playerid][14], string);

	format(string, sizeof string, "%s~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~%s", playerGetTradeName(wplayerid, 0), playerGetTradeName(wplayerid, 2));
	PlayerTextDrawSetString(playerid, playerTradeText[playerid][15], string);

	format(string, sizeof string, "%s~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~%s", playerGetTradeName(wplayerid, 1), playerGetTradeName(wplayerid, 3));
	PlayerTextDrawSetString(playerid, playerTradeText[playerid][16], string);

	// Aguardando / Pronto
	if (playerTrade[playerid][p_trade_ready])
	{
	    PlayerTextDrawColor(playerid,playerTradeText[playerid][0], 336860415), PlayerTextDrawShow(playerid, playerTradeText[playerid][0]);
	    PlayerTextDrawColor(playerid,playerTradeText[playerid][1], 842150655), PlayerTextDrawShow(playerid, playerTradeText[playerid][1]);
	    PlayerTextDrawSetString(playerid, playerTradeText[playerid][1], "PRONTO");
	} else {
	    PlayerTextDrawColor(playerid,playerTradeText[playerid][0], 505290495), PlayerTextDrawShow(playerid, playerTradeText[playerid][0]);
	    PlayerTextDrawColor(playerid,playerTradeText[playerid][1], -106), PlayerTextDrawShow(playerid, playerTradeText[playerid][1]);
	    PlayerTextDrawSetString(playerid, playerTradeText[playerid][1], "FINALIZAR");
	}

	if (playerTrade[wplayerid][p_trade_ready])
	{
	    PlayerTextDrawColor(playerid,playerTradeText[playerid][2], 336860415), PlayerTextDrawShow(playerid, playerTradeText[playerid][2]);
	    PlayerTextDrawColor(playerid,playerTradeText[playerid][3], 842150655), PlayerTextDrawShow(playerid, playerTradeText[playerid][3]);
	    PlayerTextDrawSetString(playerid, playerTradeText[playerid][3], "PRONTO");
	} else {
	    PlayerTextDrawColor(playerid,playerTradeText[playerid][2], 505290495), PlayerTextDrawShow(playerid, playerTradeText[playerid][2]);
	    PlayerTextDrawColor(playerid,playerTradeText[playerid][3], -106), PlayerTextDrawShow(playerid, playerTradeText[playerid][3]);
	    PlayerTextDrawSetString(playerid, playerTradeText[playerid][3], "Adicionando...");
	}
}

stock playerCheckValues(playerid)
{
	new wplayerid = playerTrade[playerid][p_trade_playerid];

	if (Player_GetMoney(playerid) < playerTrade[wplayerid][p_trade_money])
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não tem a quantidade de dinheiro necessária."), SendClientMessage(wplayerid, COLOR_LIGHTRED, "O jogador não tem a quantidade de dinheiro necessária."), 0;

	if (PlayerInfo[playerid][pOuros] < playerTrade[wplayerid][p_trade_ouros])
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não tem a quantidade de ouros necessária."), SendClientMessage(wplayerid, COLOR_LIGHTRED, "O jogador não tem a quantidade de ouros necessária."), 0;

	if (Player_GetCash(playerid) < playerTrade[wplayerid][p_trade_cash])
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não tem a quantidade de cash necessária."), SendClientMessage(wplayerid, COLOR_LIGHTRED, "O jogador não tem a quantidade de cash necessária."), 0;

	for(new index; index < MAX_PLAYER_TRADE_ITENS; index++)
	{
	    if (!playerTradeItens[wplayerid][index][p_trade_valid]) continue;

	    switch (playerTradeItens[wplayerid][index][p_trade_type])
	    {
			case TRADE_TYPE_HOUSE:
			{
			    if (!Houses_CheckLimit(playerid))
	    			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não pode ter mais casas."), SendClientMessage(wplayerid, COLOR_LIGHTRED, "O jogador não pode ter mais casas."), 0;
			}
			case TRADE_TYPE_FAZENDA:
			{
				return SendClientMessage(playerid, COLOR_LIGHTRED, "Sistema inativo."), 0;
				// if (!Fazenda_CheckLimit(playerid) || !PlayerInfo[playerid][pVIP]) {
	    		// 	return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não pode ter mais fazendas ou não é VIP."), SendClientMessage(wplayerid, COLOR_LIGHTRED, "O jogador não pode ter mais fazendas."), 0;
				// }
			}
			case TRADE_TYPE_PROPRIEDADE:
			{
			    if (!CheckLimitProps(playerid))
	    			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não pode ter mais propriedades."), SendClientMessage(wplayerid, COLOR_LIGHTRED, "O jogador não pode ter mais propriedades."), 0;
			}
			case TRADE_TYPE_VEICULOS:
			{
			    if (!CheckMaxPlayerVehicles(playerid))
			        return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não pode ter mais veiculos."), SendClientMessage(wplayerid, COLOR_LIGHTRED, "O jogador não pode ter mais veiculos."), 0;
			}
	    }
	}

	return 1;
}

stock playerGiveTradeItens(playerid)
{
    new wplayerid = playerTrade[playerid][p_trade_playerid];

	if(playerid == wplayerid || !strcmp(PlayerName[wplayerid], PlayerName[playerid], false)) {
		ServerLog::("bug_negociar", "%s está tentando finalizar negociação consigo mesmo.", PlayerName[playerid]);
		return;
	}

    new log_string[349];

    MEGAString[0] = EOS;

    strcat(MEGAString, "{FFFFFF}* A negociação foi finalizada, veja abaixo o que foi negociado:\n\n");

    strcat(MEGAString, "{00AAFF}Itens recebidos:{FFFFFF}\n");

    format(log_string, sizeof log_string, "%s > %s:", PlayerName[wplayerid], PlayerName[playerid]);

	for(new index; index < MAX_PLAYER_TRADE_ITENS; index++)
	{
	    if (!playerTradeItens[wplayerid][index][p_trade_valid]) continue;

		new id = playerTradeItens[wplayerid][index][p_trade_unique_id];
	    switch (playerTradeItens[wplayerid][index][p_trade_type])
	    {
			case TRADE_TYPE_ITEM:
			{
				format(log_string, sizeof log_string, "%s %s(%d),", log_string, InventarioInfo[wplayerid][id][item_nome], InvItem_GetQuantity(wplayerid, id));

			    format(MEGAString, 550, "%s%d Unid. de %s\n", MEGAString, InvItem_GetQuantity(wplayerid, id), InventarioInfo[wplayerid][id][item_nome]);
				// setar item para o jogador
			    givePlayerItem(playerid, InventarioInfo[wplayerid][id][item_type], InventarioInfo[wplayerid][id][item_model], InvItem_GetQuantity(wplayerid, id), InventarioInfo[wplayerid][id][item_nome], InventarioInfo[wplayerid][id][item_cor1], InventarioInfo[wplayerid][id][item_cor2]);
			    // resetar item do outro
			    InvItem_Reset(wplayerid, id);
			}
			case TRADE_TYPE_HOUSE:
			{
			    // if (!Houses_CheckLimit(playerid)) 
				// 	continue;

				// if(!House_IsOwner(wplayerid, id))
				// 	continue;

			    // format(log_string, sizeof log_string, "%s Casa ID: %d,", log_string, id);

			    // format(MEGAString, 550, "%sCasa ID: %d\n", MEGAString, id);

				// format(HouseInfo[id][hDono], MAX_PLAYER_NAME, PlayerName[playerid]);
				// HouseInfo[id][hDonoID] = PlayerInfo[playerid][pID];
		
				// new query[128];
				// mysql_format(MySQL_Handle, query, sizeof query, "UPDATE `casas` SET `dono` = '%d' WHERE `id` = '%d'", PlayerInfo[playerid][pID], id);
				// mysql_tquery(MySQL_Handle, query);

			    // updateHouseStats(id);
			}
			// case TRADE_TYPE_FAZENDA:
			// {
			//     if (!Fazenda_CheckLimit(playerid)) 
			// 		continue;

			// 	if(!Fazenda_IsOwner(id, PlayerInfo[wplayerid][pID]))
			// 		continue;

			//     format(log_string, sizeof log_string, "%s Fazenda ID: %d,", log_string, id);

			//     format(MEGAString, 550, "%sFazenda ID: %d\n", MEGAString, id);

            //     Fazenda_SetOwner(id, playerid);
			// }
			case TRADE_TYPE_PROPRIEDADE:
			{
			    if (!CheckLimitProps(playerid)) 
					continue;

				if (!IsPlayerOwnerPropertie(wplayerid, id)) 
					continue;

			    format(log_string, sizeof log_string, "%s Prop ID: %d,", log_string, id);

			    format(MEGAString, 550, "%sPropriedade ID: %d\n", MEGAString, id);

			    SetPropertyOwner(id, playerid);

		        atualizarPropText( id );
		        savePropertie( id );
		    }
			case TRADE_TYPE_VEICULOS:
			{
			    if (!CheckMaxPlayerVehicles(playerid)) 
					continue;

				if (PlayerVehicleInfo[wplayerid][id][pvID] == 0)
					continue;

				new vehicle_name[30];
				GetModelStaticNameFromId(GetVehicleModel(PlayerVehicleInfo[wplayerid][id][pvID]), vehicle_name);

			    format(log_string, sizeof log_string, "%s %s: %d,", log_string, vehicle_name);

			    format(MEGAString, 550, "%sVeiculo %s\n", MEGAString, vehicle_name);

			    Player_TransferVehicle(wplayerid, playerid, id);
			}
		}
	}

	Player_RemoveMoney(playerid, playerTrade[wplayerid][p_trade_money]);
	PlayerInfo[playerid][pOuros] -= playerTrade[wplayerid][p_trade_ouros];
	Player_RemoveCash(playerid, playerTrade[wplayerid][p_trade_cash]);

	Player_AddMoney(playerid, playerTrade[playerid][p_trade_money]);
	PlayerInfo[playerid][pOuros] += playerTrade[playerid][p_trade_ouros];
	Player_AddCash(playerid, playerTrade[playerid][p_trade_cash]);

	format(log_string, sizeof log_string, "%s (Cash: +%d, Grana: +%d, Ouros: +%d)", log_string, playerTrade[playerid][p_trade_cash], playerTrade[playerid][p_trade_money], playerTrade[playerid][p_trade_ouros]);
	server_log("negociar", log_string);

	format(log_string, sizeof log_string, "%s [Cash: %d, Grana: %d, Ouros: %d] > %s [Cash: %d, Grana: %d, Ouros: %d]", PlayerName[wplayerid], Player_GetCash(wplayerid), Player_GetMoney(wplayerid), PlayerInfo[wplayerid][pOuros], PlayerName[playerid], Player_GetCash(playerid), Player_GetMoney(playerid), PlayerInfo[playerid][pOuros]);
	server_log("saldo_negociar", log_string);

    strcat(MEGAString, "\n{00AAFF}Valores cobrados:\n");

    format(MEGAString, 550, "%sDinheiro: -$%s\n", MEGAString, getFormatText(playerTrade[wplayerid][p_trade_money]));
    format(MEGAString, 550, "%sOuros: -%s\n", MEGAString, getFormatText(playerTrade[wplayerid][p_trade_ouros]));
    format(MEGAString, 550, "%sCash: -%s\n", MEGAString, getFormatText(playerTrade[wplayerid][p_trade_cash]));

    strcat(MEGAString, "\n{00AAFF}Valores recebidos:\n");

    format(MEGAString, 550, "%sDinheiro: +$%s\n", MEGAString, getFormatText(playerTrade[playerid][p_trade_money]));
    format(MEGAString, 550, "%sOuros: +%s\n", MEGAString, getFormatText(playerTrade[playerid][p_trade_ouros]));
    format(MEGAString, 550, "%sCash: +%s\n", MEGAString, getFormatText(playerTrade[playerid][p_trade_cash]));

	UpdatePlayerInfos(playerid);
	UpdatePlayerInfos(wplayerid);

    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Ok", "");
}

stock playerFinalizarTrade(playerid, wplayerid)
{
	if (!playerCheckValues(playerid) || !playerCheckValues(wplayerid))
	    return 0;

	if(!Player_Logado(playerid) || !Player_Logado(wplayerid))
		return 0;

    playerGiveTradeItens(playerid);

    playerGiveTradeItens(wplayerid);

    playerHideTradeTextdraws(playerid);

    playerHideTradeTextdraws(wplayerid);

	return 1;
}

stock playerGetTradeModel(playerid, index)
{
	new uniqueid = playerTradeItens[playerid][index][p_trade_unique_id];

	switch (playerTradeItens[playerid][index][p_trade_type])
	{
		case TRADE_TYPE_ITEM:{
		    if (InventarioInfo[playerid][uniqueid][item_type] == ITEM_TYPE_WEAPON) return GetWeaponModel(InventarioInfo[playerid][uniqueid][item_model]);
  			return InventarioInfo[playerid][uniqueid][item_model];
		}
		case TRADE_TYPE_HOUSE:       return 1273;
		case TRADE_TYPE_FAZENDA:     return 1272;
		case TRADE_TYPE_PROPRIEDADE: return 19522;
		case TRADE_TYPE_VEICULOS:    return PlayerVehicleInfo[playerid][uniqueid][pvModel];
	}
	return 999;
}

stock playerGetTradeName(playerid, index)
{
	new uniqueid = playerTradeItens[playerid][index][p_trade_unique_id];
	new modelname[45] = "_";

	switch (playerTradeItens[playerid][index][p_trade_type])
	{
		case TRADE_TYPE_ITEM:        format(modelname, sizeof modelname, "%s(%d)", InventarioInfo[playerid][uniqueid][item_nome], InvItem_GetQuantity(playerid, uniqueid));
		case TRADE_TYPE_HOUSE:       format(modelname, sizeof modelname, "Casa ID: %d", uniqueid);
		case TRADE_TYPE_FAZENDA:     format(modelname, sizeof modelname, "Fazenda ID: %d", uniqueid);
		case TRADE_TYPE_PROPRIEDADE: format(modelname, sizeof modelname, "Propriedade ID: %d", uniqueid);
		case TRADE_TYPE_VEICULOS: 	 {
			new vehicle_name[30];
			GetModelStaticNameFromId(GetVehicleModel(PlayerVehicleInfo[playerid][uniqueid][pvID]), vehicle_name);
			format(modelname, sizeof modelname, "Veiculo %s", vehicle_name);
		}
	}
	return modelname;
}

stock playerShowTradeTextdraws(playerid)
{
	for(new index; index < 19; index++)
	{
		PlayerTextDrawShow(playerid, playerTradeText[playerid][index]);

		if (index < sizeof serverTradeText)
		{
		    TextDrawShowForPlayer(playerid, serverTradeText[index]);
		}
	}
	SelectTextDraw(playerid, 0x00AAFFAA);
}

stock playerHideTradeTextdraws(playerid)
{
	if (GetPVarInt(playerid, "p_intrade") == 0)
	    return 0;

	for(new index; index < 19; index++)
	{
		PlayerTextDrawHide(playerid, playerTradeText[playerid][index]);

		if (index < sizeof serverTradeText)
		{
		    TextDrawHideForPlayer(playerid, serverTradeText[index]);
		}
	}
	CancelSelectTextDraw(playerid);

	DeletePVar(playerid, "p_intrade");

	return 1;
}

hook OnClickDynamicTextDraw(playerid, Text:textid) {

    if (GetPVarInt(playerid, "p_intrade"))
    {
		if (textid == serverTradeText[5] || textid == Text:INVALID_TEXT_DRAW)
		{
		    playerCancelTrade(playerid);

		    return 1;
		}
		else if (textid == serverTradeText[3])
		{
		    if (playerTrade[playerid][p_trade_ready])
		        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode modificar enquanto estiver pronto para a troca.");

		    playerShowTradeDialog(playerid);

		    return 1;
		}
		else if (textid == serverTradeText[4])
		{
		    if (playerTrade[playerid][p_trade_ready])
		        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode modificar enquanto estiver pronto para a troca.");

		    playerResetTradeItens(playerid);

		    return 1;
		}
		else if (textid == serverTradeText[6])
		{
		    if (playerTrade[playerid][p_trade_ready])
		        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode modificar enquanto estiver pronto para a troca.");

		    MEGAString[0] = EOS;

		    format(MEGAString, 256, "Tipo\tQuantia\nDinheiro\t%s\n", getFormatText(playerTrade[playerid][p_trade_money]));
		    format(MEGAString, 256, "%sCash\t%s\n", MEGAString, getFormatText(playerTrade[playerid][p_trade_cash]));
		    format(MEGAString, 256, "%sOuros\t%s\n", MEGAString, getFormatText(playerTrade[playerid][p_trade_ouros]));

		    ShowPlayerDialog(playerid, 12005, DIALOG_STYLE_TABLIST_HEADERS, "Selecione o que deseja modificar", MEGAString, "Selecionar", "Fechar");

		    return 1;
		}
	}
    return 1;
}

hook OnClickDynPlayerTextDraw(playerid, PlayerText:textid)
{
    if (GetPVarInt(playerid, "p_intrade"))
    {
		if (textid == playerTradeText[playerid][0])
		{
		    playerTrade[playerid][p_trade_ready] = playerTrade[playerid][p_trade_ready] ? (0) : (1);

		    if (playerTrade[playerid][p_trade_ready] && playerTrade[playerTrade[playerid][p_trade_playerid]][p_trade_ready])
		    {
		        if (!playerFinalizarTrade(playerid, playerTrade[playerid][p_trade_playerid]))
		        {
		            playerTrade[playerid][p_trade_ready] = 0;
		        }
		        return 1;
		    }

		    playerUpdateTradeTextdraws(playerid);

		    playerUpdateTradeTextdraws(playerTrade[playerid][p_trade_playerid]);

		    return 1;
		}
	}
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == 11000)
	{
	    if (response) {
	        if (InventarioInfo[playerid][listitem][item_valid])
	        {
	            playerAddTradeItem(playerid, TRADE_TYPE_ITEM, listitem);
	        } else {
	            SendClientMessage(playerid, COLOR_LIGHTRED, "* Você selecionou um item inválido.");
	            playerListInventoryItens(playerid);
	        }
	    }
	}
	else if (dialogid == 12007)
	{
	    if (response) {
	        if (PlayerVehicleInfo[playerid][listitem][pvDBID] != 0)
	        {
	            playerAddTradeItem(playerid, TRADE_TYPE_VEICULOS, listitem);
	        } else {
	            SendClientMessage(playerid, COLOR_LIGHTRED, "* Você selecionou um veículo inválido.");
	            playerListVehicles(playerid);
	        }
	    }
	}
	else if (dialogid == 12000)
	{
	    if (response) {
	        switch (listitem)
	        {
	            case 0: playerListInventoryItens( playerid );
	            case 1: {
					return SendClientMessage(playerid, -1, "Manutenção de sistema.");
					// new counter,
					// 	string[128],
					// 	MapZone:zone,
					// 	zone_name[MAX_MAP_ZONE_NAME];

					// MEGAString[0] = EOS;
					// strcat(MEGAString, "ID\tLocalização\n");
					// foreach(new casas : Houses) {
					// 	if (House_IsOwner(playerid, casas, 1) || House_IsInquilino(playerid, casas)) {
					// 		selectHouse[playerid][counter] = casas;

					// 		zone = GetMapZoneAtPoint2D(HouseInfo[casas][hEntradaX], HouseInfo[casas][hEntradaY]);
					// 		GetMapZoneName(zone, zone_name);

					// 		format(string, sizeof string, "%03d\t%s\n", casas, zone_name);
					// 		strcat(MEGAString, string);
							
					// 		counter++;
					// 	}
					// }

					// inline D_MyHouses(mdlid, mdldialogid, mdlresponse, mdllistitem, string:mdltext[]) {
					// 	#pragma unused mdlid, mdldialogid, mdltext
						
					// 	if (mdlresponse && mdllistitem != -1) {
					// 		if (selectHouse[playerid][mdllistitem] < 0 || selectHouse[playerid][mdllistitem] > MAX_HOUSES)
					// 			return SendClientMessage(playerid, -1, "Você digitou o id de uma casa inválida.");

					// 		if (House_IsOwner(playerid, selectHouse[playerid][mdllistitem])) {
					// 			playerAddTradeItem(playerid, TRADE_TYPE_HOUSE, selectHouse[playerid][mdllistitem]);
					// 		} 
					// 		else {
					// 			SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é dono dessa residência.");
					// 		}
					// 	}
					// 	return 1;
					// }
					// Dialog_ShowCallback(playerid, using inline D_MyHouses, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Selecione uma casa", MEGAString, "Selecionar", "Fechar");
				}
	            case 2: ShowPlayerDialog(playerid, 12002, DIALOG_STYLE_INPUT, " ", "Digite o ID da fazenda que deseja negociar:", "Adicionar", "Voltar");
	            case 3: {
					new prop_string[128], prop_select = 0;

					MEGAString [0] = EOS;
					strcat(MEGAString, "ID Nome da empresa\tFundos\tDespesas\tVencimento\n");
					for( new prop; prop != unid; prop++) {
						if (PropInfo[prop][eOwnerID] == PlayerInfo[playerid][pID]) {
							new days = TimestampToRemainingDays(PropInfo[prop][eVencimento]);
							if ( days <= 0 ) {
								format(prop_string, sizeof (prop_string), "%02d  %s\t{00AA00}$%s\tLuz e Água\t{00AA00}$%s\t{FF0000}VENCIDO\n", prop, PropInfo[prop][ePname], getFormatText(PropInfo[prop][eTill]), getFormatText(PropInfo[prop][eDespesas]));
							} else {
								format(prop_string, sizeof (prop_string), "%02d  %s\t{00AA00}$%s\tLuz e Água\t{00AA00}$%s\t%d dias\n", prop, PropInfo[prop][ePname], getFormatText(PropInfo[prop][eTill]), getFormatText(PropInfo[prop][eDespesas]), days);
							}
							strcat(MEGAString, prop_string);
							SelectEmpresa[playerid][prop_select] = prop;
							prop_select ++;
						}
					}

					inline D_MyProps(mdlid, mdldialogid, mdlresponse, mdllistitem, string:mdltext[])
					{
						#pragma unused mdlid, mdldialogid, mdltext
						if (mdlresponse && mdllistitem != -1) {
							new propid = SelectEmpresa[playerid][mdllistitem];

							if (IsPlayerOwnerPropertie(playerid, propid)) {
								playerAddTradeItem(playerid, TRADE_TYPE_PROPRIEDADE, propid);
							} 
							else {
								SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é dono dessa propriedade.");
							}
						} 
						return 1;
					}
					Dialog_ShowCallback(playerid, using inline D_MyProps, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Selecione uma empresa", MEGAString, "Selecionar", ""C_BACKGROUND"Fechar");
				}
	            case 4: playerListVehicles(playerid);
	        }
	    }
	}
	else if (dialogid == 12001)
	{
	    if (response) {
			SendClientMessage(playerid, -1, "Manutenção de sistema.");
	        // new houseid = strval(inputtext);

			// if (houseid < 0 || houseid > MAX_HOUSES)
			// 	return SendClientMessage(playerid, -1, "Você digitou o id de uma casa inválida.");

	        // if (House_IsOwner(playerid, houseid))
	        // {
	        //     playerAddTradeItem(playerid, TRADE_TYPE_HOUSE, houseid);
	        // } else {
	        //     SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é dono dessa residência.");
	        // }
	    } else {
	        playerShowTradeDialog(playerid);
	    }
	}
	// else if (dialogid == 12002)
	// {
	//     if (response) {
	//         new fazendaid = strval(inputtext);

	//         if (Fazenda_IsOwner(fazendaid, PlayerInfo[playerid][pID]))
	//         {
	//             playerAddTradeItem(playerid, TRADE_TYPE_FAZENDA, fazendaid);
	//         } else {
	//             SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é dono dessa fazenda.");
	//         }
	//     } else {
	//         playerShowTradeDialog(playerid);
	//     }
	// }
	else if (dialogid == 12003)
	{
	    if (response) {
	        new propid = strval(inputtext);

	        if (IsPlayerOwnerPropertie(playerid, propid))
	        {
	            playerAddTradeItem(playerid, TRADE_TYPE_PROPRIEDADE, propid);
	        } else {
	            SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é dono dessa propriedade.");
	        }
	    } else {
	        playerShowTradeDialog(playerid);
	    }
	}
	else if (dialogid == 12005)
	{
	    if (!response)
	        return 1;

		switch (listitem)
		{
		    case 0:
		    {
		        SetPVarInt(playerid, "p_trade_type", 1);
		        ShowPlayerDialog(playerid, 12006, DIALOG_STYLE_INPUT, " ", "Digite a quantidade de dinheiro que você está pedindo:", "Definir", "Cancelar");
		    }
		    case 1:
		    {
		        SetPVarInt(playerid, "p_trade_type", 2);
		        ShowPlayerDialog(playerid, 12006, DIALOG_STYLE_INPUT, " ", "Digite a quantidade de cash que você está pedindo:", "Definir", "Cancelar");
		    }
		    case 2:
		    {
		        SetPVarInt(playerid, "p_trade_type", 3);
		        ShowPlayerDialog(playerid, 12006, DIALOG_STYLE_INPUT, " ", "Digite a quantidade de ouros que você está pedindo:", "Definir", "Cancelar");
		    }
		}
		return 1;
	}
	else if (dialogid == 12006)
	{
	    if (!response)
	        return 1;

        if (GetPVarInt(playerid, "p_intrade") == 0) return SendClientMessage(playerid, COLOR_LIGHTRED, "A negociação foi cancelada!");

		new value = strval(inputtext);

		if (value < 0)
		    return SendClientMessage(playerid, COLOR_GREY, "Valor inválido.");

		switch (GetPVarInt(playerid, "p_trade_type"))
		{
		    case 1:
		    {
		        playerTrade[playerid][p_trade_money] = value;
		    }
		    case 2:
		    {
		        playerTrade[playerid][p_trade_cash] = value;
		    }
		    case 3:
		    {
          		playerTrade[playerid][p_trade_ouros] = value;
  			}
		}
	    MEGAString[0] = EOS;

	    format(MEGAString, 256, "Tipo\tQuantia\nDinheiro\t%s\n", getFormatText(playerTrade[playerid][p_trade_money]));
	    format(MEGAString, 256, "%sCash\t%s\n", MEGAString, getFormatText(playerTrade[playerid][p_trade_cash]));
	    format(MEGAString, 256, "%sOuros\t%s\n", MEGAString, getFormatText(playerTrade[playerid][p_trade_ouros]));

	    ShowPlayerDialog(playerid, 12005, DIALOG_STYLE_TABLIST_HEADERS, "Selecione o que deseja modificar", MEGAString, "Selecionar", "Fechar");

	   	if (playerTrade[playerTrade[playerid][p_trade_playerid]][p_trade_ready])
	   	{
	   	    playerTrade[playerTrade[playerid][p_trade_playerid]][p_trade_ready] = 0;

	   	    SendClientMessage(playerTrade[playerid][p_trade_playerid], COLOR_GREY, "Houve uma alteração nos valores, você deve confirmar novamente.");
	   	}

    	playerUpdateTradeTextdraws(playerid);
    	playerUpdateTradeTextdraws(playerTrade[playerid][p_trade_playerid]);
		return 1;
	}
    return 0;
}

