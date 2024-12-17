new Text:store_td_prevpage,
    Text:store_td_nextpage,
	PlayerText:store_ptd_page[MAX_PLAYERS],
	PlayerText:store_ptd_preview[MAX_STORE_SLOT_PERPAGE][MAX_PLAYERS],
	PlayerText:store_ptd_qtd[MAX_STORE_SLOT_PERPAGE][MAX_PLAYERS],
	PlayerText:store_ptd_price[MAX_STORE_SLOT_PERPAGE][MAX_PLAYERS];

stock Textdraws_CreateStore()
{
	store_td_prevpage = TextDrawCreate(110.000, 415.000, "<<<");
    TextDrawLetterSize(store_td_prevpage, 0.158, 1.297);
    TextDrawTextSize(store_td_prevpage, 10.000, 70.000);
    TextDrawAlignment(store_td_prevpage, TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(store_td_prevpage, -1);
    TextDrawUseBox(store_td_prevpage, true);
    TextDrawBoxColor(store_td_prevpage, 16);
    TextDrawSetShadow(store_td_prevpage, 0);
    TextDrawSetOutline(store_td_prevpage, 0);
    TextDrawBackgroundColor(store_td_prevpage, 255);
    TextDrawFont(store_td_prevpage, TEXT_DRAW_FONT_3);
    TextDrawSetProportional(store_td_prevpage, true);
    TextDrawSetSelectable(store_td_prevpage, true);

    store_td_nextpage = TextDrawCreate(214.000, 415.000, ">>>");
    TextDrawLetterSize(store_td_nextpage, 0.158, 1.296);
    TextDrawTextSize(store_td_nextpage, 10.000, 70.000);
    TextDrawAlignment(store_td_nextpage, TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(store_td_nextpage, -1);
    TextDrawUseBox(store_td_nextpage, true);
    TextDrawBoxColor(store_td_nextpage, 16);
    TextDrawSetShadow(store_td_nextpage, 0);
    TextDrawSetOutline(store_td_nextpage, 0);
    TextDrawBackgroundColor(store_td_nextpage, 255);
    TextDrawFont(store_td_nextpage, TEXT_DRAW_FONT_1);
    TextDrawSetProportional(store_td_nextpage, true);
    TextDrawSetSelectable(store_td_nextpage, true);
}

stock Textdraws_CreatePlayerStore(playerid)
{
	store_ptd_page[playerid] = CreatePlayerTextDraw(playerid, 162.000, 414.000, "_");
    PlayerTextDrawLetterSize(playerid, store_ptd_page[playerid], 0.218, 1.199);
    PlayerTextDrawTextSize(playerid, store_ptd_page[playerid], 9.000, 113.000);
    PlayerTextDrawAlignment(playerid, store_ptd_page[playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, store_ptd_page[playerid], 1768516095);
    PlayerTextDrawSetShadow(playerid, store_ptd_page[playerid], 0);
    PlayerTextDrawSetOutline(playerid, store_ptd_page[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, store_ptd_page[playerid], 255);
    PlayerTextDrawFont(playerid, store_ptd_page[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawSetProportional(playerid, store_ptd_page[playerid], true);

    new Float:item_posX,
		Float:item_posY,
		Float:qtd_posX,
		Float:qtd_posY,
		Float:price_posX,
		Float:price_posY;
		// Float:rarity_posX,
		// Float:rarity_posZ;

    for (new slot; slot < MAX_STORE_SLOT_PERPAGE; slot++) 
	{
		switch (slot) {
			case 0..2: {
				item_posX = 75.00 + (60.00 * slot);
				item_posY = 109.00;

				qtd_posX = 130.00 + (58.00 * slot);
				qtd_posY = 158.00;

                price_posX = 130.00 + (58.00 * slot);
                price_posY = 165.00;

				// rarity_posX = 262.000 + (60.00 * slot);
				// rarity_posY = 125.000;
			}
			case 3..5: {
				item_posX = 75.00 + (60.00 * (slot - 3));
				item_posY = 109.00 + 67.00;

				qtd_posX = 130.00 + (58.00 * (slot - 3));
				qtd_posY = 158.00 + 67.00;

                price_posX = 130.00 + (58.00 * (slot - 3));
                price_posY = 165.00 + 67.00;

				// rarity_posX = 262.000 + (60.00 * (slot - 3));
				// rarity_posY = 125.000 + 70.00;
			}
			case 6..8: {
				item_posX = 75.00 + (60.00 * (slot - 6));
				item_posY = 109.00 + (67.00 * 2);

				qtd_posX = 130.00 + (58.00 * (slot - 6));
				qtd_posY = 158.00 + (67.00 * 2);

                price_posX = 130.00 + (58.00 * (slot - 6));
                price_posY = 165.00 + (67.00 * 2);

				// rarity_posX = 262.000 + (60.00 * (slot - 6));
				// rarity_posY = 125.000 + (70.00 * 2);
			}
			case 9..11: {
				item_posX = 75.00 + (60.00 * (slot - 9));
				item_posY = 109.00 + (67.00 * 3);

				qtd_posX = 130.00 + (58.00 * (slot - 9));
				qtd_posY = 158.00 + (67.00 * 3);

                price_posX = 130.00 + (58.00 * (slot - 9));
                price_posY = 165.00 + (67.00 * 3);

				// rarity_posX = 262.000 + (60.00 * (slot - 11));
				// rarity_posY = 125.000 + (70.00 * 3);
			}
		}
        store_ptd_preview[slot][playerid] = CreatePlayerTextDraw(playerid, item_posX, item_posY, "_");
        PlayerTextDrawTextSize(playerid, store_ptd_preview[slot][playerid], 57.000, 66.000);
        PlayerTextDrawAlignment(playerid, store_ptd_preview[slot][playerid], TEXT_DRAW_ALIGN_LEFT);
        PlayerTextDrawColor(playerid, store_ptd_preview[slot][playerid], -1);
        PlayerTextDrawSetShadow(playerid, store_ptd_preview[slot][playerid], 0);
        PlayerTextDrawSetOutline(playerid, store_ptd_preview[slot][playerid], 0);
        PlayerTextDrawBackgroundColor(playerid, store_ptd_preview[slot][playerid], 130);
        PlayerTextDrawFont(playerid, store_ptd_preview[slot][playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
        PlayerTextDrawSetProportional(playerid, store_ptd_preview[slot][playerid], false);
        PlayerTextDrawSetPreviewModel(playerid, store_ptd_preview[slot][playerid], 0);
        PlayerTextDrawSetPreviewRot(playerid, store_ptd_preview[slot][playerid], -30.000, 0.000, -30.000, 1.100);
        PlayerTextDrawSetPreviewVehCol(playerid, store_ptd_preview[slot][playerid], 0, 0);
        PlayerTextDrawSetSelectable(playerid, store_ptd_preview[slot][playerid], true);

        store_ptd_qtd[slot][playerid] = CreatePlayerTextDraw(playerid, qtd_posX, qtd_posY, "1.000.000.000");
        PlayerTextDrawLetterSize(playerid, store_ptd_qtd[slot][playerid], 0.138, 0.898);
        PlayerTextDrawAlignment(playerid, store_ptd_qtd[slot][playerid], TEXT_DRAW_ALIGN_RIGHT);
        PlayerTextDrawColor(playerid, store_ptd_qtd[slot][playerid], 1768516095);
        PlayerTextDrawSetShadow(playerid, store_ptd_qtd[slot][playerid], 0);
        PlayerTextDrawSetOutline(playerid, store_ptd_qtd[slot][playerid], 0);
        PlayerTextDrawBackgroundColor(playerid, store_ptd_qtd[slot][playerid], 255);
        PlayerTextDrawFont(playerid, store_ptd_qtd[slot][playerid], TEXT_DRAW_FONT_2);
        PlayerTextDrawSetProportional(playerid, store_ptd_qtd[slot][playerid], true);

        store_ptd_price[slot][playerid] = CreatePlayerTextDraw(playerid, price_posX, price_posY, "~b~C$ ~w~1.000.000.000");
        PlayerTextDrawLetterSize(playerid, store_ptd_price[slot][playerid], 0.138, 0.898);
        PlayerTextDrawAlignment(playerid, store_ptd_price[slot][playerid], TEXT_DRAW_ALIGN_RIGHT);
        PlayerTextDrawColor(playerid, store_ptd_price[slot][playerid], -1);
        PlayerTextDrawSetShadow(playerid, store_ptd_price[slot][playerid], 0);
        PlayerTextDrawSetOutline(playerid, store_ptd_price[slot][playerid], 0);
        PlayerTextDrawBackgroundColor(playerid, store_ptd_price[slot][playerid], 255);
        PlayerTextDrawFont(playerid, store_ptd_price[slot][playerid], TEXT_DRAW_FONT_2);
        PlayerTextDrawSetProportional(playerid, store_ptd_price[slot][playerid], true);

        printf("slot created: %d %.2f %.2f %.2f %.2f %.2f %.2f", slot, item_posX, item_posY, qtd_posX, qtd_posY, price_posX, price_posY);

        // store_ptd_rarity[slot][playerid] = CreatePlayerTextDraw(playerid, rarity_posX, rarity_posY, "COMUM");
        // PlayerTextDrawLetterSize(playerid, store_ptd_rarity[slot][playerid], 0.119, 0.597);
        // PlayerTextDrawTextSize(playerid, store_ptd_rarity[slot][playerid], -3.000, -4.000);
        // PlayerTextDrawAlignment(playerid, store_ptd_rarity[slot][playerid], TEXT_DRAW_ALIGN_LEFT);
        // PlayerTextDrawColor(playerid, store_ptd_rarity[slot][playerid], 2096889916);
        // PlayerTextDrawSetShadow(playerid, store_ptd_rarity[slot][playerid], 0);
        // PlayerTextDrawSetOutline(playerid, store_ptd_rarity[slot][playerid], 0);
        // PlayerTextDrawBackgroundColor(playerid, store_ptd_rarity[slot][playerid], 255);
        // PlayerTextDrawFont(playerid, store_ptd_rarity[slot][playerid], TEXT_DRAW_FONT_2);
        // PlayerTextDrawSetProportional(playerid, store_ptd_rarity[slot][playerid], true);
    }
}