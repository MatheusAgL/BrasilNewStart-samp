// Layout do velocimetro em (textdraws);
#include <YSI_Coding\y_hooks>

// Textdraws variáveis
new Text:textSpeedometer[2][6],
	PlayerText:playerTextSpeedometer[5][MAX_PLAYERS];

// Função:
stock CreateVelocity() {
	for(new i = 0; i < 2; i++) {
		new Float:sumPosX = i == 0 ? 92.000 : -10.000,
			Float:sumPosY = i == 0 ? -5.000 : 0.000;

		textSpeedometer[i][0] = TextDrawCreate(465.000000 + sumPosX, 380.000000 + sumPosY, "_");
		TextDrawFont(textSpeedometer[i][0], TEXT_DRAW_FONT_1);
		TextDrawLetterSize(textSpeedometer[i][0], 0.550000, 5.300006);
		TextDrawTextSize(textSpeedometer[i][0], 298.500000, 100.000000);
		TextDrawSetOutline(textSpeedometer[i][0], 1);
		TextDrawSetShadow(textSpeedometer[i][0], 0);
		TextDrawAlignment(textSpeedometer[i][0], TEXT_DRAW_ALIGN_CENTER);
		TextDrawColor(textSpeedometer[i][0], -1);
		TextDrawBackgroundColor(textSpeedometer[i][0], 255);
		TextDrawBoxColor(textSpeedometer[i][0], 105);
		TextDrawUseBox(textSpeedometer[i][0], true);
		TextDrawSetProportional(textSpeedometer[i][0], true);
		TextDrawSetSelectable(textSpeedometer[i][0], false);

		textSpeedometer[i][1] = TextDrawCreate(445.000000 + sumPosX, 404.000000 + sumPosY, "KM/H");
		TextDrawFont(textSpeedometer[i][1], TEXT_DRAW_FONT_1);
		TextDrawLetterSize(textSpeedometer[i][1], 0.133331, 0.900000);
		TextDrawTextSize(textSpeedometer[i][1], 400.000000, 83.500000);
		TextDrawSetOutline(textSpeedometer[i][1], 0);
		TextDrawSetShadow(textSpeedometer[i][1], 0);
		TextDrawAlignment(textSpeedometer[i][1], TEXT_DRAW_ALIGN_CENTER);
		TextDrawColor(textSpeedometer[i][1], -98);
		TextDrawBackgroundColor(textSpeedometer[i][1], 255);
		TextDrawBoxColor(textSpeedometer[i][1], 125);
		TextDrawUseBox(textSpeedometer[i][1], false);
		TextDrawSetProportional(textSpeedometer[i][1], true);
		TextDrawSetSelectable(textSpeedometer[i][1], false);

		textSpeedometer[i][2] = TextDrawCreate(421.000000 + sumPosX, 416.000000 + sumPosY, "_");
		TextDrawFont(textSpeedometer[i][2], TEXT_DRAW_FONT_1);
		TextDrawLetterSize(textSpeedometer[i][2], 0.150000, 0.200001);
		TextDrawTextSize(textSpeedometer[i][2], 469.000000 + sumPosX, 29.500000);
		TextDrawSetOutline(textSpeedometer[i][2], 1);
		TextDrawSetShadow(textSpeedometer[i][2], 0);
		TextDrawAlignment(textSpeedometer[i][2], TEXT_DRAW_ALIGN_LEFT);
		TextDrawColor(textSpeedometer[i][2], -1);
		TextDrawBackgroundColor(textSpeedometer[i][2], 255);
		TextDrawBoxColor(textSpeedometer[i][2], 1296911832);
		TextDrawUseBox(textSpeedometer[i][2], true);
		TextDrawSetProportional(textSpeedometer[i][2], true);
		TextDrawSetSelectable(textSpeedometer[i][2], false);

		textSpeedometer[i][3] = TextDrawCreate(417.000000 + sumPosX, 413.000000 + sumPosY, "~r~~h~~h~E");
		TextDrawFont(textSpeedometer[i][3], TEXT_DRAW_FONT_1);
		TextDrawLetterSize(textSpeedometer[i][3], 0.133331, 0.750000);
		TextDrawTextSize(textSpeedometer[i][3], 400.000000, 83.500000);
		TextDrawSetOutline(textSpeedometer[i][3], 0);
		TextDrawSetShadow(textSpeedometer[i][3], 0);
		TextDrawAlignment(textSpeedometer[i][3], TEXT_DRAW_ALIGN_CENTER);
		TextDrawColor(textSpeedometer[i][3], -76);
		TextDrawBackgroundColor(textSpeedometer[i][3], 255);
		TextDrawBoxColor(textSpeedometer[i][3], 125);
		TextDrawUseBox(textSpeedometer[i][3], false);
		TextDrawSetProportional(textSpeedometer[i][3], true);
		TextDrawSetSelectable(textSpeedometer[i][3], false);

		textSpeedometer[i][4] = TextDrawCreate(445.000000 + sumPosX, 421.000000 + sumPosY, "GASOLINA");
		TextDrawFont(textSpeedometer[i][4], TEXT_DRAW_FONT_2);
		TextDrawLetterSize(textSpeedometer[i][4], 0.104165, 0.750000);
		TextDrawTextSize(textSpeedometer[i][4], 400.000000, 83.500000);
		TextDrawSetOutline(textSpeedometer[i][4], 0);
		TextDrawSetShadow(textSpeedometer[i][4], 0);
		TextDrawAlignment(textSpeedometer[i][4], TEXT_DRAW_ALIGN_CENTER);
		TextDrawColor(textSpeedometer[i][4], -158);
		TextDrawBackgroundColor(textSpeedometer[i][4], 255);
		TextDrawBoxColor(textSpeedometer[i][4], 125);
		TextDrawUseBox(textSpeedometer[i][4], false);
		TextDrawSetProportional(textSpeedometer[i][4], true);
		TextDrawSetSelectable(textSpeedometer[i][4], false);

		textSpeedometer[i][5] = TextDrawCreate(472.000000 + sumPosX, 413.000000 + sumPosY, "F");
		TextDrawFont(textSpeedometer[i][5], TEXT_DRAW_FONT_1);
		TextDrawLetterSize(textSpeedometer[i][5], 0.133331, 0.750000);
		TextDrawTextSize(textSpeedometer[i][5], 400.000000, 83.500000);
		TextDrawSetOutline(textSpeedometer[i][5], 0);
		TextDrawSetShadow(textSpeedometer[i][5], 0);
		TextDrawAlignment(textSpeedometer[i][5], TEXT_DRAW_ALIGN_CENTER);
		TextDrawColor(textSpeedometer[i][5], -76);
		TextDrawBackgroundColor(textSpeedometer[i][5], 255);
		TextDrawBoxColor(textSpeedometer[i][5], 125);
		TextDrawUseBox(textSpeedometer[i][5], false);
		TextDrawSetProportional(textSpeedometer[i][5], true);
		TextDrawSetSelectable(textSpeedometer[i][5], false);
	}
}

