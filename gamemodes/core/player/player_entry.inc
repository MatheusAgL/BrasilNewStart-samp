#define		MODEL_VIEW_MESSAGE		1
#define		MODEL_VIEW_DIALOG		2

enum E_PLAYER
{
	ORM:ORM_ID,										// ID no ORM
	pID,											// ID global-player
	pLogged,										// Logado
	pKey[65],										// Senha
	pEmail[74],										// Seu e-mail
	pDiscord[26],									// Discord do player
	pLevel,											// Nível
	pMoney,											// Dinheiro na mão
	pVIP,											// VIP
	Timestamp:pVIPDate,								// Data do VIP
	pConnectTime,									// Horas jogadas
	pSalario,										// Salário do jogador (por PayDay)
	pPegouVIP,										// VIP gratuito (Login/Registro)
	pWanted,										// Nível de procurado
	Checkpoint,										// Checkpoint

	// Eventos
	pEvent,
	EventType:pEventType,
	pEventStage,

	// Modo agressivo
	bool:mAgressivo,

	// Mão direita
	bool:player_busy_hands,

	// Nome do objeto na mão direita
    right_hand_object_name[50],

	// Spawn
	pSpawn,

	// Auto Caixinha: Sócio Extreme
	bool:pAutoCaixinha,

	// Agendado na cadeia por um admin
	pAgendado,

	// Titulo ID usado
	pTitulo,

	// Titulo personalizado
	pTituloText[75],

	// Timer do Tutorial
	pTimerTuto,

	// Jogador está no hospital
	bool:pHospital,

	// Se o inventário foi carregado
	bool:pInventoryLoaded,

	bool:holdingExplosive,
	
	bool:pGalao,
	bool:pIsqueiro,
	bool:pPatins,
	bool:pObservacao,
	bool:segurandoRadio,
	bool:pChatNoob,
	bool:pTituloP,
	bool:pAnuncioP,
	pBanCadeia,
	pLimparPrisoes,
	pToggleNoob,
	pToggleSocio,
	pBolsaFamilia,
	pRoubou,
	pMatouSniper,
	pAllowWeapons,
	pTempoHospital,

	pHitSound[2],
	pHitSoundID,

	pTempoAgendado,
	pAdminAgendou[64],
	pMotivoAgendou[128],
	pSERIAL[256],

	pMinhasApreensoes,
	pMorteSuspeito,

	pContratos,
	pCigarros,
	pLastContrato,

	pExplosives,
	pSafeExplosivos,

	pTrocaNick,

	pFlood,
	pFloodTimes,
	
	pOuros,
	pSex,
	pCidade,
	bool:pMuted,
	pExp,
	pCashVip,
	pConta,
	pCrimes,
	pKills,
	pDeaths,
	pLottoNr,
	pEmprego,
	pEmprego2,
	pHeadValue,
	pHeadValueT,
	pHeadRespect,
	pHeadRespectT,
	pJailed,
	pJailTime,
	pMats,
	produtosMateriais,
	pDrogas,
	pDrogas2,
	pDrogas3,
	pMembro,
	pCargo,
	pSkin,
	pSkinServico,
	pFerSkill,
	pDetSkill,
	pAdvogadoSkill,
	pMedicoSkill,
	bool:pChatVip,
	bool:pChatMorro,
	Float:pHealth,
	Float:pArmour,
	Float:pRestoreLife,
	Float:pRestoreFome,
	Float:pRestoreSede,
	pCapacete,
	numeroCelular,
	pArenaKills,
	pArenaKillsRod,
	pFamily,
    Float:pFome,
    Float:pSede,
	pGunLic,
	pPayDay,
	pWarns,
	pWarnsAdmin,
	pMarried,
	pRequestingBackup,
	pMarriedTo[64],
	pSafeDrogas,
	pSafeDrogas2,
	pSafeDrogas3,
	psMats,
	pDoenca,
	pIdeologia,

	pPixador,

	pLuta,

