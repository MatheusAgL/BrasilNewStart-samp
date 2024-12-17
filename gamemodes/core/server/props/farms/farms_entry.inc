#define 	MAX_FARMS 			(7)
#define     MAX_FARM_ITEMS      (10)

enum ENUM_FARM
{
	farmID,
	farmOwnerName[MAX_PLAYER_NAME],
	farmOwnerID,
	Float:farmEntryX,
	Float:farmEntryY,
	Float:farmEntryZ,
	farmPrice,
	farmTypePrice,
	farmVault,
	Timestamp:farmDate,
	farmLocked,
	farmPickup,
	Text3D:farmLabel,

	bool: fbRoubado,
	fbRouboAnunciado,
	fbTempoRoubado,
	fbProtection,
	fbCofre,
	Float:fbCofreHealth,
	Text3D:fbCofreLabel,
};
new FarmInfo[MAX_FARMS][ENUM_FARM];
new Iterator:Farms<MAX_FARMS>;
new Iterator:Farm_Items[MAX_FARMS]<MAX_FARM_ITEMS>;

stock Farm_SetDate(farmid, Days:days)
	FarmInfo[farmid][farmDate] = Now() + Days:days;

stock Farm_IsOwned(idx)
	return FarmInfo[idx][fbOwnerID] != -1;

stock Farm_GetId(playerid, Float:range = 2.0)
{
	foreach(new farm : Fazendas) if (IsPlayerInRangeOfPoint(playerid, range, Farm_GetEntryX(farm), Farm_GetEntryY(farm), Farm_GetEntryZ(farm))) return farm;

	return -1;
}

stock Farm_DestroyPickup(farm)
	DestroyPickup(FarmInfo[farm][farmPickup]);

stock Farm_DestroyLabel(farm)
	DestroyPickup(FarmInfo[farm][farmLabel]);


new SelectFazendas[MAX_PLAYERS][MAX_FAZENDAS];


stock Fazenda_LoadAll()
{
	mysql_query(MySQL_Handle, "SELECT f.*, p1.nome 'donoNome' FROM fazendas f LEFT JOIN player p1 ON p1.id = f.dono ORDER BY f.id");
	new rows = MYSQL_GetRowsCount();
	for (new idx = 0; idx < rows; idx++)
	{
		Iter_Add(Fazendas, idx);
		FBizzInfo[idx][fbID] = MYSQL_GetInt(idx, "id");
		format(FBizzInfo[idx][fbMessage], 128, "%s", MYSQL_GetString(idx, "descricao"));
		if(!MYSQL_IsNull(idx, "dono")) {
			FBizzInfo[idx][fbOwnerID] = MYSQL_GetInt(idx, "dono");
			format(FBizzInfo[idx][fbOwner], 25, "%s", MYSQL_GetString(idx, "donoNome"));
		}
		else {
			FBizzInfo[idx][fbOwnerID] = -1;
			format(FBizzInfo[idx][fbOwner], 25, "Ninguém");
		}

		FBizzInfo[idx][fbEntranceX] = MYSQL_GetFloat(idx, "entradaX");
	 	FBizzInfo[idx][fbEntranceY] = MYSQL_GetFloat(idx, "entradaY");
		FBizzInfo[idx][fbEntranceZ] = MYSQL_GetFloat(idx, "entradaZ");
		FBizzInfo[idx][fbBuyPrice] = MYSQL_GetInt(idx, "preco");
		FBizzInfo[idx][fbPriceMode] = MYSQL_GetInt(idx, "precoModo");
		FBizzInfo[idx][fbTill] = MYSQL_GetInt(idx, "cofre");
		FBizzInfo[idx][fbLocked] = MYSQL_GetBool(idx, "trancada");
		FBizzInfo[idx][fbProducts] = MYSQL_GetInt(idx, "produtos");
		FBizzInfo[idx][fbMaxProducts] = MYSQL_GetInt(idx, "maximoProdutos");
		FBizzInfo[idx][fbProductsReq] = MYSQL_GetInt(idx, "produtosRequeridos");
		FBizzInfo[idx][fbPriceProd] = MYSQL_GetInt(idx, "precoProdutos");
		FBizzInfo[idx][fbProtection] = MYSQL_GetInt(idx, "protecao");
		FBizzInfo[idx][fbInsumos] = MYSQL_GetInt(idx, "insumos");
		FBizzInfo[idx][fbPrecoInsumo] = MYSQL_GetInt(idx, "precoInsumo");
		TimeParse(MYSQL_GetString(idx, "vencimento"), ISO6801_DATE, FBizzInfo[idx][fbDate]);

	    FBizzInfo[idx][fbRoubado] 		 = false;
	    FBizzInfo[idx][fbCofreHealth]    = 100.0 + (FBizzInfo[idx][fbProtection] * 100.0);
	    FBizzInfo[idx][fbRouboAnunciado] = 0;

        FBizzInfo[idx][fbCofre] = CreateDynamicObject(2332, 279.79730, 308.77884, 1002.79761,   0.00000, 0.00000, 89.44640, idx);

		// Update na 3d text
		new gstring[128];
		format(gstring, sizeof gstring, "Cofre da fazenda\nDano: %.1f\n{FFFFFF}Use: /roubarfazenda", FBizzInfo[idx][fbCofreHealth]);
		FBizzInfo[idx][fbCofreLabel] = CreateDynamic3DTextLabel(gstring, 0xFFAA00FF, 279.79730, 308.77884, 1002.79761, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, idx);

		/*if ((Now() - FBizzInfo[idx][fbDate]) > Days:100) {
		    FBizzInfo[idx][fbDate] = Now() + Days:3;
		    Fazenda_Salvar(idx);
		}*/
		FBizzInfo[idx][fbLabelid] = Create3DTextLabel("Carregando fazenda...", 0xE6D4D1FF, FBizzInfo[idx][fbEntranceX], FBizzInfo[idx][fbEntranceY], FBizzInfo[idx][fbEntranceZ]+0.5,20.0,0);
		FBizzInfo[idx][fbPickupid] = -1;
		Fazenda_UpdateLabel(idx);
	}

	return Iter_Count(Fazendas);
}

stock Fazenda_SaveAll() {

	// Salvar todas fazendas criadas;
	foreach(new idx : Fazendas)
		Fazenda_Salvar(idx);

	return 1;
}

