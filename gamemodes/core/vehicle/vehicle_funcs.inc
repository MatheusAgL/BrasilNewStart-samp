#include <YSI_Coding\y_hooks>

enum caminhaoEnum
{
	bool:caminhaoValid,
	caminhaoId, 
	carretaId,
	caminhaoCarga,
	caminhaoMaxCarga,
	caminhaoTipoCarga
}
new PlayerCaminhao[MAX_PLAYERS][caminhaoEnum];

new dinheiroStrongCar[MAX_VEHICLES];

stock Vehicle_IsCaminhao(playerid) {
	return PlayerCaminhao[playerid][caminhaoValid];
}

hook OnPlayerWeaponShot(playerid, weaponid, BULLET_HIT_TYPE:hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	// Chama a callback de atingir o veículo:
	if ((hittype == BULLET_HIT_TYPE_VEHICLE) && (22 <= weaponid <= 38)) {
	    CallLocalFunction("OnPlayerShootVehicle", "iii", playerid, hitid, weaponid);
	}
	return 1;
}

stock IsVehicleOwner(playerid, carid)
{
	if(IsAPilotoCar(carid) && HasPlayerJob(playerid, ID_JOB_PILOTO))
		return true;

	if (IsPlayerVehicleOwner(playerid, carid))
		return true;
	
	if (PlayerCaminhao[playerid][caminhaoId] == carid)
		return true;

	if (Admin_GetNivel(playerid) > AdminNivel:2)
		return true;

	return false;
}

CALLBACK: consertarVeh(playerid, vehicleid) {

	new index = getVehicleProxPlayer(playerid, 8.0, INVALID_VEHICLE_ID);

	if (index != vehicleid) {
 		SendClientMessage(playerid, -1, "Você não está perto do veículo que estava consertando!");
		ApplyAnimation(playerid,"CAR","Fixn_Car_Out",4.1,0,1,1,0,0, FORCE_SYNC:1);
	   	DeletePVar(playerid, "consertandoVeh");
   		return 0;
   	}

	new Float:healthVehicle;

	GetVehicleHealth(vehicleid, healthVehicle);

	if (healthVehicle >= 1000.0) {
 		SendClientMessage(playerid, -1, "Este veículo não precisa ser consertado!");
		ApplyAnimation(playerid,"CAR","Fixn_Car_Out",4.1,0,1,1,0,0, FORCE_SYNC:1);
	   	DeletePVar(playerid, "consertandoVeh");
   		return 0;
   	}

   	healthVehicle += 350.0;

   	if (healthVehicle >= 1000.0) {
   	    healthVehicle = 1000.0;
   	    RepairVehicle(vehicleid);
   	    SendClientMessage(playerid, -1, "Você usou um kit de reparo neste veículo, ele foi consertado totalmente.");
   	} else {
   		SetVehicleHealth(vehicleid, healthVehicle);
   		SendClientMessage(playerid, -1, "Você usou um kit de reparo neste veículo. Nem todas as partes puderam ser consertadas.");
	}

	ApplyAnimation(playerid,"CAR","Fixn_Car_Out", 4.1, 0, 1, 1, 0, 0, FORCE_SYNC:1);
   	DeletePVar(playerid, "consertandoVeh");
   	return 1;
}

CALLBACK: fixPlayerAnimation(playerid)
	return ApplyAnimation(playerid,"CAR","Fixn_Car_Loop",4.1,1,0,0,1,0);

stock CheckChave(playerid, vehicleid)
{
	new VIM:vim = Vehicle_GetVIM(vehicleid);

	if ((VIM_IsBike(vim) || VIM_IsManual(vim)))
	{
		if(GetPlayerOrg(playerid) == 16)
			return SendClientMessage(playerid, -1, "* Você pode pilotar essa moto, pois ela tem multas pendentes !"), false;
	}

	if (!IsPlayerOwnerVehFamily(playerid, vehicleid))
	{
	    if (GetVehicleFamily(vehicleid) != -1)
			return SendClientMessage(playerid, -1, "Este veículo pertence a uma família diferente da sua!");
	}

	new orgid = GetVehicleOrgID(vehicleid);
	if (!CanPlayerDriveVehicleOrg(playerid, vehicleid, orgid)) {
		return SendMsgF(playerid, -1, "Você não pode dirigir o veículo da organização %s na zona da HQ.", GetNomeOrg(orgid));
	}
	
	return false;
}

stock UpdateVehiclePlateInfo(plate[], newowner[])
{
	new log_query[128];

	mysql_format(MySQL_Handle, log_query, sizeof(log_query), "UPDATE `placas_dono` SET `dono` = '%s' WHERE placa = '%s'", plate, newowner);
	mysql_tquery(MySQL_Handle, log_query);
}

// stock removeVehiclePlate(vehicleid)
// {
// 	new log_query[75],
// 		plate[10];

// 	GetVehicleNumberPlate(vehicleid, plate);

// 	mysql_format(MySQL_Handle, log_query, sizeof(log_query), "DELETE FROM `placas_dono` WHERE `placa` = '%s'", plate);
// 	mysql_tquery(MySQL_Handle, log_query);

// 	format(log_query, sizeof(log_query), "DELETE FROM `placas` WHERE `placa` = '%s'", plate);
// 	mysql_tquery(MySQL_Handle, log_query);
// }

// stock registerVehiclePlateInfo(vehicleid, const type[], const desc[], const agente[], multa=0)
// {
// 	static log_query[248],
// 		plate[10];

// 	GetVehicleNumberPlate(vehicleid, plate);

// 	mysql_format(MySQL_Handle, log_query, sizeof(log_query), "INSERT INTO `placas` (`placa`,`tipo`,`data`,`descricao`,`agente`,`multa`) VALUES ('%s','%s',CURRENT_TIMESTAMP(),'%s','%s','%d')", plate, type, desc, agente, multa);
// 	mysql_tquery(MySQL_Handle, log_query);
// }

stock registerVehiclePlateInfoEx(const numberplate[], const type[], const desc[], const agente[], multa=0) 
{
	new log_query[248];

	mysql_format(MySQL_Handle, log_query, sizeof(log_query), "INSERT INTO `placas` (`placa`,`tipo`,`data`,`descricao`,`agente`,`multa`) VALUES ('%s','%s',CURRENT_TIMESTAMP(),'%s','%s','%d')",
	numberplate, type, desc, agente, multa);
	mysql_tquery(MySQL_Handle, log_query);
}