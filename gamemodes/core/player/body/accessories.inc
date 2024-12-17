// Sistema de acessórios refeito by: wearL

#include <YSI_Coding\y_hooks>

// -------------------- //
//	Slots attachments

// Variáveis e enumeradores
enum accessorieEnum
{
    
	acc_string[128], // Ajuste
	acc_valid,
	acc_name[75],
	acc_model,
	acc_pos_body,
	acc_visible,
	
	// Coordenadas
	Float:acc_pos[3],
	
	// Rotação
	Float:acc_rot[3],
	
	// Tamanho
	Float:acc_size[3],
	
	// Cores
	acc_color1,
	acc_color2,
}
new accessoriesInfo[MAX_PLAYERS][MAX_PLAYER_ATTACHED_OBJECTS][accessorieEnum];

// Ajuste
new BodyPartNames[19][25] =
{
	"Nenhum",
	"Espinha",
	"Cabeça",
	"Ombro esquerdo",
	"Ombro direito",
	"Mão esquerda",
	"Mão direita",
	"Coxa esquerda",
	"Coxa direita",
	"Pé esquerdo",
	"Pé direito",
	"Panturrilha esquerda",
	"Panturrilha direita",
	"Antebraço esquerdo",
	"Antebraço direito",
	"Clavícula esquerdo",
	"Clavícula direito",
	"Pescoço",
	"Mandíbula"
};

// -------------------------- //
// Funções do módulo

hook OnPlayerFirstSpawn(playerid) {
	Player_SetAccessories(playerid);

	return 1;
}

static
	Statement: stmt_saveAcessorie,
	Statement: stmt_selectPlayerAcessorioes;

hook OnMySQLConnected() {
	static const query_saveAcessorie[] = 
		"UPDATE player SET `itens_?` = '?|?|?|?|?|?|?|?|?|?|?|?|?|?|?' WHERE `id` = '?'"
	;
	stmt_saveAcessorie = MySQL_PrepareStatement(MySQL_Handle, query_saveAcessorie);

	static const query_selectPlayerAcessorioes[] = 
		"SELECT itens_0, itens_1, itens_2, itens_3, itens_4, itens_5, itens_6, itens_7, itens_8, itens_9 FROM player WHERE id = ?"
	;
	stmt_selectPlayerAcessorioes = MySQL_PrepareStatement(MySQL_Handle, query_selectPlayerAcessorioes);
}

// Salvar acessorios
static SavePlayerAccessorie(playerid, index) {

	if (index < 0 || index >= MAX_PLAYER_ATTACHED_OBJECTS) 
		return 0;

	MySQL_BindInt(stmt_saveAcessorie, 	0, index);
	MySQL_BindInt(stmt_saveAcessorie, 	1, accessoriesInfo[playerid][index][acc_valid]);
    MySQL_Bind(stmt_saveAcessorie, 		2, accessoriesInfo[playerid][index][acc_name], true);
	MySQL_BindInt(stmt_saveAcessorie, 	3, accessoriesInfo[playerid][index][acc_model]);
	MySQL_BindInt(stmt_saveAcessorie, 	4, accessoriesInfo[playerid][index][acc_pos_body]);
	MySQL_BindFloat(stmt_saveAcessorie, 5, accessoriesInfo[playerid][index][acc_pos][0]);
	MySQL_BindFloat(stmt_saveAcessorie, 6, accessoriesInfo[playerid][index][acc_pos][1]);
	MySQL_BindFloat(stmt_saveAcessorie, 7, accessoriesInfo[playerid][index][acc_pos][2]);
	MySQL_BindFloat(stmt_saveAcessorie, 8, accessoriesInfo[playerid][index][acc_rot][0]);
	MySQL_BindFloat(stmt_saveAcessorie, 9, accessoriesInfo[playerid][index][acc_rot][1]);
	MySQL_BindFloat(stmt_saveAcessorie, 10, accessoriesInfo[playerid][index][acc_rot][2]);
	MySQL_BindFloat(stmt_saveAcessorie, 11, accessoriesInfo[playerid][index][acc_size][0]);
	MySQL_BindFloat(stmt_saveAcessorie, 12, accessoriesInfo[playerid][index][acc_size][1]);
	MySQL_BindFloat(stmt_saveAcessorie, 13, accessoriesInfo[playerid][index][acc_size][2]);
	MySQL_BindInt(stmt_saveAcessorie, 	14, accessoriesInfo[playerid][index][acc_color1]);
	MySQL_BindInt(stmt_saveAcessorie, 	15, accessoriesInfo[playerid][index][acc_color2]);
	MySQL_BindInt(stmt_saveAcessorie, 	16, PlayerInfo[playerid][pID]);
	
    MySQL_ExecuteThreaded(stmt_saveAcessorie);

	return 1;
}

