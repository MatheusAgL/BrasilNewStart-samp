Player_SetBusyHand(playerid, Bodypart: bodypart, bool:stats)

stock HideNick(playerid)
{
	foreach(new i : Player)
	{
		ShowPlayerNameTagForPlayer(i, playerid, false);
	}
}

stock ShowNick(playerid)
{
 	foreach(new i : Player)
	{
		ShowPlayerNameTagForPlayer(i, playerid, true);
	}
}

stock UpdateAngleLixeira(playerid)
{
	new Float:angle, Float:pos[3];
	GetPlayerFacingAngle(playerid, angle);
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

    GetXYInFrontOfPlayer(playerid, pos[0], pos[1], 3.0);

    new idTrashCan = GetPVarInt(playerid, "playerTrashCanID");

    SetPlayerFacingAngle(playerid, angle + 20);

	InterpolateCameraPos(playerid, trashInfo[idTrashCan][trashPos][0], trashInfo[idTrashCan][trashPos][1], trashInfo[idTrashCan][trashPos][2] + 1.0,
	trashInfo[idTrashCan][trashPos][0], trashInfo[idTrashCan][trashPos][1], trashInfo[idTrashCan][trashPos][2] + 0.99, 10000, CAMERA_MOVE);

	InterpolateCameraLookAt(playerid, trashInfo[idTrashCan][trashPos][0], trashInfo[idTrashCan][trashPos][1], trashInfo[idTrashCan][trashPos][2] + 1.0,
	pos[0], pos[1], trashInfo[idTrashCan][trashPos][2], 1000, CAMERA_MOVE);
}

// new Text3D:lixo_Text [MAX_VEHICLES] = {Text3D:-1, ...};
// new lixo_Area        [MAX_VEHICLES] = {-1, ...};
// new lixo_Ammount     [MAX_VEHICLES] = {0, ...};

stock createCaminhaoLixo(vehicleid)
{
	lixo_Area[vehicleid] = CreateDynamicSphere(0.0, -4.0, 0.0, 4.0);
	lixo_Text[vehicleid] = CreateDynamic3DTextLabel("Capacidade: 0%", 0xFFFFFFF2, 0.0, 0.0, 0.0, 10.0, INVALID_PLAYER_ID, vehicleid);

	AttachDynamicAreaToVehicle(lixo_Area[vehicleid], vehicleid);

	new baseObject = CreateDynamicObject(19443, 0.02261, -3.95623, -0.41958,   0.00000, 90.00000, 0.00000);
	SetDynamicObjectMaterialText(baseObject, 0, " ");
	AttachDynamicObjectToVehicle(baseObject, vehicleid, 0.02261, -3.95623, -0.41958,   0.00000, 90.00000, 0.00000);
}

stock lixoAddCar(playerid, vehicleid)
{
	new string[45];

	lixo_Ammount[vehicleid] += GetPVarInt(playerid, "quantLixosPegou") * 2;

	if (lixo_Ammount[vehicleid] >= 100) lixo_Ammount[vehicleid] = 100;
	
	SetPVarInt(playerid, "quantLixosPegou", 0);

	format(string, sizeof string, "Capacidade: %dkg / 100kg", lixo_Ammount[vehicleid]);
	UpdateDynamic3DTextLabelText(lixo_Text[vehicleid], 0xFFFFFFF2, string);
}