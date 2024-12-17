

		/*____________________________________________________________________________________________________________________________________________

						 ___________   _________     ________
						|    ___   \  |    __   \  /         \          Brasil Play Start ®
						|   |___/  |  |   |__|  | |    ______/              Fundação: Theus_Crazzy
						|   ______/   |    _____/ |   |______                   Data: 22/02/2016
						|         \   |   /       \          \                      Modulo: Portão
						|    ____  |  |   |        \_____    /
						|   |___/  |  |   |        /         \                              Theus_Crazzy (Desenvolvedor do módulo)
						|_________/   |___|        \_________/                                  Descrição: Sistema de portão/muros/grades


		____________________________________________________________________________________________________________________________________________*/


// Includes necessárias
#include < YSI_Coding\y_hooks >

#define _SYSTEM_PORTAO true

#define 			MAX_PORTAO              1500

enum PortaoEnum
{
	Float: portaoPos[3],
	Float: portaoRot[3],
	Text3D: portaoText,
	
	portaoModel,
	portaoObject,
	portaoSenha[128],
	portaoName[40],
	portaoFamily,
	portaoFamilyDB,
	portaoVencimento,
	portaoNick[MAX_PLAYER_NAME + 1],
};

new PortaoInfo[MAX_PORTAO][PortaoEnum];
new Iterator:IterWall<MAX_PORTAO>;

stock createPortao(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, itemName[], nick[], senhaportao[] = "123")
{
    new id = Iter_Free(IterWall);
	new string[128];

	if (id != -1)
	{
	    Iter_Add(IterWall, id);

	    PortaoInfo[id][portaoPos][0]		= x;
	    PortaoInfo[id][portaoPos][1]		= y;
	    PortaoInfo[id][portaoPos][2]		= z;
	    
	    PortaoInfo[id][portaoRot][0]		= rx;
	    PortaoInfo[id][portaoRot][1]		= ry;
	    PortaoInfo[id][portaoRot][2]		= rz;

	    PortaoInfo[id][portaoModel]			= modelid;
	    
	    PortaoInfo[id][portaoFamily]		= -2;
		PortaoInfo[id][portaoFamilyDB]		= -2;
	    
	    format(PortaoInfo[id][portaoNick], 	MAX_PLAYER_NAME, nick);
	  	format(PortaoInfo[id][portaoSenha], 128, senhaportao);
	  	format(PortaoInfo[id][portaoName], 	40, itemName);

        PortaoInfo[id][portaoObject]		= CreateDynamicObject(modelid, x, y, z, rx, ry, rz);

		switch (modelid)
		{
        	case 980:
			{
				format(string, sizeof string, "Portão %d\nDono: %s\nUse: (/portao abrir) para abrir", id, nick);
				PortaoInfo[id][portaoText]	=	CreateDynamic3DTextLabel(string, 0x5BD0CAFF, x, y, z, 15.0);
			}
		}
	  	
	  	new query[348];

		mysql_format(MySQL_Handle, query, sizeof(query),
		"INSERT INTO `portoes` (`id`, `infos`, `senha`, `dono`, `portao_vencimento`) VALUE ('%d', '%f|%f|%f|%f|%f|%f|%d|%s|-1', '%s', '%s', TIMESTAMPADD(DAY, 7, CURRENT_TIMESTAMP()))",
		id, x, y, z, rx, ry, rz, modelid, itemName, senhaportao, nick), mysql_tquery(MySQL_Handle, query);
	}
	return id;
}

hook OnPlayerLogin(playerid) {
	new string[128];
	// Vencimento do portão
	foreach(new portoes : IterWall)
	{
		if (!strcmp(PortaoInfo[portoes][portaoNick], PlayerName[playerid])) // Possui portão
		{
			mysql_format(MySQL_Handle, string, sizeof (string), "UPDATE `portoes` SET `portao_vencimento` = TIMESTAMPADD(DAY, 7, CURRENT_TIMESTAMP()) WHERE dono = '%e'", PlayerName[playerid]);
			mysql_tquery(MySQL_Handle, string);
		}
	}
}

