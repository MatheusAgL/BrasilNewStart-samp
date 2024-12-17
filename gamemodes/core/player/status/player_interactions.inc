// ---------------------------------------------------------------------------------
// Include <player_interactions>
// As interações que devem ser analisadas.

stock StopCombat(playerid, playerid2) {
    if (GetPVarInt(playerid, "varPlayerCombateId") == playerid2) {
        SetPVarInt(playerid, "varPlayerCombate",   0);
        SetPVarInt(playerid, "varPlayerCombateId", INVALID_PLAYER_ID);
    }
}

stock StopPlayerSearch(playerid, playerid2)
{
    if (GetPVarInt(playerid, "varProcura") == playerid2) {
        SendClientMessage(playerid, -1, "O jogador que você estava procurando acabou de desconectar.");

        DestroyDynamicObject(GetPVarInt(playerid, "objectProcurar"));
        HidePlayerSearch(playerid);
        RemovePlayerMapIcon(playerid, 99);

        stop timer_procurar[playerid];
        SetPVarInt(playerid, "varProcura", INVALID_PLAYER_ID);
    }
}

stock StopPlayerPact(playerid, playerid2) {

    if (GetPVarInt(playerid, "acordoID") == playerid2) {
        new string[67];
        format(string, sizeof string, "O jogador %s que você tinha um acordo, saiu do servidor.", PlayerName[playerid2]);
        SendClientMessage(playerid, COLOR_YELLOW, string);
        SetPVarInt(playerid, "acordoID", 999);
    }
}


CALLBACK: OnPlayerCheckInteractions(playerid) 
{
    foreach(new players : Player) {
        StopCombat(players, playerid);
        StopPlayerSearch(players, playerid);
        StopPlayerPact(players, playerid);

        // Resetando ligação de telefone
        if (MobileInfo[players][mobileCall] == playerid) {
            MobileInfo[players][mobileCall] = MAX_PLAYERS+5;
        }
    }
    return 1;
}