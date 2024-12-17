
/*  ----------------------------------------------------------------------------------------------------------------------------------------

        Sistema de organizações;
        Módulo de entrada;
        Definições, variáveis globais do sistema;

 ----------------------------------------------------------------------------------------------------------------------------------------- */


// Id das organizações;
#define         ID_ORG_GOVERNO          7
#define         ID_ORG_SANNEWS          9

/*enum {
    GOVERNO,
    EXERCITO,
    POLICIA_MILITAR,
    POLICIA_FEDERAL,
    POLICIA_CIVIL,
    POLICIA_RODOVIARIA,
    TELECOMUNICACAO
};*/

// Nome padrão do líder e máximo de organizações
#define     DEFAULT_NAME_NULL   "Ninguem"

// Máximo de slots e cargos na organização;
#define     MAX_SLOTS_ORGS      30
#define     MAX_CARGOS_ORG      20
#define		MAX_ROLE_NAME		35					// Máximo de caracteres no nome do cargo

// Slot reservado para líder
#define     SLOT_LIDER          0

// Definições do cargo líder, sub-lider;
#define 	LIDER 			    20
#define 	SUB_LIDER_1 	    19
#define 	SUB_LIDER_2 	    18

// IDs de orgs
#define             ID_ORG_GOVERNO          7


new Dialog_Select[MAX_PLAYERS][MAX_SLOTS_ORGS];

// Tipo da organização;
enum OrgType {
    TYPE_COP,
    TYPE_GANG,
    TYPE_MAFIA,
    TYPE_ASSASSINS,
    TYPE_MERCENARY,
    TYPE_TERROR,
}

// Membros;
enum orgmembros {
    MemberID,
    MemberName[MAX_PLAYER_NAME+1],
    MemberLogin[55],
};
new OrgMembros[MAX_ORGS][MAX_SLOTS_ORGS][orgmembros];

// Cargos;
enum orgperms {
    CargoName[MAX_ROLE_NAME],
};
new OrgPermissions[MAX_ORGS][MAX_CARGOS_ORG + 1][orgperms];

// Carros da organização;
new CarrosORG[MAX_ORGS][35];

// Caros de organizações;
new CarrosLixeiros[10],
	CarrosPilotos[3];
new CarrosMedicos[7];
new CarrosMecanicos[6];
new CarrosFazendeiros[16];

new bool:roubouOrg[MAX_ORGS] = {false,...};


stock CountCops() {
	new count;

	foreach(new i : Player)
		if (IsACop(i)) count++;

	return count;
}

stock countMembrosOn(orgid)
{
	new count;

	foreach(new i : Player)
		if (GetPlayerOrg(i) == orgid)
            count++;

	return count;
}

enum CofreInfo
{
	orgVIP,
	org_vip_date[30],
	DiaLider,
	orgDinheiro,
	Materiais,
	Maconha,
	Cocaina,
	Crack,
	dMaconha,
	cMaconha,
	cMateriais,
	mMateriais,
	mMaconha,
	salarioc1,
	salarioc2,
	salarioc3,
	salarioc4,
	salarioc5,
	salariolider,
	InvasaoOrg,
	InvasaoTempo,
	TrainingOrg,
	TrainingTime
};
new CofreOrg[MAX_ORGS][CofreInfo];
new pCofreOrg[MAX_PLAYERS];

stock GetMembrosPerto(playerid)
{
	new count = 0;

	new Float: pos[3];

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	foreach(new player : Player)
	{
		if (GetPlayerOrg(playerid) == GetPlayerOrg(player) && IsPlayerInRangeOfPoint(player, 10.0, pos[0], pos[1], pos[2]))
			count++;
	}
	return count;
}