hook OnPlayerLogin(playerid) {

	inline const OnLoadAcessories() {

		new acessories_string[MAX_PLAYER_ATTACHED_OBJECTS][128],
			string_read[13][128];

		for(new index; index != MAX_PLAYER_ATTACHED_OBJECTS; index++) {
			MySQL_BindResult(stmt_selectPlayerAcessorioes, index, acessories_string[index]);
		}

		if (MySQL_Statement_FetchRow(stmt_selectPlayerAcessorioes)) 
		{
			for(new index; index != MAX_PLAYER_ATTACHED_OBJECTS; index++) {

				split(acessories_string[index], string_read, '|');

				accessoriesInfo[playerid][index][acc_valid] = strval(string_read[0]);

				if (accessoriesInfo[playerid][index][acc_valid]) {
					format(accessoriesInfo[playerid][index][acc_name], 75, string_read[1]);
					accessoriesInfo[playerid][index][acc_valid]  = strval(string_read[0]);
					accessoriesInfo[playerid][index][acc_model] = strval(string_read[2]);
					accessoriesInfo[playerid][index][acc_pos_body] 	= strval(string_read[3]);

					if(accessoriesInfo[playerid][index][acc_pos_body] < 0)
						accessoriesInfo[playerid][index][acc_pos_body] = 1;
					else if(accessoriesInfo[playerid][index][acc_pos_body] > sizeof(BodyPartNames))
						accessoriesInfo[playerid][index][acc_pos_body] = sizeof(BodyPartNames)-1;

					// Coordenadas
					accessoriesInfo[playerid][index][acc_pos][0] = floatstr(string_read[4]);
					accessoriesInfo[playerid][index][acc_pos][1] = floatstr(string_read[5]);
					accessoriesInfo[playerid][index][acc_pos][2] = floatstr(string_read[6]);
					// Rotação
					accessoriesInfo[playerid][index][acc_rot][0] = floatstr(string_read[7]);
					accessoriesInfo[playerid][index][acc_rot][1] = floatstr(string_read[8]);
					accessoriesInfo[playerid][index][acc_rot][2] = floatstr(string_read[9]);
					// Tamanho
					accessoriesInfo[playerid][index][acc_size][0] = floatstr(string_read[10]);
					accessoriesInfo[playerid][index][acc_size][1] = floatstr(string_read[11]);
					accessoriesInfo[playerid][index][acc_size][2] = floatstr(string_read[12]);

					SetPlayerAttachedObject(playerid, index, 
					accessoriesInfo[playerid][index][acc_model],accessoriesInfo[playerid][index][acc_pos_body], 
					accessoriesInfo[playerid][index][acc_pos][0], accessoriesInfo[playerid][index][acc_pos][1], accessoriesInfo[playerid][index][acc_pos][2], 
					accessoriesInfo[playerid][index][acc_rot][0], accessoriesInfo[playerid][index][acc_rot][1], accessoriesInfo[playerid][index][acc_rot][2], 
					accessoriesInfo[playerid][index][acc_size][0], accessoriesInfo[playerid][index][acc_size][1], accessoriesInfo[playerid][index][acc_size][2],
					accessoriesInfo[playerid][index][acc_color1], accessoriesInfo[playerid][index][acc_color2]);
				}
			}
		}
	}
	MySQL_BindInt(stmt_selectPlayerAcessorioes, 0, PlayerInfo[playerid][pID]);
	MySQL_ExecuteThreaded_Inline(stmt_selectPlayerAcessorioes, using inline OnLoadAcessories);
}

