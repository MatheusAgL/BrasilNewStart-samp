#if defined _inc_admin_system
	#endinput
#endif
#define _inc_admin_system true

#include <YSI_Coding\y_hooks>

// #include <admin_entry>
#include <helper_entry>
#include <helper_cmds>
#include <admin_functions>
#include <admin_cmds>

public OnRconLoginAttempt(ip[], password[], success) {
    if (success) {
        foreach(new i : Player) {
            if (!strcmp(ip, PlayerIP[i], true)) {
                new string[72 + MAX_PLAYER_NAME];
                if (Dev_GetNivel(i)) {
                    format(string, sizeof(string), "Bem vindo a rcon do servidor. Seu nick %s tem permissão para usar!", PlayerName[i]);
                    SendClientMessage(i, COLOR_LIGHTGREEN, string);

                    format(string, sizeof string, "AdmCmd: %s[%d] logou na rcon do servidor com permissão de nick.", PlayerName[i], i);
                    Staff_ChatToAll(COLOR_LIGHTGREEN, string);
                } else {
                    format(string, sizeof(string), "Seu nick %s, não tem permissão para logar na rcon e foi kickado.", PlayerName[i]);
                    SendClientMessage(i, COLOR_LIGHTRED, string);

                    KickEx(i);
                }
            }
        }
    }
    return 1;
}

hook OnPlayerConnect(playerid) 
{
	Attendance_SetValid(playerid, false);
    Attendance_SetPlayer(playerid, INVALID_PLAYER_ID);
	Report_SetValid(playerid, false);
	Report_SetPlayer(playerid, INVALID_PLAYER_ID);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) 
{
    if (Admin_GetNivel(playerid))
        SetCountAdmin(CountAdmin() - 1);

	if (Helper_GetNivel(playerid))
        SetCountHelper(CountHelper() - 1);

	SpySet_Messages(playerid, false);

    return 1;
}

hook OnPlayerResetVars(playerid)
{
	Dev_SetNivel(playerid, DEV_NONE);

	Admin_SetNivel(playerid, NOT_ADMIN);
	Admin_SetRemoveNivel(playerid, NOT_ADMIN);
    Staff_SetWorking(playerid, false);
    Staff_SetSecret(playerid, false);
	Staff_SetAFK(playerid, false);
	Staff_SetReasonAFK(playerid, "");

    Helper_SetNivel(playerid, 0);
	
	// Resetar o (/meavalie)
	new adminid;
	foreach (new i : Player) {
		adminid = AssessHelper_Get(i);
		if (adminid == playerid) {
			AssessHelper_Set(playerid, INVALID_PLAYER_ID);
			AssessHelper_SetTimer(playerid, 0);
		}
	}

	// Atendimento
	new player2 = Attendance_GetPlayer(playerid);
	if (player2 != INVALID_PLAYER_ID)
		Attendance_Finish(playerid, player2);
	
	// Report
	player2 = Report_GetPlayer(playerid);
	if (player2 != INVALID_PLAYER_ID)
		Report_Finish(playerid, player2);

	return 1;
}

