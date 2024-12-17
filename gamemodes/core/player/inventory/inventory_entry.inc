// ----------------------------------- NOMES SERVER ----------------------------------------------

#define			MAX_ITEM_INV_NAME			25
#define 		MAX_ITENS_INVENTARIO        (80)
#define			MAX_INV_SLOT_PERPAGE		20
#define 		MAX_DROP_ITENS              (800)
#define			MAX_PAGES_INVENTORY         (MAX_ITENS_INVENTARIO - MAX_INV_SLOT_PERPAGE) / MAX_INV_SLOT_PERPAGE
#define 		MAX_ITENS_TYPES_LIMIT       (110)
#define			MAX_INV_ITEM_SCREEN			15

// ----------------------- Colors:
#define			COLOR_COMBINE			0xB3F8BAFF
#define			C_COMBINE				"{B3F8BA}"
#define			COLOR_USE				0xB3C8F8FF
#define			C_USE					"{B3C8F8}"
#define			COLOR_SEPARE			0xF8CBB3FF
#define			C_SEPARE				"{F8CBB3}"
#define			COLOR_MOVE				0xF8F7B3FF
#define			C_MOVE					"{F8F7B3}"

// ----------------------------------- ITENS CONSUM�VEIS ----------------------------------------------


#define         ITEM_MODEL_CABECA			2908
#define         ITEM_MODEL_TRONCO			2907
#define         ITEM_MODEL_PERNA			2905
#define         ITEM_MODEL_BRACO			2906

#define         ITEM_MODEL_RESPAWNORG		1083
#define         ITEM_MODEL_PROCURADO	    1247
#define         ITEM_MODEL_BLINDAR_CARRO    954
#define         ITEM_MODEL_IRPARAHQ         1318
#define         ITEM_MODEL_NAMEVEH          953
#define         ITEM_MODEL_PALETA			18841
#define         ITEM_MODEL_PONTOS_ADVOGADO	1923
#define         ITEM_MODEL_ORGVIP			19347
#define         ITEM_MODEL_RESETAR_KD		11732
#define         ITEM_MODEL_SAIR_PRISAO		19302
#define         ITEM_MODEL_REPARAR_CARRO	7927
#define         ITEM_MODEL_ENCHER_TANQUE	3465

#define			ITEM_MODEL_SACO_GRAVIDO		371
#define			ITEM_MODEL_CARNAVAL_2024	19092

// ---------------------------------------------------------------------------------------------------

