new MercOffer[MAX_PLAYERS];
new MercMoney[MAX_PLAYERS];

#include <according_cmds>

stock According_Cancel(playerid)
{
    MercOffer[playerid] = 999;
    MercMoney[playerid] = 0;

    new string[128];

    foreach(new i : Player)
    {
        if(GetPVarInt(playerid, "acordoID") == i)
        {
            format(string, sizeof string, "O Mercen�rio %s n�o est� mais ajudando voc�!", PlayerName[playerid]);
            SendClientMessage(i, COLOR_LIGHTRED, string);
            format(string, sizeof string, "Voc� parou de ajudar %s.", PlayerName[i]);
            SendClientMessage(playerid, COLOR_LIGHTRED, string);
            break;
        }
        if(GetPVarInt(i, "acordoID") == playerid)
        {
            format(string, sizeof string, "*%s n�o quer mais a sua ajuda!!", PlayerName[playerid]);
            SendClientMessage(i, COLOR_LIGHTRED, string);
            format(string, sizeof string, "Voc� n�o quer mais a ajuda de %s", PlayerName[i]);
            SendClientMessage(playerid, COLOR_LIGHTRED, string);
            SetPVarInt(i, "acordoID", 999);
            SetPVarInt(i, "MercORG", 999);
            break;
        }
    }
    SetPVarInt(playerid, "acordoID", 999);
    SetPVarInt(playerid, "MercORG", 999);
}

stock According_Accept(playerid)
{
    if(MercOffer[playerid] < 999)
    {
        if(IsPlayerConnected(MercOffer[playerid]))
        {
            if (ProxDetectorS(5.0, playerid, MercOffer[playerid]))
            {
                if(!GetPlayerOrg(playerid))
                    return SendClientMessage(playerid, -1, "Voc� n�o pode ser ajudado!");

                if(Player_GetMoney(playerid) < MercMoney[playerid])
                    return SendClientMessage(playerid, -1, "Voc� n�o possui essa grana !");

                if(GetPVarInt(MercOffer[playerid], "acordoID") != 999)
                    return SendClientMessage(playerid, -1, "Este mercen�rio ja est� ajudando algu�m!");

                new string[128];
                foreach(new i : Player) {
                    if(GetPVarInt(i, "acordoID") == playerid){
                        format(string, sizeof string, "Voc� ja est� sendo ajudado por %s, digite (/cancelar ajuda) para cancelar!", PlayerName[i]);
                        return SendClientMessage(playerid, COLOR_LIGHTRED, string);
                    }
                }

                format(string, sizeof(string), "* Voc� pagou $%d para o mercen�rio %s lhe ajudar.", MercMoney[playerid], PlayerName[MercOffer[playerid]]);
                SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
                SendClientMessage(playerid, COLOR_LIGHTBLUE, "Voc� pode cancelar a ajuda usando (/cancelar ajuda)");
                format(string, sizeof(string), "* %s aceitou sua ajuda por $%d.", PlayerName[playerid], MercMoney[playerid]);
                SendClientMessage(MercOffer[playerid], COLOR_LIGHTBLUE, string);
                SendClientMessage(MercOffer[playerid], COLOR_LIGHTBLUE, "Voc� pode cancelar a ajuda usando (/cancelar ajuda)");
                new idplayer = MercOffer[playerid];
                Player_RemoveMoney(playerid, MercMoney[playerid]);
                Player_AddMoney(idplayer, MercMoney[playerid]);

                SetPVarInt(MercOffer[playerid], "acordoID", playerid);
                SetPVarInt(MercOffer[playerid], "MercORG", GetPlayerOrg(playerid));

                MercOffer[playerid] = 999;
                MercMoney[playerid] = 0;
                return true;
            }
            else
            {
                SendClientMessage(playerid, -1, "O mercen�rio n�o est� perto de voc� !");
                return true;
            }
        }
    }
    else
    {
        SendClientMessage(playerid, -1, "Ninguem se ofereceu para ajudar voc� !");
    }
    return true;
}