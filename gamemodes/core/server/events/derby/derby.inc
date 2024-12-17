#include <YSI_Coding\y_hooks>

#include <derby_entry>
#include <derby_maps>

hook OnGameModeInit() {
    CreateMaps_Derby();

    derbyTimer = SetTimer("UpdateDerbyEvent", 1000, true);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {

    if (Derby_GetPlayerPlay(playerid)) {
        Derby_PlayerExit(playerid);
    }
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) {

    if (Derby_GetPlayerPlay(playerid)) {
        if (Iter_Contains(PlayersDerby, playerid))
            Derby_PlayerEliminated(playerid);
    }

    return 1;
}

hook OnVehicleDeath(vehicleid, killerid) {

    foreach(new i : PlayersDerby) {
        if (vehicleid == derbyCar[i]) {
            if (Iter_Contains(PlayersDerby, i))
                Derby_PlayerEliminated(i);
        }
    }
    return 1;
}

hook OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate) {

    if (oldstate == PLAYER_STATE_DRIVER) {
        if (Iter_Contains(PlayersDerby, playerid))
            Derby_PlayerEliminated(playerid);
    }
    return 1;
}

hook OnPlayerSpawn(playerid) {

    if (Derby_GetPlayerPlay(playerid)) {
        if (!Iter_Contains(PlayersDerby, playerid)) {
            new spec = Iter_First(PlayersDerby),
                veh = GetPlayerVehicleID(spec);

            Derby_SetSpec(playerid, spec);
            PlayerSpectateVehicle(playerid, veh);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (newkeys & KEY_SECONDARY_ATTACK)
	{
        if (Derby_GetPlayerPlay(playerid)) {
            if (!Iter_Contains(PlayersDerby, playerid)) {
                new spec = Derby_GetSpec(playerid),
                    veh;

                if (spec == Iter_Last(PlayersDerby)) {
                    spec = Iter_First(PlayersDerby);
                } else {
                    spec = Iter_Next(PlayersDerby, spec);
                }
                veh = GetPlayerVehicleID(spec);
                Derby_SetSpec(playerid, spec);
                PlayerSpectateVehicle(playerid, veh);
            }
        }
	}
    return 1;
}

hook OnPlayerUpdate(playerid) {

    if (Derby_GetStarted()) {
        if (Iter_Contains(PlayersDerby, playerid)) {
            new Float:x, Float:y, Float:z;

            GetPlayerPos(playerid, x, y, z);
            if (z < 4.3) {
                Derby_PlayerEliminated(playerid);
            }
        }
    }
    return 1;
}

hook OV_DamageStatusUpdate(vehicleid, playerid) {

    if (Iter_Contains(PlayersDerby, playerid)) {
        if (Derby_GetVote(1) > Derby_GetVote(0))
            SetVehicleHealth(vehicleid, 10000);
    }
    return 1;
}

forward DerbyTimerStart();
public DerbyTimerStart() 
{
    Derby_Start();
    return 1;
}

forward UpdateDerbyEvent();
public UpdateDerbyEvent() 
{
    if (Derby_GetStarted()) {
        Derby_SetTime(Derby_GetTime() - 1);

        new string[10];
        if (Derby_GetTime() > 10)
            format(string, sizeof(string), "~g~%s", ConvertTime(Derby_GetTime()));
        else
            format(string, sizeof(string), "~r~%s", ConvertTime(Derby_GetTime()));

        foreach (new i : PlayersDerby)
            GameTextForPlayer(i, string, 1100, 0);

        if (Derby_GetTime() < 1) {
            Derby_Stop();
        }
    } else {
        if (Derby_GetPlayers() > 1) {
            KillTimer(derbyTimer);
            KillTimer(derbyTimerStart);
            derbyTimerStart = SetTimer("DerbyTimerStart", 10 * 1000, true);
        }
    }
    return 1;
}

stock Derby_SetPlayerIn(playerid) {
    ResetPlayerWeapons(playerid);

    Iter_Add(PlayersDerby, playerid);

    SetPlayerPos(playerid, derbySpawn[playerid][0], derbySpawn[playerid][1], derbySpawn[playerid][2] + 0.3);
    SetPlayerFacingAngle(playerid, derbySpawn[playerid][3]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 50);
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, false);

    ShowActionForPlayer(playerid, ActionDerbyVote, "Veiculos com GODMOD?", .action_time = 10000);
}

stock Derby_PlayerExit(playerid) {

    if (Derby_GetPlayerPlay(playerid)) {
        HideActionForPlayer(playerid);
        TogglePlayerControllable(playerid, true);
        Derby_SetPlayerPlay(playerid, false);
        DisableRemoteVehicleCollisions(playerid, true);

        if (Iter_Contains(PlayersDerby, playerid))
            Derby_PlayerEliminated(playerid);
    }
    return 1;
}

stock Derby_PlayerEntry(playerid) {

    if (Iter_Contains(PlayersDerby, playerid)) 
        return SendClientMessage(playerid, -1, "Você já está no evento Derby.");

    new string[128];

    if (Derby_GetStarted()) {
        format(string, sizeof(string), "A partida já foi iniciada, acabará em %d.", ConvertTime(Derby_GetTime()));
        return SendClientMessage(playerid, -1, string);
    }

    new players_event = Iter_Count(PlayersDerby);

    if (players_event > MAX_DERBY_PLAYERS) {
        format(string, sizeof(string), "A partida está no máximo de %d pessoas.", MAX_DERBY_PLAYERS);
        return SendClientMessage(playerid, -1, string);
    }
    Derby_SetPlayerIn(playerid);
    Derby_SetPlayerPlay(playerid, true);

    players_event = Iter_Count(PlayersDerby);

    if (players_event >= MAX_DERBY_PLAYERS)
        format(string, sizeof(string), ""C_RED"%d", players_event);
    else
        format(string, sizeof(string), ""C_YELLOW"%d", players_event);

    format(string, sizeof(string), ".::DERBY::. "C_WHITE"%s foi para o evento /derby (%s"C_WHITE"/%d players no evento)", PlayerName[playerid], string, MAX_DERBY_PLAYERS);
    Derby_SendMessageToAll(COLOR_YELLOW, string);

    return 1;
}

Action:ActionDerbyVote(playerid, response)
{
    new string[128];

	if (response == ACTION_RESPONSE_YES) {
		SendClientMessage(playerid, -1, "Você votou em SIM para veículos GOD.");

        Derby_SetVote(1, Derby_GetVote(1) + 1);

        new votes = Derby_GetVote(1);
        if (votes > (MAX_DERBY_PLAYERS / 2))
            Derby_Start();

        format(string, sizeof(string), ".::DERBY::. "C_WHITE"%s votou em "C_GREEN"SIM"C_WHITE". (GOD: "C_YELLOW"%d"C_WHITE"| NO GOD: "C_YELLOW"%d)", PlayerName[playerid], votes, Derby_GetVote(0));
        
	} else {
		SendClientMessage(playerid, -1, "Você votou em NÃO para veículos GOD.");

        Derby_SetVote(0, Derby_GetVote(0) + 1);

        new votes = Derby_GetVote(0);
        if (votes > (MAX_DERBY_PLAYERS / 2))
            Derby_Start();

        format(string, sizeof(string), ".::DERBY::. "C_WHITE"%s votou em "C_RED"NÃO"C_WHITE". (GOD: "C_YELLOW"%d"C_WHITE"| NO GOD: "C_YELLOW"%d)", PlayerName[playerid], Derby_GetVote(1), votes);
	}
    Derby_SendMessageToAll(COLOR_YELLOW, string);
}

stock Derby_SetPlayers() {
    foreach(new i : PlayersDerby) {
        HideActionForPlayer(i);
        TogglePlayerControllable(i, true);

        derbyCar[i] = CreateVehicle(470, derbySpawn[i][0], derbySpawn[i][1], derbySpawn[i][2], derbySpawn[i][3], -1, -1, -1);
        SetVehicleVirtualWorld(derbyCar[i], 50);
        PutPlayerInVehicle(i, derbyCar[i], 0);
        DisableRemoteVehicleCollisions(i, false);

        SendClientMessage(i, -1, "O evento vai iniciar... Caso saia do veículo será automaticamente eliminado.");
    }
}

stock Derby_Start() 
{
    Derby_SetStarted(true);
    Derby_SetTime(DERBY_MINUTES * 1000);

    Derby_SetPlayers();

    KillTimer(derbyTimerStart);
    KillTimer(derbyTimer);
    derbyTimer = SetTimer("UpdateDerbyEvent", 1000, true);

    return 1;
}

stock Derby_Stop() {
    new string[128],
        playerid;

    foreach(new i : PlayersDerby) {
        Derby_PlayerEliminated(i);
        playerid = i;
        break;
    }

    if (playerid != INVALID_PLAYER_ID) {
        foreach(new players : Player) {
            if (Derby_GetPlayerPlay(players)) {
                format(string, sizeof(string), "1º "C_GREEN"%s", PlayerName[playerid]);
                ShowPlayerDialog(players, 0, DIALOG_STYLE_MSGBOX, string, ""C_YELLOW"Vencedor do DERBY", "OK", "");
            }
        }
        format(string, sizeof(string), ".::DERBY::. "C_WHITE"A rodada acabou, o vencedor foi: "C_YELLOW"%s", PlayerName[playerid]);
        Derby_SendMessageToAll(COLOR_YELLOW, string);
    }

    Derby_SendMessageToAll(COLOR_YELLOW, ".::DERBY::. "C_WHITE"Começará uma nova rodada em 10 segundos...");

    Derby_SetStarted(false);
    Derby_SetVote(1, 0);
    Derby_SetVote(0, 0);
}

stock Derby_CheckFinish(playerid) {

    new string[128],
        players_event = Iter_Count(PlayersDerby);

    if (players_event <= 1) {
        Derby_SetTime(0);
    } else {
        format(string, sizeof(string), ".::DERBY::. "C_WHITE"%s foi eliminado do evento (%d/%d players restam)", PlayerName[playerid], players_event, MAX_DERBY_PLAYERS);
    }
    Derby_SendMessageToAll(COLOR_YELLOW, string);
}

stock Derby_PlayerEliminated(playerid) {
    Iter_Remove(PlayersDerby, playerid);
    DestroyVehicle(derbyCar[playerid]);
    Derby_CheckFinish(playerid);
    SpawnPlayer(playerid);

    return 1;
}

stock Derby_SendMessageToAll(color, const string[]) {
    foreach(new players : Player) {
        if (Derby_GetPlayerPlay(players)) {
            SendClientMessage(players, color, string);
        }
    }
    return 1;
}

new bool:derbyOff = true;

CMD:derby(playerid) {
    if (derbyOff)
        return SendClientMessage(playerid, -1, "O evento de DERBY está fechado.");

    return Derby_PlayerEntry(playerid);
}

CMD:sairderby(playerid)
    return Derby_PlayerExit(playerid);

CMD:derbytheuzin(playerid)
{
    if (derbyOff == true) {
        derbyOff = false;
    } else {
        derbyOff = true;
    }
    return 1;
}

CMD:testederbytheuzin(playerid) {
    return Derby_Start();
}

CMD:derbytheuzinKickEx(playerid) {
    return Derby_KickAll();
}

stock Derby_KickAll() {
    foreach(new players : Player) {
        if (Derby_GetPlayerPlay(players)) {
            Derby_PlayerExit(players);
        }
    }
    return 1;
}