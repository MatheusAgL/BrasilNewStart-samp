// PlayerToPoint:
#define PlayerToPoint(%1,%2,%3)    \
	IsPlayerInRangeOfPoint(%2,%1,%3)

// Utils
#include <random_rcon>
#include <chat_messages>
// #include <checkpoints>
#include <map_marker>

// Defines:
#define	CP_NULL 0

// Callbacks:
#define CALLBACK:%0(%1)		\
	forward %0(%1); public %0(%1)

// Mensagem na tela caso o sistema estiver inativo
#define	MESSAGE_WARNING_INACTIVE_SYSTEM	\
	SendClientMessage(playerid, COLOR_WARNING, "[Sistema temporariamente inativo]")

// Porcentagem
#define CalcPercentage(%0, %1) \
	floatround(floatmul(floatdiv(%0, 100.0), %1))

// Mirando
#define HOLDING(%0) \
	((newkeys & (%0)) == (%0))

// Pressionado
#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

#define RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

// Atalho para unir strings;
new atalho_string[256];
#define FormatCat(%1,%2,%3) \
		format(atalho_string,sizeof(atalho_string),%2,%3), \
		strcat(%1, atalho_string)

// Float random:
stock Float:frandnorm(const RAND_MAX = 32767) 
	return Float:random(RAND_MAX) / Float:RAND_MAX;

stock Float:randomfloat(const Float:max) 
	return (frandnorm() * max);

// Jogador com VoIP
#define IsConnectedVoIP(%0) \
    GetPVarInt(%0, "voice_samp_active") == 1

stock GetRandomPlate()
{
	new numberplater[25];
	format(numberplater, sizeof (numberplater), "%c%c%c-%d%d%d%d", 'A' + random(26), 'A' + random(26), 'A' + random(26), random(10), random(10), random(10), random(10));
	return numberplater;
}

stock GetUniqueNumberPlate() {
	new plate[25], valid = 0, string[128];

	while(!valid) {
		plate = GetRandomPlate();

		mysql_format(MySQL_Handle, string, sizeof string, "SELECT 1 FROM `player_vehicles` WHERE plate = '%s' LIMIT 1", plate);
		mysql_query(MySQL_Handle, string);

		if(MYSQL_GetRowsCount() == 0) {
			valid = 1;
		}
	}
	return plate;
}

// -----------------------------------------------------------
// Limpar o chat do servidor

stock Chat_Clear(playerid, lines = 50) {
	for (new i; i < lines; ++i)
		SendClientMessage(playerid, -1, " ");

	return 1;
}

// Não pode usar o comando;
stock Command_ActionBlock(playerid)
{
	if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK) {
		SendClientMessage(playerid, -1, "Você não pode usar esse comando em um JetPack.");
		return 0;
	}
	if (Player_GetJailed(playerid)) {
		SendClientMessage(playerid, -1, "Você não pode usar esse comando na cadeia.");
		return 0;
	}
	return 1;
}

// // Sistema de checar se está congelado.
// #undef TogglePlayerControllable

// bns_TogglePlayerControllable(playerid, bool:mode) {
// 	SetPVarInt(playerid, "Congelado", !mode);
// 	return TogglePlayerControllable(playerid, mode);
// }
// #define TogglePlayerControllable bns_TogglePlayerControllable

// Dialog Loading...
stock ShowLoadingDialog(playerid) {
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", ""C_GRAY"Carregando... Aguarde um momento!\n", "Fechar", "");
}

// Distância de um player para o outro
stock Float:GetDistanceForPlayer(player1, player2) {
    new Float:PosX[2], Float:PosY[2], Float:PosZ[2];

    if (!IsPlayerConnected(player1) || !IsPlayerConnected(player2)) 
        return -1.00;

    GetPlayerPos(player1, PosX[0], PosY[0], PosZ[0]);
    GetPlayerPos(player2, PosX[1], PosY[1], PosZ[1]);

    return floatsqroot(floatpower(floatabs(floatsub(PosX[1], PosX[0])), 2) + floatpower(floatabs(floatsub(PosY[1], PosY[0])), 2) + floatpower(floatabs(floatsub(PosZ[1], PosZ[0])), 2));
}

