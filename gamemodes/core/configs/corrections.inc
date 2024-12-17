timer _KickPlayer[1000](playerid) {
	return Kick(playerid);
}

stock KickEx(playerid) {
	defer _KickPlayer(playerid);
	return 1;
}