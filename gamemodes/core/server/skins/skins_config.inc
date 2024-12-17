GetSkinModel(skinid) {
    if(skinid >= 0 && skinid <= 311)
        return skinid;

    new models[] = {293, 305, 290, 165, 162, 230, 134, 137, 212, 135, 239};
    return models[skinid - 312];
}

// bns_SetPlayerSkin(playerid, skinid) {

//     for(new index = MAX_PLAYER_ATTACHED_OBJECTS-1; index >= 0; index--) {
// 	    if ((IsPlayerAttachedObjectSlotUsed(playerid, index) && !IsPlayerAccessoryValid(playerid, index)) || !IsPlayerAttachedObjectSlotUsed(playerid, index)) {
//             RemovePlayerAttachedObject(playerid, index);
//         }
//     }

//     if (skinid >= 0 && skinid <= 311) {
//         return SetPlayerSkin(playerid, skinid);
//     }

//     SetSkinObjects(playerid, skinid);

//     new skinModel = GetSkinModel(skinid);
//     SetPlayerSkin(playerid, skinModel);
    
// 	return true;
// }

// stock SetSkinObjects(playerid, skinid) {
//     new slotsVagos[10], cont = 0;
//     for(new index = MAX_PLAYER_ATTACHED_OBJECTS-1; index >= 0; index--) {
// 	    if ((IsPlayerAttachedObjectSlotUsed(playerid, index) && !IsPlayerAccessoryValid(playerid, index)) || !IsPlayerAttachedObjectSlotUsed(playerid, index)) {
//             slotsVagos[cont] = index;
//             RemovePlayerAttachedObject(playerid, index);
//             cont += 1;
//         }
//     }

