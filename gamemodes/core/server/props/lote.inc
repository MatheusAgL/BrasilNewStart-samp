// --------------------------------------------------------
// Sistema de lote de terras (Urbana ou Rural):

// stock Lote_TaxPay(playerid, TaxType:tax)
// {
// 	new string[128],
// 		taxValue = Tax_GetValue(tax),
// 		days,
// 		LoteType:loteType[7],
// 		taxPay[7],
// 		debtValue[7],
// 		Float:daysLate[7],
// 		MapZone:zone,
// 		zone_name[MAX_MAP_ZONE_NAME],
// 		lote_value,
// 		count;

// 	MEGAString[0] = EOS;
// 	strcat(MEGAString, "id / bairro\tdata de vencimento\tvalor\n");

// 	foreach(new casas : House) 
//     {
// 	    if (House_IsOwner(playerid, casas, 1)) 
// 		{
//             loteType[count] = HOUSE;
// 			days = House_GetDueDate(playerid, casas);
// 			zone = GetMapZoneAtPoint2D(HouseInfo[casas][hEntradaX], HouseInfo[casas][hEntradaY]);
// 			lote_value = HouseInfo[casas][hValor];
// 			GetMapZoneName(zone, zone_name);

// 			if (days < 0) {
// 				daysLate[count] = floatabs(days);
// 				debtValue[count] = floatround(daysLate[count] * floatround(floatmul(floatdiv(1.0, 100.0), taxPay[count])));

// 				format(string, sizeof(string), ""C_CYAN"%03d em %s\t"C_RED"%d DIAS DE ATRASO\t"C_MONEY"$%s\n",
// 				casas, zone_name, daysLate[count], getFormatText(taxPay[count]));

// 				taxPay[count] = (taxPay[count] + debtValue[count]);
// 			} else {
// 				taxPay[count] = (floatround(floatmul(floatdiv(taxValue, 100.0), lote_value)) / 30) * (30 - days);

// 				format(string, sizeof(string), ""C_CYAN"%03d em %s\t"C_GREEN"%d DIAS PARA VENCER\t"C_MONEY"$%s\n",
// 				casas, zone_name, days, getFormatText(taxPay[count]));
// 			}
// 			strcat(MEGAString, string);
// 	    	count++;
// 		}
// 	}
//     for(new prop; prop != unid; prop++) 
//     {
//         if (PropInfo[prop][eOwnerID] == Player_GetAccountID(playerid)) 
//         {
//             loteType[count] = BUSINESS;
//             days = Business_GetDueDate(playerid, prop);
// 			lote_value = PropInfo[prop][ePrice];

//             if (days < 0) {
// 				daysLate[count] = floatabs(days);
// 				debtValue[count] = floatround(daysLate[count] * floatround(floatmul(floatdiv(1.0, 100.0), taxPay[count])));

// 				format(string, sizeof(string), ""C_CYAN"%03d    %s\t"C_RED"%d DIAS DE ATRASO\t"C_MONEY"$%s\n",
// 				prop, PropInfo[prop][ePname], daysLate[count], getFormatText(taxPay[count]));

// 				taxPay[count] = (taxPay[count] + debtValue[count]);
// 			} else {
// 				taxPay[count] = (floatround(floatmul(floatdiv(taxValue, 100.0), lote_value)) / 30) * (30 - days);

// 				format(string, sizeof(string), ""C_CYAN"%03d	%s\t"C_GREEN"%d DIAS PARA VENCER\t"C_MONEY"$%s\n",
// 				prop, PropInfo[prop][ePname], days, getFormatText(taxPay[count]));
// 			}
// 			strcat(MEGAString, string);
// 	    	count++;
//         }
//     }

// 	if (!count)
// 		return SendClientMessage(playerid, -1, "Você não tem nenhuma propriedade urbana."), Dialog_PayTax(playerid);

// 	inline D_TaxPayConfirm(dtaxpupyid, dtaxpupydialogid, dtaxpupyresponse, dtaxpupylistitem, string:dtaxpupytext[])
// 	{
// 		#pragma unused dtaxpupyid, dtaxpupydialogid, dtaxpupytext

// 		if (!dtaxpupyresponse)
// 			return Dialog_PayTax(playerid);

// 		if (count != 0)
// 		{
//             prop_id = dtaxpupylistitem;

// 			if (Player_GetMoney(playerid) < taxPay[prop_id])
// 				return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiente.");

// 			format(string, sizeof(string), "Você pagou as contas do seu veículo: "C_CYAN"%s"C_WHITE", total "C_RED"-$%s", vehicle_name, getFormatText(taxPay[vehicle_id] - debtValue[vehicle_id]));
// 			SendClientMessage(playerid, -1, string);

// 			if (daysLate[prop_id] > 0) {
// 				format(string, sizeof(string), "O atraso gerou juros e foi cobrado "C_GRAY"1%% ao dia totalizando: "C_RED"-$%s", getFormatText(debtValue[vehicle_id]));
// 				SendClientMessage(playerid, -1, string);
// 			}
// 			Player_RemoveMoney(playerid, taxPay[prop_id]);

// 			adicionarDinheiroGoverno(floatround(floatmul(floatdiv(80.0, 100.0), taxPay[prop_id])));
// 			DepositPropertie(playerid, floatround(floatmul(floatdiv(20.0, 100.0), taxPay[prop_id])));
			
// 			Vehicle_SetDueDate(playerid, prop_id, Days:30);
// 		}
// 		Dialog_ShowCallback(
// 			playerid, using inline D_TaxPayConfirm, DIALOG_STYLE_TABLIST_HEADERS, 
// 			"IPTU", 
// 			MEGAString, "Pagar", "Retornar"
// 		);
// 	}
// 	return 1;
// }