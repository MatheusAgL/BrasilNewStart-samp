#include <YSI_Coding\y_hooks>

new Hosp_Dialog			[MAX_PLAYERS][MAX_PLAYERS];
new Timer:TimerMedico	[MAX_PLAYERS];

new Float:PacientesPos[][4] = {
	{1631.6744,-2328.0789,13.5469,348.4788},
	{1544.5087,-2229.7476,13.5469,240.3778},
	{1161.4363,-2038.0366,69.0078,309.5207},
	{488.9377,-1863.9271,3.5070,328.5297},
	{916.2723,-1873.9165,6.6505,328.5297},
	{829.3969,-2053.9185,12.8672,358.6912},
	{828.5342,-1825.2048,12.2988,358.4822},
	{102.2759,-1524.1505,6.4745,107.5638},
	{277.3748,-1251.7284,73.9105,229.3877},
	{617.1685,-1103.1157,46.7897,217.8029},
	{1045.6615,-921.7542,42.5873,269.8082},
	{1214.2014,-920.0941,42.9253,344.0689},
	{1481.4073,-1024.0995,23.8139,292.7862},
	{556.0983,-1264.5336,17.2422,343.9644},
	{793.5419,-1667.3510,13.5033,179.4948},
	{513.5475,-1392.2294,16.1328,287.4913},
	{933.9449,-1102.3480,24.3287,264.5858},
	{1154.9537,-1090.1765,26.0828,272.3874},
	{2132.1143,-1261.2170,23.9922,271.4791},
	{2338.7449,-1311.6965,24.0464,187.9227},
	{2456.1621,-1402.0549,23.9869,41.4090},
	{2366.9199,-1695.7219,13.4364,94.6762},
	{2300.6985,-1695.8625,13.4233,94.2584},
	{1919.8035,-1925.3411,13.5469,259.0732},
	{1927.8187,-2102.5496,13.5800,273.6956},
	{1792.9641,-2120.6848,13.5543,191.6015},
	{1886.9663,-1854.2418,13.5743,10.6209},
	{1942.4762,-1588.9376,13.5693,255.2320},
	{2666.3811,-1426.7788,30.5013,350.5907},
	{2698.9421,-1393.8685,33.8796,276.6433},
	{2801.1641,-1385.8690,21.2656,292.4146},
	{2705.8865,-1093.0955,69.4474,3.4780},
	{1154.6947,-641.1337,104.2550,17.5376},
	{872.9345,-752.3148,94.2959,88.4560},
	{674.3015,-591.1570,16.3359,134.0986},
	{620.5209,-601.8893,17.2330,175.7723},
	{857.2012,-591.0064,17.9306,300.7935},
	{1815.8405,-1122.0580,24.0781,330.2471},
	{859.4576,-1371.6771,13.5469,321.1604},
	{420.9743,-1554.8197,27.5781,230.1883},
	{940.2171,-1660.5544,13.5429,102.9970},
	{1500.8328,-1840.7030,13.5469,292.7744},
	{2040.8535,-1722.3386,13.5469,185.0912},
	{2519.2449,-2090.8601,13.5469,87.0636},
	{2768.8577,-2506.7957,13.6276,20.3229},
	{1975.0222,-2649.1060,13.5469,189.8378},
	{2771.3555,-2365.0308,13.6328,349.6886},
	{2599.9487,-1470.7103,16.7580,173.2715},
	{2648.5947,-1457.3765,16.2572,43.7912},
	{2788.3533,-1417.3845,16.2500,278.1348},
	{1981.5076,-1279.3131,23.8203,275.7730},
	{2080.7603,-1141.5052,23.9015,83.1990},
	{1209.1018,-1015.0696,32.5686,3.2983},
	{1296.6937,-2406.6121,12.9849,3.2983},
	{2756.7874,-1945.0839,13.5484,269.1291},
	{2748.6509,-2015.9274,13.5547,90.9858}
};

new MensagensMedico[][] = {
	{"sofreu golpes de faca"},
	{"se envolveu briga de rua"},
	{"sofreu uma tentativa de homicídio"},
	{"se feriu ao reagir a um assalto"},
	{"está passando mal"}
};

new static string[256];

