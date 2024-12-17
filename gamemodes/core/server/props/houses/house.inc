#include <YSI_Coding\y_hooks>

#include <house_entry>
#include <furniture>
#include <house_cmds>

// ------------------------ Sistema de casas ------------------------
static Iterator: OwnerHouses[MAX_PLAYERS]<MAX_PLAYER_HOUSES>;
static Iterator: DesignerHouses[MAX_PLAYERS]<MAX_HOUSE_DESIGNER>;
static Iterator: TenantHouses[MAX_PLAYERS]<2>;

static 
		Statement: stmt_insertHouse,
		Statement: stmt_selectHouses,
		Statement: stmt_selectOwnerHouses,
		Statement: stmt_selectDesignerHouses,
		Statement: stmt_selectTenantHouses,
		Statement: stmt_updateHouse;
		// Statement: stmt_deleteHouse;

hook OnMySQLConnected() 
{
	static const query_insertHouse[] = 
		"INSERT INTO `houses` (`id`, `owner`, `entry_x`, `entry_y`, `entry_z`, `exit_x`, `exit_y`, `exit_z`, `entry_rot`, `level`, \
		`value_type`, `value`, `interior`, `world`, `lock`, `status`, `expenses`, `designer`, `tenant`, `rental_value`, `maturity`, `max_furniture`) \
		VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
	;
	stmt_insertHouse = MySQL_PrepareStatement(MySQL_Handle, query_insertHouse);

	static const query_selectHouses[] = 
		"SELECT h.*,  \
			(SELECT nome FROM player WHERE id = h.owner) AS ownerName, \
			(SELECT nome FROM player WHERE id = h.designer) AS designerName, \
			(SELECT nome FROM player WHERE id = h.tenant) AS tenantName \
		FROM houses h \
		ORDER BY h.id ASC  \
		LIMIT 1000"
	;
	stmt_selectHouses = MySQL_PrepareStatement(MySQL_Handle, query_selectHouses);

	static const query_selectOwnerHouses[] = 
		"SELECT id FROM `houses` WHERE `owner` = ? ORDER BY id ASC LIMIT ?"
	;
	stmt_selectOwnerHouses = MySQL_PrepareStatement(MySQL_Handle, query_selectOwnerHouses);

	static const query_selectDesignerHouses[] = 
		"SELECT id FROM `houses` WHERE `designer` = ? ORDER BY id ASC LIMIT ?"
	;
	stmt_selectDesignerHouses = MySQL_PrepareStatement(MySQL_Handle, query_selectDesignerHouses);

	static const query_selectTenantHouses[] = 
		"SELECT id FROM `houses` WHERE `tenant` = ? ORDER BY id ASC LIMIT 1"
	;
	stmt_selectTenantHouses = MySQL_PrepareStatement(MySQL_Handle, query_selectTenantHouses);

	static const query_updateHouse[] = 
		"UPDATE `houses` SET `owner` = ?, `entry_x` = ?, `entry_y` = ?, `entry_z` = ?, `exit_x` = ?, `exit_y` = ?, `exit_z` = ?, \
		`entry_rot` = ?, `level` = ?, `value_type` = ?, `value` = ?, `interior` = ?, `world` = ?, `lock` = ?, `status` = ?, `expenses` = ?, \
		`designer` = ?, `tenant` = ?, `rental_value` = ?, `maturity` = ?, `max_furniture` = ? WHERE `id` = ?"
	;
	stmt_updateHouse = MySQL_PrepareStatement(MySQL_Handle, query_updateHouse);

	// static const query_deleteHouse[] = 
	// 	"DELETE FROM `houses` WHERE `id` = ?"
	// ;
	// stmt_deleteHouse = MySQL_PrepareStatement(MySQL_Handle, query_deleteHouse);

	OnMySQLConnected_Furniture();
	return 1;
}

hook OnGameModeInit()
{
	inline const OnLoadHouses() 
	{
		new id,
			owner,
			Float:entry_x,
			Float:entry_y,
			Float:entry_z,
			Float:exit_x,
			Float:exit_y,
			Float:exit_z,
			Float:entry_rot,
			level,
			value_type,
			value,
			interior,
			world,
			bool:lock,
			status,
			expenses,
			designer,
			tenant,
			rental_value,
			maturity[30],
			max_furniture,
			owner_name[MAX_PLAYER_NAME],
			designer_name[MAX_PLAYER_NAME],
			tenant_name[MAX_PLAYER_NAME];

		MySQL_BindResultInt(stmt_selectHouses, 0, id);
		MySQL_BindResultInt(stmt_selectHouses, 1, owner);
		MySQL_BindResultFloat(stmt_selectHouses, 2, entry_x);
		MySQL_BindResultFloat(stmt_selectHouses, 3, entry_y);
		MySQL_BindResultFloat(stmt_selectHouses, 4, entry_z);
		MySQL_BindResultFloat(stmt_selectHouses, 5, exit_x);
		MySQL_BindResultFloat(stmt_selectHouses, 6, exit_y);
		MySQL_BindResultFloat(stmt_selectHouses, 7, exit_z);
		MySQL_BindResultFloat(stmt_selectHouses, 8, entry_rot);
		MySQL_BindResultInt(stmt_selectHouses, 9, level);
		MySQL_BindResultInt(stmt_selectHouses, 10, value_type);
		MySQL_BindResultInt(stmt_selectHouses, 11, value);
		MySQL_BindResultInt(stmt_selectHouses, 12, interior);
		MySQL_BindResultInt(stmt_selectHouses, 13, world);
		MySQL_BindResultInt(stmt_selectHouses, 14, lock);
		MySQL_BindResultInt(stmt_selectHouses, 15, status);
		MySQL_BindResultInt(stmt_selectHouses, 16, expenses);
		MySQL_BindResultInt(stmt_selectHouses, 17, designer);
		MySQL_BindResultInt(stmt_selectHouses, 18, tenant);
		MySQL_BindResultInt(stmt_selectHouses, 19, rental_value);
		MySQL_BindResult(stmt_selectHouses, 20, maturity);
		MySQL_BindResultInt(stmt_selectHouses, 21, max_furniture);
		MySQL_BindResult(stmt_selectHouses, 22, owner_name);
		MySQL_BindResult(stmt_selectHouses, 23, designer_name);
		MySQL_BindResult(stmt_selectHouses, 24, tenant_name);

		while (MySQL_Statement_FetchRow(stmt_selectHouses)) {
			House_Create(id, owner, owner_name, entry_x, entry_y, entry_z, exit_x, exit_y, exit_z, entry_rot, level, value_type, value, 
						interior, world, lock, status, expenses, designer, designer_name, tenant, tenant_name, rental_value, maturity, max_furniture);
		}

		new count = Iter_Count(Houses);
		printf("[Houses]: %d loaded...", count);
	}
	MySQL_BindInt(stmt_selectHouses, 0, MAX_HOUSES);
	MySQL_ExecuteThreaded_Inline(stmt_selectHouses, using inline OnLoadHouses);

	CallRemoteFunction("OnLoadFurnitureHouses", "");
	return 1;
}

