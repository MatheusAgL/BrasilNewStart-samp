/*

====================================================================================================================== 

-> M�dulo: Cordas do helic�ptero;
-> Respons�vel por permitir uma corda para descer no ch�o com o helic�ptero no ar.

- Programador: Theus_Crazzy
	> �ltima reforma: 02/04/2022 �s 12:20;
	
	> Pode ser melhorado? D� ideias e fa�a! 

 ====================================================================================================================== 
 
 */

// Includes;
#include < YSI_Coding\y_hooks >

// Defines;
#define ROPE_LENGTH 120	// Tamanho da corda;

// Vari�veis;
static 
	r0pes[MAX_PLAYERS][ROPE_LENGTH], 	// Salva a quantidade de objetos cordas
	Float:pl_pos[MAX_PLAYERS][5]; 		// Salva as posi��es necess�rias

// Comandos;
CMD:corda(playerid)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_PASSENGER)
	    return SendClientMessage(playerid, -1, "Voc� precisa estar como passageiro.");

	new vehicleid = GetPlayerVehicleID(playerid);
	new VIM:vim = Vehicle_GetVIM(vehicleid);

	if (!VIM_IsHelicopter(vim)) 
	    return SendClientMessage(playerid, -1, "Voc� n�o est� em um helicoptero!");
	
	if (GetVehicleSpeed(vehicleid) > 4)
	    return SendClientMessage(playerid, -1, "O helic�ptero deve estar completamente parado.");
	
	// Caso n�o estiver j� usado o comando;
	if (GetPVarInt(playerid,"rope-on") == 0) {

		// Salvar posi��o atual
  		GetPlayerPos(playerid, pl_pos[playerid][0], pl_pos[playerid][1], pl_pos[playerid][2]);

		// Gettar a posi��o em Z do ch�o
		MapAndreas_FindZ_For2DCoord(pl_pos[playerid][0], pl_pos[playerid][1], pl_pos[playerid][3]);

		// Calcula a altura para chegar ao ch�o
		pl_pos[playerid][4] = floatsub(pl_pos[playerid][2], pl_pos[playerid][3]);

		// Verifica se a altura � maior que a corda
		if (pl_pos[playerid][4] >= ROPE_LENGTH)
			return SendClientMessage(playerid,-1,"O Helicoptero est� muito alto para descer!");

		// Se estiver muito baixo, desce do helic�ptero
      	if (pl_pos[playerid][4] <= 3)
		  	return RemovePlayerFromVehicle(playerid);

		// Define que est� descendo na corda do ve�culo id...
		SetPVarInt(playerid, "rope-on", 1);
		SetPVarInt(playerid, "heli-ropes-id", vehicleid);

		// Define um checkpoint no ch�o
		SetPlayerCheckpoint(playerid, pl_pos[playerid][0], pl_pos[playerid][1], floatsub(pl_pos[playerid][3], 12.0) + 3.0, 20.0);

		// Define a posi��o do jogador ap�s come�ar a descer na corda, e diminue -3.0 para ficar abaixo do helic�ptero.
		SetPlayerPos(playerid, pl_pos[playerid][0], pl_pos[playerid][1], floatsub(pl_pos[playerid][2], 3.0));

		// N�o sei exatamente a necessidade disso...
		SetPlayerVelocity(playerid, 0, 0, 0);

		// Anima��o em loop;
        ApplyAnimation(playerid, "ped", "abseil", 4.0, true, false, false, false, false);

        for(new rope_leght; rope_leght <= pl_pos[playerid][4]; rope_leght++) {
        	r0pes[playerid][rope_leght] = CreateDynamicObject(3004, pl_pos[playerid][0], pl_pos[playerid][1], floatadd(pl_pos[playerid][3], rope_leght), 87.640026855469, 342.13500976563, 350.07507324219);
      	}
 	}
	return 1;
}

// Fun��es;
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