/*  ----------------------------------------------------------------------------------------------------------------------------------------

        Sistema de e-mail;

 ----------------------------------------------------------------------------------------------------------------------------------------- */

#include <YSI_Coding\y_hooks>

// Entrada do módulo
#include <email-entry>

static 
	Statement: stmt_selectEmail,
	Statement: stmt_deleteEmail,
	Statement: stmt_updateEmail,
    Statement: stmt_loadEmails,
    Statement: stmt_insertEmail,
	Statement: stmt_countNotReadEmails;

hook OnMySQLConnected()
{
	// Selecionar e-mail
	static const query_selectEmail[] = 
		"SELECT id, de, mensagem, data, lido FROM `email` WHERE `id` = '?';"
	;
	stmt_selectEmail = MySQL_PrepareStatement(MySQL_Handle, query_selectEmail);

	// Atualizar e-mail
	static const query_updateEmail[] = 
		"UPDATE email SET `lido` = '1' WHERE `id` = '?'"
	;
	stmt_updateEmail = MySQL_PrepareStatement(MySQL_Handle, query_updateEmail);

	// Carregar e-mails
	static const query_loadEmails[] = 
		"SELECT  \
			id, de, mensagem, lido, data \
		FROM \
			`email` \
		WHERE \
			`?` = '?' \
		ORDER BY \
			data DESC \
		LIMIT ?";

    stmt_loadEmails = MySQL_PrepareStatement(MySQL_Handle, query_loadEmails);

	static const query_insertEmail[] = 
		"INSERT INTO `email` (para, de, mensagem, data) VALUES ('?', '?', '?', CURRENT_TIMESTAMP())"
	;

    stmt_insertEmail = MySQL_PrepareStatement(MySQL_Handle, query_insertEmail);

	static const query_deleteEmail[] = 
		"DELETE FROM `email` WHERE `id` = '?'"
	;
	stmt_deleteEmail = MySQL_PrepareStatement(MySQL_Handle, query_deleteEmail);

	static const query_countNotReadEmails[] = 
		"SELECT COUNT(id) FROM `email` WHERE `para` = '?' AND `lido` = '0'"
	;
	stmt_countNotReadEmails = MySQL_PrepareStatement(MySQL_Handle, query_countNotReadEmails);

    return 1;
}


