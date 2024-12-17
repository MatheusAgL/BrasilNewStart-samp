#include <YSI_Coding\y_hooks>

#define W_Velocidade        15
#define W_Damage            25
#define V_Damage            650.0

//-------------------------------------------------------
new const Float:FlySpawns[][] =
{
	//----[ Avião ]-----//
	{-1491.1969,-11.7741,48.7185},
	{-1789.4520,-415.3133,113.8290},
	{-1896.8480,-1263.6472,132.0538},
	{-2037.3015,-1897.4117,177.8156},
	{-2274.9436,-2610.8142,68.1777},
	{-1525.0313,-2945.8933,44.1423},
	{-978.3129,-2930.2197,62.2493},
	{-755.1094,-3373.6997,69.6178},
	{-1107.6266,-3440.2268,70.5846},
	{-1114.9528,-2894.9722,44.0651}
};

//-------------------------------------------------------
new const Float:BoatSpawns[][] =
{
	{111.3130,-432.2714,-0.5148},
	{303.4040,-339.7429,-0.2797},
	{555.4991,-242.5986,-0.0648},
	{823.6974,-139.2229,-0.3063},
	{1056.0095,-110.0787,0.0905},
	{1317.9407,-235.2081,-0.1033},
	{1598.9757,-78.1478,-0.0086},
	{1870.5237,-47.7913,-0.0711},
	{2097.8455,-2.9056,-0.3076},
	{2210.1038,382.6406,-0.0424},
	{2529.3115,456.7664,0.0935},
	{2847.7654,335.6822,-0.1901},
	{2963.8286,-85.5185,-0.0494},
	{2996.7993,-715.7225,0.0608},
	{2977.1450,-1561.7919,0.0817},
	{2988.7041,-1881.2853,-0.0454},
	{2908.3611,-2410.7231,-0.1064},
	{2624.6680,-2770.3235,0.1763},
	{2016.3397,-2897.8135,-0.2225},
	{1268.5513,-2756.5977,0.0159},
	{921.5064,-2275.2744,0.0590},
	{906.0276,-1943.5052,-0.4901}
};

// -------- Checkpoints carteira de motorista ----------------- //
static const Float:CPsCarteira[][] =
{
	{533.9781,-1613.3921,15.9729},
	{496.6134,-1663.5321,19.6371},
	{368.0127,-1646.2122,32.3616},
	{238.6763,-1580.2913,32.7526},
	{389.1283,-1412.7395,33.7790},
	{615.6747,-1320.0083,13.521},
	{628.5461,-1388.0393,13.1540},
	{760.4673,-1404.3176,13.0799},
	{1039.5890,-1403.8013,12.9526},
	{1058.1910,-1464.4951,13.0762},
	{1002.5800,-1573.6125,13.0885},
	{852.3422,-1600.3179,13.0920},
	{786.8358,-1587.0516,13.0923},
	{604.1711,-1586.8290,15.6761},
	{505.6995,-1561.0339,16.2139}
};

