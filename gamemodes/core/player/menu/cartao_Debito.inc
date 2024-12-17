

		/*____________________________________________________________________________________________________________________________________________

						 ___________   _________     ________
						|    ___   \  |    __   \  /         \          Brasil Play Start ®
						|   |___/  |  |   |__|  | |    ______/              Fundação: Theus_Crazzy
						|   ______/   |    _____/ |   |______                   Data: 22/02/2016
						|         \   |   /       \          \                      Modulo: Cartão de débito
						|    ____  |  |   |        \_____    /                          
						|   |___/  |  |   |        /         \                              Theus_Crazzy (Desenvolvedor do módulo)
						|_________/   |___|        \_________/                                  Descrição: Sistema de cartão de débito


		____________________________________________________________________________________________________________________________________________*/

#include < YSI_Coding\y_hooks >

#define             ITEM_BUY_CELULAR            0
#define             ITEM_BUY_AGENDA	            1
#define             ITEM_BUY_NOTEBOOK           13
#define             ITEM_BUY_CAPACETE           14
#define             ITEM_BUY_COXAFRANGO         18
#define             ITEM_BUY_KITREPARO          19


stock buyPlayerItem(playerid, iditem, valor)
{
	new string[128];
	
	SetPVarInt(playerid, "valorItem", valor);
	SetPVarInt(playerid, "idItemBuy", iditem);
	
	MEGAString[0] = EOS;
	
	strcat(MEGAString, "Método de pagamento\tValor a ser pago\tSaldo\n");

	format(string, 128, "{DBDCE0}Dinheiro\t{FF0000}-$%s\t{00AA00}$%s\n", getFormatText(valor), getFormatText(Player_GetMoney(playerid)));
	strcat(MEGAString, string);
	format(string, 128, "{DBDCE0}Cartão de débito\t{FF0000}-$%s\t{00AA00}$%s\n", getFormatText(valor+valor/100), getFormatText(PlayerInfo[playerid][pConta]));
	strcat(MEGAString, string);

	ShowPlayerDialog(playerid, 2500, DIALOG_STYLE_TABLIST_HEADERS, "{7D8084}Efetuando uma compra", MEGAString, "Confirmar", "Cancelar");
}

