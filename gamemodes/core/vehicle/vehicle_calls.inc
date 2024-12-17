public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	if (InTeste[playerid])
	{
	    SendClientMessage(playerid, COLOR_YELLOW, "((DETRAN)): {FFFFFF}Você bateu o veículo, dirija corretamente.");
	    SetPVarInt(playerid, "WarnningDamage", GetPVarInt(playerid, "WarnningDamage") + 1);
		return 1;
	}

	if (GetVehicleModel(vehicleid) == 428) {
	    SetVehicleHealth(vehicleid, 10000);
	}

	new VIM:vim = Vehicle_GetVIM(vehicleid);
	if (!VIM_IsPlane(vim))
	{
		new Float:health;

		GetVehicleHealth(vehicleid, health);

		if(health < 20 && health > 1)
		{
			StopVehicleEngine(vehicleid);

			SendClientMessage(playerid, COLOR_LIGHTRED, "O motor do veículo fundiu, use um kit reparo.");
			GameTextForPlayer(playerid, "~r~Motor avariado", 5000, 1);
		}
	}

	new panels, 
		doors, 
		lights, 
		tires;

    if (GetVehicleModel(vehicleid) == 463) {
		GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires); // Irá getar a lataria do veículo que o player está usando (Portas, Luzes, Rodas, etc...)
		UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, VEHICLE_TYRE_STATUS_NONE); // Seta todos os pneus como normal
	}

	return true;
}

public OnVehicleStreamIn(vehicleid, forplayerid) 
{
	if (IsVehicleLocked(vehicleid))
		SetVehicleParamsForPlayer(vehicleid, forplayerid, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_ON);
	else
		SetVehicleParamsForPlayer(vehicleid, forplayerid, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF);
	
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	RemoveNeonFromVehicle(vehicleid);

   	dinheiroStrongCar[vehicleid] = 0;

	switch (GetVehicleModel(vehicleid))
	{
	    case 432: SetVehicleHealth(vehicleid, 10000);
	    case 428, 425, 433, 427, 490, 520, 528, 599, 601, 470: SetVehicleHealth(vehicleid, 4000);
		case 409: SetVehicleHealth(vehicleid, 7000), AddVehicleComponent(vehicleid, 1073);
	}
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	RemoveNeonFromVehicle(vehicleid);
	StopVehicleEngine(vehicleid);
   	dinheiroStrongCar[vehicleid] = 0;

	foreach(new i : Player)
	{
	    if (GetPVarInt(i, "jatoId") == vehicleid)
		{
	        SetPlayerHealth(i, 0.0);
	        SendClientMessage(i, COLOR_LIGHTRED, "O avião em que você está, acaba de explodir!");
	        SetPVarInt(i, "jatoId", INVALID_VEHICLE_ID);
	    }
		if (GetPVarInt(i, "playerEnforcer") == vehicleid)
		{
	        SetPlayerHealth(i, 0.0);
	        SendClientMessage(i, COLOR_LIGHTRED, "O enforcer em que você está, acaba de explodir!");
	        SetPVarInt(i, "playerEnforcer", INVALID_VEHICLE_ID);
	    }
	    if (IsPlayerInDrone(i) && PlayerDrone[i][droneId] == vehicleid)
		{
			CancelPlayerDrone(i);
	    }
	    if (PlayerCaminhao[i][caminhaoValid] && PlayerCaminhao[i][caminhaoId] == vehicleid)
		{
			DestroyPlayerCaminhao(i);
	    }

		VehiclePlayer_Death(vehicleid, i);
	}
    return 1;
}