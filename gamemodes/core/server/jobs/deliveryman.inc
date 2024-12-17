#include <YSI_Coding\y_hooks>

#define ID_MENU_VEHICLES_DELIVERYMAN 5

static Deliveryman_Category[][enumMenuCategory] = 
{
    { 1, "Motoboy", 10, 0 }
};

static DeliverymanVehicle[20][tempVehicleEnum];

static DeliverymanVehiclePizzas[20];

static const RandomPizzaNome[][] =
{
	"De catupiry",
	"De 4 queijos",
	"De frango",
	"De Calabresa",
	"De chocolate",
	"De bacon"
};
static const RandomPizzaGorgeta[][] =
{
	"Sra. Marcia",
	"Sra. Stela",
	"Sr. Pedro",
	"Sra. Claudia",
	"Sr. Joao",
	"Dona Ana",
	"Seu Aufredo",
	"Dona Julia",
	"Sr. Paulo",
	"Sra. Cristiana",
	"Sr. Marcio",
	"Sra. Ana Paula",
	"Sr. Douglas",
	"Sra. Marcela",
	"Sr. Rodrigo",
	"Sra. Helena",
	"Sra. Mary",
	"Sr. Crystoffer",
	"Srta. Carol",
    "Dona Madalena",
    "Seu Jose",
    "Sra. Aufredina",
    "Sr. Lucas",
    "Sr. Daniel",
    "Sra. Daniela",
    "Sra. Juliana",
    "Sr. Joao paulo",
    "Sra. Renata",
    "Sra. Thuanny"
};

CALLBACK:IsPlayerDeliveryman(playerid) {
	return (
		PlayerInfo[playerid][pEmprego] == ID_JOB_DELIVERYMAN || 
		PlayerInfo[playerid][pEmprego2] == ID_JOB_DELIVERYMAN
	);
}

hook OnGameModeInit() {
    CreateDynamicPickup(1582, 23, 2113.4316,-1824.7124,13.5562);
    CreateDynamic3DTextLabel("Pizzaria\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para pegar pizzas", 0xFFFFFFFF,2113.4316,-1824.7124,13.5562,13.0);

	CreateDynamicPickup(19942, 23, 2107.9543,-1823.7922,13.5569);
    CreateDynamic3DTextLabel("Pizzaria\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para trabalhar", 0xFFFFFFFF,2107.9543,-1823.7922,13.5569,13.0);

	CreateDynamicPickup(1025, 23, 2096.2830,-1821.1907,13.3828); //Pegar veículo
    CreateDynamic3DTextLabel("Garagem da Pizzaria\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para pegar uma moto", 0xFFFFFFFF,2096.2830,-1821.1907,13.3828,13.0);

	CreateDynamicObject(2637, 2113.39038, -1823.07019, 12.96086,   0.00000, 0.00000, 0.72000);
	CreateDynamicObject(2453, 2113.00024, -1823.09583, 13.76485,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2453, 2113.76074, -1823.09033, 13.76485,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11729, 2108.32568, -1822.53516, 12.54170,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11729, 2107.60303, -1822.55896, 12.54170,   0.00000, 0.00000, 0.00000);
	return 1;
}

