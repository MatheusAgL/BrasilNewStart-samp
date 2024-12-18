#include <YSI_Coding\y_hooks>

#define ID_MENU_VEHICLES_TAXIDRIVER 6

new static a_string[128];

static TaxiDriver_Category[][enumMenuCategory] = 
{
    { 1, "Taxi", 10, 0 },
    { 1, "Cabbie", 10, 0 },
    { 1, "Wayfarer", 10, 0 }
};

static TaxiDriverVehicle[20][tempVehicleEnum];

CALLBACK:IsPlayerTaxidriver(playerid) {
	return (
		PlayerInfo[playerid][pEmprego] == ID_JOB_TAXISTA || 
		PlayerInfo[playerid][pEmprego2] == ID_JOB_TAXISTA
	);
}

hook OnGameModeInit() {
	CreateDynamicPickup(19942, 23, 1756.9924,-1885.6012,13.5563);
    CreateDynamic3DTextLabel("Taxista\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para trabalhar", 0xFFFFFFFF,1756.9924,-1885.6012,13.5563,13.0);

	CreateDynamicPickup(1025, 23, 1766.7280,-1905.4937,13.5677); //Pegar ve�culo
    CreateDynamic3DTextLabel("Garagem da Taxi Company\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para pegar uma moto", 0xFFFFFFFF,1766.7280,-1905.4937,13.5677,13.0);

	CreateDynamicObject(11729, 1756.68640, -1884.11926, 12.55198,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(11729, 1757.34143, -1884.12805, 12.55198,   0.00000, 0.00000, 0.00000);
	return 1;
}

hook DealWithPlayerInPosition(playerid) {
	if(PlayerToPoint(2.0, playerid, 1766.7280,-1905.4937,13.5677)) {
		if(!IsPlayerTaxidriver(playerid)) {
			SendClientMessage(playerid, -1, "Voc� n�o � um taxista.");
		}
		else if(!IsPlayerWorking(playerid)) {
			SendClientMessage(playerid, -1, "Voc� n�o est� em servi�o. Bata cart�o para pegar um ve�culo.");
		}
		else {
			TogglePlayerControllable(playerid, false);
			MenuInfo[playerid][menu_id] = ID_MENU_VEHICLES_TAXIDRIVER;
			OpenMenu(playerid, ID_MENU_VEHICLES_TAXIDRIVER);
		}
	}
    else if(PlayerToPoint(2.0, playerid, 1756.9924,-1885.6012,13.5563)) {
		if(!IsPlayerTaxidriver(playerid)) {
			SendClientMessage(playerid, -1, "Voc� n�o � um taxista.");
		}
		else {
			new string[128];
			if(!IsPlayerWorking(playerid)) {
				PlayerInfo[playerid][pSkinServico] = 142;
				SetPlayerSkin(playerid, PlayerInfo[playerid][pSkinServico]);

				format(string, sizeof string, "(( Taxistas )) {FFFFFF}%s pegou seu uniforme e est� em servi�o.", PlayerName[playerid]);
				EmpregoMensagem(0xE0D78AFF, string, ID_JOB_TAXISTA);

				TogglePlayerWorking(playerid);
			}
			else {
				TogglePlayerWorking(playerid);
				SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
				SendMsgF(playerid, COLOR_LIGHTBLUE, "Voc� guardou sua farda e n�o est� mais de servi�o");
			}
		}
	}
}

hook ChangeMenuTitle(playerid, menuid) {
	if(menuid == ID_MENU_VEHICLES_TAXIDRIVER) {
		PlayerTextDrawBoxColor(playerid, menu_ptextdraws[0][playerid], -1021765121);
		PlayerTextDrawColor(playerid, menu_ptextdraws[1][playerid], -1);
		PlayerTextDrawSetString(playerid, menu_ptextdraws[1][playerid], "Taxistas");
	}
}

hook MenuSetItens(playerid, menuid) {
	if(menuid == ID_MENU_VEHICLES_TAXIDRIVER) {
		MenuInfo[playerid][menu_max_itens] = sizeof(TaxiDriver_Category);

		for(new i; i < sizeof(TaxiDriver_Category); i++) {
			Menu_Category[playerid][i][category_id]                     = TaxiDriver_Category[i][category_id];
			format(Menu_Category[playerid][i][category_nome], 20,       TaxiDriver_Category[i][category_nome]);
			Menu_Category[playerid][i][category_quantidade]             = TaxiDriver_Category[i][category_quantidade];
			Menu_Category[playerid][i][category_position]               = TaxiDriver_Category[i][category_position];
		}
	}
}

hook OnVehicleDestroyed(vehicleid) {
	if(VehicleInfo[vehicleid][vhTemp]) {
		for(new i = 0; i < sizeof(TaxiDriverVehicle); i++) {
			if(TaxiDriverVehicle[i][tvVehicleID] == vehicleid) {
				new itemId = GetVehicleModel(vehicleid) == 407 ? 0 : 1;

				TaxiDriver_Category[itemId][category_quantidade] += 1;
				VehicleInfo[vehicleid][vhTemp] = 0;
				TaxiDriverVehicle[i][tvCreated] = 0;
				return 1;
			}	
		}
	}
	return 1;
}

hook OnPlayerConfirmMenu(playerid, menuid, pageid, itemid, selecteditem) {
	if(menuid == ID_MENU_VEHICLES_TAXIDRIVER) {
		if(TaxiDriver_Category[selecteditem][category_quantidade] <= 0) 
			return SendClientMessage(playerid, -1, "N�o existem unidades desse ve�culo dispon�veis para uso.");

		DestroyPlayerTempVehicle(playerid);

		//TaxiDriver_Category[selecteditem][category_quantidade] -= 1;

		new modelid;
        if(selecteditem == 0) {
            modelid = 420;
        }
        else if(selecteditem == 1) {
            modelid = 438;
        }
        else if(selecteditem == 2) {
            modelid = 586;
        }

		new vehid = CreateVehicle(modelid, 1777.8325,-1887.4685,13.0927,268.8184, 6, 6, -1);

		UnlockVehicleDoors(vehid);
		PutPlayerInVehicle(playerid, vehid, 0);
		SetPlayerTempVehicleID(playerid, vehid);
		VehicleInfo[vehid][vhTemp] = 1;

		for(new i = 0; i < sizeof(TaxiDriverVehicle); i++) {
			if(!TaxiDriverVehicle[i][tvCreated]) {
				TaxiDriverVehicle[i][tvCreated] = 1;
				TaxiDriverVehicle[i][tvVehicleID] = vehid;
				TaxiDriverVehicle[i][tvModelID] = modelid;
				TaxiDriverVehicle[i][tvPlayerID] = playerid;

				SetPVarInt(playerid, "TaxiDriverVehicleID", i);
				break;
			}
		}

		KickPlayerMenu(playerid);
	}
	return 1;
}

CMD:cancelartaxi(playerid)
{
    if (!GetPVarInt(playerid, "TaxiSolicitado") && !GetPVarInt(playerid, "TaxiAtendido"))  
        return SendClientMessage(playerid, -1, "Voc� n�o solicitou um taxi ou n�o atendeu uma corrida.");

    new 
        taxistaid = GetPVarInt(playerid, "TaxiAtendeu"),
        passageiroid = GetPVarInt(playerid, "TaxiCliente");

    //Se o jogador for o passageiro
    if(GetPVarInt(playerid, "TaxiSolicitado"))
    {
        if(GetPVarInt(playerid, "TaxiEmCorrida") && GetPlayerVehicleID(playerid) ==  GetPlayerVehicleID(taxistaid))
            return SendClientMessage(playerid, COLOR_GRAD, "Voc� n�o pode cancelar a corrida estando dentro do taxi.");

        SendClientMessage(playerid, -1, "Voc� cancelou o chamado de taxi.");
        SendClientMessage(taxistaid, -1, "O passageiro cancelou o chamado da corrida.");

        DeletePVar(taxistaid, "TaxiAtendeu");
        DeletePVar(taxistaid, "TaxiTotalCorrida");
        DeletePVar(taxistaid, "TaxiEmCorrida");
        DeletePVar(taxistaid, "TaxiCliente");
        DeletePVar(taxistaid, "TaxiAtendido");
        DeletePVar(taxistaid, "TaxiSolicitado");
        DeletePVar(taxistaid, "TaxiHorario");
    }
    //Se  o jogador for o  taxista
    else 
    {
        if(GetPVarInt(playerid, "TaxiEmCorrida") && GetPlayerVehicleID(playerid) ==  GetPlayerVehicleID(passageiroid))
            return SendClientMessage(playerid, COLOR_GRAD, "Voc� n�o pode cancelar a corrida com o passageiro dentro do taxi.");

        SendClientMessage(playerid, -1, "Voc� cancelou a corrida com o passageiro.");
        SendClientMessage(passageiroid, -1, "O taxista cancelou a corrida. Chame outro taxi usando /servico taxi.");

        DeletePVar(passageiroid, "TaxiAtendeu");
        DeletePVar(passageiroid, "TaxiTotalCorrida");
        DeletePVar(passageiroid, "TaxiEmCorrida");
        DeletePVar(passageiroid, "TaxiCliente");
        DeletePVar(passageiroid, "TaxiAtendido");
        DeletePVar(passageiroid, "TaxiSolicitado");
        DeletePVar(passageiroid, "TaxiHorario");
    }

    DeletePVar(playerid, "TaxiAtendeu");
    DeletePVar(playerid, "TaxiTotalCorrida");
    DeletePVar(playerid, "TaxiEmCorrida");
    DeletePVar(playerid, "TaxiCliente");
    DeletePVar(playerid, "TaxiAtendido");
    DeletePVar(playerid, "TaxiSolicitado");
    DeletePVar(playerid, "TaxiHorario");
    return true;
}

stock DarPropostaTaxi(playerid, id) {
    if (!GetPVarInt(id, "TaxiSolicitado"))  
        return SendClientMessage(playerid, -1, "O jogador n�o solicitou nenhum taxi.");

    if (GetPVarInt(playerid, "TaxiEmCorrida")) 
        return SendClientMessage(playerid, -1, "Voc� j� est� em corrida.");

    SetPVarInt(playerid, "TaxiCliente", id);
    format(MEGAString, sizeof(MEGAString), "{FFFFFF}Passageiro: {33CCFF}%s\n\n{FFFFFF}Digite o valor cobrado a cada 10 segundos de sua corrida:", PlayerName[id]);
    ShowPlayerDialog(playerid, 401, DIALOG_STYLE_INPUT, "{FFFFFF}R�dio Taxi - Proposta", MEGAString, "Ofertar", "Cancelar");
    return 1;
}

stock ServicoTaxi(playerid)
{
    new string[256];

    if (GetPVarInt(playerid, "TaxiSolicitado") == 1 && gettime() < GetPVarInt(playerid, "TaxiHorario")+120)
        return SendMsgF(playerid, -1, "Voc� chamou um taxista, aguarde %s para solicitar novamente.", ConvertTime(GetPVarInt(playerid, "TaxiHorario")+120 - gettime()));
    else if(GetPlayerInterior(playerid) != 0)
        return SendClientMessage(playerid, -1, "Voc� n�o pode chamar um taxi dentro de um interior.");

    SetPVarInt(playerid, "TaxiSolicitado", 1);
    SetPVarInt(playerid, "TaxiHorario", gettime());

    format(string, sizeof(string), "R�dio Taxi diz: %s, estamos comunicando os taxistas. Entraremos em contato quando algum estiver a caminho!", PlayerName[playerid]);
    SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

    new MapZone:zone = GetPlayerMapZone2D(playerid);
    new zone_name[MAX_MAP_ZONE_NAME];
    GetMapZoneName(zone, zone_name);

    format(string, sizeof(string), "<< R�dio Taxi >> {FFFFFF}%s[%d] est� precisando de um taxi na regi�o de %s. Use /atenderchamado!", PlayerName[playerid], playerid, zone_name);
    EmpregoMensagem(0xE0D78AFF, string, 4);

    return true;
}

stock ListarChamadosTaxi(playerid)
{
	new players, string[128];
	
	MEGAString [0] = EOS;
	strcat(MEGAString, "Id  Nome\tTempo esperando\tLocaliza��o\n");

    new MapZone:zone;
    new zone_name[MAX_MAP_ZONE_NAME];
	
	foreach(new x : Player)
	{
	    if(GetPVarInt(x, "TaxiSolicitado") && !GetPVarInt(x, "TaxiEmCorrida"))
		{
            // Se passou mais de 15 minutos
            if(gettime()-GetPVarInt(x, "TaxiHorario") >= 300)
            {
                DeletePVar(x, "TaxiSolicitado");
            }
            else 
            {
                zone = GetPlayerMapZone2D(x);
                GetMapZoneName(zone, zone_name);

                format(string, sizeof (string), "{EEEEEE}%02d  %s\t%s\t{00FFFF}%s\n", x, PlayerName[x], ConvertTime(gettime()-GetPVarInt(x, "TaxiHorario")), zone_name);
                strcat(MEGAString, string);
                
                List_SetPlayers(playerid, players, x);
                players ++;
            }
	    }
	}
	
	format(string, sizeof (string), "Clientes aguardando taxi ({00FFFF}%d{FFFFFF})", players);
	ShowPlayerDialog(playerid, 400, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Atender", "Fechar");
}

stock AtenderChamadoTaxi(playerid, clienteid)
{
	if(GetPVarInt(clienteid, "TaxiAtendido"))
        return;

    new MapZone:zone = GetPlayerMapZone2D(clienteid);
    new zone_name[MAX_MAP_ZONE_NAME];
    GetMapZoneName(zone, zone_name);

    new string[256], valor = GetPVarInt(playerid, "TaxiCorrida");
    format(string, 256, "((R�dio Taxi)) {FFFFFF}%s acabou de aceitar a corrida para atender %s em %s.", PlayerName[playerid], PlayerName[clienteid], zone_name);
    EmpregoMensagem(0xE0D78AFF, string, ID_JOB_TAXISTA);

    SendMsgF(clienteid, -1, "R�dio Taxi diz: %s, o taxista %s est� a caminho da sua localiza��o. Ele cobra $%s a cada 10 segundos de corrida.", PlayerName[clienteid], PlayerName[playerid], getFormatText(valor));

    SetPVarInt(playerid, "TaxiEmCorrida", 1);
    SetPVarInt(playerid, "TaxiCliente", clienteid);
    SetPVarInt(clienteid, "TaxiAtendido", 1);
    SetPVarInt(clienteid, "TaxiAtendeu", playerid);

    SetPVarInt(clienteid, "varProcura", playerid);

    TempoProc[playerid] = gettime() + (3 * 60);
    TempoProc[clienteid] = gettime() + (3 * 60);

    stop timer_procurar[clienteid];
	timer_procurar[clienteid] = repeat timerProcurar(clienteid, playerid);

    SetPVarInt(playerid, "varProcura", clienteid);
    stop timer_procurar[playerid];
	timer_procurar[playerid] = repeat timerProcurar(playerid, clienteid);
}

new Timer:TaxiTimer[MAX_PLAYERS];

timer t_Taximetro[10000](playerid, taxistaid)
{
    new 
        clienteTaxista = GetPVarInt(taxistaid, "TaxiCliente"),
        taxistaCliente = GetPVarInt(playerid, "TaxiAtendeu"),
        emCorrida = GetPVarInt(taxistaid, "TaxiEmCorrida"),
        valor = GetPVarInt(playerid, "TaxiTotalCorrida")
    ;

	if(GetPlayerVehicleID(playerid) != GetPlayerVehicleID(taxistaid) && emCorrida && valor > 0)
	{
        if(clienteTaxista == playerid && taxistaCliente == taxistaid)
        {
            stop TaxiTimer[playerid];
            SendMsgF(playerid, -1, "Voc� pagou um total de $%s para o taxista %s pela corrida.", getFormatText(valor), PlayerName[taxistaid]);
            SendMsgF(taxistaid, -1, "Voc� recebeu $%s do passageiro %s pela corrida realizada.", getFormatText(valor), PlayerName[playerid]);
        
            Player_RemoveMoney(playerid, valor);
            Player_AddMoney(taxistaid, valor);

            DeletePVar(playerid, "TaxiAtendeu");
            DeletePVar(playerid, "TaxiTotalCorrida");
            DeletePVar(playerid, "TaxiEmCorrida");
            DeletePVar(playerid, "TaxiCliente");
            DeletePVar(playerid, "TaxiAtendido");
            DeletePVar(playerid, "TaxiSolicitado");

            DeletePVar(taxistaid, "TaxiAtendeu");
            DeletePVar(taxistaid, "TaxiTotalCorrida");
            DeletePVar(taxistaid, "TaxiEmCorrida");
            DeletePVar(taxistaid, "TaxiCliente");
            DeletePVar(taxistaid, "TaxiAtendido");
            DeletePVar(taxistaid, "TaxiSolicitado");

            GameTextForPlayer(playerid, "~r~CORRIDA ENCERRADA!", 1000, 1);
            GameTextForPlayer(taxistaid, "~r~CORRIDA ENCERRADA!", 1000, 1);
        }
    }
    else if(!emCorrida)
    {
        stop TaxiTimer[playerid];
    }
	else
    {
        new string[32], total;
        total = valor + GetPVarInt(taxistaid, "TaxiCorrida");
        SetPVarInt(playerid, "TaxiTotalCorrida", total);
        format(string, 32, "$%d", total);
        GameTextForPlayer(playerid, string, 5000, 1);
        GameTextForPlayer(taxistaid, string, 5000, 1);

        if(Player_GetMoney(playerid) < total)
            SendClientMessage(taxistaid, COLOR_LIGHTRED, "O passageiro n�o possui dinheiro suficiente para pagar a corrida...");
    }
	return true;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) 
{
    if(GetPVarInt(playerid, "TaxiAtendido")) 
    {
        new taxistaid = GetPVarInt(playerid, "TaxiAtendeu");
        if(GetPlayerVehicleID(taxistaid) == vehicleid && ispassenger)
        {
            new valor = GetPVarInt(taxistaid, "TaxiCorrida");

            TempoProc[playerid] = gettime();
            TempoProc[taxistaid] = gettime();

            TaxiTimer[playerid] = repeat t_Taximetro(playerid, taxistaid);
            SetPVarInt(playerid, "TaxiTotalCorrida", 0);
            SendMsgF(playerid, -1, "O tax�metro come�ou a contar. Est� sendo cobrado $%s a cada 10 segundos de corrida.", getFormatText(valor));
            SendMsgF(taxistaid, -1, "O tax�metro come�ou a contar. Est� sendo cobrado $%s a cada 10 segundos de corrida.", getFormatText(valor));
        
            GameTextForPlayer(playerid, "CORRIDA INICIADA!", 5000, 1);
            GameTextForPlayer(taxistaid, "CORRIDA INICIADA!", 5000, 1);
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == 400)
	{
	    if (response && listitem >= 0)
		{
	        new playerclick = List_GetPlayers(playerid, listitem);
			if (!Player_Logado(playerclick)) 
                return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

            SetPVarInt(playerid, "PlayerClick", playerclick);
			format(a_string, sizeof (a_string), "%d", playerclick);
			callcmd::atenderchamado(playerid, a_string);
	    }
        return 1;
	}
    else if (dialogid == 401)
	{
	    if (response && strlen(inputtext))
		{
	        new playerclick = GetPVarInt(playerid, "PlayerClick"), valor = strval(inputtext);
			if (!Player_Logado(playerclick)) 
                return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");
            else if(valor < 5 || valor > 200)
                return SendClientMessage(playerid, -1, "O valor deve ser entre $5 a $200.");

            SetPVarInt(playerid, "TaxiCorrida", valor);
            SetPVarInt(playerid, "TaxiCliente", playerclick);
            SetPVarInt(playerclick, "TaxiAtendeu", playerid);

            SendMsgF(playerid, COLOR_LIGHTBLUE, "Voc� ofereceu a corrida por $%s a cada 10 segundos de corrida para o %s. Aguarde a resposta do cliente para iniciar a corrida.", getFormatText(valor), PlayerName[playerclick]);

            new string[128];
            MEGAString[0] = EOS;
            strcat(MEGAString, "{33CCFF}R�dio T�xi diz:\n");
            format(string, 128, "{FFFFFF}O taxista %s est� cobrando $%s a cada 10 segundos de corrida.\n", PlayerName[playerid], getFormatText(valor));
            strcat(MEGAString, string);
            strcat(MEGAString, "Voc� aceita essa corrida?");
			
            ShowPlayerDialog(playerclick, 402, DIALOG_STYLE_MSGBOX, "Proposta de Corrida", MEGAString, "Aceitar", "Rejeitar");
	    }
        return 1;
	}
    else if (dialogid == 402)
	{
        new taxistaid = GetPVarInt(playerid, "TaxiAtendeu");
	    if (response)
		{
			if (!Player_Logado(taxistaid)) 
                return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");
            else if(GetPVarInt(taxistaid, "TaxiEmCorrida"))
                return SendClientMessage(playerid, -1, "O taxista j� iniciou outra corrida.");

            AtenderChamadoTaxi(taxistaid, playerid);
	    }
        return 1;
	}
	return 0;
}