// Minerador
#define     MAX_ORE_TYPES   (6)
#define     MAX_VEINS       (128)
#define     MAX_ORES        (256)
#define     UPDATE_RATE     (4000)		// taxa de atualização de mineração em milissegundos, maior o valor mais longo do tempo de mineração (padrão: 200)
#define     BAR_MAX         (15.0)		// valor máximo da barra de progresso, maior o valor mais longo do tempo de extração (padrão: 15,0)
#define     ATTACH_INDEX    (9)			// setplayerattachedobject index
#define     REGEN_TIME    	(60)        // quantos minutos antes das minerios de respawning (padrão: 45)
#define     ORE_TIME        (10)         // quantos minutos antes de destruir uma queda ou (padrão: 5)

enum e_ores
{
	NameOres[16],
	Color,
	ColorStr[8],
	Float: Modifier,
	AmountOres, // quantos desse minério geram um minerio
	ValueOres, // valor desse minério
	Rate // taxa de mineração bem sucedida
}

enum e_veins
{
	Type,
	AmountOres,
	bool: BeingMined,
	VeinObject,
	Text3D: VeinLabel,
	bool: VeinExists
}

enum e_dialogs
{
    DIALOG_ORE_INFO = 18740,
    DIALOG_ORE_TAKE
}

enum e_droppedores
{
	Type,
	OreTimer,
	OreObject,
	Text3D: OreLabel,
	bool: OreExists
}

new
	OreData[MAX_ORE_TYPES][e_ores] = 
	{
	    {"Cobre", 0xB87333FF, "887333", 0.75, 8, 35000, 55},
	    {"Ametista", 0x9B59B6FF, "9B59B6", 0.60, 6, 42500, 50},
	    {"Esmeralda", 0x2ECC71FF, "2ECC71", 0.40, 4, 50500, 46},
		{"Rubi", 0xD10056FF, "D10056", 0.35, 3, 65000, 40},
		{"Safira", 0x0F52BAFF, "0F52BA", 0.30, 3, 75000, 36},
        {"Ouro", 0xFFD700FF, "FFD700", 0.25, 2, 90000, 30}
	};

new
	VeinData[MAX_VEINS][e_veins],
	DroppedOres[MAX_ORES][e_droppedores],
	MiningVein[MAX_PLAYERS] = {-1, ...},
	Timer:MiningTimer[MAX_PLAYERS],
	CarryingOre[MAX_PLAYERS] = {-1, ...}
;

stock Float: Vein_CalculateTime(id)
	return (BAR_MAX / OreData[ VeinData[id][Type] ][Modifier]) * UPDATE_RATE;