SetPlayerAccessorie(playerid, const acessorio[], index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0, materialcolor1 = 0, materialcolor2 = 0)
{
	if (index < 0 || index >= MAX_PLAYER_ATTACHED_OBJECTS) 
		return 0;

	format(accessoriesInfo[playerid][index][acc_name], 75, acessorio);
	accessoriesInfo[playerid][index][acc_valid] 	= 1;
	accessoriesInfo[playerid][index][acc_model] = modelid;
	accessoriesInfo[playerid][index][acc_pos_body] 	= bone;
	// Coordenadas
	accessoriesInfo[playerid][index][acc_pos][0] = fOffsetX;
	accessoriesInfo[playerid][index][acc_pos][1] = fOffsetY;
	accessoriesInfo[playerid][index][acc_pos][2] = fOffsetZ;
	// Rotação
	accessoriesInfo[playerid][index][acc_rot][0] = fRotX;
	accessoriesInfo[playerid][index][acc_rot][1] = fRotY;
	accessoriesInfo[playerid][index][acc_rot][2] = fRotZ;
	// Tamanho
	accessoriesInfo[playerid][index][acc_size][0] = fScaleX;
	accessoriesInfo[playerid][index][acc_size][1] = fScaleY;
	accessoriesInfo[playerid][index][acc_size][2] = fScaleZ;
	// Cores
	accessoriesInfo[playerid][index][acc_color1] = materialcolor1;
	accessoriesInfo[playerid][index][acc_color2] = materialcolor2;

	// Setar objeto
	SetPlayerAttachedObject(playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, materialcolor1, materialcolor2);
	SavePlayerAccessorie(playerid, index);

	return 1;
}

Player_SetAccessories(playerid)
{
	// Setar acessorios salvos
	for(new index; index != MAX_PLAYER_ATTACHED_OBJECTS; index++) {
	    if (accessoriesInfo[playerid][index][acc_valid]) {
	    	SetPlayerAttachedObject(playerid, index, accessoriesInfo[playerid][index][acc_model], accessoriesInfo[playerid][index][acc_pos_body], 
				accessoriesInfo[playerid][index][acc_pos][0], accessoriesInfo[playerid][index][acc_pos][1], accessoriesInfo[playerid][index][acc_pos][2], 
				accessoriesInfo[playerid][index][acc_rot][0], accessoriesInfo[playerid][index][acc_rot][1], accessoriesInfo[playerid][index][acc_rot][2], 
				accessoriesInfo[playerid][index][acc_size][0], accessoriesInfo[playerid][index][acc_size][1], accessoriesInfo[playerid][index][acc_size][2],
				accessoriesInfo[playerid][index][acc_color1], accessoriesInfo[playerid][index][acc_color2]);
	    }
	}
	return 1;
}

RemovePlayerAcessorie(playerid, index) 
{
	if (index < 0 || index >= MAX_PLAYER_ATTACHED_OBJECTS) 
		return false;

	// Main
	format(accessoriesInfo[playerid][index][acc_name], 75, "Nenhum");
	accessoriesInfo[playerid][index][acc_valid]  = 0;
	accessoriesInfo[playerid][index][acc_model] = 0;
	accessoriesInfo[playerid][index][acc_pos_body] 	= 0;
	// Coordenadas
	accessoriesInfo[playerid][index][acc_pos][0] = 0.0;
	accessoriesInfo[playerid][index][acc_pos][1] = 0.0;
	accessoriesInfo[playerid][index][acc_pos][2] = 0.0;
	// Rotação
	accessoriesInfo[playerid][index][acc_rot][0] = 0.0;
	accessoriesInfo[playerid][index][acc_rot][1] = 0.0;
	accessoriesInfo[playerid][index][acc_rot][2] = 0.0;
	// Tamanho
	accessoriesInfo[playerid][index][acc_size][0] = 1.0;
	accessoriesInfo[playerid][index][acc_size][1] = 1.0;
	accessoriesInfo[playerid][index][acc_size][2] = 1.0;
	// Cores
	accessoriesInfo[playerid][index][acc_color1] = 0;
	accessoriesInfo[playerid][index][acc_color2] = 0;

	RemovePlayerAttachedObject(playerid, index);

	SavePlayerAccessorie(playerid, index);

	return 1;
}

