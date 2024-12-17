/*  ----------------------------------------------------------------------------------------------------------------------------------------
        Sistema de organizações;
 ----------------------------------------------------------------------------------------------------------------------------------------- */

#if defined _INC_orgs
	#endinput
#endif
#define _INC_orgs

#include <YSI_Coding\y_hooks>

// Entrada do módulo
#include <orgs-entry>
#include <orgs_cmds>

#include <org_vip>			// Sistema de ORG-VIP

// --------------------------------------------------------------
// Pasta: "orgs": Controle da organização, configuração, gerenciamento;
// Sistema de shop da org
#include <orgs-shop>

// Sistema de salária;
#include <orgs_salary>

// Sistema de área segura da org;
#include <orgs-secure-area>

// Textdraws do sistema
#include <orgs-textdraws>

// --------------------------------------------------------------
// Pasta: "orgs/tasks": Tarefas para organizações;

// Sistema de guerra no morro;
#include <orgs-morro>

// Sistema de invasão de organização;
#include <orgs-invasion>

// Sistema de treinamento de organização;
#include <orgs-training>

#include <orgs_spawn>

#include <orgs_dominar>

// Organizações: Assassinas.
#include <orgs_assassinas>

// Mercenários:
#include <according>		// Sistema de acordos

// --------------------------------------------------------------

static
		Statement: stmt_selectOrg,
		Statement: stmt_updateOrg;

static 
		Statement: stmt_selectOrgMember,
		Statement: stmt_deletePlayerOrg,
		Statement: stmt_insertPlayerInOrg,
		Statement: stmt_updateCargoOrg;

static 
		Statement: stmt_updateNameCargo;

hook OnMySQLConnected() {

	// --------------------------------------------------------------------------------------------------------
	// Sistema de organização (principal)
	// --------------------------------------------------------------------------------------------------------

	static const query_selectOrg[] = 
		"SELECT * FROM `org_info` a INNER JOIN org_cargos b ON a.id = b.orgid";
	stmt_selectOrg = MySQL_PrepareStatement(MySQL_Handle, query_selectOrg);

	static const query_updateOrg[] = 
		"UPDATE `org_info` SET `?` = ? WHERE `id` = ?";
	stmt_updateOrg = MySQL_PrepareStatement(MySQL_Handle, query_updateOrg);

	// --------------------------------------------------------------------------------------------------------
	// Sistema de membros
	// --------------------------------------------------------------------------------------------------------

	static const query_selectOrgMember[] = 
		"SELECT o.orgid, o.member, p.org_cargo, p.nome, p.ultimo_login FROM org_membros o INNER JOIN player p ON p.id = o.member"
	;
	stmt_selectOrgMember = MySQL_PrepareStatement(MySQL_Handle, query_selectOrgMember);

	static const query_insertPlayerInOrg[] = 
		"INSERT INTO `org_membros` (`orgid`,`member`,`date_entrance`) VALUES ('?','?', CURRENT_TIMESTAMP())";
	stmt_insertPlayerInOrg = MySQL_PrepareStatement(MySQL_Handle, query_insertPlayerInOrg);

	static const query_deletePlayerOrg[] = 
		"DELETE FROM `org_membros` WHERE `org_membros`.`member` = ?"
	;
	stmt_deletePlayerOrg = MySQL_PrepareStatement(MySQL_Handle, query_deletePlayerOrg);

	static const query_updateCargoOrg[] = 
		"UPDATE `player` SET `org_membro` = '?', `org_cargo` = '?' WHERE id = ?"
	;
	stmt_updateCargoOrg = MySQL_PrepareStatement(MySQL_Handle, query_updateCargoOrg);

	// --------------------------------------------------------------------------------------------------------
	// Sistema de cargos
	// --------------------------------------------------------------------------------------------------------

	static const query_updateNameCargo[] = 
		"UPDATE `org_cargos` SET `cargo_?` = '?' WHERE orgid = ?"
	;
	stmt_updateNameCargo = MySQL_PrepareStatement(MySQL_Handle, query_updateNameCargo);
	
	return 1;
}

