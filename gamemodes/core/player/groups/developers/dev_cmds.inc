CMD:devcmds(playerid)
{
	if (Dev_GetNivel(playerid) < DEV_BETA)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	MEGAString[0] = EOS;

	// if (Dev_GetNivel(playerid) >= DEV_BETA)
	// {

	// 	/* ---------------------------------------------------------------------------
	// 		BETA:
	// 	- /-		(-)

	// 	*/
    // }

    if (Dev_GetNivel(playerid) >= DEV_ALPHA)
	{
        /* ---------------------------------------------------------------------------
			ALPHA:
		- /lixeira		(Gerenciamento das lixeiras do servidor)
        
		*/

        strcat(MEGAString, "\n"C_YELLOW"2. ALPHA\n");

		strcat(MEGAString,""C_WHITE"/lixeira /infocaixatx1 /derrubarcaixatx1\n");

    }

    if (Dev_GetNivel(playerid) >= DEV_DELTA)
	{
        /* ---------------------------------------------------------------------------
			DELTA:
		- /-		(-)
        
		*/

        strcat(MEGAString, "\n"C_YELLOW"4. DELTA\n");

        strcat(MEGAString,""C_WHITE"/casa carregar /casa dono /casa vencimento /trazerprop /portao dono\n");
        strcat(MEGAString,""C_WHITE"/abrirx1 /startx1 /starthideeggs /startrainpd /startquiz /startcbug /criarcupom\n");
		strcat(MEGAString,""C_WHITE"/criaritem /musicalogin /logchat /alterarmodo /testeanim /updateskate /distribuircontratos /atualizarorgs\n");
		strcat(MEGAString,""C_WHITE"/atualizarranks /resetarranks /resetativo /rcaixasequipamento /atualizarloja /setgravidade /avdev\n");
	}

    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, ""C_GRAY"Comandos administrativos", MEGAString, ""C_YELLOW"Fechar","");

	return 1;
}

// View rcon
CMD:viewrcon(playerid) 
{
	if (Dev_GetNivel(playerid) < DEV_DELTA)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	SendMsgF(playerid, -1, "Senha RCON: "C_CYAN"%s", Rcon_GetPassword());

	return 1;
}

CMD:cobjectmap(playerid, params[])
{
    if (Admin_GetNivel(playerid) < DONO) 
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    new modelid, 
        quantidade;

    if (sscanf(params, "dd", modelid, quantidade)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /criaritem (model) (quantidade)");

    new string[128];
    format(string, sizeof(string), "AdmAviso: %s criou objeto mapa INE (model: %d, qtd: %d).", PlayerName[playerid], modelid, quantidade);
    Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
    
    format(string, sizeof(string), "[/cobjectmap] %s criou (type: %d, model %d, quantidade %d, cor1: %d, cor 2: %d, nome: %s)", PlayerName[playerid], modelid, quantidade);
    server_log("dev", string);

    format(string, sizeof(string), "Object Map %d INE", modelid);
    givePlayerItem(playerid, 38, modelid, quantidade, string, 0, 0);
    return 1;
}

CMD:darsocio(playerid, params[])
{
    if (Admin_GetNivel(playerid) < DONO) 
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

    new idplayer, vip_nivel, dias;
    if (sscanf(params, "ddd", idplayer, vip_nivel, dias)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /darsocio (id do jogador) (nível de socio) (dias)");

    if (vip_nivel < 1 || vip_nivel > 8 || vip_nivel == 3 || vip_nivel == 4 || vip_nivel == 5 || vip_nivel == 6)
        return SendClientMessage(playerid, -1, "Escolha o VIP nível (1 comum, 2 premium, 7 supreme, 8 extreme)");

    if (dias < 1 || dias > 30)
        return SendClientMessage(playerid, -1, "Escolha os dias entre 1 á 30 dias.");

    GiveVipPresente(idplayer, vip_nivel, dias);

    new string[128];
    format(string, sizeof(string), "AdmAviso: %s deu %s por %d dias para %s.", PlayerName[playerid], VIP_GetName(vip_nivel), dias, PlayerName[idplayer]);
    Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);

    format(string, sizeof(string), "[/darsocio] %s deu %s para %s por %d dias.", PlayerName[playerid], VIP_GetName(vip_nivel), PlayerName[idplayer], dias);
    server_log("dev", string);

    return 1;
}

CMD:musicalogin(playerid, params[]) 
{
	if (Dev_GetNivel(playerid) < DEV_ALPHA) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

  	if (isnull(params)) 
		return SendClientMessage(playerid, -1, "Modo de uso: /musicalogin (URL da música)");

	new string[128];
	format(string, sizeof string, "AdmAviso: %s mudou a música de login do servidor para:", PlayerName[playerid]);
	Staff_ChatToAll(COLOR_LIGHTRED, string, MASTER);
	Staff_ChatToAll(COLOR_LIGHTRED, params, MASTER);
	server_log("admin", string);

	Login_SetMusic(params);

	return 1;
}

CMD:resetardia(playerid)
{
	if (Admin_GetNivel(playerid) < DONO) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new string[78];
	format(string, sizeof(string), "AdmAviso: %s resetou as estatísticas do dia manualmente.", PlayerName[playerid]);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
	
	CallLocalFunction("OnResetDay", "");
	return 1;
}

#if _inc_version_control
	CMD:atualizarversao(playerid)
	{
		if (Dev_GetNivel(playerid) < DEV_ALPHA) 
			return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

		new string[70];
		format(string, sizeof(string), "AdmAviso: %s atualizou a versão do servidor.", PlayerName[playerid]);
		Staff_ChatToAll(COLOR_LIGHTRED, string, SUB_DONO);
	
		VersionControl_LoadList();

		return 1;
	}
#endif

CMD:atualizarloja(playerid)
{
	if (Dev_GetNivel(playerid) < DEV_ALPHA) 
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new string[70];
	format(string, sizeof(string), "AdmAviso: %s atualizou a loja do servidor.", PlayerName[playerid]);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
	
	CarregarLojaCash();

	return 1;
}