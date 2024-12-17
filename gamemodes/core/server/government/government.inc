

#include <YSI_Coding\y_hooks>

#define	COLOR_GOVERNMENT	0x1B4B8EFF

#define		MAX_JOBS						45
#define		MAX_EMPREGOS            		20
// Configurações do governo
enum govInfo
{
	// Salário
	wageJob,
};
new WageJob[govInfo][MAX_JOBS];

new bool:inscricoes_casinhas = false;

stock bool:Government_SubsHouse()
	return inscricoes_casinhas;
// --------------------------------------------

new casa_governo = -1;

stock Government_GetHouse()
	return casa_governo;

stock Government_SetHouse(house)
	casa_governo = house;

// Salário do emprego
stock GetWageJob(jobid)
	return WageJob[wageJob][jobid];

// Sistema de bolsa família

enum bolsafamilia_ENUM
{
	bool: bolsaFamilia,
	bolsaValor,
	bolsaLimite,
	bolsaSaques,
	bolsaPlayers
}
new BolsaFamilia[bolsafamilia_ENUM];

stock BolsaFamilia_GetActive()
	return BolsaFamilia[bolsaFamilia];

new Iterator:IterSubsHouse<MAX_PLAYERS>;

new BolsaFamiliaDiario, LimiteBolsaFamilia;

timer timer_BolsaFamilia[60000 * 10]()
{
	if (BolsaFamilia[bolsaFamilia])
	{
		foreach(new i : Player) playerBolsaFamilia[i] = false;

		new string[128];

		SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
		SendClientMessageToAll(-1, "O programa '{92ED91}Bolsa Família{FFFFFF}' finalizou, informações de saque abaixo:");
		format(string, sizeof(string), "Valor sacado: {00AA00}$%s {FFFFFF}| Sacado por: {00FF00}%d pessoas", getFormatText(BolsaFamilia[bolsaSaques]), BolsaFamilia[bolsaPlayers]);
		SendClientMessageToAll(-1, string);
		SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

		BolsaFamilia[bolsaFamilia] = false, BolsaFamilia[bolsaSaques] = 0, BolsaFamilia[bolsaPlayers] = 0, BolsaFamilia[bolsaValor] = 0;
	}
}

hook OnResetDay() 
{
	BolsaFamiliaDiario = LimiteBolsaFamilia;
	casa_governo = -1;

	if (House_GetOwner(casa_governo) == -2) {
		House_SetOwner(casa_governo, 0, "NULL");
		House_Update(casa_governo);
	}
    return 1;
}

stock ShowDialogSubsHouse(playerid)
{
	if (!inscricoes_casinhas)
		return SendClientMessage(playerid, -1, "O governo ainda não abriu inscrições para alguma casa.");

	if (!Houses_CheckLimit(playerid)) 
		return SendClientMessage(playerid, -1, "O seu nível de sócio não permite ter mais casas.");

	new value = House_GetValue(casa_governo);

	new string[128];
	MEGAString[0] = EOS;

	strcat(MEGAString, "{FFFFFF}Ficha de inscrição:\n\n");
	format(string, sizeof string, "{FFFFFF}Olá senhor(a) %s,\n", PlayerName[playerid]);
	strcat(MEGAString, string);
	format(string, sizeof string, "{FFFFFF}Você vai se inscrever para a casa %d avaliada em {00AA00}$%s\n", casa_governo, getFormatText(value));
	strcat(MEGAString, string);
	strcat(MEGAString, "{FFFFFF}Será sorteado um dos inscritos aleatoriamente 20 minutos após abrir as inscrições\n");
	strcat(MEGAString, "{FFFFFF}Assine {00FF00}COM SEU NICK {FFFFFF}para participar do sorteio da casinha!\n");

	inline D_subshouse(d_playerid, d_dialogid, d_response, d_listitem, string:d_inputtext[])
	{
		#pragma unused d_playerid, d_dialogid, d_listitem

		if (!d_response)
			return true;

		if (!strcmp(d_inputtext, PlayerName[playerid], true))
		{
			if (casa_governo == -1) return true;

			if (!inscricoes_casinhas) return true;

			Iter_Add(IterSubsHouse, playerid);

			format(string, sizeof string, "Parabéns! {0095FF}%s {FFFFFF}você se inscreveu para a casinha: %d", PlayerName[playerid], casa_governo);
			SendClientMessage(playerid, -1, string);
			SendClientMessage(playerid, -1, "Aguarde que em breve será anunciado o ganhador da casinha!");

			return true;
		}
		else
			return SendClientMessage(playerid, -1, "Você não assinou com seu nick.");
	}
	Dialog_ShowCallback(playerid, using inline D_subshouse, DIALOG_STYLE_INPUT, "{DFD136}Ficha de inscrição", MEGAString, "Prosseguir", "Cancelar");
	
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    // Tecla: H
    if (newkeys & KEY_CTRL_BACK)
	{
		if (IsPlayerInRangeOfPoint(playerid, 2.0, SUBSHOUSE_POS_X, SUBSHOUSE_POS_Y, SUBSHOUSE_POS_Z))
			ShowDialogSubsHouse(playerid);
    }
    return 1;
}

hook OnGameModeInit()
{
	LoadSystem_SubsHouses();

	return 1;
}

#define MAX_TAX_TYPES 9

enum TaxType: {
	INSS,
	IRRF,
	FGTS,
	IPTU,
	IRPF,
	IPVA,
	IPI,
	IOF,
	ITR,
};
static TaxInfo[TaxType:MAX_TAX_TYPES];

stock Tax_SetValue(TaxType: tax, value) {
	TaxInfo[tax] = value;
}

stock Tax_GetValue(TaxType: tax) {
	return TaxInfo[tax];
}

stock Tax_GetName(TaxType: tax) {

	new name_tax[6];

	switch (tax) {
		case INSS: name_tax = "INSS";
		case IRRF: name_tax = "IRRF";
		case FGTS: name_tax = "FGTS";
		case IPTU: name_tax = "IPTU";
		case IRPF: name_tax = "IRPF";
		case IPVA: name_tax = "IPVA";
		case IPI: name_tax = "IPI";
		case IOF: name_tax = "IOF";
		case ITR: name_tax = "ITR";
	}
	return name_tax;
}

