#include <YSI_Coding\y_hooks>

stock TimestampToRemainingDays(Timestamp:ts)
    return _:((ts - Now()) / Seconds:DayInSeconds);

stock TimestampToFormat(const data[]) {
	new Timestamp:timestamp, result[30];
	TimeParse(data, MYSQL_TIMESTAMP, timestamp);
	TimeFormat(timestamp, TIMESTAMP_FORMAT, result);
	return result;
}

// ----------------------------------------------

static 
    _day,
    _month,
    _year,
    _hour,
    _minute,
    _second
;

enum DateOutput {
    ONLY_CURRENT_HOUR,
	ONLY_CURRENT_HOUR_NSEC,
    ONLY_CURRENT_DATE,
    ONLY_CURRENT_ALL,
	BR_CURRENT_ALL,
	ONLY_CURRENT_DATE_MYSQL
};

stock GetCurrentDay() {
    getdate(_year, _month, _day);
    return _day;
}

stock GetCurrentMonth() {
    getdate(_year, _month, _day);
    return _month;
}

stock GetCurrentYear() {
    getdate(_year, _month, _day);
    return _year;
}

stock GetCurrentHour() {
    gettime(_hour, _minute, _second);
    return _hour;
}

stock GetCurrentMinute() {
    gettime(_hour, _minute, _second);
    return _minute;
}

stock GetCurrentSecond() {
    gettime(_hour, _minute, _second);
    return _second;
}

stock GetCurrentDateHour(DateOutput: output) 
{
    static str[14 + 13 + 4];

    switch(output) {
        case ONLY_CURRENT_HOUR: {
            gettime(_hour, _minute, _second);
            format(str, sizeof(str), "%02d:%02d:%02d", _hour, _minute, _second);
        }
        case ONLY_CURRENT_DATE: {
            getdate(_year, _month, _day);
            format(str, sizeof(str), "%02d/%02d/%d", _year, _month, _day);
        }
        case ONLY_CURRENT_ALL: {
            getdate(_year, _month, _day);
            gettime(_hour, _minute, _second);
            format(str, sizeof(str), "%04d-%02d-%02d %02d:%02d:%02d", _year, _month, _day, _hour, _minute, _second);
        }
		case ONLY_CURRENT_HOUR_NSEC: {
            gettime(_hour, _minute, _second);
            format(str, sizeof(str), "%02d:%02d", _hour, _minute);
        }
		case BR_CURRENT_ALL: {
			getdate(_year, _month, _day);
            gettime(_hour, _minute, _second);
            format(str, sizeof(str), "%02d/%02d/%04d %02d:%02d:%02d", _day, _month, _year, _hour, _minute, _second);
		}
		case ONLY_CURRENT_DATE_MYSQL: {
            getdate(_year, _month, _day);
            format(str, sizeof(str), "%04d-%02d-%02d", _year, _month, _day);
        }
    }
    return str;
}

stock GetWeekName(const PT_Dia, const PT_Mes, const PT_Ano)
{
    new PT_A = (14 - PT_Mes) / 12, PT_B = PT_Ano - PT_A, PT_C = (PT_Mes + (12 * PT_A)) - 2, 
        PT_D = (((((PT_Dia + ((31 * PT_C) / 12)) + PT_B) + (PT_B / 4)) - (PT_B / 100)) + (PT_B / 400)), PT_E = PT_D % 7;

    static const _week[7][14] = { 
		"Domingo", 
        "Segunda-Feira", 
        "Terca-Feira", 
        "Quarta-Feira", 
        "Quinta-Feira", 
        "Sexta-Feira", 
        "Sabado" 
	};
    return _week[PT_E];
}

// ------------------------------------------------------------
// Feriados:

static 
	bool:isHoliday,
	nameHoliday[40];

stock Holiday_Get() {
	return isHoliday;
}

stock Holiday_Set(const name[], bool:stats) {
	format(nameHoliday, sizeof(nameHoliday), name);
	isHoliday = stats;
}

stock Holiday_GetName() {
	new name[40];
	format(nameHoliday, sizeof(nameHoliday), name);
	return name;
}

CALLBACK: OnResetDay() 
{
	// Checa se hoje é feriado.
	CheckFeriado();

	// Checar as propriedades com donos inativos.
	Checkproop();
}

hook OnGameModeInit() {
	SetSVarInt("Restarting", 0);
	OnServer_SetClima();

	return 1;
}

