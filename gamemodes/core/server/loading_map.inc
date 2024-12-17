// Includes
#include < YSI_Coding\y_hooks >

//Variables
static Text:loadingBackground;
static Text:loadingTitle;

stock CreateTexdraws_LoadingMap() {
    //Textdraws
    loadingBackground = TextDrawCreate(320.000000, 195.000000, "_");
    TextDrawFont(loadingBackground, TEXT_DRAW_FONT_1);
    TextDrawLetterSize(loadingBackground, 0.600000, 4.999992);
    TextDrawTextSize(loadingBackground, 298.500000, 196.500000);
    TextDrawSetOutline(loadingBackground, 1);
    TextDrawSetShadow(loadingBackground, 0);
    TextDrawAlignment(loadingBackground, TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(loadingBackground, -1);
    TextDrawBackgroundColor(loadingBackground, 1296911871);
    TextDrawBoxColor(loadingBackground, 218696058);
    TextDrawUseBox(loadingBackground, true);
    TextDrawSetProportional(loadingBackground, true);
    TextDrawSetSelectable(loadingBackground, false);
    TextDrawHideForAll(loadingBackground);

    loadingTitle = TextDrawCreate(320.000000, 209.000000, "CARREGANDO...");
    TextDrawFont(loadingTitle, TEXT_DRAW_FONT_2);
    TextDrawLetterSize(loadingTitle, 0.216665, 1.600000);
    TextDrawTextSize(loadingTitle, 400.000000, 17.000000);
    TextDrawSetOutline(loadingTitle, 0);
    TextDrawSetShadow(loadingTitle, 0);
    TextDrawAlignment(loadingTitle, TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(loadingTitle, -81);
    TextDrawBackgroundColor(loadingTitle, 255);
    TextDrawBoxColor(loadingTitle, 80);
    TextDrawUseBox(loadingTitle, false);
    TextDrawSetProportional(loadingTitle, true);
    TextDrawSetSelectable(loadingTitle, false);
    TextDrawHideForAll(loadingTitle);
}

// Variáveis
static Timer:timerLoadingMap[MAX_PLAYERS];

// Funções
timer TimerLoadingMap[3000](playerid) {
    SetPVarInt(playerid, "Invincible", 0);
	TogglePlayerControllable(playerid, true);
    TextDrawHideForPlayer(playerid, loadingBackground);
    TextDrawHideForPlayer(playerid, loadingTitle);
}

hook OnGameModeInit() {
    CreateTexdraws_LoadingMap();
}

hook OnPlayerConnect(playerid) {
    TextDrawHideForPlayer(playerid, loadingBackground);
    TextDrawHideForPlayer(playerid, loadingTitle);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    stop timerLoadingMap[playerid];
    return 1;
}

timer CheckMapLoadedForPlayer[3500](playerid) {
    if(GetPlayerAnimationIndex(playerid) != 1130)
        return;

    new Float:pos[3];
    pos[0] = GetPVarFloat(playerid, "PreviousPosX");
    pos[1] = GetPVarFloat(playerid, "PreviousPosY");
    pos[2] = GetPVarFloat(playerid, "PreviousPosZ");

    SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    ShowLoadingMap(playerid);
}

timer UpdatePreviousPos[1000](playerid) {
    new Float:pos[3];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    SetPVarFloat(playerid, "PreviousPosX", pos[0]);
    SetPVarFloat(playerid, "PreviousPosY", pos[1]);
    SetPVarFloat(playerid, "PreviousPosZ", pos[2]);
}

stock ShowLoadingMap(playerid, time=3000) {
    TogglePlayerControllable(playerid, false);
    TextDrawShowForPlayer(playerid, loadingBackground);
    TextDrawShowForPlayer(playerid, loadingTitle);
    SetPVarInt(playerid, "Invincible", 1);

    stop timerLoadingMap[playerid];
	timerLoadingMap[playerid] = defer TimerLoadingMap[Timer:time](playerid);
    defer CheckMapLoadedForPlayer(playerid);

    new Float:pos[3];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    SetPVarFloat(playerid, "PreviousPosX", pos[0]);
    SetPVarFloat(playerid, "PreviousPosY", pos[1]);
    SetPVarFloat(playerid, "PreviousPosZ", pos[2]);
    defer UpdatePreviousPos(playerid);
}