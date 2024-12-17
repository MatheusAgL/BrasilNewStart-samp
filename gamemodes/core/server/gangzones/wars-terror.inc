/**--------------------------------------------------------------------------**\
 ______ ______  ______     __  ______  ______  ______     ______  __  ______ __  __
/\  == /\  == \/\  __ \   /\ \/\  ___\/\  ___\/\__  _\   /\  ___\/\ \/\__  _/\ \_\ \
\ \  _-\ \  __<\ \ \/\ \ _\_\ \ \  __\\ \ \___\/_/\ \/   \ \ \___\ \ \/_/\ \\ \____ \
 \ \_\  \ \_\ \_\ \_____/\_____\ \_____\ \_____\ \ \_\    \ \_____\ \_\ \ \_\\/\_____\
  \/_/   \/_/ /_/\/_____\/_____/\/_____/\/_____/  \/_/     \/_____/\/_/  \/_/ \/_____/

						 ==========================
		                    Brasil Play Start
                              ® 2012 - 2016
                             Módulo: Novo sistema de guerra
						 ==========================

\**--------------------------------------------------------------------------**/

#include < YSI_Coding\y_hooks >

#define WAR_AREA_SIZE     		  300.0
#define WAR_KILL_POINTS   		  1500
#define WAR_DEATH_POINTS  		  1000
#define WAR_AIRDROP_POINTS  	  7500
#define WAR_VEHICLE_DEATH_POINTS  500
#define WAR_DISCONNECT_POINTS  	  400

/*
Pontos por kill: +1500
Pontos perdidos ao morrer dentro da guerra: -1000
Pontos perdidos por veiculo de guerra destruido na guerra: -500
Pontos perdidos ao desconectar dentro da guerra: -400
Pontos ganhos ao pegar o AirDrop: +7500
A cada segundo a org ganha +5 pontos por cada membro dentro da guerra
*/



new
	bool:orgWarTerror,
	orgWarCreated[MAX_ORGS]
;

enum guerra_ENUM {

	warCreated,
	warTime,
	warTimer,
	warTimeAirdrop,
	Float: warPosX,
	Float: warPosY,
	warGrana,
	warColor,
	warGz,
	warArea,
}
stock warInfo[guerra_ENUM];

// Orgs q participam da guerra
stock const warValidOrgs[] = {3, 15, 20, 23};

// Org pontos
stock warOrgPoints[MAX_ORGS] = {0, ...};

// Org kills
stock warOrgKills[MAX_ORGS] = {0, ...};

// Org deaths
stock warOrgDeaths[MAX_ORGS] = {0, ...};

// Org deaths vehicles
stock warOrgVDeaths[MAX_ORGS] = {0, ...};

// Textdraws
stock Text:textWar[12];

// Armas airdrop
stock warAirdrop[2] = {-1, ...};


hook OnPlayerLogin(playerid) 
{
	if (warIsCreated()) {
		GangZoneShowForPlayer(playerid, warInfo[warGz], warInfo[warColor]);
		GangZoneFlashForPlayer(playerid, warInfo[warGz], warInfo[warColor] - 0x30);
	}
}

hook OnPlayerLeaveDynamicArea(playerid, areaid)
{
	if (areaid == warInfo[warArea]) 
	{
		if (warIsOrgParticipe(GetPlayerOrg(playerid))) {
		    new string[75];

		    SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você saiu da zona de guerra.");
			format(string, sizeof string, "| GUERRA | %s saiu da zona de guerra", PlayerName[playerid]);
			warSendMessage(string, GetPlayerColor(playerid));
		}
	}
	return 1;
}

hook OnPlayerEnterDynamicArea(playerid, areaid) 
{
	if (areaid == warInfo[warArea])
	{
		if (warIsOrgParticipe(GetPlayerOrg(playerid))) {

			new string[75];

			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você entrou na zona de guerra.");
			format(string, sizeof string, "| GUERRA | %s entrou na zona de guerra", PlayerName[playerid]);
			warSendMessage(string, GetPlayerColor(playerid));
		}
	}
	return 1;
}

