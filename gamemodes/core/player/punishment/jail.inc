// Include
#include < YSI_Coding\y_hooks >

#include <jail_entry>
#include <jail_cmds>

static const Float:SpawnPrisao[][] = {
	{284.9987,1925.2871,1066.5540,0.2975},
	{291.3863,1925.2860,1066.5540,358.9214},
	{297.7576,1925.2850,1066.5540,0.7023},
	{304.1767,1925.2855,1066.5540,0.0547},
	{310.5291,1925.2837,1066.5540,0.0547},
	{317.0153,1925.2875,1066.5540,0.0547},
	{323.3083,1925.2859,1066.5540,0.0547},
	{328.4990,1931.6940,1066.5500,88.3751},
	{328.4987,1938.0900,1066.5500,89.3464},
	{328.4989,1944.4869,1066.5500,89.3464},
	{323.3480,1950.7059,1066.5540,178.3862},
	{316.9390,1950.7090,1066.5540,178.3862},
	{310.6028,1950.7065,1066.5540,178.3862},
	{304.1488,1950.7064,1066.5540,178.3862}
};

stock OnPlayerCheckJailed(playerid) 
{
    if (Player_GetJailTime(playerid) > 0) 
    {
        switch (Player_GetJailed(playerid)) {

            case 24: {
                new rdon = random(sizeof(SpawnPrisao));
                
                SetPlayerPos(playerid, SpawnPrisao[rdon][0], SpawnPrisao[rdon][1], SpawnPrisao[rdon][2]);
		        SetPlayerFacingAngle(playerid, SpawnPrisao[rdon][3]);
                SetPlayerVirtualWorld(playerid, 99);
                SetPlayerInterior(playerid, 1);

                GameTextForPlayer(playerid, "~r~~h~Aguarde um instante...", 5000, 1);
                FreezeThePlayer(playerid, 3000);
            }
            default: {
                new string[128];

                SetPlayerInterior(playerid, 5);
                SetPlayerPos(playerid, 324.4164,306.3444,999.1484); // Spawn Cadeia Admin

                if (PlayerInfo[playerid][pAgendado] == 1) {
                    format(string, sizeof(string), "STAFF: %s agendou você para (%d minutos de cadeia e %d avisos), motivo: %s",
                    PlayerInfo[playerid][pAdminAgendou], 
                    PlayerInfo[playerid][pTempoAgendado], 
                    PlayerInfo[playerid][pWarns], 
                    PlayerInfo[playerid][pMotivoAgendou]);

                    SendClientMessage(playerid, COLOR_LIGHTRED, string);

                    PlayerInfo[playerid][pAgendado] = 0;

                    Player_SetCadeia(playerid, 9, 
                        PlayerInfo[playerid][pTempoAgendado], 
                        PlayerInfo[playerid][pAdminAgendou], 
                        PlayerInfo[playerid][pMotivoAgendou], 
                        999);

                    if (PlayerInfo[playerid][pWarns] >= 3) {
                        format(string, sizeof(string), "STAFF: %s foi banido por (%d dias) automaticamente, motivo: %s",PlayerName[playerid], PlayerInfo[playerid][pWarns], PlayerInfo[playerid][pMotivoAgendou]);
                        SendClientMessageToAll(COLOR_LIGHTRED, string);
                        Banned_Player(Player_GetAccountID(playerid), 0, PlayerIP[playerid], "Limite de 3 avisos", (PlayerInfo[playerid][pWarns] * 3));
                        PlayerInfo[playerid][pWarns] = 0;
                        KickEx(playerid);
                        return 1;
                    }
                    format(string, sizeof(string), "[AGENDAMENTO]: %s logou e estava agendado para %d minutos de cadeia e %d avisos!", PlayerName[playerid], PlayerInfo[playerid][pTempoAgendado]/60, PlayerInfo[playerid][pWarns]);
                    SendClientMessageToAll(COLOR_LIGHTRED, string);
                }
                format(string, sizeof string, "[CADEIA-ADMIN]: Você tem %d prisões administrativas, ao atingir 20 ou mais, será punido com banimentos automáticos!", PlayerInfo[playerid][pPrisaoAdmin]);
                SendClientMessage(playerid, COLOR_LIGHTRED, string);

                SendMsgF(playerid, COLOR_LIGHTRED, "[CADEIA-ADMIN]: Você foi preso em %s pelo administrador %s, motivo: %s.", PlayerInfo[playerid][pPrisaoData], PlayerInfo[playerid][pRespPrisao], PlayerInfo[playerid][pMotivoPrisao]);
            }
        }
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ResetPlayerWeapons(playerid);
        SetPlayerSkin(playerid, 268);
        VozDePrisao[playerid] = 0;

        SendClientMessage(playerid, COLOR_LIGHTRED, "Sentença incompleta. Você voltou para a prisão para cumprir sua pena.");

        return 1;
    }
    return 0;
}

