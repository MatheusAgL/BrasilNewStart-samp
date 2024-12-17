#include <YSI_Coding\y_hooks>

#define ID_MENU_VEHICLES_FIREFIGHTER 4
#define MAX_FIRE_EVENTS 15

static string[256];

static Firefighter_Category[][enumMenuCategory] = 
{
    { 1, "Firetruck", 10, 0 },
	{ 2, "Firetruck LA", 10, 0 }
};

static FirefighterVehicle[20][tempVehicleEnum];

static Iterator:iterFireEvents<MAX_FIRE_EVENTS>;

//Textdraws
new Text:iconSkull, 
	Text:redBackground, 
	Text:textFire, 
	Text:textWarning;

enum feInfo
{
	Float:feTotal,
	Float:feExtinguished,
 	Float:feBaseX,
 	Float:feBaseY,
	Float:feBaseZ,
};
static FireEventInfo[MAX_FIRES][feInfo];

static OptionsInfo[MAX_PLAYERS][50];

stock CreateFireAlertTextdraws() {
	redBackground = TextDrawCreate(324.000000, -1.000000, "_");
	TextDrawFont(redBackground, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(redBackground, 0.600000, 49.999984);
	TextDrawTextSize(redBackground, 298.500000, 653.000000);
	TextDrawSetOutline(redBackground, 1);
	TextDrawSetShadow(redBackground, 0);
	TextDrawAlignment(redBackground, TEXT_DRAW_ALIGN_CENTER);
	TextDrawColor(redBackground, -1);
	TextDrawBackgroundColor(redBackground, 255);
	TextDrawBoxColor(redBackground, 1157628104);
	TextDrawUseBox(redBackground, true);
	TextDrawSetProportional(redBackground, true);
	TextDrawSetSelectable(redBackground, false);

	iconSkull = TextDrawCreate(306.000000, 85.000000, "HUD:radar_locosyndicate");
	TextDrawFont(iconSkull, TEXT_DRAW_FONT_SPRITE_DRAW);
	TextDrawLetterSize(iconSkull, 0.600000, 2.000000);
	TextDrawTextSize(iconSkull, 31.000000, 34.500000);
	TextDrawSetOutline(iconSkull, 1);
	TextDrawSetShadow(iconSkull, 0);
	TextDrawAlignment(iconSkull, TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(iconSkull, -1);
	TextDrawBackgroundColor(iconSkull, 255);
	TextDrawBoxColor(iconSkull, 50);
	TextDrawUseBox(iconSkull, true);
	TextDrawSetProportional(iconSkull, true);
	TextDrawSetSelectable(iconSkull, false);

	textFire = TextDrawCreate(266.000000, 148.000000, "Area em Incendio");
	TextDrawFont(textFire, TEXT_DRAW_FONT_2);
	TextDrawLetterSize(textFire, 0.291666, 2.099998);
	TextDrawTextSize(textFire, 400.000000, 17.000000);
	TextDrawSetOutline(textFire, 1);
	TextDrawSetShadow(textFire, 1);
	TextDrawAlignment(textFire, TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(textFire, -16776961);
	TextDrawBackgroundColor(textFire, 255);
	TextDrawBoxColor(textFire, 50);
	TextDrawUseBox(textFire, false);
	TextDrawSetProportional(textFire, true);
	TextDrawSetSelectable(textFire, false);

	textWarning = TextDrawCreate(285.000000, 118.000000, "CUIDADO!");
	TextDrawFont(textWarning, TEXT_DRAW_FONT_2);
	TextDrawLetterSize(textWarning, 0.383332, 3.699997);
	TextDrawTextSize(textWarning, 400.000000, 17.000000);
	TextDrawSetOutline(textWarning, 0);
	TextDrawSetShadow(textWarning, 1);
	TextDrawAlignment(textWarning, TEXT_DRAW_ALIGN_LEFT);
	TextDrawColor(textWarning, -16776961);
	TextDrawBackgroundColor(textWarning, 255);
	TextDrawBoxColor(textWarning, 50);
	TextDrawUseBox(textWarning, false);
	TextDrawSetProportional(textWarning, true);
	TextDrawSetSelectable(textWarning, false);
}

hook OnGameModeInit()
{
    CreateDynamicPickup(1275, 23, 952.4030, -1748.9863, 13.9448); //Pegar farda
    CreateDynamic3DTextLabel("Vestiário do Corpo de Bombeiros\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para pegar a farda", 0xFFFFFFFF,952.4030, -1748.9863, 13.9448,13.0);

	CreateDynamicPickup(1025, 23, 952.9063,-1690.3560,13.5609); //Pegar veículo
    CreateDynamic3DTextLabel("Garagem do Corpo de Bombeiros\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para pegar um veículo", 0xFFFFFFFF,952.9063,-1690.3560,13.5609,13.0);

	CreateDynamicPickup(366, 23, 965.9519,-1760.2111,13.9448); //Extintor
    CreateDynamic3DTextLabel("Equipamentos do Corpo de Bombeiros\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para pegar seu extintor", 0xFFFFFFFF,965.9519,-1760.2111,13.9448,13.0);
	
	CreateFireAlertTextdraws();
	return 1;
}

CALLBACK:IsPlayerFirefighter(playerid)
{
	new empregoPlayer = PlayerInfo[playerid][pEmprego];
	new empregoPlayer2 = PlayerInfo[playerid][pEmprego2];
	return empregoPlayer == ID_JOB_FIREFIGHTER || empregoPlayer2 == ID_JOB_FIREFIGHTER;
}
 
hook DealWithPlayerInPosition(playerid) {
	if (PlayerToPoint(2.0, playerid, 952.4030, -1748.9863, 13.9448)) {
		if(IsPlayerFirefighter(playerid)) {
			if(EmpregoDuty[playerid] != 2) {
				ShowModelSelectionMenu(playerid, SkinsFirefighter, "Escolha seu uniforme", 200, 0x000000AA);
			}
			else {
				SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
				EmpregoDuty[playerid] = 0;
				SendMsgF(playerid, COLOR_LIGHTBLUE, "Você guardou sua farda e não está mais de serviço");
			}
		}
		else
			SendClientMessage(playerid, -1, "Você não é um bombeiro.");
	}
	else if(PlayerToPoint(2.0, playerid, 952.9063,-1690.3560,13.5609)) {
		if(IsPlayerFirefighter(playerid)) {
			TogglePlayerControllable(playerid, false);
			MenuInfo[playerid][menu_id] = ID_MENU_VEHICLES_FIREFIGHTER;
			OpenMenu(playerid, ID_MENU_VEHICLES_FIREFIGHTER);
		}
		else
			SendClientMessage(playerid, -1, "Você não é um bombeiro.");
	}
	else if(PlayerToPoint(2.0, playerid, 965.9519,-1760.2111,13.9448)) {
		if(IsPlayerFirefighter(playerid)) {
			GivePlayerWeapon(playerid, WEAPON_FIREEXTINGUISHER, 9999);
			PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
		}
		else
			SendClientMessage(playerid, -1, "Você não é um bombeiro.");
	}
}

hook OnPlayerModelSelection(playerid, response, listid, modelid) {
	if (listid == SkinsFirefighter) {
	    if (!response) 
			return SendClientMessage(playerid, -1, "Você cancelou o menu de uniformes.");

        PlayerInfo[playerid][pSkinServico] = modelid;
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkinServico]);

		format(string, sizeof string, "(( Bombeiros )) {FFFFFF}%s pegou seu uniforme e está em serviço.", PlayerName[playerid]);
		EmpregoMensagem(0xE0D78AFF, string, ID_JOB_FIREFIGHTER);

		EmpregoDuty[playerid] = 2;
	}
	return 1;
}

hook ChangeMenuTitle(playerid, menuid) {
	if(menuid == ID_MENU_VEHICLES_FIREFIGHTER) {
		PlayerTextDrawBoxColor(playerid, menu_ptextdraws[0][playerid], -1021765121);
		PlayerTextDrawColor(playerid, menu_ptextdraws[1][playerid], -1);
		PlayerTextDrawSetString(playerid, menu_ptextdraws[1][playerid], "Corpo de Bombeiros");
	}
}

hook MenuSetItens(playerid, menuid) {
	if(menuid == ID_MENU_VEHICLES_FIREFIGHTER) {
		MenuInfo[playerid][menu_max_itens] = sizeof(Firefighter_Category);

		for(new i; i < sizeof(Firefighter_Category); i++) {
			Menu_Category[playerid][i][category_id]                     = Firefighter_Category[i][category_id];
			format(Menu_Category[playerid][i][category_nome], 20,       Firefighter_Category[i][category_nome]);
			Menu_Category[playerid][i][category_quantidade]             = Firefighter_Category[i][category_quantidade];
			Menu_Category[playerid][i][category_position]               = Firefighter_Category[i][category_position];
		}
	}
}

hook OnVehicleDestroyed(vehicleid) {
	if(VehicleInfo[vehicleid][vhTemp]) {
		for(new i = 0; i < sizeof(FirefighterVehicle); i++) {
			if(FirefighterVehicle[i][tvVehicleID] == vehicleid) {
				new itemId = GetVehicleModel(vehicleid) == 407 ? 0 : 1;

				Firefighter_Category[itemId][category_quantidade] += 1;
				VehicleInfo[vehicleid][vhTemp] = 0;
				FirefighterVehicle[i][tvCreated] = 0;
				return 1;
			}	
		}
	}
	return 1;
}

hook OnPlayerConfirmMenu(playerid, menuid, pageid, itemid, selecteditem) {
	if(menuid == ID_MENU_VEHICLES_FIREFIGHTER) {
		if(Firefighter_Category[selecteditem][category_quantidade] <= 0) 
			return SendClientMessage(playerid, -1, "Não existem unidades desse veículo disponíveis para uso.");

		DestroyPlayerTempVehicle(playerid);

		//Firefighter_Category[selecteditem][category_quantidade] -= 1;

		new modelid = Firefighter_Category[selecteditem][category_id] == 1 ? 407 : 544,
			vehid = CreateVehicle(modelid, 948.2359, -1682.2914, 13.7972, 32.4491, -1, -1, -1);

		UnlockVehicleDoors(vehid);
		PutPlayerInVehicle(playerid, vehid, 0);
		SetPlayerTempVehicleID(playerid, vehid);
		VehicleInfo[vehid][vhTemp] = 1;

		for(new i = 0; i < sizeof(FirefighterVehicle); i++) {
			if(!FirefighterVehicle[i][tvCreated]) {
				FirefighterVehicle[i][tvCreated] = 1;
				FirefighterVehicle[i][tvVehicleID] = vehid;
				FirefighterVehicle[i][tvModelID] = modelid;
				FirefighterVehicle[i][tvPlayerID] = playerid;
				break;
			}
		}

		KickPlayerMenu(playerid);
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == 800) {
	    if (response && listitem >= 0) {
			new fireId = OptionsInfo[playerid][listitem];

			SetPlayerCheckpoint(playerid, FireEventInfo[fireId][feBaseX], FireEventInfo[fireId][feBaseY], FireEventInfo[fireId][feBaseZ], 15.0);
	    }
        return 1;
	}
	return 1;
}

stock FinishFireEvent(fireEventId) {
	Iter_Remove(iterFireEvents, fireEventId);
	foreach(new playerid : Player) {
		if(GetPVarInt(playerid, "ExtinguishingFireEvent") && GetPVarInt(playerid, "FireEventID") == fireEventId) {
			new salary = floatround((30+random(15)) * GetPVarFloat(playerid, "FireEventExtinguished"));
			SendMsgF(playerid, COLOR_LIGHTBLUE, "Você apagou o incêndio com sucesso e foi adicionado $%s ao seu salário", getFormatText(salary));

			PlayerPlaySound(playerid, 182, 0.0, 0.0, 0.0);
			PlayerInfo[playerid][pSalario] += salary + GetWageJob(ID_JOB_FIREFIGHTER);
			removerDinheiroGoverno(salary);

			SetPVarInt(playerid, "ExtinguishingFireEvent", 0);
			SetPVarInt(playerid, "FireEventExited", 0);
			SetPVarFloat(playerid, "FireEventExtinguished", 0);
			SetPVarInt(playerid, "FireEventID", 0);
			defer timerStopSound(playerid);
		}
	}
}

CALLBACK:UpdateFireEvent(playerid, fireEventId, Float:extinguished) {
	if(playerid != INVALID_PLAYER_ID) {
		SetPVarFloat(playerid, "FireEventExtinguished", GetPVarFloat(playerid, "FireEventExtinguished") + extinguished);
	}
	FireEventInfo[fireEventId][feExtinguished] += extinguished;

	if(FireEventInfo[fireEventId][feExtinguished] >= FireEventInfo[fireEventId][feTotal]) {
		FinishFireEvent(fireEventId);
	}
}

task SpawnFireEvents[10 * 60 * 1000]() {
	new index = random(1),
		Float:baseX, Float:baseY, Float:baseZ,
		Float:x, Float:y, Float:z,
		i = Iter_Free(iterFires);

	if(i == -1)
		return 0;
	
	// //Em casa
	// if(index == 0) {
	// 	new subIndex;
	// 	while((subIndex = random(MAX_HOUSES)) != -1) {
	// 		if(HouseInfo[subIndex][hCriada]) {
	// 			baseX = HouseInfo[subIndex][hEntradaX];
	// 			baseY = HouseInfo[subIndex][hEntradaY];
	// 			baseZ = HouseInfo[subIndex][hEntradaZ];
	// 			break;
	// 		}
	// 	}
	// }
	// //Em propriedade
	// else 
	if(index == 0) {
		new subIndex;
		while((subIndex = random(84)) != -1) {
			if(PropInfo[subIndex][eLoaded]) {
				baseX = GetPropEntranceX(subIndex);
				baseY = GetPropEntranceX(subIndex);
				baseZ = GetPropEntranceX(subIndex);
				break;
			}
		}
	}
	//Em local aleatório
	else if(index == 1) {

	}

	new amount = 10 + random(5);
	for(new fi = 0; fi < amount; fi++) {
		for(new p = 0; p < 10; p++) {
			x = baseX - 10.0 + random(200)/10.0;
			y = baseY - 10.0 + random(200)/10.0;

			MapAndreas_FindZ_For2DCoord(x, y, z);
			if(abs(baseZ - z) <= 17.0) 
				break;
		}
		new fireId = AddFire(x, y, z);

		if(fireId != -1) {
			fireinfo[fireId][fireEventID] = i;
		}
	}

	new MapZone:zone = GetMapZoneAtPoint2D(baseX, baseY),
		zone_name[MAX_MAP_ZONE_NAME];
	GetMapZoneName(zone, zone_name);

	format(string, sizeof string, "(( Bombeiros )) Uma ocorrência de incêndio foi registrada na região de %s.", zone_name);
	EmpregoMensagem(0xE0D78AFF, string, ID_JOB_FIREFIGHTER);

	FireEventInfo[i][feTotal] = amount * 100.00;
	FireEventInfo[i][feExtinguished] = 0.00;
	FireEventInfo[i][feBaseX] = baseX;
	FireEventInfo[i][feBaseY] = baseY;
	FireEventInfo[i][feBaseZ] = baseZ;

	CreateExplosion(baseX, baseY , baseZ + 3, 1, 10.0);

	Iter_Add(iterFireEvents, i);
	return 1;
}

task CheckPlayersInDangerousArea[5 * 1000]() {
	foreach(new x : iterFireEvents) {
		new Float:riskRange = 60.0 * (1.0 - (FireEventInfo[x][feExtinguished] / FireEventInfo[x][feTotal]));
		foreach(new playerid : Player) {

			if(GetPlayerDistanceFromPoint(playerid, FireEventInfo[x][feBaseX], FireEventInfo[x][feBaseY], FireEventInfo[x][feBaseZ]) > riskRange) {
				if(GetPVarInt(playerid, "PlayerOnFire")) {
					TextDrawHideForPlayer(playerid, redBackground);
					TextDrawHideForPlayer(playerid, iconSkull);
					TextDrawHideForPlayer(playerid, textFire);
					TextDrawHideForPlayer(playerid, textWarning);
					SetPVarInt(playerid, "PlayerOnFire", 0);
				}
				else if(GetPVarInt(playerid, "FireEventExited") > 0 && GetPVarInt(playerid, "FireEventExited") < gettime()) {
					SetPVarInt(playerid, "FireEventExited", 0);
					SetPVarFloat(playerid, "FireEventExtinguished", 0);
					SetPVarInt(playerid, "FireEventID", 0);
				}
				else if(GetPVarInt(playerid, "ExtinguishingFireEvent")) {
					SetPVarInt(playerid, "FireEventExited", gettime()+300);
				}
				continue;
			}

			if(IsPlayerFirefighter(playerid) && EmpregoDuty[playerid] == 2 && PlayerInfo[playerid][pSkinServico] >= 277 && PlayerInfo[playerid][pSkinServico] <= 279) {
				if(!GetPVarInt(playerid, "ExtinguishingFireEvent")) {
					SetPVarInt(playerid, "ExtinguishingFireEvent", 1);
					SetPVarInt(playerid, "FireEventID", x);
					SetPVarInt(playerid, "FireEventEntered", gettime());
					SetPVarFloat(playerid, "FireEventExtinguished", 0);
				}
				continue;
			}

			DamagePlayerByFire(playerid, 0, 16.0);
			SetPVarInt(playerid, "DrunkL", 1);
			SetPVarInt(playerid, "PlayerOnFire", 1);
			TextDrawShowForPlayer(playerid, redBackground);
			TextDrawShowForPlayer(playerid, iconSkull);
			TextDrawShowForPlayer(playerid, textFire);
			TextDrawShowForPlayer(playerid, textWarning);
		}
	}
}

stock ShowPlayerFireEvents(playerid)
{
	new fires;
	
	MEGAString [0] = EOS;
	strcat(MEGAString, "Localização\tDistância\tStatus (%)\n");

    new MapZone:zone,
		zone_name[MAX_MAP_ZONE_NAME];
	
	foreach(new x : iterFireEvents)
	{
		zone = GetMapZoneAtPoint2D(FireEventInfo[x][feBaseX], FireEventInfo[x][feBaseY]);
		GetMapZoneName(zone, zone_name);

		new Float:dist = GetPlayerDistanceFromPoint(playerid, FireEventInfo[x][feBaseX], FireEventInfo[x][feBaseY], FireEventInfo[x][feBaseZ]);
		format(string, sizeof (string), "{EEEEEE}%s\t%.0f metros\t{00FFFF}%.2f %\n", zone_name, dist, (1.0 - (FireEventInfo[x][feExtinguished] / FireEventInfo[x][feTotal])) * 100.00);
		strcat(MEGAString, string);
		
		OptionsInfo[playerid][fires] = x;
		fires += 1;
	}
	
	format(string, sizeof (string), "Incêndios em andamento ({00FFFF}%d{FFFFFF})", fires);
	ShowPlayerDialog(playerid, 800, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Localizar", "Fechar");
}

CMD:incendios(playerid) {

	if(!IsPlayerFirefighter(playerid))
		return SendClientMessage(playerid, -1, "Você não é um bombeiro.");

	ShowPlayerFireEvents(playerid);
	return 1;
}
