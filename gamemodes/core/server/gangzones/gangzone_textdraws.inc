new 
    PlayerText:td_header_gangzone[MAX_PLAYERS],
    PlayerText:td_orgs_gangzone[MAX_PLAYERS],
    PlayerText:td_timer_gangzone[MAX_PLAYERS],
    PlayerText:td_points_gangzone[MAX_PLAYERS],
    PlayerText:td_name_gangzone[MAX_PLAYERS];

stock GangZones_CreateTextdraws(playerid)
{
    td_header_gangzone[playerid] = CreatePlayerTextDraw(playerid, 5.000, 225.000, "ORG                           PONTOS");
    PlayerTextDrawLetterSize(playerid, td_header_gangzone[playerid], 0.140, 0.799);
    PlayerTextDrawTextSize(playerid, td_header_gangzone[playerid], 91.000, 0.000);
    PlayerTextDrawAlignment(playerid, td_header_gangzone[playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, td_header_gangzone[playerid], -1);
    PlayerTextDrawUseBox(playerid, td_header_gangzone[playerid], true);
    PlayerTextDrawBoxColour(playerid, td_header_gangzone[playerid], 80);
    PlayerTextDrawSetShadow(playerid, td_header_gangzone[playerid], 1);
    PlayerTextDrawSetOutline(playerid, td_header_gangzone[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, td_header_gangzone[playerid], 150);
    PlayerTextDrawFont(playerid, td_header_gangzone[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawSetProportional(playerid, td_header_gangzone[playerid], true);

    td_orgs_gangzone[playerid] = CreatePlayerTextDraw(playerid, 5.000, 236.000, "Sons of Anarchy~n~Warlocks~n~Motoqueiros");
    PlayerTextDrawLetterSize(playerid, td_orgs_gangzone[playerid], 0.129, 0.899);
    PlayerTextDrawTextSize(playerid, td_orgs_gangzone[playerid], 60.000, 0.000);
    PlayerTextDrawAlignment(playerid, td_orgs_gangzone[playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, td_orgs_gangzone[playerid], -1);
    PlayerTextDrawSetShadow(playerid, td_orgs_gangzone[playerid], 1);
    PlayerTextDrawSetOutline(playerid, td_orgs_gangzone[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, td_orgs_gangzone[playerid], 150);
    PlayerTextDrawFont(playerid, td_orgs_gangzone[playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, td_orgs_gangzone[playerid], true);

    td_timer_gangzone[playerid] = CreatePlayerTextDraw(playerid, 90.000, 214.000, "TEMPO ~b~~h~00:00");
    PlayerTextDrawLetterSize(playerid, td_timer_gangzone[playerid], 0.140, 0.799);
    PlayerTextDrawAlignment(playerid, td_timer_gangzone[playerid], TEXT_DRAW_ALIGN_RIGHT);
    PlayerTextDrawColor(playerid, td_timer_gangzone[playerid], -1);
    PlayerTextDrawSetShadow(playerid, td_timer_gangzone[playerid], 1);
    PlayerTextDrawSetOutline(playerid, td_timer_gangzone[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, td_timer_gangzone[playerid], 150);
    PlayerTextDrawFont(playerid, td_timer_gangzone[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawSetProportional(playerid, td_timer_gangzone[playerid], true);

    td_points_gangzone[playerid] = CreatePlayerTextDraw(playerid, 90.000, 236.000, "10 ~n~10 ~n~100");
    PlayerTextDrawLetterSize(playerid, td_points_gangzone[playerid], 0.129, 0.899);
    PlayerTextDrawTextSize(playerid, td_points_gangzone[playerid], 60.000, 0.000);
    PlayerTextDrawAlignment(playerid, td_points_gangzone[playerid], TEXT_DRAW_ALIGN_RIGHT);
    PlayerTextDrawColor(playerid, td_points_gangzone[playerid], -1);
    PlayerTextDrawSetShadow(playerid, td_points_gangzone[playerid], 1);
    PlayerTextDrawSetOutline(playerid, td_points_gangzone[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, td_points_gangzone[playerid], 150);
    PlayerTextDrawFont(playerid, td_points_gangzone[playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, td_points_gangzone[playerid], true);

    td_name_gangzone[playerid] = CreatePlayerTextDraw(playerid, 45.000, 180.000, "Bar do Norte");
    PlayerTextDrawLetterSize(playerid, td_name_gangzone[playerid], 0.399, 1.600);
    PlayerTextDrawAlignment(playerid, td_name_gangzone[playerid], TEXT_DRAW_ALIGN_RIGHT);
    PlayerTextDrawColor(playerid, td_name_gangzone[playerid], -1);
    PlayerTextDrawSetShadow(playerid, td_name_gangzone[playerid], 1);
    PlayerTextDrawSetOutline(playerid, td_name_gangzone[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, td_name_gangzone[playerid], 150);
    PlayerTextDrawFont(playerid, td_name_gangzone[playerid], TEXT_DRAW_FONT_0);
    PlayerTextDrawSetProportional(playerid, td_name_gangzone[playerid], true);

    return 1;
}

stock GZ_ShowTextDraws(playerid, area, type, const gz_name[], time)
{
    new string[128];

    format(string, sizeof(string), "%s", gz_name);
    PlayerTextDrawSetString(playerid, td_orgs_gangzone[playerid], string);

    switch (type)
    {
        case GZ_TYPE_MERCENARYZONE:
        {
            format(string, sizeof(string), "%s ~n~%s ~n~%s",
                GetOrgName(25), 
                GetOrgName(28), 
                GetOrgName(33));
            PlayerTextDrawSetString(playerid, td_orgs_gangzone[playerid], string);

            format(string, sizeof(string), "%s ~n~%s ~n~%s",
                getFormatText(MerceZone_GetPoints(area, 25)), 
                getFormatText(MerceZone_GetPoints(area, 28)), 
                getFormatText(MerceZone_GetPoints(area, 33)));
            PlayerTextDrawSetString(playerid, td_points_gangzone[playerid], string);
        }
    }
    format(string, sizeof(string), "TEMPO: ~b~~h~%s", ConvertTempo(time));
    PlayerTextDrawSetString(playerid, td_timer_gangzone[playerid], string);

    PlayerTextDrawShow(playerid, td_header_gangzone[playerid]);
    PlayerTextDrawShow(playerid, td_orgs_gangzone[playerid]);
    PlayerTextDrawShow(playerid, td_timer_gangzone[playerid]);
    PlayerTextDrawShow(playerid, td_points_gangzone[playerid]);
    PlayerTextDrawShow(playerid, td_name_gangzone[playerid]);

    return 1;
}

stock GZ_HideTextDraws(playerid)
{
    PlayerTextDrawHide(playerid, td_header_gangzone[playerid]);
    PlayerTextDrawHide(playerid, td_orgs_gangzone[playerid]);
    PlayerTextDrawHide(playerid, td_timer_gangzone[playerid]);
    PlayerTextDrawHide(playerid, td_points_gangzone[playerid]);
    PlayerTextDrawHide(playerid, td_name_gangzone[playerid]);

    return 1;
}