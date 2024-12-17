
#include <YSI_Coding\y_hooks>

#define _HUD_SYSTEM_ON true

#include <baloon_info>

#include <action_textdraw>
#include <approach_textdraw>

// Sistema de timer
#include <timer>

// Sistema de 'procurando' na HUD
#include <procurando_info>

// Sistema de td na mira
#include <sniper_shot>

// Textdraws: Velocimetro
#include <td-velocity>

// Textdraws: Velocimetro
#include <velo-textdraws>

new 
	Text:_hud_textdraws[5],
	Text:_salary_textdraw[2],
    Text:_cash_textdraw,
    Text:_email_alert_textdraw[6],
    Text:_clock_textdraw,
    Text:_needs_textdraw[2],
    PlayerText:_clock_ptextdraw[MAX_PLAYERS],
	PlayerText:_salary_ptextdraw[MAX_PLAYERS],
	PlayerText:_cash_ptextdraw[MAX_PLAYERS],
	PlayerText:_email_alert_ptextd[MAX_PLAYERS],
    PlayerText:popup_textdraw[MAX_PLAYERS],
    PlayerText:_needhunger_progress[MAX_PLAYERS],
    PlayerText:_needthirst_progress[MAX_PLAYERS],
    PlayerText:loadBarraTela[MAX_PLAYERS][2];

#include <hud_textdraws>

// hook OnLoadVersion() 
// {
//     new string[20];

//     format(string, sizeof(string), "VERSAO: %s", SERVER_VERSION);
// 	TextDrawSetString(_hud_textdraws[0], string);

//     return 1;
// }

ptask SalaryUpdate[1000](playerid)
{
    static string[25];
    format(string, sizeof(string), " %s", ConvertTime(Player_GetPayday(playerid)));
	PlayerTextDrawSetString(playerid, _salary_ptextdraw[playerid], string);

    format(string, sizeof(string), "%s", GetCurrentDateHour(ONLY_CURRENT_HOUR_NSEC));
	PlayerTextDrawSetString(playerid, _clock_ptextdraw[playerid], string);
}

hook OnResetDay() 
{
    new string[20];
    strmid(string, GetMonthName(GetCurrentMonth()), 0, 2);
    format(string, sizeof(string), "%d %s %d", GetCurrentDay(), string, GetCurrentYear());
	TextDrawSetString(_clock_textdraw, string);

    return 1;
}

hook OnGameModeInit() 
{
    HUD_TextDrawCreates();

    new string[20];
    strmid(string, GetMonthName(GetCurrentMonth()), 0, 3);
    format(string, sizeof(string), "%d %s %d", GetCurrentDay(), string, GetCurrentYear());
	TextDrawSetString(_clock_textdraw, string);

    return 1;
}

hook OnPlayerLogin(playerid) {

    HUD_CreatePlayerTextdraws(playerid);

    new string[11];
	format(string, sizeof(string), "%s", getFormatText(Player_GetCash(playerid)));
	PlayerTextDrawSetString(playerid, _cash_ptextdraw[playerid], string);

    HUD_ShowForPlayer(playerid);

    return 1;
}

// Funções;
stock HUD_ShowForPlayer(playerid)
{
    // for(new text; text < sizeof(_hud_pascoa_textdraws); text++)
	// 	TextDrawShowForPlayer(playerid, _hud_pascoa_textdraws[text]);

	for(new text; text < sizeof(_hud_textdraws); text++)
		TextDrawShowForPlayer(playerid, _hud_textdraws[text]);

    for(new text; text < sizeof(_email_alert_textdraw) - 1; text++)
		TextDrawShowForPlayer(playerid, _email_alert_textdraw[text]);

	TextDrawShowForPlayer(playerid, _clock_textdraw);

    for(new text; text < sizeof(_salary_textdraw); text++)
		TextDrawShowForPlayer(playerid, _salary_textdraw[text]);

	TextDrawShowForPlayer(playerid, _cash_textdraw);

	PlayerTextDrawShow(playerid, _clock_ptextdraw[playerid]);
	PlayerTextDrawShow(playerid, _salary_ptextdraw[playerid]);
	PlayerTextDrawShow(playerid, _cash_ptextdraw[playerid]);
	PlayerTextDrawShow(playerid, _email_alert_ptextd[playerid]);

	CONFIG_NeedSystem(playerid, true);
}