stock Fazenda_Load(idx)
{
	static query[300];

	mysql_format(query, sizeof(query), "SELECT f.*, p1.nome 'donoNome' FROM fazendas f \
		LEFT JOIN player p1 ON p1.id = f.dono WHERE id = %d ORDER BY f.id", idx);

	mysql_query(MySQL_Handle, query);

	if (MYSQL_GetRowsCount() > 0) {
		FBizzInfo[idx][fbID] = MYSQL_GetInt(0, "id");
		format(FBizzInfo[idx][fbMessage], sizeof(FBizzInfo[idx][fbMessage]), "%s", MYSQL_GetString(0, "descricao"));
		FBizzInfo[idx][fbOwnerID] = MYSQL_GetInt(0, "dono");
		format(FBizzInfo[idx][fbOwner], sizeof(FBizzInfo[idx][fbOwner]), "%s", MYSQL_GetString(0, "donoNome"));

		FBizzInfo[idx][fbEntranceX] = MYSQL_GetFloat(0, "entradaX");
		FBizzInfo[idx][fbEntranceY] = MYSQL_GetFloat(0, "entradaY");
		FBizzInfo[idx][fbEntranceZ] = MYSQL_GetFloat(0, "entradaZ");
		FBizzInfo[idx][fbBuyPrice] = MYSQL_GetInt(0, "preco");
		FBizzInfo[idx][fbPriceMode] = MYSQL_GetInt(0, "precoModo");
		FBizzInfo[idx][fbTill] = MYSQL_GetInt(0, "cofre");
		FBizzInfo[idx][fbLocked] = MYSQL_GetInt(0, "trancada");
		FBizzInfo[idx][fbProducts] = MYSQL_GetInt(0, "produtos");
		FBizzInfo[idx][fbMaxProducts] = MYSQL_GetInt(0, "maximoProdutos");
		FBizzInfo[idx][fbProductsReq] = MYSQL_GetInt(0, "produtosRequeridos");
		FBizzInfo[idx][fbPriceProd] = MYSQL_GetInt(0, "precoProdutos");
		FBizzInfo[idx][fbProtection] = MYSQL_GetInt(0, "protecao");
		FBizzInfo[idx][fbInsumos] = MYSQL_GetInt(0, "insumos");
		FBizzInfo[idx][fbPrecoInsumo] = MYSQL_GetInt(0, "precoInsumo");
		TimeParse(MYSQL_GetString(0, "vencimento"), ISO6801_DATE, FBizzInfo[idx][fbDate]);

		FBizzInfo[idx][fbRoubado] 		 = false;
		FBizzInfo[idx][fbCofreHealth]    = 100.0 + (FBizzInfo[idx][fbProtection] * 100.0);
		FBizzInfo[idx][fbRouboAnunciado] = 0;

		FBizzInfo[idx][fbCofre] = CreateDynamicObject(2332, 279.79730, 308.77884, 1002.79761,   0.00000, 0.00000, 89.44640, idx);

		// Update na 3d text
		format(gstring, sizeof gstring, "Cofre da fazenda\nDano: %.1f\n{FFFFFF}Use: /roubarfazenda", FBizzInfo[idx][fbCofreHealth]);
		FBizzInfo[idx][fbCofreLabel] = CreateDynamic3DTextLabel(gstring, 0xFFAA00BB, 279.79730, 308.77884, 1002.79761, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, idx);

		if ((getdate() - FBizzInfo[idx][fbDate]) > 100) 
			FBizzInfo[idx][fbDate] = Now() + Days:3;
		
		Fazenda_UpdateLabel(idx);
	}
}

stock Fazenda_SetOwner(idx, playerid) {

	if(playerid == -1) {
		FBizzInfo[idx][fbOwnerID] = -1;
		format(FBizzInfo[idx][fbOwner], MAX_PLAYER_NAME, "Ninguém");
	}
	else {
		FBizzInfo[idx][fbOwnerID] = Player_GetAccountID(playerid);
		format(FBizzInfo[idx][fbOwner], MAX_PLAYER_NAME, PlayerName[playerid]);
	}

	Fazenda_Salvar(idx);
	Fazenda_UpdateLabel(idx);
}

stock Fazenda_SetOwnerOffline(idx, accountId) {

	FBizzInfo[idx][fbOwnerID] = accountId;
	format(FBizzInfo[idx][fbOwner], MAX_PLAYER_NAME, Player_GetNicknameByID(accountId));

	Fazenda_Salvar(idx);
	Fazenda_UpdateLabel(idx);
}

stock Fazenda_IsOwner(idx, id)
{
	return FBizzInfo[idx][fbOwnerID] == id;
}

stock Fazenda_Count(playerid)
{
	new count;
	foreach(new idx : Fazendas)
		if (Fazenda_IsOwner(idx, Player_GetAccountID(playerid))) 
			count++;

	return count;
}

stock Fazenda_CheckLimit(playerid)
{
	new count = Fazenda_Count(playerid);

	if (Player_GetVIP(playerid) < 1) {
		return 0;
	}

	if (count >= 1 && Player_GetVIP(playerid) < 6)
	    return 0;

	if (count >= 2 && Player_GetVIP(playerid) < 7)
	    return 0;

	if (count >= MAX_PLAYER_FAZENDAS)
	    return 0;

	return 1;
}