	bool:pAjustado,
	bool:pHAjustado,

	pLaastLogin[255],

	pCaixinha,

	pBan,

	pPrisaoAdmin,

	// Precisa tirar
	pLimparb,
	
	QuantidadeBan,

	// Configurações do conselho
	bool:pHidePar,

	// Banco filiado
	pBancoFiliado,

	// Informações da prisão
	pPrisaoData[255],
	pRespPrisao[255],
	pMotivoPrisao[255],
	orgPrendeu,

	//
	casa_alugada,
	
	// Config
	style_view_rg,

	pLastWeapons[250]
};
new PlayerInfo[MAX_PLAYERS][E_PLAYER];
new ListPlayers[MAX_PLAYERS][MAX_PLAYERS];

new g_LastAdminMoneyPickup[MAX_PLAYERS];
new g_AdminLastMoneyPickup[MAX_PLAYERS];
new gIsInAdminPasswordScreen[MAX_PLAYERS];

new ListOptions[MAX_PLAYERS][70];

// -------------------------------------------------------------------------------
// Funções;
// Getters e Setters;

// Checa se o jogador está logado
stock Player_Logado(playerid) {
	if (IsPlayerConnected(playerid) && playerid != INVALID_PLAYER_ID) {
		if (PlayerInfo[playerid][pLogged]) 
			return true;
	}
	return false;
}

stock Player_SetLogado(playerid, bool:status) {
	PlayerInfo[playerid][pLogged] = status;
}

// -------------------------------------------------------------------------------

// Formata o nome do player troca _ por espaço
stock FormatPlayerName(playerid) {
    new get_player_name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, get_player_name, MAX_PLAYER_NAME);

	for(new i; i < strlen(get_player_name); ++i) {
		if (get_player_name[i] == '_') 
			get_player_name[i] = ' ';
	}
    return get_player_name;
}

// Lista de players (para Dialog)
stock List_SetPlayers(playerid, slot, playerlist) {
	ListPlayers[playerid][slot] = playerlist;
}

stock List_GetPlayers(playerid, playerlist) {
	return ListPlayers[playerid][playerlist];
}

stock List_ResetPlayer(playerid) {
	foreach (new i : Player) {
		for(new plist; plist < MAX_PLAYERS; plist++) {
			if (ListPlayers[i][plist] == playerid) {
				ListPlayers[i][plist] = INVALID_PLAYER_ID;
			}
		}
	}
}

// --------------------------------------

// stock Player_CheckSpectating(playerid, idplayer) {
// 	if (GetPlayerSpectateID(playerid) == idplayer ||
// 		GetPlayerSpectateID(playerid) == GetPlayerVehicleID(idplayer)) {
// 		TogglePlayerSpectating(playerid, false);
// 		PlayerTextDrawHide(playerid, spectadorText[playerid]);

// 		GameTextForPlayer(playerid, "~w~                TV~n~~r~~h~                DESCONECTADO", 3500, 6);
// 		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);

// 		SpawnPlayer(playerid);
// 	}
// 	return 1;
// }

// Necessidades:
stock Float:Player_GetFome(playerid) {
	return PlayerInfo[playerid][pFome];
}

stock Player_SetFome(playerid, Float:fome) {
	PlayerInfo[playerid][pFome] = fome;
}

stock Float:Player_GetSede(playerid) {
	return PlayerInfo[playerid][pSede];
}

stock Player_SetSede(playerid, Float:sede) {
	PlayerInfo[playerid][pSede] = sede;
}

stock Player_GetPayday(playerid)
	return PlayerInfo[playerid][pPayDay];

// ---------------------------------------

stock Player_GetTempoHospital(playerid) {
	return PlayerInfo[playerid][pTempoHospital];
}

stock Player_SetTempoHospital(playerid, tempo) {
	PlayerInfo[playerid][pTempoHospital] = tempo;
}

// --------------------------------------
// Pegou caixinha:

