#include <YSI_Coding\y_hooks>

new PlayerText:action_td[2][MAX_PLAYERS];

hook CreateDynamicTextDraws(playerid) {
	action_td[0][playerid] = CreatePlayerTextDraw(playerid, 320.000000, 257.000000, "_");
	PlayerTextDrawFont(playerid, action_td[0][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, action_td[0][playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, action_td[0][playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, action_td[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid, action_td[0][playerid], 0);
	PlayerTextDrawAlignment(playerid, action_td[0][playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, action_td[0][playerid], -1061109519);
	PlayerTextDrawBackgroundColor(playerid, action_td[0][playerid], 50);
	PlayerTextDrawBoxColor(playerid, action_td[0][playerid], 50);
	PlayerTextDrawUseBox(playerid, action_td[0][playerid], false);
	PlayerTextDrawSetProportional(playerid, action_td[0][playerid], true);
	PlayerTextDrawSetSelectable(playerid, action_td[0][playerid], false);

	action_td[1][playerid] = CreatePlayerTextDraw(playerid, 300.000000, 244.000000, "LD_BEAT:cring");
	PlayerTextDrawFont(playerid, action_td[1][playerid], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawLetterSize(playerid, action_td[1][playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, action_td[1][playerid], 39.000000, 46.000000);
	PlayerTextDrawSetOutline(playerid, action_td[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid, action_td[1][playerid], 0);
	PlayerTextDrawAlignment(playerid, action_td[1][playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, action_td[1][playerid], 70);
	PlayerTextDrawBackgroundColor(playerid, action_td[1][playerid], 255);
	PlayerTextDrawBoxColor(playerid, action_td[1][playerid], 50);
	PlayerTextDrawUseBox(playerid, action_td[1][playerid], false);
	PlayerTextDrawSetProportional(playerid, action_td[1][playerid], true);
	PlayerTextDrawSetSelectable(playerid, action_td[1][playerid], false);
}

stock ShowActionTextDrawForPlayer(playerid, const key[]="H") {
	PlayerTextDrawSetString(playerid, action_td[0][playerid], key);

	for(new i; i < sizeof(action_td); i++)
		PlayerTextDrawShow(playerid, action_td[i][playerid]);
}

stock HideActionTextDrawForPlayer(playerid) {
	for(new i; i < sizeof(action_td); i++)
		PlayerTextDrawHide(playerid, action_td[i][playerid]);
}