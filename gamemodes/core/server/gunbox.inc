/**--------------------------------------------------------------------------**\
 ______ ______  ______     __  ______  ______  ______     ______  __  ______ __  __
/\  == /\  == \/\  __ \   /\ \/\  ___\/\  ___\/\__  _\   /\  ___\/\ \/\__  _/\ \_\ \
\ \  _-\ \  __<\ \ \/\ \ _\_\ \ \  __\\ \ \___\/_/\ \/   \ \ \___\ \ \/_/\ \\ \____ \
 \ \_\  \ \_\ \_\ \_____/\_____\ \_____\ \_____\ \ \_\    \ \_____\ \_\ \ \_\\/\_____\
  \/_/   \/_/ /_/\/_____\/_____/\/_____/\/_____/  \/_/     \/_____/\/_/  \/_/ \/_____/

						 ==========================
		                    Brasil Play Start
                              ® 2012 - 2016
                          Módulo: Caixa de equipamentos
						 ==========================

\**--------------------------------------------------------------------------**/

#define MAX_GUNBOX                  (100)

enum GUNBOX_SERVER_ENUM {

    gunBoxOwner[MAX_PLAYER_NAME],
    
	Float: gunX,
	Float: gunY,
	Float: gunZ,
	
	gunType,
	gunWorld,
	gunInterior,
	gunObject,
	gunMateriais,
	Text3D:gunLabel,
}

new gunInfo[MAX_GUNBOX][GUNBOX_SERVER_ENUM];
new Iterator:IterGun<MAX_GUNBOX>;

stock createPlayerGunBox(playerid, stype)
{
	new Float:x, Float:y, Float:z, Float:a;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);
	
	new id;

    switch(stype)
	{
        case GUNBOX_SMALL: 	id = createGunBox(x, y, z - 0.80, a, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), stype, PlayerName[playerid]);
        case GUNBOX_NORMAL: id = createGunBox(x, y, z - 0.80, a, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), stype, PlayerName[playerid]);
        case GUNBOX_BIG: 	id = createGunBox(x, y, z - 0.73, a, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), stype, PlayerName[playerid]);
	}

	return id;
}

stock createGunBox(Float:x, Float:y, Float:z, Float:a, gun_interior=0, world=0, gtype=GUNBOX_NORMAL, const username[]="Ninguem") {

	new id = Iter_Free(IterGun);
	
	if (id != INVALID_ITERATOR_SLOT) {
	
	    Iter_Add(IterGun, id);
	    
	    format(gunInfo[id][gunBoxOwner], MAX_PLAYER_NAME, username);
	    
	    gunInfo[id][gunX] 	   	  = x;
	    gunInfo[id][gunY] 	   	  = y;
	    gunInfo[id][gunZ] 	   	  = z;
	    
	    gunInfo[id][gunType]      = gtype;
        gunInfo[id][gunWorld]     = world;
        gunInfo[id][gunInterior]  = gun_interior;
        gunInfo[id][gunMateriais] = 100;
        
        switch(gtype)
		{
            case GUNBOX_SMALL: 	gunInfo[id][gunObject]		= CreateDynamicObject(3013, x, y, z, 0.0, 0.0, a, world, gun_interior);
			case GUNBOX_NORMAL: gunInfo[id][gunObject]		= CreateDynamicObject(2358, x, y, z, 0.0, 0.0, a, world, gun_interior);
			case GUNBOX_BIG: 	gunInfo[id][gunObject]		= CreateDynamicObject(3014, x, y, z, 0.0, 0.0, a, world, gun_interior);
		}
		gunInfo[id][gunLabel]    = CreateDynamic3DTextLabel("Segure a tecla Y para equipar-se\nMateriais: 0", 0xFFFFFFAA, x, y, z, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world, gun_interior);
		
		updateGunBox(id);
	}
	return id;
}

stock destroyGunBox(id)
{
	if (Iter_Contains(IterGun, id))
	{
	    Iter_Remove(IterGun, id);
	    
	    DestroyDynamicObject(gunInfo[id][gunObject]);
	    DestroyDynamic3DTextLabel(gunInfo[id][gunLabel]);
	
	    return true;
	}
	return 0;
}

stock destroyAllGunBoxes()
{
	new count = 0;
	for(new gunboxid = 0; gunboxid < MAX_GUNBOX; gunboxid++)
		if(destroyGunBox(gunboxid))
			count ++;
	
	return count;
}

