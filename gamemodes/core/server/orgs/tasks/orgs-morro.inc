//-------------------------------------------------------- Sistema de Guerra do Morro -------------------------------------------------------------------

#include < YSI_Coding\y_hooks >

new playerAreaMorro[MAX_PLAYERS];

new Text:guerraMorroTextDraw[9];

hook OnPlayerDeath(playerid, killerid, reason) 
{
	if (killerid != INVALID_PLAYER_ID)
	{
		// Guerra morro
		if(gGuerraMorro) {
			gCheckPontos(playerid, killerid);
		}
	}
	return 1;
}

stock OrgMorro(orgid)
{
	switch(orgid){
	    case 1, 2, 5, 14, 17, 18, 19, 21, 33, 34: return true;
	}
	return false;
}

stock gPlayerInGuerra(playerid) {

    if (!gGuerraMorro) return false;

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    if (x >= 1969 && y >= -1099.5 && x <= 2162 && y <= -902.5) return playerAreaMorro[playerid] = 0, true;
    else if (x >= 2162 && y >= -1133.5 && x <= 2407 && y <= -921.5) return playerAreaMorro[playerid] = 1, true;
    else if (x >= 2408 && y >= -1135.5 && x <= 2640 && y <= -921.5) return playerAreaMorro[playerid] = 2, true;

    else return false;
}

stock gIniciarGuerraMorro()
{
	if (!gGuerraMorro)
	{
		gSendMessage(0x00AA00FF, "» ---------------------------------------------------------------------------------------------------------------------- «");

		gSendMessage(0xF0EDEDFF, "» {00AA00}GUERRA DO MORRO {F0EDED}| A guerra foi iniciada, boa sorte as organizações participantes");

		gSendMessage(0xF0EDEDFF, "» {00AA00}Prêmio: {F0EDED}Dinheiro, respeito e caixa surpresa para os participantes da organização que vencer e dinheiro na organização!");

	    SendClientMessageToAll(0xF0EDEDFF, "» {00AA00}Guerra no morro: {F0EDED}Cidadãos, não se aproximem da área do morro ou poderão ser mortos!");

		SoundToAll(1133);

		for(new orgsid; orgsid < MAX_ORGS; orgsid++) {

			if (OrgMorro(orgsid)) SendMembersMessage(orgsid, 0xF0EDEDFF, "» {FF0000}Atenção: {F0EDED}Sua organização é participante do morro!!");
		}

		gSendMessage(0x00AA00FF, "» ---------------------------------------------------------------------------------------------------------------------- «");

		gIniciarRespawn(); // Respawn automático dos veículos do servidor

		gGuerraMorro	= true;
		gTempoMorro		= 60 * 15;
		gDinheiro		= 0;

		for(new area = 0; area < MAX_AREA_MORRO; area++) {

			GuerraMorro[area][gPontosDono]	= 0;
			GuerraMorro[area][gDono]		= 0;
			GuerraMorro[area][gMortes]		= 0;
			GuerraMorro[area][gColor]		= 0xAAAAAAAA;

		}

		gCriarTextdraws();

		gTimerMorro = SetTimer("UpdateMorro", 3000, true);

		for(new orgsid; orgsid < MAX_ORGS; orgsid++) {

            for(new area = 0; area < MAX_AREA_MORRO; area++) {
				MorroPontos[area][orgsid] = 0;
			}
		}
	}
}

gFlashGZ(){

    for(new gZone = 0; gZone < sizeof(GZMorro); gZone++) {

		GangZoneShowForAll(GZMorro[gZone], 0x000000AA);

		GangZoneFlashForAll(GZMorro[gZone], GuerraMorro[gZone][gColor]);
	}
}

gStopFlash() {

	for(new gZone = 0; gZone < sizeof(GZMorro); gZone++){

		GangZoneStopFlashForAll(GZMorro[gZone]);

		GangZoneShowForAll(GZMorro[gZone], GuerraMorro[gZone][gColor]);
	}
}

