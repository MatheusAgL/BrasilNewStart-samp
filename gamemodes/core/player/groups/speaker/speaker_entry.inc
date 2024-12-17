#define         COLOR_SPEAKER           0x4682B4AA
#define         C_SPEAKER               "{4682B4}"
#define         C_SPEAKERD              "{708090}"
#define         MAX_MUSIC_ORDERS        30              // Máximo de pedidos de músicas

enum SpeakerNivel: {
    SPEAKER_NONE,
    ESTAGIARIO_RADIO,
    LOCUTOR_RADIO,
    COORDENADOR_RADIO,
    GERENTE_RADIO,
    DIRETOR_RADIO,
    VICEPRESIDENTE_RADIO,
    PRESIDENTE_RADIO,
};

enum ENUM_SPEAKER {
    SpeakerNivel:speakerNivel,
    bool:speakerTender,
};
static SpeakerInfo[MAX_PLAYERS][ENUM_SPEAKER];

stock Speaker_SetNivel(playerid, SpeakerNivel:nivel) {
    SpeakerInfo[playerid][speakerNivel] = nivel;
}

stock SpeakerNivel:Speaker_GetNivel(playerid) {
    return SpeakerInfo[playerid][speakerNivel];
}

stock Speaker_SetTender(playerid, bool:stats) {
    SpeakerInfo[playerid][speakerTender] = stats;
}

stock bool:Speaker_GetTender(playerid) {
    return SpeakerInfo[playerid][speakerTender];
}


// --------------------------------
enum ENUM_RADIO_ORDERS {
    radioOrderTime,
    radioOrderNick[MAX_PLAYER_NAME],
    radioOrderMusic[128],
};
static RadioOrders[MAX_MUSIC_ORDERS][ENUM_RADIO_ORDERS];
new Iterator:IterRadioOrders<MAX_MUSIC_ORDERS>;

stock RadioOrders_SetTime(order, time) {
    RadioOrders[order][radioOrderTime] = time;
}

stock RadioOrders_GetTime(order) {
    return RadioOrders[order][radioOrderTime];
}

stock RadioOrders_SetNick(order, const nick[]) {
    format(RadioOrders[order][radioOrderNick], MAX_PLAYER_NAME, nick);
}

stock RadioOrders_GetNick(order) {
    new nick[MAX_PLAYER_NAME];
    format(nick, sizeof(nick), RadioOrders[order][radioOrderNick]);

    return nick;
}

stock RadioOrders_SetMusic(order, const music[]) {
    format(RadioOrders[order][radioOrderMusic], 128, music);
}

stock RadioOrders_GetMusic(order) {
    new music[128];
    format(music, sizeof(music), RadioOrders[order][radioOrderMusic]);

    return music;
}

// --------------------------------
stock Speaker_GetPositionName(SpeakerNivel:nivel) {
	new radioCargoNome[25];
	switch(nivel)
	{
		case ESTAGIARIO_RADIO:      radioCargoNome = "Estagiário";
        case LOCUTOR_RADIO:         radioCargoNome = "Locutor";
        case COORDENADOR_RADIO:     radioCargoNome = "Coordenador";
        case GERENTE_RADIO:         radioCargoNome = "Gerente";
        case DIRETOR_RADIO:         radioCargoNome = "Diretor";
        case VICEPRESIDENTE_RADIO:  radioCargoNome = "Vice-Presidente da Rádio";
        case PRESIDENTE_RADIO:      radioCargoNome = "Presidente da Rádio";
		default:                    radioCargoNome = "Desconhecido";
	}
	return radioCargoNome;
}

stock Speaker_ChatToAll(COLOR, const message[], SpeakerNivel:nivel = ESTAGIARIO_RADIO)
{
	foreach(new players : Player) {
		if (Speaker_GetNivel(players) >= nivel) 
			SendClientMessage(players, COLOR, message);
    }
}