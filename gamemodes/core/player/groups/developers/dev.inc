#if defined _inc_developers_system
	#endinput
#endif
#define _inc_developers_system true

#include <YSI_Coding\y_hooks>

#include <dev_entry>
#include <dev_cmds>

stock Dev_ChatToAll(COLOR, const message[], DevNivel:level = DEV_BETA)
{
	foreach(new players : Player) 
    {
        if (Admin_GetNivel(players) > SUB_DONO) { SendClientMessage(players, COLOR, message); continue; }
		if (Dev_GetNivel(players) >= level) SendClientMessage(players, COLOR, message);
    }
	Discord_SendMessage(message, Channel_AdminAviso);
}

/*

DEV_BETA,
DEV_ALPHA: /lixeira
DEV_GAMA,
DEV_DELTA: /casa carregar /casa dono /casa vencimento
DEV_EPSILON,
DEV_ZETA,
DEV_ETA,
DEV_TETA,
DEV_IOTA,
DEV_KAPPA,
DEV_LAMBDA,
DEV_MI,
DEV_NI,
DEV_XI,
DEV_OMICRON,
DEV_PI,
DEV_RO,
DEV_SIGMA,
DEV_TAU,
DEV_IPSILON,
DEV_FI,
DEV_CHI,
DEV_PSI,
DEV_OMEGA








*/ 