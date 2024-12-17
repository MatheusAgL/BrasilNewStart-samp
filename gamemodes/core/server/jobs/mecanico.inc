#include <YSI_Coding\y_hooks>

new static string[256];

static pmodelid[MAX_PLAYERS];

stock DarPropostaMecanico(playerid, id) {
    if (!GetPVarInt(id, "MecanicoSolicitado"))  
        return SendClientMessage(playerid, -1, "O jogador não solicitou nenhum taxi.");

    if (GetPVarInt(playerid, "MecanicoEmCorrida")) 
        return SendClientMessage(playerid, -1, "Você já está em corrida.");

    SetPVarInt(playerid, "MecanicoCliente", id);
    format(MEGAString, sizeof(MEGAString), "{FFFFFF}Cliente: {33CCFF}%s\n\n{FFFFFF}Digite o valor cobrado para atender o cliente:", PlayerName[id]);
    ShowPlayerDialog(playerid, 501, DIALOG_STYLE_INPUT, "{FFFFFF}Oficina - Proposta", MEGAString, "Ofertar", "Cancelar");
	return 1;
}

stock ServicoMecanico(playerid)
{
    if (GetPVarInt(playerid, "MecanicoSolicitado") == 1 && gettime() < GetPVarInt(playerid, "MecanicoHorario")+120)
        return SendMsgF(playerid, -1, "Você chamou um mecânico, aguarde %s para solicitar novamente.", ConvertTime(GetPVarInt(playerid, "MecanicoHorario")+120 - gettime()));
    else if(GetPlayerInterior(playerid) != 0)
        return SendClientMessage(playerid, -1, "Você não pode chamar um mecânico dentro de um interior.");

    SetPVarInt(playerid, "MecanicoSolicitado", 1);
    SetPVarInt(playerid, "MecanicoHorario", gettime());

    format(string, sizeof(string), "Oficina Mecânica diz: %s, estamos comunicando os mecânicos. Entraremos em contato quando algum estiver a caminho!", PlayerName[playerid]);
    SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

	new MapZone:zone = GetPlayerMapZone2D(playerid);
	new zone_name[MAX_MAP_ZONE_NAME];
	GetMapZoneName(zone, zone_name);

    format(string, sizeof(string), "<< Oficina >> {FFFFFF}%s[%d] está precisando de um mecânico na região de %s. Use /atenderchamado!", PlayerName[playerid], playerid, zone_name);
    EmpregoMensagem(0xE0D78AFF, string, ID_JOB_MECANICO);

    return true;
}