// Formata os valores adicionando ponto ou virgula
stock FormatNumericString(const params[], const type[] = "."){
    static string[50];
    format(string, sizeof(string), "%s", params);

    switch(strlen(string)) {
        case 4: { // Mil
			strins(string, type, 1);
		}
        case 5: { // Dez Mil
			strins(string, type, 2);
		}
        case 6: { // Cem Mil
			strins(string, type, 3);
		}
        case 7: { // Um Milhão
			strins(string, type, 1);
			strins(string, type, 5);
		}
        case 8: { // Dez Milhoes
			strins(string, type, 2);
			strins(string, type, 6);
		}
        case 9: { // Cem Milhoes
			strins(string, type, 3);
			strins(string, type, 7);
		}
        case 10: { // Um bilhão
			strins(string, type, 1);
			strins(string, type, 5);
			strins(string, type, 9);
		}
        case 11: { // Dez bilhões
			strins(string, type, 2);
			strins(string, type, 6);
			strins(string, type, 10);
		}
        case 12: { // Cem bilhões
			strins(string, type, 3);
			strins(string, type, 7);
			strins(string, type, 11);
		}
    }
    return string;
}

stock getFormatText(value, const type[] = "."){

	static string[20];

    format(string, sizeof(string),"%d", value);

    switch(strlen(string)) {
        case 4: { // Mil
			strins(string, type, 1);
		}
        case 5: { // Dez Mil
			strins(string, type, 2);
		}
        case 6: { // Cem Mil
			strins(string, type, 3);
		}
        case 7: { // Um Milhão
			strins(string, type, 1);
			strins(string, type, 5);
		}
        case 8: { // Dez Milhoes
			strins(string, type, 2);
			strins(string, type, 6);
		}
        case 9: { // Cem Milhoes
			strins(string, type, 3);
			strins(string, type, 7);
		}
        case 10: { // Um bilhão
			strins(string, type, 1);
			strins(string, type, 5);
			strins(string, type, 9);
		}
        default: format(string, sizeof(string), "%d", value);
    }
    return string;
}

// Ocultar tela esbranquiçada
timer fadeOut_Timer[1200](playerid) {
	fadeOut(playerid, 2000, 0xFFFFFFFF);
}

// Jogadores conectados no mesmo IP
stock GetPlayersOnIp(const test_ip[])
{
    if (!strcmp(test_ip, "127.0.0.1") || !strcmp(test_ip, "localhost") || !strcmp(test_ip, "77.54.92.45") || !strcmp(test_ip, "213.22.206.206"))
		return 0;

    new against_ip[32+1],
        ip_count = 0;
    
    foreach(new x : Player) {
        GetPlayerIp(x, against_ip, 32);
        
        if (!strcmp(against_ip, test_ip)) 
			ip_count++;
    }
    return ip_count;
}

// Cria uma explosão
stock CreateExplosionEx(Float:X, Float:Y, Float:Z, type, Float:Radius, world) {
	foreach(new playerid : Player) {
	    if (GetPlayerVirtualWorld(playerid) == world) {
	        CreateExplosionForPlayer(playerid, X, Y, Z, type, Radius);
	    }
	}
}

stock ConvertMile(millisecond, const format[])
{
    new
        tmp[4],
        result[64],
        vhour,
        vminute,
        vsecond,
        format_char,
        result_lenght,
        bool:padding,
        len = strlen(format)
	;

    vhour            = (millisecond / (1000 * 60 * 60));
    vminute          = (millisecond % (1000 * 60 * 60)) / (1000 * 60);
    vsecond          = ((millisecond % (1000 * 60 * 60)) % (1000 * 60)) / 1000;
    millisecond     = millisecond - (vhour * 60 * 60 * 1000) - (vminute * 60 * 1000) - (vsecond * 1000);

    while(format_char < len)
    {
        if(format[format_char] == '%')
        {
            format_char++;

            if(format[format_char] == '1')
            {
                padding = true;
                format_char++;
            }
            else
            {
                padding = false;
            }

            switch(format[format_char])
            {
                case 'h':
                {
                    valstr(tmp, vhour);

                    if(padding)
                    {
                        if(vhour < 10)
                            strcat(result, "0");
                    }

                    strcat(result, tmp);
                    result_lenght = strlen(result);
                }

                case 'm':
                {
                    valstr(tmp, vminute);

                    if(padding)
                    {
                        if(vminute < 10)
                            strcat(result, "0");
                    }

                    strcat(result, tmp);
                    result_lenght = strlen(result);
                }

                case 's':
                {
                    valstr(tmp, vsecond);

                    if(padding)
                    {
                        if(vsecond < 10)
                            strcat(result, "0");
                    }

                    strcat(result, tmp);
                    result_lenght = strlen(result);
                }

                case 'd':
                {
                    valstr(tmp, millisecond);

                    if(padding)
                    {
                        if(millisecond < 10)
                            strcat(result, "00");

                        else if(millisecond < 100)
                            strcat(result, "0");
                    }

                    strcat(result, tmp);
                    result_lenght = strlen(result);
                }
            }
        }
        else
        {
            result[result_lenght] = format[format_char];
            result_lenght++;
        }

        format_char++;
    }

    return result;
}