stock OrgCargo_Update(orgid, cargoid, const namecargo[]) {

	format(OrgPermissions[orgid][cargoid][CargoName], 35, namecargo);

	MySQL_BindInt(stmt_updateNameCargo, 0, cargoid);
	MySQL_Bind(stmt_updateNameCargo, 1, namecargo, true);
	MySQL_BindInt(stmt_updateNameCargo, 2, orgid);
	MySQL_ExecuteThreaded(stmt_updateNameCargo);
}

// stock OrgInfo_UpdateStr(idorg, const coluna[], const value[]) {

// 	new string[40];
	
// 	switch(coluna) {
// 		case "org_vip_date": {
// 			format(OrgInfo_GetVIPDate(idorg), sizeof(string), "%s", value);
// 		}
// 		default: return 1;
// 	}
// 	MySQL_Bind(stmt_updateOrg, 0, coluna, true);
// 	MySQL_Bind(stmt_updateOrg, 1, value, true);
// 	MySQL_BindInt(stmt_updateOrg, 2, idorg);
// 	MySQL_ExecuteThreaded(stmt_updateOrg);
	
// 	return 1;
// }

stock OrgInfo_UpdateInt(idorg, const coluna[], value) 
{
	MySQL_Bind(stmt_updateOrg, 0, coluna, true);
	MySQL_BindInt(stmt_updateOrg, 1, value);
	MySQL_BindInt(stmt_updateOrg, 2, idorg);
	MySQL_ExecuteThreaded(stmt_updateOrg);
	return 1;
}

// Getter's e Setter's
stock OrgInfo_GetMoney(idorg) {
	return CofreOrg[idorg][orgDinheiro];
}

stock OrgInfo_SetMoney(idorg, money) {
    if ((CofreOrg[idorg][orgDinheiro] + money) < max_money_limit) {
	    CofreOrg[idorg][orgDinheiro] = money;
		OrgInfo_UpdateInt(idorg, "money", money);
	}
}

stock OrgInfo_GetLeaderDay(idorg) {
	return CofreOrg[idorg][DiaLider];
}

stock OrgInfo_SetLeaderDay(idorg, day) {
	CofreOrg[idorg][DiaLider] = day;

	OrgInfo_UpdateInt(idorg, "leader_day", day);
}

stock OrgInfo_GetMaterials(idorg) {
	return CofreOrg[idorg][Materiais];
}

stock OrgInfo_SetMaterials(idorg, materials) {
	CofreOrg[idorg][Materiais] = materials;

	OrgInfo_UpdateInt(idorg, "materials", materials);
}

stock OrgInfo_GetMarihuana(idorg) {
	return CofreOrg[idorg][Maconha];
}

stock OrgInfo_SetMarihuana(idorg, marihuana) {
	CofreOrg[idorg][Maconha] = marihuana;

	OrgInfo_UpdateInt(idorg, "marihuana", marihuana);
}

stock OrgInfo_GetCocaine(idorg) {
	return CofreOrg[idorg][Cocaina];
}

stock OrgInfo_SetCocaine(idorg, cocaine) {
	CofreOrg[idorg][Cocaina] = cocaine;

	OrgInfo_UpdateInt(idorg, "cocaine", cocaine);
}

stock OrgInfo_GetCrack(idorg) {
	return CofreOrg[idorg][Crack];
}

stock OrgInfo_SetCrack(idorg, crack) {
	CofreOrg[idorg][Crack] = crack;

	OrgInfo_UpdateInt(idorg, "crack", crack);
}

stock OrgInfo_GetGiveMarihuana(idorg) {
	return CofreOrg[idorg][dMaconha];
}

