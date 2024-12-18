
#define MAX_PLAYER_TRADE_ITENS          (4)// N�o alterar
#define INVALID_UNIQUE_ID               (-1)

enum {
	TRADE_TYPE_INVALID,
	TRADE_TYPE_ITEM,        // Itens do invent�rio
	TRADE_TYPE_HOUSE,       // Casas
	TRADE_TYPE_FAZENDA,     // Fazendas
	TRADE_TYPE_PROPRIEDADE, // Propriedades
	TRADE_TYPE_VEICULOS,    // Ve�culos
}

enum p_trade_enum {
	p_trade_valid,
	p_trade_type,
	p_trade_unique_id, // Usado pra armazenar ID do item adicionado
}

new playerTradeItens[MAX_PLAYERS][MAX_PLAYER_TRADE_ITENS][p_trade_enum];

enum p_trade_e {
	p_trade_playerid,  // id do player que est� negociando
	p_trade_ready,     // Verificar se est� pronto
	p_trade_money,
	p_trade_ouros,
	p_trade_cash,
}

new playerTrade[MAX_PLAYERS][p_trade_e];

