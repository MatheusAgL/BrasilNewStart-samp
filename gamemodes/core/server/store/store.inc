#if defined _inc_store_system
	#endinput
#endif
#define _inc_store_system true

#include <YSI_Coding\y_hooks>

#include <store_entry>
#include <store_textdraws>

static Iterator:StoreItems<MAX_STORE_ITENS>;

static 
		Statement: stmt_insertSlotStore,
		Statement: stmt_selectSlotStore,
		Statement: stmt_updateSlotStore,
		Statement: stmt_deleteSlotStore;

hook OnMySQLConnected() {
	// --------------------------------------------------------------------------------------------------------
	// Sistema de Storeentário - MySQL
	// --------------------------------------------------------------------------------------------------------

	static const query_insertSlotStore[] = 
		"INSERT INTO `store` (id, seller, type_price, price, item_name, item_type, item_model, item_quantity, item_color1, item_color2, item_maturity) \
					VALUES (DEFAULT, '?', '?', '?', ?, '?', '?', '?', '?', '?', '?')";
	stmt_insertSlotStore = MySQL_PrepareStatement(MySQL_Handle, query_insertSlotStore);

    static const query_selectSlotStore[] = 
		"SELECT * FROM `store` LIMIT ?"
	;
	stmt_selectSlotStore = MySQL_PrepareStatement(MySQL_Handle, query_selectSlotStore);

	static const query_deleteSlotStore[] = 
		"DELETE FROM `store` WHERE `id` = ?";
	stmt_deleteSlotStore = MySQL_PrepareStatement(MySQL_Handle, query_deleteSlotStore);

	return 1;
}

hook OnGameModeInit()
{
    Textdraws_CreateStore();

	inline const OnLoadStore() 
	{
		new id,
			seller,
            type_price,
            price,
            item_name[40],
            item_tipo,
            item_modelo,
            item_quantity,
            item_color1,
            item_color2,
			item_maturity[30];

		MySQL_BindResultInt(stmt_selectSlotStore, 0, id);
		MySQL_BindResultInt(stmt_selectSlotStore, 1, seller);
		MySQL_BindResultInt(stmt_selectSlotStore, 2, type_price);
		MySQL_BindResultInt(stmt_selectSlotStore, 3, price);
		MySQL_BindResult(stmt_selectSlotStore, 4, item_name);
		MySQL_BindResultInt(stmt_selectSlotStore, 5, item_tipo);
		MySQL_BindResultInt(stmt_selectSlotStore, 6, item_modelo);
		MySQL_BindResultInt(stmt_selectSlotStore, 7, item_quantity);
		MySQL_BindResultInt(stmt_selectSlotStore, 8, item_color1);
		MySQL_BindResultInt(stmt_selectSlotStore, 9, item_color2);
		MySQL_BindResult(stmt_selectSlotStore, 10, item_maturity);

		while (MySQL_Statement_FetchRow(stmt_selectSlotStore)) {
			StoreItem_Create(id, seller, type_price, price, item_name, item_tipo, item_modelo, item_quantity, item_color1, item_color2, item_maturity);
        }

		new count = Iter_Count(StoreItems);
		printf("[Store]: %d items loaded...", count);
	}
	MySQL_BindInt(stmt_selectSlotStore, 0, MAX_STORE_ITENS);
	MySQL_ExecuteThreaded_Inline(stmt_selectSlotStore, using inline OnLoadStore);

	return 1;
}

hook OnPlayerLogin(playerid)
{
    Textdraws_CreatePlayerStore(playerid);
    return 1;
}

hook OnClickDynamicTextDraw(playerid, Text:textid)
{
	if (textid == Text:INVALID_TEXT_DRAW)
        Inventory_HideForPlayer(playerid);

	if (PlayerInStore(playerid)) {
		new currentPage = Store_GetPage(playerid);

		// Página anterior
		if (textid == store_td_prevpage) 
		{
			if (currentPage > 0) {
                currentPage--;
                Store_SetPage(playerid, currentPage);
                Store_UpdatePage(playerid);
            }
			return 1;
		}
		// Próxima página
		else if (textid == store_td_nextpage) 
		{
			if (currentPage < MAX_PAGES_STORE) {
                currentPage++;
                Store_SetPage(playerid, currentPage);
                Store_UpdatePage(playerid);
            }
			return 1;
		}
	}
	return 1;
}