stock OrgInfo_SetGiveMarihuana(idorg, marihuana) {
	CofreOrg[idorg][dMaconha] = marihuana;

	OrgInfo_UpdateInt(idorg, "give_marihuana", marihuana);
}

stock GetPlayerGZColor(playerid)
{
	new orgid = GetPlayerOrg(playerid);
	new color;
	switch(orgid)
	{
	    case 1,2,11,16,3,33,34:color 	= 0xAAAEE996;
	    case 5:color 	= TEAM_AZTECAS_COLOR;
	    case 6:color 	= COLOR_RIFA;
	    case 12:color 	= COLOR_RUSSA;
	    case 13:color 	= COLOR_YAK;
	    case 14:color 	= TEAM_GROVE_COLOR;
	    case 17:color 	= COLOR_FDN;
	    case 18:color 	= COLOR_BAIRRO13;
	    case 19:color 	= COLOR_CV;
	    case 21:color 	= COR_PCC;
	    case 24:color 	= COR_COSANOSTRA;
	    default:color   = -1;
	}
	return color;
}

stock GetPlayerCargo(playerid) 
{
	new orgid = GetPlayerOrg(playerid),
		cargoid = PlayerInfo[playerid][pCargo],
		cargoname[40];

	format(cargoname, sizeof(cargoname), OrgPermissions[orgid][cargoid][CargoName]);
	return cargoname;
}

stock GetCargoOrg(orgid, cargoid)
{
	new cargoname[40];
	format(cargoname, sizeof(cargoname), OrgPermissions[orgid][cargoid][CargoName]);
	return cargoname;
}

stock ShowMembersInOrg(playerid, iddialog, const title[], const option1[], const option2[]) {

	new orgid = GetPlayerOrg(playerid);
	new string[128];
	new loop = 0;

	MEGAString[0] = EOS;

	strcat(MEGAString, ""C_SAMP"vaga\tMembro\tÚltimo login\n");

	for(new slot; slot < MAX_SLOTS_ORGS; slot++) {

		if (OrgMembros[orgid][slot][MemberID]) {
			if (slot == SLOT_LIDER) {
				format(string, sizeof string, 
					""C_YELLOW"Líder\t"C_WHITE"%s\t"C_GRAY"%s\n",
				OrgMembros[orgid][slot][MemberName], OrgMembros[orgid][slot][MemberLogin]);
			} else {
				format(string, sizeof string, 
					""C_GRAY"%d\t"C_WHITE"%s\t"C_GRAY"%s\n", 
				slot, OrgMembros[orgid][slot][MemberName], OrgMembros[orgid][slot][MemberLogin]);
			}
			Dialog_Select[playerid][loop] = OrgMembros[orgid][slot][MemberID];
			loop++;

			strcat(MEGAString, string);
		}
	}

	ShowPlayerDialog(playerid, iddialog, DIALOG_STYLE_TABLIST_HEADERS, title, MEGAString, option1, option2);

	return 1;
}

hook OnPlayerLogin(playerid) {

	new idorg = GetPlayerOrg(playerid),
		idcargo = PlayerInfo[playerid][pCargo];

	if (idorg) {
		PlayerInfo[playerid][pMembro] = 0;
		PlayerInfo[playerid][pCargo] = 0;

		for (new slot; slot < MAX_SLOTS_ORGS; slot++) {
			if (OrgMembros[idorg][slot][MemberID] == PlayerInfo[playerid][pID]) {
				PlayerInfo[playerid][pMembro] = idorg;
				PlayerInfo[playerid][pCargo] = idcargo;
				break;
			}
		}
	}
}

stock GetSlotsInOrg(idorg) 
{
	new count;

	for (new slot; slot < MAX_SLOTS_ORGS; slot++) {
		if (!OrgMembros[idorg][slot][MemberID]) {
			count++;

			if (count > 0) break;
		}
	}
	return count;
}