// Stocks
stock warCreate(playerid, Float:x, Float:y, Float:z, time)
{
	#pragma unused z
	
	if (warInfo[warCreated]) return false;
	
	// Reset things
	warInfo[warCreated] = 1;
	warInfo[warTime] = time;
	warInfo[warTimeAirdrop] = 15 * 60;
	warInfo[warGrana] = 500;
	warInfo[warColor] = GetPlayerColor(playerid) + 0x10;
	warInfo[warPosX] = x;
	warInfo[warPosY] = y;
	
	orgWarTerror = true;
	
	// Reset orgs points
	for(new index; index < sizeof warOrgPoints; index++)
	{
	    warOrgPoints[index] = 0;
	    warOrgKills[index] = 0;
	    warOrgDeaths[index] = 0;
	    warOrgVDeaths[index] = 0;
	}
	
	new string[128];
	
	// Mensagens
	SendClientMessageToAll(GetPlayerColor(playerid), "|__________________________________________________________________________________________________________|");
	format(string, sizeof string, "| GUERRA | %s e %s %s iniciaram uma guerra, não se aproxime da área marcada no mapa", PlayerName[playerid], GetOrgArticle(GetPlayerOrg(playerid)), GetOrgName(GetPlayerOrg(playerid)));
    SendClientMessageToAll(GetPlayerColor(playerid), string);
	format(string, sizeof string, "| GUERRA | A duração da guerra vai ser de %s", ConvertTime(time));
    SendClientMessageToAll(GetPlayerColor(playerid), string);
	SendClientMessageToAll(GetPlayerColor(playerid), "|__________________________________________________________________________________________________________|");
	
	// Create areas
	warInfo[warGz] = GangZoneCreate(x-WAR_AREA_SIZE, y-WAR_AREA_SIZE, x+WAR_AREA_SIZE, y+WAR_AREA_SIZE);
	warInfo[warArea] = CreateDynamicRectangle(x-WAR_AREA_SIZE, y-WAR_AREA_SIZE, x+WAR_AREA_SIZE, y+WAR_AREA_SIZE);
	
	GangZoneShowForAll(warInfo[warGz], warInfo[warColor]);
	GangZoneFlashForAll(warInfo[warGz], warInfo[warColor] - 0x30);
	
	DestroyDynamicObject(warAirdrop[0]);
	DestroyDynamicPickup(warAirdrop[1]);
	
	warAirdrop[0] = -1;
	warAirdrop[1] = -1;
	
	// Set timer
	warInfo[warTimer] = SetTimer("warServerUpdate", 1000, true);
	
	return 1;
}