hook OnClickDynPlayerTextDraw(playerid, PlayerText:textid)
{
	if (PlayerInStore(playerid)) {
	    for(new text; text != MAX_STORE_SLOT_PERPAGE; text++) 
        {
	        if (textid == store_ptd_preview[text][playerid]) {
				new slot = text + (Store_GetPage(playerid) * MAX_STORE_SLOT_PERPAGE);
				CallLocalFunction("OnStoreSelectedItem", "dd", playerid, slot);
			}
	    }
	}
	return 1;
}

CALLBACK: OnStoreSelectedItem(playerid, slot)
{
	new last_selected = Store_GetSelected(playerid);
	Store_SetSelected(playerid, slot);
	Store_UpdateSelected(playerid, slot);

	if (last_selected != -1) {
		Store_UpdateSelected(playerid, last_selected);
        Store_UpdatePage(playerid);
	}

	// if (PlayerInStore(playerid)) {
	// 	CallLocalFunction("OnPlayerStoreSell", "dd", playerid, slot);
	// 	return 1;
	// }

	if (StoreItem_GetID(slot) != -1) {
		SendClientMessage(playerid, -1, "Selecionado item");
    }
	return 1;
}

CALLBACK: OnPlayerStoreSell(playerid, slot)
{
    inline D_StoreSellItem(did, ddialogid, dresponse, dlistitem, string:dtext[])
    {
        #pragma unused did, ddialogid, dtext

        if (!dresponse)
            return 1;

        new type_price;

        switch (dlistitem)
        {
            case 0: {
                type_price = VALUE_TYPE_CASH;
            }
            default: {
                type_price = VALUE_TYPE_MONEY;
            }
        }
        Store_Sell(playerid, slot, type_price);
    }
    Dialog_ShowCallback(playerid, using inline D_StoreSellItem, DIALOG_STYLE_LIST, "Selecione a moeda de venda", 
    ""C_CYAN"CASH\n"C_WHITE""C_MONEY"DINHEIRO", "Selecionar", "Cancelar");

    return 1;
}

stock StoreSlot_GetPage(slot)
{
	switch (slot)
	{
		case 0..7: return 0;
		case 8..15: return 1;
		case 16..23: return 2;
		case 24..31: return 3;
		case 32..39: return 4;
		case 40..47: return 5;
		case 48..55: return 6;
	}
	return -1;
}

stock Store_UpdateSelected(playerid, slot)
{
	if (StoreSlot_GetPage(slot) != Store_GetPage(playerid))
		return 1;

	new textid = slot - (Inventory_GetPage(playerid) * MAX_INV_SLOT_PERPAGE);

	if (PlayerInStore(playerid)) {
		if (Store_GetSelected(playerid) == slot)
			PlayerTextDrawBackgroundColor(playerid, store_ptd_preview[textid][playerid], 60);
		else
			PlayerTextDrawBackgroundColor(playerid, store_ptd_preview[textid][playerid], 250);

		PlayerTextDrawShow(playerid, store_ptd_preview[textid][playerid]);
	}
	return 1;
}

stock StoreItem_Insert(playerid, slot, type_price, price)
{
    new seller = Player_GetAccountID(playerid),
        item_maturity[30];

    TimeFormat((Now() + Days:3), MYSQL_TIMESTAMP, item_maturity);

    inline const OnInsertStoreItem()
    {
        new id = cache_insert_id();
        TimeFormat((Now() + Days:3), MYSQL_TIMESTAMP, item_maturity);

        new item = StoreItem_Create(id, seller, type_price, price, 
                                    InvItem_GetName(playerid, slot), 
                                    InvItem_GetType(playerid, slot), 
                                    InvItem_GetModel(playerid, slot), 
                                    InvItem_GetQuantity(playerid, slot), 
                                    InvItem_GetColor1(playerid, slot), 
                                    InvItem_GetColor2(playerid, slot),
                                    item_maturity);

        if (item != INVALID_ITERATOR_SLOT) {
            InvItem_Reset(playerid, slot);
            InvItem_SetSelected(playerid, -1);
            Inventory_UpdateSlot(playerid, slot);

            Store_UpdateSlot(item);
        }
    }
    MySQL_BindInt(stmt_insertSlotStore, 0, seller);
    MySQL_BindInt(stmt_insertSlotStore, 1, type_price);
    MySQL_BindInt(stmt_insertSlotStore, 2, price);
    MySQL_Bind(stmt_insertSlotStore, 3, InvItem_GetName(playerid, slot));
    MySQL_BindInt(stmt_insertSlotStore, 4, InvItem_GetType(playerid, slot));
    MySQL_BindInt(stmt_insertSlotStore, 5, InvItem_GetModel(playerid, slot));
    MySQL_BindInt(stmt_insertSlotStore, 6, InvItem_GetQuantity(playerid, slot));
    MySQL_BindInt(stmt_insertSlotStore, 7, InvItem_GetColor1(playerid, slot));
    MySQL_BindInt(stmt_insertSlotStore, 8, InvItem_GetColor2(playerid, slot));
    MySQL_Bind(stmt_insertSlotStore, 9, item_maturity);
    MySQL_ExecuteThreaded_Inline(stmt_insertSlotStore, using inline OnInsertStoreItem);
}

