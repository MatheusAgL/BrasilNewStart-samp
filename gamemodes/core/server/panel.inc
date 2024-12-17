// Includes necessárias
#include < YSI_Coding\y_hooks >

#define MAX_PANELS 500
#define MAX_PANELS_PER_PLAYER 10

enum PanelInfoEnum {
    pnID,
    pnOwner,
    pnOwnerName[MAX_PLAYER_NAME],
    pnObject,
    Text3D:pnTextLabel,
    pnModel,
    pnText[128],
    pnMaterialSize,
    pnFontSize,
    pnFontBold,
    pnFontColor,
    pnBackgroundColor,
    pnTextAlignment,
    Float:pnPos[3],
    Float:pnRot[3],
	pnItemName[30]
};
new PanelInfo[MAX_PANELS][PanelInfoEnum];
new Iterator:IterPanels<MAX_PANELS>;

//Queries
static const query_createPanel[] = 
    "INSERT INTO panels \
        (owner, model, `text`, material_size, font_size, font_bold, font_color, background_color, text_alignment, pos_x, pos_y, pos_z, rot_x, rot_y, rot_z, item_name) \
    VALUES \
        ('?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?')";

static const query_updatePanel[] = "UPDATE panels \
        SET owner='?', model='?', `text`='?', material_size='?', font_size='?', font_bold='?', font_color='?', background_color='?', text_alignment='?', pos_x='?', \
            pos_y='?', pos_z='?', rot_x='?', rot_y='?', rot_z='?', item_name='?' \
    WHERE id=?";

static const query_destroyPanel[] = "DELETE FROM `panels` WHERE `id` = '?'";

static const query_selectPanels[] = "SELECT \
        p.id, p.owner, p1.nome, p.model, p.`text`, p.material_size, p.font_size, p.font_bold, p.font_color, p.background_color, p.text_alignment, \
        p.pos_x, p.pos_y, p.pos_z, p.rot_x, p.rot_y, p.rot_z, p.item_name \
    FROM panels p \
    INNER JOIN player p1 ON \
        p1.id = p.owner \
    ORDER BY p.id";

stock Panel_Update3DText(panelid) {
	new string[75];
	format(string, sizeof string, "ID: %d\nDono: %s", panelid, PanelInfo[panelid][pnOwnerName]);

	if(IsValidDynamic3DTextLabel(PanelInfo[panelid][pnTextLabel]))
		DestroyDynamic3DTextLabel(PanelInfo[panelid][pnTextLabel]);
	
	PanelInfo[panelid][pnTextLabel] = CreateDynamic3DTextLabel(
		string, 0xFFFFFF30,
		PanelInfo[panelid][pnPos][0], 
		PanelInfo[panelid][pnPos][1], 
		PanelInfo[panelid][pnPos][2], 
		6.0
	);
}

stock Panel_Create(playerid, model, const itemname[], Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
    new id = Iter_Free(IterPanels);
	if(id != INVALID_ITERATOR_SLOT) {
	    Iter_Add(IterPanels, id);

		PanelInfo[id][pnOwner] = Player_GetAccountID(playerid);
		format(PanelInfo[id][pnOwnerName], MAX_PLAYER_NAME, PlayerName[playerid]);
		format(PanelInfo[id][pnText], 128, "Minha Placa");
		format(PanelInfo[id][pnItemName], 30, itemname);

		PanelInfo[id][pnPos][0] = x;
		PanelInfo[id][pnPos][1] = y;
		PanelInfo[id][pnPos][2] = z;

        PanelInfo[id][pnRot][0] = rx;
		PanelInfo[id][pnRot][1] = ry;
		PanelInfo[id][pnRot][2] = rz;

        PanelInfo[id][pnModel] = model;
		PanelInfo[id][pnMaterialSize] = 130;
        PanelInfo[id][pnFontSize] = 16;
        PanelInfo[id][pnFontColor] = 0xFFFFFFFF;
        PanelInfo[id][pnFontBold] = 1;
        PanelInfo[id][pnBackgroundColor] = 0xFF000000;
        PanelInfo[id][pnTextAlignment] = 1;

		new string[75];
		format(string, sizeof(string), "ID: %d\nDono: %s", id, PlayerName[playerid]);

		ServerLog::("placas", "%s [%d] colocou a placa %s", PlayerName[playerid], PlayerInfo[playerid][pID], PanelInfo[id][pnItemName]);

		Panel_Update3DText(id);
		PanelInfo[id][pnObject] = CreateDynamicObject(model, x, y, z, rx, ry, rz);

		Panel_UpdateObject(id);
		Panel_Save(id);
	}
	return 1;
}


