#include <YSI_Coding\y_hooks>

#include <trashcan_entry>
#include <trashcan_cmds>

// ------------------------ Sistema de grupos de usuário ------------------------
new 
		Statement: stmt_updateTrashCanItem,
		Statement: stmt_deleteTrashCanItem;

hook OnMySQLConnected() 
{
	static const query_updateTrashCanItem[] = 
		"UPDATE `trashcan_items` \
			SET `item_type` = ?, \
				`item_model` = ?, \
				`item_quantity` = ?, \
				`item_color1` = ?, \
				`item_color2` = ? \
				`item_name` = ?, \
			WHERE `trashcan_id` = ? AND `slot` = ?"
	;
	stmt_updateTrashCanItem = MySQL_PrepareStatement(MySQL_Handle, query_updateTrashCanItem);

    static const query_deleteTrashCanItem[] = 
		"DELETE FROM `trashcan_items` WHERE `trashcan_id` = ? AND `slot` = ?"
	;
	stmt_deleteTrashCanItem = MySQL_PrepareStatement(MySQL_Handle, query_deleteTrashCanItem);

    return 1;
}

stock Trash_CancelEdit(objectid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) 
{
	#pragma unused rx, ry

	foreach(new trash : IterTrash) {
		if (objectid == TrashCan_GetObject(trash)) {
			TrashCan_SetPosX(trash, x);
			TrashCan_SetPosX(trash, y);
			TrashCan_SetPosX(trash, y);
			TrashCan_SetPosX(trash, rz);

			TrashCan_UpdateText(id);
			TrashCan_Save(id);

			return 1;
		}
	}
	return 0;
}

stock TrashCan_DiscardAllItens(playerid)
{
	new count = 0,
		valid,
		type,
		model,
		quantity,
		color1,
		color2,
		item_name[34];

	for (new slot; slot != MAX_ITENS_INVENTARIO; slot++) 
	{
		valid = InvItem_GetValid(playerid, slot);
		type = InvItem_GetType(playerid, slot);
		model = InvItem_GetModel(playerid, slot);
		quantity = InvItem_GetQuantity(playerid, slot);
		color1 = InvItem_GetColor1(playerid, slot);
		color2 = InvItem_GetColor2(playerid, slot);
		format(item_name, sizeof(item_name), InvItem_GetName(playerid, slot));

		if (valid && type == ITEM_TYPE_LIXO)
			if (TrashCan_GiveItem(trashcan, type, model, color1, color2, quantity, item_name)) InvItem_Reset(playerid, slot), count++;
	}
	if (count < 1) return SendClientMessage(playerid, COLOR_LIGHTRED, "Nenhum item foi descartado na lixeira.");

	SendMsgF(playerid, COLOR_LIGHTGREEN, "[LIXEIRA]: Você descartou %d lixo(s) do seu inventário **", count);
	return 1;
}

stock TrashCan_ShowDialog(playerid)
{
	inline D_TrashCanActions(did, ddialogid, dresponse, dlistitem, string:dtext[])
	{
		#pragma unused did, ddialogid, dlistitem

		if (!response)
			return 1;

		new trashcan = TrashCan_Get(playerid);
		if (trashcan == -1) 
			return SendClientMessage(playerid, -1, "Você não está próximo de uma lixeira.");

		switch(dlistitem)
		{
			case 0: SetPlayerLixeira(playerid);
			case 1: TrashCan_DiscardItems(playerid);
			case 2: TrashCan_DiscardAllItens(playerid);
			case 3: TrashCan_ListItems(playerid, id);
		}
		return 1;
	}
	Dialog_ShowCallback(playerid, using inline D_TrashCanActions, DIALOG_STYLE_TABLIST, 
	"escolha uma opção",
	""C_GRAY"ESCONDER-SE\t"C_WHITE"Você fica escondido dentro da lixeira\n\
	"C_GRAY"DESCARTAR ITEM\t"C_WHITE"Você joga um item do inventário na lixeira\n\
	"C_GRAY"DESCARTAR TODOS LIXOS\t"C_WHITE"Descarta todos os seus lixos acumulados na lixeira\n\
	"C_GRAY"INSPECIONAR LIXO\t"C_WHITE"Vasculhar itens que estão na lixeira\n", "Selecionar", "Cancelar");

	return 1;
}

