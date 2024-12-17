enum CPEnum {
    cpID,
    Float:cpPos[3],
    Float:cpSize,
    bool:cpExists,
    bool:cpCloseOnEnter
};

new PlayerCheckpoint[MAX_PLAYERS][CPEnum];

bns_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size, id = -1, bool:closeOnEnter = true) {
    PlayerCheckpoint[playerid][cpID] = id;
    PlayerCheckpoint[playerid][cpPos][0] = x;
    PlayerCheckpoint[playerid][cpPos][1] = y;
    PlayerCheckpoint[playerid][cpPos][2] = z;
    PlayerCheckpoint[playerid][cpSize] = size;
    PlayerCheckpoint[playerid][cpExists] = true;
    PlayerCheckpoint[playerid][cpCloseOnEnter] = closeOnEnter;
    return SetPlayerCheckpoint(playerid, x, y, z, size);
}

bns_DisablePlayerCheckpoint(playerid) {
    PlayerCheckpoint[playerid][cpExists] = false;
    return DisablePlayerCheckpoint(playerid);
}

IsCloseOnEnterCheckpoint(playerid) {
    return PlayerCheckpoint[playerid][cpCloseOnEnter];
}

#define SetPlayerCheckpoint bns_SetPlayerCheckpoint
#define DisablePlayerCheckpoint bns_DisablePlayerCheckpoint