#include < YSI_Coding\y_hooks >

static 
	Timer:timer_pacifico[MAX_PLAYERS];

// -------------------------------------------------------------------------------
// Timers;
// Modo pacifico/agressivo;
timer TimerPacifico[10 * 60000](playerid) {

	if (Player_GetWanted(playerid)) {
		timer_pacifico[playerid] = defer TimerPacifico(playerid);
		return 1;
	}
	ShowPlayerPopupHUD(playerid, "STATUS", "Seu personagem esta ~g~~h~pacifico", 3000);

	PlayerTextDrawColor(playerid, baloon_preview_action[playerid], -1);

	PlayerTextDrawHide(playerid, baloon_preview_action[playerid]);

	PlayerInfo[playerid][mAgressivo] = false;

	return 1;
}

// Se��o agressivo (modo pacifico);
stock SetPlayerAgressivo(playerid) {
	PlayerInfo[playerid][mAgressivo] = true;

	PlayerTextDrawColor(playerid, baloon_preview_action[playerid], COLOR_RED);

	ShowPlayerPopupHUD(playerid, "STATUS", "Seu personagem esta ~r~~h~agressivo", 3000);

	timer_pacifico[playerid] = defer TimerPacifico(playerid);
}

stock CheckPlayerPacifico(playerid, issuerid) 
{
	// --------------------------------------------------------------------------------------------
	// Sistema de agressivo/pacifico automatico para os jogadores;

	if (issuerid != INVALID_PLAYER_ID) {
		// Condi��es para o modo pacifico;
	#if _inc_paintball_system
		if (GoChase[issuerid] != playerid && GetPlayerVirtualWorld(issuerid) != 10020 && Player_GetPaintball(issuerid) == INVALID_PAINTBALL_ID &&
		Player_InEvent(issuerid) && GetPlayerVirtualWorld(issuerid) != 10061 && !Zone_IsPlayerIn(playerid) && !gPlayerInGuerra(playerid))
		{

			if (IsACop(playerid) && !Player_GetWanted(issuerid)) {
				SetPlayerCriminal(issuerid, 255, "Agress�o a Autoridade");
				SetPlayerAgressivo(issuerid);
			}
			else if (!PlayerInfo[issuerid][mAgressivo]) {
				SetPlayerAgressivo(issuerid);

				/*if (!PlayerInfo[playerid][mAgressivo]) {
					SendClientMessage(issuerid, COLOR_LIGHTRED, "Esse jogador est� em modo pacifico, n�o provoque-o.");
				}
				return 0;*/

			} else {
				/*if (!PlayerInfo[playerid][mAgressivo]) {
					SendClientMessage(issuerid, COLOR_LIGHTRED, "Esse jogador est� em modo pacifico, n�o provoque-o.");

					SetPlayerArmedWeapon(issuerid, WEAPON_FIST);
					return 0;
				}*/
			}
		}
	#else
		if (GoChase[issuerid] != playerid && GetPlayerVirtualWorld(issuerid) != 10020 &&
		Player_InEvent(issuerid) && GetPlayerVirtualWorld(issuerid) != 10061 && !Zone_IsPlayerIn(playerid) && !gPlayerInGuerra(playerid))
		{

			if (IsACop(playerid) && !Player_GetWanted(issuerid)) {
				SetPlayerCriminal(issuerid, 255, "Agress�o a Autoridade");
				SetPlayerAgressivo(issuerid);
			}
			else if (!PlayerInfo[issuerid][mAgressivo]) {
				SetPlayerAgressivo(issuerid);

				/*if (!PlayerInfo[playerid][mAgressivo]) {
					SendClientMessage(issuerid, COLOR_LIGHTRED, "Esse jogador est� em modo pacifico, n�o provoque-o.");
				}
				return 0;*/

			} else {
				/*if (!PlayerInfo[playerid][mAgressivo]) {
					SendClientMessage(issuerid, COLOR_LIGHTRED, "Esse jogador est� em modo pacifico, n�o provoque-o.");

					SetPlayerArmedWeapon(issuerid, WEAPON_FIST);
					return 0;
				}*/
			}
		}
	#endif
	}
    return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    // --------------------------------------------------------------------------------------------
	// Anti-roubo novato de ve�culos
    // Caso voc� n�o seja dono e o ve�culo esteja ocupado.
	if (IsVehicleOccupied(vehicleid) && !ispassenger && !IsVehicleOwner(playerid, vehicleid))
	{
		/*if (!PlayerInfo[playerid][mAgressivo]) {
			SetPlayerAgressivo(playerid);
			SendClientMessage(playerid, COLOR_LIGHTRED, "Voc� tentou roubar um ve�culo e n�o est� mais em modo pacifico.");
		}
		else {
			FreezeThePlayer(playerid);
		}*/
	}
    return 1;
}