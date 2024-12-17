#if defined _inc_paintball_system
	#endinput
#endif
#define _inc_paintball_system true

#include <YSI_Coding\y_hooks>

#include <paintball_entry>
#include <paintball_textdraws>
#include <paintball_cmds>

static Iterator:IterPaintballs<MAX_PAINTBALLS>;

// Timers
static 	
	Timer:timerStartRound[MAX_PAINTBALLS],
	Timer:timerNewRound[MAX_PAINTBALLS],
	Timer:timer_entry_pb[MAX_PLAYERS],
	Timer:timerCountDuel[MAX_PLAYERS];

// ------------------------ Sistema de grupos de usuário ------------------------
static 
		Statement: stmt_createPaintball,
		Statement: stmt_selectPaintballs;

hook OnMySQLConnected() 
{
    static const query_createPaintballs[] = 
		"INSERT INTO `paintball_rooms` \
            (`owner`, `name`, `description`, `door_lock`, `world`, `round_time`, `x1`, `weapons`)  \
        VALUES \
            (?, '?', '?', ?, ?, ?, ?, '?')"
	;
	stmt_createPaintball = MySQL_PrepareStatement(MySQL_Handle, query_createPaintballs);

	static const query_selectPaintballs[] = 
		"SELECT * FROM `paintball_rooms` LIMIT ?"
	;
	stmt_selectPaintballs = MySQL_PrepareStatement(MySQL_Handle, query_selectPaintballs);

    return 1;
}

timer Paintball_StartRound[10000](pbid)
{
	foreach (new i : Player)
	{
		if (Player_GetPaintball(i) == pbid && 
			PlayerPaintball_GetOpponent(i) == INVALID_PLAYER_ID) {
			
			Chat_Clear(i);
			TogglePlayerControllable(i, true);
			Paintball_Spawn(i);

			Player_SetArenaKillsRod(i, 0);
			PlayerPlaySound(i, 31205, 0.0, 0.0, 0.0);

			ShowPlayerBaloonInfo(i, "Caso queira ~r~sair ~w~do PAINTBALL digite ~r~/sairpb", 5000);
		}
	}
	new string[128];
	format(string, sizeof(string), "| INICIO DA RODADA: "C_WHITE"A rodada tem duracao de "C_CYAN"%d "C_WHITE"minutos...", Paintball_GetRoundTime(pbid));
	Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);
}

timer Paintball_NewRound[5 * 60000](pbid)
{
	new winner = Paintball_GetWinner(pbid),
		winner_kills,
		string[128];

	if (winner != INVALID_PLAYER_ID) {
		winner_kills = Player_GetArenaKillsRod(winner);
		format(string, sizeof(string), "PAINTBALL | O vencedor foi "C_CYAN"%s"C_WHITE" com "C_RED"%d MORTES"C_WHITE"!!", PlayerName[winner], winner_kills);
	} 
	else format(string, sizeof(string), "PAINTBALL | O vencedor foi "C_CYAN"NENHUM"C_WHITE" com "C_RED"0 MORTES"C_WHITE"!!");

	Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);
	
	foreach(new playerid : Player)
	{
		if (Player_GetPaintball(playerid) == pbid && 
			PlayerPaintball_GetOpponent(playerid) == INVALID_PLAYER_ID) {
			TogglePlayerControllable(playerid, false);
			SendClientMessage(playerid, COLOR_PAINTBALL, "PAINTBALL | "C_GREEN"Iniciando uma nova rodada...");
		}
	}
	timerStartRound[pbid] = defer Paintball_StartRound(pbid);

	return 1;
}

timer timerPlayerEntryPb[30000](playerid, pbid)
{
	Player_SetPaintball(playerid, pbid);
	Paintball_SaveEntry(playerid);
	Paintball_Spawn(playerid);
	TogglePlayerControllable(playerid, true);

	Player_SetArenaKills(playerid, 0);
	ShowPlayerBaloonInfo(playerid, "Caso queira ~r~sair ~w~do PAINTBALL digite ~r~/sairpb", 5000);

	Paintball_CreateTextLabel(playerid);
	PlayerTextDrawShow(playerid, ptd_paintball[playerid]);

	new string[56];
	format(string, sizeof(string), "--> %s entrou na sala de paintball!", PlayerName[playerid]);
	Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);
}

