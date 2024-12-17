#if defined _inc_jobs_system
	#endinput
#endif
#define _inc_jobs_system

// Includes necess�rias
#include < YSI_Coding\y_hooks >

#include <jobs_spawn>

enum JobMenuEnum {
	jmID,
	jmName[64],
	jmLevel,
	jmType,
	jmRequirements[64],
	Float:jmPos[3],
	Float:jmAngle
};

static const JobMenuConfig[][JobMenuEnum] = {
	{ID_JOB_LIXEIRO, "Gari", 1, 0, "Carteira de Motorista", {2198.5359, -2010.0414, 13.5469}, 93.2263},
	{ID_JOB_TAXISTA, "Taxista", 1, 0, "Carteira de Motorista", {1564.1434, -2228.2656, 13.5547}, 58.8197},
	{ID_JOB_MEDICO, "M�dico", 1, 0, "Carteira de Motorista", {1164.6228, -1326.4603, -44.2836}, 272.3499},
	{ID_JOB_CAMINHONEIRO, "Caminhoneiro", 1, 0, "Carteira de Motorista", {1375.9441, 1057.7214, 10.8203}, 271.5050},
	{ID_JOB_DELIVERYMAN, "Entregador de Pizza", 1, 0, "Carteira de Motorista", {2098.4106, -1812.5846, 13.3828}, 177.3905},
	{ID_JOB_BANDIDO, "Bandido", 1, 1, "--------", {0.00, 0.00, 0.00}, 0.00},
	{ID_JOB_VENDEDOR_ARMAS, "Fabricante de Materiais", 1, 1, "--------", {2846.3477, 976.9812, 10.7500}, 93.2263},
	{ID_JOB_ADVOGADO, "Advogado", 2, 0, "--------", {1739.2667, -1583.4945, 14.1584}, 93.2263},
	{ID_JOB_DETETIVE, "Detetive", 2, 0, "--------", {0.00, 0.00, 0.00}, 0.00},
	{ID_JOB_MINERADOR, "Minerador", 3, 0, "--------", {1003.9560, -91.6045, 22.4495}, 28.0772},
	{ID_JOB_MECANICO, "Mec�nico", 3, 0, "--------", {2142.0698, -1729.8184, 13.5592}, 164.4512},
	{ID_JOB_FAZENDEIRO, "Fazendeiro", 3, 0, "--------", {-95.3570, -26.0419, 3.1172}, 66.6228},
	{ID_JOB_FIREFIGHTER, "Bombeiro", 4, 0, "--------", {957.3861, -1747.2125, 19.3432}, 180.000},
	{ID_JOB_DESIGNER_INTERIORES, "Designer de interiores", 4, 0, "--------", {0.00, 0.00, 0.00}, 0.00}
};

enum JobSpawnEnum {
	Float:jsPos[3],
	Float:jsAngle
}


// Nome do emprego
stock GetJobName(jobid)
{
	new string[30];

	switch (jobid)
	{
		case ID_JOB_DETETIVE: 
			string = "Detetive";
		case ID_JOB_ADVOGADO: 
			string = "Advogado";
		case ID_JOB_CARTEIRO: 
			string = "Carteiro";
		case ID_JOB_TAXISTA:
			string = "Taxista";
		case ID_JOB_MEDICO:
			string = "M�dico";
		case ID_JOB_MINERADOR:
			string = "Minerador";
		case ID_JOB_MECANICO:
			string = "Mec�nico";
		case ID_JOB_FAZENDEIRO:
			string = "Fazendeiro";
		case ID_JOB_VENDEDOR_ARMAS: 
			string = "Fabricante de Materiais";
		case ID_JOB_BANDIDO: 
			string = "Bandido";
		case ID_JOB_CAMINHONEIRO: 
			string = "Caminhoneiro";
		case ID_JOB_LIXEIRO: 
			string = "Lixeiro";
		case ID_JOB_DESIGNER_INTERIORES: 
			string = "Designer de Interiores";
		case ID_JOB_PILOTO:
			string = "Piloto";
		case ID_JOB_FIREFIGHTER:
			string = "Bombeiro";
		case ID_JOB_DELIVERYMAN:
			string = "Entregador de Pizza";
		default: 
			string = "Desempregado";
	}
	return string;
}

#include <detetive>
#include <police>

stock HasPlayerJob(playerid, jobid) {
	return PlayerInfo[playerid][pEmprego] == jobid || PlayerInfo[playerid][pEmprego2] == jobid;
}

stock Player_HaveJob(playerid) {
	return PlayerInfo[playerid][pEmprego] || PlayerInfo[playerid][pEmprego2];
}

stock IsPlayerWorking(playerid) {
	return EmpregoDuty[playerid] == 2;
}

stock TogglePlayerWorking(playerid) {
	EmpregoDuty[playerid] = IsPlayerWorking(playerid) ? 0 : 2;
}

//----------------------------------{Numero Emprego}-----------------------------------------------

CMD:atenderchamado(playerid, params[])
{
	if (!PlayerIsMecanico(playerid) && !PlayerIsTaxista(playerid)) 
        return SendClientMessage(playerid, -1, "Voc� n�o � mec�nico ou taxista.");

	new id;
	if (sscanf(params, "u", id))
	{
        if(PlayerIsTaxista(playerid))
	        ListarChamadosTaxi(playerid);
        else if(PlayerIsMecanico(playerid))
            ListarChamadosMecanico(playerid);

		return SendClientMessage(playerid, -1, "Modo de uso: /atenderchamado (id do jogador) | Escolha um jogador da lista.");
	}
	
	if (!IsPlayerConnected(id) || !Player_Logado(id)) 
        return SendClientMessage(playerid, -1, "O jogador n�o est� conectado/logado no servidor.");

	if (id == playerid) 
        return SendClientMessage(playerid, -1, "Voc� n�o pode atender voc� mesmo!");
	
    if(PlayerIsTaxista(playerid)) {
        DarPropostaTaxi(playerid, id);
    }
    else if(PlayerIsMecanico(playerid)) {
        DarPropostaMecanico(playerid, id);
    }
	return true;
}


