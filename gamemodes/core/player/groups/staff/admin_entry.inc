// Cores do módulo
#define         COLOR_ADMIN             0xFF38C5AA
#define         C_ADMIN                 "{FF38C5}"
#define         C_ADMIND                "{C52597}"
#define         COLOR_REPORT      		0xFC6161FF
#define         COLOR_ATENDIMENTO       0xFFCCCCFF

enum AdminNivel: {
    NOT_ADMIN               = 0,
    ESTAGIARIO              = 1,
    MODERADOR               = 2,
    ADMINISTRADOR           = 3,
    ENCARREGADO             = 4,
    SUPERVISOR              = 5,
    MASTER                  = 1337,
    GERENTE                 = 1338,
    DIRETOR                 = 1339,
    SUB_DONO                = 3000,
    DONO                    = 3001,
    BETA_TESTER             = 3002,
    DESENVOLVEDOR           = 3003,
    CO_FUNDADOR             = 3004,
    FUNDADOR                = 3005,
    PROGRAMADOR             = 5000,
};

enum ENUM_STAFF 
{
    AdminNivel:staffNivel,
    staffFunction[54],
    bool:staffWorking,
    bool:staffSecret,
    bool:staffAFK,
    staffAFKReason[21],

    // Espionagem --
    bool:sSpy_Par,
    bool:sSpy_Msg,
    bool:sSpy_ChatLocal,
};
static StaffInfo[MAX_PLAYERS][ENUM_STAFF];
static AdminNivel:staffNivelRemove[MAX_PLAYERS];

new PlayerText:spectadorText[MAX_PLAYERS];
new SenhaAdministracao[129];

stock Admin_SetNivel(playerid, AdminNivel:nivel) {
    StaffInfo[playerid][staffNivel] = nivel;

    if (nivel < ESTAGIARIO)
        SetCountAdmin(CountAdmin() - 1);
    else
        SetCountAdmin(CountAdmin() + 1);
}

// Nível e função
stock AdminNivel:Admin_GetNivel(playerid)
    return StaffInfo[playerid][staffNivel];

stock Staff_SetFunction(playerid, const function[])
    format(StaffInfo[playerid][staffFunction], 54, function);

stock Staff_GetFunction(playerid)
{
    new function[54];
    format(function, sizeof(function), StaffInfo[playerid][staffFunction]);
    return function;
}

// Senha admin (proteção)
stock Admin_SetRemoveNivel(playerid, AdminNivel:nivel)
    staffNivelRemove[playerid] = nivel;

stock AdminNivel:Admin_GetRemoveNivel(playerid)
    return staffNivelRemove[playerid];

// Modo trabalho e modo secreto
stock Staff_SetSecret(playerid, bool:stats)
    StaffInfo[playerid][staffSecret] = stats;

stock bool:Staff_GetSecret(playerid)
    return StaffInfo[playerid][staffSecret];

stock Staff_SetWorking(playerid, bool:stats)
    StaffInfo[playerid][staffWorking] = stats;

stock bool:Staff_GetWorking(playerid)
    return StaffInfo[playerid][staffWorking];

// AFK
stock Staff_SetAFK(playerid, bool:stats)
    StaffInfo[playerid][staffAFK] = stats;

stock bool:Staff_GetAFK(playerid)
    return StaffInfo[playerid][staffAFK];

stock Staff_SetReasonAFK(playerid, const reason[])
    format(StaffInfo[playerid][staffAFKReason], 21, reason);

stock Staff_GetReasonAFK(playerid)
{
    new reason[21];
    format(reason, sizeof(reason), StaffInfo[playerid][staffAFKReason]);
    return reason;
}

// --------------------------------
stock Admin_GetPositionName(AdminNivel:nivel, sex = MASCULINO) {
	new positionName[25];

	switch(nivel)
	{
		case ESTAGIARIO:				positionName = (sex == MASCULINO ? "Estagiário" : "Estagiária");
        case MODERADOR:					positionName = (sex == MASCULINO ? "Moderador" : "Moderadora");
        case ADMINISTRADOR:				positionName = (sex == MASCULINO ? "Administrador" : "Administradora");
        case ENCARREGADO:				positionName = (sex == MASCULINO ? "Encarregado" : "Encarregada");
        case SUPERVISOR:				positionName = (sex == MASCULINO ? "Supervisor" : "Supervisora");
        case MASTER:					positionName = (sex == MASCULINO ? "Coordenador" : "Coordenadora");
        case GERENTE:					positionName = (sex == MASCULINO ? "Gerente" : "Gerente");
        case DIRETOR:					positionName = (sex == MASCULINO ? "Diretor" : "Diretora");
        case SUB_DONO:					positionName = (sex == MASCULINO ? "Sub-Dono" : "Sub-Dona");
        case DONO:						positionName = (sex == MASCULINO ? "Dono" : "Dona");
        case BETA_TESTER:				positionName = (sex == MASCULINO ? "Beta Tester" : "Beta Tester");
        case DESENVOLVEDOR:				positionName = (sex == MASCULINO ? "Desenvolvedor" : "Desenvolvedora");
        case CO_FUNDADOR:				positionName = (sex == MASCULINO ? "Co-Fundador" : "Co-Fundadora");
        case FUNDADOR:					positionName = (sex == MASCULINO ? "Fundador" : "Fundadora");
        case PROGRAMADOR:				positionName = (sex == MASCULINO ? "Programador" : "Programadora");
        default:						positionName = (sex == MASCULINO ? "Nenhum" : "Nenhum");
	}
	return positionName;
}

