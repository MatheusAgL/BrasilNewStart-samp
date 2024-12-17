#include <YSI_Coding\y_hooks>

#define MAX_VEHICLE_ACCESSORIES 10

enum pVehicleEnum {
	pvDBID,
	pvID,
	pvModel,
	pvPrice,
	pvFuel,
	pvParked,
	pvInsurance,
	Timestamp:pvDueDate,
	pvExpenses,
	pvPlate[25],
	pvText[55],
	Float:pvPos[4],
	Float:pvHealth,
	pvMaxAccessories,
	pvColor[2],
	pvComponent[15],
	Float:pvLastPos[4],
	bool:pvPanels,
	bool:pvDoors,
	bool:pvLights,
	bool:pvTires
}
new PlayerVehicleInfo[MAX_PLAYERS][MAX_PLAYER_CARROS][pVehicleEnum];

new Iterator:IterPlayerVehicles[MAX_PLAYERS]<MAX_PLAYER_CARROS>;

/*enum pVehicleAccessoryEnum {
	pvaID,
	pvaModel,
	pvaRemovable,
	Float:pvaOffset[3],
	Float:pvaRotation[3],
	pvaName[75],
	pvaObjectID
}
new VehicleAccessoryInfo[MAX_VEHICLES][MAX_VEHICLE_ACCESSORIES][pVehicleAccessoryEnum];

new Iterator:IterPVAccessories[MAX_VEHICLES]<MAX_VEHICLE_ACCESSORIES>;*/

//Statements
static 
	Statement: stmt_selectVehicles,
	Statement: stmt_createVehicle,
	Statement: stmt_updateVehicle,
	Statement: stmt_destroyVehicle,
	// Statement: stmt_selectVehicleAccessories,
	// Statement: stmt_createVehicleAccessory,
	// Statement: stmt_updateVehicleAccessory,
	// Statement: stmt_destroyVehicleAccessory,
	Statement: stmt_updateVehiclePart
;

hook OnMySQLConnected() {
	stmt_selectVehicles = MySQL_PrepareStatement(MySQL_Handle, "SELECT \
            id, model, pos_x, pos_y, pos_z, angle, color_1, color_2, price, fuel, health, parked, insurance, max_accessories, \
            due_date, expenses, plate, `text`, last_pos_x, last_pos_y, last_pos_z, last_angle, component_0, \
            component_1, component_2, component_3, component_4, component_5, component_6, component_7, component_8, \
            component_9, component_10, component_11, component_12, component_13, component_14 \
			panels, doors, lights, tires \
        FROM player_vehicles \
        WHERE player = ? \
        ORDER BY id");

	stmt_createVehicle = MySQL_PrepareStatement(MySQL_Handle, "INSERT INTO player_vehicles \
            (player, model, pos_x, pos_y, pos_z, angle, color_1, color_2, price, fuel, health, parked, insurance, \
            max_accessories, due_date, expenses, plate, text, last_pos_x, last_pos_y, last_pos_z, last_angle, component_0, \
            component_1, component_2, component_3, component_4, component_5, component_6, component_7, component_8, \
            component_9, component_10, component_11, component_12, component_13, component_14, panels, doors, lights, tires, date_created) \
        VALUES ('?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', \
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', \
			CURRENT_TIMESTAMP)");

	stmt_updateVehicle = MySQL_PrepareStatement(MySQL_Handle, "UPDATE player_vehicles \
        SET player='?', model='?', pos_x='?', pos_y='?', pos_z='?', angle='?', color_1='?', color_2='?', \
            price='?', fuel='?', health='?', parked='?', insurance='?', max_accessories='?', due_date='?', expenses='?', \
            plate='?', `text`='?', last_pos_x='?', last_pos_y='?', last_pos_z='?', last_angle='?', component_0='?', \
            component_1='?', component_2='?', component_3='?', component_4='?', component_5='?', component_6='?', \
            component_7='?', component_8='?', component_9='?', component_10='?', component_11='?', component_12='?', \
            component_13='?', component_14='?', panels='?', doors='?', lights='?', tires='?' \
        WHERE id='?'");

	stmt_destroyVehicle = MySQL_PrepareStatement(MySQL_Handle, "DELETE FROM player_vehicles WHERE id=?");

	// stmt_selectVehicleAccessories = MySQL_PrepareStatement(MySQL_Handle, "SELECT \
	// 		pva.id, pva.vehicle, pva.model, pva.removable, pva.offset_x, pva.offset_y, pva.offset_z, \
	// 		pva.rot_x, pva.rot_y, pva.rot_z, pva.name \
	// 	FROM player_vehicle_accessories pva \
	// 	INNER JOIN player_vehicles pv ON \
	// 		pv.id = pva.vehicle \
	// 	WHERE pv.player = ? \
	// 	ORDER BY pva.vehicle");

	// stmt_selectVehicleAccessories = MySQL_PrepareStatement(MySQL_Handle, 
	// 	"SELECT \
	// 		player_vehicle_accessories.id, player_vehicle_accessories.vehicle, player_vehicle_accessories.model, player_vehicle_accessories.removable, \
	// 		player_vehicle_accessories.offset_x, player_vehicle_accessories.offset_y, player_vehicle_accessories.offset_z, \
	// 		player_vehicle_accessories.rot_x, player_vehicle_accessories.rot_y, player_vehicle_accessories.rot_z, player_vehicle_accessories.name \
	// 	FROM \
	// 		player_vehicle_accessories, player_vehicles \
	// 	WHERE \
	// 		player_vehicles.id = player_vehicle_accessories.vehicle AND player_vehicles.player = ? ORDER BY player_vehicle_accessories.vehicle");

	// stmt_createVehicleAccessory = MySQL_PrepareStatement(MySQL_Handle, "INSERT INTO player_vehicle_accessories \
	// 		(vehicle, model, offset_x, offset_y, offset_z, rot_x, rot_y, rot_z, removable, name, date_created) \
	// 	VALUES ('?', '?', '?', '?', '?', '?', '?', '?', '?', '?', CURRENT_TIMESTAMP)");

	// stmt_updateVehicleAccessory = MySQL_PrepareStatement(MySQL_Handle, "UPDATE player_vehicle_accessories \
	// 	SET offset_x='?', offset_y='?', offset_z='?', rot_x='?', rot_y='?', rot_z='?' \
    //     WHERE id='?'");

	stmt_updateVehiclePart = MySQL_PrepareStatement(MySQL_Handle, "UPDATE `player_vehicles` SET `?` = ? WHERE id = '?'");

	// stmt_destroyVehicleAccessory = MySQL_PrepareStatement(MySQL_Handle, "DELETE FROM player_vehicle_accessories WHERE id=?");
	return 1;
}

stock VehiclePlayer_Death(vehicleid, i) 
{
	foreach(new carro : IterPlayerVehicles[i])
	{
		if (vehicleid == PlayerVehicleInfo[i][carro][pvID])
		{
			new string[156];
			new Float:x, Float:y, Float:z;
			GetVehiclePos(vehicleid, x, y, z);

			new MapZone:zone = GetMapZoneAtPoint2D(x, y);
			new zone_name[MAX_MAP_ZONE_NAME];
			GetMapZoneName(zone, zone_name);

			new vehicle_name[30];
			GetModelStaticNameFromId(GetVehicleModel(vehicleid), vehicle_name);

			format(string, sizeof string, "Seu veículo {00FFFF}%s {FFFFFF}explodiu próximo a região de {FFFF00}%s.", vehicle_name, zone_name);
			SendClientMessage(i, -1, string);

			new valor = PlayerVehicleInfo[i][carro][pvPrice] / 12;

			if (PlayerVehicleInfo[i][carro][pvInsurance]) {
				valor = PlayerVehicleInfo[i][carro][pvPrice] / 17;
				SendMsgF(i, -1, "Seu carro {00AA00}Possui seguro{FFFFFF} e você pagou somente o valor da franquia de {00AA00}$%s", getFormatText(valor));
			}
			else {
				SendMsgF(i, -1, "Seu carro não tem seguro, os mecânicos cobraram {00AA00}$%s {FFFFFF}para consertá-lo!", getFormatText(valor));
			}

			if (Player_GetMoney (i) > 0)
				Player_RemoveMoney(i, valor);
			break;
		}
	}
}

hook OnPlayerDisconnect(playerid, reason) {
	Player_DestroyVehicles(playerid);
	return 1;
}

stock Player_GenerateMaxVehAccs(playerid) {
	new value = 5;

	switch (Player_GetVIP(playerid)) {
		case SOCIO_COMUM: value += 2;
		case SOCIO_PREMIUM: value += 3;
		case SOCIO_SUPREME: value += 4;
		case SOCIO_EXTREME: value += 5;
	}

	if(value > MAX_VEHICLE_ACCESSORIES)
		value = MAX_VEHICLE_ACCESSORIES;

	return value;
}

stock Player_SetVehicleComponents(playerid, vehicleid) {
	new servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];
	if(GetVehicleModel(servervehicleid) != 495) {
		for(new component; component != 14; component++) {
			if (PlayerVehicleInfo[playerid][vehicleid][pvComponent][component] > 0) {
				AddVehicleComponent(servervehicleid, PlayerVehicleInfo[playerid][vehicleid][pvComponent][component]);
			}
		}
	}
	
	if (PlayerVehicleInfo[playerid][vehicleid][pvComponent][14] > -1) {
	    ChangeVehiclePaintjob(servervehicleid, PlayerVehicleInfo[playerid][vehicleid][pvComponent][14]);
	}
	if (strlen(PlayerVehicleInfo[playerid][vehicleid][pvText]) > 4) {
	    setVehicleText(servervehicleid, PlayerVehicleInfo[playerid][vehicleid][pvText]);
	}
}