enum
{
									// ITEM TYPE        ITEM MODEL      QUANTIDADE      ITEM NOME               	ITEM COR/FUN��O             ITEM COR2/FUN��O2
	ITEM_TYPE_NONE,                 // 0		        0               0               N/A                         N/A                         N/A
	ITEM_TYPE_WEAPON,               // 1                modelid         muni��o	        (nome da arma)
	ITEM_TYPE_MACONHA,              // 2                2891	        gramas			Maconha
	ITEM_TYPE_COCAINA,              // 3                2891	        gramas			Cocaina
	ITEM_TYPE_CRACK,                // 4                2891	        gramas			Crack
	ITEM_TYPE_EXPLOSIVO,            // 5                1654	        quantidade	    Explosivo
	ITEM_TYPE_REMEDIO,              // 6                11738	        quantidade	    Remedio Grande
	ITEM_TYPE_REMEDIOP,             // 7                11736	        quantidade	    Remedio Pequeno
	ITEM_TYPE_GASOLINA,             // 8                1650            litros          Galao de Gasolina
	ITEM_TYPE_RADIO,                // 9                2226            quantidade      JBL
	ITEM_TYPE_DINHEIRO,             // 10               1212            quantidade      Dinheiro
	ITEM_TYPE_RESPEITO,             // 11               19941           quantidade      Respeito
	ITEM_TYPE_CONTRATO,             // 12               2894            quantidade      Contrato Hospitalar
	ITEM_TYPE_SKATE,                // 13               19878           quantidade      Skate
	ITEM_TYPE_COMIDA,               // 14               modelid         quantidade      (nome da comida)
	ITEM_TYPE_CELULAR,              // 15               19835         	quantidade      Coca-Cola
	ITEM_TYPE_MINA,                 // 16               19602         	quantidade      Mina Terrestre
	ITEM_TYPE_CAIXAPEQUENA,         // 17               19054         	quantidade      Caixa Surpresa Pequena
	ITEM_TYPE_CAIXAMEDIA,           // 18               19055         	quantidade      Caixa Surpresa Media
	ITEM_TYPE_CAIXAGRANDE,          // 19               19056         	quantidade      Caixa Surpresa Grande
	ITEM_TYPE_CAIXAGIGANTE,         // 20               19058         	quantidade      Caixa Surpresa Gigante
	ITEM_TYPE_MOTORISTA,            // 21               1581         	quantidade      Carteira de Motorista
	ITEM_TYPE_PILOTO,               // 21               1581         	quantidade      Licenca de Piloto
	ITEM_TYPE_MARUJO,               // 21               1581         	quantidade      Licenca Nautica
	ITEM_TYPE_NICK,					// 24               19792         	quantidade      Troca de Nick
	ITEM_TYPE_ACCESSORY, 			// 25               modelid        	quantidade      (nome do acess�rio) // Nitro 2x Veh. Inv (1010) // Nitro 1x Veh. Inv (1009)
	ITEM_TYPE_CAIXALENDARIA,		// 26               modelid        	quantidade      (nome da caixa lend�ria)
	ITEM_TYPE_OCULOS,				// 27               modelid        	quantidade      (nome do acess�rio)
	ITEM_TYPE_RELOGIO,				// 28               modelid        	quantidade      (nome do acess�rio)
	ITEM_TYPE_JETPACK,              // 29               370             quantidade      JetPack
	ITEM_TYPE_MEDKIT,               // 30               11736           quantidade      MedKit de chao
	ITEM_TYPE_HAMBURGER,            // 31               2880            quantidade      Hamburger
	ITEM_TYPE_FATIAPIZZA,           // 32               2881            quantidade      Fatia de Pizza
	ITEM_TYPE_BEBIDA,               // 33               modelid         quantidade      (nome da bebida)
	ITEM_TYPE_TRONCO,               // 34               modelid         quantidade      (nome do acess�rio)
	ITEM_TYPE_DEPOSITORY,           // 35               modelid         quantidade      (nome do b�u)
	ITEM_TYPE_CAIXAGOLD,            // 36               19057           quantidade      Caixa Surpresa Gold
	ITEM_TYPE_SKIN,                 // 37               modelid         quantidade      Skin modelid
	ITEM_TYPE_DECORACAO, 			// 38               980				quantidade      Portao
	ITEM_TYPE_GUNBOXP,              // 39               3013	        quantidade      Caixa de equipamentos P
	ITEM_TYPE_GUNBOXM,              // 40               2358	        quantidade      Caixa de equipamentos M
	ITEM_TYPE_GUNBOXG,              // 41               3014			quantidade      Caixa de equipamentos G
	ITEM_TYPE_CHAVEFENDA,           // 42               18644			quantidade      Chave de Fenda
	ITEM_TYPE_CHAVEBIELA,           // 43               18633           quantidade      Chave Biela
	ITEM_TYPE_CHAVEFIXA,            // 44               19627           quantidade      Chave Fixa
	ITEM_TYPE_NOTEBOOK,             // 45               19893           quantidade      Notebook
	ITEM_TYPE_CAPACETE,             // 46               modelid         quantidade      Capacete
	ITEM_TYPE_CAIXAPLATINA,         // 47               19918           quantidade      Caixa Surpresa Supreme
	ITEM_TYPE_GARRAFA,              // 48               1668            quantidade      Garrafa de agua
	ITEM_TYPE_DRONE, 				// 49 				modelid 		quantidade      (nome do ve�culo)
	ITEM_TYPE_AMOR, 				// 50 				1240 			quantidade      Caixa Surpresa Love
	ITEM_TYPE_COLETE, 				// 51
	ITEM_TYPE_REPAIR, 				// 52
	ITEM_TYPE_KID, 					// 53
	ITEM_TYPE_HALLOWEEN, 			// 54
	ITEM_TYPE_SACOLA, 				// 55 				modelid 		quantidade		(nome da sacola)
	ITEM_TYPE_REVEILLON, 			// 56				19057 			quantidade		Caixa_Surpresa_Reveillon
	ITEM_TYPE_ORGMES, 				// 57
	ITEM_TYPE_CARNAVAL, 			// 58 				19918 			quantidade		Caixa_Surpresa_Carnaval
	ITEM_TYPE_3ANOSBPS, 			// 59 				19918 			quantidade		Caixa_Surpresa_BPS
	ITEM_TYPE_NATAL, 				// 60
	ITEM_TYPE_KITCOP,				// 61
	ITEM_TYPE_KITSEXY, 				// 62
	ITEM_TYPE_GRANA, 				// 63
	ITEM_TYPE_COMIDACRU,			// 64
	ITEM_TYPE_LIXO,
	ITEM_TYPE_PASCOA, //66
	ITEM_TYPE_MELHORIA,
	ITEM_TYPE_ARRAIA, //68 /setariteminv 68 1240 1 ARRAIA
	ITEM_TYPE_PAPAI,
	ITEM_TYPE_CAIXAULTIMATE,
	ITEM_TYPE_SACOLATHEUS,
	ITEM_TYPE_PAO,
	ITEM_TYPE_CONSUMIVEL, 			// 73				18841			quantidade		Paleta (Arco-Iris)
	ITEM_TYPE_CARNAVALP,
	ITEM_TYPE_BPSPRO,
	ITEM_TYPE_PASCOAP,
	ITEM_TYPE_MOTHER,
	ITEM_TYPE_MOTHERP,
	ITEM_TYPE_SEMENTE,
	ITEM_TYPE_REGADOR,
	ITEM_TYPE_SEMIPRONTA,
	ITEM_TYPE_LOVEP,
	ITEM_TYPE_COPA,
	ITEM_TYPE_COPAP,
	ITEM_TYPE_SACOLATHEUS_PLUS, //85
	ITEM_TYPE_ULTIMATE, 			//		86 2663 1 Sacola Ultimate
	ITEM_TYPE_HALLOWEEN_PLUS,         // 87 6865 1 Caixa Halloween Pro
	ITEM_TYPE_NATAL_PLUS,            // 88
	ITEM_TYPE_REVEILLON_PRO,         // 89
	ITEM_TYPE_ORGAO,
	ITEM_TYPE_SACOLAPREVISOES,          // 91
	ITEM_TYPE_SACOLAFERIAS,
	ITEM_TYPE_MOCHILAPREMIADA,           // 93
	ITEM_TYPE_HEROINA,
	ITEM_TYPE_METANFETAMINA,
	ITEM_TYPE_VEH_ACCESSORY, // 96
	ITEM_TYPE_CAIXA_ITEM_VEICULAR, // 97 - 19572
	ITEM_TYPE_MATERIAL, // 98
	ITEM_TYPE_PANEL, // 99
	ITEM_TYPE_CAIXAREVOLTADO, // 100 - Caixa Surpresa Revoltado
	ITEM_TYPE_CAIXAPODEROSA, // 101 - Caixa Surpresa Poderosa (Dia 3 de Julho)
	ITEM_TYPE_CAIXASTAFF, // 102 - Caixa Destaque Staff
	ITEM_TYPE_CAIXAMESADM, // 103 - Caixa Admin do M�s
	ITEM_TYPE_SACOLAARRAIA, // 104 - Sacola Arrai�
	ITEM_TYPE_SACOLACOMUNISTA, // 105 - Sacola Comunista
	ITEM_TYPE_SACOLAPATRIOTA, // 106 - Sacola Patriota
	ITEM_TYPE_CAIXABRUNO, // 107 - Caixa Anivers�rio Bruno
	ITEM_TYPE_SACOLABOOSTERS, // Sacola Boosters DC
	ITEM_TYPE_MALETAJOAO // 108 - Maleta do Jo�o
}