hook OnPlayerLogin(playerid) 
{
	House_ReloadOwner(playerid);
	House_ReloadDesigner(playerid);
	House_ReloadTenant(playerid);
}

hook OnPlayerDisconnect(playerid) 
{
   	Iter_Clear(OwnerHouses[playerid]);
   	Iter_Clear(DesignerHouses[playerid]);
   	Iter_Clear(TenantHouses[playerid]);
	return 1;
}

stock House_IsValid(house) {
	if ((house < 0 || house > MAX_HOUSES) || !Iter_Contains(Houses, house)) return false;
	return true;
}

stock House_ReloadOwner(playerid) {
	Iter_Clear(OwnerHouses[playerid]);

	inline const OnLoadPlayerOwnerHouse() 
	{
		new id,
			house;

		MySQL_BindResultInt(stmt_selectOwnerHouses, 0, house);

		while (MySQL_Statement_FetchRow(stmt_selectOwnerHouses)) {
			id = Iter_Free(OwnerHouses[playerid]);
			if (id != -1)
				Iter_Add(OwnerHouses[playerid], house);
		}
	}
	MySQL_BindInt(stmt_selectOwnerHouses, 0, Player_GetAccountID(playerid));
	MySQL_BindInt(stmt_selectOwnerHouses, 1, MAX_PLAYER_HOUSES);
	MySQL_ExecuteThreaded_Inline(stmt_selectOwnerHouses, using inline OnLoadPlayerOwnerHouse);

}

stock House_ReloadDesigner(playerid) {
	Iter_Clear(DesignerHouses[playerid]);

	inline const OnLoadPlayerDesignerHouse() 
	{
		new id,
			house;

		MySQL_BindResultInt(stmt_selectDesignerHouses, 0, house);

		while (MySQL_Statement_FetchRow(stmt_selectDesignerHouses)) {
			id = Iter_Free(DesignerHouses[playerid]);
			if (id != -1)
				Iter_Add(DesignerHouses[playerid], house);
		}
	}
	MySQL_BindInt(stmt_selectDesignerHouses, 0, Player_GetAccountID(playerid));
	MySQL_BindInt(stmt_selectDesignerHouses, 1, MAX_HOUSE_DESIGNER);
	MySQL_ExecuteThreaded_Inline(stmt_selectDesignerHouses, using inline OnLoadPlayerDesignerHouse);
}

stock House_ReloadTenant(playerid) {
	Iter_Clear(TenantHouses[playerid]);

	inline const OnLoadPlayerTenantHouse() 
	{
		new id,
			house;

		MySQL_BindResultInt(stmt_selectTenantHouses, 0, house);

		while (MySQL_Statement_FetchRow(stmt_selectTenantHouses)) {
			id = Iter_Free(TenantHouses[playerid]);
			if (id != -1)
				Iter_Add(TenantHouses[playerid], house);
		}
	}
	MySQL_BindInt(stmt_selectTenantHouses, 0, Player_GetAccountID(playerid));
	MySQL_ExecuteThreaded_Inline(stmt_selectTenantHouses, using inline OnLoadPlayerTenantHouse);
}

stock House_Insert(house)
{	
	MySQL_BindInt(stmt_insertHouse, 0, house);

	if (House_GetOwner(house) == 0)
		MySQL_Bind(stmt_insertHouse, 1, "NULL", true);
	else
		MySQL_BindInt(stmt_insertHouse, 1, House_GetOwner(house));

	MySQL_BindFloat(stmt_insertHouse, 2, House_GetEntryX(house));
	MySQL_BindFloat(stmt_insertHouse, 3, House_GetEntryY(house));
	MySQL_BindFloat(stmt_insertHouse, 4, House_GetEntryZ(house));
	MySQL_BindFloat(stmt_insertHouse, 5, House_GetExitX(house));
	MySQL_BindFloat(stmt_insertHouse, 6, House_GetExitY(house));
	MySQL_BindFloat(stmt_insertHouse, 7, House_GetExitZ(house));
	MySQL_BindFloat(stmt_insertHouse, 8, House_GetEntryRot(house));
	MySQL_BindInt(stmt_insertHouse, 9, House_GetNivel(house));
	MySQL_BindInt(stmt_insertHouse, 10, House_GetValueType(house));
	MySQL_BindInt(stmt_insertHouse, 11, House_GetValue(house));
	MySQL_BindInt(stmt_insertHouse, 12, House_GetInterior(house));
	MySQL_BindInt(stmt_insertHouse, 13, House_GetWorld(house));
	MySQL_BindInt(stmt_insertHouse, 14, House_GetLock(house));
	MySQL_BindInt(stmt_insertHouse, 15, House_GetStatus(house));
	MySQL_BindInt(stmt_insertHouse, 16, House_GetExpenses(house));

	if (House_GetDesigner(house) == 0)
		MySQL_Bind(stmt_insertHouse, 17, "NULL", true);
	else
		MySQL_BindInt(stmt_insertHouse, 17, House_GetDesigner(house));
		
	if (House_GetTenant(house) == 0)
		MySQL_Bind(stmt_insertHouse, 18, "NULL", true);
	else
		MySQL_BindInt(stmt_insertHouse, 18, House_GetTenant(house));
	
	MySQL_BindInt(stmt_insertHouse, 19, House_GetRentalValue(house));

	new date[30];
	TimeFormat(House_GetMaturity(house), MYSQL_TIMESTAMP, date);
	MySQL_Bind(stmt_insertHouse, 20, date);

	MySQL_BindInt(stmt_insertHouse, 21, House_GetMaxFurniture(house));
	MySQL_ExecuteParallel(stmt_insertHouse);
}

stock House_Save(house)
{	
	if (House_GetOwner(house) == 0)
		MySQL_Bind(stmt_updateHouse, 0, "NULL", true);
	else
		MySQL_BindInt(stmt_updateHouse, 0, House_GetOwner(house));

	MySQL_BindFloat(stmt_updateHouse, 1, House_GetEntryX(house));
	MySQL_BindFloat(stmt_updateHouse, 2, House_GetEntryY(house));
	MySQL_BindFloat(stmt_updateHouse, 3, House_GetEntryZ(house));
	MySQL_BindFloat(stmt_updateHouse, 4, House_GetExitX(house));
	MySQL_BindFloat(stmt_updateHouse, 5, House_GetExitY(house));
	MySQL_BindFloat(stmt_updateHouse, 6, House_GetExitZ(house));
	MySQL_BindFloat(stmt_updateHouse, 7, House_GetEntryRot(house));
	MySQL_BindInt(stmt_updateHouse, 8, House_GetNivel(house));
	MySQL_BindInt(stmt_updateHouse, 9, House_GetValueType(house));
	MySQL_BindInt(stmt_updateHouse, 10, House_GetValue(house));
	MySQL_BindInt(stmt_updateHouse, 11, House_GetInterior(house));
	MySQL_BindInt(stmt_updateHouse, 12, House_GetWorld(house));
	MySQL_BindInt(stmt_updateHouse, 13, House_GetLock(house));
	MySQL_BindInt(stmt_updateHouse, 14, House_GetStatus(house));
	MySQL_BindInt(stmt_updateHouse, 15, House_GetExpenses(house));

	if (House_GetDesigner(house) == 0)
		MySQL_Bind(stmt_updateHouse, 16, "NULL", true);
	else
		MySQL_BindInt(stmt_updateHouse, 16, House_GetDesigner(house));
		
	if (House_GetTenant(house) == 0)
		MySQL_Bind(stmt_updateHouse, 17, "NULL", true);
	else
		MySQL_BindInt(stmt_updateHouse, 17, House_GetTenant(house));
	
	MySQL_BindInt(stmt_updateHouse, 18, House_GetRentalValue(house));

	new date[30];
	TimeFormat(House_GetMaturity(house), MYSQL_TIMESTAMP, date);
	MySQL_Bind(stmt_updateHouse, 19, date);

	MySQL_BindInt(stmt_updateHouse, 20, House_GetMaxFurniture(house));
	MySQL_BindInt(stmt_updateHouse, 21, house);
	MySQL_ExecuteThreaded(stmt_updateHouse);
}

