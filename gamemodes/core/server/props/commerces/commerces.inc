#include <YSI_Coding\y_hooks>


#include <commerces_entry>
#include <commerces_cmds>
#include <bank>		// Bancos

hook OnPlayerEnterDynamicCP(playerid, checkpointid) {

    for(new checkid; checkid < sizeof(prop_checkpoint_interact); checkid++) {
        switch (checkid) {
            case 53, 57, 59, 63, 65, 72, 73, 74, 75, 76, 77: {
                if (checkpointid == prop_checkpoint_interact[checkid]) {
                    if (MenuInfo[playerid][menu_id] == INVALID_MENU_ID) {
                        SetPlayerFacingAngle(playerid, 180.8780);

                        InterpolateCameraPos(playerid, 294.330169, -37.125114, 1002.676757, 294.261505, -37.953235, 1002.482360, 1000);
                        InterpolateCameraLookAt(playerid, 294.183776, -41.893886, 1001.180969, 294.398132, -42.588764, 1000.613342, 1000);

                        TogglePlayerControllable(playerid, false);

                        MenuInfo[playerid][menu_id] = ID_MENU_AMMUNATION;
                        OpenMenu(playerid, ID_MENU_AMMUNATION);
                    }
                }
            }
            default: continue;
        }
    }
    return 1;
}

stock FireAlarmPropertie( id ) {
	if( id > MAX_PROPERTIES || PropInfo[id][eAlarm]) return 0;

	foreach(new playerid : Player) {
	    if (IsPlayerInRangeOfPoint(playerid, 50.0, 2146.67065, 1633.03381, 835.57257) && GetPlayerVirtualWorld(playerid) == id + PROP_VW) {
	        PlayerPlaySound(playerid, 42801, 2146.67065, 1633.03381, 835.57257);
	    }
	}

	PropInfo[id][eAlarm] = true;
	SetTimerEx("HideAlarm", 10 * 60000, false, "i", id);

	return 1;
}

CALLBACK: HideAlarm( id ) {
    if( id > MAX_PROPERTIES || !PropInfo[id][eAlarm]) return 0;

	foreach(new playerid : Player) {
	    if (IsPlayerInRangeOfPoint(playerid, 50.0, 2146.67065, 1633.03381, 835.57257) && GetPlayerVirtualWorld(playerid) == id + PROP_VW) {
	        PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	    }
	}

    PropInfo[id][eAlarm] = false;
    return 1;
}

hook OnPlayerEnterDynamicArea(playerid, areaid)
{
	if (areaid == AreaCofre)
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return 1;

		new id = GetPVarInt(playerid, "propId");

	    if (!PropInfo[id][eLaser] or PropInfo[id][eAlarm] or IsACop(playerid)) return 1;

	    if ( !IsPlayerOwnerPropertie( playerid, id ) ) {

	        new string[144];

	        if (gettime() < PropInfo[id][eRobbed]) {
	            format(string, sizeof string, "* A empresa está se recuperando de um roubo recente. Há informações que novos fundos ...");
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				format(string, sizeof string, "... irão chegar em aproximadamente %s, até lá a empresa não pode ser roubada!", ConvertTime(PropInfo[id][eRobbed] - gettime()));
                SendClientMessage(playerid, COLOR_LIGHTRED, string);
                return 1;
			}

	        if (roubouOrg[GetPlayerOrg(playerid)]) {
                SendClientMessage(playerid, COLOR_LIGHTRED, "* Sua organização já roubou neste payday, saia do local imediatamente !");
                return 1;
			}

			format(string, sizeof string, "[Assalto ao Cofre]: %s e %s %s estão tentando roubar o cofre da empresa %s [%d]", PlayerName[playerid], GetOrgArticle(GetPlayerOrg(playerid)), GetOrgName(GetPlayerOrg(playerid)), PropInfo[id][ePname], id);
			SendClientMessageToAll(COLOR_LIGHTRED, string);
			SetPlayerCriminal(playerid, 255, "Assalto ao cofre");
		}
	    FireAlarmPropertie( id );
	    return 1;
	}

	checkAreaMina(playerid, areaid);
	checkTransporteArea(playerid, areaid);

	return 1;
}

