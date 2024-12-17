/** 
    @ Author: Mergevos
    @ Date: 29th July
    @ Git: github.com/Mergevos/samp-walking-styles
    @ Copyright (C) 2021
    @ About:
    	- This include gives you access to 15 walking styles
    @ Credits: 
        Me - Forking this and transforming into include
        MaximWizard - Fixing and rewritting this system

    @ Adapted on 11/01/2024
**/

#if defined _walking_Styles_inc
    #endinput
#endif

#include <YSI_Coding\y_hooks>

static const TIME_UPDATE_ANIMATION = 300;

enum WALKING_STYLES:
{
	WALKING_STYLE_DEFAULT = 0,
	WALKING_STYLE_NORMAL,
	WALKING_STYLE_PED,
	WALKING_STYLE_GANGSTA,
	WALKING_STYLE_GANGSTA2,
	WALKING_STYLE_OLD,
	WALKING_STYLE_FAT_OLD,
	WALKING_STYLE_FAT,
	WALKING_STYLE_WOMANOLD,
	WALKING_STYLE_WOMANFATOLD,
	WALKING_STYLE_SHUFFLE,
	WALKING_STYLE_LADY,
	WALKING_STYLE_LADY2,
	WALKING_STYLE_WHORE,
	WALKING_STYLE_WHORE2,
	WALKING_STYLE_DRUNK,
	WALKING_STYLE_BLIND
};

static 
	Walking_gsTimer[MAX_PLAYERS], 
	WALKING_STYLES: Walking_gsStyle[MAX_PLAYERS];

static const indexes_animations[] = {1231, 1224, 1226, 1276, 1278, 1280, 1228, 1230, 1458};

static const NameAnimations[][] =
{
    "WALK_player",
    "WALK_civi",
    "WALK_gang1",
    "WALK_gang2",
    "WALK_old",
    "WALK_fatold",
    "WALK_fat",
    "WOMAN_walkold",
    "WOMAN_walkfatold",
    "WALK_shuffle",
    "WOMAN_walknorm",
    "WOMAN_walkbusy",
    "WOMAN_walkpro",
    "WOMAN_walksexy",
    "WALK_drunk",
    "WALK_Wuzi"
};

stock bool: Player_SetWalkingStyle(playerid, WALKING_STYLES: style) {
    if(_:style >= sizeof(NameAnimations) || !IsPlayerConnected(playerid)) {
        return false;
    }
    Walking_gsStyle[playerid] = style;
    return true;
}

stock WALKING_STYLES: Player_GetWalkingStyle(playerid) {
	return IsPlayerConnected(playerid) ? Walking_gsStyle[playerid] : WALKING_STYLES: INVALID_PLAYER_ID;
}

hook OnPlayerConnect(playerid) 
{
	Walking_gsStyle[playerid] = WALKING_STYLE_DEFAULT;
    Walking_gsTimer[playerid] = -1;

	return 1;
}

hook OnPlayerDisconnect(playerid, reason) 
{
    if(Walking_gsTimer[playerid] != -1)
    {
        KillTimer(Walking_gsTimer[playerid]);
    }
    return 1;
}

hook OnPlayerUpdate(playerid) {  
	
    if (Player_GetWalkingStyle(playerid) > WALKING_STYLE_DEFAULT && Walking_gsTimer[playerid] == -1)
    {
        new KEY: keys, KEY: updown, KEY: leftright; 
        GetPlayerKeys(playerid, keys, updown, leftright);
        if (((!!updown  || !!leftright) && (keys & KEY_WALK)))
        {
            new temp_index_anim = GetPlayerAnimationIndex(playerid);
            for(new i = 0; i < sizeof indexes_animations; i++)
            {
                if (temp_index_anim == indexes_animations[i])
                {   
                    ApplyAnimation(playerid,"PED",NameAnimations[_:Walking_gsStyle[playerid]-1],4.1,true,true,true,true,1);
                    timer_WalkAnimation(playerid);
                    break;
                }
            }
        }        
    }
    return 1;
}

