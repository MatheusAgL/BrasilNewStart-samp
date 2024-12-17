#define     INVALID_PAINTBALL_ID        -1
#define     MAX_PAINTBALLS              20
#define     COLOR_PAINTBALL             0x51A250FF
#define     C_PAINTBALL                 "{51A250}"

new Float:PaintballSpawn[15][4] = 
{
    {-973.9935,1061.0387,1345.6748,0.000},
    {-974.0367,1077.0967,1344.9905,0.000},
    {-976.4233,1089.6028,1344.9663,0.000},
    {-996.2937,1096.7981,1342.6528,0.000},
    {-997.5055,1068.0223,1342.5001,0.000},
    {-983.3688,1053.0817,1344.0533,0.000},
    {-995.9034,1021.7935,1341.8438,0.000},
    {-1018.9267,1025.3103,1344.2072,0.000},
    {-1020.4349,1042.5686,1342.0276,0.000},
    {-1035.0374,1043.6566,1341.9498,0.000},
    {-1032.1669,1060.9025,1344.1122,0.000},
    {-1033.3435,1086.6536,1342.8842,0.000},
    {-1026.5459,1097.8673,1342.7157,0.000},
    {-1044.4702,1093.7522,1346.4680,0.000},
    {-1055.0779,1096.3853,1343.0734,0.000}
};

stock GetRankedLevel(playerid)
{
    new InfoMetodoDonate[25];

	switch (Player_GetArenaKills(playerid))
	{
		case 0..20: 			InfoMetodoDonate = "{8D6932}BRONZE";
		case 21..50: 			InfoMetodoDonate = "{D9D9D8}PRATA";
		case 51..100: 			InfoMetodoDonate = "{F3DE3E}OURO";
		case 101..200: 			InfoMetodoDonate = "{95D5F3}PLATINA";
		case 201..350: 			InfoMetodoDonate = "{16EBF7}DIAMANTE";
		case 351..500: 			InfoMetodoDonate = "{FA0202}MESTRE";
		default: 				InfoMetodoDonate = "{FCF870}CHALLENGER";
	}
	return InfoMetodoDonate;
}

enum ENUM_PAINTBALL {
    pbID,
    pbOwner,
    pbName[34],
    pbDescription[64],
    bool:pbLock,
    pbWorld,
    pbRoundTime,
    bool:pbX1,
    WEAPON:pbWeapons[13],
};
static PaintballInfo[MAX_PAINTBALLS][ENUM_PAINTBALL];

stock Paintball_SetID(paintballid, id)
    PaintballInfo[paintballid][pbID] = id;

stock Paintball_GetID(paintballid)
    return PaintballInfo[paintballid][pbID];

stock Paintball_SetName(paintballid, const name[])
    format(PaintballInfo[paintballid][pbName], 34, "%s", name);

stock Paintball_GetName(paintballid) {
    new name[34];
    format(name, sizeof(name), PaintballInfo[paintballid][pbName]);
    return name;
}

stock Paintball_SetOwner(pbid, idplayer)
    PaintballInfo[pbid][pbOwner] = idplayer;

stock Paintball_GetOwner(pbid)
    return PaintballInfo[pbid][pbOwner];

stock Paintball_SetDescription(paintballid, const description[])
    format(PaintballInfo[paintballid][pbDescription], 64, "%s", description);

stock Paintball_GetDescription(paintballid, description[]) {
    new description[64];
    format(description, sizeof(description), PaintballInfo[paintballid][pbDescription]);
    return description;
}

stock Paintball_SetLock(paintballid, bool:lock)
    PaintballInfo[paintballid][pbLock] = lock;

stock bool:Paintball_GetLock(paintballid)
    return PaintballInfo[paintballid][pbLock];

stock Paintball_SetWorld(paintballid, world)
    PaintballInfo[paintballid][pbWorld] = world;

stock Paintball_GetWorld(paintballid)
    return PaintballInfo[paintballid][pbWorld];

stock Paintball_SetRoundTime(paintballid, roundtime)
    PaintballInfo[paintballid][pbRoundTime] = roundtime;

stock Paintball_GetRoundTime(paintballid)
    return PaintballInfo[paintballid][pbRoundTime];

stock Paintball_SetX1(paintballid, bool:x1)
    PaintballInfo[paintballid][pbX1] = x1;

stock Paintball_GetX1(paintballid)
    return PaintballInfo[paintballid][pbX1];

stock Paintball_SetWeapon(paintballid, index, const string_weapon[]) {
    new weapon = strval(string_weapon);
    if (index >= 0 && index <= 13)
        PaintballInfo[paintballid][pbWeapons][index] = weapon;
}

stock Paintball_GetWeapon(paintballid, index) {
    if (index >= 0 && index <= 13)
        return PaintballInfo[paintballid][pbWeapons][index];
    
    return -1;
}

enum ENUM_PLAYER_PAINTBALL {
    paintballId,
    Text3D:pbPingText,
    Float:pbHealthEntry,
    Float:pbArmourEntry,
    WEAPON:pbWeaponEntry[13],
    pbAmmoEntry[13],
    combo_Timer,
	combo_Kills,
    pbOpponent,
};
static PlayerPaintball[MAX_PLAYERS][ENUM_PLAYER_PAINTBALL];