stock Player_SpawnVehicle(playerid, vehicleid) {
    if (PlayerVehicleInfo[playerid][vehicleid][pvLastPos][0] == 0.0) {
		PlayerVehicleInfo[playerid][vehicleid][pvLastPos][0] = PlayerVehicleInfo[playerid][vehicleid][pvPos][0];
		PlayerVehicleInfo[playerid][vehicleid][pvLastPos][1] = PlayerVehicleInfo[playerid][vehicleid][pvPos][1];
		PlayerVehicleInfo[playerid][vehicleid][pvLastPos][2] = PlayerVehicleInfo[playerid][vehicleid][pvPos][2];
		PlayerVehicleInfo[playerid][vehicleid][pvLastPos][3] = PlayerVehicleInfo[playerid][vehicleid][pvPos][3];
	}

	PlayerVehicleInfo[playerid][vehicleid][pvID] = CreateVehicle(
        PlayerVehicleInfo[playerid][vehicleid][pvModel],
	    PlayerVehicleInfo[playerid][vehicleid][pvLastPos][0],
        PlayerVehicleInfo[playerid][vehicleid][pvLastPos][1],
        PlayerVehicleInfo[playerid][vehicleid][pvLastPos][2],
	    PlayerVehicleInfo[playerid][vehicleid][pvLastPos][3], 
        PlayerVehicleInfo[playerid][vehicleid][pvColor][0],
        PlayerVehicleInfo[playerid][vehicleid][pvColor][1], 
        -1
    );
	printf("PlayerVehicleInfo[playerid][vehicleid][pvID]: %d", PlayerVehicleInfo[playerid][vehicleid][pvID]);
	SetVehicleHealth(PlayerVehicleInfo[playerid][vehicleid][pvID], PlayerVehicleInfo[playerid][vehicleid][pvHealth]);
	VehicleInfo[PlayerVehicleInfo[playerid][vehicleid][pvID]][vehicleCombustivel] = PlayerVehicleInfo[playerid][vehicleid][pvFuel];

	LockVehicleDoors(PlayerVehicleInfo[playerid][vehicleid][pvID]);
	
	SetVehicleNumberPlate(PlayerVehicleInfo[playerid][vehicleid][pvID], PlayerVehicleInfo[playerid][vehicleid][pvPlate]);

	StopVehicleEngine(PlayerVehicleInfo[playerid][vehicleid][pvID]);

    Player_SetVehicleComponents(playerid, vehicleid);

	UpdateVehicleDamageStatus(
		PlayerVehicleInfo[playerid][vehicleid][pvID], 
		PlayerVehicleInfo[playerid][vehicleid][pvPanels],
		PlayerVehicleInfo[playerid][vehicleid][pvDoors],
		PlayerVehicleInfo[playerid][vehicleid][pvLights],
		PlayerVehicleInfo[playerid][vehicleid][pvTires]
	);

	// Iter_Clear(IterPVAccessories[PlayerVehicleInfo[playerid][vehicleid][pvID]]);

	// if (Now() > PlayerVehicleInfo[playerid][vehicleid][pvDueDate]) {
	//     new string_conce[200];
	// 	new vehicle_name[30];
	// 	GetModelStaticNameFromId(GetVehicleModel(PlayerVehicleInfo[playerid][vehicleid][pvID]), vehicle_name);

	//     format(string_conce, sizeof (string_conce), "Seu carro {00FFFF}%s {FFFFFF}foi vendido, pois você não pagou as {FF0000}despesas {FFFFFF}dele!", vehicle_name);
	// 	SendClientMessage(playerid, -1, string_conce);
	// 	Player_RemoveVehicle(playerid, vehicleid);
	// }
}

// stock Player_SetVehicleAccessory(playerid, vehicleid, accessoryID) {
// 	new servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];

// 	if(!IsValidDynamicObject(VehicleAccessoryInfo[servervehicleid][accessoryID][pvaObjectID])) {
// 		VehicleAccessoryInfo[servervehicleid][accessoryID][pvaObjectID] = CreateDynamicObject(
// 			VehicleAccessoryInfo[servervehicleid][accessoryID][pvaModel], 
// 			0.000, 0.000, 0.000, 0.000, 0.000, 0.000
// 		);
// 	}
	
// 	AttachDynamicObjectToVehicle(
// 		VehicleAccessoryInfo[servervehicleid][accessoryID][pvaObjectID],
// 		servervehicleid,
// 		VehicleAccessoryInfo[servervehicleid][accessoryID][pvaOffset][0], 
// 		VehicleAccessoryInfo[servervehicleid][accessoryID][pvaOffset][1], 
// 		VehicleAccessoryInfo[servervehicleid][accessoryID][pvaOffset][2], 
// 		VehicleAccessoryInfo[servervehicleid][accessoryID][pvaRotation][0], 
// 		VehicleAccessoryInfo[servervehicleid][accessoryID][pvaRotation][1], 
// 		VehicleAccessoryInfo[servervehicleid][accessoryID][pvaRotation][2]
// 	);

// 	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
// }

// stock Player_SetVehicleAccessories(playerid, vehicleid) {
// 	new servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];

// 	foreach(new acc : IterPVAccessories[vehicleid]) {
// 		Player_SetVehicleAccessory(playerid, vehicleid, acc);
// 	}
// }

// stock Player_DestroyVehAccessories(playerid, vehicleid) {
// 	new servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];
	
// 	foreach(new acc : IterPVAccessories[vehicleid]) {
// 		if(IsValidDynamicObject(VehicleAccessoryInfo[servervehicleid][acc][pvaObjectID])) {
// 			DestroyDynamicObject(VehicleAccessoryInfo[servervehicleid][acc][pvaObjectID]);
// 		}
// 		VehicleAccessoryInfo[servervehicleid][acc][pvaID] = 0;
// 	}
// 	Iter_Clear(IterPVAccessories[vehicleid]);
// }

// stock Player_CreateVehAccessory(playerid, vehicleID, model, removable, const name[], const Float:offset[], const Float:rotation[]) {
// 	new servervehicleid = PlayerVehicleInfo[playerid][vehicleID][pvID],
// 		accessoryID = Iter_Free(IterPVAccessories[servervehicleid]);
	
// 	if (Iter_Count(IterPVAccessories[servervehicleid]) >= PlayerVehicleInfo[playerid][vehicleID][pvMaxAccessories] || accessoryID < 0)
// 		return -1;

// 	if (accessoryID != INVALID_ITERATOR_SLOT)
// 	{
// 		Iter_Add(IterPVAccessories[servervehicleid], accessoryID);

// 		VehicleAccessoryInfo[vehicleid][accessoryID][pvaID] = 0;
// 		VehicleAccessoryInfo[vehicleid][accessoryID][pvaObjectID] = INVALID_OBJECT_ID;
// 		VehicleAccessoryInfo[vehicleid][accessoryID][pvaModel] = model;
// 		VehicleAccessoryInfo[vehicleid][accessoryID][pvaRemovable] = removable;
// 		for(new i = 0; i < 3; i++) {
// 			VehicleAccessoryInfo[vehicleid][accessoryID][pvaOffset][i] = offset[i];
// 			VehicleAccessoryInfo[vehicleid][accessoryID][pvaRotation][i] = rotation[i];
// 		}

// 		format(VehicleAccessoryInfo[servervehicleid][accessoryID][pvaName], 75, name);

// 		Player_SetVehicleAccessory(playerid, vehicleID, accessoryID);
// 	}
// 	return accessoryID;
// }

// stock Player_RemoveVehAccessory(playerid, vehicleID, accessoryID) {
// 	new servervehicleid = PlayerVehicleInfo[playerid][vehicleID][pvID];

// 	Iter_Remove(IterPVAccessories[servervehicleid], accessoryID);

// 	MySQL_BindInt(stmt_destroyVehicleAccessory, 0, VehicleAccessoryInfo[servervehicleid][accessoryID][pvaID]);
// 	MySQL_ExecuteThreaded(stmt_destroyVehicleAccessory);

// 	if (IsValidDynamicObject(VehicleAccessoryInfo[servervehicleid][accessoryID][pvaObjectID])) {
// 		DestroyDynamicObject(VehicleAccessoryInfo[servervehicleid][accessoryID][pvaObjectID]);
// 	}
// 	VehicleAccessoryInfo[servervehicleid][accessoryID][pvaObjectID] = INVALID_OBJECT_ID;
// 	VehicleAccessoryInfo[servervehicleid][accessoryID][pvaID] = 0;
// }

