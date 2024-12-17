#include <YSI_Coding\y_hooks>

#include <minerador_entry>

timer timerMineracao[UPDATE_RATE](playerid)
{
    if (MiningVein[playerid] != -1) {
	    new vein_id = MiningVein[playerid];

	    Player_CleanUp(playerid);
		SetCameraBehindPlayer(playerid);

		if (random(100) < OreData[ VeinData[vein_id][Type]][Rate]) 
		{
 			VeinData[vein_id][AmountOres]--;
			Player_GiveOre(playerid, VeinData[vein_id][Type]);
   			Vein_Update(vein_id);

	    	new string[64];
	    	format(string, sizeof(string), "~n~~g~~h~Minerado %s", OreData[VeinData[vein_id][Type]][NameOres]);
	    	GameTextForPlayer(playerid, string, 2000, 3);

		} else GameTextForPlayer(playerid, "~n~~r~~h~MINERIO NAO ENCONTRADO", 2000, 3);
	}
	return 1;
}

#include <minerador_cmds>
#include <minerador_map>

hook OnPlayerResetVars(playerid)
{
	MiningVein[playerid] = -1;
	CarryingOre[playerid] = -1;

	return 1;
}

Player_GiveOre(playerid, type, cooldown = 0) 
{
    CarryingOre[playerid] = type;
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
	SetPlayerAttachedObject(playerid, ATTACH_INDEX, 2936, 5, 0.105, 0.086, 0.22, -80.3, 3.3, 28.7, 0.35, 0.35, 0.35, RGBAToARGB(OreData[type][Color]));
	SetPVarInt(playerid, "LoadingCooldown", gettime() + cooldown);

    SendClientMessage(playerid, COLOR_LIGHTBLUE, "Para soltar o minerio aperte '"C_YELLOW"H"C_LIGHTBLUE"'.");

	return 1;
}

// Vein Functions
Vein_Update(id)
{
	new label[64], 
		bool: is_red = false,
		type = VeinData[id][Type];

	if (VeinData[id][BeingMined] || VeinData[id][AmountOres] < 1) 
		is_red = true;

	format(label, sizeof(label), "%s\n%d/%d%s\nPressione ALT para minerar ou /infominerio", OreData[type][NameOres], VeinData[id][AmountOres], OreData[type][AmountOres], (is_red) ? ("{E74C3C}") : ("{FFFFFF}"));
	UpdateDynamic3DTextLabelText(VeinData[id][VeinLabel], OreData[type][Color], label);

	return 1;
}

// Ore Functions
Ore_FindFreeID()
{
	new id = -1;
	for (new i; i < MAX_ORES; i++) {
	    if(!DroppedOres[i][OreExists]) {
	        id = i;
	        break;
	    }
	}
	return id;
}

Player_CleanUp(playerid, ore = 0)
{
    if (MiningVein[playerid] != -1)
	{
		VeinData[ MiningVein[playerid] ][BeingMined] = false;
        Vein_Update(MiningVein[playerid]);
        ClearAnimations(playerid);
        TogglePlayerControllable(playerid, true);
        MiningVein[playerid] = -1;
	}

	stop MiningTimer[playerid];

	if(ore && CarryingOre[playerid] != -1)
	{
	    CarryingOre[playerid] = -1;
	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	}
	if(IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_INDEX)) RemovePlayerAttachedObject(playerid, ATTACH_INDEX);
	return 1;
}

Player_GetClosestVein(playerid, Float: range = 3.0)
{
	new id = -1, Float: dist = range, Float: tempdist, Float: pos[3];
	for(new i; i < MAX_VEINS; i++)
	{
	    if(!VeinData[i][VeinExists]) continue;
	    GetDynamicObjectPos(VeinData[i][VeinObject], pos[0], pos[1], pos[2]);
	    tempdist = GetPlayerDistanceFromPoint(playerid, pos[0], pos[1], pos[2]);
	    if(tempdist > range) continue;
		if(tempdist <= dist)
		{
			dist = tempdist;
			id = i;
		}
	}
	return id;
}

Player_GetClosestOre(playerid, Float: range = 3.0)
{
	new id = -1, Float: dist = range, Float: tempdist, Float: pos[3];
	for(new i; i < MAX_ORES; i++)
	{
	    if(!DroppedOres[i][OreExists]) continue;
	    GetDynamicObjectPos(DroppedOres[i][OreObject], pos[0], pos[1], pos[2]);
	    tempdist = GetPlayerDistanceFromPoint(playerid, pos[0], pos[1], pos[2]);
	    if(tempdist > range) continue;
		if(tempdist <= dist)
		{
			dist = tempdist;
			id = i;
		}
	}
	return id;
}

