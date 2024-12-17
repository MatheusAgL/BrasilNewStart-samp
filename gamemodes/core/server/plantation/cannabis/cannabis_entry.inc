
#define MAX_SERVER_CANNABIS     (500)
#define MAX_PLAYER_CANNABIS     (10)
#define TIME_UPDATE_ERVA        (30 * 60)     // em minutos, atual: 30 minuto(s)

enum {
	ERVA_STAGE_SEMENTE,
	ERVA_STAGE_PEQUENA,
	ERVA_STAGE_MEDIA,
	ERVA_STAGE_GRANDE,
	ERVA_STAGE_SECA,
	ERVA_STAGE_DESTROY,
}

enum e_cannabis {
	erva_owner[MAX_PLAYER_NAME],
	Float: erva_x,
	Float: erva_y,
	Float: erva_z,
	Float: erva_a,
	Float: erva_agua,
	erva_stage,
	erva_time,
}
new CannabisInfo[MAX_SERVER_CANNABIS][e_cannabis];

new CannabisObject[MAX_SERVER_CANNABIS];

new Text3D:CannabisLabel[MAX_SERVER_CANNABIS];

new SelectCannabis[MAX_PLAYERS][MAX_PLAYER_CANNABIS];

new Iterator:Cannabis<MAX_SERVER_CANNABIS>;
