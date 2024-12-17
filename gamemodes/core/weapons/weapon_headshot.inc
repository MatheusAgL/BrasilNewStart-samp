#include < YSI_Coding\y_hooks >

// Sistema de HeadShot com câmera (apenas Sniper)

#define 		CAMERA_MOVE_TIME 			2500

timer t_CameraEnd[350](playerid)
{
    CheckConquista(playerid, Conquista_HeadShot);

    SetPlayerArmedWeapon(playerid, WEAPON_SNIPER);
    TogglePlayerControllable(playerid, true);
    SetCameraBehindPlayer(playerid);

	SetPlayerVirtualWorld(playerid, GetPlayerActualWorld(playerid));
}

timer t_Spark[150](playerid, targetid, objectid)
{
	DestroyObject(objectid);
	DamagePlayer(targetid, 200.0, playerid, WEAPON_SNIPER, 9);
}

timer t_SparkCreate[CAMERA_MOVE_TIME](Float:X, Float:Y, Float:Z, objectid, playerid, targetid)
{
    DestroyObject(objectid);

	defer t_CameraEnd(playerid);
	defer t_Spark(playerid, targetid, CreateObject(18668, X, Y, Z - 1.6, 0.0, 0.0, 0.0));

	SoundInRange(32402, 30.0, X, Y, Z);
	PlayerPlaySound(playerid, 32402, 0.0, 0.0, 0.0);
	PlayerPlaySound(targetid, 32402, 0.0, 0.0, 0.0);
}

stock InitHeadShot(playerid, targetid)
{
	if (GetPlayerInterior(playerid) != 0 || GetPlayerInterior(targetid) != 0) return true;

	// Setar arma 0 na mão
	SetPlayerArmedWeapon(playerid, WEAPON_FIST);
	SetPlayerArmedWeapon(targetid, WEAPON_FIST);

	// Salva a world atual do jogador
	SetPlayerActualWorld(playerid, GetPlayerVirtualWorld(playerid));
	SetPlayerActualWorld(targetid, GetPlayerVirtualWorld(targetid));

	// Seta para uma world diferente
  	SetPlayerVirtualWorld(targetid, 24);
   	SetPlayerVirtualWorld(playerid, 24);

	// Variáveis
	new Float:fOPos[3],
		Float:fHPos[3],
		Float:Angle,
		Float:Speedd, objectid, time;

	// Pegando angulo do tiro
    GetPlayerFacingAngle(playerid, Angle);

	// Congelando ambos players
	TogglePlayerControllable(playerid, false);
	TogglePlayerControllable(targetid, false);
	
	// Pegando posição e angulo de frente do atirador
    GetPlayerPos(playerid, fOPos[0], fOPos[1], fOPos[2]);
    GetXYInFrontOfPlayer(playerid, fOPos[0], fOPos[1], 1.0);

	// Posição da camera da vitima sendo setada na posição do atirador
	SetPlayerCameraPos(targetid, fOPos[0], fOPos[1], fOPos[2]);

	// Pegando a posição da vitima e setando onde a camera irá travar 
	GetPlayerPos(targetid, fHPos[0], fHPos[1], fHPos[2]);

	fHPos[2] += 0.8;
	SetPlayerCameraLookAt(targetid, fHPos[0], fHPos[1], fHPos[2]);

	// Velocidade do objeto até o jogador
	Speedd = VectorSize(fOPos[0]-fHPos[0], fOPos[1]-fHPos[1], fOPos[2]-fHPos[2]) / (CAMERA_MOVE_TIME / 1000);

	// Objeto
	objectid = CreateObject(1636, fOPos[0], fOPos[1], fOPos[2], 0.0, 0.0, Angle);
	//SetObjectFacePoint(objectid, fHPos[0], fHPos[1]);
  	MoveObject(objectid, fHPos[0], fHPos[1], fHPos[2], Speedd);

	// Criando os timers
	defer t_SparkCreate(fHPos[0], fHPos[1], fHPos[2], objectid, playerid, targetid);

	fHPos[0] -= (1 * floatsin(-Angle, degrees));
	fHPos[1] -= (1 * floatcos(-Angle, degrees));
	fOPos[0] += (1 * floatsin(-Angle, degrees));
	fOPos[1] += (1 * floatcos(-Angle, degrees));

	// Tempo para finalizar animação
	time = CAMERA_MOVE_TIME + floatround(CAMERA_MOVE_TIME * 0.15, floatround_round);

	InterpolateCameraPos(playerid, fOPos[0], fOPos[1], fOPos[2], fHPos[0], fHPos[1], fHPos[2], time, CAMERA_MOVE);
    InterpolateCameraPos(targetid, fOPos[0], fOPos[1], fOPos[2], fHPos[0], fHPos[1], fHPos[2], time, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, fOPos[0], fOPos[1], fOPos[2], fHPos[0], fHPos[1], fHPos[2], 1000, CAMERA_MOVE);
    InterpolateCameraLookAt(targetid, fOPos[0], fOPos[1], fOPos[2], fHPos[0], fHPos[1], fHPos[2], 1000, CAMERA_MOVE);

	SetPlayerChatBubble(playerid, "[HEAD SHOT CAMERA]", 0xF12C2CFF, 50.0, CAMERA_MOVE_TIME);
    SetPlayerChatBubble(targetid, "[HEAD SHOT CAMERA]", 0xF12C2CFF, 50.0, CAMERA_MOVE_TIME);

	SetPVarInt(playerid, "InHeadShot", 1);
	SetPVarInt(targetid, "InHeadShot", 1);

	PlayerTextDrawHide(playerid, SniperShot[playerid]);

	return 1;
}

stock SetObjectFacePoint(objectid, Float: X, Float: Y) // By Lorenc_ | http://forum.sa-mp.com/showpost.php?p=1456045&postcount=2563
{
    static
        Float: pX,      Float: oX,
        Float: pY,      Float: oY,
        Float: oZ
    ;
    GetObjectRot(objectid, oX, oY, oZ);
    GetObjectRot(objectid, pX, pY, oZ);

    oZ = ( floatadd(atan2(floatsub(Y, pY), floatsub(X, pX)), 270.0) );

    SetObjectRot(objectid, oX, oY, oZ);
}