hook OP_EnterRaceCheckpoint(playerid)
{
	if( InTeste[playerid])
	{
	    AtualCP[playerid]++;
	    if(InTeste[playerid] == 1)
	    {
	        SendMsgF(playerid, COLOR_ORANGE, "Você passou pelo checkpoint [%d/%d]!", AtualCP[playerid], sizeof(CPsCarteira));
			if(AtualCP[playerid] >= sizeof(CPsCarteira))
			{
			    GameTextForPlayer(playerid, "~w~Teste~n~~g~concluido", 3000, 0);
			    DisablePlayerRaceCheckpoint(playerid);
			    TestEnd(playerid, 1);
			    return true;
			}
			else if(AtualCP[playerid] >= sizeof(CPsCarteira)-1)
			{
		    	SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_FINISH, CPsCarteira[AtualCP[playerid]][0], CPsCarteira[AtualCP[playerid]][1], CPsCarteira[AtualCP[playerid]][2],
		    	0.0,0.0,0.0, 10.0);
	            PlayerPlaySound(playerid, 1056, 0.0,0.0,0.0);
				return true;
			}
	    	SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_NORMAL, CPsCarteira[AtualCP[playerid]][0], CPsCarteira[AtualCP[playerid]][1], CPsCarteira[AtualCP[playerid]][2],
	    	CPsCarteira[AtualCP[playerid]+1][0],CPsCarteira[AtualCP[playerid]+1][1],CPsCarteira[AtualCP[playerid]+1][2], 8.0);
		}
		else if(InTeste[playerid] == 2)
		{
		    SendMsgF(playerid, COLOR_ORANGE, "Você passou pelo checkpoint [%d/%d]!", AtualCP[playerid], sizeof(FlySpawns));
			if(AtualCP[playerid] >= sizeof(FlySpawns))
			{
			    GameTextForPlayer(playerid, "~w~Teste~n~~g~concluido", 3000, 0);
			    DisablePlayerRaceCheckpoint(playerid);
			    TestEnd(playerid, 1);
			    return true;
			}
			if(AtualCP[playerid] >= sizeof(FlySpawns)-1)
			{
		    	SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_FINISH, FlySpawns[AtualCP[playerid]][0], FlySpawns[AtualCP[playerid]][1], FlySpawns[AtualCP[playerid]][2],
		    	0.0,0.0,0.0, 20.0);
	            PlayerPlaySound(playerid, 1056, 0.0,0.0,0.0);
				return true;
			}
	    	SetPlayerRaceCheckpoint(playerid, CP_TYPE_AIR_FINISH, FlySpawns[AtualCP[playerid]][0], FlySpawns[AtualCP[playerid]][1], FlySpawns[AtualCP[playerid]][2],
	    	FlySpawns[AtualCP[playerid]+1][0],FlySpawns[AtualCP[playerid]+1][1],FlySpawns[AtualCP[playerid]+1][2], 20.0);
		}
	    else if(InTeste[playerid] == 3)
	    {
	        SendMsgF(playerid, COLOR_ORANGE, "Você passou pelo checkpoint [%d/%d]!", AtualCP[playerid], sizeof(BoatSpawns));
			if(AtualCP[playerid] >= sizeof(BoatSpawns))
			{
			    GameTextForPlayer(playerid, "~w~Teste~n~~g~concluido", 3000, 0);
			    DisablePlayerRaceCheckpoint(playerid);
			    TestEnd(playerid, 1);
			    return true;
			}
			else if(AtualCP[playerid] >= sizeof(BoatSpawns)-1)
			{
		    	SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_FINISH, BoatSpawns[AtualCP[playerid]][0], BoatSpawns[AtualCP[playerid]][1], BoatSpawns[AtualCP[playerid]][2],
		    	0.0,0.0,0.0, 10.0);
	            PlayerPlaySound(playerid, 1056, 0.0,0.0,0.0);
				return true;
			}
	    	SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_NORMAL, BoatSpawns[AtualCP[playerid]][0], BoatSpawns[AtualCP[playerid]][1], BoatSpawns[AtualCP[playerid]][2],
	    	BoatSpawns[AtualCP[playerid]+1][0],BoatSpawns[AtualCP[playerid]+1][1],BoatSpawns[AtualCP[playerid]+1][2], 8.0);
		}

		PlayerPlaySound(playerid, 1056, 0.0,0.0,0.0);
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == 7788)
	{
	    if (!response) return true;

	    if (IsPlayerHaveItem(playerid, ITEM_TYPE_MOTORISTA)) return SendClientMessage(playerid, -1, "Você ja tem a carteira de motorista.");

		if (Player_GetMoney(playerid) < 3000) return SendClientMessage(playerid, -1, "Você não tem {00AA00}$3.000");

		Player_RemoveMoney(playerid, 3000);
	    DepositPropertie(playerid, PagarICMS(3000));

		ComecarTeste(playerid, 1);

	    return true;
	}
	else if (dialogid == 4789)
	{
	    if (!response) return true;

	    if (IsPlayerHaveItem(playerid, ITEM_TYPE_PILOTO)) return SendClientMessage(playerid, -1, "Você ja tem a carteira de Piloto.");

        if (Player_GetMoney(playerid) < 15000) return SendClientMessage(playerid, -1, "Você não tem {00AA00}$15.000");

		Player_RemoveMoney(playerid, 15000);
	    DepositPropertie(playerid, PagarICMS(15000));

		ComecarTeste(playerid, 2);

	    return true;
	}
	else if (dialogid == 4790)
	{
	    if (!response) return true;

	    if (IsPlayerHaveItem(playerid, ITEM_TYPE_MARUJO)) return SendClientMessage(playerid, -1, "Você ja tem a carteira de navegação.");

	    if (Player_GetMoney(playerid) < 13000) return SendClientMessage(playerid, -1, "Você não tem {00AA00}$13.000");

	    Player_RemoveMoney(playerid, 13000);
	    DepositPropertie(playerid, PagarICMS(13000));

		ComecarTeste(playerid, 3);

	    return true;
	}
	return 1;
}