// ---------------------------------------
// Seção: Spy's

// Particulares
stock SpySet_Particulares(playerid, bool:stats)
    StaffInfo[playerid][sSpy_Par] = stats;

stock SpyGet_Particulares(playerid)
    return StaffInfo[playerid][sSpy_Par];

// Espiar Mensagens
stock SpySet_Messages(playerid, bool:stats)
    StaffInfo[playerid][sSpy_Msg] = stats;

stock SpyGet_Messages(playerid)
    return StaffInfo[playerid][sSpy_Msg];

// Espial Chat Local
stock SpySet_ChatLocal(playerid, bool:stats)
    StaffInfo[playerid][sSpy_ChatLocal] = stats;

stock SpyGet_ChatLocal(playerid)
    return StaffInfo[playerid][sSpy_ChatLocal];

// ---------------------------------------
//    LOG_chat (true/false (/logchat))
enum A_ENUM {
    bool:LOG_chat
};
static AdminConfig[A_ENUM];

stock Admin_GetLogChat()
    return AdminConfig[LOG_chat];

stock Admin_SetLogChat(bool: status)
    AdminConfig[LOG_chat] = status;

// ---------------------------------------
// Contar administrador
static countAdmin;

stock SetCountAdmin(value)
    countAdmin = value;

stock CountAdmin()
    return countAdmin;

// ------------------------------------
// Atendimentos
enum ENUM_ATTENDANCE
{
	bool:attendanceValid,
	attendancePlayer = INVALID_PLAYER_ID,
	attendanceTimer,
	attendanceReason[32],
}
static AttendanceInfo[MAX_PLAYERS][ENUM_ATTENDANCE];

// Valid
stock Attendance_SetValid(playerid, bool:stats)
	AttendanceInfo[playerid][attendanceValid] = stats;

stock bool:Attendance_GetValid(playerid)
	return AttendanceInfo[playerid][attendanceValid];

// Player
stock Attendance_SetPlayer(playerid, giveplayerid)
	AttendanceInfo[playerid][attendancePlayer] = giveplayerid;

stock Attendance_GetPlayer(playerid)
	return AttendanceInfo[playerid][attendancePlayer];

// Timer
stock Attendance_SetTimer(playerid, timer)
	AttendanceInfo[playerid][attendanceTimer] = timer;

stock Attendance_GetTimer(playerid)
	return AttendanceInfo[playerid][attendanceTimer];

// Reason
stock Attendance_GetReason(playerid)
{
    new reason[32];
	format(reason, sizeof(reason), AttendanceInfo[playerid][attendanceReason]);
    return reason;
}

stock Attendance_SetReason(playerid, const reason[])
	format(AttendanceInfo[playerid][attendanceReason], 32, reason);

// ------------------------------------
// Report's
enum ENUM_REPORTS
{
	bool:reportValid,
	reportPlayer,
	reportAccused,
	reportTimer,
	reportReason[32],
}
new ReportInfo[MAX_PLAYERS][ENUM_REPORTS];

// Valid
stock Report_SetValid(playerid, bool:stats)
	ReportInfo[playerid][reportValid] = stats;

stock bool:Report_GetValid(playerid)
	return ReportInfo[playerid][reportValid];

// Player
stock Report_SetPlayer(playerid, giveplayerid)
	ReportInfo[playerid][reportPlayer] = giveplayerid;

stock Report_GetPlayer(playerid)
	return ReportInfo[playerid][reportPlayer];

// Accused
stock Report_SetAccused(playerid, giveplayerid)
	ReportInfo[playerid][reportAccused] = giveplayerid;

stock Report_GetAccused(playerid)
	return ReportInfo[playerid][reportAccused];

// Timer
stock Report_SetTimer(playerid, timer)
	ReportInfo[playerid][reportTimer] = timer;

stock Report_GetTimer(playerid)
	return ReportInfo[playerid][reportTimer];

// Reason
stock Report_SetReason(playerid, const reason[])
	format(ReportInfo[playerid][reportReason], 32, reason);

// Reason
stock Report_GetReason(playerid)
{
    new reason[32];
	format(reason, sizeof(reason), ReportInfo[playerid][reportReason]);
    return reason;
}

// ------------------------------------