CALLBACK: OnAdminLogin(playerid) 
{
    SetCountAdmin(CountAdmin() + 1);
    Admin_SetNivel(playerid, Admin_GetRemoveNivel(playerid));
	callcmd::jogar(playerid, #);

    SendMsgF(playerid, -1, "Senha correta! Bem vindo "C_ADMIN"%s"C_WHITE" cargo: "C_GREEN"%s", PlayerName[playerid], Staff_GetPositionName(playerid));

	gIsInAdminPasswordScreen[playerid] = false;
    PhoneOnline[playerid] = 1;

	if (Admin_GetNivel(playerid) == BETA_TESTER)
		Dev_SetNivel(playerid, DEV_ALPHA);

    if (Admin_GetNivel(playerid) == DESENVOLVEDOR || Admin_GetNivel(playerid) == PROGRAMADOR)
		Dev_SetNivel(playerid, DEV_DELTA);

    if (Founders_GetList(playerid))
		Dev_SetNivel(playerid, DEV_DELTA);
	
	if (!strcmp(PlayerName[playerid], "iHollyZinhO") || !strcmp(PlayerName[playerid], FOUNDER_NAME_01))
		Dev_SetNivel(playerid, DEV_OMEGA);

    return 1;
}

stock Staff_GetStatus(playerid)
{
    new string[75];

    if (Staff_GetAFK(playerid))
		format(string, sizeof(string), ""C_LIGHTGREEN"AUSENTE "C_GRAY": %s", Staff_GetReasonAFK(playerid));
    else if (GetPVarInt(playerid, "varTeamViewer"))
        format(string, sizeof(string), ""C_CYAN"TEAMVIEWER");
    else if (Attendance_GetValid(playerid))
	    format(string, sizeof(string), ""C_YELLOW"EM ATENDIMENTO "C_GRAY": %s", ConvertTime(gettime() - Attendance_GetTimer(playerid)));
    else if (Report_GetValid(playerid))
        format(string, sizeof(string), ""C_BURNED_YELLOW"EM REPORT "C_GRAY": %s", ConvertTime(gettime() - Report_GetTimer(playerid)));
    else if (GetPlayerEscTime(playerid) > 4)
		format(string, sizeof(string), ""C_LIGHTGREEN"ESC "C_GRAY": %s", ConvertTime(GetPlayerEscTime(playerid)));
    else if (!Staff_GetWorking(playerid))
        format(string, sizeof(string), ""C_LIGHTBLUE"JOGANDO", ConvertTime(GetPlayerEscTime(playerid)));
    else
        format(string, sizeof(string), ""C_GREEN"DISPONIVEL", ConvertTime(GetPlayerEscTime(playerid)));

    return string;
}

stock Admin_List(playerid, type=0)
{
	MEGAString[0] = EOS;
    new string[128];

	strcat(MEGAString, "nick\tcargo\tultimo login\n");
	
    inline const OnLoadAdmins() {
		new cargo,
            player,
            playername[MAX_PLAYER_NAME],
            ultimo_login[35],
            activity_now,
            activity_week,
            count;

		MySQL_BindResultInt(stmt_selectPlayersGroup, 0, cargo);
		MySQL_BindResultInt(stmt_selectPlayersGroup, 1, player);
		MySQL_BindResult(stmt_selectPlayersGroup, 2, playername);
		MySQL_BindResult(stmt_selectPlayersGroup, 3, ultimo_login);
		MySQL_BindResultInt(stmt_selectPlayersGroup, 4, activity_now);
		MySQL_BindResultInt(stmt_selectPlayersGroup, 5, activity_week);

		while (MySQL_Statement_FetchRow(stmt_selectPlayersGroup)) {
			format(string, sizeof(string), ""C_ADMIN"%s\t"C_WHITE"%s\t"C_GRAY"%s\n", playername, Admin_GetPositionName(AdminNivel:cargo), ultimo_login);
            strcat(MEGAString, string);

            List_SetPlayers(playerid, count, player);
            count++;
		}

        if (type == 0) {
			inline D_AdminInfo(did, ddialogid, dresponse, dlistitem, string:dtext[])
            {
                #pragma unused did, ddialogid, dtext

				MEGAString[0] = EOS;

                if (!dresponse)
                    return 1;

                if (dlistitem == -1)
                    return 1;

				new id = List_GetPlayers(playerid, dlistitem),
                    idplayer = GetPlayerID(Player_GetNicknameByID(id));

				if (Player_Logado(idplayer))
					format(string, sizeof(string), ""C_BURNED_YELLOW"Status: "C_GREEN"ONLINE\n\n");
				else
					format(string, sizeof(string), ""C_BURNED_YELLOW"Status: "C_RED"OFFLINE\n\n");
			
				strcat(MEGAString, string);

				format(string, sizeof(string), ""C_BURNED_YELLOW"Tempo jogado HOJE: "C_WHITE"%s\n", ConvertTime(activity_now));
				strcat(MEGAString, string);
				format(string, sizeof(string), ""C_BURNED_YELLOW"Tempo jogado na SEMANA: "C_WHITE"%s\n", ConvertTime(activity_week));
				strcat(MEGAString, string);

                ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Informações do admin", MEGAString, "Fechar", #);
                return 1;
            }
            Dialog_ShowCallback(playerid, using inline D_AdminInfo, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Informações da equipe staff", MEGAString, "Info", "Fechar");
        } else {
            inline D_AdminDismiss(did, ddialogid, dresponse, dlistitem, string:dtext[])
            {
                #pragma unused did, ddialogid, dtext

                if (!dresponse)
                    return 1;

                if (dlistitem == -1)
                    return 1;

                new id = List_GetPlayers(playerid, dlistitem),
                    idplayer = GetPlayerID(Player_GetNicknameByID(id));

                if (Player_Logado(idplayer)) {
                    Admin_SetNivel(idplayer, NOT_ADMIN);
                    Staff_SetSecret(idplayer, false);
                    Staff_SetWorking(idplayer, false);
					SetPlayerToTeamColor(idplayer);

                    SendMsgF(idplayer, COLOR_LIGHTRED, "Você foi retirado da equipe de admin por: %s.", PlayerName[playerid]);
                }
                Group_Dismiss(id, GROUP_ADMIN);

                SendMsgF(playerid, COLOR_LIGHTBLUE, "Você limpou a vaga de %s da equipe admin.", Player_GetNicknameByID(id));
                format(string, sizeof(string), "[EQUIPE STAFF]: %s limpou a vaga de %s.", PlayerName[playerid], Player_GetNicknameByID(id));
                server_log("admins", string);

                return Admin_List(playerid, 1);
            }
            Dialog_ShowCallback(playerid, using inline D_AdminDismiss, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Selecione uma vaga para limpar:", MEGAString, "Limpar", "Cancelar");
        }
	}
	MySQL_BindInt(stmt_selectPlayersGroup, 0, _:GROUP_ADMIN);
	MySQL_ExecuteThreaded_Inline(stmt_selectPlayersGroup, using inline OnLoadAdmins);
	return 1;
}

stock Helper_List(playerid, type=0)
{
	MEGAString[0] = EOS;
	strcat(MEGAString, "nick\tcargo\tultimo login\n");

    new string[128];
    inline const OnLoadHelpers() {
		new cargo,
            player,
			nivel,
            playername[MAX_PLAYER_NAME],
            ultimo_login[35],
            count;

		MySQL_BindResultInt(stmt_selectPlayersGroup, 0, cargo);
		MySQL_BindResultInt(stmt_selectPlayersGroup, 1, player);
		MySQL_BindResultInt(stmt_selectPlayersGroup, 2, nivel);
		MySQL_BindResult(stmt_selectPlayersGroup, 2, playername);
		MySQL_BindResult(stmt_selectPlayersGroup, 3, ultimo_login);

		while (MySQL_Statement_FetchRow(stmt_selectPlayersGroup)) {
			format(string, sizeof(string), ""C_HELPER"%s\t"C_WHITE"%s\t"C_GRAY"%s\n", playername, nivel, ultimo_login);
            strcat(MEGAString, string);

            List_SetPlayers(playerid, count, player);
            count++;
		}

        if (type == 0) {
            ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Informações da equipe helper:", MEGAString, "Fechar", #);
        } else {
            inline D_HelperDismiss(did, ddialogid, dresponse, dlistitem, string:dtext[])
            {
                #pragma unused did, ddialogid, dtext

                if (!dresponse)
                    return 1;

                if (dlistitem == -1)
                    return 1;

                new id = List_GetPlayers(playerid, dlistitem),
                    idplayer = GetPlayerID(Player_GetNicknameByID(id));

                if (Player_Logado(idplayer)) {
                    Helper_SetNivel(idplayer, 0);
                    Staff_SetSecret(idplayer, false);
                    Staff_SetWorking(idplayer, false);
					SetPlayerToTeamColor(idplayer);

                    SendMsgF(idplayer, COLOR_LIGHTRED, "Você foi retirado da equipe helper por: %s.", PlayerName[playerid]);
                }
                Group_Dismiss(id, GROUP_HELPER);

                SendMsgF(playerid, COLOR_LIGHTBLUE, "Você limpou a vaga de %s da equipe helper.", Player_GetNicknameByID(id));
                format(string, sizeof(string), "[EQUIPE HELPER]: %s limpou a vaga de %s.", PlayerName[playerid], Player_GetNicknameByID(id));
                server_log("helpers", string);

                return Helper_List(playerid, 1);
            }
            Dialog_ShowCallback(playerid, using inline D_HelperDismiss, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Selecione uma vaga para limpar:", MEGAString, "Limpar", "Cancelar");
        }
	}
	MySQL_BindInt(stmt_selectPlayersGroup, 0, _:GROUP_HELPER);
	MySQL_ExecuteThreaded_Inline(stmt_selectPlayersGroup, using inline OnLoadHelpers);
	
	return 1;
}

stock Staff_ChatToAll(COLOR, const message[], AdminNivel:nivel = ESTAGIARIO)
{
	foreach(new players : Player) 
    {
        if (Admin_GetNivel(players) >= CO_FUNDADOR) goto skip_founder_chatadmin;
        if (!Staff_GetWorking(players)) continue;

        skip_founder_chatadmin:
        if (nivel == ESTAGIARIO && Helper_GetNivel(players)) { SendClientMessage(players, COLOR, message); continue; }
		if (Admin_GetNivel(players) >= nivel) SendClientMessage(players, COLOR, message);
    }
	Discord_SendMessage(message, Channel_AdminAviso);
}

stock Staff_GetPositionName(playerid)
{
	new position_name[25] = "Desconhecido",
        sex = Player_GetSex(playerid);

    if (Helper_GetNivel(playerid))
        position_name = "Helper";

	if (Admin_GetNivel(playerid))
		format(position_name, sizeof(position_name), Admin_GetPositionName(Admin_GetNivel(playerid), sex));

	return position_name;
}

stock PlayerKick(player = INVALID_PLAYER_ID, DCC_User: user = DCC_INVALID_USER, idplayer, const reason[])
{
	new string[128];
	if (user != DCC_INVALID_USER) {
		new username[DCC_USERNAME_SIZE];
		DCC_GetUserName(user, username);

		format(string, sizeof(string), 
			"=( STAFF "C_WHITE"- [discord] %s kickou %s, motivo: "C_GRAY"%s.", 
			username, PlayerName[idplayer], reason);
	} else {
		format(string, sizeof(string), 
			"=( STAFF "C_WHITE"- %s, %s kickou %s, motivo: "C_GRAY"%s.", 
			Staff_GetPositionName(player), PlayerName[player], PlayerName[idplayer], reason);
	}
	SendClientMessageToAll(COLOR_ADMIN, string);
	ServerLog::("kick", string);

	KickEx(idplayer);
	PlayerPlaySound(idplayer, 31202, 0.0, 0.0, 0.0);

	return 1;
}

stock PlayerBan(player = INVALID_PLAYER_ID, DCC_User: user = DCC_INVALID_USER, const nameBanned[], const reason[], days = -1, bool:secret = false)
{
	new string[128],
		unban_date[36];
		
	if (days == -1) format(unban_date, sizeof(unban_date), "TEMPO INDETERMINADO");
	else format(unban_date, sizeof(unban_date), "%d DIAS", days);

	if (user != DCC_INVALID_USER) {
		new username[DCC_USERNAME_SIZE];
		DCC_GetUserName(user, username);

		format(string, sizeof(string), 
			"[STAFF] "C_WHITE"[discord] %s baniu %s por %s, motivo: "C_GRAY"%s.", 
			username, nameBanned, unban_date, reason);
	} else {
		format(string, sizeof(string), 
			"[STAFF] "C_WHITE"%s, %s baniu %s por %s, motivo: "C_GRAY"%s.", 
			Staff_GetPositionName(player), PlayerName[player], nameBanned, unban_date, reason);
	}
	if (!secret) SendClientMessageToAll(COLOR_ADMIN, string);
	else Staff_ChatToAll(COLOR_ADMIN, string, MASTER);
	ServerLog::("banimentos", string);

	new idplayer = GetPlayerID(nameBanned),
		idgplayer = Player_GetAccountIDByNick(nameBanned);

	if (Player_Logado(idplayer)) {
		Banned_Player(idgplayer, Player_GetAccountID(player), PlayerIP[idplayer], reason, days), KickEx(idplayer);
		PlayerPlaySound(idplayer, 31202, 0.0, 0.0, 0.0);
	} else {
		Banned_Player(idgplayer, Player_GetAccountID(player), "0.0.0.0", reason, days);
	}
	return 1;
}

task Task_AutoReorganizeStaff[300000] ()
{
	new string[128],
		reports,
		attendances,
		biggerTimer,
		waiting = INVALID_PLAYER_ID;

	foreach(new x : Player)
	{
		if (Report_GetValid(x) && 
			Report_GetPlayer(x) == INVALID_PLAYER_ID && 
			Report_GetAccused(x) != INVALID_PLAYER_ID) {

			if (Report_GetTimer(x) > biggerTimer) {
				biggerTimer = Report_GetTimer(x);
				waiting = x;
			}
			reports++;
		}
		if (Attendance_GetValid(x) && 
			Attendance_GetPlayer(x) == INVALID_PLAYER_ID) {

			if (Attendance_GetTimer(x) > biggerTimer) {
				biggerTimer = Attendance_GetTimer(x);
				waiting = x;
			}
			attendances++;
		}
	}

	if ((reports + attendances) > 0)
	{
		format(string, sizeof(string), "[ALERTA-STAFF]: Existe(m) %d report(s) e %d atendimento(s) pendente(s). Atenda-os, por favor!", reports, attendances);
		Staff_ChatToAll(COLOR_LIGHTRED, string);

		if (biggerTimer >= 180) {
			format(string, sizeof (string), "[ALERTA-STAFF]: %s está aguardando atendimento há %s.", PlayerName[waiting], ConvertTime(gettime() - biggerTimer));
			Staff_ChatToAll(COLOR_LIGHTRED, string);
		}
	}

	new admins = CountAdmin(), 
		helpers = CountHelper();

	if (admins <= 1 && 
		helpers > 0) {
		foreach(new playerid : Player)
		{
			if (Player_Logado(playerid) && Helper_GetNivel(playerid) > 100 && !Admin_GetNivel(playerid)) 
			{
				Admin_SetNivel(playerid, ESTAGIARIO);
				Staff_SetFunction(playerid, "Temporário");
				Staff_SetWorking(playerid, true);

				SetPlayerToTeamColor(playerid);

				SendClientMessage(playerid, COLOR_LIGHTBLUE, "[INFO-STAFF] Você foi promovido automaticamente a Estagiário pois não há administradores online.");
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "[INFO-STAFF] Tome cuidado com os comandos e seja prudente. Lembre-se que é uma promoção temporária.");

				ServerLog::("administracao", "[GERENCIAMENTO]: %s foi promovido a Estagiário automaticamente.", PlayerName[playerid]);
				break;
			}
		}
	}	
	else if (admins > 3) {
		foreach(new playerid : Player)
		{
			if (Player_Logado(playerid) && 
				Helper_GetNivel(playerid) && 
				Admin_GetNivel(playerid) == ESTAGIARIO)
			{
				Admin_SetNivel(playerid, NOT_ADMIN);
				Staff_SetFunction(playerid, "Nenhuma");
				Staff_SetWorking(playerid, false);
				
				SetPlayerToTeamColor(playerid);

				SendClientMessage(playerid, COLOR_LIGHTRED, "[INFO-STAFF] Você foi retirado de Estagiário por ter administradores suficiente online.");
				ServerLog::("administracao", "[GERENCIAMENTO]: %s foi removido de Estagiário automaticamente.", PlayerName[playerid]);
			}
		}
	}
}

stock Attendance_Open(playerid, const reason[])
{
	Attendance_SetValid(playerid, true);
	Attendance_SetPlayer(playerid, INVALID_PLAYER_ID);
	Attendance_SetTimer(playerid, gettime());
	Attendance_SetReason(playerid, reason);

	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Voce solicitou um atendimento! Aguarde... Caso queira cancelar: /terminar atendimento.");

	new string[128];
	format(string, sizeof(string), "[ATENDIMENTO]: %s precisa de um admin (/atender %d) | assunto: %s", PlayerName[playerid], playerid, reason);
	Staff_ChatToAll(COLOR_LIGHTRED, string);
	
	format(string, sizeof(string), "[ATENDIMENTO]: %s solicitou atendimento, assunto: %s", PlayerName[playerid], reason);
	ServerLog::("atendimento", string);
	Discord_SendMessage(string, Channel_Attendance);
}

stock Attendance_ToMeet(adminid, playerid)
{
	if (!Attendance_GetValid(playerid)) return 0;

	Attendance_SetValid(adminid, true);
	Attendance_SetPlayer(adminid, playerid);
	Attendance_SetTimer(adminid, gettime());

	Attendance_SetValid(playerid, true);
	Attendance_SetPlayer(playerid, adminid);
	Attendance_SetTimer(playerid, gettime());

	new string[128];
	format(string, sizeof(string), "Atendimento: Você está atendendo o jogador %s | Assunto: %s", PlayerName[playerid], Attendance_GetReason(playerid));
	SendClientMessage(adminid, COLOR_ATENDIMENTO, string);

	format(string, sizeof(string), "Atendimento: %s, %s atendeu você | Assunto: %s", Staff_GetPositionName(adminid), PlayerName[adminid], Attendance_GetReason(playerid));
	SendClientMessage(playerid, COLOR_ATENDIMENTO, string);

	SendClientMessage(playerid, COLOR_ATENDIMENTO, "OBS: Aperte 'T' para digitar no chat ou use o VoIP. Para encerrar use: /terminar atendimento");
    SendClientMessage(adminid, COLOR_ATENDIMENTO, "OBS: Aperte 'T' para digitar no chat ou use o VoIP. Para encerrar use: /terminar atendimento");

	format(string, sizeof(string), "[ATENDIMENTO]: %s, %s está atendendo %s (ID: %d).", Staff_GetPositionName(adminid), PlayerName[adminid], PlayerName[playerid], playerid);
	Staff_ChatToAll(COLOR_LIGHTRED, string);
	ServerLog::("atendimento", string);
	Discord_SendMessage(string, Channel_Attendance);

	return 1;
}

stock Attendance_Finish(adminid, playerid)
{
	new string[128],
		time = gettime() - Attendance_GetTimer(playerid);

	Attendance_SetValid(playerid, false);
	Attendance_SetPlayer(playerid, INVALID_PLAYER_ID);
	Attendance_SetTimer(playerid, 0);

	Attendance_SetValid(adminid, false);
	Attendance_SetPlayer(adminid, INVALID_PLAYER_ID);
	Attendance_SetTimer(adminid, 0);
	
	format(string, sizeof(string), "O atendimento foi encerrado, o tempo de duração foi de "C_MONEY"%s"C_WHITE". Tenha um bom jogo!!", ConvertTime(time));
	SendClientMessage(playerid, COLOR_WHITE, string);
	SendClientMessage(adminid, COLOR_WHITE, string);

	format(string, sizeof(string), "[ATENDIMENTO]: %s terminou atendimento com %s", PlayerName[adminid], PlayerName[playerid]);
	ServerLog::("atendimento", string);
	Discord_SendMessage(string, Channel_Attendance);
	
	if (time > 20) {
		mysql_format(MySQL_Handle, string, sizeof(string), "UPDATE `ranks` SET `atendimento` = `atendimento` + 1 WHERE `nome` = '%s'", PlayerName[adminid]);
		mysql_tquery(MySQL_Handle, string);
	}
}

stock Attendance_List(playerid)
{
    new string[128],
		count;

	MEGAString[0] = EOS;
	strcat(MEGAString, "id	nick\ttempo de espera\tmotivo\n");

	foreach(new i : Player) {
		if (Attendance_GetValid(i) && Attendance_GetPlayer(i) == INVALID_PLAYER_ID) {
			format(string, sizeof(string), ""C_GRAY"%03d	"C_WHITE"%s\t"C_GRAY"%s\t"C_BURNED_YELLOW"%s\n", i, PlayerName[i], ConvertTime(gettime() - Attendance_GetTimer(i)), Attendance_GetReason(i));
			strcat(MEGAString, string);
			
			List_SetPlayers(playerid, count, i);
			count++;
		}
	}

	inline D_AttendanceToMeet(did, ddialogid, dresponse, dlistitem, string:dtext[])
	{
		#pragma unused did, ddialogid, dtext

		if (!dresponse)
			return 1;

		if (dlistitem == -1)
			return 1;

		new playerclick = List_GetPlayers(playerid, dlistitem);

		if (!Player_Logado(playerclick))
			return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

		format(string, sizeof(string), "%d", playerclick);
		callcmd::atender(playerid, string);

		return Attendance_List(playerid);
	}
	Dialog_ShowCallback(playerid, using inline D_AttendanceToMeet, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Selecione um atendimento:", MEGAString, "Atender", "Fechar");
	return 1;
}

stock Report_Open(playerid, accused, const reason[])
{
	Report_SetValid(playerid, true);
	Report_SetPlayer(playerid, INVALID_PLAYER_ID);
	Report_SetAccused(playerid, accused);
	Report_SetTimer(playerid, gettime());
	Report_SetReason(playerid, reason);

	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Voce reportou um jogador! Aguarde... Caso queira cancelar: /terminar report.");

	new string[128];
	format(string, sizeof(string), "[REPORT]: %s está reportando %s (/areport %d) | motivo: %s", PlayerName[playerid], PlayerName[accused], playerid, reason);
	Staff_ChatToAll(COLOR_REPORT, string);
	
	format(string, sizeof(string), "[REPORT]: %s reportou %s (%d), motivo: %s", PlayerName[playerid], PlayerName[accused], accused, reason);
	ServerLog::("reports", string);
	Discord_SendMessage(string, Channel_Attendance);
}

stock Report_ToMeet(adminid, playerid)
{
	if (!Report_GetValid(playerid)) return 0;

	new accused = Report_GetAccused(playerid);

	Report_SetValid(adminid, true);
	Report_SetPlayer(adminid, playerid);
	Report_SetAccused(adminid, accused);
	Report_SetTimer(adminid, gettime());

	Report_SetValid(playerid, true);
	Report_SetPlayer(playerid, adminid);
	Report_SetTimer(playerid, gettime());

	new string[128];
	format(string, sizeof(string), "REPORT: Você está atendendo %s | Acusado: %s (%d) | Motivo: %s", PlayerName[playerid], PlayerName[accused], accused, Report_GetReason(playerid));
	SendClientMessage(adminid, COLOR_REPORT, string);

	format(string, sizeof(string), "REPORT: %s, %s está atendendo seu report no jogador %s (%d), motivo: %s", Staff_GetPositionName(adminid), PlayerName[adminid], PlayerName[accused], accused, Report_GetReason(playerid));
	SendClientMessage(playerid, COLOR_REPORT, string);

	SendClientMessage(playerid, COLOR_REPORT, "OBS: Aperte 'T' para digitar no chat ou use o VoIP. Para encerrar use: /terminar atendimento");
    SendClientMessage(adminid, COLOR_REPORT, "OBS: Aperte 'T' para digitar no chat ou use o VoIP. Para encerrar use: /terminar atendimento");

	new params[5];
	format(params, sizeof(params), "%d", Report_GetAccused(playerid));
	callcmd::tv(adminid, params);

	format(string, sizeof(string), "AdmCmd: %s, %s está atendendo o report de: %s (%d)", Staff_GetPositionName(adminid), PlayerName[adminid], PlayerName[playerid], playerid);
	Staff_ChatToAll(COLOR_LIGHTRED, string);
	ServerLog::("reports", string);
	Discord_SendMessage(string, Channel_Attendance);

	return 1;
}

stock Report_List(playerid)
{
	MEGAString[0] = EOS;
	strcat(MEGAString, "id	nick\ttempo de espera\tsuspeito\tmotivo\n");

    new string[128],
		count;

	foreach(new i : Player) {
		if (Report_GetValid(i) && Report_GetPlayer(i) != INVALID_PLAYER_ID) {
			format(string, sizeof(string), ""C_GRAY"%03d	"C_WHITE"%s\t"C_GRAY"%s\t"C_RED"%s\t"C_BURNED_YELLOW"%s\n", i, PlayerName[i], ConvertTime(gettime() - Report_GetTimer(i)), Report_GetReason(i));
			strcat(MEGAString, string);
			
			List_SetPlayers(playerid, count, i);
			count++;
		}
	}

	inline D_ReportToMeet(did, ddialogid, dresponse, dlistitem, string:dtext[])
	{
		#pragma unused did, ddialogid, dtext

		if (!dresponse)
			return 1;

		if (!dresponse)
			return 1;

		if (dlistitem == -1)
			return 1;

		new playerclick = List_GetPlayers(playerid, dlistitem);

		if (!Player_Logado(playerclick))
			return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

		format(string, sizeof(string), "%d", playerclick);
		callcmd::areport(playerid, string);

		return Report_List(playerid);
	}
	Dialog_ShowCallback(playerid, using inline D_ReportToMeet, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Selecione um report:", MEGAString, "Atender", "Fechar");
	return 1;
}

stock Report_Finish(adminid, playerid)
{
	Report_SetValid(playerid, false);
	Report_SetPlayer(playerid, INVALID_PLAYER_ID);
	Report_SetAccused(playerid, INVALID_PLAYER_ID);
	Report_SetTimer(playerid, 0);

	Report_SetValid(adminid, false);
	Report_SetPlayer(adminid, INVALID_PLAYER_ID);
	Report_SetAccused(adminid, INVALID_PLAYER_ID);
	Report_SetTimer(adminid, 0);

	new string[128],
		time = gettime() - Report_GetTimer(playerid);
	
	format(string, sizeof(string), "O report foi encerrado, o tempo de duração foi de "C_MONEY"%s"C_WHITE". Tenha um bom jogo!!", ConvertTime(time));
	SendClientMessage(playerid, COLOR_WHITE, string);
	SendClientMessage(adminid, COLOR_WHITE, string);

	format(string, sizeof(string), "[REPORT]: %s terminou o report com %s", PlayerName[adminid], PlayerName[playerid]);
	ServerLog::("reports", string);
	Discord_SendMessage(string, Channel_Attendance);
	
	if (time > 20) {
		mysql_format(MySQL_Handle, string, sizeof(string), "UPDATE `ranks` SET `atendimento` = `atendimento` + 1 WHERE `nome` = '%s'", PlayerName[adminid]);
		mysql_tquery(MySQL_Handle, string);
	}
}

CMD:dm(playerid, params[])
{
	if(!Player_Logado(playerid))return SendClientMessage(playerid, -1, "Você não está logado !");

	new id;
	if(sscanf(params, "u", id))
	{
		SendClientMessage(playerid, -1, "Use: /dm [Playerid/Nome]");
		SendClientMessage(playerid, COLOR_LIGHTRED, "OBS: Apenas acuse o jogador se for realmente DM, ou será punido pelos admins !");
		return 1;
	}
	if (!Player_Logado(id)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if(Admin_GetNivel(id) && Staff_GetWorking(id))return SendClientMessage(playerid, -1, "Você não pode usar este comando em admins em modo trabalho !");

	if(!ProxDetectorS(200.0, playerid, id))return SendClientMessage(playerid, -1, "O jogador está muito longe de você !");

	if(gettime() < GetPVarInt(playerid, #VarFlood7))
		return SendClientMessage(playerid, COLOR_GRAD, #Você não pode usar este comando com tanta frequencia);
	SetPVarInt(playerid, #VarFlood7, gettime()+30);

	new string[256];

	format(string, sizeof string, "[DM]: %s [ID %d] acusou %s [ID %d], resultado: %s", PlayerName[playerid],playerid,PlayerName[id],id,ResultadoDM(playerid,id));
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

	format(string, sizeof string, "*Você acusou %s de cometer DM, resultado: %s", PlayerName[id], ResultadoDM(playerid,id));
	SendClientMessage(playerid, COLOR_GRAD, string);
	SendClientMessage(playerid, COLOR_GRAD, "OBS: Caso voce acusou o jogador injustamente, você será punido por um admin !");
	return 1;
}

stock ResultadoDM(playerid, acusado)
{
	new result[75];

	if(DMSystem[playerid][acusado] && !DMSystem[acusado][playerid])
		result = "{FF0000}O DENÚNCIANTE AGREDIU PRIMEIRO";

	else if(!DMSystem[playerid][acusado] && DMSystem[acusado][playerid])
		result = "{00FF00}O ACUSADO AGREDIU PRIMEIRO";
	else if(DMSystem[playerid][acusado] && DMSystem[acusado][playerid])
		result = "{FFFF00}AMBOS SE AGREDIRAM";
	else
		result = "{FFFFFF}NENHUM DOS DOIS SE AGREDIU";

	return result;
}