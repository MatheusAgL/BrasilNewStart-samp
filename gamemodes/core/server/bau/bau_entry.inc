#if defined _LOOT_SYSTEM_ON
	#endinput
#endif
#define _LOOT_SYSTEM_ON true

#define MAX_LOOT_NAME				36
#define MAX_LOOTS                   500
#define MAX_LOOT_ITENS              80

enum LOOT_SERVER_ENUM
{
	Float: lootX,
	Float: lootY,
	Float: lootZ,
	Float: lootA,
	
	lootID,
	lootOwnerID,
	lootOwner[MAX_PLAYER_NAME],
 	lootName[MAX_LOOT_NAME],
	lootModel,
	lootWorld,
	lootInterior,
	lootMax,

	lootObject,
	Text3D:lootLabel,
};
static lootInfo[MAX_LOOTS][LOOT_SERVER_ENUM];
static lootItensInfo[MAX_LOOTS][MAX_LOOT_ITENS][INVENTORY_ENUM];

new Iterator:IterLoot<MAX_LOOTS>;
new Iterator:IterLootItem[MAX_LOOTS]<MAX_LOOT_ITENS>;

stock Player_MaxLoot(playerid) {
	switch (Player_GetVIP(playerid)) {
		case SOCIO_COMUM, SOCIO_PREMIUM: return 2;
		case SOCIO_SUPREME: return 3;
		case SOCIO_EXTREME: return 4;
	}
	return 1;
}

stock Player_CountLoot(playerid) {
	new count;

	foreach(new loot : IterLoot) {
	    if (Loot_GetOwner(loot) == Player_GetAccountID(playerid))
			count++;
	}
	return count;
}

stock Player_LootCloser(playerid)
{
	new 
		Float:bau_dist = 999999.0,
		bau_id = -1
	;
	
	foreach(new id : IterLoot) {
	    if (GetPlayerInterior(playerid) != lootInfo[id][lootInterior] || GetPlayerVirtualWorld(playerid) != lootInfo[id][lootWorld])
			continue;
	
		new Float:dist = GetPlayerDistanceFromPoint(playerid, lootInfo[id][lootX], lootInfo[id][lootY], lootInfo[id][lootZ]);
		
		if (dist > 1.5000) 
			continue;
		
		if (dist < bau_dist) {
		    bau_dist = dist;
		    bau_id = id;
		}
	}
	return bau_id;
}

stock Loot_GenerateMaxItems(playerid, modelid) 
{
	new value = 40;
	if(modelid == 1271)
		value = 25;
	else if(modelid == 19058)
		value = 50;

	switch (Player_GetVIP(playerid)) {
		case SOCIO_COMUM: value += 15;
		case SOCIO_PREMIUM: value += 25;
		case SOCIO_SUPREME: value += 35;
		case SOCIO_EXTREME: value += 45;
	}

	if (value > MAX_LOOT_ITENS)
		value = MAX_LOOT_ITENS;

	return value;
}

stock Loot_CountItens(id) 
{
	if (Iter_Contains(IterLoot, id)) {
		return Iter_Count(IterLootItem[id]);
	}
	return 0;
}

stock Loot_PlayerEdit(playerid, lootid) {
	EditDynamicObject(playerid, lootInfo[lootid][lootObject]);
}

stock Loot_SetID(lootid, id) {
	lootInfo[lootid][lootID] = id;
}

stock Loot_SetMaxItems(lootid, max) {
	lootInfo[lootid][lootMax] = max;
}

stock Loot_SetModel(lootid, const itemname[], modelid)
{
	lootInfo[lootid][lootModel] = modelid;
        
    format(lootInfo[lootid][lootName], MAX_LOOT_NAME, itemname);
}

stock Loot_SetCheckpoint(playerid, lootid) {
	SetPlayerCheckpoint(playerid, lootInfo[lootid][lootX], lootInfo[lootid][lootY], lootInfo[lootid][lootZ], 3.0);
}

stock Loot_SetPlayer(playerid, lootid) {
	SetPlayerInterior(playerid, Loot_GetInterior(lootid));
	SetPlayerVirtualWorld(playerid, Loot_GetWorld(lootid));
	SetPlayerPos(playerid, lootInfo[lootid][lootX] + 0.3, lootInfo[lootid][lootY], lootInfo[lootid][lootZ] + 0.2);
}

stock Loot_SetPos(lootid, Float:x, Float:y, Float:z, Float:a, world, interior) {
	lootInfo[lootid][lootX]	= x;
	lootInfo[lootid][lootY] = y;
	lootInfo[lootid][lootZ]	= z;
	lootInfo[lootid][lootA]	= a;
	
	lootInfo[lootid][lootWorld]	= world;
	lootInfo[lootid][lootInterior] = interior;
}

stock Loot_GetPos(lootid, &Float:x, &Float:y, &Float:z, &Float:a, &world, &interior) {
	x = lootInfo[lootid][lootX];
	y = lootInfo[lootid][lootY];
	z = lootInfo[lootid][lootZ];
	a = lootInfo[lootid][lootA];
	
	world = lootInfo[lootid][lootWorld];
	interior = lootInfo[lootid][lootInterior];
}

stock Loot_GetID(lootid) {
	return lootInfo[lootid][lootID];
}

stock Loot_GetMaxItems(lootid) {
	return lootInfo[lootid][lootMax];
}

stock Loot_GetModel(lootid) {
	return lootInfo[lootid][lootModel];
}

stock Loot_GetWorld(lootid) {
	return lootInfo[lootid][lootWorld];
}

stock Loot_GetInterior(lootid) {
	return lootInfo[lootid][lootInterior];
}

stock Loot_GetName(lootid) {
	new lootname[MAX_LOOT_NAME];

	format(lootname, sizeof(lootname), lootInfo[lootid][lootName]);
	return lootname;
}

