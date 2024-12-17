enum ENUM_CONSUMABLE {
    foodActive,
};
new ConsumableInfo[MAX_PLAYERS][ENUM_CONSUMABLE];

stock Consumable_GetActive(playerid)
    return ConsumableInfo[playerid][foodActive];

stock Consumable_SetActive(playerid, value)
    ConsumableInfo[playerid][foodActive] = value;