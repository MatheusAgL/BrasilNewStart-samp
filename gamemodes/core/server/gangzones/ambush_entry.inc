#define WAR_AREA_SIZE     		  300.0
#define WAR_KILL_POINTS   		  1500
#define WAR_DEATH_POINTS  		  1000
#define WAR_AIRDROP_POINTS  	  7500
#define WAR_VEHICLE_DEATH_POINTS  500
#define WAR_DISCONNECT_POINTS  	  400

enum ENUM_AMBUSH {
	ambushValid,
	Float:ambushPosX,
	Float:ambushPosY,
	ambushMoney,
	ambushColor,
	ambushGZ,
	ambushArea,
	ambushOrgPoints[MAX_ORGS],
	ambushOrgKills[MAX_ORGS],
	ambushOrgDeaths[MAX_ORGS],
	Text:ambushText[3],
	PlayerText:ambushPText[3],
	ambushTimerCreate,
	ambushTimer,
};
static AmbushInfo[MAX_ORGS][ENUM_AMBUSH];

stock Ambush_GetCreated(org) 
	return AmbushInfo[org][ambushValid];