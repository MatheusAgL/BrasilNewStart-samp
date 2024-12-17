/*  ----------------------------------------------------------------------------------------------------------------------------------------

        Sistema de e-mail;

 ----------------------------------------------------------------------------------------------------------------------------------------- */

#if defined _INC_email
	#endinput
#endif
#define _INC_email

// -- Máximo de e-mails na caixa de entrada;
#define MAX_PLAYER_CAIXA_ENTRADA  (25)
#define MAX_PREV_MENSAGEM         (30)

// -- Definições para identificar o status dos e-mails.
#define	EMAIL_ALL	0
#define	EMAIL_NOTREAD	1
#define	EMAIL_READ	2

// -- Definições para identificar a lista de e-mails.
#define	EMAIL_INBOX	1
#define	EMAIL_OUTBOX	2