/*  ----------------------------------------------------------------------------------------------------------------------------------------

        Sistema de eventos
                            v0.63
                            Theus_Crazzy (wearLyS)

 ----------------------------------------------------------------------------------------------------------------------------------------- */

#if defined _INC_samp_random_event
	#endinput
#endif
#define _INC_samp_random_event

#if defined INC_samp_random_event_version
	#endinput
#endif
#define INC_samp_random_event_version (5)

// Textdraws;
#include <samp-random-events-textdraws>

// ----------------------------------------------------------------

#if !defined _inc_y_iterate
	#tryinclude <YSI_Data\y_iterate>
#endif

#if !defined _INC_y_timers
	#tryinclude <YSI_Coding\y_timers>
#endif

// #if !defined _drift_included
// 	#tryinclude < drift-detection >
// #endif

// --------------------------------------------------------------------------------
// Defines;
#if !defined MAX_EVENTS
    #define         MAX_EVENTS                  (3)
#endif

#if !defined MAX_RANKS_EVENT
    #define         MAX_RANKS_EVENT             (3)
#endif

#if !defined INVALID_EVENT_ID
    #define         INVALID_EVENT_ID            0
#endif

#if !defined INVALID_EVENT_TYPE
    #define         INVALID_EVENT_TYPE          0
#endif

#if !defined INVALID_EVENT_MODE
    #define         INVALID_EVENT_MODE          0
#endif

#if !defined EVENT_MODE_HIGHER_SCORE
    #define         EVENT_MODE_HIGHER_SCORE     1
#endif

#if !defined EVENT_MODE_LOWER_SCORE
    #define         EVENT_MODE_LOWER_SCORE      2
#endif

#if !defined TIMER_EVENT
	#define TIMER_EVENT (5)
#endif


// Variáveis;
enum enumEvent
{
			ev_name[20],
			ev_type,
			ev_mode,
	Timer:	ev_timer,
			ev_count,
    bool:	ev_started,
    		ev_rank[MAX_RANKS_EVENT],
			ev_score[MAX_PLAYERS],
			ev_rscore[MAX_RANKS_EVENT],
			ev_color,
			ev_bonus[MAX_PLAYERS],
			count_events,
};
new EVENT[enumEvent];