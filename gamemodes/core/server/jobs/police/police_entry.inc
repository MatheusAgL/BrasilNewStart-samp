
#define		MAX_VALID_SU				    24					
#define		MAX_SIZE_SU_DESCRIPTION			65

enum SuValidos
{
	SuTag[7],
	SuDesc[MAX_SIZE_SU_DESCRIPTION],
}

new CrimesValidos[MAX_VALID_SU][SuValidos] =
{
	{"TH", "\tTentativa de Homicidio, Art. 121�"},
	{"DOP", "\tDesobedi�ncia a ordem Policial, Art. 195�"},
	{"VAN", "\tAto de Vandalismo, Art. 1�"},
	{"CUM", "\tC�mplice, Art. 180�"},
	{"SEQ", "\tSequestro, Art. 148�"},
	{"RV", "\tRoubo de ve�culo, Art. 157�"},
	{"FLA", "\tFlagrante, Art. 302�"},
	{"DROGAS", "Portando Drogas, Art. 28�"},
	{"PIA", "\tPorte Ilegal de Armas, Art. 14�"},
	{"RP", "\tResist�ncia a pris�o, Art. 282�"},
	{"DP", "\tDire��o Perigosa, Art. 34�"},
	{"DES", "\tDesacato, Art. 331�"},
	{"FUGA", "\tFuga, Art. 351�"},
	{"TE", "\tTr�fico de Entorpecentes, Art. 33�"},
	{"AGR", "\tAgress�o, Art. 129�"},
	{"AM", "\tAmea�a, Art. 147�"},
	{"SUB", "\tSuborno, Art. 333�"},
	{"INV", "\tInvas�o, Art. 150�"},
	{"AMA", "\tAssalto a m�o armada, Art. 157�"},
	{"RACHA", "Ato de Praticar Racha, Art. 308�"},
	{"TROTE", "\tTrotes contra autoridades, Art. 340�"},
	{"FB", "Furo de bloqueio, Art. 210�"},
	{"COR", "\tCorrup��o"},
	{"PDD", "\tPorte de Dinamites, Art. 14�"}
};

new removeWantedPoints[MAX_PLAYERS];
