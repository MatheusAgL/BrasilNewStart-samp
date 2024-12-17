// Áreas neutras
#include <wars-terror>

//-------------------------------------------------------
#define 		MAX_TERRITORIOS			40

new PlayerText:textguerratr[MAX_PLAYERS];

new PlayerText:textaviso[MAX_PLAYERS];

CALLBACK:HideMessage(playerid) 
	return PlayerTextDrawHide(playerid, textaviso[playerid]);

enum {
	TR_TYPE_GANG,
	TR_TYPE_MAFIA,
	TR_TYPE_TERROR,
	TR_TYPE_MOTO,
	TR_TYPE_ASSASSINOS,
	TR_TYPE_FAMILIAS
}

enum tr_New
{
	trID,
	Float:trMinX,
	Float:trMinY,
	Float:trMaxX,
	Float:trMaxY,
	Float:trPointX,
	Float:trPointY,
	Float:trPointZ,
	trBonus,
	trName[128],
	trDono,
	trColor,
	trArea,
	trGZ,
	trTempoGuerra,
	trLiberarGuerra,
	trType,

	trGangAttack,
	trGangDeffend,
	trPontosAttack,
	trPontosDeffend,

	trTimer,
	trTempoDominado,
	bool:trGuerra,
	bool:trCreated,

	Text3D:trTextDroga,
	trPickupDroga
};
new trLS[MAX_TERRITORIOS][tr_New];

stock Float:GetTerritoryDrugProduction(trid) {
	new time = gettime() - trLS[trid][trTempoDominado];

	new Float:multiplier = (time / 60.0) / 30.0;
	if(multiplier > 10.0)
		multiplier = 10.0;

	return 1.0 + (multiplier / 10.0);
}

CALLBACK: OnUpdateTerritories(playerid) {

	// Sistema de Drogas no HUD
	new aux[2][20], timeInfo[16], _time, drugs[5][16] = {"Maconha", "Cocaina", "Crack", "Heroina", "Metanfetamina"};
	for(new i = 0; i < 5; i++) {
		format(aux[0], 20, "Efeito%s", drugs[i]);
		format(aux[1], 20, "Time%s", drugs[i]);

		if(GetPVarInt(playerid, aux[0])) {
			_time = GetPVarInt(playerid, aux[1]) - gettime();
			if(_time <= 0) {
				SetPVarInt(playerid, aux[0], 0);
				CONFIG_DrugSystem(playerid, i, false);

				foreach(new p : Player) {
					ShowPlayerNameTagForPlayer(p, playerid, true);
				}

				SetPlayerSeeNick(playerid, true);
			}
			else {
				if(!HasPlayerAnyPopup(playerid)) {
					format(timeInfo, 16, "%s", ConvertTime(_time));
					PlayerTextDrawSetString(playerid, _drugs_playertextdraw[i][playerid], timeInfo);

					if(GetPVarInt(playerid, "DrugsHidden")) {
						CONFIG_DrugSystem(playerid, i, true);
						SetPVarInt(playerid, "DrugsHidden", 0);
					}
				}
				else if(!GetPVarInt(playerid, "DrugsHidden")) {
					SetPVarInt(playerid, "DrugsHidden", 1);
				}
			}
		}
	}

	if(GetPVarInt(playerid, "EmTerritorio") && Player_GetTimerAFK(playerid) < 1) {
		new trid = GetPVarInt(playerid, "TerritorioID");
		if(GetPlayerOrg(playerid) == trLS[trid][trDono] && trLS[trid][trDono] > 0 && !IsACopOrg(trLS[trid][trDono])) {
			_time = GetPVarInt(playerid, "TerritorioTimeDroga");
			if(_time < gettime()) {
				new qtd = floatround((1 + random(6)) * GetTerritoryDrugProduction(trid), floatround_floor);
				trLS[trid][trBonus] += qtd;
				SetPVarInt(playerid, "TerritorioTimeDroga", gettime() + 20);
				UpdateTrDrug3DText(trid);
			}
		}
	}
	return 1;
}

