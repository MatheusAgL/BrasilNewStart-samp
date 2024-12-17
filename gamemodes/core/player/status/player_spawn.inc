// -- Módulo: Spawn do jogador.
// =------------------------------------------------=)

// Includes:
#include < YSI_Coding\y_hooks >

new PlayerText:textInvasao[MAX_PLAYERS];

#define MAX_SPAWN_TYPES 5

static const Float:CamasHospital[6][7] =
{
	{1127.3859, -1735.0784, 14.4565, 185.6116, 		1129.8937, -1736.8180, 13.8090},
	{1127.3157, -1738.3033, 14.4565, 180.1673,		1129.9398, -1739.7677, 13.8090},
	{1127.3782, -1744.5056, 14.4565, 181.4207,		1129.9800, -1745.4486, 13.8090},
	{1127.2550, -1748.8888, 14.4565, 181.0290,		1130.3312, -1750.2622, 13.8000},
	{1133.2866, -1749.0354, 14.4565, 6.9707,		1130.4525, -1747.6555, 13.8090},
	{1133.3649, -1735.5718, 14.4565, 2.5056,		1130.9221, -1737.4092, 13.8090}
};

stock setarhospital(playerid)
{
    SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
    new camasrandom = random(sizeof(CamasHospital));
    SetPlayerPos(playerid, CamasHospital[camasrandom][0], CamasHospital[camasrandom][1], CamasHospital[camasrandom][2]);
    SetPlayerFacingAngle(playerid, CamasHospital[camasrandom][3]);
    ApplyAnimation(playerid, "CRACK", "crckidle2", 4.1, 0, 1, 1, 1, 0);
	PlayerTextDrawSetString(playerid, TextHospital[playerid], "_");
	PlayerTextDrawShow(playerid, TextHospital[playerid]);
	SetPlayerCameraPos(playerid, CamasHospital[camasrandom][3], CamasHospital[camasrandom][4], CamasHospital[camasrandom][5]);
	SetPlayerCameraLookAt(playerid, CamasHospital[camasrandom][0], CamasHospital[camasrandom][1], CamasHospital[camasrandom][2]);
}

// Variáveis:
new BitArray:PlayerSpawnState<MAX_PLAYERS>;

// ----------------------------------------------
// Locais de spawn

enum SpawnType {
	TYPE_SPAWN_DEFAULT,
	TYPE_SPAWN_JOB,
	TYPE_SPAWN_BUSSINES,
	TYPE_SPAWN_FAMILY,
	TYPE_SPAWN_HOUSE,
	TYPE_SPAWN_SPEAKER,
	TYPE_SPAWN_YOUTUBER,
};

enum epspawn {
	SpawnID,
	SpawnType:TypeSpawn,
};
new Player_Spawn[MAX_PLAYERS][epspawn];

// ----------------------------------------------)
static Spawn_GetName(SpawnType: type) {
	static string[30];
	switch (type) {
		case TYPE_SPAWN_DEFAULT:
			string = "Organização";
		case TYPE_SPAWN_JOB:
			string = "Emprego";
		case TYPE_SPAWN_BUSSINES:
			string = "Empresa";
		case TYPE_SPAWN_FAMILY:
			string = "Familia";
		case TYPE_SPAWN_HOUSE:
			string = "Casa";
		case TYPE_SPAWN_SPEAKER:
			string = "HQ Equipe Radio";
		case TYPE_SPAWN_YOUTUBER:
			string = "HQ Youtubers";
	}
	return string;
}

stock SpawnType:Player_GetSpawnType(playerid) {
	return SpawnType:Player_Spawn[playerid][TypeSpawn];
}

stock Player_SetSpawnType(playerid, SpawnType:type, spawnid=-1) {
	#pragma unused spawnid

	Player_Spawn[playerid][TypeSpawn] = SpawnType:type;
	Player_Spawn[playerid][SpawnID] = spawnid;

	new string[128];
	if(type == TYPE_SPAWN_DEFAULT)
		format(string, sizeof(string), "Local de spawn definido para a HQ ~y~%s", NomeORG(playerid));
	else if(type == TYPE_SPAWN_JOB) {
		new empregoid = spawnid == 0 ? PlayerInfo[playerid][pEmprego] : PlayerInfo[playerid][pEmprego2];
		format(string, sizeof(string), "Local de spawn definido para a HQ do emprego de ~y~%s", GetJobName(empregoid));
	}
	else if(type == TYPE_SPAWN_BUSSINES) {
		new propertyName[64];
		format(propertyName, 64, GetPropertyName(spawnid));
		format(string, sizeof(string), "Local de spawn definido para ~y~%s (%d)", propertyName, spawnid);
	}
	else if(type == TYPE_SPAWN_FAMILY) {
		format(string, sizeof(string), "Local de spawn definido para a familia ~y~%s", GetPlayerFamilyName(playerid));
	}
	else if(type == TYPE_SPAWN_HOUSE) {
		format(string, sizeof(string), "Local de spawn definido para a ~y~Casa %d", spawnid);
	}
	else if(type == TYPE_SPAWN_SPEAKER) {
		format(string, sizeof(string), "Local de spawn definido para a ~b~Equipe da radio");
	}
	else if(type == TYPE_SPAWN_YOUTUBER) {
		format(string, sizeof(string), "Local de spawn definido para a ~r~HQ Youtubers");
	}

	PlayerPlaySound(playerid,1139,0.0,0.0,0.0);
	ShowPlayerMessage(playerid, string, 5000);
	return 1;
}

