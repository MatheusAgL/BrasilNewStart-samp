new Text:serverTradeText[7];
new PlayerText:playerTradeText[MAX_PLAYERS][19];

stock CreateServerTradeTextdraws()
{
	serverTradeText[0] = TextDrawCreate(160.000000, 150.000000, "usebox");
	TextDrawBackgroundColor(serverTradeText[0], 0);
	TextDrawFont(serverTradeText[0], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(serverTradeText[0], 0.500000, 28.000000);
	TextDrawColor(serverTradeText[0], 0);
	TextDrawSetOutline(serverTradeText[0], 0);
	TextDrawSetProportional(serverTradeText[0], true);
	TextDrawSetShadow(serverTradeText[0], 1);
	TextDrawUseBox(serverTradeText[0], true);
	TextDrawBoxColor(serverTradeText[0], 168430280);
	TextDrawTextSize(serverTradeText[0], 472.000000, 5.000000);
	TextDrawSetSelectable(serverTradeText[0], false);

	serverTradeText[1] = TextDrawCreate(163.000000, 169.000000, "usebox");
	TextDrawBackgroundColor(serverTradeText[1], 0);
	TextDrawFont(serverTradeText[1], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(serverTradeText[1], 0.500000, 20.200000);
	TextDrawColor(serverTradeText[1], 0);
	TextDrawSetOutline(serverTradeText[1], 0);
	TextDrawSetProportional(serverTradeText[1], true);
	TextDrawSetShadow(serverTradeText[1], 1);
	TextDrawUseBox(serverTradeText[1], true);
	TextDrawBoxColor(serverTradeText[1], 505290495);
	TextDrawTextSize(serverTradeText[1], 311.000000, 5.000000);
	TextDrawSetSelectable(serverTradeText[1], false);

	serverTradeText[2] = TextDrawCreate(323.000000, 169.000000, "usebox");
	TextDrawBackgroundColor(serverTradeText[2], 0);
	TextDrawFont(serverTradeText[2], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(serverTradeText[2], 0.500000, 20.200000);
	TextDrawColor(serverTradeText[2], 0);
	TextDrawSetOutline(serverTradeText[2], 0);
	TextDrawSetProportional(serverTradeText[2], true);
	TextDrawSetShadow(serverTradeText[2], 1);
	TextDrawUseBox(serverTradeText[2], true);
	TextDrawBoxColor(serverTradeText[2], 505290495);
	TextDrawTextSize(serverTradeText[2], 470.000000, 5.000000);
	TextDrawSetSelectable(serverTradeText[2], false);

	serverTradeText[3] = TextDrawCreate(163.000000, 357.000000, "+adicionar");
	TextDrawBackgroundColor(serverTradeText[3], 0);
	TextDrawFont(serverTradeText[3], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(serverTradeText[3], 0.180000, 0.899999);
	TextDrawColor(serverTradeText[3], -106);
	TextDrawSetOutline(serverTradeText[3], 0);
	TextDrawSetProportional(serverTradeText[3], true);
	TextDrawSetShadow(serverTradeText[3], 1);
	TextDrawUseBox(serverTradeText[3], true);
	TextDrawBoxColor(serverTradeText[3], 505290495);
	TextDrawTextSize(serverTradeText[3], 194.000000, 10.000000);
	TextDrawSetSelectable(serverTradeText[3], true);

	serverTradeText[4] = TextDrawCreate(199.000000, 357.000000, "resetar");
	TextDrawBackgroundColor(serverTradeText[4], 0);
	TextDrawFont(serverTradeText[4], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(serverTradeText[4], 0.180000, 0.899999);
	TextDrawColor(serverTradeText[4], -106);
	TextDrawSetOutline(serverTradeText[4], 0);
	TextDrawSetProportional(serverTradeText[4], true);
	TextDrawSetShadow(serverTradeText[4], 1);
	TextDrawUseBox(serverTradeText[4], true);
	TextDrawBoxColor(serverTradeText[4], 505290495);
	TextDrawTextSize(serverTradeText[4], 221.000000, 10.000000);
	TextDrawSetSelectable(serverTradeText[4], true);

	serverTradeText[5] = TextDrawCreate(463.000000, 153.000000, "X");
	TextDrawBackgroundColor(serverTradeText[5], 0);
	TextDrawFont(serverTradeText[5], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(serverTradeText[5], 0.219999, 0.899999);
	TextDrawColor(serverTradeText[5], -106);
	TextDrawSetOutline(serverTradeText[5], 0);
	TextDrawSetProportional(serverTradeText[5], true);
	TextDrawSetShadow(serverTradeText[5], 1);
	TextDrawUseBox(serverTradeText[5], true);
	TextDrawBoxColor(serverTradeText[5], 505290495);
	TextDrawTextSize(serverTradeText[5], 469.000000, 10.000000);
	TextDrawSetSelectable(serverTradeText[5], true);

	serverTradeText[6] = TextDrawCreate(226.000000, 357.000000, "ajustar custo");
	TextDrawBackgroundColor(serverTradeText[6], 0);
	TextDrawFont(serverTradeText[6], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(serverTradeText[6], 0.180000, 0.899999);
	TextDrawColor(serverTradeText[6], -106);
	TextDrawSetOutline(serverTradeText[6], 0);
	TextDrawSetProportional(serverTradeText[6], true);
	TextDrawSetShadow(serverTradeText[6], 1);
	TextDrawUseBox(serverTradeText[6], true);
	TextDrawBoxColor(serverTradeText[6], 505290495);
	TextDrawTextSize(serverTradeText[6], 264.000000, 10.000000);
	TextDrawSetSelectable(serverTradeText[6], true);
}