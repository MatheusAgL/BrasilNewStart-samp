#include <YSI_Coding\y_hooks>

// ------------------------ Sistema de operações ------------------------
static 
		Statement: stmt_selectOperactions,
        Statement: stmt_updateOperactions;

hook OnMySQLConnected() 
{
	static const query_selectOperactions[] = 
		"SELECT p.`nome`, o.* FROM `player` p INNER JOIN `operacoes` o ON p.`id` = o.`player` WHERE `executado_em` IS NULL"
	;
	stmt_selectOperactions = MySQL_PrepareStatement(MySQL_Handle, query_selectOperactions);

    static const query_updateOperactions[] = 
		"UPDATE `operacoes` SET `executado_em` = NOW() WHERE `id` = ?"
	;
	stmt_updateOperactions = MySQL_PrepareStatement(MySQL_Handle, query_updateOperactions);

	return 1;
}

stock Operations_LoadPending() 
{
    inline const OnLoadOperations() 
    {
		new op_name[MAX_PLAYER_NAME],
			op_id,
            op_type[10],
            op_item[10],
            op_info[70];

		MySQL_BindResult(stmt_selectOperactions, 0, op_name);
		MySQL_BindResultInt(stmt_selectOperactions, 1, op_id);
        MySQL_BindResult(stmt_selectOperactions, 3, op_type);
        MySQL_BindResult(stmt_selectOperactions, 4, op_info);
        MySQL_BindResult(stmt_selectOperactions, 7, op_item);

		while(MySQL_Statement_FetchRow(stmt_selectOperactions)) {
            ExecutarOperacao(op_name, op_id, op_type, op_item, op_info);
		}
	}
	MySQL_ExecuteParallel_Inline(stmt_selectOperactions, using inline OnLoadOperations);
    return 1;
}

