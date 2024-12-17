/* --------------------------------------------------------------------------------------------------------

         ____                _ _   _   _                  _____ _             _   
		|  _ \              (_) | | \ | |                / ____| |           | |  
		| |_) |_ __ __ _ ___ _| | |  \| | _____      __ | (___ | |_ __ _ _ __| |_ 
		|  _ <| '__/ _` / __| | | | . ` |/ _ \ \ /\ / /  \___ \| __/ _` | '__| __|
		| |_) | | | (_| \__ \ | | | |\  |  __/\ V  V /   ____) | || (_| | |  | |_ 
		|____/|_|  \__,_|___/_|_| |_| \_|\___| \_/\_/   |_____/ \__\__,_|_|   \__|
																				
																				
	----------------------------------------------------------------------------------------------------
	- Desenvolvedor(es): 		
						/ Theus_Crazzy
						/ iHollyZinhO
						/ Joao_Revolts

	- Contribuidor(es):
	- (Pelo desenvolvimento de plugins e includes avançada)
						/ Y-Less
						/ Southclaws
						/ pBlueG
						/ oscar-broman
						/ samp-incognito
						/ tdworg
						/ ltkarim


- 			Copyright of Start Group. All rights reserved.
-			Comunidade desenvolvida e planejada por Matheus de Aguiar Luz (107.840.039-39) - Tel: (43) 99828-5615

-------------------------------------------------------------------------------------------------------- */

// #define OPENMP_COMPAT
#include <a_samp>

#if !defined _INC_open_mp
	#define	TEXT_DRAW_FONT_0						0
	#define	TEXT_DRAW_FONT_1						1
	#define	TEXT_DRAW_FONT_2						2
	#define	TEXT_DRAW_FONT_3						3

	#define TEXT_DRAW_ALIGN_LEFT					1
	#define TEXT_DRAW_ALIGN_CENTRE					2
	#define TEXT_DRAW_ALIGN_CENTER					2
	#define TEXT_DRAW_ALIGN_RIGHT					3

	#define SYNC_NONE                              	0 // Don't force sync to anyone else.
	#define SYNC_ALL                               	1 // Sync to all streamed-in players.
	#define SYNC_OTHER                             	2 // Sync to all streamed-in players, except the player with the animation.

	#define VEHICLE_TYRE_STATUS_NONE               	0

	#define UNKNOWN_CP_TYPE                        -1
	#define CP_TYPE_GROUND_NORMAL                   0
	#define CP_TYPE_GROUND_FINISH                   1
	#define CP_TYPE_GROUND_EMPTY                    2
	#define CP_TYPE_AIR_NORMAL                      3
	#define CP_TYPE_AIR_FINISH                      4
	#define CP_TYPE_AIR_ROTATING                    5
	#define CP_TYPE_AIR_STROBING                    6
	#define CP_TYPE_AIR_SWINGING                    7
	#define CP_TYPE_AIR_BOBBING                     8
	// #define			TEXT_DRAW_FONT_
	// #define			TEXT_DRAW_FONT_

#endif

#include <crashdetect>					// Crashdetect
// PrintAmxBacktrace();
#include <fixes>
#include <profiler>

// ---------------------------------------------------------------------------
// Definições das bibliotecas YSI
// Essa biblioteca é o maior problema de conflitos dentro da GM
// Deve-se estudar todas as atualizações dela antes de atualizar.
// Use dependências por HASH no caso, pawn-lang/YSI-Include#8120312u8d9f87 < hashcode.

// Malloc
#define YSI_NO_HEAP_MALLOC

// Não exibe a mensagem sobre o cache do código (com `YSI_YES_MODE_CACHE`). 
#define YSI_NO_CACHE_MESSAGE

// Não verifique se esta é a versão mais recente do YSI. 
#define YSI_NO_VERSION_CHECK

#define CGEN_MEMORY 76000

#include <YSI_Coding\y_inline>
#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>
#include <YSI_Visual\y_dialog>
#include <YSI_Players\y_android>

// Erro conhecido por nome muito longo de callback;
// Biblioteca YSI:
DEFINE_HOOK_REPLACEMENT(OnPlayer, OP_);
DEFINE_HOOK_REPLACEMENT(OnUnoccupied, OU_);

/* ------------------------------------------------------------------------
	Includes em geral:
---------------------------------------------------------------------------*/
// RakNet
#include <Pawn.RakNet>				// Plugin de memória avançado (Precisamos reativa-lo)

IRawPacket:20(playerid, BitStream:bs) // 20 = ID_RPC
{
    new PacketID, RPC_ID, NumberOfBitsOfData;
    BS_ReadValue(bs, PR_UINT8, PacketID, PR_UINT8, RPC_ID, PR_CUINT32, NumberOfBitsOfData);
    printf("IRawPacket -> ID_RPC: playerid: %d, RPC_ID: %d, NumberOfBitsOfData: %d", playerid, RPC_ID, NumberOfBitsOfData);

    if (PacketID == 40 || (NumberOfBitsOfData >= 0x1FFFFF || NumberOfBitsOfData <= 0x80000000 || NumberOfBitsOfData < 0))
    {
        printf("Fix crasher - RPCID: %d, NumberOfBitsOfData: %d", RPC_ID, NumberOfBitsOfData);
        BanEx(playerid, "Intento de crashear el server");
        return false;
    }

    return true;
}

// RAK_DEBUG - habilita o log de cada acionamento de proteção, exibe um log detalhado com os dados enviados pelo player (habilitado por padrão).
// RAK_MAX_QUAT_WARNINGS - o número de avisos que um jogador receberá por um ângulo de personagem inválido antes de ser expulso do servidor.
// RAK_ENABLED_SHOT - ativa proteção contra disparos inválidos
// #define RAK_DEBUG true
// #include <rakcheat>
// #include <SKY>

#include <Pawn.CMD>						// Processador de comandos da GameMode

#define SSCANF_NO_NICE_FEATURES
#include <sscanf2>						// Include responsável pela facilitação na construção de comandos e funções
#include <strlib>						// Biblioteca de strings

#include <chrono>						// Data e hora

#include <streamer>						// Include responsável pela limitação de objetos, veículos, atores, etc...

#include <td-string-width>				// Corrigindo textdraw com string grande

#include <mapandreas>					// Plugin que identifica colisão no mapa do GTA:SA
#include <map-zones>					// Endereço dos bairros do GTA:SA

#include <corrections>					// Fix SA-MP Bugs

// #include <nex-ac>						// Anti-cheater

#include <weapon-config>				// Include responsável pela configuração de dano (dependencia adaptada)
#include <textdraw-streamer>
#include <progress2>					// Biblioteca de criação de barras de progresso

#include <mSelection>					// Menu de seleção (OBSOLETO // Necessita trocar/refazer/otimizar)
#include <lselection>					// Menu de seleção (OBSOLETO // Necessita trocar/refazer/otimizar)

// --------------------------------------------------------------------------------------------------------------------------
#include <defines>						// Definições principais
#include <mysql_config>					// Conectando o MySQL
#include <global_vars>					// Variáveis globais
#include <logs>							// Sistema de logs do servidor
#include <date_config>					// Formatação de data
#include <player_config>				// Configurações de players
#include <Anti_cheat_pack>				// Anti-cheater
#include <discord>						// API do Discord
#include <utils>						// Utils
#include <version_config>				// Versão
#include <object_remap>					// Remap de Objetos
#include <actors>						// Atores UP
#include <map_icons>					// Map Icons

// Create maps
#include <maps_create>
#include <inventory_entry>				// Inventário

#include <loading_map>					// Carregar o mapa
#include <samp-modern-menu>

// --------------------------------------------------------------------------------------------------------------------------
#include <hud_config>					// Configuração da HUD
#include <economy_config>				// Configuração da economia do jogo

#include <conquests>					// Conquistas
#include <vehicle>						// Veículos
#include <paintball>
#include <player>						// Jogador

#include <skins>
#include <events>
#include <cupom>
#include <arms_job>
#include <government>
#include <commerces>
#include <samp-tabclick-menu>
#include <email>
#include <dump-entry>
#include <portoes>
#include <panel>
#include <dealers>
#include <Fader>
#include <mailer>
#include <mentions>
#include <radio_portatil>
#include <modulo_menu>
#include <sprays>
#include <radares>
#include <elevators>
#include <modulo_dropbox>
#include <cartao_Debito>
#include <beneficios_vip>
#include <core>
#include <gunbox>

#include <auto_escola>

#include <radio>                    // Sitema de rádio
#include <props>                    // Sistema de propriedades
#include <gps>                      // Sistema de GPS
#include <territories>              // Sistema de territórios
#include <medkit>                   // Sistema de MedKit
#include <mine>						// Sistema de Mina terrestre
#include <trade>					// Sistema de negociação

#include <server>
#include <mobile-editor>

// #include <anti-cheater>				// Configurações do anti-cheater

// API integrada (configurável)
// Pode ser interpretado como se fosse um Middleware.
// Aqui é um repositório criado para desenvolvimento de programadores iniciantes.
// Separando os processos e tentando agilizar o processo de desenvolvimento.
#include <integrate>

// --------------------------------------------------------------------------------------------------------------------------
main() { 
	printf("Servidor iniciado no IP: %s:%s... [%s]", SERVER_IP, SERVER_PORTA, GetCurrentDateHour(ONLY_CURRENT_ALL));

	if (GetCurrentMonth() != MES_ACESSED_GAMEMODE) {
		print("=============================== [ERROR]:");
		print("[ERROR]: Winned GameMode! The content is locked and the server has been turned off.");
		print("===============================");
		SendRconCommand("exit");
	}
}

public OnGameModeInit()
{
	#if _inc_version_control
		VersionControl_LoadList();
	#endif

	// Configurando o servidor ao ligar
 	SendRconCommand("weburl "SERVER_DISCORD"");                                 // Definindo site oficial do servidor no 'SAMP-Client'

	// Definindo uma rcon aleatória toda vez que o servidor ligar
	// Usando o comando /viewrcon para ver a senha.
	// Apenas os nicks disponíveis na lista de desenvolvedores poderão usar a rcon
	static random_password[20];
	format(random_password, sizeof(random_password), Rcon_GetRandPass());

	Rcon_SetPassword(random_password); // Definindo sua rcon password (OBS: Raramente usará RCON nesta GameMode)
	
	// ------------------------------------------------------------------------------------------------------------------------
	SendRconCommand("language "SERVER_LANGUAGE"");                              // Definindo a linguagem do servidor

	Server_CheckStatus();

	// Os veículos não explodem sem ninguém dentro
	SetVehiclePassengerDamage(true);

	// Os veículos explodem sem ninguém dentro
	SetVehicleUnoccupiedDamage(true);

	// Bugs de munição infinita e outros bugs (sub -bugs ainda funcionam)
    SetDisableSyncBugs(true);

	// Desabilitando stunt da GameMode
	EnableStuntBonusForAll(false);

	// Aparecer players no mapa (desativado)
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);

	// Distância para ver o nick do jogador
	SetNameTagDrawDistance(25.0);

	// Desabilitar interiores padrão do GTA:SA
	DisableInteriorEnterExits();

    // Definindo oque será usado do plugin 'MapAndreas'
    MapAndreas_Init(MAP_ANDREAS_MODE_FULL);

	// Criar os objetos da GameMode
	CallLocalFunction("OnCreateObject", "");
	CallLocalFunction("OnCreateTextDraws", "");
	CreateTD_Discord();
	CreateTD_Inventory();

	CreateTextDraws_PlayerDrugInfo();

	Logger_ToggleDebug("commands", true);

    ElevatorBoostTimer = -1;
	ResetElevatorQueue();
	Elevator_Initialize();
	ResetElevatorQueue_B();
	Elevator_Initialize_B();

	Evento = 0;
	TimerHay = -1;

	NoobDesativado = 0;
	gmxAutomatico = 1;
	eventoAleatorio = 0;

	TimeGranaTR = 2 * 60;

    LoadStuff();
    resetarAtividadesOrg();
    resetarGuerrasPd();

    LoadTerritories();
    Family_LoadAll();
    loadLixeiras();
    loadSlotsPatio();
	UsePlayerPedAnims();
    carregarPortoes();
    createRadars();
    ResetCombate();
	Panel_LoadAll();

	AddPlayerClass(23, 1274.6816, -1668.3425, 19.7344, 177.000, WEAPON:0, -1, WEAPON:0, -1, WEAPON:0, -1);

    for (new i = 0; i < MAX_PLAYERS; i++)
        g_LastAdminMoneyPickup[i] = 0;

// ----------------------------------------------------------------- GangZone's -----------------------------------------------------------------
	GZMorro[0] = GangZoneCreate(1969, -1099.5, 2162, -902.5);
	GZMorro[1] = GangZoneCreate(2162, -1133.5, 2407, -921.5);
	GZMorro[2] = GangZoneCreate(2407, -1133.5, 2640, -921.5);
	
	CreateServerHQZones();

	AreaCofre = CreateDynamicCube(2162.3433, 1632.6841, 830.0000, 2133.8994, 1613.3777, 840.0000);      		// Áreas do cofre

	/*---------------------------------------------------------------------------
								CPs (Checkpoints)								*/

	CPsLanchonetes[0] = CreateDynamicCP(379.5276,-119.0465,1001.4922, 1.0, 10011);
	CPsLanchonetes[1] = CreateDynamicCP(379.5276,-119.0465,1001.4922, 1.0, 10027);
	CPsLanchonetes[2] = CreateDynamicCP(379.5276,-119.0465,1001.4922, 1.0, 10030);
	CPsLanchonetes[3] = CreateDynamicCP(379.5276,-119.0465,1001.4922, 1.0, 10038);
	CPsLanchonetes[4] = CreateDynamicCP(379.5276,-119.0465,1001.4922, 1.0, 10051);
	CPsLanchonetes[5] = CreateDynamicCP(379.5276,-119.0465,1001.4922, 1.0, 10060);

	CPsLanchonetes[6] = CreateDynamicCP(372.1015,-6.8959,1001.8589, 1.0, 10003);
	CPsLanchonetes[7] = CreateDynamicCP(372.1015,-6.8959,1001.8589, 1.0, 10004);
	CPsLanchonetes[8] = CreateDynamicCP(372.1015,-6.8959,1001.8589, 1.0, 10025);
	CPsLanchonetes[9] = CreateDynamicCP(372.1015,-6.8959,1001.8589, 1.0, 10026);
	CPsLanchonetes[10] = CreateDynamicCP(372.1015,-6.8959,1001.8589, 1.0, 10028);
	CPsLanchonetes[11] = CreateDynamicCP(372.1015,-6.8959,1001.8589, 1.0, 10029);
	CPsLanchonetes[12] = CreateDynamicCP(372.1015,-6.8959,1001.8589, 1.0, 10032);
	CPsLanchonetes[13] = CreateDynamicCP(372.1015,-6.8959,1001.8589, 1.0, 10041);
	CPsLanchonetes[14] = CreateDynamicCP(372.1015,-6.8959,1001.8589, 1.0, 10054);


	CPsLanchonetes[15] = CreateDynamicCP(378.4466,-68.3325,1001.5151, 1.0, 10002);
	CPsLanchonetes[16] = CreateDynamicCP(378.4466,-68.3325,1001.5151, 1.0, 10012);
	CPsLanchonetes[17] = CreateDynamicCP(378.4466,-68.3325,1001.5151, 1.0, 10031);
	CPsLanchonetes[18] = CreateDynamicCP(378.4466,-68.3325,1001.5151, 1.0, 10036);
	CPsLanchonetes[19] = CreateDynamicCP(378.4466,-68.3325,1001.5151, 1.0, 10037);

	CPsBar[0] = CreateDynamicCP(494.7997,-75.7400,998.7578, 1.0);
	CPsBar[1] = CreateDynamicCP(499.8263,-18.8046,1000.6719, 1.0);
	CPsBar[2] = CreateDynamicCP(-224.7805,1404.9996,27.7734, 1.0);
	CPsBar[3] = CreateDynamicCP(1215.4504,-13.3534,1000.9219, 1.0);
	CPsBar[4] = CreateDynamicCP(670.3397,-419.5163,671.5453, 1.0);

	/*---------------------------------------------------------------------------
									Pickups										*/

	// Orgs
	CreateDynamicPickup(1318, 23, -201.4692, -1092.9031, 25.2115); 		// HQ Familia do Norte
	CreateDynamicPickup(1318, 23, 919.4673, -1252.2612, 16.2109) ; 		// Policia Rodoviaria - Entrada (Estrelinha)

	CreateDynamicPickup(1318, 23, 475.6070, -1501.5156, 20.5379);		// Interior Máfia Cosa Nostra
	CreateDynamicPickup(1318, 23, 222.9435, 118.2206, 1010.2188) ; 		// Policia Rodoviaria - Saida (Interior)
    CreateDynamicPickup(1239, 23, 221.4195, 114.2523, 1010.2188, 1000); // Policia Rodoviaria - /verificar placa (Cidade pequena)

	CreateDynamicPickup(1318, 23, -26.8819,-89.6936,1003.5469) ; 		// 24/7 - Comprar item
	CreateDynamicPickup(1318, 23, 1394.1488,-24.8331,1000.9177) ; 		// 24/7 - Comprar item
	CreateDynamicPickup(1318, 23, -22.2540,-55.6456,1003.5469) ; 		// 24/7 - Comprar item
	CreateDynamicPickup(1318, 23, -22.3265,-138.4765,1003.5469) ; 		// 24/7 - Comprar item
	CreateDynamicPickup(1318, 23, -30.3140,-28.3121,1003.5573) ; 		// 24/7 - Comprar item

	// Joao_Revolts
	CreateDynamicPickup(1318, 23, 2233.0254,-1159.8149,25.8906); 		// Motel - Entrada
	CreateDynamicPickup(1240, 23, 2217.3367,-1146.8258,1025.7969); 		// Pickup - Sexo Motel

	CreateDynamicPickup(1318, 23, 238.6457, 139.2875, 1003.0234, -1) ; 	// Interior BOPE (Saida)
	CreateDynamicPickup(1247, 23, 2270.9304, -105.9503, 26.4766, -1) ; 	// HQ PRF (Exterior)
	CreateDynamicPickup(1239, 23, 1397.6309,-1789.9438,13.5469) ;
	CreateDynamicPickup(1239, 23, 2037.8967,-1760.7670,13.5469) ;
	CreateDynamicPickup(1239, 23, 1908.3629,-1452.5341,13.5469) ;
	CreateDynamicPickup(1239, 23, 1247.4297,-1409.1392,13.0103) ;
	CreateDynamicPickup(1239, 23, 1218.0498,-1391.9077,13.2801) ;
	CreateDynamicPickup(1239, 23, 219.1412,110.7154,1010.2118, 16) ; // verificar placa - dentro da hq
	CreateDynamicPickup(1239, 23, 224.3456,109.2041,1010.2188, 16) ; // verificar patio - dentro da hq
	CreateDynamicPickup(1242, 23, 226.2034,121.5204,1010.2188, 16) ; // equipar P.R.F  - dentro da hq
	CreateDynamicPickup(1318, 23, 1397.7185,-1797.1010,13.5469);
	CreateDynamicPickup(1318, 23, 2030.7540,-1760.8278,13.5469);
	CreateDynamicPickup(1318, 23, 1915.6649,-1452.4265,13.5469);
	CreateDynamicPickup(1318, 23, 1240.2002,-1409.2941,13.0107);
	CreateDynamicPickup(1318, 23, 1225.1102,-1391.8157,13.2337);
	CreateDynamicPickup(1318,23,1130.1991, -1733.0205, 13.8090); // /ajustar hospital
    CreateDynamicPickup(1241, 24, -2655.0955,639.4547,14.4531);// Hospital San Fierro Entrada
	CreateDynamicPickup(1318,23,690.7985,-1275.9355,13.5602) ; // entrada yakuza
	CreateDynamicPickup(1318,23,289.8943, -1373.6874, 14.8122) ; // entrada Italiana
	CreateDynamicPickup(1318,23,-594.6794,-1057.1132,23.3562) ; // hq Estado Islamico
	CreateDynamicPickup(1318,23,2770.6521,-1628.1273,12.1775) ; // hq triad
	CreateDynamicPickup(1318,23,-100.3403,-24.6412,1000.7188) ; // sex shop saida
	CreateDynamicPickup(1318, 23,253.9271,69.5726,1003.6406,-1); // P-S
	CreateDynamicPickup(1318,23, 1524.4977, -1677.9469, 6.2188); // Elevador PM
	CreateDynamicPickup(1318,23, 1565.1235, -1666.9944, 28.3956); // Elevador PM
	CreateDynamicPickup(1318,23, 246.4990, 88.0087, 1003.6406); // Elevador Cop
	CreateDynamicPickup(1650, 23, 1941.6409,-1764.9487,13.6406);//galao de gasolina
	pickDoacao = CreateDynamicPickup(1239, 23, 359.0061,178.5880,1008.3828); // Doação Governo
	CreateDynamicPickup(1318,23, 649.3264,-1353.8356,13.5470) ; // hq San News
	CreateDynamicPickup(1314, 23, 671.9144,-1271.4734,13.6250); //Cofre ORG
	CreateDynamicPickup(1314, 23, 294.0777,-1372.6936,14.0260); //Cofre ORG
	CreateDynamicPickup(1314, 23, 1568.6442,-1689.9729,6.2188); //Cofre ORG
    CreateDynamicPickup(1314, 23, 324.0125,-1518.6938,36.0325); //Cofre ORG 2
    CreateDynamicPickup(1314, 23, -55.8733, -300.6442, 5.4297); //Cofre ORG 34
    CreateDynamicPickup(1314, 23, -1341.9978,496.3586,11.1953); //Cofre ORG
    CreateDynamicPickup(1314, 23, 1690.1144,-2098.9558,13.8343); //Cofre ORG
   	CreateDynamicPickup(1314, 23, 1779.5671, -1781.6948, 13.5320); //Cofre ORG: 29
   	CreateDynamicPickup(1314, 23, 1688.1190,-1351.0415,17.4297); //Cofre ORG
    CreateDynamicPickup(1314, 23, 2281.0020,-2368.7363,13.5469); //Cofre ORG
    CreateDynamicPickup(1314, 23, 750.9255,-1359.1901,13.5000); //Cofre ORG
    CreateDynamicPickup(1314, 23, 1130.3765,-2043.4714,69.0078); //Cofre ORG P.F
    CreateDynamicPickup(1314, 23, 2593.9116, -1500.9254, 16.0808); //Cofre ORG
    CreateDynamicPickup(1314, 23, -599.1168,-1065.9753,23.4103); //Cofre ORG Estado Islamico
    CreateDynamicPickup(1314, 23, -198.4513, -1087.4451, 24.6806); //Cofre ORG Familia do Norte
	CreateDynamicPickup(1314, 23, 1596.2747, -733.9089, 65.3713); // Cofre ORG - C.V
    CreateDynamicPickup(1314, 23, 2825.3916,-1170.2870,25.2235); //Cofre ORG
    CreateDynamicPickup(1314, 23, 1028.7534,-1106.7701,23.8281); //Cofre ORG
    CreateDynamicPickup(1314, 23, 1329.1952, -3008.4778, 8.3392); //Cofre ORG
    CreateDynamicPickup(1314, 23, 2788.4028,-1627.9689,10.9272); //Cofre ORG
	CreateDynamicPickup(1314, 23, 358.7956,186.6793,1008.3828); //Cofre ORG
	CreateDynamicPickup(1314, 23, 479.5926,-1531.1252,19.8107); //Cofre ORG
	CreateDynamicPickup(1314, 23, 687.2863,-472.8064,16.5363); //Cofre ORG
	CreateDynamicPickup(1314, 23, 2477.7251,89.5832,26.7737); //Cofre ORG
	CreateDynamicPickup(1314, 23, 219.2626,108.5960,1010.2118, 16); //Cofre ORG - PRF
	CreateDynamicPickup(1314, 23, -308.2417,1538.4569,75.5625); //Cofre ORG
	CreateDynamicPickup(1318, 23, 338.2485,-1501.9403,36.0391);			// Elevador BOPE (subir)
	CreateDynamicPickup(1318, 23, 347.8569,-1494.7401,76.5391); 		// Elevador BOPE (descer)
	CreateDynamicPickup(1318,23, 1650.6134, -1351.0118, 17.4295);		// Elevador Policia Civil (subir)
	CreateDynamicPickup(1318,23, 1672.1484, -1334.3336, 158.4766);		// Elevador Policia Civil (descer)
	CreateDynamicPickup(1318, 23, 2473.2554,-1531.0217,24.1455);			// Elevador Familia do Norte (subir)
	CreateDynamicPickup(1318, 23, 2463.8401,-1538.7161,32.5703); 		// Elevador Familia do Norte (descer)
	CreateDynamicPickup(1318, 23, 390.4640, 173.8098,1008.3828,-1) ; // Saida  Governo
	CreateDynamicPickup(1318, 23, 967.2544,2175.1235,10.8203) ; // entrada HQ P.C.C
 	CreateDynamicPickup(1318, 23, 2281.2393,-2364.8765,13.5469);//entrada hq hitmans
	CreateDynamicPickup(1318, 23, 1684.8771,-2098.8760,13.8343) ; // entrada HQ Amigo dos Amigos
	CreateDynamicPickup(1318, 23, 2808.3562,-1176.4606,25.3687); //HQ BAIRRO-13
	CreateDynamicPickup(1318, 23, -2385.7024,2215.9673,4.9844) ; // entrada HQ Staff
	CreateDynamicPickup(1242, 23, 1530.3060,-1702.4915,6.2252,-1); //BaterCartao
	CreateDynamicPickup(1242, 23, 240.6516,112.8062,1003.2188,-1); //BaterCartao
	CreateDynamicPickup(1242, 23, 1585.4412,-1692.0966,-21.0029,-1); //BaterCartao
	CreateDynamicPickup(1242, 23, -1346.8774,491.9250,11.2027,-1); //Batercartao COP
    CreateDynamicPickup(1242, 23, 359.1856,211.4973,1008.3828,-1); //BaterCartao
	CreateDynamicPickup(1242, 23, 255.1123,77.4241,1003.6406,-1); //BaterCartao
	CreateDynamicPickup(1242, 23, 230.3021,165.0272,1003.0234,-1); //BaterCartao
	CreateDynamicPickup(1242, 23, 211.2608,185.8552,1003.0313,-1); //Equipar COP
    CreateDynamicPickup(1318,23,277.1725,1943.1394,1062.0856, 99); // Advogado Prisão La Sante
	CreateDynamicPickup(1318,23,2261.2698,-1135.8125,1050.6328,-1); // aki15
	CreateDynamicPickup(1318,23,315.4988,-142.3861,999.6016,-1); // loja de armas SF2
	CreateDynamicPickup(1318,23,369.6563,165.0458,1053.2078,-1); // SAIDA HOSPITAL
	CreateDynamicPickup(1318,23,501.8770,-67.7092,998.7578,-1); // HQ Warlocks - saida
	CreateDynamicPickup(1318,23,-329.7025,1536.6123,76.6117,-1); // HQ Al-Qaeda
	CreateDynamicPickup(1318,23,316.3902,-169.8001,999.6010,-1); //
	CreateDynamicPickup(1318,23,260.8594,1238.0526,1084.2578,-1); //
	CreateDynamicPickup(1318,23,2485.6860,89.4010,26.7737,-1); // HQ Sons Of Anarchy
	CreateDynamicPickup(1318,23,681.6184,-474.1958,16.5363,-1); // HQ Warlocks
	CreateDynamicPickup(1277, 23, -2033.3137,-117.4329,1035.1719,-1); //licencas
	CreateDynamicPickup(1318, 23, 1478.7834,-1783.3513,13.5400); //pref LS
	CreateDynamicPickup(371, 23, 1536.0, -1360.0, 1150.0); //LS towertop
	CreateDynamicPickup(1318, 23,234.8461,111.1823,1003.2257);// /limpar
	CreateDynamicPickup(1318, 23,1325.5382, -3031.5596, 8.5836);//hq P.C.C
	CreateDynamicPickup(1247, 23, 1553.3007,-1675.7654,16.1953);//DP PM
	CreateDynamicPickup(1247, 23, 1684.5236,- 1343.3313, 17.4368);//DP Policia Civil
	CreateDynamicPickup(1247, 23, 1800.0864,-1578.3821,14.0739);//Prisao La Sante - Entrada
	CreateDynamicPickup(1247, 23, 275.4004,1949.8926,1062.0856, 99);//Prisao La Sante - Saida

	//Igrejas
	CreateDynamicPickup(1318, 23, 2233.1575,-1333.2433,23.9816);//Igreja de Jefferson
	CreateDynamicPickup(1318, 23, 1720.2667,-1740.5646,13.5469);//Igreja de Little México

// Entrada de eventos
	CreateDynamicPickup(1318, 23, 1769.5328,-1863.3152,13.5752);
	CreateDynamic3DTextLabel("{00FFFF}Eventos de admin\n{FFFFFF}Use o comando {00FFFF}/entrarevento {FFFFFF}para entrar",0xFFFFFFFF,1769.5328,-1863.3152,13.5752, 25.0);

	CreateDynamic3DTextLabel("{FFFFFF}Área de Prisão\n{FFFFFF}Use o comando {FF7766}/prender {FFFFFF}para prender", 0xFFFFFFFF, 1545.4073,-1607.9791,13.3828, 11.0);
	CreateDynamicPickup(11749, 23, 1545.4073,-1607.9791,13.3828);//DP Prender

	CreateDynamic3DTextLabel("{FFFFFF}Área de Prisão\n{FFFFFF}Use o comando {FF7766}/prender {FFFFFF}para prender", 0xFFFFFFFF, 354.1136,-1506.8484,32.9804, 11.0);
	CreateDynamicPickup(11749, 23, 354.1136,-1506.8484,32.9804);//DP Prender BOPE

	CreateDynamic3DTextLabel("{FFFFFF}Área de Prisão\n{FFFFFF}Use o comando {FF7766}/prender {FFFFFF}para prender", 0xFFFFFFFF, 1706.9711,-1332.8363,13.5469, 11.0);
	CreateDynamicPickup(11749, 23, 1706.9711,-1332.8363,13.5469);    // HQ da Policia Civil

	CreateDynamic3DTextLabel("{FFFFFF}Área de Prisão\n{FFFFFF}Use o comando {FF7766}/prender {FFFFFF}para prender", 0xFFFFFFFF, 1754.9194,-1564.7217,10.0820, 11.0);
	CreateDynamicPickup(11749, 23, 1754.9194,-1564.7217,10.0820);//DP Prender
	CreateDynamic3DTextLabel("{FFFFFF}Área de Prisão\n{FFFFFF}Use o comando {FF7766}/prender {FFFFFF}para prender", 0xFFFFFFFF, -82.5581,-363.3431,1.4297, 11.0);
	CreateDynamicPickup(11749, 23, -82.5581,-363.3431,1.4297);//DP Prender
	CreateDynamic3DTextLabel("{FFFFFF}Área de Prisão\n{FFFFFF}Use o comando {FF7766}/prender {FFFFFF}para prender", 0xFFFFFFFF, 1284.7302,-2048.9648,58.9519, 11.0);
	CreateDynamicPickup(11749, 23, 1284.7302,-2048.9648,58.9519);		//	DP Policia Federal (prender)
	CreateDynamicPickup(1247, 23, -1741.0514,961.7468,24.8828);//-1741.0514,961.7468,24.8828); // PC GARAGEM PRENDER
	CreateDynamicPickup(1318, 23, 1570.3828,-1333.8882,16.4844); // Building next AB
	CreateDynamicPickup(1318, 23, 2590.2910, -1494.0944, 16.8114); // Grove HQ
   	CreateDynamicPickup(1247, 23, -1298.8188,490.5014,11.1953) ; // PRENDER Forças Armadas
   	CreateDynamicPickup(1247, 23, 1124.7544,-2036.9777,69.8833) ; // Interior Policia Federal
   	LFicha = CreateDynamicPickup(1318, 23, 198.9671,168.1982,1003.0234,-1) ; // Limpar PC
	CreateDynamicPickup(1318, 23, 253.9280,69.6094,1003.6406) ;// Limpar armas
   	CreateDynamicPickup(1314, 23, 768.2192,-3.9873,1000.7203); // mudarluta
	CreateDynamicPickup(1247, 23, 195.5733,158.4008,1003.0234); //prender novo
	// CreateDynamicPickup(1241, 24, 1175.8210,-1325.9398,-44.2836);// Hospital Saida
    CreateDynamicPickup(1247, 23, 328.1634,-1512.4167,36.0325);		//	DP BOPE
    CreateDynamicPickup(1247, 23, -50.0843, -298.3511, 5.4297);		//	DP CORE
	
	CreateDynamic3DTextLabel("{FFFFFF}Olá {00FFFF}jogador{FFFFFF}, seja bem-vindo ao {FFFF00}"SERVER_NAME"!\n{FFFFFF}Use o comando {FF7766}/atendimento {FFFFFF}se caso precisar de ajuda ou informações", 0xFFFFFFFF, 1676.5328,-2263.4382,13.5360, 10.0); // NPC Respawn Civil - Staff
	CreateDynamic3DTextLabel("{FFFFFF}Olá {00FFFF}jogador{FFFFFF}, seja bem-vindo ao {FFFF00}"SERVER_NAME"!\n{FFFFFF}Use o comando {FF7766}/atendimento {FFFFFF}se caso precisar de ajuda ou informações", 0xFFFFFFFF, 1689.3104,-2263.4380,13.4783, 10.0); // NPC Respawn Civil - Staff