CMD:tr(playerid)
{
    new org = GetPlayerOrg(playerid),
    	tr  = GetPlayerTr(playerid),
		string[185],
		color;

	if (tr < 0) 
		return SendClientMessage(playerid, -1, "Você não está em nenhum território da cidade.");

	/* Tipos de territórios e organizações liberadas */
	if (trLS[tr][trType] == TR_TYPE_GANG && !PlayerIsGang(playerid) && !IsACop(playerid))
		return SendClientMessage(playerid, -1, "Apenas gangsters e policias responsáveis pela pacificação desses territórios podem dominar.");

	if (trLS[tr][trType] == TR_TYPE_MAFIA && !PlayerIsMafia(playerid) && !IsACop(playerid))
		return SendClientMessage(playerid, -1, "Apenas mafiosos e policias responsáveis pela pacificação desses territórios podem dominar.");

	if (trLS[tr][trType] == TR_TYPE_TERROR && !PlayerIsTerror(playerid))
		return SendClientMessage(playerid, -1, "Apenas terrorista e policias responsáveis pela pacificação desses territórios podem dominar.");

	if (trLS[tr][trType] == TR_TYPE_MOTO && !PlayerIsMercenario(playerid) && !IsACop(playerid))
		return SendClientMessage(playerid, -1, "Apenas motoqueiros e policias responsáveis pela pacificação desses territórios podem dominar.");

	/* Restrições para usar o comando */
	if (GetPlayerInterior(playerid) != 0) return SendClientMessage(playerid, -1, "Você não pode dominar territórios dentro de interiores.");

	new vehicleid = GetPlayerVehicleID(playerid);
	new VIM:vim = Vehicle_GetVIM(vehicleid);

	if (VIM_IsPlane(vim))
		return SendClientMessage(playerid, -1, "Você não pode dominar territórios em veículos aéreos.");

	if ((Admin_GetNivel(playerid) || Helper_GetNivel(playerid)) && Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não pode dominar territórios em modo trabalho.");

	if (gettime() < trLS[tr][trLiberarGuerra]) return SendClientMessage(playerid, -1, "O território estava em guerra recentemente, aguarde para dominar novamente.");

	if (trLS[tr][trDono] == org) return SendClientMessage(playerid, -1, "O território já pertence a sua organização.");

	if (IsACop(playerid) && OrgIsACop(trLS[tr][trDono])) return SendClientMessage(playerid, -1, "O território já está dominado por uma organização policial.");

	if (trLS[tr][trGuerra]) return SendClientMessage(playerid, -1, "O território já está em guerra.");

	if (OrgMorro(org) && gGuerraMorro) return SendClientMessage(playerid, -1, "Este território não pode ser dominado pois está tendo guerra no morro.");

	if (IsACop(playerid) && OnDuty[playerid] != 1) return SendClientMessage(playerid, -1, "Você precisa bater o cartão para usar este comando.");

	if (warInfo[warCreated] && PlayerIsTerror(playerid)) return SendClientMessage(playerid, -1, "Você não pode dominar territórios em quanto tiver tendo guerra terrorista.");


	/* Retornando o comando para sucesso */
	for(new i; i != MAX_TERRITORIOS; ++i)
	{
 		if (trLS[i][trGangAttack] == org || trLS[i][trGangDeffend] == org)
			return SendClientMessage(playerid, -1, "Sua organização ja está defendendo ou atacando algum territorio.");
	}

	for(new tri; tri != MAX_TERRITORIOS; ++tri)
	{
		for(new i=1; i != MAX_ORGS; ++i)
		{
			if (trLS[tri][trGuerra] == true && (trLS[tri][trGangDeffend] == trLS[tr][trDono] || trLS[tri][trGangAttack] == trLS[tr][trDono]))
			    return SendClientMessage(playerid, -1, "Os donos deste território não podem defender nesse momento, pois já estão em uma guerra!");
		}
	}

	if (IsACop(playerid) && OnDuty[playerid] == 1)
	{
    	format(string, sizeof string, "Voce esta retomando o controle da regiao de ~g~%s~w~~n~espere 1 minuto para conseguir dominar esta area", trLS[tr][trName]);
    	PlayerTextDrawSetString(playerid, textaviso[playerid], string);

        GangZoneFlashForAll(trLS[tr][trGZ], 0x9999FFAA);
        color = 0x9999FF10;
		format(string, sizeof string, "Policial: %s está retomando o controle da região de %s.", PlayerName[playerid], trLS[tr][trName]);
	}
	else
	{
		new typeOrg[20];
		if(trLS[tr][trType] == TR_TYPE_GANG) {
			typeOrg = "GangZone";
		}
		else if(trLS[tr][trType] == TR_TYPE_MAFIA) {
			typeOrg = "Máfia";
		}
		else if(trLS[tr][trType] == TR_TYPE_TERROR) {
			typeOrg = "Terrorista";
		}
		else if(trLS[tr][trType] == TR_TYPE_MOTO) {
			typeOrg = "Motoqueiro";
		}

	    if(trLS[tr][trDono] < 1)
	    {
 			format(string, sizeof string, "Sua organizacao esta tentando tomar a regiao de ~g~%s", trLS[tr][trName]);
 			SendFamilyTextMessage(org, string);

			format(
				string, sizeof string, 
				"[%s]: %s esta tentando tomar a região de %s para %s %s.", 
				typeOrg, PlayerName[playerid], trLS[tr][trName], GetOrgArticle(org), GetOrgName(org)
			);
		}
		else
	    {
			format(string, sizeof string, "~r~%s (%s)~w~ estao tentando dominar a regiao de ~r~%s ~w~de voces~n~vao ate la e protejam o que e de voces", PlayerName[playerid], GetOrgName(org), trLS[tr][trName]);
			SendFamilyTextMessage(trLS[tr][trDono], string);

			format(string, sizeof string, "Sua organizacao está tentando tomar a regiao de ~g~%s~w~ %s ~r~%s", trLS[tr][trName], GetOrgArticle(trLS[tr][trDono], true), GetOrgName(trLS[tr][trDono]));
	 		SendFamilyTextMessage(org, string);

			format(
				string, sizeof string, "[%s]: %s e %s %s estão tentando tomar a região de %s %s %s.", 
				typeOrg, PlayerName[playerid], GetOrgArticle(org), GetOrgName(org), trLS[tr][trName], 
				GetOrgArticle(trLS[tr][trDono], true), GetOrgName(trLS[tr][trDono])
			);
		}
	   	GangZoneFlashForAll(trLS[tr][trGZ], GetPlayerColor(playerid)); color = GetPlayerColor(playerid);
	}

	SetPVarInt(playerid, "TomandoTr", trLS[tr][trArea]);

	trLS[tr][trGuerra] = true;

	SendClientMessageToAll(GetPlayerColor(playerid), string);

	SendClientMessage(playerid, COLOR_GRAD, "**Fique esperto, porque todos os Policiais e as Gangs foram avisadas de sua invasão!");

	trLS[tr][trGangAttack] = org;

	trLS[tr][trGangDeffend] = trLS[tr][trDono];
	trLS[tr][trLiberarGuerra] = gettime() + 2 * 60;

	trLS[tr][trPontosAttack] = 0;
	trLS[tr][trPontosDeffend] = 0;

	trLS[tr][trTempoGuerra] = 150;
	trLS[tr][trTimer] = SetTimerEx("GuerraTr", 1000, true, "dd", tr, color);

	CheckConquista(playerid, Conquista_Territorio);

	return true;
}
alias:tr("do", "territorio")

stock CheckPontosTr(playerid, killerid)
{
	new okiller = GetPlayerOrg(killerid);
	new oplayer = GetPlayerOrg(playerid);

	if(okiller < 1 || oplayer < 1)return 1;

	for(new i; i != MAX_TERRITORIOS; ++i)
	{
	    if(IsPlayerInDynamicArea(playerid, trLS[i][trArea]) && IsPlayerInDynamicArea(killerid, trLS[i][trArea]))
	    {
		    if(trLS[i][trGangAttack] == okiller && trLS[i][trGangDeffend] == oplayer)
			{
		        trLS[i][trPontosAttack]++;
		    }
		    else if(trLS[i][trGangAttack] == oplayer && trLS[i][trGangDeffend] == okiller)
			{
	            trLS[i][trPontosDeffend]++;
		    }
		}
	}
	return 1;
}

stock HidePlayerGZTextDraw(playerid) {
	PlayerTextDrawHide(playerid, textguerratr[playerid]);
}

CALLBACK:GuerraTr(trid, color)
{
	new
		pontosattack 	= trLS[trid][trPontosAttack],
		pontosdeffend 	= trLS[trid][trPontosDeffend],
		string[128]
	;

	if(trLS[trid][trGuerra]) {

		if(trLS[trid][trTempoGuerra] > 0) trLS[trid][trTempoGuerra] --;

		if(trLS[trid][trGangDeffend] > 0) {

			format(string, sizeof string,
			"~g~Tempo: %s ~w~~h~I~p~ %s~n~~y~Defendendo: ~w~%s:~r~ %d~n~~y~Atacando: ~w~%s: ~r~%d",
			ConvertTime(trLS[trid][trTempoGuerra]),
			trLS[trid][trName],
			GetOrgName(trLS[trid][trGangDeffend]),
			pontosdeffend,
			GetOrgName(trLS[trid][trGangAttack]),
			pontosattack);
		} else {
			format(string, sizeof string,
			"~g~Tempo: %s ~w~~h~I~p~ %s",
			ConvertTime(trLS[trid][trTempoGuerra]),
			trLS[trid][trName]);
		}

		foreach(new i : Player)
		{
			if(!HasPlayerAnyPopup(i)) {
				if (trLS[trid][trGangAttack] == GetPlayerOrg(i) || trLS[trid][trGangDeffend] == GetPlayerOrg(i))
				{
					GetTextDrawStringWidth(string, 2, 1);

					PlayerTextDrawSetString(i, textguerratr[i], string);
					PlayerTextDrawShow(i, textguerratr[i]);
				}
			}
			if (GetPlayerOrg(i) < 1)
			{
				PlayerTextDrawHide(i, textguerratr[i]);
	    	}
		}

		if(trLS[trid][trTempoGuerra] < 1)
		{
		    KillTimer(trLS[trid][trTimer]);
		    trLS[trid][trGuerra] = false;
		    if(CountOrgTr(trLS[trid][trGangAttack], trid) > 0)
		    {
			    if(pontosattack == pontosdeffend || pontosattack > pontosdeffend)
			    {
      				WinsGuerra(trid, trLS[trid][trGangAttack], trLS[trid][trGangDeffend], color);
			    }
			    else
			    {
			   		DeffendGuerra(trid, trLS[trid][trGangDeffend], trLS[trid][trGangAttack]);
			    }
			}
		    else
		    {
		       	DeffendGuerra(trid, trLS[trid][trGangDeffend], trLS[trid][trGangAttack]);
		    }

			trLS[trid][trGangAttack] = 0;
			trLS[trid][trGangDeffend] = 0;
		}
	}
	return 1;
}

stock WinsGuerra(trid, org, orgperde, gzcolor)
{
	new string[256], typeOrg[20], article[10], verb[20] = "conseguiu";

	article = GetOrgArticle(org, false, true);
	if(article[strlen(article)-1] == 's') {
		verb = "conseguiram";
	}

 	format(
		string, sizeof string, 
		"~r~%s %s~w~ %s tomar a regiao ~r~%s ~w~de voces~n~vao la e retomem o local", 
		article, GetOrgName(org), verb, trLS[trid][trName]
	);
  	SendFamilyTextMessage(orgperde, string);

 	format(string, sizeof string, "Voces conseguiram tomar a regiao de ~g~%s~w~ %s %s~n~Nao deixem que retomem de voces", trLS[trid][trName], GetOrgArticle(orgperde, true), GetOrgName(orgperde));
  	SendFamilyTextMessage(org, string);

	if(trLS[trid][trType] == TR_TYPE_GANG) {
		typeOrg = "Gangues";
	}
	else if(trLS[trid][trType] == TR_TYPE_MAFIA) {
		typeOrg = "Máfia";
	}
	else if(trLS[trid][trType] == TR_TYPE_TERROR) {
		typeOrg = "Terrorista";
	}
	else if(trLS[trid][trType] == TR_TYPE_MOTO) {
		typeOrg = "Motoqueiro";
	}

	if(orgperde) {
		format(
			string, sizeof string, 
			"[%s]: %s %s %s tomar a região de %s %s %s!", 
			typeOrg, article, GetOrgName(org), verb, 
			trLS[trid][trName], GetOrgArticle(orgperde, true), GetOrgName(orgperde)
		);
	} else {
		format(
			string, sizeof string, 
			"[%s]: %s %s %s tomar a região de %s!", 
			typeOrg, article, GetOrgName(org), verb, trLS[trid][trName]
		);
	}
	SendClientMessageToAll(gzcolor, string);

	format(string, sizeof string, "[Território]: Vocês conseguiram dominar a região %s e ganharam $%s no cofre.", trLS[trid][trName], getFormatText(2000));
  	SendMembersMessage(org, COLOR_LIGHTBLUE, string); 
	OrgInfo_SetMoney(org, OrgInfo_GetMoney(org) + 2000);

	if(IsACopOrg(trLS[trid][trDono]))
		trLS[trid][trBonus] = 0;

 	trLS[trid][trDono] = org;
 	trLS[trid][trColor] = gzcolor;
	trLS[trid][trTempoDominado] = gettime();
	GangZoneStopFlashForAll(trLS[trid][trGZ]);
    GangZoneShowForAll(trLS[trid][trGZ], trLS[trid][trColor]);

	UpdateTrDrug3DText(trid);
  	SaveTerritory(trid);

 	foreach(new i : Player) {
 		if(trLS[trid][trGangAttack] == GetPlayerOrg(i) || trLS[trid][trGangDeffend] == GetPlayerOrg(i)) {
	        PlayerTextDrawHide(i, textguerratr[i]);
	    }
	}
}

stock DeffendGuerra(trid, org, orgperde)
{
	new string[256], typeOrg[20], article[10], verb[20] = "conseguiu";

	article = GetOrgArticle(org, false, true);
	if(article[strlen(article)-1] == 's') {
		verb = "conseguiram";
	}

	if(trLS[trid][trType] == TR_TYPE_GANG) {
		typeOrg = "Gangues";
	}
	else if(trLS[trid][trType] == TR_TYPE_MAFIA) {
		typeOrg = "Máfia";
	}
	else if(trLS[trid][trType] == TR_TYPE_TERROR) {
		typeOrg = "Terrorista";
	}
	else if(trLS[trid][trType] == TR_TYPE_MOTO) {
		typeOrg = "Motoqueiro";
	}

 	format(
		string, sizeof string, 
		"Voces conseguiram defender a regiao de ~g~%s~w~ do ataque %s ~r~%s~n~~w~Cuidem bem do local e nao deixe que ataquem novamente", 
		trLS[trid][trName], GetOrgArticle(orgperde, true), GetOrgName(orgperde)
	);
  	SendFamilyTextMessage(org, string);

 	format(
		string, sizeof string, 
		"%s ~r~%s~w~ %s defender a regiao de ~r~%s~w~ do ataque de voces!", 
		article, GetOrgName(org), verb, trLS[trid][trName]
	);
  	SendFamilyTextMessage(orgperde, string);

	format(
		string, sizeof string, 
		"[%s]: %s %s %s defender a região de %s do ataque %s %s!", 
		typeOrg, article, GetOrgName(org), verb,  trLS[trid][trName], 
		GetOrgArticle(orgperde, true), GetOrgName(orgperde)
	);
	SendClientMessageToAll(COLOR_LIGHTRED, string);

	format(string, sizeof string, "[Território]: Vocês conseguiram defender a região %s e ganharam $%s no cofre.", trLS[trid][trName], getFormatText(2000));
  	SendMembersMessage(org, COLOR_LIGHTBLUE, string); 
	OrgInfo_SetMoney(org, OrgInfo_GetMoney(org) + 2000);

	GangZoneStopFlashForAll(trLS[trid][trGZ]);

 	foreach(new i : Player) {
 		if(trLS[trid][trGangAttack] == GetPlayerOrg(i) || trLS[trid][trGangDeffend] == GetPlayerOrg(i)) {
	        PlayerTextDrawHide(i, textguerratr[i]);
	    }
	}
}

stock CountOrgTr(orgid, trid)
{
	new count = 0;
 	foreach(new i : Player)
 	{
   		if(IsPlayerInDynamicArea(i, trLS[trid][trArea]) && GetPlayerOrg(i) == orgid){
			count++;
		}
  	}
	return count;
}

stock SendFamilyTextMessage(orgtext, const message[], hidemessage = 20000)
{
	foreach(new i : Player) {

		if(GetPlayerOrg(i) == orgtext && orgtext > 0) {
			PlayerTextDrawSetString(i, textaviso[i], message);
	        PlayerTextDrawShow(i, textaviso[i]);
	        SetTimerEx("HideMessage", hidemessage, false, "d", i);
		}
	}
}

stock CountTr()
{
	new count = 0;
	for(new tr; tr != MAX_TERRITORIOS; tr++){
	    if(trLS[tr][trCreated]){
	        count++;
	    }
	}
	return count;
}

stock Zone_IsPlayerIn(playerid)
{
    static Float:x,Float:y,Float:z;
    GetPlayerPos(playerid, x, y, z);

    for(new tr; tr != MAX_TERRITORIOS; tr++)
	{
		if (x >= trLS[tr][trMinX] && x <= trLS[tr][trMaxX] && y >= trLS[tr][trMinY] && y <= trLS[tr][trMaxY])  {
			return true;
		}
	}
	return false;
}

stock LoadTrForPlayer(playerid)
{
	for(new trid; trid != MAX_TERRITORIOS; trid++)
	{
	   	if(trLS[trid][trCreated])
	   	{
	        GangZoneShowForPlayer(playerid, trLS[trid][trGZ], trLS[trid][trColor]);
		}
	}
	return 1;
}

stock LoadTerritories()
{
	new string[256];
	mysql_format(MySQL_Handle, string, 256, "SELECT * FROM territorios");
	mysql_query(MySQL_Handle, string);

	for(new trid; trid != MAX_TERRITORIOS; trid++)
		trLS[trid][trCreated]	= false;

	new rows = MYSQL_GetRowsCount();
	for(new i = 0; i < rows; i++) {
		trLS[i][trCreated] = true;
		trLS[i][trID] = MYSQL_GetInt(i, "id");
		format(trLS[i][trName], 128, MYSQL_GetString(i, "nome"));
		trLS[i][trDono] = MYSQL_GetInt(i, "dono");
		trLS[i][trType] = MYSQL_GetInt(i, "tipo");
		trLS[i][trMinX] = MYSQL_GetFloat(i, "min_x");
		trLS[i][trMinY] = MYSQL_GetFloat(i, "min_y");
		trLS[i][trMaxX] = MYSQL_GetFloat(i, "max_x");
		trLS[i][trMaxY] = MYSQL_GetFloat(i, "max_y");
		trLS[i][trPointX] = MYSQL_GetFloat(i, "droga_x");
		trLS[i][trPointY] = MYSQL_GetFloat(i, "droga_y");
		trLS[i][trPointZ] = MYSQL_GetFloat(i, "droga_z");

		trLS[i][trBonus] = MYSQL_GetInt(i, "drogas");
		trLS[i][trGZ]	= GangZoneCreate(trLS[i][trMinX], trLS[i][trMinY], trLS[i][trMaxX], trLS[i][trMaxY]);
		trLS[i][trArea]	= CreateDynamicRectangle(trLS[i][trMinX], trLS[i][trMinY], trLS[i][trMaxX], trLS[i][trMaxY]);
		trLS[i][trTempoDominado] = gettime();

		if(IsACopOrg(trLS[i][trDono]))
			trLS[i][trColor] = 0x9999FF10;
		else {
			trLS[i][trColor] = GetOrgHexColor(trLS[i][trDono]);
		}

		GangZoneShowForAll(trLS[i][trGZ], trLS[i][trColor]);
		trLS[i][trPickupDroga] = CreateDynamicPickup(GetTerritoryDrugModel(i), 1, trLS[i][trPointX], trLS[i][trPointY], trLS[i][trPointZ]);
		trLS[i][trTextDroga] = CreateDynamic3DTextLabel("----", 0xBFBDBDFF, trLS[i][trPointX], trLS[i][trPointY], trLS[i][trPointZ], 10.0);
		UpdateTrDrug3DText(i);
	}
	return 1;
}

stock GetTerritoryDrugModel(trid) {
	new pickup[4] = {1575, 1576, 1577, 1578};
	return pickup[trLS[trid][trType]];
}

stock GetTerritoryDrugType(trid) {
	new types[4] = {ITEM_TYPE_COCAINA, ITEM_TYPE_CRACK, ITEM_TYPE_HEROINA, ITEM_TYPE_METANFETAMINA};
	return types[trLS[trid][trType]];
}

stock UpdateTrDrug3DText(trid) {
	new gstring[300];

	if(!IsACopOrg(trLS[trid][trDono])) {
		format(gstring, sizeof gstring, "%s\n\
										{8FBD8D}Ponto de Tráfico de %s\n\
										{%s}%s\n\
										{D4D4D4}Quantidade: {FFFFFF}%d grama(s)\n\
										Use {D4D4D4}/trafico {FFFFFF}para acessar", trLS[trid][trName],
			GetTerritoryDrugName(trid), GetOrgColor(trLS[trid][trDono]), GetOrgName(trLS[trid][trDono]), trLS[trid][trBonus]);
	}
	else if(trLS[trid][trDono] == 0) {
		format(gstring, sizeof gstring, "%s\n\
										{8FBD8D}Ponto de Tráfico de %s\n\
										Zona não-dominada", trLS[trid][trName],
			GetTerritoryDrugName(trid));
	}
	else {
		format(gstring, sizeof gstring, "%s\n\
										{8FBD8D}Ponto de Tráfico de %s\n\
										{FFFFFF}Controlado pela organização {%s}%s", trLS[trid][trName],
			GetTerritoryDrugName(trid), GetOrgColor(trLS[trid][trDono]), GetOrgName(trLS[trid][trDono]));
	}
	UpdateDynamic3DTextLabelText(trLS[trid][trTextDroga], 0x8FAF73FF, gstring);
}

stock GetTerritoryDrugName(trid) {
	new droga[4][30] = {"Cocaína", "Crack", "Heroína", "Metanfetamina"};
	return droga[trLS[trid][trType]];
}

stock SaveTerritory(trid)
{
	new string[300];
	mysql_format(MySQL_Handle, string, 300, "UPDATE territorios SET nome = '%e', dono = %d, tipo = %d, min_x = '%f', min_y = '%f', max_x = '%f', max_y = '%f', \
		droga_x = '%f', droga_y = '%f', droga_z = '%f', drogas = '%d' WHERE id = %d", trLS[trid][trName], trLS[trid][trDono], trLS[trid][trType], trLS[trid][trMinX],
		trLS[trid][trMinY], trLS[trid][trMaxX], trLS[trid][trMaxY], trLS[trid][trPointX], trLS[trid][trPointY], trLS[trid][trPointZ], trLS[trid][trBonus], trLS[trid][trID]);
	mysql_tquery(MySQL_Handle, string);
	return 1;
}

stock SaveTerritories()
{
	for(new tr; tr != MAX_TERRITORIOS; tr++)
	    if(trLS[tr][trCreated])
			SaveTerritory(tr);
}

stock GetPlayerTr(playerid)
{
	for(new tr; tr != MAX_TERRITORIOS; tr++)
	{
	    if(trLS[tr][trCreated]){
	    	if(IsPlayerInDynamicArea(playerid, trLS[tr][trArea])){
	    	    return tr;
			}
		}
	}
	return -1;
}

stock GetOrgTrs(orgid)
{
	if (orgid == 0)
		return 0;

	new quant = 0;

	for (new tr; tr != MAX_TERRITORIOS; tr++) {

		if (trLS[tr][trCreated] && trLS[tr][trDono] == orgid) quant++;
	}

	return quant;
}

stock GetPlayerMaxDrugs(playerid) 
{
	new maxDrugs = 10000;

	switch (Player_GetVIP(playerid)) {
		case SOCIO_COMUM: maxDrugs += 1000;
		case SOCIO_PREMIUM: maxDrugs += 2000;
		case SOCIO_SUPREME: maxDrugs += 4000;
		case SOCIO_EXTREME: maxDrugs += 5000;
	}
	return maxDrugs;
}

stock GetPlayerAvailableDrugSpace(playerid) {
	new total = 0;
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++)
	{
		if (InventarioInfo[playerid][inv][item_valid] && (InventarioInfo[playerid][inv][item_type] == ITEM_TYPE_MACONHA 
			|| InventarioInfo[playerid][inv][item_type] == ITEM_TYPE_COCAINA || InventarioInfo[playerid][inv][item_type] == ITEM_TYPE_CRACK
			|| InventarioInfo[playerid][inv][item_type] == ITEM_TYPE_CRACK || InventarioInfo[playerid][inv][item_type] == ITEM_TYPE_HEROINA
			|| InventarioInfo[playerid][inv][item_type] == ITEM_TYPE_METANFETAMINA)) {

            total += InvItem_GetQuantity(playerid, inv);
		}
	}

	total = GetPlayerMaxDrugs(playerid) - total;
	return (total > 0) ? total : 0;
}