CALLBACK: CreatePropertyeLasers(id)
{
	if(id > MAX_PROPERTIES || PropInfo [id] [eLaser]) return 0;

	PropInfo [id] [eLasers][0] = CreateDynamicObject(18643, 2139.67773, 1629.24146, 836.76978,   0.00000, 9.00000, 338.00000, id + PROP_VW);
	PropInfo [id] [eLasers][1] = CreateDynamicObject(18643, 2133.40381, 1626.73120, 836.58679,   0.00000, 25.00000, 0.00000, id + PROP_VW);
	PropInfo [id] [eLasers][2] = CreateDynamicObject(18643, 2140.05713, 1623.52380, 836.58679,   0.00000, 14.00000, 0.00000, id + PROP_VW);
	PropInfo [id] [eLasers][3] = CreateDynamicObject(18643, 2164.67578, 1619.41272, 835.66449,   0.00000, 6.00000, 203.25874, id + PROP_VW);
	PropInfo [id] [eLasers][4] = CreateDynamicObject(18643, 2154.80176, 1623.60400, 836.58679,   0.00000, 14.00000, 176.63193, id + PROP_VW);
	PropInfo [id] [eLasers][5] = CreateDynamicObject(18643, 2140.45923, 1618.59412, 836.58679,   0.00000, 11.00000, 360.00000, id + PROP_VW);
	PropInfo [id] [eLasers][6] = CreateDynamicObject(18643, 2145.46362, 1613.00623, 836.81873,   0.00000, 11.00000, 3.00000, id + PROP_VW);
	PropInfo [id] [eLasers][7] = CreateDynamicObject(18643, 2131.63281, 1614.92090, 835.72998,   0.00000, 7.00000, 360.00000, id + PROP_VW);
	PropInfo [id] [eLasers][8] = CreateDynamicObject(18643, 2154.98657, 1628.96448, 836.58679,   0.00000, 14.00000, 208.12320, id + PROP_VW);
	PropInfo [id] [eLasers][9] = CreateDynamicObject(18643, 2164.21167, 1633.04309, 835.86548,   0.00000, 9.00000, 208.00000, id + PROP_VW);
	PropInfo [id] [eLasers][10] = CreateDynamicObject(18643, 2132.06006, 1616.19385, 836.58679,   0.00000, 7.00000, 360.00000, id + PROP_VW);
	PropInfo [id] [eLasers][11] = CreateDynamicObject(18643, 2136.25342, 1612.09204, 835.38416,   0.00000, 7.00000, 60.22263, id + PROP_VW);
	PropInfo [id] [eLasers][12] = CreateDynamicObject(18643, 2145.46362, 1613.00623, 835.38416,   0.00000, 7.00000, 2.90791, id + PROP_VW);
	PropInfo [id] [eLaser]      = true;
	KillTimer(PropInfo [id] [eTimerLaser]);

	return 1;
}

stock DestroyPropertyeLasers( id, reactiveTimer = 5 * 60000 ) {
	if( id > MAX_PROPERTIES || !PropInfo [id] [eLaser]) return 0;

	for (new laser; laser != 13; laser++) {
		DestroyDynamicObject(PropInfo [id] [eLasers][laser]);
	}
	PropInfo [id] [eLaser]      = false;
	KillTimer(PropInfo [id] [eTimerLaser]);
	PropInfo [id] [eTimerLaser] = SetTimerEx("CreatePropertyeLasers", reactiveTimer, false, "i", id);

	return 1;
}