stock CreatePlayerPortao(playerid, modelid, nameportao[] = "Portao")
{
    if (IsPlayerInSafeZone(playerid)) 
		return SendClientMessage(playerid, -1, "Você não pode fazer isso em uma Área Segura.");

    new Float:playerPos[4], Float:x, Float:y;
	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
	GetPlayerFacingAngle(playerid, playerPos[3]);
	GetXYInFrontOfPlayer(playerid, x, y, 2.0);

    new id = createPortao(modelid, x, y, playerPos[2], 0.0, 0.0, playerPos[3], nameportao, PlayerName[playerid]);
	SetPlayerPos(playerid, playerPos[0]+0.01, playerPos[1], playerPos[2]);
    
    if (id != -1)
	{
	    Inventory_HideForPlayer(playerid);

		if(IsAndroidPlayer(playerid))
	    	OpenMenuEditorItem(playerid, id, 1);
		else
			EditDynamicObject(playerid, PortaoInfo[id][portaoObject]);
	}

	SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você colocou um portão neste local, use /portao ajuda para ver os comandos.");
	switch (modelid)
	{
	    case 980: SendClientMessage(playerid, COLOR_LIGHTBLUE, "* OBS: A senha padrão do portão é '123', você pode trocar a qualquer momento usando /portao senha.");
	}
	SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Edite a posição do portão.");

    return true;
}

CALLBACK: onServerPortoes()
{
	new cacheID, query[415], string[80],
		row_count, count = 0;

	cache_get_row_count(row_count);

    if (row_count)
	{
		for(new portoes; portoes < row_count; portoes++)
		{
			cache_get_value_name_int(portoes, "id", cacheID);

			static descricao_correio[82] = "Voce recebeu seu portao de volta, constamos que voce estava inativo no servidor.";

		    mysql_format(MySQL_Handle, query, sizeof(query),
			"INSERT INTO `mail_box` (`id`, `created_at`, `sender`, `recipient`, `item_type`, `item_model`, `item_quantia`, `item_cor1`, `item_cor2`, `item_nome`) \
			VALUES (NULL, CURRENT_TIMESTAMP(), '"SERVER_NAME"', '%d', '38', '%d', '1', '0', '0', '%e', '%e', '-1')", Player_GetAccountIDByNick(PortaoInfo[cacheID][portaoNick]), PortaoInfo[cacheID][portaoModel],
			PortaoInfo[cacheID][portaoName], descricao_correio), mysql_tquery(MySQL_Handle, query);

		    portaoDestruir(cacheID);

		    count++;
	    }
    }

    format(string, sizeof string, "[PORTÕES] O servidor deletou %d portões por inatividade 7 dias do dono.", count);
    SendClientMessageToAll(TEAM_BALLAS_COLOR, string);
}

stock updatePortao(idp)
{
    SetDynamicObjectPos(PortaoInfo[idp][portaoObject], PortaoInfo[idp][portaoPos][0], PortaoInfo[idp][portaoPos][1], PortaoInfo[idp][portaoPos][2]);
	SetDynamicObjectRot(PortaoInfo[idp][portaoObject], PortaoInfo[idp][portaoRot][0], PortaoInfo[idp][portaoRot][1], PortaoInfo[idp][portaoRot][2]);

    new string[200];

	mysql_format(MySQL_Handle, string, sizeof (string), "UPDATE `portoes` SET `infos` = '%f|%f|%f|%f|%f|%f|%d|%s|%d' WHERE `id` = '%d'", PortaoInfo[idp][portaoPos][0], PortaoInfo[idp][portaoPos][1], PortaoInfo[idp][portaoPos][2],
	PortaoInfo[idp][portaoRot][0], PortaoInfo[idp][portaoRot][1], PortaoInfo[idp][portaoRot][2], PortaoInfo[idp][portaoModel], PortaoInfo[idp][portaoName], PortaoInfo[idp][portaoFamilyDB], idp);
	mysql_tquery(MySQL_Handle, string);
	
	switch (PortaoInfo[idp][portaoModel])
	{
	    case 980:
	    {
		    DestroyDynamic3DTextLabel(PortaoInfo[idp][portaoText]);

			format(string, sizeof string, "Portão %d\nDono: %s\nUse: (/portao abrir) para abrir", idp, PortaoInfo[idp][portaoNick]);
			PortaoInfo[idp][portaoText]	= CreateDynamic3DTextLabel(string, 0x5BD0CAFF, PortaoInfo[idp][portaoPos][0], PortaoInfo[idp][portaoPos][1], PortaoInfo[idp][portaoPos][2], 15.0);
		}
	}
	return true;
}

stock GetClossestPortao(playerid)
{
	new portaoid = -1;
	new Float: distancia = 9999999.0;

	foreach(new x : IterWall)
	{
		new Float:dist = GetPlayerDistanceFromPoint(playerid, PortaoInfo[x][portaoPos][0], PortaoInfo[x][portaoPos][1], PortaoInfo[x][portaoPos][2]);

		if (dist < distancia && dist < 10.0)
		{
			distancia = dist;
			portaoid = x;
		}
	}
	return portaoid;
}