hook OnPlayerSpawn(playerid)
{
	if(!GetPVarInt(playerid, "CountingEmails")) {
		inline const OnCountSelected() {
			new emails;

			MySQL_BindResultInt(stmt_countNotReadEmails, 0, emails);
			MySQL_Statement_FetchRow(stmt_countNotReadEmails);

			if (emails > 0) {
				SendMsgF(playerid, COLOR_NOTIFICATION, ">> NOTIFICAÇÃO: Você tem %d e-mails não lidos em sua caixa de entrada. (Use /email)", emails);
				updateTextDrawEmails(playerid, emails);
			}
			SetPVarInt(playerid, "CountingEmails", 0);
		}
		SetPVarInt(playerid, "CountingEmails", 1);
		MySQL_Bind(stmt_countNotReadEmails, 0, PlayerName[playerid], true);
		MySQL_ExecuteParallel_Inline(stmt_countNotReadEmails, using inline OnCountSelected);
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == 360) 
	{
	    if (response) {
	        switch (listitem) 
			{
	            case 0: 
					EMAIL_List(playerid, EMAIL_INBOX);
	            case 1: 
					EMAIL_List(playerid, EMAIL_OUTBOX);
	            case 2: {
	                ShowPlayerDialog(playerid, 364, DIALOG_STYLE_INPUT, 
						""C_GRAY"Notebook: Enviar um e-mail", 
						""C_WHITE"Digite o "C_YELLOW"nick do jogador "C_WHITE"que deseja enviar um e-mail:",
						""C_WHITE"Confirmar", "Retornar")
					;
	            }
	        }
	    }
	    return 1;
	}

	if (dialogid == 364) 
	{
		if (!response) 
			return 1;

		new emails = countPlayerEmails(PlayerName[playerid], EMAIL_ALL);
		new string[128];

		if (emails >= MAX_PLAYER_CAIXA_ENTRADA)
			return ShowPlayerDialog(playerid, 362, DIALOG_STYLE_MSGBOX, " ", ""C_GRAY"- A caixa de e-mails do jogador está cheia.", ""C_RED"Fechar", "");

		SetPVarString(playerid, "emailUser", inputtext);
		
		format(string, sizeof string, 
			""C_WHITE"Destinatário "C_YELLOW"%s\n\n\
			"C_WHITE"Mínimo de caracteres: 10\n\
			"C_WHITE"Máximo de caracteres: 148\n\n\
			Digite abaixo:", inputtext)
		;
		ShowPlayerDialog(playerid, 365, DIALOG_STYLE_INPUT, ""C_GRAY"Notebook: Enviar e-mail", string, ""C_GRAY"Confirmar", "Retornar");

	    return 1;
	}

	if (dialogid == 365)
	{
		new string[128];
		new gstring[128];

	    if (response) {
            SetPVarString(playerid, "emailMensagem", inputtext);
            GetPVarString(playerid, "emailUser", gstring, sizeof gstring);

            new string_mensagem[255];
            format(string_mensagem, sizeof string_mensagem, inputtext);

            MEGAString[0] = EOS;
            strcat(MEGAString, "* Quase terminando:\n\n");
            format(string, sizeof string, "{F5DEB3}* E-mail para:{FFFFFF} %s\n", gstring);
            strcat(MEGAString, string);

            if (strlen(string_mensagem) > 75) {

				new posSpace = strfind(string_mensagem, " ", true, 74);

                if (posSpace != -1) {

					strins(string_mensagem, "\n", posSpace);
                }
            }

            format(string, sizeof string, "{F5DEB3}* Mensagem:{FFFFFF} %s\n\n", string_mensagem);
            strcat(MEGAString, string);

			strcat(MEGAString, "{FF4444}OBS: {AAAAAA}Caso o jogador não esteja on-line, o mesmo poderá visualizar o e-mail quando entrar!");

	        ShowPlayerDialog(playerid, 366, DIALOG_STYLE_MSGBOX, " ", MEGAString, "Enviar", "Voltar");
	    } else {
	        ShowPlayerDialog(playerid, 364, DIALOG_STYLE_INPUT, " ", "* Digite o nick para quem você quer enviar o e-mail\n\
			\n{FF4444}OBS: {AAAAAA}O nick deve estar registrado no servidor, caso contrário você não poderá enviar o e-mail!", "Prosseguir", "Voltar");
	    }
	    return 1;
	}

	if (dialogid == 366) {

		new string[128];
		new gstring[128];
	    if (response) {

	        new string_mensagem[255];
	        GetPVarString(playerid, "emailUser", gstring, sizeof gstring);
            GetPVarString(playerid, "emailMensagem", string_mensagem, sizeof string_mensagem);

	        format(string, sizeof string, "* E-mail enviado com sucesso para %s, o mesmo poderá visualizá-lo a qualquer momento!", gstring);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

			// Enviar a mensagem
			SendPlayerEmail(PlayerName[playerid], gstring, string_mensagem);

	    } else {
	        GetPVarString(playerid, "emailUser", gstring, sizeof gstring);
	        format(string, sizeof string, "* Digite a mensagem que será enviada para %s abaixo:\n\n{FF4444}OBS: {AAAAAA}Evite escrever um texto muito grande ou usar acentos. O mesmo receberá o e-mail mesmo estando off-line!", gstring);
	        ShowPlayerDialog(playerid, 365, DIALOG_STYLE_INPUT, " ", string, "Prosseguir", "Voltar");
	    }

	    return 1;
	}

	if (dialogid == 362) {
	    DialogShow_EmailMain(playerid);
	    return 1;
	}

	if (dialogid == 367) {
		new string[128];
		new gstring[128];
		if (response) {

	        GetPVarString(playerid, "emailUser", gstring, sizeof gstring);
	        format(string, sizeof string, "* Digite a resposta que será enviada para %s abaixo:\n\n{FF4444}OBS: {AAAAAA}Evite escrever um texto muito grande ou usar acentos. O mesmo receberá o e-mail mesmo estando off-line!", gstring);
	        ShowPlayerDialog(playerid, 365, DIALOG_STYLE_INPUT, " ", string, "Prosseguir", "Voltar");
		} else {
	    	EMAIL_List(playerid, EMAIL_INBOX);
		}
	    return 1;
	}

	if (dialogid == 370) {

	    EMAIL_List(playerid, EMAIL_OUTBOX);
	    return 1;
	}

	if (dialogid == 361) {

	    if (response) {
	        SetPVarInt(playerid, "emailSelect", List_GetPlayers(playerid, listitem));
	        ShowPlayerDialog(playerid, 368, DIALOG_STYLE_LIST, "Escolha uma opção", "Visualizar e-mail\nDeletar e-mail", "Selecionar", "Fechar");

	    } else {
	        DialogShow_EmailMain(playerid);
	    }
	    return 1;
	}

	if (dialogid == 363) {

	    if (response) {
	        ShowEmailForPlayerEnviado(playerid, List_GetPlayers(playerid, listitem));
	    } else {
	        DialogShow_EmailMain(playerid);
	    }
	    return 1;
	}

	if (dialogid == 368) {

	    if (response) {

	        new index = GetPVarInt(playerid, "emailSelect");

	        switch (listitem) {

	            case 0: {
	                ShowEmailForPlayer(playerid, index);
	            }
	            case 1: {
	                DeletePlayerEmail(playerid, index);
	            }
	        }
	    }
	    return 1;
	}

	return 0;
}

