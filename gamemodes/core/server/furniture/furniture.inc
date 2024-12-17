#include <YSI_Coding\y_hooks>

#include <furniture_entry>

static Iterator:FurnituresHouse[MAX_HOUSES]<MAX_FURNITURE>;

// ------------------- Sistema de mobiliar casas -------------------
static 
    Statement: stmt_createFurniture,
	Statement: stmt_destroyFurniture,
    Statement: stmt_selectFurniture,
	Statement: stmt_updateFurniture,
	Statement: stmt_destroyAllFurniture;

stock OnMySQLConnected_Furniture() {
    static const query_createFurniture[] = 
		"INSERT INTO `house_furniture` \
            (`house`, `model`, `posX`, `posY`, `posZ`, `rotX`, `rotY`, `rotZ`, `created`)  \
        VALUES \
            (?, ?, ?, ?, ?, ?, ?, ?, ?) \
        ";
	stmt_createFurniture = MySQL_PrepareStatement(MySQL_Handle, query_createFurniture);

    static const query_selectFurniture[] = "SELECT id, house, model, posX, posY, posZ, rotX, rotY, rotZ, created \
											FROM `house_furniture` \
											ORDER BY house";
	stmt_selectFurniture = MySQL_PrepareStatement(MySQL_Handle, query_selectFurniture);

	static const query_updateFurniture[] = "UPDATE `house_furniture` \
											SET posX = ?, posY = ?, posZ = ?, rotX = ?, rotY = ?, rotZ = ?, created = ? WHERE `id` = '?'";
	stmt_updateFurniture = MySQL_PrepareStatement(MySQL_Handle, query_updateFurniture);

	static const query_destroyFurniture[] = "DELETE FROM `house_furniture` WHERE `id` = '?'";
	stmt_destroyFurniture = MySQL_PrepareStatement(MySQL_Handle, query_destroyFurniture);

	static const query_destroyAllFurniture[] = "DELETE FROM `house_furniture` WHERE `house` = '?'";
	stmt_destroyAllFurniture = MySQL_PrepareStatement(MySQL_Handle, query_destroyAllFurniture);

	return 1;
}

// hook OP_EditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) 
// {
// 	new house = Player_GetInHouse(playerid);

// 	foreach (new furniture : FurnituresHouse[house]) {
// 		if (objectid == FurnitureHouse_GetObject(house, furniture)) {
// 			if (response == 0) {
// 				ShowPlayerBaloonInfo(playerid, "Voce removeu o movel dessa casa", 7000);
// 				Furniture_Remove(house, furniture);
// 			} else if (response == 1) {
// 				if (IsPlayerInRangeOfPoint(playerid, 50.0, House_GetExitX(house), House_GetExitY(house), House_GetExitZ(house)))
// 					return SendClientMessage(playerid, -1, "Você está longe do interior da casa.");
				
// 				FurnitureHouse_SetPosX(house, furniture, x);
// 				FurnitureHouse_SetPosY(house, furniture, y);
// 				FurnitureHouse_SetPosZ(house, furniture, z);
// 				FurnitureHouse_SetRotX(house, furniture, rx);
// 				FurnitureHouse_SetRotY(house, furniture, ry);
// 				FurnitureHouse_SetRotZ(house, furniture, rz);
// 				FurnitureHouse_UpdateObject(house, furniture, x, y, z, rx, ry, rz);
// 				Furniture_Save(house, furniture);
// 			}
// 		}
// 	}
// 	return 1;
// }

