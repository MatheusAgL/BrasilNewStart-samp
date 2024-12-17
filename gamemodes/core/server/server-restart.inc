// -------------------------------
// GMX

timer TimerGMX[5 * 1000]()
	GameModeExit();

stock GMX(const player[], const motivo[])
{
	// Mensagem enviada a todos os jogadores
	SendClientMessageToAll(COLOR_SAMP, "Servidor reiniciando...");
	SendClientMessageToAll(COLOR_SAMP, "Dentro de alguns instantes estaremos online novamente, saia e entre no jogo.");

	SetSVarInt("Restarting", 1);

	new string[MAX_PLAYER_NAME+64];
	format(string, sizeof(string), "%s reiniciou o servidor pelo motivo: %s", player, motivo);
	server_log("gmx", string);

	// Desligando a GameMode
	foreach (new i : Player)
	{
		// Salvar posição correta
		saveLastPlayerPos(i);

		// Abre a dialog de informações do GMX
		ShowDialog_GMX(i, player, motivo);
	}
	// Alguns segundos para executar a GMX.
	defer TimerGMX();
}

stock ShowDialog_GMX(playerid, const player[], const motivo[])
{
	new string[128];

	MEGAString[0] = EOS;

	strcat(MEGAString, 
	"{7D8084}Servidor sendo reiniciado...\n\
	Aguarde alguns minutinhos e entre no servidor novamente!\n\n");

	format(string, sizeof(string), "{FFFFFF}Responsável: {00FF00}%s\n", player);
	strcat(MEGAString, string);
	format(string, sizeof(string), "{FFFFFF}Data: {7D8084}%s\n", GetCurrentDateHour(ONLY_CURRENT_ALL));
	strcat(MEGAString, string);
	format(string, sizeof(string), "{FFFFFF}Motivo: {7D8084}%s\n", motivo);
	strcat(MEGAString, string);

	strcat(MEGAString, "\n{FF0000}OBS: {FFFFFF}Use /ajuda para saber todas informações do servidor!\n");

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{00AA00}Reiniciando...", MEGAString, "Fechar", "");
}