hook OnPlayerConnect(playerid) {
    Bit_Set(PlayerSpawnState, playerid, false);
}

CALLBACK: AntiSpawnKillExit(playerid) 
	return SetPVarInt(playerid, "AntiSpawnKill", 0);

public OnPlayerSpawn(playerid) 
{
	Bit_Set(PlayerSpawnState, playerid, true);

	if (!Player_Logado(playerid) || 
		Player_CheckBan(playerid))
		return 1;

	// Default:
    SetCameraBehindPlayer(playerid);
	TogglePlayerControllable(playerid, true);
	SetPlayerToTeamColor(playerid);
	
#if _inc_paintball_system
	if (Player_GetPaintball(playerid) != INVALID_PAINTBALL_ID) 
	{
		if (PlayerInfo[playerid][pSkin] > 0)
		{
			SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		}
		else
		{
			if (PlayerInfo[playerid][pSex] == 1)
			{
				PlayerInfo[playerid][pSkin] = 23;
				SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
			}
			else
			{
				PlayerInfo[playerid][pSkin] = 216;
				SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
			}
		}
		Paintball_Spawn(playerid);
		return 1;
	}
#endif

	// Addon:
	Player_SetAccessories(playerid);

	if(PlayerInfo[playerid][pHospital]) {
	    new camasrandom = random(sizeof(CamasHospital));

	    SetPlayerPos(playerid, 
			CamasHospital[camasrandom][0], 
			CamasHospital[camasrandom][1], 
			CamasHospital[camasrandom][2]);

		SetPlayerFacingAngle(playerid, 
			CamasHospital[camasrandom][3]);

	    ApplyAnimation(playerid, "CRACK", "crckidle2", 4.1, 0, 1, 1, 1, 0);

		PlayerTextDrawSetString(playerid, TextHospital[playerid], "_");
		PlayerTextDrawShow(playerid, TextHospital[playerid]);
		
		SetPlayerCameraPos(playerid, 1150.56, -1332.78, -43.15);
		SetPlayerCameraLookAt(playerid, 1154.67, -1328.59, -44.38);

	    return 1;
	}

	// Condição do jogador:
	if (!OnPlayerCheckJailed(playerid)) {
		switch (Player_GetSpawnType(playerid)) 
		{
			case TYPE_SPAWN_FAMILY: {
				Player_SpawnInFamily(playerid);
			}
			case TYPE_SPAWN_JOB: {
				Player_SpawnInJob(playerid);
			}
			case TYPE_SPAWN_HOUSE: {
				Player_SpawnInHouse(playerid);
			}
			case TYPE_SPAWN_BUSSINES: {
				Player_SpawnInBusiness(playerid);
			}
			default: {
				Player_SpawnInOrg(playerid);
			}
		}
	}

	// Está desbanido do servidor.
	if (PlayerInfo[playerid][pBan] > 0) {
	    SendClientMessage(playerid, COLOR_DBLUE, "Você foi desbanido do servidor, tenha um bom jogo!");
	    PlayerInfo[playerid][pBan] = 0;
	}

	// ShowPlayerBaloonInfo(playerid, "Aperte a letra 'N' para abrir seu inventario", 5000);

	// Variáveis de morte;
	wLastShooter[playerid] = INVALID_PLAYER_ID;			// Player que deu o último tiro (limpar)
	SetPVarInt(playerid, "varDead", 0);					// Player não está morto, já spawnou
	SetPVarInt(playerid, "VarDano", 0);					// Player não está mais em combate

	// Fugiu da cadeia
	SetPVarInt(playerid, "varFugitivo", 0);
    KillTimer(GetPVarInt(playerid, "varTimerFugitivo"));
    SetPVarInt(playerid, "varTimerFugitivo", -1);

	// Estava descendo na corda do helicoptero
    SetPVarInt(playerid, "roped", 0);
    SetPVarInt(playerid, "chop_id", -1);

	// Ocultar texto de invasão
	PlayerTextDrawHide(playerid, textInvasao[playerid]);

	// Sistema de anti-DM (limpeza após spawn)
	foreach(new i : Player) {
	    DMSystem[playerid][i] = false;
	    DMSystem[i][playerid] = false;
	}

	// Policial (remover o cartão batido)
	if (!IsACop(playerid))
		OnDuty[playerid] = 0;

	// Destroi o caminhão
	if (Vehicle_IsCaminhao(playerid))
		DestroyPlayerCaminhao(playerid);

	// Anti spawn-kill
	if (!GetPVarInt(playerid, "AntiSpawnKill")) {
	    SetTimerEx("AntiSpawnKillExit", 15000, false, "i", playerid); 	// 15 Segundos
	    SetPVarInt(playerid, "AntiSpawnKill", 1);
	}
	
	if (OnDuty[playerid]) {														// Caso for policial com cartão batido
	    SetPlayerSkin(playerid, PlayerInfo[playerid][pSkinServico]);
	} else {																	// Padrão
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	}

	// Carregar as armas do jogador
	if (GetPVarInt(playerid, "LastWeaponsLoadded") == 0) 
		SetTimerEx("LoadLastWeapons", 2000, false, "i", playerid);

	// Armas bloqueadas
	if (block_temp_weapons[playerid])
		GivePlayerTempWeapons(playerid);

    return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason) {
    Bit_Set(PlayerSpawnState, playerid, false);
    return 1;
}