CALLBACK:OnLoadFurnitureHouses() 
{
	inline const OnLoadFurnitureHouse() {
		new furniture,
			house,
			model,
			Float:posX,
			Float:posY,
			Float:posZ,
			Float:rotX,
			Float:rotY,
			Float:rotZ;

		while (MySQL_Statement_FetchRow(stmt_selectFurniture)) {
			MySQL_BindResultInt(stmt_selectFurniture, 0, furniture);
			MySQL_BindResultInt(stmt_selectFurniture, 1, house);
			MySQL_BindResultInt(stmt_selectFurniture, 2, model);
			MySQL_BindResultFloat(stmt_selectFurniture, 3, posX);
			MySQL_BindResultFloat(stmt_selectFurniture, 4, posY);
			MySQL_BindResultFloat(stmt_selectFurniture, 5, posZ);
			MySQL_BindResultFloat(stmt_selectFurniture, 6, rotX);
			MySQL_BindResultFloat(stmt_selectFurniture, 7, rotY);
			MySQL_BindResultFloat(stmt_selectFurniture, 8, rotZ);

			FurnitureHouse_Create(furniture, house, model, posX, posY, posZ, rotX, rotY, rotZ);
		}
	}
    MySQL_ExecuteThreaded_Inline(stmt_selectFurniture, using inline OnLoadFurnitureHouse);
	return 1;
}

stock FurnitureHouse_Create(furniture, house, model, Float:posX, Float:posY, Float:posZ, Float:rotX, Float:rotY, Float:rotZ)
{
	new id = Iter_Free(FurnituresHouse[house]);

	if (id != -1) {
		Iter_Add(FurnituresHouse[house], id);

		FurnitureHouse_SetID(house, id, furniture);
		FurnitureHouse_SetModel(house, id, model);
		FurnitureHouse_SetPosX(house, id, posX);
		FurnitureHouse_SetPosY(house, id, posY);
		FurnitureHouse_SetPosZ(house, id, posZ);
		FurnitureHouse_SetRotX(house, id, rotX);
		FurnitureHouse_SetRotY(house, id, rotY);
		FurnitureHouse_SetRotZ(house, id, rotZ);

		FurnitureHouse_CreateObject(house, id, model, posX, posY, posZ, rotX, rotY, rotZ);
		return id;
	}
	return -1;
}

stock FurnitureHouse_Insert(house, model, Float:posX, Float:posY, Float:posZ, Float:rotX, Float:rotY, Float:rotZ) 
{
	new id = -1;

	inline OnFurnitureCreated() {
		id = cache_insert_id();
		FurnitureHouse_Create(id, house, model, posX, posY, posZ, rotX, rotY, rotZ);
	}
	MySQL_BindInt(stmt_createFurniture, 0, house);
	MySQL_BindInt(stmt_createFurniture, 1, model);
	MySQL_BindFloat(stmt_createFurniture, 2, posX);
	MySQL_BindFloat(stmt_createFurniture, 3, posY);
	MySQL_BindFloat(stmt_createFurniture, 4, posZ);
	MySQL_BindFloat(stmt_createFurniture, 5, rotX);
	MySQL_BindFloat(stmt_createFurniture, 6, rotY);
	MySQL_BindFloat(stmt_createFurniture, 7, rotZ);
	MySQL_ExecuteThreaded_Inline(stmt_createFurniture, using inline OnFurnitureCreated);

	return id;
}

stock Furniture_Remove(house, furniture) {
	if (Iter_Contains(FurnituresHouse[house], furniture)) {
		DestroyDynamicObject(FurnitureHouse_GetObject(house, furniture));

		Iter_Remove(FurnituresHouse[house], furniture);

		MySQL_BindInt(stmt_destroyFurniture, 0, FurnitureHouse_GetID(house, furniture));
		MySQL_ExecuteThreaded(stmt_destroyFurniture);
	}
}

stock Furniture_Save(house, furniture) {
	MySQL_BindFloat(stmt_updateFurniture, 0, FurnitureHouse_GetPosX(house, furniture));
	MySQL_BindFloat(stmt_updateFurniture, 1, FurnitureHouse_GetPosY(house, furniture));
	MySQL_BindFloat(stmt_updateFurniture, 2, FurnitureHouse_GetPosZ(house, furniture));
	MySQL_BindFloat(stmt_updateFurniture, 3, FurnitureHouse_GetRotX(house, furniture));
	MySQL_BindFloat(stmt_updateFurniture, 4, FurnitureHouse_GetRotY(house, furniture));
	MySQL_BindFloat(stmt_updateFurniture, 5, FurnitureHouse_GetRotZ(house, furniture));
	MySQL_BindInt(stmt_updateFurniture, 6, FurnitureHouse_GetID(house, furniture));
	MySQL_ExecuteThreaded(stmt_updateFurniture);
}

