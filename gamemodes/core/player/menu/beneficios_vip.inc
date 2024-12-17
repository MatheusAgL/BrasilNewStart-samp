

		/*____________________________________________________________________________________________________________________________________________

						 ___________   _________     ________
						|    ___   \  |    __   \  /         \          Brasil Play Start ®
						|   |___/  |  |   |__|  | |    ______/              Fundação: Theus_Crazzy
						|   ______/   |    _____/ |   |______                   Data: 22/02/2016
						|         \   |   /       \          \                      Modulo: Menu de configurações
						|    ____  |  |   |        \_____    /                          
						|   |___/  |  |   |        /         \                              Theus_Crazzy (Desenvolvedor do módulo)
						|_________/   |___|        \_________/                                  Descrição: Sistema de menu de configurações gerais


		____________________________________________________________________________________________________________________________________________*/


// ----------- Armas de kit --------------

stock weaponsDonateRank(playerid, rankvip)
{
	switch (rankvip)
	{
		case 1:
		{
			SetPlayerHealth(playerid, 100);         // Vida 100 por cento
			SetPlayerArmour(playerid, 100);         // Colete 100 por cento

			ResetPlayerWeapons(playerid);           // Resetar as Armas
			GivePlayerWeapon(playerid, WEAPON_BRASSKNUCKLE, 1);
			GivePlayerWeapon(playerid, WEAPON_KNIFE, 1);
			GivePlayerWeapon(playerid, WEAPON_DEAGLE, 999);
			GivePlayerWeapon(playerid, WEAPON_SHOTGSPA, 999);
			GivePlayerWeapon(playerid, WEAPON_MP5, 999);
			GivePlayerWeapon(playerid, WEAPON_M4, 999);
			GivePlayerWeapon(playerid, WEAPON_SNIPER, 999);
			GivePlayerWeapon(playerid, WEAPON_SPRAYCAN, 999);
		}
		case 2:
		{
			SetPlayerHealth(playerid, 100);         // Vida 100 por cento
			SetPlayerArmour(playerid, 100);         // Colete 100 por cento

			ResetPlayerWeapons(playerid); 			// Resetar as Armas
			GivePlayerWeapon(playerid, WEAPON_BRASSKNUCKLE, 1);
			GivePlayerWeapon(playerid, WEAPON_KNIFE, 1);
			GivePlayerWeapon(playerid, WEAPON_KNIFE, 10);
			GivePlayerWeapon(playerid, WEAPON_DEAGLE, 999);
			GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 999);
			GivePlayerWeapon(playerid, WEAPON_MP5, 999);
			GivePlayerWeapon(playerid, WEAPON_AK47, 999);
			GivePlayerWeapon(playerid, WEAPON_SNIPER, 999);
			GivePlayerWeapon(playerid, WEAPON_FIREEXTINGUISHER, 9999);
		}
		case 3:
		{
			SetPlayerHealth(playerid, 100);         // Vida 100 por cento
			SetPlayerArmour(playerid, 100);         // Colete 100 por cento

		   	ResetPlayerWeapons(playerid); 			// Resetar as Armas
			GivePlayerWeapon(playerid, WEAPON_BRASSKNUCKLE, 1);
			GivePlayerWeapon(playerid, WEAPON_KNIFE, 1);
			GivePlayerWeapon(playerid, WEAPON_KNIFE, 10);
			GivePlayerWeapon(playerid, WEAPON_DEAGLE, 999);
			GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 999);
			GivePlayerWeapon(playerid, WEAPON_MP5, 999);
			GivePlayerWeapon(playerid, WEAPON_M4, 999);
			GivePlayerWeapon(playerid, WEAPON_SNIPER, 999);
			GivePlayerWeapon(playerid, WEAPON_FIREEXTINGUISHER, 9999);
 		}
 		case 4:
 		{
			SetPlayerHealth(playerid, 100);         // Vida 100 por cento
			SetPlayerArmour(playerid, 100);         // Colete 100 por cento

 		    ResetPlayerWeapons(playerid); 			// Resetar as Armas
			GivePlayerWeapon(playerid, WEAPON_KNIFE, 1);
			GivePlayerWeapon(playerid, WEAPON_DEAGLE, 999);
			GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 999);
			GivePlayerWeapon(playerid, WEAPON_MP5, 999);
			GivePlayerWeapon(playerid, WEAPON_M4, 999);
			GivePlayerWeapon(playerid, WEAPON_SNIPER, 9999);
		}
		case 5:
		{
			SetPlayerHealth(playerid, 100);         // Vida 100 por cento
			SetPlayerArmour(playerid, 100);         // Colete 100 por cento

		    ResetPlayerWeapons(playerid); 			// Resetar as Armas
			GivePlayerWeapon(playerid, WEAPON_BRASSKNUCKLE, 1);
			GivePlayerWeapon(playerid, WEAPON_KNIFE, 1);
			GivePlayerWeapon(playerid, WEAPON_DEAGLE, 999);
			GivePlayerWeapon(playerid, WEAPON_SHOTGSPA, 999);
			GivePlayerWeapon(playerid, WEAPON_MP5, 999);
			GivePlayerWeapon(playerid, WEAPON_M4, 999);
			GivePlayerWeapon(playerid, WEAPON_SNIPER, 9999);
			GivePlayerWeapon(playerid, WEAPON_SPRAYCAN, 9999);
		}
	}
}