stock getPlayerItemBuy(playerid, itembuy)
{
	new string[155];
	
	switch (itembuy) {
	
		case ITEM_BUY_CELULAR:
		{
			new randphone = 80000 + random(9999);
			PlayerInfo[playerid][numeroCelular] = randphone;
			format(string, sizeof(string), "Seu novo número de celular é %d", randphone);
			SendClientMessage(playerid, -1, string);
			SendClientMessage(playerid, -1, "Dê uma olhada nos seus documentos /rg");
			SendClientMessage(playerid, -1, "Dica: Digite /ajudacelular em caso de dúvidas");
		}
	    case ITEM_BUY_AGENDA:
		{
			SendClientMessage(playerid, -1, "   Nova agenda telefônica comprada!");
			SendClientMessage(playerid, -1, "Server: Digite /agenda <id/nome> ou use /agendatel para adicionar/remover contatos da agenda! ");
		}
		case 2:
		{
			gDice[playerid] = 1;
			SendClientMessage(playerid, -1, "   Você comprou um dado! Aproveite.");
			SendClientMessage(playerid, -1, "Server: Digite /dado");
		}
		case 3:
		{
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendClientMessage(playerid, -1, "Camisinha comprada.");
			SendClientMessage(playerid, -1, "Agora você pode fazer sexo com segurança.");
		}
		case 4:
		{
       		givePlayerItem(playerid, ITEM_TYPE_COMIDACRU, 19582, 1, "Carne Crua");

		    SendClientMessage(playerid, -1, "Você comprou 1 peça de Carne para cozinhar.");
		}
		case 5:
		{
        	SendClientMessage(playerid, -1, "Você comprou uma carteira de cigarro com 20 cigarros, use: /fumar.");
        	PlayerInfo[playerid][pCigarros] = 20;
    	}
    	case 6:
    	{
    		SendClientMessage(playerid, -1, "Galão de Gasolina comprada, USE: /incendio para incendiar o local.");
        	PlayerInfo[playerid][pGalao] = true;
     	}
     	case 7:
     	{
     	    SendClientMessage(playerid, -1, "Isqueiro comprado, Agora você pode usar /incendio.");
        	PlayerInfo[playerid][pIsqueiro] = true;
		}
		case 8:
		{
			SendClientMessage(playerid, -1, "Patins comprado, Agora você pode andar de patins usando /patins.");
			PlayerInfo[playerid][pPatins] = true;
		}
		case 9:
		{
			SendClientMessage(playerid, -1, "JBL comprado, Você pode pegar ele em seu inventário!");
			givePlayerItem(playerid, ITEM_TYPE_RADIO, 2226, 1, "JBL CHARGE 2");
			PlayerInfo[playerid][segurandoRadio] = false;
		}
		case 10:
		{
			SendClientMessage(playerid, -1, "Chave de Fenda comprada, ela está em seu inventário!");
			givePlayerItem(playerid, ITEM_TYPE_CHAVEFENDA, 18644, 1, "Chave de Fenda");
		}
		case 11:
		{
			SendClientMessage(playerid, COLOR_GRAD, "Chave Fixa comprada, ela está em seu inventário!");
			givePlayerItem(playerid, ITEM_TYPE_CHAVEFIXA, 19627, 1, "Chave Fixa");
		}
		case 12:
		{
			SendClientMessage(playerid, COLOR_GRAD, "Chave Biela comprada, ela está em seu inventário!");
			givePlayerItem(playerid, ITEM_TYPE_CHAVEBIELA, 18633, 1, "Chave Biela");
		}
		case ITEM_BUY_NOTEBOOK:
		{
			SendClientMessage(playerid, COLOR_GRAD, "Notebook comprado, você agora pode receber/enviar e-mails usando /email!");
			givePlayerItem(playerid, ITEM_TYPE_NOTEBOOK, 19893, 1, "Notebook");

			#if defined _INC_email
				SendPlayerEmail(SERVER_NAME, PlayerName[playerid], "Você acaba de criar uma conta. Seu limite de mensagens na caixa de entrada é de 25. Tenha um bom jogo!");
			#else
				MESSAGE_WARNING_INACTIVE_SYSTEM;
			#endif
		}
		case ITEM_BUY_CAPACETE:
		{
			SendClientMessage(playerid, COLOR_GRAD, "Escolha um capacete para comprar!");
		    ShowModelSelectionMenu(playerid, CapaceteList, "Escolha um capacete", 200, 0x000000AA);
  		}
  		case 15:
		{
			SendClientMessage(playerid, COLOR_GRAD, "Você comprou 5 garrafas de agua.");
		    givePlayerItem(playerid, ITEM_TYPE_GARRAFA, 1668, 5, "Garrafa de agua");
  		}
  		case 16:
  		{
  			SendClientMessage(playerid, COLOR_GRAD, "Regador comprado, veja em sua mochila apertando 'N'");
			givePlayerItem(playerid, ITEM_TYPE_REGADOR, 19621, 1, "Regador de plantas");
		}
		case 17:
		{
		    new vehid = GetPlayerVehicleID(playerid), BuyVehicleId = GetPVarInt(playerid, "buyVehicleID");
		
		   	if (vehid == CarrosConce[BuyVehicleId][ConceID])
  			{
				if ((Player_SetVehicleFromDealership(playerid, CarrosConce[BuyVehicleId][ConceModel], CarrosConce[BuyVehicleId][ConceValue]/3, vehid)) == -1) {
					format(string, sizeof string, "Você já excedeu o limite de {00FFFF}%d {FFFFFF}carros!", MAX_PLAYER_CARROS);
					SendClientMessage(playerid, -1, string);
					return 1;
				}
				new vehicle_name[30];
				GetModelStaticNameFromId(GetVehicleModel(vehid), vehicle_name);

				format(string, sizeof string, "Parabéns! Você pagou {00AA00}$%s {FFFFFF}por este {00FFFF}%s{FFFFFF}, use /veiculo ajuda!", getFormatText(CarrosConce[BuyVehicleId][ConceValue]), vehicle_name);
				SendClientMessage(playerid, -1, string);
				SendClientMessage(playerid, -1, "A concessionária já encomendou outro veículo do mesmo modelo, em breve estará à venda!");
				SendClientMessage(playerid, -1, "Pague corretamente as despesas do carro, caso contrario ele será {FF0000}vendido{FFFFFF}!");

				new vehicleid = CarrosConce[BuyVehicleId][ConceID];
				VehicleInfo[vehicleid][vhType] = VH_TYPE_COMMON;
				VehicleInfo[vehicleid][vhInfoID] = 0;

				CarrosConce[BuyVehicleId][ConceID] = INVALID_VEHICLE_ID;
				DestroyDynamic3DTextLabel(CarrosConce[BuyVehicleId][ConceText]);
				CarrosConce[BuyVehicleId][ConceText] = Text3D:-1;

				SetTimerEx("restoreCar", 60000, false, "i", BuyVehicleId);
			}
		}
		case ITEM_BUY_COXAFRANGO:
  		{
  			SendClientMessage(playerid, -1, "Você comprou 1 coxa de frango para cozinhar.");
			givePlayerItem(playerid, ITEM_TYPE_COMIDACRU, 19847, 1, "Coxa de Frango Crua");
		}
		case ITEM_BUY_KITREPARO:
  		{
  			SendClientMessage(playerid, -1, "Você comprou 5 kit reparo de veículo.");
  			givePlayerItem(playerid, ITEM_TYPE_REPAIR, 19921, 5, "Kit reparo de veiculo");
		}
  	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == 2500)
	{
     	if (response)
	    {
	        new string[128],
				idItem = GetPVarInt(playerid, "idItemBuy"),
				valorTotal = GetPVarInt(playerid, "valorItem"),
				bancoFiliado = PlayerInfo[playerid][pBancoFiliado];
	    
	        switch (listitem)
			{
	            case 0:
				{
					if (Player_GetMoney(playerid) < valorTotal) 
						return SendClientMessage(playerid, -1, "Você não tem esse valor em sua carteira.");

					Player_RemoveMoney(playerid, valorTotal);

		            format(string, sizeof string, "Você acaba de pagar {00AA00}$%s{FFFFFF} de sua carteira.", getFormatText(GetPVarInt(playerid, "valorItem")));
					SendClientMessage(playerid, -1, string);

					getPlayerItemBuy(playerid, idItem);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

					if (GetPlayerVirtualWorld(playerid) != 0)
						DepositPropertie(playerid, valorTotal);
				}
				case 1:
				{
					new taxBank = valorTotal/100;
		            
		            if (bancoFiliado < 1) 
						return SendClientMessage(playerid, -1, "Você não é filiado a nenhum banco, vá até algum para filiar-se.");
		        
					if (PlayerInfo[playerid][pConta] < valorTotal) 
						return SendClientMessage(playerid, -1, "Você não tem esse valor em sua conta bancária.");

					PlayerInfo[playerid][pConta] -= (valorTotal + taxBank);
					PropInfo[bancoFiliado][eTill] += taxBank;
					
					format(string, sizeof string, "Você acaba de pagar {00AA00}$%s{FFFFFF} com o seu cartão de débito.", getFormatText(valorTotal));
					SendClientMessage(playerid, -1, string);

					getPlayerItemBuy(playerid, idItem);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

					if (GetPlayerVirtualWorld(playerid) != 0)
						DepositPropertie(playerid, valorTotal);
				}
		    }
		}
	}
	return 0;
}
