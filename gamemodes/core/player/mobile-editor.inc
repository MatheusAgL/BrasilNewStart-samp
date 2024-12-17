// Developer: iHollyZinhO

#if defined _INC_ac_editor_android
	#endinput
#endif
#define _INC_ac_editor_android

#include <YSI_Coding\y_hooks>

new PlayerText:tdMenuItem[MAX_PLAYERS][22];
new Float:velocidadeItem[] = {0.005, 0.01, 0.05, 0.1, 0.2, 0.5, 1.0};
new modosItem[][] = {"Posicao", "Rotacao", "Tamanho"};
new modosObjeto[][] = {"Posicao", "Rotacao"};

// TextDraws
CreateMenuEditorItem(playerid) {
	tdMenuItem[playerid][0] = CreatePlayerTextDraw(playerid, 150.000000, 138.000000, "_");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][0], TEXT_DRAW_FONT_0);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][0], 0.600000, 1.149981);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][0], 307.500000, 120.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][0], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][0], 200);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][0], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][0], false);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][0], false);

	tdMenuItem[playerid][1] = CreatePlayerTextDraw(playerid, 150.000000, 154.000000, "_");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][1], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][1], 0.600000, 4.599981);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][1], 296.000000, 120.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][1], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][1], 200);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][1], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][1], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][1], false);

	tdMenuItem[playerid][2] = CreatePlayerTextDraw(playerid, 127.000000, 136.000000, "EDITOR");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][2], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][2], 0.312500, 1.450000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][2], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][2], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][2], 1687547391);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][2], false);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][2], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][2], false);

	tdMenuItem[playerid][3] = CreatePlayerTextDraw(playerid, 93.000000, 153.000000, "~y~Item: ~w~Colete");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][3], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][3], 0.204167, 1.150000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][3], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][3], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][3], false);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][3], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][3], false);

	tdMenuItem[playerid][4] = CreatePlayerTextDraw(playerid, 93.000000, 184.000000, "~y~Velocidade: ~w~0.1");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][4], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][4], 0.204167, 1.150000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][4], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][4], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][4], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][4], false);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][4], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][4], false);

	tdMenuItem[playerid][5] = CreatePlayerTextDraw(playerid, 187.000000, 169.000000, "ALTERNAR");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][5], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][5], 0.133333, 0.950000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][5], 15.500000, 10.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][5], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][5], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][5], -2686721);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][5], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][5], 200);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][5], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][5], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][5], true);

	tdMenuItem[playerid][6] = CreatePlayerTextDraw(playerid, 150.000000, 201.000000, "_");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][6], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][6], 0.600000, 12.850012);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][6], 298.500000, 120.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][6], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][6], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][6], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][6], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][6], 200);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][6], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][6], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][6], false);

	tdMenuItem[playerid][7] = CreatePlayerTextDraw(playerid, 114.000000, 213.000000, "ld_beat:left");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][7], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][7], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][7], 22.500000, 24.500000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][7], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][7], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][7], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][7], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][7], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][7], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][7], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][7], true);

	tdMenuItem[playerid][8] = CreatePlayerTextDraw(playerid, 165.000000, 213.000000, "ld_beat:right");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][8], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][8], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][8], 22.500000, 24.500000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][8], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][8], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][8], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][8], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][8], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][8], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][8], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][8], true);

	tdMenuItem[playerid][9] = CreatePlayerTextDraw(playerid, 133.000000, 199.000000, "Eixo X");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][9], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][9], 0.254167, 1.350000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][9], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][9], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][9], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][9], -764862721);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][9], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][9], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][9], false);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][9], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][9], false);

	tdMenuItem[playerid][10] = CreatePlayerTextDraw(playerid, 133.000000, 242.000000, "EIXO Y");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][10], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][10], 0.254167, 1.350000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][10], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][10], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][10], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][10], -764862721);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][10], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][10], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][10], false);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][10], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][10], false);

	tdMenuItem[playerid][11] = CreatePlayerTextDraw(playerid, 114.000000, 254.000000, "ld_beat:left");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][11], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][11], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][11], 22.500000, 24.500000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][11], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][11], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][11], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][11], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][11], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][11], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][11], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][11], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][11], true);

	tdMenuItem[playerid][12] = CreatePlayerTextDraw(playerid, 164.000000, 254.000000, "ld_beat:right");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][12], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][12], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][12], 22.500000, 24.500000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][12], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][12], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][12], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][12], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][12], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][12], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][12], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][12], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][12], true);

	tdMenuItem[playerid][13] = CreatePlayerTextDraw(playerid, 133.000000, 280.000000, "EIXO Z");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][13], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][13], 0.254167, 1.350000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][13], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][13], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][13], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][13], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][13], -764862721);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][13], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][13], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][13], false);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][13], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][13], false);

	tdMenuItem[playerid][14] = CreatePlayerTextDraw(playerid, 114.000000, 293.000000, "ld_beat:left");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][14], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][14], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][14], 22.500000, 24.500000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][14], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][14], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][14], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][14], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][14], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][14], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][14], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][14], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][14], true);

	tdMenuItem[playerid][15] = CreatePlayerTextDraw(playerid, 164.000000, 293.000000, "ld_beat:right");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][15], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][15], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][15], 22.500000, 24.500000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][15], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][15], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][15], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][15], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][15], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][15], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][15], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][15], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][15], true);

	tdMenuItem[playerid][16] = CreatePlayerTextDraw(playerid, 93.000000, 168.000000, "~y~Modo: ~w~Posicao");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][16], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][16], 0.204167, 1.150000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][16], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][16], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][16], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][16], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][16], -1);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][16], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][16], 50);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][16], false);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][16], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][16], false);

	tdMenuItem[playerid][17] = CreatePlayerTextDraw(playerid, 187.000000, 185.000000, "ALTERNAR");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][17], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][17], 0.133333, 0.950000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][17], 15.500000, 10.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][17], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][17], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][17], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][17], -2686721);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][17], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][17], 200);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][17], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][17], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][17], true);

	tdMenuItem[playerid][18] = CreatePlayerTextDraw(playerid, 125.000000, 322.000000, "SALVAR");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][18], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][18], 0.133331, 0.949998);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][18], 15.500000, 41.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][18], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][18], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][18], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][18], 1097458175);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][18], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][18], 200);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][18], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][18], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][18], true);

	tdMenuItem[playerid][19] = CreatePlayerTextDraw(playerid, 174.000000, 322.000000, "REDEFINIR");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][19], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][19], 0.133331, 0.949998);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][19], 15.500000, 41.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][19], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][19], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][19], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][19], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][19], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][19], 200);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][19], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][19], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][19], true);

	tdMenuItem[playerid][20] = CreatePlayerTextDraw(playerid, 205.000000, 138.000000, "X");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][20], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][20], 0.308331, 1.100000);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][20], 12.000000, 9.500000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][20], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][20], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][20], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][20], -16776961);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][20], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][20], 200);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][20], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][20], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][20], true);

	tdMenuItem[playerid][21] = CreatePlayerTextDraw(playerid, 150.000000, 360.000000, "CAMERA");
	PlayerTextDrawFont(playerid, tdMenuItem[playerid][21], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid, tdMenuItem[playerid][21], 0.133331, 0.949998);
	PlayerTextDrawTextSize(playerid, tdMenuItem[playerid][21], 15.500000, 41.000000);
	PlayerTextDrawSetOutline(playerid, tdMenuItem[playerid][21], 1);
	PlayerTextDrawSetShadow(playerid, tdMenuItem[playerid][21], 0);
	PlayerTextDrawAlignment(playerid, tdMenuItem[playerid][21], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, tdMenuItem[playerid][21], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, tdMenuItem[playerid][21], 255);
	PlayerTextDrawBoxColor(playerid, tdMenuItem[playerid][21], 200);
	PlayerTextDrawUseBox(playerid, tdMenuItem[playerid][21], true);
	PlayerTextDrawSetProportional(playerid, tdMenuItem[playerid][21], true);
	PlayerTextDrawSetSelectable(playerid, tdMenuItem[playerid][21], true);
}