hook CreateDynamicTextDraws(playerid) {
	new Float:sumPosX = IsPCPlayer(playerid) ? 92.000 : -10.0000,
		Float:sumPosY = IsPCPlayer(playerid) ? -5.000 : 0.000;

	playerTextSpeedometer[0][playerid] = CreatePlayerTextDraw(playerid, 445.000000 + sumPosX, 380.000000 + sumPosY, "TAXI");
	PlayerTextDrawFont(playerid, playerTextSpeedometer[0][playerid], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, playerTextSpeedometer[0][playerid], 0.133331, 0.900000);
	PlayerTextDrawTextSize(playerid, playerTextSpeedometer[0][playerid], 400.000000, 83.500000);
	PlayerTextDrawSetOutline(playerid, playerTextSpeedometer[0][playerid], 0);
	PlayerTextDrawSetShadow(playerid, playerTextSpeedometer[0][playerid], 0);
	PlayerTextDrawAlignment(playerid, playerTextSpeedometer[0][playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, playerTextSpeedometer[0][playerid], -158);
	PlayerTextDrawBackgroundColor(playerid, playerTextSpeedometer[0][playerid], 255);
	PlayerTextDrawBoxColor(playerid, playerTextSpeedometer[0][playerid], 125);
	PlayerTextDrawUseBox(playerid, playerTextSpeedometer[0][playerid], false);
	PlayerTextDrawSetProportional(playerid, playerTextSpeedometer[0][playerid], true);
	PlayerTextDrawSetSelectable(playerid, playerTextSpeedometer[0][playerid], false);

	playerTextSpeedometer[1][playerid] = CreatePlayerTextDraw(playerid, 445.000000 + sumPosX, 390.000000 + sumPosY, "00");
	PlayerTextDrawFont(playerid, playerTextSpeedometer[1][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, playerTextSpeedometer[1][playerid], 0.333333, 1.500000);
	PlayerTextDrawTextSize(playerid, playerTextSpeedometer[1][playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, playerTextSpeedometer[1][playerid], 0);
	PlayerTextDrawSetShadow(playerid, playerTextSpeedometer[1][playerid], 0);
	PlayerTextDrawAlignment(playerid, playerTextSpeedometer[1][playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, playerTextSpeedometer[1][playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, playerTextSpeedometer[1][playerid], 255);
	PlayerTextDrawBoxColor(playerid, playerTextSpeedometer[1][playerid], 50);
	PlayerTextDrawUseBox(playerid, playerTextSpeedometer[1][playerid], false);
	PlayerTextDrawSetProportional(playerid, playerTextSpeedometer[1][playerid], true);
	PlayerTextDrawSetSelectable(playerid, playerTextSpeedometer[1][playerid], false);

	playerTextSpeedometer[2][playerid] = CreatePlayerTextDraw(playerid, 421.000000 + sumPosX, 416.000000 + sumPosY, "_");
	PlayerTextDrawFont(playerid, playerTextSpeedometer[2][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, playerTextSpeedometer[2][playerid], 0.150000, 0.200001);
	PlayerTextDrawTextSize(playerid, playerTextSpeedometer[2][playerid], 418.500000 + sumPosX, 29.500000);
	PlayerTextDrawSetOutline(playerid, playerTextSpeedometer[2][playerid], 1);
	PlayerTextDrawSetShadow(playerid, playerTextSpeedometer[2][playerid], 0);
	PlayerTextDrawAlignment(playerid, playerTextSpeedometer[2][playerid], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, playerTextSpeedometer[2][playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, playerTextSpeedometer[2][playerid], 255);
	PlayerTextDrawBoxColor(playerid, playerTextSpeedometer[2][playerid], -40);
	PlayerTextDrawUseBox(playerid, playerTextSpeedometer[2][playerid], true);
	PlayerTextDrawSetProportional(playerid, playerTextSpeedometer[2][playerid], true);
	PlayerTextDrawSetSelectable(playerid, playerTextSpeedometer[2][playerid], false);

	playerTextSpeedometer[3][playerid] = CreatePlayerTextDraw(playerid, 474.000000 + sumPosX, 372.000000 + sumPosY, "Preview_Model");
	PlayerTextDrawFont(playerid, playerTextSpeedometer[3][playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawLetterSize(playerid, playerTextSpeedometer[3][playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, playerTextSpeedometer[3][playerid], 46.000000, 66.000000);
	PlayerTextDrawSetOutline(playerid, playerTextSpeedometer[3][playerid], 0);
	PlayerTextDrawSetShadow(playerid, playerTextSpeedometer[3][playerid], 0);
	PlayerTextDrawAlignment(playerid, playerTextSpeedometer[3][playerid], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, playerTextSpeedometer[3][playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, playerTextSpeedometer[3][playerid], 0);
	PlayerTextDrawBoxColor(playerid, playerTextSpeedometer[3][playerid], 255);
	PlayerTextDrawUseBox(playerid, playerTextSpeedometer[3][playerid], false);
	PlayerTextDrawSetProportional(playerid, playerTextSpeedometer[3][playerid], true);
	PlayerTextDrawSetSelectable(playerid, playerTextSpeedometer[3][playerid], false);
	PlayerTextDrawSetPreviewModel(playerid, playerTextSpeedometer[3][playerid], 560);
	PlayerTextDrawSetPreviewRot(playerid, playerTextSpeedometer[3][playerid], -18.000000, 0.000000, -38.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, playerTextSpeedometer[3][playerid], 1, 1);

	playerTextSpeedometer[4][playerid] = CreatePlayerTextDraw(playerid, 498.000000 + sumPosX, 380.000000 + sumPosY, "100%");
	PlayerTextDrawFont(playerid, playerTextSpeedometer[4][playerid], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, playerTextSpeedometer[4][playerid], 0.133331, 0.900000);
	PlayerTextDrawTextSize(playerid, playerTextSpeedometer[4][playerid], 400.000000, 83.500000);
	PlayerTextDrawSetOutline(playerid, playerTextSpeedometer[4][playerid], 0);
	PlayerTextDrawSetShadow(playerid, playerTextSpeedometer[4][playerid], 0);
	PlayerTextDrawAlignment(playerid, playerTextSpeedometer[4][playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, playerTextSpeedometer[4][playerid], -76);
	PlayerTextDrawBackgroundColor(playerid, playerTextSpeedometer[4][playerid], 255);
	PlayerTextDrawBoxColor(playerid, playerTextSpeedometer[4][playerid], 125);
	PlayerTextDrawUseBox(playerid, playerTextSpeedometer[4][playerid], false);
	PlayerTextDrawSetProportional(playerid, playerTextSpeedometer[4][playerid], true);
	PlayerTextDrawSetSelectable(playerid, playerTextSpeedometer[4][playerid], false);
}