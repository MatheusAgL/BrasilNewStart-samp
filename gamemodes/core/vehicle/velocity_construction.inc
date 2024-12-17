
/*  ----------------------------------------------------------------------------------------------------------------------------------------

        Sistema de velocimetro com ponteiro
                            v0.1
                            Theus_Crazzy (wearLyS)

 ----------------------------------------------------------------------------------------------------------------------------------------- */

#include    < YSI_Coding\y_hooks >

// (Global Textdraws velocimetro)
static Text:textVelocimetro[32];

// (Player Textdraws velocimetro)
static PlayerText:textPlayerVelocimetro[18][MAX_PLAYERS];

new Timer:velocity_Timer[MAX_PLAYERS];

stock UpdatePlayerVelocimetro(playerid, vehicleid)
{
	static string_velo[25]; 

	format(string_velo, sizeof (string_velo), "%.0f", GetVehicleSpeed(vehicleid));
	PlayerTextDrawSetString(playerid, textPlayerVelocimetro[0][playerid], string_velo);

	if (GetVehicleSpeed(vehicleid) > 0)
		UpdatePonteiro(playerid, GetVehicleSpeed(vehicleid));
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		if (!Player_Logado(playerid)) return 1;

		stop velocity_Timer[playerid];
	    velocity_Timer[playerid] = repeat velocimetroTimer[500](playerid);
	
	    ShowPlayerVelocimetro(playerid);
	}
	else 
	{
		if (!Player_Logado(playerid)) return 1;

		HidePlayerVelocimetro(playerid);
	}
	return 1;
}

stock ShowPlayerVelocimetro(playerid)
{
	for(new text; text != sizeof(textVelocimetro); text++) 
		TextDrawShowForPlayer(playerid, textVelocimetro[text]);

	for(new text; text != sizeof(textPlayerVelocimetro); text++) 
		PlayerTextDrawShow(playerid, textPlayerVelocimetro[text][playerid]);

	return 1;
}

stock HidePlayerVelocimetro(playerid)
{
	for(new text; text != sizeof(textVelocimetro); text++) 
		TextDrawHideForPlayer(playerid, textVelocimetro[text]);
	for(new text; text != sizeof(textPlayerVelocimetro); text++) 
		PlayerTextDrawHide(playerid, textPlayerVelocimetro[text][playerid]);

	return 1;
}

timer velocimetroTimer[500](playerid)
{
    new vehicleid;

    if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if ((vehicleid = GetPlayerVehicleID(playerid)) != INVALID_VEHICLE_ID)
		{
		    new VIM:vim = Vehicle_GetVIM(vehicleid);

		    if (!PlayerCaminhao[playerid][caminhaoValid] && !VIM_IsManual(vim) && !IsALixeiroCar(vehicleid) && IsVehicleEngineStarted(vehicleid))
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

				if(VehicleInfo[vehicleid][vehicleCombustivel] > 0)
					VehicleInfo[vehicleid][vehicleCombustivel]--;
			}
			UpdatePlayerVelocimetro(playerid, vehicleid);
		}
	}
	else if (GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
	{
	    if ((vehicleid = GetPlayerVehicleID(playerid)) != INVALID_VEHICLE_ID)
		{
	    	UpdatePlayerVelocimetro(playerid, vehicleid);
 		}
	}
	else stop velocity_Timer[playerid];
	
	return true;
}

hook OnPlayerConnect(playerid) 
{
	

	return 1;
}

