//------------------------------------ Sistema de caixa eletrônico ---------------------------------------

#if defined _INC_caixa_eletronico
	#endinput
#endif
#define _INC_caixa_eletronico

#include < YSI_Coding\y_hooks >

#define 			MAX_PICKUPS_ROUBO       		15              						// Máximo de dinheiro que será espalhado no chão
#define             MAX_CAIXAS                      19                                      // Máximo de caixas eletrônicos na cidade
#define             CaixaPlayerProximo				GetPlayerCaixa(playerid, 3.0)           // Caixa próximo ao player (distância 3.0)
#define             caixaStrongCarProx				GetPlayerCaixa(playerid, 10.0)          // Caixa próximo ao carro forte (distância 10.0)

enum caixaInfo {

	bool:caixaRoubado,
	caixaDinheiro,
	caixaObject,
	caixaPickup,
	Text3D:caixaText,
	caixaPickups,
    caixaObjectBomba,
};

new
	CaixaInfo[MAX_CAIXAS][caixaInfo],
	pickupsRouboCaixa[MAX_CAIXAS][MAX_PICKUPS_ROUBO]
;

new Float:UltimaCaixaRoubada[3];

new bool:TendoRoubo;
new TransferenciaID		[MAX_PLAYERS];

new Float:RdonPickups[][] =
{
	{0.1},{0.2},{0.3},{0.4},
	{0.5},{0.6},{0.7},{0.8},
	{0.9},{1.0},{1.2},{1.3},
	{1.4},{1.5},{1.6},{1.7},
	{1.8},{1.9},{2.0},{2.1},
	{2.2},{2.3},{2.4},{2.5},
	{2.6},{2.7},{2.8},
	//
	{-0.1},{-0.2},{-0.3},{-0.4},
	{-0.5},{-0.6},{-0.7},{-0.8},
	{-0.9},{-1.0},{-1.2},{-1.3},
	{-1.4},{-1.5},{-1.6},{-1.7},
	{-1.8},{-1.9},{-2.0},{-2.1},
	{-2.2},{-2.3},{-2.4},{-2.5},
	{-2.6},{-2.7},{-2.8}
};

// ----------------------------------------------------------------------------------------------------------------

hook OnGameModeInit() 
{
	TendoRoubo = false;

	CreateCaixa(1, 2942, 1928.69604, -1784.04639, 13.15720,   0.00000, 0.00000, 88.44680);
	CreateCaixa(2, 2942, 1831.94666, -1405.75806, 12.99174,   0.00000, 0.00000, 176.68292);
	CreateCaixa(3, 2942, 1363.55298, -1750.63855, 13.17531,   0.00000, 0.00000, 271.14401);
	CreateCaixa(4, 2942, 1070.77478, -1881.54370, 13.16587,   0.00000, 0.00000, 271.18671);
	CreateCaixa(5, 2942, 833.72095, -1384.92908, 13.07656,   0.00000, 0.00000, 0.00000);
	CreateCaixa(6, 2942, 1797.89026, -1190.45325, 23.54218,   0.00000, 0.00000, 182.18976);
	CreateCaixa(7, 2942, 2209.10791, -1141.88208, 25.39645,   0.00000, 0.00000, 88.60888);
	CreateCaixa(8, 2942, 2313.50586, -1373.55334, 23.69597,   0.00000, 0.00000, 271.93027);
	CreateCaixa(9, 2942, 2351.94897, -1548.61584, 23.54486,   0.00000, 0.00000, 264.68781);
	CreateCaixa(10, 2942, 2243.18921, -1722.77673, 13.15102,   0.00000, 0.00000, 0.00000);
	CreateCaixa(11, 2942, 1940.07886, -2113.70752, 13.30774,   0.00000, 0.00000, 89.08496);
	CreateCaixa(12, 2942, 1677.4283, -2278.0093, 13.5403,   0.00000, 0.00000, 88.2283); // Caixa Respawn Civil
	CreateCaixa(13, 2942, 365.37585, -1354.45508, 14.12511,   0.00000, 0.00000, 29.47749);
	CreateCaixa(14, 2942, 1296.89661, -1158.12537, 23.39852,   0.00000, 0.00000, 177.93507);
	CreateCaixa(15, 2942, 1492.36804, -1022.19519, 23.41977,   0.00000, 0.00000, 0.00000);
	CreateCaixa(16, 2942, 1830.88367, -1071.68689, 23.48169,   0.00000, 0.00000, 269.40909);
	CreateCaixa(17, 2942, 1863.66504, -1270.39185, 13.16138,   0.00000, 0.00000, 182.03978);
	CreateCaixa(18, 2942, 2096.18994, 1443.96680, 10.43300,   0.00000, 0.00000, 268.02911);
	CreateCaixa(19, 2942, -1970.42078, 309.32761, 34.82810,   0.00000, 0.00000, 000.00000);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) 
{
	if (newkeys & KEY_SECONDARY_ATTACK)
	{
		if (!IsPlayerInAnyVehicle(playerid))
		{
			if (CaixaPlayerProximo) 
				callcmd::banco(playerid);
		}
	}
	return 1;
}

stock Float:GetXYInFrontOfCaixa(objectid, &Float:q, &Float:w, Float:distance) {

	new
		Float:a,
		Float:rotx,
		Float:roty
	;

	GetDynamicObjectPos(objectid, q, w, a);
	GetDynamicObjectRot(objectid, rotx, roty, a);

	q -= (distance * floatsin(-a, degrees));
	w -= (distance * floatcos(-a, degrees));

	return a;
}