stock Player_IsSpawned(playerid) {
    return Bit_Get(PlayerSpawnState, playerid);
}

CALLBACK: OnPlayerFirstSpawn(playerid) {
    return 1;
}

CMD:mudarlocal(playerid)
{
	MEGAString[0] = EOS;
	new string[128];

	for (new loop; loop < MAX_SPAWN_TYPES; loop++) {
		format(string, sizeof(string), "%sLocal: %s\n", 
		Player_GetSpawnType(playerid) == SpawnType:loop ? ""C_NIGHTBLUE"-> " : ""C_WHITE"", Spawn_GetName(SpawnType:loop));
		strcat(MEGAString, string);
	}

	inline D_MudarLocal(djsid, djsdialogid, djsresponse, djslistitem, string:djstext[])
	{
		#pragma unused djsid, djsdialogid, djstext
		if (!djsresponse) 
			return true;

		switch (djslistitem)
		{
			case TYPE_SPAWN_DEFAULT:
				return Player_SetSpawnType(playerid, TYPE_SPAWN_DEFAULT);
			case TYPE_SPAWN_JOB: {
				if (!Player_HaveJob(playerid))
					return SendClientMessage(playerid, -1, "Você não tem um emprego.");

				ShowPlayerJobs(playerid);
			}
			case TYPE_SPAWN_BUSSINES: {
				if(!CountProperties(playerid))
					return SendClientMessage(playerid, -1, "Você não possui empresa.");

				ShowPlayerProperties(playerid);
			}
			case TYPE_SPAWN_FAMILY: {
				if(GetPlayerFamily(playerid) == -1)
					return SendClientMessage(playerid, -1, "Você não faz parte de uma família.");

				return Player_SetSpawnType(playerid, TYPE_SPAWN_FAMILY);
			}
			case TYPE_SPAWN_HOUSE: {
				if (!HousesPlayer_Count(playerid))
					return SendClientMessage(playerid, -1, "Você não tem uma casa.");

				Houses_Show(playerid, 1);
			}
			case TYPE_SPAWN_SPEAKER: {
				if (Speaker_GetNivel(playerid) < ESTAGIARIO_RADIO)
					return SendClientMessage(playerid, -1, "Você não faz parte da equipe da rádio.");

				return Player_SetSpawnType(playerid, TYPE_SPAWN_SPEAKER);
			}
			case TYPE_SPAWN_YOUTUBER: {
				if (Youtuber_GetNivel(playerid) < YOUTUBER_INICIANTE)
					return SendClientMessage(playerid, -1, "Você não faz parte dos Youtubers.");

				return Player_SetSpawnType(playerid, TYPE_SPAWN_YOUTUBER);
			}
		}
		return 1;
	}
    Dialog_ShowCallback(playerid, using inline D_MudarLocal, DIALOG_STYLE_LIST, ""C_GRAY"Selecione um novo local de spawn", MEGAString, "Selecionar", ""C_GRAY"Fechar");
	return 1;
}