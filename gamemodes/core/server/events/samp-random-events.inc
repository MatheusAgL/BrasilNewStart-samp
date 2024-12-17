// Include: samp-random-events.
// Developer: wearLyS

// Includes

#include <YSI_Coding\y_hooks>

// Treino de C-Bug
#include <solo-train-cbug>
// Chuva de PayDay
#include <event-rain-pd>
// Esconder ovos com presentes
#include <event-hide-eggs>

// --------------------------------------------------------------------------------
// Funções

// --------------------------------------------------------------------------------
// - 		EVENT_Timer()
// -
// - 			Parâmetros:
// - 				Timer global (não precisa de parametros)
// -
// - 		Objetivo: Contador do inicio ao final do evento
// --------------------------------------------------------------------------------
timer EVENT_Timer[1000]()
{
    switch (EVENT[ev_count])
	{
        case 0: {
			new string[128];

			SendMsgAllF(EVENT[ev_color], "[%s]:", EVENT[ev_name]);

			SendClientMessageToAll(EVENT[ev_color], "");

			new winners = 0;
			for(new pos; pos < sizeof(EVENT[ev_rank]); pos++) {

				if (EVENT[ev_rank][pos] != INVALID_PLAYER_ID) {
					winners++;
					new winnerid = EVENT[ev_rank][pos];
					
					SendMsgAllF(-1, "%dº - {9C9C9C}%s {FFFFFF}[ Pontuação: {3558B8}%s{FFFFFF} | Prêmio: {00AA00}$%s {FFFFFF}]", pos + 1, PlayerName[winnerid], getFormatText(EVENT[ev_score][winnerid]), getFormatText(EVENT[ev_bonus][winnerid]));

					// Conquista: Ganhar evento drift
					// if (EVENT[ev_type] == DRIFT_EVENT_ID)
					// 	CheckConquista(EVENT[ev_rank][0], Conquista_Drift);

					Player_AddMoney(EVENT[ev_rank][pos], EVENT[ev_bonus][winnerid]);
				}
			}

			if (0 == winners)
				SendClientMessageToAll(-1, "Não houve ganhadores no evento dessa vez!");

			SendClientMessageToAll(EVENT[ev_color], "______________________________________________________________________________");

			// Limpando as variáveis do evento
			foreach(new i : Player) {
				EVENT_HideTextDraw(i);

				// if (EVENT[ev_score][i] > 0 && EVENT[ev_type] == DRIFT_EVENT_ID) {
				// 	SendMsgF(i, COLOR_WHITE, "Você marcou pontuação de {3558B8}%s "C_WHITE"no evento.", getFormatText(EVENT[ev_score][i]));
				// }
				if (EVENT[ev_score][i] > 0 && EVENT[ev_type] == QUIZ_EVENT_ID) {
					format(string, sizeof(string), "Você marcou pontuação de {3558B8}%s acertos {FFFFFF}no evento.", getFormatText(EVENT[ev_score][i]));
					SendClientMessage(i, -1, string);
				}
				else if (EVENT[ev_score][i] < 999999999 && EVENT[ev_type] == CBUG_EVENT_ID) {
					format(string, sizeof(string), "Você marcou pontuação de {3558B8}%sms {FFFFFF}no evento.", getFormatText(EVENT[ev_score][i]));
					SendClientMessage(i, -1, string);
				}
			}

			EVENT_ResetVars();
		}
		default:
		{
			new str[10];

			if (EVENT[ev_type] == RAIN_PD_EVENT_ID) {
				switch (EVENT[ev_count]) {
					case 290, 260, 240, 220, 200, 170, 140, 120, 100, 70, 50, 30, 10: {
						foreach(new i : Player) {
							PagarPayday(i);
						}
					}
				}
			}

			EVENT[ev_count]--;

			format(str, sizeof(str), "%s", ConvertTime(EVENT[ev_count]));
			TextDrawSetString(event_textdraw[7], str);
		}
    }
	return 1;
}