//Portões
	PDDOORa 			= CreateDynamicObject(985 , 247.005905 , 72.448440 , 1003.640625 , 0.000000 , 0.000000 , 1260.000000 );
	PDDOORb 			= CreateDynamicObject(985 , 250.774871 , 60.822799 , 1003.640625 , 0.000000 , 0.000000 , 5130.000000 );
	PDDOORc 			= CreateDynamicObject(986 , 248.142105 , 78.125961 , 1003.640625 , 0.000000 , 0.000000 , 12690.000000 );
	PDPMLS 				= CreateDynamicObject(980, 1546.8681640625, -1627.3585205078, 15.156204223633, 0, 0, 90);
	PortaoReporter[0] 	= CreateDynamicObject(980, 778.11206, -1384.84778, 13.94793,   0.00000, 0.00000, 179.73135);
	PortaoReporter[1]	= CreateDynamicObject(980, 777.45294, -1330.08032, 13.69681,   0.00000, 0.00000, 357.97565);
	pYak1 				= CreateDynamicObject(980, 664.8619,-1307.4937,15.3109,0.0000,0.0000,0.0000);
	pYak2 				= CreateDynamicObject(980, 660.7543,-1227.8146,17.4440,0.0000,0.0000,-118.2998);
	pYak3 				= CreateDynamicObject(980, 783.9084,-1152.4266,25.4053,0.0000,0.0000,-90.2999);
    PortaoCN 			= CreateDynamicObject(980, 493.8057,-1547.1104,19.8590,0.0000,0.0000,210.6994);
	portaoDetran1	  	= CreateDynamicObject(985, 2271.17578, -122.50561, 27.07960,   0.00000, 0.00000, 90.65700);
	portaoDetran2  		= CreateDynamicObject(985, 2270.97070, -113.03745, 27.13612,   0.00000, 0.00000, 90.65700);
	PortaoGN       	    = CreateDynamicObject(980, -1527.77454, 482.17676, 8.99428,   0.00000, 0.00000, -1.02000);
	PortaoMayans   		= CreateDynamicObject(2933,702.0000000,-475.1000100,17.1000000,0.0000000,0.0000000,0.0000000);
	portaoRussa         = CreateDynamicObject(980, 222.95401, -1434.97827, 14.91388,   0.00000, 0.00000, 223.62000);
	portaoPC		  	= CreateDynamicObject(980, 1622.12415, -1322.47363, 19.18700,   0.00000, 0.00000, 90.00000);
	portaoPC2	  		= CreateDynamicObject(980, 1658.79480, -1365.14771, 19.18700,   0.00000, 0.00000, -90.00000);
	PortaoBPEV	 	    = CreateDynamicObject(980, -79.86600, -352.73331, 3.21830,   0.00000, 0.00000, 90.00000);
	PortaoBOPE          = CreateDynamicObject(980, 283.38159, -1542.82373, 25.92710,   0.00000, 0.00000, -35.00000); // Portão 1 - Nova HQ BOPE
	PortaoBOPE2			= CreateDynamicObject(980, 321.12421, -1488.35999, 25.92710,   0.00000, 0.00000, 145.00000); // Portão 2 - Nova HQ BOPE

	// Lixeiros
	CarrosLixeiros[0] = AddStaticVehicleEx(408, 2193.7795, -2029.8522, 14.0571, 314.0179,26, 26, -1);
	CarrosLixeiros[1] = AddStaticVehicleEx(408, 2190.1143, -1984.6404, 14.0571, 90.1422,26, 26, -1);
	CarrosLixeiros[2] = AddStaticVehicleEx(408, 2190.1606, -1988.9692, 14.0571, 90.1422,26, 26, -1);
	CarrosLixeiros[3] = AddStaticVehicleEx(408, 2190.2095, -1993.5096, 14.0571, 90.1422,26, 26, -1);
	CarrosLixeiros[4] = AddStaticVehicleEx(408, 2190.2544, -1997.6758, 14.0571, 90.1422,26, 26, -1);
	CarrosLixeiros[5] = AddStaticVehicleEx(408, 2177.3159, -2013.9741, 14.0571, 314.0179,26, 26, -1);
	CarrosLixeiros[6] = AddStaticVehicleEx(408, 2180.4705, -2017.0167, 14.0571, 314.0179,26, 26, -1);
	CarrosLixeiros[7] = AddStaticVehicleEx(408, 2183.7063, -2020.1375, 14.0571, 314.0179,26, 26, -1);
	CarrosLixeiros[8] = AddStaticVehicleEx(408, 2186.9429, -2023.2589, 14.0571, 314.0179,26, 26, -1);
	CarrosLixeiros[9] = AddStaticVehicleEx(408, 2190.2605, -2026.4584, 14.0571, 314.0179,26, 26, -1);

	// Pilotos
	CarrosPilotos[0] = AddStaticVehicleEx(519, 2137.8911, -2469.1851, 14.4655, 89.9216, 26, 26, -1);
	CarrosPilotos[1] = AddStaticVehicleEx(519, 2138.6765, -2447.2051, 14.4655, 87.7437, 26, 26, -1);
	CarrosPilotos[2] = AddStaticVehicleEx(519, 2139.5754, -2424.2461, 14.4656, 88.6762, 26, 26, -1);

	// Médicos
	CarrosMedicos[0] = AddStaticVehicleEx(416, 1140.2944, -1757.0580, 13.9202, 272.1776, 1, 1, -1); 	// Ambulancia 1
	CarrosMedicos[1] = AddStaticVehicleEx(416, 1140.2654, -1752.5856, 13.9199, 270.9952, 1, 1, -1); 	// Ambulancia 2
	CarrosMedicos[2] = AddStaticVehicleEx(416, 1140.2218, -1748.4182, 13.9198, 270.3728, 1, 1, -1); 	// Ambulancia 3
	CarrosMedicos[3] = AddStaticVehicleEx(416, 1144.5291, -1729.1790, 13.9689, 183.5474, 1, 1, -1); 	// Ambulancia 4
	CarrosMedicos[4] = AddStaticVehicleEx(416, 1149.2925, -1728.7373, 13.9754, 183.0479, 1, 1, -1); 	// Ambulancia 5
	CarrosMedicos[5] = AddStaticVehicleEx(416, 1153.7654, -1728.6666, 13.9749, 182.0512, 1, 1, -1); 	// Ambulancia 6
	CarrosMedicos[6] = AddStaticVehicleEx(416, 1158.4980, -1728.2567, 13.9871, 179.7441, 1, 1, -1); 	// Ambulancia 7

	// Mecânicos
	CarrosMecanicos[0] = AddStaticVehicleEx(525,2136.7910,-1727.9109,13.4174,182.4886,3,3,100); // guinc 1
	CarrosMecanicos[1] = AddStaticVehicleEx(525,2132.8440,-1728.1467,13.4188,182.0968,3,3,100); // guinc 2
	CarrosMecanicos[2] = AddStaticVehicleEx(525,2128.4348,-1728.2551,13.4294,181.8682,3,3,100); // guinc 3
	CarrosMecanicos[3] = AddStaticVehicleEx(525,2172.1008,-1733.1909,13.4211,270.2484,3,3,100); // guinc 4
	CarrosMecanicos[4] = AddStaticVehicleEx(525,2172.0615,-1728.9380,13.4157,271.0391,3,3,100); // guinc 5
	CarrosMecanicos[5] = AddStaticVehicleEx(525,2172.0222,-1725.0200,13.4226,270.7825,3,3,100); // guinc 6

	// Fazendeiros
	CarrosFazendeiros[0] = AddStaticVehicleEx(478,-107.0430,12.6038,3.1191,70.9481,123,123,6);   // Carro Fazendeiro [Pesquisa]
    CarrosFazendeiros[1] = AddStaticVehicleEx(478,-105.1281,17.8855,3.1000,70.9492,123,123,6);   // Carro Fazendeiro [Pesquisa]
    CarrosFazendeiros[2] = AddStaticVehicleEx(478,-103.1489,23.3120,3.1192,71.1000,123,123,6);   // Carro Fazendeiro [Pesquisa]
    CarrosFazendeiros[3] = AddStaticVehicleEx(531,-106.4615,-48.2775,3.0999,73.8993,123,123,6);  // Carro Fazendeiro [Plantação]
    CarrosFazendeiros[4] = AddStaticVehicleEx(531,-109.6858,-44.5170,3.1011,70.3967,123,123,6);  // Carro Fazendeiro [Plantação]
    CarrosFazendeiros[5] = AddStaticVehicleEx(531,-110.1615,-42.1847,3.1011,72.1567,123,123,6);  // Carro Fazendeiro [Plantação]
    CarrosFazendeiros[6] = AddStaticVehicleEx(531,-109.5083,-40.1579,3.1028,72.0105,123,123,6);  // Carro Fazendeiro [Plantação]
    CarrosFazendeiros[7] = AddStaticVehicleEx(531,-108.7549,-37.8649,3.0917,71.9367,123,123,6);  // Carro Fazendeiro [Plantação]
    CarrosFazendeiros[8] = AddStaticVehicleEx(531,-108.1526,-35.9845,3.0975,72.0179,123,123,6);  // Carro Fazendeiro [Plantação]
    CarrosFazendeiros[9] = AddStaticVehicleEx(531,-107.3281,-33.4457,3.0977,72.0096,123,123,6);  // Carro Fazendeiro [Plantação]
    CarrosFazendeiros[10] = AddStaticVehicleEx(532,-144.0908,-26.4986,4.1102,68.7238,123,123,6); // Carro Fazendeiro [Colheita]
    CarrosFazendeiros[11] = AddStaticVehicleEx(532,-148.3079,-37.3457,4.1081,68.7711,123,123,6); // Carro Fazendeiro [Colheita]
    CarrosFazendeiros[12] = AddStaticVehicleEx(532,-152.9258,-49.1944,4.1067,68.2280,123,123,6); // Carro Fazendeiro [Colheita]
    CarrosFazendeiros[13] = AddStaticVehicleEx(532,-157.4057,-60.6977,4.1071,68.8048,123,123,6); // Carro Fazendeiro [Colheita]
    CarrosFazendeiros[14] = AddStaticVehicleEx(532,-162.0294,-72.1085,4.1069,68.5032,123,123,6); // Carro Fazendeiro [Colheita]
    CarrosFazendeiros[15] = AddStaticVehicleEx(532,-166.1365,-82.9459,4.1071,69.3229,123,123,6); // Carro Fazendeiro [Colheita]

	for(new caminhoes_lixo; caminhoes_lixo != 10; caminhoes_lixo++) {
	    createCaminhaoLixo(CarrosLixeiros[caminhoes_lixo]);
	}

	static const ORGS_ID[] = {1, 2, 3, 5, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 25, 28, 33, 34}; // Função para determinar veículos de organização

	for(new i = 0; i < sizeof(ORGS_ID); i++) {
		new orgid = ORGS_ID[i];
		for(new j = 0; j < 35; j++) {
			new vehicleid = CarrosORG[orgid][j];
			if(vehicleid == 0)
				break;

			VehicleInfo[vehicleid][vhType] = VH_TYPE_ORG;
			VehicleInfo[vehicleid][vhInfoID] = orgid;
			VehicleInfo[vehicleid][vhArrested] = 0;
		}
	}