stock Player_SetCaixinha(playerid, bool:stats) {
	PlayerInfo[playerid][pCaixinha] = stats;
}

stock Player_GetCaixinha(playerid) {
	return PlayerInfo[playerid][pCaixinha];
}

// -----------------------------
// Nível

stock Player_SetNivel(playerid, level) {
	PlayerInfo[playerid][pLevel] = level;
	SetPlayerScore(playerid, level);
}

stock Player_GetNivel(playerid) {
	SetPlayerScore(playerid, PlayerInfo[playerid][pLevel]);
	return PlayerInfo[playerid][pLevel];
}

// -----------------------------
// Discord

stock Player_GetDiscordUser(playerid) {
	new str[26];
	format(str, sizeof(str), "%s", PlayerInfo[playerid][pDiscord]);
	return str;
}

stock Player_SetDiscordUser(playerid, const user[]) {
	format(PlayerInfo[playerid][pDiscord], 26, "%s", user);
}

// -----------------------------
// Sexo

stock Player_SetSex(playerid, level) {
	PlayerInfo[playerid][pSex] = level;
}

stock Player_GetSex(playerid) {
	return PlayerInfo[playerid][pSex];
}

// -----------------------------
// Kills

stock Player_SetKills(playerid, kills) {
	PlayerInfo[playerid][pKills] = kills;
}

stock Player_GetKills(playerid) {
	return PlayerInfo[playerid][pKills];
}

// -----------------------------
// Deaths

stock Player_SetDeaths(playerid, deaths) {
	PlayerInfo[playerid][pDeaths] = deaths;
}

stock Player_GetDeaths(playerid) {
	return PlayerInfo[playerid][pDeaths];
}

// -----------------------------
// Luta

stock Player_SetStruggle(playerid, struggle) {
	PlayerInfo[playerid][pLuta] = struggle;
}

stock Player_GetStruggle(playerid) {
	return PlayerInfo[playerid][pLuta];
}

// -----------------------------
// Skin

stock Player_SetSkin(playerid, skin) {
	PlayerInfo[playerid][pSkin] = skin;
	SetPlayerSkin(playerid, skin);
}

stock Player_GetSkin(playerid) {
	return PlayerInfo[playerid][pSkin];
}

// -----------------------------
// VIP

stock Player_SetVIP(playerid, level) {
	PlayerInfo[playerid][pVIP] = level;
}

stock Player_GetVIP(playerid) {
	return PlayerInfo[playerid][pVIP];
}

stock Player_SetVIPDate(playerid, Timestamp:Date) {
	PlayerInfo[playerid][pVIPDate] = date;
}

stock Player_GetVIPDate(playerid) {
	return PlayerInfo[playerid][pVIPDate];
}

// -----------------------------
// Seção dinheiro da mão
stock Player_GetMoney(playerid) {
	return PlayerInfo[playerid][pMoney];
}

stock Player_SetMoney(playerid, value) {
	ServerLog::("dinheiro", "%s estava com $%s e ficou com $%s.", PlayerName[playerid], getFormatText(Player_GetMoney(playerid)), getFormatText(value));
	PlayerInfo[playerid][pMoney] = value;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, value);
}

stock Player_AddMoney(playerid, value) {
	ServerLog::("dinheiro", "%s estava com $%s e ficou com $%s.", PlayerName[playerid], getFormatText(Player_GetMoney(playerid)), getFormatText(Player_GetMoney(playerid) + value));
	PlayerInfo[playerid][pMoney] += value;
	GivePlayerMoney(playerid, value);
}

stock Player_RemoveMoney(playerid, value) {
	ServerLog::("dinheiro", "%s estava com $%s e ficou com $%s.", PlayerName[playerid], getFormatText(Player_GetMoney(playerid)), getFormatText(Player_GetMoney(playerid) - value));
	PlayerInfo[playerid][pMoney] -= value;
	GivePlayerMoney(playerid, -value);
}

