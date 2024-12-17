#if defined _inc_banishment_system
	#endinput
#endif
#define _inc_banishment_system true

#include <YSI_Coding\y_hooks>

#define         MAX_DAYS_BAN        5000

// ------------------------ Sistema de banimento ------------------------
static 
		Statement: stmt_insertBan,
		Statement: stmt_insertBanIP,
		// Statement: stmt_selectBannedNick,
		Statement: stmt_deletarBan,
		Statement: stmt_deletarBanIP;
		// Statement: stmt_lastBans;

hook OnMySQLConnected() 
{
	static const query_insertBan[] = 
		"INSERT INTO `banidos` (`player`,`ip`,`admin`,`motivo`,`data`,`desban_data`) VALUES       \
		    ('?','?','?','?', CURRENT_TIMESTAMP(), ADDDATE(CURRENT_DATE(), ?))"
	;
	stmt_insertBan = MySQL_PrepareStatement(MySQL_Handle, query_insertBan);

	static const query_insertBanIP[] = 
		"INSERT INTO `banidos_ip` (`player`,`ip`,`admin`,`motivo`,`data`,`desban_data`) VALUES     \
		    ('?','?','?','?', CURRENT_TIMESTAMP(), ADDDATE(CURRENT_DATE(), ?))"
	;
	stmt_insertBanIP = MySQL_PrepareStatement(MySQL_Handle, query_insertBanIP);

	// static const query_selectBannedNick[] = 
	// 	"SELECT p.`nome`, b.`player`, b.`ip`, b.`admin`, b.`motivo`, b.`data`, b.`desban_data` FROM `banidos` b INNER JOIN `player` p ON b.`player` = p.`id` WHERE p.`nome` = ? LIMIT 1"
	// ;
	// stmt_selectBannedNick = MySQL_PrepareStatement(MySQL_Handle, query_selectBannedNick);

	static const query_deletarBan[] = 
		"DELETE FROM `banidos` WHERE `player` = ?"
	;
	stmt_deletarBan = MySQL_PrepareStatement(MySQL_Handle, query_deletarBan);

	static const query_deletarBanIP[] = 
		"DELETE FROM `banidos_ip` WHERE `player` = ?"
	;
	stmt_deletarBanIP = MySQL_PrepareStatement(MySQL_Handle, query_deletarBanIP);

	// static const query_lastBans[] = 
	// 	"SELECT * FROM `banidos` ORDER BY `data` DESC LIMIT 30"
	// ;
	// stmt_lastBans = MySQL_PrepareStatement(MySQL_Handle, query_lastBans);

	return 1;
}

stock Banned_Player(idgplayer, idgadmin, const playerip[], const reason[], days = -1) 
{
    MySQL_BindInt(stmt_insertBan, 0, idgplayer);
    MySQL_Bind(stmt_insertBan, 1, playerip, true);
    MySQL_BindInt(stmt_insertBan, 2, idgadmin);
    MySQL_Bind(stmt_insertBan, 3, reason, true);

	MySQL_BindInt(stmt_insertBanIP, 0, idgplayer);
    MySQL_Bind(stmt_insertBanIP, 1, playerip, true);
    MySQL_BindInt(stmt_insertBanIP, 2, idgadmin);
    MySQL_Bind(stmt_insertBanIP, 3, reason, true);

	if (days != -1) {
		MySQL_BindInt(stmt_insertBan, 4, days);
		MySQL_BindInt(stmt_insertBanIP, 4, days);
	} else {
        MySQL_BindInt(stmt_insertBan, 4, MAX_DAYS_BAN);
		MySQL_BindInt(stmt_insertBanIP, 4, MAX_DAYS_BAN);
	}
	MySQL_ExecuteThreaded(stmt_insertBan);
	MySQL_ExecuteThreaded(stmt_insertBanIP);
}

stock HardBanIP(const ip[]) {
	new string[40];
	format(string, sizeof(string), "banip %s", ip);
	return SendRconCommand(string);
}

stock HardUnbanIP(const ip[]) {
	new string[45];
	format(string, sizeof(string), "unbanip %s", ip);
	return SendRconCommand(string);
}