CALLBACK: timer_WalkAnimation(playerid)
{
    Walking_gsTimer[playerid] = -1;
    if(Walking_gsStyle[playerid] <= WALKING_STYLE_DEFAULT) 
    {
        return false;
    }
    new KEY: keys, KEY: updown, KEY: leftright;
    GetPlayerKeys(playerid,keys,updown,leftright);
    if (((!!updown  || !!leftright) && (keys & KEY_WALK) ))
    {
        new temp_index_anim = GetPlayerAnimationIndex(playerid);
        for(new i = 0; i < sizeof indexes_animations; i++)
        {
            if (temp_index_anim == indexes_animations[i])
            {   
                Walking_gsTimer[playerid] = SetTimerEx("timer_WalkAnimation",TIME_UPDATE_ANIMATION,false,"d",playerid);
                return true;
            }
        }
    }
	ApplyAnimation(playerid, "PED", NameAnimations[_:Walking_gsStyle[playerid]-1], 4.0, false, false, false, false, 1); 
    return 1;
}

CMD:mudarestilotx1(playerid, params[])
{
    inline D_WalkingStyle(meaid, meadialogid, mearesponse, mealistitem, string:meatext[])
    {
        #pragma unused meaid, meadialogid, meatext
        if (!mearesponse)
            return 1;

        switch (mealistitem) {
            case 1: Player_SetWalkingStyle(playerid, WALKING_STYLE_NORMAL);
            case 2: Player_SetWalkingStyle(playerid, WALKING_STYLE_PED);
            case 3: Player_SetWalkingStyle(playerid, WALKING_STYLE_GANGSTA);
            case 4: Player_SetWalkingStyle(playerid, WALKING_STYLE_GANGSTA2);
            case 5: Player_SetWalkingStyle(playerid, WALKING_STYLE_OLD);
            case 6: Player_SetWalkingStyle(playerid, WALKING_STYLE_FAT_OLD);
            case 7: Player_SetWalkingStyle(playerid, WALKING_STYLE_FAT);
            case 8: Player_SetWalkingStyle(playerid, WALKING_STYLE_WOMANOLD);
            case 9: Player_SetWalkingStyle(playerid, WALKING_STYLE_WOMANFATOLD);
            case 10: Player_SetWalkingStyle(playerid, WALKING_STYLE_SHUFFLE);
            case 11: Player_SetWalkingStyle(playerid, WALKING_STYLE_LADY);
            case 12: Player_SetWalkingStyle(playerid, WALKING_STYLE_LADY2);
            case 13: Player_SetWalkingStyle(playerid, WALKING_STYLE_WHORE);
            case 14: Player_SetWalkingStyle(playerid, WALKING_STYLE_WHORE2);
            case 15: Player_SetWalkingStyle(playerid, WALKING_STYLE_DRUNK);
            case 16: Player_SetWalkingStyle(playerid, WALKING_STYLE_BLIND);
            default: Player_SetWalkingStyle(playerid, WALKING_STYLE_DEFAULT);
        }
        SendClientMessage(playerid, -1, "Estilo de caminhar alterado com sucesso!");
        
        return 1;
    }
    Dialog_ShowCallback(playerid, using inline D_WalkingStyle, DIALOG_STYLE_LIST, ""C_YELLOW"Estilo de andar", 
                    "WALKING_STYLE_DEFAULT\nWALKING_STYLE_NORMAL\nWALKING_STYLE_PED\nWALKING_STYLE_GANGSTA\nWALKING_STYLE_GANGSTA2\nWALKING_STYLE_OLD\
                     \nWALKING_STYLE_FAT_OLD\nWALKING_STYLE_FAT\nWALKING_STYLE_WOMANOLD\nWALKING_STYLE_WOMANFATOLD\nWALKING_STYLE_SHUFFLE\nWALKING_STYLE_LADY\
                     \nWALKING_STYLE_LADY2\nWALKING_STYLE_WHORE\nWALKING_STYLE_WHORE2\nWALKING_STYLE_DRUNK\nWALKING_STYLE_BLIND", 
    "Selecionar", "Cancelar");

    return 1;
}