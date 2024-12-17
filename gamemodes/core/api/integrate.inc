
// API editável para administrador;
// samp-server-package-manager;
// -----------------------------------------------------------------------
// Sacolas do inventário
#include <inventory\sacolas>

// -----------------------------------------------------------------------
// Comando: /ajuda

// ID do dialog
#define DIALOG_ID_HELP 28
#define DIALOG_ID_HELP_CP 27
#define DIALOG_ID_HELP_VIP 8742

// Include
#include <commands\cmd_help>

// Comandos:
CMD:ajuda(playerid) return Help_List(playerid);
alias:ajuda("help")

CMD:regras(playerid)
    return Help_List(playerid, HELP_REGRAS);

CMD:ajudageral(playerid)
    return Help_List(playerid, HELP_GERAL);

CMD:vip(playerid) return Help_List(playerid, HELP_VIP);
alias:vip("ajudavip")

CMD:ajudacozinha(playerid)
    return Help_List(playerid, HELP_COZINHA, "Ajuda cozinha");

CMD:ajudalider(playerid)
	return Help_List(playerid, HELP_LIDER, "Ajuda líder");

CMD:ajudacelular(playerid)
    return Help_List(playerid, HELP_CELULAR, "Ajuda celular");

CMD:ajudaorg(playerid)
    return Help_List(playerid, HELP_ORG, "Ajuda organização");

// Comando de ajuda emprego
CMD:ajudaemprego(playerid)
    return Help_List(playerid, HELP_EMPREGO, "Ajuda emprego");

CMD:comprarcash(playerid)
    return Help_List(playerid, HELP_COMPRAR_CASH, "Ajuda comprar cash");

CMD:ajudaradio(playerid)
    return Help_List(playerid, HELP_RADIO);

CMD:infocaixa(playerid)
    return Help_List(playerid, HELP_CAIXA);
    
CMD:infocaixa2(playerid)
    return Help_List(playerid, HELP_CAIXA2);

CMD:ajudadrogas(playerid) 
    return Help_List(playerid, HELP_DROGAS);

CMD:infosacolas(playerid)
    return Help_List(playerid, HELP_SACOLAS);

CMD:ajudaouros(playerid, params[])
	return Help_List(playerid, HELP_OUROS);

CMD:ajudahelper(playerid, params[]) {
    Help_StaffCommands(playerid);
    return 1;
}

CMD:ajudafamilia(playerid)
	return Help_List(playerid, HELP_FAMILIA);

CMD:ajudamoveis(playerid)
	return Help_List(playerid, HELP_MOVEIS);

CMD:ajudafazenda(playerid)
	return Help_List(playerid, HELP_FAZENDA, "Ajuda Fazenda");

// -----------------------------------------------------------------------
// Sistema de mensagens aleatórias

#include <others\samp-random-messages>

// -----------------------------------------------------------------------