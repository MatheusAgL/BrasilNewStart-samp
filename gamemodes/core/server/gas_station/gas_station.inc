
CMD:abastecer(playerid, params[])
{
	new vehicle_id = GetPlayerVehicleID(playerid);

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER || !IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, -1, "Voc� n�o � o motorista do ve�culo ou n�o est� em um ve�culo.");

	if (!IsAtGasStation(playerid)) return SendClientMessage(playerid, -1, "Voc� n�o est� em um posto de combustivel.");

	if (VehicleInfo[vehicle_id][vehicleCombustivel] >= 100) return SendClientMessage(playerid, -1, "O tanque j� est� cheio.");

	GameTextForPlayer(playerid, " ~w~Abastecendo o tanque... ", 3003, 3);
	SetTimerEx("Fillup", 5000, false, "i", playerid);
	TogglePlayerControllable(playerid, false);
	Refueling[playerid] = 1;
	SendClientMessage(playerid, -1, " Voc� est� reabastecendo este ve�culo, Aguarde...");

	return true;
}