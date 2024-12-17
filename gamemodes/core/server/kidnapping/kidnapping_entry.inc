new
	bool:orgKidnapping[MAX_ORGS],
	bool:retirandoOrgaos[MAX_PLAYERS],
	sequestrosAtivo,
	resgateValor[MAX_PLAYERS],
	Text3D:textRipOrgan[MAX_PLAYERS],
	usandoCativeiro[MAX_PLAYERS];

static
	bool:beingAbducted[MAX_PLAYERS];

stock SetPlayerBeingAbducted(playerid, bool:status)
	beingAbducted[playerid] = status;

stock GetPlayerBeingAbducted(playerid)
	return beingAbducted[playerid];

stock isOrgSeq(playerid)
{
	switch (GetPlayerOrg(playerid))
	{
		case 5, 6, 8, 10, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28: return true;
	}
	return false;
}