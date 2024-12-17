#include <YSI_Coding\y_hooks>

// Dados do passe
enum weeklyPassInfo {
    wpInProgress,
    wpName[40],
    wpID,
    wpPaid,
    wpValue,
    wpCurrency,
    Timestamp:wpStartDate,
    Timestamp:wpEndDate
};

new WeeklyPassInfo[weeklyPassInfo];

// Dados dos itens do passe
enum weeklyPassItemInfo {
    wpiID,
    wpiType,
    wpiModel,
    wpiName[30],
    wpiAmount,
    wpiColor1,
    wpiColor2,
    wpiCurrent,
    wpiExists,
    wpiTime,
    wpiAvailable,
    Timestamp:wpiDateAvailable,
    Float:wpiRotationX, 
    Float:wpiRotationY, 
    Float:wpiRotationZ,
    Float:wpiZoom, 
    Float:wpiTextSizeX, 
    Float:wpiTextSizeY, 
    wpiBackgroundColor
};

new WeeklyPassItemInfo[7][weeklyPassItemInfo];

// Dados do player em relação aos itens do passe
enum weeklyPassPlayerItemInfo {
    wppID,
    wppItemID,
    wppReceived
};

new WeeklyPassPlayerItemInfo[MAX_PLAYERS][7][weeklyPassPlayerItemInfo];

// Dados do player relacionados ao passe
enum weeklyPassPlayerInfo {
    wppWeeklyPassID,
    wppPlayedTime,
    wppAvailable,
    wppDay
};

new WeeklyPassPlayerInfo[MAX_PLAYERS][weeklyPassPlayerInfo];


static PlayerText:seasonBackground[MAX_PLAYERS],
       PlayerText:seasonServerTitle[MAX_PLAYERS],
       PlayerText:seasonTitle[MAX_PLAYERS],
       PlayerText:seasonItemBackground[7][MAX_PLAYERS],
       PlayerText:seasonItemInternalBackground[7][MAX_PLAYERS],
       PlayerText:seasonItem[7][MAX_PLAYERS],
       PlayerText:seasonItemTitle[7][MAX_PLAYERS],
       PlayerText:seasonItemName[7][MAX_PLAYERS],
       PlayerText:seasonItemAmount[7][MAX_PLAYERS],
       Text:seasonBtnClose;

stock LoadWeeklyPass() {
	mysql_tquery(MySQL_Handle, "SELECT * FROM weekly_passes WHERE CURDATE() BETWEEN startDate AND endDate LIMIT 1", "OnWeeklyPassLoaded");
}

CALLBACK:OnWeeklyPassLoaded() {
	new rows = MYSQL_GetRowsCount(), query[300];
	if(rows == 0) {
		WeeklyPassInfo[wpInProgress] = 0;
        return;
	}

	WeeklyPassInfo[wpInProgress] = 1;
    WeeklyPassInfo[wpID] = MYSQL_GetInt(0, "id");
    format(WeeklyPassInfo[wpName], 64, MYSQL_GetString(0, "name"));
    WeeklyPassInfo[wpPaid] = MYSQL_GetInt(0, "paid");
    WeeklyPassInfo[wpValue] = MYSQL_GetInt(0, "value");
    WeeklyPassInfo[wpCurrency] = MYSQL_GetInt(0, "currency");
    TimeParse(MYSQL_GetString(0, "startDate"), ISO6801_DATE, WeeklyPassInfo[wpStartDate]);
    TimeParse(MYSQL_GetString(0, "endDate"), ISO6801_DATE, WeeklyPassInfo[wpEndDate]);

    mysql_format(MySQL_Handle, query, sizeof(query), "SELECT * FROM weekly_passes_items WHERE weeklyPass = %d ORDER BY dayOfWeek ASC LIMIT 7", WeeklyPassInfo[wpID]);
	mysql_tquery(MySQL_Handle, query, "OnWeeklyPassItemsLoaded");
}