stock ExecutarOperacao(const nick[], operationid, const tipo[], const item[], const info[]) 
{
    new string[128],
        playerid = GetPlayerID(nick);

    if (Player_Logado(playerid)) 
    {
        if (!strcmp(item, "CASA", true)) {
            if (!strcmp(tipo, "ADD", true)) {

                new casaid = strval(info);
                House_SetOwner(casaid, Player_GetAccountID(playerid), PlayerName[playerid]);
                House_Update(casaid);
                House_Save(casaid);

                new MapZone:zone = GetMapZoneAtPoint2D(House_GetEntryX(casaid), House_GetEntryY(casaid));
				new zone_name[MAX_MAP_ZONE_NAME];
				GetMapZoneName(zone, zone_name);

                format(string, 128, "<< OPERAÇÃO >> Você recebeu a casa %d, em %s. Use /casa ajuda para ver os comandos.", casaid, zone_name);
                SendClientMessage(playerid, COLOR_ORANGE, string);

                PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
                Operation_Save(operationid);
            }
        }
        else if (!strcmp(item, "PROPRIEDADE", true)) {
            if (!strcmp(tipo, "ADD", true)) {

                new id = strval(info);
                SetPropertyOwner(id, playerid);
                Property_SetDate(id, Days:7);
                atualizarPropText(id);
                savePropertie(id);

                format(string, 128, "<< OPERAÇÃO >> Você recebeu a propriedade %s[%d]. Use /propriedade ajuda para ver os comandos.",
                    id, PropInfo[id][ePname]);
                SendClientMessage(playerid, COLOR_ORANGE, string);

                PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
                Operation_Save(operationid);
            }
        }
        // else if (!strcmp(item, "FAZENDA", true)) {
        //     if (!strcmp(tipo, "ADD", true)) {
        //         new fazendaid = strval(info);
        //         Fazenda_SetOwner(fazendaid, playerid);
        //         Fazenda_SetDate(fazendaid, Days:3);

        //         format(string, 128, "<< OPERAÇÃO >> Você recebeu a fazenda %d. Use /ajudafazenda para ver os comandos.", fazendaid);
        //         SendClientMessage(playerid, COLOR_ORANGE, string);

        //         PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
        //         Operation_Save(operationid);
        //     }
        // }
        else if (!strcmp(item, "ITEM", true)) {
            if (!strcmp(tipo, "ADD", true)) {

                new string_inv[8][76], itemnome[75], itemtype, modelid, quantidade, cor1, cor2;
                split(info, string_inv, '|');

                format(itemnome, 75, string_inv[0]);
                itemtype = strval(string_inv[2]);
                modelid	= strval(string_inv[3]);
                quantidade = strval(string_inv[4]);
                cor1 = strval(string_inv[5]);
                cor2 = strval(string_inv[6]);

                if (givePlayerItem(playerid, itemtype, modelid, quantidade, itemnome, cor1, cor2)) {
                    format(string, 128, "<< OPERAÇÃO >> Você recebeu o item %s com %d unidade(s). Veja em seu inventário!", itemnome, quantidade);
                    SendClientMessage(playerid, COLOR_ORANGE, string);

                    PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
                    Operation_Save(operationid);
                }
                else {
                    format(string, 128, "<< OPERAÇÃO >> Você não pode receber o item %s com %d unidade(s) por estar com o inventário cheio.", itemnome, quantidade);
                    return SendClientMessage(playerid, COLOR_LIGHTRED, string);
                }
            }
        }
    }
    
    if (!strcmp(item, "CADEIA", true)) {
        if (!strcmp(tipo, "ADD", true)) {

            new 
                string_split[8][76], 
                presoid,
                adminid,
                denuncianteid, 
                motivo[75],
                admin[MAX_PLAYER_NAME],
                preso[MAX_PLAYER_NAME],
                denunciante[MAX_PLAYER_NAME];

            split(info, string_split, '|');

            adminid = strval(string_split[0]);
            presoid = strval(string_split[1]);
            denuncianteid = strval(string_split[2]);
            format(motivo, 75, string_split[4]);

            format(admin, MAX_PLAYER_NAME, Player_GetNicknameByID(adminid));
            format(preso, MAX_PLAYER_NAME, Player_GetNicknameByID(presoid));
            format(denunciante, MAX_PLAYER_NAME, Player_GetNicknameByID(denuncianteid));

            if(strlen(admin) > 0 && strlen(preso) > 0 && strlen(denunciante) > 0) 
            {
                new id = GetPlayerID(preso);
                if(id != INVALID_PLAYER_ID && Player_Logado(id)) 
                    Cadeia(admin, id, denunciante, motivo);
                else
                    AgendarCadeia(admin, preso, denunciante, motivo);

                Operation_Save(operationid);
            }
        }
    }
    else if (!strcmp(item, "CASH", true)) {
        if (!strcmp(tipo, "ADD", true)) {
            new 
                string_split[2][10], 
                quantidade,
                metodo
            ;

            split(info, string_split, '|');

            quantidade = strval(string_split[0]);
            metodo = strval(string_split[1]);
            AtivarCash("Servidor", nick, quantidade, metodo);

            Operation_Save(operationid);
            UpdatePlayerInfos(playerid);
        }
    }
    else if (!strcmp(item, "EDIT_RG", true)) {
        if (!strcmp(tipo, "SET", true)) {

            new 
                string_split[5][50],
                query[128],
                level,
                horas_jogadas,
                dinheiro,
                matou, morreu
            ;

            split(info, string_split, '|');

            level = strval(string_split[0]);
            horas_jogadas = strval(string_split[1]);
            dinheiro = strval(string_split[2]);
            matou = strval(string_split[3]);
            morreu = strval(string_split[4]);

            mysql_format(MySQL_Handle, query, sizeof query, 
                "UPDATE \
                    `player` \
                SET \
                    `level` = '%d', \
                    `horas_jogadas` = '%d',  \
                    `dinheiro` = '%d',  \
                    `assassinatos` = '%d',  \
                    `mortes` = '%d',  \
                WHERE \
                    nome = '%s' \
            ", level, horas_jogadas, dinheiro, matou, morreu, nick);
            
			mysql_tquery(MySQL_Handle, query);

            Operation_Save(operationid);
        }
    }
    return 1;
}   

stock Operation_Save(operationid) {
    MySQL_BindInt(stmt_updateOperactions, 0, operationid);
    MySQL_ExecuteThreaded(stmt_updateOperactions);
}

task Operations_Execute[5*60*1000] () {
	Operations_LoadPending();

    if (!VERSION_TEST)
        DCC_SendEmbed(Embed_Online);
}