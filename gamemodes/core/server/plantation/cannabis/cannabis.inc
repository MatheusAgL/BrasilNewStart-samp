
stock CreateCannabis(Float:x, Float:y, Float:z, Float:a, owner[] = "Ninguem")
{
	new idx = Iter_Alloc(Cannabis);
	if (idx >= 0)
	{
	    z -= 0.7;
	    
	    CannabisInfo[idx][erva_x] = x;
	    CannabisInfo[idx][erva_y] = y;
	    CannabisInfo[idx][erva_z] = z;
	    CannabisInfo[idx][erva_a] = a;
	    CannabisInfo[idx][erva_stage] = ERVA_STAGE_SEMENTE;
	    CannabisInfo[idx][erva_agua] = 10.0;
	    CannabisInfo[idx][erva_time] = gettime() + TIME_UPDATE_ERVA;
	    format(CannabisInfo[idx][erva_owner], MAX_PLAYER_NAME + 1, owner);
	    
	    new string[128],
			log_string[128];
			
	    format(string, sizeof string, "Plantação de %s\nCrescimento: %d/3\nAgua: %0.1fL", owner, CannabisInfo[idx][erva_stage], CannabisInfo[idx][erva_agua]);
	    
	    format(log_string, sizeof log_string, "[Plantações] Maconha de %s, posição | x,y,z: %f, %f, %f.", owner,
	    CannabisInfo[idx][erva_x], CannabisInfo[idx][erva_y], CannabisInfo[idx][erva_z]);
	    server_log("plantacao", log_string);

	    CannabisLabel[idx] = CreateDynamic3DTextLabel(string, 0xFFFFFF77, x, y, z + 0.5, 5.0);
	    
	    CannabisObject[idx] = CreateDynamicObject(GetCannabisObject(idx), x, y, z, 0.0, 0.0, a);
	    
	    SaveCannabis(idx);
	}
	return idx;
}

stock DestroyCannabis(idx)
{
	if (Iter_Contains(Cannabis, idx))
	{
	    new string[75];
	    format(string, sizeof string, "ArquivosBPS/Plantacoes/%d.ini", idx);
	    
	    if (fexist(string)) 
			fremove(string);
	    
	    Iter_Remove(Cannabis, idx);
	    DestroyDynamicObject(CannabisObject[idx]);
	    DestroyDynamic3DTextLabel(CannabisLabel[idx]);
	    return 1;
	}
	return 0;
}

stock SaveCannabis(idx)
{
	if (Iter_Contains(Cannabis, idx)) {
	    new string[75];
	    format(string, sizeof string, "ArquivosBPS/Plantacoes/%d.ini", idx);
	    
		new File: file = fopen(string, io_write);
	    if (file) {
	        fblockwrite(file, CannabisInfo[idx]);
	        fclose(file);
	    }
	    return 1;
	}
	return 0;
}

stock LoadCannabis(idx)
{
	new string[128];
    format(string, sizeof string, "ArquivosBPS/Plantacoes/%d.ini", idx);
    new File: file = fopen(string, io_read);
    if (file) {
        Iter_Add(Cannabis, idx);
    	fblockread(file, CannabisInfo[idx]);
      	fclose(file);
	    format(string, sizeof string, "Plantação de %s\nCrescimento: %d/3\nAgua: %0.1fL", CannabisInfo[idx][erva_owner], CannabisInfo[idx][erva_stage], CannabisInfo[idx][erva_agua]);
	    CannabisLabel[idx] = CreateDynamic3DTextLabel(string, 0xFFFFFF77, CannabisInfo[idx][erva_x], CannabisInfo[idx][erva_y], CannabisInfo[idx][erva_z] + 0.5, 5.0);
	    CannabisObject[idx] = CreateDynamicObject(GetCannabisObject(idx), CannabisInfo[idx][erva_x], CannabisInfo[idx][erva_y], CannabisInfo[idx][erva_z], 0.0, 0.0, CannabisInfo[idx][erva_a]);
      	return 1;
    }
    return 0;
}

stock IsPlayerOwnerCannabis(playerid, idx) {
	if (!strcmp(PlayerName[playerid], CannabisInfo[idx][erva_owner]))
	    return 1;
	    
	return 0;
}