stock TrashCan_DiscardItems(playerid)
{
    new string[128],
		valid,
		quantity,
		item_name[34];

  	MEGAString[0] = EOS;
    strcat(MEGAString, "nome do item\tqtd.\n");

    for (new slot; slot != MAX_ITENS_INVENTARIO; slot++)
	{
		valid = InvItem_GetValid(playerid, slot);
		quantity = InvItem_GetQuantity(playerid, slot);
		format(item_name, sizeof(item_name), InvItem_GetName(playerid, slot));
		
		if (valid)
			format(string, sizeof (string), ""C_GRAY"%s\t"C_WHITE"%d\n", item_name, quantity);
		else
			format(string, sizeof (string), ""C_GRAY"----------> VAZIO\n");
		
     	strcat(MEGAString, string);
	}
	ShowPlayerDialog(playerid, 4265, DIALOG_STYLE_TABLIST_HEADERS, ""C_RED"[ DESCARTAR ITEM ]", MEGAString, "Descartar", "Retornar");

	return 1;
}

stock TrashCan_GiveItem(trashcan, type, model, color1, color2, quantity, const name[])
{
	if (trashcan == -1) 
		return false;

    new valid;
	for (new slot; slot != MAX_TRASH_ITENS; slot++)
	{
		valid = TrashCan_GetValid(trashcan, slot);
		if (valid)
		{
			TrashCanItem_SetValid(trashcan, slot, true);
			TrashCanItem_SetType(trashcan, slot, type);
			TrashCanItem_SetModel(trashcan, slot, model);
			TrashCanItem_SetQuantity(trashcan, slot, color1);
			TrashCanItem_SetColor1(trashcan, slot, color2);
			TrashCanItem_SetColor2(trashcan, slot, quantity);
			TrashCanItem_SetName(trashcan, slot, name);

			MySQL_BindInt(stmt_updateTrashCanItem, 0, type);
			MySQL_BindInt(stmt_updateTrashCanItem, 1, model);
			MySQL_BindInt(stmt_updateTrashCanItem, 2, quantity);
			MySQL_BindInt(stmt_updateTrashCanItem, 3, color1);
			MySQL_BindInt(stmt_updateTrashCanItem, 4, color2);
			MySQL_BindInt(stmt_updateTrashCanItem, 5, name);
			MySQL_BindInt(stmt_updateTrashCanItem, 6, trashcan);
			MySQL_BindInt(stmt_updateTrashCanItem, 7, slot);
			MySQL_ExecuteThreaded(stmt_updateTrashCanItem);

	    	return true;
		}
	}
	return false;
}

stock TrashCan_ListItems(playerid, id)
{
	if (Iter_Contains(IterTrash, id))
	{
		// Setar o angulo do player para o ferido
	    SetPlayerFaceToPoint(playerid, trashInfo[id][trashPos][0], trashInfo[id][trashPos][1]);

	    // Aplicar animação de médico
	    ApplyAnimation(playerid, "OTB", "betslp_tnk", 4.1, true, false, false, false, 0, SYNC_ALL);

		// Formatando a MEGAString
	    MEGAString[0] = EOS;
	
	    new string_add[128];
	    
	    strcat(MEGAString, "Nome do item\tQuantidade\n");
	    
	    for (new item; item != MAX_TRASH_ITENS; item++)
		{
	        if (trashItens[id][item][item_valid])
				format(string_add, sizeof (string_add), "%s\t%d\n", trashItens[id][item][item_nome], trashItens[id][item][item_quantia]);
				
	        else format(string_add, sizeof (string_add), "{AAAAAA}Nenhum\n");

	        strcat(MEGAString, string_add);
	    }
		
		ShowPlayerDialog(playerid, 4266, DIALOG_STYLE_TABLIST_HEADERS, "Itens nessa lixeira", MEGAString, "Pegar", "Retornar");

		return 1;
	}
	return false;
}