hook OnGameModeInit()
{
	textVelocimetro[0] = TextDrawCreate(394.666564, 348.248138, "LD_POOL:ball");
	TextDrawTextSize(textVelocimetro[0], 83.000000, 92.000000);
	TextDrawAlignment(textVelocimetro[0], TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(textVelocimetro[0], 128);
	TextDrawSetShadow(textVelocimetro[0], 0);
	TextDrawBackgroundColor(textVelocimetro[0], 255);
	TextDrawFont(textVelocimetro[0], TEXT_DRAW_FONT_SPRITE_DRAW);
	TextDrawSetProportional(textVelocimetro[0], false);

	textVelocimetro[1] = TextDrawCreate(408.498321, 387.165252, "/");
	TextDrawLetterSize(textVelocimetro[1], 0.339664, -0.116888);
	TextDrawAlignment(textVelocimetro[1], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[1], -1);
	TextDrawSetShadow(textVelocimetro[1], 0);
	TextDrawBackgroundColor(textVelocimetro[1], 255);
	TextDrawFont(textVelocimetro[1], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[1], true);

	textVelocimetro[2] = TextDrawCreate(432.166687, 389.470581, "LD_DUAL:light");
	TextDrawTextSize(textVelocimetro[2], 8.000000, 9.039999);
	TextDrawAlignment(textVelocimetro[2], TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(textVelocimetro[2], 128);
	TextDrawSetShadow(textVelocimetro[2], 0);
	TextDrawBackgroundColor(textVelocimetro[2], 255);
	TextDrawFont(textVelocimetro[2], TEXT_DRAW_FONT_SPRITE_DRAW);
	TextDrawSetProportional(textVelocimetro[2], false);

	textVelocimetro[3] = TextDrawCreate(417.432189, 418.367156, "/");
	TextDrawLetterSize(textVelocimetro[3], 0.213331, 0.405777);
	TextDrawAlignment(textVelocimetro[3], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[3], -1);
	TextDrawSetShadow(textVelocimetro[3], 0);
	TextDrawBackgroundColor(textVelocimetro[3], 255);
	TextDrawFont(textVelocimetro[3], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[3], true);

	textVelocimetro[4] = TextDrawCreate(413.831970, 421.767364, "0");
	TextDrawLetterSize(textVelocimetro[4], 0.159333, 0.826222);
	TextDrawAlignment(textVelocimetro[4], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[4], -1);
	TextDrawSetShadow(textVelocimetro[4], 0);
	TextDrawBackgroundColor(textVelocimetro[4], 255);
	TextDrawFont(textVelocimetro[4], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[4], true);

	textVelocimetro[5] = TextDrawCreate(413.365295, 413.681671, "/");
	TextDrawLetterSize(textVelocimetro[5], 0.289332, 0.264741);
	TextDrawAlignment(textVelocimetro[5], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[5], -1);
	TextDrawSetShadow(textVelocimetro[5], 0);
	TextDrawBackgroundColor(textVelocimetro[5], 255);
	TextDrawFont(textVelocimetro[5], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[5], true);

	textVelocimetro[6] = TextDrawCreate(405.298126, 406.966461, "20");
	TextDrawLetterSize(textVelocimetro[6], 0.159333, 0.826222);
	TextDrawAlignment(textVelocimetro[6], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[6], -1);
	TextDrawSetShadow(textVelocimetro[6], 0);
	TextDrawBackgroundColor(textVelocimetro[6], 255);
	TextDrawFont(textVelocimetro[6], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[6], true);

	textVelocimetro[7] = TextDrawCreate(411.598510, 407.866516, "/");
	TextDrawLetterSize(textVelocimetro[7], 0.315665, 0.194222);
	TextDrawAlignment(textVelocimetro[7], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[7], -1);
	TextDrawSetShadow(textVelocimetro[7], 0);
	TextDrawBackgroundColor(textVelocimetro[7], 255);
	TextDrawFont(textVelocimetro[7], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[7], true);

	textVelocimetro[8] = TextDrawCreate(401.797912, 390.165435, "40");
	TextDrawLetterSize(textVelocimetro[8], 0.159333, 0.826222);
	TextDrawAlignment(textVelocimetro[8], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[8], -1);
	TextDrawSetShadow(textVelocimetro[8], 0);
	TextDrawBackgroundColor(textVelocimetro[8], 255);
	TextDrawFont(textVelocimetro[8], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[8], true);

	textVelocimetro[9] = TextDrawCreate(409.398376, 400.966094, "/");
	TextDrawLetterSize(textVelocimetro[9], 0.334665, 0.136147);
	TextDrawAlignment(textVelocimetro[9], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[9], -1);
	TextDrawSetShadow(textVelocimetro[9], 0);
	TextDrawBackgroundColor(textVelocimetro[9], 255);
	TextDrawFont(textVelocimetro[9], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[9], true);

	textVelocimetro[10] = TextDrawCreate(408.398315, 391.265502, "-");
	TextDrawLetterSize(textVelocimetro[10], 0.271333, 0.517553);
	TextDrawAlignment(textVelocimetro[10], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[10], -1);
	TextDrawSetShadow(textVelocimetro[10], 0);
	TextDrawBackgroundColor(textVelocimetro[10], 255);
	TextDrawFont(textVelocimetro[10], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[10], true);

	textVelocimetro[11] = TextDrawCreate(404.664764, 371.864318, "60");
	TextDrawLetterSize(textVelocimetro[11], 0.159333, 0.826222);
	TextDrawAlignment(textVelocimetro[11], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[11], -1);
	TextDrawSetShadow(textVelocimetro[11], 0);
	TextDrawBackgroundColor(textVelocimetro[11], 255);
	TextDrawFont(textVelocimetro[11], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[11], true);

	textVelocimetro[12] = TextDrawCreate(417.865112, 357.019653, "80");
	TextDrawLetterSize(textVelocimetro[12], 0.169332, 0.806222);
	TextDrawAlignment(textVelocimetro[12], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[12], -1);
	TextDrawSetShadow(textVelocimetro[12], 0);
	TextDrawBackgroundColor(textVelocimetro[12], 255);
	TextDrawFont(textVelocimetro[12], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[12], true);

	textVelocimetro[13] = TextDrawCreate(433.999938, 359.378356, "I");
	TextDrawLetterSize(textVelocimetro[13], 0.110999, 0.629777);
	TextDrawAlignment(textVelocimetro[13], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[13], -1);
	TextDrawSetShadow(textVelocimetro[13], 0);
	TextDrawBackgroundColor(textVelocimetro[13], 255);
	TextDrawFont(textVelocimetro[13], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[13], true);

	textVelocimetro[14] = TextDrawCreate(441.965148, 360.700073, "/");
	TextDrawLetterSize(textVelocimetro[14], 0.084665, 0.422369);
	TextDrawAlignment(textVelocimetro[14], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[14], -1);
	TextDrawSetShadow(textVelocimetro[14], 0);
	TextDrawBackgroundColor(textVelocimetro[14], 255);
	TextDrawFont(textVelocimetro[14], TEXT_DRAW_FONT_3);
	TextDrawSetProportional(textVelocimetro[14], true);

	textVelocimetro[15] = TextDrawCreate(451.767181, 354.919525, "120");
	TextDrawLetterSize(textVelocimetro[15], 0.169332, 0.806222);
	TextDrawAlignment(textVelocimetro[15], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[15], -1);
	TextDrawSetShadow(textVelocimetro[15], 0);
	TextDrawBackgroundColor(textVelocimetro[15], 255);
	TextDrawFont(textVelocimetro[15], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[15], true);

	textVelocimetro[16] = TextDrawCreate(449.431976, 364.618621, "/");
	TextDrawLetterSize(textVelocimetro[16], 0.125664, 0.277184);
	TextDrawAlignment(textVelocimetro[16], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[16], -1);
	TextDrawSetShadow(textVelocimetro[16], 0);
	TextDrawBackgroundColor(textVelocimetro[16], 255);
	TextDrawFont(textVelocimetro[16], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[16], true);

	textVelocimetro[17] = TextDrawCreate(455.932373, 369.218902, "/");
	TextDrawLetterSize(textVelocimetro[17], 0.202997, 0.285481);
	TextDrawAlignment(textVelocimetro[17], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[17], -1);
	TextDrawSetShadow(textVelocimetro[17], 0);
	TextDrawBackgroundColor(textVelocimetro[17], 255);
	TextDrawFont(textVelocimetro[17], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[17], true);

	textVelocimetro[18] = TextDrawCreate(459.632598, 376.419342, "/");
	TextDrawLetterSize(textVelocimetro[18], 0.271665, 0.194222);
	TextDrawAlignment(textVelocimetro[18], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[18], -1);
	TextDrawSetShadow(textVelocimetro[18], 0);
	TextDrawBackgroundColor(textVelocimetro[18], 255);
	TextDrawFont(textVelocimetro[18], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[18], true);

	textVelocimetro[19] = TextDrawCreate(466.700408, 371.067810, "140");
	TextDrawLetterSize(textVelocimetro[19], 0.169332, 0.806222);
	TextDrawAlignment(textVelocimetro[19], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[19], -1);
	TextDrawSetShadow(textVelocimetro[19], 0);
	TextDrawBackgroundColor(textVelocimetro[19], 255);
	TextDrawFont(textVelocimetro[19], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[19], true);

	textVelocimetro[20] = TextDrawCreate(462.232757, 384.819854, "/");
	TextDrawLetterSize(textVelocimetro[20], 0.302664, 0.161036);
	TextDrawAlignment(textVelocimetro[20], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[20], -1);
	TextDrawSetShadow(textVelocimetro[20], 0);
	TextDrawBackgroundColor(textVelocimetro[20], 255);
	TextDrawFont(textVelocimetro[20], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[20], true);

	textVelocimetro[21] = TextDrawCreate(462.632781, 392.320312, "-");
	TextDrawLetterSize(textVelocimetro[21], 0.307664, 0.411036);
	TextDrawAlignment(textVelocimetro[21], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[21], -1);
	TextDrawSetShadow(textVelocimetro[21], 0);
	TextDrawBackgroundColor(textVelocimetro[21], 255);
	TextDrawFont(textVelocimetro[21], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[21], true);

	textVelocimetro[22] = TextDrawCreate(470.200622, 390.168975, "160");
	TextDrawLetterSize(textVelocimetro[22], 0.169332, 0.806222);
	TextDrawAlignment(textVelocimetro[22], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[22], -1);
	TextDrawSetShadow(textVelocimetro[22], 0);
	TextDrawBackgroundColor(textVelocimetro[22], 255);
	TextDrawFont(textVelocimetro[22], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[22], true);

	textVelocimetro[23] = TextDrawCreate(466.500396, 409.570159, "180");
	TextDrawLetterSize(textVelocimetro[23], 0.153332, 0.736222);
	TextDrawAlignment(textVelocimetro[23], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[23], -16776961);
	TextDrawSetShadow(textVelocimetro[23], 0);
	TextDrawBackgroundColor(textVelocimetro[23], 255);
	TextDrawFont(textVelocimetro[23], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[23], true);

	textVelocimetro[24] = TextDrawCreate(429.767547, 387.976531, ".");
	TextDrawLetterSize(textVelocimetro[24], 0.358666, 1.641850);
	TextDrawAlignment(textVelocimetro[24], TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(textVelocimetro[24], -16776961);
	TextDrawSetShadow(textVelocimetro[24], 0);
	TextDrawBackgroundColor(textVelocimetro[24], 255);
	TextDrawFont(textVelocimetro[24], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[24], true);

	textVelocimetro[25] = TextDrawCreate(410.298431, 379.364776, "/");
	TextDrawLetterSize(textVelocimetro[25], 0.289998, -0.183259);
	TextDrawAlignment(textVelocimetro[25], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[25], -1);
	TextDrawSetShadow(textVelocimetro[25], 0);
	TextDrawBackgroundColor(textVelocimetro[25], 255);
	TextDrawFont(textVelocimetro[25], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[25], true);

	textVelocimetro[26] = TextDrawCreate(413.331634, 370.151367, "/");
	TextDrawLetterSize(textVelocimetro[26], -0.227001, 0.243999);
	TextDrawAlignment(textVelocimetro[26], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[26], -1);
	TextDrawSetShadow(textVelocimetro[26], 0);
	TextDrawBackgroundColor(textVelocimetro[26], 255);
	TextDrawFont(textVelocimetro[26], TEXT_DRAW_FONT_3);
	TextDrawSetProportional(textVelocimetro[26], true);

	textVelocimetro[27] = TextDrawCreate(419.932037, 365.051055, "/");
	TextDrawLetterSize(textVelocimetro[27], -0.132001, 0.281332);
	TextDrawAlignment(textVelocimetro[27], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[27], -1);
	TextDrawSetShadow(textVelocimetro[27], 0);
	TextDrawBackgroundColor(textVelocimetro[27], 255);
	TextDrawFont(textVelocimetro[27], TEXT_DRAW_FONT_3);
	TextDrawSetProportional(textVelocimetro[27], true);

	textVelocimetro[28] = TextDrawCreate(426.732452, 360.350769, "/");
	TextDrawLetterSize(textVelocimetro[28], -0.108334, 0.434814);
	TextDrawAlignment(textVelocimetro[28], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[28], -1);
	TextDrawSetShadow(textVelocimetro[28], 0);
	TextDrawBackgroundColor(textVelocimetro[28], 255);
	TextDrawFont(textVelocimetro[28], TEXT_DRAW_FONT_3);
	TextDrawSetProportional(textVelocimetro[28], true);

	textVelocimetro[29] = TextDrawCreate(461.732666, 403.997955, "/");
	TextDrawLetterSize(textVelocimetro[29], 0.297329, -0.108592);
	TextDrawAlignment(textVelocimetro[29], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[29], -16776961);
	TextDrawSetShadow(textVelocimetro[29], 0);
	TextDrawBackgroundColor(textVelocimetro[29], 255);
	TextDrawFont(textVelocimetro[29], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[29], true);

	textVelocimetro[30] = TextDrawCreate(460.232574, 411.398406, "/");
	TextDrawLetterSize(textVelocimetro[30], 0.282330, -0.129333);
	TextDrawAlignment(textVelocimetro[30], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(textVelocimetro[30], -16776961);
	TextDrawSetShadow(textVelocimetro[30], 0);
	TextDrawBackgroundColor(textVelocimetro[30], 255);
	TextDrawFont(textVelocimetro[30], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(textVelocimetro[30], true);

 	return 1;
}

stock UpdatePonteiro(playerid, Float:velocidade) 
{
	destroyVelocityPonteiro(playerid);

	//new Float:calculePonteiroX = (velocidade / 13.0);
	//new Float:calculePonteiroY = (velocidade / 19.4);

	/*417.966827, 405.577606
	455.966827, 398.577606
	432.966827, 353.577606*/
}

stock destroyVelocityPonteiro(playerid)
{
	for (new text = 1; text != 10; text++) {
	    PlayerTextDrawDestroy(playerid, textPlayerVelocimetro[text][playerid]);
	    textPlayerVelocimetro[text][playerid] = PlayerText:-1;
	}
}