stock GetTotalMembersInOrg(idorg) 
{
	new count;

	for (new slot; slot < MAX_SLOTS_ORGS; slot++) {
		if (OrgMembros[idorg][slot][MemberID]) {
			count++;
		}
	}
	return count;
}

stock SetPlayerMember(playerid, orgid) {

	for (new slot = 1; slot < MAX_SLOTS_ORGS; slot++) {
		if (!OrgMembros[orgid][slot][MemberID]) {

			// Define na organização
			OrgMembros[orgid][slot][MemberID] = PlayerInfo[playerid][pID];
			format(OrgMembros[orgid][slot][MemberName], MAX_PLAYER_NAME, PlayerName[playerid]);

			// Inserir na tabela
			MySQL_BindInt(stmt_insertPlayerInOrg, 0, orgid);
			MySQL_BindInt(stmt_insertPlayerInOrg, 1, PlayerInfo[playerid][pID]);
			MySQL_ExecuteThreaded(stmt_insertPlayerInOrg);

			// Inserir na variavel
			PlayerInfo[playerid][pMembro] = orgid;
			PlayerInfo[playerid][pCargo] = 1;

			break;
		}
	}
}

stock ShowInfoOrg(playerid, orgid, iddialog, const title[], const option1[], const option2[]) 
{
	new string[210];
	new havePedido = CofreOrg[orgid][cMateriais] + CofreOrg[orgid][cMaconha];

	MEGAString[0] = EOS;

	format(string, sizeof(string), ""C_GRAY"Organização: "C_WHITE"%s\n", GetOrgName(orgid));
	strcat(MEGAString, string);

	format(string, sizeof(string), ""C_CYAN"Líder: "C_WHITE"%s\n\n", OrgMembros[orgid][SLOT_LIDER][MemberName]);
	strcat(MEGAString, string);

	strcat(MEGAString, ""C_GRAY"----------------------------------------------------------------------\n\n");

	format(string, sizeof(string), ""C_YELLOW"Organização VIP:	%s\n", CofreOrg[orgid][orgVIP] ? (""C_GREEN"SIM") : (""C_RED"NAO"));
	strcat(MEGAString, string);

	if (CofreOrg[orgid][orgVIP]) {
		format(string,sizeof(string),""C_GRAY"Vencimento: "C_WHITE"%s\n", CofreOrg[orgid][org_vip_date]);
		strcat(MEGAString, string);
	}

	strcat(MEGAString, ""C_GRAY"----------------------------------------------------------------------\n\n");

	format(string, sizeof(string), ""C_MONEY"Dinheiro:		"C_WHITE"$%s\n", getFormatText(OrgInfo_GetMoney(orgid)));
	strcat(MEGAString, string);
	format(string,sizeof(string), ""C_GREEN"Maconha:		"C_WHITE"%sg\n", getFormatText(CofreOrg[orgid][Maconha], ","));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY2"Crack: 			"C_WHITE"%dg\n", getFormatText(CofreOrg[orgid][Crack], ","));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_RED"Cocaina: 		"C_WHITE"%dg\n", getFormatText(CofreOrg[orgid][Cocaina], ","));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_BROWN"Materiais: 		"C_WHITE"%sg\n", getFormatText(CofreOrg[orgid][Materiais]));
	strcat(MEGAString, string);

	if (havePedido) {
		strcat(MEGAString, ""C_GRAY"----------------------------------------------------------------------\n");
		strcat(MEGAString, ""C_GRAY2"Pedidos: \n\n");

		if (CofreOrg[orgid][cMateriais] > 0) {
			format(string, sizeof(string),""C_WHITE"Comprando até "C_BROWN"%sg "C_WHITE"de materiais, por: "C_MONEY"$%s "C_WHITE"a grama.\n", 
			getFormatText(CofreOrg[orgid][cMateriais]), getFormatText(CofreOrg[orgid][mMateriais]));

			strcat(MEGAString, string);
		}

		if (CofreOrg[orgid][cMaconha] > 0) {
			format(string, sizeof(string),""C_WHITE"Comprando até "C_GREEN"%sg "C_WHITE"de maconha, por: "C_MONEY"$%s "C_WHITE"a grama.\n", 
			getFormatText(CofreOrg[orgid][cMaconha]), getFormatText(CofreOrg[orgid][mMaconha]));

			strcat(MEGAString, string);
		}
	}

	// Mudar
	strcat(MEGAString, ""C_GRAY"----------------------------------------------------------------------\n");
	strcat(MEGAString, ""C_GRAY2"Salário dos membros: \n\n");

	format(string, sizeof(string), ""C_GRAY"Cargo 1: 		"C_WHITE"%d\n",CofreOrg[orgid][salarioc1]);
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"Cargo 2: 		"C_WHITE"%d\n",CofreOrg[orgid][salarioc2]);
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"Cargo 3: 		"C_WHITE"%d\n",CofreOrg[orgid][salarioc3]);
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"Cargo 4: 		"C_WHITE"%d\n",CofreOrg[orgid][salarioc4]);
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"Cargo 5+: 		"C_WHITE"%d\n", CofreOrg[orgid][salarioc5]);
	strcat(MEGAString, string);

	format(string, sizeof(string), ""C_GRAY"Sub-Lideres: 		"C_WHITE"%d\n", CofreOrg[orgid][salarioc5]);
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"Líder: 			"C_WHITE"%d\n", CofreOrg[orgid][salariolider]);
	strcat(MEGAString, string);

	strcat(MEGAString, ""C_GRAY"----------------------------------------------------------------------");
	
	ShowPlayerDialog(playerid, iddialog, DIALOG_STYLE_LIST, title, MEGAString, option1, option2);
}