stock warDestroy() {

	// Kill timer
	KillTimer(warInfo[warTimer]);
	
	// Destroy areas
	DestroyDynamicArea(warInfo[warArea]);
	GangZoneDestroy(warInfo[warGz]);
	
	// Esconder textdraws para todos
	for(new index; index < sizeof textWar; index++) {
	    TextDrawHideForAll(textWar[index]);
	}
	
	warInfo[warCreated] = 0;
	
	DestroyDynamicObject(warAirdrop[0]);
	DestroyDynamicPickup(warAirdrop[1]);

	warAirdrop[0] = -1;
	warAirdrop[1] = -1;
	
	// Pegar o vencedor
	new
	    orgWinner = warGetWinner();
	    
	if (orgWinner != -1) {
	
	    new string[256];
	
		SendClientMessageToAll(-1, "|__________________________________________________________________________________________________________|");
		format(string, sizeof string, "| GUERRA | A guerra chega ao fim tendo como vencedora a organização: {00FFFF}%s {FFFFFF}com {FFAA00}%d {FFFFFF}pontos.", GetOrgName(orgWinner), warOrgPoints[orgWinner]);
	    SendClientMessageToAll(-1, string);
        format(string, sizeof string, "| GUERRA | Prêmio: {00AA00}$%s {FFFFFF}e cada membro ganhou: {00FFFF}Caixa Surpresa Gigante", getFormatText(warInfo[warGrana]));
        SendClientMessageToAll(-1, string);

		// Dar premios
		OrgInfo_SetMoney(orgWinner, OrgInfo_GetMoney(orgWinner) + warInfo[warGrana]);
	 	
		foreach(new i : Player)
		{
			if(GetPlayerOrg(i) == orgWinner){
				// 5% de chance de ganhar caixa Gold
				new rand_caixa = random(100);
				if(rand_caixa >= 20 && rand_caixa < 25) {
					format(string, 256, "%s recebeu uma Caixa Surpresa GOLD como prêmio pela vitória na guerra", PlayerName[i]);
					SendClientMessageToAll(0xFEE73AFF, string);
					GiftBox_Give(i, ITEM_TYPE_CAIXAGOLD, false);
				}
				else {
					GiftBox_Give(i, ITEM_TYPE_CAIXAGIGANTE, false);
				}
		    }
		}

		SendClientMessageToAll(-1, "|__________________________________________________________________________________________________________|");
		
		// Mostrar resultado pra todos
		for(new index; index < sizeof textWar; index++) {
		    TextDrawShowForAll(textWar[index]);
		}
		SetTimer("hideWarTextdraws", 7000, false);
	} else {
		SendClientMessageToAll(-1, "|__________________________________________________________________________________________________________|");
        SendClientMessageToAll(-1, "| GUERRA | A guerra terminou sem nenhuma org vencedora");
		SendClientMessageToAll(-1, "|__________________________________________________________________________________________________________|");

	}
}

CALLBACK: hideWarTextdraws() {
	for(new index; index < sizeof textWar; index++) {
	    TextDrawHideForAll(textWar[index]);
	}
}

stock warShowPlayerTextdraws(playerid) {
	for(new index; index < sizeof textWar; index++) {
	    TextDrawShowForPlayer(playerid, textWar[index]);
	}
}

stock warHidePlayerTextdraws(playerid) {
	for(new index; index < sizeof textWar; index++) {
	    TextDrawHideForPlayer(playerid, textWar[index]);
	}
}

stock warIsOrgParticipe(orgid) {

	for(new index; index < sizeof warValidOrgs; index++) {
	    if (warValidOrgs[index] == orgid) return 1;
	}
	return 0;
}

stock warIsCreated() return warInfo[warCreated];

stock warIsPlayerIn(playerid) {

	if (!warInfo[warCreated])
	    return 0;

	static
	    Float:x, Float:y, Float:z;
	    
	GetPlayerPos(playerid, x, y, z);

	return IsPointInDynamicArea(warInfo[warArea], x, y, z);
}

stock warGetWinner() {

	new winnerpoints = 1, winner = -1;
	
	for(new index; index < sizeof warOrgPoints; index++) {

		if (warOrgPoints[index] > winnerpoints) {
		    winnerpoints = warOrgPoints[index];
		    winner = index;
		}
	}
	return winner;
}

stock warGetTotalPoints() {
	return (warOrgPoints[3] + warOrgPoints[15] + warOrgPoints[20] + warOrgPoints[23] + warOrgPoints[29]);
}

stock warSendMessage(const message[], color = 0xFFFFFFFF) {

    foreach(new playerid : Player) {
		if (warIsOrgParticipe(GetPlayerOrg(playerid))) {
			SendClientMessage(playerid, color, message);
		}
    }
}

