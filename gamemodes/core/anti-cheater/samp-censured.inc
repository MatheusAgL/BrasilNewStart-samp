/*
    Sistema de censura, palavr�es e divulga��o

    �ltima modifica��o: 12/05/2021
    Respons�vel: Theus_Crazzy
*/

#define			_CENSORED_protection		true // Use 'false' para desativar a censura dos palavr�es e divulga��o


stock const palavroes_string[51][20] =
{
	"macaco",
	"preto fodido",
	"chupa rola",
	"vagabundo",
	"vagabunda",
	"lixoso",
	" c� ",
	"capeta",
	"diabo",
	"satanas",
	"criolo",
	"seu preto",
	"preto fedido",
	"preto de merda",
	"� preto",
	"homossexual",
	"viad�o",
	"boiola",
	"bixinha",
	"queima rosca",
	"verme",
	"ordinario",
	"ordin�rio",
	"porra",
	"fdp",
	"retardado",
	"demente",
	"cuz�o",
	"cuzao",
	"viadinho",
	"gay",
	"fuder",
	"puta",
	"vadia",
	"deficiente",
	"corno",
	"sh0x",
	"shox",
	"brasilplayshox",
	"s.h.o.x",
	"s hox",
	"sh ox",
	"brasilplayvicio",
	"playvicio",
	"newstyle",
	"new style",
	"play vicio",
	"brasilnewstyle",
	":7777",
	"ip.",
	"sv1.",
	"br.sv",
	"f.d.p"
};

stock censored_word_detected(censored_string[]) {
	for(new len; len < sizeof(palavroes_string); len++) {
		strreplace(censored_string, palavroes_string[len], "bobba", true, 0, -1, 128);
	}
}