stock HideTextDrawHUD(playerid)
{
//     for(new text; text < sizeof(_hud_pascoa_textdraws); text++)
// 		TextDrawHideForPlayer(playerid, _hud_pascoa_textdraws[text]);

	for(new text; text < sizeof(_hud_textdraws); text++)
		TextDrawHideForPlayer(playerid, _hud_textdraws[text]);

    for(new text; text < sizeof(_email_alert_textdraw) - 1; text++)
		TextDrawHideForPlayer(playerid, _email_alert_textdraw[text]);

	TextDrawHideForPlayer(playerid, _clock_textdraw);

    for(new text; text < sizeof(_salary_textdraw); text++)
		TextDrawHideForPlayer(playerid, _salary_textdraw[text]);

    TextDrawHideForPlayer(playerid, _cash_textdraw);

	PlayerTextDrawHide(playerid, _clock_ptextdraw[playerid]);
	PlayerTextDrawHide(playerid, _salary_ptextdraw[playerid]);
	PlayerTextDrawHide(playerid, _cash_ptextdraw[playerid]);
	PlayerTextDrawHide(playerid, _email_alert_ptextd[playerid]);

	CONFIG_NeedSystem(playerid, false);
}

stock HUD_UpdateNeeds(playerid, Float:fome, Float:sede) {

    new Float:size;

    fome = floatround(fome, floatround_ceil);
    sede = floatround(sede, floatround_ceil);

    size = -0.49 - (fome * 0.0121); // -1.70
    if (size < -1.70) size = -1.70;
    if (IsValidDynamicPlayerTextDraw(playerid, _needhunger_progress[playerid]))
    {
        PlayerTextDrawLetterSize(playerid, _needhunger_progress[playerid], 0.67, size);
        PlayerTextDrawShow(playerid, _needhunger_progress[playerid]);
    }

    size = -0.49 - (sede * 0.0121); // -1.70
    if (size < -1.70) size = -1.70;
    if (IsValidDynamicPlayerTextDraw(playerid, _needthirst_progress[playerid]))
    {
        PlayerTextDrawLetterSize(playerid, _needthirst_progress[playerid], 0.67, size);
        PlayerTextDrawShow(playerid, _needthirst_progress[playerid]);
    }
}

stock CONFIG_NeedSystem(playerid, bool:status2 = true)
{
    if (status2)
    {
        for(new loop1; loop1 < sizeof(_needs_textdraw); loop1++)
            TextDrawShowForPlayer(playerid, _needs_textdraw[loop1]);

        PlayerTextDrawShow(playerid, _needhunger_progress[playerid]);
        PlayerTextDrawShow(playerid, _needthirst_progress[playerid]);
    }
    else
    {
        for(new loop1; loop1 < sizeof(_needs_textdraw); loop1++)
            TextDrawHideForPlayer(playerid, _needs_textdraw[loop1]);

        PlayerTextDrawHide(playerid, _needhunger_progress[playerid]);
        PlayerTextDrawHide(playerid, _needthirst_progress[playerid]);
    }
}

stock CONFIG_DrugSystem(playerid, drugid, bool:status2 = true)
{
    if (HasPlayerAnyPopup(playerid))
        return;

    if (status2)
    {
        PlayerTextDrawShow(playerid, _drugs_playertextdraw[drugid][playerid]);
        TextDrawShowForPlayer(playerid, _drugs_textdraw[drugid]);
    }
    else
    {
        PlayerTextDrawHide(playerid, _drugs_playertextdraw[drugid][playerid]);
        TextDrawHideForPlayer(playerid, _drugs_textdraw[drugid]);
    }
}

