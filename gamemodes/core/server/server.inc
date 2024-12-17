#include <YSI_Coding\y_hooks>

#include <server-restart>
#include <gas_station>
#include <house>
// #include <farms>
#include <jobs>
#include <operations>
#include <gangzone>
#include <kidnapping>

// #include <store>

#define CHAT_TYPE_NOOB 1

hook OnPlayerConnect(playerid)
{
	// Carregar as informações...
	CreateTextDraws(playerid);
	PlayerTextdraws_CreateOrgs(playerid);
	InitFly(playerid);

	SafeZones_ShowForPlayer(playerid);
	GangZones_CreateTextdraws(playerid);

	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	// Atualiza o contador de jogadores onlines
	UpdatePlayersON();

	// Loop em todos os jogadores onlines após deslogar (para checar relação com algo do jogador.)
	OnPlayerCheckInteractions(playerid);

	// ---------------------------------------
	// Resetando variáveis
	
	// Dialog (Listas)
	List_ResetPlayer(playerid);	

	// Timer do tutorial:
	KillTimer(PlayerInfo[playerid][pTimerTuto]);

	// ProgressBar
	DestroyPlayerProgressBar(playerid, BarSprayTag[playerid]);

	// Fader (ofuscar tela)
    gPlayerFadeInfo[playerid][fadeTimer] = 0;

	// Resetar o objeto de procura
	if (GetPVarInt(playerid, "varProcura") != INVALID_PLAYER_ID) {
	    DestroyDynamicObject(GetPVarInt(playerid, "objectProcurar"));
	}

	// Resetar skate
	if (SkateInfo[playerid][s_Setado])
	{
		if (SkateInfo[playerid][s_Andando]) 
			DestroyDynamicObject(SkateInfo[playerid][s_Skate]);

		guardarSkate(playerid);
	}

	if (GetPVarInt(playerid, "DominandoMN"))
	{
		DominandoMercadoNegro = 0;
	    KillTimer(GetPVarInt(playerid, "TimerDominandoMN"));
	    SetPVarInt(playerid, "TimerDominandoMN", -1);
	}

	if (GetPVarInt(playerid, "DominandoFM"))
	{
		DominandoFabricaMateriais = 0;
	    KillTimer(GetPVarInt(playerid, "TimerDominandoFM"));
	    SetPVarInt(playerid, "TimerDominandoFM", -1);
	}

	if (eEjet[playerid] != -1) 
		KillTimer(eEjet[playerid]);

	if (GetPVarInt(playerid, "VarBomba"))
	{
		new objectid = GetPVarInt(playerid, "VarObject");
		DestroyDynamicObject(objectid);
	}

	for(new coneid; coneid < MAX_CONE; ++coneid)
	    if (!strcmp(PlayerName[playerid], ConeInfo[coneid][coneOwner])) destroyCone(coneid);

	for(new barreiraid; barreiraid < MAX_BARREIRA; ++barreiraid)
		if (!strcmp(PlayerName[playerid], BarreiraInfo[barreiraid][barreiraOwner])) destroyBarreira(barreiraid);

	for(new bloqueioid; bloqueioid < MAX_BLOQUEIO; ++bloqueioid) 
		if (!strcmp(PlayerName[playerid], BloqueioInfo[bloqueioid][bloqueioOwner])) destroyBloqueio(bloqueioid);


    new string[256];

    switch(reason)
    {
        case 0:
		{
            new Float:x, Float:y, Float:z, clientVersion[12];

		    GetPlayerPos(playerid, x, y, z);
		    GetPlayerVersion(playerid, clientVersion, 12);

			format(
				string, sizeof(string), 
				"%s: saiu do servidor por erro de conexão ou crash. (ID: %d - Ping: %d - PL: %.2f)", 
				PlayerName[playerid],
				playerid,
				GetPlayerPing(playerid),
				NetStats_PacketLossPercent(playerid)
			);
		}
		case 1:
		{
		    // if (GetPVarInt(playerid, "InHeadShot"))
			// {
			// 	format(string, sizeof(string), "CADEIA: %s foi automaticamente preso por 30 minutos (Saiu durante o Head-Shot)",PlayerName[playerid]);
			// 	SendClientMessageToAll(COLOR_LIGHTRED, string);
			// 	server_log("cadeia", string);

			// 	Player_SetCadeia(playerid, 9, 30 * 60, "Admin Automático", "Saiu durante o Head-Shot", 999);
			// }
			
			if (gettime() < GetPVarInt(playerid, "varPlayerCombate") && GetPVarInt(playerid, "varPlayerCombateId") != INVALID_PLAYER_ID)
			{
				format(string, sizeof(string), "CADEIA: %s foi automaticamente preso por 20 minutos (Saiu durante um Combate)", PlayerName[playerid]);
				SendClientMessageToAll(COLOR_LIGHTRED, string);
				server_log("cadeia", string);

				Player_SetCadeia(playerid, 9, 20 * 60, "Admin Automático", "Saiu durante um Combate", 999);
			}

			format(string, sizeof(string), "%s: saiu do servidor por vontade propria.", PlayerName[playerid]);
		}
		case 2: format(string, sizeof(string), "%s: saiu do servidor kickado ou banido.", PlayerName[playerid]);
		default: format(string, sizeof(string), "%s: saiu do servidor por causa desconhecida.", PlayerName[playerid]);
	}

	if (SpectadorInfo[playerid][spectadorID] != INVALID_PLAYER_ID)
		SendClientMessageInRange(30.0, playerid, string, COLOR_BURNED_YELLOW, COLOR_BURNED_YELLOW, COLOR_BURNED_YELLOW, COLOR_BURNED_YELLOW, COLOR_BURNED_YELLOW);

	if (InTeste[playerid]) TestEnd(playerid, 0);

	DisablePlayerCheckpoint(playerid);

	if(GetPVarInt(playerid, "assaltado") == 1 && (GetPVarInt(playerid, "assaltoTempo") > gettime())) {
		callcmd::aceitar(playerid, "assalto");
	}
	
	if(VozDePrisao[playerid] == 1)
	{
		format(string, sizeof(string), "%s saiu do servidor com voz de prisao e foi preso automaticamente!", PlayerName[playerid]);
		SendClientMessageInRange(50.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		VozDePrisao[playerid] = 0;

		Player_SetCadeia(playerid, 9, 8 * 60, "Admin Automático", "Saiu durante a voz de prisão", 999);
	}

	new onlineCall = MobileInfo[playerid][mobileCall];
	if (onlineCall != MAX_PLAYERS+5)
	{
		SendClientMessage(onlineCall, -1, "((Chamada de voz)) Ligação encerrada.");
		MobileInfo[onlineCall][mobileCall] = MAX_PLAYERS+5, MobileInfo[playerid][mobileCall] = MAX_PLAYERS+5;
	}

	if (GetPVarInt(playerid, "Abordou"))
	{
		new idplayer = GetPVarInt(playerid, "Abordando");

		if (idplayer != INVALID_PLAYER_ID) {
			TogglePlayerControllable(idplayer, true);
			SetPVarInt(idplayer, "Abordado", 0);
		}
	}

	new assassinoid = GetChased[playerid];
    if (assassinoid != INVALID_PLAYER_ID) {
        if ((GotHit[playerid] > 0 && GotTri[playerid] > 0) && IsPlayerConnected(assassinoid)) {
			format(string, sizeof(string), "O seu contrato em %s (%d) foi cancelado pois ele se desconectou do servidor.", PlayerName[playerid], playerid);
        	SendClientMessage(assassinoid, COLOR_LIGHTRED, string);
		}
		GoChase[playerid] = INVALID_PLAYER_ID;
		GoChase[assassinoid] = INVALID_PLAYER_ID;
	}

	if (PlayerInfo[playerid][segurandoRadio] || idMySoundBox(playerid)) {
		givePlayerItem(playerid, ITEM_TYPE_RADIO, GetPVarInt(playerid, "modelidRadio"), 1, "Caixa de Som");
		destroyPlayerSound(playerid);
	}

	ServerLog::("logout", "%s(%d) [UserID: %d] deslogou do servidor.", PlayerName[playerid], playerid, Player_GetAccountID(playerid));

	if (Player_Logado(playerid)) {
		new Float:health, Float:armour;
		GetPlayerHealth(playerid, health);
		GetPlayerArmour(playerid, armour);
		PlayerInfo[playerid][pHealth] = health;
		PlayerInfo[playerid][pArmour] = armour;

		SavePlayerAccount(playerid, true);
	    playerCancelTrade(playerid);
	}
	DestroyPlayerMemory(playerid); // Economizando espaço

	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new lenn = strlen(inputtext);

	for(new tt; tt < lenn; tt++)
	    if (inputtext[tt] == 37) inputtext[tt] = '@';

	new string[256];

	if (dialogid == 29)
	{
 		if (!emailValido(inputtext))
	    {
	        format(string, sizeof string,
			"{FFFFFF}Bem vindo {00BFFF}%s{FFFFFF}, digite seu e-mail {00FF00}CORRETAMENTE\n\
			{FFFFFF}Você vai usar ele para recuperar sua senha, não esqueça o e-mail!\n\n\n\
			{FF0000}Você digitou um e-mail inválido...", PlayerName[playerid]);
	        ShowPlayerDialog(playerid, 2828, DIALOG_STYLE_INPUT, "E-mail", string, "Confirmar", "");
	    }
	    else
	    {
			format(PlayerInfo[playerid][pEmail], 128, inputtext);
			SplitColor(PlayerInfo[playerid][pEmail]);

			format(string, sizeof string, "Parabéns! Você definiu seu e-mail: {00FF00}%s{FFFFFF}, para trocar, use: /menu.", inputtext);
			SendClientMessage(playerid, -1, string);
	    }
	    return false;
	}

	if (dialogid == 10048)
	{
		if (response)
		{
			SendClientMessage(playerid, COLOR_GRAD, "Você confirmou o comando de trazer todos.");
			ConfirmacaoVidaColete(playerid);
			//ChamadaTrazerTodos(playerid); // Antiga chamada trazer todos
		}
		else {
			SendClientMessage(playerid, COLOR_GRAD, "Você cancelou o comando de trazer todos.");
		}
	}

	if (dialogid == 10049)
	{
		if (response)
		{
			confirmacaovida = 0;
			SendClientMessage(playerid, COLOR_GRAD, "Opção confirmada: Trazer todos sem colete.");
			ChamadaTrazerTodos(playerid);
		}
		else {
			confirmacaovida = 1;
			SendClientMessage(playerid, COLOR_GRAD, "Opção confirmada: Trazer todos com colete.");
			ChamadaTrazerTodos(playerid);
		}
	}

	if (dialogid == 10050)
	{
		if (response)
		{

			if (!Player_Logado(playerid))
				return SendClientMessage(playerid, COLOR_GRAD, "Você não está logado.");

			if (Player_GetJailed(playerid))
				return SendClientMessage(playerid, COLOR_GRAD, "Você não pode ir ao Administrador, pois você está preso.");

			if (IsPlayerInCombat(playerid))
				return SendClientMessage(playerid, COLOR_GRAD, "Você está em combate, por isso não pode ir até ao Administrador.");

			SetPlayerHealth(playerid, 100);
			
			if (confirmacaovida == 1) {
				SetPlayerArmour(playerid, 100);
			}
			else {
				SetPlayerArmour(playerid, 0);
			}
			
			SetPlayerPos(playerid, tzt[0], tzt[1], tzt[2]);
			SetPlayerInterior(playerid, tztinterior);
			SetPlayerVirtualWorld(playerid, tztworld);

			ResetPlayerWeapons(playerid);

			SendClientMessage(playerid, COLOR_GRAD, "Você foi à posição do(a) Administrador(a).");
		}
		else {
			SendClientMessage(playerid, COLOR_GRAD, "Você optou por não ir.");
		}

		return 1;
	}

	if (dialogid == 10052)
	{
		if (response)
		{
			avisomoderno = 1;
			SendClientMessage(playerid, -1, "Você selecionou a opção moderna.");
		}
		else {
			avisomoderno = 0;
			SendClientMessage(playerid, -1, "Você selecionou a opção simples.");
		}
	}

	if (dialogid == 14000)
	{
	    if (response)
	    {
	        new idx = SelectCannabis[playerid][listitem];

	        SetPlayerCheckpoint(playerid, CannabisInfo[idx][erva_x], CannabisInfo[idx][erva_y], CannabisInfo[idx][erva_z], 2.0);

	        SendClientMessage(playerid, COLOR_LIGHTRED, "Você localizou sua plantação de maconha, siga o ponto vermelho no mapa.");
	    }
	    return 1;
	}

	if (dialogid == 451)
	{
	    if (!response || listitem == -1) 
			return true;

	 	new rand = random(sizeof(CaminhaoSpawn));

		if (CaminhoesAtivos > 9) return SendClientMessage(playerid, -1, "Existem muitos caminhões alugados no momento, tente mais tarde!");

		if (Player_GetMoney(playerid) < CaminhaoPreco[listitem])
		{
			format(string, sizeof string, "Você não tem "C_MONEY"$%s{FFFFFF} na carteira.", getFormatText(CaminhaoPreco[listitem]));
			return SendClientMessage(playerid, -1, string);
		}
		PlayerCaminhao[playerid][caminhaoValid] = true;
		PlayerCaminhao[playerid][caminhaoId] = CreateVehicle(CaminhaoModel[listitem], CaminhaoSpawn[rand][0], CaminhaoSpawn[rand][1], CaminhaoSpawn[rand][2], CaminhaoSpawn[rand][3], -1, -1, -1);

		VehicleCaminhao[PlayerCaminhao[playerid][caminhaoId]][caminhaoVALID] = true;

		PlayerCaminhao[playerid][caminhaoMaxCarga] = CaminhaoMax[listitem];
		Player_RemoveMoney(playerid, CaminhaoPreco[listitem]);
		CaminhoesAtivos++;

  		// Limpa as animações e special action para não ter bugs
	    ClearAnimations(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		DisableRemoteVehicleCollisions(playerid, true);

		// Esconder o inventario
		Inventory_HideForPlayer(playerid);

		UnlockVehicleDoors(PlayerCaminhao[playerid][caminhaoId]);

  		// Colocar o jogador no drone
		PutPlayerInVehicle(playerid, PlayerCaminhao[playerid][caminhaoId], 0);

		SetPlayerMapIcon(playerid, 98, 1389.4375, 1173.9647, 10.7415, 0, 0xFFFF00FF, MAPICON_GLOBAL);
		SetPlayerMapIcon(playerid, 97, 1486.5421, 993.5022, 10.8203, 0, 0xFFFF00FF, MAPICON_GLOBAL);
        SendClientMessage(playerid, 0xE7CF90FF, "Tutorial: Foram marcados no mapa os locais onde você pode pegar comprar os produtos.");
	    return true;
	}

	// else if (dialogid == 452)
	// {
	//     if (!response) return true;

	// 	if(listitem == 0) {
	// 		MEGAString[0] = EOS;
	// 		strcat(MEGAString, "ID Propriedade\tPreço por Insumo\tInsumos Disponíveis\tTotal Disponível\n");

	// 		for(new i = 0; i != unid; i++) {
	// 			if(PropInfo[i][eLoaded]) {
	// 				if(PropInfo[i][eInsumosReq] > 0 && PropInfo[i][eTill] > 0 && PropInfo[i][ePrecoInsumo] > 0) {
	// 					new insumosPodePagar = PropInfo[i][eTill] / PropInfo[i][ePrecoInsumo];
	// 					new insumosCompra = (insumosPodePagar > PropInfo[i][eInsumosReq]) ? PropInfo[i][eInsumosReq] : insumosPodePagar;
	// 					// ID Prop - Preço por Insumo - Insumos Disponíveis para Compra - Total Disponível

	// 					format(string, sizeof(string), "{FFFFFF}%d %s\t"C_MONEY"$%s\t{FFFFFF}%d\t"C_MONEY"$%s\n", i, PropInfo[i][ePname], 
	// 						getFormatText(PropInfo[i][ePrecoInsumo]), insumosCompra, getFormatText(insumosCompra*PropInfo[i][ePrecoInsumo]));

	// 					strcat(MEGAString, string);
	// 				}
	// 			}
	// 		}
	// 		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "Propriedades", MEGAString, "Fechar", "");
	// 	}
	// 	else if(listitem == 1) {
	// 		MEGAString[0] = EOS;
	// 		strcat(MEGAString, "ID Fazenda\tPreço por Produto\tProdutos Disponíveis\tTotal Disponível\n");

	// 		foreach(new i : Fazendas) {
	// 			if(FBizzInfo[i][fbProductsReq] > 0 && FBizzInfo[i][fbTill] > 0) {
	// 				new produtosPodePagar = FBizzInfo[i][fbTill] / FBizzInfo[i][fbPriceProd];
	// 				new produtosCompra = (produtosPodePagar > FBizzInfo[i][fbProductsReq]) ? FBizzInfo[i][fbProductsReq] : produtosPodePagar;
	// 				// ID Prop - Preço por Insumo - Insumos Disponíveis para Compra - Total Disponível

	// 				format(string, sizeof(string), "{FFFFFF}%d %s\t"C_MONEY"$%s\t{FFFFFF}%d\t"C_MONEY"$%s\n", i, FBizzInfo[i][fbMessage], 
	// 					getFormatText(FBizzInfo[i][fbPriceProd]), produtosCompra, getFormatText(produtosCompra*FBizzInfo[i][fbPriceProd]));

	// 				strcat(MEGAString, string);
	// 			}
	// 		}
	// 		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "Fazendas", MEGAString, "Fechar", "");
	// 	}

	//     return true;
	// }

    else if (dialogid == 300) {

		if (response) {

			if (IsPlayerHaveItem(playerid, ITEM_TYPE_CHAVEFENDA) &&
	            IsPlayerHaveItem(playerid, ITEM_TYPE_CHAVEBIELA) &&
	            IsPlayerHaveItem(playerid, ITEM_TYPE_CHAVEFIXA)) {

				new id = GetPVarInt(playerid, "propId");

			   	if (gettime() < PropInfo[id][eRobbed]) {
			       	format(string, sizeof string, "* A empresa está se recuperando de um roubo recente. Há informações que novos fundos ...");
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					format(string, sizeof string, "... irão chegar em aproximadamente %s, até lá a empresa não pode ser roubada!", ConvertTime(PropInfo[id][eRobbed] - gettime()));
			        SendClientMessage(playerid, COLOR_LIGHTRED, string);
			        return 1;
				}

		   		if (PropInfo[id][eAlarm]) {
			        SendClientMessage(playerid, COLOR_LIGHTRED, "* O alarme já foi disparado !");
			        return 1;
				}

				foreach(new x : Player) {

				    if (GetPVarInt(x, "propId") == id && GetPVarInt(x, "desarmandoLasers")) {
				        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Alguém já está tentando desativar o alarme...");
				    }
				}

	            SetPVarInt(playerid, "desarmandoLasers", 1);

	            SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você está tentando desarmar os lasers, as chances de sucesso depende de sua habilidade com ferramentas.");

	            SetTimerEx("desarmarLaser", 70000 - (PlayerInfo[playerid][pFerSkill] * 1000), false, "i", playerid);

	            SetPlayerAttachedObject(playerid, Slot_Explosivo, 18644, 5, 0.089000,0.020000,-0.040999,0.000000,4.000048,0.000000,1.243999,1.297000,1.183000);

	            SetPlayerPos(playerid, 2146.8528,1612.1110,835.0683);
	            SetPlayerFacingAngle(playerid, 15.2500);

	       		ApplyAnimation(playerid, "CAMERA","piccrch_take", 4.0, true, false, false, false, 0);
				SetTimerEx(#SetAnimCofre, 500, false, "d", playerid);

			} else {

			    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você precisa de 3 ferramentas para tentar desarmar os lasers: Chave de Fenda, Chave Fixa e Chave Biela !");
			}
   		}
		return 1;
	}

	// else if (dialogid == 2667) {

	//     if (response && strlen(inputtext)) {

	//         SetPVarString(playerid, "multaMotivo", inputtext);

	// 		new id = GetPVarInt(playerid, "multarCarro");
	// 		new plate[10];
	// 		GetVehicleNumberPlate(id, plate);

	// 		static 
	// 			vehicle_name[32];

	// 		Vehicle_GetName(id, vehicle_name);

	// 		format(string, sizeof string,
	// 		"{33CCFF} * NOME DO CARRO: {AAAAAA}%s\n\
	// 		{33CCFF}PLACA: {AAAAAA}%s\n\n\
	// 		{FFFFFF}Digite abaixo o VALOR da multa:", vehicle_name, plate);

	// 		ShowPlayerDialog(playerid, 2668, DIALOG_STYLE_INPUT, " ", string, "Multar", "Cancelar");
	//     }
	//     return 1;
	// }

	if (dialogid == 145) {

	    if (response) {

			new id = GetPVarInt(playerid, "propId");
			new nomeLocal[50];
			format(nomeLocal, 50, "%s", PropInfo[id][ePname]);
			SetPVarString(playerid, "NomeLocal", nomeLocal);

			switch(listitem)
			{
			    case 0:
				{
					if (!IsPlayerOwnerPropertie(playerid, id))
					{
						if ( PropInfo[id][eLock] ) {
						    return SendClientMessage( playerid, -1, "A porta está trancada, apenas o dono pode entrar!" );
						}
						atualizarPropText( id );
						savePropertie( id );
					}

					PutPlayerInProperty( playerid, id );

					SetPlayerCP(playerid, 9988);
				}
			    case 1: {

			        if (IsPlayerOwnerPropertie(playerid, id) || IsAMember(playerid) || IsACop(playerid) ) {

						if ( PropInfo[id][eLock] && !IsPlayerOwnerPropertie(playerid, id)) {
						    return SendClientMessage( playerid, -1, "A porta está trancada, apenas o dono pode entrar!" );
						}

				        SetPlayerPos(playerid, 2151.8035,1609.6300,847.6677);
				        SetPlayerInterior(playerid, 10);
				        SetPlayerVirtualWorld(playerid, id + PROP_VW);

				        if (PropInfo[id][eAlarm]) {
				            PlayerPlaySound(playerid, 42801, 2146.67065, 1633.03381, 835.57257);
				        }
					} else {
					    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o dono do comércio e membros de organizações criminosas podem entrar !");
					}
			    }
			}
   		}
	    return 1;
	}

	if (dialogid == 4214) {

	    SetPVarInt(playerid, "doando", 0);

	    if (response) {

	        new valordoado = strval(inputtext);

	        if (valordoado < 100 or valordoado > 1000000)
	            return SendClientMessage(playerid, COLOR_LIGHTRED, "* O valor da doação deve estar entre $100 e $1.000.000 !");


	        if (Player_GetMoney(playerid) < valordoado)
	            return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não tem todo esse dinheiro para doar !");

			format(string, sizeof(string), "* %s doou $%s para o cofre do Governo", PlayerName[playerid], getFormatText(valordoado));
			SendMembersMessage(7, COLOR_LIGHTBLUE, string);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

			adicionarDinheiroGoverno(valordoado);
			Player_RemoveMoney(playerid, valordoado);
	    }
	    return true;
	}

	else if (dialogid == 4264)
	{
	    if (response)
		{
	        new id = TrashCan_Get(playerid);

			if (id == -1) return SendClientMessage(playerid, -1, "Você não está próximo de uma lixeira.");

			switch(listitem)
			{
			    case 0: SetPlayerLixeira(playerid);
			    case 1: TrashCan_DiscardItems(playerid);
				case 2: 
				{
					new descartado = 0;

					for (new item; item != MAX_ITENS_INVENTARIO; item++)
					{
						if (InventarioInfo[playerid][item][item_valid] && InventarioInfo[playerid][item][item_type] == ITEM_TYPE_LIXO) {
							if(TrashCan_GiveItem(id, InventarioInfo[playerid][item][item_type], InventarioInfo[playerid][item][item_model], 
								InventarioInfo[playerid][item][item_cor1], InventarioInfo[playerid][item][item_cor2], InvItem_GetQuantity(playerid, item), 
								InventarioInfo[playerid][item][item_nome])) {

								descartado += 1;
								InvItem_Reset(playerid, item);
							}
						}
					}
					SendMsgF(playerid, COLOR_LIGHTGREEN, "[Lixeira] Foram descartados %d itens de lixo do seu inventário.", descartado);
				}
			    case 3: TrashCan_ListItems(playerid, id);
			    case 4:
				{
				    if (!PlayerIsGari(playerid)) return SendClientMessage(playerid, -1, "Você não é um gari.");

				    if (!GetPVarInt(playerid, "emColetaLixo")) return SendClientMessage(playerid, -1, "Você precisa /iniciarcoleta para ensacar lixos.");

				    if (GetPVarInt(playerid, "pegouLixo")) return SendClientMessage(playerid, -1, "Você já está segurando uma sacola de lixo na mão, jogue-a no caminhão.");

				    if (gettime() < trashInfo[id][trashTime][playerid])
					{
					    format(string, sizeof (string), "Você precisa esperar {82E789}%s{FFFFFF} para ensacar os lixos dessa lixeira novamente, vá até a próxima.", ConvertTempo(trashInfo[id][trashTime][playerid] - gettime()));
						return SendClientMessage(playerid, -1, string);
					}

			        SetPVarInt(playerid, "pegouLixo", 1);
				    SetPlayerAttachedObject(playerid, Slot_Pizza, 1265, 6, 0.1990, -0.0210, 0.1810, 13.3000, -175.2000, -4.0999, 0.6060, 0.4709, 0.9160);
				    ApplyAnimation(playerid, "BOMBER", "BOM_Plant_2Idle", 4.1, false, true, true, false, 0);

				    SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você ensacou o lixo que estava nessa lixeira, aproxime-se da caçamba do caminhão!");

				    trashInfo[id][trashTime][playerid] = gettime() + 2 * 60;

				    new count;

				    for (new itens; itens != MAX_TRASH_ITENS; itens++)
					{
					    if (count > 4) break;

					    if (trashItens[id][itens][item_valid])
					    {
					        count++;

					    	trashItens[id][itens][item_valid]		= 0;
					    	trashItens[id][itens][item_type] 		= 0;
					    	trashItens[id][itens][item_model] 		= 0;
					    	trashItens[id][itens][item_cor1] 		= 0;
					    	trashItens[id][itens][item_cor2] 		= 0;
					    	trashItens[id][itens][item_quantia] 	= 0;
					    	format(trashItens[id][itens][item_nome], 75, "Nenhum");

					    	mysql_format(MySQL_Handle, string, sizeof (string), "UPDATE `lixeiras` SET `item_%d` = '0|0|0|0|0|0|Nenhum' WHERE `id` = '%d'", itens, id);
						    mysql_tquery(MySQL_Handle, string);
						}
					}

					SetPVarInt(playerid, "quantLixosPegou", count);

					TrashCan_UpdateText(id);
			    }
			}
		}
	    return 1;
	}

	else if (dialogid == 4265)
	{
		new id = TrashCan_Get(playerid);
		if (id == -1) 
			return SendClientMessage(playerid, -1, "Você não está próximo de uma lixeira.");

		if (!response) 
			return TrashCan_ShowDialog(playerid);

		if (!InvItem_IsValid(playerid, listitem)) 
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você selecionou um item inválido."), TrashCan_DiscardItems(playerid);

		if (InventarioInfo[playerid][listitem][item_vender]) 
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você está negociando esse item, não pode jogar fora."), TrashCan_DiscardItems(playerid);

		if (InventarioInfo[playerid][listitem][item_type] == ITEM_TYPE_SACOLAPREVISOES && InventarioInfo[playerid][listitem][item_type] == ITEM_TYPE_CAIXAGOLD)
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não pode descartar esse item na lixeira."), TrashCan_DiscardItems(playerid);

		if (InventarioInfo[playerid][listitem][item_type] == ITEM_TYPE_DRONE)
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não pode descartar um veículo de inventário na lixeira."), TrashCan_DiscardItems(playerid);

		if(strfind(InventarioInfo[playerid][listitem][item_nome], "INE", false) != -1)
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não pode descartar esse item na lixeira."), TrashCan_DiscardItems(playerid);

		new result = TrashCan_GiveItem(id, InventarioInfo[playerid][listitem][item_type], InventarioInfo[playerid][listitem][item_model], InventarioInfo[playerid][listitem][item_cor1], InventarioInfo[playerid][listitem][item_cor2],
			InvItem_GetQuantity(playerid, listitem), InventarioInfo[playerid][listitem][item_nome]);

		if (!result) 
			return SendClientMessage(playerid, -1, "A lixeira está sem espaço, jogue fora em outra lixeira.");

		format(string, sizeof string, "(( %s jogou fora %d unidade(s) de %s no lixo ))", PlayerName[playerid], InvItem_GetQuantity(playerid, listitem), InventarioInfo[playerid][listitem][item_nome]);
		SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

		InvItem_Reset(playerid, listitem);
		TrashCan_UpdateText(id);

		format(string, sizeof string, "[LIXEIRA %d]: %s jogou %d unidade(s) de %s.", id, PlayerName[playerid], InvItem_GetQuantity(playerid, listitem), InventarioInfo[playerid][listitem][item_nome]);
		server_log("lixeira", string);

	    return 1;
	}

    else if (dialogid == 4266)
	{
	    new id = TrashCan_Get(playerid);
		if (id == -1) return SendClientMessage(playerid, -1, "Você não está próximo de uma lixeira.");

		ClearAnimations(playerid);

	    if (response && listitem >= 0)
		{
			if (isInventoryFull(playerid))
	    		return SendClientMessage(playerid, -1, "Você não tem espaço no inventário."), TrashCan_ListItems(playerid, id);

			if (!trashItens[id][listitem][item_valid])
				return SendClientMessage(playerid, COLOR_LIGHTRED, "O item selecionado é inválido."), TrashCan_ListItems(playerid, id);

			if (trashItens[id][listitem][item_type] == ITEM_TYPE_LIXO)
				return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não pode pegar lixos."), TrashCan_ListItems(playerid, id);

			format(string, sizeof string, "(( %s pegou %d unidade(s) de %s no lixo ))", PlayerName[playerid], trashItens[id][listitem][item_quantia], trashItens[id][listitem][item_nome]);
			SendClientMessageInRange(25.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

			if (trashItens[id][listitem][item_type] == ITEM_TYPE_SACOLAPREVISOES)
				format(string, sizeof string, "%s encontrou {FDC945}SACOLA DE PREVISÕES {FFFFFF}na lixeira %d da cidade de Los Santos.", PlayerName[playerid], id), SendClientMessageToAll(-1, string);
			else if (trashItens[id][listitem][item_type] == ITEM_TYPE_CAIXAGOLD)
				format(string, sizeof string, "%s encontrou {FEE73A}CAIXA SURPRESA GOLD {FFFFFF}na lixeira %d da cidade de Los Santos.", PlayerName[playerid], id), SendClientMessageToAll(-1, string);

			format(string, sizeof string, "[LIXEIRA %d]: %s pegou %d unidade(s) de %s.", id, PlayerName[playerid], trashItens[id][listitem][item_quantia], trashItens[id][listitem][item_nome], id);
			server_log("lixeira", string);

			givePlayerItem(playerid, trashItens[id][listitem][item_type], trashItens[id][listitem][item_model], trashItens[id][listitem][item_quantia], trashItens[id][listitem][item_nome],
			trashItens[id][listitem][item_cor1], trashItens[id][listitem][item_cor2]);

			TrashCan_RemoveItem(id, listitem);
		}
	    else TrashCan_ShowDialog(playerid);

		return true;
	}

	else if (dialogid == 4267)
	{
	    if (!response) 
			return callcmd::gps(playerid);

		new 
			Float:x, 
			Float:y, 
			Float:z,
			trashid;

		switch (listitem)
		{
			case 0: {

				trashid = trashInfo[TrashCan_GetTheClosest(playerid)][trashObject];

				GetDynamicObjectPos(trashid, x, y, z);
			}
			default: {
				trashid = trashInfo[listitem-1][trashObject];

				GetDynamicObjectPos(trashid, x, y, z);
			}
		}

		SetPlayerCheckpoint(playerid, x, y, z, 5.0);
		SetPlayerCP(playerid, CP_NULL);

		new MapZone:zone = GetMapZoneAtPoint2D(x, y);
		new zone_name[MAX_MAP_ZONE_NAME];
		GetMapZoneName(zone, zone_name);

		format(string, sizeof string, "(GPS): "C_GRAY"Foi marcado no mapa em vermelho a lixeira %d | Local: %s", listitem-1, zone_name);
		SendClientMessage(playerid, COLOR_YELLOW, string);

	    return 1;
	}

	else if (dialogid == 4301)
	{
	    if (response)
		{
			if (!strlen(inputtext)) {
				InvItem_SetSelected(playerid, -1);
				return SendClientMessage(playerid, -1, "Você precisa digitar 'Confirmar' para dropar o item.");
			}

	        if (!strcmp(inputtext, "confirmar", true))
			{
		        if (InvItem_GetSelected(playerid) != -1)
				{
					droparItem(playerid, InvItem_GetSelected(playerid));
			    }
				else
				{
			        SendClientMessage(playerid, -1, "Você não selecionou nenhum item em seu inventário.");
				}
	        } else { 
				SendClientMessage(playerid, -1, "Você precisa digitar 'Confirmar' para dropar o item.");
				InvItem_SetSelected(playerid, -1);
			}
	    }
	    return true;
	}

	else if (dialogid == 9252) {

		if (response) {

			SetPVarInt(playerid, "familyCar", listitem);

			ShowModelSelectionMenu(playerid, CarrosFamilyList, "Escolha o novo carro", 200, 0x000000AA);
		}
		return 1;
	}

	else if (dialogid == 9842) {

	    if (response) {

	        new id = SelectFamily[playerid][listitem];

			SetPVarInt(playerid, "familyHQ", id);

	        Family_ShowInfo( playerid, id , false );
	    }
	    return 1;
	}

	else if (dialogid == 250) {

	    if (response) {

	        new id = GetPVarInt(playerid, "familyHQ");
			SendClientMessage(playerid, COLOR_LIGHTRED, "INFO: Siga o ponto vermelho no mapa!");
			SetPlayerCheckpoint(playerid, familyInfo[id][familySpawn][0],familyInfo[id][familySpawn][1],familyInfo[id][familySpawn][2], 5.0);
	    } else {
	        callcmd::familias(playerid);
	    }
	    return 1;
	}

	else if (dialogid == 122)
	{
		new index = GetPVarInt(playerid, "varAcessorio");
		DeletePVar(playerid, "varAcessorio");

		if ( accessoriesInfo[playerid][index][acc_valid] ) {

		    if ( response ) {
				if(IsAndroidPlayer(playerid))
					OpenMenuEditorItem(playerid, index);
				else
		        	EditAttachedObject(playerid, index);

		        format(string, sizeof string, "* %s está editando o acessório %s.", PlayerName[playerid], accessoriesInfo[playerid][index][acc_name]);
				server_log("inventarioitem", string);
		    }
			else
			{
				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

				givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, accessoriesInfo[playerid][index][acc_model], 1, accessoriesInfo[playerid][index][acc_name]);

				format(string, sizeof string, "Você retirou o acessório {00FFFF}%s {FFFFFF}e guardou no inventário!", accessoriesInfo[playerid][index][acc_name]);
		        SendClientMessage(playerid, -1, string);

		        format(string, sizeof string, "* %s retirou o acessório %s e guardou no inventário.", PlayerName[playerid], accessoriesInfo[playerid][index][acc_name]);
				server_log("inventarioitem", string);
				RemovePlayerAcessorie(playerid, index);
			}
		}
	    return 1;
	}

	else if (dialogid == 103)
	{
		if (!response) return true;

		switch (listitem)
		{
		    case 0:
		    {
		        new count = 0;

		        foreach(new i : Player)
				{
				    if (PlayerInfo[i][pLottoNr] != 0) count ++;
		        }

		        MEGAString[0] = EOS;

		        strcat(MEGAString, "Nº do Sorteio\tValor da aposta\tParticipantes Online\tValor do prêmio\n");

				format(string, sizeof string, "{9C9C9C}%d\t"C_MONEY"$100\t{00FF00}%d\t"C_MONEY"$%s\n", SorteioID, count, getFormatText(LotValue));
				strcat(MEGAString, string);

				ShowPlayerDialog(playerid, 104, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Lotérica » {00BFFF}Apostas", MEGAString, "Apostar", "Cancelar");
		    }
		    case 1:
		    {
		        MEGAString[0] = EOS;

		        strcat(MEGAString, "Nome do programa\tValor restante\tValor do saque\tAutorização\n");

				if (BolsaFamilia_GetActive())
				{
					format(string, sizeof string, "{9C9C9C}Bolsa Familia\t"C_MONEY"$%s\t"C_MONEY"$%s\t%s\n", getFormatText(BolsaFamilia[bolsaValor]),
					getFormatText(BolsaFamilia[bolsaLimite]), playerBolsaFamilia[playerid] ? ("{5DA9F1}Autorizado(a)") : ("{EC4444}Não autorizado(a)"));
				}
				else
				{
					format(string, sizeof string, "{EC4444}Indisponível\t"C_MONEY"$%s\t"C_MONEY"$%s\t{EC4444}Indisponível\n", getFormatText(BolsaFamilia[bolsaValor]), getFormatText(BolsaFamilia[bolsaLimite]));
				}
				strcat(MEGAString, string);

				ShowPlayerDialog(playerid, 114, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Governo » {00BFFF}Bolsa família", MEGAString, "Sacar", "Cancelar");
		    }
		    case 2:
		    {
				format(string, sizeof string, "Tipo de Imóvel\tTipo de Imposto\tValor p/hora\n\
				Casas\tIPTU\t"C_MONEY"$15\n\
				Propriedades\tIPTU\t"C_MONEY"$18\n\
				Veículos\tIPVA\t"C_MONEY"$8");

				ShowPlayerDialog(playerid, 105, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Lotérica » {00BFFF}Pagar as contas", string, "Prosseguir", "Cancelar");
			}
		}
		return true;
	}

	else if (dialogid == 104)
	{
		if (!response) return true;

		switch (listitem)
		{
		    case 0:
		    {
		        if (PlayerInfo[playerid][pLottoNr] > 0) return SendClientMessage(playerid, -1, "Você já tem um bilhete de loteria, aguarde o sorteio no próximo PayDay.");

		    	ShowPlayerDialog(playerid, 113, DIALOG_STYLE_INPUT, "{FFFFFF}Lotérica » {00BFFF}Apostas", "\n{FFFFFF}Abaixo digite o número que deseja apostar (de 1 a 100):", "Apostar", "Cancelar");
		    }
		}
		return true;
	}

	else if (dialogid == 113)
	{
		if (!response) return true;

	    if (!strlen(inputtext)) return SendClientMessage(playerid, COLOR_LIGHTRED, "Digite um número de 1 a 100.");

	    new lottonr = strval(inputtext);

 		if (lottonr < 1 || lottonr > 100) return SendClientMessage(playerid, -1, "Número da loteria, de 1 a 100.");

		if (PlayerInfo[playerid][pLottoNr] > 0) return SendClientMessage(playerid, -1, "Você já tem um bilhete de loteria.");

		if (Player_GetMoney(playerid) < 100) return SendClientMessage(playerid, -1, "Você não tem $100 para pagar o número de loteria.");

		format(string, sizeof(string), "* Você comprou um bilhete de loteria com número: %d.", lottonr);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

		Player_RemoveMoney(playerid, 170);
		PlayerInfo[playerid][pLottoNr] = lottonr, DepositPropertie(playerid, 30);

		return LotValue += 90;
	}

	else if (dialogid == 114)
	{
		if (!response) return true;

		if (!BolsaFamilia[bolsaFamilia]) return SendClientMessage(playerid, -1, "O programa bolsa família já foi finalizado ou não iniciaram ainda!");

	    if (!playerBolsaFamilia[playerid])
		{
		    SendClientMessage(playerid, -1, "Você não está autorizado a pegar o bolsa família.");
			return SendClientMessage(playerid, COLOR_LIGHTRED, "OBS: Você não estava logado na hora da liberação ou já pegou!");
		}

		if (BolsaFamilia[bolsaValor] < BolsaFamilia[bolsaLimite]) return SendClientMessage(playerid, -1, "O governo não poderá pagar o seu saque.");

		format(string, sizeof(string), "Bolsa família: {FFFFFF}Parabéns! Você sacou "C_MONEY"$%s {FFFFFF}do programa.", getFormatText(BolsaFamilia[bolsaLimite]));
		SendClientMessage(playerid, 0x92ED91FF, string);

		removerDinheiroGoverno(BolsaFamilia[bolsaLimite]);

		Player_AddMoney(playerid, BolsaFamilia[bolsaLimite]);
		BolsaFamilia[bolsaValor] -= BolsaFamilia[bolsaLimite], playerBolsaFamilia[playerid] = false;
		BolsaFamilia[bolsaSaques] += BolsaFamilia[bolsaLimite], BolsaFamilia[bolsaPlayers]++;

		return true;
	}

	else if (dialogid == 105)
	{
		if (response)
		{
		    new select_prop;
		    MEGAString [0] = EOS;
			switch (listitem) {

			    case 0: House_Fatura(playerid);
			    case 1:
				{
					strcat(MEGAString, "ID Nome da empresa\tFundos\tDespesas\tVencimento\n");
					for( new prop; prop != unid; prop++) {

			      		if (PropInfo[prop][eOwnerID] == PlayerInfo[playerid][pID]) {
							new days = TimestampToRemainingDays(PropInfo[prop][eVencimento]);
	          				if ( days <= 0 ) {
               					format(string, sizeof (string), "%02d  %s\tLuz e Água\t"C_MONEY"$%s\t{FF0000}VENCIDO\n", prop, PropInfo[prop][ePname], getFormatText(PropInfo[prop][eDespesas]));
			            	} else {
			            		format(string, sizeof (string), "%02d  %s\tLuz e Água\t"C_MONEY"$%s\t%d dias\n", prop, PropInfo[prop][ePname], getFormatText(PropInfo[prop][eDespesas]), days);
							}
							strcat(MEGAString, string);
							SelectEmpresa[playerid][select_prop] = prop;
							select_prop ++;
						}
					}
					ShowPlayerDialog(playerid, 108, DIALOG_STYLE_TABLIST_HEADERS, "Pagar suas despesas", MEGAString, "Pagar", "Voltar");
			    }
			    case 2:
				{
					strcat(MEGAString, "Carro\tTipo de despesa\tVencimento\n");
					foreach(new carro : IterPlayerVehicles[playerid]) {
						new Float:x, Float:y, Float:z;
						GetVehiclePos(PlayerVehicleInfo[playerid][carro][pvID], x, y, z);

						new vehicle_name[30];
						GetModelStaticNameFromId(GetVehicleModel(PlayerVehicleInfo[playerid][carro][pvID]), vehicle_name);

						new days = TimestampToRemainingDays(PlayerVehicleInfo[playerid][carro][pvDueDate]);
						if (days < 0) {
							format(string, sizeof string, "{00FFFF}%s\t{FFFFFF}IPVA e Documentos "C_MONEY"$%s\t{FF0000}VENCIDO\n",
							vehicle_name, getFormatText(PlayerVehicleInfo[playerid][carro][pvExpenses]));
						} else {
							format(string, sizeof string, "{00FFFF}%s\t{FFFFFF}IPVA e Documentos "C_MONEY"$%s\t%d dias\n",
							vehicle_name, getFormatText(PlayerVehicleInfo[playerid][carro][pvExpenses]), days);
						}
						strcat(MEGAString, string);

						SelectCarros[playerid][select_prop] = carro;
						select_prop ++;
					}
					if (!select_prop) {
						return SendClientMessage(playerid, -1, "Você não tem um veiculo");
					}
					ShowPlayerDialog(playerid, 107, DIALOG_STYLE_TABLIST_HEADERS, "Pagar suas despesas", MEGAString, "Pagar", "Voltar");

					return 1;
			    }
			}
		}
		return 1;
	}

	else if (dialogid == 107) {

	    if (response) 
		{
   			new carroid = SelectCarros[playerid][listitem];

	        if (GetPlayerMoney(playerid) < PlayerVehicleInfo[playerid][carroid][pvExpenses]) {
	            return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte, caso não pague perderá o carro !");
	        }

	        if (PlayerVehicleInfo[playerid][carroid][pvExpenses] < 1) {
	            return SendClientMessage(playerid, -1, "Não há despesas a ser pagas !");
	        }

			format(string, sizeof string, "Você pagou as despesas do carro {00FFFF}%v{FFFFFF}, total "C_MONEY"$%s{FFFFFF}!", GetVehicleModel(PlayerVehicleInfo[playerid][carroid][pvID]), getFormatText(PlayerVehicleInfo[playerid][carroid][pvExpenses]));
	        SendClientMessage(playerid, -1, string);

            new lucro = PagarICMS(PlayerVehicleInfo[playerid][carroid][pvExpenses]);
            DepositPropertie(playerid, lucro);

	        GivePlayerMoney(playerid, - PlayerVehicleInfo[playerid][carroid][pvExpenses]);
	        PlayerVehicleInfo[playerid][carroid][pvExpenses] = 0;
	        PlayerVehicleInfo[playerid][carroid][pvDueDate] = Now() + Days:15;
	        Player_SaveVehicle(playerid, carroid);
	    } else {
	        callcmd::loterica(playerid);
	    }
	    return 1;
	}

	else if (dialogid == 132) 
	{
	    if (response) 
		{
			if (IsPlayerHaveItem(playerid, ITEM_TYPE_CONTRATO)) 
			{
				SendClientMessage(playerid, -1, "Você usou um {00FFFF}Contrato Hospitalar{FFFFFF}. Os médicos te levaram até o local de spawn!");
				SetPVarInt(playerid, "LastPosLoadded", 1);
				RemoveQuantiaItem(playerid, ITEM_TYPE_CONTRATO);
				SpawnPlayer(playerid);
			} else {
			    SendClientMessage(playerid, -1, "Você não possui um Contrato Hospitalar!");
			}
	    } else {
	        SendClientMessage(playerid, -1, "Você não quis usar seu {00FFFF}Contrato Hospitalar{FFFFFF}, por isto permanecerá no hospital!");
	    }
		return 1;
	}
	else if (dialogid == 108) {

	    if (response && CountProperties(playerid)) {

   			new prop = SelectEmpresa[playerid][listitem];

			if (prop == INVALID_PROP_ID)
				return 1;

	        if (Player_GetMoney(playerid) < PropInfo[prop][eDespesas])
	            return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte, caso não pague perderá o comércio !");

			format(string, sizeof string, "Você pagou as despesas do comércio {00FFFF}%s{FFFFFF}, total "C_MONEY"$%s{FFFFFF}!", PropInfo[prop][ePname], getFormatText(PropInfo[prop][eDespesas]));
	        SendClientMessage(playerid, -1, string);

	        format(string, sizeof string, "%s pagou as despesas do comércio %d", PlayerName[playerid], prop);
	        server_log("propriedades", string);

			Player_RemoveMoney(playerid, PropInfo[prop][eDespesas]);
	        PropInfo[prop][eDespesas] = 0;
	        PropInfo[prop][eVencimento] = Now() + Days:7;

            new lucro = PagarICMS(PropInfo[prop][eDespesas]);
            DepositPropertie(currentInt[playerid], lucro);

	        savePropertie(prop);
	    } else {
	        callcmd::loterica(playerid);
	    }
	    return 1;
	}

	else if (dialogid == 7224) {

	    if (response) {
	        if (strlen (inputtext) > 0) {
	            new prop = SelectEmpresa[playerid][listitem];
	            format(string, sizeof string, "Você localizou o comércio {00FFFF}%s{FFFFFF}, siga a marca vermelha no mapa!", PropInfo[prop][ePname]);
				SendClientMessage(playerid, -1, string);

				new Float:x, Float:y, Float:z;
				GetPropertyEntrance(prop, x, y, z);
				SetPlayerCheckpoint(playerid, x, y, z, 5.0);
			}
	    } else {
	        if (GetPVarInt(playerid, "varTipoGps")) {
	        	callcmd::gps(playerid);
			}
	    }
	    return 1;
	}

	else if (dialogid == 131) 
	{
        if (response) 
		{
			if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");
            
            if (listitem == 0)
			{
                if (Player_GetMoney(playerid) < 3000) return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte!"), callcmd::enterexit(playerid, #);

                givePlayerItem(playerid, ITEM_TYPE_CONTRATO, 2894, 1, "Contrato Hospitalar");
                SendClientMessage(playerid, -1, "Você comprou {00FFFF}1 Contrato Hospitalar {FFFFFF}por "C_MONEY"$3.000{FFFFFF}!");
                adicionarDinheiroGoverno(3000);
				Player_RemoveMoney(playerid, 3000);
            }
            else if (listitem == 1)
			{
                if (Player_GetMoney(playerid) < 6000) return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte!"), callcmd::enterexit(playerid, #);

                givePlayerItem(playerid, ITEM_TYPE_CONTRATO, 2894, 2, "Contrato Hospitalar");
                SendClientMessage(playerid, -1, "Você comprou {00FFFF}2 Contratos Hospitalares {FFFFFF}por "C_MONEY"$6.000{FFFFFF}!");
                adicionarDinheiroGoverno(6000);
				Player_RemoveMoney(playerid, 6000);
            }
            else if (listitem == 2)
			{
                if (Player_GetMoney(playerid) < 15000) return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte!"), callcmd::enterexit(playerid, #);

                givePlayerItem(playerid, ITEM_TYPE_CONTRATO, 2894, 5, "Contrato Hospitalar");
                SendClientMessage(playerid, -1, "Você comprou {00FFFF}5 Contratos Hospitalares {FFFFFF}por "C_MONEY"$15.000{FFFFFF}!");
                adicionarDinheiroGoverno(15000);
				Player_RemoveMoney(playerid, 15000);
            }
        }
        return 1;
    }
	else if (dialogid == 101) {

	    if (response) {

	        if (listitem == 0)
			{
				if (Player_GetMoney(playerid) < 20)
				    return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte!");

				Player_RemoveMoney(playerid, 20);
			    givePlayerItem(playerid, ITEM_TYPE_COMIDACRU, 19580, 1, "Pizza");
			    SendClientMessage(playerid, -1, "Você comprou uma {00FFFF}Pizza Congelada {FFFFFF}por "C_MONEY"$20{FFFFFF}!");
                DepositPropertie(playerid, PagarICMS(20));
			}
	        else if (listitem == 1)
			{
				if (Player_GetMoney(playerid) < 11)
				    return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte!");

				Player_RemoveMoney(playerid, 11);
			    givePlayerItem(playerid, ITEM_TYPE_BEBIDA, 19835, 1, "Coca-Cola");
			    SendClientMessage(playerid, -1, "Você comprou uma {00FFFF}Coca-Cola {FFFFFF}por "C_MONEY"$11{FFFFFF}!");
                DepositPropertie(playerid, PagarICMS(11));
			}
	        else if (listitem == 2) {
				if (Player_GetMoney(playerid) < 15)
				    return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte!");

				Player_RemoveMoney(playerid, 15);
			    givePlayerItem(playerid, ITEM_TYPE_COMIDA, ITEM_MODEL_BURGUER, 1, "Hamburger");
			    SendClientMessage(playerid, -1, "Você comprou um {00FFFF}Hambúrger {FFFFFF}por "C_MONEY"$15{FFFFFF}!");
                DepositPropertie(playerid, PagarICMS(15));
			}
			else if (listitem == 3)
			{
				if (Player_GetMoney(playerid) < 80)
				    return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte!");

				Player_RemoveMoney(playerid, 80);
			    givePlayerItem(playerid, ITEM_TYPE_COMIDACRU, 19580, 5, "Pizza Congelada");
			    SendClientMessage(playerid, -1, "Você comprou 5 {00FFFF}Pizza Congelada {FFFFFF}por "C_MONEY"$80{FFFFFF}!");
                DepositPropertie(playerid, PagarICMS(80));
			}
	        else if (listitem == 4)
			{
				if (Player_GetMoney(playerid) < 50)
				    return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte!");

				Player_RemoveMoney(playerid, 50);
			    givePlayerItem(playerid, ITEM_TYPE_BEBIDA, 19835, 5, "Coca-Cola");
			    SendClientMessage(playerid, -1, "Você comprou 5 {00FFFF}Coca-Cola {FFFFFF}por "C_MONEY"$50{FFFFFF}!");
                DepositPropertie(playerid, PagarICMS(50));
			}
	        else if (listitem == 5)
			{
				if (Player_GetMoney(playerid) < 65)
				    return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte!");

				Player_RemoveMoney(playerid, 65);
			    givePlayerItem(playerid, ITEM_TYPE_COMIDA, ITEM_MODEL_BURGUER, 5, "Hamburger");
			    SendClientMessage(playerid, -1, "Você comprou 5 {00FFFF}Hambúrger {FFFFFF}por "C_MONEY"$65{FFFFFF}!");
                DepositPropertie(playerid, PagarICMS(65));
			}
	    }
	    return 1;
	}
	else if (dialogid == 102) {

	    if (response) {

			if (Player_GetMoney(playerid) < 250) {
			    return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiênte!");
			}
			Player_RemoveMoney(playerid, 250);
			DepositPropertie( playerid, 250);

	        if (listitem == 0) {
			    givePlayerItem(playerid, ITEM_TYPE_BEBIDA, 19820, 1, "Tval");
			    SendClientMessage(playerid, -1, "Você comprou a bebida {00FFFF}Tval {FFFFFF}por "C_MONEY"$250{FFFFFF}!");
			}
	        else if (listitem == 1) {
			    givePlayerItem(playerid, ITEM_TYPE_BEBIDA, 19821, 1, "Gorbach");
			    SendClientMessage(playerid, -1, "Você comprou a bebida {00FFFF}Gorbach {FFFFFF}por "C_MONEY"$250{FFFFFF}!");
	        }
	        else if (listitem == 2) {
			    givePlayerItem(playerid, ITEM_TYPE_BEBIDA, 19822, 1, "Vinho");
			    SendClientMessage(playerid, -1, "Você comprou um {00FFFF}Vinho {FFFFFF}por "C_MONEY"$250{FFFFFF}!");
	        }
	        else if (listitem == 3) {
			    givePlayerItem(playerid, ITEM_TYPE_BEBIDA, 19823, 1, "Big Cook");
			    SendClientMessage(playerid, -1, "Você comprou a bebida {00FFFF}Big Cook {FFFFFF}por "C_MONEY"$250{FFFFFF}!");
	        }
	        else if (listitem == 4) {
			    givePlayerItem(playerid, ITEM_TYPE_BEBIDA, 19824, 1, "Champagne");
			    SendClientMessage(playerid, -1, "Você comprou um {00FFFF}Champagne {FFFFFF}por "C_MONEY"$250{FFFFFF}!");
	        }
	    }
	    return 1;
	}

	else if (dialogid == 100) {

	    if (response) {
			if (listitem >= 0)
	        	activeGPSLocation(playerid, listitem);
	    } else {
	        callcmd::gps(playerid);
	    }
	    return 1;
	}

	else if (dialogid == 109) 
	{
	    if (response) {
			if (listitem >= 0)
	        	SelectLocalTransfender(playerid, listitem);
	    } else {
	        callcmd::gps(playerid);
	    }
	    return 1;
	}

	else if (dialogid == 8714)
	{
		if (response)
		{
		    switch(listitem)
			{
		        case 0:{
					if (Admin_GetNivel(playerid) < MASTER) {
						return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
					}
					show_server_log(playerid, inputtext, "casas");
				}
		        case 1:{
					if (Admin_GetNivel(playerid) < MASTER) {
						return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
					}
					show_server_log(playerid, inputtext, "propriedades");
				}
		        case 2:{
					if (Admin_GetNivel(playerid) < MASTER) {
						return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
					}
					show_server_log(playerid, inputtext, "fempresas");
				}
		        case 3:{
					if (Admin_GetNivel(playerid) < MASTER) {
						return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
					}
					show_server_log(playerid, inputtext, "cash");
				}
		        case 4:{
		            if (Dev_GetNivel(playerid) < DEV_DELTA) 
						return SendClientMessage(playerid, -1 ,"Você não tem autorização para usar esse comando.");

					show_server_log(playerid, inputtext, "ip");
				}
		        case 5:show_server_log(playerid, inputtext, "ban");
		        case 6:show_server_log(playerid, inputtext, "kick");
		        case 7:show_server_log(playerid, inputtext, "cadeia");
		        case 8:show_server_log(playerid, inputtext, "anuncios");
		        case 9:show_server_log(playerid, inputtext, "contratos");
		        case 10:{
		            if (Admin_GetNivel(playerid) < MASTER) {
		                return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
		            }
					show_server_log(playerid, inputtext, "administracao");
				}
		        case 11:{
		            if (Admin_GetNivel(playerid) < MASTER) {
		                return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
		            }
					show_server_log(playerid, inputtext, "helper");
				}
		        case 12:{
		            if (Admin_GetNivel(playerid) < MASTER) {
		                return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
		            }
					show_server_log(playerid, inputtext, "limparadmin");
				}
		        case 13:{
		            if (Admin_GetNivel(playerid) < MASTER) {
		                return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
		            }
					show_server_log(playerid, inputtext, "limparhelper");
				}
		        case 14:{
		            if (Admin_GetNivel(playerid) < DIRETOR) {
		                return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
		            }
					show_server_log(playerid, inputtext, "senhaadmin");
				}
		        case 15:{
		            if (Admin_GetNivel(playerid) < DONO) {
		                return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
		            }
					show_server_log(playerid, inputtext, "gmx");
				}
		        case 16:show_server_log(playerid, inputtext, "lideres");
		        case 17:{
		            if (Admin_GetNivel(playerid) < MASTER) {
		                return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
		            }
					show_server_log(playerid, inputtext, "atendimento");
				}
		        case 18:show_server_log(playerid, inputtext, "xiters");
		        case 19:show_server_log(playerid, inputtext, "sms");
		        case 20:show_server_log(playerid, inputtext, "mudarnick");
		        case 21:{
		            if (Admin_GetNivel(playerid) < MASTER) {
		                return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
		            }
					show_server_log(playerid, inputtext, "chat_admin");
				}
		        case 22:{
		            if (Admin_GetNivel(playerid) < MASTER) {
		                return SendClientMessage(playerid, -1, "Você não tem permissão para ver este log!");
		            }
					show_server_log(playerid, inputtext, "comandosadmin");
				}
		        case 23:show_server_log(playerid, inputtext, "anorg");
				case 24:show_server_log(playerid, inputtext, "su");
				case 25:{
					if (Dev_GetNivel(playerid) < DEV_DELTA) 
						return SendClientMessage(playerid, -1 ,"Você não tem autorização para usar esse comando.");
						
					show_server_log(playerid, inputtext, "chat_gestor");
				}
		    }
		}
	    return 1;
	}

    else if (dialogid == DIALOG_ID_B)
    {
        if (!response) return false;

        if(FloorRequestedBy_B[listitem] != INVALID_PLAYER_ID || IsFloorInQueue_B(listitem))
            GameTextForPlayer(playerid, "~r~Este andar ja esta na fila", 3500, 4);
		else if(DidPlayerRequestElevator_B(playerid))
		    GameTextForPlayer(playerid, "~r~Voce ja chamou o elevador", 3500, 4);
		else
	        CallElevator_B(playerid, listitem);

		return true;
    }

	else if (dialogid == 8715) {
		if (Admin_GetNivel(playerid) >= MODERADOR) {
			return callcmd::verlogs(playerid);
		}
	}
	else if (dialogid == 7642)
	{
	    if (response && listitem >= 0)
		{
			new idPlayer = List_GetPlayers(playerid, listitem);
			if (idPlayer != INVALID_PLAYER_ID) {
				SetPVarInt(idPlayer, "varNegociando", playerid);

				if (!ProxDetectorS(15.0, playerid, idPlayer)) {
					return SendClientMessage(playerid, -1, "O jogador não está mais perto de você !");
				}

				if (GetPVarInt(idPlayer, "p_intrade"))
					return SendClientMessage(playerid, -1, "O jogador já está negociando com alguém !");

				if (InvItens_GetFreeSlots(playerid) < 4)
					return SendClientMessage(playerid, -1, "Você deve ter pelo menos 4 slots livres em seu inventário.");

				format(string, sizeof(string), "* Oferta de item: Você quer iniciar negociações com %s, aguarde o mesmo aceitar...", PlayerName[idPlayer]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

				MEGAString[0] = EOS;

				format(MEGAString, 350, "{FFFFFF}* %s quer iniciar negociações com você, deseja aceitar?\n\n{FF5500}OBS: {999999}Será aberta uma janela para negociar.", PlayerName[playerid]);
				ShowPlayerDialog(idPlayer, 7643, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Aceitar", "Recusar");
			}
		} else {
		    SetPVarInt(playerid, "Negociando", 0);
		}
	    return 1;
	}

	else if (dialogid == 7643) {

        SetPVarInt(playerid, "Negociando", 0);

        new idPlayer = GetPVarInt(playerid, "varNegociando");

	    if (response) {

			if (!ProxDetectorS(15.0, playerid, idPlayer)) {
			    return SendClientMessage(playerid, -1, "O jogador não está mais perto de você !");
			}

			if (GetPVarInt(idPlayer, "p_intrade"))
			    return SendClientMessage(playerid, -1, "O jogador já está negociando com alguém !");

			if (InvItens_GetFreeSlots(playerid) < 4)
			    return SendClientMessage(playerid, -1, "Você deve ter pelo menos 4 slots livres em seu inventário.");

			if (IsPlayerInAnyVehicle(idPlayer))
			    return SendClientMessage(playerid, -1, "O jogador que você tentou negociar está em um veículo!");

			if(playerid == idPlayer) {
				ServerLog::("bug_negociar", "%s está tentando negociar consigo mesmo.", PlayerName[playerid]);
				return 1;
			}

            playerShowTrade(playerid, idPlayer);
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você recusou iniciar negociações.");
		    SendClientMessage(idPlayer, COLOR_LIGHTRED, "* O jogador recusou-se a iniciar negociações com você.");
		}
	    return 1;
	}

	else if (dialogid == 8974) {

	    if (response) {

			if (OwnerMercadoNegro == 11 || OwnerMercadoNegro == 34) return SendClientMessage(playerid, -1, "A Polícia apreendeu os produtos do mercado negro, volte quando a máfia retomar o controle.");

	        if (listitem == 0) {

				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

				if (Player_GetMoney(playerid) < 1300) return SendClientMessage(playerid, -1, "Você não pode pagar pelo explosivo ($1300)");

	            givePlayerItem(playerid, ITEM_TYPE_EXPLOSIVO, 1654, 1, "Explosivo");
	            SendClientMessage(playerid, -1, "Você comprou um {00FFFF}Explosivo C4{FFFFFF} por "C_MONEY"$1300{FFFFFF}, abra seu inventário para usá-la!");
				Player_RemoveMoney(playerid, 1300);
				OrgInfo_SetMoney(OwnerMercadoNegro, OrgInfo_GetMoney(OwnerMercadoNegro) + 1300/2);
				DepositPropertie( playerid, 1300/2 );
				SendMembersMessage(OwnerMercadoNegro, -1, "Alguém comprou um {00FFFF}Explosivo C4{FFFFFF} no mercado negro, vocês lucraram "C_MONEY"$1150{FFFFFF}!");
	        }
	        else if (listitem == 1) 
			{
				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

				if(Player_GetMoney(playerid) < 1400)
				    return SendClientMessage(playerid, -1, "Você não pode pagar pela Mina Terrestre ($1400)");

	            givePlayerMina(playerid);
	            SendClientMessage(playerid, -1, "Você comprou uma {00FFFF}Mina Terrestre{FFFFFF} por "C_MONEY"$1400{FFFFFF}, abra seu inventário para usá-la!");
				Player_RemoveMoney(playerid, 1400);
				OrgInfo_SetMoney(OwnerMercadoNegro, OrgInfo_GetMoney(OwnerMercadoNegro) + 1400/2);
				DepositPropertie( playerid, 1400/2);
				SendMembersMessage(OwnerMercadoNegro, -1, "Alguém comprou um {00FFFF}Mina Terrestre{FFFFFF} no mercado negro, vocês lucraram "C_MONEY"$700{FFFFFF}!");
	        }
	        else if (listitem == 2) {

				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

				if(Player_GetMoney(playerid) < 1090)
				    return SendClientMessage(playerid, -1, "Você não pode pagar pela semente ($90)");

                givePlayerItem(playerid, ITEM_TYPE_SEMENTE, 1575, 1, "Semente de maconha");
	            SendClientMessage(playerid, -1, "Você comprou uma {00FFFF}Semente de maconha{FFFFFF} por "C_MONEY"$1090{FFFFFF}, use-a em seu inventário!");
				Player_RemoveMoney(playerid, 1090);
				OrgInfo_SetMoney(OwnerMercadoNegro, OrgInfo_GetMoney(OwnerMercadoNegro) + 1090/2);
				DepositPropertie( playerid, 1090/2 );
				SendMembersMessage(OwnerMercadoNegro, -1, "Alguém comprou uma {00FFFF}Semente de Maconha{FFFFFF} no mercado negro, vocês lucraram "C_MONEY"$1045{FFFFFF}!");
	        }
	        else if (listitem == 3) {

				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

				if (Player_GetMoney(playerid) < 1020) return SendClientMessage(playerid, -1, "Você não pode pagar por isto ($1020)");

                givePlayerItem(playerid, ITEM_TYPE_WEAPON, 41, 500, "Lata de Spray");

	            SendClientMessage(playerid, -1, "Você comprou uma {00FFFF}Lata de Spray{FFFFFF} por "C_MONEY"$1020{FFFFFF}!");
				Player_RemoveMoney(playerid, 1020);
				OrgInfo_SetMoney(OwnerMercadoNegro, OrgInfo_GetMoney(OwnerMercadoNegro) + 1020/2);
				DepositPropertie( playerid, 1020/2 );
				SendMembersMessage(OwnerMercadoNegro, -1, "Alguém comprou uma {00FFFF}Lata de Spray{FFFFFF} no mercado negro, vocês lucraram "C_MONEY"$510{FFFFFF}!");
	        }
	        else if (listitem == 4) {

				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

				if(Player_GetMoney(playerid) < 1060) return SendClientMessage(playerid, -1, "Você não pode pagar por isto ($1060)");

                givePlayerItem(playerid, ITEM_TYPE_WEAPON, 8, 1, "Katana");

	            SendClientMessage(playerid, -1, "Você comprou uma {00FFFF}Katana{FFFFFF} por "C_MONEY"$1060{FFFFFF}!");
				Player_RemoveMoney(playerid, 1060);
				OrgInfo_SetMoney(OwnerMercadoNegro, OrgInfo_GetMoney(OwnerMercadoNegro) + 1060/2);
				DepositPropertie( playerid, 1060/2 );
				SendMembersMessage(OwnerMercadoNegro, -1, "Alguém comprou uma {00FFFF}Katana{FFFFFF} no mercado negro, vocês lucraram "C_MONEY"$530{FFFFFF}!");
	        }
	        else if (listitem == 5) {

				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

				if (Player_GetMoney(playerid) < 3000) return SendClientMessage(playerid, -1, "Você não pode pagar por isto ($3.000)");

                givePlayerGunBox(playerid, GUNBOX_SMALL);

	            SendClientMessage(playerid, -1, "Você comprou uma {00FFFF}Caixa de equipamentos P{FFFFFF} por "C_MONEY"$3.000{FFFFFF}!");
				Player_RemoveMoney(playerid, 3000);
				OrgInfo_SetMoney(OwnerMercadoNegro, OrgInfo_GetMoney(OwnerMercadoNegro) + 3000/2);
				DepositPropertie( playerid, 3000/2 );
				SendMembersMessage(OwnerMercadoNegro, -1, "Alguém comprou uma {00FFFF}Caixa de equipamentos P{FFFFFF} no mercado negro, vocês lucraram "C_MONEY"$1.500{FFFFFF}!");
	        }
	        else if (listitem == 6) {

				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

				if(Player_GetMoney(playerid) < 5000)
				    return SendClientMessage(playerid, -1, "Você não pode pagar por isto ($5.000)");

                givePlayerGunBox(playerid, GUNBOX_NORMAL);

	            SendClientMessage(playerid, -1, "Você comprou uma {00FFFF}Caixa de equipamentos M{FFFFFF} por "C_MONEY"$5.000{FFFFFF}!");
				Player_RemoveMoney(playerid, 5000);
				OrgInfo_SetMoney(OwnerMercadoNegro, OrgInfo_GetMoney(OwnerMercadoNegro) + 5000/2);
				DepositPropertie( playerid, 5000/2 );
				SendMembersMessage(OwnerMercadoNegro, -1, "Alguém comprou uma {00FFFF}Caixa de equipamentos M{FFFFFF} no mercado negro, vocês lucraram "C_MONEY"$2.500{FFFFFF}!");
	        }
	        else if (listitem == 7) {

				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

				if(Player_GetMoney(playerid) < 6000) return SendClientMessage(playerid, -1, "Você não pode pagar por isto ($6.000)");

                givePlayerGunBox(playerid, GUNBOX_BIG);

	            SendClientMessage(playerid, -1, "Você comprou uma {00FFFF}Caixa de equipamentos G{FFFFFF} por "C_MONEY"$6.000{FFFFFF}!");
				Player_RemoveMoney(playerid, 6000);
				OrgInfo_SetMoney(OwnerMercadoNegro, OrgInfo_GetMoney(OwnerMercadoNegro) + 6000/2);
				DepositPropertie( playerid, 6000/2 );
				SendMembersMessage(OwnerMercadoNegro, -1, "Alguém comprou uma {00FFFF}Caixa de equipamentos G{FFFFFF} no mercado negro, vocês lucraram "C_MONEY"$3.000{FFFFFF}!");
	        }
	    }
		return 1;
	}

	else if(dialogid == 1950)
	{
	    if (response)
		{
	        if (listitem == 0)
			{
	            showDialogMenuConfig(playerid);
	        }
	        else if (listitem == 1)
			{
			    if (PlayerInfo[playerid][pVIP] < 1 && !Admin_GetNivel(playerid))
				{
					SendClientMessage(playerid, -1, "Você não é um jogador Sócio.");
					DialogShow_MenuPlayer(playerid);
				}
				else showDialogMenuVIPConfig(playerid);
	        }
	        else if (listitem == 2)
			{
	            showDialogCash(playerid);
	        }
	        else if (listitem == 3)
			{
	            showDialogMenuConselho(playerid);
	        }
   		}
	    else SendClientMessage(playerid, COLOR_LIGHTRED, "Você fechou o menu principal.");

	    return true;
	}

   	else if (dialogid == 1951)
	{
	    if (response)
		{
		    switch (listitem)
		    {
				case 0:
		        {
		            new playerHitSoundID = PlayerInfo[playerid][pHitSoundID];

		            if (playerHitSoundID == 17802)
		       			playerHitSoundID = 1095;
		            else if (playerHitSoundID == 1095)
		       			playerHitSoundID = 1055;
					else if (playerHitSoundID == 1055)
		       			playerHitSoundID = 1130;
		       		else
						playerHitSoundID = 17802;

					PlayerInfo[playerid][pHitSoundID] = playerHitSoundID;

					// #if defined _INC_WEAPON_CONFIG
		            // 	CheckDamageSounds(playerid);
					// #endif

					showDialogMenuConfig(playerid);
				}
		        case 1:
		        {
					if (PlayerInfo[playerid][pHitSound][0] && !PlayerInfo[playerid][pHitSound][1]) {
						PlayerInfo[playerid][pHitSound][0] = false;
						PlayerInfo[playerid][pHitSound][1] = true;
					}
					else if (!PlayerInfo[playerid][pHitSound][0] && PlayerInfo[playerid][pHitSound][1]) {
						PlayerInfo[playerid][pHitSound][0] = true;
						PlayerInfo[playerid][pHitSound][1] = false;
					}
					else if (PlayerInfo[playerid][pHitSound][0] && PlayerInfo[playerid][pHitSound][1]) {
						PlayerInfo[playerid][pHitSound][0] = false;
						PlayerInfo[playerid][pHitSound][1] = false;
					}
					else {
						PlayerInfo[playerid][pHitSound][0] = true;
						PlayerInfo[playerid][pHitSound][1] = true;
					}

					// #if defined _INC_WEAPON_CONFIG
		            // 	CheckDamageSounds(playerid);
					// #endif

					showDialogMenuConfig(playerid);
				}
				case 2:
				{
				    if (!PlayerInfo[playerid][pChatMorro])		PlayerInfo[playerid][pChatMorro] = true;
	                else if (PlayerInfo[playerid][pChatMorro])	PlayerInfo[playerid][pChatMorro] = false;

	                showDialogMenuConfig(playerid);
				}
				case 3:
				{
					new style_view = PlayerInfo[playerid][style_view_rg];

					if (style_view == MODEL_VIEW_DIALOG) 
					{	// Estilo mensagem
						PlayerInfo[playerid][style_view_rg] = MODEL_VIEW_MESSAGE;
					} 
					else // Estilo dialog
					{
						PlayerInfo[playerid][style_view_rg] = MODEL_VIEW_DIALOG;
					}
					
					showDialogMenuConfig(playerid);
				}
				case 4:
				{
				    if (PlayerInfo[playerid][pVIP] < 8) return SendClientMessage(playerid, COLOR_LIGHTRED, "Opção disponível apenas para jogadores Sócio Extreme.");

					if (!PlayerInfo[playerid][pAutoCaixinha]) 		PlayerInfo[playerid][pAutoCaixinha] = true;
	                else if (PlayerInfo[playerid][pAutoCaixinha]) 	PlayerInfo[playerid][pAutoCaixinha] = false;

					showDialogMenuConfig(playerid);
				}
				case 5:
				{
					if(GetPVarInt(playerid, "ChatEmpregoDesativado") == 0) {
						SetPVarInt(playerid, "ChatEmpregoDesativado", 1);
					}
					else {
						SetPVarInt(playerid, "ChatEmpregoDesativado", 0);
					}
					showDialogMenuConfig(playerid);
				}
				#if SERVER_ID == 3
				case 6: {
					Consumable_Config(playerid);
					showDialogMenuConfig(playerid);
				}
				case 7:
				#else
				case 6:
				#endif
				{
					showDialogTrocarEmail(playerid);
				}
				
				default:
				{
				    showDialogMenuConfig(playerid); SendClientMessage(playerid, COLOR_LIGHTRED, "O sistema está temporáriamente inativo.");
				}
			}

		} else {
		    callcmd::menu(playerid);
  		}
		return 1;
	}

	else if (dialogid == 1958)
	{
	    if (response)
		{
	        if (listitem == 0)
			{
	            if (!PhoneOnline[playerid]) 		PhoneOnline[playerid] = true;
                else if (PhoneOnline[playerid]) 	PhoneOnline[playerid] = false;
			}
	        else if (listitem == 1)
			{
				if (!PlayerInfo[playerid][pChatVip])		PlayerInfo[playerid][pChatVip] = true;
                else if (PlayerInfo[playerid][pChatVip])	PlayerInfo[playerid][pChatVip] = false;
			}
			showDialogMenuVIPConfig(playerid);
		} else {
		    callcmd::menu(playerid);
  		}
		return 1;
	}

	else if (dialogid == 1959) {

	    if (response) {

	        if (listitem == 0) {
				if (PlayerInfo[playerid][pHidePar])			PlayerInfo[playerid][pHidePar] = false;
                else if (!PlayerInfo[playerid][pHidePar])	PlayerInfo[playerid][pHidePar] = true;
			}
			else if (listitem == 1) {
				callcmd::desativarnoob(playerid);
			}
			else if (listitem == 2) {
				callcmd::gmxautomatico(playerid);
			}
			else if (listitem == 3) {
				callcmd::logchat(playerid);
			}
			else if (listitem == 4) {
				callcmd::eventoaleatorio(playerid);
			}
			else if(listitem == 5) {
				Logger_ToggleDebug("commands", false);
				format(string, sizeof string, "AdmCmd: Admin %s desativou o log de comandos.", PlayerName[playerid]);
				Staff_ChatToAll(COLOR_LIGHTRED,string);
			}
			showDialogMenuConselho(playerid);
		} else {
		    callcmd::menu(playerid);
  		}
		return 1;
	}

	else if (dialogid == 9832)
	{
	    if (response) {

	        new idcash;

			sscanf(inputtext, "u", idcash);

	        if (!Player_Logado(idcash)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

			SetPVarInt(playerid, "TransferirCash", idcash);

			MEGAString[0] = EOS;

			format(string, sizeof string, "{FFFFFF} » {00FF00}CASH » {FFFFFF} Você está prestes a transferir Cash para: {00FFFF}%s\n\n", PlayerName[idcash]);
			strcat(MEGAString, string);

			format(string, sizeof string, "{F5DEB3}Saldo atual: {00FF00}${FFFFFF}%s\n\n", getFormatText(Player_GetCash(playerid)));
			strcat(MEGAString, string);

			format(string, sizeof string, "{FFFFFF}* Digite a quantidade de Cash que deseja transferir:\n\n");
			strcat(MEGAString, string);

			strcat(MEGAString, "{FF6347}OBS: {B4B5B7}Consulte a quantidade de cash que possui para não dar transferência inválida.\n");

			ShowPlayerDialog(playerid, 8611, DIALOG_STYLE_INPUT, "{FFFFFF} » {00FFFF}CASH » {FFFFFF}Transferir Cash !", MEGAString, "Continuar", "Voltar");
	    } else {
	        callcmd::menu(playerid);
	    }
	    return 1;
	}

	else if (dialogid == 8611) {

	    if (response) {
	        new idcash = GetPVarInt(playerid, "TransferirCash");
	        new quantidade = strval(inputtext);

            if (!Player_Logado(idcash)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

            if (quantidade < 1 || quantidade > 1000000) 
				return SendClientMessage(playerid, -1, "A quantidade que você digitou é inválida ou muito alta!");

			SetPVarInt(playerid, "TransferirCashTotal", quantidade);

			MEGAString[0] = EOS;

			strcat(MEGAString, "{FFFFFF} » {00FF00}CASH » {FFFFFF} Transferência quase concluída !\n\n");

			format(string, sizeof string, "{F5DEB3}Destinatário: {FFFFFF}%s\n", PlayerName[idcash]);
			strcat(MEGAString, string);
			format(string, sizeof string, "{F5DEB3}Valor da transferência: {00FF00}${FFFFFF}%s\n\n", getFormatText(quantidade));
			strcat(MEGAString, string);

			if (Player_GetCash(playerid) >= quantidade) {
				format(string, sizeof string, "{F5DEB3}Seu saldo atual: {00FF00}${FFFFFF}%s\n", getFormatText(Player_GetCash(playerid)));
				strcat(MEGAString, string);
				format(string, sizeof string, "{F5DEB3}Saldo após a transferência: {00FF00}${FFFFFF}%s\n\n", getFormatText(Player_GetCash(playerid) - quantidade));
				strcat(MEGAString, string);
			} else {
				strcat(MEGAString, "{F5DEB3}Seu saldo atual: {FF0000}Insuficiênte\n");
				strcat(MEGAString, "{F5DEB3}Saldo após a transferência: {FF0000}Insuficiênte\n\n");
			}

			strcat(MEGAString, "{FFFFFF}* Caso você queira confirmar a transferência, digite {00FFFF}''{00FF00}CONFIRMAR{00FFFF}''\n\n");

			strcat(MEGAString, "{FF6347}OBS: {B4B5B7}Tenha cuidado, pois este valor que você está transferindo não é reembolsável.\n");

			ShowPlayerDialog(playerid, 9871, DIALOG_STYLE_INPUT, "{FFFFFF} » {00FFFF}CASH » {FFFFFF}Transferir Cash !", MEGAString, "Continuar", "");
	    } else {
	        callcmd::menu(playerid);
	    }
	    return 1;
	}

	else if (dialogid == 9871)
	{
	    if (response)
		{
			if (!strlen(inputtext)) return SendClientMessage(playerid, COLOR_LIGHTRED, " Você não escreveu ''CONFIRMAR'' e a transferência foi cancelada !");

	        if (!strcmp(inputtext, "confirmar", true))
			{
		        new idcash = GetPVarInt(playerid, "TransferirCash");
		        new quantidade = GetPVarInt(playerid, "TransferirCashTotal");

                if (!Player_Logado(idcash)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	            if(quantidade < 1 || quantidade > 1000000) return SendClientMessage(playerid, -1, " A quantidade que você digitou é inválida !");
				if (quantidade > Player_GetCash(playerid)) return SendClientMessage(playerid, -1, " Você não possui essa quantidade de cash !");

				SetPVarInt(playerid, "TransferirCashTotal", quantidade);

				Player_AddCash(idcash, quantidade);
				Player_RemoveCash(playerid, quantidade);

				format(string, sizeof string, "* Você recebeu $%s de cash de %s, utilize-os como desejar !", getFormatText(quantidade), PlayerName[playerid]);
				SendClientMessage(idcash, COLOR_LIGHTBLUE, string);

				// Som do PIX
				PlayerPlaySound(playerid, 20801, 0.0, 0.0, 0.0);

				format(string, sizeof string, "* Você transferiu $%s de cash para %s, transferência concluida com sucesso !", getFormatText(quantidade), PlayerName[idcash]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

				format(string, sizeof string, "CASH: %s transferiu $%s de cash para %s !", PlayerName[playerid], getFormatText(quantidade), PlayerName[idcash]);
			 	Staff_ChatToAll(COLOR_LIGHTGREEN,string);
				server_log("cash", string);

				MEGAString[0] = EOS;

				strcat(MEGAString, "{FFFFFF} » {00FF00}CASH » {FFFFFF} Transferência concluída !\n\n");

				format(string, sizeof string, "{F5DEB3}Destinatário: {FFFFFF}%s\n", PlayerName[idcash]);
				strcat(MEGAString, string);
				format(string, sizeof string, "{F5DEB3}Valor da transferência: {00FF00}${FFFFFF}%s\n\n", getFormatText(quantidade));
				strcat(MEGAString, string);

				format(string, sizeof string, "{F5DEB3}Seu saldo atual: {00FF00}${FFFFFF}%s\n\n", getFormatText(Player_GetCash(playerid)));
				strcat(MEGAString, string);

				strcat(MEGAString, "{FF6347}OBS: {B4B5B7}Caso a transferência foi feita para o ID errado, contate um admin imediatamente.\n");

				ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFFFFF} » {00FFFF}CASH » {FFFFFF}Transferência concluida !", MEGAString, "Fechar", "");

				MEGAString[0] = EOS;

				strcat(MEGAString, "{FFFFFF} » {00FF00}CASH » {FFFFFF} Você acaba de receber Cash !\n\n");

				format(string, sizeof string, "{F5DEB3}Remetente: {FFFFFF}%s\n", PlayerName[playerid]);
				strcat(MEGAString, string);
				format(string, sizeof string, "{F5DEB3}Valor da transferência: {00FF00}${FFFFFF}%s\n\n", getFormatText(quantidade));
				strcat(MEGAString, string);

				format(string, sizeof string, "{F5DEB3}Seu saldo atual: {00FF00}${FFFFFF}%s\n\n", getFormatText(Player_GetCash(idcash)));
				strcat(MEGAString, string);

				strcat(MEGAString, "{FF6347}OBS: {B4B5B7}Agora você pode gastar seus Cash utilizando o comando /menucash.\n");

				ShowPlayerDialog(idcash, 0, DIALOG_STYLE_MSGBOX, "{FFFFFF} » {00FFFF}CASH » {FFFFFF}Transferência concluida !", MEGAString, "Fechar", "");


	        } else {
	            SendClientMessage(playerid, COLOR_LIGHTRED, " Você não escreveu ''CONFIRMAR'' e a transferência foi cancelada !");
	        }
	    }
	    return 1;
	}

	else if (dialogid == 9872)
	{
	    if (response)
		{
			if (!strlen(inputtext)) {
				InvItem_SetSelected(playerid, -1);
				return SendClientMessage(playerid, COLOR_LIGHTRED, "Você precisa digitar 'CONFIRMAR' para dropar o ITEM.");
			}

	        if (!strcmp(inputtext, "confirmar", true))
			{
		        if (InvItem_GetSelected(playerid) != -1)
				{
					droparItem(playerid, InvItem_GetSelected(playerid));
			    } else {
			        SendClientMessage(playerid, COLOR_LIGHTRED, "Você não selecionou nenhum item.");
				}
	        } else {
	            SendClientMessage(playerid, COLOR_LIGHTRED, "Você precisa digitar 'CONFIRMAR' para dropar o ITEM.");
				InvItem_SetSelected(playerid, -1);
	        }
	    }
	    return 1;
	}

	else if(dialogid == 1960)
	{
	    if (response)
		{
	        if (!IsPlayerHaveItem(playerid, ITEM_TYPE_CONSUMIVEL) && !IsPlayerHaveItemModel(playerid, ITEM_MODEL_NAMEVEH))
	        	return SendClientMessage(playerid, -1, "Você não possui o item de adicionar nick no veículo.");

	    	if (strlen(inputtext) > 28) 
				return SendClientMessage(playerid, -1, "O nick que você digitou é muito grande para adicionar.");

            new itemid = GetPVarInt(playerid, "mudarNickVehID");
            new modelid = InventarioInfo[playerid][itemid][item_model];

			new vehicle_name[30];
			GetModelStaticNameFromId(modelid, vehicle_name);

            format(string, sizeof string, "%s %s", vehicle_name, inputtext);
	 		format(InventarioInfo[playerid][itemid][item_nome], 75, string);
	 		SplitColor(InventarioInfo[playerid][itemid][item_nome]);

	 		removerItemTypeModel(playerid, ITEM_TYPE_CONSUMIVEL, ITEM_MODEL_NAMEVEH);

	 		format(string, sizeof(string), "((ITEM)) {FFFFFF}%s usou o item: {00BFFF}Nick no veículo de inv{FFFFFF}, mudou para %s.", PlayerName[playerid], string);
		    SendClientMessageToAll(0x00AA00FF, string);

		    Inventory_UpdateSlot(playerid, InvItem_GetSelected(playerid));

			return 1;
		}
	    return 0;
	}

	else if (dialogid == 1961)
	{
	    if (response && strlen(inputtext ) > 5)
		{
	        new playerclick = List_GetPlayers(playerid, listitem);

			if (!Player_Logado(playerclick)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

			format(string, sizeof (string), "%d", playerclick);
			callcmd::ocorrencia(playerid, string);
	    }
	    return 1;
	}
	else if (dialogid == 450)
	{
	    if (response)
		{

	        MEGAString[0] = EOS;

			if (!strlen(inputtext))
			{
			    strcat(MEGAString, "\n		{FF6347}CADEIA ADMINISTRATIVA\n\n");

				strcat(MEGAString, "{7D8084}Você está condenado pela administração do servidor\n");
				format(string, 128, "{7D8084}O seu tempo de punição é de {7D8084}+%s {7D8084}minutos\n", ConvertTime(PlayerInfo[playerid][pJailTime]));
				strcat(MEGAString, string);
				strcat(MEGAString, "{7D8084}Você pagou uma multa para o denunciante, (minutos vezes 500)\n");

				strcat(MEGAString, "\n		{FEE73A}DÚVIDAS FREQUENTES\n");

				strcat(MEGAString, "\n{7D8084}PERGUNTA: {DBDCE0}Como eu vejo as regras do servidor?\n");
				strcat(MEGAString, "{49E468}RESPOSTA: {DBDCE0}Acesse o fórum: "SERVER_SITE"\n");

				strcat(MEGAString, "\n{7D8084}PERGUNTA: {DBDCE0}Eu fui punido injustamente, como proceder?\n");
				strcat(MEGAString, "{49E468}RESPOSTA: {DBDCE0}Abra uma denúncia no fórum com o nome do administrador que te puniu\n");

				strcat(MEGAString, "\n{7D8084}PERGUNTA: {DBDCE0}Como funciona o tempo de punição?\n");
				strcat(MEGAString, "{49E468}RESPOSTA: {DBDCE0}Você fica preso por 20 minutos vezes quantas Prisões Admin (/rg) você tem!\n");

				strcat(MEGAString, "\n{DBDCE0}Quando terminar de ler digite {00FF00}ENTENDI {DBDCE0}para fechar.\n");

				ShowPlayerDialog(playerid, 450, DIALOG_STYLE_INPUT, "{7D8084}Informações da cadeia administrativa", MEGAString, "Confirmar", "");
			}

	        if (!strcmp(inputtext, "entendi", true))
				return SendClientMessage(playerid, -1, "Você nos informou que entendeu sobre a sua punição!");

			else
			{
	            strcat(MEGAString, "\n		{FF6347}CADEIA ADMINISTRATIVA\n\n");

				strcat(MEGAString, "{7D8084}Você está condenado pela administração do servidor\n");
				format(string, 128, "{7D8084}O seu tempo de punição é de {7D8084}+%s {7D8084}minutos\n", ConvertTime(PlayerInfo[playerid][pJailTime]));
				strcat(MEGAString, string);
				strcat(MEGAString, "{7D8084}Você pagou uma multa para o denunciante, (minutos vezes 500)\n");

				strcat(MEGAString, "\n		{FEE73A}DÚVIDAS FREQUENTES\n");

				strcat(MEGAString, "\n{7D8084}PERGUNTA: {DBDCE0}Como eu vejo as regras do servidor?\n");
				strcat(MEGAString, "{49E468}RESPOSTA: {DBDCE0}Acesse o fórum: "SERVER_SITE"\n");

				strcat(MEGAString, "\n{7D8084}PERGUNTA: {DBDCE0}Eu fui punido injustamente, como proceder?\n");
				strcat(MEGAString, "{49E468}RESPOSTA: {DBDCE0}Abra uma denúncia no fórum com o nome do administrador que te puniu\n");

				strcat(MEGAString, "\n{7D8084}PERGUNTA: {DBDCE0}Como funciona o tempo de punição?\n");
				strcat(MEGAString, "{49E468}RESPOSTA: {DBDCE0}Você fica preso por 20 minutos vezes quantas Prisões Admin (/rg) você tem!\n");

				strcat(MEGAString, "\n{DBDCE0}Quando terminar de ler digite {00FF00}ENTENDI {DBDCE0}para fechar.\n");

				ShowPlayerDialog(playerid, 450, DIALOG_STYLE_INPUT, "{7D8084}Informações da cadeia administrativa", MEGAString, "Confirmar", "");
	        }
	    }
	    return 1;
	}

	else if (dialogid == 7765)
	{
	    if (response)
		{
			if (!strlen(inputtext)) return SendClientMessage(playerid, COLOR_LIGHTRED, " Você não escreveu ''TROCAS'' ou ''SEM-TROCAS'' e a renovação foi cancelada !");

			if (!strcmp(inputtext, "trocas", true))
			{
				new id = GetPlayerFamily(playerid);

				if (id != -1)
				{
					if (Player_GetCash(playerid) < 40000) 
						return SendClientMessage(playerid, -1, "Você não possui essa quantidade em cash.");

					if (isInventoryFull(playerid))
						return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

					familyInfo[id][familyVencimento] += Days:30;
					Player_RemoveCash(playerid, 40000);
					givePlayerItem(playerid, ITEM_TYPE_NICK, 19792, 15, "Troca de Nick (familia)");

					Family_Save(id);

					SendClientMessage(playerid, -1, "Você renovou a família em +30 dias e recebeu 15 trocas de item no inventário, por: {00FF00}40.000 {FFFFFF}de cash");

				    // LOGS
				    format(string, sizeof string, "[%s] %s renovou a família em +30 dias", familyInfo[id][familyName], PlayerName[playerid]);
				    server_log("family", string);
				}
			}
			else if (!strcmp(inputtext, "sem-trocas", true))
			{
				new id = GetPlayerFamily(playerid);

				if (id != -1)
				{
					if (Player_GetCash(playerid) < 20000) return SendClientMessage(playerid, -1, "Você não possui essa quantidade em cash.");

					familyInfo[id][familyVencimento] += Days:30;
					Player_RemoveCash(playerid, 20000);

					Family_Save( id );

					SendClientMessage(playerid, -1, "Você renovou a família em +30 dias, por: {00FF00}20.000 {FFFFFF}de cash");

				    // LOGS
				    format(string, sizeof string, "[%s] %s renovou a família em +30 dias", familyInfo[id][familyName], PlayerName[playerid]);
				    server_log("family", string);
				}
			}
			else SendClientMessage(playerid, COLOR_LIGHTRED, " Você não escreveu ''TROCAS'' ou ''SEM-TROCAS'' e a renovação foi cancelada !");
		}
	    return true;
	}
	else if (dialogid == 33)
	{
	    if (!response || listitem == -1) return 1;

	    new idPlayer = List_GetPlayers(playerid, listitem);

		if (idPlayer != INVALID_PLAYER_ID) {
			MEGAString[0] = EOS;

			format(string, 128, "\n{ACABAB}	Nome:					{F1EFEF}%s\n", PlayerName[idPlayer]);
			strcat(MEGAString, string);

			format(string, 128, "{ACABAB}	Preso pela(o):				{F1EFEF}%s\n", GetNomeOrg(PlayerInfo[idPlayer][orgPrendeu]));
			strcat(MEGAString, string);

			format(string, 128, "{ACABAB}	Responsável pela prisão:		{F1EFEF}%s\n", PlayerInfo[idPlayer][pRespPrisao]);
			strcat(MEGAString, string);

			format(string, 128, "{ACABAB}	Motivo da prisão:			{F1EFEF}%s\n", PlayerInfo[idPlayer][pMotivoPrisao]);
			strcat(MEGAString, string);

			format(string, 128, "{ACABAB}	Data da prisão:				{F1EFEF}%s\n\n", PlayerInfo[idPlayer][pPrisaoData]);
			strcat(MEGAString, string);

			if (PlayerInfo[idPlayer][orgPrendeu] == 999)
			{
				strcat(MEGAString, "{FF0000}OBS: {F1EFEF}Abra um inquerito contra o administrador caso a prisão seja incorreta, link abaixo:\n");
				strcat(MEGAString, "Use o mesmo login da sua conta do servidor no painel: "SERVER_SITE"/complaints/create\n");
			}
			ShowPlayerDialog(playerid, 34, DIALOG_STYLE_MSGBOX, "{EC5C5C}Informações do presidiário", MEGAString, "Fechar", "Retornar");
		}
		return 1;
	}

	else if (dialogid == 34)
	{
	    if (!response) callcmd::presos(playerid);

		return 1;
	}

	else if (dialogid == 8472) {

		if(response) {

			if (GoChase[playerid] != INVALID_PLAYER_ID) {
     			return SendClientMessage(playerid, -1, "Você ja possui um contrato !");
			}

			new contratoid = List_GetPlayers(playerid, listitem);

			if(IsPlayerConnected(contratoid)) {

				if (GetPlayerOrg(playerid) == 8) {

					if (GotHit[contratoid]) {
						return SendClientMessage(playerid, COLOR_LIGHTRED, " Alguém da sua agência já pegou este contrato !");
					}
					if (PlayerInfo[contratoid][pHeadValue] == 0) {
						return SendClientMessage(playerid, COLOR_LIGHTRED, " O contrato nessa pessoa já foi cumprido !");
					}

					format(string, sizeof(string), "Agência | %s, pegou um contrato em: %s(%d), por $%s e %d respeitos.", PlayerName[playerid], PlayerName[contratoid], contratoid, getFormatText(PlayerInfo[contratoid][pHeadValue]), PlayerInfo[contratoid][pHeadRespectT]);
					SendMembersMessage(8, COLOR_YELLOW, string);
					server_log("contratos", string);
					GoChase[playerid] = contratoid;
					GetChased[contratoid] = playerid;
					GotHit[contratoid] = 1;

				} else {

					if (GotTri[contratoid]) {
						return SendClientMessage(playerid, COLOR_LIGHTRED, " Alguém da sua agência já pegou este contrato !");
					}
					if (PlayerInfo[contratoid][pHeadValueT] == 0) {
						return SendClientMessage(playerid, COLOR_LIGHTRED, " O contrato nessa pessoa já foi cumprido !");
					}

					format(string, sizeof(string), "Agência | %s, pegou um contrato em: %s(%d), por $%s e %d respeitos.", PlayerName[playerid], PlayerName[contratoid], contratoid, getFormatText(PlayerInfo[contratoid][pHeadValueT]), PlayerInfo[contratoid][pHeadRespectT]);
					SendMembersMessage(22, COLOR_YELLOW, string);
					server_log("contratos", string);
					GoChase[playerid] = contratoid;
					GetChased[contratoid] = playerid;
					GotTri[contratoid] = 1;
				}
			} else {
				SendClientMessage(playerid, -1, "Este contrato não está mais conectado !");
			}
		} else {
			SendClientMessage(playerid, -1, " Você fechou o menu de contratos !");
		}
		return 1;
	}

	else if (dialogid == 9784) {

		if(response) {

		    if(!strlen(inputtext)) {
				return ShowPlayerDialog(playerid, 9784, DIALOG_STYLE_PASSWORD, "Senha do portão", "Digite a senha deste portão:", "Abrir", "Cancelar");
		    }

		    if (!strcmp(inputtext, PortaoInfo[GetPVarInt(playerid, "varPortaoSenha")][portaoSenha], true)) {
		        SendClientMessage(playerid, TEAM_BALLAS_COLOR, " Senha correta! Você acaba de abrir o portão, ele fechará em 5 segundos !");
		        portaoAbrir(GetPVarInt(playerid, "varPortaoSenha"));
		    } else {
		        SendClientMessage(playerid, COLOR_LIGHTRED, " Senha incorreta !");
		    }
		} else {
		    SendClientMessage(playerid, -1, " Você decidiu não digitar a senha do portão !");
		}
		return 1;
	}

	else if(dialogid == 9274)
	{
	    if(response)
		{
			if(gettime() < GetPVarInt(playerid, #VarFlood15))
			    return SendClientMessage(playerid, COLOR_GRAD, #Você precisa esperar alguns segundos para mandar mensagem no chat novamente);

			if (Admin_GetNivel(playerid) || Helper_GetNivel(playerid))
			{
				SetPVarInt(playerid, #VarFlood15, gettime()+1);
			}
			else if(PlayerInfo[playerid][pConnectTime] >= 2000)
			{
				SetPVarInt(playerid, #VarFlood15, gettime()+50);
			}
			else if(PlayerInfo[playerid][pConnectTime] >= 400)
			{
				SetPVarInt(playerid, #VarFlood15, gettime()+80);
			}
			else
			{
				SetPVarInt(playerid, #VarFlood15, gettime()+100);
			}

	        GetPVarString(playerid, "varNoob", string, sizeof(string));
			
			SendMessageChat(CHAT_TYPE_NOOB, playerid, string);
	    }
	    return 1;
	}

	else if (dialogid == 36)
	{
	    if (response)
		{
     		if(PlayerInfo[playerid][pVIP] < 7 && !PlayerInfo[playerid][pAnuncioP]) return SendClientMessage(playerid, -1, "Você não tem permissão para usar anúncio personalizado.");

	        if (strlen(inputtext) < 20 || strlen(inputtext) > 93) return SendClientMessage(playerid, -1, "O anúncio deve estar entre 30 a 120 caracteres.");

            new payout = strlen(inputtext) * 22;

	        format(string, sizeof(string), "[ANÚNCIO]: %s{BEBEBE}, %s[%d] Celular: %d", inputtext, PlayerName[playerid], playerid, PlayerInfo[playerid][numeroCelular]);
			
			#if defined _CENSORED_protection
					censored_word_detected(string);
				#endif

      		SendClientMessageToAll(0xBEBEBEFF,string), server_log("anuncios", string);

            format(string, sizeof(string), "Você pagou $%s para anunciar, caracteres usados: %d.", getFormatText(payout), strlen(inputtext));
	    	SendClientMessage(playerid, -1, string);

	    	Player_RemoveMoney(playerid, payout);
			adicionarDinheiroGoverno(payout);

        	SetPVarInt(playerid, #VarFloodAnP, gettime() + 15);
	    }
	    return 1;
	}
	else if(dialogid == 5988)
	{
	    if(response)
	    {
	        callcmd::aceitar(playerid, "multa");
	    }
	    else
	    {
			format(string, sizeof(string), "* Você NÃO pagou a multa de $%d, e agora está sendo procurado!", TicketMoney[playerid]);
			SendClientMessage(playerid, COLOR_LIGHTRED, string);
			format(string, sizeof(string), "* %s NÃO pagou a multa de $%d e agora está sendo procurado!", PlayerName[playerid], TicketMoney[playerid]);
			SendClientMessage(TicketOffer[playerid], COLOR_LIGHTRED, string);
			TicketOffer[playerid] =  999;
			TicketMoney[playerid] = 0;
			SetPlayerCriminal(playerid, 255, "Recusou as multas");
	    }
	    return 1;
	}
	else if(dialogid == 5009)
	{
		if (!response) return true;

	    switch(listitem)
	    {
	        case 0:
	        {
                listRank(playerid, "nivel", "Níveis", "Rank: Nível");
			}
	        case 1:
	        {
	            listRank(playerid, "horasjogadas", "Horas", "Rank: Horas Jogadas");
	        }
	        case 2:
	        {
                listRank(playerid, "kills", "Kills", "Rank: Kills");
			}
	        case 3:
	        {
                listRank(playerid, "mortes", "Morreu", "Rank: Vezes que morreu");
			}
	        case 4:
	        {
                listRank(playerid, "banco", "Grana", "Rank: Dinheiro");
			}
	        case 5:
	        {
                listRank(playerid, "crimes", "Crimes", "Rank: Crimes Cometidos");
			}
	        case 6:
	        {
                listRank(playerid, "materiais", "Materiais", "Rank: Materiais");
			}
	        case 7:
	        {
                listRank(playerid, "maconha", "Gramas", "Rank: Maconha");
			}
	        case 8:
	        {
                listRank(playerid, "cocaina", "Carreirinhas", "Rank: Cocaina");
			}
	        case 9:
	        {
                listRank(playerid, "crack", "Pedras", "Rank: Crack");
			}
			case 10:
			{
			    listRank(playerid, "arenakills", "ArenaKills", "Rank: Arena Kills");
			}
			case 11:
	        {
                listRank(playerid, "contratos" , "Contratos" , "Rank: Contratos Cumpridos");
			}
			case 12:
	        {
                listRank(playerid, "apreensoes" , "Apreensoes" , "Rank: Apreensões Policial");
			}
	        case 13:
	        {
                showAtivos(playerid);
			}
			case 14:
	        {
                listRank(playerid, "cash", "Cash", "Rank: Cash");
			}
			case 15:
	        {
                listRank(playerid, "ouros", "Ouros", "Rank: Ouros");
			}
	        case 16:
	        {
                listRank(playerid, "pixador" , "Paredes" , "Rank: Maior Pichador");
			}
	        case 17:
	        {
                listRank(playerid, "atendimento" , "Atendimentos" , "Rank: Atendimento (Admins e Helpers)");
			}
	    }
	    return true;
	}

	else if (dialogid == 5008)
	{
	    return callcmd::rank(playerid);
	}

	else if(dialogid == 6602)
	{
	    if (!response) return true;

	    if (!PlayerToPoint(1.0, playerid,-26.8017,-89.5741,1003.5469) && !PlayerToPoint(1.0, playerid,1394.1488,-24.8331,1000.9177)) 
			return SendClientMessage(playerid, -1, "Você não está em uma 24/7.");

	    switch(listitem)
		{
  			case 0:
  			{
				if (PlayerInfo[playerid][numeroCelular] != 0) return SendClientMessage(playerid, -1, "Você já possui um celular, acabou o estoque de chips.");

			    buyPlayerItem(playerid, ITEM_BUY_CELULAR, 1500);
			}
			case 1:
			{
			    buyPlayerItem(playerid, ITEM_BUY_AGENDA, 50);
			}
			case 2:
			{
			    buyPlayerItem(playerid, 2, 30);
			}
			case 3:
			{
				buyPlayerItem(playerid, 3, 12);
			}
			case 4:
			{
				buyPlayerItem(playerid, 4, 50);
			}
			case 5:
			{
			    if(PlayerInfo[playerid][pCigarros] > 0) return SendClientMessage(playerid, -1, "Você já possui uma carteira de cigarro no bolso.");

			    buyPlayerItem(playerid, 5, 15);
			}
			case 6:
			{
			    if(PlayerInfo[playerid][pGalao]) return SendClientMessage(playerid, -1, "Você já possui um galão de gasolina.");

			    buyPlayerItem(playerid, 6, 60);
			}
			case 7:
			{
			    if(PlayerInfo[playerid][pIsqueiro]) return SendClientMessage(playerid, -1, "Você já possui um isqueiro.");

			    buyPlayerItem(playerid, 7, 10);
			}
			case 8:
			{
			    if(PlayerInfo[playerid][pPatins]) return SendClientMessage(playerid, -1, "Você já possui um patins.");

			    buyPlayerItem(playerid, 8, 80);
			}
			case 9:
			{
			    buyPlayerItem(playerid, 9, 700);
			}
			case 10:
			{
			    buyPlayerItem(playerid, 10, 180);
			}
			case 11:
			{
			    buyPlayerItem(playerid, 11, 180);
			}
			case 12:
			{
			    buyPlayerItem(playerid, 12, 180);
			}
			case 13:
			{
			    if (IsPlayerHaveItem(playerid, ITEM_TYPE_NOTEBOOK)) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você já tem um Notebook em seu inventário!");

			    buyPlayerItem(playerid, ITEM_BUY_NOTEBOOK, 3000);
			}
			case 14:
			{
			    if (IsPlayerHaveItem(playerid, ITEM_TYPE_CAPACETE))return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você já tem um Capacete em seu inventário!");

			    buyPlayerItem(playerid, ITEM_BUY_CAPACETE, 100);
			}
			case 15:
			{
			    buyPlayerItem(playerid, 15, 150);
			}
			case 16:
			{
			    buyPlayerItem(playerid, 16, 100);
			}
			case 17:
			{
			    buyPlayerItem(playerid, ITEM_BUY_COXAFRANGO, 20);
			}
			case 18:
			{
			    buyPlayerItem(playerid, ITEM_BUY_KITREPARO, 200);
			}
		}
		return true;
	}

	else if(dialogid == 5874)
	{
	    if(response)
	    {
			SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
			SetPlayerToTeamColor(playerid);

		    new dorg;
		    switch(listitem)
		    {
		    	case 1:dorg = 7;
		        case 2:dorg = 3;
		        case 3:dorg = 11;
		        case 4:dorg = 33;
		        case 5:dorg = 16;
		        case 6:dorg = 9;
		        case 7:dorg = 1;
		        case 8:dorg = 2;
		        case 9:dorg = 34;
		        case 11:dorg = 29;
		        case 12:dorg = 5;
		        case 13:dorg = 14;
		        case 14:dorg = 17;
		        case 15:dorg = 18;
		        case 16:dorg = 10;
		        case 17:dorg = 19;
		        case 18:dorg = 21;
		        case 20:dorg = 26;
		        case 21:dorg = 8;
		        case 22:dorg = 22;
		        case 24:dorg = 12;
		        case 25:dorg = 13;
		        case 27:dorg = 24;
		        case 28:dorg = 15;
		        case 29:dorg = 20;
		        case 31:dorg = 23;
		        case 32:dorg = 25;
		        case 33:dorg = 28;
          		case 34:dorg = 0;
		    }
			switch(dorg)
			{
				case 1: SetPlayerColor(playerid, 0x605DFFAA);
				case 2: SetPlayerColor(playerid, 0x737373AA);
				case 3: SetPlayerColor(playerid, 0x00660CAA);
				case 5: SetPlayerColor(playerid, 0x2641FEAA);
			    case 7: SetPlayerColor(playerid, 0x0095FFAA);
				case 8: SetPlayerColor(playerid, 0xBDBDBDAA);
				case 9: SetPlayerColor(playerid, 0xDFB77BAA);
				case 11: SetPlayerColor(playerid, 0x917662AA);
				case 12: SetPlayerColor(playerid, 0xD85300AA); // Nova Cor da Máfia Italiana (Vermelho)
				case 13: SetPlayerColor(playerid, 0x18C09FAA);
				case 14: SetPlayerColor(playerid, 0x177517AA);
				case 15: SetPlayerColor(playerid, 0x571E1EAA);
				case 16: SetPlayerColor(playerid, 0xFFFF44AA);
				case 17: SetPlayerColor(playerid, 0x99311EAA);
				case 18: SetPlayerColor(playerid, 0x010701AA);
				case 19: SetPlayerColor(playerid, 0xF80505AA);
				case 20: SetPlayerColor(playerid, 0xEE2323AA);
				case 21: SetPlayerColor(playerid, 0x7F994CAA);
				case 22: SetPlayerColor(playerid, 0xA4D1FFAA);
				case 23: SetPlayerColor(playerid, 0x024566AA);
			 	case 24: SetPlayerColor(playerid, 0x33FFFFAA);
				case 25: SetPlayerColor(playerid, 0x576176AA);
				case 26: SetPlayerColor(playerid, 0xFFFF99AA);
				case 28: SetPlayerColor(playerid, 0xA3283DAA);
				case 33: SetPlayerColor(playerid, 0x996600AA);
				case 34: SetPlayerColor(playerid, 0x333300AA);
				default:
				{
				    SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
				    return SetPlayerToTeamColor(playerid);
				}
			}

			format(string, sizeof string, "* Você se disfarçou de %s, tome cuidado para que não descubram você.", GetOrgName(dorg));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

			format(string, sizeof string, "(Agência de Assassinos) %s se disfarçou de %s.", PlayerName[playerid], GetOrgName(dorg));
			SendMembersMessage(GetPlayerOrg(playerid), COLOR_YELLOW, string);
		}
	}

    else if (dialogid == 4785)
    {
        if (!response) return false;

        if (FloorRequestedBy[listitem] != INVALID_PLAYER_ID || IsFloorInQueue(listitem))
            GameTextForPlayer(playerid, "~r~Este andar ja esta na fila", 3500, 4);
		else if (DidPlayerRequestElevator(playerid))
		    GameTextForPlayer(playerid, "~r~Voce ja chamou o elevador", 3500, 4);
		else
	        CallElevator(playerid, listitem);

		return 1;
    }

	// Sistema de advogados
	else if (dialogid == 4587)
	{
		if (!response || listitem == -1) 
			return SendClientMessage(playerid, -1, "Você fechou o menu de advogados.");

		new idPlayer = List_GetPlayers(playerid, listitem);

		if (idPlayer != INVALID_PLAYER_ID) {
			if (AdvogadoInfo[idPlayer][advogadoID] != INVALID_PLAYER_ID) return SendClientMessage(playerid, -1, "Esse prisioneiro recebeu uma oferta de outro advogado.");

			if (PlayerInfo[idPlayer][pAjustado]) return SendClientMessage(playerid, -1, "Esse prisioneiro já foi ajustado ou não pode ser ajustado.");

			ShowPlayerDialog(playerid, 4588, DIALOG_STYLE_TABLIST_HEADERS, "Menu do advogado",
			"Função\tPorcentagem\n\
			{9C9C9C}Reduzir pena\t{FFFFFF}5%\n\
			{9C9C9C}Reduzir pena\t{FFFFFF}10%\n\
			{9C9C9C}Reduzir pena\t{FFFFFF}15%\n\
			{9C9C9C}Reduzir pena\t{FFFFFF}20%\n\
			{9C9C9C}Reduzir pena\t{FFFFFF}25%\n\
			{9C9C9C}Reduzir pena\t{FFFFFF}30%\n\
			{9C9C9C}Reduzir pena\t{FFFFFF}35%\n\
			{9C9C9C}Reduzir pena\t{FFFFFF}40%\n\
			{9C9C9C}Reduzir pena\t{FFFFFF}45%\n\
			{9C9C9C}Reduzir pena\t{FFFFFF}50%\n", "Confirmar", "Cancelar");

			AdvogadoInfo[playerid][advogadoID] = idPlayer;
		}
	    return true;
	}
	else if(dialogid == 4588)
	{
	    new idPlayer = AdvogadoInfo[playerid][advogadoID];

		if (!response)
		{
		    AdvogadoInfo[idPlayer][advogadoID] 		= INVALID_PLAYER_ID;
		    AdvogadoInfo[playerid][porcentPrisao] 	= 0;

			return SendClientMessage(playerid, -1, "Você fechou o menu de advogados.");
		}

		switch(listitem)
		{
		    case 0:
			{
			    AdvogadoInfo[idPlayer][porcentPrisao] = 5;
   			}
		    case 1:
			{
			    if (PlayerInfo[playerid][pAdvogadoSkill] < 50)
				{
				    AdvogadoInfo[playerid][porcentPrisao] = 0; AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;
				    format(string, sizeof string, "* ADVOGADO: Para usar redução de pena de 10 por cento você precisa de mais %d pontos.", (50 - PlayerInfo[playerid][pAdvogadoSkill]));
					return SendClientMessage(playerid, 0x4072F0FF, string);
				}

			    AdvogadoInfo[idPlayer][porcentPrisao] = 10;
   			}
		    case 2:
			{
				if (PlayerInfo[playerid][pAdvogadoSkill] < 100)
				{
				    AdvogadoInfo[playerid][porcentPrisao] = 0; AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;
				    format(string, sizeof string, "* ADVOGADO: Para usar redução de pena de 15 por cento você precisa de mais %d pontos.", (100 - PlayerInfo[playerid][pAdvogadoSkill]));
					return SendClientMessage(playerid, 0x4072F0FF, string);
				}

			    AdvogadoInfo[idPlayer][porcentPrisao] = 15;
			}
		    case 3:
			{
				if (PlayerInfo[playerid][pAdvogadoSkill] < 200)
				{
				    AdvogadoInfo[playerid][porcentPrisao] = 0; AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;
				    format(string, sizeof string, "* ADVOGADO: Para usar redução de pena de 20 por cento você precisa de mais %d pontos.", (200 - PlayerInfo[playerid][pAdvogadoSkill]));
					return SendClientMessage(playerid, 0x4072F0FF, string);
				}

			    AdvogadoInfo[idPlayer][porcentPrisao] = 20;
			}
		    case 4:
   			{
				if (PlayerInfo[playerid][pAdvogadoSkill] < 350)
				{
				    AdvogadoInfo[playerid][porcentPrisao] = 0; AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;
				    format(string, sizeof string, "* ADVOGADO: Para usar redução de pena de 25 por cento você precisa de mais %d pontos.", (350 - PlayerInfo[playerid][pAdvogadoSkill]));
					return SendClientMessage(playerid, 0x4072F0FF, string);
				}

			    AdvogadoInfo[idPlayer][porcentPrisao] = 25;
			}
		    case 5:
			{
				if (PlayerInfo[playerid][pAdvogadoSkill] < 500)
				{
				    AdvogadoInfo[playerid][porcentPrisao] = 0; AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;
				    format(string, sizeof string, "* ADVOGADO: Para usar redução de pena de 30 por cento você precisa de mais %d pontos.", (500 - PlayerInfo[playerid][pAdvogadoSkill]));
					return SendClientMessage(playerid, 0x4072F0FF, string);
				}

			    AdvogadoInfo[idPlayer][porcentPrisao] = 30;
			}
		    case 6:
			{
				if (PlayerInfo[playerid][pAdvogadoSkill] < 750)
				{
				    AdvogadoInfo[playerid][porcentPrisao] = 0; AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;
				    format(string, sizeof string, "* ADVOGADO: Para usar redução de pena de 35 por cento você precisa de mais %d pontos.", (750 - PlayerInfo[playerid][pAdvogadoSkill]));
					return SendClientMessage(playerid, 0x4072F0FF, string);
				}

			    AdvogadoInfo[idPlayer][porcentPrisao] = 35;
			}
			case 7:
			{
				if (PlayerInfo[playerid][pAdvogadoSkill] < 1100)
				{
				    AdvogadoInfo[playerid][porcentPrisao] = 0; AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;
				    format(string, sizeof string, "* ADVOGADO: Para usar redu??ão de pena de 40 por cento você precisa de mais %d pontos.", (1100 - PlayerInfo[playerid][pAdvogadoSkill]));
					return SendClientMessage(playerid, 0x4072F0FF, string);
				}

			    AdvogadoInfo[idPlayer][porcentPrisao] = 40;
			}
			case 8:
			{
				if (PlayerInfo[playerid][pAdvogadoSkill] < 1500)
				{
				    AdvogadoInfo[playerid][porcentPrisao] = 0; AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;
				    format(string, sizeof string, "* ADVOGADO: Para usar redução de pena de 45 por cento você precisa de mais %d pontos.", (1500 - PlayerInfo[playerid][pAdvogadoSkill]));
					return SendClientMessage(playerid, 0x4072F0FF, string);
				}

			    AdvogadoInfo[idPlayer][porcentPrisao] = 45;
			}
			case 9:
			{
				if (PlayerInfo[playerid][pAdvogadoSkill] < 2000)
				{
				    AdvogadoInfo[playerid][porcentPrisao] = 0; AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;
				    format(string, sizeof string, "* ADVOGADO: Para usar redução de pena de 50 por cento você precisa de mais %d pontos.", (2000 - PlayerInfo[playerid][pAdvogadoSkill]));
					return SendClientMessage(playerid, 0x4072F0FF, string);
				}

			    AdvogadoInfo[idPlayer][porcentPrisao] = 50;
			}
		}

		MEGAString[0] = EOS;

		format(string, sizeof string, "{4072F0}Advogados » {DBDCE0}Defina o valor que vai cobrar do seu cliente %s.\n\n", PlayerName[AdvogadoInfo[playerid][advogadoID]]);
		strcat(MEGAString, string);

        format(string, sizeof string, "{FF6347}Observação: {DBDCE0}Você vai tirar {00BFFF}%d por cento {DBDCE0}da pena do jogador, digite um preço abaixo.\n\n", AdvogadoInfo[idPlayer][porcentPrisao]);
		strcat(MEGAString, string);

		ShowPlayerDialog(playerid, 4589, DIALOG_STYLE_INPUT, "{4072F0}Menu do advogado", MEGAString, "Cobrar", "Cancelar");

		return true;
	}

	else if (dialogid == 4589)
	{
	    if (!response) return true;

	    new idPlayer = AdvogadoInfo[playerid][advogadoID];

		if (!strval(inputtext) || strval(inputtext) < 500 || strval(inputtext) > 1000000)
		    return SendClientMessage(playerid, -1, "O valor deve estar entre $500 a $1.000.000");


		AdvogadoInfo[idPlayer][precoAdvogado] = strval(inputtext);
		AdvogadoInfo[idPlayer][advogadoID] = playerid;

		MEGAString[0] = EOS;

	   	format(string, sizeof string, "{4072F0}Advogado » {DBDCE0}%s está cobrando $%s para tirar %d%% da sua pena.\n\n", PlayerName[playerid], getFormatText(AdvogadoInfo[idPlayer][precoAdvogado]), AdvogadoInfo[idPlayer][porcentPrisao]);
		strcat(MEGAString, string);

		strcat(MEGAString, "{FF6347}Observação: {DBDCE0}Você precisa digitar 'CONFIRMAR' para aceitar a oferta do advogado.\n\n");

		ShowPlayerDialog(idPlayer, 4590, DIALOG_STYLE_INPUT, "{4072F0}Oferta do advogado", MEGAString, "Prosseguir", "Cancelar");

		format(string, sizeof string, "Você quer reduzir a pena de %s em %d por cento pelo valor de $%s", PlayerName[idPlayer], AdvogadoInfo[idPlayer][porcentPrisao], getFormatText(AdvogadoInfo[idPlayer][precoAdvogado]));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

		return true;
	}

	else if(dialogid == 4590)
	{
	    new idPlayer = AdvogadoInfo[playerid][advogadoID];

	    if (!IsPlayerConnected(idPlayer) || !PlayerIsAdvogado(idPlayer))
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Esse jogador não está mais conectado ou não é mais um advogado."), AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;

		if (PlayerInfo[playerid][pJailTime] < 1) return SendClientMessage(playerid, -1, "Você não está mais preso.");

		if (response)
		{
	        if (!strcmp(inputtext, "confirmar", true))
			{
                if (Player_GetMoney(playerid) < AdvogadoInfo[playerid][precoAdvogado])
		        {
		            format(string, sizeof string, "Você não pode pagar pela oferta de $%s feita pelo advogado.", getFormatText(AdvogadoInfo[playerid][precoAdvogado]));
					SendClientMessage(playerid, -1, string);

					format(string, sizeof string, "O prisioneiro %s não pode pagar o valor da oferta feita por você.", PlayerName[playerid]);
					SendClientMessage(idPlayer, -1, string);

					AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;

					return true;
		        }

		        format(string, sizeof string, "O advogado %s retirou %d% da sua pena por $%s.", PlayerName[idPlayer], AdvogadoInfo[playerid][porcentPrisao], getFormatText(AdvogadoInfo[playerid][precoAdvogado]));
				SendClientMessage(playerid, 0x4072F0FF, string);

				format(string, sizeof string, "Você retirou %d% da pena de %s por $%s.", AdvogadoInfo[playerid][porcentPrisao], PlayerName[playerid], getFormatText(AdvogadoInfo[playerid][precoAdvogado]));
				SendClientMessage(idPlayer, 0x4072F0FF, string);

				Player_RemoveMoney(playerid, AdvogadoInfo[playerid][precoAdvogado]);
				PlayerInfo[idPlayer][pSalario] += AdvogadoInfo[playerid][precoAdvogado];

				PlayerInfo[playerid][pAjustado] = true;

				new reduzirPrisao = (PlayerInfo[playerid][pJailTime]/100) * AdvogadoInfo[playerid][porcentPrisao];

				PlayerInfo[playerid][pJailTime] = (PlayerInfo[playerid][pJailTime] - reduzirPrisao);

				AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;

				CheckConquista(idPlayer, Conquista_Advogado);

				PlayerInfo[idPlayer][pAdvogadoSkill] ++;

				SendClientMessage(idPlayer, 0x4072F0FF, "Você recebeu +1 ponto de advogado. (Use /habilidades para ver seu nível)");
			}
	        else
			{
	            format(string, sizeof string, "Você recusou a oferta do advogado %s, para retirar %d% da pena por $%s.", PlayerName[idPlayer], AdvogadoInfo[playerid][porcentPrisao], getFormatText(AdvogadoInfo[playerid][precoAdvogado]));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

		        format(string, sizeof string, "%s recusou sua oferta de tirar %d% da pena dele por $%s.", PlayerName[playerid], AdvogadoInfo[playerid][porcentPrisao], getFormatText(AdvogadoInfo[playerid][precoAdvogado]));
				SendClientMessage(idPlayer, COLOR_LIGHTBLUE, string);

				AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;

				return SendClientMessage(playerid, COLOR_LIGHTRED, "Observação: Você precisa digitar 'CONFIRMAR' para aceitar o advogado.");
			}
		}
		else
		{
	   		format(string, sizeof string, "Você recusou a oferta do advogado %s, para retirar %d% da pena por $%s.", PlayerName[idPlayer], AdvogadoInfo[playerid][porcentPrisao], getFormatText(AdvogadoInfo[playerid][precoAdvogado]));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

			format(string, sizeof string, "%s recusou sua oferta de tirar %d% da pena dele por $%s.", PlayerName[playerid], AdvogadoInfo[playerid][porcentPrisao], getFormatText(AdvogadoInfo[playerid][precoAdvogado]));
			SendClientMessage(idPlayer, COLOR_LIGHTBLUE, string);

			AdvogadoInfo[playerid][advogadoID] = INVALID_PLAYER_ID;

			return SendClientMessage(playerid, COLOR_LIGHTRED, "Observação: Você precisa digitar 'CONFIRMAR' para aceitar o advogado.");
		}

	    return true;
	}

	else if (dialogid == 1991)
	{
        if (response == 0) return true;

		if (PlayerInfo[playerid][pCargo] < 4) return SendClientMessage(playerid, -1, "Você precisa ser cargo 4 ou maior para designar contratos.");

	 	new idPlayer = strval(inputtext);
	 	if(hitfound == 0)
   		{
		   	SendClientMessage(playerid, -1, "Não ha contratos na agência dos Hitmans, USE contratos em seu laptop primeiro!");
		   	return true;
		}
		if(IsPlayerConnected(idPlayer))
		{
		    if(GetPlayerOrg(idPlayer) != GetPlayerOrg(playerid))
		    {
		        SendClientMessage(playerid, -1, "Esse Jogador não é um Assassino da sua agência!");
				return true;
		   	}
		    if(GoChase[idPlayer] != INVALID_PLAYER_ID)
		    {
		      	SendClientMessage(playerid, -1, "Esse Assassino ja possui um contrato!");
				return true;
		  	}
		   	if(IsPlayerConnected(hitmanid))
		    {
		   		format(string, sizeof(string), "Agência | %s, deu um contrato para %s em: %s(%d), por $%s e %d respeitos.", PlayerName[playerid], PlayerName[idPlayer], PlayerName[hitmanid], hitmanid, PlayerInfo[hitmanid][pHeadValue]);
		   		SendMembersMessage(GetPlayerOrg(playerid), COLOR_YELLOW, string);
		   		GoChase[idPlayer] = hitmanid;
		   		GetChased[hitmanid] = idPlayer;
		   		GotHit[hitmanid] = 1;
		   		hitmanid = 999;
		   		hitfound = 0;
			    return true;
		   	}
		    else
		   	{
		       	SendClientMessage(playerid, -1, "O contrato saiu do servidor, USE contratos no seu laptop novamente!");
		     	return true;
		    }
		}
		else
		{
		   	SendClientMessage(playerid, -1, "Esse não e um Assassino ativo!");
		   	return true;
		}
	}

	else if(dialogid == 1992)
	{
        if(response == 0) return 1;
		if(PlayerInfo[playerid][pCargo] < 4)
		{
		  	SendClientMessage(playerid, -1, "Voce precisa de cargo 4+ para dar contrato!");
		  	return 1;
	 	}
	 	new idplayer = strval(inputtext);
		if(trifound == 0)
   		{
		   	SendClientMessage(playerid, -1, "Não ha contratos na agência dos Triad, USE contratos em seu laptop primeiro!");
		   	return true;
		}
		if(IsPlayerConnected(idplayer))
		{
		   	if(GoChase[idplayer] != INVALID_PLAYER_ID)
		    {
			 	SendClientMessage(playerid, -1, "Esse Assassino ja possui um contrato!");
				return true;
			}
		  	if(IsPlayerConnected(triid))
		    {
		   		format(string, sizeof(string), "Agência | %s, deu um contrato para %s em: %s(%d), por $%s e %d respeitos.", PlayerName[playerid], PlayerName[idplayer], PlayerName[triid], triid, PlayerInfo[triid][pHeadValueT]);
		   		SendMembersMessage(22, COLOR_YELLOW, string);
		  		GoChase[idplayer] = triid;
		   		GetChased[triid] = idplayer;
		   		GotTri[triid] = 1;
		   		triid = 999;
		   		trifound = 0;
		      	return true;
		   	}
		   	else
		    {
			    SendClientMessage(playerid, -1, "O contrato saiu do servidor, USE contratos no seu laptop novamente!");
			    return true;
		  	}
		}
		else
		{
		   	SendClientMessage(playerid, -1, "Esse não e um Assassino ativo!");
		   	return true;
		}
	}
    else if(dialogid == 1389)
	{
        if(response)
		{
            if(listitem == 0)
			{
                SetPlayerFightingStyle (playerid, FIGHT_STYLE_ELBOW);
                PlayerInfo[playerid][pLuta] = 1;
            }
            if(listitem == 1)
			{
                SetPlayerFightingStyle (playerid, FIGHT_STYLE_BOXING);
                PlayerInfo[playerid][pLuta] = 2;
            }
            if(listitem == 2)
			{
                SetPlayerFightingStyle (playerid, FIGHT_STYLE_GRABKICK);
                PlayerInfo[playerid][pLuta] = 3;
            }
            if(listitem == 3)
			{
                SetPlayerFightingStyle (playerid, FIGHT_STYLE_KNEEHEAD);
                PlayerInfo[playerid][pLuta] = 4;
            }
            if(listitem == 4)
			{
                SetPlayerFightingStyle (playerid, FIGHT_STYLE_KUNGFU);
                PlayerInfo[playerid][pLuta] = 5;
            }
            if(listitem == 5)
			{
                SetPlayerFightingStyle (playerid, FIGHT_STYLE_NORMAL);
                PlayerInfo[playerid][pLuta] = 6;
            }
        }
        return true;
	}

    else if(dialogid == 133)
	{
	    if (response == 0) 
			return true;

		switch(listitem)
        {
            case 0:
			{
  	    		SetPlayerMapMarker(playerid, 1370.7482,-1760.6443,13.6598, "Agência de Empregos");
			   	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Agência de Empregos{FFFFFF}, siga a marca vermelha no mapa!");
	     	}
            case 1:
			{
  	    		SetPlayerMapMarker(playerid, 2846.3477,976.9812,10.7500, "HQ Fabricante de Materiais");
			   	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Fabricante de Materiais{FFFFFF}, siga a marca vermelha no mapa!");
	      	}
	    	case 2:
			{
  	    		SetPlayerMapMarker(playerid, 1739.2667,-1583.4945,14.1584, "HQ de Advogados");
				SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ de Advogados{FFFFFF}, siga a marca vermelha no mapa!");
	    	}
	        case 3:
			{
  	   			SetPlayerMapMarker(playerid, 1375.9441, 1057.7214, 10.8203, "HQ de Caminhoneiros");
			   	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ de Caminhoneiros{FFFFFF}, siga a marca vermelha no mapa!");
	        }
	        case 4:
			{
  	    		SetPlayerMapMarker(playerid, 2198.5359,-2010.0414,13.5469, "HQ de Lixeiro");
			   	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ de Lixeiro{FFFFFF}, siga a marca vermelha no mapa!");
	        }
			case 5:
			{
  	    		SetPlayerMapMarker(playerid, 1564.1434,-2228.2656,13.5547, "HQ de Taxista");
			   	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ de Taxista{FFFFFF}, siga a marca vermelha no mapa!");
	        }
			case 6:
			{
  	    		SetPlayerMapMarker(playerid, 1183.9657, -1323.1019, 13.5755, "HQ de Médico");
			   	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ de Médico{FFFFFF}, siga a marca vermelha no mapa!");
	        }
			case 7:
			{
  	    		SetPlayerMapMarker(playerid, 1003.9560,-91.6045,22.4495, "HQ de Minerador");
			   	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ de Minerador{FFFFFF}, siga a marca vermelha no mapa!");
	        }
			case 8:
			{
  	    		SetPlayerMapMarker(playerid, 2142.0698,-1729.8184,13.5592, "HQ de Mecânico");
			   	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ de Mecânico{FFFFFF}, siga a marca vermelha no mapa!");
	        }
   		}
   		return true;
	}

	else if(dialogid == 2571)
	{
	    TogglePlayerControllable(playerid, true);
	    if(response == 0) { return true; }
        switch(listitem)
        {
            case 0:
			{
                ShowPlayerDialog(playerid, 7788, DIALOG_STYLE_MSGBOX, "Teste de habilitação","Custo do teste: $3.000\nClique em 'Iniciar' para começar", "Iniciar","Cancelar");
            }
            case 1:
			{
				ShowPlayerDialog(playerid, 4789, DIALOG_STYLE_MSGBOX, "Licença de Pilotagem","Custo do teste: $15.000\nClique em 'Iniciar' para começar", "Iniciar","Cancelar");
            }
            case 2:
			{
				ShowPlayerDialog(playerid, 4790, DIALOG_STYLE_MSGBOX, "Licença de Marujo","Custo do teste: $13.000\nClique em 'Iniciar' para começar", "Iniciar","Cancelar");
            }
            case 3:
			{
                if (Player_GetMoney(playerid) < 10000) return SendClientMessage(playerid,-1, "Você não tem "C_MONEY"$10.000");

                TogglePlayerControllable(playerid, true);

				Player_RemoveMoney(playerid, 10000);
                DepositPropertie(playerid, 5000), adicionarDinheiroGoverno(5000);

                PlayerInfo[playerid][pGunLic] = 1;
                SendClientMessage(playerid, COLOR_LIGHTBLUE,"Você adquiriu seu porte de armas.");
            }
        }
        return 1;
	}

	else if(dialogid == 2585)
	{
		if (!response) return true;
		switch(listitem)
    	{
	       	case 0:
		    {
		        SetPlayerInterior(playerid, 0);
	            SetPlayerPos(playerid, 1524.4977,-1677.9469,6.2188);
 			}
 			case 1:
	        {
	            SetPlayerInterior(playerid, 6);
		    	SetPlayerPos(playerid, 246.4990, 88.0087, 1003.6406);
 			}
 			case 2:
    		{
                SetPlayerInterior(playerid, 0);
	        	SetPlayerPos(playerid, 1565.1235,-1666.9944,28.3956);
 			}
		}
		return true;
	}

	else if(dialogid == 4507)
	{
	    new org = GetPlayerOrg(playerid);

	    if (!response) showDialogDefinicoes(playerid, org);

		if(response >= 1)
		{
			if(listitem == 0)
			{
				format(string,sizeof(string),"O Saldo da Sua Organização é de $%d", OrgInfo_GetMoney(org));
			    ShowPlayerDialog(playerid, 13, DIALOG_STYLE_MSGBOX, "Cofre da Organização", string, "Depositar","Sair");
			    return true;
			}
			if(listitem == 1)
			{
				switch (org) {
					case 1, 2, 3, 4, 7, 9, 10, 11, 16, 27, 30, 31, 32: return SendClientMessage(playerid, -1," Sua organização não trabalha com Materiais!");
				}

				format(string,sizeof(string),"Sua organização tem %sg de Materiais.", getFormatText(CofreOrg[org][Materiais]));
			    ShowPlayerDialog(playerid, 14, DIALOG_STYLE_MSGBOX, "Cofre da Organização", string, "Depositar","Sair");
			    return true;
			}
			if(listitem == 2)
			{
  				switch (org) {
					case 1, 2, 3, 4, 7, 9, 10, 11, 16, 27, 30, 31, 32: return SendClientMessage(playerid, -1," Sua organização não trabalha com maconha!");
				}

				format(string,sizeof(string),"A Sua Organização tem %d de Maconha\nO que você deseja fazer ?",CofreOrg[org][Maconha]);
			    ShowPlayerDialog(playerid, 15, DIALOG_STYLE_MSGBOX, "Cofre da Organização", string, "Sacar", "Depositar");
			    return true;
			}
			if(listitem == 3)
			{
  				switch (org) {
					case 1, 2, 3, 4, 7, 9, 10, 11, 16, 27, 30, 31, 32: return SendClientMessage(playerid, -1," Sua organização não trabalha com cocaina!");
				}
				format(string,sizeof(string),"A Sua Organização tem %d de Cocaina\nO que você deseja fazer ?",CofreOrg[org][Cocaina]);
			    ShowPlayerDialog(playerid, 16, DIALOG_STYLE_MSGBOX, "Cofre da Organização", string, "Sacar", "Depositar");
			    return true;
			}
			if(listitem == 4)
			{
  				switch (org) {
					case 1, 2, 3, 4, 7, 9, 10, 11, 16, 27, 30, 31, 32: return SendClientMessage(playerid, -1," Sua organização não trabalha com crack!");
				}
				format(string,sizeof(string),"A Sua Organização tem %d de Crack\nO que você deseja fazer ?",CofreOrg[org][Crack]);
			    ShowPlayerDialog(playerid, 17, DIALOG_STYLE_MSGBOX, "Cofre da Organização", string, "Sacar", "Depositar");
			    return true;
			}
		}
		return true;
	}

	else if(dialogid == 4902)
	{
	    if (!response) return true;

		switch(listitem)
		{
		    case 0: showGPSLocations(playerid);
		    case 1: {
				#if defined _INC_caixa_eletronico
					LocationCaixaEletronico(playerid);
				//#else
					//SHOW_MESSAGE_INATIVE_SYSTEM(playerid);
				#endif
			}
		    case 2: localTrashCan(playerid);
		    case 3:
		    {
	            MEGAString[0] = EOS;
	            format(string, 128, " Palácio do Planalto (HQ %s)\n", GetOrgName(7));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(1));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(2));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(3));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(5));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(8));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(9));
	    		strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(11));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(12));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(13));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(14));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(15));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(17));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(18));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(21));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(22));
				strcat(MEGAString,string);
	            format(string, 128, " HQ %s\n", GetOrgName(33));
				strcat(MEGAString,string);
	   			format(string, 128, " HQ %s\n", GetOrgName(16));
				strcat(MEGAString,string);
	   			format(string, 128, " HQ %s\n", GetOrgName(24));
				strcat(MEGAString,string);
	   			format(string, 128, " HQ %s\n", GetOrgName(25));
				strcat(MEGAString,string);
	   			format(string, 128, " HQ %s\n", GetOrgName(20));
				strcat(MEGAString,string);
	   			format(string, 128, " HQ %s\n", GetOrgName(28));
				strcat(MEGAString,string);
				format(string, 128, " HQ %s\n", GetOrgName(34));
				strcat(MEGAString,string);
				ShowPlayerDialog(playerid, 8971, DIALOG_STYLE_LIST, "GPS - HQs das Organizações", MEGAString, "Localizar","Voltar");
		    }
		    case 4:
			{
		        ShowPlayerDialog(playerid, 92, DIALOG_STYLE_TABLIST_HEADERS, "Concessionárias",
		        "Tipo\tNível necessário\n\
				Carros Antigos\t1\n\
				Carros Lowriders\t4\n\
				Carros Comuns\t5\n\
				Carros Raros\t8\n\
				Helicopteros\t15\n\
				Motos\t1\n\
				Bicicletas\t1\n\
				Barcos\t7\n\
				Aviões\t30",
				"Localizar", "Retornar");
		    }
		    case 5:
			{
		        ShowPlayerDialog(playerid, 133, DIALOG_STYLE_LIST, "Locais de empregos",
		        "Agência de Empregos\n\
		        Fabricante de Materiais\n\
				Emprego de Advogado\n\
				Emprego de Caminhoneiro\n\
				Emprego de Gari\n\
				Emprego de Taxista\n\
				Emprego de Médico\n\
				Emprego de Minerador\n\
				Emprego de Mecânico\n",
				"Localizar", "Voltar");
		    }
		    case 6:
			{
				ShowPlayerDialog(playerid, 1066, DIALOG_STYLE_LIST, "Localizar casas",
				"{FFFFFF}Localizar casa pelo ID\n\
				{FFFFFF}Localizar casas á venda (dinheiro)\n\
				{FFFFFF}Localizar casas á venda (cash)\n\
				{FFFFFF}Localizar casas para {FFA500}alugar\n",
				"Localizar", "Retornar");
		    }
		    case 7: {
       			ShowEmpresaList(playerid, 1);
		    }
			case 8: {
      			// Locais de tunagem
				ShowTransfendersLocal(playerid);
		    }
		    case 9: {
      			ShowEmpresaList(playerid, 3);
		    }
			case 10: {
				MEGAString[0] = EOS;
				for(new tr = 0; tr < MAX_TERRITORIOS; tr++) {
					if(trLS[tr][trCreated]) {
						FormatCat(MEGAString, "%s\n", trLS[tr][trName]);
					}
				}

				ShowPlayerDialog(playerid, 6588, DIALOG_STYLE_LIST, "Pontos de Tráfico", MEGAString, "Localizar", "Voltar");
			}
			case 11: {
				MEGAString = "{FFFFFF}Nome\tRegião\tSituação\n";
				for(new d = 0; d < MAX_DEALERS; d++) {
					FormatCat(MEGAString, "{FFFFFF}%s\t%s\t%s\n", DealerInfo[d][diName], DealerInfo[d][diAreaName], !DealerInfo[d][diArrested] ? ("{00FF00}Traficando") : ("{FF0000}Preso"));
				}

				ShowPlayerDialog(playerid, 6589, DIALOG_STYLE_TABLIST_HEADERS, "Traficantes", MEGAString, "Localizar", "Voltar");
			}
			case 12: {
				MEGAString[0] = EOS;
				strcat(MEGAString, "Cativeiro\tCidade\n");

				strcat(MEGAString, "{7D8084}Cativeiro I\t{FFFFFF}Las Venturas\n");
				strcat(MEGAString, "{7D8084}Cativeiro II\t{FFFFFF}Las Venturas\n");
				strcat(MEGAString, "{7D8084}Cativeiro III\t{FFFFFF}Las Venturas\n");

				ShowPlayerDialog(playerid, 8813, DIALOG_STYLE_TABLIST_HEADERS, "Cativeiros para sequestros", MEGAString, "Localizar", "Fechar");
			}
		}
		return true;
	}

	else if(dialogid == 6588)
    {
    	if(!response)
	    {
	    	return callcmd::gps(playerid);
      	}
       	else
        {
			if (trLS[listitem][trCreated]) {
				SetPlayerCheckpoint(playerid, trLS[listitem][trPointX], trLS[listitem][trPointY], trLS[listitem][trPointZ], 8.0);
				SendMsgF(playerid, COLOR_YELLOW, "[GPS]: %s foi marcado de vermelho no seu mapa", trLS[listitem][trName]);
			}
		}
       	return true;
   	}

	else if(dialogid == 6589)
    {
    	if(!response)
	    {
	    	return callcmd::gps(playerid);
      	}
       	else
        {
			SetPlayerCheckpoint(playerid, DealerInfo[listitem][diPosX], DealerInfo[listitem][diPosY], DealerInfo[listitem][diPosZ], 8.0);//
			SendMsgF(playerid, COLOR_YELLOW, "[GPS]: O traficante de %s foi marcado de vermelho no seu mapa", DealerInfo[listitem][diAreaName]);
		}
       	return true;
   	}

	else if (dialogid == 92) {

	    if (response) {

	        switch(listitem) {

	            case 0: {
  	    			SetPlayerCheckpoint(playerid, 2097.1567,1434.3655,10.8203, 10.0);
			    	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Concessionária de carros Antigos{FFFFFF}, siga a marca vermelha no mapa!");
	            }
	            case 1: {
  	    			SetPlayerCheckpoint(playerid, 2765.0276,-2009.2236,13.5620, 10.0);
			    	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Concessionária de carros Lowriders{FFFFFF}, siga a marca vermelha no mapa!");
	            }
	            case 2: {
  	    			SetPlayerCheckpoint(playerid, 560.3389,-1257.0521,17.2422, 10.0);
			    	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Concessionária de carros Comuns{FFFFFF}, siga a marca vermelha no mapa!");
	            }
	            case 3: {
  	    			SetPlayerCheckpoint(playerid, -1968.5513,296.1877,35.1719, 10.0);
			    	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Concessionária de carros Raros{FFFFFF}, siga a marca vermelha no mapa!");
	            }
	            case 4: {
  	    			SetPlayerCheckpoint(playerid, 1935.9233,-2649.9656,13.5469, 10.0);
			    	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Concessionária de Helicopteros{FFFFFF}, siga a marca vermelha no mapa!");
	            }
	            case 5: {
  	    			SetPlayerCheckpoint(playerid, 2047.0797,-1907.9780,13.5469, 10.0);
			    	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Concessionária de Motocicletas{FFFFFF}, siga a marca vermelha no mapa!");
	            }
	            case 6: {
  	    			SetPlayerCheckpoint(playerid, 2283.3213,-2019.5406,13.5414, 10.0);
			    	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Concessionária de Bicicletas{FFFFFF}, siga a marca vermelha no mapa!");
	            }
	            case 7: {
  	    			SetPlayerCheckpoint(playerid, 951.7903,-1937.9349,-0.6073, 10.0);
			    	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Concessionária de Barcos{FFFFFF}, siga a marca vermelha no mapa!");
	            }
	            case 8: {
  	    			SetPlayerCheckpoint(playerid, 1924.3663,-2292.1001,13.5469, 10.0);
			    	SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Concessionária de Aviões{FFFFFF}, siga a marca vermelha no mapa!");
	            }
	        }
	    } else {
	        callcmd::gps(playerid);
	    }
	    return 1;
	}

	else if(dialogid == 3578){

	    if(!response)return callcmd::gps(playerid);

	    SetPlayerCP(playerid, CP_NULL);
	    switch(listitem){

	        case 0:{

	    		SetPlayerCheckpoint(playerid, 810.4855, -1616.1888, 13.5469, 10.0);
			    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Burger Shot{FFFFFF}, siga a marca vermelha no mapa!");
	        }
	        case 1:{

	    		SetPlayerCheckpoint(playerid, 927.6217, -1353.0105, 13.3438, 10.0);
			    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Cluckin Bell{FFFFFF}, siga a marca vermelha no mapa!");
	        }
	        case 2:{

	    		SetPlayerCheckpoint(playerid, 2105.4858, -1806.4725,13.5547, 10.0);
			    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Well Stacked Pizza{FFFFFF}, siga a marca vermelha no mapa!");
	        }
	    }
	    return 1;
	}
	else if(dialogid == 8813)
	{
	    if(response)
	    {
	        switch(listitem)
	        {
	            case 0:
				{
				    SetPlayerCheckpoint(playerid, 2919.8228,2117.9873,17.8955, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Cativeiro I{FFFFFF}, siga a marca vermelha no mapa!");
				}
	            case 1:
				{
				    SetPlayerCheckpoint(playerid, 2811.0066,2919.7876,36.5046, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Cativeiro II{FFFFFF}, siga a marca vermelha no mapa!");
				}
	            case 2:
				{
				    SetPlayerCheckpoint(playerid, 2007.0468,2910.1699,47.8231, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Cativeiro III{FFFFFF}, siga a marca vermelha no mapa!");
				}
	        }
	    }
	    return 1;
	}

	else if (dialogid == 8814)
	{
	    if(response)
	    {
	        if (!IsPlayerConnected(List_GetPlayers(playerid, listitem))) return SendClientMessage(playerid, -1, "O jogador não está mais conectado no servidor.");

	        switch(GetPlayerVirtualWorld(List_GetPlayers(playerid, listitem)))
	        {
	            case 1001:
				{
				    SetPlayerCheckpoint(playerid, 2919.8228,2117.9873,17.8955, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Cativeiro I{FFFFFF}, siga a marca vermelha no mapa!");
				}
	            case 1002:
				{
				    SetPlayerCheckpoint(playerid, 2811.0066,2919.7876,36.5046, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Cativeiro II{FFFFFF}, siga a marca vermelha no mapa!");
				}
	            case 1003:
				{
				    SetPlayerCheckpoint(playerid, 2007.0468,2910.1699,47.8231, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Cativeiro III{FFFFFF}, siga a marca vermelha no mapa!");
				}
				default: SendClientMessage(playerid, -1, "O jogador ainda está dentro de um veículo, ainda não está em um cativeiro!");
	        }
	    }
	    return 1;
	}

	else if(dialogid == 8815)
	{
	    if(response && listitem >= 0)
	    {
			if (List_GetPlayers(playerid, listitem) != INVALID_PLAYER_ID) {
				new Float:x, Float:y, Float:z;
				GetVehiclePos(List_GetPlayers(playerid, listitem), x, y, z);

				new MapZone:zone = GetMapZoneAtPoint2D(x, y);
				new zone_name[MAX_MAP_ZONE_NAME];
				GetMapZoneName(zone, zone_name);

				new vehicle_name[30];
				GetModelStaticNameFromId(GetVehicleModel(List_GetPlayers(playerid, listitem)), vehicle_name);

				format(string, sizeof string, "Você localizou o veículo {00FFFF}%s {FFFFFF}que está em {FFFF00}%s, {FFFFFF}siga a marca vermelha!", vehicle_name, zone_name);
				SendClientMessage(playerid, -1, string);

				SetPlayerCheckpoint(playerid, x, y, z, 1.0);
				SetPlayerCP(playerid, CP_NULL);
			}

	    } else {
	        SendClientMessage(playerid, -1, "Você fechou a lista de veículos da sua organização");
     	}
	    return 1;
	}
	else if(dialogid == 4600)
	{
	    if(!response)return SendClientMessage(playerid, -1, "Você não quis ir ao local que marcou no mapa.");
		if(Admin_GetNivel(playerid))
		{
			if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				new vehicleID = GetPlayerVehicleID(playerid);
				SetVehiclePos(vehicleID, GetPVarFloat(playerid, "FindX"), GetPVarFloat(playerid, "FindY"), GetPVarFloat(playerid, "FindZ"));
			}
			else {
		    	SetPlayerPos(playerid, GetPVarFloat(playerid, "FindX"), GetPVarFloat(playerid, "FindY"), GetPVarFloat(playerid, "FindZ"));
			}
			SendClientMessage(playerid, COLOR_GRAD, " Você foi ao local que marcou no mapa.");
		}
		return true;
	}
	return 0;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new
		string[128]
	;

	// Mirando de sniper
	new
		Float: HP,
		Float: AP;
		// -------
		// true:
	if (HOLDING(KEY_HANDBRAKE) && GetPlayerWeapon(playerid) == WEAPON_SNIPER)
	{
		if (!GetPVarInt(playerid, "acessories_removed")) {
			RemovePlayerAcessoriesTemp(playerid);
		}
		PlayerTextDrawHide(playerid, SniperShot[playerid]);

		new targetid = GetPlayerTargetPlayer(playerid);
		if (targetid != INVALID_PLAYER_ID) // GetPlayerState(playerid) != PLAYER_STATE_SPECTATING
		{
			new orgid = GetPlayerOrg(targetid);
			MEGAString[0] = EOS;

			GetPlayerHealth(targetid, HP);
			GetPlayerArmour(targetid, AP);
			format(MEGAString, 256, "~r~~h~%s~n~~n~\
								~p~Vida: ~w~%0.1f~n~\
								~p~Colete: ~w~%0.1f~n~\
								~p~Distancia: ~w~%dm~n~\
								~p~Ping: ~w~%d~n~\
								~p~Org: ~w~%s",
								PlayerName[targetid], HP, AP, floatround(GetDistanceForPlayer(targetid, playerid)), GetPlayerPing(targetid), GetOrgName(orgid));
			PlayerTextDrawSetString(playerid, SniperShot[playerid], MEGAString);
			PlayerTextDrawShow(playerid, SniperShot[playerid]);

			if (gPlayerInGuerra(playerid) && !GetPVarInt(playerid, "varDead") && GetPlayerInterior(playerid) == 0 && !Staff_GetWorking(playerid)) {
				for(new textGMorro; textGMorro != sizeof guerraMorroTextDraw; textGMorro++) {
					TextDrawHideForPlayer(playerid, guerraMorroTextDraw[textGMorro]);
				}
			}

			SetPVarInt(playerid, "AimingWithSniper", 1);
		}
	}
		// -------
		// false:
	else if (!HOLDING(KEY_HANDBRAKE))
	{
		if (GetPVarInt(playerid, "acessories_removed")) {
			SetPVarInt(playerid, "acessories_removed", 0);
			Player_SetAccessories(playerid);
		}
		if (IsValidDynamicPlayerTextDraw(playerid, SniperShot[playerid]))
			PlayerTextDrawHide(playerid, SniperShot[playerid]);

		if (gPlayerInGuerra(playerid) && !GetPVarInt(playerid, "varDead") && GetPlayerInterior(playerid) == 0 && !Staff_GetWorking(playerid)) {
			for(new textGMorro; textGMorro != sizeof guerraMorroTextDraw; textGMorro++) {
				TextDrawShowForPlayer(playerid, guerraMorroTextDraw[textGMorro]);
			}
		}

		SetPVarInt(playerid, "AimingWithSniper", 0);
	}

	if (newkeys & KEY_SECONDARY_ATTACK)
	{
		if (!IsPlayerInAnyVehicle(playerid))
		{
	 		if(PlayerToPoint(1.0,playerid,247.8818,71.5204,1003.6406) || PlayerToPoint(1.0,playerid,245.3463, 73.8183, 1003.6406))
			{
	            ApplyAnimation(playerid, "HEIST9","Use_SwipeCard", 4.0, false, false, false, false, 0);
	            callcmd::pp(playerid);
			}
			else if(PlayerToPoint(1.0,playerid,249.0358, 74.6236, 1003.6406) || PlayerToPoint(1.0,playerid,247.4305,77.2490,1003.6406))
			{
	      		ApplyAnimation(playerid, "HEIST9","Use_SwipeCard", 4.0, false, false, false, false, 0);
	            callcmd::pv(playerid);
			}
			else if(PlayerToPoint(1.0,playerid,249.9555,64.5031,1003.6406) || PlayerToPoint(1.0,playerid,251.3744,64.5719,1003.6406))
			{
	      		ApplyAnimation(playerid, "HEIST9","Use_SwipeCard", 4.0, false, false, false, false, 0);
	            callcmd::pr(playerid);
			}

	        pickupItem(playerid);

			callcmd::equipar(playerid, #);

			if (GetPVarInt(playerid, "playerInTrashCan"))
			{
				SetPlayerLixeira(playerid);
			}

			for(new x; x != MAX_SOUNDS; x++)
			{
			    if (SomInfo[x][somCreated] && IsPlayerInRangeOfPoint(playerid, 1.8, SomInfo[x][somX], SomInfo[x][somY], SomInfo[x][somZ]) && SomInfo[x][somID] == playerid)
				{
			        destroyPlayerSound(playerid);
			        GetPVarString(playerid, "nameRadioPortatil", string, 20);

					format(string, sizeof(string), "* %s desligou sua %s.", PlayerName[playerid], string);
					SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	    			PlayerInfo[playerid][segurandoRadio] = true;

	    			SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, GetPVarInt(playerid, "modelidRadio"), 5, 0.394999, 0.045000, 0.027000, -25.299999, -101.699974, 0.000000);

					ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle", 4.1, false, true, true, false, 0);

					break;
				}
			}
		}
	}
	else if (newkeys & KEY_YES)
	{
		if (GetPVarInt(playerid, "playerInTrashCan"))
		{
			if(IsAndroidPlayer(playerid))
			{
				UpdateAngleLixeira(playerid);
			}
		}

		Bank_OpenVault(playerid);

		new actorid = GetPlayerTargetActor( playerid ) ;
		new weaponid = GetPlayerWeapon(playerid);

		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetPVarInt(playerid, "Abordado") == 0) {
	    	callcmd::motor(playerid);
		}
		else
		{
			if (actorid != INVALID_ACTOR_ID && actorid < sizeof (g_Actors) && ProxDetectorActor(7.0, playerid, actorid) && weaponid >= 22 && weaponid <= 38) 
			{
				if (GetPVarInt(playerid, "assaltando") == actorid) {

					new rdon = random(14);
					if ( rdon == 1 || rdon == 3 || rdon == 5 || rdon == 7) {

						// Fail
						HidePlayerProgressBar(playerid, BarSprayTag[playerid]);

						KillTimer(GetPVarInt(playerid, "timerassalto"));

						SendClientMessage(playerid, COLOR_LIGHTRED, "* Você assustou o cidadão e ele DESMAIOU. Saia do local, pois a polícia já foi informada!");

						ApplyActorAnimation(actorid,"CRACK","crckdeth3", 4.1, false, true, true, true, 0);

						for(new x; x != 4; x++) {
							PlayerTextDrawHide(playerid, textAbordagem[x][playerid]);
						}

						ActorInfo[actorid][assaltotempo] = gettime() + (5 * 60);
						SetPVarInt(playerid, "assaltando", INVALID_ACTOR_ID);
						// Restaurar
						if ( ActorInfo[actorid][actTimer] != -1) {
							KillTimer(ActorInfo[actorid][actTimer]);
						}
						ActorInfo[actorid][actTimer] = SetTimerEx("acalmarActor", 55000, false, "d", actorid);
						return 1;
					}

					if ( gettime() < GetPVarInt(playerid, "apressando")) {
						return 1;
					}
					SetPVarInt(playerid, "apressando", gettime() + 5);

					SendClientMessage(playerid, -1, "Você apressou o cidadão, cuidado pois ele pode {FF0000}DESMAIAR{FFFFFF}!");

					SetPVarFloat(playerid, "percent", GetPVarFloat(playerid, "percent") + 5.0);

					ApplyActorAnimation(actorid, "SHOP","SHP_Rob_React",4.1, false, true, true, true, 0);

					return 1;
				}

				if ( !IsAMember( playerid ) ) {
					return SendClientMessage(playerid, -1, "Você não pode assaltar este cidadão!");
				}
				if ( ActorInfo[actorid][actmorto]) {
					return SendClientMessage(playerid, -1, "Essa pessoa está morta!");
				}
				if ( gettime() < ActorInfo[actorid][assaltotempo] ) {
					return SendClientMessage(playerid, -1, "Este cidadão já foi assaltado a poucos minutos!");
				}
				if ( gettime() < GetPVarInt(playerid, "assaltou") ) {
					return SendClientMessage(playerid, -1, "Aguarde 2 minutos para assaltar outro cidadão!");
				}

				SetPVarInt(playerid, "mirandoActor", 0);
				PlayerTextDrawSetString(playerid, textAbordagem[3][playerid], "OPCOES:~n~Y = Apressa-lo");

				SetPVarInt(playerid, "timerassalto", SetTimerEx("assaltoActor", 450, false, "dd", playerid, actorid));
				SetPlayerProgressBarValue(playerid, BarSprayTag[playerid], 0.0);
				ShowPlayerProgressBar(playerid, BarSprayTag[playerid] );
				SetPVarFloat(playerid, "percent", 0.0);
				SetPVarInt(playerid, "assaltando", actorid);
				SetPlayerCriminal(playerid, 255, "Assalto a mão armada, Art. 157º");
				SendClientMessage(playerid, COLOR_LIGHTRED, "* Você está assaltando este(a) cidadão. Continue com a arma apontada pra ele!");

				if ( ActorInfo[actorid][actTimer] != -1) {
					KillTimer(ActorInfo[actorid][actTimer]);
				}
				ActorInfo[actorid][actTimer] = SetTimerEx("acalmarActor", 55000, false, "d", actorid);

				return 1;
			}

			if (TrashCan_Get(playerid) != -1)
				TrashCan_ShowDialog(playerid);

			if (GetPVarInt(playerid, "Abordado"))
			{
				KillTimer(GetPVarInt(playerid, "TimerAbordagem"));
				Abordagem(playerid, 1);
				return 1;
			}
			if (GetPVarInt(playerid, "Abordou")) {

				new idplayer = GetPVarInt(playerid, "Abordando");
				if(GetPVarInt(idplayer, "EmAbordagem")) {
					ShowPlayerMessage(idplayer, "Voce foi liberado da abordagem pelo oficial", 5000);
					ShowPlayerMessage(playerid, "Voce liberou o cidadao da abordagem policial", 5000);

					format(string, sizeof(string), "* O oficial %s liberou %s da abordagem.", PlayerName[playerid], PlayerName[idplayer]);
					SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

					ClearAnimations(idplayer);
					TogglePlayerControllable(idplayer, true);
					SetPlayerSpecialAction(idplayer, SPECIAL_ACTION_NONE);
					SetPVarInt(idplayer, "EmAbordagem", 0);

					for(new x; x != 4; x++) {
						PlayerTextDrawHide(playerid, textAbordagem[x][playerid]);
					}
					SetPVarInt(playerid, "Abordou", 0);
				}
				return 1;
			}

			callcmd::enterexit(playerid, #);
		}
	}
	else if (newkeys & KEY_NO) {

		new actorid = GetPlayerTargetActor( playerid ) ;
		new weaponid = GetPlayerWeapon(playerid);

		if ( actorid != INVALID_ACTOR_ID && ProxDetectorActor(7.0, playerid, actorid) && weaponid >= 22 && weaponid <= 38) {

			if ( ActorInfo[actorid][actmorto]) {
			    return SendClientMessage(playerid, -1, "Essa pessoa está morta!");
			}

			for(new x; x != 4; x++) {
				PlayerTextDrawHide(playerid, textAbordagem[x][playerid]);
		  	}
		  	SetPVarInt(playerid, "mirandoActor", 0);

			ApplyActorAnimation(actorid, "PED", "DUCK_cower",4.1, true, false, false, false, 0);

			if ( ActorInfo[actorid][actTimer] != -1) {
			    KillTimer(ActorInfo[actorid][actTimer]);
			}
			ActorInfo[actorid][actTimer] = SetTimerEx("acalmarActor", 45000, false, "d", actorid);
			return 1;
		}
	    if (GetPVarInt(playerid, "Abordado")) {
			KillTimer(GetPVarInt(playerid, "TimerAbordagem"));
			Abordagem(playerid, 0);
   			return 1;
		}
	 	if (GetPVarInt(playerid, "Abordou")) {

            new idplayer = GetPVarInt(playerid, "Abordando");
			SendClientMessage(idplayer, COLOR_LIGHTBLUE, "* Você recebeu uma voz de prisão !");
            SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você deu uma voz de prisão !");

			format(string, sizeof(string), "%s diz: %s, você está preso!", PlayerName[playerid], PlayerName[idplayer]);
			SendClientMessageInRange(30.0, playerid, string, -1,-1,-1,-1,-1);
			format(string, sizeof(string), "%s diz: Você tem o direito de permanecer calado, e tudo que disser poderá e deverá ser usado", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, -1,-1,-1,-1,-1);
			format(string, sizeof(string), "%s diz: contra você no tribunal. Você tem o direito a um advogado. Você entendeu seus direitos?", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, -1,-1,-1,-1,-1);

			for(new x; x != 4; x++) {
				PlayerTextDrawHide(playerid, textAbordagem[x][playerid]);
			}

            ClearAnimations(idplayer);
            TogglePlayerControllable(idplayer, true);

			Player_SetHandcuffed(idplayer, true);

			VozDePrisao[idplayer] = 1;

			SetPVarInt(playerid, "Abordou", 0);
			return 1;
		}
	    if (!Inventory_IsOpen(playerid))
	        callcmd::inventario(playerid);
	}
	else if(newkeys & KEY_JUMP)
	{
	    timejump[playerid] = GetTickCount()+450;

		if (IsPlayerCuffed(playerid)) {

			ApplyAnimation(playerid, "GYMNASIUM", "gym_jog_falloff", 4.1, false, true, true, false, 0);
	    }
	}
	else if (newkeys & KEY_SPRINT && IsPCPlayer(playerid))
	{
		if (GetPVarInt(playerid, "playerInTrashCan"))
		{
			UpdateAngleLixeira(playerid);
		}
	}
	else if(newkeys & KEY_HANDBRAKE)
	{
		if (SkateInfo[playerid][s_Setado])
		{
			if (!SkateInfo[playerid][s_Andando])
			{
				SetPlayerSkate(playerid);
			}
			else
			{
				SetPlayerArmedWeapon(playerid, WEAPON_FIST);

				UpdatePlayerSkate(playerid, 128);
			}
		}
	}
	else if (newkeys & KEY_ANALOG_LEFT)
	{
	    if (!IsPlayerInAnyVehicle(playerid))
	    {
	        callcmd::trancar(playerid);
     	}
	}
	else if (newkeys & KEY_CROUCH)
	{
	    if(IsPlayerInAnyVehicle(playerid))
		{
		    if(IsACop(playerid) || GetPlayerOrg(playerid) == 7)
			{
				callcmd::pe(playerid);
	  			callcmd::pexe(playerid);
	  			callcmd::ppc1(playerid);
	  			callcmd::ppc2(playerid);
	  			//callcmd::ppf(playerid);
	  			callcmd::pbope(playerid);
	  			callcmd::prota(playerid);
				callcmd::prota2(playerid);
	   		}
	   		else if(GetPlayerOrg(playerid) == 13)
	   		{
	   		    callcmd::pyakuza1(playerid);
	   		    callcmd::pyakuza2(playerid);
	   		    callcmd::pyakuza3(playerid);
	   		}
	   		else if(GetPlayerOrg(playerid) == 24)
	   		{
	   		    callcmd::pcn(playerid);
	   		}
	   		else if(GetPlayerOrg(playerid) == 16)
	   		{
	   		    callcmd::pdetran(playerid);
	   		}
	   		else if(GetPlayerOrg(playerid) == 28)
	   		{
	   		    callcmd::pwar(playerid);
	   		}
	        else if(GetPlayerOrg(playerid) == 9)
			{
				callcmd::preporter(playerid);
				callcmd::preporter2(playerid);
			}
			else if(GetPlayerOrg(playerid) == 12)
	   		{
	   		    callcmd::pitaliana(playerid);
	   		}
			callcmd::portao(playerid, "abrir");
		}
	}
	if ((IsAndroidPlayer(playerid) && newkeys & KEY_YES) || (IsPCPlayer(playerid) && PRESSED(KEY_YES)))
	{
	    new id = GetPlayerGunBox(playerid);
	    if (id != -1)
		{
			if (GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK)
			    return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você precisa estar agachado para equipar na caixa de equipamentos !");

            SetPlayerFaceToPoint(playerid, gunInfo[id][gunX], gunInfo[id][gunY]);
            ApplyAnimation(playerid,"BOMBER","BOM_Plant_Loop", 4.1, true, false, false, false, 0);
			SetPlayerProgressBarValue(playerid, BarSprayTag[playerid], 0.0);
            ShowPlayerProgressBar(playerid, BarSprayTag[playerid]);
	        KillTimer(GetPVarInt(playerid, "timerEquip"));
	        SetPVarInt(playerid, "timerEquip", SetTimerEx("equipGunBox", 75, false, "iif", playerid, id, 0.0));
	 	}
	}
	else if(IsPCPlayer(playerid) && RELEASED(KEY_YES))
	{
	    if (GetPVarInt(playerid, "timerEquip") != -1)
		{
	        HidePlayerProgressBar(playerid, BarSprayTag[playerid]);

	    	KillTimer(GetPVarInt(playerid, "timerEquip"));
	    	ClearAnimations(playerid);
		}
	   	SetPVarInt(playerid, "timerEquip", -1);
	}
	return 1;
}

hook OU_VehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	new modelid = GetVehicleModel(vehicleid);

	if (modelid == 510 || modelid == 481 || modelid == 509) return true;

	new Float:veh_x, Float:veh_y, Float:veh_z, Float:veh_a;

	GetVehiclePos(vehicleid, veh_x, veh_y, veh_z);
	GetVehicleZAngle(vehicleid, veh_a);

	new Float:distance = VectorSize(veh_x - new_x, veh_y - new_y, veh_z - new_z);

	if (distance > 30.0 && new_z > -65.0)
	{
	    SetVehiclePos(vehicleid, veh_x, veh_y, veh_z);
	    SetVehicleZAngle(vehicleid, veh_a);
	    return false;
	}
	return true;
}

hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(Admin_GetNivel(playerid) >= MASTER)
	{
		MapAndreas_FindZ_For2DCoord(fX, fY, fZ);
	    SetPVarFloat(playerid, "FindX", fX);
	    SetPVarFloat(playerid, "FindY", fY);
	    SetPVarFloat(playerid, "FindZ", fZ+3.0);
		ShowPlayerDialog(playerid, 4600, DIALOG_STYLE_MSGBOX, "Teleporte Mapa", "Você deseja ir ao local que você marcou no mapa?", #Sim, #Não);
	}

	if(GetPVarInt(playerid, "mapaMarcar")) {
		new player = GetPVarInt(playerid, "mapaPlayer");
		MapAndreas_FindZ_For2DCoord(fX, fY, fZ);
		SetPlayerCheckpoint(player, fX, fY, fZ, 10.0);

		new MapZone:zone = GetMapZoneAtPoint2D(fX, fY);
		new zone_name[MAX_MAP_ZONE_NAME];
		GetMapZoneName(zone, zone_name);

		SetPVarInt(playerid, "mapaMarcar", 0);
		SendMsgF(playerid, COLOR_LIGHTBLUE, "Você marcou a região de %s para o jogador %s.", zone_name, PlayerName[player]);
	}
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	for (new cp; cp != sizeof (CPsLanchonetes); cp++)
	{
	    if (checkpointid == CPsLanchonetes[cp])
		{
	        ShowPlayerDialog(playerid, 101, DIALOG_STYLE_TABLIST_HEADERS, "Comprar alimento",
			"Item\tSaúde\tFome\tCusto\n\
			Pizza Congelada\t{00FFFF}+40\t{00FFFF}-30\t"C_MONEY"$20\n\
			Coca-Cola\t{00FFFF}+40\t{00FFFF}-8\t"C_MONEY"$11\n\
			Hambúrger\t{00FFFF}+20\t{00FFFF}-20\t"C_MONEY"$15\n\
			5 Pizza Congelada\t{00FFFF}+40\t{00FFFF}-30\t"C_MONEY"$80\n\
			5 Coca-Cola\t{00FFFF}+40\t{00FFFF}-8\t"C_MONEY"$50\n\
			5 Hambúrger\t{00FFFF}+20\t{00FFFF}-20\t"C_MONEY"$65\n", "Comprar", "Fechar");
	    }
	}
	for (new cp; cp != sizeof (CPsBar); cp++)
	{
	    if (checkpointid == CPsBar[cp])
		{
	        ShowPlayerDialog(playerid, 102, DIALOG_STYLE_TABLIST_HEADERS, "Itens do bar",
			"item\tdescricao\tcusto\n\
			Cachaça Tval\t"C_CYAN"+35 sede\t"C_MONEY"$250\n\
			Cachaça Gorbach\t"C_CYAN"+35 sede\t"C_MONEY"$250\n\
			Vinho Tinto\t"C_CYAN"+35 sede\t"C_MONEY"$250\n\
			Big Cook\t"C_CYAN"+35 sede\t"C_MONEY"$250\n\
			Champagne\t"C_CYAN"+35 sede\t"C_MONEY"$250\n", "Comprar", "Fechar");
	    }
	}
	return 1;
}

hook OnPlayerEnterCheckpoint(playerid)
{
    if (GetPlayerCP(playerid) == 451)
    {
		SendClientMessage(playerid, 0xE7CF90FF, "Tutorial: Você precisa engantar a carga e ir até a balança comprar os produtos.");
		SetPlayerCheckpoint(playerid, 2227.3552,-2225.3704,13.6299, 20.0);
        SetPlayerCP(playerid, CP_NULL);

		return 1;
    }

    else if (GetPlayerCP(playerid) == 444)
    {
		SendClientMessage(playerid, 0xE7CF90FF, "Tutorial: Você precisa engantar a carga e ir até a balança comprar os produtos.");
		SetPlayerCheckpoint(playerid, 2227.3552,-2225.3704,13.6299, 20.0);
        SetPlayerCP(playerid, CP_NULL);

		return 1;
    }

	else if(GetPlayerCP(playerid) == 76){

	    GameTextForPlayer(playerid, "~r~Voce chegou ao pedido de reforco", 4000, 5);
	    SetPlayerCP(playerid, CP_NULL);
	}

	else if(GetPlayerCP(playerid) == 58)
	{
	    GameTextForPlayer(playerid, "Voce chegou ao~n~caixa", 4000, 5);
	    SetPlayerCP(playerid, CP_NULL);
	}
	// Quando seleciona HQ no gps
	else if(GetPlayerCP(playerid) == 620)
	{
	    GameTextForPlayer(playerid, "Voce chegou na~n~HQ da Organizacao", 4000, 5);
	    SetPlayerCP(playerid, CP_NULL);
	}
   	else if(PlayerToPoint(1.7,playerid,246.4971,74.3957,1003.6406))//Postao Presos DP
    {
        callcmd::pp(playerid);
        GameTextForPlayer(playerid, " ~w~Portao Celas ~b~Aberto", 5000, 3);
   	}
   	else if(PlayerToPoint(1.7,playerid, 245.3453, 73.8288, 1003.6406)) //Postao Presos DP
    {
        callcmd::pp(playerid);
        GameTextForPlayer(playerid, " ~w~Portao Celas ~b~Aberto", 5000, 3);
   	}
	// else if (GetPlayerCP(playerid) != 9988 && IsCloseOnEnterCheckpoint(playerid)) {
	else if (GetPlayerCP(playerid) != 9988) {
		DisablePlayerCheckpoint(playerid);
	}
	return 1;
}

hook OP_PickUpDynamicPickup(playerid, pickupid)
{
    waOnPlayerPickUpDynamicPickup(playerid, pickupid);

	if (bxOnPlayerPickUpDynamicPickup(playerid, pickupid)) return true;

    if (pickupid == pickDoacao)
	{
        if (GetPVarInt(playerid, "doando")) return 1;

        SetPVarInt(playerid, "doando", 1);

        return ShowPlayerDialog(playerid, 4214, DIALOG_STYLE_INPUT, " ", "Você pode fazer uma doação para o cofre do Governo.\nDigite o valor de sua doação abaixo:\nOBS: O valor doado irá diretamente para o cofre do Governo e não poderá ser reembolsado!", "Doar", "Cancelar");
    }

	if (pickupid == pickHay && JoinedHay[playerid])
	{
	    DestroyDynamicPickup(pickHay);
	    winHay(playerid);
	    return 1;
	}

	if( pickupid == LFicha) {
		return GameTextForPlayer(playerid, "~b~digite~n~~w~/limparficha", 3000, 3);
	}

    return 1;
}

hook OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	if (result == -1) 
		return SendMsgF(playerid, -1, "O comando ({FF0000}%s{FFFFFF}) que você digitou não existe no servidor, use: {FFAA00}/ajuda", cmd), 0;

	if (!strcmp(cmd, "/atendimento")) {
		if (!Admin_GetNivel(playerid) && Player_GetMuted(playerid)) {
			SendClientMessage(playerid, COLOR_WARNING, "Você está mutado, digite: /atendimento.");
			return 0;
		}
	}

	// Anti Flood
	if (GetTickCount() < PlayerInfo[playerid][pFlood])
	{
		PlayerInfo[playerid][pFloodTimes] ++;

		if (PlayerInfo[playerid][pFloodTimes] > 2) {
			SendClientMessage(playerid, COLOR_LIGHTRED, "Você precisa parar de floodar ou será kickado.");
		}
		else if (PlayerInfo[playerid][pFloodTimes] > 4)
		{
			PlayerInfo[playerid][pFloodTimes] = 0;
			SendClientMessage(playerid, COLOR_LIGHTRED, "Você foi kickado do servidor por flood excessivo.");
			KickEx(playerid);
		}
	}
	else
	{
		PlayerInfo[playerid][pFlood] 	  = GetTickCount() + 500;
		PlayerInfo[playerid][pFloodTimes] = 0;
	}
	return 1;
}

hook OnPlayerText(playerid, text[])
{
	if (!Admin_GetNivel(playerid) && Player_GetMuted(playerid)) 
		return SendClientMessage(playerid, COLOR_WARNING, "Você está mutado, digite: /atendimento."), false;

	if (GetPlayerBeingAbducted(playerid)) 
		return SendClientMessage(playerid, COLOR_WARNING, "Você foi amordaçado, não pode falar."), false;

    static string[144];

	if (text[0] == '@')
	{
		if (strlen(text[1]) < 1)
			return SendClientMessage(playerid, -1, "Use: @ [texto] - para falar no chat da família"), false;

        new id = GetPlayerFamily( playerid );

		if ( id != -1) {

			format(string, sizeof string, "@ %s [%s]: %s", familyInfo[id][familyName], PlayerName[playerid], text[1]);
			sendFamilyMsg(id, 0xFFAAAAFF, string);

			log_chat(playerid, string);

		    return 0;
		} else {
		    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pertence a nenhuma família!");
		    return 0;
		}
	}
	else if(text[0] == '!') {
		if (strlen(text[1]) < 1)
			return SendClientMessage(playerid, -1, "Use: ! [texto] - para falar no chat"), false;

		SendRealChatMessage(playerid, text[1]);
		return 0;
	}

	if(MarriageCeremoney[playerid] > 0)
	{
 		if (!strcmp(text, "sim", true))
		{
		    if(GotProposedBy[playerid] < 999)
		    {
			    if(IsPlayerConnected(GotProposedBy[playerid]))
				{
				    format(string, sizeof(string), "Padre: %s Você aceita %s como sua amada esposa? (Digite 'sim', qualquer outra coisa cancela o casamento).", PlayerName[GotProposedBy[playerid]], PlayerName[playerid]);
					SendClientMessage(GotProposedBy[playerid], -1, string);
					MarriageCeremoney[GotProposedBy[playerid]] = 1;
					MarriageCeremoney[playerid] = 0;
					GotProposedBy[playerid] = 999;
				    return true;
			    }
			    else
			    {
			        MarriageCeremoney[playerid] = 0;
			        GotProposedBy[playerid] = 999;
			        return 0;
			    }
			}
			else if(ProposedTo[playerid] < 999)
			{
			    if(IsPlayerConnected(ProposedTo[playerid]))
				{
					if(PlayerInfo[playerid][pSex] != PlayerInfo[ProposedTo[playerid]][pSex])
					{
						format(string, sizeof(string), "Padre: %s e %s eu vos declaro Marido e Mulher, Pode Beijar a Noiva.", PlayerName[playerid], PlayerName[ProposedTo[playerid]]);
						SendClientMessage(playerid, -1, string);
				   		format(string, sizeof(string), "Padre: %s e %s eu vos declaro Marido e Mulher, Pode Beijar o Noivo.", PlayerName[ProposedTo[playerid]], PlayerName[playerid]);
						SendClientMessage(ProposedTo[playerid], -1, string);
						format(string, sizeof(string), "Noticia de Casamento: Temos um novo Casamento, %s e %s se casaram.", PlayerName[playerid], PlayerName[ProposedTo[playerid]]);
						SendClientMessageToAll(-1, string);
					}
					else if(PlayerInfo[playerid][pSex] == 1 && PlayerInfo[ProposedTo[playerid]][pSex] == 1)
					{
					    format(string, sizeof(string), "Padre: %s e %s eu os declaro Marido e Marido, Pode Beijar o Noivo.", PlayerName[playerid], PlayerName[ProposedTo[playerid]]);
						SendClientMessage(playerid, -1, string);
				   		format(string, sizeof(string), "Padre: %s e %s eu os declaro Marido e Marido, Pode Beijar o Noivo.", PlayerName[ProposedTo[playerid]], PlayerName[playerid]);
						SendClientMessage(ProposedTo[playerid], -1, string);
						format(string, sizeof(string), "Noticia de Casamento: Temos um novo Casamento Gay, %s e %s se casaram.", PlayerName[playerid], PlayerName[ProposedTo[playerid]]);
						SendClientMessageToAll(-1, string);
					}
					else if(PlayerInfo[playerid][pSex] == 2 && PlayerInfo[ProposedTo[playerid]][pSex] == 2)
					{
					    format(string, sizeof(string), "Padre: %s e %s eu os declaro Esposa e Esposa, Pode Beijar a Noiva.", PlayerName[playerid], PlayerName[ProposedTo[playerid]]);
						SendClientMessage(playerid, -1, string);
				   		format(string, sizeof(string), "Padre: %s e %s eu os declaro Esposa e Esposa, Pode Beijar a Noiva", PlayerName[ProposedTo[playerid]], PlayerName[playerid]);
						SendClientMessage(ProposedTo[playerid], -1, string);
						format(string, sizeof(string), "Noticia de Casamento: Temos um novo Casamento Lesbico, %s e %s se casaram.", PlayerName[playerid], PlayerName[ProposedTo[playerid]]);
						SendClientMessageToAll(-1, string);
					}
					CheckConquista(playerid, Conquista_Casado);
					CheckConquista(ProposedTo[playerid], Conquista_Casado);
					MarriageCeremoney[ProposedTo[playerid]] = 0;
					MarriageCeremoney[playerid] = 0;
					format(string, sizeof(string), "%s", PlayerName[playerid]);
					strmid(PlayerInfo[ProposedTo[playerid]][pMarriedTo], string, 0, strlen(string), 255);
					format(string, sizeof(string), "%s", PlayerName[ProposedTo[playerid]]);
					strmid(PlayerInfo[playerid][pMarriedTo], string, 0, strlen(string), 255);
					PlayerInfo[playerid][pMarried] = 1;
					PlayerInfo[ProposedTo[playerid]][pMarried] = 1;
					ProposedTo[playerid] = 999;
					MarriageCeremoney[playerid] = 0;

				    return true;
			    }
			    else
			    {
			        MarriageCeremoney[playerid] = 0;
			        ProposedTo[playerid] = 999;
			        return 0;
			    }
			}
		}
		else
		{
		    if(GotProposedBy[playerid] < 999)
		    {
				if(IsPlayerConnected(GotProposedBy[playerid]))
				{
					format(string, sizeof(string), "* Você deseja se casar com %s, Se quiser Digite 'sim'.", PlayerName[GotProposedBy[playerid]]);
				    SendClientMessage(playerid, COLOR_YELLOW, string);
				    format(string, sizeof(string), "* %s quer casar com Você, um 'sim' foi dito.",PlayerName[playerid]);
				    SendClientMessage(GotProposedBy[playerid], COLOR_YELLOW, string);
				    return 0;
			    }
			    else
			    {
			        MarriageCeremoney[playerid] = 0;
			        GotProposedBy[playerid] = 999;
			        return 0;
			    }
		    }
		    else if(ProposedTo[playerid] < 999)
			{
			    if(IsPlayerConnected(ProposedTo[playerid]))
				{
					format(string, sizeof(string), "* Você deseja se casar com %s, Se quiser Digite 'sim'.", PlayerName[ProposedTo[playerid]]);
				    SendClientMessage(playerid, COLOR_YELLOW, string);
				    format(string, sizeof(string), "* %s quer casar com Você, um 'sim' foi dito.",PlayerName[playerid]);
				    SendClientMessage(ProposedTo[playerid], COLOR_YELLOW, string);
				    return 0;
			    }
			    else
			    {
			        MarriageCeremoney[playerid] = 0;
			        ProposedTo[playerid] = 999;
			        return 0;
			    }
			}
		}
	    return 0;
	}

	if (atendimentoFarmacia[playerid])
	{
	    new playerWorld = GetPlayerVirtualWorld(playerid);

		switch (playerWorld)
		{
			case 10013: ApplyDynamicActorAnimation(actorFarmacia[0], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
			case 10014: ApplyDynamicActorAnimation(actorFarmacia[1], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
			case 10015: ApplyDynamicActorAnimation(actorFarmacia[2], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
			default: ApplyDynamicActorAnimation(actorFarmacia[3], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		}

		if (!IsPlayerInRangeOfPoint(playerid, 3.0, 604.0738, -601.3110, 985.6933))
		{
			atendimentoFarmacia[playerid] = false;
			return SendClientMessage(playerid, -1, "Você não está mais na farmácia, o atendimento foi cancelado."), false;
		}

	    if (!strcmp(text, "remedinho", true))
	    {
 			SetPVarInt(playerid, "farmaciaItem", 1);

 			format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, agora a quantidade de remedinho: 1, 5 ou 10?", PlayerName[playerid]);
			return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
		}
		else if (!strcmp(text, "remedio", true))
	    {
 			SetPVarInt(playerid, "farmaciaItem", 2);

 			format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, agora a quantidade de remédio grande: 1, 5 ou 10?", PlayerName[playerid]);
			return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
		}
		else if (!strcmp(text, "medkit", true))
	    {
 			SetPVarInt(playerid, "farmaciaItem", 3);

 			format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, agora a quantidade de medkit: 1, 5 ou 10?", PlayerName[playerid]);
			return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
		}
		else if (!strcmp(text, "1", true))
	    {
			if (isInventoryFull(playerid))
				return SendClientMessage(playerid, -1, "Você não tem espaço no inventário."), false;

			if (GetPVarInt(playerid, "farmaciaItem") == 1) {

			    if (Player_GetMoney(playerid) < 120) {

			    	atendimentoFarmacia[playerid] = false;
	   				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não tem dinheiro suficiente.", PlayerName[playerid]);
					return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
 				}
        		givePlayerItem(playerid, ITEM_TYPE_REMEDIOP, 11736, 1, "Remedio Pequeno");

				Player_RemoveMoney(playerid, 120);
				DepositPropertie(playerid, 120); DeletePVar(playerid, "farmaciaItem");

				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você comprou 1 remédio pequeno por $120.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
        	}
        	else if (GetPVarInt(playerid, "farmaciaItem") == 2)
			{
			    if (Player_GetMoney(playerid) < 200)
				{
			    	atendimentoFarmacia[playerid] = false;
	   				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não tem dinheiro suficiente.", PlayerName[playerid]);
					return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
 				}
        		givePlayerItem(playerid, ITEM_TYPE_REMEDIO, 11738, 1, "Remedio Grande");

				Player_RemoveMoney(playerid, 200);
				DepositPropertie(playerid, 200); DeletePVar(playerid, "farmaciaItem");

				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você comprou 1 remédio grande por $200.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
        	}
        	else if (GetPVarInt(playerid, "farmaciaItem") == 3)
			{
			    if (Player_GetMoney(playerid) < 250)
				{
			    	atendimentoFarmacia[playerid] = false;
	   				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não tem dinheiro suficiente.", PlayerName[playerid]);
					return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
 				}
        		givePlayerItem(playerid, ITEM_TYPE_MEDKIT, 11736, 1, "MedKit de chao");

				Player_RemoveMoney(playerid, 250);
				DepositPropertie(playerid, 250); DeletePVar(playerid, "farmaciaItem");

				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você comprou 1 medkit de chão por $250.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
        	}
        	else {
        		format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não nos informou o produto.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
			}
		}
		else if (!strcmp(text, "5", true))
	    {
		    if (isInventoryFull(playerid))
				return SendClientMessage(playerid, -1, "Você não tem espaço no inventário."), false;

			if (GetPVarInt(playerid, "farmaciaItem") == 1) {

			    if (Player_GetMoney(playerid) < 500) {

			    	atendimentoFarmacia[playerid] = false;
	   				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não tem dinheiro suficiente.", PlayerName[playerid]);
					return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
 				}
        		givePlayerItem(playerid, ITEM_TYPE_REMEDIOP, 11736, 5, "Remedio Pequeno");

				Player_RemoveMoney(playerid, 500);
				DepositPropertie(playerid, 500); DeletePVar(playerid, "farmaciaItem");

				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você comprou 5 remédios pequeno por $500.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
        	}
        	else if (GetPVarInt(playerid, "farmaciaItem") == 2) {

			    if (Player_GetMoney(playerid) < 900) {

			    	atendimentoFarmacia[playerid] = false;
	   				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não tem dinheiro suficiente.", PlayerName[playerid]);
					return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
 				}
        		givePlayerItem(playerid, ITEM_TYPE_REMEDIO, 11738, 5, "Remedio Grande");

				Player_RemoveMoney(playerid, 900);
				DepositPropertie(playerid, 900); DeletePVar(playerid, "farmaciaItem");

				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você comprou 5 remédios grande por $900.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
        	}
        	else if (GetPVarInt(playerid, "farmaciaItem") == 3) {

			    if (Player_GetMoney(playerid) < 1000) {

			    	atendimentoFarmacia[playerid] = false;
	   				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não tem dinheiro suficiente.", PlayerName[playerid]);
					return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
 				}
        		givePlayerItem(playerid, ITEM_TYPE_MEDKIT, 11736, 5, "MedKit de chao");

				Player_RemoveMoney(playerid, 1000);
				DepositPropertie(playerid, 1000); DeletePVar(playerid, "farmaciaItem");

				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você comprou 5 medkits de chão por $1.000.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
        	}
        	else {
        		format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não nos informou o produto.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
			}
		}
		else if (!strcmp(text, "10", true))
	    {
		    if (isInventoryFull(playerid))
				return SendClientMessage(playerid, -1, "Você não tem espaço no inventário."), false;

			if (GetPVarInt(playerid, "farmaciaItem") == 1) {

			    if (Player_GetMoney(playerid) < 900) {

			    	atendimentoFarmacia[playerid] = false;
	   				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não tem dinheiro suficiente.", PlayerName[playerid]);
					return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
 				}
        		givePlayerItem(playerid, ITEM_TYPE_REMEDIOP, 11736, 10, "Remedio Pequeno");

				Player_RemoveMoney(playerid, 900);
				DepositPropertie(playerid, 900); DeletePVar(playerid, "farmaciaItem");

				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você comprou 10 remédios pequeno por $900.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
        	}
        	else if (GetPVarInt(playerid, "farmaciaItem") == 2) {

			    if (Player_GetMoney(playerid) < 1700) {

			    	atendimentoFarmacia[playerid] = false;
	   				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não tem dinheiro suficiente.", PlayerName[playerid]);
					return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
 				}
        		givePlayerItem(playerid, ITEM_TYPE_REMEDIO, 11738, 10, "Remedio Grande");

				Player_RemoveMoney(playerid, 1700);
				DepositPropertie(playerid, 1700); DeletePVar(playerid, "farmaciaItem");

				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você comprou 10 remédios grande por $1.700.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
        	}
        	else if (GetPVarInt(playerid, "farmaciaItem") == 3) {

			    if (Player_GetMoney(playerid) < 2000) {

			    	atendimentoFarmacia[playerid] = false;
	   				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não tem dinheiro suficiente.", PlayerName[playerid]);
					return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
 				}
        		givePlayerItem(playerid, ITEM_TYPE_MEDKIT, 11736, 10, "MedKit de chao");

				Player_RemoveMoney(playerid, 2000);
				DepositPropertie(playerid, 2000); DeletePVar(playerid, "farmaciaItem");

				format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você comprou 10 medkits de chão por $2.000.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
        	}
        	else {
        		format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, você não nos informou o produto.", PlayerName[playerid]);
				return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
			}
		}
		else {
		    atendimentoFarmacia[playerid] = false;
		    format(string, sizeof(string), "Willian Rodrigues(503) diz: %s, não compreendi seu pedido.", PlayerName[playerid]);
			return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
	 	}
	}

	if (TalkingLive[playerid] != 255)
	{
	    format(string, sizeof(string), "(AO VIVO) {9ACD32}%s: %s", PlayerName[playerid], text);
		OOCNews(0xFF0000AA, string); SetPlayerChatBubble(playerid, text, -1, 20.0, 10000);
		log_chat(playerid, string);
		return 0;
	}

	new onlineCall = MobileInfo[playerid][mobileCall];
	if (onlineCall != MAX_PLAYERS+5)
	{
		format(string, sizeof(string), "((Chamada de voz)) %s diz: %s", PlayerName[playerid], text);
		SetPlayerChatBubble(playerid, string, -1, 20.0, 10000);

		SendClientMessageInRange(20.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		log_chat(playerid, string);

		if (!IsPlayerConnected(onlineCall)) {
			onlineCall = MAX_PLAYERS+5;
			return SendClientMessage(playerid, -1, "((Chamada de voz)) A ligação caiu.");
		}

		if (MobileInfo[onlineCall][mobileCall] == playerid)
		{
			SendClientMessage(onlineCall, COLOR_YELLOW, string);
		}
		return false;
	}
	
	if (Attendance_GetValid(playerid) && Attendance_GetPlayer(playerid) != INVALID_PLAYER_ID) {
		new idplayer = Attendance_GetPlayer(playerid);

		if (Admin_GetNivel(playerid) || Helper_GetNivel(playerid))
			format(string, sizeof(string), "Atendimento ["C_ADMIN"%s{FFCCCC}] %s: %s", Staff_GetPositionName(playerid), PlayerName[playerid], text);
		else 
			format(string, sizeof(string), "Atendimento ["C_WHITE"Jogador{FFCCCC}] %s: %s", PlayerName[playerid], text);

		SendClientMessage(playerid, COLOR_ATENDIMENTO, string);
		SendClientMessage(idplayer, COLOR_ATENDIMENTO, string);
		log_chat(playerid, string);

		return 0;
	}
#if _inc_paintball_system
	if (OnChatPaintball(playerid, text)) return 0;
#endif
	
	SendRealChatMessage(playerid, text);
	return 0;
}

hook OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate)
{
    new vehicleid = GetPlayerVehicleID(playerid);
	new VIM:vim = Vehicle_GetVIM(vehicleid);

	SetPVarInt(playerid, "isPlayerEnteringVehicle", gettime() + 5);

	foreach(new i : Player) {
		if (Admin_GetNivel(i)) {
			if (SpectadorInfo[i][spectadorID] == playerid) {
				if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
					PlayerSpectateVehicle(i, GetPlayerVehicleID(playerid));
				else
					PlayerSpectatePlayer(i, playerid);
			}
		}
	}

	if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{
		if (GetPVarInt(playerid, "VarFPS"))
		{
	    	if(IsValidObject(dcObject[playerid])) DestroyObject(dcObject[playerid]);
			SetCameraBehindPlayer(playerid);
			SetPVarInt(playerid, "VarFPS", 0);
		}
	}

	if (newstate == PLAYER_STATE_DRIVER)
    {	
		if (IsPlayerInDrone(playerid) && PlayerCaminhao[playerid][caminhaoValid]) 
			return true;

		if (CheckChave(playerid, GetPlayerVehicleID(playerid))) {
			RemovePlayerFromVehicle(playerid);
		} else {
			SendClientMessage(playerid, -1, "Pressione 'Y' ou digite (/motor) para girar a chave e ligar o veículo.");
			SendClientMessage(playerid, -1, "Para obter ajuda sobre o veiculo use: /ajudaveiculos, e use /menucarro para acessar o menu.");
			SendClientMessage(playerid, -1, "Use /camera para dirigir o veículo em primeira pessoa");

            // for(new carro; carro < sizeof(CarrosConce); carro++) {
		    // 	if (vehicleid == CarrosConce[carro][ConceID]) {
            //         StopVehicleEngine(vehicleid);
			// 		VehicleInfo[vehicleid][vehicleCombustivel] = 100;
			// 		break;
			// 	}
			// }
			if (!VIM_IsBike(vim)) {
				if (!IsPlayerHaveItem(playerid, ITEM_TYPE_MOTORISTA) && !InTeste[playerid])
					SendClientMessage(playerid, COLOR_LIGHTRED, "Você não tem carteira de habilitação, fique atento com a Policia Rodoviária.");
			}

			if (VIM_IsPlane(vim)) {
		    	if (!IsPlayerHaveItem(playerid, ITEM_TYPE_PILOTO) && !InTeste[playerid]) {
			    	SendClientMessage(playerid, COLOR_LIGHTRED, "Você ainda não tem licença para Voar! Compre uma no centro de licenças !");
				}
			}

			if (VIM_IsBoat(vim)) {
		    	if (!IsPlayerHaveItem(playerid, ITEM_TYPE_MARUJO) && !InTeste[playerid]) {
			    	SendClientMessage(playerid, COLOR_LIGHTRED, "Você ainda não tem licença para Navegar! Compre uma no centro de licenças !");
				}
			}
		}

        if(GetVehicleModel(vehicleid) == 497){

            SendClientMessage(playerid, -1, "SERVER: Este helicoptero está equipado com uma plataforma externa!");
            if(!Plataforma[vehicleid]){

			    new plataformaHeli1,plataformaHeli2;

				plataformaHeli1 = CreateDynamicObject(19443, 0.0, 0.0, 0.0,   0.00000, 0.00000, 0.0);
				plataformaHeli2 = CreateDynamicObject(19443, 0.0, 0.0, 0.0,   0.00000, 0.00000, 0.0);

				AttachDynamicObjectToVehicle(plataformaHeli1, GetPlayerVehicleID(playerid), 1.96569, 0.93654, -1.11930,   0.00000, -90.00000, 270.27441);
		        AttachDynamicObjectToVehicle(plataformaHeli2, GetPlayerVehicleID(playerid), -1.99423, 0.95571, -1.11930,   0.00000, -90.00000, 270.27441);

				SetDynamicObjectMaterialText(plataformaHeli1, 0, " ");
				SetDynamicObjectMaterialText(plataformaHeli2, 0, " ");

				Plataforma[vehicleid] = true;

                SendClientMessage(playerid, -1, "SERVER: Plataforma criada com sucesso!");
            }
        }

	    if (!IsPlayerInDrone(playerid) && IsABombCar(GetPlayerVehicleID(playerid)))
		{
			if(GetPlayerOrg(playerid) != 3
			  && GetPlayerOrg(playerid) != 15
			  && GetPlayerOrg(playerid) != 23
			  && GetPlayerOrg(playerid) != 20
			  && GetPlayerOrg(playerid) != 29)
			{
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, " Você não está autorizado a usar este veiculo !");
			    RemovePlayerFromVehicle(playerid);
			}
	    }

		if (PlayerCaminhao[playerid][caminhaoValid] && GetPlayerVehicleID(playerid) == PlayerCaminhao[playerid][caminhaoId])
			CaminhaoCancelForPlayer(playerid);
    }

	if(newstate == PLAYER_STATE_PASSENGER)
	{
		if (GetVehicleModel(vehicleid) == 427 && GetPlayerVehicleSeat(playerid) > 1)
		{
            SetPlayerPos(playerid, -26.3874,42.8232,1000.3384);
            SetPlayerFacingAngle(playerid, 1.9905);
            SetPlayerInterior(playerid, 10);
            SetPlayerVirtualWorld(playerid, vehicleid);
            SetCameraBehindPlayer(playerid);
            Streamer_UpdateEx(playerid, -26.3874,42.8232,1000.3384, -1, -1, STREAMER_TYPE_OBJECT);

            SetPVarInt(playerid, "playerEnforcer", vehicleid);
			FreezeThePlayer(playerid, 3000);

            return 1;
        }

	   	new arma = GetPlayerWeapon(playerid);
	    if(arma == 24 || arma == 25)
	    {
			SetPlayerArmedWeapon(playerid, WEAPON_FIST);
			SendClientMessage(playerid, -1, "Proibido entrar de passageiro com esta arma, ela foi retirada de sua mão!");
		}
	}

	if (newstate == PLAYER_STATE_ONFOOT)
	{
		if (IsPlayerAttachedObjectSlotUsed(playerid, Slot_Capacete))
		{
		    RemovePlayerAttachedObject(playerid, Slot_Capacete);
		}
    }

    if (newstate != PLAYER_STATE_DRIVER)
    {
		if (PlayerCaminhao[playerid][caminhaoValid] && GetPlayerVehicleID(playerid) == PlayerCaminhao[playerid][caminhaoId])
		{
			CaminhaoCancelForPlayer(playerid);
			CancelPlayerCaminhao(playerid);
		}
    }

	if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE:3)
    {
	   	new arma = GetPlayerWeapon(playerid);
	    if(arma == 24 || arma == 27)
	    {
			SetPlayerArmedWeapon(playerid, WEAPON_FIST);
			SendClientMessage(playerid, COLOR_GRAD, "OBS: Você foi desarmado por tentar entrar de passageiro com uma arma proibida!");
		}
	}
	return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
	if (Player_GetBusyHand(playerid, RIGHT_HAND) && Player_GetBusyHand(playerid, LEFT_HAND)) {
		return SendClientMessage(playerid, -1, "Você está com as duas mãos ocupadas."), false;
	}

	switch (GetVehicleModel(vehicleid))
	{
	    case 578:
	    {
	        if (PlayerCaminhao[playerid][caminhaoCarga] > 0)
	        {
				SendClientMessage(playerid, -1, "Você perdeu a carga do caminhão pois saiu dele!");

				PlayerCaminhao[playerid][caminhaoCarga] = 0; // Perde a carga do caminhão
			}
		}
	}

	new VIM:vim = Vehicle_GetVIM(vehicleid);

	if (GetVehicleSpeed(vehicleid) > 25 && VIM_IsPlane(vim) && eEjet[playerid] == -1) {

	    if (IsPlaneInAir(vehicleid))
		{
	        new Float: Vel[3];

			GetPlayerPos(playerid, Vel[0], Vel[1], Vel[2]);
	        SetPlayerPos(playerid, Vel[0], Vel[1], Vel[2] + 5.0);

			GetPlayerVelocity(playerid, Vel[0], Vel[1], Vel[2]);
			SetPlayerVelocity(playerid, Vel[0], Vel[1], Vel[2] + 500.0);

			SetTimerEx("eTerminar", 3100, false, "dd", playerid, vehicleid);

			GivePlayerWeapon(playerid, WEAPON_PARACHUTE, 1);

			eEjet[playerid] = SetTimerEx("eContinuar", 50, true, "i", playerid);

			ApplyAnimation(playerid, "FOOD","FF_Sit_Loop", 4.0, true, true, true, false, 0);
	    }
	}

	if (GetPVarInt(playerid, "VarFPS"))
	{
		if (IsValidObject(dcObject[playerid])) DestroyObject(dcObject[playerid]);
		SetCameraBehindPlayer(playerid);
		SetPVarInt(playerid, "VarFPS", 0);
	}

 	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		return true;

	TogglePlayerControllable(playerid, true);

	return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	SetPVarInt(playerid, "isPlayerEnteringVehicle", gettime() + 5);

	switch (GetVehicleModel(vehicleid))
	{
	    case 519:
	    {
	        if (ispassenger)
	        {
				SetPlayerInterior(playerid, 1);
				SetPlayerPos(playerid, 2.6812,33.1429,1199.5938);
				SetPlayerFacingAngle(playerid, 273.5990);
			    SetPVarInt(playerid, "jatoId", vehicleid);
			    SetPlayerVirtualWorld(playerid, vehicleid);
			    return true;
    		}
	    }
	}

	if (vehicleid == PlayerCaminhao[playerid][caminhaoId]) 
		CaminhaoCancelForPlayer(playerid);
	
	return 1;
}

// ------------------------------ Últimos kills, Iniciar Combate ------------------------------
#define SHOW_LAST_KILLS  (10)

static playerLastKills[MAX_PLAYERS][SHOW_LAST_KILLS][55];

stock addPlayerLastKill(playerid, killedid, WEAPON:weaponid)
{
	if (playerid != INVALID_PLAYER_ID)
	{
		new sdate[3];
		new string[55];
		gettime(sdate[0], sdate[1], sdate[2]);

		// Loop
		for(new loop; loop != SHOW_LAST_KILLS - 1; loop++)
		    format(playerLastKills[playerid][loop], sizeof (string), playerLastKills[playerid][loop + 1]);

		new weapon_name[25];
		GetWeaponName(weaponid, weapon_name);

		// Add
		format(string, sizeof string, "[%02d:%02d:%02d]\tMatou %s com uma %s\n", sdate[0], sdate[1], sdate[2], PlayerName[killedid], weapon_name);
	    format(playerLastKills[playerid][SHOW_LAST_KILLS - 1], 55, string);
	}
}

stock resetPlayerLastKill(playerid)
{
	for (new loop; loop != SHOW_LAST_KILLS; loop++)
	    format(playerLastKills[playerid][loop], 55, "[00:00:00]\tMatou ---- com uma ----\n");
}

stock showLogKills(playerid, showid)
{
	MEGAString[0] = EOS;

	new string[75];

	for(new loop; loop != SHOW_LAST_KILLS; loop++)
		strcat(MEGAString, playerLastKills[playerid][loop]);

	format(string, sizeof string, "Últimos %d kills de %s", SHOW_LAST_KILLS, PlayerName[playerid]);
	ShowPlayerDialog(showid, 0, DIALOG_STYLE_MSGBOX, string, MEGAString, "Fechar", "");

	return true;
}

CMD:meuskills(playerid) return showLogKills(playerid, playerid);

#define MAX_COMBATES (31)
new CombateLog[31][160];

enum CombateEnum {
	cbPlayer1,
	cbPlayer2,
	cbTimestamp[30],
	bool:cbRevidado,
	bool:cbAssassinoAluguel,
	bool:cbCriado
}

new CombateInfo[MAX_COMBATES][CombateEnum];

stock ResetCombate()
{
	for(new i = 0; i < MAX_COMBATES; i++) {
		CombateInfo[i][cbCriado] = false;
	}

	for(new x; x != MAX_COMBATES; x++)
	    format(CombateLog[x], 160, "{E0D78A}[00:00:00] {FFFFFF}Ninguem iniciou um combate contra Ninguem\n");
}

stock AddCombate(playerid, damagedid)
{
	new string[160];

	new hora, minuto, segundo;
	gettime(hora, minuto, segundo);

	new id = MAX_COMBATES - 1;
	CombateInfo[id][cbPlayer1] = playerid;
	CombateInfo[id][cbPlayer2] = damagedid;
	CombateInfo[id][cbCriado] = true;
	CombateInfo[id][cbRevidado] = false;
	CombateInfo[id][cbAssassinoAluguel] = false;

	format(CombateInfo[id][cbTimestamp], 30, "%02d:%02d:%02d", hora, minuto, segundo);

	if (GoChase[playerid] == damagedid) {
		CombateInfo[id][cbAssassinoAluguel] = true;
	}

	UpdateCombateLog(id);

	for(new x; x != MAX_COMBATES - 1; x++)
	{
		CombateInfo[x][cbPlayer1] = CombateInfo[x + 1][cbPlayer1];
		CombateInfo[x][cbPlayer2] = CombateInfo[x + 1][cbPlayer2];
		CombateInfo[x][cbCriado] = CombateInfo[x + 1][cbCriado];
		CombateInfo[x][cbRevidado] = CombateInfo[x + 1][cbRevidado];
		CombateInfo[x][cbAssassinoAluguel] = CombateInfo[x + 1][cbAssassinoAluguel];
		format(CombateInfo[x][cbTimestamp], 30, CombateInfo[x + 1][cbTimestamp]);

	    format(CombateLog[x], 160, CombateLog[x + 1]);
	}

	format(CombateLog[MAX_COMBATES - 1], 160, string);
}

stock UpdateCombateLog(combateid) {
	if(CombateInfo[combateid][cbCriado]) {
		new playerid = CombateInfo[combateid][cbPlayer1], damagedid = CombateInfo[combateid][cbPlayer2], 
			status[20] = "revidado";

		if(!CombateInfo[combateid][cbRevidado])
			format(status, 20, "não revidado");

		if(!CombateInfo[combateid][cbAssassinoAluguel]) {
			format(CombateLog[combateid], 160, "{E0D78A}[%s] {%s}%s {FFFFFF}iniciou um combate contra {%s}%s [%s]\n", CombateInfo[combateid][cbTimestamp],
				GetOrgColor(GetPlayerOrg(playerid)), PlayerName[playerid], GetOrgColor(GetPlayerOrg(damagedid)), PlayerName[damagedid], status);
		}
		else {
			format(CombateLog[combateid], 160, "{E0D78A}[%s] {%s}Assassino {FFFFFF}iniciou um combate contra {%s}%s [%s]\n", CombateInfo[combateid][cbTimestamp],
				GetOrgColor(GetPlayerOrg(playerid)), GetOrgColor(GetPlayerOrg(damagedid)), PlayerName[damagedid], status);
		}

		new string[128];

		format(string, sizeof(string), "(%s - %s) Iniciou um combate contra (%s - %s)", PlayerName[playerid], GetNomeOrg(GetPlayerOrg(playerid)), PlayerName[damagedid], GetNomeOrg(GetPlayerOrg(damagedid)));
		server_log("combates", string);
	}
	else {
		format(CombateLog[combateid], 160, "{E0D78A}[00:00:00] {FFFFFF}Ninguem iniciou um combate contra Ninguem\n");
	}
}

stock UpdatePlayersCombate(playerid, damagedid) {
	for(new i = 0; i < MAX_COMBATES; i++) {
		if(CombateInfo[i][cbCriado] && ((CombateInfo[i][cbPlayer1] == playerid && CombateInfo[i][cbPlayer2] == damagedid) || 
			(CombateInfo[i][cbPlayer2] == playerid && CombateInfo[i][cbPlayer1] == damagedid)) && !CombateInfo[i][cbRevidado]) {
			
			CombateInfo[i][cbRevidado] = true;
			UpdateCombateLog(i);
			break;
		}
	}
}

CMD:vercombates(playerid)
{
    MEGAString[0] = EOS;

	strcat(MEGAString, "» Logs de início de combate (Quem atirou/bateu primeiro)\n\n");

	for(new x; x != MAX_COMBATES; x++)
	{
		if (CombateLog[x][0])
			strcat(MEGAString, CombateLog[x]);
	}
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "» Log de Combates", MEGAString, "Fechar", "");

	return true;
}


// GPS Locais

enum enumGps {
	Float:gpsX,
	Float:gpsY,
	Float:gpsZ,
	gpsName[45],
}

new g_GpsLocations[][enumGps] =
{
	{1682.7728, -2286.5195, 13.5077, "Respawn Civil"},
	{1478.7834,-1783.3513,13.5400, "Governo"},
	{1546.4607,-1675.7776,13.5624, "Delegacia de Policia"},
	{1479.1299,-1631.8226,14.7433, "Presentes"},
	#if defined _JAIL_SYSTEM_ON
		{_JAIL_ENTRY_X, _JAIL_ENTRY_Y, _JAIL_ENTRY_Z, _JAIL_NAME},
	#else
		{0.0, 0.0, 0.0, "{FF0000}[!] "_JAIL_NAME""},
	#endif
	{1769.9475,-1863.3495,13.5752, "Eventos Admin"},
	{1961.4530,-2188.9846,13.1108, "Aeroporto"},
	{1607.6766,-1549.4669,13.1521, "Mercado Negro"},
	{2247.9729,-132.32190,26.5753, "Pátio da Policia Rodoviaria"},
	{2689.0776, -1695.2633, 9.9104, "Paintball (Arena de combate)"},
	{1005.5239,-939.8887,42.1797, "Posto Norte"},
	{1944.5698,-1772.5813,13.3906, "Posto Sul"}
};

activeGPSLocation(playerid, gpsid)
{
	new string_gps[100];
	format(string_gps, sizeof (string_gps), "Seu GPS foi ativado em {00FFFF}%s{FFFFFF}, siga a marca vermelha no mapa!", g_GpsLocations[gpsid][gpsName]);
	SendClientMessage(playerid, -1, string_gps);

	SetPlayerCheckpoint(playerid, g_GpsLocations[gpsid][gpsX],g_GpsLocations[gpsid][gpsY],g_GpsLocations[gpsid][gpsZ], 5.0);

	SetPlayerCP(playerid, CP_NULL);
}

showGPSLocations(playerid) 
{
	new string_gps[128];

	MEGAString [0] = EOS;
	strcat(MEGAString, "Local\tDistância\n");

	for(new location; location != sizeof (g_GpsLocations); location++) {
	    format(string_gps, sizeof (string_gps), "{00FFFF}%s\t{FFFFFF}%.0f Metros\n", g_GpsLocations[location][gpsName],
		GetPlayerDistanceFromPoint(playerid, g_GpsLocations[location][gpsX], g_GpsLocations[location][gpsY], g_GpsLocations[location][gpsZ]));
	    strcat(MEGAString, string_gps);
	}
	ShowPlayerDialog(playerid, 100, DIALOG_STYLE_TABLIST_HEADERS, "GPS > Locais importantes", MEGAString, "Localizar", "Voltar");
}

// Localização das garagens de tunagem
enum enumTransfLocal 
{
	Float:transl_x,
	Float:transl_y,
	Float:transl_z,
	cidade_transfender[16],
	name_transfender[29],
}

new TransfendersLocalization[5][enumTransfLocal] = {
	{2644.8623, -2038.8019, 13.5500, "Los Santos", "Loco Low Co."},
	{-2715.9458, 217.4100, 4.3490, "San Fierro", "Whell Arch Angels"},
	{1041.3127, -1026.3291, 32.1016, "Los Santos", "Trasnfender Body Swap Shop"},
	{-1936.0258, 239.1326, 34.3216, "San Fierro", "Transfender Body Swap Shop"},
	{2386.6638, 1043.2096, 10.8203, "Las Venturas", "Trasnfender Body Swap Shop"}
};

stock SelectLocalTransfender(playerid, selectid) {
	new string[100];
	format(string, sizeof (string), "Seu GPS foi ativado em {00FFFF}%s{FFFFFF}, siga a marca vermelha no mapa!", TransfendersLocalization[selectid][name_transfender]);
	SendClientMessage(playerid, -1, string);

	SetPlayerCheckpoint(playerid, TransfendersLocalization[selectid][transl_x], TransfendersLocalization[selectid][transl_y], TransfendersLocalization[selectid][transl_z], 5.0);
    SetPlayerCP(playerid, CP_NULL);
}

stock ShowTransfendersLocal(playerid) {
	new string[128];

	MEGAString [0] = EOS;
	strcat(MEGAString, "Local\tCidade\tDistância\n");

	for(new location; location != sizeof (TransfendersLocalization); location++) 
	{
	    format(string, sizeof (string), "{FFFFFF}%s\t{9C9C9C}%s\t%.0f Metros\n", 
		TransfendersLocalization[location][name_transfender], TransfendersLocalization[location][cidade_transfender],
		GetPlayerDistanceFromPoint(playerid, TransfendersLocalization[location][transl_x], TransfendersLocalization[location][transl_y], TransfendersLocalization[location][transl_z]));
	    strcat(MEGAString, string);
	}
	ShowPlayerDialog(playerid, 109, DIALOG_STYLE_TABLIST_HEADERS, "GPS > Locais de tunning", MEGAString, "Localizar", "Voltar");
}


CMD:at(playerid)
{
	if (MobileInfo[playerid][mobileCall] != MAX_PLAYERS+5) return SendClientMessage(playerid, -1, "Você já está em uma ligação.");

	new string[128];
	foreach(new i : Player)
	{
		if (MobileInfo[i][mobileCall] == playerid)
		{
			MobileInfo[playerid][mobileCall] = i;
			SendClientMessage(i, COLOR_GRAD, "Chamada de voz iniciada... (aperte T para se comunicar)");

			format(string, sizeof(string), "(( %s atendeu uma chamada de voz ))", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

			return true;
		}
	}
	return true;
}

CMD:des(playerid, params[])
{
	new onlineCall = MobileInfo[playerid][mobileCall];

	if (!IsPlayerConnected(onlineCall)) return SendClientMessage(playerid,  COLOR_GRAD, "Você não está em nenhuma ligação.");

	if (onlineCall != INVALID_PLAYER_ID)
	{
		SendClientMessage(onlineCall, -1, "((Chamada de voz)) A ligação foi finalizada.");
		SendClientMessage(playerid, -1, "Você desligou a chamada de voz.");
		MobileInfo[onlineCall][mobileCall] = MAX_PLAYERS+5, MobileInfo[playerid][mobileCall] = MAX_PLAYERS+5;

		return true;
	}

	return SendClientMessage(playerid, -1, "Você guardou o celular em seu bolso.");
}

CMD:ligar(playerid, params[])
{
 	if (PlayerInfo[playerid][numeroCelular] == 0) return SendClientMessage(playerid, -1, "Você não possui um número de celular.");

	new numberCell;
	if (sscanf(params, "d", numberCell)) return SendClientMessage(playerid, -1, "Modo de uso: /ligar (número de celular)");

	if (numberCell == PlayerInfo[playerid][numeroCelular]) return false;

	if (MobileInfo[playerid][mobileCall] != MAX_PLAYERS+5) return SendClientMessage(playerid, -1, "Você está em uma ligação, use: /des, para desligar.");

	switch (numberCell)
	{
	    case 0: return SendClientMessage(playerid, -1, "O jogador que você tentou ligar não tem um celular!"), true;
		case 190: return callcmd::servico(playerid, "policia"), true;
		case 192: return callcmd::servico(playerid, "medico"), true;
	}

	new string[70 + MAX_PLAYER_NAME];

	format(string, sizeof(string), "(( %s pegou seu celular ))", PlayerName[playerid]);
	SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

	PlayerPlaySound(playerid, 3600,  0.0, 0.0, 0.0);

	foreach(new GivePlayer : Player)
	{
		if (PlayerInfo[GivePlayer][numeroCelular] == numberCell && numberCell != 0)
		{
		    if (MobileInfo[GivePlayer][mobileCall] != MAX_PLAYERS+5) return SendClientMessage(COLOR_YELLOW, -1, "O número que você ligou está ocupado");

		 	if (PhoneOnline[GivePlayer] > 0) return SendClientMessage(COLOR_YELLOW, -1, "((Chamada de voz)) A chipSIM informa, celular desligado ou fora da área de cobertura.");

		 	MobileInfo[playerid][mobileCall] = GivePlayer;

			format(string, sizeof(string), "Seu celular está recebendo uma ligação de %s. Use /at para atender.", PlayerName[playerid]);
			SendClientMessage(GivePlayer, COLOR_YELLOW, string);

			PlayerPlaySound(GivePlayer, 23000, 0.0, 0.0, 0.0);
			PlayerPlaySound(playerid, 23000, 0.0, 0.0, 0.0);

			SendClientMessage(playerid, -1, "Info: Use a letra 'T' para falar no celular.");
			SendClientMessage(playerid, -1, "Info: Para desligar seu telefone use /des.");

			format(string, sizeof(string), "(( O telefone celular de: %s está tocando ))", PlayerName[GivePlayer]);
			SendClientMessageInRange(30.0, GivePlayer, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

			return true;
		}
	}
	return SendClientMessage(playerid, COLOR_YELLOW, "((Chamada de voz)) A chipSIM informa, o número que você ligou está ocupado.");
}

CMD:sms(playerid, params[])
{
	if (!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Você não pode usar esse comando no momento.");

	new result[128], phonenumb;
	if (sscanf(params, "ds[128]", phonenumb, result)) return SendClientMessage(playerid, -1, "Modo de uso: /sms (número do celular) (mensagem)");

	if (strlen(result) < 2 || strlen(result) > 100) return SendClientMessage(playerid, -1, "O sms deve conter entre 2 a 100 caracteres.");

	if (PlayerInfo[playerid][numeroCelular] == 0) return SendClientMessage(playerid, -1, "Você não possui um celular, compre em um mercado 24/7.");

	if (phonenumb == PlayerInfo[playerid][numeroCelular])
		return SendClientMessage(playerid, -1, "Você não pode enviar mensagens para você mesmo.");


	new string[128];
	format(string, sizeof(string), "(( %s enviou uma mensagem de texto ))", PlayerName[playerid]);
	SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

	foreach(new i : Player)
	{
		if (PlayerInfo[i][numeroCelular] == phonenumb)
		{
			if (PhoneOnline[i] > 0) {
				return SendClientMessage(playerid, -1, "O número que você mandou mensagem está desligado.");
			} else {

				format(string, sizeof(string), "((SMS de %s [%d])): %s", PlayerName[playerid], PlayerInfo[playerid][numeroCelular], result);

				#if defined _CENSORED_protection
					censored_word_detected(string);
				#endif

				SendClientMessage(i, 0xDBED15FF, string);

				SendClientMessage(playerid, 0xDBED15FF, "Mensagem de texto enviada com sucesso!");

				foreach(new adm : Player)
				{
					if (SpyGet_Messages(adm) || (GetPVarInt(adm, "grampoModo") && GetPVarInt(adm, "grampoPlayer") == adm))
					{
					    format(string, sizeof string, "(( %s enviou um SMS para %s: %s ))", PlayerName[playerid], PlayerName[i], result);
					    SendClientMessage(adm, 0xDBED15FF, string);
					}
				}

				PlayerPlaySound(playerid, 3600,  0.0, 0.0, 0.0);
				PlayerPlaySound(i, 3600,  0.0, 0.0, 0.0);

				Player_RemoveMoney(playerid, PRICE_ENVIAR_SMS);
				format(string, sizeof string, "~r~ -$%d", PRICE_ENVIAR_SMS);
				GameTextForPlayer(playerid, string, 5000, 1);

				format(string, sizeof(string), "SMS: %s, enviou: %s para %s", result, PlayerName[playerid], PlayerName[i]);
				server_log("sms", string);
				return true;
			}
		}
	}
	SendClientMessage(playerid, -1, "Falha ao enviar a mensagem!");
	return true;
}

stock LoadStuff()
{
	ICMS = strval(LoadConfig("ICMS"));
	GovernoTaxa = strval(LoadConfig("TAXA_SALARIO"));
	LotValue = strval(LoadConfig("VALOR_LOTERIA"));
	BolsaFamilia[bolsaLimite] = strval(LoadConfig("VALOR_BOLSA_FAMILIA"));
	LimiteBolsaFamilia = strval(LoadConfig("LIMITE_BOLSA_FAMILIA"));
	BolsaFamiliaDiario = strval(LoadConfig("BOLSA_FAMILIA_DIARIO"));
	CofreAdmin = strval(LoadConfig("COFRE_ADMIN"));
	CofreEvento = strval(LoadConfig("COFRE_EVENTO"));
	Cash_SetPromo(strval(LoadConfig("PROMOCAO_ATIVA")));

	propinaMateriais = strval(LoadConfig("PROPINA_MATERIAIS"));

	// Salários
	WageJob[wageJob][ID_JOB_LIXEIRO] = strval(LoadConfig("SALARIO_LIXEIRO"));
	WageJob[wageJob][ID_JOB_MEDICO] = strval(LoadConfig("SALARIO_MEDICO"));
	WageJob[wageJob][ID_JOB_MECANICO] = strval(LoadConfig("SALARIO_MECANICO"));
	WageJob[wageJob][ID_JOB_FAZENDEIRO] = strval(LoadConfig("SALARIO_FAZENDEIRO"));
	WageJob[wageJob][ID_JOB_CAMINHONEIRO] = strval(LoadConfig("SALARIO_CAMINHONEIRO"));
	WageJob[wageJob][ID_JOB_FIREFIGHTER] = strval(LoadConfig("SALARIO_FIREFIGHTER"));

	return 1;
}

stock SaveStuff()
{
	SaveConfigInt("ICMS", ICMS);
	SaveConfigInt("PROMOCAO_ATIVA", Cash_GetPromo());
	SaveConfigInt("TAXA_SALARIO", GovernoTaxa);
	SaveConfigInt("VALOR_LOTERIA", LotValue);
	SaveConfigInt("VALOR_BOLSA_FAMILIA", BolsaFamilia[bolsaLimite]);
	SaveConfigInt("PROPINA_MATERIAIS", propinaMateriais);
	
	SaveConfigInt("COFRE_ADMIN", CofreAdmin);
	SaveConfigInt("COFRE_EVENTO", CofreEvento);

	SaveConfigInt("SALARIO_LIXEIRO", WageJob[wageJob][ID_JOB_LIXEIRO]);
	SaveConfigInt("SALARIO_MEDICO", WageJob[wageJob][ID_JOB_MEDICO]);
	SaveConfigInt("SALARIO_FAZENDEIRO", WageJob[wageJob][ID_JOB_FAZENDEIRO]);
	SaveConfigInt("SALARIO_CAMINHONEIRO", WageJob[wageJob][ID_JOB_CAMINHONEIRO]);
	SaveConfigInt("SALARIO_FIREFIGHTER", WageJob[wageJob][ID_JOB_FIREFIGHTER]);

	return 1;
}

CALLBACK:IsAtGasStation(playerid)
{
    if (IsPlayerConnected(playerid))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		new VIM:vim = Vehicle_GetVIM(vehicleid);

	    if (PlayerToPoint(15.0,playerid,1941.9850,-1774.6639,19.7006))
			if (VIM_IsPlane(vim)) return true;

		if (PlayerToPoint(15.0, playerid, 1004.0070, -939.3102, 42.1797) 		 // Posto de Temple
		|| PlayerToPoint(15.0, playerid, 1944.3260, -1772.9254, 13.3906)      // Posto de Idlewood
		|| PlayerToPoint(15.0, playerid, -90.5515, -1169.4578, 2.4079)        // Posto da Flint County
		|| PlayerToPoint(15.0, playerid, -1609.7958, -2718.2048, 48.5391)     // Posto de Whetstone
		|| PlayerToPoint(15.0, playerid, 654.9639, -570.4174, 16.5015)        // Posto de Dillimore (Bomba 1)
		|| PlayerToPoint(15.0, playerid, 654.9691, -559.7495, 16.5015)        // Posto de Dillimore (Bomba 2)
		|| PlayerToPoint(15.0, playerid, 2478.2307, 61.1110, 26.5184)         // Posto de Palomino Creek
		|| PlayerToPoint(15.0, playerid, -2408.7590, 976.0934, 45.4175)       // Posto de Juniper Hollow
		|| PlayerToPoint(15.0, playerid, 1380.4712, 462.7467, 20.1107)        // Posto de Montgomery (Bomba 1)
		|| PlayerToPoint(15.0, playerid, 1385.0475, 460.5417, 20.1068)        // Posto de Montgomery (Bomba 2)
		|| PlayerToPoint(15.0, playerid, -2243.9629, -2560.6477, 31.8841)     // Posto de Angel Pine
		|| PlayerToPoint(15.0, playerid, -1676.6323, 414.0262, 6.9484) 		 // Posto de Easter Basin
		|| PlayerToPoint(15.0, playerid, 2202.2349, 2474.3494, 10.5258)		 // Posto de A ilha esmeralda
		|| PlayerToPoint(15.0, playerid, 614.9333, 1689.7418, 6.6968)        // Posto de Bone County
		|| PlayerToPoint(15.0, playerid, -1328.8250, 2677.2173, 49.7665)	 	// Posto de Tierra Robada
		|| PlayerToPoint(15.0, playerid, 2933.03857, -1996.06421, 11.41720))	 // Posto HQ BOPE
		    return true;
	}
	return false;
}

stock CreateTextDraws(playerid)
{
	textCBug[playerid] = CreatePlayerTextDraw(playerid,143.000000, 328.000000, "CBUG: 0 ms~n~Balas: 0/7");
	PlayerTextDrawBackgroundColor(playerid,textCBug[playerid], 0);
	PlayerTextDrawFont(playerid,textCBug[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textCBug[playerid], 0.260000, 1.099998);
	PlayerTextDrawColor(playerid,textCBug[playerid], -156);
	PlayerTextDrawSetOutline(playerid,textCBug[playerid], 0);
	PlayerTextDrawSetProportional(playerid,textCBug[playerid], true);
	PlayerTextDrawSetShadow(playerid,textCBug[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textCBug[playerid], false);

	TextHospital[playerid] = CreatePlayerTextDraw(playerid, 10.000000, 240.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, TextHospital[playerid], 50);
	PlayerTextDrawFont(playerid, TextHospital[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, TextHospital[playerid], 0.240000, 1.200000);
	PlayerTextDrawColor(playerid, TextHospital[playerid], -1);
	PlayerTextDrawSetOutline(playerid, TextHospital[playerid], true);
	PlayerTextDrawSetProportional(playerid, TextHospital[playerid], true);

	spectadorText[playerid] = CreatePlayerTextDraw(playerid, 5.666686, 143.955657, "_");
	PlayerTextDrawLetterSize(playerid, spectadorText[playerid], 0.193666, 1.156147);
	PlayerTextDrawTextSize(playerid, spectadorText[playerid], 86.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, spectadorText[playerid], TEXT_DRAW_ALIGN_LEFT);
	PlayerTextDrawColor(playerid, spectadorText[playerid], -1);
	PlayerTextDrawUseBox(playerid, spectadorText[playerid], true);
	PlayerTextDrawBoxColor(playerid, spectadorText[playerid], 102);
	PlayerTextDrawSetShadow(playerid, spectadorText[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, spectadorText[playerid], 255);
	PlayerTextDrawFont(playerid, spectadorText[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawSetProportional(playerid, spectadorText[playerid], true);

	playerTradeText[playerid][0] = CreatePlayerTextDraw(playerid,201.000000, 373.000000, "ld_dual:white");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][0], 255);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][0], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][0], 336860415);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][0], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][0], 1);
	PlayerTextDrawUseBox(playerid,playerTradeText[playerid][0], true);
	PlayerTextDrawBoxColor(playerid,playerTradeText[playerid][0], 255);
	PlayerTextDrawTextSize(playerid,playerTradeText[playerid][0], 70.000000, 20.000000);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][0], true);

	playerTradeText[playerid][1] = CreatePlayerTextDraw(playerid,235.000000, 378.000000, "PRONTO");
	PlayerTextDrawAlignment(playerid,playerTradeText[playerid][1], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][1], 0);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][1], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][1], 0.209999, 1.099998);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][1], 842150655);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][1], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][1], false);

	playerTradeText[playerid][2] = CreatePlayerTextDraw(playerid,355.000000, 373.000000, "ld_dual:white");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][2], 255);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][2], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][2], 505290495);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][2], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][2], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][2], 1);
	PlayerTextDrawUseBox(playerid,playerTradeText[playerid][2], true);
	PlayerTextDrawBoxColor(playerid,playerTradeText[playerid][2], 255);
	PlayerTextDrawTextSize(playerid,playerTradeText[playerid][2], 70.000000, 20.000000);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][2], false);

	playerTradeText[playerid][3] = CreatePlayerTextDraw(playerid,389.000000, 378.000000, "Adicionando...");
	PlayerTextDrawAlignment(playerid,playerTradeText[playerid][3], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][3], 0);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][3], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][3], 0.209999, 1.099998);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][3], -106);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][3], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][3], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][3], false);

	playerTradeText[playerid][4] = CreatePlayerTextDraw(playerid,391.000000, 364.000000, "=");
	PlayerTextDrawAlignment(playerid,playerTradeText[playerid][4], TEXT_DRAW_ALIGN_CENTER);
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][4], 0);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][4], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][4], 0.149998, 0.899999);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][4], -236);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][4], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][4], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][4], false);

	playerTradeText[playerid][5] = CreatePlayerTextDraw(playerid,164.000000, 170.000000, "model");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][5], 336860415);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][5], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][5], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][5], -1);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][5], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][5], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][5], 1);
	PlayerTextDrawUseBox(playerid,playerTradeText[playerid][5], true);
	PlayerTextDrawBoxColor(playerid,playerTradeText[playerid][5], 0);
	PlayerTextDrawTextSize(playerid,playerTradeText[playerid][5], 72.000000, 89.000000);
	PlayerTextDrawSetPreviewModel(playerid, playerTradeText[playerid][5], 19300);
	PlayerTextDrawSetPreviewRot(playerid, playerTradeText[playerid][5], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][5], false);

	playerTradeText[playerid][6] = CreatePlayerTextDraw(playerid,238.000000, 170.000000, "model");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][6], 336860415);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][6], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][6], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][6], -1);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][6], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][6], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][6], 1);
	PlayerTextDrawUseBox(playerid,playerTradeText[playerid][6], true);
	PlayerTextDrawBoxColor(playerid,playerTradeText[playerid][6], 0);
	PlayerTextDrawTextSize(playerid,playerTradeText[playerid][6], 72.000000, 89.000000);
	PlayerTextDrawSetPreviewModel(playerid, playerTradeText[playerid][6], 19300);
	PlayerTextDrawSetPreviewRot(playerid, playerTradeText[playerid][6], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][6], false);

	playerTradeText[playerid][7] = CreatePlayerTextDraw(playerid,164.000000, 261.000000, "model");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][7], 336860415);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][7], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][7], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][7], -1);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][7], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][7], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][7], 1);
	PlayerTextDrawUseBox(playerid,playerTradeText[playerid][7], true);
	PlayerTextDrawBoxColor(playerid,playerTradeText[playerid][7], 0);
	PlayerTextDrawTextSize(playerid,playerTradeText[playerid][7], 72.000000, 89.000000);
	PlayerTextDrawSetPreviewModel(playerid, playerTradeText[playerid][7], 19300);
	PlayerTextDrawSetPreviewRot(playerid, playerTradeText[playerid][7], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][7], false);

	playerTradeText[playerid][8] = CreatePlayerTextDraw(playerid,238.000000, 261.000000, "model");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][8], 336860415);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][8], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][8], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][8], -1);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][8], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][8], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][8], 1);
	PlayerTextDrawUseBox(playerid,playerTradeText[playerid][8], true);
	PlayerTextDrawBoxColor(playerid,playerTradeText[playerid][8], 0);
	PlayerTextDrawTextSize(playerid,playerTradeText[playerid][8], 72.000000, 89.000000);
	PlayerTextDrawSetPreviewModel(playerid, playerTradeText[playerid][8], 19300);
	PlayerTextDrawSetPreviewRot(playerid, playerTradeText[playerid][8], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][8], false);

	playerTradeText[playerid][9] = CreatePlayerTextDraw(playerid,324.000000, 170.000000, "pmodel");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][9], 336860415);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][9], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][9], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][9], -1);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][9], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][9], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][9], 1);
	PlayerTextDrawUseBox(playerid,playerTradeText[playerid][9], true);
	PlayerTextDrawBoxColor(playerid,playerTradeText[playerid][9], 0);
	PlayerTextDrawTextSize(playerid,playerTradeText[playerid][9], 72.000000, 89.000000);
	PlayerTextDrawSetPreviewModel(playerid, playerTradeText[playerid][9], 19300);
	PlayerTextDrawSetPreviewRot(playerid, playerTradeText[playerid][9], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][9], false);

	playerTradeText[playerid][10] = CreatePlayerTextDraw(playerid,398.000000, 170.000000, "pmodel");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][10], 336860415);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][10], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][10], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][10], -1);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][10], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][10], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][10], 1);
	PlayerTextDrawUseBox(playerid,playerTradeText[playerid][10], true);
	PlayerTextDrawBoxColor(playerid,playerTradeText[playerid][10], 0);
	PlayerTextDrawTextSize(playerid,playerTradeText[playerid][10], 72.000000, 89.000000);
	PlayerTextDrawSetPreviewModel(playerid, playerTradeText[playerid][10], 19300);
	PlayerTextDrawSetPreviewRot(playerid, playerTradeText[playerid][10], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][10], false);

	playerTradeText[playerid][11] = CreatePlayerTextDraw(playerid,324.000000, 261.000000, "pmodel");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][11], 336860415);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][11], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][11], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][11], -1);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][11], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][11], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][11], 1);
	PlayerTextDrawUseBox(playerid,playerTradeText[playerid][11], true);
	PlayerTextDrawBoxColor(playerid,playerTradeText[playerid][11], 0);
	PlayerTextDrawTextSize(playerid,playerTradeText[playerid][11], 72.000000, 89.000000);
	PlayerTextDrawSetPreviewModel(playerid, playerTradeText[playerid][11], 19300);
	PlayerTextDrawSetPreviewRot(playerid, playerTradeText[playerid][11], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][11], false);

	playerTradeText[playerid][12] = CreatePlayerTextDraw(playerid,398.000000, 261.000000, "pmodel");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][12], 336860415);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][12], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][12], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][12], -1);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][12], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][12], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][12], 1);
	PlayerTextDrawUseBox(playerid,playerTradeText[playerid][12], true);
	PlayerTextDrawBoxColor(playerid,playerTradeText[playerid][12], 0);
	PlayerTextDrawTextSize(playerid,playerTradeText[playerid][12], 72.000000, 89.000000);
	PlayerTextDrawSetPreviewModel(playerid, playerTradeText[playerid][12], 19300);
	PlayerTextDrawSetPreviewRot(playerid, playerTradeText[playerid][12], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][12], false);

	playerTradeText[playerid][13] = CreatePlayerTextDraw(playerid,166.000000, 249.000000, "Item nome 1~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~Item nome 3");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][13], 0);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][13], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][13], 0.149997, 0.919999);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][13], -206);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][13], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][13], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][13], 1);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][13], false);

	playerTradeText[playerid][14] = CreatePlayerTextDraw(playerid,240.000000, 249.000000, "Item nome 2~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~Item nome 4");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][14], 0);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][14], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][14], 0.149997, 0.919999);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][14], -206);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][14], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][14], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][14], 1);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][14], false);

	playerTradeText[playerid][15] = CreatePlayerTextDraw(playerid,325.000000, 249.000000, "Item nome 1~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~Item nome 3");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][15], 0);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][15], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][15], 0.149997, 0.919999);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][15], -206);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][15], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][15], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][15], 1);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][15], false);

	playerTradeText[playerid][16] = CreatePlayerTextDraw(playerid,400.000000, 249.000000, "Item nome 2~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~Item nome 4");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][16], 0);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][16], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][16], 0.149997, 0.919999);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][16], -206);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][16], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][16], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][16], 1);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][16], false);

	playerTradeText[playerid][17] = CreatePlayerTextDraw(playerid,161.000000, 158.000000, "$5.733.742 / Cash 1.453 / Ouros 2.521");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][17], 0);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][17], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][17], 0.149998, 0.899999);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][17], -206);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][17], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][17], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][17], 1);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][17], false);

	playerTradeText[playerid][18] = CreatePlayerTextDraw(playerid,321.000000, 158.000000, "$5.733.742 / Cash 1.453 / Ouros 2.521");
	PlayerTextDrawBackgroundColor(playerid,playerTradeText[playerid][18], 0);
	PlayerTextDrawFont(playerid,playerTradeText[playerid][18], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid,playerTradeText[playerid][18], 0.149998, 0.899999);
	PlayerTextDrawColor(playerid,playerTradeText[playerid][18], -206);
	PlayerTextDrawSetOutline(playerid,playerTradeText[playerid][18], 0);
	PlayerTextDrawSetProportional(playerid,playerTradeText[playerid][18], true);
	PlayerTextDrawSetShadow(playerid,playerTradeText[playerid][18], 1);
	PlayerTextDrawSetSelectable(playerid,playerTradeText[playerid][18], false);