// --------------------------------------------------------------------------------
// - 		EVENT_ShowTextDraw(playerid)
// -
// - 			Parâmetros:
// - 				1. playerid: O id do jogador
// -
// - 		Objetivo: Mostrar as textdraw do evento ao jogador
// --------------------------------------------------------------------------------
stock EVENT_ShowTextDraw(playerid)
{
    for(new text; text < sizeof(event_textdraw); text++)
		TextDrawShowForPlayer(playerid, event_textdraw[text]);

	for(new text; text < sizeof(event_ptextdraw); text++)
		PlayerTextDrawShow(playerid, event_ptextdraw[text][playerid]);

	return 1;
}

// --------------------------------------------------------------------------------
// - 		EVENT_HideTextDraw(playerid)
// -
// - 			Parâmetros:
// - 				1. playerid: O id do jogador
// -
// - 		Objetivo: Mostrar as textdraw do evento ao jogador
// --------------------------------------------------------------------------------
stock EVENT_HideTextDraw(playerid)
{
    for(new text; text < sizeof(event_textdraw); text++)
		TextDrawHideForPlayer(playerid, event_textdraw[text]);

	for(new text; text < sizeof(event_ptextdraw); text++)
		PlayerTextDrawHide(playerid, event_ptextdraw[text][playerid]);

	return 1;
}

// --------------------------------------------------------------------------------
// - 		EVENT_UpdateTextDraw()
// -
// - 			Parâmetros:
// - 				Stock global não precisa de parametro
// -
// - 		Objetivo: Mostrar as textdraw do evento ao jogador
// --------------------------------------------------------------------------------
stock EVENT_UpdateTextDraw()
{
	new string[128];

	for(new pos; pos < sizeof(EVENT[ev_rank]); pos++) {

		if (EVENT[ev_rank][pos] != INVALID_PLAYER_ID) {

			format(string, sizeof(string), "%s", PlayerName[EVENT[ev_rank][pos]]);
			TextDrawSetString(event_textdraw[1 + pos], string);

			switch (EVENT[ev_type])
			{
				case CBUG_EVENT_ID: format(string, sizeof(string), "%d ms", EVENT[ev_rscore][pos]);
				// case DRIFT_EVENT_ID: format(string, sizeof(string), "%d", EVENT[ev_rscore][pos]);
				case QUIZ_EVENT_ID: format(string, sizeof(string), "%d acertos", EVENT[ev_rscore][pos]);
			}
			TextDrawSetString(event_textdraw[4 + pos], string);
		}
	}
}

// --------------------------------------------------------------------------------
// - 		EVENT_Start(eventoid)
// -
// - 			Parâmetros:
// - 				1. eventoid: O id do jogador
// -
// - 		Objetivo: Iniciar o evento
// --------------------------------------------------------------------------------
stock EVENT_Start(const name[], type = INVALID_EVENT_TYPE, mode = INVALID_EVENT_MODE, color=COLOR_SAMP)
{
	EVENT_ResetVars();

	EVENT[ev_started] = true;
	EVENT[ev_type] = type;
	EVENT[ev_color] = color;
	EVENT[ev_mode] = mode;

	format(EVENT[ev_name], sizeof(EVENT[ev_name]), "%s", name);

	EVENT_UpdateName(name, color);

	if (EVENT[ev_type] == QUIZ_EVENT_ID)
	{
		QUIZ_QUESTION = random(sizeof(QUIZ_Event));
		SendMsgAllF(EVENT[ev_color], "[EVENTO QUIZ]: {FFFFFF}%s", QUIZ_Event[QUIZ_QUESTION][question]);
	}
	else if (EVENT[ev_type] == RAIN_PD_EVENT_ID)
	{
		QUIZ_QUESTION = random(sizeof(QUIZ_Event));
		SendClientMessageToAll(EVENT[ev_color], "[EVENTO CHUVA-PD]: {FFFFFF}Iniciou um evento automático de Chuva de Payday, vá até os Presentes!");
	}
	else if (EVENT[ev_type] == HIDE_EGGS_EVENT_ID) {
		SpreadEggsInMap();
		SendClientMessageToAll(EVENT[ev_color], "[EVENTO OVOS PREMIADOS]: {FFFFFF}Foram escondidos 10 ovos por LS, procure para ganhar prêmios! (Use: /pegarpresente)");
	}

	for(new pos; pos < sizeof(EVENT[ev_rank]); pos++) {
        if (mode == EVENT_MODE_HIGHER_SCORE)
			EVENT[ev_rscore][pos] = 0;
		else if (mode == EVENT_MODE_LOWER_SCORE)
			EVENT[ev_rscore][pos] = 999999999;
    }

	stop EVENT[ev_timer];
	EVENT[ev_timer] = repeat EVENT_Timer();
	EVENT[ev_count] = (TIMER_EVENT * 60);

	for(new players; players < MAX_PLAYERS; players++) {
		for(new text; text < sizeof(event_ptextdraw); text++)
			PlayerTextDrawSetString(players, event_ptextdraw[text][players], "-");

		if (mode == EVENT_MODE_HIGHER_SCORE)
			EVENT[ev_score][players] = 0;
		else if (mode == EVENT_MODE_LOWER_SCORE)
			EVENT[ev_score][players] = 999999999;

		EVENT[ev_bonus][players] = 0;

		EVENT_ShowTextDraw(players);
	}
}

