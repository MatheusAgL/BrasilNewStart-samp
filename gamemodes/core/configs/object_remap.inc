// Evita crash no GMX

#include <YSI_Coding\y_hooks>

static AlreadyDestroyed[MAX_PLAYERS];

hook OnGameModeInit() {
    foreach(new p : Player) {
        AlreadyDestroyed[p] = 1;
    }
    return 1;
}

hook OnPlayerDisconnect(playerid) {
    AlreadyDestroyed[playerid] = 0;
    return 1;
}

bns_RemoveBuildingForPlayer(playerid, modelid, Float:x, Float:y, Float:z, Float:range) {
    if(!AlreadyDestroyed[playerid]) {
        return RemoveBuildingForPlayer(playerid, modelid, x, y, z, range);
    }
    return 0;
}

//#undef RemoveBuildingForPlayer
#define RemoveBuildingForPlayer bns_RemoveBuildingForPlayer