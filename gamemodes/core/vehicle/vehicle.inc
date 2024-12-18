/*

    Configura��es dos ve�culos

    �ltima modifica��o: 01/12/2020
    Respons�vel: Theus_Crazzy

*/

// ---------------------------------------------------------------------------
// YSI-Includes: Vehicles;
#include <YSI_Game\y_vehicledata>

// Bibliotecas e configura��es de ve�culos (dependencia adaptada)
#include <tdw_vehicle>
#include <tdw_vdetail>
#include <tdw_vmath>
#include <tdw_vutils>
#include < tdw_vsa_data >
#include < tdw_vyengine >
#include < tdw_vxplight >
#include < tdw_vxneon >
#include < tdw_vylock >

#include <EVF>

#include <vehicle_entry>
#include <vehicle_velocity>
#include <vehicle_heli_ropes>
// #include <vehicle_drift>

// Com�rcio: Concession�rias
#include <dealership>

#include <vehicle_funcs>
#include <vehicle_body_text>

#include <vehicle_inventory>

// C�mera em primeira pessoa no ve�culo
#include <vehicle_first_person>

// Callbacks:
#include <vehicle_calls>

stock HasPlayerVehicleKey(playerid, vehicleid, ignore_type) {
	if(ignore_type == 0) {
		return (
			IsVehicleOwner(playerid, vehicleid) || 
			GetPlayerOrg(playerid) == GetVehicleOrgID(vehicleid) || 
			(GetPlayerFamily(playerid) != -1 && GetPlayerFamily(playerid) == GetVehicleFamily(vehicleid) || 
			IsVehicleGarageOwner(playerid, vehicleid))
		);
	}
	
	new orgid = GetVehicleOrgID(vehicleid);
	return orgid == -1 || GetPlayerOrg(playerid) == orgid;
}

CMD:trancar(playerid)
{
	if (gettime() < GetPVarInt(playerid, "varFlood_cmd")) 
		return SendClientMessage(playerid, -1, "Voc� n�o pode usar essa fun��o com tanta frequ�ncia.");

	new carid = GetNearestVehicle(playerid);

	if (carid != INVALID_VEHICLE_ID)
	{
		if (HasPlayerVehicleKey(playerid, carid, 0))
		{
			if (!IsVehicleLocked(carid))
			{
				GameTextForPlayer(playerid, "~w~veiculo ~r~~h~fechado", 5000, 6);

				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);

				LockVehicleDoors(carid);

				SetPVarInt(playerid, "varFlood_cmd", gettime() + 2);
			}
			else
			{
				GameTextForPlayer(playerid, "~w~veiculo ~g~~h~aberto", 5000, 6);

				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
				UnlockVehicleDoors(carid);

				SetPVarInt(playerid, "varFlood_cmd", gettime() + 2);
			}
		}
		else
		{
			SendClientMessage(playerid, -1, "Voc� n�o possui a chave desse ve�culo.");

			PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
		}
	}
	return 1;
}
alias:trancar("destrancar")

CMD:motor(playerid)
{
	if (!IsPlayerInAnyVehicle(playerid)) 
		return SendClientMessage(playerid, -1, "Voc� n�o est� em um ve�culo.");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendClientMessage(playerid, -1, "Voc� n�o � o motorista do ve�culo.");

	new vehicleid = GetPlayerVehicleID(playerid);

	if (VehicleInfo[vehicleid][vehicleCombustivel] < 2) 
		return SendClientMessage(playerid, 0x84C0A3FF, "Combust�vel esgotado. Procure um posto mais pr�ximo para comprar gal�o! (/gps)");

	new string[128];

	if (IsVehicleEngineStarted(vehicleid))
	{
		format(string, sizeof(string), "(( %s desligou seu veiculo ))", PlayerName[playerid]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
		StopVehicleEngine(vehicleid);
	}
	else if(!HasPlayerVehicleKey(playerid, vehicleid, 1)) {
		SendClientMessage(playerid, -1, "Voc� n�o possui a chave para ligar esse ve�culo!");
		PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
	}
	else
	{
		format(string, sizeof(string), "(( %s girou a chave para ligar o veiculo ))", PlayerName[playerid]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
		StartVehicleEngine(vehicleid);
	}
	return 1;
}

CMD:farol(playerid)
{
	if (!IsPlayerInAnyVehicle(playerid)) 
		return SendClientMessage(playerid, -1, "Voc� n�o est� em um ve�culo.");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendClientMessage(playerid, -1, "Voc� n�o � o motorista do ve�culo.");

	new vehicleid = GetPlayerVehicleID(playerid),
		string[128];

	if (IsVehicleLightsStarted(vehicleid))
	{
		format(string, sizeof(string), "(( %s desligou os farois do veiculo ))", PlayerName[playerid]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		StopVehicleLights(vehicleid);
	}
	else
	{
		format(string, sizeof(string), "(( %s ligou os farois do veiculo ))", PlayerName[playerid]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		StartVehicleLights(vehicleid);
	}
	return 1;
}