stock Player_LoadVehicles(playerid) {
	inline const OnLoadVehicles() {
		new 
			dbid,
            model,
            price,
            fuel,
            parked,
            insurance,
			expenses,
            date[20],
            plate[25],
            text[55],
            Float:pos[4],
            Float:health,
            maxAccessories,
            color[2],
            component[15],
            Float:vLastPos[4],
			bool:panels,
			bool:doors,
			bool:lights,
			bool:tires
        ;

		MySQL_BindResultInt(stmt_selectVehicles, 0, dbid);
        MySQL_BindResultInt(stmt_selectVehicles, 1, model);
        for(new i = 0; i < 4; i++) 
			MySQL_BindResultFloat(stmt_selectVehicles, 2+i, pos[i]);
        for(new i = 0; i < 2; i++)  
            MySQL_BindResultInt(stmt_selectVehicles, 6+i, color[i]);
        MySQL_BindResultInt(stmt_selectVehicles, 8, price);
        MySQL_BindResultInt(stmt_selectVehicles, 9, fuel);
        MySQL_BindResultFloat(stmt_selectVehicles, 10, health);
        MySQL_BindResultInt(stmt_selectVehicles, 11, parked);
        MySQL_BindResultInt(stmt_selectVehicles, 12, insurance);
        MySQL_BindResultInt(stmt_selectVehicles, 13, maxAccessories);
        MySQL_BindResult(stmt_selectVehicles, 14, date, sizeof(date));
        MySQL_BindResultInt(stmt_selectVehicles, 15, expenses);
        MySQL_BindResult(stmt_selectVehicles, 16, plate, sizeof(plate));
        MySQL_BindResult(stmt_selectVehicles, 17, text, sizeof(text));
        for(new i = 0; i < 4; i++) 
			MySQL_BindResultFloat(stmt_selectVehicles, 18+i, vLastPos[i]);
        for(new i = 0; i < 15; i++) 
            MySQL_BindResultInt(stmt_selectVehicles, 22+i, component[i]);

		MySQL_BindResultInt(stmt_selectVehicles, 37, panels);
		MySQL_BindResultInt(stmt_selectVehicles, 38, doors);
		MySQL_BindResultInt(stmt_selectVehicles, 39, lights);
		MySQL_BindResultInt(stmt_selectVehicles, 40, tires);

		while (MySQL_Statement_FetchRow(stmt_selectVehicles)) {
			new id = Iter_Free(IterPlayerVehicles[playerid]);

			if (id != INVALID_ITERATOR_SLOT) {
				Iter_Add(IterPlayerVehicles[playerid], id);

				PlayerVehicleInfo[playerid][id][pvDBID] = dbid;
				PlayerVehicleInfo[playerid][id][pvModel] = model;
				PlayerVehicleInfo[playerid][id][pvPrice] = price;
				PlayerVehicleInfo[playerid][id][pvFuel] = fuel;
				PlayerVehicleInfo[playerid][id][pvHealth] = health;
				PlayerVehicleInfo[playerid][id][pvParked] = parked;
				PlayerVehicleInfo[playerid][id][pvInsurance] = insurance;
				PlayerVehicleInfo[playerid][id][pvMaxAccessories] = maxAccessories;
				PlayerVehicleInfo[playerid][id][pvExpenses] = expenses;
				PlayerVehicleInfo[playerid][id][pvPanels] = panels;
				PlayerVehicleInfo[playerid][id][pvDoors] = doors;
				PlayerVehicleInfo[playerid][id][pvLights] = lights;
				PlayerVehicleInfo[playerid][id][pvTires] = tires;

				if(PlayerVehicleInfo[playerid][id][pvMaxAccessories] == 0) {
					PlayerVehicleInfo[playerid][id][pvMaxAccessories] = Player_GenerateMaxVehAccs(playerid);
				}

				for(new i = 0; i < 4; i++) {
					PlayerVehicleInfo[playerid][id][pvPos][i] = pos[i];
					PlayerVehicleInfo[playerid][id][pvLastPos][i] = vLastPos[i];
				}

				for(new i = 0; i < 2; i++) {
					PlayerVehicleInfo[playerid][id][pvColor][i] = color[i];
				}

				for(new i = 0; i < 15; i++) {
					PlayerVehicleInfo[playerid][id][pvComponent][i] = component[i];
				}

				TimeParse(date, ISO6801_DATE, PlayerVehicleInfo[playerid][id][pvDueDate]);
				format(PlayerVehicleInfo[playerid][id][pvPlate], 25, plate);
				format(PlayerVehicleInfo[playerid][id][pvText], 55, text);

				Player_SpawnVehicle(playerid, id);
			}
		}

		foreach(new vehicleid : IterPlayerVehicles[playerid]) {
			if (strlen(PlayerVehicleInfo[playerid][vehicleid][pvPlate]) < 5) {
				format(PlayerVehicleInfo[playerid][vehicleid][pvPlate], 25, GetUniqueNumberPlate());
				SetVehicleNumberPlate(PlayerVehicleInfo[playerid][vehicleid][pvID], PlayerVehicleInfo[playerid][vehicleid][pvPlate]);
			}
		}

		/*inline const OnLoadVehiclesAccessories() {
			new vaid, vaVehicleID, vaModel, vaRemovable, Float:vaOffset[3], Float:vaRot[3], name[35];
			MySQL_BindResultInt(stmt_selectVehicleAccessories, 0, vaid);
			MySQL_BindResultInt(stmt_selectVehicleAccessories, 1, vaVehicleID);
			MySQL_BindResultInt(stmt_selectVehicleAccessories, 2, vaModel);
			MySQL_BindResultInt(stmt_selectVehicleAccessories, 3, vaRemovable);
			for(new i = 0; i < 3; i++) {
				MySQL_BindResultFloat(stmt_selectVehicleAccessories, 4+i, vaOffset[i]);
				MySQL_BindResultFloat(stmt_selectVehicleAccessories, 7+i, vaRot[i]);
			}
			MySQL_BindResult(stmt_selectVehicleAccessories, 10, name, 75);

			new previousVehicleID, vehicleID;
			while (MySQL_Statement_FetchRow(stmt_selectVehicleAccessories)) {
				if(previousVehicleID != vaVehicleID) {
					foreach(new v : IterPlayerVehicles[playerid]) {
						if(PlayerVehicleInfo[playerid][v][pvDBID] == vaVehicleID) {
							vehicleID = v;
							break;
						}
					}
					previousVehicleID = vaVehicleID;
				}

				new accindex = Player_CreateVehAccessory(
					playerid, vehicleID, vaModel, vaRemovable, name, vaOffset, vaRot
				);
				if(accindex != -1) {
					new servervehicleid = PlayerVehicleInfo[playerid][vehicleID][pvID];
					VehicleAccessoryInfo[servervehicleid][accindex][pvaID] = vaid;
				}
			}
		}
		MySQL_BindInt(stmt_selectVehicleAccessories, 0, Player_GetAccountID(playerid));
    	MySQL_ExecuteThreaded_Inline(stmt_selectVehicleAccessories, using inline OnLoadVehiclesAccessories);*/
	}
	MySQL_BindInt(stmt_selectVehicles, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_selectVehicles, using inline OnLoadVehicles);
}

stock Player_CountVehicles(playerid) {
	return Iter_Count(IterPlayerVehicles[playerid]);
}

stock Player_TransferVehicle(playerid, giveid, slotid) {
    new carro = Iter_Free(IterPlayerVehicles[giveid]);
    if(carro < 0)
        return -1;

	Iter_Add(IterPlayerVehicles[giveid], carro);
    PlayerVehicleInfo[giveid][carro][pvDBID] = PlayerVehicleInfo[playerid][slotid][pvDBID];
    PlayerVehicleInfo[giveid][carro][pvID] = PlayerVehicleInfo[playerid][slotid][pvID];
    PlayerVehicleInfo[giveid][carro][pvModel] = PlayerVehicleInfo[playerid][slotid][pvModel];
    PlayerVehicleInfo[giveid][carro][pvHealth] = PlayerVehicleInfo[playerid][slotid][pvHealth];
    PlayerVehicleInfo[giveid][carro][pvColor][0] = PlayerVehicleInfo[playerid][slotid][pvColor][0];
    PlayerVehicleInfo[giveid][carro][pvColor][1] = PlayerVehicleInfo[playerid][slotid][pvColor][1];
    PlayerVehicleInfo[giveid][carro][pvPrice] = PlayerVehicleInfo[playerid][slotid][pvPrice];
    PlayerVehicleInfo[giveid][carro][pvParked] = PlayerVehicleInfo[playerid][slotid][pvParked];
    PlayerVehicleInfo[giveid][carro][pvInsurance] = PlayerVehicleInfo[playerid][slotid][pvInsurance];
    PlayerVehicleInfo[giveid][carro][pvMaxAccessories] = Player_GenerateMaxVehAccs(giveid);
    PlayerVehicleInfo[giveid][carro][pvDueDate] = PlayerVehicleInfo[playerid][slotid][pvDueDate];
    PlayerVehicleInfo[giveid][carro][pvExpenses] = PlayerVehicleInfo[playerid][slotid][pvExpenses];
    PlayerVehicleInfo[giveid][carro][pvFuel] = PlayerVehicleInfo[playerid][slotid][pvFuel];

	for(new i = 0; i < 4; i++) {
		PlayerVehicleInfo[giveid][carro][pvPos][i] = PlayerVehicleInfo[playerid][slotid][pvPos][i];
		PlayerVehicleInfo[giveid][carro][pvLastPos][i] = PlayerVehicleInfo[playerid][slotid][pvLastPos][i];
	}

    for(new component; component < 15; component++) {
        PlayerVehicleInfo[giveid][carro][pvComponent][component] = PlayerVehicleInfo[playerid][slotid][pvComponent][component];
    }
    format(PlayerVehicleInfo[giveid][carro][pvPlate], 25, PlayerVehicleInfo[playerid][slotid][pvPlate]);
    format(PlayerVehicleInfo[giveid][carro][pvText], 55, PlayerVehicleInfo[playerid][slotid][pvText]);

    Player_SaveVehicle(giveid, carro);
    UpdateVehiclePlateInfo(PlayerVehicleInfo[giveid][carro][pvPlate], PlayerName[giveid]);
    
    Iter_Remove(IterPlayerVehicles[playerid], slotid);
    PlayerVehicleInfo[playerid][slotid][pvID] = INVALID_VEHICLE_ID;
    return carro;
}

stock Player_DestroyVehicles(playerid) {
	foreach(new v : IterPlayerVehicles[playerid]) {
		//Player_DestroyVehAccessories(playerid, v);
        removeVehicleText(PlayerVehicleInfo[playerid][v][pvID]);
        DestroyVehicle(PlayerVehicleInfo[playerid][v][pvID]);
        PlayerVehicleInfo[playerid][v][pvID] = INVALID_VEHICLE_ID;
	}
	Iter_Clear(IterPlayerVehicles[playerid]);
}

stock Player_RemoveVehicle(playerid, vehicleid) {
	PlayerVehicleInfo[playerid][vehicleid][pvPrice] = 0;
	PlayerVehicleInfo[playerid][vehicleid][pvModel] = 400;

	for(new i; i < 4; i++) {
	  	PlayerVehicleInfo[playerid][vehicleid][pvPos][i] = 0.0;
	}
	for(new component; component < 15; component++) {
	  	PlayerVehicleInfo[playerid][vehicleid][pvComponent][component] = -1;
	}

	MySQL_BindInt(stmt_destroyVehicle, 0, PlayerVehicleInfo[playerid][vehicleid][pvDBID]);
	MySQL_ExecuteThreaded(stmt_destroyVehicle);

	// removeVehiclePlate(PlayerVehicleInfo[playerid][vehicleid][pvID]);

	//Player_DestroyVehAccessories(playerid, vehicleid);
	removeVehicleText(PlayerVehicleInfo[playerid][vehicleid][pvID]);
	DestroyVehicle(PlayerVehicleInfo[playerid][vehicleid][pvID]);

	//Iter_Clear(IterPVAccessories[PlayerVehicleInfo[playerid][vehicleid][pvID]]);
	Iter_Remove(IterPlayerVehicles[playerid], vehicleid);

	PlayerVehicleInfo[playerid][vehicleid][pvID] = INVALID_VEHICLE_ID;
	PlayerVehicleInfo[playerid][vehicleid][pvDBID] = 0;
}

stock IsPlayerVehicleOwner(playerid, vehicleid) {
	foreach(new v : IterPlayerVehicles[playerid]) {
	    if (PlayerVehicleInfo[playerid][v][pvID] == vehicleid) {
	        return 1;
		}
	}
	return 0;
}

CALLBACK:Player_UpdateVehicleText(vehicleid, const text[]) {
	foreach(new playerid : Player) {
		foreach(new carro : IterPlayerVehicles[playerid]) {
	   		if (PlayerVehicleInfo[playerid][carro][pvID] == vehicleid) {
				format(PlayerVehicleInfo[playerid][carro][pvText], 75, text);
				break;
			}
		}
	}
	return 0;
}

stock IsPlayerVehicleOwnerByPlate(playerid, const numberplate[]) {
    foreach(new v : IterPlayerVehicles[playerid]) {
	    if (!strcmp(PlayerVehicleInfo[playerid][v][pvPlate], numberplate, true)) {
	        return 1;
		}
	}
	return 0;
}

stock Player_UpdateVehicleComponents(playerid, vehicleid) {
	new servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];

	for(new component; component < 14; component++) {
    	PlayerVehicleInfo[playerid][vehicleid][pvComponent][component] = GetVehicleComponentInSlot(servervehicleid, component);
	}
}