stock Store_Sell(playerid, slot, type_price)
{
    inline D_StoreSellItem(did, ddialogid, dresponse, dlistitem, string:dtext[])
    {
        #pragma unused did, ddialogid, dlistitem

        if (!dresponse)
            return 1;

        new price = strval(dtext);
		if (price < 1 || price > max_money_limit)
            return SendClientMessage(playerid, -1, "Esse valor não é valido.");

        StoreItem_Insert(playerid, slot, type_price, price);
    }
    Dialog_ShowCallback(playerid, using inline D_StoreSellItem, DIALOG_STYLE_INPUT, ""C_WHITE"-", 
    ""C_GRAY"-> Digite o valor que deseja para anunciar o item:", "Anunciar", "Cancelar");

    return 1;
}

stock StoreItem_Create(id, seller, type_price, price, const item_name[], item_tipo, item_modelo, item_quantity, item_color1, item_color2, const item_maturity[])
{
    new items = Iter_Free(StoreItems);

    if (items != INVALID_ITERATOR_SLOT) {
        Iter_Add(StoreItems, items);

        StoreItem_SetID(items, id);
        StoreItem_SetSeller(items, seller);
        StoreItem_SetTypePrice(items, type_price);
        StoreItem_SetPrice(items, price);
        StoreItem_SetName(items, item_name);
        StoreItem_SetType(items, item_tipo);
        StoreItem_SetModel(items, item_modelo);
        StoreItem_SetQuantity(items, item_quantity);
        StoreItem_SetColor1(items, item_color1);
        StoreItem_SetColor2(items, item_color2);
        StoreItem_SetMaturity(items, item_maturity);
    }
    return items;
}

stock Store_UpdateSlot(slot)
{
    new first_item,
        last_item;

    foreach (new playerid : Player)
    {
        if (PlayerInStore(playerid)) {
            first_item = (Store_GetPage(playerid) * MAX_STORE_SLOT_PERPAGE);
            last_item = (first_item + MAX_STORE_SLOT_PERPAGE);

            if (slot >= first_item || slot <= last_item)
                Store_UpdatePlayerSlot(playerid, slot);
        }
    }
}

