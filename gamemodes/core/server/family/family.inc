/**--------------------------------------------------------------------------**\
 ______ ______  ______     __  ______  ______  ______     ______  __  ______ __  __
/\  == /\  == \/\  __ \   /\ \/\  ___\/\  ___\/\__  _\   /\  ___\/\ \/\__  _/\ \_\ \
\ \  _-\ \  __<\ \ \/\ \ _\_\ \ \  __\\ \ \___\/_/\ \/   \ \ \___\ \ \/_/\ \\ \____ \
 \ \_\  \ \_\ \_\ \_____/\_____\ \_____\ \_____\ \ \_\    \ \_____\ \_\ \ \_\\/\_____\
  \/_/   \/_/ /_/\/_____\/_____/\/_____/\/_____/  \/_/     \/_____/\/_/  \/_/ \/_____/

						 ==========================
		                    Brasil Project City
                              ® 2012 - 2016
                             Módulo: Famílias
						 ==========================

\**--------------------------------------------------------------------------**/

#include < YSI_Coding\y_hooks >

#define MAX_FAMILYS         (20)
#define MAX_FAMILY_MEMBERS  (25)
#define MAX_FAMILY_NAME     (24)
#define MAX_FAMILY_CARS     (5)

enum familyEnum {
	
	familyID,

	// Nome da família
	familyName[MAX_FAMILY_NAME],

	// Líder da família
	familyLeader[MAX_PLAYER_NAME],
	familyLeaderID,

	// Sub Líder da família
	familySubLeader[MAX_PLAYER_NAME],
	familySubLeaderID,

	// Spawm da família
	Float: familySpawn[4],

	// Interior do spawn
	familyInterior,

	// Virtual do spawn
	familyWorld,

	// Dinheiro
	familyMoney,

	// Pickup
	familyPickup,

	// 3DText Label
	Text3D:familyLabel,
	
	Timestamp:familyVencimento
}
enum familyVehiclesEnum {
	familyVehDBID,
	familyVehId,
	familyVehModel,
	Float:familyVehPos[4],
}

enum familyMemberEnum {
	familyMemberID,
	familyMemberName[MAX_PLAYER_NAME]
}

new familyInfo		   [MAX_FAMILYS][familyEnum];
new familyMembers	   [MAX_FAMILYS][MAX_FAMILY_MEMBERS][familyMemberEnum];
new familyVehInfo	   [MAX_FAMILYS][MAX_FAMILY_CARS][familyVehiclesEnum];
new Iterator:IterFamily<MAX_FAMILYS>,
	Iterator:IterFamilyMembers[MAX_FAMILYS]<MAX_FAMILY_MEMBERS>,
	Iterator:IterFamilyVehicles[MAX_FAMILYS]<MAX_FAMILY_CARS>;

new SelectFamily       [MAX_PLAYERS][MAX_FAMILYS];

static 
	Statement: stmt_selectFamilies,
    Statement: stmt_createFamily,
	Statement: stmt_destroyFamily,
	Statement: stmt_updateFamily,
	Statement: stmt_selectFamilyMembers,
	Statement: stmt_selectFamilyVehicles,
	Statement: stmt_createFamilyVehicle,
	Statement: stmt_updateFamilyVehicle,
	Statement: stmt_createFamilyMember,
	Statement: stmt_destroyFamilyMember
;

hook OnMySQLConnected() {
    static const query_createFamily[] = 
		"INSERT INTO families \
			(name, leader, subleader, spawn_x, spawn_y, spawn_z, spawn_angle, spawn_interior, spawn_world, money, due_date) \
		VALUES \
			('?', '?', ?, '?', '?', '?', '?', '?', '?', '?', '?')";
	stmt_createFamily = MySQL_PrepareStatement(MySQL_Handle, query_createFamily);

	static const query_updateFamily[] = "UPDATE families \
		SET name='?', leader='?', subleader=?, spawn_x='?', spawn_y='?', spawn_z='?', spawn_angle='?', \
			spawn_interior='?', spawn_world='?', money='?', due_date='?' \
		WHERE id=?";
	stmt_updateFamily = MySQL_PrepareStatement(MySQL_Handle, query_updateFamily);

	static const query_destroyFamily[] = "DELETE FROM `families` WHERE `id` = '?'";
	stmt_destroyFamily = MySQL_PrepareStatement(MySQL_Handle, query_destroyFamily);

    static const query_selectFamilies[] = "SELECT \
			f.id, f.name, p1.nome, f.leader, p2.nome, f.subleader, f.spawn_x, f.spawn_y, f.spawn_z, f.spawn_angle, \
			f.spawn_interior, f.spawn_world, f.money, f.due_date \
		FROM families f \
		INNER JOIN player p1 ON \
			p1.id = f.leader \
		LEFT JOIN player p2 ON \
			p2.id = f.subleader \
		ORDER BY f.id";
	stmt_selectFamilies = MySQL_PrepareStatement(MySQL_Handle, query_selectFamilies);

	static const query_selectFamilyMembers[] = "SELECT \
			fm.player, fm.family, p1.nome \
		FROM family_members fm \
		INNER JOIN player p1 ON \
			p1.id = fm.player \
		ORDER BY fm.family";
	stmt_selectFamilyMembers = MySQL_PrepareStatement(MySQL_Handle, query_selectFamilyMembers);

	static const query_selectFamilyVehicles[] = "SELECT \
			fv.id, fv.family, fv.model, fv.pos_x, fv.pos_y, fv.pos_z, fv.angle \
		FROM family_vehicles fv \
		ORDER BY fv.family";
	stmt_selectFamilyVehicles = MySQL_PrepareStatement(MySQL_Handle, query_selectFamilyVehicles);

	static const query_createFamilyVehicle[] = 
		"INSERT INTO family_vehicles (family, model, pos_x, pos_y, pos_z, angle) VALUES ('?', '?', '?', '?', '?', '?')";
	stmt_createFamilyVehicle = MySQL_PrepareStatement(MySQL_Handle, query_createFamilyVehicle);

	static const query_updateFamilyVehicle[] = "UPDATE family_vehicles \
		SET model='?', pos_x='?', pos_y='?', pos_z='?', angle='?' \
		WHERE id=?";
	stmt_updateFamilyVehicle = MySQL_PrepareStatement(MySQL_Handle, query_updateFamilyVehicle);

	static const query_createFamilyMember[] = 
		"INSERT INTO family_members (player, family) VALUES ('?', '?')";
	stmt_createFamilyMember = MySQL_PrepareStatement(MySQL_Handle, query_createFamilyMember);

	static const query_destroyFamilyMember[] = "DELETE FROM `family_members` WHERE `player` = ? AND family = ?";
	stmt_destroyFamilyMember = MySQL_PrepareStatement(MySQL_Handle, query_destroyFamilyMember);

	return 1;
}

stock Family_Create(fNome[], Float:fSpawnX, Float:fSpawnY, Float:fSpawnZ, Float:fSpawnA=0.0, fInterior=0, fWorld=0, leaderID) {
	new id = Iter_Free(IterFamily);

	if ( id != -1 ) {

	    Iter_Add(IterFamily, id);

		format(familyInfo[id][familyName],   MAX_FAMILY_NAME, fNome);

		familyInfo[id][familyLeaderID] = Player_GetAccountID(leaderID);
		format(familyInfo[id][familyLeader], MAX_PLAYER_NAME, PlayerName[leaderID]);

		familyInfo[id][familySubLeaderID] = 0;
		format(familyInfo[id][familySubLeader], MAX_PLAYER_NAME, "Ninguem");

		familyInfo[id][familySpawn][0] = fSpawnX;
		familyInfo[id][familySpawn][1] = fSpawnY;
		familyInfo[id][familySpawn][2] = fSpawnZ;
		familyInfo[id][familySpawn][3] = fSpawnA;

		familyInfo[id][familyInterior] = fInterior;
		familyInfo[id][familyWorld]    = fWorld;
		familyInfo[id][familyMoney]    = 0;
		
		familyInfo[id][familyVencimento] = Now() + Days:30;

		new string[75];

		format(string, sizeof string, "HQ da Família %s", fNome);
		familyInfo[id][familyLabel] = CreateDynamic3DTextLabel(string, 0xFFAA00FF, fSpawnX, fSpawnY, fSpawnZ, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, fWorld, fInterior);
		familyInfo[id][familyPickup] = CreateDynamicPickup(1314, 24, fSpawnX, fSpawnY, fSpawnZ, fWorld, fInterior);

		for (new members; members < MAX_FAMILY_MEMBERS; members++) {
		    format(familyMembers[id][members], MAX_PLAYER_NAME, "Ninguem");
		}
		for (new veh; veh != MAX_FAMILY_CARS; veh++) {
		    familyVehInfo[id][veh][familyVehId]    = INVALID_VEHICLE_ID;
		    familyVehInfo[id][veh][familyVehModel] = -1;
  		}

		Family_Save( id );
	}
	return id;
}