stock GetPlayerTerritoryMaxCollection(playerid, trid) {
	new cargo = PlayerInfo[playerid][pCargo],
		maximo = 0,
		espaco = GetPlayerAvailableDrugSpace(playerid);

	if(GetPlayerOrg(playerid) == trLS[trid][trDono]) {
		if(cargo == 1)
			maximo = 2000;
		else if(cargo == 2)
			maximo = 3000;
		else if(cargo == 3)
			maximo = 4000;
		else if(cargo == 4)
			maximo = 4500;
		else if(cargo == LIDER)
			maximo = 6000;
		else if(cargo >= 5)
			maximo = 5500;


		if(maximo > trLS[trid][trBonus])
			maximo = trLS[trid][trBonus];

		if(maximo > espaco)
			maximo = espaco;
	}
	return maximo;
}

hook OP_EnterDynamicArea(playerid, areaid)
{
	for(new tr = 0; tr < MAX_TERRITORIOS; tr++) {
		if(trLS[tr][trCreated] && areaid == trLS[tr][trArea]) {
			SetPVarInt(playerid, "TerritorioID", tr);
			SetPVarInt(playerid, "EmTerritorio", 1);
			SetPVarInt(playerid, "TerritorioTimeDroga", gettime() + 20);
		}
	}
	return 1;
}

