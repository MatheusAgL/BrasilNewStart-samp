
CMD:playerspb(playerid)
{
	new string[128],
        pbid;

    MEGAString[0] = EOS;

    strcat(MEGAString, "ID\tNome\tSala\n");

	foreach(new i : Player) 
    {
        pbid = Player_GetPaintball(i);

        if (pbid != INVALID_PAINTBALL_ID) {
            format(string, sizeof(string), ""C_GRAY"%02d\t"C_WHITE"%s\t%s\n", i, PlayerName[i], Paintball_GetName(pbid));
            strcat(MEGAString, string);
        }
    }
    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "PLAYERS NO PAINTBALL", MEGAString, "OK", "");
	return 1;
}

CMD:sairpb(playerid)
{
    if (Player_GetPaintball(playerid) == INVALID_PAINTBALL_ID) 
		return SendClientMessage(playerid, -1, "Voc� n�o est� na arena.");

	if (PlayerPaintball_GetOpponent(playerid) != INVALID_PLAYER_ID)
		return SendClientMessage(playerid, -1, "Voc� n�o pode sair da arena durante um duelo.");

    Paintball_Exit(playerid);
	return 1;
}

CMD:duel(playerid, params[])
{
    new pbid = Player_GetPaintball(playerid);

    if (pbid != INVALID_PAINTBALL_ID) 
        return SendClientMessage(playerid, -1, "Voc� n�o est� em um paintball!");

    new 
        Float:health,
        Float:armour;

 	GetPlayerHealth(playerid, health);
 	GetPlayerArmour(playerid, armour);

    if ((health + armour) < 195.0)
        return SendClientMessage(playerid, COLOR_LIGHTRED, "DUELO INFO: Voc� precisa estar com a vida e colete cheio para iniciar um DUELO!");

    new string[128],
        idplayer,
        world = Paintball_GetWorld(pbid),
        opponent = PlayerPaintball_GetOpponent(playerid);

	if (sscanf(params, "u", idplayer))
	{
	    if (opponent == INVALID_PLAYER_ID)
		{
		    if (GetPlayerInterior(playerid) == 1) 
                return Paintball_Spawn(playerid);

            SetPlayerPos(playerid, 1367.5123,-25.3243,1200.9219);
            SetPlayerFacingAngle(playerid, 271.4699);
            SetPlayerInterior(playerid, 1);
            SetPlayerVirtualWorld(playerid, playerid + world);

            format(string, sizeof (string), "[PAINTBALL-DUEL]: "C_CYAN"%s "C_PAINTBALL"chamou algu�m para um duelo, digite "C_GREEN"/duelo %d"C_PAINTBALL" para aceitar!", PlayerName[playerid], playerid);
            Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);

            SendClientMessage(playerid, COLOR_LIGHTRED, "Para cancelar voc� pode digitar /duelo novamente!");
	    } else {
            format(string, sizeof (string), "[PAINTBALL-DUEL]: "C_WHITE"O jogador %s {FF0000}Abandonou "C_WHITE"um duelo contra %s!", PlayerName[playerid], PlayerName[opponent]);
            Paintball_SendMessage(pbid, COLOR_PAINTBALL, string);

            Paintball_Bolt(playerid, opponent);
	    }
    } else {
	    if (Player_GetPaintball(idplayer) != pbid) 
            return SendClientMessage(playerid, -1, "Esse jogador n�o est� nessa sala.");

	    if (opponent != INVALID_PLAYER_ID) 
            return SendClientMessage(playerid, -1, "Voc� j� est� em um duelo!");

	    if (PlayerPaintball_GetOpponent(idplayer) != INVALID_PLAYER_ID) 
            return SendClientMessage(playerid, -1, "Este jogador j� est� em um duelo!");

	    if (GetPlayerInterior(idplayer) != 1) 
            return SendClientMessage(playerid, -1, "Este jogador n�o est� esperando um duelo!");

	    if (idplayer == playerid) 
            return SendClientMessage(playerid, -1, "Voc� n�o pode iniciar um duelo com voc� mesmo!");

	    Paintball_StartDuel(idplayer, playerid);
    }
    return 1;
}
alias:duel("duelo")

CMD:abrirpb(playerid, params[])
{
    new pbid = Player_GetPaintball(playerid);

    if (Paintball_GetOwner(pbid) != Player_GetAccountID(playerid)) 
		return SendClientMessage(playerid, -1, "Voc� precisa ser o dono desse paintball.");

    Paintball_Open(playerid, pbid);
	return 1;
}