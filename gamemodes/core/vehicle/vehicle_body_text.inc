// Sistema de textos na lateral do veículo.

enum vTextEnum 
{
	vTextObject1,
	vTextObject2,
}
new vTextInfo[MAX_VEHICLES][vTextEnum];

enum enumCText 
{
	vTextModel,
	Float:vTextCoord,
}
new ModelInfoCoords[][enumCText] = {
    // Model   		Attach Text
	{565,	        0.9590},
	{559,	        1.0918},
	{561,	        1.0918},
	{603,	        1.2232},
	{560,	        1.0542},
	{587,	        1.1669},
	{506,	        1.0667},
	{402,	        1.1769},
	{558,	        1.0730},
	{475,	        1.0730},
	{495,	        1.2044},
	{477,	        1.1857},
	{480,	        0.9979},
	{415,	        1.0554},
	{562,	        1.0354},
	{429,	        1.0367},
	{494,	        1.0354},
	{502,           1.0354},
	{503,           1.0354},
	{451,       	1.0267},
	{541,       	1.0742},
	{411,       	1.1090}
};

stock showPlayerDialogTexto(playerid) 
{
	MEGAString[0] = EOS;

	strcat(MEGAString, " Digite aqui um texto\n\n{FF5500}OBS: {AAAAAA}Você deve colocar um texto com no máximo 34 caracteres.\n");
	strcat(MEGAString, "Você também pode usar alguns códigos de cores para colorir seu texto\n\n");
	strcat(MEGAString, "{AAAAAA}Alguns códigos de cores:\n");
	strcat(MEGAString, "{FFFFFF}{ FF0000 } = {FF0000}Vermelho\n");
	strcat(MEGAString, "{FFFFFF}{ 0000FF } = {0000FF}Azul\n");
	strcat(MEGAString, "{FFFFFF}{ FF00FF } = {FF00FF}Rosa\n");
 	strcat(MEGAString, "{FFFFFF}{ FFFF00 } = {FFFF00}Amarelo\n");
    strcat(MEGAString, "{FFFFFF}{ FFFFFF } = {FFFFFF}Branco\n\n");
    strcat(MEGAString, "{FFFFFF}* OBS: Você deve utilizar o código da cor antes do Texto (SEM ESPAÇOS DENTROS DAS CHAVES)");

    inline D_VehicleText(dvtid, dvtdialogid, dvtresponse, dvtlistitem, string:dvttext[])
    {
        #pragma unused dvtid, dvtdialogid, dvtlistitem, dvttext
        if (dvtresponse)
        {
            new pvehicleid2 = GetPlayerVehicleID(playerid);

	        if (!IsVehicleSupportText(pvehicleid2))
	            return SendClientMessage(playerid, -1, "Este modelo de veículo não suporta textos laterais.");

	        if (!IsPlayerVehicleOwner(playerid, pvehicleid2))
	            return SendClientMessage(playerid, -1, "Você só poderá usar textos laterais em veículos pessoais (de concessionária).");

	        for(new len; len < strlen(dvttext); len++)
			{
	            if ((dvttext[len] >= 'a' && dvttext[len] <= 'z') || (dvttext[len] >= 'A' && dvttext[len] <= 'Z') ||
	            (dvttext[len] >= '0' && dvttext[len] <= '9') || dvttext[len] == '{' || dvttext[len] == '}' || dvttext[len] == '[' || dvttext[len] == ']' ||
				dvttext[len] == '.' || dvttext[len] == '>' || dvttext[len] == '<' || dvttext[len] == '@' ||
				dvttext[len] == '&' || dvttext[len] == '!' || dvttext[len] == '?' || dvttext[len] == ' ')
					continue;

				return SendClientMessage(playerid, -1, "O seu texto contém algum caractere inválido.");
	        }

	        if (strlen(dvttext) < 4 || strlen(dvttext))
			{
         		SendClientMessage(playerid, -1, "O texto deve conter mais de 3 caracteres!");
           		showPlayerDialogTexto(playerid);
           		return true;
	        }
	        setVehicleText(pvehicleid2, dvttext);
			SendMsgF(playerid, COLOR_LIGHTBLUE, "Você alterou o texto lateral do veículo para: %s", dvttext);

            return true;
        }
        else return SendClientMessage(playerid,-1, "Você cancelou a edição do texto lateral no veículo.");
    }
    Dialog_ShowCallback(playerid, using inline D_VehicleText, DIALOG_STYLE_INPUT, "Editar » Texto lateral (veiculo)", MEGAString, "Inserir", "Cancelar");

    return true;
}

