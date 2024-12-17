
#include <YSI_Coding\y_hooks>

// ---------------------------------------------
// Módulo player

#include <player_entry>
#include <groups>
// #include <phone>
#include <player_spawn>			// Spawn
#include <banishment>			// Sistema de banimento
#include <changepass>			// Sistema de mudança de senha
#include <weekly_pass>			// Sistema de passe semanal
#include <consumable>			// Consumíveis
#include <login>				// Sistema de login
#include <licences>				// Licenças (Documentos)
#include <marriage>				// Casamento (Documentos)
#include <player_body>			// Corpo
#include <jail>					// Sistema de cadeia
#include <accessories>
#include <anims>				// Animações
#include <walking_styles>		// Estilos de andar
#include <orgs>					// Sistema de organização
#include <family>				// Sistema de familias
#include <player_logout>		// Logout
#include <vip>					// Sistema de VIP
#include <player_lastpos>		// Última posição
#include <player_struggle>		// Estilo de luta
#include <player_infos>			// Informações
#include <aggressive>			// Humor
#include <player_interactions>	// Interações
#include <player_married>		// Casamento
#include <player_afk>			// Ausente
#include <player_activity>		// Atividade
#include <player_eat>			// Comer & beber
#include <player_vices>			// Vicios
#include <player_titles>		// Titulos
#include <player_vehicles>		// Veículos
#include <vehicle_garage>

// Configurações de armas;
#include <weapon>

#include <patio>

// Plantações:
#include <cannabis_entry>
#include <cannabis>

// Báu
#include <bau>
#include <inventory>
#include <request_work>

// ------------------------ Sistema player ------------------------
new 
		Statement: stmt_updatePlayerStats,
		Statement: stmt_updatePlayerBank;

hook OnMySQLConnected() 
{
	static const query_updatePlayerStats[] = 
		"UPDATE `player` SET `?` = ? WHERE `id` = ?"
	;
	stmt_updatePlayerStats = MySQL_PrepareStatement(MySQL_Handle, query_updatePlayerStats);

	static const query_updatePlayerBank[] = 
		"UPDATE `player` SET `dinheiro_banco` = `dinheiro_banco` + ? WHERE `id` = ?"
	;
	stmt_updatePlayerBank = MySQL_PrepareStatement(MySQL_Handle, query_updatePlayerBank);

    return 1;
}

#include <bonus_activity>		// Bônus mais ativo do dia

stock Player_UpdateMoneyBank(id, value)
{
	MySQL_BindInt(stmt_updatePlayerBank, 0, value);
	MySQL_BindInt(stmt_updatePlayerBank, 1, id);
	MySQL_ExecuteParallel(stmt_updatePlayerBank);
}

// stock Player_GetAccountIDByNick(const nick[])
// {
// 	new idgplayer;
	
// 	inline const OnSelectPlayerByName() {
// 		new result_id;

// 		MySQL_BindResultInt(stmt_selectPlayerID, 0, result_id);
		
// 		if (MySQL_Statement_FetchRow(stmt_selectPlayerID))
// 			idgplayer = result_id;

// 		return idgplayer;
// 	}
// 	MySQL_Bind(stmt_selectPlayerID, 0, nick, true);
// 	MySQL_ExecuteThreaded_Inline(stmt_selectPlayerID, using inline OnSelectPlayerByName);

// 	return idgplayer;
// }

// stock Player_GetNicknameByID(id)
// {
// 	new name[MAX_PLAYER_NAME];

// 	inline const OnSelectPlayerByID() {
// 		new result_name[MAX_PLAYER_NAME];

// 		MySQL_BindResult(stmt_selectPlayer, 0, result_name);

// 		if (MySQL_Statement_FetchRow(stmt_selectPlayer))
// 			format(name, sizeof(name), result_name);

// 		return name;
// 	}
// 	MySQL_BindInt(stmt_selectPlayer, 0, id);
// 	MySQL_ExecuteThreaded_Inline(stmt_selectPlayer, using inline OnSelectPlayerByID);

// 	return name;
// }

stock Player_GetAccountIDByNick(const nick[])
{
	new query[128];

	mysql_format(MySQL_Handle, query, sizeof query, "SELECT id FROM `player` WHERE `nome` = '%s'", nick);
	mysql_query(MySQL_Handle, query);

	new row_count = MYSQL_GetRowsCount();
	if (row_count > 0)
		return MYSQL_GetInt(0, "id");

	return -1;
}

stock Player_GetNicknameByID(id)
{
	new query[128];

	mysql_format(MySQL_Handle, query, sizeof query, "SELECT nome FROM `player` WHERE `id` = %d", id);
	mysql_query(MySQL_Handle, query);

	new row_count = MYSQL_GetRowsCount(), str[MAX_PLAYER_NAME] = "";
	if(row_count > 0)
		format(str, MAX_PLAYER_NAME, MYSQL_GetString(0, "nome"));

	return str;
}

enum EditPlayer:
{
	EDIT_PLAYER_NONE,
	EDIT_PLAYER_LEVEL,
	EDIT_PLAYER_RESPEITO,
	EDIT_PLAYER_HORAS_JOGADAS,
	EDIT_PLAYER_DINHEIRO,
	EDIT_PLAYER_DINHEIRO_BANCO,
	EDIT_PLAYER_OUROS,
	EDIT_PLAYER_CASH,
	EDIT_PLAYER_VIPNIVEL,
	EDIT_PLAYER_KILL,
	EDIT_PLAYER_MORTES,
	EDIT_PLAYER_SEX,
	EDIT_PLAYER_SKIN,
	EDIT_PLAYER_CONTRATOS,
	EDIT_PLAYER_APREENSOES,
	EDIT_PLAYER_CELULAR,
	EDIT_PLAYER_MACONHA,
	EDIT_PLAYER_COCAINA,
	EDIT_PLAYER_CRACK,
	EDIT_PLAYER_SKILL_DET,
	EDIT_PLAYER_SKILL_ADV,
	EDIT_PLAYER_AVISOS,
	EDIT_PLAYER_PRISAO_ADM,
	EDIT_PLAYER_TROCAS_NICK,
};

