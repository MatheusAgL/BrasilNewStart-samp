#include <YSI_Coding\y_hooks>

#include <bau_entry>
#include <bau_cmds>

static 
    Statement: stmt_createBau,
	Statement: stmt_destroyBau,
	Statement: stmt_updateBau,
	Statement: stmt_createBauItem,
	Statement: stmt_removeBauItem,
	Statement: stmt_selectBauItens,
    Statement: stmt_selectBaus;

hook OnMySQLConnected() 
{
    static const query_createBau[] = 
		"INSERT INTO `bau` \
            (`player`, `name`, `model`, `max`, `pos_x`, `pos_y`, `pos_z`, `pos_a`, `world`, `interior`, `date_created`)  \
        VALUES \
            (?, '?', '?', '?', '?', '?', '?', '?', '?', '?', CURRENT_TIMESTAMP) \
        ";
	stmt_createBau = MySQL_PrepareStatement(MySQL_Handle, query_createBau);

    static const query_selectBaus[] = "SELECT \
			b.id, b.player, b.name, b.model, b.max, b.pos_x, b.pos_y, b.pos_z, b.pos_a, b.world, b.interior, p.nome \
		FROM `bau` b \
		INNER JOIN `player` p \
			ON b.player = p.id \
		ORDER BY b.id";
	stmt_selectBaus = MySQL_PrepareStatement(MySQL_Handle, query_selectBaus);

	static const query_selectBauItens[] = "SELECT \
			id, bau, name, type, model, quantidade, color_1, color_2 \
		FROM `bau_itens` \
		ORDER BY bau";
	stmt_selectBauItens = MySQL_PrepareStatement(MySQL_Handle, query_selectBauItens);

	static const query_destroyBau[] = "DELETE FROM `bau` WHERE `id` = '?'";
	stmt_destroyBau = MySQL_PrepareStatement(MySQL_Handle, query_destroyBau);

	static const query_createBauItem[] = "INSERT INTO bau_itens \
		(bau, name, `type`, model, quantidade, color_1, color_2, date_modified) \
		VALUES(?, ?, ?, ?, ?, ?, ?, CURRENT_TIMESTAMP);";

	stmt_createBauItem = MySQL_PrepareStatement(MySQL_Handle, query_createBauItem);

	static const query_removeBauItem[] = "DELETE FROM `bau_itens` WHERE `id` = '?'";
	stmt_removeBauItem = MySQL_PrepareStatement(MySQL_Handle, query_removeBauItem);

	static const query_updateBau[] = "UPDATE `bau` \
		SET pos_x=?, pos_y=?, pos_z=?, pos_a=?, world=?, interior=? \
		WHERE `id` = '?'";
	stmt_updateBau = MySQL_PrepareStatement(MySQL_Handle, query_updateBau);

	return 1;
}

