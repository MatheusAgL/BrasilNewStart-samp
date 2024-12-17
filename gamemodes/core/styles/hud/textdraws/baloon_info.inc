

#define         _BALOON_INFO_hud_system         true
#define MAX_PLAYER_POPUPS 4

new PlayerText:baloon_info_playertextdraw[2][MAX_PLAYERS],
	Text:textDrawBgPopUp[MAX_PLAYER_POPUPS],
	PlayerText:baloon_preview_action[MAX_PLAYERS],
	PlayerText:textDrawPlayerMessage[MAX_PLAYERS],
	Timer:timerPlayerMessage[MAX_PLAYERS],
	PlayerText:textDrawPopUp[2][MAX_PLAYERS][MAX_PLAYER_POPUPS],
	Iterator:IterPlayerPopUps[MAX_PLAYERS]<MAX_PLAYER_POPUPS>,
	Timer:timer_balao_info[MAX_PLAYERS];

hook OnGameModeInit() {
	for(new i = 0; i < MAX_PLAYER_POPUPS; i++) {
		new Float:height =  i * 38.0;

		textDrawBgPopUp[i] = TextDrawCreate(165.000000, 397.000000 - height, "_");
		TextDrawFont(textDrawBgPopUp[i], TEXT_DRAW_FONT_1);
		TextDrawLetterSize(textDrawBgPopUp[i], 0.600000, 2.850001);
		TextDrawTextSize(textDrawBgPopUp[i], 298.500000, 90.500000);
		TextDrawSetOutline(textDrawBgPopUp[i], 1);
		TextDrawSetShadow(textDrawBgPopUp[i], 0);
		TextDrawAlignment(textDrawBgPopUp[i], TEXT_DRAW_ALIGN_CENTER);
		TextDrawColor(textDrawBgPopUp[i], -1);
		TextDrawBackgroundColor(textDrawBgPopUp[i], 255);
		TextDrawBoxColor(textDrawBgPopUp[i], 319819761);
		TextDrawUseBox(textDrawBgPopUp[i], true);
		TextDrawSetProportional(textDrawBgPopUp[i], true);
		TextDrawSetSelectable(textDrawBgPopUp[i], false);
	}
	return 1;
}