enum INVENTORY_ENUM
{
	item_id,
	item_valid,
	item_type,
	item_model,
	item_vender,
	item_nome[30],
	item_quantia,
	item_cor1,
	item_cor2,
}
new InventarioInfo[MAX_PLAYERS][MAX_ITENS_INVENTARIO][INVENTORY_ENUM];
new itensPlayer[MAX_ITENS_INVENTARIO][INVENTORY_ENUM];

enum DROP_ITEM_ENUM
{
	drop_valid,
	drop_type,
	drop_model,
	drop_quantia,
	drop_nome[30],
	drop_world,
	drop_house,
	drop_time,
	Float:drop_x,
	Float:drop_y,
	Float:drop_z,
	Text3D:drop_text,
	drop_object,
	drop_cor1,
	drop_cor2,
}
new DropItensInfo[MAX_DROP_ITENS][DROP_ITEM_ENUM];

enum INVENTORY_ACTION_ENUM {
	bool:inventory_open,
	inventory_page,
	item_selected,
};
new InventoryAction[MAX_PLAYERS][INVENTORY_ACTION_ENUM];

new PaletaColor1[MAX_PLAYERS];
new PaletaColor2[MAX_PLAYERS];

stock InvItem_SetSelected(playerid, selected)
	InventoryAction[playerid][item_selected] = selected;

stock InvItem_GetSelected(playerid)
	return InventoryAction[playerid][item_selected];

