#if defined _inc_speakers_system
	#endinput
#endif
#define _inc_speakers_system true

#include <YSI_Coding\y_hooks>

#include <speaker_entry>
#include <speaker_cmds>

hook OnPlayerResetVars(playerid) 
{
    Speaker_SetNivel(playerid, SPEAKER_NONE);
    Speaker_SetTender(playerid, false);
    return 1;
}

stock Radio_DialogAskMusic(playerid)
{
    inline D_AskMusic(did, ddialogid, dresponse, dlistitem, string:dtext[])
    {
        #pragma unused did, ddialogid, dlistitem

        if (!dresponse)
            return 1;

        if (!strlen(dtext))
            return SendClientMessage(playerid, -1, "Digite ' nome do artista - música '.");

        if (strlen(dtext) < 20 || strlen(dtext) > 50)
            return SendClientMessage(playerid, -1, "Você precisa digitar entre 20 á 50 caracteres.");

        new musics = Iter_Free(IterRadioOrders);
        if (musics == INVALID_ITERATOR_SLOT)
            return SendClientMessage(playerid, -1, "Os pedidos estão lotados, aguarde os locutores atender á todos!");

        Iter_Add(IterRadioOrders, musics);
        RadioOrders_SetTime(musics, gettime());
        RadioOrders_SetNick(musics, PlayerName[playerid]);
        RadioOrders_SetMusic(musics, dtext);

        SendMsgF(playerid, COLOR_LIGHTBLUE, "Você fez um pedido de música: "C_SPEAKER"%s", dtext);

        new string[128];
        format(string, sizeof(string), "o< (( Novo pedido de música ' %s ', use /pedidos ))", dtext);
        Speaker_ChatToAll(COLOR_SPEAKER, string);

        return 1;
    }
    Dialog_ShowCallback(playerid, using inline D_AskMusic, DIALOG_STYLE_INPUT, ""C_GRAY"Pedindo uma musica...", 
    ""C_WHITE"Envie um pedido de musica para que a "C_SPEAKER"EQUIPE RÁDIO "C_WHITE"possa tocar!\n\
	"C_YELLOW"EXEMPLO: Guns n' roses - Don't Cry\n\n\
	"C_GRAY"Digite abaixo:", "Enviar", "Cancelar");

	return 1;
}

stock RadioOrders_List(playerid)
{
    if (Speaker_GetNivel(playerid) < ESTAGIARIO_RADIO)
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	MEGAString[0] = EOS;
	strcat(MEGAString, "nick\ttempo do pedido\tmusica\n");
	
    new string[128],
        tempopedido,
        count;

	foreach(new order : IterRadioOrders) {
        tempopedido = gettime() - RadioOrders_GetTime(order);

	    format(string, sizeof string, "%s\t%s\t%s\n", RadioOrders_GetNick(order), ConvertTime(tempopedido), RadioOrders_GetMusic(order));
        strcat(MEGAString, string);

        List_SetPlayers(playerid, count, order);
        count++;
	}
    inline D_RadioOrdersList(did, ddialogid, dresponse, dlistitem, string:dtext[])
    {
        #pragma unused did, ddialogid, dtext

        if (!dresponse)
            return 1;

        new order = List_GetPlayers(playerid, dlistitem);

        if (!Iter_Contains(IterRadioOrders, order))
            return SendClientMessage(playerid, -1, "Esse pedido da rádio já foi concluido.");

        Iter_Remove(IterRadioOrders, order);
        SendMsgF(playerid, COLOR_LIGHTBLUE, "Você marcou como concluido a música: "C_SPEAKER"%s", RadioOrders_GetMusic(order));
  
        return RadioOrders_List(playerid);
    }
    format(string, sizeof(string), "Últimos pedidos: "C_YELLOW"%d", count);
    Dialog_ShowCallback(playerid, using inline D_RadioOrdersList, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Concluir", "Fechar");
	return 1;
}

stock Speaker_List(playerid, type=0)
{
	MEGAString[0] = EOS;
	strcat(MEGAString, "nick\tcargo\tultimo login\n");

    new string[128];
    inline const OnLoadSpeakers() {
		new cargo,
            player,
            playername[MAX_PLAYER_NAME],
            ultimo_login[35],
            count;

		MySQL_BindResultInt(stmt_selectPlayersGroup, 0, cargo);
		MySQL_BindResultInt(stmt_selectPlayersGroup, 1, player);
		MySQL_BindResult(stmt_selectPlayersGroup, 2, playername);
		MySQL_BindResult(stmt_selectPlayersGroup, 3, ultimo_login);

		while (MySQL_Statement_FetchRow(stmt_selectPlayersGroup)) {
			format(string, sizeof(string), ""C_SPEAKER"%s\t"C_WHITE"%s\t"C_GRAY"%s\n", playername, Speaker_GetPositionName(SpeakerNivel:cargo), ultimo_login);
            strcat(MEGAString, string);

            List_SetPlayers(playerid, count, player);
            count++;
		}

        if (type == 0) {
            ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Informações da equipe da rádio:", MEGAString, "Fechar", #);
        } else {
            inline D_SpeakerDismiss(did, ddialogid, dresponse, dlistitem, string:dtext[])
            {
                #pragma unused did, ddialogid, dtext

                if (!dresponse)
                    return 1;

                if (dlistitem == -1)
                    return 1;

                new id = List_GetPlayers(playerid, dlistitem),
                    idplayer = GetPlayerID(Player_GetNicknameByID(id));

                if (Player_Logado(idplayer)) {
                    Speaker_SetNivel(idplayer, SPEAKER_NONE);
                    Speaker_SetTender(idplayer, false);

                    SendMsgF(idplayer, COLOR_LIGHTRED, "Você foi retirado da equipe da rádio por: %s.", PlayerName[playerid]);
                }
                Group_Dismiss(id, GROUP_SPEAKER);

                SendMsgF(playerid, COLOR_LIGHTBLUE, "Você limpou a vaga de %s da equipe rádio.", Player_GetNicknameByID(id));
                format(string, sizeof(string), "[EQUIPE RÁDIO]: %s limpou a vaga de %s.", PlayerName[playerid], Player_GetNicknameByID(id));
                server_log("locutores", string);

                return Speaker_List(playerid, 1);
            }
            Dialog_ShowCallback(playerid, using inline D_SpeakerDismiss, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Selecione uma vaga para limpar:", MEGAString, "Limpar", "Cancelar");
        }
	}
	MySQL_BindInt(stmt_selectPlayersGroup, 0, _:GROUP_SPEAKER);
	MySQL_ExecuteThreaded_Inline(stmt_selectPlayersGroup, using inline OnLoadSpeakers);

	return 1;
}