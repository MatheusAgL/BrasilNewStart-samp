/* ---------------------------------------------------------------------
    - Textdraws: Celular
 --------------------------------------------------------------------- */

new 
    PlayerText:background_phone_ptext[2][MAX_PLAYERS],
    PlayerText:ptd_whats_messages[4][MAX_PLAYERS],
    PlayerText:phone_navbar_box[MAX_PLAYERS]
;


new 
    // Corpo do celular
    Text:body_phone_text[8] = Text:INVALID_TEXT_DRAW,

    // Relogio do topo:
    Text:phone_relogio_text = Text:INVALID_TEXT_DRAW,

    // Botão do meio:
    Text:phone_button_main = Text:INVALID_TEXT_DRAW,

    // Caso sem conexão:
    Text:phone_network = Text:INVALID_TEXT_DRAW,

    // Botão retornar ao inicio:
    Text:phone_button_whats_tomain = Text:INVALID_TEXT_DRAW,

    // Designer botão pesquisar:
    Text:phone_button_search[4] = Text:INVALID_TEXT_DRAW,

    // Espaço entre as conversas
    //Text:phone_whatsmain_spacer[MAX_LINES_WHATS_MSG],

    // Backgroud perfil (conversas)
    //Text:phone_backgroud_perfil[MAX_LINES_WHATS_MSG],

    // Abrir chat:
    Text:phone_button_new_conversation[2] = Text:INVALID_TEXT_DRAW,

    // Decorações (sistemas inativos)
    Text:phone_whats_decoration[2] = Text:INVALID_TEXT_DRAW,

    // Navbar botões
    Text:phone_navbar_button_calls[2] = Text:INVALID_TEXT_DRAW,
    Text:phone_navbar_button_convstns[2] = Text:INVALID_TEXT_DRAW,

    // Descer histórico de conversas do WhatsApp
    Text:phone_whats_historic_down = Text:INVALID_TEXT_DRAW,

    // (Dentro das mensagens)

    // WhatsApp - Background principal
    Text:box_whats_send_message = Text:INVALID_TEXT_DRAW,

    // WhatsApp - Background decoração
    PlayerText:background_whats_messages[2][MAX_PLAYERS],

    // WhatsApp - Chamar player
    Text:phone_whats_messages_cbutton = Text:INVALID_TEXT_DRAW,

    // ----------------------------
    // WhatsApp -

    // NavBar

    // Balão de notificação (vermelho)
    Text:phone_whats_notify_ballon[2] = Text:INVALID_TEXT_DRAW,

    // Foto de perfil (da mensagem)
    PlayerText:phone_whats_main_photo_msg[MAX_LINES_WHATS_MSG][MAX_PLAYERS],

    // Imagem de perfil no Whats:
    PlayerText:phone_whats_profile_photo[MAX_LINES_WHATS_MSG][MAX_PLAYERS],

    // Data da ultima mensagem
    PlayerText:phone_whats_msg_date[MAX_LINES_WHATS_MSG][MAX_PLAYERS],

    // Quantidade de mensagem não lida
    PlayerText:phone_whats_text_notify[MAX_LINES_WHATS_MSG][MAX_PLAYERS],

    // Quantidade de mensagem não lida no navbar
    PlayerText:phone_notify_whatsmain_text[MAX_LINES_WHATS_MSG][MAX_PLAYERS],

    // Texto da mensagem WhatsApp
    PlayerText:phone_whats_main_msg_ptext[MAX_LINES_WHATS_MSG][MAX_PLAYERS],

    // Barra de rolagem
    PlayerText:phone_scrollbar[MAX_PLAYERS],

    // Texto: Conversas (Topo)
    PlayerText:phone_topo_text_main[MAX_PLAYERS],

    // Texto: Procurar conversa
    PlayerText:phone_text_search[MAX_PLAYERS],

    // Conexão do jogador
    PlayerText:phone_network_info[3][MAX_PLAYERS],

    PlayerText:box_whatsapp_message[MAX_LINES_WHATS_MSG][MAX_PLAYERS],
    PlayerText:msg_whatsapp_message[MAX_LINES_WHATS_MSG][MAX_PLAYERS],
    PlayerText:hour_whatsapp_message[MAX_LINES_WHATS_MSG][MAX_PLAYERS],

    PlayerText:tophour_whatsapp_message[MAX_LINES_WHATS_MSG][MAX_PLAYERS]
;


// Atualiza a hora no celular
stock Phone_SetHourNotSec() {
    TextDrawSetString(phone_relogio_text, GetCurrentDateHour(ONLY_CURRENT_HOUR_NSEC));
}

enum PhoneParty 
{
    PHONE_PARTY_BODY,
    PHONE_PARTY_BACKGROUND,
    PHONE_PARTY_RELOGIO,
    PHONE_WHATSAPP_NAVBAR_MESSAGES,
    PHONE_WHATSAPP_CONVRS,
    PHONE_WHATSAPP_MESSAGES,
    PHONE_PART_NETWORK,
    PHONE_PART_NETWORK_CLOSED
};

void:Phone_HideParty(playerid) {

    new PhoneScreen:telaid = Phone_GetScreen(playerid);

    switch (telaid) {
        case PHONE_TELA_SPLASH: {
            Phone_ShowParty(playerid, PHONE_PARTY_BACKGROUND, false);
        }
        case WHATSAPP_TELA_CONVERSATION: {
            Phone_ShowParty(playerid, PHONE_PARTY_RELOGIO, false);
            Phone_ShowParty(playerid, PHONE_WHATSAPP_CONVRS, false);
        }
        case WHATSAPP_TELA_MESSAGES: {
            WhatsApp_SetMessagesTela(playerid, 0);

            Phone_ShowParty(playerid, PHONE_PARTY_BACKGROUND, false);
            Phone_ShowParty(playerid, PHONE_PARTY_RELOGIO, false);
            Phone_ShowParty(playerid, PHONE_PART_NETWORK, false);
            Phone_ShowParty(playerid, PHONE_WHATSAPP_MESSAGES, false);
            Phone_ShowParty(playerid, PHONE_WHATSAPP_NAVBAR_MESSAGES, false);
        }
        //case WHATSAPP_TELA_CONVERSATION: Phone_ShowParty(playerid, PHONE_WHATSAPP_CONVRS, false);
    }
}