stock Furniture_Count(house) {
	return Iter_Count(FurnituresHouse[house]);
}

stock Furniture_Reset(house) {
	foreach(new furniture : FurnituresHouse[house]) {
		DestroyDynamicObject(MobInfo[houseid][x][mobObject]);
	}
	MySQL_BindInt(stmt_destroyAllFurniture, 0, houseid);
	MySQL_ExecuteThreaded(stmt_destroyAllFurniture);

	Iter_Clear(FurnituresHouse[houseid]);
}

stock Furniture_ShowNear(playerid) {
	new house = Player_GetInHouse(playerid),
		index = 0,
		string[128];

	MEGAString[0] = EOS;

	strcat(MEGAString, "ID do Objeto\tDistância\n");
	
	foreach(new furniture : FurnituresHouse[house]) {
		new Float:dist = GetPlayerDistanceFromPoint(
			playerid, FurnitureHouse_GetPosX(house, furniture), FurnitureHouse_GetPosY(house, furniture), FurnitureHouse_GetPosZ(house, furniture)
		);
		if(dist <= 8.0) {
			format(string, sizeof (string), "%d\t%.2f metros\n", FurnitureHouse_GetModel(house, furniture), dist);
			strcat(MEGAString, string);
			ListOptions[playerid][index] = furniture;
			index += 1;
		}
	}

	inline D_SelectFurnitureAction(dyid, dydialogid, dyresponse, dylistitem, string:dytext[])
	{
		#pragma unused dyid, dydialogid, dytext, dyresponse
		if(!dyresponse)
			return 1;

		new furnitureId = GetPVarInt(playerid, "editMovel");
		if (!Iter_Contains(FurnituresHouse[house], furnitureId))
			return SendClientMessage(playerid, -1, "Móvel inválido."), Furniture_ShowNear(playerid);

		if(dylistitem == 0) {
			OpenMenuEditorItem(playerid, furnitureId, 2);
		}
		else {
			ShowPlayerBaloonInfo(playerid, "Voce removeu o movel dessa casa", 7000);
			Furniture_Remove(house, furnitureId);
			Furniture_ShowNear(playerid);
		}
		return 1;
	}

	inline D_SelectFurniture(dyid, dydialogid, dyresponse, dylistitem, string:dytext[])
	{
		#pragma unused dyid, dydialogid, dytext, dyresponse
		if(!dyresponse)
			return 1;

		new furnitureId = ListOptions[playerid][dylistitem];
		if (!Iter_Contains(FurnituresHouse[house], furnitureId))
			return SendClientMessage(playerid, -1, "Móvel inválido."), Furniture_ShowNear(playerid);

		SetPVarInt(playerid, "editHouseID", house);
		SetPVarInt(playerid, "editMovel", furnitureId);

		Dialog_ShowCallback(
			playerid, using inline D_SelectFurnitureAction, DIALOG_STYLE_LIST, 
			"O que deseja fazer com esse movel?", 
			"Editar\nRemover", 
			"Selecionar", 
			""C_WARNING"Fechar"
		);
		return 1;
	}

	format(string, sizeof(string), C_BLUELIGHT"Móveis próximos [%d]", index);
	Dialog_ShowCallback(playerid, using inline D_SelectFurniture, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Selecionar", ""C_WARNING"Fechar");
	return 1;
}

stock isMovelRoubavel(modelid) {
	switch(modelid)
	{
	    case 14705,14772,1429,1518,2595,14532,2654,19055,19056,19058,932,
		1663,1704,1705,1708,1735,1811,2096,1954,2121,2123,2240,2069,2176,2701,
		2103,2077,2777,2225,2811,1815,2855,1782,1783,1785,1787,1788,1790,19587,
		19573,19572,19933,19999,19893,19894,19878,19830,19831,19806,19805,19786,
		19787,19624,19616,19615,19614,19613,19612,19611,19592: return true;
	}
	return false;
}

stock getFogaoPerto(playerid) 
{
	new house = Player_GetInHouse(playerid);

	if (House_IsValid(house)) {
	    foreach (new furniture : FurnituresHouse) {
	        if (IsPlayerInRangeOfPoint(playerid, 1.8, Furniture_GetPosX(house, furniture), Furniture_GetPosY(house, furniture), Furniture_GetPosZ(house, furniture)) &&
				isMovelCooker(Furniture_GetModel(house, furniture)))
	            return Furniture_GetID(house, furniture);
	    }
	}
	return -1;
}

stock isMovelCooker(modelid) 
{
	switch(modelid) {
	    case 19915: 
			return true;
	}
	return false;
}

stock getMovelPerto(playerid) 
{
	new house = Player_GetInHouse(playerid);

	if (House_IsValid(house)) 
	{
		if (House_GetOwner(house) == Player_GetAccountID(playerid)) 
			return false;

	    foreach(new furniture : FurnituresHouse[house]) {
	        if (IsPlayerInRangeOfPoint(playerid, 1.8, Furniture_GetPosX(house, furniture), Furniture_GetPosY(house, furniture), Furniture_GetPosZ(house, furniture)) && 
				isMovelRoubavel(Furniture_GetModel(house, furniture)))
	            return furniture;
	    }
	}
	return false;
}

hook OP_SelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z){

	foreach (new house : Houses)
	{
		if (House_GetOwner(house) == Player_GetAccountID(playerid) || 
			House_GetDesigner(house) == Player_GetAccountID(playerid)) {

			foreach(new furniture : FurnituresHouse[house])
			{
				if (objectid == FurnitureHouse_GetObject(house, furniture))
				{
		            SetPVarInt(playerid, "editHouseID", house);
		            SetPVarInt(playerid, "editMovel", furniture);

					if (IsAndroidPlayer(playerid))
						OpenMenuEditorItem(playerid, furniture, 2);
					else {
						ShowPlayerBaloonInfo(playerid, "Use os comandos para alterar o movel. Para remove-lo, aperte ESC", 7000);
						EditDynamicObject(playerid, FurnitureHouse_GetObject(house, furniture));
					}
					return 1;
		        }
		    }
		}
	}
	return 1;
}

