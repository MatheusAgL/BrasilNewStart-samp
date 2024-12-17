#include <YSI_Coding\y_hooks>

new PlayerText:SniperShot[MAX_PLAYERS];

hook CreateDynamicTextDraws(playerid) {
    new Float:height = IsAndroidPlayer(playerid) ? 0.00 : -30.00;

    SniperShot[playerid] = CreatePlayerTextDraw(playerid,7.000000, 214.000000 + height, "_");
	PlayerTextDrawBackgroundColor(playerid,SniperShot[playerid], 255);
	PlayerTextDrawFont(playerid,SniperShot[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,SniperShot[playerid], 0.300000, 1.200000);
	PlayerTextDrawColor(playerid,SniperShot[playerid], -1);
	PlayerTextDrawSetOutline(playerid,SniperShot[playerid], 1);
	PlayerTextDrawSetProportional(playerid,SniperShot[playerid], true);
	PlayerTextDrawSetSelectable(playerid,SniperShot[playerid], false);
}