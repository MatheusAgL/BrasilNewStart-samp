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