#define         COLOR_YOUTUBER          0xB22222AA
#define         C_YOUTUBER              "{B22222}"
#define         C_YOUTUBERD             "{8B0000}"

enum YoutuberNivel: {
    YOUTUBER_NONE,
    YOUTUBER_INICIANTE,
    YOUTUBER_1K,
    YOUTUBER_10K,
    YOUTUBER_25K,
    YOUTUBER_50K,
    YOUTUBER_70K,
    YOUTUBER_100K,
    RESPONSAVEL_YOUTUBER,
};

enum ENUM_YOUTUBER {
    YoutuberNivel:youtuberNivel,
    bool:youtuberRec,
};
static YoutuberInfo[MAX_PLAYERS][ENUM_YOUTUBER];

stock Youtuber_SetNivel(playerid, YoutuberNivel:nivel) {
    YoutuberInfo[playerid][youtuberNivel] = nivel;
}

stock YoutuberNivel:Youtuber_GetNivel(playerid) {
    return YoutuberInfo[playerid][youtuberNivel];
}

stock Youtuber_SetRec(playerid, bool:stats) {
    YoutuberInfo[playerid][youtuberRec] = stats;
}

stock bool:Youtuber_GetRec(playerid) {
    return YoutuberInfo[playerid][youtuberRec];
}

// --------------------------------
stock Youtuber_GetPositionName(YoutuberNivel:nivel) {
	new radioCargoNome[25];
	switch(nivel) {
		case YOUTUBER_INICIANTE:    radioCargoNome = "Youtuber brotinho";
        case YOUTUBER_1K:           radioCargoNome = "Youtuber 1K+";
        case YOUTUBER_10K:          radioCargoNome = "Youtuber 10K+";
        case YOUTUBER_25K:          radioCargoNome = "Youtuber 25K+";
        case YOUTUBER_50K:          radioCargoNome = "Youtuber 50K+";
        case YOUTUBER_70K:          radioCargoNome = "Youtuber 70K+";
        case YOUTUBER_100K:         radioCargoNome = "Youtuber 100K+";
        case RESPONSAVEL_YOUTUBER:  radioCargoNome = "Responsável Youtubers";
		default:                    radioCargoNome = "Desconhecido";
	}
	return radioCargoNome;
}

stock Youtuber_ChatToAll(COLOR, const message[], YoutuberNivel:nivel = YOUTUBER_INICIANTE)
{
	foreach(new players : Player) {
		if (Youtuber_GetNivel(players) >= nivel) 
			SendClientMessage(players, COLOR, message);
    }
}