CMD:portao(playerid, const params[])
{
	if (isnull(params))
	{
	    SendClientMessage(playerid, -1, "Modo de uso: /portao (nome | lista abaixo)");
		if (Dev_GetNivel(playerid) > DEV_DELTA) SendClientMessage(playerid, -1, "Administração: ir | destruir | dono");
	    return SendClientMessage(playerid, -1, "Nomes disponíveis: abrir | senha | editar | guardar | arrombar");
	}

	new string[200], null[25];

	if (!strcmp(params, "abrir", true))
	{
        new idPortao = GetClossestPortao(playerid);
		if (idPortao == -1) 
			return true;

		if(PortaoInfo[idPortao][portaoFamily] == -1) {
			foreach(new family : IterFamily) {
				if(familyInfo[family][familyID] == PortaoInfo[idPortao][portaoFamilyDB]) {
					PortaoInfo[idPortao][portaoFamily] = family;
					break;
				}
			}
		}

		switch (PortaoInfo[idPortao][portaoModel])
		{
		    case 980:
			{
			    if (!strcmp(PlayerName[playerid], PortaoInfo[idPortao][portaoNick]) || GetPlayerFamily(playerid) == PortaoInfo[idPortao][portaoFamily])
				{
			        SendClientMessage(playerid, TEAM_BALLAS_COLOR, "Você acaba de abrir o seu portão, ele fechará em 5 segundos.");
			        portaoAbrir(idPortao);
				}
				else
				{
				    SetPVarInt(playerid, "varPortaoSenha", idPortao);
				    ShowPlayerDialog(playerid, 9784, DIALOG_STYLE_PASSWORD, "Senha do portão", "Digite a senha deste portão:", "Abrir", "Cancelar");
				}
			}
			default: return SendClientMessage(playerid, -1, "Este portão não tem a opção de abrir.");
		}
	}
	else if (!strcmp(params, "arrombar", true))
	{
		new idPortao = GetClossestPortao(playerid);

		if (idPortao == -1) return SendClientMessage(playerid, -1, "Você não está próximo á um portão.");

		if (!IsACop(playerid) && OnDuty[playerid] != 1 && GetPlayerOrg(playerid) != 8 && GetPlayerOrg(playerid) != 22) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é um policial ou não está fardado!");

	    if (GetPVarInt(playerid, "explodindop")) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você já está tentando arrombar um portão !");

		switch (PortaoInfo[idPortao][portaoModel])
		{
		    case 980:
			{
				format(string, sizeof(string), "* %s está tentando arrombar um portão", PlayerName[playerid]);
				SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Aguarde 30 segundos para arrombar o portão, saia de perto...");

				SetPVarInt(playerid, "explodindop", 1);
				SetTimerEx("ArrombarPortao", 30000, false, "ii", playerid, idPortao);
			}
			default: SendClientMessage(playerid, -1, "Não é possível arrombar esse tipo de portão.");
		}
	}
	else if (!strcmp(params, "guardar", true))
	{
	    new x = GetClossestPortao(playerid);

		if (x == -1) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está perto de um portão!");

		if (!strcmp(PlayerName[playerid], PortaoInfo[x][portaoNick]))
		{
			if (isInventoryFull(playerid))
				return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

		  	SendClientMessage(playerid, TEAM_BALLAS_COLOR, " Você guardou seu portão no inventário !");

            givePlayerItem(playerid, ITEM_TYPE_DECORACAO, PortaoInfo[x][portaoModel], 1, PortaoInfo[x][portaoName]);

			portaoDestruir(x);
		}
		else
		{
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é dono deste portão!");
		}
	}
	else if (!strcmp(params, "editar", true))
	{
		new x = GetClossestPortao(playerid);

		if (x == -1) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está perto de um portão!");

		if (!strcmp(PlayerName[playerid], PortaoInfo[x][portaoNick]))
		{
			SendClientMessage(playerid, TEAM_BALLAS_COLOR, " Você está editando este portão !");

			if(IsAndroidPlayer(playerid))
				OpenMenuEditorItem(playerid, x, 1);
			else
				EditDynamicObject(playerid, PortaoInfo[x][portaoObject]);
		}
		else
		{
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é dono deste portão!");
		}
	}
	else if (!strcmp(params, "destruir", true)) 
	{
		if (Admin_GetNivel(playerid) < MASTER) return SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando !");

		new x = GetClossestPortao(playerid);

		if (x == -1) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está perto de um portão!");

	 	SendClientMessage(playerid, TEAM_BALLAS_COLOR, " Você destruiu este portão !");

		#if defined _INC_email
			SendPlayerEmail("Staff", PortaoInfo[x][portaoNick], string);
		#else
			MESSAGE_WARNING_INACTIVE_SYSTEM;
		#endif

	 	//mysql_format(MySQL_Handle, string, sizeof(string), "INSERT INTO `celular_correio` (`para`,`tipo`,`modelo`,`quantidade`,`nome`) VALUES ('%e', '38', '%d', '1', '%s')",
		//PortaoInfo[x][portaoNick], PortaoInfo[x][portaoModel], PortaoInfo[x][portaoName]), mysql_tquery(MySQL_Handle, string, "","");

		portaoDestruir(x);

		format(string, sizeof(string), "Admin: %s destruiu o portão de %s (modelid: %d) (name: %s) (%.2f %.2f %.2f).", PlayerName[playerid], PortaoInfo[x][portaoNick], PortaoInfo[x][portaoModel], PortaoInfo[x][portaoName],
		PortaoInfo[x][portaoPos][0], PortaoInfo[x][portaoPos][1], PortaoInfo[x][portaoPos][2]);
	    Staff_ChatToAll(COLOR_LIGHTRED, string);

	    server_log("portoes", string);
	}
	else if (strfind(params, "senha", true) != -1)
	{
      	new senhaportao[128];

		if (sscanf(params, "s[25]s[128]", null, senhaportao)) return SendClientMessage(playerid, -1, "Modo de uso: /portao senha (senha do portão)");

	    new x = GetClossestPortao(playerid);

		if (x == -1) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está perto de um portão!");

		switch (PortaoInfo[x][portaoModel])
		{
		    case 980:
			{
			    if (strcmp(PlayerName[playerid], PortaoInfo[x][portaoNick])) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Este portão não pertence a você !");
			    
				format(string, sizeof string, "Você trocou a senha desse portão para: {FFFFFF}%s", senhaportao);
				SendClientMessage(playerid, COLOR_YELLOW, string);

				format(PortaoInfo[x][portaoSenha], 128, senhaportao);

				mysql_format(MySQL_Handle, string, sizeof (string), "UPDATE `portoes` SET `senha` = '%s' WHERE `id` = '%d'", senhaportao, x);
				mysql_tquery(MySQL_Handle, string);
			}
			default: SendClientMessage(playerid, -1, "Este portão não precisa de senha.");
		}
	}
	else if (strfind(params, "ir", true) != -1)
	{
     	if (Admin_GetNivel(playerid) < ESTAGIARIO) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

		new portaoid;
		if (sscanf(params, "s[25]d", null, portaoid)) return SendClientMessage(playerid, -1, "Modo de uso: /portao ir (id do portão)");

		if (portaoid < 0 || portaoid >= MAX_PORTAO) return SendClientMessage(playerid, -1, "O limite de portões é 800 (0 á 800) apenas.");

		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);

		SetPlayerPos(playerid, PortaoInfo[portaoid][portaoPos][0], PortaoInfo[portaoid][portaoPos][1] + 1.0, PortaoInfo[portaoid][portaoPos][2] + 1.0);

		format(string, sizeof string, "Você foi teleportado até o portão (ID: %d).", portaoid);
	 	SendClientMessage(playerid, 0xFFDEADFF, string);
	}
	else if (strfind(params, "dono", true) != -1)
	{
		if (Dev_GetNivel(playerid) < DEV_DELTA) 
			return SendClientMessage(playerid, -1 ,"Você não tem autorização para usar esse comando.");

      	new player[MAX_PLAYER_NAME];

		if (sscanf(params, "s[25]s[24]", null, player)) 
			return SendClientMessage(playerid, -1, "Modo de uso: /portao dono (player)");

	    new x = GetClossestPortao(playerid), id = Player_GetAccountIDByNick(player);

		if (x == -1) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está perto de um portão!");

		else if(id == -1) return SendClientMessage(playerid, -1, "Jogador inexistente.");

		format(string, sizeof(string), "Admin: %s alterou o dono do portão de %s para %s (modelid: %d) (name: %s) (%.2f %.2f %.2f).", PlayerName[playerid], PortaoInfo[x][portaoNick], player, PortaoInfo[x][portaoModel], PortaoInfo[x][portaoName],
		PortaoInfo[x][portaoPos][0], PortaoInfo[x][portaoPos][1], PortaoInfo[x][portaoPos][2]);
	    Staff_ChatToAll(COLOR_LIGHTRED, string);

	    server_log("portoes", string);

		format(PortaoInfo[x][portaoNick], MAX_PLAYER_NAME, player);
	}
	else if (strfind(params, "permissao", true) != -1)
	{
      	new familyid;
		if (sscanf(params, "s[25]d", null, familyid)) return SendClientMessage(playerid, -1, "Modo de uso: /portao permissao (id da família)");

	    new x = GetClossestPortao(playerid);
		if (x == -1) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está perto de um portão!");

		switch (PortaoInfo[x][portaoModel])
		{
		    case 980:
			{
			    if (strcmp(PlayerName[playerid], PortaoInfo[x][portaoNick])) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Este portão não pertence a você !");

				format(string, sizeof string, "Você deu permissão para a família %s, abrir o portão sem senha.", familyInfo[familyid][familyName]);
				SendClientMessage(playerid, COLOR_YELLOW, string);
				SendClientMessage(playerid, -1, "Caso queira remover a permissão, use: /portao permissao -2");

				PortaoInfo[x][portaoFamily] = familyid;
				PortaoInfo[x][portaoFamilyDB] = familyInfo[familyid][familyID];

				mysql_format(MySQL_Handle, string, sizeof (string), "UPDATE `portoes` SET `infos` = '%f|%f|%f|%f|%f|%f|%d|%s|%d' WHERE `id` = '%d'", PortaoInfo[x][portaoPos][0], PortaoInfo[x][portaoPos][1], PortaoInfo[x][portaoPos][2],
				PortaoInfo[x][portaoRot][0], PortaoInfo[x][portaoRot][1], PortaoInfo[x][portaoRot][2], PortaoInfo[x][portaoModel], PortaoInfo[x][portaoName], PortaoInfo[x][portaoFamilyDB], x);
				mysql_tquery(MySQL_Handle, string);
			}
			default: SendClientMessage(playerid, -1, "Este portão não precisa de permissão.");
		}
	}
	else
	{
	    SendClientMessage(playerid, -1, "Nomes disponíveis: abrir | senha | editar | guardar | arrombar | permissao");
	    if (Dev_GetNivel(playerid) > DEV_DELTA) SendClientMessage(playerid, -1, "Administração: ir | destruir");
	}
	return true;
}

