#include <a_samp>
#include <sampvoice>

#define FILTERSCRIPT

#define COLOR_SAMP 0xACCBF1FF
#define SERVER_DISCORD "https://discord.gg/pj7ySw9tPG"

new SV_LSTREAM:lstream[MAX_PLAYERS] = { SV_NULL, ... };
//new Text3D:playerTextVoIP[MAX_PLAYERS];

public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid) 
{
    // Tecla 'B'
    if (keyid == 0x42 && lstream[playerid])
        SvAttachSpeakerToStream(lstream[playerid], playerid);
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Tecla 'B'
    if (keyid == 0x42 && lstream[playerid])
        SvDetachSpeakerFromStream(lstream[playerid], playerid);
}

public OnFilterScriptInit() {
    print("VoIP: Carregado com sucesso...");
}

public OnPlayerConnect(playerid)
{
    // Checando se o sampvoice está no computador.
    if (SvGetVersion(playerid) == SV_NULL)
    {
        SetPVarInt(playerid, "voice_samp_active", 0);

        SendClientMessage(playerid, COLOR_SAMP, "Você não possui o 'sampvoice-plugin' instalado em seu GTA.");
		SendClientMessage(playerid, COLOR_SAMP, "Para mais informações entre em nosso discord: "SERVER_DISCORD"");
    }
    // Checando se está com microfone ativo
    else if (SvHasMicro(playerid) == SV_FALSE)
    {
        SetPVarInt(playerid, "voice_samp_active", 1);

        SendClientMessage(playerid, COLOR_SAMP, "Você tem o 'sampvoice-plugin' instalado, mas não detectamos nenhum microfone.");
    }
	// Informando que está com microfone e com o plugin ativo, modifique '15.0' para distância da voz.
    else if ((lstream[playerid] = SvCreateDLStreamAtPlayer(15.0, SV_INFINITY, playerid, COLOR_SAMP, "Local")))
    {
        SetPVarInt(playerid, "voice_samp_active", 1);

        SendClientMessage(playerid, COLOR_SAMP, "Você está com o 'sampvoice-plugin' instalado!");
		SendClientMessage(playerid, COLOR_SAMP, "Use a letra 'B' para falar no chat voice local e F11 para configurações.");

        // Tecla 'B'
        SvAddKey(playerid, 0x42);
    }
}

public OnPlayerDisconnect(playerid)
{
    if (lstream[playerid]) {
        SvDeleteStream(lstream[playerid]);
        lstream[playerid] = SV_NULL;
    }
}

