#include < YSI_Coding\y_hooks >

new atendimentoPolicial[MAX_PLAYERS];

enum ocorrenciaEnum {

	bool:ocorrenciaValid,
	ocorrenciaID,
	ocorrenciaTempo,
	ocorrenciaAssunto[128],
}
new OcorrenciaInfo[MAX_PLAYERS][ocorrenciaEnum];

static OpenOcorrencia(playerid, assunto[])
{
	new string[143];

	OcorrenciaInfo[playerid][ocorrenciaValid] 	= true;
	OcorrenciaInfo[playerid][ocorrenciaID] 		= INVALID_PLAYER_ID;
	OcorrenciaInfo[playerid][ocorrenciaTempo] 	= gettime();
	format(OcorrenciaInfo[playerid][ocorrenciaAssunto], 128, assunto);

	format(string, sizeof (string), "<< COPOM >> %s est� solicitando um policial, use: /ocorrencia %d | ocorr�ncia: %s", PlayerName[playerid], playerid, assunto);
	SendCopMessage(COLOR_LIGHTRED, string), SendMembersMessage(7, COLOR_LIGHTRED, string);
}

static listOcorrencias(playerid)
{
	new players;
	new string[128];

	MEGAString [0] = EOS;
	strcat(MEGAString, "Id  Nome\tTempo esperando\tAssunto\n");
	foreach(new x : Player) {

	    if (OcorrenciaInfo[x][ocorrenciaValid] && OcorrenciaInfo[x][ocorrenciaID] == INVALID_PLAYER_ID)
		{
	       	format(string, sizeof (string), "{FFFFFF}%02d  %s\t%s\t{00FFFF}%s\n", x, PlayerName[x], ConvertTime(gettime()-OcorrenciaInfo[x][ocorrenciaTempo]), OcorrenciaInfo[x][ocorrenciaAssunto]);
			strcat(MEGAString, string);

			List_SetPlayers(playerid, players, x);
			players ++;
	    }
	}

	format(string, sizeof (string), "Ocorr�ncias em aberto ({FF0000}%d{FFFFFF})", players);
	ShowPlayerDialog(playerid, 1961, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Atender", "Fechar");
}

CMD:ocorrencia(playerid, params[])
{
	if (!IsACop(playerid) && OnDuty[playerid] != 1) return SendClientMessage(playerid, -1, "Voc� n�o � um policial ou n�o bateu o cart�o.");

	new id;
	if (sscanf(params, "u", id))
	{
	    listOcorrencias(playerid);
	    return SendClientMessage(playerid, -1, "Modo de uso: /ocorrencia (id do jogador)");
	}

	if (!OcorrenciaInfo[id][ocorrenciaValid]) return SendClientMessage(playerid, -1, "Este jogador n�o fez uma chamada policial.");

	if (OcorrenciaInfo[id][ocorrenciaID] != INVALID_PLAYER_ID) return SendClientMessage(playerid, -1, "Este jogador j� foi atendido por outro policial.");

	if (id == playerid) return SendClientMessage(playerid, -1, "Voc� n�o pode atender a si mesmo.");

	AtenderOcorrencia(playerid, id);

	return true;
}

static AtenderOcorrencia(policialid, playerid)
{
    new string[145];

	if (!OcorrenciaInfo[playerid][ocorrenciaValid]) return false;

	format(string, sizeof(string), "Atendente 190(505) diz: O policial %s da %s, atendeu sua ocorr�ncia.", PlayerName[policialid], GetPlayerOrg(policialid));
	SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

	format(string, sizeof (string), "<< COPOM >> %s, %s da %s, atendeu a ocorr�ncia %d de: %s.", GetPlayerCargo(policialid), PlayerName[policialid], NomeORG(policialid), playerid, PlayerName[playerid]);
	SendCopMessage(COLOR_LIGHTRED, string), SendMembersMessage(7, COLOR_LIGHTRED, string);

	// A v�tima
    OcorrenciaInfo[playerid][ocorrenciaValid]	= true;
	OcorrenciaInfo[playerid][ocorrenciaID]		= policialid;
	OcorrenciaInfo[playerid][ocorrenciaTempo]	= gettime();

	// O policial
    OcorrenciaInfo[policialid][ocorrenciaValid]	= true;
	OcorrenciaInfo[policialid][ocorrenciaID]	= playerid;
	OcorrenciaInfo[policialid][ocorrenciaTempo]	= gettime();

	return true;
}

hook OnPlayerText(playerid, text[]) 
{
	if (atendimentoPolicial[playerid])
	{
		new string[128];
		
		if (strlen(text) < 10 || strlen(text) > 30)
		{
			format(string, sizeof(string), "Atendente 190(505) diz: %s, abrevie o assunto entre 10 a 30 caracteres.", PlayerName[playerid]);
			return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
		}
		OpenOcorrencia(playerid, text), atendimentoPolicial[playerid] = false;

		format(string, sizeof(string), "Atendente 190(505) diz: %s, enviamos o ocorrido, aguarde uma resposta.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5), false;
	}
	return 1;
}

CMD:servico(playerid, const params[])
{
    if (gettime() < GetPVarInt(playerid, #VarFloodServico)) return SendClientMessage(playerid, -1, "Aguarde um minuto para solicitar novamente.");

    if (isnull(params))
	{
	    SendClientMessage(playerid, -1, "Modo de uso: /servico (nome)");
	    SendClientMessage(playerid, COLOR_GRAD, "NOMES: policia, taxi, mecanico");
 		SendClientMessage(playerid, COLOR_GRAD, "_________________________________________________");
		return true;
	}

	new string[128];

	if (!strcmp(params, "policia", true)) {
		if (atendimentoPolicial[playerid])
			return SendClientMessage(playerid, -1, "Voc� j� abriu uma ocorr�ncia, aguarde atenderem seu chamado.");

		atendimentoPolicial[playerid] = true;

		format(string, sizeof(string), "Atendente 190(505) diz: %s, digite o assunto da ocorr�ncia.", PlayerName[playerid]);
		SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}
	else if (!strcmp(params, "taxi", true))
	{
		ServicoTaxi(playerid);
	}
	else if (!strcmp(params, "mecanico", true))
	{
		ServicoMecanico(playerid);
	}
	else
	{
		SendClientMessage(playerid, -1, "Modo de uso: /servico (nome)");
	    SendClientMessage(playerid, COLOR_GRAD, "NOMES: policia | taxi | mercenario | mecanico");
 		SendClientMessage(playerid, COLOR_GRAD, "_________________________________________________");
	}
	return true;
}