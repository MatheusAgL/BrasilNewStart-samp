
// -----------------------------------------------------------
// Propriedade:

enum LoteType: {
	HOUSE,
	BUSSINES,
	FARM,
};

#include <lote>
// Lotérica:
#include <lotto>

stock ShowEmpresaList(playerid, emptipo) {

    // new count;

    // MEGAString [0] = EOS;

    if (emptipo == 1) {
        listPropriedades( playerid ) ;
		SetPVarInt(playerid, "varTipoGps", emptipo);
	}
    // else if (emptipo == 3) {

	//     strcat(MEGAString, "Fazenda ID\tDono\tProdutos req. (Preço prod.)\tStatus\n");

	//     // foreach(new e : Fazendas)
	// 	// {
	// 	// 	if(Fazenda_IsOwned(e))
	// 	//     	format(string_emp, sizeof (string_emp), "{FFFFFF}Fazenda %02d\t%s\t%d ($%d)\t%s\n", e, FBizzInfo[e][fbOwner], FBizzInfo[e][fbProductsReq], FBizzInfo[e][fbPriceProd], !FBizzInfo[e][fbLocked] ? ("{00AA00}ABERTA") : ("{FF0000}FECHADA"));
	// 	// 	else 
	// 	// 		format(string_emp, sizeof (string_emp), "{FFFFFF}Fazenda %02d\tNinguém\t%d ($%d)\t%s\n", e, FBizzInfo[e][fbProductsReq], FBizzInfo[e][fbPriceProd], !FBizzInfo[e][fbLocked] ? ("{00AA00}ABERTA") : ("{FF0000}FECHADA"));
			
	// 	// 	strcat(MEGAString, string_emp);
    //     //     SelectFazendas[playerid][count] = e;
    //     //     count++;
	// 	// }
	// 	ShowPlayerDialog(playerid, 7254, DIALOG_STYLE_TABLIST_HEADERS, "Localizar Fazenda/Empresa", MEGAString, "Selecionar", "Voltar");
	// }
}

stock Checkproop()
{
 	new string[144];

	for(new fid = 0; fid < sizeof(familyInfo); fid++)
	{
		if ( Iter_Contains(IterFamily, fid) ) {

			if (familyInfo[fid][familyVencimento] < Now() - Days:5) {

			    Family_Destroy(fid);
			    format(string, sizeof(string), "[FAMÍLIAS]: A familia ID: %d venceu e foi destruida.", fid);
			    SendClientMessageToAll(TEAM_BALLAS_COLOR, string);
				server_log("family", string);
			}
			else if (familyInfo[fid][familyVencimento] < Now()) {

			    Family_Destroy(fid);
			    format(string, sizeof(string), "Sua família venceu, renove em 5 dias ou ela irá ser excluida automaticamente!");
			    sendFamilyMsg( fid , 0xFFAAAAFF, string);
				server_log("family", string);
			}
		}
	}
	new liberou;
	for (new prop; prop != unid; prop++)
	{
		if (IsPropertyOwner( prop ) && Now() > PropInfo[prop][eVencimento])
		{
			// Logs
			format(string, sizeof(string), "Propriedade %d foi liberada por inatividade (dono: %s [%d])", prop, PropInfo[prop][eOwner], PropInfo[prop][eOwnerID]);
			server_log("propriedades", string);

		    SetPropertyOwner(prop, -1);
		    savePropertie( prop );
		    liberou ++;
		    atualizarPropText( prop );
		}
	}

	// new casa_liberou = 0;
	// for (new casa; casa != MAX_HOUSES; casa++)
	// {
	// 	if (HouseInfo[casa][hCriada] && House_HaveOwner(casa) && Now() > HouseInfo[casa][hVencimento])
	// 	{
	// 	    // Logs
	// 		format(string, sizeof(string), "Casa %d foi liberada por inatividade (dono: %s [%d])", casa, HouseInfo[casa][hDono], HouseInfo[casa][hDonoID]);
	// 		server_log("casas", string);

	// 		SetHouseOwner(casa, -1);
	// 	    casa_liberou ++;
	// 	    updateHouseStats(casa);
	// 	}
	// }

	if ( liberou ) {
		format(string, sizeof(string), "PROPRIEDADES: Foram liberadas %d propriedades por não terem pago as faturas!", liberou);
		SendClientMessageToAll(TEAM_BALLAS_COLOR, string);
	}
	
	// if ( casa_liberou ) {
	// 	format(string, sizeof(string), "CASAS: Foram liberadas %d casas por não terem pago as faturas!", casa_liberou);
	// 	SendClientMessageToAll(COLOR_ORANGE, string);
	// }

	return true;
}

// Mercado:
//#include <market>

stock fazendaSellState(idx, hmode = 1)
{
	new string[128];

	if (hmode == 1)
	{
		format(string, sizeof(string), "Fazenda %d foi liberada por inatividade (dono: %s)", idx, FBizzInfo[idx][fbOwner]);
		server_log("fempresas", string);

		format(string, sizeof(string), "FAZENDAS: Uma fazenda está a venda por $%d de %s", FBizzInfo[idx][fbBuyPrice], 
			FBizzInfo[idx][fbPriceMode] == 0 ? ("cash") : ("ouros"));
	}
	
	SendClientMessageToAll(TEAM_BALLAS_COLOR, string);

	FBizzInfo[idx][fbLocked] = 0;
	FBizzInfo[idx][fbOwnerID] = -1;
	strmid(FBizzInfo[idx][fbOwner], "Ninguém", 0, strlen("Ninguém"), 255);

	Fazenda_Salvar(idx);
	Fazenda_UpdateLabel(idx);
}
