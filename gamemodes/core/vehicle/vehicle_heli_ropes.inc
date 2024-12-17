/*

====================================================================================================================== 

-> Módulo: Cordas do helicóptero;
-> Responsável por permitir uma corda para descer no chão com o helicóptero no ar.

- Programador: Theus_Crazzy
	> Última reforma: 02/04/2022 ás 12:20;
	
	> Pode ser melhorado? Dê ideias e faça! 

 ====================================================================================================================== 
 
 */

// Includes;
#include < YSI_Coding\y_hooks >

// Defines;
#define ROPE_LENGTH 120	// Tamanho da corda;

// Variáveis;
static 
	r0pes[MAX_PLAYERS][ROPE_LENGTH], 	// Salva a quantidade de objetos cordas
	Float:pl_pos[MAX_PLAYERS][5]; 		// Salva as posições necessárias

// Comandos;
CMD:corda(playerid)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_PASSENGER)
	    return SendClientMessage(playerid, -1, "Você precisa estar como passageiro.");

	new vehicleid = GetPlayerVehicleID(playerid);
	new VIM:vim = Vehicle_GetVIM(vehicleid);

	if (!VIM_IsHelicopter(vim)) 
	    return SendClientMessage(playerid, -1, "Você não está em um helicoptero!");
	
	if (GetVehicleSpeed(vehicleid) > 4)
	    return SendClientMessage(playerid, -1, "O helicóptero deve estar completamente parado.");
	
	// Caso não estiver já usado o comando;
	if (GetPVarInt(playerid,"rope-on") == 0) {

		// Salvar posição atual
  		GetPlayerPos(playerid, pl_pos[playerid][0], pl_pos[playerid][1], pl_pos[playerid][2]);

		// Gettar a posição em Z do chão
		MapAndreas_FindZ_For2DCoord(pl_pos[playerid][0], pl_pos[playerid][1], pl_pos[playerid][3]);

		// Calcula a altura para chegar ao chão
		pl_pos[playerid][4] = floatsub(pl_pos[playerid][2], pl_pos[playerid][3]);

		// Verifica se a altura é maior que a corda
		if (pl_pos[playerid][4] >= ROPE_LENGTH)
			return SendClientMessage(playerid,-1,"O Helicoptero está muito alto para descer!");

		// Se estiver muito baixo, desce do helicóptero
      	if (pl_pos[playerid][4] <= 3)
		  	return RemovePlayerFromVehicle(playerid);

		// Define que está descendo na corda do veículo id...
		SetPVarInt(playerid, "rope-on", 1);
		SetPVarInt(playerid, "heli-ropes-id", vehicleid);

		// Define um checkpoint no chão
		SetPlayerCheckpoint(playerid, pl_pos[playerid][0], pl_pos[playerid][1], floatsub(pl_pos[playerid][3], 12.0) + 3.0, 20.0);

		// Define a posição do jogador após começar a descer na corda, e diminue -3.0 para ficar abaixo do helicóptero.
		SetPlayerPos(playerid, pl_pos[playerid][0], pl_pos[playerid][1], floatsub(pl_pos[playerid][2], 3.0));

		// Não sei exatamente a necessidade disso...
		SetPlayerVelocity(playerid, 0, 0, 0);

		// Animação em loop;
        ApplyAnimation(playerid, "ped", "abseil", 4.0, true, false, false, false, false);

        for(new rope_leght; rope_leght <= pl_pos[playerid][4]; rope_leght++) {
        	r0pes[playerid][rope_leght] = CreateDynamicObject(3004, pl_pos[playerid][0], pl_pos[playerid][1], floatadd(pl_pos[playerid][3], rope_leght), 87.640026855469, 342.13500976563, 350.07507324219);
      	}
 	}
	return 1;
}

// Funções;
hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    // --------------------------------------------------------------------------------------------
	// Cordas no helicoptero
    new VIM:vim = Vehicle_GetVIM(vehicleid);

	if (VIM_IsHelicopter(vim)) 
        ShowPlayerBaloonInfo(playerid, "~w~Para descer na corda do helicoptero ~n~Use o comando ~b~/corda", 5000);

    return 1;
}

hook OnVehicleDeath(vehicleid, killerid) 
{
	new VIM:vim = Vehicle_GetVIM(vehicleid);

	if (VIM_IsHelicopter(vim)) {

		foreach(new playerid : Player) {

      		if (GetPlayerVehicleRopes(playerid) == vehicleid && GetPlayerRopes(playerid)) {

             	DisablePlayerCheckpoint(playerid);
				
              	ClearAnimations(playerid);
				
               	TogglePlayerControllable(playerid, true);

               	DestroyRopesObjects(playerid);
        	}
     	}
	}
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) 
{
	// Destruir os objetos da corda caso o jogador se desconecte;
    if (GetPlayerRopes(playerid)) {
    	DestroyRopesObjects(playerid);
	}
    return 1;
}

hook OnPlayerEnterCheckpoint(playerid)
{
    if (GetPlayerRopes(playerid))
    {
        ClearAnimations(playerid);

        TogglePlayerControllable(playerid, true);

        DisablePlayerCheckpoint(playerid);

        DestroyRopesObjects(playerid);

       	return 1;
	}
    return 1;
}

static GetPlayerRopes(playerid) {
	return GetPVarInt(playerid, "rope-on");
}

static DestroyRopesObjects(playerid) {
	SetPVarInt(playerid, "rope-on", 0);
    SetPVarInt(playerid, "heli-ropes-id", INVALID_VEHICLE_ID);

	for(new rope_leght; rope_leght <= ROPE_LENGTH; rope_leght++)
      	DestroyDynamicObject(r0pes[playerid][rope_leght]);
}

static GetPlayerVehicleRopes(playerid) {
	return GetPVarInt(playerid, "heli-ropes-id");
}