stock Panel_Save(id) {
	if (Iter_Contains(IterPanels, id)) {

		if(PanelInfo[id][pnID] == 0) {
			new Statement:stmt_createPanel = MySQL_PrepareStatement(MySQL_Handle, query_createPanel);

			MySQL_BindInt(stmt_createPanel, 0, PanelInfo[id][pnOwner]);
			MySQL_BindInt(stmt_createPanel, 1, PanelInfo[id][pnModel]);
			MySQL_Bind(stmt_createPanel, 2, PanelInfo[id][pnText], true);
			MySQL_BindInt(stmt_createPanel, 3, PanelInfo[id][pnMaterialSize]);
			MySQL_BindInt(stmt_createPanel, 4, PanelInfo[id][pnFontSize]);
			MySQL_BindInt(stmt_createPanel, 5, PanelInfo[id][pnFontBold]);
			MySQL_BindInt(stmt_createPanel, 6, PanelInfo[id][pnFontColor]);
			MySQL_BindInt(stmt_createPanel, 7, PanelInfo[id][pnBackgroundColor]);
			MySQL_BindInt(stmt_createPanel, 8, PanelInfo[id][pnTextAlignment]);

			for(new i = 0; i < 3; i++) {
				MySQL_BindFloat(stmt_createPanel, 9+i, PanelInfo[id][pnPos][i]);
				MySQL_BindFloat(stmt_createPanel, 12+i, PanelInfo[id][pnRot][i]);
			}

			MySQL_Bind(stmt_createPanel, 15, PanelInfo[id][pnItemName], true);

			inline const OnPanelCreated() {
				PanelInfo[id][pnID] = cache_insert_id();
				MySQL_StatementClose(stmt_createPanel);
			}
			MySQL_ExecuteThreaded_Inline(stmt_createPanel, using inline OnPanelCreated);
		}
		else {
			new Statement:stmt_updatePanel = MySQL_PrepareStatement(MySQL_Handle, query_updatePanel);

			MySQL_BindInt(stmt_updatePanel, 0, PanelInfo[id][pnOwner]);
			MySQL_BindInt(stmt_updatePanel, 1, PanelInfo[id][pnModel]);
			MySQL_Bind(stmt_updatePanel, 2, PanelInfo[id][pnText], true);
			MySQL_BindInt(stmt_updatePanel, 3, PanelInfo[id][pnMaterialSize]);
			MySQL_BindInt(stmt_updatePanel, 4, PanelInfo[id][pnFontSize]);
			MySQL_BindInt(stmt_updatePanel, 5, PanelInfo[id][pnFontBold]);
			MySQL_BindInt(stmt_updatePanel, 6, PanelInfo[id][pnFontColor]);
			MySQL_BindInt(stmt_updatePanel, 7, PanelInfo[id][pnBackgroundColor]);
			MySQL_BindInt(stmt_updatePanel, 8, PanelInfo[id][pnTextAlignment]);

			for(new i = 0; i < 3; i++) {
				MySQL_BindFloat(stmt_updatePanel, 9+i, PanelInfo[id][pnPos][i]);
				MySQL_BindFloat(stmt_updatePanel, 12+i, PanelInfo[id][pnRot][i]);
			}

			MySQL_Bind(stmt_updatePanel, 15, PanelInfo[id][pnItemName], true);
			MySQL_BindInt(stmt_updatePanel, 16, PanelInfo[id][pnID]);

			MySQL_ExecuteThreaded(stmt_updatePanel);
			MySQL_StatementClose(stmt_updatePanel);
		}
		return 1;
	}
	return 0;
}

stock Panel_Destroy(id) {
	if (Iter_Contains(IterPanels, id)) {
		Iter_Remove(IterPanels, id);

		DestroyDynamic3DTextLabel(PanelInfo[id][pnTextLabel]);
		DestroyDynamicObject(PanelInfo[id][pnObject]);

		new Statement:stmt_destroyPanel = MySQL_PrepareStatement(MySQL_Handle, query_destroyPanel);
		MySQL_BindInt(stmt_destroyPanel, 0, PanelInfo[id][pnID]);
		MySQL_ExecuteThreaded(stmt_destroyPanel);
		MySQL_StatementClose(stmt_destroyPanel);
		
		PanelInfo[id][pnID] = 0;
		return 1;
	}
	return 0;
}

