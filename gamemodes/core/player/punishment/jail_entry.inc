// Defines
#define         _JAIL_ENTRY_X               1797.4390           // Posição X da entrada da prisão
#define         _JAIL_ENTRY_Y               -1578.9257          // Posição Y da entrada da prisão
#define         _JAIL_ENTRY_Z               14.0852             // Posição Z da entrada da prisão
#define         _JAIL_ENTRY_R               99.2950             // Posição reta virada para a porta
#define         _JAIL_RANGE_                2.0                 // Distância para entrar no interior da prisão

#define         _JAIL_NAME                  "prisão La Sante"   // Nome da prisão

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
    bool:jail_exploded = false,          // Prisão explodida
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
	    case 3:delegacia = "HQ Forças Armadas";
	    case 9:delegacia = "Cadeia Admin";
	    case 16:delegacia = "HQ SWAT";
	    case 11:delegacia = "HQ Policia Federal";
	    case 24:delegacia = "Prisao La Sante";
	    case 33:delegacia = "HQ Policia Civil";
	    default:delegacia = "Nenhuma";
	}
	return delegacia;
}