void:Phone_ShowParty(playerid, PhoneParty: party, bool:stats = true, background_color = 269488383) 
{
    #pragma unused background_color

    switch (party) 
    {
        case PHONE_PARTY_BACKGROUND:
        {
            if (stats) {
                background_phone_ptext[0][playerid] = CreatePlayerTextDraw(playerid, 407.000000, 201.000000, "_");
                PlayerTextDrawLetterSize(playerid, background_phone_ptext[0][playerid], 0.612500, 23.049961);
                PlayerTextDrawTextSize(playerid, background_phone_ptext[0][playerid], 507.000000, 17.500000);
                PlayerTextDrawAlignment(playerid, background_phone_ptext[0][playerid], TEXT_DRAW_ALIGN_LEFT);
                PlayerTextDrawBoxColor(playerid, background_phone_ptext[0][playerid], background_color);
                PlayerTextDrawUseBox(playerid, background_phone_ptext[0][playerid], true);
    
                background_phone_ptext[1][playerid] = CreatePlayerTextDraw(playerid, 407.000000, 201.000000, "_");
                PlayerTextDrawLetterSize(playerid, background_phone_ptext[1][playerid], 0.612500, 0.800005);
                PlayerTextDrawTextSize(playerid, background_phone_ptext[1][playerid], 507.000000, 6.000000);
                PlayerTextDrawAlignment(playerid, background_phone_ptext[1][playerid], TEXT_DRAW_ALIGN_LEFT);
                PlayerTextDrawBoxColor(playerid, background_phone_ptext[1][playerid], 186);
                PlayerTextDrawUseBox(playerid, background_phone_ptext[1][playerid], true);

                for (new loop; loop < sizeof(background_phone_ptext); loop++) {
                    PlayerTextDrawShow(playerid, background_phone_ptext[loop][playerid]);
                }
            } else {
                for (new loop; loop < sizeof(background_phone_ptext); loop++) {
                    PlayerTextDrawHide(playerid, background_phone_ptext[loop][playerid]);
                    PlayerTextDrawDestroy(playerid, background_phone_ptext[loop][playerid]);
                }
            }
        }

        case PHONE_PARTY_BODY: {

            if (stats) {
                for (new loop; loop < sizeof(body_phone_text); loop++)
                    TextDrawShowForPlayer(playerid, body_phone_text[loop]);

                TextDrawShowForPlayer(playerid, phone_button_main);
            } else {
                for (new loop; loop < sizeof(body_phone_text); loop++)
                    TextDrawHideForPlayer(playerid, body_phone_text[loop]);
            
                TextDrawHideForPlayer(playerid, phone_button_main);
            }
        }

        case PHONE_PARTY_RELOGIO: {
            if (stats) {
                TextDrawShowForPlayer(playerid, phone_relogio_text);
            } else {
                TextDrawHideForPlayer(playerid, phone_relogio_text);
            }
        }

        case PHONE_WHATSAPP_CONVRS: {

            if (stats) {

                // Botão para retornar ao menu anterior
                TextDrawShowForPlayer(playerid, phone_button_whats_tomain);

                // Nova conversa
                for (new loop; loop < sizeof(phone_button_new_conversation); loop++) {
                    TextDrawShowForPlayer(playerid, phone_button_new_conversation[loop]);
                    TextDrawShowForPlayer(playerid, phone_whats_decoration[loop]);
                }

                // Layout do botão pesquisar
                for (new loop; loop < sizeof(phone_button_search); loop++) {
                    TextDrawShowForPlayer(playerid, phone_button_search[loop]);
                }

            } else {
                // Botão para retornar ao menu anterior
                TextDrawHideForPlayer(playerid, phone_button_whats_tomain);

                // Nova conversa
                for (new loop; loop < sizeof(phone_button_new_conversation); loop++) {
                    TextDrawHideForPlayer(playerid, phone_button_new_conversation[loop]);
                    TextDrawHideForPlayer(playerid, phone_whats_decoration[loop]);
                }

                // Layout do botão pesquisar
                for (new loop; loop < sizeof(phone_button_search); loop++) {
                    TextDrawHideForPlayer(playerid, phone_button_search[loop]);
                }
            }
        }

        case PHONE_PART_NETWORK: {
            if (stats) {
                for (new loop; loop < sizeof(phone_network_info); loop++) {
                    phone_network_info[loop][playerid] = CreatePlayerTextDraw(playerid, 487.0 + (loop * 4.0), 203.000000 - (loop * 2.0), "I");
                    PlayerTextDrawFont(playerid, phone_network_info[loop][playerid], TEXT_DRAW_FONT_2);
                    PlayerTextDrawLetterSize(playerid, phone_network_info[loop][playerid], 0.449999, 0.500000 + (loop * 0.25));
                    PlayerTextDrawTextSize(playerid, phone_network_info[loop][playerid], 507.000000, 6.000000);
                    PlayerTextDrawSetOutline(playerid, phone_network_info[loop][playerid], 1);
                    PlayerTextDrawSetShadow(playerid, phone_network_info[loop][playerid], 0);
                    PlayerTextDrawAlignment(playerid, phone_network_info[loop][playerid], TEXT_DRAW_ALIGN_RIGHT);
                    PlayerTextDrawColor(playerid, phone_network_info[loop][playerid], -1);
                    PlayerTextDrawBackgroundColor(playerid, phone_network_info[loop][playerid], 255);
                    PlayerTextDrawBoxColor(playerid, phone_network_info[loop][playerid], 186);
                    PlayerTextDrawUseBox(playerid, phone_network_info[loop][playerid], false);
                    PlayerTextDrawSetProportional(playerid, phone_network_info[loop][playerid], true);
                    PlayerTextDrawSetSelectable(playerid, phone_network_info[loop][playerid], false);

                    PlayerTextDrawShow(playerid, phone_network_info[loop][playerid]);
                }
            } else {
                for (new loop; loop < sizeof(phone_network_info); loop++) {
                    PlayerTextDrawHide(playerid, phone_network_info[loop][playerid]);
                    PlayerTextDrawDestroy(playerid, phone_network_info[loop][playerid]);
                }
            }
        }

        case PHONE_WHATSAPP_NAVBAR_MESSAGES: {
            if (stats) {
                phone_navbar_box[playerid] = CreatePlayerTextDraw(playerid, 407.000000, 393.000000, "_");
                PlayerTextDrawFont(playerid, phone_navbar_box[playerid], TEXT_DRAW_FONT_0);
                PlayerTextDrawLetterSize(playerid, phone_navbar_box[playerid], 0.612500, 1.750005);
                PlayerTextDrawTextSize(playerid, phone_navbar_box[playerid], 503.500000, 38.500000);
                PlayerTextDrawSetOutline(playerid, phone_navbar_box[playerid], 1);
                PlayerTextDrawSetShadow(playerid, phone_navbar_box[playerid], 0);
                PlayerTextDrawAlignment(playerid, phone_navbar_box[playerid], TEXT_DRAW_ALIGN_LEFT);
                PlayerTextDrawColor(playerid, phone_navbar_box[playerid], 255);
                PlayerTextDrawBackgroundColor(playerid, phone_navbar_box[playerid], 255);
                PlayerTextDrawBoxColor(playerid, phone_navbar_box[playerid], 227);
                PlayerTextDrawUseBox(playerid, phone_navbar_box[playerid], true);
                PlayerTextDrawSetProportional(playerid, phone_navbar_box[playerid], true);
                PlayerTextDrawSetSelectable(playerid, phone_navbar_box[playerid], false);

                PlayerTextDrawShow(playerid, phone_navbar_box[playerid]);
            } else {
                PlayerTextDrawHide(playerid, phone_navbar_box[playerid]);
                PlayerTextDrawDestroy(playerid, phone_navbar_box[playerid]);
            }
        }

        case PHONE_WHATSAPP_MESSAGES: {

            if (stats) {
                ptd_whats_messages[0][playerid] = CreatePlayerTextDraw(playerid, 438.000000, 212.000000, "_");
                PlayerTextDrawFont(playerid, ptd_whats_messages[0][playerid], TEXT_DRAW_FONT_1);
                PlayerTextDrawLetterSize(playerid, ptd_whats_messages[0][playerid], 0.158332, 0.800005);
                PlayerTextDrawTextSize(playerid, ptd_whats_messages[0][playerid], 504.000000, 6.000000);
                PlayerTextDrawSetOutline(playerid, ptd_whats_messages[0][playerid], 2);
                PlayerTextDrawSetShadow(playerid, ptd_whats_messages[0][playerid], 0);
                PlayerTextDrawAlignment(playerid, ptd_whats_messages[0][playerid], TEXT_DRAW_ALIGN_LEFT);
                PlayerTextDrawBackgroundColor(playerid, ptd_whats_messages[0][playerid], 0);
                PlayerTextDrawColor(playerid, ptd_whats_messages[0][playerid], -1);
                PlayerTextDrawSetProportional(playerid, ptd_whats_messages[0][playerid], true);
                PlayerTextDrawSetSelectable(playerid, ptd_whats_messages[0][playerid], false);

                ptd_whats_messages[1][playerid] = CreatePlayerTextDraw(playerid, 438.000000, 220.000000, "visto por ultimo~n~22/10/2022 as 22:22:22");
                PlayerTextDrawFont(playerid, ptd_whats_messages[1][playerid], TEXT_DRAW_FONT_2);
                PlayerTextDrawLetterSize(playerid, ptd_whats_messages[1][playerid], 0.099999, 0.550005);
                PlayerTextDrawTextSize(playerid, ptd_whats_messages[1][playerid], 504.000000, 6.000000);
                PlayerTextDrawSetOutline(playerid, ptd_whats_messages[1][playerid], 2);
                PlayerTextDrawSetShadow(playerid, ptd_whats_messages[1][playerid], 0);
                PlayerTextDrawAlignment(playerid, ptd_whats_messages[1][playerid], TEXT_DRAW_ALIGN_LEFT);
                PlayerTextDrawColor(playerid, ptd_whats_messages[1][playerid], 1296911871);
                PlayerTextDrawBackgroundColor(playerid, ptd_whats_messages[1][playerid], 0);
                PlayerTextDrawBoxColor(playerid, ptd_whats_messages[1][playerid], 186);
                PlayerTextDrawUseBox(playerid, ptd_whats_messages[1][playerid], false);
                PlayerTextDrawSetProportional(playerid, ptd_whats_messages[1][playerid], true);
                PlayerTextDrawSetSelectable(playerid, ptd_whats_messages[1][playerid], false);

                ptd_whats_messages[2][playerid] = CreatePlayerTextDraw(playerid, 416.000000, 211.000000, "Preview_Model");
                PlayerTextDrawFont(playerid, ptd_whats_messages[2][playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
                PlayerTextDrawLetterSize(playerid, ptd_whats_messages[2][playerid], 0.600000, 2.000000);
                PlayerTextDrawTextSize(playerid, ptd_whats_messages[2][playerid], 23.000000, 19.000000);
                PlayerTextDrawSetOutline(playerid, ptd_whats_messages[2][playerid], 0);
                PlayerTextDrawSetShadow(playerid, ptd_whats_messages[2][playerid], 0);
                PlayerTextDrawAlignment(playerid, ptd_whats_messages[2][playerid], TEXT_DRAW_ALIGN_LEFT);
                PlayerTextDrawColor(playerid, ptd_whats_messages[2][playerid], -1);
                PlayerTextDrawBackgroundColor(playerid, ptd_whats_messages[2][playerid], 0);
                PlayerTextDrawBoxColor(playerid, ptd_whats_messages[2][playerid], 255);
                PlayerTextDrawUseBox(playerid, ptd_whats_messages[2][playerid], false);
                PlayerTextDrawSetProportional(playerid, ptd_whats_messages[2][playerid], true);
                PlayerTextDrawSetSelectable(playerid, ptd_whats_messages[2][playerid], false);
                PlayerTextDrawSetPreviewModel(playerid, ptd_whats_messages[2][playerid], 88);
                PlayerTextDrawSetPreviewRot(playerid, ptd_whats_messages[2][playerid], 0.000000, 0.000000, 0.000000, 0.789999);
                PlayerTextDrawSetPreviewVehCol(playerid, ptd_whats_messages[2][playerid], 1, 1);

                ptd_whats_messages[3][playerid] = CreatePlayerTextDraw(playerid, 408.000000, 215.000000, "< 8");
                PlayerTextDrawFont(playerid, ptd_whats_messages[3][playerid], TEXT_DRAW_FONT_2);
                PlayerTextDrawLetterSize(playerid, ptd_whats_messages[3][playerid], 0.108332, 1.100005);
                PlayerTextDrawTextSize(playerid, ptd_whats_messages[3][playerid], 419.000000, 11.500000);
                PlayerTextDrawSetOutline(playerid, ptd_whats_messages[3][playerid], 2);
                PlayerTextDrawSetShadow(playerid, ptd_whats_messages[3][playerid], 0);
                PlayerTextDrawAlignment(playerid, ptd_whats_messages[3][playerid], TEXT_DRAW_ALIGN_LEFT);
                PlayerTextDrawColor(playerid, ptd_whats_messages[3][playerid], 1097458175);
                PlayerTextDrawBackgroundColor(playerid, ptd_whats_messages[3][playerid], 0);
                PlayerTextDrawBoxColor(playerid, ptd_whats_messages[3][playerid], 186);
                PlayerTextDrawUseBox(playerid, ptd_whats_messages[3][playerid], false);
                PlayerTextDrawSetProportional(playerid, ptd_whats_messages[3][playerid], true);
                PlayerTextDrawSetSelectable(playerid, ptd_whats_messages[3][playerid], true);

                for (new loop; loop < sizeof(ptd_whats_messages); loop++) {
                    PlayerTextDrawShow(playerid, ptd_whats_messages[loop][playerid]);
                }
                TextDrawShowForPlayer(playerid, phone_whats_messages_cbutton);
    
            } else {
                for (new loop; loop < sizeof(ptd_whats_messages); loop++) {
                    PlayerTextDrawHide(playerid, ptd_whats_messages[loop][playerid]);
                    PlayerTextDrawDestroy(playerid, ptd_whats_messages[loop][playerid]);
                }
            }
        }

        case PHONE_PART_NETWORK_CLOSED: {

            TextDrawColor(body_phone_text[2], 0xB6B5B5FF);

            if (stats) {
                TextDrawShowForPlayer(playerid, phone_network);
            } else {
                TextDrawHideForPlayer(playerid, phone_network);
            }
        }
    }
}


// Crie os text do celular:
stock TDCreate_Phone()
{

    // Sistema operacional:
    // iOs

    // Corpo principal
    body_phone_text[0] = TextDrawCreate(407.000000, 197.000000, "_");
    TextDrawFont(body_phone_text[0], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(body_phone_text[0], 0.612500, 25.549922);
    TextDrawTextSize(body_phone_text[0], 507.000000, 24.000000);
    TextDrawSetOutline(body_phone_text[0], 1);
    TextDrawSetShadow(body_phone_text[0], 0);
    TextDrawAlignment(body_phone_text[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(body_phone_text[0], -1);
    TextDrawBackgroundColor(body_phone_text[0], 255);
    TextDrawBoxColor(body_phone_text[0], 255);
    TextDrawUseBox(body_phone_text[0], true);
    TextDrawSetProportional(body_phone_text[0], true);
    TextDrawSetSelectable(body_phone_text[0], false);

    // Bolinhas para arredondar o corpo do celular
    body_phone_text[1] = TextDrawCreate(402.000000, 195.000000, "ld_pool:ball");
    TextDrawFont(body_phone_text[1], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(body_phone_text[1], 0.600000, 2.000000);
    TextDrawTextSize(body_phone_text[1], 10.500000, 11.000000);
    TextDrawSetOutline(body_phone_text[1], 1);
    TextDrawSetShadow(body_phone_text[1], 0);
    TextDrawAlignment(body_phone_text[1], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(body_phone_text[1], 255);
    TextDrawBackgroundColor(body_phone_text[1], 255);
    TextDrawBoxColor(body_phone_text[1], 50);
    TextDrawUseBox(body_phone_text[1], true);
    TextDrawSetProportional(body_phone_text[1], true);
    TextDrawSetSelectable(body_phone_text[1], false);

    body_phone_text[2] = TextDrawCreate(501.000000, 195.000000, "ld_pool:ball");
    TextDrawFont(body_phone_text[2], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(body_phone_text[2], 0.600000, 2.000000);
    TextDrawTextSize(body_phone_text[2], 10.500000, 11.000000);
    TextDrawSetOutline(body_phone_text[2], 1);
    TextDrawSetShadow(body_phone_text[2], 0);
    TextDrawAlignment(body_phone_text[2], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(body_phone_text[2], 255);
    TextDrawBackgroundColor(body_phone_text[2], 255);
    TextDrawBoxColor(body_phone_text[2], 50);
    TextDrawUseBox(body_phone_text[2], true);
    TextDrawSetProportional(body_phone_text[2], true);
    TextDrawSetSelectable(body_phone_text[2], false);

    body_phone_text[3] = TextDrawCreate(501.000000, 418.000000, "ld_pool:ball");
    TextDrawFont(body_phone_text[3], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(body_phone_text[3], 0.600000, 2.000000);
    TextDrawTextSize(body_phone_text[3], 10.500000, 11.000000);
    TextDrawSetOutline(body_phone_text[3], 1);
    TextDrawSetShadow(body_phone_text[3], 0);
    TextDrawAlignment(body_phone_text[3], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(body_phone_text[3], 255);
    TextDrawBackgroundColor(body_phone_text[3], 255);
    TextDrawBoxColor(body_phone_text[3], 50);
    TextDrawUseBox(body_phone_text[3], true);
    TextDrawSetProportional(body_phone_text[3], true);
    TextDrawSetSelectable(body_phone_text[3], false);

    body_phone_text[4] = TextDrawCreate(402.000000, 418.000000, "ld_pool:ball");
    TextDrawFont(body_phone_text[4], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(body_phone_text[4], 0.600000, 2.000000);
    TextDrawTextSize(body_phone_text[4], 10.500000, 11.000000);
    TextDrawSetOutline(body_phone_text[4], 1);
    TextDrawSetShadow(body_phone_text[4], 0);
    TextDrawAlignment(body_phone_text[4], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(body_phone_text[4], 255);
    TextDrawBackgroundColor(body_phone_text[4], 255);
    TextDrawBoxColor(body_phone_text[4], 50);
    TextDrawUseBox(body_phone_text[4], true);
    TextDrawSetProportional(body_phone_text[4], true);
    TextDrawSetSelectable(body_phone_text[4], false);

    // Corpo secundário
    body_phone_text[5] = TextDrawCreate(403.500000, 202.000000, "_");
    TextDrawFont(body_phone_text[5], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(body_phone_text[5], 0.600000, 24.349941);
    TextDrawTextSize(body_phone_text[5], 510.500000, 24.000000);
    TextDrawSetOutline(body_phone_text[5], 1);
    TextDrawSetShadow(body_phone_text[5], 0);
    TextDrawAlignment(body_phone_text[5], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(body_phone_text[5], -1);
    TextDrawBackgroundColor(body_phone_text[5], 255);
    TextDrawBoxColor(body_phone_text[5], 255);
    TextDrawUseBox(body_phone_text[5], true);
    TextDrawSetProportional(body_phone_text[5], true);
    TextDrawSetSelectable(body_phone_text[5], false);
    
    // Câmera e Flash
    body_phone_text[6] = TextDrawCreate(451.000000, 191.000000, ".");
    TextDrawFont(body_phone_text[6], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(body_phone_text[6], 0.216664, 0.900007);
    TextDrawTextSize(body_phone_text[6], 502.500000, 8.000000);
    TextDrawSetOutline(body_phone_text[6], 0);
    TextDrawSetShadow(body_phone_text[6], 0);
    TextDrawAlignment(body_phone_text[6], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(body_phone_text[6], -1);
    TextDrawBackgroundColor(body_phone_text[6], 255);
    TextDrawBoxColor(body_phone_text[6], 186);
    TextDrawUseBox(body_phone_text[6], false);
    TextDrawSetProportional(body_phone_text[6], true);
    TextDrawSetSelectable(body_phone_text[6], false);

    body_phone_text[7] = TextDrawCreate(456.000000, 196.000000, "ld_dual:light");
    TextDrawFont(body_phone_text[7], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(body_phone_text[7], 0.600000, 2.000000);
    TextDrawTextSize(body_phone_text[7], 2.000000, 2.500000);
    TextDrawSetOutline(body_phone_text[7], 1);
    TextDrawSetShadow(body_phone_text[7], 0);
    TextDrawAlignment(body_phone_text[7], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(body_phone_text[7], 1296911871);
    TextDrawBackgroundColor(body_phone_text[7], 255);
    TextDrawBoxColor(body_phone_text[7], 50);
    TextDrawUseBox(body_phone_text[7], true);
    TextDrawSetProportional(body_phone_text[7], true);
    TextDrawSetSelectable(body_phone_text[7], false);

    // Botão de retorno principal:
    phone_button_main = TextDrawCreate(453.000000, 413.000000, "ld_pool:ball");
    TextDrawFont(phone_button_main, TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(phone_button_main, 0.600000, 2.000000);
    TextDrawTextSize(phone_button_main, 10.500000, 11.000000);
    TextDrawSetOutline(phone_button_main, 1);
    TextDrawSetShadow(phone_button_main, 0);
    TextDrawAlignment(phone_button_main, TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(phone_button_main, 421075455);
    TextDrawBackgroundColor(phone_button_main, 255);
    TextDrawBoxColor(phone_button_main, 50);
    TextDrawUseBox(phone_button_main, true);
    TextDrawSetProportional(phone_button_main, true);
    TextDrawSetSelectable(phone_button_main, true);

    // Relógio principal (Localizado: Topo)
    phone_relogio_text = TextDrawCreate(409.000000, 200.000000, "--:--");
    TextDrawFont(phone_relogio_text, TEXT_DRAW_FONT_2);
    TextDrawLetterSize(phone_relogio_text, 0.137499, 0.750006);
    TextDrawTextSize(phone_relogio_text, 507.000000, 6.000000);
    TextDrawSetOutline(phone_relogio_text, 0);
    TextDrawSetShadow(phone_relogio_text, 0);
    TextDrawAlignment(phone_relogio_text, TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(phone_relogio_text, -1);
    TextDrawBackgroundColor(phone_relogio_text, 255);
    TextDrawBoxColor(phone_relogio_text, 186);
    TextDrawUseBox(phone_relogio_text, false);
    TextDrawSetProportional(phone_relogio_text, true);
    TextDrawSetSelectable(phone_relogio_text, false);

    // Sinal de rede (Localizado: Topo)
    // Offline
    phone_network = TextDrawCreate(479.000000, 203.000000, "X");
    TextDrawFont(phone_network, TEXT_DRAW_FONT_1);
    TextDrawLetterSize(phone_network, 0.104162, 0.500010);
    TextDrawTextSize(phone_network, 502.500000, 8.000000);
    TextDrawSetOutline(phone_network, 0);
    TextDrawSetShadow(phone_network, 0);
    TextDrawAlignment(phone_network, TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(phone_network, -16776961);
    TextDrawBackgroundColor(phone_network, 255);
    TextDrawBoxColor(phone_network, 186);
    TextDrawUseBox(phone_network, false);
    TextDrawSetProportional(phone_network, true);
    TextDrawSetSelectable(phone_network, false);

    // Botão retornar ao Lobby:
    phone_button_whats_tomain = TextDrawCreate(408.000000, 212.000000, "<");
    TextDrawFont(phone_button_whats_tomain, TEXT_DRAW_FONT_2);
    TextDrawLetterSize(phone_button_whats_tomain, 0.124999, 1.600005);
    TextDrawTextSize(phone_button_whats_tomain, 412.500000, 12.500000);
    TextDrawSetOutline(phone_button_whats_tomain, 2);
    TextDrawSetShadow(phone_button_whats_tomain, 0);
    TextDrawAlignment(phone_button_whats_tomain, TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(phone_button_whats_tomain, -1);
    TextDrawBackgroundColor(phone_button_whats_tomain, 0);
    TextDrawBoxColor(phone_button_whats_tomain, 186);
    TextDrawUseBox(phone_button_whats_tomain, false);
    TextDrawSetProportional(phone_button_whats_tomain, true);
    TextDrawSetSelectable(phone_button_whats_tomain, true);

    // -----------------------------------
    // Botão pesquisar:


    // Arredondamento
    phone_button_search[0] = TextDrawCreate(407.000000, 228.500000, "ld_pool:ball");
    TextDrawFont(phone_button_search[0], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(phone_button_search[0], 0.600000, 2.000000);
    TextDrawTextSize(phone_button_search[0], 12.000000, 12.000000);
    TextDrawSetOutline(phone_button_search[0], 1);
    TextDrawSetShadow(phone_button_search[0], 0);
    TextDrawAlignment(phone_button_search[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(phone_button_search[0], 255);
    TextDrawBackgroundColor(phone_button_search[0], 255);
    TextDrawBoxColor(phone_button_search[0], 50);
    TextDrawUseBox(phone_button_search[0], true);
    TextDrawSetProportional(phone_button_search[0], true);
    TextDrawSetSelectable(phone_button_search[0], false);

    phone_button_search[1] = TextDrawCreate(492.000000, 228.500000, "ld_pool:ball");
    TextDrawFont(phone_button_search[1], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(phone_button_search[1], 0.600000, 2.000000);
    TextDrawTextSize(phone_button_search[1], 12.000000, 12.000000);
    TextDrawSetOutline(phone_button_search[1], 1);
    TextDrawSetShadow(phone_button_search[1], 0);
    TextDrawAlignment(phone_button_search[1], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(phone_button_search[1], 255);
    TextDrawBackgroundColor(phone_button_search[1], 255);
    TextDrawBoxColor(phone_button_search[1], 50);
    TextDrawUseBox(phone_button_search[1], true);
    TextDrawSetProportional(phone_button_search[1], true);
    TextDrawSetSelectable(phone_button_search[1], false);

    // Box
    phone_button_search[2] = TextDrawCreate(413.000000, 230.000000, "_");
    TextDrawFont(phone_button_search[2], TEXT_DRAW_FONT_0);
    TextDrawLetterSize(phone_button_search[2], 0.612500, 0.950003);
    TextDrawTextSize(phone_button_search[2], 498.000000, 28.500000);
    TextDrawSetOutline(phone_button_search[2], 1);
    TextDrawSetShadow(phone_button_search[2], 0);
    TextDrawAlignment(phone_button_search[2], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(phone_button_search[2], 255);
    TextDrawBackgroundColor(phone_button_search[2], 255);
    TextDrawBoxColor(phone_button_search[2], 235);
    TextDrawUseBox(phone_button_search[2], true);
    TextDrawSetProportional(phone_button_search[2], true);
    TextDrawSetSelectable(phone_button_search[2], false);

    // Detalhe extra
    phone_button_search[3] = TextDrawCreate(413.000000, 231.000000, "~n~ \"");
    TextDrawFont(phone_button_search[3], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(phone_button_search[3], 0.233333, 0.350003);
    TextDrawTextSize(phone_button_search[3], 450.500000, 6.500000);
    TextDrawSetOutline(phone_button_search[3], 1);
    TextDrawSetShadow(phone_button_search[3], 0);
    TextDrawAlignment(phone_button_search[3], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(phone_button_search[3], 1296911871);
    TextDrawBackgroundColor(phone_button_search[3], 0);
    TextDrawBoxColor(phone_button_search[3], -213);
    TextDrawUseBox(phone_button_search[3], false);
    TextDrawSetProportional(phone_button_search[3], true);
    TextDrawSetSelectable(phone_button_search[3], true);

    /*for (new loop; loop < sizeof(phone_whatsmain_spacer); loop++) {

        // WhatsApp - Separadores:
        phone_whatsmain_spacer[loop] = TextDrawCreate(408.000000, 255.000000 + (loop * 25.0), "_");
        TextDrawFont(phone_whatsmain_spacer[loop], TEXT_DRAW_FONT_0);
        TextDrawLetterSize(phone_whatsmain_spacer[loop], 0.612500, -0.349992);
        TextDrawTextSize(phone_whatsmain_spacer[loop], 503.500000, 32.500000);
        TextDrawSetOutline(phone_whatsmain_spacer[loop], 1);
        TextDrawSetShadow(phone_whatsmain_spacer[loop], 0);
        TextDrawAlignment(phone_whatsmain_spacer[loop], TEXT_DRAW_ALIGN_LEFT);
        TextDrawColor(phone_whatsmain_spacer[loop], 255);
        TextDrawBackgroundColor(phone_whatsmain_spacer[loop], 255);
        TextDrawBoxColor(phone_whatsmain_spacer[loop], 1296911756);
        TextDrawUseBox(phone_whatsmain_spacer[loop], true);
        TextDrawSetProportional(phone_whatsmain_spacer[loop], true);
        TextDrawSetSelectable(phone_whatsmain_spacer[loop], false);

        // Backgroud - Perfil (WhatsApp)
        phone_backgroud_perfil[loop] = TextDrawCreate(407.000000, 257.000000 + (loop * 26.0), "ld_pool:ball");
        TextDrawFont(phone_backgroud_perfil[loop], TEXT_DRAW_FONT_SPRITE_DRAW);
        TextDrawLetterSize(phone_backgroud_perfil[loop], 0.600000, 2.000000);
        TextDrawTextSize(phone_backgroud_perfil[loop], 19.000000, 20.000000);
        TextDrawSetOutline(phone_backgroud_perfil[loop], 1);
        TextDrawSetShadow(phone_backgroud_perfil[loop], 0);
        TextDrawAlignment(phone_backgroud_perfil[loop], TEXT_DRAW_ALIGN_LEFT);
        TextDrawColor(phone_backgroud_perfil[loop], 155);
        TextDrawBackgroundColor(phone_backgroud_perfil[loop], 255);
        TextDrawBoxColor(phone_backgroud_perfil[loop], 50);
        TextDrawUseBox(phone_backgroud_perfil[loop], true);
        TextDrawSetProportional(phone_backgroud_perfil[loop], true);
        TextDrawSetSelectable(phone_backgroud_perfil[loop], false);
    }*/

    // WhatsApp - Decoração (sistema futuro)
    phone_whats_decoration[0] = TextDrawCreate(409.000000, 243.000000, "Lista de transmissao");
    TextDrawFont(phone_whats_decoration[0], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(phone_whats_decoration[0], 0.125000, 0.750006);
    TextDrawTextSize(phone_whats_decoration[0], 507.000000, 6.000000);
    TextDrawSetOutline(phone_whats_decoration[0], 1);
    TextDrawSetShadow(phone_whats_decoration[0], 0);
    TextDrawAlignment(phone_whats_decoration[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(phone_whats_decoration[0], 1097458175);
    TextDrawBackgroundColor(phone_whats_decoration[0], 0);
    TextDrawBoxColor(phone_whats_decoration[0], 0);
    TextDrawUseBox(phone_whats_decoration[0], false);
    TextDrawSetProportional(phone_whats_decoration[0], true);
    TextDrawSetSelectable(phone_whats_decoration[0], false);

    phone_whats_decoration[1] = TextDrawCreate(504.000000, 243.000000, "Novo grupo");
    TextDrawFont(phone_whats_decoration[1], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(phone_whats_decoration[1], 0.125000, 0.750006);
    TextDrawTextSize(phone_whats_decoration[1], 530.000000, 15.500000);
    TextDrawSetOutline(phone_whats_decoration[1], 1);
    TextDrawSetShadow(phone_whats_decoration[1], 0);
    TextDrawAlignment(phone_whats_decoration[1], TEXT_DRAW_ALIGN_RIGHT);
    TextDrawColor(phone_whats_decoration[1], 1097458175);
    TextDrawBackgroundColor(phone_whats_decoration[1], 0);
    TextDrawBoxColor(phone_whats_decoration[1], 255);
    TextDrawUseBox(phone_whats_decoration[1], false);
    TextDrawSetProportional(phone_whats_decoration[1], true);
    TextDrawSetSelectable(phone_whats_decoration[1], false);

    // WhatsApp - Abrir novo chat
    phone_button_new_conversation[0] = TextDrawCreate(495.000000, 213.000000, "O");
    TextDrawFont(phone_button_new_conversation[0], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(phone_button_new_conversation[0], 0.250000, 1.299998);
    TextDrawTextSize(phone_button_new_conversation[0], 502.000000, 10.000000);
    TextDrawSetOutline(phone_button_new_conversation[0], 0);
    TextDrawSetShadow(phone_button_new_conversation[0], 0);
    TextDrawAlignment(phone_button_new_conversation[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(phone_button_new_conversation[0], 1097458175);
    TextDrawBackgroundColor(phone_button_new_conversation[0], -1061109505);
    TextDrawBoxColor(phone_button_new_conversation[0], 50);
    TextDrawUseBox(phone_button_new_conversation[0], true);
    TextDrawSetProportional(phone_button_new_conversation[0], true);
    TextDrawSetSelectable(phone_button_new_conversation[0], true);

    phone_button_new_conversation[1] = TextDrawCreate(502.000000, 214.000000, "/");
    TextDrawFont(phone_button_new_conversation[1], TEXT_DRAW_FONT_3);
    TextDrawLetterSize(phone_button_new_conversation[1], 0.291666, 0.649999);
    TextDrawTextSize(phone_button_new_conversation[1], 509.000000, 9.300000);
    TextDrawSetOutline(phone_button_new_conversation[1], 0);
    TextDrawSetShadow(phone_button_new_conversation[1], 0);
    TextDrawAlignment(phone_button_new_conversation[1], TEXT_DRAW_ALIGN_RIGHT);
    TextDrawColor(phone_button_new_conversation[1], 1097458175);
    TextDrawBackgroundColor(phone_button_new_conversation[1], -1061109505);
    TextDrawBoxColor(phone_button_new_conversation[1], 50);
    TextDrawUseBox(phone_button_new_conversation[1], false);
    TextDrawSetProportional(phone_button_new_conversation[1], true);
    TextDrawSetSelectable(phone_button_new_conversation[1], true);

    // WhatsApp - Navbar

    // Funções
    phone_navbar_button_calls[0] = TextDrawCreate(431.000000, 391.000000, "C");
    TextDrawFont(phone_navbar_button_calls[0], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(phone_navbar_button_calls[0], 0.250000, 1.299998);
    TextDrawTextSize(phone_navbar_button_calls[0], 17.600000, 18.500000);
    TextDrawSetOutline(phone_navbar_button_calls[0], 0);
    TextDrawSetShadow(phone_navbar_button_calls[0], 0);
    TextDrawAlignment(phone_navbar_button_calls[0], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(phone_navbar_button_calls[0], 1296911871);
    TextDrawBackgroundColor(phone_navbar_button_calls[0], -1061109505);
    TextDrawBoxColor(phone_navbar_button_calls[0], -206);
    TextDrawUseBox(phone_navbar_button_calls[0], false);
    TextDrawSetProportional(phone_navbar_button_calls[0], true);
    TextDrawSetSelectable(phone_navbar_button_calls[0], true);

    phone_navbar_button_calls[1] = TextDrawCreate(431.000000, 390.000000, "~n~~n~Chamadas");
    TextDrawFont(phone_navbar_button_calls[1], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(phone_navbar_button_calls[1], 0.112498, 0.750000);
    TextDrawTextSize(phone_navbar_button_calls[1], 18.500000, 18.000000);
    TextDrawSetOutline(phone_navbar_button_calls[1], 0);
    TextDrawSetShadow(phone_navbar_button_calls[1], 0);
    TextDrawAlignment(phone_navbar_button_calls[1], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(phone_navbar_button_calls[1], 1296911871);
    TextDrawBackgroundColor(phone_navbar_button_calls[1], -1061109505);
    TextDrawBoxColor(phone_navbar_button_calls[1], -206);
    TextDrawUseBox(phone_navbar_button_calls[1], false);
    TextDrawSetProportional(phone_navbar_button_calls[1], true);
    TextDrawSetSelectable(phone_navbar_button_calls[1], true);

    phone_navbar_button_convstns[0] = TextDrawCreate(479.000000, 392.000000, ".O");
    TextDrawFont(phone_navbar_button_convstns[0], TEXT_DRAW_FONT_2);
    TextDrawLetterSize(phone_navbar_button_convstns[0], 0.250000, 1.299998);
    TextDrawTextSize(phone_navbar_button_convstns[0], 17.000000, 20.000000);
    TextDrawSetOutline(phone_navbar_button_convstns[0], 0);
    TextDrawSetShadow(phone_navbar_button_convstns[0], 0);
    TextDrawAlignment(phone_navbar_button_convstns[0], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(phone_navbar_button_convstns[0], 1097458175);
    TextDrawBackgroundColor(phone_navbar_button_convstns[0], -1061109505);
    TextDrawBoxColor(phone_navbar_button_convstns[0], -206);
    TextDrawUseBox(phone_navbar_button_convstns[0], false);
    TextDrawSetProportional(phone_navbar_button_convstns[0], true);
    TextDrawSetSelectable(phone_navbar_button_convstns[0], true);

    phone_navbar_button_convstns[1] = TextDrawCreate(479.000000, 392.000000, "~n~~n~Conversas");
    TextDrawFont(phone_navbar_button_convstns[1], TEXT_DRAW_FONT_1);
    TextDrawLetterSize(phone_navbar_button_convstns[1], 0.112498, 0.649999);
    TextDrawTextSize(phone_navbar_button_convstns[1], 17.000000, 20.000000);
    TextDrawSetOutline(phone_navbar_button_convstns[1], 0);
    TextDrawSetShadow(phone_navbar_button_convstns[1], 0);
    TextDrawAlignment(phone_navbar_button_convstns[1], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(phone_navbar_button_convstns[1], 1097458175);
    TextDrawBackgroundColor(phone_navbar_button_convstns[1], -1061109505);
    TextDrawBoxColor(phone_navbar_button_convstns[1], -1);
    TextDrawUseBox(phone_navbar_button_convstns[1], false);
    TextDrawSetProportional(phone_navbar_button_convstns[1], true);
    TextDrawSetSelectable(phone_navbar_button_convstns[1], true);

    // Ballon notificações
    for (new loop; loop < sizeof(phone_whats_notify_ballon); loop++) {
        phone_whats_notify_ballon[loop] = TextDrawCreate(427.0 + (loop*53.0), 393.000000, "ld_pool:ball");
        TextDrawFont(phone_whats_notify_ballon[loop], TEXT_DRAW_FONT_SPRITE_DRAW);
        TextDrawLetterSize(phone_whats_notify_ballon[loop], 0.600000, 2.000000);
        TextDrawTextSize(phone_whats_notify_ballon[loop], 4.500000, 6.000000);
        TextDrawSetOutline(phone_whats_notify_ballon[loop], 1);
        TextDrawSetShadow(phone_whats_notify_ballon[loop], 0);
        TextDrawAlignment(phone_whats_notify_ballon[loop], TEXT_DRAW_ALIGN_LEFT);
        TextDrawColor(phone_whats_notify_ballon[loop], -16776992);
        TextDrawBackgroundColor(phone_whats_notify_ballon[loop], 255);
        TextDrawBoxColor(phone_whats_notify_ballon[loop], 1097457970);
        TextDrawUseBox(phone_whats_notify_ballon[loop], true);
        TextDrawSetProportional(phone_whats_notify_ballon[loop], true);
        TextDrawSetSelectable(phone_whats_notify_ballon[loop], false);
    }

    phone_whats_messages_cbutton = TextDrawCreate(496.000000, 213.000000, "C");
    TextDrawFont(phone_whats_messages_cbutton, TEXT_DRAW_FONT_2);
    TextDrawLetterSize(phone_whats_messages_cbutton, 0.250000, 1.299998);
    TextDrawTextSize(phone_whats_messages_cbutton, 502.000000, 10.000000);
    TextDrawSetOutline(phone_whats_messages_cbutton, 0);
    TextDrawSetShadow(phone_whats_messages_cbutton, 0);
    TextDrawAlignment(phone_whats_messages_cbutton, TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(phone_whats_messages_cbutton, 1097458175);
    TextDrawBackgroundColor(phone_whats_messages_cbutton, -1061109505);
    TextDrawBoxColor(phone_whats_messages_cbutton, 50);
    TextDrawUseBox(phone_whats_messages_cbutton, true);
    TextDrawSetProportional(phone_whats_messages_cbutton, true);
    TextDrawSetSelectable(phone_whats_messages_cbutton, true);

    // Decoração - WhatsApp Groups

    // 2 Mans
    /*PublicTD[23] = TextDrawCreate(404.000000, 286.000000, "Preview_Model");
    TextDrawFont(PublicTD[23], TEXT_DRAW_FONT_MODEL_PREVIEW);
    TextDrawLetterSize(PublicTD[23], 0.600000, 2.000000);
    TextDrawTextSize(PublicTD[23], 20.000000, 12.500000);
    TextDrawSetOutline(PublicTD[23], 0);
    TextDrawSetShadow(PublicTD[23], 0);
    TextDrawAlignment(PublicTD[23], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(PublicTD[23], 255);
    TextDrawBackgroundColor(PublicTD[23], 0);
    TextDrawBoxColor(PublicTD[23], 255);
    TextDrawUseBox(PublicTD[23], false);
    TextDrawSetProportional(PublicTD[23], true);
    TextDrawSetSelectable(PublicTD[23], false);
    TextDrawSetPreviewModel(PublicTD[23], 0);
    TextDrawSetPreviewRot(PublicTD[23], 0.000000, 0.000000, 6.000000, 0.789999);
    TextDrawSetPreviewVehCol(PublicTD[23], 1, 1);

    PublicTD[24] = TextDrawCreate(409.000000, 286.000000, "Preview_Model");
    TextDrawFont(PublicTD[24], TEXT_DRAW_FONT_MODEL_PREVIEW);
    TextDrawLetterSize(PublicTD[24], 0.600000, 2.000000);
    TextDrawTextSize(PublicTD[24], 20.000000, 12.500000);
    TextDrawSetOutline(PublicTD[24], 0);
    TextDrawSetShadow(PublicTD[24], 0);
    TextDrawAlignment(PublicTD[24], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(PublicTD[24], 255);
    TextDrawBackgroundColor(PublicTD[24], 0);
    TextDrawBoxColor(PublicTD[24], 255);
    TextDrawUseBox(PublicTD[24], false);
    TextDrawSetProportional(PublicTD[24], true);
    TextDrawSetSelectable(PublicTD[24], false);
    TextDrawSetPreviewModel(PublicTD[24], 0);
    TextDrawSetPreviewRot(PublicTD[24], 0.000000, 0.000000, 6.000000, 0.789999);
    TextDrawSetPreviewVehCol(PublicTD[24], 1, 1);*/

    // WhatsApp - Descer histórico
    phone_whats_historic_down = TextDrawCreate(455.000000, 386.000000, "~DOWN~");
    TextDrawFont(phone_whats_historic_down, TEXT_DRAW_FONT_2);
    TextDrawLetterSize(phone_whats_historic_down, 0.124999, 0.350005);
    TextDrawTextSize(phone_whats_historic_down, 5.000000, 97.000000);
    TextDrawSetOutline(phone_whats_historic_down, 2);
    TextDrawSetShadow(phone_whats_historic_down, 0);
    TextDrawAlignment(phone_whats_historic_down, TEXT_DRAW_ALIGN_CENTER);
    TextDrawColor(phone_whats_historic_down, -1);
    TextDrawBackgroundColor(phone_whats_historic_down, 0);
    TextDrawBoxColor(phone_whats_historic_down, 186);
    TextDrawUseBox(phone_whats_historic_down, true);
    TextDrawSetProportional(phone_whats_historic_down, true);
    TextDrawSetSelectable(phone_whats_historic_down, true);

    box_whats_send_message = TextDrawCreate(423.000000, 398.000000, "_");
    TextDrawFont(box_whats_send_message, TEXT_DRAW_FONT_0);
    TextDrawLetterSize(box_whats_send_message, 0.612500, 0.600004);
    TextDrawTextSize(box_whats_send_message, 487.500000, 36.500000);
    TextDrawSetOutline(box_whats_send_message, 0);
    TextDrawSetShadow(box_whats_send_message, 0);
    TextDrawAlignment(box_whats_send_message, TEXT_DRAW_ALIGN_LEFT);
    TextDrawColor(box_whats_send_message, 1296911871);
    TextDrawBackgroundColor(box_whats_send_message, 255);
    TextDrawBoxColor(box_whats_send_message, 1296911871);
    TextDrawUseBox(box_whats_send_message, true);
    TextDrawSetProportional(box_whats_send_message, true);
    TextDrawSetSelectable(box_whats_send_message, false);
}

stock PTDCreate_Phone(playerid)
{
    // WhatsApp - Main Text Topo
    phone_topo_text_main[playerid] = CreatePlayerTextDraw(playerid, 414.000000, 214.000000, "Conversas");
    PlayerTextDrawFont(playerid, phone_topo_text_main[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, phone_topo_text_main[playerid], 0.229166, 1.100007);
    PlayerTextDrawTextSize(playerid, phone_topo_text_main[playerid], 504.000000, 6.000000);
    PlayerTextDrawSetOutline(playerid, phone_topo_text_main[playerid], 2);
    PlayerTextDrawSetShadow(playerid, phone_topo_text_main[playerid], 0);
    PlayerTextDrawAlignment(playerid, phone_topo_text_main[playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, phone_topo_text_main[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, phone_topo_text_main[playerid], 0);
    PlayerTextDrawBoxColor(playerid, phone_topo_text_main[playerid], 186);
    PlayerTextDrawUseBox(playerid, phone_topo_text_main[playerid], false);
    PlayerTextDrawSetProportional(playerid, phone_topo_text_main[playerid], true);
    PlayerTextDrawSetSelectable(playerid, phone_topo_text_main[playerid], true);

    // Barra de rolagem
    phone_scrollbar[playerid] = CreatePlayerTextDraw(playerid, 507.000000, 212.000000, "_");
    PlayerTextDrawFont(playerid, phone_scrollbar[playerid], TEXT_DRAW_FONT_0);
    PlayerTextDrawLetterSize(playerid, phone_scrollbar[playerid], 0.612500, 21.699958);
    PlayerTextDrawTextSize(playerid, phone_scrollbar[playerid], 506.000000, 31.000000);
    PlayerTextDrawSetOutline(playerid, phone_scrollbar[playerid], 1);
    PlayerTextDrawSetShadow(playerid, phone_scrollbar[playerid], 0);
    PlayerTextDrawAlignment(playerid, phone_scrollbar[playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, phone_scrollbar[playerid], 255);
    PlayerTextDrawBackgroundColor(playerid, phone_scrollbar[playerid], 255);
    PlayerTextDrawBoxColor(playerid, phone_scrollbar[playerid], 186);
    PlayerTextDrawUseBox(playerid, phone_scrollbar[playerid], true);
    PlayerTextDrawSetProportional(playerid, phone_scrollbar[playerid], true);
    PlayerTextDrawSetSelectable(playerid, phone_scrollbar[playerid], false);

    // -----------------------------------
    // Botão pesquisar:

    // Texto (procurar conversa):
    phone_text_search[playerid] = CreatePlayerTextDraw(playerid, 432.000000, 230.000000, "O  Pesquisar"); // Padrão (manter "O" e 2 espaços)
    PlayerTextDrawFont(playerid, phone_text_search[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, phone_text_search[playerid], 0.162496, 0.800005);
    PlayerTextDrawTextSize(playerid, phone_text_search[playerid], 7.500000, 37.500000);
    PlayerTextDrawSetOutline(playerid, phone_text_search[playerid], 1);
    PlayerTextDrawSetShadow(playerid, phone_text_search[playerid], 0);
    PlayerTextDrawAlignment(playerid, phone_text_search[playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, phone_text_search[playerid], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, phone_text_search[playerid], 0);
    PlayerTextDrawBoxColor(playerid, phone_text_search[playerid], -246);
    PlayerTextDrawUseBox(playerid, phone_text_search[playerid], false);
    PlayerTextDrawSetProportional(playerid, phone_text_search[playerid], true);
    PlayerTextDrawSetSelectable(playerid, phone_text_search[playerid], true);

    // WhatsApp - Navbar (Notificações)
    for (new loop; loop < sizeof(phone_notify_whatsmain_text); loop++) {
        phone_notify_whatsmain_text[loop][playerid] = CreatePlayerTextDraw(playerid, 429.000000 + (53.0 * loop), 393.500000, "_");
        PlayerTextDrawFont(playerid, phone_notify_whatsmain_text[loop][playerid], TEXT_DRAW_FONT_1);
        PlayerTextDrawLetterSize(playerid, phone_notify_whatsmain_text[loop][playerid], 0.083333, 0.400000);
        PlayerTextDrawTextSize(playerid, phone_notify_whatsmain_text[loop][playerid], 502.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, phone_notify_whatsmain_text[loop][playerid], 0);
        PlayerTextDrawSetShadow(playerid, phone_notify_whatsmain_text[loop][playerid], 0);
        PlayerTextDrawAlignment(playerid, phone_notify_whatsmain_text[loop][playerid], TEXT_DRAW_ALIGN_CENTER);
        PlayerTextDrawColor(playerid, phone_notify_whatsmain_text[loop][playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, phone_notify_whatsmain_text[loop][playerid], -1061109505);
        PlayerTextDrawBoxColor(playerid, phone_notify_whatsmain_text[loop][playerid], 50);
        PlayerTextDrawUseBox(playerid, phone_notify_whatsmain_text[loop][playerid], false);
        PlayerTextDrawSetProportional(playerid, phone_notify_whatsmain_text[loop][playerid], true);
        PlayerTextDrawSetSelectable(playerid, phone_notify_whatsmain_text[loop][playerid], false);
    }

    // WhatsApp - Tela principal:

    for (new loop; loop < MAX_LINES_WHATS_MSG; loop++) {

        // Texto da última mensagem
        // Caso seja o remetente (   Voce: Ok!) Espaço padrão <
        phone_whats_main_msg_ptext[loop][playerid] = CreatePlayerTextDraw(playerid, 430.000000, 266.0 + (26.0 * loop), "_");
        PlayerTextDrawFont(playerid, phone_whats_main_msg_ptext[loop][playerid], TEXT_DRAW_FONT_1);
        PlayerTextDrawLetterSize(playerid, phone_whats_main_msg_ptext[loop][playerid], 0.125000, 0.600000);
        PlayerTextDrawTextSize(playerid, phone_whats_main_msg_ptext[loop][playerid], 502.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, phone_whats_main_msg_ptext[loop][playerid], 0);
        PlayerTextDrawSetShadow(playerid, phone_whats_main_msg_ptext[loop][playerid], 0);
        PlayerTextDrawAlignment(playerid, phone_whats_main_msg_ptext[loop][playerid], TEXT_DRAW_ALIGN_LEFT);
        PlayerTextDrawColor(playerid, phone_whats_main_msg_ptext[loop][playerid], 1296911871);
        PlayerTextDrawBackgroundColor(playerid, phone_whats_main_msg_ptext[loop][playerid], -1061109505);
        PlayerTextDrawBoxColor(playerid, phone_whats_main_msg_ptext[loop][playerid], 50);
        PlayerTextDrawUseBox(playerid, phone_whats_main_msg_ptext[loop][playerid], false);
        PlayerTextDrawSetProportional(playerid, phone_whats_main_msg_ptext[loop][playerid], true);
        PlayerTextDrawSetSelectable(playerid, phone_whats_main_msg_ptext[loop][playerid], false);

        // Nome dos jogadores da mensagem:
        phone_whats_main_photo_msg[loop][playerid] = CreatePlayerTextDraw(playerid, 430.000000, 257.000000 + (26.0 * loop), "-");
        PlayerTextDrawFont(playerid, phone_whats_main_photo_msg[loop][playerid], TEXT_DRAW_FONT_1);
        PlayerTextDrawLetterSize(playerid, phone_whats_main_photo_msg[loop][playerid], 0.208333, 0.949998);
        PlayerTextDrawTextSize(playerid, phone_whats_main_photo_msg[loop][playerid], 490.500000, 17.000000);
        PlayerTextDrawSetOutline(playerid, phone_whats_main_photo_msg[loop][playerid], 0);
        PlayerTextDrawSetShadow(playerid, phone_whats_main_photo_msg[loop][playerid], 0);
        PlayerTextDrawAlignment(playerid, phone_whats_main_photo_msg[loop][playerid], TEXT_DRAW_ALIGN_LEFT);
        PlayerTextDrawColor(playerid, phone_whats_main_photo_msg[loop][playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, phone_whats_main_photo_msg[loop][playerid], -1061109505);
        PlayerTextDrawBoxColor(playerid, phone_whats_main_photo_msg[loop][playerid], 50);
        PlayerTextDrawUseBox(playerid, phone_whats_main_photo_msg[loop][playerid], false);
        PlayerTextDrawSetProportional(playerid, phone_whats_main_photo_msg[loop][playerid], true);
        PlayerTextDrawSetSelectable(playerid, phone_whats_main_photo_msg[loop][playerid], true);

        // Foto do perfil dos jogadores na mensagem:
        phone_whats_profile_photo[loop][playerid] = CreatePlayerTextDraw(playerid, 405.000000, 257.0 + (loop * 25.0), "Preview_Model");
        PlayerTextDrawFont(playerid, phone_whats_profile_photo[loop][playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
        PlayerTextDrawLetterSize(playerid, phone_whats_profile_photo[loop][playerid], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, phone_whats_profile_photo[loop][playerid], 23.000000, 19.000000);
        PlayerTextDrawSetOutline(playerid, phone_whats_profile_photo[loop][playerid], 0);
        PlayerTextDrawSetShadow(playerid, phone_whats_profile_photo[loop][playerid], 0);
        PlayerTextDrawAlignment(playerid, phone_whats_profile_photo[loop][playerid], TEXT_DRAW_ALIGN_LEFT);
        PlayerTextDrawColor(playerid, phone_whats_profile_photo[loop][playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, phone_whats_profile_photo[loop][playerid], 0);
        PlayerTextDrawBoxColor(playerid, phone_whats_profile_photo[loop][playerid], 255);
        PlayerTextDrawUseBox(playerid, phone_whats_profile_photo[loop][playerid], false);
        PlayerTextDrawSetProportional(playerid, phone_whats_profile_photo[loop][playerid], true);
        PlayerTextDrawSetSelectable(playerid, phone_whats_profile_photo[loop][playerid], false);
        PlayerTextDrawSetPreviewModel(playerid, phone_whats_profile_photo[loop][playerid], 0);
        PlayerTextDrawSetPreviewRot(playerid, phone_whats_profile_photo[loop][playerid], 0.000000, 0.000000, 0.000000, 0.789999);
        PlayerTextDrawSetPreviewVehCol(playerid, phone_whats_profile_photo[loop][playerid], 1, 1);

        // Texto da notificação informando a quantidade de mensagem não lida
        phone_whats_text_notify[loop][playerid] = CreatePlayerTextDraw(playerid, 501.500000, 265.500000 + (26.0 * loop), "_");
        PlayerTextDrawFont(playerid, phone_whats_text_notify[loop][playerid], TEXT_DRAW_FONT_1);
        PlayerTextDrawLetterSize(playerid, phone_whats_text_notify[loop][playerid], 0.083333, 0.400000);
        PlayerTextDrawTextSize(playerid, phone_whats_text_notify[loop][playerid], 502.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, phone_whats_text_notify[loop][playerid], 0);
        PlayerTextDrawSetShadow(playerid, phone_whats_text_notify[loop][playerid], 0);
        PlayerTextDrawAlignment(playerid, phone_whats_text_notify[loop][playerid], TEXT_DRAW_ALIGN_CENTER);
        PlayerTextDrawColor(playerid, phone_whats_text_notify[loop][playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, phone_whats_text_notify[loop][playerid], -1061109505);
        PlayerTextDrawBoxColor(playerid, phone_whats_text_notify[loop][playerid], 50);
        PlayerTextDrawUseBox(playerid, phone_whats_text_notify[loop][playerid], false);
        PlayerTextDrawSetProportional(playerid, phone_whats_text_notify[loop][playerid], true);
        PlayerTextDrawSetSelectable(playerid, phone_whats_text_notify[loop][playerid], false);

        // Hora da ultima mensagem
        phone_whats_msg_date[loop][playerid] = CreatePlayerTextDraw(playerid, 505.000000, 255.000000 + (26.0 * loop), "--:--");
        PlayerTextDrawFont(playerid, phone_whats_msg_date[loop][playerid], TEXT_DRAW_FONT_2);
        PlayerTextDrawLetterSize(playerid, phone_whats_msg_date[loop][playerid], 0.095830, 0.650004);
        PlayerTextDrawTextSize(playerid, phone_whats_msg_date[loop][playerid], 507.000000, 6.000000);
        PlayerTextDrawSetOutline(playerid, phone_whats_msg_date[loop][playerid], 0);
        PlayerTextDrawSetShadow(playerid, phone_whats_msg_date[loop][playerid], 0);
        PlayerTextDrawAlignment(playerid, phone_whats_msg_date[loop][playerid], TEXT_DRAW_ALIGN_RIGHT);
        PlayerTextDrawColor(playerid, phone_whats_msg_date[loop][playerid], 1097458175);
        PlayerTextDrawBackgroundColor(playerid, phone_whats_msg_date[loop][playerid], 255);
        PlayerTextDrawBoxColor(playerid, phone_whats_msg_date[loop][playerid], 186);
        PlayerTextDrawUseBox(playerid, phone_whats_msg_date[loop][playerid], false);
        PlayerTextDrawSetProportional(playerid, phone_whats_msg_date[loop][playerid], true);
        PlayerTextDrawSetSelectable(playerid, phone_whats_msg_date[loop][playerid], false);

        // Mensagem lida? (Caso seja o remetente)
        /*phone_whats_msg_read_ptext[loop][playerid] = CreatePlayerTextDraw(playerid, 434.000000, 319.000000, "VV");
        PlayerTextDrawFont(playerid, phone_whats_msg_read_ptext[loop][playerid], 2);
        PlayerTextDrawLetterSize(playerid, phone_whats_msg_read_ptext[loop][playerid], 0.091664, 0.400000);
        PlayerTextDrawTextSize(playerid, phone_whats_msg_read_ptext[loop][playerid], 502.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, phone_whats_msg_read_ptext[loop][playerid], 0);
        PlayerTextDrawSetShadow(playerid, phone_whats_msg_read_ptext[loop][playerid], 0);
        PlayerTextDrawAlignment(playerid, phone_whats_msg_read_ptext[loop][playerid], TEXT_DRAW_ALIGN_RIGHT);
        PlayerTextDrawColor(playerid, phone_whats_msg_read_ptext[loop][playerid], 1097458175);
        PlayerTextDrawBackgroundColor(playerid, phone_whats_msg_read_ptext[loop][playerid], -1061109505);
        PlayerTextDrawBoxColor(playerid, phone_whats_msg_read_ptext[loop][playerid], 50);
        PlayerTextDrawUseBox(playerid, phone_whats_msg_read_ptext[loop][playerid], false);
        PlayerTextDrawSetProportional(playerid, phone_whats_msg_read_ptext[loop][playerid], true);
        PlayerTextDrawSetSelectable(playerid, phone_whats_msg_read_ptext[loop][playerid], false);*/
    }

    // Backgroud - WhatsApp Messages
    background_whats_messages[0][playerid] = CreatePlayerTextDraw(playerid, 407.000000, 211.000000, "_");
    PlayerTextDrawFont(playerid, background_whats_messages[0][playerid], TEXT_DRAW_FONT_0);
    PlayerTextDrawLetterSize(playerid, background_whats_messages[0][playerid], 0.600000, 2.050002);
    PlayerTextDrawTextSize(playerid, background_whats_messages[0][playerid], 507.000000, 38.500000);
    PlayerTextDrawSetOutline(playerid, background_whats_messages[0][playerid], 1);
    PlayerTextDrawSetShadow(playerid, background_whats_messages[0][playerid], 0);
    PlayerTextDrawAlignment(playerid, background_whats_messages[0][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, background_whats_messages[0][playerid], 255);
    PlayerTextDrawBackgroundColor(playerid, background_whats_messages[0][playerid], 255);
    PlayerTextDrawBoxColor(playerid, background_whats_messages[0][playerid], 186);
    PlayerTextDrawUseBox(playerid, background_whats_messages[0][playerid], true);
    PlayerTextDrawSetProportional(playerid, background_whats_messages[0][playerid], true);

    background_whats_messages[1][playerid] = CreatePlayerTextDraw(playerid, 407.000000, 229.000000, "XOXOXOXOXOXO~n~XOXOXOXOXOXO~n~XOXOXOXOXOXO~n~XOXOXOXOXOXO~n~XOXOXOXOXOXO~n~XOXOXOXOXOXO~n~XOXOXOXOXOXO~n~XOXOXOXOXOXO~n~");
    PlayerTextDrawFont(playerid, background_whats_messages[1][playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawLetterSize(playerid, background_whats_messages[1][playerid], 0.291666, 2.249999);
    PlayerTextDrawTextSize(playerid, background_whats_messages[1][playerid], 405.000000, 22.000000);
    PlayerTextDrawSetOutline(playerid, background_whats_messages[1][playerid], 0);
    PlayerTextDrawSetShadow(playerid, background_whats_messages[1][playerid], 0);
    PlayerTextDrawAlignment(playerid, background_whats_messages[1][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, background_whats_messages[1][playerid], 40);
    PlayerTextDrawBackgroundColor(playerid, background_whats_messages[1][playerid], 255);
    PlayerTextDrawBoxColor(playerid, background_whats_messages[1][playerid], 50);
    PlayerTextDrawUseBox(playerid, background_whats_messages[1][playerid], false);
    PlayerTextDrawSetProportional(playerid, background_whats_messages[1][playerid], true);
}

stock WhatsApp_CreateHourMessage(playerid, tophourid, messageid, Float:layout_start_y) 
{
    PlayerTextDrawDestroy(playerid, tophour_whatsapp_message[tophourid][playerid]);

    tophour_whatsapp_message[tophourid][playerid] = CreatePlayerTextDraw(playerid, 457.000000, layout_start_y, "_");
    PlayerTextDrawFont(playerid, tophour_whatsapp_message[tophourid][playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawLetterSize(playerid, tophour_whatsapp_message[tophourid][playerid], 0.104166, 0.500005);
    PlayerTextDrawTextSize(playerid, tophour_whatsapp_message[tophourid][playerid], 503.500000, 26.500000);
    PlayerTextDrawAlignment(playerid, tophour_whatsapp_message[tophourid][playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColor(playerid, tophour_whatsapp_message[tophourid][playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, tophour_whatsapp_message[tophourid][playerid], 255);
    PlayerTextDrawBoxColor(playerid, tophour_whatsapp_message[tophourid][playerid], 134);
    PlayerTextDrawUseBox(playerid, tophour_whatsapp_message[tophourid][playerid], true);
    PlayerTextDrawSetProportional(playerid, tophour_whatsapp_message[tophourid][playerid], true);

    PlayerTextDrawSetString(playerid, tophour_whatsapp_message[tophourid][playerid], WhatsApp_GetDateMessageF(playerid, messageid));

    PlayerTextDrawShow(playerid, tophour_whatsapp_message[tophourid][playerid]);

    return 1;
}

stock WhatsApp_CreateMessage(playerid, messageline, messageid, Float:box_pos_x, Float:layot_start_y, Float:box_msg_size)
{
    new Float:layout_start_y_hour;

    if (box_msg_size == 1.250) {
        layout_start_y_hour = 6.0;
    } else if (box_msg_size == 2.000) {
        layout_start_y_hour = 12.0;
    } else {
        layout_start_y_hour = 19.0;
    }

    box_whatsapp_message[messageline][playerid] = CreatePlayerTextDraw(playerid, box_pos_x, layot_start_y, "_");
    if (box_pos_x == 408.0) {
        PlayerTextDrawBoxColor(playerid, box_whatsapp_message[messageline][playerid], 909523199);
        PlayerTextDrawTextSize(playerid, box_whatsapp_message[messageline][playerid], 495.000000, 41.500000);
    } else {
        PlayerTextDrawBoxColor(playerid, box_whatsapp_message[messageline][playerid], 5392127);
        PlayerTextDrawTextSize(playerid, box_whatsapp_message[messageline][playerid], 505.500000, 41.500000);
    }
    PlayerTextDrawLetterSize(playerid, box_whatsapp_message[messageline][playerid], 0.612500, box_msg_size);
    PlayerTextDrawUseBox(playerid, box_whatsapp_message[messageline][playerid], true);
    PlayerTextDrawSetProportional(playerid, box_whatsapp_message[messageline][playerid], true);

    msg_whatsapp_message[messageline][playerid] = CreatePlayerTextDraw(playerid, box_pos_x + 0.5, layot_start_y - 2.0, "_");
    PlayerTextDrawFont(playerid, msg_whatsapp_message[messageline][playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, msg_whatsapp_message[messageline][playerid], 0.108332, 0.700000);
    if (box_pos_x == 408.0) {
        PlayerTextDrawTextSize(playerid, msg_whatsapp_message[messageline][playerid], 494.000000, box_msg_size + 3.0);
    } else {
        PlayerTextDrawTextSize(playerid, msg_whatsapp_message[messageline][playerid], 504.500000, box_msg_size + 3.0);
    }   
    PlayerTextDrawSetOutline(playerid, msg_whatsapp_message[messageline][playerid], 2);
    PlayerTextDrawSetShadow(playerid, msg_whatsapp_message[messageline][playerid], 0);
    PlayerTextDrawAlignment(playerid, msg_whatsapp_message[messageline][playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, msg_whatsapp_message[messageline][playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, msg_whatsapp_message[messageline][playerid], 0);
    PlayerTextDrawSetProportional(playerid, msg_whatsapp_message[messageline][playerid], true);
    PlayerTextDrawSetSelectable(playerid, msg_whatsapp_message[messageline][playerid], true);

    if (box_pos_x == 408.0) {
        hour_whatsapp_message[messageline][playerid] = CreatePlayerTextDraw(playerid, 489.000000, layot_start_y + layout_start_y_hour, "--:--");
    } else {
        hour_whatsapp_message[messageline][playerid] = CreatePlayerTextDraw(playerid, 498.000000, layot_start_y + layout_start_y_hour, "--:--");
    }
    PlayerTextDrawFont(playerid, hour_whatsapp_message[messageline][playerid], TEXT_DRAW_FONT_2);
    PlayerTextDrawLetterSize(playerid, hour_whatsapp_message[messageline][playerid], 0.095831, 0.600004);
    PlayerTextDrawSetOutline(playerid, hour_whatsapp_message[messageline][playerid], 0);
    PlayerTextDrawSetShadow(playerid, hour_whatsapp_message[messageline][playerid], 0);
    PlayerTextDrawAlignment(playerid, hour_whatsapp_message[messageline][playerid], TEXT_DRAW_ALIGN_RIGHT);
    PlayerTextDrawColor(playerid, hour_whatsapp_message[messageline][playerid], 1888449535);
    PlayerTextDrawBackgroundColor(playerid, hour_whatsapp_message[messageline][playerid], 255);
    PlayerTextDrawSetProportional(playerid, hour_whatsapp_message[messageline][playerid], true);

    PlayerTextDrawSetString(playerid, msg_whatsapp_message[messageline][playerid], WhatsApp_GetMessage(playerid, messageid));
    PlayerTextDrawSetString(playerid, hour_whatsapp_message[messageline][playerid], WhatsApp_GetHourMessage(playerid, messageid));

    PlayerTextDrawShow(playerid, box_whatsapp_message[messageline][playerid]);
    PlayerTextDrawShow(playerid, msg_whatsapp_message[messageline][playerid]);
    PlayerTextDrawShow(playerid, hour_whatsapp_message[messageline][playerid]);
}

stock WhatsApp_GetMessages(playerid) 
{
    new 
        Float:layout_size       = 17.450,
        Float:layout_start_y    = 391.00,
        Float:box_msg_size      = 1.250,
        Float:box_pos_x,
        Float:box_pos_y         = 16.0,

        tophourid,
        date_message_last[35],
        date_message[35],

        messageid = WhatsApp_GetPage(playerid)
    ;

    if (WhatsApp_GetMessagesTela(playerid) > 0) {
        for (new loop; loop < WhatsApp_GetMessagesTela(playerid); loop++) {
            PlayerTextDrawHide(playerid, box_whatsapp_message[loop][playerid]);
            PlayerTextDrawDestroy(playerid, box_whatsapp_message[loop][playerid]);
            PlayerTextDrawHide(playerid, msg_whatsapp_message[loop][playerid]);
            PlayerTextDrawDestroy(playerid, msg_whatsapp_message[loop][playerid]);
            PlayerTextDrawHide(playerid, hour_whatsapp_message[loop][playerid]);
            PlayerTextDrawDestroy(playerid, hour_whatsapp_message[loop][playerid]);
        }
    }

    for(new i; i < MAX_LINES_WHATS_MSG; i++) {

        format(date_message, sizeof(date_message), WhatsApp_GetDateMessageF(playerid, messageid));
        printf("%s %s", date_message, date_message_last);

        if (i != 0) {
            if (layout_size < 5.0) 
                break;

            if (strcmp(date_message, date_message_last) && !isnull(date_message) && !isnull(date_message_last)) {
                layout_start_y -= 5.0;
                layout_size -= (2.0 + 0.550);

                WhatsApp_CreateHourMessage(playerid, tophourid, messageid, layout_start_y);
                printf("WhatsApp_CreateHourMessage: %d %d %d %f", playerid, tophourid, messageid, layout_start_y);

                tophourid++;
            }
        }
        format(date_message_last, sizeof(date_message_last), WhatsApp_GetDateMessageF(playerid, messageid));

        if (strlen(WhatsApp_GetMessage(playerid, messageid)) > 56) {
            box_msg_size = 2.000;
            box_pos_y = 23.0;
        }
        if (strlen(WhatsApp_GetMessage(playerid, messageid)) > 92) {
            box_msg_size = 2.850;
            box_pos_y = 30.0;
        }

        if (WhatsApp_GetDestinatario(playerid, messageid) == 1) {
            box_pos_x = 408.0;
        } else {
            box_pos_x = 420.0;
        }

        if (layout_size < (box_msg_size + 0.550)) 
            break;

        layout_start_y -= box_pos_y;
        layout_size -= (box_msg_size + 0.550);

        WhatsApp_CreateMessage(playerid, i, messageid, box_pos_x, layout_start_y, box_msg_size);
        printf("WhatsApp_CreateMessage: %d %d %d %f %f %f", playerid, i, messageid, box_pos_x, layout_start_y, box_msg_size);

        WhatsApp_SetMessagesTela(playerid, messageid);
        messageid++;
    }
}