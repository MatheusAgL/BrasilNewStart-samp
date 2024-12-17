stock createPlayerBody(playerid, lastbodypart) 
{
	if (lastbodypart > sizeof(_death_bodyparts_name)) return 0;

	if (gettime() < GetPVarInt(playerid, "timerBody")) return 0;
	SetPVarInt(playerid, "timerBody", gettime() + 70);

	if (GetPlayerBeingAbducted(playerid)) return 0;

#if _inc_paintball_system
	if (Player_GetPaintball(playerid) != INVALID_PAINTBALL_ID) 
		return 0;
#endif
	
	static Float:x, Float:y, Float:z, Float:ang, id, Text3D:textLabel;
	
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);
	
	id = CreateActor(GetPlayerSkin(playerid), x, y, z, ang);
	SetActorInvulnerable(id, false);
	SetActorHealth(id, 0.0);

	if (GetPVarInt(playerid, "InHeadShot") == 0)
		SetActorVirtualWorld(id, GetPlayerVirtualWorld(playerid));
	else
		SetActorVirtualWorld(id, GetPlayerActualWorld(playerid));
	
	// Text 3d
	new string_body[85];
	format(string_body, sizeof string_body, "Corpo de %s\n\nA causa da morte foi: %s", PlayerName[playerid], _death_bodyparts_name[lastbodypart]);
	
	textLabel = CreateDynamic3DTextLabel(string_body, 0xFFFFFFBB, x, y, z, 5.0);
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, textLabel, E_STREAMER_WORLD_ID, GetPlayerVirtualWorld(playerid));
	
	// Tempo para desaparecer
	SetTimerEx("destroyPlayerBody", 60000, false, "dd", id, _:textLabel);
	
	return 1;
}

CALLBACK: destroyPlayerBody(id, Text3D:textLabel) {

	DestroyActor( id );
	DestroyDynamic3DTextLabel( textLabel );
}

hook OnPlayerDeathFinished(playerid)
{
    createPlayerBody(playerid, DanoInfo[playerid][danoBodypart]);

	return 1;
}

