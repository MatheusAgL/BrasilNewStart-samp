CMD:divorcio(playerid, params[])
{
	new string[128],
		divorcio_string[MAX_PLAYER_NAME],
		divorciado_string[MAX_PLAYER_NAME];

	new idplayer;
	if(sscanf(params, "u", idplayer)) {
		return SendClientMessage(playerid, -1, "Use: /divorciar [ID]");
	}

	if(!PlayerToPoint(10.0, playerid, -1077.9645,713.4493,630.0579)) {
		return SendClientMessage(playerid, -1, "Voc� n�o est� em uma igreja.");
	}

	if(PlayerInfo[playerid][pMarried] == 0) {
		return SendClientMessage(playerid, -1, "Voc� n�o est� casado.");
	}

	if(IsPlayerConnected(idplayer)) {

		if(idplayer != INVALID_PLAYER_ID) {

			if (ProxDetectorS(8.0, playerid, idplayer)) {

				if(idplayer == playerid) {
					return SendClientMessage(playerid, -1, "Voc� n�o pode se divorciar de si mesmo.");
				}

				format(string, sizeof(string), "%s", PlayerName[idplayer]);
				strmid(divorciado_string, string, 0, strlen(string), 255);

				format(string, sizeof(string), "%s", PlayerInfo[playerid][pMarriedTo]);
				strmid(divorcio_string, string, 0, strlen(string), 255);

				if (strcmp(divorcio_string, divorciado_string, true ) == 0) {

					format(string, sizeof(string), "Voc� enviou os papeis do div�rcio para ( %s ).", PlayerName[idplayer]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					format(string, sizeof(string), "( %s ) pediu sua assinatura para o div�rcio | Use: /aceitar divorcio.", PlayerName[playerid]);
					SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);
					DivorceOffer[idplayer] = playerid;
					return true;

				} else {
					return SendClientMessage(playerid, -1, "Voc� n�o est� casado com essa pessoa.");
				}
			} else {
				return SendClientMessage(playerid, -1, "Esse jogador est� longe de voc�.");
			}
		}
	} else {
		return SendClientMessage(playerid, -1, "Esse jogador n�o est� conectado.");
	}
	return true;
}

CMD:casar(playerid, params[])
{
	if(!PlayerToPoint(10.0, playerid, -1077.9645,713.4493,630.0579))
		return SendClientMessage(playerid, -1, "Voc� n�o est� na igreja de Los Santos !");

	if(Player_GetMoney(playerid) < 1000)
		return SendClientMessage(playerid, -1, "O casamento tem o custo de 1000$.");

	if(PlayerInfo[playerid][pMarried] > 0)
		return SendClientMessage(playerid, -1, "Voc� j� � casado.");

	new idplayer;
	if(sscanf(params, "u", idplayer))
		return SendClientMessage(playerid, -1, "Use: /casar [id]");

	if(IsPlayerConnected(idplayer))
	{
		if(idplayer != INVALID_PLAYER_ID)
		{
			if(PlayerInfo[idplayer][pMarried] > 0)
			{
				SendClientMessage(playerid, -1, "Este jogador(a) ja � casado(a) !");
				return true;
			}
			if (ProxDetectorS(8.0, playerid, idplayer))
			{
				new string[128];
				if(idplayer == playerid) { SendClientMessage(playerid, -1, "Voc� n�o pode propor a si mesmo!"); return true; }

				format(string, sizeof(string), "* Voc� prop�s casamento a %s.", PlayerName[idplayer]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				format(string, sizeof(string), "* %s Voc� foi pedida em casamento (Digite /aceitar casamento) para aceitar.", PlayerName[playerid]);
				SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);
				ProposeOffer[idplayer] = playerid;
			}
			else
			{
				SendClientMessage(playerid, -1, "O Jogador n�o est� perto de voc� !");
				return true;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "O jogador esta offline !");
		return true;
	}
	return true;
}

CMD:padrinho(playerid, params[])
{
	if(!PlayerToPoint(10.0, playerid, -1077.9645,713.4493,630.0579))
	{
		SendClientMessage(playerid, -1, "Voc� n�o est� na igreja de Los Santos !");
		return true;
	}
	new idplayer;
	if(sscanf(params, "u", idplayer))
	{
		SendClientMessage(playerid, -1, "Use: /padrinho [id]");
		return true;
	}
	if (IsPlayerConnected(idplayer))
	{
		if(idplayer != INVALID_PLAYER_ID)
		{
			if (ProxDetectorS(8.0, playerid, idplayer))
			{
				new string[128];
				if(idplayer == playerid) { SendClientMessage(playerid, -1, "Voc� n�o pode ser marido e padrinho do casamento!"); return true; }
				format(string, sizeof(string), "* Voc� chamou %s para ser seu padrinho de casamento.", PlayerName[idplayer]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				format(string, sizeof(string), "* %s Voc� foi chamado para ser Padrinho do Casamento (Digite /aceitar padrinho) para aceitar.", PlayerName[playerid]);
				SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);
				MarryWitnessOffer[idplayer] = playerid;
			}
			else
			{
				SendClientMessage(playerid, -1, "O Jogador n�o est� perto de voc� !");
				return true;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "O Jogador esta offline !");
		return true;
	}
	return true;
}