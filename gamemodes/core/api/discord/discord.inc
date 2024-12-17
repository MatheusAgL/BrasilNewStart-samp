#include <YSI_Coding\y_hooks>

#include <discord_entry>            // Módulo configurações
#include <discord-connector>        // Discord Connector
#include <discord-cmd>              // Command processor
#include <discord_textdraws>        // Textdraws do módulo

stock Discord_SendMessage(const message[], DCC_Channel:channel)
{
    new message_utf8[1000];
    utf8encode(message_utf8, message, sizeof(message_utf8));
    DCC_SendChannelMessage(channel, message_utf8);
    return 1;
}

hook OnDiscordLink(playerid)
{
    Login_Hidescreen(playerid);

    new DCC_User:user = DCC_FindUserById(Player_GetDiscordUser(playerid));

    if (user != DCC_INVALID_USER) {
        CallLocalFunction("OnPlayerLogin", "i", playerid);
        return 1;
    }
    TogglePlayerSpectating(playerid, true);
    TogglePlayerControllable(playerid, true);

    DiscordLink_ShowTextDraws(playerid);
    SelectTextDraw(playerid, COLOR_DISCORD);
    return 1;
}

hook OnClickDynamicTextDraw(playerid, Text:textid)
{
    if (textid == td_discord_link[4])
    {
        new const query_selectDiscordID[] = 
		    "SELECT discord FROM `player` WHERE `id` = ?";

        new Statement:stmt_selectDiscordID = MySQL_PrepareStatement(MySQL_Handle, query_selectDiscordID);

        inline const OnDbSelect_DiscordID() {
			new user[36];
			MySQL_BindResult(stmt_selectDiscordID, 0, user);

			if (MySQL_Statement_FetchRow(stmt_selectDiscordID)) {
                new DCC_User:userid = DCC_FindUserById(user);

                if (userid == DCC_INVALID_USER) {
                    SendClientMessage(playerid, COLOR_DISCORD, "DISCORD: "C_WHITE"Você não foi vinculado, acesse a sala 'vincular-discord' e acesse a conta do jogo por lá!");
                } else {
                    Player_SetDiscordUser(playerid, user);
                    SendClientMessage(playerid, COLOR_DISCORD, "DISCORD: "C_WHITE"Você foi vinculado com "C_GREEN"SUCESSO"C_WHITE"!!");

                    DiscordLink_HideTextDraws(playerid);
                    CancelSelectTextDraw(playerid);
                    CallLocalFunction("OnPlayerLogin", "i", playerid);
                }
            }
            MySQL_StatementClose(stmt_selectDiscordID);
		}
		MySQL_BindInt(stmt_selectDiscordID, 0, Player_GetAccountID(playerid));
		MySQL_ExecuteThreaded_Inline(stmt_selectDiscordID, using inline OnDbSelect_DiscordID);
    }
    return 1;
}

CALLBACK: Discord_SendEmbed(DCC_Embed: embed, DCC_Channel: channel, const message[] = "", const embed_title[] = SERVER_NAME, const thumbnail_img[] = SERVER_LOGO_URL, const embed_url[] = SERVER_SITE, const embed_img[] = "", embed_color = SERVER_EMBED_COLOR, const footer_img[] = SERVER_LOGO_URL) 
{
    #pragma unused embed_img

    embed = DCC_CreateEmbed();
    DCC_SetEmbedColor(embed, embed_color);
    DCC_SetEmbedTitle(embed, embed_title);
    DCC_SetEmbedUrl(embed, embed_url);
    DCC_SetEmbedFooter(embed, "Copyright of Start Group. All rights reserved.", footer_img);
    DCC_SetEmbedThumbnail(embed, thumbnail_img);

    new message_utf8[300];
    utf8encode(message_utf8, message);
    DCC_SetEmbedDescription(embed, message_utf8);

    DCC_SendChannelEmbedMessage(channel, embed, "");
}