stock Family_Save( id ) {
	if (Iter_Contains(IterFamily, id)) {

		if(familyInfo[id][familyID] == 0) {
			new date[20];
			TimeFormat(familyInfo[id][familyVencimento], MYSQL_TIMESTAMP, date);

			MySQL_Bind(stmt_createFamily, 0, familyInfo[id][familyName], true);
			MySQL_BindInt(stmt_createFamily, 1, familyInfo[id][familyLeaderID]);
			MySQL_Bind(stmt_createFamily, 2, "NULL", true);
			MySQL_BindFloat(stmt_createFamily, 3, familyInfo[id][familySpawn][0]);
			MySQL_BindFloat(stmt_createFamily, 4, familyInfo[id][familySpawn][1]);
			MySQL_BindFloat(stmt_createFamily, 5, familyInfo[id][familySpawn][2]);
			MySQL_BindFloat(stmt_createFamily, 6, familyInfo[id][familySpawn][3]);
			MySQL_BindInt(stmt_createFamily, 7, familyInfo[id][familyInterior]);
			MySQL_BindInt(stmt_createFamily, 8, familyInfo[id][familyWorld]);
			MySQL_BindInt(stmt_createFamily, 9, familyInfo[id][familyMoney]);
			MySQL_Bind(stmt_createFamily, 10, date, true);

			inline const OnLootCreated() {
				familyInfo[id][familyID] = cache_insert_id();
			}
			MySQL_ExecuteThreaded_Inline(stmt_createFamily, using inline OnLootCreated);
		}
		else {
			new date[20];
			TimeFormat(familyInfo[id][familyVencimento], MYSQL_TIMESTAMP, date);

			MySQL_Bind(stmt_updateFamily, 0, familyInfo[id][familyName], true);
			MySQL_BindInt(stmt_updateFamily, 1, familyInfo[id][familyLeaderID]);
			if(familyInfo[id][familySubLeaderID] != 0) {
				MySQL_BindInt(stmt_updateFamily, 2, familyInfo[id][familySubLeaderID]);
			}
			else {
				MySQL_Bind(stmt_updateFamily, 2, "NULL", true);
			}
			MySQL_BindFloat(stmt_updateFamily, 3, familyInfo[id][familySpawn][0]);
			MySQL_BindFloat(stmt_updateFamily, 4, familyInfo[id][familySpawn][1]);
			MySQL_BindFloat(stmt_updateFamily, 5, familyInfo[id][familySpawn][2]);
			MySQL_BindFloat(stmt_updateFamily, 6, familyInfo[id][familySpawn][3]);
			MySQL_BindInt(stmt_updateFamily, 7, familyInfo[id][familyInterior]);
			MySQL_BindInt(stmt_updateFamily, 8, familyInfo[id][familyWorld]);
			MySQL_BindInt(stmt_updateFamily, 9, familyInfo[id][familyMoney]);
			MySQL_Bind(stmt_updateFamily, 10, date, true);
			MySQL_BindInt(stmt_updateFamily, 11, familyInfo[id][familyID]);
			MySQL_ExecuteThreaded(stmt_updateFamily);
		}

		return 1;
	}
	return 0;
}

stock Family_SaveVehicle(familyid, vehicleID) {
	if (Iter_Contains(IterFamilyVehicles[familyid], vehicleID)) {

		if(familyVehInfo[familyid][vehicleID][familyVehDBID] == 0) {
			MySQL_BindInt(stmt_createFamilyVehicle, 0, familyInfo[familyid][familyID]);
			MySQL_BindInt(stmt_createFamilyVehicle, 1, familyVehInfo[familyid][vehicleID][familyVehModel]);
			for(new i = 0; i < 4; i++)
				MySQL_BindFloat(stmt_createFamilyVehicle, 2+i, familyVehInfo[familyid][vehicleID][familyVehPos][i]);

			inline const OnFamilyVehicleCreated() {
				familyVehInfo[familyid][vehicleID][familyVehDBID] = cache_insert_id();
			}
			MySQL_ExecuteThreaded_Inline(stmt_createFamilyVehicle, using inline OnFamilyVehicleCreated);
		}
		else {
			MySQL_BindInt(stmt_updateFamilyVehicle, 0, familyVehInfo[familyid][vehicleID][familyVehModel]);
			for(new i = 0; i < 4; i++)
				MySQL_BindFloat(stmt_updateFamilyVehicle, 1+i, familyVehInfo[familyid][vehicleID][familyVehPos][i]);

			MySQL_BindInt(stmt_updateFamilyVehicle, 2, familyInfo[familyid][familyID]);
			MySQL_ExecuteThreaded(stmt_updateFamilyVehicle);
		}
		return 1;
	}
	return 0;
}

stock Family_Destroy( id ) {
	if (Iter_Contains(IterFamily, id)) {

		Iter_Remove(IterFamily, id);

		DestroyDynamic3DTextLabel(familyInfo[id][familyLabel]);
		DestroyDynamicPickup(familyInfo[id][familyPickup]);

		MySQL_BindInt(stmt_destroyFamily, 0, familyInfo[id][familyID]);
		MySQL_ExecuteThreaded(stmt_destroyFamily);

		for (new veh; veh < MAX_FAMILY_CARS; veh++) {
		   	if (familyVehInfo[id][veh][familyVehModel] != -1) {
				new vehicleid = familyVehInfo[id][veh][familyVehId];
				VehicleInfo[vehicleid][vhType] = VH_TYPE_COMMON;
				VehicleInfo[vehicleid][vhInfoID] = 0;

		   	    DestroyVehicle(familyVehInfo[id][veh][familyVehId]);
		   	    familyVehInfo[id][veh][familyVehId] = INVALID_VEHICLE_ID;
		   	}
		}
		return 1;
	}
	return 0;
}

