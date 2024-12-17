#include <YSI_Coding\y_hooks>

#define MAX_DEALERS 16

static const Float:DealersPos[][4] = {
	{2175.8381, -1716.1682, 13.5265, 268.0555},
	{2015.7886, -1028.5599, 24.7981, 83.8138},
	{1074.5594, -1889.5283, 13.5469, 0.1125},
	{2312.6016, -1223.0970, 24.1370, 90.7709},
	{360.3899, -1758.4163, 5.6586, 90.7709},
	{1394.4150, -914.6793, 35.4005, 77.8371},
	{1044.6611, -1231.4335, 16.8792, 274.1306},
    {2366.3015, -1815.2783, 13.3320, 359.5532},
    {1878.6151, -1860.1746, 13.5778, 92.3443},
    {1864.6682, -2018.7400, 13.5469, 92.2379},
    {2479.1924, -1379.1639, 28.8355, 270.7890},
    {2678.0454, -1986.1519, 13.5518, 265.6758},
    {2188.1890, -1261.5684, 23.9369, 354.3125},
    {1830.5922, -1117.8073, 23.8449, 90.5147},
    {1145.5828, -2229.3977, 46.1162, 253.4056},
    {1893.4115, -2107.5989, 13.5862, 51.6949}
};

static const DealerItemsInfo[][][] = {
    {"Maconha", "D3DEAB", "grama"},
    {"Cocaína", "CFD1C7", "grama"},
    {"Crack", "77873A", "grama"},
    {"Heroína", "8A3D54", "grama"},
    {"Metanfetamina", "257D70", "grama"},
    {"Móvel", "C4C0C2", "unidade"}
};

static const DealerNames[][] = {
    "Tião",
    "Chiquin",
    "Tripa",
    "Banguela",
    "Cabeleira",
    "Baixinho",
    "Gordo",
    "Bolota",
    "Mão Branca",
    "Pé Rapado",
    "Baratão",
    "Mosquito",
    "Alemão",
    "Farol",
    "Xuxa",
    "Guga",
    "Pata de Galinha",
    "Mula"
};

static const DealerSkins[] = {
    28, 29, 30, 78, 79, 115, 116, 103, 104, 105, 254
};

// Dados dos dealers
enum dealerInfo {
    diSkinID,
    Float:diPosX,
    Float:diPosY,
    Float:diPosZ,
    Float:diRotation,
    diAnimLib[35],
    diAnimName[35],
    diActorID,
    Text3D:diText,
    diAmountAvailable[6],
    diValueAvailable[6],
    diName[30],
    diAreaName[30],
    diArrested
};

new DealerInfo[MAX_DEALERS][dealerInfo];

stock SpawnDealer(dealerid) {
    DealerInfo[dealerid][diSkinID] = DealerSkins[random(sizeof(DealerSkins))];
    DealerInfo[dealerid][diArrested] = 0;
    
    new string[256];
    format(DealerInfo[dealerid][diName], 30, "%s", DealerNames[random(sizeof(DealerNames))]);
    DealerInfo[dealerid][diActorID] = CreateDynamicActor(DealerInfo[dealerid][diSkinID], DealerInfo[dealerid][diPosX], DealerInfo[dealerid][diPosY], DealerInfo[dealerid][diPosZ], DealerInfo[dealerid][diRotation], false, 100.0, 0);
    PreloadActorAnimations(dealerid);

    ApplyDynamicActorAnimation(DealerInfo[dealerid][diActorID], "DEALER", "DEALER_IDLE", 4.1, 1, 0, 0, 0, 0);
    ApplyDynamicActorAnimation(DealerInfo[dealerid][diActorID], "DEALER", "DEALER_IDLE", 4.1, 1, 0, 0, 0, 0);

    format(string, sizeof(string), 
        "{FF7575}Traficante - %s\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para negociar",
        DealerInfo[dealerid][diName]
    );
    if(DealerInfo[dealerid][diText] == INVALID_3DTEXT_ID) {
        DealerInfo[dealerid][diText] = CreateDynamic3DTextLabel(
            string,
            0xFFFFFFFF, 
            DealerInfo[dealerid][diPosX], 
            DealerInfo[dealerid][diPosY], 
            DealerInfo[dealerid][diPosZ] + 1.0, 
            15.0
        );
    }
    else {
        UpdateDynamic3DTextLabelText(DealerInfo[dealerid][diText], 0xFFFFFFFF, string);
    }
}