stock Fazenda_UpdateLabel(idx)
{
	if(FBizzInfo[idx][fbPickupid] != -1)
		DestroyPickup(FBizzInfo[idx][fbPickupid]);

	static gstring[500];

	if(!Fazenda_IsOwned(idx))
	{
		FBizzInfo[idx][fbPickupid] = CreatePickup(1579, 1, FBizzInfo[idx][fbEntranceX], FBizzInfo[idx][fbEntranceY], FBizzInfo[idx][fbEntranceZ]);
			 
		format(gstring, sizeof(gstring),
		"{FFFFFF}Fazenda\n\
		{FFFFFF}A Venda por: {00FF00}%s %s\n\
		{FFFFFF}Nome: {00FFFF}%s\n\
		{FFFFFF}Fundos: {00FFFF}$%s\n\
		{FFFFFF}Produtos: {00FFFF}%d\n\
		{FFFFFF}Produtos Requeridos: {00FFFF}%d\n\
		{FFFFFF}Preço por produto: {00FFFF}$%s\n\n\
		{FFFFFF}Use {00FFFF}/fazenda comprar {FFFFFF}para comprá-la",
		getFormatText(FBizzInfo[idx][fbBuyPrice]),
		FBizzInfo[idx][fbPriceMode] == 0 ? ("{00BFFF}Cash") : ("{F3DE3E}Ouro"),
		FBizzInfo[idx][fbMessage],
		getFormatText(FBizzInfo[idx][fbTill]),
		FBizzInfo[idx][fbProducts],
		FBizzInfo[idx][fbProductsReq],
		getFormatText(FBizzInfo[idx][fbPriceProd]));

		Update3DTextLabelText(FBizzInfo[idx][fbLabelid], 0xFFFFFFAA, gstring);
	}
	else
	{
		FBizzInfo[idx][fbPickupid] = CreatePickup(1580, 1, FBizzInfo[idx][fbEntranceX], FBizzInfo[idx][fbEntranceY], FBizzInfo[idx][fbEntranceZ]);
		format(gstring, sizeof(gstring),
		"{FFFFFF}Fazenda\n\
		{FFFFFF}Dono: {00AA00}%s\n\
		{FFFFFF}Nome: {00FFFF}%s\n\
		{FFFFFF}Fundos: {00FFFF}$%s\n\
		{FFFFFF}Produtos: {00FFFF}%d\n\
		{FFFFFF}Produtos Requeridos: {00FFFF}%d\n\
		{FFFFFF}Preço por produto: {00FFFF}$%s\n\
		{FFFFFF}Insumos: {00FFFF}%d\n\
		{FFFFFF}Preço por insumo: {00FFFF}$%s",
		FBizzInfo[idx][fbOwner],
		FBizzInfo[idx][fbMessage],
		getFormatText(FBizzInfo[idx][fbTill]),
		FBizzInfo[idx][fbProducts],
		FBizzInfo[idx][fbProductsReq],
		getFormatText(FBizzInfo[idx][fbPriceProd]),
		FBizzInfo[idx][fbInsumos],
		getFormatText(FBizzInfo[idx][fbPrecoInsumo]));

        Update3DTextLabelText(FBizzInfo[idx][fbLabelid], 0xFFFFFFAA, gstring);
	}
}

stock Fazenda_Salvar(idx)
{
	if (!Iter_Contains(Fazendas, idx))
	    return 0;

	new query[600], date[20];

	new dono[MAX_PLAYER_NAME] = "NULL";
	if(FBizzInfo[idx][fbOwnerID] > 0)
		format(dono, 25, "%d", FBizzInfo[idx][fbOwnerID]);

	TimeFormat(FBizzInfo[idx][fbDate], ISO6801_DATE, date);
	mysql_format(MySQL_Handle, query, sizeof(query), "UPDATE fazendas SET descricao='%e', dono=%s, entradaX=%f, \
		entradaY=%f, entradaZ=%f, preco=%d, precoModo=%d, cofre=%d, trancada=%d, produtos=%d, \
		maximoProdutos=%d, precoProdutos=%d, produtosRequeridos=%d, protecao=%d, insumos=%d, precoInsumo=%d, vencimento='%s' WHERE id = %d",
		FBizzInfo[idx][fbMessage], dono, FBizzInfo[idx][fbEntranceX], FBizzInfo[idx][fbEntranceY], FBizzInfo[idx][fbEntranceZ], 
		FBizzInfo[idx][fbBuyPrice], FBizzInfo[idx][fbPriceMode], FBizzInfo[idx][fbTill], 
		FBizzInfo[idx][fbLocked], FBizzInfo[idx][fbProducts], FBizzInfo[idx][fbMaxProducts], FBizzInfo[idx][fbPriceProd], 
		FBizzInfo[idx][fbProductsReq], FBizzInfo[idx][fbProtection], FBizzInfo[idx][fbInsumos], FBizzInfo[idx][fbPrecoInsumo], date, FBizzInfo[idx][fbID]);
	mysql_tquery(MySQL_Handle, query);

	return 1;
}

