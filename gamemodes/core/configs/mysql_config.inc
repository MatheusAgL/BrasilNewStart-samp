// MySQL:
#include <mysql_connection>

#include <db_utils>						// Utils de banco de dados

stock LoadConfig(const name[]) 
{
    new query[185];
	mysql_format(MySQL_Handle, query, sizeof query, "SELECT * FROM `config` WHERE `chave` = '%s' LIMIT 1", name);
	mysql_query(MySQL_Handle, query);

    new retorno[64] = "";
	if (MYSQL_GetRowsCount() > 0)
	    format(retorno, 64, MYSQL_GetString(0, "valor"));

    return retorno;
}

stock SaveConfigInt(const name[], value) 
{
    new query[185];
	mysql_format(MySQL_Handle, query, sizeof query, "UPDATE `config` SET valor = '%d' WHERE chave = '%s' LIMIT 1", value, name);
	mysql_tquery(MySQL_Handle, query);
}

stock SaveConfig(const name[], const value[]) 
{
    new query[185];
	mysql_format(MySQL_Handle, query, sizeof query, "UPDATE `config` SET valor = '%e' WHERE chave = '%s' LIMIT 1", value, name);
	mysql_tquery(MySQL_Handle, query);
}

stock SumConfigInt(const name[], value)
{
	new query[185];
	mysql_format(MySQL_Handle, query, sizeof query, "UPDATE `config` SET valor = CAST(valor AS SIGNED) + %d WHERE chave = '%s' LIMIT 1", value, name);
	mysql_tquery(MySQL_Handle, query);
}