stock Panel_LoadAll() {
	new Statement:stmt_selectPanels = MySQL_PrepareStatement(MySQL_Handle, query_selectPanels);

	inline const OnLoadPanels() {

		new 
			dbid,
			owner,
			ownerName[MAX_PLAYER_NAME],
			model,
			text[128],
			materialSize,
			fontSize,
			fontBold,
			fontColor,
			backgroundColor,
			textAlignment,
			Float:pos[3],
			Float:rot[3],
			itemName[30]
        ;

		MySQL_BindResultInt(stmt_selectPanels, 0, dbid);
		MySQL_BindResultInt(stmt_selectPanels, 1, owner);
		MySQL_BindResult(stmt_selectPanels, 2, ownerName, sizeof(ownerName));
		MySQL_BindResultInt(stmt_selectPanels, 3, model);
		MySQL_BindResult(stmt_selectPanels, 4, text, sizeof(text));
		MySQL_BindResultInt(stmt_selectPanels, 5, materialSize);
		MySQL_BindResultInt(stmt_selectPanels, 6, fontSize);
		MySQL_BindResultInt(stmt_selectPanels, 7, fontBold);
		MySQL_BindResultInt(stmt_selectPanels, 8, fontColor);
		MySQL_BindResultInt(stmt_selectPanels, 9, backgroundColor);
		MySQL_BindResultInt(stmt_selectPanels, 10, textAlignment);

		for(new i = 0; i < 3; i++) {
			MySQL_BindResultFloat(stmt_selectPanels, 11+i, pos[i]);
			MySQL_BindResultFloat(stmt_selectPanels, 14+i, rot[i]);
		}

		MySQL_BindResult(stmt_selectPanels, 17, itemName, sizeof(itemName));

		new row;
		while (MySQL_Statement_FetchRow(stmt_selectPanels)) {
			new id = Iter_Free(IterPanels);

			if (id != INVALID_ITERATOR_SLOT) 
			{
				Iter_Add(IterPanels, id);

				PanelInfo[id][pnID] = dbid;
				PanelInfo[id][pnOwner] = owner;
				format(PanelInfo[id][pnOwnerName], MAX_PLAYER_NAME, ownerName);
				format(PanelInfo[id][pnText], 128, text);
				format(PanelInfo[id][pnItemName], 30, itemName);

				for(new i = 0; i < 3; i++) {
					PanelInfo[id][pnPos][i] = pos[i];
					PanelInfo[id][pnRot][i] = rot[i];
				}

				PanelInfo[id][pnModel] = model;
				PanelInfo[id][pnMaterialSize] = materialSize;
				PanelInfo[id][pnFontSize] = fontSize;
				PanelInfo[id][pnFontColor] = fontColor;
				PanelInfo[id][pnFontBold] = fontBold;
				PanelInfo[id][pnBackgroundColor] = backgroundColor;
				PanelInfo[id][pnTextAlignment] = textAlignment;

				Panel_Update3DText(id);
				PanelInfo[id][pnObject] = CreateDynamicObject(model, pos[0], pos[1], pos[2], rot[0], rot[1], rot[2]);

				SetDynamicObjectMaterialText(
					PanelInfo[id][pnObject], 0, 
					PanelInfo[id][pnText], 
					PanelInfo[id][pnMaterialSize], "Ariel", 
					PanelInfo[id][pnFontSize], 
					PanelInfo[id][pnFontBold], 
					PanelInfo[id][pnFontColor], 
					PanelInfo[id][pnBackgroundColor], 
					PanelInfo[id][pnTextAlignment]
				);
				row += 1;
			}
		}
		printf("[PLACAS]: %d placas carregadas!", Iter_Count(IterPanels));
		MySQL_StatementClose(stmt_selectPanels);
	}
    MySQL_ExecuteThreaded_Inline(stmt_selectPanels, using inline OnLoadPanels);
}


stock Player_FindClosestPanel(playerid)
{
	new Float:minDist = 999999.0, panelid = -1;
	
	foreach(new id : IterLoot) {
		new Float:dist = GetPlayerDistanceFromPoint(
			playerid, PanelInfo[id][pnPos][0], PanelInfo[id][pnPos][1], PanelInfo[id][pnPos][2]
		);
		
		if (dist > 1.5000) 
			continue;
		
		if (dist < minDist) {
		    minDist = dist;
		    panelid = id;
		}
	}
	return panelid;
}


stock Panel_GetOwner(id) {
	return PanelInfo[id][pnOwner];
}

stock Panel_UpdateObject(id) {
	SetDynamicObjectMaterialText(
		PanelInfo[id][pnObject], 0, 
		PanelInfo[id][pnText], 
		PanelInfo[id][pnMaterialSize], "Ariel", 
		PanelInfo[id][pnFontSize], 
		PanelInfo[id][pnFontBold], 
		PanelInfo[id][pnFontColor], 
		PanelInfo[id][pnBackgroundColor], 
		PanelInfo[id][pnTextAlignment]
	);
}

stock Player_CountPanel(playerid) {
	new count;

	foreach(new panel : IterPanels) {
	    if (Panel_GetOwner(panel) == Player_GetAccountID(playerid))
			count++;
	}
	return count;
}

