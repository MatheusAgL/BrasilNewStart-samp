// ---------------------------------------------------------------
new
    g_MysqlRaceCheck[MAX_PLAYERS],
	Timer:loadLogin_Timer[MAX_PLAYERS],
	percent_loadLogin[MAX_PLAYERS]
;

stock Login_CheckIP(playerid, const test_ip[])
{
	if (!strcmp(test_ip, "127.0.0.1") || 
		!strcmp(test_ip, "localhost"))
		return 0;

    new against_ip[32 + 1];
    
    foreach(new x : Player) 
	{
		if (x == playerid)
			continue;

        GetPlayerIp(x, against_ip, 32);
        
        if (!strcmp(against_ip, test_ip) && (Admin_GetNivel(x) || Helper_GetNivel(x)) && !Player_Logado(x)) 
			return 1;
    }
    return 0;
}

stock Player_CheckNick(playerid) 
{
	new nickname[MAX_PLAYER_NAME];
	GetPlayerName(playerid, nickname, MAX_PLAYER_NAME);
	
	if (strcmp(nickname, PlayerName[playerid], false) && 
		SetPlayerName(playerid, PlayerName[playerid]) != 1) {
		ServerLog::("bug", "%s tentou logar com o mesmo nick duas vezes.", PlayerName[playerid]);
		KickEx(playerid);

		return false;
	}
	return true;
}

stock SetRandomName(playerid) {
	new playername[MAX_PLAYER_NAME];
	format(playername, sizeof(playername), "Logando_%d", playerid);
	SetPlayerName(playerid, playername);
}

static bool:playerRegistered[MAX_PLAYERS];

stock IsPlayerRegistered(playerid) {
	return playerRegistered[playerid];
}

stock SetPlayerRegistered(playerid, bool:status) {
	playerRegistered[playerid] = status;
}