stock ConvertTime(number)
{
    new 
        hours = 0, 
        mins = 0, 
        secs = 0, 
        string[17];

    hours = floatround(number / 3600);
    mins = floatround((number / 60) - (hours * 60));
    secs = floatround(number - ((hours * 3600) + (mins * 60)));

	if (hours > 0) {
        format(string, sizeof(string), "%02d:%02d:%02d", hours, mins, secs);
    } else {
        format(string, sizeof(string), "%02d:%02d", mins, secs);
    }
    return string;
}

stock ConvertTempo(number)
{
    new hours = 0, 
        mins = 0, 
        secs = 0,
        string[20];

    hours = floatround(number / 3600);
    mins = floatround((number / 60) - (hours * 60));
    secs = floatround(number - ((hours * 3600) + (mins * 60)));

	if (hours > 0) {
        format(string, sizeof(string), "%02dh %02dm %02ds", hours, mins, secs);
    } else {
        format(string, sizeof(string), "%02dm %02ds", mins, secs);
    }
    return string;
}

stock Float:GetDistanceBetweenPoints(Float:pos1X, Float:pos1Y, Float:pos1Z, Float:pos2X, Float:pos2Y, Float:pos2Z) {
	return floatadd(floatadd(floatsqroot(floatpower(floatsub(pos1X, pos2X), 2)), floatsqroot(floatpower(floatsub(pos1Y, pos2Y), 2))), floatsqroot(floatpower(floatsub(pos1Z, pos2Z), 2)));
}

stock Float:GetXYInDireitaPlane(&Float:q, &Float:w, Float:a, Float:distance)
{
	q -= (distance * floatsin(-a-92.0, degrees));
	w -= (distance * floatcos(-a-92.0, degrees));
	return a;
}

stock Float:GetXYInFrontOfPoint(&Float:q, &Float:w, Float:a, Float:distance)
{
	q += (distance * floatsin(-a, degrees));
	w += (distance * floatcos(-a, degrees));
	return a;
}

stock Float:GetXYInTrasOfPoint(&Float:q, &Float:w, Float:a, Float:distance)
{
	q -= (distance * floatsin(-a, degrees));
	w -= (distance * floatcos(-a, degrees));
	return a;
}

stock RGBAToARGB(rgba) {
    return rgba >>> 8 | rgba << 24;
}

stock SplitItem(const info[], itemnome[], &itemtype, &modelid, &quantidade, &cor1, &cor2) {
    new string_inv[8][76];
    split(info, string_inv, '|');

    format(itemnome, 75, string_inv[0]);
    itemtype = strval(string_inv[2]);
    modelid	= strval(string_inv[3]);
    quantidade = strval(string_inv[4]);
    cor1 = strval(string_inv[5]);
    cor2 = strval(string_inv[6]);
}

stock GetPlayerSpeedEx(playerid)
{
	static Float: 
		posS[3];

	GetPlayerVelocity(playerid, posS[0], posS[1], posS[2]);

	return floatround(floatmul(floatsqroot(floatadd(floatpower(posS[0], 2), floatpower(posS[1], 2))), 170.0));
}

stock GetPlayerSpeedSkate(playerid)
{
	new 
		Float:Pos[3], Float:PS;

 	GetPlayerVelocity(playerid, Pos[0], Pos[1], Pos[2]);
  	PS = floatsqroot(Pos[0] * Pos[0] + Pos[1] * Pos[1] + Pos[2] * Pos[2]) * 170;

   	return floatround(PS, floatround_round);
}