stock DCC_SendEmbed(DCC_Embed: embed) {

    new message[300];
    if (embed == Embed_Online) 
    {
        new players = Iter_Count(Player),
            player_average = Daily_GetPlayerAverage();

        format(message, sizeof(message), "Veja os status do servidor em tempo real.\n\n \
                            > **STATUS**\n\
                            ```\
                            Online\
                            ```\
                            \n> **JOGADORES**\n\
                            ```\
                            %d/%d\
                            ```\
                            \n> **MÉDIA DIÁRIA**\n\
                            ```\
                            %d\
                            ```\
                            \n> **IP DO SERVIDOR**\n\
                            ```\
                            "SERVER_IP":"SERVER_PORTA"\
                            ```", players, MAX_PLAYERS, player_average);

        if (Message_EmbedOnline != DCC_Message:0)
            DCC_DeleteMessage(Message_EmbedOnline);
        
        Discord_SendEmbed(Embed_Online, Channel_Conexao, message);
        Daily_SetPlayerAverage(players);
    }
}

hook OnGameModeInit() 
{
    Channel_BatePapo = 
        DCC_FindChannelById(DISCORD_CHANNEL_BATEPAPO);      // 'Bate-papo'

    Channel_SocioLogs =
        DCC_FindChannelById(DISCORD_CHANNEL_SOCIOLOGS);     // 'logs-sócio'

    Channel_Comandos = 
        DCC_FindChannelById(DISCORD_CHANNEL_COMANDOS);      // 'comandos-servidor'

    Channel_Conexao = 
        DCC_FindChannelById(DISCORD_CHANNEL_CONEXAO);       // 'conexão'

    Channel_Attendance = 
        DCC_FindChannelById(DISCORD_CHANNEL_ATTENDANCE);    // 'log-atendimentos'

    Channel_AdminAviso = 
        DCC_FindChannelById(DISCORD_CHANNEL_ADMINAVISO);    // 'log-adminaviso'

    return 1;
}

hook OnGameModeExit() {
    DCC_DeleteMessage(Message_EmbedOnline);
}

public OnDiscordCommandAttempt(DCC_User:user, DCC_Channel:channel, const cmdtext[])
{
    return 1;
}

public OnDiscordCommandPerformed(DCC_User:user, DCC_Channel:channel, const cmdtext[], success)
{
    return 1;
}

public DCC_OnMessageCreate(DCC_Message:message)
{
    new 
        message_id[DCC_ID_SIZE], 
        content[128],
        DCC_Channel:channel;

    DCC_GetMessageId(message, message_id);
    DCC_GetMessageChannel(message, channel);
    DCC_GetMessageContent(message, content);

    if (channel == Channel_Conexao) {
        Message_EmbedOnline = message;
        DCC_SetMessagePersistent(Message_EmbedOnline, true);
    }
    return 1;
}

hook OnPlayerLogin(playerid)
{
    new DCC_Guild:guild = DCC_FindGuildById("381623944748466188"),
        DCC_User:user = DCC_FindUserById(Player_GetDiscordUser(playerid)),
        offset;

    DCC_GetGuildMember(guild, offset, user);
    return 1;
}

stock Discord_SetPlayerNick(playerid, const new_nick[]) 
{
    new DCC_Guild:guild = DCC_FindGuildById(DISCORD_SERVER_ID),
        DCC_User:user = DCC_FindUserById(Player_GetDiscordUser(playerid));

    new string[128];
	format(string, sizeof(string), "%s | %d", new_nick, Player_GetAccountID(playerid));
	DCC_SetGuildMemberNickname(guild, user, string);
    return 1;
}