timer CountDuel[1000](playerid, playerid2, countduel)
{
    if (Player_GetPaintball(playerid) == INVALID_PAINTBALL_ID || 
		Player_GetPaintball(playerid2) == INVALID_PAINTBALL_ID || 
		!IsPlayerConnected(playerid) || 
		!IsPlayerConnected(playerid2) || 
		PlayerPaintball_GetOpponent(playerid) != playerid2 || 
		PlayerPaintball_GetOpponent(playerid2) != playerid) {
		Paintball_Spawn(playerid);
		Paintball_Spawn(playerid2);
		return false;
    }

    if (countduel < 1)
	{
 		SetPlayerHealth(playerid, 100.0);
 		SetPlayerArmour(playerid, 100.0);
 		SetCameraBehindPlayer(playerid);
 		SetPlayerArmedWeapon(playerid, WEAPON_DEAGLE);
 		TogglePlayerControllable(playerid, true);
 		SetPVarInt(playerid, "duelo", gettime());

 		SetPlayerHealth(playerid2, 100.0);
 		SetPlayerArmour(playerid2, 100.0);
 		SetCameraBehindPlayer(playerid2);
 		SetPlayerArmedWeapon(playerid2, WEAPON_DEAGLE);
 		TogglePlayerControllable(playerid2, true);
 		SetPVarInt(playerid2, "duelo", gettime());

		PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
		PlayerPlaySound(playerid2, 1057, 0.0, 0.0, 0.0);

		GameTextForPlayer(playerid, "_~n~_~n~_~n~_~n~GO!", 2000, 6);

		stop timerCountDuel[playerid];
    } else {
		PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
		PlayerPlaySound(playerid2, 1056, 0.0, 0.0, 0.0);

        SetCameraBehindPlayer(playerid);
        SetCameraBehindPlayer(playerid2);

	    new string[25];
	    format(string, sizeof(string), "_~n~_~n~_~n~_~n~%d", countduel);

	    GameTextForPlayer(playerid, string, 2000, 6);
	    GameTextForPlayer(playerid2, string, 2000, 6);

        countduel--;

		timerCountDuel[playerid] = defer CountDuel(playerid, playerid2, countduel);
    }

    return 1;
}

hook OnGameModeInit() 
{
	inline const OnLoadPaintballs() 
	{
		new id,
			pbid,
            owner,
			name[34],
			description[64],
			door_lock,
			world,
			round_time,
			x1,
			weapons_string[128],
			weapons[13][128];

		MySQL_BindResultInt(stmt_selectPaintballs, 0, pbid);
		MySQL_BindResultInt(stmt_selectPaintballs, 1, owner);
		MySQL_BindResult(stmt_selectPaintballs, 2, name);
		MySQL_BindResult(stmt_selectPaintballs, 3, description);
		MySQL_BindResultInt(stmt_selectPaintballs, 4, door_lock);
		MySQL_BindResultInt(stmt_selectPaintballs, 5, world);
		MySQL_BindResultInt(stmt_selectPaintballs, 6, round_time);
		MySQL_BindResultInt(stmt_selectPaintballs, 7, x1);
		MySQL_BindResult(stmt_selectPaintballs, 8, weapons_string);

		while (MySQL_Statement_FetchRow(stmt_selectPaintballs)) 
		{
			id = Iter_Free(IterPaintballs);

			if (id != INVALID_ITERATOR_SLOT)
			{
				Iter_Add(IterPaintballs, id);

				Paintball_SetID(id, pbid);
				Paintball_SetOwner(id, owner);
				Paintball_SetName(id, name);
				Paintball_SetDescription(id, description);
				Paintball_SetLock(id, bool:door_lock);
				Paintball_SetWorld(id, world);
				Paintball_SetRoundTime(id, round_time);
				Paintball_SetX1(id, bool:x1);
				
				split(weapons_string, weapons, ',');
				for(new w; w < 13; w++)
					Paintball_SetWeapon(id, w, weapons[w]);

				if (door_lock == 0)
					timerNewRound[id] = defer Paintball_NewRound[Timer:round_time](id);

				printf("Paintball %d: %s loaded...", pbid, name);
			}
		}
	}
	MySQL_BindInt(stmt_selectPaintballs, 0, MAX_PAINTBALLS);
	MySQL_ExecuteParallel_Inline(stmt_selectPaintballs, using inline OnLoadPaintballs);

	// Pickups e TextLabel
	CreateDynamicPickup(1254, 23, 2695.5930, -1704.6952, 11.8438); 		// Entrada paintball
 	CreateDynamicPickup(1254, 23, -978.3629, 1053.1130, 1344.9878); 	// Saida paintball
    CreateDynamic3DTextLabel("PAINTBALL\n"C_WHITE"Pressione "_KEY_PATH_ENTER_INT_COLOR" "C_WHITE"para entrar", COLOR_PAINTBALL, 2695.5930, -1704.6952, 11.8438, 30.0);
    CreateDynamic3DTextLabel("PAINTBALL\n"C_WHITE"Use "C_RED"/sairpb "C_WHITE"para sair", COLOR_PAINTBALL, -978.3629, 1053.1130, 1344.9878, 50.0);

	return 1;
}