stock check_ban_nick(const nick[])
{
	new query[128];

	mysql_format(MySQL_Handle, query, sizeof query, "SELECT b.*, p.nome FROM `banidos` b INNER JOIN `player` p ON b.player = p.id WHERE p.`nome` = '%s' LIMIT 1", nick);
	new Cache:serverCache = mysql_query(MySQL_Handle, query);

	new row_count;
	cache_get_row_count(row_count);

	cache_delete(serverCache);

	return row_count;
}

stock DoesPlayerExists(const nick[])
{
	new query[128];

	mysql_format(MySQL_Handle, query, sizeof query, "SELECT * FROM `player` WHERE `nome` = '%s' LIMIT 1", nick);
	new Cache:serverCache = mysql_query(MySQL_Handle, query);

	new row_count;
	cache_get_row_count(row_count);

	cache_delete(serverCache);
	return row_count > 0;
}

stock check_ban_ip(const ban_ip[]) 
{
	new query[128];

	mysql_format(MySQL_Handle, query, sizeof query, "SELECT * FROM `banidos_ip` WHERE `ip` = '%s' LIMIT 1", ban_ip);
	new Cache:serverCache = mysql_query(MySQL_Handle, query);

	new row_count;
	cache_get_row_count(row_count);

	cache_delete(serverCache);

	return row_count;
}

stock Unbanned_Player(idgplayer)
{
	MySQL_BindInt(stmt_deletarBan, 0, idgplayer);
	MySQL_ExecuteThreaded(stmt_deletarBan);

	MySQL_BindInt(stmt_deletarBanIP, 0, idgplayer);
	MySQL_ExecuteThreaded(stmt_deletarBanIP);

	return 1;
}

stock desban_ip(ban_ip[]) {

	new query[128];

	mysql_format(MySQL_Handle, query, sizeof query, "DELETE FROM `banidos_ip` WHERE `ip` = '%s'", ban_ip);
	mysql_tquery(MySQL_Handle, query);
}