static CreateCaixa(caixaid, objectid, Float:x, Float:y, Float:z, Float:rotx, Float:roty, Float:rotz)
{
	if (caixaid >= MAX_CAIXAS) return false;

    CaixaInfo[caixaid][caixaObject] = CreateDynamicObject(objectid, x, y, z, rotx, roty, rotz);
    CaixaInfo[caixaid][caixaDinheiro] = 5000;
    CaixaInfo[caixaid][caixaRoubado] = false;

   	new Float:pX, Float:pY, Float:pZ, str[104];

	GetDynamicObjectPos(CaixaInfo[caixaid][caixaObject], pX, pY, pZ);
	GetXYInFrontOfCaixa(CaixaInfo[caixaid][caixaObject], pX, pY, 1.0);
	CaixaInfo[caixaid][caixaPickup] = CreateDynamicPickup(1274, 1, pX, pY, pZ);

	format(str, sizeof str, "Caixa Eletrônico\n{7D8084}Aperte '{FFFFFF}ENTER{7D8084}' para usar\nDinheiro no caixa: {00AA00}$%s", getFormatText(CaixaInfo[caixaid][caixaDinheiro]));
	CaixaInfo[caixaid][caixaText] = Create3DTextLabel(str, 0xDBDCE0FF, pX, pY, pZ, 15.0, 0);

	return true;
}

static GetPlayerCaixa(playerid, Float:range)
{
	new
		Float:px,
		Float:py,
		Float:pz
	;

	for(new caixa = 1; caixa < MAX_CAIXAS; caixa++)
	{
	    GetDynamicObjectPos(CaixaInfo[caixa][caixaObject], px, py, pz);

	    if (IsPlayerInRangeOfPoint(playerid, range, px, py, pz)) return caixa;
	}
	return 0;
}

stock PegarCaixaProximo(playerid)
{
	new cid = -1, Float:dis = 999999.999;
	new Float:x, Float:y, Float:z;
	for(new i = 1; i < MAX_CAIXAS; i++)
	{
		GetDynamicObjectPos(CaixaInfo[i][caixaObject], x, y, z);
  		if(GetPlayerDistanceFromPoint(playerid, x, y, z) < dis)
 		{
    		dis = GetPlayerDistanceFromPoint(playerid, x, y, z);
			cid = i;
		}
	}
    return cid;
}

stock AbastecerCaixasEletronicos() {

	new string[110],
		total = 0;

    for(new caixa = 1; caixa < MAX_CAIXAS; caixa++)
    {
		new value = 5000 + random(15000);
	    if ((CaixaInfo[caixa][caixaDinheiro]+value) < 120000 && !CaixaInfo[caixa][caixaRoubado])
		{
			CaixaInfo[caixa][caixaDinheiro] += value;
			total += value;

	    	format(string, sizeof string, "Caixa Eletrônico\n{7D8084}Aperte '{FFFFFF}ENTER{7D8084}' para usar\nDinheiro no caixa: {00AA00}$%s", getFormatText(CaixaInfo[caixa][caixaDinheiro]));
			Update3DTextLabelText(CaixaInfo[caixa][caixaText], 0xDBDCE0FF, string);
		}
	}
	removerDinheiroGoverno(total);
}

CMD:consertarcaixa(playerid)
{
	if(!IsACop(playerid)) return SendClientMessage(playerid, -1, "Você não é um policial!");

	new
		caixa_id
	;
	if(!(caixa_id=CaixaPlayerProximo))return SendClientMessage(playerid, -1, "Você não está perto de nenhum caixa eletronico");

	if(CaixaInfo[caixa_id][caixaRoubado])
	{
		new
			Float:px, Float:py, Float:pz,
			Float:rx, Float:ry, Float:rz
			;

		foreach(new i : Player)
		{
			if(GetPVarInt(i, "Consertando") == caixa_id)
				return SendClientMessage(playerid, -1, "Alguem já está consertando este caixa!");
		}

		GetDynamicObjectPos(CaixaInfo[caixa_id][caixaObject], px, py, pz);
		GetDynamicObjectRot(CaixaInfo[caixa_id][caixaObject], rx, ry, rz);
		GetXYInFrontOfCaixa(CaixaInfo[caixa_id][caixaObject], px, py, 0.9);
		SetPlayerPos(playerid, px, py, pz);
		SetPlayerFacingAngle(playerid, rz);

		SetPVarInt(playerid, "Consertando", caixa_id);

		ApplyAnimation(playerid,"BOMBER","BOM_Plant_Loop",4.0,1,0,0,0,0);
		SetTimerEx("ConsertarCaixa", 40*1000, false, "dd", playerid, CaixaPlayerProximo);

		SendClientMessage(playerid, GetPlayerColor(playerid), " - Você está tentando consertar este caixa eletrônico, aguarde 40 segundos...");
		GameTextForPlayer(playerid, "~g~Consertando, aguarde...", 5000, 1);
	}
	else SendClientMessage(playerid, -1, "Este caixa não foi roubado!");
	return 1;
}