CMD:fazenda(playerid, const params[])
{
    if (sscanf(params, "s[128]", params))
	{
	    SendClientMessage(playerid, -1, "Modo de uso: /fazenda (nome)");
	    SendClientMessage(playerid, COLOR_GRAD, "NOMES: ajuda | comprar | vender | nome | precoproduto | pedirprodutos | precoinsumo");
		SendClientMessage(playerid, COLOR_GRAD, "NOMES: sacar | depositar | entrada | melhorarcofre | chave");

	    if (Admin_GetNivel(playerid) >= MASTER)
	    	SendClientMessage(playerid, COLOR_GRAD, "NOMES: criar | destruir | preco | precomodo | produtos | dono | ir");
	    	
 		SendClientMessage(playerid, COLOR_GRAD, "_________________________________________________");
		return true;
	}

	new null[25], string[128];

	if (!strcmp(params, "ajuda", true)) {
		return cmd_ajudafazenda(playerid);
	}
	
	else if(strfind(params, "trazer", true) != -1) 
	{
		if(Admin_GetNivel(playerid) < DONO)
		    return SendClientMessage(playerid, -1, "	Você não pode usar este comando!");

		new idemp;
		if(sscanf(params, "s[24]d", null, idemp))
			return SendClientMessage(playerid,-1, "Use: /fazenda trazer [ID]");

		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		FBizzInfo[idemp][fbEntranceX] = x;
		FBizzInfo[idemp][fbEntranceY] = y;
		FBizzInfo[idemp][fbEntranceZ] = z;
		Fazenda_Salvar(idemp);
	}
	else if (strfind(params, "criar", true) != -1)
	{
		if (Admin_GetNivel(playerid) < DONO) return SendClientMessage(playerid, -1, "Você não pode usar este comando!");

		new preco;
		if (sscanf(params, "s[25]d", null, preco)) return SendClientMessage(playerid, -1, "Modo de uso: /fazenda criar (preco)");

		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);

		new idx = Fazenda_Create(x, y, z, .price=preco);
		if (idx != -1)
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você criou uma fazenda neste local.");
		else 
			SendClientMessage(playerid, -1, "Limite de fazendas excedido.");
	}

	else if (!strcmp(params, "destruir", true))
	{
		if (Admin_GetNivel(playerid) < DONO) {
			return SendClientMessage(playerid, -1, "Você não pode usar este comando!");
		}

		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1)
			return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		if (Fazenda_Destroy(fazendaid))
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Fazenda destruida com sucesso.");
		else
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Não foi possível destruir esta fazenda.");
	}

	else if (strfind(params, "chave", true) != -1)
	{
		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1)
			return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		if (!Fazenda_IsOwner(fazendaid, Player_GetAccountID(playerid)))
			return SendClientMessage(playerid, -1, "Você não é o proprietário dessa fazenda.");

		if(FBizzInfo[fazendaid][fbLocked] == 1) {
			FBizzInfo[fazendaid][fbLocked] = 0;
			ShowPlayerMessage(playerid, "~w~Fazenda ~g~aberta", 5000);
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		} else {
			FBizzInfo[fazendaid][fbLocked] = 1;
			ShowPlayerMessage(playerid, "~w~Fazenda ~r~fechada", 5000);
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		}
	}

	else if (strfind(params, "nome", true) != -1)
	{
		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1)
			return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		new nome[64];
		if (sscanf(params, "s[25]s[64]", null, nome)) return SendClientMessage(playerid, -1, "Modo de uso: /fazenda nome (nome)");

		if (Fazenda_IsOwner(fazendaid, Player_GetAccountID(playerid)))
		{
			format(string, sizeof(string), "FAZENDA %d: nome mudado para {00FFFF}%s", fazendaid, nome);
			SendClientMessage(playerid, -1, string);
			strmid(FBizzInfo[fazendaid][fbMessage], nome, 0, strlen(nome), 255);

			Fazenda_Salvar(fazendaid);
			Fazenda_UpdateLabel(fazendaid);
		} else {
			SendClientMessage(playerid, -1, "Essa fazenda não é sua!");
		}
	}

	else if (strfind(params, "precoproduto", true) != -1)
	{
		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1)
			return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		if (!Fazenda_IsOwner(fazendaid, Player_GetAccountID(playerid)))
			return SendClientMessage(playerid, -1, "Essa fazenda não é sua.");

		new amount;
		if (sscanf(params, "s[25]d", null, amount)) return SendClientMessage(playerid, -1, "Modo de uso: /fazenda precoproduto (preco)");

		if (amount < 10 || amount > 400)
			return SendClientMessage(playerid, -1, "A quantia mínima é $10, a quantia máxima é $400.");

		if(gettime() < GetPVarInt(playerid, "VarFloodPrecoProdutoFazenda"))
			return SendClientMessage(playerid, COLOR_GRAD, "Você precisa esperar alguns segundos para usar esse comando novamente");

		SetPVarInt(playerid, "VarFloodPrecoProdutoFazenda", gettime()+20);

		FBizzInfo[fazendaid][fbPriceProd] = amount;

		format(string, sizeof(string), "FAZENDA: Você alterou o preço de compra dos produtos para $%s.", getFormatText(FBizzInfo[fazendaid][fbPriceProd]));
		SendClientMessage(playerid, -1, string);

		SendMsgAllF(-1, "A {00FFFF}Fazenda %d {FFFFFF}alterou o preço dos produtos para {00AA00}$%s/produto", fazendaid, getFormatText(FBizzInfo[fazendaid][fbPriceProd]));
		Fazenda_Salvar(fazendaid);
		Fazenda_UpdateLabel(fazendaid);
	}

	else if (strfind(params, "precoinsumo", true) != -1)
	{
		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1)
			return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		if (!Fazenda_IsOwner(fazendaid, Player_GetAccountID(playerid)))
			return SendClientMessage(playerid, -1, "Essa fazenda não é sua.");

		new amount;
		if (sscanf(params, "s[25]d", null, amount)) return SendClientMessage(playerid, -1, "Modo de uso: /fazenda precoinsumo (preco)");

		if (amount < 10 || amount > 400)
			return SendClientMessage(playerid, -1, "A quantia mínima é $10, a quantia máxima é $400.");

		if(gettime() < GetPVarInt(playerid, "VarFloodPrecoInsumoFazenda"))
			return SendClientMessage(playerid, COLOR_GRAD, "Você precisa esperar alguns segundos para usar esse comando novamente");

		SetPVarInt(playerid, "VarFloodPrecoInsumoFazenda", gettime()+20);

		FBizzInfo[fazendaid][fbPrecoInsumo] = amount;

		format(string, sizeof(string), "FAZENDA: Você alterou o preço de compra dos insumos para $%s.", getFormatText(FBizzInfo[fazendaid][fbPrecoInsumo]));
		SendClientMessage(playerid, -1, string);

		SendMsgAllF(-1, "A {00FFFF}Fazenda %d {FFFFFF}alterou o preço dos insumos para {00AA00}$%s/insumo", fazendaid, getFormatText(FBizzInfo[fazendaid][fbPrecoInsumo]));
		Fazenda_Salvar(fazendaid);
		Fazenda_UpdateLabel(fazendaid);
	}

	else if (strfind(params, "pedirprodutos", true) != -1)
	{
		new fazendaid = Fazenda_GetId(playerid);
		if (fazendaid == -1) return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");
		if (!Fazenda_IsOwner(fazendaid, Player_GetAccountID(playerid))) return SendClientMessage(playerid, -1, "Essa fazenda não é sua.");

		new amount;
		if (sscanf(params, "s[25]d", null, amount)) return SendClientMessage(playerid, -1, "Modo de uso: /fazenda pedirprodutos (preco)");
		if (amount < 0 || amount > 40000) return SendClientMessage(playerid, -1, "A quantia mínima é 1, a quantia máxima é 40.000.");
		if (FBizzInfo[fazendaid][fbProducts] > 40000) return SendClientMessage(playerid, -1, "A fazenda já está com 40.000 produtos ou mais, espere abaixar para pedir.");

		if(gettime() < GetPVarInt(playerid, "VarFloodPedirProdutosFazenda"))
			return SendClientMessage(playerid, COLOR_GRAD, "Você precisa esperar alguns segundos para usar esse comando novamente");

		SetPVarInt(playerid, "VarFloodPedirProdutosFazenda", gettime()+20);

		FBizzInfo[fazendaid][fbProductsReq] = amount;
		format(string, sizeof(string), "FAZENDA: Você anunciou a solicitação de %d produtos.", FBizzInfo[fazendaid][fbProductsReq]);
		SendClientMessage(playerid, -1, string);
		SendMsgAllF(-1, "A {00FFFF}Fazenda %d {FFFFFF}está precisando de {00FFFF}%d produtos {FFFFFF}pelo preço de {00AA00}$%s por produto", fazendaid, FBizzInfo[fazendaid][fbProductsReq], getFormatText(FBizzInfo[fazendaid][fbPriceProd]));
		Fazenda_Salvar(fazendaid);
		Fazenda_UpdateLabel(fazendaid);
	}

	else if (strfind(params, "sacar", true) != -1)
	{
		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1)
			return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		if (!Fazenda_IsOwner(fazendaid, Player_GetAccountID(playerid)))
			return SendClientMessage(playerid, -1, "Essa fazenda não é sua.");

		new quant;
		if (sscanf(params, "s[25]d", null, quant))
		{
			format(string, sizeof(string), "  Você tem $%s no cofre da fazenda.", getFormatText(FBizzInfo[fazendaid][fbTill]));
			SendClientMessage(playerid, COLOR_GRAD, string);
			SendClientMessage(playerid, -1, "Use: /fazenda sacar [quantidade]");
			return 1;
		}

		if(quant > FBizzInfo[fazendaid][fbTill] || quant < 1)
			return SendClientMessage(playerid, -1, "Você não tem essa quantia em sua Fazenda.");

		Player_AddMoney(playerid, quant);
		FBizzInfo[fazendaid][fbTill] -= quant;
		format(string, sizeof(string), "FAZENDA: Você retirou $%s de sua fazenda - restante: $%s ", getFormatText(quant), getFormatText(FBizzInfo[fazendaid][fbTill]));
		SendClientMessage(playerid, COLOR_YELLOW, string);
		Fazenda_Salvar(fazendaid);
		Fazenda_UpdateLabel(fazendaid);
		ServerLog::("fazendas", "%s sacou $%d da fazenda %d - saldo $%d", PlayerName[playerid], quant, FBizzInfo[fazendaid][fbTill]);
	}

	else if (strfind(params, "depositar", true) != -1)
	{
		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1)
			return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		if (!Fazenda_IsOwner(fazendaid, Player_GetAccountID(playerid)))
			return SendClientMessage(playerid, -1, "Essa fazenda não é sua.");

		new quant;
		if (sscanf(params, "s[25]d", null, quant))
		{
			format(string, sizeof(string), "  Você tem $%s no cofre da fazenda.", getFormatText(FBizzInfo[fazendaid][fbTill]));
			SendClientMessage(playerid, COLOR_GRAD, string);
			SendClientMessage(playerid, -1, "Use: /fazenda depositar [quantidade]");
			return 1;
		}

		if(quant > Player_GetMoney(playerid) || quant < 1)
			return SendClientMessage(playerid, -1, "Você não tem essa quantia de dinheiro em mãos.");

		Player_RemoveMoney(playerid, quant);
		FBizzInfo[fazendaid][fbTill] += quant;
		format(string, sizeof(string), "FAZENDA: Você guardou $%s nessa fazenda. Novo saldo do cofre: $%s ", getFormatText(quant), getFormatText(FBizzInfo[fazendaid][fbTill]));
		SendClientMessage(playerid, COLOR_YELLOW, string);
		Fazenda_Salvar(fazendaid);
		Fazenda_UpdateLabel(fazendaid);
		ServerLog::("fazendas", "%s depositou $%d na fazenda %d - saldo $%d", PlayerName[playerid], quant, FBizzInfo[fazendaid][fbTill]);
	}

	else if (strfind(params, "precomodo", true) != -1)
	{
		if (Admin_GetNivel(playerid) < DONO) return true;

		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1) return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		new modo[24];
		if (sscanf(params, "s[25]s[24]", null, modo)) return SendClientMessage(playerid, -1, "Modo de uso: /fazenda precomodo (cash / ouros)");

		if(strcmp(modo, "cash", false) == 0) 
			FBizzInfo[fazendaid][fbPriceMode] = 0;
		else if(strcmp(modo, "ouros", false) == 0)
			FBizzInfo[fazendaid][fbPriceMode] = 1;
		else 
			return SendClientMessage(playerid, -1, "Modo de uso: /fazenda precomodo (cash / ouros)"); 

		format(string, sizeof(string), "FAZENDA %d: O modo de pagamento da fazenda foi modificado para %s.", fazendaid, 
			FBizzInfo[fazendaid][fbPriceMode] == 0 ? ("cash") : ("ouros"));
		SendClientMessage(playerid, -1, string);
		Fazenda_Salvar(fazendaid);
		Fazenda_UpdateLabel(fazendaid);
	}

	else if (strfind(params, "preco", true) != -1)
	{
		if (Admin_GetNivel(playerid) < DONO) return true;

		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1) return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		new valorFazenda;
		if (sscanf(params, "s[25]d", null, valorFazenda)) return SendClientMessage(playerid, -1, "Modo de uso: /fazenda preco (valor)");

		format(string, sizeof(string), "FAZENDA %d: O valor da fazenda foi modificado para {00FFFF}%d Cash", fazendaid, valorFazenda);
		SendClientMessage(playerid, -1, string);

		FBizzInfo[fazendaid][fbBuyPrice] = valorFazenda;
		Fazenda_Salvar(fazendaid);
		Fazenda_UpdateLabel(fazendaid);
	}

	else if (strfind(params, "produtos", true) != -1)
	{
		if (Admin_GetNivel(playerid) < DONO) return true;

		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1) return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		new quantidadeProdutos, motivo[30];
		if (sscanf(params, "s[25]ds[30]", null, quantidadeProdutos, motivo))
			return SendClientMessage(playerid, -1, "Modo de uso: /fazenda produtos (valor) (motivo)");

		format(string, sizeof(string), "FAZENDA %d: Recebeu %d produtos do %s, %s, motivo: %s.", fazendaid, quantidadeProdutos, Staff_GetPositionName(playerid), PlayerName[playerid], motivo);
		SendClientMessageToAll(-1, string);

		FBizzInfo[fazendaid][fbProducts] += quantidadeProdutos;
		FBizzInfo[fazendaid][fbProductsReq] -= quantidadeProdutos;

		Fazenda_Salvar(fazendaid);

		Fazenda_UpdateLabel(fazendaid);
	}

	else if (strfind(params, "dono", true) != -1)
	{
		if (Admin_GetNivel(playerid) < DONO) return true;

		new fazendaid = Fazenda_GetId(playerid);
		if (fazendaid == -1) return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		new namePlayer[MAX_PLAYER_NAME];
		if (sscanf(params, "s[25]s[24]", null, namePlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /fazenda dono (nick do jogador)");

		new id = Player_GetAccountIDByNick(namePlayer);
		if(id != -1) {
			Fazenda_SetOwnerOffline(fazendaid, id);
			FBizzInfo[fazendaid][fbDate] = Now() + Days:3;
			Fazenda_Salvar(fazendaid);
			Fazenda_UpdateLabel(fazendaid);
		}
		else
			SendClientMessage(playerid, -1, "Jogador inexistente.");
	}

	else if (!strcmp(params, "comprar", true))
	{
		if (Player_GetVIP(playerid) < 1) return SendClientMessage(playerid, -1, "Apenas jogadores VIP+ podem comprar fazenda.");

		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1)
			return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		if (Fazenda_IsOwned(fazendaid))
			return SendClientMessage(playerid, -1, "Esta fazenda já possui um dono.");

		new count = Fazenda_Count(playerid);

		if (count >= 1 && Player_GetVIP(playerid) < 6)
			return SendClientMessage(playerid, -1, "Apenas jogadores SÓCIO-GOLD+ pode ter mais de uma fazenda.");

		if (count >= 2 && Player_GetVIP(playerid) < 7)
			return SendClientMessage(playerid, -1, "Apenas jogadores SÓCIO-PLATINA+ pode ter mais de duas fazendas.");

		if (count >= MAX_PLAYER_FAZENDAS)
			return SendClientMessage(playerid, -1, "Você já excedeu o limite de fazendas por conta.");

		if (FBizzInfo[fazendaid][fbPriceMode] == 0 && Player_GetCash(playerid) >= FBizzInfo[fazendaid][fbBuyPrice]) {
			Player_SetCash(playerid, Player_GetCash(playerid) - FBizzInfo[fazendaid][fbBuyPrice]);
		}
		else if (FBizzInfo[fazendaid][fbPriceMode] == 1 && Player_GetOuros(playerid) >= FBizzInfo[fazendaid][fbBuyPrice]) {
			Player_SetOuros(playerid, Player_GetOuros(playerid) - FBizzInfo[fazendaid][fbBuyPrice]);
		}
		else {
			return SendClientMessage(playerid, -1, "Você não tem recurso suficiente para comprar a fazenda.");
		}

		FBizzInfo[fazendaid][fbLocked] = 0;
		SendClientMessage(playerid, -1, "Parabéns você comprou uma {00FFFF}fazenda{FFFFFF}, use {00FFFF}/ajudafazenda {FFFFFF}para mais informações!");
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		FBizzInfo[fazendaid][fbDate] = Now() + Days:3;
		Fazenda_SetOwner(fazendaid, playerid);
		format(string, sizeof(string), "%s comprou a fazenda (ID: %d)", PlayerName[playerid], fazendaid);
		server_log("fazendas", string);
	}

	else if (!strcmp(params, "vender", true))
	{
		new fazendaid = Fazenda_GetId(playerid);

		if (fazendaid == -1)
			return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		if (GetPVarInt(playerid, "p_intrade"))
			return 1;

		if (Fazenda_IsOwner(fazendaid, Player_GetAccountID(playerid)))
		{
			if (FBizzInfo[fazendaid][fbPriceMode] == 0) {
				Player_SetCash(playerid, Player_GetCash(playerid) + FBizzInfo[fazendaid][fbBuyPrice]/2);
			}
			else if (FBizzInfo[fazendaid][fbPriceMode] == 1) {
				Player_SetOuros(playerid, Player_GetOuros(playerid) + FBizzInfo[fazendaid][fbBuyPrice]/2);
			}
			
			format(string, sizeof(string), "~w~Parabens~n~ Voce vendeu a fazenda por ~n~~g~%d de %s", FBizzInfo[fazendaid][fbBuyPrice]/2,
				FBizzInfo[fazendaid][fbPriceMode] == 0 ? ("cash") : ("ouros"));
			FBizzInfo[fazendaid][fbLocked] = 0;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			GameTextForPlayer(playerid, string, 10000, 3);

			Fazenda_SetOwner(fazendaid, -1);

			format(string, sizeof(string), "%s vendeu sua Fazenda ID: %d", PlayerName[playerid], fazendaid);
			server_log("fempresas", string);
		} else {
			SendClientMessage(playerid, -1, "Essa fazenda não é sua!");
		}
	}

	else if (!strcmp(params, "info", true))
	{
		new fazendaid = Fazenda_GetId(playerid);
		if (fazendaid == -1)
			return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		if (Fazenda_IsOwner(fazendaid, Player_GetAccountID(playerid)))
		{
			PrintFBizInfo(playerid, fazendaid);
		} else {
			SendClientMessage(playerid, -1, "Essa fazenda não é sua!");
		}
	}

	else if (!strcmp(params, "melhorarcofre", true))
	{
		if (Fazenda_Count(playerid) == 0) {
			return SendClientMessage(playerid, -1, "Você não possui uma fazenda.");
		}

		new fazendaid = Fazenda_GetId(playerid);
		if (fazendaid == -1)
			return SendClientMessage(playerid, -1, "Você não está perto de nenhuma fazenda.");

		if (Fazenda_IsOwner(fazendaid, Player_GetAccountID(playerid)))
		{
			MEGAString[0] = EOS;
			strcat(MEGAString, "Nível da proteção\tCusto\tAcréscimo de proteção\n");

			for(new idx = 1; idx < 11; idx++) {
				format(string, sizeof string, "Proteção nível %d\t{00AA00}$%s\t{00DDFF}+%.1f\n", idx, getFormatText(idx * 15000), idx * 100.0);
				strcat(MEGAString, string);
			}
			ShowPlayerDialog(playerid, 5252, DIALOG_STYLE_TABLIST_HEADERS, "Proteção para o cofre de sua fazenda", MEGAString, "Comprar", "Cancelar");
		} else {
			SendClientMessage(playerid, -1, "Essa fazenda não é sua!");
		}
	}

	else if (strfind(params, "ir", true) != -1)
	{
		if (Admin_GetNivel(playerid) < MASTER) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

		if (Staff_GetWorking(playerid) < 1 && Admin_GetNivel(playerid) < DONO) return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

		new idFazenda;
		if(sscanf(params, "s[24]d", null, idFazenda)) return SendClientMessage(playerid, -1, "Modo de uso: /fazenda ir (id da fazenda)");

		SetPlayerPos(playerid, FBizzInfo[idFazenda][fbEntranceX], FBizzInfo[idFazenda][fbEntranceY], FBizzInfo[idFazenda][fbEntranceZ]);
	}
	return true;
}