stock warCheckDeath(playerid) {

	if (!warInfo[warCreated])
	    return 0;

   	if (!warIsPlayerIn(playerid))
	    return 0;

	static
	    playerOrg;

	// Get a players org
	playerOrg = GetPlayerOrg(playerid);

	if (!warIsOrgParticipe(playerOrg))
	    return 0;

	// Give org points
	warOrgDeaths[playerOrg] ++;
    warOrgPoints[playerOrg] -= WAR_DEATH_POINTS;

	if (warOrgPoints[playerOrg] < 0) {
	    warOrgPoints[playerOrg] = 0;
	}
	
	return 1;
}

stock warCheckKill(playerid, killerid) {

	if (killerid == INVALID_PLAYER_ID)
	    return 0;

	if (!warInfo[warCreated])
	    return 0;

	static
	    playerOrg,
	    killerOrg;
	    
	// Get a players org
	playerOrg = GetPlayerOrg(playerid);
	killerOrg = GetPlayerOrg(killerid);
	    
	if (playerOrg == killerOrg)
	    return 0;
	    
	if (!warIsPlayerIn(killerid))
	    return 0;
	    
	if (!warIsOrgParticipe(playerOrg) or !warIsOrgParticipe(killerOrg))
	    return 0;
	    
    warInfo[warGrana] += 20 + random(30);
	    
	// Give org points
	warOrgKills[killerOrg] ++;
	warOrgDeaths[playerOrg] ++;
	    
    warOrgPoints[killerOrg] += WAR_KILL_POINTS;
    warOrgPoints[playerOrg] -= WAR_DEATH_POINTS;
	    
	if (warOrgPoints[playerOrg] < 0) {
	    warOrgPoints[playerOrg] = 0;
	}
	    
	return 1;
}

CALLBACK: warServerUpdate() {

	if (!warInfo[warCreated])
	    return 0;

    warInfo[warTime] --;

    if (warInfo[warTime] > 0) {

        new string[144];

        format(string, sizeof string, "tempo restante: %s~n~total pontos: %d", ConvertTime(warInfo[warTime]), warGetTotalPoints());
        TextDrawSetString(textWar[2], string);

        // Update K/D das orgs
        format(string, sizeof string, "K: %d  D: %d  VD: %d~n~~n~~n~K: %d  D: %d  VD: %d~n~~n~~n~K: %d  D: %d  VD: %d",
		warOrgKills[3], warOrgDeaths[3], warOrgVDeaths[3],
		warOrgKills[15], warOrgDeaths[15], warOrgVDeaths[15],
		warOrgKills[20], warOrgDeaths[20], warOrgVDeaths[20]);
        TextDrawSetString(textWar[10], string);

        // Update points
        format(string, sizeof string, "%d~n~~n~~n~%d~n~~n~~n~%d~n~",
		warOrgPoints[3], warOrgPoints[15], warOrgPoints[20]);
        TextDrawSetString(textWar[11], string);

        // Update progressbar
        static
            Float:totalpoints,
            Float:orgpoints;

		totalpoints = warGetTotalPoints();

		// Não bugar a barra
		if (totalpoints < 1.0) {
		    totalpoints = 1.0000;
		}

		// Exercito
		orgpoints = warOrgPoints[3];
        TextDrawTextSize(textWar[7], ((23.0 - 6.0) + (((76.0 + 6.0) - 23.0) * orgpoints) / totalpoints), 0.000000);

		// Estado Islamico
		orgpoints = warOrgPoints[15];
        TextDrawTextSize(textWar[8], ((23.0 - 6.0) + (((76.0 + 6.0) - 23.0) * orgpoints) / totalpoints), 0.000000);

		// Al-Qaeda
		orgpoints = warOrgPoints[20];
        TextDrawTextSize(textWar[9], ((23.0 - 6.0) + (((76.0 + 6.0) - 23.0) * orgpoints) / totalpoints), 0.000000);

        // Mostrar textdraws para membros da guerra
        foreach(new playerid : Player) {

			static
			    playerOrg;

			playerOrg = GetPlayerOrg(playerid);

			if (warIsOrgParticipe(playerOrg)) {

				// Mostrar textdraws guerra
				warShowPlayerTextdraws(playerid);

				// Se tiver na guerra, dar pontos
				if (warIsPlayerIn(playerid)) {
				    warOrgPoints[playerOrg] += 2;
				}
			} else {
				// Esconder textdraws guerra
				warHidePlayerTextdraws(playerid);
			}
        }

        // Airdrop

        warInfo[warTimeAirdrop] --;

        if (warInfo[warTimeAirdrop] < 1) {

			DestroyDynamicObject(warAirdrop[0]);
			DestroyDynamicPickup(warAirdrop[1]);

			warAirdrop[0] = -1;
			warAirdrop[1] = -1;

            warInfo[warTimeAirdrop] = 15 * 60;

            // Criar drop
            static
                Float:x, Float:y, Float:z;

			x = (warInfo[warPosX] + (randomfloat(WAR_AREA_SIZE) - randomfloat(WAR_AREA_SIZE)));
			y = (warInfo[warPosY] + (randomfloat(WAR_AREA_SIZE) - randomfloat(WAR_AREA_SIZE)));

			MapAndreas_FindZ_For2DCoord(x, y, z);

			warAirdrop[0] = CreateDynamicObject(2903, x, y, z + 300.0, 0.0, 0.0, 0.0, -1, -1, -1, 800.0, 800.0);
			MoveDynamicObject(warAirdrop[0], x, y, z + 7.0, 1.9, 0.0, 0.0, 0.0);

			warSendMessage("| {FF0000}AIRDROP{FFFFFF} | Um airdrop foi lançado na zona de guerra, em breve chegará ao solo.");
        }
    } else {
        warDestroy();
    }
    return 1;
}