static ComecarTeste(playerid, testeid)
{
    AtualCP[playerid] = 0;

	switch (testeid) {

		case 1: {
		    InTeste[playerid] = 1; TempoTeste[playerid] = 8*60;

		    SetPVarInt(playerid, "CarroTeste", CreateVehicle(560,510.2119,-1563.0643,16.3218,218.9997, -1, -1, -1));

		    SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_NORMAL, CPsCarteira[AtualCP[playerid]][0], CPsCarteira[AtualCP[playerid]][1], CPsCarteira[AtualCP[playerid]][2],
		    CPsCarteira[AtualCP[playerid]+1][0],CPsCarteira[AtualCP[playerid]+1][1],CPsCarteira[AtualCP[playerid]+1][2], 8.0);

			ShowPlayerBaloonInfo(playerid, "~>~~y~DETRAN: ~n~~w~Voce iniciou o exame pratico, aperte ~p~Y~w~ para ligar o veiculo.", 5000);
		}
		case 2: {
		    InTeste[playerid] = 2; TempoTeste[playerid] = 10*60;

		    SetPVarInt(playerid, "CarroTeste", CreateVehicle(593,-1091.7706,400.4440,14.3178,134.3243, 1, 3, -1));

		    SetPlayerRaceCheckpoint(playerid, CP_TYPE_AIR_FINISH, FlySpawns[AtualCP[playerid]][0], FlySpawns[AtualCP[playerid]][1], FlySpawns[AtualCP[playerid]][2],
		    FlySpawns[AtualCP[playerid]+1][0],FlySpawns[AtualCP[playerid]+1][1],FlySpawns[AtualCP[playerid]+1][2], 20.0);

			ShowPlayerBaloonInfo(playerid, "~>~~y~DETRAN: ~n~~w~Voce iniciou o exame pratico, aperte ~p~Y~w~ para ligar o veiculo.~n~Uma dica para você. Use as teclas ~p~Q ~w~e ~p~E~w~ para controlar o aviao.", 10000);
		}
		case 3: {
		    InTeste[playerid] = 3; TempoTeste[playerid] = 10*60;

		    SetPVarInt(playerid, "CarroTeste", CreateVehicle(452,1.7691,-568.5583,-0.5061,318.0349, 1, 3, -1));

		    SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_NORMAL, BoatSpawns[AtualCP[playerid]][0], BoatSpawns[AtualCP[playerid]][1], BoatSpawns[AtualCP[playerid]][2],
		    BoatSpawns[AtualCP[playerid]+1][0],BoatSpawns[AtualCP[playerid]+1][1],BoatSpawns[AtualCP[playerid]+1][2], 10.0);

			ShowPlayerBaloonInfo(playerid, "~>~~y~DETRAN: ~n~~w~Voce iniciou o exame pratico, aperte ~p~Y~w~ para ligar o veiculo.~n~Uma dica para voce. Sempre que for fazer uma curva, acelere o barco.", 10000);
		}
	}

	CriarTextTeste(playerid);
    SetPVarInt(playerid, "WarnningVelocidade", 0);
    SetPVarInt(playerid, "WarnningDamage", 0);
	
 	SetPlayerInterior(playerid, 0);
 	SetPlayerVirtualWorld(playerid, 0);

	UnlockVehicleDoors(GetPVarInt(playerid, "CarroTeste"));
	 
 	PutPlayerInVehicle(playerid, GetPVarInt(playerid, "CarroTeste"), 0);

	PlayerTextDrawShow(playerid, TextTeste[playerid][0]);
	PlayerTextDrawShow(playerid, TextTeste[playerid][1]);
	PlayerTextDrawShow(playerid, TextTeste[playerid][2]);
	PlayerTextDrawShow(playerid, TextTeste[playerid][3]);

	SetTimerEx("delayTeste", 3000, false, "i", playerid);

    VehicleInfo[GetPVarInt(playerid, "CarroTeste")][vehicleCombustivel] = 100;
	return true;
}

CALLBACK: delayTeste(playerid){

	return SetPVarInt(playerid, "TimerTeste", SetTimerEx("UpdateTeste", 1000, true, "i", playerid));
}

stock TestEnd(playerid, sucess)
{
	return EndTeste(playerid, InTeste[playerid], sucess);
}