//-------------- Textdraws da corrida --------------------
	raceBox = TextDrawCreate(634.000000, 48.000000+30.0, "_");
	TextDrawBackgroundColor(raceBox, 255);
	TextDrawFont(raceBox, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(raceBox, 0.500000, 17.900007);
	TextDrawColor(raceBox, -1);
	TextDrawSetOutline(raceBox, 0);
	TextDrawSetProportional(raceBox, true);
	TextDrawSetShadow(raceBox, 1);
	TextDrawUseBox(raceBox, true);
	TextDrawBoxColor(raceBox, 60);
	TextDrawTextSize(raceBox, 490.000000, 0.000000);
	TextDrawSetSelectable(raceBox, false);

	raceRisco = TextDrawCreate(483.000000, 101.000000+30.0, "-");
	TextDrawBackgroundColor(raceRisco, 255);
	TextDrawFont(raceRisco, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(raceRisco, 10.800004, 0.699999);
	TextDrawColor(raceRisco, -1);
	TextDrawSetOutline(raceRisco, 0);
	TextDrawSetProportional(raceRisco, true);
	TextDrawSetShadow(raceRisco, 1);
	TextDrawSetSelectable(raceRisco, false);

	raceTempo = TextDrawCreate(499.000000, 84.000000+30.0, "Tempo: --:--");
	TextDrawBackgroundColor(raceTempo, 0);
	TextDrawFont(raceTempo, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(raceTempo, 0.449999, 1.700000);
	TextDrawColor(raceTempo, -1);
	TextDrawSetOutline(raceTempo, 1);
	TextDrawSetProportional(raceTempo, true);
	TextDrawSetSelectable(raceTempo, false);

	racePos[1] = TextDrawCreate(501.000000, 111.000000+30.0, "N/A");
	TextDrawBackgroundColor(racePos[1], 0);
	TextDrawFont(racePos[1], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(racePos[1], 0.190000, 1.100000);
	TextDrawColor(racePos[1], -1);
	TextDrawSetOutline(racePos[1], 1);
	TextDrawSetProportional(racePos[1], true);
	TextDrawUseBox(racePos[1], true);
	TextDrawBoxColor(racePos[1], 336860210);
	TextDrawTextSize(racePos[1], 621.000000, 0.000000);
	TextDrawSetSelectable(racePos[1], false);

	racePos[2] = TextDrawCreate(501.000000, 129.000000+30.0, "N/A");
	TextDrawBackgroundColor(racePos[2], 0);
	TextDrawFont(racePos[2], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(racePos[2], 0.190000, 1.100000);
	TextDrawColor(racePos[2], -1);
	TextDrawSetOutline(racePos[2], 1);
	TextDrawSetProportional(racePos[2], true);
	TextDrawUseBox(racePos[2], true);
	TextDrawBoxColor(racePos[2], 336860210);
	TextDrawTextSize(racePos[2], 621.000000, 0.000000);
	TextDrawSetSelectable(racePos[2], false);

	racePos[3] = TextDrawCreate(501.000000, 146.000000+30.0, "N/A");
	TextDrawBackgroundColor(racePos[3], 0);
	TextDrawFont(racePos[3], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(racePos[3], 0.190000, 1.100000);
	TextDrawColor(racePos[3], -1);
	TextDrawSetOutline(racePos[3], 1);
	TextDrawSetProportional(racePos[3], true);
	TextDrawUseBox(racePos[3], true);
	TextDrawBoxColor(racePos[3], 336860210);
	TextDrawTextSize(racePos[3], 621.000000, 0.000000);
	TextDrawSetSelectable(racePos[3], false);

	racePos[4] = TextDrawCreate(501.000000, 163.000000+30.0, "N/A");
	TextDrawBackgroundColor(racePos[4], 0);
	TextDrawFont(racePos[4], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(racePos[4], 0.190000, 1.100000);
	TextDrawColor(racePos[4], -1);
	TextDrawSetOutline(racePos[4], 1);
	TextDrawSetProportional(racePos[4], true);
	TextDrawUseBox(racePos[4], true);
	TextDrawBoxColor(racePos[4], 50);
	TextDrawTextSize(racePos[4], 621.000000, 0.000000);
	TextDrawSetSelectable(racePos[4], false);

	racePos[5] = TextDrawCreate(501.000000, 181.000000+30.0, "N/A");
	TextDrawBackgroundColor(racePos[5], 0);
	TextDrawFont(racePos[5], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(racePos[5], 0.190000, 1.100000);
	TextDrawColor(racePos[5], -1);
	TextDrawSetOutline(racePos[5], 1);
	TextDrawSetProportional(racePos[5], true);
	TextDrawUseBox(racePos[5], true);
	TextDrawBoxColor(racePos[5], 50);
	TextDrawTextSize(racePos[5], 621.000000, 0.000000);
	TextDrawSetSelectable(racePos[5], false);

	racePos[6] = TextDrawCreate(501.000000, 199.000000+30.0, "N/A");
	TextDrawBackgroundColor(racePos[6], 0);
	TextDrawFont(racePos[6], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(racePos[6], 0.190000, 1.100000);
	TextDrawColor(racePos[6], -1);
	TextDrawSetOutline(racePos[6], 1);
	TextDrawSetProportional(racePos[6], true);
	TextDrawUseBox(racePos[6], true);
	TextDrawBoxColor(racePos[6], 50);
	TextDrawTextSize(racePos[6], 621.000000, 0.000000);
	TextDrawSetSelectable(racePos[6], false);

	raceTime[1] = TextDrawCreate(599.000000, 111.000000+30.0, "--:--");
	TextDrawBackgroundColor(raceTime[1], 0);
	TextDrawFont(raceTime[1], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(raceTime[1], 0.190000, 1.100000);
	TextDrawColor(raceTime[1], -65281);
	TextDrawSetOutline(raceTime[1], 1);
	TextDrawSetProportional(raceTime[1], true);
	TextDrawSetSelectable(raceTime[1], false);

	raceTime[2] = TextDrawCreate(599.000000, 128.000000+30.0, "--:--");
	TextDrawBackgroundColor(raceTime[2], 0);
	TextDrawFont(raceTime[2], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(raceTime[2], 0.190000, 1.100000);
	TextDrawColor(raceTime[2], -65281);
	TextDrawSetOutline(raceTime[2], 1);
	TextDrawSetProportional(raceTime[2], true);
	TextDrawSetSelectable(raceTime[2], false);

	raceTime[3] = TextDrawCreate(599.000000, 146.000000+30.0, "--:--");
	TextDrawBackgroundColor(raceTime[3], 0);
	TextDrawFont(raceTime[3], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(raceTime[3], 0.190000, 1.100000);
	TextDrawColor(raceTime[3], -65281);
	TextDrawSetOutline(raceTime[3], 1);
	TextDrawSetProportional(raceTime[3], true);
	TextDrawSetSelectable(raceTime[3], false);

	raceTime[4] = TextDrawCreate(599.000000, 162.000000+30.0, "--:--");
	TextDrawBackgroundColor(raceTime[4], 0);
	TextDrawFont(raceTime[4], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(raceTime[4], 0.190000, 1.100000);
	TextDrawColor(raceTime[4], -65281);
	TextDrawSetOutline(raceTime[4], 1);
	TextDrawSetProportional(raceTime[4], true);
	TextDrawSetSelectable(raceTime[4], false);

	raceTime[5] = TextDrawCreate(599.000000, 180.000000+30.0, "--:--");
	TextDrawBackgroundColor(raceTime[5], 0);
	TextDrawFont(raceTime[5], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(raceTime[5], 0.190000, 1.100000);
	TextDrawColor(raceTime[5], -65281);
	TextDrawSetOutline(raceTime[5], 1);
	TextDrawSetProportional(raceTime[5], true);
	TextDrawSetSelectable(raceTime[5], false);

	raceTime[6] = TextDrawCreate(599.000000, 198.000000+30.0, "--:--");
	TextDrawBackgroundColor(raceTime[6], 0);
	TextDrawFont(raceTime[6], TEXT_DRAW_FONT_2);
	TextDrawLetterSize(raceTime[6], 0.190000, 1.100000);
	TextDrawColor(raceTime[6], -65281);
	TextDrawSetOutline(raceTime[6], 1);
	TextDrawSetProportional(raceTime[6], true);
	TextDrawSetSelectable(raceTime[6], false);

	raceBoxPos = TextDrawCreate(630.000000, 52.000000+30.0, "_");
	TextDrawBackgroundColor(raceBoxPos, 255);
	TextDrawFont(raceBoxPos, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(raceBoxPos, 0.500000, 3.300000);
	TextDrawColor(raceBoxPos, -1);
	TextDrawSetOutline(raceBoxPos, 0);
	TextDrawSetProportional(raceBoxPos, true);
	TextDrawSetShadow(raceBoxPos, 1);
	TextDrawUseBox(raceBoxPos, true);
	TextDrawBoxColor(raceBoxPos, 150);
	TextDrawTextSize(raceBoxPos, 494.000000, 0.000000);
	TextDrawSetSelectable(raceBoxPos, false);

	raceTotalPlayers = TextDrawCreate(559.000000, 47.000000+30.0, "/0");
	TextDrawBackgroundColor(raceTotalPlayers, 0);
	TextDrawFont(raceTotalPlayers, TEXT_DRAW_FONT_2);
	TextDrawLetterSize(raceTotalPlayers, 0.810000, 3.800000);
	TextDrawColor(raceTotalPlayers, -1258320641);
	TextDrawSetOutline(raceTotalPlayers, 1);
	TextDrawSetProportional(raceTotalPlayers, true);
	TextDrawSetSelectable(raceTotalPlayers, false);

	raceCount = TextDrawCreate(286.000000, 149.000000+30.0, "_");
	TextDrawBackgroundColor(raceCount, 0);
	TextDrawFont(raceCount, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(raceCount, 1.130000, 4.200001);
	TextDrawColor(raceCount, -1258320641);
	TextDrawSetOutline(raceCount, 0);
	TextDrawSetProportional(raceCount, true);
	TextDrawSetShadow(raceCount, 1);
	TextDrawSetSelectable(raceCount, false);

	textPremio1 = TextDrawCreate(519.000000, 177.000000, "_");
	TextDrawBackgroundColor(textPremio1, 255);
	TextDrawFont(textPremio1, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textPremio1, 0.490000, 14.099991);
	TextDrawColor(textPremio1, -1);
	TextDrawSetOutline(textPremio1, 0);
	TextDrawSetProportional(textPremio1, true);
	TextDrawSetShadow(textPremio1, 1);
	TextDrawUseBox(textPremio1, true);
	TextDrawBoxColor(textPremio1, 180);
	TextDrawTextSize(textPremio1, 99.000000, 0.000000);
	TextDrawSetSelectable(textPremio1, false);

	textPremio2 = TextDrawCreate(504.000000, 196.000000, "_");
	TextDrawBackgroundColor(textPremio2, 255);
	TextDrawFont(textPremio2, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textPremio2, 0.500000, 4.799997);
	TextDrawColor(textPremio2, -1);
	TextDrawSetOutline(textPremio2, 0);
	TextDrawSetProportional(textPremio2, true);
	TextDrawSetShadow(textPremio2, 1);
	TextDrawUseBox(textPremio2, true);
	TextDrawBoxColor(textPremio2, 1684300900);
	TextDrawTextSize(textPremio2, 110.000000, 0.000000);
	TextDrawSetSelectable(textPremio2, false);

	textPremio3 = TextDrawCreate(504.000000, 252.000000, "_");
	TextDrawBackgroundColor(textPremio3, 255);
	TextDrawFont(textPremio3, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textPremio3, 0.500000, 4.799997);
	TextDrawColor(textPremio3, -1);
	TextDrawSetOutline(textPremio3, 0);
	TextDrawSetProportional(textPremio3, true);
	TextDrawSetShadow(textPremio3, 1);
	TextDrawUseBox(textPremio3, true);
	TextDrawBoxColor(textPremio3, 1684300900);
	TextDrawTextSize(textPremio3, 110.000000, 0.000000);
	TextDrawSetSelectable(textPremio3, false);

	textPremioMsg = TextDrawCreate(115.000000, 173.000000, "Premios que voce ganhou");
	TextDrawBackgroundColor(textPremioMsg, 0);
	TextDrawFont(textPremioMsg, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textPremioMsg, 0.419999, 1.799999);
	TextDrawColor(textPremioMsg, -1258320641);
	TextDrawSetOutline(textPremioMsg, 1);
	TextDrawSetProportional(textPremioMsg, true);
	TextDrawSetSelectable(textPremioMsg, false);

	// Aceitar morte
	textMorteAcc[0] = TextDrawCreate(-10.000000, -10.000000, "usebox");
	TextDrawBackgroundColor(textMorteAcc[0], 0);
	TextDrawFont(textMorteAcc[0], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textMorteAcc[0], 0.500000, 53.000000);
	TextDrawColor(textMorteAcc[0], 0);
	TextDrawSetOutline(textMorteAcc[0], 0);
	TextDrawSetProportional(textMorteAcc[0], true);
	TextDrawSetShadow(textMorteAcc[0], 1);
	TextDrawUseBox(textMorteAcc[0], true);
	TextDrawBoxColor(textMorteAcc[0], 505290360);
	TextDrawTextSize(textMorteAcc[0], 700.000000, 0.000000);
	TextDrawSetSelectable(textMorteAcc[0], false);

	textMorteAcc[1] = TextDrawCreate(260.000000, 302.000000, "ld_dual:white");
	TextDrawBackgroundColor(textMorteAcc[1], 255);
	TextDrawFont(textMorteAcc[1], TEXT_DRAW_FONT_SPRITE_DRAW);
	TextDrawLetterSize(textMorteAcc[1], 0.500000, 1.000000);
	TextDrawColor(textMorteAcc[1], 673720575);
	TextDrawSetOutline(textMorteAcc[1], 0);
	TextDrawSetProportional(textMorteAcc[1], true);
	TextDrawSetShadow(textMorteAcc[1], 1);
	TextDrawUseBox(textMorteAcc[1], true);
	TextDrawBoxColor(textMorteAcc[1], 255);
	TextDrawTextSize(textMorteAcc[1], 115.000000, 21.000000);
	TextDrawSetSelectable(textMorteAcc[1], false);

	textMorteAcc[2] = TextDrawCreate(261.000000, 303.000000, "ld_dual:white");
	TextDrawBackgroundColor(textMorteAcc[2], 255);
	TextDrawFont(textMorteAcc[2], TEXT_DRAW_FONT_SPRITE_DRAW);
	TextDrawLetterSize(textMorteAcc[2], 0.500000, 1.000000);
	TextDrawColor(textMorteAcc[2], 505290495);
	TextDrawSetOutline(textMorteAcc[2], 0);
	TextDrawSetProportional(textMorteAcc[2], true);
	TextDrawSetShadow(textMorteAcc[2], 1);
	TextDrawUseBox(textMorteAcc[2], true);
	TextDrawBoxColor(textMorteAcc[2], 255);
	TextDrawTextSize(textMorteAcc[2], 113.000000, 19.000000);
	TextDrawSetSelectable(textMorteAcc[2], true);

	textMorteAcc[3] = TextDrawCreate(317.000000, 307.000000, "Aceitar morte");
	TextDrawAlignment(textMorteAcc[3], TEXT_DRAW_ALIGN_CENTER);
	TextDrawBackgroundColor(textMorteAcc[3], 0);
	TextDrawFont(textMorteAcc[3], TEXT_DRAW_FONT_1);
	TextDrawLetterSize(textMorteAcc[3], 0.289999, 1.000000);
	TextDrawColor(textMorteAcc[3], -156);
	TextDrawSetOutline(textMorteAcc[3], 0);
	TextDrawSetProportional(textMorteAcc[3], true);
	TextDrawSetShadow(textMorteAcc[3], 1);
	TextDrawSetSelectable(textMorteAcc[3], false);

	//Conquista
	createBaseConquistas();

	// Guerra
	warCreateTextdraws();

	CreateServerTradeTextdraws();

	loadSpraysTags();

//---------------------------------------------------------------------------------
	printf(" ");
	printf("-------------------------------------------------------------------------------------------");
	printf(" ");

    printf(">	Concessionária\t: %d Carros", loadCarrosConce());
    printf(">	Comércios\t: %d Carregados", LoadProperties());
	printf(">	Itens de Loja\t: %d Carregados", CarregarLojaCash());
    printf(">	Senha Admin\t: %s", LoadSenhaAdmin());
	LoadSalarioOrg();
    printf(" ");
    printf("-------------------------------------------------------------------------------------------");

    LoadAllCannabis();

	for (new vehicle = 0; vehicle != MAX_VEHICLES; vehicle++)
	{
		StopVehicleEngine(vehicle);

	 	VehicleInfo[vehicle][vehicleCombustivel] = 100;

	    new str[74];
	    format(str, sizeof str, ""SERVER_TAG"-%04d", vehicle);
	   	SetVehicleNumberPlate(vehicle, str);

		SetVehicleToRespawn(vehicle);
	}
	return 1;
}

public OnGameModeExit()
{
	// Caso desligue sem GMX
	if (!Server_IsRestarting()) {
		SendClientMessageToAll(COLOR_SAMP, "Servidor desligado manualmente... Use /quit e entre novamente!");
		printf("Servidor desligado manualmente...");
	}
	// Caso for via GMX
	else stop timer_gmx;

	foreach (new i : Player)
	{
		// Pula para o próximo antes de ler o código se for NPC
	    if (!IsPlayerNPC(i)) 
			continue;

		// Desconectando todos os jogadores conectados!
		KickEx(i);
	}

	// Salvando as propriedades
	saveProps();

	// Salvando os territórios
	SaveTerritories();

	// Salvando as maconhas
    SaveAllCannabis();

	// Descarregando o plugin 'MapAndreas'.
	MapAndreas_Unload();

	// Destruindo elevador
	Elevator_Destroy();

	// Salvando dados (para trocar)
	SaveStuff();

	MySQL_DestroyConnection();

	return 1;
}

public OnPlayerConnect(playerid)
{
	if (Server_IsRestarting())
		KickEx(playerid);

	CallLocalFunction("OnLoadObjectsForPlayer", "i", playerid);

	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnIncomingConnection(playerid, ip_address[], port) 
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid) 
{
	if (Player_Logado(playerid))
		SpawnPlayer(playerid);

	return 1;
}

public OnPlayerText(playerid, text[])
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (!Player_Logado(playerid))
		return 1;

	return 0;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	if (!Player_Logado(playerid))
		return 0;

	return 1;
}

public OnClickDynamicPlayerTextDraw(playerid, PlayerText:textid)
{
   	if (!Player_Logado(playerid))
		return 0;

	return 1;
}

CALLBACK: OnCreateTextDraws()
{
	print("OnCreateTextDraws");
	return 1;
}

CALLBACK: OnCreatePlayerTextDraws()
{
	return 1;
}

CALLBACK: OnCreateObject()
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnDynamicObjectMoved(objectid) 
{
    return 1;
}

public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z) {

	if (!Player_Logado(playerid))
		return 0;

	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid) 
{
	if (!Player_Logado(playerid))
		return 0;

	return 1;
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{
	if (!Player_Logado(playerid))
		return 0;
		
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	if (!Player_Logado(playerid))
		return 0;

	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if (!Player_Logado(playerid))
		return 0;

	return 1;
}

public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if (!Player_Logado(playerid))
		return 0;

	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
    if (!Player_Logado(playerid))
		return 0;

	return 1;
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
    if (!Player_Logado(playerid))
		return 0;

    return 1;
}

public OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate)
{
    if (!Player_Logado(playerid))
		return 0;

	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (!Player_Logado(playerid))
		return 0;
	
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if (!Player_Logado(playerid))
		return 0;

	return 1;
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	if (!Player_Logado(playerid))
		return 0;

	return 1;
}

task OtherTimer[1000]()
{
	for (new medkit; medkit != MAX_MEDKIT; medkit++)
	{
		if (MedkitInfo[medkit][medkit_Valid]) {
			if (MedkitInfo[medkit][medkitLife] < 1.0 || gettime() > MedkitInfo[medkit][medkitTime])
				destroyMedKit(medkit);
		}
	}

	if (AnuncioMandado > 0)
	    AnuncioMandado --;

	if (TimeGranaTR > 0)
		TimeGranaTR --;
	else
	{
		new gstring[176];

	    for (new x; x != MAX_ORGS; x++)
		{
	        if (GetOrgTrs(x) && x > 0)
			{
	            new mney = GetOrgTrs(x) * 2000;

	            format(gstring, sizeof gstring, "Info: {FFFFFF}Sua organização ganhou {00AA00}$%s {FFFFFF}por manter {00AAFF}%d {FFFFFF}territórios sob controle.", getFormatText(mney), GetOrgTrs(x));
	            SendMembersMessage(x, 0x00AA44FF, gstring);

				OrgInfo_SetMoney(x, OrgInfo_GetMoney(x) + mney);
	        }
	    }

	    TimeGranaTR = ( 10 ) * 60 ;// 10 Minutos
	}
}

task updateImpostos[60000] ()
{
	for(new i = 0; i < unid; i++)
	{
		if (PropInfo[i][eLoaded] && PropInfo[i][eInsumos] > 0)
		{
			new lucro = GetPropriedadeLucro(i);
			removerDinheiroGoverno(lucro);
		   	PropInfo[i][eTill] += lucro;
			PropInfo[i][eInsumos] -= 6;

			if(PropInfo[i][eInsumos] < 0)
				PropInfo[i][eInsumos] = 0;


			atualizarPropText(i);
		}
	}

	for(new orgsid; orgsid < MAX_ORGS; orgsid++)
	{
	    if (OrgIsBuyMateriais(orgsid) && CofreOrg[orgsid][Materiais] < 500 && CofreOrg[orgsid][cMateriais] < 1500 && OrgInfo_GetMoney(orgsid) >= 1500*3)
	    {
	        new string[128];

	        pedido_MateriaisGramas(orgsid, 1500);
	   		pedido_MateriaisPreco(orgsid, 3);

	        format(string,sizeof(string), "((Rádio do tráfico)) {FFFFFF}%s está pedindo %sg de materiais e paga $%s por grama.", GetNomeOrg(orgsid), getFormatText(CofreOrg[orgsid][cMateriais]), getFormatText(CofreOrg[orgsid][mMateriais]));
	  		EmpregoMensagem(0xF1A439FF, string, 7); SendMembersMessage(12, 0xF1A439FF, string); SendMembersMessage(13, 0xF1A439FF, string); SendMembersMessage(24, 0xF1A439FF, string);

			format(string,sizeof(string), "{%s}» %s: {E4D88D}pedido de %sg de materiais automaticamente (pagando $%s por grama)", GetOrgColor(orgsid), GetNomeOrg(orgsid), getFormatText(CofreOrg[orgsid][cMateriais]), getFormatText(CofreOrg[orgsid][mMateriais]));
			SendMembersMessage(orgsid, -1, string);
		}
	}

	new Float:vehPos[3];
	
	for(new vehicleid; vehicleid != MAX_VEHICLES; vehicleid++)
	{
		GetVehiclePos(vehicleid, vehPos[0], vehPos[1], vehPos[2]);
	
		if (vehPos[0] >= 1969.0 && vehPos[1] >= -1099.5 && vehPos[0] <= 2162.0 && vehPos[1] <= -902.5 && !IsVehicleOccupied(vehicleid) && !IsACargaCar(vehicleid)) SetVehicleToRespawn(vehicleid);
	    else if (vehPos[0] >= 2162.0 && vehPos[1] >= -1133.5 && vehPos[0] <= 2407.0 && vehPos[1] <= -921.5 && !IsVehicleOccupied(vehicleid) && !IsACargaCar(vehicleid)) SetVehicleToRespawn(vehicleid);
	    else if (vehPos[0] >= 2408.0 && vehPos[1] >= -1135.5 && vehPos[0] <= 2640.0 && vehPos[1] <= -921.5 && !IsVehicleOccupied(vehicleid) && !IsACargaCar(vehicleid)) SetVehicleToRespawn(vehicleid);
	}

	/* 			Outros				*/
	if (OwnerMercadoNegro == 11) {
		OrgInfo_SetMoney(11, OrgInfo_GetMoney(11) + 120);
	}
}

task CheckGas[20000]()
{
   	checkCarsPositions();
	return true;
}

CALLBACK:Fillup(playerid)
{
    new string[128];
 	new FillUp;

    FillUp = GasMax - VehicleInfo[GetPlayerVehicleID(playerid)][vehicleCombustivel];

	new valorCombustivel = FillUp * 3;

	if(Refueling[playerid] == 1)
    {
		if(Player_GetMoney(playerid) >= valorCombustivel)
		{
			VehicleInfo[GetPlayerVehicleID(playerid)][vehicleCombustivel] = 100;

		    format(string, sizeof(string),"Você reabasteceu %d litros de combustível no seu veículo por $%s.", FillUp, getFormatText(valorCombustivel));
		    SendClientMessage(playerid,COLOR_LIGHTBLUE, string);
		    TogglePlayerControllable(playerid, true);
			Player_RemoveMoney(playerid, valorCombustivel);
			adicionarDinheiroGoverno(valorCombustivel);
			Refueling[playerid] = 0;
		}
		else
		{
		    TogglePlayerControllable(playerid, true);
		    format(string,sizeof(string),"Você não tem dinheiro suficiente para abastecer o seu veículo, custo: $%s.", getFormatText(valorCombustivel));
		    SendClientMessage(playerid,-1,string);
	   	}
	}
	return true;
}

showAtivos(playerid) 
{
	mysql_tquery(MySQL_Handle, "SELECT * FROM `ranks` ORDER BY `jogoudia` DESC LIMIT 50", "OnShowAtivos", "i", playerid);
}

CALLBACK:OnShowAtivos(playerid) {
	new row_count = MYSQL_GetRowsCount();
	if (row_count)
	{
		new string[128], name[MAX_PLAYER_NAME], jogou_dia;
	    MEGAString[0] = EOS;

	    strcat(MEGAString, "Pos/Nick\tTempo Jogado\n");

	    for(new s_rows; s_rows != row_count; s_rows++)
		{
	        cache_get_value_name(s_rows, "nome", name);
	        cache_get_value_name_int(s_rows, "jogoudia", jogou_dia);

	        if (!strcmp(name, PlayerName[playerid], true)) {
	            format(string, sizeof string, "{00FF00}%d º %s\t{00FF00}%s Tempo Jogado\n", s_rows + 1, name, ConvertTime(jogou_dia));
	        } else {
	        	format(string, sizeof string, "{999999}%d º {FFFFFF}%s\t%s {999999}Tempo Jogado\n", s_rows + 1, name, ConvertTime(jogou_dia));
			}
			strcat(MEGAString, string);
		}
	    ShowPlayerDialog(playerid, 5008, DIALOG_STYLE_TABLIST_HEADERS, "Rank: Mais ativos do dia", MEGAString, "Voltar", "");

	} else {
	    SendClientMessage(playerid, -1, "Houve um erro em nosso banco de dados, não foi possível obter os ranks !");
	}
}

stock listRank(playerid, const rankname[], const descricao[], const caminho[]) 
{
	new query[128];

	mysql_format(MySQL_Handle, query, sizeof query, "SELECT * FROM `ranks` ORDER BY `%s` DESC LIMIT 50", rankname);
	mysql_tquery(MySQL_Handle, query, "OnListRank", "isss", playerid, rankname, descricao, caminho);

	ShowLoadingDialog(playerid);
}

CALLBACK:OnListRank(playerid, const rankname[], const descricao[], const caminho[]) {
	new string[128];
	new name[MAX_PLAYER_NAME];
	new row_count = MYSQL_GetRowsCount();
	if (row_count)
	{
	    MEGAString[0] = EOS;
		strcat(MEGAString, "Pos/Nick\tPontos\n");

	    new rank_Name;
	    for(new s_rows; s_rows != row_count; s_rows++)
		{
	        cache_get_value_name(s_rows, "nome", name);
	        cache_get_value_name_int(s_rows, rankname, rank_Name);

	        if (!strcmp(name, PlayerName[playerid], true)) {
	            format(string, sizeof string, "{00FF00}%dº %s\t{00FF00}%d %s\n", s_rows + 1, name, rank_Name, descricao);
	        } else {
	        	format(string, sizeof string, "{999999}%dº {FFFFFF}%s\t%d {999999}%s\n", s_rows + 1, name, rank_Name, descricao);
			}
			strcat(MEGAString, string);
		}
	    ShowPlayerDialog(playerid, 5008, DIALOG_STYLE_TABLIST_HEADERS, caminho, MEGAString, "Voltar", "");

	} else {
	    SendClientMessage(playerid, -1, "Houve um erro em nosso banco de dados, não foi possível obter os ranks !");
	}
}

saveRank(playerid)
{
	new query[385];
	mysql_format(MySQL_Handle, query, sizeof query, "SELECT * FROM `ranks` WHERE `nome` = '%s' LIMIT 1", PlayerName[playerid]);
	mysql_tquery(MySQL_Handle, query, "OnSelectRank", "i", playerid);
}

CALLBACK:OnSelectRank(playerid) {
	new rowsmysql = MYSQL_GetRowsCount(), query[385];

	if (!rowsmysql) {
	    mysql_format(MySQL_Handle, query, sizeof query, "INSERT INTO `ranks` (`nome`) VALUE ('%s')", PlayerName[playerid]);
	    mysql_tquery(MySQL_Handle, query);
	}

	new maconha = CountPlayerItemsByType(playerid, ITEM_TYPE_MACONHA),
		cocaina = CountPlayerItemsByType(playerid, ITEM_TYPE_COCAINA),
		crack = CountPlayerItemsByType(playerid, ITEM_TYPE_CRACK);

	mysql_format(MySQL_Handle, query, sizeof query, "UPDATE `ranks` SET `nivel`='%d',`horasjogadas`='%d',`kills`='%d',`mortes`='%d',\
		`banco`='%d',`crimes`='%d',`materiais`='%d',`maconha`='%d',`cocaina`='%d',`crack`='%d',`arenakills`='%d',`contratos`='%d',\
		`apreensoes`='%d',`jogoudia`='%d',`cash`='%d',`ouros`='%d',`pixador`='%d' WHERE nome = '%e' LIMIT 1",
		PlayerInfo[playerid][pLevel], PlayerInfo[playerid][pConnectTime], PlayerInfo[playerid][pKills],
		PlayerInfo[playerid][pDeaths], PlayerInfo[playerid][pConta], PlayerInfo[playerid][pCrimes],
		PlayerInfo[playerid][pMats], maconha, cocaina, crack, 
		PlayerInfo[playerid][pArenaKills], PlayerInfo[playerid][pContratos], PlayerInfo[playerid][pMinhasApreensoes]+PlayerInfo[playerid][pMorteSuspeito],
		Player_GetActivity(playerid, getdate()), Player_GetCash(playerid), PlayerInfo[playerid][pOuros], PlayerInfo[playerid][pPixador], 
		PlayerName[playerid]);
	mysql_pquery(MySQL_Handle, query);
}

ptask AtualizarRank[1200000](playerid) {
    if (Player_Logado(playerid))
		saveRank(playerid);

	return 1;
}

stock IsABombCar(carid)
{
	new model = GetVehicleModel(carid);
	switch(model)
	{
	    case 520, 432, 425: return 1;
	}
	return 0;
}

stock IsACargaCar(carid)
{
	new model = GetVehicleModel(carid);
	switch(model)
	{
	    case 435, 450, 584, 591: return 1;
	}
	return 0;
}

stock resetarAtividadesOrg()
{
	for(new x; x != MAX_ORGS; x++)
	{
	    orgKidnapping[x] = false; 
		irReforco[x][3] = 0; 
		CofreOrg[x][InvasaoOrg] = 0;
		CofreOrg[x][TrainingOrg] = 0;
		roubouOrg[x] = false;
	}
}

stock resetarGuerrasPd()
{
	for(new org; org != MAX_ORGS; org++)
	{
	    if (orgWarCreated[org] > 0) orgWarCreated[org]--;
	}
	if (!warInfo[warCreated]) orgWarTerror = false;
}

CALLBACK: onPlayerPortoesCheck(playerid)
{
	new query[185];
	new rowstring[75];

	cache_get_value_name(0, "portao_vencimento", rowstring);
	format(query, sizeof (query), "UPDATE `portoes` SET `portao_vencimento` = TIMESTAMPADD(DAY, 7, '%s') WHERE nome = '%e'", rowstring, PlayerName[playerid]);
	mysql_tquery(MySQL_Handle, query);
}

hook OnPlayerUpdate(playerid)
{
    timerESC[playerid] = gettime();

 	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
   	{
		// Sistema de Skate
		if (SkateInfo[playerid][s_Setado] && SkateInfo[playerid][s_Andando])
		{
			static KEY:playerKeys[3];

			GetPlayerKeys(playerid, playerKeys[0], playerKeys[1], playerKeys[2]);

			if (playerKeys [1] != KEY:0 || playerKeys [2] != KEY:0)
			{
			    SendClientMessage(playerid, COLOR_LIGHTRED, "OBS: Você deve segurar apenas o 'BOTÃO DE MIRAR' e virar o mouse pra direção que desejar!");
				StopPlayerSkate(playerid);

				return true;
			}
			UpdatePlayerSkate(playerid, playerKeys[0]);

			return true;
		}
	}

	if (PlayerInfo[playerid][pRestoreFome] > 0.0 && PlayerInfo[playerid][pRestoreSede] > 0.0 && SMOKE_PUFF_LIFE[playerid] > 0.0)
	{
		SetPlayerArmedWeapon(playerid, WEAPON_FIST);
	}

	return true;
}

CMD:laptop(playerid, params[])
{
	if (GetPlayerOrg(playerid) != 8 && GetPlayerOrg(playerid) != 22)
		return SendClientMessage(playerid, -1, "Você não é um assassino de aluguel.");

	MEGAString[0] = EOS;
	strcat(MEGAString, "Contratos\n");
	strcat(MEGAString, "Disfarce\n");
	strcat(MEGAString, "Meu contrato\n");
	strcat(MEGAString, "Largar contrato\n");
	strcat(MEGAString, "Modo secreto\n");

	ShowPlayerDialog(playerid, 90, DIALOG_STYLE_LIST, "× Agência dos Assassinos ×", MEGAString, "Acessar", "Cancelar");
	return true;
}

CMD:capacete(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	new VIM:vim = Vehicle_GetVIM(vehicleid);

	if (VIM_IsBike(vim))
	{
		if (!IsPlayerHaveItem(playerid, ITEM_TYPE_CAPACETE))
			return SendClientMessage(playerid, -1, "Você não tem um capacete na mochila. Compre um no mercado 24/7!");

		new string[75];
		format(string, sizeof string, "*%s colocou seu capacete", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		SetPlayerAttachedObject(playerid, Slot_Capacete, GetPlayerItemTypeModel(playerid, ITEM_TYPE_CAPACETE), 2, 0.069999,0.027999,0.000000,0.000000,86.700019,88.999969,1.083999,1.124000,1.194000);
		SendClientMessage(playerid, -1, "Caso queira tirar o capacete da cabeça use: /retirarcapacete.");
	}
	else SendClientMessage(playerid, -1, "Você precisa estar em uma moto!");

	return true;
}

CMD:hospitalizar(playerid, params[])
{
	new	motivo[15],
		string[120],
		tempo
	;

	if (!Admin_GetNivel(playerid)) return SendClientMessage(playerid, -1, "Você não está autorizado a usar este comando.");

	if (Admin_GetNivel(playerid) < DONO && !Staff_GetWorking(playerid)) return SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

	new idplayer;
	if (sscanf(params, "uds[15]", idplayer, tempo, motivo)) return SendClientMessage(playerid, -1, "Modo de uso: /hospitalizar (id do jogador) (minutos) (motivo)");

	if (!Player_Logado(idplayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (strlen(motivo) < 3 || strlen(motivo) > 15) return SendClientMessage(playerid, -1, "O motivo deve ter entre 3 a 15 caracteres.");

	format(string, 127, "AdmAviso: %s hospitalizou %s por %d minutos, motivo: %s.", PlayerName[playerid], PlayerName[idplayer], tempo, motivo);
	SendClientMessageToAll(COLOR_LIGHTRED, string);

	PlayerInfo[idplayer][pHospital] = true;
	PlayerInfo[idplayer][pTempoHospital] = tempo*60;
	PlayerInfo[idplayer][pHAjustado] = false;
	customorte[idplayer] = 0;
	SpawnPlayer(idplayer);

	server_log("hospitalizar", string);

	return true;
}

CMD:hospitalizados(playerid, params[])
{
	new string[128];
	new count = 0;

	MEGAString[0] = EOS;
	strcat(MEGAString, "ID\tNick\tTempo\tHospital\n");
	foreach(new players : Character)
	{
		if(PlayerInfo[players][pHospital] && PlayerInfo[players][pTempoHospital] > 0)
		{
			format(string, sizeof string, "%02d\t%s\t{FF0000}%s (%d segundos)\tHospital Central\n",
			players, PlayerName[players], ConvertTime(PlayerInfo[players][pTempoHospital]), PlayerInfo[players][pTempoHospital]);
			strcat(MEGAString, string);

			List_SetPlayers(playerid, count, players);
			count ++;
		}
	}

	format(string, sizeof string, " {FFFFFF}Hospitalizados ({FF0000}%d{FFFFFF})", count);

	if (!count) {
		return SendClientMessage(playerid, -1, "Não tem nenhum hospitalizado online.");
	}
	ShowPlayerDialog(playerid, 33, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Infos", "Fechar");
	return true;
}

CMD:stopani(playerid, params[])
{
	if (GetPlayerAnimationIndex(playerid) == 1130) 
		return true;
	
	if (IsPlayerWithHandsUp(playerid))
		return true;

	if (GetPVarInt(playerid, "movelRoubou") || IsPlayerInDrone(playerid) || PlayerCaminhao[playerid][caminhaoValid])
		return SendClientMessage(playerid, -1, "Você não pode usar este comando agora !");

	//if(IsPlayerCongelado(playerid))return SendClientMessage(playerid, -1, "Você não pode usar este comando estando congelado !");

	if (PlayerToPoint(3.0,playerid,2144.3711,1641.4792,993.5761) || PlayerToPoint(3.0,playerid, 303.9886,-169.0725,999.5938) || PlayerToPoint(3.0,playerid,294.8029,-57.8727,1001.5156) || PlayerToPoint(3.0,playerid,162.1254,-79.7925,1001.8047) ||
		PlayerToPoint(3.0,playerid,211.3817,-96.1272,1005.2578) || PlayerToPoint(3.0,playerid,820.8934,8.5365,1004.1958) || PlayerToPoint(3.0,playerid,205.4959,-11.5585,1005.2109)) return SendClientMessage(playerid, -1, "Você não pode usar esse comando agora.");

	ClearAnimations(playerid);

	return true;
}

CMD:entrarevento(playerid)
{
	if (PlayerToPoint(3, playerid, 1769.5328,-1863.3152,13.5752))
	{
    	if(typeevento == 1)
    	{
		    // Corrida
		}
		else if(typeevento == 3)
		{
		    if(hayiniciado)
		    {
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você entrou no evento de HAY, suba até o topo para pegar o prêmio!");
		    	SetPlayerHay(playerid);
			}
			else SendClientMessage(playerid, -1, "Nenhum Evento de HAY iniciado!");
		}
		else if(typeevento == 4)
		{
		    if(SurvivalInitialized)
		    {
		        if (SurvivalTimer != -1)return SendClientMessage(playerid, -1, "O evento Survival já foi iniciado, tente na próxima vez!");

				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Você entrou no evento de Survival, aguarde um admin iniciar!");
		    	SetPlayerInSurvival(playerid);
			}
			else SendClientMessage(playerid, -1, "Nenhum evento Survival iniciado!");
		}
		else SendClientMessage(playerid, -1, "Nenhum Evento iniciado, espere um admin iniciar um!");
	}
	else SendClientMessage(playerid, -1, "Você não está na empresa de eventos!");
	return true;
}

CMD:mudarluta(playerid, params[])
{
    if(IsPlayerInRangeOfPoint(playerid, 2.0, 768.2192,-3.9873,1000.7203))
	{
	    TogglePlayerControllable(playerid, true);
		ShowPlayerDialog(playerid, 1389, DIALOG_STYLE_LIST, "Estilos De Luta", "Cotoveladas\nBoxe\nRua\nKickBoxing\nKarate\nNormal", "Confirma", "Cancela");
	}
	else
	{
        SendClientMessage(playerid, -1, "Voce não está no ginásio de luta de LS.");
	}
	return true;
}

stock ChangePlayerNick(playerid, const new_nick[], size=sizeof(new_nick)) {
	new string[128];

	for(new prop; prop != unid; prop++)
	{
	    if (IsPlayerOwnerPropertie(playerid, prop))
		{
			format(PropInfo[prop][eOwner], MAX_PLAYER_NAME, new_nick);
        	atualizarPropText(prop);
	    }
	}

	Discord_SetPlayerNick(playerid, new_nick);
	Loot_OwnerChangeNick(playerid, new_nick);

	mysql_format(MySQL_Handle, string, sizeof string, "UPDATE ranks SET `nome` = '%e' WHERE nome = '%e'", new_nick, PlayerName[playerid]);
	mysql_tquery(MySQL_Handle, string);

	// player
	mysql_format(MySQL_Handle, string, sizeof string, "UPDATE player SET `nome` = '%e' WHERE `id` = '%d'", new_nick, PlayerInfo[playerid][pID]);
	mysql_tquery(MySQL_Handle, string);

	// E-mails
	mysql_format(MySQL_Handle, string, sizeof string, "UPDATE email SET `de` = '%e' WHERE `de` = '%e'", new_nick, PlayerName[playerid]);
	mysql_tquery(MySQL_Handle, string);
	mysql_format(MySQL_Handle, string, sizeof string, "UPDATE email SET `para` = '%e' WHERE `para` = '%e'", new_nick, PlayerName[playerid]);
	mysql_tquery(MySQL_Handle, string);

	mysql_format(MySQL_Handle, string, sizeof string, "UPDATE ranks SET `nome` = '%e' WHERE `nome` = '%e'", new_nick, PlayerName[playerid]);
	mysql_tquery(MySQL_Handle, string);

	mysql_format(MySQL_Handle, string, sizeof string, "UPDATE ranks SET `nome` = '%e' WHERE `nome` = '%e'", new_nick, PlayerName[playerid]);
	mysql_tquery(MySQL_Handle, string);

	foreach(new portoes : IterWall)
	{
	    if (!strcmp(PortaoInfo[portoes][portaoNick], PlayerName[playerid])) {
			format(PortaoInfo[portoes][portaoNick], MAX_PLAYER_NAME, new_nick);

			mysql_format(MySQL_Handle, string, sizeof (string), "UPDATE `portoes` SET `dono` = '%e' WHERE `id` = '%d'", new_nick, portoes);
			mysql_tquery(MySQL_Handle, string);
		}
	}

	// Atualiza as informações do player na organização
	for(new slot; slot < MAX_SLOTS_ORGS; slot++) {
		if (OrgMembros[GetPlayerOrg(playerid)][slot][MemberID] == PlayerInfo[playerid][pID]) {
			format(OrgMembros[GetPlayerOrg(playerid)][slot][MemberName], size, new_nick);
		}
	}

	SetPlayerName(playerid, new_nick);
	GetPlayerName(playerid, PlayerName[playerid], MAX_PLAYER_NAME);

	UpdatePlayerInfos(playerid);
}

CMD:trocarnick(playerid, params[])
{
	if (PlayerInfo[playerid][pTrocaNick] < 1)
	{
	    SendClientMessage(playerid, COLOR_ERROR, "Você não tem trocas de nick disponível.");
	    SendClientMessage(playerid, COLOR_ORANGE, "Como comprar? Você pode comprar na /lojacash do servidor, ou de outro jogador, procure um no /anuncio.");
	    SendClientMessage(playerid, COLOR_ORANGE, "Como usar? Ao comprar, use o item que foi para o inventário e use o comando novamente, o uso é por unidade.");
		return true;
	}

	new new_nick[MAX_PLAYER_NAME], string[128];
	if (sscanf(params, "s[24]", new_nick))
	{
		SendClientMessage(playerid, -1, "Modo de uso: /trocarnick (novo nick)");
		format(string, sizeof(string), "Informação: Você tem %d trocas de nick disponível no RG.", PlayerInfo[playerid][pTrocaNick]);
		SendClientMessage(playerid, COLOR_ORANGE, string);
		
		return true;
	}

	if (!PlayerIsNickValid(new_nick))
		return SendClientMessage(playerid, -1, "Você digitou um nick inválido, tente outro, use entre 5 a 20 caracteres.");

	if (strcmp(PlayerName[playerid], new_nick, true) == 0)
		return SendClientMessage(playerid, -1, "Você precisa usar um nick diferente do atual.");

	if (DoesPlayerExists(new_nick))
		return SendClientMessage(playerid, -1, "O nick que você escolheu não está disponível.");

	// Logs e mensagem de aviso
	format(string, sizeof(string), "AdmAviso: %s(%d) mudou o nick para %s.", PlayerName[playerid], playerid, new_nick);
	Staff_ChatToAll(COLOR_LIGHTRED, string, ESTAGIARIO); 
	server_log("mudarnick", string);

	format(string, sizeof(string), "Você alterou seu nick para %s.", new_nick);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

	ChangePlayerNick(playerid, new_nick);

	PlayerInfo[playerid][pTrocaNick] --;
	return true;
}

CMD:assaltar(playerid, params[])
{
	if(gettime() < GetPVarInt(playerid, #VarFloodAssalto))
		return SendClientMessage(playerid, COLOR_GRAD, #Você precisa esperar alguns segundos para mandar mensagem no chat novamente);

	SetPVarInt(playerid, #VarFloodAssalto, gettime()+15);

	if(!IsAMember(playerid))
	{
	    SendClientMessage(playerid, -1, "Você não pode usar esse comando!" );
		return 1;
	}

	if (IsPlayerInSafeZone(playerid))
		return SendClientMessage(playerid, -1, "Você não pode assaltar um jogador que está em área neutra.");

	if(PlayerInfo[playerid][pLevel] < 2)
		return SendClientMessage(playerid, -1, "Você precisa ter no mínimo nível 2 para usar esse comando.");


	new idplayer;
	if(sscanf(params, "u", idplayer)) return SendClientMessage(playerid, -1, "Use: /assaltar [id]");

	if (!IsPlayerConnected(idplayer)) return SendClientMessage(playerid, -1, "Este jogador não está conectado.");
	
	new comparsa = GetPVarInt(playerid, "Comparsa");
	if(comparsa == -1) return SendClientMessage(playerid, -1, "Você não possui um comparsa. Use /comparsa para convidar alguém.");
	if(!Player_Logado(comparsa)) {
		SetPVarInt(playerid, "Comparsa", -1);
		return SendClientMessage(playerid, -1, "Seu comparsa não está mais logado no servidor.");
	}

	if(!ProxDetectorS(5.0, playerid, comparsa))
		return SendClientMessage(playerid, -1, "Seu comparsa não está próximo de você para assaltar.");

	if(GetPlayerInterior(playerid) > 0)
		return SendClientMessage(playerid, -1, "Não é permitido assaltar em interiores.");

	if(idplayer != INVALID_PLAYER_ID)
	{
		if (ProxDetectorS(5.0, playerid, idplayer))
		{
			new string[128];
			format(string, sizeof(string), "* Você está assaltando %s.", PlayerName[idplayer]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			format(string, sizeof(string), "* Assaltante %s diz: Perdeu! Isso é um assalto, passa tudo pra cá.", PlayerName[playerid]);
			SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);
			format(string, sizeof(string), "* Assaltante %s diz: Bora, bora, manda logo, senão vai morrer.", PlayerName[comparsa]);
			SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);
			SendClientMessage(idplayer, COLOR_LIGHTBLUE, "/aceitar assalto para aceitar");
			SendClientMessage(idplayer, COLOR_LIGHTRED, "Caso reaja ao assalto e morra, irá perder o dinheiro e passsará 5 minutos no hospital!");
			format(string, sizeof(string), "*%s está assaltando %s!", PlayerName[playerid], PlayerName[idplayer]);
			SendClientMessageInRange(20.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			SetPlayerCriminal(playerid, 255, "Tentativa de Assalto", 2);
			SetPVarInt(idplayer, "assaltado", 1);
			SetPVarInt(idplayer, "assaltante", playerid);
			SetPVarInt(idplayer, "assaltoTempo", gettime()+120);
			SetPVarInt(idplayer, "assaltoTempoMinimo", gettime()+20);

			format(string, sizeof(string), "%s e %s tentaram assaltar %s", PlayerName[playerid], PlayerName[comparsa], PlayerName[idplayer]);
			server_log("assaltos", string);
		}
		else
		{
			SendClientMessage(playerid, -1, "Esse jogador não está perto de você!");
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "ID/Nome Invalido !");
		return 1;
	}
	return 1;
}

CMD:hqpr(playerid, params[])
{
    if(PlayerToPoint(2.0, playerid, 865.3195, -1634.3951, 14.9297))
	{
        SetPlayerInterior(playerid, 0);
		SetPlayerPos(playerid, 2122.5610,-2270.5774,20.6719);
	}
    if(PlayerToPoint(2.0, playerid, 2122.5610,-2270.5774,20.6719))
    {
	    SetPlayerInterior(playerid, 0);
        SetPlayerPos(playerid, 865.3195, -1634.3951, 14.9297);
    }
	return true;
}

CMD:pagar(playerid, params[])
{
	new quantidade;

	new idplayer;
	if (sscanf(params, "ud", idplayer, quantidade)) return SendClientMessage(playerid, -1, "Modo de uso: /pagar (id do jogador) (quantidade)");

	if (!Player_Logado(idplayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

	if (Staff_GetWorking(idplayer) && Admin_GetNivel(playerid)) return SendClientMessage(playerid, -1, "Você não pode pagar para administrador em modo trabalho.");

	if (quantidade < 1 || quantidade > 10000) return SendClientMessage(playerid, -1, "Você deve pagar entre $1 a $10.000.");

	if (!ProxDetectorS(5.0, playerid, idplayer)) return SendClientMessage(playerid, -1, "Você não está perto desse jogador.");

	if (Player_GetMoney(playerid) < quantidade) return SendClientMessage(playerid, -1, "Você não tem esse valor em mãos.");

	if(GetPVarInt(playerid, "assaltado") == 1) return SendClientMessage(playerid, -1, "Você não pode usar esse comando sendo assaltado.");

	Player_RemoveMoney(playerid, quantidade);
	Player_AddMoney(idplayer, quantidade);

	new string[98];

	format(string, sizeof(string), "Você pagou {FF0000}$%s {FFFFFF}para %s(%d).", getFormatText(quantidade), PlayerName[idplayer], idplayer);
	SendClientMessage(playerid, -1, string);

	format(string, sizeof(string), "Você recebeu {00AA00}$%s {FFFFFF}de %s(%d).", getFormatText(quantidade), PlayerName[playerid], playerid);
	SendClientMessage(idplayer, -1, string);

	format(string, sizeof(string), "(( %s deu dinheiro para %s ))", PlayerName[playerid], PlayerName[idplayer]);
	SendClientMessageInRange(30.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

	format(string, sizeof(string), "(Pagar): %s(%d) deu $%s para %s(%d)", PlayerName[playerid], playerid, getFormatText(quantidade), PlayerName[idplayer], idplayer);
	server_log("pagar", string);

	return true;
}

CMD:licencas(playerid, const params[])
{
	if (PlayerToPoint(2.0, playerid, -2033.3137,-117.4329,1035.1719))
	{
		TogglePlayerControllable(playerid, true);
		ShowPlayerDialog(playerid,2571,DIALOG_STYLE_TABLIST_HEADERS,
		"Compre sua licença",
		"Licença\tCusto\n\
		{FFFFFF}Carteira de Motorista\t{00AA00}$3.000\n\
		{FFFFFF}Licença Aérea\t{00AA00}$15.000\n\
		{FFFFFF}Licença de Navegacao\t{00AA00}$13.000\n\
		{FFFFFF}Porte de Armas\t{00AA00}$10.000","Prosseguir","Cancelar");
	}
	return 1;
}

CMD:agenda(playerid, params[])
{
	new idPlayer;
	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /agenda (id do jogador)");

	if (!IsPlayerConnected(idPlayer) || !Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "Este jogador não está conectado/logado no servidor.");

	new string[128];
	format(string, 128, "Agenda telefônica: {FFFFFF}O número do celular de: {00CCFF}%s{FFFFFF} é {FFA54F}%d", PlayerName[idPlayer], PlayerInfo[idPlayer][numeroCelular]);
	SendClientMessage(playerid, 0xFFA54FFF, string);

	return true;
}

CMD:patins(playerid)
{
	if(!PlayerInfo[playerid][pPatins])return SendClientMessage(playerid, -1, "Você não tem um patins, compre um na 24/7 !");
	if(IsPlayerInAnyVehicle(playerid))return SendClientMessage(playerid, -1, "Você não pode usar este comando dentro de um veículo !");

	new string[55];
	if(patinss[playerid] == 0)
	{
		if(SkateInfo[playerid][s_Setado])
			return SendClientMessage(playerid, -1, "Você não pode andar de patins com um skate na mão !");

		patinss[playerid]=1;
		SendClientMessage(playerid, COLOR_GREY, "Você colocou seus patins");
		ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle", 4.1, false, true, true, false, 0);
		format(string, sizeof(string), "* %s colocou seu patins", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	}
	else
	{
		patinss[playerid]=0;
		SendClientMessage(playerid, COLOR_GREY, "Você retirou seus patins");
		SetTimerEx("DesbugarPatins", 800, false, "d", playerid);
		ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle", 4.1, false, true, true, false, 0);
		format(string, sizeof(string), "* %s retirou seu patins", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	}
	return 1;
}

CALLBACK:DesbugarPatins(playerid)
{
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]+0.7);
	return ClearAnimations(playerid);
}

CMD:trocarsenha(playerid)
	return SendClientMessage(playerid, -1, "Sistema temporariamente indisponível");

CMD:ang(playerid, params[]) 
	return SendClientMessage(playerid, -1, "Use /anorg (comando mudado para evitar possíveis FAIL).");

/* 								Comandos de Anúncios								*/

CMD:an(playerid, result[])
{
	if (!strcmp(result, "personalizado", true) || !strcmp(result, "personalisado", true))
		return SendClientMessage(playerid, -1, "Use /anperso (comando mudado para evitar possíveis FAIL).");

	else return SendClientMessage(playerid, -1, "Use /anuncio (comando mudado para evitar possíveis FAIL).");
}

CMD:anuncio(playerid, result[])
{
	if (!Player_Logado(playerid))
		return SendClientMessage(playerid,-1, "Você não pode usar esse comando no momento.");

	if(PlayerInfo[playerid][pLevel] < 3 || PlayerInfo[playerid][pConnectTime] < 10)
		return SendClientMessage(playerid, -1, "É necessário ter no mínimo nível 3 e 10 horas de jogo.");

	if (sscanf(result, "s[87]", result)) return SendClientMessage(playerid, -1, "Modo de uso: /anuncio (texto)");

	if (strlen(result) < 20 || strlen(result) > 86) return SendClientMessage(playerid, -1, "O anúncio deve conter entre 20 a 86 caracteres.");

	new string[210], payout = strlen(result) * 20;          // String e valor do anúncio

	if (Player_GetMoney(playerid) < payout)
	{
		format(string, sizeof(string), "Você precisa de $%s para anunciar %d caracteres no anúncio.", getFormatText(payout), strlen(result));
		return SendClientMessage(playerid, -1, string);
	}
	if (TempoAn[playerid] > 0)
	{
		format(string, sizeof(string), "Você usou o anúncio recentemente, aguarde %s para usar novamente.", ConvertTempo(TempoAn[playerid]));
		return SendClientMessage(playerid, -1, string);
	}
	if(AnuncioMandado > 0)
	{
		format(string, sizeof(string), "Um anúncio foi mandado a %d segundos, aguarde para mandar novamente.", AnuncioMandado);
		return SendClientMessage(playerid, -1, string);
	}

	format(string, sizeof(string), "[ANÚNCIO %s]{FCFCFA}: %s{%s}, %s[%d] Celular: %d", GetAnuncioRank(playerid), result, GetVipColor(playerid), PlayerName[playerid], playerid, PlayerInfo[playerid][numeroCelular]);

	#if defined _CENSORED_protection
		censored_word_detected(string);
	#endif

	switch (PlayerInfo[playerid][pVIP])
	{
		case 1: 			SendClientMessageToAll(0xA4CCC3FF, string), TempoAn[playerid] = 50;
		case 2, 5, 6: 		SendClientMessageToAll(0xDBB960FF, string), TempoAn[playerid] = 40;
		case 7: 			SendClientMessageToAll(0x017bffFF, string), TempoAn[playerid] = 35;
		case 8:
		{
			SendClientMessageToAll(0xDC0139FF, string);

			TempoAn[playerid] = 30;
		}
		default: 			SendClientMessageToAll(0x00D900FF, string), TempoAn[playerid] = 70;
	}

	server_log("anuncios", string);

	Player_RemoveMoney(playerid, payout);
	OrgInfo_SetMoney(ID_ORG_SANNEWS, OrgInfo_GetMoney(ID_ORG_SANNEWS) + payout);
	AnuncioMandado = 20;

	format(string, sizeof(string), "Você pagou $%s para anunciar, caracteres usados: %d.", getFormatText(payout), strlen(result));
	return SendClientMessage(playerid, -1, string);
}

CMD:anperso(playerid)
{
	if (!Player_Logado(playerid))
		return SendClientMessage(playerid,-1, "Você não pode usar esse comando no momento.");

	if (PlayerInfo[playerid][pAnuncioP] == false && PlayerInfo[playerid][pVIP] < 7) return SendClientMessage(playerid, -1, "Você precisa ser Sócio Supreme ou ter o item Anúncio Personalizado.");

	if (gettime() < GetPVarInt(playerid, #VarFloodAnP)) return SendClientMessage(playerid, -1, #Você precisa esperar alguns segundos para mandar mensagem no chat novamente);

	MEGAString[0] = EOS;

	strcat(MEGAString, "{FFFFFF}Anúncio personalizado » {DC5858}Explicação\n\n");

	strcat(MEGAString, "{DC5858}Funcionamento:\n");
	strcat(MEGAString, "{FFFFFF}			Você pode fazer anúncios com as cores que preferir.\n\n");

	strcat(MEGAString, "{DC5858}Qual as cores que posso usar?\n");
	strcat(MEGAString, "{FFFFFF}			Entre no site: http://html-color-codes.info/Codigos-de-Cores-HTML/.\n\n");

	strcat(MEGAString, "{DC5858}Exemplo de textos:\n\n");
	strcat(MEGAString, "{FFFFFF}			{*FF0000} VENDO CASA {*00FF00}100kk {8B8A8A}(sem os '*' no código de cor)\n");
	strcat(MEGAString, "{FFFFFF}Como ficará:	{FF0000}VENDO CASA {00FF00}100kk\n\n");

	strcat(MEGAString, "{DC5858}OBS: {FFFFFF}O anúncio personalizado é apenas para jogadores Sócio Supreme ou com o item 'Anúncio Personalizado Permanente'");

	ShowPlayerDialog(playerid, 36, DIALOG_STYLE_INPUT, "{DC5858}Anúncio personalizado", MEGAString, "Anunciar", "Cancelar");

	return true;
}

CMD:desativar(playerid, tmp[])
{
	if(!Player_Logado(playerid))
	{
		SendClientMessage(playerid, COLOR_GRAD, "    Você não fez o login");
		return true;
	}
	if(isnull(tmp))
	{
		SendClientMessage(playerid, -1, "|______________ Desabilitar ______________|");
		SendClientMessage(playerid, -1,"/desativar [nome]");
		SendClientMessage(playerid, COLOR_GREY,"Nomes Disponíveis: org, noticias");
		return true;
	}
	if(strcmp(tmp, "noticias", true) == 0)
	{
		if (!gNoticias[playerid])
		{
			gNoticias[playerid] = 1;
			SendClientMessage(playerid, -1, "Chat de notícias desativado !");
		}
		else if (gNoticias[playerid])
		{
			gNoticias[playerid] = 0;
			SendClientMessage(playerid, -1, "Chat de notícias ativado !");
		}
	}
	if(strcmp(tmp, "org", true) == 0)
	{
		if (!Chat_Organizacao[playerid])
		{
			Chat_Organizacao[playerid] = 1;
			SendClientMessage(playerid, -1, "Chat da organização desativado !");
		}
		else if (Chat_Organizacao[playerid])
		{
			Chat_Organizacao[playerid] = 0;
			SendClientMessage(playerid, -1, "Chat da organização ativado !");
		}
	}
	else if(strcmp(tmp, "celular", true) == 0)
	{
		if(PlayerInfo[playerid][pVIP] > 0 || Admin_GetNivel(playerid) >= ESTAGIARIO)
		{
			if (!PhoneOnline[playerid])
			{
				PhoneOnline[playerid] = 1;
				SendClientMessage(playerid, COLOR_GRAD, "   Você desligou seu celular (não receberá ligações nem SMS) !");
				MobileInfo[playerid][mobileCall] = MAX_PLAYERS+5;
			}
			else if (PhoneOnline[playerid])
			{
				PhoneOnline[playerid] = 0;
				SendClientMessage(playerid, COLOR_GRAD, "   Você ligou seu celular !");
			}
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "|______________ Desabilitar ______________|");
		SendClientMessage(playerid, -1,"/desativar [nome]");
		SendClientMessage(playerid, COLOR_GREY,"Nomes Disponíveis: org, noticias");
	}
	return true;
}

CMD:eu(playerid, result[])
{
	if (!Player_Logado(playerid)) return SendClientMessage(playerid, -1, "Você não pode usar este comando agora.");

	if(isnull(result)) return SendClientMessage(playerid, -1, "Modo de uso: /eu (ação que irá simular)");

	new string[128];

	format(string, sizeof(string), "%s %s", PlayerName[playerid], result);

	#if defined _CENSORED_protection
		censored_word_detected(string);
	#endif

	return SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
}
alias:eu("me")

// CMD:largararma(playerid)
// {
// 	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;

// 	if(gettime() < GetPVarInt(playerid, #VarFlood17))
// 		return SendClientMessage(playerid, COLOR_GRAD, #Você não pode usar este comando com tanta frequencia);
// 	SetPVarInt(playerid, #VarFlood17, gettime()+5);

// 	if(IsPlayerCuffed(playerid) || Player_GetTraining(playerid)){

// 		return SendClientMessage(playerid, -1, "Você não pode usar este comando agora !");
// 	}

// 	switch(GetPlayerWeapon(playerid)){

// 		case 9, 16, 35, 37, 38, 44, 45:
// 			return SendClientMessage(playerid, -1, "Você não pode largar esta arma !");
// 	}

// 	new WEAPON:GunID = GetPlayerWeapon(playerid);
// 	new GunAmmo = GetPlayerAmmo(playerid);

// 	if (GunID > WEAPON:0 && GunAmmo != 0) {
// 		RemovePlayerWeapon(playerid, GunID);

// 		new weapon_name[25];
// 		GetWeaponName(GunID, weapon_name);
// 		dropItem(playerid, ITEM_TYPE_WEAPON, GunID, GunAmmo, weapon_name);

// 		new buffer[85];
// 		format(buffer, sizeof(buffer), "Você largou um(a) %s.", weapon_name);
// 		SendClientMessage(playerid, 0x33AA3300, buffer);

// 		format(buffer, sizeof(buffer), "*%s colocou um(a) %s no chão.", PlayerName[playerid], weapon_name);
// 		SendClientMessageInRange(30.0, playerid, buffer, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
// 	}
// 	return 1;
// }

CMD:largargrana(playerid, params[]) {

	if(!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Você não está logado !");

	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || GetPVarInt(playerid, "assaltado") == 1)
		return SendClientMessage(playerid, -1, "Você não pode usar este comando agora !");

	if(gettime() < GetPVarInt(playerid, #VarFlood17))
		return SendClientMessage(playerid, COLOR_GRAD, #Você não pode usar este comando com tanta frequencia);
	SetPVarInt(playerid, #VarFlood17, gettime()+2);

	if(IsPlayerCuffed(playerid)){
		return SendClientMessage(playerid, -1, "Você não pode usar este comando agora !");
	}

	new quantia;

	if (sscanf(params, "d", quantia))
		return SendClientMessage(playerid, -1, "Use: /largargrana [Quantidade]");

	if(quantia < 1000 || quantia > 1000000){
		return SendClientMessage(playerid, -1, "Você pode largar no mínimo $1.000 e no máximo $1.000.0000 !");
	}

	if(Player_GetMoney(playerid) < quantia){

		return SendClientMessage(playerid, -1, "Você não tem toda essa grana !");
	}

	new
		string[75]
	;

	format(string, sizeof string, "%s largou $%d", PlayerName[playerid], quantia);
	server_log("dinheiro", string);

	dropItem(playerid, ITEM_TYPE_DINHEIRO, 1212, quantia, "Dinheiro");

	Player_RemoveMoney(playerid, quantia);

	format(string, sizeof string, "Você dropou $%s", getFormatText(quantia));
	SendClientMessage(playerid, COLOR_GREY, string);
	return 1;
}
alias:largargrana("largardinheiro")

CMD:guardargrana(playerid, params[]) {

	if(!Player_Logado(playerid))
		return SendClientMessage(playerid, -1, "Você não está logado !");

	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || GetPVarInt(playerid, "assaltado") == 1)
		return SendClientMessage(playerid, -1, "Você não pode usar este comando agora !");

	if(gettime() < GetPVarInt(playerid, #VarFlood17))
		return SendClientMessage(playerid, COLOR_GRAD, #Você não pode usar este comando com tanta frequencia);
	SetPVarInt(playerid, #VarFlood17, gettime()+2);

	if(IsPlayerCuffed(playerid)){
		return SendClientMessage(playerid, -1, "Você não pode usar este comando agora !");
	}

	new quantia;

	if (sscanf(params, "d", quantia))
		return SendClientMessage(playerid, -1, "Use: /guardargrana [Quantidade]");

	if(quantia < 1000 || quantia > 1000000){
		return SendClientMessage(playerid, -1, "Você pode guardar no mínimo $1.000 e no máximo $1.000.000 !");
	}

	if (isInventoryFull(playerid))
		return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

	if(Player_GetMoney(playerid) < quantia){

		return SendClientMessage(playerid, -1, "Você não tem toda essa grana !");
	}

	new string[75];
	format(string, sizeof string, "%s guardou $%d", PlayerName[playerid], quantia);
	server_log("dinheiro", string);

	givePlayerItem(playerid, ITEM_TYPE_DINHEIRO, 1212, quantia, "Dinheiro");

	Player_RemoveMoney(playerid, quantia);
	format(string, sizeof string, "Você guardou $%s", getFormatText(quantia));
	SendClientMessage(playerid, COLOR_GREY, string);
	return 1;
}
alias:guardargrana("ggrana", "guardardinheiro")

CMD:largarexplosivo(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;

	if(gettime() < GetPVarInt(playerid, #VarFlood17))
		return SendClientMessage(playerid, COLOR_GRAD, #Você não pode usar este comando com tanta frequencia);
	SetPVarInt(playerid, #VarFlood17, gettime()+5);

	if(IsPlayerCuffed(playerid)){

		return SendClientMessage(playerid, -1, "Você não pode usar este comando agora !");
	}

	if(PlayerInfo[playerid][pExplosives]){

		dropItem(playerid, ITEM_TYPE_EXPLOSIVO, 1654, 1, "Explosivo");

		PlayerInfo[playerid][pExplosives] = 0;

		RemovePlayerAttachedObject(playerid, Slot_Explosivo);

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

		new buffer[85];

		SendClientMessage(playerid, 0x33AA3300, "Você largou um(a) Explosivo.");

		format(buffer, sizeof(buffer), "*%s colocou um(a) Explosivo no chão.", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, buffer, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	}
	else SendClientMessage(playerid, -1, "Você não tem um explosivo !");
	return 1;
}

CMD:equipargang(playerid)
{
	if (!PlayerIsGang(playerid)) return SendClientMessage(playerid, -1, "Você precisa ser de uma gang para equipar na Van.");

	new vPlayerVehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || GetVehicleModel(vPlayerVehicle) != 482)
		return SendClientMessage(playerid, -1, "Você precisa estar em uma Van para equipar.");

	if (gettime() < vanEquipamentosTime[vPlayerVehicle])
		return SendClientMessage(playerid, -1, "Alguém ja equipou recentemente nessa Van, aguarde 1 minuto !");

	if (vanEquipamentos[vPlayerVehicle] == GetPlayerOrg(playerid))
	{
		new string[80];
		format(string, sizeof(string), "%s equipou-se na Van dos %s", PlayerName[playerid], GetOrgName(GetPlayerOrg(playerid)));
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		weaponsOrganizacao(playerid, GetPlayerOrg(playerid));

		vanEquipamentosTime[vPlayerVehicle] = gettime() + 60;
	}
	else SendClientMessage(playerid, GetPlayerColor(playerid), " Essa Van não pertence a sua Gang !");

	return 1;
}

CMD:equiparmerce(playerid)
{
	if (!PlayerIsMercenario(playerid)) return SendClientMessage(playerid, -1, "Você precisa ser de mercenário para equipar nessa Van.");

	new vPlayerVehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "Você precisa estar em uma Van para equipar.");

	if (gettime() < vanEquipamentosTime[vPlayerVehicle])
		return SendClientMessage(playerid, -1, "Alguém ja equipou recentemente nessa Van, aguarde 1 minuto !");

	if (vanEquipamentos[vPlayerVehicle] == GetPlayerOrg(playerid))
	{
		new string[80];
		format(string, sizeof(string), "%s equipou-se na Van dos %s", PlayerName[playerid], GetOrgName(GetPlayerOrg(playerid)));
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		weaponsOrganizacao(playerid, GetPlayerOrg(playerid));

		vanEquipamentosTime[vPlayerVehicle] = gettime() + 60;
	}
	else SendClientMessage(playerid, GetPlayerColor(playerid), "Esse veículo não é uma Van ou não pertence a sua organização");

	return 1;
}

CMD:equipar(playerid, const params[])
{
	if (PlayerToPoint(1.5, playerid, -27.5506, 40.9372, 1000.2366)) { // Interior do Enforce
		weaponsOrganizacao(playerid, GetPlayerOrg(playerid));
	}
	return true;
}

CMD:repararvip(playerid, params[])
{
	if(PlayerInfo[playerid][pVIP] > 1 || Admin_GetNivel(playerid) >= SUPERVISOR)
	{
		new string[128];
		if(!IsPlayerInAnyVehicle(playerid))
			return SendClientMessage(playerid, -1, "Você não está em um veículo !");

		if(IsABombCar(GetPlayerVehicleID(playerid)))
			return SendClientMessage(playerid, -1, "Você não pode reparar um veículo de guerra!");

		if (gettime() < GetPVarInt(playerid, "varFloodReparar")) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, " Aguarde um pouco para reparar novamente...");
		}
		SetPVarInt(playerid, "varFloodReparar", gettime() + 60);

		format(string, sizeof(string), "[VIP/SÓCIO] %s arrumou seu veículo", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		RepairVehicle(GetPlayerVehicleID(playerid));
		return true;
	}
	else
	{
		SendClientMessage(playerid, COLOR_LIGHTRED, "Você não é Sócio Premium");
		return true;
	}
}
alias:repararvip("repvip")

CMD:abastecervip(playerid, params[])
{
	if(PlayerInfo[playerid][pVIP] > 1 || Admin_GetNivel(playerid))
	{
		new string[128];
		if(!IsPlayerInAnyVehicle(playerid))
			return SendClientMessage(playerid, -1, "Você não está em um veículo !");

		if (gettime() < GetPVarInt(playerid, "varFloodAbastecer") && !Admin_GetNivel(playerid)) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, " Aguarde um pouco para reparar novamente...");
		}

		format(string, sizeof(string), "[%s] %s abasteceu seu veículo", Admin_GetNivel(playerid) ? ("ADMIN") : ("VIP/SÓCIO"), PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		SetPVarInt(playerid, "varFloodAbastecer", gettime() + 300);

		VehicleInfo[GetPlayerVehicleID(playerid)][vehicleCombustivel] = 100;
		return true;
	}
	else
	{
		SendClientMessage(playerid, COLOR_LIGHTRED, "Você não é Sócio Premium");
		return true;
	}
}
alias:abastecervip("absvip")

new Timer:timerCocaina[MAX_PLAYERS];
timer EfeitoCocaina[1000](playerid) {
	if(GetPVarInt(playerid, "TimeCocaina") < gettime()) {
		SetPVarInt(playerid, "EfeitoCocaina", 0);
		stop timerCocaina[playerid];
	}
	else {
		new Float:health;
		GetPlayerHealth(playerid, health);
		SetPlayerHealth(playerid, health - 0.5);
	}
}


CMD:usardrogas(playerid, params[])
{
	if (isnull(params)) {
		SendClientMessage(playerid, -1, "|______________[ Uso de Drogas ]______________|");
		SendClientMessage(playerid, -1, "Use: /usardrogas [nome] (maconha, crack, cocaina, heroina, metanfetamina)");
		return true;
	}

	if (IsPlayerInCombat(playerid))
		return SendClientMessage(playerid, -1, "Você só poderá equipar 1 minuto após tomar dano de alguém!");

	new string[128];
	if(strcmp(params,"maconha",true) == 0)
	{
		if (GetPlayerItemTypeAmount(playerid, ITEM_TYPE_MACONHA) < 3)
			return SendClientMessage(playerid, -1, "Você não tem 3 gramas de maconha suficiente para usar!");
		else if(GetPVarInt(playerid, "EfeitoMaconha") && GetPVarInt(playerid, "TimeMaconha")-gettime() > 360)
			return SendClientMessage(playerid, -1, "Você já está muito drogado... aguarde um pouco.");
		else if(!PlayerInfo[playerid][pIsqueiro])
			return SendClientMessage(playerid, -1, "Você não tem um Isqueiro, compre um na 24/7!");

		defer fadeOut_Timer(playerid);
		fadeIn(playerid, 800, 0xAAAAAAAA);

		GameTextForPlayer(playerid,"~w~Voce esta~n~~p~chapado",4000,1);
		RemovePlayerItemTypeAmount(playerid, ITEM_TYPE_MACONHA, 3);

		format(string, sizeof(string), "* %s está fumando maconha", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		if(GetPVarInt(playerid, "EfeitoMaconha"))
			SetPVarInt(playerid, "TimeMaconha", GetPVarInt(playerid, "TimeMaconha") + 30);
		else
			SetPVarInt(playerid, "TimeMaconha", gettime() + 30);

		SetPVarInt(playerid, "EfeitoMaconha", 1);
		CONFIG_DrugSystem(playerid, 0, true);

		new timeInfo[16];
		format(timeInfo, 16, "%s", ConvertTime(GetPVarInt(playerid, "TimeMaconha") - gettime()));
		PlayerTextDrawSetString(playerid, _drugs_playertextdraw[0][playerid], timeInfo);

		// Cigarrinho
		ApplyAnimation(playerid, "SMOKING", "M_smk_drag", 4.1, false, false, false, false, TIME_SMOKE_PUFF, SYNC_NONE);
	}
	else if(strcmp(params,"cocaina",true) == 0)
	{
		if (GetPlayerItemTypeAmount(playerid, ITEM_TYPE_COCAINA) < 9)
			return SendClientMessage(playerid, -1, "Você não tem 9 gramas de cocaína suficiente para usar!");
		else if(GetPVarInt(playerid, "EfeitoCocaina") && GetPVarInt(playerid, "TimeCocaina")-gettime() > 360)
			return SendClientMessage(playerid, -1, "Você já está muito drogado... aguarde um pouco.");

		defer fadeOut_Timer(playerid);
		fadeIn(playerid, 800, 0xAAAAAAAA);

		GameTextForPlayer(playerid,"~w~Voce esta~n~~p~ligadao",4000,1);
		RemovePlayerItemTypeAmount(playerid, ITEM_TYPE_COCAINA, 9);

		format(string, sizeof(string), "* %s está cheirando cocaína", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		if(GetPVarInt(playerid, "EfeitoCocaina"))
			SetPVarInt(playerid, "TimeCocaina", GetPVarInt(playerid, "TimeCocaina") + 30);
		else {
			SetPVarInt(playerid, "TimeCocaina", gettime() + 30);
			timerCocaina[playerid] = repeat EfeitoCocaina(playerid);
		}

		SetPVarInt(playerid, "EfeitoCocaina", 1);
		CONFIG_DrugSystem(playerid, 1, true);

		new timeInfo[16];
		format(timeInfo, 16, "%s", ConvertTime(GetPVarInt(playerid, "TimeCocaina") - gettime()));
		PlayerTextDrawSetString(playerid, _drugs_playertextdraw[1][playerid], timeInfo);

		// Cigarrinho
		ApplyAnimation(playerid, "SMOKING", "M_smk_drag", 4.1, false, false, false, false, TIME_SMOKE_PUFF, SYNC_NONE);
	}
	else if(strcmp(params,"crack",true) == 0)
	{
		if (GetPlayerItemTypeAmount(playerid, ITEM_TYPE_CRACK) < 15)
			return SendClientMessage(playerid, -1, "Você não tem 15 gramas de crack suficiente para usar!");
		else if(GetPVarInt(playerid, "EfeitoCrack") && GetPVarInt(playerid, "TimeCrack")-gettime() > 360)
			return SendClientMessage(playerid, -1, "Você já está muito drogado... aguarde um pouco.");

		defer fadeOut_Timer(playerid);
		fadeIn(playerid, 800, 0xAAAAAAAA);

		GameTextForPlayer(playerid,"~w~Voce esta~n~~p~estralado",4000,1);
		RemovePlayerItemTypeAmount(playerid, ITEM_TYPE_CRACK, 15);

		format(string, sizeof(string), "* %s está fumando crack", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		if(GetPVarInt(playerid, "EfeitoCrack"))
			SetPVarInt(playerid, "TimeCrack", GetPVarInt(playerid, "TimeCrack") + 40);
		else
			SetPVarInt(playerid, "TimeCrack", gettime() + 40);

		SetPVarInt(playerid, "EfeitoCrack", 1);
		SetPVarInt(playerid, "LimiteCrack", 1 + random(3));
		CONFIG_DrugSystem(playerid, 2, true);

		new timeInfo[16];
		format(timeInfo, 16, "%s", ConvertTime(GetPVarInt(playerid, "TimeCrack")  - gettime()));
		PlayerTextDrawSetString(playerid, _drugs_playertextdraw[2][playerid], timeInfo);

		// Cigarrinho
		ApplyAnimation(playerid, "SMOKING", "M_smk_drag", 4.1, false, false, false, false, TIME_SMOKE_PUFF, SYNC_NONE);
	}
	else if(strcmp(params,"heroina",true) == 0)
	{
		if (GetPlayerItemTypeAmount(playerid, ITEM_TYPE_HEROINA) < 10)
			return SendClientMessage(playerid, -1, "Você não tem 10 gramas de heroína suficiente para usar!");
		else if(GetPVarInt(playerid, "EfeitoHeroina") && GetPVarInt(playerid, "TimeHeroina")-gettime() > 360)
			return SendClientMessage(playerid, -1, "Você já está muito drogado... aguarde um pouco.");

		defer fadeOut_Timer(playerid);
		fadeIn(playerid, 800, 0xAAAAAAAA);

		GameTextForPlayer(playerid,"~w~Voce esta~n~~p~estralado",4000,1);
		RemovePlayerItemTypeAmount(playerid, ITEM_TYPE_HEROINA, 10);

		format(string, sizeof(string), "* %s está fumando heroína", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		if(GetPVarInt(playerid, "EfeitoHeroina"))
			SetPVarInt(playerid, "TimeHeroina", GetPVarInt(playerid, "TimeHeroina") + 120);
		else
			SetPVarInt(playerid, "TimeHeroina", gettime() + 120);

		SetPVarInt(playerid, "EfeitoHeroina", 1);
		CONFIG_DrugSystem(playerid, 3, true);

		new timeInfo[16];
		format(timeInfo, 16, "%s", ConvertTime(GetPVarInt(playerid, "TimeHeroina")  - gettime()));
		PlayerTextDrawSetString(playerid, _drugs_playertextdraw[2][playerid], timeInfo);

		foreach(new i : Player)
		{
			ShowPlayerNameTagForPlayer(i, playerid, false);
		}
		SetPlayerSeeNick(playerid, false);

		// Cigarrinho
		ApplyAnimation(playerid, "SMOKING", "M_smk_drag", 4.1, false, false, false, false, TIME_SMOKE_PUFF, SYNC_NONE);
	}
	else if(strcmp(params,"metanfetamina",true) == 0)
	{
		if (GetPlayerItemTypeAmount(playerid, ITEM_TYPE_METANFETAMINA) < 12)
			return SendClientMessage(playerid, -1, "Você não tem 12 gramas de metanfetamina suficiente para usar!");
		else if(GetPVarInt(playerid, "EfeitoMetanfetamina") && GetPVarInt(playerid, "TimeMetanfetamina")-gettime() > 360)
			return SendClientMessage(playerid, -1, "Você já está muito drogado... aguarde um pouco.");

		defer fadeOut_Timer(playerid);
		fadeIn(playerid, 800, 0xAAAAAAAA);

		GameTextForPlayer(playerid,"~w~Voce esta~n~~p~drogado",4000,1);
		RemovePlayerItemTypeAmount(playerid, ITEM_TYPE_METANFETAMINA, 12);

		format(string, sizeof(string), "* %s está fumando metanfetamina", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

		if(GetPVarInt(playerid, "EfeitoMetanfetamina"))
			SetPVarInt(playerid, "TimeMetanfetamina", GetPVarInt(playerid, "TimeMetanfetamina") + 60);
		else
			SetPVarInt(playerid, "TimeMetanfetamina", gettime() + 60);

		SetPVarInt(playerid, "EfeitoMetanfetamina", 1);
		CONFIG_DrugSystem(playerid, 4, true);

		new timeInfo[16];
		format(timeInfo, 16, "%s", ConvertTime(GetPVarInt(playerid, "TimeMetanfetamina")  - gettime()));
		PlayerTextDrawSetString(playerid, _drugs_playertextdraw[2][playerid], timeInfo);

		// Cigarrinho
		ApplyAnimation(playerid, "SMOKING", "M_smk_drag", 4.1, false, false, false, false, TIME_SMOKE_PUFF, SYNC_NONE);
	}
	return true;
}

CMD:chave(playerid, params[]) {
	SendClientMessage(playerid, -1, "Use /casa chave para abrir/fechar sua casa.");
	SendClientMessage(playerid, -1, "Use /fazenda chave para abrir/fechar sua fazenda.");
	return true;
}

CMD:dado(playerid, params[])
{
	new dice = random(6)+1;

	if ( gDice[playerid] == 1 ) {

		new string[71];

		format(string, sizeof(string), "* %s jogou um dado e caiu no número: {FF0000}%d", PlayerName[playerid], dice);
		SendClientMessageInRange(10.0, playerid, string, 0xFFE4E1FF, 0xFFE4E1FF, 0xFFE4E1FF, 0xFFE4E1FF, 0xFFE4E1FF);

		PlayerPlaySound(playerid, 33401, 0.0, 0.0, 0.0);
		Sound(playerid, 33401, 15.0);
	}
	else
	{
		SendClientMessage(playerid, -1, "	Você não possui dado, compre em um Mercado 24/7 (use: /gps » Comércios).");
		return true;
	}
	return 1;
}

//----------------------------------[Skin]-----------------------------------------------
CMD:meuskin(playerid, const params[])
{
    if (PlayerToPoint(3.0, playerid, 210.4596,-100.4582,1005.2578)
	|| PlayerToPoint(3.0, playerid, 161.5581,-83.5712,1001.8047)
	|| PlayerToPoint(3.0, playerid, 202.4701,-136.1887,1002.8744) 
	|| PlayerToPoint(3.0, playerid, 206.3915,-9.2168,1001.2109) 
	|| PlayerToPoint(3.0, playerid, 204.3578,-159.3506,1000.5234))
	{
		new loja = properties[currentInt[playerid]][eUniqIntId], valor = 800000, skinList = mS_INVALID_LISTID;
		if(loja == 80)  // Binco 
			valor = 9000, skinList = SkinsListBinco;
		else if(loja == 53) // ZIP
			valor = 16000, skinList = SkinsListZip;
		else if(loja == 25) // Victim
			valor = 18000, skinList = SkinsListVictim;
		else if(loja == 33) // SubUrban
			valor = 12000, skinList = SkinsListSuburban;
		else if(loja == 61) // Didier-Sachs
			valor = 80000, skinList = SkinsListDS;
		else if(loja == 16) // Pro Laps
			valor = 28000, skinList = SkinsListPL;

		if (Player_GetMoney(playerid) < valor) 
			return SendMsgF(playerid, -1, "Você não tem $%d para comprar alguma roupa nesta loja.", valor);

		SetPVarInt(playerid, "skinList", skinList);
		SetPVarInt(playerid, "skinValor", valor);

		ShowModelSelectionMenu(playerid, skinList, "Escolha sua skin", 200, 0x000000AA);
		SendMsgF(playerid, COLOR_YELLOW, "Atendente: Por favor, escolha a skin desejada! Valor: $%s", getFormatText(valor));
   	}
	else SendClientMessage(playerid, -1, "Você não está no balcão de uma loja de roupas.");

	return true;
}

public OnPlayerModelSelection(playerid, response, listid, modelid)
{
	new string[128];

	if (listid == GetPVarInt(playerid, "skinList"))
	{
		if (!response) return SendClientMessage(playerid, -1, "Você cancelou o menu de skins.");

		if (isInventoryFull(playerid))
			return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

		new valor = GetPVarInt(playerid, "skinValor");
		format(string, sizeof(string), "Você comprou uma nova skin por $%s. A roupa está no seu inventário, coloque-a quando quiser!",
			getFormatText(valor));
		SendClientMessage(playerid, COLOR_ORANGE, string);

		Player_RemoveMoney(playerid, valor);
		DepositPropertie(playerid, PagarICMS(valor));

		format(string, sizeof string, "Skin %d", modelid);
		givePlayerItem(playerid, ITEM_TYPE_SKIN, modelid, 1, string);

		format(string, sizeof string, "Voce comprou a %s por ~g~~h~$%s~w~, ela foi guardada em seu inventario", string, getFormatText(valor));
		ShowPlayerBaloonInfo(playerid, string, 5000);

		ServerLog::("skins", "%s comprou a Skin %d por $%d", PlayerName[playerid], modelid, valor);
	}
	else if (listid == SkinsCopsList || listid == SkinsCopListSimple)
	{
	    if (!response) return SendClientMessage(playerid, -1, "Você cancelou o menu de uniformes.");

		new playerOrg = GetPlayerOrg(playerid);

        PlayerInfo[playerid][pSkinServico] = modelid;
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkinServico]);

		format(string, sizeof(string), "<< %s: %s %s vestiu sua farda. >>", GetOrgName(playerOrg), GetPlayerCargo(playerid), PlayerName[playerid]);
		SendCopMessageAll(0xFF8282AA, string);

		OnDuty[playerid] = 1;
		EmpregoDuty[playerid] = 2;

		SetPlayerToTeamColor(playerid);
	}
	else if(listid == CarrosFamilyList)
	{
	    if (response) {

	        new id = GetPlayerFamily( playerid );

	        if (IsPlayerOwnerFamily( playerid, id )) {

                new idCar = GetPVarInt(playerid, "familyCar");
				new Float:x, Float:y, Float:z, Float:ang;

				GetPlayerPos(playerid, x, y, z);
				GetPlayerFacingAngle(playerid, ang);

			    if (GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0) {
       				return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode comprar um carro agora!");
			    }

			    if (!IsPlayerInRangeOfFamily( playerid, id )) {
			        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está perto da HQ da sua família!");
			    }

	            if (familyVehInfo[id][idCar][familyVehModel] != 0) {

				    if (familyInfo[id][familyMoney] < 100000) {
				        return SendClientMessage(playerid, COLOR_LIGHTRED, "* A família não possui $100.000 para trocar de carro!");
				    }

					Family_SetVehicle(id, idCar, modelid, x, y, z, ang);

					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você trocou um carro da família por $100.000!");

					familyInfo[id][familyMoney] -= 100000;

	            } else {

				    if (familyInfo[id][familyMoney] < 5000000) {
				        return SendClientMessage(playerid, COLOR_LIGHTRED, "* A família não possui $5.000.000 para comprar este carro!");
				    }

					Family_SetVehicle(id, idCar, modelid, x, y, z, ang);

					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você comprou um carro para a família por $5.000.000!");

					familyInfo[id][familyMoney] -= 5000000;
				}
	        } else {

	        }
	    }
		else SendClientMessage(playerid, -1, " Você fechou o menu de carros!");
	}
	else if(listid == CapaceteList) {

	    if (response) {

			if (IsPlayerHaveItem(playerid, ITEM_TYPE_CAPACETE))
				return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você já tem um Capacete em seu inventário!");

			if (Player_GetMoney(playerid) < 100)
				return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode pagar pelo capacete !");

			Player_RemoveMoney(playerid, 100);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
            SendClientMessage(playerid, COLOR_GRAD, "Capacete comprado, você agora pode pilotar motocicletas sem correr o risco de ser multado!");
            givePlayerItem(playerid, ITEM_TYPE_CAPACETE, modelid, 1, "Capacete");
    		format(string, sizeof(string), "~r~-$%d", 100);
		    GameTextForPlayer(playerid, string, 5000, 1);

		    DepositPropertie(playerid, 100);
	    } else {

	    }
	}
	return 1;
}

CMD:reforco(playerid)
{
    if (!GetPlayerOrg(playerid)) return SendClientMessage(playerid, -1, "Você não é membro de uma organização.");

	new string[129], org = GetPlayerOrg(playerid);

	SendMembersMessage(org, 0xCC66FFFF, "|----------------------------------------------------------------------------------------------------------------|");
	format(string, sizeof string,      "| ATENÇÃO: %s está precisando de reforço, USE: (/aceitar reforco)", PlayerName[playerid]);
	SendMembersMessage(org, 0xCC66FFFF, string);
	SendMembersMessage(org, 0xCC66FFFF, "| O reforço será cancelado em 2 minutos!");
	SendMembersMessage(org, 0xCC66FFFF, "|----------------------------------------------------------------------------------------------------------------|");

	GetPlayerPos(playerid, irReforco[org][0], irReforco[org][1], irReforco[org][2]);
	irReforco[org][3] = gettime() + 120;

	return true;
}

CMD:meucontrato(playerid)
{
    new string[72];

    new id = GoChase[playerid];

    if (!IsPlayerConnected(id))
        return SendClientMessage(playerid, -1, "	Você não possui um contrato.");

 	if(GetPlayerOrg(playerid) == 8) {
	    format(string, sizeof(string), "Meu contrato: %s(%d) - valor: $%s e %d respeitos.", PlayerName[id], id, getFormatText(PlayerInfo[id][pHeadValue]), PlayerInfo[id][pHeadRespect]);
  		SendClientMessage(playerid, COLOR_GRAD, string);
	}
	if(GetPlayerOrg(playerid) == 22) {
	    format(string, sizeof(string), "Meu contrato: %s(%d) - valor: $%s e %d respeitos.", PlayerName[id], id, getFormatText(PlayerInfo[id][pHeadValueT]), PlayerInfo[id][pHeadRespectT]);
  		SendClientMessage(playerid, COLOR_GRAD, string);
	}
	return true;
}
alias:meucontrato("mcont")

CMD:largarcontrato(playerid, const params[])
{
    new result[20],
		string[121];

	if(sscanf(params, "s[20]", result)) {
		return SendClientMessage(playerid, -1, "Use: /largarcontrato [motivo]");
	}

	if ( strlen(result) < 3 || strlen(result) > 20 ) {
		return SendClientMessage(playerid, -1, "O motivo deve conter de 3 a 20 caracteres!");
	}

    if (IsPlayerInCombat(playerid)) return SendClientMessage(playerid, -1, "Você não pode usar esse comando em um combate.");

    if (GoChase[playerid] == INVALID_PLAYER_ID) {
        return SendClientMessage(playerid, -1, "	Você não possui um contrato.");

 	} else {

		if(GetPlayerOrg(playerid) == 8) {
		    format(string, sizeof string, "<< Hitman, %s, largou seu contrato em: %s - motivo: %s >>", PlayerName[playerid], PlayerName[GoChase[playerid]], (result));
		    SendMembersMessage(8, 0xD86248FF, string);
		    GotHit[GoChase[playerid]] = 0;
		}
		if(GetPlayerOrg(playerid) == 22) {
		    format(string, sizeof string, "<< Triad, %s, largou seu contrato em: %s - motivo: %s >>", PlayerName[playerid], PlayerName[GoChase[playerid]], (result));
		    SendMembersMessage(22, 0xD86248FF, string);
		    GotTri[GoChase[playerid]] = 0;
		}
		GetChased[GoChase[playerid]] = INVALID_PLAYER_ID;
		GoChase[playerid] = INVALID_PLAYER_ID;
	}
	return true;
}
alias:largarcontrato("lcontrato", "lcont")

CMD:infocontrato(playerid, params[])
{
	new string[92];

	new idplayer;
	if(sscanf(params, "u", idplayer)) {
	    return SendClientMessage(playerid, -1, "Use: /infocontrato [playerid]");
	}

    if (!Admin_GetNivel(playerid)) {
		return SendClientMessage(playerid, -1, "Você não tem autorização para usar esse comando.");
	}

	if(GoChase[idplayer] == INVALID_PLAYER_ID) {
		return SendClientMessage(playerid, COLOR_GRAD, "** Este assassino não possui um contrato ativo.");
	} else {
	    format(string, sizeof(string), "** Assassino %s, está com contrato em: %s[%d].", PlayerName[idplayer], PlayerName[GoChase[idplayer]], GoChase[idplayer]);
		SendClientMessage(playerid, COLOR_GRAD, string);
	}
	return true;
}

CALLBACK: desarmarLaser(playerid)
{
	SetPVarInt(playerid, "desarmandoLasers", 0);

    if (!IsPlayerConnected(playerid) || !IsPlayerInRangeOfPoint(playerid, 2.0, 2146.8528,1612.1110,835.0683)) {

        SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está no painel de lasers !");
    	ClearAnimations(playerid);
    	RemovePlayerAttachedObject(playerid, Slot_Explosivo);
        return 1;
    }

    ClearAnimations(playerid);
    RemovePlayerAttachedObject(playerid, Slot_Explosivo);

    new id = GetPVarInt(playerid, "propId");
    new randomSucess = random(80);

    if (randomSucess < PlayerInfo[playerid][pFerSkill]) {
        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Você conseguiu desarmar os lasers, ele ficará desativado por 5 minutos, aproveite o tempo que resta!");

        DestroyPropertyeLasers( id );

		if (PlayerInfo[playerid][pFerSkill] < 40) {
		    PlayerInfo[playerid][pFerSkill] ++;
		    SendClientMessage(playerid, COLOR_YELLOW, "Você ganhou +1 ponto de habilidade com ferramentas, use /habilidades 9.");
		}

	} else {

 		if (!PropInfo[id][eAlarm]) {

			new string[128];
			format(string, sizeof string, "[Assalto ao Cofre]: %s e %s %s estão tentando roubar o cofre da empresa %s [%d]", PlayerName[playerid], GetOrgArticle(GetPlayerOrg(playerid)), GetOrgName(GetPlayerOrg(playerid)), PropInfo[id][ePname], id);
			SendClientMessageToAll(COLOR_LIGHTRED, string);
			SetPlayerCriminal(playerid, 255, "Assalto ao cofre");

            FireAlarmPropertie( id );
		}
		SendClientMessage(playerid, COLOR_LIGHTRED, "* Você cortou o fio errado e o alarme disparou, os policiais foram avisados do roubo e estão a caminho !");
    }

    return 1;
}

CMD:pegargrana(playerid) {
    new id = GetPlayerCofreProp( playerid );

	if (id >= 81)
		return SendClientMessage(playerid, COLOR_LIGHTRED, "Essa propriedade está com BUGs é impossível rouba-la.");

    if ( id != -1 ) {

        if ( !IsAMember(playerid) ) {
            return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode roubar uma empresa !");
        }

        if ( IsPlayerOwnerPropertie( playerid, id )) {
            return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode roubar sua própria empresa !");
        }
        if(gettime() < PlayerInfo[playerid][pRoubou]) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você já pegou dinheiro de algum cofre recentemente, aguarde 5 minutos para poder pegar mais !");
		}

        if ( GetPVarInt(playerid, "pegandoGrana") ) {
            return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você já está roubando !");
        }

        SetPVarInt(playerid, "pegandoGrana", 1);
		ApplyAnimation(playerid,"ROB_BANK","CAT_Safe_Rob", 4.1, true, false, false, false, 0);
	    SetTimerEx(#ApplyAnim, 500, false, "i", playerid);
	    SetPlayerAttachedObject(playerid, Slot_Explosivo, 1550,1,-0.068000,0.382000,-0.109999,-91.699996,101.200012,-149.300003,1.000000,1.000000,1.000000);
		SetTimerEx("pegarGranaCofre", 70000, false, "ii", playerid, id);

    } else {
        SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está perto do dinheiro do cofre de nenhuma empresa !");
    }

    return 1;
}

CALLBACK: pegarGranaCofre( playerid, id ) {

    SetPVarInt(playerid, "pegandoGrana", 0);
 	if ( !IsPlayerConnected(playerid) || GetPlayerCofreProp( playerid ) != id) {

    	ClearAnimations(playerid);
    	RemovePlayerAttachedObject(playerid, Slot_Explosivo);

		return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não está no cofre da empresa que estava roubando !");
	}

	new value = PropInfo[id][eTill] / (12 - (random(3)));

	if (PropInfo[id][eTill] > value) {
	    PropInfo[id][eTill] -= value;
	} else {
	    value = PropInfo[id][eTill];
	    PropInfo[id][eTill] = 0;
	}

    PlayerInfo[playerid][pRoubou] = gettime() + (5 * 60);
	Player_AddMoney(playerid, value);

    new string[128];
    format(string, sizeof string, "* Você pegou uma bolsa com $%s do cofre, agora saia o mais rápido possível, pois a polícia foi avisada !", getFormatText(value));
    SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

   	ClearAnimations(playerid);
   	SetPlayerAttachedObject(playerid, Slot_Explosivo, 1550, 1, 0.000000, -0.313611, 0.021003, 0.445490, 86.754409, 355.370239, 0.926815, 1.000000, 1.000000);

    atualizarPropText( id );
    savePropertie( id );

    return 1;
}

CALLBACK:DealWithPlayerInPosition(playerid) 
{
	return 1;
}

CMD:enterexit(playerid, const params[])
{
	if (gettime() < GetPVarInt(playerid, "enterInteriorFlood")) return true;

	SetPVarInt(playerid, "enterInteriorFlood", gettime() + 1);
	SetPVarString(playerid, "NomeLocal", "Nenhum");

	House_PlayerEntry(playerid);

	// Cativeiros para sequestradores
	if (PlayerToPoint(1.0, playerid, 2919.8228,2117.9873,17.8955))     // Entrada do Cativeiro I
	{
		SetPlayerPos(playerid, 2542.0439,-1303.9512,1025.0703);
		SetPlayerInterior(playerid, 2);
		SetPlayerVirtualWorld(playerid, 1001);
		SetPVarString(playerid, "NomeLocal", "Cativeiro I");
	}
	else if (PlayerToPoint(1.0, playerid, 2811.0066,2919.7876,36.5046))     // Entrada do Cativeiro II
	{
		SetPlayerPos(playerid, 2542.0439,-1303.9512,1025.0703);
		SetPlayerInterior(playerid, 2);
		SetPlayerVirtualWorld(playerid, 1002);
		SetPVarString(playerid, "NomeLocal", "Cativeiro II");
	}
	else if (PlayerToPoint(1.0, playerid, 2007.0468,2910.1699,47.8231))     // Entrada do Cativeiro III
	{
		SetPlayerPos(playerid, 2542.0439,-1303.9512,1025.0703);
		SetPlayerInterior(playerid, 2);
		SetPlayerVirtualWorld(playerid, 1003);
		SetPVarString(playerid, "NomeLocal", "Cativeiro III");
	}
	else if (PlayerToPoint(1, playerid, 2542.0439,-1303.9512,1025.0703))       // Saida dos Cativeiros
	{
	    if (GetPlayerVirtualWorld(playerid) == 1001) SetPlayerPos(playerid, 2919.8228,2117.9873,17.8955);
	    else if (GetPlayerVirtualWorld(playerid) == 1002) SetPlayerPos(playerid, 2811.0066,2919.7876,36.5046);
	    else if (GetPlayerVirtualWorld(playerid) == 1003) SetPlayerPos(playerid, 2007.0468,2910.1699,47.8231);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
	else if(PlayerToPoint(3.0, playerid,995.5361,-73.5942,22.0867))
	{
		//ENTRADA MINA
		GameTextForPlayer(playerid, "~w~Mina", 5000, 1);
		SetPlayerInterior(playerid, 27);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, 2396.1985, -1506.7729 ,1402.2000);

		ShowLoadingMap(playerid);
	}
	else if(PlayerToPoint(3.0, playerid,2396.1985,-1506.7729,1402.2000))
	{
		//SAIDA MINA
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid,995.5361,-73.5942,22.0867);
	}

#if _inc_paintball_system
	else if (IsPlayerInRangeOfPoint(playerid, 2.5, 2695.5930, -1704.6952, 11.8438)) {
		Paintball_ShowDialog(playerid);
	}
#endif

	new string[128];

	if (GetPlayerBeingAbducted(playerid))
	{
		format(string, sizeof(string), "* O jogador sequestrado: %s, não pode entrar em interiores, apenas Cativeiro.", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		return true;
	}

	if (lastPickup[playerid] != -1)
	{
	    new
  		  	id = propPickups[lastPickup[playerid]],
		   	Float:x,
		   	Float:y,
	      	Float:z
		;

		if (id == 81)
			return 1;

		GetPropertyEntrance(id, x, y, z);
 		if (IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z))
	 	{
			SetPVarInt(playerid, "propId", id);
			ShowPlayerDialog(playerid, 145, DIALOG_STYLE_LIST, "Escolha uma opção", "Entrar na empresa\nEntrar no cofre", "Entrar", "Fechar");
  	    	return 1;
		}
	}

   	if (currentInt[playerid] > -1 && GetPlayerInterior(playerid) == GetPropertyInteriorId(currentInt[playerid]))
	{
       	new
			id = currentInt[playerid],
     		Float:x,
		 	Float:y,
		 	Float:z,
			Float:a
		;

		GetPropertyExit(id, x, y, z);

		if (IsPlayerInRangeOfPoint(playerid,2.0,x,y,z))
		{
			a = GetPropertyEntrance(id, x, y, z);
			SetPlayerPos(playerid, x, y, z);
			SetPlayerFacingAngle(playerid, a);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetCameraBehindPlayer(playerid);
			ShowLoadingMap(playerid);

			currentInt[playerid] = -1;
			GivePlayerTempWeapons(playerid);

			SetPlayerCP(playerid, CP_NULL);
			return 1;
		}
	}
	if (IsPlayerInRangeOfPoint(playerid, 1.5, -26.3874,42.8232,1000.3384)) {

	    if (GetPVarInt(playerid, "playerEnforcer") != INVALID_VEHICLE_ID) {

	        static Float:x, Float:y, Float:z, Float:angul;
	        GetVehiclePos(GetPVarInt(playerid, "playerEnforcer"), x, y, z);
	        GetVehicleZAngle(GetPVarInt(playerid, "playerEnforcer"), angul);
	        SetPlayerInterior(playerid, 0);
	        SetPlayerVirtualWorld(playerid, 0);
	        GetXYInTrasOfPoint(x, y, angul, 4.3);
	        SetPlayerPos(playerid, x, y, z - 0.1);
	        SetPVarInt(playerid, "playerEnforcer", INVALID_VEHICLE_ID);
	    }
	}

	if (PlayerToPoint(1.0, playerid,-26.8017,-89.5741,1003.5469) || PlayerToPoint(1.0, playerid,1394.1488,-24.8331,1000.9177))
	{
        MEGAString[0]=EOS;

		// Header
		strcat(MEGAString, "ID / Nome do Item\tPreço do Item\n");

		// Itens
		strcat(MEGAString, "{FFFFFF}01: Celular 			\t{00AA00}$1.500\n");
		strcat(MEGAString, "{FFFFFF}02: Agenda 				\t{00AA00}$50\n");
		strcat(MEGAString, "{FFFFFF}03: Dado 				\t{00AA00}$30\n");
		strcat(MEGAString, "{FFFFFF}04: Camisinha 			\t{00AA00}$12\n");
		strcat(MEGAString, "{FFFFFF}05: Carne Crua 			\t{00AA00}$50\n");
		strcat(MEGAString, "{FFFFFF}06: Carteira de cigarro \t{00AA00}$15\n");
		strcat(MEGAString, "{FFFFFF}07: Galão de Gasolina 	\t{00AA00}$60\n");
		strcat(MEGAString, "{FFFFFF}08: Isqueiro 			\t{00AA00}$10\n");
		strcat(MEGAString, "{FFFFFF}09: Patins 				\t{00AA00}$80\n");
		strcat(MEGAString, "{FFFFFF}10: JBL 				\t{00AA00}$700\n");
		strcat(MEGAString, "{FFFFFF}11: Chave de Fenda 		\t{00AA00}$180\n");
		strcat(MEGAString, "{FFFFFF}12: Chave Fixa 			\t{00AA00}$180\n");
		strcat(MEGAString, "{FFFFFF}13: Chave Biela 		\t{00AA00}$180\n");
		strcat(MEGAString, "{FFFFFF}14: Notebook 			\t{00AA00}$3.000\n");
		strcat(MEGAString, "{FFFFFF}15: Capacete 			\t{00AA00}$100\n");
		strcat(MEGAString, "{FFFFFF}16: 5 Garrafa d'agua 	\t{00AA00}$150\n");
		strcat(MEGAString, "{FFFFFF}17: Regador de plantas 	\t{00AA00}$100\n");
		strcat(MEGAString, "{FFFFFF}18: Coxa de Frango Crua	\t{00AA00}$20\n");
		strcat(MEGAString, "{FFFFFF}19: 5 Kits de Reparo (veículo)	\t{00AA00}$200\n");

		ShowPlayerDialog(playerid, 6602, DIALOG_STYLE_TABLIST_HEADERS, "Mercado 24/7", MEGAString, "Comprar", "Fechar");
	}
	else if (PlayerToPoint(2.5, playerid,2151.8035,1609.6300,847.6677))
	{
       	new id = GetPVarInt(playerid, "propId");
     	new Float:x;
		new	Float:y;
		new	Float:z;
		new	Float:a;

		GetPropertyExit( id, x, y, z );

		a = GetPropertyEntrance( id, x, y, z );
		SetPlayerPos( playerid, x, y, z );
		SetPlayerFacingAngle( playerid, a );
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld( playerid, 0 );
		currentInt[playerid] = -1;
		PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);

		SetPlayerCP(playerid, CP_NULL);
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.0, 1064.0251, -1754.7593, 13.7404))
	{
	    ShowPlayerDialog(playerid, 131, DIALOG_STYLE_TABLIST_HEADERS, "Menu do Hospital",
	    "{FFFFFF}Produto\t{00AA00}Preço\t{00FFFF}Unidades\t{FFFFFF}Função\n\
		Contrato Hospitalar\t{00AA00}$3000\t1 Unidade(s)\t{AAAAAA}Leva o paciênte até em casa\n\
		Contrato Hospitalar\t{00AA00}$6000\t2 Unidade(s)\t{AAAAAA}Leva o paciênte até em casa\n\
		Contrato Hospitalar\t{00AA00}$15000\t5 Unidade(s)\t{AAAAAA}Leva o paciênte até em casa",
		"Comprar", "Fechar");

		TogglePlayerControllable(playerid, true);
	}
	
    else if(IsPlayerInRangeOfPoint(playerid, 2.0, 941.9362,2176.6089,1011.0234))
    {
        MEGAString[0] = EOS;
        strcat(MEGAString, "Item\tPreço\tDano\n");

		strcat(MEGAString, "Explosivo C4\t{00AA00}$1300\t{FF0000}Morte\n");
		strcat(MEGAString, "Mina Terrestre\t{00AA00}$1400\t{FF0000}Morte\n");
		strcat(MEGAString, "Semente de maconha\t{00AA00}$1090\tN/A\n");
		strcat(MEGAString, "Lata de Spray\t{00AA00}$1020\tN/A\n");
		strcat(MEGAString, "Katana\t{00AA00}$1060\t{FF0000}-21\n");
		strcat(MEGAString, "Caixa de equipamentos P\t{00AA00}$3.000\tN/A\n");
		strcat(MEGAString, "Caixa de equipamentos M\t{00AA00}$5.000\tN/A\n");
		strcat(MEGAString, "Caixa de equipamentos G\t{00AA00}$6.000\tN/A\n");

		ShowPlayerDialog(playerid, 8974, DIALOG_STYLE_TABLIST_HEADERS, " Mercado negro", MEGAString, "Comprar", "Fechar");
	}

  	else if(PlayerToPoint(2, playerid, 2146.64551, 1612.74670, 835.40332))
    {
    	new id = GetPVarInt(playerid, "propId");

    	SetPlayerFaceToPoint(playerid, 2146.64551, 1612.74670);
    	ApplyAnimation(playerid, "HEIST9","Use_SwipeCard", 4.0, false, false, false, false, 0);

    	if (IsPlayerOwnerPropertie( playerid, id )) {

    	    if (PropInfo [id] [eLaser]) {
    	        HideAlarm( id );
    	        DestroyPropertyeLasers( id );
    	        SendClientMessage(playerid, TEAM_BALLAS_COLOR, "* Você desativou os lasers, o sistema reativará automaticamente em 5 minutos !");
    	    } else {
    	        CreatePropertyeLasers( id );
    	        SendClientMessage(playerid, TEAM_BALLAS_COLOR, "* Você ativou os lasers !");
    	    }

    	} else {

            if (PropInfo [id] [eLaser] && IsAMember(playerid)) {

                if (GetPVarInt(playerid, "desarmandoLasers"))
                    return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você já está tentando desativar os lasers !");

				ShowPlayerDialog(playerid, 300, DIALOG_STYLE_MSGBOX, " ",
				"\t{FF3300}ASSALTO AO COFRE DA EMPRESA:\n\n\
				{FFFFFF}O sistema de lasers está ativado. Você pode tentar desarmá-los.\n\
				Para isso você precisará de 3 ferramentas: {AAFFFF}Chave de Fenda, Chave Fixa e Chave Biela.\n\n\
				{FF2200}OBS: {BBBBBB}Se você passar pelos lasers sem desarmá-los, o alarme irá\n\
				disparar e todos serão avisados!", "Desarmar", "Cancelar");
			} else {
			    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o dono do comércio tem a senha para ativar os lasers !");
			}
		}
    }

  	else if(PlayerToPoint(0.8, playerid, 2146.7195,1632.6847,835.1881)) // fora do cofre
    {
    	new id = GetPVarInt(playerid, "propId");

    	SetPlayerFaceToPoint(playerid, 2146.67065, 1633.03381);
    	ApplyAnimation(playerid, "HEIST9","Use_SwipeCard", 4.0, false, false, false, false, 0);

    	if (IsPlayerOwnerPropertie( playerid, id )) {

			if (PropInfo[id][eDoorDestroyed]) {
			    return SendClientMessage(playerid, COLOR_LIGHTRED, "* A porta do cofre está destruida, o seguro irá consertar em alguns minutos !");
			}

			if (PropInfo[id][eDoorOpen]) {
			    ReconstroyPropDoor( id );
			    SendClientMessage(playerid, TEAM_BALLAS_COLOR, "* Você fechou a porta do cofre !");
			} else {
			    OpenPropDoor( id );
			    SendClientMessage(playerid, TEAM_BALLAS_COLOR, "* Você abriu a porta do cofre, ela fechará automaticamente em 1 minuto !");
			}

    	} else {
    	    SendClientMessage(playerid, COLOR_LIGHTRED, "* Apenas o dono do comércio tem a senha para abrir e fechar a porta do cofre !");
    	}
    }

  	else if(PlayerToPoint(0.8, playerid, 2146.6191,1634.0874,835.0760)) // dentro do cofre
    {
    	new id = GetPVarInt(playerid, "propId");

    	SetPlayerFaceToPoint(playerid, 2146.67065, 1633.03381);
    	ApplyAnimation(playerid, "HEIST9","Use_SwipeCard", 4.0, false, false, false, false, 0);

		if (PropInfo[id][eDoorDestroyed]) {
		    return SendClientMessage(playerid, COLOR_LIGHTRED, "* A porta do cofre está destruida, o seguro irá consertar em alguns minutos !");
		}

		if (PropInfo[id][eDoorOpen]) {
		    ReconstroyPropDoor( id );
		    SendClientMessage(playerid, TEAM_BALLAS_COLOR, "* Você fechou a porta do cofre !");
		} else {
		    OpenPropDoor( id );
		    SendClientMessage(playerid, TEAM_BALLAS_COLOR, "* Você abriu a porta do cofre, ela fechará automaticamente em 1 minuto !");
		}
    }

    else if (PlayerToPoint(2, playerid, 1398.5177,1046.8518,10.8203)) // Alugar caminhão
    {
		if (!PlayerIsCaminhoneiro(playerid)) return SendClientMessage(playerid, -1, "Você não é um caminhoneiro.");

		if (PlayerCaminhao[playerid][caminhaoValid]) return SendClientMessage(playerid, -1, "Você já está usando um caminhão.");

		MEGAString[0] = EOS;

		strcat(MEGAString, "Função\tNome do caminhão\tValor\n");

		strcat(MEGAString, "{9C9C9C}Alugar caminhão\t{FFFFFF}Rumpo\t{00AA00}$10\n");
		strcat(MEGAString, "{9C9C9C}Alugar caminhão\t{FFFFFF}Mule\t{00AA00}$20\n");
		strcat(MEGAString, "{9C9C9C}Alugar caminhão\t{FFFFFF}Yankee\t{00AA00}$25\n");
		strcat(MEGAString, "{9C9C9C}Alugar caminhão\t{FFFFFF}Flatbed\t{00AA00}$30\n");

		ShowPlayerDialog(playerid, 451, DIALOG_STYLE_TABLIST_HEADERS, "Menu caminhoneiro", MEGAString, "Alugar", "Cancelar");
    }

	else if (PlayerToPoint(2, playerid, 1426.1326,1090.9473,10.8203)) // Central caminhoneiros
    {
		if (!PlayerIsCaminhoneiro(playerid)) return SendClientMessage(playerid, -1, "Você não é um caminhoneiro.");

		ShowPlayerDialog(playerid, 452, DIALOG_STYLE_LIST, "Menu caminhoneiro", "Propriedades\nFazendas", "Alugar", "Cancelar");
    }

    else if(IsPlayerInRangeOfPoint(playerid, 2.0, 268.4154,77.2977,1001.0391))
    {
        ShowAdvogado(playerid, 1);
    }
    else if(IsPlayerInRangeOfPoint(playerid, 2.0, 198.2904,179.1829,1003.0306) && GetPlayerVirtualWorld(playerid) == 1)
    {
        ShowAdvogado(playerid, 2);
    }
    else if(IsPlayerInRangeOfPoint(playerid, 2.0, 198.2904,179.1829,1003.0306) && GetPlayerVirtualWorld(playerid) == 2)
    {
        ShowAdvogado(playerid, 11);
    }
    else if(IsPlayerInRangeOfPoint(playerid, 2.0, 198.2904,179.1829,1003.0306) && GetPlayerVirtualWorld(playerid) == 3)
    {
        ShowAdvogado(playerid, 16);
    }
    else if(IsPlayerInRangeOfPoint(playerid, 2.0, 219.8365,115.7170,999.0156))
    {
        ShowAdvogado(playerid, 33);
    }
    else if(IsPlayerInRangeOfPoint(playerid, 2.0, 282.3564,1944.4896,1062.0924) && GetPlayerVirtualWorld(playerid) == 99)
    {
        ShowAdvogado(playerid, 24);
    }
	else if(IsPlayerInRangeOfPoint(playerid, 2.0, 289.3872,-136.8302,1004.0741) && GetPlayerVirtualWorld(playerid) == 99)
    {
        ShowSurrenderProposal(playerid);
    }
    else if(IsPlayerInRangeOfPoint(playerid, 1.0, 1130.1991, -1733.0205, 13.8090))
    {
        callcmd::ajustar(playerid);
    }

	else if (PlayerToPoint(15.0, playerid, 1479.1299,-1631.8226,14.7433)) 
		callcmd::caixinha(playerid);

	else if (PlayerToPoint(3.0, playerid, 210.4596,-100.4582,1005.2578)
		|| PlayerToPoint(3.0, playerid, 161.5581,-83.5712,1001.8047)
		|| PlayerToPoint(3.0, playerid, 202.4701,-136.1887,1002.8744) 
		|| PlayerToPoint(3.0, playerid, 206.3915,-9.2168,1001.2109) 
		|| PlayerToPoint(3.0, playerid, 204.3578,-159.3506,1000.5234))
	{
		callcmd::meuskin(playerid, #);
	}
	else if (PlayerToPoint(2, playerid, -2033.3137,-117.4329,1035.1719))
	{
		callcmd::licencas(playerid, #);
	}
    else if(IsPlayerInRangeOfPoint(playerid, 2.0, 768.2192,-3.9873,1000.7203))
	{
		ShowPlayerDialog(playerid, 1389, DIALOG_STYLE_LIST, "Estilos De Luta", "Cotoveladas\nBoxe\nRua\nKickBoxing\nKarate\nNormal", "confirma", "Cancela");
	}
	else if (PlayerToPoint(2.0, playerid, 1524.4977,-1677.9469,6.2188) ||PlayerToPoint(2.0, playerid, 1565.1235,-1666.9944,28.3956) || PlayerToPoint(2.0, playerid, 246.4990, 88.0087, 1003.6406) || PlayerToPoint(2.0, playerid, 1565.1235,-1666.9944,28.3956))
	{
	    if (!IsACop(playerid)) return true;

	    TogglePlayerControllable(playerid, true);
		ShowPlayerDialog(playerid, 2585, DIALOG_STYLE_LIST, "Elevador Policial", "Garagem\nDepartamento\nTelhado", "Confirma", "Cancela");
	}
	else if(PlayerToPoint(1, playerid, 1130.3765,-2043.4714,69.0078))
	{
        OrgCofre[playerid] = 11;
        TogglePlayerControllable(playerid, true);

		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, -1341.9978,496.3586,11.1953))
	{
        OrgCofre[playerid] = 3;
        TogglePlayerControllable(playerid, true);

		ShowDialogCofreOrg(playerid);
	}
	else if (PlayerToPoint(1, playerid, 324.0125,-1518.6938,36.0325))
	{
		OrgCofre[playerid] = 2;
		TogglePlayerControllable(playerid, true);

		ShowDialogCofreOrg(playerid);
	}
	else if (PlayerToPoint(1, playerid, -55.8733, -300.6442, 5.4297))
	{
		OrgCofre[playerid] = 34, TogglePlayerControllable(playerid, true);
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 1568.6442,-1689.9729,6.2188))
	{
        OrgCofre[playerid] = 1;
        TogglePlayerControllable(playerid, true);
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, -599.1168,-1065.9753,23.4103))
	{
        OrgCofre[playerid] = 15;
        TogglePlayerControllable(playerid, true);
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 219.2626,108.5960,1010.2118))
	{
        OrgCofre[playerid] = 16;
        TogglePlayerControllable(playerid, true);
		ShowDialogCofreOrg(playerid);
	}
 	else if(PlayerToPoint(1, playerid, 2477.7251,89.5832,26.7737))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 25;
		ShowDialogCofreOrg(playerid);
	}
 	else if(PlayerToPoint(1, playerid, 479.5926,-1531.1252,19.8107))
	{
        OrgCofre[playerid] = 24;
        TogglePlayerControllable(playerid, true);
		ShowDialogCofreOrg(playerid);
	}
 	else if(PlayerToPoint(1, playerid, 294.0777,-1372.6936,14.0260))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 12;
		ShowDialogCofreOrg(playerid);
	}
 	else if(PlayerToPoint(1, playerid, 671.9144,-1271.4734,13.6250))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 13;
		ShowDialogCofreOrg(playerid);
	}

 	else if(PlayerToPoint(1, playerid, 687.2863,-472.8064,16.5363))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 28;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 1690.1144,-2098.9558,13.8343))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 5;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 1688.1190,-1351.0415,17.4297))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 33;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 2593.9116, -1500.9254, 16.0808))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 14;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, -198.4513, -1087.4451, 24.6806))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 17;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 2825.3916,-1170.2870,25.2235))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 18;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 1596.2747, -733.9089, 65.3713)) // Menu ORG - C.V
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 19;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 1329.1952, -3008.4778, 8.3392))
	{
    	TogglePlayerControllable(playerid, true);
    	OrgCofre[playerid] = 21;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 2788.4028,-1627.9689,10.9272))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 22;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 358.7956,186.6793,1008.3828))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 7;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 2281.0020,-2368.7363,13.5469))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 8;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, 750.9255,-1359.1901,13.5000))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 9;
		ShowDialogCofreOrg(playerid);
	}
	else if(PlayerToPoint(1, playerid, -308.2417,1538.4569,75.5625))
	{
        TogglePlayerControllable(playerid, true);
        OrgCofre[playerid] = 20;
		ShowDialogCofreOrg(playerid);
	}
	else if (PlayerToPoint(1, playerid,-329.7025,1536.6123,76.6117))
	{
		//Entrada HQ EI
		SetPlayerPos(playerid,301.0507,306.1636,1003.5391);
		SetPlayerInterior(playerid, 4);
		SetPlayerVirtualWorld(playerid, 0);
	}
	else if (PlayerToPoint(1, playerid, 301.0507,306.1636,1003.5391))
	{
		//Saida HQ EI
		SetPlayerPos(playerid,-329.7025,1536.6123,76.6117);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}

	else if (PlayerToPoint(1.0, playerid, 649.3264,-1353.8356,13.5470))     	// Entrada da San News
	{
		SetPlayerPos(playerid, 982.2499,-1328.6437,701.0859);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 509);
		ShowLoadingMap(playerid);
	}
	else if (PlayerToPoint(1.0, playerid, 982.2499,-1328.6437,701.0859))     // Saida da San News
	{
		SetPlayerPos(playerid, 649.3264,-1353.8356,13.5470);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}

 	else if (PlayerToPoint(2.0, playerid, 1800.0864,-1578.3821,14.0739))
	{//Entrada Prisão La Sante
		GameTextForPlayer(playerid, "~w~Prisao La Sante", 5000, 1);
		SetPlayerInterior(playerid, 7);
		SetPlayerVirtualWorld(playerid, 99);
		SetPlayerPos(playerid, 298.6140,-127.6900,1004.0741);
		SetPlayerFacingAngle(playerid, 123.6967);
		SetCameraBehindPlayer(playerid);
		ShowLoadingMap(playerid);
	}
 	else if (PlayerToPoint(1.0, playerid, 298.6140,-127.6900,1004.0741))
	{//Saida Prisão La Sante
	    if(Player_GetJailed(playerid) > 0) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você ainda é um detento !");
	    }

	    GameTextForPlayer(playerid, "~w~Los Santos", 5000, 1);
	    SetPlayerInterior(playerid, 0);
	    SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, 1800.0864,-1578.3821,14.0739);
	}
	else if (PlayerToPoint(2.0, playerid, 282.5788,-139.5177,1004.0825))
	{//Entrada - Celas Prisão La Sante
		SetPlayerInterior(playerid, 7);
		SetPlayerVirtualWorld(playerid, 99);
		SetPlayerPos(playerid, 279.5692,1935.7527,1062.0924);
		SetPlayerFacingAngle(playerid, 267.4312);
		SetCameraBehindPlayer(playerid);
		ShowLoadingMap(playerid);
	}
 	else if (PlayerToPoint(1.0, playerid, 279.5692,1935.7527,1062.0924))
	{//Saida - Celas Prisão La Sante
	    if(Player_GetJailed(playerid) > 0) {
	        return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você ainda é um detento !");
	    }

	    SetPlayerInterior(playerid, 7);
		SetPlayerVirtualWorld(playerid, 99);
		SetPlayerPos(playerid, 282.5788,-139.5177,1004.0825);
		SetPlayerFacingAngle(playerid, 0.00);
		SetCameraBehindPlayer(playerid);
		ShowLoadingMap(playerid);
	}
	// P.R.F
 	else if (PlayerToPoint(3.0, playerid, 919.4673,-1252.2612,16.2109))
	{
	    GameTextForPlayer(playerid, "~w~P.R.F", 5000, 1);
	    SetPlayerVirtualWorld(playerid, 16);
	    SetPlayerInterior(playerid, 10);
		SetPlayerPos(playerid, 222.9435,118.2206,1010.2188);
		SetPlayerFacingAngle(playerid, 180.0000);
		SetCameraBehindPlayer(playerid);
	}
	// Departamento de Veículos
	else if (PlayerToPoint(3.0, playerid, 2248.0339,-134.3159,26.7618))
	{
	    GameTextForPlayer(playerid, "~w~Dep. de Veiculos", 5000, 1);
	    SetPlayerVirtualWorld(playerid, 1000);
	    SetPlayerInterior(playerid, 10);
		SetPlayerPos(playerid, 222.9435,118.2206,1010.2188);
		SetPlayerFacingAngle(playerid, 180.0000);
		SetCameraBehindPlayer(playerid);
	}
	else if (PlayerToPoint(2.0, playerid, 222.9435,118.2206,1010.2188))
	{
		if(GetPlayerVirtualWorld(playerid) == 16) 
		{
	    	GameTextForPlayer(playerid, "~w~HQ P.R.F", 5000, 1);
			SetPlayerPos(playerid, 919.4673,-1252.2612,16.2109);
			SetPlayerFacingAngle(playerid, 97.0936);
		}
		else if(GetPlayerVirtualWorld(playerid) == 1000)
		{
			GameTextForPlayer(playerid, "~w~Patio", 5000, 1);
			SetPlayerPos(playerid, 2248.0339,-134.3159,26.7618);
			SetPlayerFacingAngle(playerid, 0.000);
		}
	    SetPlayerInterior(playerid, 0);
	    SetPlayerVirtualWorld(playerid, 0);
		SetCameraBehindPlayer(playerid);
	}
//--
	//HQ Sons Of Anarchy
 	else if (PlayerToPoint(2.0, playerid, 2485.6860,89.4010,26.7737))
	{
	    GameTextForPlayer(playerid, "~w~Bar da Sons", 5000, 1);
	    SetPlayerInterior(playerid, 11);
	    SetPlayerVirtualWorld(playerid, 25);
		SetPlayerPos(playerid, 501.9019,-67.7362,998.7578);
		SetPlayerCP(playerid, 9988);
	}

	//---------------------------------------------
	else if (PlayerToPoint(2.0, playerid, 501.9019,-67.7362,998.7578))
	{
		new world = GetPlayerVirtualWorld(playerid);
	    if (world == 25)
		{
		    GameTextForPlayer(playerid, "~w~HQ Sons Of Anarchy", 5000, 1);
			SetPlayerPos(playerid, 2485.6860, 89.4010, 26.7737);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
		}
	}

	// HQ Warlocks
 	else if (PlayerToPoint(2.0, playerid, 681.6184, -474.1958, 16.5363))
	{
	    GameTextForPlayer(playerid, "~w~Bar da Warlocks", 5000, 1);
	    SetPlayerInterior(playerid, 11);
	    SetPlayerVirtualWorld(playerid, 28);
	    SetPlayerCP(playerid, 9988);
		SetPlayerPos(playerid, 668.9234, -422.0179, 671.8927);
	}
	// Saida HQ Warlocks
 	else if (PlayerToPoint(2.0, playerid, 668.9234, -422.0179, 671.8927))
	{
		if (GetPlayerVirtualWorld(playerid) == 28)
		{
		    GameTextForPlayer(playerid, "~w~HQ Warlocks", 5000, 1);
			SetPlayerPos(playerid, 681.6184, -474.1958, 16.5363);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
		}
	}


	else if (PlayerToPoint(3, playerid,1548.8167,-1366.2247,326.2109))
	{
		SetPlayerPos(playerid, 1572.1115,-1332.5288,16.4844);
	}
	else if (PlayerToPoint(2, playerid,-2385.7024,2215.9673,4.9844))
	{
	    if (!Helper_GetNivel(playerid) && !Admin_GetNivel(playerid)) 
			return SendClientMessage(playerid, -1, "Você não faz parte da Equipe do Servidor!");

		SetPlayerPos(playerid, 745.6591,1439.1343,1102.7031); // Clube da Putaria (HQ Staff)
		GameTextForPlayer(playerid, "~w~HQ Staff", 5000, 1);
		SetPlayerInterior(playerid, 6);
		SetPlayerFacingAngle(playerid, 0.1053);
		SetPlayerVirtualWorld(playerid, 1337);
	}
	else if (PlayerToPoint(2, playerid,745.6591,1439.1343,1102.7031))
	{
		SetPlayerPos(playerid,-2385.7024,2215.9673,4.9844);
		GameTextForPlayer(playerid, "~w~SAN FIERRO", 5000, 1);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
	else if(PlayerToPoint(1.0, playerid,-2027.0715,-103.6059,1035.1818))
	{
        SetPlayerPos(playerid,952.5583,-909.3518,45.7656);
		SetPlayerInterior(playerid, 0);
	}
    else if(PlayerToPoint(3.0, playerid, 246.8302, 62.3217, 1003.6406))
    {
    	SetPlayerVirtualWorld(playerid, 0);
    	SetPlayerInterior(playerid, 0);
    	SetPlayerPos(playerid, 1553.3007,-1675.7654,16.1953);
		SetPlayerFacingAngle(playerid, 90.0000);
		SetCameraBehindPlayer(playerid);
	}

	else if(PlayerToPoint(4.0, playerid,390.4640, 173.8098,1008.3828))
    {
    	SetPlayerVirtualWorld(playerid, 0);
    	SetPlayerInterior(playerid, 0);
    	SetPlayerPos(playerid, 1478.7834,-1783.3513,13.5400); // SetPlayerPosHouse	
	}
    else if(PlayerToPoint(3, playerid,1836.4064,-1682.4403,13.3493))
    {//Alhambra Entrance
		GameTextForPlayer(playerid, "~w~Alhambra", 5000, 1);
		SetPlayerInterior(playerid, 17);
 		SetPlayerVirtualWorld(playerid, 0);
 		SetPlayerPos(playerid,493.3891,-22.7212,1000.6797);
	}
	else if(PlayerToPoint(3.0, playerid,493.3891,-22.7212,1000.6797))
    {//Saida Alhambra

		SetPlayerInterior(playerid, 0);
 		SetPlayerVirtualWorld(playerid, 0);
 		SetPlayerPos(playerid,1836.4064,-1682.4403,13.3493);

		StopPlayerAudioStream(playerid);
	}

	// Saída das Igrejas
	else if(PlayerToPoint(3.0, playerid,-1059.3474,713.6876,630.3285))
    {
		// Saída da Igreja de Jefferson
		if(GetPlayerVirtualWorld(playerid) == 1) {
			SetPlayerPos(playerid,2233.1575,-1333.2433,23.9816);
			SetPlayerFacingAngle(playerid, 270.00);
		}

		// Saída da Igreja de Little Mexico
		else {
    		SetPlayerPos(playerid,1720.2667,-1740.5646,13.5469);
			SetPlayerFacingAngle(playerid, 180.00);
		}
    	SetPlayerVirtualWorld(playerid, 0);
    	SetPlayerInterior(playerid, 0);
		SetCameraBehindPlayer(playerid);
	}
   	else if (PlayerToPoint(2.0, playerid,-2171.3071,645.2919,1057.5938))
    {
 		SetPlayerPos(playerid, 1325.5382, -3031.5596, 8.5836);
   	 	SetPlayerInterior(playerid, 0);
	   	SetPlayerFacingAngle(playerid, 0);
       	SetPlayerVirtualWorld(playerid, 0);
    }

    else if (PlayerToPoint(3, playerid, 328.1634,-1512.4167,36.0325)) //BOPE entrada
	{
        SetPlayerPos(playerid, 238.7052,139.3275,1003.0234);
        GameTextForPlayer(playerid, "~w~DP BOPE",5000,1);
        SetPlayerInterior(playerid, 3);
        SetPlayerFacingAngle(playerid, 0);
        SetPlayerVirtualWorld(playerid, 2);
    }

    else if (PlayerToPoint(3, playerid, -50.0843, -298.3511, 5.4297)) //CORE entrada
	{
        SetPlayerPos(playerid, 238.7052,139.3275,1003.0234);
        GameTextForPlayer(playerid, "~w~DP CORE",5000,1);
        SetPlayerInterior(playerid, 3);
        SetPlayerFacingAngle(playerid, 0);
        SetPlayerVirtualWorld(playerid, 34);
    }

    else if (PlayerToPoint(2.0, playerid, 238.6815,138.6710,1003.0234))
    {
	    if (GetPlayerVirtualWorld(playerid) == 2)
	    {
    		SetPlayerPos(playerid, 328.1634,-1512.4167,36.0325);
		}
	    if (GetPlayerVirtualWorld(playerid) == 11)
	    {
    		SetPlayerPos(playerid, 1124.7544,-2036.9777,69.8833);
		}
		if (GetPlayerVirtualWorld(playerid) == 16)
	    {
    		SetPlayerPos(playerid, 1780.6324, -1789.2137, 13.5286);
		}
		if (GetPlayerVirtualWorld(playerid) == 34)
	    {
    		SetPlayerPos(playerid, -50.0843, -298.3511, 5.4297);
		}
		SetPlayerInterior(playerid, 0);
    	SetPlayerFacingAngle(playerid, 0);
   		SetPlayerVirtualWorld(playerid, 0);
    }

    else if(PlayerToPoint(2.0, playerid,246.3772,107.4653,1003.2188))
    {//Saida HQ Policia Civil

	    SetPlayerInterior(playerid, 0);
	    SetPlayerPos(playerid,1684.5236,- 1343.3313, 17.4368);
	    SetPlayerVirtualWorld(playerid, 0);
    }

    else if (PlayerToPoint(1.0, playerid,2496.0398,-1692.0844,1014.7422) && GetPlayerVirtualWorld(playerid) == 0)
	{
		// HQ G.R.O.T.A Saida
 		SetPlayerPos(playerid,2590.2910,-1494.0944,16.8114);
 		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 4.0967);
		SetPlayerVirtualWorld(playerid, 0);
    }

    else if(PlayerToPoint(1.0, playerid,343.7183,304.9376,999.1484))
	{
		// SAIDA HQ HITMANS
 		SetPlayerInterior(playerid, 0);
 		SetPlayerPos(playerid,2281.2393,-2364.8765,13.5469);
 		SetPlayerVirtualWorld(playerid, 0);
	}
    else if (PlayerToPoint(2.0, playerid,295.1739,1472.2755,1080.2578))
    {//SAIDA HQ BAIRRO-13
  	    SetPlayerPos(playerid, 2808.3562,-1176.4606,25.3687);
	  	SetPlayerInterior(playerid, 0);
    	SetPlayerFacingAngle(playerid, 0);
 		SetPlayerVirtualWorld(playerid, 0);
    }
	else if (PlayerToPoint(2, playerid,1478.7834,-1783.3513,13.5400))
	{//Governo LS(Entrada)
	    SetPlayerInterior(playerid, 3);
	    SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid,390.4640,173.8098,1008.3828);
		GameTextForPlayer(playerid, "~w~Bem vindo a HQ Governo !", 5000, 1);
		SetPlayerFacingAngle(playerid, 180.0000);
	}

	else if(IsPlayerInRangeOfPoint(playerid, 2.5, 690.7985,-1275.9355,13.5602))
	{//yakuza
	    SetPlayerPos(playerid, 2468.0916,-1698.3778,1013.5078);
	    SetPlayerInterior(playerid, 2);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.5, 2468.0916,-1698.3778,1013.5078))
	{//yakuza
	    SetPlayerPos(playerid, 690.7985,-1275.9355,13.5602);
	    SetPlayerInterior(playerid, 0);
	    SetPlayerVirtualWorld(playerid, 0);
	}

	else if(IsPlayerInRangeOfPoint(playerid, 2.5, 289.8943, -1373.6874, 14.8122))
	{//Máfia Italiana
	    SetPlayerPos(playerid, 2261.0310,-1135.9053,1050.6328);
	    SetPlayerInterior(playerid, 10);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.5, 2261.0310,-1135.9053,1050.6328))
	{//Máfia Italiana
	    SetPlayerPos(playerid, 289.8943, -1373.6874, 14.8122);
	    SetPlayerInterior(playerid, 0);
	    SetPlayerVirtualWorld(playerid, 0);
	}

/*        							  FARC HQ 											*/

    else if (PlayerToPoint(2.0, playerid, 1684.8771,-2098.8760,13.8343))
	{//entrada HQ AZTECAS

		GameTextForPlayer(playerid, "~w~HQ Amigo dos Amigos", 5000, 1);
		SetPlayerInterior(playerid, 5);
		SetPlayerVirtualWorld(playerid, 5);
		SetPlayerPos(playerid, 22.8858,1405.1282,1084.4297);
    }

    else if (PlayerToPoint(3, playerid, -594.6794,-1057.1132,23.3562))
	{   // Interior FARC Entrada
		GameTextForPlayer(playerid, "~y~HQ Estado Islamico", 5000, 1);
		SetPlayerInterior(playerid, 5);
		SetPlayerVirtualWorld(playerid, 15);
		SetPlayerPos(playerid, 22.8858,1405.1282,1084.4297);
	}

	else if (PlayerToPoint(3, playerid, -201.4692, -1092.9031, 25.2115))
	{   // Interior HQ Familia do Norte Entrada
		GameTextForPlayer(playerid, "~p~HQ Familia do Norte", 5000, 1);
		SetPlayerInterior(playerid, 5);
		SetPlayerVirtualWorld(playerid, 17);
		SetPlayerPos(playerid, 318.5944,1115.5940,1083.8828);
		SetPlayerFacingAngle(playerid, 359.6651);
	}
	else if (PlayerToPoint(2, playerid, 318.5944,1115.5940,1083.8828))
	{   // Interior HQ Familia do Norte Saida
		if( GetPlayerVirtualWorld(playerid) == 17 )
		{
			SetPlayerPos(playerid,-201.4692, -1092.9031, 25.2115);
			SetPlayerFacingAngle(playerid, 87.7350);
			GameTextForPlayer(playerid, "~w~Los Santos", 5000, 1);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
		}
	}

    else if(PlayerToPoint(1.0, playerid, 22.8858,1405.1282,1084.4297))
	{
	    if (GetPlayerVirtualWorld(playerid) == 5)
	    {
    		SetPlayerPos(playerid, 1684.8771,-2098.8760,13.8343);
		}
		else if (GetPlayerVirtualWorld(playerid) == 15)
		{
		    SetPlayerPos(playerid, -594.6794,-1057.1132,23.3562);
  		}

		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
    }
	else if (PlayerToPoint(3, playerid,2770.6521,-1628.1273,12.1775))
	{   // Interior Triad Entrada
		SetPlayerPos(playerid, 2807.2886,-1173.1145,1025.5703);
		GameTextForPlayer(playerid, "~w~HQ Triad", 5000, 1);
		SetPlayerInterior(playerid, 8);
		SetPlayerVirtualWorld(playerid, 22);
	}
	else if (PlayerToPoint(2, playerid, 2807.2886,-1173.1145,1025.5703))
	{   // Interior Triad Saida
		if( GetPlayerVirtualWorld(playerid) == 22 )
		{
			SetPlayerPos(playerid,2770.6521,-1628.1273,12.1775);
			GameTextForPlayer(playerid, "~w~Los Santos", 5000, 1);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
		}
	}

	// Elevador da Policia Civil
	else if(PlayerToPoint(2, playerid, 1650.6134, -1351.0118, 17.4295))
	{
		SetPlayerPos(playerid, 1672.1484, -1334.3336, 158.4766);
	}
	else if(PlayerToPoint(1.2, playerid, 1672.1484, -1334.3336, 158.4766))
	{
		SetPlayerPos(playerid, 1650.6134, -1351.0118, 17.4295);
	}
	// Nova HQ BOPE - Elevador
	else if(PlayerToPoint(2, playerid, 338.2485,-1501.9403,36.0391))
	{
		SetPlayerPos(playerid, 347.8569,-1494.7401,76.5391);
	}
	else if(PlayerToPoint(1.2, playerid, 347.8569,-1494.7401,76.5391))
	{
		SetPlayerPos(playerid, 338.2485,-1501.9403,36.0391);
	}

	// Nova HQ Familia do Norte - Elevador
	else if(PlayerToPoint(2, playerid, 2473.2554,-1531.0217,24.1455))
	{
		SetPlayerPos(playerid, 2463.8401,-1538.7161,32.5703);
	}
	else if(PlayerToPoint(1.2, playerid, 2463.8401,-1538.7161,32.5703))
	{
		SetPlayerPos(playerid, 2473.2554,-1531.0217,24.1455);
	}

	// Casinha 1
	else if(PlayerToPoint(0.7, playerid,1397.7185,-1797.1010,13.5469))
	{
		if (GetPlayerOrg(playerid) != 16 && !IsACop(playerid)) return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não é um agente da P.R.F ou um policial!");
		SetPlayerPos(playerid,1397.7185,-1795.1010,13.5469);
	}
	else if(PlayerToPoint(0.8, playerid,1397.7185,-1795.1010,13.5469)) SetPlayerPos(playerid,1397.7185,-1797.1010,13.5469);
	// Casinha 2
	else if(PlayerToPoint(0.7, playerid,2030.7540,-1760.8278,13.5469))
	{
        if (GetPlayerOrg(playerid) != 16 && !IsACop(playerid)) return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não é um agente da P.R.F ou um policial!");
		SetPlayerPos(playerid,2032.7944,-1760.7570,13.5469);
	}
	else if(PlayerToPoint(0.8, playerid,2032.7944,-1760.7570,13.5469)) SetPlayerPos(playerid,2030.7540,-1760.8278,13.5469);
	// Casinha 3
	else if(PlayerToPoint(0.7, playerid,1915.6649,-1452.4265,13.5469))
	{
        if (GetPlayerOrg(playerid) != 16 && !IsACop(playerid)) return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não é um agente da P.R.F ou um policial!");
		SetPlayerPos(playerid,1913.4480,-1452.6014,13.5469);
	}
	else if(PlayerToPoint(0.8, playerid,1913.4480,-1452.6014,13.5469)) SetPlayerPos(playerid,1915.6649,-1452.4265,13.5469);
	// Casinha 4
	else if (PlayerToPoint(0.7, playerid,1240.2002,-1409.2941,13.0107))
	{
        if (GetPlayerOrg(playerid) != 16 && !IsACop(playerid)) return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não é um agente da P.R.F ou um policial!");
		SetPlayerPos(playerid,1242.0645,-1409.2439,13.0106);
	}
	else if (PlayerToPoint(0.8, playerid,1242.0645,-1409.2439,13.0106)) SetPlayerPos(playerid,1240.2002,-1409.2941,13.0107);
	// Casinha 5
	else if (PlayerToPoint(0.7, playerid,1225.1102,-1391.8157,13.2337))
	{
        if (GetPlayerOrg(playerid) != 16 && !IsACop(playerid)) return SendClientMessage(playerid, COLOR_LIGHTRED, "Você não é um agente da P.R.F ou um policial!");
		SetPlayerPos(playerid,1223.1981,-1391.9094,13.2449);
	}
	else if (PlayerToPoint(0.8, playerid,1223.1981,-1391.9094,13.2449)) SetPlayerPos(playerid,1225.1102,-1391.8157,13.2337);

//----------------------------------

	else if (PlayerToPoint(1, playerid,1570.3828,-1333.8882,16.4844))
	{
		SetPlayerPos(playerid, 1545.0068,-1366.5094,327.2868);
	}

	else if(PlayerToPoint(3, playerid, 1553.3007,-1675.7654,16.1953))
    {//Departamento de Policia Los Santos
    	GameTextForPlayer(playerid, "~w~Departamento da Policia Militar", 5000, 1);
    	SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 6);
		SetPlayerPos(playerid, 246.8302, 62.3217, 1003.6406);
		SetPlayerFacingAngle(playerid, 90.0000);
		SetCameraBehindPlayer(playerid);
    }


	// Igreja de Jefferson
	else if(PlayerToPoint(3, playerid, 2233.1575,-1333.2433,23.9816))
    {
    	GameTextForPlayer(playerid, "~w~Igreja de Jefferson", 5000, 1);
    	SetPlayerVirtualWorld(playerid, 1);
		SetPlayerPos(playerid,-1059.3474,713.6876,630.3285);
		SetPlayerFacingAngle(playerid, 90.0000);
		SetCameraBehindPlayer(playerid);
		FreezeThePlayer(playerid, 3000);
}

	// Igreja de Little Mexico
	else if(PlayerToPoint(3, playerid, 1720.2667,-1740.5646,13.5469))
    {
    	GameTextForPlayer(playerid, "~w~Igreja de Little Mexico", 5000, 1);
    	SetPlayerVirtualWorld(playerid, 2);
		SetPlayerPos(playerid,-1059.3474,713.6876,630.3285);
		SetPlayerFacingAngle(playerid, 90.0000);
		SetCameraBehindPlayer(playerid);
		FreezeThePlayer(playerid, 3000);
    }

