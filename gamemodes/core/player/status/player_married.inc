
CALLBACK:ClearMarriage(playerid)
{
	if (!IsPlayerConnected(playerid)) return false;

	strmid(PlayerInfo[playerid][pMarriedTo], "Ninguem", 0, strlen("Ninguem"), 255);
	PlayerInfo[playerid][pMarried] = 0;

	return true;
}

CALLBACK:ClearCrime(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		strmid(PlayerCrime[playerid][pBplayer], "********", 0, strlen("********"), 255);
		strmid(PlayerCrime[playerid][pVictim], "********", 0, strlen("********"), 255);
		strmid(PlayerCrime[playerid][pAccusing], "********", 0, strlen("********"), 255);
		strmid(PlayerCrime[playerid][pAccusedof], "********", 0, strlen("********"), 255);
	}
	return true;
}