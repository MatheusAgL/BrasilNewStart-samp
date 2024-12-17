

#if !defined actions_included
	#include <td-actions>           // https://github.com/dimmyi/td-actions
#endif

// Erro conhecido por nome muito longo de callback;
// Biblioteca YSI:
DEFINE_HOOK_REPLACEMENT(OnVehicle, OV_);

// -------------------------------------------------

#define     MAX_DERBY_PLAYERS       26
#define     DERBY_MINUTES           5


#define     C_WHITE             "{FFFFFF}"
#define     C_RED               "{FF0000}"
#define     COLOR_YELLOW        0xFFF000FF
#define     C_YELLOW            "{FFF000}"
#define     C_RED               "{FF0000}"
#define     C_GREEN             "{00FF00}"

new 
    Iterator:PlayersDerby<MAX_DERBY_PLAYERS>,
    bool:playerPlayDerby[MAX_PLAYERS],
    playerDerbySpec[MAX_PLAYERS],
    bool:derbyStart,
    derbyCar[MAX_PLAYERS],
    derbyPlayers,
    derbyTime,
    derbyTimer,
    derbyTimerStart;

new derbyVote[2];

new Float:derbySpawn[MAX_DERBY_PLAYERS][4] = {
    {817.7307,4543.5376,17.2458,270.2914},
    {772.6514,4543.9004,17.2458,89.9088},
    {792.0927,4563.1953,17.2304,359.6661},
    {792.0832,4522.2334,17.2305,179.5086},
    {791.9821,4490.3506,27.5854,179.2964},
    {844.8969,4543.7715,27.2403,269.1624},
    {791.8098,4594.5825,26.8612,359.7111},
    {734.3566,4543.8262,30.8603,89.7765},
    {715.8024,4550.2627,39.9954,359.8230},
    {717.8143,4601.1279,39.9911,220.9421},
    {764.9551,4543.7524,40.0242,269.1233},
    {718.0518,4487.2388,39.9923,318.1865},
    {789.7573,4568.5298,40.0709,180.4135},
    {792.8224,4520.8037,40.0763,0.5000},
    {816.9938,4543.7759,40.0242,269.7262},
    {868.6559,4486.4961,39.9940,47.9267},
    {869.7164,4547.5513,39.9954,1.5651},
    {867.1855,4599.5718,39.9926,135.2095},
    {736.1015,4616.3384,39.9835,220.0632},
    {849.1599,4618.2300,39.9940,143.4852},
    {735.0769,4468.3252,39.9940,322.2218},
    {794.5975,4466.1870,39.9982,270.3296},
    {849.8888,4468.0835,39.9940,36.6699},
    {764.2360,4506.0376,18.5323,270.6186},
    {829.9869,4509.4961,18.6344,1.3059},
    {760.4803,4506.0049,18.5512,271.5792}
};

stock Derby_GetPlayers() {
    return derbyPlayers;
}

stock Derby_SetVote(vote, value) {
    derbyVote[vote] = value;
}

stock Derby_GetVote(vote) {
    return derbyVote[vote];
}

stock Derby_SetStarted(bool:stats) {
    derbyStart = stats;
}

stock Derby_GetStarted() {
    return derbyStart;
}

stock Derby_SetTime(time) {
    derbyTime = time;
}

stock Derby_GetTime() {
    return derbyTime;
}

stock Derby_SetPlayerPlay(playerid, bool:stats) {
    playerPlayDerby[playerid] = stats;
    
    if (stats)
        derbyPlayers++;
    else
        derbyPlayers--;
}

stock Derby_GetPlayerPlay(playerid) {
    return playerPlayDerby[playerid];
}

stock Derby_SetSpec(playerid, player) {
    playerDerbySpec[playerid] = player;
}

stock Derby_GetSpec(playerid) {
    return playerDerbySpec[playerid];
}