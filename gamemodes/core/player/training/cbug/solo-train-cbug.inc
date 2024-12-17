/*  ----------------------------------------------------------------------------------------------------------------------------------------

        Treinamento solo de cbug
                            v0.3
                            Theus_Crazzy (wearLyS)

 ----------------------------------------------------------------------------------------------------------------------------------------- */

// Includes

#include <YSI_Coding\y_hooks>

#include <solo-train-cbug-entry>


// --------------------------------------------------------------------------------
// Variáveis
enum cbugEnum
{
	bool: cbug_valid,
	cbug_tick,
	cbug_count,
	Timer: cbug_timer,
}
static CBUG[MAX_PLAYERS][cbugEnum];

// --------------------------------------------------------------------------------
// Funções

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) 
{
	if (weaponid == 24) {
		updatePlayerCBug(playerid);
	}
    return 1;
}

CALLBACK: OnPlayerCbugged(playerid, timercbug)
{
	new string[128];

	if (EVENT[ev_started] && EVENT[ev_type] == CBUG_EVENT_ID)
	{
		EVENT[ev_score][playerid] = timercbug;
		EVENT[ev_bonus][playerid] = (4000000/timercbug);

		PlayerTextDrawChangeString(string, playerid, "%s", event_ptextdraw[0][playerid], PlayerName[playerid]);
		PlayerTextDrawChangeString(string, playerid, "%d ms", event_ptextdraw[1][playerid], EVENT[ev_score][playerid]);

		EVENT_UpdateRanks();
	}
	return 1;
}

timer updateCountCbug[500](playerid)
{
	new timercbug = GetTickCount() - CBUG[playerid][cbug_tick];

	new string[35];
	PlayerTextDrawChangeString(string, playerid, "C-BUG~n~%d ms~n~Balas: %d/7", popup_textdraw[playerid], timercbug, CBUG[playerid][cbug_count]);

	if (timercbug > 10000)
	    cancelPlayerCbug(playerid);
}

stock updatePlayerCBug(playerid)
{
	if (CBUG[playerid][cbug_valid])
	{
	    CBUG[playerid][cbug_count] ++;

		if (CBUG[playerid][cbug_count] >= 7)
		{
 		    new string[100];
 		    new timercbug = GetTickCount() - CBUG[playerid][cbug_tick];

 		    format(string, sizeof string, "[CBUG]: %s gastou as 7 balas de Desert Eagle em [%d ms]", PlayerName[playerid], timercbug);
 		    SendClientMessageInRange(30.0, playerid, string, 0xBBBBFFFF, 0xBBBBFFFF, 0xBBBBFFFF, 0xBBBBFFFF, 0xBBBBFFFF);

			// Caso tenha evento
			OnPlayerCbugged(playerid, timercbug);

 		    cancelPlayerCbug(playerid);

 		    return true;
 		}

	    if (CBUG[playerid][cbug_count] == 1)
		{
			stop CBUG[playerid][cbug_timer];

	        CBUG[playerid][cbug_tick]  = GetTickCount();
			CBUG[playerid][cbug_timer] = repeat updateCountCbug(playerid);

			PlayerTextDrawSetString(playerid, popup_textdraw[playerid], "C-BUG~n~000 ms");
			PlayerTextDrawShow(playerid, popup_textdraw[playerid]);
	    }
	}
	return 1;
}

stock cancelPlayerCbug(playerid)
{
    CBUG[playerid][cbug_valid] = false;

 	stop CBUG[playerid][cbug_timer];
 	PlayerTextDrawHide(playerid, popup_textdraw[playerid]);
}

CMD:testarcbug(playerid)
{
    cancelPlayerCbug(playerid);

    CBUG[playerid][cbug_valid] = true;
    CBUG[playerid][cbug_count] = 0;

    SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você iniciou o teste CBUG, agora dispare 7 tiros com a Desert Eagle!");

	return 1;
}
alias:testarcbug("cbug")

hook OnPlayerDisconnect(playerid, reason)
{
	CBUG[playerid][cbug_valid] = false;
	stop CBUG[playerid][cbug_timer];

	return 1;
}