hook OnDynamicObjectMoved(objectid) {

	if (warAirdrop[0] == objectid) {
	
	    if (warInfo[warCreated]) {
	    
	        static
	            Float:x, Float:y, Float:z;

			GetDynamicObjectPos(objectid, x, y, z);
	            
            MapAndreas_FindZ_For2DCoord(x, y, z);
            
            z = z + 1.0;
            
            warAirdrop[1] = CreateDynamicPickup(1271, 24, x, y, z);
            
			warSendMessage("| {FF0000}AIRDROP{FFFFFF} | O airdrop chegou ao solo, nele contém pontos e armas poderosas.");
	    }
	
	    warAirdrop[0] = -1;
	
	    DestroyDynamicObject(objectid);
	    
	}
	return 1;
}

stock waOnPlayerPickUpDynamicPickup(playerid, pickupid) {

	if (warAirdrop[1] == pickupid) {

		new
		    playerOrg = GetPlayerOrg(playerid);

		if (warInfo[warCreated] && warIsOrgParticipe(playerOrg)) {
		
		    new string[128];
		    
		    format(string, sizeof string, "| {FF0000}AIRDROP{%06x} | %s pegou o airdrop, o mesmo ganhou armas e %d pontos para a organização.", GetPlayerColor(playerid) >>> 8, PlayerName[playerid], WAR_AIRDROP_POINTS);
		    warSendMessage(string, GetPlayerColor(playerid));
		
		    warOrgPoints[playerOrg] += WAR_AIRDROP_POINTS;
			GivePlayerWeapon(playerid, WEAPON_HEATSEEKER, 15);
			DestroyDynamicPickup(pickupid);
			warAirdrop[1] = -1;
		}
	}
	return 1;
}