// --------------------------------------------------------------------------------
// - 		EVENT_Start_Random()
// -
// - 			Parâmetros:
// - 				-
// -
// - 		Objetivo: Iniciar um dos eventos aleatorios
// --------------------------------------------------------------------------------
stock EVENT_Start_Random()
{
	if (EVENT[ev_started]) return 1;

	new eventoid = random(EVENT[count_events]) + 1;

	switch (eventoid)
	{
		// case DRIFT_EVENT_ID: EVENT_Start("Evento Drift", DRIFT_EVENT_ID, EVENT_MODE_HIGHER_SCORE, COLOR_DRIFT_EVENT);
		case CBUG_EVENT_ID: EVENT_Start("Evento Cbug", CBUG_EVENT_ID, EVENT_MODE_LOWER_SCORE, COLOR_CBUG_EVENT);
		case QUIZ_EVENT_ID: EVENT_Start("Evento Quiz", QUIZ_EVENT_ID, EVENT_MODE_HIGHER_SCORE, COLOR_QUIZ_EVENT);
		case RAIN_PD_EVENT_ID: EVENT_Start("Evento Chuva-PD", RAIN_PD_EVENT_ID, EVENT_MODE_HIGHER_SCORE, COLOR_RAIN_PD_EVENT);
		//case HIDE_EGGS_EVENT_ID: EVENT_Start("Evento Ovos", HIDE_EGGS_EVENT_ID, EVENT_MODE_HIGHER_SCORE, COLOR_HIDE_EGGS_EVENT);
	}
	return 1;
}

// --------------------------------------------------------------------------------
// - 		EVENT_ResetVars()
// -
// - 			Parâmetros:
// - 				-
// -
// - 		Objetivo: Reseta as variaveis do evento
// --------------------------------------------------------------------------------
static stock EVENT_ResetVars()
{
    EVENT[ev_started] = false;
	EVENT[ev_count] = 0;
	stop EVENT[ev_timer];

    for(new pos; pos < sizeof(EVENT[ev_rank]); pos++) {
        EVENT[ev_rank][pos] = INVALID_PLAYER_ID;
    }

	if (EVENT[ev_type] == HIDE_EGGS_EVENT_ID)
		DestroyEggsInMap();

	for(new text = 1; text <= 6; text++)
        TextDrawSetString(event_textdraw[text], "-");

	for(new players; players < MAX_PLAYERS; players++) {
		PlayerTextDrawSetString(players, event_ptextdraw[0][players], "-");
		PlayerTextDrawSetString(players, event_ptextdraw[1][players], "-");

		EVENT[ev_score][players] = 0;
		EVENT[ev_bonus][players] = 0;
	}
}

