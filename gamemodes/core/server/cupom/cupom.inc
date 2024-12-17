#include < YSI_Coding\y_hooks >

static 
    Statement: stmt_createCupom,
    Statement: stmt_selectCupom,
    Statement: stmt_useCupom,
    Statement: stmt_selectCupomUsed,
    Statement: stmt_updateCupom;

hook OnMySQLConnected() {

    static const query_createCupom[] = 
		"INSERT INTO `cupons` \
            (`code`, `description`, `value`, `units`, `date_created`)  \
        VALUES \
            ('?', '?', '?', '?', CURRENT_TIMESTAMP) \
        ";
	stmt_createCupom = MySQL_PrepareStatement(MySQL_Handle, query_createCupom);

    static const query_selectCupom[] = 
		"SELECT * FROM `cupons` WHERE `code` = '?'";
	stmt_selectCupom = MySQL_PrepareStatement(MySQL_Handle, query_selectCupom);

    static const query_updateCupom[] = 
		"UPDATE `cupons` SET `units` = '?' WHERE `code` = '?'";
	stmt_updateCupom = MySQL_PrepareStatement(MySQL_Handle, query_updateCupom);

    static const query_useCupom[] = 
		"INSERT INTO `cupons_used` (`id`, `player`, `code`, `date_used`) VALUES (NULL, '?', '?', CURRENT_TIMESTAMP)";
	stmt_useCupom = MySQL_PrepareStatement(MySQL_Handle, query_useCupom);

    static const query_selectCupomUsed[] = 
		"SELECT date_used FROM `cupons_used` WHERE `code` = '?' AND `player` = '?'";
	stmt_selectCupomUsed = MySQL_PrepareStatement(MySQL_Handle, query_selectCupomUsed);
}

static CreateCupom(const code[], const description[], value, units) {

    MySQL_Bind(stmt_createCupom, 0, code, true);
    MySQL_Bind(stmt_createCupom, 1, description, true);
    MySQL_BindInt(stmt_createCupom, 2, value);
    MySQL_BindInt(stmt_createCupom, 3, units);
    MySQL_ExecuteThreaded(stmt_createCupom);
}

stock Cupom_ShowDialog(playerid) {

    inline D_Cupom(dcpnid, dcpndialogid, dcpnresponse, dcpnlistitem, string:dcpntext[])
	{
		#pragma unused dcpnid, dcpndialogid, dcpnlistitem
		if (!dcpnresponse) 
			return callcmd::menu(playerid);

        if (strlen(dcpntext) < 1 || strlen(dcpntext) > 60)
            return SendClientMessage(playerid, COLOR_BLUELIGHT, "O cupom deve ter entre 1 á 60 caracteres.");

        Check_Cupom(playerid, dcpntext);
	}
    Dialog_ShowCallback(playerid, using inline D_Cupom, DIALOG_STYLE_INPUT, ""C_BLUELIGHT"Resgate de cupom", ""C_WHITE"Abaixo digite o codigo do cupom:", "Resgatar", ""C_WARNING"Fechar");

    return 1;
}

