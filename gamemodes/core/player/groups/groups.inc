#if defined _inc_groups_system
	#endinput
#endif
#define _inc_groups_system true

#include <YSI_Coding\y_hooks>

#include <groups_entry>

// ------------------------ Sistema de grupos de usuário ------------------------
new 
		Statement: stmt_selectPlayerGroup,
		Statement: stmt_selectPlayersGroup,
		Statement: stmt_updatePlayerGroup,
		Statement: stmt_vacancyGroup,
		Statement: stmt_addPlayerGroup;

hook OnMySQLConnected() 
{
    static const query_selectPlayerGroup[] = 
		"SELECT `nivel`, `cargo`, `funcao` FROM `cargos` WHERE `player` = ?"
	;
	stmt_selectPlayerGroup = MySQL_PrepareStatement(MySQL_Handle, query_selectPlayerGroup);

    static const query_selectPlayersGroup[] = 
		"SELECT \
            c.nivel, \
            p.id, \
            p.nome, \
            p.ultimo_login, \
            COALESCE(SUM(CASE WHEN a.diaDoAno = DAYOFYEAR(CURDATE()) AND a.ano = YEAR(CURDATE()) THEN a.atividade ELSE 0 END), 0) AS tempo_jogado_hoje, \
            COALESCE(SUM(CASE WHEN a.diaDoAno BETWEEN DAYOFYEAR(CURDATE()) - 6 AND DAYOFYEAR(CURDATE()) AND a.ano = YEAR(CURDATE()) THEN a.atividade ELSE 0 END), 0) AS tempo_jogado_semana \
        FROM \
            cargos c \
        LEFT JOIN \
            player p ON p.id = c.player \
        LEFT JOIN \
            atividades a ON a.player = p.id \
        WHERE \
            c.cargo = ? \
            AND c.player IS NOT NULL \
        GROUP BY \
            c.nivel, p.id, p.nome, p.ultimo_login \
        ORDER BY `nivel` DESC"
	;
	stmt_selectPlayersGroup = MySQL_PrepareStatement(MySQL_Handle, query_selectPlayersGroup);

    static const query_updatePlayerGroup[] = 
		"UPDATE `cargos` SET `player` = ?, `nivel` = ?, `funcao` = ? WHERE `player` = ? AND `cargo` = ?"
	;
	stmt_updatePlayerGroup = MySQL_PrepareStatement(MySQL_Handle, query_updatePlayerGroup);

    static const query_vacancyGroup[] = 
        "SELECT `id` FROM `cargos` WHERE `player` IS NULL AND `cargo` = ? LIMIT 1"
    ;
	stmt_vacancyGroup = MySQL_PrepareStatement(MySQL_Handle, query_vacancyGroup);

    static const query_addPlayerGroup[] = 
		"UPDATE `cargos` SET `player` = ?, `nivel` = ?, `funcao` = ? WHERE `id` = ? AND `cargo` = ?"
	;
	stmt_addPlayerGroup = MySQL_PrepareStatement(MySQL_Handle, query_addPlayerGroup);

    return 1;
}

// Groups
#include <admin_entry>
#include <helper_entry>
#include <dev>
#include <admin>
#include <speaker>
#include <youtuber>

