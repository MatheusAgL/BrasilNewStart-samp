CMD:minhaslicencas(playerid, params[])
{
	new text1[20];
	new text2[20];
	new text4[20];
	new text5[20];
	new string[128];
	if(IsPlayerHaveItem(playerid, ITEM_TYPE_MOTORISTA)) { text1 = "Passou"; } else { text1 = "Negativo"; }
	if(IsPlayerHaveItem(playerid, ITEM_TYPE_PILOTO)) { text4 = "Passou"; } else { text4 = "Negativo"; }
	if(IsPlayerHaveItem(playerid, ITEM_TYPE_MARUJO)) { text2 = "Passou"; } else { text2 = "Negativo"; }
	if(PlayerInfo[playerid][pGunLic]) { text5 = "Passou"; } else { text5 = "Negativo"; }
	SendClientMessage(playerid, -1, "|__________________ Licencas __________________|");
	format(string, sizeof(string), "** Motorista: %s.", text1);
	SendClientMessage(playerid, COLOR_GREY, string);
	format(string, sizeof(string), "** Piloto: %s.", text4);
	SendClientMessage(playerid, COLOR_GREY, string);
	format(string, sizeof(string), "** Marujo: %s.", text2);
	SendClientMessage(playerid, COLOR_GREY, string);
	format(string, sizeof(string), "** Pescador: Passou.");
	SendClientMessage(playerid, COLOR_GREY, string);
	format(string, sizeof(string), "** Armas: %s.", text5);
	SendClientMessage(playerid, COLOR_GREY, string);
	return true;
}

CMD:mostrarlicencas(playerid, params[])
{
	new idplayer;
	if(sscanf(params, "u", idplayer))
	{
		SendClientMessage(playerid, -1, "Use: /mostrarlicencas [id]");
		return true;
	}
	if(IsPlayerConnected(idplayer))
	{
		if(idplayer != INVALID_PLAYER_ID)
		{
			if(Admin_GetNivel(idplayer) && Staff_GetWorking(idplayer))
			{
				SendClientMessage(playerid, -1, "Você não pode mostrar licenças para admins em modo trabalho !");
				return true;
			}

			if (ProxDetectorS(8.0, playerid, idplayer))
			{
				if(idplayer == playerid) { SendClientMessage(playerid, -1, "Para ver suas licencas Use: /minhaslicencas!"); return true; }
				new text1[20];
				new text2[20];
				new text4[20];
				new text5[20];
				if(IsPlayerHaveItem(playerid, ITEM_TYPE_MOTORISTA)) { text1 = "Passou"; } else { text1 = "Negativo"; }
				if(IsPlayerHaveItem(playerid, ITEM_TYPE_PILOTO)) { text4 = "Passou"; } else { text4 = "Negativo"; }

				new string[128];
				if(IsPlayerHaveItem(playerid, ITEM_TYPE_MARUJO)) { text2 = "Passou"; } else { text2 = "Negativo"; }
				if(PlayerInfo[playerid][pGunLic]) { text5 = "Passou"; } else { text5 = "Negativo"; }
				format(string, sizeof(string), "|__________ Licencas de %s __________|", PlayerName[playerid]);
				SendClientMessage(idplayer, -1, string);
				format(string, sizeof(string), "** Motorista: %s.", text1);
				SendClientMessage(idplayer, COLOR_GREY, string);
				format(string, sizeof(string), "** Piloto: %s.", text4);
				SendClientMessage(idplayer, COLOR_GREY, string);
				format(string, sizeof(string), "** Marujo: %s.", text2);
				SendClientMessage(idplayer, COLOR_GREY, string);
				format(string, sizeof(string), "** Pescador: Passou.");
				SendClientMessage(idplayer, COLOR_GREY, string);
				format(string, sizeof(string), "** Armas: %s.", text5);
				SendClientMessage(idplayer, COLOR_GREY, string);
				format(string, sizeof(string), "* %s mostrou suas licencas para você.", PlayerName[playerid]);
				SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);
				format(string, sizeof(string), "* Você mostrou suas licencas para %s.", PlayerName[idplayer]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			}
			else
			{
				SendClientMessage(playerid, -1, "O Jogador esta longe de Você !");
				return true;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "O Jogador está offline !");
		return true;
	}
	return true;
}
alias:mostrarlicencas("mli")