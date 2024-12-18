
#include <YSI_Coding\y_hooks>

new DominandoMercadoNegro = 0, DominandoFabricaMateriais = 0;

CMD:dominar(playerid)
{
    new string[226];

	if (IsPlayerInRangeOfPoint(playerid, 45.0, 942.3033,2163.3245,1012.2277))
	{
		if (!PlayerIsMafia(playerid) && GetPlayerOrg(playerid) != 11 && GetPlayerOrg(playerid) != 34)
			return SendClientMessage(playerid, -1, "Apenas os mafiosos ou a policia federal podem dominar esse local.");

		if (OwnerMercadoNegro == GetPlayerOrg(playerid)) return SendClientMessage(playerid, -1, "A sua organiza��o j� est� no controle do local.");

		if (DominandoMercadoNegro) return SendClientMessage(playerid, -1, "O mercado negro j� est� sendo dominado.");

	    if (OwnerMercadoNegro != 0) format(string, sizeof string, "[Mercado Negro]: {FFFFFF}A organiza��o {%06x}%s{FFFFFF} est� dominando o mercado negro dos {%s}%s", (GetPlayerColor(playerid) >>> 8), GetOrgName(GetPlayerOrg(playerid)), GetOrgColor(OwnerMercadoNegro), GetOrgName(OwnerMercadoNegro));
		else format(string, sizeof string, "[Mercado Negro]: {FFFFFF}A organiza��o {%06x}%s{FFFFFF} est� tentando dominar o mercado negro", (GetPlayerColor(playerid) >>> 8), GetOrgName(GetPlayerOrg(playerid)));
		SendClientMessageToAll(0x00AAFFFF, string);

		SendClientMessage(playerid, -1, "Voc� est� tentando dominar o mercado negro, aguarde {00AA00}1 minuto e meio {FFFFFF}no local para terminar!");

		DominandoMercadoNegro = 1;
		SetPVarInt(playerid, "DominandoMN", 1);
		SetPVarInt(playerid, "TimerDominandoMN", SetTimerEx("dominarMercado", 60000+30000, false, "ii", playerid, GetPlayerOrg(playerid)));
	}
	else if (IsPlayerInRangeOfPoint(playerid, 20.0, -961.3480, 1907.2937, 9.9657))
	{
		if (!PlayerIsMafia(playerid) && GetPlayerOrg(playerid) != 11 && GetPlayerOrg(playerid) != 34)
			return SendClientMessage(playerid, -1, "Apenas os mafiosos ou a policia federal podem dominar esse local.");

		if (OwnerFabricaMateriais == GetPlayerOrg(playerid)) return SendClientMessage(playerid, -1, "A sua organiza��o j� est� no controle da f�brica.");

		if (DominandoFabricaMateriais) return SendClientMessage(playerid, -1, "A f�brica de materiais j� est� sendo dominada.");

	    if (OwnerFabricaMateriais != 0) format(string, sizeof string, "[F�brica de Materiais]: {FFFFFF}A organiza��o {%06x}%s{FFFFFF} est� dominando a f�brica de materiais dos {%s}%s", (GetPlayerColor(playerid) >>> 8), GetOrgName(GetPlayerOrg(playerid)), GetOrgColor(OwnerFabricaMateriais), GetOrgName(OwnerFabricaMateriais));
		else format(string, sizeof string, "[F�brica de Materiais]: {FFFFFF}A organiza��o {%06x}%s{FFFFFF} est� tentando dominar a f�brica de materiais", (GetPlayerColor(playerid) >>> 8), GetOrgName(GetPlayerOrg(playerid)));
		SendClientMessageToAll(0x00AAFFFF, string);

		SendClientMessage(playerid, -1, "Voc� est� tentando dominar a f�brica de materiais, aguarde {00AA00}1 minuto e meio {FFFFFF}no local para terminar!");

		DominandoFabricaMateriais = 1;
		SetPVarInt(playerid, "DominandoFM", 1);
		SetPVarInt(playerid, "TimerDominandoFM", SetTimerEx("dominarFabricaM", 60000+30000, false, "ii", playerid, GetPlayerOrg(playerid)));
	}
	else SendClientMessage(playerid, -1, "Voc� n�o est� em nenhum lugar de domina��o mafiosa.");

	return true;
}