hook OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	if (Player_GetPaintball(playerid) != INVALID_PAINTBALL_ID)
	{
		if (strcmp(cmd, "/sairpb", true) != 0 && 
			strcmp(cmd, "/abrirpb", true) != 0 && 
			strcmp(cmd, "/armaspb", true) != 0 && 
			strcmp(cmd, "/duelo", true) != 0 && 
			strcmp(cmd, "/sairduelo", true) != 0 && 
			strcmp(cmd, "/a", true) != 0 && 
			strcmp(cmd, "/s", true) != 0 &&
			strcmp(cmd, "/n", true) != 0 &&
			strcmp(cmd, "/atendimento", true) != 0) {

			SendClientMessage(playerid, COLOR_LIGHTRED, "Você está no PAINTBALL, não pode usar qualquer comando, apenas:");
			SendClientMessage(playerid, COLOR_LIGHTRED, "/sairpb /abrirpb /armaspb /s /n /atendimento.");
			return 0;
		}
	}
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) 
{
	new pbid = Player_GetPaintball(playerid);

	if (pbid != INVALID_PAINTBALL_ID) 
	{
		new string[128],
			weapon_name[25];

		GetWeaponName(WEAPON:reason, weapon_name);

		if (Player_GetPaintball(killerid) == pbid)
		{
			new kills = Player_GetArenaKills(playerid);

			Player_SetArenaKills(playerid, kills + 1);
			Player_SetArenaKillsRod(playerid, kills + 1);

			format(string, sizeof(string), "** Você foi abatido por "C_RED"%s "C_TEAM_BALLAS"[Arma: %s]", PlayerName[killerid], weapon_name);
			SendClientMessage(playerid, TEAM_BALLAS_COLOR, string);

			format(string, sizeof(string), "** Você abateu "C_RED"%s "C_TEAM_BALLAS"[Arma: %s]", PlayerName[playerid], weapon_name);
			SendClientMessage(killerid, TEAM_BALLAS_COLOR, string);
			format(string, sizeof(string), "** Você agora tem "C_RED"%d abates!!", Player_GetArenaKills(killerid));
			SendClientMessage(killerid, TEAM_BALLAS_COLOR, string);

			PlayerPaintball_CheckCombo(playerid, killerid);
			Paintball_Spawn(playerid);
			Paintball_SendDeathMessage(killerid, playerid, reason);

			if (PlayerPaintball_GetOpponent(killerid) == playerid &&
				PlayerPaintball_GetOpponent(playerid) == killerid) {
				new Float:health,
					Float:armour,
					tempoduel = GetPVarInt(killerid, "duelo");

				GetPlayerHealth(killerid, health);
				GetPlayerArmour(killerid, armour);

				if ((health + armour) >= 200.0)
					format(string, sizeof(string), "[X1 PAINTBALL]: "C_CYAN"%s "C_WHITE"derrotou "C_RED"%s "C_WHITE"| Tempo: %s | "C_GREEN"PERFECT", PlayerName[killerid], PlayerName[playerid], ConvertTime(gettime() - tempoduel));
				else
					format(string, sizeof(string), "[X1 PAINTBALL]: "C_CYAN"%s "C_WHITE"derrotou "C_RED"%s "C_WHITE"| Tempo: %s | Vida: %.0f", PlayerName[killerid], PlayerName[playerid], ConvertTime(gettime() - tempoduel), (health + armour));
				
				Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);

				PlayerPaintball_SetOpponent(playerid, INVALID_PLAYER_ID);
				PlayerPaintball_SetOpponent(killerid, INVALID_PLAYER_ID);
				DeletePVar(killerid, "duelo");
				DeletePVar(playerid, "duelo");
				Paintball_Spawn(killerid);
				Paintball_Spawn(playerid);

				return 1;
			}
			SetPlayerHealth(killerid, 100.0);
			SetPlayerArmour(killerid, 100.0);

			foreach (new i : Player) if (Player_GetPaintball(i) == pbid) PlayerTextdraw_UpdatePaintball(playerid);
		}
		return 1;
	}
	return 1;
}

