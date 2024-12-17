/*  ----------------------------------------------------------------------------------------------------------------------------------------

        Sistema de velocimetro
                            v0.63
                            Theus_Crazzy (wearLyS)

 ----------------------------------------------------------------------------------------------------------------------------------------- */

#define _INC_velocity

#if !defined _INC_velocity
	#endinput
#endif

#define _INC_velocity_version (1)

#include < YSI_Coding\y_hooks >

// -----------------------------------------------------------------

// (Player Textdraws velocimetro)
static	
		Timer:velocity_Timer[MAX_PLAYERS];

static UpdatePlayerVelocimetro(playerid, vehicleid)
{
	static string_velo[25]; 
	static Float:healthVehicle;

	GetVehicleHealth(vehicleid, healthVehicle);

	format(string_velo, sizeof (string_velo), "%02d", floatround(GetVehicleSpeed(vehicleid)));
	PlayerTextDrawSetString(playerid, playerTextSpeedometer[1][playerid], string_velo);

	format(string_velo, sizeof (string_velo), "%.0f%", healthVehicle / 10.0);
	PlayerTextDrawSetString(playerid, playerTextSpeedometer[4][playerid], string_velo);

}

stock UpdateSpeedometerFuel(playerid, fuel) {
	new Float:decFuel = fuel / 100.0,
		color = 0xFFFFFFD8;

	if(fuel < 11) {
		color = 0x801818D8;
	}

	new Float:sumPosX = IsPCPlayer(playerid) ? 92.000 : -10.0000;

	PlayerTextDrawTextSize(playerid, playerTextSpeedometer[2][playerid], 418.500000 + sumPosX + 50.00000*decFuel, 29.500000);
	PlayerTextDrawBoxColor(playerid, playerTextSpeedometer[2][playerid], color);
	PlayerTextDrawShow(playerid, playerTextSpeedometer[2][playerid]);
}

// Timer de atualização do velocimetro
timer velocimetroTimer[500](playerid)
{
    new vehicleid;

    if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if ((vehicleid = GetPlayerVehicleID(playerid)) != INVALID_VEHICLE_ID)
		{
			new VIM:vim = Vehicle_GetVIM(vehicleid);

		    if (!Vehicle_IsCaminhao(playerid) && !VIM_IsManual(vim) && !IsALixeiroCar(vehicleid) && IsVehicleEngineStarted(vehicleid))
				VehicleInfo[vehicleid][vehicleCombUpdate]++;
			
		   	if (VehicleInfo[vehicleid][vehicleCombUpdate] > 100)
		   	{
		   	    VehicleInfo[vehicleid][vehicleCombUpdate] = 0;
		   	
				if (VehicleInfo[vehicleid][vehicleCombustivel] < 2)
				{
					StopVehicleEngine(vehicleid);

					SendClientMessage(playerid, -1, "O motor do veículo falhou por falta de combustível...");
					SendClientMessage(playerid, -1, "Você pode ir no posto mais próximo e comprar galão, ou usar: /servico mecanico.");
				
					PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				}
				else if (VehicleInfo[vehicleid][vehicleCombustivel] < 11)
				{
					PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			  	}

				if(VehicleInfo[vehicleid][vehicleCombustivel] > 0) {
					VehicleInfo[vehicleid][vehicleCombustivel]--;
					UpdateSpeedometerFuel(playerid, VehicleInfo[vehicleid][vehicleCombustivel]);
				}
			}

			UpdatePlayerVelocimetro(playerid, vehicleid);
		}
	}
	else if (GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
	{
	    if ((vehicleid = GetPlayerVehicleID(playerid)) != INVALID_VEHICLE_ID)
		{
	    	UpdatePlayerVelocimetro(playerid, vehicleid);

			if (VehicleInfo[vehicleid][vehicleCombUpdate] == 0) {
				UpdateSpeedometerFuel(playerid, VehicleInfo[vehicleid][vehicleCombustivel]);
			}
 		}
	}
	else stop velocity_Timer[playerid];
	
	return true;
}

// Caso o jogador entre em um veículo ou saia
hook OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		if (!Player_Logado(playerid)) return 1;

		stop velocity_Timer[playerid];
	    velocity_Timer[playerid] = repeat velocimetroTimer(playerid);

	    ShowPlayerVelocimetro(playerid);
	} else  {
		if (!Player_Logado(playerid)) return 1;

		HidePlayerVelocimetro(playerid);
	}
	return 1;
}

// Mostra o velocimetro
stock ShowPlayerVelocimetro(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid), color[2], string_velo[30];
	GetVehicleColor(vehicleid, color[0], color[1]);

	new vehicle_name[30];
	GetModelStaticNameFromId(GetVehicleModel(vehicleid), vehicle_name);

	format(string_velo, sizeof(string_velo), "%s", vehicle_name);
	PlayerTextDrawSetString(playerid, playerTextSpeedometer[0][playerid], string_velo);

	PlayerTextDrawSetPreviewModel(playerid, playerTextSpeedometer[3][playerid], GetVehicleModel(vehicleid));
	PlayerTextDrawSetPreviewVehCol(playerid, playerTextSpeedometer[3][playerid], color[0], color[1]);

	UpdateSpeedometerFuel(playerid, VehicleInfo[vehicleid][vehicleCombustivel]);

	new speedoId = IsAndroidPlayer(playerid) ? 1 : 0;
	for(new text; text != 6; text++) {
		TextDrawShowForPlayer(playerid, textSpeedometer[speedoId][text]);
	}

	for(new text; text != 5; text++) {
		PlayerTextDrawShow(playerid, playerTextSpeedometer[text][playerid]);
	}
	return 1;
}

// Oculta o velocimetro
stock HidePlayerVelocimetro(playerid)
{
	new speedoId = IsAndroidPlayer(playerid) ? 1 : 0;

	for(new text; text != 6; text++) {
		TextDrawHideForPlayer(playerid, textSpeedometer[speedoId][text]);
	}

	for(new text; text != 5; text++) {
		PlayerTextDrawHide(playerid, playerTextSpeedometer[text][playerid]);
	}
	return 1;
}

// Cria ao iniciar o servidor (textdraws fixa);
hook OnGameModeInit()
{
	CreateVelocity();
 	return 1;
}

// Quando o jogador desconecta;
hook OnPlayerDisconnect(playerid, reason) 
{
	stop velocity_Timer[playerid];
	return 1;
}