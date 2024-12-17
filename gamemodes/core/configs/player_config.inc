#define	        MAX_PLAYER_IP           20      // Tamanho da string de IP

new PlayerName[MAX_PLAYERS][MAX_PLAYER_NAME];   // Nickname
new PlayerIP[MAX_PLAYERS][MAX_PLAYER_IP];       // IP

// ID de empregos:
enum {
    ID_JOB_NONE = 0,
    ID_JOB_DETETIVE = 1,
    ID_JOB_ADVOGADO = 2, 
    ID_JOB_CARTEIRO = 3, 
    ID_JOB_TAXISTA = 4,
    ID_JOB_MEDICO = 5,
    ID_JOB_MINERADOR = 6,
    ID_JOB_VENDEDOR_ARMAS = 7, 
    ID_JOB_BANDIDO = 8, 
    ID_JOB_MECANICO = 9,
    ID_JOB_FAZENDEIRO = 10,
    ID_JOB_CAMINHONEIRO = 11, 
    ID_JOB_PILOTO = 12,
    ID_JOB_FIREFIGHTER = 13,
    ID_JOB_DELIVERYMAN = 14,
    ID_JOB_LIXEIRO = 26, 
    ID_JOB_DESIGNER_INTERIORES = 43,
};

// Níveis de Sócio:
enum {
        SOCIO_COMUM             = 1,
        SOCIO_PREMIUM           = 6,
        SOCIO_SUPREME           = 7,
        SOCIO_EXTREME           = 8,
};