stock House_Create(id, owner, const owner_name[], Float:entry_x, Float:entry_y, Float:entry_z, Float:exit_x, Float:exit_y, Float:exit_z, Float:entry_rot, 
					level, value_type, value, interior, world, bool:lock, status, expenses, designer, const designer_name[], tenant, const tenant_name[], 
					rent_value, const maturity[], max_furniture) 
{
	new house = Iter_Free(Houses);

	if (house != -1) 
	{
		Iter_Add(Houses, house);

		House_SetID(house, id);
		House_SetOwner(house, owner, owner_name);
		House_SetEntryX(house, entry_x);
		House_SetEntryY(house, entry_y);
		House_SetEntryZ(house, entry_z);
		House_SetExitX(house, exit_x);
		House_SetExitY(house, exit_y);
		House_SetExitZ(house, exit_z);
		House_SetEntryRot(house, entry_rot);
		House_SetNivel(house, level);
		House_SetValueType(house, value_type);
		House_SetValue(house, value);
		House_SetInterior(house, interior);
		House_SetWorld(house, world);
		House_SetLock(house, lock);
		House_SetStatus(house, status);
		House_SetExpenses(house, expenses);
		House_SetDesigner(house, designer, designer_name);
		House_SetTenant(house, tenant, tenant_name);
		House_SetRentalValue(house, rent_value);
		House_SetMaturity(house, maturity);
		House_SetMaxFurniture(house, max_furniture);

		House_Update(house, true);

		return 1;
	}
	return 0;
}

stock House_Buy(playerid, house)
{
	if (!Houses_CheckLimit(playerid)) 
		return SendMsgF(playerid, -1, "Você pode ter até no máximo %d casas de acordo com seu SÓCIO, use: (/minhascasas).", HousesPlayer_Count(playerid));
	
	if (Player_GetVIP(playerid) < SOCIO_COMUM && 
		Player_GetNivel(playerid) < House_GetNivel(house))
		return SendClientMessage(playerid, -1, "Você não tem nível suficiente para comprar essa casa.");

	new value = House_GetValue(house);
	switch (House_GetValueType(house))
	{
		case VALUE_TYPE_MONEY: {
			if (Player_GetMoney(playerid) < value) 
				return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiente para comprar essa casa.");
			
			Player_RemoveMoney(playerid, value);
		}
		case VALUE_TYPE_CASH: {
			if (Player_GetCash(playerid) < value) 
				return SendClientMessage(playerid, -1, "Você não tem cash suficiente para comprar essa casa.");
		
			Player_RemoveCash(playerid, value);
		}
	}

	new MapZone:zone,
		zone_name[MAX_MAP_ZONE_NAME];

	zone = GetMapZoneAtPoint2D(House_GetEntryX(house), House_GetEntryY(house));
	GetMapZoneName(zone, zone_name);
	ScreenStart_HouseBuy(playerid, house);

	SendMsgF(playerid, COLOR_ORANGE, "<< Casas >> Você comprou a casa em %s por %s%s{FFA500}, use /casa ajuda para ver os comandos.", zone_name, House_ValueType(house), getFormatText(value));
	SendMsgF(playerid, COLOR_ORANGE, "<< Casas >> Pague as despesas da casa em uma Lotérica a cada %d dias para que ela não seja vendida automaticamente.", HOUSE_DAYS_EXPENSES);
	SendClientMessage(playerid, COLOR_ORANGE, "<< Casas >> Verifique na lotérica se as despesas da casa estão quitadas!");

	House_SetOwner(house, Player_GetAccountID(playerid), PlayerName[playerid]);
	House_SetMaxFurniture(house, House_GenerateMaxFurniture(playerid, house));
	House_Update(house);
	House_Save(house);
	
	CheckConquista(playerid, Conquista_Casa);
	ServerLog::("casas", "%s comprou a casa %d", PlayerName[playerid], house);

	return 1;
}

stock House_Sell(house)
{
	House_SetOwner(house, 0, "NULL");
	House_SetTenant(house, 0, "NULL");
	House_SetDesigner(house, 0, "NULL");
	House_Update(house);
	return 1;
}

stock House_Rent(playerid, house)
{
	new string[128],
		MapZone:zone,
		zone_name[MAX_MAP_ZONE_NAME],
		value = House_GetRentalValue(house);

	zone = GetMapZoneAtPoint2D(House_GetEntryX(house), House_GetEntryY(house));
	GetMapZoneName(zone, zone_name);

	MEGAString[0] = EOS;

	format(MEGAString, sizeof(MEGAString), 
		""C_ORANGE"[ RESIDENCIA ]\n\n\
		"C_WHITE"Você está prestes a alugar uma residencia localizada em "C_CYAN"%s\n\
		"C_WHITE"Você vai pagar "C_MONEY"$%s "C_WHITE"por PayDay ao dono da casa.\n\
		-> Para desalugar uma casa use: "C_GRAY"/desalugar casa\n\
		"C_WHITE"-> Para nascer na residencia alugada use: "C_GRAY"/mudarlocal",
	zone_name, getFormatText(value));

	inline D_HouseRent(did, ddialogid, dresponse, dlistitem, string:dtext[])
	{
		#pragma unused did, ddialogid, dtext, dlistitem
		
		if (!dresponse) 
			return SendClientMessage(playerid, COLOR_WHITE, "Você cancelou o aluguel da residencia.");
		
		format(string, sizeof(string), "Sua residencia %d em %s foi alugada por %s.", house, zone_name, PlayerName[playerid]);
		SendPlayerEmail("Imobiliaria "SERVER_TAG"", House_GetOwnerName(house), string);
		
		SendMsgF(playerid, COLOR_ORANGE, "<< Casas >> Você alugou a casa %d em %s, pagamento $%s por Payday.", house, zone_name, getFormatText(value));
		
		House_SetTenant(house, Player_GetAccountID(playerid), PlayerName[playerid]);
		House_Update(house);
		House_Save(house);

		return 1;
	}
	Dialog_ShowCallback(playerid, using inline D_HouseRent, DIALOG_STYLE_MSGBOX, "Alugar residencia", MEGAString, "Alugar", "Cancelar");

	return 1;
}