stock Player_Info(const name[], DCC_Channel: channel) 
{
	new idplayer = GetPlayerID(name);
	MEGAString[0] = EOS;
	if (Player_Logado(idplayer)) {
		format(MEGAString, sizeof(MEGAString), "Informações do jogador **%s**\n \
					\n> Level: **%d**\
					\n> Respeitos: **%d**\
					\n> Horas Jogadas: **%d**\
					\n> Dinheiro: **%s**\
					\n> Dinheiro Banco: **%s**\
					\n> Ouros: **%s**\
					\n> Cash: **%s**\
					\n> VIP: **%s**\
					\n> Kills: **%d**\
					\n> Deaths: **%d**\
					\n> Skin: **%d**\
					\n> Contratos: **%d**\
					\n> Apreensões: **%d**\
					\n> Número de celular: **%d**\
					\n> Maconha: **%d**\
					\n> Cocaina: **%d**\
					\n> Crack: **%d**\
					\n> Skill detetive: **%d**\
					\n> Skill advogado: **%d**\
					\n> Avisos: **%d**\
					\n> Prisões admin: **%d**\
					\n> Trocas de nick: **%d**", 
					PlayerName[idplayer], Player_GetNivel(idplayer), PlayerInfo[idplayer][pExp], PlayerInfo[idplayer][pConnectTime], 
					getFormatText(Player_GetMoney(idplayer)), getFormatText(Player_GetMoneyBank(idplayer)), getFormatText(Player_GetOuros(idplayer)), 
					getFormatText(Player_GetCash(idplayer)), VIP_GetName(Player_GetVIP(idplayer)), PlayerInfo[idplayer][pKills], PlayerInfo[idplayer][pDeaths],
					PlayerInfo[idplayer][pKills], PlayerInfo[idplayer][pSex], PlayerInfo[idplayer][pContratos], PlayerInfo[idplayer][pMinhasApreensoes], 
					PlayerInfo[idplayer][numeroCelular], PlayerInfo[idplayer][pDrogas], PlayerInfo[idplayer][pDrogas2], PlayerInfo[idplayer][pDrogas3],
					PlayerInfo[idplayer][pDetSkill], PlayerInfo[idplayer][pAdvogadoSkill], PlayerInfo[idplayer][pWarns], PlayerInfo[idplayer][pPrisaoAdmin],
					PlayerInfo[idplayer][pTrocaNick]);

		new url[78];
		format(url, sizeof(url), ""SERVER_SITE"/static/img/skins/Avatar_%d.png", Player_GetSkin(idplayer));
		Discord_SendEmbed(Embed_InfoPlayer, channel, MEGAString, .thumbnail_img = url);
	} else {
		new const query_selectPlayerName[] = 
			"SELECT id, nome, level, respeitos, horas_jogadas, dinheiro, dinheiro_banco, ouros, cash, vip_nivel, assassinatos, mortes, skin, sexo, contratos, apreensoes, phone_number, 	\
			maconha, cocaina, crack, skill_detetive, skill_advogado, avisos, prisao_admin, trocas_nick FROM `player` WHERE `nome` = ? LIMIT 1"
		;
		new Statement:stmt_selectPlayerName = MySQL_PrepareStatement(MySQL_Handle, query_selectPlayerName);

		inline const OnDbSelect_PlayerInfo() {
			new 
				idgplayer,
				nome[MAX_PLAYER_NAME],
				level,
				respeitos,
				horas_jogadas,
				dinheiro,
				dinheiro_banco,
				ouros,
				cash,
				vip_nivel,
				kills,
				deaths,
				skin,
				sex,
				contracts,
				seizure,
				phone_number,
				marihuana,
				cocaine,
				crack,
				skill_det,
				skill_adv,
				warnings,
				admin_prision,
				change_nick;			

			MySQL_BindResultInt(stmt_selectPlayerName, 0, idgplayer);
			MySQL_BindResult(stmt_selectPlayerName, 1, nome);
			MySQL_BindResultInt(stmt_selectPlayerName, 2, level);
			MySQL_BindResultInt(stmt_selectPlayerName, 3, respeitos);
			MySQL_BindResultInt(stmt_selectPlayerName, 4, horas_jogadas);
			MySQL_BindResultInt(stmt_selectPlayerName, 5, dinheiro);
			MySQL_BindResultInt(stmt_selectPlayerName, 6, dinheiro_banco);
			MySQL_BindResultInt(stmt_selectPlayerName, 7, ouros);
			MySQL_BindResultInt(stmt_selectPlayerName, 8, cash);
			MySQL_BindResultInt(stmt_selectPlayerName, 9, vip_nivel);
			MySQL_BindResultInt(stmt_selectPlayerName, 10, kills);
			MySQL_BindResultInt(stmt_selectPlayerName, 11, deaths);
			MySQL_BindResultInt(stmt_selectPlayerName, 12, skin);
			MySQL_BindResultInt(stmt_selectPlayerName, 13, sex);
			MySQL_BindResultInt(stmt_selectPlayerName, 14, contracts);
			MySQL_BindResultInt(stmt_selectPlayerName, 15, seizure);
			MySQL_BindResultInt(stmt_selectPlayerName, 16, phone_number);
			MySQL_BindResultInt(stmt_selectPlayerName, 17, marihuana);
			MySQL_BindResultInt(stmt_selectPlayerName, 18, cocaine);
			MySQL_BindResultInt(stmt_selectPlayerName, 19, crack);
			MySQL_BindResultInt(stmt_selectPlayerName, 20, skill_det);
			MySQL_BindResultInt(stmt_selectPlayerName, 21, skill_adv);
			MySQL_BindResultInt(stmt_selectPlayerName, 22, warnings);
			MySQL_BindResultInt(stmt_selectPlayerName, 23, admin_prision);
			MySQL_BindResultInt(stmt_selectPlayerName, 24, change_nick);

			if (!MySQL_Statement_FetchRow(stmt_selectPlayerName))
				return 0;

			format(MEGAString, sizeof(MEGAString), "Informações do jogador %s\n \
						\n> Level: **%d**\
						\n> Respeitos: **%d**\
						\n> Horas Jogadas: **%d**\
						\n> Dinheiro:	**%s**\
						\n> Dinheiro Banco: **%s**\
						\n> Ouros: **%s**\
						\n> Cash: **%s**\
						\n> VIP: **%s**\
						\n> Kills: **%d**\
						\n> Deaths: **%d**\
						\n> Skin: **%d**\
						\n> Contratos: **%d**\
						\n> Apreensões: **%d**\
						\n> Número de celular: **%d**\
						\n> Maconha: **%d**\
						\n> Cocaina: **%d**\
						\n> Crack: **%d**\
						\n> Skill detetive: **%d**\
						\n> Skill advogado: **%d**\
						\n> Avisos: **%d**\
						\n> Prisões admin: **%d**\
						\n> Trocas de nick: **%d**", 
						nome, level, respeitos, horas_jogadas, getFormatText(dinheiro), getFormatText(dinheiro_banco),
						getFormatText(ouros), getFormatText(cash), VIP_GetName(vip_nivel), kills, deaths, skin, contracts, seizure,
						phone_number, marihuana, cocaine, crack, skill_det, skill_adv, warnings, admin_prision, change_nick);

			new url[78];
			format(url, sizeof(url), ""SERVER_SITE"/static/img/skins/Avatar_%d.png", skin);
			Discord_SendEmbed(Embed_InfoPlayer, channel, MEGAString, .thumbnail_img = url);
			MySQL_StatementClose(stmt_selectPlayerName);
		}
		MySQL_Bind(stmt_selectPlayerName, 0, name);
		MySQL_ExecuteParallel_Inline(stmt_selectPlayerName, using inline OnDbSelect_PlayerInfo);
	}
	return 1;
}

stock Player_Edit(playerid = INVALID_PLAYER_ID, DCC_User: user, const name[], EditPlayer:stats, value) 
{
	#pragma unused user, playerid
	new stats_name[25];

	switch (stats) {
		case EDIT_PLAYER_LEVEL: 			stats_name = "level";
		case EDIT_PLAYER_RESPEITO: 			stats_name = "respeitos";
		case EDIT_PLAYER_HORAS_JOGADAS: 	stats_name = "horas_jogadas";
		case EDIT_PLAYER_DINHEIRO: 			stats_name = "dinheiro";
		case EDIT_PLAYER_DINHEIRO_BANCO: 	stats_name = "dinheiro_banco";
		case EDIT_PLAYER_OUROS: 			stats_name = "ouros";
		case EDIT_PLAYER_CASH: 				stats_name = "cash";
		case EDIT_PLAYER_VIPNIVEL: 			stats_name = "vip_nivel";
		case EDIT_PLAYER_KILL: 				stats_name = "assassinatos";
		case EDIT_PLAYER_MORTES: 			stats_name = "mortes";
		case EDIT_PLAYER_SKIN: 				stats_name = "skin";
		case EDIT_PLAYER_SEX: 				stats_name = "sexo";
		case EDIT_PLAYER_CONTRATOS: 		stats_name = "contratos";
		case EDIT_PLAYER_APREENSOES: 		stats_name = "apreensoes";
		case EDIT_PLAYER_CELULAR: 			stats_name = "phone_number";
		case EDIT_PLAYER_MACONHA: 			stats_name = "maconha";
		case EDIT_PLAYER_COCAINA: 			stats_name = "cocaina";
		case EDIT_PLAYER_CRACK: 			stats_name = "crack";
		case EDIT_PLAYER_SKILL_DET: 		stats_name = "skill_detetive";
		case EDIT_PLAYER_SKILL_ADV: 		stats_name = "skill_advogado";
		case EDIT_PLAYER_AVISOS: 			stats_name = "avisos";
		case EDIT_PLAYER_PRISAO_ADM: 		stats_name = "prisao_admin";
		case EDIT_PLAYER_TROCAS_NICK: 		stats_name = "trocas_nick";
		default: return 0;
	}

	new idplayer = GetPlayerID(name);
	if (Player_Logado(idplayer)) {
		switch (stats) {
			case EDIT_PLAYER_LEVEL: 			Player_SetNivel(idplayer, value);
			case EDIT_PLAYER_RESPEITO: 			PlayerInfo[idplayer][pExp] = value;
			case EDIT_PLAYER_HORAS_JOGADAS: 	PlayerInfo[idplayer][pConnectTime] = value;
			case EDIT_PLAYER_DINHEIRO: 			Player_SetMoney(idplayer, value);
			case EDIT_PLAYER_DINHEIRO_BANCO: 	Player_SetMoneyBank(idplayer, value);
			case EDIT_PLAYER_OUROS: 			Player_SetOuros(idplayer, value);
			case EDIT_PLAYER_CASH: 				Player_SetCash(idplayer, value);
			case EDIT_PLAYER_VIPNIVEL: 			Player_SetVIP(idplayer, value);
			case EDIT_PLAYER_KILL: 				PlayerInfo[idplayer][pKills] = value;
			case EDIT_PLAYER_MORTES: 			PlayerInfo[idplayer][pDeaths] = value;
			case EDIT_PLAYER_SKIN: 				Player_SetSkin(idplayer, value);
			case EDIT_PLAYER_SEX: 				PlayerInfo[idplayer][pSex] = value;
			case EDIT_PLAYER_CONTRATOS: 		PlayerInfo[idplayer][pContratos] = value;
			case EDIT_PLAYER_APREENSOES: 		PlayerInfo[idplayer][pMinhasApreensoes] = value;
			case EDIT_PLAYER_CELULAR: 			PlayerInfo[idplayer][numeroCelular] = value;
			case EDIT_PLAYER_MACONHA: 			PlayerInfo[idplayer][pDrogas] = value;
			case EDIT_PLAYER_COCAINA: 			PlayerInfo[idplayer][pDrogas2] = value;
			case EDIT_PLAYER_CRACK: 			PlayerInfo[idplayer][pDrogas3] = value;
			case EDIT_PLAYER_SKILL_DET: 		PlayerInfo[idplayer][pDetSkill] = value;
			case EDIT_PLAYER_SKILL_ADV: 		PlayerInfo[idplayer][pAdvogadoSkill] = value;
			case EDIT_PLAYER_AVISOS: 			PlayerInfo[idplayer][pWarns] = value;
			case EDIT_PLAYER_PRISAO_ADM: 		PlayerInfo[idplayer][pPrisaoAdmin] = value;
			case EDIT_PLAYER_TROCAS_NICK: 		PlayerInfo[idplayer][pTrocaNick] = value;
			default: return 0;
		}
		UpdatePlayerInfos(idplayer);
	} else {
		new const query_selectPlayerName[] = 
			"SELECT id, nome, level, respeitos, horas_jogadas, dinheiro, dinheiro_banco, ouros, cash, vip_nivel, assassinatos, mortes, skin, sexo, contratos, apreensoes, phone_number, 	\
			maconha, cocaina, crack, skill_detetive, skill_advogado, avisos, prisao_admin, trocas_nick FROM `player` WHERE `nome` = ? LIMIT 1"
		;
		new Statement:stmt_selectPlayerName = MySQL_PrepareStatement(MySQL_Handle, query_selectPlayerName);

		inline const OnDbSelect_PlayerName() {
			new idgplayer;

			MySQL_BindResultInt(stmt_selectPlayerName, 0, idgplayer);

			if (!MySQL_Statement_FetchRow(stmt_selectPlayerName))
				return 0;

			MySQL_Bind(stmt_updatePlayerStats, 0, stats_name, true);
			MySQL_BindInt(stmt_updatePlayerStats, 1, value);
			MySQL_BindInt(stmt_updatePlayerStats, 2, idgplayer);
			MySQL_ExecuteParallel(stmt_updatePlayerStats);
			MySQL_StatementClose(stmt_selectPlayerName);
		}
		MySQL_Bind(stmt_selectPlayerName, 0, name);
		MySQL_ExecuteParallel_Inline(stmt_selectPlayerName, using inline OnDbSelect_PlayerName);
	}

	new string[128],
		username[DCC_USERNAME_SIZE];
	
	if (user != DCC_INVALID_USER)
		DCC_GetUserName(user, username);
	else
		format(username, MAX_PLAYER_NAME, PlayerName[playerid]);

	if (Player_Logado(idplayer)) {
		format(string, sizeof(string), "Você teve '%s' ajustado para %s por %s pelo %s.", stats_name, getFormatText(value), username, (user != DCC_INVALID_USER) ? "DISCORD" : "GAME");
		SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);
	}

	format(string, sizeof(string), "AdmAviso: %s ajustou o RG de %s status '%s' para: %s pelo %s.", username, name, stats_name, getFormatText(value), (user != DCC_INVALID_USER) ? "DISCORD" : "GAME");
	Staff_ChatToAll(COLOR_LIGHTRED, string);

	ServerLog::("editar", "[EDITAR] %s editou %s status: %s valor: %s. (%s)", username, name, stats_name, getFormatText(value), (user != DCC_INVALID_USER) ? "DISCORD" : "GAME");
	return 1;
}