stock ArrestDealer(dealerid) {
    new string[256];

    DestroyDynamicActor(DealerInfo[dealerid][diActorID]);

    format(string, sizeof(string), 
        "\n\n\n\n\n\n\n\n\
        {FF7575}O traficante da região de %s foi preso.\n\
        Os criminosos vão colocar outra pessoa nesse local.",
        DealerInfo[dealerid][diAreaName]
    );

    UpdateDynamic3DTextLabelText(DealerInfo[dealerid][diText], 0xFFFFFFFF, string);
    DealerInfo[dealerid][diArrested] = 1;
}

stock CreateDealers() {
    for(new i = 0; i < sizeof(DealersPos); i++) {
        DealerInfo[i][diPosX] = DealersPos[i][0];
        DealerInfo[i][diPosY] = DealersPos[i][1]; 
        DealerInfo[i][diPosZ] = DealersPos[i][2];
        DealerInfo[i][diRotation] = DealersPos[i][3];
        DealerInfo[i][diText] = INVALID_3DTEXT_ID;

        new MapZone:zone = GetMapZoneAtPoint2D(DealerInfo[i][diPosX], DealerInfo[i][diPosY]);
        GetMapZoneName(zone, DealerInfo[i][diAreaName]);

        SpawnDealer(i);
        UpdateDealerValues(i);
    }
}

stock UpdateDealerValues(dealerid) {
    for(new x = 0; x < 5; x++) {
        DealerInfo[dealerid][diAmountAvailable][x] = 50 + random(300);
        DealerInfo[dealerid][diValueAvailable][x] = 70 + random(100);
    }
    DealerInfo[dealerid][diAmountAvailable][5] = 5 + random(3);
    DealerInfo[dealerid][diValueAvailable][5] = 500 + random(800);
}

stock ShowPlayerDealerMenu(playerid, dealerid) {
    SetPVarInt(playerid, "DealerInContact", dealerid);
    new string[256];

    MEGAString = "Ação\tItem\tQuantidade disponível\n";
    for(new x = 0; x < 6; x++) {
        format(
            string, 
            256,
            "{FFFFFF}Vender\t{%s}%s\t{FFFFFF}%s %ss\n", 
            DealerItemsInfo[x][1], 
            DealerItemsInfo[x][0], 
            getFormatText(DealerInfo[dealerid][diAmountAvailable][x]), 
            DealerItemsInfo[x][2]
        );
        strcat(MEGAString, string);
    }

    ShowPlayerDialog(playerid, 680, DIALOG_STYLE_TABLIST_HEADERS, "Traficante", 
        MEGAString, 
        "Selecionar", "Cancelar");
}