CALLBACK: dominarMercado(playerid, orgid)
{
	DominandoMercadoNegro = 0;
	SetPVarInt(playerid, "DominandoMN", 0);
	SetPVarInt(playerid, "TimerDominandoMN", -1);

 	if (GetPlayerOrg(playerid) == OwnerMercadoNegro) return false;

	if (GetPlayerOrg(playerid) != orgid) return SendClientMessage(playerid, -1, "Voc� n�o pertence mais a organiza��o que estava dominando.");

	if (!IsPlayerInRangeOfPoint(playerid, 45.0, 942.3033,2163.3245,1012.2277)) return SendClientMessage(playerid, -1, "Voc� n�o est� no mercado negro.");

    new string[169];

	if ( OwnerMercadoNegro != 0) format(string, sizeof string, "[Mercado Negro]: {FFFFFF}A organiza��o {%06x}%s{FFFFFF} conseguiu tomar o mercado negro dos {FF4400}%s", (GetPlayerColor(playerid) >>> 8), GetOrgName(orgid), GetOrgName(OwnerMercadoNegro));
	else format(string, sizeof string, "[Mercado Negro]: {FFFFFF}A organiza��o {%06x}%s{FFFFFF} agora tem o controle do o mercado negro", (GetPlayerColor(playerid) >>> 8), GetOrgName(orgid));
    SendClientMessageToAll(0x00AAFFFF, string);

	SendClientMessage(playerid, -1, "Voc�s tomaram o controle do mercado negro, mantenha o local seguro de ataques rivais!");

    OwnerMercadoNegro = orgid;

    format(string, sizeof string, "Use o comando {00FFFF}/dominar{FFFFFF} para dominar este local\nOrganiza��o no controle: {%06x}%s", (GetPlayerColor(playerid) >>> 8), GetOrgName(orgid));
	UpdateDynamic3DTextLabelText(OwnerMercadoNegroText, -1, string);

   	return true;
}

CALLBACK: dominarFabricaM(playerid, orgid)
{
	SetPVarInt(playerid, "DominandoFM", 0);
	SetPVarInt(playerid, "TimerDominandoFM", -1);

 	if (GetPlayerOrg(playerid) == OwnerFabricaMateriais) return false;

	if (GetPlayerOrg(playerid) != orgid) return SendClientMessage(playerid, -1, "Voc� n�o pertence mais a organiza��o que estava dominando.");

	if (!IsPlayerInRangeOfPoint(playerid, 45.0, -961.3480, 1907.2937, 9.9657)) return SendClientMessage(playerid, -1, "Voc� n�o est� na f�brica de materiais.");

    new string[169];

	if (OwnerMercadoNegro != 0) format(string, sizeof string, "[F�brica de Materiais]: {FFFFFF}A organiza��o {%06x}%s{FFFFFF} conseguiu tomar a f�brica dos {FF4400}%s", (GetPlayerColor(playerid) >>> 8), GetOrgName(orgid), GetOrgName(OwnerFabricaMateriais));
	else format(string, sizeof string, "[F�brica de Materiais]: {FFFFFF}A organiza��o {%06x}%s{FFFFFF} agora tem o controle da f�brica de materiais.", (GetPlayerColor(playerid) >>> 8), GetOrgName(orgid));
    SendClientMessageToAll(0x00AAFFFF, string);

    OwnerFabricaMateriais = orgid;
	DominandoFabricaMateriais = 0;

	if (OwnerFabricaMateriais == 11 && OwnerFabricaMateriais == 34)
	{
	    format(string, sizeof string, "F�brica de Materiais\n\n{FFFFFF}Use: {E3DA7B}/dominar{FFFFFF} para tomar o local\nDominado por: {%06x}%s\n{FFFFFF}Propina de materiais: {E3AC5E}Apreendido", (GetPlayerColor(playerid) >>> 8), GetOrgName(orgid));
		UpdateDynamic3DTextLabelText(OwnerFabricaMateriaisText, 0x89DFE5F9, string);

		SendMembersMessage(orgid, GetPlayerColor(playerid), "Sua organiza��o tomou o controle da f�brica de materiais e acabou com a propina de materiais.");
	}
	else
	{
	    format(string, sizeof string, "F�brica de Materiais\n\n{FFFFFF}Use: {E3DA7B}/dominar{FFFFFF} para tomar o local\nDominado por: {%06x}%s\n{FFFFFF}Propina de materiais: {E3AC5E}%sg", (GetPlayerColor(playerid) >>> 8), GetOrgName(orgid), getFormatText(propinaMateriais));
		UpdateDynamic3DTextLabelText(OwnerFabricaMateriaisText, 0x89DFE5F9, string);

		SendMembersMessage(orgid, GetPlayerColor(playerid), "Sua organiza��o tomou o controle da f�brica de materiais, fique atento nas propinas de materiais.");
	}

   	return true;
}