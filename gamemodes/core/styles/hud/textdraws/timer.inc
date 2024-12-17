#include <YSI_Coding\y_hooks>

new PlayerText:textDrawTimer[3][MAX_PLAYERS];

hook CreateStaticTextDraws(playerid) {
    textDrawTimer[0][playerid] = CreatePlayerTextDraw(playerid, 319.000000, 371.000000, "_");
    PlayerTextDrawFont(playerid, textDrawTimer[0][playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, textDrawTimer[0][playerid], 0.600000, 4.399999);
    PlayerTextDrawTextSize(playerid, textDrawTimer[0][playerid], 334.000000, 97.000000);
    PlayerTextDrawSetOutline(playerid, textDrawTimer[0][playerid], 1);
    PlayerTextDrawSetShadow(playerid, textDrawTimer[0][playerid], 0);
    PlayerTextDrawAlignment(playerid, textDrawTimer[0][playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, textDrawTimer[0][playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, textDrawTimer[0][playerid], 255);
    PlayerTextDrawBoxColor(playerid, textDrawTimer[0][playerid], 135);
    PlayerTextDrawUseBox(playerid, textDrawTimer[0][playerid], true);
    PlayerTextDrawSetProportional(playerid, textDrawTimer[0][playerid], true);
    PlayerTextDrawSetSelectable(playerid, textDrawTimer[0][playerid], false);

    textDrawTimer[1][playerid] = CreatePlayerTextDraw(playerid, 319.000000, 387.000000, "TEMPO RESTANTE DE PRISAO~n~~r~~h~~h~120");
    PlayerTextDrawFont(playerid, textDrawTimer[1][playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, textDrawTimer[1][playerid], 0.179166, 1.100000);
    PlayerTextDrawTextSize(playerid, textDrawTimer[1][playerid], 400.000000, 167.000000);
    PlayerTextDrawSetOutline(playerid, textDrawTimer[1][playerid], 0);
    PlayerTextDrawSetShadow(playerid, textDrawTimer[1][playerid], 0);
    PlayerTextDrawAlignment(playerid, textDrawTimer[1][playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, textDrawTimer[1][playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, textDrawTimer[1][playerid], 255);
    PlayerTextDrawBoxColor(playerid, textDrawTimer[1][playerid], 50);
    PlayerTextDrawUseBox(playerid, textDrawTimer[1][playerid], false);
    PlayerTextDrawSetProportional(playerid, textDrawTimer[1][playerid], true);
    PlayerTextDrawSetSelectable(playerid, textDrawTimer[1][playerid], false);

    textDrawTimer[2][playerid] = CreatePlayerTextDraw(playerid, 319.000000, 371.000000, "CADEIA ADMIN");
    PlayerTextDrawFont(playerid, textDrawTimer[2][playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawLetterSize(playerid, textDrawTimer[2][playerid], 0.120833, 1.100000);
    PlayerTextDrawTextSize(playerid, textDrawTimer[2][playerid], 400.000000, 167.000000);
    PlayerTextDrawSetOutline(playerid, textDrawTimer[2][playerid], 0);
    PlayerTextDrawSetShadow(playerid, textDrawTimer[2][playerid], 0);
    PlayerTextDrawAlignment(playerid, textDrawTimer[2][playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, textDrawTimer[2][playerid], -764862721);
    PlayerTextDrawBackgroundColor(playerid, textDrawTimer[2][playerid], 255);
    PlayerTextDrawBoxColor(playerid, textDrawTimer[2][playerid], -764862926);
    PlayerTextDrawUseBox(playerid, textDrawTimer[2][playerid], false);
    PlayerTextDrawSetProportional(playerid, textDrawTimer[2][playerid], true);
    PlayerTextDrawSetSelectable(playerid, textDrawTimer[2][playerid], false);
}

CALLBACK:HidePlayerTimer(playerid) {
    for(new i = 0; i < 3; i++) {
	    PlayerTextDrawHide(playerid, textDrawTimer[i][playerid]);
    }
}

CALLBACK:ShowPlayerTimer(playerid, const title[], const body[], remainingTime) {
    new fullBody[64];
    format(fullBody, sizeof(fullBody), "%s~n~~r~~h~~h~~h~%s", body, ConvertTime(remainingTime));
    PlayerTextDrawSetString(playerid, textDrawTimer[1][playerid], fullBody);
    PlayerTextDrawSetString(playerid, textDrawTimer[2][playerid], title);

    for(new i = 0; i < 3; i++) {
	    PlayerTextDrawShow(playerid, textDrawTimer[i][playerid]);
    }
}

