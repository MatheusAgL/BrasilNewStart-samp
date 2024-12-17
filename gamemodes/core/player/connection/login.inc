#if defined _inc_player_login_system
	#endinput
#endif
#define _inc_player_login_system true

#include <YSI_Coding\y_hooks>

#include <login_entry>

// ----------------------------------------------------
// Sistema de login:

CMD:logar(playerid)
{
	if (Player_Logado(playerid)) return 1;
	
	if (GetPVarInt(playerid, "LoginChecked") == 1) 
	{
		if (!GetPVarInt(playerid, "AccountBeingLoaded")) 
		{
			if (IsPlayerRegistered(playerid))
				Login_ShowDialog(playerid);
			else
				Register_ShowDialog(playerid);
		} else {
			ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", ""C_OPENMP"Carregando a conta...", "Fechar", "");
		}
	} else {
		SetPVarInt(playerid, "LoginClicked", 1);
		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", ""C_OPENMP"Buscando a conta...", "Fechar", "");
	}
	return 1;
}

hook OnClickDynPlayerTextDraw(playerid, PlayerText:textid)
{
   	if (!Player_Logado(playerid)) {
		// Entrar/Cadastrar
        if (textid == login_ptextdraws[2][playerid]) 
		{
			callcmd::logar(playerid);
	    }
        return 1;
    }
    return 1;
}

hook OnClickDynamicTextDraw(playerid, Text:textid) {

    if (!Player_Logado(playerid)) {
		// Esqueceu sua sennha?
	    if (textid == login_textdraws[6]) {
			ShowPlayerConfirmEmail(playerid);
        }
	    return 1;
	}
	return 1;
}

#define     MAX_AREA_MORRO      3
#define     MAX_ORGS            35
new GZMorro[MAX_AREA_MORRO];

enum guerraMorro {

	gDono,
	gPontosDono,
	gMortes,
	gColor,
};
new GuerraMorro[MAX_AREA_MORRO][guerraMorro];

new MorroPontos[MAX_AREA_MORRO][MAX_ORGS];
new gTempoMorro;
new gTimerMorro;
new gDinheiro;
new bool:gGuerraMorro;
 
