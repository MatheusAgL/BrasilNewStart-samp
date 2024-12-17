#define         COLOR_HELPER             0x00F17FAA
#define         C_HELPER                 "{00F17F}"
#define         C_HELPERD                "{00B861}"

// ---------------------------------------
// Helpers
enum ENUM_HELPER
{
    helperNivel,
};
static HelperInfo[MAX_PLAYERS][ENUM_HELPER]; 

stock Helper_GetNivel(playerid)
    return HelperInfo[playerid][helperNivel];

stock Helper_SetNivel(playerid, nivel) 
{
    HelperInfo[playerid][helperNivel] = nivel;

    if (nivel < 1)
        SetCountHelper(CountHelper() - 1);
    else
        SetCountHelper(CountHelper() + 1);
}

// ---------------------------------------
// Avaliar Helper

static  assessHelper[MAX_PLAYERS],
        assessHelper_Timer[MAX_PLAYERS];

stock AssessHelper_Get(playerid)
    return assessHelper[playerid];

stock AssessHelper_Set(playerid, idplayer)
    assessHelper[playerid] = idplayer;

stock AssessHelper_GetTimer(playerid)
    return assessHelper_Timer[playerid];

stock AssessHelper_SetTimer(playerid, timer)
    assessHelper_Timer[playerid] = timer;

// ---------------------------------------
// Contar helpers
static countHelper;

stock SetCountHelper(value)
    countHelper = value;

stock CountHelper()
    return countHelper;