
#define		MAX_VALID_SU				    24					
#define		MAX_SIZE_SU_DESCRIPTION			65

enum SuValidos
{
	SuTag[7],
	SuDesc[MAX_SIZE_SU_DESCRIPTION],
}

new CrimesValidos[MAX_VALID_SU][SuValidos] =
{
	{"TH", "\tTentativa de Homicidio, Art. 121º"},
	{"DOP", "\tDesobediência a ordem Policial, Art. 195º"},
	{"VAN", "\tAto de Vandalismo, Art. 1º"},
	{"CUM", "\tCúmplice, Art. 180º"},
	{"SEQ", "\tSequestro, Art. 148º"},
	{"RV", "\tRoubo de veículo, Art. 157º"},
	{"FLA", "\tFlagrante, Art. 302º"},
	{"DROGAS", "Portando Drogas, Art. 28º"},
	{"PIA", "\tPorte Ilegal de Armas, Art. 14º"},
	{"RP", "\tResistência a prisão, Art. 282º"},
	{"DP", "\tDireção Perigosa, Art. 34º"},
	{"DES", "\tDesacato, Art. 331º"},
	{"FUGA", "\tFuga, Art. 351º"},
	{"TE", "\tTráfico de Entorpecentes, Art. 33º"},
	{"AGR", "\tAgressão, Art. 129º"},
	{"AM", "\tAmeaça, Art. 147º"},
	{"SUB", "\tSuborno, Art. 333º"},
	{"INV", "\tInvasão, Art. 150º"},
	{"AMA", "\tAssalto a mão armada, Art. 157º"},
	{"RACHA", "Ato de Praticar Racha, Art. 308º"},
	{"TROTE", "\tTrotes contra autoridades, Art. 340º"},
	{"FB", "Furo de bloqueio, Art. 210º"},
	{"COR", "\tCorrupção"},
	{"PDD", "\tPorte de Dinamites, Art. 14º"}
};

new removeWantedPoints[MAX_PLAYERS];