CALLBACK: Ore_Destroy(id)
{
	KillTimer(DroppedOres[id][OreTimer]);
	DestroyDynamicObject(DroppedOres[id][OreObject]);
	DestroyDynamic3DTextLabel(DroppedOres[id][OreLabel]);
	DroppedOres[id][OreExists] = false;

	return 1;
}

stock Vein_Regenerate()
{
	new Float: spawn_coords[][3] = {
    	{2713.2390,-1521.0090,1407.1035},
		{2708.6111,-1523.2028,1406.3407},
		{2710.4429,-1526.8110,1405.9806},
		{2713.0420,-1530.0448,1405.7485},
		{2714.9426,-1535.7014,1404.9961},
		{2711.5249,-1538.5266,1404.3505},
		{2708.8027,-1540.8801,1403.7446},
		{2705.5056,-1543.3655,1403.0648},
		{2704.4011,-1547.3834,1402.3660},
		{2707.0718,-1551.0443,1402.0692},
		{2714.2703,-1549.1642,1402.4281},
		{2717.7588,-1549.3385,1402.3949},
		{2719.9619,-1546.3038,1402.9738},
		{2705.8557,-1550.9757,1401.9724},
		{2703.3118,-1551.1017,1401.7129},
		{2702.9656,-1549.3824,1401.9343},
		{2702.8521,-1547.1532,1402.2533},
		{2702.5779,-1541.4160,1403.0757},
		{2702.1345,-1536.0027,1403.8344},
		{2701.6321,-1530.8209,1404.5531},
		{2698.9658,-1524.8395,1405.1851},
		{2695.9878,-1527.4705,1404.5139},
		{2691.1821,-1532.6552,1403.2920},
		{2688.1897,-1536.4728,1402.4440},
		{2683.8835,-1537.8529,1402.2617},
		{2681.5984,-1544.1699,1401.7987},
		{2678.0681,-1546.2535,1401.6460},
		{2672.1626,-1542.2178,1401.9418},
		{2669.3801,-1535.6577,1402.4224},
		{2666.2996,-1529.3048,1402.8679},
		{2662.9260,-1526.5881,1402.5684},
		{2659.4954,-1529.4756,1402.2849},
		{2653.9238,-1535.6791,1401.8302},
		{2648.5615,-1536.5435,1401.3734},
		{2643.5359,-1532.9724,1400.9290},
		{2642.4084,-1526.0519,1400.9495},
		{2640.7488,-1522.0944,1400.9656},
		{2641.1128,-1517.8917,1401.0172},
		{2641.5732,-1513.1461,1402.3065},
		{2643.0833,-1509.0205,1403.8866},
		{2640.7966,-1508.6284,1403.7914},
		{2641.3372,-1504.7448,1405.1898},
		{2643.2097,-1499.9010,1407.2710},
		{2637.8083,-1496.3179,1410.5887},
		{2632.6802,-1497.3242,1411.0773},
		{2625.4321,-1498.0255,1406.0192},
		{2621.1897,-1498.9922,1405.5901},
		{2616.2988,-1500.1451,1405.0845},
		{2612.2412,-1498.2246,1405.4919},
		{2608.5852,-1502.8778,1404.0243},
		{2606.3569,-1507.3616,1402.6560},
		{2602.5667,-1510.1139,1401.7299},
		{2603.3728,-1515.1812,1401.4122},
		{2601.5767,-1520.2463,1401.3451},
		{2598.2837,-1522.9854,1401.3303},
		{2595.8591,-1523.5116,1401.3441},
		{2592.2651,-1521.8153,1401.4148},
		{2589.9958,-1517.6595,1401.4835},
		{2587.2000,-1512.0563,1401.2329},
		{2585.2024,-1508.0920,1400.2756},
		{2584.4160,-1504.6104,1401.7544},
		{2580.0784,-1502.2086,1401.7593},
		{2577.7378,-1501.0507,1401.6846},
		{2576.6846,-1497.8915,1403.1311},
		{2574.7285,-1493.3201,1405.0907},
		{2576.4683,-1489.2421,1408.2861},
		{2579.0981,-1487.2334,1410.8018},
		{2582.3655,-1485.5592,1413.1030},
		{2587.1416,-1485.8523,1413.7180},
		{2590.4556,-1485.1384,1415.0647},
		{2576.3979,-1526.1185,1401.3435},
		{2574.8281,-1526.4927,1401.3374},
		{2570.5828,-1527.3075,1400.8358},
		{2567.7661,-1524.4454,1399.9141},
		{2565.0889,-1521.0660,1398.9346}
	};

	foreach (new i : Player)
	{
	    if (!IsPlayerConnected(i)) 
			continue;

        Player_CleanUp(i);
	}

	// Destroy Old Veins
	for(new i; i < MAX_VEINS; i++)
	{
		if (!VeinData[i][VeinExists]) 
			continue;

		DestroyDynamicObject(VeinData[i][VeinObject]);
		DestroyDynamic3DTextLabel(VeinData[i][VeinLabel]);
		VeinData[i][VeinExists] = false;
	}

	// Respawn
    new type;
	for(new i; i < sizeof(spawn_coords); i++) {

	    if (i >= MAX_VEINS) 
			break;
	    
		type = random(MAX_ORE_TYPES);
	    
		VeinData[i][Type] = type;
	    VeinData[i][AmountOres] = OreData[type][AmountOres];
	    
		VeinData[i][VeinObject] = CreateDynamicObject(867, spawn_coords[i][0], spawn_coords[i][1], spawn_coords[i][2]-0.65, 0.0, 0.0, random(360));
  		SetDynamicObjectMaterial(VeinData[i][VeinObject], 0, 2936, "kmb_rckx", "larock256", RGBAToARGB(OreData[type][Color]));
  		VeinData[i][VeinLabel] = CreateDynamic3DTextLabel("Label", OreData[type][Color], spawn_coords[i][0], spawn_coords[i][1], spawn_coords[i][2] + 0.5, 5.0, .testlos = 1);
	    VeinData[i][VeinExists] = true;

	    Vein_Update(i);
	}
}

