/*  ----------------------------------------------------------------------------------------------------------------------------------------

        Treinamento solo de cbug
                            v0.3
                            Theus_Crazzy (wearLyS)

 ----------------------------------------------------------------------------------------------------------------------------------------- */

#if defined _INC_solo_train_cbug
	#endinput
#endif
#define _INC_solo_train_cbug

// ---------------------------------------------------------------------------------
// Include <samp-random-events>

#if defined _INC_samp_random_event
	#if INC_samp_random_event_version < (5)
		#error Install version 5 or greater of the <samp-random-events> library
	#else
		#if !defined CBUG_EVENT
			#define CBUG_EVENT true
			#define CBUG_EVENT_ID 2
			#define COLOR_CBUG_EVENT 0xC41E29FF
		#endif
	#endif
#endif

#if !defined _INC_y_timers
	#tryinclude <YSI_Coding\y_timers>
#endif

// --------------------------------------------------------------------------------