hook OnPlayerSocioActivate(playerid, nivel)
{
    new DCC_Guild:guild = DCC_FindGuildById("381623944748466188"),
        DCC_User:user = DCC_FindUserById(Player_GetDiscordUser(playerid)),
        DCC_Role:socio1 = DCC_FindRoleById("1156007295793238088"),
        DCC_Role:socio2 = DCC_FindRoleById("1156007139194699877"),
        DCC_Role:socio3 = DCC_FindRoleById("1156006639548239983"),
        DCC_Role:socio4 = DCC_FindRoleById("1156005722589507654");

    DCC_RemoveGuildMemberRole(guild, user, socio1);
    DCC_RemoveGuildMemberRole(guild, user, socio2);
    DCC_RemoveGuildMemberRole(guild, user, socio3);
    DCC_RemoveGuildMemberRole(guild, user, socio4);

    switch (nivel) {
        case SOCIO_COMUM:       DCC_AddGuildMemberRole(guild, user, socio1);
        case SOCIO_PREMIUM:     DCC_AddGuildMemberRole(guild, user, socio2);
        case SOCIO_SUPREME:     DCC_AddGuildMemberRole(guild, user, socio3);
        case SOCIO_EXTREME:     DCC_AddGuildMemberRole(guild, user, socio4);
    }
    return 1;
}

stock Discord_SetStaff(playerid, level)
{
    new DCC_Guild:guild = DCC_FindGuildById("381623944748466188"),
        DCC_User:user = DCC_FindUserById(Player_GetDiscordUser(playerid)),
        DCC_Role:estagiario = DCC_FindRoleById("381626691522527232"),
        DCC_Role:moderador = DCC_FindRoleById("381627025699635201"),
        DCC_Role:admin = DCC_FindRoleById("381627346475810817"),
        DCC_Role:encarregado = DCC_FindRoleById("381627475215646720"),
        DCC_Role:supervisor = DCC_FindRoleById("381627907140878338"),
        DCC_Role:coordenador = DCC_FindRoleById("1039502059034136576"),
        DCC_Role:gerente = DCC_FindRoleById("381628127547359252"),
        DCC_Role:diretor = DCC_FindRoleById("1241219429660885002"),
        DCC_Role:subdono = DCC_FindRoleById("1039503036051107870"),
        DCC_Role:dono = DCC_FindRoleById("795992878907260959"),
        DCC_Role:cofundador = DCC_FindRoleById("1027577311018635357"),
        DCC_Role:fundador = DCC_FindRoleById("810925418621304862"),
        DCC_Role:desenvolvedor = DCC_FindRoleById("381646500029005836");

    DCC_RemoveGuildMemberRole(guild, user, estagiario);
    DCC_RemoveGuildMemberRole(guild, user, moderador);
    DCC_RemoveGuildMemberRole(guild, user, admin);
    DCC_RemoveGuildMemberRole(guild, user, encarregado);
    DCC_RemoveGuildMemberRole(guild, user, supervisor);
    DCC_RemoveGuildMemberRole(guild, user, coordenador);
    DCC_RemoveGuildMemberRole(guild, user, gerente);
    DCC_RemoveGuildMemberRole(guild, user, subdono);
    DCC_RemoveGuildMemberRole(guild, user, cofundador);
    DCC_RemoveGuildMemberRole(guild, user, fundador);
    DCC_RemoveGuildMemberRole(guild, user, desenvolvedor);

    switch (level) {
        case 1: DCC_AddGuildMemberRole(guild, user, estagiario);
        case 2: DCC_AddGuildMemberRole(guild, user, moderador);
        case 3: DCC_AddGuildMemberRole(guild, user, admin);
        case 4: DCC_AddGuildMemberRole(guild, user, encarregado);
        case 5: DCC_AddGuildMemberRole(guild, user, supervisor);
        case 1337: DCC_AddGuildMemberRole(guild, user, coordenador);
        case 1338: DCC_AddGuildMemberRole(guild, user, gerente);
        case 1339: DCC_AddGuildMemberRole(guild, user, diretor);
        case 3000: DCC_AddGuildMemberRole(guild, user, subdono);
        case 3001: DCC_AddGuildMemberRole(guild, user, dono);
        case 3004: DCC_AddGuildMemberRole(guild, user, cofundador);
        case 3005: DCC_AddGuildMemberRole(guild, user, fundador);
        case 5000: DCC_AddGuildMemberRole(guild, user, desenvolvedor);
    }

}

