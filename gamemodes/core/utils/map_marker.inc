#include <YSI_Coding\y_hooks>

enum EnumMapMarkerInfo {
    Text3D:mmID,
    bool:mmEnabled,
    Float:mmPos[3],
    mmText[64]
};
new MapMarkerInfo[MAX_PLAYERS][EnumMapMarkerInfo];

ptask UpdateMapMarker[2000](playerid) {
    if(MapMarkerInfo[playerid][mmEnabled]) {
        new string[128], Float:distance = GetPlayerDistanceFromPoint(
            playerid, 
            MapMarkerInfo[playerid][mmPos][0], MapMarkerInfo[playerid][mmPos][1], MapMarkerInfo[playerid][mmPos][2]
        );
        format(string, sizeof(string), "[ %s ]\n%.0fm", MapMarkerInfo[playerid][mmText], distance);
        UpdateDynamic3DTextLabelText(MapMarkerInfo[playerid][mmID], 0xFE0133FE, string);
    }
}

stock SetPlayerMapMarker(playerid, Float:x, Float:y, Float:z, const text[]) {
    DisablePlayerMapMarker(playerid);

    new string[128];
    new Float:distance = GetPlayerDistanceFromPoint(playerid, x, y, z);

    format(MapMarkerInfo[playerid][mmText], 64, text);
    format(string, sizeof(string), "[ %s ]\n%.0fm", MapMarkerInfo[playerid][mmText], distance);

    //attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = -1, priority = 0 )

    MapMarkerInfo[playerid][mmID] = CreateDynamic3DTextLabel(string, 0xFE0133FE, x, y, z, 20000.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid, 20000.0);
    SetPlayerCheckpoint(playerid, x, y, z, 5.0);
    MapMarkerInfo[playerid][mmEnabled] = true;
    MapMarkerInfo[playerid][mmPos][0] = x;
    MapMarkerInfo[playerid][mmPos][1] = y;
    MapMarkerInfo[playerid][mmPos][2] = z;
}

stock IsPlayerInMapMarker(playerid) {
    return (
        MapMarkerInfo[playerid][mmEnabled] && 
        PlayerToPoint(5.0, playerid, MapMarkerInfo[playerid][mmPos][0], MapMarkerInfo[playerid][mmPos][1], MapMarkerInfo[playerid][mmPos][2])
    );
}

hook OnPlayerEnterCheckpoint(playerid) {
    if(IsPlayerInMapMarker(playerid)) {
        ShowPlayerMessage(playerid, "Voce chegou ate o local marcado", 5000);
        DisablePlayerMapMarker(playerid);
    }
}

stock DisablePlayerMapMarker(playerid) {
    if(MapMarkerInfo[playerid][mmEnabled]) {
        DisablePlayerCheckpoint(playerid);
        DestroyDynamic3DTextLabel(MapMarkerInfo[playerid][mmID]);
        MapMarkerInfo[playerid][mmEnabled] = false;
    }
}


hook OnPlayerDisconnect(playerid, reason) {
    DisablePlayerMapMarker(playerid);
    return 1;
}