CMD:guerra(playerid, params[])
{
    if (warInfo[warCreated]) return SendClientMessage(playerid, -1, "Está ocorrendo uma guerra no momento.");
    
    if (orgWarCreated[GetPlayerOrg(playerid)] > 0) return SendClientMessage(playerid, -1, "Sua organização precisa aguardar 2 paydays para criar outra guerra.");

	if (orgWarTerror == true) return SendClientMessage(playerid, -1, "Uma guerra foi finalizada nesse payday, aguarde o próximo.");

	static Float:x, Float:y, Float:z, time;
	    
	if (sscanf(params, "d", time)) return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /guerra [minutos (30 - 40)]");
	    
    if (time < 30 || time > 40) return SendClientMessage(playerid, -1, "Minutos de 30 - 40");

	if (!warIsOrgParticipe(GetPlayerOrg(playerid))) return SendClientMessage(playerid, -1, "Você não pode criar uma guerra!");
	    
	GetPlayerPos(playerid, x, y, z);
	
	warCreate(playerid, x, y, z, (time * 60));
	
	orgWarCreated[GetPlayerOrg(playerid)] = 2;

	return true;
}

CMD:terminarguerra(playerid, result[])
{
	if(Admin_GetNivel(playerid) < ADMINISTRADOR) {
	    return SendClientMessage(playerid, -1, "Você não é um Admin!");
	}

	if(isnull(result)) {
		return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /terminarguerra [motivo]");
	}

    new string[144];

	format(string, sizeof(string), "AdmCmd: O admin %s terminou a guerra, motivo: %s", PlayerName[playerid], result);
	SendClientMessageToAll(COLOR_LIGHTRED, string);
		
	// Reset orgs points
	for(new index; index < sizeof warOrgPoints; index++) {
	    warOrgPoints[index] = 0;
	    warOrgKills[index] = 0;
	    warOrgDeaths[index] = 0;
	    warOrgVDeaths[index] = 0;
	}
		
	warDestroy();
		
	return 1;
}

hook OnVehicleDeath(vehicleid, killerid)
{
	static
	    Float:x, Float:y, Float:z;
	    
	GetVehiclePos(vehicleid, x, y, z);

	switch (GetVehicleModel(vehicleid))
	{
	    case 520, 476, 432, 417, 425, 548, 563:
		{
	        new playerid = GetVehicleLastDriverId(vehicleid);
	    
	        if (IsPlayerConnected(playerid) && warInfo[warCreated]) {
	        
				static
				    playerOrg;

				playerOrg = GetPlayerOrg(playerid);

				if (warIsOrgParticipe(playerOrg) && IsPointInDynamicArea(warInfo[warArea], x, y, z)) {

                    warOrgVDeaths[playerOrg] ++;

					warOrgPoints[playerOrg] -= WAR_VEHICLE_DEATH_POINTS;
					
					if (warOrgPoints[playerOrg] < 0) {
					    warOrgPoints[playerOrg] = 0;
					}
					
					new string[128];

					new vehicle_name[30];
					GetModelStaticNameFromId(GetVehicleModel(vehicleid), vehicle_name);

					format(string, sizeof string, "| GUERRA | O veículo %s da org %s foi explodido na zona de guerra, a org perdeu %d pontos.", vehicle_name, GetOrgName(playerOrg), WAR_VEHICLE_DEATH_POINTS);
					warSendMessage(string, GetPlayerColor(playerid));
				}
	        }
	    }
	}

	return 1;
}

hook OnPlayerDisconnect(playerid, reason) 
{
	static
	    playerOrg;

	playerOrg = GetPlayerOrg(playerid);

	if (warIsOrgParticipe(playerOrg) && warIsPlayerIn(playerid)) {

		warOrgPoints[playerOrg] -= WAR_DISCONNECT_POINTS;

		if (warOrgPoints[playerOrg] < 0) {
		    warOrgPoints[playerOrg] = 0;
		}
		
		new string[128];

		format(string, sizeof string, "| GUERRA | %s desconectou dentro da zona de guerra, a org perdeu %d pontos.", PlayerName[playerid], WAR_DISCONNECT_POINTS);
		warSendMessage(string, GetPlayerColor(playerid));
		print(string);
		
	}

	return 1;
}

