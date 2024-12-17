/**--------------------------------------------------------------------------**\
 ______ ______  ______     __  ______  ______  ______     ______  __  ______ __  __
/\  == /\  == \/\  __ \   /\ \/\  ___\/\  ___\/\__  _\   /\  ___\/\ \/\__  _/\ \_\ \
\ \  _-\ \  __<\ \ \/\ \ _\_\ \ \  __\\ \ \___\/_/\ \/   \ \ \___\ \ \/_/\ \\ \____ \
 \ \_\  \ \_\ \_\ \_____/\_____\ \_____\ \_____\ \ \_\    \ \_____\ \_\ \ \_\\/\_____\
  \/_/   \/_/ /_/\/_____\/_____/\/_____/\/_____/  \/_/     \/_____/\/_/  \/_/ \/_____/

						 ==========================
		                    Brasil Play Start
                              ® 2013 - 2017
                   			Módulo: Evento survival
						 ==========================

\**--------------------------------------------------------------------------**/

#include <YSI_Coding\y_hooks>

#define SendSurvivalMessage(%1) foreach(new xplayerid:IterSurvival) SendClientMessage(xplayerid, 0xFF0000FF, %1)

new
	Iterator:IterSurvival<MAX_PLAYERS>,
	SurvivalStats[MAX_PLAYERS],
	Text:textSurvival,
	SurvivalTimer = -1,
	bool:SurvivalInitialized = false
;

stock CreateTextSurvival()
{
	textSurvival = TextDrawCreate(310.000000, 380.000000, "~b~Humanos ~w~~h~0 x 0 ~r~Zombies");
	TextDrawAlignment(textSurvival, TEXT_DRAW_ALIGN_CENTER);
	TextDrawBackgroundColor(textSurvival, 50);
	TextDrawFont(textSurvival, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textSurvival, 0.530000, 2.300000);
	TextDrawColor(textSurvival, -1);
	TextDrawSetOutline(textSurvival, 1);
	TextDrawSetProportional(textSurvival, true);
	TextDrawSetSelectable(textSurvival, false);
}

stock InitializeSurvival()
{
	if (SurvivalInitialized) return false;

	CreateTextSurvival();
	SurvivalInitialized = true;
	SurvivalTimer = -1;
	
	return true;
}

stock StartSurvival()
{
	if (SurvivalTimer != -1) KillTimer(SurvivalTimer);

	SurvivalTimer = SetTimer("UpdateSurvival", 1000, true);
	
	SetPlayerZombie(Iter_Random(IterSurvival));
}

stock IsPlayerInSurvival(playerid) return Iter_Contains(IterSurvival, playerid);

stock DestroySurvival()
{
	if (!SurvivalInitialized) return false;

	TextDrawDestroy(textSurvival);
	SurvivalInitialized = false;

	KillTimer(SurvivalTimer);
	
	SurvivalTimer = -1;
	
	foreach(new playerid : IterSurvival)
	{
	    SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	    SetPlayerToTeamColor(playerid);
	    SetPlayerPos(playerid, 1769.5328,-1863.3152,13.5752);
		SetPVarInt(playerid, "BlockJetpack", 0);
		SetPVarInt(playerid, "BlockInventory", 0);

		if (Admin_GetNivel(playerid) < ENCARREGADO && Staff_GetWorking(playerid)) {
			goto skip_admin_armassurvival;
		}

		GivePlayerTempWeapons(playerid);

		skip_admin_armassurvival:
	}
	for (new playerid; playerid != MAX_PLAYERS; playerid++)
	{
	    Iter_Remove(IterSurvival, playerid);
	    SurvivalStats[playerid] = 0;
	}
	return true;
}

stock EndSurvival()
{
	new string[102];

	foreach(new playerid : IterSurvival)
	{
	    if (!SurvivalStats[playerid])
		{
			format(string, sizeof string, "[SURVIVAL] %s sobreviveu ao ataque dos zombies e ganhou o evento, parabéns!", PlayerName[playerid]);
			SendClientMessageToAll(0xFF0000FF, string);
	    }
	}
	
	DestroySurvival();
}

stock AtualizeTextSurvival()
{
	new zombies;
	new humans;
	
	foreach(new playerid : IterSurvival)
	{
	    if (!SurvivalStats[playerid]) humans ++;
	    else zombies ++;
	}
	
	new string[45];
	format(string, sizeof string, "~b~Humanos ~w~~h~%d x %d ~r~Zombies", humans, zombies);
	TextDrawSetString(textSurvival, string);
}

stock SetPlayerInSurvival(playerid)
{
	Iter_Add(IterSurvival, playerid);
	SurvivalStats[playerid] = 0;
	SetPVarInt(playerid, "BlockJetpack", 1);
	SetPVarInt(playerid, "BlockInventory", 1);
	BlockPlayerTempWeapons(playerid);
	
	SetPlayerPos(playerid, -1467.2277 + randomfloat(3.0) - randomfloat(3.0), 1490.0062 + randomfloat(3.0) - randomfloat(3.0), 8.2578);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerSkin(playerid, 26);
	SetPlayerColor(playerid, 0x0000FFFF);
	ResetPlayerWeapons(playerid);
	SetPlayerHealth(playerid, 100.0);
	SetPlayerArmour(playerid, 100.0);
	
	AtualizeTextSurvival();
	TextDrawShowForPlayer(playerid, textSurvival);
}