timer Exploding_Jail[TIME_EXPLOSION_JAIL * 1000](playerid)
{
    SetPVarInt(playerid, "player_exploding_jail", 0);

    if (!IsPlayerInRangeOfPoint(playerid, _JAIL_RANGE_, 1772.3076, -1548.2365, 9.9063)) 
    {
        JailInfo[jail_exploded] = false;
        SendClientMessageToAll(COLOR_LIGHTRED, "[Atenção]: A porta da "_JAIL_NAME" não pode ser explodida por algum motivo!");
        return SendClientMessage(playerid, COLOR_LIGHTRED, " Explosão abortada! você não está perto suficiênte da porta da prisão!");
    }
    JailInfo[object_explosao] = CreateDynamicObject(1654, 1772.0231, -1548.0222, 9.0072, -90.0, 0.0, random(360));

    PlayerInfo[playerid][pExplosives] = 0;
    SetPlayerExplosive(playerid, false);
    RemovePlayerAttachedObject(playerid, Slot_Explosivo);
    SetTimerEx("ExplosaoPorta", 10000, false, "d", playerid);

    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você plantou uma bomba na porta, agora afaste-se e espere explodir !");
    GameTextForPlayer(playerid, "~r~afaste-se da porta", 5000, 1);
    ClearAnimations(playerid, SYNC_ALL);
    
    return 1;
}

CALLBACK:ExplosaoPorta(playerid) 
{
    JailInfo[jail_exploded] = false;
    DestroyDynamicObject(JailInfo[object_explosao]);

    CreateExplosion(1772.3076, -1548.2365, 9.9063, 7, 1.0);

    new rand = random(10);

    switch(rand) 
    {
        case 0,1,2,4,5,6,7: {//Sucesso
            SendClientMessageToAll(COLOR_LIGHTRED, "[Atenção]: A porta da "_JAIL_NAME" foi explodida e todos os presidiários foram liberados!");
            SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você explodiu a porta da prisão !");

            SetTimer("LiberarPresos", 800, false);
            SendCopMessage(COLOR_LIGHTRED, "* Os presidiários da "_JAIL_NAME" escaparam! Para capturá-los novamente, Use /IMO em um fugitivo!");
        }
        default:{//Falhou
            SendClientMessageToAll(COLOR_LIGHTRED, "[Atenção]: A força da bomba não foi suficiente para explodir a porta da "_JAIL_NAME"!");
            SendClientMessage(playerid, COLOR_LIGHTRED, "* A força da bomba não foi suficiente !");
        }
    }

    return 1;
}

CALLBACK:LiberarPresos() 
{
    foreach(new i : Player) 
    {
        if (PlayerInfo[i][pJailed] == 24 && !GetPVarInt(i, "varFugitivo")) 
        {
            SetPlayerInterior(i, 0);
            SetPlayerVirtualWorld(i, 0);
            SetPlayerPos(i,1770.5781,-1546.5270,9.9245);
            SetPlayerFacingAngle(i, 45.7799);
            SetCameraBehindPlayer(i);

            SetPlayerHealth(i, 100.0);
            SetPlayerArmour(i, 0);
            
            SendClientMessage(i, COLOR_LIGHTRED,"* Você agora é um fugitivo da cadeia, corra e se esconda por 3 minutos!");
            GameTextForPlayer(i, "~r~Livre~n~~w~Se esconda por 3 minutos", 5000, 1);

            Player_SetHandcuffed(i, true);

            SetPVarInt(i, "varFugitivo", 1);
            SetPVarInt(i, "varTimerFugitivo", SetTimerEx("EscaparCadeia", 3*60000, false, "d", i));
        }
    }

    SoundInRange(14800, 200.0, 1772.3076, -1548.2365, 9.9063);
    return 1;
}