timer timerMedico[1000](playerid)
{
	new tempo = GetPVarInt(playerid, "tempoMedico");
	if(tempo > 1) {
		if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 416) {
			DisablePlayerCheckpoint(playerid);
			SetPVarInt(playerid, "foraAmbulanciaMedico", 1);
		}
		else if(GetPVarInt(playerid, "foraAmbulanciaMedico")) {
			new pos = GetPVarInt(playerid, "posMedico");
			SetPlayerCheckpoint(playerid, PacientesPos[pos][0], PacientesPos[pos][1], PacientesPos[pos][2], 5.0);
			SetPVarInt(playerid, "foraAmbulanciaMedico", 0);
		}

		tempo -= 1;
		SetPVarInt(playerid, "tempoMedico", tempo);

		format(string, 256, "~y~%s", ConvertTime(tempo));
		GameTextForPlayer(playerid, string, 1050, 6);
	}
	else {
		new cash = 200 + random(300);
		SendMsgF(playerid, COLOR_LIGHTRED, "Você foi punido em $%d por não socorrer o paciente a tempo.", cash);
		Player_RemoveMoney(playerid, cash);
		GameTextForPlayer(playerid, "~r~O paciente morreu", 4000, 6);
		stop TimerMedico[playerid];
		SetPVarInt(playerid, "servicoMedico", 0);
		DisablePlayerCheckpoint(playerid);
	}
	return 1;
}

timer timerDestroyActorMedico[10000](playerid)
{
	DestroyDynamicActor(GetPVarInt(playerid, "actorMedico"));
	return 1;
}

timer timerAtendimentoMedico[5000](playerid)
{
	new mode = GetPVarInt(playerid, "modoMedico");
	SetCameraBehindPlayer(playerid);
	TogglePlayerControllable(playerid, true);
	if(mode == 1) {
		PagarSalarioMedico(playerid, 400);
		defer timerDestroyActorMedico(playerid);
	}
	else if(mode == 2) {
		if(GetPVarInt(playerid, "retornoMedico") == 0) {
			SetPlayerCheckpoint(playerid, 1183.9657, -1323.1019, 13.5755, 5.0);
			SendClientMessage(playerid, -1, "Leve o paciência de volta ao hospital para que ele seja tratado com urgência!");
			SetPVarInt(playerid, "retornoMedico", 1);
			DestroyDynamicActor(GetPVarInt(playerid, "actorMedico"));
		}
		else
			PagarSalarioMedico(playerid, 600);
	}
	return 1;
}

stock IniciarServicoMedico(playerid) {
	
	new pos = random(sizeof(PacientesPos));
	new actorid = CreateDynamicActor(20+random(150), PacientesPos[pos][0], PacientesPos[pos][1], PacientesPos[pos][2], PacientesPos[pos][3]);
	new mode = random(10);

	SetPVarInt(playerid, "servicoMedico", 1);
	SetPVarInt(playerid, "posMedico", pos);
	SetPVarInt(playerid, "retornoMedico", 0);
	SetPVarInt(playerid, "foraAmbulanciaMedico", 0);
	SetPVarInt(playerid, "actorMedico", actorid);

	PlayerPlaySound(playerid, 3002, 0.0, 0.0, 0.0);

	new MapZone:zone = GetMapZoneAtPoint2D(PacientesPos[pos][0], PacientesPos[pos][1]);
	new zone_name[MAX_MAP_ZONE_NAME];
	GetMapZoneName(zone, zone_name);
	
	// Cura normal
	if(mode < 3) {
		new tempo = 90 + random(60);
		ApplyDynamicActorAnimation(actorid, "MD_END", "END_SC2_SWE", 4.1, 1, 1, 1, 1, 1);
		SetPVarInt(playerid, "modoMedico", 1);
		SetPVarInt(playerid, "tempoMedico", tempo);

		SendMsgF(playerid, COLOR_YELLOW, "Um cidadão está ferido e precisa de atendimento médico na região de {FFFFFF}%s", zone_name);
		SendMsgF(playerid, COLOR_YELLOW, "Segundo informações passadas à equipe, o cidadão %s e precisa de ajuda no local", MensagensMedico[random(sizeof(MensagensMedico))]);
	}
	// Emergência
	else {
		new tempo = 120 + random(60);
		ApplyDynamicActorAnimation(actorid, "CRACK", "crckidle3", 4.1, 1, 1, 1, 1, 1);
		SetPVarInt(playerid, "modoMedico", 2);
		SetPVarInt(playerid, "tempoMedico", tempo);

		SendMsgF(playerid, COLOR_LIGHTRED, "Um cidadão está em estado grave e precisa de socorro médico na região de {FFFFFF}%s", zone_name);
		SendMsgF(playerid, COLOR_YELLOW, "Segundo informações passadas à equipe, o cidadão %s e precisa chegar ao hospital com urgência", MensagensMedico[random(sizeof(MensagensMedico))]);
	}

	SetPlayerCheckpoint(playerid, PacientesPos[pos][0], PacientesPos[pos][1], PacientesPos[pos][2], 5.0);
	stop TimerMedico[playerid];
	TimerMedico[playerid] = repeat timerMedico(playerid);
}