stock Player_MaxPanel(playerid) {
	switch (Player_GetVIP(playerid)) {
		case SOCIO_COMUM, SOCIO_PREMIUM: return 5;
		case SOCIO_SUPREME: return 6;
		case SOCIO_EXTREME: return 7;
	}
	return 3;
} 

stock Panel_ShowTextChange(playerid, id) {
	inline D_Panel(did, ddialogid, dresponse, dlistitem, string:dtext[]) {
		#pragma unused did, ddialogid, dlistitem
		if (!dresponse) {
			return Panel_ShowDialog(playerid, id);
		}

		if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
			if (Dev_GetNivel(playerid)) {
				goto skip_developer_showtextchange;
			}
		}
		if (Panel_GetOwner(id) != Player_GetAccountID(playerid))
			return SendClientMessage(playerid, -1, "Você não é o proprietário dessa placa.");

		else if(strlen(dtext) == 0)
			return SendClientMessage(playerid, -1, "Você não pode salvar um texto vazio.");

		skip_developer_showtextchange:

		new cleaned[128], length = 0, textsize = strlen(dtext);
		for(new i = 0; i < textsize; i++) {
			if(i+1 < textsize && dtext[i] == '\\' && dtext[i+1] == 'n') {
				cleaned[length] = '\n';
				i += 1;
			}
			else {
				cleaned[length] = dtext[i];
			}
			length += 1;
		}
		if(length < 128)
			cleaned[length] = EOS;

		format(PanelInfo[id][pnText], 128, cleaned);
		Panel_UpdateObject(id);
		Panel_Save(id);
		Panel_ShowDialog(playerid, id);
		return 1;
	}

	format(
		MEGAString, sizeof(MEGAString), 
		"{FFFFFF}Você está editando o texto atual da sua placa.\n\n\
		Você pode adicionar cores e quebrar linhas para personalizar sua placa. Exemplo:\n\
		- Cores: use hexadecimal de 6 dígitos dentro de chaves -> {FFFF00 } Texto vermelho\n\
		- Quebra de linha: use \\n para quebrar linhas.\n\n\
		Texto atual:\n{FFFF00}%s",
		PanelInfo[id][pnText]
	);
	
    Dialog_ShowCallback(
		playerid, using inline D_Panel, DIALOG_STYLE_INPUT, 
		"Edição de texto", MEGAString, "Selecionar", ""C_WARNING"Fechar"
	);
	return 1;
}


stock Panel_ShowMSizeChange(playerid, id) {
	inline D_Panel(did, ddialogid, dresponse, dlistitem, string:dtext[]) {
		#pragma unused did, ddialogid, dlistitem, dtext
		if (!dresponse) {
			return Panel_ShowDialog(playerid, id);
		}

		if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
			if (Dev_GetNivel(playerid)) {
				goto skip_developer_showsizechange;
			}
		}

		if (Panel_GetOwner(id) != Player_GetAccountID(playerid))
			return SendClientMessage(playerid, -1, "Você não é o proprietário dessa placa.");

		skip_developer_showsizechange:

		PanelInfo[id][pnMaterialSize] = (dlistitem + 1) * 10;
		Panel_UpdateObject(id);
		Panel_Save(id);
		Panel_ShowDialog(playerid, id);
		return 1;
	}

	static const sizes[][] = {
		"32x32", "64x32", "64x64", "128x32", "128x64", "128x128", 
		"256x32", "256x64", "256x128", "256x256", "512x32", 
		"512x64", "512x128", "512x256", "512x512"
	};

	MEGAString[0] = EOS;
	for(new i = 0; i < sizeof(sizes); i++) {
		FormatCat(MEGAString, "%s\n", sizes[i]);
	}

    Dialog_ShowCallback(
		playerid, using inline D_Panel, DIALOG_STYLE_LIST, 
		"Edição de resolução", MEGAString, "Selecionar", ""C_WARNING"Fechar"
	);
	return 1;
}