hook OnGameModeInit() {

	inline const OnLoadBaus() {

		new 
			index,
			lootid,
			idgplayer,
            lootname[MAX_LOOT_NAME],
            model,
			maxItems,
            Float:pos[4],
			world,
			interior,
			playername[MAX_PLAYER_NAME]
        ;

		MySQL_BindResultInt(stmt_selectBaus, 0, lootid);
		MySQL_BindResultInt(stmt_selectBaus, 1, idgplayer);
		MySQL_BindResult(stmt_selectBaus, 2, lootname, sizeof(lootname));
        MySQL_BindResultInt(stmt_selectBaus, 3, model);
		MySQL_BindResultInt(stmt_selectBaus, 4, maxItems);
		MySQL_BindResultFloat(stmt_selectBaus, 5, pos[0]);
		MySQL_BindResultFloat(stmt_selectBaus, 6, pos[1]);
		MySQL_BindResultFloat(stmt_selectBaus, 7, pos[2]);
		MySQL_BindResultFloat(stmt_selectBaus, 8, pos[3]);
		MySQL_BindResultInt(stmt_selectBaus, 9, world);
		MySQL_BindResultInt(stmt_selectBaus, 10, interior);
		MySQL_BindResult(stmt_selectBaus, 11, playername, sizeof(playername));

		while (MySQL_Statement_FetchRow(stmt_selectBaus)) {
			index = Iter_Free(IterLoot);

			if (index != INVALID_ITERATOR_SLOT) {
				Iter_Add(IterLoot, index);

				Loot_SetID(index, lootid);
				Loot_SetOwner(index, idgplayer);
				Loot_SetOwnerName(index, playername);
				Loot_SetMaxItems(index, maxItems);

				Loot_SetModel(index, lootname, model);
				Loot_SetPos(index, pos[0], pos[1], pos[2], pos[3], world, interior);

				Loot_CreateObject(index);
				Loot_CreateTextLabel(index);
			}
		}
	}
    MySQL_ExecuteThreaded_Inline(stmt_selectBaus, using inline OnLoadBaus);

	// Carregando os itens
	inline const OnLoadBausItens() {

		new 
			id,
			itemid,
			lootid,
            itemname[MAX_LOOT_NAME],
			type,
            modelid,
			amount,
			color_1,
			color_2,
			previousLootId,
			lootIndex
        ;

		while (MySQL_Statement_FetchRow(stmt_selectBauItens)) {
			MySQL_BindResultInt(stmt_selectBauItens, 0, itemid);
			MySQL_BindResultInt(stmt_selectBauItens, 1, lootid);
			MySQL_BindResult(stmt_selectBauItens, 2, itemname, sizeof(itemname));
			MySQL_BindResultInt(stmt_selectBauItens, 3, type);
			MySQL_BindResultInt(stmt_selectBauItens, 4, modelid);
			MySQL_BindResultInt(stmt_selectBauItens, 5, amount);
			MySQL_BindResultInt(stmt_selectBauItens, 6, color_1);
			MySQL_BindResultInt(stmt_selectBauItens, 7, color_2);

			if(previousLootId != lootid) {
				Loot_UpdateTextLabel(lootIndex);

				foreach(new l : IterLoot) {
					if(Loot_GetID(l) == lootid) {
						lootIndex = l;
						break;
					}
				}
				previousLootId = lootid;
			}

			id = Iter_Free(IterLootItem[lootIndex]);

			if (id != INVALID_ITERATOR_SLOT) {
				Iter_Add(IterLootItem[lootIndex], id);

				LootItem_SetID(lootIndex, id, itemid);
				LootItem_SetType(lootIndex, id, type);
				LootItem_SetModel(lootIndex, id, modelid);
				LootItem_SetName(lootIndex, id, itemname);
				LootItem_SetAmount(lootIndex, id, amount);
				LootItem_SetCor1(lootIndex, id, color_1);
				LootItem_SetCor2(lootIndex, id, color_2);
			}
		}
		Loot_UpdateTextLabel(lootIndex);
	}
    MySQL_ExecuteThreaded_Inline(stmt_selectBauItens, using inline OnLoadBausItens);

	return 1;
}