stock Family_LoadAll() {
	inline const OnLoadFamilies() {

		new 
			familyid,
			name[MAX_FAMILY_NAME],
			leaderName[MAX_PLAYER_NAME],
			leaderID,
			subleaderName[MAX_PLAYER_NAME],
			subleaderID,
			Float:pos[4],
			interior,
			world,
			money,
			dueDate[20]
        ;

		MySQL_BindResultInt(stmt_selectFamilies, 0, familyid);
		MySQL_BindResult(stmt_selectFamilies, 1, name, sizeof(name));
		MySQL_BindResult(stmt_selectFamilies, 2, leaderName, sizeof(leaderName));
		MySQL_BindResultInt(stmt_selectFamilies, 3, leaderID);
		MySQL_BindResult(stmt_selectFamilies, 4, subleaderName, sizeof(subleaderName));
		MySQL_BindResultInt(stmt_selectFamilies, 5, subleaderID);
		for(new i = 0; i < 4; i++) 
			MySQL_BindResultFloat(stmt_selectFamilies, 6+i, pos[i]);

        MySQL_BindResultInt(stmt_selectFamilies, 10, interior);
		MySQL_BindResultInt(stmt_selectFamilies, 11, world);
		MySQL_BindResultInt(stmt_selectFamilies, 12, money);
		MySQL_BindResult(stmt_selectFamilies, 13, dueDate, sizeof(dueDate));

		new row, string[75];
		while (MySQL_Statement_FetchRow(stmt_selectFamilies)) {
			new id = Iter_Free(IterFamily);

			Iter_Add(IterFamily, id);

			familyInfo[id][familyID] = familyid;

			format(familyInfo[id][familyName],   MAX_FAMILY_NAME, name);

			familyInfo[id][familyLeaderID] = leaderID;
			format(familyInfo[id][familyLeader], MAX_PLAYER_NAME, leaderName);

			if(MYSQL_IsNull(row, "subleader")) {
				familyInfo[id][familySubLeaderID] = 0;
				format(familyInfo[id][familySubLeader], MAX_PLAYER_NAME, "Ninguem");
			}
			else {
				familyInfo[id][familySubLeaderID] = subleaderID;
				format(familyInfo[id][familySubLeader], MAX_PLAYER_NAME, subleaderName);
			}

			for(new i = 0; i < 4; i++) 
				familyInfo[id][familySpawn][i] = pos[i];

			familyInfo[id][familyInterior] = interior;
			familyInfo[id][familyWorld]    = world;
			familyInfo[id][familyMoney]    = money;
			
			TimeParse(dueDate, ISO6801_DATE, familyInfo[id][familyVencimento]);

			format(string, sizeof string, "HQ da Família %s", name);
			familyInfo[id][familyLabel] = CreateDynamic3DTextLabel(string, 0xFFAA00FF, pos[0], pos[1], pos[2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world, interior);
			familyInfo[id][familyPickup] = CreateDynamicPickup(1314, 24, pos[0], pos[1], pos[2], world, interior);

			
			for(new m = 0; m < MAX_FAMILY_MEMBERS; m++) {
				familyMembers[id][m][familyMemberID] = 0;
				format(familyMembers[id][m][familyMemberName], MAX_PLAYER_NAME, "Ninguem");
			}

			for(new v = 0; v < MAX_FAMILY_CARS; v++) {
				familyVehInfo[id][v][familyVehId] = INVALID_VEHICLE_ID;
			}

			row += 1;
		}

		// Carregando membros da família
		inline const OnLoadFamilyMembers() {
			new memberID, memberName[MAX_PLAYER_NAME], previousFamilyid, id = -1;

			MySQL_BindResultInt(stmt_selectFamilyMembers, 0, memberID);
			MySQL_BindResultInt(stmt_selectFamilyMembers, 1, familyid);
			MySQL_BindResult(stmt_selectFamilyMembers, 2, memberName, sizeof(memberName));

			while (MySQL_Statement_FetchRow(stmt_selectFamilyMembers)) {

				if(previousFamilyid != familyid) {
					foreach(new f : IterFamily) {
						if(familyInfo[f][familyID] == familyid) {
							id = f;
							break;
						}
					}
					previousFamilyid = familyid;
				}
				
				if(id == -1)
					continue;

				new member = Iter_Free(IterFamilyMembers[id]);

				Iter_Add(IterFamilyMembers[id], member);

				familyMembers[id][member][familyMemberID] = memberID;
				format(familyMembers[id][member][familyMemberName], MAX_PLAYER_NAME, memberName);
			}
		}
		MySQL_ExecuteThreaded_Inline(stmt_selectFamilyMembers, using inline OnLoadFamilyMembers);

		// Carregando veículos da família
		inline const OnLoadFamilyVehicles() {
			new vehicleID, model, Float:vehiclePos[4], previousFamilyid, id = -1;

			MySQL_BindResultInt(stmt_selectFamilyVehicles, 0, vehicleID);
			MySQL_BindResultInt(stmt_selectFamilyVehicles, 1, familyid);
			MySQL_BindResultInt(stmt_selectFamilyVehicles, 2, model);
			for(new i = 0; i < 4; i++)
				MySQL_BindResultFloat(stmt_selectFamilyVehicles, 3+i, vehiclePos[i]);

			while (MySQL_Statement_FetchRow(stmt_selectFamilyVehicles)) {
				
				if(previousFamilyid != familyid) {
					foreach(new f : IterFamily) {
						if(familyInfo[f][familyID] == familyid) {
							id = f;
							break;
						}
					}
					previousFamilyid = familyid;
				}

				if(id == -1)
					continue;

				new vehicle = Iter_Free(IterFamilyVehicles[id]);

				Iter_Add(IterFamilyVehicles[id], vehicle);

				familyVehInfo[id][vehicle][familyVehDBID] = vehicleID;
				familyVehInfo[id][vehicle][familyVehModel] = model;
				for(new i = 0; i < 4; i++)
					familyVehInfo[id][vehicle][familyVehPos][i] = vehiclePos[i];
			}
		}
		MySQL_ExecuteThreaded_Inline(stmt_selectFamilyVehicles, using inline OnLoadFamilyVehicles);
		printf("[FAMÍLIAS]: %d famílias carregadas!", Iter_Count(IterFamily));
	}
    MySQL_ExecuteThreaded_Inline(stmt_selectFamilies, using inline OnLoadFamilies);
}

// stock Family_SpawnVehicles( id ) {
// 	for (new veh; veh < MAX_FAMILY_CARS; veh++) {

// 		if (familyVehInfo[id][veh][familyVehModel] != -1) {
//             familyVehInfo[id][veh][familyVehId] = AddStaticVehicleEx(
// 				familyVehInfo[id][veh][familyVehModel],
// 				familyVehInfo[id][veh][familyVehPos][0],
// 				familyVehInfo[id][veh][familyVehPos][1],
// 				familyVehInfo[id][veh][familyVehPos][2],
// 				familyVehInfo[id][veh][familyVehPos][3], 
// 				-1, -1, -1
// 			);
		
// 			new vehicleid = familyVehInfo[id][veh][familyVehId];
// 			VehicleInfo[vehicleid][vhType] = VH_TYPE_FAMILY;
// 			VehicleInfo[vehicleid][vhInfoID] = id;
// 		} else {
// 		    familyVehInfo[id][veh][familyVehId] = INVALID_VEHICLE_ID;
// 		}
// 	}
// }

stock Family_SetVehicle(id, slot, model, Float:cSpawnX, Float:cSpawnY, Float:cSpawnZ, Float:cSpawnA) {

	if (slot < 0 || slot >= MAX_FAMILY_CARS) return 0;

	Iter_Add(IterFamilyVehicles[id], slot);

 	familyVehInfo[id][slot][familyVehModel] = model;

    familyVehInfo[id][slot][familyVehPos][0] = cSpawnX;
    familyVehInfo[id][slot][familyVehPos][1] = cSpawnY;
    familyVehInfo[id][slot][familyVehPos][2] = cSpawnZ;
    familyVehInfo[id][slot][familyVehPos][3] = cSpawnA;

	if (familyVehInfo[id][slot][familyVehId] != INVALID_VEHICLE_ID) {
 		DestroyVehicle(familyVehInfo[id][slot][familyVehId]);
	}

	familyVehInfo[id][slot][familyVehId] = AddStaticVehicleEx(familyVehInfo[id][slot][familyVehModel],
	familyVehInfo[id][slot][familyVehPos][0],familyVehInfo[id][slot][familyVehPos][1],familyVehInfo[id][slot][familyVehPos][2],familyVehInfo[id][slot][familyVehPos][3], -1, -1, -1);
	
	new vehicleid = familyVehInfo[id][slot][familyVehId];
	VehicleInfo[vehicleid][vhType] = VH_TYPE_FAMILY;
	VehicleInfo[vehicleid][vhInfoID] = id;

	Family_SaveVehicle(id, slot);
	return 1;
}

stock Family_SetSpawn(id, Float:fSpawnX, Float:fSpawnY, Float:fSpawnZ, Float:fSpawnA=0.0, fInterior=0, fWorld=0) {
	if (Iter_Contains(IterFamily, id)) {

		familyInfo[id][familySpawn][0] = fSpawnX;
		familyInfo[id][familySpawn][1] = fSpawnY;
		familyInfo[id][familySpawn][2] = fSpawnZ;
		familyInfo[id][familySpawn][3] = fSpawnA;

		familyInfo[id][familyInterior] = fInterior;
		familyInfo[id][familyWorld]    = fWorld;

		DestroyDynamic3DTextLabel(familyInfo[id][familyLabel]);
		DestroyDynamicPickup(familyInfo[id][familyPickup]);

		new string[75];
		format(string, sizeof string, "HQ da Família %s", familyInfo[id][familyName]);
		familyInfo[id][familyLabel] = CreateDynamic3DTextLabel(string, 0xFFAA00FF, fSpawnX, fSpawnY, fSpawnZ, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, fWorld, fInterior);
		familyInfo[id][familyPickup]= CreateDynamicPickup(1314, 24, fSpawnX, fSpawnY, fSpawnZ, fWorld, fInterior);

		Family_Save( id );

		return 1;
	}
	return 0;
}

stock sendFamilyMsg(id, color, const fMessage[]) {

	if (Iter_Contains(IterFamily, id)) {

		foreach(new playerid : Player) {

		    if (GetPlayerFamily(playerid) == id) {
		        SendClientMessage(playerid, color, fMessage);
		    }
		}

		return 1;
	}
	return 0;
}

stock Family_AddMember( id, playerid ) {
	if (Iter_Contains(IterFamily, id)) {

		new index = Iter_Free(IterFamilyMembers[id]);
		if(index == -1)
			return 0;

		Iter_Add(IterFamilyMembers[id], index);

		format(familyMembers[id][index][familyMemberName], MAX_PLAYER_NAME, PlayerName[playerid]);
		familyMembers[id][index][familyMemberID] = Player_GetAccountID(playerid);
		SetPlayerFamily(playerid);

		MySQL_BindInt(stmt_createFamilyMember, 0, familyMembers[id][index][familyMemberID]);
		MySQL_BindInt(stmt_createFamilyMember, 1, familyInfo[id][familyID]);

		MySQL_ExecuteThreaded(stmt_createFamilyMember);
		return 1;
	}
	return 0;
}

stock Family_RemoveMember( id, playerid ) {
	if (Iter_Contains(IterFamily, id)) {

		new accountID = Player_GetAccountID(playerid),
			index = -1;

		if(familyInfo[id][familySubLeaderID] == accountID) {
			familyInfo[id][familySubLeaderID] = 0;
			format(familyInfo[id][familySubLeader], 24, "Ninguem");
			Family_Save(id);
			return 1;
		}
		
		foreach(new familyMember : IterFamilyMembers[id]) {
			if(familyMembers[id][familyMember][familyMemberID] == accountID) {
				index = familyMember;
				break;
			}
		}

		if(index == -1)
			return 0;

		format(familyMembers[id][index][familyMemberName], MAX_PLAYER_NAME, "Ninguem");
		familyMembers[id][index][familyMemberID] = 0;

		MySQL_BindInt(stmt_destroyFamilyMember, 0, accountID);
		MySQL_BindInt(stmt_destroyFamilyMember, 1, familyInfo[id][familyID]);

		MySQL_ExecuteThreaded(stmt_destroyFamilyMember);
		return 1;
	}
	return 0;
}

stock Family_RemoveMemberID( id, memberid ) {
	if (memberid < 0 || memberid >= MAX_FAMILY_MEMBERS) return 0;

	if (Iter_Contains(IterFamily, id)) {

		if (familyMembers[id][memberid][familyMemberID] == 0) {
		    return 0;
		}

		new accountID = familyMembers[id][memberid][familyMemberID];

		if (familyInfo[id][familySubLeaderID] == familyMembers[id][memberid][familyMemberID]) {
		    format(familyInfo[id][familySubLeader], 24, "Ninguem");
			familyInfo[id][familySubLeaderID] = 0;
			Family_Save(id);
		}

		format(familyMembers[id][memberid][familyMemberName], MAX_PLAYER_NAME, "Ninguem");
		familyMembers[id][memberid][familyMemberID] = 0;

		MySQL_BindInt(stmt_destroyFamilyMember, 0, accountID);
		MySQL_BindInt(stmt_destroyFamilyMember, 1, familyInfo[id][familyID]);

		MySQL_ExecuteThreaded(stmt_destroyFamilyMember);
	 	return 1;
	}
	return 0;
}

stock IsPlayerOwnerVehFamily(playerid, vehicleid) {

   	new id = GetVehicleFamily( vehicleid );

	if ( id == -1 ) return 0;

   	if ( GetPlayerFamily( playerid ) == id ) {
   	    return 1;
   	}

   	return 0;
}

stock GetVehicleFamily(vehicleid) {
	if (vehicleid == INVALID_VEHICLE_ID) 
		return -1;

	if(VehicleInfo[vehicleid][vhType] == VH_TYPE_FAMILY)
		return VehicleInfo[vehicleid][vhInfoID];

	return -1;
}

stock IsPlayerInRangeOfFamily(playerid, id, Float:range = 40.0) {
	if (Iter_Contains(IterFamily, id)) {

		if (IsPlayerInRangeOfPoint(playerid, range, familyInfo[id][familySpawn][0], familyInfo[id][familySpawn][1], familyInfo[id][familySpawn][2])) {
		    return 1;
		}
	}
	return 0;
}

stock Family_ShowCommands(playerid) {
	MEGAString[0] = EOS;

	strcat(MEGAString, "{00AAFF}Uso correto do comando: {FFFFFF}/familia [Nome]\n\n");
	strcat(MEGAString, "{AAAAAA}Nomes disponíveis:\n");
	strcat(MEGAString, "{00AAFF}• Ajuda:    \t{AAAAAA}Mostra os comandos da família\n");
	strcat(MEGAString, "{00AAFF}• Criar:    \t{AAAAAA}Usado para criar uma família\n");
	strcat(MEGAString, "{00AAFF}• DarSub:   \t{AAAAAA}Promove alguém para sub-lider\n");
	strcat(MEGAString, "{00AAFF}• Nome:     \t{AAAAAA}Trocar nome da família | {00FF00}5,000{AAAAAA} cash\n");
	strcat(MEGAString, "{00AAFF}• Info:     \t{AAAAAA}Usado para ver as informações da família\n");
	strcat(MEGAString, "{00AAFF}• Depositar:\t{AAAAAA}Para depositar dinheiro ao cofre da família\n");
	strcat(MEGAString, "{00AAFF}• Sacar:    \t{AAAAAA}Para sacar dinheiro do cofre da família\n");
	strcat(MEGAString, "{00AAFF}• Spawn:    \t{AAAAAA}Setar o local de spawn da família\n");
	strcat(MEGAString, "{00AAFF}• Carro:    \t{AAAAAA}Usado para comprar um carro para a família\n");
	strcat(MEGAString, "{00AAFF}• Convidar: \t{AAAAAA}Usado para convidar alguém para a família\n");
	strcat(MEGAString, "{00AAFF}• Expulsar: \t{AAAAAA}Usado para expulsar alguém da família\n");
	strcat(MEGAString, "{00AAFF}• Limpar:   \t{AAAAAA}Usado para limpar a vaga de um membro da família\n");
	strcat(MEGAString, "{00AAFF}• Destruir: \t{AAAAAA}Usado para destruir a família\n");
	strcat(MEGAString, "{00FF00}• Renovar: \t{AAAAAA}Novo comando para renovar família!\n");

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Comandos da família", MEGAString, "Fechar", "");
	
	return true;
}

stock Family_ShowInfo( playerid, id , bool:infoOnly = true ) {
	if (Iter_Contains(IterFamily, id)) {

	    new string[128];
	    MEGAString[0] = EOS;

		new idleader = GetPlayerID(familyInfo[id][familyLeader]);
		new idsubleader = GetPlayerID(familyInfo[id][familySubLeader]);
		new date[15];

		TimeFormat(familyInfo[id][familyVencimento], "%d/%m/%Y", date);

	    format(string, sizeof string, "{00AAFF}\t\tFamília: {FFFFFF}%s\n\n", familyInfo[id][familyName]);
	    strcat(MEGAString, string);
	    format(string, sizeof string, "{00AAFF}Líder da família: {FFFFFF}%s %s\n", familyInfo[id][familyLeader], Player_Logado(idleader) ? ("{00AA00}[Online]") : ("{AAAAAA}[Offline]"));
	    strcat(MEGAString, string);
	    format(string, sizeof string, "{00AAFF}Sub-Líder da família: {FFFFFF}%s %s\n\n", familyInfo[id][familySubLeader], Player_Logado(idsubleader) ? ("{00AA00}[Online]") : ("{AAAAAA}[Offline]"));
	    strcat(MEGAString, string);
	    format(string, sizeof string, "{00AAFF}Spawn da família: {FFFFFF}%.4f, %.4f, %.4f\n", familyInfo[id][familySpawn][0], familyInfo[id][familySpawn][1], familyInfo[id][familySpawn][2]);
	    strcat(MEGAString, string);
	    format(string, sizeof string, "{00AAFF}Interior: {FFFFFF}%d\n", familyInfo[id][familyInterior]);
	    strcat(MEGAString, string);
	    format(string, sizeof string, "{00AAFF}World: {FFFFFF}%d\n", familyInfo[id][familyWorld]);
	    strcat(MEGAString, string);
	    format(string, sizeof string, "{00AAFF}Dinheiro: {FFFFFF}$%s\n", getFormatText(familyInfo[id][familyMoney]));
	    strcat(MEGAString, string);
	    format(string, sizeof string, "{00AAFF}Vencimento: {FFFFFF}%s (%d dias)\n\n", date, TimestampToRemainingDays(familyInfo[id][familyVencimento]));
	    strcat(MEGAString, string);

	    strcat(MEGAString, "{AAAAAA}Carros da família:\n");

		new vehicle_name[30];
		for (new veh; veh < MAX_FAMILY_CARS; veh++) {
			GetModelStaticNameFromId(familyVehInfo[id][veh][familyVehModel], vehicle_name);

			if (familyVehInfo[id][veh][familyVehModel] != -1) {

	    		format(string, sizeof string, "{00AAFF}Veículo %d: {FFFFFF}%s\n", veh + 1, vehicle_name);
	    		strcat(MEGAString, string);
	        } else {

	    		format(string, sizeof string, "{00AAFF}Veículo %d: {FFFFFF}Nenhum\n", veh + 1);
	    		strcat(MEGAString, string);
	        }
		}

	    strcat(MEGAString, "\n{AAAAAA}Membros da família:\n");

		new idmember;

		for (new members; members < MAX_FAMILY_MEMBERS; members++) {

			idmember = GetPlayerID(familyMembers[id][members][familyMemberName]);

	    	format(
				string, sizeof string, "%s\t{00AAFF}Vaga %02d: {FFFFFF}%s\n", 
				Player_Logado(idmember) ? ("{00AA00}[Online]") : ("{AAAAAA}[Offline]"), 
				members + 1, 
				familyMembers[id][members][familyMemberName]
			);
	    	strcat(MEGAString, string);
		}

		if (infoOnly) {
			ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Informações da família", MEGAString, "Fechar", "");
		} else {
		    ShowPlayerDialog(playerid, 250, DIALOG_STYLE_MSGBOX, "Informações da família", MEGAString, "Localizar HQ", "Voltar");
		}
		return 1;
	}
	return 0;
}

stock GetPlayerFamily(playerid) {
	return PlayerInfo[playerid][pFamily];
}

stock GetPlayerFamilyName(playerid) {
	new familyid = PlayerInfo[playerid][pFamily], name[64];
	if(familyid != -1) {
		format(name, sizeof(name), familyInfo[familyid][familyName]);
	}
	else {
		format(name, sizeof(name), "Nenhuma");
	}
	return name;
}

stock SetPlayerFamily(playerid) {
	new accountID = Player_GetAccountID(playerid);
	foreach(new id : IterFamily) {

	    if (familyInfo[id][familyLeaderID] == accountID || familyInfo[id][familySubLeaderID] == accountID) {
	        PlayerInfo[playerid][pFamily] = id;
			return 1;
	    }

		foreach(new familyMember : IterFamilyMembers[id]) {
			if(familyMembers[id][familyMember][familyMemberID] == accountID) {
				PlayerInfo[playerid][pFamily] = id;
				return 1;
			}
		}
	}
	PlayerInfo[playerid][pFamily] = -1;
	return 1;
}

stock DoesFamilyExist(const familynome[]) {
	foreach(new id : IterFamily) {
	    if (!strcmp(familynome, familyInfo[id][familyName], true)) 
			return 1;
	}
	return 0;
}

stock Family_ListVehicles( playerid, id ) {

	if (Iter_Contains(IterFamily, id)) {

		new string[75];
		MEGAString[0] = EOS;

		strcat(MEGAString, "Veículo\tNome\tCusto de compra/troca\n");

		new vehicle_name[30];
		for (new veh; veh < MAX_FAMILY_CARS; veh++) {
			GetModelStaticNameFromId(familyVehInfo[id][veh][familyVehModel], vehicle_name);

			if (familyVehInfo[id][veh][familyVehModel] != -1) {

	    		format(string, sizeof string, "{00AAFF}Veículo %d:\t{FFFFFF}%s\t{00AA00}$100.000\n", veh + 1, vehicle_name);
	    		strcat(MEGAString, string);
	        } else {

	    		format(string, sizeof string, "{00AAFF}Veículo %d:\t{FFFFFF}Nenhum\t{00AA00}$5.000.000\n", veh + 1);
	    		strcat(MEGAString, string);
	        }
		}
		ShowPlayerDialog(playerid, 9252, DIALOG_STYLE_TABLIST_HEADERS, "Escolha um slot para comprar/trocar de carro", MEGAString, "Selecionar", "Fechar");

		return 1;
	}
	return 0;
}

stock ListFamilies( playerid ) {
	new string[128];
	MEGAString[0] = EOS;

	new familyid;

	strcat(MEGAString, "Id  Nome da família\tLíder da família\tStatus\n");

	new idleader;

	foreach(new id : IterFamily) {

		idleader = GetPlayerID(familyInfo[id][familyLeader]);

	    format(string, sizeof string, "%02d  %s\t%s\t%s\n", id, familyInfo[id][familyName], familyInfo[id][familyLeader], Player_Logado(idleader) ? ("{00AA00}Online") : ("{AAAAAA}Offline"));
	    strcat(MEGAString, string);

	    SelectFamily[playerid][familyid] = id;
	    familyid ++;
	}

	if (familyid) {
	    ShowPlayerDialog(playerid, 9842, DIALOG_STYLE_TABLIST_HEADERS, " Famílias do servidor", MEGAString, "Informações", "Fechar");
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTRED, "* Nenhuma família foi criada no servidor!");
	}
}