stock Panel_ShowFSizeChange(playerid, id) {
	inline D_Panel(did, ddialogid, dresponse, dlistitem, string:dtext[]) {
		#pragma unused did, ddialogid, dlistitem
		if (!dresponse) {
			return Panel_ShowDialog(playerid, id);
		}

		if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
			if (Dev_GetNivel(playerid)) {
				goto skip_developer_showfsizechange;
			}
		}


		if (Panel_GetOwner(id) != Player_GetAccountID(playerid))
			return SendClientMessage(playerid, -1, "Você não é o proprietário dessa placa.");

		skip_developer_showfsizechange:

		new val = strval(dtext);
		if(strlen(dtext) == 0 || val < 1 || val > 255)
			return SendClientMessage(playerid, -1, "Você não pode salvar um valor inválido. Informe um número de 1 a 255.");

		PanelInfo[id][pnFontSize] = val;
		Panel_UpdateObject(id);
		Panel_Save(id);
		Panel_ShowDialog(playerid, id);
		return 1;
	}

	format(
		MEGAString, sizeof(MEGAString), 
		"{FFFFFF}Você está editando o tamanho da fonte atual da sua placa.\n\n\
		Você pode selecionar um valor entre 1 e 255.\n\n\
		Valor atual: {FFFF00}%d",
		PanelInfo[id][pnFontSize]
	);
	
    Dialog_ShowCallback(
		playerid, using inline D_Panel, DIALOG_STYLE_INPUT, 
		"Edição de tamanho da fonte", MEGAString, "Selecionar", ""C_WARNING"Fechar"
	);
	return 1;
}


stock Panel_ShowFBoldChange(playerid, id) {
	inline D_Panel(did, ddialogid, dresponse, dlistitem, string:dtext[]) {
		#pragma unused did, ddialogid, dlistitem, dtext
		if (!dresponse) {
			return Panel_ShowDialog(playerid, id);
		}

		if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
			if (Dev_GetNivel(playerid)) {
				goto skip_developer_showboldchange;
			}
		}

		if (Panel_GetOwner(id) != Player_GetAccountID(playerid))
			return SendClientMessage(playerid, -1, "Você não é o proprietário dessa placa.");

		skip_developer_showboldchange:

		PanelInfo[id][pnFontBold] = dlistitem;
		Panel_UpdateObject(id);
		Panel_Save(id);
		Panel_ShowDialog(playerid, id);
		return 1;
	}

    Dialog_ShowCallback(
		playerid, using inline D_Panel, DIALOG_STYLE_LIST, 
		"Edição de negrito", "Não\nSim", "Selecionar", ""C_WARNING"Fechar"
	);
	return 1;
}

stock Panel_ShowAlignmentChange(playerid, id) {
	inline D_Panel(did, ddialogid, dresponse, dlistitem, string:dtext[]) {
		#pragma unused did, ddialogid, dlistitem, dtext
		if (!dresponse) {
			return Panel_ShowDialog(playerid, id);
		}

		if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
			if (Dev_GetNivel(playerid)) {
				goto skip_developer_showchange;
			}
		}

		if (Panel_GetOwner(id) != Player_GetAccountID(playerid))
			return SendClientMessage(playerid, -1, "Você não é o proprietário dessa placa.");

		skip_developer_showchange:

		PanelInfo[id][pnTextAlignment] = dlistitem;
		Panel_UpdateObject(id);
		Panel_Save(id);
		Panel_ShowDialog(playerid, id);
		return 1;
	}

    Dialog_ShowCallback(
		playerid, using inline D_Panel, DIALOG_STYLE_LIST, 
		"Edição de negrito", "Esquerda\nCentro\nDireita", "Selecionar", ""C_WARNING"Fechar"
	);
	return 1;
}

stock Panel_ShowFColorChange(playerid, id) {
	inline D_Panel(did, ddialogid, dresponse, dlistitem, string:dtext[]) {
		#pragma unused did, ddialogid, dlistitem
		if (!dresponse) {
			return Panel_ShowDialog(playerid, id);
		}

		if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
			if (Dev_GetNivel(playerid)) {
				goto skip_developer_showcolorchange;
			}
		}

		if (Panel_GetOwner(id) != Player_GetAccountID(playerid))
			return SendClientMessage(playerid, -1, "Você não é o proprietário dessa placa.");

		else if(strlen(dtext) == 0)
			return SendClientMessage(playerid, -1, "Você não pode salvar uma cor vazia.");

		skip_developer_showcolorchange:

		PanelInfo[id][pnFontColor] = HexToInt(dtext);
		Panel_UpdateObject(id);
		Panel_Save(id);
		Panel_ShowDialog(playerid, id);
		return 1;
	}

	format(
		MEGAString, sizeof(MEGAString), 
		"{FFFFFF}Você está editando a cor da fonte da sua placa.\n\
		Você pode deve informar uma cor no formato ARGB. Exemplos:\n\
		- FF0000FF = Cor vermelha sem transparência\n\
		- 800000FF = Cor vermelha com 50 por cento de transparência\n\n\
		Valor atual: {FFFF00}%x",
		PanelInfo[id][pnFontColor]
	);
	
    Dialog_ShowCallback(
		playerid, using inline D_Panel, DIALOG_STYLE_INPUT, 
		"Edição de cor da fonte", MEGAString, "Selecionar", ""C_WARNING"Fechar"
	);
	return 1;
}