stock ShowPlayerFurnitureSaleDialog(playerid, dealerid)
{
	if(!GetPVarInt(playerid, "movelRoubou"))
		return SendClientMessage(playerid, -1 , "Você não tem nada para negociar com este traficante !");
	else if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_CARRY) {
		RemovePlayerAttachedObject(playerid, Slot_Movel);
		SetPVarInt(playerid, "movelRoubou", 0);
		return SendClientMessage(playerid, -1, "Você não está mais carregando um móvel roubado.");
	}

	new string[128];
	MEGAString[0] = EOS;

	format(string, sizeof string, "Vender este móvel por $%s\n", getFormatText(DealerInfo[dealerid][diValueAvailable][5]));
	strcat(MEGAString, string);

	format(string, sizeof string, "Trocar este móvel por %d gramas de maconha\n", GetPVarInt(playerid, "movelMaconha"));
	strcat(MEGAString, string);

	format(string, sizeof string, "Trocar este móvel por %d gramas de crack\n", GetPVarInt(playerid, "movelCrack"));
	strcat(MEGAString, string);

	format(string, sizeof string, "Trocar este móvel por %d gramas de cocaina\n", GetPVarInt(playerid, "movelCocaina"));
	strcat(MEGAString, string);

	inline D_SelectAction(dyid, dydialogid, dyresponse, dylistitem, string:dytext[])
	{
		#pragma unused dyid, dydialogid, dytext, dyresponse
		if(!dyresponse)
			return 1;

		if(dylistitem == 0) {
			new total = DealerInfo[dealerid][diValueAvailable][5];
			Player_AddMoney(playerid, total);
			format(string, sizeof(string), "Traficante diz: Valeu fi, toma aí teus $%s pila", getFormatText(total));
            SendClientMessageInRange(35.0, playerid, 
                string, 
                COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5
            );
		}
		else if(dylistitem == 1) {
			new total = GetPVarInt(playerid, "movelMaconha");
			givePlayerItem(playerid, ITEM_TYPE_MACONHA, 2891, total, "Maconha");
			format(string, sizeof(string), "Traficante diz: Valeu fi, pega aí tuas %d gramas de maconha", getFormatText(total));
            SendClientMessageInRange(35.0, playerid, 
                string, 
                COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5
            );
		}
		else if(dylistitem == 2) {
			new total = GetPVarInt(playerid, "movelCrack");
			givePlayerItem(playerid, ITEM_TYPE_MACONHA, 2891, total, "Crack");
			format(string, sizeof(string), "Traficante diz: Valeu fi, pega aí tuas %d gramas de crack", getFormatText(total));
            SendClientMessageInRange(35.0, playerid, 
                string, 
                COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5
            );
		}
		else if(dylistitem == 3) {
			new total = GetPVarInt(playerid, "movelCocaina");
			givePlayerItem(playerid, ITEM_TYPE_MACONHA, 2891, total, "Cocaina");
			format(string, sizeof(string), "Traficante diz: Valeu fi, pega aí tuas %d gramas de cocaína", getFormatText(total));
            SendClientMessageInRange(35.0, playerid, 
                string, 
                COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5
            );
		}
		
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, Slot_Movel);
		SetPVarInt(playerid, "movelRoubou", 0);
		ApplyAnimation(playerid,"CARRY","putdwn",6.1,0,1,1,0,0);
		return 1;
	}

	Dialog_ShowCallback(playerid, using inline D_SelectAction, DIALOG_STYLE_LIST, "Escolha uma opção", MEGAString, "Negociar", "Sair");
	return 1;
}

CALLBACK:CheckAndArrestDealer(playerid) {
    new string[256];
    for(new i = 0; i < MAX_DEALERS; i++) {
        if(!DealerInfo[i][diArrested] && PlayerToPoint(2.0, playerid, DealerInfo[i][diPosX], DealerInfo[i][diPosY], DealerInfo[i][diPosZ])) {
            format(string, sizeof(string), "** %s prendeu o traficante %s da região de %s.", PlayerName[playerid], DealerInfo[i][diName], DealerInfo[i][diAreaName]);
            SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

            new lucro = 100 + random(10000);
            removerDinheiroGoverno(lucro);
            Player_AddMoney(playerid, lucro);

            format(string, sizeof(string), "<< COPOM >>: %s efetuou uma prisão de um traficante na região de %s.", PlayerName[playerid], DealerInfo[i][diAreaName]);
            SendMembersMessage(GetPlayerOrg(playerid), COLOR_LIGHTRED, string), SendMembersMessage(7, COLOR_LIGHTRED, string);
            PlayerPlaySound(playerid, 1039, 0.0, 0.0, 0.0);
            ArrestDealer(i);
            return 1;
        }
    }
    return 0;
}

hook OnGameModeInit() {
    CreateDealers();
}

