//------------------------------------------------------------------------------

#include < YSI_Coding\y_hooks >

#define MAX_CONQUISTAS 		(45)

//------------------------------------------------------------------------------

enum {
	Conquista_Registrado,
	Conquista_HeadShot,
	Conquista_Emprego,
	Conquista_Carro,
	Conquista_Casa,
	Conquista_Empresa,
	Conquista_Organizacao,
	Conquista_x1,
	Conquista_Nivel,
	Conquista_Lider,
	Conquista_SubLider,
	Conquista_Helper,
	Conquista_Admin,
	Conquista_Dev,
	Conquista_Socio,
	Conquista_SocioPremium,
	Conquista_Roubo,
	Conquista_Advogado,
	Conquista_Medico,
	Conquista_Territorio,
	Conquista_Incendio,
	Conquista_Sexo,
	Conquista_Beijo,
	Conquista_Cumprimento,
	Conquista_Musica,
	Conquista_Motorista,
	Conquista_Prisao,
	Conquista_12Estrelas,
	Conquista_EasterEgg,
	Conquista_Contrato,
	Conquista_Busao,
	Conquista_Danca,
	Conquista_Mijar,
	Conquista_Solto,
	Conquista_Explosao,
	Conquista_Loteria,
	Conquista_Deposito,
	Conquista_Drift,
	Conquista_RouboMovel,
	Conquista_Decorar,
	Conquista_Castigo,
	Conquista_Casado,
	Conquista_Alimentar,
	Conquista_Ajudante,
	Conquista_Morro,
}

//------------------------------------------------------------------------------

enum ConquistaEnum {
	ConquistaNome[75],
	ConquistaGrana,
}

//------------------------------------------------------------------------------

new PlayerText:textConquista[5][MAX_PLAYERS];
new PlayerConquistas[MAX_PLAYERS][MAX_CONQUISTAS];
new Text:viewConquistas1;
new Text:viewConquistas2;
new PlayerText:viewConquistas3[MAX_PLAYERS];
new PlayerText:viewConquistas[MAX_PLAYERS][MAX_CONQUISTAS];

//------------------------------------------------------------------------------

new ConquistaInfo[MAX_CONQUISTAS][ConquistaEnum] = {
	{"Registrado no servidor", 		7000},
	{"HeadShot", 					15000},
	{"O primeiro emprego", 			7000},
	{"O primeiro carro", 			7000},
	{"A primeira casa", 			7000},
	{"A primeira empresa", 			7000},
	{"A primeira Organizacao", 		7000},
	{"O primeiro x1 ganho", 		7000},
	{"Passar de Nivel", 			7000},
	{"Ser Lider", 					300000},
	{"Ser Sub-Lider", 				100000},
	{"Ser Helper", 					500000},
	{"Ser Admin", 					2000000},
	{"Fazer parte da Equipe Dev.",	5000000},
	{"Ser Socio", 					7000},
	{"Ser Socio Ouro ou maior", 	7000},
	{"O primeiro Roubo", 			7000},
	{"O primeiro preso ajustado", 	7000},
	{"O primeiro paciente curado", 	7000},
	{"O primeiro territorio", 		7000},
	{"O primeiro incendio apagado", 7000},
	{"O primeiro Sexo", 			7000},
	{"O primeiro Beijo", 			7000},
	{"O primeiro cumprimento", 		7000},
	{"A primeira musica", 			7000},
	{"Carteira de Motorista", 		7000},
	{"A primeira prisao", 			7000},
	{"8 estrelas", 					7000},
	{"Misterio resolvido", 			7000},
	{"O primeiro contrato", 		7000},
	{"Pegar o busao", 				7000},
	{"A primeira danca", 			7000},
	{"Pra que banheiro? - Mijar", 	7000},
	{"Sair da prisao", 				7000},
	{"A primeira explosao", 		7000},
	{"Ganhou na loteria", 			7000},
	{"Depositou na conta", 			7000},
	{"Vencer o evento de drift", 	30000},
	{"Ladrao de casas", 			7000},
	{"Decorando a casa", 			7000},
	{"O primeiro castigo", 			7000},
	{"Ser casado", 					7000},
	{"Se alimentar", 				7000},
	{"Avaliado positivamente", 		7000},
	{"Dono do morro", 	        	7000}
};

// -------------------------------------------------
hook OnPlayerRegister(playerid) {
	CheckConquista(playerid, Conquista_Registrado);
}

hook OnPlayerConnect(playerid)
{
	createTextdrawsConquistas(playerid);
	createViewConquistas(playerid);
}

