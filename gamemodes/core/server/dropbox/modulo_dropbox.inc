/**--------------------------------------------------------------------------**\
 ______ ______  ______     __  ______  ______  ______     ______  __  ______ __  __
/\  == /\  == \/\  __ \   /\ \/\  ___\/\  ___\/\__  _\   /\  ___\/\ \/\__  _/\ \_\ \
\ \  _-\ \  __<\ \ \/\ \ _\_\ \ \  __\\ \ \___\/_/\ \/   \ \ \___\ \ \/_/\ \\ \____ \
 \ \_\  \ \_\ \_\ \_____/\_____\ \_____\ \_____\ \ \_\    \ \_____\ \_\ \ \_\\/\_____\
  \/_/   \/_/ /_/\/_____\/_____/\/_____/\/_____/  \/_/     \/_____/\/_/  \/_/ \/_____/

						 ==========================
		                    Brasil Project City
                              ® 2012 - 2016
                             Módulo: Drop de caixas
						 ==========================

\**--------------------------------------------------------------------------**/

#define MAX_DROP_BOX    (20)

enum dropBoxEnum {

	boxPickup,
	boxType,
	boxIgnore,
	Text3D:boxLabel,
}
new DropBoxInfo[MAX_DROP_BOX][dropBoxEnum];
new Iterator:IterBox<MAX_DROP_BOX>;

stock createDropBox(playerid) {

	new rdon = random(20);

	if (rdon == 10) {

		new Float:pX, Float:pY, Float:pZ;
		GetPlayerPos(playerid, pX, pY, pZ);

		new boxrandom = random(5);
		return DropBoxType(boxrandom+1, pX, pY, pZ, playerid);
	}

	return 0;
}

stock DropBoxType(type, Float:pX, Float:pY, Float:pZ, ignoreid = INVALID_PLAYER_ID) {

	new id = Iter_Free(IterBox);

	if ( id >= 0 ) {

		Iter_Add(IterBox, id);

		new string_box[144];

		pX += randomfloat(3.0) - randomfloat(3.0);
		pY += randomfloat(3.0) - randomfloat(3.0);

        DropBoxInfo[id][boxIgnore] = ignoreid;

		new MapZone:zone = GetMapZoneAtPoint2D(pX, pY);
		new zone_name[MAX_MAP_ZONE_NAME];
		GetMapZoneName(zone, zone_name);

        SoundToAll(41601);

		switch(type) {

		    case 1: {

		        format(string_box, sizeof (string_box), "[{FFFFFF}Caixa Surpresa{00AAFF}] Uma caixa surpresa {FFFFFF}PEQUENA{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nCaixa Surpresa {FFFFFF}Pequena", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_CAIXAPEQUENA;
                DropBoxInfo[id][boxPickup] = CreateDynamicPickup(19054, 24, pX, pY, pZ);
		    }
		    case 2: {

		        format(string_box, sizeof (string_box), "[{FFFFFF}Caixa Surpresa{00AAFF}] Uma caixa surpresa {FFFFFF}MÉDIA{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nCaixa Surpresa {FFFFFF}Média", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_CAIXAMEDIA;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(19055, 24, pX, pY, pZ);
		    }
		    case 3: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Caixa Surpresa{00AAFF}] Uma caixa surpresa {FFFFFF}GRANDE{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nCaixa Surpresa {FFFFFF}Grande", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_CAIXAGRANDE;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(19056, 24, pX, pY, pZ);
		    }
		    case 4: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Caixa Surpresa{00AAFF}] Uma caixa surpresa {FFFFFF}GIGANTE{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nCaixa Surpresa {FFFFFF}Gigante", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_CAIXAGIGANTE;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(19058, 24, pX, pY, pZ);
		    }
			case 5: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Caixa Surpresa{00AAFF}] Uma caixa surpresa {FEE73A}GOLD{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nCaixa Surpresa {FEE73A}GOLD", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_CAIXAGOLD;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(19057, 24, pX, pY, pZ);
		    }
			case 6: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Caixa Surpresa{00AAFF}] Uma caixa surpresa {017bff}SUPREME{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nCaixa Surpresa {017bff}SUPREME", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_CAIXAPLATINA;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(19918, 24, pX, pY, pZ);
		    }
			case 7: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Caixa Surpresa{00AAFF}] Uma caixa surpresa {FF0000}REVOLTADO{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nCaixa Surpresa {FF0000}REVOLTADO", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_CAIXAREVOLTADO;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(2694, 24, pX, pY, pZ);
		    }
			case 8: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Caixa Surpresa{00AAFF}] Uma caixa surpresa {00FF00}PODEROSA{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nCaixa Surpresa {00FF00}PODEROSA", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_CAIXAPODEROSA;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(19918, 24, pX, pY, pZ);
		    }
			case 9: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Sacola{00AAFF}] Uma sacola {FFD700}ARRAIÁ{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nSacola {FFD700}ARRAIA", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_SACOLAARRAIA;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(2663, 24, pX, pY, pZ);
		    }
			case 10: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Sacola{00AAFF}] Uma sacola {E41B17}COMUNISTA{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nSacola {E41B17}COMUNISTA", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_SACOLACOMUNISTA;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(2663, 24, pX, pY, pZ);
		    }
			case 11: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Sacola{00AAFF}] Uma sacola {0000FF}PATRIOTA{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nSacola {0000FF}PATRIOTA", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_SACOLAPATRIOTA;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(2663, 24, pX, pY, pZ);
		    }
			case 12: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Caixa Aniversário{00AAFF}] Uma caixa aniversário {A020F0}BRUNO{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nCaixa Aniversario {A020F0}Bruno", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_CAIXABRUNO;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(2694, 24, pX, pY, pZ);
		    }
			case 13: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Caixa Surpresa{00AAFF}] Uma caixa surpresa {E68510}HALLOWEEN{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nCaixa Surpresa {E68510}Halloween", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_HALLOWEEN;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(2694, 24, pX, pY, pZ);
		    }
			case 14: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Caixa Surpresa{00AAFF}] Uma caixa surpresa {C93F3C}NATAL{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\nCaixa Surpresa {C93F3C}Natal", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_NATAL;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(19057, 24, pX, pY, pZ);
		    }
			case 15: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}Maleta{00AAFF}] Uma {4169E1}maleta{FFFFFF} do Joao{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\n{4169E1}Maleta {FFFFFF}do Joao", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_MALETAJOAO;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(1210, 24, pX, pY, pZ);
		    }
			case 16: {

 		        format(string_box, sizeof (string_box), "[{FFFFFF}BOOSTER{00AAFF}] Uma {4169E1}Sacola{29DFFF} Boosters{00AAFF} foi derrubada em: %s",  zone_name);
		        SendClientMessageToAll(0x00AAFFFF, string_box);

		        DropBoxInfo[id][boxLabel]  = CreateDynamic3DTextLabel("•\n{4169E1}Sacola {29DFFF}Boosters", 0x00AAFFF5, pX, pY, pZ + 0.5, 15.0);
		        DropBoxInfo[id][boxType]   = ITEM_TYPE_SACOLABOOSTERS;
		        DropBoxInfo[id][boxPickup] = CreateDynamicPickup(2420, 24, pX, pY, pZ);
		    }
  		}
  		return 1;
	}
	return 0;
}