CALLBACK:EscaparCadeia(playerid)
{
    SetPVarInt(playerid, "varTimerFugitivo", -1);
    SetPVarInt(playerid, "varFugitivo", 0);
    
    Player_SetCadeia(playerid, 0, 0, "Nenhum", "Nenhum", 998);
    
    GameTextForPlayer(playerid, "~g~~h~Escapou com sucesso!", 7000, 1);

    SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
    ClearCrime(playerid);
    HidePlayerTimer(playerid);

    AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;

    Player_SetHandcuffed(playerid, false);
    ClearAnimations(playerid);

    PlayerPlaySound(playerid, 182, 0.0, 0.0, 0.0);
	
	SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, true);
    PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);

    return 1;
}

hook OnGameModeInit()
{
    Create3DTextLabel("{FFFFFF}Menu de Advogados\n{FFFFFF}Aperte a tecla {FF7766}"_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para ajustar um preso", 0xFFFFFFF6, 338.0980, 37.7896, 1001.5156, 5.0, 99);
    Create3DTextLabel("{FFFFFF}Área dos Fundos da Prisão\n{FFFFFF}Use o comando {FF7766}/explodirporta {FFFFFF}para iniciar a invasão", 0xFFFFFFFF, 1772.3076,-1548.2365,9.9063, 10.0, 0);

    CreateObject(19794, 1787.13, -1565.68, 11.9688, 0, 0, 0);
    PortaoLaSante[0] = CreateObject(19795, 1824.318481, -1534.731201, 14.296878 - 0.01, 0, 0, 343.0);
    PortaoLaSante[1] = CreateObject(19795, 1822.407592, -1540.949951, 14.296878 - 0.01, 0, 0, 163.0);
    PortaoLaSante[2] = CreateObject(19796, 1752.004150, -1591.186523, 14.267195 - 0.01, 0, 0, 77.0);
    PortaoLaSante[3] = CreateObject(19796, 1756.914062, -1592.316284, 14.267195 - 0.01, 0, 0, 257.0);

    LabelGates[0] = CreateDynamic3DTextLabel("Presídio La Sante\nAperte {FF7766}"_KEY_PATH_USE_HORN_COLOR" {FFFFFF}para abrir o portão", 0xFFFFFFFF, 1823.78, -1537.98, 13.54, 10.5);
    LabelGates[1] = CreateDynamic3DTextLabel("Presídio La Sante\nAperte {FF7766}"_KEY_PATH_USE_HORN_COLOR" {FFFFFF}para abrir o portão", 0xFFFFFFFF, 1754.27, -1592.18, 13.54, 10.5);

    CreateDynamicPickup(1247, 23, 1823.78, -1537.98, 13.54);//Peni Fora
	CreateDynamicPickup(1247, 23, 1754.27, -1592.18, 13.54);//Peni Fora
    CreateDynamicPickup(1654, 23, 1772.3076,-1548.2365,9.9063);//Explodir porta

    return 1;
}

hook OnPlayerConnect(playerid)
{
    RemoveBuildingForPlayer(playerid, 4000, 1787.13, -1565.68, 11.9688, 250.0);
	RemoveBuildingForPlayer(playerid, 4080, 1787.13, -1565.68, 11.9688, 250.0);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == KEY_CTRL_BACK || (IsPlayerInAnyVehicle(playerid) && newkeys == KEY_CROUCH))
	{
        if (IsPlayerInRangeOfPoint(playerid, 10.0, 1823.78, -1537.98, 13.54))
	    {
            if(!IsACop(playerid))
                return SendClientMessage(playerid, -1, "Você não é um policial e não tem acesso ao portão!");

	        if (PortaoEsquerdaLS == GATES_OPENING)
	        {
	            SendClientMessage(playerid, COLOR_YELLOW, "* Você deve esperar para que os portões se abram totalmente primeiro.");
	            return 1;
	        }
	        else if (PortaoEsquerdaLS == GATES_CLOSING)
	        {
	            SendClientMessage(playerid, COLOR_YELLOW, "* Você deve esperar para que os portões se fechem totalmente primeiro.");
	            return 1;
	        }
	        PlaySoundForPlayersInRange(1035, 50.0, 1823.78, -1537.98, 13.54);
	        if (PortaoEsquerdaLS == GATES_CLOSED)
	        {
				GameTextForPlayer(playerid, "~b~~h~La Sante~n~~b~~h~Abrindo Portoes!", 3000, 3);
		    	MoveObject(PortaoLaSante[0], 1824.318481, -1534.731201, 14.296878 + 0.01, 0.002, 0, 0, 258);
		    	MoveObject(PortaoLaSante[1], 1822.407592, -1540.949951, 14.296878 + 0.01, 0.002, 0, 0, 253);
		    	PortaoEsquerdaLS = GATES_OPENING;
	    	}
	    	else
	    	{
				GameTextForPlayer(playerid, "~b~~h~La Sante~n~~b~~h~Fechando Portoes!", 3000, 3);
		    	MoveObject(PortaoLaSante[0], 1824.318481, -1534.731201, 14.296878 - 0.01, 0.002, 0, 0, 343);
		    	MoveObject(PortaoLaSante[1], 1822.407592, -1540.949951, 14.296878 - 0.01, 0.002, 0, 0, 163);
		    	PortaoEsquerdaLS = GATES_CLOSING;
	    	}
	    }
	    else if (IsPlayerInRangeOfPoint(playerid, 10.0, 1754.27, -1592.18, 13.54))
	    {
            if(!IsACop(playerid))
                return SendClientMessage(playerid, -1, "Você não é um policial e não tem acesso ao portão!");

	        if (PortaoDireitaLS == GATES_OPENING)
	        {
	            SendClientMessage(playerid, COLOR_YELLOW, "* Você deve esperar para que os portões se abram totalmente primeiro..");
	            return 1;
	        }
	        else if (PortaoDireitaLS == GATES_CLOSING)
	        {
	            SendClientMessage(playerid, COLOR_YELLOW, "* Você deve esperar para que os portões se fechem totalmente primeiro..");
	            return 1;
	        }
	        PlaySoundForPlayersInRange(1035, 50.0, 1754.27, -1592.18, 13.54);
	        if (PortaoDireitaLS == GATES_CLOSED)
	        {
				GameTextForPlayer(playerid, "~b~~h~La Sante~n~~b~~h~Abrindo Portoes!", 3000, 3);
		    	MoveObject(PortaoLaSante[2], 1752.004150, -1591.186523, 14.267195 + 0.01, 0.002, 0, 0, 172);
		    	MoveObject(PortaoLaSante[3], 1756.914062, -1592.316284, 14.267195 + 0.01, 0.002, 0, 0, 187);
		    	PortaoDireitaLS = GATES_OPENING;
	    	}
	    	else
	    	{
				GameTextForPlayer(playerid, "~b~~h~La Sante~n~~b~~h~Fechando Portoes!", 3000, 3);
		    	MoveObject(PortaoLaSante[2], 1752.004150, -1591.186523, 14.267195 - 0.01, 0.002, 0, 0, 77);
		    	MoveObject(PortaoLaSante[3], 1756.914062, -1592.316284, 14.267195 - 0.01, 0.002, 0, 0, 257);
		    	PortaoDireitaLS = GATES_CLOSING;
	    	}
	    }
    }
    return 1;
}

