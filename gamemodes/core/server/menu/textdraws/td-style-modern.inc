// Textdraws do menu
new PlayerText:menu_ptextdraws[4][MAX_PLAYERS];
new PlayerText:menu_pstextdraws[MAX_PAGE_ITENS][MAX_PLAYERS]; // Item
new PlayerText:menu_pqtextdraws[MAX_PAGE_ITENS][MAX_PLAYERS]; // Quantidade
new Text:menu_textdraws[3];

stock CreatePTexdraws_MenuModern(playerid) 
{
    // Box do titulo
    menu_ptextdraws[0][playerid] = CreatePlayerTextDraw(playerid, 43.500000, 170.000000, "_");
    PlayerTextDrawLetterSize(playerid, menu_ptextdraws[0][playerid], 0.260999, 2.238816);
    PlayerTextDrawTextSize(playerid, menu_ptextdraws[0][playerid], 171.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, menu_ptextdraws[0][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, menu_ptextdraws[0][playerid], -1);
    PlayerTextDrawUseBox(playerid, menu_ptextdraws[0][playerid], true);
    PlayerTextDrawBoxColor(playerid, menu_ptextdraws[0][playerid], -1);
    PlayerTextDrawSetShadow(playerid, menu_ptextdraws[0][playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, menu_ptextdraws[0][playerid], 255);
    PlayerTextDrawFont(playerid, menu_ptextdraws[0][playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, menu_ptextdraws[0][playerid], true);

    // Titulo
    menu_ptextdraws[1][playerid] = CreatePlayerTextDraw(playerid, 49.000000, 170.000000, "Titulo");
    PlayerTextDrawLetterSize(playerid, menu_ptextdraws[1][playerid], 0.315334, 1.619629);
    PlayerTextDrawAlignment(playerid, menu_ptextdraws[1][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, menu_ptextdraws[1][playerid], 0x000000FF);
    PlayerTextDrawSetShadow(playerid, menu_ptextdraws[1][playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, menu_ptextdraws[1][playerid], 255);
    PlayerTextDrawFont(playerid, menu_ptextdraws[1][playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawSetProportional(playerid, menu_ptextdraws[1][playerid], true);

    // Parte superior primaria
    // Espaçamento 1: "Categoria                                        Itens"
    // Espaçamento 2: "Nome do item             Unidades                Valor"
    menu_ptextdraws[2][playerid] = CreatePlayerTextDraw(playerid, 43.500000, 193.000000, "espacamento");
    PlayerTextDrawLetterSize(playerid, menu_ptextdraws[2][playerid], 0.130332, 0.738444);
    PlayerTextDrawTextSize(playerid, menu_ptextdraws[2][playerid], 170.900177, 0.000000);
    PlayerTextDrawAlignment(playerid, menu_ptextdraws[2][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, menu_ptextdraws[2][playerid], -2139062017);
    PlayerTextDrawUseBox(playerid, menu_ptextdraws[2][playerid], true);
    PlayerTextDrawBoxColor(playerid, menu_ptextdraws[2][playerid], 170);
    PlayerTextDrawSetShadow(playerid, menu_ptextdraws[2][playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, menu_ptextdraws[2][playerid], 255);
    PlayerTextDrawFont(playerid, menu_ptextdraws[2][playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, menu_ptextdraws[2][playerid], true);

    // Numero de itens
    menu_ptextdraws[3][playerid] = CreatePlayerTextDraw(playerid, 170.000000, 316.000000, "00/00");
    PlayerTextDrawLetterSize(playerid, menu_ptextdraws[3][playerid], 0.146666, 0.828444);
    PlayerTextDrawTextSize(playerid, menu_ptextdraws[3][playerid], 146.909194, 0.000000);
    PlayerTextDrawAlignment(playerid, menu_ptextdraws[3][playerid], TEXT_DRAW_ALIGN_RIGHT);
    PlayerTextDrawColor(playerid, menu_ptextdraws[3][playerid], -1061109505);
    PlayerTextDrawSetShadow(playerid, menu_ptextdraws[3][playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, menu_ptextdraws[3][playerid], 255);
    PlayerTextDrawFont(playerid, menu_ptextdraws[3][playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, menu_ptextdraws[3][playerid], true);

    // Itens
    for(new text; text < sizeof(menu_pstextdraws); text++) {
        menu_pstextdraws[text][playerid] = CreatePlayerTextDraw(playerid, 43.500000, (text * 10.50) + 203.000000, "Nome do item");
        PlayerTextDrawLetterSize(playerid, menu_pstextdraws[text][playerid], 0.160666, 0.799407);
        PlayerTextDrawTextSize(playerid, menu_pstextdraws[text][playerid], 170.500000, 0.000000);
        PlayerTextDrawAlignment(playerid, menu_pstextdraws[text][playerid], TEXT_DRAW_ALIGN_LEFT);
        PlayerTextDrawColor(playerid, menu_pstextdraws[text][playerid], -1);
        PlayerTextDrawUseBox(playerid, menu_pstextdraws[text][playerid], true);
        PlayerTextDrawBoxColor(playerid, menu_pstextdraws[text][playerid], 0x00000000);
        PlayerTextDrawSetShadow(playerid, menu_pstextdraws[text][playerid], 0);
        PlayerTextDrawBackgroundColor(playerid, menu_pstextdraws[text][playerid], 255);
        PlayerTextDrawFont(playerid, menu_pstextdraws[text][playerid], TEXT_DRAW_FONT_1);
        PlayerTextDrawSetProportional(playerid, menu_pstextdraws[text][playerid], true);
    }

    for(new text; text < sizeof(menu_pqtextdraws); text++) {
        menu_pqtextdraws[text][playerid] = CreatePlayerTextDraw(playerid, 170.000000, (text * 10.50) + 203.000000, "Quantidade");
        PlayerTextDrawLetterSize(playerid, menu_pqtextdraws[text][playerid], 0.160666, 0.799407);
        PlayerTextDrawTextSize(playerid, menu_pqtextdraws[text][playerid], 146.719116, 0.000000);
        PlayerTextDrawAlignment(playerid, menu_pqtextdraws[text][playerid], TEXT_DRAW_ALIGN_RIGHT);
        PlayerTextDrawColor(playerid, menu_pqtextdraws[text][playerid], -1);
        PlayerTextDrawSetShadow(playerid, menu_pqtextdraws[text][playerid], 0);
        PlayerTextDrawBackgroundColor(playerid, menu_pqtextdraws[text][playerid], 255);
        PlayerTextDrawFont(playerid, menu_pqtextdraws[text][playerid], TEXT_DRAW_FONT_1);
        PlayerTextDrawSetProportional(playerid, menu_pqtextdraws[text][playerid], true);
    }
}

stock CreateTextdraws_MenuModern() 
{
    menu_textdraws[0] = TextDrawCreate(107.000000, 192.000000, "_");
    TextDrawLetterSize(menu_textdraws[0], 0.335999, 14.645928);
    TextDrawTextSize(menu_textdraws[0], 0.000000, 127.000000);
    TextDrawAlignment(menu_textdraws[0], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(menu_textdraws[0], -1);
    TextDrawUseBox(menu_textdraws[0], true);
    TextDrawBoxColor(menu_textdraws[0], 144);
    TextDrawSetShadow(menu_textdraws[0], 0);
    TextDrawBackgroundColor(menu_textdraws[0], 255);
    TextDrawFont(menu_textdraws[0], TEXT_DRAW_FONT_1);
    TextDrawSetProportional(menu_textdraws[0], true);

    menu_textdraws[1] = TextDrawCreate(43.500000, 316.000000, "Selecao do menu");
    TextDrawLetterSize(menu_textdraws[1], 0.146666, 0.828444);
    TextDrawTextSize(menu_textdraws[1], 170.500000, 0.000000);
    TextDrawAlignment(menu_textdraws[1], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(menu_textdraws[1], -2139062017);
    TextDrawUseBox(menu_textdraws[1], true);
    TextDrawBoxColor(menu_textdraws[1], 170);
    TextDrawSetShadow(menu_textdraws[1], 0);
    TextDrawBackgroundColor(menu_textdraws[1], 255);
    TextDrawFont(menu_textdraws[1], TEXT_DRAW_FONT_2);
    TextDrawSetProportional(menu_textdraws[1], true);

    menu_textdraws[2] = TextDrawCreate(107.000000, 307.700000, "V");
    TextDrawLetterSize(menu_textdraws[2], 0.184664, 0.498443);
    TextDrawTextSize(menu_textdraws[2], 2.669996, 126.120025);
    TextDrawAlignment(menu_textdraws[2], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(menu_textdraws[2], -1);
    TextDrawUseBox(menu_textdraws[2], true);
    TextDrawBoxColor(menu_textdraws[2], 170);
    TextDrawSetShadow(menu_textdraws[2], 0);
    TextDrawBackgroundColor(menu_textdraws[2], 255);
    TextDrawFont(menu_textdraws[2], TEXT_DRAW_FONT_2);
    TextDrawSetProportional(menu_textdraws[2], true);
    TextDrawSetSelectable(menu_textdraws[2], true);
}