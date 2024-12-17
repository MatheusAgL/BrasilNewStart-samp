#include <YSI_Coding\y_hooks>

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if (dialogid == 90) 
    {
		if (response)
		{
			if(listitem == 0) {
				listContratos(playerid, GetPlayerOrg(playerid));
			}
			else if(listitem == 1) {
				if(GoChase[playerid] == INVALID_PLAYER_ID) 
					return SendClientMessage(playerid, -1, "Você não possui um contrato");

				new string[128];
				MEGAString[0] = EOS;

				format(string, 128, "ID da Organização\tNome da Organização\n");
				strcat(MEGAString,string);

				/*	Los Santos			
					Governamentais                                            */
				format(string, 128, "{337EFF}Governamental\n");
				strcat(MEGAString,string);
				format(string, 128, "{0095FF}07:\t{0095FF}%s\n", GetOrgName(7));
				strcat(MEGAString,string);
				format(string, 128, "{00660C}03:\t{00660C}%s\n", GetOrgName(3));
				strcat(MEGAString,string);
				format(string, 128, "{917662}11:\t{917662}%s\n", GetOrgName(11));
				strcat(MEGAString,string);
				format(string, 128, "{996600}33:\t{996600}%s\n", GetOrgName(33));
				strcat(MEGAString,string);
				format(string, 128, "{FFFF44}16:\t{FFFF44}%s\n", GetOrgName(16));
				strcat(MEGAString,string);
				format(string, 128, "{EDD893}09:\t{EDD893}%s\n", GetOrgName(9));
				strcat(MEGAString,string);
				format(string, 128, "{605DFF}01:\t{605DFF}%s\n", GetOrgName(1));
				strcat(MEGAString,string);
				format(string, 128, "{737373}02:\t{737373}%s\n", GetOrgName(2));
				strcat(MEGAString,string);
				format(string, 128, "{333300}34:\t{333300}%s\n", GetOrgName(34));
				strcat(MEGAString,string);
				format(string, 128, "{3A3939}29:\t{3A3939}%s\n", GetOrgName(29));
				strcat(MEGAString,string);
				/*	Gangues                                            */
				format(string, 128, "{337EFF}Gangsters\n");
				strcat(MEGAString,string);
				format(string, 128, "{2641FE}05:\t{2641FE}%s\n", GetOrgName(5));
				strcat(MEGAString,string);
				format(string, 128, "{00DB1D}14:\t{00DB1D}%s\n", GetOrgName(14));
				strcat(MEGAString,string);
				format(string, 128, "{CB42E3}17:\t{CB42E3}%s\n", GetOrgName(17));
				strcat(MEGAString,string);
				format(string, 128, "{010701}18:\t{010701}%s\n", GetOrgName(18));
				strcat(MEGAString,string);
				format(string, 128, "{61A1AF}10:\t{61A1AF}%s\n", GetOrgName(10));
				strcat(MEGAString,string);
				format(string, 128, "{FF3636}19:\t{FF3636}%s\n", GetOrgName(19));
				strcat(MEGAString,string);
				format(string, 128, "{9ACD32}21:\t{9ACD32}%s\n", GetOrgName(21));
				strcat(MEGAString,string);
				format(string, 128, "{FFFF99}26:\t{FFFF99}%s\n", GetOrgName(26));
				strcat(MEGAString,string);
				/*	Assassinas                                            */
				format(string, 128, "{337EFF}Assassinas\n");
				strcat(MEGAString,string);
				format(string, 128, "{BDBDBD}08:\t{BDBDBD}%s\n", GetOrgName(8));
				strcat(MEGAString,string);
				format(string, 128, "{A4D1FF}22:\t{A4D1FF}%s\n", GetOrgName(22));
				strcat(MEGAString,string);
				/*	Máfias                                       [FALTA 1]     */
				format(string, 128, "{337EFF}Mafiosas\n");
				strcat(MEGAString,string);
				format(string, 128, "{D85300}12:\t{D85300}%s\n", GetOrgName(12));
				strcat(MEGAString,string);
				format(string, 128, "{18C09F}13:\t{18C09F}%s\n", GetOrgName(13));
				strcat(MEGAString,string);
				format(string, 128, "{66CCFF}24:\t{66CCFF}%s\n", GetOrgName(24));
				strcat(MEGAString,string);
				/*	Terroristas                                           */
				format(string, 128, "{337EFF}Terroristas\n");
				strcat(MEGAString,string);
				format(string, 128, "{571E1E}15:\t{571E1E}%s\n", GetOrgName(15));
				strcat(MEGAString,string);
				format(string, 128, "{EE2323}20:\t{EE2323}%s\n", GetOrgName(20));
				strcat(MEGAString,string);
				format(string, 128, "{024566}23:\t{024566}%s\n", GetOrgName(23));
				strcat(MEGAString,string);
				/*	Mercenárias                                           */
				format(string, 128, "{337EFF}Mercenárias\n");
				strcat(MEGAString,string);
				format(string, 128, "{576176}25:\t{576176}%s\n", GetOrgName(25));
				strcat(MEGAString,string);
				format(string, 128, "{A3283D}28:\t{A3283D}%s\n", GetOrgName(28));
				strcat(MEGAString,string);

				strcat(MEGAString,"{FFFFFF}» Retirar disfarce");
				ShowPlayerDialog(playerid, 5874, DIALOG_STYLE_TABLIST_HEADERS, "Disfarces de Organizações", MEGAString, "Disfarçar", "Sair");
			}
			else if(listitem == 2) {
				callcmd::meucontrato(playerid);
			}
			else if(listitem == 3) {
				callcmd::largarcontrato(playerid, #);
			}
			else if(listitem == 4) {
				callcmd::secreto(playerid);
			}
		}
	}
    return 1;
}