static Check_Cupom(playerid, const _code[]) 
{
    inline const OnLoadCupons() {

        new 
            description[128],
            date_created[50],
            code[60],
            value,
            units
        ;

        MySQL_BindResult(stmt_selectCupom, 0, code, sizeof(code));
        MySQL_BindResult(stmt_selectCupom, 1, description, sizeof(description));
        MySQL_BindResultInt(stmt_selectCupom, 2, value);
        MySQL_BindResultInt(stmt_selectCupom, 3, units);
        MySQL_BindResult(stmt_selectCupom, 4, date_created, sizeof(date_created));

        if (MySQL_Statement_FetchRow(stmt_selectCupom)) {
            
            if (units < 1) {
                SendClientMessage(playerid, COLOR_BLUELIGHT, "... Unidades insuficientes do cupom.");
            } else {
                inline const OnCupomUsed() {
                    if (MySQL_Statement_FetchRow(stmt_selectCupomUsed)) {
                        new date_used[50];

                        MySQL_BindResult(stmt_selectCupomUsed, 0, date_used, sizeof(date_used));

                        SendMsgF(playerid, COLOR_BLUELIGHT, "... Você já usou esse cupom no dia %s.", date_used);
                    } else {
                        MEGAString[0] = EOS;
                        new string[128];

                        format(string, sizeof(string), ""C_WHITE"Você resgatou o cupom "C_YELLOW"%s\n\n", code);
                        strcat(MEGAString, string);

                        format(string, sizeof(string), 
                            ""C_WHITE"Descrição: "C_GRAY"%s\n\n", description);
                        strcat(MEGAString, string);

                        Player_SetCash(playerid, Player_GetCash(playerid) + value);
                        
                        format(string, sizeof(string), ""C_WHITE"Valor: "C_CYAN"%s de cash\n", getFormatText(value));
                        strcat(MEGAString, string);

                        units--;

                        format(string, sizeof(string), ""C_WHITE"Unidades restantes: "C_GRAY"%d\n\n", units);
                        strcat(MEGAString, string);

                        format(string, sizeof(string), ""C_GRAY"Cupom criado em: %s", date_created);
                        strcat(MEGAString, string);

                        ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, ""C_BLUELIGHT"Resgate de cupom", MEGAString, ""C_WARNING"Fechar", "");

                        format(string, sizeof(string), "CUPOM: "C_WHITE"%s regastou um cupom de %s cash.", PlayerName[playerid], getFormatText(value));
                        SendClientMessageToAll(COLOR_BLUELIGHT, string);

                        MySQL_BindInt(stmt_updateCupom, 0, units);
                        MySQL_Bind(stmt_updateCupom, 1, code, true);
                        MySQL_ExecuteThreaded(stmt_updateCupom);

                        MySQL_BindInt(stmt_useCupom, 0, Player_GetAccountID(playerid));
                        MySQL_Bind(stmt_useCupom, 1, code, true);
                        MySQL_ExecuteThreaded(stmt_useCupom);
                    }
                }
                MySQL_Bind(stmt_selectCupomUsed, 0, code, true);
                MySQL_BindInt(stmt_selectCupomUsed, 1, Player_GetAccountID(playerid));
                MySQL_ExecuteThreaded_Inline(stmt_selectCupomUsed, using inline OnCupomUsed);
            } 
        } else {
            SendMsgF(playerid, COLOR_BLUELIGHT, "... O cupom %s não existe.", _code);
        }
    }
    MySQL_Bind(stmt_selectCupom, 0, _code, true);
    MySQL_ExecuteThreaded_Inline(stmt_selectCupom, using inline OnLoadCupons);
}

CMD:criarcupom(playerid, params[]) {

    if (!Player_Logado(playerid))
        return SendClientMessage(playerid, -1, "Você não está logado.");

    if (Dev_GetNivel(playerid) < DEV_DELTA)
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

    new code[60], 
        description[128],
        value,
        units;

    if (sscanf(params, "s[60]dds[128]", code, value, units, description))
		return SendClientMessage(playerid, -1, "Modo de uso: /criarcupom (código) (valor) (unidades) (descricao)");

    if (strlen(code) < 1 || strlen(code) > sizeof(code))
        return SendClientMessage(playerid, COLOR_BLUELIGHT, "O código deve ter no mínimo 1 caractere e no máximo 60.");

    if (strlen(description) < 1 || strlen(description) > sizeof(description))
        return SendClientMessage(playerid, COLOR_BLUELIGHT, "A descrição deve ter no máximo 128 caracteres.");

    if (Founders_GetList(playerid))
    {
        if (units > 50)
            return SendClientMessage(playerid, COLOR_BLUELIGHT, "O máximo de unidades para um Scripter em um cupom é 50.");

        goto skip_coders_cupom;
    }

    if (value > 5000)
        return SendClientMessage(playerid, COLOR_BLUELIGHT, "O máximo de valor em um cupom é de 5.000 cash.");
    
    if (units > 10)
        return SendClientMessage(playerid, COLOR_BLUELIGHT, "O máximo de unidades em um cupom é 10.");

    skip_coders_cupom:

    CreateCupom(code, description, value, units);

    new string[128];

    format(string, sizeof(string), "AdmAviso: %s criou um cupom de %s cash com %d unidades.", PlayerName[playerid], getFormatText(value), units);
    Staff_ChatToAll(COLOR_LIGHTRED, string);

    format(string, sizeof(string), "%s criou o cupom %s de %s cash com %d unidades.", PlayerName[playerid], code, getFormatText(value), units);
    server_log("cupom", string);

    return 1;
}