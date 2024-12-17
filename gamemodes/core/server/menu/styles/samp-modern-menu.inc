// Includes necessárias
#include < YSI_Coding\y_hooks >

#define PlayerTextDrawChangeString(%1,%2,%3,%4,%5) \
	format(%1, sizeof(%1), %3, %5),		\
	PlayerTextDrawSetString(%2, %4, %1)

// Máximo de itens na página
#define     MAX_PAGE_ITENS              10
#define     MAX_MENU_CATEGORY           10
#define     EMPTY_CATEGORY              -1
#define     EMPTY_MENU_ITEM             -1
#define     MAX_MENU_ITENS              25
#define     INVALID_MENU_ID             0

// Textdraws: Estilo moderno (GTA V)
#include <td-style-modern>

// ID das Páginas
#define     MENU_PAGE_MAIN              1
#define     MENU_PAGE_ITENS             2

// ID do menu
#define     ID_MENU_AMMUNATION          1
#define     ID_MENU_BURGUERSHOT         2

// ID da direção da seleção
#define     MENU_PAGE_DOWN              0
#define     MENU_PAGE_UP                1

// Variáveis de armazenamento
enum enumMenuCategory
{
    category_id,
    category_nome[20],
    category_quantidade,
    category_position,
};
new Menu_Category[MAX_PLAYERS][MAX_MENU_CATEGORY][enumMenuCategory];

enum enumMenuItem
{
    menu_item_id,
    menu_item_value,
    menu_animlib[25],
	menu_animname[35],
};
new Menu_Itens[MAX_PLAYERS][MAX_MENU_ITENS][enumMenuItem];

new Category_Selected[MAX_PLAYERS];

// Ammunation
#include <ammunation>

// Burguer Shot
#include <burguer_shot>

// Enumerador do menu
enum enumMenu
{
    menu_id,
    menu_item,
    menu_page,
    menu_selected,
    menu_max_itens,
};
new MenuInfo[MAX_PLAYERS][enumMenu];

stock Player_InMenu(playerid) {
    if (MenuInfo[playerid][menu_id] != INVALID_MENU_ID)
        return true;

    return false;
}