stock ListarChamadosMecanico(playerid)
{
	new players;

	new MapZone:zone;
	new zone_name[MAX_MAP_ZONE_NAME];

	MEGAString [0] = EOS;
	strcat(MEGAString, "Id  Nome\tTempo esperando\tLocalização\n");
	
	foreach(new x : Player)
	{
	    if(GetPVarInt(x, "MecanicoSolicitado") && !GetPVarInt(x, "MecanicoEmCorrida"))
		{
            // Se passou mais de 15 minutos
            if(gettime()-GetPVarInt(x, "MecanicoHorario") >= 300)
            {
                DeletePVar(x, "MecanicoSolicitado");
            }
            else 
            {
				zone = GetPlayerMapZone2D(playerid);
				GetMapZoneName(zone, zone_name);

                format(string, sizeof (string), "{EEEEEE}%02d  %s\t%s\t{00FFFF}%s\n", x, PlayerName[x], ConvertTime(gettime()-GetPVarInt(x, "MecanicoHorario")), zone_name);
                strcat(MEGAString, string);
            
				List_SetPlayers(playerid, players, x);
                players ++;
            }
	    }
	}
	
	format(string, sizeof (string), "Clientes aguardando mecânico ({00FFFF}%d{FFFFFF})", players);
	ShowPlayerDialog(playerid, 400, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Atender", "Fechar");
}

stock AtenderChamadoMecanico(playerid, clienteid)
{
	if(GetPVarInt(clienteid, "MecanicoAtendido"))
        return;

	new MapZone:zone = GetPlayerMapZone2D(clienteid);
	new zone_name[MAX_MAP_ZONE_NAME];
	GetMapZoneName(zone, zone_name);

    format(string, 256, "((Oficina)) {FFFFFF}%s acabou de aceitar o chamado para atender %s em %s.", PlayerName[playerid], PlayerName[clienteid], zone_name);
    EmpregoMensagem(0xE0D78AFF, string, ID_JOB_MECANICO);

    SendMsgF(clienteid, -1, "Oficina Mecânica diz: %s, o mecânica %s está a caminho da sua localização.", PlayerName[clienteid], PlayerName[playerid]);

    SetPVarInt(playerid, "MecanicoEmCorrida", 1);
    SetPVarInt(playerid, "MecanicoCliente", clienteid);
    SetPVarInt(clienteid, "MecanicoAtendido", 1);
    SetPVarInt(clienteid, "MecanicoAtendeu", playerid);

    SetPVarInt(clienteid, "varProcura", playerid);

    TempoProc[playerid] = gettime() + (3 * 60);
    TempoProc[clienteid] = gettime() + (3 * 60);

    stop timer_procurar[clienteid];
	timer_procurar[clienteid] = repeat timerProcurar(clienteid, playerid);

    SetPVarInt(playerid, "varProcura", clienteid);
    stop timer_procurar[playerid];
	timer_procurar[playerid] = repeat timerProcurar(playerid, clienteid);
}

CMD:abastecerveiculo(playerid, params[])
{
	new cliente, money, qtde;
	if(!PlayerIsMecanico(playerid)) return SendClientMessage(playerid, -1, "Você não é mecânico!");
	else if(sscanf(params, "udd", cliente, qtde, money)) return SendClientMessage(playerid, -1, "{FE9A2E}×{ffffff} USE: /abastecercarro [id] [quantidade] [preço]");
	else if(money < 1 || money > 3000) return SendClientMessage(playerid, -1, "O valor deve ser entre $1 e $3000!"); 
	else if(qtde < 1 || qtde > 100) return SendClientMessage(playerid, -1, "O abastecimento deve ser entre 1 e 100.");
	else if(!IsPlayerConnected(cliente) || !Player_Logado(cliente)) return SendClientMessage(playerid, -1, "Jogador offline.");
	else if(!ProxDetectorS(8.0, playerid, cliente) || !IsPlayerInAnyVehicle(cliente)) return SendClientMessage(playerid, -1, "O jogador não está próximo de você ou não está no carro.");
	else if(cliente == playerid) return SendClientMessage(playerid, -1, "Você não pode se atender!");

	SendMsgF(playerid, COLOR_LIGHTBLUE, "Você ofereceu abastecimento de veículo a %s por $%s.", PlayerName[cliente], getFormatText(money));
	SendMsgF(cliente, COLOR_LIGHTBLUE, "O mecânico %s quer abastecer seu veículo por por $%s. Digite /aceitar abastecimento para confirmar!", PlayerName[playerid], getFormatText(money));
	SetPVarInt(cliente, "mecanicoAbastecimentoOferta", 1);
	SetPVarInt(cliente, "mecanicoAbastecimentoId", playerid);
	SetPVarInt(cliente, "mecanicoAbastecimentoPreco", money);
	return 1;
}

CMD:repararveiculo(playerid, params[])
{
	new cliente, money;
	if(!PlayerIsMecanico(playerid)) return SendClientMessage(playerid, -1, "Você não é mecânico!");
	else if(sscanf(params, "ud", cliente, money)) return SendClientMessage(playerid, -1, "{FE9A2E}×{ffffff} USE: /repararveiculo [id] [preço]");
	else if(money < 1 || money > 5000) return SendClientMessage(playerid, -1, "O valor deve ser entre $1 e $5000!"); 
	else if(!IsPlayerConnected(cliente) || !Player_Logado(cliente)) return SendClientMessage(playerid, -1, "Jogador offline.");
	else if(!ProxDetectorS(8.0, playerid, cliente) || !IsPlayerInAnyVehicle(cliente)) return SendClientMessage(playerid, -1, "O jogador não está próximo de você ou não está em um veículo.");
	else if(cliente == playerid) return SendClientMessage(playerid, -1, "Você não pode se atender!");

	SendMsgF(playerid, COLOR_LIGHTBLUE, "Você ofereceu reparo de veículo a %s por $%s.", PlayerName[cliente], getFormatText(money));
	SendMsgF(cliente, COLOR_LIGHTBLUE, "O mecânico %s quer reparar seu veículo por por $%s. Digite /aceitar reparo para confirmar!", PlayerName[playerid], getFormatText(money));
	SetPVarInt(cliente, "mecanicoReparoOferta", 1);
	SetPVarInt(cliente, "mecanicoReparoId", playerid);
	SetPVarInt(cliente, "mecanicoReparoPreco", money);
	return 1;
}

LimparDadosMecanico(playerid)
{
	DeletePVar(playerid, "MecanicoAtendeu");
	DeletePVar(playerid, "MecanicoTotalCorrida");
	DeletePVar(playerid, "MecanicoEmCorrida");
	DeletePVar(playerid, "MecanicoCliente");
	DeletePVar(playerid, "MecanicoAtendido");
	DeletePVar(playerid, "MecanicoSolicitado");
	DeletePVar(playerid, "MecanicoHorario");
}

CMD:cancelarmecanico(playerid)
{
    if (!GetPVarInt(playerid, "MecanicoSolicitado") && !GetPVarInt(playerid, "MecanicoAtendido"))  
        return SendClientMessage(playerid, -1, "Você não solicitou um mecânico ou não atendeu uma corrida.");

    new 
        taxistaid = GetPVarInt(playerid, "MecanicoAtendeu"),
        passageiroid = GetPVarInt(playerid, "MecanicoCliente");

    //Se o jogador for o passageiro
    if(GetPVarInt(playerid, "MecanicoSolicitado"))
    {
        if(GetPVarInt(playerid, "MecanicoEmCorrida"))
            return SendClientMessage(playerid, COLOR_GRAD, "Você não pode cancelar o chamado após o mecânico ter aceito.");

        SendClientMessage(playerid, -1, "Você cancelou o chamado de mecânico.");
        SendClientMessage(taxistaid, -1, "O cliente cancelou o chamado da corrida.");

        LimparDadosMecanico(taxistaid);
    }
    //Se  o jogador for o  taxista
    else 
    {
        if(GetPVarInt(playerid, "MecanicoEmCorrida"))
            return SendClientMessage(playerid, COLOR_GRAD, "Você não pode cancelar o chamado após ter aceito.");

        SendClientMessage(playerid, -1, "Você cancelou o chamado com o passageiro.");
        SendClientMessage(passageiroid, -1, "O mecânico cancelou o chamado. Chame outro mecanico usando /servico mecanico.");

        LimparDadosMecanico(passageiroid);
    }

    LimparDadosMecanico(playerid);
    return true;
}

AceitarOfertaMecanico(playerid, tipo)
{
	new op[15], verbo[15];
	format(op, 15, (tipo == 1) ? ("Abastecimento") : ("Reparo"));
	format(verbo, 15, (tipo == 1) ? ("abasteceu") : ("reparou"));
	format(string, sizeof(string), "mecanico%sOferta", op);
	if(GetPVarInt(playerid, string) == 0)
		return SendClientMessage(playerid, -1, "Você não recebeu uma oferta por um mecânico.");

	format(string, sizeof(string), "mecanico%sId", op);
	new mecanico = GetPVarInt(playerid, string);
	format(string, sizeof(string), "mecanico%sPreco", op);
	new preco = GetPVarInt(playerid, string);
	new veh = GetPlayerVehicleID(playerid);
	new custo = 0;

	if(!ProxDetectorS(8.0, playerid, mecanico) || !IsPlayerInAnyVehicle(playerid)) 
		return SendClientMessage(playerid, -1, "O mecânico não está próximo de você ou você não está em um veículo.");
	else if(Player_GetMoney(playerid) < preco)
		return SendClientMessage(playerid, -1, "Você não possui dinheiro o suficiente para pagar o mecânico.");

	if(tipo == 1) {
		new qtd = GetPVarInt(playerid, "mecanicoAbastecimentoQtde");
		custo = qtd * 3;
		VehicleInfo[veh][vehicleCombustivel] += qtd;
		if(VehicleInfo[veh][vehicleCombustivel] > 100)
			VehicleInfo[veh][vehicleCombustivel] = 100;
		SetPVarInt(playerid, "mecanicoAbastecimentoOferta", 0);
	}
	else if(tipo == 2) {
		new Float:health;
		GetVehicleHealth(veh, health);
		custo = floatround((1000.0 - health) * 0.8);
		SetVehicleHealth(veh, 1000.0);
		RepairVehicle(veh);
		SetPVarInt(playerid, "mecanicoReparoOferta", 0);
	}
	
	Player_RemoveMoney(playerid, preco);
	Player_AddMoney(mecanico, (preco-custo));

	SendMsgF(playerid, COLOR_LIGHTBLUE, "* O mecânico %s %s seu veículo por $%s.", PlayerName[mecanico], verbo, getFormatText(preco));
	SendMsgF(mecanico, COLOR_LIGHTBLUE, "* Você %s o carro de %s e recebeu $%s pelo serviço com custos de $%s.", verbo, PlayerName[playerid], getFormatText(preco), getFormatText(custo));
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == 500)
	{
	    if (response && listitem >= 0)
		{
	        new playerclick = List_GetPlayers(playerid, listitem);
			if (!Player_Logado(playerclick)) 
                return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

            SetPVarInt(playerid, "PlayerClick", playerclick);
			format(string, sizeof (string), "%d", playerclick);
			callcmd::atenderchamado(playerid, string);
	    }
        return 1;
	}
    else if (dialogid == 501)
	{
	    if (response && strlen(inputtext))
		{
	        new playerclick = GetPVarInt(playerid, "PlayerClick"), valor = strval(inputtext);
			if (!Player_Logado(playerclick)) 
                return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");
            else if(valor < 5 || valor > 200)
                return SendClientMessage(playerid, -1, "O valor deve ser entre $5 a $200.");

            SetPVarInt(playerid, "MecanicoCorrida", valor);
            SetPVarInt(playerid, "MecanicoCliente", playerclick);
            SetPVarInt(playerclick, "MecanicoAtendeu", playerid);

            SendMsgF(playerid, COLOR_LIGHTBLUE, "Você cobrou $%s para ir ao local atender %s. Aguarde a resposta do cliente para iniciar a corrida.", getFormatText(valor), PlayerName[playerclick]);

            MEGAString[0] = EOS;
            strcat(MEGAString, "{33CCFF}Oficina Mecânica diz:\n");
            format(string, 128, "{FFFFFF}O mecânico %s está cobrando $%s para ir até sua localização lhe atender.\n", PlayerName[playerid], getFormatText(valor));
            strcat(MEGAString, string);
            strcat(MEGAString, "Você aceita essa proposta?");
			
            ShowPlayerDialog(playerclick, 502, DIALOG_STYLE_MSGBOX, "Proposta de Atendimento", MEGAString, "Aceitar", "Rejeitar");
	    }
        return 1;
	}
    else if (dialogid == 502)
	{
        new taxistaid = GetPVarInt(playerid, "MecanicoAtendeu");
	    if (response)
		{
			if (!Player_Logado(taxistaid)) 
                return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");
            else if(GetPVarInt(taxistaid, "MecanicoEmCorrida"))
                return SendClientMessage(playerid, -1, "O mecânico já iniciou outra corrida.");

            AtenderChamadoMecanico(taxistaid, playerid);
	    }
        return 1;
	}
	// Menu de Tunning
	else if(dialogid == 505) {
		if(response) {
			new modelosWheel[] = {562, 565, 559, 561, 560, 558}, wheel;
			new modelosLocos[] = {575, 534, 567, 536, 535, 576}, locos;

			for(new i = 0; i < sizeof(modelosWheel); i++)
				if(pmodelid[playerid] == modelosWheel[i])
					wheel = 1;

			for(new i = 0; i < sizeof(modelosLocos); i++)
				if(pmodelid[playerid] == modelosLocos[i])
					locos = 1;

			MEGAString[0] = EOS;

			if(listitem == 0) {
				ShowPlayerDialog(playerid, 506, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", "Paintjob 1\nPaintjob 2\nPaintjob 3\nPaintjob 4\nPaintjob 5\nVoltar", "Avançar", "Cancelar");
			}
			else if(listitem == 1) {
				if(wheel) 
					strcat(MEGAString, "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\n");
				if(locos)
					strcat(MEGAString, "Locos Low Chromer Exhaust\nLocos Low Slamin Exhaust\n");

				strcat(MEGAString, "Voltar");
				ShowPlayerDialog(playerid, 508, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", MEGAString, "Avançar", "Cancelar");
			}
			else if(listitem == 2) {
				if(wheel) 
					strcat(MEGAString, "Wheel Arch Alien Bumper\nWheel Arch X-Flow Bumper\n");
				if(locos)
					strcat(MEGAString, "Locos Low Chromer Bumper\nLocos Low Slamin Bumper\n");
					
				strcat(MEGAString, "Voltar");
				ShowPlayerDialog(playerid, 509, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", MEGAString, "Avançar", "Cancelar");
			}
			else if(listitem == 3) {
				if(wheel) 
					strcat(MEGAString, "Wheel Arch Alien Bumper\nWheel Arch X-Flow Bumper\n");
				if(locos)
					strcat(MEGAString, "Locos Low Chromer Bumper\nLocos Low Slamin Bumper\n");
					
				strcat(MEGAString, "Voltar");
				ShowPlayerDialog(playerid, 510, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", MEGAString, "Avançar", "Cancelar");
			}
			else if(listitem == 4) {
				if(wheel) 
					strcat(MEGAString, "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\n");
				if(locos)
					strcat(MEGAString, "Locos Low Hardtop Roof\nLocos Low Hardtop Roof\n");
					
				strcat(MEGAString, "Voltar");
				ShowPlayerDialog(playerid, 511, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", MEGAString, "Avançar", "Cancelar");
			}
			else if(listitem == 5) {
				ShowPlayerDialog(playerid, 512, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", "Alien Spoiler\nX-Flow Spoiler\nVoltar", "Avançar", "Cancelar");
			}
			else if(listitem == 6) {
				if(wheel) 
					strcat(MEGAString, "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\n");
				if(locos)
					strcat(MEGAString, "Locos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\n");
					
				strcat(MEGAString, "Voltar");
				ShowPlayerDialog(playerid, 513, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", MEGAString, "Avançar", "Cancelar");
			}
			else if(listitem == 7) {
				ShowPlayerDialog(playerid, 514, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", "Locos Low Chrome Grill\nLocos Low Chrome Bars\nLocos Low Chrome Lights\n\
					Locos Low Chrome Bullbar\nVoltar", "Avançar", "Cancelar");
			}
			else if(listitem == 8) {
				ShowPlayerDialog(playerid, 507, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", "Preto\nBranco\nVermelho\nAzul\nVerde\nAmarelo\nRosa\nMarrom\nCinza\nOuro\nAzul Escuro\n\
					Azul Claro\nVerde\nCinza Claro\nVermelho Escuro\nMarrom Escuro\nVoltar", "Avançar", "Cancelar");
			}
			else if(listitem == 9) {
				ShowPlayerDialog(playerid, 515, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\n\
					Trance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\nVoltar", "Avançar", "Cancelar");
			}
			else if(listitem == 10) {
				ShowPlayerDialog(playerid, 516, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", "Bass Boost\nHidraulica\nVoltar", "Avançar", "Cancelar");
			}
			else if(listitem == 11) {
				ShowPlayerDialog(playerid, 517, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", "2x Nitro\n5x Nitro\n10x Nitro\nVoltar", "Avançar", "Cancelar");
			}
			else if(listitem == 12) {
				ShowPlayerDialog(playerid, 518, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", "Neon: Azul\nNeon: Vermelho\nNeon: Verde\nNeon: Branco\nNeon: Rosa\n\
					Neon: Amarelo\nRemover Neon", "Avançar", "Cancelar");
			}
		}
	}
	else if(dialogid == 506) {
		if(response) {
			new modelos[] = {562, 565, 559, 561, 560, 575, 534, 567, 483, 536, 535, 576, 558};
			for(new i = 0; i < sizeof(modelos); i++) {
				if(pmodelid[playerid] == modelos[i]) {
					new car = GetPlayerVehicleID(playerid);
					ChangeVehiclePaintjob(car, listitem);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} paintjob{FFFFFF} ao veículo");
					break;
				}
			}
			MenuTuning(playerid);
		}
	}
	else if(dialogid == 507) {
		if(response) {
			new cores[] = {0, 1, 3, 79, 86, 6, 126, 66};
			if(listitem >= 0 && listitem < sizeof(cores)) {
				if(Player_GetMoney(playerid) >= 0) {
					new car = GetPlayerVehicleID(playerid);
					ChangeVehicleColor(car, cores[listitem], cores[listitem]);
					SendClientMessage(playerid, -1, "Você mudou a{FFFF00} cor{FFFFFF} do veículo");
				}
				else 
					SendClientMessage(playerid, -1, "[AVISO] Você não pode adicionar isso.");

				MenuTuning(playerid);
			}
		}
	}
	else if(dialogid == 508) {
		if(response) {
			new ind = -1, car = GetPlayerVehicleID(playerid);
			if(IsLocosVehicle(car))
				listitem += 2;

			if(listitem == 0) {
				new modelos[] = {562, 565, 559, 561, 560, 558};
				new componentes[] = {1034, 1046, 1065, 1064, 1028, 1089};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch Alien Exhaust{FFFFFF}.");
				}
			}
			else if(listitem == 1) {
				new modelos[] = {562, 565, 559, 561, 560, 558};
				new componentes[] = {1037, 1045, 1066, 1059, 1029, 1092};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch X-Flow Exhaust{FFFFFF}.");
				}
			}
			else if(listitem == 2) {
				new modelos[] = {575, 534, 567, 536, 535, 576};
				new componentes[] = {1044, 1126, 1129, 1104, 1113, 1136};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Chromer Exhaust{FFFFFF}.");
				}
			}
			else if(listitem == 3) {
				new modelos[] = {575, 534, 567, 536, 535, 576};
				new componentes[] = {1043, 1127, 1132, 1105, 1114, 1135};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Slamin Exhaust{FFFFFF}.");
				}
			}
			MenuTuning(playerid);
		}
	}
	else if(dialogid == 509) {
		if(response) {
			new ind = -1, car = GetPlayerVehicleID(playerid);
			if(IsLocosVehicle(car))
				listitem += 2;

			if(listitem == 0) {
				new modelos[] = {562, 565, 559, 561, 560, 558};
				new componentes[] = {1171, 1153, 1160, 1155, 1169, 1166};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch X-Flow front bumper{FFFFFF}.");
				}
			}
			else if(listitem == 1) {
				new modelos[] = {562, 565, 559, 561, 560, 558};
				new componentes[] = {1172, 1152, 1173, 1157, 1170, 1165};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch X-Flow front bumper{FFFFFF}.");
				}
			}
			else if(listitem == 2) {
				new modelos[] = {575, 534, 567, 536, 535, 576};
				new componentes[] = {1174, 1179, 1189, 1182, 1115, 1191};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;

				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Chromer front bumper{FFFFFF}.");
				}
			}
			else if(listitem == 3) {
				new modelos[] = {575, 534, 567, 536, 535, 576};
				new componentes[] = {1175, 1185, 1188, 1181, 1116, 1190};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;

				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Slamin front bumper{FFFFFF}.");
				}
			}
			MenuTuning(playerid);
		}
	}
	else if(dialogid == 510) {
		if(response) {
			new ind = -1, car = GetPlayerVehicleID(playerid);
			if(IsLocosVehicle(car))
				listitem += 2;

			if(listitem == 0) {
				new modelos[] = {562, 565, 559, 561, 560, 558};
				new componentes[] = {1149, 1150, 1159, 1154, 1141, 1168};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				AddVehicleComponent(car, componentes[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch Alien rear bumper{FFFFFF}.");
			}
			else if(listitem == 1) {
				new modelos[] = {562, 565, 559, 561, 560, 558};
				new componentes[] = {1148, 1151, 1161, 1156, 1140, 1167};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				AddVehicleComponent(car, componentes[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch X-Flow rear bumper{FFFFFF}.");
			}
			else if(listitem == 2) {
				new modelos[] = {575, 534, 567, 536, 535, 576};
				new componentes[] = {1176, 1180, 1187, 1184, 1109, 1192};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				AddVehicleComponent(car, componentes[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Chromer rear bumper{FFFFFF}.");
			}
			else if(listitem == 3) {
				new modelos[] = {575, 534, 567, 536, 535, 576};
				new componentes[] = {1177, 1178, 1186, 1183, 1110, 1193};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				AddVehicleComponent(car, componentes[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Slamin front bumper{FFFFFF}.");
			}
			MenuTuning(playerid);
		}
	}
	else if(dialogid == 511) {
		if(response) {
			new ind = -1, car = GetPlayerVehicleID(playerid);
			if(IsLocosVehicle(car))
				listitem += 2;

			if(listitem == 0) {
				new modelos[] = {562, 565, 559, 561, 560};
				new componentes[] = {1035, 1054, 1067, 1055, 1032};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch Alien roof vent{FFFFFF}.");
				}
			}
			else if(listitem == 1) {
				new modelos[] = {562, 565, 559, 561, 560};
				new componentes[] = {1035, 1053, 1068, 1061, 1033};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch X-Flow roof vent{FFFFFF}.");
				}
			}
			else if(listitem == 2) {
				new modelos[] = {567, 536};
				new componentes[] = {1130, 1128};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Hardtop Roof{FFFFFF}.");
				}
			}
			else if(listitem == 3) {
				new modelos[] = {567, 536};
				new componentes[] = {1131, 1103};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Softtop Roof{FFFFFF}.");
				}
			}
			MenuTuning(playerid);
		}
	}
	else if(dialogid == 512) {
		if(response) {
			new ind = -1, car = GetPlayerVehicleID(playerid);
			if(listitem == 0) {
				new modelos[] = {562, 565, 559, 561, 560};
				new componentes[] = {1147, 1049, 1162, 1158, 1138};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch Alien Spoilers{FFFFFF}.");
				}
			}
			else if(listitem == 1) {
				new modelos[] = {562, 565, 559, 561, 560};
				new componentes[] = {1146, 1150, 1158, 1060, 1139, 1163};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				if (ind != -1) {
					AddVehicleComponent(car, componentes[ind]);
					SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch X-Flow Spoilers{FFFFFF}.");
				}
			}
			MenuTuning(playerid);
		}
	}
	else if(dialogid == 513) {
		if(response) {
			new ind = -1, car = GetPlayerVehicleID(playerid);
			
			if(IsLocosVehicle(car))
				listitem += 2;

			if(listitem == 0) {
				new modelos[] = {562, 565, 559, 561, 560};
				new componentes[] = {1036, 1047, 1069, 1056, 1026, 1090};
				new componentes2[] = {1040, 1051, 1071, 1062, 1027, 1094};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				if(ind == -1)
					return SendMsgF(playerid, -1, "Falha: O componente %d não existe", ind);

				AddVehicleComponent(car, componentes[ind]);
				AddVehicleComponent(car, componentes2[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch Alien Side Skirts{FFFFFF}.");
			}
			else if(listitem == 1) {
				new modelos[] = {562, 565, 559, 561, 560};
				new componentes[] = {1039, 1048, 1070, 1057, 1031, 1093};
				new componentes2[] = {1041, 1052, 1072, 1063, 1030, 1095};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;

				if(ind == -1)
					return SendMsgF(playerid, -1, "Falha: O componente %d não existe", ind);
				
				AddVehicleComponent(car, componentes[ind]);
				AddVehicleComponent(car, componentes2[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Wheel Arch X-Flow Side Skirts{FFFFFF}.");
			}
			else if(listitem == 2) {
				new modelos[] = {575, 536, 576, 567};
				new componentes[] = {1042, 1102, 1134, 1108};
				new componentes2[] = {1099, 1133, 1137, 1107};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;

				if(ind == -1)
					return SendMsgF(playerid, -1, "Falha: O componente %d não existe", ind);
				
				AddVehicleComponent(car, componentes[ind]);
				AddVehicleComponent(car, componentes2[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Chrome Strip Side Skirts{FFFFFF}.");
			}
			else if(listitem == 3) {
				new modelos[] = {534};
				new componentes[] = {1122};
				new componentes2[] = {1101};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				if(ind == -1)
					return SendMsgF(playerid, -1, "Falha: O componente %d não existe", ind);

				AddVehicleComponent(car, componentes[ind]);
				AddVehicleComponent(car, componentes2[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Chrome Flames Side Skirts{FFFFFF}.");
			}
			else if(listitem == 4) {
				new modelos[] = {534};
				new componentes[] = {1106};
				new componentes2[] = {1124};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;

				if(ind == -1)
					return SendMsgF(playerid, -1, "Falha: O componente %d não existe", ind);
				
				AddVehicleComponent(car, componentes[ind]);
				AddVehicleComponent(car, componentes2[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Chrome Arches Side Skirts{FFFFFF}.");
			}
			else if(listitem == 5) {
				new modelos[] = {535};
				new componentes[] = {1118};
				new componentes2[] = {1120};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;
				
				if(ind == -1)
					return SendMsgF(playerid, -1, "Falha: O componente %d não existe", ind);

				AddVehicleComponent(car, componentes[ind]);
				AddVehicleComponent(car, componentes2[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Chrome Trim Side Skirts{FFFFFF}.");
			}
			else if(listitem == 6) {
				new modelos[] = {535};
				new componentes[] = {1119};
				new componentes2[] = {1121};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;

				if(ind == -1)
					return SendMsgF(playerid, -1, "Falha: O componente %d não existe", ind);
				
				AddVehicleComponent(car, componentes[ind]);
				AddVehicleComponent(car, componentes2[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Chrome Wheelcovers{FFFFFF}.");
			}
			MenuTuning(playerid);
		}
	}
	else if(dialogid == 514) {
		if(response) {
			new ind = -1, car = GetPlayerVehicleID(playerid);
			if(listitem == 0) {
				new modelos[] = {534};
				new componentes[] = {1100};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;

				if(ind == -1)
					return SendMsgF(playerid, -1, "Falha: O componente %d não existe", ind);
				
				AddVehicleComponent(car, componentes[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Chrome Grill{FFFFFF}.");
			}
			else if(listitem == 1) {
				new modelos[] = {534};
				new componentes[] = {1123};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;

				if(ind == -1)
					return SendMsgF(playerid, -1, "Falha: O componente %d não existe", ind);
				
				AddVehicleComponent(car, componentes[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Chrome Bars{FFFFFF}.");
			}
			else if(listitem == 2) {
				new modelos[] = {535};
				new componentes[] = {1117};

				for(new i = 0; i < sizeof(modelos); i++) 
					if(modelos[i] == pmodelid[playerid]) 
						ind = i;

				if(ind == -1)
					return SendMsgF(playerid, -1, "Falha: O componente %d não existe", ind);
				
				AddVehicleComponent(car, componentes[ind]);
				SendClientMessage(playerid, -1, "Você adicionou{FFFF00} Locos Low Chrome Lights{FFFFFF}.");
			}
			MenuTuning(playerid);
		}
	}
	else if(dialogid == 515) {
		if(response) {
			new car = GetPlayerVehicleID(playerid);
			new componentes[] = {1025, 1074, 1076, 1078, 1081, 1082, 1085, 1096, 1097, 1098, 1084, 1073, 1075, 1077, 1079, 1080, 1083};
			new nomes[][] = {"Offroad", "Mega", "Wires", "Twist", "Grove", "Import", "Atomic", "Ahab", "Virtual", "Access", "Trance", "Shadow",
				"Rimshine", "Classic", "Cutter", "Switch", "Dollar"};

			if(listitem >= 0 && listitem < sizeof(nomes)) {
				if(Player_GetMoney(playerid) >= 0) {
					AddVehicleComponent(car, componentes[listitem]);
					SendMsgF(playerid, -1, "Você adicionou as rodas para {FFFF00}%s{FFFFFF}.", nomes[listitem]);
				}
				else 
					SendClientMessage(playerid, -1, "[AVISO] Você não pode adicionar isso.");
			}
			MenuTuning(playerid);
		}
	}
	else if(dialogid == 516) {
		if(response) {
			new car = GetPlayerVehicleID(playerid);
			new componentes[] = {1086, 1087};
			new nomes[][] = {"Stereo Bass boost system", "Hidráulica"};

			if(listitem >= 0 && listitem < sizeof(nomes)) {
				if(Player_GetMoney(playerid) >= 0) {
					AddVehicleComponent(car, componentes[listitem]);
					SendMsgF(playerid, -1, "Você adicionou {FFFF00}%s{FFFFFF} ao veículo.", nomes[listitem]);
				}
				else 
					SendClientMessage(playerid, -1, "[AVISO] Você não pode adicionar isso.");
			}
			MenuTuning(playerid);
		}
	}
	else if(dialogid == 517) {
		if(response) {
			new car = GetPlayerVehicleID(playerid);
			new componentes[] = {1008, 1009, 1010};
			new nomes[][] = {"2x Nitro", "5x Nitro", "10x Nitro"};

			if(listitem >= 0 && listitem < sizeof(nomes)) {
				if(Player_GetMoney(playerid) >= 0) {
					AddVehicleComponent(car, componentes[listitem]);
					SendMsgF(playerid, -1, "Você adicionou {FFFF00}%s{FFFFFF} ao veículo.", nomes[listitem]);
				}
				else 
					SendClientMessage(playerid, -1, "[AVISO] Você não pode adicionar isso.");
			}
			MenuTuning(playerid);
		}
	}
	else if(dialogid == 518) {
		if(response) {
			new car = GetPlayerVehicleID(playerid);

			switch (listitem) {
				case 0: {
					AddNeonToVehicle(car, NEON_COLOR_BLUE);

					SendMsgF(playerid, -1, "Você adicionou {FFFF00}Neon azul{FFFFFF} ao veículo.");
				}
				case 1: {
					AddNeonToVehicle(car, NEON_COLOR_RED);

					SendMsgF(playerid, -1, "Você adicionou {FFFF00}Neon vermelho{FFFFFF} ao veículo.");
				}
				case 2: {
					AddNeonToVehicle(car, NEON_COLOR_GREEN);

					SendMsgF(playerid, -1, "Você adicionou {FFFF00}Neon verde{FFFFFF} ao veículo.");
				}
				case 3: {
					AddNeonToVehicle(car, NEON_COLOR_WHITE);

					SendMsgF(playerid, -1, "Você adicionou {FFFF00}Neon branco{FFFFFF} ao veículo.");
				}
				case 4: {
					AddNeonToVehicle(car, NEON_COLOR_PINK);

					SendMsgF(playerid, -1, "Você adicionou {FFFF00}Neon pink{FFFFFF} ao veículo.");
				}
				case 5: {
					AddNeonToVehicle(car, NEON_COLOR_YELLOW);

					SendMsgF(playerid, -1, "Você adicionou {FFFF00}Neon amarelo{FFFFFF} ao veículo.");
				}
				default: {
					RemoveNeonFromVehicle(car);
                	SendClientMessage(playerid, -1, "Você removeu{FFFF00} Todos os Neons{FFFFFF}.");
				}
			}
			MenuTuning(playerid);
		}
	}
	return 1;
}

hook OnPlayerConnect(playerid)
{
	RemoveBuildingForPlayer(playerid, 5551, 2140.5156, -1735.1406, 15.8906, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 2116.7266, -1713.4609, 13.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 2118.0938, -1718.5469, 13.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 2121.3750, -1721.6875, 13.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 2126.5781, -1722.4688, 13.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 5410, 2140.5156, -1735.1406, 15.8906, 0.25);
	return 1;
}

hook OnGameModeInit()
{
    CreateDynamicPickup(1097, 23, 2152.0327,-1727.2501,14.5319);//Vender Minérios
    CreateDynamicPickup(1025, 23, 2161.7061,-1727.4569,14.5319);//Entrada Mina
    CreateDynamic3DTextLabel("Oficina de Tuning\nUse {AFAFAF}/tunar {FFFFFF}para personalizar", 0xFFFFFFFF,2152.0327,-1727.2501,14.5319,10.5);
    CreateDynamic3DTextLabel("Oficina de Tuning\nUse {AFAFAF}/tunar {FFFFFF}para personalizar", 0xFFFFFFFF,2161.7061,-1727.4569,14.5319,10.5);

	new tmpobjid;
	tmpobjid = CreateDynamicObject(10575, 2152.647216, -1735.895996, 17.400230, 0.000000, 85.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 9514, "711_sfw", "sw_sheddoor2", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2168.206542, -1729.110839, 15.931400, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19817, 2151.989501, -1729.435058, 11.610030, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 16640, "a51", "sm_conc_hatch", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2168.206542, -1729.110839, 15.931400, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2163.476806, -1724.381713, 15.931400, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2153.843994, -1724.379028, 15.931400, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2144.230957, -1724.377197, 15.931400, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2139.482666, -1729.108642, 15.931409, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2144.620605, -1729.132568, 17.834899, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2139.482666, -1729.108642, 12.434800, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2144.211181, -1724.380371, 12.434800, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2153.843994, -1724.379028, 12.434800, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2163.476806, -1724.381713, 12.434800, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2168.206542, -1729.110839, 12.434800, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2155.146484, -1729.131103, 12.473299, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "ws_airpt_concrete", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2163.042724, -1729.132202, 12.471300, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "ws_airpt_concrete", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2144.645019, -1729.131103, 12.473299, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "ws_airpt_concrete", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2155.115966, -1729.132324, 17.662900, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2163.042724, -1729.132202, 17.664899, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(19385, 2141.176025, -1733.836791, 15.928831, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2144.386230, -1733.835449, 12.434800, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2141.173095, -1727.103149, 12.434800, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2144.381591, -1727.102539, 12.434800, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2145.905517, -1729.103759, 12.434800, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2141.173095, -1727.103149, 15.931400, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2144.381591, -1727.102539, 15.931400, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19447, 2145.905517, -1729.103759, 15.931400, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2144.386230, -1733.835449, 15.931400, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19385, 2141.176513, -1733.838623, 12.434800, 0.000000, 180.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(2010, 2145.364501, -1733.247192, 12.560310, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4003, "cityhall_tr_lan", "foliage256", 0x00000000);
	tmpobjid = CreateDynamicObject(19385, 2141.176513, -1733.826660, 14.154040, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 16640, "a51", "plaintarmac1", 0x00000000);
	tmpobjid = CreateDynamicObject(19385, 2141.176513, -1733.836669, 15.153630, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 16640, "a51", "plaintarmac1", 0x00000000);
	tmpobjid = CreateDynamicObject(2010, 2139.927734, -1734.271484, 12.540390, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4830, "airport2", "kbplanter_plants1", 0x00000000);
	tmpobjid = CreateDynamicObject(2010, 2142.472167, -1734.315429, 12.540390, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4830, "airport2", "kbplanter_plants1", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2151.109375, -1737.494750, 12.471300, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1259, "billbrd", "ws_oldpainted2", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2161.604980, -1737.495117, 12.471300, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1259, "billbrd", "ws_oldpainted2", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2163.025634, -1737.500488, 12.469300, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1259, "billbrd", "ws_oldpainted2", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 2156.927978, -1733.856567, 15.931400, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(10575, 2161.531005, -1735.855346, 17.400230, 0.000000, 85.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 9514, "711_sfw", "sw_sheddoor2", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2144.620605, -1729.132568, 17.662929, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2155.115966, -1729.132324, 17.834899, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2163.042724, -1729.132202, 17.832899, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2147.588623, -1733.835327, 15.931400, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2166.588623, -1733.759033, 15.931400, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 2157.268798, -1733.844604, 15.931400, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10370, "alleys_sfs", "ws_sandstone1", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2147.588623, -1733.835327, 12.434800, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 2156.927978, -1733.856567, 12.434800, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19430, 2157.268798, -1733.844604, 12.434800, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2166.588623, -1733.759033, 12.434800, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "sl_vicwall01", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2144.666992, -1737.490722, 12.469300, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1259, "billbrd", "ws_oldpainted2", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2141.010253, -1732.116577, 16.234409, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2141.147705, -1728.883056, 16.234409, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2144.272460, -1728.881347, 16.234409, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(19360, 2144.207275, -1732.064453, 16.234409, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(19817, 2161.529296, -1729.669433, 11.610030, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 16640, "a51", "sm_conc_hatch", 0x00000000);
	tmpobjid = CreateDynamicObject(2311, 2166.181396, -1730.897827, 12.557000, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 12821, "alleystuff", "planks01", 0x00000000);
	tmpobjid = CreateDynamicObject(2258, 2147.924072, -1724.471679, 16.484579, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 16093, "a51_ext", "ws_controltowerwin1", 0x00000000);
	tmpobjid = CreateDynamicObject(2258, 2165.585937, -1724.487792, 16.484579, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 16093, "a51_ext", "ws_controltowerwin1", 0x00000000);
	tmpobjid = CreateDynamicObject(2258, 2156.776855, -1724.475341, 16.484579, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 16093, "a51_ext", "ws_controltowerwin1", 0x00000000);
	tmpobjid = CreateDynamicObject(2258, 2152.176269, -1724.476928, 16.484579, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 16093, "a51_ext", "ws_controltowerwin1", 0x00000000);
	tmpobjid = CreateDynamicObject(2258, 2160.958496, -1724.530029, 16.484579, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 16093, "a51_ext", "ws_controltowerwin1", 0x00000000);
	tmpobjid = CreateDynamicObject(3593, 2122.1951, -1726.4116, 13.0495, 0.000000, 0.000000, 40.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(1217, 2119.212890, -1735.429443, 12.928600, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(1217, 2118.037353, -1734.551269, 12.928600, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(1217, 2117.088867, -1735.041259, 12.928600, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(2670, 2118.684570, -1734.030395, 12.656399, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "ws_carparknew2a", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2144.199951, -1733.986083, 7.317242, 0.000000, 0.000000, 89.700035, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2153.793701, -1734.036376, 7.317242, 0.000000, 0.000000, 89.700035, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19377, 2163.479003, -1734.047607, 7.317242, 0.000000, 0.000000, 90.000030, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tmpobjid = CreateDynamicObject(19903, 2154.089843, -1724.869750, 12.545200, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(11709, 2148.440917, -1724.942749, 13.191260, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1502, 2140.387939, -1733.875488, 12.399299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1998, 2141.096435, -1728.682006, 12.559900, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1714, 2140.982421, -1727.591186, 12.560770, 0.000000, 0.000000, 358.290618, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1726, 2145.259277, -1730.364135, 12.560000, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2311, 2143.655517, -1732.210815, 12.560400, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1776, 2145.365478, -1727.871093, 13.670399, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2059, 2143.493896, -1731.047119, 13.090399, 0.000000, 0.000000, 52.666278, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2161, 2143.056396, -1727.196411, 12.558950, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1893, 2141.997802, -1728.335327, 16.649150, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1893, 2142.186767, -1732.242919, 16.649150, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19903, 2163.433837, -1724.933349, 12.545200, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1098, 2158.677978, -1724.900512, 13.037099, 0.000000, 0.000000, 280.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1728, 2167.683593, -1729.055541, 12.556799, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1487, 2166.414062, -1729.222778, 13.265500, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1487, 2166.350097, -1730.953002, 13.265500, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2823, 2166.286865, -1729.507690, 13.061249, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2860, 2166.117919, -1730.297119, 13.061200, 0.000000, 0.000000, 200.783340, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 2166.031494, -1728.116088, 12.649399, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 2157.192871, -1731.992553, 12.649399, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 2166.522949, -1732.575195, 12.649399, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 2147.671142, -1730.795410, 12.649399, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2671, 2148.262939, -1727.432495, 12.571100, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2671, 2156.388916, -1726.302612, 12.571100, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2671, 2162.434570, -1727.662353, 12.571100, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(3632, 2146.641113, -1726.681396, 12.961990, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(3632, 2146.365966, -1727.368408, 12.961990, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(3632, 2154.950439, -1724.961181, 12.961990, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19621, 2155.086181, -1725.144653, 13.531100, 0.000000, 0.000000, 231.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19899, 2156.797851, -1725.000488, 12.558699, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19899, 2167.624755, -1726.149291, 12.558699, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19900, 2146.435791, -1728.267456, 12.559880, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19900, 2159.250488, -1725.698120, 12.559900, 0.000000, 0.000000, 32.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19815, 2151.250976, -1724.455688, 14.981550, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19815, 2160.403564, -1724.478759, 14.981550, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19921, 2146.557373, -1729.212768, 12.643699, 0.000000, 0.000000, 32120.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19921, 2153.961425, -1728.156860, 12.643699, 0.000000, 0.000000, 32120.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1128, 2147.151367, -1731.377807, 12.560199, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1150, 2147.927734, -1729.616088, 12.566049, 0.000000, 0.000000, 6.122260, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1074, 2146.182373, -1730.443115, 13.040300, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1074, 2148.540771, -1733.557983, 13.040300, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1074, 2148.579345, -1732.554931, 12.669300, 0.000000, 270.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1010, 2152.832275, -1725.111938, 13.529939, 0.000000, 0.000000, 10.675700, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1008, 2159.128173, -1725.726806, 13.434889, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2551, 2157.119628, -1733.310058, 13.496100, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2585, 2146.123779, -1732.459594, 13.746100, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1001, 2165.400146, -1725.064331, 12.558090, 0.000000, 0.000000, 0.406040, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1000, 2165.444580, -1725.401367, 12.558190, 0.000000, 0.000000, 358.274200, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1003, 2165.370605, -1726.243896, 12.558219, 0.000000, 0.000000, 0.828570, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1010, 2167.499511, -1726.978149, 13.826359, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1078, 2166.945556, -1726.952026, 13.053899, 0.000000, -10.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1078, 2167.931152, -1728.040771, 13.053899, 0.000000, -10.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1078, 2166.124023, -1726.927368, 12.652899, 0.000000, 270.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2000, 2149.885009, -1724.937866, 12.561470, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2000, 2167.613769, -1732.305419, 12.558500, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19622, 2167.242187, -1733.562255, 13.265999, 10.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19622, 2157.890136, -1733.609863, 13.265999, 10.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19621, 2157.312255, -1733.511962, 15.097599, 0.000000, 0.000000, 120.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19621, 2156.908447, -1733.551635, 15.097599, 0.000000, 0.000000, 170.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19631, 2157.000488, -1733.525024, 14.700900, 0.000000, 90.000000, 80.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19627, 2157.239257, -1733.441650, 14.677599, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19627, 2157.024658, -1733.348632, 14.677599, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19627, 2156.978515, -1733.446411, 14.677599, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19627, 2157.405029, -1733.350830, 14.677599, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19832, 2157.364257, -1733.569213, 14.316880, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19832, 2156.891113, -1733.480712, 14.316900, 0.000000, 0.000000, 30.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19917, 2161.536621, -1725.575927, 12.558329, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(18633, 2157.216064, -1733.516723, 13.984999, 0.000000, 90.000000, 80.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(19627, 2157.344970, -1733.352172, 13.985600, 0.000000, 0.000000, -353.055297, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(18635, 2157.146240, -1733.606079, 13.609700, 90.000000, 90.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(18635, 2157.094970, -1733.469482, 13.609700, 90.000000, 90.000000, 20.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(18634, 2156.690429, -1733.565307, 13.646599, 0.000000, 90.000000, -50.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1893, 2150.796386, -1729.450805, 17.868000, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1893, 2163.750976, -1729.825439, 17.868000, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1893, 2159.770751, -1729.762451, 17.868000, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1893, 2155.130371, -1729.742675, 17.868000, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1412, 2126.665771, -1722.637451, 13.703700, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1412, 2121.414062, -1722.636962, 13.703700, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1412, 2116.149658, -1722.638671, 13.703700, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1412, 2112.625732, -1725.110473, 13.703700, 0.000000, 0.000000, 70.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1412, 2110.822753, -1730.064086, 13.703700, 0.000000, 0.000000, 70.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1412, 2109.022705, -1735.007202, 13.703700, 0.000000, 0.000000, 70.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1412, 2107.830810, -1738.276855, 13.703700, 0.000000, 0.000000, 70.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1412, 2109.602050, -1740.739990, 13.703700, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1412, 2114.872314, -1740.741333, 13.703700, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1412, 2120.131591, -1740.742675, 13.703700, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1358, 2116.105957, -1726.113281, 13.749990, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(3594, 2111.832519, -1736.207519, 13.245900, 0.000000, 0.000000, 10.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(3594, 2119.9658, -1731.0959, 13.2459, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(3593, 2117.541503, -1736.943725, 13.049500, 0.000000, 0.000000, 80.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1217, 2118.331542, -1724.575805, 12.928600, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1217, 2118.718261, -1726.025146, 12.928600, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(918, 2121.5396, -1731.7986, 12.8604, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(918, 2121.5259, -1732.6794, 12.8604, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(918, 2156.983642, -1725.919311, 12.860400, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(918, 2147.071044, -1728.924804, 12.860400, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1222, 2122.052734, -1738.390380, 13.060190, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 2124.145263, -1738.783325, 12.656399, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2670, 2126.290039, -1729.016967, 12.656399, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2671, 2109.642333, -1738.470336, 12.567099, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2671, 2120.514892, -1726.805541, 12.567099, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2671, 2113.870117, -1734.545654, 12.567099, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(2671, 2127.554199, -1730.345581, 12.567099, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1299, 2113.688964, -1730.012207, 12.942350, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1149, 2116.847900, -1729.071044, 12.539859, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1149, 2114.875732, -1738.593750, 12.539859, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1226, 2114.081298, -1724.468139, 16.302299, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1226, 2135.712158, -1724.377319, 16.302299, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1226, 2108.739501, -1740.063598, 16.302299, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1226, 2114.081298, -1724.468139, 16.302299, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1226, 2135.712158, -1724.377319, 16.302299, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1226, 2108.739501, -1740.063598, 16.302299, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1215, 2156.474121, -1734.285278, 12.558380, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1215, 2157.697021, -1734.286254, 12.558380, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
}

CMD:tunar(playerid)
{
	if(PlayerToPoint(2.0, playerid, 2151.9905,-1727.4324,14.1933) || PlayerToPoint(2.0, playerid, 2161.4419,-1727.6823,14.1953)) {
		new PLAYER_STATE:Status = GetPlayerState(playerid);
		if (Status == PLAYER_STATE_DRIVER)
			MenuTuning(playerid);
		else
			SendClientMessage(playerid, -1, "Você não está em um veículo.");
	}
	return 1;
}

stock IsWheelVehicle(vehicleid) {
	new model = GetVehicleModel(vehicleid);
	new modelosLocos[] = {575, 534, 567, 536, 535, 576};

	for(new i = 0; i < sizeof(modelosWheel); i++)
		if(model == modelosWheel[i])
			return 1;

	return 0;
}

stock IsLocosVehicle(vehicleid) {
	new model = GetVehicleModel(vehicleid);
	new modelosLocos[] = {575, 534, 567, 536, 535, 576};

	for(new i = 0; i < sizeof(modelosLocos); i++)
		if(model == modelosLocos[i])
			return 1;

	return 0;
}

stock MenuTuning(playerid)
{
	pmodelid[playerid] = GetVehicleModel(GetPlayerVehicleID(playerid));
	switch(pmodelid[playerid])
	{
		case 562,565,559,561,560,575,534,567,536,535,576,411,579,602,496,518,527,589,597,419,
		533,526,474,545,517,410,600,436,580,439,549,491,445,604,507,585,587,466,492,546,551,516,
		426, 547, 405, 409, 550, 566, 540, 421,	529,431,438,437,420,525,552,416,433,427,490,528,
		407,544,470,598,596,599,601,428,499,609,524,578,486,406,573,455,588,403,514,423,
		414,443,515,456,422,482,530,418,572,413,440,543,583,478,554,402,542,603,475,568,504,457,
		483,508,429,541,415,480,434,506,451,555,477,400,404,489,479,442,458,467,558:
		{
			MEGAString[0] = EOS;
			strcat(MEGAString, "Paint Jobs\n");

			strcat(MEGAString, "Escapamentos\n");
			strcat(MEGAString, "Parachoque Dianteiro\n");
			strcat(MEGAString, "Parachoque Traseiro\n");
			strcat(MEGAString, "Capô\n");

			strcat(MEGAString, "Spoilers\n");

			strcat(MEGAString, "Saias Laterais\n");
			strcat(MEGAString, "Bullbars\n");

			strcat(MEGAString, "Cores\n");
			strcat(MEGAString, "Rodas\n");
			strcat(MEGAString, "Adicionais\n");
			strcat(MEGAString, "Nitro\n");
			//strcat(MEGAString, "Neon\n");

			ShowPlayerDialog(playerid, 505, DIALOG_STYLE_LIST, "{FFFFFF}Tunagem", MEGAString, "Avançar", "Cancelar");
		}
		default: return SendClientMessage(playerid, COLOR_GRAD,"Você não pode tunar este veículo.");
	}
	return 1;
}


