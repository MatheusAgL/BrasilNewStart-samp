
enum DevNivel: {
    DEV_NONE,
    DEV_BETA,
    DEV_ALPHA,
    DEV_GAMA,
    DEV_DELTA,
    DEV_EPSILON,
    DEV_ZETA,
    DEV_ETA,
    DEV_TETA,
    DEV_IOTA,
    DEV_KAPPA,
    DEV_LAMBDA,
    DEV_MI,
    DEV_NI,
    DEV_XI,
    DEV_OMICRON,
    DEV_PI,
    DEV_RO,
    DEV_SIGMA,
    DEV_TAU,
    DEV_IPSILON,
    DEV_FI,
    DEV_CHI,
    DEV_PSI,
    DEV_OMEGA
};

enum ENUM_DEV {
    DevNivel:devNivel,
    devFunction[34],
};
static DevInfo[MAX_PLAYERS][ENUM_DEV];

stock Dev_SetNivel(playerid, DevNivel:nivel) {
    DevInfo[playerid][devNivel] = nivel;
}

stock DevNivel:Dev_GetNivel(playerid) {
    return DevInfo[playerid][devNivel];
}

stock Dev_GetPositionName(DevNivel:level) {
	new devPositionName[25];
	switch(level)
	{
		case DEV_BETA:          devPositionName = "Beta";
        case DEV_ALPHA:         devPositionName = "Alpha";
        case DEV_GAMA:          devPositionName = "Gama";
        case DEV_DELTA:         devPositionName = "Delta";
        case DEV_EPSILON:       devPositionName = "Epsilon";
        case DEV_ZETA:          devPositionName = "Zeta";
        case DEV_ETA:           devPositionName = "Eta";
        case DEV_TETA:          devPositionName = "Teta";
        case DEV_IOTA:          devPositionName = "Iota";
        case DEV_KAPPA:         devPositionName = "Kappa";
        case DEV_LAMBDA:        devPositionName = "Lambda";
        case DEV_MI:            devPositionName = "MI";
        case DEV_NI:            devPositionName = "NI";
        case DEV_XI:            devPositionName = "XI";
        case DEV_OMICRON:       devPositionName = "Omicron";
        case DEV_PI:            devPositionName = "PI";
        case DEV_RO:            devPositionName = "RO";
        case DEV_SIGMA:         devPositionName = "Sigma";
        case DEV_TAU:           devPositionName = "Tau";
        case DEV_IPSILON:       devPositionName = "Ipsilon";
        case DEV_FI:            devPositionName = "FI";
        case DEV_CHI:           devPositionName = "CHI";
        case DEV_PSI:           devPositionName = "PSI";
        case DEV_OMEGA:         devPositionName = "Omega";
		default:                devPositionName = "Desconhecido";
	}
	return devPositionName;
}

// --------------------------------
stock IsServerCreator(playerid) {
    if (strcmp(PlayerName[playerid], "Theus_Crazzy") &&
        strcmp(PlayerName[playerid], "Joao_Revolts") &&
        strcmp(PlayerName[playerid], "Poderoso_Supremo"))
        return false;

    return true;
}

stock Founders_GetList(playerid) {
    if (strcmp(PlayerName[playerid], "Theus_Crazzy") &&
        strcmp(PlayerName[playerid], "iHollyZinhO") &&
        strcmp(PlayerName[playerid], "Joao_Revolts") &&
        strcmp(PlayerName[playerid], "Poderoso_Supremo") &&
        strcmp(PlayerName[playerid], "MaryJane_VTX") &&
        strcmp(PlayerName[playerid], "ChiLeZiNhO") &&
        strcmp(PlayerName[playerid], "AleK_VTX") &&
        strcmp(PlayerName[playerid], "VkZera_"))
        return false;

    return true;
}