CMD:empregos(playerid, params[])
{
	if (!Admin_GetNivel(playerid)) return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para usar esse comando.");

	MEGAString[0] = EOS;
	strcat(MEGAString, "Nome do Emprego\tID\n");

	for(new i = 0; i < sizeof(JobMenuConfig); i++) {
		FormatCat(MEGAString, "{FFFFFF}%s\t%d\n", JobMenuConfig[i][jmName], JobMenuConfig[i][jmID]);
	}
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "Empregos", MEGAString, "Fechar", "");
	return true;
}


hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == 80) {
		if (!response)
			return SendClientMessage(playerid, -1, "Voc� cancelou o menu de empregos.");

		switch (listitem)
		{
			case 0: ShowHelpJob(playerid, ID_JOB_NONE);
			case 1: ShowHelpJob(playerid, ID_JOB_DETETIVE);
			case 2: ShowHelpJob(playerid, ID_JOB_DESIGNER_INTERIORES);
			case 3: ShowHelpJob(playerid, ID_JOB_BANDIDO);
			case 4: ShowHelpJob(playerid, ID_JOB_VENDEDOR_ARMAS);
			case 5: ShowHelpJob(playerid, ID_JOB_ADVOGADO);
			case 6: ShowHelpJob(playerid, ID_JOB_CAMINHONEIRO);
			case 7: ShowHelpJob(playerid, ID_JOB_LIXEIRO);
			case 8: ShowHelpJob(playerid, ID_JOB_TAXISTA);
			case 9: ShowHelpJob(playerid, ID_JOB_MEDICO);
			case 10: ShowHelpJob(playerid, ID_JOB_MINERADOR);
			case 11: ShowHelpJob(playerid, ID_JOB_MECANICO);
			case 12: ShowHelpJob(playerid, ID_JOB_FAZENDEIRO);
			case 13: ShowHelpJob(playerid, ID_JOB_FIREFIGHTER);
			case 14: ShowHelpJob(playerid, ID_JOB_DELIVERYMAN);
		}
	}
	else if(dialogid == 590) //dialog fazendeiro
    {
        if(!response)
			return SendClientMessage(playerid, -1, "Voc� cancelou o menu de empregos.");

		new string[128];
		if(PlayerInfo[playerid][pLevel] < JobMenuConfig[listitem][jmLevel])
			return SendClientMessage(playerid, -1, "Voc� n�o possui n�vel suficiente para ter esse emprego.");
		

		MEGAString[0] = EOS;
		format(string, sizeof(string), "\n{E9ED19}Contrato para %s\n\n", JobMenuConfig[listitem][jmName]);
		strcat(MEGAString, string);

		format(string, sizeof string, "{FFFFFF}Ol� {00FF00}%s{FFFFFF}, leia atentamente antes de assinar!\n\n", PlayerName[playerid]);
		strcat(MEGAString, string);

		strcat(MEGAString, "{FFFFFF}Voc� ter� que {AAAAAA}cumprir {FFFFFF}exatamente {59FA72}8 horas(payday) {FFFFFF}no trabalho antes de pedir demiss�o!\n");
		strcat(MEGAString, "{FFFFFF}Para entender tudo sobre o {59FA72}emprego{FFFFFF} ap�s assinar o {52B0EF}contrato{FFFFFF} use: /ajudaemprego\n");
		strcat(MEGAString, "{FFFFFF}Caso queira se {FF0000}demitir {FFFFFF}do emprego ap�s cumprir as {59FA72}8 horas{FFFFFF} no trabalho, use: /emprego sair\n");


		strcat(MEGAString, "\n\n\n{8B8A8A}Para aceitar o trabalho clique em 'Aceitar'.\n\n");

		ShowPlayerDialog(playerid, 2586, DIALOG_STYLE_MSGBOX, "{FFFFFF}Ag�ncia de empregos", MEGAString, "Aceitar", "Negar");
		GettingEmprego[playerid] = listitem;
	}
	else if(dialogid == 2586)
	{
	    if(!response)
		{
			GettingEmprego[playerid] = 0;
			return SendClientMessage(playerid, -1, "Voc� cancelou o emprego.");
		}
		else
		{
			new index = GettingEmprego[playerid],
				jobid = JobMenuConfig[index][jmID],
				string[128];

	    	if (PlayerInfo[playerid][pEmprego] != 0 && PlayerInfo[playerid][pVIP] < 8)
				return SendClientMessage(playerid, -1, "Voc� precisa ser S�cio Extreme para ter dois empregos, use: /emprego sair, para demitir-se.");

        	if (PlayerInfo[playerid][pEmprego] != 0 && PlayerInfo[playerid][pEmprego2] != 0)
				return SendClientMessage(playerid, -1, "Voc� possui dois empregos, use: /emprego sair.");

			if (PlayerInfo[playerid][pEmprego] != 0) {
				PlayerInfo[playerid][pEmprego2] = jobid;
			} else {
			    PlayerInfo[playerid][pEmprego] = jobid;
			}

			format(
				string, sizeof(string), 
				"Voce esta iniciando um emprego de ~y~~h~%s~w~. Use /ajuda > Empregos para ver as informacoes.",
				JobMenuConfig[index][jmName]
			);
			ShowPlayerBaloonInfo(playerid, string, 7000);

		    SendMsgF(
				playerid, COLOR_LIGHTBLUE, 
				"* Voc� acabou de adquirir um novo emprego como %s, digite /ajuda para ver os comandos!", 
				JobMenuConfig[index][jmName]
			);
            CheckConquista(playerid, Conquista_Emprego);

			PlayerPlaySound(playerid, 182, 0.0, 0.0, 0.0);
			defer timerStopSound(playerid);

			if(JobMenuConfig[index][jmPos][0] != 0.00) {
				SetPlayerPos(playerid, JobMenuConfig[index][jmPos][0], JobMenuConfig[index][jmPos][1], JobMenuConfig[index][jmPos][2]);
				SetPlayerFacingAngle(playerid, JobMenuConfig[index][jmAngle]);
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetCameraBehindPlayer(playerid);
			}
		}
		return 1;
	}
	return 0;
}

