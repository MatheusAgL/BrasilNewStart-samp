static bool:GIFT_SUPREME = false;

CMD:caixinha(playerid)
{
    if (Player_GetCaixinha(playerid))
        return SendClientMessage(playerid, -1, "Você já pegou sua caixinha nesse Payday.");

    if (isInventoryFull(playerid))
	    return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

    if (Player_GetVIP(playerid) >= SOCIO_SUPREME) {
        GiftBox_Get(playerid);
        if (Player_GetVIP(playerid) >= SOCIO_EXTREME)
            GiftBox_Get(playerid);

        if (Holiday_Get()) {
            GiftBox_Get(playerid);
            if (Player_GetVIP(playerid) >= SOCIO_EXTREME)
                GiftBox_Get(playerid);

            SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você recebeu em dobro seus presentes por conta do feriado!");
        }
    } else if (!PlayerToPoint(5.0,playerid, 1479.1299,-1631.8226,14.7433)) {
        return SendClientMessage(playerid, -1, "Você precisa estar no local de presentes (Use: /gps).");
    } else {
        GiftBox_Get(playerid);

        if (Holiday_Get()) {
            GiftBox_Get(playerid);

            SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você recebeu em dobro seus presentes por conta do feriado!");
        }
    }
    Player_SetCaixinha(playerid, true);
    return 1;
}


stock GiftBox_Get(playerid)
{
	new rdon = random(70) + random(51);

	if (GIFT_SUPREME) {
		GiftBox_Give(playerid, ITEM_TYPE_CAIXAGIGANTE);
        GIFT_SUPREME = false;
	} else {
		switch(rdon) {
			case 86, 89, 94, 98: {
                GiftBox_Give(playerid, ITEM_TYPE_CAIXAGIGANTE);
			}
            case 87: {
                if (ContarJogadores() >= SERVER_PLAYER_META) {
                    GiftBox_Give(playerid, ITEM_TYPE_SACOLAPREVISOES); // Sacola de Previsões
                }
                else {
                    GiftBox_Give(playerid, ITEM_TYPE_CAIXAGIGANTE);
                }
            }
            case 100: {
                if (ContarJogadores() >= SERVER_PLAYER_META) {
                    GiftBox_Give(playerid, ITEM_TYPE_CAIXAPLATINA);
                } else {
                    GiftBox_Give(playerid, ITEM_TYPE_CAIXAGIGANTE); // Usado para caixas especiais
                }
            }
            case 3, 4: {
                GiftBox_Give(playerid, ITEM_TYPE_CAIXAGOLD);
			}
			case 5..15: {
				GiftBox_Give(playerid, ITEM_TYPE_CAIXAPEQUENA);
			}
			case 16..35: {
				GiftBox_Give(playerid, ITEM_TYPE_CAIXAMEDIA);
			}
			case 36..42: {
				GiftBox_Give(playerid, ITEM_TYPE_CAIXAGRANDE);
			}
			case 43..50: {
                GiftBox_Give(playerid, ITEM_TYPE_CAIXAGIGANTE);
			}
			case 51..60: {
                // Saco de Carnaval
                if (GetCurrentMonth() == 2) {
                    if (GetCurrentDay() >= 4 && GetCurrentDay() <= 10) {
                        GiftBox_Give(playerid, ITEM_MODEL_CARNAVAL_2024);
                    } else {
                        GiftBox_Give(playerid, ITEM_TYPE_CAIXAGRANDE);
                    }
                } else {
                    GiftBox_Give(playerid, ITEM_TYPE_CAIXAGRANDE);
                }
			}
			case 61..80: {
				GiftBox_Give(playerid, ITEM_TYPE_CAIXAMEDIA);
			}
            case 81..85: {
                GiftBox_Give(playerid, ITEM_TYPE_CAIXAGIGANTE);
            }
			default:
			{
				GiftBox_Give(playerid, ITEM_TYPE_CAIXAPEQUENA);
			}
		}
	}
	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Voce recebeu um item em seu inventario, pressione 'N' para verificar.");

	return 1;
}