new HospId				[MAX_PLAYERS];
new cEmprego[MAX_PLAYERS];
stock EmpregoMensagem(COLOR, const string[], emprego)
{
	foreach(new i: Player) {
	    if (!cEmprego[i]) continue;

		if (PlayerInfo[i][pEmprego] == emprego || PlayerInfo[i][pEmprego2] == emprego) 
            SendClientMessage(i, COLOR, string);
	}
	return true;
}

CALLBACK: SetPlayerToTeamColor(playerid)
{
	if ((Admin_GetNivel(playerid) < DONO && Staff_GetWorking(playerid)) && !Staff_GetSecret(playerid)) 
		return SetPlayerColor(playerid, COLOR_ADMIN);

	if (Helper_GetNivel(playerid) && Staff_GetWorking(playerid))
		return SetPlayerColor(playerid, COLOR_HELPER);

	switch (GetPlayerOrg(playerid)) {

		case 1: if( OnDuty[playerid] == 1 ) { SetPlayerColor(playerid, 0x605DFFAA); } else { SetPlayerColor(playerid, 0xFFFFFFAA); }
		case 2: if( OnDuty[playerid] == 1 ) { SetPlayerColor(playerid, 0x737373AA); } else { SetPlayerColor(playerid, 0xFFFFFFAA); }
		case 3: if( OnDuty[playerid] == 1 ) { SetPlayerColor(playerid, 0x00660CAA); } else { SetPlayerColor(playerid, 0xFFFFFFAA); }
		case 4:SetPlayerColor(playerid, 0xEA8282AA);
		case 5:SetPlayerColor(playerid, 0x2641FEAA);
		case 6:SetPlayerColor(playerid, 0xF09F50AA);
	    case 7:SetPlayerColor(playerid, 0x0095FFAA);
		case 8:SetPlayerColor(playerid, 0xBDBDBDAA);
		case 9:SetPlayerColor(playerid, 0xDFB77BAA);
	    case 10:SetPlayerColor(playerid, 0x61A1AFAA);
		case 11: if( OnDuty[playerid] == 1 ) { SetPlayerColor(playerid, 0x917662AA); } else { SetPlayerColor(playerid, 0xFFFFFFAA); }
		case 12:SetPlayerColor(playerid, 0xD85300AA);
		case 13:SetPlayerColor(playerid, 0x18C09FAA);
		case 14:SetPlayerColor(playerid, 0x177517AA);
		case 15:SetPlayerColor(playerid, 0x571E1EAA);
		case 16: if( OnDuty[playerid] == 1 ) { SetPlayerColor(playerid, 0xFFFF44AA); } else { SetPlayerColor(playerid, 0xFFFFFFAA); }
		case 17:SetPlayerColor(playerid, 0x99311EAA);
		case 18:SetPlayerColor(playerid, 0x010701AA);
		case 19:SetPlayerColor(playerid, 0xF80505AA);
		case 20:SetPlayerColor(playerid, 0xEE2323AA);
		case 21:SetPlayerColor(playerid, 0x7F994CAA);
		case 22:SetPlayerColor(playerid, 0xA4D1FFAA);
	 	case 23:SetPlayerColor(playerid, 0x024566AA);
	 	case 24:SetPlayerColor(playerid, 0x33FFFFAA);
		case 25:SetPlayerColor(playerid, 0x576176AA);
		case 26:SetPlayerColor(playerid, 0xFFFF99AA);
		case 27:SetPlayerColor(playerid, 0xCC0066AA);
		case 28:SetPlayerColor(playerid, 0xA3283DAA);
		case 29: if( OnDuty[playerid] == 1 ) { SetPlayerColor(playerid, 0x3A3939AA); } else { SetPlayerColor(playerid, 0xFFFFFFAA); }
		case 30:SetPlayerColor(playerid, 0xEE4000AA);
		case 32:SetPlayerColor(playerid, 0xFF9900AA);
		case 33: if( OnDuty[playerid] == 1 ) { SetPlayerColor(playerid, 0x996600AA); } else { SetPlayerColor(playerid, 0xFFFFFFAA); }
		case 34: if( OnDuty[playerid] == 1 ) { SetPlayerColor(playerid, 0x333300AA); } else { SetPlayerColor(playerid, 0xFFFFFFAA); }
		default:
		{
			#if _inc_speakers_system
				if (Speaker_GetNivel(playerid)) 
					return SetPlayerColor(playerid, COLOR_SPEAKER);
			#endif
			SetPlayerColor(playerid, 0xFFFFFFAA);
		}
	}
	return false;
}

stock GetPlayerColorEx(playerid)
{
	new color[15];
    if (Staff_GetWorking(playerid) && !Staff_GetSecret(playerid))
	{
		if (Admin_GetNivel(playerid))
			color = "FF66BE";

		else if (Helper_GetNivel(playerid))
			color = "55F6AC";

		return color;
	}

	switch(GetPlayerOrg(playerid))
	{
		case 1:color = "605DFF";
		case 2:color = "737373";
		case 3:color = "00660C";
		case 4:color = "EA8282";
		case 5:color = "2641FE";
		case 6:color = "F09F50";
	    case 7:color = "0095FF";
		case 8:color = "BDBDBD";
		case 9:color = "DFB77B";
	    case 10:color = "61A1AF";
		case 11:color = "917662";
		case 12:color = "D85300";
		case 13:color = "18C09F";
		case 14:color = "177517";
		case 15:color = "571E1E";
		case 16:color = "FFFF44";
		case 17:color = "99311E";
		case 18:color = "010701";
		case 19:color = "F80505";
		case 20:color = "EE2323";
		case 21:color = "7F994C";
		case 22:color = "A4D1FF";
	 	case 23:color = "024566";
	 	case 24:color = "33FFFF";
		case 25:color = "576176";
		case 26:color = "FFFF99";
		case 27:color = "CC0066";
		case 28:color = "A3283D";
		case 29:color = "3A3939";
		case 30:color = "EE4000";
		case 32:color = "FF9900";
		case 33:color = "996600";
		case 34:color = "333300";
		default:color = "FFFFFF";
	}
	return color;
}

new bool: playerBolsaFamilia[MAX_PLAYERS];
new Float:irReforco[MAX_ORGS][4];

stock IsPlayerHaveRespect(playerid)
{
	if (PlayerInfo[playerid][pExp] >= ((PlayerInfo[playerid][pLevel] + 1) * 8)) 
		return true;

	return false;
}

