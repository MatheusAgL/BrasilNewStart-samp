#include <YSI_Coding\y_hooks>

#define			COLOR_PLAYER_TITLE		0xFFA500FF
#define			C_PLAYER_TITLE			"{FFA500}"

static Text3D:playerTitle[MAX_PLAYERS];

stock PlayerTitle_Set(playerid, const title_name[])
	format(PlayerInfo[playerid][pTituloText], 64, title_name);

stock PlayerTitle_Get(playerid)
{
	new title_name[64];
	format(title_name, sizeof(title_name), PlayerInfo[playerid][pTituloText]);
	return title_name;
}

stock PlayerTitle_Update(playerid) 
{
    new title_name[64];
	format(title_name, sizeof(title_name), PlayerTitle_Get(playerid));

	if (strlen(title_name))
		format(title_name, sizeof(title_name), "%s\n%s\n\n", IsConnectedVoIP(playerid) ? (""C_GREEN"VoIP [ON]") : (""C_RED"VoIP [OFF]"), title_name);
	else
		format(title_name, sizeof(title_name), "%s\n\n", IsConnectedVoIP(playerid) ? (""C_GREEN"VoIP [ON]") : (""C_RED"VoIP [OFF]"));

    if (!IsValidDynamic3DTextLabel(playerTitle[playerid]))
        playerTitle[playerid] = CreateDynamic3DTextLabel(title_name, COLOR_PLAYER_TITLE, 0.00, 0.00, 0.50, 2.5, playerid);
    else
        UpdateDynamic3DTextLabelText(playerTitle[playerid], COLOR_PLAYER_TITLE, title_name);
}

hook OnPlayerLogin(playerid) {
    PlayerTitle_Update(playerid);
	return 1;
}

hook OnPlayerResetVars(playerid) {
	if (IsValidDynamic3DTextLabel(playerTitle[playerid])) {
		DestroyDynamic3DTextLabel(playerTitle[playerid]);
		playerTitle[playerid] = Text3D:INVALID_3DTEXT_ID;
	}
}

