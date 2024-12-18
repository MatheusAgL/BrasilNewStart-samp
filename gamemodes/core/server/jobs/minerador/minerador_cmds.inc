CMD:minerar(playerid)
{
    if (!PlayerIsMinerador(playerid)) 
		return SendClientMessage(playerid, -1, "Voc� n�o � um minerador.");

    if (CarryingOre[playerid] != -1) 
		return SendClientMessage(playerid, -1, "Voc� j� est� carregando um min�rio.");

    new id = Player_GetClosestVein(playerid);
    if (id == -1) 
		return SendClientMessage(playerid, -1, "Voc� n�o est� perto de nenhum min�rio.");

    if (VeinData[id][BeingMined]) 
		return SendClientMessage(playerid, -1, "O minerio que voc� quer mina est� sendo minerada por outra pessoa.");

    if (VeinData[id][AmountOres] < 1) 
		return SendClientMessage(playerid, -1, "O minerio que voc� quer minerar est� vazio.");

    MiningVein[playerid] = id;
    MiningTimer[playerid] = repeat timerMineracao(playerid);
    SetPlayerAttachedObject(playerid, ATTACH_INDEX, 19631, 6, 0.048, 0.029, 0.103, -80.0, 80.0, 0.0);

	new Float:coord[4];
	GetPlayerPos(playerid, coord[0], coord[1], coord[2]);
	GetPlayerFacingAngle(playerid, coord[3]);
	GetXYInFrontOfPoint(coord[0], coord[1], coord[3] + 45.0, 6.0);
	SetPlayerCameraPos(playerid, coord[0], coord[1], coord[2]+2.50);

	GetPlayerPos(playerid, coord[0], coord[1], coord[2]);
	SetPlayerCameraLookAt(playerid, coord[0], coord[1], coord[2]);

    TogglePlayerControllable(playerid, false);
    SetPlayerArmedWeapon(playerid, WEAPON_FIST);
    ApplyAnimation(playerid, "BASEBALL", "Bat_4", 4.1, true, false, false, true, 0, SYNC_ALL);

    new string[64];
    format(string, sizeof(string), "~n~~y~~h~Minerando %s...", OreData[ VeinData[id][Type] ][NameOres]);
    GameTextForPlayer(playerid, string, floatround(Vein_CalculateTime(id)) + 1000, 3);

    VeinData[id][BeingMined] = true;
    Vein_Update(id);

    return 1;
}


CMD:pegarminerio(playerid) 
{
    if (!PlayerIsMinerador(playerid)) 
		return SendClientMessage(playerid, -1, "Voc� n�o � um minerador!");

    new id = Player_GetClosestOre(playerid);
    if (id == -1) 
		return SendClientMessage(playerid, -1, "Voc� n�o est� pr�ximo de um min�rio.");

    Player_GiveOre(playerid, DroppedOres[id][Type]);
    Ore_Destroy(id);

    return 1;
}

CMD:venderminerio(playerid)
{
	if (!PlayerIsMinerador(playerid)) 
        return SendClientMessage(playerid, -1, "Voc� n�o � um minerador.");
    else if (!PlayerToPoint(2, playerid, 990.2281,-78.3008,21.6394))
		return SendClientMessage(playerid, -1, "Voc� n�o est� no local de venda de min�rios.");
	else if (CarryingOre[playerid] == -1)
		return SendClientMessage(playerid, -1, "Voc� n�o est� com um min�rio em m�os.");

	new ore_id = CarryingOre[playerid], cash = OreData[ore_id][ValueOres];

	new governo_cut = cash / 4; // 25% para o governo
	new player_salary = cash - governo_cut; // 75% para o jogador


	adicionarDinheiroGoverno(governo_cut);

	SendMsgF(playerid, 0xE0D78AFF, "<< Mineradora >> {FFFFFF}Voc� vendeu {%s}%s {FFFFFF}e foi adicionado {00AA00}$%s {FFFFFF}ao seu sal�rio.", OreData[ore_id][ColorStr], OreData[ore_id][NameOres], getFormatText(player_salary));
	
	PlayerInfo[playerid][pSalario] += player_salary;
	Player_CleanUp(playerid, 1);
    
	return 1;
}

CMD:infominerio(playerid)
{
    if (!PlayerIsMinerador(playerid)) 
        return SendClientMessage(playerid, -1, "Voc� n�o � um minerador.");

    new id = Player_GetClosestVein(playerid);
    if (id == -1) 
		return SendClientMessage(playerid, -1, "Voc� n�o est� perto de um minerio.");

    new 
		string[128], 
		type = VeinData[id][Type]
	;

    format(string, sizeof(string), "Nome\t{%06x}%s\nValor\t{2ECC71}$%d\nValor do min�rio\t{2ECC71}$%d\nTempo de minera��o\t%.2f segundos", OreData[type][Color] >>> 8, OreData[type][NameOres], OreData[type][ValueOres], (OreData[type][ValueOres] * VeinData[id][AmountOres]), Vein_CalculateTime(id) / 1000);
    ShowPlayerDialog(playerid, DIALOG_ORE_INFO, DIALOG_STYLE_TABLIST, "Min�rio Informa��o", string, "Close", "");
    
	return 1;
}