hook OP_PickUpDynamicPickup(playerid, pickupid)
{
	if (!Player_GetBusyHand(playerid, RIGHT_HAND) ||
		!Player_GetBusyHand(playerid, LEFT_HAND)) {
	    for(new i = 1; i < MAX_CAIXAS; ++i)
	    {
	        if(!CaixaInfo[i][caixaRoubado]) continue;
	        for(new p; p < MAX_PICKUPS_ROUBO; p++)
	        {
	        	if(pickupid == pickupsRouboCaixa[i][p])
				{
    				if(IsACop(playerid))
					{
						ShowPlayerMessage(playerid, "Use ~g~/consertarcaixa ~w~para conserta-lo!", 3000);
						continue;
					}
					new KEY:actions, KEY:ud, KEY:lr;
				    GetPlayerKeys(playerid, actions, ud, lr);
				    if (actions & KEY_YES)
				    {
						GranaRoubo(playerid, i);
						DestroyDynamicPickup(pickupid);
						pickupsRouboCaixa[i][p] = -1;
					}
					else
					{
						ShowPlayerBaloonInfo(playerid, "Aperte ~p~Y ~w~para pegar a grana do chao!", 8000, true);
					}
					return 1;
				}
			}
		}
	}

	return 1;
}

CALLBACK:ConsertarCaixa(playerid, caixa_id)
{
	if(CaixaPlayerProximo != GetPVarInt(playerid, "Consertando"))
	{
		SetPVarInt(playerid, "Consertando", 0);
		return GameTextForPlayer(playerid, "~r~Voce nao esta no caixa que estava consertando", 5000, 1);
	}
	if(CaixaInfo[caixa_id][caixaRoubado] && IsPlayerConnected(playerid))
	{
		new
			string[105],
			valorGanho = CaixaInfo[CaixaPlayerProximo][caixaDinheiro]/4
		;

		format(string, sizeof string, "Você consertou o caixa eletrônico e recebeu {00AA00}$%s {FFFFFF}do governo.", getFormatText(valorGanho));
		SendClientMessage(playerid, -1, string);

		CaixaInfo[CaixaPlayerProximo][caixaDinheiro] -= valorGanho;
		Player_AddMoney(playerid, valorGanho);

		format(string, sizeof string, "<< COPOM >> %s - %s, %s: consertou um caixa eletrônico da cidade.", GetOrgName(GetPlayerOrg(playerid)), GetPlayerCargo(playerid), PlayerName[playerid]);
		SendCopMessage(TEAM_BLUE_COLOR, string);

		format(string, sizeof string, "Caixa Eletrônico\n{7D8084}Aperte '{FFFFFF}ENTER{7D8084}' para usar\nDinheiro no caixa: {00AA00}$%s", getFormatText(CaixaInfo[CaixaPlayerProximo][caixaDinheiro]));
		Update3DTextLabelText(CaixaInfo[CaixaPlayerProximo][caixaText], 0xDBDCE0FF, string);

		ClearAnimations(playerid);

		RestoreCaixa(caixa_id);
		SetPVarInt(playerid, "Consertando", 0);
	}
	return 1;
}

CMD:banco(playerid)
{
	new caixaid = CaixaPlayerProximo;
	if (caixaid)
	{
		if (CaixaInfo[CaixaPlayerProximo][caixaRoubado]) 
			return SendClientMessage(playerid, -1, "Este caixa eletronico foi roubado por assaltantes recentemente.");
		
		if(caixaid == 12)
			ShowPlayerDialog(playerid, 172, DIALOG_STYLE_LIST, "Caixa Eletrônico","Consultar saldo\nSacar\nDepositar\nTransferência", "Confirmar", "Cancelar");
		else
			ShowPlayerDialog(playerid, 172, DIALOG_STYLE_LIST, "Caixa Eletrônico","Consultar saldo\nSacar\nDepositar\nTransferência\n{FF0000}ROUBAR", "Confirmar", "Cancelar");
	}
	return 1;
}

CMD:roubar(playerid)
{
	//if(IsPlayerCongelado(playerid))return SendClientMessage(playerid, -1, "Você não pode usar este comando estando congelado !");
	if(!OrgsRoubo(playerid))
	{
		SendClientMessage(playerid,-1, "Você não pode roubar caixas eletronicos !");
		return true;
	}

	new
		caixa_id
	;

	if (GetPlayerExplosives(playerid) < 1)
		return SendClientMessage(playerid, -1, "Você não tem nenhum explosivo.");

	if (!GetPlayerHoldingExplosive(playerid))
		return SendClientMessage(playerid, -1, "Você não está segurando um explosivo. (Use: /explosivo pegar)");

	if(!(caixa_id=CaixaPlayerProximo))return SendClientMessage(playerid, -1, "Você não está perto de nenhum caixa eletronico");
	if(CaixaInfo[caixa_id][caixaRoubado])return SendClientMessage(playerid, -1, "*Este caixa eletronico ja foi roubado a pouco tempo.");
	if(TendoRoubo && !TendoRoubo) return SendClientMessage(playerid, -1, "Ja roubaram um caixa eletronico a pouco tempo, espere um pouco para roubar outro.");
	if(Staff_GetWorking(playerid))
		return SendClientMessage(playerid, -1, "Você não pode roubar em modo trabalho!");

	new
		Float:px, Float:py, Float:pz,
		Float:rx, Float:ry, Float:rz,
		string[256]
		;


	GetDynamicObjectPos(CaixaInfo[caixa_id][caixaObject], px, py, pz);
	GetDynamicObjectRot(CaixaInfo[caixa_id][caixaObject], rx, ry, rz);
	GetXYInFrontOfCaixa(CaixaInfo[caixa_id][caixaObject], px, py, 0.9);

	UltimaCaixaRoubada[0] = px;
	UltimaCaixaRoubada[1] = py;
	UltimaCaixaRoubada[2] = pz;

	SetPVarInt(playerid, "player_TakingMoney", 0);
	Player_GetBusyHand(playerid, RIGHT_HAND);
	Player_GetBusyHand(playerid, LEFT_HAND);

	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	SetPlayerPos(playerid, px, py, pz);
	SetPlayerFacingAngle(playerid, rz);

	ApplyAnimation(playerid,"BOMBER","BOM_Plant_Loop",4.0,1,0,0,0,0);
	SetTimerEx("RoubarCaixa", 20*1000, false, "dd", playerid, CaixaPlayerProximo);

	SetPVarInt(playerid, "VarPlayerOcupado", 	1);
	SetPVarInt(playerid, "VarRouboCaixa", gettime()+5*60);

	if (!PlayerInfo[playerid][mAgressivo]) {
		SetPlayerAgressivo(playerid);
		SendClientMessage(playerid, COLOR_LIGHTRED, "Você está roubando o caixa seu personagem está agressivo.");
	}

	CaixaInfo[caixa_id][caixaRoubado] = true;

	new MapZone:zone = GetPlayerMapZone(playerid);
	new zone_name[MAX_MAP_ZONE_NAME];

	GetMapZoneName(zone, zone_name);

	if(GetPlayerOrg(playerid) == 0)
		format(string, sizeof string, "<< Roubo: %s está tentando roubar o caixa eletronico de %s >>", PlayerName[playerid], zone_name);
	else
		format(string, sizeof string, "<< Roubo: %s e %s %s estão tentando roubar o caixa eletronico de %s >>", PlayerName[playerid], GetOrgArticle(GetPlayerOrg(playerid)), GetOrgName(GetPlayerOrg(playerid)), zone_name);
	SendCopMessage(COLOR_LIGHTRED, string);
	SendClientMessageInRange(30.0, playerid, string, COLOR_LIGHTRED,COLOR_LIGHTRED,COLOR_LIGHTRED,COLOR_LIGHTRED,COLOR_LIGHTRED);
	SetPlayerCriminal(playerid, 255, "Roubo a caixa eletronico");
	SendCopMessage(COLOR_LIGHTRED, "[Policiais]: USE: /localizarcaixa para saber onde foi o roubo.");
	SendClientMessage(playerid, COLOR_GRAD, "*Você está colocando uma bomba no caixa eletronico, aguarde...");

	GameTextForPlayer(playerid, "~r~plantando bomba...", 5000, 1);

	ShowPlayerBaloonInfo(playerid, "Espere a bomba ser plantada, depois afaste-se", 5000);

	return 1;
}

