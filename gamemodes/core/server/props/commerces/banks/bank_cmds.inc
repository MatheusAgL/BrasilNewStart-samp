
CMD:sacar(playerid, params[])
{
	if (gettime() < GetPVarInt(playerid, #varFlood_sacar)) return SendClientMessage(playerid, -1, #Você não pode usar este comando com tanta frequencia);

	if (!IsPlayerInRangeOfPoint(playerid, 3.0, 1456.5311, -1128.0327, 23.9580)) return SendClientMessage(playerid, -1, "Você não está no banco.");

	new string[128], dinheiroSacar;

	if (sscanf(params, "d", dinheiroSacar)) return SendClientMessage(playerid, -1, "Modo de uso: /sacar (quantidade)");

	switch (GetPlayerVirtualWorld(playerid))
	{
		case 10082: ApplyDynamicActorAnimation(actorBanco[2], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		case 10083: ApplyDynamicActorAnimation(actorBanco[4], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		default: ApplyDynamicActorAnimation(actorBanco[0], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
	}

	if ((Player_GetMoney(playerid) + dinheiroSacar) > max_money_limit)
	{
		SetPVarInt(playerid, #varFlood_sacar, gettime() + 10);

		format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, esse valor ultrapassa o limite de dinheiro.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}
	if (dinheiroSacar < 1 || dinheiroSacar > 500000000)
	{
		SetPVarInt(playerid, #varFlood_sacar, gettime() + 10);

		format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, você pode sacar apenas entre $1 e $500.000.000.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}
	if (dinheiroSacar > PlayerInfo[playerid][pConta])
	{
		SetPVarInt(playerid, #varFlood_sacar, gettime() + 10);

		format(string, sizeof(string), "Gabriel Azevedo(501) diz: Olá %s, você não tem $%s na conta.", PlayerName[playerid], getFormatText(dinheiroSacar));
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}

	new taxsaque = dinheiroSacar / 1000;

	PlayerInfo[playerid][pConta] -= (dinheiroSacar + taxsaque);
	Player_AddMoney(playerid, dinheiroSacar);
	SetPVarInt(playerid, #varFlood_sacar, gettime() + 5);

	if (GetPlayerVirtualWorld(playerid) != 0)
		DepositPropertie(playerid, taxsaque);
	else
		DepositPropertieID(81, taxsaque);

	format(string, sizeof(string), "%s sacou $%s no banco, seu saldo: $%s", PlayerName[playerid], getFormatText(dinheiroSacar), getFormatText(PlayerInfo[playerid][pConta]));
	server_log("banco", string);

	format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, você sacou $%s na conta, saldo atual: $%s.", PlayerName[playerid], getFormatText(dinheiroSacar), getFormatText(PlayerInfo[playerid][pConta]));
	SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

	format(string, sizeof(string), "...você pagou 0.1 por cento da taxa de saque, valor descontado: $%s.", getFormatText(taxsaque));
	return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
}

CMD:depositar(playerid, params[])
{
	if (gettime() < GetPVarInt(playerid, #varFlood_depositar)) return SendClientMessage(playerid, -1, #Você não pode usar este comando com tanta frequencia);

	if (!IsPlayerInRangeOfPoint(playerid, 3.0, 1456.5311, -1128.0327, 23.9580)) return SendClientMessage(playerid, -1, "Você não está no banco.");

	new dinheiroDeposito;
	if (sscanf(params, "d", dinheiroDeposito)) return SendClientMessage(playerid, -1, "Modo de uso: /depositar (quantidade)");

	switch (GetPlayerVirtualWorld(playerid)) {
		case 10082: ApplyDynamicActorAnimation(actorBanco[2], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		case 10083: ApplyDynamicActorAnimation(actorBanco[4], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		default: ApplyDynamicActorAnimation(actorBanco[0], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
	}

	new string[128];

	if (Player_GetMoney(playerid) < dinheiroDeposito || dinheiroDeposito < 1)
	{
		SetPVarInt(playerid, #varFlood_depositar, gettime() + 10);

		format(string, sizeof(string), "Gabriel Azevedo(501) diz: Olá %s, você não tem esse valor em mãos.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}

	if (PlayerInfo[playerid][pConta] > 1500000000) {

		SetPVarInt(playerid, #varFlood_depositar, gettime() + 10);

		format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, você tem mais de $1.500.000.000 na conta, /comprarouros.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}
	if (dinheiroDeposito < 1 || dinheiroDeposito > 500000000) {

		SetPVarInt(playerid, #varFlood_depositar, gettime() + 10);

		format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, você pode apenas depositar entre $1 e $500.000.000.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}

	new taxdeposito = dinheiroDeposito / 1000;

	CheckConquista(playerid, Conquista_Deposito);

	Player_RemoveMoney(playerid, dinheiroDeposito);
	PlayerInfo[playerid][pConta] += (dinheiroDeposito - taxdeposito);

	if (GetPlayerVirtualWorld(playerid) != 0)
		DepositPropertie(playerid, taxdeposito);
	else
		DepositPropertieID(81, taxdeposito);

	SetPVarInt(playerid, #varFlood_depositar, gettime() + 5);

	format(string, sizeof(string), "%s depositou $%s no banco, seu saldo: $%s", PlayerName[playerid], getFormatText(dinheiroDeposito), getFormatText(PlayerInfo[playerid][pConta]));
	server_log("banco", string);

	format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, você depositou $%s na conta, seu saldo: $%s.", PlayerName[playerid], getFormatText(dinheiroDeposito), getFormatText(PlayerInfo[playerid][pConta]));
	SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

	format(string, sizeof(string), "...você pagou 0.1 por cento da taxa de depósito, valor descontado: $%s.", getFormatText(taxdeposito));
	return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
}

CMD:transferir(playerid, params[])
{
	if (gettime() < GetPVarInt(playerid, #varFlood_transferir)) return SendClientMessage(playerid, -1, #Você não pode usar este comando com tanta frequencia);

	if (!IsPlayerInRangeOfPoint(playerid, 3.0, 1456.5311, -1128.0327, 23.9580)) return SendClientMessage(playerid, -1, "Você não está no banco.");

	new dinheiroTransferencia, string[128];

	new idplayer;
	if (sscanf(params, "ud", idplayer, dinheiroTransferencia)) return SendClientMessage(playerid, -1, "Modo de uso: /transferir (id/nick do jogador) (quantidade)");

	if (!Player_Logado(idplayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (idplayer == playerid) return SendClientMessage(playerid, -1, "Você não pode fazer transferencia para si mesmo.");

	switch (GetPlayerVirtualWorld(playerid)) {
		case 10082: ApplyDynamicActorAnimation(actorBanco[2], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		case 10083: ApplyDynamicActorAnimation(actorBanco[4], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		default: ApplyDynamicActorAnimation(actorBanco[0], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
	}

	/*if (PlayerInfo[playerid][pLevel] < 3) {

		SetPVarInt(playerid, #varFlood_transferir, gettime() + 10);

		format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, você não tem nível 3+ para fazer transferencias.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}*/

	if (dinheiroTransferencia < 1 || dinheiroTransferencia > 500000000) {

		SetPVarInt(playerid, #varFlood_transferir, gettime() + 10);

		format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, você pode apenas transferir entre $1 e $500.000.000.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}

	if (idplayer != INVALID_PLAYER_ID) {

		if (dinheiroTransferencia < 1 || dinheiroTransferencia > PlayerInfo[playerid][pConta]) {

			SetPVarInt(playerid, #varFlood_transferir, gettime() + 10);

			format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, você não tem esse valor na sua conta.", PlayerName[playerid]);
			return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		}

		if (PlayerInfo[idplayer][pConta] > 1500000000)
		{
			SetPVarInt(playerid, #varFlood_transferir, gettime() + 10);

			format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, este jogador possui muito dinheiro na conta.", PlayerName[playerid]);
			return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		}

		new taxtransferencia = dinheiroTransferencia / 1000;

		PlayerInfo[playerid][pConta] -= (dinheiroTransferencia + taxtransferencia);
		PlayerInfo[idplayer][pConta] += dinheiroTransferencia;

		SetPVarInt(playerid, #varFlood_transferir, gettime() + 5);

		format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, você transferiu $%s para %s...", PlayerName[playerid], getFormatText(dinheiroTransferencia), PlayerName[idplayer]);
		SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

		format(string, sizeof(string), "...você pagou 0.1 por cento da taxa de transferência, valor descontado: $%s.", getFormatText(taxtransferencia));
		SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

		SendClientMessage(idplayer, 0xDBED15FF, "» Informações da transferência");

		format(string, sizeof(string), "%s transferiu {00AA00}$%s {FFFFFF}para você", PlayerName[playerid], getFormatText(dinheiroTransferencia));
		SendClientMessage(idplayer, -1, string);

		// Som do PIX
		PlayerPlaySound(idplayer, 20801, 0.0, 0.0, 0.0);

		format(string, sizeof(string), "Novo saldo: {00AA00}$%s", getFormatText(PlayerInfo[idplayer][pConta]));
		SendClientMessage(idplayer, -1, string);

		SendClientMessage(idplayer, 0xDBED15FF, "_______________________________________");

		format(string, sizeof(string), "(Conta bancária): %s(%d) transferiu $%s para %s(%d).", PlayerName[playerid], playerid, getFormatText(dinheiroTransferencia), PlayerName[idplayer], idplayer);
		Staff_ChatToAll(COLOR_YELLOW, string, ESTAGIARIO); 
		
		server_log("transferir", string);

		format(string, sizeof string, "%s [Grana: %d, Banco: %d] > %s [Grana: %d, Banco: %d]", PlayerName[playerid], Player_GetMoney(playerid), PlayerInfo[playerid][pConta], PlayerName[idplayer], Player_GetMoney(idplayer), PlayerInfo[idplayer][pConta]);
		server_log("saldo_banco", string);

		if (GetPlayerVirtualWorld(playerid) != 0)
			DepositPropertie(playerid, taxtransferencia);
		else
			DepositPropertieID(81, taxtransferencia);

		PlayerPlaySound(idplayer, 1052, 0.0, 0.0, 0.0); PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	}
	return true;
}

CMD:filiar(playerid, params[])
{
	if (gettime() < GetPVarInt(playerid, #varFlood_filiar)) return SendClientMessage(playerid, -1, #Você não pode usar este comando com tanta frequencia);

	if (!IsPlayerInRangeOfPoint(playerid, 3.0, 1456.5311, -1128.0327, 23.9580)) return SendClientMessage(playerid, -1, "Você não está no banco.");

	new string[128];

	new idplayer;
	if (sscanf(params, "u", idplayer)) {

		SendClientMessage(playerid, -1, "Modo de uso: /filiar (seu id/nick)");
		SendClientMessage(playerid, 0x00AA00FF, "Você pagará $100.000 para afiliar-se");
		return true;
	}

	if (idplayer != playerid) return SendClientMessage(playerid, -1, "Você precisa colocar o seu id ou nick para filiar-se a esse banco.");

	switch (GetPlayerVirtualWorld(playerid)) {
		case 10082: ApplyDynamicActorAnimation(actorBanco[2], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		case 10083: ApplyDynamicActorAnimation(actorBanco[4], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		default: ApplyDynamicActorAnimation(actorBanco[0], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
	}

	if (PlayerInfo[playerid][pConta] < 10000000) {

		SetPVarInt(playerid, #varFlood_filiar, gettime() + 5);

		format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, você precisa ter $10.000.000 no banco.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}

	PlayerInfo[playerid][pConta] -= 100000;
	PlayerInfo[playerid][pBancoFiliado] = currentInt[playerid];
	DepositPropertie(playerid, 100000);

	SetPVarInt(playerid, #varFlood_filiar, gettime() + 30);

	format(string, sizeof(string), "Gabriel Azevedo(501) diz: %s, você filiou-se ao banco ID: %d...", PlayerName[playerid], currentInt[playerid]);
	SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

	SendClientMessageInRange(35.0, playerid, "...O banco receberá uma taxa cobrada a cada compra pelo cartão.", COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

	format(string, sizeof(string), "(Conta bancária): %s filiou-se ao banco %d.", PlayerName[playerid], playerid, currentInt[playerid]);
	Staff_ChatToAll(COLOR_YELLOW, string, SUB_DONO); server_log("filiados", string);

	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

	return true;
}

CMD:comprarouros(playerid, result[])
{
	if(!PlayerToPoint(3.0, playerid, 1460.4261, -1124.5687, 23.9580)) return SendClientMessage(playerid, -1, "Você não esta no banco.");

	if(gettime() < GetPVarInt(playerid, #varFlood_bancoouros)) return SendClientMessage(playerid, -1, #Você não pode usar este comando com tanta frequencia);

	new ourosComprados;

	if (sscanf(result, "d", ourosComprados)) return SendClientMessage(playerid, -1, "Modo de uso: /comprarouros (quantidade)");

	new valorFinal = ourosComprados * 100000;

	switch (GetPlayerVirtualWorld(playerid))
	{
		case 10082: ApplyDynamicActorAnimation(actorBanco[5], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		case 10083: ApplyDynamicActorAnimation(actorBanco[3], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		default: ApplyDynamicActorAnimation(actorBanco[1], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
	}

	new string[128];

	if (ourosComprados < 1 || ourosComprados > 10000)
	{
		SetPVarInt(playerid, #varFlood_bancoouros, gettime() + 10);

		format(string, sizeof(string), "Bruno Santos(502) diz: Olá %s, você precisa comprar entre 1 a 10.000 ouros.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}

	if (PlayerInfo[playerid][pConta] >= valorFinal)
	{
		new taxcomprarouros = valorFinal / 1000;

		SetPVarInt(playerid, #varFlood_bancoouros, gettime() + 5);

		format(string, sizeof(string), "Bruno Santos(502) diz: %s, você comprou %d ouros por $%s.", PlayerName[playerid], ourosComprados, getFormatText(valorFinal));
		SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

		format(string, sizeof(string), "...você pagou 0.1 por cento da taxa de comprar ouros, valor descontado: $%s.", getFormatText(taxcomprarouros));
		SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

		PlayerInfo[playerid][pConta] -= (valorFinal + taxcomprarouros);
		PlayerInfo[playerid][pOuros] += ourosComprados;

		if (GetPlayerVirtualWorld(playerid) != 0)
			DepositPropertie(playerid, taxcomprarouros);
		else
			DepositPropertieID(81, taxcomprarouros);

		format(string, sizeof(string), "(Ouros): %s comprou %d ouros pagou %s.", PlayerName[playerid], ourosComprados, getFormatText(valorFinal));
		server_log("ouros", string);
	}
	else
	{
		SetPVarInt(playerid, #varFlood_bancoouros, gettime() + 10);

		format(string, sizeof(string), "Bruno Santos(502) diz: %s, você não tem $%s na conta.", PlayerName[playerid], getFormatText(valorFinal));
		SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}
	return true;
}
alias:comprarouros("couros")

CMD:venderouros(playerid, result[])
{
	if (gettime() < GetPVarInt(playerid, #varFlood_bancoouros)) return SendClientMessage(playerid, -1, #Você não pode usar este comando com tanta frequencia);

	if (!PlayerToPoint(3.0, playerid, 1460.4261, -1124.5687, 23.9580)) return SendClientMessage(playerid, -1, "Você não esta no banco.");

	new ourosVender;

	if (sscanf(result, "d", ourosVender)) return SendClientMessage(playerid, -1, "Modo de uso: /venderouros (quantidade)");

	switch (GetPlayerVirtualWorld(playerid))
	{
		case 10082: ApplyDynamicActorAnimation(actorBanco[5], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		case 10083: ApplyDynamicActorAnimation(actorBanco[3], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		default: ApplyDynamicActorAnimation(actorBanco[1], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
	}

	new string[128];

	if (ourosVender < 1 || ourosVender > 10000)
	{
		SetPVarInt(playerid, #varFlood_bancoouros, gettime() + 10);

		format(string, sizeof(string), "Bruno Santos(502) diz: Olá %s, você pode vender entre 1 a 10.000 ouros.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}

	new valorFinal = ourosVender * 100000;

	if (PlayerInfo[playerid][pOuros] >= ourosVender)
	{
		if ((PlayerInfo[playerid][pConta] + valorFinal) > max_money_limit)
		{
			SetPVarInt(playerid, #varFlood_bancoouros, gettime() + 10);

			format(string, sizeof(string), "Bruno Santos(502) diz: %s, este valor ultrapassa o limite de dinheiro.", PlayerName[playerid]);
			return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		}

		new taxvenderouros = valorFinal / 1000;

		SetPVarInt(playerid, #varFlood_bancoouros, gettime() + 5);

		format(string, sizeof(string), "Bruno Santos(502) diz: %s, você vendeu %d ouros por $%s.", PlayerName[playerid], ourosVender, getFormatText(valorFinal));
		SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

		format(string, sizeof(string), "...você pagou 0.1 por cento da taxa de vender ouros, valor descontado: $%s.", getFormatText(taxvenderouros));
		SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

		PlayerInfo[playerid][pConta] += (valorFinal - taxvenderouros);
		PlayerInfo[playerid][pOuros] -= ourosVender;

		if (GetPlayerVirtualWorld(playerid) != 0)
			DepositPropertie(playerid, taxvenderouros);
		else
			DepositPropertieID(81, taxvenderouros);

		format(string, sizeof(string), "(Ouros) %s vendeu %d ouros.", PlayerName[playerid], ourosVender);
		server_log("ouros", string);
	}
	else
	{
		SetPVarInt(playerid, #varFlood_bancoouros, gettime() + 10);

		format(string, sizeof(string), "Bruno Santos(502) diz: %s, você não tem %d ouros, use /rg.", PlayerName[playerid], ourosVender);
		SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}
	return true;
}
alias:venderouros("vouros")

CMD:transferirouros(playerid, params[])
{
	if (gettime() < GetPVarInt(playerid, #varFlood_bancoouros)) return SendClientMessage(playerid, -1, #Você não pode usar este comando com tanta frequencia);

	if (!PlayerToPoint(3.0, playerid, 1460.4261, -1124.5687, 23.9580)) return SendClientMessage(playerid, -1, "Você não esta no banco.");

	new ourosTransferencia, idplayer;
	if (sscanf(params, "ud", idplayer, ourosTransferencia)) return SendClientMessage(playerid, -1, "Modo de uso: /transferirouros (id/nick do jogador) (quantidade)");

	if (!Player_Logado(idplayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (idplayer == playerid) return SendClientMessage(playerid, -1, "Você não pode fazer transferencia para si mesmo.");


	switch (GetPlayerVirtualWorld(playerid))
	{
		case 10082: ApplyDynamicActorAnimation(actorBanco[5], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		case 10083: ApplyDynamicActorAnimation(actorBanco[3], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		default: ApplyDynamicActorAnimation(actorBanco[1], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
	}

	new string[128];

	if (ourosTransferencia < 1 || ourosTransferencia > PlayerInfo[playerid][pOuros])
	{
		SetPVarInt(playerid, #varFlood_bancoouros, gettime() + 10);

		format(string, sizeof(string), "Bruno Santos(502) diz: %s, você não tem esse valor em ouros.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}

	if (PlayerInfo[idplayer][pOuros] > 1500000000) {

		SetPVarInt(playerid, #varFlood_bancoouros, gettime() + 10);

		format(string, sizeof(string), "Bruno Santos(502) diz: %s, este jogador possui muitos ouros.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}

	SetPVarInt(playerid, #varFlood_bancoouros, gettime() + 5);

	PlayerInfo[playerid][pOuros] -= ourosTransferencia;
	PlayerInfo[idplayer][pOuros] += ourosTransferencia;

	format(string, sizeof(string), "Bruno Santos(502) diz: %s, você transferiu %s ouros para %s...", PlayerName[playerid], getFormatText(ourosTransferencia), PlayerName[idplayer]);
	SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

	format(string, sizeof(string), "(Ouros): %s transferiu %s ouros para %s.", PlayerName[playerid], getFormatText(ourosTransferencia), PlayerName[idplayer]);
	Staff_ChatToAll(COLOR_YELLOW, string, ESTAGIARIO), server_log("ouros", string);

	PlayerPlaySound(idplayer, 1052, 0.0, 0.0, 0.0); PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

	return true;
}