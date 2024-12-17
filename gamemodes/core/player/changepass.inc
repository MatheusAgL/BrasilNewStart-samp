#include <YSI_Coding\y_hooks>

#define			PASSWORD_HASH 		"78sdjs86d2h"

stock ShowPlayerConfirmEmail(playerid)
{
	SendClientMessage(playerid, -1, "Sistema em reformas.");
	// ShowPlayerDialog(playerid, 12405, DIALOG_STYLE_INPUT, "Confirmação de e-mail", "{FFFFFF}Antes de solicitar a troca de senha você deve confirmar seu e-mail primeiro!\n\nDigite abaixo o {00AAFF}e-mail {FFFFFF}que você utiliza em sua conta:", "Confirmar", "Cancelar");
}