stock GetBoxNameByType(type) {

	new namebox[45];

	switch (type) {

	    case ITEM_TYPE_CAIXAPEQUENA: strcat(namebox, "Caixa Surpresa Pequena");
	    case ITEM_TYPE_CAIXAMEDIA:   strcat(namebox, "Caixa Surpresa Média");
	    case ITEM_TYPE_CAIXAGRANDE:  strcat(namebox, "Caixa Surpresa Grande");
	    case ITEM_TYPE_CAIXAGIGANTE: strcat(namebox, "Caixa Surpresa Gigante");
	    case ITEM_TYPE_CAIXAGOLD:    strcat(namebox, "Caixa Surpresa Gold");
	    case ITEM_TYPE_CAIXAPLATINA: strcat(namebox, "Caixa Surpresa Supreme");
		case ITEM_TYPE_CAIXAREVOLTADO: strcat(namebox, "Caixa Surpresa Revoltado");
		case ITEM_TYPE_CAIXAPODEROSA:  strcat(namebox, "Caixa Surpresa Poderosa");
		case ITEM_TYPE_HALLOWEEN: 	 strcat(namebox, "Caixa Surpresa Halloween");
		case ITEM_TYPE_NATAL: 		 strcat(namebox, "Caixa Surpresa Natal");
	    case ITEM_TYPE_KID: 	     strcat(namebox, "Caixa Surpresa KID");
		case ITEM_TYPE_CAIXA_ITEM_VEICULAR: strcat(namebox, "Caixa Surpresa Item Veicular");
		case ITEM_TYPE_SACOLAARRAIA: strcat(namebox, "Sacola Arraiá");
		case ITEM_TYPE_SACOLACOMUNISTA: strcat(namebox, "Sacola Comunista");
		case ITEM_TYPE_SACOLAPATRIOTA: strcat(namebox, "Sacola Patriota");
		case ITEM_TYPE_CAIXABRUNO:	strcat(namebox, "Caixa Aniversário Bruno");
		case ITEM_TYPE_MALETAJOAO:	strcat(namebox, "Maleta do Joao");		
		case ITEM_TYPE_SACOLABOOSTERS:	strcat(namebox, "Sacola Boosters");
	    default: strcat(namebox, "Caixa Surpresa Desconhecida");
	}
	return namebox;
}