stock listContratos(playerid, orgid) {

	MEGAString[0] = EOS;

	new
	    contratoString[128],
	    contratoListitem = 0;

	strcat(MEGAString, "Id/Nome\tValor\tRespeitos\tInterior\n");

	foreach(new x : Player) {

		if (orgid == 8) {
			if (PlayerInfo[x][pHeadValue] > 0 && !GotHit[x] && GetPlayerInterior(x) == 0 && !Staff_GetWorking(x)) {

				List_SetPlayers(playerid, contratoListitem, x);

                format(contratoString, sizeof contratoString, "%d %s\t{00AA00}$%s\t{ECD563}%d\t{E37E7E}não\n", x, PlayerName[x], getFormatText(PlayerInfo[x][pHeadValue]), PlayerInfo[x][pHeadRespect]);
                strcat(MEGAString, contratoString);

                contratoListitem ++;
			}
			else if (PlayerInfo[x][pHeadValue] > 0 && !GotHit[x] && GetPlayerInterior(x) != 0 && !Staff_GetWorking(x)) {

				List_SetPlayers(playerid, contratoListitem, x);

                format(contratoString, sizeof contratoString, "%d %s\t{00AA00}$%s\t{ECD563}%d\t{82E789}sim\n", x, PlayerName[x], getFormatText(PlayerInfo[x][pHeadValue]), PlayerInfo[x][pHeadRespect]);
                strcat(MEGAString, contratoString);

                contratoListitem ++;
			}
		} else {

			if (PlayerInfo[x][pHeadValueT] > 0 && !GotTri[x] && GetPlayerInterior(x) == 0 && !Staff_GetWorking(x)) {

				List_SetPlayers(playerid, contratoListitem, x);

                format(contratoString, sizeof contratoString, "%d %s\t{00AA00}$%s\t{ECD563}%d\t{E37E7E}não\n", x, PlayerName[x], getFormatText(PlayerInfo[x][pHeadValueT]), PlayerInfo[x][pHeadRespectT]);
                strcat(MEGAString, contratoString);

                contratoListitem ++;
			}
			else if (PlayerInfo[x][pHeadValueT] > 0 && !GotTri[x] && GetPlayerInterior(x) != 0 && !Staff_GetWorking(x)) {

				List_SetPlayers(playerid, contratoListitem, x);

                format(contratoString, sizeof contratoString, "%d %s\t{00AA00}$%s\t{ECD563}%d\t{82E789}sim\n", x, PlayerName[x], getFormatText(PlayerInfo[x][pHeadValueT]), PlayerInfo[x][pHeadRespectT]);
                strcat(MEGAString, contratoString);

                contratoListitem ++;
			}
		}

		if (contratoListitem > 30) break;
	}

	if (!contratoListitem) {
		return SendClientMessage(playerid, -1, "Não há contratos disponíveis.");
	}

	ShowPlayerDialog(playerid, 8472, DIALOG_STYLE_TABLIST_HEADERS, "Contratos da agência", MEGAString, "Pegar", "Fechar");

	return 1;
}

stock SearchingHit(playerid)
{
    new
		string[100],
		searchhit = 0
	;

    foreach(new i : Player)
	{
        if(searchhit == 0)
		{
            if(PlayerInfo[i][pHeadValue] > 0 && GotHit[i] == 0)
			{
				searchhit = 1, hitfound = 1, hitmanid = i;
     			SendMembersMessage(8, -1, "------------------------------- (Agência Hitmans) -------------------------------");
                format(string, sizeof(string), "| Está disponível um novo contrato em: %s[%d] (valor $%s e %d respeitos)", PlayerName[i], i, getFormatText(PlayerInfo[i][pHeadValue]), PlayerInfo[i][pHeadRespect]);
                SendMembersMessage(8, COLOR_DBLUE, string);
                SendMembersMessage(8, -1, "---------------------------------------------------------------------------------");
				return true;
			}
        }
    }
    if(searchhit == 0) SendClientMessage(playerid, 0xFF0000AA, "Não há contratos disponíveis no momento.");

    return false;
}

stock SearchingTri(playerid)
{
	new
		string[100],
		searchTri = 0
	;

    foreach(new i : Player)
	{
        if(searchTri == 0)
		{
            if(PlayerInfo[i][pHeadValueT] > 0 && GotTri[i] == 0)
			{
				searchTri = 1, trifound = 1, triid = i;

                SendMembersMessage(22, -1, "------------------------------- (Agência Triads) -------------------------------");
                format(string, sizeof(string), "| Está disponível um novo contrato em: %s[%d] (valor $%s e %d respeitos)", PlayerName[i], i, getFormatText(PlayerInfo[i][pHeadValueT]), PlayerInfo[i][pHeadRespectT]);
                SendMembersMessage(22, COLOR_DBLUE, string);
                SendMembersMessage(22, -1, "---------------------------------------------------------------------------------");

                return false;
            }
        }
    }
    if(searchTri == 0) SendClientMessage(playerid, -1, "Não há contratos disponiveis!");

    return false;
}