hook OnPlayerConnect(playerid)
{
	Player_SetPaintball(playerid, INVALID_PAINTBALL_ID);
    PlayerPaintball_SetOpponent(playerid, INVALID_PLAYER_ID);

	CreatePlayerTD_Paintball(playerid);

	return 1;
}

hook OnPlayerResetVars(playerid)
{
	new opponent = PlayerPaintball_GetOpponent(playerid),
		pbid = Player_GetPaintball(playerid);
		
	if (opponent != INVALID_PLAYER_ID)
	{
		new string[128];
		format(string, sizeof(string), "[X1 PAINTBALL]: "C_WHITE"O jogador %s "C_RED"saiu "C_WHITE"no meio de um x1 contra "C_CYAN"%s", PlayerName[playerid], PlayerName[opponent]);
  		Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);

		if (Player_GetPaintball(opponent) != INVALID_PAINTBALL_ID) {
			SpawnPlayer(opponent);
			printf("OnPlayerResetVars(opponent): %d", opponent);
		}
       	PlayerPaintball_SetOpponent(opponent, INVALID_PLAYER_ID);
       	PlayerPaintball_SetOpponent(playerid, INVALID_PLAYER_ID);
  	}
	Paintball_Exit(playerid);
	stop timer_entry_pb[playerid];
	stop timerCountDuel[playerid];

	return 1;
}

hook OnPlayerSpawn(playerid)
{
	PlayerPaintball_ResetCombo(playerid);
	return 1;
}

CALLBACK: OnChatPaintball(playerid, const text[])
{
	new pbid = Player_GetPaintball(playerid),
		string[128];
		
	if (pbid != INVALID_PAINTBALL_ID)
	{
		format(string, sizeof(string), "[%s"C_GREEN"]: %s(%d): "C_WHITE"%s", GetRankedLevel(playerid), PlayerName[playerid], playerid, text);
		Paintball_SendMessage(pbid, COLOR_GREEN, string);
		log_chat(playerid, string);

		return true;
	}
	return false;
}

stock Paintball_Spawn(playerid)
{
	new pbid = Player_GetPaintball(playerid),
		rdon = random(15);

	SetPlayerPos(playerid, PaintballSpawn[rdon][0], PaintballSpawn[rdon][1], PaintballSpawn[rdon][2]);
	SetPlayerFacingAngle(playerid, PaintballSpawn[rdon][3]);
	SetPlayerInterior(playerid, 10);
	SetPlayerVirtualWorld(playerid, Paintball_GetWorld(pbid));

	SetPlayerHealth(playerid, 100.0);
	SetPlayerArmour(playerid, 100.0);

	ResetPlayerWeapons(playerid);

	for (new w; w < 13; w++)
		GivePlayerWeapon(playerid, Paintball_GetWeapon(pbid, w), 9999);

	return 1;
}