CALLBACK:AlarmCaixa(caixa_id)
{
    new Float:px, Float:py, Float:pz;

	if (!CaixaInfo[caixa_id][caixaRoubado]) {

		SoundToAll(0);
		for(new i = 1; i < MAX_CAIXAS; i ++) {

		    if(CaixaInfo[i][caixaRoubado])
		    {
			    GetDynamicObjectPos(CaixaInfo[i][caixaObject], px, py, pz);
				SoundInRange(9200, 20.0, px, py, pz);
		    }
		}
		return 1;
	}

    GetDynamicObjectPos(CaixaInfo[caixa_id][caixaObject], px, py, pz);
	SoundInRange(9200, 20.0, px, py, pz);

	SetTimerEx("AlarmCaixa", 5000, false, "d", caixa_id);
	return 1;
}

CALLBACK:ExplodirCaixa(caixa_id)
{
	new Float:px, Float:py, Float:pz,
		Float:rx, Float:ry, Float:rz;

	new str[200];

	format(str, sizeof str, "Caixa Eletrônico\n{FF0000}CAIXA DESTRUIDO\n{7D8084}Dinheiro despejado: {00AA00}$%s", getFormatText(CaixaInfo[caixa_id][caixaDinheiro]));
	Update3DTextLabelText(CaixaInfo[caixa_id][caixaText], 0xDBDCE0FF, str);

	GetDynamicObjectPos(CaixaInfo[caixa_id][caixaObject], px, py, pz);
	GetDynamicObjectRot(CaixaInfo[caixa_id][caixaObject], rx, ry, rz);
	CreateExplosion(px, py, pz, 10, 2.0);
	DestroyDynamicObject(CaixaInfo[caixa_id][caixaObjectBomba]);
	DestroyDynamicObject(CaixaInfo[caixa_id][caixaObject]);
	CaixaInfo[caixa_id][caixaObject] = CreateDynamicObject(2943, px, py, pz, rx, ry, rz);

	AlarmCaixa(caixa_id);

//--------- Jogar grana no chão --

	GetXYInFrontOfCaixa(CaixaInfo[caixa_id][caixaObject], px, py, 3.1);

	for(new i; i < MAX_PICKUPS_ROUBO; ++i) {
		pickupsRouboCaixa[caixa_id][i] = CreateDynamicPickup(1212, 23, px + (RdonPickups[random(sizeof(RdonPickups))][0]), py - (RdonPickups[random(sizeof(RdonPickups))][0]), pz - 0.3);
	}

	CaixaInfo[caixa_id][caixaPickups] = MAX_PICKUPS_ROUBO;

	SetTimerEx("RestoreCaixa", 60000*20, false, "d", caixa_id);

	return 1;
}
CALLBACK:RestoreCaixa(caixa_id)
{
    if(CaixaInfo[caixa_id][caixaRoubado])
    {
		new Float:px, Float:py, Float:pz,
			Float:rx, Float:ry, Float:rz,
			str[104];

	    CaixaInfo[caixa_id][caixaRoubado] = false;

	    format(str, sizeof str, "Caixa Eletrônico\n{7D8084}Aperte '{FFFFFF}ENTER{7D8084}' para usar\nDinheiro no caixa: {00AA00}$%s", getFormatText(CaixaInfo[caixa_id][caixaDinheiro]));
		Update3DTextLabelText(CaixaInfo[caixa_id][caixaText], 0xDBDCE0FF, str);

		GetDynamicObjectPos(CaixaInfo[caixa_id][caixaObject], px, py, pz);
		GetDynamicObjectRot(CaixaInfo[caixa_id][caixaObject], rx, ry, rz);

		DestroyDynamicObject(CaixaInfo[caixa_id][caixaObject]);
		CaixaInfo[caixa_id][caixaObject] = CreateDynamicObject(2942, px, py, pz, rx, ry, rz);

		for(new i; i < MAX_PICKUPS_ROUBO; ++i)
		{
		    DestroyDynamicPickup(pickupsRouboCaixa[caixa_id][i]);
		}
	}
	return true;
}

