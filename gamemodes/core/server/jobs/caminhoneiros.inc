//------------------------- (Sistema de caminhoneiros) -------------------------
enum CaminhaoEnum
{
    bool: caminhaoVALID,
    bool: carretaVALID,
}
new VehicleCaminhao[MAX_VEHICLES][CaminhaoEnum];

stock IsTruckCarJob(vehicleid) {
	return VehicleCaminhao[vehicleid][caminhaoVALID];
}

stock IsTruckTrailerCarJob(vehicleid) {
	return VehicleCaminhao[vehicleid][carretaVALID];
}


new const Float:CaminhaoSpawn[12][4] =
{
	{1426.4534, 1085.8065, 11.1474, 90.0000},
	{1426.4534, 1081.5441, 11.1474, 90.0000},
	{1426.4534, 1077.2834, 11.1474, 90.0000},
	{1426.4534, 1072.8574, 11.1474, 90.0000},
	{1426.4534, 1062.4734, 11.1474, 90.0000},
	{1426.4534, 1058.3920, 11.1474, 90.0000},
	{1426.4534, 1054.2527, 11.1474, 90.0000},
	{1426.4534, 1050.2682, 11.1474, 90.0000},
	{1426.4534, 1045.9110, 11.1474, 90.0000},
	{1426.4534, 1025.2620, 11.1474, 90.0000},
	{1426.4534, 1020.6422, 11.1474, 90.0000},
	{1426.4534, 1016.2432, 11.1474, 90.0000}
};
new const CaminhaoModel[] = {440, 414, 456, 455, 578};
new const CaminhaoMax[] = {130, 140, 160, 180, 220};
new const CaminhaoPreco[] = {70, 80, 100, 120, 200};
new CaminhoesAtivos = 0;

new Timer:cancel_caminhao_timer[MAX_PLAYERS];
new percent_cancel_caminhao[MAX_PLAYERS] = 200;

stock DestroyPlayerCaminhao(playerid)
{
    if (!PlayerCaminhao[playerid][caminhaoValid]) return false; // Verifica se o jogador está em um caminhão (veículo de trabalho).

    PlayerCaminhao[playerid][caminhaoCarga] = 0; // Perde a carga do caminhão

    VehicleCaminhao[PlayerCaminhao[playerid][caminhaoId]][caminhaoVALID] = false;

    DisableRemoteVehicleCollisions(playerid, false); // Habilita as colisões com veículos para o player.

    CaminhoesAtivos--; // Controle e limitação do aluguel de caminhões.

    PlayerCaminhao[playerid][caminhaoValid] = false; // Remove o jogador do caminhão (veículo de inventário).

	percent_cancel_caminhao[playerid] = 200;

    DestroyVehicle(PlayerCaminhao[playerid][caminhaoId]); // Destruir o caminhão (veículo de trabalho).

    return true;
}

stock CaminhaoCancelForPlayer(playerid)
{
	HidePlayerSearch(playerid);
	stop cancel_caminhao_timer[playerid];
}

timer Timer_cancel_caminhao[1000](playerid)
{
	static string[128];

	switch (percent_cancel_caminhao[playerid])
	{
		case 200:
		{
			format(string, sizeof string, "Voce tem ~r~~h~%d segundos ~w~para voltar ao caminhao", percent_cancel_caminhao[playerid]);
			ShowPlayerMessage(playerid, string, 1000);

			cancel_caminhao_timer[playerid] = repeat Timer_cancel_caminhao(playerid);
		   	percent_cancel_caminhao[playerid]--;
		}
		case 0:
		{
	        DestroyPlayerCaminhao(playerid);

			CaminhaoCancelForPlayer(playerid);
		}
		default:
        {
			format(string, sizeof string, "Voce tem ~r~~h~%d segundos ~w~para voltar ao caminhao", percent_cancel_caminhao[playerid]);
			ShowPlayerMessage(playerid, string, 1000);

		   	percent_cancel_caminhao[playerid]--;
		}
	}
}

stock CancelPlayerCaminhao(playerid)
{
	percent_cancel_caminhao[playerid] = 200;

	cancel_caminhao_timer[playerid] = defer Timer_cancel_caminhao(playerid);
}