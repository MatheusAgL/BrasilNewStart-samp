static IsPlayerInLoterica(playerid) {

	if (IsPlayerInRangeOfPoint(playerid, 2.0, 822.0084,6.3861,1004.1797) ||
	    IsPlayerInRangeOfPoint(playerid, 2.0, 822.0084,4.1540,1004.1797) ||
	    IsPlayerInRangeOfPoint(playerid, 2.0, 822.0085,1.8853,1004.1797) ||
	    IsPlayerInRangeOfPoint(playerid, 2.0, 822.0086,-0.3084,1004.1797)) {
	    return true;
	}
	return false;
}

CMD:loteria(playerid) 
	return SendClientMessage(playerid, -1, "Voc� precisa ir at� uma Lot�rica, use: /gps � Com�rcios.");
	
CMD:loterica(playerid)
{
    if (!IsPlayerInLoterica(playerid)) return SendClientMessage(playerid, -1, "Voc� n�o est� na lot�rica, use /gps � Com�rcios.");

	MEGAString[0] = EOS;

	strcat(MEGAString, "Tipo\tFun��o\n");

	strcat(MEGAString, "{9C9C9C}Loteria\t{FFFFFF}Apostar\n");

	strcat(MEGAString, "{9C9C9C}Governo\t{FFFFFF}Bolsa fam�lia\n");

	strcat(MEGAString, "{9C9C9C}Loterica\t{FFFFFF}Pagar minhas contas\n");

	ShowPlayerDialog(playerid, 103, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Menu � {00BFFF}Lot�rica", MEGAString, "Prosseguir", "Cancelar");

    return 1;
}