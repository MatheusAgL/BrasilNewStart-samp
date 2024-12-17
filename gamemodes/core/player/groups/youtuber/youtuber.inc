#if defined _inc_youtubers_system
	#endinput
#endif
#define _inc_youtubers_system true

#include <YSI_Coding\y_hooks>

#include <youtuber_entry>
#include <youtuber_cmds>

hook OnPlayerResetVars(playerid) 
{
    Youtuber_SetNivel(playerid, YOUTUBER_NONE);
    Youtuber_SetRec(playerid, false);
    return 1;
}

stock Youtuber_List(playerid, type=0)
{
	MEGAString[0] = EOS;
	strcat(MEGAString, "nick\tcargo\tultimo login\n");

    new string[128];
    inline const OnLoadYoutubers() {
		new cargo,
            player,
            playername[MAX_PLAYER_NAME],
            ultimo_login[35],
            count;

		MySQL_BindResultInt(stmt_selectPlayersGroup, 0, cargo);
		MySQL_BindResultInt(stmt_selectPlayersGroup, 1, player);
		MySQL_BindResult(stmt_selectPlayersGroup, 2, playername);
		MySQL_BindResult(stmt_selectPlayersGroup, 3, ultimo_login);

		while (MySQL_Statement_FetchRow(stmt_selectPlayersGroup)) {
			format(string, sizeof(string), ""C_YOUTUBER"%s\t"C_WHITE"%s\t"C_GRAY"%s\n", playername, Youtuber_GetPositionName(YoutuberNivel:cargo), ultimo_login);
            strcat(MEGAString, string);

            List_SetPlayers(playerid, count, player);
            count++;
		}

        if (type == 0) {
            ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Informações dos youtubers:", MEGAString, "Fechar", #);
        } else {
            inline D_YoutuberDismiss(did, ddialogid, dresponse, dlistitem, string:dtext[])
            {
                #pragma unused did, ddialogid, dtext

                if (!dresponse)
                    return 1;

                new id = List_GetPlayers(playerid, dlistitem),
                    idplayer = GetPlayerID(Player_GetNicknameByID(id));

                if (Player_Logado(idplayer)) {
                    Youtuber_SetNivel(idplayer, YOUTUBER_NONE);
                    Youtuber_SetRec(idplayer, false);

                    SendMsgF(idplayer, COLOR_LIGHTRED, "Você foi retirado dos youtubers por: %s.", PlayerName[playerid]);
                }
                Group_Dismiss(id, GROUP_YOUTUBER);

                SendMsgF(playerid, COLOR_LIGHTBLUE, "Você limpou a vaga de %s dos youtubers.", Player_GetNicknameByID(id));
                format(string, sizeof(string), "[YOUTUBERS]: %s limpou a vaga de %s.", PlayerName[playerid], Player_GetNicknameByID(id));
                server_log("youtubers", string);

                return Youtuber_List(playerid, 1);
            }
            Dialog_ShowCallback(playerid, using inline D_YoutuberDismiss, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Selecione uma vaga para limpar:", MEGAString, "Limpar", "Cancelar");
        }
	}
	MySQL_BindInt(stmt_selectPlayersGroup, 0, _:GROUP_YOUTUBER);
	MySQL_ExecuteThreaded_Inline(stmt_selectPlayersGroup, using inline OnLoadYoutubers);
	
	return 1;
}