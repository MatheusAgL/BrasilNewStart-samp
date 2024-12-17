#include <YSI_Coding\y_hooks>

// ---------------------
// Municipais:

#include <map_garages_ls>				// Garagens em LS
#include <map_cityhall_plaza>			// City Hall Plaza (Praça da prefeitura)
#include <map_hospital_ls>				// Mapa: Hospital de LS
#include <map_morro>					// Morro (Guerra do Morro)
#include <map_jail>						// Cadeia (La Sante)
#include <map_church>					// Igreja

// ---------------------
// HQs

// Governamentais
#include <hq_san_news>					// HQ da San News
#include <hq_prf>						// HQ da PRF

// Facções
#include <map_favela_1>					// Favela 1 | FDN (Familia do Norte)
#include <map_favela_2>					// Favela 2 | PCC (Primeiro Comando da Capital)
#include <map_favela_3>					// Favela 3 | CV (Comando Vermelho)
#include <map_favela_4>					// Favela 4 | GROTA

// ---------------------
// Empregos

#include <hq_taxista>					// HQ dos Taxistas
#include <hq_caminhoneiro>				// HQ dos Caminhoneiros

// ---------------------
// Propriedades

#include <map_market>					// Mercado 24/7
#include <map_ammunation>				// Ammunation
#include <map_bank_ls>					// Banco de LS

// ---------------------
// Residencias
#include <map_house_1>

// ---------------------
// Extras
#include <map_enforce>					// Interior do Enforce

// -----------------------------------------------------------
// Diversos:

#include <map_mansion_radio>
#include <map_x1>
#include <map_buildings>
#include <map_bank>
#include <map_park>
#include <map_ganton_park>
#include <map_agency>
#include <map_lsfd>
#include <map_new_prison>
#include <map_faveladay>

#include <map_placa_spawn>

#if SERVER_ARRAIA
	#include <map_arraia_spawn>
	#include <map_arraiapraia>
#endif

// -----------------------------------------------------------

// All:
#include <map_main>

hook OnPlayerConnect(playerid) 
{
	CallLocalFunction("OnRemoveBuilding", "i", playerid);
	
	RemoveBuildingsOfServer(playerid);
	RemoveBuilding_MapBuildings(playerid);
	
	RemoveBuilding_CityHall_Plaza(playerid);
	RemoveBuilding_BankLS(playerid);
	RemoveBuilding_Hospital_LS(playerid);

	RemoveBuilding_MapGantonPark(playerid);
	RemoveBuilding_MapAgency(playerid);
	RemoveBuilding_MapLSFD(playerid);
	RemoveBuilding_MapFavela1(playerid);
    return 1;
}

hook OnGameModeInit()
{
	CreateMap_Main();

	Create3DTextsLabelsOfServer();

	CreateMap_CityHall_Plaza();
	CreateMap_BankLS();
	CreateMap_Hospital_LS();
	
	// CreateMap_BikesBar();

	// Mapas
	#if defined _MAP_LOGIN_SCREEN
		CreateMap_LoginScreen();
	#endif

	#if defined _JAIL_SYSTEM_ON
		CreateMap_PrisaoLaSante();
	#endif

	#if defined _SAN_NEWS_SYSTEM_ON
		CreateMap_SanNews();
	#endif

	#if defined _HQ_PRF_SYSTEM_ON
		CreateMap_HQ_PRF();
	#endif

	/*#if defined _HQ_TAXISTA_SYSTEM_ON
		CreateMap_HQ_Taxista();
	#endif*/

	#if defined _HQ_CAMINHONEIRO_SYSTEM_ON
		CreateMap_HQ_Caminhoneiro();
	#endif

	#if _INTERIOR_ENFORCE_ON
		CreateMap_InteriorEnforce();
	#endif

	#if defined _MANSAO_RADIO_SYSTEM_ON
		CreateMap_Mansao_Radio();
	#endif

	#if defined _MAPA_POLICIA_SYSTEM_ON
		CreateMap_Policia();
	#endif

	#if defined _MAPA_LOJA247_SYSTEM_ON
		CreateMap_Loja247();
	#endif

	CreateMap_Favela_1();
	CreateMap_Favela_2();
	CreateMap_Favela_3();
	CreateMap_Favela_4();

	#if defined _MAPA_NATAL_SYSTEM_ON
		CreateMap_Natal();
	#endif

	#if defined _MAPA_IGREJA_SYSTEM_ON
		CreateMap_Igreja();
	#endif

	#if defined _MAPA_X1_SYSTEM_ON
		CreateMap_X1();
	#endif

	// CreateMap_Escritorio();

	CreateMap_Ammunations();

	CreateMap_Buildings();
	
	CreateMap_GantonPark();

	CreateMap_Agency();

	CreateMap_LSFD();

	CreateMap_NewPrison();

	CreateMap_Favela_Day();

    return 1;
}