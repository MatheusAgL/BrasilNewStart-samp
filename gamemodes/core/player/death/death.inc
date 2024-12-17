
#include <death_entry>

// Sistema de ferimento, aceitar a morte
stock Textdraw_InjuredAccepted(playerid, bool:show = false)
{
    if (show) {
        for(new text; text < sizeof (textMorteAcc); text++)
            TextDrawShowForPlayer(playerid, textMorteAcc[text]);

        PlayerTextDrawShow(playerid, textPlayerMorteAcc[playerid]);
        PlayerTextDrawSetString(playerid, textPlayerMorteAcc[playerid], "_");

        SelectTextDraw(playerid, COLOR_SELECTED);
    } else {
        for(new text; text < sizeof (textMorteAcc); text++)
            TextDrawHideForPlayer(playerid, textMorteAcc[text]);

        PlayerTextDrawHide(playerid, textPlayerMorteAcc[playerid]);

        CancelSelectTextDraw(playerid);
    }
}

stock Death_Accepted(playerid, killerid)
{
    Death_SetInjured(playerid, false);

    Textdraw_InjuredAccepted(playerid, false);

	DestroyDynamic3DTextLabel(Injured_3DText(playerid));

	DamagePlayer(playerid, 200.0, killerid, DanoInfo[playerid][danoWeapon], DanoInfo[playerid][danoBodypart]);

	if (killerid != INVALID_PLAYER_ID)
	{
		new string[95];
		format(string, sizeof string, "* O jogador %s acabou não resistindo aos ferimentos que você causou.", PlayerName[playerid]);
		SendClientMessage(killerid, COLOR_LIGHTRED, string);
		format(string, sizeof string, "* O jogador %s foi responsabilizado por sua morte!", PlayerName[killerid]);
		SendClientMessage(playerid, COLOR_LIGHTRED, string);
	} else {
		SendClientMessage(playerid, COLOR_LIGHTRED, "Você não resistiu aos ferimentos e morreu...");
	}
}

hook OnPlayerDamageDone(playerid, Float:amount, issuerid, weapon, bodypart)
{
    if (bodypart != BODY_PART_HEAD) {

        new Float:armour, 
            Float:health;

        GetPlayerArmour(playerid, armour);
        GetPlayerHealth(playerid, health);

        if (health <= 10.0) {
            ApplyAnimation(playerid, "CRACK", "crckdeth3", 4.1, 0, 1, 1, 1, 1, 1);
        }
    }
	return 1;
}