// Retorna quantidade de e-mails (total/lidos/não lidos)
static countPlayerEmails(const nickname[], stateRead = EMAIL_ALL)
{
	new emails,
		query[99];

	switch (stateRead)
	{
		// E-mails não lidos;
		case EMAIL_NOTREAD: mysql_format(MySQL_Handle, query, sizeof(query), "SELECT COUNT(id) FROM `email` WHERE `para` = '%e' AND `lido` = '0'", nickname);

		// E-mails lidos;
		case EMAIL_READ: mysql_format(MySQL_Handle, query, sizeof(query), "SELECT COUNT(id) FROM `email` WHERE `para` = '%e' AND `lido` = '1'", nickname);

		// Todos os e-mails;
		default: mysql_format(MySQL_Handle, query, sizeof(query), "SELECT COUNT(id) FROM `email` WHERE `para` = '%e'", nickname);
	}
	new 
		Cache:mysql_cache = mysql_query(MySQL_Handle, query);
		
	cache_get_value_int(0, 0, emails);

	cache_delete(mysql_cache);

	return emails;
}

// Dialog principal do notebook;
static DialogShow_EmailMain(playerid)
{
	new emails = countPlayerEmails(PlayerName[playerid], EMAIL_ALL);
	new emails_notread = countPlayerEmails(PlayerName[playerid], EMAIL_NOTREAD);

	static string[144];

	format(string, sizeof (string),
		""C_WHITE"Caixa de entrada	"C_CYAN"%d\n\
		Caixa de saida	"C_GRAY"%d\n\
		Enviar e-mail\n", 
	emails, emails_notread);

	ShowPlayerDialog(playerid, 360, DIALOG_STYLE_TABLIST, "Notebook", string, "Selecionar", "Cancelar");
}

stock SendPlayerEmail(const remetente[], const nickname[], const message[]) 
{
	// Inserir na tabela
	MySQL_Bind(stmt_insertEmail, 0, remetente, true);
    MySQL_Bind(stmt_insertEmail, 1, nickname, true);
	MySQL_Bind(stmt_insertEmail, 2, message, true);

    MySQL_ExecuteThreaded(stmt_insertEmail);

	new idplayer = GetPlayerID(nickname);

	if (Player_Logado(idplayer)) {
		SendClientMessage(idplayer, COLOR_NOTIFICATION, ">> NOTIFICAÇÃO: Você acabou de receber um e-mail. (Verifique sua caixa de entrada, use: /email).");
		updateTextDrawEmails(idplayer, countPlayerEmails(PlayerName[idplayer]));
	}
}

static updateTextDrawEmails(playerid, count)
{
	if (count > 0) {
		TextDrawShowForPlayer(playerid, _email_alert_textdraw[5]);
		PlayerTextDrawShow(playerid, _email_alert_ptextd[playerid]);

		static s_string[4];
		PlayerTextDrawChangeString(s_string, playerid, "%d", _email_alert_ptextd[playerid], count);
	}
	else {
		TextDrawHideForPlayer(playerid, _email_alert_textdraw[5]);
		PlayerTextDrawHide(playerid, _email_alert_ptextd[playerid]);
	}
}