CALLBACK:UpdateTeste(playerid)
{
	if (InTeste[playerid])
	{
 		new Float:vhealth, striiing[256];

		GetVehicleHealth(GetPlayerVehicleID(playerid), vhealth);

	    if (GetVehicleSpeed(GetPlayerVehicleID(playerid)) > 160)
	    {
	        SetPVarInt(playerid, "WarnningVelocidade", GetPVarInt(playerid, "WarnningVelocidade")+1);
	        SendClientMessage(playerid, COLOR_YELLOW, "Auto Escola: voce esta acima do limite de velocidade, reduza a velocidade para não reprovar.");
		}
		TempoTeste[playerid] --;
		if (GetPVarInt(playerid, "WarnningVelocidade") > W_Velocidade || GetPVarInt(playerid, "WarnningDamage") > W_Damage || vhealth < V_Damage)
		{
		    SendClientMessage(playerid, COLOR_YELLOW, "Você excedeu o limite de avisos e foi reprovado.");
		    return TestEnd(playerid, 0);
		}
		if (TempoTeste[playerid] < 1)
		{
		    SendClientMessage(playerid, COLOR_YELLOW, "Tempo estourado, você foi reprovado no teste.");
		    return TestEnd(playerid, 0);
		}
		if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
		    SendClientMessage(playerid, COLOR_YELLOW, "Você nao esta no carro da Auto Escola, teste encerrado");
		    return TestEnd(playerid, 0);
		}

		format(striiing, sizeof(striiing),
		"~g~maxima velocidade: ~r~150~n~\
		~w~Velocidade: ~g~%.0f km/h~n~_~n~_~n~\
		~g~minimo damage: ~r~%.0f~n~\
		~w~Damage: ~g~%.0f", GetVehicleSpeed(GetPlayerVehicleID(playerid)), V_Damage, vhealth);

		PlayerTextDrawSetString(playerid, TextTeste[playerid][2], striiing);

		format(striiing, sizeof striiing, "avisos: %d/%d", GetPVarInt(playerid, "WarnningVelocidade"), W_Velocidade);
		PlayerTextDrawSetString(playerid, TextTeste[playerid][0], striiing);

		format(striiing, sizeof striiing, "avisos: %d/%d~n~_~n~~y~tempo: %02d", GetPVarInt(playerid, "WarnningDamage"), W_Damage, TempoTeste[playerid]);
		PlayerTextDrawSetString(playerid, TextTeste[playerid][3], striiing);
	}
	return 0;
}

