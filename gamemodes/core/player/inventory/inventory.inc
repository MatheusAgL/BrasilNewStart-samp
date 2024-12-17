#if defined _inc_inventory_system
	#endinput
#endif
#define _inc_inventory_system true

#include <YSI_Coding\y_hooks>

enum {
	GUNBOX_SMALL,
	GUNBOX_NORMAL,
	GUNBOX_BIG,
}

new Iterator:playerItemType[MAX_ITENS_TYPES_LIMIT]<MAX_ITENS_INVENTARIO>;

// ----------------------------------------

#include <inventory_textdraws>
#include <inventory_functions>
#include <inventory_refinator>
#include <inventory_cmds>

static 
		Statement: stmt_loadInventory,
		Statement: stmt_insertSlotInv,
		Statement: stmt_updateSlotInv,
		Statement: stmt_deleteSlotInv;

hook OnMySQLConnected() {

	// --------------------------------------------------------------------------------------------------------
	// Sistema de invent·rio - MySQL
	// --------------------------------------------------------------------------------------------------------

	static const query_loadInventory[] = 
		"SELECT `slot`, `nome`, `tipo`, `modelo`, `quantidade`, `cor1`, `cor2` FROM `inventarios` WHERE `player` = ? ORDER BY `slot` ASC";
	stmt_loadInventory = MySQL_PrepareStatement(MySQL_Handle, query_loadInventory);

	static const query_insertSlotInv[] = 
		"INSERT INTO `inventarios` (id, player, slot, nome, tipo, modelo, quantidade, cor1, cor2) \
					VALUES (DEFAULT, '?', '?', '?', '?', '?', '?', '?', '?')";
	stmt_insertSlotInv = MySQL_PrepareStatement(MySQL_Handle, query_insertSlotInv);

	static const query_updateSlotInv[] = 
		"UPDATE `inventarios` SET `nome` = '?', `tipo` = ?, `modelo` = ?, `quantidade` = ?, `cor1` = ?, `cor2` = ? WHERE `player` = ? AND `slot` = ?";
	stmt_updateSlotInv = MySQL_PrepareStatement(MySQL_Handle, query_updateSlotInv);

	static const query_deleteSlotInv[] = 
		"DELETE FROM `inventarios` WHERE `player` = ? AND `slot` = ?";
	stmt_deleteSlotInv = MySQL_PrepareStatement(MySQL_Handle, query_deleteSlotInv);

	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, const inputtext[])
{
	if (dialogid == 4300)
	{
	    if (response)
		{
		    new itemID = InvItem_GetSelected(playerid);
			new string[128];

		    if (itemID == -1) 
				return SendClientMessage(playerid, COLOR_LIGHTRED, "VocÍ n„o selecionou nenhum item em seu invent·rio.");

			switch(listitem)
			{
			    case 0:
				{
			        new id = TrashCan_Get(playerid);

					if (id == -1) return SendClientMessage(playerid, -1, "VocÍ n„o est· prÛximo de uma lixeira.");

					if (InventarioInfo[playerid][itemID][item_type] == ITEM_TYPE_SACOLAPREVISOES)
						return SendClientMessage(playerid, COLOR_LIGHTRED, "VocÍ n„o pode descartar esse item na lixeira."), false;

					if (InventarioInfo[playerid][itemID][item_type] == ITEM_TYPE_CAIXAGOLD)
						return SendClientMessage(playerid, COLOR_LIGHTRED, "VocÍ n„o pode descartar esse item na lixeira."), false;

					if (InventarioInfo[playerid][itemID][item_type] == ITEM_TYPE_DRONE)
						return SendClientMessage(playerid, COLOR_LIGHTRED, "VocÍ n„o pode descartar um veÌculo de invent·rio na lixeira."), false;

					if (InventarioInfo[playerid][itemID][item_type] == ITEM_TYPE_CONSUMIVEL)
						return SendClientMessage(playerid, COLOR_LIGHTRED, "VocÍ n„o pode descartar paleta de cores na lixeira."), false;

					if (InventarioInfo[playerid][itemID][item_type] == Pallete_InUse(playerid))
						return SendClientMessage(playerid, COLOR_LIGHTRED, "VocÍ n„o pode descartar paleta de cores em uso na lixeira."), false;

					if(strfind(InventarioInfo[playerid][listitem][item_nome], "INE", false) != -1)
						return SendClientMessage(playerid, COLOR_LIGHTRED, "VocÍ n„o pode descartar esse item na lixeira."), TrashCan_DiscardItems(playerid);

					new result = TrashCan_GiveItem(id, InventarioInfo[playerid][itemID][item_type], InventarioInfo[playerid][itemID][item_model], InventarioInfo[playerid][itemID][item_cor1],
					InventarioInfo[playerid][itemID][item_cor2], InvItem_GetQuantity(playerid, itemID), InventarioInfo[playerid][itemID][item_nome]);

					if (!result) return SendClientMessage(playerid, -1, "A lixeira est· sem espaÁo, jogue fora em outra lixeira."), false;

		   			format(string, sizeof(string), "(( %s jogou fora %d unidade(s) de %s no lixo ))", PlayerName[playerid], InvItem_GetQuantity(playerid, itemID), InventarioInfo[playerid][itemID][item_nome]);
					SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

					TrashCan_UpdateText(id);
			        InvItem_Reset(playerid, itemID);

					format(string, sizeof(string), "[LIXEIRA %d]: %s jogou %d unidade(s) de %s.", id, PlayerName[playerid], InvItem_GetQuantity(playerid, itemID), InventarioInfo[playerid][itemID][item_nome]);
					server_log("lixeira", string);
     			}
			    case 1:
			    {
					if (!IsItemDropavel(playerid, itemID))
					{
						return SendClientMessage(playerid, COLOR_LIGHTRED, " * Esse item n„o È dropavel, vocÍ sÛ pode vende-lo!");
					}

					MEGAString[0] = EOS;

					format(string, sizeof string, "{DF6176}Descartar Item: {F3F1F1}VocÍ est· descartando o item {DF6176}%s\n\n", InventarioInfo[playerid][itemID][item_nome]);
					strcat(MEGAString, string);

				    strcat(MEGAString, "{F3F1F1}Para descarta-lo, digite: {46F181}CONFIRMAR{F3F1F1} (na caixa de texto abaixo)\n\n");

					strcat(MEGAString, "{FF5252}ObservaÁ„o: {F3F1F1}N„o fazemos a devoluÁ„o apÛs confirmar essa aÁ„o!\n");

					ShowPlayerDialog(playerid, 4301, DIALOG_STYLE_INPUT, "{F3F1F1}Confirme se quer descartar", MEGAString, "Descartar", "Cancelar");
				}
			}
		}
	    return true;
	}
	else if (dialogid == 2530)
    {
        if(!response) return 1;
        
        new Float:health;
        GetPlayerHealth(playerid, health);
        if(listitem == 0) {
            SendClientMessage(playerid, -1, "VocÍ comprou um Churrasco por $20.");
            givePlayerItem(playerid, ITEM_TYPE_COMIDA, 19882, 1, "Carne Frita");
            Player_RemoveMoney(playerid, 20);
            PlayerPlaySound(playerid, 1058,  0.0, 0.0, 0.0);
        }
        else if(listitem == 1) {
            SendClientMessage(playerid, -1, "VocÍ comprou um Coxa de Frango por $11.");
            givePlayerItem(playerid, ITEM_TYPE_COMIDA, 19847, 1, "Coxa de Frango");
            Player_RemoveMoney(playerid, 11);
            PlayerPlaySound(playerid, 1058,  0.0, 0.0, 0.0);
        }
        else if(listitem == 2) {
            SendClientMessage(playerid, -1, "VocÍ comprou uma Cerveja por $15.");
            givePlayerItem(playerid, ITEM_TYPE_BEBIDA, 1484, 1, "Cerveja");
            Player_RemoveMoney(playerid, 15);
            PlayerPlaySound(playerid, 1058,  0.0, 0.0, 0.0);
        }
        else if(listitem == 3) {
            SendClientMessage(playerid, -1, "VocÍ comprou uma Coca-Cola por $11.");
            givePlayerItem(playerid, ITEM_TYPE_BEBIDA, 19835, 1, "Coca-Cola");
            Player_RemoveMoney(playerid, 11);
            PlayerPlaySound(playerid, 1058,  0.0, 0.0, 0.0);
        }
        else if(listitem == 4) {
            SendClientMessage(playerid, -1, "VocÍ comprou uma ¡gua por $9.");
            givePlayerItem(playerid, ITEM_TYPE_GARRAFA, 1668, 1, "Agua");
            Player_RemoveMoney(playerid, 9);
            PlayerPlaySound(playerid, 1058,  0.0, 0.0, 0.0);
        }
    }
    else if(dialogid == 2531)
    {
        if(!response) return 1;
        
        new Float:health;
        GetPlayerHealth(playerid, health);
        if(listitem == 0) {
            SendClientMessage(playerid, -1, "VocÍ comprou um Quent„o por $30.");
            givePlayerItem(playerid, ITEM_TYPE_COMIDA, 19346, 1, "Quentao");
            Player_RemoveMoney(playerid, 30);
            PlayerPlaySound(playerid, 1058,  0.0, 0.0, 0.0);
        }
        else if(listitem == 1) {
            SendClientMessage(playerid, -1, "VocÍ comprou uma Pipoca por $10.");
            givePlayerItem(playerid, ITEM_TYPE_COMIDA, 2881, 1, "Fatia de Pizza");
            Player_RemoveMoney(playerid, 20);
            PlayerPlaySound(playerid, 1058,  0.0, 0.0, 0.0);
        }
    }
	return 1;
}

stock InsertSlotInv(playerid, slot, const itemname[], type, model, quantity, color1, color2) {
	MySQL_BindInt(stmt_insertSlotInv, 0, Player_GetAccountID(playerid));
	MySQL_BindInt(stmt_insertSlotInv, 1, slot);
	MySQL_Bind(stmt_insertSlotInv, 2, itemname, true);
	MySQL_BindInt(stmt_insertSlotInv, 3, type);
	MySQL_BindInt(stmt_insertSlotInv, 4, model);
	MySQL_BindInt(stmt_insertSlotInv, 5, quantity);
	MySQL_BindInt(stmt_insertSlotInv, 6, color1);
	MySQL_BindInt(stmt_insertSlotInv, 7, color2);
	MySQL_ExecuteParallel(stmt_insertSlotInv);
}

stock UpdateSlotInv(playerid, slot) {
	MySQL_Bind(stmt_updateSlotInv, 0, InventarioInfo[playerid][slot][item_nome], true);
	MySQL_BindInt(stmt_updateSlotInv, 1, InventarioInfo[playerid][slot][item_type]);
	MySQL_BindInt(stmt_updateSlotInv, 2, InventarioInfo[playerid][slot][item_model]);
	MySQL_BindInt(stmt_updateSlotInv, 3, InvItem_GetQuantity(playerid, slot));
	MySQL_BindInt(stmt_updateSlotInv, 4, InventarioInfo[playerid][slot][item_cor1]);
	MySQL_BindInt(stmt_updateSlotInv, 5, InventarioInfo[playerid][slot][item_cor2]);
	MySQL_BindInt(stmt_updateSlotInv, 6, Player_GetAccountID(playerid));
	MySQL_BindInt(stmt_updateSlotInv, 7, slot);
	MySQL_ExecuteParallel(stmt_updateSlotInv);
}

stock RemoveSlotInv(playerid, slot) {
	MySQL_BindInt(stmt_deleteSlotInv, 0, Player_GetAccountID(playerid));
	MySQL_BindInt(stmt_deleteSlotInv, 1, slot);
	MySQL_ExecuteParallel(stmt_deleteSlotInv);
}

stock Inventory_AlterSlot(const nickname[], slot, item_tipo, item_modelo, item_quantity, const item_name[], item_color1, item_color2)
{
	new playerid = GetPlayerID(nickname);
	if (Player_Logado(playerid))
	{
		if (item_tipo == ITEM_TYPE_NONE)
			return InvItem_Reset(playerid, slot);

		InvItem_SetName(playerid, slot, item_name);
		InvItem_SetType(playerid, slot, item_tipo);
		InvItem_SetModel(playerid, slot, item_modelo);
		InvItem_SetQuantity(playerid, slot, item_quantity, false);
		InvItem_SetColor1(playerid, slot, item_color1);
		InvItem_SetColor2(playerid, slot, item_color2);

		if (!InvItem_IsValid(playerid, slot)) {
			InvItem_SetValid(playerid, slot, true);
			InsertSlotInv(playerid, slot, item_name, item_tipo, item_modelo, item_quantity, item_color1, item_color2);
		} else {
			UpdateSlotInv(playerid, slot);
		}

		if (Inventory_IsOpen(playerid))
			Inventory_UpdateSlot(playerid, slot);
	}
	else
	{
		new idgplayer = Player_GetAccountIDByNick(nickname);
		if (!idgplayer) return 0;

		if (item_tipo == 0) 
		{
			MySQL_BindInt(stmt_deleteSlotInv, 0, idgplayer);
			MySQL_BindInt(stmt_deleteSlotInv, 1, slot);
			MySQL_ExecuteParallel(stmt_deleteSlotInv);
		} else {
			MySQL_Bind(stmt_updateSlotInv, 0, item_name, true);
			MySQL_BindInt(stmt_updateSlotInv, 1, item_tipo);
			MySQL_BindInt(stmt_updateSlotInv, 2, item_modelo);
			MySQL_BindInt(stmt_updateSlotInv, 3, item_quantity);
			MySQL_BindInt(stmt_updateSlotInv, 4, item_color1);
			MySQL_BindInt(stmt_updateSlotInv, 5, item_color2);
			MySQL_BindInt(stmt_updateSlotInv, 6, idgplayer);
			MySQL_BindInt(stmt_updateSlotInv, 7, slot);
			MySQL_ExecuteParallel(stmt_updateSlotInv);
		}
		return 1;
	}
	return 1;
}

stock AlterItemInventory(const nickname[], isvalid, index, itemtype, modelid, quantidade, const itemnome[], itemcor1, itemcor2)
{
	new query[300],
		inventoryPlayer = Player_GetAccountIDByNick(nickname);

	if (isvalid == 1) {
		mysql_format(MySQL_Handle, query, sizeof(query), "SELECT id FROM inventarios WHERE player = %d AND slot = %d", inventoryPlayer, index);
		mysql_query(MySQL_Handle, query);

		if (MYSQL_GetRowsCount() > 0) {
			MySQL_Bind(stmt_updateSlotInv, 0, itemnome, true);
			MySQL_BindInt(stmt_updateSlotInv, 1, itemtype);
			MySQL_BindInt(stmt_updateSlotInv, 2, modelid);
			MySQL_BindInt(stmt_updateSlotInv, 3, quantidade);
			MySQL_BindInt(stmt_updateSlotInv, 4, itemcor1);
			MySQL_BindInt(stmt_updateSlotInv, 5, itemcor2);
			MySQL_BindInt(stmt_updateSlotInv, 6, inventoryPlayer);
			MySQL_BindInt(stmt_updateSlotInv, 7, index);
			MySQL_ExecuteParallel(stmt_updateSlotInv);
		}
		else {
			MySQL_BindInt(stmt_insertSlotInv, 0, inventoryPlayer);
			MySQL_BindInt(stmt_insertSlotInv, 1, index);
			MySQL_Bind(stmt_insertSlotInv, 2, itemnome, true);
			MySQL_BindInt(stmt_insertSlotInv, 3, itemtype);
			MySQL_BindInt(stmt_insertSlotInv, 4, modelid);
			MySQL_BindInt(stmt_insertSlotInv, 5, quantidade);
			MySQL_BindInt(stmt_insertSlotInv, 6, itemcor1);
			MySQL_BindInt(stmt_insertSlotInv, 7, itemcor2);
			MySQL_ExecuteParallel(stmt_insertSlotInv);
		}
	} else {
		MySQL_BindInt(stmt_deleteSlotInv, 0, inventoryPlayer);
		MySQL_BindInt(stmt_deleteSlotInv, 1, index);
		MySQL_ExecuteParallel(stmt_deleteSlotInv);
	}
}

stock Player_UseItemInv(playerid)
{
	inline D_InvUseItem(dinvid, dinvdialogid, dinvresponse, dinvlistitem, string:dinvtext[])
	{
		#pragma unused dinvid, dinvdialogid, dinvlistitem
		if (!dinvresponse)
			return 1;

		new item_quantity = strval(dinvtext),
			selected_item = InvItem_GetSelected(playerid);

		if (!strlen(dinvtext) || (item_quantity < 1 || item_quantity > 2000000))
			return SendClientMessage(playerid, COLOR_LIGHTRED, "VocÍ deve digitar a QUANTIDADE de itens que deseja usar.");

		if (InvItem_GetQuantity(playerid, selected_item) < item_quantity)
			return SendClientMessage(playerid, COLOR_LIGHTRED, "VocÍ n„o tem essa quantidade desse item.");

		utilizarItem(playerid, selected_item, item_quantity);
		return 1;
	}
	Dialog_ShowCallback(
		playerid, using inline D_InvUseItem, DIALOG_STYLE_INPUT, ""C_USE"[ USE ]", 
		""C_WHITE"VocÍ precisa digitar quantas unidades que deseja usar do item", "Usar", "Fechar"
	);
	return 1;
}

hook OnClickDynamicTextDraw(playerid, Text:textid)
{
	if (textid == Text:INVALID_TEXT_DRAW)
        Inventory_HideForPlayer(playerid);

	if (Inventory_IsOpen(playerid) && 
		!GetPVarInt(playerid, "Negociando")) {
		new itemid = InvItem_GetSelected(playerid);

		if (textid == inv_botton_use)
		{
			if (itemid == -1)
				return SendClientMessage(playerid, COLOR_ERROR, "VocÍ n„o selecionou nenhum item.");
			
			switch (InvItem_GetType(playerid, itemid))
			{
				case ITEM_TYPE_RESPEITO, ITEM_TYPE_CAIXAPEQUENA, ITEM_TYPE_CAIXAMEDIA, ITEM_TYPE_CAIXAGRANDE, ITEM_TYPE_CAIXAGIGANTE:
				{
					if (InvItem_GetQuantity(playerid, itemid) > 1)
						Player_UseItemInv(playerid);
					else
						utilizarItem(playerid, itemid);
				}
				default: 
					utilizarItem(playerid, itemid);
			}
	    }
		else if (textid == inv_botton_combine)
		{
			if (itemid == -1)
				return SendClientMessage(playerid, COLOR_ERROR, "VocÍ n„o selecionou nenhum item.");
			
			SetPVarInt(playerid, "Combinando",  1);
			SetPVarInt(playerid, "varCombinar", itemid);
			SelectTextDraw(playerid, COLOR_COMBINE);
			return 1;
		}
		else if (textid == inv_botton_move) {

			if (itemid == -1)
				return SendClientMessage(playerid, COLOR_ERROR, "VocÍ n„o selecionou nenhum item.");

			SetPVarInt(playerid, "Movendo",  1);
			SetPVarInt(playerid, "varMover", itemid);
			SelectTextDraw(playerid, COLOR_MOVE);
		    return 1;
		}
		else if (textid == inv_botton_discard)
		{
			if (itemid == -1)
				return SendClientMessage(playerid, COLOR_ERROR, "VocÍ n„o selecionou nenhum item.");

			showDroparOpcoes(playerid);
			return 1;
		}
		else if (textid == inv_botton_separate) 
		{
			if (itemid == -1)
				return SendClientMessage(playerid, COLOR_ERROR, "VocÍ n„o selecionou nenhum item.");

			inline D_InvSepareItem(dinvid, dinvdialogid, dinvresponse, dinvlistitem, string:dinvtext[])
			{
				#pragma unused dinvid, dinvdialogid, dinvlistitem
				if (!dinvresponse)
					return 1;

				new 
					item_quantity = strval(dinvtext),
					item_tipo = InvItem_GetType(playerid, itemid),
					item_modelo = InvItem_GetModel(playerid, itemid),
					item_name[30],
					item_color1 = InvItem_GetColor1(playerid, itemid),
					item_color2 = InvItem_GetColor2(playerid, itemid);

				if (item_quantity < 1 || item_quantity >= InvItem_GetQuantity(playerid, itemid))
					return SendClientMessage(playerid, COLOR_ERROR, "VocÍ precisa digitar um valor v·lido.");

				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "VocÍ n„o tem espaÁo no invent·rio.");

				format(item_name, sizeof(item_name), InvItem_GetName(playerid, itemid));
				givePlayerItem(playerid, item_tipo, item_modelo, item_quantity, item_name, item_color1, item_color2);

				InvItem_SetQuantity(playerid, itemid, InvItem_GetQuantity(playerid, itemid) - item_quantity);
				Inventory_UpdateSlot(playerid, itemid);

				SendMsgF(playerid, COLOR_LIGHTBLUE, "** VocÍ separou %d unidade(s) do item %s.", item_quantity, InvItem_GetName(playerid, itemid));
				return 1;
			}

			Dialog_ShowCallback(
				playerid, using inline D_InvSepareItem, DIALOG_STYLE_INPUT, ""C_SEPARE"[ SEPARAR ITEM ]", 
				""C_WHITE"VocÍ precisa digitar quantas unidades que deseja separar do item", "Separar", "Fechar"
			);
			return 1;
		}
		// P·gina anterior
		else if (textid == inv_botton_prevpage) 
		{
			new page = Inventory_GetPage(playerid);

			if (page > 0)
				Inventory_SetPage(playerid, page - 1), Inventory_UpdatePage(playerid);
			
			return 1;
		}
		// PrÛxima p·gina
		else if (textid == inv_botton_nextpage) 
		{
			new page = Inventory_GetPage(playerid);

			if (page < MAX_PAGES_INVENTORY) 
				Inventory_SetPage(playerid, page + 1), Inventory_UpdatePage(playerid);
			
			return 1;
		}
		else if (textid == inv_botton_close) 
		{
            Inventory_HideForPlayer(playerid);
            return 1;
		}
		else if (textid == inv_botton_organize) 
		{
			organizarPlayerInventory(playerid);
		    return 1;
		}
		else if (textid == inv_botton_trade) 
		{
			showPlayersPerto(playerid);
		    return 1;
		}
	}
	return 1;
}