stock givePlayerGunBox(playerid, type)
{
    switch(type)
	{
        case GUNBOX_SMALL:	givePlayerItem(playerid, ITEM_TYPE_GUNBOXP, 3013, 1, "Caixa de equipamentos P");
		case GUNBOX_NORMAL:	givePlayerItem(playerid, ITEM_TYPE_GUNBOXM, 2358, 1, "Caixa de equipamentos M");
		case GUNBOX_BIG:	givePlayerItem(playerid, ITEM_TYPE_GUNBOXG, 3014, 1, "Caixa de equipamentos G");
	}
	return true;
}

stock updateGunBox( id )
{
	if (Iter_Contains(IterGun, id))
	{
		new string[128];

		format(string, sizeof string,
		"Segure a tecla Y para equipar-se\nMateriais: %d", gunInfo[id][gunMateriais]);

		UpdateDynamic3DTextLabelText(gunInfo[id][gunLabel], 0xFFFFFFCC, string);

		return true;
	}
	return false;
}

stock IsPlayerOwnerGunBox(playerid, id)
{
	if (Iter_Contains(IterGun, id))
		if (!strcmp(PlayerName[playerid], gunInfo[id][gunBoxOwner])) return true;

	return false;
}

stock countPlayerGunBox(playerid)
{
	new count;
	
	foreach(new gunboxid: IterGun)
	    if (IsPlayerOwnerGunBox(playerid, gunboxid)) count ++;

	return count;
}

stock GetPlayerGunBox(playerid)
{
	new Float:
		bau_dist = 999999.0;
	new bau_id   = -1;
	

	foreach(new id : IterGun)
	{
	    if (GetPlayerInterior(playerid) != gunInfo[id][gunInterior] || GetPlayerVirtualWorld(playerid) != gunInfo[id][gunWorld]) continue;
	
		new Float:dist = GetPlayerDistanceFromPoint(playerid, gunInfo[id][gunX], gunInfo[id][gunY], gunInfo[id][gunZ]);
		
		if (dist > 1.5000) continue;
		
		if (dist < bau_dist)
		{
		    bau_dist = dist;
		    bau_id   = id;
		}
	}
	
	return bau_id;
}


