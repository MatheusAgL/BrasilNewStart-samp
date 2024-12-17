#include <YSI_Coding\y_hooks>

new Text:inv_background[7],
	Text:inv_botton_use,
	Text:inv_botton_combine,
	Text:inv_botton_move,
	Text:inv_botton_discard,
	Text:inv_botton_separate,
	Text:inv_botton_prevpage,
	Text:inv_botton_nextpage,
	Text:inv_botton_organize,
	Text:inv_botton_trade,
	Text:inv_botton_close,
	PlayerText:inv_item_selected[3][MAX_PLAYERS],
	PlayerText:inv_page_number[MAX_PLAYERS],
	PlayerText:inv_total_items[MAX_PLAYERS],
	PlayerText:inv_item_preview[MAX_INV_SLOT_PERPAGE][MAX_PLAYERS],
	PlayerText:inv_item_preview_qtd[MAX_INV_SLOT_PERPAGE][MAX_PLAYERS],
	PlayerText:inv_item_preview_rarity[MAX_INV_SLOT_PERPAGE][MAX_PLAYERS];

stock CreateTD_Inventory()
{
	inv_background[0] = TextDrawCreate(409.000, 105.000, "_");
	TextDrawLetterSize(inv_background[0], 0.300, 36.097);
	TextDrawTextSize(inv_background[0], 2.000, 309.000);
	TextDrawAlignment(inv_background[0], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_background[0], -1);
	TextDrawUseBox(inv_background[0], true);
	TextDrawBoxColor(inv_background[0], 165);
	TextDrawSetShadow(inv_background[0], 1);
	TextDrawSetOutline(inv_background[0], 1);
	TextDrawBackgroundColor(inv_background[0], 421097727);
	TextDrawFont(inv_background[0], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(inv_background[0], true);

	inv_background[1] = TextDrawCreate(162.000, 105.000, "_");
	TextDrawLetterSize(inv_background[1], 0.300, 36.097);
	TextDrawTextSize(inv_background[1], 2.000, 179.000);
	TextDrawAlignment(inv_background[1], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_background[1], -1);
	TextDrawUseBox(inv_background[1], true);
	TextDrawBoxColor(inv_background[1], 165);
	TextDrawSetShadow(inv_background[1], 1);
	TextDrawSetOutline(inv_background[1], 1);
	TextDrawBackgroundColor(inv_background[1], 421097727);
	TextDrawFont(inv_background[1], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(inv_background[1], true);

	// Background (usar/mover/combinar...)
	inv_background[2] = TextDrawCreate(165.000, 310.000, "_");
	TextDrawLetterSize(inv_background[2], 0.188, 1.797);
	TextDrawTextSize(inv_background[2], 10.000, 118.000);
	TextDrawAlignment(inv_background[2], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_background[2], -1);
	TextDrawUseBox(inv_background[2], true);
	TextDrawBoxColor(inv_background[2], 50);
	TextDrawSetShadow(inv_background[2], 0);
	TextDrawSetOutline(inv_background[2], 0);
	TextDrawBackgroundColor(inv_background[2], 255);
	TextDrawFont(inv_background[2], TEXT_DRAW_FONT_2);
	TextDrawSetProportional(inv_background[2], true);
	TextDrawSetSelectable(inv_background[2], true);

	inv_background[3] = TextDrawCreate(165.000, 330.000, "_");
	TextDrawLetterSize(inv_background[3], 0.188, 1.797);
	TextDrawTextSize(inv_background[3], 10.000, 118.000);
	TextDrawAlignment(inv_background[3], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_background[3], -1);
	TextDrawUseBox(inv_background[3], true);
	TextDrawBoxColor(inv_background[3], 50);
	TextDrawSetShadow(inv_background[3], 0);
	TextDrawSetOutline(inv_background[3], 0);
	TextDrawBackgroundColor(inv_background[3], 255);
	TextDrawFont(inv_background[3], TEXT_DRAW_FONT_2);
	TextDrawSetProportional(inv_background[3], true);
	TextDrawSetSelectable(inv_background[3], true);

	inv_background[4] = TextDrawCreate(165.000, 350.000, "_");
	TextDrawLetterSize(inv_background[4], 0.188, 1.797);
	TextDrawTextSize(inv_background[4], 10.000, 118.000);
	TextDrawAlignment(inv_background[4], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_background[4], -1);
	TextDrawUseBox(inv_background[4], true);
	TextDrawBoxColor(inv_background[4], 50);
	TextDrawSetShadow(inv_background[4], 0);
	TextDrawSetOutline(inv_background[4], 0);
	TextDrawBackgroundColor(inv_background[4], 255);
	TextDrawFont(inv_background[4], TEXT_DRAW_FONT_2);
	TextDrawSetProportional(inv_background[4], true);
	TextDrawSetSelectable(inv_background[4], true);

	inv_background[5] = TextDrawCreate(165.000, 370.000, "_");
	TextDrawLetterSize(inv_background[5], 0.188, 1.797);
	TextDrawTextSize(inv_background[5], 10.000, 118.000);
	TextDrawAlignment(inv_background[5], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_background[5], -1);
	TextDrawUseBox(inv_background[5], true);
	TextDrawBoxColor(inv_background[5], 50);
	TextDrawSetShadow(inv_background[5], 0);
	TextDrawSetOutline(inv_background[5], 0);
	TextDrawBackgroundColor(inv_background[5], 255);
	TextDrawFont(inv_background[5], TEXT_DRAW_FONT_2);
	TextDrawSetProportional(inv_background[5], true);
	TextDrawSetSelectable(inv_background[5], true);

	inv_background[6] = TextDrawCreate(165.000, 390.000, "_");
	TextDrawLetterSize(inv_background[6], 0.188, 1.797);
	TextDrawTextSize(inv_background[6], 10.000, 118.000);
	TextDrawAlignment(inv_background[6], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_background[6], -1);
	TextDrawUseBox(inv_background[6], true);
	TextDrawBoxColor(inv_background[6], 50);
	TextDrawSetShadow(inv_background[6], 0);
	TextDrawSetOutline(inv_background[6], 0);
	TextDrawBackgroundColor(inv_background[6], 255);
	TextDrawFont(inv_background[6], TEXT_DRAW_FONT_2);
	TextDrawSetProportional(inv_background[6], true);
	TextDrawSetSelectable(inv_background[6], true);

	inv_botton_close = TextDrawCreate(529.000, 108.000, "Fechar");
	TextDrawLetterSize(inv_botton_close, 0.269, 1.297);
	TextDrawTextSize(inv_botton_close, 10.000, 57.000);
	TextDrawAlignment(inv_botton_close, TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_botton_close, -1);
	TextDrawUseBox(inv_botton_close, true);
	TextDrawBoxColor(inv_botton_close, -2147483578);
	TextDrawSetShadow(inv_botton_close, 0);
	TextDrawSetOutline(inv_botton_close, 0);
	TextDrawBackgroundColor(inv_botton_close, 255);
	TextDrawFont(inv_botton_close, TEXT_DRAW_FONT_2);
	TextDrawSetProportional(inv_botton_close, true);
	TextDrawSetSelectable(inv_botton_close, true);

	inv_botton_use = TextDrawCreate(165.000, 312.000, "Usar");
	TextDrawLetterSize(inv_botton_use, 0.280, 1.199);
	TextDrawTextSize(inv_botton_use, 10.000, 113.000);
	TextDrawAlignment(inv_botton_use, TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_botton_use, 1768516095);
	TextDrawSetShadow(inv_botton_use, 0);
	TextDrawSetOutline(inv_botton_use, 0);
	TextDrawBackgroundColor(inv_botton_use, 255);
	TextDrawFont(inv_botton_use, TEXT_DRAW_FONT_1);
	TextDrawSetProportional(inv_botton_use, true);
	TextDrawSetSelectable(inv_botton_use, true);

	inv_botton_move = TextDrawCreate(165.000, 332.000, "Mover");
	TextDrawLetterSize(inv_botton_move, 0.280, 1.199);
	TextDrawTextSize(inv_botton_move, 10.000, 113.000);
	TextDrawAlignment(inv_botton_move, TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_botton_move, 1768516095);
	TextDrawSetShadow(inv_botton_move, 0);
	TextDrawSetOutline(inv_botton_move, 0);
	TextDrawBackgroundColor(inv_botton_move, 255);
	TextDrawFont(inv_botton_move, TEXT_DRAW_FONT_1);
	TextDrawSetProportional(inv_botton_move, true);
	TextDrawSetSelectable(inv_botton_move, true);

	inv_botton_combine = TextDrawCreate(165.000, 352.000, "Combinar");
	TextDrawLetterSize(inv_botton_combine, 0.280, 1.199);
	TextDrawTextSize(inv_botton_combine, 10.000, 113.000);
	TextDrawAlignment(inv_botton_combine, TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_botton_combine, 1768516095);
	TextDrawSetShadow(inv_botton_combine, 0);
	TextDrawSetOutline(inv_botton_combine, 0);
	TextDrawBackgroundColor(inv_botton_combine, 255);
	TextDrawFont(inv_botton_combine, TEXT_DRAW_FONT_1);
	TextDrawSetProportional(inv_botton_combine, true);
	TextDrawSetSelectable(inv_botton_combine, true);

	inv_botton_separate = TextDrawCreate(165.000, 372.000, "Separar");
	TextDrawLetterSize(inv_botton_separate, 0.280, 1.199);
	TextDrawTextSize(inv_botton_separate, 10.000, 113.000);
	TextDrawAlignment(inv_botton_separate, TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_botton_separate, 1768516095);
	TextDrawSetShadow(inv_botton_separate, 0);
	TextDrawSetOutline(inv_botton_separate, 0);
	TextDrawBackgroundColor(inv_botton_separate, 255);
	TextDrawFont(inv_botton_separate, TEXT_DRAW_FONT_1);
	TextDrawSetProportional(inv_botton_separate, true);
	TextDrawSetSelectable(inv_botton_separate, true);

	inv_botton_discard = TextDrawCreate(165.000, 392.000, "Descartar");
	TextDrawLetterSize(inv_botton_discard, 0.280, 1.199);
	TextDrawTextSize(inv_botton_discard, 10.000, 113.000);
	TextDrawAlignment(inv_botton_discard, TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_botton_discard, 1768516095);
	TextDrawSetShadow(inv_botton_discard, 0);
	TextDrawSetOutline(inv_botton_discard, 0);
	TextDrawBackgroundColor(inv_botton_discard, 255);
	TextDrawFont(inv_botton_discard, TEXT_DRAW_FONT_1);
	TextDrawSetProportional(inv_botton_discard, true);
	TextDrawSetSelectable(inv_botton_discard, true);

	inv_botton_organize = TextDrawCreate(286.000, 415.000, "Organizar");
	TextDrawLetterSize(inv_botton_organize, 0.219, 1.297);
	TextDrawTextSize(inv_botton_organize, 10.000, 57.000);
	TextDrawAlignment(inv_botton_organize, TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_botton_organize, -1);
	TextDrawUseBox(inv_botton_organize, true);
	TextDrawBoxColor(inv_botton_organize, 1768515880);
	TextDrawSetShadow(inv_botton_organize, 0);
	TextDrawSetOutline(inv_botton_organize, 0);
	TextDrawBackgroundColor(inv_botton_organize, 255);
	TextDrawFont(inv_botton_organize, TEXT_DRAW_FONT_2);
	TextDrawSetProportional(inv_botton_organize, true);
	TextDrawSetSelectable(inv_botton_organize, true);

	inv_botton_trade = TextDrawCreate(347.000, 415.000, "Negociar");
	TextDrawLetterSize(inv_botton_trade, 0.239, 1.297);
	TextDrawTextSize(inv_botton_trade, 10.000, 57.000);
	TextDrawAlignment(inv_botton_trade, TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_botton_trade, -1);
	TextDrawUseBox(inv_botton_trade, true);
	TextDrawBoxColor(inv_botton_trade, -2139094990);
	TextDrawSetShadow(inv_botton_trade, 0);
	TextDrawSetOutline(inv_botton_trade, 0);
	TextDrawBackgroundColor(inv_botton_trade, 255);
	TextDrawFont(inv_botton_trade, TEXT_DRAW_FONT_2);
	TextDrawSetProportional(inv_botton_trade, true);
	TextDrawSetSelectable(inv_botton_trade, true);

	inv_botton_prevpage = TextDrawCreate(415.000, 415.000, "<<<");
	TextDrawLetterSize(inv_botton_prevpage, 0.158, 1.297);
	TextDrawTextSize(inv_botton_prevpage, 10.000, 70.000);
	TextDrawAlignment(inv_botton_prevpage, TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_botton_prevpage, -1);
	TextDrawUseBox(inv_botton_prevpage, true);
	TextDrawBoxColor(inv_botton_prevpage, 16);
	TextDrawSetShadow(inv_botton_prevpage, 0);
	TextDrawSetOutline(inv_botton_prevpage, 0);
	TextDrawBackgroundColor(inv_botton_prevpage, 255);
	TextDrawFont(inv_botton_prevpage, TEXT_DRAW_FONT_3);
	TextDrawSetProportional(inv_botton_prevpage, true);
	TextDrawSetSelectable(inv_botton_prevpage, true);

	inv_botton_nextpage = TextDrawCreate(526.000, 415.000, ">>>");
	TextDrawLetterSize(inv_botton_nextpage, 0.158, 1.296);
	TextDrawTextSize(inv_botton_nextpage, 10.000, 70.000);
	TextDrawAlignment(inv_botton_nextpage, TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(inv_botton_nextpage, -1);
	TextDrawUseBox(inv_botton_nextpage, true);
	TextDrawBoxColor(inv_botton_nextpage, 16);
	TextDrawSetShadow(inv_botton_nextpage, 0);
	TextDrawSetOutline(inv_botton_nextpage, 0);
	TextDrawBackgroundColor(inv_botton_nextpage, 255);
	TextDrawFont(inv_botton_nextpage, TEXT_DRAW_FONT_1);
	TextDrawSetProportional(inv_botton_nextpage, true);
	TextDrawSetSelectable(inv_botton_nextpage, true);
}

stock CreatePlayerTD_Inventory(playerid)
{
	inv_item_selected[0][playerid] = CreatePlayerTextDraw(playerid, 105.000, 124.000, "_"); // Item
	PlayerTextDrawTextSize(playerid, inv_item_selected[0][playerid], 124.000, 124.000);
	PlayerTextDrawAlignment(playerid, inv_item_selected[0][playerid], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, inv_item_selected[0][playerid], -1);
	PlayerTextDrawSetShadow(playerid, inv_item_selected[0][playerid], 0);
	PlayerTextDrawSetOutline(playerid, inv_item_selected[0][playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, inv_item_selected[0][playerid], 130);
	PlayerTextDrawFont(playerid, inv_item_selected[0][playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawSetProportional(playerid, inv_item_selected[0][playerid], false);
	PlayerTextDrawSetPreviewModel(playerid, inv_item_selected[0][playerid], -1);
	PlayerTextDrawSetPreviewRot(playerid, inv_item_selected[0][playerid], -30.000, 0.000, -30.000, 1.100);
	PlayerTextDrawSetPreviewVehCol(playerid, inv_item_selected[0][playerid], 0, 0);

	inv_item_selected[1][playerid] = CreatePlayerTextDraw(playerid, 165.000, 244.000, "_"); // Nome do item
	PlayerTextDrawLetterSize(playerid, inv_item_selected[1][playerid], 0.219, 1.098);
	PlayerTextDrawAlignment(playerid, inv_item_selected[1][playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, inv_item_selected[1][playerid], -1);
	PlayerTextDrawSetShadow(playerid, inv_item_selected[1][playerid], 0);
	PlayerTextDrawSetOutline(playerid, inv_item_selected[1][playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, inv_item_selected[1][playerid], 255);
	PlayerTextDrawFont(playerid, inv_item_selected[1][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawSetProportional(playerid, inv_item_selected[1][playerid], true);

	inv_item_selected[2][playerid] = CreatePlayerTextDraw(playerid, 106.000, 261.000, "_"); // Descri��o do item
	PlayerTextDrawLetterSize(playerid, inv_item_selected[2][playerid], 0.150, 0.999);
	PlayerTextDrawTextSize(playerid, inv_item_selected[2][playerid], 209.000, 0.000);
	PlayerTextDrawAlignment(playerid, inv_item_selected[2][playerid], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, inv_item_selected[2][playerid], 1768516095);
	PlayerTextDrawSetShadow(playerid, inv_item_selected[2][playerid], 0);
	PlayerTextDrawSetOutline(playerid, inv_item_selected[2][playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, inv_item_selected[2][playerid], 255);
	PlayerTextDrawFont(playerid, inv_item_selected[2][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawSetProportional(playerid, inv_item_selected[2][playerid], true);

	inv_page_number[playerid] = CreatePlayerTextDraw(playerid, 470.000, 414.000, "Pagina 3");
	PlayerTextDrawLetterSize(playerid, inv_page_number[playerid], 0.219, 1.199);
	PlayerTextDrawTextSize(playerid, inv_page_number[playerid], 9.000, 113.000);
	PlayerTextDrawAlignment(playerid, inv_page_number[playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, inv_page_number[playerid], 1768516095);
	PlayerTextDrawSetShadow(playerid, inv_page_number[playerid], 0);
	PlayerTextDrawSetOutline(playerid, inv_page_number[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, inv_page_number[playerid], 255);
	PlayerTextDrawFont(playerid, inv_page_number[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawSetProportional(playerid, inv_page_number[playerid], true);

	inv_total_items[playerid] = CreatePlayerTextDraw(playerid, 379.000, 109.000, "itens 0/80");
	PlayerTextDrawLetterSize(playerid, inv_total_items[playerid], 0.180, 0.898);
	PlayerTextDrawTextSize(playerid, inv_total_items[playerid], 9.000, 113.000);
	PlayerTextDrawAlignment(playerid, inv_total_items[playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, inv_total_items[playerid], 1768516095);
	PlayerTextDrawSetShadow(playerid, inv_total_items[playerid], 0);
	PlayerTextDrawSetOutline(playerid, inv_total_items[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, inv_total_items[playerid], 255);
	PlayerTextDrawFont(playerid, inv_total_items[playerid], TEXT_DRAW_FONT_2);
	PlayerTextDrawSetProportional(playerid, inv_total_items[playerid], true);

	// Slots do invent�rio
	new Float:item_posX,
		Float:item_posY,
		Float:qtd_posX,
		Float:qtd_posY,
		Float:rarity_posX,
		Float:rarity_posY;

	for (new loop; loop < MAX_INV_SLOT_PERPAGE; loop++) 
	{
		switch (loop) {
			case 0..4: {
				item_posX = 260.00 + (60.00 * loop);
				item_posY = 124.00;

				qtd_posX = 317.00 + (60.00 * loop);
				qtd_posY = 183.00;

				rarity_posX = 262.000 + (60.00 * loop);
				rarity_posY = 125.000;
			}
			case 5..9: {
				item_posX = 260.00 + (60.00 * (loop - 5));
				item_posY = 124.00 + 70.00;

				qtd_posX = 317.00 + (60.00 * (loop - 5));
				qtd_posY = 183.00 + 69.00;

				rarity_posX = 262.000 + (60.00 * (loop - 5));
				rarity_posY = 125.000 + 70.00;
			}
			case 10..14: {
				item_posX = 260.00 + (60.00 * (loop - 10));
				item_posY = 124.00 + (70.00 * 2);

				qtd_posX = 317.00 + (60.00 * (loop - 10));
				qtd_posY = 183.00 + (69.00 * 2);

				rarity_posX = 262.000 + (60.00 * (loop - 10));
				rarity_posY = 125.000 + (70.00 * 2);
			}
			case 15..19: {
				item_posX = 260.00 + (60.00 * (loop - 15));
				item_posY = 124.00 + (70.00 * 3);

				qtd_posX = 317.00 + (60.00 * (loop - 15));
				qtd_posY = 183.00 + (69.00 * 3);

				rarity_posX = 262.000 + (60.00 * (loop - 15));
				rarity_posY = 125.000 + (70.00 * 3);
			}
		}

		inv_item_preview[loop][playerid] = CreatePlayerTextDraw(playerid, item_posX, item_posY, "_");
		PlayerTextDrawTextSize(playerid, inv_item_preview[loop][playerid], 59.000, 69.000);
		PlayerTextDrawAlignment(playerid, inv_item_preview[loop][playerid], TEXT_DRAW_ALIGN_LEFT);
		PlayerTextDrawColor(playerid, inv_item_preview[loop][playerid], -1);
		PlayerTextDrawSetShadow(playerid, inv_item_preview[loop][playerid], 0);
		PlayerTextDrawSetOutline(playerid, inv_item_preview[loop][playerid], 0);
		PlayerTextDrawBackgroundColor(playerid, inv_item_preview[loop][playerid], 130);
		PlayerTextDrawFont(playerid, inv_item_preview[loop][playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
		PlayerTextDrawSetProportional(playerid, inv_item_preview[loop][playerid], false);
		PlayerTextDrawSetPreviewModel(playerid, inv_item_preview[loop][playerid], -1);
		PlayerTextDrawSetPreviewRot(playerid, inv_item_preview[loop][playerid], -30.000, 0.000, -30.000, 1.100);
		PlayerTextDrawSetPreviewVehCol(playerid, inv_item_preview[loop][playerid], 0, 0);
		PlayerTextDrawSetSelectable(playerid, inv_item_preview[loop][playerid], true);

		inv_item_preview_qtd[loop][playerid] = CreatePlayerTextDraw(playerid, qtd_posX, qtd_posY, "_");
		PlayerTextDrawLetterSize(playerid, inv_item_preview_qtd[loop][playerid], 0.139, 0.898);
		PlayerTextDrawAlignment(playerid, inv_item_preview_qtd[loop][playerid], TEXT_DRAW_ALIGN_RIGHT);
		PlayerTextDrawColor(playerid, inv_item_preview_qtd[loop][playerid], 1768516095);
		PlayerTextDrawSetShadow(playerid, inv_item_preview_qtd[loop][playerid], 0);
		PlayerTextDrawSetOutline(playerid, inv_item_preview_qtd[loop][playerid], 0);
		PlayerTextDrawBackgroundColor(playerid, inv_item_preview_qtd[loop][playerid], 255);
		PlayerTextDrawFont(playerid, inv_item_preview_qtd[loop][playerid], TEXT_DRAW_FONT_2);
		PlayerTextDrawSetProportional(playerid, inv_item_preview_qtd[loop][playerid], true);

		inv_item_preview_rarity[loop][playerid] = CreatePlayerTextDraw(playerid, rarity_posX, rarity_posY, "_");
		PlayerTextDrawLetterSize(playerid, inv_item_preview_rarity[loop][playerid], 0.119, 0.597);
		PlayerTextDrawTextSize(playerid, inv_item_preview_rarity[loop][playerid], -3.000, -4.000);
		PlayerTextDrawAlignment(playerid, inv_item_preview_rarity[loop][playerid], TEXT_DRAW_ALIGN_LEFT);
		PlayerTextDrawColor(playerid, inv_item_preview_rarity[loop][playerid], 2096889916);
		// PlayerTextDrawColor(playerid, Text_Player[playerid][10], 512819014); Raro
		// PlayerTextDrawColor(playerid, inv_page_number[playerid], -1976835514); �pico
		// PlayerTextDrawColor(playerid, Text_Player[playerid][7], -12255162); Lendario
		// PlayerTextDrawColor(playerid, Text_Player[playerid][13], -16777146); Ultimate
		PlayerTextDrawSetShadow(playerid, inv_item_preview_rarity[loop][playerid], 0);
		PlayerTextDrawSetOutline(playerid, inv_item_preview_rarity[loop][playerid], 0);
		PlayerTextDrawBackgroundColor(playerid, inv_item_preview_rarity[loop][playerid], 255);
		PlayerTextDrawFont(playerid, inv_item_preview_rarity[loop][playerid], TEXT_DRAW_FONT_2);
		PlayerTextDrawSetProportional(playerid, inv_item_preview_rarity[loop][playerid], true);
	}
}