stock House_DumpTenant(house)
{
	House_SetTenant(house, 0, "NULL");
	House_Update(house);
	House_Save(house);
}

stock Tenant_CountHouse(playerid)
	return Iter_Count(TenantHouses[playerid]);

CALLBACK: House_ChargeRental(playerid)
{
	new string[128],
		MapZone:zone,
		zone_name[MAX_MAP_ZONE_NAME],
		value;

	foreach (new house : TenantHouses[playerid])
	{
		value = House_GetRentalValue(house);
		zone = GetMapZoneAtPoint2D(House_GetEntryX(house), House_GetEntryY(house));
		GetMapZoneName(zone, zone_name);

		if (Player_GetMoneyBank(playerid) < 0)
		{
			format(string, sizeof(string), "%s foi despejado de sua residencia %d em %s por divida bancaria.", PlayerName[playerid], house, zone_name);
			SendPlayerEmail("Imobiliaria "SERVER_TAG"", House_GetOwnerName(house), string);

			SendMsgF(playerid, COLOR_ORANGE, "<< Casas >> Você foi despejado da casa %d em %s, por divida bancaria.", house, zone_name);

			House_DumpTenant(house);
			House_ReloadTenant(playerid);
			PlayerInfo[playerid][pSpawn] = 0;
		} else {
			Player_SetMoneyBank(playerid, Player_GetMoneyBank(playerid) - value);
			
			new ownerid = GetPlayerID(House_GetOwnerName(house));

			if (Player_Logado(ownerid))
				Player_SetMoneyBank(ownerid, Player_GetMoneyBank(ownerid) + value);
			else
				Player_UpdateMoneyBank(House_GetOwner(house), value);
		}
	}
}

stock House_Update(house, bool:create = false)
{
	new pickup;
	MEGAString[0] = EOS;

	if (House_GetStatus(house) == HOUSE_STATUS_ADMIN) {
		format(MEGAString, sizeof(MEGAString),
		"Casa %d\n\
		"C_GRAY"CASA BLOQUEADA PELA STAFF"C_WHITE" para comprá-la", house);

		pickup = 1273;
	}
	else if (House_GetOwner(house) == -2)
	{
		format(MEGAString, sizeof(MEGAString),
		""C_MONEY"CASINHA DO GOVERNO\n\n\
		"C_WHITE"Casa %d\n\
		"C_WHITE"Inscrições: %s\n\
		"C_WHITE"Local de inscrição: Prefeitura\n\n\
		"C_WHITE"Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" "C_WHITE" para entrar",
		house, Government_SubsHouse() ? (""C_GREEN"ABERTAS") : (""C_RED"FECHADAS"));
		
		pickup = 1273;
	}
	else if (!House_GetOwner(house)) {
		format(MEGAString, sizeof(MEGAString),
		"Casa %d\n\
		"C_WHITE"A venda por: %s%s\n\
		"C_WHITE"Nível necessário: "C_CYAN"%d\n\n\
		"C_WHITE"Use "C_CYAN"/casa comprar"C_WHITE" para comprá-la",
		house, House_ValueType(house), getFormatText(House_GetValue(house)), House_GetNivel(house));

		pickup = 1273;
	}
	else if (House_GetOwner(house) && House_GetTenant(house))
	{
		format(MEGAString, sizeof(MEGAString),
		"{FFA500}ALUGADA\n\n\
		"C_WHITE"Casa %d\n\
		"C_WHITE"Morador: {FFF000}%s\n\
		"C_WHITE"Dono: {EAEAEA}%s\n\
		"C_WHITE"Designer: {00FFFF}%s\n\n\
		"C_WHITE"Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" "C_WHITE" para entrar",
		house, House_GetTenantName(house), House_GetOwnerName(house), House_GetDesignerName(house));
		
		pickup = 19523;
	}
	else if (House_GetOwner(house) && !House_GetTenant(house) && House_GetRentalValue(house) > 0)
	{
	    format(MEGAString, sizeof(MEGAString),
  		"{FFA500}ALUGA-SE\n\n\
		"C_WHITE"Casa %d\n\
		"C_WHITE"Dono: {EAEAEA}%s\n\
		"C_WHITE"Aluguel: {00AA00}$%s\n\
		"C_WHITE"Designer: {00FFFF}%s\n\
		"C_WHITE"Use {00FFFF}/alugar casa "C_WHITE"para alugar\n\n\
		"C_WHITE"Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" "C_WHITE" para entrar",
		house, House_GetOwnerName(house), getFormatText(House_GetRentalValue(house)), House_GetDesignerName(house));
		
		pickup = 19523;
	}
	else
	{
	    format(MEGAString, sizeof(MEGAString),
		"Casa %d\n\
		"C_WHITE"Dono: {EAEAEA}%s\n\
		"C_WHITE"Designer: {00FFFF}%s\n\n\
		"C_WHITE"Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" "C_WHITE" para entrar",
		house, House_GetOwnerName(house), House_GetDesignerName(house));

		pickup = 19522;
	}

	if (create) {
		House_CreatePickup(house, pickup);
		House_CreateLabel(house, MEGAString);
	} else {
		House_UpdatePickup(house, pickup);
		House_UpdateLabel(house, MEGAString);
	}
}

stock House_Status(house)
{
    new valuetype[50];
	switch (House_GetStatus(house)) {
		case HOUSE_STATUS_OPEN:			valuetype = "{48CA35}Livre e/ou morando";
		case HOUSE_STATUS_ADMIN:		valuetype = "{D7150A}Restringida pela adminstracao";
 	}
 	return valuetype;
}

stock House_Find(playerid, house) {
	if (!House_IsValid(house))
		return 1;

	SetPlayerCheckpoint(playerid, House_GetEntryX(house), House_GetEntryY(house), House_GetEntryZ(house), 3.0);

	new string[52];
	format(string, sizeof(string), "A casa ID: %d foi marcada em seu mapa.", house);
	SendClientMessage(playerid, COLOR_ORANGE, string);

	return 1;
}

stock House_ValueType(house, type = 0)
{
    new valuetype[15];
	switch (House_GetValueType(house)) {
		case VALUE_TYPE_MONEY: {
		    if (type != 1)
				valuetype = "{00AA00}$";
			else
			    valuetype = "~g~$";

		}
		case VALUE_TYPE_CASH: {
		    if (type != 1)
				valuetype = "{00BFFF}C$";
            else
			    valuetype = "~b~~h~C$";
		}
 	}
 	return valuetype;
}

stock Houses_CheckLimit(playerid)
{
	new qtd = HousesPlayer_Count(playerid);
	if (qtd >= 1 && Player_GetVIP(playerid) < SOCIO_PREMIUM) 
		return false;

	if (qtd >= 2 && Player_GetVIP(playerid) < SOCIO_EXTREME) 
		return false;

	if (qtd >= MAX_PLAYER_HOUSES) 
		return false;
	
	return true;
}

