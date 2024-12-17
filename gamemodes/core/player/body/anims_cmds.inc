CMD:anims(playerid)
{
    MEGAString[0] = EOS;

    format(MEGAString, sizeof(MEGAString), ""C_GRAY"Lista de animações: \n\n\
                                            "C_WHITE"/mijar /beijar /cumprimentar /boquete /sentar /deitar /tchau /protegerse /chega /alongar /boxe /morto /masturbar /apontar\n\n\
                                            /dance /handsup /animairport /animat /animbar /animball /animfire /animbeach /animbp /animinf /animbiked /animbh /animfood\n\
                                            /animbikelp /animms /animbikes /animcar /animbikev /animbmx /animbikedbz /animchase /animbox /animbomber /animbsp /animcamera\n\
                                            /animgym /animpara /animgangs /animlookers /animcarchat /animcasino /animbuddy /animbus /animcarry /animintshop /animjst\n\
                                            /animkart /animkissing /animknife /animlapdan /animdend /animmedic /animmtb /animmusc /animotb /animpark /animsaw /animchoppa\n\
                                            /animclothes /animcoach /animcolt /animcopa /animcod /animcrack /animpaulnmac /animcrib /animjump /animdealer /animdildo\n\
                                            /animdodge /animdozer /animdrivebys /animfat /animfightb /animfightc /animfightd /animfighte /animfinale /animfinale2 /animflamef\n\
                                            /animflowers /animghands /animfw /animghetto /animgog /animgraffity /animgreya /animgren /animhaircut /animheist /animinthouse\n\
                                            /animintoffice /animplayerdbf /animplayidles /animpolice /animpool /animpoor /animpython /animquad /animquadbz /animrapping\n\
                                            /animrifle /animriot /animrobbank /animrocket /animrustler /animryder /animscrat /animshamal /animshop /animskate /animshotgun\n\
                                            /animvortex /animtec /animtrain /animsil /animtattoo  /animsmoking /animsniper /animspray /animstrip /animbath /animswat /animsweet\n\
                                            /animswim /animsword /animtank /animtruck /animuzi  /animvan /animvending /animway /animweap /animblowjob\n\
                                            ");

    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Animações", MEGAString, "Fechar", #);
	return 1;
}
alias:anims("animlist", "animlist2")

CMD:beijar(playerid, params[])
{
	new idplayer, style;
	if (sscanf(params, "ud", idplayer, style))
		return SendClientMessage(playerid, -1, "Modo de uso: /beijar (id do jogador) (style: 1, 2 ou 3)");

	if (idplayer == playerid)
        return 1;

	if (!Player_Logado(idplayer))
        return SendClientMessage(playerid, -1, "Esse jogador não está conectado/logado no servidor.");

    if (!ProxDetectorS(1.0, playerid, idplayer))
        return SendClientMessage(playerid, -1, "Você não está próximo desse jogador.");

    if (style < 1 || style > 3)
        return SendClientMessage(playerid, -1, "Escolha o estilo do beijo, 1, 2 ou 3.");
        
    SendMsgF(playerid, COLOR_LIGHTBLUE, "* %s está querendo te dar um beijo, pressione 'Y' para aceitar ou 'N' para negar.", PlayerName[playerid]);
    SendMsgF(playerid, COLOR_LIGHTBLUE, "* Você pediu para dar um beijo em %s, aguarde uma resposta...", PlayerName[idplayer]);

    PairAction(playerid, idplayer, KISS_ACTION, style);

	return 1;
}

CMD:continencia(playerid)
{
	new string[78];

	format(string, sizeof(string), "* %s bateu continência.", PlayerName[playerid]);
	SendClientMessageInRange(15.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

	ApplyAnimation(playerid, "ON_LOOKERS", "Pointup_shout", 4.1, false, true, true, false, 0);
	return 1;
}

CMD:mijar(playerid)
{
	if (GetPVarInt(playerid, "movelRoubou"))
		return SendClientMessage(playerid, -1, "Você não pode usar este comando agora !");

	ApplyAnimation(playerid, "PAULNMAC", "Piss_in", 4.0, true, false, false, false, 0);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_PISSING);
	CheckConquista(playerid, Conquista_Mijar);
	return 1;
}

CMD:sentar(playerid) 
{
    if (GetPlayerAnimationIndex(playerid) != 1189) {
        ApplyAnimation(playerid, "PED", "SEAT_up", 4.0, false, true, true, true, 1, SYNC_ALL);
    } else {
        ApplyAnimation(playerid, "PED", "SEAT_down", 4.0, false, true, true, true, 1, SYNC_ALL);
    }
	return 1;
}

CMD:deitar(playerid) 
{
    ApplyAnimation(playerid,"CRACK", "crckidle2", 4.1, false, false, false, true, 1, SYNC_ALL);
	return 1;
}

CMD:tchau(playerid) 
{
    ApplyAnimation(playerid,"PED", "endchat_03", 4.1, false, true, true, false, 0, SYNC_ALL);
	return 1;
}

CMD:protegerse(playerid) 
{
    ApplyAnimation(playerid,"PED", "DUCK_cower", 4.1, false, false, false, true, 1, SYNC_ALL);
	return 1;
}

CMD:chega(playerid) {

    ApplyAnimation(playerid,"PED","endchat_02", 4.1, false, true, true, false, 0, SYNC_ALL);
	return 1;
}

CMD:alongar(playerid) {

    ApplyAnimation(playerid,"PLAYIDLES","stretch",4.1, false, true, true, false, 0, SYNC_ALL);
	return 1;
}

CMD:boxe(playerid) {

    ApplyAnimation(playerid,"GYMNASIUM","GYMshadowbox",4.1, false, true, true, false, 0, SYNC_ALL);
	return 1;
}

CMD:morto(playerid) {

    ApplyAnimation(playerid,"PED","FLOOR_hit_f",4.1, false, false, false, true, 1, SYNC_ALL);
	return 1;
}

CMD:masturbar(playerid) {

    ApplyAnimation(playerid,"PAULNMAC","wank_loop",4.1, false, true, true, false, 0, SYNC_ALL);
	return 1;
}

CMD:apontar(playerid) {

    ApplyAnimation(playerid,"PED","gang_gunstand",4.1, false, false, false, true, 1, SYNC_ALL);
	return 1;
}


CMD:dance(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid,COLOR_RED," Proibido anims em veiculos.");
	new dancing;
	if(sscanf(params, "d", dancing))
	{
		SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /dance [1-15]");
		return true;
	}
	if(dancing < 1 || dancing > 15) return SendClientMessage(playerid, 0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /dance [1-15]");
    CheckConquista(playerid, Conquista_Danca);
	switch(dancing)
	{
		case 1: SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
		case 2: SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
		case 3: SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE3);
		case 4: SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
   	    case 5:ApplyAnimation(playerid, "DANCING","dance_loop", 4.0, true, true, true, true, 0, SYNC_ALL);
	    case 6:ApplyAnimation(playerid, "DANCING","DAN_Down_A", 4.0, true, true, true, true, 0, SYNC_ALL);
	    case 7:ApplyAnimation(playerid, "DANCING","DAN_Left_A", 4.0, true, true, true, true, 0, SYNC_ALL);
	    case 8:ApplyAnimation(playerid, "DANCING","DAN_Loop_A", 4.0, true, true, true, true, 0, SYNC_ALL);
	    case 9:ApplyAnimation(playerid, "DANCING","DAN_Right_A", 4.0, true, true, true, true, 0, SYNC_ALL);
	    case 10:ApplyAnimation(playerid, "DANCING","DAN_Up_A", 4.0, true, true, true, true, 0, SYNC_ALL);
	    case 11:ApplyAnimation(playerid, "DANCING","dnce_M_a", 4.0, true, true, true, true, 0, SYNC_ALL);
	    case 12:ApplyAnimation(playerid, "DANCING","dnce_M_b", 4.0, true, true, true, true, 0, SYNC_ALL);
	    case 13:ApplyAnimation(playerid, "DANCING","dnce_M_c", 4.0, true, true, true, true, 0, SYNC_ALL);
	    case 14:ApplyAnimation(playerid, "DANCING","dnce_M_d", 4.0, true, true, true, true, 0, SYNC_ALL);
	    case 15:ApplyAnimation(playerid, "DANCING","dnce_M_ e", 4.0, true, true, true, true, 0, SYNC_ALL);
	}
	return true;
}

CMD:handsup(playerid)
{
	if (GetPVarInt(playerid, "movelRoubou"))
	   	return SendClientMessage(playerid, COLOR_GREY, " Você não pode usar este comando agora !");

    //if (IsPlayerCongelado(playerid))return SendClientMessage(playerid, COLOR_GREY, " Você não pode usar este comando estando congelado !");

	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_HANDSUP);
	return true;
}

CMD:animbar(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbar [1-12]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 12) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbar [1-12]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BAR","Barcustom_get", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BAR","Barcustom_loop",4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BAR","Barcustom_order", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BAR","Barserve_bottle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BAR","Barserve_give", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BAR","Barserve_glass", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BAR","Barserve_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BAR","Barserve_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BAR","Barserve_order", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BAR","dnk_stndF_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"BAR","dnk_stndM_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"BAR","BARman_idle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animball(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animball [1-11]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 11) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animball [1-11]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BASEBALL","Bat_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BASEBALL","Bat_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BASEBALL","Bat_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BASEBALL","Bat_4", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BASEBALL","Bat_block", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BASEBALL","Bat_Hit_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BASEBALL","Bat_Hit_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BASEBALL","Bat_Hit_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BASEBALL","Bat_IDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BASEBALL","Bat_M", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"BASEBALL","BAT_PART", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animfire(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfire [1-13]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 13) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfire [1-13]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BD_FIRE","BD_Fire1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BD_FIRE","BD_Fire2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BD_FIRE","BD_Fire3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BD_FIRE","BD_GF_Wave", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BD_FIRE","BD_Panic_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BD_FIRE","BD_Panic_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BD_FIRE","BD_Panic_03", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BD_FIRE","BD_Panic_04", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BD_FIRE","BD_Panic_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BD_FIRE","M_smklean_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"BD_FIRE","M_smklean_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"BD_FIRE","Playa_Kiss_03", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"BD_FIRE","wash_up", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


// CMD:animbeach(playerid, params[])
// {
//     new animationplayed;
//     if(sscanf(params, "d", animationplayed)) {
//         SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbeach [1-5]");
//         return 1;
//     }

//     if(animationplayed < 1 || animationplayed > 5) {
//         SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbeach [1-5]");
//         return 1;
//     }
//     if(animationplayed == 1) {
//         ApplyAnimation(playerid,"BEACH","bather", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 2) {
//         ApplyAnimation(playerid,"BEACH","Lay_Bac_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 3) {
//         ApplyAnimation(playerid,"BEACH","BD_Fire3", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 4) {
//         ApplyAnimation(playerid,"BEACH","ParkSit_W_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 5) {
//         ApplyAnimation(playerid,"BEACH","SitnWait_loop_W", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     return 1;
// }


