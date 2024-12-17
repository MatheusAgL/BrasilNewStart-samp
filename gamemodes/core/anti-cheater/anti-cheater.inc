
// --------------------------------------------------------
// Configurações do Anti-cheater;

CALLBACK: OnCheatDetected(playerid, const ip_address[], type, code) {

	new string[128],
		name_cheater[46];

	switch (code) {
		case 0: name_cheater = "Anti-AirBreak (onfoot)";
		case 1: name_cheater = "Anti-AirBreak (in vehicle)";
		case 2: name_cheater = "Anti-teleport hack (onfoot)";
		case 3: name_cheater = "Anti-teleport hack (in vehicle)";
		case 4: name_cheater = "Anti-teleport hack (into/between vehicles)";
		case 5: name_cheater = "Anti-teleport hack (vehicle to player)";
		case 6: name_cheater = "Anti-teleport hack (pickups)";
		case 7: name_cheater = "Anti-FlyHack (onfoot)";
		case 8: name_cheater = "Anti-FlyHack (in vehicle)";
		case 9: name_cheater = "Anti-SpeedHack (onfoot)";
		case 10: name_cheater = "Anti-SpeedHack (in vehicle)";
		case 11: name_cheater = "Anti-Health hack (in vehicle)";
		case 12: name_cheater = "Anti-Health hack (onfoot)";
		case 13: name_cheater = "Anti-Armour hack";
		case 14: name_cheater = "Anti-Money hack";
		case 15: name_cheater = "Anti-Weapon hack";
		case 16: name_cheater = "Anti-Ammo hack (add)";
		case 17: name_cheater = "Anti-Ammo hack (infinite)";
		case 18: name_cheater = "Anti-Special actions hack";
		case 19: name_cheater = "Anti-GodMode from bullets (onfoot)";
		case 20: name_cheater = "Anti-GodMode from bullets (in vehicle)";
		case 21: name_cheater = "Anti-Invisible hack";
		case 22: name_cheater = "Anti-lagcomp-spoof";
		case 23: name_cheater = "Anti-Tuning hack";
		case 24: name_cheater = "Anti-Parkour mod";
		case 25: name_cheater = "Anti-Quick turn";
		case 26: name_cheater = "Anti-Rapid fire";
		case 27: name_cheater = "Anti-FakeSpawn";
		case 28: name_cheater = "Anti-FakeKill";
		case 29: name_cheater = "Anti-Pro Aim";
		case 30: name_cheater = "Anti-CJ run";
		case 31: name_cheater = "Anti-CarShot";
		case 32: name_cheater = "Anti-CarJack";
		case 33: name_cheater = "Anti-UnFreeze";
		case 34: name_cheater = "Anti-AFK Ghost";
		case 35: name_cheater = "Anti-Full Aiming";
		case 36: name_cheater = "Anti-Fake NPC";
		case 37: name_cheater = "Anti-Reconnect";
		case 38: name_cheater = "Anti-High ping";
		case 39: name_cheater = "Anti-Dialog hack";
		case 40: name_cheater = "Protection from sandbox";
		case 41: name_cheater = "Protection from invalid version";
		case 42: name_cheater = "Anti-Rcon hack";
		case 43: name_cheater = "Anti-Tuning crasher";
		case 44: name_cheater = "Anti-Invalid seat crasher";
		case 45: name_cheater = "Anti-Dialog crasher";
		case 46: name_cheater = "Anti-Attached object crasher";
		case 47: name_cheater = "Anti-Weapon Crasher";
		case 48: name_cheater = "Protection from connection flood in one slot";
		case 49: name_cheater = "Anti-callback functions flood";
		case 50: name_cheater = "Anti-flood by seat changing";
		case 51: name_cheater = "Anti-DoS";
		case 52: name_cheater = "Anti-NOPs";
	}

	format(string, sizeof(string), "[Nex-AC BNS]: %s[%d] (IP: %s) é suspeita de: %s", PlayerName[playerid], playerid, PlayerIP[playerid], name_cheater);
	printf(string);

	switch (code) {
		case 0, 1, 35, 47: 
		{
			new 
				timer = GetPVarInt(playerid, #varFlood_CRASH),
				warns = GetPVarInt(playerid, #varFlood_CRASH_warns);

			if (gettime() > timer)
			{
				SetPVarInt(playerid, #varFlood_CRASH_warns, 1);
				SetPVarInt(playerid, #varFlood_CRASH, gettime() + 10);
			} else {
				SetPVarInt(playerid, #varFlood_CRASH_warns, warns + 1);

				if (warns + 1 == 8) {
					SendClientMessage(playerid, COLOR_LIGHTRED, "ANTI-CHEATER: Você foi kickado por provavelmente estar de RT.");
					KickEx(playerid);

					format(string, sizeof(string), "[Nex-AC BNS]: %s[%d] foi kickado por %s", PlayerName[playerid], playerid, name_cheater);
					printf(string);
				}
			}
		}
	}

	if (type != 1) {
		if (gettime() > GetPVarInt(playerid, #varFlood_AC)) {
			if ((Admin_GetNivel(playerid) && Staff_GetWorking(playerid)) || Admin_GetNivel(playerid) > MASTER)
				return 1;

			format(string, sizeof(string), "ANTI-CHEATER: %s[%d] é suspeita de: %s", PlayerName[playerid], playerid, name_cheater);
			SetPVarInt(playerid, #varFlood_AC, gettime() + 8);
			Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
		}
	}
	return 1;
}