hook DealWithPlayerInPosition(playerid) {
    for(new i = 0; i < MAX_DEALERS; i++) {
        if(!DealerInfo[i][diArrested] && PlayerToPoint(2.0, playerid, DealerInfo[i][diPosX], DealerInfo[i][diPosY], DealerInfo[i][diPosZ])) {
            ShowPlayerDealerMenu(playerid, i);
            break;
        }
    }
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if(dialogid == 680) {
        if(!response)
            return 1;

        if (listitem == -1)
            return 1;

        new dealerid = GetPVarInt(playerid, "DealerInContact");
        if(DealerInfo[dealerid][diAmountAvailable][listitem] <= 0) 
            return SendClientMessageInRange(35.0, playerid, 
                "Traficante diz: Opa... foi mal, num vai rolar pra eu comprar isso de ti, passa mais tarde.", 
                COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5
            );

        SetPVarInt(playerid, "DealerProduct", listitem);
        if(listitem != 6) {
            format(
                MEGAString, 
                sizeof(MEGAString),
                "{CFCFCF}Fala, menor, quanto que tu tem aí para me vender de {%s}%s{CFCFCF}?\n\n\
                Quantidade que eu posso comprar: {FFFFFF}%s %ss\n\
                {CFCFCF}Valor que eu posso pagar: {FFFFFF}$%s/%s\n\n\
                {CFCFCF}Agora fala aí quanto que tu quer vender?", 
                DealerItemsInfo[listitem][1], 
                DealerItemsInfo[listitem][0],
                getFormatText(DealerInfo[dealerid][diAmountAvailable][listitem]),
                DealerItemsInfo[listitem][2],
                getFormatText(DealerInfo[dealerid][diValueAvailable][listitem]),
                DealerItemsInfo[listitem][2]
            );

            ShowPlayerDialog(playerid, 681, DIALOG_STYLE_INPUT, "Negociação com traficante", 
                MEGAString, 
                "Vender", "Cancelar");
        }
        else {
            ShowPlayerFurnitureSaleDialog(playerid, dealerid);
        }
    }
    else if(dialogid == 681 || dialogid == 682) {
        if(!response)
            return 1;

        new dealerid = GetPVarInt(playerid, "DealerInContact"),
            itemid = GetPVarInt(playerid, "DealerProduct"),
            amount = strval(inputtext),
            itemType;

        if(itemid == 0)
            itemType = ITEM_TYPE_MACONHA;
        else if(itemid == 1)
            itemType = ITEM_TYPE_COCAINA;
        else if(itemid == 2)
            itemType = ITEM_TYPE_CRACK;
        else if(itemid == 3)
            itemType = ITEM_TYPE_HEROINA;
        else if(itemid == 4)
            itemType = ITEM_TYPE_METANFETAMINA;

        if(DealerInfo[dealerid][diAmountAvailable][itemid] <= 0) 
            return SendClientMessageInRange(35.0, playerid, 
                "Traficante diz: Opa... foi mal, num vai rolar pra eu comprar isso de ti, passa mais tarde.", 
                COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5
            );
        else if(dialogid == 681 && DealerInfo[dealerid][diAmountAvailable][itemid] < amount)
            return SendClientMessageInRange(35.0, playerid, 
                "Traficante diz: Coé, menor, num dá pra eu comprar essa quantidade aí não.", 
                COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5
            );
        else if(dialogid == 681 && GetPlayerItemTypeAmount(playerid, itemType) < amount)
            return SendClientMessageInRange(35.0, playerid, 
                "Traficante diz: Coé, menor, tu tá loucão? Tu nem tem isso aí pra me vender.", 
                COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5
            );
        else if(dialogid == 682 && !GetPVarInt(playerid, "movelRoubou"))
            return SendClientMessageInRange(35.0, playerid, 
                "Traficante diz: Coé, menor, tu tá loucão? Tu nem tem nada pra me vender.", 
                COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5
            );
        else if(amount <= 0) 
            return SendClientMessageInRange(35.0, playerid, 
                "Traficante diz: Coé, menor, tu tá loucão? Quer passar a perna na quebrada?", 
                COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5
            );
        

        if(dialogid == 681) {
            new value = amount*DealerInfo[dealerid][diValueAvailable][itemid],
                string[256];
            RemovePlayerItemTypeAmount(playerid, itemType, amount);
            Player_AddMoney(playerid, value);

            format(string, sizeof(string), "Traficante diz: Valeu fi, toma aí teus $%s pila", getFormatText(value));
            SendClientMessageInRange(35.0, playerid, 
                string, 
                COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5
            );

            DealerInfo[dealerid][diAmountAvailable][itemid] -= amount;
            PlayerPlaySound(playerid, 1058,  0.0, 0.0, 0.0);
        }
    }
    return 1;
}

task UpdateDealerAmount[15 * 60 * 1000]() {
    for(new d = 0; d < MAX_DEALERS; d++) {
        if(DealerInfo[d][diArrested])
            continue;

        for(new x = 0; x < 5; x++) {
            DealerInfo[d][diAmountAvailable][x] += 50 + random(60);
            DealerInfo[d][diValueAvailable][x] = 70 + random(100);

            if(DealerInfo[d][diAmountAvailable][x] > 7000)
                DealerInfo[d][diAmountAvailable][x] = 7000;
        }
    }
}

task RespawnArrestedDealers[20 * 60 * 1000]() {
    for(new d = 0; d < MAX_DEALERS; d++) {
        if(DealerInfo[d][diArrested]) {
            SpawnDealer(d);            
        }
    }
}