hook DealWithPlayerInPosition(playerid) {
	if(PlayerToPoint(2.0, playerid, 2096.2830,-1821.1907,13.3828)) {
		if(!IsPlayerDeliveryman(playerid)) {
			SendClientMessage(playerid, -1, "Você não é um entregador de pizza.");
		}
		else if(!IsPlayerWorking(playerid)) {
			SendClientMessage(playerid, -1, "Você não está em serviço. Bata cartão para pegar as pizzas.");
		}
		else {
			TogglePlayerControllable(playerid, false);
			MenuInfo[playerid][menu_id] = ID_MENU_VEHICLES_DELIVERYMAN;
			OpenMenu(playerid, ID_MENU_VEHICLES_DELIVERYMAN);
		}
	}
	else if(PlayerToPoint(2.0, playerid, 2113.4316,-1824.7124,13.5562)) {
		new pizzas = GetPVarInt(playerid, "DeliverymanPizzas");
		new dvid = GetPVarInt(playerid, "DeliverymanVehicleID");
		
		if(!IsPlayerDeliveryman(playerid)) {
			SendClientMessage(playerid, -1, "Você não é um entregador de pizza.");
		}
		else if(!IsPlayerWorking(playerid)) {
			SendClientMessage(playerid, -1, "Você não está em serviço. Bata cartão para pegar as pizzas.");
		}
		else if(pizzas >= 15) {
			SendClientMessage(playerid, -1, "Você já está com 15 pizzas, venda-as primeiro.");
		}
		else if(!DeliverymanVehicle[dvid][tvCreated] || DeliverymanVehicle[dvid][tvPlayerID] != playerid) {
			SendClientMessage(playerid, -1, "Você ainda não pegou sua moto de entregas. Pegue-a primeiro!");
		}
		else {
			new string[64], remaining = 15 - pizzas;
			
			format(string, sizeof(string), "~r~~h~~h~+%d ~w~Pizza", remaining);
			ShowPlayerPopupHUD(playerid, "PIZZARIA", string, 6000);

			SetPVarInt(playerid, "DeliverymanPizzas", 15);

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
			SetPlayerAttachedObject(
				playerid, Slot_Pizza, 1582, 5, 
				0.109999, -0.005000, 0.153000, 
				-85.199981, -13.100001, 10.600001, 
				0.682000, 0.726999, 1.410999
			);
		}
	}
	else if(PlayerToPoint(2.0, playerid, 2107.9543,-1823.7922,13.5569)) {
		if(!IsPlayerDeliveryman(playerid)) {
			SendClientMessage(playerid, -1, "Você não é um entregador de pizza.");
		}
		else {
			new string[128];
			if(!IsPlayerWorking(playerid)) {
				PlayerInfo[playerid][pSkinServico] = 155;
				SetPlayerSkin(playerid, PlayerInfo[playerid][pSkinServico]);

				format(string, sizeof string, "(( Entregadores de Pizza )) {FFFFFF}%s pegou seu uniforme e está em serviço.", PlayerName[playerid]);
				EmpregoMensagem(0xE0D78AFF, string, ID_JOB_DELIVERYMAN);

				TogglePlayerWorking(playerid);
			}
			else {
				TogglePlayerWorking(playerid);
				SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
				SendMsgF(playerid, COLOR_LIGHTBLUE, "Você guardou sua farda e não está mais de serviço");
			}
		}
	}
}

hook ChangeMenuTitle(playerid, menuid) {
	if(menuid == ID_MENU_VEHICLES_DELIVERYMAN) {
		PlayerTextDrawBoxColor(playerid, menu_ptextdraws[0][playerid], -1021765121);
		PlayerTextDrawColor(playerid, menu_ptextdraws[1][playerid], -1);
		PlayerTextDrawSetString(playerid, menu_ptextdraws[1][playerid], "Entregadores");
	}
}

hook MenuSetItens(playerid, menuid) {
	if(menuid == ID_MENU_VEHICLES_DELIVERYMAN) {
		MenuInfo[playerid][menu_max_itens] = sizeof(Deliveryman_Category);

		for(new i; i < sizeof(Deliveryman_Category); i++) {
			Menu_Category[playerid][i][category_id]                     = Deliveryman_Category[i][category_id];
			format(Menu_Category[playerid][i][category_nome], 20,       Deliveryman_Category[i][category_nome]);
			Menu_Category[playerid][i][category_quantidade]             = Deliveryman_Category[i][category_quantidade];
			Menu_Category[playerid][i][category_position]               = Deliveryman_Category[i][category_position];
		}
	}
}

hook OnVehicleDestroyed(vehicleid) {
	if(VehicleInfo[vehicleid][vhTemp]) {
		for(new i = 0; i < sizeof(DeliverymanVehicle); i++) {
			if(DeliverymanVehicle[i][tvVehicleID] == vehicleid) {

				// ERROR. Attempted to read/write array element at index 1 in array of size 1
				// new itemId = GetVehicleModel(vehicleid) == 407 ? 0 : 1;
				// Deliveryman_Category[itemId][category_quantidade] += 1;

				Deliveryman_Category[0][category_quantidade] += 1;
				VehicleInfo[vehicleid][vhTemp] = 0;
				DeliverymanVehicle[i][tvCreated] = 0;
				return 1;
			}	
		}
	}
	return 1;
}

