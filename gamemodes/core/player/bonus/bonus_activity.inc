#include <YSI_Coding\y_hooks>

#define         VALUE_BONUS_ACTIVITY        2000

hook OnResetDay()
{
    Bonus_Activity();
    return 1;
}

stock Bonus_Activity()
{
    new const query_selectRank[] = 
		    "SELECT p.`id`, p.`cash`, r.`nome`, r.`jogoudia` FROM `ranks` r INNER JOIN `player` p ON p.`nome` = r.`nome` ORDER BY `jogoudia` DESC LIMIT 1";

    new Statement:stmt_selectRank = MySQL_PrepareStatement(MySQL_Handle, query_selectRank);
    
    inline const OnSelectedRank() 
    {
        new string[128],
            player_id,
            name[MAX_PLAYER_NAME],
            jogoudia,
            cash;

        MySQL_BindResultInt(stmt_selectRank, 0, player_id);
        MySQL_BindResultInt(stmt_selectRank, 1, cash);
        MySQL_BindResult(stmt_selectRank, 2, name);
        MySQL_BindResultInt(stmt_selectRank, 3, jogoudia);

        if (MySQL_Statement_FetchRow(stmt_selectRank)) {
            if (jogoudia > 0) {

                format(string, sizeof(string), "Ativo do dia: "C_WHITE"%s ganhou "C_CYAN"%s (Cash) "C_WHITE"por ficar "C_CYAN"%s "C_WHITE"TOP 1 do (/rank) 'Mais ativo do dia'.", name, getFormatText(VALUE_BONUS_ACTIVITY), ConvertTime(jogoudia));
                SendClientMessageToAll(COLOR_CYAN, string);
                server_log("cash", string);

                new idplayer = GetPlayerID(name);
                if (Player_Logado(idplayer)) {
                    Player_AddCash(idplayer, VALUE_BONUS_ACTIVITY);
                } else {
                    MySQL_Bind(stmt_updatePlayerStats, 0, "cash", true);
                    MySQL_BindInt(stmt_updatePlayerStats, 1, cash + VALUE_BONUS_ACTIVITY);
                    MySQL_BindInt(stmt_updatePlayerStats, 2, player_id);
                    MySQL_ExecuteParallel(stmt_updatePlayerStats);
                }
            }
        }
        MySQL_StatementClose(stmt_selectRank);
    }
    MySQL_ExecuteThreaded_Inline(stmt_selectRank, using inline OnSelectedRank);

	mysql_tquery(MySQL_Handle, "UPDATE `ranks` SET `jogoudia` = '0'");
    return 1;
}

CMD:asijdausidhaushd43534543(playerid)
    return Bonus_Activity();