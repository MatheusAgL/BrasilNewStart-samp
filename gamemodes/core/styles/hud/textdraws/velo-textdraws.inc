/*

    Textdraws da HUD
	Modulação controlável, facilmente de se compreender, muita dedicação envolvida!

    Última modificação: 22/02/2021
    Responsável: Theus_Crazzy

*/
#include <YSI_Coding\y_hooks>

stock CreateTextDraws_PlayerDrugInfo()
{
    _drugs_textdraw[0] = TextDrawCreate(124.000000, 356.000000 - 12.000, "HUD:radar_mcstrap");
    TextDrawFont(_drugs_textdraw[0], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(_drugs_textdraw[0], 0.600000, 2.000000);
    TextDrawTextSize(_drugs_textdraw[0], 12.000000, 12.000000);
    TextDrawSetOutline(_drugs_textdraw[0], 1);
    TextDrawSetShadow(_drugs_textdraw[0], 0);
    TextDrawAlignment(_drugs_textdraw[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_drugs_textdraw[0], -1);
    TextDrawBackgroundColor(_drugs_textdraw[0], 255);
    TextDrawBoxColor(_drugs_textdraw[0], 50);
    TextDrawUseBox(_drugs_textdraw[0], true);
    TextDrawSetProportional(_drugs_textdraw[0], true);
    TextDrawSetSelectable(_drugs_textdraw[0], false);

    _drugs_textdraw[1] = TextDrawCreate(124.000000, 375.000000 - 12.000, "HUD:radar_triadscasino");
    TextDrawFont(_drugs_textdraw[1], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(_drugs_textdraw[1], 0.600000, 2.000000);
    TextDrawTextSize(_drugs_textdraw[1], 12.000000, 12.000000);
    TextDrawSetOutline(_drugs_textdraw[1], 1);
    TextDrawSetShadow(_drugs_textdraw[1], 0);
    TextDrawAlignment(_drugs_textdraw[1], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_drugs_textdraw[1], -1);
    TextDrawBackgroundColor(_drugs_textdraw[1], 255);
    TextDrawBoxColor(_drugs_textdraw[1], 50);
    TextDrawUseBox(_drugs_textdraw[1], true);
    TextDrawSetProportional(_drugs_textdraw[1], true);
    TextDrawSetSelectable(_drugs_textdraw[1], false);

    _drugs_textdraw[2] = TextDrawCreate(124.000000, 394.000000 - 12.000, "HUD:radar_triads");
    TextDrawFont(_drugs_textdraw[2], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(_drugs_textdraw[2], 0.600000, 2.000000);
    TextDrawTextSize(_drugs_textdraw[2], 12.000000, 12.000000);
    TextDrawSetOutline(_drugs_textdraw[2], 1);
    TextDrawSetShadow(_drugs_textdraw[2], 0);
    TextDrawAlignment(_drugs_textdraw[2], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_drugs_textdraw[2], -1);
    TextDrawBackgroundColor(_drugs_textdraw[2], 255);
    TextDrawBoxColor(_drugs_textdraw[2], 50);
    TextDrawUseBox(_drugs_textdraw[2], true);
    TextDrawSetProportional(_drugs_textdraw[2], true);
    TextDrawSetSelectable(_drugs_textdraw[2], false);

    _drugs_textdraw[3] = TextDrawCreate(124.000000, 413.000000 - 12.000, "HUD:radar_LocoSyndicate");
    TextDrawFont(_drugs_textdraw[3], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(_drugs_textdraw[3], 0.600000, 2.000000);
    TextDrawTextSize(_drugs_textdraw[3], 12.000000, 12.000000);
    TextDrawSetOutline(_drugs_textdraw[3], 1);
    TextDrawSetShadow(_drugs_textdraw[3], 0);
    TextDrawAlignment(_drugs_textdraw[3], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_drugs_textdraw[3], -1);
    TextDrawBackgroundColor(_drugs_textdraw[3], 255);
    TextDrawBoxColor(_drugs_textdraw[3], 50);
    TextDrawUseBox(_drugs_textdraw[3], true);
    TextDrawSetProportional(_drugs_textdraw[3], true);
    TextDrawSetSelectable(_drugs_textdraw[3], false);

    _drugs_textdraw[4] = TextDrawCreate(124.000000, 432.000000 - 12.000, "HUD:radar_mafiaCasino");
    TextDrawFont(_drugs_textdraw[4], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(_drugs_textdraw[4], 0.600000, 2.000000);
    TextDrawTextSize(_drugs_textdraw[4], 12.000000, 12.000000);
    TextDrawSetOutline(_drugs_textdraw[4], 1);
    TextDrawSetShadow(_drugs_textdraw[4], 0);
    TextDrawAlignment(_drugs_textdraw[4], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_drugs_textdraw[4], -1);
    TextDrawBackgroundColor(_drugs_textdraw[4], 255);
    TextDrawBoxColor(_drugs_textdraw[4], 50);
    TextDrawUseBox(_drugs_textdraw[4], true);
    TextDrawSetProportional(_drugs_textdraw[4], true);
    TextDrawSetSelectable(_drugs_textdraw[4], false);
}

stock CreatePlayerTextDrawsDrugInfo(playerid)
{	
    _drugs_playertextdraw[0][playerid] = CreatePlayerTextDraw(playerid, 139.000000, 356.000000 - 12.000, "01:00");
    PlayerTextDrawFont(playerid, _drugs_playertextdraw[0][playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, _drugs_playertextdraw[0][playerid], 0.191667, 1.149999);
    PlayerTextDrawTextSize(playerid, _drugs_playertextdraw[0][playerid], 396.000000, 13.500000);
    PlayerTextDrawSetOutline(playerid, _drugs_playertextdraw[0][playerid], 1);
    PlayerTextDrawSetShadow(playerid, _drugs_playertextdraw[0][playerid], 0);
    PlayerTextDrawAlignment(playerid, _drugs_playertextdraw[0][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, _drugs_playertextdraw[0][playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, _drugs_playertextdraw[0][playerid], 255);
    PlayerTextDrawBoxColor(playerid, _drugs_playertextdraw[0][playerid], 50);
    PlayerTextDrawUseBox(playerid, _drugs_playertextdraw[0][playerid], false);
    PlayerTextDrawSetProportional(playerid, _drugs_playertextdraw[0][playerid], true);
    PlayerTextDrawSetSelectable(playerid, _drugs_playertextdraw[0][playerid], false);

    _drugs_playertextdraw[1][playerid] = CreatePlayerTextDraw(playerid, 139.000000, 375.000000 - 12.000, "01:00");
    PlayerTextDrawFont(playerid, _drugs_playertextdraw[1][playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, _drugs_playertextdraw[1][playerid], 0.191667, 1.149999);
    PlayerTextDrawTextSize(playerid, _drugs_playertextdraw[1][playerid], 396.000000, 13.500000);
    PlayerTextDrawSetOutline(playerid, _drugs_playertextdraw[1][playerid], 1);
    PlayerTextDrawSetShadow(playerid, _drugs_playertextdraw[1][playerid], 0);
    PlayerTextDrawAlignment(playerid, _drugs_playertextdraw[1][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, _drugs_playertextdraw[1][playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, _drugs_playertextdraw[1][playerid], 255);
    PlayerTextDrawBoxColor(playerid, _drugs_playertextdraw[1][playerid], 50);
    PlayerTextDrawUseBox(playerid, _drugs_playertextdraw[1][playerid], false);
    PlayerTextDrawSetProportional(playerid, _drugs_playertextdraw[1][playerid], true);
    PlayerTextDrawSetSelectable(playerid, _drugs_playertextdraw[1][playerid], false);

    _drugs_playertextdraw[2][playerid] = CreatePlayerTextDraw(playerid, 139.000000, 394.000000 - 12.000, "01:00");
    PlayerTextDrawFont(playerid, _drugs_playertextdraw[2][playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, _drugs_playertextdraw[2][playerid], 0.191667, 1.149999);
    PlayerTextDrawTextSize(playerid, _drugs_playertextdraw[2][playerid], 396.000000, 13.500000);
    PlayerTextDrawSetOutline(playerid, _drugs_playertextdraw[2][playerid], 1);
    PlayerTextDrawSetShadow(playerid, _drugs_playertextdraw[2][playerid], 0);
    PlayerTextDrawAlignment(playerid, _drugs_playertextdraw[2][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, _drugs_playertextdraw[2][playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, _drugs_playertextdraw[2][playerid], 255);
    PlayerTextDrawBoxColor(playerid, _drugs_playertextdraw[2][playerid], 50);
    PlayerTextDrawUseBox(playerid, _drugs_playertextdraw[2][playerid], false);
    PlayerTextDrawSetProportional(playerid, _drugs_playertextdraw[2][playerid], true);
    PlayerTextDrawSetSelectable(playerid, _drugs_playertextdraw[2][playerid], false);

    _drugs_playertextdraw[3][playerid] = CreatePlayerTextDraw(playerid, 139.000000, 413.000000 - 12.000, "01:00");
    PlayerTextDrawFont(playerid, _drugs_playertextdraw[3][playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, _drugs_playertextdraw[3][playerid], 0.191667, 1.149999);
    PlayerTextDrawTextSize(playerid, _drugs_playertextdraw[3][playerid], 396.000000, 13.500000);
    PlayerTextDrawSetOutline(playerid, _drugs_playertextdraw[3][playerid], 1);
    PlayerTextDrawSetShadow(playerid, _drugs_playertextdraw[3][playerid], 0);
    PlayerTextDrawAlignment(playerid, _drugs_playertextdraw[3][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, _drugs_playertextdraw[3][playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, _drugs_playertextdraw[3][playerid], 255);
    PlayerTextDrawBoxColor(playerid, _drugs_playertextdraw[3][playerid], 50);
    PlayerTextDrawUseBox(playerid, _drugs_playertextdraw[3][playerid], false);
    PlayerTextDrawSetProportional(playerid, _drugs_playertextdraw[3][playerid], true);
    PlayerTextDrawSetSelectable(playerid, _drugs_playertextdraw[3][playerid], false);

    _drugs_playertextdraw[4][playerid] = CreatePlayerTextDraw(playerid, 139.000000, 432.000000 - 12.000, "01:00");
    PlayerTextDrawFont(playerid, _drugs_playertextdraw[4][playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, _drugs_playertextdraw[4][playerid], 0.191667, 1.149999);
    PlayerTextDrawTextSize(playerid, _drugs_playertextdraw[4][playerid], 396.000000, 13.500000);
    PlayerTextDrawSetOutline(playerid, _drugs_playertextdraw[4][playerid], 1);
    PlayerTextDrawSetShadow(playerid, _drugs_playertextdraw[4][playerid], 0);
    PlayerTextDrawAlignment(playerid, _drugs_playertextdraw[4][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, _drugs_playertextdraw[4][playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, _drugs_playertextdraw[4][playerid], 255);
    PlayerTextDrawBoxColor(playerid, _drugs_playertextdraw[4][playerid], 50);
    PlayerTextDrawUseBox(playerid, _drugs_playertextdraw[4][playerid], false);
    PlayerTextDrawSetProportional(playerid, _drugs_playertextdraw[4][playerid], true);
    PlayerTextDrawSetSelectable(playerid, _drugs_playertextdraw[4][playerid], false);
}