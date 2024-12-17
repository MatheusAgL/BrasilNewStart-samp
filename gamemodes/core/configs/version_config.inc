#if defined _inc_version_control
	#endinput
#endif
#define _inc_version_control true

#define 	MAX_VERSIONS 		10

// -----------------------------------------
// Controle de versão da GameMode

static
	SERVER_VERSION[30],
	SERVER_VERSION_DATE[30],
	SERVER_TEXT_DRAW_COLOR_VERSION[10],
	COLOR_VERSION_GM;

new bool:VERSION_TEST = false;
	
enum EnumVersionInfo 
{
	viID,
	viCode[15],
	Timestamp:viReleaseDate,
	viTDColor[10],
	viColor
};
static VersionInfo[MAX_VERSIONS][EnumVersionInfo];
static Iterator:IterVersions<MAX_VERSIONS>;

stock Version_GetNumber() 
{
	new str[30];
	format(str, sizeof(str), "%s", SERVER_VERSION);
	return str;
}

stock Version_GetColor()
	return COLOR_VERSION_GM;

stock Timestamp:Version_GetDate(version = 0)
	return VersionInfo[version][viReleaseDate];

stock Server_CheckStatus()
{
	new port = GetConsoleVarAsInt("port");
	if (port == 7778) {
		SendRconCommand("hostname Brasil New Start | Servidor de TESTES");               // Definindo o nome do servidor

		SendRconCommand("password "SERVER_PASSWORD"");

		VERSION_TEST = true;
	} else {
		SendRconCommand(DEFAULT_HOSTNAME);

		#if defined _inc_discord_connector
			new string[128];
			format(string, sizeof(string), ":green_circle: **Servidor online... ** IP: "SERVER_IP":"SERVER_PORTA" versão: %s (data: %s) | :video_game:", SERVER_VERSION, SERVER_VERSION_DATE);
			Discord_SendMessage(string, Channel_BatePapo);

			DCC_SendEmbed(Embed_Online);
		#endif

		VERSION_TEST = false;
	}
}

stock OnLoadVersion()
{
	format(SERVER_VERSION, sizeof(SERVER_VERSION), VersionInfo[0][viCode]);

	TimeFormat(VersionInfo[0][viReleaseDate], TIMESTAMP_FORMAT, SERVER_VERSION_DATE);
	format(SERVER_TEXT_DRAW_COLOR_VERSION, sizeof(SERVER_TEXT_DRAW_COLOR_VERSION), VersionInfo[0][viTDColor]);
	COLOR_VERSION_GM = VersionInfo[0][viColor];

	new string[128];
	format(string, sizeof(string), "RPG | Brasil v%s", SERVER_VERSION);
	SetGameModeText(string);
	SendRconCommand(DEFAULT_HOSTNAME);

	printf("-----------------------------------------------------------");
	printf("- VERSAO: %s | COR: %d", SERVER_VERSION, COLOR_VERSION_GM);
	printf("- DATA DE ATUALIZACAO: %s", SERVER_VERSION_DATE);
	printf("-----------------------------------------------------------");
}

stock VersionControl_LoadList() {

	new Statement:stmtLoadVersions = 
		MySQL_PrepareStatement(MySQL_Handle, 
		"SELECT id, code, release_date, td_color, color \
		FROM versions \
		ORDER BY release_date DESC \
		LIMIT 10"
	);

	inline const OnLoadVersions() {
		Iter_Clear(IterVersions);

		new id, 
			code[15], 
			date[20], 
			tdcolor[10], 
			color,
			index;

		MySQL_BindResultInt(stmtLoadVersions, 0, id);
		MySQL_BindResult(stmtLoadVersions, 1, code);
		MySQL_BindResult(stmtLoadVersions, 2, date);
		MySQL_BindResult(stmtLoadVersions, 3, tdcolor);
		MySQL_BindResultInt(stmtLoadVersions, 4, color);

		while (MySQL_Statement_FetchRow(stmtLoadVersions)) {
			index = Iter_Free(IterVersions);

			if (index != INVALID_ITERATOR_SLOT) {
				Iter_Add(IterVersions, index);

				VersionInfo[index][viID] = id;
				format(VersionInfo[index][viCode], 10, code);
				TimeParse(date, MYSQL_TIMESTAMP, VersionInfo[index][viReleaseDate]);
				format(VersionInfo[index][viTDColor], 10, tdcolor);
				VersionInfo[index][viColor] = color;
			}
		}
		OnLoadVersion();
		MySQL_StatementClose(stmtLoadVersions);
	}
	MySQL_ExecuteThreaded_Inline(stmtLoadVersions, using inline OnLoadVersions);
}

stock VersionControl_ChangeLog(playerid, versionid) 
{
	new dbid = VersionInfo[versionid][viID];
	new Statement:stmtLoadChangelog = MySQL_PrepareStatement(MySQL_Handle, "SELECT \
			changelog FROM versions WHERE id = ?");

	MySQL_BindInt(stmtLoadChangelog, 0, dbid);

	inline const OnLoadChangelog() {
		MySQL_BindResult(stmtLoadChangelog, 0, MEGAString);
		MySQL_Statement_FetchRow(stmtLoadChangelog);

		new string[128];
		format(string, sizeof(string), ""C_WHITE"Changelog - "C_YELLOW"%s", VersionInfo[versionid][viCode]);
		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, string, MEGAString, "OK", "");

		MySQL_StatementClose(stmtLoadChangelog);
	}
	MySQL_ExecuteThreaded_Inline(stmtLoadChangelog, using inline OnLoadChangelog);
}

// ------------------------------------------------
// Comandos:

