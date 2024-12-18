CMD:furtarmovel(playerid) {
	new
		movelid = getMovelPerto(playerid),
		casaid = Player_GetInHouse(playerid)
	;

	if (movelid)
	{
		if(GetPVarInt(playerid, "movelRoubou"))
		    return SendClientMessage(playerid, -1 , "Voc� ja roubou um m�vel, agora venda ou troque por drogas!");

		if(!OrgsRoubo(playerid))
	  		return SendClientMessage(playerid, -1 , "Voc� n�o pode roubar resid�ncias!");

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
			    SendClientMessage(playerid, COLOR_GRAD, "OBS1: Os vizinhos escutaram barulhos e chamaram a pol�cia, saia daqui o mais r�pido poss�vel.");
	            SendClientMessage(playerid, COLOR_GRAD, "OBS2: Art. 155 - Subtrair, para si ou para outrem, coisa alheia m�vel.");
	            SetPlayerCriminal(playerid, 255, "Furto em resid�ncia");
			}

			SendClientMessage(playerid, COLOR_LIGHTRED, "* Voc� pegou esse m�vel, o alarme foi acionado e os policiais ja foram avisados !");
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
		return SendClientMessage(playerid, -1, "Voc� n�o est� em uma casa que voc� � o dono/designer!");
	else if (!(House_IsOwner(playerid, House) || Player_GetAccountID(playerid) == HouseInfo[House][hDesignerID]))
		return SendClientMessage(playerid, -1, "Essa casa n�o � sua ou voc� n�o � o designer!");
	else if (!IsPlayerInRangeOfPoint(playerid, 50.0, HouseInfo[House][hSaidaX], HouseInfo[House][hSaidaY], HouseInfo[House][hSaidaZ]))
		return SendClientMessage(playerid, -1, "Voc� est� longe do interior de uma casa onde voc� seja o dono/designer!");
	else if (Player_GetAccountID(playerid) == HouseInfo[House][hDesigner] && !PlayerIsDesignInterior(playerid))
		return SendClientMessage(playerid, -1, "Voc� � o designer dessa casa, mas n�o est� mais no emprego!");
	else if (Furniture_Count(House) >= HouseInfo[House][hMaxMoveis])
		return SendClientMessage(playerid, -1, "Sua casa atingiu o limite m�ximo de m�veis. Seja um s�cio para aumentar a quantidade.");
				    
	ShowPlayerBaloonInfo(playerid, "Escolha um movel para comprar", 7000);

	ShowPlayerDialog(playerid, 7472, DIALOG_STYLE_LIST, "Escolha uma op��o",
	"{999999}M�veis >>{FFFFFF} Quarto\n\
	{999999}M�veis >>{FFFFFF} Sala\n\
	{999999}M�veis >>{FFFFFF} Cozinha\n\
	{999999}M�veis >>{FFFFFF} Banheiro\n\
	{999999}M�veis >>{FFFFFF} Decorac�o\n\
	{999999}M�veis >>{FFFFFF} Outros",
	"Escolher", "Sair");
	return 1;
}

CMD:selecionarmovel(playerid) {
	new House = Player_GetInHouse(playerid);
	if (House == -1) 
		return SendClientMessage(playerid, -1, "Voc� n�o est� em uma casa que voc� � o dono/designer!");
	else if (!(House_IsOwner(playerid, House) || Player_GetAccountID(playerid) == HouseInfo[House][hDesigner]))
		return SendClientMessage(playerid, -1, "Essa casa n�o � sua ou voc� n�o � o designer!");
	else if (!IsPlayerInRangeOfPoint(playerid, 50.0, HouseInfo[House][hSaidaX], HouseInfo[House][hSaidaY], HouseInfo[House][hSaidaZ]))
		return SendClientMessage(playerid, -1, "Voc� est� longe do interior de uma casa onde voc� seja o dono/designer!");
	else if (Player_GetAccountID(playerid) == HouseInfo[House][hDesigner] && !PlayerIsDesignInterior(playerid))
		return SendClientMessage(playerid, -1, "Voc� � o designer dessa casa, mas n�o est� mais no emprego!");

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
		return SendClientMessage(playerid, -1, "Voc� n�o est� em uma casa que voc� � o dono/designer!");
	else if (!(House_IsOwner(playerid, House) || Player_GetAccountID(playerid) == HouseInfo[House][hDesigner]))
		return SendClientMessage(playerid, -1, "Essa casa n�o � sua ou voc� n�o � o designer!");
	else if (!IsPlayerInRangeOfPoint(playerid, 50.0, HouseInfo[House][hSaidaX], HouseInfo[House][hSaidaY], HouseInfo[House][hSaidaZ]))
		return SendClientMessage(playerid, -1, "Voc� est� longe do interior de uma casa onde voc� seja o dono/designer!");
	else if (Player_GetAccountID(playerid) == HouseInfo[House][hDesigner] && !PlayerIsDesignInterior(playerid))
		return SendClientMessage(playerid, -1, "Voc� � o designer dessa casa, mas n�o est� mais no emprego!");

	Furniture_Reset(House);
	EndObjectEditing(playerid);
	ShowPlayerBaloonInfo(playerid, "Voce resetou os moveis dessa casa", 7000);
	return 1;
}