CALLBACK: EMAIL_List(playerid, list) {

    inline const OnEmailListLoad() 
	{
        new
			id_email,
            player_name[MAX_PLAYER_NAME+1],
			mensagem[148],
			lido,
			data[20],
			Timestamp:timestamp;

		MySQL_BindResultInt(stmt_loadEmails, 0, id_email);
        MySQL_BindResult(stmt_loadEmails, 1, player_name, sizeof(player_name));
		MySQL_BindResult(stmt_loadEmails, 2, mensagem, sizeof(mensagem));
		MySQL_BindResultInt(stmt_loadEmails, 3, lido);
		MySQL_BindResult(stmt_loadEmails, 4, data, sizeof(data));

		MEGAString[0] = EOS;
		strcat(MEGAString, "Remetente\tMensagem\tData\n");

		new email = 0;

		if (MySQL_Statement_RowsLeft(stmt_loadEmails) == 0) {
			return SendClientMessage(playerid, COLOR_WARNING, "Pasta de e-mails vazia!");
		}

        while(MySQL_Statement_FetchRow(stmt_loadEmails)) {

			TimeParse(data, MYSQL_TIMESTAMP, timestamp);
			TimeFormat(timestamp, TIMESTAMP_FORMAT, data);

            FormatCat(MEGAString, "%s%02d. %s\t", lido ? (C_WHITE) : (C_GRAY), email + 1, player_name);
			
			if (strlen(mensagem) > MAX_PREV_MENSAGEM) {
				strdel(mensagem, MAX_PREV_MENSAGEM, sizeof(mensagem));
				strins(mensagem, "...", MAX_PREV_MENSAGEM);
			}
			FormatCat(MEGAString, "%s%s\t", lido ? (C_WHITE) : (C_GRAY), mensagem);
			SplitColor(mensagem);

			FormatCat(MEGAString, "%s%s\n", lido ? (C_WHITE) : (C_GRAY), data);
			
			List_SetPlayers(playerid, email, id_email);
			email++;
        } 
		ShowPlayerDialog(playerid, 361, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Notebook: Caixa de entrada", MEGAString, "Selecionar", "Voltar");
    }
    MySQL_Bind(stmt_loadEmails, 0, list == EMAIL_INBOX ? "para" : "de", true);
    MySQL_Bind(stmt_loadEmails, 1, PlayerName[playerid], true);
	MySQL_BindInt(stmt_loadEmails, 2, MAX_PLAYER_CAIXA_ENTRADA);
    MySQL_ExecuteParallel_Inline(stmt_loadEmails, using inline OnEmailListLoad);
	return 1;
}

static ShowEmailForPlayer(playerid, index)
{
	inline const OnSelectEmail() {
		new
			id,
			remetente[MAX_PLAYER_NAME],
			mensagem[148],
			data[20],
			Timestamp:timestamp,
			lido;

		MEGAString[0] = EOS;

		MySQL_BindResultInt(stmt_selectEmail, 0, id);
		MySQL_BindResult(stmt_selectEmail, 1, remetente, MAX_PLAYER_NAME);
        MySQL_BindResult(stmt_selectEmail, 2, mensagem, sizeof(mensagem));
		MySQL_BindResult(stmt_selectEmail, 3, data, sizeof(data));
		MySQL_BindResultInt(stmt_selectEmail, 4, lido);

		while(MySQL_Statement_FetchRow(stmt_selectEmail)) 
		{
			TimeParse(data, MYSQL_TIMESTAMP, timestamp);
			TimeFormat(timestamp, TIMESTAMP_FORMAT, data);

			strcat(MEGAString, "* E-mail que você recebeu:\n\n");
			FormatCat(MEGAString, "{F5DEB3}* Remetente: {FFFFFF}%s\n", remetente);
			FormatCat(MEGAString, "{F5DEB3}* Data do envio: {FFFFFF}%s\n", data);

			SetPVarString(playerid, "emailUser", remetente);

			if (strlen(mensagem) > 75) {
				new posSpace = strfind(mensagem, " ", true, 74);
				if (posSpace != -1) {
					strins(mensagem, "\n", posSpace);
				}
			}
			FormatCat(MEGAString, "{F5DEB3}* Mensagem: {FFFFFF}%s\n", mensagem);

			if(lido == 0) {
				MySQL_BindInt(stmt_updateEmail, 0, id);
				MySQL_ExecuteParallel(stmt_updateEmail);
			}
		}
		ShowPlayerDialog(playerid, 367, DIALOG_STYLE_MSGBOX, ""C_GRAY"Notebook: E-mail recebido", MEGAString, "Responder", "Voltar");
	}
	MySQL_BindInt(stmt_selectEmail, 0, index);
	MySQL_ExecuteParallel_Inline(stmt_selectEmail, using inline OnSelectEmail);
}

stock ShowEmailForPlayerEnviado(playerid, index)
{
	new Cache:serverCache;
	new query[255];
	mysql_format(MySQL_Handle, query, sizeof query, "SELECT * FROM `email` WHERE `id` = '%d'", index);
	serverCache = mysql_query(MySQL_Handle, query);

	new row_count;
    cache_get_row_count(row_count);

	if (row_count)
	{
	    MEGAString[0] = EOS;

	    new string[255];

        strcat(MEGAString, "* E-mail que você enviou:\n\n");
	    cache_get_value_name(0, "de", query);
	    format(string, sizeof string, "{F5DEB3}* Remetente: {FFFFFF}%s\n", query);
	    strcat(MEGAString, string);
	    
	    cache_get_value_name(0, "para", query);
	    format(string, sizeof string, "{F5DEB3}* destinatário: {FFFFFF}%s\n", query);
	    strcat(MEGAString, string);

	    cache_get_value_name(0, "data", query);
	    format(string, sizeof string, "{F5DEB3}* Data do envio: {FFFFFF}%s\n", query);
	    strcat(MEGAString, string);

	    cache_get_value_name(0, "mensagem", query);

        if (strlen(query) > 75) {

			new posSpace = strfind(query, " ", true, 74);

            if (posSpace != -1) {

				strins(query, "\n", posSpace);
            }
        }

	    format(string, sizeof string, "{F5DEB3}* Mensagem: {FFFFFF}%s\n", query);
	    strcat(MEGAString, string);

	    ShowPlayerDialog(playerid, 370, DIALOG_STYLE_MSGBOX, "E-mail que você enviou", MEGAString, "Voltar", "");

	} else {
	    ShowPlayerDialog(playerid, 362, DIALOG_STYLE_MSGBOX, " ", "\n\t{FF5500}NADA CONSTA NESSA MENSAGEM\n", "Voltar", "");
	}
	cache_delete(serverCache);
}

static DeletePlayerEmail(playerid, index) 
{
	MySQL_BindInt(stmt_deleteEmail, 0, index);
	MySQL_ExecuteThreaded(stmt_deleteEmail, "EMAIL_List", "dd", playerid, EMAIL_INBOX);

	SendClientMessage(playerid, COLOR_NOTIFICATION, ">> NOTIFICAÇÃO: E-mail deletado com sucesso!");
	updateTextDrawEmails(playerid, countPlayerEmails(PlayerName[playerid]));
}

CMD:email(playerid) 
{
    if (!IsPlayerHaveItem(playerid, ITEM_TYPE_NOTEBOOK))
		return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não tem um Notebook.");

	DialogShow_EmailMain(playerid);

	return 1;
}

CMD:aemail(playerid, result[])
{
	if (Admin_GetNivel(playerid) < MASTER) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (isnull(result)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /aemail (texto) "C_GRAY"Enviar um e-mail á todos jogadores onlines.");

	if (strlen(result) > 148)
		return SendClientMessage(playerid, COLOR_WHITE, "Você não pode enviar um e-mail com mais de 148 caracteres.");

	new players;
	new mensagem[148];

	format(mensagem, sizeof mensagem, "%s. Atenciosamente, %s", result, PlayerName[playerid]);

	foreach(new id : Player) {
		if (!Player_Logado(id)) 
			continue;

		SendPlayerEmail(SERVER_NAME, PlayerName[id], mensagem);

		players++;
	}
	SendMsgF(playerid, COLOR_LIGHTBLUE, "Você enviou um e-mail para %d jogadores conectados.", players);

	return 1;
}