DestroyMenuEditorItem(playerid) {
	for(new i = 0; i < 21; i++) 
		PlayerTextDrawDestroy(playerid, tdMenuItem[playerid][i]);
}

OpenMenuEditorItem(playerid, slotid, type = 0) {
	new string[80];

	for(new i = 0; i < 21; i++) 
		PlayerTextDrawShow(playerid, tdMenuItem[playerid][i]);

	SelectTextDraw(playerid, 0xFF0000FF);

	SetPVarInt(playerid, "editorItem", 1);
	SetPVarInt(playerid, "editorTipo", type);
	SetPVarInt(playerid, "editorSlot", slotid);
	SetPVarInt(playerid, "editorModo", 0); // Modo Posição
	SetPVarInt(playerid, "editorVelocidade", 1);
	SetPVarInt(playerid, "editorCamera", 0);

	// Edição de acessório
	if(type == 0) {
		SetPVarFloat(playerid, "editorPosX", accessoriesInfo[playerid][slotid][acc_pos][0]);
		SetPVarFloat(playerid, "editorPosY", accessoriesInfo[playerid][slotid][acc_pos][1]);
		SetPVarFloat(playerid, "editorPosZ", accessoriesInfo[playerid][slotid][acc_pos][2]);
		SetPVarFloat(playerid, "editorRotX", accessoriesInfo[playerid][slotid][acc_rot][0]);
		SetPVarFloat(playerid, "editorRotY", accessoriesInfo[playerid][slotid][acc_rot][1]);
		SetPVarFloat(playerid, "editorRotZ", accessoriesInfo[playerid][slotid][acc_rot][2]);
		SetPVarFloat(playerid, "editorTamX", accessoriesInfo[playerid][slotid][acc_size][0]);
		SetPVarFloat(playerid, "editorTamY", accessoriesInfo[playerid][slotid][acc_size][1]);
		SetPVarFloat(playerid, "editorTamZ", accessoriesInfo[playerid][slotid][acc_size][2]);
	}
	// Edição de portão
	else if(type == 1) {
		SetPVarFloat(playerid, "editorPosX", PortaoInfo[slotid][portaoPos][0]);
		SetPVarFloat(playerid, "editorPosY", PortaoInfo[slotid][portaoPos][1]);
		SetPVarFloat(playerid, "editorPosZ", PortaoInfo[slotid][portaoPos][2]);
		SetPVarFloat(playerid, "editorRotX", PortaoInfo[slotid][portaoRot][0]);
		SetPVarFloat(playerid, "editorRotY", PortaoInfo[slotid][portaoRot][1]);
		SetPVarFloat(playerid, "editorRotZ", PortaoInfo[slotid][portaoRot][2]);
	}
	// Edição de móvel
	else if(type == 2) {
		new house = Player_GetInHouse(playerid);
		SetPVarFloat(playerid, "editorPosX", FurnitureHouse_GetPosX(house, slotid));
		SetPVarFloat(playerid, "editorPosY", FurnitureHouse_GetPosY(house, slotid));
		SetPVarFloat(playerid, "editorPosZ", FurnitureHouse_GetPosZ(house, slotid));
		SetPVarFloat(playerid, "editorRotX", FurnitureHouse_GetRotX(house, slotid));
		SetPVarFloat(playerid, "editorRotY", FurnitureHouse_GetRotY(house, slotid));
		SetPVarFloat(playerid, "editorRotZ", FurnitureHouse_GetRotZ(house, slotid));
	}
	// Edição de acessório veicular
	// else if(type == 3) {
	// 	new vehicleid = GetPVarInt(playerid, "editVehicleID"),
	// 		servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];

	// 	SetPVarFloat(playerid, "editorPosX", VehicleAccessoryInfo[servervehicleid][slotid][pvaOffset][0]);
	// 	SetPVarFloat(playerid, "editorPosY", VehicleAccessoryInfo[servervehicleid][slotid][pvaOffset][1]);
	// 	SetPVarFloat(playerid, "editorPosZ", VehicleAccessoryInfo[servervehicleid][slotid][pvaOffset][2]);
	// 	SetPVarFloat(playerid, "editorRotX", VehicleAccessoryInfo[servervehicleid][slotid][pvaRotation][0]);
	// 	SetPVarFloat(playerid, "editorRotY", VehicleAccessoryInfo[servervehicleid][slotid][pvaRotation][1]);
	// 	SetPVarFloat(playerid, "editorRotZ", VehicleAccessoryInfo[servervehicleid][slotid][pvaRotation][2]);
	// }
	// Edição de placa
	else if(type == 5) {
		new panelid = GetPVarInt(playerid, "UpdatePanelID");

		SetPVarFloat(playerid, "editorPosX", PanelInfo[panelid][pnPos][0]);
		SetPVarFloat(playerid, "editorPosY", PanelInfo[panelid][pnPos][1]);
		SetPVarFloat(playerid, "editorPosZ", PanelInfo[panelid][pnPos][2]);
		SetPVarFloat(playerid, "editorRotX", PanelInfo[panelid][pnRot][0]);
		SetPVarFloat(playerid, "editorRotY", PanelInfo[panelid][pnRot][1]);
		SetPVarFloat(playerid, "editorRotZ", PanelInfo[panelid][pnRot][2]);
	}

	if(type == 0) 
		format(string, sizeof(string), "~y~Item: ~w~%s", accessoriesInfo[playerid][slotid][acc_name]);
	else if(type == 1)
		format(string, sizeof(string), "~y~Objeto: ~w~Portao");
	else if(type == 2)
		format(string, sizeof(string), "~y~Objeto: ~w~Movel");
	else if(type == 3)
		format(string, sizeof(string), "~y~Objeto: ~w~Acessorio Veicular");
	else if(type == 5)
		format(string, sizeof(string), "~y~Objeto: ~w~Placa");

	PlayerTextDrawSetString(playerid, tdMenuItem[playerid][3], string);

	format(string, sizeof(string), "~y~Modo: ~w~%s", type == 0 ? (modosItem[0]) : (modosObjeto[0]));
	PlayerTextDrawSetString(playerid, tdMenuItem[playerid][16], string);

	format(string, sizeof(string), "~y~Velocidade: ~w~%.1f", velocidadeItem[1] * 100.0);
	PlayerTextDrawSetString(playerid, tdMenuItem[playerid][4], string);
}