stock OpenPropDoor( id , timeconsertar = 2 * 60000)
{
    if( id > MAX_PROPERTIES || PropInfo[id][eDoorDestroyed]) return 1;

	MoveDynamicObject(PropInfo[id][eDoor], 2148.6719, 1632.2874, 835.7532, 10.0, 0.0000, 0.0000, 246.6403);
	PropInfo[id][eDoorOpen] = true;

	KillTimer(PropInfo[id][eDoorTimer]);
	PropInfo[id][eDoorTimer] = SetTimerEx("ReconstroyPropDoor", timeconsertar, false, "i", id);

	return 1;
}

stock DestroyPropDoor( id , timeconsertar = 10 * 60000) {

    if( id > MAX_PROPERTIES ) return 1;

	MoveDynamicObject(PropInfo[id][eDoor], 2148.0889, 1634.7677, 834.1683, 10.0, 96.0000, -26.0000, 174.0000);
	PropInfo[id][eDoorDestroyed] = true;

	KillTimer(PropInfo[id][eDoorTimer]);
	PropInfo[id][eDoorTimer] = SetTimerEx("ReconstroyPropDoor", timeconsertar, false, "i", id);

	return 1;
}

CALLBACK: ReconstroyPropDoor( id ) {

    if( id > MAX_PROPERTIES ) return 1;

    MoveDynamicObject(PropInfo[id][eDoor], 2148.09399, 1633.38513, 835.75317, 8.0, 0.00000, 0.00000, 180.36060);
    PropInfo[id][eDoorDestroyed] = false;
    PropInfo[id][eDoorOpen] 	 = false;
    KillTimer(PropInfo[id][eDoorTimer]);

    return 1;
}

stock DepositPropertie(playerid, quantia)
{
	new id = currentInt[playerid];

	if (id < 0) return false;

    if (id > MAX_PROPERTIES || quantia < 1) return false;

	if (id != -1) {
	    PropInfo[id][eTill] += quantia;
		atualizarPropText(id);
		savePropertie(id);
		return 1;
	}
	return 0;
}

stock DepositPropertieID(prop, quantia)
{
	if (prop < 0) return false;

    if (prop > MAX_PROPERTIES || quantia < 1) return false;

	if (prop != -1) {
	    PropInfo[prop][eTill] += quantia;
		atualizarPropText(prop);
		savePropertie(prop);
		return 1;
	}
	return 0;
}

stock CountProperties(playerid) {
	new countp;
	for ( new prop; prop != unid; prop++ ) {
	    if (IsPlayerOwnerPropertie(playerid, prop) ) {
	        countp ++;
	    }
	}
	return countp;
}

CreateProperties()
{
	for(new i = 0; i < sizeof(properties); i++)
	{
		CreateProperty(properties[i][eUniqIntId], properties[i][eIcon], properties[i][eEntX], properties[i][eEntY], properties[i][eEntZ], 
			properties[i][eEntA], properties[i][eType]);

		CreateDynamicMapIcon(
			properties[i][eEntX],
			properties[i][eEntY],
			properties[i][eEntZ],
			properties[i][eMapIcon],
			0xE6E6E6E6,
			-1, -1, -1,
			1300.00
		);
	}
	return 1;
}

