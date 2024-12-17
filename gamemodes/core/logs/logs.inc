
#include < YSI_Coding\y_hooks >
// #include < logger >

stock logStringServer[256];

#define ServerLog::(%0,%1) \
		server_log(%0, (format(logStringServer, 256, %1), logStringServer))

#define Log::(%0,%1) \
		serverLogEx(%0, (format(logStringServer, 256, %1), logStringServer))

stock serverLogEx(const namelog[], const logtext[])
{
	new File:fileLog;
	new fileString[256];

	format(fileString, sizeof(fileString), "ArquivosBPS/Logs/log_%s.txt", namelog);

	fileLog = fopen(fileString, io_append);

	if (fileLog)
	{
	    static date[3];
	    static shour[3];

	    getdate(date[2], date[1], date[0]);
	    gettime(shour[0], shour[1], shour[2]);

	    format(fileString, sizeof (fileString), "%02d-%02d-%04d %02d:%02d:%02d|%s\t\t|%s\r\n", date[0], date[1], date[2], shour[0], shour[1], shour[2], namelog, logtext);
	    fwrite(fileLog, fileString);
	    fclose(fileLog);
	}
}

CALLBACK:server_log(const nome_log[], const log_texto[])
{
	new query[345];
	
	mysql_format(MySQL_Handle, query, sizeof(query), "INSERT INTO `logs` VALUES (DEFAULT, '%e', CURRENT_TIMESTAMP(), '%e')", nome_log, log_texto);
	mysql_pquery(MySQL_Handle, query);
}

CALLBACK:log_chat(playerid, const log_texto[])
{
	if (Admin_GetLogChat()) {
		new query[345], Float:pos[3];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		mysql_format(MySQL_Handle, query, sizeof(query), "INSERT INTO log_chat (player_id, datahora, texto, pos_x, pos_y, pos_z) VALUES (%d, CURRENT_TIMESTAMP(), '%e', %f, %f, %f)", 
			Player_GetAccountID(playerid), log_texto, pos[0], pos[1], pos[2]);
		mysql_pquery(MySQL_Handle, query);
	}
}

stock show_server_log(playerid, const nomelog[], const keylog[], mode = 0)
{
	new log_query[128];

	mysql_format(MySQL_Handle, log_query, sizeof(log_query), "SELECT * FROM `logs` WHERE `nomelog` = '%e' ORDER BY `data` DESC LIMIT 20", keylog);
	mysql_tquery(MySQL_Handle, log_query, "show_server_log_ex", "isi", playerid, nomelog, mode);
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", "\n\t{AAAAAA}AGUARDE UM MOMENTO...\n", "Ok", "");
}

stock show_server_log_pl(playerid, playeridname[], nomelog[], mode = 0)
{
	new log_query[256];

	mysql_format(MySQL_Handle, log_query, sizeof(log_query), "SELECT * FROM `logs` WHERE `nomelog` = '%e' and `log_texto` like '%%%e%%' ORDER BY `data` DESC LIMIT 20", nomelog, playeridname);
	mysql_tquery(MySQL_Handle, log_query, "show_server_log_ex", "isi", playerid, playeridname, mode);
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", "\n\t{AAAAAA}AGUARDE UM MOMENTO...\n", "Ok", "");
}

forward show_server_log_ex(playerid, nomelog[], mode);
public show_server_log_ex(playerid, nomelog[], mode)
{
	new log_string[2][256];

	MEGAString[0] = EOS;

	if(mode == 0)
		strcat(MEGAString, "Data\tLog\n");
	else
		strcat(MEGAString, "{FFFFFF}Data\t\t\tLog\n");

	new row_count;
	cache_get_row_count(row_count);
	for(new rlog; rlog != row_count; rlog++)
	{
	    cache_get_value_name(rlog, "data", log_string[1]);
	    format(log_string[0], 255, "{FFFFFF}%s\t", log_string[1]);
	    strcat(MEGAString, log_string[0]);

	    cache_get_value_name(rlog, "log_texto", log_string[1]);
	    format(log_string[0], 255, "%s\n", log_string[1]);
	    strcat(MEGAString, log_string[0]);
	}

	format(log_string[0], 128, "{00FFFF}Painel de Registros: {FFFFFF}%s", nomelog);
	ShowPlayerDialog(playerid, 8715, (mode == 0) ? DIALOG_STYLE_TABLIST_HEADERS : DIALOG_STYLE_MSGBOX, log_string[0], MEGAString, "Voltar", "");
}