stock Panel_ShowBGColorChange(playerid, id) {
	inline D_Panel(did, ddialogid, dresponse, dlistitem, string:dtext[]) {
		#pragma unused did, ddialogid, dlistitem
		if (!dresponse) {
			return Panel_ShowDialog(playerid, id);
		}

		if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
			if (Dev_GetNivel(playerid)) {
				goto skip_developer_showcchange;
			}
		}

		if (Panel_GetOwner(id) != Player_GetAccountID(playerid))
			return SendClientMessage(playerid, -1, "Você não é o proprietário dessa placa.");

		else if(strlen(dtext) == 0)
			return SendClientMessage(playerid, -1, "Você não pode salvar uma cor vazia.");

		skip_developer_showcchange:

		PanelInfo[id][pnBackgroundColor] = HexToInt(dtext);
		Panel_UpdateObject(id);
		Panel_Save(id);
		Panel_ShowDialog(playerid, id);
		return 1;
	}

	format(
		MEGAString, sizeof(MEGAString), 
		"{FFFFFF}Você está editando a cor de fundo da sua placa.\n\
		Você pode deve informar uma cor no formato ARGB. Exemplos:\n\
		- FFFF0000 = Cor vermelha sem transparência\n\
		- 00000000 = Sem fundo\n\n\
		Valor atual: {FFFF00}%x",
		PanelInfo[id][pnBackgroundColor]
	);
	
    Dialog_ShowCallback(
		playerid, using inline D_Panel, DIALOG_STYLE_INPUT, 
		"Edição de cor de fundo", MEGAString, "Selecionar", ""C_WARNING"Fechar"
	);
	return 1;
}