stock CreateTelaLogin() {
    //Textdraws
    login_textdraws[0] = TextDrawCreate(-2.000000, -1.000000, "_");
    TextDrawFont(login_textdraws[0], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(login_textdraws[0], 0.570833, 49.850013);
    TextDrawTextSize(login_textdraws[0], 184.500000, 17.000000);
    TextDrawSetOutline(login_textdraws[0], 1);
    TextDrawSetShadow(login_textdraws[0], 0);
    TextDrawAlignment(login_textdraws[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(login_textdraws[0], -1);
    TextDrawBackgroundColor(login_textdraws[0], 255);
    TextDrawBoxColor(login_textdraws[0], 190);
    TextDrawUseBox(login_textdraws[0], true);
    TextDrawSetProportional(login_textdraws[0], true);
    TextDrawSetSelectable(login_textdraws[0], false);

    login_textdraws[1] = TextDrawCreate(25.000000, 309.000000, "_");
    TextDrawFont(login_textdraws[1], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(login_textdraws[1], 0.229166, 2.899996);
    TextDrawTextSize(login_textdraws[1], 144.500000, 17.000000);
    TextDrawSetOutline(login_textdraws[1], 0);
    TextDrawSetShadow(login_textdraws[1], 0);
    TextDrawAlignment(login_textdraws[1], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(login_textdraws[1], -1);
    TextDrawBackgroundColor(login_textdraws[1], 255);
    TextDrawBoxColor(login_textdraws[1], -1094795743);
    TextDrawUseBox(login_textdraws[1], true);
    TextDrawSetProportional(login_textdraws[1], true);
    TextDrawSetSelectable(login_textdraws[1], false);

    login_textdraws[2] = TextDrawCreate(15.000000, 271.000000, "_");
    TextDrawFont(login_textdraws[2], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(login_textdraws[2], 0.229166, -0.300000);
    TextDrawTextSize(login_textdraws[2], 159.000000, 17.000000);
    TextDrawSetOutline(login_textdraws[2], 0);
    TextDrawSetShadow(login_textdraws[2], 0);
    TextDrawAlignment(login_textdraws[2], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(login_textdraws[2], -1);
    TextDrawBackgroundColor(login_textdraws[2], 255);
    TextDrawBoxColor(login_textdraws[2], 1296911871);
    TextDrawUseBox(login_textdraws[2], true);
    TextDrawSetProportional(login_textdraws[2], true);
    TextDrawSetSelectable(login_textdraws[2], false);

    login_textdraws[3] = TextDrawCreate(15.000000, 128.000000, "_");
    TextDrawFont(login_textdraws[3], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(login_textdraws[3], 0.229166, -0.300000);
    TextDrawTextSize(login_textdraws[3], 159.000000, 17.000000);
    TextDrawSetOutline(login_textdraws[3], 0);
    TextDrawSetShadow(login_textdraws[3], 0);
    TextDrawAlignment(login_textdraws[3], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(login_textdraws[3], -1);
    TextDrawBackgroundColor(login_textdraws[3], 255);
    TextDrawBoxColor(login_textdraws[3], 1296911871);
    TextDrawUseBox(login_textdraws[3], true);
    TextDrawSetProportional(login_textdraws[3], true);
    TextDrawSetSelectable(login_textdraws[3], false);

    login_textdraws[4] = TextDrawCreate(34.000000, 312.000000, "Preview_Model");
    TextDrawFont(login_textdraws[4], TEXT_DRAW_FONT_MODEL_PREVIEW);
    TextDrawLetterSize(login_textdraws[4], 0.600000, 2.000000);
    TextDrawTextSize(login_textdraws[4], 18.500000, 20.500000);
    TextDrawSetOutline(login_textdraws[4], 0);
    TextDrawSetShadow(login_textdraws[4], 0);
    TextDrawAlignment(login_textdraws[4], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(login_textdraws[4], 16711935);
    TextDrawBackgroundColor(login_textdraws[4], 0);
    TextDrawBoxColor(login_textdraws[4], 255);
    TextDrawUseBox(login_textdraws[4], false);
    TextDrawSetProportional(login_textdraws[4], true);
    TextDrawSetSelectable(login_textdraws[4], false);
    TextDrawSetPreviewModel(login_textdraws[4], 19134);
    TextDrawSetPreviewRot(login_textdraws[4], 43.000000, 265.000000, -221.000000, 1.000000);
    TextDrawSetPreviewVehCol(login_textdraws[4], 1, 1);

    login_textdraws[5] = TextDrawCreate(16.000000, 161.000000, "-");
    TextDrawFont(login_textdraws[5], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(login_textdraws[5], 0.166666, 0.850000);
    TextDrawTextSize(login_textdraws[5], 406.000000, 17.000000);
    TextDrawSetOutline(login_textdraws[5], 0);
    TextDrawSetShadow(login_textdraws[5], 0);
    TextDrawAlignment(login_textdraws[5], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(login_textdraws[5], 9109759);
    TextDrawBackgroundColor(login_textdraws[5], 255);
    TextDrawBoxColor(login_textdraws[5], 50);
    TextDrawUseBox(login_textdraws[5], false);
    TextDrawSetProportional(login_textdraws[5], true);
    TextDrawSetSelectable(login_textdraws[5], false);

    login_textdraws[6] = TextDrawCreate(82.000000, 337.000000, "Esqueci minha senha");
    TextDrawFont(login_textdraws[6], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(login_textdraws[6], 0.137500, 0.899999);
    TextDrawTextSize(login_textdraws[6], 164.000000, 19.500000);
    TextDrawSetOutline(login_textdraws[6], 0);
    TextDrawSetShadow(login_textdraws[6], 0);
    TextDrawAlignment(login_textdraws[6], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(login_textdraws[6], 1296911871);
    TextDrawBackgroundColor(login_textdraws[6], 255);
    TextDrawBoxColor(login_textdraws[6], 50);
    TextDrawUseBox(login_textdraws[6], false);
    TextDrawSetProportional(login_textdraws[6], true);
    TextDrawSetSelectable(login_textdraws[6], true);

    login_textdraws[7] = TextDrawCreate(158.000000, 161.000000, "-"); // $~w~2.000.000.000
    TextDrawFont(login_textdraws[7], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(login_textdraws[7], 0.166666, 0.850000);
    TextDrawTextSize(login_textdraws[7], 406.000000, 17.000000);
    TextDrawSetOutline(login_textdraws[7], 0);
    TextDrawSetShadow(login_textdraws[7], 0);
    TextDrawAlignment(login_textdraws[7], TEXT_DRAW_ALIGN_RIGHT);
    TextDrawColor(login_textdraws[7], 1097458175);
    TextDrawBackgroundColor(login_textdraws[7], 255);
    TextDrawBoxColor(login_textdraws[7], 50);
    TextDrawUseBox(login_textdraws[7], false);
    TextDrawSetProportional(login_textdraws[7], true);
    TextDrawSetSelectable(login_textdraws[7], false);

    login_textdraws[8] = TextDrawCreate(156.000000, 222.000000, "-");
    TextDrawFont(login_textdraws[8], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(login_textdraws[8], 0.287499, 1.250000);
    TextDrawTextSize(login_textdraws[8], 406.000000, 17.000000);
    TextDrawSetOutline(login_textdraws[8], 0);
    TextDrawSetShadow(login_textdraws[8], 0);
    TextDrawAlignment(login_textdraws[8], TEXT_DRAW_ALIGN_RIGHT);
    TextDrawColor(login_textdraws[8], -1);
    TextDrawBackgroundColor(login_textdraws[8], 255);
    TextDrawBoxColor(login_textdraws[8], 50);
    TextDrawUseBox(login_textdraws[8], false);
    TextDrawSetProportional(login_textdraws[8], true);
    TextDrawSetSelectable(login_textdraws[8], false);

    login_textdraws[9] = TextDrawCreate(16.000000, 222.000000, "-");
    TextDrawFont(login_textdraws[9], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(login_textdraws[9], 0.287499, 1.250000);
    TextDrawTextSize(login_textdraws[9], 406.000000, 17.000000);
    TextDrawSetOutline(login_textdraws[9], 0);
    TextDrawSetShadow(login_textdraws[9], 0);
    TextDrawAlignment(login_textdraws[9], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(login_textdraws[9], -1);
    TextDrawBackgroundColor(login_textdraws[9], 255);
    TextDrawBoxColor(login_textdraws[9], 50);
    TextDrawUseBox(login_textdraws[9], false);
    TextDrawSetProportional(login_textdraws[9], true);
    TextDrawSetSelectable(login_textdraws[9], false);

    login_textdraws[10] = TextDrawCreate(16.000000, 148.000000, "Economia de dinheiro              Economia de cash");
    TextDrawFont(login_textdraws[10], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(login_textdraws[10], 0.137500, 0.899999);
    TextDrawTextSize(login_textdraws[10], 159.000000, 17.000000);
    TextDrawSetOutline(login_textdraws[10], 0);
    TextDrawSetShadow(login_textdraws[10], 0);
    TextDrawAlignment(login_textdraws[10], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(login_textdraws[10], 1296911871);
    TextDrawBackgroundColor(login_textdraws[10], 255);
    TextDrawBoxColor(login_textdraws[10], 50);
    TextDrawUseBox(login_textdraws[10], false);
    TextDrawSetProportional(login_textdraws[10], true);

    login_textdraws[11] = TextDrawCreate(16.000000, 211.000000, "Logins diarios                    Players Conectados");
    TextDrawFont(login_textdraws[11], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(login_textdraws[11], 0.137500, 0.899999);
    TextDrawTextSize(login_textdraws[11], 159.000000, 17.000000);
    TextDrawSetOutline(login_textdraws[11], 0);
    TextDrawSetShadow(login_textdraws[11], 0);
    TextDrawAlignment(login_textdraws[11], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(login_textdraws[11], 1296911871);
    TextDrawBackgroundColor(login_textdraws[11], 255);
    TextDrawBoxColor(login_textdraws[11], 50);
    TextDrawUseBox(login_textdraws[11], false);
    TextDrawSetProportional(login_textdraws[11], true);

    LoadLoginScreenValues();
}

task LoadLoginScreenValues[60000 * 20]() {
	mysql_tquery(MySQL_Handle, "SELECT \
        (SELECT SUM(p.dinheiro) + SUM(p.dinheiro_banco) FROM player p) +  \
        (SELECT SUM(i.quantidade) FROM inventarios i WHERE i.tipo = 10) as 'money', \
        (SELECT SUM(p.cash) FROM player p) as 'cash', \
        (SELECT COUNT(p.id) FROM player p WHERE ultimo_login like CONCAT(CURDATE(), '%')) as 'logins'", "OnScreenValuesLoaded");
}

CALLBACK:OnScreenValuesLoaded() {
    new logins = MYSQL_GetInt(0, "logins"),
        stringtd[30];

	format(stringtd, sizeof(stringtd), "$%s", FormatNumericString(MYSQL_GetString(0, "money")));
	TextDrawSetString(login_textdraws[5], stringtd);

    format(stringtd, sizeof(stringtd), "C$%s", FormatNumericString(MYSQL_GetString(0, "cash")));
	TextDrawSetString(login_textdraws[7], stringtd);

    format(stringtd, sizeof(stringtd), "%s", getFormatText(logins));
	TextDrawSetString(login_textdraws[9], stringtd);
}

stock CreatePlayerLoginTD(playerid)
{
    //Player Textdraws
    login_ptextdraws[0][playerid] = CreatePlayerTextDraw(playerid, 23.000000, 99.000000, "Bem vindo, ~n~~w~Theus_Crazzy");
    PlayerTextDrawFont(playerid, login_ptextdraws[0][playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, login_ptextdraws[0][playerid], 0.245829, 1.149999);
    PlayerTextDrawTextSize(playerid, login_ptextdraws[0][playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, login_ptextdraws[0][playerid], 0);
    PlayerTextDrawSetShadow(playerid, login_ptextdraws[0][playerid], 0);
    PlayerTextDrawAlignment(playerid, login_ptextdraws[0][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, login_ptextdraws[0][playerid], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, login_ptextdraws[0][playerid], 255);
    PlayerTextDrawBoxColor(playerid, login_ptextdraws[0][playerid], 50);
    PlayerTextDrawUseBox(playerid, login_ptextdraws[0][playerid], false);
    PlayerTextDrawSetProportional(playerid, login_ptextdraws[0][playerid], true);
    PlayerTextDrawSetSelectable(playerid, login_ptextdraws[0][playerid], false);

    login_ptextdraws[1][playerid] = CreatePlayerTextDraw(playerid, 23.000000, 272.000000, "~y~Buscando ~w~sua conta. ~n~~w~Por favor, aguarde:");
    PlayerTextDrawFont(playerid, login_ptextdraws[1][playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, login_ptextdraws[1][playerid], 0.229166, 1.149999);
    PlayerTextDrawTextSize(playerid, login_ptextdraws[1][playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, login_ptextdraws[1][playerid], 0);
    PlayerTextDrawSetShadow(playerid, login_ptextdraws[1][playerid], 0);
    PlayerTextDrawAlignment(playerid, login_ptextdraws[1][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, login_ptextdraws[1][playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, login_ptextdraws[1][playerid], 255);
    PlayerTextDrawBoxColor(playerid, login_ptextdraws[1][playerid], 50);
    PlayerTextDrawUseBox(playerid, login_ptextdraws[1][playerid], false);
    PlayerTextDrawSetProportional(playerid, login_ptextdraws[1][playerid], true);
    PlayerTextDrawSetSelectable(playerid, login_ptextdraws[1][playerid], false);

    login_ptextdraws[2][playerid] = CreatePlayerTextDraw(playerid, 91.000000, 316.000000, "Aguarde");
    PlayerTextDrawFont(playerid, login_ptextdraws[2][playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawLetterSize(playerid, login_ptextdraws[2][playerid], 0.229166, 1.149999);
    PlayerTextDrawTextSize(playerid, login_ptextdraws[2][playerid], 13.500000, 67.500000);
    PlayerTextDrawSetOutline(playerid, login_ptextdraws[2][playerid], 0);
    PlayerTextDrawSetShadow(playerid, login_ptextdraws[2][playerid], 0);
    PlayerTextDrawAlignment(playerid, login_ptextdraws[2][playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, login_ptextdraws[2][playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, login_ptextdraws[2][playerid], 255);
    PlayerTextDrawBoxColor(playerid, login_ptextdraws[2][playerid], 50);
    PlayerTextDrawUseBox(playerid, login_ptextdraws[2][playerid], false);
    PlayerTextDrawSetProportional(playerid, login_ptextdraws[2][playerid], true);
    PlayerTextDrawSetSelectable(playerid, login_ptextdraws[2][playerid], true);
}

new Text:loadTela[4];

stock CreateLoadTela()
{
    loadTela[0] = TextDrawCreate(0.000000, 0.000000, "_");
    TextDrawFont(loadTela[0], TEXT_DRAW_FONT_0);
    TextDrawLetterSize(loadTela[0], 0.999997, 49.999938);
    TextDrawTextSize(loadTela[0], 640.000000, 17.000000);
    TextDrawSetOutline(loadTela[0], 0);
    TextDrawSetShadow(loadTela[0], 0);
    TextDrawAlignment(loadTela[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(loadTela[0], 255);
    TextDrawBackgroundColor(loadTela[0], 255);
    TextDrawBoxColor(loadTela[0], 255);
    TextDrawUseBox(loadTela[0], true);

    loadTela[1] = TextDrawCreate(311.000000, 193.000000, "ld_beat:cring");
    TextDrawFont(loadTela[1], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(loadTela[1], 0.600000, 2.000000);
    TextDrawTextSize(loadTela[1], 28.000000, 34.500000);
    TextDrawSetOutline(loadTela[1], 1);
    TextDrawSetShadow(loadTela[1], 0);
    TextDrawAlignment(loadTela[1], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(loadTela[1], SERVER_COLOR_PRIMARY);
    TextDrawBackgroundColor(loadTela[1], 255);
    TextDrawBoxColor(loadTela[1], 50);
    TextDrawUseBox(loadTela[1], true);
    TextDrawSetProportional(loadTela[1], true);
    TextDrawSetSelectable(loadTela[1], false);

    loadTela[2] = TextDrawCreate(269.000000, 196.000000, SERVER_TAG);
    TextDrawFont(loadTela[2], TEXT_DRAW_FONT_3);
    TextDrawLetterSize(loadTela[2], 0.629166, 3.199997);
    TextDrawTextSize(loadTela[2], 400.000000, 17.000000);
    TextDrawSetOutline(loadTela[2], 1);
    TextDrawSetShadow(loadTela[2], 0);
    TextDrawAlignment(loadTela[2], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(loadTela[2], -1);
    TextDrawBackgroundColor(loadTela[2], 255);
    TextDrawBoxColor(loadTela[2], 50);
    TextDrawUseBox(loadTela[2], false);
    TextDrawSetProportional(loadTela[2], true);
    TextDrawSetSelectable(loadTela[2], false);

    loadTela[3] = TextDrawCreate(258.000000, 224.000000, TEXT_SERVER_ID);
    TextDrawColor(loadTela[3], SERVER_COLOR_PRIMARY);
    TextDrawFont(loadTela[3], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(loadTela[3], 0.133332, 0.899999);
    TextDrawTextSize(loadTela[3], 400.000000, 17.000000);
    TextDrawSetOutline(loadTela[3], 1);
    TextDrawSetShadow(loadTela[3], 0);
    TextDrawAlignment(loadTela[3], TEXT_DRAW_ALIGN_LEFT);
    TextDrawBackgroundColor(loadTela[3], 255);
    TextDrawBoxColor(loadTela[3], 50);
    TextDrawUseBox(loadTela[3], false);
    TextDrawSetProportional(loadTela[3], true);
    TextDrawSetSelectable(loadTela[3], false);
}

stock CreatePlayerLoadTela(playerid) {

    loadBarraTela[playerid][0] = CreatePlayerTextDraw(playerid, 347.000000, 227.000000, "100%");
    PlayerTextDrawFont(playerid, loadBarraTela[playerid][0], TEXT_DRAW_FONT_2);
    PlayerTextDrawLetterSize(playerid, loadBarraTela[playerid][0], 0.133332, 0.899999);
    PlayerTextDrawTextSize(playerid, loadBarraTela[playerid][0], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, loadBarraTela[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, loadBarraTela[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, loadBarraTela[playerid][0], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, loadBarraTela[playerid][0], SERVER_COLOR_PRIMARY);
    PlayerTextDrawBackgroundColor(playerid, loadBarraTela[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, loadBarraTela[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, loadBarraTela[playerid][0], false);
    PlayerTextDrawSetProportional(playerid, loadBarraTela[playerid][0], true);
    PlayerTextDrawSetSelectable(playerid, loadBarraTela[playerid][0], false);
    
    loadBarraTela[playerid][1] = CreatePlayerTextDraw(playerid, 0.0, 0.0, "_");
    PlayerTextDrawFont(playerid, loadBarraTela[playerid][1], TEXT_DRAW_FONT_2);
    PlayerTextDrawLetterSize(playerid, loadBarraTela[playerid][1], 0.170833, 0.649999);
    PlayerTextDrawTextSize(playerid, loadBarraTela[playerid][1], 315.500000, 4.500000);
    PlayerTextDrawSetOutline(playerid, loadBarraTela[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, loadBarraTela[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, loadBarraTela[playerid][1], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, loadBarraTela[playerid][1], 255);
    PlayerTextDrawBackgroundColor(playerid, loadBarraTela[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, loadBarraTela[playerid][1], 255);
    PlayerTextDrawUseBox(playerid, loadBarraTela[playerid][1], true);
    PlayerTextDrawSetProportional(playerid, loadBarraTela[playerid][1], true);
    PlayerTextDrawSetSelectable(playerid, loadBarraTela[playerid][1], false);

	return 1;
}

static const Float:pos_ptd[15][2] = { 
    { 332.00, 207.00 },
    { 332.00, 209.00 },
    { 330.00, 214.00 },
    { 327.00, 216.00 },
    { 324.00, 216.00 },
    { 319.00, 216.00 },
    { 318.00, 213.00 },
    { 318.00, 209.00 },
    { 318.00, 207.00 },
    { 319.00, 205.00 },
    { 322.00, 201.00 },
    { 325.00, 200.00 },
    { 328.00, 200.00 },
    { 332.00, 201.00 },
    { 332.00, 205.00 }
};
new loadSpinPos[MAX_PLAYERS];

stock CreateLoadSpinPTD(playerid) 
{
    // loadBarraTela[playerid][1] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
    DestroyLoadTextDraw(playerid);

    if (loadSpinPos[playerid] < 14) {
		loadSpinPos[playerid]++;
	} else {
		loadSpinPos[playerid] = 0;
	}
    new loadspinpos = loadSpinPos[playerid];

    loadBarraTela[playerid][1] = CreatePlayerTextDraw(playerid, pos_ptd[loadspinpos][0], pos_ptd[loadspinpos][1], "_");
    PlayerTextDrawFont(playerid, loadBarraTela[playerid][1], TEXT_DRAW_FONT_2);
    PlayerTextDrawLetterSize(playerid, loadBarraTela[playerid][1], 0.170833, 0.649999);
    PlayerTextDrawTextSize(playerid, loadBarraTela[playerid][1], 315.500000, 4.500000);
    PlayerTextDrawSetOutline(playerid, loadBarraTela[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, loadBarraTela[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, loadBarraTela[playerid][1], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, loadBarraTela[playerid][1], 255);
    PlayerTextDrawBackgroundColor(playerid, loadBarraTela[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, loadBarraTela[playerid][1], 255);
    PlayerTextDrawUseBox(playerid, loadBarraTela[playerid][1], true);
    PlayerTextDrawSetProportional(playerid, loadBarraTela[playerid][1], true);
    PlayerTextDrawSetSelectable(playerid, loadBarraTela[playerid][1], false);
}

stock DestroyLoadTextDraw(playerid) {
    PlayerTextDrawDestroy(playerid, loadBarraTela[playerid][1]);
}

stock UpdatePlayersON() {
    // TextDraw...
	static stringtd[5];
	format(stringtd, sizeof(stringtd), "%d", ContarJogadores());
	TextDrawSetString(login_textdraws[8], stringtd);
}

CALLBACK:CreateStaticTextDraws(playerid) {
    return 1;
}

CALLBACK:CreateDynamicTextDraws(playerid) {
    return 1;
}