// -----------------------------
// Seção banco
stock Player_GetMoneyBank(playerid) {
	return PlayerInfo[playerid][pConta];
}

stock Player_SetMoneyBank(playerid, value) {
	PlayerInfo[playerid][pConta] = value;
}

// -----------------------------
// Seção cadeia

stock Player_GetJailsAdmin(playerid) {
	return PlayerInfo[playerid][pPrisaoAdmin];
}

stock Player_SetJailsAdmin(playerid, jails) {
	PlayerInfo[playerid][pPrisaoAdmin] = jails;
}

stock Player_GetJailTime(playerid) {
	return PlayerInfo[playerid][pJailTime];
}

stock Jail_GetOrg(playerid) {
	return PlayerInfo[playerid][orgPrendeu];
}

stock Jail_GetResp(playerid) {
	new str[sizeof(PlayerInfo[playerid][pRespPrisao])];

	format(str, sizeof(str), "%s", PlayerInfo[playerid][pRespPrisao]);

	return str;
}

stock Jail_GetDate(playerid) {
	new str[sizeof(PlayerInfo[playerid][pPrisaoData])];

	format(str, sizeof(str), "%s", PlayerInfo[playerid][pPrisaoData]);

	return str;
}

stock Jail_GetReason(playerid) {
	new str[sizeof(PlayerInfo[playerid][pMotivoPrisao])];

	format(str, sizeof(str), "%s", PlayerInfo[playerid][pMotivoPrisao]);

	return str;
}

stock Jail_GetAjusted(playerid) {
	return PlayerInfo[playerid][pAjustado];
}

stock Player_GetJailed(playerid) {
	return PlayerInfo[playerid][pJailed];
}

stock Jail_SetJailed(playerid, jailedid) {
	PlayerInfo[playerid][pJailed] = jailedid;
}

stock Jail_SetTime(playerid, time) {
	PlayerInfo[playerid][pJailTime] = time;
}

stock Jail_SetOrg(playerid, orgid) {
	PlayerInfo[playerid][orgPrendeu] = orgid;
}

stock Jail_SetResp(playerid, const str[]) {
	format(PlayerInfo[playerid][pRespPrisao], 35, "%s", str);
}

stock Jail_SetDate(playerid, const str[]) {
	format(PlayerInfo[playerid][pPrisaoData], 60, "%s", str);
}

stock Jail_SetReason(playerid, const str[]) {
	format(PlayerInfo[playerid][pMotivoPrisao], 50, "%s", str);
}

stock Jail_SetAjusted(playerid, bool:ajusted) {
	PlayerInfo[playerid][pAjustado] = ajusted;
}

stock Staff_GetConfig(playerid, const str[])
{
	if (!strcmp(str, "particulares", true)) {
		return PlayerInfo[playerid][pHidePar];
	}
	return -1;
}

// -----------------------------
// Seção eventos;

stock Player_SetInEvent(playerid, bool:stats, EventType:type) {
	PlayerInfo[playerid][pEvent] = stats;
	PlayerInfo[playerid][pEventType] = type;
}

stock Player_InEvent(playerid) {
	return PlayerInfo[playerid][pEvent];
}

stock Player_InEventType(playerid) {
	return PlayerInfo[playerid][pEventType];
}

stock Player_SetEventStage(playerid, stage) {
	PlayerInfo[playerid][pEventStage] = stage;
}

stock Player_InEventStage(playerid) {
	return PlayerInfo[playerid][pEventStage];
}

// -----------------------------
// Mutado

stock Player_SetMuted(playerid, bool:value) {
	PlayerInfo[playerid][pMuted] = value;
}

stock Player_GetMuted(playerid) {
	return PlayerInfo[playerid][pMuted];
}

// -----------------------------
// Seção explosivos;

stock Player_GetExplosivos(playerid) {
	return PlayerInfo[playerid][pExplosives];
}

stock Player_SetExplosivo(playerid, value) {
	PlayerInfo[playerid][pExplosives] = value;
}

