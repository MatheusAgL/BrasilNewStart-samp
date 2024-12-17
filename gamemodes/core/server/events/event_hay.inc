//--------------- Hay evento ---------------------------------------------------
#define HAY_X            	4
#define HAY_Y 	        	4
#define HAY_Z           	30
#define HAY_B          		146
#define HAY_R            	4
#define SPEED_FACTOR     	3000.0
#define ID_HAY_OBJECT    	3374

//------------------------------------------------------------------------------

//news
new Matrix[HAY_X][HAY_Y][HAY_Z];
new Speed_xy;
new Speed_z;
new Center_x;
new Center_y;
new Hays[HAY_B];
new TimerHay;
new hayObject;
new hayiniciado;
new pickHay;
new moneyHay;

//------------------------------------------------------------------------------

stock DestroyHay()
{
    for (new obj; obj < HAY_B ; obj++)
    {
        if (IsValidDynamicObject(Hays[obj]))
            DestroyDynamicObject(Hays[obj]);
    }

    KillTimer(TimerHay);
    DestroyDynamicObject(hayObject);
    DestroyDynamicPickup(pickHay);

    foreach (new i : Player)
    {
        if (JoinedHay[i])
        {
            JoinedHay[i] = false;
            SetPVarInt(i, "BlockJetpack", 0);
            SetPVarInt(i, "BlockInventory", 0);
            GivePlayerTempWeapons(i);
            SpawnPlayer(i);
        }
    }
}

stock SetPlayerHay(playerid)
{
    SetPVarInt(playerid, "BlockJetpack", 1);
    SetPVarInt(playerid, "BlockInventory", 1);
    BlockPlayerTempWeapons(playerid);

    JoinedHay[playerid] = true;
    SetPlayerPos(playerid, 0, 6.5, 3.2);
    SetPlayerFacingAngle(playerid, 135);
    SetPlayerVirtualWorld(playerid, 50);
    SetPlayerHealth(playerid, 100.0);
    ResetPlayerWeapons(playerid);
}

stock winHay(playerid)
{
    new string_hay[62 + MAX_PLAYER_NAME];

    format(string_hay, sizeof string_hay, "[EVENTO]: %s(%d) chegou ao topo e ganhou $%s como prêmio.", PlayerName[playerid], playerid, getFormatText(moneyHay));
    SendClientMessageToAll(COLOR_LIGHTBLUE, string_hay);

    Player_AddMoney(playerid, moneyHay);
}

RestartEveryThing()
{
    new xq, yq, zq;
    new Number;

    Speed_xy = 2000 / (HAY_Z + 1);
    Speed_z = 1500 / (HAY_Z + 1);
    for (xq = 0 ; xq < HAY_X ; xq++)
    {
        for (yq = 0 ; yq < HAY_Y ; yq++)
        {
            for (zq = 0 ; zq < HAY_Z ; zq++)
            {
                Matrix[xq][yq][zq] = 0;
            }
        }
    }
    for (Number = 0 ; Number < HAY_B ; Number++)
    {
        do
        {
            xq = random(HAY_X);
            yq = random(HAY_Y);
            zq = random(HAY_Z);
        }
        while (Matrix[xq][yq][zq] != 0);
        Matrix[xq][yq][zq] = 1;
        Hays[Number] = CreateDynamicObject(ID_HAY_OBJECT, xq * (-4), yq * (-4), (zq + 1) * 3, 0.0, 0.0, random(2) * 180, 50);
    }
    Center_x = (HAY_X + 1) * -2;
    Center_y = (HAY_Y + 1) * -2;
    hayObject = CreateDynamicObject(ID_HAY_OBJECT, Center_x, Center_y, HAY_Z * 3 + 3, 0, 0, 0, 50);
    TimerHay = SetTimer("TimerMove", 100, false);
    pickHay = CreateDynamicPickup(1210, 24, -9.7836, -9.9502, 95.5060, 50);
}

//------------------------------------------------------------------------------