hook OP_EditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if (GetPVarInt(playerid, "UpdatingLoot") && response != EDIT_RESPONSE_UPDATE) {
		new loot = GetPVarInt(playerid, "UpdateLootID");
		if (objectid == Loot_GetObject(loot)) {
			Loot_SetPos(loot, x, y, z, rz, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
			Loot_UpdateObject(loot);

			Loot_DestroyTextLabel(loot);
			Loot_CreateTextLabel(loot);
			Loot_Save(loot);
		}
		SetPVarInt(playerid, "UpdatingLoot", 0);
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) 
{
	if (newkeys & KEY_WALK) {
		new loot = Player_LootCloser(playerid);

		if (loot != -1) {
		    if (Loot_GetOwner(loot) != Player_GetAccountID(playerid) && Dev_GetNivel(playerid) < DEV_DELTA)
				return SendClientMessage(playerid, -1, "Você não é o proprietário desse baú.");

			Loot_ShowDialog(playerid);
		}
	}
	return 1;
}

stock Loot_ShowDialog(playerid)
{
	inline D_Loot(dlootid, dlootdialogid, dlootresponse, dlootlistitem, string:dloottext[])
	{
		#pragma unused dlootid, dlootdialogid, dloottext, dlootlistitem
		if (!dlootresponse) 
			return 1;

        new loot = Player_LootCloser(playerid);
		if (loot == -1)
			return SendClientMessage(playerid, -1, "Você não está próximo de um baú.");

		if (Loot_GetOwner(loot) != Player_GetAccountID(playerid) && Dev_GetNivel(playerid) < DEV_DELTA)
			return SendClientMessage(playerid, -1, "Você não é o proprietário desse baú.");

		switch(dlootlistitem) {

			case 0: {
				Loot_ShowPlayerItems(playerid, loot);
			}
			case 1: {
				Loot_ShowListItens(playerid, loot);
			}
			case 2: {
				SetPVarInt(playerid, "UpdateLootID", loot);
				SetPVarInt(playerid, "UpdatingLoot", 1);
				EditDynamicObject(playerid, Loot_GetObject(loot));
			}
			case 3:
			{
				if (Loot_CountItens(loot)) 
					return SendClientMessage(playerid, -1, "O baú precisa estar vazio para guarda-lo.");

				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

				SendMsgF(playerid, COLOR_LIGHTBLUE, "* Você guardou um %s em seu inventário.", Loot_GetName(loot));

				Loot_SetInventory(playerid, Loot_GetName(loot), Loot_GetModel(loot));
				Loot_Destroy(playerid, loot);
			}
	    }
		return 1;
	}
    Dialog_ShowCallback(playerid, using inline D_Loot, DIALOG_STYLE_TABLIST_HEADERS, ""C_BLUELIGHT"Baú: Opcões", 
		"Ação\tInformação\n\
		"C_WHITE"Guardar Item\t"C_GRAY"Remove o item do inventário e adiciona no bau\n\
		"C_WHITE"Pegar Item\t"C_GRAY"Recebe o item no inventário e remove do bau\n\
		"C_WHITE"Mover Bau\t"C_GRAY"Edita a posição atual do bau\n\
		"C_WHITE"Desmontar Bau\t"C_GRAY"Guarda o bau no inventario", 
		"Selecionar", ""C_WARNING"Fechar");

	return 1;
}


hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) 
{
	if (dialogid == 8784)
	{
	    if (response) {
	        new loot = Player_LootCloser(playerid);

			if (loot != -1)
			{
			    if (Loot_GetOwner(loot) != Player_GetAccountID(playerid) && Dev_GetNivel(playerid) < DEV_DELTA) 
					return SendClientMessage(playerid, -1, "Você não é o dono desse baú.");

				if (!InventarioInfo[playerid][listitem][item_valid]) {
					Loot_ShowPlayerItems(playerid, loot);
					return SendClientMessage(playerid, COLOR_LIGHTRED, "O item que você selecionou é inválido.");
				}

				if (InventarioInfo[playerid][listitem][item_vender]) {
					Loot_ShowPlayerItems(playerid, loot);
					return SendClientMessage(playerid, COLOR_LIGHTRED, "Você está negociando esse item, não pode guarda-lo no baú.");
				}

				if (InventarioInfo[playerid][listitem][item_type] == ITEM_TYPE_CELULAR && InventarioInfo[playerid][listitem][item_model] == 18874) {
					Loot_ShowPlayerItems(playerid, loot);
					return SendClientMessage(playerid, COLOR_LIGHTRED, "Não pode guardar números de celular no baú.");
				}

                new result = LootItem_Add(
					loot, InventarioInfo[playerid][listitem][item_type], InventarioInfo[playerid][listitem][item_model],
					InventarioInfo[playerid][listitem][item_nome], InvItem_GetQuantity(playerid, listitem),
					InventarioInfo[playerid][listitem][item_cor1], InventarioInfo[playerid][listitem][item_cor2]
				);

				if (!result) {
					Loot_ShowPlayerItems(playerid, loot);
					return SendClientMessage(playerid, COLOR_LIGHTRED, "O baú está sem espaço, retire algumas coisas ou coloque outro baú.");
				}

				SendMsgF(playerid, COLOR_LIGHTBLUE, "* Você guardou %d unidade(s) de %s nesse baú.", InvItem_GetQuantity(playerid, listitem), InventarioInfo[playerid][listitem][item_nome]);
				ServerLog::("bau_itens", "%s (%d) guardou %d unidade(s) de %s (cores: %d/%d) no baú.", PlayerName[playerid], Player_GetAccountID(playerid), InvItem_GetQuantity(playerid, listitem), InventarioInfo[playerid][listitem][item_nome]);

				InvItem_Reset(playerid, listitem); 
				Loot_ShowPlayerItems(playerid, loot);
			}
			else SendClientMessage(playerid, COLOR_GREY, "Você não está próximo de um baú.");
	    }
		else
		{
	        Loot_ShowDialog(playerid);
	    }
	    return true;
	}
	return 1;
}

stock OnPlayerUseDepository(playerid, const itemname[], modelid) 
{
	if (Player_CountLoot(playerid) >= Player_MaxLoot(playerid))
		return SendMsgF(playerid, COLOR_LIGHTRED, "Você pode apenas ter %d baús de acordo com seu VIP. Use: /bau localizar", Player_MaxLoot(playerid)), false;

	new loot = Iter_Free(IterLoot);
	if (loot == INVALID_ITERATOR_SLOT)
		return SendClientMessage(playerid, -1, "Não há mais espaços para baús no servidor."), false;

	Loot_PlayerCreate(playerid, modelid, itemname);
	return SendMsgF(playerid, COLOR_LIGHTBLUE, "Você montou um(a) %s, agora poderá guardar e pegar itens nela.", itemname);
}