// Resetar todas as variaveis
CALLBACK: OnPlayerResetVars(playerid)
{
	static const	empty_cars[pVehicleEnum],
					empty_attached[accessorieEnum],
					empty_player[E_PLAYER],
					empty_jailed[JAIL_enum],
					empty_bodypartbusy[Bodypart],
					empty_inventory[INVENTORY_ENUM];

	PlayerInfo[playerid] = empty_player;
	BodyPartBusy[playerid] = empty_bodypartbusy;
	JailInfo = empty_jailed;

	for(new car; car < MAX_PLAYER_CARROS; car++)
		PlayerVehicleInfo[playerid][car] = empty_cars;

	for(new index; index != MAX_PLAYER_ATTACHED_OBJECTS; index++)
		accessoriesInfo[playerid][index] = empty_attached;

	for(new slot; slot != MAX_ITENS_INVENTARIO; slot++)
		InventarioInfo[playerid][slot] = empty_inventory;

	Player_SetPaletteColor(playerid, -1, -1, -1);

	SetPVarString(playerid, "NomeLocal", "Nenhum");

	// Modo tv administrativo
	SpectadorInfo[playerid][spectadorID] 				= INVALID_PLAYER_ID;

	SetPVarInt(playerid, "varProcura", INVALID_PLAYER_ID);
	SetPVarInt(playerid, "objectProcurar", -1);

	SetPlayerSeeNick(playerid, true);
	SetPlayerBeingAbducted(playerid, false);

	//bools
	PlayerInfo[playerid][pInventoryLoaded]				= false;
	ChatKill[playerid] 									= true;
	InTaser[playerid] 									= false;
	SkateInfo[playerid][s_Setado] 						= false;
	DanoInfo[playerid][danoKilled] 						= false;
	atendimentoFarmacia[playerid] 						= false;      	// Atendimento do farmaceutico
	atendimentoPolicial[playerid] 						= false;      	// Atendimento do COPOM
	//pegandoFogo[playerid] 								= false;     	// Jogador pegando fogo
	wallAdmin[playerid]                                 = false;        // Wall-Hack administrativo

	// Atendimento (ligar 190)
	OcorrenciaInfo[playerid][ocorrenciaValid]			= false;
	OcorrenciaInfo[playerid][ocorrenciaID] 				= INVALID_PLAYER_ID;
	OcorrenciaInfo[playerid][ocorrenciaTempo] 			= 0;

	AdvogadoInfo[playerid][advogadoID]					= INVALID_PLAYER_ID;
	AdvogadoInfo[playerid][porcentPrisao]               = 0;
	AdvogadoInfo[playerid][precoAdvogado]               = 0;

	playerBolsaFamilia[playerid]		 				= false;

	//PVars
	SetPVarInt(playerid, "quantLixosPegou", 			0);
	SetPVarInt(playerid, "pegouLixo", 					0);
	SetPVarInt(playerid, "emColetaLixo", 				0);
	SetPVarInt(playerid, "acordoID", 					999);
	SetPVarInt(playerid, "EntregaPizza", 				0);
	SetPVarInt(playerid, "VarMSG", 						0);
	SetPVarInt(playerid, "varTeamViewer", 				0);
 	SetPVarInt(playerid, "playerInTrashCan", 			0);
	SetPVarInt(playerid, "playerTrashCanID", 			-1);
	SetPVarInt(playerid, "ConviteComparsa", 			-1);
	SetPVarInt(playerid, "Comparsa", 			-1);
	SetPVarInt(playerid, "gPlayerHitMark_DB",      		1);
	SetPVarInt(playerid, "reanimando", 					INVALID_PLAYER_ID);
	SetPVarInt(playerid, "timerEquip",					-1);
	SetPVarInt(playerid, "timer_playerAFK", 				-1);

	for(new i; i < MAX_PLAYERS; i++)
	{
		if (GetPVarInt(i, "ofertaMateriais_ID") == playerid)
		    SetPVarInt(i, "ofertaMateriais_ID", INVALID_PLAYER_ID);
	}

	SetPVarInt(playerid, "playerStoreSelected", -1);
	SetPVarInt(playerid, "familyAcc", -1);

	Propertie_SetLastPickup(playerid, 0);
	JoinedHay[playerid] 								= false;
	cEmprego[playerid] 									= 1;
    patinss[playerid] 									= 0;

	Inventory_SetPage(playerid, 0);
    PrisionVoiceTimer[playerid] 								= -1;
	eEjet[playerid] 									= -1;
	InTeste[playerid] 									= 0;
	pCofreOrg[playerid] 								= 0;
	InviteOffer[playerid] 								= 999;
	InviteJob[playerid] 								= 0;
    VozDePrisao[playerid] 								= 0;
	timerESC[playerid] 									= 0;
	PhoneOnline[playerid] 								= 0;
	GettingEmprego[playerid]	 						= 0;
	TalkingLive[playerid]								= 255;
	LiveOffer[playerid] 								= 999;
	valorLiveOffer[playerid] 							= 0;
	DrugOffer[playerid] 								= 999;
	DrugPrice[playerid] 								= 0;
	DrugGram[playerid] 									= 0;
	GotHit[playerid] 									= 0;
	GotTri[playerid] 									= 0;
	GoChase[playerid] 									= INVALID_PLAYER_ID;
	GetChased[playerid] 								= INVALID_PLAYER_ID;
	OnDuty[playerid] 									= 0;
	EmpregoDuty[playerid] 								= 0;
	gNoticias[playerid] 								= 0;
	BigEar[playerid] 									= 0;
	gDice[playerid] 									= 0;
	Chat_Organizacao[playerid] 							= 0;
	TicketOffer[playerid] 								= 999;
	TicketMoney[playerid] 								= 0;
	ProposeOffer[playerid] 								= 999;
	MarryWitness[playerid]								= 999;
	MarryWitnessOffer[playerid] 						= 999;
	MarriageCeremoney[playerid] 						= 0;
	ProposedTo[playerid] 								= 999;
	GotProposedBy[playerid] 							= 999;
	DivorceOffer[playerid] 								= 999;
	HospId[playerid] = 999;
	MobileInfo[playerid][mobileCall] 					= MAX_PLAYERS + 5;

	PlayerCaminhao[playerid][caminhaoValid] = false;
	PlayerCaminhao[playerid][caminhaoId] = INVALID_VEHICLE_ID;
	PlayerInfo[playerid][pFamily] = -1;

	// Conquistas
	ResetConquistas(playerid);

	// Resetar crime e casamento
	ClearCrime(playerid);
	ClearMarriage(playerid);

	resetPlayerLastKill(playerid);

	// Hitmarks
	resetPlayerHitMarks(playerid);

	playerResetTrade(playerid);
}

#include <player_update>