CALLBACK:IsPlayerAccessoryValid(playerid, slotid) {
	return accessoriesInfo[playerid][slotid][acc_valid];
}

CALLBACK:SetPlayerAccessoryValid(playerid, slotid, value) {
	accessoriesInfo[playerid][slotid][acc_valid] = value;
}

RemovePlayerAcessoriesTemp(playerid) {
	SetPVarInt(playerid, "acessories_removed", 1);

	for(new index = MAX_PLAYER_ATTACHED_OBJECTS-1; index >= 0; index--) {
	    if (IsPlayerAttachedObjectSlotUsed(playerid, index)) {
            RemovePlayerAttachedObject(playerid, index);
        }
    }
}

stock Accessorie_BodyParts(playerid)
{
	if (Inventory_IsOpen(playerid))
		Inventory_HideForPlayer(playerid);

	MEGAString[0] = EOS;
	
	for(new index = 1; index < sizeof (BodyPartNames); index++) {
		strcat(MEGAString, BodyPartNames[index]);
		strcat(MEGAString, "\n");
	}
	SetPVarInt(playerid, "varEditing", 1);

	inline D_Accessorie_BodyParts(did, ddialogid, dresponse, dlistitem, string:dtext[])
	{
		#pragma unused did, ddialogid, dtext
		if (!dresponse) {
			SetPVarInt(playerid, "varEditing", 0);
			return 1;
		}

		new 
			index = GetPVarInt(playerid, "accessoryItem"),
			slotid = GetPVarInt(playerid, "accessorySlot"),
			name[35],
			model = GetPVarInt(playerid, "accessoryModel"),
			color1 = GetPVarInt(playerid, "accessoryCor1"),
			color2 = GetPVarInt(playerid, "accessoryCor2");

		GetPVarString(playerid, "accessoryName", name, sizeof(name));

		if (InvItem_GetQuantity(playerid, index) > 1)
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Você deve separar os acessórios antes de usá-los.");

		if (index != -1) {
			SetPlayerAccessorie(playerid, name, slotid, model, dlistitem + 1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, color1, color2);

			if (IsAndroidPlayer(playerid))
				OpenMenuEditorItem(playerid, slotid);
			else
				EditAttachedObject(playerid, slotid);

			InvItem_Reset(playerid, index);
			Acessorie_Select(playerid, false);
		}
		return 1;
	}
    Dialog_ShowCallback(playerid, using inline D_Accessorie_BodyParts, DIALOG_STYLE_LIST, ""C_WHITE"Selecione um local do corpo", MEGAString, "Selecionar", "Cancelar");

	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	if (!response) 
		return EditAttachedObject(playerid, index);

	if (index < 0 || index >= MAX_PLAYER_ATTACHED_OBJECTS)
		return true;

	// Coordenadas
	accessoriesInfo[playerid][index][acc_pos][0] = fOffsetX;
	accessoriesInfo[playerid][index][acc_pos][1] = fOffsetY;
	accessoriesInfo[playerid][index][acc_pos][2] = fOffsetZ;
	// Rotação
	accessoriesInfo[playerid][index][acc_rot][0] = fRotX;
	accessoriesInfo[playerid][index][acc_rot][1] = fRotY;
	accessoriesInfo[playerid][index][acc_rot][2] = fRotZ;
	// Tamanho
	accessoriesInfo[playerid][index][acc_size][0] = fScaleX;
	accessoriesInfo[playerid][index][acc_size][1] = fScaleY;
	accessoriesInfo[playerid][index][acc_size][2] = fScaleZ;

	SetPlayerAttachedObject(
		playerid, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, 
		accessoriesInfo[playerid][index][acc_color1], accessoriesInfo[playerid][index][acc_color2]); // Cores

    SendClientMessage(playerid, COLOR_WHITE, "Acessório editado! Use "C_CYAN"/acessorios "C_WHITE"para ver seus acessórios.");
    
	// Salvar objeto attachado
	SavePlayerAccessorie(playerid, index);

	return 1;
}