stock IsLeaderOrg(playerid) {
	new org = GetPlayerOrg(playerid);

	if (PlayerInfo[playerid][pCargo] == LIDER) {
		return org;
	}
	return 0;
}

stock SendMembersMessage(idorg, color, const msg[])
{
	if (!idorg)
		return 1;
	
	foreach(new i : Player) {
		if (GetPlayerOrg(i) == idorg) {
			if(!Chat_Organizacao[i]) {
				SendClientMessage(i, color, msg);
			}
		}
		//obs
		else if(GetPVarInt(i, "OrelhaGrandeOrg")) {
			new admin_string[128];
			format(admin_string, 128, "[%s] %s", GetOrgName(idorg), msg);
			SendClientMessage(i, color, admin_string);
		}
	}
	return 1;
}

// A organização tem líder
stock HaveLeaderInOrg(idorg) 
{
	if (OrgMembros[idorg][SLOT_LIDER][MemberID])
		return true;
	
	return false;
}

stock SetPlayerCargo(idplayer, idorg, idcargo) 
{
	PlayerInfo[idplayer][pMembro] = idorg;
	PlayerInfo[idplayer][pCargo] = idcargo;

	if (idcargo == LIDER) {
		OrgMembros[idorg][SLOT_LIDER][MemberID] = PlayerInfo[idplayer][pID];

		MySQL_BindInt(stmt_insertPlayerInOrg, 0, idorg);
		MySQL_BindInt(stmt_insertPlayerInOrg, 1, PlayerInfo[idplayer][pID]);
		MySQL_ExecuteThreaded(stmt_insertPlayerInOrg);
	} else {
		MySQL_BindInt(stmt_updateCargoOrg, 0, idorg);
		MySQL_BindInt(stmt_updateCargoOrg, 1, idcargo);
		MySQL_BindInt(stmt_updateCargoOrg, 2, PlayerInfo[idplayer][pID]);
		MySQL_ExecuteThreaded(stmt_updateCargoOrg);
	}

	return 1;
}

