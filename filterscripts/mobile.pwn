
#include <a_samp>

#define FILTERSCRIPT
#pragma warning disable 239

public OnFilterScriptInit() {
    print("Android check: Carregado com sucesso!");
}

public OnPlayerConnect(playerid) {
    SendClientCheck(playerid, 0x48, 0, 0, 2);
    return 1;
}

public OnClientCheckResponse(playerid, actionid, memaddr, retndata)
{
    switch(actionid) {       
        case 0x48: {
            SetPVarInt(playerid, "NotAndroid", 1);	
        }
    }
    return 1;
}