CMD:emprego(playerid, const params[])
{
	new string[128];
	new null[25];

	if(isnull(params)) {
		return SendClientMessage(playerid, -1, "Use: /emprego [pegar / sair]");
	}

	if (!strcmp(params, "pegar", true))
	{
		if (PlayerInfo[playerid][pEmprego] != 0 && PlayerInfo[playerid][pVIP] < 8)
			return SendClientMessage(playerid, -1, "Apenas 'S�cio-Extreme' pode ter 2 empregos.");

		// Verifica se o jogador est� no local
		if (!IsPlayerInRangeOfPoint(playerid, 2.0, WORKING_POS_X, WORKING_POS_Y, WORKING_POS_Z))
			return SendClientMessage(playerid, -1, "Voc� precisa ir at� a prefeitura.");

		MEGAString[0] = EOS;

		strcat(MEGAString, "#  Nome do emprego\tN�vel necess�rio\tTipo\tRequisitos\n");

		new line[128];
		for(new i = 0; i < sizeof(JobMenuConfig); i++) {
			format(
				line, sizeof(line), "{FFFFFF}%d  {AAAAAA}%s\t{FFFFFF}%d\t%s\t%s\n",
				i+1,
				JobMenuConfig[i][jmName],
				JobMenuConfig[i][jmLevel],
				JobMenuConfig[i][jmType] == 0 ? ("{FFFFFF}Honesto") : ("{EB4034}Criminoso"),
				JobMenuConfig[i][jmRequirements]
			);
			strcat(MEGAString, line);
		}

		ShowPlayerDialog(playerid, 590, DIALOG_STYLE_TABLIST_HEADERS, "{DFD136}Ag�ncia de empregos", MEGAString, "Prosseguir", "Cancelar"); //2569
	}

	else if (strfind(params, "sair", true) != -1) 
	{
		new job1 = PlayerInfo[playerid][pEmprego];
		new job2 = PlayerInfo[playerid][pEmprego2];

		if (job1 == 0 && job2 == 0)
			return SendClientMessage(playerid, -1, "Voc� j� est� desempregado.");

		new idjob;
		if (sscanf(params, "s[25]d", null, idjob))
		{
	    	SendClientMessage(playerid, -1, "Modo de uso: /emprego sair (1 ou 2)");
			
			format(string, sizeof(string), "Seu emprego 1: %s, seu emprego 2: %s.", GetJobName(job1), GetJobName(job2));
			SendClientMessage(playerid, -1, string);

	    	return 1;
		}

		if (idjob == 1) 
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Voc� saiu do seu emprego prim�rio, est� livre para empregar-se em outro.");
			PlayerInfo[playerid][pEmprego] = 0;
		} 
		else if (idjob == 2) 
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Voc� saiu do seu emprego secund�rio, est� livre para empregar-se em outro.");
			PlayerInfo[playerid][pEmprego2] = 0;
		} 
		else
		{
			SendClientMessage(playerid, -1, "Voc� precisa digitar se quer sair do emprego 1 ou 2.");
		}
		return true;
	}
	return 1;
}

