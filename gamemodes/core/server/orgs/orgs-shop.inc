

new 
	OrgCofre[MAX_PLAYERS];

/*--------------------------------------------------------------------------*/

// Limites de sal?rio
#define		MAX_SALARIO_C1		10000
#define		MAX_SALARIO_C2		20000
#define		MAX_SALARIO_C3		30000
#define		MAX_SALARIO_C4		40000
#define		MAX_SALARIO_C5		50000
#define		MAX_SALARIO_C6		60000

// Variáveis
new tempoAnunciosOrg[MAX_ORGS] = 0;

CMD:anorg(playerid, params[])
{
    new org = GetPlayerOrg(playerid),
        string[128];

    if (org < 1 || PlayerInfo[playerid][pCargo] < 3) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    if (isnull(params)) return SendClientMessage(playerid, -1, "Modo de uso: /anorg (texto de anúncio)");
    
    if (strlen(params) < 16 || strlen(params) > 86) return SendClientMessage(playerid, -1, "O anúncio da organização deve conter entre 16 á 86 caracteres.");
	
    if (gettime() < tempoAnunciosOrg[org]) return SendClientMessage(playerid, -1, "Você deve esperar alguns minutos para mandar outro anuncio da sua organização!");

    if (IsACop(playerid) && OnDuty[playerid] != 1) return SendClientMessage(playerid, -1, "Você precisa bater o cartão para usar este comando.");

    format(string, sizeof string, "{9C9C9C}  »             Anúncio de {%s}%s	{9C9C9C}| Organização: {%s}%s{9C9C9C}             «  ", GetOrgColor(GetPlayerOrg(playerid)), PlayerName[playerid], GetOrgColor(GetPlayerOrg(playerid)), GetOrgName(org));
    SendClientMessageToAll(-1, string);
    format(string, sizeof string, "{%s}%s", GetOrgColor(GetPlayerOrg(playerid)), params);
    SendClientMessageToAll(-1, string);
    SendClientMessageToAll(0x9C9C9CFF, "_____________________________________________________________________________________________________");

    if (org == ID_ORG_GOVERNO) tempoAnunciosOrg[org] = gettime() + 10;
    else tempoAnunciosOrg[org] = gettime() + 120;

	ServerLog::("anorg", "%s [%s]: %s", PlayerName[playerid], GetOrgName(org), params);

    return 1;
}
alias:anorg("pre", "gov")

#define		DIALOG_ID_ORG		44

stock ShowDialogCofreOrg(playerid) {

	MEGAString[0] = EOS;

	// ALL
	strcat(MEGAString, 
			""C_WHITE"Informações\nMembros\n"C_RED"Equipar\n"C_WHITE"Area para vendedores");

	if (PlayerInfo[playerid][pCargo] > SUB_LIDER_2) {
		strcat(MEGAString, 
			"\n"C_YELLOW"Gerenciamento");
	}

	ShowPlayerDialog(playerid, DIALOG_ID_ORG, DIALOG_STYLE_LIST, ""C_SAMP"Organização: Painel", MEGAString, ""C_SAMP"Prosseguir", "Fechar");

	return 1;
}

static EditMembers(playerid, const function[]) {

	new string[100];
	new orgid = GetPlayerOrg(playerid);
	MEGAString[0] = EOS;

	if (!strcmp(function, "cargos", true)) {

		strcat(MEGAString, ""C_SAMP"id cargo\tnome do cargo\n");

		for (new cargoid = 1; cargoid < MAX_CARGOS_ORG + 1; cargoid++) {
			format(string, sizeof string,
				""C_WHITE"Cargo %d\t%s\n", cargoid, GetCargoOrg(orgid, cargoid));
			strcat(MEGAString, string);
		}
		ShowPlayerDialog(playerid, DIALOG_ID_ORG + 3, DIALOG_STYLE_TABLIST_HEADERS, ""C_SAMP"Organização: Editar cargos", MEGAString, ""C_SAMP"Editar", "Retornar");
	}

	return 1;
}

stock showDialogDefinicoes(playerid, orgid)
{
    new string[128];
	MEGAString[0] = EOS;

	TogglePlayerControllable(playerid, true);

 	strcat(MEGAString, "(Item e/ou arma)\t(Quant. ou munição)\n");

	strcat(MEGAString, "{EBE8E8}Editar\t{9C9C9C}Nome dos cargos\n");

	strcat(MEGAString, "{EBE8E8}Limpar\t{9C9C9C}Vagas\n");

	format(string, sizeof string, "{EBE8E8}Limite de {9C9C9C}Maconha\t{DF8F43}%sg\n", getFormatText(CofreOrg[orgid][Maconha]));
	strcat(MEGAString, string);

	format(string, sizeof string, "{EBE8E8}Pedido de {9C9C9C}Materiais\t{5ED661}%sg\n", getFormatText(CofreOrg[orgid][cMateriais]));
	strcat(MEGAString, string);

	format(string, sizeof string, "{EBE8E8}Pedido de {9C9C9C}Maconha\t{5ED661}%sg\n", getFormatText(CofreOrg[orgid][cMaconha]));
	strcat(MEGAString, string);
	
	strcat(MEGAString, "Cofre da organização {9C9C9C}(Drogas/Dinheiro)\t{5ED661}(deposite)\n");

	strcat(MEGAString, "Editar salário dos {9C9C9C}membros\t{5ED661}(por cargo)\n");

	ShowPlayerDialog(playerid, DIALOG_ID_ORG + 2, DIALOG_STYLE_TABLIST_HEADERS, "{DACB70}Definições da organização", MEGAString, "Prosseguir", "Retornar");

	return true;
}

