#include <YSI_Coding\y_hooks>

#define 	MAX_SOUNDS		50

enum somI
{
	bool:  		somCreated,
	Float: 		somX,
	Float: 		somY,
	Float: 		somZ,
	Float:      somVida,
	Text3D:  	somText,
	somLink     [256],
	somVolume,
	somID,
	somWorld,
	somObject,
};
new bool: OuvindoSom[MAX_PLAYERS];
new SomInfo[MAX_SOUNDS][somI];

stock const URL_WhiteList[][] =
{
	{"https://"},
	{"https://www.dropbox.com"},
	{"http://yp.shoutcast.com"},
	{"http://shoutcast.com"},
	{"http://radio"},
	{SERVER_SITE} // Site do servidor, lista branca.
};

stock IsLinkAllow(const link[])
{
	for(new whitelink = 0; whitelink < sizeof (URL_WhiteList); whitelink++)
	{
		if (strfind(link, URL_WhiteList[whitelink]) == 0) return true;
	}
	return false;
}

hook OP_ShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z){

	for(new id; id != MAX_SOUNDS; id++)
	{
	    if(SomInfo[id][somCreated] && objectid == SomInfo[id][somObject] && Admin_GetNivel(playerid))
		{
			GameTextForPlayer(playerid, "~r~~>~destruindo radio~<~", 5000, 1);

	        if(SomInfo[id][somVida] > 0)
			{
	            SomInfo[id][somVida] -= 4.0;
	        }
			else
			{
             	new string[97];

	            GetPVarString(playerid, "nameRadioPortatil", string, 20);

				givePlayerItem(SomInfo[id][somID], ITEM_TYPE_RADIO, GetPVarInt(playerid, "modelidRadio"), 1, string);

	            format(string, sizeof string, "AVISO: %s destruiu sua JBL.", PlayerName[playerid]);
	            SendClientMessage(SomInfo[id][somID], COLOR_LIGHTRED, string);

				format(string, sizeof(string), "* %s destruiu o JBL de %s.", PlayerName[playerid], PlayerName[SomInfo[id][somID]]);
				SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

				destroyPlayerSound(SomInfo[id][somID]);
	        }
	        break;
	    }
	}
	return true;
}

CMD:tocarsom(playerid, params[])
{
 	if (!PlayerInfo[playerid][segurandoRadio]) 
		return SendClientMessage(playerid, -1, "Você não está com seu rádio em mãos.");

    if (isPertoSound(playerid) || isPlayerSound(playerid)) 
		return SendClientMessage(playerid, -1, "Há um rádio tocando muito próximo a esse local ou seu rádio já está tocando.");

	if (IsPlayerInSafeZone(playerid)) 
		return SendClientMessage(playerid, -1, "Você não pode fazer isso em uma Área Segura.");

	if (GetPlayerSpeedEx(playerid) > 1) 
		return SendClientMessage(playerid, -1, "Você precisa estar parado para colocar seu rádio.");

	MEGAString[0] = EOS;

	strcat(MEGAString, "\n		{FFFFFF}Caixa de Som {A9A6A6}(usado para tocar músicas para jogadores próximos)		\n\n");

    strcat(MEGAString, "{A9A6A6}Exemplo de link: {FFFFFF}https://sounds."SERVER_SITE"/musica_login.mp3\n\n");

    strcat(MEGAString, "{A9A6A6}WhiteList de links que podem ser usados: {FFFFFF}'https://, https://www.dropbox.com...\n");
    strcat(MEGAString, "								{FFFFFF}http://yp.shoutcast.com, http://radio...\n");
    strcat(MEGAString, "								{FFFFFF}https://"SERVER_SITE"'\n\n");

    strcat(MEGAString, "{A9A6A6}Exemplo de link do Youtube: {FFFFFF}www.youtube.com/watch?v=YgFyi74DVjc\n");

	inline Dialog_RadioPortatil(pid, dialogid, response, listitem, string:inputtext[]) 
	{
		#pragma unused pid, dialogid, listitem

		if (response)
		{
			if (strlen(inputtext) > 250) 
				return SendClientMessage(playerid, -1, "O link que você digitou está muito grande.");

			if (isPertoSound(playerid)) 
				return SendClientMessage(playerid, -1, "Há um rádio tocando próximo a este local.");

			if (!IsLinkAllow(inputtext)) 
				return SendClientMessage(playerid, -1, "Link não permitido! Recomendamos que você use o site: {A9A6A6}www.palcomp3.com");

			new string[128];
			format(string, sizeof(string), "(( %s ligou sua caixa de som ))", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

            ApplyAnimation(playerid, "BOMBER", "BOM_Plant_2Idle", 4.1, 0, 1, 1, 0, 0);

            RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);
            PlayerInfo[playerid][segurandoRadio] = false;

            if (strfind(inputtext,"www.youtube.com",true) != -1) 
			{
				new localURL[128];
				strmid(localURL, inputtext, strfind(inputtext, "v=")+2, strfind(inputtext, "v=")+19);
				format(inputtext, 128, "http://mwrserver.com/youtube.php?videoid=%s", localURL);
            }
		    createSound(playerid, GetPVarInt(playerid, "modelidRadio"), inputtext, 40); 
			CheckConquista(playerid, Conquista_Musica);  	/* Cria o rádio e checa se o jogador recebeu conquista */
		}
	}
	Dialog_ShowCallback(playerid, using inline Dialog_RadioPortatil,
		DIALOG_STYLE_INPUT,
		"Radio portatil", MEGAString, "Ligar", "Cancelar"
	);

	return 1;
}