stock GetMonthName(month) {
    static str_month[11];

    switch (month) {
		case 1: str_month = "Janeiro";
		case 2: str_month = "Fevereiro";
		case 3: str_month = "Marco";
		case 4: str_month = "Abril";
		case 5: str_month = "Maio";
		case 6: str_month = "Junho";
		case 7: str_month = "Julho";
		case 8: str_month = "Agosto";
		case 9: str_month = "Setembro";
		case 10: str_month = "Outubro";
		case 11: str_month = "Novembro";
		case 12: str_month = "Dezembro";
		default: str_month = "-";
	}
    return str_month;
}

CALLBACK: OnTimeUpdate() {

	// PayDay horário
	if (GetCurrentMinute() == 0 && GetCurrentSecond() == 0)
		PayDay();

	switch (GetCurrentMinute()) {
		case 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60: {
			if (GetCurrentSecond() < 1) {
				OnServer_SetClima();
			}
		}
	}

	// Meia-noite;
	if (GetCurrentHour() == 0 && GetCurrentMinute() == 0 && GetCurrentSecond() == 0)
		OnResetDay();

	// Anúncios pré-definidos;
	switch (GetCurrentMinute()) {
		case 15, 19: {
			if (eventoAleatorio) {
				if (GetCurrentSecond() == 0)
					SendMsgAllF(-1, "[{F9E36C}EVENTO ALEATÓRIO{FFFFFF}] Em %d minutos inicia um evento aleatório.", (20 - GetCurrentMinute()), getFormatText(LotValue));
			}
		}
		case 20: {
			if (eventoAleatorio) {
				new chance = random(5);

				// Inicia evento se cair 1 ou 3
				if (chance % 2 == 1)
					EVENT_Start_Random();
			}
		}
		case 55, 58, 59: 
		{
	    	if (GetCurrentSecond() == 0) {
				SendMsgAllF(-1, "[{F9E36C}LOTÉRICA{FFFFFF}]: O sorteio iniciará em %d minutos. Prêmio acumulado: {00AA00}$%s", (60 - GetCurrentMinute()), getFormatText(LotValue));
			}
 		}
	}

	// GMX automático
	if (gmxAutomatico) {
		if (GetCurrentHour() == HORA_GMX_AUTOMATICO-1 && GetCurrentSecond() == 0) {
			if (GetCurrentMinute() % 15 == 0 || GetCurrentMinute() >= 55) {
				SendMsgAllF(-1, "[{F9E36C}GMX Diário{FFFFFF}] O servidor será reiniciado automaticamente daqui a %d minutos, exatamente às %02d:00. Prepare-se!", (60 - GetCurrentMinute()), HORA_GMX_AUTOMATICO);
			}
		}
		else if (GetCurrentHour() == HORA_GMX_AUTOMATICO && GetCurrentMinute() == 0 && GetCurrentSecond() <= 4 && !GetSVarInt("Restarting")) {
			GMX("Automático", "GMX para atualização diária.");
		}
	}

	// Guerra no morro;
	switch (GetCurrentHour()) {
		case 13, 18, 21: {

			// Guerra morro
			if (GetCurrentMinute() == 5 && GetCurrentSecond() == 0)
				SendMsgAllF(COLOR_YELLOW, "[Guerra no Morro]: Faltam apenas %d minutos para começar.", (GetCurrentMinute()));

			if (GetCurrentMinute() == 10 && GetCurrentSecond() == 0)
				gIniciarGuerraMorro();
		}
		case 9, 15: {

			// Guerra morro
			if (GetCurrentMinute() == 25 && GetCurrentSecond() == 0)
				SendMsgAllF(COLOR_YELLOW, "[Guerra no Morro]: Faltam apenas %d minutos para começar.", (30 - GetCurrentMinute()));

			if (GetCurrentMinute() == 30 && GetCurrentSecond() == 0)
				gIniciarGuerraMorro();
		}
	}
}

task _date_update[1000]() {
	OnTimeUpdate();
}

stock OnServer_SetClima()
{
	switch (GetCurrentHour()) {
		case 17: {
			SetWorldTime(23);
		}
		case 18..23: {
			SetWorldTime(0);
		}
		default: {
			SetWorldTime(GetCurrentHour());
		}
	}
	SetWeather(1);
}