stock GranaRoubo(playerid, caixa_id)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	SetPVarFloat(playerid, "RouboX", x);
	SetPVarFloat(playerid, "RouboY", y);
	SetPVarFloat(playerid, "RouboZ", z);

    SetPVarInt(playerid, "player_TakingMoney", 1);
    ApplyAnimation(playerid,"ROB_BANK","CAT_Safe_Rob",4.1,1,0,0,0,0);

	SetPVarInt(playerid, "VarRouboCaixa", gettime()+5*60);

	if (!PlayerInfo[playerid][mAgressivo]) {
		SetPlayerAgressivo(playerid);
		SendClientMessage(playerid, COLOR_LIGHTRED, "Você está roubando o dinheiro caixa seu personagem está agressivo.");
	}

    SetTimerEx(#ApplyAnim, 500, false, "i", playerid);
    SetTimerEx("PegarGrana", 10000, false, "id", playerid, caixa_id);
    SetPlayerAttachedObject(playerid, Slot_Explosivo, 1550,1,-0.068000,0.382000,-0.109999,-91.699996,101.200012,-149.300003,1.000000,1.000000,1.000000);
}

CALLBACK:ApplyAnim(playerid)
	return ApplyAnimation(playerid,"ROB_BANK","CAT_Safe_Rob",4.1,1,0,0,0,0);

CALLBACK:PegarGrana(playerid, caixa_id)
{

	SetPVarInt(playerid, "player_TakingMoney", 0);
    ClearAnimations(playerid);
    if (!CaixaInfo[caixa_id][caixaRoubado]) return true;

    if (!IsPlayerInRangeOfPoint(playerid, 5.0, GetPVarFloat(playerid, "RouboX"),GetPVarFloat(playerid, "RouboY"),GetPVarFloat(playerid, "RouboZ"))) {
	    RemovePlayerAttachedObject(playerid, Slot_Explosivo);
	    return GameTextForPlayer(playerid, "~r~Voce nao esta no local do roubo", 5000, 1);
	}

	new
		str[200],
		picks = CaixaInfo[caixa_id][caixaPickups]
	;

	if (picks == 0)
		Player_AddMoney(playerid, CaixaInfo[caixa_id][caixaDinheiro]);
	else
		Player_AddMoney(playerid, CaixaInfo[caixa_id][caixaDinheiro]/picks);

	if (!Player_GetWanted(playerid)) SetPlayerCriminal(playerid, 255, "Roubo de caixa eletrônico");

	if (picks == 0)
	{
		format(str, sizeof str, "Você pegou {00AA00}$%s {FFFFFF}do caixa eletrônico.", getFormatText(CaixaInfo[caixa_id][caixaDinheiro]));
		CaixaInfo[caixa_id][caixaDinheiro] -= (CaixaInfo[caixa_id][caixaDinheiro]);
	}
	else
	{
		format(str, sizeof str, "Você pegou {00AA00}$%s {FFFFFF}do caixa eletrônico.", getFormatText(CaixaInfo[caixa_id][caixaDinheiro]/picks));
		CaixaInfo[caixa_id][caixaDinheiro] -= (CaixaInfo[caixa_id][caixaDinheiro]/picks);
	}

	SendClientMessage(playerid, -1, str);

 	format(str, sizeof str, "Caixa Eletrônico\n{FF0000}CAIXA DESTRUIDO\n{7D8084}Dinheiro despejado: {00AA00}$%s", getFormatText(CaixaInfo[caixa_id][caixaDinheiro]));
	Update3DTextLabelText(CaixaInfo[caixa_id][caixaText], 0xDBDCE0FF, str);

	CaixaInfo[caixa_id][caixaPickups] --;

	SetPlayerAttachedObject(playerid, Slot_Explosivo, 1550, 1, 0.000000, -0.313611, 0.021003, 0.445490, 86.754409, 355.370239, 0.926815, 1.000000, 1.000000);

	KillTimer(GetPVarInt(playerid, "ROBj"));

	SetPVarInt(playerid, "ROBj", SetTimerEx("RObject", 2*60000, false, "d", playerid));
	return 0;
}

CALLBACK:RObject(playerid)
{
	RemovePlayerAttachedObject(playerid, Slot_Explosivo);
	SetPVarInt(playerid, "ROBj", -1);
}

CMD:consertarcaixas(playerid)
{
	if (Admin_GetNivel(playerid) < GERENTE) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new string[68+MAX_PLAYER_NAME];

	for(new caixaID = 1; caixaID < MAX_CAIXAS; ++caixaID)
		restoreCashMachine(caixaID);

	format(string, sizeof string, "AdmCmd: O admin %s consertou todos os caixas eletrônicos da cidade.", PlayerName[playerid]);
	return SendClientMessageToAll(COLOR_YELLOW, string);
}