// Ajuda emprego
stock ShowHelpJob(playerid, jobid)
{
	new string[128];
	MEGAString[0] = EOS;

	switch (jobid)
	{
		case ID_JOB_NONE:
		{
			// Como pegar um emprego?
			SetPlayerCheckpoint(playerid, 1478.7834,-1783.3513,13.5400, 10.0);

			SendClientMessage(playerid, -1, "Siga o local {FF0000}marcado em vermelho {FFFFFF}no mapa para pegar um emprego.");
		}
		case ID_JOB_DETETIVE:
		{
			strcat(MEGAString, "{FFFFFF}Detetive:\n");
			strcat(MEGAString, "{9C9C9C}Encontre a localiza��o de outros players\n");
			// Sal�rio � definido pelo governo
			/*format(string, sizeof(string), "{797978}Sal�rio: {AA00AA}$%s {797978}(por assassinato descoberto)\n", getFormatText(GetWageJob(ID_JOB_DETETIVE)));
			strcat(MEGAString, string);*/

			strcat(MEGAString, "\n{FFFFFF}Fun��es:\n");
			strcat(MEGAString, "	{9C9C9C}Encontrar players. (/procurar)\n");
			//strcat(MEGAString, "        {797978}N�vel 10+ |		{FFFFFF}Identificar o assassino analisando a cena do crime {FFF000}(em breve)\n");

			/*strcat(MEGAString, "{F8973F}Benef�cios por n�vel:\n");
			strcat(MEGAString, "        {797978}N�vel 1 |		{FFFFFF}Voc� tem acesso ao comando /procurar com limita��es\n");
			strcat(MEGAString, "        {797978}N�vel 2 |		{FFFFFF}Voc� ganha habilidade para poder usar o /procurar mais rapidamente\n");
			strcat(MEGAString, "        {797978}N�vel 3 |		{FFFFFF}Voc� ganha um acess�rio que representa o emprego de detetive\n");
			strcat(MEGAString, "        {797978}N�vel 4 |		{FFFFFF}Voc� ganha habilidade para poder usar o /procurar mais rapidamente\n");
			strcat(MEGAString, "        {797978}N�vel 5 |		{FFFFFF}Voc� ganha uma Caixa Surpresa Supreme para abrir ou negociar\n");
			strcat(MEGAString, "        {797978}N�vel 6 |		{FFFFFF}Voc� ganha um n�vel de b�nus do servidor\n");
			strcat(MEGAString, "        {797978}N�vel 7 |		{FFFFFF}Voc� ganha habilidade para usar o /procurar por tempo infinito\n");
			strcat(MEGAString, "        {797978}N�vel 8 |		{FFFFFF}Voc� ganha um b�nus salarial de $54.000 do servidor\n");
			strcat(MEGAString, "        {797978}N�vel 9 |		{FFFFFF}Voc� ganha uma skin do emprego de detetive de presente do invent�rio\n");
			strcat(MEGAString, "        {797978}N�vel 10 |		{FFFFFF}Voc� ganha permiss�o para usar o comando /investigar assassinato\n");*/

			strcat(MEGAString, "\n{FFFFFF}Comandos:\n");
			strcat(MEGAString, "	{DFD136}/procurar\n");
			strcat(MEGAString, "	{9C9C9C}Voc� usa o comando para encontrar um jogador.\n");
			/*strcat(MEGAString, "        {797978}2. {FFFFFF}/investigar assassinato\n");
			strcat(MEGAString, "				{9C9C9C}Voc� usa o comando para informar o assassino para a policia.");*/

			strcat(MEGAString, "\n\n {9C9C9C}--------------------------------------------------------------------------------------------------- \n");
		}
		case ID_JOB_ADVOGADO:
		{
			strcat(MEGAString, "{08C2DA}> Advogado:\n\n");

			strcat(MEGAString, "{8B8A8A}	Objetivo: {FFFFFF}Libera��o dos presos na cadeia La Sante\n");
			strcat(MEGAString, "{8B8A8A}	Ganhos: {FFFFFF}Voc� mesmo determina o valor com o seu cliente\n");
			strcat(MEGAString, "{8B8A8A}	Como trabalhar? {FFFFFF}Digite: /gps depois Locais Importantes e v� em Pris�o La Sante.\n");
			strcat(MEGAString, "{8B8A8A}	Como soltar preso? {FFFFFF}Dentro da Pris�o La Sante ter� um 'sinal branco', clique nele!\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");

		}
		case ID_JOB_VENDEDOR_ARMAS:
		{
			strcat(MEGAString, "{08C2DA}> Fabricante de Materiais:\n\n");

			strcat(MEGAString, "{8B8A8A}	Objetivo: {FFFFFF}Fabricar materiais e vender para organiza��es\n");
			strcat(MEGAString, "{8B8A8A}	Ganhos: {FFFFFF}A organiza��o vai definir, use: /materiais pedidos\n");
			strcat(MEGAString, "{8B8A8A}	Como trabalhar? {FFFFFF}Digite /materiais fabricar (pr�ximo a uma mesa de fabrica��o)\n");
			strcat(MEGAString, "{FF0000}	OBS: {356FB2}Use /materiais produtos (a frente da mesa de fabrica��o)\n");
			strcat(MEGAString, "{8B8A8A}	Como vender para ORG? {FFFFFF}Veja se ela fez pedido e v� at� o InfoOrg da mesma!\n\n");

			strcat(MEGAString, "{8B8A8A}	Atualiza��o: {FFFFFF}O emprego foi recentemente reprogramado (antigo Vendedor de armas)\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");

		}
		case ID_JOB_BANDIDO:
		{
			strcat(MEGAString, "{08C2DA}> Bandido:\n\n");

			strcat(MEGAString, "{8B8A8A}	Objetivo: {FFFFFF}Explodir Caixas e pegar o dinheiro e Explodir Pris�o La Sante\n");
			strcat(MEGAString, "{8B8A8A}	Ganhos: {FFFFFF}Os ganhos s�o aleat�rios\n");
			strcat(MEGAString, "{8B8A8A}	Como roubar caixas? {356FB2}Use: /gps > Caixas Eletronicos e v� at� algum\n");
			strcat(MEGAString, "{8B8A8A}	Como pegar explosivo? {356FB2}Use: /gps > Locais Importantes > Mercado Negro\n");
			strcat(MEGAString, "{FF0000}	OBS: {FFFFFF}Fa�a isso com alguns amigos, ou um grupo, para ser mais f�cil roubar\n");
			strcat(MEGAString, "{8B8A8A}	Vou ser preso? {FFFFFF}A policia ser� avisada e voc� poder� ser preso\n");

			strcat(MEGAString, "{8B8A8A}	Atualiza��o: {FFFFFF}Poder� explodir a Pris�o La Sante para soltar os presos! (Sem ganhar)\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_CAMINHONEIRO:
		{
			strcat(MEGAString, "{08C2DA}> Caminhoneiro:\n\n");

			strcat(MEGAString, "{8B8A8A}	Objetivo: {FFFFFF}Vender produtos para fazendas\n");
			strcat(MEGAString, "{8B8A8A}	Ganhos: {FFFFFF}Determinado pela fazenda que voc� vender!\n");
			strcat(MEGAString, "{8B8A8A}	Trabalhando para fazendas:\n");
			strcat(MEGAString, "{8B8A8A}	Como comprar? {FFFFFF}Digite: /comprarprods | no local de servi�o\n");
			strcat(MEGAString, "{8B8A8A}	Como entregar? {FFFFFF}Digite: /venderprods | na fazenda que ir� vender\n");
			strcat(MEGAString, "{8B8A8A}	Trabalhando para propriedade:\n");
			strcat(MEGAString, "{8B8A8A}	Como comprar? {FFFFFF}Digite: /comprarinsumos | em uma fazenda\n");
			strcat(MEGAString, "{8B8A8A}	Como entregar? {FFFFFF}Digite: /venderinsumos | na propriedade que ir� vender\n");
			strcat(MEGAString, "{8B8A8A}	Para ver os produtos/insumos no caminh�o: {FFFFFF}/prods\n");

			strcat(MEGAString, "{FFF000}	* DICA: {FFFFFF}Digite /gps e procure uma fazenda/propriedade que paga melhor pelos produtos/insumos!\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_LIXEIRO:
		{
			strcat(MEGAString, "{00FF00}Lixeiro\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}� recolher todos os lixos das lixeiras espalhadas pela cidade, e entregar\n");
			strcat(MEGAString, "		no lix�o, que � onde � sua HQ. O caminh�o tem a capacidade de 50 unidades...\n");
			strcat(MEGAString, "		de lixo, que � equivalente a 100 KG.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Voc� recebe por KG entregue multiplicado pelo pagamento por kg, esse\n");
			format(string, sizeof string, "		valor � definido pelo governador, e atualmente est� em: {00AA00}$%s {FFFFFF}por KG.\n", getFormatText(GetWageJob(ID_JOB_LIXEIRO)));
			strcat(MEGAString, string);
			format(string, sizeof string, "		Sabendo disso, � correto afirmar que voc� estar� recebendo {00AA00}$%s\n", getFormatText(GetWageJob(ID_JOB_LIXEIRO) * 100));
			strcat(MEGAString, string);
			strcat(MEGAString, "		{FFFFFF}a cada 100 KG entregues.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/iniciarcoleta {FFFFFF}- comando utilizado para iniciar uma coleta\n");
			strcat(MEGAString, "		{FFFC05}/gps {FFFFFF}- comando utilizado para localizar as lixeiras da cidade.\n\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");

			strcat(MEGAString, "		{FFFC05}/entregarcoleta {FFFFFF}- comando utilizado para entregar a coleta de lixo e receber...\n");
			strcat(MEGAString, "		seu pagamento. Deve ser utilizado no lix�o, se utilizado fora do lix�o,\n");
			strcat(MEGAString, "		ele automaticamente ser� marcado para voc�.\n");
		}
		case ID_JOB_TAXISTA:
		{
			strcat(MEGAString, "{00FF00}Taxista\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Transportar passageiros a seus locais de destino. O transporte\n");
			strcat(MEGAString, "		pode ser realizado em qualquer ve�culo, desde que o passageiro seja\n");
			strcat(MEGAString, "		levado. Existem ve�culos p�blicos na HQ, pr�ximo ao Aeroporto de Los Santos.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Voc� recebe por corrida, onde o tax�metro conta a cada 10 segundos\n");
			strcat(MEGAString, "		{FFFFFF}o valor que foi oferecido pelo taxista e aceito pelo cliente.\n");
			strcat(MEGAString, "		{FFFFFF}Ao final da corrida, quando o passageiro sair do ve�culo, ele paga o total da corrida.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/servico taxi {FFFFFF}- comando para solicitar um taxi.\n");
			strcat(MEGAString, "		{FFFC05}/atenderchamado {FFFFFF}- comando utilizado ver os chamados pendentes.\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_MEDICO:
		{
			strcat(MEGAString, "{00FF00}M�dico\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Ajudar os pacientes enquanto estiverem hospitalizados.\n");
			strcat(MEGAString, "		Voc� pode diminuir o per�odo que um paciente passa no hospital,\n");
			strcat(MEGAString, "		al�m de tamb�m poder curar os pacientes em locais remotos.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Voc� recebe por cura nos hospitais e tamb�m pode cura em locais remotos.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/ajustar {FFFFFF}- comando para ajustar um paciente.\n");
			strcat(MEGAString, "		{FFFC05}/hospitalizados {FFFFFF}- comando para ver pacientes no hospital.\n");
			strcat(MEGAString, "		{FFFC05}/iniciarservico {FFFFFF}- comando para iniciar o resgate.\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_MINERADOR:
		{
			strcat(MEGAString, "{00FF00}Minerador\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Trabalhar na mina de extra��o de materiais preciosos.\n");
			strcat(MEGAString, "		Voc� pode extrair min�rios e entreg�-los para a mineradora\n");
			strcat(MEGAString, "		e ser� recompensado conforme a raridade do min�rio capturado.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Voc� recebe por cada min�rio entregue � mineradora.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/minerar {FFFFFF}- comando para minerar um material.\n");
			strcat(MEGAString, "		{FFFC05}/infominerio {FFFFFF}- comando para ver informa��es de um min�rio.\n");
			strcat(MEGAString, "		{FFFC05}/venderminerio {FFFFFF}- comando para vender o min�rio � mineradora.\n");
			strcat(MEGAString, "		{FFFC05}/pegarminerio {FFFFFF}- comando para pegar um min�rio abandonado.\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_MECANICO:
		{
			strcat(MEGAString, "{00FF00}Mec�nico\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Resolver problemas de ve�culos, desde abastecimento a reparo.\n");
			strcat(MEGAString, "		Um mec�nico pode atender as pessoas nos mais diversos hor�rios e situa��es\n");
			strcat(MEGAString, "		e ser� recompensado pelo servi�o prestado, mas precisando pagar os custos.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Voc� recebe pelos servi�os prestados.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/atenderchamado {FFFFFF}- comando para atender um chamado.\n");
			strcat(MEGAString, "		{FFFC05}/cancelarmecanico {FFFFFF}- comando para cancelar um chamado.\n");
			strcat(MEGAString, "		{FFFC05}/abastecerveiculo {FFFFFF}- comando para oferecer um abastecimento.\n");
			strcat(MEGAString, "		{FFFC05}/repararveiculo {FFFFFF}- comando para oferecer um reparo.\n");
			strcat(MEGAString, "		{FFFC05}/guinchar {FFFFFF}- comando para guinchar um ve�culo.\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_FAZENDEIRO:
		{
			strcat(MEGAString, "{00FF00}Fazendeiro\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Plantar sementes na fazenda, colher as planta��es e entreg�-las no armazem.\n");
			strcat(MEGAString, "		Voc� pode plantar Milho, Trigo, Soja, Caf� e Arroz e ser� remunerado conforme.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Voc� recebe pelas colheitas realizadas.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/plantar {FFFFFF}- comando para plantar uma semente.\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_FIREFIGHTER:
		{
			strcat(MEGAString, "{00FF00}Bombeiro\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Combater os inc�ndios que ocorrerem em todos os locais.\n");
			strcat(MEGAString, "		Voc� poder� pegar um caminh�o e um extintor na HQ e ir ao local de inc�ndio.\n");
			strcat(MEGAString, "		Quanto mais tempo permanecer atuando no inc�ndio, maior ser� sua remunera��o.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Voc� recebe pelo tempo que permanecer apagando as chamas.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/incendios {FFFFFF}- comando para localizar os inc�ndios.\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_DESIGNER_INTERIORES:
		{
			strcat(MEGAString, "{08C2DA}> Designer de Interiores:\n\n");

			strcat(MEGAString, "{8B8A8A}	Objetivo: {FFFFFF}Montar os interiores das casas dos jogadores\n");
			strcat(MEGAString, "{8B8A8A}	Ganhos: {FFFFFF}Voc� mesmo determina o valor com o seu cliente\n");
			strcat(MEGAString, "{8B8A8A}	Como trabalhar? {FFFFFF}Procure por um cliente no /an (an�ncio geral) \n");
			strcat(MEGAString, "{8B8A8A}	... {356FB2}e pe�a para lhe contratar (/contratar designer)\n\n");
			strcat(MEGAString, "{8B8A8A}	Como montar? {FFFFFF}Espere ele lhe contratar e entre na casa\n");
			strcat(MEGAString, "{8B8A8A}	... {356FB2}Use os comandos de m�vel para montar o interior\n\n");
			strcat(MEGAString, "{05E5FF}    Comandos\n");
			strcat(MEGAString, "	{FFFC05}/casasdesigner {FFFFFF}- comando para ver as casas que voc� � o designer.\n");
			strcat(MEGAString, "	{FFFC05}/comprarmovel {FFFFFF}- comando para comprar m�veis para uma casa.\n");
			strcat(MEGAString, "	{FFFC05}/selecionarmovel {FFFFFF}- comando para selecionar um m�vel de uma casa.\n");
			strcat(MEGAString, "	{FFFC05}/resetarmoveis {FFFFFF}- comando para remover todos os m�veis de uma casa.\n");
		}
		case ID_JOB_DELIVERYMAN:
		{
			strcat(MEGAString, "{00FF00}Entregador de Pizzas\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Fazer entregas de moto pela cidade e tamb�m fazer vendas de pizzas.\n");
			strcat(MEGAString, "		Voc� poder� pegar pizzas na sua HQ e vend�-las a outros jogadores ou entreg�-las aos clientes.\n");
			strcat(MEGAString, "		Voc� recebe gratuitamente as pizzas e recebe ao entreg�-las ou ao vend�-las.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Voc� recebe por cada entrega/venda de pizza feita.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/pizza entregar {FFFFFF}- comando para fazer entrega de pizzas.\n");
			strcat(MEGAString, "		{FFFC05}/pizza pegar {FFFFFF}- comando para pegar 1 pizza do ba� da moto.\n");
			strcat(MEGAString, "		{FFFC05}/pizza guardar {FFFFFF}- comando para colocar as pizzas no ba� da moto.\n");
			strcat(MEGAString, "		{FFFC05}/pizza pegartodas {FFFFFF}- comando para pegar todas as pizzas do ba� da moto.\n");
			strcat(MEGAString, "		{FFFC05}/pizza guardarmochila {FFFFFF}- comando para colocar as pizzas no invent�rio.\n");
		}
	}
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{DFD136}Ajuda emprego", MEGAString, "Fechar", "");
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    // Tecla: H
    if (newkeys & KEY_CTRL_BACK)
	{
        if (IsPlayerInRangeOfPoint(playerid, 2.0, WORKING_POS_X, WORKING_POS_Y, WORKING_POS_Z))
			callcmd::emprego(playerid, "pegar");
    }
    return 1;
}

#include <fires-entry>

#include <taxista>

#include <medico>

#include <minerador>

#include <mecanico>

#include <fazendeiro>

#include <caminhoneiros>

#include <modulo_transporte>

#include <firefighter>

#include <deliveryman>

//
#define 		MAX_BARREIRA  				10
#define         MAX_BLOQUEIO                15

#define         OBJECT_TYPE_BARREIRA    	2
#define         OBJECT_TYPE_BLOQUEIO        3

enum barreiraInfo
{
	barreiraObject,
	barreiraOwner[MAX_PLAYER_NAME],
	Float:barreiraPos[3],
	Text3D:barreiraText,
};

new
	BarreiraInfo[MAX_BARREIRA][barreiraInfo],
	Iterator:IterBarreira<MAX_BARREIRA>
;

static createPlayerBarreira(playerid, modelid = 981)
{
	new Float:x,
		Float:y,
		Float:z,
		Float:a;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);
	GetXYInFrontOfPlayer(playerid, x, y, 3.5);

	new id = Iter_Free(IterBarreira),
	    string[124];

	if (id != -1)
	{
    	Iter_Add(IterBarreira, id);

    	BarreiraInfo[id][barreiraPos][0] = x;
    	BarreiraInfo[id][barreiraPos][1] = y;
    	BarreiraInfo[id][barreiraPos][2] = z;

		new MapZone:zone = GetMapZoneAtPoint2D(BarreiraInfo[id][barreiraPos][0], BarreiraInfo[id][barreiraPos][1]);
		new zone_name[MAX_MAP_ZONE_NAME];
		GetMapZoneName(zone, zone_name);

    	GameTextForPlayer(playerid, "~b~~h~Voce colocou uma barreira", 5000, 5);

    	SendClientMessage(playerid, -1, "Voc� colocou uma barreira, para remover use: /rbarreira, ou use /rbarreiras para remover todas.");

    	format(string, sizeof(string), "<< COPOM >> %s: %s, %s colocou uma barreira em %s.", NomeORG(playerid), GetPlayerCargo(playerid), PlayerName[playerid], zone_name);
    	SendCopMessage(COLOR_LIGHTRED, string);

        BarreiraInfo[id][barreiraObject] = CreateDynamicObject(modelid, x, y, z, 0.0, 0.0, a + 180.0, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

        format(string, sizeof string, "Barreira\nCriada por: %s[%d]", PlayerName[playerid], playerid);
		BarreiraInfo[id][barreiraText] = CreateDynamic3DTextLabel(string, 0xFFFF00F6, x, y, z, 10.0, INVALID_PLAYER_ID);

        format(BarreiraInfo[id][barreiraOwner], MAX_PLAYER_NAME, PlayerName[playerid]);
	}
	return id;
}

stock destroyBarreira(id)
{
    if (Iter_Contains(IterBarreira, id))
	{
		Iter_Remove(IterBarreira, id);

		DestroyDynamicObject(BarreiraInfo[id][barreiraObject]);
		DestroyDynamic3DTextLabel(BarreiraInfo[id][barreiraText]);
	}
}

static IsPlayerOwnerBarreira(playerid, barreiraid)
{
	if (Admin_GetNivel(playerid) || !strcmp(PlayerName[playerid], BarreiraInfo[barreiraid][barreiraOwner]) || GetPlayerOrg(playerid) == ID_ORG_GOVERNO)
		return true;

	return false;
}

static countPlayerBarreira(playerid)
{
	new count;

	foreach(new id : IterBarreira)
	{
	    if (Iter_Contains(IterBarreira, id))
		{
			if (!strcmp(PlayerName[playerid], BarreiraInfo[id][barreiraOwner])) count++;
		}
	}
	return count;
}

CMD:br(playerid)
{
	if (!IsACop(playerid)) return SendClientMessage(playerid, -1, "Voc� n�o tem autoridade para usar esse comando.");

    if (countPlayerBarreira(playerid) >= 2 && PlayerInfo[playerid][pVIP] < 8)
		return SendClientMessage(playerid, -1, "Voc� poder� colocar at� 4 barreiras caso for S�cio Extreme.");

	if (countPlayerBarreira(playerid) >= 4) return SendClientMessage(playerid, -1, "Voc� atingiu o limite de 4 barreiras.");

	if (createPlayerBarreira(playerid) == -1) return SendClientMessage(playerid, -1, "O servidor est� com o m�ximo de barreiras criadas (10)...");

	return true;
}
alias:barreira("br")

CMD:rbarreira(playerid)
{
    new barreiraid = getPositionObject(playerid, OBJECT_TYPE_BARREIRA);

	if (barreiraid == -1) return SendClientMessage(playerid, -1, "Voc� n�o est� pr�ximo de uma barreira.");

	if (!IsPlayerOwnerBarreira(playerid, barreiraid)) return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para remover essa barreira.");

	new string[128];

	new MapZone:zone = GetMapZoneAtPoint2D(BarreiraInfo[barreiraid][barreiraPos][0], BarreiraInfo[barreiraid][barreiraPos][1]);
	new zone_name[MAX_MAP_ZONE_NAME];
	GetMapZoneName(zone, zone_name);

    format(string, sizeof(string), "<< COPOM >> %s, %s removeu a barreira de %s em %s.", GetPlayerCargo(playerid), PlayerName[playerid],
	BarreiraInfo[barreiraid][barreiraOwner], zone_name);
   	SendCopMessage(COLOR_LIGHTRED, string);

    destroyBarreira(barreiraid);

	return true;
}
alias:rbarreira("rbr")

CMD:removerbarreiras(playerid)
{
    if (Admin_GetNivel(playerid) < MODERADOR) 
		return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para usar esse comando.");

    new count = DestroyAllBarreiras();

    new string[92];

    format(string, sizeof(string), "AdmCmd: %s, %s removeu todas as barreiras do servidor | Total: %d.", Staff_GetPositionName(playerid), PlayerName[playerid], count);
    Staff_ChatToAll(COLOR_LIGHTRED, string);

    return true;
}

DestroyAllBarreiras()
{
    new i = 0, c = 0;

    while (i < MAX_BARREIRA)
    {
        if (Iter_Contains(IterBarreira, i))
        {
            Iter_Remove(IterBarreira, i);

            DestroyDynamicObject(BarreiraInfo[i][barreiraObject]);
			DestroyDynamic3DTextLabel(BarreiraInfo[i][barreiraText]);

            ++c;
        }
        i++;
    }
    return c;
}

enum bloqueioInfo
{
	bloqueioObject,
	bloqueioOwner[MAX_PLAYER_NAME],
	Float:bloqueioPos[3],
	Text3D:bloqueioText,
};

new
	BloqueioInfo[MAX_BLOQUEIO][bloqueioInfo],
	Iterator:IterBloqueio<MAX_BLOQUEIO>;

static createPlayerBloqueio(playerid, modelid = 1358)
{
	new Float:x,
		Float:y,
		Float:z,
		Float:a,
		orgid = GetPlayerOrg(playerid);

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);
	GetXYInFrontOfPlayer(playerid, x, y, 3.5);

	new id = Iter_Free(IterBloqueio),
	    string[124];

	if (id != -1)
	{
    	Iter_Add(IterBloqueio, id);

    	BloqueioInfo[id][bloqueioPos][0] = x;
    	BloqueioInfo[id][bloqueioPos][1] = y;
    	BloqueioInfo[id][bloqueioPos][2] = z;

		new MapZone:zone = GetMapZoneAtPoint2D(BloqueioInfo[id][bloqueioPos][0], BloqueioInfo[id][bloqueioPos][1]);
		new zone_name[MAX_MAP_ZONE_NAME];
		GetMapZoneName(zone, zone_name);

    	GameTextForPlayer(playerid, "~r~~h~Voce colocou um bloqueio", 5000, 5);

    	SendClientMessage(playerid, -1, "Voc� colocou um bloqueio, para remover use: /rbloqueio.");

    	format(string, sizeof(string), "<< %s >> %s, %s: colocou um bloqueio em %s.", NomeORG(playerid), GetPlayerCargo(playerid), PlayerName[playerid], zone_name);
    	SendMembersMessage(orgid, GetPlayerColor(playerid), string);

        BloqueioInfo[id][bloqueioObject] = CreateDynamicObject(modelid, x, y, z, 0.0, 0.0, a + 180.0, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

        format(string, sizeof string, "Bloqueio da(o) %s\nCriado por: %s[%d]", GetOrgName(orgid), PlayerName[playerid], playerid);
		BloqueioInfo[id][bloqueioText] = CreateDynamic3DTextLabel(string, 0xFFFF00F6, x, y, z, 8.0, INVALID_PLAYER_ID);

        format(BloqueioInfo[id][bloqueioOwner], MAX_PLAYER_NAME, PlayerName[playerid]);
	}
	return id;
}

static PlayerIsBloqueio(playerid)
{
	switch (GetPlayerOrg(playerid))
	{
		case 5, 8, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 28: return true;
	}
	return false;
}

stock destroyBloqueio(id)
{
    if (Iter_Contains(IterBloqueio, id))
	{
		Iter_Remove(IterBloqueio, id);

		DestroyDynamicObject(BloqueioInfo[id][bloqueioObject]);
		DestroyDynamic3DTextLabel(BloqueioInfo[id][bloqueioText]);
	}
}

stock IsPlayerOwnerBloqueio(playerid, bloqueioid)
{
	if (Admin_GetNivel(playerid))
		return true;

	if (!strcmp(PlayerName[playerid], BloqueioInfo[bloqueioid][bloqueioOwner]))
		return true;

	return false;
}

static countPlayerBloqueio(playerid)
{
	new count;

	foreach(new id : IterBloqueio)
	{
	    if (Iter_Contains(IterBloqueio, id))
		{
			if (!strcmp(PlayerName[playerid], BloqueioInfo[id][bloqueioOwner])) count++;
		}
	}
	return count;
}

CMD:bq(playerid)
{
	if (!Command_ActionBlock(playerid)) return true;

	if (!PlayerIsBloqueio(playerid)) return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para usar esse comando.");

	if (GetPlayerInterior(playerid) > 0)
		return SendClientMessage(playerid, COLOR_YELLOW, "Voc� n�o pode colocar um bloqueio num interior.");

    if (countPlayerBloqueio(playerid) >= 2 && PlayerInfo[playerid][pVIP] < 8)
		return SendClientMessage(playerid, -1, "Voc� poder� colocar at� 4 bloqueios caso for S�cio Extreme.");

	if (countPlayerBloqueio(playerid) >= 4) return SendClientMessage(playerid, -1, "Voc� atingiu o limite de 4 bloqueios.");

	if (createPlayerBloqueio(playerid) == -1) return SendClientMessage(playerid, -1, "O servidor est� com o m�ximo de bloqueios criados (15)...");

	return true;
}
alias:bq("bloqueio")

CMD:rbloqueio(playerid)
{
    new bloqueioid = getPositionObject(playerid, OBJECT_TYPE_BLOQUEIO);

	if (bloqueioid == -1) return SendClientMessage(playerid, -1, "Voc� n�o est� pr�ximo de um bloqueio.");

	if (!IsPlayerOwnerBloqueio(playerid, bloqueioid)) return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para remover esse bloqueio.");

	new string[128];

	new MapZone:zone = GetMapZoneAtPoint2D(BloqueioInfo[bloqueioid][bloqueioPos][0], BloqueioInfo[bloqueioid][bloqueioPos][1]);
	new zone_name[MAX_MAP_ZONE_NAME];
	GetMapZoneName(zone, zone_name);

    format(string, sizeof(string), "<< %s >> %s, %s removeu o bloqueio de %s em %s.", NomeORG(playerid), GetPlayerCargo(playerid), PlayerName[playerid],
	BloqueioInfo[bloqueioid][bloqueioOwner], zone_name);
   	SendMembersMessage(GetPlayerOrg(playerid), GetPlayerColor(playerid), string);

    destroyBloqueio(bloqueioid);

	return true;
}
alias:rbloqueio("rbq")

CMD:removerbloqueios(playerid)
{
    if (Admin_GetNivel(playerid) < MODERADOR) 
		return SendClientMessage(playerid, -1, "Voc� n�o tem autoriza��o para usar esse comando.");

    new count = DestroyAllBloqueios();

    new string[92];

    format(string, sizeof(string), "AdmCmd: %s, %s removeu todos os bloqueios do servidor | Total: %d.", Staff_GetPositionName(playerid), PlayerName[playerid], count);
    Staff_ChatToAll(COLOR_LIGHTRED, string);

    return true;
}

DestroyAllBloqueios()
{
    new i = 0, c = 0;

    while (i < MAX_BLOQUEIO)
    {
        if (Iter_Contains(IterBloqueio, i))
        {
            Iter_Remove(IterBloqueio, i);

            DestroyDynamicObject(BloqueioInfo[i][bloqueioObject]);
			DestroyDynamic3DTextLabel(BloqueioInfo[i][bloqueioText]);

            ++c;
        }
        i++;
    }
    return c;
}

stock getPositionObject(playerid, type)
{
	new Float: distancia = 9999999.0, Float:dist, objectid = -1;

	switch (type)
	{
		case OBJECT_TYPE_CONE:
		{
			foreach(new x : IterCone)
			{
				dist = GetPlayerDistanceFromPoint(playerid, ConeInfo[x][conePos][0], ConeInfo[x][conePos][1], ConeInfo[x][conePos][2]);

				if (dist < distancia && dist < 10.0)
				{
					distancia = dist;
					objectid = x;
				}
			}
		}
		case OBJECT_TYPE_BARREIRA:
		{
		    foreach(new x : IterBarreira)
			{
			    dist = GetPlayerDistanceFromPoint(playerid, BarreiraInfo[x][barreiraPos][0], BarreiraInfo[x][barreiraPos][1], BarreiraInfo[x][barreiraPos][2]);

				if (dist < distancia && dist < 10.0)
				{
					distancia = dist;
					objectid = x;
				}
			}
		}
		case OBJECT_TYPE_BLOQUEIO:
		{
		    foreach(new x : IterBloqueio)
			{
			    dist = GetPlayerDistanceFromPoint(playerid, BloqueioInfo[x][bloqueioPos][0], BloqueioInfo[x][bloqueioPos][1], BloqueioInfo[x][bloqueioPos][2]);

				if (dist < distancia && dist < 10.0)
				{
					distancia = dist;
					objectid = x;
				}
			}
		}
	}

	return objectid;
}