
#define     MAX_FURNITURE     		200       // Máximo de móveis

enum mobInfo 
{
    mobID,

	Float:mobPosX,
	Float:mobPosY,
	Float:mobPosZ,
	Float:mobRotX,
	Float:mobRotY,
	Float:mobRotZ,

	mobObject,
	mobModel
};
static MobInfo[MAX_HOUSES][MAX_FURNITURE][mobInfo];

stock FurnitureHouse_SetID(house, furniture, id)
    MobInfo[house][furniture][mobID] = id;

stock FurnitureHouse_GetID(house, furniture)
    return MobInfo[house][furniture][mobID];

stock FurnitureHouse_SetModel(house, furniture, model)
    MobInfo[house][furniture][mobModel] = model;

stock FurnitureHouse_GetModel(house, furniture)
    return MobInfo[house][furniture][mobModel];

stock FurnitureHouse_SetPosX(house, furniture, Float:pos_x)
    MobInfo[house][furniture][mobPosX] = pos_x;

stock Float:FurnitureHouse_GetPosX(house, furniture)
    return MobInfo[house][furniture][mobPosX];

stock FurnitureHouse_SetPosY(house, furniture, Float:pos_y)
    MobInfo[house][furniture][mobPosY] = pos_y;

stock Float:FurnitureHouse_GetPosY(house, furniture)
    return MobInfo[house][furniture][mobPosY];

stock FurnitureHouse_SetPosZ(house, furniture, Float:pos_z)
    MobInfo[house][furniture][mobPosZ] = pos_z;

stock Float:FurnitureHouse_GetPosZ(house, furniture)
    return MobInfo[house][furniture][mobPosZ];

stock FurnitureHouse_SetRotX(house, furniture, Float:rot_x)
    MobInfo[house][furniture][mobRotX] = rot_x;

stock Float:FurnitureHouse_GetRotX(house, furniture)
    return MobInfo[house][furniture][mobRotX];

stock FurnitureHouse_SetRotY(house, furniture, Float:rot_y)
    MobInfo[house][furniture][mobRotY] = rot_y;

stock Float:FurnitureHouse_GetRotY(house, furniture)
    return MobInfo[house][furniture][mobRotY];

stock FurnitureHouse_SetRotZ(house, furniture, Float:rot_z)
    MobInfo[house][furniture][mobRotZ] = rot_z;

stock Float:FurnitureHouse_GetRotZ(house, furniture)
    return MobInfo[house][furniture][mobRotZ];

stock FurnitureHouse_GetObject(house, furniture)
    return MobInfo[house][furniture][mobObject];

stock FurnitureHouse_CreateObject(house, furniture, model, Float:posX, Float:posY, Float:posZ, Float:rotX, Float:rotY, Float:rotZ) {
    MobInfo[house][furniture][mobObject] = CreateDynamicObject(model, posX, posY, posZ, rotX, rotY, rotZ, house);
}

stock FurnitureHouse_UpdateObject(house, furniture, Float:posX, Float:posY, Float:posZ, Float:rotX, Float:rotY, Float:rotZ) {
    SetDynamicObjectPos(MobInfo[house][furniture][mobObject], posX, posY, posZ);
	SetDynamicObjectRot(MobInfo[house][furniture][mobObject], rotX, rotY, rotZ);
}