stock Player_UpdateVehicleStats(playerid, vehicleid) {
    new Float:vehiclePos[4],
        servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];
    
	if (servervehicleid != INVALID_VEHICLE_ID) {
		GetVehiclePos(servervehicleid, vehiclePos[0], vehiclePos[1], vehiclePos[2]);
		GetVehicleZAngle(servervehicleid, vehiclePos[3]);

		if(!PlayerVehicleInfo[playerid][vehicleid][pvParked]) {
			for(new i = 0; i < 4; i++)
				PlayerVehicleInfo[playerid][vehicleid][pvPos][i] = vehiclePos[i];
		}

		for(new i = 0; i < 4; i++)
			PlayerVehicleInfo[playerid][vehicleid][pvLastPos][i] = vehiclePos[i];

		PlayerVehicleInfo[playerid][vehicleid][pvFuel] = VehicleInfo[PlayerVehicleInfo[playerid][vehicleid][pvID]][vehicleCombustivel];

		GetVehicleHealth(servervehicleid, PlayerVehicleInfo[playerid][vehicleid][pvHealth]);

		GetVehicleDamageStatus(
			servervehicleid, 
			PlayerVehicleInfo[playerid][vehicleid][pvPanels],
			PlayerVehicleInfo[playerid][vehicleid][pvDoors],
			PlayerVehicleInfo[playerid][vehicleid][pvLights],
			PlayerVehicleInfo[playerid][vehicleid][pvTires]
		);

		Player_UpdateVehicleComponents(playerid, vehicleid);
	}
}

stock Vehicle_GetDueDate(playerid, vehicleid) {
	new days = TimestampToRemainingDays(PlayerVehicleInfo[playerid][vehicleid][pvDueDate]);
	return days;
}

stock Vehicle_SetDueDate(playerid, vehicleid, Days:days) 
{
	PlayerVehicleInfo[playerid][vehicleid][pvDueDate] = Now() + Days:days;

	new date[20];
	TimeFormat(PlayerVehicleInfo[playerid][vehicleid][pvDueDate], MYSQL_DATE, date);

	MySQL_Bind(stmt_updateVehiclePart, 0, "due_date", true);
	MySQL_Bind(stmt_updateVehiclePart, 1, date);
	MySQL_BindInt(stmt_updateVehiclePart, 2, PlayerVehicleInfo[playerid][vehicleid][pvDBID]);
	MySQL_ExecuteThreaded(stmt_updateVehiclePart);
}

stock Vehicle_TaxPay(playerid, TaxType:tax)
{
	new string[128],
		taxValue = Tax_GetValue(tax),
		days,
		taxPay[MAX_PLAYER_CARROS],
		debtValue[MAX_PLAYER_CARROS],
		Float:daysLate[MAX_PLAYER_CARROS],
		vehicle_id,
		vehicle_model,
		vehicle_value,
		vehicle_name[30];

	if (Iter_Count(IterPlayerVehicles[playerid]) < 1)
		return SendClientMessage(playerid, -1, "Você não tem nenhum veículo."), Dialog_PayTax(playerid);

	MEGAString[0] = EOS;
	strcat(MEGAString, "veiculo\tdata de vencimento\tvalor\n");

	foreach(new carro : IterPlayerVehicles[playerid]) {
		vehicle_id = carro;
		days = Vehicle_GetDueDate(playerid, carro);
		vehicle_value = PlayerVehicleInfo[playerid][carro][pvPrice];

		taxPay[carro] = floatround(floatmul(floatdiv(taxValue, 100.0), vehicle_value));

		vehicle_model = PlayerVehicleInfo[playerid][vehicle_id][pvModel];
		GetModelStaticNameFromId(vehicle_model, vehicle_name);

		if (days < 0) {
			daysLate[carro] = floatabs(days);
			debtValue[carro] = floatround(daysLate[carro] * floatround(floatmul(floatdiv(1.0, 100.0), taxPay[carro])));

			format(string, sizeof(string), ""C_CYAN"%s\t"C_RED"%d DIAS DE ATRASO\t"C_MONEY"$%s\n",
			vehicle_name, daysLate[carro], getFormatText(taxPay[carro]));

			taxPay[carro] = (taxPay[carro] + debtValue[carro]);
		} else {
			taxPay[carro] = (floatround(floatmul(floatdiv(taxValue, 100.0), vehicle_value)) / 30) * (30 - days);

			format(string, sizeof(string), ""C_CYAN"%s\t"C_GREEN"%d DIAS PARA VENCER\t"C_MONEY"$%s\n",
			vehicle_name, days, getFormatText(taxPay[carro]));
		}
		strcat(MEGAString, string);
	}

	inline D_TaxPayConfirm(dtaxpupyid, dtaxpupydialogid, dtaxpupyresponse, dtaxpupylistitem, string:dtaxpupytext[])
	{
		#pragma unused dtaxpupyid, dtaxpupydialogid, dtaxpupylistitem, dtaxpupytext

		if (!dtaxpupyresponse)
			return Dialog_PayTax(playerid);

		if (Iter_Contains(IterPlayerVehicles[playerid], vehicle_id)) 
		{
			if (Player_GetMoney(playerid) < taxPay[vehicle_id])
				return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiente.");

			format(string, sizeof(string), "Você pagou as contas do seu veículo: "C_CYAN"%s"C_WHITE", total "C_RED"-$%s", vehicle_name, getFormatText(taxPay[vehicle_id] - debtValue[vehicle_id]));
			SendClientMessage(playerid, -1, string);

			if (daysLate[vehicle_id] > 0) {
				format(string, sizeof(string), "O atraso gerou juros e foi cobrado "C_GRAY"1%% ao dia totalizando: "C_RED"-$%s", getFormatText(debtValue[vehicle_id]));
				SendClientMessage(playerid, -1, string);
			}
			Player_RemoveMoney(playerid, taxPay[vehicle_id]);

			adicionarDinheiroGoverno(floatround(floatmul(floatdiv(80.0, 100.0), taxPay[vehicle_id])));
			DepositPropertie(playerid, floatround(floatmul(floatdiv(20.0, 100.0), taxPay[vehicle_id])));
			
			Vehicle_SetDueDate(playerid, vehicle_id, Days:30);
		}
		Dialog_ShowCallback(
			playerid, using inline D_TaxPayConfirm, DIALOG_STYLE_TABLIST_HEADERS, 
			"IPVA", 
			MEGAString, "Pagar", "Retornar"
		);
	}
	return 1;
}

stock Player_SaveVehicle(playerid, vehicleid) {
    if (vehicleid < 0 || vehicleid >= MAX_PLAYER_CARROS || !Player_Logado(playerid))
	    return 0;
    
    if (Iter_Contains(IterPlayerVehicles[playerid], vehicleid)) {

        new date[20], plate[25], text[55], Statement:stmt;
        format(plate, sizeof(plate), PlayerVehicleInfo[playerid][vehicleid][pvPlate]);
        format(text, sizeof(text), PlayerVehicleInfo[playerid][vehicleid][pvText]);
        TimeFormat(PlayerVehicleInfo[playerid][vehicleid][pvDueDate], MYSQL_DATE, date);

        Player_UpdateVehicleStats(playerid, vehicleid);

        stmt = (PlayerVehicleInfo[playerid][vehicleid][pvDBID] == 0) ? stmt_createVehicle : stmt_updateVehicle;

        MySQL_BindInt(stmt, 0, Player_GetAccountID(playerid));
        MySQL_BindInt(stmt, 1, PlayerVehicleInfo[playerid][vehicleid][pvModel]);
        MySQL_BindInt(stmt, 8, PlayerVehicleInfo[playerid][vehicleid][pvPrice]);
        MySQL_BindInt(stmt, 9, PlayerVehicleInfo[playerid][vehicleid][pvFuel]);
        MySQL_BindFloat(stmt, 10, PlayerVehicleInfo[playerid][vehicleid][pvHealth]);
        MySQL_BindInt(stmt, 11, PlayerVehicleInfo[playerid][vehicleid][pvParked]);
        MySQL_BindInt(stmt, 12, PlayerVehicleInfo[playerid][vehicleid][pvInsurance]);
        //MySQL_BindInt(stmt, 13, PlayerVehicleInfo[playerid][vehicleid][pvMaxAccessories]);
        MySQL_Bind(stmt, 14, date, true);
        MySQL_BindInt(stmt, 15, PlayerVehicleInfo[playerid][vehicleid][pvExpenses]);
        MySQL_Bind(stmt, 16, plate, true);
        MySQL_Bind(stmt, 17, text, true);
		
        for(new i = 0; i < 15; i++) {
			if (i < 2)
				MySQL_BindInt(stmt, 6+i, PlayerVehicleInfo[playerid][vehicleid][pvColor][i]);

			if (i < 4) {
				MySQL_BindFloat(stmt, 2+i, PlayerVehicleInfo[playerid][vehicleid][pvPos][i]);
				MySQL_BindFloat(stmt, 18+i, PlayerVehicleInfo[playerid][vehicleid][pvLastPos][i]);
			}
			MySQL_BindInt(stmt, 22+i, PlayerVehicleInfo[playerid][vehicleid][pvComponent][i]);
		}
		
		MySQL_BindInt(stmt, 37, PlayerVehicleInfo[playerid][vehicleid][pvPanels]);
		MySQL_BindInt(stmt, 38, PlayerVehicleInfo[playerid][vehicleid][pvDoors]);
		MySQL_BindInt(stmt, 39, PlayerVehicleInfo[playerid][vehicleid][pvLights]);
		MySQL_BindInt(stmt, 40, PlayerVehicleInfo[playerid][vehicleid][pvTires]);

		if (PlayerVehicleInfo[playerid][vehicleid][pvDBID] == 0) {
			inline const OnPlayerVehicleCreated() {
				PlayerVehicleInfo[playerid][vehicleid][pvDBID] = cache_insert_id();
			}
			MySQL_ExecuteThreaded_Inline(stmt, using inline OnPlayerVehicleCreated);
		}
		else {
            MySQL_BindInt(stmt, 41, PlayerVehicleInfo[playerid][vehicleid][pvDBID]);
			MySQL_ExecuteThreaded(stmt);
		}
		return 1;
	}
	return 0;
}

stock Player_SaveAllVehicles(playerid) {
    foreach(new v : IterPlayerVehicles[playerid]) {
	    Player_SaveVehicle(playerid, v);
	}
}