stock TrashCan_RemoveItem(trashcan, slot)
{
    new valid = TrashCanItem_GetValid(trashcan, slot);
	if (valid)
	{
		TrashCanItem_SetValid(trashcan, slot, false);
		TrashCanItem_SetType(trashcan, slot, 0);
		TrashCanItem_SetModel(trashcan, slot, 0);
		TrashCanItem_SetQuantity(trashcan, slot, 0);
		TrashCanItem_SetColor1(trashcan, slot, 0);
		TrashCanItem_SetColor2(trashcan, slot, 0);
		TrashCanItem_SetName(trashcan, slot, "Nenhum");

		MySQL_BindInt(stmt_deleteTrashCanItem, 0, trashcan);
		MySQL_BindInt(stmt_deleteTrashCanItem, 1, slot);
		MySQL_ExecuteThreaded(stmt_deleteTrashCanItem);

	    TrashCan_UpdateText(trashcan);

	    return true;
	}
	return false;
}

stock localTrashCan(playerid)
{
	new
		string[128],
		Float:x,
		Float:y,
		Float:z,
		MapZone:zone,
		zone_name[MAX_MAP_ZONE_NAME]
	;

	MEGAString[0] = EOS;
	
	strcat(MEGAString, "ID\tCapacidade\tLocal\tDistância\n");

	strcat(MEGAString, "{00FF00}» Localizar a lixeira mais próxima\n");

	foreach(new id : IterTrash)
	{
		GetDynamicObjectPos(trashInfo[id][trashObject], x, y, z);

		zone = GetMapZoneAtPoint2D(x, y);
		GetMapZoneName(zone, zone_name);
		
		format(string, sizeof string, "{FFFFFF}Lixeira %d\t{00F0FF}%d/%d\t{9C9C9C}%s\t%.0f Metros\n", id, TrashCan_CountItems(id), MAX_TRASH_ITENS,
		zone_name, GetPlayerDistanceFromPoint(playerid, trashInfo[id][trashPos][0], trashInfo[id][trashPos][1], trashInfo[id][trashPos][2]));
		
		strcat(MEGAString, string);
	}
	ShowPlayerDialog(playerid, 4267, DIALOG_STYLE_TABLIST_HEADERS, "GPS » Lixeiras", MEGAString, "Localizar", "Retornar");
	
	return true;
}

// Buscar a lixeira á frente do jogador:
stock TrashCan_Get(playerid)
{
	new Float: trashDist 	= 999999.0,
		trashID				= -1;

	foreach(new id : IterTrash)
	{
	    if (GetPlayerInterior(playerid) != trashInfo[id][trashInterior] || 
			GetPlayerVirtualWorld(playerid) != trashInfo[id][trashWorld]) continue;

		new Float:objectDistance = GetPlayerDistanceFromPoint(playerid, trashInfo[id][trashPos][0], trashInfo[id][trashPos][1], trashInfo[id][trashPos][2]);

		if (objectDistance > 1.5) 
			continue;

		if (objectDistance < trashDist) {
		    trashDist		= objectDistance;
		    trashID			= id;
		}
	}
	return trashID;
}

// Buscar a lixeira mais próxima:
stock TrashCan_GetTheClosest(playerid)
{
	new Float: trashDist 	= 999999.0,
		trashID				= -1;

	foreach(new id : IterTrash)
	{
		new Float:objectDistance = GetPlayerDistanceFromPoint(playerid, trashInfo[id][trashPos][0], trashInfo[id][trashPos][1], trashInfo[id][trashPos][2]);

		if (objectDistance < trashDist)
		{
		    trashDist		= objectDistance;
		    trashID			= id;
		}
	}
	return trashID;
}

