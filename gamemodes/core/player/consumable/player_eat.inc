// --------------------------------------------------------------------
// Sistema de comidas e bebidas do personagem

#define         TIME_PLAYER_FOOD            1000*3      // Quantidade de tempo para comer a comida/beber a bebida

#define         ITEM_MODEL_CARNE            19882
#define         ITEM_MODEL_PAO              19883
#define         ITEM_MODEL_PIZZA            2881
#define         ITEM_MODEL_FRANGO           19847
#define         ITEM_MODEL_BURGUER          2880
#define         ITEM_MODEL_HOTDOG           19346

stock giveFome(playerid, Float:quantia)
{
    PlayerInfo[playerid][pFome] += quantia;

	if (PlayerInfo[playerid][pFome] > 100.0) {
	    PlayerInfo[playerid][pFome] = 100.0;
	}

	if (PlayerInfo[playerid][pFome] < 1.0) {
	    PlayerInfo[playerid][pFome] = 1.0;
	}

	return 1;
}

stock giveSede(playerid, Float:quantia)
{
    PlayerInfo[playerid][pSede] += quantia;

	if (PlayerInfo[playerid][pSede] > 100.0)
	    PlayerInfo[playerid][pSede] = 100.0;

	if (PlayerInfo[playerid][pSede] < 1.0)
	    PlayerInfo[playerid][pSede] = 1.0;

   	return 1;
}

stock UpdatePlayerFomeSede(playerid)
{
	if (!Player_Logado(playerid)) 
		return 1;

	// Nomes que não perdem fome/sede de jeito nenhum
	if (!Founders_GetList(playerid) && Player_GetTimerAFK(playerid) < 1 && !Staff_GetWorking(playerid)) {
		if (PlayerInfo[playerid][pVIP] < 8)
		{
			if (PlayerInfo[playerid][pFome] > 1.5) PlayerInfo[playerid][pFome] -= 0.006;
			if (PlayerInfo[playerid][pSede] > 1.5) PlayerInfo[playerid][pSede] -= 0.009;
		}
		else
		{
			if (PlayerInfo[playerid][pFome] > 1.5) PlayerInfo[playerid][pFome] -= 0.004;
			if (PlayerInfo[playerid][pSede] > 1.5) PlayerInfo[playerid][pSede] -= 0.007;
		}
	}

	if(PlayerInfo[playerid][pFome] > 100.0)
		PlayerInfo[playerid][pFome] = 100.0;
	if(PlayerInfo[playerid][pSede] > 100.0)
		PlayerInfo[playerid][pSede] = 100.0;

	HUD_UpdateNeeds(playerid, PlayerInfo[playerid][pFome], PlayerInfo[playerid][pSede]);

	if (PlayerInfo[playerid][pFome] < 10.0 or PlayerInfo[playerid][pSede] < 10.0)
	{
		new Float:playerHealth,
			Float:playerArmour;

		GetPlayerHealth(playerid, playerHealth);
		GetPlayerArmour(playerid, playerArmour);

		if (PlayerInfo[playerid][pFome] < 10.0)
		{
			if (playerArmour > 0.0)
			    SetPlayerArmour(playerid, playerArmour - (randomfloat(0.4) + 0.1));

			else
			{
			    if (playerHealth > 5.5)
			    	SetPlayerHealth(playerid, playerHealth - (randomfloat(0.2) + 0.1));
			}
		}

		GetPlayerHealth(playerid, playerHealth);
		GetPlayerArmour(playerid, playerArmour);

		if (PlayerInfo[playerid][pSede] < 10.0)
		{
			if (playerArmour > 0.0)
			    SetPlayerArmour(playerid, playerArmour - (randomfloat(0.4) + 0.1));

			else
			{
			    if (playerHealth > 5.5)
			    	SetPlayerHealth(playerid, playerHealth - (randomfloat(0.2) + 0.1));
			}
		}
	}
	return 1;
}

stock ApplyAnimationFood(playerid)
{
    new modelid = GetPVarInt(playerid, "right_hand_object");

    switch (modelid)
    {
        case ITEM_MODEL_FRANGO:
        {
            ApplyAnimation(playerid,"FOOD","EAT_Chicken", 4.1, false, false, false, false, TIME_PLAYER_FOOD, SYNC_NONE);
        }
        default: 
        {
            ApplyAnimation(playerid,"FOOD","EAT_Pizza", 4.1, false, false, false, false, TIME_PLAYER_FOOD, SYNC_NONE);
        }
    }

    // Som de comendo;
    PlayerPlaySound(playerid, 32200, 0.0, 0.0, 0.0);
}