

enum pDanoEnum
{
	bool: danoKilled,
	danoDamager,
	danoWeapon,
	danoBodypart,
	danoTime,
	danoLast,
	Text3D:danoText,
}
new DanoInfo[MAX_PLAYERS][pDanoEnum];


// Getters e Setters
stock Text3D:Injured_3DText(playerid) {
    return DanoInfo[playerid][danoText];
}