// Carrega as textdraws
hook OnPlayerConnect(playerid) {
    static const	empty_menu[enumMenu];
    MenuInfo[playerid] = empty_menu;

    CreatePTexdraws_MenuModern(playerid);
    SetPVarInt(playerid, #flood_key, GetTickCount() + 200);
}

hook OnGameModeInit() {
    CreateTextdraws_MenuModern();
}
// ---------------------------------------------------------

hook OnPlayerUpdate(playerid)
{
    if (IsPCPlayer(playerid)) {

        new 
            KEY:actions, 
            KEY:ud, 
            KEY:lr;

        GetPlayerKeys(playerid, actions, ud, lr);

        if (ud == KEY:KEY_UP)
        {
            if (MenuInfo[playerid][menu_id] != INVALID_MENU_ID) {
                if (GetTickCount() > GetPVarInt(playerid, #flood_key)) {
                    new itemid = MenuInfo[playerid][menu_item];

                    if (MenuInfo[playerid][menu_selected] > 0) {
                        MenuInfo[playerid][menu_item]--;
                        MenuInfo[playerid][menu_selected]--;

                        PlayerPlaySound(playerid, 1054,  0.0, 0.0, 0.0);

                        UpdateItemSelected(playerid, MenuInfo[playerid][menu_selected], MENU_PAGE_UP);

                        switch (MenuInfo[playerid][menu_page]) {
                            case MENU_PAGE_ITENS: {
                                UpdatePageItens(playerid, itemid);
                            }
                        }
                    }
                    SetPVarInt(playerid, #flood_key, GetTickCount() + 100);
                }
            }
        }
        else if (ud == KEY:KEY_DOWN)
        {
            if (MenuInfo[playerid][menu_id] != INVALID_MENU_ID) {
                if (GetTickCount() > GetPVarInt(playerid, #flood_key)) {
                    new itemid = MenuInfo[playerid][menu_item];
                    
                    if ((MenuInfo[playerid][menu_selected] + 1) < MenuInfo[playerid][menu_max_itens]) {
                        MenuInfo[playerid][menu_item]++;
                        MenuInfo[playerid][menu_selected]++;

                        PlayerPlaySound(playerid, 1055,  0.0, 0.0, 0.0);

                        UpdateItemSelected(playerid, MenuInfo[playerid][menu_selected], MENU_PAGE_DOWN);

                        switch (MenuInfo[playerid][menu_page]) {
                            case MENU_PAGE_ITENS: {
                                UpdatePageItens(playerid, itemid);
                            }
                        }
                    }
                    else {
                        // Old posição
                        new oldpos = MenuInfo[playerid][menu_selected];
                        
                        // Nome do item
                        PlayerTextDrawHide(playerid, menu_pstextdraws[oldpos][playerid]);
                        PlayerTextDrawColor(playerid, menu_pstextdraws[oldpos][playerid], -1);
                        PlayerTextDrawBoxColor(playerid, menu_pstextdraws[oldpos][playerid], 0x00000000);
                        PlayerTextDrawShow(playerid, menu_pstextdraws[oldpos][playerid]);

                        // Quantidade do item
                        PlayerTextDrawHide(playerid, menu_pqtextdraws[oldpos][playerid]);
                        PlayerTextDrawColor(playerid, menu_pqtextdraws[oldpos][playerid], -1);
                        PlayerTextDrawShow(playerid, menu_pqtextdraws[oldpos][playerid]);

                        // Voltando ao inicio
                        MenuInfo[playerid][menu_selected] = 0;

                        UpdateItemSelected(playerid, MenuInfo[playerid][menu_selected]);

                        PlayerPlaySound(playerid, 1055,  0.0, 0.0, 0.0);
                    }
                    SetPVarInt(playerid, #flood_key, GetTickCount() + 100);
                }
            }
        }
    }
    return 1;
}

CALLBACK:OnPlayerConfirmMenu(playerid, menuid, pageid, itemid, selecteditem){
    switch (pageid) {
        case MENU_PAGE_MAIN: {

            MenuInfo[playerid][menu_item] = Menu_Category[playerid][selecteditem][category_position];
            MenuInfo[playerid][menu_max_itens] = Menu_Category[playerid][selecteditem][category_quantidade];

            if(menuid == ID_MENU_AMMUNATION) {
                ChangeMenuPage(playerid, MENU_PAGE_ITENS);
            }
        }
        case MENU_PAGE_ITENS: {
            if(menuid == ID_MENU_AMMUNATION) {
                if (Player_GetMoney(playerid) < Menu_Itens[playerid][itemid][menu_item_value]) {
                    return SendMsgF(playerid, -1, "Você não tem $%s!", getFormatText(Menu_Itens[playerid][itemid][menu_item_value]));
                }
            
                Player_RemoveMoney(playerid, Menu_Itens[playerid][itemid][menu_item_value]);
                GivePlayerWeapon(playerid, Menu_Itens[playerid][itemid][menu_item_id], 10);
                DepositPropertie(playerid, PagarICMS(Menu_Itens[playerid][itemid][menu_item_value]));
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newactions, oldactions) 
{
    if (IsAndroidPlayer(playerid) && newactions & KEY_YES)
    {
        if (MenuInfo[playerid][menu_id] != INVALID_MENU_ID) {
            new itemid = MenuInfo[playerid][menu_item];

            if (MenuInfo[playerid][menu_selected] > 0) {
                MenuInfo[playerid][menu_item]--;
                MenuInfo[playerid][menu_selected]--;

                PlayerPlaySound(playerid, 1054,  0.0, 0.0, 0.0);

                UpdateItemSelected(playerid, MenuInfo[playerid][menu_selected], MENU_PAGE_UP);

                switch (MenuInfo[playerid][menu_page]) {
                    case MENU_PAGE_ITENS: {
                        UpdatePageItens(playerid, itemid);
                    }
                }
            }
            else {
                // Old posição
                new oldpos = MenuInfo[playerid][menu_selected];
                
                // Nome do item
                PlayerTextDrawHide(playerid, menu_pstextdraws[oldpos][playerid]);
                PlayerTextDrawColor(playerid, menu_pstextdraws[oldpos][playerid], -1);
                PlayerTextDrawBoxColor(playerid, menu_pstextdraws[oldpos][playerid], 0x00000000);
                PlayerTextDrawShow(playerid, menu_pstextdraws[oldpos][playerid]);

                // Quantidade do item
                PlayerTextDrawHide(playerid, menu_pqtextdraws[oldpos][playerid]);
                PlayerTextDrawColor(playerid, menu_pqtextdraws[oldpos][playerid], -1);
                PlayerTextDrawShow(playerid, menu_pqtextdraws[oldpos][playerid]);

                // Voltando ao final
                MenuInfo[playerid][menu_selected] = MenuInfo[playerid][menu_max_itens]-1;

                UpdateItemSelected(playerid, MenuInfo[playerid][menu_selected]);

                PlayerPlaySound(playerid, 1055,  0.0, 0.0, 0.0);
            }
        }
    }
    else if (IsAndroidPlayer(playerid) && newactions & KEY_NO)
    {
        if (MenuInfo[playerid][menu_id] != INVALID_MENU_ID) {
            new itemid = MenuInfo[playerid][menu_item];
            
            if ((MenuInfo[playerid][menu_selected] + 1) < MenuInfo[playerid][menu_max_itens]) {
                MenuInfo[playerid][menu_item]++;
                MenuInfo[playerid][menu_selected]++;

                PlayerPlaySound(playerid, 1055,  0.0, 0.0, 0.0);

                UpdateItemSelected(playerid, MenuInfo[playerid][menu_selected], MENU_PAGE_DOWN);

                switch (MenuInfo[playerid][menu_page]) {
                    case MENU_PAGE_ITENS: {
                        UpdatePageItens(playerid, itemid);
                    }
                }
            }
            else {
                // Old posição
                new oldpos = MenuInfo[playerid][menu_selected];
                
                // Nome do item
                PlayerTextDrawHide(playerid, menu_pstextdraws[oldpos][playerid]);
                PlayerTextDrawColor(playerid, menu_pstextdraws[oldpos][playerid], -1);
                PlayerTextDrawBoxColor(playerid, menu_pstextdraws[oldpos][playerid], 0x00000000);
                PlayerTextDrawShow(playerid, menu_pstextdraws[oldpos][playerid]);

                // Quantidade do item
                PlayerTextDrawHide(playerid, menu_pqtextdraws[oldpos][playerid]);
                PlayerTextDrawColor(playerid, menu_pqtextdraws[oldpos][playerid], -1);
                PlayerTextDrawShow(playerid, menu_pqtextdraws[oldpos][playerid]);

                // Voltando ao inicio
                MenuInfo[playerid][menu_selected] = 0;

                UpdateItemSelected(playerid, MenuInfo[playerid][menu_selected]);

                PlayerPlaySound(playerid, 1055,  0.0, 0.0, 0.0);
            }
        }
    }
    else if ((IsPCPlayer(playerid) && newactions & KEY_SPRINT) || (IsAndroidPlayer(playerid) && newactions & KEY_CTRL_BACK))
	{
		if (MenuInfo[playerid][menu_id] != INVALID_MENU_ID) 
        {
            new itemid = MenuInfo[playerid][menu_item],
                selecteditem = MenuInfo[playerid][menu_selected],
                pageid = MenuInfo[playerid][menu_page];

            if (itemid < 0)
                return 1;

            PlayerPlaySound(playerid, 1058,  0.0, 0.0, 0.0);
            CallLocalFunction("OnPlayerConfirmMenu", "iiiii", playerid, MenuInfo[playerid][menu_id], pageid, itemid, selecteditem);
        }
	}

    else if (newactions & KEY_SECONDARY_ATTACK)
	{
		if (MenuInfo[playerid][menu_id] != INVALID_MENU_ID)
        {
            switch (MenuInfo[playerid][menu_page]) {
                case MENU_PAGE_MAIN: {
                    KickPlayerMenu(playerid);
                }
                case MENU_PAGE_ITENS: 
                {
                    ChangeMenuPage(playerid, MENU_PAGE_MAIN);

                    UpdateItemSelected(playerid, MenuInfo[playerid][menu_selected]);

                    PlayerPlaySound(playerid, 1058,  0.0, 0.0, 0.0);
                }
            }
        }
	}
    return 1;
}

stock UpdatePageItens(playerid, itemid=-1)
{
    if(itemid < 0)
        return 1;

    Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

    return 1;
}

// Kickar o jogador do menu
stock KickPlayerMenu(playerid) 
{
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, true);

    HideMenu(playerid);

    return 1;
}

// Muda a página do menu
stock ChangeMenuPage(playerid, pageitem=MENU_PAGE_MAIN)
{
    ChangeMenuHeaders(playerid, pageitem);
    MenuInfo[playerid][menu_page] = pageitem;

    for(new text; text < MAX_PAGE_ITENS; text++) {
        PlayerTextDrawHide(playerid, menu_pstextdraws[text][playerid]);
        PlayerTextDrawHide(playerid, menu_pqtextdraws[text][playerid]);
    }

    new small_string[20];
    new itemid = MenuInfo[playerid][menu_item];

    switch (pageitem)
    {
        case MENU_PAGE_MAIN: {
            MenuInfo[playerid][menu_item] = 1;

            if (MenuInfo[playerid][menu_id] == ID_MENU_AMMUNATION)
                MenuInfo[playerid][menu_max_itens] = sizeof(AMMU_Category);

            for(new text; text < MenuInfo[playerid][menu_max_itens]; text++) {
                PlayerTextDrawChangeString(small_string, playerid, "%s", menu_pstextdraws[text][playerid], Menu_Category[playerid][text][category_nome]);
                PlayerTextDrawChangeString(small_string, playerid, "%d", menu_pqtextdraws[text][playerid], Menu_Category[playerid][text][category_quantidade]);

                PlayerTextDrawColor(playerid, menu_pstextdraws[text][playerid], -1);
                PlayerTextDrawColor(playerid, menu_pqtextdraws[text][playerid], -1);
                PlayerTextDrawBoxColor(playerid, menu_pstextdraws[text][playerid], 0x00000000);

                PlayerTextDrawShow(playerid, menu_pstextdraws[text][playerid]);
                PlayerTextDrawShow(playerid, menu_pqtextdraws[text][playerid]);
            }
        }
        case MENU_PAGE_ITENS: {

            Category_Selected[playerid] = MenuInfo[playerid][menu_selected];
            new positionid = Menu_Category[playerid][Category_Selected[playerid]][category_position],
                WEAPON:armaid,
                weapon_name[30];

            UpdatePageItens(playerid, itemid);

            for(new text; text < Menu_Category[playerid][Category_Selected[playerid]][category_quantidade]; text++) {
                armaid = WEAPON:Menu_Itens[playerid][text + positionid][menu_item_id];
                GetWeaponName(armaid, weapon_name);

                PlayerTextDrawSetString(playerid, menu_pstextdraws[text][playerid], weapon_name);
                PlayerTextDrawChangeString(small_string, playerid, "$%s", menu_pqtextdraws[text][playerid], getFormatText(Menu_Itens[playerid][text + positionid][menu_item_value]));

                PlayerTextDrawColor(playerid, menu_pstextdraws[text][playerid], -1);
                PlayerTextDrawColor(playerid, menu_pqtextdraws[text][playerid], -1);
                PlayerTextDrawBoxColor(playerid, menu_pstextdraws[text][playerid], 0x00000000);

                PlayerTextDrawShow(playerid, menu_pstextdraws[text][playerid]);
                PlayerTextDrawShow(playerid, menu_pqtextdraws[text][playerid]);
            }
        }
    }
    MenuInfo[playerid][menu_selected] = 0;

    UpdateItemSelected(playerid, MenuInfo[playerid][menu_selected]);
}

// Mostra o menu
stock ShowMenu(playerid) 
{
    for(new text; text < sizeof(menu_textdraws); text++) {
        TextDrawShowForPlayer(playerid, menu_textdraws[text]);
    }
    for(new text; text < sizeof(menu_ptextdraws); text++) {
        PlayerTextDrawShow(playerid, menu_ptextdraws[text][playerid]);
    }
    return 1;
}

// Oculta o menu
stock HideMenu(playerid) 
{
    for(new text; text < sizeof(menu_textdraws); text++) {
        TextDrawHideForPlayer(playerid, menu_textdraws[text]);
    }
    for(new text; text < sizeof(menu_ptextdraws); text++) {
        PlayerTextDrawHide(playerid, menu_ptextdraws[text][playerid]);
    }
    for(new text; text < sizeof(menu_pstextdraws); text++) {
        PlayerTextDrawHide(playerid, menu_pstextdraws[text][playerid]);
        PlayerTextDrawHide(playerid, menu_pqtextdraws[text][playerid]);
    }
    MenuResetItens(playerid);

    return MenuInfo[playerid][menu_id] = INVALID_MENU_ID;
}

// Muda o titulo e estilo do titulo principal
CALLBACK:ChangeMenuTitle(playerid, menuid) {
	if(menuid == ID_MENU_AMMUNATION) {
		PlayerTextDrawBoxColor(playerid, menu_ptextdraws[0][playerid], -1021765121);
        PlayerTextDrawColor(playerid, menu_ptextdraws[1][playerid], -1);
        PlayerTextDrawSetString(playerid, menu_ptextdraws[1][playerid], "Ammunation");
	}
}

// Muda as informações do topo
stock ChangeMenuHeaders(playerid, pageitem) {
    switch (pageitem)
    {
        case MENU_PAGE_MAIN: {
            PlayerTextDrawSetString(playerid, menu_ptextdraws[2][playerid], "CATEGORIA                                               ITENS");
        }
        case MENU_PAGE_ITENS: {
            PlayerTextDrawSetString(playerid, menu_ptextdraws[2][playerid], "NOME DO ITEM                UNIDADES             VALOR");
        }
    }
}

// Atualiza a seleção atual de textdraw
stock UpdateItemSelected(playerid, selectitem, pos=-1)
{
    // ID do item selecionado
    new string[20];
    format(string, sizeof(string), "%d/%d", MenuInfo[playerid][menu_selected]+1, MenuInfo[playerid][menu_max_itens]);
    PlayerTextDrawSetString(playerid, menu_ptextdraws[3][playerid], string);

    // Subir ou descer
    new oldpos;
    if (pos == MENU_PAGE_DOWN) {
        oldpos = selectitem-1;
    }
    else if (pos == MENU_PAGE_UP) {
        oldpos = selectitem+1;
    }

    // Old posição
    // Nome do item
    PlayerTextDrawHide(playerid, menu_pstextdraws[oldpos][playerid]);
    PlayerTextDrawColor(playerid, menu_pstextdraws[oldpos][playerid], -1);
    PlayerTextDrawBoxColor(playerid, menu_pstextdraws[oldpos][playerid], 0x00000000);
    PlayerTextDrawShow(playerid, menu_pstextdraws[oldpos][playerid]);

    // Quantidade do item
    PlayerTextDrawHide(playerid, menu_pqtextdraws[oldpos][playerid]);
    PlayerTextDrawColor(playerid, menu_pqtextdraws[oldpos][playerid], -1);
    PlayerTextDrawShow(playerid, menu_pqtextdraws[oldpos][playerid]);

    // New posição
    // Nome do item
    PlayerTextDrawHide(playerid, menu_pstextdraws[selectitem][playerid]);
    PlayerTextDrawColor(playerid, menu_pstextdraws[selectitem][playerid], 255);
    PlayerTextDrawBoxColor(playerid, menu_pstextdraws[selectitem][playerid], -1);
    PlayerTextDrawShow(playerid, menu_pstextdraws[selectitem][playerid]);

    // Quantidade do item
    PlayerTextDrawHide(playerid, menu_pqtextdraws[selectitem][playerid]);
    PlayerTextDrawColor(playerid, menu_pqtextdraws[selectitem][playerid], 255);
    PlayerTextDrawShow(playerid, menu_pqtextdraws[selectitem][playerid]);
}

stock OpenMenu(playerid, menuid=-1) 
{
    MenuInfo[playerid][menu_id] = menuid;

    CallLocalFunction("ChangeMenuTitle", "ii", playerid, menuid);
    CallLocalFunction("MenuSetItens", "ii", playerid, menuid);
    ShowMenu(playerid);

    ChangeMenuPage(playerid, MENU_PAGE_MAIN);

    if (IsAndroidPlayer(playerid)) {
        ShowPlayerMessage(playerid, "Pressione ~g~Y ~w~para cima e ~g~N ~w~para baixo~n~Selecione usando ~g~H ~w~e para voltar use ~g~F", 15000);
    }
    else {
        ShowPlayerMessage(playerid, "Pressione ~g~W ~w~para cima e ~g~S ~w~para baixo~n~Selecione usando ~g~ESPACO ~w~e para voltar use ~g~ENTER", 15000);
    }
}

CALLBACK:MenuSetItens(playerid, menuid) {

    MenuInfo[playerid][menu_item] = 1;

    switch (menuid) {
        case ID_MENU_AMMUNATION:
        {
            MenuInfo[playerid][menu_max_itens] = sizeof(AMMU_Category);

            for(new i; i < sizeof(AMMU_Category); i++) {
                Menu_Category[playerid][i][category_id]                     = AMMU_Category[i][category_id];
                format(Menu_Category[playerid][i][category_nome], 20,       AMMU_Category[i][category_nome]);
                Menu_Category[playerid][i][category_quantidade]             = AMMU_Category[i][category_quantidade];
                Menu_Category[playerid][i][category_position]               = AMMU_Category[i][category_position];
            }
            for(new i; i < sizeof(AMMU_Item); i++) {
                Menu_Itens[playerid][i][menu_item_id]                       = AMMU_Item[i][menu_item_id];
                Menu_Itens[playerid][i][menu_item_value]                    = AMMU_Item[i][menu_item_value];
                Menu_Itens[playerid][i][menu_animlib]                       = AMMU_Item[i][menu_animlib];
                Menu_Itens[playerid][i][menu_animname]                      = AMMU_Item[i][menu_animname];
            }
        }
        case ID_MENU_BURGUERSHOT:
        {
            MenuInfo[playerid][menu_max_itens] = sizeof(BurguerShot_Item);

            for(new i; i < sizeof(BurguerShot_Category); i++) {
                Menu_Category[playerid][i][category_id]                     = BurguerShot_Category[i][category_id];
                format(Menu_Category[playerid][i][category_nome], 20,       BurguerShot_Category[i][category_nome]);
                Menu_Category[playerid][i][category_quantidade]             = BurguerShot_Category[i][category_quantidade];
                Menu_Category[playerid][i][category_position]               = BurguerShot_Category[i][category_position];
            }
            for(new i; i < sizeof(BurguerShot_Item); i++) {
                Menu_Itens[playerid][i][menu_item_id]                       = BurguerShot_Item[i][menu_item_id];
                Menu_Itens[playerid][i][menu_item_value]                    = BurguerShot_Item[i][menu_item_value];
                Menu_Itens[playerid][i][menu_animlib]                       = BurguerShot_Item[i][menu_animlib];
                Menu_Itens[playerid][i][menu_animname]                      = BurguerShot_Item[i][menu_animname];
            }
        }
    }
}

stock MenuResetItens(playerid)
{
    static const 
                empty_menuitens[enumMenuItem],
                empty_menucateg[enumMenuCategory];
    
    for(new loop; loop < MAX_MENU_CATEGORY; loop++) {
        Menu_Category[playerid][loop] = empty_menucateg;
    }
    for(new loop; loop < MAX_MENU_ITENS; loop++) {
        Menu_Itens[playerid][loop] = empty_menuitens;
    }
  
    return 1;
}