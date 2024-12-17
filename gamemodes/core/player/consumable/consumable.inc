#if defined _inc_consumable_system
	#endinput
#endif
#define _inc_consumable_system true

#include <YSI_Coding\y_hooks>

#include <consumable_entry>

hook OnPlayerLogin(playerid)
{
    #if SERVER_ID == 3
        if (!Consumable_GetActive(playerid)) {
            inline D_ConsumableActive(did, ddialogid, dresponse, dlistitem, string:dtext[])
            {
                #pragma unused did, ddialogid, dresponse, dlistitem, dtext

                Consumable_Config(playerid);
                return 1;
            }
            Dialog_ShowCallback(playerid, using inline D_ConsumableActive, DIALOG_STYLE_MSGBOX, ""C_GRAY"Sistema de fome/sede", ""C_WHITE"Selecione abaixo:", "Ativado", "Desativado");
        }

        if (Consumable_GetActive(playerid) == 2)
            CONFIG_NeedSystem(playerid, false);
        else
            CONFIG_NeedSystem(playerid, true);
    #else
        CONFIG_NeedSystem(playerid);
	#endif

    return 1;
}

hook OnPlayerResetVars(playerid) {
    Consumable_SetActive(playerid, 1);
    return 1;
}

stock Consumable_Config(playerid) {

    if (Consumable_GetActive(playerid) == 2) {
        Consumable_SetActive(playerid, 1);
        CONFIG_NeedSystem(playerid, true);
    } else {
        Consumable_SetActive(playerid, 2);
        CONFIG_NeedSystem(playerid, false);
    }
    SendMsgF(playerid, COLOR_LIGHTBLUE, "Você %s o sistema de fome/sede, você pode mudar pelo /menu.", Consumable_GetActive(playerid) == 1 ? "ativou" : "desativou");
}