CMD:titulos(playerid) 
{
	MEGAString[0] = EOS;
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_RED"REMOVER\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_DEV".:: EQUIPE DEV ::.\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_ADMIN".:: EQUIPE STAFF ::.\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_SPEAKER".:: EQUIPE RADIO ::.\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_YOUTUBER".:: YOUTUBER ::.\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_GRAY"- CARGO DA FAC -\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_GRAY"- NOME DA FAMILIA -\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_GRAY"~~| TOP Cash |~~\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_GRAY"~~| TOP Ouros |~~\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_GRAY"~~| TOP Kills |~~\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_GRAY"<| NIVEL DE SOCIO |>\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_GRAY"$$$ TRILIONARIO $$$\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_GRAY"$$ BILIONARIO $$\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_GRAY"$ MILIONARIO $\n");
	strcat(MEGAString, ""C_BURNED_YELLOW"Titulo » "C_GRAY"PERSONALIZAR\n");

	inline D_PlayerUseTitle(did, ddialogid, dresponse, dlistitem, string:dtext[])
	{
		#pragma unused did, ddialogid, dtext
		if (!dresponse)
			return 1;

		new title[64];

		switch(dlistitem) 
		{
			case 0: {
				PlayerTitle_Set(playerid, "");
				SendClientMessage(playerid, COLOR_PLAYER_TITLE, "Voce removeu seu titulo.");
				return 1;
			}
			case 1:
			{
				if (!Dev_GetNivel(playerid))
					return SendClientMessage(playerid, -1, "Você não faz parte da 'Equipe de Desevolvimento'.");

				title = ""C_DEV".:: EQUIPE DEV ::.";
			}
			case 2:
			{
				if (!Admin_GetNivel(playerid) && !Helper_GetNivel(playerid)) 
					return SendClientMessage(playerid, -1, "Você não faz parte da 'Equipe Staff'.");

				format(title, sizeof(title), "%s.:: %s ::.", Admin_GetNivel(playerid) ? C_ADMIN : C_HELPER, Staff_GetPositionName(playerid));
			}
			case 3:
			{
				new SpeakerNivel:speaker_nivel = Speaker_GetNivel(playerid);
				if (!speaker_nivel) 
					return SendClientMessage(playerid, -1, "Você não faz parte da 'Equipe Radio'.");

				format(title, sizeof(title), ""C_SPEAKER".:: %s ::.", Speaker_GetPositionName(speaker_nivel));
			}
			case 4:
			{
				new YoutuberNivel:youtuber_nivel = Youtuber_GetNivel(playerid);
				if (!youtuber_nivel) 
					return SendClientMessage(playerid, -1, "Você não é um 'Youtuber'.");

				format(title, sizeof(title), ""C_YOUTUBER".:: %s ::.", Youtuber_GetPositionName(youtuber_nivel));
			}
			case 5:
			{
				new org = GetPlayerOrg(playerid);
				if (!org)
					return SendClientMessage(playerid, -1, "Você não faz parte de uma organização/facção.");

				format(title, sizeof(title), "{%s}- %s -", GetOrgColor(org), GetPlayerCargo(playerid));
			}
			case 6:
			{
				if (GetPlayerFamily(playerid) == -1)
					return SendClientMessage(playerid, -1, "Você não faz parte de uma familia.");

				format(title, sizeof(title), ""C_CYAN"- %s -", GetPlayerFamilyName(playerid));
			}
			case 7:
			{
				// if (PlayerInfo[playerid][pConnectTime] <= 400)
				return SendClientMessage(playerid, -1, "Você precisa ser o TOP 1 de Cash.");
				// format(title, sizeof(title), ""C_CYAN"- %s -", GetPlayerFamilyName(playerid));
			}
			case 8:
			{
				// if (PlayerInfo[playerid][pConnectTime] <= 400)
				return SendClientMessage(playerid, -1, "Você precisa ser o TOP 1 de Ouros.");
				// format(title, sizeof(title), ""C_CYAN"- %s -", GetPlayerFamilyName(playerid));
			}
			case 9:
			{
				// if (PlayerInfo[playerid][pConnectTime] <= 400)
				return SendClientMessage(playerid, -1, "Você precisa ser o TOP 1 de Kills.");
				// format(title, sizeof(title), ""C_CYAN"- %s -", GetPlayerFamilyName(playerid));
			}
			case 10:
			{
				if (!Player_GetVIP(playerid))
					return SendClientMessage(playerid, -1, "Você não é um jogador Sócio.");

				new vip_nivel = Player_GetVIP(playerid);
				format(title, sizeof(title), "{%s}<| %s |>", GetVipColor(playerid), VIP_GetName(vip_nivel));
			}
			case 11:
			{
				if (((Player_GetMoney(playerid) / 100000) + (Player_GetMoneyBank(playerid) / 100000) + Player_GetOuros(playerid)) <= 100000)
					return SendClientMessage(playerid, -1, "Você precisa ter $1.000.000.000.000 equivalente a 100.000 ouros (juntando mão, banco e ouros).");

				title = ""C_YELLOW"$$$ TRILIONARIO $$$";
			}
			case 12:
			{
				if (((Player_GetMoney(playerid) / 100000) + (Player_GetMoneyBank(playerid) / 100000) + Player_GetOuros(playerid)) <= 10000)
					return SendClientMessage(playerid, -1, "Você precisa ter $1.000.000.000 equivalente a 10.000 ouros (juntando mão, banco e ouros).");

				title = ""C_YELLOW"$$ BILIONARIO $$";
			}
			case 13:
			{
				if (((Player_GetMoney(playerid) / 100000) + (Player_GetMoneyBank(playerid) / 100000) + Player_GetOuros(playerid)) <= 1000)
					return SendClientMessage(playerid, -1, "Você precisa ter $1.000.000 equivalente a 1.000 ouros (juntando mão, banco e ouros).");

				title = ""C_YELLOW"$ MILIONARIO $";
			}
			case 14:
			{
				new string[128];
				MEGAString[0] = EOS;
		
				format(string, sizeof(string), "Voce esta personalizando seu atual titulo: %s\n", PlayerTitle_Get(playerid));
				strcat(MEGAString, string);
				strcat(MEGAString, "Voce pode usar codigos HTML para definir uma cor para seu titulo:\n\n\
									"C_YELLOW"	- Exemplos: \n\
									"C_RED"{ FF0000 }		VERMELHO\n\
									"C_GREEN"{ 00FF00 }		VERDE\n\
									"C_WHITE"{ FFFFFF }		BRANCO\n\
									"C_CYAN"{ 00BFFF }		CIANO\n\
									"C_YELLOW"{ FFF000 }		AMARELO\n\n\
									"C_RED"Observacao: "C_WHITE"Voce deve remover os espacos para usar a cor, digite seu titulo personalizado abaixo:");

				inline D_PlayerPersonalizeTitle(dsid, dsdialogid, dsresponse, dslistitem, string:dstext[])
				{
					#pragma unused dsid, dsdialogid, dslistitem
					if (!dsresponse)
						return 1;

					if (Player_GetVIP(playerid) < SOCIO_SUPREME)
						return SendClientMessage(playerid, -1, "Você precisa ser Sócio Supreme+ para personalizar seu titulo.");

					if (strlen(dstext) < 5 || strlen(dstext) > sizeof(title)) 
						return SendClientMessage(playerid, COLOR_GREY, "Voce deve digitar um titulo entre 5 a 64 caracteres.");

					format(title, sizeof(title), dstext);
				}
				Dialog_ShowCallback(playerid, using inline D_PlayerPersonalizeTitle, DIALOG_STYLE_INPUT, ""C_GRAY"Personalize seu titulo:", MEGAString, "Confirmar", "Fechar");
			}
		}
		PlayerTitle_Set(playerid, title);
		PlayerTitle_Update(playerid);
		SendClientMessage(playerid, COLOR_PLAYER_TITLE, "Você mudou seu titulo para '' %s ''.", title);
		return 1;
	}
	Dialog_ShowCallback(playerid, using inline D_PlayerUseTitle, DIALOG_STYLE_LIST, ""C_GRAY"Selecione um titulo:", MEGAString, "Usar", "Fechar");
	return 1;
}