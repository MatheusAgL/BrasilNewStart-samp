


//------------- Animações em dupla
enum ActionType {
    NONE_ACTION,
	KISS_ACTION,
};

enum ENUM_PAIR_ACTION {
	pairPlayer,
    ActionType:pairAction,
    pairActionStyle,
};

new PairActionInfo[MAX_PLAYERS][ENUM_PAIR_ACTION];

stock PairAction(playerid, idplayer, ActionType:action, style_anim) {
	PairActionInfo[playerid][pairPlayer] = idplayer;
	PairActionInfo[playerid][pairAction] = action;
	PairActionInfo[playerid][pairActionStyle] = style_anim;
	PairActionInfo[idplayer][pairPlayer] = playerid;
	PairActionInfo[idplayer][pairAction] = action;
	PairActionInfo[idplayer][pairActionStyle] = style_anim;
}

stock PairAction_GetPair(playerid)
    return PairActionInfo[playerid][pairPlayer];

stock PairAction_GetActionStyle(playerid)
    return PairActionInfo[playerid][pairPlayer];

stock PairAction_Cancel(playerid) {
    new playerPair = PairActionInfo[playerid][pairPlayer];

    if (playerPair != INVALID_PLAYER_ID) {
        PairActionInfo[playerid][pairPlayer] = INVALID_PLAYER_ID;
        PairActionInfo[playerid][pairAction] = NONE_ACTION;
        PairActionInfo[playerid][pairActionStyle] = 0;

        PairActionInfo[playerPair][pairPlayer] = INVALID_PLAYER_ID;
        PairActionInfo[playerPair][pairAction] = NONE_ACTION;
        PairActionInfo[playerPair][pairActionStyle] = 0;
    }
}

hook OnPlayerConnect(playerid) 
{
    PairAction_Cancel(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) 
{
    PairAction_Cancel(playerid);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (newkeys & KEY_YES) {
        if (PairAction_GetPair(playerid) != INVALID_PLAYER_ID) {
            new playerPair = PairAction_GetPair(playerid);

            if (!ProxDetectorS(1.0, playerid, playerPair))
                return SendClientMessage(playerid, -1, "Você não está próximo do jogador. Caso queira cancelar pressione 'N'.");

            new style = PairAction_GetActionStyle(playerid);
            AnimAccept_Kiss(playerid, playerPair, style);

            PairAction_Cancel(playerid);
        }
    } else if (newkeys & KEY_NO) {
        if (PairAction_GetPair(playerid) != INVALID_PLAYER_ID) {
            new playerPair = PairAction_GetPair(playerid);

            if (!ProxDetectorS(1.0, playerid, playerPair))
                return SendClientMessage(playerid, -1, "Você não está próximo do jogador. Caso queira cancelar pressione 'N'.");

            SendMsgF(playerid, -1, "Você negou o pedido de beijo de %s", PlayerName[playerPair]);
            PairAction_Cancel(playerid);
        }
    }
    return 1;
}

stock AnimAccept_Kiss(playerid, idplayer, style) 
{
	new 
        string[78],
	    Float:x, 
        Float:y, 
        Float:z;

	GetPlayerPos(idplayer, x, y, z);
	SetPlayerFaceToPoint(playerid, x, y);
	GetPlayerPos(playerid, x, y, z);
	SetPlayerFaceToPoint(idplayer, x, y);

	format(string, sizeof(string), "* %s e %s estão se beijando...", PlayerName[playerid], PlayerName[idplayer]);
	SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

    switch (style) {
        case 1: {
            ApplyAnimation(idplayer, "KISSING", "Playa_Kiss_01", 4.1, false, false, false, false, SYNC_ALL);
            ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_01", 4.1, false, true, false, false, SYNC_ALL);
        }
        case 2: 
        {
            ApplyAnimation(idplayer, "KISSING", "Playa_Kiss_02", 4.1, false, false, false, false, SYNC_ALL);
            ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_02", 4.1, false, true, false, false, SYNC_ALL);
        }
        default: 
        {
            ApplyAnimation(idplayer, "KISSING", "Playa_Kiss_03", 4.1, false, false, false, false, SYNC_ALL);
            ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_03", 4.1, false, true, false, false, SYNC_ALL);
        }
    }
	CheckConquista(playerid, Conquista_Beijo);
	CheckConquista(idplayer, Conquista_Beijo);
}

#include <anims_cmds>