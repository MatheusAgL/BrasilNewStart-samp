/*

    Sistema de vícios, uso de drogas, cigarro, bebida, personagem com problemas.

    Última modificação: 10/03/2021
    Responsável: Theus_Crazzy

*/

#include        < YSI_Coding\y_hooks >		            // Include 'y_hooks'

#define         TIME_SMOKE_PUFF             1000*3      // Quantidade de tempo que leva para soltar a fumaça

#define         STATUS_CIGARETTE_LIGHTING   1           // Acendendo o cigarro
#define         STATUS_CIGARETTE_ASHES      2           // Batendo as cinzas do cigarro
#define         STATUS_CIGARETTE_THROW      3           // Jogando o cigarro fora
#define         STATUS_CIGARETTE_GULP       4           // Dando um trago

new Float:SMOKE_PUFF_LIFE[MAX_PLAYERS];                 // Quantidade de vida no cigarro

CMD:fumar(playerid)
{
    if (PlayerInfo[playerid][pCigarros] < 1)
        return SendClientMessage(playerid, -1, "Você não tem cigarro, compre em algum comércio.");

    if (!PlayerInfo[playerid][pIsqueiro])
        return SendClientMessage(playerid, -1, "Você está sem isqueiro, compre em algum comércio.");

    if (GetPVarInt(playerid, "busyhands")) {
        SendClientMessage(playerid, -1, "A sua mão direita está ocupada.");
        return SendClientMessage(playerid, 0x9C9C9CAA, "Use H para consumir e ALT para jogar fora o item!");
    }

    // Definindo a quantidade de vida para restaurar fumando
    SMOKE_PUFF_LIFE[playerid] = 20.0;

    // Removendo 1 cigarro do maço do jogador
    PlayerInfo[playerid][pCigarros]--;

    // Enviando uma mensagem aos jogadores próximos
    new string[53];

    format(string, sizeof(string), "* %s começou a fumar um cigarro.", PlayerName[playerid]);
    SendClientMessageInRange(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

    // Cigarrinho
    SetPlayerAttachedObject(playerid, Slot_Colete, 19625, 6, 0.1250, -0.0030, 0.0360, -99.0000, 41.0000, 90.1000, 1.0000, 1.0000, 1.0000);

    // Aparece na tela do player
    ShowPlayerPopupHUD(playerid, "STATUS", "~w~Voce esta fumando, use ~p~ALT", 6000);

    // Define a ação de fumar
    SetPVarInt(playerid, "busyhands", 0);

    // NULL #Bug fix
    ApplyAnimation(playerid, "SMOKING", "null", 0.0, 0,0, 0, 0, 0);

    return 1;
}

timer smokePuff_Timer[TIME_SMOKE_PUFF](playerid)
{
    SetPVarInt(playerid, "busyhands", 0);

    // Adicionando recuperador de saúde lenta
    switch(SMOKE_PUFF_LIFE[playerid])   
    {
        case 20.0: 
        {
            // Removendo o fogo do isqueiro
            RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);

            SMOKE_PUFF_LIFE[playerid] -= 2.0;
            PlayerInfo[playerid][pRestoreLife] += 2.0;
        }
        case 10.0: 
        {
            SMOKE_PUFF_LIFE[playerid] -= 2.0;
            PlayerInfo[playerid][pRestoreLife] += 2.0;
        }
        case 2.0:
        {
            // Restaurar vida
            SMOKE_PUFF_LIFE[playerid] -= 2.0;
            PlayerInfo[playerid][pRestoreLife] += 2.0;

            // Lixo na rua
            GenerateTrash(playerid, 19625, 1, "Bituca de cigarro", 1);

            // Removendo itens de cigarro
            RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);
            RemovePlayerAttachedObject(playerid, Slot_Colete);

            // Limpando animações
            ClearAnimations(playerid);

            // Balão informativo
            ShowPlayerPopupHUD(playerid, "STATUS", "Seu cigarro acabou...", 5000);
        }
        default: 
        {
            // Soltar fumaça
            SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, 18677, 2, 0.0000, 0.1630, -1.5550, 0.0000, 0.0000, 0.0000, 1.0000, 1.0000, 1.0000);

            SMOKE_PUFF_LIFE[playerid] -= 2.0;
            PlayerInfo[playerid][pRestoreLife] += 2.0;
        }
    }
}

