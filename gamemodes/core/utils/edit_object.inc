
public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if (response == 1 || response == 0) {
        if (Portao_CancelEdit(objectid, x, y, z, rx, ry, rz))
            SendClientMessage(playerid, -1, "A edição do objeto foi finalizada.");
	}
	return 1;
}