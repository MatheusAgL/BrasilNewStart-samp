#include <YSI_Coding\y_hooks>

hook OnLoadObjectsForPlayer(playerid)
{
    RemoveBuildingForPlayer(playerid, 968, -1526.4375, 481.3828, 6.9063, 0.25);
	RemoveBuildingForPlayer(playerid, 966, -1526.3906, 481.3828, 6.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 10829, -1523.2578, 486.7969, 6.1563, 0.25);
}