/*stock Player_SaveVehicleAccessory(playerid, vehicleid, accessoryID) {
	if (vehicleid < 0 || vehicleid >= MAX_VEHICLE_ACCESSORIES || !Player_Logado(playerid))
	    return 0;
    
    if(!Iter_Contains(IterPlayerVehicles[playerid], vehicleid)) 
		return 0;

	new servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];
	if(!Iter_Contains(IterPVAccessories[servervehicleid], accessoryID)) 
		return 0;

	new Statement:stmt;

	stmt = (VehicleAccessoryInfo[servervehicleid][accessoryID][pvaID] == 0) ? stmt_createVehicleAccessory : stmt_updateVehicleAccessory;

	if(VehicleAccessoryInfo[servervehicleid][accessoryID][pvaID] == 0) {
		MySQL_BindInt(stmt, 0, PlayerVehicleInfo[playerid][vehicleid][pvDBID]);
		MySQL_BindInt(stmt, 1, VehicleAccessoryInfo[servervehicleid][accessoryID][pvaModel]);
		for(new i = 0; i < 3; i++) {
			MySQL_BindFloat(stmt, 2+i, VehicleAccessoryInfo[servervehicleid][accessoryID][pvaOffset][i]);
			MySQL_BindFloat(stmt, 5+i, VehicleAccessoryInfo[servervehicleid][accessoryID][pvaRotation][i]);
		}
		MySQL_BindInt(stmt, 8, VehicleAccessoryInfo[servervehicleid][accessoryID][pvaRemovable]);
		MySQL_Bind(stmt, 9, VehicleAccessoryInfo[servervehicleid][accessoryID][pvaName], true);

		inline const OnAccessoryCreated() {
			VehicleAccessoryInfo[servervehicleid][accessoryID][pvaID] = cache_insert_id();
		}
		MySQL_ExecuteThreaded_Inline(stmt, using inline OnAccessoryCreated);
	}
	else {
		for(new i = 0; i < 3; i++) {
			MySQL_BindFloat(stmt, 0+i, VehicleAccessoryInfo[servervehicleid][accessoryID][pvaOffset][i]);
			MySQL_BindFloat(stmt, 3+i, VehicleAccessoryInfo[servervehicleid][accessoryID][pvaRotation][i]);
		}

		MySQL_BindInt(stmt, 6, VehicleAccessoryInfo[servervehicleid][accessoryID][pvaID]);
		MySQL_ExecuteThreaded(stmt);
	}
	return 1;
}

stock Player_SaveVehicleAccessories(playerid, vehicleid) {
	new servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];
    foreach(new acc : IterPVAccessories[servervehicleid]) {
	    Player_SaveVehicleAccessory(playerid, vehicleid, acc);
	}
}*/

stock Player_SetVehicleFromDealership(playerid, model, preco, vehid) {
	if (vehid == INVALID_VEHICLE_ID) 
        return -1;

    new carro = Iter_Free(IterPlayerVehicles[playerid]);
    if(carro == INVALID_ITERATOR_SLOT)
        return -1;

	Iter_Add(IterPlayerVehicles[playerid], carro);

	PlayerVehicleInfo[playerid][carro][pvDBID] = 0;
    PlayerVehicleInfo[playerid][carro][pvID] = vehid;
    PlayerVehicleInfo[playerid][carro][pvModel] = model;
    PlayerVehicleInfo[playerid][carro][pvHealth] = 1000.0;
    PlayerVehicleInfo[playerid][carro][pvColor][0] = -1;
    PlayerVehicleInfo[playerid][carro][pvColor][1] = -1;
    PlayerVehicleInfo[playerid][carro][pvPrice] = preco;
    PlayerVehicleInfo[playerid][carro][pvParked] = 0;
    PlayerVehicleInfo[playerid][carro][pvInsurance] = 0;
    PlayerVehicleInfo[playerid][carro][pvMaxAccessories] = Player_GenerateMaxVehAccs(playerid);
    PlayerVehicleInfo[playerid][carro][pvDueDate] = Now() + Days:60;
    PlayerVehicleInfo[playerid][carro][pvExpenses] = 0;
    PlayerVehicleInfo[playerid][carro][pvFuel] = 50;

    VehicleInfo[vehid][vehicleCombustivel] = 50;
    for(new component; component < 15; component++) {
        PlayerVehicleInfo[playerid][carro][pvComponent][component] = -1;
    }
    format(PlayerVehicleInfo[playerid][carro][pvPlate], 25, GetUniqueNumberPlate());
    format(PlayerVehicleInfo[playerid][carro][pvText], 25, "");

    SetVehicleHealth(vehid, 1000.0);
    StartVehicleEngine(vehid);

    SetVehicleNumberPlate(vehid, PlayerVehicleInfo[playerid][carro][pvPlate]);

    Player_SaveVehicle(playerid, carro);
    return carro;
}

stock CheckMaxPlayerVehicles(playerid) {
	if(Player_GetVIP(playerid) < 1 && Player_CountVehicles(playerid) >= 1) 
        return false;
	else if(Player_GetVIP(playerid) < 5 && Player_CountVehicles(playerid) >= 2) 
        return false;
	else if(Player_GetVIP(playerid) < 7 && Player_CountVehicles(playerid) >= 3) 
        return false;
    else if(Player_CountVehicles(playerid) >= 4) 
        return false;

	return true;
}

stock Player_ShowNearbyVehicles(playerid) {
	if (Inventory_IsOpen(playerid))
		Inventory_HideForPlayer(playerid);

	MEGAString[0] = EOS;
	strcat(MEGAString, "ID\tModelo\n");

	new Float:pos[3], index;
	foreach(new v : IterPlayerVehicles[playerid]) {
		GetVehiclePos(PlayerVehicleInfo[playerid][v][pvID], pos[0], pos[1], pos[2]);
		if(PlayerToPoint(10.0, playerid, pos[0], pos[1], pos[2])) {
			new vehicle_name[30];
			GetModelStaticNameFromId(GetVehicleModel(PlayerVehicleInfo[playerid][v][pvID]), vehicle_name);

			FormatCat(MEGAString, "{FFFFFF}%d\t{00FFFF}%s\n", PlayerVehicleInfo[playerid][v][pvID], vehicle_name);
			SelectCarros[playerid][index++] = v;
		}
	}
	ShowPlayerDialog(playerid, 350, DIALOG_STYLE_TABLIST_HEADERS, ""C_WHITE"Selecione o seu veículo que deseja equipar", MEGAString, "Selecionar", "Cancelar");
}

stock Player_GetVehicleInRange(playerid, Float:range) {
	new Float:pos[3], Float:minDist = 10000.00, vehicleid = -1;
	foreach(new v : IterPlayerVehicles[playerid]) {
		GetVehiclePos(PlayerVehicleInfo[playerid][v][pvID], pos[0], pos[1], pos[2]);
		new Float:dist = GetPlayerDistanceFromPoint(playerid, pos[0], pos[1], pos[2]);
		if(dist <= range && dist < minDist) {
			minDist = dist;
			vehicleid = v;
		}
	}
	return vehicleid;
}

hook OnEnterExitModShop(playerid, enterexit, interiorid) {
	new string[128];
	new vehicleid = GetPlayerVehicleID(playerid);
	new vehicle_name[30];
	GetModelStaticNameFromId(GetVehicleModel(vehicleid), vehicle_name);

	if(enterexit == 0 || interiorid == 0) {
        foreach(new v : IterPlayerVehicles[playerid]) {
	        if (vehicleid == PlayerVehicleInfo[playerid][v][pvID]) {
                Player_UpdateVehicleComponents(playerid, v);
				Player_SaveVehicle(playerid, v);
				break;
	        }
	    }
	    format(string, sizeof string, " Você terminou de tunar o carro {00FFFF}%s{FFFFFF}!", vehicle_name);
	    SendClientMessage(playerid, -1, string);
	} 
	else {
	    if (enterexit) {
	    	format(string, sizeof string, " Você está pronto para tunar o carro {00FFFF}%s{FFFFFF}!", vehicle_name);
	    	SendClientMessage(playerid, -1, string);
		}
	}
	return 1;
}

hook OnVehiclePaintjob(playerid, vehicleid, paintjobid) {
    foreach(new v : IterPlayerVehicles[playerid]) {
		if (vehicleid == PlayerVehicleInfo[playerid][v][pvID]) {
            PlayerVehicleInfo[playerid][v][pvComponent][14] = paintjobid;
			break ;
   		}
   	}
	return 1;
}

hook OnVehicleRespray(playerid, vehicleid, color1, color2) {
    foreach(new v : IterPlayerVehicles[playerid]) {
		if (vehicleid == PlayerVehicleInfo[playerid][v][pvID]) {
			PlayerVehicleInfo[playerid][v][pvColor][0] = color1;
           	PlayerVehicleInfo[playerid][v][pvColor][1] = color2;
			break;
   		}
   	}
	return 1;
}

