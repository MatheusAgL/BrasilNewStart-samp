// Defines
#define         _JAIL_ENTRY_X               1797.4390           // Posi��o X da entrada da pris�o
#define         _JAIL_ENTRY_Y               -1578.9257          // Posi��o Y da entrada da pris�o
#define         _JAIL_ENTRY_Z               14.0852             // Posi��o Z da entrada da pris�o
#define         _JAIL_ENTRY_R               99.2950             // Posi��o reta virada para a porta
#define         _JAIL_RANGE_                2.0                 // Dist�ncia para entrar no interior da pris�o

#define         _JAIL_NAME                  "pris�o La Sante"   // Nome da pris�o

#define         TIME_EXPLOSION_JAIL         40                  // Tempo para explodir (em segundos)

#define         MODEL_MAP_ICON_LASANTE      30                  // Modelo do icone do mapa

#define GATES_CLOSED  	0
#define GATES_CLOSING  	1
#define GATES_OPEN    	2
#define GATES_OPENING   3

new Text3D:LabelGates[2], PortaoLaSante[4];
new PortaoEsquerdaLS = GATES_CLOSED;
new PortaoDireitaLS = GATES_CLOSED;

enum JAIL_enum
{
    bool:jail_exploded = false,          // Pris�o explodida
    Timer:server_exploding_jail[MAX_PLAYERS],
    object_explosao,
};
new JailInfo[JAIL_enum];

stock GetDelegaciaName(playerid)
{
	new delegacia[35];
	switch(Player_GetJailed(playerid))
	{
	    case 1:delegacia = "HQ Policia Militar";
	    case 2:delegacia = "HQ BOPE Los Santos";
	    case 3:delegacia = "HQ For�as Armadas";
	    case 9:delegacia = "Cadeia Admin";
	    case 16:delegacia = "HQ SWAT";
	    case 11:delegacia = "HQ Policia Federal";
	    case 24:delegacia = "Prisao La Sante";
	    case 33:delegacia = "HQ Policia Civil";
	    default:delegacia = "Nenhuma";
	}
	return delegacia;
}