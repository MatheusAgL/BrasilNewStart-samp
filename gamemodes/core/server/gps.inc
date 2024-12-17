CMD:gps(playerid)
{
    MEGAString [0] = EOS;

	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Locais Importantes\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Caixas Eletronicos\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Lixeiras\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}HQs das Organizações\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Concessionárias\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Locais de Empregos\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Casas\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Comércios\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {EC8510}Locais de tunagem\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Fazendas\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Pontos de Tráfico\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Traficantes\n");
	strcat(MEGAString, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Cativeiros\n");

	ShowPlayerDialog(playerid, 4902, DIALOG_STYLE_LIST, "{FFFFFF}» {00FFFF}GPS » {FFFFFF}Menu principal", MEGAString, "Selecionar", "Fechar");
	return true;
}