CMD:casa(playerid, const params[])
{
    if (sscanf(params, "s[128]", params)) {
	    SendClientMessage(playerid, COLOR_WHITE, "Modo de uso: /casa (nome)");
	    SendClientMessage(playerid, COLOR_GRAY, "NOMES: ajuda | comprar | vender | chave");

	    if (Admin_GetNivel(playerid) >= MASTER)
	    	SendClientMessage(playerid, COLOR_ADMIN, "NOMES: criar | destruir | ir | trazer | editar | rotacao | interior");
	    	
		return SendClientMessage(playerid, COLOR_GRAY, "_________________________________________________");
	}

	new string[128],
		null[25];

	if (!strcmp(params, "ajuda", true)) {
		Help_List(playerid, 12, "Ajuda casa");
		return 1;
	}
	else if (!strcmp(params, "comprar", true)) 
	{
		new house = House_PlayerGet(playerid);

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está proximo de uma residencia.");

		if (House_GetOwner(house)) 
			return SendClientMessage(playerid, -1, "A casa não está á venda.");

		if (IsLeaderOrg(playerid) == ID_ORG_GOVERNO && 
			Government_GetHouse() == -1) {
				
			inline D_BuyHouseGov(did, ddialogid, dresponse, dlistitem, string:dtext[])
			{
				#pragma unused did, ddialogid, dtext

				if (!dresponse)
					return 1;
					
				switch (dlistitem)
				{
					case 1: {
						new value = House_GetValue(house);

						if (House_GetValueType(house) == VALUE_TYPE_CASH)
							return SendClientMessage(playerid, -1, "O governo não pode comprar casas de cash.");

						if (OrgInfo_GetMoney(ID_ORG_GOVERNO) < value)
							return SendClientMessage(playerid, -1, "O governo não tem dinheiro suficiente para comprar essa casa.");

						Government_SetHouse(house);
						removerDinheiroGoverno(value);
						ScreenStart_HouseBuy(playerid, house);

						new MapZone:zone = GetMapZoneAtPoint2D(House_GetEntryX(house), House_GetEntryY(house));
						new zone_name[MAX_MAP_ZONE_NAME];
						GetMapZoneName(zone, zone_name);

						SendMsgF(playerid, COLOR_ORANGE, "<< Casas >> Você comprou a casa em %s por %s%s{FFA500}, para o governo, abras as inscrições!.", zone_name, House_ValueType(house), getFormatText(value));
						SendClientMessage(playerid, COLOR_ORANGE, "<< Casas >> Para abrir as inscrições use /menugoverno, escolha o nível máximo para se inscrever.");
						
						format(string, sizeof(string), "%s comprou a casa %d para o governo", PlayerName[playerid], house);
						server_log("casas", string);

						House_SetOwner(house, -2, "Governo do Estado");
						House_Update(house);
					}
					default: {
						House_Buy(playerid, house);
					}
				}
			}
			Dialog_ShowCallback(playerid, using inline D_BuyHouseGov, DIALOG_STYLE_LIST, "selecione uma opcao", 
			""C_WHITE"Comprar a casa "C_YELLOW"para mim\n"C_WHITE"Comprar a casa "C_CYAN"para o governo\n", "Comprar", "Cancelar");
		} else {
			House_Buy(playerid, house);
		}
		return 1;
	}
    else if (!strcmp(params, "vender", true))
    {
		new house = House_PlayerGet(playerid);

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está proximo de uma residencia.");

		if (House_GetOwner(house) != Player_GetAccountID(playerid) && Dev_GetNivel(playerid) < DEV_DELTA)
			return SendClientMessage(playerid, -1, "Você não é dono dessa casa.");

		if (GetPVarInt(playerid, "p_intrade"))
			return 1;

		new value = House_GetValue(house),
			MapZone:zone = GetMapZoneAtPoint2D(House_GetEntryX(house), House_GetEntryY(house)),
			zone_name[MAX_MAP_ZONE_NAME];

		GetMapZoneName(zone, zone_name);

		switch (House_GetValueType(house)) {
	        case VALUE_TYPE_MONEY: Player_AddMoney(playerid, floatround(value / 2.0));
			case VALUE_TYPE_CASH: Player_AddCash(playerid, floatround(value / 2.0));
		}
		House_Sell(house);
		House_Save(house);
		
    	SendMsgF(playerid, COLOR_ORANGE, "<< Casas >> Você vendeu a casa em %s por %s%s{FFA500}.", zone_name, House_ValueType(house), getFormatText(floatround(value / 2.0)));
		ServerLog::("casas", "%s vendeu a casa %d por %s %s", PlayerName[playerid], house, value, House_GetValueType(house) == VALUE_TYPE_MONEY ? "em dinheiro" : "em cash");
		return 1;
	}
	else if (!strcmp(params, "trancar", true)) return callcmd::casa(playerid, "chave");
	else if (!strcmp(params, "chave", true))
    {
        new house = House_PlayerGet(playerid);

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está proximo de uma residencia.");

		if (House_GetOwner(house) != Player_GetAccountID(playerid) && Dev_GetNivel(playerid) < DEV_DELTA)
			return SendClientMessage(playerid, -1, "Você não é dono dessa casa.");

		if (!House_GetLock(house)) {
			House_SetLock(house, true);
			House_Save(house);
			ShowPlayerMessage(playerid, "Voce ~r~~h~trancou ~w~a sua residencia", 5000);
		}
		else {
			House_SetLock(house, false);
			House_Save(house);
			ShowPlayerMessage(playerid, "Voce ~g~~h~abriu ~w~a sua residencia", 5000);
		}
		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		return 1;
	}
	else if (strfind(params, "ir", true) != -1)
	{
	    if (Admin_GetNivel(playerid) < MASTER  && Dev_GetNivel(playerid) < DEV_ALPHA) 
			return SendClientMessage(playerid, -1 ,"Você não tem autorização para usar esse comando.");

		new house;
		if (sscanf(params, "s[25]d", null, house))
			return SendClientMessage(playerid, -1, "Modo de uso: /casa ir (id da casa)");

		if (!House_IsValid(house))
			return SendClientMessage(playerid, -1, "Você digitou o id de uma casa inválida.");

		SetPlayerPos(playerid, House_GetEntryX(house), House_GetEntryY(house), House_GetEntryZ(house));
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);

		format(string, sizeof(string), "DevCmd: %s(%d) foi até a casa %d.", PlayerName[playerid], playerid, house);
		Staff_ChatToAll(COLOR_DEV, string, SUB_DONO);
		return 1;
	}
	else if (strfind(params, "dono", true) != -1)
	{
	    if (Dev_GetNivel(playerid) < DEV_DELTA) 
			return SendClientMessage(playerid, -1 ,"Você não tem autorização para usar esse comando.");

		new house, name[MAX_PLAYER_NAME];
		if (sscanf(params, "s[25]ds[25]", null, house, name)) 
			return SendClientMessage(playerid, COLOR_WHITE, "Modo de uso: /casa dono (id da casa) (nome)");

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você digitou o id de uma casa inválida.");

		new id = Player_GetAccountIDByNick(name);
		if(id == -1)
			return SendClientMessage(playerid, COLOR_WHITE, "Você selecionou um jogador inexistente.");

		House_SetOwner(house, id, name);
		House_Update(house);
		House_Save(house);

		format(string, sizeof(string), "DevCmd: %s(%d) setou o dono da casa %d para %s.", PlayerName[playerid], playerid, house, name);
		Staff_ChatToAll(COLOR_DEV, string, SUB_DONO);
		return 1;
	}
	else if (strfind(params, "vencimento", true) != -1)
	{
	    if (Dev_GetNivel(playerid) < DEV_DELTA) 
			return SendClientMessage(playerid, COLOR_WHITE ,"Você não tem autorização para usar esse comando.");

		new house, vencimento[25];
		if (sscanf(params, "s[25]ds[25]", null, house, vencimento)) 
			return SendClientMessage(playerid, COLOR_WHITE, "Modo de uso: /casa vencimento (id da casa) (yyyy-mm-dd hh:MM:ss)");

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você digitou o id de uma casa inválida.");

		House_SetMaturity(house, vencimento);
		House_Save(house);

		format(string, sizeof(string), "DevCmd: %s(%d) setou o vencimento da casa %d para %s.", PlayerName[playerid], playerid, house, vencimento);
		Staff_ChatToAll(COLOR_DEV, string, SUB_DONO);
		ServerLog::("casa_vencimento", "%s(%d) setou o vencimento da casa %d para %s.", PlayerName[playerid], playerid, house, vencimento);
		return 1;
	}
	else if (strfind(params, "criar", true) != -1)
	{
	    if (Dev_GetNivel(playerid) < DEV_DELTA) 
			return SendClientMessage(playerid, -1 ,"Você não tem autorização para usar esse comando.");

		new house = Iter_Free(Houses);
		
		if (house == INVALID_ITERATOR_SLOT)
			return SendClientMessage(playerid, -1 ,"Limite de casas atinjido.");

		new 
			owner = 0,
			owner_name[MAX_PLAYER_NAME] = "NULL",
			Float:entry_x,
			Float:entry_y,
			Float:entry_z,
			Float:exit_x = 530.251,
			Float:exit_y = 1573.86,
			Float:exit_z = 655.987,
			Float:entry_rot,
			level = 10,
			value_type = 0,
			value = 300000,
			interior = 7,
			world = house,
			bool:lock = false,
			status = 0,
			expenses = 0,
			designer = 0,
			designer_name[MAX_PLAYER_NAME] = "NULL",
			tenant = 0,
			tenant_name[MAX_PLAYER_NAME] = "NULL",
			rental_value = 0,
			maturity[30],
			max_furniture;
			
		GetPlayerPos(playerid, entry_x, entry_y, entry_z);
		GetPlayerFacingAngle(playerid, entry_rot);
		
		TimeFormat((Now() + Days:30), MYSQL_TIMESTAMP, maturity);
		max_furniture = 120;
	
		if (House_Create(house, owner, owner_name, entry_x, entry_y, entry_z, exit_x, exit_y, exit_z, entry_rot, level, value_type, value, 
			interior, world, lock, status, expenses, designer, designer_name, tenant, tenant_name, rental_value, maturity, max_furniture)) {
			House_Insert(house);
		}

		format(string, sizeof(string), "DevCmd: %s(%d) criou a casa %d.", PlayerName[playerid], playerid, house, House_ValueType(house), getFormatText(value));
		Staff_ChatToAll(COLOR_DEV, string, SUB_DONO);
		ServerLog::("casa_editar", "%s(%d) criou a casa %d.", PlayerName[playerid], playerid, house, House_GetNivel(house), getFormatText(value), House_GetValueType(house) == VALUE_TYPE_CASH ? "em cash" : "em dinheiro");
		return 1;
	}
	else if (strfind(params, "editar", true) != -1)
	{
     	new house = House_PlayerGet(playerid);

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está proximo de uma residencia.");

	    if (Dev_GetNivel(playerid) < DEV_DELTA) 
			return SendClientMessage(playerid, -1 ,"Você não tem autorização para usar esse comando.");

		new type_value, value, level;
		if (sscanf(params, "s[25]ddd", null, type_value, value, level)) {
			SendClientMessage(playerid, COLOR_WHITE, "Modo de uso: /casa editar (moeda de pagamento) (preco) (nivel)");
			SendClientMessage(playerid, COLOR_GRAY, "Moeda de pagamento: DINHEIRO: (0) | CASH (1)");
			return 1;
		}
		
		House_SetValueType(house, type_value);
		House_SetValue(house, value);
		House_SetNivel(house, level);
		House_Update(house);
		House_Save(house);

		format(string, sizeof(string), "DevCmd: %s(%d) alterou o valor da casa %d para %s%s.", PlayerName[playerid], playerid, house, House_ValueType(house), getFormatText(value));
		Staff_ChatToAll(COLOR_DEV, string, SUB_DONO);
		ServerLog::("casa_editar", "%s(%d) editou a casa %d para nível %d e valor: %s %s.", PlayerName[playerid], playerid, house, House_GetNivel(house), getFormatText(value), House_GetValueType(house) == VALUE_TYPE_CASH ? "em cash" : "em dinheiro");
		return 1;
	}
	else if (strfind(params, "status", true) != -1)
	{
	    new house = House_PlayerGet(playerid);
		
		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está proximo de uma residencia.");

		if (Dev_GetNivel(playerid) < DEV_DELTA) 
			return SendClientMessage(playerid, -1 ,"Você não tem autorização para usar esse comando.");

		new status;
		if (sscanf(params, "s[25]d", null, status)) 
			return SendClientMessage(playerid, -1, "Modo de uso: /casa status (LIBERAR (0) | PROIBIR (1))");

		if (status < 0 || status > 1)
			return SendClientMessage(playerid, -1, "Use 0 para liberar e 1 para proibir a compra/venda da casa.");
		
		House_SetStatus(house, status);
		House_Update(house);
		House_Save(house);

		format(string, sizeof(string), "DevCmd: %s(%d) alterou o status da casa %d para %s.", PlayerName[playerid], playerid, house, !House_GetStatus(house) ? "liberada" : "proibida");
		Staff_ChatToAll(COLOR_DEV, string, SUB_DONO);
		ServerLog::("casa_editar", "%s(%d) alterou o status da casa %d para %s.", PlayerName[playerid], playerid, house, !House_GetStatus(house) ? "liberada" : "proibida");
		return 1;
	}
 	else if (strfind(params, "trazer", true) != -1)
	{
		if (Dev_GetNivel(playerid) < DEV_DELTA) 
			return SendClientMessage(playerid, -1 ,"Você não tem autorização para usar esse comando.");

	    new house;
		if (sscanf(params, "s[25]d", null, house)) 
			return SendClientMessage(playerid, -1, "Modo de uso: /casa trazer (id da casa)");

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você digitou o id de uma casa inválida.");

		new Float:posX,
			Float:posY,
			Float:posZ,
			Float:angle,
			MapZone:zone,
			zone_name[MAX_MAP_ZONE_NAME];

		GetPlayerPos(playerid, posX, posY, posZ);
		GetPlayerFacingAngle(playerid, angle);

		House_SetEntryX(house, posX);
		House_SetEntryY(house, posY);
		House_SetEntryZ(house, posZ);
		House_SetWorld(house, house);
		House_SetEntryRot(house, angle);
		House_Update(house, true);
		House_Save(house);

		zone = GetMapZoneAtPoint2D(House_GetEntryX(house), House_GetEntryY(house));
		GetMapZoneName(zone, zone_name);

		format(string, sizeof(string), "DevCmd: %s(%d) puxou a casa %d para %s.", PlayerName[playerid], playerid, house, zone_name);
		Staff_ChatToAll(COLOR_DEV, string, SUB_DONO);
		ServerLog::("casa_trazer", "%s(%d) puxou a casa %d para %s.", PlayerName[playerid], playerid, house, zone_name);
    	return 1;
	}
	else if (!strcmp(params, "rotacao", true))
	{
		if (Admin_GetNivel(playerid) < DONO) 
			return SendClientMessage(playerid, -1 ,"Você não tem autorização para usar esse comando.");
	
		new house = House_PlayerGet(playerid),
			Float:angle;

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está proximo de uma residencia.");

		GetPlayerFacingAngle(playerid, angle);
		House_SetEntryRot(house, angle);
	    House_Save(house);

		format(string, sizeof(string), "DevCmd: %s(%d) ajustou a rotação da casa %d.", PlayerName[playerid], playerid, house);
		Staff_ChatToAll(COLOR_DEV, string, SUB_DONO);
		return 1;
	}
	else if (strfind(params, "interior", true) != -1)
	{
		if (Admin_GetNivel(playerid) < DONO) 
			return SendClientMessage(playerid, -1 ,"Você não tem autorização para usar esse comando.");

	    new house;
		if (sscanf(params, "s[25]d", null, house)) 
			return SendClientMessage(playerid, -1, "Modo de uso: /casa interior (id da casa)");

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você digitou o id de uma casa inválida.");

		new Float:posX,
			Float:posY,
			Float:posZ,
			interior = GetPlayerInterior(playerid);

		GetPlayerPos(playerid, posX, posY, posZ);

		House_SetExitX(house, posX);
		House_SetExitY(house, posY);
		House_SetExitZ(house, posZ);

		House_SetInterior(house, interior);

		format(string, sizeof(string), "DevCmd: %s(%d) trocou o interior da casa %d.", PlayerName[playerid], playerid, house);
		Staff_ChatToAll(COLOR_DEV, string, SUB_DONO);
		ServerLog::("casa_editar", "%s(%d) trocou o interior da casa %d.", PlayerName[playerid], playerid, house);
		return 1;
	}
	return 1;
}