// -------------------------------------------------------------------------
/* Local reservado para os comandos do módulo */
// -------------------------------------------------------------------------
// Comandos:
CMD:acessorios(playerid)
{
	if (IsAndroidPlayer(playerid)) {
		if (IsPlayerInEditorItem(playerid))
			return SendClientMessage(playerid, -1, "Você não pode usar o comando ao estar numa edição de item/bau ou portão.");
	}
	
	new string[128],
		players;

	MEGAString[0] = EOS;

	strcat(MEGAString, "Slot\tNome\tLocal do corpo\n");

	for (new loop; loop != MAX_PLAYER_ATTACHED_OBJECTS; loop++) 
	{
		if (accessoriesInfo[playerid][loop][acc_valid]) {

			format(string, sizeof string, ""C_GRAY"%d\t"C_WHITE"%s\t"C_GRAY"%s\n", // Future: Validade ( \t"C_CYAN"- ) 
			loop, accessoriesInfo[playerid][loop][acc_name], BodyPartNames[accessoriesInfo[playerid][loop][acc_pos_body]]);

			strcat(MEGAString, string);
			
			List_SetPlayers(playerid, players, loop);
			players++;
		}
	}

	SetPVarInt(playerid, "varEditing", 1);

	inline DialogAcessories(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext

		if (!response) {
			SetPVarInt(playerid, "varEditing", 0);
			return 1;
		}

		new index = List_GetPlayers(playerid, listitem);

		if (index != INVALID_PLAYER_ID)
		{
			SetPVarInt(playerid, "varAcessorio", index);

			if (index < 0 || index > 10)
				return SendClientMessage(playerid, COLOR_ERROR, "Houve um erro comunique a administração!");

			if (accessoriesInfo[playerid][index][acc_valid])
			{
				format(MEGAString, sizeof(MEGAString),
				"{FFFFFF}Editar seu acessório\n\n\
				Nome do acessório: {00FFFF}%s\n\
				{FFFFFF}Local do corpo: {00FFFF}%s\n\n\
				{FFFFFF}O que você deseja fazer com este acessório?", accessoriesInfo[playerid][index][acc_name], BodyPartNames[accessoriesInfo[playerid][index][acc_pos_body]]);
				ShowPlayerDialog(playerid, 122, DIALOG_STYLE_MSGBOX, "Editar seu acessório", MEGAString, "Editar", "Guardar");
			}
		}
	}
	Dialog_ShowCallback(playerid, using inline DialogAcessories,
        DIALOG_STYLE_TABLIST_HEADERS, ""C_WHITE"Seus acessórios", MEGAString, "Editar", "Cancelar"
    );
	return 1;
}

stock Accessories_Count(playerid) {
	new count_accessories;
	
	for (new slot = 5; slot < 9; slot++) {
		if (IsPlayerAttachedObjectSlotUsed(playerid, slot))
			count_accessories++;
	}
	return count_accessories;
}

stock Acessorie_Select(playerid, bool:stats = true) {
	if (stats == false) {
		DeletePVar(playerid, "accessoryItem");
		DeletePVar(playerid, "accessoryName");
		DeletePVar(playerid, "accessoryModel");
		DeletePVar(playerid, "accessorySlot");
		DeletePVar(playerid, "accessoryCor1");
		DeletePVar(playerid, "accessoryCor2");
	}
}