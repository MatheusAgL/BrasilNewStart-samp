#include <YSI_Coding\y_hooks>

// Variáveis
new Text:orgs_textdraw[12];
new Text:player_orgs_textdraw[24];
new PlayerText:player_orgs_textdraw_page[MAX_PLAYERS];
new page_orgs[MAX_PLAYERS];

stock CreateOrgsTextDraws() {
    orgs_textdraw[0] = TextDrawCreate(150.000000, 133.000000, "_");
    TextDrawFont(orgs_textdraw[0], TEXT_DRAW_FONT_3);
    TextDrawLetterSize(orgs_textdraw[0], 0.683332, 22.649974);
    TextDrawTextSize(orgs_textdraw[0], 482.500000, 23.000000);
    TextDrawSetOutline(orgs_textdraw[0], 1);
    TextDrawSetShadow(orgs_textdraw[0], 0);
    TextDrawAlignment(orgs_textdraw[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[0], -1);
    TextDrawBackgroundColor(orgs_textdraw[0], 255);
    TextDrawBoxColor(orgs_textdraw[0], 353703423);
    TextDrawUseBox(orgs_textdraw[0], true);
    TextDrawSetProportional(orgs_textdraw[0], true);
    TextDrawSetSelectable(orgs_textdraw[0], false);

    orgs_textdraw[1] = TextDrawCreate(155.000000, 135.000000, "id            nome                                 lider                    membros     pontuacao");
    TextDrawFont(orgs_textdraw[1], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(orgs_textdraw[1], 0.170833, 0.850000);
    TextDrawTextSize(orgs_textdraw[1], 456.000000, 17.000000);
    TextDrawSetOutline(orgs_textdraw[1], 0);
    TextDrawSetShadow(orgs_textdraw[1], 0);
    TextDrawAlignment(orgs_textdraw[1], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[1], 1734895871);
    TextDrawBackgroundColor(orgs_textdraw[1], 255);
    TextDrawBoxColor(orgs_textdraw[1], 50);
    TextDrawUseBox(orgs_textdraw[1], false);
    TextDrawSetProportional(orgs_textdraw[1], true);
    TextDrawSetSelectable(orgs_textdraw[1], false);

    orgs_textdraw[2] = TextDrawCreate(155.000000, 156.000000, "_");
    TextDrawFont(orgs_textdraw[2], TEXT_DRAW_FONT_3);
    TextDrawLetterSize(orgs_textdraw[2], 0.641665, 1.250000);
    TextDrawTextSize(orgs_textdraw[2], 477.500000, 16.000000);
    TextDrawSetOutline(orgs_textdraw[2], 1);
    TextDrawSetShadow(orgs_textdraw[2], 0);
    TextDrawAlignment(orgs_textdraw[2], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[2], -1);
    TextDrawBackgroundColor(orgs_textdraw[2], 255);
    TextDrawBoxColor(orgs_textdraw[2], 50);
    TextDrawUseBox(orgs_textdraw[2], true);
    TextDrawSetProportional(orgs_textdraw[2], true);
    TextDrawSetSelectable(orgs_textdraw[2], false);

    orgs_textdraw[3] = TextDrawCreate(155.000000, 178.000000, "_");
    TextDrawFont(orgs_textdraw[3], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(orgs_textdraw[3], 0.641665, 1.250000);
    TextDrawTextSize(orgs_textdraw[3], 477.500000, 19.500000);
    TextDrawSetOutline(orgs_textdraw[3], 1);
    TextDrawSetShadow(orgs_textdraw[3], 0);
    TextDrawAlignment(orgs_textdraw[3], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[3], -1);
    TextDrawBackgroundColor(orgs_textdraw[3], 255);
    TextDrawBoxColor(orgs_textdraw[3], 50);
    TextDrawUseBox(orgs_textdraw[3], true);
    TextDrawSetProportional(orgs_textdraw[3], true);
    TextDrawSetSelectable(orgs_textdraw[3], false);

    orgs_textdraw[4] = TextDrawCreate(155.000000, 202.000000, "_");
    TextDrawFont(orgs_textdraw[4], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(orgs_textdraw[4], 0.641665, 1.250000);
    TextDrawTextSize(orgs_textdraw[4], 477.500000, 19.500000);
    TextDrawSetOutline(orgs_textdraw[4], 1);
    TextDrawSetShadow(orgs_textdraw[4], 0);
    TextDrawAlignment(orgs_textdraw[4], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[4], -1);
    TextDrawBackgroundColor(orgs_textdraw[4], 255);
    TextDrawBoxColor(orgs_textdraw[4], 50);
    TextDrawUseBox(orgs_textdraw[4], true);
    TextDrawSetProportional(orgs_textdraw[4], true);
    TextDrawSetSelectable(orgs_textdraw[4], false);

    orgs_textdraw[5] = TextDrawCreate(155.000000, 224.000000, "_");
    TextDrawFont(orgs_textdraw[5], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(orgs_textdraw[5], 0.641665, 1.250000);
    TextDrawTextSize(orgs_textdraw[5], 477.500000, 19.500000);
    TextDrawSetOutline(orgs_textdraw[5], 1);
    TextDrawSetShadow(orgs_textdraw[5], 0);
    TextDrawAlignment(orgs_textdraw[5], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[5], -1);
    TextDrawBackgroundColor(orgs_textdraw[5], 255);
    TextDrawBoxColor(orgs_textdraw[5], 50);
    TextDrawUseBox(orgs_textdraw[5], true);
    TextDrawSetProportional(orgs_textdraw[5], true);
    TextDrawSetSelectable(orgs_textdraw[5], false);

    orgs_textdraw[6] = TextDrawCreate(155.000000, 246.000000, "_");
    TextDrawFont(orgs_textdraw[6], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(orgs_textdraw[6], 0.641665, 1.250000);
    TextDrawTextSize(orgs_textdraw[6], 477.500000, 19.500000);
    TextDrawSetOutline(orgs_textdraw[6], 1);
    TextDrawSetShadow(orgs_textdraw[6], 0);
    TextDrawAlignment(orgs_textdraw[6], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[6], -1);
    TextDrawBackgroundColor(orgs_textdraw[6], 255);
    TextDrawBoxColor(orgs_textdraw[6], 50);
    TextDrawUseBox(orgs_textdraw[6], true);
    TextDrawSetProportional(orgs_textdraw[6], true);
    TextDrawSetSelectable(orgs_textdraw[6], false);

    orgs_textdraw[7] = TextDrawCreate(155.000000, 269.000000, "_");
    TextDrawFont(orgs_textdraw[7], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(orgs_textdraw[7], 0.641665, 1.250000);
    TextDrawTextSize(orgs_textdraw[7], 477.500000, 19.500000);
    TextDrawSetOutline(orgs_textdraw[7], 1);
    TextDrawSetShadow(orgs_textdraw[7], 0);
    TextDrawAlignment(orgs_textdraw[7], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[7], -1);
    TextDrawBackgroundColor(orgs_textdraw[7], 255);
    TextDrawBoxColor(orgs_textdraw[7], 50);
    TextDrawUseBox(orgs_textdraw[7], true);
    TextDrawSetProportional(orgs_textdraw[7], true);
    TextDrawSetSelectable(orgs_textdraw[7], false);

    orgs_textdraw[8] = TextDrawCreate(155.000000, 292.000000, "_");
    TextDrawFont(orgs_textdraw[8], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(orgs_textdraw[8], 0.641665, 1.250000);
    TextDrawTextSize(orgs_textdraw[8], 477.500000, 19.500000);
    TextDrawSetOutline(orgs_textdraw[8], 1);
    TextDrawSetShadow(orgs_textdraw[8], 0);
    TextDrawAlignment(orgs_textdraw[8], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[8], -1);
    TextDrawBackgroundColor(orgs_textdraw[8], 255);
    TextDrawBoxColor(orgs_textdraw[8], 50);
    TextDrawUseBox(orgs_textdraw[8], true);
    TextDrawSetProportional(orgs_textdraw[8], true);
    TextDrawSetSelectable(orgs_textdraw[8], false);

    orgs_textdraw[9] = TextDrawCreate(268.000000, 314.000000, "LD_BEAT:left");
    TextDrawFont(orgs_textdraw[9], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(orgs_textdraw[9], 0.600000, 2.000000);
    TextDrawTextSize(orgs_textdraw[9], 16.500000, 17.000000);
    TextDrawSetOutline(orgs_textdraw[9], 1);
    TextDrawSetShadow(orgs_textdraw[9], 0);
    TextDrawAlignment(orgs_textdraw[9], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[9], -1);
    TextDrawBackgroundColor(orgs_textdraw[9], 255);
    TextDrawBoxColor(orgs_textdraw[9], 50);
    TextDrawUseBox(orgs_textdraw[9], true);
    TextDrawSetProportional(orgs_textdraw[9], true);
    TextDrawSetSelectable(orgs_textdraw[9], true);

    orgs_textdraw[10] = TextDrawCreate(344.000000, 314.000000, "LD_BEAT:right");
    TextDrawFont(orgs_textdraw[10], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(orgs_textdraw[10], 0.600000, 2.000000);
    TextDrawTextSize(orgs_textdraw[10], 16.500000, 17.000000);
    TextDrawSetOutline(orgs_textdraw[10], 1);
    TextDrawSetShadow(orgs_textdraw[10], 0);
    TextDrawAlignment(orgs_textdraw[10], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[10], -1);
    TextDrawBackgroundColor(orgs_textdraw[10], 255);
    TextDrawBoxColor(orgs_textdraw[10], 50);
    TextDrawUseBox(orgs_textdraw[10], true);
    TextDrawSetProportional(orgs_textdraw[10], true);
    TextDrawSetSelectable(orgs_textdraw[10], true);

    orgs_textdraw[11] = TextDrawCreate(470.000000, 134.000000, "ld_beat:cross");
    TextDrawFont(orgs_textdraw[11], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(orgs_textdraw[11], 0.600000, 2.000000);
    TextDrawTextSize(orgs_textdraw[11], 11.500000, 12.000000);
    TextDrawSetOutline(orgs_textdraw[11], 1);
    TextDrawSetShadow(orgs_textdraw[11], 0);
    TextDrawAlignment(orgs_textdraw[11], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(orgs_textdraw[11], -16776961);
    TextDrawBackgroundColor(orgs_textdraw[11], 255);
    TextDrawBoxColor(orgs_textdraw[11], 50);
    TextDrawUseBox(orgs_textdraw[11], true);
    TextDrawSetProportional(orgs_textdraw[11], true);
    TextDrawSetSelectable(orgs_textdraw[11], true);

    player_orgs_textdraw[0] = TextDrawCreate(157.000000, 155.000000, "1~n~~n~2~n~~n~3~n~~n~4~n~~n~5~n~~n~6~n~~n~7");
    TextDrawFont(player_orgs_textdraw[0], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(player_orgs_textdraw[0], 0.179167, 1.259999);
    TextDrawTextSize(player_orgs_textdraw[0], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[0], 0);
    TextDrawSetShadow(player_orgs_textdraw[0], 0);
    TextDrawAlignment(player_orgs_textdraw[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[0], -1);
    TextDrawBackgroundColor(player_orgs_textdraw[0], 255);
    TextDrawBoxColor(player_orgs_textdraw[0], 50);
    TextDrawUseBox(player_orgs_textdraw[0], false);
    TextDrawSetProportional(player_orgs_textdraw[0], true);
    TextDrawSetSelectable(player_orgs_textdraw[0], false);

    player_orgs_textdraw[1] = TextDrawCreate(165.000000, 150.000000, "LD_TATT:9crown");
    TextDrawFont(player_orgs_textdraw[1], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(player_orgs_textdraw[1], 0.600000, 2.000000);
    TextDrawTextSize(player_orgs_textdraw[1], 19.500000, 21.500000);
    TextDrawSetOutline(player_orgs_textdraw[1], 1);
    TextDrawSetShadow(player_orgs_textdraw[1], 0);
    TextDrawAlignment(player_orgs_textdraw[1], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[1], 1097458175);
    TextDrawBackgroundColor(player_orgs_textdraw[1], 255);
    TextDrawBoxColor(player_orgs_textdraw[1], 50);
    TextDrawUseBox(player_orgs_textdraw[1], true);
    TextDrawSetProportional(player_orgs_textdraw[1], true);
    TextDrawSetSelectable(player_orgs_textdraw[1], false);

    player_orgs_textdraw[2] = TextDrawCreate(165.000000, 173.000000, "LD_TATT:9gun2");
    TextDrawFont(player_orgs_textdraw[2], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(player_orgs_textdraw[2], 0.600000, 2.000000);
    TextDrawTextSize(player_orgs_textdraw[2], 19.500000, 21.500000);
    TextDrawSetOutline(player_orgs_textdraw[2], 1);
    TextDrawSetShadow(player_orgs_textdraw[2], 0);
    TextDrawAlignment(player_orgs_textdraw[2], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[2], 1687547391);
    TextDrawBackgroundColor(player_orgs_textdraw[2], 255);
    TextDrawBoxColor(player_orgs_textdraw[2], 50);
    TextDrawUseBox(player_orgs_textdraw[2], true);
    TextDrawSetProportional(player_orgs_textdraw[2], true);
    TextDrawSetSelectable(player_orgs_textdraw[2], false);

    player_orgs_textdraw[3] = TextDrawCreate(165.000000, 196.000000, "LD_TATT:9gun2");
    TextDrawFont(player_orgs_textdraw[3], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(player_orgs_textdraw[3], 0.600000, 2.000000);
    TextDrawTextSize(player_orgs_textdraw[3], 19.500000, 21.500000);
    TextDrawSetOutline(player_orgs_textdraw[3], 1);
    TextDrawSetShadow(player_orgs_textdraw[3], 0);
    TextDrawAlignment(player_orgs_textdraw[3], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[3], 1296911871);
    TextDrawBackgroundColor(player_orgs_textdraw[3], 255);
    TextDrawBoxColor(player_orgs_textdraw[3], 50);
    TextDrawUseBox(player_orgs_textdraw[3], true);
    TextDrawSetProportional(player_orgs_textdraw[3], true);
    TextDrawSetSelectable(player_orgs_textdraw[3], false);

    player_orgs_textdraw[4] = TextDrawCreate(165.000000, 219.000000, "LD_TATT:9gun2");
    TextDrawFont(player_orgs_textdraw[4], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(player_orgs_textdraw[4], 0.600000, 2.000000);
    TextDrawTextSize(player_orgs_textdraw[4], 19.500000, 21.500000);
    TextDrawSetOutline(player_orgs_textdraw[4], 1);
    TextDrawSetShadow(player_orgs_textdraw[4], 0);
    TextDrawAlignment(player_orgs_textdraw[4], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[4], -764862721);
    TextDrawBackgroundColor(player_orgs_textdraw[4], 255);
    TextDrawBoxColor(player_orgs_textdraw[4], 50);
    TextDrawUseBox(player_orgs_textdraw[4], true);
    TextDrawSetProportional(player_orgs_textdraw[4], true);
    TextDrawSetSelectable(player_orgs_textdraw[4], false);

    player_orgs_textdraw[5] = TextDrawCreate(165.000000, 242.000000, "LD_TATT:9gun2");
    TextDrawFont(player_orgs_textdraw[5], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(player_orgs_textdraw[5], 0.600000, 2.000000);
    TextDrawTextSize(player_orgs_textdraw[5], 19.500000, 21.500000);
    TextDrawSetOutline(player_orgs_textdraw[5], 1);
    TextDrawSetShadow(player_orgs_textdraw[5], 0);
    TextDrawAlignment(player_orgs_textdraw[5], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[5], -2686721);
    TextDrawBackgroundColor(player_orgs_textdraw[5], 255);
    TextDrawBoxColor(player_orgs_textdraw[5], 50);
    TextDrawUseBox(player_orgs_textdraw[5], true);
    TextDrawSetProportional(player_orgs_textdraw[5], true);
    TextDrawSetSelectable(player_orgs_textdraw[5], false);

    player_orgs_textdraw[6] = TextDrawCreate(165.000000, 265.000000, "LD_TATT:9gun2");
    TextDrawFont(player_orgs_textdraw[6], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(player_orgs_textdraw[6], 0.600000, 2.000000);
    TextDrawTextSize(player_orgs_textdraw[6], 19.500000, 21.500000);
    TextDrawSetOutline(player_orgs_textdraw[6], 1);
    TextDrawSetShadow(player_orgs_textdraw[6], 0);
    TextDrawAlignment(player_orgs_textdraw[6], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[6], -1061109505);
    TextDrawBackgroundColor(player_orgs_textdraw[6], 255);
    TextDrawBoxColor(player_orgs_textdraw[6], 50);
    TextDrawUseBox(player_orgs_textdraw[6], true);
    TextDrawSetProportional(player_orgs_textdraw[6], true);
    TextDrawSetSelectable(player_orgs_textdraw[6], false);

    player_orgs_textdraw[7] = TextDrawCreate(165.000000, 288.000000, "LD_TATT:9gun2");
    TextDrawFont(player_orgs_textdraw[7], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(player_orgs_textdraw[7], 0.600000, 2.000000);
    TextDrawTextSize(player_orgs_textdraw[7], 19.500000, 21.500000);
    TextDrawSetOutline(player_orgs_textdraw[7], 1);
    TextDrawSetShadow(player_orgs_textdraw[7], 0);
    TextDrawAlignment(player_orgs_textdraw[7], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[7], 1433087999);
    TextDrawBackgroundColor(player_orgs_textdraw[7], 255);
    TextDrawBoxColor(player_orgs_textdraw[7], 50);
    TextDrawUseBox(player_orgs_textdraw[7], true);
    TextDrawSetProportional(player_orgs_textdraw[7], true);
    TextDrawSetSelectable(player_orgs_textdraw[7], false);

    player_orgs_textdraw[8] = TextDrawCreate(188.000000, 155.000000, "Governo");
    TextDrawFont(player_orgs_textdraw[8], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[8], 0.224999, 1.200000);
    TextDrawTextSize(player_orgs_textdraw[8], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[8], 0);
    TextDrawSetShadow(player_orgs_textdraw[8], 0);
    TextDrawAlignment(player_orgs_textdraw[8], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[8], 1097458175);
    TextDrawBackgroundColor(player_orgs_textdraw[8], 255);
    TextDrawBoxColor(player_orgs_textdraw[8], 50);
    TextDrawUseBox(player_orgs_textdraw[8], false);
    TextDrawSetProportional(player_orgs_textdraw[8], true);
    TextDrawSetSelectable(player_orgs_textdraw[8], false);

    player_orgs_textdraw[9] = TextDrawCreate(188.000000, 178.000000, "Policia Militar");
    TextDrawFont(player_orgs_textdraw[9], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[9], 0.224999, 1.200000);
    TextDrawTextSize(player_orgs_textdraw[9], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[9], 0);
    TextDrawSetShadow(player_orgs_textdraw[9], 0);
    TextDrawAlignment(player_orgs_textdraw[9], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[9], 1687547391);
    TextDrawBackgroundColor(player_orgs_textdraw[9], 255);
    TextDrawBoxColor(player_orgs_textdraw[9], 50);
    TextDrawUseBox(player_orgs_textdraw[9], false);
    TextDrawSetProportional(player_orgs_textdraw[9], true);
    TextDrawSetSelectable(player_orgs_textdraw[9], false);

    player_orgs_textdraw[10] = TextDrawCreate(188.000000, 201.000000, "B.O.P.E");
    TextDrawFont(player_orgs_textdraw[10], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[10], 0.224999, 1.200000);
    TextDrawTextSize(player_orgs_textdraw[10], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[10], 0);
    TextDrawSetShadow(player_orgs_textdraw[10], 0);
    TextDrawAlignment(player_orgs_textdraw[10], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[10], 1296911871);
    TextDrawBackgroundColor(player_orgs_textdraw[10], 255);
    TextDrawBoxColor(player_orgs_textdraw[10], 50);
    TextDrawUseBox(player_orgs_textdraw[10], false);
    TextDrawSetProportional(player_orgs_textdraw[10], true);
    TextDrawSetSelectable(player_orgs_textdraw[10], false);

    player_orgs_textdraw[11] = TextDrawCreate(188.000000, 224.000000, "Policia Federal");
    TextDrawFont(player_orgs_textdraw[11], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[11], 0.224999, 1.200000);
    TextDrawTextSize(player_orgs_textdraw[11], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[11], 0);
    TextDrawSetShadow(player_orgs_textdraw[11], 0);
    TextDrawAlignment(player_orgs_textdraw[11], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[11], -764862721);
    TextDrawBackgroundColor(player_orgs_textdraw[11], 255);
    TextDrawBoxColor(player_orgs_textdraw[11], 50);
    TextDrawUseBox(player_orgs_textdraw[11], false);
    TextDrawSetProportional(player_orgs_textdraw[11], true);
    TextDrawSetSelectable(player_orgs_textdraw[11], false);

    player_orgs_textdraw[12] = TextDrawCreate(188.000000, 246.000000, "P.R.F");
    TextDrawFont(player_orgs_textdraw[12], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[12], 0.224999, 1.200000);
    TextDrawTextSize(player_orgs_textdraw[12], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[12], 0);
    TextDrawSetShadow(player_orgs_textdraw[12], 0);
    TextDrawAlignment(player_orgs_textdraw[12], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[12], -2686721);
    TextDrawBackgroundColor(player_orgs_textdraw[12], 255);
    TextDrawBoxColor(player_orgs_textdraw[12], 50);
    TextDrawUseBox(player_orgs_textdraw[12], false);
    TextDrawSetProportional(player_orgs_textdraw[12], true);
    TextDrawSetSelectable(player_orgs_textdraw[12], false);

    player_orgs_textdraw[13] = TextDrawCreate(188.000000, 269.000000, "Policia Civil");
    TextDrawFont(player_orgs_textdraw[13], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[13], 0.224999, 1.200000);
    TextDrawTextSize(player_orgs_textdraw[13], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[13], 0);
    TextDrawSetShadow(player_orgs_textdraw[13], 0);
    TextDrawAlignment(player_orgs_textdraw[13], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[13], -1061109505);
    TextDrawBackgroundColor(player_orgs_textdraw[13], 255);
    TextDrawBoxColor(player_orgs_textdraw[13], 50);
    TextDrawUseBox(player_orgs_textdraw[13], false);
    TextDrawSetProportional(player_orgs_textdraw[13], true);
    TextDrawSetSelectable(player_orgs_textdraw[13], false);

    player_orgs_textdraw[14] = TextDrawCreate(188.000000, 292.000000, "Exercito");
    TextDrawFont(player_orgs_textdraw[14], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[14], 0.224999, 1.200000);
    TextDrawTextSize(player_orgs_textdraw[14], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[14], 0);
    TextDrawSetShadow(player_orgs_textdraw[14], 0);
    TextDrawAlignment(player_orgs_textdraw[14], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[14], 1433087999);
    TextDrawBackgroundColor(player_orgs_textdraw[14], 255);
    TextDrawBoxColor(player_orgs_textdraw[14], 50);
    TextDrawUseBox(player_orgs_textdraw[14], false);
    TextDrawSetProportional(player_orgs_textdraw[14], true);
    TextDrawSetSelectable(player_orgs_textdraw[14], false);

    player_orgs_textdraw[15] = TextDrawCreate(349.000000, 155.000000, "1/30~n~~n~2/30~n~~n~3/30~n~~n~4/30~n~~n~5/30~n~~n~65/30~n~~n~7/30");
    TextDrawFont(player_orgs_textdraw[15], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(player_orgs_textdraw[15], 0.179167, 1.259999);
    TextDrawTextSize(player_orgs_textdraw[15], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[15], 0);
    TextDrawSetShadow(player_orgs_textdraw[15], 0);
    TextDrawAlignment(player_orgs_textdraw[15], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(player_orgs_textdraw[15], -1);
    TextDrawBackgroundColor(player_orgs_textdraw[15], 255);
    TextDrawBoxColor(player_orgs_textdraw[15], 50);
    TextDrawUseBox(player_orgs_textdraw[15], false);
    TextDrawSetProportional(player_orgs_textdraw[15], true);
    TextDrawSetSelectable(player_orgs_textdraw[15], false);

    player_orgs_textdraw[16] = TextDrawCreate(397.000000, 155.000000, "1~n~~n~2~n~~n~3~n~~n~4~n~~n~5~n~~n~6~n~~n~7");
    TextDrawFont(player_orgs_textdraw[16], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(player_orgs_textdraw[16], 0.179167, 1.259999);
    TextDrawTextSize(player_orgs_textdraw[16], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[16], 0);
    TextDrawSetShadow(player_orgs_textdraw[16], 0);
    TextDrawAlignment(player_orgs_textdraw[16], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(player_orgs_textdraw[16], -1);
    TextDrawBackgroundColor(player_orgs_textdraw[16], 255);
    TextDrawBoxColor(player_orgs_textdraw[16], 50);
    TextDrawUseBox(player_orgs_textdraw[16], false);
    TextDrawSetProportional(player_orgs_textdraw[16], true);
    TextDrawSetSelectable(player_orgs_textdraw[16], false);

    player_orgs_textdraw[17] = TextDrawCreate(273.000000, 156.000000, "Theus_Crazzy");
    TextDrawFont(player_orgs_textdraw[17], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[17], 0.183332, 1.049999);
    TextDrawTextSize(player_orgs_textdraw[17], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[17], 0);
    TextDrawSetShadow(player_orgs_textdraw[17], 0);
    TextDrawAlignment(player_orgs_textdraw[17], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[17], -1);
    TextDrawBackgroundColor(player_orgs_textdraw[17], 255);
    TextDrawBoxColor(player_orgs_textdraw[17], 50);
    TextDrawUseBox(player_orgs_textdraw[17], false);
    TextDrawSetProportional(player_orgs_textdraw[17], true);
    TextDrawSetSelectable(player_orgs_textdraw[17], false);

    player_orgs_textdraw[18] = TextDrawCreate(273.000000, 178.000000, "Theus_Crazzy");
    TextDrawFont(player_orgs_textdraw[18], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[18], 0.183332, 1.049999);
    TextDrawTextSize(player_orgs_textdraw[18], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[18], 0);
    TextDrawSetShadow(player_orgs_textdraw[18], 0);
    TextDrawAlignment(player_orgs_textdraw[18], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[18], -1);
    TextDrawBackgroundColor(player_orgs_textdraw[18], 255);
    TextDrawBoxColor(player_orgs_textdraw[18], 50);
    TextDrawUseBox(player_orgs_textdraw[18], false);
    TextDrawSetProportional(player_orgs_textdraw[18], true);
    TextDrawSetSelectable(player_orgs_textdraw[18], false);

    player_orgs_textdraw[19] = TextDrawCreate(273.000000, 202.000000, "Theus_Crazzy");
    TextDrawFont(player_orgs_textdraw[19], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[19], 0.183332, 1.049999);
    TextDrawTextSize(player_orgs_textdraw[19], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[19], 0);
    TextDrawSetShadow(player_orgs_textdraw[19], 0);
    TextDrawAlignment(player_orgs_textdraw[19], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[19], -1);
    TextDrawBackgroundColor(player_orgs_textdraw[19], 255);
    TextDrawBoxColor(player_orgs_textdraw[19], 50);
    TextDrawUseBox(player_orgs_textdraw[19], false);
    TextDrawSetProportional(player_orgs_textdraw[19], true);
    TextDrawSetSelectable(player_orgs_textdraw[19], false);

    player_orgs_textdraw[20] = TextDrawCreate(273.000000, 224.000000, "Theus_Crazzy");
    TextDrawFont(player_orgs_textdraw[20], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[20], 0.183332, 1.049999);
    TextDrawTextSize(player_orgs_textdraw[20], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[20], 0);
    TextDrawSetShadow(player_orgs_textdraw[20], 0);
    TextDrawAlignment(player_orgs_textdraw[20], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[20], -1);
    TextDrawBackgroundColor(player_orgs_textdraw[20], 255);
    TextDrawBoxColor(player_orgs_textdraw[20], 50);
    TextDrawUseBox(player_orgs_textdraw[20], false);
    TextDrawSetProportional(player_orgs_textdraw[20], true);
    TextDrawSetSelectable(player_orgs_textdraw[20], false);

    player_orgs_textdraw[21] = TextDrawCreate(273.000000, 246.000000, "Theus_Crazzy");
    TextDrawFont(player_orgs_textdraw[21], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[21], 0.183332, 1.049999);
    TextDrawTextSize(player_orgs_textdraw[21], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[21], 0);
    TextDrawSetShadow(player_orgs_textdraw[21], 0);
    TextDrawAlignment(player_orgs_textdraw[21], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[21], -1);
    TextDrawBackgroundColor(player_orgs_textdraw[21], 255);
    TextDrawBoxColor(player_orgs_textdraw[21], 50);
    TextDrawUseBox(player_orgs_textdraw[21], false);
    TextDrawSetProportional(player_orgs_textdraw[21], true);
    TextDrawSetSelectable(player_orgs_textdraw[21], false);

    player_orgs_textdraw[22] = TextDrawCreate(273.000000, 269.000000, "Theus_Crazzy");
    TextDrawFont(player_orgs_textdraw[22], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[22], 0.183332, 1.049999);
    TextDrawTextSize(player_orgs_textdraw[22], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[22], 0);
    TextDrawSetShadow(player_orgs_textdraw[22], 0);
    TextDrawAlignment(player_orgs_textdraw[22], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[22], -1);
    TextDrawBackgroundColor(player_orgs_textdraw[22], 255);
    TextDrawBoxColor(player_orgs_textdraw[22], 50);
    TextDrawUseBox(player_orgs_textdraw[22], false);
    TextDrawSetProportional(player_orgs_textdraw[22], true);
    TextDrawSetSelectable(player_orgs_textdraw[22], false);

    player_orgs_textdraw[23] = TextDrawCreate(273.000000, 292.000000, "Theus_Crazzy");
    TextDrawFont(player_orgs_textdraw[23], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(player_orgs_textdraw[23], 0.183332, 1.049999);
    TextDrawTextSize(player_orgs_textdraw[23], 456.000000, 17.000000);
    TextDrawSetOutline(player_orgs_textdraw[23], 0);
    TextDrawSetShadow(player_orgs_textdraw[23], 0);
    TextDrawAlignment(player_orgs_textdraw[23], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(player_orgs_textdraw[23], -1);
    TextDrawBackgroundColor(player_orgs_textdraw[23], 255);
    TextDrawBoxColor(player_orgs_textdraw[23], 50);
    TextDrawUseBox(player_orgs_textdraw[23], false);
    TextDrawSetProportional(player_orgs_textdraw[23], true);
    TextDrawSetSelectable(player_orgs_textdraw[23], false);
}

//Player Textdraws
stock PlayerTextdraws_CreateOrgs(playerid)
{
    player_orgs_textdraw_page[playerid] = CreatePlayerTextDraw(playerid, 313.000000, 315.000000, "Pagina~n~1/4");
    PlayerTextDrawFont(playerid, player_orgs_textdraw_page[playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawLetterSize(playerid, player_orgs_textdraw_page[playerid], 0.170833, 0.850000);
    PlayerTextDrawTextSize(playerid, player_orgs_textdraw_page[playerid], 456.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, player_orgs_textdraw_page[playerid], 0);
    PlayerTextDrawSetShadow(playerid, player_orgs_textdraw_page[playerid], 0);
    PlayerTextDrawAlignment(playerid, player_orgs_textdraw_page[playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, player_orgs_textdraw_page[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, player_orgs_textdraw_page[playerid], 255);
    PlayerTextDrawBoxColor(playerid, player_orgs_textdraw_page[playerid], 50);
    PlayerTextDrawUseBox(playerid, player_orgs_textdraw_page[playerid], false);
    PlayerTextDrawSetProportional(playerid, player_orgs_textdraw_page[playerid], true);
    PlayerTextDrawSetSelectable(playerid, player_orgs_textdraw_page[playerid], false);
    return 1;
}

static const orgs_array_td[] = { 7, 1, 2, 3, 11, 16, 33, 34, 9, 12, 13, 24, 5, 14, 17, 18, 19, 21, 8, 22, 15, 20, 25, 28 };

static const orgs_array_td_sprite[][] = { 
    "LD_TATT:9crown", // Governo
    "LD_TATT:9gun2", "LD_TATT:9gun2", "LD_TATT:9gun2", "LD_TATT:9gun2", "LD_TATT:9gun2", "LD_TATT:9gun2", "LD_TATT:9gun2",    // Policia
    //"LD_TATT:7cross", // SAMU - ORG ID 4
    "LD_TATT:10ls2", /// Reporteres
    "LD_TATT:8gun", "LD_TATT:8gun", "LD_TATT:8gun", // Máfia
    "LD_TATT:9gun", "LD_TATT:9gun", "LD_TATT:9gun", "LD_TATT:9gun", "LD_TATT:9gun", "LD_TATT:9gun", // Gangster
    "LD_TATT:12dager", "LD_TATT:12dager", // Assassinos
    "LD_TATT:7mary", "LD_TATT:7mary", // Terroritas
    "LD_TATT:8poker", "LD_TATT:8poker" // Mercenário
};

// Comando
CMD:orgs(playerid)
{
	ChangePageOrgs(playerid);
    ShowPlayerOrgs(playerid);

    SelectTextDraw(playerid, 0x1CB8BA50);

	return 1;
}

static ChangePageOrgs(playerid, page=0)
{
    new 
        itens_page = (page * 7), 
        orgid,
        string[128]
    ;

    if (page == 0)
        page_orgs[playerid] = 0;

    format(string, sizeof(string), "Pagina~n~%d/4", page+1);
    PlayerTextDrawSetString(playerid, player_orgs_textdraw_page[playerid], string);

    if (page != 3) 
    {
        format(string, sizeof(string), "%d/30~n~~n~%d/30~n~~n~%d/30~n~~n~%d/30~n~~n~%d/30~n~~n~%d/30~n~~n~%d/30", 
        GetTotalMembersInOrg(orgs_array_td[itens_page]), GetTotalMembersInOrg(orgs_array_td[itens_page+1]), GetTotalMembersInOrg(orgs_array_td[itens_page+2]), 
        GetTotalMembersInOrg(orgs_array_td[itens_page+3]), GetTotalMembersInOrg(orgs_array_td[itens_page+4]), GetTotalMembersInOrg(orgs_array_td[itens_page+5]), 
        GetTotalMembersInOrg(orgs_array_td[itens_page+6]));
        TextDrawSetString(player_orgs_textdraw[15], string);

        format(string, sizeof(string), "%d~n~~n~%d~n~~n~%d~n~~n~%d~n~~n~%d~n~~n~%d~n~~n~%d", 
        orgs_array_td[itens_page], orgs_array_td[itens_page+1], orgs_array_td[itens_page+2], orgs_array_td[itens_page+3], 
        orgs_array_td[itens_page+4], orgs_array_td[itens_page+5], orgs_array_td[itens_page+6]);
        TextDrawSetString(player_orgs_textdraw[0], string);

        //format(string, sizeof(string), "1~n~~n~2~n~~n~3~n~~n~4~n~~n~5~n~~n~6~n~~n~7", orgs_array_td[itens_page], orgs_array_td[itens_page+1], orgs_array_td[itens_page+2]);
        TextDrawSetString(player_orgs_textdraw[16], "-~n~~n~-~n~~n~-~n~~n~-~n~~n~-~n~~n~-~n~~n~-");

        for (new text; text < 7; text++) {

            orgid = orgs_array_td[itens_page + text];

            TextDrawColor(player_orgs_textdraw[text + 1], GetOrgHexColor(orgid));
            TextDrawSetString(player_orgs_textdraw[text + 1], orgs_array_td_sprite[itens_page + text]);

            TextDrawColor(player_orgs_textdraw[text + 8], GetOrgHexColor(orgid));
            TextDrawSetString(player_orgs_textdraw[text + 8], GetOrgName(orgid));

            TextDrawSetString(player_orgs_textdraw[text + 17], OrgMembros[orgid][SLOT_LIDER][MemberName]);
        }
    } else {

        format(string, sizeof(string), "%d/30~n~~n~%d/30~n~~n~%d/30", 
        GetTotalMembersInOrg(orgs_array_td[itens_page]), GetTotalMembersInOrg(orgs_array_td[itens_page+1]), GetTotalMembersInOrg(orgs_array_td[itens_page+2]));
        TextDrawSetString(player_orgs_textdraw[15], string);

        format(string, sizeof(string), "%d~n~~n~%d~n~~n~%d", 
        orgs_array_td[itens_page], orgs_array_td[itens_page+1], orgs_array_td[itens_page+2]);
        TextDrawSetString(player_orgs_textdraw[0], string);

        //format(string, sizeof(string), "%d~n~~n~%d~n~~n~%d", orgs_array_td[itens_page], orgs_array_td[itens_page+1], orgs_array_td[itens_page+2]);
        TextDrawSetString(player_orgs_textdraw[16], "-~n~~n~-~n~~n~-");

        for (new text; text < 3; text++) {

            orgid = orgs_array_td[itens_page + text];

            TextDrawColor(player_orgs_textdraw[text + 1], GetOrgHexColor(orgid));
            TextDrawSetString(player_orgs_textdraw[text + 1], orgs_array_td_sprite[itens_page + text]);

            TextDrawColor(player_orgs_textdraw[text + 8], GetOrgHexColor(orgid));
            TextDrawSetString(player_orgs_textdraw[text + 8], GetOrgName(orgid));

            TextDrawSetString(player_orgs_textdraw[text + 17], OrgMembros[orgid][SLOT_LIDER][MemberName]);
        }
    }

    return 1;
}

static ShowPlayerOrgs(playerid) {
    PlayerTextDrawShow(playerid, player_orgs_textdraw_page[playerid]);
    
    for (new text; text < sizeof(orgs_textdraw); text++) {
        TextDrawShowForPlayer(playerid, orgs_textdraw[text]);
    }
    for (new text; text < sizeof(player_orgs_textdraw); text++) {
        TextDrawShowForPlayer(playerid, player_orgs_textdraw[text]);
    }
}

static HidePlayerOrgs(playerid) {
    PlayerTextDrawHide(playerid, player_orgs_textdraw_page[playerid]);
    
    for (new text; text < sizeof(orgs_textdraw); text++) {
        TextDrawHideForPlayer(playerid, orgs_textdraw[text]);
    }
    for (new text; text < sizeof(player_orgs_textdraw); text++) {
        TextDrawHideForPlayer(playerid, player_orgs_textdraw[text]);
    }
}

hook OnClickDynamicTextDraw(playerid, Text:textid)
{
    if (textid == Text:INVALID_TEXT_DRAW) {
        HidePlayerOrgs(playerid);
    }
	else if (textid == orgs_textdraw[11]) {
		HidePlayerOrgs(playerid);

        CancelSelectTextDraw(playerid);
	}
    else if (textid == orgs_textdraw[10]) {
        if (page_orgs[playerid] == 2) {
            HidePlayerOrgs(playerid);

            page_orgs[playerid]++;
            ChangePageOrgs(playerid, page_orgs[playerid]);

            ShowPlayerOrgs(playerid);

            for (new text; text < 4; text++) {
                TextDrawHideForPlayer(playerid, player_orgs_textdraw[text + 1 + 3]);
                TextDrawHideForPlayer(playerid, player_orgs_textdraw[text + 8 + 3]);
                TextDrawHideForPlayer(playerid, player_orgs_textdraw[text + 17 + 3]);
            }
        }
        else {
            if (page_orgs[playerid] < 3) {
                HidePlayerOrgs(playerid);
                page_orgs[playerid]++;
                ChangePageOrgs(playerid, page_orgs[playerid]);
                ShowPlayerOrgs(playerid);
            }
        }
	}
    else if (textid == orgs_textdraw[9]) {
        if (page_orgs[playerid] > 0) {
            HidePlayerOrgs(playerid);
            page_orgs[playerid]--;
            ChangePageOrgs(playerid, page_orgs[playerid]);
            ShowPlayerOrgs(playerid);
        }
	}
    return 1;
}