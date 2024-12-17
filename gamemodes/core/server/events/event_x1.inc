/*  ----------------------------------------------------------------------------------------------------------------------------------------
        Sistema de evento X1
 ----------------------------------------------------------------------------------------------------------------------------------------- */

#define COLOR_EVENT_X1 0xF03737FF

enum ENUM_EVENT_X1 {
	player1 = INVALID_PLAYER_ID,
	player2 = INVALID_PLAYER_ID,
	x1Active,
	countx1,
	Timer:timer_x1
};
static X1Info[ENUM_EVENT_X1];

static EventX1_CountPart() {
	new count;

	foreach (new i : PlayersEvent) {
		count++;
	}
	return count;
}

timer TimerX1[3000]() {
	if (X1Info[countx1] > 0) {
		X1Info[countx1]--;

		static string[15];
		format(string, sizeof(string), "_~n~_~n~_~n~_~n~%d", X1Info[countx1]);
		GameTextForAll(string, 3000, 6);
	} else {
		GameTextForAll("_~n~_~n~_~n~_~n~||GOGOGO||", 2800, 6);

		SetCameraBehindPlayer(EventX1_GetCombat(1));
		SetCameraBehindPlayer(EventX1_GetCombat(2));
		TogglePlayerControllable(EventX1_GetCombat(1), true);
		TogglePlayerControllable(EventX1_GetCombat(2), true);

		stop X1Info[timer_x1];
	}
}

static Event_StartCombat() {
	X1_SetPlayer(EventX1_GetCombat(1));
	X1_SetPlayer(EventX1_GetCombat(2));

	X1Info[x1Active] = 1;
	X1Info[countx1] = 3;
	X1Info[timer_x1] = repeat TimerX1();
}

stock X1_Finished(idplayer1, idplayer2) {
	SendMsgAllF(COLOR_EVENT_X1, "-: EVENTO X1 :- "C_WHITE"%s "C_GREEN"venceu "C_WHITE"%s com o total de tempo "C_CYAN"%s", PlayerName[idplayer1], PlayerName[idplayer2]);
	SendMsgAllF(COLOR_EVENT_X1, "-: EVENTO X1 :- Agora restam apenas %d participantes no evento de X1!", EventX1_CountPart());

	CheckConquista(idplayer1, Conquista_x1);
	Player_SetEventStage(idplayer1, Event_GetStage() + 1);
	Load_LastPlayerPos(idplayer1);

	EventX1_SetCombat(1, INVALID_PLAYER_ID);
	EventX1_SetCombat(2, INVALID_PLAYER_ID);

	EventX1_RandomFight();
}

static X1_SetPlayer(playerid) {

	ResetPlayerWeapons(playerid);

	GivePlayerWeapon(playerid, WEAPON_DEAGLE, 999);
	GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 999);

	SetPlayerHealth(playerid, 100.0);
	SetPlayerArmour(playerid, 100.0);

	SetPlayerVirtualWorld(playerid, 0);
	if (playerid == EventX1_GetCombat(1)) {
		SetPlayerPos(playerid, 1771.0746, -1775.5294, 1052.4688);
		SetPlayerFacingAngle(playerid, 270.7515);
	} else {
		SetPlayerPos(playerid, 1793.6478, -1775.9736, 1052.4688);
		SetPlayerFacingAngle(playerid, 88.2645);
	}
	TogglePlayerControllable(playerid, false);
}

stock EventX1_SetCombat(playern, playerid) {
	if (playern == 1) {
		X1Info[player1] = playerid;
	} else {
		X1Info[player2] = playerid;
	}
}

stock EventX1_GetCombat(playern) {
	if(!X1Info[x1Active])
		return INVALID_PLAYER_ID;

	if (playern == 1) {
		return X1Info[player1];
	} else {
		return X1Info[player2];
	}
}

stock EventX1_RandomFight() {

	foreach (new i : PlayersEvent) {
		if (Player_InEventStage(i) == Event_GetStage()) {
			if (EventX1_GetCombat(1) == INVALID_PLAYER_ID) {
				saveLastPlayerPos(i);
				EventX1_SetCombat(1, i);
				continue;
			}
			if (EventX1_GetCombat(2) == INVALID_PLAYER_ID) {
				saveLastPlayerPos(i);
				EventX1_SetCombat(2, i);

				SendMsgAllF(COLOR_EVENT_X1, "-: EVENTO X1 :- "C_WHITE"O próximo x1 será entre "C_CYAN"(%s vs %s)", PlayerName[EventX1_GetCombat(1)], PlayerName[EventX1_GetCombat(2)]);
				Event_StartCombat();

				break;
			} else {
				if (EventX1_CountPart() == 1) {
					SendMsgAllF(COLOR_EVENT_X1, "-: EVENTO X1 :- "C_WHITE"Vencedor do evento: "C_GREEN"%s "C_WHITE"recebeu "C_CYAN"500 de cash", PlayerName[i]);

					Player_SetCash(i, Player_GetCash(i) + 500);

					X1Info[x1Active] = 0;
		
				} else {
					Event_SetStage(Event_GetStage() + 1);

					SendMsgAllF(COLOR_EVENT_X1, "-: EVENTO X1 :- "C_WHITE"O evento está começando o Stagio "C_CYAN"%d", Event_GetStage());

					EventX1_RandomFight();
				}
				break;
			}
		}
	}
}

CMD:abrirx1(playerid) {

	if (!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Você não está logado.");

	if (Dev_GetNivel(playerid) < DEV_DELTA)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	if (!Event_GetStatus()) {
		Event_SetStatus(true);
		Event_SetType(EVENT_X1);
		Event_SetStage(0);
		Event_SetTimerInvite(30);

		SendClientMessageToAll(COLOR_EVENT_X1, "-: EVENTO X1 INICIANDO... :- "C_WHITE"Você tem 30 segundos para participar, use: "C_CYAN"/entrarx1");
	} else {
		Event_SetStatus(false);
		Event_SetType(EVENT_NONE);
		Event_SetStage(0);

		foreach (new i : PlayersEvent) {
			Iter_Remove(PlayersEvent, i);
		}
		SendClientMessageToAll(COLOR_EVENT_X1, "-: EVENTO X1 CANCELADO... :- "C_WHITE"Aguarde o próximo!");
	}
	return 1;
}

CMD:startx1(playerid) {

	if (!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Você não está logado.");

	if (Dev_GetNivel(playerid) < DEV_DELTA)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar este comando.");

	EventX1_RandomFight();

	SendMsgAllF(COLOR_EVENT_X1, "-: EVENTO X1 INICIADO... :- "C_WHITE"Stagio 0 iniciado: Possuem "C_CYAN"%d "C_WHITE"participantes!", EventX1_CountPart());

	return 1;
}

CMD:entrarx1(playerid) {

	if (Event_PlayerEntry(playerid)) {
		SendMsgAllF(COLOR_EVENT_X1, "-: EVENTO X1 :- "C_WHITE"Jogador: "C_GREEN"%s "C_WHITE"entrou no evento. Possuem "C_CYAN"%d "C_WHITE"participantes!", PlayerName[playerid], EventX1_CountPart());
	}

	return 1;
}

CMD:sairevento(playerid) {

	Event_PlayerExit(playerid);

	return 1;
}

/*CMD:assistirx1(playerid) {

	Event_PlayerEntry(playerid);

	return 1;
}*/