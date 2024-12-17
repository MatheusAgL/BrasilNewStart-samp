
#define _SYSTEM_TRASH_CAN true

#include <YSI_Coding\y_hooks>

#define 		MAX_TRASH					(20)
#define 		MAX_TRASH_ITENS				(20)

enum TrashEnum
{
	Float: trashPos[4],
	
	trashModel,
	trashWorld,
	trashInterior,
	trashObject,
	trashTime[MAX_PLAYERS],
	Text3D:lixeiraLabel,
}

new trashInfo[MAX_TRASH][TrashEnum];
new trashItens[MAX_TRASH][MAX_TRASH_ITENS][INVENTORY_ENUM];
new Iterator:IterTrash<MAX_TRASH>;

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

hook OnPlayerEnterDynamicArea(playerid, areaid)
{
	checkLixoArea(playerid, areaid);
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

stock TrashCan_CountItems(id)
{
	if (Iter_Contains(IterTrash, id))
	{
		new count;
		
		for (new itens = 0; itens < MAX_TRASH_ITENS; itens++)
		{
		    if (trashItens[id][itens][item_valid])
				count ++;
		}
		return count;
	}
	return false;
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
    new lixeira_read[7][25];
	new lixeira_string[228];
	new string[128];
	
	new id;
	cache_get_value_int(row, "id", id);

   	Iter_Add(IterTrash, id);

	cache_get_value_name(row, "infos", lixeira_string);
	split(lixeira_string, lixeira_read, '|');

	trashInfo[id][trashPos][0] 			= floatstr(lixeira_read[0]);
	trashInfo[id][trashPos][1] 			= floatstr(lixeira_read[1]);
	trashInfo[id][trashPos][2] 			= floatstr(lixeira_read[2]);
	trashInfo[id][trashPos][3] 			= floatstr(lixeira_read[3]);
	trashInfo[id][trashModel] 			= strval(lixeira_read[4]);
	trashInfo[id][trashWorld] 			= strval(lixeira_read[5]);
	trashInfo[id][trashInterior] 		= strval(lixeira_read[6]);

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

CMD:lixeira(playerid, params[])
{
    if (Dev_GetNivel(playerid) < DEV_ALPHA)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (isnull(params))
	{
	    SendClientMessage(playerid, -1, "Modo de uso: /lixeira (nome | lista abaixo)");
	    return SendClientMessage(playerid, -1, "Nomes disponíveis: Ir | Criar | Destruir | Limpar");
	}
	
	new string[128], null[25];
	
	if (strfind(params, "destruir", true) != -1)
	{
	    new trashID;
		if (sscanf(params, "s[25]d", null, trashID)) return SendClientMessage(playerid, -1, "Modo de uso: /lixeira destruir (id da lixeira)");

		if (trashID < 0 || trashID >= MAX_TRASH)
		{
		    format(string, sizeof string, "O ID das lixeiras está entre 0 á %d.", MAX_TRASH - 1);
		    return SendClientMessage(playerid, -1, string);
		}

		destroyTrashCan(trashID);

		format(string, sizeof string, "(Conselho): %s, %s destruiu a Lixeira - ID: %d.", Staff_GetPositionName(playerid), PlayerName[playerid], trashID);
		Staff_ChatToAll(0x97D0CFAA, string), server_log("lixeiras", string);
	}
	
	else if (strfind(params, "ir", true) != -1)
	{
        new trashID;
		if (sscanf(params, "s[25]d", null, trashID)) return SendClientMessage(playerid, -1, "Modo de uso: /lixeira ir (id da lixeira)");

		if (trashID < 0 || trashID >= MAX_TRASH)
		{
		    format(string, sizeof string, "O ID das lixeiras está entre 0 á %d.", MAX_TRASH - 1);
		    return SendClientMessage(playerid, -1, string);
		}

		SetPlayerInterior(playerid, trashInfo[trashID][trashInterior]);
		SetPlayerVirtualWorld(playerid, trashInfo[trashID][trashWorld]);

		SetPlayerPos(playerid, trashInfo[trashID][trashPos][0], trashInfo[trashID][trashPos][1], trashInfo[trashID][trashPos][2]);

		format(string, sizeof string, "Você foi teleportado até a Lixeira [ID: %d].", trashID);
	 	SendClientMessage(playerid, 0x97D0CFAA, string);
	}

	else if (!strcmp(params, "criar", true))
	{
        new trashID = createServerLixeira(playerid);

		if (trashID == -1) return SendClientMessage(playerid, -1, "O máximo de lixeiras no servidor é 20..."), false;

        format(string, sizeof string, "(Conselho): %s, %s criou uma Lixeira - ID: %d.", Staff_GetPositionName(playerid), PlayerName[playerid], trashID);
		Staff_ChatToAll(0x97D0CFAA, string), server_log("lixeiras", string);
	}

	else if (strfind(params, "limpar", true) != -1)
	{
	    new trashID, trash_string[228];
		if (sscanf(params, "s[25]d", null, trashID)) return SendClientMessage(playerid, -1, "Modo de uso: /lixeira limpar (id da lixeira)");
	
		for (new itens; itens != MAX_TRASH_ITENS; itens++)
		{
	    	trashItens[trashID][itens][item_valid]		= 0;
	    	trashItens[trashID][itens][item_type] 		= 0;
	    	trashItens[trashID][itens][item_model] 		= 0;
	    	trashItens[trashID][itens][item_cor1] 		= 0;
	    	trashItens[trashID][itens][item_cor2] 		= 0;
	    	trashItens[trashID][itens][item_quantia] 	= 0;
	    	format(trashItens[trashID][itens][item_nome], 75, "Nenhum");

	    	mysql_format(MySQL_Handle, trash_string, sizeof (trash_string), "UPDATE `lixeiras` SET `item_%d` = '0|0|0|0|0|0|Nenhum' WHERE `id` = '%d'", itens, trashID);
		    mysql_tquery(MySQL_Handle, trash_string);
		}
		TrashCan_UpdateText(trashID);
	}
	else
	{
	    SendClientMessage(playerid, -1, "Nomes disponíveis: Ajuda | Localizar");
	    if (Admin_GetNivel(playerid) > DONO) SendClientMessage(playerid, -1, "Administração: Ir | Criar | Destruir | Limpar");
	}
	return true;
}

stock TrashCan_Get(playerid)
{
	new Float: trashDist 	= 999999.0,
		trashID				= -1;

	foreach(new id : IterTrash)
	{
	    if (GetPlayerInterior(playerid) != trashInfo[id][trashInterior] || GetPlayerVirtualWorld(playerid) != trashInfo[id][trashWorld]) continue;

		new Float:objectDistance = GetPlayerDistanceFromPoint(playerid, trashInfo[id][trashPos][0], trashInfo[id][trashPos][1], trashInfo[id][trashPos][2]);

		if (objectDistance > 1.5000) continue;

		if (objectDistance < trashDist)
		{
		    trashDist		= objectDistance;
		    trashID			= id;
		}
	}
	return trashID;
}

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

stock HideNick(playerid)
{
	foreach(new i : Player)
	{
		ShowPlayerNameTagForPlayer(i, playerid, false);
	}
}

stock ShowNick(playerid)
{
 	foreach(new i : Player)
	{
		ShowPlayerNameTagForPlayer(i, playerid, true);
	}
}

stock UpdateAngleLixeira(playerid)
{
	new Float:angle, Float:pos[3];
	GetPlayerFacingAngle(playerid, angle);
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

    GetXYInFrontOfPlayer(playerid, pos[0], pos[1], 3.0);

    new idTrashCan = GetPVarInt(playerid, "playerTrashCanID");

    SetPlayerFacingAngle(playerid, angle + 20);

	InterpolateCameraPos(playerid, trashInfo[idTrashCan][trashPos][0], trashInfo[idTrashCan][trashPos][1], trashInfo[idTrashCan][trashPos][2] + 1.0,
	trashInfo[idTrashCan][trashPos][0], trashInfo[idTrashCan][trashPos][1], trashInfo[idTrashCan][trashPos][2] + 0.99, 10000, CAMERA_MOVE);

	InterpolateCameraLookAt(playerid, trashInfo[idTrashCan][trashPos][0], trashInfo[idTrashCan][trashPos][1], trashInfo[idTrashCan][trashPos][2] + 1.0,
	pos[0], pos[1], trashInfo[idTrashCan][trashPos][2], 1000, CAMERA_MOVE);
}

stock TrashCan_ShowDialog(playerid)
{
	ShowPlayerDialog(playerid, 4264, DIALOG_STYLE_TABLIST, "Escolha uma opção",
	"{FFFFFF}Se esconder\t{9C9C9C}Você se esconde na lixeira\n\
	{FFFFFF}Descartar item\t{9C9C9C}Jogar item do inventário no lixo\n\
	{FFFFFF}Descartar lixos\t{9C9C9C}Jogar todos os lixos do inventário na lixeira\n\
	{FFFFFF}Revirar lixo\t{9C9C9C}Você pode encontrar algum item\n\
	{FFFFFF}Ensacar lixos\t{9C9C9C}Área disponível para lixeiros", "Prosseguir", "Cancelar");

	return 1;
}

stock TrashCan_DiscardItems(playerid)
{
  	MEGAString[0] = EOS;

    new string[128];

    strcat(MEGAString, "Nome do item\tQuantidade\n");

    for (new item; item != MAX_ITENS_INVENTARIO; item++)
	{
		if (InventarioInfo[playerid][item][item_valid]) {
			format(string, sizeof (string), "%s\t%d\n", InventarioInfo[playerid][item][item_nome], InvItem_GetQuantity(playerid, item));
		} else {
			format(string, sizeof (string), "{AAAAAA}Nenhum\n");
		}
     	strcat(MEGAString, string);
	}
	ShowPlayerDialog(playerid, 4265, DIALOG_STYLE_TABLIST_HEADERS, "Selecione o item que quer jogar fora", MEGAString, "Descartar", "Retornar");

	return 1;
}

stock TrashCan_GiveItem(lixeiraid, type, model, cor1, cor2, quantia, const nome[])
{
	if(lixeiraid == -1)
		return false;

    new trash_string[228];

	for (new itens; itens != MAX_TRASH_ITENS; itens++)
	{
	    if (!trashItens[lixeiraid][itens][item_valid])
		{
	    	trashItens[lixeiraid][itens][item_valid] = 1;

	    	trashItens[lixeiraid][itens][item_type] = type;
	    	trashItens[lixeiraid][itens][item_model] = model;
	    	trashItens[lixeiraid][itens][item_cor1] = cor1;
	    	trashItens[lixeiraid][itens][item_cor2] = cor2;
	    	trashItens[lixeiraid][itens][item_quantia] = quantia;
	    	format(trashItens[lixeiraid][itens][item_nome], 75, nome);
	    	
	    	mysql_format(MySQL_Handle, trash_string, sizeof (trash_string), "UPDATE `lixeiras` SET `item_%d` = '1|%d|%d|%d|%d|%d|%e' WHERE `id` = '%d'", itens, type, model, cor1, cor2, quantia, nome, lixeiraid);
		    mysql_tquery(MySQL_Handle, trash_string);

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

stock TrashCan_RemoveItem(id, itemid)
{
    new trash_string[228];

	if (trashItens[id][itemid][item_valid])
	{
	    trashItens[id][itemid][item_valid] = 0;

	    mysql_format(MySQL_Handle, trash_string, sizeof (trash_string), "UPDATE `lixeiras` SET `item_%d` = '0|0|0|0|0|0|Nenhum' WHERE `id` = '%d'", itemid, id);
	    mysql_tquery(MySQL_Handle, trash_string);

	    TrashCan_UpdateText(id);

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

new Text3D:lixo_Text [MAX_VEHICLES] = {Text3D:-1, ...};
new lixo_Area        [MAX_VEHICLES] = {-1, ...};
new lixo_Ammount     [MAX_VEHICLES] = {0, ...};

stock createCaminhaoLixo(vehicleid)
{
	lixo_Area[vehicleid] = CreateDynamicSphere(0.0, -4.0, 0.0, 4.0);
	lixo_Text[vehicleid] = CreateDynamic3DTextLabel("Capacidade: 0%", 0xFFFFFFF2, 0.0, 0.0, 0.0, 10.0, INVALID_PLAYER_ID, vehicleid);

	AttachDynamicAreaToVehicle(lixo_Area[vehicleid], vehicleid);

	new baseObject = CreateDynamicObject(19443, 0.02261, -3.95623, -0.41958,   0.00000, 90.00000, 0.00000);
	SetDynamicObjectMaterialText(baseObject, 0, " ");
	AttachDynamicObjectToVehicle(baseObject, vehicleid, 0.02261, -3.95623, -0.41958,   0.00000, 90.00000, 0.00000);
}

CMD:iniciarcoleta(playerid)
{
    if (!PlayerIsGari(playerid)) 
		return SendClientMessage(playerid, -1, "Você não é um gari.");

	new vehicleid = GetPlayerVehicleID(playerid);
    if (!IsPlayerInAnyVehicle(playerid) || GetVehicleModel(vehicleid) != 408) 
		return SendClientMessage(playerid, -1, "Você não está em um caminhão de lixo.");

	new count;
	foreach(new id : IterTrash) {
	    if (TrashCan_CountItems(id) > 0) {
			count++;
			break;
		}
	}
	
	if (count < 1)
		SendClientMessage(playerid, -1, "A cidade está limpa, sem lixos!");

	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você iniciou uma coleta, use o comando /gps e veja quais lixeiras tem lixos.");
	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Quando o caminhão estiver cheio, volte para a HQ e digite /entregarcoleta para esvaziar o caminhão!");

	new string[95];
	
	SetPVarInt(playerid, "emColetaLixo", 1);
	
	format(string, sizeof string, "((Rádio Lixeiro)) "C_WHITE"%s iniciou a rota de coleta.", PlayerName[playerid]);
	EmpregoMensagem(0x5AD794FF, string, 26);
	
	return 1;
}

CMD:cancelarcoleta(playerid)
{
    if (!PlayerIsGari(playerid)) return SendClientMessage(playerid, -1, "Você não é um gari.");

	RemovePlayerAttachedObject(playerid, Slot_Pizza);
	SetPVarInt(playerid, "pegouLixo", 0), SetPVarInt(playerid, "quantLixosPegou", 0), SetPVarInt(playerid, "emColetaLixo", 0);

	SendClientMessage(playerid, COLOR_LIGHTRED, "Você cancelou a coleta de lixo.");
	
	return true;
}

CMD:entregarcoleta(playerid)
{
    if (!PlayerIsGari(playerid)) return SendClientMessage(playerid, -1, "Você não é um gari.");

    if (!IsPlayerInRangeOfPoint(playerid, 50.0, 2136.3916,-1989.0623,14.7006)) return SendClientMessage(playerid, -1, "Você precisa estar no lixão.");

    new vehicleid = GetPlayerVehicleID(playerid);

    if (!IsALixeiroCar(vehicleid)) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está em um caminhão de lixo!");

	if (lixo_Ammount[vehicleid] > 0)
	{
	    new string[144];

	    new cost = lixo_Ammount[vehicleid] * GetWageJob(ID_JOB_LIXEIRO);

	    SetPVarInt(playerid, "emColetaLixo", 0);
		
		format(string, sizeof string, "((Rádio Lixeiro)) {FFFFFF}%s entregou %dKGs de lixo e foi adicionado $%s no salário.", PlayerName[playerid], lixo_Ammount[vehicleid], getFormatText(cost));
		EmpregoMensagem(0x5AD794FF, string, 26);

        format(string, sizeof string, "* Você entregou %dKG de lixo, foi adicionado ao seu salário +$%s, você receberá no payday!", lixo_Ammount[vehicleid], getFormatText(cost));
	    SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

	    PlayerInfo[playerid][pSalario] += cost;
		removerDinheiroGoverno(cost);

	    lixo_Ammount[vehicleid] = 0;
	    
	    format(string, sizeof string, "Capacidade: %dkg / 100kg", lixo_Ammount[vehicleid]);
		UpdateDynamic3DTextLabelText(lixo_Text[vehicleid], 0xFFFFFFF2, string);

	} else {
	    SendClientMessage(playerid, COLOR_LIGHTRED, "* Este veículo não tem lixos para entregar!");
	}

	return 1;
}

stock lixoAddCar(playerid, vehicleid)
{
	new string[45];

	lixo_Ammount[vehicleid] += GetPVarInt(playerid, "quantLixosPegou") * 2;

	if (lixo_Ammount[vehicleid] >= 100) lixo_Ammount[vehicleid] = 100;
	
	SetPVarInt(playerid, "quantLixosPegou", 0);

	format(string, sizeof string, "Capacidade: %dkg / 100kg", lixo_Ammount[vehicleid]);
	UpdateDynamic3DTextLabelText(lixo_Text[vehicleid], 0xFFFFFFF2, string);
}

stock checkLixoArea(playerid, areaid)
{
	if (!PlayerIsGari(playerid)) return false;

    if (!GetPVarInt(playerid, "pegouLixo")) return false;

	for(new caminhoes; caminhoes != MAX_VEHICLES; caminhoes++)
	{
	    if (areaid == lixo_Area[caminhoes])
		{
			if (lixo_Ammount[caminhoes] >= 100)
			{
				RemovePlayerAttachedObject(playerid, Slot_Pizza);
				SetPVarInt(playerid, "pegouLixo", 0), SetPVarInt(playerid, "quantLixosPegou", 0), SetPVarInt(playerid, "emColetaLixo", 0);

				return SendClientMessage(playerid, COLOR_LIGHTRED, "O caminhão está cheio, volte ao Lixão para entregar o lixo.");
			}

            lixoAddCar(playerid, caminhoes);

			RemovePlayerAttachedObject(playerid, Slot_Pizza);
   			SetPVarInt(playerid, "pegouLixo", 0);

			break;
	    }
	}
	return 1;
}

stock Trash_CancelEdit(objectid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	#pragma unused rx, ry

	foreach(new id : IterTrash) {
		if (objectid == trashInfo[id][trashObject]) {
			trashInfo[id][trashPos][0] = x;
			trashInfo[id][trashPos][1] = y;
			trashInfo[id][trashPos][2] = z;
			trashInfo[id][trashPos][3] = rz;

			TrashCan_UpdateText(id);
			TrashCan_Save(id);

			return 1;
		}
	}
	return 0;
}