PutPlayerInProperty(playerid, propId, propVW = 0)
{
	new Float:x, Float:y, Float:z, Float:a;

	if (PropInfo[propId][prop_type] == TRADE_TYPE_PARKING) {
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehiclePos(vehicleid, 2318.5457, 1933.2838, 5.0396);
			SetVehicleVirtualWorld(vehicleid, (propVW==0) ? propId+PROP_VW:propVW);
			SetPlayerFacingAngle(playerid, 357.8259);
		}
		else {
			a = GetPropertyExit(propId, x, y, z);
			SetPlayerPos(playerid, x, y, z);
			SetPlayerFacingAngle(playerid, a);

			SetCameraBehindPlayer(playerid);
		}
	} else {
		a = GetPropertyExit(propId, x, y, z);
		SetPlayerPos(playerid, x, y, z);
		SetPlayerFacingAngle(playerid, a);

		SetCameraBehindPlayer(playerid);
	}

	// Liberando Mercado Negro e Fábrica de Materiais
	new propsLiberadas[] = {20, 61, 53, 57, 59, 63, 65, 72, 73, 74, 75, 76, 77}, block = 1;
	for(new i = 0; i < sizeof(propsLiberadas); i++) {
		if(propId == propsLiberadas[i]) {
			block = 0;
			break;
		}
	}

	if(block) {
		if (!IsACop(playerid) && OnDuty[playerid] != 1 && EmpregoDuty[playerid] != 2) {
			SendClientMessage(playerid, -1, "Bem vindo! {FF0000}Removemos suas armas {FFFFFF}no detector de metais e lhe devolveremos ao sair.");
			BlockPlayerTempWeapons(playerid);
		} else {
			SendClientMessage(playerid, -1, "Bem vindo Oficial! Você tem {00FF00}autorização para portar armas {FFFFFF}dentro deste local.");
		}
	}

	SetPlayerInterior(playerid, GetPropertyInteriorId(propId));
	SetPlayerVirtualWorld(playerid, (propVW==0) ? propId+PROP_VW:propVW);
	currentInt[playerid] = propId;

	if (propId == 56) SendClientMessage(playerid, -1, "Use seu veículo de inventário por: {00AA00}$10.000 {FFFFFF}pagos para {00BFFF}8-Track Stadium");
}

CreateProperty(uniqIntId, iconId, Float:entX, Float:entY, Float:entZ, Float:entA, p_type, price=0)
{
	if ((unid + 1) < MAX_PROPERTIES)
	{
		new Id = CreatePickup( iconId ,23, entX, entY, entZ, -1);
		propPickups[Id] = unid;
		properties[unid][eEntX] 		= entX;
		properties[unid][eEntY] 		= entY;
		properties[unid][eEntZ] 		= entZ;
		properties[unid][eEntA] 		= entA;
		properties[unid][eUniqIntId] 	= uniqIntId;
		PropInfo  [unid][ePrice] 		= price;
		format(PropInfo[unid][ePname], 64, interiorInfo[properties[unid][eUniqIntId]][inName]);
		properties[unid][eType] 		= p_type;
		PropInfo[unid][eDoor]     		= CreateDynamicObject(2634, 2148.09399, 1633.38513, 835.75317,   0.00000, 0.00000, 180.36060, unid + PROP_VW);
        PropInfo[unid][eDoorOpen]   	= false;
		PropInfo[unid][eLoaded] 		= false;
		if (unid == 81)
        	PropInfo[unid][eText]     		= CreateDynamic3DTextLabel("Fundos da empresa: $0", 0xFFFFFFF5, 1442.4266, -1119.4700, 24.9146, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID);
        else
			PropInfo[unid][eText]     		= CreateDynamic3DTextLabel("Fundos da empresa: $0", 0xFFFFFFF5, 2148.2170,1648.1301,835.3793, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, unid + PROP_VW);
		CreatePropertyeLasers(unid);

		propTextInfo[unid] = Text3D:INVALID_3DTEXT_ID;

        switch (p_type)
		{
		    case TYPE_HOUSE: 		propTextInfo[unid] = CreateDynamic3DTextLabel("_", 0xFFFFFFF6, entX, entY, entZ + 0.75, 20.0);
		    case TYPE_BUSINESS: 	propTextInfo[unid] = CreateDynamic3DTextLabel("_", 0xFFFFFFF6, entX, entY, entZ + 0.75, 20.0);
		    case TYPE_BANK:			propTextInfo[unid] = CreateDynamic3DTextLabel("_", 0xFFFFFFF6, entX, entY, entZ + 0.75, 20.0);
		    case TYPE_COPS:			propTextInfo[unid] = CreateDynamic3DTextLabel("_", 0xFFFFFFF6, entX, entY, entZ + 0.75, 20.0);
		}

		new Float:x, Float:y, Float:z;
        GetPropertyExit(unid, x, y, z);
		
		CreateDynamic3DTextLabel("{B90A0A}SAIDA\n{DDDDDE}Pressione "_KEY_PATH_ENTER_INT_COLOR" {DDDDDE}para sair",0xFFFFFFF6, x, y, z + 0.95, 10.0);

		return unid++;
	}
	else return -1;
}