stock SetPlayerFaceToPoint(playerid, Float: X, Float: Y)
{
    static
        Float: pX,
        Float: pY,
        Float: oZ;

    GetPlayerPos(playerid, pX, pY, oZ);
    oZ = (floatadd(atan2(floatsub(Y, pY), floatsub(X, pX)), 270.0));
    SetPlayerFacingAngle(playerid, oZ);
}

stock SetPlayerCostasToPoint(playerid, Float: X, Float: Y)
{
    static
        Float: pX,
        Float: pY,
        Float: oZ;

    GetPlayerPos(playerid, pX, pY, oZ);

    oZ = ( floatadd(atan2(floatsub(Y, pY), floatsub(X, pX)), 270.0) );

    SetPlayerFacingAngle(playerid, oZ - 180.0);
}

stock SoundToAll(soundid)
{
	foreach(new p : Player)
	{
	    PlayerPlaySound(p, soundid, 0.0, 0.0, 0.0);
	}
	return 1;
}

stock SoundInRange(soundid, Float:range, Float:x, Float:y, Float:z)
{
	foreach(new p : Player)
	{
	    if(IsPlayerInRangeOfPoint(p, range, x, y, z))
	        PlayerPlaySound(p, soundid, x, y, z);
	}
}

stock emailValido(const email[])
{
	new pontos = 0,
		arroba = 0,
		caract = 0;

	for(new i = 0; i < strlen(email); ++i)
	{
	    if (email[i] == '.' || email[i] == '@' || email[i] == '{' || email[i] == '}')
		{
	        if (email[i] == '.')
				pontos++;

			else if (email[i] == '{' || email[i] == '}') caract++;

	        else arroba ++;
	    }
	}
	if (arroba >= 1 && pontos >= 1) return true;

	if (caract > 0) return false;

	return false;
}

stock SplitColor(str[])
{
    if (strlen(str) >= 8)
    {
        new i, j;

        do
        {
            if(str[i] == '{' && strlen(str[i]) >= 7 && str[i + 7] == '}') //First checking
            {
                for(j = i + 1; j < i + 7; j++)
                {
                    if (!('A' <= str[j] <= 'F' || 'a' <= str[j] <= 'f' || '0' <= str[j] <= '9'))
                    {
                        i += 8;
                        j = -1;
                        break;
                    }
                }
                if (j != -1) strdel(str, i, i + 8);
            }
            else if (str[i] == '}' && i >= 7 && str[i - 7] == '{') i -= 7;
            else i++;
        }
        while(str[i]);
    }
    return true;
}

stock IsPointInLosSantos(Float:x, Float:y) {
    return x >= 67.9620 && x <= 2952.9524 && y >= -2822.1204 && y <= -728.2902;
}

stock Float:GetXYInFrontOfPlayer(playerid, &Float:q, &Float:w, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, q, w, a);
    if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	else GetPlayerFacingAngle(playerid, a);
	q += (distance * floatsin(-a, degrees));
	w += (distance * floatcos(-a, degrees));
	return a;
}

stock Float:GetPointDistanceToPoint(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2)
{
	new Float:x, Float:y, Float:z;
	x = x1 - x2;
	y = y1 - y2;
	z = z1 - z2;
	return floatsqroot( x * x + y * y + z * z );
}

stock IsPlayerNearOfVehicle(playerid, vehicleid, Float:range) {
    new Float:pos[3];
    GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);

    return PlayerToPoint(range, playerid, pos[0], pos[1], pos[2]);
}

stock Float:abs(Float:value) {
	if(value < 0.0) {
		return -value;
	}
	return value;
}

stock HexToInt(const string[])
{
	if (string[0] == 0) 
        return 0;
    
    new i, cur=1, res=0;
    for(i = strlen(string); i > 0; i--) {
        if (string[i-1] < 58) 
            res = res + cur * (string[i-1]-48); 
        else 
            res = res + cur * (string[i-1]-65+10);

        cur = cur*16;
    }
    return res;
}