stock Player_CheckBan(playerid)
{
	new ban_query[276];
	new ban_string[128];
	new ban_field[128];

	if (check_ban_nick(PlayerName[playerid])) 
	{
		mysql_format(MySQL_Handle, ban_query, sizeof ban_query, "SELECT b.*, p.nome FROM `banidos` b INNER JOIN `player` p ON b.player = p.id WHERE p.`nome` = '%s' AND CURRENT_DATE() < `desban_data` LIMIT 1", PlayerName[playerid]);
		mysql_query(MySQL_Handle, ban_query);

		if (MYSQL_GetRowsCount() > 0) {
			MEGAString[0] = EOS;
			strcat(MEGAString, "{FF0000}|		- Esta conta est� banida no servidor		|\n\n");

			cache_get_value_name(0, "nome", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}Nick: {DA4F4F}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			cache_get_value_name(0, "ip", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}IP: {8B8A8A}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			cache_get_value_name(0, "admin", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}Admin respons�vel: {00CCFF}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			cache_get_value_name(0, "motivo", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}Motivo: {F74242}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			cache_get_value_name(0, "data", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}Data: {DA4F4F}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			cache_get_value_name(0, "desban_data", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}Desban: {F74242}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			strcat(MEGAString, "\n{FFFFFF}Ol� jogador, voc� tem algumas op��es para sua conta ser desbanida\n{FFFFFF}Entre em nosso painel: "SERVER_SITE"\n\
			1 - Voc� pode abrir uma revis�o de banimento no f�rum\n2 - Voc� pode pagar a taxa de desbanimento (R$50,00) encontra-se no f�rum tamb�m!\n\n");

			ShowPlayerDialog(playerid, 8723, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Sair", "");
			KickEx(playerid);
			return 1;
		}
		else {
		    mysql_format(MySQL_Handle, ban_query, sizeof ban_query, "SELECT * FROM `banidos` WHERE `player` = (SELECT id FROM player WHERE nome = 'noquiero315@gmail.com') AND CURRENT_DATE() >= `desban_data`", PlayerName[playerid]);
		    mysql_tquery(MySQL_Handle, ban_query);
			return 0;
		}
	}

	if (check_ban_ip(PlayerIP[playerid])) {

		mysql_format(MySQL_Handle, ban_query, sizeof ban_query, "SELECT * FROM `banidos_ip` WHERE `ip` = '%s' AND CURRENT_DATE() < `desban_data` LIMIT 1", PlayerIP[playerid]);
		mysql_query(MySQL_Handle, ban_query);

		if (MYSQL_GetRowsCount() > 0) {
			MEGAString[0] = EOS;
			strcat(MEGAString, "{FF0000}|		- Este IP est� banido no servidor		|\n\n");

			cache_get_value_name(0, "nome", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}Nick: {DA4F4F}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			cache_get_value_name(0, "ip", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}IP: {8B8A8A}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			cache_get_value_name(0, "admin", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}Admin respons�vel: {00CCFF}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			cache_get_value_name(0, "motivo", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}Motivo: {F74242}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			cache_get_value_name(0, "data", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}Data: {DA4F4F}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			cache_get_value_name(0, "desban_data", ban_field);
			format(ban_string, sizeof ban_string, "{FFFFFF}Desban: {F74242}%s\n", ban_field);
			strcat(MEGAString, ban_string);

			strcat(MEGAString, "\n{FFFFFF}Ol� jogador, voc� tem algumas op��es para sua conta ser desbanida\n{FFFFFF}Entre em nosso painel: "SERVER_SITE"\n\
			1 - Voc� pode abrir uma revis�o de banimento no f�rum\n2 - Voc� pode pagar a taxa de desbanimento (R$50,00) encontra-se no f�rum tamb�m!\n\n");

			ShowPlayerDialog(playerid, 8723, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Sair", "");
			KickEx(playerid);
			return 1;
		}
		else {
			mysql_format(MySQL_Handle, ban_query, sizeof ban_query, "DELETE FROM `banidos_ip` WHERE `ip` = '%s'", PlayerIP[playerid]);
		    mysql_tquery(MySQL_Handle, ban_query);
		    return 0;
		}
	}
	return 0;
}

stock show_nick_ban(playerid, nick[])
{
	new ban_query[128];
	new ban_string[128];
	new ban_field[128];

	mysql_format(MySQL_Handle, ban_query, sizeof ban_query, "SELECT b.*, p.nome FROM `banidos` b INNER JOIN `player` p ON b.player = p.id WHERE p.`nome` = '%s' LIMIT 1", nick);
	mysql_query(MySQL_Handle, ban_query);

	if(MYSQL_GetRowsCount() > 0) {

		MEGAString[0] = EOS;
		strcat(MEGAString, "{FF0000}|		- Esta conta est� banida no servidor		|\n\n");

		cache_get_value_name(0, "nome", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}Nick: {DA4F4F}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		cache_get_value_name(0, "ip", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}IP: {8B8A8A}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		cache_get_value_name(0, "admin", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}Admin respons�vel: {00CCFF}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		cache_get_value_name(0, "motivo", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}Motivo: {F74242}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		cache_get_value_name(0, "data", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}Data: {DA4F4F}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		cache_get_value_name(0, "desban_data", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}Desban: {F74242}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		strcat(MEGAString, "\n{FFFFFF}Ol� jogador, voc� tem algumas op��es para sua conta ser desbanida\n{FFFFFF}Entre em nosso painel: "SERVER_SITE"\n\
		1 - Voc� pode abrir uma revis�o de banimento no f�rum\n2 - Voc� pode pagar a taxa de desbanimento (R$50,00) encontra-se no f�rum tamb�m!\n\n");

		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Fechar", "");
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTRED, " Nick n�o encontrado em nosso banco de dados !");
	}
	return 1;
}


show_ip_ban(playerid, ipban[]) {

	new ban_query[129];
	new ban_string[128];
	new ban_field[128];

	mysql_format(MySQL_Handle, ban_query, sizeof ban_query, "SELECT * FROM `banidos_ip` WHERE `ip` = '%s' LIMIT 1", ipban);
	mysql_query(MySQL_Handle, ban_query);

	if(MYSQL_GetRowsCount() > 0) {
		MEGAString[0] = EOS;
		strcat(MEGAString, "{FF0000}|		- Este IP est� banido no servidor		|\n\n");

		cache_get_value_name(0, "nome", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}Nick: {DA4F4F}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		cache_get_value_name(0, "ip", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}IP: {8B8A8A}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		cache_get_value_name(0, "admin", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}Admin respons�vel: {00CCFF}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		cache_get_value_name(0, "motivo", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}Motivo: {F74242}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		cache_get_value_name(0, "data", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}Data: {DA4F4F}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		cache_get_value_name(0, "desban_data", ban_field);
		format(ban_string, sizeof ban_string, "{FFFFFF}Desban: {F74242}%s\n", ban_field);
		strcat(MEGAString, ban_string);

		strcat(MEGAString, "\n{FFFFFF}Ol� jogador, voc� tem algumas op��es para sua conta ser desbanida\n{FFFFFF}Entre em nosso painel: "SERVER_SITE"\n\
		1 - Voc� pode abrir uma revis�o de banimento no f�rum\n2 - Voc� pode pagar a taxa de desbanimento (R$50,00) encontra-se no f�rum tamb�m!\n\n");

		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Fechar", "");
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTRED, " IP n�o encontrado em nosso banco de dados !");
	}
	return 1;
}

