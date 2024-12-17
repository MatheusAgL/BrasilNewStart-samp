/**--------------------------------------------------------------------------**\
 ______ ______  ______     __  ______  ______  ______     ______  __  ______ __  __
/\  == /\  == \/\  __ \   /\ \/\  ___\/\  ___\/\__  _\   /\  ___\/\ \/\__  _/\ \_\ \
\ \  _-\ \  __<\ \ \/\ \ _\_\ \ \  __\\ \ \___\/_/\ \/   \ \ \___\ \ \/_/\ \\ \____ \
 \ \_\  \ \_\ \_\ \_____/\_____\ \_____\ \_____\ \ \_\    \ \_____\ \_\ \ \_\\/\_____\
  \/_/   \/_/ /_/\/_____\/_____/\/_____/\/_____/  \/_/     \/_____/\/_/  \/_/ \/_____/

						 ==========================
		                    Brasil Play Start
                              ® 2013 - 2017
                             Módulo: Radar
						 ==========================

\**--------------------------------------------------------------------------**/
#define 		MAX_RADARS 			8


enum RadarsEnum
{
	Float:rPos[3],
	Float:rRot,
	Float:rRange,
	rSpeedLimit,
	rArea,
	rObject,
};

new RadarInfo[MAX_RADARS][RadarsEnum] =
{
	{{561.525510, -1727.22168, 11.97362}, 079.00000, 15.0, 90, -1},
	{{1558.36597, -1724.72412, 12.53827}, 267.19882, 13.0, 90, -1},
	{{1838.92517, -1494.12268, 12.53738}, 000.00000, 18.0, 90, -1},
	{{1283.69299, -1844.82593, 12.54428}, 270.74612, 13.0, 90, -1},
	{{2882.05957, -1443.58167, 09.95030}, 178.12360, 12.0, 90, -1},
	{{997.736150, -1133.88562, 22.81804}, 269.40909, 21.0, 90, -1},
	{{-144.26364, -1391.12976, 01.78813}, 183.20825, 14.0, 90, -1},
	{{561.525510, -1727.22168, 11.97362}, 259.00000, 13.0, 90, -1}
};

forward onPlayerFined(playerid, radarid, vehicleid, maxspeed, playerspeed);

stock createRadars()
{
	new string_radar[75];

	for (new radar; radar < MAX_RADARS; radar++)
	{
	    new speedlimit = RadarInfo[radar][rSpeedLimit];

	    format(string_radar, sizeof (string_radar), "RADAR\nVelocidade máxima: %d", speedlimit);
	    CreateDynamic3DTextLabel(string_radar, 0xFFAA00FF, RadarInfo[radar][rPos][0], RadarInfo[radar][rPos][1], RadarInfo[radar][rPos][2] + 6.3, 55.0);
	    RadarInfo[radar][rObject] = CreateDynamicObject(18880, RadarInfo[radar][rPos][0], RadarInfo[radar][rPos][1], RadarInfo[radar][rPos][2], 0.0, 0.0, RadarInfo[radar][rRot]);

		new Float:a = (RadarInfo[radar][rRot] - 90.0), Float:minPos[2], Float:maxPos[2];

        minPos[0] = RadarInfo[radar][rPos][0];
		minPos[1] = RadarInfo[radar][rPos][1];
		maxPos[0] = RadarInfo[radar][rPos][0] + (RadarInfo[radar][rRange] * floatsin(-a, degrees)) + (20 * floatsin(-(a + 90.0), degrees));
		maxPos[1] = RadarInfo[radar][rPos][1] + (RadarInfo[radar][rRange] * floatcos(-a, degrees)) + (20 * floatcos(-(a + 90.0), degrees));

	    RadarInfo[radar][rArea] = CreateDynamicRectangle(minPos[0], minPos[1], maxPos[0], maxPos[1]);
	}
}


public OnPlayerEnterDynamicArea(playerid, areaid)
{
    if (IsPlayerNPC(playerid)) return 0;

	for (new radar; radar < MAX_RADARS; radar++)
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && RadarInfo[radar][rArea] == areaid)
		{
		    new Float:speedPlayer = GetVehicleSpeed(GetPlayerVehicleID(playerid));

		    if (speedPlayer > RadarInfo[radar][rSpeedLimit])
		    {
          		new Float:Pos[3];
		        GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
		        if(floatabs(Pos[2] - RadarInfo[radar][rPos][2]) <= 2.0)
					CallLocalFunction("onPlayerFined", "iiiii", playerid, radar, GetPlayerVehicleID(playerid), RadarInfo[radar][rSpeedLimit], speedPlayer);
			}
			break;
		}
	}

	#if defined rdOnPlayerEnterDynamicArea
	    return rdOnPlayerEnterDynamicArea(playerid, areaid);
	#else
	    return 1;
	#endif
}

#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea rdOnPlayerEnterDynamicArea
#if defined rdOnPlayerEnterDynamicArea
	forward rdOnPlayerEnterDynamicArea(playerid, areaid);
#endif

public onPlayerFined(playerid, radarid, vehicleid, maxspeed, playerspeed)
{
	new VIM:vim = Vehicle_GetVIM(vehicleid);
	if (OnDuty[playerid] || IsPlayerNPC(playerid) || VIM_IsManual(vim))
		return false;

	SendClientMessage(playerid, 0xFF5500FF, "* Você foi multado por passar no radar acima da velocidade permitida.");
	SendClientMessage(playerid, 0xFF5500FF, "* Descrição: {888888}EXCESSO DE VELOCIDADE {FF5500}Valor da multa: {00AA00}$1200");

	// if(!IsPlayerInDrone(playerid))
	// 	registerVehiclePlateInfo(vehicleid, "multas", "EXCESSO DE VELOCIDADE", "RADAR", 1200);
	// else {
	SendClientMessage(playerid, 0xFF5500FF, "* O valor foi descontado automaticamente.");
	Player_RemoveMoney(playerid, 1200);
	// }

	adicionarDinheiroGoverno(1200);


	PlayerPlaySound(playerid, 1132, 0.0, 0.0, 0.0);
	SoundInRange(1132, 50.0, RadarInfo[radarid][rPos][0], RadarInfo[radarid][rPos][1], RadarInfo[radarid][rPos][2]);

	return true;
}

