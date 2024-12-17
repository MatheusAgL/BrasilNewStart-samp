#include <YSI_Coding\y_hooks>

#define         _PROCURANDO_INFO_hud_system     true

new PlayerText:textDrawSearch[6][MAX_PLAYERS];

hook CreateDynamicTextDraws(playerid) {

	static Float:sumPosX = 0.00;
	if (IsAndroidPlayer(playerid))
		sumPosX = -108.00;

	textDrawSearch[0][playerid] = CreatePlayerTextDraw(playerid, 428.000000 + sumPosX, 393.000000, "_");
	PlayerTextDrawFont(playerid, textDrawSearch[0][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, textDrawSearch[0][playerid], 0.550000, 3.900002);
	PlayerTextDrawTextSize(playerid, textDrawSearch[0][playerid], 298.500000, 83.500000);
	PlayerTextDrawSetOutline(playerid, textDrawSearch[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textDrawSearch[0][playerid], 0);
	PlayerTextDrawAlignment(playerid, textDrawSearch[0][playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, textDrawSearch[0][playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, textDrawSearch[0][playerid], 255);
	PlayerTextDrawBoxColor(playerid, textDrawSearch[0][playerid], 105);
	PlayerTextDrawUseBox(playerid, textDrawSearch[0][playerid], true);
	PlayerTextDrawSetProportional(playerid, textDrawSearch[0][playerid], true);
	PlayerTextDrawSetSelectable(playerid, textDrawSearch[0][playerid], false);

	textDrawSearch[1][playerid] = CreatePlayerTextDraw(playerid, 428.000000 + sumPosX, 380.000000, "PROCURA");
	PlayerTextDrawFont(playerid, textDrawSearch[1][playerid], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, textDrawSearch[1][playerid], 0.133332, 1.100000);
	PlayerTextDrawTextSize(playerid, textDrawSearch[1][playerid], 400.000000, 83.500000);
	PlayerTextDrawSetOutline(playerid, textDrawSearch[1][playerid], 0);
	PlayerTextDrawSetShadow(playerid, textDrawSearch[1][playerid], 0);
	PlayerTextDrawAlignment(playerid, textDrawSearch[1][playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, textDrawSearch[1][playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, textDrawSearch[1][playerid], 255);
	PlayerTextDrawBoxColor(playerid, textDrawSearch[1][playerid], 125);
	PlayerTextDrawUseBox(playerid, textDrawSearch[1][playerid], true);
	PlayerTextDrawSetProportional(playerid, textDrawSearch[1][playerid], true);
	PlayerTextDrawSetSelectable(playerid, textDrawSearch[1][playerid], false);

	textDrawSearch[2][playerid] = CreatePlayerTextDraw(playerid, 428.000000 + sumPosX, 405.000000, "G.R.O.T.A");
	PlayerTextDrawFont(playerid, textDrawSearch[2][playerid], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, textDrawSearch[2][playerid], 0.133332, 0.949999);
	PlayerTextDrawTextSize(playerid, textDrawSearch[2][playerid], 400.000000, 83.500000);
	PlayerTextDrawSetOutline(playerid, textDrawSearch[2][playerid], 0);
	PlayerTextDrawSetShadow(playerid, textDrawSearch[2][playerid], 0);
	PlayerTextDrawAlignment(playerid, textDrawSearch[2][playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, textDrawSearch[2][playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, textDrawSearch[2][playerid], 255);
	PlayerTextDrawBoxColor(playerid, textDrawSearch[2][playerid], 189);
	PlayerTextDrawUseBox(playerid, textDrawSearch[2][playerid], false);
	PlayerTextDrawSetProportional(playerid, textDrawSearch[2][playerid], true);
	PlayerTextDrawSetSelectable(playerid, textDrawSearch[2][playerid], false);

	textDrawSearch[3][playerid] = CreatePlayerTextDraw(playerid, 428.000000 + sumPosX, 416.000000, "~y~Commerce");
	PlayerTextDrawFont(playerid, textDrawSearch[3][playerid], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, textDrawSearch[3][playerid], 0.133332, 0.949999);
	PlayerTextDrawTextSize(playerid, textDrawSearch[3][playerid], 400.000000, 83.500000);
	PlayerTextDrawSetOutline(playerid, textDrawSearch[3][playerid], 0);
	PlayerTextDrawSetShadow(playerid, textDrawSearch[3][playerid], 0);
	PlayerTextDrawAlignment(playerid, textDrawSearch[3][playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, textDrawSearch[3][playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, textDrawSearch[3][playerid], 255);
	PlayerTextDrawBoxColor(playerid, textDrawSearch[3][playerid], 189);
	PlayerTextDrawUseBox(playerid, textDrawSearch[3][playerid], false);
	PlayerTextDrawSetProportional(playerid, textDrawSearch[3][playerid], true);
	PlayerTextDrawSetSelectable(playerid, textDrawSearch[3][playerid], false);

	textDrawSearch[4][playerid] = CreatePlayerTextDraw(playerid, 428.000000 + sumPosX, 393.000000, "iHollyZinhO");
	PlayerTextDrawFont(playerid, textDrawSearch[4][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, textDrawSearch[4][playerid], 0.179166, 1.100000);
	PlayerTextDrawTextSize(playerid, textDrawSearch[4][playerid], 400.000000, 524.500000);
	PlayerTextDrawSetOutline(playerid, textDrawSearch[4][playerid], 0);
	PlayerTextDrawSetShadow(playerid, textDrawSearch[4][playerid], 0);
	PlayerTextDrawAlignment(playerid, textDrawSearch[4][playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, textDrawSearch[4][playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, textDrawSearch[4][playerid], 255);
	PlayerTextDrawBoxColor(playerid, textDrawSearch[4][playerid], 189);
	PlayerTextDrawUseBox(playerid, textDrawSearch[4][playerid], false);
	PlayerTextDrawSetProportional(playerid, textDrawSearch[4][playerid], true);
	PlayerTextDrawSetSelectable(playerid, textDrawSearch[4][playerid], false);

	textDrawSearch[5][playerid] = CreatePlayerTextDraw(playerid, 460.000000 + sumPosX, 381.000000, "300");
	PlayerTextDrawFont(playerid, textDrawSearch[5][playerid], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, textDrawSearch[5][playerid], 0.104166, 0.899999);
	PlayerTextDrawTextSize(playerid, textDrawSearch[5][playerid], 395.000000, 15.000000);
	PlayerTextDrawSetOutline(playerid, textDrawSearch[5][playerid], 0);
	PlayerTextDrawSetShadow(playerid, textDrawSearch[5][playerid], 0);
	PlayerTextDrawAlignment(playerid, textDrawSearch[5][playerid], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, textDrawSearch[5][playerid], 1687547391);
	PlayerTextDrawBackgroundColor(playerid, textDrawSearch[5][playerid], 255);
	PlayerTextDrawBoxColor(playerid, textDrawSearch[5][playerid], 50);
	PlayerTextDrawUseBox(playerid, textDrawSearch[5][playerid], false);
	PlayerTextDrawSetProportional(playerid, textDrawSearch[5][playerid], true);
	PlayerTextDrawSetSelectable(playerid, textDrawSearch[5][playerid], false);
}

hook OnPlayerDisconnect(playerid) {
    for(new i = 0; i < sizeof(textDrawSearch); i++)
        PlayerTextDrawDestroy(playerid, textDrawSearch[i][playerid]);
}

stock HidePlayerSearch(playerid) {
    for(new i = 0; i < sizeof(textDrawSearch); i++)
        PlayerTextDrawHide(playerid, textDrawSearch[i][playerid]);
}

stock ShowPlayerSearch(playerid, searchedid) {
    new Float:x, Float:y, Float:z, string[256];
	GetPlayerPos(searchedid, x, y, z);

    new MapZone:zone = GetMapZoneAtPoint2D(x, y), zone_name[MAX_MAP_ZONE_NAME];
	GetMapZoneName(zone, zone_name);

	if (IsValidDynamicPlayerTextDraw(playerid, textDrawSearch[2][playerid]))
    	PlayerTextDrawSetString(playerid, textDrawSearch[2][playerid], NomeORG(searchedid));

    format(string, sizeof(string), "~y~%s", zone_name);
	if (IsValidDynamicPlayerTextDraw(playerid, textDrawSearch[3][playerid]))
    	PlayerTextDrawSetString(playerid, textDrawSearch[3][playerid], string);

	if (IsValidDynamicPlayerTextDraw(playerid, textDrawSearch[4][playerid]))
    	PlayerTextDrawSetString(playerid, textDrawSearch[4][playerid], PlayerName[searchedid]);

    format(string, sizeof(string), "%d", Search_GetTime(playerid) - gettime());
	if (IsValidDynamicPlayerTextDraw(playerid, textDrawSearch[5][playerid]))
    	PlayerTextDrawSetString(playerid, textDrawSearch[5][playerid], string);

    for(new i = 0; i < 6; i++) {
		if (IsValidDynamicPlayerTextDraw(playerid, textDrawSearch[i][playerid]))
        	PlayerTextDrawShow(playerid, textDrawSearch[i][playerid]);
    }
}