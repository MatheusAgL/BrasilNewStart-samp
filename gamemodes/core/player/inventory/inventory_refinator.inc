
#if defined _inc_inv_refinator
	#endinput
#endif
#define _inc_inv_refinator true


#define         ITEM_MODEL_REFINADORA       18876


enum e_refinator {
    bool:inUse,
}
new RefinatorInfo[MAX_PLAYERS][e_refinator];

stock IsRefinableItem(type, model)
{
    if (type == ITEM_TYPE_DRONE) {
        switch(model) { // Tampa, Perennial, NRG-500, Blista, Stratum, Bullet, Vincent
            case 549, 404, 522, 529, 496, 561, 541, 540: {
                return true;
            }
            default: return false;
        }
    }
	return false;
}

stock Refinator_InUse(playerid)
    return RefinatorInfo[playerid][inUse];

stock Refinator_Use(playerid)
    RefinatorInfo[playerid][inUse] = true;

stock Refinator_Cancel(playerid) {
    RefinatorInfo[playerid][inUse] = false;
}

stock Refinator_Start(playerid, const item_name[]) 
{
    new string[384];
    MEGAString[0] = EOS;

    format(string, sizeof string, 
    "\n"C_WHITE"1.\t4 Tampa -> Euros ou Jester\
    \n2.\t4 Perennial -> Alpha ou Buffalo\
    \n3.\t4 NRG-500 -> Hydra ou Maverick\
    \n4.\t4 Blista -> Tractor ou Sultan\
    \n5.\t4 Stratum -> Bloodring Banger ou Elegy\
    \n6.\t4 Bullet -> Cargobob ou Hunter\
    \n7.\t4 Vincent -> Sadler ou Bobcat\
    \n\nConfirme para receber um dos itens acima:\
    \nVocê está refinando: "C_PEACH"(4 %s)", item_name);
    strcat(MEGAString, string);

    inline D_RefinatorStart(did, ddialogid, dresponse, dlistitem, string:dtext[]) {
        #pragma unused did, ddialogid, dlistitem
        
        if (dresponse) {
            if (!strlen(dtext)) 
                return SendClientMessage(playerid, COLOR_LIGHTRED, "Você precisa digitar CONFIRMAR para refinar o acessório.");

	        if (!strcmp(dtext, "confirmar", true))
			{
	            if (!IsPlayerHaveItem(playerid, ITEM_TYPE_CONSUMIVEL) && !IsPlayerHaveItemModel(playerid, ITEM_MODEL_REFINADORA))
	        		return SendClientMessage(playerid, -1, "Você não possui uma refinadora de itens.");

            	new 
                    itemid = GetPVarInt(playerid, "refinadoraAcessorioID"),
                    quantity = InvItem_GetQuantity(playerid, itemid),
                    model = InventarioInfo[playerid][itemid][item_model],
                    award_name[30],
                    award_model;

            	if (quantity != 4)
                    return SendClientMessage(playerid, -1, "Você precisa ter 4 itens iguais combinados.");

				new rdon = random(100);

	    		switch (model)
				{
		    	    case 549:       // Tampa
					{
                        if (52 < rdon > 0) {
                            award_name = "Euros";
                            award_model = 587;
                        } else {
                            award_name = "Jester";
                            award_model = 559;
                        }
					}
                    case 404:       // Perennial
					{
                        if (52 < rdon > 0) {
                            award_name = "Euros";
                            award_model = 402;
                        } else {
                            award_name = "Alpha";
                            award_model = 602;
                        }
					}
                    case 522:       // NRG-500
					{
                        if (65 < rdon > 0) {
                            award_name = "Maverick";
                            award_model = 487;
                        } else {
                            award_name = "Hydra";
                            award_model = 520;
                        }
					}
                    case 496:       // Blista
					{
                        if (52 < rdon > 0) {
                            award_name = "Tractor";
                            award_model = 531;
                        } else {
                            award_name = "Sultan";
                            award_model = 560;
                        }
					}
                    case 561:       // Stratum
					{
                        if (52 < rdon > 0) {
                            award_name = "Elegy";
                            award_model = 562;
                        } else {
                            award_name = "Bloodring Banger";
                            award_model = 504;
                        }
					}
                    case 541:       // Bullet
					{
                        if (52 < rdon > 0) {
                            award_name = "Cargobob";
                            award_model = 548;
                        } else {
                            award_name = "Hunter";
                            award_model = 425;
                        }
					}
                    case 540:       // Vincent
					{
                        if (52 < rdon > 0) {
                            award_name = "Sadler";
                            award_model = 543;
                        } else {
                            award_name = "Bobcat";
                            award_model = 422;
                        }
					}
                	default:
					{
                        return SendClientMessage(playerid, -1, "O item não é refinável.");
                	}
				}

                format(string, sizeof(string), "REFINADORA DE ITENS | "C_WHITE"%s refinou "C_PEACH"4 %s"C_WHITE", ganhou: "C_CYAN"%s", PlayerName[playerid], item_name, award_name);
                SendClientMessageToAll(COLOR_PEACH, string);

                InvItem_Reset(playerid, itemid);
                Inventory_UpdatePreview(playerid, itemid);
                
	    		removerItemTypeModel(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_REFINADORA);
                InvItem_SetSelected(playerid, -1);

                givePlayerItem(playerid, ITEM_TYPE_DRONE, award_model, 1, award_name);
                ServerLog::("refinadora", "%s refinou 4 %s e ganhou veículo %d %s", PlayerName[playerid], item_name, award_model, award_name);

                Refinator_Cancel(playerid);
		   	 	return 1;
			} else {
                return SendClientMessage(playerid, COLOR_WARNING, "A ação foi cancelada, pois você precisa digitar 'CONFIRMAR'.");
            }
        }
    }
    Dialog_ShowCallback(playerid, using inline D_RefinatorStart, DIALOG_STYLE_INPUT, ""C_GRAY"Confirme para receber o item", MEGAString, "OK", "Cancelar");

    return 1;
}