stock Float:GetCameraDistancePlayers(playerid1, playerid2) {

	new Float:pPos[3];
	GetPlayerPos(playerid1, pPos[0], pPos[1], pPos[2]);

	new Float:distance = GetPlayerDistanceFromPoint(playerid2, pPos[0], pPos[1], pPos[2]);
	return distance;
}

stock OOCNews(COLOR,const string[])
{
	foreach(new i : Player) {
 		if (Player_Logado(i) && !gNoticias[i])
			SendClientMessage(i, COLOR, string);
	}
}

stock SendClientMessageInRange(Float:range, playerid, const message[], color1, color2, color3, color4, color5)
{
	new Float:playerPos[3];
	GetPlayerPos(playerid, playerPos[0], Float:playerPos[1], Float:playerPos[2]);

	foreach(new i : Player)
	{
		if (!BigEar[i])
		{
		    if (GetPlayerVirtualWorld(i) != GetPlayerVirtualWorld(playerid)) continue;

			if (GetPlayerDistanceFromPoint(i, playerPos[0], playerPos[1], playerPos[2]) < range/16) SendClientMessage(i, color1, message);

			else if (GetPlayerDistanceFromPoint(i, playerPos[0], playerPos[1], playerPos[2]) < range/8) SendClientMessage(i, color2, message);

			else if (GetPlayerDistanceFromPoint(i, playerPos[0], playerPos[1], playerPos[2]) < range/4) SendClientMessage(i, color3, message);

			else if (GetPlayerDistanceFromPoint(i, playerPos[0], playerPos[1], playerPos[2]) < range/2) SendClientMessage(i, color4, message);

			else if (GetPlayerDistanceFromPoint(i, playerPos[0], playerPos[1], playerPos[2]) < range) SendClientMessage(i, color5, message);
		}
		else
		{
			SendClientMessage(i, color1, message);
		}
	}
	return true;
}

stock ProxDetectorS(Float:radi, playerid, targetid)
{
    if (GetPlayerState(targetid) == PLAYER_STATE_SPECTATING)
		return false;

	static Float:posx, Float:posy, Float:posz;
	GetPlayerPos(targetid, posx, posy, posz);

	if (IsPlayerInRangeOfPoint(playerid, radi, posx, posy, posz))
		return true;

	return false;
}


stock ProxDetectorActor(Float:radi, playerid, targetid)
{
	static Float:posx, Float:posy, Float:posz;
	GetActorPos(targetid, posx, posy, posz);
	if (IsPlayerInRangeOfPoint(playerid, radi, posx, posy, posz))
	{
		return true;
	}
	return 0;
}

stock getVehicleProxPlayer(playerid, Float:range = 8.500, ignoreid = INVALID_VEHICLE_ID) {

	new playerVehicle  		 = INVALID_VEHICLE_ID;
	new Float:playerDistance = 999999.0;
	new Float:playerVehPos[3];

	for (new vehicleid; vehicleid != MAX_VEHICLES; vehicleid++) {

		if (vehicleid == ignoreid)
			continue;

		GetVehiclePos(vehicleid, playerVehPos[0], playerVehPos[1], playerVehPos[2]);

		new Float:playerDist = GetPlayerDistanceFromPoint(playerid, playerVehPos[0], playerVehPos[1], playerVehPos[2]);

		if (playerDist < playerDistance && playerDist < range) {

			playerDistance = playerDist;
			playerVehicle  = vehicleid;
		}
	}
	return playerVehicle;
}

CALLBACK:PlayerIsDetetive(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == 1 || empregoPlayer2 == 1) return true;

	return false;
}

stock PlayerIsAdvogado(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == 2 || empregoPlayer2 == 2) return true;

	return false;
}

CALLBACK:PlayerIsFabricanteMat(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == 7 || empregoPlayer2 == 7) return true;

	return false;
}

CALLBACK:PlayerIsBandido(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == 8 || empregoPlayer2 == 8) return true;

	return false;
}

CALLBACK:PlayerIsCaminhoneiro(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == 11 || empregoPlayer2 == 11) return true;

	return false;
}

stock PlayerIsGari(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == 26 || empregoPlayer2 == 26) return true;

	return false;
}

stock PlayerIsTaxista(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == ID_JOB_TAXISTA || empregoPlayer2 == ID_JOB_TAXISTA) return true;

	return false;
}