stock IsPlayerOwnerFamily( playerid, id ) {
	if (Iter_Contains(IterFamily, id) && familyInfo[id][familyLeaderID] == Player_GetAccountID(playerid)) {
		return 1;
	}
	return 0;
}

stock IsPlayerOwnerFamilyEx( playerid, id ) {

	if (Iter_Contains(IterFamily, id)) {

		if(familyInfo[id][familySubLeaderID] == Player_GetAccountID(playerid)) {
		    return 1;
		}

		if(familyInfo[id][familyLeaderID] == Player_GetAccountID(playerid)) {
		    return 1;
		}
	}
	return 0;
}

stock SetPlayerToFamilySpawn( playerid, id ) {
	if (Iter_Contains(IterFamily, id)) {

		SetPlayerPos(playerid, familyInfo[id][familySpawn][0], familyInfo[id][familySpawn][1], familyInfo[id][familySpawn][2]);
		SetPlayerFacingAngle(playerid, familyInfo[id][familySpawn][3]);
		SetPlayerInterior(playerid, familyInfo[id][familyInterior]);
		SetPlayerVirtualWorld(playerid, familyInfo[id][familyWorld]);

		return 1;
	}
	return 0;
}

CMD:familias(playerid) {
    ListFamilies( playerid );
	return 1;
}