stock PlayerMaxCannabis(playerid) {
	if (CountPlayerCannabis(playerid) >= MAX_PLAYER_CANNABIS) 
		return true;

	return false;
}

stock CountPlayerCannabis(playerid) {
	new count;
	foreach(new idx : Cannabis) {
	    if (IsPlayerOwnerCannabis(playerid, idx)) 
			count++;
	}
	return count;
}

stock GetPlayerCannabisId(playerid) {
	foreach(new idx : Cannabis) {
	    if (IsPlayerInRangeOfPoint(playerid, 2.0, CannabisInfo[idx][erva_x], CannabisInfo[idx][erva_y], CannabisInfo[idx][erva_z])) {
	        return idx;
	    }
	}
	return -1;
}

stock GetCannabisQuantidade(idx) {
	switch (CannabisInfo[idx][erva_stage]) {
		case ERVA_STAGE_SEMENTE:    return 1;
		case ERVA_STAGE_PEQUENA:    return 2 + random(3);
		case ERVA_STAGE_MEDIA:      return 5 + random(5);
		case ERVA_STAGE_GRANDE:     return 10 + random(10);
		case ERVA_STAGE_SECA:     	return 3 + random(5);
	}
	return 1;
}

stock GetCannabisObject(idx) {
	switch (CannabisInfo[idx][erva_stage]) {
		case ERVA_STAGE_SEMENTE:    return 19300;
		case ERVA_STAGE_PEQUENA:    return 2247;
		case ERVA_STAGE_MEDIA:      return 2250;
		case ERVA_STAGE_GRANDE:     return 823;
		case ERVA_STAGE_SECA:     	return 819;
	}
	return 19300;
}

CALLBACK: RegarCannabis(playerid, idx) {
	ClearAnimations(playerid);

	RemovePlayerAttachedObject(playerid, 1);
	RemovePlayerAttachedObject(playerid, 3);

	if (GetPlayerCannabisId(playerid) != idx)
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não está mais perto da plantação.");

    CannabisInfo[idx][erva_agua] += 50.0;

	if (CannabisInfo[idx][erva_agua] > 100.0)
	    CannabisInfo[idx][erva_agua] = 100.0;

	new string[128];
	format(string, sizeof string, "Plantação de %s\nCrescimento: %d/3\nAgua: %0.1fL", CannabisInfo[idx][erva_owner], CannabisInfo[idx][erva_stage], CannabisInfo[idx][erva_agua]);

	if (CannabisInfo[idx][erva_stage] > 3)
		format(string, sizeof string, "Plantação de %s\nCrescimento: Morrendo...\nAgua: %0.1fL", CannabisInfo[idx][erva_owner], CannabisInfo[idx][erva_agua]);

	UpdateDynamic3DTextLabelText(CannabisLabel[idx], 0xFFFFFF77, string);
	return 1;
}

stock LoadAllCannabis() {
	for(new idx; idx < MAX_SERVER_CANNABIS; idx++)
	    LoadCannabis(idx);
	    
	return Iter_Count(Cannabis);
}

stock SaveAllCannabis() {
	foreach(new idx : Cannabis)
	    SaveCannabis(idx);

	return 1;
}

// regador: 19621
// agua: 18720

