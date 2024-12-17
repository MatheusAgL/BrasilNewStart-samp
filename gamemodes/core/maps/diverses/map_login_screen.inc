#define _MAP_LOGIN_SCREEN true

stock CreateMap_LoginScreen() // Mapa
{
    new tmp_objid;
	tmp_objid = CreateDynamicObject(18762, 1981.687134, 1189.544922, 27.878761, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(18762, 1980.686401, 1189.544922, 27.878761, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(18762, 1982.687866, 1189.544922, 27.878761, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(18762, 1979.685547, 1189.544922, 27.878761, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(18762, 1983.688599, 1189.544922, 27.878761, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(2399, 1984.548950, 1189.791504, 28.113008, 0.000014, -0.000014, 179.999832, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 2819, "gb_bedroomclths01", "GB_clothesbed01", 0);
	tmp_objid = CreateDynamicObject(2397, 1984.568970, 1189.791504, 27.112520, 0.000014, -0.000014, 179.999832, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 3961, "lee_kitch", "ChoppingBoard", 0);
	tmp_objid = CreateDynamicObject(19921, 1984.887451, 1190.072021, 27.480881, 0.000037, 89.999939, 179.999466, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(19483, 1984.890503, 1190.039429, 27.428146, 89.999992, 359.815582, -89.815483, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18065, "ab_sfammumain", "shelf_glas", 0x90FFFFFF);
	tmp_objid = CreateDynamicObject(19921, 1984.917480, 1190.072021, 27.480881, 0.000037, 89.999939, 179.999466, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(19445, 1984.572632, 1190.639893, 29.841480, 180.000000, 90.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14865, "gf2", "mp_bobbie_carpwhite", 0);
	tmp_objid = CreateDynamicObject(19483, 1984.900513, 1189.739380, 27.470627, 89.999992, 359.815582, -89.815483, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(11683, 1985.137939, 1193.110840, 25.864622, 0.000000, 0.000000, 810.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(11685, 1985.266968, 1193.050781, 25.866623, 0.000000, 0.000000, 540.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(2707, 1985.097656, 1191.026978, 29.744587, -0.000073, -0.000058, -179.999115, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2397, 1985.238892, 1189.791504, 27.112520, 0.000014, -0.000014, 179.999832, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	tmp_objid = CreateDynamicObject(2399, 1985.238892, 1189.791504, 28.113008, 0.000014, -0.000014, 179.999832, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 2819, "gb_bedroomclths01", "GB_clothesbed05", 0);
	tmp_objid = CreateDynamicObject(19859, 1984.203613, 1188.540771, 27.474411, 0.000059, 0.000045, 89.999664, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0);
	tmp_objid = CreateDynamicObject(19445, 1984.572632, 1194.139160, 29.841480, 180.000000, 90.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14865, "gf2", "mp_bobbie_carpwhite", 0);
	tmp_objid = CreateDynamicObject(2707, 1985.247559, 1191.026978, 29.744587, -0.000073, -0.000058, -179.999115, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2448, 1984.422607, 1188.440674, 28.284592, 0.000059, 90.000046, 89.999664, -1, -1, -1, 300.0); // 5
	SetDynamicObjectMaterial(tmp_objid, 4, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(1575, 1985.931274, 1192.800415, 26.486189, 77.499992, -0.000070, 179.999802, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 1355, "break_s_bins", "CJ_RED_LEATHER", 0);
	tmp_objid = CreateDynamicObject(19353, 1984.566528, 1195.063843, 25.797598, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 15041, "bigsfsave", "carp11S", 0);
	tmp_objid = CreateDynamicObject(19483, 1984.890503, 1188.771606, 28.658127, 0.000037, 270.000000, 179.999435, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(19483, 1984.890503, 1188.769653, 26.457199, 0.000037, 270.000000, 179.999435, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(19445, 1984.488403, 1189.973389, 24.166018, 0.000000, 0.000000, 450.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	tmp_objid = CreateDynamicObject(2399, 1985.950195, 1189.791504, 28.113008, 0.000014, -0.000022, 179.999786, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 2819, "gb_bedroomclths01", "GB_clothesbed04", 0);
	tmp_objid = CreateDynamicObject(2397, 1985.970215, 1189.791504, 27.112520, 0.000014, -0.000022, 179.999786, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 2819, "gb_bedroomclths01", "GB_clothesbed02", 0);
	tmp_objid = CreateDynamicObject(19604, 1984.298584, 1190.071777, 23.784176, 180.000000, 90.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14561, "triad_neon", "kbneon", 0x90000000);
	tmp_objid = CreateDynamicObject(19921, 1986.266479, 1190.070068, 27.480881, 0.000037, 89.999947, 179.999512, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(19426, 1986.258179, 1191.262695, 25.795597, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 15041, "bigsfsave", "carp11S", 0);
	tmp_objid = CreateDynamicObject(19483, 1986.269531, 1190.037476, 27.428146, 89.999992, 359.631104, -89.631012, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18065, "ab_sfammumain", "shelf_glas", 0x90FFFFFF);
	tmp_objid = CreateDynamicObject(19921, 1986.296509, 1190.070068, 27.480881, 0.000037, 89.999947, 179.999512, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(1818, 1985.033569, 1195.328369, 25.866793, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 642, "canopy", "wood02", 0);
	tmp_objid = CreateDynamicObject(1818, 1985.035522, 1195.330322, 25.766790, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	tmp_objid = CreateDynamicObject(1818, 1985.035522, 1195.330322, 25.626787, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	tmp_objid = CreateDynamicObject(19483, 1986.279541, 1189.737427, 27.470627, 89.999992, 359.631104, -89.631012, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(2448, 1985.382568, 1188.440674, 26.827682, -0.000059, 270.000000, -89.999542, -1, -1, -1, 300.0); // 5
	SetDynamicObjectMaterial(tmp_objid, 4, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(1818, 1985.035522, 1195.330322, 25.506784, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	tmp_objid = CreateDynamicObject(19859, 1985.582642, 1188.538818, 27.474411, 0.000051, 0.000045, 89.999687, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0);
	tmp_objid = CreateDynamicObject(19859, 1985.603516, 1188.540771, 27.474411, 0.000059, 0.000045, 89.999664, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0);
	tmp_objid = CreateDynamicObject(2028, 1985.407715, 1195.439819, 26.294664, -7.500038, -4.999989, 21.000134, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 6, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 5, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19604, 1984.298584, 1190.061768, 31.814207, 180.000000, 90.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14561, "triad_neon", "kbneon", 0x90000000);
	tmp_objid = CreateDynamicObject(11685, 1986.577637, 1193.050781, 25.866623, 0.000000, 0.000000, 540.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(2028, 1985.407715, 1195.599731, 26.294664, -7.500054, -4.999986, -68.999687, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 6, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 5, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2270, 1985.992065, 1194.883423, 28.870630, 0.000000, 0.000014, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1560, "7_11_door", "CJ_CHROME2", 0);
	tmp_objid = CreateDynamicObject(18765, 1979.008423, 1194.583618, 23.379709, 0.000000, 0.000007, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 3820, "boxhses_sfsx", "tanboard1", 0);
	tmp_objid = CreateDynamicObject(2397, 1986.640137, 1189.791504, 27.112520, 0.000014, -0.000022, 179.999786, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 2819, "gb_bedroomclths01", "GB_clothesbed01", 0);
	tmp_objid = CreateDynamicObject(2399, 1986.640137, 1189.791504, 28.113008, 0.000014, -0.000022, 179.999786, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 2819, "gb_bedroomclths01", "GB_clothesbed03", 0);
	tmp_objid = CreateDynamicObject(2448, 1985.801636, 1188.438721, 28.284592, 0.000051, 90.000046, 89.999687, -1, -1, -1, 300.0); // 5
	SetDynamicObjectMaterial(tmp_objid, 4, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2270, 1985.708862, 1195.323608, 29.226954, -0.000037, -89.999985, -89.999847, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1560, "7_11_door", "CJ_CHROME2", 0);
	tmp_objid = CreateDynamicObject(2707, 1986.617676, 1191.026978, 29.744587, -0.000067, -0.000058, -179.999130, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	CreateDynamicObject(2816, 1985.309937, 1195.980713, 26.371935, 0.000014, -0.000012, 81.799721, -1, -1, -1, 300.0); // 0
	tmp_objid = CreateDynamicObject(19353, 1985.927856, 1195.063843, 25.795597, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 15041, "bigsfsave", "carp11S", 0);
	tmp_objid = CreateDynamicObject(2829, 1985.778198, 1195.534058, 26.372248, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 7
	SetDynamicObjectMaterial(tmp_objid, 6, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 5, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 14745, "rystuff", "mp_CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19466, 1985.522339, 1195.872192, 26.369608, 0.000000, 270.000000, -179.999985, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18065, "ab_sfammumain", "shelf_glas", 0);
	tmp_objid = CreateDynamicObject(18765, 1984.400269, 1194.583618, 23.375708, 0.000000, 0.000007, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 3820, "boxhses_sfsx", "tanboard1", 0);
	tmp_objid = CreateDynamicObject(2707, 1986.767578, 1191.026978, 29.744587, -0.000067, -0.000058, -179.999130, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19483, 1986.269531, 1188.769653, 28.658127, 0.000037, 270.000000, 179.999481, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(19483, 1986.269531, 1188.767700, 26.457199, 0.000037, 270.000000, 179.999481, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(1575, 1987.232544, 1192.800415, 26.486189, 77.499992, -0.000035, 179.999802, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 1355, "break_s_bins", "CJ_RED_LEATHER", 0);
	tmp_objid = CreateDynamicObject(1818, 1986.054443, 1195.338379, 25.868793, 0.000007, 0.000000, 89.999977, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 642, "canopy", "wood02", 0);
	tmp_objid = CreateDynamicObject(19893, 1985.826904, 1195.878052, 26.506851, -69.699974, -0.000019, -90.000008, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 18868, "mobilephone4", "mobilephone4-2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19353, 1985.912842, 1191.000854, 31.500202, 0.000007, 0.000022, 89.999893, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 13077, "cunte_bar1", "black16", 0);
	tmp_objid = CreateDynamicObject(18763, 1984.880371, 1188.552002, 31.218781, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(18763, 1984.880371, 1188.552002, 23.888754, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(2270, 1986.002075, 1195.843994, 28.870630, 0.000000, -0.000014, 179.999908, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1560, "7_11_door", "CJ_CHROME2", 0);
	tmp_objid = CreateDynamicObject(19893, 1986.042847, 1195.878052, 26.363512, 0.000007, 0.000000, 89.999878, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 18996, "mattextures", "sampblack", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19787, "samplcdtvs1", "samplcdtv1", 0);
	tmp_objid = CreateDynamicObject(2270, 1985.318604, 1196.482788, 29.236963, 0.000006, 449.999939, -89.999985, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1560, "7_11_door", "CJ_CHROME2", 0);
	tmp_objid = CreateDynamicObject(2270, 1985.987915, 1195.964355, 28.870630, 0.000000, 0.000014, -0.000012, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1560, "7_11_door", "CJ_CHROME2", 0);
	tmp_objid = CreateDynamicObject(3785, 1985.992920, 1195.953247, 29.013575, 0.000000, 0.000014, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(1946, 1986.013672, 1195.920410, 29.211573, 0.000000, 0.000014, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18835, "mickytextures", "whiteforletters", 0);
	tmp_objid = CreateDynamicObject(2399, 1987.311279, 1189.791504, 28.113008, 0.000014, -0.000007, 179.999878, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 2819, "gb_bedroomclths01", "GB_clothesbed01", 0);
	tmp_objid = CreateDynamicObject(2397, 1987.331299, 1189.791504, 27.112520, 0.000014, -0.000007, 179.999878, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 3961, "lee_kitch", "ChoppingBoard", 0);
	CreateDynamicObject(18673, 1985.981812, 1195.439087, 24.829607, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 0
	tmp_objid = CreateDynamicObject(11683, 1982.711304, 1197.925293, 25.864622, 0.000023, -0.000015, 134.999985, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(19482, 1985.996460, 1195.944214, 29.739283, 0.000000, 89.999985, 179.999908, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "sphere", 0x90000000);
	tmp_objid = CreateDynamicObject(2270, 1986.671387, 1195.325562, 29.236963, 0.000037, 449.999939, 89.999893, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1560, "7_11_door", "CJ_CHROME2", 0);
	tmp_objid = CreateDynamicObject(2448, 1986.761597, 1188.438721, 26.827682, -0.000051, 270.000000, -89.999565, -1, -1, -1, 300.0); // 5
	SetDynamicObjectMaterial(tmp_objid, 4, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19353, 1984.566528, 1197.315796, 25.799599, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 15041, "bigsfsave", "carp11S", 0);
	tmp_objid = CreateDynamicObject(19921, 1987.645630, 1190.068115, 27.480881, 0.000037, 89.999954, 179.999557, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(19483, 1987.648682, 1190.035522, 27.428146, 89.999992, 359.262177, -89.262093, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18065, "ab_sfammumain", "shelf_glas", 0x90FFFFFF);
	tmp_objid = CreateDynamicObject(19859, 1986.961792, 1188.536865, 27.474411, 0.000045, 0.000045, 89.999710, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0);
	tmp_objid = CreateDynamicObject(11685, 1982.739624, 1198.065674, 25.868624, 0.000015, 0.000023, 44.999985, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(19921, 1987.675659, 1190.068115, 27.480881, 0.000037, 89.999954, 179.999557, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(19859, 1986.982544, 1188.538818, 27.474411, 0.000051, 0.000045, 89.999687, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0);
	tmp_objid = CreateDynamicObject(1575, 1982.558228, 1198.280273, 26.486189, 77.499992, 0.000039, 44.999653, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 1355, "break_s_bins", "CJ_RED_LEATHER", 0);
	tmp_objid = CreateDynamicObject(11683, 1982.886841, 1198.106201, 25.866623, -0.000023, 0.000015, -45.000004, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(19483, 1987.658691, 1189.735474, 27.470627, 89.999992, 359.262177, -89.262093, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(11685, 1987.877686, 1193.050781, 25.866623, 0.000000, 0.000000, 540.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(2448, 1987.180786, 1188.436768, 28.284592, 0.000045, 90.000046, 89.999710, -1, -1, -1, 300.0); // 5
	SetDynamicObjectMaterial(tmp_objid, 4, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2270, 1986.281128, 1196.484741, 29.226954, -0.000006, -89.999985, 90.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1560, "7_11_door", "CJ_CHROME2", 0);
	tmp_objid = CreateDynamicObject(2270, 1985.997925, 1196.924927, 28.870630, 0.000000, -0.000014, 179.999802, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1560, "7_11_door", "CJ_CHROME2", 0);
	tmp_objid = CreateDynamicObject(19353, 1987.013916, 1191.000854, 31.500202, 0.000007, 0.000022, 89.999893, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 13077, "cunte_bar1", "black16", 0);
	tmp_objid = CreateDynamicObject(19445, 1984.572632, 1197.639160, 29.841480, 180.000000, 90.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14865, "gf2", "mp_bobbie_carpwhite", 0);
	tmp_objid = CreateDynamicObject(2397, 1988.001221, 1189.791504, 27.112520, 0.000014, -0.000007, 179.999878, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	tmp_objid = CreateDynamicObject(2399, 1988.001221, 1189.791504, 28.113008, 0.000014, -0.000007, 179.999878, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 2819, "gb_bedroomclths01", "GB_clothesbed05", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.906128, 1198.855225, 27.622343, -6.999829, -179.999985, 99.999611, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.901367, 1198.857910, 27.622343, -7.000008, -179.999863, 10.000000, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.909302, 1198.859131, 27.622343, -6.999969, 179.999863, -170.000381, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2327, 1981.904175, 1198.860107, 27.576353, -0.000157, 89.999931, -79.999977, -1, -1, -1, 300.0); // 9
	SetDynamicObjectMaterial(tmp_objid, 8, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 7, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 6, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 5, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 10101, "2notherbuildsfe", "ferry_build14", 0);
	tmp_objid = CreateDynamicObject(2327, 1981.904175, 1198.860107, 27.676357, -0.000157, 89.999931, -79.999977, -1, -1, -1, 300.0); // 9
	SetDynamicObjectMaterial(tmp_objid, 8, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 7, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 6, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 5, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 10101, "2notherbuildsfe", "ferry_build14", 0);
	tmp_objid = CreateDynamicObject(2327, 1981.904175, 1198.860107, 27.476353, -0.000157, 89.999931, -79.999977, -1, -1, -1, 300.0); // 9
	SetDynamicObjectMaterial(tmp_objid, 8, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 7, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 6, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 5, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 10101, "2notherbuildsfe", "ferry_build14", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.905029, 1198.862427, 27.622343, -7.000145, 179.999985, -79.999565, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19197, 1981.902588, 1198.869263, 27.133007, -0.000163, 179.999985, -79.999641, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14634, "blindinglite", "ws_volumetriclight", 0x90FFFFFF);
	tmp_objid = CreateDynamicObject(11685, 1988.087891, 1193.250977, 25.868624, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(19483, 1987.648682, 1188.767700, 28.658127, 0.000037, 270.000000, 179.999527, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(2260, 1982.581665, 1198.914673, 27.676891, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 1, 2266, "picture_frame", "CJ_PAINTING34", 0);
	tmp_objid = CreateDynamicObject(19483, 1987.648682, 1188.765747, 26.457199, 0.000037, 270.000000, 179.999527, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(1575, 1988.313232, 1193.320923, 26.486189, 77.500015, 0.000000, -90.000076, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 1355, "break_s_bins", "CJ_RED_LEATHER", 0);
	tmp_objid = CreateDynamicObject(2691, 1981.930908, 1198.884888, 25.901861, -89.999992, 89.999992, 89.999992, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "sphere", 0);
	tmp_objid = CreateDynamicObject(2750, 1982.928711, 1198.937866, 28.196712, -0.000029, 89.999977, 90.000557, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19424, "headphones", "headphones02", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19353, 1985.927856, 1197.312744, 25.797600, 0.000000, 90.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 15041, "bigsfsave", "carp11S", 0);
	tmp_objid = CreateDynamicObject(11685, 1988.087891, 1194.561401, 25.868624, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(2707, 1983.606812, 1198.631958, 29.744587, -0.000073, -0.000057, -179.999115, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2707, 1988.512085, 1191.850098, 29.744587, -0.000111, -0.000059, -89.999031, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2707, 1988.512085, 1191.700195, 29.744587, -0.000111, -0.000059, -89.999031, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2707, 1983.756714, 1198.631958, 29.744587, -0.000073, -0.000057, -179.999115, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2750, 1983.589233, 1198.937866, 28.736725, -0.000043, 89.999977, 90.000603, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19424, "headphones", "headphones02", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(1575, 1988.313232, 1194.550537, 26.486189, 77.500031, 0.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 1355, "break_s_bins", "CJ_RED_LEATHER", 0);
	tmp_objid = CreateDynamicObject(2707, 1982.958252, 1199.198364, 27.876898, -0.000029, -0.000012, 90.000557, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 18889, "forcefields", "glass1", 0);
	tmp_objid = CreateDynamicObject(19981, 1988.750000, 1190.545288, 27.622343, -6.999832, -179.999985, 28.599674, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0);
	tmp_objid = CreateDynamicObject(19981, 1988.751099, 1190.550659, 27.622343, -7.000008, -179.999863, -61.399944, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2327, 1988.754028, 1190.548828, 27.576353, -0.000157, 89.999931, -151.399918, -1, -1, -1, 300.0); // 9
	SetDynamicObjectMaterial(tmp_objid, 8, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 7, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 6, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 5, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 10101, "2notherbuildsfe", "ferry_build14", 0);
	tmp_objid = CreateDynamicObject(2327, 1988.754028, 1190.548828, 27.676357, -0.000157, 89.999931, -151.399918, -1, -1, -1, 300.0); // 9
	SetDynamicObjectMaterial(tmp_objid, 8, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 7, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 6, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 5, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 10101, "2notherbuildsfe", "ferry_build14", 0);
	tmp_objid = CreateDynamicObject(2327, 1988.754028, 1190.548828, 27.476353, -0.000157, 89.999931, -151.399918, -1, -1, -1, 300.0); // 9
	SetDynamicObjectMaterial(tmp_objid, 8, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 7, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 6, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 5, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 10101, "2notherbuildsfe", "ferry_build14", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 10101, "2notherbuildsfe", "ferry_build14", 0);
	tmp_objid = CreateDynamicObject(19981, 1988.754761, 1190.543579, 27.622343, -6.999969, 179.999863, 118.599594, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1988.756470, 1190.548706, 27.622343, -7.000144, 179.999985, -151.399506, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19084, 1982.929688, 1199.217407, 27.998837, 0.000036, 270.000000, 90.000267, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 18996, "mattextures", "sampblack", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18996, "mattextures", "sampblack", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampblack", 0);
	tmp_objid = CreateDynamicObject(19197, 1988.762207, 1190.553223, 27.133007, -0.000165, 179.999985, -151.399582, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14634, "blindinglite", "ws_volumetriclight", 0x90FFFFFF);
	tmp_objid = CreateDynamicObject(2707, 1988.512085, 1193.220215, 29.744587, -0.000103, -0.000059, -89.999046, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2707, 1988.512085, 1193.370117, 29.744587, -0.000103, -0.000059, -89.999046, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2247, 1983.471558, 1199.064087, 26.349010, 0.000000, 0.000022, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 10839, "aircarpkbarier_sfse", "glass_64a", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2811, 1983.526245, 1198.975586, 25.940445, 0.000000, 0.000022, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2260, 1988.841309, 1190.523193, 27.676891, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 1, 2266, "picture_frame", "CJ_PAINTING5", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.478271, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.578247, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.378296, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.678223, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.278320, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.778198, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.178345, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.878174, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.078369, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.978149, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.978394, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.078125, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.878418, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.178101, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.778442, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.278076, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.678467, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2448, 1988.140747, 1188.436768, 26.827682, -0.000045, 270.000000, -89.999588, -1, -1, -1, 300.0); // 5
	SetDynamicObjectMaterial(tmp_objid, 4, 18632, "fishingrod", "rodpole2", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.378052, 1199.425049, 28.535713, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2691, 1988.733154, 1190.542725, 25.901861, 270.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "sphere", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.588257, 1199.425049, 28.535713, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2707, 1983.618774, 1199.198364, 28.416910, -0.000043, -0.000012, 90.000603, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 18889, "forcefields", "glass1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.478638, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.488281, 1199.425049, 28.535713, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.578613, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.388306, 1199.425049, 28.535713, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19084, 1983.590210, 1199.217407, 28.538849, 0.000020, 270.000000, 90.000313, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 18996, "mattextures", "sampblack", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18996, "mattextures", "sampblack", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampblack", 0);
	tmp_objid = CreateDynamicObject(19939, 1984.467529, 1198.890747, 26.546616, -0.000029, 90.000008, -89.999947, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampwhite", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.678589, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.288330, 1199.425049, 28.535713, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2662, 1981.855957, 1199.361328, 29.406652, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(19981, 1982.778564, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.188354, 1199.425049, 28.535713, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.878540, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.088379, 1199.425049, 28.535713, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.478271, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.578247, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.378296, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.678223, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.278320, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.978516, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.778198, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.178345, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1979.988403, 1199.425049, 28.535713, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.878174, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.078369, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1981.978149, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.978394, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19859, 1988.361694, 1188.536865, 27.474411, 0.000045, 0.000045, 89.999710, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18632, "fishingrod", "rodpole2", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.078125, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.078491, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.878418, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1979.888428, 1199.425049, 28.535713, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.178101, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.778442, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.278076, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.678467, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.178467, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.378052, 1199.425049, 25.865709, 0.000014, 0.000007, 89.999954, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19084, 1982.929688, 1199.217407, 29.789110, 0.000036, 270.000000, 90.000267, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 18996, "mattextures", "sampblack", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18996, "mattextures", "sampblack", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampblack", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.588257, 1199.425049, 25.865709, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.478638, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.488281, 1199.425049, 25.865709, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.278442, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.578613, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.388306, 1199.425049, 25.865709, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19835, 1984.360596, 1199.103882, 26.728775, 0.000000, 0.000067, 0.000000, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 3, 2514, "cj_bathroom", "cj_toilet", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 2514, "cj_bathroom", "cj_toilet", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 2514, "cj_bathroom", "cj_toilet", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.678589, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.378418, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.288330, 1199.425049, 25.865709, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19835, 1984.230469, 1199.183960, 26.768776, 0.000000, 0.000059, 0.000000, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 3, 2514, "cj_bathroom", "cj_toilet", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 2514, "cj_bathroom", "cj_toilet", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 2514, "cj_bathroom", "cj_toilet", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.778564, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.188354, 1199.425049, 25.865709, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.478394, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(18762, 1988.880371, 1189.544922, 27.878761, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(19981, 1982.878540, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1980.088379, 1199.425049, 25.865709, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19353, 1982.723999, 1198.605835, 31.500202, 0.000000, 0.000022, 89.999916, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 13077, "cunte_bar1", "black16", 0);
	tmp_objid = CreateDynamicObject(19981, 1982.978516, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.578369, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(14788, 1989.241211, 1192.744263, 28.107922, 0.000000, 0.000014, 180.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 2823, "gb_kitchtake", "deep_red64", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2854, 1984.816895, 1198.994141, 26.900501, 0.092303, -540.186218, -107.799805, -1, -1, -1, 300.0); // 6
	SetDynamicObjectMaterial(tmp_objid, 5, 2813, "gb_books01", "GB_novels02", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1979.988403, 1199.425049, 25.865709, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2854, 1984.816895, 1198.994019, 26.860584, 0.092303, -540.186218, -107.799805, -1, -1, -1, 300.0); // 6
	SetDynamicObjectMaterial(tmp_objid, 5, 2813, "gb_books01", "GB_novels03", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2854, 1984.816895, 1198.993896, 26.820545, 0.092303, -540.186218, -107.799805, -1, -1, -1, 300.0); // 6
	SetDynamicObjectMaterial(tmp_objid, 5, 2813, "gb_books01", "GB_novels09", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2662, 1983.253174, 1199.361328, 29.406652, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(19981, 1983.078491, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1979.888428, 1199.425049, 25.865709, 0.000022, 0.000007, 89.999931, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.678345, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.178467, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19869, 1989.327148, 1191.579956, 27.513948, 0.000000, 89.999939, 89.999619, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 10973, "mall_sfse", "ws_grilleshade", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19297, "matlights", "invisible", 0);
	tmp_objid = CreateDynamicObject(11735, 1984.993042, 1198.870972, 26.268209, 22.200012, 0.000000, -89.999954, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 1246, "icons", "pill_32", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.778320, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(11685, 1988.087891, 1195.872192, 25.868624, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(19084, 1983.590210, 1199.217407, 29.789110, 0.000020, 270.000000, 90.000313, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 18996, "mattextures", "sampblack", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 18996, "mattextures", "sampblack", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampblack", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.278442, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.878296, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.378418, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.478394, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	CreateDynamicObject(18701, 1984.220581, 1199.167358, 25.767141, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 0
	tmp_objid = CreateDynamicObject(19981, 1983.978271, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(1575, 1988.313232, 1195.861816, 26.486189, 77.500031, 0.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 1355, "break_s_bins", "CJ_RED_LEATHER", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.578369, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2662, 1989.225952, 1191.689819, 29.406652, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(19981, 1984.078247, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	CreateDynamicObject(18701, 1984.370728, 1199.127319, 25.687140, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 0
	tmp_objid = CreateDynamicObject(19981, 1983.678345, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.178223, 1199.425049, 28.535713, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2662, 1989.225952, 1192.860474, 29.406652, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(19981, 1983.778320, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2930, 1989.407349, 1191.248779, 28.543633, 0.000000, 0.000037, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.279053, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2930, 1989.405396, 1192.878174, 28.543633, 0.000000, 0.000029, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.878296, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1983.978271, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.379028, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19939, 1985.478516, 1198.890747, 26.546616, -0.000029, 90.000008, -89.999947, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampwhite", 0);
	tmp_objid = CreateDynamicObject(19353, 1988.538208, 1192.515381, 31.500202, 0.000007, -0.000014, 179.999634, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 13077, "cunte_bar1", "black16", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.078247, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.479004, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(18763, 1987.880005, 1188.552002, 31.218781, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(19981, 1984.178223, 1199.425049, 25.865709, 0.000007, 0.000007, 89.999977, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.578979, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(18763, 1987.880005, 1188.552002, 23.888754, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(2714, 1985.148438, 1199.248047, 27.576431, -0.000062, 0.000201, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "HBO", 130, "Century Gothic", 90, 1, 0xFFCDCDCD, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.279053, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19445, 1984.605103, 1199.509399, 27.601490, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampblack", 0);
	tmp_objid = CreateDynamicObject(2714, 1984.988281, 1199.267700, 28.633438, -0.000062, 0.000172, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, SERVER_SITE, 130, "Arial", 43, 0, 0xFF363636, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.678955, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2714, 1985.149170, 1199.267822, 27.566429, -0.000062, 0.000201, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "g", 100, "Webdings", 120, 0, 0xFF0A0A0A, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2247, 1988.990479, 1194.992432, 26.439013, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 10839, "aircarpkbarier_sfse", "glass_64a", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.379028, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2714, 1985.244141, 1199.247925, 27.572428, -0.000062, 0.000201, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "n", 130, "Webdings", 30, 1, 0xFFCDCDCD, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2930, 1989.409302, 1191.250732, 29.591661, 0.000000, 0.000045, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.778931, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2662, 1989.225952, 1194.041138, 29.406652, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(2930, 1989.407349, 1192.880127, 29.591661, 0.000000, 0.000037, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2869, 1984.241699, 1199.551636, 26.039284, 0.000006, 0.000003, 57.899994, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1970, "dinerseat1", "diner_seat1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.479004, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2869, 1984.371826, 1199.501587, 25.969282, 0.000012, 0.000007, 57.899994, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1970, "dinerseat1", "diner_seat1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.878906, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2811, 1989.045166, 1194.903931, 26.030447, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.578979, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2662, 1984.704102, 1199.361328, 29.406652, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(19981, 1984.978882, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.678955, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.078857, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.778931, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(11735, 1986.003662, 1198.870972, 26.268209, 22.200020, 0.000000, -89.999977, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 1246, "icons", "pill_32", 0);
	tmp_objid = CreateDynamicObject(2930, 1989.403442, 1194.506592, 28.543633, 0.000000, 0.000022, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.178833, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.878906, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1984.978882, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.278809, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2714, 1985.709229, 1199.258423, 27.570435, -0.000062, 0.000201, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "NETFLIX", 120, "Arial Black", 50, 1, 0xFF65000B, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2714, 1985.708496, 1199.267944, 27.566429, -0.000062, 0.000201, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "g", 100, "Webdings", 120, 0, 0xFFFFFFFF, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.078857, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19353, 1988.538208, 1194.546509, 31.500202, 0.000007, -0.000014, 179.999634, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 13077, "cunte_bar1", "black16", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.378784, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.178833, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2714, 1985.819092, 1199.267944, 28.163429, -0.000062, 0.000224, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, SERVER_NAME, 130, "Calibri", 85, 1, 0xFFCDCDCD, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.478760, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2707, 1988.512085, 1196.272705, 29.744587, -0.000096, -0.000059, -89.999077, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(18749, 1986.005005, 1199.182617, 26.863951, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1564, "ab_jetlite", "CJ_BULLETBRASS", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1564, "ab_jetlite", "CJ_BULLETBRASS", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.278809, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2930, 1989.405396, 1194.508545, 29.591661, 0.000000, 0.000029, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.578735, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19483, 1985.896484, 1199.308594, 27.798788, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 17588, "lae2coast_alpha", "LAShad1", 0);
	tmp_objid = CreateDynamicObject(11685, 1988.087891, 1197.152954, 25.868624, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(1575, 1988.313232, 1197.042603, 26.486189, 77.500031, 0.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 1355, "break_s_bins", "CJ_RED_LEATHER", 0);
	tmp_objid = CreateDynamicObject(2714, 1985.988892, 1199.267822, 27.913422, -0.000062, 0.000203, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "Musica de Login de Natal "SERVER_TAG"", 130, "Arial", 30, 0, 0xFF363636, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2707, 1988.512085, 1196.422607, 29.744587, -0.000096, -0.000059, -89.999077, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.378784, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2714, 1986.001099, 1199.273438, 27.343430, -0.000062, 0.000195, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "SAMSUNG", 130, "Arial Black", 25, 0, 0xFF363636, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(11683, 1988.018921, 1197.281860, 25.864622, 0.000000, 0.000000, 720.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 13816, "lahills_safe1", "white_girdr", 0);
	tmp_objid = CreateDynamicObject(19939, 1986.489258, 1198.890747, 26.546616, -0.000029, 90.000008, -89.999947, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampwhite", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.678711, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19483, 1986.002930, 1199.290161, 28.049889, 0.000165, 0.000065, 89.999619, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 65535, "none", "none", 0xFFFF99FF);
	SetDynamicObjectMaterial(tmp_objid, 0, 17555, "eastbeach3c_lae2", "gradient128", 0xFF663333);
	tmp_objid = CreateDynamicObject(2714, 1986.064331, 1199.266113, 27.818710, -0.000065, 0.000174, -0.000218, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "9;8 {FF3030}4", 130, "Webdings", 50, 0, 0xFFFFFFFF, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19480, "signsurf", "sign", 0);
	tmp_objid = CreateDynamicObject(1719, 1985.452637, 1199.607178, 27.014299, -0.000007, 0.000000, -89.999977, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1736, "cj_ammo", "CJ_SPEAKER_c", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1736, "cj_ammo", "CJ_SPEAKER_c", 0);
	tmp_objid = CreateDynamicObject(19172, 1986.005615, 1199.310059, 28.051941, -0.000062, 0.000172, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 15040, "cuntcuts", "GB_phone02", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampblack", 0xFFCDCDCD);
	tmp_objid = CreateDynamicObject(19981, 1985.478760, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.778687, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19869, 1989.327148, 1195.680420, 27.513948, 0.000000, 89.999939, 89.999619, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 10973, "mall_sfse", "ws_grilleshade", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19297, "matlights", "invisible", 0);
	tmp_objid = CreateDynamicObject(2707, 1986.617676, 1198.631958, 29.744587, -0.000067, -0.000049, -179.999176, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.578735, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.878662, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19937, 1984.913086, 1199.905396, 26.558233, -0.000029, 90.000008, -89.999947, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19800, "lsacarpark1", "dt_officewall1", 0);
	tmp_objid = CreateDynamicObject(2714, 1986.259277, 1199.258301, 27.570435, -0.000062, 0.000201, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "FOX", 130, "Arial Black", 80, 0, 0xFFCDCDCD, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19937, 1984.914063, 1199.907349, 26.528234, -0.000029, 90.000008, -89.999947, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19800, "lsacarpark1", "dt_officewall1", 0);
	tmp_objid = CreateDynamicObject(19426, 1986.033813, 1199.409302, 27.741493, 90.000000, 180.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14865, "gf2", "mp_bobbie_carpwhite", 0);
	tmp_objid = CreateDynamicObject(19426, 1986.031860, 1199.413208, 27.739492, 90.000000, 180.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 10101, "2notherbuildsfe", "ferry_build14", 0);
	tmp_objid = CreateDynamicObject(2714, 1986.239380, 1199.257935, 28.223431, -0.000062, 0.000224, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, ".com.br", 130, "Arial Black", 65, 0, 0xFF000000, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2714, 1986.269287, 1199.267944, 27.566429, -0.000062, 0.000201, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "g", 100, "Webdings", 120, 0, 0xFF0A0A0A, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.678711, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2714, 1986.249268, 1199.266357, 28.223421, -0.000062, 0.000224, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "G", 140, "GTAWEAPON3", 115, 0, 0xFFFFC200, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2714, 1986.252319, 1199.267822, 28.223421, -0.000062, 0.000224, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "G", 140, "GTAWEAPON3", 127, 0, 0xFF7B6115, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19426, 1986.033813, 1199.409302, 28.331507, 90.000000, 180.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14865, "gf2", "mp_bobbie_carpwhite", 0);
	tmp_objid = CreateDynamicObject(19426, 1986.031860, 1199.413208, 28.329506, 90.000000, 180.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 10101, "2notherbuildsfe", "ferry_build14", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.978638, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2707, 1986.767578, 1198.631958, 29.744587, -0.000067, -0.000049, -179.999176, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.778687, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(1719, 1985.802002, 1199.607178, 27.014299, -0.000007, 0.000000, -89.999977, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1736, "cj_ammo", "CJ_SPEAKER_c", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1736, "cj_ammo", "CJ_SPEAKER_c", 0);
	tmp_objid = CreateDynamicObject(19981, 1986.078613, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2662, 1989.225952, 1195.772217, 29.406652, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(19981, 1985.878662, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19981, 1986.178589, 1199.425049, 28.535713, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19445, 1984.605103, 1199.509399, 31.061510, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampblack", 0);
	tmp_objid = CreateDynamicObject(19981, 1985.978638, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19479, 1989.346436, 1196.036987, 26.846189, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19941, "goldbar1", "chrome", 0x90FFFFFF);
	tmp_objid = CreateDynamicObject(19353, 1985.912842, 1198.605835, 31.500202, 0.000000, 0.000022, 89.999916, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 13077, "cunte_bar1", "black16", 0);
	tmp_objid = CreateDynamicObject(19981, 1986.078613, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2662, 1986.154541, 1199.361328, 29.406652, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(11735, 1987.014282, 1198.870972, 26.268209, 22.200003, 0.000000, -89.999931, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 1246, "icons", "pill_32", 0);
	tmp_objid = CreateDynamicObject(1719, 1986.163330, 1199.607178, 27.014299, -0.000007, 0.000000, -89.999977, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1736, "cj_ammo", "CJ_SPEAKER_c", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1736, "cj_ammo", "CJ_SPEAKER_c", 0);
	tmp_objid = CreateDynamicObject(19981, 1986.178589, 1199.425049, 25.865709, 0.000000, 0.000007, 450.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2930, 1989.401489, 1196.136230, 28.543633, 0.000000, 0.000014, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19604, 1984.389038, 1199.390869, 31.814207, 180.000000, 90.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14561, "triad_neon", "kbneon", 0x90000000);
	tmp_objid = CreateDynamicObject(19445, 1989.388550, 1194.672729, 24.166018, 0.000000, 0.000000, 540.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	tmp_objid = CreateDynamicObject(2714, 1986.829102, 1199.257446, 27.566422, -0.000062, 0.000201, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "YouTube", 130, "Arial", 55, 1, 0xFFCDCDCD, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2714, 1986.828735, 1199.268066, 27.566429, -0.000062, 0.000201, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "g", 100, "Webdings", 120, 0, 0xFF65000B, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19937, 1985.854736, 1199.906372, 26.530235, -0.000029, 90.000008, -89.999947, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19800, "lsacarpark1", "dt_officewall1", 0);
	tmp_objid = CreateDynamicObject(19604, 1989.249390, 1194.391113, 31.814207, 180.000000, 90.000000, 180.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14561, "triad_neon", "kbneon", 0x90000000);
	tmp_objid = CreateDynamicObject(19445, 1989.346191, 1194.839355, 31.341488, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 2669, "cj_chris", "Bow_Fence_Metal", 0);
	tmp_objid = CreateDynamicObject(2930, 1989.403442, 1196.138184, 29.591661, 0.000000, 0.000022, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(1719, 1986.522705, 1199.607178, 27.014299, -0.000007, 0.000000, -89.999977, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1736, "cj_ammo", "CJ_SPEAKER_c", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 1736, "cj_ammo", "CJ_SPEAKER_c", 0);
	tmp_objid = CreateDynamicObject(2714, 1986.979370, 1199.267334, 28.633438, -0.000062, 0.000172, 0.000059, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 0, "SUN 12:45", 130, "Arial", 43, 0, 0xFF363636, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19604, 1989.289673, 1195.002319, 23.784176, 180.000000, 90.000000, 360.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14561, "triad_neon", "kbneon", 0x90000000);
	tmp_objid = CreateDynamicObject(19482, 1985.437012, 1200.109375, 25.878759, 180.000000, 90.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 17588, "lae2coast_alpha", "LAShad1", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.406250, 1198.034790, 27.024845, 0.000096, -0.000025, 134.999802, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil4-128x128", 0);
	tmp_objid = CreateDynamicObject(19939, 1987.500244, 1198.890747, 26.546616, -0.000029, 90.000008, 270.000061, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampwhite", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.254639, 1198.262329, 27.524845, 0.000109, 0.000009, 112.499672, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19937, 1986.143555, 1199.905396, 26.556232, -0.000029, 90.000008, -89.999947, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19800, "lsacarpark1", "dt_officewall1", 0);
	tmp_objid = CreateDynamicObject(19527, 1985.997192, 1200.052979, 27.999176, 6.200168, 270.000000, 89.999458, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterialText(tmp_objid, 1, "HAPPY NEW YEAR", 100, "Arial", 27, 1, 0xFFFFFFFF, 0, 1);
	SetDynamicObjectMaterial(tmp_objid, 0, 19480, "signsurf", "sign", 0);
	tmp_objid = CreateDynamicObject(19797, 1987.167358, 1199.296997, 27.365000, -0.000062, 90.000214, 0.000134, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "g", 130, "Webdings", 30, 1, 0xFFFF0000, 0, 1);
	tmp_objid = CreateDynamicObject(19574, 1988.633545, 1197.883423, 27.524845, 0.000077, -0.000056, 157.499298, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil3-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.477051, 1198.105591, 28.024845, -0.000079, 0.000022, -45.000004, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil5-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1987.393311, 1199.183960, 26.878893, 0.000080, 0.000000, 89.999748, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 12855, "cunte_cop", "sw_copgrass01", 0);
	tmp_objid = CreateDynamicObject(19835, 1987.393311, 1199.183960, 26.768776, 0.000000, 0.000075, 0.000000, -1, -1, -1, 300.0); // 4
	SetDynamicObjectMaterial(tmp_objid, 3, 2514, "cj_bathroom", "cj_toilet", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 2514, "cj_bathroom", "cj_toilet", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 2514, "cj_bathroom", "cj_toilet", 0);
	tmp_objid = CreateDynamicObject(2707, 1988.512085, 1197.792725, 29.744587, -0.000090, -0.000059, -89.999092, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2662, 1989.225952, 1196.941772, 29.406652, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(19574, 1988.347290, 1198.300415, 26.524845, 0.000103, 0.000003, 112.499725, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.201416, 1198.529785, 27.024845, 0.000096, 0.000036, 89.999672, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.671997, 1197.975708, 26.524845, 0.000072, -0.000060, 157.499573, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19814, 1987.644043, 1199.104004, 26.913364, -0.000029, 89.999908, -90.000420, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19607, "enexmarkers", "enexmarker1-2", 0);
	tmp_objid = CreateDynamicObject(19918, 1988.419434, 1198.161743, 25.857853, 0.000094, -0.000039, 133.999832, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19058, "xmasboxes", "wrappingpaper16", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(2707, 1988.512085, 1197.942627, 29.744587, -0.000090, -0.000059, -89.999092, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 1560, "7_11_door", "CJ_CHROME2", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.901367, 1197.830200, 27.024845, 0.000045, -0.000076, 179.999344, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.301270, 1198.529907, 28.024845, -0.000074, -0.000044, -90.000031, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil3-128x128", 0);
	tmp_objid = CreateDynamicObject(19353, 1987.013916, 1198.605835, 31.500202, 0.000000, 0.000022, 89.999916, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 13077, "cunte_bar1", "black16", 0);
	tmp_objid = CreateDynamicObject(19894, 1987.640137, 1199.171143, 26.914097, 0.000086, 89.999962, 179.999496, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19424, "headphones", "headphones02", 0);
	tmp_objid = CreateDynamicObject(19918, 1988.356079, 1198.354614, 26.077946, 0.000102, 0.000004, 106.999718, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19058, "xmasboxes", "wrappingpaper1", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(19574, 1988.901367, 1197.929810, 28.024845, 0.000051, -0.000074, 179.999344, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19894, 1987.679688, 1199.171143, 26.914097, 0.000086, 89.999962, 179.999496, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19424, "headphones", "headphones02", 0);
	tmp_objid = CreateDynamicObject(19353, 1988.538208, 1197.087891, 31.500202, 0.000007, 0.000000, 179.999725, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 13077, "cunte_bar1", "black16", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.531738, 1198.377075, 28.524845, -0.000088, -0.000007, -67.499939, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(2854, 1987.508789, 1199.374512, 26.940586, 72.199936, -89.899887, -0.300273, -1, -1, -1, 300.0); // 6
	SetDynamicObjectMaterial(tmp_objid, 5, 2813, "gb_books01", "GB_novels09", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.748291, 1198.160278, 28.524845, 0.000077, -0.000056, 157.499344, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil2-128x128", 0);
	tmp_objid = CreateDynamicObject(2854, 1987.548828, 1199.374390, 26.940586, 72.199936, -89.899887, -0.300273, -1, -1, -1, 300.0); // 6
	SetDynamicObjectMaterial(tmp_objid, 5, 2813, "gb_books01", "GB_novels03", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.254639, 1198.797974, 27.524845, -0.000052, -0.000048, -112.499939, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil4-128x128", 0);
	tmp_objid = CreateDynamicObject(19094, 1987.869751, 1198.964233, 25.929548, -17.700014, 270.000000, -0.000068, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 15040, "cuntcuts", "GB_phone02", 0);
	tmp_objid = CreateDynamicObject(2854, 1987.588745, 1199.374268, 26.940586, 72.199936, -89.899887, -0.300273, -1, -1, -1, 300.0); // 6
	SetDynamicObjectMaterial(tmp_objid, 5, 2813, "gb_books01", "GB_novels02", 0);
	SetDynamicObjectMaterial(tmp_objid, 4, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2811, 1987.834595, 1199.185303, 26.830465, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2247, 1987.779907, 1199.273804, 27.239031, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 10839, "aircarpkbarier_sfse", "glass_64a", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19918, 1988.319458, 1198.573853, 25.857853, 0.000096, 0.000037, 88.299675, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19058, "xmasboxes", "wrappingpaper20", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(19574, 1989.169067, 1197.883301, 27.524845, 0.000011, -0.000080, -157.500046, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil5-128x128", 0);
	tmp_objid = CreateDynamicObject(19797, 1987.845093, 1199.141724, 26.091551, -0.000039, 90.000175, -0.000036, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "---", 130, "Webdings", 30, 1, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(19574, 1988.347290, 1198.759399, 26.524845, -0.000059, -0.000055, -112.499878, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil2-128x128", 0);
	tmp_objid = CreateDynamicObject(19937, 1987.054443, 1199.905396, 26.558233, -0.000029, 90.000008, -89.999947, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19800, "lsacarpark1", "dt_officewall1", 0);
	tmp_objid = CreateDynamicObject(19937, 1987.055908, 1199.907349, 26.528234, -0.000029, 90.000008, -89.999947, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19800, "lsacarpark1", "dt_officewall1", 0);
	tmp_objid = CreateDynamicObject(2662, 1987.615356, 1199.361328, 29.406652, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(19574, 1988.531738, 1198.683228, 28.524845, -0.000056, -0.000070, -112.499939, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil5-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.130859, 1197.975708, 26.524845, 0.000006, -0.000086, -157.500046, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil4-128x128", 0);
	tmp_objid = CreateDynamicObject(2040, 1987.890747, 1199.219360, 25.986952, 0.000094, -179.999985, 89.999664, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18868, "mobilephone4", "mobilephone4-1", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.054443, 1198.160278, 28.524845, -0.000003, 0.000097, 22.499992, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(2930, 1989.399536, 1197.765869, 28.543633, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.701416, 1198.529907, 29.024845, 0.000096, 0.000036, 89.999672, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil2-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.901367, 1198.330200, 29.024845, 0.000036, -0.000089, 179.999344, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil4-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.477051, 1198.954224, 28.024845, 0.000027, 0.000090, 44.999985, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19445, 1975.104248, 1199.509399, 27.601490, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampblack", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.406250, 1199.025024, 27.024845, -0.000024, -0.000073, -135.000259, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(627, 1988.901367, 1198.529907, 27.647648, -0.000083, 0.000044, -44.999939, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 654, "gta_tree_oldpine", "tree19Mi", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(627, 1988.901367, 1198.529907, 27.647648, -0.000028, 0.000092, -0.000136, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 654, "gta_tree_oldpine", "tree19Mi", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(627, 1988.901367, 1198.529907, 27.647648, -0.000059, 0.000075, -22.500053, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 654, "gta_tree_oldpine", "tree19Mi", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(627, 1988.901367, 1198.529907, 27.647648, -0.000096, 0.000007, -67.499786, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 654, "gta_tree_oldpine", "tree19Mi", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(627, 1988.901367, 1198.529907, 27.647648, 0.000103, -0.000003, 112.499725, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 654, "gta_tree_oldpine", "tree19Mi", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(627, 1988.901367, 1198.529907, 27.647648, 0.000069, -0.000075, 157.499573, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 654, "gta_tree_oldpine", "tree19Mi", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(627, 1988.901367, 1198.529907, 27.647648, 0.000093, -0.000040, 134.999802, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 654, "gta_tree_oldpine", "tree19Mi", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(627, 1988.901367, 1198.529907, 27.647648, 0.000096, 0.000036, 89.999672, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 5462, "glenpark6_lae", "dirty256", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 1731, "cj_lighting", "cj_plantpot", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 654, "gta_tree_oldpine", "tree19Mi", 0xFFFFFFFF);
	tmp_objid = CreateDynamicObject(2260, 1988.561035, 1198.914673, 27.676891, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 1, 2266, "picture_frame", "CJ_PAINTING23", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.325684, 1198.105591, 28.024845, 0.000027, 0.000090, 44.999985, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil2-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.396484, 1198.034790, 27.024845, -0.000024, -0.000073, -135.000259, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil3-128x128", 0);
	tmp_objid = CreateDynamicObject(2930, 1989.401489, 1197.767822, 29.591661, 0.000000, 0.000014, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(2662, 1989.225952, 1198.112915, 29.406652, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(2691, 1988.733154, 1198.724731, 25.901861, 270.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "sphere", 0);
	tmp_objid = CreateDynamicObject(1247, 1988.901367, 1198.529907, 29.447697, 0.000095, 0.000029, 134.999695, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18835, "mickytextures", "wood051", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.748291, 1198.899414, 28.524845, -0.000003, 0.000097, 22.499992, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil3-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.270996, 1198.377075, 28.524845, -0.000056, -0.000070, -112.499939, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.901367, 1198.730103, 29.024845, 0.000036, -0.000089, 179.999344, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil5-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.633667, 1199.176880, 27.524845, 0.000011, -0.000080, -157.500046, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.101318, 1198.529907, 29.024845, 0.000096, 0.000036, 89.999672, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil3-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.671997, 1199.084106, 26.524845, 0.000006, -0.000086, -157.500046, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.548096, 1198.262207, 27.524845, -0.000052, -0.000048, -112.499939, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(2654, 1988.751099, 1199.049927, 26.067936, -0.000097, -0.000030, -87.499634, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 2, 19058, "xmasboxes", "wrappingpaper4-2", 0);
	SetDynamicObjectMaterial(tmp_objid, 1, 19058, "xmasboxes", "wrappingpaper16", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19058, "xmasboxes", "wrappingpaper28", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.054443, 1198.899536, 28.524845, 0.000077, -0.000056, 157.499344, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.901367, 1199.130005, 28.024845, 0.000051, -0.000074, 179.999344, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil4-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.270996, 1198.683228, 28.524845, -0.000088, -0.000007, -67.499939, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil4-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.501465, 1198.529907, 28.024845, -0.000074, -0.000044, -90.000031, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1988.901367, 1199.230103, 27.024845, 0.000045, -0.000076, 179.999344, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil2-128x128", 0);
	tmp_objid = CreateDynamicObject(19353, 1987.798706, 1199.482544, 24.166018, 0.000000, 0.000000, 450.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.601318, 1198.529907, 27.024845, 0.000096, 0.000036, 89.999672, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil5-128x128", 0);
	tmp_objid = CreateDynamicObject(19445, 1975.094971, 1199.509399, 31.061510, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 18996, "mattextures", "sampblack", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.130859, 1199.084106, 26.524845, 0.000072, -0.000060, 157.499573, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil5-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.325684, 1198.954224, 28.024845, -0.000079, 0.000022, -45.000004, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.169189, 1199.176880, 27.524845, 0.000077, -0.000056, 157.499298, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.548096, 1198.797974, 27.524845, 0.000109, 0.000009, 112.499672, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil2-128x128", 0);
	tmp_objid = CreateDynamicObject(19574, 1989.396484, 1199.025024, 27.024845, 0.000096, -0.000025, 134.999802, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 19063, "xmasorbs", "foil1-128x128", 0);
	tmp_objid = CreateDynamicObject(2662, 1989.076416, 1199.361328, 29.406652, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterialText(tmp_objid, 0, "T", 130, "Wingdings", 199, 0, 0xFFFFFFFF, 0, 1);
	tmp_objid = CreateDynamicObject(18763, 1987.691772, 1200.895508, 27.668758, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(2930, 1989.397583, 1199.395508, 28.543633, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(18763, 1987.829956, 1200.893555, 27.668758, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.0); // 1
	SetDynamicObjectMaterial(tmp_objid, 0, 5461, "glenpark6d_lae", "tiledwall01_LA", 0xFFB89351);
	tmp_objid = CreateDynamicObject(2930, 1989.399536, 1199.397461, 29.591661, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.0); // 2
	SetDynamicObjectMaterial(tmp_objid, 1, 642, "canopy", "wood02", 0xFFFFFFFF);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	tmp_objid = CreateDynamicObject(14788, 1989.241211, 1201.116211, 28.107922, 0.000000, 0.000014, 180.000000, -1, -1, -1, 300.0); // 3
	SetDynamicObjectMaterial(tmp_objid, 3, 19962, "samproadsigns", "materialtext1", 0);
	SetDynamicObjectMaterial(tmp_objid, 2, 2823, "gb_kitchtake", "deep_red64", 0);
	SetDynamicObjectMaterial(tmp_objid, 0, 19962, "samproadsigns", "materialtext1", 0);
	CreateDynamicObject(18863, 1984.170532, 1223.662598, 54.370598, 0.000000, -42.100002, 125.400024, -1, -1, -1, 300.0); // 0

    printf("[MAPA %d]: Tela de login... Carregado com sucesso!", gm_count[COUNT_CREATEMAP]);
    gm_count[COUNT_CREATEMAP]++;
}