CMD:familia(playerid, params[]) {
	if (isnull(params)) 
		return Family_ShowCommands(playerid);

	new string[128],
		null[75];
		
	new Float:x, Float:y, Float:z, Float:ang;

 	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, ang);

	if (strfind(params, "ajuda", true) != -1)
	{
        Family_ShowCommands(playerid);
	}
	else if (strfind(params, "criar", true) != -1)
	{
	    if (!GetPVarInt(playerid, "FamilyAutorizado"))
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não tem autorização para criar família.");

	    new familyname[MAX_FAMILY_NAME];
	    if(sscanf(params, "s[75]s[24]", null, familyname))
	        return SendClientMessage(playerid, -1, "Modo de uso: /familia criar (nome da familia)");

	    if (strlen(familyname) >= MAX_FAMILY_NAME)
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "Você deve escolher um nome de família entre 5 á 24 caracteres.");

	    if (DoesFamilyExist(familyname)) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Já existe uma família com o mesmo nome!");
	    }

	    if (IsPlayerInSafeZone(playerid)) 
			return SendClientMessage(playerid, -1, "Você não pode fazer isso em uma Área Segura.");

		new idf = GetPlayerFamily( playerid );

		if ( idf != -1 ) {
		    return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você já pertence a uma família!");
		}

	    new id = Family_Create(familyname, x, y, z, ang, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), playerid);

		if(id != -1) 
		{
		    format(string, sizeof string, "* Você criou a família %s, use /ajudafamilia para saber os comandos!", familyname);
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

		    format(string, sizeof string, "[Famílias] %s criou uma família chamada '%s', use /familias para mais informações!", PlayerName[playerid], familyname);
		    SendClientMessageToAll(0xFFAAAAFF, string);

		    SetPVarInt(playerid, "FamilyAutorizado", 0);

		    // LOGS
		    format(string, sizeof string, "%s criou a familia %s", PlayerName[playerid], familyname);
		    server_log("family", string);

			SetPlayerFamily(playerid);
		}
		else 
		{
		    SendClientMessage(playerid, COLOR_LIGHTRED, "O limite de família no servidor foi atingido!");
		}
	}
	else if (strfind(params, "Nome", true) != -1) {

        new nomefamily[MAX_FAMILY_NAME],
			idf = GetPlayerFamily(playerid);
        
        if (!IsPlayerOwnerFamily(playerid, idf)) return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não é o líder/sub da família.");

	    if (Player_GetCash(playerid) < 5000) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você precisa ter 5.000 cash para trocar nome da família.");

	    if(sscanf(params, "s[75]s[24]", null, nomefamily)) return SendClientMessage(playerid, 0xBBBBBBFF, "Modo de uso: /familia nome (novo nome da familia)");

	    if (strlen(nomefamily) >= MAX_FAMILY_NAME) return SendClientMessage(playerid, COLOR_LIGHTRED, "* O nome da família está muito grande!");

	    if (DoesFamilyExist(nomefamily)) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Já existe uma família com o mesmo nome!");
		
		format(familyInfo[idf][familyName], MAX_FAMILY_NAME, nomefamily);

		format(string, sizeof string, "HQ da Família %s", nomefamily);
		UpdateDynamic3DTextLabelText(familyInfo[idf][familyLabel], 0xFFAA00FF, string);
		
		Player_RemoveCash(playerid, 5000);
		
		format(string, sizeof string, "*(( %s mudou o nome da família para %s ))*", PlayerName[playerid], nomefamily);
	    sendFamilyMsg(idf, 0xFFAAAAFF, string), server_log("family", string);
	    
	    Family_Save(idf);
	}
	else if (strfind(params, "Info", true) != -1) {

		new id = GetPlayerFamily( playerid );

		if ( id != -1 ) {

		    Family_ShowInfo( playerid, id );
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
		}
	}
	else if (strfind(params, "Spawn", true) != -1) {

		new id = GetPlayerFamily( playerid );

		if ( id != -1 ) {

			if (IsPlayerOwnerFamily( playerid, id )) 
			{
			    if (IsPlayerInSafeZone(playerid)) 
					return SendClientMessage(playerid, -1, "Você não pode fazer isso em uma Área Segura.");

				Family_SetSpawn(id, x, y, z, ang, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

			    format(string, sizeof string, "* O novo spawn da família será aqui!");
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

			    format(string, sizeof string, "Spawn: %.4f | %.4f | %.4f | Interior: %d | World: %d", x, y, z, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
			    SendClientMessage(playerid, TEAM_GROVE_COLOR, string);

			    // LOGS
			    format(string, sizeof string, "[%s] %s setou o spawn da familia: %.4f | %.4f | %.4f", familyInfo[id][familyName], PlayerName[playerid], x, y, z);
			    server_log("family", string);

			} else {
			    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o líder da família pode usar este comando!");
			}
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
		}
	}
	else if (strfind(params, "Carro", true) != -1) {

		new id = GetPlayerFamily( playerid );

	  	if (GetPlayerInterior(playerid) != 0) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode usar este comando aqui!");
	    }

		if ( id != -1 ) {

			if (IsPlayerOwnerFamily( playerid, id )) {

			    SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Escolha um carro para comprar para a família.");
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, "OBS1: O veículo custa $5.000.000, o dinheiro gasto não será reembolsado!");
                SendClientMessage(playerid, COLOR_LIGHTBLUE, "OBS2: Ao ser comprado/trocado, o veículo irá sempre nascer na sua posição atual!");

                Family_ListVehicles( playerid, id );

			} else {
			    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o líder da família pode usar este comando!");
			}
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
		}
	}
	else if (strfind(params, "Convidar", true) != -1) {

		new idPlayer;
	    if(sscanf(params, "s[75]u", null, idPlayer)) {
	        return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /familia Convidar [playerid]");
	    }

	    if(!IsPlayerConnected(idPlayer)) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* O jogador não está conectado!");
	    }

	    if (GetPlayerFamily( idPlayer ) != -1) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Este jogador já participa de uma família!");
	    }

		new id = GetPlayerFamily( playerid );

		if ( id != -1 ) {

			if (IsPlayerOwnerFamilyEx( playerid, id )) {

			    format(string, sizeof string, "* Você convidou %s para participar da sua família, aguarde uma resposta do mesmo!", PlayerName[idPlayer]);
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

			    format(string, sizeof string, "* %s convidou você para participar da família %s, use /aceitarfamilia para aceitar!", PlayerName[playerid], familyInfo[id][familyName]);
			    SendClientMessage(idPlayer, COLOR_LIGHTBLUE, string);

			    SetPVarInt(idPlayer, "familyAcc", id);

			    // LOGS
			    format(string, sizeof string, "[%s] %s convidou %s", familyInfo[id][familyName], PlayerName[playerid], PlayerName[idPlayer]);
			    server_log("family", string);
			} else {
			    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o líder da família pode usar este comando!");
			}
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
		}
	}
	else if (strfind(params, "DarSub", true) != -1) {

		new idPlayer;
	    if(sscanf(params, "s[75]u", null, idPlayer)) {
	        return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /familia DarSub [playerid]");
	    }

	    if(!IsPlayerConnected(idPlayer)) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* O jogador não está conectado!");
	    }

	    if (GetPlayerFamily( idPlayer ) != GetPlayerFamily( idPlayer )) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Este jogador não participa da sua família!");
	    }

		new id = GetPlayerFamily( playerid );

		if ( id != -1 ) {

			if (IsPlayerOwnerFamily( playerid, id )) {

			    format(string, sizeof string, "* Você promoveu %s para sub-lider da família!", PlayerName[idPlayer]);
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

			    format(string, sizeof string, "* %s promoveu você para sub-lider da família %s!", PlayerName[playerid], familyInfo[id][familyName]);
			    SendClientMessage(idPlayer, COLOR_LIGHTBLUE, string);

			    format(familyInfo[id][familySubLeader], 24, PlayerName[idPlayer]);
				familyInfo[id][familySubLeaderID] = Player_GetAccountID(idPlayer);

                Family_Save( id );

			    // LOGS
			    format(string, sizeof string, "[%s] %s deu sub para %s", familyInfo[id][familyName], PlayerName[playerid], PlayerName[idPlayer]);
			    server_log("family", string);

				SetPlayerFamily(idPlayer);
			} else {
			    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o líder da família pode usar este comando!");
			}
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
		}
	}
	else if (strfind(params, "Expulsar", true) != -1) {

		new idPlayer;
	    if(sscanf(params, "s[75]u", null, idPlayer)) {
	        return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /familia Expulsar [playerid]");
	    }

	    if(!IsPlayerConnected(idPlayer)) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* O jogador não está conectado!");
	    }

		new id = GetPlayerFamily( playerid );

	    if (GetPlayerFamily( idPlayer ) != id) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Este jogador é de uma família diferente da sua!");
	    }

	    if (idPlayer == playerid) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode expulsar você mesmo, use /familia destruir!");
	    }

		if ( id != -1 ) {

			if (IsPlayerOwnerFamily( playerid, id )) {

			    format(string, sizeof string, "* Você expulsou %s da sua família!", PlayerName[idPlayer]);
			    SendClientMessage(playerid, COLOR_LIGHTRED, string);

			    format(string, sizeof string, "* %s expulsou você da família %s!", PlayerName[playerid], familyInfo[id][familyName]);
			    SendClientMessage(idPlayer, COLOR_LIGHTRED, string);

				Family_RemoveMember( id, idPlayer);

				SetPlayerFamily(idPlayer);

			    // LOGS
			    format(string, sizeof string, "[%s] %s expulsou %s", familyInfo[id][familyName], PlayerName[playerid], PlayerName[idPlayer]);
			    server_log("family", string);
			} else {
			    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o líder da família pode usar este comando!");
			}
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
		}
	}
	else if (strfind(params, "Limpar", true) != -1) {

		new idPlayer;
	    if(sscanf(params, "s[75]d", null, idPlayer)) {
	        return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /familia Limpar [Vaga ID]");
	    }

		new id = GetPlayerFamily( playerid );

		if ( id != -1 ) {

			if (IsPlayerOwnerFamily( playerid, id )) {

				new playerName[MAX_PLAYER_NAME];
				format(playerName, MAX_PLAYER_NAME, familyMembers[id][idPlayer-1][familyMemberName]);

				if (!Family_RemoveMemberID( id, idPlayer-1 )) {
				    return SendClientMessage(playerid, COLOR_LIGHTRED, "* Houve um erro ao tentar limpar essa vaga, verifique se já está limpa ou se ela existe!");
				}

			    format(string, sizeof string, "* Você limpou a vaga nº %d, que era de %s.", idPlayer, playerName);
			    SendClientMessage(playerid, COLOR_LIGHTRED, string);

			    // LOGS
			    format(string, sizeof string, "[%s] %s limpou a vaga %d", familyInfo[id][familyName], PlayerName[playerid], idPlayer);
			    server_log("family", string);

				new idmember = GetPlayerID(playerName);

				if (Player_Logado(idmember)) {

			    	format(string, sizeof string, "* %s expulsou você da família %s!", PlayerName[playerid], familyInfo[id][familyName]);
			    	SendClientMessage(idmember, COLOR_LIGHTRED, string);
					SetPlayerFamily(idPlayer);
				}
			} else {
			    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o líder da família pode usar este comando!");
			}
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
		}
	}

	else if (strfind(params, "depositar", true) != -1) {

		new value;
	    if(sscanf(params, "s[75]d", null, value)) {
	        return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /familia Depositar [Valor]");
	    }

	    if (value < 20000 || value > 5000000) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Valor mínimo 20.000 e máximo 5.000.000!");
	    }

	    if (Player_GetMoney(playerid) < value)
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não tem esse dinheiro todo!");

		new id = GetPlayerFamily( playerid );

		if ( id != -1 ) {

		  	format(string, sizeof string, "* Você depositou $%s no cofre da família.", getFormatText(value));
	    	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

			Player_RemoveMoney(playerid, value);
			familyInfo[id][familyMoney] += value;

			Family_Save( id );

		    // LOGS
		    format(string, sizeof string, "[%s] %s depositou $%d", familyInfo[id][familyName], PlayerName[playerid], value);
		    server_log("family", string);

		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
		}
	}

	else if (strfind(params, "sacar", true) != -1) {

		new valuefamily;
	    if(sscanf(params, "s[75]d", null, valuefamily)) {
	        return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /familia Sacar [Valor]");
	    }

        new id = GetPlayerFamily( playerid );

	    if (familyInfo[id][familyMoney] < valuefamily) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* A família não tem esse dinheiro todo!");
	    }
		else if (valuefamily <= 0 || valuefamily > 5000000) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Valor mínimo 1 e máximo 5.000.000!");
	    }

		if ( id != -1 ) {

			if (IsPlayerOwnerFamily( playerid, id )) {

				format(string, sizeof string, "* Você sacou $%s do cofre da família!", getFormatText(valuefamily));
                SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

				Player_AddMoney(playerid, valuefamily);
				familyInfo[id][familyMoney] -= valuefamily;

				Family_Save( id );

			    // LOGS
			    format(string, sizeof string, "[%s] %s sacou $%d", familyInfo[id][familyName], PlayerName[playerid], valuefamily);
			    server_log("family", string);
			} else {
			    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o líder da família pode usar este comando!");
			}
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
		}
	}
	
	else if (strfind(params, "Renovar", true) != -1) {

		new id = GetPlayerFamily( playerid );

		if ( id != -1 ) {

		    if (IsPlayerOwnerFamilyEx( playerid, id )) {

			    MEGAString[0] = EOS;

			    strcat(MEGAString, "\n{FFF000}>>			{FFFFFF}Renovação de família (+30 dias)			{FFF000}<<\n\n");

			    strcat(MEGAString, "{FFFFFF}* Caso queira renovar família com 15 trocas de nick use: {00FFFF}''{00FF00}TROCAS{00FFFF}'' (40.000 de cash)\n");

				strcat(MEGAString, "{FFFFFF}* Caso queira renovar a família sem as trocas de nick use: {00FFFF}''{00FF00}SEM-TROCAS{00FFFF}'' (20.000 de cash)\n\n");

				strcat(MEGAString, "{FF6347}OBS: {B4B5B7}Não fazemos devolução caso confirme a compra!\n");

				ShowPlayerDialog(playerid, 7765, DIALOG_STYLE_INPUT, "{FFFFFF} » {00FFFF}CASH » {FFFFFF}Transferir Cash !", MEGAString, "Continuar", "");

			} else {
			    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o líder ou sub-líder família pode usar este comando!");
			}
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
		}

		Family_Save( id );
	}

	else if (strfind(params, "Destruir", true) != -1) {

		new id = GetPlayerFamily( playerid );

		if ( id != -1 ) {

			if (IsPlayerOwnerFamily( playerid, id )) {

				format(string, sizeof string, "* Você destruiu a família '%s', todas as informações da mesma foram deletadas!", familyInfo[id][familyName]);
                SendClientMessage(playerid, COLOR_LIGHTRED, string);

        		Family_Destroy( id );

			    // LOGS
			    format(string, sizeof string, "[%s] %s destruiu a familia", familyInfo[id][familyName], PlayerName[playerid]);
			    server_log("family", string);
			} else {
			    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o líder da família pode usar este comando!");
			}
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a uma família!");
		}

	} else {
	    Family_ShowCommands(playerid);
	}

	return 1;
}