// Possui algum explosivo;
stock GetPlayerExplosives(playerid) {
	return PlayerInfo[playerid][pExplosives];
}

// Caso estiver segurando um explosivo;
stock GetPlayerHoldingExplosive(playerid) {
	return PlayerInfo[playerid][holdingExplosive];
}

// Define se está segurando um explosivo;
stock SetPlayerExplosive(playerid, bool:isholding) {
	PlayerInfo[playerid][holdingExplosive] = isholding;
}

// -----------------------------
// Seção Checkpoint;
stock SetPlayerCP(playerid, cp_id = CP_NULL) {
	PlayerInfo[playerid][Checkpoint] = cp_id;
}

// Pega o modo atual;
stock GetPlayerCP(playerid) {
	return PlayerInfo[playerid][Checkpoint];
}

// -----------------------------
// Seção player;

// ID atual do jogador;
stock GetPlayerID(const nickplayer[])
{
	foreach(new i : Player) {
	   	if (!strcmp(PlayerName[i], nickplayer, true)) {
	   	    return i;
		}
    }
    return INVALID_PLAYER_ID;
}

stock GetPlayerIdByIdGlobal(g_id)
{
	foreach(new i : Player) {
		if (PlayerInfo[i][pID] == g_id) {
			return i;
		}
	}
	return -1;
}

// ID global;
stock Player_GetGID(playerid) {
	return PlayerInfo[playerid][pID];
}

stock GetPlayerAgressive(playerid) {
	return PlayerInfo[playerid][mAgressivo];
}

static bool:SeeNick[MAX_PLAYERS];

stock SetPlayerSeeNick(playerid, bool:status) {
	SeeNick[playerid] = status;
}

stock GetPlayerSeeNick(playerid) {
	return SeeNick[playerid];
}

static pWorld_atual[MAX_PLAYERS];

stock SetPlayerActualWorld(playerid, worldid) {
	pWorld_atual[playerid] = worldid;
}

stock GetPlayerActualWorld(playerid) {
	return pWorld_atual[playerid];	
}

// ------------------------------------------------------
// Área dos cash

stock Player_GetCash(playerid) {
	return PlayerInfo[playerid][pCashVip];
}

stock Player_SetCash(playerid, value) 
{
	PlayerInfo[playerid][pCashVip] = value;
	PlayerTextDrawSetString(playerid, _cash_ptextdraw[playerid], getFormatText(value));

	new string[128];
	format(string, sizeof(string), "(CASH): %s foi de $%s cash para $%s", PlayerName[playerid], Player_GetCash(playerid), value);
	server_log("cash_economy", string);
}

stock Player_AddCash(playerid, value) {
	Player_SetCash(playerid, Player_GetCash(playerid) + value);
}

stock Player_RemoveCash(playerid, value) {
	Player_SetCash(playerid, Player_GetCash(playerid) - value);
}

// ------------------------------------------------------
// Área dos ouros

stock Player_SetOuros(playerid, value) {
	PlayerInfo[playerid][pOuros] = value;
}

stock Player_GetOuros(playerid) {
	return PlayerInfo[playerid][pOuros];
}

// Tempo roubos:
stock Player_SetTempoRoubou(playerid, time) {
	PlayerInfo[playerid][pRoubou] = time;
}

stock Player_GetTempoRoubou(playerid) {
	return PlayerInfo[playerid][pRoubou];
}

// Doença do jogador ( Sistema de Sexo )
stock Player_SetDoenca(playerid, doenca) {
	PlayerInfo[playerid][pDoenca] = doenca;
}

stock Player_GetDoenca(playerid) {
	return PlayerInfo[playerid][pDoenca];
}

stock SetAdminLastMoneyPickup(playerid, timestamp) {
    g_LastAdminMoneyPickup[playerid] = timestamp;
    g_AdminLastMoneyPickup[playerid] = timestamp;  // Persistência entre sessões
    SaveStuff();
    return true;
}

