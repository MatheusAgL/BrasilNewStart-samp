#define GZ_TYPE_SAFEZONE	        1
#define GZ_TYPE_MERCENARYZONE       2

enum ENUM_GANGZONE {
	gzID,
	Float:minX,
	Float:minY,
	Float:maxX,
	Float:maxY,
};
new GangZoneInfo[ENUM_GANGZONE];

stock GZ_GetID()
    return GangZoneInfo[gzID];

stock GZ_SetID(id)
    GangZoneInfo[gzID] = id;

stock Float:GZ_GetMinX()
    return GangZoneInfo[minX];

stock GZ_SetMinX(Float: min_x)
    GangZoneInfo[minX] = min_x;

stock Float:GZ_GetMinY()
    return GangZoneInfo[minY];

stock GZ_SetMinY(Float: min_y)
    GangZoneInfo[minY] = min_y;

stock Float:GZ_GetMaxX()
    return GangZoneInfo[maxX];

stock GZ_SetMaxX(Float: max_x)
    GangZoneInfo[maxX] = max_x;

stock Float:GZ_GetMaxY()
    return GangZoneInfo[maxY];

stock GZ_SetMaxY(Float: max_y)
    GangZoneInfo[maxY] = max_y;

stock GZ_Create(Float: min_x, Float: min_y, Float: max_x, Float: max_y)
{
    GangZoneInfo[gzID] = 
		GangZoneCreate(min_x, min_y, max_x, max_y);
}