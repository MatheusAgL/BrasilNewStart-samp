CMD:bau(playerid, params[])
{
	if (!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Voc� n�o est� logado.");
		
	if (isnull(params)) 
	{
		if (Dev_GetNivel(playerid) >= DEV_ALPHA)
			SendClientMessage(playerid, COLOR_DEV, "[Developer]: destruir | ir | trazer");

	    SendClientMessage(playerid, -1, "Modo de uso: /bau (nome | lista abaixo)");
	    SendClientMessage(playerid, COLOR_GRAY, "Nomes dispon�veis: Ajuda | Localizar");

		return 1;
	}
	
	new 
		string[128], 
		null[25];

	if (!strcmp(params, "ajuda", true))
	{
	    SendClientMessage(playerid, -1, " ");
	    SendClientMessage(playerid, COLOR_LIGHTBLUE, "Algumas informa��es:");
	    SendClientMessage(playerid, -1, "- O ba� (caixa de itens) serve para guardar itens de seu invent�rio para evitar ficar andando com eles.");
        SendClientMessage(playerid, -1, "- Voc� pode compr�-lo no /lojacash ou de outros jogadores e tamb�m pode revend�-lo.");
        SendClientMessage(playerid, -1, "- Voc� pode montar seu bau no ch�o onde voc� estiver usando ele no invent�rio");
		SendClientMessage(playerid, -1, "- Um ba� normal cabe {FFFF00}25{FFFFFF} itens, mas a quantidade pode ser aumentada com VIP ou com ba�s especiais.");
		SendClientMessage(playerid, -1, "- A capacidade m�xima de um ba� � de {008800}80{FFFFFF} itens, com todos os benef�cios.");

		SendMsgF(playerid, COLOR_VIP, "VIP � O seu n�vel de VIP permite que voc� monte at� %d ba�s no servidor.", Player_MaxLoot(playerid));

		SendClientMessage(playerid, COLOR_ERROR, "OBS: {FFFFFF}Voc� n�o pode colocar sua caixa de itens em qualquer lugar, leia as regras.");
	}
	else if (!strcmp(params, "destruir", true)) {

		if (Dev_GetNivel(playerid) < DEV_DELTA)
			return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para usar este comando.");

		new x = Player_LootCloser(playerid);
		if (x == -1) 
			return SendClientMessage(playerid, -1, "N�o h� nenhum ba� pr�ximo.");

		Loot_Destroy(playerid, x);

		SendClientMessage(playerid, COLOR_GRAY, "Ba� deletado com sucesso.");
	}
	else if (!strcmp(params, "localizar", true))
	{
		new listbau;
		MEGAString [0] = EOS;
		strcat(MEGAString, "ID Ba�\tItens Ba�\tMundo\tInterior\n");

		foreach(new loot : IterLoot) {
            if (Loot_GetOwner(loot) == Player_GetAccountID(playerid)) {
				
		       	format(string, sizeof string, "{7D8084}Ba� %d\t{7D8084}%d/%d {DBDCE0}Itens\t{7D8084}%d\t{7D8084}%d\n",
				loot, Loot_CountItens(loot), Loot_GetMaxItems(loot), Loot_GetWorld(loot), Loot_GetInterior(loot));
				strcat(MEGAString, string);

				List_SetPlayers(playerid, listbau, loot);
		        listbau++;
		    }
		}
		inline D_Loot(dyid, dydialogid, dyresponse, dylistitem, string:dytext[])
		{
			#pragma unused dyid, dydialogid, dytext
			if (!dyresponse) 
				return 1;

			new lootid = List_GetPlayers(playerid, dylistitem);

			format(string, sizeof string, "Voc� localizou seu ba� de ID %d. Siga a "C_RED"marca vermelha "C_BLUELIGHT"no mapa.", lootid);
			SendClientMessage(playerid, COLOR_BLUELIGHT, string);

			if (Loot_GetWorld(lootid) >= 505 && Loot_GetInterior(lootid) != 0) {
				SendMsgF(playerid, -1, "O ba� est� em no interior: %d e no world: %d.", Loot_GetInterior(lootid), Loot_GetWorld(lootid));
			} else if (Loot_GetWorld(lootid) != 0 && Loot_GetInterior(lootid) > 550) {
				SendMsgF(playerid, -1, "O ba� est� na casa %d interior: %d.", Loot_GetWorld(lootid), Loot_GetInterior(lootid));
			} else {
				Loot_SetCheckpoint(playerid, lootid);
			}
		}
		Dialog_ShowCallback(playerid, using inline D_Loot, DIALOG_STYLE_TABLIST_HEADERS, ""C_BLUELIGHT"Bau: Localizar", MEGAString, "Localizar", ""C_WARNING"Fechar");
	} 
	else if (strfind(params, "ir", true) != -1) 
	{
		if (Dev_GetNivel(playerid) < DEV_ALPHA)
			return SendClientMessage(playerid, -1, "Voc� n�o pode usar um comando da equipe de desenvolvimento.");

		new lootid;
		if (sscanf(params, "s[25]d", null, lootid)) 
			return SendClientMessage(playerid, -1, "Modo de uso: /bau ir (id)");

		if (!Iter_Contains(IterLoot, lootid))
		    return SendClientMessage(playerid, -1, "O ba� n�o existe.");

		Loot_SetPlayer(playerid, lootid);

	 	SendMsgF(playerid, COLOR_LIGHTGREEN, "Voc� foi at� o ba�: %d (%s)", lootid, Loot_GetName(lootid));	
	}
	else if (strfind(params, "trazer", true) != -1)
	{
		if (Dev_GetNivel(playerid) < DEV_ALPHA)
			return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para usar este comando.");

		new lootid;
		if (sscanf(params, "s[25]d", null, lootid)) 
			return SendClientMessage(playerid, -1, "Modo de uso: /bau trazer (id da caixa de itens)");

		new 
			Float:x, Float:y, Float:z, Float:a;

		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, a);

		Loot_SetPos(lootid, x, y, z, a, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
		Loot_DestroyObject(lootid);
		Loot_CreateObject(lootid);
		Loot_DestroyTextLabel(lootid);
		Loot_CreateTextLabel(lootid);
		
		SendMsgF(playerid, COLOR_LIGHTGREEN, "Voc� trouxe o ba�: %d (%s)", lootid, Loot_GetName(lootid));	
	}
	else {
	    SendClientMessage(playerid, -1, "Nomes dispon�veis: Ajuda | Localizar");

		if (Dev_GetNivel(playerid) >= DEV_ALPHA) {
			SendClientMessage(playerid, COLOR_DEV, "[Desenvolvedor]: destruir | ir | trazer");
		}
	}
	return true;
}