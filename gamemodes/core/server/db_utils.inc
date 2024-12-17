stock MYSQL_GetInt(row, const field[])
{
	new num;
	cache_get_value_name_int(row, field, num);
	return num;
}

stock bool:MYSQL_GetBool(row, const field[])
{
	new num;
	cache_get_value_name_int(row, field, num);
	return num == 1;
}

stock Float:MYSQL_GetFloat(row, const field[])
{
	new Float:num;
	cache_get_value_name_float(row, field, num);
	return num;
}

stock MYSQL_GetString(row, const field[])
{
	new str[128];
	cache_get_value_name(row, field, str);
	return str;
}

stock MYSQL_GetRowsCount() {
	new row_count;
    cache_get_row_count(row_count);
	return row_count;
}

stock MYSQL_IsNull(row, const field[]) {
	new bool:is_null;
	cache_is_value_name_null(row, field, is_null);
	return is_null ? (1) : (0);
}

stock ORM_IsValid(ORM:id, const name[], const key[])
{
	new 
		E_ORM_ERROR:status = orm_errno(id),
		log_string[128]
	;

	if(status == ERROR_OK) 
	{
		return true;
	}
	else if(status == ERROR_INVALID) 
	{
		format(log_string, 128, "Falha ao salvar %s => %s. ORM inválido!", name, key);
	}
	else if(status == ERROR_NO_DATA) 
	{
		format(log_string, 128, "Falha ao salvar %s => %s. ID não encontrado!", name, key);
	}
	return false;
}