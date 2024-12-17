// Mapa completo da Ammunation (Criação de Theus_Crazzy / wearLyS)
// Aqui ainda o desenvolvimento está de forma embaralhada, ainda será reorganizado de forma que entenda o código.

#include    < YSI_Coding\y_hooks >

enum enumActorAmmu
{
    actor_skin,
    Float:actor_x,
    Float:actor_y,
    Float:actor_z,
    Float:actor_r,
    actor_world,
};

new prop_checkpoint_interact[1000];

// Adiciona os atores aqui e aumente o máximo em MAX_ACTORS_AMMU
static const AMMU_Actor[11][enumActorAmmu] =
{
    { 179, 294.1832, -40.2677, 1000.8156, 0.0000, 10053 },
    { 179, 294.1832, -40.2677, 1000.8156, 0.0000, 10057 },
    { 179, 294.1832, -40.2677, 1000.8156, 0.0000, 10059 },
    { 179, 294.1832, -40.2677, 1000.8156, 0.0000, 10063 },
    { 179, 294.1832, -40.2677, 1000.8156, 0.0000, 10065 },
    { 179, 294.1832, -40.2677, 1000.8156, 0.0000, 10072 },
    { 179, 294.1832, -40.2677, 1000.8156, 0.0000, 10073 },
    { 179, 294.1832, -40.2677, 1000.8156, 0.0000, 10074 },
    { 179, 294.1832, -40.2677, 1000.8156, 0.0000, 10075 },
    { 179, 294.1832, -40.2677, 1000.8156, 0.0000, 10076 },
    { 179, 294.1832, -40.2677, 1000.8156, 0.0000, 10077 }
};
new AMMU_ActorID[sizeof(AMMU_Actor)];

stock CreateMap_Ammunations() // Ammunation
{
    //Actors
    for (new actors; actors < sizeof(AMMU_ActorID); actors++) {
        AMMU_ActorID[actors] = CreateDynamicActor(AMMU_Actor[actors][actor_skin], AMMU_Actor[actors][actor_x], AMMU_Actor[actors][actor_y], AMMU_Actor[actors][actor_z], AMMU_Actor[actors][actor_r]);
        SetDynamicActorVirtualWorld(AMMU_ActorID[actors], AMMU_Actor[actors][actor_world]);
        ApplyDynamicActorAnimation(AMMU_ActorID[actors], "WEAPONS","SHP_Tray_Pose", 4.1, 1, 0, 0, 0, 0);
        ApplyDynamicActorAnimation(AMMU_ActorID[actors], "WEAPONS","SHP_Tray_Pose", 4.1, 1, 0, 0, 0, 0);
    }
    for (new checkid; checkid < sizeof(prop_checkpoint_interact); checkid++) {
        switch (checkid) {
            case 53, 57, 59, 63, 65, 72, 73, 74, 75, 76, 77: {
                prop_checkpoint_interact[checkid] = CreateDynamicCP(294.0913, -38.5131, 1001.5156, 0.5, (10000 + checkid));
            }
        }
    }

    printf("[MAPA %d]: Ammunation 01... Carregada com sucesso!", gm_count[COUNT_CREATEMAP]);
    gm_count[COUNT_CREATEMAP]++;
}