stock SetPlayerLixeira(playerid)
{
	if (GetPVarInt(playerid, "playerInTrashCan"))
	{
	    new trashID = GetPVarInt(playerid, "playerTrashCanID");
	    
 		SetPlayerPos(playerid, trashInfo[trashID][trashPos][0], trashInfo[trashID][trashPos][1], trashInfo[trashID][trashPos][2] + 1.0);
 		
   		SetPVarInt(playerid, "playerTrashCanID", -1), SetPVarInt(playerid, "playerInTrashCan", 0);
   		
   		TogglePlayerControllable(playerid, true), SetCameraBehindPlayer(playerid);
   		
	    SendClientMessage(playerid, 0xE0B062FF, "Você saiu da lixeira.");
	    
	    ShowNick(playerid), Sound(playerid, 12601, 20.0);
	    
	    return true;
	}
	
	new idTrashCan = TrashCan_Get(playerid);

	if (idTrashCan == -1) return SendClientMessage(playerid, -1, "Você não está próximo de uma lixeira.");

    if (playerItIsTrashCan(idTrashCan) && !GetPVarInt(playerid, "playerInTrashCan"))
	{
		SendClientMessage(playerid, 0xE0B062FF, "Você removeu alguém que estava na lixeira.");
		removePlayerTrashCan(idTrashCan);
 		return true;
	}

	SetPVarInt(playerid, "playerInTrashCan", 1), SetPVarInt(playerid, "playerTrashCanID", idTrashCan);

	TogglePlayerControllable(playerid, false);
	
	SetPlayerPos(playerid, trashInfo[idTrashCan][trashPos][0], trashInfo[idTrashCan][trashPos][1], trashInfo[idTrashCan][trashPos][2] - 1.8);

	InterpolateCameraPos(playerid, trashInfo[idTrashCan][trashPos][0], trashInfo[idTrashCan][trashPos][1], trashInfo[idTrashCan][trashPos][2] + 1.0,
	trashInfo[idTrashCan][trashPos][0], trashInfo[idTrashCan][trashPos][1], trashInfo[idTrashCan][trashPos][2] + 1.0, 10000);

	InterpolateCameraLookAt(playerid, trashInfo[idTrashCan][trashPos][0], trashInfo[idTrashCan][trashPos][1], trashInfo[idTrashCan][trashPos][2] + 1.0,
	trashInfo[idTrashCan][trashPos][0], trashInfo[idTrashCan][trashPos][1] + 3, trashInfo[idTrashCan][trashPos][2], 10000);

	if(IsAndroidPlayer(playerid))
 		SendClientMessage(playerid, 0xE0B062FF, "Para sair da lixeira aperte 'F', para mudar o ângulo de visão aperte 'Y'.");
	else
		SendClientMessage(playerid, 0xE0B062FF, "Para sair da lixeira aperte 'F', para mudar o ângulo de visão aperte 'ESPAÇO'.");

	Sound(playerid, 12601, 20.0), HideNick(playerid), UpdateAngleLixeira(playerid);

	return true;
}

stock static playerItIsTrashCan(lixeiraid)
{
	foreach(new playerid : Player)
	{
	    if (GetPVarInt(playerid, "playerTrashCanID") == lixeiraid) return true;
	}
	return false;
}

stock removePlayerTrashCan(lixeiraid)
{
	foreach(new playerid : Player)
	{
	    if (GetPVarInt(playerid, "playerTrashCanID") == lixeiraid)
		{
	        SetPlayerPos(playerid, trashInfo[lixeiraid][trashPos][0], trashInfo[lixeiraid][trashPos][1], trashInfo[lixeiraid][trashPos][2] + 1.0);
	        
            SetPVarInt(playerid, "playerTrashCanID", -1), SetPVarInt(playerid, "playerInTrashCan", 0);
            
            TogglePlayerControllable(playerid, true), SetCameraBehindPlayer(playerid);

            SendClientMessage(playerid, 0xE0B062FF, "Você foi retirado dessa lixeira.");

            Sound(playerid, 12601, 20.0), ShowNick(playerid);
		}
	}
}

hook OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if (response == 1 || response == 0) {
		if (Trash_CancelEdit(objectid, x, y, z, rx, ry, rz))
			SendClientMessage(playerid, -1, "A edição do objeto foi finalizada.");
	}
	return 1;
}