CALLBACK: ArrombarPortao(playerid, id)
{
	new rdon = random(10);

	CreateExplosion(PortaoInfo[id][portaoPos][0], PortaoInfo[id][portaoPos][1], PortaoInfo[id][portaoPos][2], 0, 1.0);
	SetPVarInt(playerid, "explodindop", 0);

	if (rdon < 6)
	{
	    SendClientMessage(playerid, COLOR_LIGHTRED, "* O portão foi arrombado com sucesso, o mesmo fechará em 1 minuto !");

	    portaoAbrir(id, 60000);
	}
	else SendClientMessage(playerid, COLOR_LIGHTRED, "A força do explosivo não foi suficiente para arrombar o portão.");

}

stock portaoAbrir(p, tempo=5000)
{
	MoveDynamicObject(PortaoInfo[p][portaoObject], PortaoInfo[p][portaoPos][0], PortaoInfo[p][portaoPos][1], PortaoInfo[p][portaoPos][2]-10.0, 5.0, PortaoInfo[p][portaoRot][0], PortaoInfo[p][portaoRot][1], PortaoInfo[p][portaoRot][2]);

	foreach(new playerid : Player)
	{
	    if (IsPlayerInRangeOfPoint(playerid, 20.0, PortaoInfo[p][portaoPos][0], PortaoInfo[p][portaoPos][1], PortaoInfo[p][portaoPos][2]))
		{
	        PlayerPlaySound(playerid, 12201, PortaoInfo[p][portaoPos][0], PortaoInfo[p][portaoPos][1], PortaoInfo[p][portaoPos][2]);
	    }
	}
	SetTimerEx("voltarPortao", tempo, false, "i", p);
}

