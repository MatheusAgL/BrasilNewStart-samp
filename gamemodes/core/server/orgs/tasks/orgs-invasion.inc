#if defined _INC_org_invasion
	#endinput
#endif
#define _INC_org_invasion

// Sistema de invasão de HQ

new Timer:timer_invasao_gang[MAX_ORGS];

timer INVASION_Gangster_Timer[1000](orgid, orghq)
{
	new string[128];

	if (CofreOrg[orgid][InvasaoTempo] < 1) {

		format(string, sizeof string, "[INVASÃO DE HQ]: A invasão que estava acontecendo na HQ %s terminou.", GetOrgName(orghq));
		SendClientMessageToAll(COLOR_DBLUE, string);

		stop timer_invasao_gang[orgid];

		foreach(new playerid : Player) {

			if (GetPlayerOrg(playerid) == orgid || GetPlayerOrg(playerid) == orghq)
			{
				PlayerTextDrawHide(playerid, textInvasao[playerid]);
			}
		}

		return 1;
	}

	foreach(new playerid : Player)
	{
		if (GetPlayerOrg(playerid) == orgid || GetPlayerOrg(playerid) == orghq) {

			PlayerTextDrawShow(playerid, textInvasao[playerid]);

			format(string, sizeof string, "Tempo: ~g~~h~%s", ConvertTime(CofreOrg[orgid][InvasaoTempo]));
			PlayerTextDrawSetString(playerid, textInvasao[playerid], string);
		}
	}

	if (CofreOrg[orgid][InvasaoTempo] > 0)
	{
		CofreOrg[orgid][InvasaoTempo] --;
	}
	GangZoneStopFlashForAll(GZOrg[orgid]);
	return 1;
}

CMD:invadirhq(playerid, params[])
{
	if (!Player_Logado(playerid)) return SendClientMessage(playerid, -1, "Você não está logado !");

	if (!PlayerIsGang(playerid)) return SendClientMessage(playerid, -1, "Você não pode invadir HQ !");

	if (CofreOrg[GetPlayerOrg(playerid)][InvasaoOrg]) return SendClientMessage(playerid, -1, "Sua organização já atacou/defendeu uma HQ neste PayDay !");

	if (PlayerInfo[playerid][pCargo] < 4) return SendClientMessage(playerid, -1, "Você precisa ser cargo 4 ou superior.");

	new orgid, tempoinvasao;

	if (sscanf(params, "dd", orgid, tempoinvasao)) return SendClientMessage(playerid, -1, "Use: /invadirhq [ID da Gang] [Tempo (Em minutos)]");

	if (orgid < 1 || orgid >= MAX_ORGS) {
		return SendClientMessage(playerid, -1, "Você digitou um id de gang inválido !");
	}

	if (!PlayerIsGang(orgid)) {
		return SendClientMessage(playerid, -1, "Você só pode invadir HQ's de Gangsters !");
	}

	if (orgid == GetPlayerOrg(playerid)) {
		return SendClientMessage(playerid, -1, "Você não pode invadir sua própria HQ !");
	}

	if (CofreOrg[orgid][InvasaoOrg]) return SendClientMessage(playerid, -1, "Esta organização já atacou/defendeu uma HQ neste PayDay !");

	if (CofreOrg[orgid][TrainingTime]) 
		return SendClientMessage(playerid, -1, "Não é permitido invadir uma HQ durante um treinamento!");

	if (tempoinvasao < 5 || tempoinvasao > 20) return SendClientMessage(playerid, -1, "O tempo deve estar entre 3 - 10 minutos !");

	new PlayerOrg = GetPlayerOrg(playerid);
	new PlayersInvasao = GetMembrosPerto(playerid);

	if (PlayersInvasao < 5) return SendClientMessage(playerid, -1, "Você não pode fazer uma invasão com menos de 5 membros !");

	new string[128];

	CofreOrg[PlayerOrg][InvasaoTempo] = tempoinvasao * 60;
	CofreOrg[PlayerOrg][InvasaoOrg] = 1;
	CofreOrg[orgid][InvasaoOrg] = 1;

	SendClientMessageToAll(GetPlayerColor(playerid), "|----------------------------------- | INVASÃO DE HQ | ------------------------------------|");
	format(string, sizeof string, "* %s e %s %s iniciaram uma invasão na HQ %s %s!", PlayerName[playerid], GetOrgArticle(PlayerOrg), GetOrgName(PlayerOrg), GetOrgArticle(orgid, true), GetOrgName(orgid));
	SendClientMessageToAll(GetPlayerColor(playerid), string);
	format(string, sizeof string, "* Aproximadamente %d membros estão invadindo.", PlayersInvasao);
	SendClientMessageToAll(GetPlayerColor(playerid), string);
	SendClientMessageToAll(GetPlayerColor(playerid), "|------------------------------------------------------------------------------------------------|");

	stop timer_invasao_gang[PlayerOrg];
	timer_invasao_gang[PlayerOrg] = repeat INVASION_Gangster_Timer[Timer:1000](PlayerOrg, orgid);
	GangZoneFlashForAll(GZOrg[orgid], CoresOrg[PlayerOrg]);

	return 1;
}

stock CreatePlayerTextDrawInvasion(playerid) {
	textInvasao[playerid] = CreatePlayerTextDraw(playerid, 547.000000, 341.000000, "TEMPO: ~h~03:00");
	PlayerTextDrawFont(playerid, textInvasao[playerid], TEXT_DRAW_FONT_3);
	PlayerTextDrawLetterSize(playerid, textInvasao[playerid] , 0.233333, 1.450000);
	PlayerTextDrawTextSize(playerid, textInvasao[playerid] , 400.000000, 129.000000);
	PlayerTextDrawSetOutline(playerid, textInvasao[playerid] , 1);
	PlayerTextDrawSetShadow(playerid, textInvasao[playerid] , 0);
	PlayerTextDrawAlignment(playerid, textInvasao[playerid] , TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, textInvasao[playerid] , 9145343);
	PlayerTextDrawBackgroundColor(playerid, textInvasao[playerid] , 255);
	PlayerTextDrawBoxColor(playerid, textInvasao[playerid] , 30);
	PlayerTextDrawUseBox(playerid, textInvasao[playerid] , true);
	PlayerTextDrawSetProportional(playerid, textInvasao[playerid] , true);
	PlayerTextDrawSetSelectable(playerid, textInvasao[playerid] , false);
}