CALLBACK: OnPlayerSelectedItem(playerid, slot)
{
	new last_selected = InvItem_GetSelected(playerid);
	InvItem_SetSelected(playerid, slot);
	Inventory_UpdateSelected(playerid, slot);

	if (last_selected != -1)
		Inventory_UpdateSelected(playerid, last_selected);

	if (PlayerInStore(playerid)) {
		CallLocalFunction("OnPlayerStoreSell", "dd", playerid, slot);
		return 1;
	}

	if (GetPVarInt(playerid, "Combinando")) {
		tryCombinar(playerid, GetPVarInt(playerid, "varCombinar"), slot);
		return 1;
	}
	else if (GetPVarInt(playerid, "Movendo"))
	{
		moverItem(playerid, GetPVarInt(playerid, "varMover"), slot);
		return 1;
	}

	else if (GetPVarInt(playerid, "mudarNickVeh"))
	{
		if (InventarioInfo[playerid][slot][item_type] != ITEM_TYPE_DRONE) {
			SetPVarInt(playerid, "mudarNickVeh", 0);
			SelectTextDraw(playerid, 0x9C9C9CFF);
			return SendClientMessage(playerid, -1, "VocÍ apenas pode usar esse item em veÌculos de invent·rio."), true;
		}
		if (InvItem_GetQuantity(playerid, slot) != 1) {

			SetPVarInt(playerid, "mudarNickVeh", 0);
			SelectTextDraw(playerid, 0x9C9C9CFF);
			return SendClientMessage(playerid, -1, "VocÍ precisa separar os veÌculos antes de usar o item nele."), true;
		}

		ShowPlayerDialog(playerid, 1960, DIALOG_STYLE_INPUT,
		"Adicionando nick ao seu veiculo...", "{FFFFFF}Digite abaixo o nick corretamente do player que deseja...\n\
		adicionar o nick (As letras minusculas e maiusculas diferenciam)", "Adicionar", "Cancelar");

		SetPVarInt(playerid, "mudarNickVeh", 0), SetPVarInt(playerid, "mudarNickVehID", slot);
		SelectTextDraw(playerid, 0x9C9C9CFF);
		return 1;
	}

	else if (Refinator_InUse(playerid)) {
		new type = InventarioInfo[playerid][slot][item_type],
			model = InventarioInfo[playerid][slot][item_model],
			quantity = InvItem_GetQuantity(playerid, slot);

		if (!IsRefinableItem(type, model)) {
			SelectTextDraw(playerid, 0x9C9C9CFF);
			Refinator_Cancel(playerid);

			ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, 
			""C_GRAY"Lista de refin·veis 2024",
			"\n"C_WHITE"1.\t4 Tampa -> Euros ou Jester \
			\n2.\t4 Perennial -> Alpha ou Buffalo \
			\n3.\t4 NRG-500 -> Hydra ou Maverick \
			\n4.\t4 Blista -> Tractor ou Sultan \
			\n5.\t4 Stratum -> Bloodring Banger ou Elegy \
			\n6.\t4 Bullet -> Cargobob ou Hunter \
			\n7.\t4 Vincent -> Sadler ou Bobcat", "OK", "");

			SendClientMessage(playerid, -1, "Esse item n„o È refin·vel na nova refinadora de 2024.");
			return SendClientMessage(playerid, COLOR_GRAD, "Cheque a lista para identificar quais os itens disponÌveis."), true;
		}

		if (quantity != 4) {
			SelectTextDraw(playerid, 0x9C9C9CFF);
			Refinator_Cancel(playerid);
			return SendClientMessage(playerid, -1, "Esse item n„o tem 5 unidades combinadas."), true;
		}

		SetPVarInt(playerid, "refinadoraAcessorioID", slot);
		Refinator_Start(playerid, InventarioInfo[playerid][slot][item_nome]);
		
		SelectTextDraw(playerid, 0x9C9C9CFF);
		return 1;
	}

	else if (Pallete_InUse(playerid) != -1) 
	{
		new pallete = Pallete_InUse(playerid);
	
	    if (!Inventory_IsOpen(playerid)) // Verifica se o invent·rio est· aberto
		{
       		SelectTextDraw(playerid, 0x9C9C9CFF);
      		return SendClientMessage(playerid, -1, "A aÁ„o da paleta foi cancelada pois o invent·rio foi fechado!");
		}

		if (InvItem_GetType(playerid, slot) != ITEM_TYPE_DRONE) {
			SelectTextDraw(playerid, 0x9C9C9CFF);
			return SendClientMessage(playerid, -1, "VocÍ sÛ pode usar a paleta em veÌculos de invent·rio."), true;
		}

		if (InvItem_GetQuantity(playerid, slot) != 1) {
			SelectTextDraw(playerid, 0x9C9C9CFF);
			return SendClientMessage(playerid, -1, "O veÌculo precisa ter apenas 1 unidade."), true;
		}
		CancelSelectTextDraw(playerid);

		MEGAString[0] = EOS;

		format(MEGAString, sizeof(MEGAString), 
						""C_LIGHTGREEN"[ PALETA DE CORES ]\n\n\
						"C_WHITE"VocÍ selecionou %s para pintar com as cores (1: %d) e (2: %d)\n\n\
						"C_RED"Obs: "C_WHITE"N„o reembolsamos caso usar incorretamente, digite '"C_GREEN"CONFIRMAR"C_WHITE"'.", 
						InventarioInfo[playerid][slot][item_nome], InventarioInfo[playerid][slot][item_cor1], InventarioInfo[playerid][slot][item_cor2]);

		inline D_UsePallete(did, ddialogid, dresponse, dlistitem, string:dtext[]) 
		{
			#pragma unused did, ddialogid, dlistitem, dresponse

			if (strcmp(dtext, "confirmar", true))
				return SendClientMessage(playerid, COLOR_ERROR, "VocÍ precisa digitar 'CONFIRMAR'.");

			new 
				color1 = InvItem_GetColor1(playerid, pallete),
				color2 = InvItem_GetColor2(playerid, pallete);

			InvItem_SetColor1(playerid, slot, color1);
			InvItem_SetColor2(playerid, slot, color2);
			Inventory_UpdateSlot(playerid, slot);
			UpdateSlotInv(playerid, slot);

			new string[128];
			format(string, sizeof(string), "[PALETA DE CORES] "C_WHITE"%s usou a "C_CYAN"%s"C_WHITE", para pintar: %s.", 
			PlayerName[playerid], InvItem_GetName(playerid, pallete), InvItem_GetName(playerid, slot));
			SendClientMessageToAll(COLOR_LIGHTGREEN, string);

			InvItem_Reset(playerid, pallete);
			Player_SetPaletteColor(playerid, -1, -1, -1);

			SelectTextDraw(playerid, 0x9C9C9CFF);
		}
		Dialog_ShowCallback(
			playerid, using inline D_UsePallete, DIALOG_STYLE_INPUT, 
			""C_USE"Confirmar uso", MEGAString, "Confirmar", "Fechar"
		);

		SelectTextDraw(playerid, 0x9C9C9CFF);
		return 1;
	}

	new modelid;
	if (InvItem_IsValid(playerid, slot)) {
		switch (InvItem_GetType(playerid, slot))
		{
			case ITEM_TYPE_WEAPON: {
				PlayerTextDrawSetPreviewRot(playerid, inv_item_selected[0][playerid], -16.000000, 0.000000, -55.000000, 1.000000);
				modelid = GetWeaponModel(InventarioInfo[playerid][slot][item_model]);
			}
			case ITEM_TYPE_SKIN: modelid = GetSkinModel(InventarioInfo[playerid][slot][item_model]);
			default: modelid = InventarioInfo[playerid][slot][item_model];
		}
	} else {
		modelid = -1;
	}
	PlayerTextDrawSetPreviewModel(playerid, inv_item_selected[0][playerid], modelid);
	PlayerTextDrawSetPreviewVehCol(playerid, inv_item_preview[0][playerid], InvItem_GetColor1(playerid, slot), InvItem_GetColor2(playerid, slot));
	PlayerTextDrawHide(playerid, inv_item_selected[0][playerid]);
	PlayerTextDrawSetString(playerid, inv_item_selected[1][playerid], InventarioInfo[playerid][slot][item_nome]);
	PlayerTextDrawSetString(playerid, inv_item_selected[2][playerid], "Breve descricao");
	Inventory_ShowInfo(playerid);
	return 1;
}

hook OnClickDynPlayerTextDraw(playerid, PlayerText:textid)
{
	if (Inventory_IsOpen(playerid) && !GetPVarInt(playerid, "Negociando"))
	{
		new page = Inventory_GetPage(playerid);

	    for(new text; text != MAX_INV_SLOT_PERPAGE; text++) 
		{
	        if (textid == inv_item_preview[text][playerid]) {
				new slot = text + (page * MAX_INV_SLOT_PERPAGE);
				CallLocalFunction("OnPlayerSelectedItem", "dd", playerid, slot);
			}
	    }
	}
	return 1;
}

hook OnPlayerResetVars(playerid) {
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++) {
	    InventarioInfo[playerid][inv][item_valid] 	= 0;
	    InventarioInfo[playerid][inv][item_id] 		= 0;
	    InventarioInfo[playerid][inv][item_type] 	= ITEM_TYPE_NONE;
	    InventarioInfo[playerid][inv][item_model] 	= 0;
	    InventarioInfo[playerid][inv][item_quantia] = 0;
	    InventarioInfo[playerid][inv][item_vender]  = 0;
	    InventarioInfo[playerid][inv][item_cor1] 	= 0;
	    InventarioInfo[playerid][inv][item_cor2] 	= 0;
	    format(InventarioInfo[playerid][inv][item_nome], 30, "Nenhum Item");
	}
}

stock isInventoryFull(playerid)
{
	for (new slot; slot != MAX_ITENS_INVENTARIO; slot++) if (!InvItem_IsValid(playerid, slot)) return false;
	return true;
}

stock InvItens_Count(playerid)
{
	new count;
	for (new slot; slot != MAX_ITENS_INVENTARIO; slot++) if (InvItem_IsValid(playerid, slot)) count++;

	return count;
}

stock InvItens_GetFreeSlots(playerid)
	return (MAX_ITENS_INVENTARIO - InvItens_Count(playerid));

CALLBACK: organizarInvTimer(playerid, Float:percent)
{
	if (percent >= 100.0)
	{
        percent = 100.0;
        organizarPlayerInventory(playerid);
        SetPVarInt(playerid, "timerOrganizarInv", -1);
    }
	else
	{
        percent += 1.0;
        SetPVarInt(playerid, "timerOrganizarInv", SetTimerEx("organizarInvTimer", 25, false, "if", playerid, percent));
	}
	return true;
}

new blockinv = 0;

CMD:blockinv(playerid) {

	if (Admin_GetNivel(playerid) < MASTER)
		return SendClientMessage(playerid, -1, "Comando indisponÌvel para seu cargo.");

	SendClientMessage(playerid, -1, "Comando executado!");

	if (blockinv == 0)
		blockinv = 1;
	else
		blockinv = 0;

	return 1;
}

stock organizarPlayerInventory(playerid)
{
	if (blockinv == 0)
		return SendClientMessage(playerid, -1, "O sistema de organizar est· em manutenÁ„o temporariamente."), false;

	if (gettime() < GetPVarInt(playerid, "organizarInv"))
	    return ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "-", ""C_ALERT"VocÍ organizou seu invent·rio h· poucos segundos.", "OK", "");

	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++) {
		if (InventarioInfo[playerid][inv][item_vender])
			return ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "-", ""C_ALERT"VocÍ est· negociando, finalize a negociaÁ„o para organizar o invent·rio.", "OK", "");
	}

	for (new types; types < MAX_ITENS_TYPES_LIMIT; types++)
		Iter_Clear(playerItemType[types]);

	// Loop nos itens
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++) {
		if (InventarioInfo[playerid][inv][item_valid]) {
			itensPlayer[inv][item_valid] = 			InventarioInfo[playerid][inv][item_valid];
			itensPlayer[inv][item_type] = 			InventarioInfo[playerid][inv][item_type];
			itensPlayer[inv][item_model] = 			InventarioInfo[playerid][inv][item_model];
			itensPlayer[inv][item_quantia] = 		InvItem_GetQuantity(playerid, inv);
			format(itensPlayer[inv][item_nome], 30, InventarioInfo[playerid][inv][item_nome]);
			itensPlayer[inv][item_cor1] = 			InventarioInfo[playerid][inv][item_cor1];
			itensPlayer[inv][item_cor2] = 			InventarioInfo[playerid][inv][item_cor2];

			InvItem_Reset(playerid, inv);
			Iter_Add(playerItemType[itensPlayer[inv][item_type]], inv);
		}
	}

	// Dar todos os itens novamente(Ordem definida pelo ID do tipo)
	for(new types; types < MAX_ITENS_TYPES_LIMIT; types++) {
		foreach(new inv : playerItemType[types]) {
			if (itensPlayer[inv][item_valid]) {
				givePlayerItem(playerid, itensPlayer[inv][item_type], itensPlayer[inv][item_model], itensPlayer[inv][item_quantia], itensPlayer[inv][item_nome], itensPlayer[inv][item_cor1], itensPlayer[inv][item_cor2]);
	        }
	    }
	}

    InvItem_SetSelected(playerid, -1);
    SetPVarInt(playerid, "organizarInv", gettime() + 120);
	Inventory_SetOpen(playerid, true);
	SetPVarInt(playerid, "Combinando", 0);
	SetPVarInt(playerid, "Movendo", 0);
	Acessorie_Select(playerid, false);
	Refinator_Cancel(playerid);
	Inventory_Show(playerid);
	Inventory_UpdatePage(playerid);
	SelectTextDraw(playerid, 0xFFFFFFFF);
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "-", ""C_LIGHTGREEN"VocÍ organizou seu invent·rio com sucesso.", "OK", "");
	return 1;
}

stock getPlayerItemInfo(playerid, itemid, &valid, &type, &modelid, &quantidade, itemnome[])
{
	if (!InventarioInfo[playerid][itemid][item_valid]) return false;
	
	valid 		= InventarioInfo[playerid][itemid][item_valid];
  	type 		= InventarioInfo[playerid][itemid][item_type];
	modelid 	= InventarioInfo[playerid][itemid][item_model];
	quantidade 	= InvItem_GetQuantity(playerid, itemid);
	format(itemnome, 75, InventarioInfo[playerid][itemid][item_nome]);

	return true;
}

stock createDroppedItem(Float:x, Float:y, Float:z, const itemnome[], type, model, quantia, world = 0, house = 0, cor1 = 0, cor2 = 0)
{
	if (quantia < 1 || type == ITEM_TYPE_NONE) return false;

	for(new drop; drop != MAX_DROP_ITENS; drop++)
	{
	    if (!DropItensInfo[drop][drop_valid])
		{
	        new drop_string[128];

	        DropItensInfo[drop][drop_valid] = 1;

	        DropItensInfo[drop][drop_x] = x;
	        DropItensInfo[drop][drop_y] = y;
	        DropItensInfo[drop][drop_z] = z;

	        DropItensInfo[drop][drop_type] = type;
	        DropItensInfo[drop][drop_model] = model;
	        DropItensInfo[drop][drop_quantia] = quantia;
	        DropItensInfo[drop][drop_world] = world;
	        DropItensInfo[drop][drop_house] = house;
	        
	        DropItensInfo[drop][drop_cor1] = cor1;
	        DropItensInfo[drop][drop_cor2] = cor2;

	        format(DropItensInfo[drop][drop_nome], 75, itemnome);
	        
	        switch (type)
	        {
				case ITEM_TYPE_WEAPON:
				{
					DropItensInfo[drop][drop_object] = CreateDynamicObject(GetWeaponModel(model), DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 93.7, 120.0, random(360), world);

					format(drop_string, sizeof (drop_string), "Item: %s\nBala(s): %d", itemnome, quantia);
				}
				case ITEM_TYPE_EXPLOSIVO:
				{
					DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], -90.0, 0.0, random(360), world);

					format(drop_string, sizeof (drop_string), "Item: %s\nUnidade(s): %d", itemnome, quantia);
				}
				case ITEM_TYPE_REMEDIO:
				{
					DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), world);

					format(drop_string, sizeof (drop_string), "Item: %s\nUnidade(s): %d", itemnome, quantia);
				}
				case ITEM_TYPE_GASOLINA:
				{
					DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], -90.0, 0.0, random(360), world);

					format(drop_string, sizeof (drop_string), "Item: %s\nLitro(s) %d", itemnome, quantia);
				}
				case ITEM_TYPE_SKATE, ITEM_TYPE_COMIDA, ITEM_TYPE_CELULAR:
				{
					DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), world);

					format(drop_string, sizeof (drop_string), "Item: %s\nUnidade(s): %d", itemnome, quantia);
				}
				case ITEM_TYPE_DRONE:
				{
					DropItensInfo[drop][drop_object] = CreateDynamicObject(2485, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), -1, -1, -1, 80.0);
                	format(drop_string, sizeof (drop_string), "%s", itemnome);
				}
				case ITEM_TYPE_SKIN:
				{
					DropItensInfo[drop][drop_object] = CreateDynamicObject(2846, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), -1, -1, -1, 80.0);
               		format(drop_string, sizeof (drop_string), "%s", itemnome);
				}
				default:
				{
                    DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), world);

			    	format(drop_string, sizeof (drop_string), "Item: %s\nUnidade(s): %d", itemnome, quantia);
			    }
			}
			DropItensInfo[drop][drop_text] = CreateDynamic3DTextLabel(drop_string, 0xFFFFFF50,
			DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world);

			return true;
	    }
	}
	return false;
}

stock loadInventory(playerid)
{
	new query[128];

	mysql_format(MySQL_Handle, query, sizeof query, "SELECT slot, nome, tipo, modelo, quantidade, cor1, cor2 FROM inventarios WHERE player = %d", Player_GetAccountID(playerid));
	mysql_tquery(MySQL_Handle, query, "OnInventoryLoaded", "d", playerid);
}

CALLBACK:OnInventoryLoaded(playerid) {
	new rows = MYSQL_GetRowsCount();
	for(new i = 0; i < rows; i++) {
		new slot = MYSQL_GetInt(i, "slot");
		format(InventarioInfo[playerid][slot][item_nome], 30, MYSQL_GetString(i, "nome"));
		InventarioInfo[playerid][slot][item_type] 	= MYSQL_GetInt(i, "tipo");
		InventarioInfo[playerid][slot][item_model] 	= MYSQL_GetInt(i, "modelo");
		InventarioInfo[playerid][slot][item_quantia] = MYSQL_GetInt(i, "quantidade");
		InventarioInfo[playerid][slot][item_cor1] 	= MYSQL_GetInt(i, "cor1");
		InventarioInfo[playerid][slot][item_cor2] 	= MYSQL_GetInt(i, "cor2");
		InventarioInfo[playerid][slot][item_valid] 	= 1;

		if (strlen(InventarioInfo[playerid][slot][item_nome]) < 3)
			InvItem_Reset(playerid, slot);
	}

	PlayerInfo[playerid][pInventoryLoaded] = true;

	if(PlayerInfo[playerid][pMats] > 0) {
		if(givePlayerItem(playerid, ITEM_TYPE_MATERIAL, 2040, PlayerInfo[playerid][pMats], "Material")) {
			PlayerInfo[playerid][pMats] = 0;
		}
	}
}

stock Inventory_ShowInfo(playerid)
{
	for (new loop = 1; loop < sizeof(inv_background); loop++)
		TextDrawShowForPlayer(playerid, inv_background[loop]);

	for (new loop; loop < sizeof(inv_item_selected); loop++)
		PlayerTextDrawShow(playerid, inv_item_selected[loop][playerid]);
	
	TextDrawShowForPlayer(playerid, inv_botton_use);
	TextDrawShowForPlayer(playerid, inv_botton_move);
	TextDrawShowForPlayer(playerid, inv_botton_combine);
	TextDrawShowForPlayer(playerid, inv_botton_separate);
	TextDrawShowForPlayer(playerid, inv_botton_discard);
}

