#include <YSI_Coding\y_hooks>

enum bpsInfoEnum
{
	Tels[20],
 	pTels,
	ArmaLoja[52],
};
new BPSInfo[MAX_PLAYERS][bpsInfoEnum];

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) 
{
	new string[128];

    if (dialogid == 3)
 	{
		if (!response) {
	    	BPSInfo[playerid][Tels] = 0;
	    	return SendClientMessage(playerid, COLOR_LIGHTRED, "Você cancelou a lista de opções administrativas do TAB.");
      	}

		switch (listitem)
		{
			case 0:
			{
				format(string, sizeof(string),"%d", BPSInfo[playerid][Tels]);
				callcmd::ligar(playerid, string);
				return true;
			}
			case 1:
			{
			    if (Player_GetJailed(playerid) > 0) return SendClientMessage(playerid, -1, "Você não pode enviar mensagem de texto na cadeia.");

				ShowPlayerDialog(playerid, 9958, DIALOG_STYLE_INPUT, "Enviar SMS", "Digite a sua mensagem abaixo:", "Enviar", "Cancelar");
				return true;
			}
      		case 9:
			{
				format(string,sizeof(string),"%d",BPSInfo[playerid][pTels]);
				callcmd::tv(playerid, string);
				return true;
      		}
      		case 10:
			{
				format(string,sizeof(string),"%d",BPSInfo[playerid][pTels]);
				callcmd::trazer(playerid, string);
				return true;
  			}
      		case 11:
			{
		 		format(string,sizeof(string),"%d",BPSInfo[playerid][pTels]);
				callcmd::ir(playerid, string);
			   	return true;
      		}
 	    }
 	    return true;
	}

	else if (dialogid == 4275) {

	    if (response) {

	        if (!Player_Logado(List_GetPlayers(playerid, listitem))) 
				return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	        BPSInfo[playerid][pTels] = List_GetPlayers(playerid, listitem);
	        BPSInfo[playerid][Tels] = PlayerInfo[BPSInfo[playerid][pTels]][numeroCelular];

	        ShowPlayerDialog(playerid, 9958, DIALOG_STYLE_INPUT, "Mandar SMS", "Digite a sua mensagem abaixo:", "Enviar", "Cancelar");
	    }
	    return 1;
	}

    else if(dialogid == 9958)
   	{
    	if(response == 0)
    	{
    		BPSInfo[playerid][Tels] = 0;
    		return 1;
    	}
    	if(response >= 1)
    	{
    		format(string,sizeof(string),"%d %s",BPSInfo[playerid][Tels],inputtext);
   			callcmd::sms(playerid, string);
    		return 1;
    	}
    	return 1;
    }
   	else if(dialogid == 9960)
	{
		if(response == 0)
	    {
		    BPSInfo[playerid][Tels] = 0;
		    return 1;
	    }
	    if(response >= 1)
	    {
     		format(string,sizeof(string),"%d %s",BPSInfo[playerid][pTels],inputtext);
	        callcmd::kick(playerid, string);
	    	return 1;
	    }
	    return 1;
	}


	else if(dialogid == 9961)
	{
		if(response == 0)
	    {
	    	BPSInfo[playerid][Tels] = 0;
	        return 1;
	    }
	    if(response >= 1)
	    {
	    	format(string,sizeof(string),"%d %s",BPSInfo[playerid][pTels],inputtext);
	        callcmd::ban(playerid, string);
         	return 1;
	    }
		return 1;
	}

    return 0;
}

#if defined _INC_open_mp
public OnPlayerClickPlayer(playerid, clickedplayerid, CLICK_SOURCE:source)
#else
public OnPlayerClickPlayer(playerid, clickedplayerid, source)
#endif
{
	if (gIsInAdminPasswordScreen[playerid]) return 1;

	BPSInfo[playerid][Tels] = 0;
	BPSInfo[playerid][pTels] = 0;

	new pstring[550];

    format(pstring, sizeof(pstring),
	"Ligar\t{C1C1C2}Iniciar uma chamada de voz\n\
	Enviar mensagem\t{C1C1C2}Envia mensagem ao jogador");

    if (Admin_GetNivel(playerid))
    {
    	format(pstring, sizeof(pstring),
		"Modo TV\t{C1C1C2}Telar o jogador\n\
		Trazer\t{C1C1C2}Puxar o jogador\n\
		Ir\t{C1C1C2}Ir até o jogador");
	}

	new string[75];

	format(string, sizeof(string), "Ação para: {888888}%s", PlayerName[clickedplayerid]);
    ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, string, pstring, "Prosseguir", "Cancelar");

    BPSInfo[playerid][Tels] = PlayerInfo[clickedplayerid][numeroCelular];
    BPSInfo[playerid][pTels] = clickedplayerid;

	return 1;
}