CMD:maconha(playerid, params[]) {
	if (isnull(params)) {
	    SendClientMessage(playerid, COLOR_GREY, "USE: /maconha [nome]");
	    SendClientMessage(playerid, COLOR_GREY, "Nomes disponíveis: colher, destruir, localizar");
	    return 1;
	}
	
	new idx = GetPlayerCannabisId(playerid);
	new string[128];
	
	if (!strcmp(params, "colher", true)) {
	    if (idx == -1)
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não está perto de nenhuma plantação de maconha.");
	        
		if (!IsPlayerOwnerCannabis(playerid, idx))
		    return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não é dono dessa plantação.");
		    
		static
		    Float:x, Float:y, Float:z;

		GetPlayerPos(playerid, x, y, z);
		    
        new quant = GetCannabisQuantidade(idx);
		    
        ApplyAnimation(playerid,"BOMBER","BOM_Plant_Loop", 4.1,0,0,0,0,0);
		    
		format(string, sizeof string, "* Maconha: Esta plantação lhe rendeu %d gramas de maconha semi-pronta.", quant);
		SendClientMessage(playerid, -1, string);
		SendClientMessage(playerid, -1, "* Maconha: Ainda não está pronta para consumo. Você deve levá-la para o processamento no mercado negro.");
		    
        createDroppedItem(x, y, z - 0.9, "Maconha semi-pronta", ITEM_TYPE_SEMIPRONTA, 2901, quant);
        DestroyCannabis(idx);
	}
	else if (!strcmp(params, "destruir", true)) {
	    if (idx == -1)
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não está perto de nenhuma plantação de maconha.");

		if (!(IsACop(playerid) || Admin_GetNivel(playerid)))
		    return SendClientMessage(playerid, COLOR_LIGHTRED, "Comando destinado a policiais ou administradores.");

        ApplyAnimation(playerid,"BOMBER","BOM_Plant_Loop", 4.1,0,0,0,0,0);

		format(string, sizeof string, "* Maconha: Você destruiu esta plantação que pertencia a %s.", CannabisInfo[idx][erva_owner]);
		SendClientMessage(playerid, -1, string);
		SendClientMessage(playerid, -1, "* Maconha: Verifique os arredores para ver se há mais plantações como esta.");
        DestroyCannabis(idx);
	}
	else if (!strcmp(params, "localizar", true)) {
	    new count;
	    
	    MEGAString[0] = EOS;
	    strcat(MEGAString, "Dono da plantação\tEstágio do crescimento\tAgua restante\n");
		foreach(new id : Cannabis) {
		    if (IsPlayerOwnerCannabis(playerid, id)) {
		        format(string, sizeof string, "%s\t{00BB00}%d/3\t%0.1fL\n", CannabisInfo[id][erva_owner], CannabisInfo[id][erva_stage], CannabisInfo[id][erva_agua]);
		    
		        if (CannabisInfo[id][erva_stage] > 3)
					format(string, sizeof string, "%s\t{00BB00}Morrendo...\t%0.1fL\n", CannabisInfo[idx][erva_owner], CannabisInfo[idx][erva_agua]);
		    
		        strcat(MEGAString, string);
		        SelectCannabis[playerid][count] = id;
		        count ++;
		    }
		}
		if (!count) 
			return SendClientMessage(playerid, COLOR_GREY, "Você não tem nenhuma plantação de maconha.");
		
		ShowPlayerDialog(playerid, 14000, DIALOG_STYLE_TABLIST_HEADERS, "Localizar suas plantações de maconha", MEGAString, "Localizar", "Fechar");
	}
	return 1;
}

task UpdateCannabis[10000]() {
	new string[128];
	foreach(new idx : Cannabis) {
	    if (CannabisInfo[idx][erva_agua] > 0.1) {
	        CannabisInfo[idx][erva_agua] -= 0.07 + randomfloat(0.07);

			// Fazer a ervinha crescer
			if (gettime() > CannabisInfo[idx][erva_time]) {
			    CannabisInfo[idx][erva_time] = gettime() + TIME_UPDATE_ERVA;
				if (CannabisInfo[idx][erva_stage] < 5) {
				    CannabisInfo[idx][erva_stage] ++;
				    DestroyDynamicObject(CannabisObject[idx]);
					CannabisObject[idx] = CreateDynamicObject(GetCannabisObject(idx), CannabisInfo[idx][erva_x], CannabisInfo[idx][erva_y], CannabisInfo[idx][erva_z], 0.0, 0.0, CannabisInfo[idx][erva_a]);
					if (CannabisInfo[idx][erva_stage] == ERVA_STAGE_DESTROY) {
					    DestroyCannabis(idx);
						break;
					}
				}
			}
			
			format(string, sizeof string, "Plantação de %s\nCrescimento: %d/3\nAgua: %0.1fF", CannabisInfo[idx][erva_owner], CannabisInfo[idx][erva_stage], CannabisInfo[idx][erva_agua]);

			if (CannabisInfo[idx][erva_stage] > 3)
				format(string, sizeof string, "Plantação de %s\nCrescimento: Morrendo...\nAgua: %0.1fF", CannabisInfo[idx][erva_owner], CannabisInfo[idx][erva_agua]);

			UpdateDynamic3DTextLabelText(CannabisLabel[idx], 0xFFFFFF77, string);
		}
	}
	return 1;
}