CMD:volumeradio(playerid, params[])
{
    if (!isPertoSound(playerid) && !idMySoundBox(playerid)) return SendClientMessage(playerid, -1, "Você não está próximo a sua caixa de som.");

    new volumeRadio;
	if (sscanf(params, "d", volumeRadio)) return SendClientMessage(playerid, -1, "Modo de uso: /volumeradio (volume 10 á 120)");

    switch (GetPVarInt(playerid, "modelidRadio"))
    {
        case 2102: if (volumeRadio < 10 || volumeRadio > 80) return SendClientMessage(playerid, -1, "A sua caixa de som vai apenas do volume 10 até o volume 80.");
        default: if (volumeRadio < 10 || volumeRadio > 40) return SendClientMessage(playerid, -1, "A sua caixa de som vai apenas do volume 10 até o volume 40.");
    }

    new string[98];

    format(string, sizeof(string), "* %s aumentou o volume do seu rádio para %d.", PlayerName[playerid], volumeRadio);
	SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

    SomInfo[idMySoundBox(playerid)][somVolume] = volumeRadio;

	return 1;
}

CMD:guardarradio(playerid)
{
	//if (IsPlayerCongelado(playerid)) return SendClientMessage(playerid, -1, "Você não pode usar esse comando pois está congelado.");

	if(IsPlayerCuffed(playerid)) return SendClientMessage(playerid, -1, "Você não pode usar o comando no momento.");

	if(!PlayerInfo[playerid][segurandoRadio])return SendClientMessage(playerid, -1, "Você não está com sua caixa de som em mãos.");

	if(isPlayerSound(playerid))return SendClientMessage(playerid, -1, "Sua JBL está tocando no momento, pegue-a antes de guardar.");

	new radioName_string[20];
	GetPVarString(playerid, "nameRadioPortatil", radioName_string, 20);

	givePlayerItem(playerid, ITEM_TYPE_RADIO, GetPVarInt(playerid, "modelidRadio"), 1, radioName_string);

    new string[73];
	format(string, sizeof(string), "* %s guardou seu radio %s.", PlayerName[playerid], radioName_string);
	SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

    PlayerInfo[playerid][segurandoRadio] = false;

	RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);

	return true;
}