timer playerFood_Timer[TIME_PLAYER_FOOD](playerid)
{
    SetPVarInt(playerid, "busyhands", 0);

    if (PlayerInfo[playerid][pRestoreFome] >= 10.0) {
        PlayerInfo[playerid][pRestoreFome] -= 10.0;
        giveFome(playerid, 10.0);
    }
    else {
        giveFome(playerid, PlayerInfo[playerid][pRestoreFome]);
        PlayerInfo[playerid][pRestoreFome] = 0.0;
    }

    if (PlayerInfo[playerid][pRestoreFome] > 0.0) {
        new string[128];
        GetPVarString(playerid, "right_hand_object_name", string, sizeof(string));

        format(string, sizeof(string), "~w~Voce mastigou um(a) ~p~%s ~w~aperte ~b~ALT ~w~para comer mais", string);
        ShowPlayerBaloonInfo(playerid, string, 5000);
    }
    else {
        if(PlayerInfo[playerid][pFome] >= 98.00 && PlayerInfo[playerid][pFome] <= 200.00)
            ShowPlayerPopupHUD(playerid, "FOME", "~w~Voce comeu e esta: ~g~~h~cheio", 10000);
        else if(PlayerInfo[playerid][pFome] >= 80.00 && PlayerInfo[playerid][pFome] < 98.00)
            ShowPlayerPopupHUD(playerid, "FOME", "~w~Voce comeu e esta: ~g~satisfeito", 10000);
        else if(PlayerInfo[playerid][pFome] >= 50.00 && PlayerInfo[playerid][pFome] < 80.00)
            ShowPlayerPopupHUD(playerid, "FOME", "~w~Voce comeu e esta: ~b~~h~meio satisfeito", 10000);
        else
            ShowPlayerPopupHUD(playerid, "FOME", "~w~Voce comeu e esta: ~r~~h~insatisfeito", 10000);

        RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);
        ClearAnimations(playerid);
    }
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    // Sistema de soltar a fumaça do cigarro no personagem
    if (newkeys & KEY_WALK)
	{
        if (GetPVarInt(playerid, "busyhands") == 0) 
        {
            if (SMOKE_PUFF_LIFE[playerid] > 0.0)
            {
                switch(SMOKE_PUFF_LIFE[playerid])
                {
                    case 20.0: ApplyAnimationCigar(playerid, STATUS_CIGARETTE_LIGHTING); // Acendendo o cigarro
                    case 10.0: ApplyAnimationCigar(playerid, STATUS_CIGARETTE_ASHES); // Batendo as cinzas do cigarro
                    case 2.0: ApplyAnimationCigar(playerid, STATUS_CIGARETTE_THROW); // Jogando o cigarro fora
                    default: ApplyAnimationCigar(playerid, STATUS_CIGARETTE_GULP); // Dando um trago
                }
            }
            if (PlayerInfo[playerid][pRestoreFome] > 0.0)
            {
                ClearAnimations(playerid);
                ApplyAnimationFood(playerid);
                ShowPlayerPopupHUD(playerid, "STATUS", "~g~! ~w~Voce esta mastigando...", TIME_PLAYER_FOOD-500);
                defer playerFood_Timer(playerid);
                SetPVarInt(playerid, "busyhands", 1);
            }
        }
    }
    else if (newkeys & KEY_SECONDARY_ATTACK)
    {
        new string[128];

        if (PlayerInfo[playerid][pRestoreFome] > 0.0)
        {
            // Pegando nome e ID da comida/bebida
            new modelid = GetPVarInt(playerid, "right_hand_object");
            GetPVarString(playerid, "right_hand_object_name", string, sizeof(string));

            // Mensagem
            format(string, sizeof(string), "Você jogou fora a(o) '%s' que estava comendo.", string);
            SendClientMessage(playerid, -1, string);

            // Gerando lixo no chão ou no inventário
            switch (modelid)
			{
				case ITEM_MODEL_CARNE: GenerateTrash(playerid, modelid, 1, "Restos de carne");
				case ITEM_MODEL_PAO: GenerateTrash(playerid, modelid, 1, "Farelos de pao");
				case ITEM_MODEL_PIZZA: GenerateTrash(playerid, 2838, 1, "Embalagem de pizza");
				case ITEM_MODEL_FRANGO: GenerateTrash(playerid, modelid, 1, "Restos de frango");
				case ITEM_MODEL_BURGUER: GenerateTrash(playerid, 2768, 1, "Embalagem de hamburger");
				default: GenerateTrash(playerid, modelid, 1, "Restos de Peixe");
			}

            // Removendo item da mão
            RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);

            // Cancelando animação e zerando restauração da fome
            ClearAnimations(playerid);
            PlayerInfo[playerid][pRestoreFome] = 0;
        }

        if (PlayerInfo[playerid][pRestoreSede] > 0.0)
        {
            // Pegando nome e ID da comida/bebida
            new modelid = GetPVarInt(playerid, "right_hand_object");
            GetPVarString(playerid, "right_hand_object_name", string, sizeof(string));

            // Mensagem
            format(string, sizeof(string), "Você jogou fora a(o) '%s' que estava comendo.", string);
            SendClientMessage(playerid, -1, string);

            // Gerando lixo no chão ou no inventário
            switch (modelid)
			{
				case ITEM_MODEL_CARNE: GenerateTrash(playerid, modelid, 1, "Restos de carne");
				case ITEM_MODEL_PAO: GenerateTrash(playerid, modelid, 1, "Farelos de pao");
				case ITEM_MODEL_PIZZA: GenerateTrash(playerid, 2838, 1, "Embalagem de pizza");
				case ITEM_MODEL_FRANGO: GenerateTrash(playerid, modelid, 1, "Restos de frango");
				case ITEM_MODEL_BURGUER: GenerateTrash(playerid, 2768, 1, "Embalagem de hamburger");
				default: GenerateTrash(playerid, modelid, 1, "Restos de Peixe");
			}

            // Removendo item da mão
            RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);

            // Cancelando animação e zerando restauração da fome
            ClearAnimations(playerid);
            PlayerInfo[playerid][pRestoreFome] = 0;
        }

        if (SMOKE_PUFF_LIFE[playerid] > 0.0)
        {
            SendClientMessage(playerid, -1, "Você jogou fora seu cigarro que estava fumando.");

            GenerateTrash(playerid, 19625, 1, "Bituca de cigarro", 1);

            RemovePlayerAttachedObject(playerid, SLOT_HAND_RIGHT);
            RemovePlayerAttachedObject(playerid, Slot_Colete);

            ClearAnimations(playerid);
            SMOKE_PUFF_LIFE[playerid] = 0.0;
        }
    }

    return 1;
}

