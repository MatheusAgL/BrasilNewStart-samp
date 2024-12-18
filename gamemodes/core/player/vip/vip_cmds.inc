CMD:s(playerid, const params[])
{
	if (PlayerInfo[playerid][pVIP] < 1) 
		return SendClientMessage(playerid, -1, "Voc� n�o � um jogador S�cio.");

	if (PlayerInfo[playerid][pConnectTime] < 5)
		return SendClientMessage(playerid, -1, "� necess�rio 5 horas jogadas para usar o chat s�cio.");

	if (isnull(params)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /s (texto no chat s�cio)");

	new string[128];
	new stringdiscord[128];
	new stringlog[128];
	new vip_nivel = Player_GetVIP(playerid);

	if (chatsocio == 0)
		return SendClientMessage(playerid, -1, "O Chat S�cio est� desativado por um Administrador.");

	if (!PlayerInfo[playerid][pChatVip]) 
		return SendClientMessage(playerid, -1, "Seu chat-s�cio est� desligado, use /menu.");

	if (gettime() < GetPVarInt(playerid, #varFlood_chat)) 
		return SendClientMessage(playerid, COLOR_GRAD, #Voc� n�o pode usar este comando com tanta frequencia);

	SetPVarInt(playerid, #varFlood_chat, gettime() + 5);

	format(string, sizeof(string), "[%s{33FF00}] %s: %s", GetDonateRank(playerid), PlayerName[playerid], params);

	format(stringdiscord, sizeof(stringdiscord), "[%s] %s: %s", VIP_GetName(vip_nivel), PlayerName[playerid], params);

	format(stringlog, sizeof(stringlog), "[%s] %s: %s", GetDonateRank(playerid), PlayerName[playerid], params);
	server_log("chatsocio", stringlog);

	#if defined _CENSORED_protection
		censored_word_detected(string);
	#endif

	SendVIPMessage(0x33FF00FF, string);

	Discord_SendMessage(stringdiscord, Channel_SocioLogs);

	return true;
}
alias:v("s")

CMD:kitsocio(playerid, params[])
{
	if(GetPVarInt(playerid, "ArmasRestringidas") > gettime())
		return SendMsgF(playerid, -1, "Suas armas est�o restringidas. Aguarde %d segundos.", GetPVarInt(playerid, "ArmasRestringidas")-gettime());

    if (PlayerInEvento(playerid))
		return SendClientMessage(playerid, COLOR_LIGHTRED, "Voc� est� em um evento, n�o pode usar esse comando.");

  	if (IsPlayerInCombat(playerid)) return SendClientMessage(playerid, -1, "Voc� est� em modo combate, aguarde 1 minuto para usar o comando novamente.");

	new valid = 1;
	if (isnull(params))
		valid = 0;

	new string[128];

   	if (Player_GetVIP(playerid) < 2 && !Admin_GetNivel(playerid)) 
		return SendClientMessage(playerid, -1, "Voc� precisa ser S�cio Premium, Supreme ou Extreme para usar esse comando.");

   	if (IsPlayerInAnyVehicle(playerid)) 
		return SendClientMessage(playerid, -1, "Voc� n�o pode usar o comando dentro de um ve�culo.");

	if(GetPVarInt(playerid, "Abordado")) {
		return SendClientMessage(playerid, -1, "Voc� n�o pode pegar o kit s�cio enquanto estiver sendo abordado.");
	}

   	if (!strcmp(params, "1", true))
	{
		weaponsDonateRank(playerid, 1);

		format(string, sizeof(string), "* %s pegou o seu KIT-S�CIO I.", PlayerName[playerid]);
		SendClientMessageInRange(50.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
	}
	else if (!strcmp(params, "2", true))
	{
		weaponsDonateRank(playerid, 2);

		format(string, sizeof(string), "* %s pegou o seu KIT-S�CIO II.", PlayerName[playerid]);
		SendClientMessageInRange(50.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
	}
	else if (!strcmp(params, "3", true))
	{
		weaponsDonateRank(playerid, 3);

		format(string, sizeof(string), "* %s pegou o seu KIT-S�CIO III.", PlayerName[playerid]);
		SendClientMessageInRange(50.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
	}
	else if (!strcmp(params, "4", true))
	{
		weaponsDonateRank(playerid, 4);

		format(string, sizeof(string), "* %s pegou o seu KIT-S�CIO IV.", PlayerName[playerid]);
		SendClientMessageInRange(50.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
	}
	else if (!strcmp(params, "supreme", true))
	{
		if (Player_GetVIP(playerid) < 7) return SendClientMessage(playerid, -1, "Voc� precisa ser S�cio Supreme ou extreme para usar esse kit.");

		weaponsDonateRank(playerid, 5);

		format(string, sizeof(string), "* %s pegou o seu KIT-S�cio Supreme.", PlayerName[playerid]);
		SendClientMessageInRange(50.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);
	}
	else {
		valid = 0;
	}

	if(valid == 0) {
		SendClientMessage(playerid, -1, "/kitsocio 1       {8B8A8A}(Soco ingl�s, Faca, Eagle, Combat-Shotgun, MP5, M4, Sniper, Spray)");
		SendClientMessage(playerid, -1, "/kitsocio 2       {8B8A8A}(Soco ingl�s, Katana, Tear G�s, Eagle, Shotgun, MP5, AK-47, Sniper, Extintor)");
	  	SendClientMessage(playerid, -1, "/kitsocio 3       {8B8A8A}(Soco ingl�s, Faca, Tear G�s, Eagle, Shotgun, MP5, M4, Sniper, Extintor)");
	  	SendClientMessage(playerid, -1, "/kitsocio 4       {8B8A8A}(Armas simples, como Faca, Eagle, Shotgun, M4, Sniper)");
		SendClientMessage(playerid, -1, "/kitsocio supreme {8B8A8A}(Soco ingl�s, Faca, Eagle, Shotgun, MP5, M4, Sniper, Spray)");
	}
	else {
		if(GetPVarInt(playerid, "AntiSpawnKill")) {
			SetPVarInt(playerid, "AntiSpawnKill", 0);
		}
	}
	return true;
}