stock Inventory_Show(playerid)
{
	for (new loop; loop < MAX_INV_SLOT_PERPAGE; loop++) {
	    PlayerTextDrawShow(playerid, inv_item_preview[loop][playerid]);
	    PlayerTextDrawShow(playerid, inv_item_preview_qtd[loop][playerid]);
	    PlayerTextDrawShow(playerid, inv_item_preview_rarity[loop][playerid]);
	}
	PlayerTextDrawShow(playerid, inv_page_number[playerid]);
	PlayerTextDrawShow(playerid, inv_total_items[playerid]);
	TextDrawShowForPlayer(playerid, inv_background[0]);
	TextDrawShowForPlayer(playerid, inv_botton_close);
	TextDrawShowForPlayer(playerid, inv_botton_organize);
	TextDrawShowForPlayer(playerid, inv_botton_trade);
	TextDrawShowForPlayer(playerid, inv_botton_prevpage);
	TextDrawShowForPlayer(playerid, inv_botton_nextpage);
}

stock Inventory_Hide(playerid) 
{
	for (new loop; loop < MAX_INV_SLOT_PERPAGE; loop++) {
	    PlayerTextDrawHide(playerid, inv_item_preview[loop][playerid]);
	    PlayerTextDrawHide(playerid, inv_item_preview_qtd[loop][playerid]);
	    PlayerTextDrawHide(playerid, inv_item_preview_rarity[loop][playerid]);
	}
	PlayerTextDrawHide(playerid, inv_page_number[playerid]);
	PlayerTextDrawHide(playerid, inv_total_items[playerid]);
	TextDrawHideForPlayer(playerid, inv_background[0]);
	TextDrawHideForPlayer(playerid, inv_background[1]);

	for (new loop; loop < sizeof(inv_background); loop++)
		TextDrawHideForPlayer(playerid, inv_background[loop]);

	for (new loop; loop < sizeof(inv_item_selected); loop++)
		PlayerTextDrawHide(playerid, inv_item_selected[loop][playerid]);
	
	TextDrawHideForPlayer(playerid, inv_botton_close);
	TextDrawHideForPlayer(playerid, inv_botton_organize);
	TextDrawHideForPlayer(playerid, inv_botton_trade);
	TextDrawHideForPlayer(playerid, inv_botton_use);
	TextDrawHideForPlayer(playerid, inv_botton_move);
	TextDrawHideForPlayer(playerid, inv_botton_combine);
	TextDrawHideForPlayer(playerid, inv_botton_separate);
	TextDrawHideForPlayer(playerid, inv_botton_discard);
	TextDrawHideForPlayer(playerid, inv_botton_prevpage);
	TextDrawHideForPlayer(playerid, inv_botton_nextpage);

	// Store_Hide(playerid);
}

CMD:inventario(playerid)
{
	if (IsPlayerWithHandsUp(playerid)) 
		return true;

	if (Inventory_IsOpen(playerid) ||
		!PlayerInfo[playerid][pInventoryLoaded] ||
		GetPVarInt(playerid, "p_intrade") ||
		GetPVarInt(playerid, "varEditing") ||
		GetPlayerAnimationIndex(playerid) == 1130 ||
		gettime() < GetPVarInt(playerid, #isPlayerEnteringVehicle) ||
		(GetPlayerAnimationIndex(playerid) >= 958 && GetPlayerAnimationIndex(playerid) <= 978) ||
		GetPlayerAnimationIndex(playerid) == 1134 ||
		GetPVarInt(playerid, "Abordado") ||
		Player_InMenu(playerid) ||
		Player_GetJailed(playerid) || 
		PlayerInfo[playerid][pHospital] ||
		GetPVarInt(playerid, "ExplodindoPorta") || 
		IsPlayerInDrone(playerid) || 
		(PlayerInEvento(playerid) && !Admin_GetNivel(playerid))) {
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "VocÍ n„o pode abrir o invent·rio agora.");
	}

	if (GetPVarInt(playerid, "BlockInventory"))
		return SendClientMessage(playerid, -1, "VocÍ est· temporariamente proibido de abrir o invent·rio");

	if (!IsPlayerInAnyVehicle(playerid) && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_USEJETPACK) {
		SetPlayerAttachedObject(playerid, Slot_Mochila, 19559,6,-0.018999,0.224000,-0.078999,60.800003,15.400002,66.199981);
		ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 1, 0, 0, 0, 0);
	}

	if (GetPVarInt(playerid, "Searching"))
		HidePlayerSearch(playerid);

	if (HasPlayerAnyPopup(playerid))
		foreach(new popup : IterPlayerPopUps[playerid]) HidePlayerPopUp(playerid, popup);

	InvItem_SetSelected(playerid, -1);
	Inventory_SetOpen(playerid, true);
	SetPVarInt(playerid, "Combinando",  0);
	SetPVarInt(playerid, "Movendo",  0);
	SetPVarInt(playerid, "boneItem", -1);
	Inventory_Show(playerid);
	Inventory_UpdatePage(playerid);
	SelectTextDraw(playerid, 0x9C9C9C80);
	return 1;
}

stock updateInventoryText(playerid)
{
	new string[89];	
	format(string, sizeof string, "itens: %d/%d", InvItens_Count(playerid), MAX_ITENS_INVENTARIO);
	PlayerTextDrawSetString(playerid, inv_total_items[playerid], string);
}

stock Inventory_UpdatePreview(playerid, slot)
{
	new model = InvItem_GetModel(playerid, slot),
		page = Inventory_GetPage(playerid),
		first_slot = (page * MAX_INV_SLOT_PERPAGE),
		textid = slot - (first_slot);

	if (InvItem_IsValid(playerid, slot)) 
	{
		switch (InvItem_GetType(playerid, slot))
		{
			case ITEM_TYPE_WEAPON: {
				PlayerTextDrawSetPreviewRot(playerid, inv_item_preview[textid][playerid], -16.000000, 0.000000, -55.000000, 1.000000);
				model = GetWeaponModel(model);
			}
			case ITEM_TYPE_MOTORISTA, ITEM_TYPE_PILOTO, ITEM_TYPE_MARUJO, ITEM_TYPE_EXPLOSIVO: {
				PlayerTextDrawSetPreviewRot(playerid, inv_item_preview[textid][playerid], -16.000000, 0.000000, 180.000000, 1.000000);
			}
			case ITEM_TYPE_DRONE: {
				PlayerTextDrawSetPreviewVehCol(playerid, inv_item_preview[textid][playerid], InvItem_GetColor1(playerid, slot), InvItem_GetColor2(playerid, slot));
			}
			case ITEM_TYPE_SKIN: {
				model = GetSkinModel(model);
			}
			case ITEM_TYPE_PANEL: {
				model = 19805;
			}
		}
	} else model = -1;

	PlayerTextDrawSetPreviewModel(playerid, inv_item_preview[textid][playerid], model);
	PlayerTextDrawHide(playerid, inv_item_preview[textid][playerid]);
	Inventory_UpdateQuantity(playerid, slot);
	updateInventoryText(playerid);

	if (Inventory_IsOpen(playerid)) {
		PlayerTextDrawShow(playerid, inv_item_preview[textid][playerid]);
		PlayerTextDrawShow(playerid, inv_item_preview_qtd[textid][playerid]);
		PlayerTextDrawShow(playerid, inv_item_preview_rarity[textid][playerid]);
	}
}

stock InvSlot_GetPage(slot)
{
	switch (slot)
	{
		case 0..19: return 0;
		case 20..39: return 1;
		case 40..59: return 2;
		case 60..79: return 3;
	}
	return -1;
}

stock Inventory_UpdateSelected(playerid, slot)
{
	new page = Inventory_GetPage(playerid);

	if (InvSlot_GetPage(slot) != page)
		return 1;

	new textid = slot - (page * MAX_INV_SLOT_PERPAGE);

	if (Inventory_IsOpen(playerid)) 
	{
		if (InvItem_GetSelected(playerid) == slot)
			PlayerTextDrawBackgroundColour(playerid, inv_item_preview[textid][playerid], 60);
		else
			PlayerTextDrawBackgroundColour(playerid, inv_item_preview[textid][playerid], 250);

		PlayerTextDrawShow(playerid, inv_item_preview[textid][playerid]);
	}
	return 1;
}
	
stock Inventory_UpdatePage(playerid)
{
	new string[75],
		page = Inventory_GetPage(playerid),
		first_slot = (page * MAX_INV_SLOT_PERPAGE);

	for (new slot = first_slot; slot < (page + 1) * MAX_INV_SLOT_PERPAGE; slot++) {
		Inventory_UpdateSlot(playerid, slot);
	}
	format(string, sizeof(string), "Pagina %d", (page + 1));
	PlayerTextDrawSetString(playerid, inv_page_number[playerid], string);
}

stock Inventory_UpdateQuantity(playerid, slot) 
{
	new string[11],
		page = Inventory_GetPage(playerid),
		textid = slot - (page * MAX_INV_SLOT_PERPAGE);

	if (InvItem_IsValid(playerid, slot))
		format(string, sizeof(string), "%d", InvItem_GetQuantity(playerid, slot));
	else
		format(string, sizeof(string), "_");
	
	PlayerTextDrawSetString(playerid, inv_item_preview_qtd[textid][playerid], string);
	
	return 1;
}

stock Inventory_UpdateSlot(playerid, slot)
{
	if (slot < 0 || slot >= MAX_ITENS_INVENTARIO) 
		return 0;

    new page = Inventory_GetPage(playerid),
		textid = slot - (page * MAX_INV_SLOT_PERPAGE);
	if (textid < 0 || textid > 19) 
		return 0;

	Inventory_UpdatePreview(playerid, slot);
	Inventory_UpdateSelected(playerid, slot);
	
	return 1;
}

IsItemCombinavel(itemtype)
{
	switch(itemtype) {
	    case ITEM_TYPE_WEAPON, ITEM_TYPE_MACONHA, ITEM_TYPE_COCAINA, ITEM_TYPE_CRACK, ITEM_TYPE_HEROINA, ITEM_TYPE_METANFETAMINA, ITEM_TYPE_DINHEIRO, 
		ITEM_TYPE_RESPEITO, ITEM_TYPE_COMIDACRU, ITEM_TYPE_CONTRATO, ITEM_TYPE_CAIXAPEQUENA, ITEM_TYPE_CAIXAMEDIA, ITEM_TYPE_CAIXAGRANDE, ITEM_TYPE_CAIXAGIGANTE: return true;
	}
	return false;
}

IsItemFiftyCombinavel(itemtype)
{
	switch(itemtype)
	{
	    case ITEM_TYPE_REMEDIO, ITEM_TYPE_MEDKIT, ITEM_TYPE_REMEDIOP: return true;
	}
	return false;
}

itemIsNotCombinavel(itemtype)
{
	switch(itemtype)
	{
	    case ITEM_TYPE_LIXO: return true;
	}
	return false;
}

stock DroneAleatorio(playerid)
{
	new randomDrone = random(211) + 400;

	switch (randomDrone)
	{
	    case 406, 417, 425, 430, 432, 434, 435, 441, 442, 446, 447, 448, 449, 450, 452, 453, 454, 460,464, 465, 469, 472, 473, 476, 484, 486, 487, 488, 493, 497, 511, 512, 513, 519, 520, 532,
		537, 538, 548, 553, 556, 557, 563, 564, 568, 569, 570, 577, 584, 588, 590, 591, 592, 593, 594, 595, 601, 606, 607, 608, 609, 610, 611: return DroneAleatorio(playerid), false;
 	}
 	SetPVarInt(playerid, "vehAleatorio", randomDrone);

	return true;
}

