#if defined _inc_playerbody
	#endinput
#endif
#define _inc_playerbody true

#include <YSI_Coding\y_hooks>

#include <skins_attachments_fixed>			// Fixar os acessórios

#include <body_entry>						// Entrada do módulo
#include <body_death>						// Sistema de morte

// --------------------------------------
// Algemas

enum Bodypart {
	LEFT_HAND,
	RIGHT_HAND,
	LEFT_LEG,
	RIGHT_LEG,
};
new BodyPartBusy[MAX_PLAYERS][Bodypart];

stock Player_GetBusyHand(playerid, Bodypart: bodypart) {
	switch (bodypart) {
		case LEFT_HAND: return BodyPartBusy[playerid][LEFT_HAND];
		case RIGHT_HAND: return BodyPartBusy[playerid][RIGHT_HAND];
		case LEFT_LEG: return BodyPartBusy[playerid][LEFT_LEG];
		case RIGHT_LEG: return BodyPartBusy[playerid][RIGHT_LEG];
	}
	return -1;
}

stock Player_SetBusyHand(playerid, Bodypart: bodypart, bool:stats) {
	switch (bodypart) {
		case LEFT_HAND: BodyPartBusy[playerid][LEFT_HAND] = stats;
		case RIGHT_HAND: BodyPartBusy[playerid][RIGHT_HAND] = stats;
		case LEFT_LEG: BodyPartBusy[playerid][LEFT_LEG] = stats;
		case RIGHT_LEG: BodyPartBusy[playerid][RIGHT_LEG] = stats;
	}
	return -1;
}

stock Player_SetHandcuffed(playerid, bool:stats) {

	if (stats) {

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

		new skin = GetPlayerSkin(playerid);

		SetPlayerAttachedObject(playerid, Slot_Relogio, 19418, 6, CUFF_CuffObjectOffsets[skin][0], 
		CUFF_CuffObjectOffsets[skin][1], CUFF_CuffObjectOffsets[skin][2], CUFF_CuffObjectOffsets[skin][3], CUFF_CuffObjectOffsets[skin][4], 
		CUFF_CuffObjectOffsets[skin][5], CUFF_CuffObjectOffsets[skin][6], CUFF_CuffObjectOffsets[skin][7], CUFF_CuffObjectOffsets[skin][8]);

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CUFFED);
		SetPVarInt(playerid, "Cuffed", 1);
	} else {
		RemovePlayerAttachedObject(playerid, Slot_Relogio);
		SetPVarInt(playerid, "Cuffed", 0);

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	}
	Player_SetBusyHand(playerid, RIGHT_HAND, stats);
	Player_SetBusyHand(playerid, LEFT_HAND, stats);
}

stock IsPlayerCuffed(playerid)
	return GetPVarInt(playerid, "Cuffed") || GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED;

stock IsPlayerWithHandsUp(playerid) {
	return (
		GetPVarInt(playerid, "EmAbordagem") || 
		GetPlayerAnimationIndex(playerid) == 1169 || 
		GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_HANDSUP
	);
}

stock Player_GetHandcuffed(playerid) {
	return IsPlayerCuffed(playerid);
}

hook OnPlayerResetVars(playerid)
{
	static const 
		empty_var[Bodypart];
		
	BodyPartBusy[playerid] = empty_var;

	return 1;
}
// --------------------------------------
// Skate

UpdatePlayerSkate(playerid, keys)
{
	if (GetTickCount() < SkateInfo[playerid][s_Update]) return true;

	SkateInfo[playerid][s_Update] = (GetTickCount() + update_rate_skate);

	new Float:playerCam [3], Float:x, Float:y, Float:z[2];

    if (keys & 128) {
		// Outras Funções
		GetPlayerCameraFront(playerid, playerCam [0], playerCam [1], playerCam [2]);

		// Remover Armas do player
		SetPlayerArmedWeapon(playerid, WEAPON_FIST);

		// Setar o ângulo para mover o Skate
		SetPlayerAngulo(playerid, playerCam [0], playerCam [1]);
	} else {
	    SkateInfo[playerid][s_Speed] -= 0.68;
	}

	GetPlayerPos(playerid, x, y, z[0]);

	// Aplicar a animação de skatista
	ApplyAnimation(playerid,"PED","roadcross_old",8.1,0,1,1,0,0);

	//GetXYInEsquerdaOfPlayer(playerid, x, y, 4.6);
	GetXYInEsquerdaOfObject(SkateInfo[playerid][s_Skate], x, y, 3.5);

	//Pegar a Posição Z de alguns metros à frente
	MapAndreas_FindZ_For2DCoord(x, y, z[1]);

	// Mover o Skate para a pocição à frente
	MoveDynamicObject(SkateInfo[playerid][s_Skate], x, y, z[1] + 0.1, SkateInfo[playerid][s_Speed], 0.0, 0.0, SkateInfo[playerid][s_Angulo]);

	// Checando se está caindo de mais de 10 metros de altura
	if (floatsub(z[0], z[1]) > 10.0) {
	    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você está em um lugar muito alto para andar de Skate !");
	    StopPlayerSkate(playerid);
	    return 1;
	}

	if ((z[0] - 1.0) > z[1]) {

		if (SkateInfo[playerid][s_Speed] < velocidade_skate[playerid]) {
	        SkateInfo[playerid][s_Speed] += 0.6;
	    }
	} else {
	    SkateInfo[playerid][s_Speed] -= 0.1;
	}

    if (SkateInfo[playerid][s_Speed] < 0.1) {
 	   	SendClientMessage(playerid, COLOR_LIGHTRED, "* Seu skate perdeu velocidade e parou !");
	   	StopPlayerSkate(playerid);
   	}

	// Checando um obstáculo a frente, e parando o skate
	if (floatsub(z[1], z[0]) > 0.2) {
	    SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode andar de skate aqui !");
	    StopPlayerSkate(playerid);
	}
	return 1;
}