stock Loot_GetOwner(lootid) {
	return lootInfo[lootid][lootOwnerID];
}

stock Loot_GetOwnerName(lootid) {
	new namePlayer[MAX_PLAYER_NAME];

	format(namePlayer, MAX_PLAYER_NAME, lootInfo[lootid][lootOwner]);
	return namePlayer;
}

stock Loot_SetOwnerName(lootid, const name[]) {
	format(lootInfo[lootid][lootOwner], MAX_PLAYER_NAME, name);
}

stock Loot_SetOwner(lootid, gid) {
	lootInfo[lootid][lootOwnerID] = gid;
}

stock Loot_GetObject(loot) {
	return lootInfo[loot][lootObject];
}

stock Loot_DestroyObject(lootid) {
	DestroyDynamicObject(lootInfo[lootid][lootObject]);
}

stock Loot_UpdateObject(lootid) {
	SetDynamicObjectPos(lootInfo[lootid][lootObject], lootInfo[lootid][lootX], lootInfo[lootid][lootY], lootInfo[lootid][lootZ]);
	SetDynamicObjectRot(lootInfo[lootid][lootObject], 0.0, 0.0, lootInfo[lootid][lootA]);
}

stock Loot_CreateObject(lootid) {
	lootInfo[lootid][lootObject] = 
		CreateDynamicObject(lootInfo[lootid][lootModel], lootInfo[lootid][lootX], lootInfo[lootid][lootY], lootInfo[lootid][lootZ], 0.0, 0.0, lootInfo[lootid][lootA], lootInfo[lootid][lootWorld], lootInfo[lootid][lootInterior]);
}

stock Loot_DestroyTextLabel(lootid) {
	DestroyDynamic3DTextLabel(lootInfo[lootid][lootLabel]);
}

stock Loot_CreateTextLabel(lootid) {
	new string[190];

	format(string, sizeof string,
	"{F0EDED}%s [ID: %d]\n\n\
	Proprietário: {9C9C9C}%s\n\
	{F0EDED}Itens: {9C9C9C}%d/%d\n\n\
	{F0EDED}Aperte a tecla {9C9C9C}ALT {F0EDED}para usar", lootInfo[lootid][lootName], lootid, Loot_GetOwnerName(lootid), Loot_CountItens(lootid), lootInfo[lootid][lootMax]);
	
	lootInfo[lootid][lootLabel] = 
		CreateDynamic3DTextLabel(string, 0xFFFFFFAA, lootInfo[lootid][lootX], lootInfo[lootid][lootY], lootInfo[lootid][lootZ], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, lootInfo[lootid][lootWorld], lootInfo[lootid][lootInterior]);
}

stock Loot_UpdateTextLabel(lootid) {

	new string[256];

	format(string, sizeof string,
	"{F0EDED}%s [ID: %d]\n\n\
	Proprietário: {9C9C9C}%s\n\
	{F0EDED}Itens: {9C9C9C}%d/%d\n\n\
	{F0EDED}Aperte a tecla {9C9C9C}ALT {F0EDED}para usar", lootInfo[lootid][lootName], lootid, Loot_GetOwnerName(lootid), Loot_CountItens(lootid), lootInfo[lootid][lootMax]);

	UpdateDynamic3DTextLabelText(lootInfo[lootid][lootLabel], 0xFFFFFFAA, string);
}

stock Loot_SetInventory(playerid, const lootname[], modelid, quant=1) {
	givePlayerItem(playerid, ITEM_TYPE_DEPOSITORY, modelid, quant, lootname);
}

stock Loot_OwnerChangeNick(playerid, const newnick[]) {

	foreach(new loot : IterLoot) {
	    if (Loot_GetOwner(loot) == Player_GetAccountID(playerid)) {
			Loot_SetOwnerName(loot, newnick);
		}
	}
}

stock LootItem_SetValid(loot, item, value) {
	lootItensInfo[loot][item][item_valid] = value;
}

stock LootItem_IsValid(loot, item) {
	return lootItensInfo[loot][item][item_valid];
}

stock LootItem_SetID(loot, item, id) {
	lootItensInfo[loot][item][item_id] = id;
}

stock LootItem_GetID(loot, item) {
	return lootItensInfo[loot][item][item_id];
}

stock LootItem_SetModel(loot, item, modelid) {
	lootItensInfo[loot][item][item_model] = modelid;
}

stock LootItem_GetModel(loot, item) {
	return lootItensInfo[loot][item][item_model];
}

stock LootItem_SetName(loot, item, const name[]) {
	format(lootItensInfo[loot][item][item_nome], 30, name);
}

stock LootItem_GetName(loot, item) {
	new itemname[30];

	format(itemname, sizeof(itemname), lootItensInfo[loot][item][item_nome]);
	return itemname;
}

stock LootItem_SetAmount(loot, item, amount) {
	lootItensInfo[loot][item][item_quantia] = amount;
}

stock LootItem_GetAmount(loot, item) {
	return lootItensInfo[loot][item][item_quantia];
}

stock LootItem_SetType(loot, item, type) {
	lootItensInfo[loot][item][item_type] = type;
}

stock LootItem_GetType(loot, item) {
	return lootItensInfo[loot][item][item_type];
}

stock LootItem_SetCor1(loot, item, color) {
	lootItensInfo[loot][item][item_cor1] = color;
}

stock LootItem_GetCor1(loot, item) {
	return lootItensInfo[loot][item][item_cor1];
}

stock LootItem_SetCor2(loot, item, color) {
	lootItensInfo[loot][item][item_cor2] = color;
}

stock LootItem_GetCor2(loot, item) {
	return lootItensInfo[loot][item][item_cor2];
}