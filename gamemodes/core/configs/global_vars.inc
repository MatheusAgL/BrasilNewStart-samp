// -----------------------------------------------------------------------------------
// Variáveis globais:

new MEGAString[4000];

// Contador de addons
enum counts_enum {
    COUNT_CREATEMAP,
    COUNT_CREATEPICKUPS,
	COUNT_CREATEVEHICLES,
	COUNT_CREATEMAPICON,
	COUNT_CREATETEXTDRAWS,
	COUNT_CREATEACTORS,
};
new gm_count[counts_enum];

new Timer:timer_gmx;
static bool:IsServerRestarting;

stock bool:Server_IsRestarting()
    return IsServerRestarting;

// -------------------------------

new ChatKill[MAX_PLAYERS];

new PlayerBar:BarSprayTag[MAX_PLAYERS];

enum pCrime
{
	pBplayer[55],
	pAccusing[55],
	pAccusedof[55],
	pVictim[55],
};

enum saveEnum
{
	Float:lastPos[4],
	lastInterior,
	lastVirtual,
	lastHouseEntered,
	lastStoreEntered,
	lastPosString[200]
};

enum pDanoEnum
{
	bool: danoKilled,
	danoDamager,
	danoWeapon,
	danoBodypart,
	danoTime,
	danoLast,
	Text3D:danoText,
}
new DanoInfo[MAX_PLAYERS][pDanoEnum];

new LastPosInfo[MAX_PLAYERS][saveEnum];
new GoChase[MAX_PLAYERS];
new EmpregoDuty[MAX_PLAYERS];
new DivorceOffer[MAX_PLAYERS];
new MarriageCeremoney[MAX_PLAYERS];
new ProposeOffer[MAX_PLAYERS];
new ProposedTo[MAX_PLAYERS];
new DoSexOffer[MAX_PLAYERS];
new GotProposedBy[MAX_PLAYERS];
new MarryWitness[MAX_PLAYERS];
new MarryWitnessOffer[MAX_PLAYERS];
new TicketOffer[MAX_PLAYERS];
new TicketMoney[MAX_PLAYERS];
new GotHit[MAX_PLAYERS];
new GotTri[MAX_PLAYERS];
new GetChased[MAX_PLAYERS];
new LiveOffer[MAX_PLAYERS];
new valorLiveOffer[MAX_PLAYERS]; //////////////////////////
new TalkingLive[MAX_PLAYERS];
new GettingEmprego[MAX_PLAYERS];
new DrugOffer[MAX_PLAYERS];
new DrugPrice[MAX_PLAYERS];
new DrugGram[MAX_PLAYERS];
new OnDuty[MAX_PLAYERS];
new gNoticias[MAX_PLAYERS];
new Chat_Organizacao[MAX_PLAYERS];
new BigEar[MAX_PLAYERS];
new PhoneOnline[MAX_PLAYERS];
new gDice[MAX_PLAYERS];
new DMSystem[MAX_PLAYERS][MAX_PLAYERS];
new PlayerCrime[MAX_PLAYERS][pCrime];
new PlayerText:TextTeste[MAX_PLAYERS][4];   // USANDO (Auto escola)
new InTeste[MAX_PLAYERS];                   // USANDO (Auto escola)
new TempoTeste[MAX_PLAYERS];                // USANDO (Auto escola)
new AtualCP[MAX_PLAYERS];                   // USANDO
new LotValue;
new
 	NoobDesativado,
	gmxAutomatico,
	eventoAleatorio,
	logDeComandos,
	Evento,
	vwa, inta,
	Float:ex,
	Float:ey,
	Float:ez,
	object_Fabricar[2]
;
new bool:wallAdmin[MAX_PLAYERS];
new patinss[MAX_PLAYERS];
new timejump[MAX_PLAYERS];
new block_temp_weapons[MAX_PLAYERS];
new bool:votou[MAX_PLAYERS];
new ICMS;
new GovernoTaxa;
new CofreAdmin;
new CofreEvento;
new PlayerText:TextHospital[MAX_PLAYERS];
new wLastShooter[MAX_PLAYERS];
new PlayerText:textAbordagem[4][MAX_PLAYERS];
new atendimentoFarmacia[MAX_PLAYERS];

#define GasMax             	 		100

new pickDoacao,
	CPsLanchonetes[20],
	CPsBar[5],
	AreaCofre;

new PortaoCN,
	pYak1,
	pYak2,
	pYak3,
	portaoDetran1,
    portaoDetran2,
	portaoPC,
    portaoPC2,
	portaoRussa,
	PortaoGN,
	PortaoBPEV,
	PortaoBOPE,
	PortaoBOPE2;

new VozDePrisao[MAX_PLAYERS];

new TempoAn[MAX_PLAYERS];
new PrisionVoiceTimer	[MAX_PLAYERS];
new InviteOffer			[MAX_PLAYERS];
new InviteJob			[MAX_PLAYERS];
new eEjet				[MAX_PLAYERS];
new Timer:timer_procurar[MAX_PLAYERS];
new Text:_drugs_textdraw[5],
    PlayerText:_drugs_playertextdraw[5][MAX_PLAYERS],
	Text:login_textdraws[12],
    PlayerText:login_ptextdraws[3][MAX_PLAYERS]
;
enum advogadoInfo
{
	advogadoID,
	porcentPrisao,
	precoAdvogado,
};
new AdvogadoInfo[MAX_PLAYERS][advogadoInfo];

new bool: JoinedHay[MAX_PLAYERS];
new OwnerMercadoNegro = 0, OwnerFabricaMateriais = 0;
new propinaMateriais = 0, bool:FabricandoMateriais[MAX_PLAYERS];

new Text3D:textFabricandoMat[MAX_PLAYERS];

new customorte[MAX_PLAYERS] = 100;
enum pSkateEnum {

	bool:	s_Setado,
	bool: 	s_Andando,
	Float:	s_Speed,
	Float:	s_Angulo,
	s_Skate,
	s_Update,
}
new SkateInfo[MAX_PLAYERS][pSkateEnum];

enum mobileInfo
{
	mobileCall,
};
new MobileInfo[MAX_PLAYERS + 6][mobileInfo];
new Text:textDeath;
new Text:textMorteAcc[4];
new PlayerText:textPlayerMorteAcc[MAX_PLAYERS];
new bool:InTaser[MAX_PLAYERS];
new PlayerText:textPlayerDamaged[2][MAX_PLAYERS];
new PlayerText:textPlayerDamager[2][MAX_PLAYERS];
new Float:playerCombo[2][MAX_PLAYERS];
new update_rate_skate = 70;
new Float:velocidade_skate[MAX_PLAYERS] = {11.0, ...};
new typeevento = 0;
new LFicha;
new AnuncioMandado;
new PortaoRally;
new PortaoReporter[2];
new PortaoMayans;
new PDELEVATOR;
new PortaoHit1;
new PortaoTriad1;
new hitfound = 0;
new trifound = 0;
new hitmanid = 999;
new triid = 999;
new TimeGranaTR = (2)*60; //2 minutos
new Refueling[MAX_PLAYERS];
new SorteioID = 0;