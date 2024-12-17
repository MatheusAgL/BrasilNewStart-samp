#define     MAX_STORE_ITENS             56
#define     MAX_STORE_SLOT_PERPAGE      10
#define     MAX_PAGES_STORE             7

enum ENUM_STORE
{
    storeID,
    storeSeller,
    storeTypePrice,
    storePrice,
    storeItemName[40],
    storeItemType,
    storeItemModel,
    storeItemQuantity,
    storeItemColor1,
    storeItemColor2,
    Timestamp:storeItemMaturity,
};
static StoreInfo[MAX_STORE_ITENS][ENUM_STORE];

static storeSlotSelected[MAX_PLAYERS];

stock Store_SetSelected(playerid, selected_id)
    storeSlotSelected[playerid] = selected_id;

stock Store_GetSelected(playerid)
    return storeSlotSelected[playerid];

// ------------------------------

stock StoreItem_SetID(item, id)
    StoreInfo[item][storeID] = id;

stock StoreItem_GetID(item)
    return StoreInfo[item][storeID];

stock StoreItem_GetSeller(item)
    return StoreInfo[item][storeSeller];

stock StoreItem_SetSeller(item, seller)
    StoreInfo[item][storeSeller] = seller;

stock StoreItem_SetTypePrice(item, type_price)
    StoreInfo[item][storeTypePrice] = type_price;

stock StoreItem_GetTypePrice(item)
    return StoreInfo[item][storeTypePrice];

stock StoreItem_SetPrice(item, price)
    StoreInfo[item][storePrice] = price;

stock StoreItem_GetPrice(item)
    return StoreInfo[item][storePrice];

stock StoreItem_SetName(item, const name[])
    format(StoreInfo[item][storeItemName], MAX_PLAYER_NAME, name);

stock StoreItem_GetName(item) {
    new name[MAX_PLAYER_NAME];
    format(name, sizeof(name), StoreInfo[item][storeItemName]);
    return name;
}

stock StoreItem_SetType(item, type)
    StoreInfo[item][storeItemType] = type;

stock StoreItem_GetType(item)
    return StoreInfo[item][storeItemType];

stock StoreItem_SetModel(item, model)
    StoreInfo[item][storeItemModel] = model;

stock StoreItem_GetModel(item)
    return StoreInfo[item][storeItemModel];

stock StoreItem_SetQuantity(item, quantity)
    StoreInfo[item][storeItemQuantity] = quantity;

stock StoreItem_GetQuantity(item)
    return StoreInfo[item][storeItemQuantity];

stock StoreItem_SetColor1(item, color1)
    StoreInfo[item][storeItemColor1] = color1;

stock StoreItem_GetColor1(item)
    return StoreInfo[item][storeItemColor1];

stock StoreItem_SetColor2(item, color2)
    StoreInfo[item][storeItemColor2] = color2;

stock StoreItem_GetColor2(item)
    return StoreInfo[item][storeItemColor2];

stock Timestamp:StoreItem_GetMaturity(item)
	return StoreInfo[item][storeItemMaturity];

stock StoreItem_SetMaturity(item, const maturity[]) {
	TimeParse(maturity, MYSQL_TIMESTAMP, StoreInfo[item][storeItemMaturity]);
}

stock StoreItem_GetMaturityDays(item) {
	new days = TimestampToRemainingDays(StoreInfo[item][storeItemMaturity]);
	return days;
}

stock StoreItem_AddMaturity(item, Timestamp:maturity) {
	StoreInfo[item][storeItemMaturity] = maturity;
}