stock Inventory_SetPage(playerid, page)
	InventoryAction[playerid][inventory_page] = page;

stock Inventory_GetPage(playerid)
	return InventoryAction[playerid][inventory_page];

stock bool:Inventory_IsOpen(playerid)
	return InventoryAction[playerid][inventory_open];

stock Inventory_SetOpen(playerid, bool:stats)
	InventoryAction[playerid][inventory_open] = stats;

static palleteInUseID[MAX_PLAYERS] = -1;

stock Pallete_InUse(playerid)
	return palleteInUseID[playerid];

stock Player_SetPaletteColor(playerid, slot, color1, color2) {
	palleteInUseID[playerid] = slot;
	PaletaColor1[playerid] = color1;
	PaletaColor2[playerid] = color2;
}

stock givePlayerItem(playerid, itemtype, modelid, quantidade, const itemnome[], cor1 = 0, cor2 = 0)
{
	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++) {
		if (!InventarioInfo[playerid][inv][item_valid]) {
		    InventarioInfo[playerid][inv][item_valid] 	= 1;
		    InventarioInfo[playerid][inv][item_type] 	= itemtype;
		    InventarioInfo[playerid][inv][item_model] 	= modelid;
		    InventarioInfo[playerid][inv][item_quantia] = quantidade;
		    format(InventarioInfo[playerid][inv][item_nome], 30, itemnome);
		    InventarioInfo[playerid][inv][item_cor1] 	= cor1;
		    InventarioInfo[playerid][inv][item_cor2] 	= cor2;

			if (Inventory_IsOpen(playerid))
				Inventory_UpdateSlot(playerid, inv);

			InsertSlotInv(playerid, inv, itemnome, itemtype, modelid, quantidade, cor1, cor2);

			return inv;
		}
	}
	return -1;
}

stock InvItem_Reset(playerid, itemid)
{
	RemoveSlotInv(playerid, itemid);

	InventarioInfo[playerid][itemid][item_valid] 	= 0;
 	InventarioInfo[playerid][itemid][item_type] 	= ITEM_TYPE_NONE;
  	InventarioInfo[playerid][itemid][item_model] 	= 0;
   	InventarioInfo[playerid][itemid][item_quantia]  = 0;
   	InventarioInfo[playerid][itemid][item_vender]   = 0;
   	InventarioInfo[playerid][itemid][item_cor1] 	= 0;
	InventarioInfo[playerid][itemid][item_cor2] 	= 0;
   	format(InventarioInfo[playerid][itemid][item_nome], 30, "Nenhum Item");

	Inventory_UpdateSlot(playerid, itemid);

   	return 1;
}

stock InvItem_SetValid(playerid, slot, bool:valid)
	InventarioInfo[playerid][slot][item_valid] = valid;

stock InvItem_IsValid(playerid, slot)
	return InventarioInfo[playerid][slot][item_valid];

stock InvItem_ID(playerid, slot)
	return InventarioInfo[playerid][slot][item_id];

stock InvItem_SetName(playerid, slot, const name[])
    format(InventarioInfo[playerid][slot][item_nome], 30, name);

stock InvItem_GetName(playerid, slot) 
{
    new name[40];
    format(name, sizeof(name), InventarioInfo[playerid][slot][item_nome]);
    return name;
}

stock InvItem_SetQuantity(playerid, slot, quantity, bool:update = true) 
{
	InventarioInfo[playerid][slot][item_quantia] = quantity;
	if (update) UpdateSlotInv(playerid, slot);
}

stock InvItem_GetQuantity(playerid, slot)
	return InventarioInfo[playerid][slot][item_quantia];

stock InvItem_SetModel(playerid, slot, model)
	InventarioInfo[playerid][slot][item_model] = model;

stock InvItem_GetModel(playerid, slot)
	return InventarioInfo[playerid][slot][item_model];

stock InvItem_SetType(playerid, slot, type)
	InventarioInfo[playerid][slot][item_type] = type;

stock InvItem_GetType(playerid, slot)
	return InventarioInfo[playerid][slot][item_type];
	
stock InvItem_SetColor1(playerid, slot, cor1)
	InventarioInfo[playerid][slot][item_cor1] = cor1;

stock InvItem_GetColor1(playerid, slot)
	return InventarioInfo[playerid][slot][item_cor1];
	
stock InvItem_SetColor2(playerid, slot, cor2)
	InventarioInfo[playerid][slot][item_cor2] = cor2;

stock InvItem_GetColor2(playerid, slot)
	return InventarioInfo[playerid][slot][item_cor2];