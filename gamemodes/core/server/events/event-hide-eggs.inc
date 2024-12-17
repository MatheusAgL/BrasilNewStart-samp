
/*  ----------------------------------------------------------------------------------------------------------------------------------------

        Sistema de eventos
                            v0.63
                            Theus_Crazzy (wearLyS)

 ----------------------------------------------------------------------------------------------------------------------------------------- */

#include <YSI_Coding\y_hooks>

// ---------------------------------------------------------------------------------
#if defined _INC_samp_random_event
	#if INC_samp_random_event_version < (5)
		#error Install version 5 or greater of the <samp-random-events> library
	#endif
#endif

#define HIDE_EGGS_EVENT	true
#define HIDE_EGGS_EVENT_ID 5
#define MAX_EGGS_HIDE 10
#define DIALOG_ID_HIDE_EGGS 93
#define COLOR_HIDE_EGGS_EVENT 0xFDB184AA

// ---------------------------------------------------------------------------------

enum hideeggsEnum
{
	object_eggs_hide,
    Float:pos_eggs_x,
    Float:pos_eggs_y,
    Float:pos_eggs_z,
}

new Float:HideEggs_Event[MAX_EGGS_HIDE][hideeggsEnum] = 
{
	{ 19342, 410.6921, -1265.5786, 54.4177 },
	{ 19341, 1037.5566, -1345.5715, 18.5141 },
	{ 19343, 1209.0708, -1282.8612, 63.5066 },
	{ 19344, 1476.8126, -1725.5530, 18.8831 },
	{ 19345, 1672.9397, -1774.9843, 3.9625 },
	{ 19342, 1866.6731, -1864.3054, 13.5749 },
	{ 19343, 1933.8683, -1764.5468, 19.5250 },
	{ 19345, 2104.1626, -1830.9325, 13.5552 },
	{ 19343, 2275.4055, -1696.3677, 13.6375 },
	{ 19342, 2290.5325, -1528.5808, 26.8750 }
};

new Eggs_Objects[MAX_EGGS_HIDE];
new Eggs_Valid[MAX_EGGS_HIDE];

stock SpreadEggsInMap() {
    for (new loop = 1; loop < sizeof(Eggs_Objects); loop++) {
        Eggs_Objects[loop] = CreateDynamicObject(HideEggs_Event[loop][object_eggs_hide], HideEggs_Event[loop][pos_eggs_x], HideEggs_Event[loop][pos_eggs_y], HideEggs_Event[loop][pos_eggs_z], 0.0, 0.0, 0.0);
    
		Eggs_Valid[loop] = true;
	}
}

stock DestroyEggsInMap() {
    for (new loop = 1; loop < sizeof(Eggs_Objects); loop++)
        DestroyObject(Eggs_Objects[loop]);
}

static GetPlayerNearEgg(playerid)
{
	new
		Float:px,
		Float:py,
		Float:pz
	;

	for (new loop = 1; loop < sizeof(Eggs_Objects); loop++) {
	    GetDynamicObjectPos(Eggs_Objects[loop], px, py, pz);

		if (IsPlayerInRangeOfPoint(playerid, 5.0, px, py, pz) && Eggs_Valid[loop]) 
			return loop;
	}
	return 0;
}

static FoundEggInMap(playerid) {

	new ovo_proximo = GetPlayerNearEgg(playerid);

	if (!ovo_proximo)
		return SendClientMessage(playerid, -1, "Você não está próximo de um ovo premiado.");

    if (EVENT[ev_started] && EVENT[ev_type] == HIDE_EGGS_EVENT_ID)
	{
		static string[40];

        EVENT[ev_score][playerid]++;
		EVENT[ev_bonus][playerid] += floatround(EVENT[ev_score][playerid], floatround_ceil) * 1000;

		PlayerTextDrawChangeString(string, playerid, "%s", event_ptextdraw[0][playerid], PlayerName[playerid]);
		PlayerTextDrawChangeString(string, playerid, "%d", event_ptextdraw[1][playerid], EVENT[ev_score][playerid]);

		EVENT_UpdateRanks();
	}
    DestroyObject(Eggs_Objects[ovo_proximo]);
	Eggs_Valid[ovo_proximo] = false;

	SendMsgAllF(EVENT[ev_color], "[EVENTO OVOS PREMIADOS]: {FFFFFF}%s encontrou um ovo premiado!", PlayerName[playerid]);
	
	ShowPlayerDialog(playerid, DIALOG_ID_HIDE_EGGS, DIALOG_STYLE_LIST, ""C_SAMP"Ovo premiado, encontrado!", "{FFFFFF}Pegar premio\nDoar premio", "Confirmar", "Cancelar");

	return 1;
}

