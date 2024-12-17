/** -------------------------------------------------------------------------- **\
 ______ ______  ______     __  ______  ______  ______     ______  __  ______ __  __
/\  == /\  == \/\  __ \   /\ \/\  ___\/\  ___\/\__  _\   /\  ___\/\ \/\__  _/\ \_\ \
\ \  _-\ \  __<\ \ \/\ \ _\_\ \ \  __\\ \ \___\/_/\ \/   \ \ \___\ \ \/_/\ \\ \____ \
 \ \_\  \ \_\ \_\ \_____/\_____\ \_____\ \_____\ \ \_\    \ \_____\ \_\ \ \_\\/\_____\
  \/_/   \/_/ /_/\/_____\/_____/\/_____/\/_____/  \/_/     \/_____/\/_/  \/_/ \/_____/

						 ==========================
		                    Brasil Play Start
                              ® 2013 - 2017
                             Módulo: Medkit
						 ==========================

\** -------------------------------------------------------------------------- **/

#define 		MAX_MEDKIT   		100

enum MedkitEnum
{
	bool:medkit_Valid = false,
	medkitObject[2],
	medkitWorld,
	medkitTime,
	Float:medkitPos[3],
	Float:medkitLife,
};
new MedkitInfo[MAX_MEDKIT][MedkitEnum];

new Iterator:IterMedkit<MAX_MEDKIT>;

CALLBACK: OnUpdateMedKit(playerid) {
	for (new medkit; medkit != MAX_MEDKIT; medkit++) {
		if (MedkitInfo[medkit][medkit_Valid] && GetPlayerVirtualWorld(playerid) == MedkitInfo[medkit][medkitWorld] &&
		IsPlayerInRangeOfPoint(playerid, 1.2, MedkitInfo[medkit][medkitPos][0], MedkitInfo[medkit][medkitPos][1], MedkitInfo[medkit][medkitPos][2]))
		{
			if (givePlayerLife(playerid, 5.0)) {
				PlayerPlaySound(playerid, 45400, 0.0, 0.0, 0.0);

				if (MedkitInfo[medkit][medkitLife] < 5.0) 
					destroyMedKit(medkit);

				MedkitInfo[medkit][medkitLife] -= 5.0;
			}
	    }
    }
	return 1;
}

stock createMedKit(playerid, Float:medLife = 150.0)
{
	new Float:x,
		Float:y,
		Float:z;

	GetPlayerPos(playerid, x, y, z);
	
	new id = Iter_Free(IterMedkit);
	
	if (id != INVALID_ITERATOR_SLOT)
	{
	    Iter_Add(IterMedkit, id);
	    
	    x += randomfloat(0.3);
		y += randomfloat(0.3);
		z -= 1.0;
	        
		SoundInRange(20800, 10.0, x, y, z);
	        
		MedkitInfo[id][medkit_Valid] = true;

		MedkitInfo[id][medkitPos][0] = x;
	 	MedkitInfo[id][medkitPos][1] = y;
		MedkitInfo[id][medkitPos][2] = z;
	        
		MedkitInfo[id][medkitLife] = medLife;
	        
		MedkitInfo[id][medkitWorld] = GetPlayerVirtualWorld(playerid);
	        
		MedkitInfo[id][medkitObject][0] = CreateDynamicObject(11736, x, y, z, 0.0, 0.0, 0.0, MedkitInfo[id][medkitWorld]);
		MedkitInfo[id][medkitObject][1] = CreateDynamicObject(19606, x, y, z - 1.3, 0.0, 0.0, 0.0, MedkitInfo[id][medkitWorld]);
	        
		MedkitInfo[id][medkitTime] = gettime() + 10 * 60;
	}
	return id;
}

stock destroyMedKit(id)
{
    if (Iter_Contains(IterMedkit, id))
    {
		Iter_Remove(IterMedkit, id);

		MedkitInfo[id][medkit_Valid] = false;

		SoundInRange(17807, 10.0, MedkitInfo[id][medkitPos][0], MedkitInfo[id][medkitPos][1], MedkitInfo[id][medkitPos][2]);

		DestroyDynamicObject(MedkitInfo[id][medkitObject][0]);
		DestroyDynamicObject(MedkitInfo[id][medkitObject][1]);
	}
	return true;
}

stock givePlayerLife(playerid, Float:life)
{
	//if (IsPlayerSpawned(playerid)) return false;

	new Float:playerLife[2];
	
	GetPlayerHealth(playerid, playerLife[0]);
	GetPlayerArmour(playerid, playerLife[1]);

	if (playerLife[0] + playerLife[1] + life < 200.0)
	{
		if (playerLife[0] < 100.0)
		{
			SetPlayerHealth(playerid, playerLife[0] + life);
		}
		else
		{
			SetPlayerArmour(playerid, playerLife[1] + life);
		}
		return true;
	}
	
	return false;
}

hook OP_ShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z)
{
	for (new medkit; medkit != MAX_MEDKIT; medkit++)
	{
		if (MedkitInfo[medkit][medkitObject][0] == objectid) 
			destroyMedKit(medkit);
	}

	return 1;
}









