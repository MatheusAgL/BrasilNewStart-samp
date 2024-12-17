#define 		MAX_TRASH					50
#define 		MAX_TRASH_ITENS				50

enum TRASHCAN_ENUM
{
	Float:trashCanPos[4],
	trashCanModel,
	trashCanWorld,
	trashCanInterior,
	trashCanObject,
	trashCanTime[MAX_PLAYERS],
	Text3D:lixeiraLabel,
}
static TrashCanInfo[MAX_TRASH][TRASHCAN_ENUM];
static TrashCanItens[MAX_TRASH][MAX_TRASH_ITENS][INVENTORY_ENUM];

new Iterator:IterTrash<MAX_TRASH>;

stock TrashCan_SetPosX(trash, Float:posX)
    TrashCanInfo[trash][trashCanPos][0] = posX;

stock Float:TrashCan_GetPosX(trash)
    return TrashCanInfo[trash][trashCanPos][0];

stock TrashCan_SetPosY(trash, Float:posY)
    TrashCanInfo[trash][trashCanPos][1] = posY;

stock Float:TrashCan_GetPosY(trash)
    return TrashCanInfo[trash][trashCanPos][1];

stock TrashCan_SetPosZ(trash, Float:posZ)
    TrashCanInfo[trash][trashCanPos][2] = posZ;

stock Float:TrashCan_GetPosZ(trash)
    return TrashCanInfo[trash][trashCanPos][2];

stock TrashCan_SetRot(trash, Float:rot)
    TrashCanInfo[trash][trashCanPos][3] = rot;

stock Float:TrashCan_GetRot(trash)
    return TrashCanInfo[trash][trashCanPos][3];

stock TrashCan_SetModel(trash, model)
    TrashCanInfo[trash][trashCanModel] = model;

stock TrashCan_GetModel(trash, model)
    return TrashCanInfo[trash][trashCanModel];

stock TrashCan_SetWorld(trash, world)
    TrashCanInfo[trash][trashCanWorld] = world;

stock TrashCan_GetWorld(trash, world)
    return TrashCanInfo[trash][trashCanWorld];

stock TrashCan_SetInterior(trash, interior)
    TrashCanInfo[trash][trashCanInterior] = interior;

stock TrashCan_GetInterior(trash, interior)
    return TrashCanInfo[trash][trashCanInterior];

stock TrashCan_SetTimer(trash, playerid, timer)
    TrashCanInfo[trash][trashCanTimer][playerid] = timer;

stock TrashCan_GetTimer(trash, playerid)
    return TrashCanInfo[trash][trashCanTimer][playerid];

stock TrashCan_CreateObject(trash)
    TrashCanInfo[trash][trashCanObject] = interior;

stock TrashCan_GetObject(trash)
    return TrashCanInfo[trash][trashCanObject];

enum TRASHVEHICLE_ENUM
{
	Text3D:trashVehicleText,
	trashArea = {-1, ...},
	trashAmmount,
};
static TrashVehicle[MAX_VEHICLES][TRASHVEHICLE_ENUM];