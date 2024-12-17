/* -----------------------------------------------------------------------------------------------------
-
-   (vehicles/drift/textdraws)
- 	    Módulo das textdraws do servidor
-
-------------------------------------------------------------------------------------------------------- */

// Variáveis
new PlayerText: event_ptextdraw[2][MAX_PLAYERS];
new Text: event_textdraw[9];

// ------------------------------------------------------------------------
stock EVENT_CreatePlayerTextDraw(playerid)
{
	// Textdraws: Evento
	event_ptextdraw[0][playerid] = CreatePlayerTextDraw(playerid, 146.666748, 403.313385, "-");
	PlayerTextDrawLetterSize(playerid, event_ptextdraw[0][playerid], 0.182999, 0.898963);
	PlayerTextDrawTextSize(playerid, event_ptextdraw[0][playerid], 233.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, event_ptextdraw[0][playerid], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, event_ptextdraw[0][playerid], -2139062017);
	PlayerTextDrawUseBox(playerid, event_ptextdraw[0][playerid], true);
	PlayerTextDrawBoxColor(playerid, event_ptextdraw[0][playerid], 255);
	PlayerTextDrawSetShadow(playerid, event_ptextdraw[0][playerid], 0);
	PlayerTextDrawSetOutline(playerid, event_ptextdraw[0][playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, event_ptextdraw[0][playerid], 255);
	PlayerTextDrawFont(playerid, event_ptextdraw[0][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawSetProportional(playerid, event_ptextdraw[0][playerid], true);

	event_ptextdraw[1][playerid] = CreatePlayerTextDraw(playerid, 233.100006, 404.257965, "-");
	PlayerTextDrawLetterSize(playerid, event_ptextdraw[1][playerid], 0.179333, 0.786963);
	PlayerTextDrawAlignment(playerid, event_ptextdraw[1][playerid], TEXT_DRAW_ALIGN_RIGHT);
	PlayerTextDrawColor(playerid, event_ptextdraw[1][playerid], -1);
	PlayerTextDrawSetShadow(playerid, event_ptextdraw[1][playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, event_ptextdraw[1][playerid], 255);
	PlayerTextDrawFont(playerid, event_ptextdraw[1][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawSetProportional(playerid, event_ptextdraw[1][playerid], true);
}

stock EVENT_CreateTextDraw()
{
	// Textdraws: Evento
	event_textdraw[0] = TextDrawCreate(144.666748, 355.926147, "_");
	TextDrawLetterSize(event_textdraw[0], 0.392666, 6.814222);
	TextDrawTextSize(event_textdraw[0], 235.000000, 0.000000);
	TextDrawAlignment(event_textdraw[0], TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(event_textdraw[0], -1);
	TextDrawUseBox(event_textdraw[0], true);
	TextDrawBoxColor(event_textdraw[0], 144);
	TextDrawSetShadow(event_textdraw[0], 0);
	TextDrawBackgroundColor(event_textdraw[0], 255);
	TextDrawFont(event_textdraw[0], TEXT_DRAW_FONT_3);
	TextDrawSetProportional(event_textdraw[0], true);

	event_textdraw[1] = TextDrawCreate(146.666748, 366.711151, "1. -");
	TextDrawLetterSize(event_textdraw[1], 0.182999, 0.898963);
	TextDrawTextSize(event_textdraw[1], 233.000000, 0.000000);
	TextDrawAlignment(event_textdraw[1], TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(event_textdraw[1], -323478273);
	TextDrawUseBox(event_textdraw[1], true);
	TextDrawBoxColor(event_textdraw[1], 255);
	TextDrawSetShadow(event_textdraw[1], 0);
	TextDrawSetOutline(event_textdraw[1], 1);
	TextDrawBackgroundColor(event_textdraw[1], 255);
	TextDrawFont(event_textdraw[1], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(event_textdraw[1], true);

	event_textdraw[2] = TextDrawCreate(146.666748, 378.911895, "2. -");
	TextDrawLetterSize(event_textdraw[2], 0.182999, 0.898963);
	TextDrawTextSize(event_textdraw[2], 233.000000, 0.000000);
	TextDrawAlignment(event_textdraw[2], TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(event_textdraw[2], -1);
	TextDrawUseBox(event_textdraw[2], true);
	TextDrawBoxColor(event_textdraw[2], 255);
	TextDrawSetShadow(event_textdraw[2], 0);
	TextDrawSetOutline(event_textdraw[2], 1);
	TextDrawBackgroundColor(event_textdraw[2], 255);
	TextDrawFont(event_textdraw[2], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(event_textdraw[2], true);

	event_textdraw[3] = TextDrawCreate(146.666748, 391.112640, "3. -");
	TextDrawLetterSize(event_textdraw[3], 0.182999, 0.898963);
	TextDrawTextSize(event_textdraw[3], 233.000000, 0.000000);
	TextDrawAlignment(event_textdraw[3], TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(event_textdraw[3], -1);
	TextDrawUseBox(event_textdraw[3], true);
	TextDrawBoxColor(event_textdraw[3], 255);
	TextDrawSetShadow(event_textdraw[3], 0);
	TextDrawSetOutline(event_textdraw[3], 1);
	TextDrawBackgroundColor(event_textdraw[3], 255);
	TextDrawFont(event_textdraw[3], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(event_textdraw[3], true);

	event_textdraw[4] = TextDrawCreate(233.100006, 367.755737, "-");
	TextDrawLetterSize(event_textdraw[4], 0.179333, 0.786963);
	TextDrawAlignment(event_textdraw[4], TEXT_DRAW_ALIGN_RIGHT);
	TextDrawColor(event_textdraw[4], -1);
	TextDrawSetShadow(event_textdraw[4], 0);
	TextDrawBackgroundColor(event_textdraw[4], 255);
	TextDrawFont(event_textdraw[4], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(event_textdraw[4], true);

	event_textdraw[5] = TextDrawCreate(233.100006, 379.456451, "-");
	TextDrawLetterSize(event_textdraw[5], 0.179333, 0.786963);
	TextDrawAlignment(event_textdraw[5], TEXT_DRAW_ALIGN_RIGHT);
	TextDrawColor(event_textdraw[5], -1);
	TextDrawSetShadow(event_textdraw[5], 0);
	TextDrawBackgroundColor(event_textdraw[5], 255);
	TextDrawFont(event_textdraw[5], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(event_textdraw[5], true);

	event_textdraw[6] = TextDrawCreate(233.100006, 391.257171, "-");
	TextDrawLetterSize(event_textdraw[6], 0.179333, 0.786963);
	TextDrawAlignment(event_textdraw[6], TEXT_DRAW_ALIGN_RIGHT);
	TextDrawColor(event_textdraw[6], -1);
	TextDrawSetShadow(event_textdraw[6], 0);
	TextDrawBackgroundColor(event_textdraw[6], 255);
	TextDrawFont(event_textdraw[6], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(event_textdraw[6], true);

	event_textdraw[7] = TextDrawCreate(198.100036, 356.139526, "00:00");
	TextDrawLetterSize(event_textdraw[7], 0.179333, 0.786963);
	TextDrawAlignment(event_textdraw[7], TEXT_DRAW_ALIGN_RIGHT);
	TextDrawColor(event_textdraw[7], -1378294017);
	TextDrawSetShadow(event_textdraw[7], 0);
	TextDrawBackgroundColor(event_textdraw[7], 255);
	TextDrawFont(event_textdraw[7], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(event_textdraw[7], true);

	event_textdraw[8] = TextDrawCreate(164.433410, 335.813507, "-");
	TextDrawColor(event_textdraw[8], 0xFF0000AA);
	TextDrawLetterSize(event_textdraw[8], 0.326000, 1.757628);
	TextDrawTextSize(event_textdraw[8], 0.000000, 86.000000);
	TextDrawAlignment(event_textdraw[8], TEXT_DRAW_ALIGN_CENTER);
	TextDrawSetShadow(event_textdraw[8], 0);
	TextDrawBackgroundColor(event_textdraw[8], 255);
	TextDrawFont(event_textdraw[8], TEXT_DRAW_FONT_0);
	TextDrawSetProportional(event_textdraw[8], true);
}

stock Text:EVENT_UpdateName(const name[], color=COLOR_SAMP)
{
	// Destruir
	TextDrawDestroy(event_textdraw[8]);

	// Recriar
	event_textdraw[8] = TextDrawCreate(164.433410, 335.813507, name);
	TextDrawColor(event_textdraw[8], color);
	TextDrawLetterSize(event_textdraw[8], 0.326000, 1.757628);
	TextDrawTextSize(event_textdraw[8], 0.000000, 86.000000);
	TextDrawAlignment(event_textdraw[8], TEXT_DRAW_ALIGN_CENTER);
	TextDrawSetShadow(event_textdraw[8], 0);
	TextDrawBackgroundColor(event_textdraw[8], 255);
	TextDrawFont(event_textdraw[8], TEXT_DRAW_FONT_0);
	TextDrawSetProportional(event_textdraw[8], true);
}