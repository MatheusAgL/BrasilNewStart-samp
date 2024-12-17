// ----------------------------------------------------------------------------------------------------
// Sistema de casas

#define 		MAX_HOUSES 						1000       	// Máximo de casas
#define         MAX_HOUSES_DESCRIPTION          27
#define 		MAX_PLAYER_HOUSES   	        3           // Máximo de casas (por player)
#define			MAX_HOUSE_DESIGNER				10			// Máximo de casa por designer

#define         INVALID_HOUSE_ID        		-1			// Valor inválido de casa

#define			VALUE_TYPE_MONEY				0
#define			VALUE_TYPE_CASH					1

#define         HOUSE_IMPOSTOS          		2500        // Impostos por casa (1 minuto)
#define			HOUSE_DAYS_EXPENSES				30
#define         HOUSE_STATUS_OPEN				0
#define         HOUSE_STATUS_ADMIN              1

enum ENUM_HOUSE
{
	hID,
	Text3D:hLabel,
	hEntryPickup,
	hExitPickup,
	hOwner,
	hOwnerName[MAX_PLAYER_NAME],
	Float:hEntryX,
	Float:hEntryY,
	Float:hEntryZ,
	Float:hExitX,
	Float:hExitY,
	Float:hExitZ,
	Float:hEntryRot,
	hNivel,
	hValueType,
	hValue,
	hInterior,
	hWorld,
	bool:hLock,
	hStatus,
	hExpenses,
	hDesigner,
	hDesignerName[MAX_PLAYER_NAME],
	hTenant,
	hTenantName[MAX_PLAYER_NAME],
	hRentalValue,
	Timestamp:hMaturity,
	hMaxFurniture,
};
static HouseInfo[MAX_HOUSES][ENUM_HOUSE];
static PlayerInHouse[MAX_PLAYERS] = -1;
// new Text3D:textCooking[MAX_PLAYERS];

new Iterator:Houses<MAX_HOUSES>;

new selectHouse[MAX_PLAYERS][MAX_HOUSES];

// Houses:
stock House_SetID(house, id)
	HouseInfo[house][hID] = id;

stock House_GetID(house, id)
	return HouseInfo[house][hID];

stock Player_GetInHouse(playerid)
	return PlayerInHouse[playerid];

stock Player_SetInHouse(playerid, casaid)
	PlayerInHouse[playerid] = casaid;

stock House_GetOwnerName(house)
{
	new name[MAX_PLAYER_NAME];
	format(name, sizeof(name), HouseInfo[house][hOwnerName]);
	return name;
}

stock House_GetOwner(house)
	return HouseInfo[house][hOwner];

stock House_SetOwner(house, owner, const name[])
{
	format(HouseInfo[house][hOwnerName], MAX_PLAYER_NAME, name);
	HouseInfo[house][hOwner] = owner;

	new idplayer = GetPlayerID(name);
	if (Player_Logado(idplayer)) House_ReloadOwner(idplayer);
}

stock House_GetDesignerName(house)
{
	new name[MAX_PLAYER_NAME];
	format(name, sizeof(name), HouseInfo[house][hDesignerName]);
	return name;
}

stock House_GetDesigner(house)
	return HouseInfo[house][hDesigner];

stock House_SetDesigner(house, designer, const name[])
{
	format(HouseInfo[house][hDesignerName], MAX_PLAYER_NAME, name);
	HouseInfo[house][hDesigner] = designer;
	
	new idplayer = GetPlayerID(name);
	if (Player_Logado(idplayer)) House_ReloadDesigner(idplayer);
}

stock House_GetTenantName(house)
{
	new name[MAX_PLAYER_NAME];
	format(name, sizeof(name), HouseInfo[house][hTenantName]);
	return name;
}

stock House_GetTenant(house)
	return HouseInfo[house][hTenant];

stock House_SetTenant(house, tenant, const name[])
{
	format(HouseInfo[house][hTenantName], MAX_PLAYER_NAME, name);
	HouseInfo[house][hTenant] = tenant;

	new idplayer = GetPlayerID(name);
	if (Player_Logado(idplayer)) House_ReloadTenant(idplayer);
}

stock House_GetMaturityDays(house) {
	new days = TimestampToRemainingDays(HouseInfo[house][hMaturity]);
	return days;
}

stock Timestamp:House_GetMaturity(house)
	return HouseInfo[house][hMaturity];

stock House_SetMaturity(house, const maturity[]) {
	TimeParse(maturity, MYSQL_TIMESTAMP, HouseInfo[house][hMaturity]);
}

stock House_AddMaturity(house, Timestamp:maturity) {
	HouseInfo[house][hMaturity] = maturity;
}