stock Dialog_EditTax(playerid) 
{
	new string[128],
		inss = Tax_GetValue(INSS),
		irrf = Tax_GetValue(IRRF),
		fgts = Tax_GetValue(FGTS),
		iptu = Tax_GetValue(IPTU),
		irpf = Tax_GetValue(IRPF),
		ipva = Tax_GetValue(IPVA),
		ipi = Tax_GetValue(IPI),
		iof = Tax_GetValue(IOF),
		itr = Tax_GetValue(ITR);

	MEGAString[0] = EOS;

	strcat(MEGAString, "sigla / nome do imposto\tporcentagem atual\n");
	format(string, sizeof(string), ""C_GRAY"INSS		"C_WHITE"Imposto de Renda Pessoa Fisica\t"C_GRAY"%s%%\n", getFormatText(inss));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"IRRF		"C_WHITE"Imposto de Renda Pessoa Fisica\t"C_GRAY"%s%%\n", getFormatText(irrf));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"FGTS		"C_WHITE"Imposto de Renda Pessoa Fisica\t"C_GRAY"%s%%\n", getFormatText(fgts));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"IPTU		"C_WHITE"Imposto de Renda Pessoa Fisica\t"C_GRAY"%s%%\n", getFormatText(iptu));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"IRPF		"C_WHITE"Imposto de Renda Pessoa Fisica\t"C_GRAY"%s%%\n", getFormatText(irpf));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"IPVA		"C_WHITE"Imposto sobre Propriedade de Veiculo Automotor\t"C_GRAY"%s%%\n", getFormatText(ipva));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"IPI			"C_WHITE"Imposto sobre Produtos Industrializados\t"C_GRAY"%s%%\n", getFormatText(ipi));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"IOF			"C_WHITE"Imposto sobre Operações Financeiras\t"C_GRAY"%s%%\n", getFormatText(iof));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"ITR			"C_WHITE"Imposto sobre a Propriedade Territorial Rural\t"C_GRAY"%s%%\n", getFormatText(itr));
	strcat(MEGAString, string);

	inline D_TaxEdit(dtaxyid, dtaxydialogid, dtaxyresponse, dtaxylistitem, string:dtaxytext[])
	{
		#pragma unused dtaxyid, dtaxydialogid, dtaxylistitem, dtaxytext

		if (!dtaxyresponse)
			return callcmd::menugoverno(playerid);

		new TaxType:tax = TaxType:dtaxylistitem;

		inline D_TaxUpdate(dtaxupyid, dtaxupydialogid, dtaxupyresponse, dtaxupylistitem, string:dtaxupytext[])
		{
			#pragma unused dtaxupyid, dtaxupydialogid, dtaxupylistitem

			if (!dtaxupyresponse)
				return 1;

			new taxOldValue = Tax_GetValue(tax),
				taxValue = strval(dtaxupytext);

			if (taxValue < 0 || taxValue > 5)
				return SendClientMessage(playerid, -1, "O valor deve estar entre 0 e 5 por cento."), Dialog_EditTax(playerid);

			SendClientMessageToAll(COLOR_GOVERNMENT, "- ______________________ DIARIO OFICIAL (GOVERNO) ______________________");
			format(string, sizeof(string), "- %s, %s: "C_WHITE"alterou o valor do %s de %s%% para %s%%", 
										GetPlayerCargo(playerid), PlayerName[playerid], Tax_GetName(tax), getFormatText(taxOldValue), getFormatText(taxValue));

			SendClientMessageToAll(COLOR_GOVERNMENT, string);
			SendClientMessageToAll(COLOR_GOVERNMENT, "- ______________________________________________________________________");

			Tax_SetValue(tax, taxValue);
			Dialog_EditTax(playerid);
		}
		format(string, sizeof(string), ""C_GRAY"Editando a porcentagem do %s", Tax_GetName(tax));
		Dialog_ShowCallback(
			playerid, using inline D_TaxUpdate, DIALOG_STYLE_INPUT, 
			string, 
			""C_WHITE"Digite abaixo a porcentagem de 0 a 5 para o imposto:", "Confirmar", "Cancelar"
		);
	}
	Dialog_ShowCallback(
		playerid, using inline D_TaxEdit, DIALOG_STYLE_TABLIST_HEADERS, 
		""C_GRAY"Editar impostos", 
		MEGAString, 
		"Modificar", "Cancelar"
	);
	return 1;
}

stock Dialog_PayTax(playerid) 
{
	new string[128],
		iptu = Tax_GetValue(IPTU),
		itr = Tax_GetValue(ITR),
		ipva = Tax_GetValue(IPVA);

	MEGAString[0] = EOS;

	strcat(MEGAString, "sigla / nome do imposto\tporcentagem atual\tcontinuar\n");
	format(string, sizeof(string), ""C_GRAY"IPTU		"C_WHITE"Imposto Predial e Territorial Urbano\t%s%%\t"C_GRAY"( >>>>>>>> )\n", getFormatText(iptu));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"ITR			"C_WHITE"Imposto sobre Propriedade Territorial Rural\t%s%%\t"C_GRAY"( >>>>>>>> )\n", getFormatText(itr));
	strcat(MEGAString, string);
	format(string, sizeof(string), ""C_GRAY"IPVA		"C_WHITE"Imposto sobre Propriedade de Veiculo Automotor\t%s%%\t"C_GRAY"( >>>>>>>> )\n", getFormatText(ipva));
	strcat(MEGAString, string);

	inline D_TaxPay(dtaxpyid, dtaxpydialogid, dtaxpyresponse, dtaxpylistitem, string:dtaxpytext[])
	{
		#pragma unused dtaxpyid, dtaxpydialogid, dtaxpytext

		if (!dtaxpyresponse)
			return callcmd::loterica(playerid);

		switch (dtaxpylistitem) 
		{
			case 0: {
				// Lote_TaxPay(playerid, IPTU);
				return callcmd::loterica(playerid);
			}
			case 1: {
				// Lote_TaxPay(playerid, ITR);
				return callcmd::loterica(playerid);
			}
			case 2: {
				Vehicle_TaxPay(playerid, IPVA);
			}
		}
	}
	Dialog_ShowCallback(
		playerid, using inline D_TaxPay, DIALOG_STYLE_TABLIST_HEADERS, 
		""C_GRAY"Pagar impostos", 
		MEGAString, 
		"Continuar", "Retornar"
	);

	return 1;
}

stock Player_IsGovernment(playerid) 
{
	if (GetPlayerOrg(playerid) != ID_ORG_GOVERNO)
		return 0;
	
	return 1;
}