stock GetOffsetTexto(vehicleid, &Float:coord) {

    coord = 1.1090;

    for(new model; model != sizeof ModelInfoCoords; model++) {

        if (GetVehicleModel(vehicleid) == ModelInfoCoords[model][vTextModel]) {
            coord = ModelInfoCoords[model][vTextCoord];
            break;
        }
    }
}

stock IsVehicleSupportText(vehicleid) {

    for(new model; model != sizeof ModelInfoCoords; model++) {
        if (GetVehicleModel(vehicleid) == ModelInfoCoords[model][vTextModel]) {
            return 1;
        }
    }
	return 0;
}

stock resetVehiclesText() {

	for(new vehicleid; vehicleid != MAX_VEHICLES; vehicleid++) {
		vTextInfo[vehicleid][vTextObject1] = -1;
		vTextInfo[vehicleid][vTextObject2] = -1;
	}
}

stock removeVehicleText(vehicleid) {
	if (vehicleid < 1 || vehicleid >= MAX_VEHICLES)
	    return 0;
	
	DestroyDynamicObject(vTextInfo[vehicleid][vTextObject1]);
	DestroyDynamicObject(vTextInfo[vehicleid][vTextObject2]);

	vTextInfo[vehicleid][vTextObject1] = -1;
	vTextInfo[vehicleid][vTextObject2] = -1;
	return 1;
}

stock setVehicleText(vehicleid, const text[])
{
	if (vehicleid < 1 || vehicleid >= MAX_VEHICLES)
	    return 0;
	
	if (vTextInfo[vehicleid][vTextObject1] != 0)
		DestroyDynamicObject(vTextInfo[vehicleid][vTextObject1]);
		
	if (vTextInfo[vehicleid][vTextObject2] != 0)
		DestroyDynamicObject(vTextInfo[vehicleid][vTextObject2]);

	vTextInfo[vehicleid][vTextObject1] = CreateDynamicObject(19173, -1.10794, -0.17881, -0.13230,   0.00000, 0.00000, 89.50240);
	vTextInfo[vehicleid][vTextObject2] = CreateDynamicObject(19173, 1.11731, -0.15837, -0.13230,   0.00000, 0.00000, 89.50240);

	SetDynamicObjectMaterialText(vTextInfo[vehicleid][vTextObject1], 1, " ");
	SetDynamicObjectMaterialText(vTextInfo[vehicleid][vTextObject2], 1, " ");

	SetDynamicObjectMaterialText(vTextInfo[vehicleid][vTextObject1], 0, text, OBJECT_MATERIAL_SIZE_256x128, "Arial", 37);
	SetDynamicObjectMaterialText(vTextInfo[vehicleid][vTextObject2], 0, text, OBJECT_MATERIAL_SIZE_256x128, "Arial", 37);

	new Float:offsetX, Float:offsetZ;

	GetOffsetTexto(vehicleid, offsetX);

	switch(GetVehicleModel(vehicleid)) {

	    case 415, 603: {
	        offsetZ = -0.43230;
	    }
	    default: {
	        offsetZ = -0.23230;
	    }
	}
	AttachDynamicObjectToVehicle(vTextInfo[vehicleid][vTextObject1], vehicleid, -offsetX, -0.17881, offsetZ,   0.00000, 0.00000, 89.50240);
    AttachDynamicObjectToVehicle(vTextInfo[vehicleid][vTextObject2], vehicleid, offsetX, -0.15837, offsetZ,   0.00000, 0.00000, 89.50240);

	CallRemoteFunction("Player_UpdateVehicleText", "is[]", vehicleid, text);
	return 1;
}