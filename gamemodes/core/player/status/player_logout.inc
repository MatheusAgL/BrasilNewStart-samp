#include <YSI_Coding\y_hooks>

stock GetDisconnectReasonName(reason) {
    new reasonName[30];
    if(reason == 0)
        reasonName = "Erro de conexao ou crash";
    else if(reason == 1)
        reasonName = "Vontade propria";
    else if(reason == 2)
        reasonName = "Kickado ou banido";
    else
        reasonName = "Causa desconhecida";
    
    return reasonName;
}

timer TimerDestroyLogoutMark[90 * 1000](Text3D:logoutMark) {
    DestroyDynamic3DTextLabel(logoutMark);
}


hook OnPlayerDisconnect(playerid, reason) {

	if (SpectadorInfo[playerid][spectadorID] != INVALID_PLAYER_ID) {
        new string[128], Float:pos[3];

        format(
            string, sizeof(string),
            "Deslogou | %s\n\n{FFFFFF}%s\n%s",
            GetDisconnectReasonName(reason),
            PlayerName[playerid],
            GetCurrentDateHour(BR_CURRENT_ALL)
        );

        GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

        new Text3D:logoutMark = CreateDynamic3DTextLabel(string, 0xFF7C7DAA, pos[0], pos[1], pos[2], 10.0);
        defer TimerDestroyLogoutMark(logoutMark);
    }
    return 1;
}