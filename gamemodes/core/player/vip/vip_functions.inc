CALLBACK:SendVIPMessage(color, striing[]) {
    foreach(new i : Player) {
        if (PlayerInfo[i][pVIP] > 0 && PlayerInfo[i][pChatVip]) SendClientMessage(i, color, striing);
    }
}


stock GetDonateRank(playerid)
{
	new Str[75];

	switch(PlayerInfo[playerid][pVIP])
	{
	    case 1			:Str = "{A4CCC3}S�cio Comum";
	    case 2..6		:Str = "{DBB960}S�cio Premium";
	    case 7			:Str = "{017bff}S�cio Supreme";
	    case 8			:Str = "{DC0139}S�cio Extreme";
	    default         :Str = "Free";
	}
	return Str;
}

stock GetVipColor(playerid)
{
	new playerVIPColor[7];

	switch(Player_GetVIP(playerid)) 
	{
  		case 1:			playerVIPColor = "A4CCC3";
		case 2..6:		playerVIPColor = "DBB960";
		case 7:			playerVIPColor = "017bff";
		case 8:			playerVIPColor = "DC0139";
		default:		playerVIPColor = "00D900";
	}
	return playerVIPColor;
}

stock GetAnuncioRank(playerid) 
{
	new playerVIPName[25];

	switch(Player_GetVIP(playerid)) 
	{
  		case 1:			playerVIPName = "COMUM";
		case 2..6:		playerVIPName = "PREMIUM";
		case 7:			playerVIPName = "SUPREME";
		case 8:			playerVIPName = "EXTREME";
		case 9:			playerVIPName = "BOOSTER";
		default:		playerVIPName = "FREE";
	}
	return playerVIPName;
}

stock VIP_GetName(vip_nivel)
{
    new vip_name[15];
	switch (vip_nivel) {
		case 1: 	vip_name = "S�cio Comum";
		case 2..6: 	vip_name = "S�cio Premium";
		case 7: 	vip_name = "S�cio Supreme";
		case 8: 	vip_name = "S�cio Extreme";
		case 9:		vip_name = "S�cio Booster";
		default: 	vip_name = "FREE";
	}
	return vip_name;
}