stock usePlayerCaixa(playerid, caixatype, caixamodel, quantidade, cor1, cor2, itemname[])
{
	new rand_respeito  				= 0,
		rand_dinheiro  				= 0,
		rand_acessorio				= 0,
		rand_caixas					= 0,
		rand_acessoriosacola 		= 0,
		rand_acessoriocomunista 	= 0,
		rand_acessoriopatriota 		= 0,
		rand_acessorionatal 		= 0,
		rand_acessoriojoao  		= 0,
		rand_acessoriobooster  		= 0,
		rand_veiculo				= 0,
		rand_veiculomaleta			= 0,
		rand_veiculobooster			= 0,
		rand_extras	   				= 0,
		rand_vip       				= 0,
		rand_cash      				= 0,
		rand_laser          		= 0,
		rand_lendaria				= 0,
		rand_orgmes         		= 0,
		rand_caixastaff				= 0,
		rand_caixamesadm			= 0,
		rand_platina   				= 0,
		rand_socioult  				= 0,
		rand_revoltado				= 0,
		rand_bruno					= 0,
		rand_poderosa				= 0,
		rand_arraia					= 0,
		rand_comunista				= 0,
		rand_patriota				= 0,
		rand_boosters				= 0,
		rand_sacolap       			= 0,
		rand_nivel          		= 0,
		rand_mochilap       		= 0,
		rand_halloween 				= 0,
		rand_natal 					= 0,
		rand_reveillon 				= 0,
		rand_maletajoao				= 0;

	switch (caixatype) {
	    case ITEM_TYPE_CAIXAPEQUENA: {
			for(new q; q < quantidade; q++) {
				rand_respeito += (random(1) + 1);
				rand_dinheiro += (random(250) + 50);
			}
	    }
	    case ITEM_TYPE_CAIXAMEDIA: {
	        for(new q; q < quantidade; q++) {
				rand_respeito += (random(2) + 1);
				rand_dinheiro += (random(450) + 50);
			}
	    }
	    case ITEM_TYPE_CAIXAGRANDE: {
			for(new q; q < quantidade; q++) {
				rand_respeito += (random(2) + 2);
				rand_dinheiro += (random(500) + 100);
			}
	    }
	    case ITEM_TYPE_CAIXAGIGANTE: {
			for(new q; q < quantidade; q++) {
				rand_respeito += (random(3) + 2);
				rand_dinheiro += (random(700) + 300);
			}
	    }
	    case ITEM_TYPE_CAIXAGOLD: {
			rand_extras    = 1;
	        rand_vip       = (random(1) + 2);
	        rand_respeito  = (random(5) + 3);
	        rand_dinheiro  = (random(500) + 1000);
	        rand_cash      = (random(100) + 100);
	    }
		case ITEM_TYPE_CAIXAPLATINA: {
			rand_extras    = 1;
	        rand_vip       = (random(3) + 1);
	        rand_respeito  = (random(8) + 4);
	        rand_dinheiro  = (random(2000) + 3000);
	        rand_cash      = (random(300) + 200);
			rand_platina   = 1;
	    }
		case ITEM_TYPE_CAIXALENDARIA: {
	        rand_vip       = (random(4) + 2);
	        rand_respeito  = (random(10) + 5);
	        rand_dinheiro  = (random(3000) + 5000);
	        rand_cash      = (random(500) + 300);
			rand_lendaria  = 1;
		}
		case ITEM_TYPE_CAIXAREVOLTADO: {
			rand_respeito  = (random(5) + 3);
			rand_dinheiro  = (random(2000) + 3000);
			rand_revoltado = 1;
	    }
		case ITEM_TYPE_CAIXAPODEROSA: {
			rand_respeito  = (random(4) + 1);
			rand_dinheiro  = (random(2000) + 150);
			rand_poderosa  = 1;
	    }
		case ITEM_TYPE_CAIXASTAFF:
		{
	        rand_respeito  = random(7) + 3;
	        rand_dinheiro  = random(10000) + 5000;

	        rand_extras    = 1;
	        rand_laser     = 1;
	        rand_vip       = random(3) + 3;
	        rand_cash      = random(200) + 50;
			rand_caixastaff = 1;
	    }
		case ITEM_TYPE_CAIXAMESADM:
		{
	        rand_respeito  = random(10) + 3;
	        rand_dinheiro  = random(20000) + 7500;

	        rand_extras    = 1;
	        rand_laser     = 1;
			rand_acessorio = 1;
	        rand_vip       = random(5) + 2;
	        rand_cash      = random(200) + 90;
			rand_caixamesadm = 1;
	    }
		case ITEM_TYPE_SACOLAARRAIA:
		{
			rand_respeito += (random(4)+1);
			rand_dinheiro += (random(2000)+150);
			rand_arraia  = 1;
	    }
		case ITEM_TYPE_SACOLACOMUNISTA:
		{
			rand_respeito += (random(4)+1);
			rand_dinheiro += (random(2000)+150);
			rand_comunista  = 1;
	    }
		case ITEM_TYPE_SACOLAPATRIOTA:
		{
			rand_respeito += (random(4)+1);
			rand_dinheiro += (random(2000)+150);
			rand_patriota  = 1;
		}
		case ITEM_TYPE_SACOLABOOSTERS:
		{
			rand_respeito += (random(10)+5);
			rand_dinheiro += (random(100000)+15000);

			rand_cash      = random(1000) + 150;
			rand_boosters  = 1;
			rand_vip       = random(6) + 1;
			rand_acessoriobooster	= 1;

			rand_veiculobooster = 1;

			SendClientMessage(playerid, -1, "{3244A8}ChiLeZiNhO: {29DFFF}diz: {FFFFFF}Obrigado por impulsionar nosso discord!");
		}
		case ITEM_TYPE_CAIXABRUNO:
		{
			rand_respeito += (random(4)+1);
			rand_dinheiro += (random(2000)+150);
			rand_bruno  = 1;
	    }
	    case ITEM_TYPE_SACOLAPREVISOES:
		{
			rand_extras    = 1;
	        rand_respeito  = random(3) + 2;
	        rand_dinheiro  = random(100) + 1000;
	        rand_cash      = random(40) + 10;

	        if (PlayerInfo[playerid][pVIP] > 0) rand_vip = 1;
			else rand_vip = 2;

	        rand_sacolap   = 1;
	    }
	    case ITEM_TYPE_ORGMES:
		{
	        rand_respeito  = random(3) + 3;
	        rand_dinheiro  = random(100) + 1000;

	        rand_extras    = 1;
	        rand_laser     = 1;
	        rand_orgmes    = 1;
	        rand_vip       = random(3) + 3;
	        rand_cash      = random(199) + 10;
	    }
		case ITEM_TYPE_ULTIMATE:
		{
	        rand_respeito  = random(3) + 4;
	        rand_dinheiro  = random(100) + 10000;

	        rand_vip       = random(2) + 1;
	        rand_cash      = random(500) + 50;
      		rand_socioult  = 1;
	    }
		case ITEM_TYPE_HALLOWEEN:
		{
	        rand_respeito += (random(4)+1);
			rand_dinheiro += (random(2000)+150);
			rand_halloween  = 1;

	        /*rand_vip       = random(2) + 1;
	        rand_cash      = random(300) + 50;
			rand_laser = 1;*/
	    }
		case ITEM_TYPE_MALETAJOAO:
		{
	        rand_respeito += (random(4)+1);
			rand_dinheiro += (random(2000)+150);
			rand_maletajoao  = 1;

	        rand_vip       = random(6) + 1;
	        rand_cash      = random(600) + 50;
			rand_acessoriojoao = 1;

			rand_veiculomaleta = 1;
	    }
		case ITEM_TYPE_NATAL:
		{
	        rand_respeito  = random(10) + 4;
	        rand_dinheiro  = random(60000) + 15000;

	        rand_vip       = random(6) + 1;
	        rand_cash      = random(500) + 50;
			rand_acessorionatal = 1;
			rand_natal 		= 1;

			SendClientMessage(playerid, -1, "{E41B17}Papai Noel {A9A9A9}diz: {FFFFFF}Ho! Ho! Ho! Feliz Natal !");
	    }
	    case ITEM_TYPE_MOCHILAPREMIADA:
	    {
	        rand_extras         = 1;
	        rand_mochilap       = 1;
	        rand_vip            = 2;
	        rand_cash           = random(400) + 800;
	    }
		case ITEM_TYPE_REVEILLON:
		{
			rand_extras    = 1;
	        rand_respeito  = random(3) + 10;
	        rand_dinheiro  = random(100) + 1000;
	        rand_cash      = random(40) + 50;

	        if (PlayerInfo[playerid][pVIP] > 0) rand_vip = 1;
			else rand_vip = 2;

	        rand_reveillon   = 1;
	    }
		case ITEM_TYPE_CAIXA_ITEM_VEICULAR:
		{
			rand_respeito = random(4)+1;
			rand_dinheiro = random(3500)+120;
	    }
		default:
		{
			rand_respeito  = random(3) + 4;
	        rand_dinheiro  = random(30000) + 1000;
			//rand_cash      = random(50);
		}
	}

	// Mostrar dialog dos itens ganho
	MEGAString[0] = EOS;
	new string[185];

	strcat(MEGAString, "{DBDCE0}Itens que ganhou na caixa:\n\n");

	if (rand_respeito)
	{
		format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Respeito: {FFFFFF}%d {7D8084}unidade(s)\n", rand_respeito);
		strcat(MEGAString, string);

		addQuantiaItem(playerid, ITEM_TYPE_RESPEITO, 19941, rand_respeito, "Respeito", 0, 0);
	}
	if (rand_dinheiro)
	{
		format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Dinheiro: {00AA00}$%s\n", getFormatText(rand_dinheiro));
		strcat(MEGAString, string);

		addQuantiaItem(playerid, ITEM_TYPE_DINHEIRO, 1212, rand_dinheiro, "Dinheiro", 0, 0);
	}
	if (rand_nivel)
	{
	    format(string, sizeof (string), "{7D8084}◊ {DBDCE0}NÌvel: {FFFFFF}%d {7D8084}unidade(s)\n", rand_nivel);
		strcat(MEGAString, string);

		PlayerInfo[playerid][pLevel] += rand_nivel;
	}

	if (rand_socioult == -1)
	{
	    DroneAleatorio(playerid);

	    new modelvehicle = GetPVarInt(playerid, "vehAleatorio");

		new vehicle_name[30];
		GetModelStaticNameFromId(modelvehicle, vehicle_name);

		format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Raro: {6A4949}%s {7D8084}(veÌculo de invent·rio)\n", vehicle_name);
		strcat(MEGAString, string);

		format(string, sizeof string, "(%s) ª {FFFFFF}%s ganhou um {7D8084}%s {FFFFFF}de invent·rio, aleatÛriamente.", itemname, PlayerName[playerid], vehicle_name);
	    SendClientMessageToAll(0x00AA00FF, string);

	    format(string, sizeof string, "[SACOLA EXTREME]: %s ganhou o veÌculo %s aleatÛrio.", PlayerName[playerid], vehicle_name);
		server_log("raros", string);

		if (!isInventoryFull(playerid)) {
	     	givePlayerItem(playerid, ITEM_TYPE_DRONE, modelvehicle, 1, vehicle_name, cor1, cor2);
	 	} else {
	 		dropItem(playerid, ITEM_TYPE_DRONE, modelvehicle, 1, vehicle_name, cor1, cor2);
			SendClientMessage(playerid, COLOR_LIGHTRED, "O item raro foi dropado no ch„o pois o invent·rio est· full.");
		}
	}

	if (rand_lendaria) {
		new rdon = random(8);

		switch(rdon)
		{
			case 1, 2, 3:
			{
				if (caixamodel == ITEM_MODEL_SACO_GRAVIDO) {
					strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}Acsr. Clothes M {7D8084}(1 unidade)\n");
					givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 1275, 1, "Acsr. Clothes M");
				} else {
					strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}Acsr. Taca de vinho {7D8084}(1 unidade)\n");
					givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 1667, 1, "Acsr. Taca de vinho");
				}
			}
			case 4, 5, 6:
			{
				if (caixamodel == ITEM_MODEL_SACO_GRAVIDO) {
					strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}Two Players {7D8084}(1 unidade)\n");
					givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 1314, 1, "Acsr. Two Players");
				} else {
					strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}Acsr. Jack Daniels {7D8084}(1 unidade)\n");
					givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 1512, 1, "Acsr. Jack Daniels");
				}
			}
			default:
			{
				if (caixamodel == ITEM_MODEL_SACO_GRAVIDO) {
					strcat(MEGAString, "{7D8084}◊ {DBDCE0}DecoraÁ„o: {FFFFFF}Light Pink {7D8084}(1 unidade)\n");
					givePlayerItem(playerid, ITEM_TYPE_DECORACAO, 19127, 1, "Dec. Light Pink");
				} else {
					strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}Acsr. Redlabel {7D8084}(1 unidade)\n");
					givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19820, 1, "Acsr. Redlabel");
				}
			}
		}
	}

	if (rand_caixas)
	{
		new rdon = random(12);

		switch(rdon)
		{
			case 1, 2, 3:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Caixa Surpresa: {FFFFFF}Pequena {7D8084}(5 unidades)\n");

				givePlayerItem(playerid, ITEM_TYPE_CAIXAPEQUENA, 19054, 5, "Caixa Surpresa Pequena");
			}
			case 4, 5, 6:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Caixa Surpresa: {FFFFFF}MÈdia {7D8084}(3 unidades)\n");

				givePlayerItem(playerid, ITEM_TYPE_CAIXAMEDIA, 19055, 3, "Caixa Surpresa Media");
			}
		    case 7, 8:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Caixa Surpresa: {FFFFFF}Grande {7D8084}(2 unidades)\n");

				givePlayerItem(playerid, ITEM_TYPE_CAIXAGRANDE, 19056, 2, "Caixa Surpresa Grande");
			}
			case 9, 10:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Caixa Surpresa: {FFFFFF}Gigante {7D8084}(2 unidades)\n");

				givePlayerItem(playerid, ITEM_TYPE_CAIXAGRANDE, 19058, 2, "Caixa Surpresa Gigante");
			}
			case 11:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Caixa Surpresa: {FEE73A}GOLD {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_CAIXAGOLD, 19057, 1, "Caixa Surpresa Gold");
			}
			default:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Caixa Surpresa: {FFFFFF}Pequena {7D8084}(5 unidades)\n");

				givePlayerItem(playerid, ITEM_TYPE_CAIXAPEQUENA, 19054, 5, "Caixa Surpresa Pequena");
			}
		}
	}

	if (rand_acessorio)
	{
		new rdon = random(8);

		switch(rdon)
		{
			case 1, 2, 3:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Crowbar {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 18634, 1, "ASCR. Crowbar");
			}
			case 4, 5:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Chapeu Fazendeiro {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19553, 1, "ASCR. Chapeu Fazendeiro");
			}
		    case 6, 7:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Placa Nuclear {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 11700, 1, "ASCR. Placa Nuclear");
			}
			default:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Colete Construtor {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19904, 1, "ASCR. Colete Construtor");
			}
		}
	}

	if (rand_acessorionatal)
	{
		new rdon = random(9);

		switch(rdon)
		{
			case 1, 2, 3:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Gorro de Natal {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19065, 1, "ASCR. Gorro de Natal");
			}
			case 4, 5:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Cervo {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19315, 1, "ASCR. Cervo");
			}
		    case 6, 7:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Bola Vermelha {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19060, 1, "ASCR. Bola Vermelha");
			}
			case 8:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Cruz {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 11712, 1, "ASCR. Cruz");
			}
			default:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Bola Verde {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19061, 1, "ASCR. Bola Verde");
			}
		}
	}

	if (rand_acessoriojoao)
	{
		new rdon = random(20);

		switch(rdon)
		{
			case 1, 2, 3:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Cigarro do Joao {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19625, 1, "ASCR. Cigarro do Joao");
			}
			case 4, 5:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Refrigerante do Joao {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 2601, 1, "ASCR. Refrigerante do Joao");
			}
		    case 6, 7, 8, 9, 10:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Hamburger do Joao {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 2880, 1, "ASCR. Hamburger do Joao");
			}
			case 11:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Shotgun do Joao {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 349, 1, "ASCR. Shotgun do Joao");
			}
		}
	}

	if (rand_acessoriobooster)
	{
		new rdon = random(20);

		switch(rdon)
		{
			case 1, 2, 3:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Cigarro {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19625, 1, "ASCR. Cigarro");
			}
			case 4, 5:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Galao de Gasolina {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 1650, 1, "ASCR. Galao de Gasolina");
			}
		    case 6, 7, 8, 9, 10:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Hamburger {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 2880, 1, "ASCR. Hamburger");
			}
			case 11:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Shotgun {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 349, 1, "ASCR. Shotgun");
			}
		}
	}

	if (rand_acessoriosacola)
	{
		new rdon = random(8);

		switch(rdon)
		{
			case 1, 2:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. M·scara do Diabo {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 11704, 1, "ASCR. Mascara do Diabo");
			}
			case 3, 4:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Medkit da Katarina {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 11738, 1, "ASCR. Medkit da Katarina");
			}
		    case 5:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Black Hat {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 18639, 1, "ASCR. Black Hat");
			}
			case 6:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}Bandeira Comunista {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19306, 1, "ASCR. Bandeira Comunista");
			}
			case 7:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}Bandeira Vermelha {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19307, 1, "ASCR. Bandeira Vermelha");
			}
			default:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Marreta do Everson Zoio {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19631, 1, "ASCR. Marreta do Zoio");
			}
		}
	}

	if (rand_acessoriocomunista)
	{
		new rdon = random(8);

		switch(rdon)
		{
			case 1, 2:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Chave Inglesa {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 18633, 1, "ASCR. Chave Inglesa");
			}
			case 3, 4:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Martelo {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 18635, 1, "ASCR. Martelo");
			}
		    case 5:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Black Hat {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 18639, 1, "ASCR. Black Hat");
			}
			case 6:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Capacete de Construtor {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 18638, 1, "ASCR. Capacete Construtor");
			}
			case 7:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Placa STOP {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19966, 1, "ASCR. Placa STOP");
			}
			default:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. ChapÈu Comunista {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 18934, 1, "ASCR. Chapeu Comunista");
			}
		}
	}

	if (rand_acessoriopatriota)
	{
		new rdon = random(8);

		switch(rdon)
		{
			case 1, 2:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Capacete do ExÈrcito {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19110, 1, "ASCR. Capacete Exercito");
			}
			case 3, 4:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. ”culos Policial {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19140, 1, "ASCR. Oculos Policial");
			}
		    case 5:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Banana {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19578, 1, "ASCR. Banana");
			}
			case 6:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Cigarro do Theus {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19625, 1, "ASCR. Cigarro do Theus");
			}
			case 7:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Placa de ProibiÁ„o {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19967, 1, "ASCR. Placa Proibicao");
			}
			default:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}AcessÛrio: {FFFFFF}ASCR. Entidade FBI {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19776, 1, "ASCR. Entidade FBI");
			}
		}
	}

	if (rand_veiculo)
	{
		new rdon = random(3);

		switch(rdon)
		{
			case 1:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Raro: {FFFFFF}Tampa {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_DRONE, 549, 1, "Tampa");

				format(string, sizeof string, "ª {FFFFFF}%s ganhou um {7D8084}Tampa {FFFFFF}de invent·rio, pela {00FF00}Caixa Surpresa Poderosa.", PlayerName[playerid]);
	    		SendClientMessageToAll(0x00AA00FF, string);
			}
			case 2:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Raro: {FFFFFF}Windsor {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_DRONE, 555, 1, "Windsor");

				format(string, sizeof string, "ª {FFFFFF}%s ganhou um {00CED1}Windsor {FFFFFF}de invent·rio, pela {00FF00}Caixa Surpresa Poderosa.", PlayerName[playerid]);
	    		SendClientMessageToAll(0x00AA00FF, string);
			}
			default:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Raro: {FFFFFF}Tampa {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_DRONE, 549, 1, "Tampa");

				format(string, sizeof string, "ª {FFFFFF}%s ganhou um {7D8084}Tampa {FFFFFF}de invent·rio, pela {00FF00}Caixa Surpresa Poderosa.", PlayerName[playerid]);
	    		SendClientMessageToAll(0x00AA00FF, string);
			}
		}
	}

	if (rand_veiculomaleta)
	{
		new rdon = random(5);

		switch(rdon)
		{
			case 1:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Raro: {FFFFFF}Tampa {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_DRONE, 549, 1, "Tampa");

				format(string, sizeof string, "ª {FFFFFF}%s ganhou um {7D8084}Tampa {FFFFFF}de invent·rio, pela {4169E1}Maleta{FFFFFF} do Joao.", PlayerName[playerid]);
	    		SendClientMessageToAll(0x00AA00FF, string);
			}
			case 2:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Raro: {FFFFFF}Clover {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_DRONE, 542, 1, "Clover");

				format(string, sizeof string, "ª {FFFFFF}%s ganhou um {00CED1}Clover {FFFFFF}de invent·rio, pela {4169E1}Maleta{FFFFFF} do Joao.", PlayerName[playerid]);
	    		SendClientMessageToAll(0x00AA00FF, string);
			}
			case 3:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Raro: {FFFFFF}Romero {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_DRONE, 442, 1, "Romero");

				format(string, sizeof string, "ª {FFFFFF}%s ganhou um {DB7093}Romero {FFFFFF}de invent·rio, pela {4169E1}Maleta{FFFFFF} do Joao.", PlayerName[playerid]);
	    		SendClientMessageToAll(0x00AA00FF, string);
			}
		}
	}

	if (rand_veiculobooster)
	{
		new rdon = random(5);

		switch(rdon)
		{
			case 1:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Raro: {FFFFFF}Euros {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_DRONE, 587, 1, "Euros");

				format(string, sizeof string, "ª {FFFFFF}%s ganhou um {7D8084}Euros {FFFFFF}de invent·rio, pela {4169E1}Sacola{29DFFF} de Boosters.", PlayerName[playerid]);
	    		SendClientMessageToAll(0x00AA00FF, string);
			}
			case 2:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Raro: {FFFFFF}Feltzer {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_DRONE, 533, 1, "Feltzer");

				format(string, sizeof string, "ª {FFFFFF}%s ganhou um {00CED1}Feltzer {FFFFFF}de invent·rio, pela {4169E1}Sacola{29DFFF} de Boosters.", PlayerName[playerid]);
	    		SendClientMessageToAll(0x00AA00FF, string);
			}
			case 3:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}LENDARIO: {FFFFFF}Hustler {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_DRONE, 545, 1, "Hustler");

				format(string, sizeof string, "ª {FFFFFF}%s ganhou um {DB7093}Hustler {FFFFFF}de invent·rio, pela {4169E1}Sacola{29DFFF} de Boosters.", PlayerName[playerid]);
	    		SendClientMessageToAll(0x00AA00FF, string);
			}
		}
	}

	if (rand_extras)
	{
		new rdon = random(13);

		switch(rdon)
		{
			case 1, 2, 9:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Respawn Carros Org {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_RESPAWNORG, 1, "Respawn Carros Org");
			}
			case 4, 5:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Limpar procurado {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_PROCURADO, 1, "Limpar procurado");
			}
		    case 3:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Blindar veÌculo {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_BLINDAR_CARRO, 1, "Blindar veiculo");
			}
			case 6:
			{
			    new rdon2 = random(5)+2;

			    format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Pontos de advogado {7D8084}(%d unidade)\n", rdon2);
				strcat(MEGAString, string);

				givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_PONTOS_ADVOGADO, rdon2, "Pontos de Advogado");
			}
			case 11:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Refinadora de Itens {7D8084}(1 unidade)\n");

				givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_REFINADORA, 1, "Refinadora de Itens");
			}
			default:
			{
				strcat(MEGAString, "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Ir para HQ {7D8084}(1 unidade)\n");

                givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_IRPARAHQ, 1, "Ir para HQ");
			}
		}
	}

	if (rand_cash)
	{
		format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Cash: {00FF00}${FFFFFF}%s\n", getFormatText(rand_cash));
		strcat(MEGAString, string);
		Player_AddCash(playerid, rand_cash);
	}

	if (rand_platina)
	{
		new rdon = random(15);

		switch(rdon) {

			case 1, 9, 12:
			{
			    format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Respawn Carros Org {7D8084}(1 unidade)\n");
				strcat(MEGAString, string);

				givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_RESPAWNORG, 1, "Respawn Carros Org");
			}
			case 4, 5, 13:
			{
				format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Limpar procurado {7D8084}(1 unidade)\n");
				strcat(MEGAString, string);

				givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_PROCURADO, 1, "Limpar procurado");
			}
		    case 3:
			{
			    format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Blindar veÌculo {7D8084}(1 unidade)\n");
				strcat(MEGAString, string);

				givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_BLINDAR_CARRO, 1, "Blindar veiculo");
			}
			case 6:
			{
			    format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Paleta (Nevoa/Porcelana) {7D8084}(1 unidade)\n");
				strcat(MEGAString, string);

				givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_PALETA, 1, "Paleta (Nevoa/Porcelana)", 15, 14);
			}
			case 10:
			{
			    new rdon2 = random(5)+2;

			    format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Pontos de advogado {7D8084}(%d unidade)\n", rdon2);
				strcat(MEGAString, string);

				givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_PONTOS_ADVOGADO, rdon2, "Pontos de Advogado");
			}
			case 14:
			{
			    format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Paleta (Porcelana/Nevoa) {7D8084}(1 unidade)\n");
				strcat(MEGAString, string);

				givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_PALETA, 1, "Paleta (Porcelana/Nevoa)", 14, 15);
			}
			default:
			{
				format(string, sizeof (string), "{7D8084}◊ {DBDCE0}Extra: {FFFFFF}Ir para HQ {7D8084}(1 unidade)\n");
				strcat(MEGAString, string);

                givePlayerItem(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_IRPARAHQ, 1, "Ir para HQ");
			}
		}
	}
	if (rand_natal) {
		if(random(12) < 4) {
			givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19065, 1, "Gorro - Natal 2022");
			format(string, sizeof (string), "◊ {DBDCE0}AcessÛrio: {FFFFFF}Gorro - Natal 2022 {7D8084}(1 unidade)\n");
			strcat(MEGAString, string);
		}
		if(random(10) < 3) {
			givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19315, 1, "Rena de Natal");
			format(string, sizeof (string), "◊ {DBDCE0}AcessÛrio: {FFFFFF}Rena de Natal {7D8084}(1 unidade)\n");
			strcat(MEGAString, string);
		}
	}

	if (rand_laser)
	{
		format(string, sizeof (string), "◊ {DBDCE0}AcessÛrio: {FFFFFF}Laser {7D8084}(1 unidade)\n");
		strcat(MEGAString, string);

		new rdon = random(6);

		switch(rdon)
		{
            case 0: givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19080, 1, "Laser");
			case 1: givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 18643, 1, "Laser");
			case 2: givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19082, 1, "Laser");
		    case 3: givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19081, 1, "Laser");
			case 4: givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19084, 1, "Laser");
			default: givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19083, 1, "Laser");
		}
	}

	if(caixatype == ITEM_TYPE_CAIXA_ITEM_VEICULAR) {
		enum AccBoxInfo {
			accName[35],
			accModel
		};
		static const accessories[][AccBoxInfo] = {
			{"Caixa de Som G", 2232},
			{"Caixa de Som P", 2229},
			{"Neon Roxo", 18651},
			{"Neon Azul", 18648},
			{"Neon Amarelo", 18649},
			{"Neon Vermelho", 18647},
			{"Neon Branco", 18652},
			{"Spot Verde", 19152},
			{"Spot Amarelo", 19143},
			{"Spot Vermelho", 19148},
			{"Spot Verde Claro", 19149},
			{"Spot Laranja", 19144},
			{"Roda Offroad", 1025},
			{"Roda Shadow", 1073},
			{"Roda Mega", 1074},
			{"Roda Rimshine", 1075},
			{"Roda Wires", 1076},
			{"Roda Classic", 1077},
			{"Roda Twist", 1078},
			{"Roda Cutter", 1079},
			{"Roda Switch", 1080},
			{"Roda Grove", 1081},
			{"Roda Import", 1082},
			{"Roda Dollar", 1083},
			{"Roda Trance", 1084},
			{"Roda Atomic", 1085},
			{"Roda Ahab", 1096},
			{"Roda Virtual", 1097},
			{"Roda Access", 1098},
			{"Spoiler Sultan Alien", 1138},
			{"Spoiler Sultan X-Flow", 1139},
			{"Spoiler Elegy Alien", 1146},
			{"Spoiler Elegy X-Flow", 1147},
			{"AK-47 Veicular", 355},
			{"M4 Veicular", 356},
			{"RPG Veicular", 359},
			{"Minigun Veicular", 362},
			{"Deagle Veicular", 348}
		};
		new amountItems = 1 + random(3), size = sizeof(accessories);
		for(new i = 0; i < amountItems; i++) {
			new rdon = random(10000) % size;
			givePlayerItem(playerid, ITEM_TYPE_VEH_ACCESSORY, accessories[rdon][accModel], 1, accessories[rdon][accName]);

			format(string, sizeof(string), "◊ {DBDCE0}AcessÛrio Veicular: {FFFFFF}%s {7D8084}(1 unidade)\n", accessories[rdon][accName]);
			strcat(MEGAString, string);
		}
	}

	if (rand_vip)
	{
		format(string, sizeof (string), "◊ {DBDCE0}Dias de sÛcio: {FFFFFF}+%d {7D8084}dias\n", rand_vip);
		strcat(MEGAString, string);

    	static vip_values[4]     = {1, 6, 7, 8};
	    static vip_names[9][25]  = {"Nenhum", "SÛcio Comum", "SÛcio Premium", "SÛcio Premium", "SÛcio Premium", "SÛcio Premium", "SÛcio Premium", "SÛcio Supreme", "SÛcio Extreme"};

		new vipvalues;

		if (rand_platina)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

      		SetPVarString(playerid, "textCaixaPresente", "{017bff}Caixa Surpresa Supreme");
        }
		else if (rand_lendaria)
		{
			if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

			if (caixamodel == ITEM_MODEL_SACO_GRAVIDO) {
				SetPVarString(playerid, "textCaixaPresente", "{1E4C99}Saco do Gravido");
			}
			else if (caixamodel == ITEM_MODEL_CARNAVAL_2024) {
				SetPVarString(playerid, "textCaixaPresente", "{8C52FF}Saco do {7ED957}Carnaval");
			}
      		else {
				SetPVarString(playerid, "textCaixaPresente", "{017bff}Caixa Surpresa Lendaria");
			}
        }
		else if (rand_halloween)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

      		SetPVarString(playerid, "textCaixaPresente", "{E68510}Caixa Surpresa Halloween");
        }
		else if (rand_socioult)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = 8;

		    SetPVarString(playerid, "textCaixaPresente", "{017bff}Caixa Surpresa Supreme");
		}
		else if (rand_revoltado)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{FF0000}Caixa Surpresa Revoltado");
		}
		else if (rand_poderosa)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{00FF00}Caixa Surpresa Poderosa");
		}
		else if (rand_arraia)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{FFD700}Sacola Arrai·");
		}
		else if (rand_comunista)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{E41B17}Sacola Comunista");
		}
		else if (rand_patriota)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{0000FF}Sacola de Patriota");
		}
		else if (rand_boosters)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{29DFFF}Sacola Boosters");
		}
		else if (rand_bruno)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{A020F0}Caixa Anivers·rio Bruno");
		}
		else if (rand_caixastaff)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{FF1493}Caixa Destaque Staff");
		}
		else if (rand_caixamesadm)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{FFFF00}Caixa Admin do MÍs");
		}
		else if (rand_maletajoao)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{4169E1}Maleta{FFFFFF} do Joao");
		}
		else if (rand_natal)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{C93F3C}Caixa Surpresa Natal");
		}
		else if (rand_reveillon)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = vip_values[random(sizeof(vip_values))];

		    SetPVarString(playerid, "textCaixaPresente", "{FFF1C9}Caixa Surpresa Reveillon");
		}
		else if (rand_sacolap)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = 7;

		    SetPVarString(playerid, "textCaixaPresente", "{FDC945}Sacola de Previsıes");
		}
		else if (rand_orgmes)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = 1;

		    SetPVarString(playerid, "textCaixaPresente", "{556B2F}Sacola OrganizaÁ„o MÍs");
        }
		else if (rand_mochilap)
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = 8;

		    SetPVarString(playerid, "textCaixaPresente", "{FFF000}Mochila Premiada");
		}
		else
		{
		    if (PlayerInfo[playerid][pVIP]) vipvalues = PlayerInfo[playerid][pVIP];
			else vipvalues = 1;

		    SetPVarString(playerid, "textCaixaPresente", "{FEE73A}Caixa Surpresa Gold");
		}

		new nameCaixa[42];

		GetPVarString(playerid, "textCaixaPresente", nameCaixa, sizeof nameCaixa);

		format(string, sizeof string, "Presentes ª {DEDFCD}%s abriu um(a) %s {DEDFCD}ganhou +%d dias %s e +%s cash.", PlayerName[playerid], nameCaixa, rand_vip, vip_names[vipvalues], getFormatText(rand_cash));
	 	SendClientMessageToAll(0xFFFFFFFF, string);

	 	GiveVipPresente(playerid, vipvalues, rand_vip);
	}

	strcat(MEGAString, "\n{DA5858}OBS: {7D8084}Os itens da Caixa ou Sacola est„o no seu invent·rio.");
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{7D8084}Caixa surpresa aberta", MEGAString, "Fechar", "");
	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
}