//     // Skin OG Log Hamburguer - Colete
//     if(skinid == 312) {
//         SetPlayerAttachedObject(playerid, slotsVagos[0], 19094, 2,  0.145999, -0.000999, -0.004999,  0.000000, 0.000000, 0.000000,  1.000000, 0.721000, 0.713999); // 293
//         SetPlayerAttachedObject(playerid, slotsVagos[1], 19515, 1,  0.093999, 0.038000, -0.003000,  0.000000, 0.000000, 0.000000,  1.000000, 1.042000, 1.000000); // 293
//         SetPlayerAccessoryValid(playerid, slotsVagos[0], 0);
//         SetPlayerAccessoryValid(playerid, slotsVagos[1], 0);
//     }
//     // Skin Marinheiro
//     else if(skinid == 313) {
//         SetPlayerAttachedObject(playerid, slotsVagos[0], 19520, 2,  0.148000, 0.004999, -0.000000,  0.000000, 0.000000, 0.000000,  1.142000, 1.048001, 1.192002); // 305
//         SetPlayerAttachedObject(playerid, slotsVagos[1], 19033, 2,  0.091000, 0.027999, -0.001000,  0.000000, 90.000000, 90.000000,  1.000000, 1.000000, 1.000000); // 305
//         SetPlayerAccessoryValid(playerid, slotsVagos[0], 0);
//         SetPlayerAccessoryValid(playerid, slotsVagos[1], 0);
//     }
//     // Skin Mágico
//     else if(skinid == 314) {
//         SetPlayerAttachedObject(playerid, slotsVagos[0], 19352, 2,  0.107999, 0.006999, 0.001999,  0.000000, 90.000000, 90.000000,  1.056000, 1.035001, 1.000000); // 290
//         SetPlayerAttachedObject(playerid, slotsVagos[1], 18912, 2,  0.104000, 0.012000, 0.007999,  -91.699913, -3.300004, -98.799926,  1.039000, 1.000000, 1.100000); // 290
//         SetPlayerAccessoryValid(playerid, slotsVagos[0], 0);
//         SetPlayerAccessoryValid(playerid, slotsVagos[1], 0);
//     }
//     // Skin Segurança
//     else if(skinid == 315) {
//         SetPlayerAttachedObject(playerid, slotsVagos[0], 19515, 1,  -0.016000, 0.045999, 0.000000,  0.000000, 0.000000, 0.000000,  1.101999, 1.187000, 1.084000); // 165
//         SetPlayerAccessoryValid(playerid, slotsVagos[0], 0);
//     }
//     // Skin Magrelo
//     else if(skinid == 316) {
//         SetPlayerAttachedObject(playerid, slotsVagos[0], 19077, 2,  0.105999, -0.008000, -0.002999,  0.000000, 0.000000, 0.000000,  1.000000, 1.218000, 1.063000); // 162
//         SetPlayerAttachedObject(playerid, slotsVagos[1], 19033, 2,  0.101000, 0.044000, -0.003000,  0.000000, 90.000000, 90.000000,  1.000000, 1.027000, 1.000000); // 162
//         SetPlayerAccessoryValid(playerid, slotsVagos[0], 0);
//         SetPlayerAccessoryValid(playerid, slotsVagos[1], 0);
//     }
//     // Skin Mendigo Blask Mask
//     else if(skinid == 317) {
//         SetPlayerAttachedObject(playerid, slotsVagos[0], 19163, 2,  0.009000, 0.047999, -0.006000,  6.599989, 82.499870, 174.199920,  0.856000, 0.852000, 0.904999);
//         SetPlayerAccessoryValid(playerid, slotsVagos[0], 0);
//     }
//     // Skin Mendigo Zorro
//     else if(skinid == 318) {
//         SetPlayerAttachedObject(playerid, slotsVagos[0], 3785, 1,  -0.031999, -0.063000, -0.004000,  -89.700004, 108.999954, -5.900071,  0.733000, 0.784000, 0.623999); // 134
//         SetPlayerAttachedObject(playerid, slotsVagos[1], 18974, 2,  0.072999, 0.029999, 0.003999,  88.299980, 76.199935, -4.300071,  0.733000, 0.996000, 0.969999); // 134
//         SetPlayerAccessoryValid(playerid, slotsVagos[0], 0);
//         SetPlayerAccessoryValid(playerid, slotsVagos[1], 0);
//     }
//     // Skin Mendigo Burguer Head
//     else if(skinid == 319) {
//         SetPlayerAttachedObject(playerid, slotsVagos[0], 19811, 2,  0.116999, -0.017000, 0.003999,  88.299980, 76.199935, -4.300071,  1.388000, 1.227000, 1.356999); // 137
//         SetPlayerAccessoryValid(playerid, slotsVagos[0], 0);
//     }
//     // Skin Mendigo Rapper
//     else if(skinid == 320) {
//         SetPlayerAttachedObject(playerid, slotsVagos[0], 19617, 1,  0.006999, 0.111999, 0.003999,  88.299980, 76.199935, 97.699996,  0.352000, 1.227000, 0.381999); // 212
//         SetPlayerAttachedObject(playerid, slotsVagos[1], 18948, 2,  0.130999, 0.017999, 0.001999,  8.399994, 7.999953, 5.400002,  1.080000, 0.858000, 0.998998); // 212
//         SetPlayerAccessoryValid(playerid, slotsVagos[0], 0);
//         SetPlayerAccessoryValid(playerid, slotsVagos[1], 0);
//     }
//     // Skin Mendigo Gordo Gangster
//     else if(skinid == 321) {
//         SetPlayerAttachedObject(playerid, slotsVagos[0], 18912, 2,  0.058999, 0.017999, 0.001999,  -82.599998, 9.699954, -99.900009,  1.012999, 0.858000, 1.028998); // 135
//         SetPlayerAccessoryValid(playerid, slotsVagos[0], 0);
//     }
//     // Skin Mendigo Gas
//     else if(skinid == 322) {
//         SetPlayerAttachedObject(playerid, slotsVagos[0], 19472, 2,  0.034999, 0.127999, 0.000999,  94.099952, 69.499954, -4.099975,  0.889000, 1.315000, 1.213998); // 239
//         SetPlayerAccessoryValid(playerid, slotsVagos[0], 0);
//     }
// }

// #define SetPlayerSkin bns_SetPlayerSkin