hook OnGameModeInit() {

	// Criar os textdraws;
	CreateOrgsTextDraws();

	// Carregar organização;
	inline const OnLoadOrgs() {

		new 
            // Informações gerais
            idorg,
			// nameorg[36],
			vip_date[30],
			leader_day,
			money,
			materials,
			marihuana,
			cocaine,
			crack,
			give_marihuana,
			buy_marihuana_qtd,
			buy_marihuana_price,
			buy_materials_qtd,
			buy_materials_price,
            
            // Cargos
            rolename[MAX_CARGOS_ORG+1][MAX_ROLE_NAME];

        // Informações gerais
		MySQL_BindResultInt(stmt_selectOrg, 0, idorg);
		MySQL_BindResult(stmt_selectOrg, 1, vip_date);
		MySQL_BindResultInt(stmt_selectOrg, 2, leader_day);
		MySQL_BindResultInt(stmt_selectOrg, 3, money);
		MySQL_BindResultInt(stmt_selectOrg, 4, materials);
		MySQL_BindResultInt(stmt_selectOrg, 5, marihuana);
		MySQL_BindResultInt(stmt_selectOrg, 6, cocaine);
		MySQL_BindResultInt(stmt_selectOrg, 7, crack);
		MySQL_BindResultInt(stmt_selectOrg, 8, give_marihuana);
		MySQL_BindResultInt(stmt_selectOrg, 9, buy_marihuana_qtd);
		MySQL_BindResultInt(stmt_selectOrg, 10, buy_marihuana_price);
		MySQL_BindResultInt(stmt_selectOrg, 11, buy_materials_qtd);
		MySQL_BindResultInt(stmt_selectOrg, 12, buy_materials_price);

        // Cargos
        for (new role = 1; role < MAX_CARGOS_ORG + 1; role++)
            MySQL_BindResult(stmt_selectOrg, 13 + role, rolename[role]);

		while(MySQL_Statement_FetchRow(stmt_selectOrg)) 
		{
			CofreOrg[idorg][DiaLider] = leader_day;
			format(CofreOrg[idorg][org_vip_date], 30, vip_date);
			CofreOrg[idorg][orgDinheiro] = money;
			CofreOrg[idorg][Materiais] = materials;
			CofreOrg[idorg][Maconha] = marihuana;
			CofreOrg[idorg][Cocaina] = cocaine;
			CofreOrg[idorg][Crack] = crack;
			CofreOrg[idorg][dMaconha] = give_marihuana;
			CofreOrg[idorg][cMaconha] = buy_marihuana_qtd;
			CofreOrg[idorg][mMaconha] = buy_marihuana_price;
			CofreOrg[idorg][cMateriais] = buy_materials_qtd;
			CofreOrg[idorg][mMateriais] = buy_materials_price;

            for (new role = 1; role < MAX_CARGOS_ORG + 1; role++)
				format(OrgPermissions[idorg][role][CargoName], MAX_ROLE_NAME, rolename[role]);
		}
	}
	MySQL_ExecuteParallel_Inline(stmt_selectOrg, using inline OnLoadOrgs);
	
	inline const OnLoadPlayersOrg() {

		new idorg,
			memberid,
			idcargo,
			membername[MAX_PLAYER_NAME+1],
			memberlogin[55];

		MySQL_BindResultInt(stmt_selectOrgMember, 0, idorg);
		MySQL_BindResultInt(stmt_selectOrgMember, 1, memberid);
		MySQL_BindResultInt(stmt_selectOrgMember, 2, idcargo);
		MySQL_BindResult(stmt_selectOrgMember, 3, membername);
		MySQL_BindResult(stmt_selectOrgMember, 4, memberlogin);

		while(MySQL_Statement_FetchRow(stmt_selectOrgMember)) 
		{
			if (idcargo == LIDER) {
				OrgMembros[idorg][SLOT_LIDER][MemberID] = memberid;
				format(OrgMembros[idorg][SLOT_LIDER][MemberName], sizeof(membername), membername);
				format(OrgMembros[idorg][SLOT_LIDER][MemberLogin], sizeof(memberlogin), memberlogin);
			} else {
				for(new slots = 1; slots < MAX_SLOTS_ORGS; slots++) {
					if (!OrgMembros[idorg][slots][MemberID]) {
						OrgMembros[idorg][slots][MemberID] = memberid;
						format(OrgMembros[idorg][slots][MemberName], sizeof(membername), membername);
						format(OrgMembros[idorg][slots][MemberLogin], sizeof(memberlogin), memberlogin);

						break;
					}
				}
			}
		}
	}
	MySQL_ExecuteParallel_Inline(stmt_selectOrgMember, using inline OnLoadPlayersOrg);

	return 1;
}