stock CriarTextTeste(playerid)
{
	if( InTeste[playerid])
	{
		TextTeste[playerid][0] = CreatePlayerTextDraw(playerid, 514.000000, 233.000000, "avisos: 1/10");
		PlayerTextDrawBackgroundColor(playerid, TextTeste[playerid][0], 20);
		PlayerTextDrawFont(playerid, TextTeste[playerid][0], TEXT_DRAW_FONT_2);
		PlayerTextDrawLetterSize(playerid, TextTeste[playerid][0], 0.220000, 1.000000);
		PlayerTextDrawColor(playerid, TextTeste[playerid][0], -16776961);
		PlayerTextDrawSetOutline(playerid, TextTeste[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, TextTeste[playerid][0], true);

		TextTeste[playerid][1] = CreatePlayerTextDraw(playerid, 617.000000, 209.000000, "_");
		PlayerTextDrawBackgroundColor(playerid, TextTeste[playerid][1], 255);
		PlayerTextDrawFont(playerid, TextTeste[playerid][1], TEXT_DRAW_FONT_1);
		PlayerTextDrawLetterSize(playerid, TextTeste[playerid][1], 0.500000, 8.499998);
		PlayerTextDrawColor(playerid, TextTeste[playerid][1], -1);
		PlayerTextDrawSetOutline(playerid, TextTeste[playerid][1], 0);
		PlayerTextDrawSetProportional(playerid, TextTeste[playerid][1], true);
		PlayerTextDrawSetShadow(playerid, TextTeste[playerid][1], 1);
		PlayerTextDrawUseBox(playerid, TextTeste[playerid][1], true);
		PlayerTextDrawBoxColor(playerid, TextTeste[playerid][1], 80);
		PlayerTextDrawTextSize(playerid, TextTeste[playerid][1], 505.000000, 0.000000);

		TextTeste[playerid][2] = CreatePlayerTextDraw(playerid, 513.000000, 215.000000, "~g~maxima velocidade: ~r~150~n~~w~Velocidade: ~g~135~n~_~n~_~n~~g~minimo damage: ~r~650~n~~w~Damage: ~g~980");
		PlayerTextDrawBackgroundColor(playerid, TextTeste[playerid][2], 20);
		PlayerTextDrawFont(playerid, TextTeste[playerid][2], TEXT_DRAW_FONT_1);
		PlayerTextDrawLetterSize(playerid, TextTeste[playerid][2], 0.230000, 1.099999);
		PlayerTextDrawColor(playerid, TextTeste[playerid][2], -65281);
		PlayerTextDrawSetOutline(playerid, TextTeste[playerid][2], 1);
		PlayerTextDrawSetProportional(playerid, TextTeste[playerid][2], true);

		TextTeste[playerid][3] = CreatePlayerTextDraw(playerid, 514.000000, 273.000000, "avisos: 1/10");
		PlayerTextDrawBackgroundColor(playerid, TextTeste[playerid][3], 20);
		PlayerTextDrawFont(playerid, TextTeste[playerid][3], TEXT_DRAW_FONT_2);
		PlayerTextDrawLetterSize(playerid, TextTeste[playerid][3], 0.220000, 1.000000);
		PlayerTextDrawColor(playerid, TextTeste[playerid][3], -16776961);
		PlayerTextDrawSetOutline(playerid, TextTeste[playerid][3], 1);
		PlayerTextDrawSetProportional(playerid, TextTeste[playerid][3], true);
	}
}

stock EndTeste(playerid, testeid, success)
{
	new Float:vhealth;
	new gstring[256];
	GetVehicleHealth(GetPlayerVehicleID(playerid), vhealth);
	if(success)
	{
		format(gstring, sizeof gstring,
		"---------- Aprovado ----------\n\
		Avisos de Velocidade: %d/%d\n\
	 	Avisos de Damage: %d/%d\n\
		Veiculo Damage: %.0f/%.0f\n\
		Tempo limite: %02d\n\
	 	{00CC00}---------- APROVADO ------------",
	 	GetPVarInt(playerid, "WarnningVelocidade"), W_Velocidade, GetPVarInt(playerid, "WarnningDamage"), W_Damage,
	 	vhealth, V_Damage, TempoTeste[playerid]);
	 	ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Resultado", gstring, "Fechar", "");
	 	PlayerPlaySound(playerid, 36205, 0.0, 0.0, 0.0);

	 	CheckConquista(playerid, Conquista_Motorista);
	}
	else
	{
		format(gstring, sizeof gstring,
		"---------- Reprovado ----------\n\
	 	Avisos de Velocidade: %d/%d\n\
	 	Avisos de Damage: %d/%d\n\
	 	Veiculo Damage: %.0f/%.0f\n\
	 	Tempo limite: %02d\n\
	 	{FF0000}---------- REPROVADO ------------",
	 	GetPVarInt(playerid, "WarnningVelocidade"), W_Velocidade, GetPVarInt(playerid, "WarnningDamage"), W_Damage,
	 	vhealth, V_Damage, TempoTeste[playerid]);
	 	ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Resultado", gstring, "Fechar", "");
	}
 	InTeste[playerid] = 0;
   	AtualCP[playerid] = 0;
   	TempoTeste[playerid] = 0;
   	DestroyVehicle(GetPVarInt(playerid, "CarroTeste"));
    DeletePVar(playerid, "CarroTeste");
    KillTimer(GetPVarInt(playerid, "TimerTeste"));
 	DeletePVar(playerid, "TimerTeste");

	for(new i = 0; i < 4; i++) {
		PlayerTextDrawDestroy(playerid, TextTeste[playerid][i]);
	}
	
	SetPlayerPos(playerid, -2033.3137,-117.4329,1035.1719);
	SetPlayerInterior(playerid, 3);
	DisablePlayerRaceCheckpoint(playerid);
	if(!success)
	{
	    SendClientMessage(playerid, 0xFF0000AA, "Você foi reprovado no teste.");
	    return true;
	}
	else
	{
	    if(testeid == 1)
	    {
		    SendClientMessage(playerid, 0x2ED82DAA, "Parabens!! Você foi aprovado e adquiriu a carteira de motorista.");
			if (!IsPlayerHaveItem(playerid, ITEM_TYPE_MOTORISTA))
			{
				givePlayerItem(playerid, ITEM_TYPE_MOTORISTA, 1581, 1, "Carteira de Motorista");
			}
		}
		else if(testeid == 2)
		{
	    	SendClientMessage(playerid, 0x2ED82DAA, "Parabens!! Você foi aprovado e adquiriu a licença de pilotagem.");
			if (!IsPlayerHaveItem(playerid, ITEM_TYPE_PILOTO))
			{
				givePlayerItem(playerid, ITEM_TYPE_PILOTO, 1581, 1, "Licenca de Piloto");
			}
		}
		else if(testeid == 3)
		{
	    	SendClientMessage(playerid, 0x2ED82DAA, "Parabens!! Você foi aprovado e adquiriu a licença Náutica.");
			if (!IsPlayerHaveItem(playerid, ITEM_TYPE_MARUJO))
			{
				givePlayerItem(playerid, ITEM_TYPE_MARUJO, 1581, 1, "Licenca Nautica");
			}
		}
		return true;
	}
}