stock PagarSalarioMedico(playerid, salario) {
	new pos = GetPVarInt(playerid, "posMedico"), mode = GetPVarInt(playerid, "modoMedico"), tempo = GetPVarInt(playerid, "tempoMedico");
	new dist = floatround(GetDistanceBetweenPoints(PacientesPos[pos][0], PacientesPos[pos][1], PacientesPos[pos][2], 1183.9657, -1323.1019, 13.5755));
	new bonus = random(salario) + floatround(dist*0.7) + tempo * 3;

	if(mode == 1) 
		SendMsgF(playerid, -1, "Foi adicionado {00AA00}$%s{FFFFFF} ao seu salário por atender o paciente no próprio local.", getFormatText(bonus));
	else if(mode == 2) 
		SendMsgF(playerid, -1, "Foi adicionado {00AA00}$%s{FFFFFF} ao seu salário por socorrer o paciente e levá-lo ao hospital.", getFormatText(bonus));

	GameTextForPlayer(playerid, "~g~Paciente salvo", 2000, 4);
	PlayerInfo[playerid][pSalario] += bonus;
	removerDinheiroGoverno(bonus);

	SetPVarInt(playerid, "servicoMedico", 0);
	PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
}

hook OnPlayerEnterCheckpoint(playerid) {
	if(GetPVarInt(playerid, "servicoMedico")) {
		if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 416)
			return SendClientMessage(playerid, -1, "Você não está em uma ambulância.");

		if(GetPVarInt(playerid, "retornoMedico")) {
			stop TimerMedico[playerid];
		}
		else {
			new pos = GetPVarInt(playerid, "posMedico"), mode = GetPVarInt(playerid, "modoMedico");
			if(!PlayerToPoint(15.0, playerid, PacientesPos[pos][0], PacientesPos[pos][1], PacientesPos[pos][2])) {
				SetPlayerCheckpoint(playerid, PacientesPos[pos][0], PacientesPos[pos][1], PacientesPos[pos][2], 5.0);
				return 1;
			}

			if(mode == 1)
				stop TimerMedico[playerid];

		}
		new Float:coord[4];
		GetPlayerPos(playerid, coord[0], coord[1], coord[2]);
		GetPlayerFacingAngle(playerid, coord[3]);
		GetXYInFrontOfPoint(coord[0], coord[1], coord[3] + 35.0, 10.0);
		SetPlayerCameraPos(playerid, coord[0], coord[1], coord[2]+1.00);

		GetPlayerPos(playerid, coord[0], coord[1], coord[2]);
		SetPlayerCameraLookAt(playerid, coord[0], coord[1], coord[2]);

		TogglePlayerControllable(playerid, false);
		defer timerAtendimentoMedico(playerid);
	}
	return 1;
}

CMD:ajustar(playerid)
{
	if(!IsPlayerInRangeOfPoint(playerid, 1.0, 1130.1991, -1733.0205, 13.8090))
		return SendClientMessage(playerid, -1, "Você não esta na area de ajuste dos pacientes.");

    if(PlayerIsMedico(playerid))
	{
	    new In_Hosp = 0;
	    MEGAString[0] = EOS;
	    foreach(new i : Player)
	    {
	        if(PlayerInfo[i][pHospital])
	        {
				List_SetPlayers(playerid, In_Hosp, i);
	            format(string, sizeof string, "Hospitalizado: %s [%d segundos]\n", PlayerName[i], PlayerInfo[i][pTempoHospital]);
				strcat(MEGAString, string);
				In_Hosp ++;
			}
	    }
	    if(In_Hosp == 0) return SendClientMessage(playerid, -1, "Ninguém está hospitalizado neste hospital.");
	    ShowPlayerDialog(playerid, 5587, DIALOG_STYLE_LIST, "Hospitalizados neste hospital", MEGAString, "Ajustar", "Sair");
	}
	else SendClientMessage(playerid, -1, "Apenas médicos podem acessar esta area.");
	return true;
}