CMD:minhasfazendas(playerid)
{
	new string_emp[128];

	new count;

    MEGAString[0] = EOS;

	strcat(MEGAString, "Fazenda ID\tDono\tProdutos req.\tPreço prod.\n");

	foreach(new e : Fazendas)
	{
	    if (!Fazenda_IsOwner(e, Player_GetAccountID(playerid)))
			continue;

 		format(string_emp, sizeof (string_emp), "Fazenda %02d\t%s\t%d\t$%d\n", e, FBizzInfo[e][fbOwner], FBizzInfo[e][fbProductsReq], FBizzInfo[e][fbPriceProd]);
   		strcat(MEGAString, string_emp);

		SelectFazendas[playerid][count] = e;

		count++;
	}

	if (!count)
	    return SendClientMessage(playerid, COLOR_GREY, "Você não possui nenhuma fazenda.");

	ShowPlayerDialog(playerid, 7254, DIALOG_STYLE_TABLIST_HEADERS, "Localizar Fazenda", MEGAString, "Selecionar", "Voltar");

	return 1;
}

CMD:roubarfazenda(playerid)
{
	if(!IsAMember(playerid))
	{
		SendClientMessage(playerid,-1, "Apenas organizações criminosas podem roubar cofres !");
		return true;
	}

	if(Player_GetExplosivos(playerid) < 1)
		return SendClientMessage(playerid, -1, "Você não tem um explosivo, compre um no mercado negro.");

	if (!GetPlayerHoldingExplosive(playerid)) 
			return SendClientMessage(playerid, -1, "Você não está segurando um explosivo. (Use: /explosivo pegar)");

	if (!IsPlayerInRangeOfPoint(playerid, 2.0, 279.7973, 308.7788, 1002.7976)) {
		return SendClientMessage(playerid, -1, "Você não está no cofre da fazenda!");
	}

	new string[144];

	new id = GetPlayerVirtualWorld(playerid);

	if (FBizzInfo[id][fbRoubado]) {
		SendClientMessage(playerid, COLOR_LIGHTRED, "* O cofre dessa fazenda já está explodido!");
		return 1;
	}

	if (gettime() < FBizzInfo[id][fbTempoRoubado]) {
		format(string, sizeof string, "* O cofre dessa fazenda já foi explodido recentemente, aguarde %s para roubar novamente!", ConvertTime(FBizzInfo[id][fbTempoRoubado] - gettime()));
		SendClientMessage(playerid, COLOR_LIGHTRED, string);
		return 1;
	}

	foreach(new x : Player) {

		if (GetPlayerVirtualWorld(x) == id && GetPVarInt(x, "ExplodindoCofre")) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, "* Alguém já colocou um explosivo na porta, aguarde detonar...");
		}
	}

	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	SetPlayerPos(playerid, 280.5806,308.7981,1003.3943);
	SetPlayerFacingAngle(playerid, 89.5718);

	SetPVarInt(playerid, "ExplodindoCofre", 1);

	ApplyAnimation(playerid, "CAMERA","piccrch_take", 4.0, 1, 0,0,0,0);
	SetTimerEx("ExplodirCofreFazenda", 20 * 1000, false, "d", playerid);

	SetTimerEx(#SetAnimCofre, 500, false, "d", playerid);

	if (gettime() > FBizzInfo[id][fbRouboAnunciado]) {

		format(string, sizeof string, "ROUBO: %s e %s %s estão roubando a Fazenda: %d", PlayerName[playerid], GetOrgArticle(GetPlayerOrg(playerid)), GetOrgName(GetPlayerOrg(playerid)), id);
		SendCopMessage(COLOR_LIGHTRED, string);
		SendClientMessageInRange(30.0, playerid, string, COLOR_LIGHTRED,COLOR_LIGHTRED,COLOR_LIGHTRED,COLOR_LIGHTRED,COLOR_LIGHTRED);
		SetPlayerCriminal(playerid,255,"Assalto ao cofre");
		FBizzInfo[id][fbRouboAnunciado] = gettime() + (10 * 60);
	}

	SendClientMessage(playerid, COLOR_GRAD, "*Você está colocando uma bomba no cofre, aguarde...");

	GameTextForPlayer(playerid, "~r~plantando bomba...", 5000, 1);

	ShowPlayerBaloonInfo(playerid, "Espere a bomba ser plantada, depois afaste-se", 5000);
	return 1;
}