stock createServerLixeira(playerid, modelid = 1343)
{
	new Float:x,
		Float:y,
		Float:z,
		Float:a;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	new id = createLixeira(modelid, x, y, z, a, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

	if (id != -1)
	{
	    Inventory_HideForPlayer(playerid);

	    EditDynamicObject(playerid, trashInfo[id][trashObject]);
	}
	return id;
}

stock createLixeira(modelid, Float:x, Float:y, Float:z, Float:a, interior = 0, world = 0)
{
	new id = Iter_Free(IterTrash);
	new string[128];
	
	if (id != -1)
	{
	    Iter_Add(IterTrash, id);
	    
	    trashInfo[id][trashPos][0]			= x;
	    trashInfo[id][trashPos][1]			= y;
	    trashInfo[id][trashPos][2]			= z;
	    trashInfo[id][trashPos][3]			= a;
	    
	    trashInfo[id][trashModel]			= modelid;
        trashInfo[id][trashWorld]			= world;
        trashInfo[id][trashInterior]		= interior;
        
        trashInfo[id][trashObject]			= CreateDynamicObject(modelid, x, y, z, 0.0, 0.0, a, world, interior);
        trashInfo[id][lixeiraLabel]			= CreateDynamic3DTextLabel("_", 0x92C688AA, x, y, z, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world, interior);
        
		mysql_format(MySQL_Handle, string, sizeof(string), "INSERT INTO `lixeiras` (`id`, `infos`) VALUE ('%d', '%f|%f|%f|%f|%d|%d|%d')", id, x, y, z, a, modelid, world, interior);
		mysql_tquery(MySQL_Handle, string);
		
		TrashCan_UpdateText(id);
	}
	return id;
}

hook PayDay() {
	foreach(new id : IterTrash)
	{
		new rdn = random(67);
		switch (rdn)
		{
		    case 0..13: TrashCan_GiveItem(id, ITEM_TYPE_COMIDA, ITEM_MODEL_CARNE, 0, 0, 1, "Carne Frita");
		    case 14..24: TrashCan_GiveItem(id, ITEM_TYPE_COMIDA, ITEM_MODEL_PAO, 0, 0, 4, "Fatia de Pao");
		    case 25..36: TrashCan_GiveItem(id, ITEM_TYPE_COMIDA, ITEM_MODEL_FRANGO, 0, 0, 1, "Coxa de Frango");
		    case 50..55: TrashCan_GiveItem(id, ITEM_TYPE_RESPEITO, 19941, 0, 0, random(3) + 1, "Respeitos");
		    case 56..64: TrashCan_GiveItem(id, ITEM_TYPE_COMIDA, ITEM_MODEL_PIZZA, 0, 0, 2, "Fatia de Pizza");
		    default: TrashCan_GiveItem(id, ITEM_TYPE_DINHEIRO, 1212, 0, 0, random(100) + 50, "Dinheiro");
  		}
		TrashCan_UpdateText(id);
 	}
}

stock destroyTrashCan(id)
{
    new string[165];

	if (Iter_Contains(IterTrash, id))
	{
	    Iter_Remove(IterTrash, id);
	    
	    DestroyDynamicObject(trashInfo[id][trashObject]);
	    DestroyDynamic3DTextLabel(trashInfo[id][lixeiraLabel]);
	    
	    mysql_format(MySQL_Handle, string, sizeof (string), "DELETE FROM `lixeiras` WHERE `id` = '%d'", id), mysql_tquery(MySQL_Handle, string);

	    return true;
	}
	return false;
}

stock TrashCan_UpdateText(id)
{
	new string[95];

	format(string, sizeof string,"\nLixeira\n{C8C8C8}Aperte a letra {FFF000}Y {C8C8C8}para usar\nCapacidade {00F0FF}%d/%d", TrashCan_CountItems(id), MAX_TRASH_ITENS);
	UpdateDynamic3DTextLabelText(trashInfo[id][lixeiraLabel], 0x92C688AA, string);

	return true;
}

stock TrashCan_Save(id)
{
	if (Iter_Contains(IterTrash, id))
	{
		SetDynamicObjectPos(trashInfo[id][trashObject], trashInfo[id][trashPos][0], trashInfo[id][trashPos][1], trashInfo[id][trashPos][2]);
		SetDynamicObjectRot(trashInfo[id][trashObject], 0.0, 0.0, trashInfo[id][trashPos][3]);
	
		new string[200];

		DestroyDynamic3DTextLabel(trashInfo[id][lixeiraLabel]);
		
		format(string, sizeof string,"\nLixeira\n{C8C8C8}Aperte a letra {FFF000}Y {C8C8C8}para usar\nCapacidade {00F0FF}%d/%d", TrashCan_CountItems(id), MAX_TRASH_ITENS);
        trashInfo[id][lixeiraLabel] = CreateDynamic3DTextLabel(string, 0x92C688AA, trashInfo[id][trashPos][0], trashInfo[id][trashPos][1], trashInfo[id][trashPos][2] + 0.4, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, trashInfo[id][trashWorld], trashInfo[id][trashInterior]);

		mysql_format(MySQL_Handle, string, sizeof (string), "UPDATE `lixeiras` SET `infos` = '%f|%f|%f|%f|%d|%d|%d' WHERE `id` = '%d'", trashInfo[id][trashPos][0], trashInfo[id][trashPos][1],
		trashInfo[id][trashPos][2], trashInfo[id][trashPos][3], trashInfo[id][trashModel], trashInfo[id][trashWorld], trashInfo[id][trashInterior], id);
		mysql_tquery(MySQL_Handle, string);

		return true;
	}
	return false;
}

stock TrashCan_CountItems(trashcan)
{
	new count;
	if (Iter_Contains(IterTrash, trashcan))
		for (new slot; slot < MAX_TRASH_ITENS; slot++) if (TrashCanItem_GetValid(trashcan, slot)) count ++;
	
	return count;
}

stock loadLixeiras()
{
    new rows;

	mysql_query(MySQL_Handle, "SELECT * FROM lixeiras ORDER BY `id` ASC LIMIT 20");
	cache_get_row_count(rows);
	
	if(rows > 0)
	    for(new i = 0; i < rows; i++)
			onLoadServerLixeiras(i);
	
	
	printf("[LIXEIRAS]: %d lixeiras foram carregadas...", Iter_Count(IterTrash));
}

CALLBACK: onLoadServerLixeiras(row)
{

	inline const OnLoadTrashCans() {
		new nivel,
            group,
            function[54];

		MySQL_BindResultInt(stmt_selectTrashCans, 0, nivel);
		MySQL_BindResultInt(stmt_selectTrashCans, 1, group);
		MySQL_BindResult(stmt_selectTrashCans, 2, function);

		while (MySQL_Statement_FetchRow(stmt_selectTrashCans)) {
            // TrashCanItem_SetValid(trashcan, slot, false);
			// TrashCanItem_SetType(trashcan, slot, 0);
			// TrashCanItem_SetModel(trashcan, slot, 0);
			// TrashCanItem_SetQuantity(trashcan, slot, 0);
			// TrashCanItem_SetColor1(trashcan, slot, 0);
			// TrashCanItem_SetColor2(trashcan, slot, 0);
			// TrashCanItem_SetName(trashcan, slot, "Nenhum");

			TrashCan_SetPosX(trash, posX);
			TrashCan_SetPosY(trash, posY);
			TrashCan_SetPosZ(trash, posZ);
			TrashCan_SetRot(trash, rot);
			TrashCan_SetModel(trash, model);
			TrashCan_SetWorld(trash, world);
			TrashCan_SetInterior(trash, interior);

			Iter_Add(IterTrash, trash);
        }
	}
	MySQL_BindInt(stmt_selectTrashCans, 0, Player_GetAccountID(playerid));
	MySQL_ExecuteParallel_Inline(stmt_selectTrashCans, using inline OnLoadTrashCans);

	for (new itens; itens != MAX_TRASH_ITENS; itens++)
	{
  		format(string, sizeof string, "item_%d", itens);
		cache_get_value_name(row, string, lixeira_string);

		split(lixeira_string, lixeira_read, '|');

	    trashItens[id][itens][item_valid] 			= strval(lixeira_read[0]);
		trashItens[id][itens][item_type] 			= strval(lixeira_read[1]);
		trashItens[id][itens][item_model] 			= strval(lixeira_read[2]);
		trashItens[id][itens][item_cor1] 			= strval(lixeira_read[3]);
		trashItens[id][itens][item_cor2] 			= strval(lixeira_read[4]);
		trashItens[id][itens][item_quantia] 		= strval(lixeira_read[5]);
		format(trashItens[id][itens][item_nome], 30, lixeira_read[6]);
	}
	
	trashInfo[id][trashObject] = CreateDynamicObject(trashInfo[id][trashModel], trashInfo[id][trashPos][0], trashInfo[id][trashPos][1], trashInfo[id][trashPos][2], 0.0, 0.0, trashInfo[id][trashPos][3], trashInfo[id][trashWorld], trashInfo[id][trashInterior]);

	format(lixeira_string, sizeof lixeira_string,"\nLixeira\n{C8C8C8}Aperte a letra {FFF000}Y {C8C8C8}para usar\nCapacidade {00F0FF}%d/%d", TrashCan_CountItems(id), MAX_TRASH_ITENS);
	trashInfo[id][lixeiraLabel] = CreateDynamic3DTextLabel(lixeira_string, 0x92C688AA, trashInfo[id][trashPos][0], trashInfo[id][trashPos][1], trashInfo[id][trashPos][2] + 0.4, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, trashInfo[id][trashWorld], trashInfo[id][trashInterior]);
}