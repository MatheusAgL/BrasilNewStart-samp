CMD:furtarmovel(playerid) {
	new
		movelid = getMovelPerto(playerid),
		casaid = Player_GetInHouse(playerid)
	;

	if (movelid)
	{
		if(GetPVarInt(playerid, "movelRoubou"))
		    return SendClientMessage(playerid, -1 , "Você ja roubou um móvel, agora venda ou troque por drogas!");

		if(!OrgsRoubo(playerid))
	  		return SendClientMessage(playerid, -1 , "Você não pode roubar residências!");

		if (isMovelRoubavel(MobInfo[casaid][movelid][mobModel]))
		{
		    SetPVarInt(playerid, "movelMaconha", random(30)+40);
		    SetPVarInt(playerid, "movelCrack", random(60)+10);
		    SetPVarInt(playerid, "movelCocaina", random(50)+15);
		    SetPVarInt(playerid, "movelRoubou", 1);

			SetPlayerFaceToPoint(playerid, MobInfo[casaid][movelid][mobPos][0], MobInfo[casaid][movelid][mobPos][1]);

			Furniture_Remove(casaid, movelid);

			if (casaid != GetPVarInt(playerid, "casaRoubo"))
			{
			    SendClientMessage(playerid, COLOR_GRAD, "OBS1: Os vizinhos escutaram barulhos e chamaram a polícia, saia daqui o mais rápido possível.");
	            SendClientMessage(playerid, COLOR_GRAD, "OBS2: Art. 155 - Subtrair, para si ou para outrem, coisa alheia móvel.");
	            SetPlayerCriminal(playerid, 255, "Furto em residência");
			}

			SendClientMessage(playerid, COLOR_LIGHTRED, "* Você pegou esse móvel, o alarme foi acionado e os policiais ja foram avisados !");
	        SendClientMessage(playerid, COLOR_LIGHTRED, "* Agora ache um traficante e tente vende-lo ou trocar por drogas.");

			CheckConquista(playerid, Conquista_RouboMovel);

			ShowPlayerBaloonInfo(playerid, "Agora ache um traficante para vender ou trocar", 7000);

			SetPVarInt(playerid, "casaRoubo", casaid);

            ApplyAnimation(playerid, "CARRY", "liftup", 7.1, 0, 1, 1, 0, 0);

		    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

		    SetPlayerAttachedObject(playerid, Slot_Movel, MobInfo[casaid][movelid][mobModel],6,0.162000,0.131000,-0.226000,63.999984,164.399963,-96.100028,1.000000);
		}
	}
	return 1;
}

CMD:comprarmovel(playerid) {
	new House = Player_GetInHouse(playerid);
	if (House == -1) 
		return SendClientMessage(playerid, -1, "Você não está em uma casa que você é o dono/designer!");
	else if (!(House_IsOwner(playerid, House) || Player_GetAccountID(playerid) == HouseInfo[House][hDesignerID]))
		return SendClientMessage(playerid, -1, "Essa casa não é sua ou você não é o designer!");
	else if (!IsPlayerInRangeOfPoint(playerid, 50.0, HouseInfo[House][hSaidaX], HouseInfo[House][hSaidaY], HouseInfo[House][hSaidaZ]))
		return SendClientMessage(playerid, -1, "Você está longe do interior de uma casa onde você seja o dono/designer!");
	else if (Player_GetAccountID(playerid) == HouseInfo[House][hDesigner] && !PlayerIsDesignInterior(playerid))
		return SendClientMessage(playerid, -1, "Você é o designer dessa casa, mas não está mais no emprego!");
	else if (Furniture_Count(House) >= HouseInfo[House][hMaxMoveis])
		return SendClientMessage(playerid, -1, "Sua casa atingiu o limite máximo de móveis. Seja um sócio para aumentar a quantidade.");
				    
	ShowPlayerBaloonInfo(playerid, "Escolha um movel para comprar", 7000);

	ShowPlayerDialog(playerid, 7472, DIALOG_STYLE_LIST, "Escolha uma opção",
	"{999999}Móveis >>{FFFFFF} Quarto\n\
	{999999}Móveis >>{FFFFFF} Sala\n\
	{999999}Móveis >>{FFFFFF} Cozinha\n\
	{999999}Móveis >>{FFFFFF} Banheiro\n\
	{999999}Móveis >>{FFFFFF} Decoracão\n\
	{999999}Móveis >>{FFFFFF} Outros",
	"Escolher", "Sair");
	return 1;
}

CMD:selecionarmovel(playerid) {
	new House = Player_GetInHouse(playerid);
	if (House == -1) 
		return SendClientMessage(playerid, -1, "Você não está em uma casa que você é o dono/designer!");
	else if (!(House_IsOwner(playerid, House) || Player_GetAccountID(playerid) == HouseInfo[House][hDesigner]))
		return SendClientMessage(playerid, -1, "Essa casa não é sua ou você não é o designer!");
	else if (!IsPlayerInRangeOfPoint(playerid, 50.0, HouseInfo[House][hSaidaX], HouseInfo[House][hSaidaY], HouseInfo[House][hSaidaZ]))
		return SendClientMessage(playerid, -1, "Você está longe do interior de uma casa onde você seja o dono/designer!");
	else if (Player_GetAccountID(playerid) == HouseInfo[House][hDesigner] && !PlayerIsDesignInterior(playerid))
		return SendClientMessage(playerid, -1, "Você é o designer dessa casa, mas não está mais no emprego!");

	if(IsAndroidPlayer(playerid)) {
		ShowPlayerBaloonInfo(playerid, "Selecione um dos moveis dentro dessa casa", 7000);
		Furniture_ShowNear(playerid);
	}
	else {
		ShowPlayerBaloonInfo(playerid, "Clique no movel em que voce deseja gerenciar", 7000);
		BeginObjectSelecting(playerid);
	}
	return 1;
}

CMD:resetarmoveis(playerid) {
	new House = Player_GetInHouse(playerid);
	if (House == -1) 
		return SendClientMessage(playerid, -1, "Você não está em uma casa que você é o dono/designer!");
	else if (!(House_IsOwner(playerid, House) || Player_GetAccountID(playerid) == HouseInfo[House][hDesigner]))
		return SendClientMessage(playerid, -1, "Essa casa não é sua ou você não é o designer!");
	else if (!IsPlayerInRangeOfPoint(playerid, 50.0, HouseInfo[House][hSaidaX], HouseInfo[House][hSaidaY], HouseInfo[House][hSaidaZ]))
		return SendClientMessage(playerid, -1, "Você está longe do interior de uma casa onde você seja o dono/designer!");
	else if (Player_GetAccountID(playerid) == HouseInfo[House][hDesigner] && !PlayerIsDesignInterior(playerid))
		return SendClientMessage(playerid, -1, "Você é o designer dessa casa, mas não está mais no emprego!");

	Furniture_Reset(House);
	EndObjectEditing(playerid);
	ShowPlayerBaloonInfo(playerid, "Voce resetou os moveis dessa casa", 7000);
	return 1;
}