hook OnPlayerConnect(playerid)
{
	EVENT_CreatePlayerTextDraw(playerid);

	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if (EVENT[ev_started])
	{
		for(new pos; pos < sizeof(EVENT[ev_rank]); pos++) {

			if (EVENT[ev_rank][pos] == playerid) {

				EVENT[ev_rank][pos] = INVALID_PLAYER_ID;

				if (EVENT[ev_mode] == EVENT_MODE_HIGHER_SCORE) {
					EVENT[ev_score][playerid] = 0;
					EVENT[ev_rscore][pos] = 0;
				}
				else {
					EVENT[ev_score][playerid] = 999999999;
					EVENT[ev_rscore][pos] = 999999999;
				}
				EVENT[ev_bonus] = 0;

				EVENT_UpdateRanks();
			}
		}
	}
	return 1;
}

hook OnGameModeInit()
{
	// ------------------------------------------------------------------------------------------------
	printf("<samp-random-events>: carregado na versao %d.", INC_samp_random_event_version);

	// #if DRIFT_EVENT
	// 	EVENT[count_events]++;

	// 	printf("<samp-random-events>: Evento Drift carregado (ID: %d)...", EVENT[count_events]);
	// #endif

	#if CBUG_EVENT
		EVENT[count_events]++;

		printf("<samp-random-events>: Evento C-bug carregado (ID: %d)...", EVENT[count_events]);
	#endif

	#if QUIZ_EVENT
		EVENT[count_events]++;

		printf("<samp-random-events>: Evento Quiz carregado (ID: %d)...", EVENT[count_events]);
	#endif

	#if RAIN_PD_EVENT
		EVENT[count_events]++;

		printf("<samp-random-events>: Evento Rain-PD carregado (ID: %d)...", EVENT[count_events]);
	#endif

	#if HIDE_EGGS_EVENT
		EVENT[count_events]++;

		printf("<samp-random-events>: Evento Hide-Eggs carregado (ID: %d)...", EVENT[count_events]);
	#endif

	if (EVENT[count_events] > 0)
		printf("<samp-random-events>: %d eventos aleatorios foram carregados...", EVENT[count_events]);
	else
		print("<samp-random-events>: Nenhum evento foi carregado...");

	// ------------------------------------------------------------------------------------------------
	// Criando as textdraws e resetando as variáveis do sistema
	EVENT_CreateTextDraw();

	EVENT_ResetVars();

	// ------------------------------------------------------------------------------------------------

	return 1;
}

hook OnPlayerSpawn(playerid)
{
	// ------------------------------------------------------------------------------------------------
	// Mostrando as textdraw ao spawnar caso tiver tendo evento
	if (Player_Logado(playerid) && EVENT[ev_started])
		EVENT_ShowTextDraw(playerid);

	// ------------------------------------------------------------------------------------------------
	return 1;
}

