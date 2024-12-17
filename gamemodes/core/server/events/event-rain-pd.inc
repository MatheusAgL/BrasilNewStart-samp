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
		#if !defined RAIN_PD_EVENT
			#define RAIN_PD_EVENT true
			#define RAIN_PD_EVENT_ID 4
			#define COLOR_RAIN_PD_EVENT 0x1EA7E7AA
		#endif
	#endif
#endif

// ---------------------------------------------------------------------------------