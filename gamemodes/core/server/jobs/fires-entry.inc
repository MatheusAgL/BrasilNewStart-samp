
// Callbacks
forward OnFireDeathPlayer(fireid, playerid);
forward OnFireDamagePlayer(fireid, damagedid);
forward ExtinguishFire(playerid);

#define MAX_FIRES 			100
#define INVALID_FIRE        0xFFFF
#define IsValidFire(%0) Iter_Contains(iterFires, %0)

new Iterator:iterFires<MAX_FIRES>;

enum f_info
{
	fireo,
 	Float:firex,
 	Float:firey,
 	Float:firez,
 	Float:fireh,
	fireEventID,
 	Text3D:firet,
};
new fireinfo[MAX_FIRES][f_info];

stock AddFire(Float:x, Float:y, Float:z)
{
	new i = Iter_Free(iterFires);

	if (i != -1) {
 		fireinfo[i][firet] = CreateDynamic3DTextLabel("100/100", 0xAAAAAA80, x, y, z, 10.0);
	        
		fireinfo[i][fireo] = CreateDynamicObject(18690, x, y, z-2.0, 0.0, 0.0, 0.0);
		fireinfo[i][firex] = x;
		fireinfo[i][firey] = y;
		fireinfo[i][firez] = z;
		fireinfo[i][fireh] = 100.0;
		fireinfo[i][fireEventID] = -1;
		Iter_Add(iterFires, i);

		return i;
	}
	return INVALID_FIRE;
}

stock DeleteFire(fireid)
{
	if (IsValidFire(fireid)) {
		DestroyDynamicObject(fireinfo[fireid][fireo]);
		DestroyDynamic3DTextLabel(fireinfo[fireid][firet]);
		Iter_Remove(iterFires, fireid);

		return true;
	}
	return false;
}

stock DeleteAllFire()
{
	for(new i; i < MAX_FIRES; i++) {
		DeleteFire(i);
	}
}

stock GetPlayerFire(playerid)
{
	foreach(new i : iterFires) {
	    if (IsPlayerInRangeOfPoint(playerid, 1.5, fireinfo[i][firex],  fireinfo[i][firey],  fireinfo[i][firez])) {
	        return i;
		}
	}
	return false;
}

stock GetPlayerNearFire(playerid, &Float:x, &Float:y, &Float:z) {

	if (CountFires()) {
		new fireid, Float:maxdist = 9999999.00;

		foreach(new i : iterFires) {
		
		    new Float:dist = GetPlayerDistanceFromPoint(playerid, fireinfo[i][firex],  fireinfo[i][firey],  fireinfo[i][firez]);

			if (dist < maxdist) {
				maxdist = dist;
			    fireid = i;
			}
		}
	 	x = fireinfo[fireid][firex];
	 	y = fireinfo[fireid][firey];
	 	z = fireinfo[fireid][firez];
	}
}

stock CountFires() {
	return Iter_Count(iterFires);
}

stock IsPlayerInFire(playerid, fireid) 
{
	if (GetPlayerFire(playerid) == fireid)
	    return true;

	return false;
}

stock IsPlayerInAnyFire(playerid) {
	return GetPlayerFire(playerid);
}

stock f_PlayerApagando(playerid, i, KEY:newkeys) {

	if (HOLDING(KEY_FIRE))
	{
        if (GetPlayerWeapon(playerid) == WEAPON:42 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {

			if (PlayerFaces(playerid, fireinfo[i][firex],  fireinfo[i][firey],  fireinfo[i][firez], 1.0) &&
			IsPlayerInRangeOfPoint(playerid, 5, fireinfo[i][firex],  fireinfo[i][firey],  fireinfo[i][firez]))
 			{
				new Float:extinguished = 8.0 + (random(81) / 10.0),
					stringf[45];

 	       	    fireinfo[i][fireh] -= extinguished;

				format(stringf, 44, "%.0f/100", fireinfo[i][fireh]);
				UpdateDynamic3DTextLabelText(fireinfo[i][firet], 0xAAAAAA80, stringf);

				if(fireinfo[i][fireEventID] != -1) {
					CallRemoteFunction("UpdateFireEvent", "ddf", playerid, fireinfo[i][fireEventID], extinguished);
				}

				if(fireinfo[i][fireh] < 0.1){
					DeleteFire(i);
					CallRemoteFunction("ExtinguishFire", "d", playerid);
				}
			}
		}
        else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetVehicleModel(GetPlayerVehicleID(playerid)) == 407)
        {
 	   	    if(PlayerFaces(playerid, fireinfo[i][firex],  fireinfo[i][firey],  fireinfo[i][firez], 3.0) &&
 			IsPlayerInRangeOfPoint(playerid, 20, fireinfo[i][firex],  fireinfo[i][firey],  fireinfo[i][firez])){

				new Float:extinguished = 12.0 + (random(130) / 10.0),
					stringf[45];

 	       	    fireinfo[i][fireh] -= extinguished;

				if(fireinfo[i][fireEventID] != -1) {
					CallRemoteFunction("UpdateFireEvent", "ddf", playerid, fireinfo[i][fireEventID], extinguished);
				}

				format(stringf, 44, "%.0f/100", fireinfo[i][fireh]);
				UpdateDynamic3DTextLabelText(fireinfo[i][firet], 0xAAAAAA80, stringf);

				if(fireinfo[i][fireh] < 0.1){
					DeleteFire(i);
					CallRemoteFunction("ExtinguishFire", "d", playerid);
				}
			}
		}
	}
}