stock House_PlayerGet(playerid)
{
	foreach(new h : Houses) 
		if (IsPlayerInRangeOfPoint(playerid, 1.0, House_GetEntryX(h), House_GetEntryY(h), House_GetEntryZ(h))) return h;
		
	return INVALID_HOUSE_ID;
}

stock Houses_Count()
	return Iter_Count(Houses);

stock Houses_Random() {
	new rdn = Iter_Random(Houses);
	return rdn;
}

stock HousesPlayer_Count(playerid)
{
	new count;
	foreach (new h : Houses)
	{
		if (House_GetOwner(h) == Player_GetAccountID(playerid) ||
		 	House_GetTenant(h) == Player_GetAccountID(playerid)) count++;
	}
	return count;
}

timer timerHideScreen[7000](playerid)
{
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, true);
    PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
}

stock ScreenStart_HouseBuy(playerid, house)
{
    TogglePlayerControllable(playerid, false);

	new string[60],
		Float:entry_x = House_GetEntryX(house),
		Float:entry_y = House_GetEntryY(house),
		value = House_GetValue(house);
		
	format(string, sizeof(string), "~n~~n~~w~Casa adquirida~n~-%s%s", House_ValueType(house, 1), getFormatText(value));
	GameTextForPlayer(playerid, string, 3000, 0);
    
    SetPlayerCameraLookAt(playerid, House_GetEntryX(house), House_GetEntryY(house), House_GetEntryZ(house));
    
    GetXYInFrontOfPoint(entry_x, entry_y, House_GetEntryRot(house), 15.0);
	SetPlayerCameraPos(playerid, entry_x, entry_y, House_GetEntryZ(house) + 2.0);

	PlayerPlaySound(playerid, 182, 0.0, 0.0, 0.0);
	defer timerHideScreen(playerid);
}

stock House_GenerateMaxFurniture(playerid, house) 
{
	new value = 80;

	if (House_GetValueType(house) == VALUE_TYPE_CASH)
		value = 140;

	switch (Player_GetVIP(playerid)) {
		case SOCIO_COMUM: value += 25;
		case SOCIO_PREMIUM: value += 30;
		case SOCIO_SUPREME: value += 40;
		case SOCIO_EXTREME: value += 60;
	}
	if (value > MAX_FURNITURE)
		value = MAX_FURNITURE;

	return value;
}

stock House_PlayerEntry(playerid)
{
	new house = Player_GetInHouse(playerid);

    if (house != INVALID_HOUSE_ID) {
		if (PlayerToPoint(5.0, playerid, House_GetExitX(house), House_GetExitY(house), House_GetExitZ(house)) && 
			GetPlayerVirtualWorld(playerid) == House_GetWorld(house)) {
				
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid, House_GetEntryX(house), House_GetEntryY(house), House_GetEntryZ(house));

			Player_SetInHouse(playerid, INVALID_HOUSE_ID);
		}
	}

	foreach(new houses : Houses) {
		if (IsPlayerInRangeOfPoint(playerid, 1.0, House_GetEntryX(houses), House_GetEntryY(houses), House_GetEntryZ(houses)))
		{
			if (House_GetOwner(houses) == Player_GetAccountID(playerid) || House_GetTenant(houses) == Player_GetAccountID(playerid) || 
				!House_GetLock(houses) || Dev_GetNivel(playerid) >= DEV_DELTA) {

				SetPlayerPos(playerid, House_GetExitX(houses), House_GetExitY(houses), House_GetExitZ(houses));
				SetPlayerInterior(playerid, House_GetInterior(houses));
				SetPlayerVirtualWorld(playerid, House_GetWorld(houses));
				Player_SetInHouse(playerid, houses);

				ShowLoadingMap(playerid);
				break;
			} else {
				GameTextForPlayer(playerid, "~r~Porta fechada", 3000, 1);
			}
		}
	}
}

stock Houses_Show(playerid, show_type = 0) {
	new string[128],
		house[MAX_PLAYER_HOUSES + 1],
		count,
		MapZone:zone,
		zone_name[MAX_MAP_ZONE_NAME];

	MEGAString[0] = EOS;

	if (show_type == 1) {
		strcat(MEGAString, "id\tlocalizacao\n");

		foreach(new houses : Houses) {
			if (House_GetOwner(houses) == Player_GetAccountID(playerid) || 
				House_GetTenant(houses) == Player_GetAccountID(playerid)) {
					
				house[count] = houses;
				zone = GetMapZoneAtPoint2D(House_GetEntryX(houses), House_GetEntryY(houses));
				GetMapZoneName(zone, zone_name);

				format(string, sizeof(string), "%03d\t%s\n", houses, zone_name);
				strcat(MEGAString, string);
				count++;
			}
		}

		inline D_MyHouses(mdlid, mdldialogid, mdlresponse, mdllistitem, string:mdltext[])
		{
			#pragma unused mdlid, mdldialogid, mdltext
			if (!mdlresponse)
				return 1;

			if (mdllistitem != -1) {
				Player_SetSpawnType(playerid, TYPE_SPAWN_HOUSE, house[mdllistitem]);
			}
			return 1;
		}
		Dialog_ShowCallback(playerid, using inline D_MyHouses, DIALOG_STYLE_TABLIST_HEADERS, "Selecione uma casa", MEGAString, "Selecionar", "Fechar");
	} else if (show_type == 2) {
		strcat(MEGAString, "id\tlocalizacao\tcargo\n");

		foreach(new houses : Houses) {
			if (House_GetOwner(houses) == Player_GetAccountID(playerid) || 
				House_GetTenant(houses) == Player_GetAccountID(playerid) ||
				House_GetDesigner(houses) == Player_GetAccountID(playerid)) {
					
				house[count] = houses;
				zone = GetMapZoneAtPoint2D(House_GetEntryX(houses), House_GetEntryY(houses));
				GetMapZoneName(zone, zone_name);

				if (House_GetOwner(houses) == Player_GetAccountID(playerid))
					format(string, sizeof(string), "%03d\t%s\t"C_LIGHTBLUE"Proprietario\n", houses, zone_name);
				else if (House_GetTenant(houses) == Player_GetAccountID(playerid))
					format(string, sizeof(string), "%03d\t%s\t"C_ORANGE"Inquilino\n", houses, zone_name);
				else if (House_GetDesigner(houses) == Player_GetAccountID(playerid))
					format(string, sizeof(string), "%03d\t%s\t"C_CYAN"Designer\n", houses, zone_name);
				strcat(MEGAString, string);
				count++;
			}
		}

		inline D_MyHouses(mdlid, mdldialogid, mdlresponse, mdllistitem, string:mdltext[])
		{
			#pragma unused mdlid, mdldialogid, mdltext
			if (!mdlresponse) 
				return 1;

			new selected_house = house[mdllistitem];

			SetPlayerCheckpoint(playerid, House_GetEntryX(selected_house), House_GetEntryY(selected_house), House_GetEntryZ(selected_house), 5.0);
			SetPlayerCP(playerid, CP_NULL);

			zone = GetMapZoneAtPoint2D(House_GetEntryX(selected_house), House_GetEntryY(selected_house));
			GetMapZoneName(zone, zone_name);

			SendMsgF(playerid, COLOR_ORANGE, "<< GPS >> A casa %d, localizada em %s, foi marcada no mapa!", selected_house, zone_name);
			return 1;
		}
		Dialog_ShowCallback(playerid, using inline D_MyHouses, DIALOG_STYLE_TABLIST_HEADERS, "Selecione uma casa", MEGAString, "Selecionar", "Fechar");
	} else {
		strcat(MEGAString, "id	local\tstatus\tvalor fatura\tvencimento\n");

		foreach(new houses : Houses) {
			if (House_GetOwner(houses) == Player_GetAccountID(playerid)) 
			{
				house[count] = houses;
				zone = GetMapZoneAtPoint2D(House_GetEntryX(houses), House_GetEntryY(houses));
				GetMapZoneName(zone, zone_name);

				new days = House_GetMaturityDays(houses);
				if (days > 0)
					format(string, sizeof(string), ""C_GRAY"%d em %s\t"C_MONEY"$%s\t"C_WHITE"%d dias\n", houses, zone_name, getFormatText(House_GetExpenses(houses)), days);
				else
					format(string, sizeof(string), ""C_GRAY"%d em %s\t"C_MONEY"$%s\t"C_RED"VENCIDO\n", houses, zone_name, getFormatText(House_GetExpenses(houses)));

				format(string, sizeof(string), "%03d\t%s\n", houses, zone_name);
				strcat(MEGAString, string);
				count++;
			}
		}

		inline D_MyHouses(mdlid, mdldialogid, mdlresponse, mdllistitem, string:mdltext[])
		{
			#pragma unused mdlid, mdldialogid, mdltext
			if (!mdlresponse) 
				return 1;

			new selected_house = house[mdllistitem];

			SetPlayerCheckpoint(playerid, House_GetEntryX(selected_house), House_GetEntryY(selected_house), House_GetEntryZ(selected_house), 5.0);
			SetPlayerCP(playerid, CP_NULL);

			zone = GetMapZoneAtPoint2D(House_GetEntryX(selected_house), House_GetEntryY(selected_house));
			GetMapZoneName(zone, zone_name);

			SendMsgF(playerid, COLOR_ORANGE, "<< GPS >> A sua casa %d, localizada em %s, foi marcada no mapa!", selected_house, zone_name);
			return 1;
		}
		Dialog_ShowCallback(playerid, using inline D_MyHouses, DIALOG_STYLE_TABLIST_HEADERS, "Selecione uma casa", MEGAString, "Selecionar", "Fechar");
	}
	return 1;
}

