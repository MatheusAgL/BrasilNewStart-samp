#if defined _inc_sweeper_system
	#endinput
#endif
#define _inc_sweeper_system true

#include <YSI_Coding\y_hooks>

#include <trashcan>


hook OnPlayerEnterDynamicArea(playerid, areaid)
{
	if (!PlayerIsGari(playerid) || Player_GetBusyHand(playerid, RIGHT_HAND)) 
		return false;

	for(new trucks; trucks != MAX_VEHICLES; trucks++)
	{
	    if (areaid == lixo_Area[trucks])
		{
			if (lixo_Ammount[trucks] >= 100)
			{
				RemovePlayerAttachedObject(playerid, Slot_Pizza);
				SetPVarInt(playerid, "pegouLixo", 0), SetPVarInt(playerid, "quantLixosPegou", 0), SetPVarInt(playerid, "emColetaLixo", 0);

				Player_SetBusyHand(playerid, RIGHT_HAND, true);

				return SendClientMessage(playerid, COLOR_LIGHTRED, "O caminhão está cheio, volte ao Lixão para entregar o lixo.");
			}

            lixoAddCar(playerid, caminhoes);

			RemovePlayerAttachedObject(playerid, Slot_Pizza);
   			SetPVarInt(playerid, "pegouLixo", 0);

			break;
	    }
	}
	return 1;
}