CMD:iniciarservico(playerid)
{
	if (!PlayerIsMedico(playerid)) 
		return SendClientMessage(playerid, -1, "Você não é um médico.");
    else if (!IsPlayerInAnyVehicle(playerid) || GetVehicleModel(GetPlayerVehicleID(playerid)) != 416) 
		return SendClientMessage(playerid, -1, "Você não está em uma ambulância.");
	else if(gettime() < GetPVarInt(playerid, "tempoInicioMedico"))
		return SendMsgF(playerid, -1, "Aguarde %s para iniciar outro serviço como médico", ConvertTime(GetPVarInt(playerid, "tempoInicioMedico")-gettime()));

	SetPVarInt(playerid, "tempoInicioMedico", gettime()+60);
	IniciarServicoMedico(playerid);
	return true;	
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == 5587)
	{
		if(!response)return SendClientMessage(playerid, COLOR_GRAD, "Você cancelou o menu de medico.");
		if(!Player_Logado(Hosp_Dialog[playerid][listitem])) return SendClientMessage(playerid, COLOR_GRAD, "O jogador selecionado não está mais conectado/logado.");
	    if(HospId[Hosp_Dialog[playerid][listitem]] != 999) return SendClientMessage(playerid, COLOR_GRAD, "Este hospitalizado já está sendo ajustado por outro medico.");
		if(PlayerInfo[Hosp_Dialog[playerid][listitem]][pHAjustado])  return SendClientMessage(playerid, COLOR_GRAD, "Este hospitalizado já foi ajustado por outro médico.");
		ShowPlayerDialog(playerid, 5588, DIALOG_STYLE_LIST, "Quanto voce quer retirar do tempo de hospital dele?", 
		"Retirar: 50% {33CCFF}(Nível 1+)\n\
		Retirar: 60% {33CCFF}(Nível 2+)\n\
		Retirar: 70% {33CCFF}(Nível 3+)\n\
		Retirar: 80% {33CCFF}(Nível 4+)\n\
		Retirar: 90% {33CCFF}(Nível 5)",
	 	"Continuar", " Sair");
	 	SetPVarInt(playerid, "list2", listitem);
	 	HospId[Hosp_Dialog[playerid][listitem]] = playerid;
	    return true;
	}
	else if(dialogid == 5588)
	{
		if(!response)
		{
		    HospId[Hosp_Dialog[playerid][GetPVarInt(playerid, "list2")]] = 999;
			return SendClientMessage(playerid, COLOR_GRAD, "Você cancelou o menu de médicos.");
		}
		switch(listitem)
		{
		    case 0:{
				SetPVarInt(playerid, "H_Ajust", 50);
			}
		    case 1:{
				if(PlayerInfo[playerid][pMedicoSkill] < 50){return SendClientMessage(playerid, COLOR_GRAD, "*Você não tem nível suficiente para esta quantidade."),HospId[Hosp_Dialog[playerid][GetPVarInt(playerid, "list2")]] = 999;}
				SetPVarInt(playerid, "H_Ajust", 60);
			}
		    case 2:{
				if(PlayerInfo[playerid][pMedicoSkill] < 100){return SendClientMessage(playerid, COLOR_GRAD, "*Você não tem nível suficiente para esta quantidade."),HospId[Hosp_Dialog[playerid][GetPVarInt(playerid, "list2")]] = 999;}
				SetPVarInt(playerid, "H_Ajust", 70);
			}
		    case 3:{
				if(PlayerInfo[playerid][pMedicoSkill] < 200){return SendClientMessage(playerid, COLOR_GRAD, "*Você não tem nível suficiente para esta quantidade."),HospId[Hosp_Dialog[playerid][GetPVarInt(playerid, "list2")]] = 999;}
				SetPVarInt(playerid, "H_Ajust", 80);
			}
		    case 4:{
				if(PlayerInfo[playerid][pMedicoSkill] < 350){return SendClientMessage(playerid, COLOR_GRAD, "*Você não tem nível suficiente para esta quantidade."),HospId[Hosp_Dialog[playerid][GetPVarInt(playerid, "list2")]] = 999;}
				SetPVarInt(playerid, "H_Ajust", 90);
			}
		}
		ShowPlayerDialog(playerid, 5589, DIALOG_STYLE_INPUT, "Quanto você quer?", "{FFFFFF}Digite quanto você quer para ajustar o paciente", "Continuar", "");
		return true;
	}
	else if(dialogid == 5589)
	{
		if (!Player_Logado(Hosp_Dialog[playerid][GetPVarInt(playerid, "list2")]))
			return SendClientMessage(playerid, COLOR_GRAD, "O jogador não está mais conectado no servidor");

		if(!response || !strval(inputtext) || strval(inputtext) < 50 || strval(inputtext) > 5000)
		{
		    ShowPlayerDialog(playerid, 5589, DIALOG_STYLE_INPUT, "Quanto você quer?", "{FFFFFF}Digite quanto você quer para ajustar o paciente", "Continuar", "");
		    return SendClientMessage(playerid, COLOR_GRAD, "Preço de R$50 a R$5000");
		}
		SetPVarInt(playerid, "H_Preco", strval(inputtext));

		format(string, sizeof string,
		"{FFFFFF}O médico %s está receitando um remédio que irá retirar %d por cento de seu tempo de internação\n\
		por R$%d, você aceita ou não?\n\
		{33CCFF}OBS: Se o preço estiver abusivo, relate isto a um admin on-line.",
		PlayerName[playerid], GetPVarInt(playerid, "H_Ajust"), GetPVarInt(playerid, "H_Preco"));
		ShowPlayerDialog(Hosp_Dialog[playerid][GetPVarInt(playerid, "list2")], 5590, DIALOG_STYLE_MSGBOX, "médico", string, "Aceitar", "Recusar");

		format(string, sizeof string, "* Você quer retirar %s de %d por cento de seu tempo de internação por R$%d",
		PlayerName[Hosp_Dialog[playerid][GetPVarInt(playerid, "list2")]],
		GetPVarInt(playerid, "H_Ajust"), strval(inputtext));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
		return true;
	}
	else if(dialogid == 5590)
	{
	    new id = HospId[playerid];
	    if(!IsPlayerConnected(id) || !PlayerIsMedico(id))return SendClientMessage(playerid, COLOR_LIGHTRED, "* Este médico não esta mais conectado ou não é mais um médico"), HospId[playerid] = 999;
		if(PlayerInfo[playerid][pTempoHospital] < 1)
		    return SendClientMessage(playerid, COLOR_GRAD, "Você não está mais hospitalizado!");
		switch(response)
		{
		    case 0:
		    {
		        format(string, sizeof string, " * Você recusou o médico %s.", PlayerName[id]);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
		        format(string, sizeof string, " * %s recusou seu pedido de ajuste de tempo de internação.", PlayerName[playerid]);
				SendClientMessage(id, COLOR_LIGHTRED, string);
			}
		    case 1:
		    {
		        if(Player_GetMoney(playerid) < GetPVarInt(id, "H_Preco"))
		        {
					SendClientMessage(playerid, COLOR_LIGHTRED, "Você nao pode pagar o que o médico pediu.");
			        format(string, sizeof string, " * o paciente %s não pode pagar o que você pediu.", PlayerName[playerid]);
					SendClientMessage(id, COLOR_LIGHTRED, string);
					HospId[playerid] = 999;
					return 1;
		        }
		        format(string, sizeof string, " * O médico %s retirou %d por cento do seu tempo de internação por R$%d.", PlayerName[id], GetPVarInt(id, "H_Ajust"),GetPVarInt(id, "H_Preco"));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
		        format(string, sizeof string, " * Você retirou %d por cento do tempo de internação de %s, por R$%d.", GetPVarInt(id, "H_Ajust"), PlayerName[playerid], GetPVarInt(id, "H_Preco"));
				SendClientMessage(id, COLOR_LIGHTBLUE, string);
				Player_RemoveMoney(playerid, GetPVarInt(id, "H_Preco"));
				Player_AddMoney(id, GetPVarInt(id, "H_Preco"));
				PlayerInfo[id][pMedicoSkill]++;
				PlayerInfo[playerid][pHAjustado] = true;
				new time = PlayerInfo[playerid][pTempoHospital];
				new ajust = GetPVarInt(id, "H_Ajust");
				PlayerInfo[playerid][pTempoHospital] = floatround(time - time * ajust / 100);
		    }
		}
		HospId[playerid] = 999;
	    return true;
	}
	return 0;
}