stock Paintball_Bolt(playerid, opponent)
{
	Paintball_Spawn(playerid);

	if (Player_GetPaintball(opponent) != INVALID_PAINTBALL_ID)
		Paintball_Spawn(opponent);

	PlayerPaintball_SetOpponent(playerid, INVALID_PLAYER_ID);
	PlayerPaintball_SetOpponent(opponent, INVALID_PLAYER_ID);

	stop timerCountDuel[playerid];

	return 1;
}

stock Paintball_ShowDialog(playerid) 
{
	new status[25],
		string[128],
		item[MAX_PAINTBALLS + 1],
		count;

	MEGAString[0] = EOS;
	strcat(MEGAString, "id	nome\tstatus\n");

	foreach (new pb : IterPaintballs)
	{
		if (Paintball_GetLock(pb)) status = ""C_RED"TRANCADA";
		else status = ""C_GREEN"ABERTA";

		format(string, sizeof(string), ""C_GRAY"%d	"C_WHITE"%s\t%s\n", pb, Paintball_GetName(pb), status);
		strcat(MEGAString, string);

		item[count] = pb;
		count++;
	}
	item[count] = 1000;
	strcat(MEGAString, ""C_GREEN"---> Criar minha sala!");

	inline D_Paintball(mdlid, mdldialogid, mdlresponse, mdllistitem, string:mdltext[])
	{
		#pragma unused mdlid, mdldialogid, mdltext
		if (!mdlresponse)
			return 1;

		new pbid = item[mdllistitem];
		if (pbid == INVALID_PAINTBALL_ID) return 1;

		if (pbid == 1000) {
			MEGAString[0] = EOS;

			if (Player_GetVIP(playerid) < SOCIO_SUPREME)
				return SendClientMessage(playerid, COLOR_LIGHTRED, "Apenas jogadores SOCIO-SUPREME+ pode adquirir uma sala do paintball.");

			strcat(MEGAString, 
				""C_WHITE"Voce esta prestes a criar sua sala de "C_PAINTBALL"PAINTBALL"C_WHITE".\n\
				Nela voce podera editar as armas, abrir e fechar, mudar tempo do round, e privacidade.\n\n\
				Para criar sua sala voce devera escolher um nome abaixo e pagar "C_GREEN"20.000 cash\n");

			inline D_PaintballCreate(did, ddialogid, dresponse, dlistitem, string:dtext[])
			{
				#pragma unused did, ddialogid, dlistitem

				if (!dresponse)
					return 1;

				new id = Iter_Free(IterPaintballs);
				if (id == INVALID_ITERATOR_SLOT)
					return SendClientMessage(playerid, -1, "Não há mais vagas de salas de paintball.");

				if (strlen(dtext) < 3 || strlen(dtext) > 34)
					return SendClientMessage(playerid, -1, "Escolha um nome de 3 a 34 caracteres.");

				if (Player_GetCash(playerid) < 20000)
					return SendClientMessage(playerid, -1, "Você não tem 20.000 cash.");

				Player_RemoveCash(playerid, 20000);

				new weapons[13][128];

				MySQL_BindInt(stmt_createPaintball, 0, Player_GetAccountID(playerid));
				MySQL_Bind(stmt_createPaintball, 1, dtext, true);
				MySQL_Bind(stmt_createPaintball, 2, "-", true);
				MySQL_BindInt(stmt_createPaintball, 3, 0);
				MySQL_BindInt(stmt_createPaintball, 4, (id * 1000));
				MySQL_BindInt(stmt_createPaintball, 5, (5 * 60000));
				MySQL_BindInt(stmt_createPaintball, 6, 1);
				MySQL_Bind(stmt_createPaintball, 7, "24,25", true);

				inline const OnPaintballCreated() {
					Iter_Add(IterPaintballs, id);

					Paintball_SetID(id, cache_insert_id());
					Paintball_SetOwner(id, Player_GetAccountID(playerid));
					Paintball_SetName(id, dtext);
					Paintball_SetDescription(id, "-");
					Paintball_SetLock(id, false);
					Paintball_SetWorld(id, (10000 * id));
					Paintball_SetRoundTime(id, (5 * 60000));
					Paintball_SetX1(id, true);
					
					split("24,25", weapons, ',');
					for(new w; w < 13; w++)
						Paintball_SetWeapon(id, w, weapons[w]);

					printf("Paintball %d: %s created...", pbid, dtext);
				}
				MySQL_ExecuteThreaded_Inline(stmt_createPaintball, using inline OnPaintballCreated);
			}
			Dialog_ShowCallback(playerid, using inline D_PaintballCreate, DIALOG_STYLE_INPUT, ""C_PAINTBALL"PAINTBALL", MEGAString, "Selecionar", "Fechar");

			return 1;
		}

		if (Paintball_GetLock(pbid) && Paintball_GetOwner(pbid) != Player_GetAccountID(playerid))
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Essa sala do paintball está trancada!");

		if (IsPlayerInCombat(playerid)) 
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você só poderá entrar 1 minuto após tomar dano de alguém!");

		timer_entry_pb[playerid] = defer timerPlayerEntryPb[Timer:30000](playerid, pbid);

		ShowPlayerBaloonInfo(playerid, "Aguarde ~g~~h~30 segundos ~w~para entrar na sala do ~b~~h~PAINTBALL", 5000);
		TogglePlayerControllable(playerid, false);
		
		return 1;
	}
	Dialog_ShowCallback(playerid, using inline D_Paintball, DIALOG_STYLE_TABLIST_HEADERS, ""C_PAINTBALL"PAINTBALL", MEGAString, "Selecionar", "Fechar");
	return 1;
}

