#include <YSI_Coding\y_hooks>


new Text3D:transporte_Text [MAX_VEHICLES] = {Text3D:-1, ...};
new transporte_Area        [MAX_VEHICLES] = {-1, ...};
new transporte_Ammount     [MAX_VEHICLES] = {0, ...};

hook OnPlayerEnterDynamicArea(playerid, areaid)
{
	checkTransporteArea(playerid, areaid);
	return 1;
}

stock createAviaoTransporte(vehicleid) {

	transporte_Area[vehicleid] = CreateDynamicSphere(0.0, -4.0, 0.0, 8.0);
	transporte_Text[vehicleid] = CreateDynamic3DTextLabel("Produtos: 0/100", 0xFFFFFFF2, 0.0, 0.0, 0.0, 10.0, INVALID_PLAYER_ID, vehicleid);
	
	AttachDynamicAreaToVehicle(transporte_Area[vehicleid], vehicleid);
}

stock transporteAddCar(vehicleid, specifcvalue = -1) {


	if ( specifcvalue == -1 ) {

		specifcvalue = random(2) + 1;
	} 
	
	new string[45];
	
	transporte_Ammount[vehicleid] += specifcvalue;
	
	if (transporte_Ammount[vehicleid] >= 100) {
	    transporte_Ammount[vehicleid] = 100;
	}
	format(string, sizeof string, "Produtos: %d/100", transporte_Ammount[vehicleid]);
	UpdateDynamic3DTextLabelText(transporte_Text[vehicleid], 0xFFFFFFF2, string);
}

CMD:iniciartransporte(playerid) {

    if (PlayerInfo[playerid][pEmprego] != 27) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é um Transportador!");

    if (!IsPlayerInAnyVehicle(playerid) || GetVehicleModel(GetPlayerVehicleID(playerid)) != 553) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está no Avião de Transporte!");

	new rdon = random(2);
	
	if (rdon == 1) {
	    SetPlayerCheckpoint(playerid, -1272.3809,-633.5328,14.1484, 10.0);
	} else {
	    SetPlayerCheckpoint(playerid, 1348.3610,1756.4521,10.8203, 10.0);
	}
	
    new string[75];

    SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você iniciou um transporte aéreo, siga a marca vermelha em seu mapa para pegar os produtos!");

	format(string, sizeof(string), "* %s iniciou um transporte", PlayerName[playerid]);
	SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	return 1;
}

CMD:cancelartransporte(playerid) {

    if (PlayerInfo[playerid][pEmprego] != 27) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é um Transportador!");

	if (GetPVarInt(playerid, "pegouTransporte")) {
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	}

	RemovePlayerAttachedObject(playerid, Slot_Pizza);
	SetPVarInt(playerid, "pegouTransporte", 0);
	SendClientMessage(playerid, COLOR_LIGHTRED, "* Você cancelou o transporte!");
	DisablePlayerCheckpoint(playerid);
	return 1;
}

CMD:entregarprodutos(playerid) {

    if (PlayerInfo[playerid][pEmprego] != 27) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é um Transportador!");
    
    if (!IsPlayerInRangeOfPoint(playerid, 40.0, 1995.0183,-2380.5210,13.5469)) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está no local de entrega dos produtos!");

    if (!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está em avião de transporte!");

	new vehicleid = GetPlayerVehicleID(playerid);
	
	if (transporte_Ammount[vehicleid] > 0) {

	    new string[144];
	    
	    new cost = transporte_Ammount[vehicleid] * 25;
	    
	    format(string, sizeof string, "* Você entregou %d produtos, foi adicionado ao seu salário +$%s!", transporte_Ammount[vehicleid], getFormatText(cost));
	    SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	    
		format(string, sizeof(string), "* %s entregou %d produtos e ganhou $%s", PlayerName[playerid], transporte_Ammount[vehicleid], getFormatText(cost));
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	    Player_AddMoney(playerid, cost);
	    
	    transporte_Ammount[vehicleid] = 0;
	    transporteAddCar(vehicleid, 0);
	    
	    DisablePlayerCheckpoint(playerid);
	
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTRED, "* Este veículo não tem produtos para entregar!");
	}
	
	return 1;
}

CMD:pegarproduto(playerid) {

    if (PlayerInfo[playerid][pEmprego] != 27) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não é um Transportador!");

	if (GetPVarInt(playerid, "pegouTransporte")) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você já está com produtos em mãos, entregue no avião!");
	
	if (!IsPlayerInRangeOfPoint(playerid, 8.0, 1348.3610,1756.4521,10.8203) && !IsPlayerInRangeOfPoint(playerid, 8.0, -1272.3809,-633.5328,14.1484))
		return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está em um dos locais onde pega produtos !");
	
 	SetPVarInt(playerid, "pegouTransporte", 1);
    SetPlayerAttachedObject(playerid, Slot_Pizza, 1221,6,0.345000,0.399999,-0.397999,-25.300006,0.000000,0.000000,1.000000,1.000000,1.000000);
    ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle",4.1,0,1,1,0,0);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    SendClientMessage(playerid, COLOR_YELLOW, "* Você pegou produtos, entregue no avião!");
	    
	return 1;
}

stock checkTransporteArea(playerid, areaid) {

	if (PlayerInfo[playerid][pEmprego] != 27) return 0;

    if (!GetPVarInt(playerid, "pegouTransporte")) return 0;

	for(new avioes; avioes != MAX_VEHICLES; avioes++) {
	
	    if (areaid == transporte_Area[avioes]) {

			if (transporte_Ammount[avioes] >= 100)  {

				RemovePlayerAttachedObject(playerid, Slot_Pizza);
				SetPVarInt(playerid, "pegouTransporte", 0);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

				return SendClientMessage(playerid, COLOR_LIGHTRED, "* Este avião está cheio, volte para o local de entrega de produtos e use /entregarprodutos!");
			}

            transporteAddCar(avioes);

			RemovePlayerAttachedObject(playerid, Slot_Pizza);
			SetPVarInt(playerid, "pegouTransporte", 0);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			
			if (transporte_Ammount[avioes] < 100) {
			
		     	SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você colocou produtos no avião, continue pegando as caixas !");
			} else {
			
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* O avião está cheio! Vá ao local de entrega que foi marcado no seu mapa e digite /entregarprodutos.");
				SetPlayerCheckpoint(playerid, 1995.0183,-2380.5210,13.5469, 25.0);
			}

			break;
	    }
	}
	return 1;
}





