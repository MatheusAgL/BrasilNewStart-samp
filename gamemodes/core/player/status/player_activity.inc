#if defined _inc_playeractivity_system
	#endinput
#endif
#define _inc_playeractivity_system true

#include <YSI_Coding\y_hooks>

static ActivityInfo[MAX_PLAYERS][DAYS_OF_YEAR];

stock Player_GetActivity(playerid, day)
	return ActivityInfo[playerid][day];

static Player_SetActivity(playerid, day, activity) {
	ActivityInfo[playerid][day] = activity;
}

// ------------------------ Sistema de atividade ------------------------
static 
		Statement: stmt_insertAtividades,
		Statement: stmt_selectAtividades,
		Statement: stmt_selectAtividadesOff,
		Statement: stmt_updateAtividade;

hook OnMySQLConnected() 
{
	static const query_insertAtividades[] = 
		"INSERT INTO atividades (player, diaDoAno, atividade, ano) VALUES (?, ?, 0, ?)"
	;
	stmt_insertAtividades = MySQL_PrepareStatement(MySQL_Handle, query_insertAtividades);

	static const query_selectAtividades[] = 
		"SELECT `diaDoAno`, `atividade` FROM atividades WHERE `player` = ? AND `ano` = ? ORDER BY `diaDoAno` ASC"
	;
	stmt_selectAtividades = MySQL_PrepareStatement(MySQL_Handle, query_selectAtividades);

	static const query_updateAtividade[] = 
		"UPDATE `atividades` SET `atividade` = ?, `ano` = ? WHERE `player` = ? AND `diaDoAno` = ? AND `ano` = ?"
	;
	stmt_updateAtividade = MySQL_PrepareStatement(MySQL_Handle, query_updateAtividade);

	static const query_selectAtividadesOff[] = 
		"SELECT `diaDoAno`, `atividade` FROM `atividades` WHERE `player` = ? AND `diaDoAno` BETWEEN ? AND ? AND `ano` = ? ORDER BY `diaDoAno` ASC"
	;
	stmt_selectAtividadesOff = MySQL_PrepareStatement(MySQL_Handle, query_selectAtividadesOff);
	return 1;
}

hook OnPlayerLogin(playerid) 
{
	inline const OnLoadActivity() 
	{
		new days_of_year,
			activity;

		MySQL_BindResultInt(stmt_selectAtividades, 0, days_of_year);
		MySQL_BindResultInt(stmt_selectAtividades, 1, activity);

		while (MySQL_Statement_FetchRow(stmt_selectAtividades))
			Player_SetActivity(playerid, days_of_year, activity);

		if (Player_GetActivity(playerid, getdate()) < 1) {
			MySQL_BindInt(stmt_insertAtividades, 0, Player_GetAccountID(playerid));
			MySQL_BindInt(stmt_insertAtividades, 1, getdate());
			MySQL_BindInt(stmt_insertAtividades, 2, GetCurrentYear());
			MySQL_ExecuteThreaded(stmt_insertAtividades);

			Player_SetActivity(playerid, getdate(), 0);
		}
		for(new day; day < DAYS_OF_YEAR; day++) {
			if (Player_GetActivity(playerid, day) < 1)
				Player_SetActivity(playerid, day, 0);
		}
		SetPVarInt(playerid, "ActivityLoaded", 1);
	}
	MySQL_BindInt(stmt_selectAtividades, 0, Player_GetAccountID(playerid));
	MySQL_BindInt(stmt_selectAtividades, 1, GetCurrentYear());
	MySQL_ExecuteThreaded_Inline(stmt_selectAtividades, using inline OnLoadActivity);
	return 1;
}

hook OnPlayerResetVars(playerid) 
{
	for(new day; day < DAYS_OF_YEAR; day++) Player_SetActivity(playerid, day, -1);

	return 1;
}

