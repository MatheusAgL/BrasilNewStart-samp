CMD:propvdono(playerid, params[])
{
	if (!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Você não está logado.");
		
	if (Admin_GetNivel(playerid) < SUB_DONO)
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new string[128], idProp, namePlayer[MAX_PLAYER_NAME];
	if (sscanf(params, "ds[24]", idProp, namePlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /propvdono (id da propriedade) (nome do jogador)");

	new id = Player_GetAccountIDByNick(namePlayer);
	if (id == -1) 
		return SendClientMessage(playerid, -1, "Jogador inexistente.");

	PropInfo[idProp][eOwnerID] = id;
	format(PropInfo[idProp][eOwner], MAX_PLAYER_NAME, namePlayer);

	format(string, sizeof string, "AdmCmd: O %s, %s setou a propriedade %s ({00BFFF}%d{FFFFFF}) para {00FFFF}%s", Staff_GetPositionName(playerid), PlayerName[playerid], PropInfo[idProp][ePname], idProp, namePlayer);
	SendClientMessageToAll(-1, string);

	atualizarPropText(idProp);
	savePropertie(idProp);
	
	// Logs
	format(string, sizeof(string), "(Prop): %s setou a propriedade %d para o jogador %s", PlayerName[playerid], idProp, namePlayer);
	server_log("propriedades", string);

	return true;
}

CMD:propvencimento(playerid, params[])
{
	if (Admin_GetNivel(playerid) < DONO) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");
	
	new string[128], idProp, vencimento[MAX_PLAYER_NAME];
	if (sscanf(params, "ds[24]", idProp, vencimento)) return SendClientMessage(playerid, -1, "Modo de uso: /propvencimento (id da propriedade) (data YYYY-MM-DD)");

	TimeParse(vencimento, ISO6801_DATE, PropInfo[idProp][eVencimento]);

	format(string, sizeof string, "AdmCmd: O %s, %s setou o vencimento da propriedade %s ({00BFFF}%d{FFFFFF}) para {00FFFF}%s", Staff_GetPositionName(playerid), PlayerName[playerid], PropInfo[idProp][ePname], idProp, vencimento);
	SendClientMessageToAll(-1, string);

	atualizarPropText(idProp);
	savePropertie(idProp);
	
	// Logs
	format(string, sizeof(string), "(Prop): %s setou o vencimento da propriedade %d para %s", PlayerName[playerid], idProp, vencimento);
	server_log("propriedades", string);

	return true;
}

CMD:propvalue(playerid, params[])
{
	if (Admin_GetNivel(playerid) < DONO) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");
	
	new string[128], idProp, valueprop;
	if (sscanf(params, "dd", idProp, valueprop)) return SendClientMessage(playerid, -1, "Modo de uso: /propvalue (id da propriedade) (valor)");

    PropInfo[idProp][ePrice] = valueprop;

	format(string, sizeof string, "AdmCmd: O %s, %s setou a propriedade %s ({00BFFF}%d {FFFFFF})para {00AA00}$%s", Staff_GetPositionName(playerid), PlayerName[playerid], PropInfo[idProp][ePname], idProp, getFormatText(valueprop));
	SendClientMessageToAll(-1, string);

	atualizarPropText(idProp);
	savePropertie(idProp);
	
	// Logs
	format(string, sizeof(string), "(Prop): %s setou a propriedade %d para $%s", PlayerName[playerid], idProp, valueprop);
	server_log("propriedades", string);

	return true;
}

CMD:propcomprar(playerid, params[]) return callcmd::propriedade(playerid, "comprar");
CMD:propvender(playerid, params[]) return callcmd::propriedade(playerid, "vender");
CMD:proplocalizar(playerid, params[]) return callcmd::propriedade(playerid, "localizar");
CMD:propfechar(playerid, params[]) return callcmd::propriedade(playerid, "fechar");
CMD:propabrir(playerid, params[]) return callcmd::propriedade(playerid, "abrir");
CMD:propsacar(playerid, params[]) return callcmd::propriedade(playerid, "retirardinheiro");
CMD:propentrada(playerid, params[]) return callcmd::propriedade(playerid, "sacar");
CMD:propriedade(playerid, const params[])
{
	if (isnull(params))
	{
	    SendClientMessage(playerid, -1, "Modo de uso: /propriedade (nome | lista abaixo)");
	    SendClientMessage(playerid, -1, "Nomes disponíveis: Ajuda | Ajuda | Comprar | Vender | Sacar | Depositar | Localizar | Abrir");
		SendClientMessage(playerid, -1, "Nomes disponíveis: PrecoInsumo | PedirInsumos | PrecoInsumo");
		return true;
	}

	new
	    string[256],
		null[25],
		id,
		Float:x,
		Float:y,
		Float:z
	;

	if (lastPickup[playerid] != -1 || properties[lastPickup[playerid]][eType] > 0)
	{
	   	id = propPickups[lastPickup[playerid]];

		GetPropertyEntrance( id, x, y, z );
	}

	if (!strcmp(params, "ajuda", true)) {
	    SendClientMessage(playerid, -1, " ");
		SendClientMessage(playerid, -1, "Comandos que podem ser utilizados:");
		SendClientMessage(playerid, -1, "/propriedade ajuda | /propriedade comprar | /propriedade vender | /propriedade localizar");
        SendClientMessage(playerid, -1, "/propriedade abrir | /propriedade fechar | /propriedade retirardinheiro | /propriedade entrada");
	}

	else if(!strcmp(params, "info", true)) {
		if(!IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z))
			return SendClientMessage(playerid, -1, "Você não está próximo a nenhuma propriedade.");	

		new lucro = GetPropriedadeLucro(id);

		MEGAString[0] = EOS;

		strcat(MEGAString, "{00AA00}------- Informações da Propriedade -------{FFFFFF}\n");
		FormatCat(MEGAString, "Propriedade: %s [%d]\n\n", PropInfo[id][ePname], id);
		FormatCat(MEGAString, "Dono: %s\n", PropInfo[id][eOwner]);
		FormatCat(MEGAString, "Valor: $%s\n", getFormatText(PropInfo[id][ePrice]));
		FormatCat(MEGAString, "Cofre: $%s\n", getFormatText(PropInfo[id][eTill]));
		strcat(MEGAString, "\n{00AA00}------- Financeiro -------{FFFFFF}\n");
		FormatCat(MEGAString, "Lucro por minuto: $%s\n", getFormatText(lucro));
		FormatCat(MEGAString, "Lucro por hora: $%s\n", getFormatText(lucro * 60));
		FormatCat(MEGAString, "Lucro por dia: $%s\n", getFormatText(lucro * 60 * 24));
		FormatCat(MEGAString, "Lucro por semana: $%s\n", getFormatText(lucro * 60 * 24 * 7));

		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Propriedade", MEGAString, "OK","");
	}

	else if (!strcmp(params, "comprar", true))
	{
	 	if(IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z))
		{
			if (IsPropertyOwner(id)) return SendClientMessage( playerid, -1, "Esta propriedade já tem dono !" );

			if (Player_GetMoney(playerid) < PropInfo[id][ePrice] ) {
			    format(string, sizeof string, "Você não tem {00AA00}$%s{FFFFFF} para comprar!", getFormatText(PropInfo[id][ePrice]));
				return SendClientMessage( playerid, -1, string );
			}

			if (PlayerInfo[playerid][pVIP] < 6 && CountProperties(playerid) >= 2) 
				return SendClientMessage(playerid, -1, "Apenas jogadores SÓCIO-EXTREME podem ter mais de duas empresas.");
			else if (PlayerInfo[playerid][pVIP] <= SOCIO_EXTREME && CountProperties(playerid) >= 3) 
				return SendClientMessage(playerid, -1, "Você já atingiu o limite máximo de propriedades.");
			else if (PlayerInfo[playerid][pVIP] == 0 && CountProperties(playerid) > 1) {
			    return SendClientMessage( playerid, -1, "Você pode ter no máximo {00AA00}1{FFFFFF} propriedade." );
			}
			Player_RemoveMoney(playerid, PropInfo[id][ePrice]);
            SetPropertyOwner(id, playerid);
	   		PutPlayerInProperty( playerid, id );

	   		format(string, sizeof string, "Você comprou a propriedade {00FFFF}%s {FFFFFF}por {00AA00}$%s{FFFFFF}, use /propriedade ajuda!", PropInfo[id][ePname], getFormatText(PropInfo[id][ePrice]));
	 	   	SendClientMessage( playerid, -1, string);
			format(string, sizeof string, "Caso você queira vende-la novamente, ela valerá {FF0000}$%s{FFFFFF}!", getFormatText(PropInfo[id][ePrice]/2));
	 	   	SendClientMessage( playerid, -1, string);
	 	   	SendClientMessage( playerid, -1, "Pague corretamente as despesas da propriedade, caso contrario ela será {FF0000}vendida{FFFFFF}!");
	 	   	format(string, sizeof string, "~b~~h~~h~%s~n~~g~comprada, Parabens!", PropInfo[id][ePname]);
	 	   	GameTextForPlayer(playerid, string, 5000, 3);

			PropInfo[id][eVencimento] = Now() + Days:7;

            atualizarPropText( id );
            savePropertie( id );
            // Logs
			format(string, sizeof(string), "%s comprou a propriedade %d", PlayerName[playerid], id);
			server_log("propriedades", string);
	  	   	return 1;
		}
		return SendClientMessage(playerid, -1, "Você não está perto de nenhuma propriedade !");
	}

	else if ( !strcmp(params, "vender", true) ) {

	 	if( IsPlayerInRangeOfPoint( playerid, 3.0, x, y, z )){

			if (!IsPlayerOwnerPropertie(playerid, id ) && Admin_GetNivel(playerid) < DONO) {
				return SendClientMessage( playerid, -1, "Você não é dono dessa propriedade !" );
			}

			if ( !IsPropertyOwner( id ) ) {
				return SendClientMessage( playerid, -1, "Esta propriedade não tem dono !" );
			}

			format(string, sizeof string, "Você vendeu a propriedade {00FFFF}%s {FFFFFF}por {00AA00}$%s{FFFFFF}!", PropInfo[id][ePname], getFormatText(PropInfo[id][ePrice]/2));
 			SendClientMessage( playerid, -1, string);
			Player_AddMoney(playerid, (PropInfo[id][ePrice] / 2));

            SetPropertyOwner(id, -1);

	 	   	atualizarPropText( id );
	 	   	savePropertie( id );
            // Logs
			format(string, sizeof(string), "%s vendeu a propriedade %d", PlayerName[playerid], id );
			server_log("propriedades", string);
	  	   	return 1;
		}
		return SendClientMessage(playerid, -1, "Você não está perto de nenhuma propriedade !");
	}
	else if ( !strcmp(params, "abrir", true) ) {

	 	if( IsPlayerInRangeOfPoint( playerid, 3.0, x, y, z )){

			if (!IsPlayerOwnerPropertie(playerid, id ) && Admin_GetNivel(playerid) < DONO) {
				return SendClientMessage( playerid, -1, "Você não é dono dessa propriedade !" );
			}
			if ( !PropInfo[id][eLock] ) {
				return SendClientMessage( playerid, -1, "A porta dessa propriedade já está aberta !" );
			}

			PropInfo[id][eLock] = 0;

			format(string, sizeof string, "Você abriu as portas da propriedade {00FFFF}%s{FFFFFF}!", PropInfo[id][ePname]);
	 	   	SendClientMessage( playerid, -1, string);
	 	   	savePropertie( id );
	  	   	return 1;
		}
		return SendClientMessage(playerid, -1, "Você não está perto de nenhuma propriedade !");
	}
	else if ( !strcmp(params, "fechar", true) ) {

	 	if( IsPlayerInRangeOfPoint( playerid, 3.0, x, y, z )){

			if (!IsPlayerOwnerPropertie(playerid, id ) && Admin_GetNivel(playerid) < MASTER) {
				return SendClientMessage( playerid, -1, "Você não é dono dessa propriedade !" );
			}
			if ( PropInfo[id][eLock] ) {
				return SendClientMessage( playerid, -1, "A porta dessa propriedade já está fechada !" );
			}

			PropInfo[id][eLock] = 1;

			format(string, sizeof string, "Você fechou as portas da propriedade {00FFFF}%s{FFFFFF}!", PropInfo[id][ePname]);
	 	   	SendClientMessage( playerid, -1, string);
	 	   	savePropertie( id );
	  	   	return 1;
		}
		return SendClientMessage(playerid, -1, "Você não está perto de nenhuma propriedade !");
	}
	else if (strfind(params, "sacar", true) != -1) {

		new propid = GetPlayerCofreProp( playerid ), quant;

		if (propid == -1) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está no cofre de uma propriedade sua !");
		}

		if (!IsPlayerOwnerPropertie(playerid, propid ) ) {
			return SendClientMessage( playerid, -1, "Você não é dono dessa propriedade !" );
		}

		if (sscanf(params, "s[25]d", null, quant))
		{
			format(string, sizeof(string), "  Você tem $%s no cofre da propriedade.", getFormatText(PropInfo[propid][eTill]));
			SendClientMessage(playerid, COLOR_GRAD, string);
			SendClientMessage(playerid, -1, "Use: /propriedade sacar [quantidade]");
			return 1;
		}

		if(quant > PropInfo[propid][eTill] || quant < 1) {
			return SendClientMessage( playerid, -1, "A propriedade está sem dinheiro para retirar !" );
		}

		Player_AddMoney(playerid, quant);

		format(string, sizeof(string), "Você retirou {00AA00}$%s {FFFFFF}da propriedade {00FFFF}%s{FFFFFF}!", getFormatText(quant), PropInfo[id][ePname]);
	   	SendClientMessage( playerid, -1, string);

	   	PropInfo[propid][eTill] -= quant;
	   	atualizarPropText(propid);
	   	savePropertie(propid);
	}
	else if (strfind(params, "depositar", true) != -1) {

		new propid = GetPlayerCofreProp( playerid ), quant;

		if (propid == -1) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está no cofre de uma propriedade sua !");
		}

		if (!IsPlayerOwnerPropertie(playerid, propid ) ) {
			return SendClientMessage( playerid, -1, "Você não é dono dessa propriedade !" );
		}

		if (sscanf(params, "s[25]d", null, quant))
		{
			format(string, sizeof(string), "  Você tem $%s no cofre da propriedade.", getFormatText(PropInfo[propid][eTill]));
			SendClientMessage(playerid, COLOR_GRAD, string);
			SendClientMessage(playerid, -1, "Use: /propriedade depositar [quantidade]");
			return 1;
		}

		if(quant > Player_GetMoney(playerid) || quant < 1) {
			return SendClientMessage( playerid, -1, "Você não possui essa quantia para depositar !" );
		}

		Player_RemoveMoney(playerid, quant);

		format(string, sizeof(string), "Você depositou {00AA00}$%s {FFFFFF}da propriedade {00FFFF}%s{FFFFFF}!", getFormatText(quant), PropInfo[id][ePname]);
	   	SendClientMessage( playerid, -1, string);

	   	PropInfo[propid][eTill] += quant;

	   	atualizarPropText(propid);
	   	savePropertie(propid);
	}

	else if ( !strcmp(params, "localizar", true)) {
	    listPropriedades(playerid, 1);
	    SetPVarInt(playerid, "varTipoGps", 0);
	}

	else if (strfind(params, "precoinsumo", true) != -1)
	{
		if( IsPlayerInRangeOfPoint( playerid, 3.0, x, y, z )){

			if (!IsPlayerOwnerPropertie(playerid, id ) && Admin_GetNivel(playerid) < MASTER) {
				return SendClientMessage( playerid, -1, "Você não é dono dessa propriedade !" );
			}

			new amount;
			if (sscanf(params, "s[25]d", null, amount)) return SendClientMessage(playerid, -1, "Modo de uso: /propriedade precoproduto (preco)");

			if (amount < 10 || amount > 400)
				return SendClientMessage(playerid, -1, "A quantia mínima é $10, a quantia máxima é $400.");

			PropInfo[id][ePrecoInsumo] = amount;

			format(string, sizeof(string), "PROPRIEDADE: Você alterou o preço de compra dos insumos para $%s.", getFormatText(PropInfo[id][ePrecoInsumo]));
			SendClientMessage(playerid, -1, string);

			format(string, sizeof(string), "{00FFFF}%s [%d] {FFFFFF}alterou o preço de compra dos insumos para {00AA00}$%s/insumo", PropInfo[id][ePname], 
				id, getFormatText(PropInfo[id][ePrecoInsumo]));
			SendClientMessageToAll(-1, string);

			savePropertie(id);
			atualizarPropText(id);
		}
	}

	else if (strfind(params, "pedirinsumos", true) != -1)
	{
		if( IsPlayerInRangeOfPoint( playerid, 3.0, x, y, z )){

			if (!IsPlayerOwnerPropertie(playerid, id ) && Admin_GetNivel(playerid) < MASTER) {
				return SendClientMessage( playerid, -1, "Você não é dono dessa propriedade !" );
			}

			new amount;
			if (sscanf(params, "s[25]d", null, amount)) return SendClientMessage(playerid, -1, "Modo de uso: /propriedade pedirinsumos (preco)");
			if (amount < 0 || amount > 20000) return SendClientMessage(playerid, -1, "A quantia mínima é 1, a quantia máxima é 20.000.");
			if (PropInfo[id][eInsumos] > 20000) return SendClientMessage(playerid, -1, "A propriedade já está com 20.000 insumos ou mais, espere abaixar para pedir.");

			PropInfo[id][eInsumosReq] = amount;
			format(string, sizeof(string), "PROPRIEDADE: Você anunciou a solicitação de %d produtos.", PropInfo[id][eInsumosReq]);
			SendClientMessage(playerid, -1, string);

			format(string, sizeof(string), "{00FFFF}%s [%d] {FFFFFF}está precisando de {00FFFF}%d insumos {FFFFFF}pelo preço de {00AA00}$%s por produto", PropInfo[id][ePname], 
				id, PropInfo[id][eInsumosReq], getFormatText(PropInfo[id][ePrecoInsumo]));
			SendClientMessageToAll(-1, string);
			
			savePropertie(id);
			atualizarPropText(id);
		}
	}
	else {
	    SendClientMessage(playerid, -1, "Nomes: Ajuda | Ajuda | Comprar | Vender | Sacar | Localizar | Abrir | PrecoInsumo | PedirInsumos | PrecoInsumo");
	}

	return 1;
}

CMD:irprop(playerid, params[]) {

	if (Admin_GetNivel(playerid) < SUPERVISOR) {
	    return SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando!");
	}

	if (isnull(params)) {
	    return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /irprop [id]");
	}
	new id = strval(params);

	if (id < 0 || id >= unid) {
	    return SendClientMessage(playerid, -1, "Esta propriedade não existe!");
	}
	new Float:x, Float:y, Float:z;

	GetPropertyEntrance( id, x, y, z);
	SetPlayerPos(playerid, x, y, z);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);

	new string[95];
	format(string, sizeof string, "Você foi até a propriedade {00FFFF}%s{FFFFFF}!", PropInfo[id][ePname]);
  	SendClientMessage( playerid, -1, string);
	return 1;
}