stock PlayerIsMedico(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == ID_JOB_MEDICO || empregoPlayer2 == ID_JOB_MEDICO) return true;

	return false;
}

stock PlayerIsMinerador(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == ID_JOB_MINERADOR || empregoPlayer2 == ID_JOB_MINERADOR) return true;

	return false;
}

stock PlayerIsFazendeiro(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == ID_JOB_FAZENDEIRO || empregoPlayer2 == ID_JOB_FAZENDEIRO) return true;

	return false;
}

stock PlayerIsMecanico(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == ID_JOB_MECANICO || empregoPlayer2 == ID_JOB_MECANICO) return true;

	return false;
}

CALLBACK:PlayerIsDesignInterior(playerid)
{
	new empregoPlayer = Player_GetJob(playerid);
	new empregoPlayer2 = Player_GetJob(playerid, 2);

	if (empregoPlayer == 43 || empregoPlayer2 == 43) return true;

	return false;
}

stock gIniciarRespawn()
{
    for (new i; i < MAX_VEHICLES; ++i)
    {
        if (IsACargaCar(i) || IsVehicleInDetran(i) || IsTruckCarJob(i) || IsTruckTrailerCarJob(i)) 
			continue;

        new bool:pde = true;
        foreach (new p : Player)
        {
            if (GetPlayerVehicleID(p) == i) pde = false;
        }
        if (pde)
        {
            SetVehicleToRespawn(i);
            StopVehicleEngine(i);
            StopVehicleLights(i);
        }
    }
    SendClientMessageToAll(COLOR_YELLOW, "Respawn de veículos: Todos os veículos do servidor foram respawnados.");
}

timer timerStopSound[7000](playerid)
{
    PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
}

//------------------------------------------------------------------------------
stock GetPlayersPerto(playerid) 
{
	new count;

	foreach(new x : Player) {
	    if (x == playerid || GetPlayerState(x) == PLAYER_STATE_SPECTATING) {
	        continue;
	    }
	    if (ProxDetectorS(15.0, playerid, x)) {
	        count++;
	    }
	}
	return count;
}

CALLBACK: showPlayersPerto(playerid) 
{
	if (GetPlayersPerto(playerid) < 1)
		return SendClientMessage(playerid, -1, "Não há ninguém por perto !"), false;

	MEGAString[0] = EOS;

	new string_players[128];
	new listitem;

	strcat(MEGAString, "ID\tNick\tNível\n");

	foreach(new x : Player) {

	    if (x == playerid || GetPlayerState(x) == PLAYER_STATE_SPECTATING) {
	        continue;
	    }
	    if (ProxDetectorS(15.0, playerid, x)) {

	        format(string_players, sizeof string_players, "%d\t%s\t%d\n", x, PlayerName[x], Player_GetNivel(x));
	        strcat(MEGAString, string_players);

			List_SetPlayers(playerid, listitem, x);
	        listitem ++;
	    }
	}
	ShowPlayerDialog(playerid, 7642, DIALOG_STYLE_TABLIST_HEADERS, "Player(s) Próximo(s)", MEGAString, "Negociar", "Fechar");

	return 1;
}

stock split(const strsrc[], strdest[][], delimiter)
{
	new i, li;
	new aNum;
	new len;
	while(i <= strlen(strsrc))
	{
	    if(strsrc[i] == delimiter || i == strlen(strsrc))
		{
	        len = strmid(strdest[aNum], strsrc, li, i, 128);
	        strdest[aNum][len] = 0;
	        li = i+1;
	        aNum++;
		}
		i++;
	}
	return true;
}

// Pegar a posição X Y da esquerda do Skate
Float:GetXYInEsquerdaOfObject(objectid, &Float:q, &Float:w, Float:distance)
{
	new Float:a, Float:x, Float:y;
	GetDynamicObjectPos(objectid, q, w, a);
	GetDynamicObjectPos(objectid, x, y, a);
	q += (distance * floatsin(-a-90.0, degrees));
	w += (distance * floatcos(-a-90.0, degrees));
	return a;
}