stock Store_UpdatePlayerSlot(playerid, slot)
{
	new model = StoreItem_GetModel(slot),
		first_slot = (Store_GetPage(playerid) * MAX_STORE_SLOT_PERPAGE),
		text = (slot - first_slot);

	if (Iter_Contains(StoreItems, slot)) 
	{
		switch (StoreItem_GetType(slot))
		{
			case ITEM_TYPE_WEAPON: {
				PlayerTextDrawSetPreviewRot(playerid, store_ptd_preview[text][playerid], -16.000000, 0.000000, -55.000000, 1.000000);
				model = GetWeaponModel(model);
			}
			case ITEM_TYPE_MOTORISTA, ITEM_TYPE_PILOTO, ITEM_TYPE_MARUJO, ITEM_TYPE_EXPLOSIVO: {
				PlayerTextDrawSetPreviewRot(playerid, store_ptd_preview[text][playerid], -16.000000, 0.000000, 180.000000, 1.000000);
			}
			case ITEM_TYPE_DRONE: {
				PlayerTextDrawSetPreviewVehCol(playerid, store_ptd_preview[text][playerid], InvItem_GetColor1(playerid, slot), InvItem_GetColor2(playerid, slot));
			}
			case ITEM_TYPE_SKIN: {
				model = GetSkinModel(model);
			}
			case ITEM_TYPE_PANEL: {
				model = 19805;
			}
		}
	} else model = 999;

	PlayerTextDrawSetPreviewModel(playerid, store_ptd_preview[text][playerid], model);

    new string[128];
    format(string, sizeof(string), "%s", getFormatText(StoreItem_GetQuantity(slot)));
    PlayerTextDrawSetString(playerid, store_ptd_qtd[text][playerid], string);
    format(string, sizeof(string), "%s %s", StoreItem_GetTypePrice(slot) == VALUE_TYPE_CASH ? "~b~C$" : "~g~$", getFormatText(StoreItem_GetPrice(slot)));
    PlayerTextDrawSetString(playerid, store_ptd_price[text][playerid], string);

	if (PlayerInStore(playerid)) {
		PlayerTextDrawShow(playerid, store_ptd_preview[text][playerid]);
		PlayerTextDrawShow(playerid, store_ptd_qtd[text][playerid]);
		PlayerTextDrawShow(playerid, store_ptd_price[text][playerid]);
	}
	return 1;
}

stock Store_UpdatePage(playerid)
{
	new string[5],
		first_slot = (Store_GetPage(playerid) * MAX_STORE_SLOT_PERPAGE),
        last_slot = (Store_GetPage(playerid) + 1) * MAX_STORE_SLOT_PERPAGE;

	for (new slot = first_slot; slot < last_slot; slot++)
		Store_UpdatePlayerSlot(playerid, slot);
	
	format(string, sizeof(string), "%d-%d", (Store_GetPage(playerid) + 1), MAX_PAGES_STORE);
	PlayerTextDrawSetString(playerid, store_ptd_page[playerid], string);
}

CMD:verstore(playerid)
    return Store_Show(playerid);

stock Store_Show(playerid)
{
    // if (!Inventory_IsOpen(playerid))
    //     return SendClientMessage(playerid, -1, "Você precisa estar com o inventário aberto.");

    PlayerSetInStore(playerid, true);

	TextDrawShowForPlayer(playerid, inv_background[1]);
    
    for (new slot; slot < MAX_STORE_SLOT_PERPAGE; slot++) {
        printf("slot: %d", slot);
	    PlayerTextDrawShow(playerid, store_ptd_preview[slot][playerid]);
	    PlayerTextDrawShow(playerid, store_ptd_qtd[slot][playerid]);
	    PlayerTextDrawShow(playerid, store_ptd_price[slot][playerid]);
	}
	PlayerTextDrawShow(playerid, store_ptd_page[playerid]);
	TextDrawShowForPlayer(playerid, store_td_prevpage);
	TextDrawShowForPlayer(playerid, store_td_nextpage);

    Store_UpdatePage(playerid);

    return 1;
}

stock Store_Hide(playerid)
{
    PlayerSetInStore(playerid, false);

    for (new slot; slot < MAX_STORE_SLOT_PERPAGE; slot++) {
	    PlayerTextDrawHide(playerid, store_ptd_preview[slot][playerid]);
	    PlayerTextDrawHide(playerid, store_ptd_qtd[slot][playerid]);
	    PlayerTextDrawHide(playerid, store_ptd_price[slot][playerid]);
	}
	PlayerTextDrawHide(playerid, store_ptd_page[playerid]);
	TextDrawHideForPlayer(playerid, store_td_prevpage);
	TextDrawHideForPlayer(playerid, store_td_nextpage);
}

    // MEGAString[0] = EOS;

    // format(MEGAString, sizeof(MEGAString), 
    //     ""C_WHITE"Voce esta comprando o item "C_YELLOW"%s "C_WHITE"com "C_CYAN"%d "C_WHITE"unidades\n\n
    //     "C_WHITE"Tipo do item: "C_GRAY"%s\n
    //     "C_WHITE"Valor do item: %s%s\n
    //     "C_WHITE"Nivel de raridade: %s\n
    //     "C_RED"Observacao: "C_WHITE"Digite '"C_GREEN"CONFIRMAR"C_WHITE"' para comprar o item."); // 

    // ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, ""C_YELLOW"[ COMPRANDO ITEM ]", MEGAString, "Comprar", "Cancelar");