stock Panel_ShowNear(playerid) {
	new index = 0, string[128];

	MEGAString[0] = EOS;

	strcat(MEGAString, "ID\tNome\tDistância\n");

	foreach(new id : IterPanels) {
		new Float:dist = GetPlayerDistanceFromPoint(
			playerid, PanelInfo[id][pnPos][0], PanelInfo[id][pnPos][1], PanelInfo[id][pnPos][2]
		);
		
		if (dist <= 20.0) {
			format(string, sizeof (string), "%d\t%s\t%.2f metros\n", id, PanelInfo[id][pnItemName], dist);
			strcat(MEGAString, string);
			ListOptions[playerid][index] = id;
			index += 1;
		}
	}
	
	inline D_SelectPanel(dyid, dydialogid, dyresponse, dylistitem, string:dytext[])
	{
		#pragma unused dyid, dydialogid, dytext, dyresponse
		if(!dyresponse)
			return 1;

		new panelid = ListOptions[playerid][dylistitem];
		if (!Iter_Contains(IterPanels, panelid)) {
			Panel_ShowNear(playerid);
			return SendClientMessage(playerid, -1, "Placa inválida.");
		}

		else if (Panel_GetOwner(panelid) != Player_GetAccountID(playerid) && !Dev_GetNivel(playerid))
			return SendClientMessage(playerid, -1, "Você não é o proprietário dessa placa.");

		Panel_ShowDialog(playerid, panelid);
		return 1;
	}

	format(string, sizeof(string), C_BLUELIGHT"Placas próximas [%d]", index);
	Dialog_ShowCallback(playerid, using inline D_SelectPanel, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Selecionar", ""C_WARNING"Fechar");
	return 1;
}

stock Panel_ShowDialog(playerid, id)
{
	inline D_Panel(did, ddialogid, dresponse, dlistitem, string:dtext[]) {
		#pragma unused did, ddialogid, dtext, dlistitem
		if (!dresponse) 
			return 1;

		if (Admin_GetNivel(playerid) >= DESENVOLVEDOR) {
			if (Dev_GetNivel(playerid)) {
				goto skip_developer_showdialog;
			}
		}

		if (Panel_GetOwner(id) != Player_GetAccountID(playerid))
			return SendClientMessage(playerid, -1, "Você não é o proprietário dessa placa.");

		skip_developer_showdialog:

		switch(dlistitem) {

			case 0: {
				SetPVarInt(playerid, "UpdatePanelID", id);
				SetPVarInt(playerid, "UpdatingPanel", 1);

				if(IsAndroidPlayer(playerid))
					OpenMenuEditorItem(playerid, id, 5);
				else
					EditDynamicObject(playerid, PanelInfo[id][pnObject]);
			}
			case 1: {
				Panel_ShowTextChange(playerid, id);
			}
			case 2: {
				Panel_ShowMSizeChange(playerid, id);
			}
			case 3: {
				Panel_ShowFSizeChange(playerid, id);
			}
			case 4: {
				Panel_ShowFBoldChange(playerid, id);
			}
			case 5: {
				Panel_ShowFColorChange(playerid, id);
			}
			case 6: {
				Panel_ShowBGColorChange(playerid, id);
			}
			case 7: {
				Panel_ShowAlignmentChange(playerid, id);
			}
			case 8:
			{
				if (isInventoryFull(playerid))
					return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

				ServerLog::("placas", "%s [%d] guardou a placa %s no inventario", PlayerName[playerid], PlayerInfo[playerid][pID], PanelInfo[id][pnItemName]);

				SendMsgF(playerid, COLOR_LIGHTBLUE, "* Você guardou um %s em seu inventário.", PanelInfo[id][pnItemName]);
				givePlayerItem(playerid, ITEM_TYPE_PANEL, PanelInfo[id][pnModel], 1, PanelInfo[id][pnItemName]);
				Panel_Destroy(id);
			}
	    }
		return 1;
	}
    Dialog_ShowCallback(playerid, using inline D_Panel, DIALOG_STYLE_LIST, ""C_BLUELIGHT"Placa: Opcões", 
		"Alterar posição\n\
		"C_WHITE"Alterar texto\n\
		"C_WHITE"Alterar resolução\n\
		"C_WHITE"Alterar tamanho da fonte\n\
		"C_WHITE"Alterar negrito\n\
		"C_WHITE"Alterar cor da fonte\n\
		"C_WHITE"Alterar cor de fundo\n\
		"C_WHITE"Alterar alinhamento\n\
		"C_WHITE"Guardar",
		"Selecionar", 
		""C_WARNING"Fechar"
	);
	return 1;
}


hook OP_EditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	new id = GetPVarInt(playerid, "UpdatePanelID");

	if(GetPVarInt(playerid, "UpdatingPanel")) {
		if(response == 0 || response == 1) {
			if(response == 1)
			{
				
				PanelInfo[id][pnPos][0] 		= x;
				PanelInfo[id][pnPos][1] 		= y;
				PanelInfo[id][pnPos][2] 		= z;
				PanelInfo[id][pnRot][0] 		= rx;
				PanelInfo[id][pnRot][1] 		= ry;
				PanelInfo[id][pnRot][2] 		= rz;

				SetDynamicObjectPos(PanelInfo[id][pnObject], x, y, z);
				SetDynamicObjectRot(PanelInfo[id][pnObject], rx, ry, rz);

				Panel_Update3DText(id);
				Panel_Save(id);
			}
			else
			{
				SetDynamicObjectPos(
					PanelInfo[id][pnObject], PanelInfo[id][pnPos][0], PanelInfo[id][pnPos][1], PanelInfo[id][pnPos][2]
				);
				SetDynamicObjectRot(
					PanelInfo[id][pnObject], PanelInfo[id][pnRot][0], PanelInfo[id][pnRot][1], PanelInfo[id][pnRot][2]
				);
			}
			SetPVarInt(playerid, "UpdatePanelID", 0);
		}
	}
	return 1;
}


