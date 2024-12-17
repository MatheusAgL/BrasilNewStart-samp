#include <YSI_Coding\y_hooks>

#include <farms_entry>

hook OnPlayerLogin(playerid) 
{
	new string[128];

	foreach(new farm : Fazendas) {
		if (Player_GetAccountID(playerid) == Farm_GetOwner(farm)) {
			Farm_SetDate(farm, Now() + Days:3);

			format(string, sizeof(string), "Fazendas: %s entrou no servidor, dono da fazenda: %d", PlayerName[playerid], farm);
			server_log("fazendas", string);
		}
	}
}

stock Fazenda_Create(Float:x, Float:y, Float:z, const owner[] = "The State", const discription[] = "Fazenda "SERVER_TAG"", price = 1000000, mode = 0)
{
	new farm = Iter_Free(Farms),
		query[600];

	if (farm != -1)
	{
	    Iter_Add(Fazendas, idx);
		FBizzInfo[idx][fbOwnerID] = -1;
	    format(FBizzInfo[idx][fbOwner], MAX_PLAYER_NAME, owner);
	    format(FBizzInfo[idx][fbMessage], 128, discription);

	    FBizzInfo[idx][fbEntranceX] = x;
	    FBizzInfo[idx][fbEntranceY] = y;
	    FBizzInfo[idx][fbEntranceZ] = z;

	    FBizzInfo[idx][fbBuyPrice] = price;
		FBizzInfo[idx][fbPriceMode] = mode;
	    FBizzInfo[idx][fbTill] = 0;
	    FBizzInfo[idx][fbLocked] = 0;
	    FBizzInfo[idx][fbProducts] = 0;
	    FBizzInfo[idx][fbMaxProducts] = 0;
	    FBizzInfo[idx][fbPriceProd] = 1;
	    FBizzInfo[idx][fbProductsReq] = 0;
	    FBizzInfo[idx][fbProtection] = 1;
	    FBizzInfo[idx][fbDate] = Now() + Days:3;

		FBizzInfo[idx][fbInsumos] = 0;
		FBizzInfo[idx][fbPrecoInsumo] = 1;

	    FBizzInfo[idx][fbRoubado] 		 = false;
	    FBizzInfo[idx][fbCofreHealth]    = 100.0 + (FBizzInfo[idx][fbProtection] * 100.0);
	    FBizzInfo[idx][fbRouboAnunciado] = 0;

	    FBizzInfo[idx][fbCofre] = CreateDynamicObject(2332, 279.79730, 308.77884, 1002.79761,   0.00000, 0.00000, 89.44640, idx);
		FBizzInfo[idx][fbPickupid] = -1;

		mysql_format(MySQL_Handle, query, sizeof(query), "INSERT INTO fazendas (descricao, entradaX, entradaY, entradaZ, preco, precoModo, \
			cofre, trancada, produtos, maximoProdutos, precoProdutos, produtosRequeridos, protecao, vencimento, insumos, precoInsumo) VALUES \
			('%s', %f, %f, %f, %d, %d, 150, 0, 0, 0, 0, 1, 0, 1, NOW(), 0, 1);", FBizzInfo[idx][fbMessage], x, y, z, price, mode);
		mysql_query(MySQL_Handle, query);

		FBizzInfo[idx][fbID] = cache_insert_id();

	    new gstring[256];

		format(gstring, sizeof gstring, "Cofre da fazenda\nDano: %.1f\n{FFFFFF}Use: /roubarfazenda", FBizzInfo[idx][fbCofreHealth]);
		FBizzInfo[idx][fbCofreLabel] = CreateDynamic3DTextLabel(gstring, 0xFFAA00BB, 279.79730, 308.77884, 1002.79761, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, idx);

		FBizzInfo[idx][fbLabelid] = Create3DTextLabel("Erro ao carregar a fazenda...", 0xE6D4D1FF, FBizzInfo[idx][fbEntranceX], FBizzInfo[idx][fbEntranceY], FBizzInfo[idx][fbEntranceZ]+0.5,20.0,0);

	 	Fazenda_Salvar(idx);
		Fazenda_UpdateLabel(idx);
	}
	return idx;
}

stock Fazenda_Destroy(idx)
{
	if (Iter_Contains(Fazendas, idx))
	{
	    Iter_Remove(Fazendas, idx);

	    Farm_DestroyPickup(idx);
	    Delete3DTextLabel(FBizzInfo[idx][fbLabelid]);

	    DestroyDynamicObject(FBizzInfo[idx][fbCofre]);
	    DestroyDynamic3DTextLabel(FBizzInfo[idx][fbCofreLabel]);

	    new query[300];
		mysql_format(MySQL_Handle, query, sizeof(query), "DELETE FROM fazendas WHERE id = %d", idx);
		mysql_query(MySQL_Handle, query);

		return 1;
	}
	return 0;
}