CALLBACK: tryCombinar(playerid, item1, item2)
{
	SetPVarInt(playerid, "Combinando", 0);
	SelectTextDraw(playerid, 0x00FFFFFF);

	if (item1 < 0 || item2 < 0 || item1 >= MAX_ITENS_INVENTARIO || item2 >= MAX_ITENS_INVENTARIO)
		return 0;

	if (InventarioInfo[playerid][item1][item_model] == InventarioInfo[playerid][item2][item_model] && InventarioInfo[playerid][item1][item_type] == InventarioInfo[playerid][item2][item_type] &&
	InventarioInfo[playerid][item1][item_cor1] == InventarioInfo[playerid][item2][item_cor1] && InventarioInfo[playerid][item1][item_cor2] == InventarioInfo[playerid][item2][item_cor2] && item1 != item2)
	{
		new quantity1 = InvItem_GetQuantity(playerid, item1),
			quantity2 = InvItem_GetQuantity(playerid, item2);

	    if ((quantity1 + quantity2) > 0 && itemIsNotCombinavel(InventarioInfo[playerid][item2][item_type])) {
	        SendClientMessage(playerid, COLOR_LIGHTRED, "O item selecionado n„o pode ser combinado.");
		}
	    else if ((quantity1 + quantity2) > 10
			&& !IsItemCombinavel(InventarioInfo[playerid][item2][item_type]) && !IsItemFiftyCombinavel(InventarioInfo[playerid][item2][item_type])) {
	        SendClientMessage(playerid, COLOR_LIGHTRED, "O item selecionado suporta apenas 10 unidades.");
		}
		else if ((quantity1 + quantity2) > 50
			&& !IsItemCombinavel(InventarioInfo[playerid][item2][item_type])) {
	        SendClientMessage(playerid, COLOR_LIGHTRED, "O item selecionado suporta apenas 50 unidades.");
		} else {
			InvItem_SetQuantity(playerid, item2, (quantity2 + quantity1));
			InvItem_Reset(playerid, item1);
		}
	}
	else SendClientMessage(playerid, COLOR_LIGHTRED, " * N„o foi possÌvel combinar os dois Itens !");

	InvItem_SetSelected(playerid, -1);

	Inventory_UpdateSlot(playerid, item1);
	Inventory_UpdateSlot(playerid, item2);

	return false;
}

CALLBACK: moverItem(playerid, item1, item2)
{
	SetPVarInt(playerid, "Movendo", 0);
	SelectTextDraw(playerid, 0x00FFFFFF);

	if (item1 < 0 || item2 < 0 || item1 >= MAX_ITENS_INVENTARIO || item2 >= MAX_ITENS_INVENTARIO)
		return 0;

	if (!InventarioInfo[playerid][item2][item_valid]) {
	    InventarioInfo[playerid][item2][item_valid] = InventarioInfo[playerid][item1][item_valid];
	    InventarioInfo[playerid][item2][item_type] = InventarioInfo[playerid][item1][item_type];
	    InventarioInfo[playerid][item2][item_model] = InventarioInfo[playerid][item1][item_model];
	    InventarioInfo[playerid][item2][item_quantia] = InvItem_GetQuantity(playerid, item1);
	    format(InventarioInfo[playerid][item2][item_nome], 75, InventarioInfo[playerid][item1][item_nome]);
	    InventarioInfo[playerid][item2][item_cor1] = InventarioInfo[playerid][item1][item_cor1];
	    InventarioInfo[playerid][item2][item_cor2] = InventarioInfo[playerid][item1][item_cor2];

		InsertSlotInv(
			playerid, 
			item2, 
			InventarioInfo[playerid][item1][item_nome],
			InventarioInfo[playerid][item1][item_type], 
			InventarioInfo[playerid][item1][item_model], 
			InvItem_GetQuantity(playerid, item1), 
			InventarioInfo[playerid][item1][item_cor1], 
			InventarioInfo[playerid][item1][item_cor2]);

		InvItem_Reset(playerid, item1);
			
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTRED, " * N„o foi possÌvel mover este item !");
	}

	InvItem_SetSelected(playerid, -1);

	Inventory_UpdateSlot(playerid, item1);
	Inventory_UpdateSlot(playerid, item2);

	return 0;
}


stock utilizarItem(playerid, itemid, quant=1)
{
	if (itemid < 0 || itemid >= MAX_ITENS_INVENTARIO) return false;

	if (InvItem_GetQuantity(playerid, itemid))
	{
		if (!IsItemUtilizavel(playerid, itemid)) {
			SendClientMessage(playerid, COLOR_LIGHTRED, "VocÍ n„o pode usar esse item.");
			return 1;
		}

		new quantity = InvItem_GetQuantity(playerid, itemid);
		switch (InventarioInfo[playerid][itemid][item_type])
        {
            case ITEM_TYPE_RESPEITO, ITEM_TYPE_CAIXAPEQUENA, ITEM_TYPE_CAIXAMEDIA, ITEM_TYPE_CAIXAGRANDE, ITEM_TYPE_CAIXAGIGANTE: {
		        if (OnPlayerUseItem(playerid, itemid, InventarioInfo[playerid][itemid][item_nome], InventarioInfo[playerid][itemid][item_type],
				InventarioInfo[playerid][itemid][item_model], quant, InventarioInfo[playerid][itemid][item_cor1], InventarioInfo[playerid][itemid][item_cor2])) {
					quantity -= quant;
					InvItem_SetQuantity(playerid, itemid, quantity);
				}
			}
			case ITEM_TYPE_DINHEIRO, ITEM_TYPE_WEAPON, ITEM_TYPE_GASOLINA, ITEM_TYPE_COLETE: {
		        if (OnPlayerUseItem(playerid, itemid, InventarioInfo[playerid][itemid][item_nome], InventarioInfo[playerid][itemid][item_type], InventarioInfo[playerid][itemid][item_model], 
					InvItem_GetQuantity(playerid, itemid), InventarioInfo[playerid][itemid][item_cor1], InventarioInfo[playerid][itemid][item_cor2])) {
					quantity = 0;
				}
			} 
			default: {
				if (OnPlayerUseItem(playerid, itemid, InventarioInfo[playerid][itemid][item_nome], InventarioInfo[playerid][itemid][item_type], InventarioInfo[playerid][itemid][item_model],
					InvItem_GetQuantity(playerid, itemid), InventarioInfo[playerid][itemid][item_cor1], InventarioInfo[playerid][itemid][item_cor2])) {
					quantity -= 1;
					InvItem_SetQuantity(playerid, itemid, quantity);
				}
			}
		}
	  	if (quantity < 1) {
			InvItem_Reset(playerid, itemid);
			InvItem_SetSelected(playerid, -1);
			Inventory_UpdateSelected(playerid, itemid);
		}
		Inventory_UpdateSlot(playerid, itemid);
	}
	return 1;
}

CALLBACK: dropAllItensType(playerid, itemtype)
{
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++) {

		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {
            dropItem(playerid, itemtype, InventarioInfo[playerid][inv][item_model], InvItem_GetQuantity(playerid, inv), InventarioInfo[playerid][inv][item_nome], InventarioInfo[playerid][inv][item_cor1], InventarioInfo[playerid][inv][item_cor2]);
			InvItem_Reset(playerid, inv);
		}
	}
	updateInventoryText(playerid);
	return 1;
}

stock IsPlayerHaveItem(playerid, itemtype)
{
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++)
	{
		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype)
            return true;
	}
	return false;
}

stock GetPlayerItemTypeAmount(playerid, itemtype)
{
	new total = 0;
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++)
	{
		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {
            total += InvItem_GetQuantity(playerid, inv);
		}
	}
	return total;
}

stock RemovePlayerItemTypeAmount(playerid, itemtype, quantity)
{
	new remaining = quantity;
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++)
	{
		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {
            if (InvItem_GetQuantity(playerid, inv) > remaining) {
				InvItem_SetQuantity(playerid, inv, (InvItem_GetQuantity(playerid, inv) - remaining));
			} else {
				InvItem_Reset(playerid, inv);
			}
			break;
		}
	}
}

stock GetPlayerItemTypeModel(playerid, itemtype)
{
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++)
	{
		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {
            return InventarioInfo[playerid][inv][item_model];
		}
	}
	return 0;
}

stock CountPlayerItemsByType(playerid, itemtype)
{
	new count = 0;
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++)
	{
		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype && InvItem_GetQuantity(playerid, inv) > 0) 
			count += InvItem_GetQuantity(playerid, inv);
	}
	return count;
}

stock IsPlayerHaveItemModel(playerid, itemmodel, itemcor1=0, itemcor2=0)
{
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++)
	{
		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_model] == itemmodel &&
			InventarioInfo[playerid][inv][item_cor1] == itemcor1 && InventarioInfo[playerid][inv][item_cor2] == itemcor2)
			return true;
	}
	return false;
}

stock IsPlayerHaveItemColor(playerid, itemcor1, itemcor2)
{
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++)
	{
		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_cor1] == itemcor1 && InventarioInfo[playerid][inv][item_cor2] == itemcor2)
			return true;
	}
	return false;
}

CALLBACK: ResetAllItensType(playerid, itemtype) {

	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++) {

		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {

			InvItem_Reset(playerid, inv);

			if (Inventory_IsOpen(playerid)) {
		    	Inventory_UpdateSlot(playerid, inv);
		    }
		}
	}
	updateInventoryText(playerid);
	return 0;
}

CALLBACK: addQuantiaItem(playerid, itemtype, itemmodel, quantidade, const itemnome[], itemcor1, itemcor2)
{
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++)
	{
		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype && InventarioInfo[playerid][inv][item_model] == itemmodel
		&& InvItem_GetQuantity(playerid, inv) <= 1000000000 && InventarioInfo[playerid][inv][item_cor1] == itemcor1 && InventarioInfo[playerid][inv][item_cor2] == itemcor2)
		{
			if (InvItem_GetQuantity(playerid, inv) > 0)
			{
				InvItem_SetQuantity(playerid, inv, (InvItem_GetQuantity(playerid, inv) + quantidade));

				if (Inventory_IsOpen(playerid))
				{
					InvItem_SetSelected(playerid, -1);
					Inventory_UpdateSlot(playerid, inv);
				}
		    	return true;
			}
		}
		else if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype && InventarioInfo[playerid][inv][item_model] == itemmodel
		&& InvItem_GetQuantity(playerid, inv) > 1000000000 && InventarioInfo[playerid][inv][item_cor1] == itemcor1 && InventarioInfo[playerid][inv][item_cor2] == itemcor2)
		{
		    if (!isInventoryFull(playerid)) 
				return givePlayerItem(playerid, itemtype, itemmodel, quantidade, itemnome, itemcor1, itemcor2);
			else 
				return dropItem(playerid, itemtype, itemmodel, quantidade, itemnome, itemcor1, itemcor2);
		}
		else if (!InventarioInfo[playerid][inv][item_valid])
		{
		    if (!isInventoryFull(playerid)) 
				return givePlayerItem(playerid, itemtype, itemmodel, quantidade, itemnome, itemcor1, itemcor2);
			else 
				return dropItem(playerid, itemtype, itemmodel, quantidade, itemnome, itemcor1, itemcor2);
		}
	}
	return 0;
}

CALLBACK: RemoveQuantiaItem(playerid, itemtype)
{
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++)
	{
		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype)
		{
			if (InvItem_GetQuantity(playerid, inv) > 0) {
				InvItem_SetQuantity(playerid, inv, (InvItem_GetQuantity(playerid, inv) - 1));

		    	if (InvItem_GetQuantity(playerid, inv) < 1)
					InvItem_Reset(playerid, inv);

				if (Inventory_IsOpen(playerid)) {
					InvItem_SetSelected(playerid, -1);
		    	    Inventory_UpdateSlot(playerid, inv);
			    }
			    return 1;
			}
		}
	}
	return false;
}

stock removerItemTypeModel(playerid, itemtype, itemmodel, itemcor1=0, itemcor2=0)
{
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++)
	{
		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype && InventarioInfo[playerid][inv][item_model] == itemmodel &&
		InventarioInfo[playerid][inv][item_cor1] == itemcor1 && InventarioInfo[playerid][inv][item_cor2] == itemcor2)
		{
			if (InvItem_GetQuantity(playerid, inv) > 0) {
				InvItem_SetQuantity(playerid, inv, (InvItem_GetQuantity(playerid, inv) - 1));

		    	if (InvItem_GetQuantity(playerid, inv) < 1) 
					InvItem_Reset(playerid, inv);
				
				if (Inventory_IsOpen(playerid)) {
					InvItem_SetSelected(playerid, -1);
		    	    Inventory_UpdateSlot(playerid, inv);
				}
			    Inventory_UpdatePreview(playerid, inv);
			    return 1;
			}
		}
	}
	return false;
}

stock IsItemUtilizavel(playerid, itemid)
{
	switch (InventarioInfo[playerid][itemid][item_type])
	{
	    case ITEM_TYPE_MOTORISTA, ITEM_TYPE_PILOTO, ITEM_TYPE_MARUJO, ITEM_TYPE_CONTRATO, ITEM_TYPE_JETPACK,
		ITEM_TYPE_CHAVEFENDA, ITEM_TYPE_CHAVEFIXA, ITEM_TYPE_CHAVEBIELA, ITEM_TYPE_CAPACETE: return false;
	}
	return 1;
}

stock IsItemDropavel(playerid, itemid)
{
	switch(InventarioInfo[playerid][itemid][item_type])
	{
	    case ITEM_TYPE_MOTORISTA, ITEM_TYPE_PILOTO, ITEM_TYPE_MARUJO, ITEM_TYPE_CAIXAPEQUENA, ITEM_TYPE_CAIXAMEDIA, ITEM_TYPE_CAIXAGRANDE, ITEM_TYPE_CAIXAGIGANTE,
		ITEM_TYPE_CAIXAGOLD, ITEM_TYPE_DEPOSITORY, ITEM_TYPE_DECORACAO, ITEM_TYPE_DRONE, ITEM_TYPE_KID, ITEM_TYPE_HALLOWEEN, ITEM_TYPE_CAIXAPLATINA, ITEM_TYPE_CAIXAREVOLTADO, ITEM_TYPE_CAIXABRUNO, ITEM_TYPE_CAIXAPODEROSA, ITEM_TYPE_REVEILLON,
		ITEM_TYPE_ORGMES, ITEM_TYPE_CAIXASTAFF, ITEM_TYPE_CAIXAMESADM, ITEM_TYPE_SACOLAARRAIA, ITEM_TYPE_SACOLACOMUNISTA, ITEM_TYPE_SACOLAPATRIOTA, ITEM_TYPE_SACOLABOOSTERS, ITEM_TYPE_CARNAVAL, ITEM_TYPE_3ANOSBPS, ITEM_TYPE_NATAL, ITEM_TYPE_MALETAJOAO, ITEM_TYPE_KITCOP, ITEM_TYPE_KITSEXY, ITEM_TYPE_ARRAIA, ITEM_TYPE_PAPAI,
		ITEM_TYPE_CAIXAULTIMATE, ITEM_TYPE_SACOLATHEUS, ITEM_TYPE_HALLOWEEN_PLUS, ITEM_TYPE_CONSUMIVEL, ITEM_TYPE_LIXO: return false;
	}
	return true;
}

CALLBACK: droparItem(playerid, itemid)
{
	if (itemid < 0 || itemid >= MAX_ITENS_INVENTARIO)
		return false;

	if (InvItem_GetQuantity(playerid, itemid))
	{
        if (IsItemDropavel(playerid, itemid))
        	dropItem(playerid, InventarioInfo[playerid][itemid][item_type], InventarioInfo[playerid][itemid][item_model], InvItem_GetQuantity(playerid, itemid), InventarioInfo[playerid][itemid][item_nome], InventarioInfo[playerid][itemid][item_cor1], InventarioInfo[playerid][itemid][item_cor2]);

		OnPlayerDropItem(playerid, InventarioInfo[playerid][itemid][item_type], InventarioInfo[playerid][itemid][item_model], InvItem_GetQuantity(playerid, itemid), 
		InventarioInfo[playerid][itemid][item_nome], InventarioInfo[playerid][itemid][item_cor1], InventarioInfo[playerid][itemid][item_cor2]);

		InvItem_Reset(playerid, itemid);
		InvItem_SetSelected(playerid, -1);
		Inventory_UpdateSlot(playerid, itemid);
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTRED, " * N„o h· itens suficiÍntes para ser descartado !");
	}
	return 1;
}

CALLBACK: destroyDropItens()
{
	for(new drop; drop != MAX_DROP_ITENS; drop++) {
	    if (DropItensInfo[drop][drop_valid] && gettime() > DropItensInfo[drop][drop_time]) destroyDropItem(drop);
	}
}

stock GenerateTrash(playerid, modelid, amount, const text[], fixtrash=0)
{
    // Para forÁar o player dropar o item no ch„o
    if (fixtrash == 1) {
        dropItem(playerid, ITEM_TYPE_LIXO, modelid, amount, text, 0, 0, false);
    }
    else
    {
        // AleatÛriamente se vai pro invent·rio ou joga no ch„o
        // No futuro pretendo fazer um sistema de 'Comportamento' onde no /menu > Jogador, poder· definir o estilo do personagem...
        // Com isso, n„o vai ser aleatÛrio aqui, vai ser direto, se for 'Porco' joga o lixo no ch„o, mas perde respeito.. etc...

        new rand = random(10);
        
        if (rand > 5)
            // Jogador joga o item no ch„o
            dropItem(playerid, ITEM_TYPE_LIXO, modelid, amount, text, 0, 0, false);
        else
            // Jogador recebe o item no invent·rio
            givePlayerItem(playerid, ITEM_TYPE_LIXO, modelid, amount, text);
    }
}