CMD:menugoverno(playerid)
{
	if (GetPlayerOrg(playerid) != 7) return SendClientMessage(playerid, -1, "Você não é do governo");

	if (PlayerInfo[playerid][pCargo] < 3) return SendClientMessage(playerid, -1, "Você precisa ser cargo 3+");

	new string[128];
	MEGAString[0] = EOS;

	strcat(MEGAString, "{FFFFFF}Nome da taxa\tValor atual\n");
	format(string, sizeof string, "{FFFFFF}Taxa de impostos (por PayDay)\t{00AA00}$%s\n", getFormatText(GovernoTaxa));
	strcat(MEGAString, string);
	format(string, sizeof string, "{FFFFFF}Multa por nível de procurado\t{FF0000}DESATIVADA\n");
	strcat(MEGAString, string);
	format(string, sizeof string, "{FFFFFF}Imposto sobre Mercadorias/Serviços (ICMS)\t{00AA00}%d por cento\n", ICMS);
	strcat(MEGAString, string);
	format(string, sizeof string, "{FFFFFF}Imposto sobre Prisão\t{FF0000}DESATIVADA\n");
	strcat(MEGAString, string);
	format(string, sizeof string, "{FFFFFF}Inscrições casinhas\t%s\n", inscricoes_casinhas ? ("{00FF00}ABERTAS") : ("{FF0000}FECHADAS"));
	strcat(MEGAString, string);
	format(string, sizeof string, "{FFFFFF}Salário de Lixeiro\t{00AA00}$%s (por KG)\n", getFormatText(GetWageJob(ID_JOB_LIXEIRO)));
	strcat(MEGAString, string);
	format(string, sizeof string, "{FFFFFF}Apoio de Carga\t{00AA00}$%s\n", getFormatText(GetWageJob(ID_JOB_CAMINHONEIRO)));
	strcat(MEGAString, string);
	format(string, sizeof string, "{FFFFFF}Salário de Fazendeiro\t{00AA00}$%s\n", getFormatText(GetWageJob(ID_JOB_FAZENDEIRO)));
	strcat(MEGAString, string);
	format(string, sizeof string, "{FFFFFF}Salário de Bombeiro\t{00AA00}$%s\n", getFormatText(GetWageJob(ID_JOB_FIREFIGHTER)));
	strcat(MEGAString, string);
	format(string, sizeof string, "{FFFFFF}Salário de Médico\t{00AA00}$%s\n", getFormatText(GetWageJob(ID_JOB_MEDICO)));
	strcat(MEGAString, string);

	// Sistema desenvolver...
	//format(string, sizeof string, "Salario Detetive\t{00AA00}$%s (por investigação)\n", getFormatText(GetWageJob(ID_JOB_DETETIVE)));
	//strcat(MEGAString, string);

	inline D_c_menugoverno(dcmenugovid, dcmenugovdialogid, dcmenugovresponse, dcmenugovlistitem, string:dcmenugovtext[])
	{
		#pragma unused dcmenugovid, dcmenugovdialogid, dcmenugovtext
		if (!dcmenugovresponse)
			return SendClientMessage(playerid, -1, "Você cancelou o menu de empregos.");

		switch (dcmenugovlistitem)
		{
			case 0:
			{
				inline D_taxpayday(dtaxpaydayid, dtaxpaydaydialogid, dtaxpaydayresponse, dtaxpaydaylistitem, string:dtaxpaydaytext[])
				{
					#pragma unused dtaxpaydayid, dtaxpaydaydialogid, dtaxpaydaylistitem

					if (!dtaxpaydayresponse)
						return callcmd::menugoverno(playerid);
					
					new NovaTaxa = strval(dtaxpaydaytext);

					if (NovaTaxa < 500 || NovaTaxa > 30000)
					{
						SendClientMessage(playerid, -1, "O valor deve estar entre $500 a $30.000"), callcmd::menugoverno(playerid);
						return true;
					}

					SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
					format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}alterou o valor dos impostos por PayDay", GetPlayerCargo(playerid), PlayerName[playerid]);
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Taxa antiga (por pessoa): {00AA00}$%s {FFFFFF}| Taxa atual (por pessoa): {00AA00}$%s", getFormatText(GovernoTaxa), getFormatText(NovaTaxa));
					SendClientMessageToAll(-1, string);
					SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

					GovernoTaxa = NovaTaxa;
				}
				Dialog_ShowCallback(
					playerid, using inline D_taxpayday, DIALOG_STYLE_INPUT, 
					"{DFD136}Menu do governo", 
					"Digite o novo valor da taxa de impostos abaixo.\n\n\
					O valor deve ser entre $50 e $30.000!", 
					"Confirmar", "Cancelar"
				);
			}
			case 1, 3: 
			{
				return SendClientMessage(playerid, -1, "Essa taxa foi desativada.");
				// inline D_wantedLevelValue(dplayerid, ddialogid, dresponse, dlistitem, string:dtext[])
				// {
				// 	#pragma unused dplayerid, ddialogid, dlistitem

				// 	if (!dresponse)
				// 		return callcmd::menugoverno(playerid);
					
				// 	new NovaTaxa = strval(dtext);

				// 	if (WantedLevelValue == NovaTaxa)
				// 	{
				// 		return SendClientMessage(playerid, -1, "Você não pode colocar o mesmo valor."), callcmd::menugoverno(playerid);
				// 	}

				// 	if (NovaTaxa < 1000 || NovaTaxa > 25000)
				// 	{
				// 		SendClientMessage(playerid, -1, "O valor deve estar entre $1000 a $25.000"), callcmd::menugoverno(playerid);
				// 		return true;
				// 	}

				// 	SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
				// 	format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}alterou a multa por nível de procurado", GetPlayerCargo(playerid), PlayerName[playerid]);
				// 	SendClientMessageToAll(-1, string);
				// 	format(string, sizeof string, "Valor antigo (por nível): {00AA00}$%s {FFFFFF}| Valor atual (por nível): {00AA00}$%s", getFormatText(WantedLevelValue), getFormatText(NovaTaxa));
				// 	SendClientMessageToAll(-1, string);
				// 	SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

				// 	WantedLevelValue = NovaTaxa;

				// 	SaveStuff();
				// }
				// Dialog_ShowCallback(
				// 	playerid, using inline D_wantedLevelValue, DIALOG_STYLE_INPUT, 
				// 	"{DFD136}Menu do governo", 
				// 	"Digite abaixo o valor que será cobrado de multa por nível de procurado.\n\n\
				// 	O valor deve ser entre $1000 e $25.000!", 
				// 	"Confirmar", "Cancelar"
				// );
			}
			case 2: 
			{
				inline D_definirICMS(d_playerid, d_dialogid, d_response, d_listitem, string:d_inputtext[])
				{
					#pragma unused d_playerid, d_dialogid, d_listitem

					if (!d_response)
						return callcmd::menugoverno(playerid);
					
					new NovaTaxa = strval(d_inputtext);

					if (NovaTaxa < 0 || NovaTaxa > 80)
					{
						SendClientMessage(playerid, -1, "O valor deve estar entre 0 e 80"), callcmd::menugoverno(playerid);
						return true;
					}

					SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
					format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}alterou o Imposto sobre Mercadoria e Serviços (ICMS)", GetPlayerCargo(playerid), PlayerName[playerid]);
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Porcentagem antiga: {00AA00}%d {FFFFFF}| Porcentagem atual: {00AA00}%d", ICMS, NovaTaxa);
					SendClientMessageToAll(-1, string);
					SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

					ICMS = NovaTaxa;
					SaveStuff();
				}
				Dialog_ShowCallback(
					playerid, using inline D_definirICMS, DIALOG_STYLE_INPUT, 
					"{DFD136}Menu do governo", 
					"Digite abaixo a nova taxa de ICMS.\n\n\
					O valor deve ser entre 0 e 80 por cento!", 
					"Confirmar", "Cancelar"
				);	
			}
			// case 3: 
			// {
			// 	inline D_definirTaxaPrisao(d_playerid, d_dialogid, d_response, d_listitem, string:d_inputtext[])
			// 	{
			// 		#pragma unused d_playerid, d_dialogid, d_listitem

			// 		if (!d_response)
			// 			return callcmd::menugoverno(playerid);
					
			// 		new NovaTaxa = strval(d_inputtext);

			// 		if (NovaTaxa < 0 || NovaTaxa > 100)
			// 		{
			// 			SendClientMessage(playerid, -1, "O valor deve estar entre 0 e 100 por cento"), callcmd::menugoverno(playerid);
			// 			return true;
			// 		}

			// 		SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
			// 		format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}alterou o Imposto sobre Prisão", GetPlayerCargo(playerid), PlayerName[playerid]);
			// 		SendClientMessageToAll(-1, string);
			// 		format(string, sizeof string, "Porcentagem antiga: {00AA00}%d {FFFFFF}| Porcentagem atual: {00AA00}%d", TaxaPrisao, NovaTaxa);
			// 		SendClientMessageToAll(-1, string);
			// 		SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

			// 		TaxaPrisao = NovaTaxa;
			// 		SaveStuff();
			// 	}
			// 	Dialog_ShowCallback(
			// 		playerid, using inline D_definirTaxaPrisao, DIALOG_STYLE_INPUT, 
			// 		"{DFD136}Menu do governo", 
			// 		"Digite abaixo a nova taxa de imposto sobre prisão.\n\n\
			// 		O valor deve ser entre 0 e 100 por cento!", 
			// 		"Confirmar", "Cancelar"
			// 	);
			// }
			case 4: 
			{
				if (IsLeaderOrg(playerid) != 7)
					return SendClientMessage(playerid, -1, "Apenas o governador pode usar essa função.");

				if (!inscricoes_casinhas)
				{
					inline D_liberarinscricoes(d_playerid, d_dialogid, d_response, d_listitem, string:d_inputtext[])
					{
						#pragma unused d_playerid, d_dialogid, d_listitem

						if (!d_response)
							return callcmd::menugoverno(playerid);

						if (casa_governo == -1)
							return SendClientMessage(playerid, -1, "O governo não tem nenhuma casa para abrir inscrição."), callcmd::menugoverno(playerid);

						if (casa_governo == -2)
							return SendClientMessage(playerid, -1, "O governo já sorteou uma casa hoje.");

						if (ContarJogadores() < SERVER_PLAYER_META) {
							format(string, sizeof(string), "Para abrir as inscrições das casinhas o servidor precisa ter mais de %d online.", SERVER_PLAYER_META);
							SendClientMessage(playerid, -1, string);
							callcmd::menugoverno(playerid);
							return 1;
						}
						new nivel_max = strval(d_inputtext);

						if (nivel_max < 5 || nivel_max > 199)
							return SendClientMessage(playerid, -1, "O nivel maximo deve estar entre 5 á 100."), callcmd::menugoverno(playerid);

						SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
						format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}liberou as inscrições para a casinha %d", GetPlayerCargo(playerid), PlayerName[playerid], casa_governo);
						SendClientMessageToAll(-1, string);
						format(string, sizeof string, "Info: Você precisa ter no máximo nível %d e se inscrever na Prefeitura, use /gps", nivel_max);
						SendClientMessageToAll(-1, string);
						SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

						SetPVarInt(playerid, #tempoInscricao, gettime() + (60 * 5));

						inscricoes_casinhas = true;
					}
					Dialog_ShowCallback(playerid, using inline D_liberarinscricoes, DIALOG_STYLE_INPUT, 
						"{DFD136}Menu do governo", "Abaixo informe qual o nivel maximo para fazer inscricao da casinha:", "Confirmar", "Cancelar");
				}
				else 
				{
					if (gettime() < GetPVarInt(playerid, #tempoInscricao)) {
						format(string, sizeof (string), "Você deve aguardar {82E789}%s {FFFFFF}para usar o comando!", ConvertTempo(PlayerInfo[playerid][pToggleNoob] - gettime()));
						return SendClientMessage(playerid, -1, string);
					}

					new rand = Iter_Random(IterSubsHouse);

					SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
					format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}fechou as inscrições para a casinha %d", GetPlayerCargo(playerid), PlayerName[playerid], casa_governo);
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Info: O sorteio foi realizado e o ganhador é %s(%d)", PlayerName[rand], rand);
					SendClientMessageToAll(-1, string);
					SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

					ScreenStart_HouseBuy(rand, casa_governo);
					House_SetOwner(casa_governo, rand, PlayerName[rand]);
					House_Update(casa_governo);
					House_Save(casa_governo);

					for (new i; i != MAX_PLAYERS; i++)
						Iter_Remove(IterSubsHouse, i);

					casa_governo = -2;
					inscricoes_casinhas = false;
				}
			}
			case 5: 
			{
				inline D_salariolixeiro(dwagelixeiroid, dwagelixeirodialogid, dwagelixeiroresponse, dwagelixeirolistitem, string:dwagelixeirotext[])
				{
					#pragma unused dwagelixeiroid, dwagelixeirodialogid, dwagelixeirolistitem

					if (!dwagelixeiroresponse)
						return callcmd::menugoverno(playerid);
					
					new NovaTaxa = strval(dwagelixeirotext);

					if (NovaTaxa < 25 || NovaTaxa > 3000)
					{
						SendClientMessage(playerid, -1, "O valor deve estar entre $25 a $3.000"), callcmd::menugoverno(playerid);
						return true;
					}

					SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
					format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}alterou o pagamento por KG de lixo", GetPlayerCargo(playerid), PlayerName[playerid]);
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Preço antigo (por KG): {00AA00}$%s {FFFFFF}| Preço atual (por KG): {00AA00}$%s", getFormatText(GetWageJob(ID_JOB_LIXEIRO)), getFormatText(NovaTaxa));
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Cada gari estará recebendo {00AA00}$%s {FFFFFF}á cada 100KGs entregue.", getFormatText(NovaTaxa*100));
					SendClientMessageToAll(-1, string);
					SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

					WageJob[wageJob][ID_JOB_LIXEIRO] = NovaTaxa;

					SaveStuff();
				}
				Dialog_ShowCallback(
					playerid, using inline D_salariolixeiro, DIALOG_STYLE_INPUT, 
					"{DFD136}Menu do governo", 
					"Digite abaixo o valor que pagará por KGs para lixeiros\n\n\
					O valor deve ser entre $25 e $3.000!", 
					"Confirmar", "Cancelar"
				);	
			}
			case 6: 
			{
				inline D_salariocaminhoneiro(dwagecaminhoneiroid, dwagecaminhoneirodialogid, dwagecaminhoneiroresponse, dwagecaminhoneirolistitem, string:dwagecaminhoneirotext[])
				{
					#pragma unused dwagecaminhoneiroid, dwagecaminhoneirodialogid, dwagecaminhoneirolistitem

					if (!dwagecaminhoneiroresponse)
						return callcmd::menugoverno(playerid);
					
					new NovaTaxa = strval(dwagecaminhoneirotext);

					if (NovaTaxa < 5000 || NovaTaxa > 120000)
					{
						SendClientMessage(playerid, -1, "O valor deve estar entre $5.000 a $120.000"), callcmd::menugoverno(playerid);
						return true;
					}

					SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
					format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}alterou o apoio às cargas dos caminhoneiros", GetPlayerCargo(playerid), PlayerName[playerid]);
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Valor antigo do apoio: {00AA00}$%s {FFFFFF}| Novo valor do apoio: {00AA00}$%s", getFormatText(GetWageJob(ID_JOB_CAMINHONEIRO)), getFormatText(NovaTaxa));
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Cada caminhoneiro receberá {00AA00}$%s {FFFFFF}de apoio a cada entrega realizada.", getFormatText(NovaTaxa));
					SendClientMessageToAll(-1, string);
					SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

					WageJob[wageJob][ID_JOB_CAMINHONEIRO] = NovaTaxa;

					SaveStuff();
				}
				Dialog_ShowCallback(
					playerid, using inline D_salariocaminhoneiro, DIALOG_STYLE_INPUT, 
					"{DFD136}Menu do governo", 
					"Digite abaixo o valor que pagará pelo apoio aos caminhoneiros\n\n\
					O valor deve ser entre $5.000 e $120.000!", 
					"Confirmar", "Cancelar"
				);	
			}
			case 7: 
			{
				inline D_salariofazendeiro(dwagefazendeiroid, dwagefazendeirodialogid, dwagefazendeiroresponse, dwagefazendeirolistitem, string:dwagefazendeirotext[])
				{
					#pragma unused dwagefazendeiroid, dwagefazendeirodialogid, dwagefazendeirolistitem

					if (!dwagefazendeiroresponse)
						return callcmd::menugoverno(playerid);
					
					new NovaTaxa = strval(dwagefazendeirotext);

					if (NovaTaxa < 2000 || NovaTaxa > 70000)
					{
						SendClientMessage(playerid, -1, "O valor deve estar entre $5.000 a $70.000"), callcmd::menugoverno(playerid);
						return true;
					}

					SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
					format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}alterou o salário dos Fazendeiros", GetPlayerCargo(playerid), PlayerName[playerid]);
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Valor antigo do salário: {00AA00}$%s {FFFFFF}| Novo valor do salário: {00AA00}$%s", getFormatText(GetWageJob(ID_JOB_FAZENDEIRO)), getFormatText(NovaTaxa));
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Cada fazendeiro receberá {00AA00}$%s {FFFFFF}por cada colheita feita.", getFormatText(NovaTaxa));
					SendClientMessageToAll(-1, string);
					SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

					WageJob[wageJob][ID_JOB_FAZENDEIRO] = NovaTaxa;

					SaveStuff();
				}
				Dialog_ShowCallback(
					playerid, using inline D_salariofazendeiro, DIALOG_STYLE_INPUT, 
					"{DFD136}Menu do governo", 
					"Digite abaixo o valor que pagará pela colheita dos fazendeiros\n\n\
					O valor deve ser entre $2.000 e $70.000!", 
					"Confirmar", "Cancelar"
				);	
			}
			case 8: 
			{
				inline D_salariobombeiro(dwagebombeiroid, dwagebombeirodialogid, dwagebombeiroresponse, dwagebombeirolistitem, string:dwagebombeirotext[])
				{
					#pragma unused dwagebombeiroid, dwagebombeirodialogid, dwagebombeirolistitem

					if (!dwagebombeiroresponse)
						return callcmd::menugoverno(playerid);
					
					new NovaTaxa = strval(dwagebombeirotext);

					if (NovaTaxa < 5000 || NovaTaxa > 70000)
					{
						SendClientMessage(playerid, -1, "O valor deve estar entre $5.000 a $70.000"), callcmd::menugoverno(playerid);
						return true;
					}

					SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
					format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}alterou o salário dos Bombeiros", GetPlayerCargo(playerid), PlayerName[playerid]);
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Valor antigo do salário: {00AA00}$%s {FFFFFF}| Novo valor do salário: {00AA00}$%s", getFormatText(GetWageJob(ID_JOB_FIREFIGHTER)), getFormatText(NovaTaxa));
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Cada bombeiro receberá {00AA00}$%s {FFFFFF} de salário.", getFormatText(NovaTaxa));
					SendClientMessageToAll(-1, string);
					SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

					WageJob[wageJob][ID_JOB_FIREFIGHTER] = NovaTaxa;

					SaveStuff();
				}
				Dialog_ShowCallback(
					playerid, using inline D_salariobombeiro, DIALOG_STYLE_INPUT, 
					"{DFD136}Menu do governo", 
					"Digite abaixo o valor que pagará pelo trabalho dos bombeiros\n\n\
					O valor deve ser entre $5.000 e $70.000!", 
					"Confirmar", "Cancelar"
				);	
			}
			case 9: 
			{
				inline D_salariomedico(dwagemedicoid, dwagemedicodialogid, dwagemedicoresponse, dwagemedicolistitem, string:dwagemedicotext[])
				{
					#pragma unused dwagemedicoid, dwagemedicodialogid, dwagemedicolistitem

					if (!dwagemedicoresponse)
						return callcmd::menugoverno(playerid);
					
					new NovaTaxa = strval(dwagemedicotext);

					if (NovaTaxa < 5000 || NovaTaxa > 90000)
					{
						SendClientMessage(playerid, -1, "O valor deve estar entre $5.000 a $90.000"), callcmd::menugoverno(playerid);
						return true;
					}

					SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
					format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}alterou o salário dos Médicos", GetPlayerCargo(playerid), PlayerName[playerid]);
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Valor antigo do salário: {00AA00}$%s {FFFFFF}| Novo valor do salário: {00AA00}$%s", getFormatText(GetWageJob(ID_JOB_MEDICO)), getFormatText(NovaTaxa));
					SendClientMessageToAll(-1, string);
					format(string, sizeof string, "Cada médico receberá {00AA00}$%s {FFFFFF}pelo seu serviço na área da saúde.", getFormatText(NovaTaxa));
					SendClientMessageToAll(-1, string);
					SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

					WageJob[wageJob][ID_JOB_MEDICO] = NovaTaxa;

					SaveStuff();
				}
				Dialog_ShowCallback(
					playerid, using inline D_salariomedico, DIALOG_STYLE_INPUT, 
					"{DFD136}Menu do governo", 
					"Digite abaixo o valor que pagará pelo trabalho dos bombeiros\n\n\
					O valor deve ser entre $5.000 e $90.000!", 
					"Confirmar", "Cancelar"
				);	
			}
			default: callcmd::menugoverno(playerid);
		}
	}
	Dialog_ShowCallback(playerid, using inline D_c_menugoverno, DIALOG_STYLE_TABLIST_HEADERS, "{DFD136}Menu do governo", MEGAString, "Modificar", "Cancelar");
    return 1;
}