CALLBACK: voltarPortao(p)
{
    MoveDynamicObject(PortaoInfo[p][portaoObject], PortaoInfo[p][portaoPos][0], PortaoInfo[p][portaoPos][1], PortaoInfo[p][portaoPos][2], 5.0, PortaoInfo[p][portaoRot][0], PortaoInfo[p][portaoRot][1], PortaoInfo[p][portaoRot][2]);

	foreach(new playerid : Player)
	{
	    if (IsPlayerInRangeOfPoint(playerid, 20.0, PortaoInfo[p][portaoPos][0], PortaoInfo[p][portaoPos][1], PortaoInfo[p][portaoPos][2]))
		{
	        PlayerPlaySound(playerid, 12201, PortaoInfo[p][portaoPos][0], PortaoInfo[p][portaoPos][1], PortaoInfo[p][portaoPos][2]);
	    }
	}
	return true;
}

stock portaoDestruir(idp)
{
	new string[210];
	
	if (Iter_Contains(IterWall, idp))
	{
		Iter_Remove(IterWall, idp);
		
		DestroyDynamicObject(PortaoInfo[idp][portaoObject]);
		DestroyDynamic3DTextLabel(PortaoInfo[idp][portaoText]);

	    mysql_format(MySQL_Handle, string, sizeof string, "DELETE FROM `portoes` WHERE `id` = '%d'", idp);
		mysql_tquery(MySQL_Handle, string);
 	}
}