stock House_GetDueDate(house)
{
	new days = TimestampToRemainingDays(HouseInfo[house][hVencimento]);
	return days;
}

stock House_SetEntryX(house, Float:entry_x)
	HouseInfo[house][hEntryX] = entry_x;

stock Float:House_GetEntryX(house)
	return HouseInfo[house][hEntryX];

stock House_SetEntryY(house, Float:entry_y)
	HouseInfo[house][hEntryY] = entry_y;

stock Float:House_GetEntryY(house)
	return HouseInfo[house][hEntryY];

stock House_SetEntryZ(house, Float:entry_z)
	HouseInfo[house][hEntryZ] = entry_z;

stock Float:House_GetEntryZ(house)
	return HouseInfo[house][hEntryZ];

stock House_SetExitX(house, Float:exit_x)
	HouseInfo[house][hExitX] = exit_x;

stock Float:House_GetExitX(house)
	return HouseInfo[house][hExitX];

stock House_SetExitY(house, Float:exit_y)
	HouseInfo[house][hExitY] = exit_y;

stock Float:House_GetExitY(house)
	return HouseInfo[house][hExitY];

stock House_SetExitZ(house, Float:exit_z)
	HouseInfo[house][hExitZ] = exit_z;

stock Float:House_GetExitZ(house)
	return HouseInfo[house][hExitZ];

stock Float:House_GetEntryRot(house)
	return HouseInfo[house][hEntryRot];

stock House_SetEntryRot(house, Float:entry_rot)
	HouseInfo[house][hEntryRot] = entry_rot;

stock bool:House_GetLock(house)
	return HouseInfo[house][hLock];

stock House_SetLock(house, bool:stats)
	HouseInfo[house][hLock] = stats;

stock House_GetInterior(house)
	return HouseInfo[house][hInterior];

stock House_SetInterior(house, interior)
	HouseInfo[house][hInterior] = interior;

stock House_GetWorld(house)
	return HouseInfo[house][hWorld];

stock House_SetWorld(house, world)
	HouseInfo[house][hWorld] = world;

stock House_GetValueType(house)
	return HouseInfo[house][hValueType];

stock House_SetValueType(house, type_value)
	HouseInfo[house][hValueType] = type_value;

stock House_GetValue(house)
	return HouseInfo[house][hValue];

stock House_SetValue(house, value)
	HouseInfo[house][hValue] = value;

stock House_GetNivel(house)
	return HouseInfo[house][hNivel];

stock House_SetNivel(house, level)
	HouseInfo[house][hNivel] = level;

stock House_GetStatus(house)
	return HouseInfo[house][hStatus];

stock House_SetStatus(house, status)
	HouseInfo[house][hStatus] = status;

stock House_GetExpenses(house)
	return HouseInfo[house][hExpenses];

stock House_SetExpenses(house, expenses)
	HouseInfo[house][hExpenses] = expenses;

stock House_GetRentalValue(house)
	return HouseInfo[house][hRentalValue];

stock House_SetRentalValue(house, rental_value)
	HouseInfo[house][hRentalValue] = rental_value;

stock House_GetMaxFurniture(house)
	return HouseInfo[house][hMaxFurniture];

stock House_SetMaxFurniture(house, max_furniture)
	HouseInfo[house][hMaxFurniture] = max_furniture;

stock House_CreatePickup(house, pickup)
{
	DestroyDynamicPickup(HouseInfo[house][hEntryPickup]);
	DestroyDynamicPickup(HouseInfo[house][hExitPickup]);

	HouseInfo[house][hExitPickup] = 
		CreateDynamicPickup(1318, 23, House_GetExitX(house), House_GetExitY(house), House_GetExitZ(house), House_GetWorld(house));

	HouseInfo[house][hEntryPickup] = 
		CreateDynamicPickup(pickup, 23, House_GetEntryX(house), House_GetEntryY(house), House_GetEntryZ(house));
}

stock House_UpdatePickup(house, pickup)
{
	DestroyDynamicPickup(HouseInfo[house][hEntryPickup]);
	HouseInfo[house][hEntryPickup] = CreateDynamicPickup(pickup, 23, House_GetEntryX(house), House_GetEntryY(house), House_GetEntryZ(house));
}

stock House_CreateLabel(house, const text[])
{
	DestroyDynamic3DTextLabel(HouseInfo[house][hLabel]);

	HouseInfo[house][hLabel] = 
		CreateDynamic3DTextLabel(text, COLOR_WHITE, House_GetEntryX(house), House_GetEntryY(house), House_GetEntryZ(house) + 0.5, 10.0);
}

stock House_UpdateLabel(house, const text[]) {
	UpdateDynamic3DTextLabelText(HouseInfo[house][hLabel], COLOR_WHITE, text);
}