CMD:contratar(playerid, params[])
{
    if (sscanf(params, "s[128]", params))
	{
	    SendClientMessage(playerid, -1, "Modo de uso: /contratar (nome)");
	    SendClientMessage(playerid, COLOR_GRAD, "NOMES: designer");
 		SendClientMessage(playerid, COLOR_GRAD, "_________________________________________________");
		return true;
	}

	new null[25], string[95];

    if (strfind(params, "designer", true) != -1)
    {
		new house = House_PlayerGet(playerid);

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está proximo de uma residencia.");

	    if (House_GetOwner(house) != Player_GetAccountID(playerid)) 
			return SendClientMessage(playerid, -1, "Você não está próximo a uma casa sua.");

        new idplayer;
		if (sscanf(params, "s[25]d", null, idplayer)) 
			return SendClientMessage(playerid, -1, "Modo de uso: /contratar designer (id do jogador)");

	    if (!Player_Logado(idplayer)) 
			return SendClientMessage(playerid, -1, "Este jogador não está conectado/logado no servidor.");

		if (!ProxDetectorS(20.0, playerid, idplayer)) 
			return SendClientMessage(playerid, -1, "Você não está próximo ao jogador.");

		if (!PlayerIsDesignInterior(idplayer)) 
			return SendClientMessage(playerid, -1, "Este jogador não é um designer de interiores.");

		// if (!DesignerHouses_Free(idplayer)) {
		// 	new houses = DesignerHouses_Count(idplayer);
		// 	SendMsgF(idplayer, COLOR_ORANGE, "<< Casas >> %s tentou te contratar mas você já é designer de %d residencias.", PlayerName[playerid], houses);
		// 	SendMsgF(playerid, COLOR_ORANGE, "<< Casas >> Você tentou te contratar %s mas ele já é designer de %d residencias.", PlayerName[idplayer], houses);
		
		// 	return 1;
		// }

	   	SendMsgF(idplayer, COLOR_ORANGE, "<< Casas >> Você foi contratado por %s para decorar a casa %d.", PlayerName[playerid], house);
	   	SendMsgF(playerid, COLOR_ORANGE, "<< Casas >> Você acaba de contratar %s como designer de sua casa %d.", PlayerName[idplayer], house);

		House_SetDesigner(house, Player_GetAccountID(idplayer), PlayerName[idplayer]);
		House_Update(house);
		House_Save(house);

		format(string, sizeof(string), "%s contratou o designer %s para a casa %d.", PlayerName[playerid], PlayerName[idplayer], house);
		ServerLog::("casas_designer", string);
		return 1;
	}
	return 1;
}

