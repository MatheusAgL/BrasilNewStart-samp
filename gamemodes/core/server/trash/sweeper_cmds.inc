CMD:iniciarcoleta(playerid)
{
    if (!PlayerIsGari(playerid))  return SendClientMessage(playerid, -1, "Você não é um Gari.");
    if (!Sweeper_GetWork(playerid))  return SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você não está em serviço!");

	new vehicleid = GetPlayerVehicleID(playerid);
    if (!IsPlayerInAnyVehicle(playerid) || GetVehicleModel(vehicleid) != 408) 0000
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