stock UpdatePlayerWeeklyPass(playerid) {
    PlayerTextDrawSetString(playerid, seasonTitle[playerid], WeeklyPassInfo[wpName]);

    for(new day = 0; day < 7; day++) {
        new tdString[5][64];
        format(tdString[0], 64, "Dia %d", day+1);
        format(tdString[1], 64, WeeklyPassItemInfo[day][wpiName]);
        format(tdString[2], 64, "x%d", WeeklyPassItemInfo[day][wpiAmount]);

        PlayerTextDrawSetString(playerid, seasonItemTitle[day][playerid], tdString[0]);
        PlayerTextDrawSetString(playerid, seasonItemName[day][playerid], tdString[1]);
        PlayerTextDrawSetString(playerid, seasonItemAmount[day][playerid], tdString[2]);
        PlayerTextDrawSetPreviewModel(playerid, seasonItem[day][playerid], WeeklyPassItemInfo[day][wpiModel]);
        PlayerTextDrawTextSize(playerid, seasonItem[day][playerid], WeeklyPassItemInfo[day][wpiTextSizeX], WeeklyPassItemInfo[day][wpiTextSizeY]);
        PlayerTextDrawSetPreviewRot(playerid, seasonItem[day][playerid], WeeklyPassItemInfo[day][wpiRotationX], WeeklyPassItemInfo[day][wpiRotationY], WeeklyPassItemInfo[day][wpiRotationZ], WeeklyPassItemInfo[day][wpiZoom]);
        PlayerTextDrawBoxColor(playerid, seasonItemInternalBackground[day][playerid], WeeklyPassItemInfo[day][wpiBackgroundColor]);
    }
}

CALLBACK:OnWeeklyPassItemsLoaded() {
    for(new i = 0; i < 7; i++) {
        WeeklyPassItemInfo[i][wpiExists] = 0;
        WeeklyPassItemInfo[i][wpiAvailable] = 0;
    }

	new rows = MYSQL_GetRowsCount(),
        Timestamp:today = Now();

    for(new i = 0; i < rows; i++) {
        new day = MYSQL_GetInt(i, "dayOfWeek");
        WeeklyPassItemInfo[day][wpiID] = MYSQL_GetInt(i, "id");
        WeeklyPassItemInfo[day][wpiTime] = MYSQL_GetInt(i, "timeRequired");
        WeeklyPassItemInfo[day][wpiType] = MYSQL_GetInt(i, "type");
        WeeklyPassItemInfo[day][wpiModel] = MYSQL_GetInt(i, "model");
        WeeklyPassItemInfo[day][wpiAmount] = MYSQL_GetInt(i, "amount");
        WeeklyPassItemInfo[day][wpiColor1] = MYSQL_GetInt(i, "color1");
        WeeklyPassItemInfo[day][wpiColor2] = MYSQL_GetInt(i, "color2");
        format(WeeklyPassItemInfo[day][wpiName], 30, MYSQL_GetString(i, "name"));

        TimeParse(MYSQL_GetString(i, "dateAvailable"), ISO6801_DATE, WeeklyPassItemInfo[day][wpiDateAvailable]);
        if(WeeklyPassItemInfo[day][wpiDateAvailable] <= today) {
            WeeklyPassItemInfo[day][wpiAvailable] = 1;
        }

        WeeklyPassItemInfo[day][wpiRotationX] = MYSQL_GetFloat(i, "rotationX");
        WeeklyPassItemInfo[day][wpiRotationY] = MYSQL_GetFloat(i, "rotationY");
        WeeklyPassItemInfo[day][wpiRotationZ] = MYSQL_GetFloat(i, "rotationZ");
        WeeklyPassItemInfo[day][wpiZoom] = MYSQL_GetFloat(i, "zoom");
        WeeklyPassItemInfo[day][wpiTextSizeX] = MYSQL_GetFloat(i, "textSizeX");
        WeeklyPassItemInfo[day][wpiTextSizeY] = MYSQL_GetFloat(i, "textSizeY");
        WeeklyPassItemInfo[day][wpiBackgroundColor] = MYSQL_GetInt(i, "backgroundColor");

        new tdString[5][64];
        format(tdString[0], 64, "Dia %d", day+1);
        format(tdString[1], 64, WeeklyPassItemInfo[day][wpiName]);
        format(tdString[2], 64, "x%d", WeeklyPassItemInfo[day][wpiAmount]);

        for(new p = 0; p < MAX_PLAYERS; p++) {
            PlayerTextDrawSetString(p, seasonItemTitle[day][p], tdString[0]);
            PlayerTextDrawSetString(p, seasonItemName[day][p], tdString[1]);
            PlayerTextDrawSetString(p, seasonItemAmount[day][p], tdString[2]);
            PlayerTextDrawSetPreviewModel(p, seasonItem[day][p], WeeklyPassItemInfo[day][wpiModel]);
            PlayerTextDrawTextSize(p, seasonItem[day][p], WeeklyPassItemInfo[day][wpiTextSizeX], WeeklyPassItemInfo[day][wpiTextSizeY]);
            PlayerTextDrawSetPreviewRot(p, seasonItem[day][p], WeeklyPassItemInfo[day][wpiRotationX], WeeklyPassItemInfo[day][wpiRotationY], WeeklyPassItemInfo[day][wpiRotationZ], WeeklyPassItemInfo[day][wpiZoom]);
            PlayerTextDrawBoxColor(p, seasonItemInternalBackground[day][p], WeeklyPassItemInfo[day][wpiBackgroundColor]);
        }
    }

    for(new p = 0; p < MAX_PLAYERS; p++) {
        PlayerTextDrawSetString(p, seasonTitle[p], WeeklyPassInfo[wpName]);
    }
}