hook OnResetDay(playerid) {
	if (Player_Logado(playerid) && GetPVarInt(playerid, "ActivityLoaded")) {
		MySQL_BindInt(stmt_insertAtividades, 0, Player_GetAccountID(playerid));
		MySQL_BindInt(stmt_insertAtividades, 1, getdate());
		MySQL_BindInt(stmt_insertAtividades, 2, GetCurrentYear());
		MySQL_ExecuteThreaded(stmt_insertAtividades);
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
	Player_SaveActivity(playerid);
	return 1;
}

ptask OnSaveActivity[60 * 1000](playerid) {
	Player_SaveActivity(playerid);
}

ptask OnPlayerActivityUpdate[1000](playerid)
{
	if (GetPlayerEscTime(playerid) < 5 * 60 && !Player_GetTimerAFK(playerid)) {
		new bool:isNotAfk = (
			(Admin_GetNivel(playerid) && GetPVarInt(playerid, "varTeamViewer")) ||
			(Admin_GetNivel(playerid) && !Staff_GetAFK(playerid)) ||
			(!Admin_GetNivel(playerid))
		);

		if (Player_Logado(playerid) && GetPVarInt(playerid, "ActivityLoaded") && isNotAfk) {
			Player_SetActivity(playerid, getdate(), Player_GetActivity(playerid, getdate()) + 1);
			AddTimeOnWeeklyPass(playerid);
		}
	}
	return 1;
}

stock Player_SaveActivity(playerid)
{
	if (Player_Logado(playerid) && GetPVarInt(playerid, "ActivityLoaded")) {
		MySQL_BindInt(stmt_updateAtividade, 0, Player_GetActivity(playerid, getdate()));
		MySQL_BindInt(stmt_updateAtividade, 1, GetCurrentYear());
		MySQL_BindInt(stmt_updateAtividade, 2, Player_GetAccountID(playerid));
		MySQL_BindInt(stmt_updateAtividade, 3, getdate());
		MySQL_BindInt(stmt_updateAtividade, 4, GetCurrentYear());
		MySQL_ExecuteThreaded(stmt_updateAtividade);
	}
	return 1;
}

stock Player_GetActivityDay(gid, last_days)
{
	new days_date = getdate();
	new days_ago;
	new days_atividade = 0;

    days_ago = days_date - last_days;

	if (days_ago < 0) {
	    days_ago = 0;
	}

	new playerid = GetPlayerIdByIdGlobal(gid);
	if (Player_Logado(playerid)) {
	    for (new days = days_ago; days != days_date + 1; days++) 
	        days_atividade += Player_GetActivity(playerid, days);
	} else {
		new query[300];
		mysql_format(MySQL_Handle, query, sizeof(query), "SELECT SUM(atividade) AS total FROM atividades WHERE player = %d AND diaDoAno >= %d ORDER BY diaDoAno ASC", 
			gid, days_ago);
		mysql_query(MySQL_Handle, query);

		days_atividade = MYSQL_GetInt(0, "total");
	}
	return days_atividade;
}

stock Print_ActivityOff(playerid, gid, days) 
{
	MEGAString[0] = EOS;
	new string[128];

	inline const OnLoadActivityOff() {
		new atividade[DAYS_OF_YEAR],
			days_atividade,
			days_soma,
			day, 
			activity,
			date = getdate() - days, 
			current = getdate();

		if (date < 0)
			date = 0;

		MySQL_BindResultInt(stmt_selectAtividadesOff, 0, day);
		MySQL_BindResultInt(stmt_selectAtividadesOff, 1, activity);

		format(string, sizeof string, ""C_BURNED_YELLOW"Status: "C_RED"OFFLINE\n\n");
		strcat(MEGAString, string);

		while(MySQL_Statement_FetchRow(stmt_selectAtividadesOff)) {
			atividade[day] = activity;
		}

		for(new i = date; i <= current; i++) {
			days_atividade = atividade[i];
			days_soma += days_atividade;

			if (i == current) {
				format(string, sizeof string, ""C_BURNED_YELLOW"Tempo jogado Hoje: "C_WHITE"%s\n", ConvertTime(days_atividade));
			} else {
				format(string, sizeof string, ""C_BURNED_YELLOW"Tempo jogado %02d dia(s) atrás: "C_WHITE"%s\n", current - i, ConvertTime(days_atividade));
			}
			strcat(MEGAString, string);
		}

		format(string, sizeof string, "\n"C_BURNED_YELLOW"Total de tempo jogado em %d dias: "C_WHITE"%s\n", days, ConvertTime(days_soma));
		strcat(MEGAString, string);

		format(string, sizeof string, ""C_BURNED_YELLOW"Total de tempo jogado no ano: "C_WHITE"%s\n", ConvertTime(Player_GetActivityDay(gid, DAYS_OF_YEAR)));
		strcat(MEGAString, string);

		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Fechar", "");

	}
	MySQL_BindInt(stmt_selectAtividadesOff, 0, gid);
	MySQL_BindInt(stmt_selectAtividadesOff, 1, (getdate() - days));
	MySQL_BindInt(stmt_selectAtividadesOff, 2, getdate());
	MySQL_BindInt(stmt_selectAtividadesOff, 3, GetCurrentYear());
	MySQL_ExecuteThreaded_Inline(stmt_selectAtividadesOff, using inline OnLoadActivityOff);
}

stock Print_ActivityOn(playerid, idplayer, const nick[], gid, days) 
{
	MEGAString[0] = EOS;
	new string[255];

	format(string, sizeof string, ""C_BURNED_YELLOW"Nick: "C_WHITE"%s\n", nick);
	strcat(MEGAString, string);

	new days_atividade, 
		days_soma,
		current = getdate(),
		date = getdate() - days;

	if (date < 0)
		date = 0;

	format(string, sizeof string, ""C_BURNED_YELLOW"Status: "C_GREEN"ONLINE\n\n");
	strcat(MEGAString, string);

	for(new day = date; day <= current; day++) {
		days_atividade = Player_GetActivity(idplayer, day);
		days_soma += days_atividade;
		if (day == current) {
			format(string, sizeof string, ""C_BURNED_YELLOW"Tempo jogado Hoje: "C_WHITE"%s\n", ConvertTime(days_atividade));
		} else {
			format(string, sizeof string, ""C_BURNED_YELLOW"Tempo jogado %02d dia(s) atrás: "C_WHITE"%s\n", current - day, ConvertTime(days_atividade));
		}
		strcat(MEGAString, string);
	}
	format(string, sizeof(string), "\n"C_BURNED_YELLOW"Total de tempo jogado em %d dias: "C_WHITE"%s\n", days, ConvertTime(days_soma));
	strcat(MEGAString, string);

	format(string, sizeof(string), ""C_BURNED_YELLOW"Total de tempo jogado no ano: "C_WHITE"%s\n", ConvertTime(Player_GetActivityDay(gid, DAYS_OF_YEAR)));
	strcat(MEGAString, string);

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Fechar", "");
}

CMD:minhaatividade(playerid, params[])
{
	new days;
	if (sscanf(params, "d", days))
		return SendClientMessage(playerid, -1, "Modo de uso: /minhaatividade (Dias [0(Hoje) - 30])");

	if (days < 0 || days > 30)
		return SendClientMessage(playerid, -1, "Você deve escolher quantos dias atrás deseja ver sua atividade (0 á 30 dias)");

	new string[200];

	MEGAString[0] = EOS;

	format(string, sizeof string, ""C_BURNED_YELLOW"Nick: "C_WHITE"%s\n", PlayerName[playerid]);
	strcat(MEGAString, string);

	format(string, sizeof string, ""C_BURNED_YELLOW"Status: "C_GREEN"ONLINE\n\n");
	strcat(MEGAString, string);

	new current = getdate(),
		date = current - days;

	if (date < 0)
		date = 0;

	new days_soma;
	new days_atividade;

	for(new i = date; i <= current; i++) {
		days_atividade = Player_GetActivity(playerid, i);
		days_soma += days_atividade;
		
		if (i == current) {
			format(string, sizeof string, ""C_BURNED_YELLOW"Tempo jogado Hoje: "C_WHITE"%s\n", ConvertTime(days_atividade));
		} else {
			format(string, sizeof string, ""C_BURNED_YELLOW"Tempo jogado %02d dia(s) atrás: "C_WHITE"%s\n", current - i, ConvertTime(days_atividade));
		}
		strcat(MEGAString, string);
	}

	format(string, sizeof string, "\n"C_BURNED_YELLOW"Total de tempo jogado em %d dias: "C_WHITE"%s\n", days, ConvertTime(days_soma));
	strcat(MEGAString, string);

	format(string, sizeof string, ""C_BURNED_YELLOW"Total de tempo jogado no ano: "C_WHITE"%s\n", ConvertTime(Player_GetActivityDay(Player_GetGID(playerid), DAYS_OF_YEAR)));
	strcat(MEGAString, string);

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Fechar", "");

	return 1;
}

CMD:pegaratividade(playerid, params[])
{
	new nick[MAX_PLAYER_NAME],
		days;

	if (sscanf(params, "s[24]d", nick, days))
		return SendClientMessage(playerid, -1, "Modo de uso: /pegaratividade (nick do jogador) (Dias [0(Hoje) - 30])");

	#if _inc_admin_system
	if (Admin_GetNivel(playerid) < SUPERVISOR)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (days < 0 || days > 30)
		return SendClientMessage(playerid, -1, "Você deve escolher quantos dias atrás deseja ver sua atividade (0 á 30 dias)");

	new gid = Player_GetAccountIDByNick(nick);

	if (gid == -1) 
		return SendClientMessage(playerid, -1, "Esse nick não está cadastrado.");

	new idplayer = GetPlayerID(nick);
	if (Player_Logado(idplayer)) {
		Print_ActivityOn(playerid, idplayer, nick, gid, days);
	} else {
		Print_ActivityOff(playerid, gid, days);
	}
	return 1;
}