CALLBACK:restoreCashMachine(caixa_id)
{
    if (!CaixaInfo[caixa_id][caixaRoubado]) return false;

	new Float:px, Float:py, Float:pz,
		Float:rx, Float:ry, Float:rz,
		str[104];

    CaixaInfo[caixa_id][caixaRoubado] = false;

	format(str, sizeof str, "Caixa Eletrônico\n{7D8084}Aperte '{FFFFFF}ENTER{7D8084}' para usar\nDinheiro no caixa: {00AA00}$%s", getFormatText(CaixaInfo[caixa_id][caixaDinheiro]));
	Update3DTextLabelText(CaixaInfo[caixa_id][caixaText], 0xDBDCE0FF, str);

	GetDynamicObjectPos(CaixaInfo[caixa_id][caixaObject], px, py, pz);
	GetDynamicObjectRot(CaixaInfo[caixa_id][caixaObject], rx, ry, rz);

	DestroyDynamicObject(CaixaInfo[caixa_id][caixaObject]);
	CaixaInfo[caixa_id][caixaObject] = CreateDynamicObject(2942, px, py, pz, rx, ry, rz);

	for(new caixaID; caixaID < MAX_PICKUPS_ROUBO; ++caixaID)
	    DestroyDynamicPickup(pickupsRouboCaixa[caixa_id][caixaID]);

	return true;
}

CMD:localizarcaixa(playerid)
{
	if(IsACop(playerid))
	{
		SetPlayerCP(playerid, 58);
		SetPlayerCheckpoint(playerid, UltimaCaixaRoubada[0], UltimaCaixaRoubada[1], UltimaCaixaRoubada[2], 2.0);
		ShowPlayerMessage(playerid, "~w~Caixa eletronico ~r~marcado ~w~ no mapa", 5000);
	}
	return 1;
}

