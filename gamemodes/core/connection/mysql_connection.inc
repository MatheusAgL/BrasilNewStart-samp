#include <YSI_Coding\y_hooks>

// MySQL
#include <a_mysql>

// Statements
#define MAX_STATEMENTS (100)
#define MAX_PARAMS 50

#define MYSQL_PREPARE_DEBUG         (true)
#include <mysql_prepared>
// -----------------------------------------

// Define o formato da data MySQL
#define MYSQL_TIMESTAMP "%Y-%m-%d %H:%M:%S"
#define MYSQL_DATE "%Y-%m-%d"
#define DATE_FORMAT "%d/%m/%Y"
#define TIMESTAMP_FORMAT "%d/%m/%Y %H:%M:%S"

// Handle
new MySQL:MySQL_Handle;

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
	switch(errorid) {
		case 1136: printf("[MySQL] Error 1136 | Column count does not match value count => \"%s\"", query);
		case 1054: printf("[MySQL] Error 1054 | Invalid field name => \"%s\"", query);
		case 1065: printf("[MySQL] Error 1065 | Query was empty (variable's size too small?) => \"%s\" from \"%s\"", query, callback);
		case 1058: printf("[MySQL] Error 1058 | Column count doesn't match value count => \"%s\" from \"%s\"", query, callback);
		case 1203: printf("[MySQL] Error 1203 | User already has more than 'max_user_connections' active connections => \"%s\" from \"%s\"", query, callback);
		case 1045: printf("[MySQL] Error 1045 | Access denied");
		case ER_SYNTAX_ERROR: printf("[MySQL] Syntax Error => \"%s\"",query);

		default : printf("[MySQL] Error %d | Callback: %s | \"%s\"", errorid, callback, query);
	}
	return 1;
}

hook OnGameModeInit()
{
	new MySQLOpt: 
		option_id = mysql_init_options();

	mysql_set_option(option_id, AUTO_RECONNECT, false);
	//mysql_set_option(option_id, SSL_ENABLE, false);

    MySQL_Handle = mysql_connect_file("mysql.cfg");

    if (MySQL_Handle == MYSQL_INVALID_HANDLE || mysql_errno(MySQL_Handle) != 0) {
        print("MySQL: Falha na conexao... Servidor desligado!");
		// SendRconCommand("exit");
        return 1;
    }
	mysql_log(ERROR | WARNING);

	print("MySQL: Conectado com sucesso!");

    #if defined SETUP_TABLE
        CallLocalFunction("OnMySQLSetupTable", "");
    #endif

    CallLocalFunction("OnMySQLConnected", "");

    return 1;
}

stock MySQL_DestroyConnection() 
{
    mysql_close(MySQL_Handle);
	print("MySQL: Desconectado com sucesso!");
    return 1;
}