#include <YSI_Coding\y_hooks>

#define MAX_SEMENTE_TIPO 5

new Timer:colheitapickup[MAX_PLAYERS],
	FenoPlantado[MAX_PLAYERS][5],
	Planta[MAX_PLAYERS][5],
	Sementes[MAX_PLAYERS],
	PegaSemente[MAX_PLAYERS],
	PegaPlanta[MAX_PLAYERS],
	TempoPlantar[MAX_PLAYERS],
	PegouFeno[MAX_PLAYERS],
	tempocolheita[MAX_PLAYERS],
	Float:plantaX[MAX_PLAYERS][5],
	Float:plantaY[MAX_PLAYERS][5],
	Float:plantaZ[MAX_PLAYERS][5];

enum    e_sementes
{
	NomeSemente[16],
	Color,
	ColorStr[8],
	ValorSemente, 
	BonusSemente
};

//Milho, Trigo, Soja, Café e Arroz

new
	SementeData[MAX_SEMENTE_TIPO][e_sementes] = {
	    {"Trigo", 0xC9BB89FF, "C9BB89", 15000, 55},
	    {"Milho", 0xF0D36EFF, "F0D36E", 16000, 50},
	    {"Arroz", 0xBDBDBDFF, "BDBDBD", 18500, 80},
		{"Soja", 0xABAB46FF, "ABAB46", 24500, 70},
		{"Café", 0x5C5C51FF, "5C5C51", 28000, 56}
	};

stock CarrosPlantacao(carid)
{
	for(new i = 3; i <= 9; i++) {
		if(carid == CarrosFazendeiros[i])
			return 1;
	}
	return 0;
}

stock CarrosColheita(carid)
{
	for(new i = 10; i <= 15; i++) {
		if(carid == CarrosFazendeiros[i])
			return 1;
	}
	return 0;
}

timer PickupFazendeiro[1000](playerid)
{
    new vid = GetPlayerVehicleID(playerid);
    new modelo = GetVehicleModel(vid);
    if(IsPlayerConnected(playerid))
    {
		for(new i = 0; i < 5; i++) {
			if(PlayerToPoint(3.0, playerid, plantaX[playerid][i], plantaY[playerid][i], plantaZ[playerid][i]))
			{
				if(!IsPlayerInVehicle(playerid, vid) || modelo != 532)
					return 1;
				
				PegaPlanta[playerid] -= 1;
				tempocolheita[playerid] = i+1;
				DestroyDynamicPickup(Planta[playerid][i]);
				FenoPlantado[playerid][i] = CreateDynamicPickup(2901, 23, plantaX[playerid][i], plantaY[playerid][i], plantaZ[playerid][i]);
			}
		}

		if(tempocolheita[playerid] == 5)
		{
			PegaPlanta[playerid] = 0;
			tempocolheita[playerid] = 0;
			stop colheitapickup[playerid];
		}
	}
	return 1;
}