CMD:casasdesigner(playerid)
	return Houses_Show(playerid, 2);

CMD:minhascasas(playerid)
	return Houses_Show(playerid);

CMD:alugar(playerid, params[])
{
    if (sscanf(params, "s[128]", params)) {
	    SendClientMessage(playerid, COLOR_WHITE, "Modo de uso: /alugar (nome)");
	    SendClientMessage(playerid, COLOR_GRAY, "NOMES: casa");
 		SendClientMessage(playerid, COLOR_GRAY, "_________________________________________________");
		return true;
	}
	if (!strcmp(params, "casa", true))
	{
		new house = House_PlayerGet(playerid);

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está proximo de uma casa.");

		if (House_GetOwner(house) == Player_GetAccountID(playerid)) 
			return SendClientMessage(playerid, COLOR_WHITE, "Você não pode alugar sua própria casa.");

		if (Tenant_CountHouse(playerid) > 0)
			return SendClientMessage(playerid, COLOR_WHITE, "Você já alugou uma casa.");

		if (House_GetTenant(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Essa casa já está alugada.");

		new value = House_GetRentalValue(house);
		if (value < 1)
			return SendClientMessage(playerid, COLOR_WHITE, "Essa casa não está alugando.");

		if (Player_GetMoney(playerid) < value)
			return SendClientMessage(playerid, COLOR_WHITE, "Você não tem dinheiro para pagar o aluguel.");

		if (Player_GetMoneyBank(playerid) < 0)
			return SendClientMessage(playerid, COLOR_WHITE, "Você está endividado com o banco e não pode alugar uma casa.");

		House_Rent(playerid, house);
		return 1;
	}
	return 1;
}

CMD:desalugar(playerid, params[])
{
	if (sscanf(params, "s[128]", params)) {
	    SendClientMessage(playerid, COLOR_WHITE, "Modo de uso: /desalugar (nome)");
	    SendClientMessage(playerid, COLOR_GRAY, "NOMES: casa");
 		SendClientMessage(playerid, COLOR_GRAY, "_________________________________________________");
		return 1;
	}
	new string[128];

	if (!strcmp(params, "casa", true)) {
	    new house = House_PlayerGet(playerid);
		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está proximo de uma residencia.");
	
	    if (House_GetTenant(house) != Player_GetAccountID(playerid)) 
			return SendClientMessage(playerid, COLOR_WHITE, "Você não é inquilino dessa residencia.");

		new MapZone:zone,
			zone_name[MAX_MAP_ZONE_NAME];

		zone = GetMapZoneAtPoint2D(House_GetEntryX(house), House_GetEntryY(house));
		GetMapZoneName(zone, zone_name);

		format(string, sizeof(string), "%s desalugou sua residencia %d em %s.", PlayerName[playerid], house, zone_name);
		SendPlayerEmail("Imobiliaria "SERVER_TAG"", House_GetOwnerName(house), string);

		format(string, sizeof(string), "<< Casas >> Você desalugou a residencia %d em %s, pagamento cancelado.", PlayerName[playerid], house, zone_name);
		SendClientMessage(playerid, COLOR_ORANGE, string), 

		House_DumpTenant(house);
		House_ReloadTenant(playerid);
		PlayerInfo[playerid][pSpawn] = 0;
		return 1;
	}
	return 1;
}

CMD:aluguel(playerid, const params[])
{
    if (sscanf(params, "s[128]", params))
	{
	    SendClientMessage(playerid, COLOR_WHITE, "Modo de uso: /aluguel (nome)");
	    SendClientMessage(playerid, COLOR_GRAY, "NOMES: ajuda | permissao | valor | despejar");
 		SendClientMessage(playerid, COLOR_GRAY, "_________________________________________________");
		return true;
	}

	new null[25], string[140];

    if (!strcmp(params, "ajuda", true))
    {
		MEGAString[0] = EOS;

		format(MEGAString, sizeof(MEGAString), 
			""C_ORANGE"-> "C_WHITE"Funcionamento:		"C_WHITE"Você pode alugar sua casa para 1 pessoa e receber por Payday que a pessoa estiver on-line.\n\
			"C_ORANGE"-> "C_WHITE"Permitir aluguel:		"C_WHITE"Para permitir o aluguel, o valor deve ser definido maior que 0 (/aluguel valor).\n\
			"C_ORANGE"-> "C_WHITE"Valor do aluguel:		"C_WHITE"Você pode definir entre $1 á $1.000, se definido como 0, não permite alugar.\n\
			"C_ORANGE"-> "C_WHITE"Despejando:			"C_WHITE"Para despejar um inquilino use: /casa despejar.\n\n\
			"C_RED"Observacao: "C_WHITE"O jogador que alugar poderá nascer na casa e usar a garagem, mas parte de mobiliar é do proprietário.");

		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, ""C_ORANGE"[ ALUGUEL DA RESIDENCIA ]", MEGAString, "Entendi", "");
		
		return 1;
    }
	else if (strfind(params, "valor", true) != -1)
	{
	    new house = House_PlayerGet(playerid);

		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está proximo de uma residencia.");

		if (House_GetOwner(house) != Player_GetAccountID(playerid)) 
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está próximo a uma casa sua.");
	
	    if (House_GetTenant(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você tem um inquilino, despeje-o para aumentar o valor do aluguel.");
	
	    new value;
		if (sscanf(params, "s[25]d", null, value)) 
			return SendClientMessage(playerid, COLOR_WHITE, "Modo de uso: /aluguel valor (valor do aluguel | entre $1 a $1.000)");

		if (value < 1 || value > 1000) 
			return SendClientMessage(playerid, COLOR_WHITE, "Você deve definir um valor de $200 a $1.000");

		House_SetRentalValue(house, value);
		
		format(string, sizeof(string), "<< Casas >> Você definiu o valor do aluguel da residencia %d para $%s.", house, getFormatText(value));
		SendClientMessage(playerid, COLOR_ORANGE, string);

		House_Update(house);
		House_Save(house);

		return 1;
	}
	else if (strfind(params, "despejar", true) != -1)
	{
	    new house = House_PlayerGet(playerid);
		
		if (!House_IsValid(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está proximo de uma residencia.");

		if (House_GetOwner(house) != Player_GetAccountID(playerid)) 
			return SendClientMessage(playerid, COLOR_WHITE, "Você não está próximo a uma casa sua.");
	
	    if (House_GetTenant(house))
			return SendClientMessage(playerid, COLOR_WHITE, "Você não tem um inquilino.");
	
	    new result[36];
		if (sscanf(params, "s[25]s[36]", null, result)) 
			return SendClientMessage(playerid, -1, "Modo de uso: /aluguel despejar (motivo)");

		if (strlen(result) < 5 || strlen(result) > 35) 
			return SendClientMessage(playerid, -1, "O motivo deve estar entre 5 a 35 caracteres.");
		
		format(string, sizeof(string), "<< Casas >> Você despejou o inquilino %s de sua casa, motivo: %s.", House_GetTenantName(house), result);
		SendClientMessage(playerid, COLOR_ORANGE, string);

		House_DumpTenant(house);
		House_Update(house);
		House_Save(house);

		new idplayer = GetPlayerID(House_GetTenantName(house));
		if (Player_Logado(idplayer))
		{
			House_ReloadTenant(idplayer);
			PlayerInfo[idplayer][pSpawn] = 0;

			format(string, sizeof(string), "<< Casas >> %s, dono da casa %d, te despejou, motivo: %s.", PlayerName[playerid], house, result);
			SendClientMessage(idplayer, COLOR_ORANGE, string);
		}
		return 1;
	}
	return 1;
}

// CMD:guardarcomida(playerid, params[])
// {
// 	new casaid = Player_GetInHouse(playerid);
// 	new fogaoid = getFogaoPerto(playerid);

//     if (GetPVarInt(playerid, "cozidoPronto") != 1)
//         return SendClientMessage(playerid, -1, "Não há nada cozinhado pronto ainda, aguarde!");

// 	if (MobInfo[casaid][fogaoid][mobObject] != GetPVarInt(playerid, "fogaoUsado") && isMovelCooker(MobInfo[casaid][fogaoid][mobModel])
// 	&& IsPlayerInRangeOfPoint(playerid, 1.5, MobInfo[casaid][fogaoid][mobPos][0], MobInfo[casaid][fogaoid][mobPos][1], MobInfo[casaid][fogaoid][mobPos][2]))
// 		return SendClientMessage(playerid, -1, "Este fogão não há nada ou não foi você que preparou!"), 0;

// 	if (MobInfo[casaid][fogaoid][mobObject] == GetPVarInt(playerid, "fogaoUsado") && isMovelCooker(MobInfo[casaid][fogaoid][mobModel])
// 	&& IsPlayerInRangeOfPoint(playerid, 1.5, MobInfo[casaid][fogaoid][mobPos][0], MobInfo[casaid][fogaoid][mobPos][1], MobInfo[casaid][fogaoid][mobPos][2]))
// 	{
// 	    switch (GetPVarInt(playerid, "idObjectFinale"))
// 	    {
// 		    case 19882: {
// 		        givePlayerItem(playerid, ITEM_TYPE_COMIDA, ITEM_MODEL_CARNE, 1, "Carne Frita");
// 		        SendClientMessage(playerid, -1, "Você guardou {00BFFF}Carne Frita"C_WHITE", em seu inventário!");
// 	      	}
// 	      	case 19580: {
// 		        givePlayerItem(playerid, ITEM_TYPE_COMIDA, ITEM_MODEL_PIZZA, 6, "Fatia de Pizza");
// 		        SendClientMessage(playerid, -1, "Você guardou {00BFFF}6 fatias de pizza"C_WHITE", em seu inventário!");
// 	      	}
// 	      	case ITEM_MODEL_FRANGO: {
// 		        givePlayerItem(playerid, ITEM_TYPE_COMIDA, ITEM_MODEL_FRANGO, 1, "Coxa de Frango");
// 		        SendClientMessage(playerid, -1, "Você guardou {00BFFF}Coxa de Frango"C_WHITE", em seu inventário!");
// 	      	}
// 	   		default: {
// 				givePlayerItem(playerid, ITEM_TYPE_COMIDA, ITEM_MODEL_PAO, 8, "Fatia de Pao");
// 		        SendClientMessage(playerid, -1, "Você guardou {00BFFF}8 fatias de pão"C_WHITE", em seu inventário!");
// 			}
// 		}
// 		FinaleCookingReady(playerid);
//       	return 1;
// 	} else {
// 	    return SendClientMessage(playerid, -1, "Você não está perto de um fogão!");
//  	}
// }

CMD:arrombar(playerid, params[])
{
	if (!IsACop(playerid) && 
		GetPlayerOrg(playerid) != 8 && 
		GetPlayerOrg(playerid) != 22) 
		return SendClientMessage(playerid, -1, "Apenas organizações policiais e assassinas possui esse comando.");

	// SetPlayerFacingAngle(playerid, House_GetEntryRot(house));
	ApplyAnimation(playerid,"POLICE","Door_Kick", 4.1, false, true, true, true, 1, SYNC_ALL);

	foreach (new h : Houses)
	{
		if (PlayerToPoint(3, playerid, House_GetEntryX(h), House_GetEntryY(h), House_GetEntryZ(h))) {
			SetPlayerPos(playerid, House_GetExitX(h), House_GetExitY(h), House_GetExitZ(h));
			SetPlayerInterior(playerid, House_GetInterior(h));
			SetPlayerVirtualWorld(playerid, House_GetWorld(h));
			Player_SetInHouse(playerid, h);
		    GameTextForPlayer(playerid, "~w~Voce arrombou a porta...", 5000, 1);
			PlayerPlaySound(playerid, 32400, 0.0, 0.0, 0.0);
		}
	}
	return 1;
}