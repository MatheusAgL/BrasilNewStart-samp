
// Local de pegar emprego
#define		WORKING_POS_X					1370.7482
#define		WORKING_POS_Y					-1760.6443
#define		WORKING_POS_Z					13.6598

// Local de inscrever para casinhas do governo
#define 	SUBSHOUSE_POS_X 				358.9051
#define 	SUBSHOUSE_POS_Y 				167.8140
#define 	SUBSHOUSE_POS_Z					1008.3828

new PDDOORa;
new PDDOORb;
new PDDOORc;
new PDPMLS;
new PortaoPMSF;

new Text3D:OwnerMercadoNegroText, Text3D:OwnerFabricaMateriaisText;

new actorBanco[6],
	actorFarmacia[4];

stock CreateDynamicObjectMBR(model, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    new obj = CreateDynamicObject(model, x, y, z,   rx, ry, rz);
    SetDynamicObjectMaterial(obj, 0, 8399, "vgs_shops", "villainnwall02_128", 0);
    return obj;
}

stock Create3DTextsLabelsOfServer() {
	// Servidor: Geral
	CreateDynamic3DTextLabel("GALÃO DE 5 LITROS\n\n{FFFFFF}Use: {E9ED19}/comprar galao\n{FFFFFF}Valor: {00AA00}$80", 0xEB3F21FF, 1941.6409, -1764.9487, 13.6406, 10.0);

	// novo banco
    CreateDynamic3DTextLabel("Aperte 'Y' para abrir ou fechar o cofre", 0xFFFFFFAA, 1447.1038, -1123.0455, 23.9590, 4.0);// Laser's Cofre Roubo
	// Locais de roubos: Laser do cofre
    CreateDynamic3DTextLabel("Aperte 'Y' para desativar os lasers", 0xFFFFFFAA, 2146.64551, 1612.74670, 835.40332, 4.0);// Laser's Cofre Roubo
    CreateDynamic3DTextLabel("Aperte 'Y' para abrir o cofre", 0xFFFFFFAA, 2146.67065, 1633.03381, 835.57257, 4.0);// Laser's Cofre Roubo
    CreateDynamic3DTextLabel("Use /explodircofre para tentar explodir a porta",0xFFFFFFAA, 2148.09399, 1633.38513, 835.75317, 5.0);// Laser's Cofre Roubo

	// Organização: Polícia Rodoviária
	CreateDynamic3DTextLabel("Use {00FFFF}/verificar placa {FFFFFF}para consultar uma placa", 0xFFFFFFFF, 219.1412,110.7154,1010.2118,6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 16); 
	CreateDynamic3DTextLabel("Use {00FFFF}/verificar patio {FFFFFF}para consultar o pátio", 0xFFFFFFFF, 224.3456,109.2041,1010.2188,6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 16); 
	CreateDynamic3DTextLabel("Use {00FFFF}/apreenderveiculo {FFFFFF}para fazer a apreensão do veículo", 0xFFFFFFFF, 2270.9304,-105.9503,26.4766,8.0); 

	// Departamento de Veículos
	CreateDynamic3DTextLabel("Use {00FFFF}/verificar placa {FFFFFF}neste local", 0xFFFFFFFF, 221.4195,114.2523,1010.2188,6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 1000); 
	                                                   		// Polícia Rodoviária (verificar placa)
	// Skins loja de roupas
    CreateDynamic3DTextLabel("{FFFFFF}Loja de Roupas\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para escolher outra skin",0xFFFFFFFF, 161.5581,-83.5712,1001.8047,5.0);
    CreateDynamicPickup(1275, 23, 210.4596,-100.4582,1005.2578);//Skin binco
	CreateDynamic3DTextLabel("{FFFFFF}Loja de Roupas\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para escolher outra skin",0xFFFFFFFF, 210.4596,-100.4582,1005.2578,5.0);
    CreateDynamicPickup(1275, 23, 161.5581,-83.5712,1001.8047);//Skin ZIP
	CreateDynamic3DTextLabel("{FFFFFF}Loja de Roupas\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para escolher outra skin",0xFFFFFFFF, 202.4701,-136.1887,1002.8744,5.0);
    CreateDynamicPickup(1275, 23, 202.4701,-136.1887,1002.8744);//Skin ProLaps
    CreateDynamic3DTextLabel("{FFFFFF}Loja de Roupas\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para escolher outra skin",0xFFFFFFFF, 206.3915,-9.2168,1001.2109,5.0);
    CreateDynamicPickup(1275, 23, 206.3915,-9.2168,1001.2109);//Skin Victim
    CreateDynamic3DTextLabel("{FFFFFF}Loja de Roupas\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para escolher outra skin",0xFFFFFFFF, 204.3578,-159.3506,1000.5234,5.0);
    CreateDynamicPickup(1275, 23, 204.3578,-159.3506,1000.5234);//Skin DSs
	// Abrir portao do apartamento
    CreateDynamic3DTextLabel("Use /portaopredio para abrir",0xFFFFFF70, 262.5076,-1639.5582,19.4608, 10.0);
	// Seguradora
	CreateDynamic3DTextLabel("{FFFFFF}Seguradora de Veículos\n{FFFFFF}Use o comando {00FFFF}/veiculo seguro {FFFFFF}para comprar um seguro para seu veículo!",0xFFFFFFFF, 1167.3950,1348.2433,673.3744,5.0);
    CreateDynamicPickup(1239,23,1167.3950,1348.2433,673.3744,-1) ; // Seguradora
	// Revendedora
	CreateDynamic3DTextLabel("{FFFFFF}Revendedora\n{FFFFFF}Use o comando {00FFFF}/veiculo revender {FFFFFF}para revender um de seus veículos!",0xFFFFFFFF, 1167.8572,1342.1548,673.3744,5.0);
    CreateDynamicPickup(1239,23,1167.8572,1342.1548,673.3744,-1) ; // Revendedora
	// Comprar contrato hospitalar
 	CreateDynamic3DTextLabel("{FFFFFF}Contrato Hospitalar\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para comprar um contrato",0xFFFFFFFF, 1064.0251, -1754.7593, 13.7404,3.0);
    CreateDynamicPickup(2894, 23, 1064.0251, -1754.7593, 13.7404,-1) ; // contrato hospitalar
	// Mercado Negro
    CreateDynamic3DTextLabel("{FFFFFF}Mercado Negro\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para comprar algo",0xFFFFFFFF, 941.9362,2176.6089,1011.0234,10.0);
    CreateDynamicPickup(1254, 23, 941.9362,2176.6089,1011.0234); // Comprar itens mercado negro
    OwnerMercadoNegroText = CreateDynamic3DTextLabel("{FFFFFF}Use o comando {00FFFF}/dominar{FFFFFF} para dominar este local\nOrganização dona: {00FFFF}Nenhuma",0xFFFFFF77, 942.3033,2163.3245,1012.2277,20.0);
    CreateDynamic3DTextLabel("{FFFFFF}Processar maconha\n{FFFFFF}Use a maconha {00FFFF}SEMI-PRONTA {FFFFFF}aqui para processá-la",0xFFFFFFFF, 944.5869,2176.7280,1011.0234,10.0);
    CreateDynamicPickup(2901, 23, 944.5869,2176.7280,1011.0234); // Processar maconha

    OwnerFabricaMateriaisText = CreateDynamic3DTextLabel("Fábrica de Materiais\n\n{FFFFFF}Use: {E3DA7B}/dominar{FFFFFF} para tomar o local\nNenhuma organização dominou", 0x89DFE5F9, -961.3480,1907.2937,9.8657,20.0);

	// Empregos
	CreateDynamic3DTextLabel("Agencia de Empregos\n{FFFFFF}Aperte a tecla "_KEY_PATH_USE_HORN_COLOR" {FFFFFF}para pegar um emprego", 0xFFFFFFFF, WORKING_POS_X, WORKING_POS_Y, WORKING_POS_Z, 6.0);
    CreateDynamicPickup(1210, 23, WORKING_POS_X, WORKING_POS_Y, WORKING_POS_Z); // Maleta dentro da agência

    CreateDynamic3DTextLabel("Comprar Produtos\n{FFFFFF}Use: {E3DA7B}/materiais produtos {FFFFFF}para comprar materiais", 0xDBA75BFF, -960.2817, 1855.4542, 9.0000, 6.0);
    CreateDynamicPickup(3014, 23, -960.2817, 1855.4542, 9.0000);

    CreateDynamic3DTextLabel("Aluguel de caminhões\n{FFFFFF}Pressione {8FAF73}"_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para alugar um caminhão", 0xE7EEE1FF, 1398.5177, 1046.8518, 10.8203, 15.0);
	CreateDynamicPickup(1318, 23, 1398.5177, 1046.8518, 10.8203);

	CreateDynamic3DTextLabel("Central de Caminhoneiros\n{FFFFFF}Pressione {8FAF73}"_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para acessar", 0xE7EEE1FF, 1426.1326,1090.9473,10.8203, 15.0);
	CreateDynamicPickup(1318, 23, 1426.1326,1090.9473,10.8203);

    CreateDynamic3DTextLabel("Ponto de Compra [1]\n{FFFFFF}Use {8FAF73}/comprarprodutos {FFFFFF}para carregar o caminhão", 0xE7EEE1FF, 1389.4375, 1173.9647, 10.7415, 30.0);
	CreateDynamic3DTextLabel("Ponto de Compra [2]\n{FFFFFF}Use {8FAF73}/comprarprodutos {FFFFFF}para carregar o caminhão", 0xE7EEE1FF, 1486.5421, 993.5022, 10.8203, 30.0);

	// Lotérica
	CreateDynamic3DTextLabel("{FFFFFF}Use {00FFFF}/loterica {FFFFFF}para pagar suas despesas",0xFFFFFFFF, 822.0084,6.3861,1004.1797,6.0);
    CreateDynamic3DTextLabel("{FFFFFF}Use {00FFFF}/loterica {FFFFFF}para pagar suas despesas",0xFFFFFFFF, 822.0084,4.1540,1004.1797,6.0);
    CreateDynamic3DTextLabel("{FFFFFF}Use {00FFFF}/loterica {FFFFFF}para pagar suas despesas",0xFFFFFFFF, 822.0085,1.8853,1004.1797,6.0);
    CreateDynamic3DTextLabel("{FFFFFF}Use {00FFFF}/loterica {FFFFFF}para pagar suas despesas",0xFFFFFFFF, 822.0086,-0.3084,1004.1797,6.0);
    CreateDynamicPickup(1274,23,822.0084,6.3861,1004.1797,-1) ; // Lotérica
    CreateDynamicPickup(1274,23,822.0084,4.1540,1004.1797,-1) ; // Lotérica
    CreateDynamicPickup(1274,23,822.0085,1.8853,1004.1797,-1) ; // Lotérica
    CreateDynamicPickup(1274,23,822.0086,-0.3084,1004.1797,-1) ; // Lotérica
	
	// Interior enforcer
	CreateDynamic3DTextLabel("Use /equipar para equipar-se", 0xFFFFFFFF, -27.5506, 40.9372, 1000.2366, 3.0);
	
	// Outros
    CreateDynamic3DTextLabel("{FFFFFF}Polícia Rodoviária Federal\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,919.4673,-1252.2612,16.2109, 10.0);
	CreateDynamic3DTextLabel("{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para sair",0xFFFFFFFF, 1494.4199,1304.1959,1093.2891, 6.0);// agencia de empregos - saida
	CreateDynamic3DTextLabel("{FFFFFF}Prisão La Sante\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,1800.0864,-1578.3821,14.0739, 30.0);
    Create3DTextLabel("{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para sair do presídio",0xFFFFFFFF,344.7534,39.0710,1001.5156, 15.0, 99);
    CreateDynamic3DTextLabel("{FFFFFF}HQ Aztecas\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,1684.8771,-2098.8760,13.8343,15);
	
	CreateDynamic3DTextLabel("{FFFFFF}Bater Cartão\n{FFFFFF}Aperte "_KEY_PATH_ENTER_INT_COLOR" ou use {00FFFF}/batercartao {FFFFFF}neste local",0xFFFFFFFF,1530.3060,-1702.4915,6.2252,8.0);
    CreateDynamic3DTextLabel("{FFFFFF}Bater Cartão\n{FFFFFF}Aperte "_KEY_PATH_ENTER_INT_COLOR" ou use {00FFFF}/batercartao {FFFFFF}neste local",0xFFFFFFFF,240.6516,112.8062,1003.2188,8.0);
    CreateDynamic3DTextLabel("{FFFFFF}Bater Cartão\n{FFFFFF}Aperte "_KEY_PATH_ENTER_INT_COLOR" ou use {00FFFF}/batercartao {FFFFFF}neste local",0xFFFFFFFF,1585.4412,-1692.0966,-21.0029,8.0);
	CreateDynamic3DTextLabel("{FFFFFF}Bater Cartão\n{FFFFFF}Aperte "_KEY_PATH_ENTER_INT_COLOR" ou use {00FFFF}/batercartao {FFFFFF}neste local",0xFFFFFFFF,-1346.8774,491.9250,11.2027,25.0);
	CreateDynamic3DTextLabel("{FFFFFF}Bater Cartão\n{FFFFFF}Aperte "_KEY_PATH_ENTER_INT_COLOR" ou use {00FFFF}/batercartao {FFFFFF}neste local",0xFFFFFFFF,359.1856,211.4973,1008.3829,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}Bater Cartão\n{FFFFFF}Aperte "_KEY_PATH_ENTER_INT_COLOR" ou use {00FFFF}/batercartao {FFFFFF}neste local",0xFFFFFFFF,255.1123,77.4241,1003.6406,8.0);
	CreateDynamic3DTextLabel("{FFFFFF}Bater Cartão\n{FFFFFF}Aperte "_KEY_PATH_ENTER_INT_COLOR" ou use {00FFFF}/batercartao {FFFFFF}neste local",0xFFFFFFFF,230.3021,165.0272,1003.0234,8.0);
	CreateDynamic3DTextLabel("{FFFFFF}Bater Cartão\n{FFFFFF}Aperte "_KEY_PATH_ENTER_INT_COLOR" ou use {00FFFF}/batercartao {FFFFFF}neste local",0xFFFFFFFF,226.2034,121.5204,1010.2188,8.0);

	CreateDynamic3DTextLabel("{FFFFFF}Aperte a tecla {00FFFF}ENTER {FFFFFF}neste local para equipar",0xFFFFFFFF,211.2608,185.8552,1003.0313,15.0);
    CreateDynamic3DTextLabel("{FFFFFF}Ginásio de Lutas\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para mudar seu estilo de lutar",0xFFFFFFFF,768.2192,-3.9873,1000.7203,15.0);
    CreateDynamic3DTextLabel("{FFFFFF}Departamento de Polícia Militar\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,1553.3007,-1675.7654,16.1953,40.0);
    CreateDynamic3DTextLabel("{FFFFFF}Governo de Los Santos\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,1478.7834,-1783.3513,13.5400,30.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ dos BAIRRO-13\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,2808.3562,-1176.4606,25.3687,20.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ dos Familia do Norte\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,-201.4692, -1092.9031, 25.2115,20.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ da Máfia Yakuza\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,690.7985,-1275.9355,13.5602,20.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ da Máfia Italiana\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF, 289.8943, -1373.6874, 14.8122,20.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ da P.C.C\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,1325.5382, -3031.5596, 8.5836,20.0);
	CreateDynamic3DTextLabel("{FFFFFF}Departamento da Polícia Federal\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,1124.7544,-2036.9777,69.8833,25.0);
	// CreateDynamic3DTextLabel("{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para sair do hospital",0xFFFFFFFF,1175.8210,-1325.9398,-44.2836, 10.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ da G.R.O.T.A\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,2590.2910, -1494.0944, 16.8114,25.0);
	CreateDynamic3DTextLabel("{FFFFFF}Mercado 24/7\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para ver o menu",0xFFFFFFFF,-26.8819,-89.6936,1003.5469,25.0);
	CreateDynamic3DTextLabel("{FFFFFF}Mercado 24/7\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para ver o menu",0xFFFFFFFF,1394.1488,-24.8331,1000.9177,25.0);
	CreateDynamic3DTextLabel("{FFFFFF}Elevador\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para usar",0xFFFFFFFF,1524.4977,-1677.9469,6.2188,10.0);
	CreateDynamic3DTextLabel("{FFFFFF}Elevador\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para usar",0xFFFFFFFF,1565.1235,-1666.9944,28.3956,10.0);
	CreateDynamic3DTextLabel("{FFFFFF}Elevador\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para usar",0xFFFFFFFF,246.4990, 88.0087, 1003.6406,10.0);
	CreateDynamic3DTextLabel("{FFFFFF}Menu de Licenças\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para ver o menu",0xFFFFFFFF,-2033.3137,-117.4329,1035.1719,20.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ do Estado Islamico\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,-594.6794,-1057.1132,23.3562,20.0);
	CreateDynamic3DTextLabel("{FFFFFF}Bar da Sons Of Anarchy\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,2485.6860,89.4010,26.7737,20.0);
	CreateDynamic3DTextLabel("{FFFFFF}Bar da Warlocks\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,681.6184,-474.1958,16.5363,20.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ da Triad\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,2770.6521,-1628.1273,12.1775,20.0);
	CreateDynamic3DTextLabel("{FFFFFF}Use o comando {00FFFF}/limparficha {FFFFFF}para limpar a ficha de alguém",0xFFFFFFFF,1584.7238,-1674.6664,-20.9991,3);
	CreateDynamic3DTextLabel("{FFFFFF}Use o comando {00FFFF}/limparficha {FFFFFF}para limpar a ficha de alguém",0xFFFFFFFF,234.8419,111.2194,1003.2257,3);

	CreateDynamic3DTextLabel("{00FFFF}Motel\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR"{FFFFFF} para entrar", 0xFFFFFFFF,2233.0254,-1159.8149,25.8906,25.0); // Motel
	CreateDynamic3DTextLabel("{00FFFF}Motel -{FFFFFF} Sexo\n{FFFFFF}Use o comando {FFFF00}/convidarsexo {FFFFFF}para convidar sua parceira(o) para fazer sexo",0xFFFFFFFF,2217.3367,-1146.8258,1025.7969,10.0); // Pickup Sexo

	CreateDynamic3DTextLabel("{FFFFFF}HQ {FF1493}Staff\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,-2385.7024,2215.9673,4.9844,20.0); // HQ Staff

	CreateDynamic3DTextLabel(
		""C_YELLOW"[ PRESENTE ]\n\n\
		"C_WHITE"Aperte "_KEY_PATH_ENTER_INT_COLOR" "C_WHITE"para pegar seu presente\n\
		"C_ARRAIA"Vem para o Arraia do BNS! <3", 0xFFFFFFFF, 1479.1299,-1631.8226,14.7433, 15.0);
	CreateDynamicPickup(19343, 24, 1479.1299,-1631.8226,14.7433);

    CreateDynamic3DTextLabel("{FFFFFF}[Area para Médicos]\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para ajustar os pacientes",0xFFFFFFFF,1130.1991, -1733.0205, 13.8090,10.0);

    CreateDynamic3DTextLabel("{FFFFFF}HQ dos Reporteres\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF, 649.3264,-1353.8356,13.5470,20.0);

    CreateDynamic3DTextLabel("{FFFFFF}HQ da Al-Qaeda\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,-329.7025,1536.6123,76.6117,20.0);

	CreateDynamic3DTextLabel("{00FFFF}Doação de Fundos ao Governo\n{FFFFFF}Aproxime para fazer sua doação",0xFFFFFFFF, 358.9107,178.5443,1008.3828, 20.0); // Doação para Cofre Governo

	// Igrejas
	CreateDynamic3DTextLabel("{FFFFFF}Igreja de Jefferson\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,2233.1575,-1333.2433,23.9816,40.0);
	CreateDynamic3DTextLabel("{FFFFFF}Igreja de Little Mexico\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,1720.2667,-1740.5646,13.5469,40.0);

	CreateDynamicPickup(2894, 23, -1077.9645,713.4493,630.0579,-1) ; // Local de casamento

	//TextLabel Cofres / Menu ORG
	CreateDynamic3DTextLabel("{FFFFFF}HQ {18C09F}Máfia Yakuza\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,671.9144,-1271.4734,13.6250,25.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ {D85300}Máfia Italiana\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,294.0777,-1372.6936,14.0260,25.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ {33FFFF}Máfia Cosa Nostra\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,479.5926,-1531.1252,19.8107,25.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ {605DFF}Policia Militar\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,1568.6442,-1689.9729,6.2188,10.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {737373}BOPE\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,324.0125,-1518.6938,36.0325,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {333300}CORE\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,-55.8733, -300.6442, 5.4297,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {00660C}Forças Armadas\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,-1341.9978,496.3586,11.1953,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {2641FE}Amigo dos Amigos\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,1690.1144,-2098.9558,13.8343,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {996600}Policia Civil\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,1688.1190,-1351.0415,17.4297,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {0095FF}Governo\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,358.7956,186.6793,1008.3828,25.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ {BDBDBD}Hitmans\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,2281.0020,-2368.7363,13.5469,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {DFB77B}Repórteres\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,750.9255,-1359.1901,13.5000,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {917662}Policia Federal\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,1130.3765,-2043.4714,69.0078,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {177517}G.R.O.T.A\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,2593.9116, -1500.9254, 16.0808,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {571E1E}Estado Islamico\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,-599.1168,-1065.9753,23.4103,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {99311E}Familia do Norte\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,-198.4513, -1087.4451, 24.6806,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {010701}BAIRRO-13\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,2825.3916,-1170.2870,25.2235,25.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ {F80505}C.V\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,1596.2747, -733.9089, 65.3713,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {7F994C}P.C.C\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,1329.1952, -3008.4778, 8.3392,25.0);
	CreateDynamic3DTextLabel("{FFFFFF}HQ {A4D1FF}The Triads\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,2788.4028,-1627.9689,10.9272,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {A3283D}Warlocks\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,687.2863,-472.8064,16.5363,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {576176}Sons Of Anarchy\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF,2477.7251,89.5832,26.7737,25.0);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {FFFF44}P.R.F\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF, 219.2626,108.5960,1010.2118, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 16);
    CreateDynamic3DTextLabel("{FFFFFF}HQ {EE2323}Al-Qaeda\n{FFFFFF}Aperte Y para acessar o menu da organização",0xFF0000FF, -308.2417,1538.4569,75.5625,7.0);

	//----------
	CreateDynamic3DTextLabel("{FFFFFF}HQ dos Hitmans\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,2281.2393,-2364.8765,13.5469,7);
	// CreateDynamic3DTextLabel("{FFFFFF}Hospital de Los Santos\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF,1172.7867,-1323.3781,15.4007, 25.0);

	/*						Carro Forte						*/
	CreateDynamic3DTextLabel("Entrega de dinheiro\n{FFFFFF}/entregardinheiro",0xDBED15FF, 1468.8262,-1775.3623,13.5400, 6.0);
	CreateDynamicPickup(1239, 23, 1468.8262,-1775.3623,13.5400, -1);

	//  HQs de Organizações
	CreateDynamic3DTextLabel("Departamento do CORE\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar", 0xFFFFFFFF, -50.0843, -298.3511, 5.4297,25.0);
	CreateDynamic3DTextLabel("Departamento da BOPE\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar",0xFFFFFFFF, 328.1634,-1512.4167,36.0325,25.0);
	CreateDynamic3DTextLabel("Departamento da Polícia Civil\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar", 0xFFFFFFFF, 1684.5236, -1343.3313, 17.4368,40.0);
	CreateDynamic3DTextLabel("HQ da Máfia Cosa Nostra\n{FFFFFF}Aperte a tecla "_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para entrar", 0xFFFFFFFF, 475.6070, -1501.5156, 20.5379,40.0);


	/*				Actores do banco			*/
	CreateDynamic3DTextLabel("Banco\n{DBED15}/depositar /sacar /transferir {00FF00}/filiar", 0xFFFFFFFF, 1456.5311, -1128.0327, 23.9580, 10.0);
	CreateDynamic3DTextLabel("Banco\n{DBED15}/comprarouros /venderouros /transferirouros", 0xFFFFFFFF, 1460.4261, -1124.5687, 23.9580, 10.0);

	actorBanco[0] = CreateDynamicActor(186, 2318.3064, -15.5078, 26.7496, 89.6586, true, 100.0, 10081);
	actorBanco[1] = CreateDynamicActor(240, 2318.3064, -7.3369, 26.7496, 90.5986, true, 100.0, 10081);

	actorBanco[2] = CreateDynamicActor(186, 2318.3064, -15.5078, 26.7496, 89.6586, true, 100.0, 10082);
	actorBanco[3] = CreateDynamicActor(240, 2318.3064, -7.3369, 26.7496, 90.5986, true, 100.0, 10082);

	actorBanco[4] = CreateDynamicActor(186, 2318.3064, -15.5078, 26.7496, 89.6586, true, 100.0, 10083);
	actorBanco[5] = CreateDynamicActor(240, 2318.3064, -7.3369, 26.7496, 90.5986, true, 100.0, 10083);

	/*				Actores da farmácia			*/
	CreateDynamic3DTextLabel("Farmácia\n{DBED15}/comprar remedio",0xFFFFFFFF, 604.0738, -601.3110, 985.6933, 5.0);

	actorFarmacia[0] = CreateDynamicActor(186, 604.127, -599.921, 985.693, 178.476, true, 100.0, 10013);
	actorFarmacia[1] = CreateDynamicActor(186, 604.127, -599.921, 985.693, 178.476, true, 100.0, 10014);
	actorFarmacia[2] = CreateDynamicActor(186, 604.127, -599.921, 985.693, 178.476, true, 100.0, 10015);
	actorFarmacia[3] = CreateDynamicActor(186, 604.127, -599.921, 985.693, 178.476, true, 100.0, 10016);

	CreateDynamic3DTextLabel("Elevador\n{FFFFFF}Aperte 'Y' para subir",0xDBED15FF, 338.2485,-1501.9403,36.0391, 10); // Elevador HQ BOPE
	CreateDynamic3DTextLabel("Elevador\n{FFFFFF}Aperte 'Y' para descer",0xDBED15FF, 347.8569,-1494.7401,76.5391, 10); // Elevador HQ BOPE

	CreateDynamic3DTextLabel("Elevador\n{FFFFFF}Aperte 'Y' para subir",0xDBED15FF, 2473.2554,-1531.0217,24.1455, 10); // Elevador HQ Familia do Norte
	CreateDynamic3DTextLabel("Elevador\n{FFFFFF}Aperte 'Y' para descer",0xDBED15FF, 2463.8401,-1538.7161,32.5703, 10); // Elevador HQ Familia do Norte

	CreateDynamic3DTextLabel("Elevador\n{FFFFFF}Aperte 'Y' para subir",0xDBED15FF, 1650.6134, -1351.0118, 17.4295, 10);
	CreateDynamic3DTextLabel("Elevador\n{FFFFFF}Aperte 'Y' para descer",0xDBED15FF, 1672.1484, -1334.3336, 158.4766, 10);

	/*				Cativeiros			*/
	CreateDynamic3DTextLabel("Cativeiro\n{FFFFFF}Aperte "_KEY_PATH_ENTER_INT_COLOR" para entrar", 0xDBED15FF, 2919.8228,2117.9873,17.8955,5.0);
	CreateDynamicPickup(19133, 24, 2919.8228,2117.9873,17.8955);

	CreateDynamic3DTextLabel("Cativeiro\n{FFFFFF}Aperte "_KEY_PATH_ENTER_INT_COLOR" para entrar", 0xDBED15FF, 2811.0066,2919.7876,36.5046,5.0);
	CreateDynamicPickup(19133, 24, 2919.8228,2117.9873,17.8955);

	CreateDynamic3DTextLabel("Cativeiro\n{FFFFFF}Aperte "_KEY_PATH_ENTER_INT_COLOR" para entrar", 0xDBED15FF, 2007.0468,2910.1699,47.8231,5.0);
	CreateDynamicPickup(19133, 24, 2919.8228,2117.9873,17.8955);

	/*				Vender órgãos e retirar órgãos			*/
	CreateDynamic3DTextLabel("Vender órgãos\n{FFFFFF}Abra seu inventário e use o órgão que deseja vender", 0xDBED15FF, 939.4326, 2177.0520, 1011.0234,5.0);

	CreateDynamic3DTextLabel("Retirar órgãos\n{FFFFFF}Digite /retirarorgaos próximo á vitima aqui", 0xDBED15FF, 2561.0088,-1290.1510,1031.4219,5.0);

	return 1;
}
#include <map_house_335>
#include <hq_exercito>
stock RemoveBuildingsOfServer(playerid)
{
	/* 								Apartamento								*/
	RemoveBuildingForPlayer(playerid, 6518, 280.297, -1606.2, 72.3984, 250.0); // Night Lights
	RemoveBuildingForPlayer(playerid, 1226, 265.481, -1581.1, 32.9311, 5.0);   // Lamp Post
	
	/* 								HQ Lixeiros								*/
	RemoveBuildingForPlayer(playerid, 3723, 2178.7344, -1971.2656, 16.8672, 0.25);
	RemoveBuildingForPlayer(playerid, 3723, 2189.9922, -1949.3281, 16.8672, 0.25);
	RemoveBuildingForPlayer(playerid, 3770, 2197.9766, -1970.5625, 14.0000, 0.25);
	RemoveBuildingForPlayer(playerid, 5357, 2177.9922, -2006.7578, 23.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 5291, 2177.9922, -2006.7578, 23.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 3722, 2178.7344, -1971.2656, 16.8672, 0.25);
	RemoveBuildingForPlayer(playerid, 3626, 2197.9766, -1970.5625, 14.0000, 0.25);
	RemoveBuildingForPlayer(playerid, 3722, 2189.9922, -1949.3281, 16.8672, 0.25);
	
	/* 								HQ P.R.F							*/
	RemoveBuildingForPlayer(playerid, 3326, 2321.3594, -127.0469, 28.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 3327, 2296.3594, -127.0469, 28.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 3329, 2275.4688, -127.4844, 26.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 13461, 2373.2344, 29.1719, 30.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 3328, 2242.3750, -127.4844, 26.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 779, 2236.6953, -118.9609, 25.9531, 0.25);
	RemoveBuildingForPlayer(playerid, 1419, 2236.2500, -108.3594, 25.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 3315, 2242.3750, -127.4844, 26.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1419, 2242.0313, -108.3594, 25.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1419, 2244.1172, -110.4531, 26.1875, 0.25);
	RemoveBuildingForPlayer(playerid, 1419, 2244.1172, -114.5469, 26.5938, 0.25);
	RemoveBuildingForPlayer(playerid, 3407, 2244.6328, -108.7188, 25.4766, 0.25);
	RemoveBuildingForPlayer(playerid, 3314, 2275.4688, -127.4844, 26.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 764, 2272.9297, -141.8906, 26.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 782, 2267.9141, -110.4922, 25.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2283.8750, -143.4453, 28.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2283.8750, -138.7109, 28.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2283.8750, -133.9766, 28.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2283.8750, -129.2500, 28.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2283.8750, -124.5078, 28.0000, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2283.8750, -119.7813, 27.7578, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2283.8750, -115.0781, 27.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2283.8750, -110.8125, 27.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 3316, 2296.3594, -127.0469, 28.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 780, 2288.2578, -116.6875, 25.7891, 0.25);
	RemoveBuildingForPlayer(playerid, 769, 2313.6484, -141.6328, 26.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 765, 2311.9922, -111.7656, 25.5313, 0.25);
	RemoveBuildingForPlayer(playerid, 1407, 2311.6875, -108.4219, 26.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 1407, 2306.2344, -108.4219, 26.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 3317, 2321.3594, -127.0469, 28.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1407, 2316.4297, -108.4219, 26.2109, 0.25);
	
 	/* 							Interior da Fazenda							*/
	RemoveBuildingForPlayer(playerid, 14871, 286.1875, 307.6094, 1002.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 14875, 280.5313, 308.1563, 1003.2188, 0.25);

    /* 							Prisão La Sante (exterior)					*/
	RemoveBuildingForPlayer(playerid, 700, 1799.1563, -1596.5391, 13.4453, 0.25);
	RemoveBuildingForPlayer(playerid, 647, 1799.4844, -1594.4063, 14.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 647, 1800.2891, -1598.2891, 14.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 647, 1801.8750, -1592.4531, 14.4141, 0.25);
	RemoveBuildingForPlayer(playerid, 647, 1805.6328, -1589.9688, 14.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 1807.4688, -1590.4766, 13.4453, 0.25);
	RemoveBuildingForPlayer(playerid, 647, 1808.8672, -1591.0547, 14.4609, 0.25);
	
	/*							HQ Sons Of Anarchy							*/
	RemoveBuildingForPlayer(playerid, 3323, 2511.4297, 89.1953, 28.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 3324, 2486.4219, 64.1953, 28.4219, 0.25);
	RemoveBuildingForPlayer(playerid, 3325, 2486.4297, 89.1953, 27.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 3322, 2511.4375, 64.1875, 28.4219, 0.25);
	RemoveBuildingForPlayer(playerid, 13375, 2436.8594, 63.8047, 32.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1294, 2472.8203, 50.6172, 29.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1308, 2499.1953, 51.4766, 25.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 781, 2494.0391, 53.8359, 25.3984, 0.25);
	RemoveBuildingForPlayer(playerid, 765, 2475.0859, 59.4453, 25.1563, 0.25);
	RemoveBuildingForPlayer(playerid, 3312, 2486.4219, 64.1953, 28.4219, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2474.0781, 59.5469, 26.2734, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2476.4297, 57.0234, 26.2266, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2481.1641, 57.0234, 26.2266, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2491.6094, 57.0234, 26.2266, 0.25);
	RemoveBuildingForPlayer(playerid, 1308, 2473.8438, 74.4609, 25.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 764, 2497.0938, 71.9766, 25.1406, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2474.0781, 67.0000, 26.2734, 0.25);
	RemoveBuildingForPlayer(playerid, 766, 2494.1719, 79.7422, 24.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 764, 2503.7656, 80.1484, 23.2656, 0.25);
	RemoveBuildingForPlayer(playerid, 1408, 2474.1797, 87.1875, 26.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 1408, 2474.1797, 80.0781, 26.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 779, 2489.7969, 96.2813, 25.4297, 0.25);
	RemoveBuildingForPlayer(playerid, 1408, 2498.8906, 92.6094, 26.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 1408, 2474.1797, 92.7500, 26.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 3310, 2486.4297, 89.1953, 27.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 1294, 2525.0313, 50.5625, 29.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 779, 2523.5391, 65.0938, 25.4297, 0.25);
	RemoveBuildingForPlayer(playerid, 3311, 2511.4375, 64.1875, 28.4219, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2523.8125, 57.6406, 26.2734, 0.25);
	RemoveBuildingForPlayer(playerid, 1446, 2523.8125, 62.3516, 26.2734, 0.25);
	RemoveBuildingForPlayer(playerid, 1308, 2524.1797, 76.6641, 25.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 3313, 2511.4297, 89.1953, 28.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 1294, 2472.8203, 102.7813, 29.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1408, 2498.8906, 101.4219, 26.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 1408, 2498.8906, 98.5313, 26.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 1408, 2474.1797, 98.9063, 26.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 1294, 2525.0469, 102.7891, 29.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1408, 2513.6563, 101.4219, 26.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 1408, 2519.1641, 101.4219, 26.0156, 0.25);

	/*						HQ Governo - Prefeitura								*/
	RemoveBuildingForPlayer(playerid, 1231, 1432.3047, -1832.9141, 15.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 1480.0313, -1832.9141, 15.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 1529.2891, -1832.9141, 15.2891, 0.25);
	
	/*							HQ Warlocks								*/
	RemoveBuildingForPlayer(playerid, 1345, 693.2891, -456.0156, 16.0078, 0.25);
	
	/* 							HQ Máfia Russa									*/
 	RemoveBuildingForPlayer(playerid, 1268, 193.9453, -1453.7344, 24.6406, 0.25);
    RemoveBuildingForPlayer(playerid, 1268, 218.2266, -1434.5625, 24.6406, 0.25);
    RemoveBuildingForPlayer(playerid, 673, 193.1484, -1449.2344, 11.0703, 0.25);
    RemoveBuildingForPlayer(playerid, 673, 189.2422, -1444.7734, 11.0703, 0.25);
    RemoveBuildingForPlayer(playerid, 1259, 193.9453, -1453.7344, 24.6406, 0.25);
    RemoveBuildingForPlayer(playerid, 673, 197.9688, -1454.4609, 11.0703, 0.25);
    RemoveBuildingForPlayer(playerid, 6350, 247.3906, -1454.8281, 37.7344, 0.25);
    RemoveBuildingForPlayer(playerid, 1259, 218.2266, -1434.5625, 24.6406, 0.25);
    RemoveBuildingForPlayer(playerid, 1226, 203.1953, -1429.2031, 15.8125, 0.25);
    RemoveBuildingForPlayer(playerid, 673, 223.0469, -1419.7266, 11.0703, 0.25);
    RemoveBuildingForPlayer(playerid, 673, 227.8672, -1424.9531, 11.0703, 0.25);
    RemoveBuildingForPlayer(playerid, 1308, 232.5000, -1426.0078, 12.5859, 0.25);
    RemoveBuildingForPlayer(playerid, 620, 235.8906, -1422.5469, 10.3203, 0.25);
    RemoveBuildingForPlayer(playerid, 620, 278.0000, -1392.7188, 10.3203, 0.25);
    RemoveBuildingForPlayer(playerid, 620, 280.1875, -1391.6953, 10.3203, 0.25);
    RemoveBuildingForPlayer(playerid, 620, 285.6406, -1383.6406, 11.6328, 0.25);
    
    /*							HQ Policia Federal								*/
    RemoveBuildingForPlayer(playerid, 729, 864.5234, -1694.3281, 11.4531, 0.25);
	RemoveBuildingForPlayer(playerid, 729, 878.0234, -1686.8125, 11.4531, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 930.1406, -1662.2969, 4.9688, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 942.6641, -1651.6094, 15.2500, 0.25);
	RemoveBuildingForPlayer(playerid, 759, 902.4297, -1695.9766, 12.4844, 0.25);
	RemoveBuildingForPlayer(playerid, 615, 902.0000, -1693.2344, 12.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 870.6328, -1690.7813, 14.5391, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 897.1641, -1690.7734, 14.5391, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 901.5781, -1692.4219, 8.9219, 0.25);
	RemoveBuildingForPlayer(playerid, 759, 903.8125, -1692.5078, 12.4844, 0.25);
	RemoveBuildingForPlayer(playerid, 759, 901.6719, -1691.3359, 12.4844, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 862.7734, -1686.7422, 11.5313, 0.25);
	RemoveBuildingForPlayer(playerid, 1297, 922.7500, -1683.3438, 15.9375, 0.25);
	RemoveBuildingForPlayer(playerid, 1297, 913.0547, -1670.1641, 15.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 6204, 880.6016, -1653.7656, 14.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 759, 870.0469, -1641.9219, 12.7969, 0.25);
	RemoveBuildingForPlayer(playerid, 759, 875.8047, -1641.9219, 12.4375, 0.25);
	RemoveBuildingForPlayer(playerid, 634, 868.3438, -1642.6641, 11.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 712, 871.8828, -1642.7969, 20.8984, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 886.8672, -1644.1719, 8.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 759, 884.2031, -1641.9219, 12.7969, 0.25);
	RemoveBuildingForPlayer(playerid, 712, 881.7813, -1642.7969, 20.8984, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 906.7656, -1644.6953, 4.9688, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 898.2656, -1644.6953, 8.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 759, 897.4297, -1641.9219, 12.7969, 0.25);
	RemoveBuildingForPlayer(playerid, 759, 901.5391, -1641.9063, 12.2734, 0.25);
	RemoveBuildingForPlayer(playerid, 634, 901.2500, -1642.6641, 11.9219, 0.25);
	RemoveBuildingForPlayer(playerid, 634, 887.1719, -1642.6641, 11.9219, 0.25);

	/*							HQ da G.R.O.T.A								*/
	RemoveBuildingForPlayer(playerid, 1265, 2491.2344, -1653.9609, 12.9219, 0.25);
	RemoveBuildingForPlayer(playerid, 1230, 2492.2656, -1653.9922, 12.8984, 0.25);
	RemoveBuildingForPlayer(playerid, 1265, 2505.6719, -1658.9063, 12.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1468, 2522.1016, -1665.6484, 15.3281, 0.25);
	RemoveBuildingForPlayer(playerid, 1230, 2475.0000, -1653.6094, 12.7891, 0.25);
	
	/*							HQ da Polícia Cívil								*/
	RemoveBuildingForPlayer(playerid, 729, 1631.7656, -1345.7500, 16.1875, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 1633.0000, -1358.4531, 15.7969, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1625.3672, -1361.9063, 16.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1625.3984, -1349.5781, 16.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1625.4766, -1354.7500, 16.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1625.4375, -1330.1250, 16.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1625.4766, -1337.2266, 16.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1625.4766, -1342.3984, 16.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 1633.2969, -1334.5078, 15.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1639.7578, -1361.9141, 16.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1639.7344, -1349.7031, 16.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1639.7344, -1354.8828, 16.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1639.7344, -1337.3984, 16.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1639.7344, -1342.3438, 16.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1215, 1639.7656, -1330.2813, 16.9766, 0.25);
	
	/*						HQ da Guerrilheiros Israelitas						*/
	RemoveBuildingForPlayer(playerid, 1412, 1130.6719, 1850.9141, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1413, 1129.5391, 1845.7656, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1413, 1132.3750, 1855.8906, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1134.5938, 1860.6719, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1136.8281, 1865.4531, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1139.0547, 1870.2344, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1141.2891, 1875.0234, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1147.9766, 1889.3672, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1145.7500, 1884.5859, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1143.5156, 1879.8047, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1150.2031, 1894.1484, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1152.4375, 1898.9297, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1154.6641, 1903.7109, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1413, 1158.4297, 1905.8438, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1163.6797, 1905.3906, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1413, 1167.5625, 1907.4375, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1170.1875, 1912.0078, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1172.8281, 1916.5781, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1412, 1175.4688, 1921.1484, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1413, 1176.7656, 1926.0391, 11.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 3474, 1124.6797, 1963.3672, 16.7422, 0.25);
	RemoveBuildingForPlayer(playerid, 19447, 1157.0000, 0.0000, 3611.0000, 0.25);

	/*							HQ Estado Islamico										*/
	RemoveBuildingForPlayer(playerid, 696, -604.8672, -1106.0547, 24.3047, 0.25);
	RemoveBuildingForPlayer(playerid, 696, -546.0625, -1003.8672, 28.3906, 0.25);
	RemoveBuildingForPlayer(playerid, 790, -506.4219, -1012.3828, 28.9609, 0.25);

	/*						HQ dos Caminhoneiros							*/
	RemoveBuildingForPlayer(playerid, 3686, 2195.0859, -2216.8438, 15.9063, 0.25);
	RemoveBuildingForPlayer(playerid, 3744, 2183.1719, -2237.2734, 14.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 3744, 2174.6406, -2215.6563, 15.1016, 0.25);
	RemoveBuildingForPlayer(playerid, 3744, 2193.0625, -2196.6406, 15.1016, 0.25);
	RemoveBuildingForPlayer(playerid, 5305, 2198.8516, -2213.9219, 14.8828, 0.25);
	RemoveBuildingForPlayer(playerid, 3632, 2167.8047, -2257.3516, 16.3828, 0.25);
	RemoveBuildingForPlayer(playerid, 3632, 2167.1719, -2257.1250, 16.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 3632, 2158.5703, -2251.0156, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 3632, 2158.0469, -2250.5078, 15.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 5132, 2163.2891, -2251.6094, 14.1406, 0.25);
	RemoveBuildingForPlayer(playerid, 3578, 2194.4766, -2242.8750, 13.2578, 0.25);
	RemoveBuildingForPlayer(playerid, 3574, 2183.1719, -2237.2734, 14.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 3574, 2174.6406, -2215.6563, 15.1016, 0.25);
	RemoveBuildingForPlayer(playerid, 3627, 2195.0859, -2216.8438, 15.9063, 0.25);
	RemoveBuildingForPlayer(playerid, 5244, 2198.8516, -2213.9219, 14.8828, 0.25);
	RemoveBuildingForPlayer(playerid, 3574, 2193.0625, -2196.6406, 15.1016, 0.25);
	
	/*						HQ dos BOPE e R.O.C.A.M							*/
	RemoveBuildingForPlayer(playerid, 620, 2730.8672, -1960.3750, 9.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 2806.6875, -1958.7578, 9.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 2810.2656, -1909.2813, 9.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 2831.3203, -1921.5391, 10.8047, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 2831.3203, -1937.1953, 10.8047, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 2848.2813, -1952.8438, 10.8047, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 2848.2813, -1968.5000, 10.8047, 0.25);
	RemoveBuildingForPlayer(playerid, 4268, 2882.0781, -2036.4531, -4.0000, 0.25);
	RemoveBuildingForPlayer(playerid, 4402, 2882.0781, -2036.4531, -4.0000, 0.25);
	
	// HQ BPEV
	RemoveBuildingForPlayer(playerid, 3377, -149.9141, -324.3438, 1.5781, 0.25);
	RemoveBuildingForPlayer(playerid, 12932, -117.9609, -337.4531, 3.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 3378, -149.9141, -324.3438, 1.5781, 0.25);
	RemoveBuildingForPlayer(playerid, 12936, -155.8672, -304.7266, 7.1875, 0.25);

	// HQ Governo (Prefeitura)
	RemoveBuildingForPlayer(playerid, 4024, 1479.8672, -1790.3984, 56.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 4044, 1481.1875, -1785.0703, 22.3828, 0.25);
	RemoveBuildingForPlayer(playerid, 4045, 1479.3359, -1802.2891, 12.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 4046, 1479.5234, -1852.6406, 24.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 4047, 1531.6328, -1852.6406, 24.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1527, 1448.2344, -1755.8984, 14.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 4217, 1449.2500, -1852.5703, 22.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 713, 1407.1953, -1749.3125, 13.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 1266, 1482.0859, -1859.9688, 25.0391, 0.25);
	RemoveBuildingForPlayer(playerid, 713, 1405.2344, -1821.1172, 13.1016, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 1417.9766, -1832.5313, 11.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 673, 1405.5781, -1831.6953, 12.3984, 0.25);
	RemoveBuildingForPlayer(playerid, 1265, 1465.4766, -1848.2500, 12.9922, 0.25);
	RemoveBuildingForPlayer(playerid, 1372, 1466.9453, -1847.8438, 12.6641, 0.25);
	RemoveBuildingForPlayer(playerid, 1372, 1419.7344, -1846.5469, 12.6641, 0.25);
	RemoveBuildingForPlayer(playerid, 1265, 1420.4297, -1845.3438, 12.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 1372, 1419.6953, -1844.2031, 12.6641, 0.25);
	RemoveBuildingForPlayer(playerid, 1220, 1420.4922, -1842.4375, 12.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 1220, 1419.7266, -1842.8516, 12.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 1230, 1419.6719, -1842.0313, 12.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 4170, 1433.9531, -1844.4063, 21.4219, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 1447.1016, -1832.5000, 12.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 1432.3047, -1832.9141, 15.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 4174, 1435.7656, -1823.6641, 15.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 1456.3984, -1832.5313, 11.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 673, 1464.0938, -1831.8828, 12.3984, 0.25);
	RemoveBuildingForPlayer(playerid, 1260, 1482.0859, -1859.9688, 25.0391, 0.25);
	RemoveBuildingForPlayer(playerid, 4004, 1479.5234, -1852.6406, 24.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1357, 1487.6953, -1848.1094, 12.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 1372, 1486.2109, -1848.1250, 12.6641, 0.25);
	RemoveBuildingForPlayer(playerid, 1372, 1468.0625, -1847.7891, 12.6641, 0.25);
	RemoveBuildingForPlayer(playerid, 1230, 1488.9219, -1848.2734, 12.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 1480.0313, -1832.9141, 15.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 3997, 1479.3359, -1802.2891, 12.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 4171, 1503.3984, -1848.3359, 21.4609, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 1504.8438, -1832.5313, 11.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 673, 1499.0469, -1832.2734, 12.8828, 0.25);
	RemoveBuildingForPlayer(playerid, 1265, 1515.3828, -1850.0547, 12.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 1265, 1514.4219, -1850.0391, 12.9922, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 1512.9453, -1832.3516, 13.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 1372, 1516.6875, -1850.0547, 12.6641, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 1404.9141, -1765.2656, 12.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 4173, 1427.2734, -1756.1797, 15.0000, 0.25);
	RemoveBuildingForPlayer(playerid, 673, 1415.3125, -1748.5625, 12.3984, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 1429.5313, -1748.4219, 12.9063, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 1438.0313, -1747.9375, 13.4453, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 1447.9063, -1748.2266, 12.9063, 0.25);
	RemoveBuildingForPlayer(playerid, 4002, 1479.8672, -1790.3984, 56.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 3980, 1481.1875, -1785.0703, 22.3828, 0.25);
	RemoveBuildingForPlayer(playerid, 4003, 1481.0781, -1747.0313, 33.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 1516.0000, -1748.6016, 13.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 4048, 1531.6328, -1852.6406, 24.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 1372, 1538.9453, -1849.2734, 12.6641, 0.25);
	RemoveBuildingForPlayer(playerid, 1230, 1538.8359, -1847.6250, 13.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 1220, 1538.3906, -1847.9297, 12.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 1220, 1539.1016, -1847.2969, 12.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 1231, 1529.2891, -1832.9141, 15.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 1549.5313, -1832.3125, 12.8828, 0.25);
	RemoveBuildingForPlayer(playerid, 673, 1555.6641, -1830.5938, 13.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 4175, 1524.4141, -1823.8516, 15.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 1554.8203, -1816.1563, 13.4766, 0.25);
	RemoveBuildingForPlayer(playerid, 673, 1553.2578, -1764.8125, 12.7969, 0.25);
	RemoveBuildingForPlayer(playerid, 4172, 1534.7656, -1756.1797, 15.0000, 0.25);
	RemoveBuildingForPlayer(playerid, 620, 1533.2656, -1749.0234, 12.8047, 0.25);
	RemoveBuildingForPlayer(playerid, 673, 1522.1641, -1748.5703, 13.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 1553.7031, -1747.9375, 13.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 19379, 1481.0000, 508911136.0000, -1861.0000, 0.25);

	return 1;
}

stock CreateMap_Main()
{
	//          Fábrica de Materiais por João Revolts
	object_Fabricar[0] = CreateDynamicObject(3383,-961.2999900,1886.8000000,8.0000000,0.0000000,0.0000000,270.0000000); //object(a51_labtable1_) (1)
	object_Fabricar[1] = CreateDynamicObject(3383,-961.2999900,1890.8000000,8.0000000,0.0000000,0.0000000,270.0000000); //object(a51_labtable1_) (2)
	CreateDynamicObject(1271,-961.5999800,1893.4000000,8.4000000,0.0000000,0.0000000,0.0000000); //object(gunbox) (1)
	CreateDynamicObject(1271,-961.5999800,1893.4000000,9.1000000,0.0000000,0.0000000,0.0000000); //object(gunbox) (2)
	CreateDynamicObject(3015,-961.2999900,1891.7000000,9.1000000,0.0000000,0.0000000,0.0000000); //object(cr_cratestack) (1)
	CreateDynamicObject(3015,-961.2999900,1890.4000000,9.1000000,0.0000000,0.0000000,0.0000000); //object(cr_cratestack) (2)
	CreateDynamicObject(3013,-961.2999900,1885.6000000,9.2000000,0.0000000,0.0000000,0.0000000); //object(cr_ammobox) (1)
	CreateDynamicObject(3013,-961.2999900,1886.7000000,9.2000000,0.0000000,0.0000000,0.0000000); //object(cr_ammobox) (2)
	CreateDynamicObject(3013,-961.2999900,1887.8000000,9.2000000,0.0000000,0.0000000,0.0000000); //object(cr_ammobox) (3)
	CreateDynamicObject(2973,-961.7999900,1874.7000000,8.0000000,0.0000000,0.0000000,0.0000000); //object(k_cargo2) (1)object_Fabricar
	CreateDynamicObject(2973,-961.7999900,1877.2000000,8.0000000,0.0000000,0.0000000,0.0000000); //object(k_cargo2) (2)
	CreateDynamicObject(923,-961.5999800,1871.0000000,8.9000000,0.0000000,0.0000000,90.0000000); //object(packing_carates2) (1)
	CreateDynamicObject(923,-961.5999800,1869.2000000,8.9000000,0.0000000,0.0000000,90.0000000); //object(packing_carates2) (2)
	CreateDynamicObject(922,-961.5999800,1865.9000000,8.9000000,0.0000000,0.0000000,90.0000000); //object(packing_carates1) (1)
	CreateDynamicObject(942,-961.7999900,1854.1000000,10.4000000,0.0000000,0.0000000,90.0000000); //object(cj_df_unit_2) (1)
	CreateDynamicObject(939,-962.2000100,1897.4000000,10.4000000,0.0000000,0.0000000,90.0000000); //object(cj_df_unit) (1)
	CreateDynamicObject(964,-961.2999900,1907.3000000,8.0000000,0.0000000,0.0000000,90.0000000); //object(cj_metal_crate) (1)
	CreateDynamicObject(1685,-961.5000000,1914.5000000,8.8000000,0.0000000,0.0000000,0.0000000); //object(blockpallet) (1)
	CreateDynamicObject(2043,-961.2000100,1889.7000000,9.2000000,0.0000000,0.0000000,0.0000000); //object(ammo_box_m4) (1)
	CreateDynamicObject(2040,-961.2000100,1888.5000000,9.2000000,0.0000000,0.0000000,0.0000000); //object(ammo_box_m1) (1)
	CreateDynamicObject(2359,-961.0999800,1891.0000000,9.3000000,0.0000000,0.0000000,180.0000000); //object(ammo_box_c5) (1)
	CreateDynamicObject(2975,-961.5000000,1912.5000000,8.0000000,0.0000000,0.0000000,0.0000000); //object(k_cargo3) (1)
	CreateDynamicObject(931,-961.5000000,1918.0000000,9.1000000,0.0000000,0.0000000,90.0000000); //object(rack3) (1)
	CreateDynamicObject(2567,-961.5999800,1930.4000000,9.9000000,0.0000000,0.0000000,90.0000000); //object(ab_warehouseshelf) (1)
	CreateDynamicObject(1271,-962.0999800,1919.8000000,8.3000000,0.0000000,0.0000000,0.0000000); //object(gunbox) (3)
	CreateDynamicObject(1271,-962.0999800,1919.8000000,9.0000000,0.0000000,0.0000000,0.0000000); //object(gunbox) (4)
	CreateDynamicObject(1271,-962.0999800,1919.8000000,9.7000000,0.0000000,0.0000000,0.0000000); //object(gunbox) (5)
	CreateDynamicObject(1271,-962.0999800,1920.7000000,8.3000000,0.0000000,0.0000000,0.0000000); //object(gunbox) (6)
	CreateDynamicObject(1271,-962.0999800,1920.7000000,9.0000000,0.0000000,0.0000000,0.0000000); //object(gunbox) (7)
	CreateDynamicObject(1271,-962.0999800,1920.7000000,9.7000000,0.0000000,0.0000000,0.0000000); //object(gunbox) (8)
	CreateDynamicObject(1271,-961.2999900,1920.3000000,8.3000000,0.0000000,0.0000000,0.0000000); //object(gunbox) (9)
	CreateDynamicObject(1271,-961.2999900,1920.3000000,9.0000000,0.0000000,0.0000000,0.0000000); //object(gunbox) (10)
	CreateDynamicObject(923,-961.5000000,1934.0000000,8.9000000,0.0000000,0.0000000,90.0000000); //object(packing_carates2) (3)
	CreateDynamicObject(923,-961.5000000,1935.9000000,8.9000000,0.0000000,0.0000000,90.0000000); //object(packing_carates2) (4)
	CreateDynamicObject(939,-962.0000000,1946.2000000,10.4000000,0.0000000,0.0000000,90.0000000); //object(cj_df_unit) (2)

    // Máfia Italiana
	CreateDynamicObjectMBR(18766, 258.48285, -1408.54651, 14.82910,   0.00000, 0.00000, 27.00000);
    CreateDynamicObjectMBR(18766, 267.35571, -1404.02637, 14.82910,   0.00000, 0.00000, 27.00000);
    CreateDynamicObjectMBR(18766, 276.25601, -1399.49329, 14.82910,   0.00000, 0.00000, 27.00000);
    CreateDynamicObjectMBR(18766, 285.28000, -1395.29504, 14.82910,   0.00000, 0.00000, 23.00000);
    CreateDynamicObjectMBR(18766, 299.04248, -1375.55322, 14.82910,   0.00000, 0.00000, 110.00000);
    CreateDynamicObjectMBR(18766, 295.64981, -1366.22998, 14.82910,   0.00000, 0.00000, 110.00000);
    CreateDynamicObjectMBR(18766, 250.03069, -1413.61938, 14.82910,   0.00000, 0.00000, 34.91999);
    CreateDynamicObjectMBR(18766, 241.85330, -1419.32666, 14.82910,   0.00000, 0.00000, 34.92000);
    CreateDynamicObjectMBR(18766, 233.86798, -1425.23315, 14.82910,   0.00000, 0.00000, 38.10001);
    CreateDynamicObject(3749, 221.95856, -1433.98535, 18.01501,   0.00000, 0.00000, 43.62001);
    CreateDynamicObjectMBR(18766, 212.67050, -1445.45618, 14.44240,   0.00000, 0.00000, 47.88000);
    CreateDynamicObjectMBR(18766, 205.99013, -1452.81592, 14.44238,   0.00000, 0.00000, 47.88000);
    CreateDynamicObjectMBR(18766, 195.24670, -1456.77710, 14.34221,   0.00000, 0.00000, -50.88000);
    CreateDynamicObjectMBR(18766, 188.97804, -1449.06946, 14.34220,   0.00000, 0.00000, -50.88000);
    CreateDynamicObjectMBR(18766, 294.46930, -1391.39526, 14.82910,   0.00000, 0.00000, 23.00000);
    CreateDynamicObjectMBR(18766, 299.74719, -1384.88904, 14.82800,   0.00000, 0.00000, 78.74010);
    CreateDynamicObjectMBR(18766, 201.68730, -1457.56885, 14.44100,   0.00000, 0.00000, 47.88000);
    CreateDynamicObjectMBR(18766, 182.70531, -1441.35498, 14.34220,   0.00000, 0.00000, -50.88000);
    CreateDynamicObject(3640, 288.02481, -1370.73132, 17.28098,   0.00000, 0.00000, 20.27999);
	
	/*						Interior da HQ Warlocks							*/
	CreateObject(14655, 669.00000, -412.70001, 672.59998,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14652, 669.00000, -417.29999, 672.59998,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14650, 669.05530, -417.00281, 672.59998,   0.00000, -2.00000, -180.00000);
	CreateDynamicObject(14657, 669.00299, -416.91901, 671.34491,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14651, 663.94312, -410.46909, 672.74719,   0.00000, 0.00000, -91.00000);
	CreateDynamicObject(1543, 670.60168, -415.94229, 671.60718,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1543, 670.62817, -417.34439, 671.60718,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1543, 670.63861, -418.60620, 671.60718,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1543, 667.19031, -414.48099, 671.60742,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1543, 667.25671, -415.99860, 671.60742,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1543, 667.25043, -417.27530, 671.60742,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1543, 667.25043, -418.87531, 671.60742,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1511, 670.02252, -413.81961, 672.41827,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1511, 670.32532, -413.82849, 672.41827,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19390, 668.95190, -422.76440, 672.32349,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19859, 668.19531, -422.77820, 671.80402,   0.00000, 0.00000, 0.00000);

    // HQ BAFEF
	CreateDynamicObject(3749, -78.05655, -352.75934, 6.33230,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71410, -362.99490, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71840, -372.07031, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.72370, -384.03119, 4.39550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71890, -331.01059, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71890, -319.09061, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71890, -307.17059, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71890, -295.25061, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3928, 4.03200, -227.97430, 4.43400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3928, 4.03200, -247.39430, 4.43400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3666, 0.04887, -232.36427, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 0.04960, -223.92349, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.02960, -223.92349, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.02960, -223.92349, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.06960, -232.30350, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 0.04890, -243.12430, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 0.04890, -252.14430, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.04890, -252.14430, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.04890, -252.14430, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.04890, -243.12430, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(964, -40.67290, -299.69260, 4.41820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(964, -40.67290, -299.69260, 4.41820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(964, -39.23290, -299.69260, 4.41820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3267, -57.96410, -337.11420, 4.43580,   0.00000, 0.00000, 128.00000);
	CreateDynamicObject(3267, -58.03920, -365.52789, 3.99420,   0.00000, 0.00000, 65.00000);
	CreateDynamicObject(3749, -78.05655, -352.75934, 6.33230,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71410, -362.99490, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71840, -372.07031, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.72370, -384.03119, 4.39550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71890, -331.01059, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71890, -319.09061, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71890, -307.17059, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -75.71890, -295.25061, 4.41550,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3666, 0.04887, -232.36427, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 0.04960, -223.92349, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.02960, -223.92349, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.02960, -223.92349, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.06960, -232.30350, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 0.04890, -243.12430, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 0.04890, -252.14430, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.04890, -252.14430, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.04890, -252.14430, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3666, 8.04890, -243.12430, 4.92640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(964, -40.67290, -299.69260, 4.41820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(964, -40.67290, -299.69260, 4.41820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(964, -39.23290, -299.69260, 4.41820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3267, -57.96410, -337.11420, 4.43580,   0.00000, 0.00000, 128.00000);
	CreateDynamicObject(3267, -58.03920, -365.52789, 3.99420,   0.00000, 0.00000, 65.00000);

	//Yakuza [1]
	CreateDynamicObject(986, 668.23810, -1217.64343, 16.81433,   0.00000, 0.00000, 43.74180);//Portao Yakuza

	// HQ Lixeiros [9]
	CreateDynamicObject(18862, 2134.04199, -1983.91040, 15.49657,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18862, 2155.01343, -2010.21594, 17.10275,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18862, 2146.55566, -1987.80164, 17.10275,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18862, 2158.08496, -1994.59546, 17.10275,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18862, 2134.83496, -1998.61926, 17.10275,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18862, 2119.99316, -2003.80151, 17.10275,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18862, 2122.19751, -1988.58386, 17.48230,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18862, 2143.27490, -1998.25647, 17.10275,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3626, 2201.70166, -2010.95239, 13.77080,   0.00000, 0.00000, 294.12949);
	
	// HQ Transportador Aéreo [23]
	CreateDynamicObject(3574, 1998.25000, -2390.34399, 15.09508,   0.00000, 0.00000, 269.41003);
	CreateDynamicObject(3574, 1999.96387, -2369.99731, 15.09508,   0.00000, 0.00000, 91.11382);
	CreateDynamicObject(2991, 1349.49304, 1750.22351, 10.46129,   0.00000, 0.00000, 89.78668);
	CreateDynamicObject(1421, 1348.97375, 1753.92126, 10.55285,   0.00000, 0.00000, 84.76120);
	CreateDynamicObject(2971, 1350.76990, 1761.55823, 9.77263,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2991, 1347.01257, 1753.09412, 10.46129,   0.00000, 0.00000, 89.78668);
	CreateDynamicObject(2991, 1347.00439, 1748.55042, 10.46129,   0.00000, 0.00000, 89.78668);
	CreateDynamicObject(2971, 1347.44080, 1759.25867, 9.77263,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2971, 1346.73792, 1765.16479, 9.77263,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1421, 1347.40723, 1756.53918, 10.55285,   0.00000, 0.00000, 84.76120);
	CreateDynamicObject(1421, 1347.41382, 1761.87915, 10.55285,   0.00000, 0.00000, 84.76120);
	CreateDynamicObject(1421, 1349.91638, 1759.19165, 10.55285,   0.00000, 0.00000, 84.76120);
	CreateDynamicObject(2971, -1279.79456, -634.25409, 13.12906,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2991, -1275.47766, -634.63934, 13.74707,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1421, -1282.35486, -633.09662, 13.94202,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1421, -1269.80945, -632.06238, 13.94202,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2991, -1272.11658, -629.46906, 13.74707,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2971, -1266.95618, -632.45581, 13.12906,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2991, -1276.49695, -631.88995, 13.74707,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2971, -1272.62610, -632.12421, 13.12906,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1421, -1280.46777, -631.32983, 13.94202,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2971, -1277.03320, -629.69067, 13.12906,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2991, -1268.76428, -634.58612, 13.74707,   0.00000, 0.00000, 0.00000);
	
	// HQ G.R.O.T.A [12]
	CreateDynamicObject(1728, 2529.74463, -1670.71204, 14.19090,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1516, 2528.70435, -1669.11829, 14.35400,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1279, 2528.46021, -1669.14734, 14.94000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(356, 2529.02808, -1669.38342, 14.93960,   -84.00000, 4.00000, 91.00000);
	CreateDynamicObject(1358, 2523.12402, -1669.11328, 15.25330,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3594, 2492.86060, -1669.92334, 13.12060,   3.11640, 0.00700, 18.98960);
	CreateDynamicObject(1358, 2466.37329, -1656.25110, 13.56710,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1758, 2463.75635, -1655.70325, 12.37030,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(356, 2463.63184, -1657.11230, 12.59350,   25.00000, -84.00000, 178.00000);
	CreateDynamicObject(1728, 2533.76782, -1664.63232, 14.19090,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1516, 2532.14063, -1665.75427, 14.35400,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1279, 2532.17480, -1665.78503, 14.94000,   0.00000, 0.00000, 90.00000);
	
	//HQ Cosa Nostra [3]
	CreateDynamicObject(3749,494.5,-1548.3,22.9,0,0,32.25);
	CreateDynamicObject(987,505,-1465.3,15.8,0,0,152);
	CreateDynamicObject(987,494.5,-1459.6,15.8,0,0,151.996);
	
	//HQ Policia Militar [7]
	CreateDynamicObject(2886,247.72758484,72.33472443,1003.92919922,0.00000000,0.00000000,0.00000000); // Botão DP
	CreateDynamicObject(2886,250.40625000,64.48971558,1003.90820312,0.00000000,0.00000000,270.00000000); // Botão DP
	CreateDynamicObject(2886,250.90625000,64.57377625,1003.92028809,0.00000000,0.00000000,90.00000000); // Botão DP
	CreateDynamicObject(2886,244.89843750,73.80095673,1003.94177246,0.00000000,0.00000000,90.00000000); // Botão DP
	CreateDynamicObject(2886,248.41078186,74.61183929,1003.93310547,0.00000000,0.00000000,90.00000000); // Botão DP
	CreateDynamicObject(2886,247.88383484,77.16934967,1003.94836426,0.00000000,0.00000000,270.00000000); // Botão DP
	
	CreateDynamicObject(18766, 1603.39709, -1638.35498, 14.87400,   0.00000, 0.00000, 5.16000);
	CreateDynamicObject(18766, 1607.85706, -1633.00684, 14.87400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(18766, 1607.83862, -1626.99500, 14.87400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(18766, 1607.83862, -1617.02087, 14.87400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(18766, 1607.83862, -1607.04407, 14.87400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(18766, 1602.35242, -1602.54663, 14.87400,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, 1592.33679, -1602.55261, 14.87400,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, 1582.35303, -1602.54663, 14.87400,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, 1572.37256, -1602.54663, 14.87400,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, 1562.37000, -1602.54663, 14.87400,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, 1552.37000, -1602.54663, 14.87400,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, 1543.88220, -1602.54688, 14.87400,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, 1539.37183, -1607.15515, 14.87400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(18766, 1539.37976, -1613.00098, 14.87400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(18766, 1544.89197, -1617.49475, 14.87400,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, 1553.50891, -1620.26428, 12.31289,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, 1563.46497, -1620.26428, 12.31290,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18766, 1573.45935, -1620.26428, 12.31290,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3749, 1547.86353, -1627.34241, 18.24123,   0.00000, 0.00000, 90.00000);
	
	//                          HQ Polícia Civil [ 37 objetos ]
	CreateDynamicObject(987, 1643.58008, -1316.93164, 16.42320,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(987, 1654.75415, -1316.93848, 16.42320,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(987, 1664.91895, -1316.93372, 16.42320,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(987, 1658.68750, -1333.27625, 16.41630,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(987, 1658.69324, -1328.84155, 16.41630,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(987, 1622.24866, -1328.28284, 16.45720,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, 1634.00781, -1316.91541, 16.42320,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(987, 1622.23657, -1340.18726, 16.45720,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, 1622.22095, -1352.11914, 16.45720,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, 1622.20752, -1364.05676, 16.45720,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, 1658.71521, -1359.27954, 16.41630,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(869, 1699.28198, -1329.40894, 16.71100,   0.00000, 0.00000, 91.00000);
	CreateDynamicObject(869, 1699.20313, -1323.38818, 16.71100,   0.00000, 0.00000, 89.00000);
	CreateDynamicObject(869, 1699.60791, -1356.92798, 16.71100,   0.00000, 0.00000, 91.00000);
	CreateDynamicObject(869, 1699.53345, -1362.94287, 16.71100,   0.00000, 0.00000, 89.00000);
	CreateDynamicObject(4003, 1694.13965, -1342.75073, 29.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(869, 1636.26135, -1358.37891, 16.70920,   0.00000, 0.00000, 76.00000);
	CreateDynamicObject(869, 1632.11279, -1358.57141, 16.70920,   0.00000, 0.00000, 76.00000);
	CreateDynamicObject(869, 1632.38867, -1346.27100, 16.70920,   0.00000, 0.00000, 76.00000);
	CreateDynamicObject(869, 1636.36450, -1346.01758, 16.70920,   0.00000, 0.00000, 76.00000);
	CreateDynamicObject(869, 1632.53833, -1333.86145, 16.70920,   0.00000, 0.00000, 76.00000);
	CreateDynamicObject(869, 1636.55457, -1333.89746, 16.70920,   0.00000, 0.00000, 76.00000);
	CreateDynamicObject(3881, 1687.97717, -1310.86182, 14.64300,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3578, 1694.48279, -1308.02246, 13.02640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1694.48804, -1293.46228, 13.02640,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1699.56238, -1300.84204, 12.47120,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1697.58252, -1300.84216, 12.47120,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1695.70911, -1300.83313, 12.47120,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1693.27075, -1300.87915, 12.47120,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1689.04285, -1300.84827, 12.47120,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3865, 1694.56433, -1303.85339, 10.94900,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3865, 1694.39587, -1297.62390, 10.94900,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1237, 1691.15906, -1300.86438, 12.47120,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3934, 1677.67151, -1343.10767, 157.46091,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3934, 1665.17712, -1342.97913, 157.46091,   0.00000, 0.00000, 90.00000);

	//							Nova HQ Governo (Prefeitura) 
	CreateObject(6959, 1419.77136, -1762.26062, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(6959, 1461.10437, -1762.26904, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(6959, 1502.44153, -1762.26477, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(6959, 1543.78625, -1762.27209, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(6959, 1543.77002, -1802.25952, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(6959, 1502.42651, -1802.26355, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(6959, 1461.08154, -1802.24927, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(6959, 1419.74475, -1802.22327, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(6959, 1543.75037, -1842.25098, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(6959, 1502.42517, -1842.25830, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(6959, 1461.08472, -1842.24609, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(6959, 1419.79871, -1842.18457, 12.57130,   0.00000, 0.00000, 0.00000); // Chão do Governo
	CreateObject(9901, 1479.00439, -1821.83533, 38.27780,   0.00000, 0.00000, -90.00000); // Prédio do Governo
	CreateDynamicObject(4003, 1478.80115, -1782.80005, 29.69730,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(5812, 1541.81165, -1789.93665, 12.79990,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(5812, 1416.26123, -1789.93530, 12.79990,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(5812, 1416.25305, -1789.93811, 12.51790,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(5812, 1541.81165, -1789.93665, 12.53390,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(9949, 1471.50916, -1798.00000, 24.54910,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1652, 1556.82971, -1755.16052, 13.21270,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1652, 1556.83521, -1780.76050, 13.21270,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1652, 1556.85083, -1806.35950, 13.21270,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1652, 1518.46045, -1742.33252, 13.20510,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(1652, 1401.28308, -1755.11475, 13.21270,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1652, 1401.28772, -1780.70496, 13.21270,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1652, 1401.25610, -1806.30725, 13.21270,   0.00000, 0.00000, 89.82000);
	CreateDynamicObject(1652, 1414.06689, -1742.29370, 13.20510,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(1652, 1439.65405, -1742.30176, 13.20510,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(1231, 1556.40247, -1743.43921, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1556.24207, -1754.21802, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1556.23755, -1765.20825, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1556.31824, -1775.90088, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1556.29199, -1787.28833, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1556.54199, -1800.24268, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1556.49475, -1813.58386, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1547.35962, -1743.30347, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1527.46277, -1743.24304, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1536.80774, -1743.18250, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1401.96338, -1743.21350, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1401.88123, -1754.48254, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1401.86487, -1768.06360, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1401.78711, -1781.19519, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1401.80334, -1795.15625, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1401.75598, -1807.26819, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1401.62610, -1816.32800, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1430.71814, -1743.49670, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1422.36145, -1743.26404, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1411.94226, -1743.13416, 15.41460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 1550.94958, -1749.38123, 12.59851,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 1552.55688, -1772.82874, 12.59851,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 1536.37598, -1753.55310, 12.59851,   0.00000, 0.00000, 90.06001);
	CreateDynamicObject(700, 1530.10022, -1769.35364, 12.59851,   0.00000, 0.00000, 90.06001);
	CreateDynamicObject(700, 1405.51672, -1783.65320, 12.42480,   0.00000, 0.00000, 90.06001);
	CreateDynamicObject(700, 1407.45032, -1748.47156, 12.42480,   0.00000, 0.00000, 90.06001);
	CreateDynamicObject(700, 1425.11707, -1748.33472, 12.42480,   0.00000, 0.00000, 90.06001);
	CreateDynamicObject(700, 1407.96887, -1762.65381, 12.42480,   0.00000, 0.00000, 90.06001);
	CreateDynamicObject(712, 1542.74219, -1766.58752, 22.54393,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(712, 1542.84546, -1778.73816, 22.54393,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(712, 1417.18530, -1778.06299, 22.34293,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(712, 1417.21436, -1767.61609, 22.34293,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(620, 1542.11963, -1771.82373, 12.74861,   0.00000, 0.00000, -205.67999);
	CreateDynamicObject(620, 1417.87280, -1772.55225, 12.02726,   0.00000, 0.00000, -342.59998);
	CreateDynamicObject(700, 1428.47607, -1768.79614, 12.42480,   0.00000, 0.00000, 90.06001);
	CreateDynamicObject(1652, 1544.05688, -1742.32227, 13.20510,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(984, 1520.62720, -1768.31812, 13.16320,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(984, 1495.05237, -1768.30029, 13.16320,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1231, 1505.86694, -1742.64880, 15.23460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1451.97095, -1742.72351, 15.23460,   0.00000, 0.00000, 1.14000);
	CreateDynamicObject(984, 1507.82788, -1768.30566, 13.16320,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(10183, 1510.15259, -1764.38135, 12.55740,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(984, 1463.06738, -1768.32556, 13.16320,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(984, 1450.28857, -1768.32068, 13.16320,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(984, 1437.50989, -1768.32043, 13.16320,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(10183, 1447.93188, -1764.28784, 12.55740,   0.00000, 0.00000, -135.00000);
	CreateDynamicObject(984, 1488.64075, -1761.90857, 13.16320,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(984, 1488.63428, -1749.11609, 13.16320,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(984, 1469.43604, -1761.94202, 13.16320,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(984, 1469.43616, -1749.17310, 13.16320,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1488.63818, -1742.56689, 15.23460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 1469.38989, -1742.55151, 15.23460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(10183, 1432.13220, -1746.80762, 12.55740,   0.00000, 0.00000, -315.23999);
	CreateDynamicObject(10183, 1526.28711, -1746.43005, 12.55740,   0.00000, 0.00000, -315.23999);
	CreateDynamicObject(640, 1488.21130, -1745.54517, 13.18960,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(640, 1488.19543, -1752.05920, 13.18960,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(640, 1488.14966, -1758.48364, 13.18960,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(640, 1488.12231, -1764.96436, 13.18960,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(640, 1469.88208, -1745.48694, 13.18960,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(640, 1469.87561, -1751.92188, 13.18960,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(640, 1469.91492, -1758.31665, 13.18960,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(640, 1469.93420, -1764.74561, 13.18960,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 1488.22729, -1761.87720, 12.57474,   0.00000, 0.00000, 131.82002);
	CreateDynamicObject(700, 1488.22351, -1755.43262, 12.57474,   0.00000, 0.00000, 131.82002);
	CreateDynamicObject(700, 1488.21411, -1748.93433, 12.57474,   0.00000, 0.00000, 131.82002);
	CreateDynamicObject(700, 1469.76660, -1761.51013, 12.57474,   0.00000, 0.00000, -9.11997);
	CreateDynamicObject(700, 1469.72437, -1755.10779, 12.57474,   0.00000, 0.00000, -9.11997);
	CreateDynamicObject(700, 1469.76428, -1748.71265, 12.57474,   0.00000, 0.00000, -9.11997);
	CreateDynamicObject(700, 1469.74255, -1767.93848, 12.57474,   0.00000, 0.00000, -9.11997);
	CreateDynamicObject(700, 1488.30225, -1768.35217, 12.57474,   0.00000, 0.00000, 131.82002);
	CreateDynamicObject(640, 1491.38879, -1768.80957, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1496.76196, -1768.80872, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1503.09143, -1768.78687, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1508.47156, -1768.78235, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1514.59094, -1768.80664, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1519.97156, -1768.80493, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1524.38525, -1768.79834, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(700, 1499.93384, -1768.95911, 12.57474,   0.00000, 0.00000, 78.35998);
	CreateDynamicObject(700, 1511.52661, -1768.88782, 12.57474,   0.00000, 0.00000, 78.35998);
	CreateDynamicObject(640, 1466.81519, -1768.92773, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1461.45325, -1768.92749, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1455.24902, -1768.95630, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1449.86731, -1768.99268, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1443.74561, -1768.97852, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1438.36035, -1769.02258, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(640, 1434.64001, -1769.00415, 13.18960,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(700, 1461.32190, -1775.14355, 12.57474,   0.00000, 0.00000, 78.35998);
	CreateDynamicObject(700, 1446.82202, -1769.15234, 12.57474,   0.00000, 0.00000, 78.35998);
	CreateDynamicObject(700, 1424.06750, -1756.94702, 12.42480,   0.00000, 0.00000, 90.06001);
	CreateDynamicObject(9345, 1505.18091, -1776.66382, 12.30720,   0.00000, 0.00000, -539.69952);
	CreateDynamicObject(9345, 1455.78650, -1773.42554, 12.30720,   0.00000, 0.00000, -899.45978);
	CreateDynamicObject(712, 1449.10596, -1773.37366, 21.60708,   0.00000, 0.00000, 43.98000);
	CreateDynamicObject(712, 1509.25269, -1777.16455, 21.83283,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 1497.72009, -1776.33008, 12.95320,   0.00000, 0.00000, -179.03999);
	CreateDynamicObject(822, 1460.10449, -1776.14246, 12.96644,   0.00000, 0.00000, 59.22000);
	CreateDynamicObject(822, 1460.12109, -1773.42346, 12.96644,   0.00000, 0.00000, 59.22000);
	CreateDynamicObject(822, 1456.60193, -1774.81763, 12.96644,   0.00000, 0.00000, 59.22000);
	CreateDynamicObject(822, 1454.33618, -1774.11047, 12.96644,   0.00000, 0.00000, 59.22000);
	CreateDynamicObject(822, 1451.55957, -1773.53674, 12.96644,   0.00000, 0.00000, 59.22000);
	CreateDynamicObject(822, 1449.88306, -1773.86609, 12.96644,   0.00000, 0.00000, 234.23996);
	CreateDynamicObject(822, 1499.15320, -1776.64478, 12.96644,   0.00000, 0.00000, 234.23996);
	CreateDynamicObject(822, 1502.87415, -1777.13733, 12.96644,   0.00000, 0.00000, 234.23996);
	CreateDynamicObject(822, 1505.54041, -1777.41223, 12.96644,   0.00000, 0.00000, 234.23996);
	CreateDynamicObject(822, 1509.73584, -1776.48401, 12.96644,   0.00000, 0.00000, 234.23996);
	CreateDynamicObject(822, 1508.72034, -1779.14954, 12.96644,   0.00000, 0.00000, 219.35997);
	CreateDynamicObject(19456, 1403.90979, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1413.43518, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1422.93896, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1432.40259, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1441.87854, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1451.27686, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1460.74390, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1470.25061, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1479.64063, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1488.96240, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1498.44885, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1507.89807, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1517.50354, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1527.12231, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1536.53723, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1546.01038, -1862.20410, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19456, 1554.83105, -1862.22412, 10.81410,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19545, 1516.40918, -1808.26636, 33.87079,   0.00000, 0.00000, 90.00000);

	//                          HQ Reporteres [ 1 objetos ]
	CreateDynamicObject(11472, 738.85358, -1360.89075, 21.48436,   0.00000, 0.00000, 268.41263);
	
	//                          HQ Sons Of Anarchy [ 30 objetos ]
	CreateObject(18981, 2486.44971, 64.19960, 25.01840,   0.00000, 90.00000, 90.00000);
	CreateObject(18981, 2511.42334, 89.18431, 25.01840,   0.00000, 90.00000, 90.00000);
	CreateObject(18981, 2511.44312, 64.19360, 25.01840,   0.00000, 90.00000, 90.00000);
	CreateObject(18981, 2486.42969, 89.20840, 25.01840,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(18282, 2489.66187, 94.26590, 25.77240,   0.00000, 0.00000, 0.00000);
	CreateObject(7861, 2523.33179, 90.67064, 29.07730,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(12943, 2496.64795, 59.91433, 25.32100,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(12943, 2488.56909, 59.92462, 25.32100,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1080, 2484.71509, 59.86470, 27.79890,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1080, 2484.70703, 63.87690, 27.79890,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19815, 2492.37988, 59.34950, 28.17680,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19815, 2500.63989, 58.98950, 28.17680,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3934, 2516.72583, 89.46520, 30.92100,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3934, 2516.72583, 59.42540, 30.92100,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8613, 2517.27173, 100.71280, 27.71210,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(18452, 2479.35034, 61.22588, 27.38070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1686, 2481.94922, 61.03506, 25.51990,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1686, 2476.76001, 61.03510, 25.51990,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19899, 2499.21655, 52.56911, 25.45320,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19899, 2491.00220, 52.87374, 25.45320,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(17951, 2484.40454, 54.97060, 27.15060,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(978, 2504.73413, 51.92670, 26.20410,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(970, 2506.54346, 96.96210, 26.15820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(970, 2502.43750, 96.96210, 26.15820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3524, 2475.62207, 88.19075, 27.10124,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3524, 2503.54712, 88.16427, 27.10124,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2047, 2479.21851, 66.74810, 29.30510,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2048, 2488.31396, 87.90770, 27.83800,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2614, 2508.89771, 74.36090, 29.06590,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(1653, 2480.32544, 51.76860, 26.18430,   0.00000, 0.00000, 0.00000);
	
	//                          HQ Warlocks [ 30 objetos ]
	CreateDynamicObject(3049,697.0999800,-475.1000100,17.6000000,0.0000000,0.0000000,0.0000000); //
	CreateDynamicObject(3049,711.4000200,-475.1000100,17.6000000,0.0000000,0.0000000,0.0000000); //
	CreateDynamicObject(9131,697.5000000,-475.1000100,16.5000000,0.0000000,0.0000000,0.0000000); //
	CreateDynamicObject(9131,697.5000000,-475.1000100,18.7700000,0.0000000,0.0000000,0.0000000); //
	CreateDynamicObject(9131,706.5000000,-475.1000100,16.5000000,0.0000000,0.0000000,0.0000000); //
	CreateDynamicObject(9131,706.5000000,-475.1000100,18.7700000,0.0000000,0.0000000,0.0000000); //
	CreateDynamicObject(3049,692.7000100,-475.1000100,17.6000000,0.0000000,0.0000000,270.0000000); //
	CreateDynamicObject(3049,692.7000100,-470.7000100,17.6000000,0.0000000,0.0000000,270.0000000); //
	CreateDynamicObject(3049,692.7000100,-466.2999900,17.6000000,0.0000000,0.0000000,270.0000000); //
	CreateDynamicObject(3049,692.7000100,-461.8999900,17.6000000,0.0000000,0.0000000,270.0000000); //
	CreateDynamicObject(3049,692.7000100,-457.5000000,17.6000000,0.0000000,0.0000000,270.0000000); //
	CreateDynamicObject(3049,692.7000100,-453.1000100,17.6000000,0.0000000,0.0000000,270.0000000); //
	CreateDynamicObject(3049,692.7000100,-448.6000100,17.6000000,0.0000000,0.0000000,270.0000000); //
	CreateDynamicObject(3049,692.7000100,-444.2000100,17.6000000,0.0000000,0.0000000,270.0000000); //
	CreateDynamicObject(3049,693.0999800,-439.7000100,17.6000000,0.0000000,0.0000000,180.0000000); //
	CreateDynamicObject(3049,697.5000000,-439.7000100,17.6000000,0.0000000,0.0000000,179.9950000); //
	CreateDynamicObject(3049,701.9000200,-439.7000100,17.6000000,0.0000000,0.0000000,179.9950000); //
	CreateDynamicObject(3049,706.2999900,-439.7000100,17.6000000,0.0000000,0.0000000,179.9950000); //
	CreateDynamicObject(3049,711.2999900,-439.7000100,17.6000000,0.0000000,0.0000000,89.9950000); //
	CreateDynamicObject(3049,711.2999900,-444.1000100,17.6000000,0.0000000,0.0000000,89.9950000); //
	CreateDynamicObject(3049,711.2999900,-448.5000000,17.6000000,0.0000000,0.0000000,89.9950000); //
	CreateDynamicObject(3049,711.2999900,-452.8999900,17.6000000,0.0000000,0.0000000,89.9950000); //
	CreateDynamicObject(3049,711.2999900,-457.2999900,17.6000000,0.0000000,0.0000000,89.9950000); //
	CreateDynamicObject(3049,711.2999900,-461.7000100,17.6000000,0.0000000,0.0000000,89.9950000); //
	CreateDynamicObject(3049,711.2999900,-466.1000100,17.6000000,0.0000000,0.0000000,89.9950000); //
	CreateDynamicObject(3049,711.2999900,-470.5000000,17.6000000,0.0000000,0.0000000,89.9950000); //
	CreateDynamicObject(9131,693.0000000,-439.7999900,16.2000000,0.0000000,0.0000000,0.0000000); //
	CreateDynamicObject(9131,693.0000000,-439.7999900,18.4700000,0.0000000,0.0000000,0.0000000); //
	CreateDynamicObject(9131,710.9000200,-439.7999900,16.2000000,0.0000000,0.0000000,0.0000000); //
	CreateDynamicObject(9131,710.9000200,-439.7999900,18.4600000,0.0000000,0.0000000,0.0000000); //
	CreateDynamicObject(8572,693.4531300,-452.3727100,17.5988400,0.0000000,0.0000000,88.1984600); //
	
	//      Outros objetos
 	CreateDynamicObject(8209,-1657.58972168,309.62448120,6.68852663,0.00000000,0.00000000,9.92492676); 		//   HQ Exército (correto)
	CreateDynamicObject(7657,-1516.18835449,481.56393433,12.89653015,0.00000000,0.00000000,178.64941406); 	//   HQ Exército (correto)
	CreateDynamicObject(2930, 1582.6254882813, -1638.0324707031, 15.007925987244, 0, 0, 91.309509277344); 	//   HQ Policia Militar (correto)
	CreateDynamicObject(7927,366.49870000,189.72340000,1008.61030000,0.00000000,0.00000000,90.00000000); 	//  Bloqueio na porta da prefeitura
	CreateDynamicObject(1676, 1000.5368041992, -937.51239013672, 42.908992767334, 0, 0, 9.9249267578125);   // Posto de combustível
	CreateDynamicObject(1676, 1007.5074462891, -936.49285888672, 42.908992767334, 0, 0, 7.939208984375); 	// Posto de combustível
	CreateDynamicObject(2930, -1297.6999511719, 491.39999389648, 12.89999961853, 0, 0, 0);                  // Grade de presos no exército
	CreateDynamicObject(4206, 1336.37708, -650.46631, 107.82912,   0.00000, 0.00000, 0.00000);  			// Piscina [Casa 181]
	CreateDynamicObject(3109, 321.46438598633, 302.0078125, 999.40002441406, 0.00000000, 0.00000000, 268.69067382813);  //GRADES CELAS PM,PF
    
	//HQ REPORTER
	CreateDynamicObject(11472,738.68500000,-1360.54800000,21.54300000,0.00000000,0.00000000,-90.00000000); //
	CreateDynamicObject(7927,366.49870000,189.72340000,1008.61030000,0.00000000,0.00000000,90.00000000); //

	//PORTA BOPE [2]
	CreateDynamicObject(2946, 327.39999389648, -1511.8000488281, 35, 0, 0, 142);
	CreateDynamicObject(2946, 327.39999389648, -1511.8000488281, 35, 0, 0, 320.99829101563);
	
	// Grades do posto
	CreateDynamicObject(985, 1941.16760, -1776.33264, 11.92526,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(985, 1942.17590, -1776.38354, 11.92526,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(985, 1941.20569, -1769.35229, 11.92526,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(985, 1942.15332, -1769.37329, 11.92526,   0.00000, 0.00000, 90.00000);
	
	// Interiores das casas
	CreateObject(14717, 410.42529, 1689.03076, 661.14990,   0.00000, 0.00000, 0.00000);
	CreateObject(14713, 419.07544, 1606.10449, 659.39374,   0.00000, 0.00000, 0.00000);
	CreateObject(14712, 404.75720, 1522.81848, 658.18738,   0.00000, 0.00000, 0.00000);
	CreateObject(14711, 521.74866, 1566.45605, 656.58105,   0.00000, 0.00000, 0.00000);
	CreateObject(14701, 673.81982, 1619.98486, 656.04376,   0.00000, 0.00000, 0.00000);
	CreateObject(15046, 328.64923, 1636.60144, 660.21521,   0.00000, 0.00000, 0.00000);
	CreateObject(15041, 329.86246, 1552.34436, 658.95233,   0.00000, 0.00000, 0.00000);
	CreateObject(14714, 372.28116, 1590.65796, 659.50568,   0.00000, 0.00000, 0.00000);
	CreateObject(14710, 298.60919, 1607.41577, 659.62909,   0.00000, 0.00000, 0.00000);
	CreateObject(14709, 247.65154, 1586.86206, 660.82965,   0.00000, 0.00000, 0.00000);
	CreateObject(14708, 251.38222, 1656.49951, 661.64160,   0.00000, 0.00000, 0.00000);
	CreateObject(14707, 310.93021, 1723.98230, 659.85046,   0.00000, 0.00000, 0.00000);
	CreateObject(14706, 267.89044, 1796.53186, 655.23450,   0.00000, 0.00000, 0.00000);
	CreateObject(14703, 335.76971, 1792.87366, 655.62256,   0.00000, 0.00000, 0.00000);
	CreateObject(14700, 379.82001, 1725.07703, 660.98438,   0.00000, 0.00000, 0.00000);

	// apartamento
	CreateDynamicObject(19858, 295.57620, -1623.00940, 96.76500,   0.00000, 0.00000, 259.49261);
	CreateDynamicObject(19858, 275.63242, -1621.01111, 51.69873,   0.00000, 0.00000, 80.10859);
	CreateDynamicObject(19858, 275.63242, -1621.01111, 56.30246,   0.00000, 0.00000, 80.10859);
	CreateDynamicObject(19858, 275.63242, -1621.01111, 60.72276,   0.00000, 0.00000, 80.10859);
	CreateDynamicObject(19858, 275.63239, -1621.01111, 65.25250,   0.00000, 0.00000, 80.10860);
	CreateDynamicObject(19858, 275.63239, -1621.01111, 69.75050,   0.00000, 0.00000, 80.10860);
	CreateDynamicObject(19858, 275.63239, -1621.01111, 74.23580,   0.00000, 0.00000, 80.10860);
	CreateDynamicObject(19858, 275.63239, -1621.01111, 78.73100,   0.00000, 0.00000, 80.10860);
	CreateDynamicObject(19858, 275.63239, -1621.01111, 83.23870,   0.00000, 0.00000, 80.10860);
	CreateDynamicObject(19858, 275.63239, -1621.01111, 87.77896,   0.00000, 0.00000, 80.10860);
	CreateDynamicObject(19858, 275.63239, -1621.01111, 96.74580,   0.00000, 0.00000, 80.10860);
	CreateDynamicObject(19858, 275.63242, -1621.01111, 47.24230,   0.00000, 0.00000, 80.10859);
	CreateDynamicObject(19858, 295.58228, -1623.01013, 47.24230,   0.00000, 0.00000, 259.49255);
	CreateDynamicObject(19858, 295.58231, -1623.01013, 51.75130,   0.00000, 0.00000, 259.49261);
	CreateDynamicObject(19858, 295.58231, -1623.01013, 56.26210,   0.00000, 0.00000, 259.49261);
	CreateDynamicObject(19858, 295.58231, -1623.01013, 60.74469,   0.00000, 0.00000, 259.49261);
	CreateDynamicObject(19858, 295.57620, -1623.00940, 65.25700,   0.00000, 0.00000, 259.49261);
	CreateDynamicObject(19858, 295.57620, -1623.00940, 69.76505,   0.00000, 0.00000, 259.49261);
	CreateDynamicObject(19858, 295.57620, -1623.00940, 74.30327,   0.00000, 0.00000, 259.49261);
	CreateDynamicObject(19858, 295.57620, -1623.00940, 78.77100,   0.00000, 0.00000, 259.49261);
	CreateDynamicObject(19858, 295.57620, -1623.00940, 83.26180,   0.00000, 0.00000, 259.49261);
	CreateDynamicObject(19858, 295.57620, -1623.00940, 87.76949,   0.00000, 0.00000, 259.49261);
	CreateDynamicObject(19858, 295.57620, -1623.00940, 92.26477,   0.00000, 0.00000, 259.49261);
	CreateDynamicObject(19858, 275.63239, -1621.01111, 92.28970,   0.00000, 0.00000, 80.10860);
	
	for (new andares; andares != 12; andares++) {
		CreateDynamicObject(1893, 290.96729, -1623.02856, 50.40520  + (andares * 4.5),   0.00000, 0.00000, 349.78290);
		CreateDynamicObject(1893, 285.58588, -1618.99060, 50.40520  + (andares * 4.5),   0.00000, 0.00000, 349.78290);
		CreateDynamicObject(1893, 278.72418, -1620.74475, 50.40520  + (andares * 4.5),   0.00000, 0.00000, 349.78290);
		CreateDynamicObject(3657, 283.58481, -1613.23877, 46.29588  + (andares * 4.5),   0.00000, 0.00000, 80.23085);
		CreateDynamicObject(3657, 290.55411, -1614.65857, 46.29588  + (andares * 4.5),   0.00000, 0.00000, 260.04898);
		CreateDynamicObject(1808, 282.57037, -1618.47107, 45.99618  + (andares * 4.5),   0.00000, 0.00000, 80.46153);
		CreateDynamicObject(1808, 289.76160, -1619.86279, 45.99618  + (andares * 4.5),   0.00000, 0.00000, 259.26761);
		CreateDynamicObject(14532, 290.00293, -1618.01855, 46.96370 + (andares * 4.5),   0.00000, 0.00000, 81.29030);
		CreateDynamicObject(14532, 282.97424, -1616.60339, 46.96370 + (andares * 4.5),   0.00000, 0.00000, 260.36731);
		CreateDynamicObject(11728, 285.28778, -1623.47473, 47.67649 + (andares * 4.5),   0.00000, 0.00000, 170.01711);
		CreateDynamicObject(2286, 283.18030, -1613.33887, 48.68870  + (andares * 4.5),   0.00000, 0.00000, 80.00840);
		CreateDynamicObject(2277, 290.38589, -1614.60962, 48.18940  + (andares * 4.5),   0.00000, 0.00000, 260.37860);
		CreateDynamicObject(2847, 286.94370, -1612.69861, 45.99630  + (andares * 4.5),   0.00000, 0.00000, 349.93201);
		CreateDynamicObject(2922, 289.95099, -1612.06506, 47.40870  + (andares * 4.5),   0.00000, 0.00000, 170.31740);
	}
    CreateObject(19597, 280.297, -1606.2, 72.3984, 0, 0, 0);
    CreateObject(19800, 280.297, -1606.2, 22.3984, 0, 0, 0);

// sensei_--_house_interior_[big]
	CreateDynamicObject(19376, 831.57208, -131.39006, 1006.11377,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19376, 842.05109, -131.37013, 1006.11377,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19376, 842.04504, -141.00259, 1006.11377,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19376, 831.55249, -141.00351, 1006.11377,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19459, 847.16821, -131.43800, 1007.92999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 847.17395, -140.99786, 1007.92999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 842.40387, -126.71085, 1007.92999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 829.94897, -130.25330, 1006.27002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 832.78082, -126.71257, 1007.92999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 823.19202, -126.70594, 1007.92999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19376, 821.07190, -131.39247, 1006.11377,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19376, 821.06183, -141.00487, 1006.11377,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(14395, 844.66852, -143.14011, 1007.46527,   0.00000, 0.00000, 181.00000);
	CreateDynamicObject(14397, 843.14941, -129.90230, 994.11987,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19459, 842.28070, -145.72807, 1007.92999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 832.70074, -145.72580, 1007.92999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 823.11157, -145.72395, 1007.92999,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19440, 844.44714, -141.65344, 1007.93799,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19440, 844.44861, -142.64854, 1007.93799,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19440, 843.68347, -143.36401, 1007.93799,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19440, 842.34485, -143.36082, 1007.93799,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19440, 841.63171, -144.16945, 1007.93799,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19440, 841.62952, -145.76990, 1007.93799,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14397, 824.38953, -129.94119, 994.11987,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19459, 818.38062, -140.84048, 1007.92999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 818.38202, -131.23445, 1007.92999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14397, 833.74487, -129.90990, 994.11987,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19459, 834.51721, -135.18993, 1007.92999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19404, 834.69177, -133.82961, 1007.31152,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1651, 834.72498, -133.88760, 1007.18518,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2233, 834.50708, -131.72943, 1006.50098,   0.00000, 0.00000, 89.00000);
	CreateDynamicObject(2233, 834.50421, -135.14226, 1006.50098,   0.00000, 0.00000, 89.00000);
	CreateDynamicObject(2229, 834.54218, -132.30389, 1006.79730,   0.00000, 0.00000, 91.00000);
	CreateDynamicObject(2229, 834.56519, -134.73770, 1006.79730,   0.00000, 0.00000, 91.00000);
	CreateDynamicObject(18652, 834.83557, -133.84735, 1008.27039,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8169, 836.83893, -133.73994, 1006.49280,   0.00000, 0.00000, 107.00000);
	CreateDynamicObject(8169, 841.37079, -133.73579, 1006.49280,   0.00000, 0.00000, 107.00000);
	CreateDynamicObject(19367, 843.74377, -131.99582, 1005.70782,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 843.74463, -135.20163, 1005.70782,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 843.74384, -135.70079, 1005.70782,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 839.01080, -130.26451, 1006.27002,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 842.20673, -137.23941, 1005.70782,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 836.15686, -137.23805, 1005.70782,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1698, 839.19702, -137.46867, 1006.18738,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1698, 839.19287, -137.16650, 1006.27441,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1698, 839.20563, -136.85815, 1006.35742,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(15036, 832.94641, -132.62291, 1007.31219,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1649, 841.51276, -132.01178, 1006.52142,   -90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1649, 841.52356, -135.23430, 1006.52142,   -90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1649, 837.14825, -132.00938, 1006.52142,   -90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1649, 837.15900, -135.25484, 1006.52142,   -90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19458, 832.65009, -135.18565, 1006.26068,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19458, 829.15656, -135.18576, 1006.26068,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(2442, 827.86145, -133.93433, 1006.34680,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(2441, 827.86591, -132.98224, 1006.34741,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2441, 827.86200, -132.00204, 1006.34741,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2441, 829.24188, -134.37999, 1006.34912,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 832.83197, -139.92401, 1005.70782,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2357, 830.88879, -137.51956, 1006.72729,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19395, 823.28101, -144.11819, 1007.91492,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 823.27460, -140.94200, 1007.90491,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 821.62543, -139.43420, 1007.90082,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 818.42603, -139.43373, 1007.90082,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1990, 827.91211, -130.87589, 1006.34662,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19440, 827.31793, -131.07782, 1007.93799,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19440, 827.77032, -130.27077, 1007.93799,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19440, 826.18982, -130.26738, 1007.93799,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 822.64520, -131.52718, 1007.92999,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19395, 822.64423, -137.82100, 1007.91492,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2120, 833.67902, -137.51122, 1006.92230,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2120, 832.52820, -138.78329, 1006.92230,   0.00000, 0.00000, 269.00000);
	CreateDynamicObject(2120, 831.41162, -138.79114, 1006.92230,   0.00000, 0.00000, 269.00000);
	CreateDynamicObject(2120, 829.25885, -138.78981, 1006.92230,   0.00000, 0.00000, 269.00000);
	CreateDynamicObject(2120, 830.32898, -138.79301, 1006.92230,   0.00000, 0.00000, 269.00000);
	CreateDynamicObject(2120, 828.11603, -137.50053, 1006.92230,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2120, 829.27081, -136.27460, 1006.92230,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2120, 830.37091, -136.25964, 1006.92230,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2120, 831.41113, -136.25787, 1006.92230,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2120, 832.44806, -136.26595, 1006.92230,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1846, 829.92822, -129.29919, 1008.73169,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1846, 832.69513, -129.29630, 1008.73169,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1846, 835.45850, -129.29939, 1008.73169,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1846, 838.23920, -129.29961, 1008.72968,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1846, 841.01599, -129.30409, 1008.72968,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1846, 842.30768, -129.30740, 1008.73370,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 834.54230, -144.09300, 1005.70782,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19454, 817.96680, -144.32146, 1006.26068,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 821.46106, -144.32761, 1006.26068,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(18001, 818.49396, -143.60695, 1008.22980,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(18001, 819.12128, -145.61269, 1008.22980,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14480, 820.59631, -141.21581, 1006.98468,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 819.59869, -141.82408, 1005.79883,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14481, 819.78271, -140.25612, 1007.49988,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1208, 818.81342, -145.09718, 1006.33539,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(2815, 823.19183, -144.56172, 1006.34790,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2565, 820.99670, -137.19513, 1006.71930,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2565, 820.99518, -132.26822, 1006.71930,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3813, 820.67828, -127.12580, 1008.38409,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2421, 827.64795, -131.75061, 1007.35388,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 842.27966, -145.72983, 1011.28998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 832.70068, -145.72580, 1011.28998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 823.11157, -145.72400, 1011.28998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 847.17603, -140.99774, 1011.28998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 847.16821, -131.43800, 1011.28998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 842.40375, -126.70890, 1011.28998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 832.78070, -126.71060, 1011.28998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 823.19244, -126.70395, 1011.28998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 823.33185, -144.86269, 1006.20178,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 822.69104, -138.57011, 1006.20178,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1753, 843.19513, -132.73901, 1006.52002,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1754, 841.79535, -131.58089, 1006.51996,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1754, 841.79962, -135.93202, 1006.52002,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14455, 839.75232, -130.55690, 1007.90021,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(19443, 839.61633, -130.44313, 1007.93799,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19443, 838.01581, -130.43974, 1007.93799,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19443, 836.41559, -130.43710, 1007.93799,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19443, 835.51532, -130.43794, 1007.93799,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2835, 838.75452, -136.98100, 1006.51178,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2833, 835.03925, -127.89139, 1006.20245,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1566, 833.98547, -126.76500, 1007.57428,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1566, 837.09052, -126.75875, 1007.57428,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3801, 837.21051, -127.08949, 1008.10492,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3801, 834.48578, -129.82202, 1008.10492,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(0, 846.31873, -127.50880, 1006.30292,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(948, 846.66882, -127.24855, 1006.20087,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(948, 837.32092, -127.16544, 1006.20087,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(948, 833.80298, -127.20206, 1006.20087,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(948, 823.05438, -127.14735, 1006.20087,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2811, 818.83118, -139.00999, 1006.15973,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2811, 822.89404, -145.36334, 1006.29468,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1828, 837.72009, -133.73225, 1006.52045,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2241, 835.07941, -136.75644, 1007.00891,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2241, 837.23083, -137.76076, 1006.67291,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2241, 841.03180, -137.69560, 1006.67291,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2251, 830.78802, -137.53310, 1007.83661,   0.14000, 0.00000, 0.00000);
	CreateDynamicObject(1790, 834.61188, -133.83150, 1006.63202,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19462, 839.81378, -147.22060, 1006.26068,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(1817, 842.29297, -134.24181, 1006.51923,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2253, 841.75116, -133.75684, 1007.24750,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11665, 839.96692, -144.10510, 1007.04779,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19367, 840.12146, -142.43204, 1005.92877,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 841.63690, -143.98640, 1005.92480,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 839.66833, -142.43410, 1005.92877,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19440, 838.14893, -143.14990, 1005.92798,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19466, 840.55719, -142.40170, 1007.29651,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19466, 839.19940, -142.40073, 1007.29651,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19466, 841.67957, -143.52092, 1007.29651,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2225, 841.07068, -130.29205, 1006.54639,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2069, 843.22461, -135.71635, 1006.51941,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2847, 830.08197, -134.07375, 1006.34912,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2836, 845.32391, -140.79224, 1006.20142,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2815, 824.46350, -144.54880, 1006.19592,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(948, 834.09229, -145.31677, 1006.20087,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19454, 842.73761, -138.59389, 1009.62268,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19367, 842.93066, -143.35054, 1011.28888,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19440, 844.44617, -142.63652, 1011.28900,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19440, 844.44623, -141.69641, 1011.28900,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19413, 845.96411, -140.80670, 1011.28888,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 845.89697, -133.20189, 1011.28998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 841.01636, -134.72299, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 818.33545, -130.71182, 1011.28998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 823.73132, -141.17563, 1011.28998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19395, 841.01575, -137.23177, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 841.01331, -140.40335, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 841.01544, -141.83795, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 842.55042, -143.35254, 1011.28888,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 841.08081, -140.79129, 1009.71735,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 836.27399, -142.45581, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 825.26758, -140.84052, 1011.28998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19459, 821.91473, -133.20590, 1011.28998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 836.28961, -136.00005, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 834.75531, -140.83589, 1011.28888,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19395, 831.68457, -140.83971, 1011.28888,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19395, 831.58112, -137.66225, 1011.28888,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 834.77472, -137.66249, 1011.28888,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 836.27289, -145.65685, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19459, 831.51691, -133.17575, 1011.28998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 836.28394, -134.69179, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19466, 843.67438, -140.74519, 1011.40131,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19466, 819.53247, -141.84940, 1007.66052,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19466, 820.07318, -141.84850, 1007.66052,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2258, 843.10370, -143.25211, 1008.07770,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14446, 845.44458, -135.18260, 1010.16302,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2833, 842.16339, -137.65935, 1009.71753,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2833, 840.83942, -137.70358, 1009.71753,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 842.70728, -140.81677, 1013.98389,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19367, 842.81622, -140.81310, 1013.98389,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19466, 843.67438, -140.74319, 1010.51331,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(970, 842.47717, -130.35075, 1010.22589,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(970, 838.32672, -130.35048, 1010.22589,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(970, 834.18829, -130.34805, 1010.22589,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(970, 830.04633, -130.34340, 1010.22589,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(970, 827.96411, -130.34286, 1010.22589,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(970, 825.88123, -128.26114, 1010.22589,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(970, 844.57581, -128.27887, 1010.22589,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2025, 843.89319, -142.89679, 1009.71759,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2021, 841.76147, -141.79300, 1009.70868,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1502, 830.79663, -137.67949, 1009.53729,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1502, 830.88812, -140.85040, 1009.52429,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1828, 845.51727, -137.87804, 1009.70178,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1714, 842.61481, -133.84892, 1009.71741,   0.00000, 0.00000, -62.00000);
	CreateDynamicObject(2008, 841.63763, -135.03221, 1009.71753,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2313, 846.44952, -140.35410, 1009.71051,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1792, 845.84967, -140.46515, 1010.14740,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2230, 846.28503, -140.58353, 1009.72852,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2230, 844.62830, -140.60344, 1009.72852,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2286, 845.46997, -133.34790, 1011.44568,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2069, 844.12494, -141.02081, 1009.72998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1731, 843.73474, -133.46919, 1010.94720,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1731, 846.95435, -133.45602, 1010.94720,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19377, 835.74762, -138.59203, 1009.62183,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 846.25201, -135.89906, 1009.62268,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 846.25342, -126.30472, 1009.62268,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 839.68909, -132.03659, 1009.62268,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19454, 830.05713, -132.03610, 1009.62268,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19454, 820.43481, -132.03841, 1009.62268,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19454, 821.14697, -128.54025, 1009.62268,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19377, 825.27423, -138.58606, 1009.62183,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19454, 836.74323, -145.15030, 1009.62268,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19454, 827.12323, -145.15080, 1009.62469,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19454, 817.52661, -145.14172, 1009.62268,   0.00000, 90.00000, 90.00000);
	CreateDynamicObject(19377, 814.76227, -138.59692, 1009.62183,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19367, 842.69678, -133.20380, 1011.28998,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19466, 845.92615, -140.80519, 1011.22131,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1731, 840.77869, -136.26529, 1010.94720,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1731, 840.78455, -138.11505, 1010.94720,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1731, 830.71191, -137.91600, 1010.94720,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1731, 832.46692, -137.90089, 1010.94720,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1731, 832.55481, -140.58331, 1010.94720,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1731, 830.77374, -140.59969, 1010.94720,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2833, 831.11853, -138.82213, 1009.71753,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2833, 831.14636, -140.73384, 1009.71753,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3813, 847.28802, -136.46820, 1011.80981,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(16779, 841.86218, -133.79294, 1009.62061,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2259, 836.83423, -144.58224, 1010.94641,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(644, 846.56409, -132.27609, 1009.87170,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2267, 836.42786, -135.35614, 1011.59338,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2266, 840.43109, -134.82680, 1011.23132,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2272, 840.43011, -142.15421, 1011.00818,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2273, 840.42371, -139.83340, 1011.09222,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1808, 828.37476, -133.79330, 1006.20020,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2257, 847.06750, -133.99901, 1007.84839,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(914, 831.90759, -145.57680, 1007.89978,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(914, 830.73853, -145.57658, 1007.89978,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(914, 827.73633, -145.59026, 1007.89978,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(914, 826.54309, -145.58716, 1007.89978,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(14699, 831.57953, -142.78349, 1008.03198,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14699, 831.78992, -137.52600, 1008.03003,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3801, 833.86047, -127.09150, 1008.10492,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3801, 825.15790, -129.87549, 1008.10492,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3801, 843.91962, -129.82698, 1008.10492,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(14699, 822.31848, -134.74800, 1008.03003,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19377, 839.55859, -134.36432, 1013.02979,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 829.05469, -134.36673, 1013.02979,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 829.05908, -144.00340, 1013.03180,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 839.55597, -144.00011, 1013.02979,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 850.01483, -143.99579, 1013.02979,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 850.05542, -134.35748, 1013.02979,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 848.77216, -124.73765, 1013.02979,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, 820.92615, -124.73669, 1013.02979,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(1649, 841.44476, -128.02036, 1013.06738,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1649, 837.08466, -128.01842, 1013.06738,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1649, 832.68408, -128.02823, 1013.06738,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1649, 828.32330, -128.01736, 1013.06738,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(8169, 840.30408, -127.34339, 1013.05682,   0.00000, 0.00000, 16.00000);
	CreateDynamicObject(8169, 833.45947, -127.28559, 1013.05682,   0.00000, 0.00000, 16.00000);
	CreateDynamicObject(8169, 826.64575, -127.21107, 1013.05682,   0.00000, 0.00000, 16.00000);
	CreateDynamicObject(914, 845.73187, -145.56360, 1010.45081,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(19367, 823.73688, -134.76364, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14831, 833.06915, -129.12532, 1011.25531,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1723, 823.34497, -127.31069, 1009.71051,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2295, 822.36810, -128.06351, 1009.71167,   0.00000, 0.00000, 44.00000);
	CreateDynamicObject(1819, 823.91205, -129.28947, 1009.71069,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1951, 824.38483, -129.06050, 1010.40851,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1950, 824.12042, -128.84660, 1010.40851,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1543, 824.69281, -128.85953, 1010.20837,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1665, 824.52509, -128.53819, 1010.23169,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1724, 825.40643, -130.07358, 1009.71112,   0.00000, 0.00000, -160.00000);
	CreateDynamicObject(19122, 825.95160, -130.50050, 1010.27173,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19122, 825.91437, -132.93678, 1010.27173,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14565, 818.00922, -130.04010, 1011.55182,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1840, 824.20428, -126.80097, 1011.84229,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1840, 821.17114, -126.80173, 1011.84229,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1840, 820.91144, -133.11549, 1011.84229,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1840, 825.00696, -133.11220, 1011.84229,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19377, 818.55774, -134.36531, 1013.02979,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(948, 834.99237, -145.31619, 1006.20087,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2712, 818.87408, -144.63510, 1006.91772,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(914, 835.50403, -126.86559, 1011.17841,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(914, 839.63098, -126.86036, 1011.17841,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(914, 843.55151, -126.88209, 1011.17841,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(914, 831.40259, -126.85687, 1011.17841,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(914, 827.22247, -126.86802, 1011.17841,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(957, 831.79266, -139.12587, 1012.90088,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(957, 845.79865, -144.54774, 1012.90088,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2074, 821.26923, -143.18219, 1009.30658,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2799, 845.17664, -128.33003, 1010.21521,   0.00000, 0.00000, 30.00000);
	CreateDynamicObject(2800, 845.18011, -128.33057, 1010.22223,   0.00000, 0.00000, 30.00000);
	CreateDynamicObject(1538, 841.01080, -136.46217, 1009.54218,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2004, 847.12964, -134.25471, 1010.72540,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19367, 830.81476, -142.38887, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19395, 830.81262, -144.78139, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1499, 828.16229, -140.92044, 1009.71088,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19313, 828.15552, -149.44687, 1012.99231,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19313, 828.17749, -147.87134, 1015.54327,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19313, 833.13373, -147.87723, 1015.54327,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1499, 830.81262, -145.52220, 1009.54291,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1499, 833.14587, -140.92491, 1009.71088,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19313, 833.16138, -149.45937, 1012.99231,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2568, 833.69049, -145.69475, 1009.71039,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1806, 835.01740, -143.29823, 1009.71051,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1806, 834.89929, -144.91560, 1009.71051,   0.00000, 0.00000, 64.00000);
	CreateDynamicObject(2921, 828.13281, -141.00430, 1012.25922,   0.00000, -13.00000, -209.00000);
	CreateDynamicObject(357, 841.17761, -139.94360, 1010.28040,   0.00000, -31.00000, 98.00000);
	CreateDynamicObject(355, 841.16821, -140.00078, 1011.16840,   0.00000, -31.00000, 98.00000);
	CreateDynamicObject(348, 844.29968, -134.54649, 1010.28802,   -91.00000, 0.00000, 34.00000);
	CreateDynamicObject(19313, 823.92841, -147.92061, 1012.99231,   0.00000, 0.00000, 89.99800);
	CreateDynamicObject(353, 824.01886, -142.02628, 1012.55438,   -2.00000, 3.00000, 96.00000);
	CreateDynamicObject(355, 823.99890, -144.81041, 1011.16840,   -2.00000, -48.00000, 96.00000);
	CreateDynamicObject(355, 823.99518, -144.30611, 1011.16840,   -2.00000, -48.00000, 96.00000);
	CreateDynamicObject(356, 823.99658, -145.00600, 1012.18237,   -2.00000, -21.00000, 96.00000);
	CreateDynamicObject(356, 823.95203, -144.10992, 1012.22137,   -2.00000, -21.00000, 96.00000);
	CreateDynamicObject(355, 823.97333, -143.77521, 1011.16840,   -2.00000, -48.00000, 96.00000);
	CreateDynamicObject(353, 823.97760, -142.94910, 1012.55438,   -2.00000, 3.00000, 96.00000);
	CreateDynamicObject(353, 823.97760, -142.94910, 1012.09241,   -2.00000, 3.00000, 96.00000);
	CreateDynamicObject(353, 824.01892, -142.02631, 1012.09241,   -2.00000, 3.00000, 96.00000);
	CreateDynamicObject(352, 823.98535, -141.36716, 1011.63037,   -2.00000, 13.00000, 96.00000);
	CreateDynamicObject(352, 824.06927, -143.01511, 1011.63037,   -2.00000, 13.00000, 96.00000);
	CreateDynamicObject(352, 824.05249, -142.68552, 1011.63037,   -2.00000, 13.00000, 96.00000);
	CreateDynamicObject(352, 824.03571, -142.35593, 1011.63037,   -2.00000, 13.00000, 96.00000);
	CreateDynamicObject(352, 824.01892, -142.02634, 1011.63037,   -2.00000, 13.00000, 96.00000);
	CreateDynamicObject(352, 824.00214, -141.69675, 1011.63037,   -2.00000, 13.00000, 96.00000);
	CreateDynamicObject(351, 824.02594, -143.05658, 1011.16840,   -2.00000, 5.00000, 96.00000);
	CreateDynamicObject(351, 823.99860, -141.49872, 1011.16840,   -2.00000, 5.00000, 96.00000);
	CreateDynamicObject(351, 824.00787, -142.02667, 1011.16840,   -2.00000, 5.00000, 96.00000);
	CreateDynamicObject(351, 824.01715, -142.55463, 1011.16840,   -2.00000, 5.00000, 96.00000);
	CreateDynamicObject(2029, 824.45367, -145.22043, 1009.70923,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1575, 824.26392, -145.07513, 1010.51001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 824.29327, -145.41141, 1010.65002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 824.29327, -145.41141, 1010.78998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 824.29333, -145.41142, 1010.51001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 824.71442, -145.41370, 1010.65002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 824.71442, -145.41370, 1010.78998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 824.71436, -145.41374, 1010.51001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 824.71118, -145.04970, 1010.65002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 824.71118, -145.04970, 1010.78998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 824.71118, -145.04974, 1010.51001,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 824.26392, -145.07510, 1010.65002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 824.26392, -145.07510, 1010.78998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2029, 824.45697, -143.23454, 1009.70923,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1271, 827.29053, -143.24762, 1010.05243,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1271, 826.20905, -145.23274, 1010.05243,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1271, 825.50299, -145.23068, 1010.05243,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1271, 825.50299, -145.17439, 1010.73041,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1271, 826.20898, -145.16870, 1010.73041,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2041, 824.79559, -144.57869, 1010.71979,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2043, 824.64044, -143.91748, 1010.71979,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2041, 824.36017, -144.57161, 1010.71979,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2041, 824.57037, -144.57503, 1010.71979,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2041, 824.13507, -144.57970, 1010.71979,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2043, 824.14496, -143.92906, 1010.71979,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2043, 824.37018, -143.92380, 1010.71979,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3390, 827.54523, -144.36563, 1009.67828,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2068, 823.98724, -143.70505, 1013.20300,   7.00000, 0.00000, 90.00000);
	CreateDynamicObject(2606, 836.06372, -144.39200, 1011.92529,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3016, 824.21484, -143.26494, 1010.66888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3016, 824.67511, -143.26840, 1010.66888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3016, 824.67010, -142.84834, 1010.66888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3016, 824.21661, -142.85301, 1010.66888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19413, 833.99481, -134.82068, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 829.90961, -137.90321, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19395, 829.90509, -134.88210, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19367, 829.91162, -139.15155, 1011.28888,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3077, 826.67310, -140.24887, 1009.70929,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 825.28607, -137.43842, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 825.94611, -137.43840, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 826.62030, -137.43840, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 827.30017, -137.43840, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 827.97357, -137.43840, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 825.28607, -135.97400, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 825.94611, -135.97400, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 826.62030, -135.97400, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 827.30017, -135.97400, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 827.97357, -135.97400, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 825.28632, -134.58000, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 825.94611, -134.58000, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 826.62030, -134.58000, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1671, 827.30017, -134.57970, 1010.11768,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1494, 829.88733, -134.10910, 1009.54089,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3111, 827.66278, -140.20351, 1011.70209,   90.00000, 90.00000, 90.00000);
	CreateDynamicObject(2257, 830.02832, -139.22470, 1011.57941,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2008, 834.54346, -135.22064, 1009.70959,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1806, 835.69086, -134.58385, 1009.71039,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1550, 824.13531, -141.98045, 1010.88660,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 824.14624, -142.45654, 1010.88660,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 824.63690, -142.45879, 1010.88660,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 824.61200, -141.98352, 1010.88660,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1212, 844.55017, -134.89250, 1010.27570,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1212, 844.54559, -134.67380, 1010.25470,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1212, 844.33478, -134.80960, 1010.27570,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1212, 844.32654, -134.81166, 1010.33368,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1212, 844.25732, -135.02150, 1010.19171,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(353, 841.17981, -138.72356, 1010.50238,   0.00000, -31.00000, 98.00000);
	CreateDynamicObject(358, 841.15747, -139.05580, 1011.16840,   0.00000, -31.00000, 98.00000);
	CreateDynamicObject(18075, 841.53961, -135.75078, 1012.93884,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1271, 827.31116, -144.57907, 1010.05243,   0.00000, 0.00000, 0.00000);
	
	// Mansion by Yakuzaa
	CreateDynamicObject(3749, -59.05746, -1591.17517, 7.37920,   0.00000, 0.00000, 47.99999);
	CreateDynamicObject(3619, -95.68013, -1567.52502, 5.15420,   0.00000, 0.00000, 45.41986);
	CreateDynamicObject(18766, -84.82140, -1612.65356, 3.58340,   0.00000, 0.00000, 25.08000);
	CreateDynamicObject(18766, -76.37010, -1608.10144, 3.58340,   0.00000, 0.00000, 31.26000);
	CreateDynamicObject(18766, -68.29200, -1602.43518, 3.58340,   0.00000, 0.00000, 38.76000);
	CreateDynamicObject(18766, -39.57393, -1563.62744, 3.58345,   0.00000, 0.00000, 67.85997);
	CreateDynamicObject(18766, -43.86018, -1572.53577, 3.58345,   0.00000, 0.00000, 60.77996);
	CreateDynamicObject(18766, -48.98720, -1581.05627, 3.58345,   0.00000, 0.00000, 57.11995);
	CreateDynamicObject(18766, -41.89981, -1556.10327, 3.58345,   0.00000, 0.00000, 141.30009);
	CreateDynamicObject(18766, -49.29526, -1549.57727, 3.58345,   0.00000, 0.00000, 135.54024);
	CreateDynamicObject(18766, -56.37542, -1542.69006, 3.58345,   0.00000, 0.00000, 136.38017);
	CreateDynamicObject(18766, -64.20230, -1537.13342, 3.58345,   0.00000, 0.00000, 152.82008);
	CreateDynamicObject(18766, -70.20446, -1533.97437, 3.58345,   0.00000, 0.00000, 152.22011);
	CreateDynamicObject(18766, -77.54846, -1535.00989, 3.58345,   0.00000, 0.00000, 223.68008);
	CreateDynamicObject(18766, -84.77532, -1541.90820, 3.58345,   0.00000, 0.00000, 223.68008);
	CreateDynamicObject(18766, -91.95628, -1548.82593, 3.58345,   0.00000, 0.00000, 224.16006);
	CreateDynamicObject(18766, -99.10548, -1555.76550, 3.58345,   0.00000, 0.00000, 224.16006);
	CreateDynamicObject(18766, -106.27151, -1562.71375, 3.58345,   0.00000, 0.00000, 224.16006);
	CreateDynamicObject(18766, -112.98162, -1569.21838, 3.58345,   0.00000, 0.00000, 224.16006);
	CreateDynamicObject(18766, -113.40627, -1576.70569, 3.58345,   0.00000, 0.00000, 303.36017);
	CreateDynamicObject(18766, -107.89413, -1585.09619, 3.58345,   0.00000, 0.00000, 303.36017);
	CreateDynamicObject(18766, -102.40781, -1593.44446, 3.58345,   0.00000, 0.00000, 303.36017);
	CreateDynamicObject(18766, -96.92109, -1601.79651, 3.58345,   0.00000, 0.00000, 303.36017);
	CreateDynamicObject(18766, -91.55209, -1610.23901, 3.58345,   0.00000, 0.00000, 301.44025);
	CreateDynamicObject(3589, -50.56660, -1562.51343, 4.32965,   0.00000, 0.00000, -261.77966);
	CreateDynamicObject(19377, -64.01530, -1548.30151, 3.02830,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, -74.49175, -1548.30151, 3.02833,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19377, -74.49422, -1553.03870, -1.69606,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(19377, -63.99780, -1553.03943, -1.69370,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(19377, -64.00210, -1543.58215, -1.69370,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(19377, -74.48690, -1543.57727, -1.69410,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(19377, -79.65180, -1548.30151, -2.12790,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19377, -58.86530, -1548.30151, -2.12570,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3934, -74.68260, -1548.76440, 3.15310,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(3934, -63.86260, -1548.76819, 3.15310,   0.00000, 0.00000, -90.00000);
	
	// Interior Seguradora
	CreateObject(8230, 1161.44312, 1347.80798, 674.24225,   0.00000, 0.00000, 0.00000);
	CreateObject(8231, 1161.37646, 1347.98669, 674.07751,   0.00000, 0.00000, 0.00000);
	CreateObject(8237, 1167.36572, 1341.19836, 672.37134,   0.00000, 0.00000, 0.00000);
	CreateObject(1557, 1164.12891, 1356.53198, 672.37122,   0.00000, 0.00000, 180.42619);
	
	// Interior Mercado negro
	CreateDynamicObject(5422, 952.07971, 2160.94922, 1012.02661,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(5422, 941.93005, 2147.63940, 1012.00629,   0.00000, 0.00000, 269.30869);
	CreateDynamicObject(19447, 946.97998, 2147.62476, 1012.83087,   -90.00000, 0.00000, 270.02036);
	CreateDynamicObject(19447, 937.04871, 2147.59009, 1012.83087,   -90.00000, 0.00000, 270.02036);
	CreateDynamicObject(2901, 940.50592, 2177.96631, 1013.48682,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1654, 940.45819, 2178.23364, 1011.65741,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1654, 943.52570, 2178.24414, 1011.65741,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1654, 943.30383, 2178.24170, 1011.65741,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19602, 941.13501, 2177.80493, 1011.21649,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19602, 943.55371, 2178.19653, 1011.21649,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19602, 943.15198, 2178.18286, 1011.21649,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1575, 940.35931, 2177.82715, 1011.27618,   -180.00000, 0.00000, 0.00000);
	CreateDynamicObject(1654, 943.08398, 2178.21973, 1011.65741,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1654, 941.96490, 2178.13037, 1011.22449,   -90.00000, 91.00000, 0.00000);
	CreateDynamicObject(1654, 940.67871, 2178.21973, 1011.65741,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2901, 942.08649, 2178.02661, 1012.69305,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2901, 942.08649, 2178.02661, 1013.50922,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2901, 943.85352, 2178.07324, 1013.50922,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2901, 943.85352, 2178.07324, 1012.69818,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2901, 940.50671, 2177.92627, 1012.69818,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19602, 942.74768, 2178.18726, 1011.21649,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19602, 942.77075, 2177.78198, 1011.21649,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19602, 943.27197, 2177.81006, 1011.21649,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19602, 943.68469, 2177.63281, 1011.21649,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19602, 940.82886, 2177.88696, 1011.21649,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19602, 940.85168, 2177.48560, 1011.21649,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1654, 940.90118, 2178.20532, 1011.65741,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1577, 937.82330, 2178.30322, 1012.06647,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1577, 937.82330, 2178.30322, 1011.15039,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(1577, 937.82330, 2178.30322, 1011.66046,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(3785, 939.10431, 2178.27368, 1013.70844,   0.00000, 0.00000, 289.70798);
	CreateDynamicObject(3785, 945.52124, 2178.30273, 1013.70844,   0.00000, 0.00000, 289.70798);
	
	// Interior lotérica
	CreateDynamicObject(2773, 822.46179, 0.72614, 1003.69531,   0.00000, 0.00000, 269.44321);
	CreateDynamicObject(2773, 822.58618, 5.23439, 1003.69531,   0.00000, 0.00000, 269.44321);
	CreateDynamicObject(2773, 822.51404, 2.96529, 1003.69531,   0.00000, 0.00000, 269.44321);
	CreateDynamicObject(1722, 827.60217, -1.48154, 1003.17383,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1722, 826.98059, -1.48432, 1003.17383,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1722, 826.36511, -1.48968, 1003.17383,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1722, 825.73804, -1.49548, 1003.17383,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1491, 824.43158, 10.87860, 1003.18628,   0.00000, 0.00000, 269.16711);
	CreateDynamicObject(11728, 834.87750, 5.51422, 1004.61499,   0.00000, 0.00000, 270.46930);
	
	// Interior Farmácia
	CreateObject(12853, 606.83179, -598.27838, 986.68597,   0.00000, 0.00000, 0.00000);
	CreateObject(12854, 606.58191, -604.26349, 986.66718,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19456, 610.13715, -596.83545, 986.15344,   0.00000, 0.00000, 180.54738);
	CreateDynamicObject(19325, 602.39496, -600.27521, 983.41742,   0.00000, 0.00000, 270.10165);
	CreateDynamicObject(19325, 608.52155, -607.85461, 984.46979,   0.00000, 0.00000, 269.92331);
	CreateDynamicObject(19456, 601.57318, -602.44629, 985.80029,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19325, 608.51672, -603.51721, 984.46979,   0.00000, 0.00000, 269.92331);
	CreateDynamicObject(19456, 607.25671, -598.31219, 986.15344,   0.00000, 0.00000, 269.97055);
	CreateDynamicObject(19325, 602.56781, -600.96313, 983.41742,   0.00000, 0.00000, 270.10165);
	CreateDynamicObject(1651, 607.97229, -599.04364, 985.29889,   0.00000, 0.00000, 89.31909);
	CreateDynamicObject(1651, 609.40924, -600.15680, 985.29889,   0.00000, 0.00000, 1.05956);
	CreateDynamicObject(11736, 605.81073, -607.38397, 985.42041,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11738, 607.08704, -607.35956, 985.42059,   0.00000, 0.00000, 180.27000);
	CreateDynamicObject(11738, 606.63074, -604.04266, 985.42059,   0.00000, 0.00000, 357.49820);
	CreateDynamicObject(11736, 609.85968, -607.41949, 985.42041,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11736, 605.65076, -604.04510, 985.42041,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11738, 609.08173, -607.36981, 985.42059,   0.00000, 0.00000, 180.27000);
	CreateDynamicObject(11736, 602.69324, -600.49359, 985.59259,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11738, 602.74786, -600.87335, 985.61786,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11705, 603.23737, -600.69086, 985.57281,   0.00000, 0.00000, 156.13780);
	CreateDynamicObject(2894, 604.01947, -600.62970, 985.57312,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19893, 605.17053, -600.65308, 985.57300,   0.00000, 0.00000, 211.18388);
	CreateDynamicObject(11736, 607.99261, -607.38068, 985.42041,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11736, 607.76691, -603.99036, 985.42041,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11738, 609.77301, -604.02283, 985.42059,   0.00000, 0.00000, 357.49820);
	CreateDynamicObject(11738, 608.73346, -604.00690, 985.42059,   0.00000, 0.00000, 357.49820);
	
	// HQ Exercito
	CreateDynamicObject(982, -1220.67432, 455.06720, 6.87360,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(982, -1325.94116, 433.68149, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1300.29443, 433.65588, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1274.70044, 433.65683, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1249.10303, 433.65210, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(983, -1338.72253, 436.90289, 6.90460,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(982, -1494.04077, 481.71735, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1239.81250, 433.64679, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(983, -1223.83679, 435.34164, 6.88456,   0.00000, 0.00000, 298.14127);
	CreateDynamicObject(983, -1223.00146, 470.37558, 6.90460,   0.00000, 0.00000, 45.54775);
	CreateDynamicObject(983, -1227.54639, 474.90344, 6.90460,   0.00000, 0.00000, 45.02018);
	CreateDynamicObject(982, -1247.14807, 481.70355, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1272.76807, 481.70911, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1302.29663, 481.71460, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1334.18787, 481.73895, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1359.78455, 481.74008, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1385.37683, 481.73193, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1410.97266, 481.71884, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1432.38818, 481.68915, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1463.97742, 481.70435, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1489.39160, 481.70761, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(982, -1298.35352, 481.70862, 6.87360,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(3475, -1636.26685, 259.52142, 3.60110,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3749, -1527.64880, 481.91235, 11.56060,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3268, -1234.22693, 455.08618, 6.13820,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2952, -1224.26685, 442.74292, 6.08081,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2952, -1224.25049, 469.18503, 6.08081,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(982, -1220.67603, 450.18823, 6.87360,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(983, -1232.06152, 479.42227, 6.90460,   0.00000, 0.00000, 45.02018);
	CreateDynamicObject(3877, -1315.38843, 481.77103, 7.77889,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3877, -1321.67224, 481.61249, 7.81580,   0.00000, 0.00000, 1.02440);
	CreateDynamicObject(3877, -1444.91113, 481.46381, 7.72138,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3877, -1451.13013, 481.57697, 7.72138,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(5130, -1334.20898, 478.73029, 8.20100,   0.00000, 0.00000, 225.36780);
	CreateDynamicObject(3115, -1456.70361, 501.31140, 16.91490,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3114, -1414.43665, 516.35565, 16.65960,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3475, -1433.01709, 291.32339, 3.05643,   0.00000, 0.00000, 181.36928);

// HQ DETRAN
	CreateObject(12959, 2256.32495, -137.41324, 25.56750,   0.00000, 0.00000, 180.08650);
	CreateObject(19544, 2302.38306, -138.43640, 25.50580,   0.00000, 0.00000, 90.02240);
	CreateObject(19544, 2265.17065, -115.77729, 25.50580,   0.00000, 0.00000, 90.02040);
	CreateObject(19544, 2326.64429, -115.74290, 25.46580,   0.00000, 0.00000, 90.02040);
	CreateObject(19544, 2364.37280, -138.29930, 25.46580,   0.00000, 0.00000, 90.22340);
	CreateObject(19544, 2302.41113, -130.61299, 25.48580,   0.00000, 0.00000, 90.22341);
	CreateObject(19544, 2364.06055, -130.47659, 25.46580,   0.00000, 0.00000, 90.22340);
	CreateDynamicObject(986, 2266.15991, -137.65410, 29.69973,   0.00000, 0.00000, 90.02943);
	CreateDynamicObject(986, 2271.33813, -141.80820, 27.30673,   0.00000, 0.00000, 90.02943);
	CreateDynamicObject(8041, 2270.89966, -117.73043, 31.17230,   0.00000, 0.00000, 181.30299);
	CreateDynamicObject(2930, 2271.34570, -128.04234, 30.67207,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2930, 2271.32568, -128.04213, 28.13445,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2930, 2271.32568, -126.41586, 28.13445,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2930, 2271.11401, -116.90580, 32.37790,   0.00000, 0.00000, 3.14840);
	CreateDynamicObject(987, 2330.85107, -121.16418, 25.49879,   0.00000, 0.00000, 90.69339);
	CreateDynamicObject(987, 2330.60620, -109.10426, 25.49879,   0.00000, 0.00000, 179.75500);
	CreateDynamicObject(987, 2283.36572, -145.74271, 25.49879,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(987, 2295.30298, -145.74158, 25.49879,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(987, 2307.24829, -145.74113, 25.49879,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(987, 2319.20703, -145.73851, 25.49879,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(987, 2331.14526, -145.78291, 25.49879,   0.00000, 0.00000, 90.69339);
	CreateDynamicObject(987, 2331.00488, -133.85147, 25.49879,   0.00000, 0.00000, 90.69339);
	CreateDynamicObject(987, 2271.41846, -145.73975, 25.49879,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(987, 2282.82373, -108.90384, 25.49879,   0.00000, 0.00000, 179.75500);
	CreateDynamicObject(987, 2294.76050, -108.96439, 25.49879,   0.00000, 0.00000, 179.75500);
	CreateDynamicObject(987, 2306.70532, -109.01540, 25.49879,   0.00000, 0.00000, 179.75500);
	CreateDynamicObject(987, 2318.65186, -109.05804, 25.49879,   0.00000, 0.00000, 179.75500);
	CreateDynamicObject(987, 2330.86157, -121.90685, 25.49879,   0.00000, 0.00000, 90.69339);
	CreateDynamicObject(2930, 2271.34570, -126.41556, 30.67730,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2930, 2271.11401, -116.90580, 31.07350,   0.00000, 0.00000, 3.14840);
	CreateDynamicObject(3593, 2273.20923, -141.58005, 25.98357,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3593, 2328.49683, -140.79350, 26.09720,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3594, 2329.22046, -113.40048, 26.09724,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3594, 2276.43945, -141.68980, 26.09720,   0.00000, 2.00000, 0.00000);
	CreateDynamicObject(984, 2233.99097, -126.64535, 26.10280,   0.00000, 0.00000, 359.86673);
	CreateDynamicObject(984, 2265.02368, -145.60051, 26.10280,   0.00000, 0.00000, 90.59090);
	CreateDynamicObject(984, 2233.96948, -139.45004, 26.10280,   0.00000, 0.00000, 359.86673);
	CreateDynamicObject(984, 2240.34888, -145.82790, 26.10280,   0.00000, 0.00000, 90.59090);
	CreateDynamicObject(984, 2253.14233, -145.70264, 26.10280,   0.00000, 0.00000, 90.59090);
	CreateDynamicObject(986, 2271.31299, -133.78305, 27.30673,   0.00000, 0.00000, 90.02943);
	CreateDynamicObject(781, 2250.03369, -131.02473, 25.75185,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(781, 2266.11450, -131.10966, 25.75185,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(781, 2258.29639, -130.35535, 25.75185,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19435, 2258.92188, -133.29456, 31.48090,   -90.00000, 0.00000, 269.98669);
	CreateDynamicObject(19435, 2253.71558, -133.30487, 31.48090,   -90.00000, 0.00000, 269.98669);
	CreateDynamicObject(19435, 2257.19800, -133.29987, 31.48090,   -90.00000, 0.00000, 269.98669);

	// Int
	CreateDynamicObject(985, 257.06839, 128.11333, 1010.85620,   0.00000, 0.00000, 270.64240);
	CreateDynamicObject(985, 220.64571, 120.70450, 1010.85620,   0.00000, 0.00000, 270.64240);
	CreateDynamicObject(1536, 222.19060, 119.42220, 1009.21362,   0.00000, 0.00000, 0.00000);
	
	// Casinhas de blitz
	CreateDynamicObject(8168, 1396.75598, -1792.60522, 14.32857,   0.00000, 0.00000, -73.56001);
	CreateDynamicObject(1237, 1389.19678, -1790.74561, 12.37333,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1389.21240, -1786.03076, 12.37333,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1389.14685, -1795.30078, 12.37333,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1389.15393, -1799.63599, 12.37333,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1389.15784, -1781.10571, 12.37333,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19987, 1393.83618, -1818.83398, 12.36965,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19987, 1384.44946, -1754.81030, 12.32020,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(3578, 1388.99744, -1779.11658, 11.72290,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1388.97925, -1783.51892, 11.72290,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1388.91833, -1788.46216, 11.72290,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1389.24463, -1793.19751, 11.72290,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1389.26306, -1797.51807, 11.72290,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1388.94690, -1801.34888, 11.72293,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(8168, 1244.77136, -1408.27869, 13.76310,   0.00000, 0.00000, 196.98720);
	CreateDynamicObject(8168, 1220.64783, -1392.83972, 13.94310,   0.00000, 0.00000, 16.63600);
	CreateDynamicObject(1237, 1234.07178, -1400.53528, 12.08652,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1216.82764, -1400.53247, 12.08652,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1251.30945, -1400.50293, 12.08652,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19987, 1271.78101, -1390.51550, 12.22972,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19987, 1205.99231, -1410.57214, 12.22970,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(996, 1221.39636, -1401.01733, 12.63832,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(996, 1229.55945, -1401.02600, 12.65063,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(996, 1238.62439, -1400.93921, 12.65990,   0.00000, 0.40000, 0.00000);
	CreateDynamicObject(996, 1246.79590, -1400.87854, 12.65990,   0.00000, 0.40000, 0.00000);
	CreateDynamicObject(1425, 1219.24036, -1408.17358, 12.64112,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1237, 1219.12134, -1406.74548, 12.08652,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1219.22449, -1409.46472, 12.08652,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1425, 1239.21399, -1392.74036, 12.64110,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1237, 1239.24170, -1394.40161, 12.08652,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1239.24084, -1391.18066, 12.08652,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1247.03235, -1400.46863, 11.28530,   0.00000, 0.00000, 89.51890);
	CreateDynamicObject(3578, 1217.27832, -1400.53088, 11.46530,   0.00000, 0.00000, 89.51894);
	CreateDynamicObject(3578, 1219.72559, -1400.53088, 11.44530,   0.00000, 0.00000, 89.51890);
	CreateDynamicObject(3578, 1222.38879, -1400.55176, 11.42530,   0.00000, 0.00000, 89.51890);
	CreateDynamicObject(3578, 1225.23706, -1400.45789, 11.40530,   0.00000, 0.00000, 89.51890);
	CreateDynamicObject(3578, 1228.11572, -1400.42310, 11.38530,   0.00000, 0.00000, 89.51890);
	CreateDynamicObject(3578, 1230.97229, -1400.39722, 11.36530,   0.00000, 0.00000, 89.51890);
	CreateDynamicObject(3578, 1234.04114, -1400.45520, 11.34530,   0.00000, 0.00000, 89.51890);
	CreateDynamicObject(3578, 1237.11475, -1400.45837, 11.32530,   0.00000, 0.00000, 89.51890);
	CreateDynamicObject(3578, 1240.57605, -1400.46179, 11.30530,   0.00000, 0.00000, 89.51890);
	CreateDynamicObject(3578, 1243.81921, -1400.46521, 11.28530,   0.00000, 0.00000, 89.51890);
	CreateDynamicObject(8168, 1911.00635, -1453.43274, 14.29610,   0.00000, 0.00000, 16.25270);
	CreateDynamicObject(3578, 1905.36011, -1458.02551, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(3578, 1905.38013, -1468.72266, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(3578, 1914.98767, -1458.01416, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(3578, 1912.61707, -1458.02637, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(3578, 1910.05823, -1458.00232, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(3578, 1907.66150, -1458.03503, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(1237, 1896.06885, -1463.45349, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1926.06165, -1463.31958, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1914.91602, -1463.42200, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1912.55200, -1463.45178, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1910.02075, -1463.46375, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1907.62061, -1463.46777, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3578, 1917.41455, -1458.00061, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(3578, 1917.46448, -1468.71411, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(3578, 1915.02942, -1468.83655, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(3578, 1912.60535, -1468.79602, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(3578, 1910.06201, -1468.79858, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(3578, 1907.68347, -1468.74158, 11.63460,   0.00000, 0.00000, 90.11440);
	CreateDynamicObject(1237, 1917.36536, -1463.30884, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1919.80920, -1463.30261, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1921.87610, -1463.30957, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1924.02039, -1463.31470, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1905.29993, -1463.43066, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1902.88721, -1463.39758, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1900.53882, -1463.41724, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 1898.23120, -1463.43604, 12.37020,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19966, 1887.38818, -1472.27466, 12.53804,   0.00000, 0.00000, 269.40909);
	CreateDynamicObject(19966, 1941.01086, -1454.41943, 12.53970,   0.00000, 0.00000, 86.23914);
	CreateDynamicObject(8168, 2035.25488, -1759.86719, 14.29970,   0.00000, 0.00000, 196.27901);
	CreateDynamicObject(3578, 2028.52832, -1752.33032, 11.62915,   0.00000, 0.00000, 269.87296);
	CreateDynamicObject(3578, 2041.97009, -1752.30322, 11.62915,   0.00000, 0.00000, 269.87296);
	CreateDynamicObject(3578, 2039.70679, -1752.36719, 11.62915,   0.00000, 0.00000, 269.87296);
	CreateDynamicObject(3578, 2037.42065, -1752.35962, 11.62915,   0.00000, 0.00000, 269.87296);
	CreateDynamicObject(3578, 2035.19824, -1752.35254, 11.62915,   0.00000, 0.00000, 269.87296);
	CreateDynamicObject(3578, 2033.04272, -1752.34521, 11.62915,   0.00000, 0.00000, 269.87296);
	CreateDynamicObject(3578, 2030.76721, -1752.33740, 11.62915,   0.00000, 0.00000, 269.87296);
	CreateDynamicObject(1237, 2019.97424, -1752.44226, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2051.78809, -1752.36194, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2039.74561, -1752.48169, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2037.43701, -1752.45190, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2035.17334, -1752.45471, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2033.05688, -1752.46326, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2030.77405, -1752.45581, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2028.51428, -1752.44873, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2026.24060, -1752.47021, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2024.11584, -1752.45740, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2021.94983, -1752.45093, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2041.99475, -1752.39075, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2044.48181, -1752.38513, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2046.97961, -1752.37927, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1237, 2049.38257, -1752.37390, 12.37548,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19966, 2068.87744, -1745.77197, 12.54364,   0.00000, 0.00000, 86.90569);
	CreateDynamicObject(19966, 2002.19568, -1759.13770, 12.54321,   0.00000, 0.00000, 266.93433);

// COFRE DO NOVO SISTEMA DE ROUBO
	CreateObject(14576, 2148.12500, 1625.59387, 842.25775,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1496, 2151.46582, 1610.86548, 842.57263,   0.00000, 0.00000, 0.41059);
	CreateDynamicObject(1496, 2153.79956, 1609.81201, 842.53259,   0.00000, 0.00000, 269.65210);
	CreateDynamicObject(977, 2153.95898, 1608.24622, 843.86560,   0.00000, 0.00000, 101.01466);
	CreateObject(2634, 2151.77002, 1610.95508, 848.16687,   0.00000, 0.00000, 179.52090);
	CreateDynamicObject(1550, 2145.21655, 1647.36267, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2145.86182, 1648.32446, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2147.80908, 1648.14319, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2147.18237, 1648.63928, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2146.31738, 1648.56238, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2147.00659, 1647.77185, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2145.07935, 1648.82361, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2145.22656, 1648.13000, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2146.45093, 1647.78552, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2145.84888, 1647.65808, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2147.82397, 1648.70093, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2148.72949, 1648.55933, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2148.34692, 1648.83508, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2148.60767, 1647.87341, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2148.05664, 1647.65295, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2147.57666, 1647.21472, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2149.27930, 1648.52075, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2149.22388, 1647.75342, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2148.58105, 1647.17029, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2150.16553, 1648.48157, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2150.52905, 1648.52454, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2150.38037, 1647.57690, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2149.88330, 1647.71765, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2149.55762, 1647.08777, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2148.94678, 1646.82202, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2148.11182, 1647.01550, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2146.89502, 1646.94287, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1550, 2146.13818, 1646.89783, 834.46918,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19941, 2151.09058, 1648.18921, 834.06531,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19941, 2151.06665, 1647.68896, 834.06531,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19941, 2151.10083, 1648.40942, 834.06531,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19941, 2151.08643, 1648.10681, 834.06531,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19941, 2151.09595, 1648.30750, 834.06531,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19941, 2151.08154, 1648.00488, 834.06531,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19941, 2151.07690, 1647.90710, 834.06531,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19941, 2151.07227, 1647.80652, 834.06531,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19273, 2146.64551, 1612.74670, 835.40332,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19273, 2146.67065, 1633.03381, 835.57257,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(19273, 2146.66772, 1633.54883, 835.57257,   0.00000, 0.00000, 179.81781);

// Ilha 3
	CreateDynamicObject(16258, 2540.16895, 4383.14307, -45.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(6295, 2493.06763, 4382.46582, 29.90000,   0.00000, 0.00000, -107.22012);
	CreateDynamicObject(620, 2473.71021, 4399.65967, -1.22750,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(620, 2487.73877, 4411.15381, -0.22750,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(620, 2477.41235, 4368.96729, 2.27250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2481.02979, 4364.25293, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2484.87109, 4362.45850, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2488.51318, 4361.50635, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2492.59375, 4360.84814, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2495.27661, 4360.51270, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2507.17871, 4368.08398, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2512.37988, 4381.56836, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2514.24292, 4386.09229, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2515.72217, 4390.61035, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2516.27588, 4395.39258, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2476.70923, 4367.22070, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(620, 2512.65283, 4386.49414, 2.27250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2503.19067, 4365.55957, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2499.62256, 4363.30664, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2472.39258, 4372.78564, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2470.58594, 4379.05859, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2469.90015, 4385.26758, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2469.68579, 4392.77881, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2468.67383, 4399.13525, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2472.43872, 4403.75977, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2477.84009, 4406.83203, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2482.87524, 4409.87158, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2488.39331, 4409.12354, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2493.47974, 4407.34375, 2.36070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(620, 2497.24170, 4363.38574, 2.27250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(620, 2515.92090, 4396.82764, 2.27250,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11490, 2610.41821, 4362.12256, 7.10000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11491, 2610.40356, 4351.08496, 8.60000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18368, 2598.13354, 4346.69727, 2.70000,   0.00000, 0.00000, -96.66000);
	CreateDynamicObject(620, 2619.56372, 4354.36230, 1.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(620, 2602.79883, 4353.96484, 1.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2617.89771, 4354.79785, 6.57778,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2622.85547, 4357.81982, 6.57778,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2628.41406, 4358.15381, 6.57778,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2628.07520, 4352.18359, 6.57780,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2600.80249, 4355.10449, 7.30000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2600.44971, 4351.62451, 7.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2596.58301, 4356.24219, 7.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2595.53955, 4351.57178, 7.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2591.83081, 4353.26611, 7.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2593.56299, 4356.96484, 7.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(970, 2582.67480, 4354.56104, 7.64250,   0.00000, 0.00000, -33.12000);
	CreateDynamicObject(970, 2586.15063, 4352.27637, 7.64250,   0.00000, 0.00000, -33.12000);
	CreateDynamicObject(970, 2589.62598, 4349.99951, 7.64250,   0.00000, 0.00000, -33.12000);
	CreateDynamicObject(970, 2591.95898, 4348.46826, 7.64250,   0.00000, 0.00000, -33.12000);
	CreateDynamicObject(970, 2595.71826, 4347.41016, 7.64250,   0.00000, 0.00000, 1.68000);
	CreateDynamicObject(970, 2599.88281, 4347.52100, 7.64250,   0.00000, 0.00000, 1.68000);
	CreateDynamicObject(970, 2604.04883, 4347.63770, 7.64250,   0.00000, 0.00000, 1.68000);
	CreateDynamicObject(970, 2608.22827, 4347.72217, 7.64250,   0.00000, 0.00000, 1.68000);
	CreateDynamicObject(970, 2604.04883, 4347.63770, 7.64250,   0.00000, 0.00000, 1.68000);
	CreateDynamicObject(970, 2610.19189, 4347.70557, 7.64250,   0.00000, 0.00000, 1.68000);
	CreateDynamicObject(626, 2610.70679, 4353.03564, 10.60000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 2632.76196, 4357.04492, 4.63227,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 2632.39697, 4352.87109, 4.63227,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 2631.85864, 4348.70410, 4.63227,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 2630.09009, 4344.92285, 4.63227,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 2628.13525, 4341.96631, 4.63227,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(703, 2586.77832, 4357.25830, 6.45064,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 2629.04883, 4338.94971, 4.63227,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 2629.86475, 4335.93164, 4.63227,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 2629.18848, 4332.59326, 4.20000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(700, 2626.78735, 4329.85693, 4.10000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2579.30249, 4348.78809, 5.07780,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2582.00610, 4345.23389, 5.07780,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2584.55615, 4341.49414, 5.07780,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2587.00952, 4337.62939, 5.07780,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2589.75342, 4332.97803, 5.07780,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11245, 2610.41162, 4353.01270, 17.22780,   0.00000, -50.00000, -90.00000);
	CreateDynamicObject(821, 2578.36182, 4356.05469, 5.07780,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2630.00903, 4362.57373, 6.57778,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2627.80371, 4366.50830, 6.57778,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(821, 2623.11548, 4367.13330, 6.57778,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(703, 2631.35425, 4371.97705, 5.45060,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3461, 2619.06128, 4347.74463, 8.66490,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3461, 2615.45435, 4347.63574, 8.66490,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(9833, 2623.59009, 4352.53418, 10.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(9833, 2596.85425, 4352.69141, 10.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1704, 2611.63379, 4365.84277, 8.59927,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1704, 2613.91943, 4365.86670, 8.59927,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1557, 2608.91089, 4366.69971, 8.60174,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1557, 2611.91968, 4366.70703, 8.60170,   0.00000, 0.00000, 179.68018);
	CreateDynamicObject(1704, 2608.23511, 4365.87256, 8.59927,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1704, 2605.97632, 4365.87793, 8.59927,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3524, 2610.44043, 4354.56494, 6.80000,   0.00000, 0.00000, 900.00000);
	CreateDynamicObject(16151, 2606.92285, 4359.06494, 9.00000,   0.00000, 0.00000, 900.00000);
	CreateDynamicObject(703, 2621.41821, 4378.36426, 5.45060,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(703, 2608.27783, 4379.30273, 5.45060,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(703, 2597.04102, 4377.39502, 5.45060,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(703, 2588.09839, 4370.15430, 5.45060,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(824, 2503.28247, 4403.51807, 2.36070,   0.00000, 0.00000, -9.18000);
	CreateDynamicObject(824, 2508.42725, 4400.65527, 2.36070,   0.00000, 0.00000, -9.18000);
	CreateDynamicObject(824, 2511.71460, 4398.47461, 2.36070,   0.00000, 0.00000, -9.18000);
	CreateDynamicObject(19172, 2607.41333, 4366.27979, 10.68803,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19175, 2613.19409, 4366.36230, 10.68800,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19172, 2614.92603, 4359.31104, 11.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19174, 2614.97192, 4356.15967, 10.97640,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(16258, 2477.23633, 4322.29102, -51.70000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3615, 2540.63208, 4300.77588, 2.70000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1461, 2547.82886, 4291.09424, 1.90000,   0.00000, 0.00000, 900.00000);
	CreateDynamicObject(1461, 2548.14087, 4309.40869, 1.90000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(822, 2532.41333, 4293.82764, 1.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(823, 2531.91016, 4300.17334, 0.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(822, 2531.47656, 4306.59180, 1.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(822, 2538.08911, 4293.72217, 0.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(823, 2537.27295, 4295.57666, 1.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(823, 2538.22119, 4308.37646, 1.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1231, 2540.33423, 4303.73486, 2.90000,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(619, 2533.91064, 4306.82910, -5.00000,   -0.50000, 0.00000, 0.00000);
	CreateDynamicObject(619, 2536.52295, 4292.18896, -5.00000,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(620, 2543.48340, 4307.53223, -9.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(822, 2543.04370, 4294.61816, 1.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(823, 2533.47339, 4291.79102, 0.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(823, 2539.25171, 4290.32861, 1.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(823, 2542.98804, 4298.52783, 1.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(823, 2543.23853, 4307.45410, 1.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(823, 2534.00659, 4309.36377, 1.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(823, 2539.74585, 4309.64453, 1.00000,   0.00000, 0.00000, 0.00000);
	
// Island interior
	CreateDynamicObject(19599, 1003.46063, -599.29919, 1083.02856,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19325, 1002.22772, -600.78082, 1087.58459,   85.00000, 0.00000, 0.00000);
	CreateDynamicObject(19325, 1007.20581, -607.79950, 1087.58459,   91.00000, 0.00000, 90.00000);
	CreateDynamicObject(19325, 1003.15472, -607.71271, 1087.58459,   91.00000, 0.00000, 90.00000);
	CreateDynamicObject(19325, 1011.25238, -607.76660, 1087.58459,   91.00000, 0.00000, 90.00000);
	CreateDynamicObject(19325, 1015.36218, -607.79749, 1087.58459,   91.00000, 0.00000, 90.00000);
	CreateDynamicObject(19325, 1020.16217, -607.74506, 1087.58459,   91.00000, 0.00000, 90.00000);
	CreateDynamicObject(19325, 1012.54358, -594.62128, 1087.58459,   91.00000, 0.00000, 90.00000);
	CreateDynamicObject(19325, 1005.54773, -594.14240, 1087.58459,   91.00000, 0.00000, 90.00000);
	CreateDynamicObject(19325, 1010.81177, -606.40833, 1090.26465,   181.00000, 0.00000, 90.00000);
	CreateDynamicObject(19325, 1006.46649, -606.49030, 1090.26465,   181.00000, 0.00000, 90.00000);
	CreateDynamicObject(19325, 1021.75281, -604.16663, 1081.54956,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19325, 1021.75305, -597.54730, 1081.54956,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19325, 1021.94928, -606.94897, 1080.32959,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19325, 1020.06531, -606.91888, 1080.32959,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19325, 1004.02417, -606.87415, 1080.32959,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19325, 1004.88959, -606.85925, 1080.32959,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19325, 1002.20673, -606.70514, 1080.32959,   0.00000, 0.00000, -181.00000);
	CreateDynamicObject(19325, 1002.15802, -603.17456, 1080.32959,   0.00000, 0.00000, -181.00000);
	CreateDynamicObject(1557, 1008.42969, -606.90631, 1080.39355,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1557, 1011.42053, -606.90216, 1080.39355,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1557, 1015.11249, -606.88745, 1080.39355,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1557, 1012.12372, -606.89301, 1080.39355,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1535, 1015.10028, -596.40302, 1080.61145,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1535, 1015.10028, -596.40302, 1078.13147,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2957, 1005.75537, -595.27545, 1082.12305,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2957, 1011.15057, -595.31427, 1082.12305,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1709, 1008.22913, -605.26880, 1080.56982,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2313, 1003.73529, -602.51440, 1080.57263,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19786, 1004.43658, -602.09448, 1082.37378,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2230, 1006.22961, -601.91449, 1081.46216,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2230, 1003.25702, -601.89801, 1081.46216,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2135, 1018.39111, -594.35315, 1080.57031,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2137, 1017.38684, -594.33398, 1080.55261,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2136, 1021.20471, -595.36884, 1080.57104,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2305, 1021.14374, -594.36560, 1080.57288,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2140, 1019.70398, -594.25049, 1080.57153,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2029, 1018.86169, -600.99402, 1080.57153,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2029, 1018.86920, -602.95569, 1080.57153,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2124, 1018.16052, -600.04169, 1081.39185,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2124, 1018.17017, -600.76947, 1081.39185,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2124, 1018.22571, -602.20569, 1081.39185,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2124, 1018.21283, -602.90576, 1081.39185,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2124, 1018.26331, -601.52264, 1081.39185,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2124, 1019.45038, -602.78381, 1081.39185,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2124, 1019.45038, -602.06378, 1081.39185,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2124, 1019.45038, -602.78381, 1081.39185,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2124, 1019.45038, -601.38379, 1081.39185,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2124, 1019.45038, -600.68378, 1081.39185,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2124, 1019.45038, -600.00378, 1081.39185,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1433, 1014.40649, -602.95490, 1080.75183,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2245, 1014.40723, -602.94952, 1081.51733,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11392, 1005.29706, -595.62292, 1080.57166,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19815, 1002.38586, -597.33423, 1082.79810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(936, 1002.90466, -597.24408, 1080.95142,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19631, 1002.98474, -597.82343, 1081.48474,   0.00000, 86.00000, -18.00000);
	CreateDynamicObject(19899, 1014.19983, -598.39648, 1080.57166,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(19787, 1009.37347, -601.92548, 1082.55640,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(1518, 1014.83423, -595.27887, 1082.35889,   0.00000, 0.00000, -56.00000);
	CreateDynamicObject(19621, 1013.88605, -597.45605, 1081.90125,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1644, 1014.82837, -595.76294, 1081.43738,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1025, 1014.23462, -599.05908, 1082.12366,   0.00000, -20.00000, -185.00000);
	CreateDynamicObject(11289, 1005.07562, -601.50269, 1080.95068,   -14.00000, 0.00000, 179.00000);
	CreateDynamicObject(2062, 1009.96118, -601.57233, 1081.17212,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2062, 1008.30060, -601.57013, 1081.17212,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2062, 1009.10046, -601.55206, 1081.17212,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(18634, 1003.18817, -597.01532, 1081.44556,   0.00000, -88.00000, 55.00000);
	CreateDynamicObject(18644, 1002.94128, -597.09949, 1081.42542,   0.00000, 91.00000, 0.00000);
	CreateDynamicObject(18635, 1003.24249, -597.50427, 1081.40491,   90.00000, 0.00000, 18.00000);
	CreateDynamicObject(330, 1014.73602, -595.39392, 1082.77722,   89.00000, 0.00000, 2.00000);
	CreateDynamicObject(2650, 1011.72772, -601.79602, 1082.24988,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(2406, 1002.43347, -599.55212, 1081.84021,   -6.00000, 0.00000, 88.00000);
	CreateDynamicObject(19806, 1018.90112, -601.38751, 1083.05933,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(14446, 1018.83618, -601.79865, 1084.56665,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(11724, 1008.65039, -595.07172, 1084.51050,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(11725, 1008.64160, -595.16278, 1084.37988,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1705, 1008.12665, -597.43420, 1083.99146,   0.00000, 0.00000, 142.00000);
	CreateDynamicObject(1705, 1010.01971, -596.80670, 1083.99146,   0.00000, 0.00000, 216.00000);
	CreateDynamicObject(19787, 1008.61578, -594.68561, 1086.09265,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2286, 1012.23761, -602.12061, 1082.87683,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2491, 1020.52417, -599.41003, 1083.99146,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2491, 1020.69818, -603.76843, 1083.99146,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19318, 1020.63751, -601.83508, 1086.15125,   0.00000, 90.00000, -90.00000);
	CreateDynamicObject(2404, 1014.79352, -605.25873, 1088.37634,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2405, 1014.80798, -602.42267, 1088.22229,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19317, 1014.80450, -603.96948, 1088.35144,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19319, 1014.79272, -600.81567, 1088.15564,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19617, 1014.84149, -598.48248, 1088.01770,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19609, 1019.42688, -596.59106, 1083.99146,   0.00000, 0.00000, -38.00000);
	CreateDynamicObject(2276, 1003.14490, -595.24603, 1086.16272,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19174, 1002.34412, -604.25452, 1086.88013,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2169, 1002.86371, -598.12042, 1083.99060,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19893, 1002.85199, -597.50958, 1084.77856,   0.00000, 0.00000, 84.00000);
	CreateDynamicObject(1714, 1003.93823, -597.54419, 1083.99280,   0.00000, 0.00000, -82.00000);
	CreateDynamicObject(2953, 1002.95331, -598.10901, 1084.80115,   0.00000, 0.00000, 52.00000);
	CreateDynamicObject(2201, 1002.53754, -596.65057, 1084.78015,   0.00000, 0.00000, 84.00000);
	CreateDynamicObject(14867, 1011.22107, -607.26917, 1085.37170,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19805, 1002.38348, -597.51630, 1086.17944,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19878, 1011.14063, -603.47498, 1084.39246,   0.00000, 64.00000, 0.00000);
	CreateDynamicObject(19619, 1020.61420, -605.46222, 1085.75110,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2255, 1005.34601, -607.19397, 1085.37744,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2267, 1020.58948, -597.36560, 1086.24390,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(2259, 1015.31140, -598.51001, 1082.02222,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1502, 1014.76886, -601.78986, 1080.57178,   0.00000, 0.00000, 90.00000);

	// HQ Radio
	new tmpobjid = CreateDynamicObjectEx(19377,1964.701,1911.844,935.113,0.000,90.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper4-2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1969.856,1911.836,936.529,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1965.226,1916.666,936.529,0.000,0.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1965.226,1906.954,936.529,0.000,0.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(14387,1958.141,1914.312,934.198,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(14387,1958.141,1909.611,934.198,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1958.596,1906.952,936.529,0.000,0.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1958.596,1916.694,936.529,0.000,0.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1953.355,1912.204,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(14387,1958.001,1904.961,934.198,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1953.985,1902.112,936.529,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1953.835,1921.442,936.529,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1953.365,1922.704,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1953.365,1901.741,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1949.375,1926.214,936.529,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1949.284,1897.211,936.529,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1943.755,1901.741,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1943.725,1912.213,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1943.735,1922.704,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1944.575,1930.954,936.529,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1939.954,1931.295,936.529,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1943.747,1933.175,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1934.127,1933.175,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1934.127,1922.704,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1934.127,1912.254,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1934.127,1901.754,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1939.653,1897.211,936.529,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1930.033,1897.211,936.529,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1925.263,1902.121,936.529,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1920.343,1906.880,936.529,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1925.263,1921.341,936.529,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1925.263,1930.971,936.529,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1930.354,1931.295,936.529,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1924.497,1933.175,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1924.497,1922.695,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1924.497,1912.206,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1924.497,1901.726,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1920.993,1931.295,936.529,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19449,1952.358,1902.074,935.056,0.000,90.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper4-2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1950.664,1902.112,929.870,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1955.455,1906.822,929.870,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(12950,1953.299,1910.132,931.684,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19531,1949.878,1868.947,941.724,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18996, "mattextures", "sampblack", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19449,1945.828,1898.434,935.056,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper4-2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19449,1936.259,1898.434,935.056,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper4-2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19449,1926.696,1898.434,935.056,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper4-2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1918.123,1911.750,936.529,0.000,0.000,540.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1920.524,1916.571,936.529,0.000,0.000,630.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1914.938,1912.206,933.129,0.000,90.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1924.912,1914.895,933.129,0.000,0.000,540.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1919.876,1910.104,932.008,0.000,180.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1924.912,1914.895,945.569,0.000,0.000,540.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19387,1924.809,1908.475,934.725,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18641, "flashlight1", "metalblack1-2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1924.912,1905.534,941.698,0.000,0.000,540.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(12950,1923.068,1909.468,933.955,0.000,0.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1919.596,1914.854,937.218,0.000,270.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1950.664,1900.180,929.870,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1941.054,1900.180,929.870,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1931.435,1900.180,929.870,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1921.765,1900.180,929.870,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(970,1950.655,1902.228,935.625,0.000,0.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(970,1948.624,1900.158,935.625,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(970,1944.464,1900.158,935.625,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(970,1940.363,1900.158,935.625,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(970,1936.223,1900.158,935.625,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(970,1932.052,1900.158,935.625,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(12950,1926.078,1905.461,931.754,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(970,1928.832,1900.148,935.625,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1935.743,1930.954,936.529,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19387,1934.059,1926.155,934.725,0.000,0.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18641, "flashlight1", "metalblack1-2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1930.953,1926.202,941.469,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1927.713,1926.202,931.069,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1921.573,1926.202,941.429,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1940.593,1926.202,941.429,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19387,1937.359,1926.215,934.725,0.000,0.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18641, "flashlight1", "metalblack1-2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1943.784,1926.272,930.959,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 2627, "genintint_gym", "bench_test2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1930.194,1931.485,933.189,0.000,90.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19853, "mihouse1", "tilesswimmingpool2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1939.823,1931.485,933.189,0.000,90.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19853, "mihouse1", "tilesswimmingpool2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1930.364,1931.265,936.529,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1925.463,1931.041,936.529,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1930.953,1926.242,941.469,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1921.573,1926.232,941.429,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1927.713,1926.222,931.069,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1935.693,1931.014,936.529,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1935.783,1931.014,936.529,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1944.515,1931.004,936.529,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1943.784,1926.292,930.959,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1940.593,1926.232,941.469,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1502,1933.249,1926.187,933.215,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14489, "carlspics", "AH_picture3", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 10713, "gayclub_sfs", "CJ_PIZZA_DOOR", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1502,1936.540,1926.197,933.215,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14489, "carlspics", "AH_picture3", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 10713, "gayclub_sfs", "CJ_PIZZA_DOOR", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19449,1926.516,1921.454,935.056,0.000,90.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper4-2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19449,1927.796,1924.533,935.036,0.000,90.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper4-2", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1923.434,1916.661,929.870,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1928.226,1921.432,929.870,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1927.746,1922.802,929.870,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(12950,1925.536,1912.500,931.714,0.000,0.000,720.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 6871, "vegascourtbld", "marbletilewal1_256", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(970,1930.442,1922.798,935.625,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(970,1928.273,1920.677,935.625,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "dt_office_gls_text", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19449,1932.477,1924.318,930.230,91.300,360.000,-179.500);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(14537,1951.692,1922.523,934.995,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2292,1947.388,1901.130,933.215,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1946.993,1901.152,933.215,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1946.122,1901.152,933.215,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1945.252,1901.152,933.215,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1944.542,1901.152,933.215,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1943.622,1901.152,933.215,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1942.731,1901.152,933.215,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2292,1941.351,1901.095,933.215,0.000,0.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1823,1946.420,1902.244,933.215,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1823,1942.136,1902.471,933.215,0.000,0.000,21.899);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1934.541,1901.152,933.215,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1935.381,1901.152,933.215,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1936.272,1901.152,933.215,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1936.582,1903.352,933.215,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1936.582,1904.173,933.215,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1933.461,1903.142,933.215,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1933.461,1902.262,933.215,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1823,1934.792,1902.321,933.215,0.000,0.000,21.899);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2292,1928.807,1917.080,933.215,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1928.810,1917.471,933.215,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1928.810,1918.302,933.215,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1928.810,1919.162,933.215,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1928.810,1920.043,933.215,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1928.810,1920.893,933.215,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1928.660,1922.263,933.215,0.000,0.000,720.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1929.481,1922.263,933.215,0.000,0.000,720.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2291,1930.451,1922.263,933.215,0.000,0.000,720.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2292,1931.832,1922.305,933.215,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1823,1930.313,1917.107,933.215,0.000,0.000,21.899);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1823,1930.681,1920.078,933.215,0.000,0.000,21.899);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1723,1949.721,1897.828,935.142,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1723,1944.960,1897.828,935.142,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1723,1939.941,1897.828,935.142,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2315,1947.832,1899.599,935.142,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2315,1942.897,1899.602,935.142,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2315,1937.987,1899.602,935.142,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1724,1932.280,1898.852,935.142,0.000,0.000,90.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1724,1936.141,1900.032,935.142,0.000,0.000,270.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1433,1934.107,1899.452,935.292,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1724,1929.320,1897.682,935.142,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1724,1927.559,1897.682,935.142,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1724,1928.010,1919.001,935.142,0.000,0.000,180.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1724,1927.089,1922.312,935.142,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1433,1927.687,1920.582,935.292,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1724,1928.090,1925.513,935.142,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(1724,1930.780,1925.513,935.142,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14738, "whorebar", "AH_cheapwindow", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2491,1945.978,1906.973,932.874,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2491,1942.268,1906.973,932.874,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2491,1937.737,1906.973,932.874,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(2491,1932.927,1906.973,932.874,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1928.103,1930.941,941.389,0.000,0.000,540.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1923.253,1928.800,936.529,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19387,1928.094,1930.220,934.515,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19387,1928.044,1927.739,934.515,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1923.183,1931.191,934.909,0.000,0.000,630.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1941.373,1931.004,941.179,0.000,0.000,360.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19387,1941.387,1930.079,934.775,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19377,1946.213,1928.774,937.319,0.000,0.000,450.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19387,1941.427,1927.809,934.775,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19357,1969.836,1911.841,936.719,0.000,0.000,0.000);
	SetDynamicObjectMaterial(tmpobjid, 0, 8391, "ballys01", "vgncorpdoor1_512", 0x00000000);
	tmpobjid = CreateDynamicObjectEx(19329,1918.287,1913.756,940.595,-0.400,-39.400,88.100);
	SetDynamicObjectMaterialText(tmpobjid, 0, "DJ", 20, "Ariel", 20, 1, 0xFF0000A0, 0x00000000, 0);
	tmpobjid = CreateDynamicObjectEx(19329,1918.303,1914.143,940.123,-0.400,-39.400,88.100);
	SetDynamicObjectMaterialText(tmpobjid, 0, "Tiesto", 20, "Ariel", 20, 1, 0xFF0000A0, 0x00000000, 0);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tmpobjid = CreateDynamicObjectEx(18648,1954.195,1918.742,941.915,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18648,1954.195,1923.362,941.915,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18648,1950.546,1926.014,941.595,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(18648,1945.406,1926.564,941.945,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(18648,1941.106,1926.564,941.945,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(18648,1936.406,1926.564,941.945,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(18648,1933.035,1926.564,941.945,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(18648,1929.715,1926.564,941.945,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(18648,1925.635,1926.564,941.945,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(18648,1924.935,1923.104,941.865,0.000,0.000,180.000);
	tmpobjid = CreateDynamicObjectEx(18648,1924.946,1913.413,942.065,0.000,0.000,180.000);
	tmpobjid = CreateDynamicObjectEx(18648,1924.935,1905.603,941.865,0.000,0.000,180.000);
	tmpobjid = CreateDynamicObjectEx(18648,1924.935,1898.823,941.865,0.000,0.000,180.000);
	tmpobjid = CreateDynamicObjectEx(18648,1929.165,1896.923,941.865,0.000,0.000,270.000);
	tmpobjid = CreateDynamicObjectEx(18648,1934.975,1896.923,941.865,0.000,0.000,270.000);
	tmpobjid = CreateDynamicObjectEx(18648,1941.485,1896.923,941.865,0.000,0.000,270.000);
	tmpobjid = CreateDynamicObjectEx(18648,1947.315,1896.923,941.865,0.000,0.000,270.000);
	tmpobjid = CreateDynamicObjectEx(18648,1951.155,1896.923,941.865,0.000,0.000,270.000);
	tmpobjid = CreateDynamicObjectEx(18648,1954.035,1898.883,941.865,0.000,0.000,360.000);
	tmpobjid = CreateDynamicObjectEx(18648,1954.035,1903.754,941.865,0.000,0.000,360.000);
	tmpobjid = CreateDynamicObjectEx(5992,1923.455,1913.497,943.944,0.000,0.000,270.000);
	tmpobjid = CreateDynamicObjectEx(18648,1955.775,1906.525,941.865,0.000,0.000,450.000);
	tmpobjid = CreateDynamicObjectEx(18648,1958.046,1906.525,941.865,0.000,0.000,450.000);
	tmpobjid = CreateDynamicObjectEx(18648,1962.366,1906.525,941.865,0.000,0.000,450.000);
	tmpobjid = CreateDynamicObjectEx(18648,1966.037,1906.525,941.865,0.000,0.000,450.000);
	tmpobjid = CreateDynamicObjectEx(18648,1967.546,1916.965,941.846,0.000,0.000,450.000);
	tmpobjid = CreateDynamicObjectEx(18648,1962.556,1916.965,941.846,0.000,0.000,450.000);
	tmpobjid = CreateDynamicObjectEx(18648,1956.567,1916.965,941.846,0.000,0.000,450.000);
	tmpobjid = CreateDynamicObjectEx(18655,1924.892,1909.873,936.495,0.000,0.000,180.000);
	tmpobjid = CreateDynamicObjectEx(18655,1925.212,1917.293,936.495,0.000,0.000,180.000);
	tmpobjid = CreateDynamicObjectEx(18102,1947.469,1917.841,941.675,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(18102,1940.328,1917.841,941.675,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(2773,1951.823,1906.604,935.635,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(2773,1950.843,1905.464,935.635,0.000,0.000,180.000);
	tmpobjid = CreateDynamicObjectEx(2773,1927.163,1916.924,935.635,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(2773,1928.083,1917.965,935.635,0.000,0.000,180.000);
	tmpobjid = CreateDynamicObjectEx(2773,1932.423,1924.435,935.635,0.000,0.000,180.000);
	tmpobjid = CreateDynamicObjectEx(1716,1949.959,1917.354,933.215,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1716,1947.749,1917.354,933.215,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1716,1946.610,1918.784,933.215,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1716,1946.610,1920.544,933.215,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(2524,1928.875,1930.530,933.275,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(2524,1930.676,1930.530,933.275,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(2524,1932.876,1930.530,933.275,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1929.669,1931.136,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(2528,1926.160,1927.300,933.275,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(2528,1926.160,1930.100,933.275,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(1523,1928.026,1928.526,932.854,0.000,0.000,270.000);
	tmpobjid = CreateDynamicObjectEx(1523,1928.026,1930.996,932.854,0.000,0.000,270.000);
	tmpobjid = CreateDynamicObjectEx(19159,1940.017,1914.949,941.454,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(2525,1943.840,1930.267,933.255,0.000,0.000,270.000);
	tmpobjid = CreateDynamicObjectEx(2525,1943.840,1927.176,933.255,0.000,0.000,270.000);
	tmpobjid = CreateDynamicObjectEx(1523,1941.435,1929.371,933.275,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(1523,1941.475,1926.979,933.275,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(18001,1937.830,1931.126,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1937.830,1931.126,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1937.830,1931.126,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1937.830,1931.126,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1937.830,1931.126,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1937.830,1931.126,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1937.830,1931.126,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1937.830,1931.126,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1937.830,1931.126,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(18001,1937.830,1931.126,935.425,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(2524,1936.835,1930.530,933.275,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(2524,1938.265,1930.530,933.275,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(2524,1940.155,1930.530,933.275,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1510,1946.836,1902.795,933.735,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1520,1947.125,1902.579,933.785,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1946.606,1902.663,933.815,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1951,1942.468,1903.199,933.895,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1951,1942.698,1903.199,933.895,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1942.152,1903.010,933.805,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1942.152,1902.800,933.805,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1935.562,1902.800,933.805,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1934.901,1903.131,933.805,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1934.901,1902.710,933.805,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1935.262,1903.381,933.805,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1951,1932.660,1906.590,934.925,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1932.802,1906.892,934.855,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1932.582,1906.892,934.855,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1937.352,1906.892,934.855,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1937.352,1906.682,934.855,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1937.562,1906.682,934.855,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1509,1941.960,1906.728,934.935,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1942.052,1906.882,934.855,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1520,1945.702,1906.638,934.845,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1520,1945.702,1906.949,934.845,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1520,1948.913,1899.489,935.675,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1520,1947.852,1899.489,935.675,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1949.056,1899.368,935.742,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1948.236,1899.368,935.742,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1944.256,1899.368,935.742,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1943.196,1899.368,935.742,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1951,1934.106,1899.468,935.962,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1934.355,1899.368,935.882,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1667,1933.765,1899.368,935.882,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1544,1930.879,1917.799,933.715,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1544,1930.518,1917.709,933.715,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(1517,1930.823,1920.666,933.905,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(14391,1922.424,1913.361,937.984,0.000,0.000,180.000);
	tmpobjid = CreateDynamicObjectEx(2229,1924.935,1910.771,936.865,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(2229,1924.815,1915.722,936.865,0.000,0.000,90.000);
	tmpobjid = CreateDynamicObjectEx(2240,1969.297,1916.105,935.679,0.000,0.000,0.000);
	tmpobjid = CreateDynamicObjectEx(2240,1969.297,1907.614,935.679,0.000,0.000,0.000);

// Escada casa de vidro
	/*CreateDynamicObject(3361, 939.59979, -2145.85229, 1.89399,   0.00000, 0.00000, 176.41638);
	CreateDynamicObject(3361, 955.90460, -2146.89478, 10.05786,   0.00000, 0.00000, 176.41638);
	CreateDynamicObject(3361, 947.72876, -2146.37671, 5.89935,   0.00000, 0.00000, 176.41638);*/

	// Apartamento
	new VIPLounge;

	CreateDynamicObject(2773, 1511.81335, -1056.29822, 24.55680,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2773, 1507.45996, -1056.27979, 24.55580,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2773, 1507.45935, -1060.13696, 24.55580,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2773, 1507.44592, -1058.20972, 24.55580,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2773, 1511.80884, -1060.13892, 24.55680,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2773, 1511.80615, -1058.21521, 24.55680,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19121, 1512.97156, -1060.28979, 24.55853,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19121, 1506.21863, -1060.21558, 24.55853,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19121, 1506.22607, -1055.50391, 24.55853,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19121, 1512.96899, -1055.70117, 24.55853,   0.00000, 0.00000, 0.00000);
	VIPLounge = CreateDynamicObject(10184, 1509.61584, -1062.10840, 23.91060,   0.00000, -90.00000, 0.00000);
	SetDynamicObjectMaterial(VIPLounge, 0, 17925, "lae2fake_int", "carpet1kb", 0xFFFF0000);
	
	// Cativeiro
	CreateDynamicObject(3095, 2561.73096, -1279.29565, 1030.54211,   0.00000, -90.00000, -90.00000);
	CreateDynamicObject(19834, 2560.57935, -1279.30615, 1031.65295,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19834, 2562.89136, -1279.30615, 1031.65295,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3383, 2555.51221, -1290.22400, 1030.39539,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19836, 2555.85815, -1290.24194, 1031.46375,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19836, 2555.72656, -1289.34631, 1031.46375,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19836, 2555.34766, -1290.93787, 1031.46375,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19836, 2556.56567, -1290.04565, 1030.43188,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19836, 2556.66504, -1289.32495, 1030.43176,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3095, 2565.88745, -1300.59143, 1030.54211,   0.00000, -90.00000, 180.00000);

	// Interior fazenda
	CreateObject(19881, 286.19073, 307.63016, 1002.01147,   0.00000, 0.00000, 0.00000);// Base interior
	CreateDynamicObject(14875, 284.19800, 307.58270, 1003.21948,   0.00000, 0.00000, 180.65829);
	
	// LS Apartamento building
	for(new andares; andares < 20; andares++) {
		CreateDynamicObject(2001, 1817.97913, -1292.56543, 21.20304 + (andares * 5.453),   0.00000, 0.00000, 0.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(2001, 1813.39819, -1306.39294, 21.20172 + (andares * 5.453),   0.00000, 0.00000, 0.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(19858, 1824.19800, -1306.83838, 22.42780 + (andares * 5.453),   0.00000, 0.00000, -90.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(19858, 1824.20886, -1292.84998, 22.42780 + (andares * 5.453),   0.00000, 0.00000, -90.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(19858, 1812.59082, -1305.89465, 22.42700 + (andares * 5.453),   0.00000, 0.00000, 180.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(19858, 1818.48511, -1291.63953, 22.42310 + (andares * 5.453),   0.00000, 0.00000, 90.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(2001, 1824.96240, -1291.90918, 21.20114 + (andares * 5.453),   0.00000, 0.00000, 0.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(2817, 1812.31702, -1306.49341, 21.20310 + (andares * 5.453),   0.00000, 0.00000, 179.70641, -1, -1, -1, 50.0);
		CreateDynamicObject(2817, 1824.78760, -1293.12610, 21.20310 + (andares * 5.453),   0.00000, 0.00000, 270.63669, -1, -1, -1, 50.0);
		CreateDynamicObject(2001, 1824.80469, -1305.80139, 21.20172 + (andares * 5.453),   0.00000, 0.00000, 0.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(2817, 1824.80151, -1307.09497, 21.20310 + (andares * 5.453),   0.00000, 0.00000, 270.63669, -1, -1, -1, 50.0);
		CreateDynamicObject(2817, 1810.60730, -1300.94958, 21.20225 + (andares * 5.453),   0.00000, 0.00000, 0.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(2817, 1816.88672, -1290.37292, 21.20148 + (andares * 5.453),   0.00000, 0.00000, 270.03693, -1, -1, -1, 50.0);
		CreateDynamicObject(1893, 1816.90210, -1291.63086, 26.06750 + (andares * 5.453),   0.00000, 0.00000, 90.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(1893, 1825.65601, -1294.14038, 26.06750 + (andares * 5.453),   0.00000, 0.00000, 90.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(1893, 1825.57825, -1308.01196, 26.06750 + (andares * 5.453),   0.00000, 0.00000, 90.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(1893, 1811.28552, -1307.11169, 26.06750 + (andares * 5.453),   0.00000, 0.00000, 0.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(1893, 1810.68396, -1299.71399, 26.06750 + (andares * 5.453),   0.00000, 0.00000, 0.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(3657, 1824.63794, -1299.90198, 21.70690 + (andares * 5.453),   0.00000, 0.00000, 90.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(3657, 1818.07263, -1297.10449, 21.70690 + (andares * 5.453),   0.00000, 0.00000, -90.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(3657, 1818.08569, -1308.71167, 21.70690 + (andares * 5.453),   0.00000, 0.00000, -90.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(2001, 1813.05774, -1300.89355, 21.20113 + (andares * 5.453),   0.00000, 0.00000, 0.00000, -1, -1, -1, 50.0);
		CreateDynamicObject(19858, 1810.34985, -1301.57190, 22.42310 + (andares * 5.453),   0.00000, 0.00000, 0.00000, -1, -1, -1, 50.0);
	}
	return 1;
}

CMD:pyakuza1(playerid)
{
	if(!IsPlayerInRangeOfPoint(playerid, 15.0,664.8619,-1307.4937,22.3109) || GetPlayerOrg(playerid) != 13)return true;
	MoveDynamicObject(pYak1, 664.8619,-1307.4937,22.3109,3,0.0000,0.0000,0.0000);
	SetTimer(#MovepYak1, 5000, false);
	SendClientMessage(playerid, 0x2641FEFF, #Portao aberto);
	return true;
}
CALLBACK:MovepYak1()
{
	MoveDynamicObject(pYak1,664.8619, -1307.4937, 15.3109,3,0.0000, 0.0000, 0.0000);
	return true;
}
//------------------- portao yakuza 2 --------------------
CMD:pyakuza2(playerid)
{
	if(!IsPlayerInRangeOfPoint(playerid, 15.0,660.7543,-1227.8146,24.4440)|| GetPlayerOrg(playerid) != 13)return true;
	MoveDynamicObject(pYak2, 660.7543,-1227.8146,24.4440,3,0.0000,0.0000,-118.2998);
	SetTimer(#MovepYak2, 5000, false);
	SendClientMessage(playerid, 0x2641FEFF, #Portao aberto);
	return true;
}
CALLBACK:MovepYak2()
{
	MoveDynamicObject(pYak2,660.7543, -1227.8146, 17.4440,3,0.0000, 0.0000, -118.2998);
	return true;
}
//----------------- portao yakuza 3 ---------------------
CMD:pyakuza3(playerid)
{
	if(!IsPlayerInRangeOfPoint(playerid, 15.0,783.9084,-1152.4266,32.4053)|| GetPlayerOrg(playerid) != 13)return true;
	MoveDynamicObject(pYak3, 783.9084,-1152.4266,32.4053,3,0.0000,0.0000,-90.2999);
	SetTimer(#MovepYak3, 5000, false);
	SendClientMessage(playerid, 0x2641FEFF, #Portao aberto);
	return true;
}
CALLBACK:MovepYak3()
{
	MoveDynamicObject(pYak3,783.9084, -1152.4266, 25.4053,3,0.0000, 0.0000, -90.2999);
	return true;
}
CALLBACK:GaragemDpClosed2()
{
	MoveDynamicObject(PDDOORb,250.774871 , 60.822799 , 1003.640625, 2);//GaragemClosed
	return true;
}

CALLBACK:GaragemDpClosed()
{
	MoveDynamicObject(PDDOORa,247.005905 , 72.448440 , 1003.640625, 2);//GaragemClosed
	return true;
}

CALLBACK:PCClosed()
{
    MoveDynamicObject(PDDOORb,248.142105 , 78.125961 , 1003.640625, 2);//CelaClosed
	return true;
}

CALLBACK:pd1()
{
	MoveDynamicObject(PDDOORc,248.142105 , 78.125961 , 1003.640625, 2);//GaragemClosed
	return true;
}

CALLBACK:pd2()
{
	MoveDynamicObject(PDPMLS,1546.8681640625, -1627.3585205078, 15.156204223633, 2);//GaragemClosed
	return true;
}

CALLBACK:pd4()
{
	MoveDynamicObject(PDELEVATOR,1549.049804 , -1697.787109 , 12.5514954, 2);//GaragemClosed
	return true;
}

CALLBACK:PTPMSF()
{
	MoveDynamicObject(PortaoPMSF,-1571.8000488281,661.09997558594,6.6999998092651, 2);//GateClosed
	return true;
}

CALLBACK:PortaoHit3()
{
	MoveDynamicObject(PortaoHit1,956.80456542969, -1503.0864257813, 15.321235656738, 2);//Portao HIT 1 Closed
	return true;
}
CALLBACK:PortaoTriad2()
{
	MoveDynamicObject(PortaoTriad1,1620.7049560547, -1861.2620849609, 15.324647903442, 2);//Portao Triad 1 Closed
	return true;
}

CALLBACK:FecharReporter() {
	MoveDynamicObject(PortaoReporter[0], 778.11206, -1384.84778, 13.94793, 2);     /* Portão dos San News Fechado */
	return true;
}

CALLBACK:FecharReporter2() {

	MoveDynamicObject(PortaoReporter[1], 777.45294, -1330.08032, 13.69681, 2);      /* Portão dos San News Fechado */
	return true;
}

CALLBACK:PortaoRally2() {
	MoveDynamicObject(PortaoRally,-2368.4670410156, -2192.6381835938, 36.037666320801, 2);//Portao Rally Closed
	return true;
}

CMD:pitaliana(playerid)
{
	if ((GetPlayerOrg(playerid) == 12) && PlayerToPoint(20.0, playerid, 222.95401, -1434.97827, 14.91388))
	{
		MoveDynamicObject(portaoRussa, 222.95401, -1434.97827, 14.91388 - 10.0, 3, 0.00000, 0.00000, 223.62000);
		SetTimer(#MovePortaoRussa, 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}

CALLBACK:MovePortaoRussa()
{
	MoveDynamicObject(portaoRussa, 222.95401, -1434.97827, 14.91388,3, 0.00000, 0.00000, 223.62000);
    return true;
}

CMD:pcn(playerid)
{
	if (GetPlayerOrg(playerid) == 24 && PlayerToPoint(25.0, playerid, 493.8057,-1547.1104,9.8590))
	{
	    MoveDynamicObject(PortaoCN, 493.8057,-1547.1104,9.8590,3,0.0000,0.0000,210.6994);
	    SetTimer(#MovePortaoCN, 5000, false);
		GameTextForPlayer(playerid, "~g~Aberto", 5000, 3);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
    }
    return true;
}

CALLBACK:MovePortaoCN()
{
    MoveDynamicObject(PortaoCN,493.8057, -1547.1104, 19.8590,3,0.0000, 0.0000, 210.6994);
    return true;
}
/* 				Portão Organização | Warlocks			*/
CMD:pwar(playerid)
{
	if (GetPlayerOrg(playerid) == 28 && PlayerToPoint(25.0, playerid, 702.0000,-475.1000100,17.1000))
	{
	    MoveDynamicObject(PortaoMayans, 702.0000,-475.1000100,17.1000 - 10.0, 3, 0.0000, 0.0000, 0.0000);
	    SetTimer(#MovePortaoMayans, 5000, false);
		GameTextForPlayer(playerid, "~g~Aberto", 5000, 3);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
    }
    return true;
}

CALLBACK:MovePortaoMayans()
{
    MoveDynamicObject(PortaoMayans,702.0000,-475.1000100,17.1000,3,0.0000, 0.0000, 0.0000);
    return true;
}

CMD:preporter(playerid)
{
	if (GetPlayerOrg(playerid) == 9 && PlayerToPoint(15.0, playerid, 778.11206, -1384.84778, 13.94793)) {   /*     Portão San News     */

		MoveDynamicObject( PortaoReporter[0], 778.11206, -1384.84778, 13.94793 - 10.0,3,0.0, 0.0, 179.73135);
		GameTextForPlayer(playerid, "~w~Portao ~y~Reporter ~n~~b~Aberto", 5000, 3);
		SetTimer("FecharReporter", 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}

CMD:preporter2(playerid)
{
	if (GetPlayerOrg(playerid) == 9 && PlayerToPoint(15.0, playerid, 777.45294, -1330.08032, 13.69681)) {   /*     Portão San News 2     */

		MoveDynamicObject( PortaoReporter[1], 777.45294, -1330.08032, 13.69681 - 10.0,3,0.0, 0.0, 357.97565);
		GameTextForPlayer(playerid, "~w~Portao ~y~Reporter ~n~~b~Aberto", 5000, 3);
		SetTimer("FecharReporter2", 5000, false);
		SendClientMessage(playerid, TEAM_BALLAS_COLOR, "O Portão Fechará em 5 segundos.");
	}
  	return true;
}