CMD:anf(playerid, params[]) {
    new id = GetPlayerFamily(playerid), string[128];
    if (!IsPlayerOwnerFamilyEx( playerid, id )) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    if (isnull(params)) return SendClientMessage(playerid, -1, "Modo de uso: /anorg (texto de anúncio)");
    
    if (strlen(params) < 16 || strlen(params) > 86) return SendClientMessage(playerid, -1, "O anúncio da família deve conter entre 16 á 86 caracteres.");
	
    format(string, sizeof string, "  »             Anúncio de %s	| Família: %s             «  ", PlayerName[playerid], familyInfo[id][familyName]);
    SendClientMessageToAll(0xFFAAAAFF, string);
    format(string, sizeof string, "%s", params), server_log("anf", string);
    SendClientMessageToAll(-1, string);
    SendClientMessageToAll(0xFFAAAAFF, "_____________________________________________________________________________________________________");
    return 1;
}

CMD:irfamilia(playerid, params[]) {
	if (!Admin_GetNivel(playerid)) {
		return SendClientMessage(playerid, -1, "* Você não está autorizado a usar este comando!");
	}

	new idfam;

	if (sscanf(params, "d", idfam)) {
		return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /irfamilia [id]");
	}

	if (idfam < 0 || idfam >= MAX_FAMILYS) {
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "* Família Inválida!");
	}

	if (!Iter_Contains(IterFamily, idfam)) {
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "* Família Inválida!");
	}

	SetPlayerPos(playerid, familyInfo[idfam][familySpawn][0], familyInfo[idfam][familySpawn][1], familyInfo[idfam][familySpawn][2]);
	SetPlayerInterior(playerid, familyInfo[idfam][familyInterior]);
	SetPlayerVirtualWorld(playerid, familyInfo[idfam][familyWorld]);
	SendClientMessage(playerid, COLOR_LIGHTGREEN, " Você foi teleportado até a família!");

	return 1;
}