stock GiftBox_Give(playerid, type_box, bool:local=true)
{
    new box_name[40];
    new box_model;
    new string[128];

	switch (type_box) {
		case ITEM_TYPE_CAIXAPEQUENA: {
            box_name = "Caixa Surpresa Pequena";
            box_model = 19054;
        }
        case ITEM_TYPE_CAIXAMEDIA: {
            box_name = "Caixa Surpresa Media";
            box_model = 19055;
        }
        case ITEM_TYPE_CAIXAGRANDE: { 
            box_name = "Caixa Surpresa Grande";
            box_model = 19056;
        }
        case ITEM_TYPE_CAIXAGIGANTE: {
            box_name = "Caixa Surpresa Gigante";
            box_model = 19058;
        }
        case ITEM_TYPE_CAIXAGOLD: {
            box_name = "{FEE73A}Caixa Surpresa Gold";
            box_model = 19057;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_CAIXAPLATINA: {
            box_name = "{017bff}Caixa Surpresa Supreme";
            box_model = 19918;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_CAIXALENDARIA: {
            box_name = "{8C52FF}Saco do {7ED957}Carnaval";
            box_model = ITEM_MODEL_CARNAVAL_2024;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_CAIXAREVOLTADO: {
            box_name = "{FF0000}Caixa Surpresa Revoltado";
            box_model = 2694;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_CAIXAPODEROSA: {
            box_name = "{00FF00}Caixa Surpresa Poderosa";
            box_model = 19918;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_SACOLAARRAIA: {
            box_name = "{FFD700}Sacola Arraia";
            box_model = 2663;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_SACOLACOMUNISTA: {
            box_name = "{E41B17}Sacola Comunista";
            box_model = 2663;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_SACOLAPATRIOTA: {
            box_name = "{0000FF}Sacola Patriota";
            box_model = 2663;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_SACOLABOOSTERS: {
            box_name = "{29DFFF}Sacola Boosters";
            box_model = 2420;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_CAIXABRUNO: {
            box_name = "{A020F0}Caixa Aniversario Bruno";
            box_model = 19918;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_CAIXA_ITEM_VEICULAR: {
            box_name = "{33C7CC}Caixa Surpresa Item Veicular";
            box_model = 19572;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
		case ITEM_TYPE_HALLOWEEN: {
            box_name = "{E68510}Caixa Surpresa Halloween";
            box_model = 6865;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
		case ITEM_TYPE_NATAL: {
            box_name = "{C93F3C}Caixa Surpresa Natal";
            box_model = 19057;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_MALETAJOAO: {
            box_name = "{4169E1}Maleta do Joao";
            box_model = 1210;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
		case ITEM_TYPE_REVEILLON: {
            box_name = "{FFF1C9}Caixa Surpresa Reveillon";
            box_model = 19057;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_ORGMES: {
            box_name = "Caixa Organizacao Mes";
            box_model = 19918;
        }
        case ITEM_TYPE_CAIXASTAFF: {
            box_name = "{FF1493}Caixa Destaque Staff";
            box_model = 19918;
        }
        case ITEM_TYPE_CAIXAMESADM: {
            box_name = "{FFFF00}Caixa Admin do Mes";
            box_model = 19918;
        }
        case ITEM_TYPE_ULTIMATE: {
            box_name = "Sacola Extreme";
            box_model = 2663;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_SACOLAPREVISOES: {
            box_name = "Sacola de Previsoes";
            box_model = 19573;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_MOCHILAPREMIADA: {
            box_name = "Mochila Premiada";
            box_model = 371;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        case ITEM_TYPE_SACOLAFERIAS: {
            box_name = "Sacola de Ferias";
            box_model = 2803;

            if (local) {
                format(string, sizeof(string), "PRESENTE -> %s recebeu um(a) %s"C_ORANGE" | Local de presentes /gps", PlayerName[playerid], box_name);
                SendClientMessageToAll(COLOR_ORANGE, string);
            }
        }
        default: {
            box_name = "Caixa vencida";
            box_model = 2972;
        }
	}

    format(string, sizeof(string), "PRESENTE -> Você recebeu um(a) %s"C_ORANGE".", box_name);
    SendClientMessage(playerid, COLOR_ORANGE, string);

    new box_item_name[30];
    if(box_name[0] == '{' && box_name[7] == '}')
        strmid(box_item_name, box_name, 8, strlen(box_name), 255);
    else
        format(box_item_name, sizeof(box_item_name), box_name);

    if (IsPlayerHaveItem(playerid, type_box) && IsPlayerHaveItemColor(playerid, 0, 0)) {
        addQuantiaItem(playerid, type_box, box_model, 1, box_item_name, 0, 0);
    }
	else {
        givePlayerItem(playerid, type_box, box_model, 1, box_item_name);
    }

    format(string, sizeof(string), "PRESENTE -> * %s recebeu um(a) %s", PlayerName[playerid], box_item_name);
    server_log("acaixa", string);

    format(string, sizeof(string), "~r~~h~~h~+1 ~w~%s", box_item_name);
    ShowPlayerPopupHUD(playerid, "NOVO ITEM RECEBIDO", string, 6000);

    return box_name;
}