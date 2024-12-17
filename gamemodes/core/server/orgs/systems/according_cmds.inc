CMD:acordo(playerid, params[])
{
	if (!PlayerIsMercenario(playerid) && !PlayerIsTerror(playerid)) 
        return SendClientMessage(playerid, -1, "Você não é um mercenário ou terrorista.");

	new idPlayer, valorAcordo;
	if (sscanf(params, "ud", idPlayer, valorAcordo)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /acorodo (id do jogador) (valor)");

	if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (!ProxDetectorS(25.0, playerid, idPlayer)) return SendClientMessage(playerid, -1, "Você não está próximo ao jogador.");

	if (valorAcordo < 100 || valorAcordo > 5000) return SendClientMessage(playerid, -1, "O valor do resgate deve estar entre $100 a $5.000");

	new string[128];

	foreach(new i : Player)
	{
		if(GetPVarInt(playerid, "acordoID") == i)
		{
			format(string, sizeof string, "Você ja está ajudando %s, digite (/cancelar ajuda) para cancelar.", PlayerName[i]);
			SendClientMessage(playerid, COLOR_LIGHTRED, string);
			SendMsgF(playerid, COLOR_YELLOW, "Você possui %sg de materiais, você poderá comprar apenas %sg.", PlayerName[i]);
			return true;
		}
	}

	if (GetPVarInt(idPlayer, "acordoID") != 999) return SendClientMessage(playerid, -1, "Alguem já fez um acordo com esse jogador.");

	format(string, sizeof(string), "* Você ofereceu ajuda para %s, por $%d", PlayerName[idPlayer], getFormatText(valorAcordo));
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

	format(string, sizeof(string), "((%s)) %s, %s ofereceu um acordo por $%s (/aceitar acordo)", NomeORG(playerid), GetPlayerCargo(playerid), PlayerName[playerid], getFormatText(valorAcordo));
	SendClientMessage(idPlayer, COLOR_LIGHTBLUE, string);

	MercOffer[idPlayer] = playerid;
	MercMoney[idPlayer] = valorAcordo;

	return true;
}