static Loot_Create(playerid, const itemname[], modelid, Float:x, Float:y, Float:z, Float:a, interior=0, world=0)
{
	new loot = Iter_Free(IterLoot),
		maxItems = Loot_GenerateMaxItems(playerid, modelid);
	
	if (loot != INVALID_ITERATOR_SLOT) {
		MySQL_BindInt(stmt_createBau, 0, Player_GetAccountID(playerid));
		MySQL_Bind(stmt_createBau, 1, itemname, true);
		MySQL_BindInt(stmt_createBau, 2, modelid);
		MySQL_BindInt(stmt_createBau, 3, maxItems);
		MySQL_BindFloat(stmt_createBau, 4, x);
		MySQL_BindFloat(stmt_createBau, 5, y);
		MySQL_BindFloat(stmt_createBau, 6, z);
		MySQL_BindFloat(stmt_createBau, 7, a);
		MySQL_BindInt(stmt_createBau, 8, world);
		MySQL_BindInt(stmt_createBau, 9, interior);

		inline const OnLootCreated() {
			Iter_Add(IterLoot, loot);

			Loot_SetID(loot, cache_insert_id());
			Loot_SetMaxItems(loot, maxItems);
			Loot_SetPos(loot, x, y, z, a, world, interior);

			Loot_SetOwner(loot, PlayerInfo[playerid][pID]);
			Loot_SetOwnerName(loot, PlayerName[playerid]);

			Loot_SetModel(loot, itemname, modelid);
			
			Loot_CreateObject(loot);
			Loot_CreateTextLabel(loot);
		}
		MySQL_ExecuteThreaded_Inline(stmt_createBau, using inline OnLootCreated);
	}
	return loot;
}

stock Loot_Save(lootid) {
	new Float:x, Float:y, Float:z, Float:a, world, interior;

	Loot_GetPos(lootid, x, y, z, a, world, interior);

	MySQL_BindFloat(stmt_updateBau, 0, x);
	MySQL_BindFloat(stmt_updateBau, 1, y);
	MySQL_BindFloat(stmt_updateBau, 2, z);
	MySQL_BindFloat(stmt_updateBau, 3, a);
	MySQL_BindInt(stmt_updateBau, 4, world);
	MySQL_BindInt(stmt_updateBau, 5, interior);
	MySQL_BindInt(stmt_updateBau, 6, Loot_GetID(lootid));
	MySQL_ExecuteThreaded(stmt_updateBau);
}

stock Loot_Destroy(playerid, loot)
{
	if (Iter_Contains(IterLoot, loot)) {
	    Iter_Remove(IterLoot, loot);
		Iter_Clear(IterLootItem[loot]);
	    
		Loot_DestroyObject(loot);
		Loot_DestroyTextLabel(loot);

		foreach (new item : IterLootItem[loot])
			LootItem_Remove(loot, item);
	
		MySQL_BindInt(stmt_destroyBau, 0, Loot_GetID(loot));
		MySQL_ExecuteThreaded(stmt_destroyBau);

		new string[128];

		format(string, sizeof(string), "%s removeu o baú id: %d (%s).", PlayerName[playerid], loot, Loot_GetName(loot));
		server_log("baus", string);

	    return true;
	}
	return false;
}

static Loot_PlayerCreate(playerid, modelid, const itemname[]="Bau Simples")
{
	new 
		Float:x,
		Float:y,
		Float:z,
		Float:a
	;

	// Cria na posição atual do player;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	new loot = Loot_Create(playerid, itemname, modelid, x, y, z - 0.5, a, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

	if (loot != -1) {
	    Inventory_HideForPlayer(playerid);

		Loot_PlayerEdit(playerid, loot);

		new string[128];
	    format(string, sizeof(string), "%s colocou um bau (ID: %d) | pos: (%f %f %f).", PlayerName[playerid], loot, x, y, z);
    	server_log("baus", string);
	}
	return loot;
}

