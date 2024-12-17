#include <YSI_Coding\y_hooks>

enum droneEnum {
	bool:droneValid,
	droneId,
	droneModel,
}
stock PlayerDrone[MAX_PLAYERS][droneEnum];

stock IsPlayerInDrone(playerid) return PlayerDrone[playerid][droneValid];

hook OnPlayerSpawn(playerid) 
{
	if (IsPlayerInDrone(playerid))
		CancelPlayerDrone(playerid);
	
	return 1;
}

stock SetPlayerDrone(playerid, modelid, cor1, cor2)
{
	if (IsPlayerInDrone(playerid)) return SendClientMessage(playerid, COLOR_LIGHTRED, "Você já está usando um veículo de inventário."), false;
	
	if ((GetPlayerAnimationIndex(playerid) >= 260 && GetPlayerAnimationIndex(playerid) <= 262)) return false;

	if (GetPlayerInterior(playerid) != 0 && (GetPlayerInterior(playerid) != 7 && GetPlayerVirtualWorld(playerid) != 10056))
		return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não está em um local adequado para usar seu veículo de inventário"), false;

	if (IsPlayerInCombat(playerid)) return SendClientMessage(playerid, -1, "Você não pode usar veículo de inventário em combate."), false;
	
	if (GetPlayerInterior(playerid) == 7 && GetPlayerVirtualWorld(playerid) == 10056 && Player_GetMoney(playerid) < 10000)
		return SendClientMessage(playerid, -1, "Você precisa ter $10.000 para usar veículos nesse local."), false;

	// Pegar a posição
	new Float:playerPos[4], Float:diminuirZ;
	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
	GetPlayerFacingAngle(playerid, playerPos[3]);
	
	switch (modelid)
	{
	    case 548, 515: 				diminuirZ = playerPos[2] + 0.3;
	    case 460, 553, 512: 		diminuirZ = playerPos[2] + 0.9;
	    default: 					diminuirZ = playerPos[2] - 0.5;
	}

    // Limpa as animações e special action para não ter bugs
    ClearAnimations(playerid);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    
	// Esconder o inventario
	Inventory_HideForPlayer(playerid);

	// Informações
	PlayerDrone[playerid][droneValid] = true;
	PlayerDrone[playerid][droneId]    = CreateVehicle(modelid, playerPos[0], playerPos[1], diminuirZ, playerPos[3], cor1, cor2, -1);

	new vehicleid = PlayerDrone[playerid][droneId];
	VehicleInfo[vehicleid][vhType] = VH_TYPE_DRONE;
	VehicleInfo[vehicleid][vhInfoID] = playerid;

    // No interior da 8-Track Stadium
    if (GetPlayerInterior(playerid) == 7 && GetPlayerVirtualWorld(playerid) == 10056)
	{
    	LinkVehicleToInterior(PlayerDrone[playerid][droneId], GetPlayerInterior(playerid));
    	SetVehicleVirtualWorld(PlayerDrone[playerid][droneId], GetPlayerVirtualWorld(playerid));
        SendClientMessage(playerid, -1, "Você pagou {00AA00}$500 {FFFFFF}para a {00BFFF}8-Track Stadium");
		Player_RemoveMoney(playerid, 500);
		DepositPropertie(playerid, 500);
	}

	UnlockVehicleDoors(PlayerDrone[playerid][droneId]);

	// Colocar o jogador no drone
	PutPlayerInVehicle(playerid, PlayerDrone[playerid][droneId], 0);
	
	// Abastece o veículo
	VehicleInfo[GetPlayerVehicleID(playerid)][vehicleCombustivel] = 100;

	// Enviar uma mensagem
	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você está em seu veículo de inventário. Aperte ENTER para desliga-lo.");
	
	StopVehicleEngine(GetPlayerVehicleID(playerid));
	StartVehicleEngine(GetPlayerVehicleID(playerid));
	return 1;
}

stock CancelPlayerDrone(playerid)
{
    if (!IsPlayerInDrone(playerid)) 
		return false; // Verifica se o jogador está em um drone (veículo de inventário).
    
    PlayerDrone[playerid][droneValid] = false; // Remove o jogador do drone (veículo de inventário).

	new vehicleid = PlayerDrone[playerid][droneId];
	VehicleInfo[vehicleid][vhType] = VH_TYPE_COMMON;
	VehicleInfo[vehicleid][vhInfoID] = 0;

	SetPVarInt(playerid, "isPlayerEnteringVehicle", 0);

    return DestroyVehicle(vehicleid); // Destruir o drone (veículo de inventário).
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (IsPlayerInDrone(playerid))
	{
	    if ((newkeys & 16))
		{
	       	CancelPlayerDrone(playerid);
	        
	       	SendClientMessage(playerid, COLOR_LIGHTRED, "* Você desligou seu veículo de brinquedo!");
	    }
	    else if ((newkeys & 1))
		{
		    new droneID = PlayerDrone[playerid][droneId];

	        if (GetVehicleModel(droneID) != 425 && GetVehicleModel(droneID) != 520 && GetVehicleModel(droneID) != 476 && GetVehicleModel(droneID) != 447 && GetVehicleModel(droneID) != 481
			&& GetVehicleModel(droneID) != 509 && GetVehicleModel(droneID) != 510)
			{
			    CancelPlayerDrone(playerid);
		        SendClientMessage(playerid, COLOR_LIGHTRED, "* Você desligou seu veículo de brinquedo!");
			}
		}
	}
	return 1;
}
