#if defined _inc_discord_connector
	#endinput
#endif
#define _inc_discord_connector true

#define DCMD_PREFIX '$'             // If you don't define, by default it is '!'
#define DCMD_STRICT_CASE            // Defining this will make commands case-sensitive. !test and !TEST will become different
#define DCMD_ALLOW_BOTS             // Defining this will not ignore commands sent on channel by bots.

#define COLOR_DISCORD		0x5D6AF2AA
#define C_DISCORD			"5D6AF2"

new
    DCC_Channel:Channel_BatePapo,
    DCC_Channel:Channel_SocioLogs,
    DCC_Channel:Channel_Comandos,
    DCC_Channel:Channel_Conexao,
    DCC_Channel:Channel_Attendance,
    DCC_Channel:Channel_AdminAviso;

new
    DCC_Embed:Embed_Online,
    DCC_Embed:Embed_InfoPlayer,
    DCC_Message:Message_EmbedOnline;

// ------------- Sistema de média de jogador durante o tempo que o servidor estiver online.
enum ENUM_PLAYER_AVERAGE {
    playerAverage,
    playerAverageTotal,
    playerAverageMinute,
};
static DailyInfo[ENUM_PLAYER_AVERAGE];

stock Daily_SetPlayerAverage(value) {
    DailyInfo[playerAverage] += value;
    DailyInfo[playerAverageMinute] ++;

    if (DailyInfo[playerAverage] != 0 && DailyInfo[playerAverageMinute] != 0)
        DailyInfo[playerAverageTotal] = (DailyInfo[playerAverage] / DailyInfo[playerAverageMinute]);
}

stock Daily_GetPlayerAverage() {
    return DailyInfo[playerAverageTotal];
}