stock createSound(playerid, modelid, const urlSound[], volumeRadio)
{
	new Float:Pos[4], string[78];

	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	GetPlayerFacingAngle(playerid, Pos[3]);

	for(new x; x != MAX_SOUNDS; x++)
	{
	    if (!SomInfo[x][somCreated])
		{
	        SomInfo[x][somCreated] 		= true;

	        SomInfo[x][somWorld]        = GetPlayerVirtualWorld(playerid);

	        SomInfo[x][somVida] 		= 100.0;
	        SomInfo[x][somVolume]       = volumeRadio;

	        SomInfo[x][somX] 			= Pos[0];
	        SomInfo[x][somY] 			= Pos[1];
	        SomInfo[x][somZ] 			= Pos[2]-0.95;
	        SomInfo[x][somID]           = playerid;

	        format(SomInfo[x][somLink], 128, urlSound);

            SomInfo[x][somObject] 		= CreateDynamicObject(modelid, SomInfo[x][somX], SomInfo[x][somY], SomInfo[x][somZ], 0.0, 0.0, Pos[3], SomInfo[x][somWorld]);

	        format(string, sizeof string, "=(:::))) Som de: %s[%d] (((:::)=", PlayerName[playerid], playerid);

            SomInfo[x][somText]         = CreateDynamic3DTextLabel(string, 0x5982D3F9, SomInfo[x][somX], SomInfo[x][somY], SomInfo[x][somZ]+0.3, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, SomInfo[x][somWorld]);

			return true;
		}
	}
	return true;
}

stock destroySound(id)
{
	if(SomInfo[id][somCreated])
	{
	    SomInfo[id][somCreated] = false;

	    DestroyDynamicObject(SomInfo[id][somObject]);
	    DestroyDynamic3DTextLabel(SomInfo[id][somText]);
	    SomInfo[id][somID] = 999;

	    foreach(new i : Player)
		{
	        if (IsPlayerInRangeOfPoint(i, 71.0, SomInfo[id][somX], SomInfo[id][somY], SomInfo[id][somZ]) && OuvindoSom[i] && GetPlayerVirtualWorld(i) == SomInfo[id][somWorld])
			{
	            StopPlayerAudioStream(i);
	            OuvindoSom[i] = false;
	        }
	    }
	}
}

stock isPlayerSound(playerid)
{
	for(new x; x != MAX_SOUNDS; x++)
	{
		if(SomInfo[x][somCreated] && SomInfo[x][somID] == playerid) return true;
	}
	return false;
}

stock isPertoSound(playerid)
{
	for(new x; x != MAX_SOUNDS; x++)
	{
		if (SomInfo[x][somCreated] && GetPlayerVirtualWorld(playerid) == SomInfo[x][somWorld] && IsPlayerInRangeOfPoint(playerid, SomInfo[x][somVolume], SomInfo[x][somX], SomInfo[x][somY], SomInfo[x][somZ]))
			return true;
	}
	return false;
}

stock idMySoundBox(playerid)
{
	for(new x; x != MAX_SOUNDS; x++)
	{
		if (SomInfo[x][somCreated] && SomInfo[x][somID] == playerid)
            return x;
	}
	return false;
}

stock destroyPlayerSound(playerid)
{
	for(new x; x != MAX_SOUNDS; x++)
	{
	    if (SomInfo[x][somCreated] && SomInfo[x][somID] == playerid)
			destroySound(x);
	}
}

stock CheckSoundProx(playerid)
{
	new string[61];

	for(new x; x != MAX_SOUNDS; x++)
	{
		if (SomInfo[x][somCreated] && GetPlayerVirtualWorld(playerid) == SomInfo[x][somWorld] && IsPlayerInRangeOfPoint(playerid, SomInfo[x][somVolume], SomInfo[x][somX], SomInfo[x][somY], SomInfo[x][somZ]))
		{
			if (!OuvindoSom[playerid] && !PlayerListeningRadio(playerid))
			{
				OuvindoSom[playerid] = true;

				PlayAudioStreamForPlayer(playerid, SomInfo[x][somLink], SomInfo[x][somX], SomInfo[x][somY], SomInfo[x][somZ], SomInfo[x][somVolume], true);

				format(string, sizeof string, "=(:::))) Você está ouvindo o som de: %s[%d]", PlayerName[SomInfo[x][somID]], SomInfo[x][somID]);
				SendClientMessage(playerid, 0x5982D3FF, string);

			}
			return true;
   		}
	}
   	if (OuvindoSom[playerid])
	{
		StopPlayerAudioStream(playerid);
  		OuvindoSom[playerid] = false;
	}
	return true;
}