stock CheckFeriado() {
	switch (GetCurrentMonth()) {
		case 1: {
			if (GetCurrentDay() == 1) {
				new string[40];
				format(string, sizeof(string), "Ano novo! Feliz ano novo %d!", GetCurrentYear());
				Holiday_Set(string, true);
			}
		}
		case 3: {
			if (GetCurrentDay() == 1) {
				Holiday_Set("Carnaval", true);
			}
			if (GetCurrentDay() == 2) {
				Holiday_Set("Quarta-feira de cinzas", true);
			}
			if (GetCurrentDay() == 8) {
				Holiday_Set("Dia internacional da mulher", true);
			}
			if (GetCurrentDay() == 20) {
				Holiday_Set("Inicio do outono", true);
			}
		}
		case 4: {
			if (GetCurrentDay() == 10) {
				Holiday_Set("Domingo de Ramos", true);
			}
			if (GetCurrentDay() == 14) {
				Holiday_Set("Quinta-feira Santa", true);
			}
			if (GetCurrentDay() == 15) {
				Holiday_Set("Sexta-feira Santa", true);
			}
			if (GetCurrentDay() == 16) {
				Holiday_Set("Sábado de Aleluia", true);
			}
			if (GetCurrentDay() == 17) {
				Holiday_Set("Páscoa", true);
			}
			if (GetCurrentDay() == 19) {
				Holiday_Set("Dia do Índio", true);
			}
			if (GetCurrentDay() == 21) {
				Holiday_Set("Tiradentes", true);
			}
			if (GetCurrentDay() == 22) {
				Holiday_Set("Descobrimento do Brasil", true);
			}
			if (GetCurrentDay() == 25) {
				Holiday_Set("Dia da Liberdade em Portugal", true);
			}
		}
		case 5: {
			if (GetCurrentDay() == 1) {
				Holiday_Set("Dia do Trabalho", true);
			}
			if (GetCurrentDay() == 8) {
				Holiday_Set("Dia das mães", true);
			}
		}
		case 6: {
			if (GetCurrentDay() == 10) {
				Holiday_Set("Dia de Portugal", true);
			}
			if (GetCurrentDay() == 12) {
				Holiday_Set("Dia dos Namorados", true);
			}
			if (GetCurrentDay() == 16) {
				Holiday_Set("Corpus Christi", true);
			}
			if (GetCurrentDay() == 21) {
				Holiday_Set("Início do Inverno", true);
			}
			if (GetCurrentDay() == 24) {
				Holiday_Set("Dia de São João", true);
			}
		}
		case 7: {
			if (GetCurrentDay() == 9) {
				Holiday_Set("Dia da Revolução Constitucionalista", true);
			}
			if (GetCurrentDay() == 20) {
				Holiday_Set("Dia do Amigo e Internacional da Amizade", true);
			}
		}
		case 8: {
			if (GetCurrentDay() == 14) {
				Holiday_Set("Dia dos Pais", true);
			}
			if (GetCurrentDay() == 22) {
				Holiday_Set("Dia do Folclore", true);
			}
			if (GetCurrentDay() == 25) {
				Holiday_Set("Dia do Soldado", true);
			}
		}
		case 9: {
			if (GetCurrentDay() == 9) {
				Holiday_Set("Dia da Independência do Brasil", true);
			}
			if (GetCurrentDay() == 20) {
				Holiday_Set("Dia da Árvore", true);
			}
			if (GetCurrentDay() == 20) {
				Holiday_Set("Início da Primavera", true);
			}
		}
		case 10: {
			if (GetCurrentDay() == 12) {
				Holiday_Set("Dia das Crianças", true);
			}
			if (GetCurrentDay() == 28) {
				Holiday_Set("Dia do Servidor Público", true);
			}
			if (GetCurrentDay() == 31) {
				Holiday_Set("Dia das Bruxas - Halloween", true);
			}
		}
		case 11: {
			if (GetCurrentDay() == 1) {
				Holiday_Set("Dia de Todos os Santos", true);
			}
			if (GetCurrentDay() == 2) {
				Holiday_Set("Finados", true);
			}
			if (GetCurrentDay() == 15) {
				Holiday_Set("Proclamação da República", true);
			}
			if (GetCurrentDay() == 19) {
				Holiday_Set("Dia da Bandeira", true);
			}
			if (GetCurrentDay() == 20) {
				Holiday_Set("Dia Nascional da Consciência Negra", true);
			}
		}
		case 12: {
			if (GetCurrentDay() == 21) {
				Holiday_Set("Início do Verão", true);
			}
			if (GetCurrentDay() == 24) {
				Holiday_Set("Véspera de Natal", true);
			}
			if (GetCurrentDay() == 25) {
				Holiday_Set("Natal", true);
			}
			if (GetCurrentDay() == 31) {
				Holiday_Set("Véspera de Ano Novo", true);
			}
		}
		default: {
			Holiday_Set("", false);
		}
	}
}