static ApplyAnimationCigar(playerid, status)
{
    // Limpa as animações (padrão á todos os 'status')
    ClearAnimations(playerid);

    switch(status) {
        case STATUS_CIGARETTE_LIGHTING: {
            // Adiciona um fogo para simular o isqueiro
            SetPlayerAttachedObject(playerid, SLOT_HAND_RIGHT, 18701, 5, 0.6610, 0.4090, 1.3890, -14.3000, -160.3000, -48.7000, 1.0000, 1.0000, 1.0000);

            // Aplica animação de acender o cigarro...
            ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.1, 0, 0, 0, 0, TIME_SMOKE_PUFF, SYNC_NONE);

            // Mensagem relacionado a ação...
            ShowPlayerMessage(playerid, "~w~Voce usou seu ~r~isqueiro ~w~para acender um cigarro...", TIME_SMOKE_PUFF-500);
        }
        case STATUS_CIGARETTE_GULP: {
            // Aplica animação de acender o cigarro...
            ApplyAnimation(playerid, "SMOKING", "M_smk_drag", 4.1, 0, 0, 0, 0, TIME_SMOKE_PUFF, SYNC_NONE);

            // Mensagem relacionado a ação...
            ShowPlayerMessage(playerid, "~w~Voce deu um trago em seu cigarro...", TIME_SMOKE_PUFF-500);
        }
        case STATUS_CIGARETTE_ASHES: {
            // Aplica animação de bater as cinzas do cigarro...
            ApplyAnimation(playerid, "SMOKING", "M_smk_tap", 4.1, 0, 0, 0, 0, TIME_SMOKE_PUFF, SYNC_NONE);

            // Mensagem relacionado a ação...
            ShowPlayerMessage(playerid, "~w~Voce esta batendo as cinzas do seu cigarro...", TIME_SMOKE_PUFF-500);
        }
        case STATUS_CIGARETTE_THROW: {
            // Aplica animação de acender o cigarro...
            ApplyAnimation(playerid, "SMOKING", "M_smk_out", 4.1, 0, 0, 0, 0, TIME_SMOKE_PUFF, SYNC_NONE);
        }
    }

    // Para soltar a fumaça após o trago!
    defer smokePuff_Timer(playerid);
    SetPVarInt(playerid, "busyhands", 1);
}