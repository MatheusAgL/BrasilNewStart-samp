#include <YSI_Coding\y_hooks>

#include <kidnapping_entry>
#include <kidnapping_cmds>

hook OnPlayerResetVars(playerid)
{
	usandoCativeiro[playerid] = 0;
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if (GetPlayerBeingAbducted(playerid))
	{
		new string[128];

		format(string, sizeof(string), "(Sequestro): A vítima do sequestro %s foi assassinada, sequestro finalizado.", PlayerName[playerid]);
		SendClientMessageToAll(COLOR_LIGHTRED, string);
		
		SetPlayerBeingAbducted(playerid, false);
		
		sequestrosAtivo--;
	}
	return 1;
}

CALLBACK:ripOrgan_Start(playerid, abductedid, percent)
{
    new	string[128],
		rdon = random(6);

    if (percent >= 100)
	{
        format(string, sizeof string, "Perna de %s", PlayerName[abductedid]), dropItem(abductedid, ITEM_TYPE_ORGAO, ITEM_MODEL_PERNA, 1, string);
		format(string, sizeof string, "Braco de %s", PlayerName[abductedid]), dropItem(abductedid, ITEM_TYPE_ORGAO, ITEM_MODEL_BRACO, 1, string);
        format(string, sizeof string, "Tronco de %s", PlayerName[abductedid]), dropItem(abductedid, ITEM_TYPE_ORGAO, ITEM_MODEL_TRONCO, 1, string);
		format(string, sizeof string, "Cabeca de %s", PlayerName[abductedid]), dropItem(abductedid, ITEM_TYPE_ORGAO, ITEM_MODEL_CABECA, 1, string);

	    TogglePlayerControllable(playerid, true);
		retirandoOrgaos[playerid] = false;
		SetCameraBehindPlayer(playerid);
		RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);

		TogglePlayerControllable(abductedid, true);
		retirandoOrgaos[abductedid] = false;
		SetPlayerHealth(abductedid, 0);

		usandoCativeiro[playerid] = 0;

		DestroyDynamic3DTextLabel(textRipOrgan[playerid]); SetPVarInt(playerid, "timerRipOrgan_Start", -1);

	} else {

	    percent += 1;

	    switch(rdon) {
			case 1:		ApplyAnimation(playerid, "OTB", "betslp_tnk", 4.1, false, true, true, true, 1, SYNC_ALL);
		    case 2,3:	ApplyAnimation(playerid, "OTB", "betslp_lkabt", 4.1, false, true, true, true, 1, SYNC_ALL);
			default:	ApplyAnimation(playerid, "OTB", "betslp_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
		}

	    format(string, sizeof string, "Retirando órgãos... %i%", percent);
		UpdateDynamic3DTextLabelText(textRipOrgan[playerid], 0x9D3A3AF9, string);

        SetPVarInt(playerid, "timerRipOrgan_Start", SetTimerEx("ripOrgan_Start", 2950, false, "iiii", playerid, abductedid, percent));
	}
}