stock carregarPortoes()
{
    new rows;

	mysql_query(MySQL_Handle, "SELECT * FROM portoes ORDER BY `id` ASC");
	cache_get_row_count(rows);

	if (rows > 0) {
	    for(new i = 0; i < rows; i++) {
			onLoadServerPortoes(i);
		}
	}

	printf("[PORTÕES]: %d portoes foram carregados...", Iter_Count(IterWall));
}

CALLBACK: onLoadServerPortoes(row)
{
    new portao_read[9][25];
	new portao_string[228];
	new string[80];
	new id;
	cache_get_value_int(row, "id", id);

   	Iter_Add(IterWall, id);

	cache_get_value_name(row, "infos", portao_string);
	split(portao_string, portao_read, '|');

	PortaoInfo[id][portaoPos][0] 			= floatstr(portao_read[0]);
	PortaoInfo[id][portaoPos][1] 			= floatstr(portao_read[1]);
	PortaoInfo[id][portaoPos][2] 			= floatstr(portao_read[2]);
	PortaoInfo[id][portaoRot][0] 			= floatstr(portao_read[3]);
	PortaoInfo[id][portaoRot][1] 			= floatstr(portao_read[4]);
	PortaoInfo[id][portaoRot][2] 			= floatstr(portao_read[5]);
	PortaoInfo[id][portaoModel] 			= strval(portao_read[6]);
	format(PortaoInfo[id][portaoName], 		30, portao_read[7]);
	PortaoInfo[id][portaoFamilyDB] 			= strval(portao_read[8]);
	PortaoInfo[id][portaoFamily] = -1;

	cache_get_value_name(row, "senha", portao_string);
    format(PortaoInfo[id][portaoSenha], 60, portao_string);
    
    cache_get_value_name(row, "dono", portao_string);
    format(PortaoInfo[id][portaoNick], 40, portao_string);

	PortaoInfo[id][portaoObject] = CreateDynamicObject(PortaoInfo[id][portaoModel], PortaoInfo[id][portaoPos][0], PortaoInfo[id][portaoPos][1], PortaoInfo[id][portaoPos][2],
																					PortaoInfo[id][portaoRot][0], PortaoInfo[id][portaoRot][1], PortaoInfo[id][portaoRot][2]);

	switch (PortaoInfo[id][portaoModel])
	{
    	case 980:
		{
			format(string, sizeof string, "Portão %d\nDono: %s\nUse: /portao abrir para abrir", id, PortaoInfo[id][portaoNick]);
		    PortaoInfo[id][portaoText] = CreateDynamic3DTextLabel(string, 0x5BD0CAFF, PortaoInfo[id][portaoPos][0], PortaoInfo[id][portaoPos][1], PortaoInfo[id][portaoPos][2], 15.0);
		}
	}
}

stock Portao_CancelEdit(objectid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	foreach(new id : IterWall) {
		if (objectid == PortaoInfo[id][portaoObject]) {

			// Posição
			PortaoInfo[id][portaoPos][0]		= x;
			PortaoInfo[id][portaoPos][1]		= y;
			PortaoInfo[id][portaoPos][2]		= z;

			// Rotação
			PortaoInfo[id][portaoRot][0]		= rx;
			PortaoInfo[id][portaoRot][1]		= ry;
			PortaoInfo[id][portaoRot][2]		= rz;

			updatePortao(id);

			return 1;
		}
	}
	return 0;
}