CALLBACK:TimerMove()
{
    new rand;
    new Hay;
    new Move = -1;
    new xq, yq, zq;
    new Float:x2, Float:y2, Float:z2;
    new Timez;
    new Float:Speeed;

    rand = random(HAY_B);
    Hay = Hays[rand];
    if (IsDynamicObjectMoving(Hay))
    {
        TimerHay = SetTimer("TimerMove", 200, false);
        return 1;
    }
    Move = random(6);
    GetDynamicObjectPos(Hay, x2, y2, z2);
    xq = floatround(x2 / -4.0);
    yq = floatround(y2 / -4.0);
    zq = floatround(z2 / 3.0) - 1;
    if ((Move == 0)  && (xq != 0) && (Matrix[xq - 1][yq][zq] == 0))
    {
        Timez = 4000 - Speed_xy * zq;
        Speeed = SPEED_FACTOR / float (Timez);
        SetTimerEx("FinishTimer", Timez, false, "iiii", rand, xq, yq, zq);
        xq = xq - 1;
        Matrix[xq][yq][zq] = 1;
        MoveDynamicObject(Hay, x2 + 4.0, y2, z2, Speeed);
    }

    else if ((Move == 1) && (xq != HAY_X - 1) && (Matrix[xq + 1][yq][zq] == 0))
    {
        Timez = 4000 - Speed_xy * zq;
        Speeed = SPEED_FACTOR / float (Timez);
        SetTimerEx("FinishTimer", Timez, false, "iiii", rand, xq, yq, zq);
        xq = xq + 1;
        Matrix[xq][yq][zq] = 1;
        MoveDynamicObject(Hay, x2 - 4.0, y2, z2, Speeed);
    }

    else if ((Move == 2) && (yq != 0) && (Matrix[xq][yq - 1][zq] == 0))
    {
        Timez = 4000 - Speed_xy * zq;
        Speeed = SPEED_FACTOR / float (Timez);
        SetTimerEx("FinishTimer", Timez, false, "iiii", rand, xq, yq, zq);
        yq = yq - 1;
        Matrix[xq][yq][zq] = 1;
        MoveDynamicObject(Hay, x2, y2 + 4.0, z2, Speeed);
    }


    else if ((Move == 3) && (yq != HAY_Y - 1) && (Matrix[xq][yq + 1][zq] == 0))
    {
        Timez = 4000 - Speed_xy * zq;
        Speeed = SPEED_FACTOR / float (Timez);
        SetTimerEx("FinishTimer", Timez, false, "iiii", rand, xq, yq, zq);
        yq = yq + 1;
        Matrix[xq][yq][zq] = 1;
        MoveDynamicObject(Hay, x2, y2 - 4.0, z2, Speeed);
    }

    else if ((Move == 4) && (zq != 0) && (Matrix[xq][yq][zq - 1] == 0))
    {
        Timez = 3000 - Speed_z * zq;
        Speeed = SPEED_FACTOR / float (Timez);
        SetTimerEx("FinishTimer", Timez, false, "iiii", rand, xq, yq, zq);
        zq = zq - 1;
        Matrix[xq][yq][zq] = 1;
        MoveDynamicObject(Hay, x2, y2, z2 - 3.0, Speeed);
    }

    else if ((Move == 5) && (zq != HAY_Z - 1) && (Matrix[xq][yq][zq + 1] == 0))
    {
        Timez = 3000 - Speed_z * zq;
        Speeed = SPEED_FACTOR / float (Timez);
        SetTimerEx("FinishTimer", Timez, false, "iiii", rand, xq, yq, zq);
        zq = zq + 1;
        Matrix[xq][yq][zq] = 1;
        MoveDynamicObject(Hay, x2, y2, z2 + 3.0, Speeed);
    }
    else if ((Move == 6) && (zq != HAY_Z - 1) && (Matrix[xq][yq][zq + 1] == 0))
    {
        Timez = 3000 - Speed_z * zq;
        Speeed = SPEED_FACTOR / float (Timez);
        SetTimerEx("FinishTimer", Timez, false, "iiii", rand, xq, yq, zq);
        zq = zq + 1;
        Matrix[xq][yq][zq] = 1;
        MoveDynamicObject(Hay, x2, y2, z2 + 3.0, Speeed);
    }
    TimerHay = SetTimer("TimerMove", 200, false);
    return 1;
}

//------------------------------------------------------------------------------

CALLBACK:FinishTimer(id, xq, yq, zq)
{
    Matrix[xq][yq][zq] = 0;
}

// -----------------------------------------------------------------------------------------------------------
// ENCARREGADO:

CMD:iniciarhay(playerid, params[])
{
    if (Admin_GetNivel(playerid) < ENCARREGADO) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (sscanf(params, "d", moneyHay)) return SendClientMessage(playerid, -1, "Modo de uso: /iniciarhay (valor do prêmio)");

	if (hayiniciado) return SendClientMessage(playerid, -1, "O evento Hay já está iniciado, use /destruirhay.");

	if (GetPlayerMoney(playerid) < moneyHay) return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiente para pagar o prêmio.");

	if (moneyHay < 10000) return SendClientMessage(playerid, -1, "O prêmio deve ser acima de $10.000.");

	Player_RemoveMoney(playerid, moneyHay);

    new string[128];

	SendClientMessageToAll(TEAM_BALLAS_COLOR, "__________________________________________________________________________________________________________________");
	format(string, sizeof string, "EVENTO: %s, %s criou um evento HAY, vá até a empresa para participar do evento!", Staff_GetPositionName(playerid), PlayerName[playerid]);
	SendClientMessageToAll(TEAM_BALLAS_COLOR, string);
	format(string, sizeof string, "Prêmio do evento: $%s", getFormatText(moneyHay));
	SendClientMessageToAll(TEAM_BALLAS_COLOR, string);
    SendClientMessageToAll(TEAM_BALLAS_COLOR, "__________________________________________________________________________________________________________________");

	hayiniciado = 1;
	typeevento = 3;

	RestartEveryThing();

	foreach(new i : Player)
	    JoinedHay[i] = false;

	return true;
}

CMD:destruirhay(playerid)
{
	if (Admin_GetNivel(playerid) < ENCARREGADO) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	new string[128];

	format(string, sizeof string, "[EVENTO]: %s, %s destruiu o evento HAY!", Staff_GetPositionName(playerid), PlayerName[playerid]);
	SendClientMessageToAll(TEAM_BALLAS_COLOR, string);

	hayiniciado = 0;

	DestroyHay();

    foreach(new i : Player)
	    JoinedHay[i] = false;

	return 1;
}