CMD:informacoes(playerid)
{
	MEGAString[0] = EOS;

	strcat(MEGAString, ""C_WHITE"SEJA BEM VINDO AO "S_C_PRIMARY""SERVER_NAME"\n\n\
						"C_YELLOW"	-> "C_WHITE"Nosso servidor conta com um painel do jogador WEB, com varias funcionalidas.\n\
						"C_YELLOW"	-> "C_WHITE"Voce pode denunciar um jogador, quando um Juiz (negar ou aprovar) ele sera automaticamente punido.\n\
						"C_YELLOW"	-> "C_WHITE"Voce pode comprar CASH e gastar na "C_CYAN"/lojacash "C_WHITE", comprar varios itens!\n\
						"C_YELLOW"	-> "C_WHITE"Voce pode ver informacoes da sua conta, regras, abrir uma revisao de banimento, e acompanhar as respostas.\n\
						"C_LIGHTBLUE"	-> "C_WHITE"Nos planejamos varias novas funcionalidades ao PAINEL, de sugestoes, entre em nosso "C_GREEN"DISCORD\n\
						"C_RED"	Obs: "C_WHITE"Para fazer LOGIN em nosso PAINEL, use a mesmo nick e senha da sua conta do jogo!!\n\n\
						"C_WHITE"----------------------------------------------------------------------------------------------------------\n\
						"C_WHITE"		1. Acesse o nosso DISCORD:			"C_GRAY""SERVER_DISCORD"\n\
						"C_WHITE"		2. Curta nossa página do Facebook:		"C_GRAY""SERVER_FACEBOOK"\n\
						"C_WHITE"		3. Siga nossa página no Instagram:		"C_GRAY""SERVER_INSTAGRAM"\n\
						"C_WHITE"		4. Siga nosso servidor no TikTok:		"C_GRAY""SERVER_TIKTOK"\n\
						"C_WHITE"		5. Siga nosso servidor no Kwai:		"C_GRAY""SERVER_TIKTOK"\n\
						"C_WHITE"----------------------------------------------------------------------------------------------------------\n\
						"C_LIGHTGREEN"Aproveite nosso servidor em todas suas areas! Caso precise de ajuda use /ajuda ou /atendimento.");

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, ""C_YELLOW"INFORMACOES", MEGAString, "OK", "");
	return 1;
}
alias:informacoes("ts", "teamspeak", "discord", "painel", "forum")

CMD:creditos(playerid)
{
	MEGAString[0] = EOS;

	strcat(MEGAString, 
		"\n"C_YELLOW"DEVELOPER'S:\n\
		"C_WHITE"		Theus_Crazzy			"C_GREEN"Criador da Comunidade "C_WHITE"| Contato: +55 (43) 99828-5615\n\
		"C_WHITE"		iHollyZinhO			"C_GREEN"Programador "C_WHITE"| Construiu o painel e inúmeros sistemas\n\
		"C_WHITE"		Joao_Revolts		"C_GREEN"Programador "C_WHITE"| Construção de alguns sistemas na GM\n\
		\n"C_BURNED_YELLOW"				-------------------------------------------\n\
		\n"C_YELLOW"The last team:\n\
		"C_WHITE"		Poderoso Supremo		"C_GRAY"| Fundador\n\
		"C_WHITE"		Teni					"C_GRAY"| Responsável Geral\n\
		"C_WHITE"		MaryJane_				"C_GRAY"| Auxiliar Geral\n\
		"C_WHITE"		ChiLeZinhO				"C_GRAY"| Responsavel Developers\n\
		\n"C_BURNED_YELLOW"				-------------------------------------------\n\
		\n"C_YELLOW"Agradecimentos Especiais:\n\
		"C_WHITE"		Joao_Revolts			"C_GRAY"| Ex-Developer StarT Group\n\
		"C_WHITE"		KatarinaJensen			"C_GRAY"| Desenvolvedora\n\
		"C_YELLOW"		E a voce, player da comunidade StarT Group!\
		\n"C_BURNED_YELLOW"				-------------------------------------------\n");


	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, ""C_YELLOW"Créditos do servidor", MEGAString, ""C_SAMP"Fechar", "");

	return 1;
}
alias:creditos("credits")

CMD:atualizacao(playerid)
{
	MEGAString[0] = EOS;

	strcat(MEGAString, "{FFA500}Versão\t{FFA500}Data de Lançamento\n{FFFFFF}");

	new string[128], date[20];
	foreach(new id : IterVersions) {
		TimeFormat(VersionInfo[id][viReleaseDate], TIMESTAMP_FORMAT, date);
		format(
			string, sizeof(string), 
			"%s%s\t%s%s\n", 
			(id == 0) ? (C_GREEN) : (""), 
			VersionInfo[id][viCode], 
			(id == 0) ? (C_GREEN) : (""), 
			date
		);
		strcat(MEGAString, string);
	}

	inline D_ServerUpdates(dyid, dydialogid, dyresponse, dylistitem, string:dytext[])
	{
		#pragma unused dyid, dydialogid, dytext, dyresponse
		if (!dyresponse)
			return 1;

		VersionControl_ChangeLog(playerid, dylistitem);
		return 1;
	}

	Dialog_ShowCallback(
		playerid, using inline D_ServerUpdates, DIALOG_STYLE_TABLIST_HEADERS, "Últimas atualizações do servidor", 
		MEGAString, "Ver changelog", "Sair"
	);
	return 1;
}

CMD:bug(playerid)
	return SendClientMessage(playerid, COLOR_LIGHTRED, "Você deseja reportar um BUG? Entre em nosso /discord e envie na sala '#report-bug'.");