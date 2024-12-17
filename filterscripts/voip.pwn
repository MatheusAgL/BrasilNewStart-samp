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
    // Checando se o sampvoice est� no computador.
    if (SvGetVersion(playerid) == SV_NULL)
    {
        SetPVarInt(playerid, "voice_samp_active", 0);

        SendClientMessage(playerid, COLOR_SAMP, "Voc� n�o possui o 'sampvoice-plugin' instalado em seu GTA.");
		SendClientMessage(playerid, COLOR_SAMP, "Para mais informa��es entre em nosso discord: "SERVER_DISCORD"");
    }
    // Checando se est� com microfone ativo
    else if (SvHasMicro(playerid) == SV_FALSE)
    {
        SetPVarInt(playerid, "voice_samp_active", 1);

        SendClientMessage(playerid, COLOR_SAMP, "Voc� tem o 'sampvoice-plugin' instalado, mas n�o detectamos nenhum microfone.");
    }
	// Informando que est� com microfone e com o plugin ativo, modifique '15.0' para dist�ncia da voz.
    else if ((lstream[playerid] = SvCreateDLStreamAtPlayer(15.0, SV_INFINITY, playerid, COLOR_SAMP, "Local")))
    {
        SetPVarInt(playerid, "voice_samp_active", 1);

        SendClientMessage(playerid, COLOR_SAMP, "Voc� est� com o 'sampvoice-plugin' instalado!");
		SendClientMessage(playerid, COLOR_SAMP, "Use a letra 'B' para falar no chat voice local e F11 para configura��es.");

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