CALLBACK:ExplodirCofreFazenda(playerid)
{
	if (!IsPlayerInRangeOfPoint(playerid, 2.0, 279.7973, 308.7788, 1002.7976) || !IsPlayerConnected(playerid))
	{
		SetPVarInt(playerid, "ExplodindoCofre", 0);
		return SendClientMessage(playerid, COLOR_LIGHTRED, " Explosão abortada! você não está perto suficiênte do cofre !");
	}

	SetPVarInt(playerid, "objectExplosao", CreateDynamicObject(1654, 280.17468, 308.77490, 1002.86517,   0.00000, 0.00000, 89.13200, GetPlayerVirtualWorld(playerid)));

	Player_SetExplosivo(playerid, 0);
	SetPlayerExplosive(playerid, false);
	RemovePlayerAttachedObject(playerid, 2); // Slot_Explosivo
	SetTimerEx("ExplosaoCofreFazenda", 10000, false, "d", playerid);

	SendClientMessage(playerid, COLOR_LIGHTRED, "* Você plantou uma bomba no cofre, agora afaste-se e espere explodir !");
	GameTextForPlayer(playerid, "~r~afaste-se do cofre", 5000, 1);
	ClearAnimations(playerid, SYNC_ALL);
	return 1;
}
CALLBACK:ExplosaoCofreFazenda(playerid) {

	SetPVarInt(playerid, "ExplodindoCofre", 0);

	DestroyDynamicObject(GetPVarInt(playerid, "objectExplosao"));
	SetPVarInt(playerid, "objectExplosao", -1);

	CreateExplosionEx(279.7973, 308.7788, 1002.7976, 12, 1.0, GetPlayerVirtualWorld(playerid));

	new id = GetPlayerVirtualWorld(playerid);

	new Float: danoCofre = 100.0 + randomfloat(100.0);

	FBizzInfo[id][fbCofreHealth] -= danoCofre;

	if (FBizzInfo[id][fbCofreHealth] <= 0.0) {

		FBizzInfo[id][fbRoubado] 		= true;
		FBizzInfo[id][fbTempoRoubado] 	= gettime() + (3 * (60 * 60)); // 3 horas pra roubar novamente

		// Destruir cofre
		DestroyDynamicObject(FBizzInfo[id][fbCofre]);
		FBizzInfo[id][fbCofre] = CreateDynamicObject(1829, 280.11200, 308.79550, 1002.84259,   0.00000, 0.00000, 89.44640, id);

		UpdateDynamic3DTextLabelText(FBizzInfo[id][fbCofreLabel], 0xFFAA00BB, "Cofre da fazenda\nDano: {FF0000}QUEBRADO\n{FFFFFF}/pegardinheiro");

		SetTimerEx("restaurarFazenda", 20 * 60000, false, "d", id);

		return 1;
	}

	new string[75];

	format(string, sizeof string, "Cofre da fazenda\nDano: %.1f\n{356FB2}Use: /roubarfazenda", FBizzInfo[id][fbCofreHealth]);
	UpdateDynamic3DTextLabelText(FBizzInfo[id][fbCofreLabel], 0xFFAA00BB, string);

	return 1;
}