stock Loot_ShowListItens(playerid, loot) {
	if (Iter_Contains(IterLoot, loot))
	{
		MEGAString[0] = EOS;
	    new string[128];

		strcat(MEGAString, "Nome do item\tQuantidade\n");
	    
	    foreach (new item : IterLootItem[loot]) {
	        format(string, sizeof (string), "%s\t%d\n", LootItem_GetName(loot, item), LootItem_GetAmount(loot, item));
	        strcat(MEGAString, string);
	    }

		inline D_LootItens(dyid, dydialogid, dyresponse, dylistitem, string:dytext[])
		{
			#pragma unused dyid, dydialogid, dytext, dyresponse
			if(!dyresponse)
				return Loot_ShowDialog(playerid);

			if (isInventoryFull(playerid))
				return SendClientMessage(playerid, -1, "Você não tem espaço no inventário."), Loot_ShowListItens(playerid, loot);

			new item = Iter_Index(IterLootItem[loot], dylistitem);

			if (!Iter_Contains(IterLootItem[loot], item))
				return SendClientMessage(playerid, -1, "Item inválido."), Loot_ShowListItens(playerid, loot);

			givePlayerItem(playerid, 
				LootItem_GetType(loot, item), 
				LootItem_GetModel(loot, item), 
				LootItem_GetAmount(loot, item), 
				LootItem_GetName(loot, item),
				LootItem_GetCor1(loot, item),
				LootItem_GetCor2(loot, item)
			);
			SendMsgF(playerid, COLOR_LIGHTBLUE, "* Você pegou um(a) %s com %d unidades do seu baú.", LootItem_GetName(loot, item), LootItem_GetAmount(loot, item));

			format(string, sizeof string, "%s pegou %d unidade(s) de %s no baú %d.", PlayerName[playerid], LootItem_GetAmount(loot, item), LootItem_GetName(loot, item), loot);
			server_log("baus", string);

			LootItem_Remove(loot, item);
			Loot_ShowListItens(playerid, loot);
		}

		format(string, sizeof(string), ""C_BLUELIGHT"Itens do Bau [%d/%d]", Loot_CountItens(loot), Loot_GetMaxItems(loot));
		Dialog_ShowCallback(playerid, using inline D_LootItens, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Pegar", ""C_WARNING"Retornar");
		
	    return 1;
	}
	return 0;
}

stock LootItem_Remove(loot, item)
{
	if (Iter_Contains(IterLootItem[loot], item)) {
		MySQL_BindInt(stmt_removeBauItem, 0, LootItem_GetID(loot, item));
		MySQL_ExecuteThreaded(stmt_removeBauItem);

		Iter_Remove(IterLootItem[loot], item);
		Loot_UpdateTextLabel(loot);
	}
	return 1;
}

stock LootItem_Add(loot, type, model, const nome[], quantia, cor1 = 0, cor2 = 0)
{
	if (Loot_CountItens(loot) >= Loot_GetMaxItems(loot))
		return false;

	new item = Iter_Free(IterLootItem[loot]);
	new itemName[75];
	format(itemName, sizeof(itemName), nome);

	if (item != INVALID_ITERATOR_SLOT) {
		new lootId = Loot_GetID(loot);

		MySQL_BindInt(stmt_createBauItem, 0, lootId);
		MySQL_Bind(stmt_createBauItem, 1, nome);
		MySQL_BindInt(stmt_createBauItem, 2, type);
		MySQL_BindInt(stmt_createBauItem, 3, model);
		MySQL_BindInt(stmt_createBauItem, 4, quantia);
		MySQL_BindInt(stmt_createBauItem, 5, cor1);
		MySQL_BindInt(stmt_createBauItem, 6, cor2);

		inline OnLootItemCreated() {
			Iter_Add(IterLootItem[loot], item);

			LootItem_SetID(loot, item, cache_insert_id());
			LootItem_SetValid(loot, item, 1);
			LootItem_SetModel(loot, item, model);
			LootItem_SetAmount(loot, item, quantia);
			LootItem_SetType(loot, item, type);
			LootItem_SetCor1(loot, item, cor1);
			LootItem_SetCor2(loot, item, cor2);
			LootItem_SetName(loot, item, itemName);

			Loot_UpdateTextLabel(loot);
		}
		MySQL_ExecuteThreaded_Inline(stmt_createBauItem, using inline OnLootItemCreated);
		return true;
	}
	return false;
}

stock Loot_ShowPlayerItems(playerid, lootid) {

  	MEGAString[0] = EOS;
    strcat(MEGAString, "Nome do item\tQuantidade\n");

	new string[97];

	for (new item; item != MAX_ITENS_INVENTARIO; item++) {
		if (InventarioInfo[playerid][item][item_valid]) {
			format(string, sizeof (string), "%s\t%d\n", InventarioInfo[playerid][item][item_nome], InvItem_GetQuantity(playerid, item));
   		} else {
			format(string, sizeof (string), "{AAAAAA}Nenhum\n");
   		}
     	strcat(MEGAString, string);
	}

	format(string, sizeof(string), "Selecione o item que deseja guardar [%d/%d]", Loot_CountItens(lootid), Loot_GetMaxItems(lootid));
	return ShowPlayerDialog(playerid, 8784, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "GUARDAR", "VOLTAR");
}