stock LocationCaixaEletronico(playerid)
{
	if (!Player_Logado(playerid)) return true;

	new
		string[128],
		Float:x,
		Float:y,
		Float:z,
		MapZone:zone,
		zone_name[MAX_MAP_ZONE_NAME]
	;

	MEGAString[0] = EOS;

	strcat(MEGAString, "{FFFF00}Caixa eletrônico mais próximo «\n");

	for(new i = 1; i < MAX_CAIXAS; ++i) {

		GetDynamicObjectPos(CaixaInfo[i][caixaObject], x, y, z);

		zone = GetMapZoneAtPoint2D(x, y);
		GetMapZoneName(zone, zone_name);

		format(string, sizeof string, "Caixa eletrônico de %s\n", zone_name);
		strcat(MEGAString, string);
	}
	ShowPlayerDialog(playerid, 4901, DIALOG_STYLE_LIST, "Caixas Eletronicos", MEGAString, #Localizar, #Voltar);
	return true;
}

CALLBACK:RoubarCaixa(playerid, caixa_id)
{
	if(!CaixaPlayerProximo)
	{
		CaixaInfo[caixa_id][caixaRoubado] = false;
		return SendClientMessage(playerid, -1, "*Você não está perto do local de roubo.");
	}

	TendoRoubo = true;
	SetTimer(#LiberarRoubo, 3*60000, false);

	new Float:px, Float:py, Float:pz,
		Float:rx, Float:ry, Float:rz
	;

	SetPVarInt(playerid, "VarPlayerOcupado", 	0);

	PlayerInfo[playerid][pExplosives] = 0;
	GetDynamicObjectPos(CaixaInfo[caixa_id][caixaObject], px, py, pz);
	GetDynamicObjectRot(CaixaInfo[caixa_id][caixaObject], rx, ry, rz);
	GetXYInFrontOfCaixa(CaixaInfo[caixa_id][caixaObject], px, py, 0.3);

	SetPlayerExplosive(playerid, false);
	RemovePlayerAttachedObject(playerid, Slot_Explosivo);
	CaixaInfo[caixa_id][caixaObjectBomba] = CreateDynamicObject(1654, px, py, pz, 0.0, 0.0, rz);
	SetTimerEx("ExplodirCaixa", 10000, false, "d", caixa_id);

	SendClientMessage(playerid, COLOR_LIGHTRED, "*Você plantou uma bomba, agora afaste-se e espere explodir!");
	ShowPlayerMessage(playerid, "~r~Afaste-se do caixa eletronico", 5000);
	ClearAnimations(playerid, SYNC_ALL);

	CheckConquista(playerid, Conquista_Roubo);
	return 0;
}

CALLBACK:LiberarRoubo()
	return TendoRoubo = false;

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) 
{
    if(dialogid == 4901)
	{
	    if (!response)
			return callcmd::gps(playerid);

		if (listitem == -1) return 1;

		new Float:x, Float:y, Float:z;

		if(listitem == 0)
		{
		    new id = PegarCaixaProximo(playerid);
		    GetDynamicObjectPos(CaixaInfo[id][caixaObject], x, y, z);

			new MapZone:zone = GetMapZoneAtPoint2D(x, y);
			new zone_name[MAX_MAP_ZONE_NAME];
			GetMapZoneName(zone, zone_name);

			SetPlayerCheckpoint(playerid, x, y, z, 5.0);
			SetPlayerCP(playerid, CP_NULL);
			SendMsgF(playerid, COLOR_YELLOW, "[GPS]: Foi marcado no mapa o Caixa Eletrônico mais próximo de você (%s)", zone_name);

		    return 1;
		}

		GetDynamicObjectPos(CaixaInfo[listitem-1][caixaObject], x, y, z);
		SetPlayerCheckpoint(playerid, x, y, z, 5.0);
		SetPlayerCP(playerid, CP_NULL);

		new MapZone:zone = GetMapZoneAtPoint2D(x, y);
		new zone_name[MAX_MAP_ZONE_NAME];
		GetMapZoneName(zone, zone_name);

		SendMsgF(playerid, COLOR_YELLOW,  "[GPS]: Foi marcado no mapa o Caixa Eletrônico de %s.", zone_name);

	    return true;
	}
    else if (dialogid == 172)
	{
  		if (response)
		{
  		    new caixa_string[65 + MAX_PLAYER_NAME];

			MEGAString[0] = EOS;

   			switch (listitem)
	   		{
	   		    case 0:
	   			{
	   			    SendClientMessage(playerid, -1, "=============================================");
					SendMsgF(playerid, COLOR_WHITE,  "Seu saldo atual no banco é de {00AA00}$%s", getFormatText(PlayerInfo[playerid][pConta]));
				   	SendClientMessage(playerid, -1, "=============================================");
	   			}
	     		case 1:
				{
				 	format(caixa_string, sizeof(caixa_string), "\n{DBDCE0}Conta bancária de %s\nSeu saldo: {00AA00}$%s\n\n", PlayerName[playerid], getFormatText(PlayerInfo[playerid][pConta]));
				   	strcat(MEGAString, caixa_string);
				   	strcat(MEGAString, "{7D8084}Digite abaixo o valor que deseja sacar no caixa:\n");

				  	ShowPlayerDialog(playerid, 172 + 1, DIALOG_STYLE_INPUT, "Efetuar saque", MEGAString, "Confirmar", "Retornar");
		 		}
	    		case 2:
				{
				 	format(caixa_string, sizeof(caixa_string), "\n{DBDCE0}Conta bancária de %s\nSeu saldo: {00AA00}$%s\n\n", PlayerName[playerid], getFormatText(PlayerInfo[playerid][pConta]));
				   	strcat(MEGAString, caixa_string);
				   	strcat(MEGAString, "{7D8084}Digite abaixo o valor que deseja depositar no caixa:\n");

				  	ShowPlayerDialog(playerid, 172 + 2, DIALOG_STYLE_INPUT, "Efetuar depósito", MEGAString, "Confirmar", "Retornar");
				}
	      		case 3:
		  		{
				 	format(caixa_string, sizeof(caixa_string), "\n{DBDCE0}Conta bancária de %s\nSeu saldo: {00AA00}$%s\n\n", PlayerName[playerid], getFormatText(PlayerInfo[playerid][pConta]));
				   	strcat(MEGAString, caixa_string);
				   	strcat(MEGAString, "{7D8084}Digite abaixo o ID do jogador em que fará a transferência:\n");

				  	ShowPlayerDialog(playerid, 172 + 3, DIALOG_STYLE_INPUT, "Transferência bancária", MEGAString, "Confirmar", "Retornar");
		  		}
	      		case 4: callcmd::roubar(playerid);
	     	}
	   	}
	   	return true;
	}

    else if(dialogid == 172 + 1)
	{
        if (response)
		{
			new str[104];

			if (gettime() < GetPVarInt(playerid, #varFlood_caixaeletronico)) return SendClientMessage(playerid, -1, "Você só pode usar essa função a cada 5 minutos.");

		    if (strval(inputtext) > PlayerInfo[playerid][pConta] || strval(inputtext) < 1) return SendClientMessage(playerid, -1, "Voce não tem tudo isso na sua conta!");

			if (strval(inputtext) > CaixaInfo[CaixaPlayerProximo][caixaDinheiro]) return SendClientMessage(playerid, -1, "O caixa eletrônico não tem esse valor todo.");

			if (strval(inputtext) > 100000) return SendClientMessage(playerid, -1, "Você pode sacar ou depositar apenas valores abaixo de $100.000.");

           	CaixaInfo[CaixaPlayerProximo][caixaDinheiro] -= strval(inputtext);
			PlayerInfo[playerid][pConta] -= strval(inputtext); 
			Player_AddMoney(playerid, strval(inputtext));

			format(str, sizeof(str), "%s sacou $%s no banco, seu saldo: $%s", PlayerName[playerid], getFormatText(strval(inputtext)), getFormatText(PlayerInfo[playerid][pConta]));
			server_log("banco", str);

			format(str, sizeof str, "Caixa Eletrônico\n{7D8084}Aperte '{FFFFFF}ENTER{7D8084}' para usar\nDinheiro no caixa: {00AA00}$%s", getFormatText(CaixaInfo[CaixaPlayerProximo][caixaDinheiro]));
			Update3DTextLabelText(CaixaInfo[CaixaPlayerProximo][caixaText], 0xDBDCE0FF, str);

			SendClientMessage(playerid, 0xDBED15FF, "» Informações do saque");

			SendMsgF(playerid, COLOR_WHITE,  "Você sacou {00AA00}$%s {FFFFFF}da sua conta", getFormatText(strval(inputtext)));

			SendMsgF(playerid, COLOR_WHITE,  "Novo saldo: {00AA00}$%s", getFormatText(PlayerInfo[playerid][pConta]));

			SendClientMessage(playerid, 0xDBED15FF, "_______________________________________");

			SetPVarInt(playerid, #varFlood_caixaeletronico, gettime() + (60 * 5));
		}
		else
		{
			callcmd::banco(playerid);
  		}
        return true;
    }

    else if(dialogid == 172 + 2)
	{
        if (response)
		{
			new str[104];

			if (gettime() < GetPVarInt(playerid, #varFlood_caixaeletronico)) return SendClientMessage(playerid, -1, "Você só pode usar essa função a cada 5 minutos.");

         	if (strval(inputtext) > Player_GetMoney(playerid) || strval(inputtext) < 1) return SendClientMessage(playerid, -1, "Voce não tem tudo isso na sua mão!");

        	if (CaixaInfo[CaixaPlayerProximo][caixaDinheiro]+strval(inputtext) > 100000)
				return SendClientMessage(playerid, -1, "O caixa eletrônico suporta no máximo $100.000, deposite mais tarde.");

			if (strval(inputtext) > 100000) return SendClientMessage(playerid, -1, "Você pode sacar ou depositar apenas valores abaixo de $100.000.");

			Player_RemoveMoney(playerid, strval(inputtext));
			PlayerInfo[playerid][pConta] += strval(inputtext);
			CaixaInfo[CaixaPlayerProximo][caixaDinheiro] += strval(inputtext);
			format(str, sizeof(str), "%s depositou $%s no banco, seu saldo: $%s", PlayerName[playerid], getFormatText(strval(inputtext)), getFormatText(PlayerInfo[playerid][pConta]));
			server_log("banco", str);

          	format(str, sizeof str, "Caixa Eletrônico\n{7D8084}Aperte '{FFFFFF}ENTER{7D8084}' para usar\nDinheiro no caixa: {00AA00}$%s", getFormatText(CaixaInfo[CaixaPlayerProximo][caixaDinheiro]));
			Update3DTextLabelText(CaixaInfo[CaixaPlayerProximo][caixaText], 0xDBDCE0FF, str);

       		SendClientMessage(playerid, 0xDBED15FF, "» Informações do depósito");

			SendMsgF(playerid, COLOR_WHITE,  "Você depositou {00AA00}$%s {FFFFFF}na sua conta", getFormatText(strval(inputtext)));

			SendMsgF(playerid, COLOR_WHITE,  "Novo saldo: {00AA00}$%s", getFormatText(PlayerInfo[playerid][pConta]));

			SetPVarInt(playerid, #varFlood_caixaeletronico, gettime() + (60 * 5));

			SendClientMessage(playerid, 0xDBED15FF, "_______________________________________");
		} else {
			callcmd::banco(playerid);
  		}
        return true;
    }

    else if (dialogid == 172 + 3)
	{
        if (response) {

            if (Admin_GetNivel(playerid) < DONO) return SendClientMessage(playerid, -1, "A transferência via caixa eletrônico está em manutenção.");

        	PlayerPlaySound(playerid, 1057,0.0,0.0,0.0);
			TransferenciaID[playerid] = strval(inputtext);
			ShowPlayerDialog(playerid, 172 + 4, DIALOG_STYLE_INPUT, "Transferência de valores","Digite abaixo a quantia para transferência", "Transferir", "Retornar");
    	} else {
			callcmd::banco(playerid);
	    }
        return true;
    }

    else if (dialogid == 172 + 4)
	{
        if (response) {

			if (!IsPlayerConnected(TransferenciaID[playerid]) || !Player_Logado(TransferenciaID[playerid])) return SendClientMessage(playerid, -1, "O jogador não está conectado no servidor.");

			if (TransferenciaID[playerid] == INVALID_PLAYER_ID) 
				return SendClientMessage(playerid, -1, "Você digitou um ID inválido.");
			
			if (TransferenciaID[playerid] == playerid)
				return SendClientMessage(playerid, -1, "Você não pode transferir para você mesmo.");

           	if (strval(inputtext) > 0 && PlayerInfo[playerid][pConta] >= strval(inputtext))
			{
				if (strval(inputtext) > 5000000) return SendClientMessage(playerid, -1, "Para transferir valores maiores que $5.000.000 vá ao banco.");

               	PlayerInfo[playerid][pConta] -= strval(inputtext);
				PlayerInfo[TransferenciaID[playerid]][pConta] += strval(inputtext);

				SendClientMessage(TransferenciaID[playerid], 0xDBED15FF, "» Informações da transferência");
				SendClientMessage(playerid, 0xDBED15FF, "» Informações da transferência");

				SendMsgF(playerid, COLOR_WHITE,  "Você transferiu {00AA00}$%s {FFFFFF}para %s", getFormatText(strval(inputtext)), PlayerName[TransferenciaID[playerid]]);
				SendMsgF(playerid, COLOR_WHITE,  "Novo saldo: {00AA00}$%s", getFormatText(PlayerInfo[playerid][pConta]));
				SendMsgF(playerid, COLOR_WHITE,  "%s transferiu {00AA00}$%s {FFFFFF}para você", PlayerName[playerid], getFormatText(strval(inputtext)));
				SendMsgF(playerid, COLOR_WHITE,  "Novo saldo: {00AA00}$%s", getFormatText(PlayerInfo[TransferenciaID[playerid]][pConta]));

				SendClientMessage(playerid, 0xDBED15FF, "_______________________________________");
				SendClientMessage(TransferenciaID[playerid], 0xDBED15FF, "_______________________________________");

				PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0); PlayerPlaySound(TransferenciaID[playerid], 1052, 0.0, 0.0, 0.0);

				new string[128];

               	format(string, sizeof(string), "(Conta bancária): %s(%d) transferiu $%s para %s(%d)", PlayerName[playerid], playerid, getFormatText(strval(inputtext)), PlayerName[TransferenciaID[playerid]], TransferenciaID[playerid]);
				Staff_ChatToAll(COLOR_YELLOW, string); server_log("transferir", string);
    		} else {
  				SendClientMessage(playerid, -1, "Transferência inválida.");
           	}
    	} else {
			callcmd::banco(playerid);
	    }
        return true;
    }
    return 0;
}