CloseMenuEditorItem(playerid) {
	for(new i = 0; i < 21; i++) 
		PlayerTextDrawHide(playerid, tdMenuItem[playerid][i]);

	CancelSelectTextDraw(playerid);
	SetPVarInt(playerid, "editorItem", 0);
}

IsPlayerInEditorItem(playerid) {
	return GetPVarInt(playerid, "editorItem");
}

hook OnPlayerConnect(playerid) {
	CreateMenuEditorItem(playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid) {
	DestroyMenuEditorItem(playerid);
	return 1;
}

hook OnClickDynPlayerTextDraw(playerid, PlayerText:textid) 
{
	if (IsPlayerInEditorItem(playerid)) {
		new indVelo = GetPVarInt(playerid, "editorVelocidade");
		new Float:velocidade = velocidadeItem[indVelo];
		new slot = GetPVarInt(playerid, "editorSlot");
		new modo = GetPVarInt(playerid, "editorModo"),
			tipo = GetPVarInt(playerid, "editorTipo");
		new string[64];

		// new houseid = GetPVarInt(playerid, "editHouseID");

		// Botão de Salvar
		if(textid == tdMenuItem[playerid][18]) {
			if(tipo == 0) {
				OnPlayerEditAttachedObject(playerid, EDIT_RESPONSE_FINAL, slot, accessoriesInfo[playerid][slot][acc_model], accessoriesInfo[playerid][slot][acc_pos_body], 
					accessoriesInfo[playerid][slot][acc_pos][0], accessoriesInfo[playerid][slot][acc_pos][1], accessoriesInfo[playerid][slot][acc_pos][2], 
					accessoriesInfo[playerid][slot][acc_rot][0], accessoriesInfo[playerid][slot][acc_rot][1], accessoriesInfo[playerid][slot][acc_rot][2], 
					accessoriesInfo[playerid][slot][acc_size][0], accessoriesInfo[playerid][slot][acc_size][1], accessoriesInfo[playerid][slot][acc_size][2]);
			}
			else if(tipo == 1) {
				updatePortao(slot);
			}
			else if(tipo == 2) {
				// Furniture_Save(houseid, slot);
			}
			// else if(tipo == 3) {
			// 	new vehicleid = GetPVarInt(playerid, "editVehicleID");
			// 	Player_SaveVehicleAccessory(playerid, vehicleid, slot);
			// }
			else if(tipo == 5) {
				new panelid = GetPVarInt(playerid, "UpdatePanelID");
				Panel_Save(panelid);
			}
		
			CloseMenuEditorItem(playerid);
		}

		// Botão de Cancelar
		else if(textid == tdMenuItem[playerid][20] || textid == tdMenuItem[playerid][19]) {
			new Float:pos[3], Float:rot[3], Float:tam[3];
			pos[0] = GetPVarFloat(playerid, "editorPosX");
			pos[1] = GetPVarFloat(playerid, "editorPosY");
			pos[2] = GetPVarFloat(playerid, "editorPosZ");
			rot[0] = GetPVarFloat(playerid, "editorRotX");
			rot[1] = GetPVarFloat(playerid, "editorRotY");
			rot[2] = GetPVarFloat(playerid, "editorRotZ");
			tam[0] = GetPVarFloat(playerid, "editorTamX");
			tam[1] = GetPVarFloat(playerid, "editorTamY");
			tam[2] = GetPVarFloat(playerid, "editorTamZ");

			if(tipo == 0) {
				SetPlayerAccessorie(playerid, accessoriesInfo[playerid][slot][acc_name], slot, accessoriesInfo[playerid][slot][acc_model], 
					accessoriesInfo[playerid][slot][acc_pos_body], pos[0], pos[1], pos[2], rot[0], rot[1], rot[2], tam[0], tam[1], tam[2],
					accessoriesInfo[playerid][slot][acc_color1], accessoriesInfo[playerid][slot][acc_color2]);
			}
			else if(tipo == 1) {
				for(new i = 0; i < 3; i++) {
					PortaoInfo[slot][portaoPos][i] = pos[i];
					PortaoInfo[slot][portaoRot][i] = rot[i];
				}
				updatePortao(slot);
			}
			else if(tipo == 2) {
				// for(new i = 0; i < 3; i++) {
				// 	MobInfo[houseid][slot][mobPos][i] 		= pos[i];
				// 	MobInfo[houseid][slot][mobRot][i] 		= rot[i];
				// }

				// SetDynamicObjectPos(MobInfo[houseid][slot][mobObject], pos[0], pos[1], pos[2]);
				// SetDynamicObjectRot(MobInfo[houseid][slot][mobObject], rot[0], rot[1], rot[2]);
			}
			// else if(tipo == 3) {
			// 	new vehicleid = GetPVarInt(playerid, "editVehicleID"),
			// 		servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];

			// 	for(new i = 0; i < 3; i++) {
			// 		VehicleAccessoryInfo[servervehicleid][slot][pvaOffset][i] 		= pos[i];
			// 		VehicleAccessoryInfo[servervehicleid][slot][pvaRotation][i] 	= rot[i];
			// 	}

			// 	Player_SetVehicleAccessory(playerid, vehicleid, slot);
			// }
			else if(tipo == 5) {
				for(new i = 0; i < 3; i++) {
					PanelInfo[slot][pnPos][i] = pos[i];
					PanelInfo[slot][pnRot][i] = rot[i];
				}

				Panel_Update3DText(slot);
				Panel_Save(slot);
			}

			if(textid == tdMenuItem[playerid][20])
				CloseMenuEditorItem(playerid);
		}

		// Botão de Alternar Modo
		else if(textid == tdMenuItem[playerid][5]) {
			modo += 1;
			if((tipo == 0 && modo == sizeof(modosItem)) || (tipo != 0 && modo == sizeof(modosObjeto)))
				modo = 0;

			SetPVarInt(playerid, "editorModo", modo);
			format(string, sizeof(string), "~y~Modo: ~w~%s", tipo == 0 ? (modosItem[modo]) : (modosObjeto[modo]));
			PlayerTextDrawSetString(playerid, tdMenuItem[playerid][16], string);
		}

		// Botão de Alternar Velocidade
		else if(textid == tdMenuItem[playerid][17]) {
			indVelo += 1;
			if(indVelo == sizeof(velocidadeItem))
				indVelo = 0;

			SetPVarInt(playerid, "editorVelocidade", indVelo);
			format(string, sizeof(string), "~y~Velocidade: ~w~%.1f", velocidadeItem[indVelo] * 100.0);
			PlayerTextDrawSetString(playerid, tdMenuItem[playerid][4], string);
		}

		// Botão de Alternar câmera
		else if(textid == tdMenuItem[playerid][21]) {
			SetPVarInt(playerid, "editorCamera", !GetPVarInt(playerid, "editorCamera"));
			
			if(GetPVarInt(playerid, "editorCamera")) 
				SelectTextDraw(playerid, 0xFF0000FF);
			else
				CancelSelectTextDraw(playerid);
		}

		// Eixo X
		new eixo = -1, Float:valor;

		if(textid == tdMenuItem[playerid][7]) {
			eixo = 0;
			valor = velocidade * -1;
		}
		else if(textid == tdMenuItem[playerid][8]) {
			eixo = 0;
			valor = velocidade * 1;
		}

		// Eixo Y
		else if(textid == tdMenuItem[playerid][11]) {
			eixo = 1;
			valor = velocidade * -1;
		}
		else if(textid == tdMenuItem[playerid][12]) {
			eixo = 1;
			valor = velocidade * 1;
		}

		// Eixo Z
		else if(textid == tdMenuItem[playerid][14]) {
			eixo = 2;
			valor = velocidade * -1;
		}
		else if(textid == tdMenuItem[playerid][15]) {
			eixo = 2;
			valor = velocidade * 1;
		}

		if(eixo >= 0) {
			if(modo == 0) {
				if(tipo == 0)
					accessoriesInfo[playerid][slot][acc_pos][eixo] += valor;
				else if(tipo == 1)
					PortaoInfo[slot][portaoPos][eixo] += valor;
				else if(tipo == 2) {
					
				}
					// MobInfo[houseid][slot][mobPos][eixo] += valor;
				// else if(tipo == 3) {
				// 	new vehicleid = GetPVarInt(playerid, "editVehicleID"),
				// 		servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];

				// 	VehicleAccessoryInfo[servervehicleid][slot][pvaOffset][eixo] += valor;
				// }
				else if(tipo == 5)
					PanelInfo[slot][pnPos][eixo] += valor;
			}
			else if(modo == 1) {
				if(tipo == 0)
					accessoriesInfo[playerid][slot][acc_rot][eixo] += valor * 100;
				else if(tipo == 1)
					PortaoInfo[slot][portaoRot][eixo] += valor * 100;
				else if(tipo == 2) {

				}
					// MobInfo[houseid][slot][mobRot][eixo] += valor * 100;
				// else if(tipo == 3) {
				// 	new vehicleid = GetPVarInt(playerid, "editVehicleID"),
				// 		servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];

				// 	VehicleAccessoryInfo[servervehicleid][slot][pvaRotation][eixo] += valor * 100;
				// }
				else if(tipo == 5)
					PanelInfo[slot][pnRot][eixo] += valor * 100;
			}
			else if(modo == 2)
				accessoriesInfo[playerid][slot][acc_size][eixo] += valor * 10;

			if(tipo == 0) {
				RemovePlayerAttachedObject(playerid, slot);
				SetPlayerAccessorie(playerid, accessoriesInfo[playerid][slot][acc_name], slot, accessoriesInfo[playerid][slot][acc_model], accessoriesInfo[playerid][slot][acc_pos_body], 
					accessoriesInfo[playerid][slot][acc_pos][0], accessoriesInfo[playerid][slot][acc_pos][1], accessoriesInfo[playerid][slot][acc_pos][2], 
					accessoriesInfo[playerid][slot][acc_rot][0], accessoriesInfo[playerid][slot][acc_rot][1], accessoriesInfo[playerid][slot][acc_rot][2], 
					accessoriesInfo[playerid][slot][acc_size][0], accessoriesInfo[playerid][slot][acc_size][1], accessoriesInfo[playerid][slot][acc_size][2],
					accessoriesInfo[playerid][slot][acc_color1], accessoriesInfo[playerid][slot][acc_color2]);
			}
			else if(tipo == 1) {
				updatePortao(slot);
			}
			else if(tipo == 2) {
				// SetDynamicObjectPos(MobInfo[houseid][slot][mobObject], MobInfo[houseid][slot][mobPos][0], MobInfo[houseid][slot][mobPos][1], MobInfo[houseid][slot][mobPos][2]);
				// SetDynamicObjectRot(MobInfo[houseid][slot][mobObject], MobInfo[houseid][slot][mobRot][0], MobInfo[houseid][slot][mobRot][1], MobInfo[houseid][slot][mobRot][2]);
			}
			// else if(tipo == 3) {
			// 	new vehicleid = GetPVarInt(playerid, "editVehicleID");
			// 	Player_SetVehicleAccessory(playerid, vehicleid, slot);
			// }
			else if(tipo == 5) {
				SetDynamicObjectPos(PanelInfo[slot][pnObject], PanelInfo[slot][pnPos][0], PanelInfo[slot][pnPos][1], PanelInfo[slot][pnPos][2]);
				SetDynamicObjectRot(PanelInfo[slot][pnObject], PanelInfo[slot][pnRot][0], PanelInfo[slot][pnRot][1], PanelInfo[slot][pnRot][2]);
			}
		}
	}
}