task Vein_Generate[REGEN_TIME*60000]()
{
    Vein_Regenerate();
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (newkeys & KEY_CTRL_BACK)
	{
	    if (CarryingOre[playerid] != -1)
		{
			new id = Ore_FindFreeID();
			if(id != -1) {
			    if (Player_GetClosestOre(playerid, 1.5) != -1) 
					return SendClientMessage(playerid, -1, "Você não pode deixar seu minério aqui.");

			    new 
					label[128], 
					type = CarryingOre[playerid], Float: x, Float: y, Float: z, Float: a
				;

			    GetPlayerPos(playerid, x, y, z);
			    GetPlayerFacingAngle(playerid, a);

			    x += (1.25 * floatsin(-a, degrees));
				y += (1.25 * floatcos(-a, degrees));

			    DroppedOres[id][Type] = type;
				DroppedOres[id][OreTimer] = SetTimerEx("Ore_Destroy", ORE_TIME * 60000, false, "i", id);
			    DroppedOres[id][OreObject] = CreateDynamicObject(3929, x, y, z - 0.65, 0.0, 0.0, random(360));
		  		SetDynamicObjectMaterial(DroppedOres[id][OreObject], 0, 2936, "kmb_rckx", "larock256", RGBAToARGB(OreData[type][Color]));
				format(label, sizeof(label), "Minério - %s\n"C_WHITE"Pressione {%s}/pegarminerio "C_WHITE"para coletá-lo", OreData[type][NameOres], OreData[type][ColorStr]);
		  		DroppedOres[id][OreLabel] = CreateDynamic3DTextLabel(label, OreData[type][Color], x, y, z, 5.0, .testlos = 1);
			    DroppedOres[id][OreExists] = true;
			}
		    ApplyAnimation(playerid, "CARRY", "putdwn05", 4.1, false, true, true, false, 0, SYNC_ALL);
			Player_CleanUp(playerid, 1);
		}
	}
	else if (newkeys & KEY_WALK)
	{
		if (Player_GetClosestVein(playerid) != -1)
			callcmd::minerar(playerid);
	}
	else if (newkeys & KEY_YES)
	{
		if (PlayerToPoint(2.0, playerid, 990.2281, -78.3008, 21.6394))
			callcmd::venderminerio(playerid);
	}
    return 1;
}

hook OnGameModeInit()
{
    CreateDynamicPickup(3014, 23, 990.2281,-78.3008,21.6394);	// Vender Minérios
    CreateDynamicPickup(1318, 23, 995.5361,-73.5942,22.0867);	// Entrada Mina
    CreateDynamic3DTextLabel("Venda de Minérios\nPressione {AFAFAF}Y {FFFFFF}para vender", 0xFFFFFFFF,990.2281,-78.3008,21.6394,10.5);
    CreateDynamic3DTextLabel("Entrada da Mina\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para acessar a mina", 0xFFFFFFFF,995.5361,-73.5942,22.0867,10.5);

    CreateMap_Minerador();

	Vein_Regenerate();
    return 1;
}