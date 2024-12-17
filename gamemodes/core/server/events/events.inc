// ------------------------------------------------------
// Eventos:

#include <YSI_Coding\y_hooks>

#if defined _INC_events
    #if !defined _INC_events
        #define _INC_events true
    #endif
#endif

#include <samp-random-events-entry>
#include <others\event-quiz-entry>
#include <samp-random-events>
// #include <derby>

//--- Textdraws corridas
new
	Text:		raceBox,
	Text:		raceTotalPlayers,
	Text:		raceBoxPos,
	Text:		raceRisco,
	Text:		raceTempo,
	Text:		racePos[7],
	Text:		raceTime[7],
	Text:		raceCount,
	PlayerText: racePosicao		[MAX_PLAYERS],
	PlayerText: textGanhou1 	[MAX_PLAYERS],
	PlayerText: textGanhou2 	[MAX_PLAYERS],
	PlayerText: textPremioXP	[MAX_PLAYERS],
	PlayerText: textPremioGrana	[MAX_PLAYERS],
	Text:		textPremio1,
	Text:		textPremio2,
	Text:		textPremio3,
	Text:		textPremioMsg;

// --- Events Entry

enum EventType {
    EVENT_NONE,
    EVENT_X1,
};

enum EVENT_ENUM {
    bool:eventStarted,
    EventType:eventType,
    eventStage,
    eventInvite,
};
static EventInfo[EVENT_ENUM];

new Iterator:PlayersEvent<MAX_PLAYERS>;

stock Event_SetStatus(bool:stats) {
    EventInfo[eventStarted] = stats;
}

stock Event_GetStatus() {
    return EventInfo[eventStarted];
}

stock Event_GetStage() {
    return EventInfo[eventStage];
}

stock Event_SetStage(stage) {
    EventInfo[eventStage] = stage;
}

stock Event_SetTimerInvite(seconds) {
    EventInfo[eventInvite] = gettime() + seconds;
}

stock Event_TimerInvite() {
    return EventInfo[eventInvite];
}

stock PlayerInEvento(playerid)
{
	if (JoinedHay[playerid] == true || GetPVarInt(playerid, "inFall") == 1 || IsPlayerInSurvival(playerid) || Player_InEvent(playerid))
	    return true;

	return false;
}

stock EventType:Event_GetType() {
    return EventInfo[eventType];
}

stock Event_SetType(EventType:type) {
    EventInfo[eventType] = type;
}

stock Event_PlayerExit(playerid) {
    if (!Player_InEvent(playerid))
        return SendClientMessage(playerid, -1, "Você não está em nenhum evento.");

    Iter_Remove(PlayersEvent, playerid);

    Player_SetInEvent(playerid, false, EVENT_NONE);
    Player_SetEventStage(playerid, 0);

    SendClientMessage(playerid, -1, "Você saiu do evento.");

    return 1;
}

stock Event_PlayerEntry(playerid) {

    if (!Event_GetStatus()) 
        return SendClientMessage(playerid, -1, "Não tem nenhum evento no momento."), 0;

    if (Player_InEvent(playerid))
        return SendClientMessage(playerid, -1, "Você já está em um evento. Use: /sairevento"), 0;

    if (gettime() > Event_TimerInvite())
        return SendClientMessage(playerid, -1, "O tempo para entrar no evento se esgotou."), 0;

    switch (Event_GetType()) {
        case EVENT_X1: {
            Iter_Add(PlayersEvent, playerid);

            Player_SetInEvent(playerid, true, EVENT_X1);
            Player_SetEventStage(playerid, 0);

            SendClientMessage(playerid, -1, "Você entrou no evento X1, aguarde para participar.");
        }
    }
    return 1;
}

// #include <event_x1>
#include <event_survival>
#include <event_hay>

// hook OnPlayerDeath(playerid, killerid, reason) 
// {
// 	if (killerid != INVALID_PLAYER_ID) {
// 		if (killerid == EventX1_GetCombat(1) || killerid == EventX1_GetCombat(2)) {
// 			if  ((killerid == EventX1_GetCombat(1) && playerid == EventX1_GetCombat(2)) || 
// 				(killerid == EventX1_GetCombat(2) && playerid == EventX1_GetCombat(2))) {
// 				X1_Finished(killerid, playerid);

// 				SendDeathMessage(killerid, playerid, reason);
// 			}
// 		}
// 	}
// 	return 1;
// }

// hook OnPlayerDisconnect(playerid, reason) 
// {
// 	if (Player_InEvent(playerid)) {
//         Event_PlayerExit(playerid);
//     }

//     if (playerid == EventX1_GetCombat(1)) {
// 		X1_Finished(EventX1_GetCombat(2), playerid);
// 	} else if (playerid == EventX1_GetCombat(2)) {
// 		X1_Finished(EventX1_GetCombat(1), playerid);
// 	}
// 	return 1;
// }