hook OnObjectMoved(objectid)
{
    if (objectid == PortaoLaSante[0])
	{
	    if (PortaoEsquerdaLS == GATES_CLOSING)
		    PortaoEsquerdaLS = GATES_CLOSED;
	    else
		    PortaoEsquerdaLS = GATES_OPEN;
	}
	else if (objectid == PortaoLaSante[2])
	{
	    if (PortaoDireitaLS == GATES_CLOSING)
		    PortaoDireitaLS = GATES_CLOSED;
	    else
		    PortaoDireitaLS = GATES_OPEN;
	}
}


stock ShowSurrenderProposal(playerid) {
    new level = Player_GetWanted(playerid);
    if(level <= 0)
        return SendClientMessage(playerid, -1, "Você não está sendo procurado pela justiça.");

    new newTime = level * 40,
        oldTime = level * 180,
        tax = level * 120;

	format(MEGAString, sizeof(MEGAString), ""C_WHITE"Você recebeu uma proposta de acordo judicial para se entregar e reduzir seu tempo de prisão.\n\n\
        Tempo de prisão atual: "C_LIGHTRED"%s"C_WHITE"\n\
        Novo tempo de prisão proposto: "C_MONEY"%s"C_WHITE"\n\n\
        Por conta dos seus crimes, você deverá restituir "C_LIGHTRED"$%s"C_WHITE" ao governo.\n\n\
        Você aceita esse acordo judicial?", ConvertTime(oldTime), ConvertTime(newTime), getFormatText(tax));

	ShowPlayerDialog(playerid, 61, DIALOG_STYLE_MSGBOX, ""C_GRAY2"Acordo judicial", 
        MEGAString
    , "Aceitar", "Recusar");
    return 1;
}


hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    new string[128];
    if(dialogid == 60) {
		if (response)
        {
            if (!OrgsRoubo(playerid)) return SendClientMessage(playerid,-1, "Você precisa ser um gangster para explodir a porta da "_JAIL_NAME".");

            if (!IsPlayerInRangeOfPoint(playerid, _JAIL_RANGE_, 1772.3076, -1548.2365, 9.9063))
                return SendClientMessage(playerid, -1, "Você não está na porta da "_JAIL_NAME"");

            if (JailInfo[jail_exploded]) return SendClientMessage(playerid, -1, "A porta da "_JAIL_NAME", já está sendo explodida por um gangster!");

            if (PlayerInfo[playerid][pExplosives] < 1) return SendClientMessage(playerid, -1, "Você não tem um explosivo, compre um no mercado negro.");

            if (!GetPlayerHoldingExplosive(playerid)) 
			    return SendClientMessage(playerid, -1, "Você não está segurando um explosivo. (Use: /explosivo pegar)");

            if (!Founders_GetList(playerid) && Staff_GetWorking(playerid)) return SendClientMessage(playerid, -1, "Você não pode explodir em modo trabalho!");

            JailInfo[jail_exploded] = true;
            SetPVarInt(playerid, "player_exploding_jail", 1);
            defer Exploding_Jail(playerid);

            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            SetPlayerPos(playerid, 1772.0231,-1548.0222,9.9072);
            SetPlayerFacingAngle(playerid, 222.9846);

            ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.0, true, false, false, false, 0, SYNC_NONE);

            new count_amigos;
            foreach(new x : Player)
            {
                if (ProxDetectorS(100.0, playerid, x)) 
                {                
                    if (GetPlayerOrg(x) == GetPlayerOrg(playerid)) 
                        count_amigos++;
                }
            }

            if(!PrisonCamerasInfo[2][cameraDestroyed]) {
                if(GetPlayerOrg(playerid) == 0)
                    format(string, sizeof string, "[ATENÇÃO]: Os bandidos estão tentando explodir a "_JAIL_NAME"");
                else 
                    format(string, sizeof string, "[ATENÇÃO]: %s estão tentando explodir a "_JAIL_NAME"", GetOrgName(GetPlayerOrg(playerid)));
                    
                SendClientMessageToAll(COLOR_LIGHTRED, string);

                if(count_amigos > 0) {
                    SetPlayerCriminal(playerid, 255, "Formação de quadrilha");
                }
                SetPlayerCriminal(playerid, 255, "Posse de arma ilegal (explosivo)");
                SetPlayerCriminal(playerid, 255, "Vandalismo");
            }
            else {
                SendClientMessage(playerid, COLOR_LIGHTBLUE, "* As câmeras foram destruídas e os policiais não foram notificados!");
            }

            ShowPlayerBaloonInfo(playerid, "~r~PLANTANDO EXPLOSIVO...~n~~w~Espere a bomba ser plantada, depois afaste-se", 5000);
            return true;
        }
        else 
			return SendClientMessage(playerid,-1, "Você precisa ser um gangster para explodir a porta da "_JAIL_NAME".");
	}
    else if(dialogid == 61) {
        if(response) {
            new level = Player_GetWanted(playerid);
            new time = level * 40,
                tax = level * 120;
            if(time <= 0) {
                return SendClientMessage(playerid, -1, "Você não está sendo procurado pela justiça.");
            }

            Player_RemoveMoney(playerid, tax);
            Player_SetCadeia(playerid, 24, time, "Nenhum", PlayerCrime[playerid][pAccusedof], 999);

            format(string, sizeof(string), "Você se entregou e foi condenado a %s de prisão com %d níveis de procurado.", ConvertTempo(time), level);
	        SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

            format(string, sizeof(string), "* %s fez um acordo e se entregou para a justiça.", PlayerName[playerid]);
            SendClientMessageInRange(15.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

            SpawnPlayer(playerid);
            SetCameraBehindPlayer(playerid);
        }
        else {
            SendClientMessage(playerid, COLOR_LIGHTRED, "Você recusou a proposta de acordo para se entregar.");
        }
    }
	return 0;
}

stock GetPlayersInJail(delegacia) {
	new count;

	foreach(new i : Player) {
		if (Player_GetJailed(i) == delegacia) {
			count ++;
		}
	}
	return count;
}