CMD:aceitar(playerid, const x_Emprego[])
{
	if(isnull(x_Emprego))
	{
		SendClientMessage(playerid, -1, "|__________________[ Aceitar ]__________________|");
		SendClientMessage(playerid, -1, "Use: aceitar [nome]");
		SendClientMessage(playerid, -1, "Nomes válidos: [convite, aovivo, assalto, reforco, beijo, divorcio, cliente]");
		SendClientMessage(playerid, -1, "Nomes válidos: [reparo, abastecimento, sexo]");
		return true;
	}
	//new para1;
	new string[128];
	if (strcmp(x_Emprego,"convite",true) == 0) {

		if (InviteOffer[playerid] < 999) {

			if (gettime() > GetPVarInt(playerid, "varConvite")) 
				return SendClientMessage(playerid, -1, "O convite expirou!");

			if (!Player_Logado(InviteOffer[playerid])) {
				return SendClientMessage(playerid, -1, "O jogador que te convidou não está mais conectado.");
			}

			new idorg = InviteJob[playerid];

			if (!GetSlotsInOrg(idorg)) {
				return SendClientMessage(playerid, COLOR_WHITE, "A organização está sem vagas.");
			}

			SetPlayerMember(playerid, idorg);
			SpawnPlayer(playerid);

			format(string, sizeof(string), "* Você foi convidado por %s para entrar para a org: %s, parabéns.", PlayerName[InviteOffer[playerid]], NomeORG(InviteOffer[playerid]));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

			#if defined _CONQUEST_SYSTEM_ON
				CheckConquista(playerid, Conquista_Organizacao);
			#endif

			SetPlayerToTeamColor(playerid);

			format(string, sizeof string, "* %s aceitou o seu convite para entrar para a organização!", PlayerName[playerid]);
			SendClientMessage(InviteOffer[playerid], COLOR_LIGHTBLUE, string);
			
		} else {
			return SendClientMessage(playerid, -1, "Você não foi convidado para nenhuma organização.");
		}
	}

	else if(strcmp(x_Emprego,"assalto",true) == 0)
	{
		if(GetPVarInt(playerid, "assaltado"))
		{
			new assaltante = GetPVarInt(playerid, "assaltante"), comparsa = GetPVarInt(assaltante, "Comparsa");
			if(IsPlayerConnected(assaltante))
			{
				if (ProxDetectorS(5.0, playerid, assaltante))
				{
					new valor = Player_GetMoney(playerid) / 2;
					format(string, sizeof(string), "* Você aceitou um assalto de %s e perdeu $%s", PlayerName[assaltante], getFormatText(Player_GetMoney(playerid)));
					SendClientMessage(playerid, COLOR_GRAD, string);
					format(string, sizeof(string), "* %s aceitou seu assalto e você recebeu $%s.", PlayerName[playerid], getFormatText(valor));
					SendClientMessage(assaltante, COLOR_LIGHTBLUE, string);
					Player_AddMoney(assaltante, valor);
					Player_AddMoney(comparsa, valor);
					Player_RemoveMoney(playerid, Player_GetMoney(playerid));
					SetPlayerCriminal(assaltante, 255, "Assalto", 5);
					SetPVarInt(playerid, "assaltado", 0);
					return 1;
				}
				else
				{
					SendClientMessage(playerid, -1, "O assaltante está longe de você!");
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, -1, "O Assaltante não está mais conectado!");
				SetPVarInt(playerid, "assaltado", 0);
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, -1, "Você não foi assaltado!");
			return 1;
		}
	}
	else if(strcmp(x_Emprego,"reforco",true) == 0)
	{
		if(GetPlayerOrg(playerid))
		{
			if(gettime() < irReforco[GetPlayerOrg(playerid)][3])
			{
				format(string, sizeof(string), "* %s aceitou o reforço!", PlayerName[playerid]);
				SendMembersMessage(GetPlayerOrg(playerid), GetPlayerColor(playerid), string);
				SendClientMessage(playerid, COLOR_GREY, "   Você aceitou o reforço, siga a marca vermelha em seu mapa!");

				new org = GetPlayerOrg(playerid);
				SetPlayerCP(playerid, 76);
				SetPlayerCheckpoint(playerid, irReforco[org][0], irReforco[org][1], irReforco[org][2], 10.0);
				GameTextForPlayer(playerid, "~r~Voce aceitou o reforco!", 5000, 1);
			}
			else
			{
				SendClientMessage(playerid, -1, "O tempo para aceitar o reforço ja se esgotou!");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, -1, "Você não participa de uma organização!");
			return 1;
		}
	}
	else if(strcmp(x_Emprego,"divorcio",true) == 0)
	{
		if(DivorceOffer[playerid] < 999)
		{
			if(IsPlayerConnected(DivorceOffer[playerid]))
			{
				if(ProxDetectorS(10.0, playerid, DivorceOffer[playerid]))
				{
					format(string, sizeof(string), "* Voce aceitou o pedido de %s para ser testemunha de seu divorcio.", PlayerName[DivorceOffer[playerid]]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					format(string, sizeof(string), "* %s aceitou o seu pedido para ser testemunha do seu divorcio.", PlayerName[playerid]);
					SendClientMessage(DivorceOffer[playerid], COLOR_LIGHTBLUE, string);
					ClearMarriage(playerid);
					ClearMarriage(DivorceOffer[playerid]);
					return true;
				}
				else
				{
					SendClientMessage(playerid, -1, "O jogador que te enviou os papéis do divórcio não está perto de você!");
					return true;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, -1, "Ninguem te enviou qualquer papel de divórcio!");
			return true;
		}
	}
	else if(strcmp(x_Emprego,"comparsa",true) == 0)
	{
		new comparsa = GetPVarInt(playerid, "ConviteComparsa");
		if(comparsa > -1)
		{
			if(IsPlayerConnected(comparsa))
			{
				SendMsgF(comparsa, COLOR_LIGHTBLUE, "%s aceitou o convite para ser seu comparsa.", PlayerName[playerid]);
				SendMsgF(playerid, COLOR_LIGHTBLUE, "Você aceitou o convite para ser comparsa de %s.", PlayerName[comparsa]);
				SetPVarInt(playerid, "Comparsa", comparsa);
				SetPVarInt(comparsa, "Comparsa", playerid);
				return true;
			}
		}
		else
		{
			SendClientMessage(playerid, -1, "Ninguém convidou você para ser comparsa!");
			return true;
		}
	}
	else if(strcmp(x_Emprego,"padrinho",true) == 0)
	{
		if(MarryWitnessOffer[playerid] < 999)
		{
			if(IsPlayerConnected(MarryWitnessOffer[playerid]))
			{
				if(ProxDetectorS(10.0, playerid, MarryWitnessOffer[playerid]))
				{
					format(string, sizeof(string), "* Você aceitou o pedido de %s para ser padrinho de seu casamento.", PlayerName[MarryWitnessOffer[playerid]]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					format(string, sizeof(string), "* %s aceitou o seu pedido para ser padrinho do seu casamento.", PlayerName[playerid]);
					SendClientMessage(MarryWitnessOffer[playerid], COLOR_LIGHTBLUE, string);
					MarryWitness[MarryWitnessOffer[playerid]] = playerid;
					MarryWitnessOffer[playerid] = 999;
					return true;
				}
				else
				{
					SendClientMessage(playerid, -1, "O jogador que pediu para ser padrinho de seu casamento não está perto de você!");
					return true;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, -1, "Ninguem pediu para ser padrinho de seu casamento!");
			return true;
		}
	}
	else if(strcmp(x_Emprego,"casamento",true) == 0)
	{
		if(ProposeOffer[playerid] < 999)
		{
			if(!PlayerToPoint(10.0, playerid, -1077.9645,713.4493,630.0579))
			{
				SendClientMessage(playerid, -1, "Você não está na igreja de Los Santos !");
				return true;
			}
			if(IsPlayerConnected(ProposeOffer[playerid]))
			{
				if(ProxDetectorS(10.0, playerid, ProposeOffer[playerid]))
				{
					if(MarryWitness[ProposeOffer[playerid]] == 999)
					{
						SendClientMessage(playerid, -1, "O jogador não possui um padrinho de casamento!");
						return true;
					}
					if(IsPlayerConnected(MarryWitness[ProposeOffer[playerid]]))
					{
						if(ProxDetectorS(12.0, ProposeOffer[playerid], MarryWitness[ProposeOffer[playerid]]))
						{
							format(string, sizeof(string), "* Voce aceitou o pedido de %s para ser seu marido.", PlayerName[ProposeOffer[playerid]]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
							format(string, sizeof(string), "* %s aceitou o seu pedido para ser sua esposa.", PlayerName[playerid]);
							SendClientMessage(ProposeOffer[playerid], COLOR_LIGHTBLUE, string);
							format(string, sizeof(string), "Padre: %s voce aceita %s como seu legitimo marido? (use 'sim', qualquer outra coisa cancela o casamento)", PlayerName[playerid], PlayerName[ProposeOffer[playerid]]);
							SendClientMessage(playerid, -1, string);
							MarriageCeremoney[playerid] = 1;
							ProposedTo[ProposeOffer[playerid]] = playerid;
							GotProposedBy[playerid] = ProposeOffer[playerid];
							MarryWitness[ProposeOffer[playerid]] = 999;
							ProposeOffer[playerid] = 999;
							return true;
						}
						else
						{
							SendClientMessage(playerid, -1, "O padrinho de casamento nao esta perto de sua noiva/noivo!");
							return true;
						}
					}
					return true;
				}
				else
				{
					SendClientMessage(playerid, -1, "O jogador não esta perto de você!");
					return true;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, -1, "Ninguem te fez uma proposta!");
			return true;
		}
	}
	else if(strcmp(x_Emprego,"sexo",true) == 0)
	{
		if(DoSexOffer[playerid] < 999)
		{
			if(!PlayerToPoint(10.0, playerid, 2217.3367,-1146.8258,1025.7969))
				return SendClientMessage(playerid, -1, "Você não está dentro do Motel !");

			if(IsPlayerConnected(DoSexOffer[playerid]))
			{
				if(ProxDetectorS(10.0, playerid, DoSexOffer[playerid]))
				{
					if(ProxDetectorS(12.0, playerid, DoSexOffer[playerid]))
					{
						new salaprivada = random(99999) + 1;

						format(string, sizeof(string), "* Você aceitou o pedido de %s para fazer sexo.", PlayerName[DoSexOffer[playerid]]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						format(string, sizeof(string), "* %s aceitou o seu pedido para fazer sexo.", PlayerName[playerid]);
						SendClientMessage(DoSexOffer[playerid], COLOR_LIGHTBLUE, string);


						TogglePlayerControllable(DoSexOffer[playerid], false);
						TogglePlayerControllable(playerid, false);

						SetPlayerPos(DoSexOffer[playerid], 2197.8140,-1176.2260,1029.8043);
						SetPlayerVirtualWorld(DoSexOffer[playerid], salaprivada);

						SetPlayerPos(playerid, 2198.7393,-1176.0931,1029.8043);
						SetPlayerVirtualWorld(playerid, salaprivada);

						ApplyAnimation(DoSexOffer[playerid], "PAULNMAC", "wank_loop", 4.1, false, true, true, false, 0, SYNC_ALL);
    					ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 3.1, false, true, true, false, 0);

						// Boquete --- Sexo (Tempo)
						SetTimerEx("MasturbarSexo", 3000, false, "i", DoSexOffer[playerid]);
    					SetTimerEx("BoqueteSexo", 3000, false, "i", playerid);

						// Cama --- Sexo (Tempo)
						//SetTimerEx("CamaSexo1", 30000, false, "i", DoSexOffer[playerid]);
						//SetTimerEx("CamaSexo2", 30000, false, "i", playerid);

						return true;
					}
					else
					{
						SendClientMessage(playerid, -1, "O jogador que propôs sexo não está perto.");
						return true;
					}
				}
				return true;
			}
			else
			{
				SendClientMessage(playerid, -1, "O jogador não esta perto de você!");
				return true;
			}
		}
	}
	else if(strcmp(x_Emprego,"multa",true) == 0)
	{
		if(TicketOffer[playerid] < 999)
		{
			if(IsPlayerConnected(TicketOffer[playerid]))
			{
				if (ProxDetectorS(5.0, playerid, TicketOffer[playerid]))
				{

					if(Player_GetMoney(playerid) < TicketMoney[playerid])
						return SendClientMessage(playerid, -1, "Você não possui essa grana !");

					format(string, sizeof(string), "* Você pagou a multa de $%d para o Oficial %s.", TicketMoney[playerid], PlayerName[TicketOffer[playerid]]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					format(string, sizeof(string), "* %s pagou a multa de $%d.", PlayerName[playerid], TicketMoney[playerid]);
					SendClientMessage(TicketOffer[playerid], COLOR_LIGHTBLUE, string);

					new idplayer = TicketOffer[playerid];
					Player_RemoveMoney(playerid, TicketMoney[playerid]);
					Player_AddMoney(idplayer, TicketMoney[playerid]);
					TicketOffer[playerid] = 999;
					TicketMoney[playerid] = 0;
					return true;
				}
				else
				{
					SendClientMessage(playerid, -1, "O policial não está perto de você !");
					return true;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, -1, "Ninguem lhe deu uma multa !");
			return true;
		}
	}
	else if(strcmp(x_Emprego,"acordo",true) == 0)
	{
		According_Accept(playerid);
	}
	else if(strcmp(x_Emprego,"aovivo",true) == 0)
	{
		if (!IsPlayerConnected(LiveOffer[playerid])) return 0;

		if (LiveOffer[playerid] == 999) return SendClientMessage(playerid, -1, "Você não foi chamado para uma conversa aovivo.");

		if (!ProxDetectorS(5.0, playerid, LiveOffer[playerid])) return SendClientMessage(playerid, -1, "Você precisa estar perto do reporter que lhe chamou.");

		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você aceitou conversar aovivo na San News.");

		format(string, sizeof(string), "* %s aceitou a conversa aovivo, e foi adicionado $%s no cofre da organização.", PlayerName[playerid], getFormatText(valorLiveOffer[playerid]));
		SendClientMessage(LiveOffer[playerid], COLOR_LIGHTBLUE, string);

		TalkingLive[playerid] = LiveOffer[playerid];
		TalkingLive[LiveOffer[playerid]] = playerid;
		LiveOffer[playerid] = 999;

		Player_RemoveMoney(playerid, valorLiveOffer[playerid]);
		OrgInfo_SetMoney(ID_ORG_SANNEWS, OrgInfo_GetMoney(ID_ORG_SANNEWS) + valorLiveOffer[playerid]);
		valorLiveOffer[playerid] = 0;

		return true;
	}
	else if(strcmp(x_Emprego,"abastecimento",true) == 0)
	{
		AceitarOfertaMecanico(playerid, 1);
		return true;
	}
	else if(strcmp(x_Emprego,"reparo",true) == 0)
	{
		AceitarOfertaMecanico(playerid, 2);
		return true;
	}
	return true;
}

CALLBACK: PagarPayday(i)
{
	if (!Player_Logado(i)) 
		return true;

	new porcentJuros, respect, restamRespeitos = (PlayerInfo[i][pLevel] + 1) * 8, bancoFiliado = PlayerInfo[i][pBancoFiliado];

	switch (PlayerInfo[i][pVIP])
	{
		case 1: 	respect = 1, 		porcentJuros = 1;
		case 2: 	respect = 1, 		porcentJuros = 2;
		case 5: 	respect = 2, 		porcentJuros = 2;
		case 6: 	respect = 3, 		porcentJuros = 3;
		case 7: 	respect = 4, 		porcentJuros = 4;
		case 8: 	respect = 5, 		porcentJuros = 6;
		default: 	respect = 1, 		porcentJuros = 1;
	}

	new interest = porcentJuros * (PlayerInfo[i][pConta]/100000);
	new taxajurosbanco = (interest / 10);

	if (interest < 500) interest = 500;

	PlayerPlaySound(i, 1183, 0.0, 0.0, 0.0);

	new string[128];

	SendClientMessage(i, -1, "____________________________ PayDay (Pagamento) ____________________________");

	format(string, sizeof(string), "Salário do trabalho: {00AA00}$%s {9C9C9C}Enviado para sua conta bancária", getFormatText(PlayerInfo[i][pSalario]));
	SendClientMessage(i, -1, string);

	format(string, sizeof(string), "Impostos do governo: {D95959}-$%s", getFormatText(GovernoTaxa));
	SendClientMessage(i, -1, string);

	format(string, sizeof(string), "Você recebe {5588CF}0,00%d por cento {FFFFFF}de juros do banco. {FFFFFF}Valor recebido: {00AA00}$%s", porcentJuros, getFormatText(interest));
	SendClientMessage(i, -1, string);

	format(string, sizeof(string), "Você pagou 0,0001 por cento {FFFFFF}para o banco. {FFFFFF}Valor pago: {D95959}-$%s", getFormatText(taxajurosbanco));
	SendClientMessage(i, -1, string);

	format(string, sizeof(string), "Respeito: +%d        (Faltam {ECD563}%d respeitos{FFFFFF} para o nível %d)", respect, restamRespeitos-PlayerInfo[i][pExp], PlayerInfo[i][pLevel]+1);
	SendClientMessage(i, -1, string);

	if (PlayerInfo[i][pConta] >= max_money_limit)
	{
	    // Converter dinheiro em ouros quando estiver em excesso...
	    PlayerInfo[i][pConta] -= 100000000;
	    PlayerInfo[i][pOuros] += (100000000/100000);

		format(string, sizeof(string), "%s: Caro %s, convertemos $100.000.000 da sua conta para 1000 ouros por excesso.", Property_GetName(bancoFiliado), PlayerName[i]);
		SendClientMessage(i, -1, string);
	}

	SalarioPlayer(i);

    // Pagar as contas e receber salários
 	PlayerInfo[i][pExp] += respect;

	new salario = Holiday_Get() ? (PlayerInfo[i][pSalario] * 2) : PlayerInfo[i][pSalario];

	PlayerInfo[i][pConta] += (interest + salario);

	PlayerInfo[i][pConta] -= (taxajurosbanco + GovernoTaxa);

	if (bancoFiliado != -1)
		Property_AddMoney(bancoFiliado, taxajurosbanco);

	adicionarDinheiroGoverno(GovernoTaxa);

	SendClientMessage(i, -1, "____________________________________________________________________________");

	format(string, sizeof(string), "Novo saldo bancário: {00AA00}$%s", getFormatText(PlayerInfo[i][pConta]));
	SendClientMessage(i, -1, string);

	format(string, sizeof(string), "Salário: %s recebeu $%s de salário no payday.", PlayerName[i], getFormatText(PlayerInfo[i][pSalario]));
    server_log("salarios", string), PlayerInfo[i][pSalario] = 0;

	defer stopMusic(i);
	PlayerInfo[i][pCaixinha] = false;
	PlayerInfo[i][pLimparb] = 0, PlayerInfo[i][pConnectTime] += 1;

	new query[185];

	mysql_format(MySQL_Handle, query, sizeof query, "UPDATE `player` SET `horas_jogadas` = '%d' WHERE `id` = '%d'", PlayerInfo[i][pConnectTime], PlayerInfo[i][pID]);
	mysql_tquery(MySQL_Handle, query);

	if (PlayerInfo[i][pAutoCaixinha] && PlayerInfo[i][pVIP] > 7) callcmd::caixinha(i), callcmd::caixinha(i);

	return true;
}

CALLBACK:Lotto(number)
{
    new loto_string[128], winsLotto = 0, premioValor;

    format(loto_string, sizeof(loto_string), "[{F9E36C}LOTÉRICA{FFFFFF}]: Sorteio de {F96C6C}Nº %d{FFFFFF}. Foi sorteado o bilhete {00BFFF}%d{FFFFFF}.", SorteioID, number);
	OOCNews(-1, loto_string); SorteioID++;

    foreach(new i : Player)
	{
	    if (PlayerInfo[i][pLottoNr] == number && Player_Logado(i))
		{
		    winsLotto++;
		    premioValor = LotValue/winsLotto;

			format(loto_string, sizeof(loto_string), "[{F9E36C}LOTÉRICA{FFFFFF}]: O bilhete {00BFFF}%d {FFFFFF}de {F96C6C}%s {FFFFFF}foi o vencedor.", PlayerInfo[i][pLottoNr], PlayerName[i]);
			OOCNews(-1, loto_string);

			Player_AddMoney(i, premioValor);
			CheckConquista(i, Conquista_Loteria);

			format(loto_string, sizeof(loto_string), "Loterica: Ganhador %s, nº %d. | Valor: $%s.", PlayerName[i], PlayerInfo[i][pLottoNr], getFormatText(LotValue));
			server_log("loterias", loto_string);
		}

 		PlayerInfo[i][pLottoNr] = 0;
	}

	if (winsLotto > 0)
	{
	    format(loto_string, sizeof(loto_string), "[{F9E36C}LOTÉRICA{FFFFFF}]: Houve {00BFFF}%d {FFFFFF}ganhadores, o prêmio foi dividido.", winsLotto);
		OOCNews(-1, loto_string);
		format(loto_string, sizeof(loto_string), "[{F9E36C}LOTÉRICA{FFFFFF}]: Cada ganhador recebeu {00AA00}$%s {FFFFFF}na sua conta bancária.", getFormatText(premioValor));
		OOCNews(-1, loto_string);

		OrgInfo_SetMoney(ID_ORG_GOVERNO, OrgInfo_GetMoney(ID_ORG_GOVERNO) - LotValue);
		LotValue = 0;
	}
	else
	{
		LotValue += 25000 + random(10000);

	    format(loto_string, sizeof(loto_string), "[{F9E36C}LOTÉRICA{FFFFFF}]: Nenhum ganhador no sorteio, prêmio acumulado em {00AA00}$%s", getFormatText(LotValue));
	    OOCNews(-1, loto_string);
	}

	return true;
}

CALLBACK:PayDay()
{
	foreach(new i : Player) {
		SetPVarInt(i, "varConvite", 0);
	}

	// Cobrança do aluguel
	CallLocalFunction("Houses_ChargeRental", "");

  	new rand = random(99) + 1;
	Lotto(rand);

	resetarAtividadesOrg(); 
	resetarGuerrasPd();

	#if defined _INC_caixa_eletronico
		AbastecerCaixasEletronicos();
	#endif

	SetSVarInt("SpecialBoxAvailable", random(3));
	return true;
}

CMD:meusalario(playerid)
{
    new string[128];

    SendClientMessage(playerid, -1, "____________________________ Extrato do trabalhador ____________________________");

    format(string, sizeof string, "Bem vindo {00BFFF}%s{FFFFFF}, ao seu extrato do salário pelo trabalho prestado...", PlayerName[playerid]);
    SendClientMessage(playerid, -1, string);

    format(string, sizeof string, "Informamos que você tem um saldo de {00AA00}$%s {FFFFFF}para receber em: %s.", getFormatText(PlayerInfo[playerid][pSalario]), ConvertTime(PlayerInfo[playerid][pPayDay]));
   	SendClientMessage(playerid, -1, string);

	if (Holiday_Get()) {
		SendMsgF(playerid, COLOR_MONEY, "Bônus salário: "C_LIGHTWHITE"Hoje o servidor está pagando o salário em dobro no PayDay por conta do feriado!");
	}

   	SendClientMessage(playerid, -1, "Você poderá recebe-lo em qualquer pagamento horário que tiver...");

   	SendClientMessage(playerid, -1, "________________________________________________________________________________");

	return true;
}

// ------------------- Sistema de Sexo by: Joao Revolts --------------------
CMD:convidarsexo(playerid, params[]) 
{
	new idplayer;

	if(!PlayerToPoint(10.0, playerid, 2217.3367,-1146.8258,1025.7969))
		return SendClientMessage(playerid, -1, "Você não está no Motel.");

	if (PlayerToPoint(1, playerid, 2217.3367,-1146.8258,1025.7969))
	{
		if (IsPlayerInCombat(playerid))
			return SendClientMessage(playerid, -1, "Você está em combate, por isso não pode pedir sexo.");

		if (sscanf(params, "d", idplayer)) 
			return SendClientMessage(playerid, -1, "Modo de uso: /convidarsexo (id do jogador)");

		if (IsPlayerInCombat(idplayer))
			return SendClientMessage(playerid, -1, "O jogador está em combate, por isso não pode responder.");

		if (!IsPlayerConnected(idplayer))
			return SendClientMessage(playerid, COLOR_GRAD, "O jogador não está conectado.");
		
		if (!Player_Logado(idplayer))
			return SendClientMessage(playerid, -1, "O jogador convidado não está logado.");
		
		new string[128];

		if (ProxDetectorS(8.0, playerid, idplayer))
		{
			if (idplayer == playerid)
				return SendClientMessage(playerid, -1, "Você não pode pedir sexo a você mesmo.");
			
			format(string, sizeof(string), "* Você pediu sexo a %s.", PlayerName[idplayer]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			format(string, sizeof(string), "* %s está pedindo para fazer sexo com você (Digite /aceitarsexo) para aceitar.", PlayerName[playerid]);
			SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);
			DoSexOffer[idplayer] = playerid;
		}
		else {
			return SendClientMessage(playerid, -1, "O jogador não está perto de você.");
		}
	}
	else {
		return SendClientMessage(playerid, -1, "Você não está no sitio de pedir sexo.");
	}

	return 1;
}

forward MasturbarSexo(playerid);
forward MasturbarSexo2(playerid);
forward MasturbarSexo3(playerid);
forward MasturbarSexo4(playerid);
forward MasturbarSexo5(playerid);
forward MasturbarSexo6(playerid);
forward BoqueteSexo(playerid);
forward BoqueteSexo2(playerid);
forward BoqueteSexo3(playerid);
forward BoqueteSexo4(playerid);
forward BoqueteSexo5(playerid);
forward BoqueteSexo6(playerid);
forward CamaSexo1(playerid);
forward CamaSexo2(playerid);
forward TerminarSexo(playerid);

// Função para aplicar a animação de "wank_loop" a cada intervalo no jogador alvo
public MasturbarSexo(playerid)
{
    ApplyAnimation(DoSexOffer[playerid], "PAULNMAC", "wank_loop", 4.1, false, true, true, false, 0, SYNC_ALL);
	SetTimerEx("MasturbarSexo2", 3000, false, "i", playerid);
	//SetTimerEx("CamaSexo1", 30000, false, "i", playerid);
}

public MasturbarSexo2(playerid)
{
    ApplyAnimation(DoSexOffer[playerid], "PAULNMAC", "wank_loop", 4.1, false, true, true, false, 0, SYNC_ALL);
	SetTimerEx("MasturbarSexo3", 3000, false, "i", playerid);
	//SetTimerEx("CamaSexo1", 30000, false, "i", playerid);
}

public MasturbarSexo3(playerid)
{
    ApplyAnimation(DoSexOffer[playerid], "PAULNMAC", "wank_loop", 4.1, false, true, true, false, 0, SYNC_ALL);
	SetTimerEx("MasturbarSexo4", 3000, false, "i", playerid);
	//SetTimerEx("CamaSexo1", 30000, false, "i", playerid);
}

public MasturbarSexo4(playerid)
{
    ApplyAnimation(DoSexOffer[playerid], "PAULNMAC", "wank_loop", 4.1, false, true, true, false, 0, SYNC_ALL);
	SetTimerEx("MasturbarSexo5", 3000, false, "i", playerid);
	//SetTimerEx("CamaSexo1", 30000, false, "i", playerid);
}

public MasturbarSexo5(playerid)
{
    ApplyAnimation(DoSexOffer[playerid], "PAULNMAC", "wank_loop", 4.1, false, true, true, false, 0, SYNC_ALL);
	SetTimerEx("MasturbarSexo6", 3000, false, "i", playerid);
	//SetTimerEx("CamaSexo1", 30000, false, "i", playerid);
}

public MasturbarSexo6(playerid)
{
    ApplyAnimation(DoSexOffer[playerid], "PAULNMAC", "wank_loop", 4.1, false, true, true, false, 0, SYNC_ALL);
	SetTimerEx("CamaSexo1", 30000, false, "i", playerid);
}

// Função para aplicar a animação de "BJ_COUCH_LOOP_W" a cada intervalo no jogador que aceitou
public BoqueteSexo(playerid)
{
    ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 3.1, false, true, true, false, 0);
	SetTimerEx("BoqueteSexo2", 3000, false, "i", playerid);
	//SetTimerEx("CamaSexo2", 30000, false, "i", playerid);
}

public BoqueteSexo2(playerid)
{
    ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 3.1, false, true, true, false, 0);
	SetTimerEx("BoqueteSexo3", 3000, false, "i", playerid);
	//SetTimerEx("CamaSexo2", 30000, false, "i", playerid);
}

public BoqueteSexo3(playerid)
{
    ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 3.1, false, true, true, false, 0);
	SetTimerEx("BoqueteSexo4", 3000, false, "i", playerid);
	//SetTimerEx("CamaSexo2", 30000, false, "i", playerid);
}

public BoqueteSexo4(playerid)
{
    ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 3.1, false, true, true, false, 0);
	SetTimerEx("BoqueteSexo5", 3000, false, "i", playerid);
	//SetTimerEx("CamaSexo2", 30000, false, "i", playerid);
}

public BoqueteSexo5(playerid)
{
    ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 3.1, false, true, true, false, 0);
	SetTimerEx("BoqueteSexo6", 3000, false, "i", playerid);
	//SetTimerEx("CamaSexo2", 30000, false, "i", playerid);
}

public BoqueteSexo6(playerid)
{
    ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 3.1, false, true, true, false, 0);
	SetTimerEx("CamaSexo2", 30000, false, "i", playerid);
}

// Função para deitar juntos
public CamaSexo1(playerid)
{
	SetPlayerPos(DoSexOffer[playerid], 2197.9556,-1178.3538,1030.4943);
    ApplyAnimation(DoSexOffer[playerid], "CRACK","crckidle2", 4.1, false, false, false, true, 1, SYNC_ALL);
	SetTimerEx("TerminarSexo", 1000, false, "i", playerid);
}

public CamaSexo2(playerid)
{
	SetPlayerPos(playerid, 2198.7786,-1178.4932,1030.4943);
    ApplyAnimation(playerid, "CRACK","crckidle2", 4.1, false, false, false, true, 1, SYNC_ALL);
	SetTimerEx("TerminarSexo", 1000, false, "i", playerid);
}

public TerminarSexo(playerid)
{
	new stringsexo[64];

	SetPlayerPos(DoSexOffer[playerid], 2224.3408,-1145.2854,1025.7969);
	SetPlayerPos(playerid, 2224.3408,-1145.2854,1025.7969);

	TogglePlayerControllable(DoSexOffer[playerid], true);
	TogglePlayerControllable(playerid, true);

	format(stringsexo, sizeof(stringsexo), "O sexo com %s terminou e saiu satisfeito.", PlayerName[playerid]);
	SendClientMessage(DoSexOffer[playerid], -1, stringsexo);
	
	format(stringsexo, sizeof(stringsexo), "O sexo com %s terminou e saiu satisfeito.", PlayerName[DoSexOffer[playerid]]);
	SendClientMessage(playerid, -1, stringsexo);

}

stock ModelViewFunc(playerid)
	return PlayerInfo[playerid][style_view_rg];

stock ShowStats(playerid, targetid)
{
	new
		rg_string[144],
		Nivel = PlayerInfo[targetid][pLevel],
		numberCell = PlayerInfo[targetid][numeroCelular],
		job1 = PlayerInfo[targetid][pEmprego],
		job2 = PlayerInfo[targetid][pEmprego2],
		Sexo = PlayerInfo[targetid][pSex], infoSexo[11],
		nickConjugue[MAX_PLAYER_NAME],
		DinheiroMao = Player_GetMoney(targetid),
		DinheiroConta = PlayerInfo[targetid][pConta],
		quantidadeOuros = PlayerInfo[targetid][pOuros],
		quantidadeCash = Player_GetCash(targetid),
		quantidadeMorte = PlayerInfo[targetid][pDeaths],
		quantidadeKills = PlayerInfo[targetid][pKills],
		quantidadeCrimes = PlayerInfo[targetid][pCrimes],
		quantidadePixacoes = PlayerInfo[targetid][pPixador],
		numeroLoteria = PlayerInfo[targetid][pLottoNr],
		contratosCumpridos = PlayerInfo[targetid][pContratos],
		prisoesAdmin = PlayerInfo[targetid][pPrisaoAdmin],
		horasJogadas = PlayerInfo[targetid][pConnectTime],
		respeitosPlayer = PlayerInfo[targetid][pExp],
		proximoNivel = PlayerInfo[targetid][pLevel] + 1,
		faltamRespeitos = proximoNivel * 8,
		Galao = PlayerInfo[targetid][pGalao], temGalao[5],
		Isqueiro = PlayerInfo[targetid][pIsqueiro], temIsqueiro[5],
		Patins = PlayerInfo[targetid][pPatins], temPatins[5],
		quantidadeExplositvos = PlayerInfo[targetid][pExplosives],
		quantidadeCigarros = PlayerInfo[targetid][pCigarros],
		quantidadeTrocasNick = PlayerInfo[targetid][pTrocaNick],
		avisos = PlayerInfo[targetid][pWarns]
	;

	if (Sexo == 1) infoSexo = "Masculino";
	else infoSexo = "Feminino";

	if (Galao) temGalao = "SIM";
	else temGalao = "NÃO";

	if (Isqueiro) temIsqueiro = "SIM";
	else temIsqueiro = "NÃO";

	if (Patins) temPatins = "SIM";
	else temPatins = "NÃO";

	strmid(nickConjugue, PlayerInfo[targetid][pMarriedTo], 0, strlen(PlayerInfo[targetid][pMarriedTo]), 255);

	if (ModelViewFunc(playerid) == MODEL_VIEW_MESSAGE)
	{
		SendClientMessage(playerid, -1,"___________________________________________________________________________________________");
		format(rg_string, sizeof(rg_string),"** RG de %s ** (Proximo pagamento: %s)", PlayerName[targetid], ConvertTime(PlayerInfo[targetid][pPayDay]));
		SendClientMessage(playerid, 0xFFFFFFFF, rg_string);
		format(rg_string, sizeof(rg_string), "ID: [%d] Nível:[%d] Celular:[%d] Sexo:[%s] Dinheiro:[$%s] Banco:[$%s] Cash:[%s] Ouros:[%s]", Player_GetAccountID(targetid), Nivel, numberCell, infoSexo, getFormatText(DinheiroMao), getFormatText(DinheiroConta), getFormatText(quantidadeCash), getFormatText(quantidadeOuros));
		SendClientMessage(playerid, 0x00AAFFFF, rg_string);
		format(rg_string, sizeof(rg_string), "Conta:[%s{00AAFF}] Conjugue:[%s] Horas Jogadas:[%d] Emprego:[%s] Emprego: [%s]", GetDonateRank(targetid), nickConjugue, horasJogadas, GetJobName(job1), GetJobName(job2));
		SendClientMessage(playerid, 0x00AAFFFF, rg_string);
		format(rg_string, sizeof(rg_string), "Crimes Cometidos:[%d] Nivel de Procura:[%d] Contratos:[%d] Pichações:[%d] Organização:[%s] Cargo:[%s]", quantidadeCrimes, Player_GetWanted(targetid), contratosCumpridos, quantidadePixacoes, NomeORG(targetid), GetPlayerCargo(targetid));
		SendClientMessage(playerid, 0x00AAFFFF, rg_string);
		format(rg_string, sizeof(rg_string), "Respeito:[%d/%d] Loteria:[%d] Galão de Gasolina:[%s] Isqueiro:[%s] Patins:[%s] Cigarros:[%d]", respeitosPlayer, faltamRespeitos, numeroLoteria, temGalao, temIsqueiro, temPatins, quantidadeCigarros);
		SendClientMessage(playerid, 0x00AAFFFF, rg_string);
		format(rg_string, sizeof(rg_string), "Prisões Admin:[%d] Avisos:[%d/3] Trocas de nick:[%d] Explosivos:[%d] Matou:[%d] Morreu:[%d] K/D (%.2f)",
		prisoesAdmin, avisos, quantidadeTrocasNick, quantidadeExplositvos, quantidadeKills, quantidadeMorte, getPlayerKD(targetid));
		SendClientMessage(playerid, 0x00AAFFFF, rg_string);
		format(rg_string, sizeof(rg_string), "Título:[%s{00AAFF}]", PlayerTitle_Get(targetid));
		SendClientMessage(playerid, 0x00AAFFFF, rg_string);
		SendClientMessage(playerid, -1,"___________________________________________________________________________________________");
	}
	else
	{
		MEGAString[0] = EOS;

		format(rg_string, sizeof(rg_string), "\n{FFFFFF}ID: [%d] Nível:[%d] Celular:[%d] Sexo:[%s] Dinheiro:[$%s] Banco:[$%s] Cash:[%s] Ouros:[%s]\n", Player_GetAccountID(targetid), Nivel, numberCell, infoSexo, getFormatText(DinheiroMao), getFormatText(DinheiroConta), getFormatText(quantidadeCash), getFormatText(quantidadeOuros));
		strcat(MEGAString, rg_string);
		format(rg_string, sizeof(rg_string), "\nConta:[%s{FFFFFF}] Conjugue:[%s] Horas Jogadas:[%d] Emprego:[%s] Emprego: [%s]\n", GetDonateRank(targetid), nickConjugue, horasJogadas, GetJobName(job1), GetJobName(job2));
		strcat(MEGAString, rg_string);
		format(rg_string, sizeof(rg_string), "\nCrimes Cometidos:[%d] Nivel de Procura:[%d] Contratos:[%d] Pichações:[%d] Organização:[%s] Cargo:[%s]\n", quantidadeCrimes, Player_GetWanted(targetid), contratosCumpridos, quantidadePixacoes, NomeORG(targetid), GetPlayerCargo(targetid));
		strcat(MEGAString, rg_string);
		format(rg_string, sizeof(rg_string), "\nRespeito:[%d/%d] Loteria:[%d] Galão de Gasolina:[%s] Isqueiro:[%s] Patins:[%s] Cigarros:[%d]\n", respeitosPlayer, faltamRespeitos, numeroLoteria, temGalao, temIsqueiro, temPatins, quantidadeCigarros);
		strcat(MEGAString, rg_string);
		format(rg_string, sizeof(rg_string), "\nPrisões Admin:[%d] Avisos:[%d/3] Trocas de nick:[%d] Explosivos:[%d] Matou:[%d] Morreu:[%d] K/D (%.2f)\n",
		prisoesAdmin, avisos, quantidadeTrocasNick, quantidadeExplositvos, quantidadeKills, quantidadeMorte, getPlayerKD(targetid));
		strcat(MEGAString, rg_string);
		format(rg_string, sizeof(rg_string), "\nTítulo:[%s{FFFFFF}]\n", PlayerTitle_Get(targetid));
		strcat(MEGAString, rg_string);

		format(rg_string, sizeof(rg_string), "RG de %s (Proximo pagamento: %s)", PlayerName[targetid], ConvertTime(PlayerInfo[targetid][pPayDay]));
		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, rg_string, MEGAString, "Fechar", "");
	}
	return true;
}

CMD:infovip(playerid)
{
	if (Player_Logado(playerid))
	{
		new sql_string[256];
		mysql_format(MySQL_Handle, sql_string, sizeof sql_string, "SELECT DATE_FORMAT(vip_vencimento, '%%d/%%m/%%Y %%H:%%i:%%s') as vip_vencimento FROM `player` WHERE `id` = '%d' AND CURRENT_TIMESTAMP() < `vip_vencimento` LIMIT 1", PlayerInfo[playerid][pID]);
		mysql_tquery(MySQL_Handle, sql_string, "onPlayerVipCheck", "d", playerid);
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está logado para usar esse comando.");
	}
	return true;
}

CMD:rg(playerid)
{
	if (!Player_Logado(playerid)) return false;

	return ShowStats(playerid, playerid);
}

CMD:mostrarrg(playerid, params[])
{
	new idplayer;
	if (sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Modo de uso: /mrg (id)");

	if (!Player_Logado(idplayer))
		return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (Admin_GetNivel(idplayer) && Staff_GetWorking(idplayer))
		return SendClientMessage(playerid, -1, "Você não pode mostrar rg para admins em modo trabalho !");

	if (!ProxDetectorS(5.0, playerid, idplayer))
		return SendClientMessage(playerid, -1, "Você não está próximo a esse jogador.");

	if (idplayer != INVALID_PLAYER_ID)
	{
		new string[128];
		ShowStats(idplayer, playerid);

		format(string, sizeof(string), "(( %s mostrou o seu rg para %s. ))", PlayerName[playerid], PlayerName[idplayer]);
		SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
	}

	return true;
}
alias:mostrarrg("mrg")