stock SetZombieSurvival(playerid) {
    SetPlayerPos(playerid, -1467.2277 + randomfloat(3.0) - randomfloat(3.0), 1490.0062 + randomfloat(3.0) - randomfloat(3.0), 8.2578);
}

stock SetPlayerZombie(playerid)
{
	if (Iter_Contains(IterSurvival, playerid))
	{
	    if (!SurvivalStats[playerid])
		{
			SetPlayerSkin(playerid, 162);
		    SurvivalStats[playerid] = 1;
		    TogglePlayerControllable(playerid, true);
		    SetPlayerColor(playerid, 0xFF0000FF);

		    new string[83];
		    format(string, sizeof string, "* O jogador %s foi transformado em um zombie, fuja dele!", PlayerName[playerid]);
		    SendSurvivalMessage(string);
		    
		    ApplyAnimation(playerid, "SWEET","Sweet_injuredloop",4.1, true, true, true, true, 0, SYNC_ALL);
		    SetTimerEx("animZombie", 5000, false, "i", playerid);
		    
		    GameTextForPlayer(playerid, "~r~Voce agora e um zombie, pegue os humanos", 5000, 5);
		}
	}
}

stock CountSurvivalHumans()
{
	new count;
	
	foreach(new playerid : IterSurvival)
	{
	    if (!SurvivalStats[playerid]) count++;
	}
	return count;
}

stock SurvivalInWather(playerid)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	
	if (z <= 0.1) return true;
	
	return false;
}

stock SurvivalDamage(playerid, damagedid)
{
	if (!SurvivalInitialized) return false;

	if (Iter_Contains(IterSurvival, playerid) && Iter_Contains(IterSurvival, damagedid)) {

		SetPlayerHealth(playerid, 100.0);
		SetPlayerHealth(damagedid, 100.0);

		if (SurvivalTimer != -1) {

		    if (SurvivalStats[playerid] && !SurvivalStats[damagedid]) {
		        SetPlayerZombie( damagedid );
		        
				new string[76];
				format(string, sizeof string, "Você transformou %s em um zombie, ganhou +$500", PlayerName[damagedid]);
				SendClientMessage(playerid, 0xFFFF00FF, string);
				Player_RemoveMoney(playerid, 500);
				
				createDropBox(damagedid);
		    }
		}
	}
	return 1;
}

CALLBACK: UpdateSurvival()
{
	foreach(new playerid : IterSurvival)
	{
	    if (SurvivalInWather(playerid))
		{
            SetZombieSurvival(playerid);
            
			if (!SurvivalStats[playerid]) SetPlayerZombie(playerid);
	    }
	}
	
    AtualizeTextSurvival();
    
	if (CountSurvivalHumans() < 2) EndSurvival();
	
	return true;
}

CALLBACK: animZombie(playerid)
{
	ClearAnimations(playerid);
	TogglePlayerControllable(playerid, true);
}


CMD:criarsurvival(playerid)
{
  	if (Admin_GetNivel(playerid) < ENCARREGADO) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (SurvivalTimer != -1) return SendClientMessage(playerid, -1, "Survival já criado, digite /destruirsurvival para destruir ou /iniciarsurvival para iniciar!");

	new string[128];
	SendClientMessageToAll(TEAM_BALLAS_COLOR, "_______________________________________________________________________________________________________________");
	format(string, sizeof string, "SURVIVAL: %s, %s iniciou um evento Survival, vá ate a empresa de eventos para participar.", Staff_GetPositionName(playerid), PlayerName[playerid]);
	SendClientMessageToAll(TEAM_BALLAS_COLOR, string);
	SendClientMessageToAll(TEAM_BALLAS_COLOR, "_______________________________________________________________________________________________________________");

    InitializeSurvival(); typeevento = 4;

	return true;
}

CMD:destruirsurvival(playerid)
{
	if (Admin_GetNivel(playerid) < ENCARREGADO) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	DestroySurvival();

	new string[82];
	format(string, sizeof string, "* %s, %s destruiu o evento survival!", Staff_GetPositionName(playerid), PlayerName[playerid]);
	SendClientMessageToAll(TEAM_BALLAS_COLOR, string);
	
	return true;
}

CMD:iniciarsurvival(playerid)
{
	if (Admin_GetNivel(playerid) < ENCARREGADO) return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");

	if (!SurvivalInitialized) return SendClientMessage(playerid, -1, "Survival não criado, digite /criarsurvival para criar!");

    if (Iter_Count(IterSurvival) < 10) return SendClientMessage(playerid, -1, "Para iniciar o evento é necessário no mínimo 10 jogadores.");

	GameTextForAll("~r~Survival iniciado!", 5000, 1);

    StartSurvival();

	new string[112];
	format(string, sizeof string, "[SURVIVAL]: %s, %s iniciou o evento, boa sorte aos participantes!", Staff_GetPositionName(playerid), PlayerName[playerid]);
	SendClientMessageToAll(COLOR_YELLOW, string);

	return true;
}

hook OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart)
{
	if (issuerid != INVALID_PLAYER_ID) {
		// Evento zombie?
		SurvivalDamage(issuerid, playerid); // Evento: Zombie
	}
	return 1;
}

hook OnPlayerDeathFinished(playerid)
{
    Iter_Remove(IterSurvival, playerid);
    return 1;
}