CMD:animinf(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animinf [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animinf [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BF_injection","BF_getin_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BF_injection","BF_getin_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BF_injection","BF_getout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BF_injection","BF_getout_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbiiked(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbiked [1-18]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 18) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbiked [1-18]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 1) {
        ApplyAnimation(playerid,"BIKED","BIKEd_drivebyFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BIKED","BIKEd_drivebyLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BIKED","BIKEd_drivebyRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BIKED","BIKEd_getoffBACK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BIKED","BIKEd_getoffLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BIKED","BIKEd_getoffRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BIKED","BIKEd_hit", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BIKED","BIKEd_jumponL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BIKED","BIKEd_jumponR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"BIKED","BIKEd_kick", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"BIKED","BIKEd_passenger", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"BIKED","BIKEd_pushes", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Ride", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"BIKED","BIKEd_shuffle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Still", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbp(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbp [1-7]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 7) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbp [1-7]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"benchpress","gym_bp_celebrate", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"benchpress","gym_bp_down", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"benchpress","gym_bp_getoff", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"benchpress","gym_bp_geton", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"benchpress","gym_bp_up_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"benchpress","gym_bp_up_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"benchpress","gym_bp_up_smooth", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbh(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbh [1-18]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 18) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbh [1-18]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_Back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_drivebyFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_drivebyLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_drivebyRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_getoffBACK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_getoffLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_getoffRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_hit", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_jumponL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_jumponR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_kick", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_passenger", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_pushes", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_Ride", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_Still", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animms(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animms [1-8]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 8) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animms [1-8]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_Back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_drivebyFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_drivebyLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_drivebyRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_getoffBACK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_getoffLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BIKEH","BIKEh_getoffRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animfood(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfood [1-33]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 33) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfood [1-33]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"FOOD","EAT_Burger", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {//
        ApplyAnimation(playerid,"FOOD","EAT_Chicken", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"FOOD","EAT_Pizza", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"FOOD","EAT_Vomit_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"FOOD","EAT_Vomit_SK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"FOOD","FF_Dam_Bkw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"FOOD","FF_Dam_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"FOOD","FF_Dam_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"FOOD","FF_Dam_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"FOOD","FF_Die_Bkw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"FOOD","FF_Die_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"FOOD","FF_Die_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"FOOD","FF_Die_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"FOOD","FF_Sit_Eat1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"FOOD","FF_Sit_Eat2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"FOOD","FF_Sit_Eat3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"FOOD","FF_Sit_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"FOOD","FF_Sit_In_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"FOOD","FF_Sit_In_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"FOOD","FF_Sit_Look", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"FOOD","FF_Sit_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"FOOD","FF_Sit_Out_180", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"FOOD","FF_Sit_Out_L_180", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 24) {
        ApplyAnimation(playerid,"FOOD","FF_Sit_Out_R_180", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 25) {
        ApplyAnimation(playerid,"FOOD","SHP_Thank", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 26) {
        ApplyAnimation(playerid,"FOOD","SHP_Tray_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 27) {
        ApplyAnimation(playerid,"FOOD","SHP_Tray_Lift", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 28) {
        ApplyAnimation(playerid,"FOOD","SHP_Tray_Lift_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 29) {
        ApplyAnimation(playerid,"FOOD","SHP_Tray_Lift_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 30) {
        ApplyAnimation(playerid,"FOOD","SHP_Tray_Lift_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 31) {
        ApplyAnimation(playerid,"FOOD","SHP_Tray_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 32) {
        ApplyAnimation(playerid,"FOOD","SHP_Tray_Pose", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 33) {
        ApplyAnimation(playerid,"FOOD","SHP_Tray_Return", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animms2(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animms2 [1-41]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 41) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animms2 [1-41]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"MISC","bitchslap", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"MISC","BMX_celebrate", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"MISC","BMX_comeon", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"MISC","bmx_idleloop_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"MISC","bmx_idleloop_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"MISC","bmx_talkleft_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"MISC","bmx_talkleft_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"MISC","bmx_talkleft_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"MISC","bmx_talkright_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"MISC","bmx_talkright_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"MISC","bmx_talkright_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"MISC","bng_wndw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"MISC","bng_wndw_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"MISC","Case_pickup", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"MISC","door_jet", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"MISC","GRAB_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"MISC","GRAB_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"MISC","Hiker_Pose", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"MISC","Hiker_Pose_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"MISC","Idle_Chat_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"MISC","KAT_Throw_K", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"MISC","KAT_Throw_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"MISC","KAT_Throw_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 24) {
        ApplyAnimation(playerid,"MISC","PASS_Rifle_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 25) {
        ApplyAnimation(playerid,"MISC","PASS_Rifle_Ped", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 26) {
        ApplyAnimation(playerid,"MISC","PASS_Rifle_Ply", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 27) {
        ApplyAnimation(playerid,"MISC","pickup_box", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 28) {
        ApplyAnimation(playerid,"MISC","Plane_door", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 29) {
        ApplyAnimation(playerid,"MISC","Plane_exit", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 30) {
        ApplyAnimation(playerid,"MISC","Plane_hijack", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 31) {
        ApplyAnimation(playerid,"MISC","Plunger_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 32) {
        ApplyAnimation(playerid,"MISC","Plyrlean_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 33) {
        ApplyAnimation(playerid,"MISC","plyr_shkhead", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed ==  34) {
        ApplyAnimation(playerid,"MISC","Run_Dive", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 35) {
        ApplyAnimation(playerid,"MISC","Scratchballs_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 36) {
        ApplyAnimation(playerid,"MISC","SEAT_LR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 37) {
        ApplyAnimation(playerid,"MISC","Seat_talk_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 38) {
        ApplyAnimation(playerid,"MISC","Seat_talk_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 39) {
        ApplyAnimation(playerid,"MISC","SEAT_watch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 40) {
        ApplyAnimation(playerid,"MISC","smalplane_door", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 41) {
        ApplyAnimation(playerid,"MISC","smlplane_door", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbikelp(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbikelp [1-9]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 9) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbikelp [1-9]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BIKELEAP","bk_blnce_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BIKELEAP","bk_blnce_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BIKELEAP","bk_jmp", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BIKELEAP","bk_rdy_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BIKELEAP","bk_rdy_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BIKELEAP","struggle_cesar", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BIKELEAP","struggle_driver", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BIKELEAP","truck_driver", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BIKELEAP","truck_getin", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbikes(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbikes [1-18]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 18) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbikes [1-18]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BIKES","BIKEs_Back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BIKES","BIKEs_drivebyFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BIKES","BIKEs_drivebyLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BIKES","BIKEs_drivebyRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BIKES","BIKEs_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BIKES","BIKEs_getoffBACK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BIKES","BIKEs_getoffLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BIKES","BIKEs_getoffRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BIKES","BIKEs_hit", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BIKES","BIKEs_jumponL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"BIKES","BIKEs_jumponR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"BIKES","BIKEs_kick", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"BIKES","BIKEs_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"BIKES","BIKEs_passenger", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"BIKES","BIKEs_pushes", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"BIKES","BIKEs_Ride", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"BIKES","BIKEs_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"BIKES","BIKEs_Still", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbikev(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbikev [1-18]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 18) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbikev [1-18]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_Back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_drivebyFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_drivebyLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_drivebyRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_getoffBACK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_getoffLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_getoffRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_hit", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_jumponL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_jumponR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_kick", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_passenger", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_pushes", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_Ride", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"BIKEV","BIKEv_Still", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbmx(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbmx [1-18]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 18) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbmx [1-18]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BMX","BMX_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BMX","BMX_bunnyhop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BMX","BMX_drivebyFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BMX","BMX_driveby_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BMX","BMX_driveby_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BMX","BMX_fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BMX","BMX_getoffBACK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BMX","BMX_pushes", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BMX","BMX_getoffLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BMX","BMX_getoffRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"BMX","BMX_jumponL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"BMX","BMX_jumponR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"BMX","BMX_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"BMX","BMX_pedal", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"BMX","BMX_Ride", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"BMX","BMX_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"BMX","BMX_sprint", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"BMX","BMX_still", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbikedbz(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbikedbz [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbikedbz [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BIKE_DBZ","Pass_Driveby_BWD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BIKE_DBZ","Pass_Driveby_FWD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BIKE_DBZ","Pass_Driveby_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BIKE_DBZ","Pass_Driveby_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animchase(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animchase [1-25]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 25) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animchase [1-25]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"MD_CHASE","Carhit_Hangon", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"MD_CHASE","Carhit_Tumble", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"MD_CHASE","donutdrop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"MD_CHASE","Fen_Choppa_L1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"MD_CHASE","Fen_Choppa_L2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"MD_CHASE","Fen_Choppa_L3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"MD_CHASE","Fen_Choppa_R1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"MD_CHASE","Fen_Choppa_R2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"MD_CHASE","Fen_Choppa_R3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"MD_CHASE","Hangon_Stun_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"MD_CHASE","Hangon_Stun_Turn", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_2_HANG", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_Jmp_BL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_Jmp_F", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_Lnd_BL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_Lnd_Die_BL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_Lnd_Die_F", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_Lnd_F", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll_F", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_Punch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_Punch_F", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"MD_CHASE","MD_BIKE_Shot_F", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 24) {
        ApplyAnimation(playerid,"MD_CHASE","MD_HANG_Lnd_Roll", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 25) {
        ApplyAnimation(playerid,"MD_CHASE","MD_HANG_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbox(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbox [1-10]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 10) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbox [1-10]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BOX","boxhipin", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BOX","boxhipup", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BOX","boxshdwn", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BOX","boxshup", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BOX","bxhipwlk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BOX","bxhwlki", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BOX","bxshwlk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BOX","bxshwlki", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BOX","bxwlko", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BOX","catch_box", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbomber(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbomber [1-6]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 6) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbomber [1-6]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BOMBER","BOM_Plant", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BOMBER","BOM_Plant_Crouch_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BOMBER","BOM_Plant_Crouch_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BOMBER","BOM_Plant_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BOMBER","BOM_Plant_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbsp(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbsp [1-41]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 41) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbsp [1-41]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_def_jump_shot", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_def_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_def_stepL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_def_stepR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk_Gli", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk_Gli_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk_Lnch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk_Lnch_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk_Lnd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_idle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_idle2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_idle2_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_idleloop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_idleloop_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_idle_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Cancel", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Cancel_0", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_End", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_Net_Dnk_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 24) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_pickup", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 25) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_pickup_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 26) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_react_miss", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 27) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_react_score", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 28) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_run", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 29) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_run_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 30) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_SkidStop_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 31) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_SkidStop_L_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 32) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_SkidStop_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 33) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_SkidStop_R_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed ==  34) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_walk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 35) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_WalkStop_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 36) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_WalkStop_L_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 37) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_WalkStop_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 38) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_WalkStop_R_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 39) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_walk_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 40) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_walk_start", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 41) {
        ApplyAnimation(playerid,"BSKTBALL","BBALL_walk_start_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}

CMD:creu(playerid)
{
    new string[128];
	format(string, sizeof(string), "* %s está dançando o créu.", PlayerName[playerid]);
	SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
    ApplyAnimation(playerid,"CHOPPA","CHOPPA_back",4.1,1,1,1,1,1);
    return 1;
 }

CMD:animcamera(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcamera [1-14]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 14) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcamera [1-14]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"CAMERA","camcrch_cmon", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"CAMERA","camcrch_idleloop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"CAMERA","camcrch_stay", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"CAMERA","camcrch_to_camstnd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"CAMERA","camstnd_cmon", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"CAMERA","camstnd_idleloop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"CAMERA","camstnd_lkabt", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"CAMERA","camstnd_to_camcrch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"CAMERA","piccrch_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"CAMERA","piccrch_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"CAMERA","piccrch_take", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"CAMERA","picstnd_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"CAMERA","picstnd_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"CAMERA","picstnd_take", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animgym(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgym [1-24]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 24) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgym [1-24]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"GYMNASIUM","GYMshadowbox", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_bike_celebrate", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_bike_fast", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_bike_faster", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_bike_getoff", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_bike_geton", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_bike_pedal", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_bike_slow", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_bike_still", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_jog_falloff", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_shadowbox", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_tread_celebrate", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_tread_falloff", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_tread_getoff", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_tread_geton", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_tread_jog", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_tread_sprint", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_tread_tired", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_tread_walk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"GYMNASIUM","gym_walk_falloff", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"GYMNASIUM","Pedals_fast", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"GYMNASIUM","Pedals_med", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"GYMNASIUM","Pedals_slow", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 24) {
        ApplyAnimation(playerid,"GYMNASIUM","Pedals_still", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animpara(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpara [1-21]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 21) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpara [1-21]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"PARACHUTE","FALL_skyDive", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"PARACHUTE","FALL_SkyDive_Accel", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"PARACHUTE","FALL_skyDive_DIE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"PARACHUTE","FALL_SkyDive_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"PARACHUTE","FALL_SkyDive_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_decel", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_decel_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_float", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_float_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_Land", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_Land_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_Land_Water", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_Land_Water_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_open", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_open_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_Rip_Land_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_Rip_Loop_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_Rip_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_steerL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_steerL_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"PARACHUTE","PARA_steerR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animgangs(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgangs [1-22]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 22) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgangs [1-22]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"GANGS","DEALER_DEAL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"GANGS","DEALER_IDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"GANGS","drnkbr_prtl", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"GANGS","drnkbr_prtl_F", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"GANGS","DRUGS_BUY", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"GANGS","hndshkaa", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"GANGS","hndshkba", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"GANGS","hndshkca", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"GANGS","hndshkcb", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"GANGS","hndshkda", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"GANGS","hndshkea", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"GANGS","hndshkfa", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"GANGS","hndshkfa_swt", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"GANGS","Invite_No", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"GANGS","Invite_Yes", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"GANGS","leanIDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"GANGS","leanIN", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"GANGS","leanOUT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"GANGS","prtial_gngtlkA", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"GANGS","prtial_gngtlkB", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"GANGS","prtial_gngtlkCt", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"GANGS","prtial_gngtlkD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"GANGS","prtial_gngtlkE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 24) {
        ApplyAnimation(playerid,"GANGS","prtial_gngtlkF", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 25) {
        ApplyAnimation(playerid,"GANGS","prtial_gngtlkG", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 26) {
        ApplyAnimation(playerid,"GANGS","prtial_gngtlkH", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 27) {
        ApplyAnimation(playerid,"GANGS","prtial_hndshk_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 28) {
        ApplyAnimation(playerid,"GANGS","prtial_hndshk_biz_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 29) {
        ApplyAnimation(playerid,"GANGS","shake_cara", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 30) {
        ApplyAnimation(playerid,"GANGS","shake_carK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 31) {
        ApplyAnimation(playerid,"GANGS","shake_carSH", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 32) {
        ApplyAnimation(playerid,"GANGS","smkcig_prtl", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 33) {
        ApplyAnimation(playerid,"GANGS","smkcig_prtl_F", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animlowrider(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animlowrider [1-39]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 39) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animlowrider [1-39]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"LOWRIDER","F_smklean_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_bdbnce", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_hair", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_hurry", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_idleloop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_idle_to_l0", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l0_bnce", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l0_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l0_to_l1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l12_to_l0", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l1_bnce", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l1_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l1_to_l2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l2_bnce", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l2_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l2_to_l3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l345_to_l1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l3_bnce", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l3_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l3_to_l4", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l4_bnce", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l4_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l4_to_l5", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 24) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l5_bnce", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 25) {
        ApplyAnimation(playerid,"LOWRIDER","lrgirl_l5_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 26) {
        ApplyAnimation(playerid,"LOWRIDER","M_smklean_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 27) {
        ApplyAnimation(playerid,"LOWRIDER","M_smkstnd_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 28) {
        ApplyAnimation(playerid,"LOWRIDER","prtial_gngtlkB", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 29) {
        ApplyAnimation(playerid,"LOWRIDER","prtial_gngtlkC", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 30) {
        ApplyAnimation(playerid,"LOWRIDER","prtial_gngtlkD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 31) {
        ApplyAnimation(playerid,"LOWRIDER","prtial_gngtlkE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 32) {
        ApplyAnimation(playerid,"LOWRIDER","prtial_gngtlkF", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 33) {
        ApplyAnimation(playerid,"LOWRIDER","prtial_gngtlkG", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed ==  34) {
        ApplyAnimation(playerid,"LOWRIDER","prtial_gngtlkH", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 35) {
        ApplyAnimation(playerid,"LOWRIDER","RAP_A_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 36) {
        ApplyAnimation(playerid,"LOWRIDER","RAP_B_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 37) {
        ApplyAnimation(playerid,"LOWRIDER","RAP_C_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 38) {
        ApplyAnimation(playerid,"LOWRIDER","Sit_relaxed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 39) {
        ApplyAnimation(playerid,"LOWRIDER","Tap_hand", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animlookers(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animlookers [1-25]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 25) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animlookers [1-25]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"ON_LOOKERS","lkaround_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"ON_LOOKERS","lkaround_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"ON_LOOKERS","lkaround_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"ON_LOOKERS","lkup_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"ON_LOOKERS","lkup_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"ON_LOOKERS","lkup_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"ON_LOOKERS","lkup_point", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"ON_LOOKERS","panic_cower", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"ON_LOOKERS","panic_hide", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"ON_LOOKERS","panic_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"ON_LOOKERS","panic_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"ON_LOOKERS","panic_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"ON_LOOKERS","panic_point", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"ON_LOOKERS","panic_shout", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"ON_LOOKERS","Pointup_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"ON_LOOKERS","Pointup_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"ON_LOOKERS","Pointup_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"ON_LOOKERS","Pointup_shout", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"ON_LOOKERS","point_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"ON_LOOKERS","point_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"ON_LOOKERS","point_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"ON_LOOKERS","shout_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"ON_LOOKERS","shout_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 24) {
        ApplyAnimation(playerid,"ON_LOOKERS","shout_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 25) {
        ApplyAnimation(playerid,"ON_LOOKERS","shout_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 26) {
        ApplyAnimation(playerid,"ON_LOOKERS","shout_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 27) {
        ApplyAnimation(playerid,"ON_LOOKERS","wave_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 28) {
        ApplyAnimation(playerid,"ON_LOOKERS","wave_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 25) {
        ApplyAnimation(playerid,"ON_LOOKERS","wave_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animcarchat(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcarchat [1-20]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 20) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcarchat [1-20]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"CAR_CHAT","carfone_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"CAR_CHAT","carfone_loopA", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"CAR_CHAT","carfone_loopA_to_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"CAR_CHAT","carfone_loopB", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"CAR_CHAT","carfone_loopB_to_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"CAR_CHAT","carfone_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc1_BR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc1_FL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc1_FR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc2_FL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc3_BR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc3_FL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc3_FR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc4_BL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc4_BR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc4_FL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc4_FR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"CAR_CHAT","car_talkm_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"CAR_CHAT","car_talkm_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"CAR_CHAT","car_talkm_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}

CMD:animcasino(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcasino [1-23]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 23) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcasino [1-23]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"CASINO","cards_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"CASINO","cards_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"CASINO","cards_lose", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"CASINO","cards_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"CASINO","cards_pick_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"CASINO","cards_pick_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"CASINO","cards_raise", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"CASINO","cards_win", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"CASINO","manwinb", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"CASINO","manwind", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"CASINO","Roulette_bet", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"CASINO","Roulette_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"CASINO","Roulette_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"CASINO","Roulette_lose", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"CASINO","Roulette_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"CASINO","Roulette_win", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"CASINO","Slot_bet_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"CASINO","Slot_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"CASINO","Slot_lose_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"CASINO","Slot_Plyr", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"CASINO","Slot_wait", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"CASINO","Slot_win_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"CASINO","wof", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbuddy(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbuddy [1-5]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 5) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbuddy [1-5]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BUDDY","buddy_crouchfire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BUDDY","buddy_crouchreload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BUDDY","buddy_fire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BUDDY","buddy_fire_poor", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BUDDY","buddy_reload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbus(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbus [1-9]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 9) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbus [1-9]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BUS","BUS_close", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BUS","BUS_getin_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BUS","BUS_getin_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BUS","BUS_getout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BUS","BUS_getout_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BUS","BUS_jacked_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BUS","BUS_open", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BUS","BUS_open_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BUS","BUS_pullout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}

CMD:animcar(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcar [1-11]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 11) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcar [1-11]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"CAR","Fixn_Car_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"CAR","Fixn_Car_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"CAR","flag_drop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"CAR","Sit_relaxed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"CAR","Tap_hand", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"CAR","Tyd2car_bump", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"CAR","Tyd2car_high", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"CAR","Tyd2car_low", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"CAR","Tyd2car_med", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"CAR","Tyd2car_TurnL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"CAR","Tyd2car_TurnR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animcarry(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcarry [1-7]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 7) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcarry [1-7]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"CARRY","crry_prtial", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"CARRY","liftup", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"CARRY","liftup05", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"CARRY","liftup105", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"CARRY","putdwn", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"CARRY","putdwn05", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"CARRY","putdwn105", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animintshop(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animintshop [1-8]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 8) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animintshop [1-8]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"INT_SHOP","shop_cashier", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"INT_SHOP","shop_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"INT_SHOP","shop_lookA", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"INT_SHOP","shop_lookB", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"INT_SHOP","shop_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"INT_SHOP","shop_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"INT_SHOP","shop_pay", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"INT_SHOP","shop_shelf", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animjst(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animjst [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animjst [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"JST_BUISNESS","girl_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"JST_BUISNESS","girl_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"JST_BUISNESS","player_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"JST_BUISNESS","smoke_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animkart(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animkart [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animkart [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"KART","KART_getin_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"KART","KART_getin_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"KART","KART_getout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"KART","KART_getout_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animkissing(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animkissing [1-14]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 14) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animkissing [1-14]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"KISSING","BD_GF_Wave", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"KISSING","gfwave2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"KISSING","GF_CarArgue_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"KISSING","GF_CarArgue_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"KISSING","GF_CarSpot", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"KISSING","GF_StreetArgue_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"KISSING","GF_StreetArgue_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"KISSING", "gift_give", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_03", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid, "KISSING", "Playa_Kiss_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid, "KISSING", "Playa_Kiss_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid, "KISSING", "Playa_Kiss_03", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animknife(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animknife [1-14]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 14) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animknife [1-14]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"KNIFE","KILL_Knife_Ped_Damage", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"KNIFE","KILL_Knife_Ped_Die", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"KNIFE","KILL_Knife_Player", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"KNIFE","KILL_Partial", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"KNIFE","knife_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"KNIFE","knife_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"KNIFE","knife_4", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"KNIFE","Knife_G", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"KNIFE","knife_hit_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"KNIFE","knife_hit_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"KNIFE","knife_IDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"KNIFE","knife_hit_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"KNIFE","knife_part", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"KNIFE","WEAPON_knifeidle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animlapdan(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animlapdan [1-6]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 6) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animlapdan [1-6]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"LAPDAN1","LAPDAN_D", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"LAPDAN1","LAPDAN_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"LAPDAN2","LAPDAN_D", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"LAPDAN2","LAPDAN_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"LAPDAN3","LAPDAN_D", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"LAPDAN3","LAPDAN_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animdend(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdend [1-8]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 8) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdend [1-8]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"MD_END","END_SC1_PLY", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"MD_END","END_SC1_RYD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"MD_END","END_SC1_SMO", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"MD_END","END_SC1_SWE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"MD_END","END_SC2_PLY", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"MD_END","END_SC2_RYD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"MD_END","END_SC2_SMO", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"MD_END","END_SC2_SWE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animmedic(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animmedic [1]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 1) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animmedic [1]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"MEDIC","CPR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animmtb(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animmtb [1-18]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 18) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animmtb [1-18]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"MTB","MTB_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"MTB","MTB_bunnyhop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"MTB","MTB_drivebyFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"MTB","MTB_driveby_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"MTB","MTB_driveby_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"MTB","MTB_fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"MTB","MTB_getoffBACK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"MTB","MTB_pushes", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"MTB","MTB_getoffLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"MTB","MTB_getoffRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"MTB","MTB_jumponL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"MTB","MTB_jumponR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"MTB","MTB_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"MTB","MTB_pedal", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"MTB","MTB_Ride", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"MTB","MTB_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"MTB","MTB_sprint", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"MTB","MTB_still", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animmusc(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animmusc [1-17]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 17) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animmusc [1-17]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"MUSCULAR","MscleWalkst_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"MUSCULAR","MscleWalkst_Csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"MUSCULAR","Mscle_rckt_run", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"MUSCULAR","Mscle_rckt_walkst", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"MUSCULAR","Mscle_run_Csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"MUSCULAR","MuscleIdle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"MUSCULAR","MuscleIdle_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"MUSCULAR","MuscleIdle_Csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"MUSCULAR","MuscleIdle_rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"MUSCULAR","MuscleRun", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"MUSCULAR","MuscleRun_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"MUSCULAR","MuscleSprint", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"MUSCULAR","MuscleWalk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"MUSCULAR","MuscleWalkstart", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"MUSCULAR","MuscleWalk_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"MUSCULAR","Musclewalk_Csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"MUSCULAR","Musclewalk_rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animotb(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animotb [1-11]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 11) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animotb [1-11]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"OTB","betslp_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"OTB","betslp_lkabt", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"OTB","betslp_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"OTB","betslp_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"OTB","betslp_tnk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"OTB","wtchrace_cmon", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"OTB","wtchrace_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"OTB","wtchrace_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"OTB","wtchrace_lose", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"OTB","wtchrace_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"OTB","wtchrace_win", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


/*CMD:animnevada(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
        new animationplayed;
        if(sscanf(params, "d", animationplayed)) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animnevada [1-2]");
            return 1;
        }

        if(animationplayed < 1 || animationplayed > 2) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animnevada [1-2]");
            return 1;
        }
        if(animationplayed == 1) {
            ApplyAnimation(playerid,"NEVADA","NEVADA_getin", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 2) {
            ApplyAnimation(playerid,"NEVADA","NEVADA_getout", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        return 1;
    }
    return true;
}*/


CMD:animpark(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        new animationplayed;
        if(sscanf(params, "d", animationplayed)) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpark [1-3]");
            return 1;
        }

        if(animationplayed < 1 || animationplayed > 3) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpark [1-3]");
            return 1;
        }
        if(animationplayed == 1) {
            ApplyAnimation(playerid,"PARK","Tai_Chi_in", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 2) {
            ApplyAnimation(playerid,"PARK","Tai_Chi_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 3) {
            ApplyAnimation(playerid,"PARK","Tai_Chi_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        return 1;
    }
    return true;
}


CMD:animpaulnmac(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpaulnmac [1-12]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 12) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpaulnmac [1-12]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"PAULNMAC","Piss_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"PAULNMAC","Piss_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"PAULNMAC","Piss_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"PAULNMAC","PnM_Argue1_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"PAULNMAC","PnM_Argue1_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"PAULNMAC","PnM_Argue2_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"PAULNMAC","PnM_Argue2_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"PAULNMAC","PnM_Loop_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"PAULNMAC","PnM_Loop_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"PAULNMAC","wank_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"PAULNMAC","wank_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"PAULNMAC","wank_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animsaw(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsaw [1-10]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 12) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsaw [1-10]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"CHAINSAW","CSAW_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"CHAINSAW","CSAW_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"CHAINSAW","CSAW_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"CHAINSAW","CSAW_G", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"CHAINSAW","CSAW_Hit_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"CHAINSAW","CSAW_Hit_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"CHAINSAW","CSAW_Hit_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"CHAINSAW","IDLE_csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"CHAINSAW","WEAPON_csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"CHAINSAW","WEAPON_csawlo", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animchoppa(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animchoppa [1-18]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 18) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animchoppa [1-18]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_bunnyhop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_drivebyFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_driveby_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_driveby_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_getoffBACK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_getoffLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_getoffRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_jumponL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_jumponR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_pedal", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_Pushes", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_ride", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_sprint", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"CHOPPA","CHOPPA_Still", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animclothes(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animclothes [1-13]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 13) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animclothes [1-13]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Buy", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"CLOTHES","CLO_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Pose_Hat", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Pose_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Pose_In_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Pose_Legs", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Pose_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Pose_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Pose_Out_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Pose_Shoes", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Pose_Torso", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"CLOTHES","CLO_Pose_Watch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animcoach(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcoach [1-6]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 6) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcoach [1-6]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"COACH","COACH_inL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"COACH","COACH_inR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"COACH","COACH_opnL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"COACH","COACH_opnR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"COACH","COACH_outL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"COACH","COACH_outR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animcolt(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcolt [1-7]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 7) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcolt [1-7]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"COLT45","2guns_crouchfire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"COLT45","colt45_crouchfire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"COLT45","colt45_crouchreload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"COLT45","colt45_fire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"COLT45","colt45_fire_2hands", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"COLT45","colt45_reload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"COLT45","sawnoff_reload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animcopa(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcopa [1-12]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 12) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcopa[1-12]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"COP_AMBIENT","Copbrowse_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"COP_AMBIENT","Copbrowse_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"COP_AMBIENT","Copbrowse_nod", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"COP_AMBIENT","Copbrowse_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"COP_AMBIENT","Copbrowse_shake", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"COP_AMBIENT","Coplook_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"COP_AMBIENT","Coplook_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"COP_AMBIENT","Coplook_nod", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"COP_AMBIENT","Coplook_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"COP_AMBIENT","Coplook_shake", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"COP_AMBIENT","Coplook_think", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"COP_AMBIENT","Coplook_watch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animcod(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcod [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcod [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"COP_DVBYZ","COP_Dvby_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"COP_DVBYZ","COP_Dvby_FT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"COP_DVBYZ","COP_Dvby_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"COP_DVBYZ","COP_Dvby_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}

CMD:animcrack(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcrack[1-9]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 9) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcrack [1-9]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"CRACK","Bbalbat_Idle_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"CRACK","Bbalbat_Idle_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"CRACK","crckdeth1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"CRACK","crckdeth2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"CRACK","crckdeth3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"CRACK","crckdeth4", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"CRACK","crckidle1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"CRACK","crckidle2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"CRACK","crckidle3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


/*CMD:animsnm(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsnm[1-8]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 24241993) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsnm[1-8]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"SNM","SPANKING_IDLEW", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"SNM","SPANKING_IDLEP", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"SNM","SPANKINGW", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"SNM","SPANKINGP", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"SNM","SPANKEDW", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"SNM","SPANKEDP", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"SNM","SPANKING_ENDW", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"SNM","SPANKING_ENDP", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    if(animationplayed > 8) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsnm[1-8]");
    }
    return 1;
}*/

CMD:animcrib(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcrib [1-5]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 5) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animcrib [1-5]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"CRIB","CRIB_Console_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"CRIB","CRIB_Use_Switch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"CRIB","PED_Console_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"CRIB","PED_Console_Loose", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"CRIB","PED_Console_Win", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animjump(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animjump [1-3]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 3) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animjump [1-3]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"DAM_JUMP","DAM_Dive_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"DAM_JUMP","DAM_Land", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"DAM_JUMP","Jump_Roll", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    /*else if(animationplayed == 3) {
        ApplyAnimation(playerid,"DAM_JUMP","DAM_Launch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"DAM_JUMP","SF_JumpWall", 4.1, false, true, true, true, 1, SYNC_ALL);
    }*/
    return 1;
}


CMD:animdance(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdance [1-13]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 13) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdance [1-13]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"DANCING","bd_clap", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"DANCING","bd_clap1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"DANCING","dance_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"DANCING","DAN_Down_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"DANCING","DAN_Left_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"DANCING","DAN_Loop_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"DANCING","DAN_Right_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"DANCING","DAN_Up_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"DANCING","dnce_M_a", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"DANCING","dnce_M_b", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"DANCING","dnce_M_c", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"DANCING","dnce_M_d", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"DANCING","dnce_M_e", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animblowjob(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animblowjob [1-12]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 13) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animblowjob [1-12]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_COUCH_START_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_COUCH_START_W", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_COUCH_LOOP_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_COUCH_LOOP_W", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_COUCH_END_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_COUCH_END_W", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_STAND_START_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_STAND_START_W", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_STAND_LOOP_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_STAND_LOOP_W", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_STAND_END_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"BLOWJOBZ","BJ_STAND_END_W", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}

CMD:animdealer(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdealer [1-7]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 7) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdealer [1-7]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"DEALER","DEALER_DEAL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"DEALER","DEALER_IDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"DEALER","DEALER_IDLE_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"DEALER","DEALER_IDLE_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"DEALER","DEALER_IDLE_03", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"DEALER","DRUGS_BUY", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"DEALER","shop_pay", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animdildo(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdildo [1-9]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 9) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdildo [1-9]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"DILDO","DILDO_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"DILDO","DILDO_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"DILDO","DILDO_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"DILDO","DILDO_block", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"DILDO","DILDO_G", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"DILDO","DILDO_Hit_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"DILDO","DILDO_Hit_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"DILDO","DILDO_Hit_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"DILDO","DILDO_IDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animdodge(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdodge [1-3]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 3) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdodge [1-3]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"DODGE","Cover_Dive_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"DODGE","Crushed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"DODGE","Crush_Jump", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animdozer(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdozer [1-9]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 9) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdozer [1-9]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"DOZER","DOZER_Align_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"DOZER","DOZER_Align_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"DOZER","DOZER_getin_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"DOZER","DOZER_getin_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"DOZER","DOZER_getout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"DOZER","DOZER_getout_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"DOZER","DOZER_Jacked_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"DOZER","DOZER_Jacked_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"DOZER","DOZER_pullout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animdrivebys(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdrivebys [1-8]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 8) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animdrivebys [1-8]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"DRIVEBYS","Gang_DrivebyLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"DRIVEBYS","Gang_DrivebyLHS_Bwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"DRIVEBYS","Gang_DrivebyLHS_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"DRIVEBYS","Gang_DrivebyRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"DRIVEBYS","Gang_DrivebyRHS_Bwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"DRIVEBYS","Gang_DrivebyRHS_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"DRIVEBYS","Gang_DrivebyTop_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"DRIVEBYS","Gang_DrivebyTop_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animfat(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfat [1-17]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 17) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfat [1-17]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"FAT","FatIdle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 1) {
        ApplyAnimation(playerid,"FAT","FatIdle_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"FAT","FatIdle_Csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"FAT","FatIdle_Rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"FAT","FatRun", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"FAT","FatRun_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"FAT","FatRun_Csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"FAT","FatRun_Rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"FAT","FatSprint", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"FAT","FatWalk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"FAT","FatWalkstart", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"FAT","FatWalkstart_Csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"FAT","FatWalkSt_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"FAT","FatWalkSt_Rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"FAT","FatWalk_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"FAT","FatWalk_Csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"FAT","FatWalk_Rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"FAT","IDLE_tired", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}

CMD:animfightb(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfightb [1-10]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 10) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfightb [1-10]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"FIGHT_B","FightB_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"FIGHT_B","FightB_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"FIGHT_B","FightB_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"FIGHT_B","FightB_block", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"FIGHT_B","FightB_G", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"FIGHT_B","FightB_IDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"FIGHT_B","FightB_M", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"FIGHT_B","HitB_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"FIGHT_B","HitB_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"FIGHT_B","HitB_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animfightc(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfightc [1-12]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 12) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfightc [1-12]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"FIGHT_C","FightC_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"FIGHT_C","FightC_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"FIGHT_C","FightC_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"FIGHT_C","FightC_block", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"FIGHT_C","FightC_blocking", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"FIGHT_C","FightC_G", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"FIGHT_C","FightC_IDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"FIGHT_C","FightC_M", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"FIGHT_C","FightC_Spar", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"FIGHT_C","HitC_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"FIGHT_C","HitC_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"FIGHT_C","HitC_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animfightd(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfightd [1-10]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 10) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfightd [1-10]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"FIGHT_D","FightD_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"FIGHT_D","FightD_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"FIGHT_D","FightD_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"FIGHT_D","FightD_block", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"FIGHT_D","FightD_G", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"FIGHT_D","FightD_IDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"FIGHT_D","FightD_M", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"FIGHT_D","HitD_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"FIGHT_D","HitD_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"FIGHT_D","HitD_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animfighte(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfighte [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfighte [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"FIGHT_E","FightKick", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"FIGHT_E","FightKick_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"FIGHT_E","Hit_fightkick", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"FIGHT_E","Hit_fightkick_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animfinale(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfinale [1-15]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 15) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfinale [1-15]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"FINALE","FIN_Climb_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 1) {
        ApplyAnimation(playerid,"FINALE","FIN_Cop1_ClimbOut2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"FINALE","FIN_Cop1_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"FINALE","FIN_Cop1_Stomp", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"FINALE","FIN_Hang_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"FINALE","FIN_Hang_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"FINALE","FIN_Hang_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"FINALE","FIN_Hang_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"FINALE","FIN_Jump_On", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"FINALE","FIN_Land_Car", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"FINALE","FIN_Land_Die", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"FINALE","FIN_LegsUp", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"FINALE","FIN_LegsUp_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"FINALE","FIN_LegsUp_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"FINALE","FIN_LegsUp_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"FINALE","FIN_Let_Go", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animfinale2(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfinale2 [1-8]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 8) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfinale2 [1-8]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"FINALE2","FIN_Cop1_ClimbOut", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"FINALE2","FIN_Cop1_Fall", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"FINALE2","FIN_Cop1_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"FINALE2","FIN_Cop1_Shot", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"FINALE2","FIN_Cop1_Swing", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"FINALE2","FIN_Cop2_ClimbOut", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"FINALE2","FIN_Switch_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"FINALE2","FIN_Switch_S", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animflamef(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animflamef [1-1]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 1) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animflamef [1-1]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"FLAME","FLAME_fire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animflowers(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        new animationplayed;
        if(sscanf(params, "d", animationplayed)) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animflowers [1-3]");
            return 1;
        }

        if(animationplayed < 1 || animationplayed > 3) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animflowers [1-3]");
            return 1;
        }
        if(animationplayed == 1) {
            ApplyAnimation(playerid,"Flowers","Flower_attack", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 2) {
            ApplyAnimation(playerid,"Flowers","Flower_attack_M", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 3) {
            ApplyAnimation(playerid,"Flowers","Flower_Hit", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        return 1;
    }
    return true;
}


CMD:animghands(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animghands [1-20]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 20) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animghands [1-20]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"GHANDS","gsign1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"GHANDS","gsign1LH", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"GHANDS","gsign2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"GHANDS","gsign2LH", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"GHANDS","gsign3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"GHANDS","gsign3LH", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"GHANDS","gsign4", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"GHANDS","gsign4LH", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"GHANDS","gsign5", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"GHANDS","gsign5LH", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"GHANDS","LHGsign1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"GHANDS","LHGsign2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"GHANDS","LHGsign3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"GHANDS","LHGsign4", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"GHANDS","LHGsign5", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"GHANDS","RHGsign1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"GHANDS","RHGsign2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"GHANDS","RHGsign3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"GHANDS","RHGsign4", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"GHANDS","RHGsign5", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animfw(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfw [1-9]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 9) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animfw [1-9]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"Freeweights","gym_barbell", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"Freeweights","gym_free_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"Freeweights","gym_free_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"Freeweights","gym_free_celebrate", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"Freeweights","gym_free_down", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"Freeweights","gym_free_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"Freeweights","gym_free_pickup", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"Freeweights","gym_free_putdown", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"Freeweights","gym_free_up_smooth", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animghetto(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animghetto [1-7]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 7) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animghetto [1-7]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"GHETTO_DB","GDB_Car2_PLY", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"GHETTO_DB","GDB_Car2_SMO", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"GHETTO_DB","GDB_Car2_SWE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"GHETTO_DB","GDB_Car_PLY", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"GHETTO_DB","GDB_Car_RYD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"GHETTO_DB","GDB_Car_SMO", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"GHETTO_DB","GDB_Car_SWE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animgog(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgog [1-1]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 1) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgog [1-1]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"goggles","goggles_put_on", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animgraffity(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        new animationplayed;
        if(sscanf(params, "d", animationplayed)) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgraffity [1-2]");
            return 1;
        }

        if(animationplayed < 1 || animationplayed > 2) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgraffity [1-2]");
            return 1;
        }
        if(animationplayed == 1) {
            ApplyAnimation(playerid,"GRAFFITI","graffiti_Chkout", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 2) {
            ApplyAnimation(playerid,"GRAFFITI","spraycan_fire", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        return 1;
    }
    return true;
}


CMD:animgreya(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        new animationplayed;
        if(sscanf(params, "d", animationplayed)) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgreya [1-3]");
            return 1;
        }

        if(animationplayed < 1 || animationplayed > 3) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgreya [1-3]");
            return 1;
        }
        if(animationplayed == 1) {
            ApplyAnimation(playerid,"GRAVEYARD","mrnF_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 2) {
            ApplyAnimation(playerid,"GRAVEYARD","mrnM_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 3) {
            ApplyAnimation(playerid,"GRAVEYARD","prst_loopa", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        return 1;
    }
    return true;
}


CMD:animgren(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        new animationplayed;
        if(sscanf(params, "d", animationplayed)) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgren [1-3]");
            return 1;
        }

        if(animationplayed < 1 || animationplayed > 3) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animgren [1-3]");
            return 1;
        }
        if(animationplayed == 1) {
            ApplyAnimation(playerid,"GRENADE","WEAPON_start_throw", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 2) {
            ApplyAnimation(playerid,"GRENADE","WEAPON_throw", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 3) {
            ApplyAnimation(playerid,"GRENADE","WEAPON_throwu", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        return 1;
    }
    return true;
}


CMD:animhaircut(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animhaircut [1-13]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 13) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animhaircut [1-13]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Beard_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Buy", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Cut", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Cut_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Cut_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Hair_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Hair_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Sit_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Sit_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"HAIRCUTS","BRB_Sit_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animheist(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animheist [1-10]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 10) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animheist [1-10]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"HEIST9","CAS_G2_GasKO", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"HEIST9","swt_wllpk_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"HEIST9","swt_wllpk_L_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"HEIST9","swt_wllpk_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"HEIST9","swt_wllpk_R_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"HEIST9","swt_wllshoot_in_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"HEIST9","swt_wllshoot_in_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"HEIST9","swt_wllshoot_out_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"HEIST9","swt_wllshoot_out_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"HEIST9","Use_SwipeCard", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animinthouse(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animinthouse [1-10]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 10) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animinthouse [1-10]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"INT_HOUSE","BED_In_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"INT_HOUSE","BED_In_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"INT_HOUSE","BED_Loop_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"INT_HOUSE","BED_Loop_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"INT_HOUSE","BED_Out_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"INT_HOUSE","BED_Out_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"INT_HOUSE","LOU_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"INT_HOUSE","LOU_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"INT_HOUSE","LOU_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"INT_HOUSE","wash_up", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animintoffice(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animintoffice [1-10]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 10) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animintoffice [1-10]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"INT_OFFICE","FF_Dam_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"INT_OFFICE","OFF_Sit_2Idle_180", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"INT_OFFICE","OFF_Sit_Bored_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"INT_OFFICE","OFF_Sit_Crash", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"INT_OFFICE","OFF_Sit_Drink", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"INT_OFFICE","OFF_Sit_Idle_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"INT_OFFICE","OFF_Sit_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"INT_OFFICE","OFF_Sit_Read", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"INT_OFFICE","OFF_Sit_Type_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"INT_OFFICE","OFF_Sit_Watch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animplayerdbf(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animplayerdbf [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animplayerdbf [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"PLAYER_DVBYS","Plyr_DrivebyBwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"PLAYER_DVBYS","Plyr_DrivebyFwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"PLAYER_DVBYS","Plyr_DrivebyLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"PLAYER_DVBYS","Plyr_DrivebyRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animplayidles(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animplayidles [1-5]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 5) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animplayidles [1-5]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"PLAYIDLES","shift", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"PLAYIDLES","shldr", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"PLAYIDLES","stretch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"PLAYIDLES","strleg", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"PLAYIDLES","time", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animpolice(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpolice [1-10]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 10) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpolice [1-10]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"POLICE","CopTraf_Away", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"POLICE","CopTraf_Come", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"POLICE","CopTraf_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"POLICE","CopTraf_Stop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"POLICE","COP_getoutcar_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"POLICE","Cop_move_FWD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"POLICE","crm_drgbst_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"POLICE","Door_Kick", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"POLICE","plc_drgbst_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"POLICE","plc_drgbst_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animpool(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpool [1-21]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 21) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpool [1-21]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"POOL","POOL_ChalkCue", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"POOL","POOL_Idle_Stance", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"POOL","POOL_Long_Shot", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"POOL","POOL_Long_Shot_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"POOL","POOL_Long_Start", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"POOL","POOL_Long_Start_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"POOL","POOL_Med_Shot", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"POOL","POOL_Med_Shot_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"POOL","POOL_Med_Start", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"POOL","POOL_Med_Start_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"POOL","POOL_Place_White", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"POOL","POOL_Short_Shot", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"POOL","POOL_Short_Shot_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"POOL","POOL_Short_Start", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"POOL","POOL_Short_Start_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"POOL","POOL_Walk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"POOL","POOL_Walk_Start", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"POOL","POOL_XLong_Shot", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"POOL","POOL_XLong_Shot_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"POOL","POOL_XLong_Start", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"POOL","POOL_XLong_Start_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animpoor(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpoor [1-2]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 2) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpoor [1-2]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"POOR","WINWASH_Start", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 1) {
        ApplyAnimation(playerid,"POOR","WINWASH_Wash2Beg", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animpython(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpython [1-5]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 5) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animpython [1-5]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"PYTHON","python_crouchfire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"PYTHON","python_crouchreload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"PYTHON","python_fire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"PYTHON","python_fire_poor", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"PYTHON","python_reload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animquad(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animquad [1-17]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 17) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animquad [1-17]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"QUAD","QUAD_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"QUAD","QUAD_driveby_FT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"QUAD","QUAD_driveby_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"QUAD","QUAD_driveby_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"QUAD","QUAD_FWD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"QUAD","QUAD_getoff_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"QUAD","QUAD_getoff_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"QUAD","QUAD_getoff_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"QUAD","QUAD_geton_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"QUAD","QUAD_geton_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"QUAD","QUAD_hit", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"QUAD","QUAD_kick", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"QUAD","QUAD_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"QUAD","QUAD_passenger", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"QUAD","QUAD_reverse", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"QUAD","QUAD_ride", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"QUAD","QUAD_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animquadbz(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animquadbz [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animquadbz [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"QUAD_DBZ","Pass_Driveby_BWD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"QUAD_DBZ","Pass_Driveby_FWD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"QUAD_DBZ","Pass_Driveby_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"QUAD_DBZ","Pass_Driveby_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animrapping(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animrapping [1-8]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 8) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animrapping [1-8]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"RAPPING","Laugh_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"RAPPING","RAP_A_IN", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"RAPPING","RAP_A_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"RAPPING","RAP_A_OUT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"RAPPING","RAP_B_IN", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"RAPPING","RAP_B_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"RAPPING","RAP_B_OUT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"RAPPING","RAP_C_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animrifle(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animrifle [1-5]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 5) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animrifle [1-5]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"RIFLE","RIFLE_crouchfire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"RIFLE","RIFLE_crouchload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"RIFLE","RIFLE_fire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"RIFLE","RIFLE_fire_poor", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"RIFLE","RIFLE_load", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animriot(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animriot [1-7]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 7) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animriot [1-7]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"RIOT","RIOT_ANGRY", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"RIOT","RIOT_ANGRY_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"RIOT","RIOT_challenge", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"RIOT","RIOT_CHANT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"RIOT","RIOT_FUKU", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"RIOT","RIOT_PUNCHES", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"RIOT","RIOT_shout", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animrobbank(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animrobbank [1-5]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 5) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animrobbank [1-5]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"ROB_BANK","CAT_Safe_End", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"ROB_BANK","CAT_Safe_Open", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"ROB_BANK","CAT_Safe_Open_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"ROB_BANK","CAT_Safe_Rob", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"ROB_BANK","SHP_HandsUp_Scr", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animrocket(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animrocket [1-5]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 5) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animrocket [1-5]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"ROCKET","idle_rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"ROCKET","RocketFire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"ROCKET","run_rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"ROCKET","walk_rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"ROCKET","WALK_start_rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animrustler(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animrustler [1-5]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 5) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animrustler [1-5]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"RUSTLER","Plane_align_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"RUSTLER","Plane_close", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"RUSTLER","Plane_getin", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"RUSTLER","Plane_getout", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"RUSTLER","Plane_open", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animbiked(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbiked [1-18]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 18) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbiked [1-18]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 1) {
        ApplyAnimation(playerid,"BIKED","BIKEd_drivebyFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"BIKED","BIKEd_drivebyLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"BIKED","BIKEd_drivebyRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"BIKED","BIKEd_getoffBACK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"BIKED","BIKEd_getoffLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"BIKED","BIKEd_getoffRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"BIKED","BIKEd_hit", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"BIKED","BIKEd_jumponL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"BIKED","BIKEd_jumponR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"BIKED","BIKEd_kick", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"BIKED","BIKEd_passenger", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"BIKED","BIKEd_pushes", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Ride", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"BIKED","BIKEd_shuffle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"BIKED","BIKEd_Still", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animryder(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animryder [1-14]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 14) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animryder [1-14]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"RYDER","RYD_Beckon_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 1) {
        ApplyAnimation(playerid,"RYDER","RYD_Beckon_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"RYDER","RYD_Beckon_03", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"RYDER","RYD_Die_PT1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"RYDER","RYD_Die_PT2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"RYDER","Van_Crate_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"RYDER","Van_Crate_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"RYDER","Van_Fall_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"RYDER","Van_Fall_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"RYDER","Van_Lean_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"RYDER","Van_Lean_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"RYDER","VAN_PickUp_S", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"RYDER","Van_Stand", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"RYDER","Van_Stand_Crate", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"RYDER","Van_Throw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}

CMD:animscrat(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animscrat [1-12]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 12) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animscrat [1-12]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"SCRATCHING","scdldlp", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"SCRATCHING","scdlulp", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"SCRATCHING","scdrdlp", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"SCRATCHING","scdrulp", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"SCRATCHING","sclng_l", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"SCRATCHING","sclng_r", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"SCRATCHING","scmid_l", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"SCRATCHING","scmid_r", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"SCRATCHING","scshrtl", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"SCRATCHING","scshrtr", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"SCRATCHING","sc_ltor", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"SCRATCHING","sc_rtol", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animshamal(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animshamal [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animshamal [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"SHAMAL","SHAMAL_align", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"SHAMAL","SHAMAL_getin_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"SHAMAL","SHAMAL_getout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"SHAMAL","SHAMAL_open", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animshop(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animshop [1-24]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 24) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animshop [1-24]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"SHOP","ROB_2Idle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"SHOP","ROB_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"SHOP","donutdrop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"SHOP","ROB_Loop_Threat", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"SHOP","ROB_Shifty", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"SHOP","ROB_StickUp_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"SHOP","SHP_Duck_Fire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"SHOP","SHP_Gun_Aim", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"SHOP","SHP_Gun_Duck", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"SHOP","SHP_Gun_Fire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"SHOP","SHP_Gun_Grab", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"SHOP","SHP_Gun_Threat", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"SHOP","SHP_HandsUp_Scr", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"SHOP","SHP_Jump_Glide", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"SHOP","SHP_Jump_Land", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"SHOP","SHP_Jump_Launch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"SHOP","SHP_Rob_GiveCash", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"SHOP","SHP_Rob_HandsUp", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"SHOP","SHP_Rob_React", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"SHOP","SHP_Serve_End", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"SHOP","SHP_Serve_Idle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"SHOP","SHP_Serve_Loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"SHOP","SHP_Serve_Start", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 24) {
        ApplyAnimation(playerid,"SHOP","Smoke_RYD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animshotgun(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        new animationplayed;
        if(sscanf(params, "d", animationplayed)) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animshotgun [1-3]");
            return 1;
        }

        if(animationplayed < 1 || animationplayed > 3) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animshotgun [1-3]");
            return 1;
        }
        if(animationplayed == 1) {
            ApplyAnimation(playerid,"SHOTGUN","shotgun_crouchfire", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 2) {
            ApplyAnimation(playerid,"SHOTGUN","shotgun_fire", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 3) {
            ApplyAnimation(playerid,"SHOTGUN","shotgun_fire_poor", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        return 1;
    }
    return true;
}


CMD:animskate(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        new animationplayed;
        if(sscanf(params, "d", animationplayed)) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animskate [1-3]");
            return 1;
        }

        if(animationplayed < 1 || animationplayed > 3) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animskate [1-3]");
            return 1;
        }
        if(animationplayed == 1) {
            ApplyAnimation(playerid,"SKATE","skate_idle", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 2) {
            ApplyAnimation(playerid,"SKATE","skate_run", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 3) {
            ApplyAnimation(playerid,"SKATE","skate_sprint", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        return 1;
    }
    return true;
}


CMD:animvortex(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animvortex [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animvortex [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"VORTEX","CAR_jumpin_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"VORTEX","CAR_jumpin_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"VORTEX","vortex_getout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"VORTEX","vortex_getout_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animtec(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animtec [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animtec [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"TEC","TEC_crouchfire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"TEC","TEC_crouchreload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"TEC","TEC_fire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"TEC","TEC_reload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animtrain(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animtrain [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animtrain [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"TRAIN","tran_gtup", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"TRAIN","tran_hng", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"TRAIN","tran_ouch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"TRAIN","tran_stmb", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animsil(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsil [1-4]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 4) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsil [1-4]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"SILENCED","CrouchReload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"SILENCED","SilenceCrouchfire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"SILENCED","Silence_fire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"SILENCED","Silence_reload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animtattoo(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animtattoo [1-56]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 56) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animtattoo [1-56]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmL_In_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmL_In_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmL_In_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmL_Out_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"TATTOOS","TA_ArmL_Out_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmL_Out_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmL_Pose_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmL_Pose_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmL_Pose_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmR_In_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmR_In_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmR_In_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmR_Out_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmR_Out_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmR_Out_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmR_Pose_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmR_Pose_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"TATTOOS","TAT_ArmR_Pose_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_In_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_In_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_In_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_Out_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_Out_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 24) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_Out_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 25) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_Pose_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 26) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_Pose_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 27) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_Pose_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 28) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_Sit_In_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 29) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_Sit_Loop_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 30) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Back_Sit_Out_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 31) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Bel_In_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 32) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Bel_In_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 33) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Bel_Out_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed ==  34) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Bel_Out_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 35) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Bel_Pose_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 36) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Bel_Pose_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 37) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Che_In_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 38) {
        ApplyAnimation(playerid,"TATTOOS","Sit_relaxed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 39) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Che_In_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 40) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Che_In_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 41) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Che_Out_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 41) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Che_Out_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 42) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Che_Out_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 43) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Che_Pose_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 44) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Che_Pose_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 45) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Che_Pose_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 46) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Idle_Loop_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 47) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Idle_Loop_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 48) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Sit_In_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 49) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Sit_In_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 50) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Sit_In_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 51) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Sit_Loop_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 52) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Sit_Loop_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 53) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Sit_Loop_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 54) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Sit_Out_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 55) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Sit_Out_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 56) {
        ApplyAnimation(playerid,"TATTOOS","TAT_Sit_Out_T", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animsmoking(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsmoking [1-8]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 8) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsmoking [1-8]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"SMOKING","F_smklean_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"SMOKING","M_smklean_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"SMOKING","M_smkstnd_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"SMOKING","M_smk_drag", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"SMOKING","M_smk_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"SMOKING","M_smk_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"SMOKING","M_smk_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"SMOKING","M_smk_tap", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animsniper(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsniper [1-1]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 1) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsniper [1-1]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"SNIPER","WEAPON_sniper", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animspray(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        new animationplayed;
        if(sscanf(params, "d", animationplayed)) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animspray [1-2]");
            return 1;
        }

        if(animationplayed < 1 || animationplayed > 2) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animspray [1-2]");
            return 1;
        }
        if(animationplayed == 1) {
            ApplyAnimation(playerid,"SPRAYCAN","spraycan_fire", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 2) {
            ApplyAnimation(playerid,"SPRAYCAN","spraycan_full", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        return 1;
    }
    return true;
}


CMD:animstrip(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animstrip [1-20]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 20) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animstrip [1-20]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"STRIP","PLY_CASH", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"STRIP","PUN_CASH", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"STRIP","PUN_HOLLER", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"STRIP","PUN_LOOP", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"STRIP","strip_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"STRIP","strip_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"STRIP","strip_C", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"STRIP","strip_D", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"STRIP","strip_E", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"STRIP","strip_F", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"STRIP","strip_G", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"STRIP","STR_A2B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"STRIP","STR_B2A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"STRIP","STR_B2C", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"STRIP","STR_C1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"STRIP","STR_C2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"STRIP","STR_C2B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"STRIP","STR_Loop_A", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"STRIP","STR_Loop_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"STRIP","STR_Loop_C", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


// CMD:animbath(playerid, params[])
// {
//     new animationplayed;
//     if(sscanf(params, "d", animationplayed)) {
//         SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbath [1-17]");
//         return 1;
//     }

//     if(animationplayed < 1 || animationplayed > 18) {
//         SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animbath [1-17]");
//         return 1;
//     }
//     if(animationplayed == 1) {
//         ApplyAnimation(playerid,"SUNBATHE","batherdown", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 1) {
//         ApplyAnimation(playerid,"SUNBATHE","batherup", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 2) {
//         ApplyAnimation(playerid,"SUNBATHE","Lay_Bac_in", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 3) {
//         ApplyAnimation(playerid,"SUNBATHE","Lay_Bac_out", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 4) {
//         ApplyAnimation(playerid,"SUNBATHE","ParkSit_M_IdleA", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 5) {
//         ApplyAnimation(playerid,"SUNBATHE","ParkSit_M_IdleB", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 6) {
//         ApplyAnimation(playerid,"SUNBATHE","ParkSit_M_IdleC", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 7) {
//         ApplyAnimation(playerid,"SUNBATHE","ParkSit_M_in", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 8) {
//         ApplyAnimation(playerid,"SUNBATHE","ParkSit_M_out", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 9) {
//         ApplyAnimation(playerid,"SUNBATHE","ParkSit_W_idleA", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 10) {
//         ApplyAnimation(playerid,"SUNBATHE","ParkSit_W_idleB", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 11) {
//         ApplyAnimation(playerid,"SUNBATHE","ParkSit_W_idleC", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 12) {
//         ApplyAnimation(playerid,"SUNBATHE","ParkSit_W_in", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 13) {
//         ApplyAnimation(playerid,"SUNBATHE","ParkSit_W_out", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 14) {
//         ApplyAnimation(playerid,"SUNBATHE","SBATHE_F_LieB2Sit", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 15) {
//         ApplyAnimation(playerid,"SUNBATHE","SBATHE_F_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 16) {
//         ApplyAnimation(playerid,"SUNBATHE","SitnWait_in_W", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     else if(animationplayed == 17) {
//         ApplyAnimation(playerid,"SUNBATHE","SitnWait_out_W", 4.1, false, true, true, true, 1, SYNC_ALL);
//     }
//     return 1;
// }

CMD:animsweet(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsweet [1-7]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 7) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsweet [1-7]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"SWEET","ho_ass_slapped", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"SWEET","LaFin_Player", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"SWEET","LaFin_Sweet", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"SWEET","plyr_hndshldr_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"SWEET","sweet_ass_slap", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"SWEET","sweet_hndshldr_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"SWEET","Sweet_injuredloop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animswim(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animswim [1-7]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 7) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animswim [1-7]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"SWIM","Swim_Breast", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"SWIM","SWIM_crawl", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"SWIM","Swim_Dive_Under", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"SWIM","Swim_Glide", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"SWIM","Swim_jumpout", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"SWIM","Swim_Tread", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"SWIM","Swim_Under", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animsword(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsword [1-10]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 10) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animsword [1-10]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"SWORD","sword_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"SWORD","sword_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"SWORD","sword_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"SWORD","sword_4", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"SWORD","sword_block", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"SWORD","Sword_Hit_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"SWORD","Sword_Hit_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"SWORD","Sword_Hit_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"SWORD","sword_IDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"SWORD","sword_part", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animtank(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animtank [1-6]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 6) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animtank [1-6]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"TANK","TANK_align_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"TANK","TANK_close_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"TANK","TANK_doorlocked", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"TANK","TANK_getin_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"TANK","TANK_getout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"TANK","TANK_open_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animtruck(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animtruck [1-17]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 17) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animtruck [1-17]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_ALIGN_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_ALIGN_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_closedoor_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_closedoor_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_close_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_close_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_getin_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_getin_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_getout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_getout_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_jackedLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_jackedRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_open_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_open_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_pullout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_pullout_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"TRUCK","TRUCK_Shuffle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animswat(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}/animswat [1-19]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 19) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}/animswat [1-19]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"SWAT","gnstwall_injurd", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"SWAT","JMP_Wall1m_180", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"SWAT","Rail_fall_crawl", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"SWAT","swt_breach_01", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"SWAT","cards_pick_02", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"SWAT","swt_breach_02", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"SWAT","swt_breach_03", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"SWAT","swt_go", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"SWAT","swt_lkt", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"SWAT","swt_sty", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"SWAT","swt_vnt_sht_in", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"SWAT","swt_wllpk_L", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"SWAT","swt_wllpk_L_back", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"SWAT","swt_wllpk_R", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"SWAT","swt_wllpk_R_back", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"SWAT","swt_wllshoot_in_L", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"SWAT","swt_wllshoot_in_R", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"SWAT","swt_wllshoot_out_L", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"SWAT","swt_wllshoot_out_R", 4.1, false, true, true, true, 0, SYNC_ALL);
    }
    return 1;
}

CMD:animuzi(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animuzi [1-5]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 5) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animuzi [1-5]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"UZI","UZI_crouchfire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"UZI","UZI_crouchreload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"UZI","UZI_fire", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"UZI","UZI_fire_poor", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"UZI","UZI_reload", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animvan(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animvan [1-8]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 8) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animvan [1-8]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"VAN","VAN_close_back_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"VAN","VAN_close_back_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"VAN","VAN_getin_Back_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"VAN","VAN_getin_Back_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"VAN","VAN_getout_back_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"VAN","VAN_getout_back_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"VAN","VAN_open_back_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"VAN","VAN_open_back_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animvending(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animvending [1-6]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 6) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animvending [1-6]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"VENDING","VEND_Drink2_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"VENDING","VEND_Drink_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"VENDING","vend_eat1_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"VENDING","VEND_Eat_P", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"VENDING","VEND_Use", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"VENDING","VEND_Use_pt2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animway(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animway [1-17]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 17) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animway [1-17]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"WAYFARER","WF_Back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 1) {
        ApplyAnimation(playerid,"WAYFARER","WF_drivebyFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"WAYFARER","WF_drivebyLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"WAYFARER","WF_drivebyRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"WAYFARER","WF_Fwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"WAYFARER","WF_getoffBACK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"WAYFARER","WF_getoffLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"WAYFARER","WF_getoffRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"WAYFARER","WF_hit", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"WAYFARER","WF_jumponL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"WAYFARER","WF_jumponR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"WAYFARER","WF_kick", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"WAYFARER","WF_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"WAYFARER","WF_passenger", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"WAYFARER","WF_pushes", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"WAYFARER","WF_Ride", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"WAYFARER","WF_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"WAYFARER","WF_Still", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animweap(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animweap [1-17]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 17) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animweap [1-17]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"WEAPONS","SHP_1H_Lift", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"WEAPONS","SHP_1H_Lift_End", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"WEAPONS","SHP_1H_Ret", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"WEAPONS","SHP_1H_Ret_S", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"WEAPONS","SHP_2H_Lift", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"WEAPONS","SHP_2H_Lift_End", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"WEAPONS","SHP_2H_Ret", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"WEAPONS","SHP_2H_Ret_S", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"WEAPONS","SHP_Ar_Lift", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"WEAPONS","SHP_Ar_Lift_End", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"WEAPONS","SHP_Ar_Ret", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"WEAPONS","SHP_Ar_Ret_S", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"WEAPONS","SHP_G_Lift_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"WEAPONS","SHP_G_Lift_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"WEAPONS","SHP_Tray_In", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"WEAPONS","SHP_Tray_Out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"WEAPONS","SHP_Tray_Pose", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animwuzi(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animwuzi [1-12]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 12) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animwuzi [1-12]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"WUZI","CS_Dead_Guy", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"WUZI","CS_Plyr_pt1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"WUZI","CS_Plyr_pt2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"WUZI","CS_Wuzi_pt1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"WUZI","CS_Wuzi_pt2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"WUZI","Walkstart_Idle_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"WUZI","Wuzi_follow", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"WUZI","Wuzi_Greet_Plyr", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"WUZI","Wuzi_Greet_Wuzi", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"WUZI","Wuzi_grnd_chk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"WUZI","Wuzi_stand_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"WUZI","Wuzi_Walk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}


CMD:animat(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        new animationplayed;
        if(sscanf(params, "d", animationplayed)) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animat [1-3]");
            return 1;
        }

        if(animationplayed < 1 || animationplayed > 3) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animat [1-3]");
            return 1;
        }
        if(animationplayed == 1) {
            ApplyAnimation(playerid,"Attractors","Stepsit_in", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 2) {
            ApplyAnimation(playerid,"Attractors","Stepsit_loop", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        else if(animationplayed == 3) {
            ApplyAnimation(playerid,"Attractors","Stepsit_out", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        return 1;
    }
    return true;
}


CMD:animairport(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        new animationplayed;
        if(sscanf(params, "d", animationplayed)) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animairport [1]");
            return 1;
        }

        if(animationplayed < 1 || animationplayed > 1) {
            SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animairport [1]");
            return 1;
        }
        if(animationplayed == 1) {
            ApplyAnimation(playerid,"AIRPORT","thrw_barl_thrw", 4.1, false, true, true, true, 1, SYNC_ALL);
        }
        return 1;
    }
    return true;
}
CMD:animped(playerid, params[])
{
    new animationplayed;
    if(sscanf(params, "d", animationplayed)) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animped [1-296]");
        return 1;
    }

    if(animationplayed < 1 || animationplayed > 296) {
        SendClientMessage(playerid,0xBBBBBBFF, "{00FFFF} × {BBBBBB}Use: /animped [1-296]");
        return 1;
    }
    if(animationplayed == 1) {
        ApplyAnimation(playerid,"PED","IDLE_CHAT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 2) {
        ApplyAnimation(playerid,"PED","WALK_DRUNK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 3) {
        ApplyAnimation(playerid,"PED","abseil", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 4) {
        ApplyAnimation(playerid,"PED","ARRESTgun", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 5) {
        ApplyAnimation(playerid,"PED","ATM", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 6) {
        ApplyAnimation(playerid,"PED","BIKE_elbowL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 7) {
        ApplyAnimation(playerid,"PED","BIKE_fallR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 8) {
        ApplyAnimation(playerid,"PED","BIKE_fall_off", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 9) {
        ApplyAnimation(playerid,"PED","BIKE_pickupL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 10) {
        ApplyAnimation(playerid,"PED","BIKE_pickupR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 11) {
        ApplyAnimation(playerid,"PED","BIKE_pullupL", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 12) {
        ApplyAnimation(playerid,"PED","BIKE_pullupR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 13) {
        ApplyAnimation(playerid,"PED","bomber", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 14) {
        ApplyAnimation(playerid,"PED","CAR_alignHI_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 15) {
        ApplyAnimation(playerid,"PED","CAR_alignHI_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 16) {
        ApplyAnimation(playerid,"PED","CAR_align_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 17) {
        ApplyAnimation(playerid,"PED","CAR_align_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 18) {
        ApplyAnimation(playerid,"PED","CAR_closedoorL_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 19) {
        ApplyAnimation(playerid,"PED","CAR_closedoorL_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 20) {
        ApplyAnimation(playerid,"PED","CAR_closedoor_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 21) {
        ApplyAnimation(playerid,"PED","CAR_closedoor_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 22) {
        ApplyAnimation(playerid,"PED","CAR_close_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 23) {
        ApplyAnimation(playerid,"PED","CAR_crawloutRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 24) {
        ApplyAnimation(playerid,"PED","CAR_dead_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 25) {
        ApplyAnimation(playerid,"PED","CAR_dead_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 26) {
        ApplyAnimation(playerid,"PED","CAR_doorlocked_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 27) {
        ApplyAnimation(playerid,"PED","CAR_fallout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 28) {
        ApplyAnimation(playerid,"PED","CAR_fallout_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 29) {
        ApplyAnimation(playerid,"PED","CAR_getinL_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 30) {
        ApplyAnimation(playerid,"PED","CAR_getinL_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 31) {
        ApplyAnimation(playerid,"PED","CAR_getin_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 32) {
        ApplyAnimation(playerid,"PED","CAR_getin_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 33) {
        ApplyAnimation(playerid,"PED","CAR_getoutL_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed ==  34) {
        ApplyAnimation(playerid,"PED","CAR_getout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 35) {
        ApplyAnimation(playerid,"PED","CAR_getout_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 36) {
        ApplyAnimation(playerid,"PED","car_hookertalk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 37) {
        ApplyAnimation(playerid,"PED","CAR_jackedLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 38) {
        ApplyAnimation(playerid,"PED","CAR_jackedRHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 39) {
        ApplyAnimation(playerid,"PED","CAR_jumpin_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 40) {
        ApplyAnimation(playerid,"PED","CAR_LB", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 41) {
        ApplyAnimation(playerid,"PED","CAR_LB_pro", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 42) {
        ApplyAnimation(playerid,"PED","CAR_LB_weak", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 43) {
        ApplyAnimation(playerid,"PED","CAR_LjackedLHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 44) {
        ApplyAnimation(playerid,"PED","CAR_Lshuffle_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 45) {
        ApplyAnimation(playerid,"PED","CAR_Lsit", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 46) {
        ApplyAnimation(playerid,"PED","CAR_open_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 47) {
        ApplyAnimation(playerid,"PED","CAR_open_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 49) {
        ApplyAnimation(playerid,"PED","CAR_pulloutL_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 50) {
        ApplyAnimation(playerid,"PED","CAR_pulloutL_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 51) {
        ApplyAnimation(playerid,"PED","CAR_pullout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 52) {
        ApplyAnimation(playerid,"PED","CAR_pullout_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 53) {
        ApplyAnimation(playerid,"PED","CAR_Qjacked", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 54) {
        ApplyAnimation(playerid,"PED","CAR_rolldoor", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 55) {
        ApplyAnimation(playerid,"PED","CAR_rolldoorLO", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 56) {
        ApplyAnimation(playerid,"PED","CAR_rollout_LHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 57) {
        ApplyAnimation(playerid,"PED","CAR_rollout_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 58) {
        ApplyAnimation(playerid,"PED","CAR_shuffle_RHS", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 59) {
        ApplyAnimation(playerid,"PED","CAR_sit", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 60) {
        ApplyAnimation(playerid,"PED","CAR_sitp", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 61) {
        ApplyAnimation(playerid,"PED","CAR_sitpLO", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 62) {
        ApplyAnimation(playerid,"PED","CAR_sit_pro", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 63) {
        ApplyAnimation(playerid,"PED","CAR_sit_weak", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 64) {
        ApplyAnimation(playerid,"PED","CAR_tune_radio", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 65) {
        ApplyAnimation(playerid,"PED","CLIMB_idle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 66) {
        ApplyAnimation(playerid,"PED","CLIMB_jump", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 67) {
        ApplyAnimation(playerid,"PED","CLIMB_jump2fall", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 68) {
        ApplyAnimation(playerid,"PED","CLIMB_jump_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 69) {
        ApplyAnimation(playerid,"PED","CLIMB_Pull", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 70) {
        ApplyAnimation(playerid,"PED","CLIMB_Stand", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 71) {
        ApplyAnimation(playerid,"PED","CLIMB_Stand_finish", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 72) {
        ApplyAnimation(playerid,"PED","cower", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 73) {
        ApplyAnimation(playerid,"PED","Crouch_Roll_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 74) {
        ApplyAnimation(playerid,"PED","Crouch_Roll_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 75) {
        ApplyAnimation(playerid,"PED","DAM_armL_frmBK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 76) {
        ApplyAnimation(playerid,"PED","DAM_armL_frmFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 77) {
        ApplyAnimation(playerid,"PED","DAM_armL_frmLT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 78) {
        ApplyAnimation(playerid,"PED","DAM_armR_frmBK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 79) {
        ApplyAnimation(playerid,"PED","DAM_armR_frmFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 80) {
        ApplyAnimation(playerid,"PED","DAM_armR_frmRT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 81) {
        ApplyAnimation(playerid,"PED","DAM_LegL_frmBK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 82) {
        ApplyAnimation(playerid,"PED","DAM_LegL_frmFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 83) {
        ApplyAnimation(playerid,"PED","DAM_LegL_frmLT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 84) {
        ApplyAnimation(playerid,"PED","DAM_LegR_frmBK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 85) {
        ApplyAnimation(playerid,"PED","DAM_LegR_frmFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 86) {
        ApplyAnimation(playerid,"PED","DAM_LegR_frmRT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 87) {
        ApplyAnimation(playerid,"PED","DAM_stomach_frmBK", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 88) {
        ApplyAnimation(playerid,"PED","DAM_stomach_frmFT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 89) {
        ApplyAnimation(playerid,"PED","DAM_stomach_frmLT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 90) {
        ApplyAnimation(playerid,"PED","DAM_stomach_frmRT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 91) {
        ApplyAnimation(playerid,"PED","DOOR_LHinge_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 92) {
        ApplyAnimation(playerid,"PED","DOOR_RHinge_O", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 93) {
        ApplyAnimation(playerid,"PED","DrivebyL_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 94) {
        ApplyAnimation(playerid,"PED","DrivebyL_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 95) {
        ApplyAnimation(playerid,"PED","Driveby_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 96) {
        ApplyAnimation(playerid,"PED","Driveby_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 97) {
        ApplyAnimation(playerid,"PED","DRIVE_BOAT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 98) {
        ApplyAnimation(playerid,"PED","DRIVE_BOAT_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 99) {
        ApplyAnimation(playerid,"PED","DRIVE_BOAT_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 100) {
        ApplyAnimation(playerid,"PED","DRIVE_BOAT_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 101) {
        ApplyAnimation(playerid,"PED","Drive_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 102) {
        ApplyAnimation(playerid,"PED","Drive_LO_l", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 103) {
        ApplyAnimation(playerid,"PED","Drive_LO_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 104) {
        ApplyAnimation(playerid,"PED","Drive_L_pro", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 105) {
        ApplyAnimation(playerid,"PED","Drive_L_pro_slow", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 106) {
        ApplyAnimation(playerid,"PED","Drive_L_slow", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 107) {
        ApplyAnimation(playerid,"PED","Drive_L_weak", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 108) {
        ApplyAnimation(playerid,"PED","Drive_L_weak_slow", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 109) {
        ApplyAnimation(playerid,"PED","Drive_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 110) {
        ApplyAnimation(playerid,"PED","Drive_R_pro", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 111) {
        ApplyAnimation(playerid,"PED","Drive_R_pro_slow", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 112) {
        ApplyAnimation(playerid,"PED","Drive_R_slow", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 113) {
        ApplyAnimation(playerid,"PED","Drive_R_weak", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 114) {
        ApplyAnimation(playerid,"PED","Drive_R_weak_slow", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 115) {
        ApplyAnimation(playerid,"PED","Drive_truck", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 116) {
        ApplyAnimation(playerid,"PED","DRIVE_truck_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 117) {
        ApplyAnimation(playerid,"PED","DRIVE_truck_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 118) {
        ApplyAnimation(playerid,"PED","DRIVE_truck_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 119) {
        ApplyAnimation(playerid,"PED","Drown", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 120) {
        ApplyAnimation(playerid,"PED","DUCK_cower", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 121) {
        ApplyAnimation(playerid,"PED","endchat_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 122) {
        ApplyAnimation(playerid,"PED","endchat_02", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 123) {
        ApplyAnimation(playerid,"PED","endchat_03", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 124) {
        ApplyAnimation(playerid,"PED","DRIVE_truck_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 125) {
        ApplyAnimation(playerid,"PED","DRIVE_truck_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 126) {
        ApplyAnimation(playerid,"PED","EV_dive", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 127) {
        ApplyAnimation(playerid,"PED","EV_step", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 128) {
        ApplyAnimation(playerid,"PED","facanger", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 129) {
        ApplyAnimation(playerid,"PED","facanger", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 130) {
        ApplyAnimation(playerid,"PED","facgum", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 131) {
        ApplyAnimation(playerid,"PED","facsurp", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 132) {
        ApplyAnimation(playerid,"PED","facsurpm", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 133) {
        ApplyAnimation(playerid,"PED","factalk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 134) {
        ApplyAnimation(playerid,"PED","facurios", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 135) {
        ApplyAnimation(playerid,"PED","FALL_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 136) {
        ApplyAnimation(playerid,"PED","FALL_collapse", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 137) {
        ApplyAnimation(playerid,"PED","FALL_fall", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 138) {
        ApplyAnimation(playerid,"PED","FALL_front", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 139) {
        ApplyAnimation(playerid,"PED","FALL_glide", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 140) {
        ApplyAnimation(playerid,"PED","FALL_land", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 141) {
        ApplyAnimation(playerid,"PED","FALL_skyDive", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 142) {
        ApplyAnimation(playerid,"PED","Fight2Idle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 143) {
        ApplyAnimation(playerid,"PED","FightA_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 144) {
        ApplyAnimation(playerid,"PED","FightA_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 145) {
        ApplyAnimation(playerid,"PED","FightA_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 146) {
        ApplyAnimation(playerid,"PED","FightA_block", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 147) {
        ApplyAnimation(playerid,"PED","FightA_G", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 148) {
        ApplyAnimation(playerid,"PED","FightA_M", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 149) {
        ApplyAnimation(playerid,"PED","FIGHTIDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 150) {
        ApplyAnimation(playerid,"PED","FightShB", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 151) {
        ApplyAnimation(playerid,"PED","FightShF", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 152) {
        ApplyAnimation(playerid,"PED","FightSh_BWD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 153) {
        ApplyAnimation(playerid,"PED","FightSh_FWD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 154) {
        ApplyAnimation(playerid,"PED","FightSh_Left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 155) {
        ApplyAnimation(playerid,"PED","FightSh_Right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 156) {
        ApplyAnimation(playerid,"PED","flee_lkaround_01", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 157) {
        ApplyAnimation(playerid,"PED","FLOOR_hit", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 158) {
        ApplyAnimation(playerid,"PED","FLOOR_hit_f", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 159) {
        ApplyAnimation(playerid,"PED","fucku", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 160) {
        ApplyAnimation(playerid,"PED","gang_gunstand", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 161) {
        ApplyAnimation(playerid,"PED","gas_cwr", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 162) {
        ApplyAnimation(playerid,"PED","getup", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 163) {
        ApplyAnimation(playerid,"PED","getup_front", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 164) {
        ApplyAnimation(playerid,"PED","gum_eat", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 165) {
        ApplyAnimation(playerid,"PED","GunCrouchBwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 166) {
        ApplyAnimation(playerid,"PED","GunCrouchFwd", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 167) {
        ApplyAnimation(playerid,"PED","GunMove_BWD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 168) {
        ApplyAnimation(playerid,"PED","GunMove_FWD", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 169) {
        ApplyAnimation(playerid,"PED","GunMove_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 170) {
        ApplyAnimation(playerid,"PED","GunMove_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 171) {
        ApplyAnimation(playerid,"PED","Gun_2_IDLE", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 172) {
        ApplyAnimation(playerid,"PED","GUN_BUTT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 173) {
        ApplyAnimation(playerid,"PED","GUN_BUTT_crouch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 174) {
        ApplyAnimation(playerid,"PED","Gun_stand", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 175) {
        ApplyAnimation(playerid,"PED","handscower", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 176) {
        ApplyAnimation(playerid,"PED","handsup", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 177) {
        ApplyAnimation(playerid,"PED","HitA_1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 178) {
        ApplyAnimation(playerid,"PED","HitA_2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 179) {
        ApplyAnimation(playerid,"PED","HitA_3", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 180) {
        ApplyAnimation(playerid,"PED","HIT_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 181) {
        ApplyAnimation(playerid,"PED","HIT_behind", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 182) {
        ApplyAnimation(playerid,"PED","HIT_front", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 183) {
        ApplyAnimation(playerid,"PED","HIT_GUN_BUTT", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 184) {
        ApplyAnimation(playerid,"PED","HIT_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 185) {
        ApplyAnimation(playerid,"PED","HIT_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 186) {
        ApplyAnimation(playerid,"PED","HIT_walk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 187) {
        ApplyAnimation(playerid,"PED","HIT_wall", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 188) {
        ApplyAnimation(playerid,"PED","Idlestance_fat", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 189) {
        ApplyAnimation(playerid,"PED","idlestance_old", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 190) {
        ApplyAnimation(playerid,"PED","IDLE_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 191) {
        ApplyAnimation(playerid,"PED","IDLE_chat", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 192) {
        ApplyAnimation(playerid,"PED","IDLE_csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 193) {
        ApplyAnimation(playerid,"PED","Idle_Gang1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 194) {
        ApplyAnimation(playerid,"PED","IDLE_HBHB", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 195) {
        ApplyAnimation(playerid,"PED","IDLE_ROCKET", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 196) {
        ApplyAnimation(playerid,"PED","IDLE_stance", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 197) {
        ApplyAnimation(playerid,"PED","IDLE_taxi", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 198) {
        ApplyAnimation(playerid,"PED","IDLE_tired", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 199) {
        ApplyAnimation(playerid,"PED","Jetpack_Idle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 200) {
        ApplyAnimation(playerid,"PED","JOG_femaleA", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 201) {
        ApplyAnimation(playerid,"PED","JOG_maleA", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 202) {
        ApplyAnimation(playerid,"PED","JUMP_glide", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 203) {
        ApplyAnimation(playerid,"PED","JUMP_land", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 204) {
        ApplyAnimation(playerid,"PED","JUMP_launch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 205) {
        ApplyAnimation(playerid,"PED","JUMP_launch_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 206) {
        ApplyAnimation(playerid,"PED","KART_drive", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 207) {
        ApplyAnimation(playerid,"PED","KART_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 208) {
        ApplyAnimation(playerid,"PED","KART_LB", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 209) {
        ApplyAnimation(playerid,"PED","KART_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 210) {
        ApplyAnimation(playerid,"PED","KD_left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 211) {
        ApplyAnimation(playerid,"PED","KD_right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 212) {
        ApplyAnimation(playerid,"PED","KO_shot_face", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 213) {
        ApplyAnimation(playerid,"PED","KO_shot_front", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 214) {
        ApplyAnimation(playerid,"PED","KO_shot_stom", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 215) {
        ApplyAnimation(playerid,"PED","KO_skid_back", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 216) {
        ApplyAnimation(playerid,"PED","KO_skid_front", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 217) {
        ApplyAnimation(playerid,"PED","KO_spin_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 218) {
        ApplyAnimation(playerid,"PED","KO_spin_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 219) {
        ApplyAnimation(playerid,"PED","pass_Smoke_in_car", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 220) {
        ApplyAnimation(playerid,"PED","phone_in", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 221) {
        ApplyAnimation(playerid,"PED","phone_out", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 222) {
        ApplyAnimation(playerid,"PED","phone_talk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 223) {
        ApplyAnimation(playerid,"PED","Player_Sneak", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 224) {
        ApplyAnimation(playerid,"PED","Player_Sneak_walkstart", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 225) {
        ApplyAnimation(playerid,"PED","roadcross", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 226) {
        ApplyAnimation(playerid,"PED","roadcross_female", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 227) {
        ApplyAnimation(playerid,"PED","roadcross_gang", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 228) {
        ApplyAnimation(playerid,"PED","roadcross_old", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 229) {
        ApplyAnimation(playerid,"PED","run_1armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 230) {
        ApplyAnimation(playerid,"PED","run_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 231) {
        ApplyAnimation(playerid,"PED","run_civi", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 232) {
        ApplyAnimation(playerid,"PED","run_csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 233) {
        ApplyAnimation(playerid,"PED","run_fat", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 234) {
        ApplyAnimation(playerid,"PED","run_fatold", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 235) {
        ApplyAnimation(playerid,"PED","run_gang1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 236) {
        ApplyAnimation(playerid,"PED","run_left", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 237) {
        ApplyAnimation(playerid,"PED","run_old", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 238) {
        ApplyAnimation(playerid,"PED","run_player", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 239) {
        ApplyAnimation(playerid,"PED","run_right", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 240) {
        ApplyAnimation(playerid,"PED","run_rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 241) {
        ApplyAnimation(playerid,"PED","Run_stop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 242) {
        ApplyAnimation(playerid,"PED","Run_stopR", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 243) {
        ApplyAnimation(playerid,"PED","Run_Wuzi", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 244) {
        ApplyAnimation(playerid,"PED","SEAT_down", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 245) {
        ApplyAnimation(playerid, "PED", "SEAT_idle", 4.1, true, false, false, false, 0, SYNC_NONE);
    }
    else if(animationplayed == 246) {
        ApplyAnimation(playerid, "PED", "SEAT_up", 4.0, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 247) {
        ApplyAnimation(playerid,"PED","SHOT_leftP", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 248) {
        ApplyAnimation(playerid,"PED","SHOT_partial", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 249) {
        ApplyAnimation(playerid,"PED","SHOT_partial_B", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 250) {
        ApplyAnimation(playerid,"PED","SHOT_rightP", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 251) {
        ApplyAnimation(playerid,"PED","Shove_Partial", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 252) {
        ApplyAnimation(playerid,"PED","Smoke_in_car", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 253) {
        ApplyAnimation(playerid,"PED","sprint_civi", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 254) {
        ApplyAnimation(playerid,"PED","sprint_panic", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 255) {
        ApplyAnimation(playerid,"PED","Sprint_Wuzi", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 256) {
        ApplyAnimation(playerid,"PED","swat_run", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 257) {
        ApplyAnimation(playerid,"PED","Swim_Tread", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 258) {
        ApplyAnimation(playerid,"PED","Tap_hand", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 259) {
        ApplyAnimation(playerid,"PED","Tap_handP", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 260) {
        ApplyAnimation(playerid,"PED","turn_180", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 261) {
        ApplyAnimation(playerid,"PED","Turn_L", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 262) {
        ApplyAnimation(playerid,"PED","Turn_R", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 263) {
        ApplyAnimation(playerid,"PED","WALK_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 264) {
        ApplyAnimation(playerid,"PED","WALK_civi", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 265) {
        ApplyAnimation(playerid,"PED","WALK_csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 266) {
        ApplyAnimation(playerid,"PED","Walk_DoorPartial", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 267) {
        ApplyAnimation(playerid,"PED","WALK_drunk", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 268) {
        ApplyAnimation(playerid,"PED","WALK_fat", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 269) {
        ApplyAnimation(playerid,"PED","WALK_fatold", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 270) {
        ApplyAnimation(playerid,"PED","WALK_gang1", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 271) {
        ApplyAnimation(playerid,"PED","WALK_gang2", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 272) {
        ApplyAnimation(playerid,"PED","WALK_old", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 273) {
        ApplyAnimation(playerid,"PED","WALK_player", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 274) {
        ApplyAnimation(playerid,"PED","WALK_rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 275) {
        ApplyAnimation(playerid,"PED","WALK_shuffle", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 276) {
        ApplyAnimation(playerid,"PED","WALK_start", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 277) {
        ApplyAnimation(playerid,"PED","WALK_start_armed", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 278) {
        ApplyAnimation(playerid,"PED","WALK_start_csaw", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 279) {
        ApplyAnimation(playerid,"PED","WALK_start_rocket", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 280) {
        ApplyAnimation(playerid,"PED","Walk_Wuzi", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 281) {
        ApplyAnimation(playerid,"PED","WEAPON_crouch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 282) {
        ApplyAnimation(playerid,"PED","woman_idlestance", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 283) {
        ApplyAnimation(playerid,"PED","woman_run", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 284) {
        ApplyAnimation(playerid,"PED","WOMAN_runbusy", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 285) {
        ApplyAnimation(playerid,"PED","WOMAN_runfatold", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 286) {
        ApplyAnimation(playerid,"PED","woman_runpanic", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 287) {
        ApplyAnimation(playerid,"PED","WOMAN_runsexy", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 288) {
        ApplyAnimation(playerid,"PED","WOMAN_walkbusy", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 289) {
        ApplyAnimation(playerid,"PED","WOMAN_walkfatold", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 290) {
        ApplyAnimation(playerid,"PED","WOMAN_walknorm", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 291) {
        ApplyAnimation(playerid,"PED","WOMAN_walkold", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 292) {
        ApplyAnimation(playerid,"PED","WOMAN_walkpro", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 293) {
        ApplyAnimation(playerid,"PED","WOMAN_walksexy", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 294) {
        ApplyAnimation(playerid,"PED","WOMAN_walkshop", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 295) {
        ApplyAnimation(playerid,"PED","XPRESSscratch", 4.1, false, true, true, true, 1, SYNC_ALL);
    }
    else if(animationplayed == 296) {
        ApplyAnimation(playerid, "PED", "SEAT_idle", 4.0, false, true, true, true, 1, SYNC_ALL);
    }
    return 1;
}