static RandomAwardHideEgg(playerid) {
	new rdn = random(10);

	switch (rdn) {
		case 1: {
			SendMsgAllF(EVENT[ev_color], "[EVENTO OVOS PREMIADOS]: {FFFFFF}%s recebeu o prêmio %s"C_WHITE".", PlayerName[playerid], GiftBox_Give(playerid, ITEM_TYPE_CAIXAGIGANTE, false));
		}
		case 2: {
			SendMsgAllF(EVENT[ev_color], "[EVENTO OVOS PREMIADOS]: {FFFFFF}%s recebeu o prêmio %s"C_WHITE".", PlayerName[playerid], GiftBox_Give(playerid, ITEM_TYPE_CAIXAGOLD, false));
		}
		case 3: {
			SendMsgAllF(EVENT[ev_color], "[EVENTO OVOS PREMIADOS]: {FFFFFF}%s recebeu o prêmio %s"C_WHITE".", PlayerName[playerid], GiftBox_Give(playerid, ITEM_TYPE_SACOLA, false));
		}
		case 4: {
			SendMsgAllF(EVENT[ev_color], "[EVENTO OVOS PREMIADOS]: {FFFFFF}%s recebeu o prêmio %s"C_WHITE".", PlayerName[playerid], GiftBox_Give(playerid, ITEM_TYPE_CAIXAPLATINA, false));
		}
		case 5: {
			SendMsgAllF(EVENT[ev_color], "[EVENTO OVOS PREMIADOS]: {FFFFFF}%s recebeu o prêmio "C_LIGHTBLUE"Acessório: Cartola"C_WHITE".", PlayerName[playerid]);
			givePlayerItem(playerid, ITEM_TYPE_ACCESSORY, 19352, 1, "Acsr. Cartola");
		}
		case 6: {
			SendMsgAllF(EVENT[ev_color], "[EVENTO OVOS PREMIADOS]: {FFFFFF}%s recebeu o prêmio "C_LIGHTBLUE"1.000"C_WHITE" cash", PlayerName[playerid]);
			Player_SetCash(playerid, Player_GetCash(playerid) + 1000);
		}
		case 7: {
			SendMsgAllF(EVENT[ev_color], "[EVENTO OVOS PREMIADOS]: {FFFFFF}%s recebeu o prêmio {DC0139}Sócio Extreme "C_WHITE"por 1 dia.", PlayerName[playerid]);
			GiveVipPresente(playerid, SOCIO_EXTREME, 1);
		}
		default: {
			SendMsgAllF(EVENT[ev_color], "[EVENTO OVOS PREMIADOS]: {FFFFFF}%s recebeu o prêmio "C_MONEY"$50.000"C_WHITE".", PlayerName[playerid]);
			Player_RemoveMoney(playerid, 50000);
		}
	}
}

CMD:pegarpresente(playerid) {
	return FoundEggInMap(playerid);
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == DIALOG_ID_HIDE_EGGS) {

		if (!response) return 1;

		switch (listitem) {

			// Pegar o presente;
			case 0: {
				RandomAwardHideEgg(playerid);
			}

			// Doar o presente;
			case 1: {
				ShowPlayerDialog(playerid, DIALOG_ID_HIDE_EGGS + 1, DIALOG_STYLE_INPUT, ""C_SAMP"Doar ovo premiado!", "{FFFFFF}Digite o ID do jogador abaixo:", "Confirmar", "Cancelar");
			}
		}
	}
	else if (dialogid == DIALOG_ID_HIDE_EGGS + 1) {

		if (!response) {
			ShowPlayerDialog(playerid, DIALOG_ID_HIDE_EGGS, DIALOG_STYLE_LIST, ""C_SAMP"Ovo premiado, encontrado!", "{FFFFFF}Pegar premio\nDoar premio", "Prosseguir", "Cancelar");
		}

		new idplayer = strval(inputtext);

		if (playerid == idplayer) {
			ShowPlayerDialog(playerid, DIALOG_ID_HIDE_EGGS + 1, DIALOG_STYLE_INPUT, ""C_SAMP"Doar ovo premiado!", "{FFFFFF}Digite o ID do jogador abaixo:", "Confirmar", "Voltar");
			return SendClientMessage(playerid, -1, "Você não pode doar o prêmio para si mesmo.");
		}

		if (!Player_Logado(idplayer)) {
			ShowPlayerDialog(playerid, DIALOG_ID_HIDE_EGGS + 1, DIALOG_STYLE_INPUT, ""C_SAMP"Doar ovo premiado!", "{FFFFFF}Digite o ID do jogador abaixo:", "Confirmar", "Voltar");
			return SendClientMessage(playerid, -1, "Esse jogador não está conectado/logado no servidor.");
		} else {
			SendMsgAllF(EVENT[ev_color], "[EVENTO OVOS PREMIADOS]: {FFFFFF}%s doou seu ovo premiado para %s.", PlayerName[playerid], PlayerName[idplayer]);
			RandomAwardHideEgg(idplayer);
		}
	}
    return 1;
}