// Tipo de Organização - Necessário adicionar para aplicar em territórios
static GetOrgType(orgid) {
	static OrgType:type;

	switch (orgid) {
		case 1, 2, 3, 11, 16, 29, 33, 34: {
			type = TYPE_COP;
		}
		case 5, 14, 17, 18, 19, 21, 26: {
			type = TYPE_GANG;
		}
		case 12, 13, 24: {
			type = TYPE_MAFIA;
		}
		case 8, 22: {
			type = TYPE_ASSASSINS;
		}
		case 25, 28: {
			type = TYPE_MERCENARY;
		} 
		case 15, 20, 23: {
			type = TYPE_TERROR;
		}
	}
	return _:type;
}

stock GetOrgArticle(orgid, bool:noun=false, bool:uppercase=false) {
	new article[10];
	switch (orgid) {
		//Orgs masculina
		case 7, 20: {
			article = "o";
		}
		case 4, 5, 6, 8, 17, 18, 19: {
			article = "os";
		}
		//Orgs feminina
		case 1, 2, 9, 10, 11, 12, 13, 14, 15, 16, 21, 22, 24, 25, 28, 33, 34: {
			article = "a";
		}
		case 3: {
			article = "as";
		}
	}

	if(noun) {
		format(article, 10, "d%s", article);
	}
	if(uppercase) {
		article[0] = toupper(article[0]);
	}

	return article;
}

stock GetPlayerOrg(playerid)
{
	if (!IsPlayerConnected(playerid)) 
		return 0;
	
	if (PlayerInfo[playerid][pMembro]) {
		return PlayerInfo[playerid][pMembro];
	}
	return 0;
}

static CleanMemberFunctions(playerid) {

	switch (GetOrgType(GetPlayerOrg(playerid))) {
		case TYPE_ASSASSINS: {

			// Limpando contrato do assassino.
			if (GoChase[playerid] != INVALID_PLAYER_ID)
			{
				GotHit[GoChase[playerid]] = 0;
				GotTri[GoChase[playerid]] = 0;
				GetChased[GoChase[playerid]] = INVALID_PLAYER_ID;
				GoChase[playerid] = INVALID_PLAYER_ID;
			}
		}
	}
}

stock DismissPlayerOrg(orgid, g_id)
{
	new idglobal = GetPlayerIdByIdGlobal(g_id);

	if (Player_Logado(idglobal)) {

		// Reseta variáveis
		PlayerInfo[idglobal][pMembro] = 0;
		PlayerInfo[idglobal][pCargo] = 0;
		OnDuty[idglobal] = 0;
		EmpregoDuty[idglobal] = 0;

		// Limpa funções exclusivas da organização
		CleanMemberFunctions(idglobal);

		// Retorna a cor do jogador
		SetPlayerToTeamColor(idglobal);
	}

	// Remove do slot
	for(new slot; slot < MAX_SLOTS_ORGS; slot++) {
		if (OrgMembros[orgid][slot][MemberID] == g_id) {
			OrgMembros[orgid][slot][MemberID] = 0;
		}
	}

	// Atualiza tabela player
	MySQL_BindInt(stmt_updateCargoOrg, 0, 0);
	MySQL_BindInt(stmt_updateCargoOrg, 1, 0);
	MySQL_BindInt(stmt_updateCargoOrg, 2, g_id);
	MySQL_ExecuteThreaded(stmt_updateCargoOrg);

	// Atualiza na tabela org_membros
	MySQL_BindInt(stmt_deletePlayerOrg, 0, g_id);
	MySQL_ExecuteThreaded(stmt_deletePlayerOrg);
}