stock dropItem(playerid, type, model, quantia, const itemnome[], itemcor1=0, itemcor2=0, bool:useanim = true)
{
	if (quantia < 1 || type == ITEM_TYPE_NONE) return false;

	if (type == ITEM_TYPE_DRONE)
		return SendClientMessage(playerid, COLOR_LIGHTRED, "N„o È possÌvel dropar um veÌculo de invent·rio"), false;

	if (strfind(itemnome, "INE", false) != -1)
		return SendClientMessage(playerid, COLOR_LIGHTRED, "N„o È possÌvel dropar esse item!"), false;

	destroyDropItens();

	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	if (!Inventory_IsOpen(playerid) && useanim) ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle",4.1,0,1,1,0,0);

	for(new drop; drop != MAX_DROP_ITENS; drop++)
	{
	    if (!DropItensInfo[drop][drop_valid])
		{
	        new drop_string[128];

	        DropItensInfo[drop][drop_valid] = 1;

	        DropItensInfo[drop][drop_x] = pos[0] + randomfloat(2.0);
	        DropItensInfo[drop][drop_y] = pos[1] - randomfloat(2.0);
	        DropItensInfo[drop][drop_z] = pos[2] - 1.0;

	        DropItensInfo[drop][drop_type] = type;
	        DropItensInfo[drop][drop_model] = model;
	        DropItensInfo[drop][drop_quantia] = quantia;
	        DropItensInfo[drop][drop_world] = GetPlayerVirtualWorld(playerid);
	        
	        DropItensInfo[drop][drop_cor1] = itemcor1;
	        DropItensInfo[drop][drop_cor2] = itemcor2;

	        format(DropItensInfo[drop][drop_nome], 75, itemnome);

	        switch(type)
			{
	            case ITEM_TYPE_WEAPON: 		DropItensInfo[drop][drop_time] 	= gettime() + (45);
	            case ITEM_TYPE_EXPLOSIVO:	DropItensInfo[drop][drop_time]	= gettime() + (8	* 60);
	            case ITEM_TYPE_REMEDIO:		DropItensInfo[drop][drop_time] 	= gettime() + (8	* 60);
	            case ITEM_TYPE_RESPEITO:	DropItensInfo[drop][drop_time] 	= gettime() + (20	* 60);
	            case ITEM_TYPE_JETPACK:		DropItensInfo[drop][drop_time] 	= gettime() + (30	* 60);
	            case ITEM_TYPE_DINHEIRO:	DropItensInfo[drop][drop_time] 	= gettime() + (20	* 60);
	            case ITEM_TYPE_MELHORIA:	DropItensInfo[drop][drop_time] 	= gettime() + (20	* 60);
	            case ITEM_TYPE_CONTRATO:	DropItensInfo[drop][drop_time] 	= gettime() + (12	* 60);
	            case ITEM_TYPE_SKATE:		DropItensInfo[drop][drop_time] 	= gettime() + (18	* 60);
	            default: 					DropItensInfo[drop][drop_time] 	= gettime() + (8	* 60);
	        }

	        if (type == ITEM_TYPE_WEAPON) {

                DropItensInfo[drop][drop_object] = CreateDynamicObject(GetWeaponModel(model), DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 93.7, 120.0, random(360), GetPlayerVirtualWorld(playerid));

				format(drop_string, sizeof (drop_string), "Item: %s\nBala(s): %d", itemnome, quantia);
			}
	        else if (type == ITEM_TYPE_EXPLOSIVO) {

                DropItensInfo[drop][drop_z] += 0.08;
                DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], -90.0, 0.0, random(360), GetPlayerVirtualWorld(playerid));

				format(drop_string, sizeof (drop_string), "Item: %s\nUnidade(s): %d", itemnome, quantia);
			}
	        else if (type == ITEM_TYPE_REMEDIO) {

                DropItensInfo[drop][drop_z] += 0.09;
                DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), GetPlayerVirtualWorld(playerid));

				format(drop_string, sizeof (drop_string), "Item: %s\nUnidade(s): %d", itemnome, quantia);
			}
	        else if (type == ITEM_TYPE_JETPACK) {

                DropItensInfo[drop][drop_z] += 0.37;
                DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 90.0, 0.0, random(360), GetPlayerVirtualWorld(playerid));

				format(drop_string, sizeof (drop_string), "Item: %s\nUnidade(s): %d", itemnome, quantia);
			}
	        else if (type == ITEM_TYPE_GASOLINA) {

                DropItensInfo[drop][drop_z] += 0.05;
                DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], -90.0, 0.0, random(360), GetPlayerVirtualWorld(playerid));

				format(drop_string, sizeof (drop_string), "Item: %s\nLitros(s): %d", itemnome, quantia);
			}
	        else if (type == ITEM_TYPE_SKATE || type == ITEM_TYPE_COMIDA || type == ITEM_TYPE_CELULAR) {

                DropItensInfo[drop][drop_z] += 0.075;
                DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), GetPlayerVirtualWorld(playerid));

				format(drop_string, sizeof (drop_string), "Item: %s\nUnidade(s): %d", itemnome, quantia);
			}
	        else if (type == ITEM_TYPE_DRONE) {
                DropItensInfo[drop][drop_object] = CreateDynamicObject(2485, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), -1, -1, -1, 80.0);
                format(drop_string, sizeof (drop_string), "%s", itemnome);

			}
	        else if (type == ITEM_TYPE_SKIN) {
                DropItensInfo[drop][drop_object] = CreateDynamicObject(2846, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), -1, -1, -1, 80.0);
                format(drop_string, sizeof (drop_string), "%s", itemnome);

			} else if (type == ITEM_TYPE_ORGAO) {
                DropItensInfo[drop][drop_object] = CreateDynamicObject(model, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), -1, -1, -1, 80.0);
                format(drop_string, sizeof (drop_string), "%s", itemnome);

			} 
			else if (type == ITEM_TYPE_LIXO) 
			{
                DropItensInfo[drop][drop_object] = CreateDynamicObject(model, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], -90.0, 0.0, random(360), GetPlayerVirtualWorld(playerid));
                format(drop_string, sizeof (drop_string), "{727272}<< LIXO >>\n{A5A3A3}%s    {FFFFFF}%d", itemnome, quantia);

				DropItensInfo[drop][drop_time] = gettime() + (120 * 60);
			}
			else 
			{
			    DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), GetPlayerVirtualWorld(playerid));

			    format(drop_string, sizeof (drop_string), "Item: %s\nUnidade(s): %d", itemnome, quantia);
			}
			DropItensInfo[drop][drop_text] = CreateDynamic3DTextLabel(drop_string, 0xFFFFFF50,
			DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GetPlayerVirtualWorld(playerid));

			return true;
	    }
	}
	return false;
}

CALLBACK: destroyDropItem(itemid)
{
	if (!DropItensInfo[itemid][drop_valid]) return false;

   	DropItensInfo[itemid][drop_valid] = 0;
	DestroyDynamicObject(DropItensInfo[itemid][drop_object]);
	DestroyDynamic3DTextLabel(DropItensInfo[itemid][drop_text]);
	
	return true;
}

CALLBACK: pickupItem(playerid)
{
	if (gettime() < GetPVarInt(playerid, "PickupItemFlood")) return false;

	SetPVarInt(playerid, "PickupItemFlood", gettime() + 2);

	for(new d; d != MAX_DROP_ITENS; d++)
	{
	    if (DropItensInfo[d][drop_valid] && GetPlayerVirtualWorld(playerid) == DropItensInfo[d][drop_world])
		{
	        if (IsPlayerInRangeOfPoint(playerid, 1.5, DropItensInfo[d][drop_x], DropItensInfo[d][drop_y], DropItensInfo[d][drop_z]))
			{
	            if (isInventoryFull(playerid))
	    			return SendClientMessage(playerid, -1, "VocÍ n„o tem espaÁo no invent·rio.");

	            ApplyAnimation(playerid, "BOMBER", "BOM_Plant_2Idle",4.1, 0, 1, 1, 0, 0);
	            
				addQuantiaItem(playerid, DropItensInfo[d][drop_type], DropItensInfo[d][drop_model], DropItensInfo[d][drop_quantia], DropItensInfo[d][drop_nome], DropItensInfo[d][drop_cor1], DropItensInfo[d][drop_cor2]);

				if (Inventory_IsOpen(playerid)) 
					Inventory_UpdatePage(playerid);
				
    			destroyDropItem(d);

				OnPlayerPickUpItem(playerid, DropItensInfo[d][drop_type], DropItensInfo[d][drop_model], DropItensInfo[d][drop_quantia], DropItensInfo[d][drop_nome], DropItensInfo[d][drop_cor1], DropItensInfo[d][drop_cor2]);

				return true;
			}
	    }
	}
	return false;
}

CALLBACK: OnPlayerPickUpItem(playerid, itemtype, modelid, quantia, itemname[], cor1, cor2)
{
	new string[90];
	
	switch(itemtype)
	{
		case ITEM_TYPE_WEAPON: format(string, sizeof(string), "* VocÍ pegou: %s, com %d bala(s)", itemname, quantia);
  		case ITEM_TYPE_MACONHA, ITEM_TYPE_COCAINA, ITEM_TYPE_CRACK: format(string, sizeof string, "* VocÍ pegou: %s, com %d grama(s)", itemname, quantia);
		default: format(string, sizeof string, "* VocÍ pegou: %s, com %d unidade(s)", itemname, quantia);
	}
	SendClientMessage(playerid, 0xFFDEADFF, string);
	
	format(string, sizeof string, "(Invent·rio): %s pegou um(a) %s | (type: %d, model: %d, cor1: %d, cor2: %d, quantia: %d).", PlayerName[playerid], itemname, itemtype, modelid, cor1, cor2, quantia);
	server_log("inventario", string);
	
	return true;
}

stock OnPlayerDropItem(playerid, itemtype, modelid, quantia, const itemname[], cor1=0, cor2=0)
{
	new string[256];

	switch (itemtype)
	{
	    case ITEM_TYPE_WEAPON:
		{
			format(string, sizeof string, "* VocÍ largou uma Arma: %s, com %d bala(s)", itemname, quantia);
		}
		case ITEM_TYPE_MACONHA, ITEM_TYPE_COCAINA, ITEM_TYPE_CRACK, ITEM_TYPE_HEROINA, ITEM_TYPE_METANFETAMINA:
		{
			format(string, sizeof string, "* VocÍ largou uma Droga: %s, com %d grama(s)", itemname, quantia);
		}
		case ITEM_TYPE_MOTORISTA:
		{
			format(string, sizeof string, "* VocÍ jogou sua carteira de motorista fora !", itemname, quantia);
		}
		case ITEM_TYPE_PILOTO:
		{
			format(string, sizeof string, "* VocÍ jogou sua licenÁa de piloto fora !", itemname, quantia);
		}
		case ITEM_TYPE_MARUJO:
		{
			format(string, sizeof string, "* VocÍ jogou sua licenÁa de navegaÁ„o fora !", itemname, quantia);
	    }
	    default:
	    {
	    	format(string, sizeof string, "* VocÍ largou um Item: %s, com %d unidade(s)", itemname, quantia);
		}
	}
	SendClientMessage(playerid, 0xFFDEADFF, string);
	
	format(string, sizeof string, "[INVENT¡RIO]: %s dropou %s | (type: %d, model: %d, cor1: %d, cor2: %d, quantia: %d).", PlayerName[playerid], itemname, itemtype, modelid, cor1, cor2, quantia);
	server_log("inventario", string);
	
	return 1;
}

stock showDroparOpcoes(playerid)
{
	ShowPlayerDialog(playerid, 4300, DIALOG_STYLE_TABLIST, "Escolha uma opÁ„o",
	"{60DCB3}Jogar no lixo\t{F3F1F1}(usado prÛximo · uma lixeira para jogar nela)\n{60DCB3}Jogar no ch„o\t{F3F1F1}(usado para dropar os itens no ch„o)", "Prosseguir", "Cancelar");
}