gCriarTextdraws() {

	guerraMorroTextDraw[0] = TextDrawCreate(53.666687, 112.429679, "_");
	TextDrawLetterSize(guerraMorroTextDraw[0], 0.418999, 16.785486);
	TextDrawTextSize(guerraMorroTextDraw[0], 0.000000, 97.000000);
	TextDrawAlignment(guerraMorroTextDraw[0], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(guerraMorroTextDraw[0], -1);
	TextDrawUseBox(guerraMorroTextDraw[0], true);
	TextDrawBoxColor(guerraMorroTextDraw[0], 320017248);
	TextDrawSetShadow(guerraMorroTextDraw[0], 0);
	TextDrawBackgroundColor(guerraMorroTextDraw[0], 255);
	TextDrawFont(guerraMorroTextDraw[0], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(guerraMorroTextDraw[0], true);

	guerraMorroTextDraw[1] = TextDrawCreate(53.333309, 109.525833, "Guerra do Morro");
	TextDrawLetterSize(guerraMorroTextDraw[1], 0.175000, 1.529481);
	TextDrawTextSize(guerraMorroTextDraw[1], 0.000000, 266.000000);
	TextDrawAlignment(guerraMorroTextDraw[1], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(guerraMorroTextDraw[1], -657140481);
	TextDrawSetShadow(guerraMorroTextDraw[1], 0);
	TextDrawBackgroundColor(guerraMorroTextDraw[1], 255);
	TextDrawFont(guerraMorroTextDraw[1], TEXT_DRAW_FONT_2);
	TextDrawSetProportional(guerraMorroTextDraw[1], true);

	guerraMorroTextDraw[2] = TextDrawCreate(54.000026, 148.196762, "_");
	TextDrawLetterSize(guerraMorroTextDraw[2], 0.464333, 1.429926);
	TextDrawTextSize(guerraMorroTextDraw[2], 0.000000, 97.000000);
	TextDrawAlignment(guerraMorroTextDraw[2], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(guerraMorroTextDraw[2], -1);
	TextDrawUseBox(guerraMorroTextDraw[2], true);
	TextDrawBoxColor(guerraMorroTextDraw[2], 320017248);
	TextDrawSetShadow(guerraMorroTextDraw[2], 0);
	TextDrawBackgroundColor(guerraMorroTextDraw[2], 255);
	TextDrawFont(guerraMorroTextDraw[2], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(guerraMorroTextDraw[2], true);

	guerraMorroTextDraw[3] = TextDrawCreate(54.000022, 180.137542, "_");
	TextDrawLetterSize(guerraMorroTextDraw[3], 0.464333, 1.429926);
	TextDrawTextSize(guerraMorroTextDraw[3], 0.000000, 97.000000);
	TextDrawAlignment(guerraMorroTextDraw[3], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(guerraMorroTextDraw[3], -1);
	TextDrawUseBox(guerraMorroTextDraw[3], true);
	TextDrawBoxColor(guerraMorroTextDraw[3], 320017248);
	TextDrawSetShadow(guerraMorroTextDraw[3], 0);
	TextDrawBackgroundColor(guerraMorroTextDraw[3], 255);
	TextDrawFont(guerraMorroTextDraw[3], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(guerraMorroTextDraw[3], true);

	guerraMorroTextDraw[4] = TextDrawCreate(53.666702, 212.493057, "_");
	TextDrawLetterSize(guerraMorroTextDraw[4], 0.464333, 1.429926);
	TextDrawTextSize(guerraMorroTextDraw[4], 0.000000, 97.000000);
	TextDrawAlignment(guerraMorroTextDraw[4], TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(guerraMorroTextDraw[4], -1);
	TextDrawUseBox(guerraMorroTextDraw[4], true);
	TextDrawBoxColor(guerraMorroTextDraw[4], 320017248);
	TextDrawSetShadow(guerraMorroTextDraw[4], 0);
	TextDrawBackgroundColor(guerraMorroTextDraw[4], 255);
	TextDrawFont(guerraMorroTextDraw[4], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(guerraMorroTextDraw[4], true);

	guerraMorroTextDraw[5] = TextDrawCreate(9.333314, 148.518463, "G.R.O.T.A~n~ ~n~ ~n~ADA~n~ ~n~ ~n~P.C.C");
	TextDrawLetterSize(guerraMorroTextDraw[5], 0.174333, 1.172742);
	TextDrawTextSize(guerraMorroTextDraw[5], 325.000000, 0.000000);
	TextDrawAlignment(guerraMorroTextDraw[5], TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(guerraMorroTextDraw[5], -657140481);
	TextDrawSetShadow(guerraMorroTextDraw[5], 0);
	TextDrawBackgroundColor(guerraMorroTextDraw[5], 255);
	TextDrawFont(guerraMorroTextDraw[5], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(guerraMorroTextDraw[5], true);

	guerraMorroTextDraw[6] = TextDrawCreate(7.666648, 136.073989, "parte ~g~I  ~n~ ~n~ ~n~~w~parte ~y~II~n~ ~n~ ~n~~w~parte ~r~III");
	TextDrawLetterSize(guerraMorroTextDraw[6], 0.167333, 1.152001);
	TextDrawTextSize(guerraMorroTextDraw[6], 325.000000, 0.000000);
	TextDrawAlignment(guerraMorroTextDraw[6], TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(guerraMorroTextDraw[6], -657140481);
	TextDrawSetShadow(guerraMorroTextDraw[6], 0);
	TextDrawBackgroundColor(guerraMorroTextDraw[6], 255);
	TextDrawFont(guerraMorroTextDraw[6], TEXT_DRAW_FONT_2);
	TextDrawSetProportional(guerraMorroTextDraw[6], true);

	guerraMorroTextDraw[7] = TextDrawCreate(100.000007, 148.933288, "1060 ~w~pontos ~n~ ~n~ ~n~1080 pontos ~n~ ~n~ ~n~1080 pontos");
	TextDrawLetterSize(guerraMorroTextDraw[7], 0.174333, 1.172742);
	TextDrawTextSize(guerraMorroTextDraw[7], 325.000000, 0.000000);
	TextDrawAlignment(guerraMorroTextDraw[7], TEXT_DRAW_ALIGN_RIGHT);
	TextDrawColor(guerraMorroTextDraw[7], -1);
	TextDrawSetShadow(guerraMorroTextDraw[7], 0);
	TextDrawBackgroundColor(guerraMorroTextDraw[7], 255);
	TextDrawFont(guerraMorroTextDraw[7], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(guerraMorroTextDraw[7], true);

	guerraMorroTextDraw[8] = TextDrawCreate(16.333312, 236.836975, "Dinheiro ~g~$1.500~n~~w~Tempo~p~ 800");
	TextDrawLetterSize(guerraMorroTextDraw[8], 0.245000, 1.251556);
	TextDrawTextSize(guerraMorroTextDraw[8], 325.000000, 0.000000);
	TextDrawAlignment(guerraMorroTextDraw[8], TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(guerraMorroTextDraw[8], -657140481);
	TextDrawSetShadow(guerraMorroTextDraw[8], 0);
	TextDrawBackgroundColor(guerraMorroTextDraw[8], 255);
	TextDrawFont(guerraMorroTextDraw[8], TEXT_DRAW_FONT_1);
	TextDrawSetProportional(guerraMorroTextDraw[8], true);
}

gDestruirTextdraws(){

	for(new textGMorro; textGMorro != sizeof guerraMorroTextDraw; textGMorro++) {
	   	TextDrawDestroy(guerraMorroTextDraw[textGMorro]);
	}
}

stock gSendMessage(color, const message[], hideable=0){
	foreach(new player : Player) {
		if(OrgMorro(GetPlayerOrg(player)) && (!hideable || PlayerInfo[player][pChatMorro])){
			SendClientMessage(player, color, message);
		}
	}
	return 1;
}

stock gTerminarGuerraMorro()
{
	KillTimer(gTimerMorro);

	gDestruirTextdraws();
	gStopFlash();
	gGuerraMorro = false;

	foreach(new i : Player)
	{
	    for(new areaMorro = 0; areaMorro < sizeof(GZMorro); areaMorro++)
		{
   			if (GetPlayerOrg(i) == GuerraMorro[areaMorro][gDono] && GetPVarInt(i, "morroBonus") == 1)
			{
				new rand_dinheiro = 5000 + random(10000), rand_respeito = random(7);
				Player_AddMoney(i, rand_dinheiro);

				if(rand_respeito > 0)
					addQuantiaItem(i, ITEM_TYPE_RESPEITO, 19941, rand_respeito, "Respeito", 0, 0);

				// 5% de chance de ganhar caixa Gold
				new rand_caixa = random(100);
				if(rand_caixa >= 20 && rand_caixa < 25) {
					SendMsgF(i, COLOR_LIGHTBLUE,  "» Prêmio da Área %d do Morro: Dinheiro: $%s | Respeito: %d | {FEE73A}Caixa Surpresa GOLD", areaMorro+1, getFormatText(rand_dinheiro), rand_respeito);
					new string[256];
					format(string, 256, "%s recebeu uma Caixa Surpresa GOLD como prêmio da região %d do Morro", PlayerName[i], areaMorro + 1);
					SendClientMessageToAll(0xFEE73AFF, string);
					GiftBox_Give(i, ITEM_TYPE_CAIXAGOLD, false);
				}
				else {
					GiftBox_Give(i, ITEM_TYPE_CAIXAGIGANTE, false);
					SendMsgF(i, COLOR_LIGHTBLUE,  "» Prêmio da Área %d do Morro: Dinheiro: $%s | Respeito: %d | Caixa Surpresa Gigante", areaMorro+1, getFormatText(rand_dinheiro), rand_respeito);
				}

   				CheckConquista(i, Conquista_Morro);
			}
		}
	}

	new gStr[128];

    SendClientMessageToAll(0x00AA00FF, "» ---------------------------------------------------------------------------------------------------------------------- «");

	SendClientMessageToAll(0xF0EDEDFF, "» {00AA00}GUERRA DO MORRO {F0EDED}| A guerra foi finalizada, parabéns aos participantes!");

	for(new areaMorro = 0; areaMorro < sizeof(GZMorro); areaMorro++)
	{
   		format(gStr, 128, "» {%s}%s{F0EDED} venceu a parte %d do morro com {00BFFF}%d {F0EDED}pontos e %d mortes.", GetOrgColor(GuerraMorro[areaMorro][gDono]),
		GetOrgName(GuerraMorro[areaMorro][gDono]), areaMorro+1, MorroPontos[areaMorro][GuerraMorro[areaMorro][gDono]], GuerraMorro[areaMorro][gMortes]);
   		SendClientMessageToAll(0xF0EDEDFF, gStr);

		OrgInfo_SetMoney(GuerraMorro[areaMorro][gDono], OrgInfo_GetMoney(GuerraMorro[areaMorro][gDono]) + gDinheiro/3);
	}

	SendClientMessageToAll(0x00AA00FF, "» ---------------------------------------------------------------------------------------------------------------------- «");
    SoundToAll(1133);

	Morro_RespawnVehicles();
}

stock Morro_RespawnVehicles() {

    for (new v; v < MAX_VEHICLES; v++) {
        if (!Morro_VehicleIn(v)) 
            continue;

        new bool:vehicle_Used = true;
        foreach (new i : Player) {
            if (GetPlayerVehicleID(i) == v) 
                vehicle_Used = false;
        }
        if (vehicle_Used) {
            SetVehicleToRespawn(v);
            StopVehicleEngine(v);
            StopVehicleLights(v);
        }
        SendClientMessageToAll(COLOR_YELLOW, "Respawn morro: Os veículos do morro foram spawnados.");
    }
}

stock Morro_VehicleIn(vehicleid) {

    new Float: vX, Float: vY, Float: vZ;

    GetVehiclePos(vehicleid, vX, vY, vZ);

    if (vX >= 1969 && vY >= -1099.5 && vX <= 2162 && vY <= -902.5 ||
        vX >= 2162 && vY >= -1133.5 && vX <= 2407 && vY <= -921.5 ||
        vX >= 2408 && vY >= -1135.5 && vX <= 2640 && vY <= -921.5)
            return true;
    
    return false;
}

gCheckPontos(playerid, killerid)
{
	new gStr[156];

	if (killerid == INVALID_PLAYER_ID) {

	    if (wLastShooter[playerid] != INVALID_PLAYER_ID && gettime() < (GetPVarInt(playerid, "VarDano") + 80)) {

			new playerOrg = GetPlayerOrg(playerid);
			new killerOrg = GetPlayerOrg(wLastShooter[playerid]);
			new areaMorro = playerAreaMorro[wLastShooter[playerid]];

			if (playerOrg == killerOrg) return true;

			if (OrgMorro(playerOrg) && OrgMorro(killerOrg))
			{
				if((IsACop(playerid) && OnDuty[playerid] == 0) || (IsACop(killerid) && OnDuty[killerid] == 0))
					return true;

			    if (gPlayerInGuerra(wLastShooter[playerid])) {

            		format(gStr, 128, "Guerra do Morro: {%06x}%s(%s) {F0EDED}SE MATOU, +60 pontos para o(a): {%06x}%s", GetPlayerColor(playerid) >>> 8, PlayerName[playerid], GetOrgName(playerOrg), GetPlayerColor(wLastShooter[playerid]) >>> 8, GetOrgName(killerOrg));
            		gSendMessage(0x00AA00FF, gStr);

				    GuerraMorro[areaMorro][gMortes] 	++;
				    gDinheiro += 50+random(100);

				    MorroPontos[areaMorro][killerOrg] 	+= 60;

				    if (MorroPontos[areaMorro][killerOrg] > GuerraMorro[areaMorro][gPontosDono])
					{
						if (GuerraMorro[areaMorro][gDono] != killerOrg)
						{
				     		format(gStr, 128, "Guerra do Morro: {%06x}%s {F0EDED}assumiu a parte %d do morro com: {FF0000}%d {F0EDED}assassinatos.", GetPlayerColor(killerOrg) >>> 8, GetOrgName(killerOrg), areaMorro+1, MorroPontos[killerOrg]);
							gSendMessage(0x00AA00FF, gStr);

							SendMembersMessage(killerOrg, COLOR_LIGHTBLUE, "** Vocês agora estão na liderança da guerra no morro, não deixem que a tomem de vocês **");
						}

			     		GuerraMorro[areaMorro][gPontosDono] = MorroPontos[areaMorro][killerOrg];
			     		GuerraMorro[areaMorro][gDono]       = killerOrg;
			     		GuerraMorro[areaMorro][gColor]      = GetPlayerColor(wLastShooter[playerid])+75;
					}
			    }
			}
	    }
	} else {

		if ((Admin_GetNivel(killerid) || Helper_GetNivel(killerid)) && Staff_GetWorking(killerid)) return true;
		if (!gPlayerInGuerra(killerid) && !gPlayerInGuerra(playerid)) return false;

		new playerOrg = GetPlayerOrg(playerid),
			killerOrg = GetPlayerOrg(killerid),
			areaMorro = playerAreaMorro[killerid];

		if (!gPlayerInGuerra(killerid)) return true;

		if(OrgMorro(playerOrg) && OrgMorro(killerOrg) && playerOrg != killerOrg){

			if((IsACop(playerid) && OnDuty[playerid] == 0) || (IsACop(killerid) && OnDuty[killerid] == 0))
				return true;

		    GuerraMorro[areaMorro][gMortes] 		++;
			new money = 1000+random(3000);

			if(PlayerInfo[playerid][pConta] > money) {
				PlayerInfo[playerid][pConta] -= money;
			}
			else if(Player_GetMoney(playerid) > money) {
				Player_RemoveMoney(playerid, money);
			}
		    gDinheiro += money;

		    MorroPontos[areaMorro][killerOrg] 		+= 60;

            format(
				gStr, 128, "Guerra do Morro: {FFFFFF}%s matou {%06x}%s {FFFFFF}na Parte %d e pontuou 60 para: {%06x}%s", 
				PlayerName[killerid], GetPlayerColor(playerid) >>> 8, 
				PlayerName[playerid], areaMorro+1, GetPlayerColor(killerid) >>> 8, 
				GetOrgName(killerOrg)
			);
            gSendMessage(0x00AA00FF, gStr);

		    if (MorroPontos[areaMorro][killerOrg] > GuerraMorro[areaMorro][gPontosDono]){

				if(GuerraMorro[areaMorro][gDono] != killerOrg){

		     		format(gStr, 128, "Guerra do Morro: {F0EDED}%s assumiu a liderança da parte %d com {00BFFF}%d {F0EDED}pontos.", GetOrgName(killerOrg), areaMorro+1, MorroPontos[areaMorro][killerOrg]);
					gSendMessage(0x00AA00FF, gStr);

					format(gStr, 128, "**!** A sua organização está na liderança da parte %d do morro.", areaMorro+1);
					SendMembersMessage(killerOrg, COLOR_LIGHTBLUE, gStr);
				}

	     		GuerraMorro[areaMorro][gPontosDono] = MorroPontos[areaMorro][killerOrg];
	     		GuerraMorro[areaMorro][gDono]       = killerOrg;
	     		GuerraMorro[areaMorro][gColor]      = GetPlayerColor(killerid)+75;
			}
			createDropBox(playerid);
		}
	}
	return 1;
}

CALLBACK:UpdateMorro()
{
    if (gTempoMorro > 0)
	{
		gTempoMorro--;
	}

	gDinheiro += 10+random(20);

    gFlashGZ();
	new gStr[500], gPontos[92], gTempoDinheiro[92];

	foreach(new gPlayer : Player)
	{
	    if (gPlayerInGuerra(gPlayer) && !GetPVarInt(gPlayer, "varDead") && GetPlayerInterior(gPlayer) == 0 && !Staff_GetWorking(gPlayer)) {

			new playerOrg = GetPlayerOrg(gPlayer),
				areaMorro = playerAreaMorro[gPlayer];

			if (OrgMorro(playerOrg)) {
				if(IsACop(gPlayer) && OnDuty[gPlayer] == 0)
					return;

			    MorroPontos[areaMorro][playerOrg] ++;

			    if(MorroPontos[areaMorro][playerOrg] > GuerraMorro[areaMorro][gPontosDono]){

					if(GuerraMorro[areaMorro][gDono] != playerOrg){

			     		format(gStr, 128, "Guerra do Morro: {F0EDED}%s assumiu a liderança da parte %d com {00BFFF}%d {F0EDED}pontos.", GetOrgName(playerOrg), areaMorro+1, MorroPontos[areaMorro][playerOrg]);
						gSendMessage(0x00AA00FF, gStr);

      					SendMembersMessage(playerOrg, COLOR_LIGHTBLUE, "**!** A sua organização está na liderança de uma das partes do morro.");
					}

		     		GuerraMorro[areaMorro][gPontosDono] = MorroPontos[areaMorro][playerOrg];
		     		GuerraMorro[areaMorro][gDono]       = playerOrg;
		     		GuerraMorro[areaMorro][gColor]      = GetPlayerColor(gPlayer)+75;
				}
			}

			if(!GetPVarInt(gPlayer, "AimingWithSniper")) {
				for(new textGMorro; textGMorro != sizeof guerraMorroTextDraw; textGMorro++) {
					TextDrawShowForPlayer(gPlayer, guerraMorroTextDraw[textGMorro]);
				}
			}
	    }
	    else
		{
            for(new textGMorro; textGMorro != sizeof guerraMorroTextDraw; textGMorro++) {
	    		TextDrawHideForPlayer(gPlayer, guerraMorroTextDraw[textGMorro]);
			}
	    }
	}
	
	gStr[0] = EOS;

	format(gTempoDinheiro, sizeof gTempoDinheiro, "Dinheiro ~g~$%s~n~~w~Tempo~p~ %03d", getFormatText(gDinheiro), gTempoMorro);

	format(gStr, sizeof gStr, "%s~n~ ~n~ ~n~%s~n~ ~n~ ~n~%s",
	GetOrgName(GuerraMorro[0][gDono]), GetOrgName(GuerraMorro[1][gDono]), GetOrgName(GuerraMorro[2][gDono]));

	format(gPontos,sizeof gPontos, "%02d ~w~pontos ~n~ ~n~ ~n~%02d pontos ~n~ ~n~ ~n~%02d pontos",
	MorroPontos[0][GuerraMorro[0][gDono]], MorroPontos[1][GuerraMorro[1][gDono]], MorroPontos[2][GuerraMorro[2][gDono]]);

    TextDrawSetString(guerraMorroTextDraw[5], gStr);
	TextDrawSetString(guerraMorroTextDraw[7], gPontos);
	TextDrawSetString(guerraMorroTextDraw[8], gTempoDinheiro);

	if (gTempoMorro < 1) gTerminarGuerraMorro();
}

CMD:guerramorro(playerid)
{
	if (Admin_GetNivel(playerid) < SUPERVISOR) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!gGuerraMorro) gIniciarGuerraMorro();
	else gTerminarGuerraMorro();

	return true;
}

CMD:horariosguerra(playerid)
{
 	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ",
	"\n{FF5500}A GUERRA NO MORRO ACONTECE AUTOMATICAMENTE NOS HORARIOS:{FFFFFF}\n\
	\n » 09:30:00\
	\n » 13:10:00\
    \n » 15:30:00\
    \n » 18:10:00\
    \n » 21:10:00", "Informado", "");

	return 1;
}