StopPlayerSkate(playerid) {

	if (SkateInfo[playerid][s_Andando]) {
    	SkateInfo[playerid][s_Andando] = false;
		DestroyDynamicObject(SkateInfo[playerid][s_Skate]);
		SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, 19878, 5, 0.015000,0.026000,0.005999,-111.300125,-7.400022,-97.099937);
        ApplyAnimation(playerid,"PED","roadcross_old",8.1,0,1,1,0,100);
	}
}

SetPlayerSkate(playerid)
{
	if (IsPlayerInAnyVehicle(playerid)) return false;

	if (gettime() < GetPVarInt(playerid, "varFloodSkate")) return SendClientMessage(playerid, COLOR_LIGHTRED, " Aguarde um pouco para andar de skate novamente...");

	SetPVarInt(playerid, "varFloodSkate", gettime() + 2);

	if (SkateInfo[playerid][s_Setado] && !SkateInfo[playerid][s_Andando])
	{
		if (GetPlayerSpeedSkate(playerid) > 25) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você está muito rápido !");

		if (GetPlayerInterior(playerid) != 0) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode andar de skate em interiores !");

		if (GetPlayerPing(playerid) > 350) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Seu ping está muito alto para andar de skate, deve ficar a baixo de 320 !");

		if (PlayerInfo[playerid][pHospital]) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode andar de skate estando hospitalizado !");

		if (patinss[playerid]) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode andar de skate estando de patins !");

		if (IsPlayerInMar(playerid)) return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode andar de skate agora !");

		new Float:x, Float:y, Float:z, Float:ang;
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, ang);

		SetPlayerPos(playerid, x, y, z + 0.2);
		SkateInfo[playerid][s_Update] = 0;
		SkateInfo[playerid][s_Speed]  = GetPlayerSpeedSkate(playerid) / (3.0) + 2.0;
		SkateInfo[playerid][s_Andando]= true;
		SkateInfo[playerid][s_Skate]  = CreateDynamicObject(19878, x, y, z - 0.9, 0.0, 0.0, ang - 90);
		RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);
		UpdatePlayerSkate(playerid, 128);
	}
	return true;
}

stock BuyPlayerSkate(playerid)
{
	if (SkateInfo[playerid][s_Setado]) return SendClientMessage(playerid,COLOR_LIGHTRED,"* Você já está com seu skate, use /guardarskate !"), false;

	SkateInfo[playerid][s_Setado] = true;
	SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, 19878, 5, 0.015000,0.026000,0.005999,-111.300125,-7.400022,-97.099937);

 	SendClientMessage(playerid, 0x00CCCCFF, "* Você pegou seu Skate do inventário, /velocidadeskate para mudar a velocidade e /guardarskate para guardá-lo !");

	SendClientMessage(playerid, COLOR_LIGHTRED, "OBS: Você deve segurar apenas o 'BOTÃO DE MIRAR' e virar o mouse pra direção que desejar !");
	return 1;
}

stock guardarSkate(playerid) givePlayerItem(playerid, ITEM_TYPE_SKATE, 19878, 1, "Skate");

CMD:guardarskate(playerid)
{
	if (SkateInfo[playerid][s_Setado]) {

		if (isInventoryFull(playerid))
	    	return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

		StopPlayerSkate(playerid);
		RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);
		SkateInfo[playerid][s_Setado] = false;
		givePlayerItem(playerid, ITEM_TYPE_SKATE, 19878, 1, "Skate");
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você guardou seu skate no inventário !");
	} else {
		SendClientMessage(playerid, COLOR_LIGHTRED, " Você não possui um Skate !");
	}

	return 1;
}

CMD:velocidadeskate(playerid, params[]) {

	new Float:limite;

	if(sscanf(params, "f", limite))
		return SendClientMessage(playerid, -1, "Use: /velocidadeskate [1 - 18] {FFFFFF}OBS: recomendado menor que 12");

	if(limite < 1.0 || limite > 18.0)
		return SendClientMessage(playerid, -1, "OBS: velocidade de 1 - 18");

	velocidade_skate[playerid] = limite;

	new string[128];

	format(string, sizeof string, "AdmCmd: Você setou a máxima velocidade do skate para %.0fkm/h", velocidade_skate[playerid]);
	SendClientMessage(playerid, COLOR_LIGHTRED, string);

	return 1;
}