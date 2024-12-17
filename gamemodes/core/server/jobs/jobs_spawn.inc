
stock Player_SpawnInJob(playerid) {
    if (PlayerIsAdvogado(playerid))            // Advogados
    {
        SetPlayerInterior(playerid, 0);
        SetPlayerPos(playerid, 1739.2667,-1583.4945,14.1584);
        SetPlayerFacingAngle(playerid,2.2139);
        SetPlayerVirtualWorld(playerid,0);
    }
    else if (PlayerIsCaminhoneiro(playerid))			// Caminhoneiro
    {
        SetPlayerInterior(playerid, 0);
        SetPlayerPos(playerid, 1375.9441,1057.7214,10.8203);
        SetPlayerFacingAngle(playerid, 271.5050);
        SetPlayerVirtualWorld(playerid,0);
    }
    else if (PlayerIsGari(playerid))        			// Lixeiro
    {
        SetPlayerInterior(playerid, 0);
        SetPlayerPos(playerid, 2198.5359,-2010.0414,13.5469);
        SetPlayerFacingAngle(playerid, 295.0911);
        SetPlayerVirtualWorld(playerid, 0);
    }
    else if (PlayerIsTaxista(playerid))        			// Taxista
    {
        SetPlayerInterior(playerid, 0);
        SetPlayerPos(playerid, 1564.1434,-2228.2656,13.5547);
        SetPlayerFacingAngle(playerid, 58.8197);
        SetPlayerVirtualWorld(playerid, 0);
    }
    else if(PlayerIsMedico(playerid)) {
        SetPlayerVirtualWorld(playerid,0);
        SetPlayerInterior(playerid, 10);
        SetPlayerPos(playerid, 1164.6228,-1326.4603,-44.2836);
        SetPlayerFacingAngle(playerid,272.3499);
    }
    else if(PlayerIsMecanico(playerid)) {
        SetPlayerVirtualWorld(playerid,0);
        SetPlayerInterior(playerid, 0);
        SetPlayerPos(playerid, 2142.0698,-1729.8184,13.5592);
        SetPlayerFacingAngle(playerid,272.3499);
    }
    else if (PlayerIsMinerador(playerid)) 			// Minerador
    {
        SetPlayerInterior(playerid, 0);
        SetPlayerPos(playerid, 1003.9560,-91.6045,22.4495);
        SetPlayerFacingAngle(playerid, 28.0772);
        SetPlayerVirtualWorld(playerid, 0);
    }
    else if (PlayerIsFazendeiro(playerid)) 			// Fazendeiro
    {
        SetPlayerInterior(playerid, 0);
        SetPlayerPos(playerid, -95.3570,-26.0419,3.1172);
        SetPlayerFacingAngle(playerid, 66.6228);
        SetPlayerVirtualWorld(playerid, 0);
    }
    else if (PlayerIsFabricanteMat(playerid)) 			// Fabricante de Materiais
    {
        SetPlayerInterior(playerid, 0);
        SetPlayerPos(playerid, 2846.3477, 976.9812, 10.7500);
        SetPlayerFacingAngle(playerid, 93.6716);
        SetPlayerVirtualWorld(playerid, 0);
    }
    else if (IsPlayerFirefighter(playerid)) 			// Bombeiro
    {
        SetPlayerPos(playerid,957.3861,-1747.2125,19.3432);
        SetPlayerFacingAngle(playerid, 180.000);
        SetPlayerInterior(playerid, 0);
        SetPlayerVirtualWorld(playerid, 0);
    }
    else {
        SendClientMessage(playerid, COLOR_LIGHTRED, "Seu emprego não tem uma HQ!");
        Player_SetSpawnType(playerid, TYPE_SPAWN_DEFAULT);
    }
}

stock HasJobHQ(jobid) {
    switch(jobid) {
        case ID_JOB_ADVOGADO, ID_JOB_CAMINHONEIRO, ID_JOB_LIXEIRO, ID_JOB_TAXISTA, ID_JOB_MEDICO, ID_JOB_MECANICO, ID_JOB_MINERADOR, ID_JOB_FAZENDEIRO, ID_JOB_VENDEDOR_ARMAS, ID_JOB_FIREFIGHTER:
            return true;
    }
    return false;
}

stock ShowPlayerJobs(playerid) {
	MEGAString[0] = EOS;
	strcat(MEGAString, "Slot\tNome\n");
    if(PlayerInfo[playerid][pEmprego])
        FormatCat(MEGAString, "1\t%s\n", GetJobName(PlayerInfo[playerid][pEmprego]));
    if(PlayerInfo[playerid][pEmprego2])
        FormatCat(MEGAString, "2\t%s\n", GetJobName(PlayerInfo[playerid][pEmprego2]));

	inline D_MyJobs(mdlid, mdldialogid, mdlresponse, mdllistitem, string:mdltext[])
	{
		#pragma unused mdlid, mdldialogid, mdltext
		if (!mdlresponse)
			return 1;

		if (mdllistitem != -1) {
            new jobid = mdllistitem == 0 ? PlayerInfo[playerid][pEmprego] : PlayerInfo[playerid][pEmprego2];

            if(!HasJobHQ(jobid))
                return SendClientMessage(playerid, -1, "O seu emprego não possui uma HQ.");

			Player_SetSpawnType(playerid, TYPE_SPAWN_JOB, mdllistitem);
		}
		return 1;
	}
	Dialog_ShowCallback(playerid, using inline D_MyJobs, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Selecione um emprego", MEGAString, "Selecionar", "Fechar");
	return 1;
}