/*  ----------------------------------------------------------------------------------------------------------------------------------------

        Sistema de eventos
                            v0.63
                            Theus_Crazzy (wearLyS)

 ----------------------------------------------------------------------------------------------------------------------------------------- */

#include <YSI_Coding\y_hooks>

// ---------------------------------------------------------------------------------
// Include <samp-random-events>

#if defined _INC_samp_random_event
	#if INC_samp_random_event_version < (5)
		#error Install version 5 or greater of the <samp-random-events> library
	#else
		#if !defined QUIZ_EVENT
			#define QUIZ_EVENT true
			#define QUIZ_EVENT_ID 3
			#define COLOR_QUIZ_EVENT 0xFFF000AA
		#endif
	#endif
#endif

// ---------------------------------------------------------------------------------

enum quizEnum
{
    question[128],
    answers[128]
};

new QUIZ_QUESTION;

new QUIZ_Event[][quizEnum] = 
{
	{ "Qual clube de futebol foi o campeão mundial de 2004?", "Porto" },
	{ "O que significa a sigla ROTA?", "Rondas Ostensivas Tobias de Aguiar" },
	{ "Qual país que descobriu o Brasil?", "Portugal" },
	{ "Qual é o jogo mais popular do mundo em 2023?", "Minecraft" },
	{ "Qual é o maior estado do Brasil?", "Amazonas" },
    { "Qual é o estado mais rico dos Estados Unidos da América?", "California" },
    { "Qual é a cidade mais populosa da América do Sul?", "São Paulo" },
    { "Em que ano começou a guerra da Cisplatina?", "1825" },
    { "Qual era o nome da união de Portugal e Brasil antes da Independência do Brasil?", "Reino Unido de Portugal, Brasil e Algarves" },
    { "Qual é a aliança militar mais antiga do mundo?", "Aliança Anglo-Portuguesa" },
    { "Qual é o jogo famoso que tem criatividade de construção?", "Roblox" },
    { "Qual é o quarto distrito mais populoso de Portugal?", "Braga" },
    { "Quem é o criador do servidor?", FOUNDER_NAME_01 },
    { "Quem é o desenvolvedor da GameMode?", "Theus_Crazzy" },
    { "Que grupo resolve as coisas mais importantes do servidor?", "Conselho" },
    { "Qual é a capital do estado do Paraná?", "Curitiba" },
    { "Qual foi o primeiro Império colonial do mundo?", "Império Português" },
    { "Aonde foi sediado a Copa do Mundo de 2018?", "Rússia" },
    { "Com quantas horas jogadas você precisa para usar o /noob?", "3" },
    { "Qual era o nome antigo da organização P.C.C?", "Seville Boulevard" },
    { "Qual é a capital do estado do Amazonas?", "Manaus" },
    { "Quem era a antiga responsável pela equipe de desenvolvimento?", "KatarinaJensen" },
    { "Em que ano foi proclamado a República no Brasil?", "1889" },
    { "Qual é o nome da mesma família real do Brasil e Portugal?", "Bragança" },
    { "Aonde foi inventado a Pizza?", "Itália" },
    { "Qual é o país da África que é tem o menor IDH?", "Sudão do Sul" },
    { "Em que ano foi fundado a comunidade da Austrália?", "1901" },
    { "Qual é a península que Portugal e Espanha estão localizados?", "Península Ibérica" },
    { "Em que ano a história do "SERVER_NAME" começou?", SERVER_YEAR_FOUNDED },
    { "Qual foi o Presidente que ganhou o Prêmio Nobel da Paz de 1993?", "Nelson Mandela" },
    { "O que significa BTC?", "Bitcoin" },
    { "Qual foi o primeiro-ministro que governou o Reino Unido durante a Segunda Guerra Mundial?", "Winston Churchill" },
    { "Quantos dias tem um ano civil?", "365 dias" },
    { "Qual é a linguagem de programação mais usada e solicitada?", "Java" },
    { "Qual é o nome da Inteligência Artificial usada para pedir muita ajuda?", "ChatGPT" },
    { "Em que ano foi fundado o WhatsApp?", "2009" }
};

hook OnPlayerText(playerid, text[])
{
	new string[128];

	if (EVENT[ev_started] && EVENT[ev_type] == QUIZ_EVENT_ID)
	{
        if (strlen(text) > 50) return 1;

        if (strdistance(QUIZ_Event[QUIZ_QUESTION][answers], text) < 5)
        {
            if (gettime() < GetPVarInt(playerid, #varFloodRespostas))
                return SendClientMessage(playerid, -1, "Vá com calma! Você não é o Einstem... Responda sem robos...");

            SetPVarInt(playerid, #varFloodRespostas, gettime() + 2);

            EVENT[ev_score][playerid]++;
            EVENT[ev_bonus][playerid] += 1500;

            SendMsgAllF(EVENT[ev_color], "[EVENTO QUIZ]: {FFFFFF}%s acertou a resposta, {FFFFFF}adicionado {00AA00}+$1500", PlayerName[playerid]);

            PlayerTextDrawChangeString(string, playerid, "%s", event_ptextdraw[0][playerid], PlayerName[playerid]);
            PlayerTextDrawChangeString(string, playerid, "%d acertos", event_ptextdraw[1][playerid], EVENT[ev_score][playerid]);

            EVENT_UpdateRanks();

            QUIZ_QUESTION = random(sizeof(QUIZ_Event));
		    SendMsgAllF(EVENT[ev_color], "[EVENTO QUIZ]: {00FF00}%s", QUIZ_Event[QUIZ_QUESTION][question]);

            return 0;
        }
	}
	return 1;
}