stock Player_SpawnInHouse(playerid) 
{
	new houseid = Player_Spawn[playerid][SpawnID];

	SetPlayerPos(playerid, House_GetExitX(houseid), House_GetExitY(houseid), House_GetExitZ(houseid));
	SetPlayerInterior(playerid, House_GetInterior(houseid));
	SetPlayerVirtualWorld(playerid, House_GetWorld(houseid));
	Player_SetInHouse(playerid, houseid);
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == 7472)
	{
		if(response)
		{
		    switch(listitem)
			{
		        case 0: ShowModelSelectionMenu(playerid, QuartoList, "Moveis do Quarto", 200, 0x000000AA);
		        case 1: ShowModelSelectionMenu(playerid, SalaList, "Moveis da Sala", 200, 0x000000AA);
		        case 2: ShowModelSelectionMenu(playerid, CozinhaList, "Moveis da Cozinha", 200, 0x000000AA);
		        case 3: ShowModelSelectionMenu(playerid, BanheiroList, "Moveis do Banheiro", 200, 0x000000AA);
		        case 4: ShowModelSelectionMenu(playerid, DecoracaoList, "Moveis de Decoracao", 200, 0x000000AA);
		        case 5: ShowModelSelectionMenu(playerid, MoveisList, "Outros moveis", 200, 0x000000AA);
		    }
		}
	}

	else if(dialogid == 1066)
    {
    	if (!response) 
			return callcmd::gps(playerid);

		new value,
			count,
			Float:distance,
			MapZone:zone, 
			string[128],
			zone_name[MAX_MAP_ZONE_NAME];

		MEGAString[0] = EOS;

		switch (listitem)
		{
   			case 0:
			{
				ShowPlayerDialog(playerid, 5426, DIALOG_STYLE_INPUT, 
				"{9C9C9C}Localizar uma casa pelo ID",
		        "{FFFFFF}Abaixo, digite o id da casa que deseja encontrar! (0 ao 499)",

				"Localizar", "Voltar");
   			}
   			case 1:
			{
				strcat(MEGAString, "ID\tBairro\tPreço da casa\tDistância\n");

			    foreach(new houses : Houses)
				{
				    if (count > 20) 
						break;

					if (!House_GetOwner(houses) && 
						House_GetValueType(houses) == VALUE_TYPE_MONEY) {

						value = House_GetValue(houses);
						distance = GetPlayerDistanceFromPoint(playerid, House_GetEntryX(houses), House_GetEntryY(houses), House_GetEntryZ(houses));
						zone = GetMapZoneAtPoint2D(House_GetEntryX(houses), House_GetEntryY(houses));
						GetMapZoneName(zone, zone_name);

					    format(string, sizeof(string), "{A7A4A4}%d\t%s\t%s%s\t{9C9C9C}%.0f Metros\n", houses, zone_name, House_ValueType(houses), getFormatText(value), distance);
                		strcat(MEGAString, string);
						
			            List_SetPlayers(playerid, count, houses);
						count ++;
					}
				}

				format(string, sizeof(string), " {FFFFFF}Casas a venda ({00FF00}%d{FFFFFF})", count);

				ShowPlayerDialog(playerid, 1067, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Localizar", "Cancelar");
   			}
			case 2:
			{
				strcat(MEGAString, "ID\tBairro\tPreço da casa\tDistância\n");

			    foreach(new houses : Houses)
				{
					if (count > 20) 
						break;

					if (!House_GetOwner(houses) && 
						House_GetValueType(houses) == VALUE_TYPE_CASH) {
				
						value = House_GetValue(houses);
						distance = GetPlayerDistanceFromPoint(playerid, House_GetEntryX(houses), House_GetEntryY(houses), House_GetEntryZ(houses));
						zone = GetMapZoneAtPoint2D(House_GetEntryX(houses), House_GetEntryY(houses));

						GetMapZoneName(zone, zone_name);

					    format(string, sizeof(string), "{A7A4A4}%d\t%s\t%s%s\t{9C9C9C}%.0f Metros\n", houses, zone_name, House_ValueType(houses), getFormatText(value), distance);
                		strcat(MEGAString, string);
						
			            List_SetPlayers(playerid, count, houses);
						count ++;
					}
				}
				format(string, sizeof(string), " {FFFFFF}Casas a venda ({00FF00}%d{FFFFFF})", count);
				ShowPlayerDialog(playerid, 1067, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Localizar", "Cancelar");
   			}
			case 3:
			{
				strcat(MEGAString, "ID\tBairro\tDono\tPreço do aluguel\tDistância\n");

			    foreach(new houses : Houses)
				{
				    if (count > 20) 
						break;

					value = House_GetRentalValue(houses);

					if (House_GetOwner(houses) && 
						(value > 0 && House_GetTenant(houses) == -1)) {

						distance = GetPlayerDistanceFromPoint(playerid, House_GetEntryX(houses), House_GetEntryY(houses), House_GetEntryZ(houses));
						zone = GetMapZoneAtPoint2D(House_GetEntryX(houses), House_GetEntryY(houses));
						GetMapZoneName(zone, zone_name);

					    format(string, sizeof(string), "{A7A4A4}%d\t%s\t%s\t{00AA00}$%s\t{9C9C9C}%.0f Metros\n", houses, zone_name, House_GetOwnerName(houses), getFormatText(value), distance);
                		strcat(MEGAString, string);
						
			            List_SetPlayers(playerid, count, houses);
						count ++;
					}
				}
				format(string, sizeof(string), " {FFFFFF}Casas para alugar ({00FF00}%d{FFFFFF})", count);
				ShowPlayerDialog(playerid, 1067, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Localizar", "Cancelar");
   			}
		}
       	return 1;
   	}

	else if(dialogid == 5426)
	{
	    if (response)
		{
			new casaid = strval(inputtext);
			if (casaid < 0 || casaid >= 500)
			{
			    return SendClientMessage(playerid, -1, "O id da casa deve estar entre 0 - 500 !");
			}
			House_Find(playerid, casaid);

		} else {
		    callcmd::gps(playerid);
		}
	    return true;
	}

   	else if(dialogid == 1067)
	{
	    if (response) 
			House_Find(playerid, List_GetPlayers(playerid, listitem));
		else 
			callcmd::gps(playerid);

	    return true;
	}
    else if (dialogid == 5)
	{
	    if (!response) 
			return SendClientMessage(playerid, -1, "Você fechou o menu da lotérica."), callcmd::loterica(playerid);

		if (!HousesPlayer_Count(playerid)) 
			return SendClientMessage(playerid, -1, "Você não tem uma casa."), callcmd::loterica(playerid);

		new string[128],
			house = selectHouse[playerid][listitem],
			expenses = House_GetExpenses(house),
			MapZone:zone,
			zone_name[MAX_MAP_ZONE_NAME];

		if (Player_GetMoney(playerid) < expenses) 
			return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiente para pagar a casa.");

		if (expenses < 0) 
			return SendClientMessage(playerid, -1, "A casa selecionada não possui despesas.");

		zone = GetMapZoneAtPoint2D(House_GetEntryX(house), House_GetEntryY(house));
		GetMapZoneName(zone, zone_name);
		
		Player_RemoveMoney(playerid, expenses);
   		DepositPropertie(playerid, expenses/2);
		OrgInfo_SetMoney(7, OrgInfo_GetMoney(7) + expenses/2);

	 	House_SetExpenses(house, 0);
		House_AddMaturity(house, Now() + Days:15);
        House_Save(house);
		
		format(string, sizeof(string), "<< Casas >> Você pagou as despesas de sua casa %d em %s, pagamento: {00AA00}$%s", house, zone_name, getFormatText(expenses));
		SendClientMessage(playerid, COLOR_ORANGE, string);
		ServerLog::("casas", "%s pagou as despesas da casa %d, pagamento: $%s", PlayerName[playerid], house, getFormatText(expenses));

	    return 1;
	}
	return 0;
}

//-------------------------------------------------------- Sistema de Cozinhar -------------------------------------------------------------------
// timer timerCooking[1500](playerid, casaid, modelid, percent)
// {
//     new	string[128];

//     if (percent >= 100)
//     {
// 	    SetPVarInt(playerid, "cozidoPronto", 1);

// 	    DestroyDynamicObject(GetPVarInt(playerid, "objectFireCooking"));
// 	    DestroyDynamicObject(GetPVarInt(playerid, "objectCooking"));

// 	    for(new x; x != MAX_FURNITURE; x++)
// 		{
// 			if (MobInfo[casaid][x][mobObject] == GetPVarInt(playerid, "fogaoUsado") && isMovelCooker(MobInfo[casaid][x][mobModel]))
// 			{
// 				switch (modelid)
// 				{
// 			    	case 19582:
// 					{
// 						SetPVarInt(playerid, "objectCookingReady", CreateDynamicObject(ITEM_MODEL_CARNE, MobInfo[casaid][x][mobPos][0], MobInfo[casaid][x][mobPos][1], MobInfo[casaid][x][mobPos][2] + 1.03, 0.0, 0.0, 0.0, casaid));
// 						SetPVarInt(playerid, "idObjectFinale", ITEM_MODEL_CARNE);
// 					}
// 					case 19580:
// 					{
// 						SetPVarInt(playerid, "objectCookingReady", CreateDynamicObject(19580, MobInfo[casaid][x][mobPos][0], MobInfo[casaid][x][mobPos][1], MobInfo[casaid][x][mobPos][2] + 1.03, 0.0, 0.0, 0.0, casaid));
// 						SetPVarInt(playerid, "idObjectFinale", 19580);
// 					}
// 					case ITEM_MODEL_FRANGO:
// 					{
// 						SetPVarInt(playerid, "objectCookingReady", CreateDynamicObject(ITEM_MODEL_FRANGO, MobInfo[casaid][x][mobPos][0], MobInfo[casaid][x][mobPos][1], MobInfo[casaid][x][mobPos][2] + 1.03, 0.0, 0.0, 0.0, casaid));
// 						SetPVarInt(playerid, "idObjectFinale", ITEM_MODEL_FRANGO);
// 					}
// 					default:
// 					{
// 					    SetPVarInt(playerid, "objectCookingReady", CreateDynamicObject(19579, MobInfo[casaid][x][mobPos][0], MobInfo[casaid][x][mobPos][1], MobInfo[casaid][x][mobPos][2] + 1.03, 0.0, 0.0, 0.0, casaid));
// 						SetPVarInt(playerid, "idObjectFinale", 19579);
// 					}
// 			    }
// 	  		}
// 	  	}

// 	  	GetPVarString(playerid, "textObjectFinale", string, 20);

// 		format(string, sizeof(string), "Você cozinhou um(a) %s, use /guardarcomida próximo ao fogão.", string);
// 		SendClientMessage(playerid, -1, string);

// 		DeletePVar(playerid, "objectFireCooking"); 
// 		DestroyDynamic3DTextLabel(textCooking[playerid]); 
// 		KillTimer(GetPVarInt(playerid, "timerCooking_Start")); 
// 		SetPVarInt(playerid, "timerCooking_Start", -1);
// 	}
// 	else
// 	{
// 	    percent += 1;

// 	    format(string, sizeof(string), "Cozinhando... %i%", percent);
// 		UpdateDynamic3DTextLabelText(textCooking[playerid], 0x9C9C9CF9, string);
// 	}
// }

// stock FinaleCookingReady(playerid)
// {
//     DestroyDynamicObject(GetPVarInt(playerid, "objectCooking"));
// 	DestroyDynamicObject(GetPVarInt(playerid, "objectCookingReady"));
// 	DestroyDynamicObject(GetPVarInt(playerid, "objectFireCooking"));
// 	DestroyDynamicObject(GetPVarInt(playerid, "objectPanCooking"));
// 	DeletePVar(playerid, "playerCozinhando");
// 	DeletePVar(playerid, "objectPanCooking");
// 	DeletePVar(playerid, "objectCookingReady");
// 	DeletePVar(playerid, "fogaoUsado");
// 	DeletePVar(playerid, "cozidoPronto");
// 	DeletePVar(playerid, "idObjectFinale");
// }

stock houseSellState(h, hmode = 1)
{
	return 1;
	// new string[128];

	// if (hmode == 1)
	// {
	// 	format(string, sizeof(string), "Info: Casa ID: %d foi liberada por inatividade  %s [%d].", h, HouseInfo[h][hDono], HouseInfo[h][hDonoID]);
	// 	server_log("casas", string);

	// 	format(string, sizeof(string), "CASAS: A casa %d foi liberada por falta de pagamento das faturas", h);
	// }
	// SendClientMessageToAll(TEAM_BALLAS_COLOR, string);
	// HouseInfo[h][hFechadura] = true;
	// House_SetLock(h, true);
	// strmid(HouseInfo[h][hDono], "Ninguém", 0, strlen("Ninguém"), 255);
	// HouseInfo[h][hDonoID] = -1;
    // updateHouseStats(h);
}

stock House_Fatura(playerid)
{
	MEGAString[0] = EOS;

	strcat(MEGAString, "ID e Local\tInquilino\tDespesas\tVencimento\n");

	new 
		string[147],
		select_prop,
		MapZone:zone,
		zone_name[MAX_MAP_ZONE_NAME]
	;

	foreach(new casas : Houses)
	{
	    if (House_GetOwner(casas) == Player_GetAccountID(playerid))
		{
	        selectHouse[playerid][select_prop] = casas;

			zone = GetMapZoneAtPoint2D(House_GetEntryX(casas), House_GetEntryY(casas));
			GetMapZoneName(zone, zone_name);

			new days = House_GetMaturityDays(casas);
			if (days > 0)
				format(string, sizeof(string), "{9C9C9C}%03d em %s\t%s\t{00AA00}$%s\t{FFFFFF}%d dias\n", casas, zone_name, House_Status(casas), getFormatText(House_GetExpenses(casas)), days);
			else
				format(string, sizeof(string), "{9C9C9C}%d em %s\t%s\t{00AA00}$%s\t{FF0000}VENCIDO\n", casas, zone_name, House_Status(casas), getFormatText(House_GetExpenses(casas)));
			
			strcat(MEGAString, string);
	    	select_prop ++;
		}
	}
	ShowPlayerDialog(playerid, 5, DIALOG_STYLE_TABLIST_HEADERS, "Pagar suas contas", MEGAString, "Pagar", "Voltar");
}

// ---------------------------------------------------------------------------------

// stock Cooking_Start(playerid, modelid, itemname) {
// 	new	casaid = Player_GetInHouse(playerid),
// 		fogaoid = getFogaoPerto(playerid);

// 	if (!Player_Logado(playerid)) 
// 		return false;
	
// 	if (Player_GetInHouse(playerid) == 900) 
// 		return SendClientMessage(playerid, -1, "Você não está dentro de uma casa."), false;

// 	if (GetPVarInt(playerid, "playerCozinhando") == 1)
// 		return SendClientMessage(playerid, -1, "Você já está cozinhando ou não comeu oque cozinhou."), false;

// 	if (GetPVarInt(playerid, "playerCozinhando") != 1 && isMovelCooker(MobInfo[casaid][fogaoid][mobModel]) &&
// 	IsPlayerInRangeOfPoint(playerid, 1.5, MobInfo[casaid][fogaoid][mobPos][0], MobInfo[casaid][fogaoid][mobPos][1], MobInfo[casaid][fogaoid][mobPos][2]))
// 	{
// 		foreach(new i : Player) {
// 			if (MobInfo[casaid][fogaoid][mobObject] == GetPVarInt(i, "fogaoUsado"))
// 				return SendClientMessage(playerid, -1, "Fogão já está sendo usado"), 0;
// 		}

// 		SetPVarInt(playerid, "fogaoUsado", MobInfo[casaid][fogaoid][mobObject]); SetPVarInt(playerid, "playerCozinhando", 1);
// 		SetPVarInt(playerid, "objectCooking", CreateDynamicObject(modelid, MobInfo[casaid][fogaoid][mobPos][0], MobInfo[casaid][fogaoid][mobPos][1], MobInfo[casaid][fogaoid][mobPos][2] + 1.03, 0.0, 0.0, 0.0, casaid));
// 		SetPVarInt(playerid, "objectFireCooking", CreateDynamicObject(19632, MobInfo[casaid][fogaoid][mobPos][0], MobInfo[casaid][fogaoid][mobPos][1], MobInfo[casaid][fogaoid][mobPos][2] + 0.5, 0.0, 0.0, 0.0, casaid));
// 		SetPVarInt(playerid, "objectPanCooking", CreateDynamicObject(19581, MobInfo[casaid][fogaoid][mobPos][0], MobInfo[casaid][fogaoid][mobPos][1] + 0.45, MobInfo[casaid][fogaoid][mobPos][2] + 1.0, 1.0, 0.0, 0.0, casaid));
		
// 		format(string, sizeof(string), "Cozinhando... %i%", 0);
// 		textCooking[playerid] = CreateDynamic3DTextLabel(string, 0x9C9C9CF9, MobInfo[casaid][fogaoid][mobPos][0], MobInfo[casaid][fogaoid][mobPos][1], MobInfo[casaid][fogaoid][mobPos][2] + 1.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, casaid);

// 		timer_cooking[playerid] = repeat timerCooking(playerid, casaid, modelid, 0);

// 		SetPVarString(playerid, "textObjectFinale", itemname);

// 		format(string, sizeof(string), "* %s está cozinhando um(a) %s.", PlayerName[playerid], itemname);
// 		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

// 		//if (!PlayerOuvinte[0][playerid])
// 			//PlayAudioStreamForPlayer(playerid, ""SERVER_SITE"/sounds/som_fritura.mp3", MobInfo[casaid][fogaoid][mobX], MobInfo[casaid][fogaoid][mobY], MobInfo[casaid][fogaoid][mobZ], 20.0, 1);

// 		return true;
// 	}
// 	else
// 	{
// 		return SendClientMessage(playerid, -1, "Você não está perto de algum fogão."), false;
// 	}
// }