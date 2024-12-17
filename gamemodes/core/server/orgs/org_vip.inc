#include <YSI_Coding\y_hooks>

stock OrgInfo_SetVIP(playerid, orgid, meses) {

    new query[185];
    if (meses == 0) {
        mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `org_info` SET `org_vip_date` = TIMESTAMPDIFF(DAY, 1, CURRENT_TIMESTAMP()) WHERE `id` = '%d'", orgid);
        CofreOrg[orgid][orgVIP] = 0;
        ServerLog::("org-vip", "%s [%d] removeu a ORG-VIP da org: %d", PlayerName[playerid], PlayerInfo[playerid][pID], orgid);
        return 1;
    }

	mysql_format(MySQL_Handle, query, sizeof query, "SELECT * FROM `org_info` WHERE `id` = '%d' AND `org_vip_date` > CURRENT_TIMESTAMP() LIMIT 1", orgid);
	new Cache:serverCache = mysql_query(MySQL_Handle, query);

	new row_count;
	cache_get_row_count(row_count);
	if (row_count) {
	    new rowstring[75];
	    cache_get_value_name(0, "org_vip_date", rowstring);
	    mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `org_info` SET `org_vip_date` = TIMESTAMPADD(MONTH, %d, '%s') WHERE `id` = '%d'", meses, rowstring, orgid);
	} else {
    	mysql_format(MySQL_Handle, query, sizeof (query), "UPDATE `org_info` SET `org_vip_date` = TIMESTAMPADD(MONTH, %d, CURRENT_TIMESTAMP()) WHERE `id` = '%d'", meses, orgid);
	}
	cache_delete(serverCache);
    mysql_tquery(MySQL_Handle, query);

    CofreOrg[orgid][orgVIP] = 1;
	ServerLog::("org-vip", "%s [%d] ativou ORG-VIP para org: %d | Meses: %d", PlayerName[playerid], PlayerInfo[playerid][pID], orgid, meses);

    return 1;
}

stock OrgInfo_GetVIP(orgid) {
	return CofreOrg[orgid][orgVIP];
}

hook OnGameModeInit() {
    new query[255];
    for (new org; org < MAX_ORGS; org++) {
        format(query, sizeof(query), "SELECT DATE_FORMAT(org_vip_date, '%%d/%%m/%%Y %%H:%%i:%%s') as org_vip_date FROM `org_info` WHERE id = %d AND CURRENT_TIMESTAMP() < `org_vip_date` LIMIT 1", org);
        mysql_pquery(MySQL_Handle, query, "OnOrgVIPCheck", "d", org);
    }
}

CALLBACK: OnOrgVIPCheck(orgid) {
	new row_count;
	cache_get_row_count(row_count);
	if (row_count) {
        new serverRow[75];
		cache_get_value_name(0, "org_vip_date", serverRow);

        CofreOrg[orgid][orgVIP] = 1;
	} else {
        CofreOrg[orgid][orgVIP] = 0;

        SendMembersMessage(orgid, COLOR_LIGHTRED, "Atenção: A ORG-VIP da sua organização acaba de vencer!");

        new string[128];
        format(string, sizeof(string), "Info: A org VIP da organizacao %d venceu", orgid);
        server_log("org-vip", string);
    }
}