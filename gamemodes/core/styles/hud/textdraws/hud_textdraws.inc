#include <YSI_Coding\y_hooks>

stock HUD_TextDrawCreates() 
{
    _hud_textdraws[0] = TextDrawCreate(320.000, 437.000, "_");
    TextDrawLetterSize(_hud_textdraws[0], 0.300, 1.199);
    TextDrawTextSize(_hud_textdraws[0], 0.000, 639.000);
    TextDrawAlignment(_hud_textdraws[0], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(_hud_textdraws[0], -1);
    TextDrawUseBox(_hud_textdraws[0], true);
    TextDrawBoxColor(_hud_textdraws[0], 200);
    TextDrawSetShadow(_hud_textdraws[0], 1);
    TextDrawSetOutline(_hud_textdraws[0], 1);
    TextDrawBackgroundColor(_hud_textdraws[0], 421097727);
    TextDrawFont(_hud_textdraws[0], TEXT_DRAW_FONT_1);
    TextDrawSetProportional(_hud_textdraws[0], true);

    #if SERVER_ID == 1 || SERVER_ID == 2
        #if SERVER_PASCOA
            _hud_pascoa_textdraws[0] = TextDrawCreate(17.000, 407.000, "_");
            TextDrawTextSize(_hud_pascoa_textdraws[0], 29.000, 24.000);
            TextDrawAlignment(_hud_pascoa_textdraws[0], TEXT_DRAW_ALIGN_LEFT);
            TextDrawColor(_hud_pascoa_textdraws[0], -1);
            TextDrawSetShadow(_hud_pascoa_textdraws[0], 0);
            TextDrawSetOutline(_hud_pascoa_textdraws[0], 0);
            TextDrawBackgroundColor(_hud_pascoa_textdraws[0], 0);
            TextDrawFont(_hud_pascoa_textdraws[0], TEXT_DRAW_FONT_MODEL_PREVIEW);
            TextDrawSetProportional(_hud_pascoa_textdraws[0], false);
            TextDrawSetPreviewModel(_hud_pascoa_textdraws[0], 322);
            TextDrawSetPreviewRot(_hud_pascoa_textdraws[0], -32.000, 0.000, 0.000, 0.599);
            TextDrawSetPreviewVehCol(_hud_pascoa_textdraws[0], 0, 0);

            _hud_pascoa_textdraws[1] = TextDrawCreate(19.000, 411.000, "_");
            TextDrawTextSize(_hud_pascoa_textdraws[1], 33.000, 16.000);
            TextDrawAlignment(_hud_pascoa_textdraws[1], TEXT_DRAW_ALIGN_LEFT);
            TextDrawColor(_hud_pascoa_textdraws[1], -1);
            TextDrawSetShadow(_hud_pascoa_textdraws[1], 0);
            TextDrawSetOutline(_hud_pascoa_textdraws[1], 0);
            TextDrawBackgroundColor(_hud_pascoa_textdraws[1], 0);
            TextDrawFont(_hud_pascoa_textdraws[1], TEXT_DRAW_FONT_MODEL_PREVIEW);
            TextDrawSetProportional(_hud_pascoa_textdraws[1], false);
            TextDrawSetPreviewModel(_hud_pascoa_textdraws[1], 322);
            TextDrawSetPreviewRot(_hud_pascoa_textdraws[1], 0.000, 0.000, 0.000, 0.599);
            TextDrawSetPreviewVehCol(_hud_pascoa_textdraws[1], 0, 0);

            _hud_pascoa_textdraws[2] = TextDrawCreate(32.000, 418.000, "_");
            TextDrawTextSize(_hud_pascoa_textdraws[2], 11.000, 15.000);
            TextDrawAlignment(_hud_pascoa_textdraws[2], TEXT_DRAW_ALIGN_LEFT);
            TextDrawColor(_hud_pascoa_textdraws[2], -1);
            TextDrawSetShadow(_hud_pascoa_textdraws[2], 0);
            TextDrawSetOutline(_hud_pascoa_textdraws[2], 0);
            TextDrawBackgroundColor(_hud_pascoa_textdraws[2], 0);
            TextDrawFont(_hud_pascoa_textdraws[2], TEXT_DRAW_FONT_MODEL_PREVIEW);
            TextDrawSetProportional(_hud_pascoa_textdraws[2], false);
            TextDrawSetPreviewModel(_hud_pascoa_textdraws[2], 19343);
            TextDrawSetPreviewRot(_hud_pascoa_textdraws[2], -32.000, 0.000, 0.000, 0.599);
            TextDrawSetPreviewVehCol(_hud_pascoa_textdraws[2], 0, 0);
        #endif

        _hud_textdraws[1] = TextDrawCreate(9.000, 418.000, SERVER_TAG);
        TextDrawLetterSize(_hud_textdraws[1], 0.379, 1.598);
        TextDrawAlignment(_hud_textdraws[1], TEXT_DRAW_ALIGN_LEFT);
        #if SERVER_PASCOA
            TextDrawColor(_hud_textdraws[1], -1863413505);
        #else
            TextDrawColor(_hud_textdraws[1], -1);
        #endif
        TextDrawSetShadow(_hud_textdraws[1], 0);
        TextDrawSetOutline(_hud_textdraws[1], 1);
        TextDrawBackgroundColor(_hud_textdraws[1], 255);
        TextDrawFont(_hud_textdraws[1], TEXT_DRAW_FONT_3);
        TextDrawSetProportional(_hud_textdraws[1], true);


        _hud_textdraws[2] = TextDrawCreate(39.000, 411.000, "_");
    #else
        _hud_textdraws[1] = TextDrawCreate(3.000, 413.000, SERVER_FIRST_NAME);
        TextDrawLetterSize(_hud_textdraws[1], 0.379, 1.598);
        TextDrawAlignment(_hud_textdraws[1], TEXT_DRAW_ALIGN_LEFT);
        TextDrawColor(_hud_textdraws[1], HUD_COLOR_PRIMARY);
        TextDrawSetShadow(_hud_textdraws[1], 0);
        TextDrawSetOutline(_hud_textdraws[1], 1);
        TextDrawBackgroundColor(_hud_textdraws[1], 255);
        TextDrawFont(_hud_textdraws[1], TEXT_DRAW_FONT_3);
        TextDrawSetProportional(_hud_textdraws[1], true);

        _hud_textdraws[2] = TextDrawCreate(51.000, 423.000, SERVER_LAST_NAME);
        TextDrawLetterSize(_hud_textdraws[2], 0.308, 1.098);
        TextDrawAlignment(_hud_textdraws[2], TEXT_DRAW_ALIGN_RIGHT);
        TextDrawColor(_hud_textdraws[2], HUD_COLOR_SECONDARY);
        TextDrawSetShadow(_hud_textdraws[2], 0);
        TextDrawSetOutline(_hud_textdraws[2], 1);
        TextDrawBackgroundColor(_hud_textdraws[2], 255);
        TextDrawFont(_hud_textdraws[2], TEXT_DRAW_FONT_0);
        TextDrawSetProportional(_hud_textdraws[2], true);
    #endif

    _hud_textdraws[3] = TextDrawCreate(44.000, 438.000, SERVER_SITE);
    TextDrawLetterSize(_hud_textdraws[3], 0.119, 0.799);
    TextDrawAlignment(_hud_textdraws[3], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(_hud_textdraws[3], 1768516095);
    TextDrawSetShadow(_hud_textdraws[3], 0);
    TextDrawSetOutline(_hud_textdraws[3], 0);
    TextDrawBackgroundColor(_hud_textdraws[3], 255);
    TextDrawFont(_hud_textdraws[3], TEXT_DRAW_FONT_2);
    TextDrawSetProportional(_hud_textdraws[3], true);

    _hud_textdraws[4] = TextDrawCreate(558.000, 435.000, "LD_SPAC:thrustG");
    TextDrawTextSize(_hud_textdraws[4], 117.000, 17.000);
    TextDrawAlignment(_hud_textdraws[4], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_hud_textdraws[4], 354188870);
    TextDrawSetShadow(_hud_textdraws[4], 0);
    TextDrawSetOutline(_hud_textdraws[4], 0);
    TextDrawBackgroundColor(_hud_textdraws[4], 255);
    TextDrawFont(_hud_textdraws[4], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawSetProportional(_hud_textdraws[4], true);

    _salary_textdraw[0] = TextDrawCreate(202.000, 437.000, "_");
    TextDrawLetterSize(_salary_textdraw[0], 0.300, 1.098);
    TextDrawTextSize(_salary_textdraw[0], 257.000, -10.000);
    TextDrawAlignment(_salary_textdraw[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_salary_textdraw[0], -1);
    TextDrawUseBox(_salary_textdraw[0], true);
    TextDrawBoxColor(_salary_textdraw[0], 7766);
    TextDrawSetShadow(_salary_textdraw[0], 1);
    TextDrawSetOutline(_salary_textdraw[0], 1);
    TextDrawBackgroundColor(_salary_textdraw[0], 150);
    TextDrawFont(_salary_textdraw[0], TEXT_DRAW_FONT_1);
    TextDrawSetProportional(_salary_textdraw[0], true);

    _salary_textdraw[1] = TextDrawCreate(232.000, 437.000, "Salario:");
    TextDrawLetterSize(_salary_textdraw[1], 0.128, 0.898);
    TextDrawAlignment(_salary_textdraw[1], TEXT_DRAW_ALIGN_RIGHT);
    TextDrawColor(_salary_textdraw[1], -82);
    TextDrawSetShadow(_salary_textdraw[1], 1);
    TextDrawSetOutline(_salary_textdraw[1], 0);
    TextDrawBackgroundColor(_salary_textdraw[1], 150);
    TextDrawFont(_salary_textdraw[1], TEXT_DRAW_FONT_2);
    TextDrawSetProportional(_salary_textdraw[1], true);

    _cash_textdraw = TextDrawCreate(436.000, 437.000, "C$");
    TextDrawLetterSize(_cash_textdraw, 0.128, 0.898);
    TextDrawAlignment(_cash_textdraw, TEXT_DRAW_ALIGN_RIGHT);
    TextDrawColor(_cash_textdraw, 1182971135);
    TextDrawSetShadow(_cash_textdraw, 0);
    TextDrawSetOutline(_cash_textdraw, 0);
    TextDrawBackgroundColor(_cash_textdraw, 793726975);
    TextDrawFont(_cash_textdraw, TEXT_DRAW_FONT_2);
    TextDrawSetProportional(_cash_textdraw, true);

    _email_alert_textdraw[0] = TextDrawCreate(263.000, 440.000, "_");
    TextDrawLetterSize(_email_alert_textdraw[0], 0.549, 0.398);
    TextDrawTextSize(_email_alert_textdraw[0], 271.000, -29.000);
    TextDrawAlignment(_email_alert_textdraw[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_email_alert_textdraw[0], -1);
    TextDrawUseBox(_email_alert_textdraw[0], true);
    TextDrawBoxColor(_email_alert_textdraw[0], -1);
    TextDrawSetShadow(_email_alert_textdraw[0], 1);
    TextDrawSetOutline(_email_alert_textdraw[0], 1);
    TextDrawBackgroundColor(_email_alert_textdraw[0], 150);
    TextDrawFont(_email_alert_textdraw[0], TEXT_DRAW_FONT_1);
    TextDrawSetProportional(_email_alert_textdraw[0], true);

    _email_alert_textdraw[1] = TextDrawCreate(265.000, 437.000, "/");
    TextDrawLetterSize(_email_alert_textdraw[1], 0.479, 0.799);
    TextDrawTextSize(_email_alert_textdraw[1], 19.000, -8.000);
    TextDrawAlignment(_email_alert_textdraw[1], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_email_alert_textdraw[1], 130);
    TextDrawSetShadow(_email_alert_textdraw[1], 0);
    TextDrawSetOutline(_email_alert_textdraw[1], 0);
    TextDrawBackgroundColor(_email_alert_textdraw[1], 150);
    TextDrawFont(_email_alert_textdraw[1], TEXT_DRAW_FONT_2);
    TextDrawSetProportional(_email_alert_textdraw[1], true);

    _email_alert_textdraw[2] = TextDrawCreate(273.000, 441.000, "/");
    TextDrawLetterSize(_email_alert_textdraw[2], -0.360, 0.498);
    TextDrawTextSize(_email_alert_textdraw[2], 19.000, -8.000);
    TextDrawAlignment(_email_alert_textdraw[2], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_email_alert_textdraw[2], 130);
    TextDrawSetShadow(_email_alert_textdraw[2], 0);
    TextDrawSetOutline(_email_alert_textdraw[2], 0);
    TextDrawBackgroundColor(_email_alert_textdraw[2], 150);
    TextDrawFont(_email_alert_textdraw[2], TEXT_DRAW_FONT_2);
    TextDrawSetProportional(_email_alert_textdraw[2], true);

    _email_alert_textdraw[3] = TextDrawCreate(269.000, 437.000, "/");
    TextDrawLetterSize(_email_alert_textdraw[3], -0.530, 0.799);
    TextDrawTextSize(_email_alert_textdraw[3], 19.000, -8.000);
    TextDrawAlignment(_email_alert_textdraw[3], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_email_alert_textdraw[3], 130);
    TextDrawSetShadow(_email_alert_textdraw[3], 0);
    TextDrawSetOutline(_email_alert_textdraw[3], 0);
    TextDrawBackgroundColor(_email_alert_textdraw[3], 150);
    TextDrawFont(_email_alert_textdraw[3], TEXT_DRAW_FONT_2);
    TextDrawSetProportional(_email_alert_textdraw[3], true);

    _email_alert_textdraw[4] = TextDrawCreate(260.000, 441.000, "/");
    TextDrawLetterSize(_email_alert_textdraw[4], 0.398, 0.598);
    TextDrawTextSize(_email_alert_textdraw[4], 19.000, -8.000);
    TextDrawAlignment(_email_alert_textdraw[4], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_email_alert_textdraw[4], 130);
    TextDrawSetShadow(_email_alert_textdraw[4], 0);
    TextDrawSetOutline(_email_alert_textdraw[4], 0);
    TextDrawBackgroundColor(_email_alert_textdraw[4], 150);
    TextDrawFont(_email_alert_textdraw[4], TEXT_DRAW_FONT_2);
    TextDrawSetProportional(_email_alert_textdraw[4], true);

    _email_alert_textdraw[5] = TextDrawCreate(269.000, 435.000, "LD_BEAT:chit");
    TextDrawTextSize(_email_alert_textdraw[5], 8.000, 8.000);
    TextDrawAlignment(_email_alert_textdraw[5], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_email_alert_textdraw[5], -16776961);
    TextDrawSetShadow(_email_alert_textdraw[5], 0);
    TextDrawSetOutline(_email_alert_textdraw[5], 0);
    TextDrawBackgroundColor(_email_alert_textdraw[5], 255);
    TextDrawFont(_email_alert_textdraw[5], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawSetProportional(_email_alert_textdraw[5], true);

    _clock_textdraw = TextDrawCreate(571.000, 437.000, "4 Set 1999");
    TextDrawLetterSize(_clock_textdraw, 0.128, 0.898);
    TextDrawAlignment(_clock_textdraw, TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_clock_textdraw, -91);
    TextDrawSetShadow(_clock_textdraw, 1);
    TextDrawSetOutline(_clock_textdraw, 0);
    TextDrawBackgroundColor(_clock_textdraw, 150);
    TextDrawFont(_clock_textdraw, TEXT_DRAW_FONT_2);
    TextDrawSetProportional(_clock_textdraw, true);

    _needs_textdraw[0] = TextDrawCreate(538.000, 437.000, "HUD:radar_burgerShot");
    TextDrawTextSize(_needs_textdraw[0], 10.000, 9.000);
    TextDrawAlignment(_needs_textdraw[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_needs_textdraw[0], -106);
    TextDrawSetShadow(_needs_textdraw[0], 0);
    TextDrawSetOutline(_needs_textdraw[0], 0);
    TextDrawBackgroundColor(_needs_textdraw[0], 255);
    TextDrawFont(_needs_textdraw[0], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawSetProportional(_needs_textdraw[0], true);

    _needs_textdraw[1] = TextDrawCreate(551.000, 437.000, "HUD:radar_dateDrink");
    TextDrawTextSize(_needs_textdraw[1], 10.000, 9.000);
    TextDrawAlignment(_needs_textdraw[1], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(_needs_textdraw[1], -106);
    TextDrawSetShadow(_needs_textdraw[1], 0);
    TextDrawSetOutline(_needs_textdraw[1], 0);
    TextDrawBackgroundColor(_needs_textdraw[1], 255);
    TextDrawFont(_needs_textdraw[1], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawSetProportional(_needs_textdraw[1], true);

    return 1;
}

stock HUD_CreatePlayerTextdraws(playerid)
{
    _needhunger_progress[playerid] = CreatePlayerTextDraw(playerid, 543.000, 450.000, "_");
    PlayerTextDrawLetterSize(playerid, _needhunger_progress[playerid], 0.679, -1.700);
    PlayerTextDrawTextSize(playerid, _needhunger_progress[playerid], 548.000, 10.000);
    PlayerTextDrawAlignment(playerid, _needhunger_progress[playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, _needhunger_progress[playerid], -1);
    PlayerTextDrawUseBox(playerid, _needhunger_progress[playerid], true);
    PlayerTextDrawBoxColor(playerid, _needhunger_progress[playerid], 0xF48B0A30);
    PlayerTextDrawSetShadow(playerid, _needhunger_progress[playerid], 1);
    PlayerTextDrawSetOutline(playerid, _needhunger_progress[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, _needhunger_progress[playerid], 150);
    PlayerTextDrawFont(playerid, _needhunger_progress[playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, _needhunger_progress[playerid], true);

    _needthirst_progress[playerid] = CreatePlayerTextDraw(playerid, 556.000, 450.000, "_");
    PlayerTextDrawLetterSize(playerid, _needthirst_progress[playerid], 0.679, -1.700);
    PlayerTextDrawTextSize(playerid, _needthirst_progress[playerid], 560.000, 10.000);
    PlayerTextDrawAlignment(playerid, _needthirst_progress[playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, _needthirst_progress[playerid], 16777215);
    PlayerTextDrawUseBox(playerid, _needthirst_progress[playerid], true);
    PlayerTextDrawBoxColor(playerid, _needthirst_progress[playerid], 0x1E54DC30);
    PlayerTextDrawSetShadow(playerid, _needthirst_progress[playerid], 1);
    PlayerTextDrawSetOutline(playerid, _needthirst_progress[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, _needthirst_progress[playerid], 150);
    PlayerTextDrawFont(playerid, _needthirst_progress[playerid], TEXT_DRAW_FONT_0);
    PlayerTextDrawSetProportional(playerid, _needthirst_progress[playerid], true);

    _salary_ptextdraw[playerid] = CreatePlayerTextDraw(playerid, 252.000, 437.000, "--:--");
    PlayerTextDrawLetterSize(playerid, _salary_ptextdraw[playerid], 0.159, 0.898);
    PlayerTextDrawAlignment(playerid, _salary_ptextdraw[playerid], TEXT_DRAW_ALIGN_RIGHT);
    PlayerTextDrawColor(playerid, _salary_ptextdraw[playerid], -156);
    PlayerTextDrawSetShadow(playerid, _salary_ptextdraw[playerid], 1);
    PlayerTextDrawSetOutline(playerid, _salary_ptextdraw[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, _salary_ptextdraw[playerid], 150);
    PlayerTextDrawFont(playerid, _salary_ptextdraw[playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, _salary_ptextdraw[playerid], true);

    _cash_ptextdraw[playerid] = CreatePlayerTextDraw(playerid, 437.000, 437.000, "------------");
    PlayerTextDrawLetterSize(playerid, _cash_ptextdraw[playerid], 0.128, 0.898);
    PlayerTextDrawAlignment(playerid, _cash_ptextdraw[playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, _cash_ptextdraw[playerid], -2016478490);
    PlayerTextDrawSetShadow(playerid, _cash_ptextdraw[playerid], 0);
    PlayerTextDrawSetOutline(playerid, _cash_ptextdraw[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, _cash_ptextdraw[playerid], 793726975);
    PlayerTextDrawFont(playerid, _cash_ptextdraw[playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, _cash_ptextdraw[playerid], true);

    _email_alert_ptextd[playerid] = CreatePlayerTextDraw(playerid, 273.000, 436.000, "_");
    PlayerTextDrawLetterSize(playerid, _email_alert_ptextd[playerid], 0.108, 0.598);
    PlayerTextDrawTextSize(playerid, _email_alert_ptextd[playerid], 4.000, 0.000);
    PlayerTextDrawAlignment(playerid, _email_alert_ptextd[playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, _email_alert_ptextd[playerid], -1);
    PlayerTextDrawSetShadow(playerid, _email_alert_ptextd[playerid], 0);
    PlayerTextDrawSetOutline(playerid, _email_alert_ptextd[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, _email_alert_ptextd[playerid], 150);
    PlayerTextDrawFont(playerid, _email_alert_ptextd[playerid], TEXT_DRAW_FONT_3);
    PlayerTextDrawSetProportional(playerid, _email_alert_ptextd[playerid], true);

    _clock_ptextdraw[playerid] = CreatePlayerTextDraw(playerid, 619.000, 437.000, "--:--");
    PlayerTextDrawLetterSize(playerid, _clock_ptextdraw[playerid], 0.159, 0.898);
    PlayerTextDrawAlignment(playerid, _clock_ptextdraw[playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, _clock_ptextdraw[playerid], -156);
    PlayerTextDrawSetShadow(playerid, _clock_ptextdraw[playerid], 1);
    PlayerTextDrawSetOutline(playerid, _clock_ptextdraw[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, _clock_ptextdraw[playerid], 150);
    PlayerTextDrawFont(playerid, _clock_ptextdraw[playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, _clock_ptextdraw[playerid], true);

    // PlayerTextdraw: Pop-up (01)
    popup_textdraw[playerid] = CreatePlayerTextDraw(playerid, 250.634658, 393.429687, "pop-up-01");
    PlayerTextDrawLetterSize(playerid, popup_textdraw[playerid], 0.186331, 0.803851);
    PlayerTextDrawTextSize(playerid, popup_textdraw[playerid], 0.000000, 35.000000);
    PlayerTextDrawAlignment(playerid, popup_textdraw[playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, popup_textdraw[playerid], -112);
    PlayerTextDrawSetShadow(playerid, popup_textdraw[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, popup_textdraw[playerid], 269488144);
    PlayerTextDrawFont(playerid, popup_textdraw[playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, popup_textdraw[playerid], true);

    CallRemoteFunction("CreateStaticTextDraws", "d", playerid);

    return 1;
}

stock HUD_CreateNeedsTextDraws(playerid) 
{
    SetPlayerProgressBarValue(playerid, _needhunger_progress[playerid], floatround(PlayerInfo[playerid][pFome], floatround_ceil));
	// ShowPlayerProgressBar(playerid, _needhunger_progress[playerid]);
	// SetPlayerProgressBarValue(playerid, _needthirst_progress[playerid], floatround(PlayerInfo[playerid][pSede], floatround_ceil));
	// ShowPlayerProgressBar(playerid, _needthirst_progress[playerid]);

    return 1;
}