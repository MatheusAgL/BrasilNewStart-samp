CALLBACK:SalarioPlayer(playerid)
{
	if(PlayerInfo[playerid][pCargo] > 0)
	{
	    new gstring[128];
       	if(PlayerInfo[playerid][pCargo] == 1)
		{
  			new org = GetPlayerOrg(playerid);
  			if(CofreOrg[org][salarioc1] == 0)
		    {
      			SendClientMessage(playerid, -1, "Sua organização não tem salário definido, converse com o Líder/Sub-Líder");
      			return 1;
			}
	    	if(CofreOrg[org][orgDinheiro] < CofreOrg[org][salarioc1])
		    {
      			SendClientMessage(playerid, -1, "Sua organização não pode pagar o seu salario neste PayDay");
      			return 1;
			}
			format(gstring, sizeof(gstring), "Salario da organização: {41DD36}$%d", CofreOrg[org][salarioc1]);
			SendClientMessage(playerid, -1, gstring);

			OrgInfo_SetMoney(org, OrgInfo_GetMoney(org) - CofreOrg[org][salarioc1]);
			Player_AddMoney(playerid, CofreOrg[org][salarioc1]);
		}
		else if(PlayerInfo[playerid][pCargo] == 2)
		{
  			new org = GetPlayerOrg(playerid);
  			if(CofreOrg[org][salarioc2] == 0)
		    {
      			SendClientMessage(playerid, -1, "Sua organização não tem salário definido, converse com o Líder/Sub-Líder");
      			return 1;
			}
	    	if(CofreOrg[org][orgDinheiro] < CofreOrg[org][salarioc2])
		    {
		        SendClientMessage(playerid, -1, "Sua organização não pode pagar o seu salario neste PayDay");
      			return 1;
			}
			format(gstring, sizeof(gstring), "Salario da organização: {41DD36}$%d", CofreOrg[org][salarioc2]);
			SendClientMessage(playerid, -1, gstring);

			OrgInfo_SetMoney(org, OrgInfo_GetMoney(org) - CofreOrg[org][salarioc2]);
			Player_AddMoney(playerid, CofreOrg[org][salarioc2]);
		}
		else if(PlayerInfo[playerid][pCargo] == 3)
		{
		    new org = GetPlayerOrg(playerid);
		    if(CofreOrg[org][salarioc3] == 0)
		    {
      			SendClientMessage(playerid, -1, "Sua organização não tem salário definido, converse com o Líder/Sub-Líder");
      			return 1;
			}
		    if(CofreOrg[org][orgDinheiro] < CofreOrg[org][salarioc3])
		    {
		        SendClientMessage(playerid, -1, "Sua organização não pode pagar o seu salario neste PayDay");
		        return 1;
			}
			format(gstring, sizeof(gstring), "Salario da organização: {41DD36}$%d", CofreOrg[org][salarioc3]);
			SendClientMessage(playerid, -1, gstring);

			OrgInfo_SetMoney(org, OrgInfo_GetMoney(org) - CofreOrg[org][salarioc3]);
			Player_AddMoney(playerid, CofreOrg[org][salarioc3]);
		}
		else if(PlayerInfo[playerid][pCargo] == 4)
		{
		    new org = GetPlayerOrg(playerid);
		    if(CofreOrg[org][salarioc4] == 0)
		    {
      			SendClientMessage(playerid, -1, "Sua organização não tem salário definido, converse com o Líder/Sub-Líder");
      			return 1;
			}
		    if(CofreOrg[org][orgDinheiro] < CofreOrg[org][salarioc4])
		    {
		        SendClientMessage(playerid, -1, "Sua organização não pode pagar o seu salario neste PayDay");
		        return 1;
			}
			format(gstring, sizeof(gstring), "Salario da organização: {41DD36}$%d", CofreOrg[org][salarioc4]);
			SendClientMessage(playerid, -1, gstring);

			OrgInfo_SetMoney(org, OrgInfo_GetMoney(org) - CofreOrg[org][salarioc4]);
			Player_AddMoney(playerid, CofreOrg[org][salarioc4]);
		}
		else if(PlayerInfo[playerid][pCargo] > 5 && PlayerInfo[playerid][pCargo] != LIDER)
		{
		    new org = GetPlayerOrg(playerid);
		    if(CofreOrg[org][salarioc5] == 0)
		    {
         		SendClientMessage(playerid, -1, "Sua organização não tem salário definido, converse com o Líder/Sub-Líder");
      			return 1;
			}
		    if (CofreOrg[org][orgDinheiro] < CofreOrg[org][salarioc5])
		    {
		        SendClientMessage(playerid, -1, "Sua organização não pode pagar o seu salario neste PayDay");
		        return 1;
			}
			format(gstring, sizeof(gstring), "Salario da organização: {41DD36}$%d", CofreOrg[org][salarioc5]);
			SendClientMessage(playerid, -1, gstring);

			OrgInfo_SetMoney(org, OrgInfo_GetMoney(org) - CofreOrg[org][salarioc5]);
			Player_AddMoney(playerid, CofreOrg[org][salarioc5]);
		}
		else if(PlayerInfo[playerid][pCargo] == LIDER)
		{
		    new org = GetPlayerOrg(playerid);
		    if(CofreOrg[org][salariolider] == 0)
		    {
      			SendClientMessage(playerid, -1, "Sua organização não tem salário para Líder, defina no InfoOrg da HQ");
      			return 1;
			}
		    if (CofreOrg[org][orgDinheiro] < CofreOrg[org][salariolider])
		    {
	     		SendClientMessage(playerid, -1, "Sua organização não pode pagar o seu salario neste PayDay");
			    return 1;
			}
			format(gstring, sizeof(gstring), "Salario da organização: {41DD36}$%d", CofreOrg[org][salariolider]);
			SendClientMessage(playerid, -1, gstring);

			OrgInfo_SetMoney(org, OrgInfo_GetMoney(org) - CofreOrg[org][salariolider]);
			Player_AddMoney(playerid, CofreOrg[org][salariolider]);
		}
	}
	return true;
}