stock GetAdminLastMoneyPickup(playerid) {
    return g_LastAdminMoneyPickup[playerid];
}

// -----------------------------------------------------
// ID Global:

stock Player_GetAccountID(playerid) {
	return PlayerInfo[playerid][pID];
}

stock ORM:Player_GetORMID(playerid) {
	return PlayerInfo[playerid][ORM_ID];
}

// ----------------------------------------------)

stock Player_SetWanted(playerid, points) {
	PlayerInfo[playerid][pWanted] = points;
	SetPlayerWantedLevel(playerid, points);
}

stock Player_GetWanted(playerid) {
	return PlayerInfo[playerid][pWanted];
}

// ----------------------------------------------)

stock Player_GetJob(playerid, idjob=1) {
	if (idjob == 1) {
		return PlayerInfo[playerid][pEmprego];
	} else {
		return PlayerInfo[playerid][pEmprego2];
	}
}

// ----------------------------------------------)

// stock Player_GetArmour(playerid) {
// 	return PlayerInfo[playerid][pArmour];
// }

// stock Player_GetHealth(playerid) {
// 	return PlayerInfo[playerid][pHealth];
// }

// stock Player_GetLastPos(playerid, pos) {
// 	return PlayerInfo[playerid][pLastPos][pos];
// }

// stock Player_GetLastVehicle(playerid) {
// 	return PlayerInfo[playerid][pLastVehicle];
// }

// stock Player_GetStatus(playerid) {
// 	GetPlayerArmour(playerid, PlayerInfo[playerid][pArmour]);
// 	GetPlayerHealth(playerid, PlayerInfo[playerid][pHealth]);
// 	GetPlayerPos(playerid, PlayerInfo[playerid][pLastPos][0], PlayerInfo[playerid][pLastPos][1], PlayerInfo[playerid][pLastPos][2]);
// 	GetPlayerFacingAngle(playerid, PlayerInfo[playerid][pLastPos][3]);
// 	PlayerInfo[playerid][pLastVehicle] = GetPlayerVehicleID(playerid);
// }

// ----------------------------------------------)

stock Player_SetArenaKills(playerid, kills) {
	PlayerInfo[playerid][pArenaKills] = kills;
}

stock Player_GetArenaKills(playerid) {
	return PlayerInfo[playerid][pArenaKills];
}

stock Player_SetArenaKillsRod(playerid, kills) {
	PlayerInfo[playerid][pArenaKillsRod] = kills;
}

stock Player_GetArenaKillsRod(playerid) {
	return PlayerInfo[playerid][pArenaKillsRod];
}

stock IsPlayerInMar(playerid)
{
	new Float:x, Float:y, Float:pz;

	GetPlayerPos(playerid, x, y, pz);

	if (pz < 1.5) 
		return true;

	return false;
}

stock ContarJogadores()
{
	new	jogadoresOnline;

	foreach(new i : Player)
		jogadoresOnline++;
	
	return jogadoresOnline;
}

stock Log_IP(playerid)
{
	if (IsPlayerNPC(playerid)) 
		return false;

	new string[60];
	format(string, sizeof(string), "IP: %s - %s", PlayerIP[playerid], PlayerName[playerid]);
	server_log("ip", string);
	return 1;
}

// Spectador - /tv
enum spectadorInfo {
    spectadorID,
};
new SpectadorInfo[MAX_PLAYERS][spectadorInfo];

stock Player_GetSpectador(playerid) {
    return SpectadorInfo[playerid][spectadorID];
}

// ---------------
static bool:playerInStore[MAX_PLAYERS];
static playerInPageStore[MAX_PLAYERS];

stock PlayerSetInStore(playerid, bool:stats)
    playerInStore[playerid] = stats;

stock bool:PlayerInStore(playerid)
    return playerInStore[playerid];

stock Store_SetPage(playerid, page)
    playerInPageStore[playerid] = page;

stock Store_GetPage(playerid)
    return playerInPageStore[playerid];