stock PlayerTextdraw_UpdatePaintball(playerid)
{
	new string[128],
		pbid = Player_GetPaintball(playerid),
		winner = Paintball_GetWinner(pbid);

	if (winner != INVALID_PLAYER_ID) {
		format(string, sizeof string, "~g~~h~1| ~w~%s~n~~r~~h~KILLS: ~w~%d", PlayerName[winner], Player_GetArenaKills(winner));
		PlayerTextDrawSetString(playerid, ptd_paintball[playerid], string);
	}
	else PlayerTextDrawSetString(playerid, ptd_paintball[playerid], "~g~~h~1| ~w~-~n~~r~~h~KILLS: ~w~0");
}

stock Paintball_StartDuel(playerid, playerid2)
{
	new pbid = Player_GetPaintball(playerid),
		world = Paintball_GetWorld(pbid);

	// player1
	SetPlayerPos(playerid, 1372.0150,-19.9670,1200.9219);
	SetPlayerFacingAngle(playerid, 270.1552);
	SetPlayerInterior(playerid, 1);

 	SetPlayerHealth(playerid, 100.0);
 	SetPlayerArmour(playerid, 100.0);
 	SetPlayerArmedWeapon(playerid, WEAPON_DEAGLE);

 	SetCameraBehindPlayer(playerid);
 	TogglePlayerControllable(playerid, false);
	PlayerPaintball_SetOpponent(playerid, playerid2);

    // player2
	SetPlayerPos(playerid2, 1405.1292,-19.4831,1200.9130);
	SetPlayerFacingAngle(playerid2, 89.8343);
	SetPlayerInterior(playerid2, 1);
 	SetPlayerVirtualWorld(playerid2, playerid + world);

 	SetPlayerHealth(playerid2, 100.0);
 	SetPlayerArmour(playerid2, 100.0);
 	SetPlayerArmedWeapon(playerid2, WEAPON_DEAGLE);
 	
	SetCameraBehindPlayer(playerid2);
    TogglePlayerControllable(playerid2, false);
	PlayerPaintball_SetOpponent(playerid2, playerid);

 	new string[128];
    format(string, sizeof(string), "[X1 PAINTBALL]: "C_WHITE"O jogador "C_CYAN"%s "C_WHITE"aceitou duelar contra "C_CYAN"%s"C_WHITE"!", PlayerName[playerid2], PlayerName[playerid]);
    Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);

	timerCountDuel[playerid] = defer CountDuel(playerid, playerid2, 5);
}