atualizarPropText( id )
{
	if (id > MAX_PROPERTIES) return false;

    new text_info[256];

	if (!IsPropertyOwner(id))
	{
	 	format(text_info,256,
	 	"{00FFFF}%s [%d]\n\
	 	{FFFFFF}Dono: {00FFFF}Ninguém\n\
	 	{FFFFFF}Custo: {00AA00}$%s\n\
 		{FFFFFF}Use {00FFFF}/propriedade comprar {FFFFFF}para comprar\n\
 		{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",
 		PropInfo[id][ePname], id, getFormatText(PropInfo[id][ePrice]));

	} else {

	 	format(text_info,256,
	 	"{00FFFF}%s [%d]\n\
	 	{FFFFFF}Dono: {00FFFF}%s\n\
	 	{FFFFFF}Fundos: {00AA00}$%s\n\
		{FFFFFF}Insumos: {00AA00}%d\n\
		{FFFFFF}Insumos Requeridos: {00AA00}%d\n\
		{FFFFFF}Preço por Insumo: {00AA00}$%s\n\
 		{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",
 		PropInfo[id][ePname], id, PropInfo[id][eOwner], getFormatText(PropInfo[id][eTill]),
			PropInfo[id][eInsumos], PropInfo[id][eInsumosReq], getFormatText(PropInfo[id][ePrecoInsumo]));
	}
	UpdateDynamic3DTextLabelText(propTextInfo[id], 0xFFFFFFF6, text_info);

	format(text_info, sizeof text_info, "{FFFFFF}Fundos da empresa: {00AA00}$%s\n\n\
	{FFFFFF}Use /pegargrana para pegar uma bolsa de dinheiro", getFormatText(PropInfo[id][eTill]));
	UpdateDynamic3DTextLabelText(PropInfo[id][eText], 0xFFFFFFF5, text_info);

	return true;
}

/*stock PROP_ShowList(type)
{
	switch (type)
	{
		case PROP_TYPE_MARKET: {

			new string[128];

			MEGAString[0] = EOS;
			strcat(MEGAString, "ID Nome do mercado\tAnuncio\n");


		}
		default: return 1;
	}

	return 1;
}*/

stock listPropriedades(playerid, owner = 0)
{
	new prop_string[128];
	new prop_select = 0 ;

	MEGAString [0] = EOS ;
	strcat(MEGAString, (owner ? ("ID Nome da empresa\tFundos\tDespesas\tVencimento\n") : ("ID Nome da empresa\tDono\n")));
	for( new prop; prop != unid; prop++) {
		if (owner && PropInfo[prop][eOwnerID] == PlayerInfo[playerid][pID]) {
			new days = TimestampToRemainingDays(PropInfo[prop][eVencimento]);
			if ( days <= 0 ) {
				format(prop_string, sizeof (prop_string), "%02d  %s\t{00AA00}$%s\tLuz e Água\t{00AA00}$%s\t{FF0000}VENCIDO\n", prop, PropInfo[prop][ePname], getFormatText(PropInfo[prop][eTill]), getFormatText(PropInfo[prop][eDespesas]));
			} else {
				format(prop_string, sizeof (prop_string), "%02d  %s\t{00AA00}$%s\tLuz e Água\t{00AA00}$%s\t%d dias\n", prop, PropInfo[prop][ePname], getFormatText(PropInfo[prop][eTill]), getFormatText(PropInfo[prop][eDespesas]), days);
			}
			strcat(MEGAString, prop_string);
			SelectEmpresa[playerid][prop_select] = prop;
			prop_select ++;
	    } else if(!owner) {
     		format(prop_string, sizeof (prop_string), "%02d  %s\t%s\n", prop, PropInfo[prop][ePname], PropInfo[prop][eOwner]);
			strcat(MEGAString, prop_string);
			SelectEmpresa[playerid][prop_select] = prop;
			prop_select ++;
	    }
	}
	ShowPlayerDialog(playerid, 7224, DIALOG_STYLE_TABLIST_HEADERS, (playerid >= 0 ?  ("Suas propriedades") : ("Localizar propriedades")), MEGAString, "Localizar", "Voltar");
}