// Hooks
stock LoadSystem_SubsHouses()
{
	// Sistema de inscrições casinhas do governo
    CreateDynamicPickup(1273, 1, SUBSHOUSE_POS_X, SUBSHOUSE_POS_Y, SUBSHOUSE_POS_Z);
    Create3DTextLabel("{FFFFFF}Inscrições das casinhas do governo\nPressione "_KEY_PATH_USE_HORN_COLOR" {FFFFFF}para se inscrever", 0xFFFFFFFF, 358.9051, 167.8140, 1008.3828, 5.0, 0);

    return 1;
}

CMD:bolsafamilia(playerid, params[])
{
    if (gettime() < GetPVarInt(playerid, #varFlood_bolsafamilia)) return SendClientMessage(playerid, -1, "Você não pode usar esse comando com tanta frequência.");

    if (GetPlayerOrg(playerid) == 7 && PlayerInfo[playerid][pCargo] > 3)
	{
		if (sscanf(params, "s[128]", params))
		{
		    SendClientMessage(playerid, -1, "Modo de uso: /bolsafamilia (nome) (quantidade)");
		    SendClientMessage(playerid, COLOR_GRAD, "NOMES: iniciar | finalizar | limite");
	 		SendClientMessage(playerid, COLOR_GRAD, "_________________________________________________");
			return true;
		}

		new string[128], null[25];

		if (strfind(params, "iniciar", true) != -1)
		{
			new valorDistribuido;
			if (sscanf(params, "s[25]d", null, valorDistribuido)) return SendClientMessage(playerid, -1, "Modo de uso: /bolsafamilia iniciar (valor distribuido)");

			if (CofreOrg[7][orgDinheiro] < valorDistribuido) return SendClientMessage(playerid, -1, "O valor distruido é maior do que possui no cofre do governo.");

			if (valorDistribuido < 500000 || valorDistribuido > 10000000) return SendClientMessage(playerid, -1, "O valor a ser distribuido deve estar entre $500.000 a $10.000.000.");

			if (BolsaFamilia[bolsaFamilia]) return SendClientMessage(playerid, -1, "O bolsa família já está iniciado.");

			if(BolsaFamiliaDiario == 0) return SendClientMessage(playerid, -1, "O limite diário de bolsa família já foi excedido.");

			if(gettime() < GetSVarInt("FloodBolsaFamilia")) {
				return SendMsgF(playerid, -1, "Aguarde %s para fazer um bolsa família novamente.", ConvertTempo(GetSVarInt("FloodBolsaFamilia") - gettime()));
			}

			foreach(new i : Player) playerBolsaFamilia[i] = true;

			BolsaFamilia[bolsaFamilia] = true; 
			BolsaFamilia[bolsaValor] = valorDistribuido;

			defer timer_BolsaFamilia();

			SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
			format(string, sizeof(string), "%s, %s liberou o programa '{92ED91}Bolsa Família{FFFFFF}' para a população online no momento", GetPlayerCargo(playerid), PlayerName[playerid]);
			SendClientMessageToAll(-1, string);
			format(string, sizeof(string), "Valor distribuido: {00AA00}$%s {FFFFFF}| Valor por pessoa: {00AA00}$%s", getFormatText(valorDistribuido), getFormatText(BolsaFamilia[bolsaLimite]));
			SendClientMessageToAll(-1, string);
			format(string, sizeof(string), "Local para saque: {FFF000}Qualquer lotérica {FFFFFF}| Finaliza em: {F66565}10 minutos");
			SendClientMessageToAll(-1, string);
			SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");
			SendClientMessageToAll(COLOR_LIGHTRED, "Observação: Se caso você deslogar, vai perder a permissão de sacar o bolsa família.");

			BolsaFamiliaDiario -= 1;

			// Novamente só após 30 minutos
			SetSVarInt("FloodBolsaFamilia", gettime() + 30 * 60);
		}

		else if (!strcmp(params, "finalizar", true))
		{
		    if (!BolsaFamilia[bolsaFamilia]) return SendClientMessage(playerid, -1, "O programa bolsa família não foi liberado, use /bolsafamilia iniciar.");

		    foreach(new i : Player) playerBolsaFamilia[i] = false;

		    SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
			format(string, sizeof(string), "%s, %s finalizou o programa '{92ED91}Bolsa Família{FFFFFF}' informações de saque abaixo:", GetPlayerCargo(playerid), PlayerName[playerid]);
			SendClientMessageToAll(-1, string);
			format(string, sizeof(string), "Valor sacado: {00AA00}$%s {FFFFFF}| Sacado por: {00FF00}%d pessoas", getFormatText(BolsaFamilia[bolsaSaques]), BolsaFamilia[bolsaPlayers]);
			SendClientMessageToAll(-1, string);
			SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

			BolsaFamilia[bolsaFamilia] = false, BolsaFamilia[bolsaSaques] = 0, BolsaFamilia[bolsaPlayers] = 0, BolsaFamilia[bolsaValor] = 0;
		}

		else if (strfind(params, "limite", true) != -1)
		{
		    if (BolsaFamilia[bolsaFamilia]) return SendClientMessage(playerid, -1, "Você não pode usar o comando enquanto o bolsa família estiver iniciado.");

			new valorSaque;
			if (sscanf(params, "s[25]d", null, valorSaque)) return SendClientMessage(playerid, -1, "Modo de uso: /bolsafamilia limite (valor de saque por pessoa)");

			if (valorSaque < 300000 || valorSaque > 500000) return SendClientMessage(playerid, -1, "O valor a ser sacado por pessoa deve estar entre $300.000 a $500.000.");

			SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
			format(string, sizeof(string), "%s, %s alterou o programa '{92ED91}Bolsa Família{FFFFFF}' informações abaixo:", GetPlayerCargo(playerid), PlayerName[playerid]);
			SendClientMessageToAll(-1, string);
			format(string, sizeof(string), "Limite antigo (por pessoa): {F66565}$%s {FFFFFF}| Limite atual (por pessoa): {00AA00}$%s", getFormatText(BolsaFamilia[bolsaLimite]), getFormatText(valorSaque));
			SendClientMessageToAll(-1, string);
			SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

			BolsaFamilia[bolsaLimite] = valorSaque, SaveStuff();
		}
		else
		{
			SendClientMessage(playerid, -1, "Modo de uso: /bolsafamilia (nome) (quantidade)");
		    SendClientMessage(playerid, COLOR_GRAD, "NOMES: iniciar | finalizar | limite");
	 		SendClientMessage(playerid, COLOR_GRAD, "_________________________________________________");
			return true;
		}
	}
	else return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    SetPVarInt(playerid, #varFlood_bolsafamilia, gettime() + 60);

    return true;
}

CMD:dartaxa(playerid, params[])
{
	new givetax,
		string[128];

	if(sscanf(params, "s[8]d", params, givetax)){
	    SendClientMessage(playerid, -1, "Use: /dartaxa [nome] [valor]");
	    SendClientMessage(playerid, COLOR_GRAD, "NOMES: cops | neutras");
        SendClientMessage(playerid, COLOR_GRAD, "____________________________________________________________");
		return 1;
	}

	if (GetPlayerOrg(playerid) == 7 && PlayerInfo[playerid][pCargo] > 3)
	{
		if(!strcmp(params, "cops", true))
		{
			new Cops = 0;

	   	    if (CofreOrg[7][orgDinheiro] < givetax) return SendClientMessage(playerid, -1, "O cofre do Governo não tem esse dinheiro todo!");

	   	    if (givetax < 10000 || givetax > 1000000) {
	   	        return SendClientMessage(playerid, -1, "O valor deve estar entre $10.000 e $1.000.000!");
	   	    }

	 		if (gettime() < GetSVarInt("lastTax")) {
	            return SendClientMessage(playerid, -1, "Você só pode dar taxa de 1 em 1 hora!");
	   	    }

			foreach(new i : Player)
			{
			    if(IsACop(i))
			    {
			        Cops ++;
			    }
			}
			if(Cops >= 5)
			{
			    SetSVarInt("taxCops", givetax);
			    SetSVarInt("taxCopsTotal", Cops);

			    MEGAString[0] = EOS;

			    format(string, sizeof(string), "{FFFFFF}Você está prestes a distribuir {00AA00}$%s {FFFFFF}para todos os policiais online:\n\n", getFormatText(givetax));
			    strcat(MEGAString, string);

			    format(string, sizeof(string), "{F5DEB3}* Numero de policiais online: {FFFFFF}%d\n", Cops);
			    strcat(MEGAString, string);
			    format(string, sizeof(string), "{F5DEB3}* Valor que cada um receberá: {00AA00}$%s\n\n", getFormatText(givetax / Cops));
			    strcat(MEGAString, string);
				strcat(MEGAString, "{FF5500}OBS: {AAAAAA}Todo o dinheiro distribuído sairá do cofre do Governo!");

			    ShowPlayerDialog(playerid, 5363, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Distribuir", "Cancelar");

			} else {
			    SendClientMessage(playerid, -1, "Precisa de no mínimo 5 policiais online !");
	   		}
 		}
 		if(!strcmp(params, "neutras", true))
		{
			new Neutras = 0;

	   	    if(CofreOrg[7][orgDinheiro] < givetax)
				return SendClientMessage(playerid, -1, "O cofre do Governo não tem esse dinheiro todo!");

	  		if (givetax < 10000 || givetax > 800000) {
	            return SendClientMessage(playerid, -1, "O valor deve estar entre $10.000 e $800.000!");
			}

	  		if (gettime() < GetSVarInt("lastTax2")) {
	    		return SendClientMessage(playerid, -1, "Você só pode dar taxa de 1 em 1 horas!");
	 		}

			foreach(new i : Player)
			{
			    if(IsANeutra(i))
			    {
			        Neutras ++;
			    }
			}
			if(Neutras >= 5)
			{
			    SetSVarInt("taxNeutras", givetax);
			    SetSVarInt("taxNeutrasTotal", Neutras);

			    MEGAString[0] = EOS;

			    format(string, sizeof(string), "{FFFFFF}Você está prestes a distribuir {00AA00}$%s {FFFFFF}para todos os membros de org neutra online:\n\n", getFormatText(givetax));
			    strcat(MEGAString, string);

			    format(string, sizeof(string), "{F5DEB3}* Numero de membros org neutra online: {FFFFFF}%d\n", Neutras);
			    strcat(MEGAString, string);
			    format(string, sizeof(string), "{F5DEB3}* Valor que cada um receberá: {00AA00}$%s\n\n", getFormatText(givetax / Neutras));
			    strcat(MEGAString, string);
			    strcat(MEGAString, "{FF5500}OBS: {AAAAAA}Todo o dinheiro distribuído sairá do cofre do Governo!");

			    ShowPlayerDialog(playerid, 5364, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Distribuir", "Cancelar");

			} else {
			    SendClientMessage(playerid, -1, "Precisa de no mínimo 5 membros de org neutra online !");
	   		}
 		}
	}
	else SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	return true;
}

CMD:dartaxaorg(playerid, params[])
{
	new org, givetax,
		string[128];

	if(sscanf(params, "dd", org, givetax)){
	    SendClientMessage(playerid, -1, "Use: /dartaxaorg [id da org] [valor]");
        SendClientMessage(playerid, COLOR_GRAD, "____________________________________________________________");
		return 1;
	}

	if (GetPlayerOrg(playerid) == 7 && PlayerInfo[playerid][pCargo] > 3)
	{
		new Membros = 0;

		if (CofreOrg[7][orgDinheiro] < givetax) return SendClientMessage(playerid, -1, "O cofre do Governo não tem esse dinheiro todo!");
		if (givetax < 10000 || givetax > 500000) {
			return SendClientMessage(playerid, -1, "O valor deve estar entre $10.000 e $500.000!");
		}
		if (gettime() < GetSVarInt("lastTax3")) {
			return SendClientMessage(playerid, -1, "Você só pode dar taxa de 1 em 1 hora!");
		}
		if(!IsACopOrg(org))
			return SendClientMessage(playerid, -1, "O ID informado não é uma organização policial!");

		foreach(new i : Player)
		{
			if(GetPlayerOrg(i) == org)
			{
				Membros ++;
			}
		}
		if(Membros >= 3)
		{
			SetSVarInt("taxMembros", givetax);
			SetSVarInt("taxMembrosTotal", Membros);
			SetSVarInt("taxOrg", org);

			MEGAString[0] = EOS;

			format(string, sizeof(string), "{FFFFFF}Você está prestes a distribuir {00AA00}$%s {FFFFFF}para a organização %s:\n\n", getFormatText(givetax), GetNomeOrg(org));
			strcat(MEGAString, string);

			format(string, sizeof(string), "{F5DEB3}* Numero de membros online: {FFFFFF}%d\n", Membros);
			strcat(MEGAString, string);
			format(string, sizeof(string), "{F5DEB3}* Valor que cada um receberá: {00AA00}$%s\n\n", getFormatText(givetax / Membros));
			strcat(MEGAString, string);
			strcat(MEGAString, "{FF5500}OBS: {AAAAAA}Todo o dinheiro distribuído sairá do cofre do Governo!");

			ShowPlayerDialog(playerid, 5365, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Distribuir", "Cancelar");

		} else {
			SendClientMessage(playerid, -1, "Precisa de no mínimo 3 policiais online na organização!");
		}
	}
	else SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	return true;
}

CMD:toquerecolher(playerid, params[])
{
    if(IsLeaderOrg(playerid) != 7) {
		return SendClientMessage(playerid, -1, "Você não pode usar este comando !");
	}

    if(gettime() < GetSVarInt("toque")) {
		return SendClientMessage(playerid, -1, "Alguém já tocou o alarme a pouco tempo !");
	}

	new string[128];
	format(string, sizeof(string), "[Toque de recolher]: %s tocou a sirene do toque de recolher.", PlayerName[playerid]);
	SendClientMessageToAll(COLOR_LIGHTRED, string);
	foreach(new x : Player)
	    PlayAudioStreamForPlayer(x, "http://sounds.brasilnewstart.com.br/sounds/toque_recolher.mp3");

	SetSVarInt("toque", gettime() + 60);

	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new string[128];

    if (dialogid == 5363)
	{
	    if (response) {
            new taxsv = GetSVarInt("taxCops");
			new price = GetSVarInt("taxCops") / GetSVarInt("taxCopsTotal");

    	    if (OrgInfo_GetMoney(ID_ORG_GOVERNO) < taxsv)
				return SendClientMessage(playerid, -1, "O cofre do Governo não tem esse dinheiro todo!");

			removerDinheiroGoverno(taxsv);

            SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
			format(string, sizeof(string), "%s, {0095FF}%s {FFFFFF}deu bônus aos policiais onlines no momento.", GetPlayerCargo(playerid), PlayerName[playerid]);
			SendClientMessageToAll(-1, string);
			format(string, sizeof(string), "Valor distribuido: {00AA00}$%s {FFFFFF}| Policiais online: {FFF000}%d", getFormatText(taxsv), GetSVarInt("taxCopsTotal"));
			SendClientMessageToAll(-1, string);
			format(string, sizeof(string), "Cada policial recebeu {00AA00}$%s {FFFFFF}da distribuição do governo.", getFormatText(price));
			SendClientMessageToAll(-1, string);
			SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

			SetSVarInt("lastTax", gettime() + 3600);
		    foreach(new i : Player)
			{
			    if (IsACop(i))
			    {
			       	format(string, sizeof(string), "* {FFFFFF}Você recebeu {00AA00}$%s {FFFFFF}do banco de impostos do Governo.", getFormatText(price));
					SendClientMessage(i, 0x00AA00FF, string);
					Player_AddMoney(i, price);
			   	}
			}
		}
	    return 1;
	}

	if (dialogid == 5364) 
    {
	    if (response) {
            new taxsv = GetSVarInt("taxNeutras");
			new price = GetSVarInt("taxNeutras") / GetSVarInt("taxNeutrasTotal");

    	    if(OrgInfo_GetMoney(ID_ORG_GOVERNO) < taxsv)
				return SendClientMessage(playerid, -1, "O cofre do Governo não tem esse dinheiro todo!");

            removerDinheiroGoverno(taxsv);

            SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
			format(string, sizeof(string), "%s, {0095FF}%s {FFFFFF}deu bônus aos membros de organizações neutras.", GetPlayerCargo(playerid), PlayerName[playerid]);
			SendClientMessageToAll(-1, string);
			format(string, sizeof(string), "Valor distribuido: {00AA00}$%s {FFFFFF}| Membros online: {FFF000}%d", getFormatText(taxsv), GetSVarInt("taxNeutrasTotal"));
			SendClientMessageToAll(-1, string);
			format(string, sizeof(string), "Cada membro recebeu {00AA00}$%s {FFFFFF}da distribuição do governo.", getFormatText(price));
			SendClientMessageToAll(-1, string);
			SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

			SetSVarInt("lastTax2", gettime() + 3600);
		    foreach(new i : Player)
			{
			    if(IsANeutra(i))
			    {
			       	format(string, sizeof(string), "* {FFFFFF}Você recebeu {00AA00}$%s {FFFFFF}do banco de impostos do Governo.", getFormatText(price));
					SendClientMessage(i, 0x00AA00FF, string);
					Player_AddMoney(i, price);
			   	}
			}
		}
	    return 1;
	}

	if (dialogid == 5365) 
    {
	    if (response) {
            new taxsv = GetSVarInt("taxMembros");
			new price = GetSVarInt("taxMembros") / GetSVarInt("taxMembrosTotal");
			new org = GetSVarInt("taxOrg");

    	    if(OrgInfo_GetMoney(ID_ORG_GOVERNO) < taxsv)
				return SendClientMessage(playerid, -1, "O cofre do Governo não tem esse dinheiro todo!");

            removerDinheiroGoverno(taxsv);

            SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
			format(string, sizeof(string), "%s, {0095FF}%s {FFFFFF}deu bônus aos membros da organização %s.", GetPlayerCargo(playerid), PlayerName[playerid], GetNomeOrg(org));
			SendClientMessageToAll(-1, string);
			format(string, sizeof(string), "Valor distribuido: {00AA00}$%s {FFFFFF}| Membros online: {FFF000}%d", getFormatText(taxsv), GetSVarInt("taxMembrosTotal"));
			SendClientMessageToAll(-1, string);
			format(string, sizeof(string), "Cada membro recebeu {00AA00}$%s {FFFFFF}da distribuição do governo.", getFormatText(price));
			SendClientMessageToAll(-1, string);
			SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

			SetSVarInt("lastTax3", gettime() + 3600);
		    foreach(new i : Player)
			{
			    if(GetPlayerOrg(i) == org)
			    {
			       	format(string, sizeof(string), "* {FFFFFF}Você recebeu {00AA00}$%s {FFFFFF}do banco de impostos do Governo.", getFormatText(price));
					SendClientMessage(i, 0x00AA00FF, string);
					Player_AddMoney(i, price);
			   	}
			}
		}
	    return 1;
	}
    return 1;
}

stock InscricoesCasinhas(playerid) {
	if (!inscricoes_casinhas)
	{
		inline D_liberarinscricoes(d_playerid, d_dialogid, d_response, d_listitem, string:d_inputtext[])
		{
			#pragma unused d_playerid, d_dialogid, d_listitem

			if (!d_response)
				return callcmd::menugoverno(playerid);

			if (casa_governo == INVALID_HOUSE_ID)
				return SendClientMessage(playerid, -1, "O governo não tem nenhuma casa para abrir inscrição."), callcmd::menugoverno(playerid);

			if (casa_governo == -2)
				return SendClientMessage(playerid, -1, "O governo já sorteou uma casa hoje.");

			if (ContarJogadores() < SERVER_PLAYER_META)
				return SendClientMessage(playerid, -1, "Para abrir as inscrições das casinhas o servidor precisa ter mais de "SERVER_PLAYER_META" online."), callcmd::menugoverno(playerid);
			
			new nivel_max = strval(d_inputtext);

			if (nivel_max < 5 || nivel_max > 199)
				return SendClientMessage(playerid, -1, "O nivel maximo deve estar entre 5 á 100."), callcmd::menugoverno(playerid);

			SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
			format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}liberou as inscrições para a casinha %d", GetPlayerCargo(playerid), PlayerName[playerid], casa_governo);
			SendClientMessageToAll(-1, string);
			format(string, sizeof string, "Info: Você precisa ter no máximo nível %d e se inscrever na Prefeitura, use /gps", nivel_max);
			SendClientMessageToAll(-1, string);
			SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

			SetPVarInt(playerid, #tempoInscricao, gettime() + (60 * 5));

			inscricoes_casinhas = true;
		}
		Dialog_ShowCallback(playerid, using inline D_liberarinscricoes, DIALOG_STYLE_INPUT, 
			"{DFD136}Menu do governo", "Abaixo informe qual o nivel maximo para fazer inscricao da casinha:", "Confirmar", "Cancelar");
	}
	else 
	{
		if (gettime() < GetPVarInt(playerid, #tempoInscricao)) {
			format(string, sizeof (string), "Você deve aguardar {82E789}%s {FFFFFF}para usar o comando!", ConvertTempo(PlayerInfo[playerid][pToggleNoob] - gettime()));
			return SendClientMessage(playerid, -1, string);
		}

		new rand = Iter_Random(IterSubsHouse);

		SendClientMessageToAll(0x0095FFFF, "_____________________________________ Anúncio do governo _____________________________________");
		format(string, sizeof string, "%s, {0095FF}%s {FFFFFF}fechou as inscrições para a casinha %d", GetPlayerCargo(playerid), PlayerName[playerid], casa_governo);
		SendClientMessageToAll(-1, string);
		format(string, sizeof string, "Info: O sorteio foi realizado e o ganhador é %s(%d)", PlayerName[rand], rand);
		SendClientMessageToAll(-1, string);
		SendClientMessageToAll(0x0095FFFF, "______________________________________________________________________________________________");

		StartScreen_HouseBuy(rand, casa_governo);
		House_SetOwner(casa_governo, rand, PlayerName[rand]);

		for (new i; i != MAX_PLAYERS; i++)
			Iter_Remove(IterSubsHouse, i);

		casa_governo = -2;
		inscricoes_casinhas = false;
	}
	return 1;
}