CALLBACK: OnPlayerUseItem(playerid, itemid, itemname[], itemtype, modelid, quantia, cor1, cor2)
{
	new string[128];

	switch (itemtype) {

		case ITEM_TYPE_NONE: {
			return 1;
		}

	    case ITEM_TYPE_WEAPON:
		{
		    if (PlayerInEvento(playerid)) 
				return SendClientMessage(playerid, -1, "VocÍ est· em um evento, n„o pode usar esse comando."), false;

	        if (GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
			{
				switch (modelid) {
				    case 24, 25, 27, 34: 
						return SendClientMessage(playerid, -1, "VocÍ n„o pode usar essa arma como passageiro."), false;
				}
			}

			if (modelid > 21 && quantia <= 1) {
				format(string, sizeof(string), "A sua %s est· sem muniÁ„o.", itemname);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				return SendClientMessage(playerid, 0x9C9C9CAA, "VocÍ pode comprar mais balas em uma Ammunation, use: (/gps > ComÈrcios > Ammunation)");
			}

            format(string, sizeof(string), "(( %s pegou uma %s com %d bala(s) em seu invent·rio ))", PlayerName[playerid], itemname, quantia);
			SendClientMessageInRange(20.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

			GivePlayerWeapon(playerid, modelid, quantia);
	    }
	    case ITEM_TYPE_RADIO:
		{
			if (IsPlayerCuffed(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode usar no momento."), false;

		 	if (PlayerInfo[playerid][segurandoRadio]) return SendClientMessage(playerid, -1, "VocÍ ja est· com sua caixa de som em m„os."), false;

		    if (isPlayerSound(playerid)) return SendClientMessage(playerid, -1, "Sua caixa de som est· tocando, desligue-a primeiro."), false;

	        format(string, sizeof string, "* VocÍ pegou um(a) %s do invent·rio.", itemname);
            SendClientMessage(playerid, 0x00CCCCFF, string);

			format(string, sizeof(string), "* %s pegou seu radio port·til.", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		    PlayerInfo[playerid][segurandoRadio] = true; SetPVarInt(playerid, "modelidRadio", modelid); SetPVarString(playerid, "nameRadioPortatil", itemname);

		    SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, modelid, 5, 0.394999, 0.045000, 0.027000, -25.299999, -101.699974, 0.000000);
	    }
	    case ITEM_TYPE_REPAIR:
		{
	        if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "VocÍ precisa estar do lado de fora do veÌculo."), false;

	        if (GetPVarInt(playerid, "consertandoVeh")) {
	            SendClientMessage(playerid, -1, "VocÍ ja est· consertando um veÌculo!");
	            return 0;
	        }

	        new vehicleid = getVehicleProxPlayer(playerid, 5.5, INVALID_VEHICLE_ID);

	        if (vehicleid == INVALID_VEHICLE_ID) {
	            SendClientMessage(playerid, -1, "VocÍ n„o est· prÛximo de nenhum veÌculo!");
	            return 0;
	        }

			new Float:healthVehicle;
			new Float:vPos[3];

			GetVehicleHealth(vehicleid, healthVehicle);
			GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);

	        if (healthVehicle >= 1000.0) {
	            SendClientMessage(playerid, -1, "Este veÌculo n„o precisa ser consertado!");
	            return 0;
	        }

	        Inventory_HideForPlayer(playerid);

	        SetPlayerCostasToPoint(playerid, vPos[0], vPos[1]);
	        ApplyAnimation(playerid,"CAR","Fixn_Car_Loop",4.1,1,0,0,1,0);
	        SetTimerEx("fixPlayerAnimation", 500, false, "d", playerid);
	        SetTimerEx("consertarVeh", 6000, false, "dd", playerid, vehicleid);
	        SetPVarInt(playerid, "consertandoVeh", 1);
	        GameTextForPlayer(playerid, "~b~Consertando veiculo~n~Aguarde...", 6000, 3);
	    }

	    case ITEM_TYPE_MACONHA, ITEM_TYPE_COCAINA, ITEM_TYPE_CRACK, ITEM_TYPE_HEROINA, ITEM_TYPE_METANFETAMINA: 
		{
			SendClientMessage(playerid, -1, "* Use /usardrogas para utilizar essas drogas.");
			return 0;
	    }
	    case ITEM_TYPE_EXPLOSIVO:
		{
  			if (PlayerInfo[playerid][pExplosives]){
  				SendClientMessage(playerid, COLOR_LIGHTRED, "* VocÍ pode carregar no m·ximo 1 explosivo !");
				return 0;
			}

	        format(string, sizeof string, "* VocÍ retirou um %s do invent·rio !", itemname);
            SendClientMessage(playerid, 0x00CCCCFF, string);

			PlayerInfo[playerid][pExplosives] = 1;
			callcmd::explosivo(playerid, "pegar");
	    }
	    case ITEM_TYPE_CAIXAPEQUENA, ITEM_TYPE_CAIXAMEDIA, ITEM_TYPE_CAIXAGRANDE, ITEM_TYPE_CAIXAGIGANTE, ITEM_TYPE_CAIXAPLATINA, ITEM_TYPE_CAIXALENDARIA, ITEM_TYPE_CAIXAREVOLTADO, ITEM_TYPE_CAIXABRUNO, ITEM_TYPE_CAIXAPODEROSA, ITEM_TYPE_NATAL_PLUS, ITEM_TYPE_REVEILLON_PRO,
		ITEM_TYPE_REVEILLON, ITEM_TYPE_ORGMES, ITEM_TYPE_CAIXASTAFF, ITEM_TYPE_CAIXAMESADM, ITEM_TYPE_CARNAVAL, ITEM_TYPE_3ANOSBPS, ITEM_TYPE_CARNAVALP, ITEM_TYPE_PASCOA, ITEM_TYPE_AMOR, ITEM_TYPE_ARRAIA, ITEM_TYPE_PAPAI, ITEM_TYPE_CAIXAULTIMATE,
		ITEM_TYPE_SACOLATHEUS, ITEM_TYPE_KID, ITEM_TYPE_SACOLAARRAIA, ITEM_TYPE_SACOLACOMUNISTA, ITEM_TYPE_SACOLAPATRIOTA, ITEM_TYPE_HALLOWEEN, ITEM_TYPE_BPSPRO, ITEM_TYPE_PASCOAP, ITEM_TYPE_MOTHER, ITEM_TYPE_MOTHERP, ITEM_TYPE_LOVEP, ITEM_TYPE_COPA, ITEM_TYPE_COPAP,
		ITEM_TYPE_SACOLATHEUS_PLUS, ITEM_TYPE_ULTIMATE, ITEM_TYPE_HALLOWEEN_PLUS, ITEM_TYPE_SACOLAPREVISOES, ITEM_TYPE_SACOLAFERIAS, ITEM_TYPE_MALETAJOAO, ITEM_TYPE_SACOLABOOSTERS, ITEM_TYPE_MOCHILAPREMIADA, ITEM_TYPE_NATAL: //ITEM_TYPE_CAIXA_ITEM_VEICULAR
		{
		    if (InvItens_GetFreeSlots(playerid) < 8) 
				return SendClientMessage(playerid, -1, "VocÍ deve ter pelo menos 8 slots em seu invent·rio para abrir a caixa."), false;

            format(string, sizeof string, "VocÍ abriu uma {DBED15}%s", itemname);
            SendClientMessage(playerid, -1, string);

            format(string, sizeof string, "[Abertura de Caixa]: O jogador: %s[%d] abriu uma %s", PlayerName[playerid], playerid, itemname);
            server_log("acaixa", string);
			usePlayerCaixa(playerid, itemtype, modelid, quantia, cor1, cor2, itemname);

			return 1;
		}
		case ITEM_TYPE_SACOLA:
		{
			if (InvItens_GetFreeSlots(playerid) < 3) 
				return SendClientMessage(playerid, -1, "Voce precisa de 3 slots livres no inventario para abrir uma sacola."), false;

			OpenSacola(playerid, modelid);

			format(string, sizeof string, "[usar item]: %s[%d] usou uma %s de seu inventario.", PlayerName[playerid], playerid, itemname);
            server_log("acaixa", string);
		}
		case ITEM_TYPE_KITCOP, ITEM_TYPE_KITSEXY:
		{
		    if (InvItens_GetFreeSlots(playerid) < 5) return SendClientMessage(playerid, -1, "VocÍ deve ter pelo menos 5 slots em seu invent·rio para abrir a caixa."), false;

           	format(string, sizeof string, "Este item ainda n„o pode ser aberto.", itemname);
           	SendClientMessage(playerid, -1, string);

           	return 0;
		}
		case ITEM_TYPE_CAIXAGOLD:
		{
            if (InvItens_GetFreeSlots(playerid) < 5) return SendClientMessage(playerid, -1, "VocÍ deve ter pelo menos 5 slots em seu invent·rio para abrir a caixa."), false;

			if (PlayerInfo[playerid][pVIP] > 0)
			{
            	format(string, sizeof string, "A caixa apenas pode ser usada em jogadores que n„o s„o sÛcios.", itemname);
            	SendClientMessage(playerid, -1, string);
            	return 0;
			}
			else
			{
				format(string, sizeof string, "VocÍ abriu uma {DBED15}%s", itemname);
            	SendClientMessage(playerid, -1, string);
            	format(string, sizeof string, "%s[ID: %d] abriu uma %s", PlayerName[playerid], playerid, itemname);
           		server_log("acaixa", string);
				usePlayerCaixa(playerid, itemtype, modelid, quantia, cor1, cor2, itemname);
			}
		}
		case ITEM_TYPE_DINHEIRO:
		{
            format(string, sizeof string, "VocÍ pegou {00AA00}$%s {FFFFFF}do seu invent·rio.", getFormatText(quantia));
            SendClientMessage(playerid, -1, string);
			Player_AddMoney(playerid, quantia);
		}
		case ITEM_TYPE_RESPEITO: {

            format(string, sizeof string, "VocÍ usou {DBED15}+%s respeito", getFormatText(quantia));
            SendClientMessage(playerid, -1, string);

            PlayerInfo[playerid][pExp] += quantia;
		}
        case ITEM_TYPE_MELHORIA: {

            format(string, sizeof string, "O item foi desativado e est· inv·lido!");
            SendClientMessage(playerid, -1, string);
		}
		case ITEM_TYPE_VEH_ACCESSORY: {
			
			format(string, sizeof string, "Os acessÛrios veiculares est„o temporariamente desativados.");
			SendClientMessage(playerid, -1, string);
		}
		case ITEM_TYPE_CAIXA_ITEM_VEICULAR: {

			format(string, sizeof string, "Esta caixa est· temporariamente desativada.");
			SendClientMessage(playerid, -1, string);
		}
		case ITEM_TYPE_REMEDIO:
		{
			PlayerInfo[playerid][pRestoreLife] += 60.0;

			format(string, sizeof string, "* VocÍ tomou um %s, curou as doenÁas e vai recuperar vida/colete !", itemname);
            SendClientMessage(playerid, 0x00CCCCFF, string);

		    format(string, sizeof(string), "* %s usou um %s.", PlayerName[playerid], itemname);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		    ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1,0,1,1,0,0);

            defer fadeOut_Timer(playerid);
			fadeIn(playerid, 2100, 0xFFFFFFFF);

			GameTextForPlayer(playerid,"~w~Voce esta~n~~p~Se curando...",4000,1);
		}
		case ITEM_TYPE_REMEDIOP:
		{
    		PlayerInfo[playerid][pRestoreLife] += 40.0;

			format(string, sizeof string, "* VocÍ tomou um %s, curou as doenÁas e vai recuperar a vida/colete !", itemname);
            SendClientMessage(playerid, 0x00CCCCFF, string);

		    format(string, sizeof(string), "* %s usou um %s.", PlayerName[playerid], itemname);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		    ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1,0,1,1,0,0);

            defer fadeOut_Timer(playerid);
			fadeIn(playerid, 2100, 0xFFFFFFFF);

			GameTextForPlayer(playerid,"~w~Voce esta~n~~p~Se curando...",4000,1);
		}
		case ITEM_TYPE_CELULAR:
		{
		    switch (modelid)
		    {
				case 18873:
				{
					new numerocel = random(98) + 1;
				    format(string, sizeof(string), "(( %s mudou seu n˙mero de celular para: %d ))", PlayerName[playerid], numerocel);
					SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
					server_log("numero_celular", string);

					PlayerInfo[playerid][numeroCelular] = numerocel;
				}
		        case 18874:
				{
					new numerocel = random(998) + 1;
				    format(string, sizeof(string), "(( %s mudou seu n˙mero de celular para: %d ))", PlayerName[playerid], numerocel);
					SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
					server_log("numero_celular", string);

					PlayerInfo[playerid][numeroCelular] = numerocel;
				}
			}
		}
		case ITEM_TYPE_GARRAFA:
		{
			switch (modelid)
			{
				case 1668:
				{
				    if (InvItens_GetFreeSlots(playerid) < 2) 
						return SendClientMessage(playerid, -1, "VocÍ deve ter pelo menos 2 slots em seu invent·rio para usar esse item."), false;

		   			PlayerInfo[playerid][pRestoreLife] += 5.0;
				    format(string, sizeof(string), "* %s bebeu ·gua.", PlayerName[playerid]);
					SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* VocÍ bebeu ·gua, e foi adicionado ‡ sua Sa˙de.");
		   			giveSede(playerid, 20.0);

					GameTextForPlayer(playerid,"~w~Voce esta~n~~p~bebendo agua...",4000,1);

				    givePlayerItem(playerid, ITEM_TYPE_LIXO, 1668, 1, "Garrafa Vazia");
				}
			}
		}
		case ITEM_TYPE_COMIDACRU:
		{
			// if (!Cooking_Start(playerid, modelid, itemname))
			// 	return false;			
			return false;
		}
		case ITEM_TYPE_ORGAO:
		{
		    if (IsPlayerInRangeOfPoint(playerid, 1.5, 939.4326, 2177.0520, 1011.0234))
			{
		    	switch (modelid)
				{
		    	    case ITEM_MODEL_CABECA:
					{
						Player_AddMoney(playerid, PRICE_ORGAO_CABECA);

                		format(string, sizeof(string), "Rodrigo Fusion(504) diz: Ol· %s, nÛs pagamos $%s pela cabeÁa humana que vocÍ vendeu.", PlayerName[playerid], getFormatText(PRICE_ORGAO_CABECA));
						SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
                	}
                	case ITEM_MODEL_TRONCO:
					{
						Player_AddMoney(playerid, PRICE_ORGAO_TRONCO);

                		format(string, sizeof(string), "Rodrigo Fusion(504) diz: Ol· %s, nÛs pagamos $%s pelo tronco humano que vocÍ vendeu.", PlayerName[playerid], getFormatText(PRICE_ORGAO_TRONCO));
						SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
                	}
                	case ITEM_MODEL_PERNA:
					{
						Player_AddMoney(playerid, PRICE_ORGAO_PERNA);

                		format(string, sizeof(string), "Rodrigo Fusion(504) diz: Ol· %s, nÛs pagamos $%s pela perna humana que vocÍ vendeu.", PlayerName[playerid], getFormatText(PRICE_ORGAO_PERNA));
						SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
                	}
                	case ITEM_MODEL_BRACO:
					{
						Player_AddMoney(playerid, PRICE_ORGAO_BRACO);

                		format(string, sizeof(string), "Rodrigo Fusion(504) diz: Ol· %s, nÛs pagamos $%s pelo braÁo humano que vocÍ vendeu.", PlayerName[playerid], getFormatText(PRICE_ORGAO_BRACO));
						SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
                	}
     			}
			} else {
			    return SendClientMessage(playerid, -1, "VocÍ precisa estar no Mercado Negro para vender Ûrg„os, use: /gps."), 0;
   			}
		}

		case ITEM_TYPE_CONSUMIVEL:
		{
   			switch (modelid)
  			{
		        case ITEM_MODEL_RESPAWNORG:
				{
					return SendClientMessage(playerid, -1, "Item desativado."), false;

		    		// RespawnCarrosOrg(GetPlayerOrg(playerid));
               	}
               	case ITEM_MODEL_PROCURADO:
				{
				    if (!Player_GetWanted(playerid)) 
						return SendClientMessage(playerid, -1, "VocÍ n„o est· com nÌvel de procurado."), false;

					if (IsPlayerInCombat(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode usar esse item em combate."), false;

            		Player_SetWanted(playerid, 0);
               	}
               	case ITEM_MODEL_BLINDAR_CARRO:
				{
					new vehicleid = GetPlayerVehicleID(playerid);
					new VIM:vim = Vehicle_GetVIM(vehicleid);

               		if (!VIM_IsCar(vim))
					   return SendClientMessage(playerid, -1, "VocÍ n„o est· em nenhum veÌculo."), false;

					RepairVehicle(vehicleid);
					SetVehicleHealth(vehicleid, 4000);
     			}
     			case ITEM_MODEL_IRPARAHQ:
				{
               		if (IsPlayerInCombat(playerid)) return SendClientMessage(playerid, -1, "VocÍ sÛ pode usar este Item 1 minuto apÛs tomar dano de alguÈm !"), false;

		    		SpawnPlayer(playerid);
     			}
     			case ITEM_MODEL_NAMEVEH:
				{
				    SetPVarInt(playerid, "mudarNickVeh", 1);
					SelectTextDraw(playerid, 0x00BFFF90);

					SendClientMessage(playerid, -1, "VocÍ est· usando o item, selecione o veÌculo que deseja adicionar um nick.");

				    return false;
				}
				case ITEM_MODEL_REFINADORA:
				{
					Refinator_Use(playerid);
					SelectTextDraw(playerid, 0xFC6A6A90);

					SendClientMessage(playerid, COLOR_GRAD, "Selecione o item com 4 unidades que deseja refinar.");

				    return false;
				}
				case ITEM_MODEL_PALETA:
				{
					SelectTextDraw(playerid, 0x8CC6EF90);
					Player_SetPaletteColor(playerid, itemid, cor1, cor2);

					format(string, sizeof(string), "VocÍ usou sua %s, selecione um veÌculo de invent·rio para pintar (cor1: '%d'  cor2: %d).", itemname, cor1, cor2);
					SendClientMessage(playerid, COLOR_LIGHTGREEN, string);

					format(string, sizeof(string), "[PALETA-DE-CORES]: %s usou a paleta (cor1: '%d', cor2: %d).", PlayerName[playerid], cor1, cor2);
					server_log("paletas", string);
					
				    return false;
				}
				case ITEM_MODEL_PONTOS_ADVOGADO:
				{
					PlayerInfo[playerid][pAdvogadoSkill] ++;

					format(string, sizeof(string), "VocÍ usou +1 Pontos de Advogado. (Pontos atuais: %d)", PlayerInfo[playerid][pAdvogadoSkill]);
					SendClientMessage(playerid, 0x4072F0FF, string);
				}
				case ITEM_MODEL_ORGVIP:
				{
					new orgid = GetPlayerOrg(playerid);
					if (orgid < 1 || orgid > 34) 
						return SendClientMessage(playerid, -1, "VocÍ n„o participa de uma organizaÁ„o."), false;
					if (OrgInfo_GetVIP(orgid)) 
						return SendClientMessage(playerid, -1, "A organizaÁ„o j· est· como VIP, aguarde vencer."), false;
					
					format(string, sizeof(string), "[Ativar ORG-VIP] %s ativou ORG-VIP na organizaÁ„o: %s", PlayerName[playerid], GetOrgName(orgid));
					server_log("orgvip", string);

					format(string, sizeof(string), "A organizaÁ„o: [%s] È a mais nova ORG VIP do servidor!", GetOrgName(orgid));
					SendClientMessageToAll(COLOR_LIGHTBLUE, string);

					OrgInfo_SetVIP(playerid, orgid, 1);
				}
				case ITEM_MODEL_RESETAR_KD:
				{
					PlayerInfo[playerid][pKills] = 0;
					PlayerInfo[playerid][pDeaths] = 0;
				}
				case ITEM_MODEL_SAIR_PRISAO:
				{
					if (Player_GetJailed(playerid) == 9) return SendClientMessage(playerid, -1, "VocÍ n„o pode sair da pris„o administrativa."), false;
					if (!Player_GetJailed(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o est· na pris„o."), false;
					//if (PlayerInfo[playerid][pJailTime] > (10*60)) return SendClientMessage(playerid, -1, "O item apenas pode ser utilizado caso vocù esteja 10 minutos ou menos na prisùo.");
					PlayerInfo[playerid][pJailTime] = 0;
				}
				case ITEM_MODEL_REPARAR_CARRO:
				{
					if (!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o est· em um veÌculo."), false;
					RepairVehicle(GetPlayerVehicleID(playerid));
				}
				case ITEM_MODEL_ENCHER_TANQUE:
				{
					if (!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o est· em um veÌculo."), false;
					VehicleInfo[GetPlayerVehicleID(playerid)][vehicleCombustivel] = 100;
				}
  			}
		}
		case ITEM_TYPE_LIXO:
		{
			new id = TrashCan_Get(playerid);

			if (id == -1)
			{
				SendClientMessage(playerid, -1, "VocÍ n„o est· prÛximo de uma lixeira.");

				return false;
			}
			new result = TrashCan_GiveItem(id, itemtype, modelid, cor1, cor2, quantia, itemname);
			if (!result) return SendClientMessage(playerid, -1, "A lixeira est· sem espaÁo, jogue fora em outra lixeira."), false;

			format(string, sizeof(string), "(( %s jogou fora %d unidade(s) de %s no lixo ))", PlayerName[playerid], quantia, itemname);
			SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

			format(string, sizeof(string), "[LIXEIRA %d]: %s jogou %d unidade(s) de %s.", id, PlayerName[playerid], quantia, itemname);
			server_log("lixeira", string);

			TrashCan_UpdateText(id);
		}
		case ITEM_TYPE_BEBIDA:
		{
            if (InvItens_GetFreeSlots(playerid) < 2) 
				return SendClientMessage(playerid, -1, "VocÍ deve ter pelo menos 2 slots em seu invent·rio para usar esse item."), false;

   			PlayerInfo[playerid][pRestoreLife] += 10.0;
		    format(string, sizeof(string), "* %s bebeu uma %s.", PlayerName[playerid], itemname);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			format(string, sizeof(string), "* VocÍ bebeu uma %s e foi adicionado ‡ sua Sa˙de.", itemname);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
   			giveSede(playerid, 5.0);

			GameTextForPlayer(playerid,"~w~Voce esta~n~~p~bebendo...",4000,1);

			givePlayerItem(playerid, ITEM_TYPE_LIXO, 1551, 1, "Garrafa Vazia");
		}
		case ITEM_TYPE_COMIDA, ITEM_TYPE_HAMBURGER, ITEM_TYPE_FATIAPIZZA:
		{
            if (InvItens_GetFreeSlots(playerid) < 2) 
				return SendClientMessage(playerid, -1, "VocÍ deve ter pelo menos 2 slots em seu invent·rio para usar esse item."), 0;

			if (PlayerInfo[playerid][pRestoreFome] > 0.0)
				return SendClientMessage(playerid, -1, "VocÍ est· com uma comida em m„os, drope apertando F ou consuma apertando ALT."), 0;

			if (PlayerInfo[playerid][pRestoreSede] > 0.0)
				return SendClientMessage(playerid, -1, "VocÍ est· com uma bebida em m„os, drope apertando F ou consuma apertando ALT."), 0;

			// Fechar o invent·rio
			Inventory_HideForPlayer(playerid);
   		
		   	// Salvando modelid e nome da comida
			SetPVarString(playerid, "right_hand_object_name", itemname);
			SetPVarInt(playerid, "right_hand_object", modelid);

			// Removendo objetos que estiver na m„o
			RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);

			// Definindo quantidade de fome e sede que recupera
			switch (modelid)
			{
				case ITEM_MODEL_CARNE:
				{
					SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, modelid, 6, 0.060000, 0.056000, -0.000999, 96.800109, -52.900028, 4.300016, 0.656000, 0.781000, 0.802000);
					PlayerInfo[playerid][pRestoreFome] = 60.0;
				}
				case ITEM_MODEL_PAO:
				{
					SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, modelid, 6, 0.049999, 0.063999, 0.004000, -91.499969, -103.999870, -89.400016, 1.000000, 1.000000, 1.000000);
					PlayerInfo[playerid][pRestoreFome] = 40.0;
				}
				case ITEM_MODEL_PIZZA:
				{   
					SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, modelid, 6, 0.019999, 0.057999, 0.144999, -81.000045, -15.400002, 51.800010, 1.000000, 0.892000, 0.856000);
					PlayerInfo[playerid][pRestoreFome] = 40.0;
				}
				case ITEM_MODEL_FRANGO:
				{
					SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, modelid, 6, 0.059000, 0.009000, 0.019000, -79.100036, -10.200007, -3.899999, 0.299000, 0.388000, 0.350000);
					PlayerInfo[playerid][pRestoreFome] = 50.0;
				}
				case ITEM_MODEL_BURGUER:
				{
					SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, modelid, 6, 0.026999, -0.037999, 0.009000, 0.000000, 29.300008, 23.000005, 0.788000, 0.920000, 0.926000);
					PlayerInfo[playerid][pRestoreFome] = 20.0;
				}
				case ITEM_MODEL_HOTDOG:
				{
					SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, modelid, 6, 0.026999, -0.037999, 0.009000, 0.000000, 29.300008, 23.000005, 0.788000, 0.920000, 0.926000);
					PlayerInfo[playerid][pRestoreFome] = 25.0;
				}
				default: 
				{
					SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, 19630, 6, 0.083999, 0.058999, 0.000000, -96.899971, 20.199991, 109.499946, 1.000000, 1.000000, 1.000000);
					PlayerInfo[playerid][pRestoreFome] = 50.0;
				}
			}

			// NULL
			ApplyAnimation(playerid,"FOOD","null",0.0,0,0,0,0,0);

			// Mensagem
			format(string, sizeof(string), "~w~Voce esta segurando uma ~p~%s ~w~aperte ~b~ALT ~w~para comer", itemname);
            ShowPlayerBaloonInfo(playerid, string, 7000);

			// Vari·vel
			SetPVarInt(playerid, "busyhands", 0);

			// Informando os jogadores ao redor
		    format(string, sizeof(string), "(( %s est· comendo um(a) %s ))", PlayerName[playerid], itemname);
			SendClientMessageInRange(20.0, playerid, string, COR_ACAOCHAT,COR_ACAOCHAT,COR_ACAOCHAT,COR_ACAOCHAT,COR_ACAOCHAT);
		}
		case ITEM_TYPE_SKATE:
		{
			return BuyPlayerSkate(playerid);
		}
		case ITEM_TYPE_GASOLINA:
		{
	     	if (!IsPlayerInAnyVehicle(playerid)) 
				return SendClientMessage(playerid, -1, "VocÍ n„o est· em um veÌculo."), 0;

	     	new vid = GetPlayerVehicleID(playerid);

			VehicleInfo[vid][vehicleCombustivel] += quantia;

			if (VehicleInfo[vid][vehicleCombustivel] > 100)
				VehicleInfo[vid][vehicleCombustivel] = 100;

			format(string, sizeof string, "* VocÍ abasteceu este veÌculo com %d litros de gasolina.", quantia);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
		}
		case ITEM_TYPE_MINA:
		{
			if (IsPlayerCuffed(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode usar agora !"), false;

			if (PlayerInfo[playerid][pLevel] < 2) return SendClientMessage(playerid,-1, "VocÍ poder· plantar mina terrestre apÛs o nÌvel 2."), false;

			if (GetPlayerInterior(playerid) != 0) return SendClientMessage(playerid, -1, "VocÍ n„o pode plantar mina em interiores !"), false;

			if (GetPlayerVirtualWorld(playerid) != 0) return SendClientMessage(playerid, -1, "VocÍ n„o pode usar agora !"), false;

			if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode usar agora !"), false;

			if (IsPlayerInSafeZone(playerid)) 
				return SendClientMessage(playerid, -1, "VocÍ n„o pode fazer isso em uma ¡rea Segura."), false;

			if (isMinaFull()) return SendClientMessage(playerid, -1, "Muitas minas j· foram plantadas, tente outra hora !"), false;

			format(string, sizeof string, "* VocÍ plantou uma %s aqui !", itemname);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			SendClientMessage(playerid, COLOR_LIGHTRED, "        !ATEN«√O! VocÍ deve se afastar dela em 10 segundos, ou ela ir· explodir !");

		    GameTextForPlayer(playerid, "~r~~h~Afaste-se do local", 5000, 1);

			plantMina(playerid);
		}

		case ITEM_TYPE_SEMIPRONTA:
		{
			if(!IsPlayerInRangeOfPoint(playerid, 2.0, 944.5869,2176.7280,1011.0234)) {
				SendClientMessage(playerid, -1, "Essa maconha ainda n„o est· pronta para consumo.");
				SendClientMessage(playerid, -1, "… preciso ir atÈ o mercado negro e usar o item perto do Ìcone de processar maconha.");
				return 0;
			}

			new quant = quantia - 3;

			if (quant < 1) 
				quant = 1;

			format(string, sizeof string, "Processamento: VocÍ conseguiu %d gramas de maconha processando %d grama de maconha semi-pronta.", quant, quantia);
			SendClientMessage(playerid, -1, string);
			SendClientMessage(playerid, -1, "Processamento: A quantidade que foi para seu invent·rio agora est· pronta para consumo.");

			givePlayerItem(playerid, ITEM_TYPE_MACONHA, 2891, quant, "Maconha");
		}

		case ITEM_TYPE_SEMENTE:
		{
			if (IsPlayerCuffed(playerid)) {
				SendClientMessage(playerid, -1, "VocÍ n„o pode usar agora !");
				return 0;
			}
			if (GetPlayerInterior(playerid) != 0) {
				SendClientMessage(playerid, -1, "VocÍ n„o pode usar agora !");
				return 0;
			}

			if(GetPlayerVirtualWorld(playerid) != 0) {
				SendClientMessage(playerid, -1, "VocÍ n„o pode usar agora !");
				return 0;
			}

			if(IsPlayerInAnyVehicle(playerid)) {
				SendClientMessage(playerid, -1, "VocÍ n„o pode usar agora !");
				return 0;
			}

			if (PlayerMaxCannabis(playerid)) {
				SendClientMessage(playerid, -1, "VocÍ j· excedeu o limite de plantaÁıes por player !");
				return 0;
			}

			if (GetPlayerCannabisId(playerid) != -1)
			{
			    SendClientMessage(playerid, -1, "VocÍ est· muito perto de outra plantaÁ„o !");
			    return 0;
			}

			format(string, sizeof string, "* VocÍ plantou uma %s aqui !", itemname);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

			new
			    Float:x_cnbs, Float:y_cnbs, Float:z_cnbs, Float:a_cnbs;

			GetPlayerPos(playerid, x_cnbs, y_cnbs, z_cnbs);
			GetPlayerFacingAngle(playerid, a_cnbs);

			CreateCannabis(x_cnbs, y_cnbs, z_cnbs, a_cnbs, PlayerName[playerid]);
		}
		case ITEM_TYPE_REGADOR:
		{
		    new idx = GetPlayerCannabisId(playerid);

			if (idx == -1) return SendClientMessage(playerid, -1, "VocÍ n„o est· perto de nenhuma plantaÁ„o !"), false;

		 	Inventory_HideForPlayer(playerid, .cancelanim = 0);

			ApplyAnimation(playerid, "WEAPONS", "SHP_Tray_Pose", 4.1, true, false, false, false, 0, SYNC_ALL);

			SetPlayerFaceToPoint(playerid, CannabisInfo[idx][erva_x], CannabisInfo[idx][erva_y]);

			SetPlayerAttachedObject(playerid, 1, 19621,6,0.112000,0.068999,0.049999,31.299999,39.299999,106.000000,1.128999,1.180999,1.538000);
			SetPlayerAttachedObject(playerid, 3, 18705,6,0.882000,-0.209999,1.621001,-167.799972,-13.000032,-111.199996,1.000000,1.000000,1.000000);

			SetTimerEx("RegarCannabis", 5000, false, "ii", playerid, idx);

			SendClientMessage(playerid, COLOR_GREY, "VocÍ est· regando esta plantaÁ„o, aguarde...");
		}

		case ITEM_TYPE_NICK:
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* VocÍ adquiriu +1 direito de trocar de nick, use /trocarnick caso queira trocar.");

			PlayerInfo[playerid][pTrocaNick] ++;
		}

		// AcessÛrio veicular
		/*case ITEM_TYPE_VEH_ACCESSORY:
		{
            Player_ShowNearbyVehicles(playerid);
            SetPVarInt(playerid, "vehicleItem", itemid);

            return false;
		}*/

		// AcessÛrios no corpo
		case ITEM_TYPE_ACCESSORY:
		{
			switch (Accessories_Count(playerid)) {
				case 2: {
					if (Player_GetVIP(playerid) < SOCIO_PREMIUM)
						return SendClientMessage(playerid, -1, "VocÍ precisa ser SOCIO-PREMIUM+ para usar 3 acessÛrios."), 0;
				}
				case 3: {
					if (Player_GetVIP(playerid) < SOCIO_SUPREME)
						return SendClientMessage(playerid, -1, "VocÍ precisa ser SOCIO-SUPREME+ para usar 4 acessÛrios."), 0;
				}
				case 4: {
					if (Player_GetVIP(playerid) < SOCIO_EXTREME)
						return SendClientMessage(playerid, -1, "VocÍ precisa ser SOCIO-EXTREME+ para usar 5 acessÛrios."), 0;
				}
				case 5: {
					return SendClientMessage(playerid, -1, "VocÍ est· no limite de acessÛrios."), 0;
				}
			}

			if (!IsPlayerAttachedObjectSlotUsed(playerid, Slot_Bone)) {
				SetPVarInt(playerid, "accessorySlot", Slot_Bone);
			} else if (!IsPlayerAttachedObjectSlotUsed(playerid, Slot_Oculos)) {
				SetPVarInt(playerid, "accessorySlot", Slot_Oculos);
			} else if (!IsPlayerAttachedObjectSlotUsed(playerid, Slot_Relogio)) {
				SetPVarInt(playerid, "accessorySlot", Slot_Relogio);
			} else if (!IsPlayerAttachedObjectSlotUsed(playerid, Slot_Bandana)) {
				SetPVarInt(playerid, "accessorySlot", Slot_Bandana);
			} else if (!IsPlayerAttachedObjectSlotUsed(playerid, Slot_Guitarra)) {
				SetPVarInt(playerid, "accessorySlot", Slot_Guitarra);
			} else {
				return SendClientMessage(playerid, -1, "VocÍ est· no limite de acessÛrios."), 0;
			}
			SetPVarInt(playerid, "accessoryItem", itemid);
			SetPVarString(playerid, "accessoryName", itemname);
			SetPVarInt(playerid, "accessoryModel", modelid);
			SetPVarInt(playerid, "accessoryCor1", cor1);
			SetPVarInt(playerid, "accessoryCor2", cor2);

			Accessorie_BodyParts(playerid);
            return 0;
		}
		case ITEM_TYPE_OCULOS, ITEM_TYPE_RELOGIO, ITEM_TYPE_TRONCO:
		{
            return SendClientMessage(playerid, -1, "O acessÛrio est· bugado, solicite ajuda da administraÁ„o."), 0;
		}

		// MedKit de ch„o
		case ITEM_TYPE_MEDKIT:
		{
			if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode usar agora."), false;

			if (createMedKit(playerid) == -1) 
				return SendClientMessage(playerid, -1, "H· muitos medkit em uso no momento."), false;

			format(string, sizeof string, "* VocÍ usou um %s, fique em cima dele para ganhar vida/colete.", itemname);
            SendClientMessage(playerid, 0x00CCCCFF, string);
		}

		#if _LOOT_SYSTEM_ON
			case ITEM_TYPE_DEPOSITORY: {

				// return SendClientMessage(playerid, -1, "Sistema em manutenÁ„o."), false;

				if (IsPlayerInAnyVehicle(playerid)) 
					return SendClientMessage(playerid, -1, "VocÍ n„o pode usar este item em um veÌculo."), false;

				if (!OnPlayerUseDepository(playerid, itemname, modelid)) {
					return false;
				}
				SendClientMessage(playerid, COLOR_LIGHTGREEN, "Lembre-se: Coloque o item apenas em HQs que vocÍ faÁa parte, ou em suas propriedades.");
				SendClientMessage(playerid, COLOR_ALERT, "Alerta: Caso vocÍ n„o respeite o lembrete, iremos lhe punir removendo seu item.");
			}
		#endif
		
		case ITEM_TYPE_GUNBOXP:
		{
			if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode fazer isso no momento."), false;
			if (countPlayerGunBox(playerid) > 1 && PlayerInfo[playerid][pVIP] < 1) return SendClientMessage(playerid, -1, "VocÍ n„o pode colocar mais de uma caixa de equipamentos."), false;
			if (countPlayerGunBox(playerid) > 2 && PlayerInfo[playerid][pVIP] > 7) return SendClientMessage(playerid, -1, "VocÍ n„o pode colocar mais de duas caixa de equipamentos."), false;

			new id = createPlayerGunBox(playerid, GUNBOX_SMALL);

			if (id == -1) return SendClientMessage(playerid, -1, "Muitas caixas de equipamentos est„o sendo usadas no servidor."), false;

            format(string, sizeof(string), "(( %s montou uma %s ))", PlayerName[playerid], itemname);
			SendClientMessageInRange(45.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
		}
		case ITEM_TYPE_GUNBOXM: {

			if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode fazer isso no momento."), false;
			if (countPlayerGunBox(playerid) > 1 && PlayerInfo[playerid][pVIP] < 1) return SendClientMessage(playerid, -1, "VocÍ n„o pode colocar mais de uma caixa de equipamentos."), false;
			if (countPlayerGunBox(playerid) > 2 && PlayerInfo[playerid][pVIP] > 7) return SendClientMessage(playerid, -1, "VocÍ n„o pode colocar mais de duas caixa de equipamentos."), false;

			new id = createPlayerGunBox(playerid, GUNBOX_NORMAL);

			if (id == -1) return SendClientMessage(playerid, -1, "Muitas caixas de equipamentos est„o sendo usadas no servidor."), false;

            format(string, sizeof(string), "(( %s montou uma %s ))", PlayerName[playerid], itemname);
			SendClientMessageInRange(45.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
		}
		case ITEM_TYPE_GUNBOXG:
		{
			if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode fazer isso no momento."), false;
			if (countPlayerGunBox(playerid) > 1 && PlayerInfo[playerid][pVIP] < 1) return SendClientMessage(playerid, -1, "VocÍ n„o pode colocar mais de uma caixa de equipamentos."), false;
			if (countPlayerGunBox(playerid) > 2 && PlayerInfo[playerid][pVIP] > 7) return SendClientMessage(playerid, -1, "VocÍ n„o pode colocar mais de duas caixa de equipamentos."), false;

			new id = createPlayerGunBox(playerid, GUNBOX_BIG);

			if (id == -1) return SendClientMessage(playerid, -1, "Muitas caixas de equipamentos est„o sendo usadas no servidor."), false;

            format(string, sizeof(string), "(( %s montou uma %s ))", PlayerName[playerid], itemname);
			SendClientMessageInRange(45.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
		}
		case ITEM_TYPE_DECORACAO:
		{
			if (IsPlayerInAnyVehicle(playerid) || GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0) return SendClientMessage(playerid, -1, "VocÍ n„o pode usar agora."), false;
			
			if (IsPlayerInSafeZone(playerid)) 
				return SendClientMessage(playerid, -1, "VocÍ n„o pode fazer isso em uma ¡rea Segura."), false;

			new id = CreatePlayerPortao(playerid, modelid, itemname);

			if (!id) return SendClientMessage(playerid, -1, "O limite de portıes no servidor foi esgotado."), 0;
		}

		case ITEM_TYPE_DRONE:
		{
			if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode usar dentro de um veÌculo."), false;
			if (GetPlayerSpeedEx(playerid) > 1) return SendClientMessage(playerid, -1, "VocÍ precisa estar parado para usar seu veÌculo."), false;

			if (strfind(itemname, "PROD", true) != -1) 
				SetPVarInt(playerid, "VeiculoProdutos", 1);
			else 
				SetPVarInt(playerid, "VeiculoProdutos", 0);
				
			SetPlayerDrone(playerid, modelid, cor1, cor2);
			return 0;
		}

		case ITEM_TYPE_SKIN:
		{
			if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode trocar de roupa dentro de um carro."), false;
			if (Player_GetJailed(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode trocar de roupa preso."), false;
			if (Staff_GetWorking(playerid)) return SendClientMessage(playerid, -1, "VocÍ n„o pode trocar de roupa em modo trabalho."), false;
			if (OnDuty[playerid] == 1) return SendClientMessage(playerid, -1, "VocÍ n„o pode trocar skin com o cart„o batido."), false;

			if (isInventoryFull(playerid))
	    		return SendClientMessage(playerid, -1, "VocÍ n„o tem espaÁo no invent·rio."), false;

			new skinid = PlayerInfo[playerid][pSkin];

			format(string, sizeof string, "* VocÍ colocou a %s.", itemname);
			SendClientMessage(playerid, 0x00CCCCFF, string);

			SetPlayerSkin(playerid, modelid);
			PlayerInfo[playerid][pSkin] = modelid;

			format(string, sizeof(string), "* %s trocou de roupa", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

			format(string, sizeof string, "Skin %d", skinid);

			givePlayerItem(playerid, ITEM_TYPE_SKIN, skinid, 1, string);
			//dropItem(playerid, ITEM_TYPE_SKIN, modelid, 1, string, false);
		}
		case ITEM_TYPE_NOTEBOOK:
		{
			#if defined _INC_email
				Inventory_HideForPlayer(playerid);
				cmd_email(playerid);
			#else
				MESSAGE_WARNING_INACTIVE_SYSTEM;
			#endif

			return 0;
		}
		case ITEM_TYPE_MATERIAL:
		{
			SendClientMessage(playerid, COLOR_LIGHTRED, "O material n„o pode ser utilizado dessa forma. Venda-os!");
			return 0;
		}
		case ITEM_TYPE_PANEL:
		{
            if (IsPlayerInAnyVehicle(playerid)) 
				return SendClientMessage(playerid, -1, "VocÍ n„o pode usar este item em um veÌculo."), false;

			else if(GetPlayerInterior(playerid))
				return SendClientMessage(playerid, -1, "N„o È permitido colocar placas em interiores."), false;

			else if (Player_CountPanel(playerid) >= Player_MaxPanel(playerid))
				return SendMsgF(playerid, COLOR_LIGHTRED, "VocÍ pode apenas ter %d placas de acordo com seu VIP. Use: /placa localizar", Player_MaxPanel(playerid)), false;

			new Float:pos[3];
			GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
			if (!Panel_Create(playerid, modelid, itemname, pos[0], pos[1], pos[2], 0.0, 0.0, 0.0)) {
				SendClientMessage(playerid, COLOR_ALERT, "Ops, o limite de placas do servidor foi excedido.");
				return false;
			}

			SendClientMessage(playerid, COLOR_LIGHTGREEN, "Lembre-se: Coloque o item apenas em HQs que vocÍ faÁa parte, ou em suas propriedades.");
			SendClientMessage(playerid, COLOR_ALERT, "Alerta: Caso vocÍ n„o respeite o lembrete, iremos lhe punir removendo seu item.");
		}
		default:
		{
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, "O item est· desativado.");
			return 0;
		}
	}

	return 1;
}

stock Inventory_HideForPlayer(playerid, cancelselect = 1, cancelanim = 1)
{
	if (!Inventory_IsOpen(playerid)) 
		return false;

	InvItem_SetSelected(playerid, -1);
	RemovePlayerAttachedObject(playerid, Slot_Mochila);

	if (!IsPlayerInAnyVehicle(playerid) && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_USEJETPACK && cancelanim) {
	    ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 0, 1, 1, 0, 0);
		ClearAnimations(playerid);
	}

	Inventory_SetOpen(playerid, false);

	Inventory_Hide(playerid);

	if (cancelselect) CancelSelectTextDraw(playerid);

	SetPVarInt(playerid, "mudarNickVeh", 0);
	Refinator_Cancel(playerid);

	return 1;
}

hook OnPlayerLogin(playerid) {
	loadInventory(playerid);
	return 1;
}

CMD:verinventario(playerid, params[])
{
    if (Dev_GetNivel(playerid) < DEV_ALPHA)
        return SendClientMessage(playerid, -1, "VocÍ n„o tem autorizaÁ„o para usar esse comando.");

    new nameplayer[MAX_PLAYER_NAME];
    if (sscanf(params, "s[24]", nameplayer)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /verinventario (nick do jogador)");

    MEGAString[0] = EOS;
	strcat(MEGAString, "slot	nome\ttipo/modelo\tqntd.\tcores\n");

    new idplayer = GetPlayerID(nameplayer),
        item_edit[MAX_ITENS_INVENTARIO + 1],
        count;
        
    if (Player_Logado(idplayer)) {
        for (new slot; slot < MAX_ITENS_INVENTARIO; slot++) 
        {
            if (InvItem_IsValid(idplayer, slot)) {
                FormatCat(MEGAString, ""C_WHITE"%02d     %s\t"C_GRAY"%d | %d\t%d\t"C_WHITE"(%d %d)\n", slot, InvItem_GetName(idplayer, slot), InvItem_GetType(idplayer, slot), InvItem_GetModel(idplayer, slot), InvItem_GetQuantity(idplayer, slot), InvItem_GetColor1(idplayer, slot), InvItem_GetColor2(idplayer, slot));
            }
			item_edit[count] = slot;
            count++;
        }
    } else {
		new idgplayer = Player_GetAccountIDByNick(nameplayer);
		if (!idgplayer)
			return SendClientMessage(playerid, -1, "Esse jogador n„o existe.");

        inline OnInventoryLoad() {
            new slot,
                item_name[45],
                item_tipo,
                item_modelo,
                item_quantity,
                item_color1,
                item_color2;

            MySQL_BindResultInt(stmt_loadInventory, 0, slot);
            MySQL_BindResult(stmt_loadInventory, 1, item_name);
            MySQL_BindResultInt(stmt_loadInventory, 2, item_tipo);
            MySQL_BindResultInt(stmt_loadInventory, 3, item_modelo);
            MySQL_BindResultInt(stmt_loadInventory, 4, item_quantity);
            MySQL_BindResultInt(stmt_loadInventory, 5, item_color1);
            MySQL_BindResultInt(stmt_loadInventory, 6, item_color2);

            while(MySQL_Statement_FetchRow(stmt_loadInventory)) 
            {
                FormatCat(MEGAString, ""C_WHITE"%02d     %s\t"C_GRAY"%d\t%d\t%d\t"C_GRAY"(%d %d)\n", slot, item_name, item_tipo, item_modelo, item_quantity, item_color1, item_color2);
                
                item_edit[count] = slot;
                count++;
            }
        }
		MySQL_BindInt(stmt_loadInventory, 0, idgplayer);
        MySQL_ExecuteThreaded_Inline(stmt_loadInventory, using inline OnInventoryLoad);
    }
    item_edit[count] = -1;
    strcat(MEGAString, ""C_GRAY"->\t"C_GREEN"ADICIONAR NOVO ITEM\n");
	new string[128];
    format(string, sizeof(string), ""C_RED"[ EDITAR INVENTARIO ] "C_GRAY"%s", nameplayer);

    if (Dev_GetNivel(playerid) > DEV_ALPHA) {
        inline D_InvEdit(dinvid, dinvdialogid, dinvresponse, dinvlistitem, string:dinvtext[])
        {
            #pragma unused dinvid, dinvdialogid, dinvtext, dinvlistitem
            if (!dinvresponse) 
                return 1;

            inline D_InvEdit2(did, ddialogid, dresponse, dlistitem, string:dtext[])
            {
                #pragma unused did, ddialogid, dtext, dlistitem
                if (!dresponse) return 1;

                new slot = item_edit[dinvlistitem];
                if (slot == -1) {
                    SendClientMessage(playerid, COLOR_ERROR, "! "C_WHITE"Em construÁ„o.");
                    return 1;
                } else {
					switch (dlistitem) {
						case 0: {
							inline D_InvEditItem(ditemid, ditemdialogid, ditemresponse, ditemlistitem, string:ditemtext[])
							{
								#pragma unused ditemid, ditemdialogid, ditemlistitem, ditemresponse
								if (!dresponse) return 1;

								new type_item, model_item, quantia_item, name_item[45], cor1, cor2;
								if (sscanf(ditemtext, "ddddds[45]", type_item, model_item, quantia_item, cor1, cor2, name_item)) {
									SendClientMessage(playerid, COLOR_ERROR, "! "C_WHITE"VocÍ digitou algo errado.");
									callcmd::verinventario(playerid, nameplayer);
									return 1;
								}
								Inventory_AlterSlot(nameplayer, slot, type_item, model_item, quantia_item, name_item, cor1, cor2);
								SendMsgF(playerid, COLOR_DEV, "VocÍ editou o slot "C_WHITE"%d "C_DEV"do inventario de "C_WHITE"%s", slot, nameplayer);
								ServerLog::("edit_inventory", "[INVENTORY %s]: slot %d - item editado -> (%d %d %d %d %d %s)", nameplayer, slot, nameplayer, type_item, model_item, quantia_item, cor1, cor2, name_item);
								callcmd::verinventario(playerid, nameplayer);
							}
							Dialog_ShowCallback(playerid, using inline D_InvEditItem, DIALOG_STYLE_INPUT, "Editando o item", ""C_GREEN"Digite abaixo como o item deve ser editado\n(type) (model) (quantidade) (cor1) (cor2) (nome)", "Confirmar", "Fechar");
						}
						case 1: {
							Inventory_AlterSlot(nameplayer, slot, ITEM_TYPE_NONE, 0, 0, "", 0, 0);
							ServerLog::("edit_inventory", "[INVENTORY %s]: slot %d - item editado -> (%d %d %d %d %d %s)", nameplayer, slot, ITEM_TYPE_NONE, 0, 0, 0, 0, 0, "Nenhum item");
							callcmd::verinventario(playerid, nameplayer);
						}
						default: return 1;
					}
                }
            }
            Dialog_ShowCallback(playerid, using inline D_InvEdit2, DIALOG_STYLE_TABLIST, "selecione uma opcao", ""C_GREEN"Editar item\n"C_RED"Apagar item", "Selecionar", "Fechar");
            return 1;
        }
        Dialog_ShowCallback(playerid, using inline D_InvEdit, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Editar", "Fechar");
    } 
    else ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Fechar", #);

    return 1;
}