CMD:criaritem(playerid, params[])
{
    if (!Player_Logado(playerid))
        return SendClientMessage(playerid, -1, "Você não está logado.");

    if (Dev_GetNivel(playerid) < DEV_ALPHA) 
        return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");
    
    new itemtype, modelid, quantidade, itemnome[MAX_ITEM_INV_NAME], cor1, cor2;
    if (sscanf(params, "ddddds[25]", itemtype, modelid, quantidade, cor1, cor2, itemnome)) 
        return SendClientMessage(playerid, -1, "Modo de uso: /criaritem (type) (model) (quantidade) (cor1) (cor2) (nome do item)");

    new string[128];
    format(string, sizeof(string), "AdmAviso: %s criou item (type: %d, model: %d, qtd: %d, colors: %d, %d, '%s').", PlayerName[playerid], itemtype, modelid, quantidade, cor1, cor2, itemnome);
    Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO);
    
    format(string, sizeof(string), "[/criaritem] %s criou (type: %d, model %d, quantidade %d, cor1: %d, cor 2: %d, nome: %s)", PlayerName[playerid], itemtype, modelid, quantidade, cor1, cor2, itemnome);
    server_log("dev", string);

    givePlayerItem(playerid, itemtype, modelid, quantidade, itemnome, cor1, cor2);
    return 1;
}