CALLBACK: OnPlayerLogin(playerid)
{
	Log_IP(playerid);

	if (Player_CheckBan(playerid) || 
		!Player_CheckNick(playerid)) 
		return 1;

	SetSpawnInfo(playerid, 23, NO_TEAM, 0.0, 0.0, 120.0, 0.0, WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0);
	StopAudioStreamForPlayer(playerid);
	Login_Hidescreen(playerid);
	
	Player_SetLogado(playerid, true);
	SetPlayerHealth(playerid, PlayerInfo[playerid][pHealth]);
	SetPlayerArmour(playerid, PlayerInfo[playerid][pArmour]);
	Player_SetNivel(playerid, Player_GetNivel(playerid));
	Player_SetWanted(playerid, Player_GetWanted(playerid));
	GivePlayerMoney(playerid, Player_GetMoney(playerid));
	SetPlayerToTeamColor(playerid);

	PlayerInfo[playerid][pChatNoob] = true;

	TogglePlayerSpectating(playerid, false);

	CreatePlayerTextDrawsDrugInfo(playerid);
	CallRemoteFunction("CreateDynamicTextDraws", "d", playerid);

	// EnableHealthBarForPlayer(playerid, false);

	// Carregar GangZone Morro, territórios, guerras e Áreas Neutras
	for (new gZone = 0; gZone < sizeof(GZMorro); gZone++)
		GangZoneShowForPlayer(playerid, GZMorro[gZone], GuerraMorro[gZone][gColor]);

	ShowPlayerHQZones(playerid);
	LoadTrForPlayer(playerid);

	Player_LoadVehicles(playerid);

	if (PlayerInfo[playerid][pExplosives] > 1) 
		PlayerInfo[playerid][pExplosives] = 1;

	new lastLogin[50], 
		Timestamp:lastLoginTs;
	TimeParse(PlayerInfo[playerid][pLaastLogin], MYSQL_TIMESTAMP, lastLoginTs);
	TimeFormat(lastLoginTs, TIMESTAMP_FORMAT, lastLogin);

	new string[128];
	SendClientMessage(playerid, -1, "-----------------------------------------------------------------------------------------------------");
	format(string, sizeof string, "Olá {00CCFF}%s{FFFFFF}, seu último login no servidor foi %s", PlayerName[playerid], lastLogin);
	SendClientMessage(playerid, -1, string);
	strmid(PlayerInfo[playerid][pLaastLogin], GetCurrentDateHour(ONLY_CURRENT_ALL), 0, strlen(string), 255);

	if (Holiday_Get())
		SendMsgF(playerid, COLOR_YELLOW, "Feriado: "C_LIGHTWHITE"Hoje é feriado de... %s. Bônus ativo hoje!", Holiday_GetName());
	
	SendClientMessage(playerid, -1, "-----------------------------------------------------------------------------------------------------");

	SendClientMessage(playerid, 0xDBED15FF, "Se caso tiver algum problema use: /atendimento | caso não tenha /admins online use: /n (Canal novato)");
	SendClientMessage(playerid, 0xDBED15FF, "Use o comando {FFFFFF}/menu {DBED15}para configurar e fazer compras no servidor.");

	PlayerPlaySound(playerid, 1191, 0.0, 0.0, 0.0);

	if (PlayerInfo[playerid][pWarns] >= 1) {
		format(string, sizeof string, "Sua conta possui (%d/3) avisos | Com 3 avisos será banido automaticamente por 3 dias!", PlayerInfo[playerid][pWarns]);
		SendClientMessage(playerid, COLOR_LIGHTRED, string);
	}


	SetPlayerFamily(playerid);

	SetPVarInt(playerid, #varFlood_venderprods, gettime() + 120);
	SetPVarInt(playerid, #varFlood_propinamat, gettime() + 120);
	SetPVarInt(playerid, #varFlood_caixaeletronico, gettime());

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	//  Uma mensagem enviada a jogadores VIP maior que 0...
	if (PlayerInfo[playerid][pVIP] > 0)
	{
		new vip_nivel = Player_GetVIP(playerid);

		format(string, sizeof(string), "%s{FFFFFF}, você é um jogador {%s}%s", PlayerName[playerid], GetVipColor(playerid), VIP_GetName(vip_nivel));
		SendClientMessage(playerid, 0x00CCFFFF, string);
		
		new sql_string[256];
		mysql_format(MySQL_Handle, sql_string, sizeof sql_string, "SELECT DATE_FORMAT(vip_vencimento, '%%d/%%m/%%Y %%H:%%i:%%s') as vip_vencimento FROM `player` WHERE `id` = '%d' AND CURRENT_TIMESTAMP() < `vip_vencimento` LIMIT 1", PlayerInfo[playerid][pID]);
		mysql_tquery(MySQL_Handle, sql_string, "onPlayerVipCheck", "d", playerid);
	}

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	CallRemoteFunction("OnPlayerHouseCheck", "d", playerid);

	// O armanezamento e verificação do serial (gpci) e IP da internet
	new serial[75];

	gpci(playerid, serial, sizeof(serial));
	format(PlayerInfo[playerid][pSERIAL], 256, serial);

	format(string, sizeof string, "SERIAL: %s: %s.", PlayerName[playerid], serial);
	server_log("serial", string);

	// Aviso de passe ativo;
	if (WeeklyPassInfo[wpInProgress])
		SendMsgF(playerid, 0x40C94CFF, "Confira o passe de recompensas {FFFFFF}%s {40C94C}e ganhe prêmios com base na sua atividade ({00FF00}/infopasse{40C94C}).", WeeklyPassInfo[wpName]);

	// Avisa o jogador do servidor ter sido atualizado;
	if (lastLoginTs < Version_GetDate())
		SendClientMessage(playerid, 0x45CF40FF, "O SERVIDOR ATUALIZOU! Confira as novidades usando {FFFFFF}/atualizacao{45CF40}!");

	// VIP FREE
	#if VIP_FREE_ACTIVE
		Bonus_SetVIP(playerid, SOCIO_EXTREME, 7);
	#endif

	// #if defined _inc_discord_connector
	// 	if (PlayerInfo[playerid][pDiscord] != 0)
	// 		Socio_GetDiscordRole(playerid);
	// #endif
	
	// ----------------------------------------------------------------------------------------------------------------------------------------------
	return 1;
}

static Account_SetORMVars(playerid) {
	new ORM:ormid = PlayerInfo[playerid][ORM_ID];

	// API Discord:
	orm_addvar_string(ormid, PlayerInfo[playerid][pDiscord], 26, "discord");

	#if SERVER_ID == 3
		orm_addvar_int(ormid, ConsumableInfo[playerid][foodActive], "food_active");
	#endif

	// Status do jogo:
	orm_addvar_int(ormid, PlayerInfo[playerid][pVIP], "vip_nivel");
	orm_addvar_int(ormid, PlayerInfo[playerid][pLevel], "level");
	orm_addvar_int(ormid, PlayerInfo[playerid][pExp], "respeitos");
	orm_addvar_int(ormid, PlayerInfo[playerid][pConnectTime], "horas_jogadas");
	orm_addvar_int(ormid, PlayerInfo[playerid][pWanted], "nivel_procurado");
	orm_addvar_int(ormid, PlayerInfo[playerid][pSkin], "skin");

	// Poder aquisitivo:
	orm_addvar_int(ormid, PlayerInfo[playerid][pMoney], "dinheiro");
	orm_addvar_int(ormid, PlayerInfo[playerid][pConta], "dinheiro_banco");
	orm_addvar_int(ormid, PlayerInfo[playerid][pOuros], "ouros");
	orm_addvar_int(ormid, PlayerInfo[playerid][pCashVip], "cash");

	// Necessidades:
	orm_addvar_float(ormid, PlayerInfo[playerid][pFome], "fome");
	orm_addvar_float(ormid, PlayerInfo[playerid][pSede], "sede");

	// Comportamento:
	orm_addvar_int(ormid, PlayerInfo[playerid][pKills], "assassinatos");
	orm_addvar_int(ormid, PlayerInfo[playerid][pDeaths], "mortes");

	// Dados
	orm_addvar_string(ormid, PlayerInfo[playerid][pLaastLogin], 128, "ultimo_login");
	orm_addvar_int(ormid, PlayerInfo[playerid][pPayDay], "timer_payday");
	orm_addvar_int(ormid, PlayerInfo[playerid][pPegouVIP], "vip_pegou");

	// Estado do jogador:
	orm_addvar_int(ormid, PlayerInfo[playerid][pMuted], "mutado");

	orm_addvar_int(ormid, PlayerInfo[playerid][pCrimes], "crimes");
	orm_addvar_int(ormid, PlayerInfo[playerid][pContratos], "contratos");
	orm_addvar_int(ormid, PlayerInfo[playerid][pMinhasApreensoes], "apreensoes");
	orm_addvar_int(ormid, PlayerInfo[playerid][pMorteSuspeito], "suspeitos_mortos");

	orm_addvar_int(ormid, PlayerInfo[playerid][pExplosives], "explosivos");
	orm_addvar_int(ormid, PlayerInfo[playerid][pSafeExplosivos], "safe_explosivos");
	orm_addvar_int(ormid, PlayerInfo[playerid][pCigarros], "cigarros");
	orm_addvar_int(ormid, PlayerInfo[playerid][pPixador], "pixador");
	orm_addvar_int(ormid, PlayerInfo[playerid][pLottoNr], "lotto_number");
	orm_addvar_int(ormid, PlayerInfo[playerid][pEmprego], "emprego_1");
	orm_addvar_int(ormid, PlayerInfo[playerid][pEmprego2], "emprego_2");
	orm_addvar_int(ormid, PlayerInfo[playerid][pCaixinha], "caixinha");
	orm_addvar_int(ormid, PlayerInfo[playerid][pHeadValue], "head_value_h");
	orm_addvar_int(ormid, PlayerInfo[playerid][pHeadValueT], "head_value_t");
	orm_addvar_int(ormid, PlayerInfo[playerid][pMembro], "org_membro");
	orm_addvar_int(ormid, PlayerInfo[playerid][pCargo], "org_cargo");
	orm_addvar_int(ormid, PlayerInfo[playerid][pJailed], "jailed_id");
	orm_addvar_int(ormid, PlayerInfo[playerid][pJailTime], "jailed_time");
	orm_addvar_int(ormid, PlayerInfo[playerid][pSalario], "salario");

	orm_addvar_int(ormid, PlayerInfo[playerid][pLimparb], "mafioso_ficha");
	orm_addvar_int(ormid, PlayerInfo[playerid][pHeadRespect], "head_respect_h");
	orm_addvar_int(ormid, PlayerInfo[playerid][pHeadRespectT], "head_respect_t");
	orm_addvar_int(ormid, PlayerInfo[playerid][pTitulo], "titulo_id");
	orm_addvar_int(ormid, PlayerInfo[playerid][pCapacete], "capacete");
	orm_addvar_int(ormid, PlayerInfo[playerid][pMats], "materiais");
	orm_addvar_int(ormid, PlayerInfo[playerid][produtosMateriais], "materiais_produtos");
	orm_addvar_int(ormid, PlayerInfo[playerid][pDrogas], "maconha");
	orm_addvar_int(ormid, PlayerInfo[playerid][pDrogas2], "cocaina");
	orm_addvar_int(ormid, PlayerInfo[playerid][pDrogas3], "crack");
	orm_addvar_int(ormid, PlayerInfo[playerid][pHitSoundID], "hit_sound_id");
	orm_addvar_int(ormid, PlayerInfo[playerid][pHitSound][0], "hit_sound_1");
	orm_addvar_int(ormid, PlayerInfo[playerid][pHitSound][1], "hit_sound_2");
	orm_addvar_int(ormid, PlayerInfo[playerid][pSkinServico], "job_skin");
	orm_addvar_int(ormid, PlayerInfo[playerid][pAjustado], "jail_ajusted");
	orm_addvar_int(ormid, PlayerInfo[playerid][pHAjustado], "hospital_ajusted");
	orm_addvar_int(ormid, PlayerInfo[playerid][QuantidadeBan], "banimentos");
	orm_addvar_int(ormid, PlayerInfo[playerid][pGalao], "galao");
	orm_addvar_int(ormid, PlayerInfo[playerid][pIsqueiro], "isqueiro");
	orm_addvar_int(ormid, PlayerInfo[playerid][pMatouSniper], "sniper_kills");
	orm_addvar_int(ormid, PlayerInfo[playerid][pPatins], "patins");
	orm_addvar_int(ormid, PlayerInfo[playerid][pFerSkill], "skill_ferramentas");
	orm_addvar_int(ormid, PlayerInfo[playerid][pDetSkill], "skill_detetive");
	orm_addvar_int(ormid, PlayerInfo[playerid][pAdvogadoSkill], "skill_advogado");
	orm_addvar_int(ormid, PlayerInfo[playerid][pMedicoSkill], "skill_medico");

	orm_addvar_float(ormid, PlayerInfo[playerid][pHealth], "health");
	orm_addvar_float(ormid, PlayerInfo[playerid][pArmour], "armour");

	orm_addvar_int(ormid, PlayerInfo[playerid][numeroCelular], "phone_number");
	orm_addvar_int(ormid, PlayerInfo[playerid][pGunLic], "licenca_armas");
	orm_addvar_int(ormid, PlayerInfo[playerid][pLastContrato], "last_contrato");
	orm_addvar_int(ormid, PlayerInfo[playerid][pWarns], "avisos");
	orm_addvar_int(ormid, PlayerInfo[playerid][pWarnsAdmin], "avisos_admin");
	orm_addvar_int(ormid, PlayerInfo[playerid][pMarried], "married");

	orm_addvar_int(ormid, _:Player_Spawn[playerid][TypeSpawn], "spawn_type");
	orm_addvar_int(ormid, Player_Spawn[playerid][SpawnID], "spawn_id");
	
	orm_addvar_int(ormid, PlayerInfo[playerid][pSafeDrogas], "safe_maconha");
	orm_addvar_int(ormid, PlayerInfo[playerid][pSafeDrogas2], "safe_cocaina");
	orm_addvar_int(ormid, PlayerInfo[playerid][pSafeDrogas3], "safe_crack");
	orm_addvar_int(ormid, PlayerInfo[playerid][psMats], "safe_materiais");
	orm_addvar_int(ormid, PlayerInfo[playerid][pLuta], "luta");
	orm_addvar_int(ormid, PlayerInfo[playerid][orgPrendeu], "org_prendeu");
	orm_addvar_int(ormid, PlayerInfo[playerid][pArenaKills], "arena_kills");
	orm_addvar_int(ormid, PlayerInfo[playerid][pBan], "banido");
	orm_addvar_int(ormid, PlayerInfo[playerid][pCidade], "cidade");
	orm_addvar_int(ormid, PlayerInfo[playerid][pAgendado], "jail_agended");
	orm_addvar_int(ormid, PlayerInfo[playerid][pTempoAgendado], "jail_time_agended");
	orm_addvar_int(ormid, PlayerInfo[playerid][pPrisaoAdmin], "prisao_admin");
	orm_addvar_int(ormid, PlayerInfo[playerid][pTrocaNick], "trocas_nick");
	orm_addvar_int(ormid, PlayerInfo[playerid][pTituloP], "titulo_perma");
	orm_addvar_int(ormid, PlayerInfo[playerid][pAnuncioP], "anuncio_perma");
	orm_addvar_int(ormid, PlayerInfo[playerid][pAllowWeapons], "allow_weapons");
	orm_addvar_int(ormid, PlayerInfo[playerid][pToggleNoob], "toggle_noob");
	orm_addvar_int(ormid, PlayerInfo[playerid][pRoubou], "roubou");
	orm_addvar_int(ormid, PlayerInfo[playerid][pBancoFiliado], "banco_filiado");
	orm_addvar_int(ormid, PlayerInfo[playerid][pHospital], "hospital");
	orm_addvar_int(ormid, PlayerInfo[playerid][pTempoHospital], "tempo_hospital");
	orm_addvar_int(ormid, PlayerInfo[playerid][pAutoCaixinha], "auto_caixinha");
	orm_addvar_int(ormid, PlayerInfo[playerid][pChatVip], "chat_vip");
	orm_addvar_int(ormid, PlayerInfo[playerid][style_view_rg], "style_view_rg");
	orm_addvar_int(ormid, PlayerInfo[playerid][pChatMorro], "chat_morro");
	orm_addvar_int(ormid, PlayerInfo[playerid][pLimparPrisoes], "limpar_prisoes");
	orm_addvar_int(ormid, PlayerInfo[playerid][pDoenca], "doenca");
	orm_addvar_int(ormid, PlayerInfo[playerid][pIdeologia], "ideologia");

	orm_addvar_int(ormid, PlayerInfo[playerid][pHidePar], "hide_par");

	orm_addvar_string(ormid, PlayerCrime[playerid][pAccusedof], 255, "crime_id");
	orm_addvar_string(ormid, PlayerCrime[playerid][pVictim], 255, "crime_relato");
	orm_addvar_string(ormid, PlayerInfo[playerid][pAdminAgendou], 255, "jail_agendou");
	orm_addvar_string(ormid, PlayerInfo[playerid][pMotivoAgendou], 255, "jail_motivo");

	orm_addvar_int(ormid, PlayerInfo[playerid][casa_alugada], "casa_alugada");

	orm_addvar_string(ormid, PlayerInfo[playerid][pMarriedTo], MAX_PLAYER_NAME+1, "casado_com");
	orm_addvar_string(ormid, PlayerInfo[playerid][pTituloText], 75, "titulo_text");

	orm_addvar_string(ormid, PlayerInfo[playerid][pPrisaoData], 60, "prisao_data");
	orm_addvar_string(ormid, PlayerInfo[playerid][pRespPrisao], 45, "resp_prisao");
	orm_addvar_string(ormid, PlayerInfo[playerid][pMotivoPrisao], 200, "motivo_prisao");

	orm_addvar_string(ormid, LastPosInfo[playerid][lastPosString], 200, "player_info_lastpos");

	orm_addvar_string(ormid, PlayerInfo[playerid][pLastWeapons], 250, "player_weapons");

	orm_addvar_int(ormid, WeeklyPassPlayerInfo[playerid][wppWeeklyPassID], "weeklyPassId");
	orm_addvar_int(ormid, WeeklyPassPlayerInfo[playerid][wppAvailable], "weeklyPassAvailable");
	orm_addvar_int(ormid, WeeklyPassPlayerInfo[playerid][wppDay], "weeklyPassDay");
	orm_addvar_int(ormid, WeeklyPassPlayerInfo[playerid][wppPlayedTime], "weeklyPassPlayedTime");
}

stock Account_Load(playerid) {
	SetPVarInt(playerid, "AccountBeingLoaded", 1);
	Account_SetORMVars(playerid);
	orm_load(PlayerInfo[playerid][ORM_ID], "OnPlayerAccountLoaded", "dd", playerid, 1);
}

stock Account_Register(playerid) {
	Account_SetORMVars(playerid);
	format(PlayerInfo[playerid][pLaastLogin], 30, GetCurrentDateHour(ONLY_CURRENT_ALL));
	orm_save(PlayerInfo[playerid][ORM_ID], "OnPlayerAccountLoaded", "dd", playerid, 0);
}

CALLBACK:OnPlayerAccountLoaded(playerid, is_login)
{
	new E_ORM_ERROR:orm_status = orm_errno(PlayerInfo[playerid][ORM_ID]);
	if (orm_status == ERROR_OK) {
		SetPVarInt(playerid, "AccountBeingLoaded", 0);

		if (is_login) {
			if (Player_GetNivel(playerid) > 20) {
				CallLocalFunction("OnDiscordLink", "i", playerid);
			}
			else {
				CallLocalFunction("OnPlayerLogin", "i", playerid);
			}
		}
		else
			CallLocalFunction("OnPlayerRegister", "i", playerid);
	}
	else if (orm_status == ERROR_NO_DATA) {
		SendClientMessage(playerid, COLOR_LIGHTRED, "Falha ao carregar sua conta... Não foi possível encontrá-la.");
		KickEx(playerid);
	}
	else
	{
		SendClientMessage(playerid, COLOR_LIGHTRED, "Falha ao carregar sua conta... Não foi possível carregar os dados.");
		KickEx(playerid);
	}
	return 1;
}

static Account_Loading(playerid)
{
	new ORM: ormid = 
		PlayerInfo[playerid][ORM_ID] = orm_create("player", MySQL_Handle);

	orm_addvar_int(ormid, PlayerInfo[playerid][pID], "id");
	orm_addvar_string(ormid, PlayerName[playerid], MAX_PLAYER_NAME, "nome");
	orm_addvar_string(ormid, PlayerInfo[playerid][pKey], 65, "senha");
	orm_addvar_string(ormid, PlayerInfo[playerid][pEmail], 128, "e-mail");
	orm_addvar_string(ormid, PlayerInfo[playerid][pSERIAL], 60, "serial");
	orm_addvar_int(ormid, PlayerInfo[playerid][pSex], "sexo");

	orm_setkey(ormid, "nome");
	orm_load(ormid, "OnPlayerLoginCheck", "dd", playerid, g_MysqlRaceCheck[playerid]);

	return 1;
}

timer loadLoginTimer[120](playerid)
{
	static string[10];

	format(string, sizeof(string), "%d%", percent_loadLogin[playerid]);
	if (IsValidDynamicPlayerTextDraw(playerid, loadBarraTela[playerid][0]))
		PlayerTextDrawSetString(playerid, loadBarraTela[playerid][0], string);

	if (percent_loadLogin[playerid] % 20 == 0)
		Chat_Clear(playerid, 20);

	stop loadLogin_Timer[playerid];
	loadLogin_Timer[playerid] = defer loadLoginTimer(playerid);

	// CreateLoadSpinPTD(playerid);
	// PlayerTextDrawShow(playerid, loadBarraTela[playerid][1]);

	switch (percent_loadLogin[playerid])
	{
	    case 0:
	    {
			TogglePlayerSpectating(playerid, true);
	        SetPlayerVirtualWorld(playerid, 800);
			loadSpinPos[playerid] = 0;

		    for(new text; text != sizeof loadTela; text++) {
				if (IsValidDynamicTextDraw(loadTela[text]))
					TextDrawShowForPlayer(playerid, loadTela[text]);
			}
			Streamer_UpdateEx(playerid, -1730.8575, 1310.9913, 29.9459, 800, 0);
		}
		case 100:
		{
			InterpolateCameraPos(playerid, -1730.8575, 1310.9913, 29.9459, -1638.7533, 1409.5505, 9.0138, 8000); // Camera da Tela de Login
			InterpolateCameraLookAt(playerid, -1638.7533, 1409.5505, 9.0138, -1638.7533, 1409.5505, 9.0138, 10000);

	        HideLoadTela(playerid);
		}
	}
	percent_loadLogin[playerid] ++;
}

hook OnPlayerResetVars(playerid) {
	SetPVarInt(playerid, "LoginChecked", 0);
}

hook OnPlayerConnect(playerid) 
{
	// Pegar IP do jogador
	GetPlayerIp(playerid, PlayerIP[playerid], MAX_PLAYER_IP);

	// Máximo de conexão permitida no mesmo IP
	if (GetPlayersOnIp(PlayerIP[playerid]) > 4 && strcmp(PlayerIP[playerid], "181.214.48.170")) {
		SendClientMessage(playerid, COLOR_SAMP, "Limite máximo de conexão foi exedido para o seu IP.");
		SendClientMessage(playerid, COLOR_SAMP, "Para mais informações entre em nosso discord: "SERVER_DISCORD"'");
		KickEx(playerid);
	}
	else if(Login_CheckIP(playerid, PlayerIP[playerid])) {
		SendClientMessage(playerid, COLOR_SAMP, "[Firewall] Acesso não autorizado! Limite de jogadores se conectando por IP excedido.");
		KickEx(playerid);
		BlockIpAddress(PlayerIP[playerid], 3 * 60 * 1000);
	}
	GetPlayerName(playerid, PlayerName[playerid], MAX_PLAYER_NAME);

	if (!strfind(PlayerName[playerid], "Logando_", false, 0)) {
		SendClientMessage(playerid, COLOR_LIGHTRED, "Você está tentando se conectar com um nick indevido. Corrija e tente novamente!");
		return KickEx(playerid);
	}
	SetRandomName(playerid);

	CreatePlayerLoginTD(playerid);

	static stringtd[5];
	format(stringtd, sizeof(stringtd), "%d", ContarJogadores());
	if (IsValidDynamicTextDraw(login_textdraws[8]))
		TextDrawSetString(login_textdraws[8], stringtd);

	new string[MAX_PLAYER_NAME+22];
	format(string, sizeof(string), "Bem vindo, ~n~~w~%s", PlayerName[playerid]);
	if (IsValidDynamicPlayerTextDraw(playerid, login_ptextdraws[0][playerid]))
		PlayerTextDrawSetString(playerid, login_ptextdraws[0][playerid], string);

    // Criando os textdraw
    CreatePlayerLoadTela(playerid);

    // Cor do jogador na tela de login;
	SetPlayerColor(playerid, COLOR_GRAD);

	// Check
	g_MysqlRaceCheck[playerid]++;
	CallLocalFunction("OnPlayerResetVars", "i", playerid);
	CallLocalFunction("OnCreatePlayerTextDraws", "i", playerid);
	CreatePlayerTD_Inventory(playerid);
	Account_Loading(playerid);

    // Barra de carregamento da tela de login
	PlayerTextDrawShow(playerid, loadBarraTela[playerid][0]);
	loadLogin_Timer[playerid] = defer loadLoginTimer(playerid);

    // Inicia a música de login
	Login_PlayMusic(playerid);

    // Quando um hitman está com o nick escondido
    foreach(new i : Player) {
 	    if (!GetPlayerSeeNick(playerid))
			ShowPlayerNameTagForPlayer(playerid, i, false);
 	}

    return 1;
}

stock Register_ShowDialog(playerid)
{
	if(IsAndroidPlayer(playerid)) {
		ShowPlayerDialog(playerid, 2, DIALOG_STYLE_PASSWORD,
		""C_GRAY2"CADASTRO",

		""C_WHITE"Para se cadastrar digite sua "C_MONEY"SENHA "C_WHITE"abaixo:\n\
		Digite uma senha segura com letras, numeros e caracteres\n\
		OBS: Voce podera mudar sua senha depois, caso precise!",

		"Concluido", "Fechar");
	}
	else {
		ShowPlayerDialog(playerid, 2, DIALOG_STYLE_PASSWORD,
		""C_GRAY2"CADASTRO",

		""C_WHITE"Para se cadastrar digite sua "C_MONEY"SENHA "C_WHITE"abaixo:\n\
		Digite uma senha segura com letras, números e caracteres\n\
		OBS: Você poderá mudar sua senha depois, caso precise!",

		""C_MONEY"Concluido", "Fechar");
	}
}

stock Login_ShowDialog(playerid)
{
	new loginString[900];
	if(IsAndroidPlayer(playerid)) {
		format(loginString, sizeof(loginString), ""C_WHITE"Bem vindo, "C_MONEY"%s!\n\n\
		"C_WHITE"Voce ja possui uma conta registrada com este nome em nosso servidor.\n\
		Por favor, informe a senha de login registrada para continuar.\n\n\
		"C_GRAY"-\tAperte em 'ESQUECI MINHA SENHA' no lado esquerdo,\n\
		-\tcaso tenha, e associou seu email a sua conta.\n\n\
		"C_WHITE"OBS: Mantenha sua senha segura, para nao ter sua conta roubada!", PlayerName[playerid]);

		ShowPlayerDialog(playerid, 1, DIALOG_STYLE_PASSWORD, ""C_GRAY2"Acessando...", loginString, "Concluido", "Fechar");
	}
	else {
		format(loginString, sizeof(loginString), ""C_WHITE"Bem vindo, "C_MONEY"%s!\n\n\
		"C_WHITE"Você já possui uma conta registrada com este nome em nosso servidor.\n\
		Por favor, informe a senha de login registrada para continuar.\n\n\
		"C_GRAY"-\tAperte em 'ESQUECI MINHA SENHA' no lado esquerdo,\n\
		-\tcaso tenha, e associou seu email à sua conta.\n\n\
		"C_WHITE"OBS: Mantenha sua senha segura, para não ter sua conta roubada!", PlayerName[playerid]);

		ShowPlayerDialog(playerid, 1, DIALOG_STYLE_PASSWORD, ""C_GRAY2"Acessando...", loginString, ""C_MONEY"Concluido", "Fechar");
	}
}

stock showTelaLogin(playerid)
{
	if(GetPVarInt(playerid, "LoginChecked") == 1) {
		if (IsPlayerRegistered(playerid)) {
			if (IsValidDynamicPlayerTextDraw(playerid, login_ptextdraws[1][playerid]))
				PlayerTextDrawSetString(playerid, login_ptextdraws[1][playerid], "~w~Sua conta ~g~~h~esta cadastrada ~n~~w~Clique em 'Conectar', abaixo:");

			if (IsValidDynamicPlayerTextDraw(playerid, login_ptextdraws[2][playerid]))
				PlayerTextDrawSetString(playerid, login_ptextdraws[2][playerid], "Conectar");
		} else {
			if (IsValidDynamicPlayerTextDraw(playerid, login_ptextdraws[1][playerid]))
				PlayerTextDrawSetString(playerid, login_ptextdraws[1][playerid], "~w~Sua conta ~r~~h~nao esta cadastrada ~n~~w~Clique em 'Cadastre-se', abaixo:");

			if (IsValidDynamicPlayerTextDraw(playerid, login_ptextdraws[2][playerid]))
				PlayerTextDrawSetString(playerid, login_ptextdraws[2][playerid], "Cadastre-se");
		}
	}

	for(new x; x != sizeof (login_textdraws); x++)
	    TextDrawShowForPlayer(playerid, login_textdraws[x]);

    for (new text; text != sizeof(login_ptextdraws); text++)
		if (IsValidDynamicPlayerTextDraw(playerid, login_ptextdraws[text][playerid]))
			PlayerTextDrawShow(playerid, login_ptextdraws[text][playerid]);

	SelectTextDraw(playerid, 0xCFD1D0FF);

    return 1;
}

stock Login_Hidescreen(playerid)
{
	for(new x; x != sizeof (login_textdraws); x++) 
	    TextDrawHideForPlayer(playerid, login_textdraws[x]);

    for(new text; text != sizeof(login_ptextdraws); text++)
        PlayerTextDrawHide(playerid, login_ptextdraws[text][playerid]);
	
	CancelSelectTextDraw(playerid);
}

stock HideLoadTela(playerid)
{
	for(new text; text != sizeof(loadTela); text++)
	    TextDrawHideForPlayer(playerid, loadTela[text]);
		
	PlayerTextDrawHide(playerid, loadBarraTela[playerid][0]);
	PlayerTextDrawHide(playerid, loadBarraTela[playerid][1]);

	stop loadLogin_Timer[playerid];

	showTelaLogin(playerid);
}

hook OnPlayerDisconnect(playerid, reason) {

	if (Admin_GetNivel(playerid))
        SetCountAdmin(CountAdmin()-1);

	percent_loadLogin[playerid] = 0;

	stop loadLogin_Timer[playerid];

    g_MysqlRaceCheck[playerid]++;

    return 1;
}

hook OnGameModeInit() {

	Login_LoadMusic();

    CreateLoadTela();
    CreateTelaLogin();

    return 1;
}

CALLBACK:OnPlayerLoginCheck(playerid, race_check)
{
	/*	race condition check:
		player A connects -> SELECT query is fired -> this query takes very long
		while the query is still processing, player A with playerid 2 disconnects
		player B joins now with playerid 2 -> our laggy SELECT query is finally finished, but for the wrong player

		what do we do against it?
		we create a connection count for each playerid and increase it everytime the playerid connects or disconnects
		we also pass the current value of the connection count to our OnPlayerDataLoaded callback
		then we check if current connection count is the same as connection count we passed to the callback
		if yes, everything is okay, if not, we just kick the player
	*/
	if (race_check != g_MysqlRaceCheck[playerid]) {
        return KickEx(playerid);
    }

	orm_setkey(PlayerInfo[playerid][ORM_ID], "id");

	SetPVarInt(playerid, "LoginChecked", 1);

	new E_ORM_ERROR:orm_status = orm_errno(PlayerInfo[playerid][ORM_ID]);
	if(orm_status == ERROR_OK) {
		SetPlayerRegistered(playerid, true);

		if (IsValidDynamicPlayerTextDraw(playerid, login_ptextdraws[1][playerid]))
			PlayerTextDrawSetString(playerid, login_ptextdraws[1][playerid], "~w~Sua conta ~g~~h~esta cadastrada ~n~~w~Clique em 'Conectar', abaixo:");

		if (IsValidDynamicPlayerTextDraw(playerid, login_ptextdraws[2][playerid]))
			PlayerTextDrawSetString(playerid, login_ptextdraws[2][playerid], "Conectar");

		if (GetPVarInt(playerid, "LoginClicked") == 1) 
			Login_ShowDialog(playerid);
	}
	else if(orm_status == ERROR_NO_DATA) {
		SetPlayerRegistered(playerid, false);

		if (IsValidDynamicPlayerTextDraw(playerid, login_ptextdraws[1][playerid]))
			PlayerTextDrawSetString(playerid, login_ptextdraws[1][playerid], "~w~Sua conta ~r~~h~nao esta cadastrada ~n~~w~Clique em 'Cadastre-se', abaixo:");

		if (IsValidDynamicPlayerTextDraw(playerid, login_ptextdraws[2][playerid]))
			PlayerTextDrawSetString(playerid, login_ptextdraws[2][playerid], "Cadastre-se");

		if (GetPVarInt(playerid, "LoginClicked") == 1) 
			Register_ShowDialog(playerid);
	}
	else
	{
		SendClientMessage(playerid, COLOR_RED, "Não foi possível carregar sua conta! Relogue ou entre em contato com a administração.");
		KickEx(playerid);
	}
	return 1;
}

CALLBACK: OnPlayerRegister(playerid)
{
	// Está logado;
	Player_SetLogado(playerid, true);

	// Setar o nick após logar
	SetPlayerName(playerid, PlayerName[playerid]);

    Login_Hidescreen(playerid);

	SendClientMessage(playerid, COLOR_ORANGE, "Parabéns, você criou sua conta!");
	SetPVarInt(playerid, "LastPosLoadded", 1);

	Player_SetNivel(playerid, 3);
	Player_AddMoney(playerid, 10000);
	Player_SetMoneyBank(playerid, 40000);

	PlayerInfo[playerid][numeroCelular] = 0;
	PlayerInfo[playerid][casa_alugada] = -1;
	PlayerInfo[playerid][pPayDay] = 30 * 60;

	removerDinheiroGoverno(8000);

	PlayerInfo[playerid][pEmprego] = 0;
	PlayerInfo[playerid][pEmprego2] = 0;
	PlayerInfo[playerid][pKills] = 0;
	PlayerInfo[playerid][pDeaths] = 0;

	// Definindo fome e sede 100% ao registrar
	PlayerInfo[playerid][pHealth] = 100.0;
	PlayerInfo[playerid][pFome] = 100.0;
	PlayerInfo[playerid][pSede] = 100.0;

	gNoticias[playerid] = 1;
	Chat_Organizacao[playerid] = 1;
	TogglePlayerControllable(playerid, false);
	Chat_Clear(playerid, 8);
	SetPlayerCameraPos( playerid, 1364.4369,-872.8301,97.3800);
	SetPlayerCameraLookAt( playerid, 1411.9713,-819.7601,80.6194);
	SetPlayerInterior(playerid, 0);
	PlayerPlaySound(playerid,1139,0.0,0.0,0.0);
	SetPlayerVirtualWorld(playerid,playerid+1);
	ShowPlayerDialog(playerid,10,DIALOG_STYLE_MSGBOX,"Escolha seu sexo:","{FFFFFF}Escolha seu sexo corretamente\n\nOBS: Você não terá outra chance de escolher seu sexo\n","Masculino","Feminino");

	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {

    if (dialogid == 1)
	{
		if (!response) {
            KickEx(playerid);
            return SendClientMessage(playerid, -1, "Você foi kickado do servidor.");
        }

		new HASH_Password[65];
		SHA256_PassHash(inputtext, PASSWORD_HASH, HASH_Password, 65);

		if (strcmp(HASH_Password, PlayerInfo[playerid][pKey]) == 0) {
			Account_Load(playerid);
		} else {
			SendClientMessage(playerid, -1, "Você digitou a senha incorretamente.");
			Login_ShowDialog(playerid);
		}
		return 1;
	}
	else if (dialogid == 2)
	{
		if (!response) {
            KickEx(playerid);
            return SendClientMessage(playerid, -1, "Você foi kickado do servidor.");
        }
		if (!strlen(inputtext)) {
			Register_ShowDialog(playerid);
            return 1;
   		}

		SHA256_PassHash(inputtext, PASSWORD_HASH, PlayerInfo[playerid][pKey], 65);
		Account_Register(playerid);
		return 1;
	}
	else if(dialogid == 10)
	{
	   	if(response == 0)
     	{
			TogglePlayerControllable(playerid, false);
        	Chat_Clear(playerid, 100);
            PlayerInfo[playerid][pSex] = 2;
            SetPlayerSkin(playerid, 216);
            PlayerInfo[playerid][pSkin] = 216;
            IniciarTutorial(playerid);

            return true;
	   	}
	   	if(response == 1)
     	{
  			TogglePlayerControllable(playerid, false);
        	Chat_Clear(playerid, 100);
            PlayerInfo[playerid][pSex] = 1;
            SetPlayerSkin(playerid, 23);
            PlayerInfo[playerid][pSkin] = 23;
            IniciarTutorial(playerid);
			
			return true;
	   	}
       	return true;
    }

    return 0;
}

new NumeroTutorial[MAX_PLAYERS];

stock IniciarTutorial(playerid)
{
	SetPlayerVirtualWorld(playerid, 0);
	NumeroTutorial[playerid] = 0;
	PlayerInfo[playerid][pTimerTuto] = SetTimerEx("STuto", 5000, false, "i", playerid);

	ShowPlayerMessage(playerid, "Assista ao tutorial prestando bastante atencao.", 2500);
	return 1;
}

CALLBACK: STuto(playerid)
{
    NumeroTutorial[playerid] ++;

	new numero = NumeroTutorial[playerid];

	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

	Chat_Clear(playerid, 20);

	new tempo = 5000;

	if(numero == 1)
	{
		SetPlayerCameraPos(playerid, 1398.8627,-1757.0109,20.6024);
		SetPlayerCameraLookAt(playerid, 1378.1812,-1756.8230,13.6344);
		ShowPlayerBaloonInfo(playerid, "~>~Agencia de Empregos~n~~n~Aqui voce pode conferir as melhores oportunidades de emprego e conseguir ganhar dinheiro na cidade.", tempo);
	}
	else if(numero == 2)
	{
		SetPlayerCameraPos(playerid, 1435.75, -1716.61, 23.29);
		SetPlayerCameraLookAt(playerid, 1431.00, -1713.19, 22.00);
  		ShowPlayerBaloonInfo(playerid, "~>~Centro de licencas~n~~n~Aqui voce pode conquistar a sua carteira de motorista de veiculos terrestres, aereos, maritimos e tambem o porte de armas.", tempo);
	}
	else if(numero == 3)
	{
		SetPlayerCameraPos(playerid, 1218.0953,-1361.8190,32.1392);
		SetPlayerCameraLookAt(playerid, 1174.2048,-1322.3635,14.9922);
		ShowPlayerBaloonInfo(playerid, "~>~Hospital~n~~n~Aqui e o local onde os pacientes sao tratados, caso venham a morrer. Voce tambem pode trabalhar como medico nesse local.", tempo);
	}
	else if(numero == 4)
	{
		SetPlayerCameraPos(playerid, 1483.5536, -1139.2957, 37.4396);
		SetPlayerCameraLookAt(playerid, 1458.8859, -1137.4780, 24.0197);
		ShowPlayerBaloonInfo(playerid, "~>~CityBank LS~n~~n~Visite o banco para fazer suas transacoes financeiras como saques, depositos, tranferencias e outras negociacoes.", tempo);
	}
	else if(numero == 5)
	{
		SetPlayerCameraPos(playerid, 421.8315, -1478.4968, 44.5436);
		SetPlayerCameraLookAt(playerid, 460.7559, -1486.2715, 33.4897);
		ShowPlayerBaloonInfo(playerid, "~>~Lojas de Roupas~n~~n~Essas sao algumas das lojas de roupas da cidade. Em cada uma dela voce encontra diferentes roupas para comprar.", tempo);
	}
	else if(numero == 6)
	{
		SetPlayerCameraPos(playerid, 1343.0217, -1744.6333, 18.0360);
		SetPlayerCameraLookAt(playerid, 1351.5757, -1759.2378, 13.5078);
		ShowPlayerBaloonInfo(playerid, "~>~Mercado 24-7~n~~n~Esse e um dos mercados da cidade. Nas 24-7 voce pode comprar seu celular e tambem outros utensilios para iniciar sua vida na cidade", tempo);
	}
	else if(numero == 7)
	{
		SetPlayerCameraPos(playerid, 547.3825,-1247.9766,28.1095);
		SetPlayerCameraLookAt(playerid, 543.9026,-1291.0945,19.0916);
		ShowPlayerBaloonInfo(playerid, "~>~Concessionaria~n~~n~Visite a concessionaria de carros comuns para adquirir seu primeiro veiculo a um valor acessivel.", tempo);
    }
	else if(numero == 8)
	{
		SetPlayerCameraPos(playerid, 610.3228,-1217.1959,27.2716);
		SetPlayerCameraLookAt(playerid, 598.9510,-1248.4602,18.2635);
		ShowPlayerBaloonInfo(playerid, "~>~Revendedora e Seguradora~n~~n~Adquira um seguro para seus veiculos e tambem pode revende-los nesse local.", tempo);
    }
	else if(numero == 9)
	{
		SetPlayerCameraPos(playerid, 1477.5472, -1578.2375, 35.3198);
		SetPlayerCameraLookAt(playerid, 1479.4478, -1665.7400, 8.5532);
		ShowPlayerBaloonInfo(playerid, "~>~Praca Central~n~~n~Nesse local voce pode coletar seu presente e tambem encontrar seus amigos e conhecer novas pessoas.", tempo);
	}
	else if(numero == 10)
	{
		SetPlayerCameraPos(playerid, -244.8457,-1785.0955,18.1837);
		SetPlayerCameraLookAt(playerid, -198.2658,-1756.8746,5.4330);
		ShowPlayerBaloonInfo(playerid, "~>~Area de Eventos~n~~n~Nesse local voce pode encontrar seus amigos, conhecer novas pessoas, comprar comida e bebida e se divertir.", tempo);
	}
	else if(numero == 11)
	{
		SetPlayerCameraPos(playerid, 2077.5037,-1786.1108,21.2041);
		SetPlayerCameraLookAt(playerid, 2104.3296,-1805.6818,16.9381);
		ShowPlayerBaloonInfo(playerid, "~>~Well Pizza Stacked~n~~n~Visite esse restaurante para experimentar as deliciosas pizzas de Los Santos e a um bom custo.", tempo);
    }
	else if(numero == 12)
	{
		tempo = 3000;
		SetPlayerCameraPos(playerid, 2435.2654,-1527.1410,33.7390);
		SetPlayerCameraLookAt(playerid, 2418.1079,-1511.2660,27.3576);
		ShowPlayerBaloonInfo(playerid, "~>~Cluckin Bell~n~~n~Visite tambem esse outro restaurante para provar do saboroso e unico frango frito da cidade de Los Santos.", tempo);
    }
	else if(numero == 13)
	{
		tempo = 3000;
		SetPlayerCameraPos(playerid, 835.0854, -1614.7699, 23.6787);
		SetPlayerCameraLookAt(playerid, 790.9948, -1622.5665, 12.5388);
		ShowPlayerBaloonInfo(playerid, "~>~Burger Shot~n~~n~Conheca tambem o melhor hamburguer da cidade. Aqui tem bons precos e muito hamburguer pra voce curtir com os amigos.", tempo);
    }
    else if(numero == 14)
	{
		SetPlayerCameraPos(playerid, 1579.8325, -1530.1831, 16.5267);
		SetPlayerCameraLookAt(playerid, 1607.3809, -1560.1881, 14.1786);
		ShowPlayerBaloonInfo(playerid, "~>~Mercado Negro~n~~n~Esse local e controlado pela mafia e nele voce pode comprar diversos materiais ilicitos, como sementes, caixa de armas e explosivos", tempo);
    }
	else if(numero == 15)
	{
		SetPlayerCameraPos(playerid, 1841.9901,-1277.1450,88.1124);
		SetPlayerCameraLookAt(playerid, 1955.4200,-1176.6489,20.0234);
		ShowPlayerBaloonInfo(playerid, "~>~Territorios de Gangues~n~~n~Esses locais sao usados para producao de ~y~cocaina~w~, que sao vendidas pelos gangsters", tempo);
    }
	else if(numero == 16)
	{
		tempo = 3000;
		SetPlayerCameraPos(playerid, 205.1730,-1837.7582,37.4479);
		SetPlayerCameraLookAt(playerid, 148.3535,-1935.1472,3.7734);
		ShowPlayerBaloonInfo(playerid, "~>~Territorios de Mafias~n~~n~Esses locais sao usados para producao de ~r~~h~crack~w~, que sao vendidas pelos mafiosos", tempo);
    }
	else if(numero == 17)
	{
		tempo = 3000;
		SetPlayerCameraPos(playerid, -1687.2128,-2199.2786,56.0263);
		SetPlayerCameraLookAt(playerid, -1635.3901,-2239.1526,36.5363);
		ShowPlayerBaloonInfo(playerid, "~>~Territorios de Terroristas~n~~n~Esses locais sao usados para producao de ~y~~h~heroina~w~, que sao vendidas pelos terroristas", tempo);
    }
	else if(numero == 18)
	{
		tempo = 3000;
		SetPlayerCameraPos(playerid, -150.7800,-1221.8470,22.0392);
		SetPlayerCameraLookAt(playerid, -84.6230,-1177.0579,5.0905);
		ShowPlayerBaloonInfo(playerid, "~>~Territorios de Motoqueiros~n~~n~Esses locais sao usados para producao de ~r~~h~metanfetamina~w~, que sao vendidas pelos motoqueiros", tempo);
    }
	else if(numero == 19)
	{
		SetPlayerCameraPos(playerid, 1703.2041, -1860.2837, 18.3539);
		SetPlayerCameraLookAt(playerid, 1711.2529, -1848.3650, 13.5635);
		ShowPlayerBaloonInfo(playerid, "~>~Seja bem vindo~n~~n~Aproveite e viva a vida aqui na cidade. Caso precise de ajuda, use ~y~/noob ~w~ou use ~y~/atendimento", tempo);
    }
    else if(numero >= 20)
    {
  		Chat_Clear(playerid, 40);
		PlayerInfo[playerid][pConta] = 3000;
		Player_AddMoney(playerid, PRICE_INICIO_NOVATO);

		StopAudioStreamForPlayer(playerid);

		callcmd::s(playerid, "Olá amigos, sou novo no servidor, alguém poderia me ajudar?");

		CallLocalFunction("OnPlayerLogin", "i", playerid);
		return 1;
    }
    PlayerInfo[playerid][pTimerTuto] = SetTimerEx("STuto", tempo, false, "i", playerid);
  	return true;
}