#include <YSI_Coding\y_hooks>

new PlayerText:ptd_paintball[MAX_PLAYERS];

stock CreatePlayerTD_Paintball(playerid)
{
    ptd_paintball[playerid] = CreatePlayerTextDraw(playerid, 4.000000, 322.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, ptd_paintball[playerid], 150);
	PlayerTextDrawFont(playerid, ptd_paintball[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, ptd_paintball[playerid], 0.240000, 1.099999);
	PlayerTextDrawColor(playerid, ptd_paintball[playerid], -1);
	PlayerTextDrawSetOutline(playerid, ptd_paintball[playerid], 1);
	PlayerTextDrawSetProportional(playerid, ptd_paintball[playerid], true);
	PlayerTextDrawSetSelectable(playerid, ptd_paintball[playerid], false);

	return 1;
}