hook OnModelSelectionResponse(playerid, extraid, index, modelid, response) 
{
	if (extraid >= 3 || extraid <= 8)
	{
	    if (response)
		{
	        new	Float:posX, 
				Float:posY, 
				Float:posZ,
				Float:rotX,
				Float:rotY,
				Float:rotZ,
				house = Player_GetInHouse(playerid);
			
			if (Furniture_Count(house) >= House_GetMaxFurniture(house))
				return SendClientMessage(playerid, -1, "Sua casa atingiu o limite máximo de móveis. Seja um sócio para aumentar a quantidade.");

	        GetPlayerPos(playerid, posX, posY, posZ);
	        GetXYInFrontOfPlayer(playerid, posX, posY, 1.5);

			new id = FurnitureHouse_Insert(house, modelid, posX, posY, posZ, rotX, rotY, rotZ);
			Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

			SendMsgF(playerid, COLOR_ORANGE, "Você acabou de usar um móvel da casa [%d/%d]", Furniture_Count(house), House_GetMaxFurniture(house));

			if (id != -1) {
				if (IsAndroidPlayer(playerid))
					OpenMenuEditorItem(playerid, id, 2);
				else
					EditDynamicObject(playerid, FurnitureHouse_GetObject(house, id));
			}
		}
	    else SendClientMessage(playerid, -1, "Você cancelou o menu de Móveis!");
	}
	return 1;
}