hook OnVehicleSpawn(vehicleid) {
	foreach(new playerid : Player)  {
	    if (Player_Logado(playerid)) {
            foreach(new v : IterPlayerVehicles[playerid]) {
				if (vehicleid == PlayerVehicleInfo[playerid][v][pvID]) {
                    Player_SetVehicleComponents(playerid, v);
					return 1;
		   		}
            }
	    }
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) 
{
	new string[256];

	if (dialogid == 89) {
		if (listitem == -1)
			return 1;

	    if (response) {
	        new carroid = PlayerVehicleInfo[playerid][SelectCarros[playerid][listitem]][pvID];

		    new Float:x, Float:y, Float:z;
		    GetVehiclePos(carroid, x, y, z);

			new MapZone:zone = GetMapZoneAtPoint2D(x, y);
			new zone_name[MAX_MAP_ZONE_NAME];
			GetMapZoneName(zone, zone_name);

			new vehicle_name[30];
			GetModelStaticNameFromId(GetVehicleModel(carroid), vehicle_name);

			format(string, sizeof string, "Você localizou o veículo {00FFFF}%s {FFFFFF}que está em {FFFF00}%s, {FFFFFF}siga a marca vermelha!", vehicle_name, zone_name);
			SendClientMessage(playerid, -1, string);

			SetPlayerCheckpoint(playerid, x, y, z, 3.0);
		}
	    return 1;
	}
	else if (dialogid == 96) {
	    if (response) {
	        new carroid = SelectCarros[playerid][listitem],
				valorrevenda = PlayerVehicleInfo[playerid][carroid][pvPrice]/2;

			if (!Iter_Contains(IterPlayerVehicles[playerid], carroid))
			    return 1;

			if (IsVehicleInDetran(PlayerVehicleInfo[playerid][carroid][pvID])) 
				return SendClientMessage(playerid, -1, "Você não pode vender um veículo que está apreendido na PRF.");

			/*new servervehicleid = PlayerVehicleInfo[playerid][carroid][pvID];
			if(Iter_Count(IterPVAccessories[servervehicleid]) > 0)
				return SendClientMessage(playerid, -1, "Não é permitido vender o veículo com os acessórios. Remova-os!");*/
			
            DepositPropertie(playerid, valorrevenda);
			Player_AddMoney(playerid, valorrevenda);

			new model = GetVehicleModel(PlayerVehicleInfo[playerid][carroid][pvID]);

			new vehicle_name[30];
			GetModelStaticNameFromId(model, vehicle_name);

			format(string, sizeof string, "Você revendeu seu veículo {00FFFF}%s {FFFFFF}por {00AA00}$%s{FFFFFF}!", vehicle_name, getFormatText(valorrevenda));
			SendClientMessage(playerid, -1, string);
			format(string, sizeof string, "%s revendeu seu veículo %s por $%s!", PlayerName[playerid], vehicle_name, getFormatText(valorrevenda));
			server_log("vehicles", string);

			Player_RemoveVehicle(playerid, carroid);
		}
	    return 1;
	}
	else if (dialogid == 97) {
	    if (response) {
	        new carroid = SelectCarros[playerid][listitem],
				valorseguro = PlayerVehicleInfo[playerid][carroid][pvPrice] / 3;

			if (!Iter_Contains(IterPlayerVehicles[playerid], carroid))
			    return 1;

			if (Player_GetMoney(playerid) < valorseguro)
	  			return SendClientMessage(playerid, -1, "Você não possui dinheiro suficiênte!");

			if (PlayerVehicleInfo[playerid][carroid][pvInsurance]) {
			    return SendClientMessage(playerid, -1, "Seu veículo já possui seguro!");
			}
			PlayerVehicleInfo[playerid][carroid][pvInsurance] = 1;
   			Player_SaveVehicle(playerid, carroid);
			Player_RemoveMoney(playerid, valorseguro);

      		DepositPropertie(playerid, valorseguro);

			new vehicle_name[30];
			GetModelStaticNameFromId(GetVehicleModel(PlayerVehicleInfo[playerid][carroid][pvID]), vehicle_name);

			format(
				string, sizeof string, 
				"Seu {00FFFF}%s {FFFFFF}agora possui seguro, você pagará somente a franquia de {00AA00}$%s {FFFFFF}caso ela seja destruído!", 
				vehicle_name,
				getFormatText(PlayerVehicleInfo[playerid][carroid][pvPrice] / 17)
			);
			SendClientMessage(playerid, -1, string);
		}
	    return 1;
	}
	// else if(dialogid == 350) {
	// 	if(!response) 
	// 		return 1;

	// 	new vehicleid = SelectCarros[playerid][listitem], 
	// 		Float:pos[3], Float:rot[3], 
	// 		index = GetPVarInt(playerid, "vehicleItem"),
	// 		valid, type, modelid, quantidade, itemnome[75],
	// 		logMessage[128];

	// 	if (InvItem_GetQuantity(playerid, index) > 1)
	// 		return SendClientMessage(playerid, COLOR_LIGHTRED, "Você deve separar os acessórios antes de usá-los.");
		
	// 	getPlayerItemInfo(playerid, index, valid, type, modelid, quantidade, itemnome);

	// 	pos[2] = 1.2;

	// 	new accid = Player_CreateVehAccessory(playerid, vehicleid, modelid, 1, itemnome, pos, rot);
	// 	if(accid == -1) {
	// 		SendClientMessage(playerid, -1, "O seu veículo não comporta mais acessórios.");
	// 		if(Player_GetVIP(playerid) != SOCIO_EXTREME) {
	// 			SendClientMessage(playerid, -1, "Caso queira adicionar mais acessórios, confira as quantidades de acessórios para cada nível de VIP (/vip).");
	// 		}
	// 		return 1;
	// 	}

	// 	new vehicle_name[30];
	// 	GetModelStaticNameFromId(PlayerVehicleInfo[playerid][vehicleid][pvModel], vehicle_name);

	// 	format(
	// 		logMessage, sizeof(logMessage), 
	// 		"%s colocou o acessório %s no veículo %s [%d]", 
	// 		PlayerName[playerid], itemnome, 
	// 		PlayerVehicleInfo[playerid][vehicleid][pvModel], 
	// 		PlayerVehicleInfo[playerid][vehicleid][pvDBID]
	// 	);
	// 	server_log("acessorios_veiculares", logMessage);

	// 	InvItem_Reset(playerid, index);
	// 	Player_SaveVehicleAccessory(playerid, vehicleid, accid);
	// 	SetPVarInt(playerid, "editVehicleID", vehicleid);
	// 	OpenMenuEditorItem(playerid, accid, 3);
	// }
	// else if(dialogid == 352) {
	// 	if(!response) 
	// 		return 1;

	// 	new vehicleid = GetPVarInt(playerid, "selectedVehicleID"),
	// 		accessoryID = GetPVarInt(playerid, "selectedVehicleAcc");
		
	// 	if(listitem == 0) {
	// 		SetPVarInt(playerid, "editVehicleID", vehicleid);
	// 		OpenMenuEditorItem(playerid, accessoryID, 3);
	// 	}
	// 	else if(listitem == 1) {
	// 		if (InvItens_GetFreeSlots(playerid) < 1) 
	// 			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você está sem espaço no seu inventário.");

	// 		new servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID],
	// 			logMessage[128];

	// 		if(!Iter_Contains(IterPVAccessories[servervehicleid], accessoryID))
	// 			return SendClientMessage(playerid, COLOR_LIGHTRED, "Esse acessório não existe."); 

	// 		else if(!VehicleAccessoryInfo[servervehicleid][accessoryID][pvaRemovable])
	// 			return SendClientMessage(playerid, COLOR_LIGHTRED, "Esse acessório não pode ser guardado."); 

	// 		givePlayerItem(
	// 			playerid, 
	// 			ITEM_TYPE_VEH_ACCESSORY, 
	// 			VehicleAccessoryInfo[servervehicleid][accessoryID][pvaModel], 
	// 			1,
	// 			VehicleAccessoryInfo[servervehicleid][accessoryID][pvaName]
	// 		);
	// 		SendMsgF(playerid, COLOR_LIGHTBLUE, "Você guardou o acessório veicular %s no inventário.", VehicleAccessoryInfo[servervehicleid][accessoryID][pvaName]);

	// 		new vehicle_name[30];
	// 		GetModelStaticNameFromId(PlayerVehicleInfo[playerid][vehicleid][pvModel], vehicle_name);

	// 		format(
	// 			logMessage, sizeof(logMessage), 
	// 			"%s guardou o acessório %s do veículo %s [%d] no inventário", 
	// 			PlayerName[playerid], VehicleAccessoryInfo[servervehicleid][accessoryID][pvaName], 
	// 			vehicle_name, 
	// 			PlayerVehicleInfo[playerid][vehicleid][pvDBID]
	// 		);
	// 		server_log("acessorios_veiculares", logMessage);

	// 		Player_RemoveVehAccessory(playerid, vehicleid, accessoryID);
	// 	}
	// }
	else if(dialogid == 353) {
		if(!response)
			return 1;

		if(CheckChave(playerid, GetPlayerVehicleID(playerid))) return 1;
		new 
			bool:mot, 
			bool:lig, 
			bool:alar, 
			bool:door, 
			bool:bon, 
			bool:boot, 
			bool:obj;

		GetVehicleParamsEx(GetPlayerVehicleID(playerid), mot, lig, alar, door, bon, boot, obj);
		switch(listitem) {
			case 0: {
				callcmd::motor(playerid);
			}
			case 1: {
				if(!lig) {
					SendClientMessage(playerid, COR_ACAOCHAT, "* Você ligou o farol do veículo !");
					SetVehicleParamsEx(GetPlayerVehicleID(playerid), mot, true, alar, door, bon, boot, obj);
				}
				else {
					SendClientMessage(playerid, COR_ACAOCHAT, "* Você desligou o farol do veículo !");
					SetVehicleParamsEx(GetPlayerVehicleID(playerid), mot, false, alar, door, bon, boot, obj);
				}
			}
			case 2: {
				new carid = GetPlayerVehicleID(playerid);
				if (!HasPlayerVehicleKey(playerid, carid, 0)) 
					return SendClientMessage(playerid, -1, "Você não possui a chave desse veículo !");

				if(!alar) {
					SendClientMessage(playerid, COR_ACAOCHAT, "* Você ligou o alarme do veículo !");
					SetVehicleParamsEx(GetPlayerVehicleID(playerid), mot, lig, true, door, bon, boot, obj);
				}
				else {
					SendClientMessage(playerid, COR_ACAOCHAT, "* Você desligou o alarme do veículo !");
					SetVehicleParamsEx(GetPlayerVehicleID(playerid), mot, lig, false, door, bon, boot, obj);
				}
			}
			case 3: {
				if(!bon) {
					SendClientMessage(playerid, COR_ACAOCHAT, "* Você abriu o capô do veículo !");
					SetVehicleParamsEx(GetPlayerVehicleID(playerid), mot, lig, alar, door, true, boot, obj);
				}
				else {
					SendClientMessage(playerid, COR_ACAOCHAT, "* Você fechou o capô do veículo !");
					SetVehicleParamsEx(GetPlayerVehicleID(playerid), mot, lig, alar, door, false, boot, obj);
				}
			} 
			case 4: {
				if(!boot) {
					SendClientMessage(playerid, COR_ACAOCHAT, "* Você abriu o porta-malas do veículo !");
					SetVehicleParamsEx(GetPlayerVehicleID(playerid), mot, lig, alar, door, bon, true, obj);
				}
				else {
					SendClientMessage(playerid, COR_ACAOCHAT, "* Você fechou o porta-malas do veículo !");
					SetVehicleParamsEx(GetPlayerVehicleID(playerid), mot, lig, alar, door, bon, false, obj);
				}
			}
			case 5: {
				new bool:win[4];
				GetVehicleParamsCarWindows(GetPlayerVehicleID(playerid), win[0], win[1], win[2], win[3]);
				if(win[0]) {
					SendClientMessage(playerid, COR_ACAOCHAT, "* Você abriu as janelas do veículo !");
					SetVehicleParamsCarWindows(GetPlayerVehicleID(playerid), false, false, false, false);
				}
				else {
					SendClientMessage(playerid, COR_ACAOCHAT, "* Você fechou o janelas do veículo !");
					SetVehicleParamsCarWindows(GetPlayerVehicleID(playerid), true, true, true, true);
				}
			}
			case 6: {
				callcmd::trancar(playerid);
			}
		}
		if(IsPlayerInAnyVehicle(playerid))
			callcmd::menucarro(playerid);
	}
	return 1;
}

CMD:vestacionar(playerid, params[])
    return callcmd::veiculo(playerid, "estacionar");

CMD:vlocalizar(playerid, params[])
    return callcmd::veiculo(playerid, "localizar");

CMD:meusveiculos(playerid, params[])
    return callcmd::veiculo(playerid, "localizar");

CMD:vrevender(playerid, params[])
    return callcmd::veiculo(playerid, "revender");

CMD:veiculo(playerid, const params[]) {
	if (isnull(params)) {
	    SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /veiculo [Nome]");
	    SendClientMessage(playerid, -1, "Nomes disponíveis: Ajuda | Comprar | Revender | Localizar | Estacionar | Seguro | Acessorios | RemoverTunning");
	    return true;
	}

	new string[356], null[25];
	if (!strcmp(params, "ajuda", true)) {
		Help_List(playerid, 13);
	}
	else if (!strcmp(params, "comprar", true)) {
    	new vehid;
	    if ((vehid = GetPlayerVehicleID(playerid)) == INVALID_VEHICLE_ID || !IsPlayerInAnyVehicle(playerid)) {
			return SendClientMessage(playerid, -1, "Você precisa estar dentro do veículo para comprar !");
	    }
		for (new carro; carro < sizeof (CarrosConce); carro ++) {
		    if (vehid == CarrosConce[carro][ConceID]) {
				
				if (Player_GetVIP(playerid) < 1 && Player_CountVehicles(playerid) >= 1) {
				    return SendClientMessage(playerid, -1, "Apenas jogadores {00FFFF}VIP {FFFFFF}podem ter mais de {00FFFF}1 {FFFFFF}carros !"), RemovePlayerFromVehicle(playerid);
				}

				if (Player_GetVIP(playerid) < 5 && Player_CountVehicles(playerid) >= 2) {
				    return SendClientMessage(playerid, -1, "Apenas jogadores {00FFFF}SÓCIPREMIUMER {FFFFFF}podem ter mais de {00FFFF}2 {FFFFFF}carros !"), RemovePlayerFromVehicle(playerid);
				}

				if (Player_GetVIP(playerid) < 7 && Player_CountVehicles(playerid) >= 3) {
					return SendClientMessage(playerid, -1, "Apenas jogadores {00FFFF}SÓCIO-PLATINA {FFFFFF}podem ter mais de {00FFFF}3 {FFFFFF}carros !"), RemovePlayerFromVehicle(playerid);
				}
				
				if (Player_CountVehicles(playerid) >= 4) return SendClientMessage(playerid, -1, "Você atingiu o máximo de 4 veículos na sua conta."), RemovePlayerFromVehicle(playerid);
				
		        if (Player_GetNivel(playerid) < CarrosConce[carro][ConceNivel]) {
		            return SendClientMessage(playerid, -1, "Você não tem nível suficiênte !"), RemovePlayerFromVehicle(playerid);
		        }
		        
		        SetPVarInt(playerid, "buyVehicleID", carro), SetPVarInt(playerid, "idItemBuy", 18);
				
		        buyPlayerItem(playerid, 17, CarrosConce[carro][ConceValue]);
		        PagarICMS(CarrosConce[carro][ConceValue]); // Pagando imposto ao governo
		        return 1;
		    }
		}
		SendClientMessage(playerid, -1, "Você não pode comprar este veículo !");
	}
	else if (!strcmp(params, "localizar", true)) {
		new player_carro;
		MEGAString [0] = EOS;
		strcat(MEGAString, "ID\tCarro\tLocal\tDespesas\tVencimento\n");

        foreach(new carro : IterPlayerVehicles[playerid]) {
            new Float:x, Float:y, Float:z;
            GetVehiclePos(PlayerVehicleInfo[playerid][carro][pvID], x, y, z);

            new MapZone:zone = GetMapZoneAtPoint2D(x, y);
            new zone_name[MAX_MAP_ZONE_NAME];
            GetMapZoneName(zone, zone_name);

            new days = TimestampToRemainingDays(PlayerVehicleInfo[playerid][carro][pvDueDate]);

			new vehicle_name[30];
			GetModelStaticNameFromId(GetVehicleModel(PlayerVehicleInfo[playerid][carro][pvID]), vehicle_name);

            if (days <= 0) {
                format(
					string, sizeof string, 
					"{FFFFFF}%d\t{00FFFF}%s\t{FFFF00}%s\tIPVA e Documentos {00AA00}$%s {FFFFFF}\t{FF0000}VENCIDO\n",
					PlayerVehicleInfo[playerid][carro][pvID],
					vehicle_name, 
					zone_name,
               		getFormatText(PlayerVehicleInfo[playerid][carro][pvExpenses])
				);
            } else {
                format(
					string, sizeof string, 
					"{FFFFFF}%d\t{00FFFF}%s\t{FFFF00}%s\tIPVA e Documentos {00AA00}$%s {FFFFFF}\t%d dias\n", 
					PlayerVehicleInfo[playerid][carro][pvID],
					vehicle_name, 
					zone_name,
                	getFormatText(PlayerVehicleInfo[playerid][carro][pvExpenses]), days
				);
            }
            strcat(MEGAString, string);

            SelectCarros[playerid][player_carro] = carro;
            player_carro ++;
		}

		if (!player_carro) {
			return SendClientMessage(playerid, -1, "Você não tem nenhum veiculo.");
		}

		ShowPlayerDialog(playerid, 89, DIALOG_STYLE_TABLIST_HEADERS, "Localizar seus carros", MEGAString, "Localizar", "Fechar");
		return 1;
	}
	else if (!strcmp(params, "estacionar", true)) {

		return SendClientMessage(playerid, -1, "Veículo estacionar em manutenção.");
        // new vehid,
		// 	Float:healthVehicle;
			
	    // if ((vehid = GetPlayerVehicleID(playerid)) == INVALID_VEHICLE_ID || !IsPlayerInAnyVehicle(playerid)) 
        //     return SendClientMessage(playerid, -1, "Você precisa estar dentro do seu veículo para estacioná-lo !");

		// if (IsPlayerInSafeZone(playerid) && IsVehicleInDetran(GetPlayerVehicleID(playerid))) 
		// 	return SendClientMessage(playerid, -1, "Você não pode fazer isso em uma Área Segura.");

		// GetVehicleHealth(vehid, healthVehicle);

	    // if (healthVehicle < 800.0) {
	    //     return SendClientMessage(playerid, -1, "O veículo está com a lataria muito danificada, conserte antes de estaciona-lo.");
	    // }
	    
		// foreach(new carro : IterPlayerVehicles[playerid]) {
		//     if (PlayerVehicleInfo[playerid][carro][pvID] == vehid) {
		//         new vehDamageStatus[4];

		// 		GetVehiclePos(
		// 			PlayerVehicleInfo[playerid][carro][pvID], 
		// 			PlayerVehicleInfo[playerid][carro][pvPos][0], 
		// 			PlayerVehicleInfo[playerid][carro][pvPos][1], 
		// 			PlayerVehicleInfo[playerid][carro][pvPos][2]
		// 		);
		// 		GetVehicleZAngle(
		// 			PlayerVehicleInfo[playerid][carro][pvID],
		// 			PlayerVehicleInfo[playerid][carro][pvPos][3]
		// 		);
		// 		GetVehicleDamageStatus(
        //             PlayerVehicleInfo[playerid][carro][pvID], 
        //             vehDamageStatus[0], 
        //             vehDamageStatus[1], 
        //             vehDamageStatus[2], 
        //             vehDamageStatus[3]
        //         );

        //         PlayerVehicleInfo[playerid][carro][pvParked] = 1;
        //         Player_SaveVehicle(playerid, carro);

        //         //textDestroyVehicle(PlayerVehicleInfo[playerid][carro][pvID]);
		// 		removeVehicleText(PlayerVehicleInfo[playerid][carro][pvID]);
		// 		DestroyVehicle(PlayerVehicleInfo[playerid][carro][pvID]);
        //         PlayerVehicleInfo[playerid][carro][pvID] = CreateVehicle(
        //             PlayerVehicleInfo[playerid][carro][pvModel],
		// 		    PlayerVehicleInfo[playerid][carro][pvPos][0],
        //             PlayerVehicleInfo[playerid][carro][pvPos][1], 
        //             PlayerVehicleInfo[playerid][carro][pvPos][2],
        //             PlayerVehicleInfo[playerid][carro][pvPos][3],
		// 		    PlayerVehicleInfo[playerid][carro][pvColor][0], 
        //             PlayerVehicleInfo[playerid][carro][pvColor][1], 
        //             -1
        //         );
        //         Player_SetVehicleComponents(playerid, carro);
        //         PutPlayerInVehicle(playerid, PlayerVehicleInfo[playerid][carro][pvID], 0);
        //         SetVehicleHealth(
		// 			PlayerVehicleInfo[playerid][carro][pvID], 
		// 			PlayerVehicleInfo[playerid][carro][pvHealth]
		// 		);
        //         UpdateVehicleDamageStatus(
        //             PlayerVehicleInfo[playerid][carro][pvID],
        //             vehDamageStatus[0],
        //             vehDamageStatus[1],
        //             vehDamageStatus[2],
        //             vehDamageStatus[3]
        //         );

		// 		new MapZone:zone = GetMapZoneAtPoint2D(
        //             PlayerVehicleInfo[playerid][carro][pvPos][0], 
        //             PlayerVehicleInfo[playerid][carro][pvPos][1]
        //         );
		// 		new zone_name[MAX_MAP_ZONE_NAME];
		// 		GetMapZoneName(zone, zone_name);

		// 		new vehicle_name[30];
		// 		GetModelStaticNameFromId(GetVehicleModel(vehid), vehicle_name);

        //         format(string, sizeof string, "Você estacionou seu {00FFFF}%s {FFFFFF}em {FFFF00}%s. {FFFFFF}Agora ele irá nascer sempre aqui!", GetVehicleModel(vehid), zone_name);
		// 		SendClientMessage(playerid, -1, string);
		// 		return 1;
		// 	}
		// }
		// SendClientMessage(playerid, -1, "Este veículo não é seu !");
	}
	else if (!strcmp(params, "revender", true)) {
        if (!IsPlayerInRangeOfPoint(playerid, 2.0, 1167.8572,1342.1548,673.3744)) {
		    return SendClientMessage(playerid, -1, "Você não está na {00FFFF}Revendedora & Seguradora{FFFFFF}, use /gps para saber o local!");
		}

		new player_carro;
		MEGAString [0] = EOS;
		strcat(MEGAString, "Carro\tSeguro\tValor de revenda\n");

		new vehicle_name[30];
		foreach(new carro : IterPlayerVehicles[playerid]) {
			GetModelStaticNameFromId(GetVehicleModel(PlayerVehicleInfo[playerid][carro][pvID]), vehicle_name);

            format(
                string, 
                sizeof(string), 
                "{00FFFF}%s\t%s\t{00AA00}$%s\n",
                vehicle_name,
                PlayerVehicleInfo[playerid][carro][pvInsurance] ? ("{00AA00}Possui") : ("{FF0000}Não possui"),
                getFormatText(PlayerVehicleInfo[playerid][carro][pvPrice]/2)
            );
            strcat(MEGAString, string);

            SelectCarros[playerid][player_carro] = carro;
            player_carro ++;
		}
		if (player_carro > 0) {
			ShowPlayerDialog(playerid, 96, DIALOG_STYLE_TABLIST_HEADERS, "Revender seu veículo", MEGAString, "Revender", "Fechar");
		}
		else {
			SendClientMessage(playerid, -1, "Você não possui um veículo.");
		}
	}
	else if (!strcmp(params, "removertunning", true)) {
		new carro = Player_GetVehicleInRange(playerid, 5.00);
	    if (carro == -1) {
			return SendClientMessage(playerid, -1, "Você não está próximo de um veículo seu!");
	    }

		new vehid = PlayerVehicleInfo[playerid][carro][pvID];
		for(new component; component != 14; component++) {
			PlayerVehicleInfo[playerid][carro][pvComponent][component] = 0;
			RemoveVehicleComponent(vehid, GetVehicleComponentInSlot(vehid, component));
		}
		PlayerVehicleInfo[playerid][carro][pvComponent][14] = -1;
		ChangeVehiclePaintjob(vehid, 3);
		Player_SaveVehicle(playerid, carro);

		new vehicle_name[30];
		GetModelStaticNameFromId(GetVehicleModel(vehid), vehicle_name);
		
		format(string, sizeof string, "Você removeu o tunning do seu {00FFFF}%s {FFFFFF}!", vehicle_name);
		SendClientMessage(playerid, -1, string);
		return 1;
	}
	else if (!strcmp(params, "seguro", true)) {
		if (!IsPlayerInRangeOfPoint(playerid, 2.0, 1167.3950,1348.2433,673.3744)) {
		    return SendClientMessage(playerid, -1, "Você não está na {00FFFF}Revendedora & Seguradora{FFFFFF}, use /gps para saber o local!");
		}

		new player_carro;
		MEGAString [0] = EOS;
		strcat(MEGAString, "Nome do carro\tSeguro\tCusto do seguro\n");

		new valorseguro;
		new vehicle_name[30];

		foreach(new carro : IterPlayerVehicles[playerid]) {
			valorseguro = PlayerVehicleInfo[playerid][carro][pvPrice] / 3;
			GetModelStaticNameFromId(GetVehicleModel(PlayerVehicleInfo[playerid][carro][pvID]), vehicle_name);
            format(
                string, 
                sizeof(string), 
                "{00FFFF}%s\t%s\t{00AA00}$%s\n",
                vehicle_name,
                PlayerVehicleInfo[playerid][carro][pvInsurance] ? ("{00FF00}SIM") : ("{FF0000}NÃO"),
                getFormatText(valorseguro)
            );
            strcat(MEGAString, string);

            SelectCarros[playerid][player_carro] = carro;
            player_carro ++;
		}
		if (player_carro > 0) {
			ShowPlayerDialog(playerid, 97, DIALOG_STYLE_TABLIST_HEADERS, "Comprar seguro para seu veiculo", MEGAString, "Comprar", "Fechar");
		}
		else {
			SendClientMessage(playerid, -1, "Você não tem nenhum veiculo.");
		}
		return 1;
	}
	else if (strfind(params, "cor", true) != -1) {
        new vehid;
	    if ((vehid = GetPlayerVehicleID(playerid)) == INVALID_VEHICLE_ID || !IsPlayerInAnyVehicle(playerid)) {
			return SendClientMessage(playerid, -1, "Você precisa estar dentro do seu veículo para mudar a cor dele !");
	    }

		new VIM:vim = Vehicle_GetVIM(vehid);
		if (!Founders_GetList(playerid) && !VIM_IsBike(vim))
			return SendClientMessage(playerid, -1, "Para colocar cor em seu veículo, encontre uma Garagem de Tunning.");

		if (Player_GetMoney(playerid) < 1000 ) {
	    	SendClientMessage(playerid, -1, "Você não tem $1.000");
	    	return 1;
		}

		new setcolor1, setcolor2;
		if (sscanf(params, "s[25]dd", null, setcolor1, setcolor2)) {
	    	SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /veiculo Cor [cor1] [cor2]");
	    	SendClientMessage(playerid, -1, "O id da cor primária e secundário deve estar entre (-1 e 255)");
	    	return 1;
		}
		else if ((setcolor1 < -1 || setcolor1 > 255) || (setcolor2 < -1 || setcolor2 > 255)) {
	    	SendClientMessage(playerid, -1, "O id da cor primária e secundária deve estar entre (-1 e 255)");
	    	return 1;
		}

		new vehicle_name[30];

        foreach(new carro : IterPlayerVehicles[playerid]) {
		    if (PlayerVehicleInfo[playerid][carro][pvID] == vehid) {
				GetModelStaticNameFromId(GetVehicleModel(vehid), vehicle_name);
				SendMsgF(playerid, COLOR_WHITE, "Você mudou a cor do seu {00FFFF}%s {FFFFFF}(Cor primária: %d | Cor secundária: %d) -$1.000", vehicle_name, setcolor1, setcolor2);

				PlayerVehicleInfo[playerid][carro][pvColor][0] = setcolor1;
				PlayerVehicleInfo[playerid][carro][pvColor][1] = setcolor2;

				ChangeVehicleColor(vehid, setcolor1, setcolor2);
				Player_SaveVehicle(playerid, carro);
				return 1;
			}
		}
		SendClientMessage(playerid, -1, "Este veículo não é seu !");
	} 
	/*else if (!strcmp(params, "acessorios", true)) {

		new vehicleid = Player_GetVehicleInRange(playerid, 10.00);
	    if (vehicleid == -1) {
			return SendClientMessage(playerid, -1, "Você não está próximo de um veículo seu!");
	    }

		MEGAString[0] = EOS;
		strcat(MEGAString, "Slot\tNome\tRemovível?\n");

		new index;
		new servervehicleid = PlayerVehicleInfo[playerid][vehicleid][pvID];
		new SelectOptions[MAX_VEHICLE_ACCESSORIES];

		foreach(new acc : IterPVAccessories[servervehicleid]) {
			FormatCat(MEGAString, "{FFFFFF}%d\t{00FFFF}%s\t%s\n", acc+1, VehicleAccessoryInfo[servervehicleid][acc][pvaName], VehicleAccessoryInfo[servervehicleid][acc][pvaRemovable] ? ("{00FF00}SIM") : ("{FF0000}NÃO"));
			SelectOptions[index++] = acc;
		}

		new vehicle_name[30];
		GetModelStaticNameFromId(PlayerVehicleInfo[playerid][vehicleid][pvModel], vehicle_name);

		new title[60];
		format(title, sizeof(title), ""C_WHITE"Selecione o acessório do veículo: %s [%d/%d]", vehicle_name, index, PlayerVehicleInfo[playerid][vehicleid][pvMaxAccessories]);
		
		inline D_VehAcessories(did, ddialogid, dresponse, dlistitem, string:dtext[])
		{
			#pragma unused did, ddialogid, dtext
			if (!dresponse) return 1;

			new slot = SelectOptions[dlistitem];

			if (!Iter_Contains(IterPVAccessories[servervehicleid], slot))
				return SendClientMessage(playerid, COLOR_LIGHTRED, "Este veículo não possui acessório nesse slot.");

			SetPVarInt(playerid, "selectedVehicleAcc", slot);
			ShowPlayerDialog(
				playerid, 352, DIALOG_STYLE_TABLIST, 
				"O que deseja fazer com o acessório?", 
				VehicleAccessoryInfo[servervehicleid][slot][pvaRemovable] ? ("Editar\nGuardar no inventário") : ("Editar"), 
				"Selecionar", 
				"Fechar"
			);
		}
		Dialog_ShowCallback(playerid, using inline D_VehAcessories, DIALOG_STYLE_TABLIST_HEADERS, title, MEGAString, "Selecionar", "Cancelar");
	}*/
	else {
	    SendClientMessage(playerid, -1, "Nomes disponíveis: Ajuda | Comprar | Revender | Localizar | Estacionar | Seguro | Acessorios | RemoverTunning");
	}
	return 1;
}

CMD:verdonocarro(playerid, params[]) 
{
	if (Admin_GetNivel(playerid) < DONO) return 1;

	new vehicleid, idplayer, string[128];
	if (sscanf(params, "d", vehicleid)) {
		return SendClientMessage(playerid, -1, "Modo de uso: /verdonocarro (id do carro).");
	}

	foreach (new players : Player) {
		foreach(new carro : IterPlayerVehicles[playerid]) {
			if (PlayerVehicleInfo[playerid][carro][pvID] == vehicleid) {
				idplayer = players;
				break;
			}
		}
	}
	
	if (idplayer != INVALID_PLAYER_ID) {
		format(string, sizeof(string), "O dono do veículo %d é %s", vehicleid, PlayerName[idplayer]);
		SendClientMessage(playerid, -1, string);
	} else {
		SendClientMessage(playerid, -1, "Não é um veículo de concessionária");
	}

	return 1;
}

CMD:menucarro(playerid)
{
	if (!IsPlayerInAnyVehicle(playerid)) 
		return SendClientMessage(playerid, -1, "Você precisa estar em um veículo!");

	if (GetPlayerVehicleSeat(playerid) != 0) 
		return SendClientMessage(playerid, -1, "Você precisa ser o motorista do veículo.");

	new 
		bool:mot, 
		bool:lig, 
		bool:alar, 
		bool:door, 
		bool:bon, 
		bool:boot, 
		bool:obj,
		bool:win[4],
		Motor[32], Farol[32], Alarme[32], Capo[32], PortaMalas[32], Janelas[32], Chave[32];

	GetVehicleParamsEx(GetPlayerVehicleID(playerid), mot, lig, alar, door, bon, boot, obj);
	GetVehicleParamsCarWindows(GetPlayerVehicleID(playerid), win[0], win[1], win[2], win[3]);
	
	new string[1024];
	if(mot) Motor = "{00FF00}Ligado";
	else Motor = "{FF0000}Desligado";

	if(lig) Farol = "{00FF00}Ligado";
	else Farol = "{FF0000}Desligado";

	if(alar) Alarme = "{00FF00}Ligado";
	else Alarme = "{FF0000}Desligado";

	if(bon) Capo = "{00FF00}Aberto";
	else Capo = "{FF0000}Fechado";

	if(boot) PortaMalas = "{00FF00}Aberto";
	else PortaMalas = "{FF0000}Fechado";

	if(!win[0]) Janelas = "{00FF00}Abertas";
	else Janelas = "{FF0000}Fechadas";

	if(!IsVehicleLocked(GetPlayerVehicleID(playerid))) Chave = "{00FF00}Destrancado";
	else Chave = "{FF0000}Trancado";

	format(
		string, 1024, 
		"Parte\tStatus\n{FFFFFF}Motor\t%s\n{FFFFFF}Farol\t%s\n{FFFFFF}Alarme\t%s\n{FFFFFF}Capô\t%s\n{FFFFFF}Porta-malas\t%s\n{FFFFFF}Janelas\t%s\n{FFFFFF}Fechadura\t%s", 
		Motor, Farol, Alarme, Capo, PortaMalas, Janelas, Chave
	);
	ShowPlayerDialog(playerid, 353, DIALOG_STYLE_TABLIST_HEADERS, "Menu do Veículo", string, "Selecionar", "Fechar");
	return 1;
}