#include <YSI_Coding\y_hooks>

hook OnPlayerLogin(playerid) {
	switch (Player_GetStruggle(playerid)) {
		case 1: SetPlayerFightingStyle(playerid, FIGHT_STYLE_ELBOW);
		case 2: SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);
		case 3: SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK);
		case 4: SetPlayerFightingStyle(playerid, FIGHT_STYLE_KNEEHEAD);
		case 5: SetPlayerFightingStyle(playerid, FIGHT_STYLE_KUNGFU);
		case 6: SetPlayerFightingStyle(playerid, FIGHT_STYLE_NORMAL);
	}
}