hook OP_LeaveDynamicArea(playerid, areaid)
{
	for(new tr = 0; tr < MAX_TERRITORIOS; tr++) {
		if(trLS[tr][trCreated] && areaid == trLS[tr][trArea]) {
			SetPVarInt(playerid, "EmTerritorio", 0);
		}
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == 600)
	{
		if(!response) 
			return 1;

		new trid = GetPVarInt(playerid, "TerritorioID");
		if(listitem == 0) {
			if(trLS[trid][trBonus] == 0)
				return SendClientMessage(playerid, -1, "Não há drogas para coletar nesse território.");
			else if(GetPlayerOrg(playerid) != trLS[trid][trDono])
				return SendClientMessage(playerid, -1, "Sua organização não está com o controle desse território.");
			else if(gettime() < GetPVarInt(playerid, "TimeColetaDroga"))
				return SendMsgF(playerid, -1, "Aguarde %s para coletar drogas novamente...", ConvertTime(GetPVarInt(playerid, "TimeColetaDroga") - gettime()));

			new maximo = GetPlayerTerritoryMaxCollection(playerid, trid);
			MEGAString[0] = EOS;
			FormatCat(MEGAString, "{D4D4D4}Quantidade produzida: {FFFFFF}%d grama(s)\n", trLS[trid][trBonus]);
			FormatCat(MEGAString, "{D4D4D4}Coleta máxima: {FFFFFF}%d grama(s)\n\n", maximo);
			strcat(MEGAString, "{BBBBBB}Digite quanto você deseja coletar.");
			ShowPlayerDialog(playerid, 601, DIALOG_STYLE_INPUT, "Tráfico - Coleta de Drogas", MEGAString, "Coletar", "Cancelar");
		}
		else if(listitem == 1) {
			new maximo = floatround(7 * GetTerritoryDrugProduction(trid), floatround_floor), 
				orgid = trLS[trid][trDono];

			MEGAString[0] = EOS;
			strcat(MEGAString, "{D4D4D4}Informação\tValor\n");
			FormatCat(MEGAString, "{D4D4D4}Organização em posse\t{%s}%s\n", GetOrgColor(orgid), GetOrgName(orgid));
			FormatCat(MEGAString, "{D4D4D4}Tempo de controle\t{FFFFFF}%s\n", ConvertTime(gettime() - trLS[trid][trTempoDominado]));
			FormatCat(MEGAString, "{D4D4D4}Multiplicador por tempo de controle\t{FFFFFF}%.2f %%\n", (GetTerritoryDrugProduction(trid) - 1.0) * 100);
			FormatCat(MEGAString, "{D4D4D4}Produção de drogas por minuto\t{FFFFFF}1 a %d grama(s)\n", maximo);
			ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "Tráfico - Informações", MEGAString, "Fechar", "");
		}
	}
	else if(dialogid == 601) {
		if(!response) 
			return 1;

		new trid = GetPVarInt(playerid, "TerritorioID");
		if(trLS[trid][trBonus] == 0)
			return SendClientMessage(playerid, -1, "Não há drogas para coletar nesse território.");
		else if(GetPlayerOrg(playerid) != trLS[trid][trDono])
			return SendClientMessage(playerid, -1, "Sua organização não está com o controle desse território.");

		new qtd = strval(inputtext), 
			maximo = GetPlayerTerritoryMaxCollection(playerid, trid),
			string[128];

		if(qtd <= 0 || qtd > maximo)
			return SendMsgF(playerid, -1, "Digite um valor entre 1 e %d para coletar.", maximo);

		format(string, sizeof(string), "* %s coletou %d grama(s) de %s.", PlayerName[playerid], qtd, GetTerritoryDrugName(trid));
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		trLS[trid][trBonus] -= qtd;

		addQuantiaItem(playerid, GetTerritoryDrugType(trid), GetTerritoryDrugModel(trid), qtd, GetTerritoryDrugName(trid), 0, 0);
		SetPVarInt(playerid, "TimeColetaDroga", gettime() + (5 * 60 * 0)); // remover o 0

		UpdateTrDrug3DText(trid);

		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		ShowPlayerBaloonInfo(playerid, "Voce pegou drogas no territorio.~n~Cuidado para nao perde-las!", 5000);
	}
	return 0;
}

