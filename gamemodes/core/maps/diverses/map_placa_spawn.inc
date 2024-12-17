#include <YSI_Coding\y_hooks>

hook OnCreateObject()
{
	new mapobj_placasp[20];

	mapobj_placasp[0] = CreateObject(18762, 1663.8851, -2263.8991, 15.0620, 0.0000, 0.0000, 0.0000, 300.0); //Concrete1mx1mx5m
	SetObjectMaterial(mapobj_placasp[0], 0, 10765, "airportgnd_sfse", "white", 0xFF1E90FF);
	mapobj_placasp[1] = CreateObject(19428, 1673.1059, -2263.6679, 14.2891, 0.0000, 0.0000, -89.9999, 300.0); //wall068
	SetObjectMaterial(mapobj_placasp[1], 0, 15042, "svsfsm", "GB_rapposter01", 0x00000000);
	mapobj_placasp[2] = CreateObject(18762, 1674.6058, -2263.8991, 15.0620, 0.0000, 0.0000, 0.0000, 300.0); //Concrete1mx1mx5m
	SetObjectMaterial(mapobj_placasp[2], 0, 10765, "airportgnd_sfse", "white", 0xFF1E90FF);
	mapobj_placasp[3] = CreateObject(18766, 1669.2283, -2264.0966, 15.0284, 0.0000, 0.0000, 0.0000, 300.0); //Concrete10mx1mx5m
	SetObjectMaterial(mapobj_placasp[3], 0, 10765, "airportgnd_sfse", "white", 0xFF696969);
	mapobj_placasp[4] = CreateObject(19355, 1671.1093, -2263.6171, 15.9450, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[4], 0, "Brasil", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 95, 1, 0xFFF5F5F5, 0x00000000, 1);
	mapobj_placasp[5] = CreateObject(19355, 1669.1085, -2263.5871, 15.4151, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[5], 0, "Start", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 95, 1, 0xFFF5F5F5, 0x00000000, 1);
	mapobj_placasp[6] = CreateObject(19355, 1668.0091, -2263.5871, 13.9051, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[6], 0, "|", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 95, 1, 0xFF4682B4, 0x00000000, 1);
	mapobj_placasp[7] = CreateObject(19355, 1669.2087, -2263.5671, 16.6250, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[7], 0, "New", OBJECT_MATERIAL_SIZE_256x128, "Comic Sans MS", 95, 1, 0xFFFF8C00, 0x00000000, 1);
	mapobj_placasp[8] = CreateObject(19355, 1668.0091, -2263.5871, 16.2551, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[8], 0, "|", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 95, 1, 0xFF4682B4, 0x00000000, 1);
	mapobj_placasp[9] = CreateObject(19355, 1671.5885, -2263.5871, 14.2251, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[9], 0, "°", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 30, 1, 0xFF0000CD, 0x00000000, 1);
	mapobj_placasp[10] = CreateObject(19355, 1669.8483, -2263.5871, 14.3251, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[10], 0, "https://brasilnewstart.com.br", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 30, 1, 0xFF1E90FF, 0x00000000, 1);
	mapobj_placasp[11] = CreateObject(19355, 1671.5885, -2263.5871, 13.6750, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[11], 0, "°", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 30, 1, 0xFF0000CD, 0x00000000, 1);
	mapobj_placasp[12] = CreateObject(19355, 1669.8483, -2263.5871, 13.8251, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[12], 0, "jogar.brasilnewstart.com.br:7777", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 27, 1, 0xFF1E90FF, 0x00000000, 1);
	mapobj_placasp[13] = CreateObject(19355, 1666.4190, -2263.5871, 16.8551, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[13], 0, "Ola Player Seja bem vindo!", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 30, 1, 0xFF708090, 0x00000000, 1);
	mapobj_placasp[14] = CreateObject(19355, 1666.4190, -2263.5871, 16.2951, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[14], 0, "Use os comandos abaixo:", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 30, 1, 0xFF708090, 0x00000000, 1);
	mapobj_placasp[15] = CreateObject(19355, 1666.4190, -2263.5871, 15.4950, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[15], 0, "/ATENDIMENTO Ou /SOS", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 30, 1, 0xFF708090, 0x00000000, 1);
	mapobj_placasp[16] = CreateObject(19355, 1666.4190, -2263.5871, 15.8750, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[16], 0, "-", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 30, 1, 0xFF708090, 0x00000000, 1);
	mapobj_placasp[17] = CreateObject(19355, 1666.4190, -2263.5871, 15.0250, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[17], 0, "/AJUDA", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 30, 1, 0xFF708090, 0x00000000, 1);
	mapobj_placasp[18] = CreateObject(19355, 1666.4190, -2263.5871, 14.5750, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[18], 0, "/GPS", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 30, 1, 0xFF708090, 0x00000000, 1);
	mapobj_placasp[19] = CreateObject(19355, 1666.4190, -2263.5871, 14.1150, 0.0000, 0.0000, 90.0000, 300.0); //wall003
	SetDynamicObjectMaterialText(mapobj_placasp[19], 0, "/Admins ou /Helpers", OBJECT_MATERIAL_SIZE_256x128, "Segoe Print", 30, 1, 0xFF708090, 0x00000000, 1);

	printf("[MAPA %d]: Spawn (Placa de Ajuda) 20 OBJ loaded...", gm_count[COUNT_CREATEMAP]);
    gm_count[COUNT_CREATEMAP]++;

	return 1;
}
