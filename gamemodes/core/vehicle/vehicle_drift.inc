/* -----------------------------------------------------------------------------------------------------
-
-   (vehicles/drift)
- 	    Módulo responsável pelo pop-up do drift
-
-------------------------------------------------------------------------------------------------------- */

// Includes

#include <YSI_Coding\y_hooks>

#if !defined _drift_included
	#tryinclude < drift-detection >
#endif

// ---------------------------------------------------------------------------------
// Include <samp-random-events>
#if !defined DRIFT_EVENT
	#define DRIFT_EVENT true
	#define DRIFT_EVENT_ID 1
	#define COLOR_DRIFT_EVENT 0xE79E3CFF
#endif

// ---------------------------------------------------------------------------
// Defines

#if !defined VEHICLE_DRIFT_COLORS_SCORE
	#define	VEHICLE_DRIFT_COLORS_SCORE	true
#endif

// ---------------------------------------------------------------------------
// Variáveis

static Float:DRIFT_Score[MAX_PLAYERS];

timer HidePopup[2000](playerid)
	PlayerTextDrawHide(playerid, popup_textdraw[playerid]);

stock FadePopup(playerid, tempo = 2000) {
	defer HidePopup[tempo](playerid);
}

// ---------------------------------------------------------------------------

hook OnPlayerConnect(playerid)
{
	Drift::EnableDetection(playerid);
	Drift::EnableDamageCheck(playerid);

	return 1;
}

public OnPlayerDriftStart(playerid)
{
	PlayerTextDrawSetString(playerid, popup_textdraw[playerid], "DRIFT~n~+0");
	PlayerTextDrawShow(playerid, popup_textdraw[playerid]);

	DRIFT_Score[playerid] = 0.0;

	return true;
}

public OnPlayerDriftUpdate(playerid, Float:drift_angle, Float:speed)
{
	new string[30];
	
	DRIFT_Score[playerid] += floatmul(speed, 2.0);

	// Cores conforme o score
	#if VEHICLE_DRIFT_COLORS_SCORE
		switch (floatround(DRIFT_Score[playerid], floatround_ceil))
		{
			case 0..4999:
				PlayerTextDrawChangeString(string, playerid, "DRIFT~n~+%.0f", popup_textdraw[playerid], DRIFT_Score[playerid]);
			case 5000..9999:
				PlayerTextDrawChangeString(string, playerid, "~b~~h~DRIFT~n~+%.0f", popup_textdraw[playerid], DRIFT_Score[playerid]);
			case 10000..19999:
				PlayerTextDrawChangeString(string, playerid, "~g~~h~DRIFT~n~+%.0f", popup_textdraw[playerid], DRIFT_Score[playerid]);
			default:
				PlayerTextDrawChangeString(string, playerid, "~p~DRIFT~n~+%.0f", popup_textdraw[playerid], DRIFT_Score[playerid]);
		}
	#else
		PlayerTextDrawChangeString(string, playerid, "DRIFT~n~+%.0f", popup_textdraw[playerid], DRIFT_Score[playerid]);
	#endif

	return 1;
}

public OnPlayerDriftEnd(playerid, reason, Float: distance, time)
{
	if (reason == DRIFT_END_REASON_DAMAGED)
		return Drift_StopScore(playerid);

	PlayerTextDrawHide(playerid, popup_textdraw[playerid]);

	#if defined _INC_samp_random_event
		if (EVENT[ev_started] && EVENT[ev_type] == DRIFT_EVENT_ID) {
			new string[128];
			new score_event = EVENT[ev_score][playerid] + floatround(DRIFT_Score[playerid], floatround_ceil);

			EVENT[ev_score][playerid] = score_event;
			EVENT[ev_bonus][playerid] += floatround(DRIFT_Score[playerid], floatround_ceil)/10;

			PlayerTextDrawChangeString(string, playerid, "%s", event_ptextdraw[0][playerid], PlayerName[playerid]);
			PlayerTextDrawChangeString(string, playerid, "%d", event_ptextdraw[1][playerid], EVENT[ev_score][playerid]);

			EVENT_UpdateRanks();
		}
	#endif

	return 1;
}

static Drift_StopScore(playerid) {

	new string[31];
	PlayerTextDrawChangeString(string, playerid, "~r~~h~DRIFT~n~-%.0f", popup_textdraw[playerid], DRIFT_Score[playerid]);

	DRIFT_Score[playerid] = 0.0;

	FadePopup(playerid, 2000);

	return 1;
}