hook OnClickDynPlayerTextDraw(playerid, PlayerText:textid)
{
	new string[128];
	new vendoconquista = GetPVarInt(playerid, "varVendoConquista");
	for(new conquista; conquista != MAX_CONQUISTAS; conquista++) {

		if (textid == viewConquistas[playerid][conquista]) {

	        if(PlayerConquistas[vendoconquista][conquista]) {

		        format(string, sizeof string,
				"{FFFFFF}Conquista » {00FFFF}%s\n\
				{FFFFFF}Dinheiro ganho » {00FFFF}$%d", ConquistaInfo[conquista][ConquistaNome], ConquistaInfo[conquista][ConquistaGrana]);
	            ShowPlayerDialog(playerid, 8724, DIALOG_STYLE_MSGBOX, "» Conquista", string, "Fechar","");
			}
		}
	}
	return 1;
}

//------------------------------------------------------------------------------
CALLBACK: CheckConquista(playerid, conquistaid) {
	return 1;
}
//------------------------------------------------------------------------------

CALLBACK: MostrarConquistas(playerid, forplayerid) {

	SetPVarInt(forplayerid, "varVendoConquista", playerid);
	SetPVarInt(forplayerid, "VendoConquista", 1);
	
	new string[65];
	format(string, sizeof string, "Conquistas de %s", PlayerName[playerid]);
	PlayerTextDrawSetString(forplayerid, viewConquistas3[forplayerid], string);
	
	TextDrawShowForPlayer(forplayerid, viewConquistas1);
	TextDrawShowForPlayer(forplayerid, viewConquistas2);
	PlayerTextDrawShow(forplayerid, viewConquistas3[forplayerid]);

	for(new conquista; conquista != MAX_CONQUISTAS; conquista++) {

	    if (PlayerConquistas[playerid][conquista]) {

	        PlayerTextDrawColor(forplayerid, viewConquistas[forplayerid][conquista], 0xFFFFFFFF);
			PlayerTextDrawSetSelectable(forplayerid, viewConquistas[forplayerid][conquista], true);
		} else {
	        PlayerTextDrawColor(forplayerid, viewConquistas[forplayerid][conquista], 0xFFFFFF15);
            PlayerTextDrawSetSelectable(forplayerid, viewConquistas[forplayerid][conquista], false);
		}
	    PlayerTextDrawShow(forplayerid, viewConquistas[forplayerid][conquista]);
	}
	SelectTextDraw(forplayerid, 0x00FF00FF);
}

//------------------------------------------------------------------------------

hook OnClickDynamicTextDraw(playerid, Text:textid)
{
    if (textid == Text:INVALID_TEXT_DRAW && GetPVarInt(playerid, "VendoConquista")) {
        HideViewConquistas(playerid);
    }
	return 1;
}

//------------------------------------------------------------------------------

CALLBACK: HideViewConquistas(playerid)
{
	TextDrawHideForPlayer(playerid, viewConquistas1);
	TextDrawHideForPlayer(playerid, viewConquistas2);
	PlayerTextDrawHide(playerid, viewConquistas3[playerid]);

	for(new conquista; conquista != MAX_CONQUISTAS; conquista++) {
	    PlayerTextDrawHide(playerid, viewConquistas[playerid][conquista]);
	}

	SetPVarInt(playerid, "VendoConquista", 0);
	CancelSelectTextDraw(playerid);
}

//------------------------------------------------------------------------------

