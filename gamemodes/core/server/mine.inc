#include <YSI_Coding\y_hooks>

//--------- Sistema de Mina Terrestre

#define MAX_MINAS 200

enum pMinaEnum {

	mina_valid,
	mina_id,
	mina_object,
	mina_area,
	mina_name[MAX_PLAYER_NAME],
	Float:mina_x,
	Float:mina_y,
	Float:mina_z,
};
new MinaInfo[MAX_MINAS][pMinaEnum];

givePlayerMina(playerid) {

	givePlayerItem(playerid, ITEM_TYPE_MINA, 19602, 1, "Mina Terrestre");
}

isMinaFull() {

	for(new mina; mina != MAX_MINAS; mina++) {

	    if (!MinaInfo[mina][mina_valid]) {
	        return 0;
	    }
	}
	return 1;
}

plantMina(playerid) {

	for(new mina; mina != MAX_MINAS; mina++) {

	    if (!MinaInfo[mina][mina_valid]) {

			new string[126];

			new Float:x, Float:y, Float:z;

			GetPlayerPos(playerid, x, y, z);

            MinaInfo[mina][mina_id] 		= playerid;
            MinaInfo[mina][mina_valid] 		= 1;
            format(MinaInfo[mina][mina_name], MAX_PLAYER_NAME, PlayerName[playerid]);

            SetTimerEx("removeminaid", 5000, false, "i", mina);

            MinaInfo[mina][mina_x] 			= x;
            MinaInfo[mina][mina_y] 			= y;
            MinaInfo[mina][mina_z] 			= z - 0.9;

            MinaInfo[mina][mina_area] 		= CreateDynamicCircle(x, y, 1.5);

            MinaInfo[mina][mina_object] 	= CreateDynamicObject(19602, MinaInfo[mina][mina_x], MinaInfo[mina][mina_y], MinaInfo[mina][mina_z], 0.0, 0.0, random(360));

			format(string, sizeof(string), "Jogador: %s colocou mina terrestre no local: (%.2f %.2f %.2f).",
			PlayerName[playerid], MinaInfo[mina][mina_x], MinaInfo[mina][mina_y], MinaInfo[mina][mina_z]);
   			server_log("minaterrestre", string);

			return mina;
	    }
	}
	return -1;
}

CALLBACK: removeminaid(minaid) {

	if (MinaInfo[minaid][mina_valid]) {

	    MinaInfo[minaid][mina_id] = INVALID_PLAYER_ID;
	    return 1;
	}
	return 0;
}

explodeMina(mina)
{
	CreateExplosion(MinaInfo[mina][mina_x],MinaInfo[mina][mina_y],MinaInfo[mina][mina_z], 0, 10.0);
 	CreateExplosion(MinaInfo[mina][mina_x]+0.5,MinaInfo[mina][mina_y]-0.5,MinaInfo[mina][mina_z], 0, 10.0);
  	CreateExplosion(MinaInfo[mina][mina_x]-0.5,MinaInfo[mina][mina_y]+0.5,MinaInfo[mina][mina_z], 0, 10.0);
   	CreateExplosion(MinaInfo[mina][mina_x],MinaInfo[mina][mina_y],MinaInfo[mina][mina_z]+0.5, 0, 10.0);

	/*AddFire(MinaInfo[mina][mina_x], MinaInfo[mina][mina_y], MinaInfo[mina][mina_z] + 0.9);
	AddFire(MinaInfo[mina][mina_x], MinaInfo[mina][mina_y] + 1, MinaInfo[mina][mina_z] + 0.9);
	AddFire(MinaInfo[mina][mina_x], MinaInfo[mina][mina_y] - 2, MinaInfo[mina][mina_z] + 0.9);
	AddFire(MinaInfo[mina][mina_x] + 2, MinaInfo[mina][mina_y], MinaInfo[mina][mina_z] + 0.9);
	AddFire(MinaInfo[mina][mina_x] - 2, MinaInfo[mina][mina_y], MinaInfo[mina][mina_z] + 0.9);*/

	new string[75];

	foreach(new playerid : Player) {

		if (IsPlayerInRangeOfPoint(playerid, 9.0, MinaInfo[mina][mina_x], MinaInfo[mina][mina_y], MinaInfo[mina][mina_z]))
		{
		    format(string, sizeof string, "* A mina de %s explodiu perto de você !", MinaInfo[mina][mina_name]);
	 		SendClientMessage(playerid, COLOR_LIGHTRED, string);
			SetPlayerHealth(playerid, 0.0);
		}
	}
	destroyMina(mina);
}

checkAreaMina(playerid, areaid){

	new string[65];
	for(new mina; mina != MAX_MINAS; mina++) {

	    if (MinaInfo[mina][mina_valid] && areaid == MinaInfo[mina][mina_area] && MinaInfo[mina][mina_id] != playerid) {

			if (IsPlayerInRangeOfPoint(playerid, 2.5, MinaInfo[mina][mina_x], MinaInfo[mina][mina_y], MinaInfo[mina][mina_z])) {

                format(string, sizeof string, "* Você pisou na mina de %s !", MinaInfo[mina][mina_name]);
    			SendClientMessage(playerid, COLOR_LIGHTRED, string);
                explodeMina(mina);
				return 1;
   			}
		}
	}
	return 1;
}

destroyMina(minaid) {

	if (MinaInfo[minaid][mina_valid]) {

	    MinaInfo[minaid][mina_valid] = 0;
	    DestroyDynamicObject(MinaInfo[minaid][mina_object]);
	    DestroyDynamicArea(MinaInfo[minaid][mina_area]);
	    return 1;
	}
	return 0;
}

hook OnPlayerEnterDynamicArea(playerid, areaid)
{
	checkAreaMina(playerid, areaid);
	return 1;
}

hook OP_ShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z){

	for(new mina; mina != MAX_MINAS; mina++) {

	    if (MinaInfo[mina][mina_valid] && objectid == MinaInfo[mina][mina_object]) {

    		SendClientMessage(playerid, COLOR_LIGHTRED, "* Você atirou em uma mina !");
            explodeMina(mina);
			break;
		}
	}
    return 1;
}