stock ShowPlayerProperties(playerid) {
	new prop_string[128];
	new prop_select = 0;

	MEGAString [0] = EOS;
	strcat(MEGAString, "ID Nome da empresa\tFundos\tDespesas\tVencimento\n");
	for( new prop; prop != unid; prop++) {
		if (PropInfo[prop][eOwnerID] == PlayerInfo[playerid][pID]) {
			new days = TimestampToRemainingDays(PropInfo[prop][eVencimento]);
			if ( days <= 0 ) {
				format(prop_string, sizeof (prop_string), "%02d  %s\t{00AA00}$%s\tLuz e Água\t{00AA00}$%s\t{FF0000}VENCIDO\n", prop, PropInfo[prop][ePname], getFormatText(PropInfo[prop][eTill]), getFormatText(PropInfo[prop][eDespesas]));
			} else {
				format(prop_string, sizeof (prop_string), "%02d  %s\t{00AA00}$%s\tLuz e Água\t{00AA00}$%s\t%d dias\n", prop, PropInfo[prop][ePname], getFormatText(PropInfo[prop][eTill]), getFormatText(PropInfo[prop][eDespesas]), days);
			}
			strcat(MEGAString, prop_string);
			SelectEmpresa[playerid][prop_select] = prop;
			prop_select ++;
	    }
	}

	inline D_MyProps(mdlid, mdldialogid, mdlresponse, mdllistitem, string:mdltext[])
	{
		#pragma unused mdlid, mdldialogid, mdltext
		if (!mdlresponse)
			return 1;

		if (mdllistitem != -1) {
			Player_SetSpawnType(playerid, TYPE_SPAWN_BUSSINES, SelectEmpresa[playerid][mdllistitem]);
		}
		return 1;
	}
	Dialog_ShowCallback(playerid, using inline D_MyProps, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Selecione uma empresa", MEGAString, "Selecionar", ""C_BACKGROUND"Fechar");
	return 1;
}

stock Player_SpawnInBusiness(playerid) {
	new propid = Player_Spawn[playerid][SpawnID];
	PutPlayerInProperty(playerid, propid);
}

stock loadProps()
{
	mysql_query(MySQL_Handle, "SELECT pr.*, p.nome 'donoNome' FROM propriedades pr LEFT JOIN player p ON p.id = pr.dono ORDER BY id ASC");

	new rows = MYSQL_GetRowsCount();
	for (new prop; prop != rows; prop++)
	{
		if(!MYSQL_IsNull(prop, "dono")) {
			PropInfo[prop][eOwnerID] = MYSQL_GetInt(prop, "dono");
			format(PropInfo[prop][eOwner], MAX_PLAYER_NAME, MYSQL_GetString(prop, "donoNome"));
		}
		else {
			PropInfo[prop][eOwnerID] = -1;
			format(PropInfo[prop][eOwner], MAX_PLAYER_NAME, "Ninguém");
		}
		
		PropInfo[prop][ePrice] = MYSQL_GetInt(prop, "preco");
		PropInfo[prop][prop_type] = MYSQL_GetInt(prop, "tipo");
		PropInfo[prop][eTill] = MYSQL_GetInt(prop, "cofre");
		TimeParse(MYSQL_GetString(prop, "vencimento"), ISO6801_DATE, PropInfo[prop][eVencimento]);
		PropInfo[prop][eLock] = MYSQL_GetInt(prop, "trancada");
		PropInfo[prop][eDespesas] = MYSQL_GetInt(prop, "despesas");
		PropInfo[prop][eRobbed] = MYSQL_GetInt(prop, "roubada");

		PropInfo[prop][eInsumos] = MYSQL_GetInt(prop, "insumos");
		PropInfo[prop][eMaxInsumos] = MYSQL_GetInt(prop, "maxInsumos");
		PropInfo[prop][eInsumosReq] = MYSQL_GetInt(prop, "insumosRequisitados");
		PropInfo[prop][ePrecoInsumo] = MYSQL_GetInt(prop, "precoInsumo");

		PropInfo[prop][eLoaded] = true;

		if (PropInfo[prop][ePrice] < 1) 
			PropInfo[prop][ePrice] = 4500000;

		atualizarPropText(prop);

		if (PropInfo[prop][eVencimento] > Now() + Days:100)
		{
			PropInfo[prop][eVencimento] = Now() + Days:5;
			savePropertie(prop);
		}
	}
}

stock saveProps() {
	for ( new prop; prop != unid; prop++ ) {
        savePropertie(prop);
	}
}

stock CheckLimitProps(playerid)
{
	if (PlayerInfo[playerid][pVIP] < SOCIO_PREMIUM && CountProperties(playerid) >= 1) return false;

	if (PlayerInfo[playerid][pVIP] < SOCIO_EXTREME && CountProperties(playerid) >= 2) return false;

	if (CountProperties(playerid) > 3) return false;

	return 1;
}

stock savePropertie(prop)
{
	if(PropInfo[prop][eLoaded]) {
		new prop_query[600], dono[MAX_PLAYER_NAME] = "NULL", date[30];

		TimeFormat(PropInfo[prop][eVencimento], ISO6801_DATE, date);

		if(PropInfo[prop][eOwnerID] != -1)
			format(dono, 25, "%d", PropInfo[prop][eOwnerID]);

		mysql_format(MySQL_Handle, prop_query, sizeof(prop_query), "UPDATE propriedades SET dono=%s, preco=%d, tipo=%d, cofre=%d, vencimento='%s', trancada='%d', \
			despesas=%d, roubada=%d, insumos=%d, precoInsumo=%d, maxInsumos=%d, insumosRequisitados=%d WHERE id = %d", dono, PropInfo[prop][ePrice], 
			PropInfo[prop][prop_type], PropInfo[prop][eTill], date, PropInfo[prop][eLock], PropInfo[prop][eDespesas], PropInfo[prop][eRobbed], PropInfo[prop][eInsumos], 
			PropInfo[prop][ePrecoInsumo], PropInfo[prop][eMaxInsumos], PropInfo[prop][eInsumosReq], prop);
		mysql_tquery(MySQL_Handle, prop_query);
	}
}

stock GetPropriedadeProxima(playerid) {
	for (new i = 0; i < unid; i++)
		if (PropInfo[i][eLoaded] && PlayerToPoint(10.0, playerid, properties[i][eEntX], properties[i][eEntY], properties[i][eEntZ]))
			return i;

	return -1;
}

stock GetPropriedadeLucro(propid) {
	if(PropInfo[propid][eLoaded]) {
		new lucroBase = 400 + random(300);
		if(!IsPointInLosSantos(properties[propid][eEntX], properties[propid][eEntY])) {
			lucroBase += 200;
		}
		return lucroBase;
	}
	return 0;
}

CALLBACK:LoadProperties() {
	unid = 0;

	CreateProperties();
	loadProps();

	return unid;
}

hook OnPlayerPickUpPickup(playerid, pickupid)
{
	lastPickup[playerid] = pickupid;

	return 1;
}