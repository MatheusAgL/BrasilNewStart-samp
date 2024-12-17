

enum {
	VH_TYPE_COMMON,
	VH_TYPE_JOB,
	VH_TYPE_ORG,
	VH_TYPE_FAMILY,
	VH_TYPE_DRONE,
	VH_TYPE_SALE
};

enum vehicleEnum
{
	vehicleCombustivel,
	vehicleCombUpdate,
	vhType,
	vhInfoID,
	vhPlate[10],
	vhArrested,
	vhTemp
};
new VehicleInfo[MAX_VEHICLES][vehicleEnum];
new bool:Plataforma[MAX_VEHICLES];
new vanEquipamentos[MAX_VEHICLES];
new vanEquipamentosTime[MAX_VEHICLES];
new CarrosAdmin[15];

enum tempVehicleEnum
{
	tvCreated,
	tvVehicleID,
	tvModelID,
	tvPlayerID,
	Text3D:tvTextID
};

CALLBACK:GetPlayerTempVehicleID(playerid) {
    return GetPVarInt(playerid, "TempVehicleID");
}

CALLBACK:HasPlayerTempVehicle(playerid) {
    return GetPlayerTempVehicleID(playerid) != 0;
}

CALLBACK:SetPlayerTempVehicleID(playerid, vehicleid) {
    return SetPVarInt(playerid, "TempVehicleID", vehicleid);
}

CALLBACK:DestroyPlayerTempVehicle(playerid) {
    new vehicleid = GetPlayerTempVehicleID(playerid);
    if(vehicleid > 0) {
        return DestroyVehicle(vehicleid);
    }
    return 0;
}

hook OnPlayerDisconnect(playerid) {
	DestroyPlayerTempVehicle(playerid);
	return 1;
}