CMD:plantar(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(!IsPlayerInVehicle(playerid, vehicleid))
		return SendClientMessage(playerid, -1, "Para plantar uma semente, você deve estar em um trator !");
		
	new modeloo = GetVehicleModel(vehicleid);
	if(PlayerInfo[playerid][pEmprego] != 10)
		return SendClientMessage(playerid, -1,"Você não é um fazendeiro !");
	else if(modeloo != 531)
		return SendClientMessage(playerid, -1, "Para plantar uma semente, você deve estar em um trator !");
	else if(!PlayerToPoint(80.0, playerid, -206.3168, 11.2350, 3.1172))
		return SendClientMessage(playerid, -1, "Você precisa estar na plantação para plantar uma semente !");
	else if(Sementes[playerid] < 1)
		return SendClientMessage(playerid, -1, "Você não possui sementes !");

	new semente = 5 - Sementes[playerid];

	for(new i = 0; i < semente; i++){
		if(PlayerToPoint(35.0, playerid, plantaX[playerid][i], plantaY[playerid][i], plantaZ[playerid][i]))
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você está muito próximo de uma semente que você já plantou.");
	}

	if(Sementes[playerid] >= 2 && Sementes[playerid] <= 5)
	{
		Sementes[playerid] -= 1;
		PegaSemente[playerid] = 5;
		PegaPlanta[playerid] = -1;
		GetPlayerPos(playerid, plantaX[playerid][semente], plantaY[playerid][semente], plantaZ[playerid][semente]);
		Planta[playerid][semente] = CreateDynamicPickup(872, 1, plantaX[playerid][semente], plantaY[playerid][semente], plantaZ[playerid][semente], 0, 0, playerid);
		SendMsgF(playerid, -1, "Você plantou uma semente e ainda lhe restam %d sementes para serem plantadas.", Sementes[playerid]);
		TempoPlantar[playerid] = GetTickCount();
	}
	else if(Sementes[playerid] == 1) {
		Sementes[playerid] = 0;
		PegaPlanta[playerid] -= 1;
		GetPlayerPos(playerid, plantaX[playerid][semente], plantaY[playerid][semente], plantaZ[playerid][semente]);
		SetPlayerCheckpoint(playerid, -155.5231,-34.9998,3.1172, 8.0);
		Planta[playerid][semente] = CreateDynamicPickup(872, 1, plantaX[playerid][semente], plantaY[playerid][semente], plantaZ[playerid][semente], 0, 0, playerid);
		SendClientMessage(playerid, -1, "Você terminou de plantar as 5 sementes, pegue a Colheitadeira e passe em cima das plantas!");
		SetVehicleToRespawn(vehicleid);
		RemovePlayerAttachedObject(playerid,9);
		TempoPlantar[playerid] = GetTickCount();
	}
	colheitapickup[playerid] = repeat PickupFazendeiro(playerid);
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (newkeys & KEY_YES)
	{
		if(PlayerToPoint(2.0, playerid, -109.4007,-3.2842,3.1172))
		{
			ShowPlayerDialog(playerid, 120, DIALOG_STYLE_LIST, "Armazém do Fazendeiro", "Coletar sementes\nEntregar colheita\nAjuda", "Confirmar", "Cancelar");
		}
	}
	return 1;
}

hook OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate) 
{
	if(newstate == PLAYER_STATE_DRIVER)
    {
		new newcar = GetPlayerVehicleID(playerid);
		if(CarrosColheita(newcar))
		{
			if(Sementes[playerid] >= 1)
			{
				SendMsgF(playerid, 0x33FF00FF, "Fazendeiro, você possui [%d] sementes, vá até a plantação e termine de plantar antes de vir colher!", Sementes[playerid]);
				RemovePlayerFromVehicle(playerid);
			}
			else if(Sementes[playerid] == 0)
			{
				SendClientMessage(playerid, 0x33FF00FF, "Fazendeiro, se você já plantou as sementes, vá até a plantação e faça a colheita com este veículo!");
			}
		}
		else if(CarrosPlantacao(newcar))
		{
			if(Sementes[playerid] >= 1)
				SendMsgF(playerid, 0x33FF00FF, "Fazendeiro, vejo que você possui [%d] sementes, vá até a plantação e digite: /plantar!",Sementes);
			else if(Sementes[playerid] == 0)
			{
				SendClientMessage(playerid, 0x33FF00FF, "Fazendeiro, você não possui sementes, vá até o menu dos fazendeiros e pegue um pacote.");
				SetPlayerCheckpoint(playerid, -112.5062,-10.4502,3.1094,8.0);
				RemovePlayerFromVehicle(playerid);
			}
		}
	}
	return 1;
}