hook OnPlayerConnect(playerid) {

	textguerratr[playerid] = CreatePlayerTextDraw(playerid,122.000000, 413.000000, "~g~Tempo: 00:00 ~w~~h~I~p~ Aeroporto de Los Santos~n~~w~Groove: ~r~~h~2~n~~w~Amigo dos Amigos: ~r~~h~4");
	PlayerTextDrawBackgroundColor(playerid,textguerratr[playerid], 0);
	PlayerTextDrawFont(playerid,textguerratr[playerid], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid,textguerratr[playerid], 0.169999, 0.799999);
	PlayerTextDrawColor(playerid,textguerratr[playerid], -1);
	PlayerTextDrawSetOutline(playerid,textguerratr[playerid], 1);
	PlayerTextDrawSetProportional(playerid,textguerratr[playerid], true);
	PlayerTextDrawSetSelectable(playerid,textguerratr[playerid], false);

	textaviso[playerid] = CreatePlayerTextDraw(playerid,139.000000, 343.000000, "~r~Theus_Crazzy (Vagos)~w~ estao tentando tomar a regiao de ~r~Idlewood ~w~de voces~n~vao ate la e protejam o que e de voces");
	PlayerTextDrawBackgroundColor(playerid,textaviso[playerid], 255);
	PlayerTextDrawFont(playerid,textaviso[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textaviso[playerid], 0.309999, 1.500000);
	PlayerTextDrawColor(playerid,textaviso[playerid], -1);
	PlayerTextDrawSetOutline(playerid,textaviso[playerid], 0);
	PlayerTextDrawSetProportional(playerid,textaviso[playerid], true);
	PlayerTextDrawSetShadow(playerid,textaviso[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textaviso[playerid], false);

	return 1;
}

CMD:resettr(playerid)
{
	if (Admin_GetNivel(playerid) >= DONO)
	{
		new tr = GetPlayerTr(playerid);

		if(tr < 0)
		    return SendClientMessage(playerid, COLOR_GREY, "Você não está em nenhum território da cidade.");

	 	trLS[tr][trDono] 	= 0;
	  	trLS[tr][trColor] 	= 0xAAAAAAAA;

		GangZoneShowForAll(trLS[tr][trGZ], trLS[tr][trColor]);
		SendClientMessage(playerid, COLOR_GREY, "Territorio resetado!");
		SaveTerritory(tr);
	}
	return 1;
}

CMD:irtr(playerid, params[]) {

	if (Admin_GetNivel(playerid) < SUPERVISOR) {
	    return SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
	}

	if (isnull(params)) {
	    return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /irtr [id]");
	}
	new id = strval(params);

	if (id < 0 || id >= MAX_TERRITORIOS) {
	    return SendClientMessage(playerid, -1, "Este território não existe!");
	}

	SetPlayerPos(playerid, trLS[id][trPointX], trLS[id][trPointY], trLS[id][trPointZ]);
	SetPlayerVirtualWorld(playerid, 0);

	new string[95];
	format(string, sizeof string, "Você foi até o território {00FFFF}%s{FFFFFF}!", trLS[id][trName]);
  	SendClientMessage( playerid, -1, string);
	return 1;
}

CMD:trafico(playerid) {
	new trid = -1;
	for(new tr = 0; tr < MAX_TERRITORIOS; tr++) {
		if(trLS[tr][trCreated] && PlayerToPoint(2.0, playerid, trLS[tr][trPointX], trLS[tr][trPointY], trLS[tr][trPointZ])) {
			trid = tr;
			break;
		}
	}

	if(trid == -1) 
		return SendClientMessage(playerid, -1, "Você não está no ponto de tráfico de um território.");
	else if(IsACopOrg(trLS[trid][trDono])) 
		return SendClientMessage(playerid, -1, "Este ponto de tráfico foi dominado pelas forças policiais.");
	else if(trLS[trid][trDono] == 0) 
		return SendClientMessage(playerid, -1, "Este ponto de tráfico não está dominado pelo tráfico.");

	ShowPlayerDialog(playerid, 600, DIALOG_STYLE_LIST, "Tráfico de Drogas", "Coletar drogas\nInformações do território", "Selecionar", "Cancelar");
	return 1;
}