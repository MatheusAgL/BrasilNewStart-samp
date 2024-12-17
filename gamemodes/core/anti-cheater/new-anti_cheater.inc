#define MAX_WEAPON_SLOT			13

enum ENUM_WEAPONS
{
	weaponId,
	weaponAmmo,
};
new WeaponInfo[MAX_PLAYERS][MAX_WEAPON_SLOT][ENUM_WEAPONS];

stock Weapon_GetSlot(weapon_model)
{
    new weapon_slot;

    switch (weapon_model)
    {
        case WEAPON_BRASSKNUCKLE:       
            weapon_slot = 0;
        case WEAPON_GOLFCLUB, WEAPON_NITESTICK, WEAPON_KNIFE, WEAPON_BAT, WEAPON_SHOVEL, WEAPON_POOLSTICK, WEAPON_KATANA, WEAPON_CHAINSAW:
            weapon_slot = 1;
        case WEAPON_DILDO, WEAPON_DILDO2, WEAPON_VIBRATOR, WEAPON_VIBRATOR2, WEAPON_FLOWER, WEAPON_CANE:
            weapon_slot = 10;
        case WEAPON_GRENADE, WEAPON_TEARGAS, WEAPON_MOLTOV:
            weapon_slot = 8;
        case WEAPON_COLT45, WEAPON_SILENCED, WEAPON_DEAGLE:             
            weapon_slot = 2; // Shot
        case WEAPON_SHOTGUN, WEAPON_SAWEDOFF, WEAPON_SHOTGSPA:            
            weapon_slot = 3; // Shot
        case WEAPON_UZI, WEAPON_MP5, WEAPON_TEC9:
            weapon_slot = 4; // Shot
        case WEAPON_AK47, WEAPON_M4:
            weapon_slot = 5; // Shot
        case WEAPON_RIFLE, WEAPON_SNIPER:
            weapon_slot = 6; // Shot
        case WEAPON_ROCKETLAUNCHER, WEAPON_HEATSEEKER, WEAPON_FLAMETHROWER, WEAPON_MINIGUN:
            weapon_slot = 7; // Shot
        case WEAPON_SATCHEL:
            weapon_slot = 8;
        case WEAPON_BOMB:
            weapon_slot = 12;
        case WEAPON_SPRAYCAN, WEAPON_FIREEXTINGUISHER, WEAPON_CAMERA:
            weapon_slot = 9;
        case 44, 45, WEAPON_PARACHUTE:
            weapon_slot = 11;
    }
    return weapon_slot;
}

stock Weapon_Get(playerid, slot)
	return WeaponInfo[playerid][slot][weaponId];

stock Weapon_Set(playerid, slot, weaponid)
	WeaponInfo[playerid][slot][weaponId] = weaponid;

stock Weapon_GetAmmo(playerid, slot)
	return WeaponInfo[playerid][slot][weaponAmmo];

stock Weapon_SetAmmo(playerid, slot, ammo)
	WeaponInfo[playerid][slot][weaponAmmo] = ammo;

stock PlayerWeapon_Set(playerid, slot, weaponid, ammo) {
    Weapon_Set(playerid, slot, weaponid);
    Weapon_SetAmmo(playerid, slot, ammo);
	Weapons_Update(playerid);
}

stock Weapon_GetSlotUsed(playerid, slot) {
	if (WeaponInfo[playerid][slot][weaponId] != 0) return true;
	return false;
}

stock Weapons_Update(playerid) {
	ResetPlayerWeapons(playerid);
	for (new slot; slot < MAX_WEAPON_SLOT; slot++) GivePlayerWeapon(playerid, WeaponInfo[playerid][slot][weaponId], WeaponInfo[playerid][slot][weaponAmmo]);
}

stock Weapons_Reset(playerid) {
    for (new slot = 1; slot < MAX_WEAPON_SLOT; slot++) {
        WeaponInfo[playerid][slot][weaponId] = 0;
        WeaponInfo[playerid][slot][weaponAmmo] = 0;
    }
    ResetPlayerWeapons(playerid);
    return 1;
}

hook OnPlayerUpdate(playerid)
{
    if (GetPlayerWeapon(playerid) == WEAPON_BOMB) {
        if (GetPlayerCameraMode(playerid) == 45) {
            printf("ANTI-CHEATER: %s [ID: %d] foi kickado por: Denotador Crasher. %d/100", PlayerName[playerid], playerid, ContarJogadores());
            // Kick(playerid); 
            return 0;
        }
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    Weapons_Reset(playerid);
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    Weapons_Reset(playerid);
    return 1;
}

ptask OnPlayerCheckWeapons[1000](playerid)
{
	new weapon[MAX_WEAPON_SLOT],
		ammo[MAX_WEAPON_SLOT],
        string[128],
        weapon_name[20],
        warns = GetPVarInt(playerid, #varFlood_WeaponHack);

	for (new slot = 1; slot < MAX_WEAPON_SLOT; slot++) {
		GetPlayerWeaponData(playerid, slot, weapon[slot], ammo[slot]);
		
		if (weapon[slot] != 0 &&
            (weapon[slot] != WeaponInfo[playerid][slot][weaponId])) {

            GetWeaponName(weapon[slot], weapon_name);
			Weapons_Update(playerid);

            printf("ANTI-CHEATER: %s tentou pegar uma %s com %d de munição com Weapon-Hack.", PlayerName[playerid], weapon_name, ammo[slot]);

            SetPVarInt(playerid, #varFlood_WeaponHack, warns + 1);
            if (warns + 1 == 8) {
                format(string, sizeof(string), "ANTI-CHEATER: %s tentou pegar uma %s com %d de munição com Weapon-Hack.", PlayerName[playerid], weapon_name, ammo[slot]);
                Staff_ChatToAll(COLOR_LIGHTRED, string);
            }
        }
	}		
}