CALLBACK:IsOrgTraining(orgid) {
	return CofreOrg[orgid][TrainingOrg] > 0;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new string[128];

	if (dialogid == DIALOG_ID_ORG) {
		if (response) {
			switch (listitem) {

				// Informações da organização;
				case 0: {
					new orgid = GetPlayerOrg(playerid);

					ShowInfoOrg(playerid, orgid, DIALOG_ID_ORG + 1, "Informações da organização", "Retornar", "Fechar");
				}

				// Último login dos membros;
				case 1: {
					ShowMembersInOrg(playerid, DIALOG_ID_ORG + 5, ""C_GRAY"Organização: Membros", "Fechar", "Retornar");
				}

				// Equipar;
				case 2: {
					if (OrgCofre[playerid] != GetPlayerOrg(playerid)) 
						return SendClientMessage(playerid, -1, "Você não faz parte dessa organização.");

					weaponsOrganizacao(playerid, GetPlayerOrg(playerid));
				}

				// Área para vendedores
				case 3: {
					showDialogOrgVendas(playerid);
				}

				// Painel de gerenciamento
				case 4: {
					if (OrgCofre[playerid] != GetPlayerOrg(playerid))
						return SendClientMessage(playerid, COLOR_WHITE, "Você não faz parte dessa organização.");

					if (PlayerInfo[playerid][pCargo] < SUB_LIDER_2) 
						return SendClientMessage(playerid, COLOR_WHITE, "Você precisa ser SubLider+ para usar esse comando.");

					showDialogDefinicoes(playerid, OrgCofre[playerid]);
				}
			}
		}
	}

	else if (dialogid == DIALOG_ID_ORG + 1) {
		if (!response)
			return 1;
		
		return ShowDialogCofreOrg(playerid);
	}

	else if (dialogid == DIALOG_ID_ORG + 2)
	{
	    new org = GetPlayerOrg(playerid);

	    MEGAString[0] = EOS;

		if (!response) 
			return ShowDialogCofreOrg(playerid);

		if (PlayerInfo[playerid][pCargo] < SUB_LIDER_2) return SendClientMessage(playerid,COLOR_LIGHTBLUE, "Apenas permitido para líderes e sub-líderes.");

		switch (listitem)
		{
			case 0: EditMembers(playerid, "cargos");
			case 1: ShowMembersInOrg(playerid, DIALOG_ID_ORG + 6, ""C_GRAY"Organização: Membros", "Fechar", "Retornar");
			case 2:
			{
		  	 	format(string, sizeof(string),"Defina a quantidade de Maconha ao Equipar\nAtualmente está definido em: %d Maconha", OrgInfo_GetGiveMarihuana(org));
		    	ShowPlayerDialog(playerid, 8549, DIALOG_STYLE_INPUT, "Definição de Maconha", string, "Salvar", "Cancelar");
				return true;
			}
			// case 3:
			// {
		    // 	PlayerLojaOrgId[playerid] = 0;

			// 	strcat(MEGAString, "Nome da arma\tSlot da arma (0)\tCusto\n");

	        //     for (new itemid = PlayerLojaOrgId[playerid]; itemid != 11; itemid ++)
			// 	{
			// 	    if (CofreOrg[org][ArmaLoja][itemid]) format(string, sizeof string, "%s\t{DBDCE0}(arma branca)\t{75D336}Adquirido(a)\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));
			// 		else format(string, sizeof string, "%s\t{DBDCE0}(arma branca)\t{FFFFFF}$%s\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));

			// 		strcat(MEGAString, string);
			// 	}

			// 	ShowPlayerDialog(playerid, 8922, DIALOG_STYLE_TABLIST_HEADERS, inputtext, MEGAString, "Selecionar", "Retornar");

			// 	return true;
			// }
			// case 4:
			// {
		    // 	PlayerLojaOrgId[playerid] = 11;

			// 	strcat(MEGAString, "Nome da arma\tSlot da arma (1)\tCusto\n");

	        //     for (new itemid = PlayerLojaOrgId[playerid]; itemid != 14; itemid ++)
			// 	{
			// 	    if (CofreOrg[org][ArmaLoja][itemid]) format(string, sizeof string, "%s\t{DBDCE0}(arma especial)\t{75D336}Adquirido(a)\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));
			// 		else format(string, sizeof string, "%s\t{DBDCE0}(arma especial)\t{FFFFFF}$%s\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));

			// 		strcat(MEGAString, string);
			// 	}

			// 	ShowPlayerDialog(playerid, 8922, DIALOG_STYLE_TABLIST_HEADERS, inputtext, MEGAString, "Selecionar", "Retornar");

			// 	return true;
			// }
			// case 5:
			// {
		    // 	PlayerLojaOrgId[playerid] = 14;

			// 	strcat(MEGAString, "Nome da arma\tSlot da arma (2)\tCusto\n");

	        //     for (new itemid = PlayerLojaOrgId[playerid]; itemid != 17; itemid ++)
			// 	{
			// 	    if (CofreOrg[org][ArmaLoja][itemid]) format(string, sizeof string, "%s\t{DBDCE0}(pistola)\t{75D336}Adquirido(a)\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));
			// 		else format(string, sizeof string, "%s\t{DBDCE0}(pistola)\t{FFFFFF}$%s\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));

			// 		strcat(MEGAString, string);
			// 	}

			// 	ShowPlayerDialog(playerid, 8922, DIALOG_STYLE_TABLIST_HEADERS, inputtext, MEGAString, "Selecionar", "Retornar");

			// 	return true;
			// }
			// case 6:
			// {
		    // 	PlayerLojaOrgId[playerid] = 17;

			// 	strcat(MEGAString, "Nome da arma\tSlot da arma (3)\tCusto\n");

	        //     for (new itemid = PlayerLojaOrgId[playerid]; itemid != 20; itemid ++)
			// 	{
			// 	    if (CofreOrg[org][ArmaLoja][itemid]) format(string, sizeof string, "%s\t{DBDCE0}(shotgun)\t{75D336}Adquirido(a)\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));
			// 		else format(string, sizeof string, "%s\t{DBDCE0}(shotgun)\t{FFFFFF}$%s\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));

			// 		strcat(MEGAString, string);
			// 	}

			// 	ShowPlayerDialog(playerid, 8922, DIALOG_STYLE_TABLIST_HEADERS, inputtext, MEGAString, "Selecionar", "Retornar");

			// 	return true;
			// }
			// case 7:
			// {
		    // 	PlayerLojaOrgId[playerid] = 20;

			// 	strcat(MEGAString, "Nome da arma\tSlot da arma (4)\tCusto\n");

	        //     for (new itemid = PlayerLojaOrgId[playerid]; itemid != 22; itemid ++)
			// 	{
			// 	    if (CofreOrg[org][ArmaLoja][itemid]) format(string, sizeof string, "%s\t{DBDCE0}(sub-metralhadora)\t{75D336}Adquirido(a)\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));
			// 		else format(string, sizeof string, "%s\t{DBDCE0}(metralhadora)\t{FFFFFF}$%s\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));

			// 		strcat(MEGAString, string);
			// 	}

			// 	ShowPlayerDialog(playerid, 8922, DIALOG_STYLE_TABLIST_HEADERS, inputtext, MEGAString, "Selecionar", "Retornar");

			// 	return true;
			// }
			// case 8:
			// {
		    // 	PlayerLojaOrgId[playerid] = 22;

			// 	strcat(MEGAString, "Nome da arma\tSlot da arma (5)\tCusto\n");

	        //     for (new itemid = PlayerLojaOrgId[playerid]; itemid != 25; itemid ++)
			// 	{
			// 	    if (CofreOrg[org][ArmaLoja][itemid]) format(string, sizeof string, "%s\t{DBDCE0}(metralhadora)\t{75D336}Adquirido(a)\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));
			// 		else format(string, sizeof string, "%s\t{DBDCE0}(metralhadora)\t{FFFFFF}$%s\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));

			// 		strcat(MEGAString, string);
			// 	}

			// 	ShowPlayerDialog(playerid, 8922, DIALOG_STYLE_TABLIST_HEADERS, inputtext, MEGAString, "Selecionar", "Retornar");

			// 	return true;
			// }
  			// case 9:
			// {
		    // 	PlayerLojaOrgId[playerid] = 25;

			// 	strcat(MEGAString, "Nome da arma\tSlot da arma (6)\tCusto\n");

	        //     for (new itemid = PlayerLojaOrgId[playerid]; itemid != 27; itemid ++)
			// 	{
			// 	    if (CofreOrg[org][ArmaLoja][itemid]) format(string, sizeof string, "%s\t{DBDCE0}(rifle)\t{75D336}Adquirido(a)\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));
			// 		else format(string, sizeof string, "%s\t{DBDCE0}(rifle)\t{FFFFFF}$%s\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));

			// 		strcat(MEGAString, string);
			// 	}

			// 	ShowPlayerDialog(playerid, 8922, DIALOG_STYLE_TABLIST_HEADERS, inputtext, MEGAString, "Selecionar", "Retornar");

			// 	return true;
			// }
 			// case 10:
			// {
			//     if (!CofreOrg[org][orgVIP]) return SendClientMessage(playerid, -1, "Os slots 6 e 7 são apenas para organizações VIP.");

		    // 	PlayerLojaOrgId[playerid] = 27;

			// 	strcat(MEGAString, "Nome da arma\tSlot da arma (7)\tCusto\n");

	        //     for (new itemid = PlayerLojaOrgId[playerid]; itemid != 29; itemid ++)
			// 	{
			// 	    if (CofreOrg[org][ArmaLoja][itemid]) format(string, sizeof string, "%s\t{DBDCE0}(granada)\t{75D336}Adquirido(a)\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));
			// 		else format(string, sizeof string, "%s\t{DBDCE0}(granada)\t{FFFFFF}$%s\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));

			// 		strcat(MEGAString, string);
			// 	}

			// 	ShowPlayerDialog(playerid, 8922, DIALOG_STYLE_TABLIST_HEADERS, inputtext, MEGAString, "Selecionar", "Retornar");

			// 	return true;
			// }
			// case 11:
			// {
			//     if (!CofreOrg[org][orgVIP]) return SendClientMessage(playerid, -1, "Os slots 6 e 7 são apenas para organizações VIP.");

			// 	PlayerLojaOrgId[playerid] = 29;

			// 	strcat(MEGAString, "Nome da arma\tSlot da arma (8)\tCusto\n");

	        //     for (new itemid = PlayerLojaOrgId[playerid]; itemid != 31; itemid ++)
			// 	{
			// 	    if (CofreOrg[org][ArmaLoja][itemid]) format(string, sizeof string, "%s\t{DBDCE0}(especial)\t{75D336}Adquirido(a)\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));
			// 		else format(string, sizeof string, "%s\t{DBDCE0}(especial)\t{FFFFFF}$%s\n", ArmasOrgInfo[itemid][Arma_Nome], getFormatText(ArmasOrgInfo[itemid][Arma_Custo]));

			// 		strcat(MEGAString, string);
			// 	}

			// 	ShowPlayerDialog(playerid, 8922, DIALOG_STYLE_TABLIST_HEADERS, inputtext, MEGAString, "Selecionar", "Retornar");

			// 	return true;
			// }
			case 3:
			{
		    	format(string,sizeof(string),"Defina o Pedido de Materiais\nAtualmente está definido em: %d Materiais",CofreOrg[org][cMateriais]);
		   		ShowPlayerDialog(playerid, 8850, DIALOG_STYLE_INPUT, "Pedido de Materiais", string, "Salvar", "Cancelar");
				return true;
			}
 			case 4:
			{
		    	format(string,sizeof(string),"Defina o Pedido de Maconha\nAtualmente está definido em: %d Maconha",CofreOrg[org][cMaconha]);
		   		ShowPlayerDialog(playerid, 8851, DIALOG_STYLE_INPUT, "Pedido de Maconha", string, "Salvar", "Cancelar");
				return true;
			}
			case 5:
			{
			    ShowPlayerDialog(playerid, 4507, DIALOG_STYLE_LIST, "Drogas/Dinheiro da Organização", "Dinheiro\nMateriais\nMaconha\nCocaina\nCrack", "Selecionar","Voltar");
			    return true;
			}
 			case 6:
			{
       			format(string,sizeof(string),"Salário do Cargo 1\nSalário do Cargo 2\nSalário do Cargo 3\nSalário do Cargo 4\nSalário do Cargo 5 e Sub-Líderes\nSalário do Líder");
		   		ShowPlayerDialog(playerid, 8877, DIALOG_STYLE_LIST, "Salarios", string, "Salvar", "Cancelar");
				return true;
			}
		}
	    return 1;
	}

	else if (dialogid == DIALOG_ID_ORG + 3) {

		new idorg = GetPlayerOrg(playerid);

		if (!response) return showDialogDefinicoes(playerid, idorg);

		SetPVarInt(playerid, "selected_cargo", listitem+1);

		format(string, sizeof(string),
			""C_WHITE"Você está editando o cargo "C_GRAY"%d\n\n"C_WHITE"Como será o nome do cargo?\n"C_GRAY"--------------------------------------------------------------------------", listitem+1);

		ShowPlayerDialog(playerid, DIALOG_ID_ORG + 4, DIALOG_STYLE_INPUT, ""C_SAMP"Organização: Editando nome do cargo", string, ""C_SAMP"Salvar", "Retornar");

		return 1;
	}

	else if (dialogid == DIALOG_ID_ORG + 4) {
		if (!response) 
			return EditMembers(playerid, "cargos");

		new idorg = GetPlayerOrg(playerid),
			cargoid = GetPVarInt(playerid, "selected_cargo");
		
		if (strlen(inputtext) < 5 && strlen(inputtext) > 35) { 
			return SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você deve digitar entre 5 e 35 caracteres o nome do cargo.");
		}
		OrgCargo_Update(idorg, cargoid, inputtext);

		format(string, sizeof(string),"Você alterou o nome do cargo %d para %s.", cargoid, GetCargoOrg(idorg, cargoid));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

		EditMembers(playerid, "cargos");

		return 1;
	}

	else if (dialogid == DIALOG_ID_ORG + 5) {
		if (!response) 
			return ShowDialogCofreOrg(playerid);

		return 1;
	}

	else if (dialogid == DIALOG_ID_ORG + 6) {
		if (!response) 
			return showDialogDefinicoes(playerid, GetPlayerOrg(playerid));

		new listselect = Dialog_Select[playerid][listitem];

		SendMsgF(playerid, COLOR_LIGHTBLUE, "Você demitiu o jogador %s da sua organização.", Player_GetNicknameByID(listselect));

		DismissPlayerOrg(GetPlayerOrg(playerid), listselect);

		return 1;
	}

	else if (dialogid == DIALOG_ID_ORG + 7)
	{
		if(response >= 1)
		{
		    new org = GetPlayerOrg(playerid);
		    new saccrac = strval(inputtext);
			if(saccrac > CofreOrg[org][Crack])
			{
			    SendClientMessage(playerid,-1, "Sua Organização não tem tudo isso!");
			    return true;
			}
			if (PlayerInfo[playerid][pCargo] < SUB_LIDER_2)
			{
			    SendClientMessage(playerid,-1, "Somente Líder e Sub-Líder Podem Sacar Crack");
			    return true;
			}
			if(saccrac > 0)
			{
			    if(saccrac <= CofreOrg[org][Crack])
			    {
					givePlayerItem(playerid, ITEM_TYPE_COCAINA, 1576, saccrac, "Crack");
					OrgInfo_SetCrack(org, OrgInfo_GetCrack(org) - saccrac);
		    		format(string,sizeof(string),"Você Sacou %d de Crack, o Novo Saldo de Crack é de %d" ,saccrac, CofreOrg[org][Crack]);
		    		SendClientMessage(playerid,COLOR_GRAD,string);
		    		return true;
	    		}
		    }
			return true;
		}
	    return true;
	}

	else if (dialogid == 7463) 
	{
	    if(response){
	        callcmd::aceitar(playerid, "convite");
	    }
	    else{

	        SendClientMessage(playerid, COLOR_LIGHTRED, "* Você recusou o convite!");
			if(InviteOffer[playerid] < 999)
   			{
				if(IsPlayerConnected(InviteOffer[playerid]))
				{
				    format(string, sizeof string, "* %s recusou o seu convite para entrar para a organização!", PlayerName[playerid]);
					SendClientMessage(InviteOffer[playerid], COLOR_LIGHTRED, string);
				}
			}
	    }

	    return 1;
	}
	else if(dialogid == 8877)
	{
	    new org = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, org);

		if(response >= 1)
		{
			if(listitem == 0)
			{
		    	format(string,sizeof(string),"Defina o Salario do Cargo 1\nAtualmente esta definido em %d",CofreOrg[org][salarioc1]);
		    	ShowPlayerDialog(playerid, 8878, DIALOG_STYLE_INPUT, "Salario Cargo 1", string, "Salvar", "Cancelar");
				return true;
			}
			if(listitem == 1)
			{
		    	format(string,sizeof(string),"Defina o Salario do Cargo 2\nAtualmente esta definido em %d",CofreOrg[org][salarioc2]);
		    	ShowPlayerDialog(playerid, 8879, DIALOG_STYLE_INPUT, "Salario Cargo 2", string, "Salvar", "Cancelar");
				return true;
			}
			if(listitem == 2)
			{
		    	format(string,sizeof(string),"Defina o Salario do Cargo 3\nAtualmente esta definido em %d",CofreOrg[org][salarioc3]);
		    	ShowPlayerDialog(playerid, 8880, DIALOG_STYLE_INPUT, "Salario Cargo 3", string, "Salvar", "Cancelar");
				return true;
			}
			if(listitem == 3)
			{
		    	format(string,sizeof(string),"Defina o Salario do Cargo 4\nAtualmente esta definido em %d",CofreOrg[org][salarioc4]);
		    	ShowPlayerDialog(playerid, 8881, DIALOG_STYLE_INPUT, "Salario Cargo 4", string, "Salvar", "Cancelar");
				return true;
			}
			if(listitem == 4)
			{
		    	format(string,sizeof(string),"Defina o Salario do Cargo 5 e SUBs\nAtualmente esta definido em %d",CofreOrg[org][salarioc5]);
		    	ShowPlayerDialog(playerid, 8882, DIALOG_STYLE_INPUT, "Salario Cargo 5 e SUBs", string, "Salvar", "Cancelar");
				return true;
			}
			if(listitem == 5)
			{
		    	format(string,sizeof(string),"Defina o Salario do Lider\nAtualmente esta definido em %d",CofreOrg[org][salariolider]);
		    	ShowPlayerDialog(playerid, 8883, DIALOG_STYLE_INPUT, "Salario Lider", string, "Salvar", "Cancelar");
				return true;
			}
		}
	    return true;
	}

	else if(dialogid == 8878)
	{
	    new definicao = strval(inputtext);
	    new org = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, org);

		if(response >= 1)
		{
		    if(definicao < 0)return SendClientMessage(playerid, -1, "Valor inválido!");

			new salarioMax = MAX_SALARIO_C1;
			if(GetPlayerOrg(playerid) == 16 || GetPlayerOrg(playerid) == 11)
				salarioMax = floatround(salarioMax * 1.8);
			else if(IsACopOrg(GetPlayerOrg(playerid)))
				salarioMax = floatround(salarioMax * 1.5);

		    if(definicao > salarioMax) 
				return SendMsgF(playerid, COLOR_LIGHTBLUE, "Você definiu um salário muito alto. Máximo: R$ %s.", getFormatText(salarioMax));

		   	CofreOrg[org][salarioc1] = definicao;
		   	DefinirSalarioc1(org,definicao);
		   	format(string,sizeof(string),"	Você ajustou o salário do cargo 1 para: %d.",definicao);
		   	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			return true;
		}
	}
	else if(dialogid == 8879)
	{
	    new definicao = strval(inputtext);
	    new org = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, org);

		if(response >= 1)
		{
		    if(definicao < 0)return SendClientMessage(playerid, -1, "Valor inválido!");

		    new salarioMax = MAX_SALARIO_C2;
			if(GetPlayerOrg(playerid) == 16 || GetPlayerOrg(playerid) == 11)
				salarioMax = floatround(salarioMax * 1.8);
			else if(IsACopOrg(GetPlayerOrg(playerid)))
				salarioMax = floatround(salarioMax * 1.5);

		    if(definicao > salarioMax) 
				return SendMsgF(playerid, COLOR_LIGHTBLUE, "Você definiu um salário muito alto. Máximo: R$ %s.", getFormatText(salarioMax));
		   
		   	CofreOrg[org][salarioc2] = definicao;
		   	DefinirSalarioc2(org,definicao);
		   	format(string,sizeof(string),"	Você ajustou o salário do cargo 2 para: %d.",definicao);
		   	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			return true;
		}
	}
	else if(dialogid == 8880)
	{
	    new definicao = strval(inputtext);
	    new org = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, org);

		if(response >= 1)
		{
		    if(definicao < 0)return SendClientMessage(playerid, -1, "Valor inválido!");

		    new salarioMax = MAX_SALARIO_C3;
			if(GetPlayerOrg(playerid) == 16 || GetPlayerOrg(playerid) == 11)
				salarioMax = floatround(salarioMax * 1.8);
			else if(IsACopOrg(GetPlayerOrg(playerid)))
				salarioMax = floatround(salarioMax * 1.5);

		    if(definicao > salarioMax) 
				return SendMsgF(playerid, COLOR_LIGHTBLUE, "Você definiu um salário muito alto. Máximo: R$ %s.", getFormatText(salarioMax));

		   	CofreOrg[org][salarioc3] = definicao;
		   	DefinirSalarioc3(org,definicao);
		   	format(string,sizeof(string),"	Você ajustou o salário do cargo 3 para: %d.",definicao);
		   	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			return true;
		}
	}
	else if(dialogid == 8881)
	{
	    new definicao = strval(inputtext);
	    new org = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, org);

		if(response >= 1)
		{
		    if(definicao < 0)return SendClientMessage(playerid, -1, "Valor inválido!");

		    new salarioMax = MAX_SALARIO_C4;
			if(GetPlayerOrg(playerid) == 16 || GetPlayerOrg(playerid) == 11)
				salarioMax = floatround(salarioMax * 1.8);
			else if(IsACopOrg(GetPlayerOrg(playerid)))
				salarioMax = floatround(salarioMax * 1.5);

		    if(definicao > salarioMax) 
				return SendMsgF(playerid, COLOR_LIGHTBLUE, "Você definiu um salário muito alto. Máximo: R$ %s.", getFormatText(salarioMax));
			
		   	CofreOrg[org][salarioc4] = definicao;
		   	DefinirSalarioc4(org,definicao);
		   	format(string,sizeof(string),"	Você ajustou o salário do cargo 4 para: %d.",definicao);
		   	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			return true;
		}
	}
	else if(dialogid == 8882)
	{
	    new definicao = strval(inputtext);
	    new org = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, org);

		if(response >= 1)
		{
		    if(definicao < 0)return SendClientMessage(playerid, -1, "Valor inválido!");

		    new salarioMax = MAX_SALARIO_C5;
			if(GetPlayerOrg(playerid) == 16 || GetPlayerOrg(playerid) == 11)
				salarioMax = floatround(salarioMax * 1.8);
			else if(IsACopOrg(GetPlayerOrg(playerid)))
				salarioMax = floatround(salarioMax * 1.5);

		    if(definicao > salarioMax) 
				return SendMsgF(playerid, COLOR_LIGHTBLUE, "Você definiu um salário muito alto. Máximo: R$ %s.", getFormatText(salarioMax));

		   	CofreOrg[org][salarioc5] = definicao;
		   	DefinirSalarioc5(org,definicao);
		   	format(string,sizeof(string),"	Você ajustou o salário do cargo 5 e SUBs para: %d.",definicao);
		   	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			return true;
		}
	}

	else if(dialogid == 8883)
	{
	    new definicao = strval(inputtext);
	    new org = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, org);

		if(response >= 1)
		{
		    if(definicao < 0)return SendClientMessage(playerid, -1, "Valor inválido!");

		    new salarioMax = MAX_SALARIO_C6;
			if(GetPlayerOrg(playerid) == 16 || GetPlayerOrg(playerid) == 11)
				salarioMax = floatround(salarioMax * 1.8);
			else if(IsACopOrg(GetPlayerOrg(playerid)))
				salarioMax = floatround(salarioMax * 1.5);

		    if(definicao > salarioMax) 
				return SendMsgF(playerid, COLOR_LIGHTBLUE, "Você definiu um salário muito alto. Máximo: R$ %s.", getFormatText(salarioMax));

		   	CofreOrg[org][salariolider] = definicao;
		   	DefinirSalarioc6(org,definicao);
		   	format(string,sizeof(string),"	Você ajustou o salário do LÍDER para: %d.",definicao);
		   	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			return true;
		}
	}

	else if(dialogid == 8851)
	{
	    new definicao = strval(inputtext);
	    new org = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, org);

		if(response >= 1)
		{
		    if(definicao < 10 || definicao > 50000)
	        {
				SendClientMessage(playerid, -1, "Valor entre 10 -  50000!");
				return true;
	        }
			OrgInfo_SetGiveMarihuana(org, definicao);
		   	format(string,sizeof(string),"Defina a quantidade que paga por %d Maconhas",CofreOrg[org][cMaconha]);
		   	ShowPlayerDialog(playerid, 8860, DIALOG_STYLE_INPUT, "Definição", string, "Salvar", "Cancelar");
			return true;
		}
	}
	else if(dialogid == 8860)
	{
	    new definicao = strval(inputtext);
	    new org = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, org);

		if(response >= 1)
		{
			if(definicao < 1000 || definicao > 500000)
	        {
				SendClientMessage(playerid, -1, "Valor entre 1000 -  500.000!");
				return true;
	        }
		    if(definicao < 0)return SendClientMessage(playerid, -1, "Valor inválido!");
			OrgInfo_SetGiveMarihuana(org, definicao);
		   	format(string,sizeof(string),">|SERVER|> Você paga $%d por %d gramas de maconhanv.", CofreOrg[org][mMaconha], CofreOrg[org][cMaconha]);
		   	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			return true;
		}
	}

	else if(dialogid == 8549)
	{
	    new org = GetPlayerOrg(playerid);
	    new definicao = strval(inputtext);
		if(response >= 1)
		{
			if(definicao > 500)
			{
		   	    SendClientMessage(playerid,COLOR_LIGHTRED,"[ERRO] Você definiu um Valor muito alto");
				return 1;
	  		}
	  		if (definicao < 0)
				return SendClientMessage(playerid, -1, "Valor inválido!");

		   	format(string, sizeof(string), "Você definiu o total de maconha para: %d.", definicao);
		   	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			OrgInfo_SetGiveMarihuana(org, definicao);
   		}
		return true;
	}

	else if(dialogid == 13)
	{
	    new org = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, org);

		if(response >= 1)
		{
		    format(string,sizeof(string),"O Saldo da Sua Organização é de $%d\nQuantos você deseja depositar ?",CofreOrg[org][orgDinheiro]);
		    ShowPlayerDialog(playerid, 19, DIALOG_STYLE_INPUT, "Cofre da Organização", string, "Depositar", "Cancelar");
			return true;
		}
	    return true;
	}
	else if(dialogid == 14)
	{
	    new org = GetPlayerOrg(playerid);
	    if(response == 0)
		{
			return ShowDialogCofreOrg(playerid);
		}
		if(response >= 1)
		{
		    format(string,sizeof(string),"A sua organização possui %sg de Materiais\nVocê deseja depositar quantos materiais?", getFormatText(CofreOrg[org][Materiais]));
		    ShowPlayerDialog(playerid, 21, DIALOG_STYLE_INPUT, "Cofre da Organização", string, "Depositar", "Cancelar");
			return true;
		}
	    return true;
	}
	else if(dialogid == 15)
	{
	    new org = GetPlayerOrg(playerid);
	    if(response == 0)
		{
		    format(string,sizeof(string),"A Sua Organização tem %d de Maconha\nQuantos você deseja Depositar ?",CofreOrg[org][Maconha]);
		    ShowPlayerDialog(playerid, 22, DIALOG_STYLE_INPUT, "Cofre da Organização", string, "Depositar", "Cancelar");
			return true;
		}
		if(response >= 1)
		{
		    format(string,sizeof(string),"A Sua Organização tem %d de Maconha\nQuantos você deseja Sacar ?",CofreOrg[org][Maconha]);
		    ShowPlayerDialog(playerid, 23, DIALOG_STYLE_INPUT, "Cofre da Organização", string, "Sacar", "Cancelar");
			return true;
		}
	    return true;
	}

	else if(dialogid == 16)
	{
	    new org = GetPlayerOrg(playerid);
	    if(response == 0)
		{
		    format(string,sizeof(string),"A Sua Organização tem %d de Cocaina\nQuantos você deseja Depositar ?",CofreOrg[org][Cocaina]);
		    ShowPlayerDialog(playerid, 24, DIALOG_STYLE_INPUT, "Cofre da Organização", string, "Depositar", "Cancelar");
			return true;
		}
		if(response >= 1)
		{
		    format(string,sizeof(string),"A Sua Organização tem %d de Cocaina\nQuantos você deseja Sacar ?",CofreOrg[org][Cocaina]);
		    ShowPlayerDialog(playerid, 25, DIALOG_STYLE_INPUT, "Cofre da Organização", string, "Sacar", "Cancelar");
			return true;
		}
	    return true;
	}
	else if(dialogid == 17)
	{
	    new org = GetPlayerOrg(playerid);
	    if(response == 0)
		{
		    format(string,sizeof(string),"A Sua Organização tem %d de Crack\nQuantos você deseja Depositar ?",CofreOrg[org][Crack]);
		    ShowPlayerDialog(playerid, 26, DIALOG_STYLE_INPUT, "Cofre da Organização", string, "Depositar", "Cancelar");
			return true;
		}
		if(response >= 1)
		{
		    format(string,sizeof(string),"A Sua Organização tem %d de Crack\nQuantos você deseja Sacar ?",CofreOrg[org][Crack]);
		    ShowPlayerDialog(playerid, DIALOG_ID_ORG + 7, DIALOG_STYLE_INPUT, "Cofre da Organização", string, "Sacar", "Cancelar");
			return true;
		}
	    return true;
	}
	else if (dialogid == 19)
	{
		if(response >= 1)
		{
		    new org = GetPlayerOrg(playerid);
		    new depgrana = strval(inputtext);
			if(Player_GetMoney(playerid) < depgrana)
			{
			    SendClientMessage(playerid,-1, "Você não tem tudo isso!");
			    return true;
			}
			if(depgrana < 0)return SendClientMessage(playerid, -1, "Valor inválido!");
			if(depgrana > 0)
			{
			    if(Player_GetMoney(playerid) >= depgrana)
			    {
					Player_RemoveMoney(playerid, depgrana);
					OrgInfo_SetMoney(org, OrgInfo_GetMoney(org) + depgrana);

		    		format(string,sizeof(string),"Você Depositou $%d, o Novo Saldo é de $%d",depgrana,CofreOrg[org][orgDinheiro]);
		    		SendClientMessage(playerid,COLOR_YELLOW,string);
		    		return true;
	    		}
		    }
			return true;
		}
	    return true;
	}
	else if(dialogid == 18)
	{
		if(response >= 1)
		{
		    new org = GetPlayerOrg(playerid);
		    new sacgrana = strval(inputtext);
			if(sacgrana > CofreOrg[org][orgDinheiro])
			{
			    SendClientMessage(playerid,-1, "Sua Organização não tem tudo isso!");
			    return true;
			}
			if(PlayerInfo[playerid][pCargo] < SUB_LIDER_2)
			{
			    SendClientMessage(playerid,-1, "Somente Líder e Sub-Líder Podem Sacar Dinheiro");
			    return true;
			}
			if(sacgrana > 0)
			{
			    if(sacgrana <= CofreOrg[org][orgDinheiro])
			    {
		    		format(string,sizeof(string),"Mesmo sendo SUB ou LIDER,não é autorizado sacar dinheiro da HQ!",sacgrana,CofreOrg[org][orgDinheiro]);
		    		SendClientMessage(playerid,COLOR_GRAD,string);
		    		return true;
	    		}
		    }
			return true;
		}
	    return true;
	}
	else if(dialogid == 21)
	{
		if (!response) return true;

		new materiaisQuantia = strval(inputtext), idOrg = GetPlayerOrg(playerid);

		new saldoMateriais = GetPlayerItemTypeAmount(playerid, ITEM_TYPE_MATERIAL);
		if (saldoMateriais < materiaisQuantia) return SendClientMessage(playerid, -1, "Você não tem essa quantia em materiais.");

		if (!materiaisQuantia && materiaisQuantia < 1) return SendClientMessage(playerid, -1, "A quantia que você digitou é inválida.");

		if ((CofreOrg[idOrg][Materiais] + materiaisQuantia) > 2000 && !CofreOrg[idOrg][orgVIP])
		{
		    format(string,sizeof(string), "Sua organização limita %sg/2,000g de materiais.", getFormatText(CofreOrg[idOrg][Materiais]));
		    SendClientMessage(playerid, -1, string);
		    SendClientMessage(playerid, -1, "Caso sua organização for VIP, ela terá um limite de 4.000.");
			return true;
		}
		else if ((CofreOrg[idOrg][Materiais] + materiaisQuantia) > 4000 && CofreOrg[idOrg][orgVIP])
		{
		    format(string,sizeof(string), "Sua organização limita %sg/4,000g de materiais.", getFormatText(CofreOrg[idOrg][Materiais]));
		    SendClientMessage(playerid, -1, string);
			return true;
		}

		RemovePlayerItemTypeAmount(playerid, ITEM_TYPE_MATERIAL, materiaisQuantia);
		depositar_CofreOrgMat(idOrg, materiaisQuantia);

		format(string,sizeof(string), "%s: {D9A067}%s depositou %sg de materiais. {EAE5E1}(%sg de materiais no cofre)", PlayerName[playerid], getFormatText(materiaisQuantia), getFormatText(CofreOrg[idOrg][Materiais]));
		SendMembersMessage(GetPlayerOrg(playerid), GetPlayerColor(playerid), string);

		return true;
	}

	else if(dialogid == 22)
	{
		if(response >= 1)
		{
		    new org = GetPlayerOrg(playerid);
		    new depmac = strval(inputtext);
		    new pMaconha = GetPlayerItemTypeAmount(playerid, ITEM_TYPE_MACONHA);
			if(pMaconha < depmac)
			{
			    SendClientMessage(playerid,-1, "Você não tem tudo isso!");
			    return true;
			}
			if(depmac > 0)
			{
			    if(pMaconha >= depmac)
			    {
					RemovePlayerItemTypeAmount(playerid, ITEM_TYPE_MACONHA, depmac);
					OrgInfo_SetMarihuana(org, OrgInfo_GetMarihuana(org) + depmac);
		    		format(string,sizeof(string),"Você Depositou %d de Maconha, o Novo Saldo de Maconha é de %d",depmac,CofreOrg[org][Maconha]);
		    		SendClientMessage(playerid,COLOR_GRAD,string);
		    		return true;
	    		}
		    }
			return true;
		}
	    return true;
	}
	else if(dialogid == 23)
	{
	    if(response == 0)
		{
			return true;
		}
		if(response >= 1)
		{
		    new org = GetPlayerOrg(playerid);
		    new sacmac = strval(inputtext);
			if(sacmac > CofreOrg[org][Maconha])
			{
			    SendClientMessage(playerid,-1, "Sua Organização não tem tudo isso!");
			    return true;
			}
			if(PlayerInfo[playerid][pCargo] < 5)
			{
			    SendClientMessage(playerid,-1, "Somente Lider e Sub-Lider Podem Sacar Maconha");
			    return true;
			}
			if(sacmac > 0)
			{
			    if(sacmac <= CofreOrg[org][Maconha])
			    {
					givePlayerItem(playerid, ITEM_TYPE_MACONHA, 2891, sacmac, "Maconha");
					OrgInfo_SetMarihuana(org, OrgInfo_GetMarihuana(org) - sacmac);
		    		format(string,sizeof(string),"Você Sacou %d de Maconha, o Novo Saldo de Maconha é de %d",sacmac,CofreOrg[org][Maconha]);
		    		SendClientMessage(playerid,COLOR_GRAD,string);
		    		return true;
	    		}
		    }
			return true;
		}
	    return true;
	}
	else if(dialogid == 24)
	{
		if(response >= 1)
		{
      		new org = GetPlayerOrg(playerid);
		    new depcoca = strval(inputtext);
		    new pCocaina = GetPlayerItemTypeAmount(playerid, ITEM_TYPE_COCAINA);
			if(pCocaina < depcoca)
			{
			    SendClientMessage(playerid,-1, "Você não tem tudo isso!");
			    return true;
			}
			if(depcoca > 0)
			{
			    if(pCocaina >= depcoca)
			    {
					RemovePlayerItemTypeAmount(playerid, ITEM_TYPE_COCAINA, depcoca);
					OrgInfo_SetCocaine(org, OrgInfo_GetCocaine(org) + depcoca);
		    		format(string,sizeof(string),"Você Depositou %d de Cocaina, o Novo Saldo de Cocaina é de %d",depcoca,CofreOrg[org][Cocaina]);
		    		SendClientMessage(playerid,COLOR_GRAD,string);
		    		return true;
	    		}
		    }
			return true;
		}
	    return true;
	}

	else if(dialogid == 25)
	{
		if(response >= 1)
		{
      		new org = GetPlayerOrg(playerid);
		    new saccoca = strval(inputtext);
			if(saccoca > CofreOrg[org][Cocaina])
			{
			    SendClientMessage(playerid,-1, "Sua Organização não tem tudo isso!");
			    return true;
			}
			if(PlayerInfo[playerid][pCargo] < SUB_LIDER_2)
			{
			    SendClientMessage(playerid,-1, "Somente Líder e Sub-Líder Podem Sacar Cocaína");
			    return true;
			}
			if(saccoca > 0)
			{
			    if(saccoca <= CofreOrg[org][Cocaina])
			    {
					givePlayerItem(playerid, ITEM_TYPE_COCAINA, 1575, saccoca, "Cocaina");
					OrgInfo_SetCocaine(org, OrgInfo_GetCocaine(org) - saccoca);
		    		format(string,sizeof(string),"Você Sacou %d de Cocaína, o Novo Saldo de Cocaína é de %d", saccoca, CofreOrg[org][Cocaina]);
		    		SendClientMessage(playerid,COLOR_GRAD,string);
		    		return true;
	    		}
		    }
			return true;
		}
	    return true;
	}
	else if(dialogid == 26)
	{
		if(response >= 1)
		{
		    new org = GetPlayerOrg(playerid);
		    new depcrac = strval(inputtext);
		    new pCrack = GetPlayerItemTypeAmount(playerid, ITEM_TYPE_CRACK);
			if(pCrack < depcrac)
			{
			    SendClientMessage(playerid,-1, "Você não tem tudo isso!");
			    return true;
			}
			if(depcrac > 0)
			{
			    if(pCrack >= depcrac)
			    {
					RemovePlayerItemTypeAmount(playerid, ITEM_TYPE_CRACK, depcrac);
					OrgInfo_SetCrack(org, OrgInfo_GetCrack(org) + depcrac);
		    		format(string,sizeof(string),"Você Depositou %d de Crack, o Novo Saldo de Crack é de %d",depcrac,CofreOrg[org][Crack]);
		    		SendClientMessage(playerid,COLOR_GRAD,string);
		    		return true;
	    		}
		    }
			return true;
		}
	    return true;
	}
    else if(dialogid == 8901)
	{
		TogglePlayerControllable(playerid, true);
		new CheckNumero = OrgCofre[playerid];
		MEGAString[0] = EOS;

  		if (!response)
  		{
			return ShowDialogCofreOrg(playerid);
		}
	    switch (listitem)
		{
		    case 0:
		    {
	   			if (!OrgIsBuyMateriais(CheckNumero)) return SendClientMessage(playerid, -1, "A organização não trabalha com compra de materiais.");

			    if (!PlayerIsFabricanteMat(playerid)) return SendClientMessage(playerid, -1, "Essa área é apenas para traficantes de armas ou mafiosos.");

			    if (CofreOrg[CheckNumero][cMateriais] < 1) return SendClientMessage(playerid, -1, "A organização não fez pedido de materiais no momento.");

				format(string, sizeof string, "{D99622}Área de materiais » {DBDCE0} Você está vendendo para a: {7D8084}%s\n\n", GetNomeOrg(CheckNumero));
				strcat(MEGAString, string);

				format(string, sizeof string, "{7D8084}A organização pediu: {DBDCE0}%sg {D99622}de materiais\n\n", getFormatText(CofreOrg[CheckNumero][cMateriais]));
				strcat(MEGAString, string);

				format(string, sizeof string, "{7D8084}A organização paga: {DBDCE0}$%s {D99622}p/gramas\n\n", getFormatText(CofreOrg[CheckNumero][mMateriais]));
				strcat(MEGAString, string);

				new saldoMateriais = GetPlayerItemTypeAmount(playerid, ITEM_TYPE_MATERIAL);
				format(string, sizeof string, "{7D8084}Você possui: {DBDCE0}%sg {D99622}de materiais\n\n", getFormatText(saldoMateriais));
				strcat(MEGAString, string);

			 	strcat(MEGAString, "{00FF00}Info: {FFFFFF}Abaixo coloque a quantidade de materiais que deseja vender.\n");

				ShowPlayerDialog(playerid, 8920, DIALOG_STYLE_INPUT, "{DBDCE0}Área para venda de materiais", MEGAString, "Vender", "Retornar");

				return true;
			}
      		case 1: {
		        return SendClientMessage(playerid, -1, "Sistema inativo temporariamente");
            }
		}
	    return true;
	}

	else if (dialogid == 8920)
	{
	    new CheckNumero = OrgCofre[playerid];
	    MEGAString[0] = EOS;

	    if (!response) showDialogOrgVendas(playerid);

	    new quantidadeMateriais = strval(inputtext);

		if (!quantidadeMateriais && quantidadeMateriais < 1) return SendClientMessage(playerid, -1, "Você não digitou uma quantidade inválida.");

		new saldoMateriais = GetPlayerItemTypeAmount(playerid, ITEM_TYPE_MATERIAL);
		if (saldoMateriais < quantidadeMateriais) return SendClientMessage(playerid, -1, "Você não possui essa quantidade de materiais.");

		if (OrgInfo_GetMoney(CheckNumero) < CofreOrg[CheckNumero][mMateriais]) return SendClientMessage(playerid, -1, "A organização não pode pagar pelos materiais.");

		if (quantidadeMateriais > CofreOrg[CheckNumero][cMateriais]) return SendClientMessage(playerid, -1, "A organização não pediu essa quantidade de materiais.");

		format(string, sizeof string, "{D99622}Área de materiais » {DBDCE0} Você vendeu para: {7D8084}%s\n\n", GetNomeOrg(CheckNumero));
		strcat(MEGAString, string);

		format(string, sizeof string, "{7D8084}Foi adicionado: {DBDCE0}$%s {D99622}no seu salário do próximo PayDay\n\n", getFormatText(CofreOrg[CheckNumero][cMateriais]));
		strcat(MEGAString, string);

		format(string, sizeof string, "{7D8084}Materiais restante: {DBDCE0}%sg {D99622}de materiais\n\n", getFormatText(saldoMateriais));
		strcat(MEGAString, string);

		format(string,sizeof(string), "((Rádio do tráfico)) {FFFFFF}%s vendeu %sg de materiais para %s.", PlayerName[playerid], getFormatText(quantidadeMateriais), GetNomeOrg(CheckNumero));
		EmpregoMensagem(0xF1A439FF, string, 7); SendMembersMessage(12, 0xF1A439FF, string); SendMembersMessage(13, 0xF1A439FF, string); SendMembersMessage(24, 0xF1A439FF, string);

		format(string,sizeof(string), "» {%s}%s: {E4D88D}%s, vendeu %sg de materiais para a organização.", GetOrgColor(CheckNumero), GetNomeOrg(CheckNumero), PlayerName[playerid], getFormatText(quantidadeMateriais));
		SendMembersMessage(CheckNumero, -1, string);

		SendClientMessage(playerid, -1, "Para você ver quanto tem para receber no próximo salário use: {FFF000}/meusalario{FFFFFF}.");

		vender_CofreOrgMat(playerid, CheckNumero, quantidadeMateriais);

	   	return true;
	}

	else if (dialogid == 8850)
	{
	    new quantidadeMat = strval(inputtext);
	    new idOrg = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, idOrg);

	    if ((CofreOrg[idOrg][Materiais] + quantidadeMat) > 2000 && !CofreOrg[idOrg][orgVIP])
		{
		    format(string,sizeof(string), "Sua organização limita %sg/2,000g de materiais.", getFormatText(CofreOrg[idOrg][Materiais]));
		    SendClientMessage(playerid, -1, string);
		    SendClientMessage(playerid, -1, "Caso sua organização for VIP, ela terá um limite de 4.000.");
			return true;
		}
		else if ((CofreOrg[idOrg][Materiais] + quantidadeMat) > 4000 && CofreOrg[idOrg][orgVIP])
		{
		    format(string,sizeof(string), "Sua organização limita %sg/4,000g de materiais.", getFormatText(CofreOrg[idOrg][Materiais]));
		    SendClientMessage(playerid, -1, string);
			return true;
		}

	    if (quantidadeMat < 0 || quantidadeMat > 4000) return SendClientMessage(playerid, -1, "O pedido de materiais deve estar entre 0 a 4.000");

		pedido_MateriaisGramas(idOrg, quantidadeMat);

		if (quantidadeMat > 0)
		{
			MEGAString[0] = EOS;

			strcat(MEGAString, "{71BE5B}Pedido de materiais » {DBDCE0} Defina o valor que pagará por grama.\n\n");

			format(string, sizeof string, "{7D8084}Você está solicitando: {DBDCE0}%sg {D99622}de materiais\n\n", getFormatText(quantidadeMat));
			strcat(MEGAString, string);

			strcat(MEGAString, "{FF6347}Observação: {7D8084}Informe abaixo o valor que a organização pagará por grama.\n");

			ShowPlayerDialog(playerid, 8855, DIALOG_STYLE_INPUT, "{DBDCE0}Pedido de materiais", MEGAString, "Pedir", "Retornar");
		}
		else return SendClientMessage(playerid, -1, "Você cancelou o pedido de materiais no momento...");

		return true;
	}

	else if(dialogid == 8855)
	{
	    new valorMat = strval(inputtext);
	    new idOrg = GetPlayerOrg(playerid);

	   	if (!response) showDialogDefinicoes(playerid, idOrg);

     	if (valorMat < 2 || valorMat > 10000) return SendClientMessage(playerid, -1, "O valor por grama de materiais deve estar entre $2 a $10.000");

		pedido_MateriaisPreco(idOrg, valorMat);

	 	format(string,sizeof(string), "((Rádio do tráfico)) {FFFFFF}%s está pedindo %sg de materiais e paga $%s por grama.", GetNomeOrg(idOrg), getFormatText(CofreOrg[idOrg][cMateriais]), getFormatText(valorMat));
	  	EmpregoMensagem(0xF1A439FF, string, 7); SendMembersMessage(12, 0xF1A439FF, string); SendMembersMessage(13, 0xF1A439FF, string); SendMembersMessage(24, 0xF1A439FF, string);

		format(string,sizeof(string), "» %s: {E4D88D}%s, %s pediu %sg de materiais (pagando $%s por grama)", GetNomeOrg(idOrg), GetPlayerCargo(playerid), PlayerName[playerid], getFormatText(CofreOrg[idOrg][cMateriais]), getFormatText(valorMat));
		SendMembersMessage(idOrg, GetPlayerColor(playerid), string);

		return true;
	}

    else if(dialogid == 8971)
	{
	    if(response)
	    {
	        SetPlayerCP(playerid, 620);
	        switch(listitem)
	        {
	            case 0:
				{
				    SetPlayerCheckpoint(playerid, 1478.7834, -1783.3513, 13.5400, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}Estabelecimento do Governo{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 1:
				{
				    SetPlayerCheckpoint(playerid, 1537.3124,-1628.7273,13.3828, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Policia Militar{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 2:
				{
				    SetPlayerCheckpoint(playerid, 328.1634,-1512.4167,36.0325, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ BOPE{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 3:
				{
				    SetPlayerCheckpoint(playerid, -1346.8774,491.9250,11.2027, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Forças Armadas{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 4:
				{
				    SetPlayerCheckpoint(playerid, 1684.8771,-2098.8760,13.8343, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Aztecas{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 5:
				{
				    SetPlayerCheckpoint(playerid,2281.2393,-2364.8765,13.5469, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Hitman{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 6:
				{
				    SetPlayerCheckpoint(playerid, 649.3264,-1353.8356,13.5470, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ San News{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 7:
				{
				    SetPlayerCheckpoint(playerid, 1124.7544,-2036.9777,69.8833, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Policia Federal{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 8:
				{
				    SetPlayerCheckpoint(playerid, 224.9474, -1437.3250, 13.2924, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Máfia Italiana{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 9:
				{
				    SetPlayerCheckpoint(playerid, 664.5817,-1312.1888,13.4609, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Máfia Yakuza{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 10:
				{
				    SetPlayerCheckpoint(playerid, 2496.4561,-1668.8772,13.3438, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ G.R.O.T.A{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 11:
				{
				    SetPlayerCheckpoint(playerid, -586.4482,-1060.9926,23.4999, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Estado Islamico{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 12:
				{
				    SetPlayerCheckpoint(playerid, -201.4692, -1092.9031, 25.2115, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Familia do Norte{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 13:
				{
				    SetPlayerCheckpoint(playerid, 2808.3562,-1176.4606,25.3687, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ BAIRRO-13{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 14:
				{
				    SetPlayerCheckpoint(playerid, 2236.1865,-1452.0640,23.8358, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ P.C.C{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 15:
				{
				    SetPlayerCheckpoint(playerid, 2770.6521,-1628.1273,12.1775, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ The Triad{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 16:
				{
				    SetPlayerCheckpoint(playerid, 1684.5236,- 1343.3313, 17.4368, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Policia Civil{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 17:
				{
				    SetPlayerCheckpoint(playerid, 912.0700, -1221.2000, 16.9800, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Polícia Rodoviária Federal{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 18:
				{
				    SetPlayerCheckpoint(playerid, 475.6070, -1501.5156, 20.5379, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Cosa Nostra{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 19:
				{
				    SetPlayerCheckpoint(playerid, 2485.6860,89.4010,26.7737, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Mercenários{FFFF00}, siga a marca vermelha no mapa!");
				}
	            case 20:
				{
				    SetPlayerCheckpoint(playerid, -308.2417,1538.4569,75.5625, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Al-Qaeda{FFFF00}, siga a marca vermelha no mapa!");
				}
            	case 21:
				{
				    SetPlayerCheckpoint(playerid, 681.6184,-474.1958,16.5363, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ Warlocks{FFFF00}, siga a marca vermelha no mapa!");
				}
				case 22:
				{
				    SetPlayerCheckpoint(playerid, -50.0843, -298.3511, 5.4297, 10.0);
				    SendClientMessage(playerid, -1, "Seu GPS foi ativado em {00FFFF}HQ CORE{FFFF00}, siga a marca vermelha no mapa!");
				}
	        }
	    }
	    else
	    {
			callcmd::gps(playerid);
	    }
	    return 1;
	}

    return 0;
}

stock OrgsRoubo(playerid)
{
	switch (GetPlayerOrg(playerid)) {
		case 5,6,8,10,12,13,15,14,17,18,19,20,21,22,23,24,25,26,27,28: return true;
	}
	if (PlayerIsBandido(playerid)) return true;

	return false;
}

CALLBACK:IsAMember(playerid)
{
	switch(GetPlayerOrg(playerid))
	{
	    case 5, 8, 10, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28: return true;
	}
	return false;
}

CALLBACK:OrgIsACop(orgid)
{
	switch (orgid)
	{
	    case 1, 2, 3, 11, 16, 29, 33, 34: return true;
	}
	return false;
}

CALLBACK:OrgIsBuyMateriais(orgid)
{
	switch (orgid)
	{
		case 5, 8, 12, 13, 14, 15, 17, 18, 19, 20, 21, 24, 22, 25, 28: return true;
	}
	return false;
}

CALLBACK:IsACop(playerid)
{
	switch (GetPlayerOrg(playerid))
	{
		case 1, 2, 3, 11, 16, 29, 33, 34: return true;
	}
	return false;
}

CALLBACK:IsACopOrg(org)
{
	switch (org)
	{
		case 1, 2, 3, 11, 16, 29, 33, 34: return true;
	}
	return false;
}

// Jogador é de uma Gangue
CALLBACK:PlayerIsGang(playerid)
{
	switch (GetPlayerOrg(playerid))
	{
		case 5, 14, 17, 18, 19, 21, 26: return true;
	}
	return false;
}

// Jogador é Org Policial que vai contra Gangue
CALLBACK:PlayerIsCounterGang(playerid)
{
	switch (GetPlayerOrg(playerid))
	{
	    case 1, 2, 34: return true;
	}
	return false;
}

// Jogador é de Org Mafiosa
CALLBACK:PlayerIsMafia(playerid)
{
	switch (GetPlayerOrg(playerid))
	{
	    case 12, 13, 24: return true;
	}
	return false;
}

// Jogador é de um Policia contra Máfia
CALLBACK:PlayerIsCounterMafia(playerid)
{
	switch (GetPlayerOrg(playerid))
	{
	    case 11, 34: return true;
	}
	return false;
}

// Jogador é de Org Mercenário
stock PlayerIsMercenario(playerid)
{
	switch (GetPlayerOrg(playerid)) {
		case 25, 28, 33: return true;
	}
	return false;
}

CALLBACK:PlayerIsTerror(playerid)
{
	switch (GetPlayerOrg(playerid))
	{
	    case 3, 15, 20, 23: return true;
	}
	return false;
}

CALLBACK:IsALixeiroCar(carid)
{
    if (carid >= CarrosLixeiros[0] && carid <= CarrosLixeiros[sizeof(CarrosLixeiros)-1])
		return true;

	return false;
}

CALLBACK:IsAPilotoCar(carid)
{
    if (carid >= CarrosPilotos[0] && carid <= CarrosPilotos[sizeof(CarrosPilotos)-1])
		return true;

	return false;
}

CALLBACK:IsAMedicoCar(carid)
{
    if (carid >= CarrosMedicos[0] && carid <= CarrosMedicos[sizeof(CarrosMedicos)-1])
		return true;

	return false;
}

CALLBACK:IsAMecanicoCar(carid)
{
    if (carid >= CarrosMecanicos[0] && carid <= CarrosMecanicos[sizeof(CarrosMecanicos)-1])
		return true;

	return false;
}

stock NomeORG(playerid)
{
	new name[35];
	new idorg = GetPlayerOrg(playerid);
	switch(idorg)
	{
	    case 1:name = "Policia Militar";
	    case 2:name = "BOPE";
	    case 3:name = "Forças Armadas";
	    case 4:name = "Medicos";
	    case 5:name = "Amigo dos Amigos";
	    case 6:name = "Bloods";
	    case 7:name = "Governo";
	    case 8:name = "Hitmans";
	    case 9:name = "San News";
	    case 10:name = "Iluminati";
	    case 11:name = "Policia Federal";
	    case 12:name = "Mafia Italiana";
	    case 13:name = "Mafia Yakuza";
	    case 14:name = "G.R.O.T.A";
	    case 15:name = "Estado Islamico";
	    case 16:name = "P.R.F";
	    case 17:name = "Familia do Norte";
	    case 18:name = "BAIRRO-13";
		case 19:name = "C.V";
	    case 20:name = "Al-Qaeda";
	    case 21:name = "P.C.C";
	    case 22:name = "The Triad";
	    case 24:name = "Máfia Cosa Nostra";
	    case 25:name = "Sons Of Anarchy";
	    case 28:name = "Warlocks";
	    case 33:name = "Policia Civil";
	    case 34:name = "CORE";
	    default:name = "Civil";
	}
	return name;
}

stock GetNomeOrg(idorg)
{
	new name[35];
	switch(idorg)
	{
	    case 1:name = "Policia Militar";
	    case 2:name = "BOPE";
	    case 3:name = "Forças Armadas";
	    case 5:name = "Amigo dos Amigos";
	    case 7:name = "Governo";
	    case 8:name = "Hitmans";
	    case 9:name = "San News";
	    case 11:name = "Policia Federal";
	    case 12:name = "Mafia Italiana";
	    case 13:name = "Mafia Yakuza";
	    case 14:name = "G.R.O.T.A";
	    case 15:name = "F.A.R.C";
	    case 16:name = "Policia Rodoviaria Federal";
	    case 17:name = "Familia do Norte";
	    case 18:name = "BAIRRO-13";
		case 19:name = "C.V";
	    case 20:name = "Al-Qaeda";
	    case 21:name = "P.C.C";
	    case 22:name = "The Triad";
	    case 24:name = "Máfia Cosa Nostra";
	    case 25:name = "Sons Of Anarchy";
	    case 28:name = "Warlocks";
	    case 33:name = "Policia Civil";
	    case 34:name = "CORE";
	    case 998:name = "Nenhuma";
	    case 999:name = "Administração";
	    default:name = "Civil";
	}
	return name;
}

CALLBACK:LoadSalarioOrg()
{
	new idorg = 1;
	
	while (idorg < sizeof(CofreOrg))
	{
		CofreOrg[idorg][salarioc1] = 1000;
		CofreOrg[idorg][salarioc1] = CofreOrg[idorg][salarioc1] > MAX_SALARIO_C1 ? (MAX_SALARIO_C1) : (CofreOrg[idorg][salarioc1]);

		CofreOrg[idorg][salarioc2] = 3000;
		CofreOrg[idorg][salarioc2] = CofreOrg[idorg][salarioc2] > MAX_SALARIO_C2 ? (MAX_SALARIO_C2) : (CofreOrg[idorg][salarioc2]);

		CofreOrg[idorg][salarioc3] = 5000;
		CofreOrg[idorg][salarioc3] = CofreOrg[idorg][salarioc3] > MAX_SALARIO_C3 ? (MAX_SALARIO_C3) : (CofreOrg[idorg][salarioc3]);

		CofreOrg[idorg][salarioc4] = 7000;
		CofreOrg[idorg][salarioc4] = CofreOrg[idorg][salarioc4] > MAX_SALARIO_C4 ? (MAX_SALARIO_C4) : (CofreOrg[idorg][salarioc4]);

		CofreOrg[idorg][salarioc5] = 10000;
		CofreOrg[idorg][salarioc5] = CofreOrg[idorg][salarioc5] > MAX_SALARIO_C5 ? (MAX_SALARIO_C5) : (CofreOrg[idorg][salarioc5]);

		CofreOrg[idorg][salariolider] = 15000;
		CofreOrg[idorg][salariolider] = CofreOrg[idorg][salariolider] > MAX_SALARIO_C6 ? (MAX_SALARIO_C6) : (CofreOrg[idorg][salariolider]);
		idorg ++;
	}
	return true;
}

stock DefinirSalarioc1(org,valor)
{
	CofreOrg[org][salarioc1] = valor;
	return true;
}
stock DefinirSalarioc2(org,valor)
{
	CofreOrg[org][salarioc2] = valor;
	return true;
}
stock DefinirSalarioc3(org,valor)
{
	CofreOrg[org][salarioc3] = valor;
	return true;
}
stock DefinirSalarioc4(org,valor)
{
	CofreOrg[org][salarioc4] = valor;
	return true;
}
stock DefinirSalarioc5(org,valor)
{
	CofreOrg[org][salarioc5] = valor;
	return true;
}
stock DefinirSalarioc6(org,valor)
{
	CofreOrg[org][salariolider] = valor;
	return true;
}

stock PagarICMS(valor) {
	new governo = floatround((valor * ICMS) / 100, floatround_floor);
	new liquido = valor - governo;
	adicionarDinheiroGoverno(valor);
	return liquido;
}

stock adicionarDinheiroGoverno(valor) {
	OrgInfo_SetMoney(ID_ORG_GOVERNO, OrgInfo_GetMoney(ID_ORG_GOVERNO) + valor);
}

stock removerDinheiroGoverno(valor) {
	OrgInfo_SetMoney(ID_ORG_GOVERNO, OrgInfo_GetMoney(ID_ORG_GOVERNO) - valor);
}

CALLBACK:pedido_MateriaisGramas(idorg, valor)
{
	CofreOrg[idorg][cMateriais] = valor;
}

CALLBACK:pedido_MateriaisPreco(idorg, valor)
{
	CofreOrg[idorg][mMateriais] = valor;
	return true;
}

CALLBACK:vender_CofreOrgMat(playerid, idorg, valor)
{
	RemovePlayerItemTypeAmount(playerid, ITEM_TYPE_MATERIAL, valor);
	PlayerInfo[playerid][pSalario] += (CofreOrg[idorg][mMateriais] * valor);
	OrgInfo_SetMoney(idorg, OrgInfo_GetMoney(idorg) - (CofreOrg[idorg][mMateriais] * valor));

	CofreOrg[idorg][Materiais] += valor;
	CofreOrg[idorg][cMateriais] -= valor;

	return true;
}

CALLBACK:depositar_CofreOrgMat(idorg, valor)
{
	CofreOrg[idorg][Materiais] += valor;

	return true;
}

CALLBACK:sacar_CofreOrgMat(idorg, valor)
{
	CofreOrg[idorg][Materiais] = valor;
	return true;
}

CALLBACK:showDialogOrgVendas(playerid)
{
	if (!PlayerIsFabricanteMat(playerid)) return SendClientMessage(playerid, -1, "Você precias ser fabricante de drogas ou armas para acessar.");

	new string[128];
	MEGAString[0] = EOS;

	TogglePlayerControllable(playerid, true);

  	strcat(MEGAString, "Produto\tQuantidade\tValor que pagará\n");

	format(string, sizeof string, "{FFFFFF}Vender » {965302}Materiais\t{9C9C9C}%sg\t{5ED661}$%s por grama\n", getFormatText(CofreOrg[OrgCofre[playerid]][cMateriais]), getFormatText(CofreOrg[OrgCofre[playerid]][mMateriais]));
	strcat(MEGAString, string);
    format(string, sizeof string, "{FFFFFF}Vender » {3A853D}Maconha\t{9C9C9C}%sg\t{5ED661}$%s por grama\n", getFormatText(CofreOrg[OrgCofre[playerid]][cMaconha]), getFormatText(CofreOrg[OrgCofre[playerid]][mMaconha]));
	strcat(MEGAString, string);

	ShowPlayerDialog(playerid, 8901, DIALOG_STYLE_TABLIST_HEADERS, "{D53F35}Área de vendedores", MEGAString, "Prosseguir", "Retornar");

	return true;
}

// ----------------------------------------------------------------------------------------------------------------

CALLBACK: weaponsOrganizacao(playerid, orgid)
{
    if (!GetPlayerOrg(playerid)) return SendClientMessage(playerid,-1, "Você não é membro de uma organização.");

   	if (gettime() < GetPVarInt(playerid, #varFlood_equiparplayer)) return SendClientMessage(playerid, -1, "Você não pode usar essa função com tanta frequencia.");

	if (PlayerInfo[playerid][pCargo] < 1) return SendClientMessage(playerid,-1, "Você precisa ser cargo 1 ou maior para pegar equipamentos.");
	
	new string[128];

	if (!CofreOrg[orgid][orgVIP] && OrgIsBuyMateriais(orgid))
	{
		//new totalMunicoes = (CofreOrg[orgid][municaoArma][0] + CofreOrg[orgid][municaoArma][1] + CofreOrg[orgid][municaoArma][2] + CofreOrg[orgid][municaoArma][3] + CofreOrg[orgid][municaoArma][4] + CofreOrg[orgid][municaoArma][5]);
		new somaMateriais = (CofreOrg[orgid][Materiais] - 500/20);

		if (CofreOrg[orgid][Materiais] < 500/20)
		{
			format(string, sizeof string, "A sua organização está sem materias (Restam: %d materiais no cofre)", CofreOrg[orgid][Materiais]);
			SendClientMessage(playerid, -1, string);

			SetPlayerHealth(playerid, 100);
			SetPlayerArmour(playerid, 100);

			ResetPlayerWeapons(playerid);
			GivePlayerWeapon(playerid, WEAPON_DEAGLE, 80);
			GivePlayerWeapon(playerid, WEAPON_AK47, 250);
			GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 20);

			SendClientMessage(playerid, -1, "Você recebeu apenas 3 armas esenciais, compre materiais para a organização!");
			return true;
 		}

		SetPlayerHealth(playerid, 100);         // Vida 100 por cento
		SetPlayerArmour(playerid, 100);         // Colete 100 por cento

		ResetPlayerWeapons(playerid);           // Resetar as Armas
		GivePlayerWeapon(playerid, WEAPON_BAT, 1);
		GivePlayerWeapon(playerid, WEAPON_DEAGLE, 150);
		GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 20);
		GivePlayerWeapon(playerid, WEAPON_AK47, 170);

	   	sacar_CofreOrgMat(orgid, somaMateriais);

	   	format(string, sizeof(string), "» %s: {E4D88D}Você se equipou e gastou (%sg de materiais da HQ)", NomeORG(playerid), getFormatText(500/20));
		SendClientMessage(playerid, GetPlayerColor(playerid), string);

		SetPVarInt(playerid, #varFlood_equiparplayer, gettime() + 15);
   	}
   	else if (CofreOrg[orgid][orgVIP] && OrgIsBuyMateriais(orgid))
   	{
		new somaMateriais = (CofreOrg[orgid][Materiais] - 500/25);

		if (CofreOrg[orgid][Materiais] < 500/25)
		{
			format(string, sizeof string, "A sua organização está sem materias (Restam: %d materiais no cofre)", CofreOrg[orgid][Materiais]);
			return SendClientMessage(playerid, -1, string);
 		}

		SetPlayerHealth(playerid, 100);         // Vida 100 por cento
		SetPlayerArmour(playerid, 100);         // Colete 100 por cento

		ResetPlayerWeapons(playerid);           // Resetar as Armas
		GivePlayerWeapon(playerid, WEAPON_KNIFE, 1);
		GivePlayerWeapon(playerid, WEAPON_DEAGLE, 150);
		GivePlayerWeapon(playerid, WEAPON_MP5, 160);
		GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 20);
		GivePlayerWeapon(playerid, WEAPON_M4, 170);
		GivePlayerWeapon(playerid, WEAPON_SNIPER, 25);

	   	sacar_CofreOrgMat(orgid, somaMateriais);

	   	format(string, sizeof(string), "» %s: {E4D88D}Você se equipou e gastou (%sg de materiais da HQ)", NomeORG(playerid), getFormatText(500/25));
		SendClientMessage(playerid, GetPlayerColor(playerid), string);

		SetPVarInt(playerid, #varFlood_equiparplayer, gettime() + 15);
   	}
   	else
   	{
		SetPlayerHealth(playerid, 100);         // Vida 100 por cento
		SetPlayerArmour(playerid, 100);         // Colete 100 por cento

		ResetPlayerWeapons(playerid);           // Resetar as Armas
		GivePlayerWeapon(playerid, WEAPON_KNIFE, 1);
		GivePlayerWeapon(playerid, WEAPON_DEAGLE, 150);
		GivePlayerWeapon(playerid, WEAPON_MP5, 160);
		GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 20);
		GivePlayerWeapon(playerid, WEAPON_M4, 170);
		GivePlayerWeapon(playerid, WEAPON_SNIPER, 25);

	   	format(string, sizeof(string), "» %s: {E4D88D}Você se equipou e sua HQ recebe armas do Governo.", NomeORG(playerid));
		SendClientMessage(playerid, GetPlayerColor(playerid), string);

		SetPVarInt(playerid, #varFlood_equiparplayer, gettime() + 15);
   	}

	if(GetPVarInt(playerid, "AntiSpawnKill")) {
		SetPVarInt(playerid, "AntiSpawnKill", 0);
	}
   	return true;
}

CMD:darcaixaorgbns1(playerid, params[])
{
	new string[128];

	if (Admin_GetNivel(playerid) < SUPERVISOR) return SendClientMessage(playerid, -1, "	Você não tem autorização para usar esse comando.");

	if (!Staff_GetWorking(playerid)) return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

	if (sscanf(params, "u", params[0])) return SendClientMessage(playerid, -1, "Modo de uso: /darcaixaorgbps1 (id do jogador)");

	if (IsPlayerConnected(params[0]))
	{
		if (Player_Logado(params[0]))
		{
			GiftBox_Give(params[0], ITEM_TYPE_ORGMES, false);
			
			format(string, 128, "Premiação » %s deu {556B2F}Caixa Organização do Mês {FFFFFF}para {00BFFF}%s {FFFFFF}(%s)", PlayerName[playerid], PlayerName[params[0]], NomeORG(params[0]));
			SendClientMessageToAll(-1, string);

			server_log("caixa_org", string);
		} else {
			return SendClientMessage(playerid, -1, "O jogador não está logado no servidor.");
		}
	} else {
		return SendClientMessage(playerid, -1, "Este jogador não está conectado no servidor.");
	}

	return 1;
}


// Caixa Destaque Staff
CMD:darcaixastaffbns1(playerid, params[])
{
	new string[128];

	if (Admin_GetNivel(playerid) < DIRETOR) return SendClientMessage(playerid, -1, "	Você não tem autorização para usar esse comando.");

	if (!Staff_GetWorking(playerid)) return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

	if (sscanf(params, "u", params[0])) return SendClientMessage(playerid, -1, "Modo de uso: /darcaixastaffbns1 (id do jogador)");

	if (IsPlayerConnected(params[0]))
	{
		if (Player_Logado(params[0]))
		{
			GiftBox_Give(params[0], ITEM_TYPE_CAIXASTAFF, false);
			
			format(string, 128, "Premiação » %s, %s deu {FF1493}Caixa Destaque Staff {FFFFFF}para {00BFFF}%s.", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[params[0]]);
			SendClientMessageToAll(-1, string);

			server_log("caixa_staff", string); // Caso houver abuso da parte de algum administrador, terá nos logs. (Necessário criar um log para Caixas da Equipe do Servidor)
		} else {
			return SendClientMessage(playerid, -1, "O jogador não está logado no servidor.");
		}
	} else {
		return SendClientMessage(playerid, -1, "Este jogador não está conectado no servidor.");
	}

	return 1;
}

// Caixa Admin do Mês
CMD:darcaixamesbns1(playerid, params[])
{
	new string[128];

	if (Admin_GetNivel(playerid) < DIRETOR) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!Staff_GetWorking(playerid)) 
		return SendClientMessage(playerid, -1, "Você não pode usar este comando, pois não está em modo trabalho!");

	if (sscanf(params, "u", params[0])) 
		return SendClientMessage(playerid, -1, "Modo de uso: /darcaixamesbns1 (id do jogador)");

	if (IsPlayerConnected(params[0]))
	{
		if (Player_Logado(params[0]))
		{
			GiftBox_Give(params[0], ITEM_TYPE_CAIXAMESADM, false);
			
			format(string, 128, "Premiação » %s, %s deu {FFFF00}Caixa Admin do Mês {FFFFFF}para {00BFFF}%s.", Staff_GetPositionName(playerid), PlayerName[playerid], PlayerName[params[0]]);
			SendClientMessageToAll(-1, string);

			server_log("caixa_mes", string);
		} else {
			return SendClientMessage(playerid, -1, "O jogador não está logado no servidor.");
		}
	} else {
		return SendClientMessage(playerid, -1, "Este jogador não está conectado no servidor.");
	}

	return 1;
}

CMD:editarorg(playerid, params[])
{
	new string[128], orgid, grana;

	if (Admin_GetNivel(playerid) < DONO) return SendClientMessage(playerid, -1, "	Você não tem autorização para usar esse comando.");

	if (sscanf(params, "dd", orgid, grana)) return SendClientMessage(playerid, -1, "Modo de uso: /editarorg (id da organização) (grana)");

	format(string, 128, "AdmCmd: %s editou o dinheiro da ORG %s para $%s.", PlayerName[playerid], GetNomeOrg(orgid), getFormatText(grana));
	Staff_ChatToAll(COLOR_LIGHTRED, string, BETA_TESTER);
	server_log("cofre_org", string);

	OrgInfo_SetMoney(orgid, grana);
	return 1;
}