createBaseConquistas() {
	viewConquistas1 = TextDrawCreate(521.000000, 120.000000, "usebox");
	TextDrawBackgroundColor(viewConquistas1, 0);
	TextDrawFont(viewConquistas1, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(viewConquistas1, 0.500000, 25.500001);
	TextDrawColor(viewConquistas1, 0);
	TextDrawSetOutline(viewConquistas1, 0);
	TextDrawSetProportional(viewConquistas1, true);
	TextDrawSetShadow(viewConquistas1, 1);
	TextDrawUseBox(viewConquistas1, true);
	TextDrawBoxColor(viewConquistas1, 16711730);
	TextDrawTextSize(viewConquistas1, 98.000000, 0.000000);
	TextDrawSetSelectable(viewConquistas1, false);

	viewConquistas2 = TextDrawCreate(516.000000, 143.000000, "usebox");
	TextDrawBackgroundColor(viewConquistas2, 0);
	TextDrawFont(viewConquistas2, TEXT_DRAW_FONT_1);
	TextDrawLetterSize(viewConquistas2, 0.500000, 22.500005);
	TextDrawColor(viewConquistas2, 0);
	TextDrawSetOutline(viewConquistas2, 0);
	TextDrawSetProportional(viewConquistas2, true);
	TextDrawSetShadow(viewConquistas2, 1);
	TextDrawUseBox(viewConquistas2, true);
	TextDrawBoxColor(viewConquistas2, 336860415);
	TextDrawTextSize(viewConquistas2, 103.000000, 0.000000);
	TextDrawSetSelectable(viewConquistas2, false);
}

//------------------------------------------------------------------------------

stock createTextdrawsConquistas(playerid) {
	textConquista[0][playerid] = CreatePlayerTextDraw(playerid,7.000000, 132.000000, "_");
	PlayerTextDrawBackgroundColor(playerid,textConquista[0][playerid], 255);
	PlayerTextDrawFont(playerid,textConquista[0][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textConquista[0][playerid], 0.500000, 4.600000);
	PlayerTextDrawColor(playerid,textConquista[0][playerid], -1);
	PlayerTextDrawSetOutline(playerid,textConquista[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textConquista[0][playerid], true);
	PlayerTextDrawSetShadow(playerid,textConquista[0][playerid], 1);
	PlayerTextDrawUseBox(playerid,textConquista[0][playerid], true);
	PlayerTextDrawBoxColor(playerid,textConquista[0][playerid], 16711750);
	PlayerTextDrawTextSize(playerid,textConquista[0][playerid], 229.000000, 0.000000);
	PlayerTextDrawSetSelectable(playerid,textConquista[0][playerid], false);

	textConquista[1][playerid] = CreatePlayerTextDraw(playerid,8.000000, 133.000000, "_");
	PlayerTextDrawBackgroundColor(playerid,textConquista[1][playerid], 255);
	PlayerTextDrawFont(playerid,textConquista[1][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textConquista[1][playerid], 0.500000, 4.400000);
	PlayerTextDrawColor(playerid,textConquista[1][playerid], -1);
	PlayerTextDrawSetOutline(playerid,textConquista[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textConquista[1][playerid], true);
	PlayerTextDrawSetShadow(playerid,textConquista[1][playerid], 1);
	PlayerTextDrawUseBox(playerid,textConquista[1][playerid], true);
	PlayerTextDrawBoxColor(playerid,textConquista[1][playerid], 673720575);
	PlayerTextDrawTextSize(playerid,textConquista[1][playerid], 228.000000, 0.000000);
	PlayerTextDrawSetSelectable(playerid,textConquista[1][playerid], false);

	textConquista[2][playerid] = CreatePlayerTextDraw(playerid,7.000000, 132.000000, "ld_chat:thumbup");
	PlayerTextDrawBackgroundColor(playerid,textConquista[2][playerid], 255);
	PlayerTextDrawFont(playerid,textConquista[2][playerid], TEXT_DRAW_FONT_SPRITE_DRAW);
	PlayerTextDrawLetterSize(playerid,textConquista[2][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,textConquista[2][playerid], 16711935);
	PlayerTextDrawSetOutline(playerid,textConquista[2][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textConquista[2][playerid], true);
	PlayerTextDrawSetShadow(playerid,textConquista[2][playerid], 1);
	PlayerTextDrawUseBox(playerid,textConquista[2][playerid], true);
	PlayerTextDrawBoxColor(playerid,textConquista[2][playerid], 255);
	PlayerTextDrawTextSize(playerid,textConquista[2][playerid], 42.000000, 40.000000);
	PlayerTextDrawSetSelectable(playerid,textConquista[2][playerid], false);

	textConquista[3][playerid] = CreatePlayerTextDraw(playerid,53.000000, 131.000000, "Conquista desbloqueada");
	PlayerTextDrawBackgroundColor(playerid,textConquista[3][playerid], 0);
	PlayerTextDrawFont(playerid,textConquista[3][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textConquista[3][playerid], 0.389999, 1.600000);
	PlayerTextDrawColor(playerid,textConquista[3][playerid], -1);
	PlayerTextDrawSetOutline(playerid,textConquista[3][playerid], 1);
	PlayerTextDrawSetProportional(playerid,textConquista[3][playerid], true);
	PlayerTextDrawSetSelectable(playerid,textConquista[3][playerid], false);

	textConquista[4][playerid] = CreatePlayerTextDraw(playerid,54.000000, 153.000000, "$---- - ---------- - --------");
	PlayerTextDrawBackgroundColor(playerid,textConquista[4][playerid], 0);
	PlayerTextDrawFont(playerid,textConquista[4][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textConquista[4][playerid], 0.230000, 1.000000);
	PlayerTextDrawColor(playerid,textConquista[4][playerid], -1);
	PlayerTextDrawSetOutline(playerid,textConquista[4][playerid], 1);
	PlayerTextDrawSetProportional(playerid,textConquista[4][playerid], true);
	PlayerTextDrawUseBox(playerid,textConquista[4][playerid], true);
	PlayerTextDrawBoxColor(playerid,textConquista[4][playerid], 0);
	PlayerTextDrawTextSize(playerid,textConquista[4][playerid], 624.000000, 0.000000);
	PlayerTextDrawSetSelectable(playerid,textConquista[4][playerid], false);
	
	//createViewConquistas(playerid);
}

//------------------------------------------------------------------------------

stock createViewConquistas(playerid) {

	viewConquistas3[playerid] = CreatePlayerTextDraw(playerid, 107.000000, 120.000000, "Conquistas de -----");
	PlayerTextDrawBackgroundColor(playerid, viewConquistas3[playerid], 0);
	PlayerTextDrawFont(playerid, viewConquistas3[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, viewConquistas3[playerid], 0.439999, 1.699999);
	PlayerTextDrawColor(playerid, viewConquistas3[playerid], -1);
	PlayerTextDrawSetOutline(playerid, viewConquistas3[playerid], 0);
	PlayerTextDrawSetProportional(playerid, viewConquistas3[playerid], true);
	PlayerTextDrawSetShadow(playerid, viewConquistas3[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, viewConquistas3[playerid], false);

	new Float: baseX = 111.000000;
	new Float: baseY = 146.000000;
	new baseT = 0;

	for(new base; base != MAX_CONQUISTAS; base++) {
		viewConquistas[playerid][base] = CreatePlayerTextDraw(playerid, baseX, baseY, "ld_drv:goboat");
		PlayerTextDrawBackgroundColor(playerid, viewConquistas[playerid][base], 255);
		PlayerTextDrawFont(playerid, viewConquistas[playerid][base], TEXT_DRAW_FONT_SPRITE_DRAW);
		PlayerTextDrawLetterSize(playerid, viewConquistas[playerid][base], 0.500000, 1.000000);
		PlayerTextDrawColor(playerid, viewConquistas[playerid][base], -1);
		PlayerTextDrawSetOutline(playerid, viewConquistas[playerid][base], 0);
		PlayerTextDrawSetProportional(playerid, viewConquistas[playerid][base], true);
		PlayerTextDrawSetShadow(playerid, viewConquistas[playerid][base], 1);
		PlayerTextDrawUseBox(playerid, viewConquistas[playerid][base], true);
		PlayerTextDrawBoxColor(playerid, viewConquistas[playerid][base], 255);
		PlayerTextDrawTextSize(playerid, viewConquistas[playerid][base], 37.000000, 34.000000);
		PlayerTextDrawSetSelectable(playerid, viewConquistas[playerid][base], true);

		baseT ++;
		baseX += 40.00000;

		if (baseT >= 10) {
		    baseT = 0;

		    baseX = 111.000000;
		    baseY += 40.00000;
		}
	}
}

//------------------------------------------------------------------------------

CALLBACK: ResetConquistas(playerid) {
	for(new conquista; conquista != MAX_CONQUISTAS; conquista++) {
	    PlayerConquistas[playerid][conquista] = 0;
	}
}

//------------------------------------------------------------------------------

CALLBACK: ShowConquistas(playerid) {

	for (new Textdraw; Textdraw != 5; Textdraw++) {
		PlayerTextDrawShow(playerid, textConquista[Textdraw][playerid]);
	}
}

//------------------------------------------------------------------------------

forward HideConquistas(playerid);
public HideConquistas(playerid) {

	for (new Textdraw; Textdraw != 5; Textdraw++) {
		PlayerTextDrawHide(playerid, textConquista[Textdraw][playerid]);
	}
}

CMD:conquistas(playerid)
{
	if (Player_Logado(playerid))
	{
		MostrarConquistas(playerid, playerid);
	}
	else
	{
		SendClientMessage(playerid, -1, "Você não está logado para usar esse comando.");
	}
	return true;
}

/*CMD:mostrarconquistas(playerid, params[])
{
    if(gettime() < GetPVarInt(playerid, #varFlood_mconquistas)) return SendClientMessage(playerid, -1, #Você não pode usar este comando com tanta frequencia);

	new idplayer;
	if (sscanf(params, "u", idplayer)) return SendClientMessage(playerid, -1, "Modo de uso: /mostrarconquistas (id do jogador)");

	if (!IsPlayerConnected(idplayer) && !Player_Logado(idplayer)) 
		return SendClientMessage(playerid, -1, "O jogador não está conectado ou logado no servidor.");

	if (Staff_GetWorking(idplayer)) 
		return SendClientMessage(playerid, -1, "Você não pode mostrar conquistas para admins em modo trabalho.");

	if (!ProxDetectorS(5.0, playerid, idplayer)) return SendClientMessage(playerid, -1, "Este jogador está muito longe.");

	new
		string[90]
	;

	MostrarConquistas(playerid, idplayer);
	format(string, sizeof(string), "* %s mostrou suas conquistas para %s.",PlayerName[playerid],PlayerName[idplayer]);
	SendClientMessageInRange(15.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

	return SetPVarInt(playerid, #varFlood_mconquistas, gettime() + 10);
}*/

//------------------------------------------------------------------------------





