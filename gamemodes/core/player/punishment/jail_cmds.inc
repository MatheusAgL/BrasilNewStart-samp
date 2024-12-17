CMD:presos(playerid)
{
	new string[128];
	new count = 0;

	MEGAString[0] = EOS;

	strcat(MEGAString, "ID\tNick\tTempo\tCadeia\n");

	foreach(new players : Character)
	{
		if (Player_GetJailed(players) > 0 && Player_GetJailed(players) != 9)
		{
			format(string, sizeof string, "%02d\t%s\t{FF0000}%s (%d segundos)\tPrisão La Sante\n",
			players, PlayerName[players], ConvertTime(PlayerInfo[players][pJailTime]), PlayerInfo[players][pJailTime]);
			strcat(MEGAString, string);

			List_SetPlayers(playerid, count, players);
			count ++;
		}
		else if (Player_GetJailed(players) > 0 && Player_GetJailed(players) != 24)
		{
			format(string, sizeof string, "%02d\t%s\t{FF0000}%s (%d segundos)\t{E67ED6}Cadeia Admin\n",
			players, PlayerName[players], ConvertTime(PlayerInfo[players][pJailTime]), PlayerInfo[players][pJailTime]);
			strcat(MEGAString, string);

			List_SetPlayers(playerid, count, players);
			count ++;
		}
	}

	format(string, sizeof string, " {FFFFFF}Presos ({FF0000}%d{FFFFFF})", count);

	if (!count) {
		return SendClientMessage(playerid, -1, "Não tem nenhum preso online.");
	}
	ShowPlayerDialog(playerid, 33, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Infos", "Fechar");

	return 1;
}

CMD:explodirporta(playerid)
{
    if (gettime() < GetPVarInt(playerid, "flood_command")) return SendClientMessage(playerid, -1, "Você não pode usar este comando com tanta frequencia");

    if (!OrgsRoubo(playerid)) return SendClientMessage(playerid,-1, "Você precisa ser um gangster para explodir a porta da "_JAIL_NAME".");

    if (!IsPlayerInRangeOfPoint(playerid, 2.0, 1772.3076, -1548.2365, 9.9063))
        return SendClientMessage(playerid, -1, "Você não está na porta da "_JAIL_NAME"");

    if (JailInfo[jail_exploded]) return SendClientMessage(playerid, -1, "A porta da "_JAIL_NAME", já está sendo explodida por um gangster!");

    if (!Founders_GetList(playerid) && Staff_GetWorking(playerid)) return SendClientMessage(playerid, -1, "Você não pode explodir em modo trabalho!");

    new count_cops, count_players, count_amigos, count_presos, count_amigospreso;

    foreach(new x : Player)
    {
        if (ProxDetectorS(100.0, playerid, x)) 
        {
            count_players ++;

            if (IsACop(x)) 
                count_cops ++;
        
            if (GetPlayerOrg(x) == GetPlayerOrg(playerid)) 
                count_amigos++;
        }
        if (PlayerInfo[x][pJailed] == 24) 
        {
            count_presos ++;

            if (GetPlayerOrg(x) == GetPlayerOrg(playerid))
                count_amigospreso ++;
        }
    }

    MEGAString[0] = EOS;

    new string[128];

    strcat(MEGAString, "{FFFFFF}Você está prestes a explodir a porta da "_JAIL_NAME"!\n\n");

    format(string, sizeof string, "{F5DEB3}Pessoas perto do local: {FFFFFF}%d\n", count_players);
    strcat(MEGAString, string);
    format(string, sizeof string, "{F5DEB3}Amigos perto do local: {FFFFFF}%d\n", count_amigos);
    strcat(MEGAString, string);
    format(string, sizeof string, "{F5DEB3}Policiais perto do local: {FFFFFF}%d\n", count_cops);
    strcat(MEGAString, string);
    format(string, sizeof string, "{F5DEB3}Total de amigos preso: {FFFFFF}%d\n", count_amigospreso);
    strcat(MEGAString, string);
    format(string, sizeof string, "{F5DEB3}Total de presidiários: {FFFFFF}%d\n", count_presos);
    strcat(MEGAString, string);
    strcat(MEGAString, "{F5DEB3}Porcentagem de sucesso: {FFFFFF}70\n");

    strcat(MEGAString, "\n{FF6347}OBS: {B4B5B7}Aguarde 40 segundos para plantar a bomba na porta do presidio\n");
    strcat(MEGAString, "Fique esperto, pois a polícia será avisada dessa tentativa de resgate.\n");

    SetPVarInt(playerid, "flood_command", gettime() + 10);
    ShowPlayerDialog(playerid, 60, DIALOG_STYLE_MSGBOX, "Informações atuais da prisão:", MEGAString, "Explodir", "Cancelar");
    return 1;
}