hook OP_PickUpDynamicPickup(playerid, pickupid)
{
	for(new i = 0; i < 5; i++) {
		if(pickupid == FenoPlantado[playerid][i])
		{
			if(PlayerToPoint(2.0, playerid, plantaX[playerid][i], plantaY[playerid][i], plantaZ[playerid][i]))
			{
				if(PegouFeno[playerid] == 1)
					return 1;
				if(PegaSemente[playerid] == 1)
					PegaSemente[playerid] = 0;
				else
					PegaSemente[playerid] --;

				PegaSemente[playerid] -= 1;
				PegouFeno[playerid] = 1;
				DestroyDynamicPickup(FenoPlantado[playerid][i]);
				ApplyAnimation(playerid, "BOMBER","BOM_Plant_In",4.0,0,0,0,0,0);
				SetPlayerAttachedObject(playerid, 9, 2901, 1, 0.000000, -0.313611, 0.021003, 0.445490, 86.754409, 355.370239, 0.926815, 1.000000, 1.000000);
				SendClientMessage(playerid, COLOR_GREEN, "Você pegou um pacote de colheita, vá até o Armazem para entregá-lo.");
				SetPlayerCheckpoint(playerid, -125.2856,8.4045,3.1172,8.0);
				break;
			}
		}
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == 120) //dialog fazendeiro
    {
        if(response)
		{
            if(listitem == 0)
			{
				if(Sementes[playerid] > 0)
					return SendClientMessage(playerid, -1, "Você ainda tem sementes, plante todas e depois volte aqui !");
				else if(PegaSemente[playerid] > 0)
					return SendClientMessage(playerid, -1, "Você ainda não recolheu todos os fenos, recolhe-os e volte aqui !");
                else if(PegaPlanta[playerid] > 0)
					return SendClientMessage(playerid, -1, "Você ainda não colheu todas as plantas, recolhe-as e volte aqui !");
				
				PegaPlanta[playerid] = 5;
                Sementes[playerid] = 5;
                SetPlayerCheckpoint(playerid, -110.6766,-37.7048,3.1172, 8.0);

				new semente = random(MAX_SEMENTE_TIPO);
				SetPVarInt(playerid, "tipoSemente", semente);
                SendMsgF(playerid, -1, "Você pegou um pacote com 5 sementes de {%s}%s{FFFFFF}. Entre no Trator de plantação!", SementeData[semente][ColorStr], SementeData[semente][NomeSemente]);
                SetPlayerAttachedObject(playerid, 9, 2060, 1, 0.000000, -0.313611, 0.021003, 0.445490, 86.754409, 355.370239, 0.926815, 1.000000, 1.000000);
            }
            else if(listitem == 1)
            {
                if(PegouFeno[playerid] == 0)
					return SendClientMessage(playerid, -1, "Você ainda não recolheu os fenos colhidos, volte e recolha-os !");
                
				new tipo = GetPVarInt(playerid, "tipoSemente");
				new salario = SementeData[tipo][ValorSemente] + random(SementeData[tipo][BonusSemente] + GetWageJob(ID_JOB_FAZENDEIRO));
				PegouFeno[playerid] = 0;
				PlayerInfo[playerid][pSalario] += salario;
				removerDinheiroGoverno(salario);
				RemovePlayerAttachedObject(playerid,9);
				SendMsgF(playerid, 0xE0D78AFF, "<< Fazendeiro >> {FFFFFF}Você entregou um pacote de {%s}%s {FFFFFF}e foi adicionado {00AA00}$%s {FFFFFF}ao seu salário.", SementeData[tipo][ColorStr], SementeData[tipo][NomeSemente], getFormatText(salario));
            }
			else if(listitem == 2) {
				ShowHelpJob(playerid, ID_JOB_FAZENDEIRO);
			}
        }
        return 0;
    }
	return 1;
}

hook OnGameModeInit()
{
	CreateDynamicPickup(2060, 23, -109.4007,-3.2842,3.1172);//Menu Fazendeiro
	CreateDynamic3DTextLabel("Armazém dos Fazendeiros\nAperte "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para acessar", 0xFFFFFFFF,-109.4007,-3.2842,3.1172,10.0);
    return 1;
}