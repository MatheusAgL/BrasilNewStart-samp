
CMD:abastecer(playerid, params[])
{
	new vehicle_id = GetPlayerVehicleID(playerid);

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER || !IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, -1, "Você não é o motorista do veículo ou não está em um veículo.");

	if (!IsAtGasStation(playerid)) return SendClientMessage(playerid, -1, "Você não está em um posto de combustivel.");

	if (VehicleInfo[vehicle_id][vehicleCombustivel] >= 100) return SendClientMessage(playerid, -1, "O tanque já está cheio.");

	GameTextForPlayer(playerid, " ~w~Abastecendo o tanque... ", 3003, 3);
	SetTimerEx("Fillup", 5000, false, "i", playerid);
	TogglePlayerControllable(playerid, false);
	Refueling[playerid] = 1;
	SendClientMessage(playerid, -1, " Você está reabastecendo este veículo, Aguarde...");

	return true;
}