DCMD:editar(user, channel, params[]) 
{
    if (channel != Channel_Comandos)
        return Discord_SendMessage("Você precisa estar no canal de comandos-servidor.", Channel_Comandos);

    new name[MAX_PLAYER_NAME], stats, value;
    if (sscanf(params, "s[24]dd", name, stats, value))
        return Discord_SendMessage("Modo de uso: $editar ```str:nome do jogador | int:id da variavel | int:valor da variavel```\n\n\
                                    ```CÓDIGOS:\nLEVEL: 1 | RESPEITOS: 2 | HORAS JOGADAS: 3 | DINHEIRO: 4 | DINHEIRO_BANCO: 5\n\
                                                 OUROS: 6 | CASH: 7 | VIP_NIVEL: 8 | KILLS: 9 | DEATHS: 10 | SEXO: 11 | SKIN: 12\n\
                                                 CONTRATOS: 13 | APREENSOES: 14 | NÚMERO DE CELULAR: 15 | MACONHA: 16 | COCAINA: 17 | CRACK: 18\n\
                                                 SKILL DETETIVE: 19 | SKILL ADVOGADO: 20 | AVISOS: 21 | PRISOES ADM: 22 | TROCAS NICK: 23```", Channel_Comandos);

    if (stats == 7)
        return Discord_SendMessage("Esse código no momento não é permitido, você precisa pedir para que solicite uma Ativação de Cash no painel", Channel_Comandos);

    if (Player_Edit(INVALID_PLAYER_ID, user, name, EditPlayer:stats, value)) {
        Discord_SendMessage(":white_check_mark: A edição do jogador foi um sucesso!", Channel_Comandos);
    } else {
        Discord_SendMessage(":x: A edição não funcionou!", Channel_Comandos);
    }
    return 1;
}

DCMD:infoplayer(user, channel, params[]) 
{
    new name[MAX_PLAYER_NAME];
    if (sscanf(params, "s[24]", name))
        return Discord_SendMessage("Modo de uso: $infoplayer ```str:nome do jogador```", channel);

    if (!Player_Info(name, channel)) {
        Discord_SendMessage(":x: Jogador não localizado!", channel);
    }
    return 1;
}

DCMD:kick(user, channel, params[]) 
{
    if (channel != Channel_Comandos)
        return Discord_SendMessage("Você precisa estar no canal de comandos-servidor.", Channel_Comandos);

    new idplayer, reason[36];
    if (sscanf(params, "ds[36]", idplayer, reason))
        return Discord_SendMessage("Modo de uso: $kick ```int:id do jogador (online) | str:motivo```", channel);

    PlayerKick(INVALID_PLAYER_ID, user, idplayer, reason);
    return 1;
}

DCMD:ban(user, channel, params[]) 
{
    if (channel != Channel_Comandos)
        return Discord_SendMessage("Você precisa estar no canal de comandos-servidor.", Channel_Comandos);

    new target_player[MAX_PLAYER_NAME], days, reason[36];
    if (sscanf(params, "s[24]ds[34]", target_player, days, reason))
        return Discord_SendMessage("Modo de uso: $ban ```str:nome do jogador | int:dias (-1 para permanente) | str:motivo```", channel);

    new idgplayer = Player_GetAccountIDByNick(target_player);
    if (!idgplayer)
        return Discord_SendMessage("```Esse jogador não existe```", channel);

    new idplayer = GetPlayerID(target_player);
	if (Player_Logado(idplayer))
		PlayerBan(INVALID_PLAYER_ID, user, target_player, reason, days);
	else
		PlayerBan(INVALID_PLAYER_ID, user, target_player, reason, days);

    return 1;
}