//Info damage
	textPlayerDamaged[0][playerid] = CreatePlayerTextDraw(playerid,415.000000, 385.000000, "dano de ---~n~----~n~");
	PlayerTextDrawAlignment(playerid,textPlayerDamaged[0][playerid], TEXT_DRAW_ALIGN_RIGHT);
	PlayerTextDrawBackgroundColor(playerid,textPlayerDamaged[0][playerid], 0);
	PlayerTextDrawFont(playerid,textPlayerDamaged[0][playerid], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid,textPlayerDamaged[0][playerid], 0.159999, 0.799999);
	PlayerTextDrawColor(playerid,textPlayerDamaged[0][playerid], -12171706);
	PlayerTextDrawSetOutline(playerid,textPlayerDamaged[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerDamaged[0][playerid], true);
	PlayerTextDrawSetShadow(playerid,textPlayerDamaged[0][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textPlayerDamaged[0][playerid], false);

	textPlayerDamaged[1][playerid] = CreatePlayerTextDraw(playerid,417.000000, 398.000000, "+00");
	PlayerTextDrawAlignment(playerid,textPlayerDamaged[1][playerid], TEXT_DRAW_ALIGN_RIGHT);
	PlayerTextDrawBackgroundColor(playerid,textPlayerDamaged[1][playerid], 0);
	PlayerTextDrawFont(playerid,textPlayerDamaged[1][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textPlayerDamaged[1][playerid], 0.270000, 1.099999);
	PlayerTextDrawColor(playerid,textPlayerDamaged[1][playerid], -16776961);
	PlayerTextDrawSetOutline(playerid,textPlayerDamaged[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerDamaged[1][playerid], true);
	PlayerTextDrawSetShadow(playerid,textPlayerDamaged[1][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textPlayerDamaged[1][playerid], false);

	textPlayerDamager[0][playerid] = CreatePlayerTextDraw(playerid,166.000000, 385.000000, "dano em ---~n~----~n~");
	PlayerTextDrawBackgroundColor(playerid,textPlayerDamager[0][playerid], 0);
	PlayerTextDrawFont(playerid,textPlayerDamager[0][playerid], TEXT_DRAW_FONT_2);
	PlayerTextDrawLetterSize(playerid,textPlayerDamager[0][playerid], 0.159999, 0.799999);
	PlayerTextDrawColor(playerid,textPlayerDamager[0][playerid], -196);
	PlayerTextDrawSetOutline(playerid,textPlayerDamager[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerDamager[0][playerid], true);
	PlayerTextDrawSetShadow(playerid,textPlayerDamager[0][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textPlayerDamager[0][playerid], false);

	textPlayerDamager[1][playerid] = CreatePlayerTextDraw(playerid,166.000000, 398.000000, "+00");
	PlayerTextDrawBackgroundColor(playerid,textPlayerDamager[1][playerid], 0);
	PlayerTextDrawFont(playerid,textPlayerDamager[1][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textPlayerDamager[1][playerid], 0.420000, 1.699999);
	PlayerTextDrawColor(playerid,textPlayerDamager[1][playerid], -1);
	PlayerTextDrawSetOutline(playerid,textPlayerDamager[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerDamager[1][playerid], true);
	PlayerTextDrawSetShadow(playerid,textPlayerDamager[1][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textPlayerDamager[1][playerid], false);
//

	CreatePlayerTextDrawInvasion(playerid);
	CreatePlayerTextDrawTraining(playerid);

	// corrida
	racePosicao[playerid] = CreatePlayerTextDraw(playerid,523.000000, 52.000000+30.0, "0|");
	PlayerTextDrawBackgroundColor(playerid,racePosicao[playerid], 0);
	PlayerTextDrawFont(playerid,racePosicao[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,racePosicao[playerid], 0.620000, 2.299999);
	PlayerTextDrawColor(playerid,racePosicao[playerid], -1258320641);
	PlayerTextDrawSetOutline(playerid,racePosicao[playerid], 1);
	PlayerTextDrawSetProportional(playerid,racePosicao[playerid], true);
	PlayerTextDrawSetSelectable(playerid,racePosicao[playerid], false);

	textGanhou1[playerid] = CreatePlayerTextDraw(playerid,-9.000000, -1.000000, "_");
	PlayerTextDrawBackgroundColor(playerid,textGanhou1[playerid], 255);
	PlayerTextDrawFont(playerid,textGanhou1[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textGanhou1[playerid], 0.500000, 53.000000);
	PlayerTextDrawColor(playerid,textGanhou1[playerid], -1);
	PlayerTextDrawSetOutline(playerid,textGanhou1[playerid], 0);
	PlayerTextDrawSetProportional(playerid,textGanhou1[playerid], true);
	PlayerTextDrawSetShadow(playerid,textGanhou1[playerid], 1);
	PlayerTextDrawUseBox(playerid,textGanhou1[playerid], true);
	PlayerTextDrawBoxColor(playerid,textGanhou1[playerid], 40);
	PlayerTextDrawTextSize(playerid,textGanhou1[playerid], 650.000000, 0.000000);
	PlayerTextDrawSetSelectable(playerid,textGanhou1[playerid], false);

	textGanhou2[playerid] = CreatePlayerTextDraw(playerid,210.000000, 140.000000, "     Ganhou!~n~Tempo:      2:58");
	PlayerTextDrawBackgroundColor(playerid,textGanhou2[playerid], 0);
	PlayerTextDrawFont(playerid,textGanhou2[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textGanhou2[playerid], 0.709999, 3.099999);
	PlayerTextDrawColor(playerid,textGanhou2[playerid], -1);
	PlayerTextDrawSetOutline(playerid,textGanhou2[playerid], 0);
	PlayerTextDrawSetProportional(playerid,textGanhou2[playerid], true);
	PlayerTextDrawSetShadow(playerid,textGanhou2[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textGanhou2[playerid], false);

	textPremioXP[playerid] = CreatePlayerTextDraw(playerid,127.000000, 206.000000, "Pontos de reputacao ganho:~w~~h~                      000");
	PlayerTextDrawBackgroundColor(playerid,textPremioXP[playerid], 0);
	PlayerTextDrawFont(playerid,textPremioXP[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textPremioXP[playerid], 0.389999, 2.000000);
	PlayerTextDrawColor(playerid,textPremioXP[playerid], -1258320641);
	PlayerTextDrawSetOutline(playerid,textPremioXP[playerid], 1);
	PlayerTextDrawSetProportional(playerid,textPremioXP[playerid], true);
	PlayerTextDrawSetSelectable(playerid,textPremioXP[playerid], false);

	textPremioGrana[playerid] = CreatePlayerTextDraw(playerid,127.000000, 264.000000, "Dinheiro ganho:~w~~h~                                    000");
	PlayerTextDrawBackgroundColor(playerid,textPremioGrana[playerid], 0);
	PlayerTextDrawFont(playerid,textPremioGrana[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textPremioGrana[playerid], 0.389999, 2.000000);
	PlayerTextDrawColor(playerid,textPremioGrana[playerid], -1258320641);
	PlayerTextDrawSetOutline(playerid,textPremioGrana[playerid], 1);
	PlayerTextDrawSetProportional(playerid,textPremioGrana[playerid], true);
	PlayerTextDrawSetSelectable(playerid,textPremioGrana[playerid], false);

	return 1;
}

UpdatePlayerData(playerid, destroy = false)
{
	if (!Player_Logado(playerid)) 
		return 1;

	// orm_save sends an UPDATE query
	if(ORM_IsValid(PlayerInfo[playerid][ORM_ID], "player", PlayerName[playerid]))
	{
		if (GetPVarInt(playerid, "varAdmin") > 0)
			Admin_SetNivel(playerid, AdminNivel:GetPVarInt(playerid, "varAdmin"));

		orm_save(PlayerInfo[playerid][ORM_ID]);
		if(destroy)
			orm_destroy(PlayerInfo[playerid][ORM_ID]);
	}
	return 1;
}

SavePlayerAccount(playerid, destroy = false) {
	if (!Player_Logado(playerid)) 
		return 1;

	saveLastPlayerPos(playerid);
	SaveLastWeapons(playerid);
	UpdatePlayerData(playerid, destroy);
	Player_SaveAllVehicles(playerid);
	return 1;
}

UpdatePlayerInfos(playerid) {
	return UpdatePlayerData(playerid, false);
}

stock DestroyPlayerMemory(playerid)
{
	// Removendo dos loops
	Iter_Remove(IterSurvival, playerid);
	Iter_Remove(IterSubsHouse, playerid);

	// Deletando objetos visíveis para o player
    DestroyDynamicObject(GetPVarInt(playerid, "objectExplosao"));

	if(GetPVarInt(playerid, "servicoMedico"))
		DestroyDynamicActor(GetPVarInt(playerid, "actorMedico"));

	// Deletando veículos e limpando variáveis
    CancelPlayerDrone(playerid);
	DestroyPlayerCaminhao(playerid);

	// Encerrando os processos Timer
	stop cancel_caminhao_timer[playerid];
	stop timer_procurar[playerid];
	stop TimerMedico[playerid];

	// Sistema de prisão ativo
	#if defined _JAIL_SYSTEM_ON
		stop JailInfo[server_exploding_jail][playerid];
	#endif
}

CMD:ba(playerid, result[])
{
	if (isnull(result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /ba (texto, para falar sussurrando)");

	new string[128];
	format(string, sizeof(string), "%s(%d) sussurra: %s", PlayerName[playerid], playerid, result);

	#if defined _CENSORED_protection
		censored_word_detected(string);
	#endif

	SendClientMessageInRange(3.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

	return true;
}

CMD:g(playerid, result[])
{
	if (!Player_Logado(playerid)) return SendClientMessage(playerid, -1, "Erro: Você ainda não logou no servidor.");
	if(isnull(result))
	{
		SendClientMessage(playerid, -1, "Modo de usar: {FFA54F}(/g)ritar {FFFFFF}[{FFA54F}texto{FFFFFF}]");
		return true;
	}
	new string[128];
	format(string,sizeof(string),"%s(%d) grita: ¡%s!", PlayerName[playerid], playerid, result);

	#if defined _CENSORED_protection
		ensored_word_detected(string);
	#endif

	SendClientMessageInRange(35.0,playerid,string,-1,-1,-1,-1,-1);
	return true;
}
alias:g("gritar")

CMD:f(playerid, params[])
{
	if (!Player_Logado(playerid))
		return SendClientMessage(playerid,-1, "Você não pode usar esse comando no momento.");

	if (isnull(params)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /f (mensagem no chat)");

	new Organizacao = GetPlayerOrg(playerid);

	if (Organizacao != 8 && Organizacao != 22 && Organizacao != 9 && Organizacao != 25)
		return SendClientMessage(playerid, -1, "Você não tem permissão para usar esse comando.");

	new
		string[128]
	;

	format(string, sizeof(string), "** %s usou seu rádio comunicador **", PlayerName[playerid]);
	SendClientMessageInRange(15.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

	format(string, sizeof string, "** Rádio: %s, %s diz %s.", GetPlayerCargo(playerid), PlayerName[playerid], params);

	#if defined _CENSORED_protection
		censored_word_detected(string);
	#endif

	SendMembersMessage(Organizacao, -1, string);
	return true;
}

CMD:ga(playerid, params[])
{
	if(isnull(params))return SendClientMessage(playerid, -1, "Use: (/ga)ngue [texto]");

	new org = GetPlayerOrg(playerid);
	if(org != 5 && org != 6 && org != 14 && org != 17 && org != 18 && org != 19 && org != 20 && org != 21
		&& org != 15&& org != 23 && org != 10 && org != 13 && org != 12 && org != 24 && org != 26 && org != 27 && org != 28)
	{
		return SendClientMessage(playerid, -1, "Você não pode usar este comando");
	}
	//Anti Divulguer
	new gstring[128];
	format(gstring, sizeof(gstring), "* %s falou algo no radio.", PlayerName[playerid]);

	#if defined _CENSORED_protection
		censored_word_detected(gstring);
	#endif

	SendClientMessageInRange(20.0, playerid, gstring, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	format(gstring, sizeof gstring, "** %s %s: %s **", GetPlayerCargo(playerid), PlayerName[playerid], params);
	SendMembersMessage(org, GetPlayerColor(playerid), gstring);
	return true;
}
alias:ga("gangue")

CMD:chatkill(playerid) 
{
	if(ChatKill[playerid]) 
	{
	    ChatKill[playerid] = false;
	    SendClientMessage(playerid, -1, "Você desligou o chat kill!");
	} 
	else 
	{
	    ChatKill[playerid] = true;
	    SendClientMessage(playerid, -1, "Você ligou o chat kill!");
	}
	return 1;
}

CMD:chatnoob(playerid) 
{
	if(PlayerInfo[playerid][pChatNoob]) 
	{
	    PlayerInfo[playerid][pChatNoob] = false;
	    SendClientMessage(playerid, -1, "Você desligou o chat noob!");
	} 
	else 
	{
	    PlayerInfo[playerid][pChatNoob] = true;
	    SendClientMessage(playerid, -1, "Você ligou o chat noob!");
	}
	return 1;
}

CMD:n(playerid, params[])
{
	if (!Player_Logado(playerid)) return SendClientMessage(playerid, -1, "Você precisa estar logado.");

    if (Player_GetJailed(playerid)) return SendClientMessage(playerid, 0xFF0000AA, "Você está impedido de usar certos comandos pois está preso.");

	if (PlayerInfo[playerid][pConnectTime] < 1) return SendClientMessage(playerid, 0xFF0000AA, "Você precisa ter pelo menos 1 hora jogada para usar o chat /n");

    if (!PlayerInfo[playerid][pChatNoob]) return SendClientMessage(playerid, COLOR_LIGHTRED, " Seu chat noob está desligado, use: /chatnoob para ligar ou desligar!");

	if (NoobDesativado == 1)
		return SendClientMessage(playerid, COLOR_LIGHTRED, "O canal /noob foi desativado por um administrador!");

	if (gettime() < PlayerInfo[playerid][pToggleNoob]) {

	    new string[128];
	    format(string, sizeof (string), "Você não pode usar o canal noob durante {82E789}%s{FFFFFF}, motivo: Uso indevido", ConvertTempo(PlayerInfo[playerid][pToggleNoob] - gettime()));
		SendClientMessage(playerid, -1, string);
		return 1;
	}

	if (isnull(params))
		return SendClientMessage(playerid, -1, "Use {FFA54F}/n pergunta {FFFFFF}para obter respostas de outros jogadores");

	SetPVarString(playerid, "varNoob", params);

	format(MEGAString, sizeof MEGAString,
	"{FFFFFF}Você vai enviar um texto de dúvida no canal /n(oob).\n\n\
	{FFFFFF}Sua pergunta: {8B8A8A}%s\n\n\
	{F74242}Observação: {FFFFFF}Esse canal é apenas para tirar dúvidas sobre a GameMode...\n\
	... Caso você use indevidamente esse canal, será punido {DA4F4F}240 {FFFFFF}minutos e {115C33}$5.000 {FFFFFF}de multa\n\n",
	params);

	ShowPlayerDialog(playerid, 9274, DIALOG_STYLE_MSGBOX, "{F74242}ATENÇÃO!", MEGAString, "Enviar", "Cancelar");

	return 1;
}
alias:n("noob")

stock SendMessageChat(chat_type, playerid, const message[]) {
	
	switch (chat_type) {
		case CHAT_TYPE_NOOB: {
			new string[200];

			if (Admin_GetNivel(playerid) || Helper_GetNivel(playerid)) {
				new pmention[sizeof(string)];
				ExpandMentions(message, pmention, sizeof(pmention), 0x009999AA);

				new cargo[80];

				if(Admin_GetNivel(playerid) == DESENVOLVEDOR && Dev_GetNivel(playerid) > DEV_BETA) {
					format(cargo, sizeof(cargo), "{4169E1}%s", Staff_GetPositionName(playerid)); // {CF4913} - Cor Antiga Laranja
				}
				else if (Admin_GetNivel(playerid) == PROGRAMADOR) {
					format(cargo, sizeof(cargo), "{D2691E}%s", Staff_GetPositionName(playerid));
				}
				else if (Admin_GetNivel(playerid) == FUNDADOR) {
					format(cargo, sizeof(cargo), "{FF0000}%s", Staff_GetPositionName(playerid));
				}
				else if (Admin_GetNivel(playerid) == CO_FUNDADOR) {
					format(cargo, sizeof(cargo), "{CF4913}%s", Staff_GetPositionName(playerid));
				}
				else if (Admin_GetNivel(playerid) == DONO) {
					format(cargo, sizeof(cargo), "{00BFFF}%s", Staff_GetPositionName(playerid));
				}
				else if (Admin_GetNivel(playerid) == SUB_DONO) {
					format(cargo, sizeof(cargo), "{00FFFF}%s", Staff_GetPositionName(playerid));
				}
				else if (Admin_GetNivel(playerid) == DIRETOR) {
					format(cargo, sizeof(cargo), "{D2691E}%s", Staff_GetPositionName(playerid));
				}
				else if (Admin_GetNivel(playerid) == GERENTE) {
					format(cargo, sizeof(cargo), "{32CD32}%s", Staff_GetPositionName(playerid));
				}
				else if (Admin_GetNivel(playerid) == MASTER) {
					format(cargo, sizeof(cargo), "{9932CC}%s", Staff_GetPositionName(playerid));
				}
				else {
					format(cargo, sizeof(cargo), Staff_GetPositionName(playerid));
				}

				format(string, sizeof(string), "(Canal /n) [%s{009999}] %s (%d): %s", cargo, PlayerName[playerid], playerid, pmention);
			}
			else if(PlayerInfo[playerid][pConnectTime] >= 2000) {
				format(string, sizeof(string), "(Canal /n) [Veterano] %s (%d): %s", PlayerName[playerid], playerid, message);
			} else {
				format(string, sizeof(string), "(Canal /n) [%s] %s (%d): %s", IsAndroidPlayer(playerid) ? ("{1FBD5C}Android{009999}") : ("{6279D3}PC{009999}"), PlayerName[playerid], playerid, message);
			}

			#if defined _CENSORED_protection
				censored_word_detected(string);
			#endif

			// Envia a mensagem aos jogadores que possui a opção chat noob ativo.
			foreach(new x : Player) {
				if (PlayerInfo[x][pChatNoob]) {
					SendClientMessage(x, 0x009999AA, string);
				}
			}
		}
	}
	return 1;
}
stock SendRealChatMessage(playerid, const text[]) {
	static space_pos, string[144];
	#define max_chat_size 85

	format(string, sizeof(string), "%s(%d) diz: %s", FormatPlayerName(playerid), playerid, text);
	space_pos = strfind(string, " ", true, max_chat_size);

	if (strlen(string) > max_chat_size && space_pos != -1)
	{
		new part_2[128];
		format(part_2, sizeof (part_2), "...%s", string[space_pos + 1]);
		strdel(string, space_pos, 255);
		strcat(string, "...");
		if (Player_GetVIP(playerid) >= SOCIO_EXTREME) {
			SendClientMessageInRange(30.0, playerid, string, 0xFF8980FF, 0xDB7770FF, 0xC7756FFF, 0xAD6E6AFF, 0x9E6F6CFF);
		} else if (Player_GetVIP(playerid) >= SOCIO_SUPREME) {
			SendClientMessageInRange(30.0, playerid, string, 0x99FFFFFF, 0x99FFFFFF, 0x99FFFFFF, 0x99FFFFFF, 0x99FFFFFF);
		} else if (Admin_GetNivel(playerid) && !Staff_GetSecret(playerid)) {
			SendClientMessageInRange(30.0, playerid, string, 0x55F49AFF, 0x55F49AFF, 0x55F49AFF, 0x55F49AFF, 0x55F49AFF);
		} else if (Helper_GetNivel(playerid) && !Staff_GetSecret(playerid)) {
			SendClientMessageInRange(30.0, playerid, string, COLOR_HELPER, COLOR_HELPER, COLOR_HELPER, COLOR_HELPER, COLOR_HELPER);
		} else {
			SendClientMessageInRange(30.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		}
		log_chat(playerid, string);
		format(string, sizeof string, part_2);
	}

	if (Player_GetVIP(playerid) >= SOCIO_EXTREME) {
		SendClientMessageInRange(30.0, playerid, string, 0xFF8980FF, 0xDB7770FF, 0xC7756FFF, 0xAD6E6AFF, 0x9E6F6CFF);
		SetPlayerChatBubble(playerid, text, 0xFF8980FF, 30.0, 10000);
	} else if (Player_GetVIP(playerid) >= SOCIO_SUPREME) {
		SendClientMessageInRange(30.0, playerid, string, 0x99FFFFFF, 0x99FFFFFF, 0x99FFFFFF, 0x99FFFFFF, 0x99FFFFFF);
		SetPlayerChatBubble(playerid, text, 0x99FFFFFF, 30.0, 10000);
	} else if (Admin_GetNivel(playerid) && !Staff_GetSecret(playerid)) {
		SendClientMessageInRange(30.0, playerid, string, 0x55F49AFF, 0x55F49AFF, 0x55F49AFF, 0x55F49AFF, 0x55F49AFF);
		SetPlayerChatBubble(playerid, text, 0x55F49AFF, 30.0, 10000);
	} else if (Helper_GetNivel(playerid) && !Staff_GetSecret(playerid)) {
		SendClientMessageInRange(30.0, playerid, string, COLOR_HELPER, COLOR_HELPER, COLOR_HELPER, COLOR_HELPER, COLOR_HELPER);
		SetPlayerChatBubble(playerid, text, COLOR_HELPER, 30.0, 10000);
	} else {
		SendClientMessageInRange(30.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		SetPlayerChatBubble(playerid, text, COLOR_FADE1, 30.0, 10000);
	}
	log_chat(playerid, string);
}
