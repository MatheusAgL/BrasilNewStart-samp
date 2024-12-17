// =======================================================================================
// fly.inc
//
// Author: Norck
//
// msn:		paul_norck@hotmail.com
// icq:		44-055-21
// skype:	paul_norck
//
// Credits: Creator of SetPlayerLookAt function. Sorry, I can't remember their name
//
// you are allowed to edit this script
// you are not allowed to sell this script
//
// Please, don't remove the credits
// =======================================================================================

// variables
static bool:OnFly[MAX_PLAYERS];		// true = player is flying, false = player on foot

// callbacks // functions

stock InitFly(playerid)
{
	OnFly[playerid] = false;
	return;
}

stock bool:StartFly(playerid)
{
	if (OnFly[playerid])
        return false;

    OnFly[playerid] = true;

	new Float:x,
		Float:y,
		Float:z;

	GetPlayerPos(playerid, x, y, z);
	SetPlayerPos(playerid, x, y, z + 5.0);

	ApplyAnimation(playerid, "PARACHUTE", "PARA_steerR", 6.1, true, true, true, true, 0, SYNC_ALL);
	Fly(playerid);

	GameTextForPlayer(playerid,"~y~MODO VOAR~n~~r~~k~~PED_FIREWEAPON~ ~w~- AUMENTA ALTURA~n~~r~RMB ~w~- REDUZ ALTURA~n~\
	~r~~k~~PED_SPRINT~ ~w~- AUMENTAR SPEED~n~\
	~r~~k~~SNEAK_ABOUT~ ~w~- REDUZ SPEED", 10000, 3);

	return true;
}

CALLBACK: Fly(playerid)
{
	if (!IsPlayerConnected(playerid))
		return 1;

	new k, ud, lr;
	GetPlayerKeys(playerid, k, ud, lr);

	new Float:v_x,
		Float:v_y,
		Float:v_z,
		Float:x,
		Float:y,
		Float:z;
		
	if (ud < 0)					// FORWARD
	{
		GetPlayerCameraFrontVector(playerid,x,y,z);
		v_x = x + 0.1;
		v_y = y + 0.1;
	}
	if (k & KEY_HANDBRAKE)		// DOWN
		v_z = -0.2;
	else if (k & KEY_FIRE)		// UP
		v_z = 0.2;
	if (k & KEY_WALK)			// SLOW
	{
		v_x /= 5.0;
		v_y /= 5.0;
		v_z /= 5.0;
	}
	if (k & KEY_SPRINT)			// FAST
	{
		v_x *= 4.0;
		v_y *= 4.0;
		v_z *= 4.0;
	}
	if (v_z == 0.0)
		v_z = 0.025;

	SetPlayerVelocity(playerid, v_x, v_y, v_z);

	if (v_x == 0 && v_y == 0) {
		if (GetPlayerAnimationIndex(playerid) == 959)
			ApplyAnimation(playerid, "PARACHUTE", "PARA_steerR", 6.1, true, true, true, true, 0, SYNC_ALL);
	} else {
		GetPlayerCameraFrontVector(playerid, v_x, v_y, v_z);
		GetPlayerCameraPos(playerid, x, y, z);
		SetPlayerLookAt(playerid, v_x * 500.0 + x, v_y * 500.0 + y);

		if (GetPlayerAnimationIndex(playerid) != 959)
			ApplyAnimation(playerid,"PARACHUTE","FALL_SkyDive_Accel", 6.1, true, true, true, true, 0, SYNC_ALL);
	}
	if (OnFly[playerid])
		SetTimerEx("Fly", 100, false, "i", playerid);

	return 1;
}

stock bool:StopFly(playerid)
{
	if(!OnFly[playerid])
        return false;
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid,x,y,z);
	SetPlayerPos(playerid,x,y,z);
	OnFly[playerid] = false;
	return true;
}

static SetPlayerLookAt(playerid,Float:x,Float:y)
{
	new 
		Float:Px, 
		Float:Py, 
		Float: Pa;
		
	GetPlayerPos(playerid, Px, Py, Pa);
	Pa = floatabs(atan((y - Py) / (x - Px)));

	if (x <= Px && y >= Py)
		Pa = floatsub(180.0, Pa);
	else if (x < Px && y < Py) 
		Pa = floatadd(Pa, 180.0);
	else if (x >= Px && y <= Py)
		Pa = floatsub(360.0, Pa);
		
	Pa = floatsub(Pa, 90.0);

	if (Pa >= 360.0)
		Pa = floatsub(Pa, 360.0);

	SetPlayerFacingAngle(playerid, Pa);
	return;
}

CMD:fly(playerid)
{
	if (Admin_GetNivel(playerid) < MODERADOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!Staff_GetWorking(playerid) && Admin_GetNivel(playerid) < DONO)
		return SendClientMessage(playerid, COLOR_LIGHTGREEN, "Você não está em modo trabalho.");

	if (!OnFly[playerid]) {
		StartFly(playerid);
		SendClientMessage(playerid, COLOR_DEV, "Você ativou o modo FLY.");
	} else {
		StopFly(playerid);
		SendClientMessage(playerid, COLOR_DEV, "Você desativou o modo FLY.");
	}
	return 1;
}