stock playerEquipGunBox( playerid, id )
{
	if (Iter_Contains(IterGun, id)) {

		new string[128];

		MEGAString[0] = EOS;

		new Float:playerLife[2];
		
		GetPlayerHealth(playerid, playerLife[0]);
		GetPlayerArmour(playerid, playerLife[1]);

	    switch(gunInfo[id][gunType])
		{
	        case GUNBOX_SMALL:
			{
				strcat(MEGAString, "{7D8084}Itens da caixa:\n\n");
				
				strcat(MEGAString, "{7D8084}Vida: 		{DBDCE0}+100\n");
				strcat(MEGAString, "{7D8084}Colete:		{DBDCE0}+20\n\n");
				
				strcat(MEGAString, "{7D8084}Taco: 		{DBDCE0}1\n");
				strcat(MEGAString, "{7D8084}9mm: 		{DBDCE0}40 balas\n");
				strcat(MEGAString, "{7D8084}Shotgun: 	{DBDCE0}20 balas\n");
				strcat(MEGAString, "{7D8084}MP5: 		{DBDCE0}80 balas\n");
				
				ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{DBDCE0}Caixa de equipamentos P", MEGAString, "Fechar", "");

				GivePlayerWeapon(playerid, WEAPON_BAT, 1);
				GivePlayerWeapon(playerid, WEAPON_COLT45, 40);
				GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 20);
				GivePlayerWeapon(playerid, WEAPON_MP5, 80);
				
				SetPlayerHealth(playerid, 100);

                if (playerLife[1] > 79)
					SetPlayerArmour(playerid, 100);
				else
				    SetPlayerArmour(playerid, playerLife[1] + 20);
			}
			case GUNBOX_NORMAL:
			{
				strcat(MEGAString, "{7D8084}Itens da caixa:\n\n");

				strcat(MEGAString, "{7D8084}Vida: 			{DBDCE0}+100\n");
				strcat(MEGAString, "{7D8084}Colete:			{DBDCE0}+50\n\n");

				strcat(MEGAString, "{DBDCE0}Katana: 		{DBDCE0}1\n");
				strcat(MEGAString, "{DBDCE0}Silenced 9mm:		{DBDCE0}50 balas\n");
				strcat(MEGAString, "{7D8084}Sawnoff Shotgun:	{DBDCE0}30 balas\n");
				strcat(MEGAString, "{7D8084}MP5: 			{DBDCE0}80 balas\n");
				strcat(MEGAString, "{7D8084}AK-47: 			{DBDCE0}100 balas\n");

				ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{DBDCE0}Caixa de equipamentos M", MEGAString, "Fechar", "");

				GivePlayerWeapon(playerid, WEAPON_KATANA, 1);
				GivePlayerWeapon(playerid, WEAPON_SILENCED, 50);
				GivePlayerWeapon(playerid, WEAPON_SAWEDOFF, 30);
				GivePlayerWeapon(playerid, WEAPON_MP5, 80);
				GivePlayerWeapon(playerid, WEAPON_AK47, 100);
				
				if (playerLife[0] > 24)
					SetPlayerHealth(playerid, 100);
				else
                    SetPlayerHealth(playerid, playerLife[0] + 75);

                if (playerLife[1] > 24)
					SetPlayerArmour(playerid, 100);
				else
				    SetPlayerArmour(playerid, playerLife[1] + 75);
			}
			case GUNBOX_BIG:
			{
				strcat(MEGAString, "{7D8084}Itens da caixa:\n\n");

				strcat(MEGAString, "{7D8084}Vida: 			{DBDCE0}+100\n");
				strcat(MEGAString, "{7D8084}Colete:				{DBDCE0}+100\n\n");

				strcat(MEGAString, "{DBDCE0}Faca: 			{DBDCE0}1\n");
				strcat(MEGAString, "{DBDCE0}Desert Eagle:		{DBDCE0}70 balas\n");
				strcat(MEGAString, "{7D8084}Combat Shotgun:	{DBDCE0}50 balas\n");
				strcat(MEGAString, "{7D8084}MP5: 			{DBDCE0}100 balas\n");
				strcat(MEGAString, "{7D8084}M4: 			{DBDCE0}120 balas\n");
				strcat(MEGAString, "{7D8084}Rifle: 			{DBDCE0}10 balas\n");

				ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{DBDCE0}Caixa de equipamentos G", MEGAString, "Fechar", "");

				GivePlayerWeapon(playerid, WEAPON_KNIFE, 1);
				GivePlayerWeapon(playerid, WEAPON_DEAGLE, 70);
				GivePlayerWeapon(playerid, WEAPON_SHOTGSPA, 50);
				GivePlayerWeapon(playerid, WEAPON_MP5, 100);
				GivePlayerWeapon(playerid, WEAPON_M4, 120);
				GivePlayerWeapon(playerid, WEAPON_RIFLE, 10);
				
				SetPlayerHealth(playerid, 100);
				SetPlayerArmour(playerid, 100);
			}
		}
		
		format(string, sizeof(string), "* %s se equipou na caixa de equipamentos", PlayerName[playerid]);
		SendClientMessageInRange(45.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
		
		gunInfo[id][gunMateriais] -= (gunInfo[id][gunType]+1)*10;
		Sound(playerid, 36401, 30.0);
		
		updateGunBox(id);
		
		if (gunInfo[id][gunMateriais] < 1) destroyGunBox(id);

		return true;
	}
	return false;
}

CALLBACK: equipGunBox(playerid, idbox, Float:percent) {

    new id = GetPlayerGunBox(playerid);
    
    if (idbox != id || !IsPlayerConnected(playerid)) {
    
        SetPVarInt(playerid, "timerEquip", -1);
        HidePlayerProgressBar(playerid, BarSprayTag[playerid]);
        ClearAnimations(playerid);
        return 0;
    }
    
    if (percent >= 100.0) {
    
        percent = 100.0;

        HidePlayerProgressBar(playerid, BarSprayTag[playerid]);
        
        playerEquipGunBox( playerid, id );
        
        SetPVarInt(playerid, "timerEquip", -1);
        
        ClearAnimations(playerid);
    } else {
    
        percent += 0.8;
        SetPVarInt(playerid, "timerEquip", SetTimerEx("equipGunBox", 95, false, "iif", playerid, id, percent));

		SetPlayerProgressBarValue(playerid, BarSprayTag[playerid], percent);
	}

	return true;
}
