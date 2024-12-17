#include <YSI_Coding\y_hooks>


hook CreateDynamicTextDraws(playerid) {
    new Float:abordagemAltura = IsAndroidPlayer(playerid) ? 75.00 : 0.00;
    
	// Textdraws abordagem
	textAbordagem[0][playerid] = CreatePlayerTextDraw(playerid,10.000000, 160.000000 + abordagemAltura, "usebox");
	PlayerTextDrawBackgroundColor(playerid,textAbordagem[0][playerid], 0);
	PlayerTextDrawFont(playerid,textAbordagem[0][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textAbordagem[0][playerid], 0.500000, 6.799999);
	PlayerTextDrawColor(playerid,textAbordagem[0][playerid], 0);
	PlayerTextDrawSetOutline(playerid,textAbordagem[0][playerid], 1);
	PlayerTextDrawSetProportional(playerid,textAbordagem[0][playerid], true);
	PlayerTextDrawUseBox(playerid,textAbordagem[0][playerid], true);
	PlayerTextDrawBoxColor(playerid,textAbordagem[0][playerid], 180);
	PlayerTextDrawTextSize(playerid,textAbordagem[0][playerid], 250.000000, 0.000000);
	PlayerTextDrawSetSelectable(playerid,textAbordagem[0][playerid], false);

	textAbordagem[1][playerid] = CreatePlayerTextDraw(playerid,10.000000, 160.000000 + abordagemAltura, "~y~ABORDAGEM POLICIAL");
	PlayerTextDrawBackgroundColor(playerid,textAbordagem[1][playerid], 0);
	PlayerTextDrawFont(playerid,textAbordagem[1][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textAbordagem[1][playerid], 0.270000, 0.899999);
	PlayerTextDrawColor(playerid,textAbordagem[1][playerid], -106);
	PlayerTextDrawSetOutline(playerid,textAbordagem[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textAbordagem[1][playerid], true);
	PlayerTextDrawSetShadow(playerid,textAbordagem[1][playerid], 1);
	PlayerTextDrawUseBox(playerid,textAbordagem[1][playerid], true);
	PlayerTextDrawBoxColor(playerid,textAbordagem[1][playerid], 255);
	PlayerTextDrawTextSize(playerid,textAbordagem[1][playerid], 250.000000, 3.000000);
	PlayerTextDrawSetSelectable(playerid,textAbordagem[1][playerid], false);

	textAbordagem[2][playerid] = CreatePlayerTextDraw(playerid,9.000000, 171.000000 + abordagemAltura, "Voce esta sendo abordado pelos policiais, voce tem 5 segundos para escolher uma opcao");
	PlayerTextDrawBackgroundColor(playerid,textAbordagem[2][playerid], 0);
	PlayerTextDrawFont(playerid,textAbordagem[2][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textAbordagem[2][playerid], 0.229999, 1.000000);
	PlayerTextDrawColor(playerid,textAbordagem[2][playerid], -56);
	PlayerTextDrawSetOutline(playerid,textAbordagem[2][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textAbordagem[2][playerid], true);
	PlayerTextDrawSetShadow(playerid,textAbordagem[2][playerid], 1);
	PlayerTextDrawUseBox(playerid,textAbordagem[2][playerid], true);
	PlayerTextDrawBoxColor(playerid,textAbordagem[2][playerid], 0);
	PlayerTextDrawTextSize(playerid,textAbordagem[2][playerid], 251.000000, 0.000000);
	PlayerTextDrawSetSelectable(playerid,textAbordagem[2][playerid], false);

	textAbordagem[3][playerid] = CreatePlayerTextDraw(playerid,9.000000, 195.000000 + abordagemAltura, "OPCOES:~n~~g~Y ~w~= Aceitar a abordagem~n~~r~N = ~w~Recusar a abordagem");
	PlayerTextDrawBackgroundColor(playerid,textAbordagem[3][playerid], 0);
	PlayerTextDrawFont(playerid,textAbordagem[3][playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid,textAbordagem[3][playerid], 0.270000, 0.999998);
	PlayerTextDrawColor(playerid,textAbordagem[3][playerid], -1768515841);
	PlayerTextDrawSetOutline(playerid,textAbordagem[3][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textAbordagem[3][playerid], true);
	PlayerTextDrawSetShadow(playerid,textAbordagem[3][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textAbordagem[3][playerid], false);
}