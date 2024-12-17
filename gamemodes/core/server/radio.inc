#include <YSI_Coding\y_hooks>

#define 		MAX_FREQUENCY_RADIO 	2

static 
		bool: player_listening_radio[MAX_FREQUENCY_RADIO][MAX_PLAYERS],
		listeners_radio[MAX_FREQUENCY_RADIO];

stock PlayerListeningRadio(playerid) {
	for (new r; r < sizeof(player_listening_radio); r++) {
		return player_listening_radio[r][playerid];
	}
	return 0;
}

stock GetPlayerListenerRadio(playerid) {
	for (new r; r < sizeof(player_listening_radio); r++) {
		if (player_listening_radio[r][playerid])
			return r;
	}
	return 0;
}

stock SetPlayerListener(playerid, frequency_radio, bool:stats) {

	if (frequency_radio > sizeof(player_listening_radio)) return 0;

	player_listening_radio[frequency_radio][playerid] = stats;

	if (stats)
		listeners_radio[frequency_radio]++;
	else
		listeners_radio[frequency_radio]--;

	return 1;
}

stock StopPlayerAudioStream(playerid)
{
	for (new r; r < MAX_FREQUENCY_RADIO; r++) {
		if (!player_listening_radio[r][playerid]) return 0;
	}
	return StopAudioStreamForPlayer(playerid);
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) 
{
	if (dialogid == 4321)
	{
	    if (!response)
			return 1;

		switch (listitem)
		{
			case 0:
			{
				SetPlayerListener(playerid, 0, true);

				PlayAudioStreamForPlayer(playerid, SERVER_LINK_RADIO);

				SendMsgF(playerid, COLOR_WHITE, "Rádio ligada - Frequência: '102 - Rádio - "SERVER_NAME"' | %d ouvintes in-game.", listeners_radio[0]);
			}
			case 1: Radio_DialogAskMusic(playerid);
			case 2: {
				#if _inc_speakers_system
					callcmd::locutores(playerid);
				#else
					return SendClientMessage(playerid, COLOR_WHITE, "O sistema da 'Equipe da Rádio' está desativado.");
				#endif
			}
			case 3: {
				#if _inc_speakers_system
					callcmd::infolocutores(playerid);
				#else
					return SendClientMessage(playerid, COLOR_WHITE, "O sistema da 'Equipe da Rádio' está desativado.");
				#endif
			}
			case 4: callcmd::pedidos(playerid);
			case 5: callcmd::musicas(playerid);
			case 6:
			{
				SetPlayerListener(playerid, GetPlayerListenerRadio(playerid), false);

				StopAudioStreamForPlayer(playerid);

				SendClientMessage(playerid, COLOR_WHITE, "Você desligou a rádio.");
			}
		}
	    return 1;
	}

	else if (dialogid == 5409)
    {
        if (!response) return SendClientMessage(playerid, -1, "Você fechou o menu de frequências de rádio.");

        switch (listitem)
		{
            case 0:
			{
			    SetPlayerListener(playerid, 0, true);

				PlayAudioStreamForPlayer(playerid, SERVER_LINK_RADIO);

				SendMsgF(playerid, COLOR_WHITE, "Rádio ligada - Frequência: '102 - Rádio - "SERVER_NAME"' | %d ouvintes in-game.", listeners_radio[0]);
			}
			default:
			{
				SetPlayerListener(playerid, GetPlayerListenerRadio(playerid), false);

				StopAudioStreamForPlayer(playerid);

				SendClientMessage(playerid, COLOR_WHITE, "Você desligou a rádio.");
  			}
        }
        SendClientMessage(playerid, COLOR_WARNING, "Observação: Caso você não escute o som, aumente o volume nas configurações de seu GTA:SA.");
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason) { 
	if (PlayerListeningRadio(playerid))
		SetPlayerListener(playerid, GetPlayerListenerRadio(playerid), false);

	return 1;
}

CMD:musicas(playerid)
{
    new string[128];

    MEGAString [0] = EOS;

    strcat(MEGAString, "Frequência\tNome\tOuvintes\n");

    format(string, sizeof string, "{7D8084}101,5:\t{DBDCE0}Rádio "SERVER_NAME"\t{00FF00}%d\n", listeners_radio[0]);
	strcat(MEGAString, string);

	strcat(MEGAString, "{7D8084}000,00:\t{FF0000}Desligar rádio\n");

	ShowPlayerDialog(playerid, 5409, DIALOG_STYLE_TABLIST_HEADERS, "Frequências de rádios", MEGAString, "Ligar", "Cancelar");
	
    return 1;
}