CMD:autorizarf(playerid, params[]) {
	if (Admin_GetNivel(playerid) < SUB_DONO) {
		return SendClientMessage(playerid, -1, "* Você não está autorizado a usar este comando!");
	}

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) {
		return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /autorizarf [playerid]");
	}

	if (!IsPlayerConnected(idPlayer)) {
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "* O jogador não está conectado!");
	}

	new string[128];
	format(string, sizeof string, "* Você autorizou %s a criar uma família!", PlayerName[idPlayer]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	format(string, sizeof string, "* O admin %s autorizou você a criar uma família, use '/familia criar' para mais informações!", PlayerName[playerid]);
	SendClientMessage(idPlayer, COLOR_LIGHTBLUE, string);

	SetPVarInt(idPlayer, "FamilyAutorizado", 1);

    format(string, sizeof string, "Admin %s autorizou %s a criar uma família", PlayerName[playerid], PlayerName[idPlayer]);
    server_log("family", string);

	return 1;
}

CMD:destruirfamilia(playerid, params[]) {
	if (Admin_GetNivel(playerid) < DONO) {
		return SendClientMessage(playerid, -1, "* Você não está autorizado a usar este comando!");
	}

	new idfam;

	if (sscanf(params, "d", idfam)) {
		return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /destruirfamila [id]");
	}

	if (idfam < 0 || idfam >= MAX_FAMILYS) {
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "* Família Inválida!");
	}

	if (!Iter_Contains(IterFamily, idfam)) {
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "* Família Inválida!");
	}

	new string[128];

	format(string, sizeof string, "[Famílias] O administrador %s destruiu a família '%s'", PlayerName[playerid], familyInfo[idfam][familyName]);
	SendClientMessageToAll(0xFFAAAAFF, string);

	Family_Destroy( idfam );

    format(string, sizeof string, "Admin %s destruiu a familia %s", PlayerName[playerid], familyInfo[idfam][familyName]);
    server_log("family", string);

	return 1;
}

