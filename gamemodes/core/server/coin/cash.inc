stock GetMetodoDonate(metodo)
{
	new InfoMetodoDonate[25];

	switch (metodo)
	{
		case 1: 	InfoMetodoDonate = "{31A0F4}Caixa Econômica";
		case 2: 	InfoMetodoDonate = "{02BD5A}Sicredi";
		case 3: 	InfoMetodoDonate = "{D81504}Santander";
		case 4: 	InfoMetodoDonate = "{1A7805}PagSeguro";
		case 5: 	InfoMetodoDonate = "{1E45D7}PayPal";
		case 6: 	InfoMetodoDonate = "{38A8CE}Mercado Pago";
		case 7: 	InfoMetodoDonate = "{33D87A}PicPay";
		case 9: 	InfoMetodoDonate = "{EF9013}BitCoin";
		case 10: 	InfoMetodoDonate = "{FFF000}Banco do Brasil";
		case 11: 	InfoMetodoDonate = "{A93C3C}Pagamento";
		case 12: 	InfoMetodoDonate = "{33CCFF}Pix";
		case 13:	InfoMetodoDonate = "{00FFFF}PaySafeCard";
		case 14:	InfoMetodoDonate = "{C0C0C0}Revolut";
		case 15:	InfoMetodoDonate = "{B22222}MB Way";
		case 16:	InfoMetodoDonate = "{00FF00}Google Pay";
		case 17:	InfoMetodoDonate = "{DED356}Sorteio";

		case 50:	InfoMetodoDonate = "{3CB371}Mapper";

		default: 	InfoMetodoDonate = "{DED356}Sorteio";
	}
	return InfoMetodoDonate;
}

new Cash_Promo;

stock Cash_GetPromo()
	return Cash_Promo;

stock Cash_SetPromo(value)
	Cash_Promo = value;

CMD:ativarpromocao(playerid, params[])
{
	if (!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Você não está logado.");
		
	if (!Founders_GetList(playerid))
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new percent,
		string[200];

	if (sscanf(params, "d", percent))
		return SendClientMessage(playerid, -1, "Modo de uso: /ativarpromocao (porcentagem)");

	if (percent < 0 || percent > 100)
		return SendClientMessage(playerid, -1, "Você deve digitar uma porcentagem de 0 á 100, onde 0 é para desativar.");

	if (percent == 0) {
		#if defined _inc_discord_connector
			format(string, sizeof(string), ":money_bag: **PROMOÇÃO DE CASH!** -> Finalizada!! Ohhhhnnnnnnn ;( ;[ :money_bag:");
			Discord_SendMessage(string, Channel_BatePapo);
		#endif

		format(string, sizeof(string), "CASH:{FFFFFF} %s, %s {FF0000}desativou{FFFFFF} um desconto nas compras de cash.", Staff_GetPositionName(playerid), PlayerName[playerid], percent);
	} else {
		#if defined _inc_discord_connector
			format(string, sizeof(string), ":money_bag: **PROMOÇÃO DE CASH!** -> BÔNUS DE %d EM COMPRAS DE CASH :money_bag: Acesse: "SERVER_SITE" @everyone @here");
			Discord_SendMessage(string, Channel_BatePapo);
		#endif

		format(string, sizeof(string), "CASH:{FFFFFF} %s, %s {00FF00}ativou{FFFFFF} um desconto de +%d por cento na compra de cash.", Staff_GetPositionName(playerid), PlayerName[playerid], percent);
	}
	SendClientMessageToAll(COLOR_GREEN, string);

	Cash_Promo = percent;

	return 1;
}

stock AtivarCash(const ativador[], const cliente[], quantity, metodo)
{
	new additional = Cash_GetPromo();
	if (additional > 0) {
		additional = floatround(floatmul(floatdiv(additional, 100.0), quantity));
	}

	new value = (quantity + additional);

	new idPlayer = GetPlayerID(cliente);
	if (Player_Logado(idPlayer)) 
	{
		if (Admin_GetNivel(idPlayer))
			additional += floatround(floatmul(floatdiv(30.0, 100.0), quantity));

		value = Player_GetCash(idPlayer);
		value += (quantity + additional);

		Player_SetCash(idPlayer, value);
	} else {
		new query[200];

		mysql_format(MySQL_Handle, query, sizeof query, "UPDATE `player` SET `cash` = `cash` + %d WHERE `nome` = '%e'", value, cliente);
		mysql_tquery(MySQL_Handle, query);
	}

	new string[200];

	if (metodo == 50) {
		format(string, sizeof string, "%s » {FBFAFA}%s %s {FBFAFA}recebeu pagamento de Mapper ({548EEB}%s {FBFAFA}cash).", GetMetodoDonate(metodo), cliente, Player_Logado(idPlayer) ? ("{38D78F}[online]") : ("{ED4550}[offline]"), getFormatText(quantity + additional));
		Staff_ChatToAll(-1, string);
	}
	else if (metodo != 99) {
		format(string, sizeof string, "%s » {FBFAFA}%s %s {FBFAFA}recebeu ativação ({548EEB}%s {FBFAFA}cash).", GetMetodoDonate(metodo), cliente, Player_Logado(idPlayer) ? ("{38D78F}[online]") : ("{ED4550}[offline]"), getFormatText(quantity + additional));
		SendClientMessageToAll(-1, string);

		#if defined _inc_discord_connector
			format(string, sizeof(string), ":gem: **%s** recebeu ativação de **%s** cash. Compre cash pelo painel: "SERVER_SITE"", cliente, getFormatText(quantity + additional));
			Discord_SendMessage(string, Channel_BatePapo);
		#endif
	} else {
		format(string, sizeof string, "SORTEIO DISCORD » {FBFAFA}%s %s {FBFAFA}recebeu ({548EEB}%s {FBFAFA}cash) por ter sido sorteado.", cliente, Player_Logado(idPlayer) ? ("{38D78F}[online]") : ("{ED4550}[offline]"), getFormatText(quantity + additional));
		SendClientMessageToAll(COLOR_DISCORD, string);

		#if defined _inc_discord_connector
			format(string, sizeof(string), ":gem: **%s** recebeu **%s** cash. Através do Sorteio de Cash pelo Discord. #vincule-discord.", cliente, getFormatText(quantity + additional));
			Discord_SendMessage(string, Channel_BatePapo);
		#endif
	}

	format(string, sizeof string, "(Cash): %s ativou $%s cash para %s | método: %d", ativador, getFormatText(quantity + additional), cliente, metodo);
	server_log("cashativacao", string);
}