stock EVENT_UpdateRanks()
{
	if (!EVENT[ev_started]) return 1;

	switch (EVENT[ev_mode])
	{
		case EVENT_MODE_HIGHER_SCORE:
		{
			foreach(new players : Player) {
				if (EVENT[ev_rank][0] != players)
				{
					if (EVENT[ev_rank][1] != players)
					{
						if (EVENT[ev_rscore][2] < EVENT[ev_score][players]) {
							EVENT[ev_rscore][2] = EVENT[ev_score][players];
							EVENT[ev_rank][2] = players;
						}
						else continue;
					}
					if (EVENT[ev_rscore][1] < EVENT[ev_score][players]) {
						EVENT[ev_rank][2] = INVALID_PLAYER_ID;
						EVENT[ev_rscore][2] = 0;

						EVENT[ev_rscore][1] = EVENT[ev_score][players];
						EVENT[ev_rank][1] = players;
					}
					else continue;

					if (EVENT[ev_rscore][0] < EVENT[ev_score][players]) {
						EVENT[ev_rank][1] = INVALID_PLAYER_ID;
						EVENT[ev_rscore][1] = 0;

						EVENT[ev_rscore][0] = EVENT[ev_score][players];
						EVENT[ev_rank][0] = players;
					}
					else continue;
				}
				
				if (EVENT[ev_rscore][0] < EVENT[ev_score][players]) {
					EVENT[ev_rscore][0] = EVENT[ev_score][players];
					EVENT[ev_rank][0] = players;
				}
			}
		}
		case EVENT_MODE_LOWER_SCORE:
		{
			foreach(new players : Player) {
				if (EVENT[ev_rank][0] != players)
				{
					if (EVENT[ev_rank][1] != players)
					{
						if (EVENT[ev_rscore][2] > EVENT[ev_score][players]) {
							EVENT[ev_rscore][2] = EVENT[ev_score][players];
							EVENT[ev_rank][2] = players;
						}
						else continue;
					}
					if (EVENT[ev_rscore][1] > EVENT[ev_score][players]) {
						EVENT[ev_rank][2] = INVALID_PLAYER_ID;
						EVENT[ev_rscore][2] = 999999999;

						EVENT[ev_rscore][1] = EVENT[ev_score][players];
						EVENT[ev_rank][1] = players;
					}
					else continue;

					if (EVENT[ev_rscore][0] > EVENT[ev_score][players]) {
						EVENT[ev_rank][1] = INVALID_PLAYER_ID;
						EVENT[ev_rscore][1] = 999999999;

						EVENT[ev_rscore][0] = EVENT[ev_score][players];
						EVENT[ev_rank][0] = players;
					}
					else continue;
				}

				if (EVENT[ev_rscore][0] > EVENT[ev_score][players]) {
					EVENT[ev_rscore][0] = EVENT[ev_score][players];
					EVENT[ev_rank][0] = players;
				}
			}
		}
	}

	EVENT_UpdateTextDraw();

	return 1;
}

// CMD:startdrift(playerid)
// {
// 	if (Dev_GetNivel(playerid) < DEV_DELTA) return 1;

// 	if (!EVENT[ev_started])
// 		EVENT_Start("Evento Drift", DRIFT_EVENT_ID, EVENT_MODE_HIGHER_SCORE, COLOR_DRIFT_EVENT);
// 	else
// 		EVENT[ev_count] = 0;

// 	return 1;
// }

CMD:startcbug(playerid)
{
	if (Dev_GetNivel(playerid) < DEV_DELTA) return 1;

	if (!EVENT[ev_started])
		EVENT_Start("Evento Cbug", CBUG_EVENT_ID, EVENT_MODE_LOWER_SCORE, COLOR_CBUG_EVENT);
	else
		EVENT[ev_count] = 0;

	return 1;
}

CMD:startquiz(playerid)
{
	if (Dev_GetNivel(playerid) < DEV_DELTA) return 1;

	if (!EVENT[ev_started])
		EVENT_Start("Evento Quiz", QUIZ_EVENT_ID, EVENT_MODE_HIGHER_SCORE, COLOR_QUIZ_EVENT);
	else
		EVENT[ev_count] = 0;

	return 1;
}

CMD:startrainpd(playerid)
{
	if (Dev_GetNivel(playerid) < DEV_DELTA) 
		return 1;

	if (!EVENT[ev_started])
		EVENT_Start("Evento Chuva-PD", RAIN_PD_EVENT_ID, EVENT_MODE_HIGHER_SCORE, COLOR_RAIN_PD_EVENT);
	else
		EVENT[ev_count] = 0;

	return 1;
}

CMD:starthideeggs(playerid)
{
	if (Dev_GetNivel(playerid) < DEV_DELTA) 
		return 1;

	if (!EVENT[ev_started])
		EVENT_Start("Evento Ovos", HIDE_EGGS_EVENT_ID, EVENT_MODE_HIGHER_SCORE, COLOR_HIDE_EGGS_EVENT);
	else
		EVENT[ev_count] = 0;

	return 1;
}