stock warCreateTextdraws() {
	textWar[0] = TextDrawCreate(4.000000, 180.000000, "usebox");
	TextDrawBackgroundColor(textWar[0], 0);
	TextDrawFont(textWar[0], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textWar[0], 0.500000, 13.000000);
	TextDrawColor(textWar[0], 0);
	TextDrawSetOutline(textWar[0], 0);
	TextDrawSetProportional(textWar[0], true);
	TextDrawSetShadow(textWar[0], 1);
	TextDrawUseBox(textWar[0], true);
	TextDrawBoxColor(textWar[0], 336860260);
	TextDrawTextSize(textWar[0], 81.000000, 0.000000);
	TextDrawSetSelectable(textWar[0], false);

	textWar[1] = TextDrawCreate(18.000000, 176.000000, "Guerra");
	TextDrawBackgroundColor(textWar[1], 0);
	TextDrawFont(textWar[1], TEXT_DRAW_FONT_0);
	TextDrawLetterSize(textWar[1], 0.599999, 1.600000);
	TextDrawColor(textWar[1], -236);
	TextDrawSetOutline(textWar[1], 0);
	TextDrawSetProportional(textWar[1], true);
	TextDrawSetShadow(textWar[1], 1);
	TextDrawSetSelectable(textWar[1], false);

	textWar[2] = TextDrawCreate(3.000000, 193.000000, "tempo restante: 25:47~n~total grana: $59.574");
	TextDrawBackgroundColor(textWar[2], 0);
	TextDrawFont(textWar[2], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(textWar[2], 0.160000, 0.899999);
	TextDrawColor(textWar[2], -1258291406);
	TextDrawSetOutline(textWar[2], 0);
	TextDrawSetProportional(textWar[2], true);
	TextDrawSetShadow(textWar[2], 1);
	TextDrawSetSelectable(textWar[2], false);

	textWar[3] = TextDrawCreate(3.000000, 214.000000, "EXE~n~~n~~n~FAR~n~~n~~n~ALQ");
	TextDrawBackgroundColor(textWar[3], 0);
	TextDrawFont(textWar[3], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textWar[3], 0.230000, 0.799999);
	TextDrawColor(textWar[3], -1);
	TextDrawSetOutline(textWar[3], 0);
	TextDrawSetProportional(textWar[3], true);
	TextDrawSetShadow(textWar[3], 1);
	TextDrawSetSelectable(textWar[3], false);

	textWar[4] = TextDrawCreate(23.000000, 217.000000, "barra");
	TextDrawBackgroundColor(textWar[4], 0);
	TextDrawFont(textWar[4], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textWar[4], 0.500000, 0.300000);
	TextDrawColor(textWar[4], 0);
	TextDrawSetOutline(textWar[4], 0);
	TextDrawSetProportional(textWar[4], true);
	TextDrawSetShadow(textWar[4], 1);
	TextDrawUseBox(textWar[4], true);
	TextDrawBoxColor(textWar[4], 50);
	TextDrawTextSize(textWar[4], 76.000000, 0.000000);
	TextDrawSetSelectable(textWar[4], false);

	textWar[5] = TextDrawCreate(23.000000, 238.000000, "barra");
	TextDrawBackgroundColor(textWar[5], 0);
	TextDrawFont(textWar[5], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textWar[5], 0.500000, 0.300000);
	TextDrawColor(textWar[5], 0);
	TextDrawSetOutline(textWar[5], 0);
	TextDrawSetProportional(textWar[5], true);
	TextDrawSetShadow(textWar[5], 1);
	TextDrawUseBox(textWar[5], true);
	TextDrawBoxColor(textWar[5], 50);
	TextDrawTextSize(textWar[5], 76.000000, 0.000000);
	TextDrawSetSelectable(textWar[5], false);

	textWar[6] = TextDrawCreate(23.000000, 260.000000, "barra");
	TextDrawBackgroundColor(textWar[6], 0);
	TextDrawFont(textWar[6], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textWar[6], 0.500000, 0.300000);
	TextDrawColor(textWar[6], 0);
	TextDrawSetOutline(textWar[6], 0);
	TextDrawSetProportional(textWar[6], true);
	TextDrawSetShadow(textWar[6], 1);
	TextDrawUseBox(textWar[6], true);
	TextDrawBoxColor(textWar[6], 50);
	TextDrawTextSize(textWar[6], 76.000000, 0.000000);
	TextDrawSetSelectable(textWar[6], false);

	textWar[7] = TextDrawCreate(23.000000, 217.000000, "progress");
	TextDrawBackgroundColor(textWar[7], 0);
	TextDrawFont(textWar[7], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textWar[7], 0.500000, 0.300000);
	TextDrawColor(textWar[7], 0);
	TextDrawSetOutline(textWar[7], 0);
	TextDrawSetProportional(textWar[7], true);
	TextDrawSetShadow(textWar[7], 1);
	TextDrawUseBox(textWar[7], true);
	TextDrawBoxColor(textWar[7], -156);
	TextDrawTextSize(textWar[7], 36.000000, 0.000000);
	TextDrawSetSelectable(textWar[7], false);

	textWar[8] = TextDrawCreate(23.000000, 238.000000, "progress");
	TextDrawBackgroundColor(textWar[8], 0);
	TextDrawFont(textWar[8], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textWar[8], 0.500000, 0.300000);
	TextDrawColor(textWar[8], 0);
	TextDrawSetOutline(textWar[8], 0);
	TextDrawSetProportional(textWar[8], true);
	TextDrawSetShadow(textWar[8], 1);
	TextDrawUseBox(textWar[8], true);
	TextDrawBoxColor(textWar[8], -156);
	TextDrawTextSize(textWar[8], 26.000000, 0.000000);
	TextDrawSetSelectable(textWar[8], false);

	textWar[9] = TextDrawCreate(23.000000, 260.000000, "progress");
	TextDrawBackgroundColor(textWar[9], 0);
	TextDrawFont(textWar[9], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textWar[9], 0.500000, 0.300000);
	TextDrawColor(textWar[9], 0);
	TextDrawSetOutline(textWar[9], 0);
	TextDrawSetProportional(textWar[9], true);
	TextDrawSetShadow(textWar[9], 1);
	TextDrawUseBox(textWar[9], true);
	TextDrawBoxColor(textWar[9], -156);
	TextDrawTextSize(textWar[9], 54.000000, 0.000000);
	TextDrawSetSelectable(textWar[9], false);

	textWar[10] = TextDrawCreate(20.000000, 222.000000, "K: 0   D: 0~n~~n~~n~K: 0   D: 0~n~~n~~n~K: 0   D: 0");
	TextDrawBackgroundColor(textWar[10], 0);
	TextDrawFont(textWar[10], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(textWar[10], 0.170000, 0.799999);
	TextDrawColor(textWar[10], -206);
	TextDrawSetOutline(textWar[10], 0);
	TextDrawSetProportional(textWar[10], true);
	TextDrawSetShadow(textWar[10], 1);
	TextDrawSetSelectable(textWar[10], false);

	textWar[11] = TextDrawCreate(75.000000, 214.000000, "0000~n~~n~~n~0000~n~~n~~n~0000~n~");
	TextDrawAlignment(textWar[11], TEXT_DRAW_ALIGN_RIGHT);
	TextDrawBackgroundColor(textWar[11], 0);
	TextDrawFont(textWar[11], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(textWar[11], 0.150000, 0.799999);
	TextDrawColor(textWar[11], -922747086);
	TextDrawSetOutline(textWar[11], 0);
	TextDrawSetProportional(textWar[11], true);
	TextDrawSetShadow(textWar[11], 1);
	TextDrawSetSelectable(textWar[11], false);
}