//=-=-=-=-=-=-=-=-=| MOTEL |=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=<|
	else if (PlayerToPoint(3, playerid,2233.0254,-1159.8149,25.8906))
	{//Motel entrada
		if (Dev_GetNivel(playerid) < DEV_ALPHA)
			return SendClientMessage(playerid, -1, "O Motel está disponível somente para Equipe de Desenvolvimento.");

		SetPlayerPos(playerid, 2214.7134,-1150.4315,1025.7969);
		GameTextForPlayer(playerid, "~w~Motel",5000,1);
		SetPlayerInterior(playerid, 15);
		SetPlayerFacingAngle(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
	else if (PlayerToPoint(3, playerid,2214.7134,-1150.4315,1025.7969))
	{//Motel Saída
		SetPlayerPos(playerid, 2233.0254,-1159.8149,25.8906);
		GameTextForPlayer(playerid, "~w~Los Santos",5000,1);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
    else if (PlayerToPoint(3, playerid,1325.5382, -3031.5596, 8.5836))
	{//entrada P.C.C
        SetPlayerPos(playerid, -2171.3071,645.2919,1057.5938);
        GameTextForPlayer(playerid, "~y~HQ P.C.C",5000,1);
        SetPlayerInterior(playerid, 1);
        SetPlayerFacingAngle(playerid, 0);
        SetPlayerVirtualWorld(playerid, 0);
    }

    else if (PlayerToPoint(3, playerid,1124.7544,-2036.9777,69.8833))
	{//PF entrada
        SetPlayerPos(playerid, 238.7052,139.3275,1003.0234);
        GameTextForPlayer(playerid, "~w~DP Policia Federal",5000,1);
        SetPlayerInterior(playerid, 3);
        SetPlayerFacingAngle(playerid, 0);
        SetPlayerVirtualWorld(playerid, 11);
    }

    else if (PlayerToPoint(3, playerid,2590.2910, -1494.0944, 16.8114))
	{//HQ G.R.O.T.A entrada
        SetPlayerPos(playerid,2496.0061,-1693.5201,1014.7422);
        GameTextForPlayer(playerid, "~g~G.R.O.T.A HQ",5000,1);
        SetPlayerInterior(playerid, 3);
        SetPlayerFacingAngle(playerid, 181);
        SetPlayerVirtualWorld(playerid, 0);
    }
    else if (PlayerToPoint(3, playerid,2808.3562,-1176.4606,25.3687))
	{//HQ VAGOS
        SetPlayerPos(playerid,295.1389,1474.4699,1080.5198);
        GameTextForPlayer(playerid, "~w~HQ BAIRRO-13",5000,1);
        SetPlayerInterior(playerid, 15);
        SetPlayerFacingAngle(playerid, 0);
        SetPlayerVirtualWorld(playerid, 0);
    }

    else if(PlayerToPoint(1.0, playerid, 2281.2393,-2364.8765,13.5469))
	{//entrada HQ HITMANS
        GameTextForPlayer(playerid, "~w~HQ Hitmans", 5000, 1);
        SetPlayerInterior(playerid, 6);
        SetPlayerPos(playerid,343.7183,304.9376,999.1484);
        SetPlayerVirtualWorld(playerid, 5);
    }

	//  HQ das Organizações

	else if(PlayerToPoint(2, playerid,1684.5236,- 1343.3313, 17.4368))
	{
	    SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 10);
		SetPlayerPos(playerid,246.4452,108.4379,1003.2188);
		GameTextForPlayer(playerid, "~w~Policia Civil", 5000, 1);
	}

	else if (PlayerToPoint(3, playerid, 475.6070, -1501.5156, 20.5379))   	// Entrada: (Interior) Máfia Cosa Nostra
	{
		SetPlayerPos(playerid, 1298.6595, -795.7878, 1084.0078), SetPlayerFacingAngle(playerid, 0.8585);
		GameTextForPlayer(playerid, "~w~Mafia Cosa Nostra", 5000, 1);
		SetPlayerInterior(playerid, 5);
		SetPlayerVirtualWorld(playerid, 24);
	}
	else if (PlayerToPoint(3, playerid, 1298.6595, -795.7878, 1084.0078))
	{
		if (GetPlayerVirtualWorld(playerid) == 24)      					// Saida: (Interior) Máfia Cosa Nostra
		{
			SetPlayerPos(playerid, 475.6070, -1501.5156, 20.5379), SetPlayerFacingAngle(playerid, 83.7022);
			GameTextForPlayer(playerid, "~w~Los Santos", 5000, 1);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
		}
	}

	CallLocalFunction("DealWithPlayerInPosition", "i", playerid);
	return true;
}

CMD:rank(playerid)
{

	MEGAString[0]=EOS;
	strcat(MEGAString, "{B4B5B7} » Nível\n");
	strcat(MEGAString, "{B4B5B7} » Horas jogadas\n");
	strcat(MEGAString, "{B4B5B7} » Kills\n");
	strcat(MEGAString, "{B4B5B7} » Mortes\n");
	strcat(MEGAString, "{B4B5B7} » Dinheiro\n");
	strcat(MEGAString, "{B4B5B7} » Crimes cometidos\n");
	strcat(MEGAString, "{B4B5B7} » Materiais\n");
	strcat(MEGAString, "{B4B5B7} » Maconha\n");
	strcat(MEGAString, "{B4B5B7} » Cocaina\n");
	strcat(MEGAString, "{B4B5B7} » Crack\n");
	strcat(MEGAString, "{00FF00} » Arena Kills\n");
	strcat(MEGAString, "{B4B5B7} » Contratos cumpridos\n");
	strcat(MEGAString, "{B4B5B7} » Apreesões policial\n");
	strcat(MEGAString, "{B4B5B7} » Mais ativo do dia\n");
	strcat(MEGAString, "{B4B5B7} » Cash\n");
	strcat(MEGAString, "{B4B5B7} » Ouros\n");
	strcat(MEGAString, "{B4B5B7} » Maior Pichador\n");
	if (Admin_GetNivel(playerid) || Helper_GetNivel(playerid)) {
	    strcat(MEGAString, "{B4B5B7} » Atendimento (Admins e Helpers)\n");
	}

	ShowPlayerDialog(playerid, 5009, DIALOG_STYLE_LIST, "Ranks", MEGAString, "Ver", "Cancelar");

	return 1;
}
alias:rank("ranks")

CMD:id(playerid, params[])
{
	new idPlayer;
	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /id (nick ou id do jogador)");

	if (!IsPlayerConnected(idPlayer)) return SendClientMessage(playerid, -1, "Este jogador não está conectado no servidor.");

	if(!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "Este jogador não está logado no servidor.");

    new playerPing2 = GetPlayerPing(idPlayer), string[112];

	new cor[16] = "{00FF00}";
	if(playerPing2 >= 200 && playerPing2 < 300)
	    cor = "{F7E300}";
	else if(playerPing2 < 400)
	    cor = "{F74000}";
	else if(playerPing2 >= 400)
	    cor = "{FF0000}";

	format(string, sizeof string, "%s{FFFFFF} ID: {FF0000}%d{FFFFFF}. (P.L: %.1f%% | Ping: {00FF00}%d{FFFFFF} | %s",
	PlayerName[idPlayer], idPlayer, NetStats_PacketLossPercent(idPlayer), playerPing2, IsAndroidPlayer(idPlayer) ? ("{1FBD5C}Android") : ("{6279D3}PC"));
	SendClientMessage(playerid, 0x00CCFFFF, string);

 	format(string, sizeof string, "| Nível: {00CCFF}%d{FFFFFF}. (Seu PacketLoss: {9C9C9C}%.1f%%{FFFFFF} | Seu ping: {9C9C9C}%d{FFFFFF})",
	PlayerInfo[idPlayer][pLevel], NetStats_PacketLossPercent(playerid), GetPlayerPing(playerid));
	SendClientMessage(playerid, -1, string);

	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	if (oldinteriorid == 10) {

	    if (GetPVarInt(playerid, "playerEnforcer") != INVALID_VEHICLE_ID) {
	        SetPVarInt(playerid, "playerEnforcer", INVALID_VEHICLE_ID);
	    }
	}
    return 1;
}

CMD:camera(playerid)
{
	if (!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, -1, "Você não está dentro de um veículo, ou não é o motorista!");

	if (IsValidObject(dcObject[playerid])) DestroyObject(dcObject[playerid]);

	new carroid = GetPlayerVehicleID(playerid),
		carmodelid = GetVehicleModel(carroid) - 400;

	if(dCam_Xes[carmodelid] == INVALID_DATA || INVALID_DATA == dCam_Yes[carmodelid] || INVALID_DATA == dCam_Highs[carmodelid])
		return SendClientMessage(playerid, 0xDBED15FF, "Não foi possível ligar a câmera em primeira pessoa neste veículo.");

	dcObject[playerid] = CreateObject(19300, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	AttachObjectToVehicle(dcObject[playerid], carroid, -dCam_Xes[carmodelid], dCam_Yes[carmodelid]-0.15, dCam_Highs[carmodelid]-0.06, 0.0, 0.0, 0.0);

	AttachCameraToObject(playerid, dcObject[playerid]);
	SetPVarInt(playerid, "VarFPS", 1);
	SendClientMessage(playerid, -1, "Para desativar a câmera em primeira pessoa digite /desligarcamera");

	return true;
}

CMD:desligarcamera(playerid)
{
	if (!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, -1, "Você não está dentro de um veículo, ou não é o motorista!");

	if(GetPVarInt(playerid, "VarFPS")) {

		if (IsValidObject(dcObject[playerid])) DestroyObject(dcObject[playerid]);

		SetPVarInt(playerid, "VarFPS", 0);
	}
	SendClientMessage(playerid, 0xDBED15FF, "A camêra em primeira pessoa foi desligada");

	SetCameraBehindPlayer(playerid);

	return true;
}

CMD:membros(playerid, params[])
{
	new string[MAX_PLAYER_NAME+30];

	if (GetPlayerOrg(playerid) < 1) return SendClientMessage(playerid, -1, "Você não faz parte de nenhuma organização.");

	SendClientMessage(playerid,GetPlayerColor(playerid),"Membros Online:");
	foreach(new i : Player)
	{
		if(GetPlayerOrg(i) == GetPlayerOrg(playerid))
		{
			format(string, sizeof string, "%s: Cargo: %s", PlayerName[i], GetPlayerCargo(i));
			SendClientMessage(playerid, COLOR_GRAD, string);
		}
	}
	return true;
}

CMD:compgalao(playerid, params[]) return callcmd::comprar(playerid, "galao");
CMD:comprar(playerid, const params[])
{
	new string[128];

	if (!strcmp(params, "galao", true))
	{
		if(PlayerToPoint(2, playerid, 1941.6409,-1764.9487,13.6406))
		{
			if (Player_GetMoney(playerid) < 80) return SendClientMessage(playerid, -1, "Você não tem dinheiro suficiente para comprar galão");

			if (isInventoryFull(playerid))
				return SendClientMessage(playerid, -1, "Você não tem espaço no inventário.");

			format(string, sizeof string, "* Você pegou 20 litros de gasolina por $80, está em seu inventário e pode ser usado em carros !");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			SendClientMessage(playerid, -1, "* Agora quando acabar a gasolina do seu carro, abra seu inventario e use o galão !");

			Player_RemoveMoney(playerid, 80);
			adicionarDinheiroGoverno(80);

			givePlayerItem(playerid, ITEM_TYPE_GASOLINA, 1650, 20, "Galao de Gasolina");
		}
		else SendClientMessage(playerid, -1, "Você não está em um posto de gasolina.");

		return true;
	}
	if (!strcmp(params, "remedio", true)) {

		if (!IsPlayerInRangeOfPoint(playerid, 3.0, 604.0738, -601.3110, 985.6933)) return SendClientMessage(playerid, -1, "Você não está na farmácia.");

		switch (GetPlayerVirtualWorld(playerid)) {
			case 10013: ApplyDynamicActorAnimation(actorFarmacia[0], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
			case 10014: ApplyDynamicActorAnimation(actorFarmacia[1], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
			case 10015: ApplyDynamicActorAnimation(actorFarmacia[2], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
			default: ApplyDynamicActorAnimation(actorFarmacia[3], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
		}

		atendimentoFarmacia[playerid] = true;

		format(string, sizeof(string), "Willian Rodrigues(503) diz: Olá %s, em que posso ajuda-lo? Escolha um dos itens abaixo!", PlayerName[playerid]);
		SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

		format(string, sizeof(string), "Willian Rodrigues(503) diz: Nós temos: remedinho, remedio e medkit, digite oque precisa.", PlayerName[playerid]);
		return SendClientMessageInRange(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}
	return 1;
}

CMD:explodircofre(playerid)
{
	if (!IsAMember(playerid))
		return SendClientMessage(playerid,-1, "Apenas organizações criminosas podem roubar cofres !");

	if (PlayerInfo[playerid][pExplosives] < 1)
		return SendClientMessage(playerid, -1, "Você não tem um explosivo, compre um no mercado negro.");

	if (!GetPlayerHoldingExplosive(playerid)) 
		return SendClientMessage(playerid, -1, "Você não está segurando um explosivo. (Use: /explosivo pegar)");

	if (!IsPlayerInRangeOfPoint(playerid, 2.0, 2148.09399, 1633.38513, 835.75317) &&
		!IsPlayerInRangeOfPoint(playerid, 2.0, 1447.1038, -1123.0455, 23.9590))
		return SendClientMessage(playerid, -1, "Você não está na porta do cofre da empresa!");

	new string[128];

	new id = GetPVarInt(playerid, "propId");
	if (GetPlayerVirtualWorld(playerid) == 0)
		id = 81;

	if (id == 0)
		return SendClientMessage(playerid, COLOR_LIGHTRED, "Essa propriedade está com BUGs é impossível rouba-la.");

	if (gettime() < PropInfo[id][eRobbed]) {
		format(string, sizeof string, "* A empresa está se recuperando de um roubo recente. Há informações que novos fundos ...");
		SendClientMessage(playerid, COLOR_LIGHTRED, string);
		format(string, sizeof string, "... irão chegar em aproximadamente %s, até lá a empresa não pode ser roubada!", ConvertTime(PropInfo[id][eRobbed] - gettime()));
		SendClientMessage(playerid, COLOR_LIGHTRED, string);
		return 1;
	}

	if (roubouOrg[GetPlayerOrg(playerid)]) {
		SendClientMessage(playerid, COLOR_LIGHTRED, "* Sua organização já roubou neste payday !");
		return 1;
	}

	foreach(new x : Player) {

		if (GetPVarInt(x, "propId") == id && GetPVarInt(x, "ExplodindoCofre")) {
			return SendClientMessage(playerid, COLOR_LIGHTRED, "* Alguém já colocou um explosivo na porta, aguarde detonar...");
		}
	}

	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	if (id != 81) {
		SetPlayerPos(playerid, 2148.1201,1632.6825,835.1881);
		SetPlayerFacingAngle(playerid, 0.0);
	}
	SetPVarInt(playerid, "ExplodindoCofre", 1);

	ApplyAnimation(playerid, "CAMERA","piccrch_take", 4.0, true, false, false, false, 0);
	SetTimerEx("ExplodirCofre", 40 * 1000, false, "dd", playerid, id);

	SetTimerEx(#SetAnimCofre, 500, false, "d", playerid);

	SendClientMessage(playerid, COLOR_GRAD, "*Você está colocando uma bomba na porta do cofre, aguarde...");

	GameTextForPlayer(playerid, "~r~plantando bomba...", 5000, 1);

	ShowPlayerBaloonInfo(playerid, "Espere a bomba ser plantada, depois afaste-se", 5000);
	return 1;
}

CALLBACK:SetAnimCofre(playerid)
	return ApplyAnimation(playerid, "CAMERA","piccrch_take", 4.0, true, false, false, false, 0);

CALLBACK:ExplodirCofre(playerid, propid) {

	if (!IsPlayerInRangeOfPoint(playerid, 2.0, 2148.09399, 1633.38513, 835.75317) &&
		!IsPlayerInRangeOfPoint(playerid, 2.0, 1447.1038, -1123.0455, 23.9590)) {
		SetPVarInt(playerid, "ExplodindoCofre", 0);
		return SendClientMessage(playerid, COLOR_LIGHTRED, " Explosão abortada! você não está perto suficiênte da porta do cofre !");
	}

	if (propid != 81)
		SetPVarInt(playerid, "objectExplosao", CreateDynamicObject(1654, 2148.09766, 1633.13269, 834.96289,   0.00000, 0.00000, 0.00000, GetPlayerVirtualWorld(playerid)));

	PlayerInfo[playerid][pExplosives] = 0;
	SetPlayerExplosive(playerid, false);
	RemovePlayerAttachedObject(playerid, Slot_Explosivo);
	SetTimerEx("ExplosaoCofre", 10000, false, "dd", playerid, propid);

	SendClientMessage(playerid, COLOR_LIGHTRED, "* Você plantou uma bomba na porta, agora afaste-se e espere explodir !");
	GameTextForPlayer(playerid, "~r~afaste-se da porta", 5000, 1);
	ClearAnimations(playerid, SYNC_ALL);
	return 1;
}

timer t_CloseVault[10 * 60000]()
{
	// Close Vault
	vaultState = false;
	MoveDynamicObject(vaultDoor, 1444.822631, -1124.319946, 24.488027-0.0001, 0.0001, 0.000000, 0.000000, 579.799987);
}

CALLBACK:ExplosaoCofre(playerid, propid) {

	SetPVarInt(playerid, "ExplodindoCofre", 0);

	DestroyDynamicObject(GetPVarInt(playerid, "objectExplosao"));
	SetPVarInt(playerid, "objectExplosao", -1);

	if (propid == 81)
		CreateExplosionEx(2148.0977, 1633.1327, 834.9629, 7, 1.0, GetPlayerVirtualWorld(playerid));
	else
		CreateExplosionEx(1447.1038, -1123.0455, 23.9590, 7, 1.0, GetPlayerVirtualWorld(playerid));

	new rand = random(10);

	switch(rand) 
	{
		case 0..5: 
		{
			if (propid == 81) {
				vaultState = true;
				MoveDynamicObject(vaultDoor, 1444.822631, -1124.319946, 24.488027+0.0001, 0.0001, 0.000000, 0.000000, 127.799964);

				defer t_CloseVault();
			} 
			else DestroyPropDoor(propid);
			
			PropInfo[propid][eRobbed] 	   = (gettime() + (3 * (60 * 60)));
			savePropertie(propid);

			if (GetPlayerOrg(playerid))
				roubouOrg[GetPlayerOrg(playerid)] = true;
		}
		default:{
			SendClientMessage(playerid, COLOR_LIGHTRED, "* A força da bomba não foi suficiênte para derrubar a porta, tente novamente !");
		}
	}
	return 1;
}

CMD:retirarcapacete(playerid)
{
	if (IsPlayerAttachedObjectSlotUsed(playerid, Slot_Capacete)) {
		new string[75];
		format(string, sizeof string, "* %s retirou seu capacete", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		RemovePlayerAttachedObject(playerid, Slot_Capacete);
	} else {
		SendClientMessage(playerid, -1, "Você não está usando um capacete !");
	}
	return 1;
}

CMD:comparsa(playerid, params[])
{
	new idplayer;
	if(sscanf(params, "u", idplayer)) return SendClientMessage(playerid, -1, "/comparsa [id]");
	else if(idplayer == playerid)return SendClientMessage(playerid, -1, "Você não pode usar este comando em você mesmo!");
	else if(!IsPlayerConnected(idplayer)) return SendClientMessage(playerid, -1, "Jogador offline.");
	else if(!ProxDetectorS(4.0, playerid, idplayer)) return SendClientMessage(playerid, -1, "O jogador não está perto o suficiente de você.");
	
	new string[128];
	format(string, sizeof(string),"* %s está convidando você para ser comparsa nos assaltos, para aceitar use (/aceitar comparsa).", PlayerName[playerid]);
	SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);

	format(string, sizeof(string),"* Você convidou %s para ser seu comparsa, aguarde uma resposta...", PlayerName[idplayer]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

	SetPVarInt(idplayer, "ConviteComparsa", playerid);
	return 1;
}

CMD:cumprimentar(playerid, params[])
{
	new idplayer;
	if(sscanf(params, "u", idplayer))
	{
		SendClientMessage(playerid, -1, "/cumprimentar [Playerid]");
		return 0x01;
	}
	if(idplayer == playerid)return SendClientMessage(playerid, -1, "Você não pode usar este comando em você mesmo!");
	if(IsPlayerConnected(idplayer))
	{
		if(ProxDetectorS(1.0, playerid, idplayer))
		{
			new string[78];
			new Float:x, Float:y, Float:z;
			GetPlayerPos(idplayer, x, y, z);
			SetPlayerFaceToPoint(playerid, x, y);
			GetPlayerPos(playerid, x, y, z);
			SetPlayerFaceToPoint(idplayer, x, y);
			format(string, sizeof(string),"*%s aperta a mão de %s.", PlayerName[playerid], PlayerName[idplayer]);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			ApplyAnimation(playerid,"GANGS","hndshkaa", 3.1, false, true, true, false, 0);
			ApplyAnimation(idplayer,"GANGS","hndshkaa", 3.1, false, true, true, false, 0);

			CheckConquista(playerid, Conquista_Cumprimento);
			CheckConquista(idplayer, Conquista_Cumprimento);
		}
		else
		{
			SendClientMessage(playerid, -1, "O player não está perto o suficiente de você.");
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "Player offline.");
	}
	return 0x01;
}

CMD:boquete(playerid, params[])
{
	new idplayer;
	if(sscanf(params, "u", idplayer))
	{
		SendClientMessage(playerid, -1, "/boquete [Playerid]");
		return 0x01;
	}
	if(idplayer == playerid)
		return SendClientMessage(playerid, -1, "Você não pode usar este comando em você mesmo!");

	if(IsPlayerConnected(idplayer))
	{
		if(ProxDetectorS(1.0, playerid, idplayer))
		{
			new string[78];
			new Float:x, Float:y, Float:z;
			GetPlayerPos(idplayer, x, y, z);
			SetPlayerFaceToPoint(playerid, x, y);
			GetPlayerPos(playerid, x, y, z);
			SetPlayerFaceToPoint(idplayer, x, y);
			format(string, sizeof(string),"*%s paga um boquete para %s.", PlayerName[playerid], PlayerName[idplayer]);
			SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			ApplyAnimation(playerid,"BLOWJOBZ","BJ_COUCH_LOOP_W", 3.1, false, true, true, false, 0);
			ApplyAnimation(idplayer,"BLOWJOBZ","BJ_COUCH_END_P", 3.1, false, true, true, false, 0);
		}
		else
		{
			SendClientMessage(playerid, -1, "O player não está perto o suficiente de você.");
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "Player offline.");
	}
	return 0x01;
}

CMD:peidar(playerid, params[])
{
	new string[35];
	Sound(playerid, 20803, 15.0);
	format(string, sizeof(string),"*%s peidou.", PlayerName[playerid]);
	SendClientMessageInRange(15.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	return 1;
}

//---------------Guinchar----------------------------------
CMD:guinchar(playerid, params[])
{
	if(IsACop(playerid) or GetPlayerOrg(playerid) == 16 or PlayerIsMecanico(playerid))
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			if (GetVehicleModel(GetPlayerVehicleID(playerid)) == 525)
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				{
					new id = getVehicleProxPlayer(playerid, 8.500, GetPlayerVehicleID(playerid));

					if (id == INVALID_VEHICLE_ID) {
						return SendClientMessage(playerid,-1, "* Nenhum veículo por perto !");
					}

					new vehicleOrgID = GetVehicleOrgID(id);
					if(IsPlayerInAreaSeguraOrg(playerid, vehicleOrgID))
						return SendClientMessage(playerid, -1, "Não é permitido guinchar veículos na HQ da organização!");

					if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid))) {
						DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
					} else {
						AttachTrailerToVehicle(id, GetPlayerVehicleID(playerid));
					}
				}
				else
				{
					SendClientMessage(playerid, -1, "Você precisa estar dirigindo !");
					return true;
				}
			}
			else
			{
				SendClientMessage(playerid, -1, "Você não tem um Guincho !");
				return true;
			}
		}
		else
		{
			SendClientMessage(playerid, -1, "Você não está em um guincho !");
			return true;
		}
	}
	else
	{
		SendClientMessage(playerid,COLOR_GRAD,"Você não possui autorização para guinchar um veículo !");
		return true;
	}
	return true;
}

CMD:jetpack(playerid)
{
    if (GetPVarInt(playerid, "Abordado")) return SendClientMessage(playerid, -1, "Você não pode usar esse comando em uma abordagem.");

    if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "Você não pode usar esse comando em um veículo.");

	if(GetPVarInt(playerid, "BlockJetpack"))
		return SendClientMessage(playerid, -1, "Você está proibido de usar jetpack temporariamente.");

	if (PlayerInfo[playerid][pVIP] >= 2 || IsPlayerHaveItem(playerid, ITEM_TYPE_JETPACK) || Founders_GetList(playerid))
	{
		new string[100];

		new Float:vid, Float:colete;
	 	GetPlayerHealth(playerid, vid);
	  	GetPlayerArmour(playerid, colete);

		if(IsPlayerInCombat(playerid))
			return SendClientMessage(playerid, -1, "Você só poderá usar o Jetpack 1 minuto após tomar dano de alguém !");

	 	if (GetPlayerSpeedEx(playerid) > 1) return SendClientMessage(playerid, -1, "Você precisa estar parado para pegar o jetpack.");

        format(string, sizeof(string), "* %s pegou seu Jetpack", PlayerName[playerid]);
		SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	} else {
	    SendClientMessage(playerid, -1, "Você não e um jogador SÓCIO-OURO ou não possui um JetPack.");
	}

	return 1;
}

stock CountAdminTrampo()
{
	new count;
	foreach(new i : Player)
	{
	    if(Admin_GetNivel(i) && Staff_GetWorking(i))count ++;
	}
	return count;
}

CMD:advogados(playerid)
{
	new string[128];
	new count = 0;

	MEGAString[0] = EOS;

	strcat(MEGAString, "ID\tNome\tPontos de Advogado\n");

	foreach(new players : Character) {

	    if (PlayerIsAdvogado(players)) {

			format(string, sizeof string, "%02d\t%s\t{00BFFF}Pontos de Advogado (%d)\n", players, PlayerName[players], PlayerInfo[players][pAdvogadoSkill]);
            strcat(MEGAString, string);

            List_SetPlayers(playerid, count, players);
            count ++;
		}
	}

    format(string, sizeof string, " {FFFFFF}Advogados Online ({00FF00}%d{FFFFFF})", count);

	ShowPlayerDialog(playerid, 4275, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Enviar SMS", "Fechar");

    return true;
}

CMD:habilidades(playerid)
{
	MEGAString[0] = EOS;

	strcat(MEGAString, "Profissão\tNível\tExperiencia\n");

	// Habilidades de Advogado
	new playerAdvogado = PlayerInfo[playerid][pAdvogadoSkill];
	new playerMedico = PlayerInfo[playerid][pMedicoSkill];
	new string[128];

	new level = 6, maxPoints = 2000, limits[5] = {50, 100, 200, 350, 500};
	for(new l = 0; l < 5; l++) 
		if(playerAdvogado <= limits[l]) {
			level = l+1;
			maxPoints = limits[l];
			break;
		}

	format(string, sizeof string, "{00BFFF}Advogado\t{00FF00}%d\t{33CCFF}%d/%d\n", level, playerAdvogado, maxPoints);
	strcat(MEGAString, string);

	for(new l = 0; l < 5; l++) 
		if(playerMedico <= limits[l]) {
			level = l+1;
			maxPoints = limits[l];
			break;
		}

	format(string, sizeof string, "{00BFFF}Médico\t{00FF00}%d\t{33CCFF}%d/%d\n", level, playerMedico, maxPoints);
	strcat(MEGAString, string);

	// Habilidades com ferramentas
	level = PlayerInfo[playerid][pFerSkill];

	format(string, sizeof string, "{00BFFF}Ferramentas\t{00FF00}%d\t{33CCFF}%d/%d\n", floatround(level / 5, floatround_floor) + 1, level % 5, 5);
	strcat(MEGAString, string);

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Habilidades", MEGAString, "Fechar", "");
    return true;
}

CMD:sound(playerid, soundid[])
{
    new sd;
	if(sscanf(soundid, "d", sd))
	{
		SendClientMessage(playerid, -1, "Use: /sound [id]");
		return true;
	}
	PlayerPlaySound(playerid, sd, 0.0, 0.0, 0.0);
    return true;
}

stock GetNivelAdv(playerid)
{
	new level = PlayerInfo[playerid][pAdvogadoSkill];
	switch(level)
	{
		case 0..19:return 1;
		case 20..99:return 2;
		case 100..149:return 3;
		case 150..249:return 4;
		case 250..369:return 5;
		case 370..499:return 6;
		default:return 7;
	}
	return -1;
}

CMD:cancelar(playerid, x_Emprego[])
{
	if(isnull(x_Emprego))
	{
		SendClientMessage(playerid, -1, "|__________________[ Cancelar ]__________________|");
		SendClientMessage(playerid, -1, "Use: /cancelar [nome]");
		SendClientMessage(playerid, COLOR_GREY, "Nomes Validos: reparo, Advogado, aovivo");
		SendClientMessage(playerid, COLOR_GREY, "Nomes Validos: Policia, convite, ajuda, procura");
		return true;
	}
    new string[128];
	if(strcmp(x_Emprego,"convite",true) == 0)
	{
		InviteOffer[playerid] = 999;
		InviteJob[playerid] = 0;
	}

	else if(strcmp(x_Emprego,"procura",true) == 0)
	{
		stop timer_procurar[playerid];
		HidePlayerSearch(playerid);
		SetPVarInt(playerid, "varProcura", INVALID_PLAYER_ID);

		DestroyDynamicObject(GetPVarInt(playerid, "objectProcurar"));
		SetPVarInt(playerid, "objectProcurar", -1);
		RemovePlayerMapIcon(playerid, 99);
	}

	else if(strcmp(x_Emprego,"ajuda",true) == 0)
	{
		According_Cancel(playerid);
	}
	else if(strcmp(x_Emprego,"aovivo",true) == 0)
	{
		LiveOffer[playerid] = 999;
		valorLiveOffer[playerid] = 0;
	}
	else if(strcmp(x_Emprego,"padrinho",true) == 0)
	{
		MarryWitnessOffer[playerid] = 999;
	}
	else if(strcmp(x_Emprego,"casamento",true) == 0)
	{
		ProposeOffer[playerid] = 999;
	}
	else if (strcmp(x_Emprego,"sexo",true) == 0)
	{
		DoSexOffer[playerid] = 999;
	}
	else if(strcmp(x_Emprego,"divorcio",true) == 0)
	{
		DivorceOffer[playerid] = 999;
	}
	else { return true; }
	format(string, sizeof(string), "* Você cancelou: %s.", x_Emprego);
	SendClientMessage(playerid, COLOR_YELLOW, string);
	return true;
}

CMD:tognews(playerid, params[])
{
	if (!gNoticias[playerid])
	{
		gNoticias[playerid] = 1;
		SendClientMessage(playerid, COLOR_GRAD, "   News CHAT desabilitado  !");
	}
	else if (gNoticias[playerid])
	{
		gNoticias[playerid] = 0;
		SendClientMessage(playerid, COLOR_GRAD, "   News CHAT habilitado  !");
	}
	return 1;
}

CMD:togfam(playerid, params[])
{
	if (!Chat_Organizacao[playerid])
	{
		Chat_Organizacao[playerid] = 1;
		SendClientMessage(playerid, COLOR_GRAD, "   Familia CHAT desabilitado !");
	}
	else if (Chat_Organizacao[playerid])
	{
		Chat_Organizacao[playerid] = 0;
		SendClientMessage(playerid, COLOR_GRAD, "   Familia CHAT abilitado  !");
	}
	return 1;
}

CMD:multar(playerid, params[])
{
	if(!IsACop(playerid) && GetPlayerOrg(playerid) != 16)
		return SendClientMessage(playerid, -1, "Você não é um policial!");
	
	new result[64], valorAssalto, idplayer;
	if (sscanf(params, "uds[64]", idplayer, valorAssalto, result))
		return SendClientMessage(playerid, -1, "Use: /multar [id] [custo] [motivo]");

	if (valorAssalto < 100 || valorAssalto > 500) 
		return SendClientMessage(playerid, -1, "Você deve custear a multa entre $100 a $500");

	if(IsPlayerConnected(idplayer))
	{
		if(Player_GetJailed(idplayer) > 0)
		{
			SendClientMessage(playerid, -1, "Você não pode multar jogadores que estejam presos!");
			return true;
		}
		if (ProxDetectorS(25.0, playerid, idplayer))
		{
			new string[256];
			format(string, sizeof(string), "* Você multou %s por $%d, Razao: %s", PlayerName[idplayer], valorAssalto, result);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			format(string, sizeof(string), "* Oficial %s lhe aplicou uma multa no valor de $%d, Razao: %s", PlayerName[playerid], valorAssalto, (result));
			SendClientMessage(idplayer, COLOR_LIGHTRED, string);
			TicketOffer[idplayer] = playerid;
			TicketMoney[idplayer] = valorAssalto;

			format(string, sizeof(string),
			"* O policial %s está lhe aplicando uma multa de $%d, motivo: %s\n\
			Para aceitar esta multa basta apertar em 'ACEITAR'\n\
			OBS: Caso não aceite, você será procurado por não aceitar a multa!", PlayerName[playerid], valorAssalto, result);
			ShowPlayerDialog(idplayer, 5988, DIALOG_STYLE_MSGBOX, "Multa aplicada", string, "ACEITAR", "RECUSAR");
			return true;
		}
		else
		{
			SendClientMessage(playerid, -1, "O jogador está longe !");
			return true;
		}
	}
	else
	{
		SendClientMessage(playerid, -1, "O jogador está Offline !");
	}
	return true;
}

CMD:noticias(playerid, result[])
{
	if (GetPlayerOrg(playerid) != 9) return SendClientMessage(playerid, -1, "Você não é um reporter da San News.");

	if (isnull(result)) return SendClientMessage(playerid, -1, "Modo de uso: /noticias (texto da noticia)");

   	new vehicleid = GetPlayerVehicleID(playerid);

    if (GetVehicleModel(vehicleid) == 582 || GetPlayerVirtualWorld(playerid) == 509)
	{
   	    new string[256];
		format(string, sizeof(string), "Reporter %s: %s", PlayerName[playerid], result);
		OOCNews(COLOR_ORANGE,string);
	}
	else SendClientMessage(playerid, -1, "Você não está dentro da HQ da San News ou não está em uma Van.");

	return true;
}

CMD:aovivo(playerid, params[])
{
    new valor;

    if (GetPlayerOrg(playerid) != 9) return SendClientMessage(playerid, -1, "Você não é um reporter.");

    if (PlayerInfo[playerid][pCargo] < 2) return SendClientMessage(playerid, -1, "Você precisa ser cargo 2 para fazer um aovivo.");

	new idplayer;
    if (sscanf(params, "ud", idplayer, valor)) return SendClientMessage(playerid, -1, "Modo de uso: /aovivo (id do jogador) (valor)");

    if (valor < 1 || valor > 3000000) return SendClientMessage(playerid, -1, "O valor do aovivo deve ser entre $1 a $3.000.000");

	if (TalkingLive[playerid] != 255)
	{
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "O aovivo foi finalizado.");
		SendClientMessage(TalkingLive[playerid], COLOR_LIGHTBLUE, "O aovivo foi finalizado.");
		TogglePlayerControllable(playerid, true); TogglePlayerControllable(TalkingLive[playerid], true);
		TalkingLive[TalkingLive[playerid]] = 255; TalkingLive[playerid] = 255;
		return true;
	}

	if (!IsPlayerConnected(idplayer)) return SendClientMessage(playerid, -1, "Este jogador não está conectado.");

	if (!ProxDetectorS(5.0, playerid, idplayer)) return SendClientMessage(playerid, -1, "Você não está perto do jogador.");

	if (idplayer == playerid) return 0;

   	new string[128];
	format(string, sizeof(string), "* Você chamou %s para conversar aovivo por %s, aguarde até que ele aceite!", PlayerName[idplayer]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	format(string, sizeof(string), "* %s chamou você para conversar aovivo por $%s (/aceitar aovivo) para aceitar.", PlayerName[playerid], getFormatText(valor));
	SendClientMessage(idplayer, COLOR_LIGHTBLUE, string);

	LiveOffer[idplayer] = playerid;
	valorLiveOffer[idplayer] = valor;

	return true;
}

CMD:ejetar(playerid, params[])
{
    new PLAYER_STATE:State;
    if(IsPlayerInAnyVehicle(playerid))
    {
 		State=GetPlayerState(playerid);
        if(State!=PLAYER_STATE_DRIVER)
        {
        	SendClientMessage(playerid,-1, "Você não é o motorista do carro !");
            return true;
        }
        new playa;
		if(sscanf(params, "u", playa))
		{
			SendClientMessage(playerid, -1, "Use: /ejetar [id]");
			return true;
		}
		new test;
		test = GetPlayerVehicleID(playerid);
		if(IsPlayerConnected(playa))
		{
		    if(playa != INVALID_PLAYER_ID)
		    {
		        if(playa == playerid) { SendClientMessage(playerid, -1, "Você não pode se expulsar... Aperte Enter ¬¬!"); return true; }
		        if(IsPlayerInVehicle(playa,test))
		        {
            	    new string[128];
					format(string, sizeof(string), "* Você expulsou o(a) %s para fora do carro!", PlayerName[playa]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					format(string, sizeof(string), "* Você foi retirado do carro por %s !", PlayerName[playerid]);
					SendClientMessage(playa, COLOR_LIGHTBLUE, string);
					RemovePlayerFromVehicle(playa);
				}
				else
				{
				    SendClientMessage(playerid, -1, "Este jogador não está em seu carro !");
				    return true;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, -1, "ID/Nick - Invalido!");
		}
	}
	else
	{
	    SendClientMessage(playerid, -1, "Você precisa estar em um carro para usar este comando !");
	}
	return true;
}

CMD:invadirfichas(playerid, params[])
{
	if (!PlayerIsMafia(playerid)) return SendClientMessage(playerid, -1, "Você precisa ser mafioso para usar esse comando.");

	new idPlayer;
	if (sscanf(params, "u", idPlayer)) return SendClientMessage(playerid, -1, "Modo de uso: /invadirfichas (id do jogador)");

	if (PlayerInfo[idPlayer][pLimparb] > 0) return SendClientMessage(playerid, -1, "A ficha desse jogador tem uma tentativa de invasão nesse payday.");

	if (PlayerInfo[playerid][pCargo] < 2) return SendClientMessage(playerid, -1, "Você precisa ser cargo 2 ou superior para usar esse comando.");

	if (idPlayer == playerid) return SendClientMessage(playerid, -1, "Você não pode limpar sua própria ficha de crimes.");

	if (!Player_Logado(idPlayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado/logado no servidor.");

 	if (idPlayer != INVALID_PLAYER_ID) {

 	    new
 	        string[128],
			randomFicha = random(4)
		;

		switch(randomFicha)
		{
			case 2, 3:
			{
                format(string, sizeof(string), "(( %s invadiu o sistema de fichas criminais e conseguiu ))", PlayerName[playerid]);
				SendClientMessageInRange(20.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

				format(string, sizeof(string), "* %s, %s da %s limpou a sua ficha criminal.", GetPlayerCargo(playerid), PlayerName[playerid], GetOrgName(playerid));
				SendClientMessage(idPlayer, COLOR_LIGHTBLUE, string);

				Player_SetWanted(idPlayer, 0);
				
				ClearCrime(idPlayer);
			}
			default:
			{
			    format(string, sizeof(string), "(( %s tentou invadir o sistema de fichas criminais e não conseguiu ))", PlayerName[playerid]);
				SendClientMessageInRange(20.0, playerid, string, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT, COR_ACAOCHAT);

				format(string, sizeof(string), "* %s, %s da %s tentou limpar sua ficha criminal mas não conseguiu.", GetPlayerCargo(playerid), PlayerName[playerid], GetOrgName(playerid));
				SendClientMessage(idPlayer, COLOR_LIGHTBLUE, string);
			}
		}

		PlayerInfo[idPlayer][pLimparb] = 1;
		SetPlayerCriminal(playerid, 255, "Invasão de fichas criminais", 2);
	}
	return true;
}

CMD:contrato(playerid, params[])
{
	new respeitoContrato, valorContrato, nomeOrganizacao[8];

	new idplayer;
	if (sscanf(params, "udds[8]", idplayer, valorContrato, respeitoContrato, nomeOrganizacao))
	{
		SendClientMessage(playerid, -1, "Modo de uso: /contrato (id do jogador) (valor) (respeitos) (organização)");
		SendClientMessage(playerid, -1, "| organização: Hitman ou Triad | (novidade) respeitos: você pagará ao assassino.");

		return true;
	}

	if (!IsPlayerConnected(idplayer)) return SendClientMessage(playerid, -1, "O jogador não está conectado no servidor.");

	if (!Player_Logado(idplayer)) return SendClientMessage(playerid, -1, "O jogador não está logado no servidor.");

	if (PlayerInfo[idplayer][pHeadValue] > 0 || PlayerInfo[idplayer][pHeadValueT] > 0) return SendClientMessage(playerid, -1, "Esse jogador já está com um contrato pela sua cabeça.");

	if (valorContrato < 10000 || valorContrato > 100000) return SendClientMessage(playerid, -1, "O valor do contrato deve estar entre $10.000 a $100.000");

	if (respeitoContrato < 0 || respeitoContrato > 3) return SendClientMessage(playerid, -1, "A quantidade de respeito deve ser entre 0 a 3.");

	if (PlayerInfo[playerid][pExp] < respeitoContrato) return SendClientMessage(playerid, -1, "Você não tem essa quantidade de respeitos em seu RG.");

	if (Player_GetMoney(playerid) < valorContrato) return SendClientMessage(playerid, -1, "Você não tem esse valor em mãos.");

   	new string[128];

	if (gettime() < PlayerInfo[idplayer][pLastContrato]) {
		format(string, sizeof string, "Aviso: Você precisa esperar {FFFF00}%d {FFFFFF}para colocar contrato em %s", PlayerInfo[idplayer][pLastContrato] - gettime(), PlayerName[idplayer]);
		SendClientMessage(playerid, -1, string);
		return true;
	}

	if (idplayer == playerid) return SendClientMessage(playerid, -1, "Você não pode colocar contrato em si mesmo.");

	if (GetPlayerOrg(idplayer) == GetPlayerOrg(playerid) && GetPlayerOrg(idplayer) != 0) return SendClientMessage(playerid, -1, "Você não pode colocar contrato em membros da sua organização.");

	if (GetPlayerOrg(idplayer) == 8 || GetPlayerOrg(idplayer) == 22) return SendClientMessage(playerid, -1, "Você não pode colocar contrato em assassinos.");

	if (GetPlayerOrg(playerid) == 8 || GetPlayerOrg(playerid) == 22) return SendClientMessage(playerid, -1, "Você não pode fazer contratos pois é um assassino.");

	if (Staff_GetWorking(idplayer))
		return SendClientMessage(playerid, -1, "Você não pode colocar contrato em administradores ou helpers.");

    if (!GetPlayerOrg(idplayer) && PlayerInfo[idplayer][pLevel] < 5) return SendClientMessage(playerid, -1, "Você não pode colocar contrato em cívis level menor que 5.");

	if (IsPlayerInSafeZone(idplayer) || GetPlayerVirtualWorld(idplayer) == 10061) 
		return SendClientMessage(playerid, -1, "Você não pode fazer isso em um jogador que está na Área Segura.");

	if (IsACop(idplayer) && valorContrato < 50000) return SendClientMessage(playerid, -1, "O valor em policias deve ser igual ou maior que $50.000");

	if (strcmp(nomeOrganizacao, "Hitman", true) == 0)
	{
       	Player_RemoveMoney(playerid, valorContrato);
       	PlayerInfo[playerid][pExp] -= respeitoContrato;
       	PlayerInfo[idplayer][pHeadValue] += valorContrato;
		PlayerInfo[idplayer][pHeadRespect] += respeitoContrato;
       	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

       	format(string, sizeof(string), "(Agência): Contrato manual disponível em %s[%d], valor: $%s e %d respeitos.", PlayerName[idplayer], idplayer, getFormatText(valorContrato), respeitoContrato);
       	SendMembersMessage(8, COLOR_YELLOW, string);

		format(string, sizeof(string), "(Agência): Você solicitou um contrato em %s[%d], por $%s e %d respeitos.", PlayerName[idplayer], idplayer, getFormatText(valorContrato), respeitoContrato);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

		format(string, sizeof(string), "(Contratos): %s colocou contrato em $%s por %s e %d respeitos.", PlayerName[playerid], PlayerName[idplayer], getFormatText(valorContrato), respeitoContrato);
		server_log("contratos", string);
    	return true;
	}
	else if (strcmp(nomeOrganizacao, "Triad", true) == 0)
	{
       	Player_RemoveMoney(playerid, valorContrato);
       	PlayerInfo[playerid][pExp] -= respeitoContrato;
   		PlayerInfo[idplayer][pHeadValueT] += valorContrato;
   		PlayerInfo[idplayer][pHeadRespectT] += respeitoContrato;
   		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

 		format(string, sizeof(string), "(Agência): Contrato manual disponível em %s[%d], valor: $%s e %d respeitos.", PlayerName[idplayer], idplayer, getFormatText(valorContrato), respeitoContrato);
 		SendMembersMessage(22, COLOR_YELLOW, string);

      	format(string, sizeof(string), "(Agência): Você solicitou um contrato em %s[%d], por $%s e %d respeitos.", PlayerName[idplayer], idplayer, getFormatText(valorContrato), respeitoContrato);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);

		format(string, sizeof(string), "%s colocou contrato em %s por $%s e %d respeitos.", PlayerName[playerid], PlayerName[idplayer], getFormatText(valorContrato), respeitoContrato);
		server_log("contratos", string);
		return true;
	}
	else {

	    SendClientMessage(playerid, -1, "Modo de uso: /contrato (id do jogador) (valor) (respeitos) (organização)");
		SendClientMessage(playerid, -1, "| organização: Hitman ou Triad | {00FF00}(novidade) {FFFFFF}respeitos: você pagará ao assassino.");
		return true;
	}
}

task AutoContratos[60000 * 5]()
{
    new Iterator:IterPlayers<MAX_PLAYERS>;
    new string[128];

    foreach(new x : Player)
	{
        if (Player_Logado(x) && GetPlayerOrg(x) != 8 && GetPlayerOrg(x) != 22 && PlayerInfo[x][pConnectTime] > 10)
		{
			if ((Admin_GetNivel(x) || Helper_GetNivel(x) && Staff_GetWorking(x)) || !GetPlayerOrg(x) || GetPlayerOrg(x) == 7 || GetPlayerOrg(x) == 16 || GetPlayerOrg(x) == 9 ||
				gettime() < PlayerInfo[x][pLastContrato] || PlayerInfo[x][pHeadValue] > 0 || PlayerInfo[x][pHeadValueT] > 0 || GetPlayerVirtualWorld(x) == 10061) continue;

			Iter_Add(IterPlayers, x);
        }
    }

    if (Iter_Count(IterPlayers))
	{
        new playerid = Iter_Random(IterPlayers);
        new valor = 10000 + random(30000);


        PlayerInfo[playerid][pHeadValueT] += valor;
        PlayerInfo[playerid][pHeadRespectT] = random(2);
        format(string, sizeof(string), "(Agência): Contrato automático disponível em %s(%d), valor: $%s e 0 respeitos.",PlayerName[playerid], playerid, getFormatText(valor));
        SendMembersMessage(22, COLOR_YELLOW, string);

        playerid = Iter_Random(IterPlayers);
        valor = 10000 + random(30000);

        PlayerInfo[playerid][pHeadValue] += valor;
        PlayerInfo[playerid][pHeadRespect] = random(2);
        format(string, sizeof(string), "(Agência): Contrato automático disponível em %s(%d), valor: $%s e 0 respeitos.",PlayerName[playerid], playerid, getFormatText(valor));
        SendMembersMessage(8, COLOR_YELLOW, string);
    }
    return true;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	if (!Player_Logado(playerid) && strcmp(cmd, "/logar", true) != 0)
		return SendClientMessage(playerid, COLOR_GRAD, "Você precisa estar logado, use: /logar."), false;

	Logger_Dbg("commands", "player command received",
		Logger_S("name", PlayerName[playerid]),
		Logger_I("id", playerid),
		Logger_S("text", cmd));
	
	if (Admin_GetNivel(playerid) < DONO) {
		if (GetPVarInt(playerid, "VarPlayerOcupado") || GetPlayerBeingAbducted(playerid) || (PlayerInEvento(playerid) && !Admin_GetNivel(playerid)) || DanoInfo[playerid][danoKilled])
			return SendClientMessage(playerid, COLOR_LIGHTRED, "* Você não pode usar comandos agora!"), false;

		if (Player_GetJailed(playerid)) {

			if (Player_GetJailed(playerid) != 9) {
				if (strcmp(cmd, "/atendimento", true) != -1 || strcmp(cmd, "/ajuda", true) != -1 || strcmp(cmd, "/relatorio", true) != -1 ||
					strcmp(cmd, "/menu", true) != -1 || strcmp(cmd, "/terminar atendimento", true) != -1 || strcmp(cmd, "/radio", true) != -1 ||
					strcmp(cmd, "/n", true) != -1 || strcmp(cmd, "/s", true) != -1 || strcmp(cmd, "/admins", true) != -1) {

					SendClientMessage(playerid, COLOR_LIGHTRED, "Você está preso. Apenas os comandos abaixo estão liberados:.");
					SendClientMessage(playerid, COLOR_LIGHTRED, "/atendimento /terminar atendimento /ajuda /relatorio /menu /radio /rg /s /n /admins.");
					return 1;
				}
			} else {
				if (strcmp(cmd, "/atendimento", true) != -1 || strcmp(cmd, "/ajuda", true) != -1 || strcmp(cmd, "/relatorio", true) != -1 || 
					strcmp(cmd, "/menu", true) != -1 || strcmp(cmd, "/terminar atendimento", true) != -1 || strcmp(cmd, "/radio", true) != -1 ||
					strcmp(cmd, "/rg", true) != -1 || strcmp(cmd, "/s", true) != -1 || strcmp(cmd, "/admins", true) != -1) {

					SendClientMessage(playerid, COLOR_LIGHTRED, "Você está preso. Apenas os comandos abaixo estão liberados:.");
					SendClientMessage(playerid, COLOR_LIGHTRED, "/atendimento /terminar atendimento /ajuda /relatorio /menu /radio /rg /s /admins.");
					return 1;
				}
			}
			return SendClientMessage(playerid, COLOR_LIGHTRED, "Esse comando não é permitido estando preso."), false;
		}
	}
	return 1;
}

CALLBACK:playerIsFamily(playerid)
{
	new id = GetPlayerFamily(playerid);

	if (id != -1) 
		return true;

	return false;
}

stock ShowAdvogado(playerid, delegacia)
{
	if (!PlayerIsAdvogado(playerid)) 
		return SendClientMessage(playerid, -1, "Você não é um advogado.");

	if (GetPlayersInJail(delegacia) < 1)
		return SendClientMessage(playerid, -1, "Não há presos nessa delegacia!");

    new string[128];
	new count;

	MEGAString[0] = EOS;

   	strcat(MEGAString, "Data da prisão\tNome\tTempo de prisão\tSituação\n");

	foreach(new i : Player) {
		if (Player_GetJailed(i) == delegacia) {
			List_SetPlayers(playerid, count, i);

			if (PlayerInfo[i][pAjustado])
			    format(string, sizeof string, "{9C9C9C}%s\t{FFFFFF}%s\t{FF0000}%s (%d segundos)\t{43E846}(Julgado)\n", PlayerInfo[i][pPrisaoData], PlayerName[i], ConvertTime(PlayerInfo[i][pJailTime]), PlayerInfo[i][pJailTime]);
			else
				format(string, sizeof string, "{9C9C9C}%s\t{FFFFFF}%s\t{FF0000}%s (%d segundos)\t{4F79E1}(Aguardando)\n", PlayerInfo[i][pPrisaoData], PlayerName[i], ConvertTime(PlayerInfo[i][pJailTime]), PlayerInfo[i][pJailTime]);

			strcat(MEGAString, string);

			count ++;
		}
	}
	format(string, sizeof string, " {FFFFFF}Presos ({FF0000}%d{FFFFFF})", count);
	ShowPlayerDialog(playerid, 4587, DIALOG_STYLE_TABLIST_HEADERS, string, MEGAString, "Ajustar", "Cancelar");
	return 1;
}

CALLBACK: eContinuar(playerid)
{
	new Float: Vel[3];

	GetPlayerVelocity(playerid, Vel[0], Vel[1], Vel[2]);
	SetPlayerVelocity(playerid, Vel[0], Vel[1], Vel[2] + 25.0);

    ApplyAnimation(playerid, "FOOD","FF_Sit_Loop", 4.0, true, true, true, false, 0);

	return 1;
}

stock IsPlaneInAir(planeid)
{
	new Float: pos[4];
	GetVehiclePos(planeid, pos[0], pos[1], pos[2]);

	MapAndreas_FindZ_For2DCoord(pos[0], pos[1], pos[3]);

	if(floatsub(pos[2], pos[3]) > 20) return 1;

	return 0;
}

CALLBACK: eTerminar(playerid, vehicleid, explode)
{
	KillTimer(eEjet[playerid]);

	eEjet[playerid] = -1;
	ClearAnimations(playerid);

	if(!IsVehicleOccupied(vehicleid)) SetVehicleHealth(vehicleid, 0.0);

	return 1;
}

CALLBACK:BackupClear(playerid, calledbytimer)
{
	if(IsPlayerConnected(playerid))
	{
		if(IsACop(playerid))
		{
			if (PlayerInfo[playerid][pRequestingBackup] == 1)
			{
				foreach(new i : Player)
				{
                    if(IsACop(playerid))
					{
						SetPlayerMarkerForPlayer(i, playerid, TEAM_HIT_COLOR);
					}
				}
				if (calledbytimer != 1)
				{
					SendClientMessage(playerid, TEAM_BLUE_COLOR, "Seu pedido de reforço foi cancelado.");
				}
				else
				{
					SendClientMessage(playerid, TEAM_BLUE_COLOR, "Seu pedido de reforço foi cancelado automaticamente.");
				}
				PlayerInfo[playerid][pRequestingBackup] = 0;
			}
			else
			{
				if (calledbytimer != 1)
				{
					SendClientMessage(playerid, -1, "Você ainda não pediu reforço.");
				}
			}
		}
		else
		{
			if (calledbytimer != 1)
			{
				SendClientMessage(playerid, -1, "Você não é COP");
			}
		}
	}
	return true;
}

CALLBACK:SairHospital(playerid) 
{
	new
		string[65];

	PlayerInfo[playerid][pHospital] = false;
	PlayerInfo[playerid][pTempoHospital] = 0;
	PlayerTextDrawHide(playerid, TextHospital[playerid]);
	SetPlayerHealth(playerid, 100);
	SendClientMessage(playerid, -1, "|______________ Contas do Hospital______________| ");
	format(string, sizeof string, "|* Paciente %s", PlayerName[playerid]);
	SendClientMessage(playerid, COLOR_GRAD, string);
	format(string, sizeof string, "|* Você recebeu alta em: %s", GetCurrentDateHour(ONLY_CURRENT_ALL));
	SendClientMessage(playerid, COLOR_GRAD, string);
	format(string, sizeof string, "|* Custo Total: -$%d", customorte[playerid]);
	SendClientMessage(playerid, COLOR_GRAD, string);
	SendClientMessage(playerid, -1, "|______________________________________________|");
	SendClientMessage(playerid, COLOR_YELLOW, "Você saiu do hospital depois de um tempo internado.");
	Player_RemoveMoney(playerid, customorte[playerid]);
	SetPVarInt(playerid, "VarMSG", 0);

	SetPlayerPos(playerid, 1131.1443, -1741.1129, 13.8090);
	SetPlayerFacingAngle(playerid, 266.8522);
	SetPlayerCameraPos(playerid, 1141.4489, -1743.0889, 17.5619);
	SetPlayerCameraLookAt(playerid, 1136.0024, -1741.1626, 13.7707);
	SetPlayerVirtualWorld(playerid, 0);

	ApplyAnimation(playerid,"PED","WALK_player", 4.1, true, true, true, true, 0, SYNC_ALL);
	SetTimerEx("endHospital", 3200, false, "d", playerid);
	ShowPlayerBaloonInfo(playerid, "Voce recebeu alta do hospital", 5000);

	return 1;
}

CALLBACK: endHospital(playerid) 
{
	ClearAnimations(playerid);
	TogglePlayerControllable(playerid, true);
	SetCameraBehindPlayer(playerid);

	if (Player_GetJailed(playerid)) {
		SpawnPlayer(playerid);
		return 1;
	}

	if (IsPlayerHaveItem(playerid, ITEM_TYPE_CONTRATO)) 
	{
		ShowPlayerDialog(playerid, 132, DIALOG_STYLE_MSGBOX, "Contrato Hospitalar",
		"\n{FF6600}MENSAGEM DO HOSPITAL:\n\n{FFFFFF}Você possui um {00FFFF}Contrato Hospitalar {FFFFFF}e pode usá-lo!\n\n\
		{FF5500}OBS: {999999}O contrato hospitalar consiste em levar você\npara o local de spawn pelos médicos, deseja usá-lo?", "Usar", "Cancelar");
	}

	return 1;
}

#include <edit_object>

CALLBACK: OnDiscordLink(playerid)
{
	return 1;
}