stock GetOrgName(orgid)
{
	new name[35];
	switch(orgid)
	{
	    case 1:name = "Policia Militar";
	    case 2:name = "BOPE";
	    case 3:name = "Forças Armadas";
	    case 4:name = "S.A.M.U";
	    case 5:name = "Amigo dos Amigos";
	    case 7:name = "Governo";
	    case 8:name = "Hitmans";
	    case 9:name = "San News";
	    case 11:name = "Policia Federal";
	    case 12:name = "Mafia Italiana";
	    case 13:name = "Mafia Yakuza";
	    case 14:name = "G.R.O.T.A";
	    case 15:name = "Estado Islamico";
	    case 16:name = "P.R.F";
	    case 17:name = "Familia do Norte";
	    case 18:name = "BAIRRO-13";
		case 19:name = "C.V";
	    case 20:name = "Al-Qaeda";
	    case 21:name = "P.C.C";
	    case 22:name = "The Triad";
	    case 24:name = "Mafia Cosa Nostra";
	    case 25:name = "Sons Of Anarchy";
	    case 28:name = "Warlocks";
	    case 33:name = "Policia Civil";
	    case 34:name = "CORE";
	    default:name = "Nenhuma";
	}
	return name;
}

stock GetOrgColor(orgid)
{
	new colorOrg[8];

	switch(orgid)
	{
	    case 1: colorOrg = "605DFF";
		case 2: colorOrg = "737373";
		case 3: colorOrg = "00660C";
		case 4: colorOrg = "EA8282";
		case 5: colorOrg = "2641FE";
	    case 7: colorOrg = "0095FF";
		case 8: colorOrg = "BDBDBD";
		case 9: colorOrg = "DFB77B";
		case 11: colorOrg = "917662";
		case 12: colorOrg = "D85300";
		case 13: colorOrg = "18C09F";
		case 14: colorOrg = "177517";
		case 15: colorOrg = "571E1E";
		case 16: colorOrg = "FFFF44";
		case 17: colorOrg = "99311E";
		case 18: colorOrg = "010701";
		case 19: colorOrg = "F80505";
		case 20: colorOrg = "EE2323";
		case 21: colorOrg = "7F994C";
		case 22: colorOrg = "A4D1FF";
	 	case 23: colorOrg = "024566";
	 	case 24: colorOrg = "33FFFF";
		case 25: colorOrg = "576176";
		case 26: colorOrg = "FFFF99";
		case 28: colorOrg = "A3283D";
		case 33: colorOrg = "996600";
		case 34: colorOrg = "333300";
		default: colorOrg = "FFFFFF";
	}
	return colorOrg;
}

stock GetOrgHexColor(orgid) {
	new color[16];
	format(color, 16, "%sAA", GetOrgColor(orgid));
	return HexStr(color);
}

CALLBACK:IsANeutra(playerid)
{
	switch(GetPlayerOrg(playerid))
	{
	    case 4,9: return true;
	}
	return false;
}

CALLBACK:SendCopMessage(color, const message[])
{
	foreach(new i : Player)
	{
	    if (IsACop(i) && OnDuty[i] == 1)
	    	SendClientMessage(i, color, message);
	}
	return false;
}

CALLBACK:SendCopMessageAll(color, const message[])
{
	foreach(new i : Player)
	{
	    if (IsACop(i)) SendClientMessage(i, color, message);
	}
	return false;
}