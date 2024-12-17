CMD:explosivos(playerid)
{
	new string[40];
	format(string, sizeof string, "*** Você tem %d explosivos.", PlayerInfo[playerid][pExplosives]);
	SendClientMessage(playerid, COLOR_GRAD, string);
	return 1;
}

CMD:exploguardar(playerid, params[]) return callcmd::explosivo(playerid, "guardar");
CMD:explosivo(playerid, const params[]){

	if(IsPlayerCuffed(playerid))
		return SendClientMessage(playerid, -1, "Você não pode usar este comando agora !");

	if(GetPVarInt(playerid, "movelRoubou") || GetPVarInt(playerid, "player_exploding_jail") || GetPVarInt(playerid, "ExplodindoCofre"))
		return SendClientMessage(playerid, -1, "Você não pode usar este comando agora !");

	if(sscanf(params, "s[128]", params)){
		SendClientMessage(playerid, -1, "Use: /explosivo [nome]");
		SendClientMessage(playerid, COLOR_GRAD, "NOMES: pegar | guardar | largar | guardarmochila | plantar | detonar | pegarbomba | desarmar");
		SendClientMessage(playerid, COLOR_GRAD, "____________________________________________________________________________________________");
		return 1;
	}

	new string[128];

	if(!strcmp(params, "pegar", true)){

		if(PlayerInfo[playerid][pExplosives] > 0)
		{
			if (GetPlayerHoldingExplosive(playerid))
				return SendClientMessage(playerid, -1, "Você já está segurando um explosivo. (Use: /explosivo guardar)");

			SetPlayerExplosive(playerid, true);

			SetPlayerAttachedObject(playerid,Slot_Explosivo,1654,6,0.141000,0.043999,-0.138999,-26.300012,-4.300000,109.700019,1.264000,1.130999,1.000000);
			format(string, sizeof string, "* %s pegou seu explosivo.", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			SendClientMessage(playerid, COLOR_GRAD, "*** Você pegou o explosivo, para guardar use: /explosivo guardar.");
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
		}
		else
			SendClientMessage(playerid, -1, "Você não tem um explosivo, compre um no mercado negro ou cheque sua mochila.");
	}
	else if(!strcmp(params, "guardar", true)){

		if(PlayerInfo[playerid][pExplosives] > 0)
		{
			if(!GetPlayerHoldingExplosive(playerid))
				return SendClientMessage(playerid, -1, "Você não está segurando um explosivo.");

			SetPlayerExplosive(playerid, false);

			RemovePlayerAttachedObject(playerid, Slot_Explosivo);
			format(string, sizeof string, "* %s guardou seu explosivo.", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			SendClientMessage(playerid, COLOR_GRAD, "*** Você guardou o explosivo, para pegar use: /explosivo pegar.");
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		}
		else SendClientMessage(playerid, -1, "Você não tem um explosivo, compre um no mercado negro.");
	}
	else if(!strcmp(params, "largar", true)){

		if(gettime() < GetPVarInt(playerid, #VarFlood17))
			return SendClientMessage(playerid, COLOR_GRAD, #Você não pode usar este comando com tanta frequencia);
		SetPVarInt(playerid, #VarFlood17, gettime()+5);

		if(PlayerInfo[playerid][pExplosives]){

			dropItem(playerid, ITEM_TYPE_EXPLOSIVO, 1654, 1, "Explosivo");

			SetPlayerExplosive(playerid, false);

			PlayerInfo[playerid][pExplosives] = 0;

			RemovePlayerAttachedObject(playerid, Slot_Explosivo);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

			SendClientMessage(playerid, 0x33AA3300, "Você largou um(a) Explosivo.");

			format(string, sizeof(string), "*%s colocou um(a) Explosivo no chão.", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		}
		else SendClientMessage(playerid, -1, "Você não tem um explosivo, compre um no mercado negro ou cheque sua mochila!");
	}
	else if(!strcmp(params, "guardarmochila", true)){

		if(PlayerInfo[playerid][pExplosives] > 0)
		{
			if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

			givePlayerItem(playerid, ITEM_TYPE_EXPLOSIVO, 1654, 1, "Explosivo");

			SetPlayerExplosive(playerid, false);

			PlayerInfo[playerid][pExplosives] = 0;
			RemovePlayerAttachedObject(playerid, Slot_Explosivo);
			format(string, sizeof string, "* %s guardou um explosivo na mochila.", PlayerName[playerid]);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			SendClientMessage(playerid, COLOR_GRAD, "*** Você guardou o explosivo em sua mochila, para pegar use: /inventario.");
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		}
		else SendClientMessage(playerid, -1, "Você não tem um explosivo, compre um no mercado negro.");
	}
	else if(!strcmp(params, "plantar", true))
	{
		if (PlayerInfo[playerid][pExplosives] < 1) return SendClientMessage(playerid, -1, "Você não possui um explosivo, compre um no Mercado Negro.");

		if (GetPVarInt(playerid, "VarBomba")) return SendClientMessage(playerid, -1, "Você já plantou uma bomba, use /explosivo detonar.");

		if (IsPlayerInSafeZone(playerid)) 
			return SendClientMessage(playerid, -1, "Você não pode fazer isso em uma Área Segura.");

		if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0)
			return SendClientMessage(playerid, -1, "Você não pode plantar uma bomba estando em veículo ou em interior.");

		if (!GetPlayerHoldingExplosive(playerid)) 
			return SendClientMessage(playerid, -1, "Você não está segurando um explosivo. (Use: /explosivo pegar)");

		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);

		SetPVarInt(playerid, "VarObject",       CreateDynamicObject(1654, x, y, z-0.9, -90.0, 0.0, random(360)));
		SetPVarInt(playerid, "VarBomba", 				1);
		
		PlayerInfo[playerid][pExplosives]       = 0;

		ApplyAnimation(playerid, "BOMBER", "BOM_Plant_2Idle", 4.1, false, true, true, false, 0);

		SetPlayerExplosive(playerid, false);
		RemovePlayerAttachedObject(playerid, Slot_Explosivo);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

		SendClientMessage(playerid, -1, "*Você plantou uma bomba aqui, afaste-se e digite /explosivo detonar para detona-la!");

		format(string, sizeof(string), "*[BOMBA]: %s plantou uma bomba.", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		new nextGatePrision1 = IsPlayerInRangeOfPoint(playerid, 3.0, 1823.78, -1537.98, 13.54),
			nextGatePrision2 = IsPlayerInRangeOfPoint(playerid, 3.0, 1754.27, -1592.18, 13.54);

		if(nextGatePrision1 || nextGatePrision2) {
			SetPVarInt(playerid, "VarExplosivePlace", nextGatePrision1 ? 1 : 2);
			ShowPlayerBaloonInfo(playerid, "Voce plantou uma bomba nos portoes da prisao. Detone para tentar arromba-los!", 5000);
		}
	}
	else if(!strcmp(params, "detonar", true))
	{
		if (!GetPVarInt(playerid, "VarBomba")) return SendClientMessage(playerid, -1, "Você não plantou nenhuma bomba.");

		new objectid = GetPVarInt(playerid, "VarObject");
		new Float:x, Float:y, Float:z;
		GetDynamicObjectPos(objectid, x, y, z);

		SetPVarInt(playerid, "VarBomba", 		0);

		DestroyDynamicObject(objectid);

		new place = GetPVarInt(playerid, "VarExplosivePlace");
		if(place == 1 || place == 2) {
			CreateExplosion(x, y, z, 10, 5.0);

			new bool:open = random(10) < 7, bool:notifyCops;

			if(place == 1) {
				notifyCops = !PrisonCamerasInfo[0][cameraDestroyed];
			}
			else {
				notifyCops = !PrisonCamerasInfo[5][cameraDestroyed] || !PrisonCamerasInfo[6][cameraDestroyed];
			}

			if(open) {
				if(place == 1) {
					MoveObject(PortaoLaSante[0], 1824.318481, -1534.731201, 14.296878 + 0.01, 0.0095, 0, 0, 258);
					MoveObject(PortaoLaSante[1], 1822.407592, -1540.949951, 14.296878 + 0.01, 0.0095, 0, 0, 253);
					PortaoEsquerdaLS = GATES_OPENING;
				}
				else {
					MoveObject(PortaoLaSante[2], 1752.004150, -1591.186523, 14.267195 + 0.01, 0.0095, 0, 0, 172);
					MoveObject(PortaoLaSante[3], 1756.914062, -1592.316284, 14.267195 + 0.01, 0.0095, 0, 0, 187);
					PortaoDireitaLS = GATES_OPENING;
				}
			}

			if(notifyCops) {
				format(string, sizeof string, "[BOMBA]: %s acaba de detonar uma bomba em um dos portões da prisão.", PlayerName[playerid]);
				SendCopMessage(COLOR_LIGHTRED, string);

				SetPlayerCriminal(playerid, 255, "Vandalismo");
        		ShowPlayerBaloonInfo(playerid, "As cameras flagraram seu ato de vandalismo e todos os policiais foram notificados, cuidado!", 5000);
			}
		}
		else {
			new isTerror = PlayerIsTerror(playerid);

			CreateExplosion(x, y, z, 10, 80.0);
			CreateExplosion(x+10.0, y+10.0, z, 10, 80.0);
			CreateExplosion(x-10.0, y-10.0, z, 10, 80.0);
			if(isTerror) {
				CreateExplosion(x+10.0, y-10.0, z, 10, 80.0);
				CreateExplosion(x-108.0, y+10.0, z, 10, 80.0);
				CreateExplosion(x, y, z+10.0, 10, 80.0);
			}

			AddFire(x, y, z + 0.9);
			AddFire(x, y + 1, z + 0.9);
			AddFire(x, y - 2, z + 0.9);

			if(isTerror) {
				AddFire(x + 2, y, z + 0.9);
				AddFire(x - 2, y, z + 0.9);
			}

			if(isTerror) {
				foreach(new i : Player)
				{
					if(IsPlayerInRangeOfPoint(i, 30.0, x, y, z) && GetPlayerState(i) != PLAYER_STATE_SPECTATING)
					{
						SetPlayerHealth(i, 0.0);
					}
				}
			}

			new MapZone:zone = GetMapZoneAtPoint2D(x, y);
			new zone_name[MAX_MAP_ZONE_NAME];
			GetMapZoneName(zone, zone_name);

			format(string, sizeof string, "[BOMBA]: %s acaba de detonar uma bomba próxima a: %s.", PlayerName[playerid], zone_name);
			SendClientMessageToAll(COLOR_DBLUE, string);
		}

		CheckConquista(playerid, Conquista_Explosao);

		format(string, sizeof string, "* %s detonou seu explosivo.", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	}
	else if(!strcmp(params, "pegarbomba", true)){

		if(GetPVarInt(playerid, "VarBomba"))
		{
			new objectid = GetPVarInt(playerid, "VarObject");
			new Float:x, Float:y, Float:z;
			GetDynamicObjectPos(objectid, x, y, z);
			if(IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z))
			{
				DestroyDynamicObject(objectid);
				SetPVarInt(playerid, "VarBomba", 0);

				SendClientMessage(playerid, -1, "*Você pegou sua bomba!");

				PlayerInfo[playerid][pExplosives] = 1;

				SetPlayerAttachedObject(playerid,Slot_Explosivo,1654,6,0.141000,0.043999,-0.138999,-26.300012,-4.300000,109.700019,1.264000,1.130999,1.000000);
				SetPlayerExplosive(playerid, true);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
				ApplyAnimation(playerid, "BOMBER", "BOM_Plant_2Idle", 4.1, false, true, true, false, 0);

				format(string, sizeof(string), "*[BOMBA]: %s juntou sua bomba.", PlayerName[playerid]);
				SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

				return 1;
			}
			SendClientMessage(playerid, -1, "Você não está perto de sua bomba!");
		}
		else SendClientMessage(playerid, -1, "Você não plantou uma bomba.");
	}
	else if(!strcmp(params, "desarmar", true)){

		if(IsACop(playerid))
		{
			foreach(new i : Player)
			{
				if(GetPVarInt(i, "VarBomba"))
				{
					new objectid = GetPVarInt(i, "VarObject");
					new Float:x, Float:y, Float:z;
					GetDynamicObjectPos(objectid, x, y, z);
					if(IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z))
					{
						DestroyDynamicObject(objectid);
						SetPVarInt(i, "VarBomba", 0);
						ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle", 4.1, false, true, true, false, 0);

						format(string, sizeof string, "*O Policial %s desarmou sua bomba!", PlayerName[playerid]);
						SendClientMessage(i, -1, string);

						format(string, sizeof string, "[BOMBA]: O Policial %s conseguiu desarmar uma bomba!", PlayerName[playerid]);
						SendClientMessageToAll(COLOR_DBLUE, string);
						return 1;
					}
				}
			}
			SendClientMessage(playerid, -1, "Você não está perto de nenhuma bomba!");
		}
		else SendClientMessage(playerid, -1, "Você não é um policial!");
	}
	return 1;
}