show_list_bans_admin(playerid, adminname[]) {

	new ban_query[128];
	mysql_format(MySQL_Handle, ban_query, sizeof ban_query, "SELECT b.*, p.nome FROM `banidos` b INNER JOIN `player` p ON b.player = p.id WHERE `admin` = '%s' ORDER BY `data` DESC LIMIT 30", adminname);
	mysql_tquery(MySQL_Handle, ban_query, "OnLoadedListBanAdmin", "is", playerid, adminname);
}

CALLBACK:OnLoadedListBanAdmin(playerid, const adminname[]) {
	new ban_string[128], ban_field[128];
	MEGAString[0] = EOS;
	strcat(MEGAString, "Nick\tData\tMotivo\n");

	new row_count;
	cache_get_row_count(row_count);
	for(new ban_row; ban_row < row_count; ban_row++)
	{
	    cache_get_value_name(ban_row, "nome", ban_field);
	    format(ban_string, sizeof ban_string, "%s\t", ban_field);
	    strcat(MEGAString, ban_string);

	    cache_get_value_name(ban_row, "data", ban_field);
	    format(ban_string, sizeof ban_string, "%s\t", ban_field);
	    strcat(MEGAString, ban_string);

	    cache_get_value_name(ban_row, "motivo", ban_field);
	    format(ban_string, sizeof ban_string, "%s\n", ban_field);
	    strcat(MEGAString, ban_string);
	}

	format(ban_string, sizeof ban_string, "{FFFFFF}Lista de banidos por {00FFFF}%s", adminname);
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, ban_string, MEGAString, "Fechar", "");
}

show_list_bans_ultimos(playerid) {
	mysql_tquery(MySQL_Handle, "SELECT * FROM `banidos` ORDER BY `data` DESC LIMIT 30", "OnLoadedListBan", "i", playerid);
	ShowLoadingDialog(playerid);
}

CALLBACK:OnLoadedListBan(playerid) {
	new ban_string[128], ban_field[128];
	MEGAString[0] = EOS;
	strcat(MEGAString, "Nick\tData\tAdmin\tMotivo\n");
 
    new row_count;
    cache_get_row_count(row_count);
	for(new ban_row; ban_row < row_count; ban_row++) {

	    cache_get_value_name(ban_row, "nome", ban_field);
	    format(ban_string, sizeof ban_string, "%s\t", ban_field);
	    strcat(MEGAString, ban_string);

	    cache_get_value_name(ban_row, "data", ban_field);
	    format(ban_string, sizeof ban_string, "%s\t", ban_field);
	    strcat(MEGAString, ban_string);

	    cache_get_value_name(ban_row, "admin", ban_field);
	    format(ban_string, sizeof ban_string, "%s\t", ban_field);
	    strcat(MEGAString, ban_string);

	    cache_get_value_name(ban_row, "motivo", ban_field);
	    format(ban_string, sizeof ban_string, "%s\n", ban_field);
	    strcat(MEGAString, ban_string);
	}
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "{356FB2}Ultimos 30 banidos", MEGAString, "Fechar", "");
}