hook OnPlayerLogin(playerid)
{
    inline const OnLoadPlayerGroup() {
		new nivel,
            group,
            function[54];

		MySQL_BindResultInt(stmt_selectPlayerGroup, 0, nivel);
		MySQL_BindResultInt(stmt_selectPlayerGroup, 1, group);
		MySQL_BindResult(stmt_selectPlayerGroup, 2, function);

		while (MySQL_Statement_FetchRow(stmt_selectPlayerGroup)) {
            switch (PlayerGroup:group) {
                case GROUP_SPEAKER: {
                    Speaker_SetNivel(playerid, SpeakerNivel:nivel);
                    SendMsgF(playerid, -1, "Olá %s, voce faz parte da "C_SPEAKER"EQUIPE RADIO "C_WHITE"do "SERVER_TAG"!", PlayerName[playerid]);
                }
                case GROUP_YOUTUBER: {
                    Youtuber_SetNivel(playerid, YoutuberNivel:nivel);
                    SendMsgF(playerid, -1, "Olá %s, voce faz parte dos "C_YOUTUBER"YOUTUBERS "C_WHITE"do "SERVER_TAG"!", PlayerName[playerid]);
                }
                case GROUP_HELPER: {
                    Helper_SetNivel(playerid, nivel);
                    callcmd::jogar(playerid, #);
                    SendMsgF(playerid, -1, "Olá %s, voce faz parte da "C_HELPER"EQUIPE HELPERS "C_WHITE"do "SERVER_TAG"!", PlayerName[playerid]);
                }
                case GROUP_ADMIN: {
                    gIsInAdminPasswordScreen[playerid] = true;

                    Admin_SetRemoveNivel(playerid, AdminNivel:nivel);
                    Staff_SetFunction(playerid, function);
                    Admin_SetNivel(playerid, NOT_ADMIN);

                    if (IsServerCreator(playerid)) goto skip;

                    new string[128];
                    MEGAString[0] = EOS;

                    format(string, sizeof(string), ""C_GRAY"Olá %s, você logou como admin %d.\n", PlayerName[playerid], nivel);
                    strcat(MEGAString, string);
                    strcat(MEGAString, ""C_WHITE"Por isso terá que digitar a senha de segurança da administração\n\n");

                    strcat(MEGAString, "    "C_WHITE"-> "C_GRAY"Caso você erre a senha, você será kickado e os admins serão avisados.\n");
                    strcat(MEGAString, "    "C_WHITE"-> "C_GRAY"Tome cuidado para não errar a senha muitas vezes, pois você será banido!\n\n");

                    strcat(MEGAString, ""C_WHITE"Digite a senha da administração abaixo:\n\n");

                    inline D_SenhaAdmin(mdlid, mdldialogid, mdlresponse, mdllistitem, string:mdltext[])
                    {
                        #pragma unused mdlid, mdldialogid, mdllistitem
                        if (!mdlresponse) {
                            KickEx(playerid);
                            return 1;
                        }

                        if (strlen(mdltext)) {
                            if (!strcmp(mdltext, SenhaAdministracao, true)) {
                                skip:
                                CallLocalFunction("OnAdminLogin", "i", playerid);
                                return 1;
                            }
                        }

                        SendClientMessage(playerid, COLOR_LIGHTRED, "Você foi kickado por errar a senha da administração, os admins foram avisados!");
                        KickEx(playerid);

                        format(string, sizeof string, "AdmAviso: %s errou a senha da administração e foi kickado!", PlayerName[playerid]);
                        Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

                        ServerLog::("senhaadmin", "%s foi kickado por errar a senha da administração", PlayerName[playerid]);
                        
                        return 1;
                    }
                    Dialog_ShowCallback(playerid, using inline D_SenhaAdmin, DIALOG_STYLE_INPUT, ""C_ADMIND"Senha da administração", MEGAString, "Autenticar", "Cancelar");
                }
            }
		}
	}
	MySQL_BindInt(stmt_selectPlayerGroup, 0, Player_GetAccountID(playerid));
	MySQL_ExecuteParallel_Inline(stmt_selectPlayerGroup, using inline OnLoadPlayerGroup);
    
    return 1;
}

stock Group_UpdateVacancy(idplayer, PlayerGroup:group, nivel, const function[]="")
{
    #pragma unused function
    switch (PlayerGroup:group) {
        case GROUP_ADMIN: {
            Admin_SetNivel(idplayer, AdminNivel:nivel);
            Staff_SetFunction(idplayer, function);
            CheckConquista(idplayer, Conquista_Admin);
        }
        case GROUP_HELPER: {
            Helper_SetNivel(idplayer, nivel);
            CheckConquista(idplayer, Conquista_Helper);
        }
        // case GROUP_DEVELOPER: {
        //     Dev_SetNivel(idplayer, DevNivel:nivel);
        //     Dev_SetFunction(idplayer, function);
        //     CheckConquista(idplayer, Conquista_Dev);
        // }
        case GROUP_SPEAKER: {
            Speaker_SetNivel(idplayer, SpeakerNivel:nivel);
        }
        case GROUP_YOUTUBER: {
            Youtuber_SetNivel(idplayer, YoutuberNivel:nivel);
        }
    }
    MySQL_BindInt(stmt_updatePlayerGroup, 0, Player_GetAccountID(idplayer));
    MySQL_BindInt(stmt_updatePlayerGroup, 1, nivel);
    MySQL_Bind(stmt_updatePlayerGroup, 2, function);
    MySQL_BindInt(stmt_updatePlayerGroup, 3, Player_GetAccountID(idplayer));
    MySQL_BindInt(stmt_updatePlayerGroup, 4, _:group);
    MySQL_ExecuteThreaded(stmt_updatePlayerGroup);
    return 1;
}

stock Group_Dismiss(idplayer, PlayerGroup:group)
{
    MySQL_Bind(stmt_updatePlayerGroup, 0, "NULL", true);
    MySQL_BindInt(stmt_updatePlayerGroup, 1, 0);
    MySQL_Bind(stmt_updatePlayerGroup, 2, "");
    MySQL_BindInt(stmt_updatePlayerGroup, 3, idplayer);
    MySQL_BindInt(stmt_updatePlayerGroup, 4, _:group);
    MySQL_ExecuteThreaded(stmt_updatePlayerGroup);
    return 1;
}

stock Group_GetVacancy(idplayer, nivel, PlayerGroup:group, const function[]="") {
    #pragma unused function

    inline const OnVacancyGroup() {
        new id_vacancy;

        MySQL_BindResultInt(stmt_vacancyGroup, 0, id_vacancy);

        if (!MySQL_Statement_FetchRow(stmt_vacancyGroup))
            return false;

        MySQL_BindInt(stmt_addPlayerGroup, 0, Player_GetAccountID(idplayer));
        MySQL_BindInt(stmt_addPlayerGroup, 1, nivel);
        MySQL_Bind(stmt_addPlayerGroup, 2, function);
        MySQL_BindInt(stmt_addPlayerGroup, 3, id_vacancy);
        MySQL_BindInt(stmt_addPlayerGroup, 4, _:group);
        MySQL_ExecuteThreaded(stmt_addPlayerGroup);
    }
    MySQL_BindInt(stmt_vacancyGroup, 0, _:group);
	MySQL_ExecuteThreaded_Inline(stmt_vacancyGroup, using inline OnVacancyGroup);
    return true;
}