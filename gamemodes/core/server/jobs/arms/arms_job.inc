CALLBACK:trabalhoFabricante_Start(playerid, percent)
{
    new	string[178], rdon = random(6);

    if (percent >= 100)
	{
	    if (OwnerFabricaMateriais != 12 && OwnerFabricaMateriais != 13 && OwnerFabricaMateriais != 24)
		{
			format(string, sizeof(string), "* %s fabricou 100g de materiais.", PlayerName[playerid]);
			addQuantiaItem(playerid, ITEM_TYPE_MATERIAL, 2040, 100, "Material", 0, 0);
			PlayerInfo[playerid][produtosMateriais] -= 100;
  		}
		else
		{
			format(string, sizeof(string), "* %s fabricou 100g de materiais e pagou 10 materiais para a máfia.", PlayerName[playerid]);
			addQuantiaItem(playerid, ITEM_TYPE_MATERIAL, 2040, 90, "Material", 0, 0);
			propinaMateriais += 10; 
			PlayerInfo[playerid][produtosMateriais] -= 100;
		}
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		format(string, sizeof string, "Fábrica de Materiais\n\n{FFFFFF}Use: {E3DA7B}/dominar{FFFFFF} para tomar o local\nDominado por: {%s}%s\n{FFFFFF}Propina de materiais: {E3AC5E}%sg",
		GetOrgColor(OwnerFabricaMateriais), GetOrgName(OwnerFabricaMateriais), getFormatText(propinaMateriais)); UpdateDynamic3DTextLabelText(OwnerFabricaMateriaisText, 0x89DFE5F9, string);

		TogglePlayerControllable(playerid, true); FabricandoMateriais[playerid] = false;

		ClearAnimations(playerid);

        DestroyDynamicObject(GetPVarInt(playerid, "objectCreateMateriais")); DeletePVar(playerid, "objectCreateMateriais");

		DestroyDynamic3DTextLabel(textFabricandoMat[playerid]); SetPVarInt(playerid, "timerTrabalho_Fabricante", -1);
	}
	else
	{
	    percent += 5;

	    switch(rdon)
		{
			case 1:		ApplyAnimation(playerid, "OTB", "betslp_tnk", 4.1, false, true, true, true, 1, SYNC_ALL);
		    case 2,3:	ApplyAnimation(playerid, "OTB", "betslp_lkabt", 4.1, false, true, true, true, 1, SYNC_ALL);
			default:	ApplyAnimation(playerid, "OTB", "betslp_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
		}

	    format(string, sizeof string, "Fabricando... %sg", getFormatText(percent));
		UpdateDynamic3DTextLabelText(textFabricandoMat[playerid], 0xDBA75BF9, string);

        SetPVarInt(playerid, "timerTrabalho_Fabricante", SetTimerEx("trabalhoFabricante_Start", 1000, false, "ii", playerid, percent));
	}
}

CMD:materiais(playerid, params[])
{
    if (sscanf(params, "s[128]", params))
	{
	    SendClientMessage(playerid, -1, "Modo de uso: /materiais (nome) (quantidade)");
	    SendClientMessage(playerid, COLOR_GRAD, "NOMES: produtos | fabricar | vender | aceitar | pedidos | propina | cancelar");
 		SendClientMessage(playerid, COLOR_GRAD, "_________________________________________________");
		return true;
	}

	new string[128], null[25];

	if (strfind(params, "aceitar", true) != -1)
	{
		new quantMat = GetPVarInt(playerid, "ofertaMateriais_Gramas");
		new idPlayer = GetPVarInt(playerid, "ofertaMateriais_ID");
		new valorMat = GetPVarInt(playerid, "ofertaMateriais_Valor");

		if (idPlayer == INVALID_PLAYER_ID) return SendClientMessage(playerid, -1, "Você não recebeu nenhuma oferta de materiais.");

		if (!ProxDetectorS(8.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Você não está próximo da pessoa que te ofereceu.");

	    if (Player_GetMoney(playerid) < valorMat) return SendClientMessage(playerid, -1, "Você não tem esse valor em mãos.");

	    if (GetPlayerItemTypeAmount(idPlayer, ITEM_TYPE_MATERIAL) < quantMat) return SendClientMessage(playerid, -1, "O jogador não tem mais essa quantidade de materiais em mãos."), idPlayer = INVALID_PLAYER_ID;

		new saldoMateriais = GetPlayerItemTypeAmount(playerid, ITEM_TYPE_MATERIAL);
		if ((saldoMateriais + quantMat) > 2000)
		{
			SendMsgF(playerid, COLOR_YELLOW, "Você possui %sg de materiais, você poderá comprar apenas %sg.", getFormatText(saldoMateriais), getFormatText(2000 - saldoMateriais));
			return SendClientMessage(playerid, -1, "Limite por jogador é 2,000g de materiais, não podendo ultrapassar.");
		}

		format(string, sizeof(string), "* %s aceitou a oferta de %sg de materiais feita por %s.", PlayerName[playerid], getFormatText(quantMat), PlayerName[idPlayer]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		addQuantiaItem(playerid, ITEM_TYPE_MATERIAL, 2040, quantMat, "Material", 0, 0);
		RemovePlayerItemTypeAmount(idPlayer, ITEM_TYPE_MATERIAL, quantMat);

		Player_RemoveMoney(playerid, valorMat);
		Player_AddMoney(idPlayer, valorMat);

		SetPVarInt(playerid, "ofertaMateriais_ID", INVALID_PLAYER_ID);
	}

	else if (strfind(params, "produtos", true) != -1)
	{
	    if (!PlayerIsFabricanteMat(playerid) && !PlayerIsMafia(playerid)) return SendClientMessage(playerid, -1, "Você não é um fabricante de armas.");

	    if (!IsPlayerInRangeOfPoint(playerid, 5.0, -960.2817, 1855.4542, 9.0000)) return SendClientMessage(playerid, -1, "Você não está no local de comprar produtos (dentro da fábrica).");

		new quantProdutos;
		if (sscanf(params, "s[25]d", null, quantProdutos)) return SendClientMessage(playerid, -1, "Modo de uso: /materiais produtos (quantidade)");

		new valorProdutos = quantProdutos*1;

		if (quantProdutos < 1 || quantProdutos > 1000) return SendClientMessage(playerid, -1, "Você apenas pode comprar entre 1 a 1000 produtos.");

		if ((PlayerInfo[playerid][produtosMateriais] + quantProdutos) > 1000) return SendClientMessage(playerid, -1, "Você pode ter apenas 1.000 produtos de materiais.");

		PlayerInfo[playerid][produtosMateriais] += quantProdutos;
		Player_RemoveMoney(playerid, valorProdutos);
		DepositPropertie(playerid, valorProdutos);

		format(string, sizeof(string), "* %s comprou %s produtos e pagou $%s para a fábrica.", PlayerName[playerid], getFormatText(quantProdutos), getFormatText(valorProdutos));
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
	}

	else if (!strcmp(params, "fabricar", true))
	{
	    if (!PlayerIsFabricanteMat(playerid) && !PlayerIsMafia(playerid)) return SendClientMessage(playerid, -1, "Você não é um fabricante de armas.");

		if (PlayerInfo[playerid][produtosMateriais] < 100) return SendClientMessage(playerid, -1, "Você precisa ter 100 produtos ou mais para fabricar materiais.");

		new saldoMateriais = GetPlayerItemTypeAmount(playerid, ITEM_TYPE_MATERIAL);
		if ((saldoMateriais + 100) > 2000 && Player_GetVIP(playerid) < SOCIO_EXTREME) return SendClientMessage(playerid, -1, "Você pode ter apenas 2,000g de materiais, venda para uma organização.");

		if ((saldoMateriais + 100) > 3000) return SendClientMessage(playerid, -1, "Você pode ter apenas 3,000g de materiais, venda para uma organização.");

		if (FabricandoMateriais[playerid]) return SendClientMessage(playerid, -1, "Você já está fabricando materiais, aguarde terminar!");

	    new Float:ObjectPos[3], Float:ObjectPos2[3];

	    GetDynamicObjectPos(object_Fabricar[0], ObjectPos[0], ObjectPos[1], ObjectPos[2]);
	    GetDynamicObjectPos(object_Fabricar[1], ObjectPos2[0], ObjectPos2[1], ObjectPos2[2]);

	    if (IsPlayerInRangeOfPoint(playerid, 3.0, ObjectPos[0], ObjectPos[1], ObjectPos[2]))
		{
		    new rdon = random(3);

		    SetPlayerPos(playerid, ObjectPos[0] + 1.0, ObjectPos[1] + 1.0 - rdon, ObjectPos[2] + 1.0);
		    SetPlayerFacingAngle(playerid, 88.0434);

		    SetPVarInt(playerid, "objectCreateMateriais", CreateDynamicObject(2040, ObjectPos[0] + 0.5, ObjectPos[1] + 1.0 - rdon, ObjectPos[2] + 1.2, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid)));

		    format(string, sizeof string, "Fabricando... %sg", getFormatText(1));
			textFabricandoMat[playerid] = CreateDynamic3DTextLabel(string, 0xDBA75BF9, ObjectPos[0] + 0.5, ObjectPos[1] + 1.0 - rdon, ObjectPos[2] + 1.2, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GetPlayerVirtualWorld(playerid));

			SetPVarInt(playerid, "timerTrabalho_Fabricante", SetTimerEx("trabalhoFabricante_Start", 1200, false, "ii", playerid, 1));

		    TogglePlayerControllable(playerid, false); FabricandoMateriais[playerid] = true;
		}
		else if (IsPlayerInRangeOfPoint(playerid, 3.0, ObjectPos2[0], ObjectPos2[1], ObjectPos2[2]))
		{
            new rdon = random(3);

		    SetPlayerPos(playerid, ObjectPos2[0] + 1.0, ObjectPos2[1] + 1.0 - rdon, ObjectPos2[2] + 1.0);
		    SetPlayerFacingAngle(playerid, 88.0434);

		    SetPVarInt(playerid, "objectCreateMateriais", CreateDynamicObject(2040, ObjectPos2[0] + 0.5, ObjectPos2[1] + 1.0 - rdon, ObjectPos2[2] + 1.2, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid)));

		    format(string, sizeof string, "Fabricando... %sg", getFormatText(1));
			textFabricandoMat[playerid] = CreateDynamic3DTextLabel(string, 0xDBA75BF9, ObjectPos2[0] + 0.5, ObjectPos2[1] + 1.0 - rdon, ObjectPos2[2] + 1.2, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GetPlayerVirtualWorld(playerid));

			SetPVarInt(playerid, "timerTrabalho_Fabricante", SetTimerEx("trabalhoFabricante_Start", 1200, false, "ii", playerid, 1));

		    TogglePlayerControllable(playerid, false); FabricandoMateriais[playerid] = true;
		}
		else SendClientMessage(playerid, -1, "Você precisa estar próximo a mesa de fabricação de materiais.");

		return true;
	}

	else if (!strcmp(params, "propina", true))
	{
	    if (gettime() < GetPVarInt(playerid, #varFlood_propinamat)) return SendClientMessage(playerid, -1, "Você só pode pegar propina a cada 2 minutos!");

		if (!PlayerIsMafia(playerid)) return SendClientMessage(playerid, -1, "Você precisa ser da máfia para recolher propina.");

		if (!IsPlayerInRangeOfPoint(playerid, 5.0, -960.2968,1907.3011,9.0061)) return SendClientMessage(playerid, -1, "Você não está no local de recolher propina.");

		if (OwnerFabricaMateriais != GetPlayerOrg(playerid)) return SendClientMessage(playerid, -1, "Sua organização deve dominar a fábrica primeiro.");

		if (propinaMateriais < 100) return SendClientMessage(playerid, -1, "As propinas devem estar com 0,100g ou mais para você recolher.");

		new saldoMateriais = GetPlayerItemTypeAmount(playerid, ITEM_TYPE_MATERIAL);
		if ((saldoMateriais + 100) > 2000 && Player_GetVIP(playerid) < SOCIO_EXTREME) return SendClientMessage(playerid, -1, "Você pode ter apenas 2,000g de materiais, venda para uma organização.");

		if ((saldoMateriais + 100) > 3000) return SendClientMessage(playerid, -1, "Você pode ter apenas 3,000g de materiais, venda para uma organização.");

		SetPlayerPos(playerid, -960.2968, 1907.3011, 9.0061);
		SetPlayerFacingAngle(playerid, 88.0434);
		ApplyAnimation(playerid, "BAR", "Barserve_bottle", 4.1, false, true, true, true, 1, SYNC_ALL);

		addQuantiaItem(playerid, ITEM_TYPE_MATERIAL, 2040, 100, "Material", 0, 0);
		propinaMateriais -= 100;

		format(string, sizeof(string), "* %s pegou sua propina e guardou seus materiais no bolso.", PlayerName[playerid]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		format(string, sizeof(string), "%s » {DCD5CB}%s %s pegou 100g de materiais de propina na fábrica de materiais.", NomeORG(playerid), GetPlayerCargo(playerid), PlayerName[playerid]);
		SendMembersMessage(GetPlayerOrg(playerid), GetPlayerColor(playerid), string);

	    SetPVarInt(playerid, #varFlood_propinamat, gettime() + 120);
	}

	else if (!strcmp(params, "pedidos", true))
	{
	    if (!PlayerIsFabricanteMat(playerid) && !PlayerIsMafia(playerid)) return SendClientMessage(playerid, -1, "Você não é um fabricante de armas.");

		new count = 0;

		MEGAString[0] = EOS;

		strcat(MEGAString, "Organização/Família\tQuant. de materiais\tValor por material\n");

        for(new orgsid; orgsid < MAX_ORGS; orgsid++)
		{
		    if (OrgIsBuyMateriais(orgsid) && CofreOrg[orgsid][cMateriais] > 0 && OrgInfo_GetMoney(orgsid) >= (CofreOrg[orgsid][cMateriais] * CofreOrg[orgsid][mMateriais]))
			{
				format(string, sizeof string, "{%s}%s\t{965302}%sg\t{00AA00}$%s\n", GetOrgColor(orgsid), GetNomeOrg(orgsid), getFormatText(CofreOrg[orgsid][cMateriais]), getFormatText(CofreOrg[orgsid][mMateriais]));
                strcat(MEGAString, string);

                count++;
			}
		}

        format(string, sizeof string, " {FFFFFF}Pedidos de materiais ({00FF00}%d{FFFFFF})", count);

        SendClientMessage(playerid, COLOR_LIGHTBLUE, "Escolha uma organização e vá até ela vender os materiais {FF0000}/gps » HQs das Organizações");

		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Fechar", "");
	}

	else if (strfind(params, "vender", true) != -1)
	{
	    if (!PlayerIsFabricanteMat(playerid) && !PlayerIsMafia(playerid)) return SendClientMessage(playerid, -1, "Você não é um fabricante de armas.");

		new idPlayer, quantMat, valorMat;
		if (sscanf(params, "s[25]ddd", null, idPlayer, quantMat, valorMat)) return SendClientMessage(playerid, -1, "Modo de uso: /materiais vender (id do jogador) (quantidade) (valor total)");

		if (gettime() < GetPVarInt(idPlayer, #varFlood_ofertaMateriais))
		{
			format(string, sizeof (string), "O jogador recebeu uma oferta recente, aguarde %s para ofertar novamente.", ConvertTempo(GetPVarInt(idPlayer, #varFlood_ofertaMateriais) - gettime()));
			return SendClientMessage(playerid, -1, string);
		}

		if (!ProxDetectorS(8.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Você não está próximo da pessoa que quer oferecer.");

		new saldoMateriais = GetPlayerItemTypeAmount(playerid, ITEM_TYPE_MATERIAL);
		if (saldoMateriais < quantMat) return SendClientMessage(playerid, -1, "Você não tem essa quantidade de materiais.");

		if (valorMat < 100 || valorMat > 5000) return SendClientMessage(playerid, -1, "O valor deve estar entre $100 a $5.000.");

		if ((saldoMateriais + quantMat) > 2000)
		{
			SendMsgF(playerid, COLOR_YELLOW, "O jogador possui %sg de materiais, você poderá vender apenas %sg para ele.", getFormatText(saldoMateriais), getFormatText(2000 - saldoMateriais >= 0 ? 2000 - saldoMateriais : 0));
			return SendClientMessage(playerid, -1, "Limite por jogador é 2,000g de materiais, não podendo ultrapassar.");
		}

		SetPVarInt(idPlayer, #varFlood_ofertaMateriais, gettime() + (60 * 2));
		SetPVarInt(idPlayer, "ofertaMateriais_ID", playerid);
		SetPVarInt(idPlayer, "ofertaMateriais_Gramas", quantMat);
		SetPVarInt(idPlayer, "ofertaMateriais_Valor", valorMat);

		format(string, sizeof(string), "* %s ofertou %sg de materiais para %s por $%s.", PlayerName[playerid], getFormatText(quantMat), PlayerName[idPlayer], getFormatText(valorMat));
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
		SendClientMessage(idPlayer, -1, "Para aceitar a oferta de materiais use: {00BFFF}/materiais aceitar");
	}

	else if (!strcmp(params, "cancelar", true))
	{
		if (!FabricandoMateriais[playerid]) return SendClientMessage(playerid, -1, "Você não está fabricando materiais no momento.");

		format(string, sizeof(string), "* %s cancelou a fabricação de materiais.", PlayerName[playerid]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		TogglePlayerControllable(playerid, true); FabricandoMateriais[playerid] = false;

		ClearAnimations(playerid);

        DestroyDynamicObject(GetPVarInt(playerid, "objectCreateMateriais")); DeletePVar(playerid, "objectCreateMateriais");

		DestroyDynamic3DTextLabel(textFabricandoMat[playerid]); KillTimer(GetPVarInt(playerid, "timerTrabalho_Fabricante"));
	}

	else
	{
		SendClientMessage(playerid, -1, "Modo de uso: /materiais (nome) (quantidade)");
	    SendClientMessage(playerid, COLOR_GRAD, "NOMES: produtos | fabricar | vender | aceitar | pedidos | propina | cancelar");
 		SendClientMessage(playerid, COLOR_GRAD, "_________________________________________________");
		return true;
	}
	return true;
}