stock GetPlayerCameraFront(playerid, &Float:cX, &Float:cY, &Float:cZ)
{
	new Float:FV[3], Float:CPE[3];

	GetPlayerCameraPos(playerid, CPE[0], CPE[1], CPE[2]);

	GetPlayerCameraFrontVector(playerid, FV[0], FV[1], FV[2]);

	cX = CPE[0] + ( FV[0] * 15.0);
	cY = CPE[1] + ( FV[1] * 15.0);
	cZ = CPE[2] + ( FV[2] * 15.0);
}

stock SetPlayerAngulo(playerid, Float:X, Float:Y)
{
    new
        Float: pX,
        Float: pY,
        Float: oZ
    ;
    GetPlayerFacingAngle(playerid, oZ);

    SetDynamicObjectRot(SkateInfo[playerid][s_Skate], 0.0, 0.0, oZ);

    GetPlayerPos(playerid, pX, pY, oZ);

    oZ = ( floatadd(atan2(floatsub(Y, pY), floatsub(X, pX)), 270.0) );

	SetPlayerFacingAngle(playerid, oZ-90.0);
	SkateInfo[playerid][s_Angulo] = oZ-90.0;
}

timer stopMusic[3000](playerid)
{
	if (IsPlayerConnected(playerid)) {
	    PlayerPlaySound(playerid, 1186, 0.0, 0.0, 0.0);
	}
	return true;
}

stock PlaySoundForPlayersInRange(soundid, Float:range, Float:x, Float:y, Float:z) {
	foreach (new i : Player) {
	    if (IsPlayerInRangeOfPoint(i, range, x, y, z))
		    PlayerPlaySound(i, soundid, x, y, z);
	}
}

stock Sound(playerid, soundid, Float:range, forplayerid = INVALID_PLAYER_ID)
{
	new Float: sPOS[3];
	GetPlayerPos(playerid, sPOS[0], sPOS[1], sPOS[2]);
	if(forplayerid == INVALID_PLAYER_ID)
	{
	    foreach(new i : Player)
	    {
		    if(IsPlayerInRangeOfPoint(i, range, sPOS[0], sPOS[1], sPOS[2]))
		    {
		        PlayerPlaySound(i, soundid, sPOS[0], sPOS[1], sPOS[2]);
			}
		}
	}
	else
	{
 		if(IsPlayerInRangeOfPoint(forplayerid, range, sPOS[0], sPOS[1], sPOS[2]))
   		{
     		PlayerPlaySound(forplayerid, soundid, sPOS[0], sPOS[1], sPOS[2]);
		}
	}
	return false;
}

new timerESC[MAX_PLAYERS];

stock GetPlayerEscTime(playerid)
{
	new tempoafk = (gettime() - timerESC[playerid]);

	return tempoafk;
}

stock IsPlayerESC(playerid)
{
	new tempoafk = (gettime() - timerESC[playerid]);

	if (tempoafk > 5) return true;

	return false;
}

stock getPingText(playerid)
{
	new returnString[24];

	new playerPing2 = GetPlayerPing(playerid);

	switch(playerPing2)
	{
        case 100..199:format(returnString, sizeof returnString, "{00FF00}%d", playerPing2);
        case 200..299:format(returnString, sizeof returnString, "{FFFF00}%d", playerPing2);
		case 300..399:format(returnString, sizeof returnString, "{FFAF00}%d", playerPing2);
        case 400..5000:format(returnString, sizeof returnString, "{FF0000}%d", playerPing2);
		default:format(returnString, sizeof returnString, "{00FF00}%d", playerPing2);
	}
	return returnString;
}

stock PlayerIsNickValid(const name[])
{
    new len_nick = strlen(name);

    if (len_nick >= MAX_PLAYER_NAME or len_nick < 5) return false;

    for(new nameplayer; nameplayer < len_nick; nameplayer++)
	{
        if (name[nameplayer] == '.') continue;

		switch(name[nameplayer])
		{
		    case 'a' .. 'z': return true;
		    case 'A' .. 'Z': return true;
		    case '0' .. '9': return true;
		    case '[' .. ']': return true;
		    case '_': 		 return true;
		    default:         return false;
		}
    }
    return false;
}

stock Float:getPlayerKD(playerid) 
{
	new Float:pkills = Player_GetKills(playerid),
	    Float:pdeaths = Player_GetDeaths(playerid);

	return (pkills / pdeaths);
}

// -----------------------------------------------------
// Sistema de congelar o jogador
#include <freeze-player>