CALLBACK: restaurarFazenda(id) {

	FBizzInfo[id][fbRoubado] 		= false;
	FBizzInfo[id][fbCofreHealth]    = 100.0 + (FBizzInfo[id][fbProtection] * 100.0);
	FBizzInfo[id][fbRouboAnunciado] = 0;

	// Reconstruir cofre
	DestroyDynamicObject(FBizzInfo[id][fbCofre]);
	FBizzInfo[id][fbCofre] = CreateDynamicObject(1829, 280.11200, 308.79550, 1002.84259,   0.00000, 0.00000, 89.44640, id);

	// Update na 3d text
	new string[75];

	format(string, sizeof string, "Cofre da fazenda\nDano: %.1f\n{356FB2}Use: /roubarfazenda", FBizzInfo[id][fbCofreHealth]);
	UpdateDynamic3DTextLabelText(FBizzInfo[id][fbCofreLabel], 0xFFAA00BB, string);
	return 1;
}

CMD:pegardinheiro(playerid) {

	new id = GetPlayerVirtualWorld(playerid);

	if ( id != -1 ) {

		if (!IsPlayerInRangeOfPoint(playerid, 2.0, 279.7973, 308.7788, 1002.7976)) {
			return SendClientMessage(playerid, -1, "Você não está no cofre de nenhuma fazenda!");
		}

		if (!FBizzInfo[id][fbRoubado]) {
			SendClientMessage(playerid, COLOR_LIGHTRED, "* O cofre dessa fazenda não está explodido!");
			return 1;
		}

		if ( !IsAMember(playerid) ) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode roubar o cofre !");
		}

		if(gettime() < Player_GetTempoRoubou(playerid)) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você já pegou dinheiro de algum cofre recentemente, aguarde 5 minutos para poder pegar mais !");
		}

		if ( GetPVarInt(playerid, "pegandoGrana") ) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você já está roubando !");
		}

		if (FBizzInfo[id][fbTill] < 1) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, "* Este cofre não tem mais dinheiro !");
		}

		SetPVarInt(playerid, "pegandoGrana", 1);
		ApplyAnimation(playerid,"ROB_BANK","CAT_Safe_Rob",4.1,1,0,0,0,0);
		SetTimerEx(#ApplyAnim, 500, false, "i", playerid); // Slot_Explosivo
		SetPlayerAttachedObject(playerid, 2, 1550,1,-0.068000,0.382000,-0.109999,-91.699996,101.200012,-149.300003,1.000000,1.000000,1.000000);
		SetTimerEx("pegarGranaCofreFazenda", 50000, false, "ii", playerid, id);
		SetPlayerFaceToPoint(playerid, 279.7973, 308.7788);

	} else {
		SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está perto do dinheiro do cofre de nenhuma empresa !");
	}

	return 1;
}