hook OnPlayerConfirmMenu(playerid, menuid, pageid, itemid, selecteditem) {
	if(menuid == ID_MENU_VEHICLES_DELIVERYMAN) {
		if(Deliveryman_Category[selecteditem][category_quantidade] <= 0) 
			return SendClientMessage(playerid, -1, "Não existem unidades desse veículo disponíveis para uso.");

		DestroyPlayerTempVehicle(playerid);

		//Deliveryman_Category[selecteditem][category_quantidade] -= 1;

		new modelid = 448, string[128],
			vehid = CreateVehicle(modelid, 2096.1353,-1813.6771,12.9812,92.1198, 6, 6, -1);

		UnlockVehicleDoors(vehid);
		PutPlayerInVehicle(playerid, vehid, 0);
		SetPlayerTempVehicleID(playerid, vehid);
		VehicleInfo[vehid][vhTemp] = 1;

		for(new i = 0; i < sizeof(DeliverymanVehicle); i++) {
			if(!DeliverymanVehicle[i][tvCreated]) {
				DeliverymanVehicle[i][tvCreated] = 1;
				DeliverymanVehicle[i][tvVehicleID] = vehid;
				DeliverymanVehicle[i][tvModelID] = modelid;
				DeliverymanVehicle[i][tvPlayerID] = playerid;
				DeliverymanVehiclePizzas[i] = 0;

				format(
					string, sizeof(string), 
					"Moto de %s\nPizzas: 0\nUse /pizza pegar para pegar em mãos",
					PlayerName[playerid]
				);
				DeliverymanVehicle[i][tvTextID] = CreateDynamic3DTextLabel(
					string, 
					0xFFFFFFA0, 0.0, 0.0, 0.0, 6.0, 
					INVALID_PLAYER_ID, vehid
				); 

				SetPVarInt(playerid, "DeliverymanVehicleID", i);
				break;
			}
		}

		KickPlayerMenu(playerid);
	}
	return 1;
}

stock Player_MarkNextPizzaDelivery(playerid) {
	new subIndex = Houses_Random();

	SetPlayerCheckpoint(
		playerid, House_GetEntryX(subIndex), House_GetEntryY(subIndex), House_GetEntryZ(subIndex), 2.0
	);
	SetPlayerCP(playerid, 45);

	SetPVarInt(playerid, "DeliveringPizza", 1);
	SetPVarInt(playerid, "DeliveryTimeLimit", gettime() + 120);
}

hook OnPlayerEnterCheckpoint(playerid) {
	if(GetPlayerCP(playerid) == 45) {
		if(IsPlayerInAnyVehicle(playerid)) {
			return SendClientMessage(playerid, -1, "Você precisa estar fora do veiculo.");
		}
        
		new pizzas = GetPVarInt(playerid, "DeliverymanPizzas");
		if(pizzas <= 0) {
			return SendClientMessage(playerid, -1, "Você precisa ter uma pizza em mãos. Use /pizza pegar para retirá-la da moto.");
		}
		
        new rdon = random(sizeof(RandomPizzaGorgeta)), 
			rdon2 = random(sizeof(RandomPizzaNome)), 
			precoentrega = 10000 + random(5000), 
			gorgeta = 0,
			timeLimit = GetPVarInt(playerid, "DeliveryTimeLimit");
		
        SendClientMessage(playerid, -1, "|_________________ Entrega _________________|");
		SendMsgF(playerid, -1, "» Pizza: {EBF77E}%s", RandomPizzaNome[rdon2]);
		SendMsgF(playerid, -1, "» Entregou para: {33CCFF}%s", RandomPizzaGorgeta[rdon]);
		SendMsgF(playerid, -1, "» Preço: {00AA00}$%s", getFormatText(precoentrega));
		
		if(gettime() <= timeLimit) {
		    gorgeta = ((timeLimit - gettime()) * 20) + random(1000);
			SendMsgF(playerid, -1, "» Gorgeta: {00AA00}$%s", getFormatText(gorgeta));
		}
		else {
            SendMsgF(playerid, COLOR_LIGHTRED, "» %s diz: Por ter atrasado na entrega, você não vai ganhar gorgeta.", RandomPizzaGorgeta[rdon]);
		}
		
		SendClientMessage(playerid, -1, "_____________________________________________");

		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		PlayerInfo[playerid][pSalario] += precoentrega + gorgeta;

		ShowPlayerMessage(playerid, "~g~Pizza entregue! ~w~Va para a proxima residencia entregar a outra pizza", 7000);

		SetPVarInt(playerid, "DeliverymanPizzas", pizzas - 1);
		if(pizzas - 1 <= 0) {
			RemovePlayerAttachedObject(playerid, Slot_Pizza);
	 		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		}

		new dvid = GetPVarInt(playerid, "DeliverymanVehicleID");
		if(DeliverymanVehiclePizzas[dvid] > 0 || GetPVarInt(playerid, "DeliverymanPizzas") > 0) {
	    	Player_MarkNextPizzaDelivery(playerid);
		}
		else {
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "O baú da sua moto esvaziou, volte na pizzaria para pegar mais pizzas.");
			DisablePlayerCheckpoint(playerid);
		}
        return 1;
	}
	return 1;
}