hook OnGameModeInit() {
    LoadWeeklyPass();

    seasonBtnClose = TextDrawCreate(314.000000, 327.000000, "FECHAR");
    TextDrawFont(seasonBtnClose, TEXT_DRAW_FONT_2);
    TextDrawLetterSize(seasonBtnClose, 0.258332, 1.849999);
    TextDrawTextSize(seasonBtnClose, 16.500000, 90.500000);
    TextDrawSetOutline(seasonBtnClose, 1);
    TextDrawSetShadow(seasonBtnClose, 0);
    TextDrawAlignment(seasonBtnClose, TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(seasonBtnClose, -16776961);
    TextDrawBackgroundColor(seasonBtnClose, 255);
    TextDrawBoxColor(seasonBtnClose, 200);
    TextDrawUseBox(seasonBtnClose, true);
    TextDrawSetProportional(seasonBtnClose, true);
    TextDrawSetSelectable(seasonBtnClose, true);

    return 1;
}

hook OnResetDay() {
    LoadWeeklyPass();
}

hook OnPlayerConnect(playerid) {
    seasonBackground[playerid] = CreatePlayerTextDraw(playerid, 314.000000, 155.000000, "_");
    PlayerTextDrawFont(playerid, seasonBackground[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, seasonBackground[playerid], 0.583333, 16.450017);
    PlayerTextDrawTextSize(playerid, seasonBackground[playerid], 73.500000, 664.000000);
    PlayerTextDrawSetOutline(playerid, seasonBackground[playerid], 1);
    PlayerTextDrawSetShadow(playerid, seasonBackground[playerid], 0);
    PlayerTextDrawAlignment(playerid, seasonBackground[playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, seasonBackground[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, seasonBackground[playerid], 656877567);
    PlayerTextDrawBoxColor(playerid, seasonBackground[playerid], 234);
    PlayerTextDrawUseBox(playerid, seasonBackground[playerid], true);
    PlayerTextDrawSetProportional(playerid, seasonBackground[playerid], true);
    PlayerTextDrawSetSelectable(playerid, seasonBackground[playerid], false);

    seasonServerTitle[playerid] = CreatePlayerTextDraw(playerid, 277.000000, 292.000000, SERVER_NAME);
    PlayerTextDrawFont(playerid, seasonServerTitle[playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawLetterSize(playerid, seasonServerTitle[playerid], 0.191666, 1.100000);
    PlayerTextDrawTextSize(playerid, seasonServerTitle[playerid], 520.000000, 41.000000);
    PlayerTextDrawSetOutline(playerid, seasonServerTitle[playerid], 0);
    PlayerTextDrawSetShadow(playerid, seasonServerTitle[playerid], 0);
    PlayerTextDrawAlignment(playerid, seasonServerTitle[playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, seasonServerTitle[playerid], -229);
    PlayerTextDrawBackgroundColor(playerid, seasonServerTitle[playerid], 255);
    PlayerTextDrawBoxColor(playerid, seasonServerTitle[playerid], 50);
    PlayerTextDrawUseBox(playerid, seasonServerTitle[playerid], false);
    PlayerTextDrawSetProportional(playerid, seasonServerTitle[playerid], true);
    PlayerTextDrawSetSelectable(playerid, seasonServerTitle[playerid], false);

    seasonTitle[playerid] = CreatePlayerTextDraw(playerid, 312.000000, 139.000000, "The First Pass");
    PlayerTextDrawFont(playerid, seasonTitle[playerid], TEXT_DRAW_FONT_0);
    PlayerTextDrawLetterSize(playerid, seasonTitle[playerid], 0.583333, 2.549999);
    PlayerTextDrawTextSize(playerid, seasonTitle[playerid], 400.000000, 444.500000);
    PlayerTextDrawSetOutline(playerid, seasonTitle[playerid], 1);
    PlayerTextDrawSetShadow(playerid, seasonTitle[playerid], 0);
    PlayerTextDrawAlignment(playerid, seasonTitle[playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, seasonTitle[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, seasonTitle[playerid], 255);
    PlayerTextDrawBoxColor(playerid, seasonTitle[playerid], 50);
    PlayerTextDrawUseBox(playerid, seasonTitle[playerid], false);
    PlayerTextDrawSetProportional(playerid, seasonTitle[playerid], true);
    PlayerTextDrawSetSelectable(playerid, seasonTitle[playerid], false);

    for(new i = 0; i < 7; i++) {
        // cor 16711935
        seasonItemBackground[i][playerid] = CreatePlayerTextDraw(playerid, 136.000000 - 55.0 + i*80.0, 171.000000, "_");
        PlayerTextDrawFont(playerid, seasonItemBackground[i][playerid], TEXT_DRAW_FONT_1);
        PlayerTextDrawLetterSize(playerid, seasonItemBackground[i][playerid], 0.566666, 12.650012);
        PlayerTextDrawTextSize(playerid, seasonItemBackground[i][playerid], 296.500000, 73.000000);
        PlayerTextDrawSetOutline(playerid, seasonItemBackground[i][playerid], 1);
        PlayerTextDrawSetShadow(playerid, seasonItemBackground[i][playerid], 0);
        PlayerTextDrawAlignment(playerid, seasonItemBackground[i][playerid], TEXT_DRAW_ALIGN_CENTER);
        PlayerTextDrawColor(playerid, seasonItemBackground[i][playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, seasonItemBackground[i][playerid], 255);
        PlayerTextDrawBoxColor(playerid, seasonItemBackground[i][playerid], 1296911871);
        PlayerTextDrawUseBox(playerid, seasonItemBackground[i][playerid], true);
        PlayerTextDrawSetProportional(playerid, seasonItemBackground[i][playerid], true);
        PlayerTextDrawSetSelectable(playerid, seasonItemBackground[i][playerid], false);

        seasonItemInternalBackground[i][playerid] = CreatePlayerTextDraw(playerid, 136.000000 - 55.0 + i*80.0, 173.000000, "_");
        PlayerTextDrawFont(playerid, seasonItemInternalBackground[i][playerid], TEXT_DRAW_FONT_1);
        PlayerTextDrawLetterSize(playerid, seasonItemInternalBackground[i][playerid], 0.566666, 12.200010);
        PlayerTextDrawTextSize(playerid, seasonItemInternalBackground[i][playerid], 296.500000, 69.000000);
        PlayerTextDrawSetOutline(playerid, seasonItemInternalBackground[i][playerid], 1);
        PlayerTextDrawSetShadow(playerid, seasonItemInternalBackground[i][playerid], 0);
        PlayerTextDrawAlignment(playerid, seasonItemInternalBackground[i][playerid], TEXT_DRAW_ALIGN_CENTER);
        PlayerTextDrawColor(playerid, seasonItemInternalBackground[i][playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, seasonItemInternalBackground[i][playerid], 255);
        PlayerTextDrawBoxColor(playerid, seasonItemInternalBackground[i][playerid], -1962934017);
        PlayerTextDrawUseBox(playerid, seasonItemInternalBackground[i][playerid], true);
        PlayerTextDrawSetProportional(playerid, seasonItemInternalBackground[i][playerid], true);
        PlayerTextDrawSetSelectable(playerid, seasonItemInternalBackground[i][playerid], false);

        seasonItem[i][playerid] = CreatePlayerTextDraw(playerid, 100.000000 - 55.0 + i*80.0, 172.000000, "Preview_Model");
        PlayerTextDrawFont(playerid, seasonItem[i][playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
        PlayerTextDrawLetterSize(playerid, seasonItem[i][playerid], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, seasonItem[i][playerid], 72.000000, 106.000000);
        PlayerTextDrawSetOutline(playerid, seasonItem[i][playerid], 0);
        PlayerTextDrawSetShadow(playerid, seasonItem[i][playerid], 0);
        PlayerTextDrawAlignment(playerid, seasonItem[i][playerid], TEXT_DRAW_ALIGN_LEFT);
        PlayerTextDrawColor(playerid, seasonItem[i][playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, seasonItem[i][playerid], -2145511680);
        PlayerTextDrawBoxColor(playerid, seasonItem[i][playerid], 16711680);
        PlayerTextDrawUseBox(playerid, seasonItem[i][playerid], false);
        PlayerTextDrawSetProportional(playerid, seasonItem[i][playerid], true);
        PlayerTextDrawSetSelectable(playerid, seasonItem[i][playerid], false);
        PlayerTextDrawSetPreviewModel(playerid, seasonItem[i][playerid], 444);
        PlayerTextDrawSetPreviewRot(playerid, seasonItem[i][playerid], -10.000000, 0.000000, -27.000000, 0.970000);
        PlayerTextDrawSetPreviewVehCol(playerid, seasonItem[i][playerid], 1, 1);

        seasonItemTitle[i][playerid] = CreatePlayerTextDraw(playerid, 128.000000 - 55.0 + i*80.0, 173.000000, "DIA 1");
        PlayerTextDrawFont(playerid, seasonItemTitle[i][playerid], TEXT_DRAW_FONT_1);
        PlayerTextDrawLetterSize(playerid, seasonItemTitle[i][playerid], 0.191666, 0.949998);
        PlayerTextDrawTextSize(playerid, seasonItemTitle[i][playerid], 620.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, seasonItemTitle[i][playerid], 0);
        PlayerTextDrawSetShadow(playerid, seasonItemTitle[i][playerid], 0);
        PlayerTextDrawAlignment(playerid, seasonItemTitle[i][playerid], TEXT_DRAW_ALIGN_LEFT);
        PlayerTextDrawColor(playerid, seasonItemTitle[i][playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, seasonItemTitle[i][playerid], 255);
        PlayerTextDrawBoxColor(playerid, seasonItemTitle[i][playerid], 50);
        PlayerTextDrawUseBox(playerid, seasonItemTitle[i][playerid], false);
        PlayerTextDrawSetProportional(playerid, seasonItemTitle[i][playerid], true);
        PlayerTextDrawSetSelectable(playerid, seasonItemTitle[i][playerid], false);

        seasonItemName[i][playerid] = CreatePlayerTextDraw(playerid, 136.000000 - 55.0 + i*80.0, 266.000000, "Pumpkin head");
        PlayerTextDrawFont(playerid, seasonItemName[i][playerid], TEXT_DRAW_FONT_1);
        PlayerTextDrawLetterSize(playerid, seasonItemName[i][playerid], 0.137500, 0.800000);
        PlayerTextDrawTextSize(playerid, seasonItemName[i][playerid], 485.000000, 67.000000);
        PlayerTextDrawSetOutline(playerid, seasonItemName[i][playerid], 0);
        PlayerTextDrawSetShadow(playerid, seasonItemName[i][playerid], 0);
        PlayerTextDrawAlignment(playerid, seasonItemName[i][playerid], TEXT_DRAW_ALIGN_CENTER);
        PlayerTextDrawColor(playerid, seasonItemName[i][playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, seasonItemName[i][playerid], 255);
        PlayerTextDrawBoxColor(playerid, seasonItemName[i][playerid], 50);
        PlayerTextDrawUseBox(playerid, seasonItemName[i][playerid], false);
        PlayerTextDrawSetProportional(playerid, seasonItemName[i][playerid], true);
        PlayerTextDrawSetSelectable(playerid, seasonItemName[i][playerid], false);

        seasonItemAmount[i][playerid] = CreatePlayerTextDraw(playerid, 136.000000 - 55.0 + i*80.0, 272.000000, "x1");
        PlayerTextDrawFont(playerid, seasonItemAmount[i][playerid], TEXT_DRAW_FONT_1);
        PlayerTextDrawLetterSize(playerid, seasonItemAmount[i][playerid], 0.137500, 0.800000);
        PlayerTextDrawTextSize(playerid, seasonItemAmount[i][playerid], 485.000000, 67.000000);
        PlayerTextDrawSetOutline(playerid, seasonItemAmount[i][playerid], 0);
        PlayerTextDrawSetShadow(playerid, seasonItemAmount[i][playerid], 0);
        PlayerTextDrawAlignment(playerid, seasonItemAmount[i][playerid], TEXT_DRAW_ALIGN_CENTER);
        PlayerTextDrawColor(playerid, seasonItemAmount[i][playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, seasonItemAmount[i][playerid], 255);
        PlayerTextDrawBoxColor(playerid, seasonItemAmount[i][playerid], 50);
        PlayerTextDrawUseBox(playerid, seasonItemAmount[i][playerid], false);
        PlayerTextDrawSetProportional(playerid, seasonItemAmount[i][playerid], true);
        PlayerTextDrawSetSelectable(playerid, seasonItemAmount[i][playerid], false);
    }

    UpdatePlayerWeeklyPass(playerid);
    return 1;
}

stock LoadPlayerWeeklyPassItems(playerid) {
    new query[400];

    mysql_format(MySQL_Handle, query, sizeof(query), "SELECT pw.*, wpi.dayOfWeek FROM player_wp_items pw \
        INNER JOIN weekly_passes_items wpi ON pw.weeklyPassItem = wpi.id \
        WHERE pw.weeklyPass = %d \
        AND pw.player = %d \
        ORDER BY wpi.dayOfWeek ASC LIMIT 7", WeeklyPassInfo[wpID], PlayerInfo[playerid][pID]);
	mysql_tquery(MySQL_Handle, query, "OnPlayerWeeklyPassItemsLoaded", "i", playerid);
}

CALLBACK:OnPlayerWeeklyPassItemsLoaded(playerid) {
    for(new i = 0; i < 7; i++) {
        WeeklyPassPlayerItemInfo[playerid][i][wppID] = 0;
        WeeklyPassPlayerItemInfo[playerid][i][wppReceived] = 0;
        WeeklyPassPlayerItemInfo[playerid][i][wppItemID] = WeeklyPassItemInfo[i][wpiID];
    }

	new rows = MYSQL_GetRowsCount();
    for(new i = 0; i < rows; i++) {
        new day = MYSQL_GetInt(i, "dayOfWeek");
        WeeklyPassPlayerItemInfo[playerid][day][wppID] = MYSQL_GetInt(i, "id");
        WeeklyPassPlayerItemInfo[playerid][day][wppReceived] = 1;
    }
}

hook OnPlayerLogin(playerid) {
    LoadPlayerWeeklyPassItems(playerid);
}

stock ShowPlayerWeeklyPass(playerid, manual=0) {
    PlayerTextDrawShow(playerid, seasonBackground[playerid]);
    PlayerTextDrawShow(playerid, seasonServerTitle[playerid]);
    PlayerTextDrawShow(playerid, seasonTitle[playerid]);

    if(manual) {
        TextDrawShowForPlayer(playerid, seasonBtnClose);
        SelectTextDraw(playerid, 0xFFFFFF80);
    }

    for(new i = 0; i < 7; i++) {

        new backgroundColor = WeeklyPassPlayerItemInfo[playerid][i][wppReceived] ? 833102591 : 1296911871;
        PlayerTextDrawBoxColor(playerid, seasonItemBackground[i][playerid], backgroundColor);
        PlayerTextDrawShow(playerid, seasonItemBackground[i][playerid]);
        PlayerTextDrawShow(playerid, seasonItemInternalBackground[i][playerid]);
        PlayerTextDrawShow(playerid, seasonItem[i][playerid]);
        PlayerTextDrawShow(playerid, seasonItemTitle[i][playerid]);
        PlayerTextDrawShow(playerid, seasonItemName[i][playerid]);
        PlayerTextDrawShow(playerid, seasonItemAmount[i][playerid]);
    }

    SetPVarInt(playerid, "WeeklyPassVisible", 1);
}

timer HidePlayerWeeklyPass[7000](playerid) {
    PlayerTextDrawHide(playerid, seasonBackground[playerid]);
    PlayerTextDrawHide(playerid, seasonServerTitle[playerid]);
    PlayerTextDrawHide(playerid, seasonTitle[playerid]);
    TextDrawHideForPlayer(playerid, seasonBtnClose);

    for(new i = 0; i < 7; i++) {
        PlayerTextDrawHide(playerid, seasonItemBackground[i][playerid]);
        PlayerTextDrawHide(playerid, seasonItemInternalBackground[i][playerid]);
        PlayerTextDrawHide(playerid, seasonItem[i][playerid]);
        PlayerTextDrawHide(playerid, seasonItemTitle[i][playerid]);
        PlayerTextDrawHide(playerid, seasonItemName[i][playerid]);
        PlayerTextDrawHide(playerid, seasonItemAmount[i][playerid]);
    }

    SetPVarInt(playerid, "WeeklyPassVisible", 0);
}

stock MovePlayerWeeklyPassToNew(playerid) {
    WeeklyPassPlayerInfo[playerid][wppWeeklyPassID] = WeeklyPassInfo[wpInProgress] ? WeeklyPassInfo[wpID] : 0;
    WeeklyPassPlayerInfo[playerid][wppPlayedTime] = 0;
    WeeklyPassPlayerInfo[playerid][wppDay] = 0;
    WeeklyPassPlayerInfo[playerid][wppAvailable] = WeeklyPassInfo[wpPaid] ? 0 : 1;
}

stock CheckPlayerWeeklyPass(playerid) {
    new day = WeeklyPassPlayerInfo[playerid][wppDay];
    if(day == 7 || !WeeklyPassInfo[wpInProgress])
        return;

    if(WeeklyPassPlayerInfo[playerid][wppWeeklyPassID] != WeeklyPassInfo[wpID]) {
        MovePlayerWeeklyPassToNew(playerid);
    }
    else if(WeeklyPassPlayerItemInfo[playerid][day][wppReceived]) {
        WeeklyPassPlayerInfo[playerid][wppPlayedTime] = 0;
        WeeklyPassPlayerInfo[playerid][wppDay] += 1;
    }
    else if(
        WeeklyPassPlayerInfo[playerid][wppAvailable] && 
        WeeklyPassPlayerInfo[playerid][wppPlayedTime] >= WeeklyPassItemInfo[day][wpiTime]
    ) {

        SetDayOnWeeklyPassForPlayer(playerid);
    }
}

stock AddTimeOnWeeklyPass(playerid) {
    if(WeeklyPassPlayerInfo[playerid][wppWeeklyPassID] != WeeklyPassInfo[wpID]) {
        MovePlayerWeeklyPassToNew(playerid);
    }

    new day = WeeklyPassPlayerInfo[playerid][wppDay];
    if(day < 7 && WeeklyPassItemInfo[day][wpiAvailable] && WeeklyPassPlayerInfo[playerid][wppAvailable]) {
        WeeklyPassPlayerInfo[playerid][wppPlayedTime] += 1;
        CheckPlayerWeeklyPass(playerid);
    }
}

stock SetDayOnWeeklyPassForPlayer(playerid) {
    new day = WeeklyPassPlayerInfo[playerid][wppDay],
        query[600];
    if(!WeeklyPassPlayerItemInfo[playerid][day][wppReceived]) {
        givePlayerItem(
            playerid, 
            WeeklyPassItemInfo[day][wpiType], 
            WeeklyPassItemInfo[day][wpiModel], 
            WeeklyPassItemInfo[day][wpiAmount],
            WeeklyPassItemInfo[day][wpiName],
            WeeklyPassItemInfo[day][wpiColor1],
            WeeklyPassItemInfo[day][wpiColor2]
        );
        WeeklyPassPlayerItemInfo[playerid][day][wppReceived] = 1;
        WeeklyPassPlayerInfo[playerid][wppPlayedTime] = 0;
        WeeklyPassPlayerInfo[playerid][wppDay] += 1;
        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
        mysql_format(MySQL_Handle, query, sizeof(query), "INSERT INTO player_wp_items \
            (id, weeklyPass, weeklyPassItem, player, dateReceived) VALUES \
            (DEFAULT, %d, %d, %d, NOW())", WeeklyPassInfo[wpID], WeeklyPassItemInfo[day][wpiID], PlayerInfo[playerid][pID]);
        mysql_tquery(MySQL_Handle, query);

        ShowPlayerWeeklyPass(playerid);
        defer HidePlayerWeeklyPass(playerid);
    }
}

hook OnClickDynamicTextDraw(playerid, Text:textid)
{
	if(textid == seasonBtnClose || (textid == Text:INVALID_TEXT_DRAW && GetPVarInt(playerid, "WeeklyPassVisible"))) {
        HidePlayerWeeklyPass(playerid);
        CancelSelectTextDraw(playerid);
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if(dialogid == 650) {
        if(!response)
            return 1;

        if(listitem == 0) {
            if(!WeeklyPassInfo[wpInProgress])
                return SendClientMessage(playerid, -1, "Não há um passe em andamento no momento.");

            new day = WeeklyPassPlayerInfo[playerid][wppDay],
                status[60],
                string[128];
            
            format(string, 128, "|-~-~-~-~-~-~-~-~-~| Progresso - %s |-~-~-~-~-~-~-~-~-~|", WeeklyPassInfo[wpName]);
            new size = strlen(string);
            SendClientMessage(playerid, 0x6D6E6DFF, string);

            if(WeeklyPassPlayerInfo[playerid][wppAvailable]) {
                if(day != 7) {
                    if(WeeklyPassItemInfo[day][wpiAvailable])
                        format(status, 60, C_MONEY"EM PROGRESSO");
                    else
                        format(status, 60, C_GRAY"BLOQUEADO");
                    SendMsgF(playerid, COLOR_WHITE, "Dia da recompensa: "C_GREEN"%d "C_WHITE"- %s", day+1, status);
                    SendMsgF(playerid, COLOR_WHITE, "Tempo necessário: "C_CYAN"%s", ConvertTime(WeeklyPassItemInfo[day][wpiTime]));

                    if(WeeklyPassItemInfo[day][wpiAvailable]) {
                        new Float:progress = (1.0*WeeklyPassPlayerInfo[playerid][wppPlayedTime]) / WeeklyPassItemInfo[day][wpiTime];
                        new chars = 26;
                        new complete = floatround(chars*progress, floatround_floor);

                        new progressBar[30];
                        for(new i = 0; i < chars; i++) {
                            if(i < complete)
                                strcat(progressBar, "/");
                            else
                                strcat(progressBar, "-");
                        }

                        SendMsgF(playerid, COLOR_WHITE, "Tempo restante: "C_GRAY"%s", ConvertTime(WeeklyPassItemInfo[day][wpiTime] - WeeklyPassPlayerInfo[playerid][wppPlayedTime]));
                        SendMsgF(playerid, COLOR_WHITE, "Progresso: [%s] (%.0f por cento)", progressBar, 100.00*progress);
                    }
                    else {
                        new date[16];
                        TimeFormat(WeeklyPassItemInfo[day][wpiDateAvailable], "%d/%m/%Y", date);
                        SendMsgF(playerid, COLOR_WHITE, "Disponível a partir de: %s", date);
                    }
                }
                else {
                    SendClientMessage(playerid, 0x58B858FF, "Parabéns! Você recebeu todas as recompensas do passe.");
                }
            }
            else {
                SendClientMessage(playerid, 0x9FA19FFF, "-> O passe atual é VIP e você ainda não o comprou. Acesse {00FF00}/menucash {9FA19F}para adquiri-lo.");
            }

            format(string, 128, "");
            for(new i = 0; i < size-1; i++) {
                if(i % 2 == 0)
                    strcat(string, "-");
                else
                    strcat(string, "~");
            }
            SendMsgF(playerid, 0x6D6E6DFF, "|%s|", string);

            ShowPlayerWeeklyPass(playerid, 1);
        }
        else if(listitem == 1) {
            MEGAString[0] = EOS;

            new startDate[16], endDate[16];
			TimeFormat(WeeklyPassInfo[wpStartDate], "%d/%m/%Y", startDate);
			TimeFormat(WeeklyPassInfo[wpEndDate], "%d/%m/%Y", endDate);

            FormatCat(MEGAString, "\n{FFFFFF}		{6860F7}%s 			\n", WeeklyPassInfo[wpName]);
            strcat(MEGAString, "\n{DC0139}============================================================\n");

            strcat(MEGAString, "\n{FFBB00}Informações do passe:\n\n");
            FormatCat(MEGAString, "{7D8084}Data de início:				{DBDCE0}%s\n", startDate);
            FormatCat(MEGAString, "{7D8084}Data de fim:				{DBDCE0}%s\n\n", endDate);

            strcat(MEGAString, "\n{AEAFB0}OBS: {DBDCE0}O passe só estará disponível dentro do período acima e cada item só estará");
            strcat(MEGAString, "\n{DBDCE0}e cada item só estará disponível a partir da data informada em cada item abaixo.\n\n");


            strcat(MEGAString, "\n{FFBB00}Premiação do passe:\n\n");

            for(new i = 0; i < 7; i++) {
                new date[16];
                TimeFormat(WeeklyPassItemInfo[i][wpiDateAvailable], "%d/%m/%Y", date);

                FormatCat(MEGAString, "{FFBB00}%dº dia)\n", i+1);
                FormatCat(MEGAString, "  {7D8084}Recompensa:				{49E468}%s (x%d)\n", WeeklyPassItemInfo[i][wpiName], WeeklyPassItemInfo[i][wpiAmount]);
                FormatCat(MEGAString, "  {7D8084}Ativida requerida:			{DBDCE0}%s\n", ConvertTime(WeeklyPassItemInfo[i][wpiTime]));
                FormatCat(MEGAString, "  {7D8084}Disponível em:			{DBDCE0}%s\n\n", date);
            }

            strcat(MEGAString, "\n{DC0139}============================================================\n");

            return ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Informações do passe", MEGAString, "Entendi", "");
        }
    }
    return 1;
}

CMD:infopasse(playerid) {
    if(!WeeklyPassInfo[wpInProgress])
        return SendClientMessage(playerid, -1, "Não há um passe em andamento.");

    new string[128];
	MEGAString[0] = EOS;

	format(string, sizeof string, "{FFFFFF}Meu progresso\n");
    strcat(MEGAString, string);
    format(string, sizeof string, "{FFFFFF}Informações do passe\n");
    strcat(MEGAString, string);
    
	ShowPlayerDialog(playerid, 650, DIALOG_STYLE_LIST, "Ajuda do passe", MEGAString, "Acessar", "Cancelar");
    return 1;
}