CALLBACK: pegarGranaCofreFazenda( playerid, id ) {

	SetPVarInt(playerid, "pegandoGrana", 0);
	if ( !IsPlayerConnected(playerid) || GetPlayerVirtualWorld(playerid) != id || !IsPlayerInRangeOfPoint(playerid, 4.0, 279.7973, 308.7788, 1002.7976)) {

		ClearAnimations(playerid);
		RemovePlayerAttachedObject(playerid, 2); //Slot_Explosivo

		return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está no cofre que estava roubando !");
	}

	new value = FBizzInfo[id][fbTill] / (20 + random(5));

	if (FBizzInfo[id][fbTill] > value) {
		FBizzInfo[id][fbTill] -= value;
	} else {
		value = FBizzInfo[id][fbTill];
		FBizzInfo[id][fbTill] = 0;
	}

	Fazenda_Salvar(id);
	Fazenda_UpdateLabel (id);

	Player_SetTempoRoubou(playerid, gettime() + (5 * 60));
	Player_AddMoney(playerid, value);

	new string[128];
	format(string, sizeof string, "* Você pegou uma bolsa com $%s do cofre, agora saia o mais rápido possível, pois a polícia foi avisada !", getFormatText(value));
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

	ClearAnimations(playerid);
	SetPlayerAttachedObject(playerid, 2, 1550, 1, 0.000000, -0.313611, 0.021003, 0.445490, 86.754409, 355.370239, 0.926815, 1.000000, 1.000000); // Slot_Explosivo

	return 1;
}