Float:DistanceCameraTargetToLocation(Float:CamX, Float:CamY, Float:CamZ,   Float:ObjX, Float:ObjY, Float:ObjZ,   Float:FrX, Float:FrY, Float:FrZ) 
{
	new Float:TGTDistance;
	TGTDistance = floatsqroot((CamX - ObjX) * (CamX - ObjX) + (CamY - ObjY) * (CamY - ObjY) + (CamZ - ObjZ) * (CamZ - ObjZ));
	new Float:tmpX, Float:tmpY, Float:tmpZ;
	tmpX = FrX * TGTDistance + CamX;
	tmpY = FrY * TGTDistance + CamY;
	tmpZ = FrZ * TGTDistance + CamZ;
	return floatsqroot((tmpX - ObjX) * (tmpX - ObjX) + (tmpY - ObjY) * (tmpY - ObjY) + (tmpZ - ObjZ) * (tmpZ - ObjZ));
}

stock PlayerFaces(playerid, Float:x, Float:y, Float:z, Float:radius)
{
	new Float:cx,Float:cy,Float:cz,Float:fx,Float:fy,Float:fz;
	GetPlayerCameraPos(playerid, cx, cy, cz);
	GetPlayerCameraFrontVector(playerid, fx, fy, fz);

	return (radius >= DistanceCameraTargetToLocation(cx, cy, cz, x, y, z, fx, fy, fz));
}

stock DamagePlayerByFire(playerid, fireId, Float:damage) {
	new Float:HP;
	GetPlayerHealth(playerid, HP);
	SetPlayerHealth(playerid, HP-damage);
	CallRemoteFunction("OnFireDamagePlayer", "dd", fireId, playerid);
		
	GetPlayerHealth(playerid, HP);
	if (HP < 0.1) {
		CallRemoteFunction("OnFireDeathPlayer", "dd", fireId, playerid);
	}
}

task UpdateFires[1500]()
{
    static KEY:newkeys, KEY:lr, KEY:ud;
    
	foreach(new i : iterFires) {
		foreach(new p : Player)
		{
		    // apagar
		    GetPlayerKeys(p, newkeys, ud, lr);
		    
		    // Apagar o fogo
		    f_PlayerApagando(p, i, newkeys);
		
		    // Tirar vida
   			if (IsPlayerInRangeOfPoint(p, 1.8, fireinfo[i][firex], fireinfo[i][firey], fireinfo[i][firez]))
			{
				DamagePlayerByFire(p, i, 8.0);
				SetPlayerDrunkLevel(p, 8000);
				SetPVarInt(p, "DrunkL", 1);
			}
		}

  		fireinfo[i][fireh] -= 0.1;

		if(fireinfo[i][fireEventID] != -1) {
			CallRemoteFunction("UpdateFireEvent", "ddf", INVALID_PLAYER_ID, fireinfo[i][fireEventID], 0.1);
		}

	    if (fireinfo[i][fireh] < 0.2) {
	      	DeleteFire(i);
	        CallRemoteFunction("ExtinguishFire", "d", INVALID_PLAYER_ID);
		}

 	    new stringf[45];
 	    format(stringf, 44, "%.0f/100", fireinfo[i][fireh]);
		UpdateDynamic3DTextLabelText(fireinfo[i][firet], 0xAAAAAA80, stringf);
	}
	return 1;
}