stock PlayerPaintball_CheckCombo(playerid, killerid)
{
	if (gettime() > PlayerPaintball_GetComboTimer(killerid))
		PlayerPaintball_SetComboKills(killerid, 0);

	new kills = PlayerPaintball_GetComboKills(killerid),
		pbid = Player_GetPaintball(playerid);

	PlayerPaintball_SetComboKills(killerid, (gettime() + 20));
	PlayerPaintball_SetComboKills(killerid, kills + 1);

	new string[145],
		killsp = PlayerPaintball_GetComboKills(playerid);

    if (killsp > 4) {
	    format(string, sizeof(string), "[PAINTBALL-KILLS]: "C_CYAN"%s "C_WHITE"interrompeu um combo de "C_RED"%d mortes"C_WHITE" de "C_CYAN"%s", PlayerName[killerid], killsp, PlayerName[playerid]);
		Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);
    }
    if (kills == 5) {
	    format(string, sizeof(string), "[PAINTBALL-KILLS]: "C_CYAN"%s "C_WHITE"está implacável com uma sequencia de "C_RED"%d mortes", PlayerName[killerid], kills);
		Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);
    }
    else if (kills == 10)
	{
	    format(string, sizeof(string), "[PAINTBALL-KILLS]: "C_CYAN"%s "C_WHITE"se tornou lendário com uma sequencia de "C_RED"%d mortes", PlayerName[killerid], kills);
		Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);
    }
	return 1;
}

stock Paintball_SendMessage(pbid, COLOR, const message[])
	foreach(new i : Player) if (Player_GetPaintball(i) == pbid) SendClientMessage(i, COLOR, message);

stock Paintball_SendDeathMessage(killerid, playerid, reason)
	foreach(new i : Player) if (ChatKill[i] && Player_GetPaintball(i) != INVALID_PAINTBALL_ID) SendDeathMessageToPlayer(i, killerid, playerid, reason);

stock Paintball_Exit(playerid)
{
    new pbid = Player_GetPaintball(playerid);
    if (pbid != INVALID_PAINTBALL_ID)
    {
        new string[56];
        format(string, sizeof(string), "--> %s saiu da sala de paintball!", PlayerName[playerid]);
        Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);

        Player_SetPaintball(playerid, INVALID_PAINTBALL_ID);

        SetPlayerPos(playerid, 2695.5930, -1704.6952, 11.8438);
        SetPlayerInterior(playerid, 0);
        SetPlayerVirtualWorld(playerid, 0);

        PlayerTextDrawHide(playerid, ptd_paintball[playerid]);
        ResetPlayerWeapons(playerid);
        Paintball_LoadEntry(playerid);
    }
	Paintball_DestroyTextLabel(playerid);
}

static Paintball_GetWinner(pbid)
{
    new wins = INVALID_PLAYER_ID,
		winsKills = 0,
        kills_rod;

    foreach(new i : Player) {
        if (Player_GetPaintball(i) == pbid) 
        {
            kills_rod = Player_GetArenaKillsRod(i);
            if (kills_rod > winsKills) {
                winsKills = kills_rod;
                wins 	  = i;
            }
        }
    }
    return wins;
}

stock Paintball_Open(playerid, pbid)
{
	new round_time = Paintball_GetRoundTime(pbid),
        lock = Paintball_GetLock(pbid);

	stop timerNewRound[pbid];
    
	if (lock) {
        Paintball_SetLock(pbid, false);
		SendMsgAllF(COLOR_PAINTBALL, "PAINTBALL | "C_WHITE"%s abriu a sua sala de Paintball [%s].", PlayerName[playerid], Paintball_GetName(pbid));

		timerNewRound[pbid] = defer Paintball_NewRound[Timer:round_time](pbid);
	} else {
        Paintball_SetLock(pbid, true);
		SendMsgAllF(COLOR_PAINTBALL, "PAINTBALL | "C_WHITE"%s fechou a sua sala de Paintball [%s].", PlayerName[playerid], Paintball_GetName(pbid));

        foreach(new i : Player)
            if (Player_GetPaintball(i) == pbid) Paintball_Exit(i);
	}
	return 1;
}