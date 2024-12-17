#if defined _inc_jobs_system
	#endinput
#endif
#define _inc_jobs_system

// Includes necessárias
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
	{ID_JOB_MEDICO, "Médico", 1, 0, "Carteira de Motorista", {1164.6228, -1326.4603, -44.2836}, 272.3499},
	{ID_JOB_CAMINHONEIRO, "Caminhoneiro", 1, 0, "Carteira de Motorista", {1375.9441, 1057.7214, 10.8203}, 271.5050},
	{ID_JOB_DELIVERYMAN, "Entregador de Pizza", 1, 0, "Carteira de Motorista", {2098.4106, -1812.5846, 13.3828}, 177.3905},
	{ID_JOB_BANDIDO, "Bandido", 1, 1, "--------", {0.00, 0.00, 0.00}, 0.00},
	{ID_JOB_VENDEDOR_ARMAS, "Fabricante de Materiais", 1, 1, "--------", {2846.3477, 976.9812, 10.7500}, 93.2263},
	{ID_JOB_ADVOGADO, "Advogado", 2, 0, "--------", {1739.2667, -1583.4945, 14.1584}, 93.2263},
	{ID_JOB_DETETIVE, "Detetive", 2, 0, "--------", {0.00, 0.00, 0.00}, 0.00},
	{ID_JOB_MINERADOR, "Minerador", 3, 0, "--------", {1003.9560, -91.6045, 22.4495}, 28.0772},
	{ID_JOB_MECANICO, "Mecânico", 3, 0, "--------", {2142.0698, -1729.8184, 13.5592}, 164.4512},
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
			string = "Médico";
		case ID_JOB_MINERADOR:
			string = "Minerador";
		case ID_JOB_MECANICO:
			string = "Mecânico";
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
        return SendClientMessage(playerid, -1, "Você não é mecânico ou taxista.");

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
        return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (id == playerid) 
        return SendClientMessage(playerid, -1, "Você não pode atender você mesmo!");
	
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
	if (!Admin_GetNivel(playerid)) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

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
			return SendClientMessage(playerid, -1, "Você cancelou o menu de empregos.");

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
			return SendClientMessage(playerid, -1, "Você cancelou o menu de empregos.");

		new string[128];
		if(PlayerInfo[playerid][pLevel] < JobMenuConfig[listitem][jmLevel])
			return SendClientMessage(playerid, -1, "Você não possui nível suficiente para ter esse emprego.");
		

		MEGAString[0] = EOS;
		format(string, sizeof(string), "\n{E9ED19}Contrato para %s\n\n", JobMenuConfig[listitem][jmName]);
		strcat(MEGAString, string);

		format(string, sizeof string, "{FFFFFF}Olá {00FF00}%s{FFFFFF}, leia atentamente antes de assinar!\n\n", PlayerName[playerid]);
		strcat(MEGAString, string);

		strcat(MEGAString, "{FFFFFF}Você terá que {AAAAAA}cumprir {FFFFFF}exatamente {59FA72}8 horas(payday) {FFFFFF}no trabalho antes de pedir demissão!\n");
		strcat(MEGAString, "{FFFFFF}Para entender tudo sobre o {59FA72}emprego{FFFFFF} após assinar o {52B0EF}contrato{FFFFFF} use: /ajudaemprego\n");
		strcat(MEGAString, "{FFFFFF}Caso queira se {FF0000}demitir {FFFFFF}do emprego após cumprir as {59FA72}8 horas{FFFFFF} no trabalho, use: /emprego sair\n");


		strcat(MEGAString, "\n\n\n{8B8A8A}Para aceitar o trabalho clique em 'Aceitar'.\n\n");

		ShowPlayerDialog(playerid, 2586, DIALOG_STYLE_MSGBOX, "{FFFFFF}Agência de empregos", MEGAString, "Aceitar", "Negar");
		GettingEmprego[playerid] = listitem;
	}
	else if(dialogid == 2586)
	{
	    if(!response)
		{
			GettingEmprego[playerid] = 0;
			return SendClientMessage(playerid, -1, "Você cancelou o emprego.");
		}
		else
		{
			new index = GettingEmprego[playerid],
				jobid = JobMenuConfig[index][jmID],
				string[128];

	    	if (PlayerInfo[playerid][pEmprego] != 0 && PlayerInfo[playerid][pVIP] < 8)
				return SendClientMessage(playerid, -1, "Você precisa ser Sócio Extreme para ter dois empregos, use: /emprego sair, para demitir-se.");

        	if (PlayerInfo[playerid][pEmprego] != 0 && PlayerInfo[playerid][pEmprego2] != 0)
				return SendClientMessage(playerid, -1, "Você possui dois empregos, use: /emprego sair.");

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
				"* Você acabou de adquirir um novo emprego como %s, digite /ajuda para ver os comandos!", 
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
			return SendClientMessage(playerid, -1, "Apenas 'Sócio-Extreme' pode ter 2 empregos.");

		// Verifica se o jogador está no local
		if (!IsPlayerInRangeOfPoint(playerid, 2.0, WORKING_POS_X, WORKING_POS_Y, WORKING_POS_Z))
			return SendClientMessage(playerid, -1, "Você precisa ir até a prefeitura.");

		MEGAString[0] = EOS;

		strcat(MEGAString, "#  Nome do emprego\tNível necessário\tTipo\tRequisitos\n");

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

		ShowPlayerDialog(playerid, 590, DIALOG_STYLE_TABLIST_HEADERS, "{DFD136}Agência de empregos", MEGAString, "Prosseguir", "Cancelar"); //2569
	}

	else if (strfind(params, "sair", true) != -1) 
	{
		new job1 = PlayerInfo[playerid][pEmprego];
		new job2 = PlayerInfo[playerid][pEmprego2];

		if (job1 == 0 && job2 == 0)
			return SendClientMessage(playerid, -1, "Você já está desempregado.");

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
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você saiu do seu emprego primário, está livre para empregar-se em outro.");
			PlayerInfo[playerid][pEmprego] = 0;
		} 
		else if (idjob == 2) 
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você saiu do seu emprego secundário, está livre para empregar-se em outro.");
			PlayerInfo[playerid][pEmprego2] = 0;
		} 
		else
		{
			SendClientMessage(playerid, -1, "Você precisa digitar se quer sair do emprego 1 ou 2.");
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
			strcat(MEGAString, "{9C9C9C}Encontre a localização de outros players\n");
			// Salário é definido pelo governo
			/*format(string, sizeof(string), "{797978}Salário: {AA00AA}$%s {797978}(por assassinato descoberto)\n", getFormatText(GetWageJob(ID_JOB_DETETIVE)));
			strcat(MEGAString, string);*/

			strcat(MEGAString, "\n{FFFFFF}Funções:\n");
			strcat(MEGAString, "	{9C9C9C}Encontrar players. (/procurar)\n");
			//strcat(MEGAString, "        {797978}Nível 10+ |		{FFFFFF}Identificar o assassino analisando a cena do crime {FFF000}(em breve)\n");

			/*strcat(MEGAString, "{F8973F}Benefícios por nível:\n");
			strcat(MEGAString, "        {797978}Nível 1 |		{FFFFFF}Você tem acesso ao comando /procurar com limitações\n");
			strcat(MEGAString, "        {797978}Nível 2 |		{FFFFFF}Você ganha habilidade para poder usar o /procurar mais rapidamente\n");
			strcat(MEGAString, "        {797978}Nível 3 |		{FFFFFF}Você ganha um acessório que representa o emprego de detetive\n");
			strcat(MEGAString, "        {797978}Nível 4 |		{FFFFFF}Você ganha habilidade para poder usar o /procurar mais rapidamente\n");
			strcat(MEGAString, "        {797978}Nível 5 |		{FFFFFF}Você ganha uma Caixa Surpresa Supreme para abrir ou negociar\n");
			strcat(MEGAString, "        {797978}Nível 6 |		{FFFFFF}Você ganha um nível de bônus do servidor\n");
			strcat(MEGAString, "        {797978}Nível 7 |		{FFFFFF}Você ganha habilidade para usar o /procurar por tempo infinito\n");
			strcat(MEGAString, "        {797978}Nível 8 |		{FFFFFF}Você ganha um bônus salarial de $54.000 do servidor\n");
			strcat(MEGAString, "        {797978}Nível 9 |		{FFFFFF}Você ganha uma skin do emprego de detetive de presente do inventário\n");
			strcat(MEGAString, "        {797978}Nível 10 |		{FFFFFF}Você ganha permissão para usar o comando /investigar assassinato\n");*/

			strcat(MEGAString, "\n{FFFFFF}Comandos:\n");
			strcat(MEGAString, "	{DFD136}/procurar\n");
			strcat(MEGAString, "	{9C9C9C}Você usa o comando para encontrar um jogador.\n");
			/*strcat(MEGAString, "        {797978}2. {FFFFFF}/investigar assassinato\n");
			strcat(MEGAString, "				{9C9C9C}Você usa o comando para informar o assassino para a policia.");*/

			strcat(MEGAString, "\n\n {9C9C9C}--------------------------------------------------------------------------------------------------- \n");
		}
		case ID_JOB_ADVOGADO:
		{
			strcat(MEGAString, "{08C2DA}> Advogado:\n\n");

			strcat(MEGAString, "{8B8A8A}	Objetivo: {FFFFFF}Liberação dos presos na cadeia La Sante\n");
			strcat(MEGAString, "{8B8A8A}	Ganhos: {FFFFFF}Você mesmo determina o valor com o seu cliente\n");
			strcat(MEGAString, "{8B8A8A}	Como trabalhar? {FFFFFF}Digite: /gps depois Locais Importantes e vá em Prisão La Sante.\n");
			strcat(MEGAString, "{8B8A8A}	Como soltar preso? {FFFFFF}Dentro da Prisão La Sante terá um 'sinal branco', clique nele!\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");

		}
		case ID_JOB_VENDEDOR_ARMAS:
		{
			strcat(MEGAString, "{08C2DA}> Fabricante de Materiais:\n\n");

			strcat(MEGAString, "{8B8A8A}	Objetivo: {FFFFFF}Fabricar materiais e vender para organizações\n");
			strcat(MEGAString, "{8B8A8A}	Ganhos: {FFFFFF}A organização vai definir, use: /materiais pedidos\n");
			strcat(MEGAString, "{8B8A8A}	Como trabalhar? {FFFFFF}Digite /materiais fabricar (próximo a uma mesa de fabricação)\n");
			strcat(MEGAString, "{FF0000}	OBS: {356FB2}Use /materiais produtos (a frente da mesa de fabricação)\n");
			strcat(MEGAString, "{8B8A8A}	Como vender para ORG? {FFFFFF}Veja se ela fez pedido e vá até o InfoOrg da mesma!\n\n");

			strcat(MEGAString, "{8B8A8A}	Atualização: {FFFFFF}O emprego foi recentemente reprogramado (antigo Vendedor de armas)\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");

		}
		case ID_JOB_BANDIDO:
		{
			strcat(MEGAString, "{08C2DA}> Bandido:\n\n");

			strcat(MEGAString, "{8B8A8A}	Objetivo: {FFFFFF}Explodir Caixas e pegar o dinheiro e Explodir Prisão La Sante\n");
			strcat(MEGAString, "{8B8A8A}	Ganhos: {FFFFFF}Os ganhos são aleatórios\n");
			strcat(MEGAString, "{8B8A8A}	Como roubar caixas? {356FB2}Use: /gps > Caixas Eletronicos e vá até algum\n");
			strcat(MEGAString, "{8B8A8A}	Como pegar explosivo? {356FB2}Use: /gps > Locais Importantes > Mercado Negro\n");
			strcat(MEGAString, "{FF0000}	OBS: {FFFFFF}Faça isso com alguns amigos, ou um grupo, para ser mais fácil roubar\n");
			strcat(MEGAString, "{8B8A8A}	Vou ser preso? {FFFFFF}A policia será avisada e você poderá ser preso\n");

			strcat(MEGAString, "{8B8A8A}	Atualização: {FFFFFF}Poderá explodir a Prisão La Sante para soltar os presos! (Sem ganhar)\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_CAMINHONEIRO:
		{
			strcat(MEGAString, "{08C2DA}> Caminhoneiro:\n\n");

			strcat(MEGAString, "{8B8A8A}	Objetivo: {FFFFFF}Vender produtos para fazendas\n");
			strcat(MEGAString, "{8B8A8A}	Ganhos: {FFFFFF}Determinado pela fazenda que você vender!\n");
			strcat(MEGAString, "{8B8A8A}	Trabalhando para fazendas:\n");
			strcat(MEGAString, "{8B8A8A}	Como comprar? {FFFFFF}Digite: /comprarprods | no local de serviço\n");
			strcat(MEGAString, "{8B8A8A}	Como entregar? {FFFFFF}Digite: /venderprods | na fazenda que irá vender\n");
			strcat(MEGAString, "{8B8A8A}	Trabalhando para propriedade:\n");
			strcat(MEGAString, "{8B8A8A}	Como comprar? {FFFFFF}Digite: /comprarinsumos | em uma fazenda\n");
			strcat(MEGAString, "{8B8A8A}	Como entregar? {FFFFFF}Digite: /venderinsumos | na propriedade que irá vender\n");
			strcat(MEGAString, "{8B8A8A}	Para ver os produtos/insumos no caminhão: {FFFFFF}/prods\n");

			strcat(MEGAString, "{FFF000}	* DICA: {FFFFFF}Digite /gps e procure uma fazenda/propriedade que paga melhor pelos produtos/insumos!\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_LIXEIRO:
		{
			strcat(MEGAString, "{00FF00}Lixeiro\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}É recolher todos os lixos das lixeiras espalhadas pela cidade, e entregar\n");
			strcat(MEGAString, "		no lixão, que é onde é sua HQ. O caminhão tem a capacidade de 50 unidades...\n");
			strcat(MEGAString, "		de lixo, que é equivalente a 100 KG.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Você recebe por KG entregue multiplicado pelo pagamento por kg, esse\n");
			format(string, sizeof string, "		valor é definido pelo governador, e atualmente está em: {00AA00}$%s {FFFFFF}por KG.\n", getFormatText(GetWageJob(ID_JOB_LIXEIRO)));
			strcat(MEGAString, string);
			format(string, sizeof string, "		Sabendo disso, é correto afirmar que você estará recebendo {00AA00}$%s\n", getFormatText(GetWageJob(ID_JOB_LIXEIRO) * 100));
			strcat(MEGAString, string);
			strcat(MEGAString, "		{FFFFFF}a cada 100 KG entregues.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/iniciarcoleta {FFFFFF}- comando utilizado para iniciar uma coleta\n");
			strcat(MEGAString, "		{FFFC05}/gps {FFFFFF}- comando utilizado para localizar as lixeiras da cidade.\n\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");

			strcat(MEGAString, "		{FFFC05}/entregarcoleta {FFFFFF}- comando utilizado para entregar a coleta de lixo e receber...\n");
			strcat(MEGAString, "		seu pagamento. Deve ser utilizado no lixão, se utilizado fora do lixão,\n");
			strcat(MEGAString, "		ele automaticamente será marcado para você.\n");
		}
		case ID_JOB_TAXISTA:
		{
			strcat(MEGAString, "{00FF00}Taxista\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Transportar passageiros a seus locais de destino. O transporte\n");
			strcat(MEGAString, "		pode ser realizado em qualquer veículo, desde que o passageiro seja\n");
			strcat(MEGAString, "		levado. Existem veículos públicos na HQ, próximo ao Aeroporto de Los Santos.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Você recebe por corrida, onde o taxímetro conta a cada 10 segundos\n");
			strcat(MEGAString, "		{FFFFFF}o valor que foi oferecido pelo taxista e aceito pelo cliente.\n");
			strcat(MEGAString, "		{FFFFFF}Ao final da corrida, quando o passageiro sair do veículo, ele paga o total da corrida.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/servico taxi {FFFFFF}- comando para solicitar um taxi.\n");
			strcat(MEGAString, "		{FFFC05}/atenderchamado {FFFFFF}- comando utilizado ver os chamados pendentes.\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_MEDICO:
		{
			strcat(MEGAString, "{00FF00}Médico\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Ajudar os pacientes enquanto estiverem hospitalizados.\n");
			strcat(MEGAString, "		Você pode diminuir o período que um paciente passa no hospital,\n");
			strcat(MEGAString, "		além de também poder curar os pacientes em locais remotos.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Você recebe por cura nos hospitais e também pode cura em locais remotos.\n\n");

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
			strcat(MEGAString, "		{FFFFFF}Trabalhar na mina de extração de materiais preciosos.\n");
			strcat(MEGAString, "		Você pode extrair minérios e entregá-los para a mineradora\n");
			strcat(MEGAString, "		e será recompensado conforme a raridade do minério capturado.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Você recebe por cada minério entregue à mineradora.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/minerar {FFFFFF}- comando para minerar um material.\n");
			strcat(MEGAString, "		{FFFC05}/infominerio {FFFFFF}- comando para ver informações de um minério.\n");
			strcat(MEGAString, "		{FFFC05}/venderminerio {FFFFFF}- comando para vender o minério à mineradora.\n");
			strcat(MEGAString, "		{FFFC05}/pegarminerio {FFFFFF}- comando para pegar um minério abandonado.\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_MECANICO:
		{
			strcat(MEGAString, "{00FF00}Mecânico\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Resolver problemas de veículos, desde abastecimento a reparo.\n");
			strcat(MEGAString, "		Um mecânico pode atender as pessoas nos mais diversos horários e situações\n");
			strcat(MEGAString, "		e será recompensado pelo serviço prestado, mas precisando pagar os custos.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Você recebe pelos serviços prestados.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/atenderchamado {FFFFFF}- comando para atender um chamado.\n");
			strcat(MEGAString, "		{FFFC05}/cancelarmecanico {FFFFFF}- comando para cancelar um chamado.\n");
			strcat(MEGAString, "		{FFFC05}/abastecerveiculo {FFFFFF}- comando para oferecer um abastecimento.\n");
			strcat(MEGAString, "		{FFFC05}/repararveiculo {FFFFFF}- comando para oferecer um reparo.\n");
			strcat(MEGAString, "		{FFFC05}/guinchar {FFFFFF}- comando para guinchar um veículo.\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_FAZENDEIRO:
		{
			strcat(MEGAString, "{00FF00}Fazendeiro\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Plantar sementes na fazenda, colher as plantações e entregá-las no armazem.\n");
			strcat(MEGAString, "		Você pode plantar Milho, Trigo, Soja, Café e Arroz e será remunerado conforme.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Você recebe pelas colheitas realizadas.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/plantar {FFFFFF}- comando para plantar uma semente.\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_FIREFIGHTER:
		{
			strcat(MEGAString, "{00FF00}Bombeiro\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Combater os incêndios que ocorrerem em todos os locais.\n");
			strcat(MEGAString, "		Você poderá pegar um caminhão e um extintor na HQ e ir ao local de incêndio.\n");
			strcat(MEGAString, "		Quanto mais tempo permanecer atuando no incêndio, maior será sua remuneração.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Você recebe pelo tempo que permanecer apagando as chamas.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/incendios {FFFFFF}- comando para localizar os incêndios.\n");
			strcat(MEGAString, "		{FFFC05}/ce {FFFFFF}- comando para falar com os colegas de trabalho.\n\n");
		}
		case ID_JOB_DESIGNER_INTERIORES:
		{
			strcat(MEGAString, "{08C2DA}> Designer de Interiores:\n\n");

			strcat(MEGAString, "{8B8A8A}	Objetivo: {FFFFFF}Montar os interiores das casas dos jogadores\n");
			strcat(MEGAString, "{8B8A8A}	Ganhos: {FFFFFF}Você mesmo determina o valor com o seu cliente\n");
			strcat(MEGAString, "{8B8A8A}	Como trabalhar? {FFFFFF}Procure por um cliente no /an (anúncio geral) \n");
			strcat(MEGAString, "{8B8A8A}	... {356FB2}e peça para lhe contratar (/contratar designer)\n\n");
			strcat(MEGAString, "{8B8A8A}	Como montar? {FFFFFF}Espere ele lhe contratar e entre na casa\n");
			strcat(MEGAString, "{8B8A8A}	... {356FB2}Use os comandos de móvel para montar o interior\n\n");
			strcat(MEGAString, "{05E5FF}    Comandos\n");
			strcat(MEGAString, "	{FFFC05}/casasdesigner {FFFFFF}- comando para ver as casas que você é o designer.\n");
			strcat(MEGAString, "	{FFFC05}/comprarmovel {FFFFFF}- comando para comprar móveis para uma casa.\n");
			strcat(MEGAString, "	{FFFC05}/selecionarmovel {FFFFFF}- comando para selecionar um móvel de uma casa.\n");
			strcat(MEGAString, "	{FFFC05}/resetarmoveis {FFFFFF}- comando para remover todos os móveis de uma casa.\n");
		}
		case ID_JOB_DELIVERYMAN:
		{
			strcat(MEGAString, "{00FF00}Entregador de Pizzas\n\n");

			strcat(MEGAString, "	{05E5FF}Objetivo\n");
			strcat(MEGAString, "		{FFFFFF}Fazer entregas de moto pela cidade e também fazer vendas de pizzas.\n");
			strcat(MEGAString, "		Você poderá pegar pizzas na sua HQ e vendê-las a outros jogadores ou entregá-las aos clientes.\n");
			strcat(MEGAString, "		Você recebe gratuitamente as pizzas e recebe ao entregá-las ou ao vendê-las.\n\n");

			strcat(MEGAString, "	{05E5FF}Pagamento\n");
			strcat(MEGAString, "		{FFFFFF}Você recebe por cada entrega/venda de pizza feita.\n\n");

			strcat(MEGAString, "	{05E5FF}Comandos\n");
			strcat(MEGAString, "		{FFFC05}/pizza entregar {FFFFFF}- comando para fazer entrega de pizzas.\n");
			strcat(MEGAString, "		{FFFC05}/pizza pegar {FFFFFF}- comando para pegar 1 pizza do baú da moto.\n");
			strcat(MEGAString, "		{FFFC05}/pizza guardar {FFFFFF}- comando para colocar as pizzas no baú da moto.\n");
			strcat(MEGAString, "		{FFFC05}/pizza pegartodas {FFFFFF}- comando para pegar todas as pizzas do baú da moto.\n");
			strcat(MEGAString, "		{FFFC05}/pizza guardarmochila {FFFFFF}- comando para colocar as pizzas no inventário.\n");
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

    	SendClientMessage(playerid, -1, "Você colocou uma barreira, para remover use: /rbarreira, ou use /rbarreiras para remover todas.");

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
	if (!IsACop(playerid)) return SendClientMessage(playerid, -1, "Você não tem autoridade para usar esse comando.");

    if (countPlayerBarreira(playerid) >= 2 && PlayerInfo[playerid][pVIP] < 8)
		return SendClientMessage(playerid, -1, "Você poderá colocar até 4 barreiras caso for Sócio Extreme.");

	if (countPlayerBarreira(playerid) >= 4) return SendClientMessage(playerid, -1, "Você atingiu o limite de 4 barreiras.");

	if (createPlayerBarreira(playerid) == -1) return SendClientMessage(playerid, -1, "O servidor está com o máximo de barreiras criadas (10)...");

	return true;
}
alias:barreira("br")

CMD:rbarreira(playerid)
{
    new barreiraid = getPositionObject(playerid, OBJECT_TYPE_BARREIRA);

	if (barreiraid == -1) return SendClientMessage(playerid, -1, "Você não está próximo de uma barreira.");

	if (!IsPlayerOwnerBarreira(playerid, barreiraid)) return SendClientMessage(playerid, -1, "Você não tem autorização para remover essa barreira.");

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
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

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

    	SendClientMessage(playerid, -1, "Você colocou um bloqueio, para remover use: /rbloqueio.");

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

	if (!PlayerIsBloqueio(playerid)) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (GetPlayerInterior(playerid) > 0)
		return SendClientMessage(playerid, COLOR_YELLOW, "Voc no pode colocar um bloqueio num interior.");

    if (countPlayerBloqueio(playerid) >= 2 && PlayerInfo[playerid][pVIP] < 8)
		return SendClientMessage(playerid, -1, "Você poderá colocar até 4 bloqueios caso for Sócio Extreme.");

	if (countPlayerBloqueio(playerid) >= 4) return SendClientMessage(playerid, -1, "Você atingiu o limite de 4 bloqueios.");

	if (createPlayerBloqueio(playerid) == -1) return SendClientMessage(playerid, -1, "O servidor está com o máximo de bloqueios criados (15)...");

	return true;
}
alias:bq("bloqueio")

CMD:rbloqueio(playerid)
{
    new bloqueioid = getPositionObject(playerid, OBJECT_TYPE_BLOQUEIO);

	if (bloqueioid == -1) return SendClientMessage(playerid, -1, "Você não está próximo de um bloqueio.");

	if (!IsPlayerOwnerBloqueio(playerid, bloqueioid)) return SendClientMessage(playerid, -1, "Você não tem autorização para remover esse bloqueio.");

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
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

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