CMD:placa(playerid, params[])
{
	if (isnull(params)) {
	    if (Dev_GetNivel(playerid)) 
			SendClientMessage(playerid, COLOR_DEV, "[Developer]: destruir | ir | trazer");

	    SendClientMessage(playerid, -1, "Modo de uso: /placa (nome | lista abaixo)");
	    SendClientMessage(playerid, COLOR_GRAY, "Nomes disponíveis: Ajuda | Editar | Localizar");
		return 1;
	}
	
	new 
		string[128], 
		null[25];

	if (!strcmp(params, "ajuda", true))
	{
	    SendClientMessage(playerid, -1, " ");
	    SendClientMessage(playerid, COLOR_LIGHTBLUE, "Algumas informações:");
	    SendClientMessage(playerid, -1, "- A placa é um item que você pode escrever textos como desejar, respeitando as regras.");
        SendClientMessage(playerid, -1, "- Você pode utilizar a placa para diversas finalidades, como decorar uma HQ, uma casa, família, etc.");
		SendClientMessage(playerid, COLOR_ERROR, "OBS: {FFFFFF}Você não pode colocar sua placa em qualquer lugar, leia as regras.");
	}
	else if (!strcmp(params, "destruir", true)) {
		if (!Dev_GetNivel(playerid))
			return SendClientMessage(playerid, -1, "Você não pode usar um comando da equipe de desenvolvimento.");

		new x = Player_FindClosestPanel(playerid);
		if (x == -1) 
			return SendClientMessage(playerid, -1, "Não há nenhuma placa próxima.");

		format(
			string, sizeof(string), 
			"Admin: %s destruiu a placa %s (%d) de %s (%.2f %.2f %.2f).", 
			PlayerName[playerid], PanelInfo[x][pnItemName], PanelInfo[x][pnModel], PanelInfo[x][pnOwnerName],
			PanelInfo[x][pnPos][0], PanelInfo[x][pnPos][1], PanelInfo[x][pnPos][2]
		);
	    Staff_ChatToAll(COLOR_LIGHTRED, string);

	    server_log("placas", string);

		Panel_Destroy(x);
	}
	else if (!strcmp(params, "localizar", true))
	{
		new index;
		MEGAString [0] = EOS;
		strcat(MEGAString, "ID\tNome\tLocal\tDistância\n");

		foreach(new id : IterPanels) {
            if (Panel_GetOwner(id) == Player_GetAccountID(playerid)) {
				
				new Float:dist = GetPlayerDistanceFromPoint(
					playerid, PanelInfo[id][pnPos][0], PanelInfo[id][pnPos][1], PanelInfo[id][pnPos][2]
				);

				new zone_name[MAX_MAP_ZONE_NAME];
				GetMapZoneName(GetMapZoneAtPoint2D(PanelInfo[id][pnPos][0], PanelInfo[id][pnPos][1]), zone_name);
				
				format(
					string, sizeof(string), 
					"%d\t%s\t%s\t%.2f metros\n", 
					id, PanelInfo[id][pnItemName], zone_name, dist
				);
				strcat(MEGAString, string);
				ListOptions[playerid][index] = id;
				index += 1;
		    }
		}
		inline D_Panel(dyid, dydialogid, dyresponse, dylistitem, string:dytext[])
		{
			#pragma unused dyid, dydialogid, dytext
			if (!dyresponse) 
				return 1;

			new id = ListOptions[playerid][dylistitem];

			format(string, sizeof string, "Você localizou sua placa de ID %d. Siga a "C_RED"marca vermelha "C_BLUELIGHT"no mapa.", id);
			SendClientMessage(playerid, COLOR_BLUELIGHT, string);

			SetPlayerCheckpoint(playerid, PanelInfo[id][pnPos][0], PanelInfo[id][pnPos][1], PanelInfo[id][pnPos][2], 3.0);
		}
		Dialog_ShowCallback(playerid, using inline D_Panel, DIALOG_STYLE_TABLIST_HEADERS, ""C_BLUELIGHT"Placa: Localizar", MEGAString, "Localizar", ""C_WARNING"Fechar");
	} 
	else if (strfind(params, "ir", true) != -1) 
	{
		if (Dev_GetNivel(playerid) < DEV_ALPHA)
			return SendClientMessage(playerid, -1, "Você não pode usar um comando da equipe de desenvolvimento.");

		new id;
		if (sscanf(params, "s[25]d", null, id)) 
			return SendClientMessage(playerid, -1, "Modo de uso: /bau ir (id)");

		if (!Iter_Contains(IterPanels, id))
		    return SendClientMessage(playerid, -1, "A placa não existe.");

		SetPlayerPos(playerid, PanelInfo[id][pnPos][0], PanelInfo[id][pnPos][1], PanelInfo[id][pnPos][2]);
	 	SendMsgF(playerid, COLOR_LIGHTGREEN, "Você foi até a placa: %d (%s)", id, PanelInfo[id][pnItemName]);	
	}
	else if (strfind(params, "trazer", true) != -1)
	{
		if (Dev_GetNivel(playerid) < DEV_ALPHA)
			return SendClientMessage(playerid, -1, "Você não pode usar um comando da equipe de desenvolvimento.");

		new id;
		if (sscanf(params, "s[25]d", null, id)) 
			return SendClientMessage(playerid, -1, "Modo de uso: /placa trazer (id da placa)");

		new Float:x, Float:y, Float:z;

		GetPlayerPos(playerid, x, y, z);
		PanelInfo[id][pnPos][0] = x;
		PanelInfo[id][pnPos][1] = y;
		PanelInfo[id][pnPos][2] = z;

		SetDynamicObjectPos(PanelInfo[id][pnObject], x, y, z);

		Panel_Update3DText(id);
		Panel_Save(id);
		
		SendMsgF(playerid, COLOR_LIGHTGREEN, "Você trouxe a placa: %d (%s)", id, PanelInfo[id][pnItemName]);	
	}
	else if (!strcmp(params, "editar", true)) {
		Panel_ShowNear(playerid);
	}
	else {
	    SendClientMessage(playerid, -1, "Nomes disponíveis: Ajuda | Editar | Localizar");

	    if (Dev_GetNivel(playerid)) 
			SendClientMessage(playerid, COLOR_DEV, "[Desenvolvedor]: destruir | ir | trazer");
	}
	return true;
}