CMD:pizza(playerid, params[]) {
	if (isnull(params)) {
	    SendClientMessage(playerid, -1, "Modo de uso: /pizza (nome | lista abaixo)");
	    SendClientMessage(playerid, COLOR_GRAY, "Nomes disponíveis: Ajuda | Pegar | PegarTodas | Guardar | GuardarMochila");
		return 1;
	}
	
	new string[128];

	if (!strcmp(params, "ajuda", true)) {
	    ShowHelpJob(playerid, ID_JOB_DELIVERYMAN);
	}
	else if(!strcmp(params, "pegar", true)) {
		
		new dvid = GetPVarInt(playerid, "DeliverymanVehicleID");
		if(!IsPlayerNearOfVehicle(playerid, DeliverymanVehicle[dvid][tvVehicleID], 3.0)) {
			return SendClientMessage(playerid, -1, "Você não está próximo da sua moto de entregas.");
		}
		
		new pizzas = DeliverymanVehiclePizzas[dvid];
		if(pizzas <= 0) {
			return SendClientMessage(playerid, -1, "O baú da sua moto de entregas está vazio.");
		}

		new currentPizzas = GetPVarInt(playerid, "DeliverymanPizzas");
		if(currentPizzas >= 15) {
			return SendClientMessage(playerid, -1, "Você já está carregando 15 pizzas em mãos.");
		}
		
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
		SetPlayerAttachedObject(
			playerid, Slot_Pizza, 1582, 5, 
			0.109999, -0.005000, 0.153000, 
			-85.199981, -13.100001, 10.600001, 
			0.682000, 0.726999, 1.410999
		);

		SetPVarInt(playerid, "DeliverymanPizzas", currentPizzas + 1);
		DeliverymanVehiclePizzas[dvid] = pizzas - 1;

		format(string, sizeof(string), "~r~~h~~h~+%d ~w~Pizza", 1);
		ShowPlayerPopupHUD(playerid, "PIZZARIA", string, 6000);

		format(
			string, sizeof(string), 
			"Moto de %s\nPizzas: %d\nUse /pizza pegar para pegar em mãos", 
			PlayerName[playerid], DeliverymanVehiclePizzas[dvid]
		);
		UpdateDynamic3DTextLabelText(DeliverymanVehicle[dvid][tvTextID], 0xFFFFFFA0, string);
	}
	else if(!strcmp(params, "pegartodas", true)) {
		
		new dvid = GetPVarInt(playerid, "DeliverymanVehicleID");
		if(!IsPlayerNearOfVehicle(playerid, DeliverymanVehicle[dvid][tvVehicleID], 3.0)) {
			return SendClientMessage(playerid, -1, "Você não está próximo da sua moto de entregas.");
		}
		
		new pizzas = DeliverymanVehiclePizzas[dvid];
		if(pizzas <= 0) {
			return SendClientMessage(playerid, -1, "O baú da sua moto de entregas está vazio.");
		}

		new currentPizzas = GetPVarInt(playerid, "DeliverymanPizzas");
		if(currentPizzas >= 15) {
			return SendClientMessage(playerid, -1, "Você já está carregando 15 pizzas em mãos.");
		}
		
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
		SetPlayerAttachedObject(
			playerid, Slot_Pizza, 1582, 5, 
			0.109999, -0.005000, 0.153000, 
			-85.199981, -13.100001, 10.600001, 
			0.682000, 0.726999, 1.410999
		);

		new available = floatround(abs(pizzas - currentPizzas));
		SetPVarInt(playerid, "DeliverymanPizzas", currentPizzas + available);
		DeliverymanVehiclePizzas[dvid] = pizzas - available;

		format(string, sizeof(string), "~r~~h~~h~+%d ~w~Pizza", available);
		ShowPlayerPopupHUD(playerid, "PIZZARIA", string, 6000);

		format(
			string, sizeof(string), 
			"Moto de %s\nPizzas: %d\nUse /pizza pegar para pegar em mãos", 
			PlayerName[playerid], DeliverymanVehiclePizzas[dvid]
		);
		UpdateDynamic3DTextLabelText(DeliverymanVehicle[dvid][tvTextID], 0x89DFE5F9, string);
	}
	else if(!strcmp(params, "guardar", true)) {
		
		new dvid = GetPVarInt(playerid, "DeliverymanVehicleID");
		if(!IsPlayerNearOfVehicle(playerid, DeliverymanVehicle[dvid][tvVehicleID], 3.0)) {
			return SendClientMessage(playerid, -1, "Você não está próximo da sua moto de entregas.");
		}
		
		new pizzas = DeliverymanVehiclePizzas[dvid];
		if(pizzas >= 15) {
			return SendClientMessage(playerid, -1, "O baú da sua moto de entregas está cheia.");
		}

		new currentPizzas = GetPVarInt(playerid, "DeliverymanPizzas");
		if(currentPizzas <= 0) {
			return SendClientMessage(playerid, -1, "Você não está carregando pizzas.");
		}
		
		RemovePlayerAttachedObject(playerid, Slot_Pizza);
	 	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

		new maxPizzas = floatround(abs(pizzas - currentPizzas)),
			available = min(currentPizzas, maxPizzas);

		SetPVarInt(playerid, "DeliverymanPizzas", currentPizzas - available);
		DeliverymanVehiclePizzas[dvid] = pizzas + available;

		format(string, sizeof(string), "Voce guardou ~g~%d pizzas ~w~no bau da moto.", available);
		ShowPlayerMessage(playerid, string, 5000);

		format(
			string, sizeof(string), 
			"Moto de %s\nPizzas: %d\nUse /pizza pegar para pegar em mãos", 
			PlayerName[playerid], DeliverymanVehiclePizzas[dvid]
		);
		UpdateDynamic3DTextLabelText(DeliverymanVehicle[dvid][tvTextID], 0x89DFE5F9, string);
	}
	else if(!strcmp(params, "guardarmochila", true)) {
		
		new currentPizzas = GetPVarInt(playerid, "DeliverymanPizzas");
		if(currentPizzas <= 0) {
			return SendClientMessage(playerid, -1, "Você não está carregando pizzas.");
		}

		if (isInventoryFull(playerid))
			return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");
		
		RemovePlayerAttachedObject(playerid, Slot_Pizza);
	 	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

		SetPVarInt(playerid, "DeliverymanPizzas", 0);

		givePlayerItem(playerid, ITEM_TYPE_COMIDA, 1582, currentPizzas, "Pizza");

		format(string, sizeof(string), "~r~~h~~h~+%d ~w~Pizza", currentPizzas);
		ShowPlayerPopupHUD(playerid, "NOVO ITEM RECEBIDO", string, 6000);
	}
	else if(!strcmp(params, "entregar", true)) {
		
		new dvid = GetPVarInt(playerid, "DeliverymanVehicleID");
		if(!IsPlayerNearOfVehicle(playerid, DeliverymanVehicle[dvid][tvVehicleID], 3.0)) {
			return SendClientMessage(playerid, -1, "Você não está próximo da sua moto de entregas.");
		}
		
		new pizzas = DeliverymanVehiclePizzas[dvid];
		if(pizzas <= 0) {
			return SendClientMessage(playerid, -1, "O baú da sua moto de entregas está vazio.");
		}

		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Agora vá ate a residencia marcada no mapa para entregar uma pizza.");
		SendClientMessage(playerid, COLOR_LIGHTRED, "* Caso você queira cancelar a entrega digite /pizza cancelar");

		Player_MarkNextPizzaDelivery(playerid);
	}	

	else if(!strcmp(params, "cancelar", true)) {
		
		if(!GetPVarInt(playerid, "DeliveringPizza")) {
			return SendClientMessage(playerid, -1, "Você não iniciou entregas como entregador de pizza.");
		}

		SetPVarInt(playerid, "DeliveringPizza", 0);
		SendClientMessage(playerid, COLOR_LIGHTRED, "Você cancelou as entregas como entregador de pizza!");
		DisablePlayerCheckpoint(playerid);
	}	
	return 1;
}
