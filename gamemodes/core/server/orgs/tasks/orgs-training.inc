


#if defined _INC_org_training
	#endinput
#endif
#define _INC_org_training

stock SendDeathMessageOrgTraining(killerid, playerid, reason)
{
	foreach(new i : Player)
	{
	    if(ChatKill[i] && GetPlayerOrg(i) == GetPlayerOrg(killerid))
		{
    		SendDeathMessageToPlayer(i, killerid, playerid, reason);
		}
	}
}

new PlayerText:textTraining[MAX_PLAYERS];

timer OrgTrainingTimer[600000](orgid)
{
	SendMsgAllF(COLOR_DBLUE, "[TREINAMENTO]: O treinamento que estava acontecendo na HQ %s terminou.", GetOrgName(orgid));
	CofreOrg[orgid][TrainingTime] = 0;
	GangZoneStopFlashForAll(GZOrg[orgid]);
	return 1;
}

// Sistema de Treinamento
CMD:iniciartreinamento(playerid, params[])
{
	new trainingTime,
		orgid = GetPlayerOrg(playerid);

	if (!Player_Logado(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está logado !");
	else if (CofreOrg[GetPlayerOrg(playerid)][InvasaoOrg]) 
		return SendClientMessage(playerid, -1, "Sua organização já atacou/defendeu uma HQ neste PayDay !");
	else if (PlayerInfo[playerid][pCargo] < 4) 
		return SendClientMessage(playerid, -1, "Você precisa ser cargo 4 ou superior.");
	else if (sscanf(params, "d", trainingTime)) 
		return SendClientMessage(playerid, -1, "Use: /iniciartreinamento [Tempo (Em minutos)]");
	else if (GetPlayerOrg(playerid) == 0) 
		return SendClientMessage(playerid, -1, "Você não é membro de uma organização !");
	else if (CofreOrg[orgid][TrainingOrg]) 
		return SendClientMessage(playerid, -1, "Sua organização já fez um treinamento neste payday!");
	else if (trainingTime < 3 || trainingTime > 10) 
		return SendClientMessage(playerid, -1, "O tempo deve estar entre 3 - 10 minutos!");
	else if (CofreOrg[orgid][InvasaoTempo]) 
		return SendClientMessage(playerid, -1, "Não é permitido iniciar um treinamento durante uma invasão!");

	new playersOnline = countMembrosOn(orgid);

	if (playersOnline < 3) 
		return SendClientMessage(playerid, -1, "Você não pode fazer uma treinamento com menos de 3 membros!");

	new string[128];
	
	CofreOrg[orgid][TrainingTime] = gettime() + (trainingTime * 60);
	CofreOrg[orgid][TrainingOrg] = 1;

	SendClientMessageToAll(GetPlayerColor(playerid), "|----------------------------------- | TREINAMENTO | ------------------------------------|");
	format(string, sizeof string, "* %s e %s %s iniciaram uma treinamento da organização!", PlayerName[playerid], GetOrgArticle(orgid), GetOrgName(orgid));
	SendClientMessageToAll(GetPlayerColor(playerid), string);
	format(string, sizeof string, "* Aproximadamente %d membros estão participando do treinamento.", playersOnline);
	SendClientMessageToAll(GetPlayerColor(playerid), string);
	SendClientMessageToAll(GetPlayerColor(playerid), "|------------------------------------------------------------------------------------------------|");

	trainingTime = trainingTime * 60 * 1000;

	defer OrgTrainingTimer[Timer:trainingTime](orgid);
	GangZoneFlashForAll(GZOrg[orgid], CoresOrg[orgid] - 0x15);
	return 1;
}

stock CreatePlayerTextDrawTraining(playerid) {
	textTraining[playerid] = CreatePlayerTextDraw(playerid, 547.000000, 341.000000, "TEMPO: ~h~03:00");
	PlayerTextDrawFont(playerid, textTraining[playerid] , TEXT_DRAW_FONT_3);
	PlayerTextDrawLetterSize(playerid, textTraining[playerid] , 0.233333, 1.450000);
	PlayerTextDrawTextSize(playerid, textTraining[playerid] , 400.000000, 129.000000);
	PlayerTextDrawSetOutline(playerid, textTraining[playerid] , 1);
	PlayerTextDrawSetShadow(playerid, textTraining[playerid] , 0);
	PlayerTextDrawAlignment(playerid, textTraining[playerid] , TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawColor(playerid, textTraining[playerid] , 9145343);
	PlayerTextDrawBackgroundColor(playerid, textTraining[playerid] , 255);
	PlayerTextDrawBoxColor(playerid, textTraining[playerid] , 30);
	PlayerTextDrawUseBox(playerid, textTraining[playerid] , true);
	PlayerTextDrawSetProportional(playerid, textTraining[playerid] , true);
	PlayerTextDrawSetSelectable(playerid, textTraining[playerid] , false);
}
