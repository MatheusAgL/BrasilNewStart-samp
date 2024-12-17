#include <YSI_Coding\y_hooks>

new Text:td_discord_link[6];

stock CreateTD_Discord()
{
    td_discord_link[0] = TextDrawCreate(140.000, 61.000, "PARTICLE:bloodpool_64");
    TextDrawTextSize(td_discord_link[0], 343.000, 350.000);
    TextDrawAlignment(td_discord_link[0], 1);
    TextDrawColor(td_discord_link[0], 100);
    TextDrawSetShadow(td_discord_link[0], 0);
    TextDrawSetOutline(td_discord_link[0], 0);
    TextDrawBackgroundColor(td_discord_link[0], 255);
    TextDrawFont(td_discord_link[0], 4);
    TextDrawSetProportional(td_discord_link[0], 1);

    td_discord_link[1] = TextDrawCreate(162.000, 119.000, "LD_BEAT:downr");
    TextDrawTextSize(td_discord_link[1], 25.000, 27.000);
    TextDrawAlignment(td_discord_link[1], 1);
    TextDrawColor(td_discord_link[1], 512819199);
    TextDrawSetShadow(td_discord_link[1], 0);
    TextDrawSetOutline(td_discord_link[1], 0);
    TextDrawBackgroundColor(td_discord_link[1], 255);
    TextDrawFont(td_discord_link[1], 4);
    TextDrawSetProportional(td_discord_link[1], 1);

    td_discord_link[2] = TextDrawCreate(217.000, 190.000, "ACESSE NOSSO DISCORD~n~~n~~b~~h~~h~1. ~w~Entre na sala 'vincular-discord' e conecte-se~n~a sua conta.");
    TextDrawLetterSize(td_discord_link[2], 0.240, 1.499);
    TextDrawTextSize(td_discord_link[2], 415.000, 0.000);
    TextDrawAlignment(td_discord_link[2], 1);
    TextDrawColor(td_discord_link[2], 512819199);
    TextDrawSetShadow(td_discord_link[2], 0);
    TextDrawSetOutline(td_discord_link[2], 1);
    TextDrawBackgroundColor(td_discord_link[2], -251);
    TextDrawFont(td_discord_link[2], 1);
    TextDrawSetProportional(td_discord_link[2], 1);

    td_discord_link[3] = TextDrawCreate(388.000, 334.000, "LD_BEAT:upl");
    TextDrawTextSize(td_discord_link[3], 25.000, 27.000);
    TextDrawAlignment(td_discord_link[3], 1);
    TextDrawColor(td_discord_link[3], 512819199);
    TextDrawSetShadow(td_discord_link[3], 0);
    TextDrawSetOutline(td_discord_link[3], 0);
    TextDrawBackgroundColor(td_discord_link[3], 255);
    TextDrawFont(td_discord_link[3], 4);
    TextDrawSetProportional(td_discord_link[3], 1);

    td_discord_link[4] = TextDrawCreate(346.000, 262.000, "Confirmar");
    TextDrawLetterSize(td_discord_link[4], 0.300, 1.500);
    TextDrawTextSize(td_discord_link[4], 14.000, 57.000);
    TextDrawAlignment(td_discord_link[4], 2);
    TextDrawColor(td_discord_link[4], -1);
    TextDrawUseBox(td_discord_link[4], 1);
    TextDrawBoxColor(td_discord_link[4], 512819044);
    TextDrawSetShadow(td_discord_link[4], 1);
    TextDrawSetOutline(td_discord_link[4], 1);
    TextDrawBackgroundColor(td_discord_link[4], 255);
    TextDrawFont(td_discord_link[4], 1);
    TextDrawSetProportional(td_discord_link[4], 1);
    TextDrawSetSelectable(td_discord_link[4], 1);

    td_discord_link[5] = TextDrawCreate(316.000, 205.000, SERVER_DISCORD);
    TextDrawLetterSize(td_discord_link[5], 0.150, 0.999);
    TextDrawTextSize(td_discord_link[5], 415.000, 0.000);
    TextDrawAlignment(td_discord_link[5], 3);
    TextDrawColor(td_discord_link[5], 16423679);
    TextDrawSetShadow(td_discord_link[5], 0);
    TextDrawSetOutline(td_discord_link[5], 0);
    TextDrawBackgroundColor(td_discord_link[5], -251);
    TextDrawFont(td_discord_link[5], 2);
    TextDrawSetProportional(td_discord_link[5], 1);

    printf("[TEXTDRAW]: Discord Link... 6 loaded!", gm_count[COUNT_CREATETEXTDRAWS]);
    gm_count[COUNT_CREATETEXTDRAWS] += 6;
}

stock DiscordLink_ShowTextDraws(playerid) {
    for(new text; text < sizeof(td_discord_link); text++)
        TextDrawShowForPlayer(playerid, td_discord_link[text]);
}

stock DiscordLink_HideTextDraws(playerid) {
    for(new text; text < sizeof(td_discord_link); text++)
        TextDrawHideForPlayer(playerid, td_discord_link[text]);
}