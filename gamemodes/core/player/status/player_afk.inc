
static Float:player_OldPos[3][MAX_PLAYERS];
static PlayerAFK_Timer[MAX_PLAYERS];

stock Player_SetActive(playerid, bool:stats) 
{
    if (stats == true) {
        if (PlayerAFK_Timer[playerid] > 0) {
            PlayerAFK_Timer[playerid] = 0;
        }
    } else {
        if (PlayerAFK_Timer[playerid] == 0) {
            PlayerAFK_Timer[playerid] = gettime();
        }
    }
}

stock Player_GetTimerAFK(playerid) {
    return PlayerAFK_Timer[playerid];
}

ptask PlayerAFK_CheckPos[60000 * 10](playerid) 
{
    if (!PlayerToPoint(0.5, playerid, player_OldPos[0][playerid], player_OldPos[1][playerid], player_OldPos[2][playerid])) {
        static Float:player_ActualPos[3];
        GetPlayerPos(playerid, player_ActualPos[0], player_ActualPos[1], player_ActualPos[2]);

        player_OldPos[0][playerid] = player_ActualPos[0];
		player_OldPos[1][playerid] = player_ActualPos[1];
  		player_OldPos[2][playerid] = player_ActualPos[2];

        Player_SetActive(playerid, true);
	} else {
        Player_SetActive(playerid, false);
	}
}

hook OnPlayerText(playerid, text[]) 
{
    Player_SetActive(playerid, true);
    return 1;
}

hook OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
    Player_SetActive(playerid, true);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) 
{
    Player_SetActive(playerid, true);
    return 1;
}