hook CreateStaticTextDraws(playerid) {
	baloon_info_playertextdraw[0][playerid] = CreatePlayerTextDraw(playerid, 3.000000, 196.000000, "Voce pode digitar no chat pressionando a letra ~p~'T'~w~bom jogo para voce");
	PlayerTextDrawFont(playerid, baloon_info_playertextdraw[0][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, baloon_info_playertextdraw[0][playerid], 0.204166, 1.149999);
	PlayerTextDrawTextSize(playerid, baloon_info_playertextdraw[0][playerid], 122.000000, -52.000000);
	PlayerTextDrawSetOutline(playerid, baloon_info_playertextdraw[0][playerid], 0);
	PlayerTextDrawSetShadow(playerid, baloon_info_playertextdraw[0][playerid], 1);
	PlayerTextDrawAlignment(playerid, baloon_info_playertextdraw[0][playerid], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, baloon_info_playertextdraw[0][playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, baloon_info_playertextdraw[0][playerid], 255);
	PlayerTextDrawBoxColor(playerid, baloon_info_playertextdraw[0][playerid], 145);
	PlayerTextDrawUseBox(playerid, baloon_info_playertextdraw[0][playerid], true);
	PlayerTextDrawSetProportional(playerid, baloon_info_playertextdraw[0][playerid], true);
	PlayerTextDrawSetSelectable(playerid, baloon_info_playertextdraw[0][playerid], false);

	for(new i = 0; i < MAX_PLAYER_POPUPS; i++) {
		new Float:height =  i * 38.0;

		textDrawPopUp[0][playerid][i] = CreatePlayerTextDraw(playerid, 165.000000, 399.000000 - height, "NOVO ITEM RECEBIDO");
		PlayerTextDrawFont(playerid, textDrawPopUp[0][playerid][i], TEXT_DRAW_FONT_1);
		PlayerTextDrawLetterSize(playerid, textDrawPopUp[0][playerid][i], 0.150000, 0.899999);
		PlayerTextDrawTextSize(playerid, textDrawPopUp[0][playerid][i], 411.500000, 95.500000);
		PlayerTextDrawSetOutline(playerid, textDrawPopUp[0][playerid][i], 0);
		PlayerTextDrawSetShadow(playerid, textDrawPopUp[0][playerid][i], 0);
		PlayerTextDrawAlignment(playerid, textDrawPopUp[0][playerid][i], TEXT_DRAW_ALIGN_CENTER);
		PlayerTextDrawColor(playerid, textDrawPopUp[0][playerid][i], -1);
		PlayerTextDrawBackgroundColor(playerid, textDrawPopUp[0][playerid][i], 255);
		PlayerTextDrawBoxColor(playerid, textDrawPopUp[0][playerid][i], 370282725);
		PlayerTextDrawUseBox(playerid, textDrawPopUp[0][playerid][i], false);
		PlayerTextDrawSetProportional(playerid, textDrawPopUp[0][playerid][i], true);
		PlayerTextDrawSetSelectable(playerid, textDrawPopUp[0][playerid][i], false);

		textDrawPopUp[1][playerid][i] = CreatePlayerTextDraw(playerid, 165.000000, 410.000000 - height, "~r~~h~~h~~h~+1 ~w~Caixa Surpresa Pequena");
		PlayerTextDrawFont(playerid, textDrawPopUp[1][playerid][i], TEXT_DRAW_FONT_1);
		PlayerTextDrawLetterSize(playerid, textDrawPopUp[1][playerid][i], 0.150000, 0.899999);
		PlayerTextDrawTextSize(playerid, textDrawPopUp[1][playerid][i], 411.500000, 95.500000);
		PlayerTextDrawSetOutline(playerid, textDrawPopUp[1][playerid][i], 0);
		PlayerTextDrawSetShadow(playerid, textDrawPopUp[1][playerid][i], 0);
		PlayerTextDrawAlignment(playerid, textDrawPopUp[1][playerid][i], TEXT_DRAW_ALIGN_CENTER);
		PlayerTextDrawColor(playerid, textDrawPopUp[1][playerid][i], -1);
		PlayerTextDrawBackgroundColor(playerid, textDrawPopUp[1][playerid][i], 255);
		PlayerTextDrawBoxColor(playerid, textDrawPopUp[1][playerid][i], 370282725);
		PlayerTextDrawUseBox(playerid, textDrawPopUp[1][playerid][i], false);
		PlayerTextDrawSetProportional(playerid, textDrawPopUp[1][playerid][i], true);
		PlayerTextDrawSetSelectable(playerid, textDrawPopUp[1][playerid][i], false);
	}

	textDrawPlayerMessage[playerid] = CreatePlayerTextDraw(playerid, 321.000000, 354.000000, "Voce deve encaixar a ~g~carga ~w~no veiculo para continuar o servico.");
	PlayerTextDrawFont(playerid, textDrawPlayerMessage[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, textDrawPlayerMessage[playerid], 0.199999, 1.300000);
	PlayerTextDrawTextSize(playerid, textDrawPlayerMessage[playerid], 400.000000, 301.500000);
	PlayerTextDrawSetOutline(playerid, textDrawPlayerMessage[playerid], 0);
	PlayerTextDrawSetShadow(playerid, textDrawPlayerMessage[playerid], 1);
	PlayerTextDrawAlignment(playerid, textDrawPlayerMessage[playerid], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, textDrawPlayerMessage[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, textDrawPlayerMessage[playerid], 255);
	PlayerTextDrawBoxColor(playerid, textDrawPlayerMessage[playerid], 50);
	PlayerTextDrawUseBox(playerid, textDrawPlayerMessage[playerid], false);
	PlayerTextDrawSetProportional(playerid, textDrawPlayerMessage[playerid], true);
	PlayerTextDrawSetSelectable(playerid, textDrawPlayerMessage[playerid], false);
}

timer t_Balao_Info[5000](playerid) {
	PlayerTextDrawHide(playerid, baloon_info_playertextdraw[0][playerid]);
}

timer timerMessageInfo[5000](playerid) {
	PlayerTextDrawHide(playerid, textDrawPlayerMessage[playerid]);
}

stock ShowPlayerBaloonInfo(playerid, const string_balooninfo[], tempo, bool:antiflood=false)
{
	if (antiflood)
		if (gettime() < GetPVarInt(playerid, #varFlood_ballon))
			return true;
		else
			SetPVarInt(playerid, #varFlood_ballon, gettime() + tempo/1000);

	stop timer_balao_info[playerid];
	timer_balao_info[playerid] = defer t_Balao_Info(playerid);

	if (IsValidDynamicPlayerTextDraw(playerid, baloon_info_playertextdraw[0][playerid])) {
		PlayerTextDrawSetString(playerid, baloon_info_playertextdraw[0][playerid], string_balooninfo);
		PlayerTextDrawShow(playerid, baloon_info_playertextdraw[0][playerid]);
	}
	return true;
}

stock HidePlayerPopUp(playerid, index) {
	for(new i = 0; i < 2; i++) {
		PlayerTextDrawHide(playerid, textDrawPopUp[i][playerid][index]);
	}
	TextDrawHideForPlayer(playerid, textDrawBgPopUp[index]);
}

timer t_Action_Info[10000](playerid, index)
{
	HidePlayerPopUp(playerid, index);

	Iter_Remove(IterPlayerPopUps[playerid], index);

	if(Iter_Count(IterPlayerPopUps[playerid]) <= 0) {
		SetPVarInt(playerid, "HasPopup", 0);
	}
}

stock HasPlayerAnyPopup(playerid) {
	return GetPVarInt(playerid, "HasPopup");
}

stock ShowPlayerPopupHUD(playerid, const title[], const string[], tempo)
{
	new freeIndex = Iter_Free(IterPlayerPopUps[playerid]);

	if(freeIndex < 0)
		return;

	defer t_Action_Info[Timer:tempo](playerid, freeIndex);

	PlayerTextDrawSetString(playerid, textDrawPopUp[0][playerid][freeIndex], title);
	PlayerTextDrawSetString(playerid, textDrawPopUp[1][playerid][freeIndex], string);
	
	TextDrawShowForPlayer(playerid, textDrawBgPopUp[freeIndex]);
	for(new i = 0; i < 2; i++) {
		PlayerTextDrawShow(playerid, textDrawPopUp[i][playerid][freeIndex]);
	}

	Iter_Add(IterPlayerPopUps[playerid], freeIndex);

	//Escondendo textdraws de guerra de TR e de drogas
	HidePlayerGZTextDraw(playerid);
	for(new i = 0; i < 5; i++) {
		CONFIG_DrugSystem(playerid, i, false);
	}

	SetPVarInt(playerid, "HasPopup", 1);
}

stock ShowPlayerMessage(playerid, const string[], time) {
	stop timerPlayerMessage[playerid];

	PlayerTextDrawSetString(playerid, textDrawPlayerMessage[playerid], string);
	PlayerTextDrawShow(playerid, textDrawPlayerMessage[playerid]);
	timerPlayerMessage[playerid] = defer timerMessageInfo[Timer:time](playerid);
}

hook OnPlayerDisconnect(playerid) {
	Iter_Clear(IterPlayerPopUps[playerid]);
}