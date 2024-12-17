/**--------------------------------------------------------------------------**\
 ______ ______  ______     __  ______  ______  ______     ______  __  ______ __  __
/\  == /\  == \/\  __ \   /\ \/\  ___\/\  ___\/\__  _\   /\  ___\/\ \/\__  _/\ \_\ \
\ \  _-\ \  __<\ \ \/\ \ _\_\ \ \  __\\ \ \___\/_/\ \/   \ \ \___\ \ \/_/\ \\ \____ \
 \ \_\  \ \_\ \_\ \_____/\_____\ \_____\ \_____\ \ \_\    \ \_____\ \_\ \ \_\\/\_____\
  \/_/   \/_/ /_/\/_____\/_____/\/_____/\/_____/  \/_/     \/_____/\/_/  \/_/ \/_____/

						 ==========================
		                    Brasil Play Start
                              ® 2013 - 2017
                             Módulo: mSelection
						 ==========================

\**--------------------------------------------------------------------------**/

#include    < YSI_Coding\y_hooks >

new SkinsCopsList = mS_INVALID_LISTID;
new SkinsCopListSimple = mS_INVALID_LISTID;
new CarrosFamilyList = mS_INVALID_LISTID;
new CapaceteList = mS_INVALID_LISTID;
new SkinsFirefighter = mS_INVALID_LISTID;
new MoveisList = mS_INVALID_LISTID;
new CozinhaList = mS_INVALID_LISTID;
new QuartoList = mS_INVALID_LISTID;
new SalaList = mS_INVALID_LISTID;
new DecoracaoList = mS_INVALID_LISTID;
new BanheiroList = mS_INVALID_LISTID;
new VehiclesOrg_Police = mS_INVALID_LISTID;
new VehiclesOrg_Mercenario = mS_INVALID_LISTID;
new VehiclesOrg_Gangster = mS_INVALID_LISTID;
new VehiclesOrg_Terrorista = mS_INVALID_LISTID;
new VehiclesOrg_Assassina = mS_INVALID_LISTID;
new VehiclesOrg_Mafiosa = mS_INVALID_LISTID;
new VehiclesOrg_Civil = mS_INVALID_LISTID;
new VehiclesOrg_Governo = mS_INVALID_LISTID;
new VehiclesOrg_SanNews = mS_INVALID_LISTID;

new 
    SkinsListBinco = mS_INVALID_LISTID,
    SkinsListZip = mS_INVALID_LISTID,
    SkinsListVictim = mS_INVALID_LISTID,
    SkinsListSuburban = mS_INVALID_LISTID,
    SkinsListDS = mS_INVALID_LISTID,
    SkinsListPL = mS_INVALID_LISTID;

hook OnGameModeInit()
{
    SkinsListBinco = LoadModelSelectionMenu("ArquivosBPS/lSelections/skinsBinco.txt");
    SkinsListZip = LoadModelSelectionMenu("ArquivosBPS/lSelections/skinsZip.txt");
    SkinsListVictim = LoadModelSelectionMenu("ArquivosBPS/lSelections/skinsVictim.txt");
    SkinsListSuburban = LoadModelSelectionMenu("ArquivosBPS/lSelections/skinsSuburban.txt");
    SkinsListDS = LoadModelSelectionMenu("ArquivosBPS/lSelections/skinsDS.txt");
    SkinsListPL = LoadModelSelectionMenu("ArquivosBPS/lSelections/skinsPL.txt");
    MoveisList = LoadModelSelectionMenu("ArquivosBPS/lSelections/moveis.txt");
    CozinhaList = LoadModelSelectionMenu("ArquivosBPS/lSelections/moveis_cozinha.txt");
    QuartoList = LoadModelSelectionMenu("ArquivosBPS/lSelections/moveis_quarto.txt");
    BanheiroList = LoadModelSelectionMenu("ArquivosBPS/lSelections/moveis_banheiro.txt");
    SalaList = LoadModelSelectionMenu("ArquivosBPS/lSelections/moveis_sala.txt");
    DecoracaoList = LoadModelSelectionMenu("ArquivosBPS/lSelections/moveis_decoracao.txt");
    SkinsCopsList = LoadModelSelectionMenu("ArquivosBPS/lSelections/skinscops.txt");
    SkinsCopListSimple = LoadModelSelectionMenu("ArquivosBPS/lSelections/skinscops2.txt");
    CarrosFamilyList = LoadModelSelectionMenu("ArquivosBPS/lSelections/carrosfamilia.txt");
    CapaceteList = LoadModelSelectionMenu("ArquivosBPS/lSelections/capacetes.txt");
    SkinsFirefighter = LoadModelSelectionMenu("ArquivosBPS/lSelections/skinsFirefighter.txt");
    VehiclesOrg_Police = LoadModelSelectionMenu("ArquivosBPS/lSelections/vehicles_org_police.txt");
    VehiclesOrg_Mercenario = LoadModelSelectionMenu("ArquivosBPS/lSelections/vehicles_org_mercenary.txt");
    VehiclesOrg_Gangster = LoadModelSelectionMenu("ArquivosBPS/lSelections/vehicles_org_gangster.txt");
    VehiclesOrg_Assassina = LoadModelSelectionMenu("ArquivosBPS/lSelections/vehicles_org_assassina.txt");
    VehiclesOrg_Terrorista = LoadModelSelectionMenu("ArquivosBPS/lSelections/vehicles_org_terrorista.txt");
    VehiclesOrg_Mafiosa = LoadModelSelectionMenu("ArquivosBPS/lSelections/vehicles_org_mafia.txt");
    VehiclesOrg_Civil = LoadModelSelectionMenu("ArquivosBPS/lSelections/vehicles_org_civil.txt");
    VehiclesOrg_Governo = LoadModelSelectionMenu("ArquivosBPS/lSelections/vehicles_org_governo.txt");
    VehiclesOrg_SanNews = LoadModelSelectionMenu("ArquivosBPS/lSelections/vehicles_org_sannews.txt");
    return 1;
}