CMD:vencimentofamilia(playerid, params[]) {
	if (Admin_GetNivel(playerid) < SUB_DONO) {
		return SendClientMessage(playerid, -1, "* Você não está autorizado a usar este comando!");
	}

	new idfam, quantidade;

	if (sscanf(params, "dd", idfam, quantidade)) {
		return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /vencimentofamilia [id] [dias]");
	}

	if (idfam < 0 || idfam >= MAX_FAMILYS) {
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "* Família Inválida!");
	}

	if (!Iter_Contains(IterFamily, idfam)) {
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "* Família Inválida!");
	}

	new string[128];

	format(string, sizeof string, "[Famílias] O administrador %s setou vencimento da família '%s' para %d dias.", PlayerName[playerid], familyInfo[idfam][familyName], quantidade);
	SendClientMessageToAll(0xFFAAAAFF, string);

	familyInfo[idfam][familyVencimento] = Now() + Days:quantidade;
	
	Family_Save( idfam );

	return 1;
}

CMD:donofamilia(playerid, params[]) {
	if (Admin_GetNivel(playerid) < SUB_DONO) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new idfam, namePlayer[MAX_PLAYER_NAME];
	if (sscanf(params, "ds[24]", idfam, namePlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /donofamilia (id da família) (nome do jogador)");

	if (idfam < 0 || idfam >= MAX_FAMILYS) return SendClientMessage(playerid, -1, "O id da família digitado é inválido ou não existe.");

	if (!Iter_Contains(IterFamily, idfam)) return SendClientMessage(playerid, -1, "O id da família digitado não existe no servidor.");

	new accountid = Player_GetAccountIDByNick(namePlayer);
	if(accountid == -1) {
		return SendClientMessage(playerid, -1, "Não há uma conta cadastrada com esse nick");
	}

	new string[128];

	format(string, sizeof string, "[FAMÍLIAS] %s, %s setou dono da família '%s' para %s.", Staff_GetPositionName(playerid), PlayerName[playerid], familyInfo[idfam][familyName], namePlayer);
	SendClientMessageToAll(0xFFAAAAFF, string);

	familyInfo[idfam][familyLeaderID] = accountid;
	format(familyInfo[idfam][familyLeader], MAX_PLAYER_NAME, namePlayer);
	Family_Save(idfam);
	return true;
}

CMD:aceitarfamilia(playerid) 
{
	new id = GetPVarInt(playerid, "familyAcc");
	if (id == -1)
		return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não foi convidado para nenhuma família!");

	SetPVarInt(playerid, "familyAcc", -1);

	new string[144];

	if (!Family_AddMember(id, playerid))
		return SendClientMessage(playerid, COLOR_LIGHTRED, "* Não há mais vagas nesta família!");

	format(string, sizeof string, "* Parabéns, você acaba de entrar para a família '%s', use /ajudafamilia para saber os comandos!", familyInfo[id][familyName]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

	format(string, sizeof string, " %s @ %s acaba de entrar para a família. Dê as boas-vidas a ele!", familyInfo[id][familyName], PlayerName[playerid]);
	sendFamilyMsg(id, 0xFFAAAAFF, string);

	format(string, sizeof string, "%s entrou pra familia %s", PlayerName[playerid], familyInfo[id][familyName]);
	server_log("family", string);

	return 1;
}

CMD:sairfamilia(playerid) {
	new id = GetPlayerFamily( playerid );

	if ( id != -1 ) {

		if (IsPlayerOwnerFamily( playerid, id )) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode sair da família pois é o líder, use /familia destruir!");
		}

	    new string[144];

	    format(string, sizeof string, "* Você acaba de sair da família '%s'", familyInfo[id][familyName]);
	    SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

	    format(string, sizeof string, " %s @ %s saiu da família!", familyInfo[id][familyName], PlayerName[playerid]);
	    sendFamilyMsg( id , 0xFFAAAAFF, string);

	    Family_RemoveMember( id, playerid);

	    format(string, sizeof string, "%s saiu da familia %s", PlayerName[playerid], familyInfo[id][familyName]);
	    server_log("family", string);

	} else {
	    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
	}
	return 1;
}

//#define "systems/familia/family_spawn.inc"

stock Player_SpawnInFamily(playerid) {
    new id = GetPlayerFamily(playerid);

    if (id != -1) {
        SetPlayerToFamilySpawn(playerid, id);
    } else {
        SendClientMessage(playerid, COLOR_LIGHTRED, "Você não faz mais parte de uma família!");
        Player_SetSpawnType(playerid, TYPE_SPAWN_DEFAULT);
    }
}