// -----------------------------
// Paintball ID

stock Player_SetPaintball(playerid, paintballid)
    PlayerPaintball[playerid][paintballId] = paintballid;

stock Player_GetPaintball(playerid)
    return PlayerPaintball[playerid][paintballId];

stock PlayerPaintball_SetPingText(playerid, Text3D:text)
    PlayerPaintball[playerid][pbPingText] = text;

stock PlayerPaintball_GetPingText(playerid)
    return PlayerPaintball[playerid][pbPingText];

stock PlayerPaintball_SetHealthEntry(playerid, Float:health)
    PlayerPaintball[playerid][pbHealthEntry] = health;

stock Float: PlayerPaintball_GetHealthEntry(playerid)
    return PlayerPaintball[playerid][pbHealthEntry];

stock PlayerPaintball_SetArmourEntry(playerid, Float:armour)
    PlayerPaintball[playerid][pbArmourEntry] = armour;

stock Float: PlayerPaintball_GetArmourEntry(playerid)
    return PlayerPaintball[playerid][pbArmourEntry];

stock PlayerPaintball_SetWeaponEntry(playerid, index, weapon) {
    if (index >= 0 && index < sizeof(PlayerPaintball[playerid][pbWeaponEntry]))
        PlayerPaintball[playerid][pbWeaponEntry][index] = weapon;
}

stock PlayerPaintball_GetWeaponEntry(playerid, index) {
    if (index >= 0 && index < sizeof(PlayerPaintball[playerid][pbWeaponEntry]))
        return PlayerPaintball[playerid][pbWeaponEntry][index];
    
    return -1;
}

stock PlayerPaintball_SetAmmoEntry(playerid, index, ammo) {
    if (index >= 0 && index < sizeof(PlayerPaintball[playerid][pbAmmoEntry]))
        PlayerPaintball[playerid][pbAmmoEntry][index] = ammo;
}

stock PlayerPaintball_GetAmmoEntry(playerid, index) {
    if (index >= 0 && index < sizeof(PlayerPaintball[playerid][pbAmmoEntry]))
        return PlayerPaintball[playerid][pbAmmoEntry][index];
    
    return -1;
}

stock PlayerPaintball_SetComboTimer(playerid, timer)
    PlayerPaintball[playerid][combo_Timer] = timer;

stock PlayerPaintball_GetComboTimer(playerid)
    return PlayerPaintball[playerid][combo_Timer];

stock PlayerPaintball_SetComboKills(playerid, kills)
    PlayerPaintball[playerid][combo_Kills] = kills;

stock PlayerPaintball_GetComboKills(playerid)
    return PlayerPaintball[playerid][combo_Kills];

stock PlayerPaintball_ResetCombo(playerid) {
	PlayerPaintball_SetComboTimer(playerid, 0);
	PlayerPaintball_SetComboKills(playerid, 0);
}

// X1
stock PlayerPaintball_SetOpponent(playerid, opponent)
    PlayerPaintball[playerid][pbOpponent] = opponent;

stock PlayerPaintball_GetOpponent(playerid)
    return PlayerPaintball[playerid][pbOpponent];

stock Paintball_SaveEntry(playerid)
{
    for(new w; w < 13; w++)
        GetPlayerWeaponData(playerid, w, PlayerPaintball[playerid][pbWeaponEntry][w], PlayerPaintball[playerid][pbAmmoEntry][w]);
    
    GetPlayerHealth(playerid, PlayerPaintball[playerid][pbHealthEntry]);
    GetPlayerArmour(playerid, PlayerPaintball[playerid][pbArmourEntry]);
}

stock Paintball_LoadEntry(playerid)
{
	for(new w; w < 13; w++)
        GivePlayerWeapon(playerid, PlayerPaintball[playerid][pbWeaponEntry][w], PlayerPaintball[playerid][pbAmmoEntry][w]);
	
	SetPlayerHealth(playerid, PlayerPaintball[playerid][pbHealthEntry]);
	SetPlayerArmour(playerid, PlayerPaintball[playerid][pbArmourEntry]);
}

stock Player_GetPing(playerid) 
{
    if (PlayerPaintball[playerid][pbPingText] != Text3D:-1) {
        static string[37];
        format(string, sizeof(string), "PING: %s", getPingText(playerid));
        UpdateDynamic3DTextLabelText(PlayerPaintball[playerid][pbPingText], COLOR_PAINTBALL, string);
    }
}

stock Paintball_CreateTextLabel(playerid)
{
    if (PlayerPaintball[playerid][pbPingText] != Text3D:-1)
		PlayerPaintball[playerid][pbPingText] = CreateDynamic3DTextLabel("-", -1, 0.0, 0.0, -0.7, 30.0, playerid);
}

stock Paintball_DestroyTextLabel(playerid)
{
    if (PlayerPaintball[playerid][pbPingText] != Text3D:-1) {
		DestroyDynamic3DTextLabel(PlayerPaintball[playerid][pbPingText]);
		PlayerPaintball[playerid][pbPingText] = Text3D:-1;
	}
}