// ---------------------------------------------------------------------------
// Sistema de congelar o jogador;

// Includes
#include <YSI_Coding\y_hooks>

// Variáveis
static Timer:timer_player_congeled[MAX_PLAYERS];

// Funções
timer TimerPlayerCongeled[3000](playerid) {
	TogglePlayerControllable(playerid, true);
}

stock FreezeThePlayer(playerid, tempo=3000) {
    TogglePlayerControllable(playerid, false);
    stop timer_player_congeled[playerid];
	timer_player_congeled[playerid] = defer TimerPlayerCongeled[Timer:tempo](playerid);
}

hook OnPlayerDisconnect(playerid, reason) 
{
    stop timer_player_congeled[playerid];

    return 1;
}