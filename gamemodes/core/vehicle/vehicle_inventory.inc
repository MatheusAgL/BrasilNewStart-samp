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
	if (IsPlayerInDrone(playerid)) return SendClientMessage(playerid, COLOR_LIGHTRED, "Voc� j� est� usando um ve�culo de invent�rio."), false;
	
	if ((GetPlayerAnimationIndex(playerid) >= 260 && GetPlayerAnimationIndex(playerid) <= 262)) return false;

	if (GetPlayerInterior(playerid) != 0 && (GetPlayerInterior(playerid) != 7 && GetPlayerVirtualWorld(playerid) != 10056))
		return SendClientMessage(playerid, COLOR_LIGHTRED, "Voc� n�o est� em um local adequado para usar seu ve�culo de invent�rio"), false;

	if (IsPlayerInCombat(playerid)) return SendClientMessage(playerid, -1, "Voc� n�o pode usar ve�culo de invent�rio em combate."), false;
	
	if (GetPlayerInterior(playerid) == 7 && GetPlayerVirtualWorld(playerid) == 10056 && Player_GetMoney(playerid) < 10000)
		return SendClientMessage(playerid, -1, "Voc� precisa ter $10.000 para usar ve�culos nesse local."), false;

	// Pegar a posi��o
	new Float:playerPos[4], Float:diminuirZ;
	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
	GetPlayerFacingAngle(playerid, playerPos[3]);
	
	switch (modelid)
	{
	    case 548, 515: 				diminuirZ = playerPos[2] + 0.3;
	    case 460, 553, 512: 		diminuirZ = playerPos[2] + 0.9;
	    default: 					diminuirZ = playerPos[2] - 0.5;
	}

    // Limpa as anima��es e special action para n�o ter bugs
    ClearAnimations(playerid);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    
	// Esconder o inventario
	Inventory_HideForPlayer(playerid);

	// Informa��es
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
        SendClientMessage(playerid, -1, "Voc� pagou {00AA00}$500 {FFFFFF}para a {00BFFF}8-Track Stadium");
		Player_RemoveMoney(playerid, 500);
		DepositPropertie(playerid, 500);
	}

	UnlockVehicleDoors(PlayerDrone[playerid][droneId]);

	// Colocar o jogador no drone
	PutPlayerInVehicle(playerid, PlayerDrone[playerid][droneId], 0);
	
	// Abastece o ve�culo
	VehicleInfo[GetPlayerVehicleID(playerid)][vehicleCombustivel] = 100;

	// Enviar uma mensagem
	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Voc� est� em seu ve�culo de invent�rio. Aperte ENTER para desliga-lo.");
	
	StopVehicleEngine(GetPlayerVehicleID(playerid));
	StartVehicleEngine(GetPlayerVehicleID(playerid));
	return 1;
}

stock CancelPlayerDrone(playerid)
{
    if (!IsPlayerInDrone(playerid)) 
		return false; // Verifica se o jogador est� em um drone (ve�culo de invent�rio).
    
    PlayerDrone[playerid][droneValid] = false; // Remove o jogador do drone (ve�culo de invent�rio).

	new vehicleid = PlayerDrone[playerid][droneId];
	VehicleInfo[vehicleid][vhType] = VH_TYPE_COMMON;
	VehicleInfo[vehicleid][vhInfoID] = 0;

	SetPVarInt(playerid, "isPlayerEnteringVehicle", 0);

    return DestroyVehicle(vehicleid); // Destruir o drone (ve�culo de invent�rio).
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (IsPlayerInDrone(playerid))
	{
	    if ((newkeys & 16))
		{
	       	CancelPlayerDrone(playerid);
	        
	       	SendClientMessage(playerid, COLOR_LIGHTRED, "* Voc� desligou seu ve�culo de brinquedo!");
	    }
	    else if ((newkeys & 1))
		{
		    new droneID = PlayerDrone[playerid][droneId];

	        if (GetVehicleModel(droneID) != 425 && GetVehicleModel(droneID) != 520 && GetVehicleModel(droneID) != 476 && GetVehicleModel(droneID) != 447 && GetVehicleModel(droneID) != 481
			&& GetVehicleModel(droneID) != 509 && GetVehicleModel(droneID) != 510)
			{
			    CancelPlayerDrone(playerid);
		        SendClientMessage(playerid, COLOR_LIGHTRED, "* Voc� desligou seu ve�culo de brinquedo!");
			}
		}
	}
	return 1;
}