stock bxOnPlayerPickUpDynamicPickup(playerid, pickupid) {

	foreach(new box : IterBox) {

	    if (pickupid == DropBoxInfo[box][boxPickup]) {

	        if (isInventoryFull(playerid))
				return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

	        if ( DropBoxInfo[box][boxIgnore] == playerid ) {
	            return SendClientMessage(playerid, COLOR_GREY, " Você não pode pegar esta caixa, pois você mesmo a derrubou!");
	        }

		    new Float:pX, Float:pY, Float:pZ;
		    GetPlayerPos(playerid, pX, pY, pZ);

			new MapZone:zone = GetMapZoneAtPoint2D(pX, pY);
			new zone_name[MAX_MAP_ZONE_NAME];
			GetMapZoneName(zone, zone_name);

	        new string[144];

	        format(string, sizeof string, "[{FFFFFF}Caixa Surpresa{00AAFF}] %s pegou uma {FFFFFF}%s{00AAFF} que estava caída em: %s", PlayerName[playerid], GetBoxNameByType(DropBoxInfo[box][boxType]), zone_name);
	        SendClientMessageToAll(0x00AAFFFF, string);
	        server_log("acaixa", string);
	        
	        SoundToAll(41601);

	        GiftBox_Give(playerid, DropBoxInfo[box][boxType], false);

	        Iter_Remove(IterBox, box);

	        DestroyDynamicPickup(DropBoxInfo[box][boxPickup]);
	        DestroyDynamic3DTextLabel(DropBoxInfo[box][boxLabel]);

	        DropBoxInfo[box][boxPickup] = -1;
	        DropBoxInfo[box][boxLabel]  = Text3D:-1;
	        return 1;
	    }
	}

	return 0;
}

CMD:derrubarcaixatx1(playerid, params[]) {

	if (Admin_GetNivel(playerid) < SUB_DONO) {
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não tem autorização para usar este comando!");
	}

	new boxtype;

	if (sscanf(params, "d", boxtype) || (boxtype < 1 || boxtype > 16)) 
		return SendClientMessage(playerid, -1, "{FFFFFF}USO CORRETO: {00CCFF}/derrubarcaixa [1 - 16]");

	new Float:pX, Float:pY, Float:pZ;
 	GetPlayerPos(playerid, pX, pY, pZ);
	GetXYInFrontOfPlayer(playerid, pX, pY, 4.0);

	DropBoxType(boxtype, pX, pY, pZ);

	new string[128];

	format(string, sizeof(string), "%s, %s derrubou a caixa ID %s", Staff_GetPositionName(playerid), PlayerName[playerid], boxtype);
	server_log("dcaixa", string);

	return 1;
}

CMD:infocaixatx1(playerid, params[]) {
	//new string[128];
	MEGAString[0] = EOS;

	if (Admin_GetNivel(playerid) < SUB_DONO) {
	    return SendClientMessage(playerid, COLOR_LIGHTRED, "  Você não tem autorização para usar este comando!");
	}
	else {
		strcat(MEGAString, "\n"C_YELLOW"» LISTA DE DERRUBAR CAIXAS PARA DESENVOLVEDORES:\n\n");
		strcat(MEGAString,""C_WHITE"1 - Caixa Surpresa Pequena\n");
		strcat(MEGAString,""C_WHITE"2 - Caixa Surpresa Média\n");
		strcat(MEGAString,""C_WHITE"3 - Caixa Surpresa Grande\n");
		strcat(MEGAString,""C_WHITE"4 - Caixa Surpresa Gigante\n");
		strcat(MEGAString,""C_WHITE"5 - Caixa Surpresa {FEE73A}Gold{FFFFFF}\n");
		strcat(MEGAString,""C_WHITE"6 - Caixa Surpresa {017bff}Supreme{FFFFFF}\n");
		strcat(MEGAString,""C_WHITE"7 - Caixa Surpresa {FF0000}Revoltado{FFFFFF}\n");
		strcat(MEGAString,""C_WHITE"8 - Caixa Surpresa {00FF00}Poderosa{FFFFFF}\n");
		strcat(MEGAString,""C_WHITE"9 - Sacola {FFD700}Arraiá{FFFFFF}\n");
		strcat(MEGAString,""C_WHITE"10 - Sacola {E41B17}Comunista{FFFFFF}\n");
		strcat(MEGAString,""C_WHITE"11 - Sacola {0000FF}Eventos{FFFFFF}\n");
		strcat(MEGAString, ""C_WHITE"12 - Caixa Aniversário {A020F0}Bruno{FFFFFF}\n");
		strcat(MEGAString, ""C_WHITE"13 - Caixa Surpresa {A020F0}Halloween{FFFFFF}\n");
		strcat(MEGAString, ""C_WHITE"14 - Caixa Surpresa {C93F3C}Natal{FFFFFF}\n");
		strcat(MEGAString, ""C_WHITE"15 - {4169E1}Maleta {FFFFFF}do Joao\n");
		strcat(MEGAString, ""C_WHITE"16 - {4169E1}Sacola {29DFFF}Boosters\n");

		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, ""C_GRAY"Sistema de Derrubar Caixas - Lista", MEGAString, ""C_YELLOW"Fechar","");
	}

	return 1;
}