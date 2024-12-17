#if defined _inc_marketplace
	#endinput
#endif
#define _inc_marketplace true

#include <YSI_Coding\y_hooks>

#define MAX_MARKETPLACE_ANNOUNCES 100

#include <marketplace_textdraws>        // Textdraws

enum MARKETPLACE_ENUM {
    mpID,
    mpPlayer,
    mpPrice,
    mpTypePrice,
    mpName[35],
    mpType,
    mpModel,
    mpQuantity,
    mpColor1,
    mpColor2,
};
static MarketplaceInfo[MAX_MARKETPLACE_ANNOUNCES][MARKETPLACE_ENUM];

// ------------------------ MySQL Prepared ------------------------
static 
		Statement: stmt_insertMpItem,
		Statement: stmt_selectMpItens;

hook OnMySQLConnected() 
{
	static const query_insertMpItem[] = 
		"INSERT INTO `marketplace` (`id`, `player`, `price`, `price_type`, `nome`, `tipo`, `modelo`, `quantidade`, `cor1`, `cor2`) VALUES (NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
	;
	stmt_insertMpItem = MySQL_PrepareStatement(MySQL_Handle, query_insertMpItem);

    static const query_selectMpItens[] = 
		"SELECT * FROM `marketplace`"
	;
	stmt_selectMpItens = MySQL_PrepareStatement(MySQL_Handle, query_selectMpItens);
	return 1;
}

hook OnPlayerLogin(playerid) 
{
	inline const OnLoadMarketplace() {

		new 
			mpID,
			mpPlayer,
            mpPrice,
            mpTypePrice,
            mpName[35],
            mpType,
            mpModel,
            mpQuantity,
            mpColor1,
            mpColor2
        ;

		MySQL_BindResultInt(stmt_selectMpItens, 0, mpID);
		MySQL_BindResultInt(stmt_selectMpItens, 1, mpPlayer);
        MySQL_BindResultInt(stmt_selectMpItens, 2, mpPrice);
        MySQL_BindResultInt(stmt_selectMpItens, 3, mpTypePrice);
		MySQL_BindResult(stmt_selectMpItens, 4, mpName, sizeof(mpName));
        MySQL_BindResultInt(stmt_selectMpItens, 5, mpType);
		MySQL_BindResultInt(stmt_selectMpItens, 6, mpModel);
		MySQL_BindResultInt(stmt_selectMpItens, 7, mpQuantity);
		MySQL_BindResultInt(stmt_selectMpItens, 8, mpColor1);
		MySQL_BindResultInt(stmt_selectMpItens, 9, mpColor2);

		while (MySQL_Statement_FetchRow(stmt_selectMpItens)) {
			new index = Iter_Free(IterMpItens);

			Iter_Add(IterMpItens, index);

            MarketplaceInfo[slot][mpID] = mpID;
			MarketplaceInfo[slot][mpPlayer] = mpPlayer;
            MarketplaceInfo[slot][mpPrice] = mpPrice;
            MarketplaceInfo[slot][mpTypePrice] = mpTypePrice;
            format(MarketplaceInfo[slot][mpName], mpName);
            MarketplaceInfo[slot][mpType] = mpType;
            MarketplaceInfo[slot][mpModel] = mpModel;
            MarketplaceInfo[slot][mpQuantity] = mpQuantity;
            MarketplaceInfo[slot][mpColor1] = mpColor1;
            MarketplaceInfo[slot][mpColor2] = mpColor2;
		}
	}
    MySQL_ExecuteThreaded_Inline(stmt_selectMpItens, using inline OnLoadMarketplace);
	return 1;
}

CMD:marketplace(playerid) {
    Marketplace_ShowTextdraws(playerid);
}