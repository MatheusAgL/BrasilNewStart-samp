CALLBACK: acalmarActor(actorid) {
    ActorInfo[actorid][actrendido] = false;
    ActorInfo[actorid][actmorto] = false;
    ActorInfo[actorid][actTimer] = -1;
    ApplyActorAnimation(actorid, ActorInfo[actorid][actanimLib], ActorInfo[actorid][actanimName], 4.1, true, false, false, false, 0);
}