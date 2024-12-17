#define         _JAIL_SYSTEM_ON             true                // Significa que o sistema está ativo (caso o módulo não seja adicionado na main, esse define fica em 0)


stock CreateMap_PrisaoLaSante() // Mapa La Sante
{
	// Exterior [4]
	CreateDynamicObject(3852,1802.4,-1577,11.5,0,0,104.25);
	CreateDynamicObject(3852,1801.5,-1573.6,11.5,0,0,104.249);
	CreateDynamicObject(3034,1795,-1584.8,14.8,0,0,40.5);
	CreateDynamicObject(3034,1787.7,-1590.9,14.8,0,0,39.996);
	
	// Interior
	CreateDynamicObject(1533, 278.37329, 1934.93555, 1061.08423,   0.00000, 0.00000, 90.00000); // Porta
	CreateDynamicObject(1616, 281.12408, 1950.01697, 1068.41638,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(1616, 280.90945, 1926.08069, 1068.47693,   0.00000, 0.00000, -88.08003);
	CreateDynamicObject(1616, 327.59659, 1949.00708, 1068.43494,   0.00000, 0.00000, 83.46007);
	CreateDynamicObject(1616, 326.90253, 1926.55566, 1068.43494,   0.00000, 0.00000, -19.44002);
	CreateDynamicObject(1616, 273.66873, 1933.80725, 1064.41516,   0.00000, 0.00000, -85.19994);
	CreateDynamicObject(1616, 1812.17627, -1581.69556, 24.71440,   0.00000, -20.00000, -122.57999);
	CreateDynamicObject(1616, 1822.43518, -1543.95105, 19.98216,   0.00000, 0.00000, 132.95999);
	CreateDynamicObject(1616, 1831.41797, -1600.14270, 21.30501,   0.00000, 0.00000, -34.25996);
	
	new santeTmpObj;
	santeTmpObj = CreateDynamicObject(18981, 315.7308, 1937.9787, 1060.5924, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	CreateDynamicObject(19393, 323.3952, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 326.6152, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 313.7839, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 320.1838, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 316.9840, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 304.1838, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 307.3840, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	santeTmpObj = CreateDynamicObject(18981, 290.7550, 1937.9787, 1060.5924, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	CreateDynamicObject(19393, 310.5840, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 300.9840, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	santeTmpObj = CreateDynamicObject(19545, 300.1506, 1919.1677, 1068.1463, 0.0000, 90.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	CreateDynamicObject(19364, 294.5840, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 291.3840, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 288.1838, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 284.9840, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 281.7839, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 323.3952, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 326.6152, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 313.7839, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 320.1838, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 316.9840, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 304.1838, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 307.3840, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 310.5840, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 300.9840, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 297.7839, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 294.5840, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 291.3840, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 288.1838, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 284.9840, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 281.7839, 1925.6240, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 328.1350, 1947.6654, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19393, 328.1321, 1944.4530, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 328.1350, 1941.2530, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19393, 328.1321, 1938.0531, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 328.1350, 1934.8531, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19393, 328.1321, 1931.6529, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 328.1350, 1928.4531, 1062.8021, 0.0000, 0.0000, 0.0000); //
	santeTmpObj = CreateDynamicObject(18981, 315.7297, 1959.7098, 1065.0539, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	CreateDynamicObject(19393, 323.3952, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 326.6152, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 313.7839, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 320.1838, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 316.9840, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 304.1838, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 307.3840, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 310.5840, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 300.9840, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 297.7839, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 294.5840, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 291.3840, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 288.1838, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 284.9840, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 281.7839, 1950.3603, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 323.3952, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 326.6152, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 313.7839, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 320.1838, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 316.9840, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 304.1838, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 307.3840, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 310.5840, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 300.9840, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 297.7839, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 294.5840, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 291.3840, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 288.1838, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19393, 284.9840, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 281.7839, 1925.6240, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 328.1350, 1947.6654, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19393, 328.1321, 1944.4530, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 328.1350, 1941.2530, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19393, 328.1321, 1938.0531, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 328.1350, 1934.8531, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19393, 328.1321, 1931.6529, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 328.1350, 1928.4531, 1067.2790, 0.0000, 0.0000, 0.0000); //
	santeTmpObj = CreateDynamicObject(18981, 290.7387, 1959.7098, 1065.0539, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	santeTmpObj = CreateDynamicObject(18981, 315.7297, 1916.4215, 1065.0539, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	santeTmpObj = CreateDynamicObject(18981, 290.7387, 1916.4215, 1065.0539, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	santeTmpObj = CreateDynamicObject(18981, 337.4522, 1938.0119, 1065.0500, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	CreateDynamicObject(19302, 323.4317, 1925.6688, 1066.7805, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 317.0317, 1925.6688, 1066.7805, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 310.6317, 1925.6688, 1066.7805, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 304.2315, 1925.6688, 1066.7805, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 297.8316, 1925.6688, 1066.7805, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 291.4317, 1925.6688, 1066.7805, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 285.0317, 1925.6688, 1066.7805, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 285.0317, 1925.6688, 1062.3208, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 323.4317, 1925.6688, 1062.3208, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 317.0317, 1925.6688, 1062.3208, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 310.6317, 1925.6688, 1062.3208, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 304.2315, 1925.6688, 1062.3208, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 297.8316, 1925.6688, 1062.3208, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 291.4317, 1925.6688, 1062.3208, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 285.0317, 1925.6688, 1062.3208, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(19302, 285.0317, 1950.3239, 1066.7805, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 323.4317, 1950.3239, 1062.3208, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 317.0317, 1950.3239, 1062.3208, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 310.6317, 1950.3239, 1062.3208, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 304.2315, 1950.3239, 1062.3208, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 297.8316, 1950.3239, 1062.3208, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 291.4317, 1950.3239, 1062.3208, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 285.0317, 1950.3239, 1062.3208, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 285.0317, 1950.3239, 1062.3208, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 323.4317, 1950.3239, 1066.7805, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 317.0317, 1950.3239, 1066.7805, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 310.6317, 1950.3239, 1066.7805, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 304.2315, 1950.3239, 1066.7805, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 297.8316, 1950.3239, 1066.7805, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 291.4317, 1950.3239, 1066.7805, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19302, 328.1166, 1944.5228, 1066.7805, 0.0000, 0.0000, -90.0000); //
	CreateDynamicObject(19302, 328.1166, 1938.1228, 1066.7805, 0.0000, 0.0000, -90.0000); //
	CreateDynamicObject(19302, 328.1166, 1931.7226, 1066.7805, 0.0000, 0.0000, -90.0000); //
	CreateDynamicObject(19302, 328.1166, 1931.7226, 1062.3208, 0.0000, 0.0000, -90.0000); //
	CreateDynamicObject(19302, 328.1166, 1938.1228, 1062.3208, 0.0000, 0.0000, -90.0000); //
	CreateDynamicObject(19302, 328.1166, 1944.5228, 1062.3208, 0.0000, 0.0000, -90.0000); //
	santeTmpObj = CreateDynamicObject(18980, 327.7732, 1926.2635, 1061.0810, 0.0000, 0.0000, 11.0398); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(18980, 327.7731, 1949.8089, 1061.0810, 0.0000, 0.0000, -11.0397); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(2606, 280.8869, 1946.2790, 1062.8907, 0.0000, 0.0000, 87.6600); //
	santeTmpObj = CreateDynamicObject(18981, 290.7550, 1937.9787, 1069.4300, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	santeTmpObj = CreateDynamicObject(18981, 339.4522, 1938.0119, 1060.5904, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	CreateDynamicObject(19364, 286.4913, 1923.9747, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 292.8912, 1923.9747, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 299.2911, 1923.9747, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 305.6913, 1923.9747, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 312.0913, 1923.9747, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 318.4913, 1923.9747, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 325.0913, 1923.9747, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 286.4913, 1920.7607, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 292.8912, 1920.7607, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 299.2911, 1920.7607, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 305.6913, 1920.7607, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 312.0913, 1920.7607, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 318.4913, 1920.7607, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 325.0913, 1920.7607, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 286.4913, 1952.0532, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 292.8912, 1952.0532, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 299.2911, 1952.0532, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 305.6913, 1952.0532, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 312.0913, 1952.0532, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 318.4913, 1952.0532, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 325.0913, 1952.0532, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 286.4913, 1955.2591, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 292.8912, 1955.2591, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 299.2911, 1955.2591, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 305.6913, 1955.2591, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 312.0913, 1955.2591, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 318.4913, 1955.2591, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 325.0913, 1955.2591, 1067.2790, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 286.4913, 1923.9747, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 292.8912, 1923.9747, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 299.2911, 1923.9747, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 305.6913, 1923.9747, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 312.0913, 1923.9747, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 318.4913, 1923.9747, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 325.0913, 1923.9747, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 286.4913, 1920.7607, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 292.8912, 1920.7607, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 299.2911, 1920.7607, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 305.6913, 1920.7607, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 312.0913, 1920.7607, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 318.4913, 1920.7607, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 325.0913, 1920.7607, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 286.4913, 1952.0532, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 292.8912, 1952.0532, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 299.2911, 1952.0532, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 305.6913, 1952.0532, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 312.0913, 1952.0532, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 318.4913, 1952.0532, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 325.0913, 1952.0532, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 286.4913, 1955.2591, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 292.8912, 1955.2591, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 299.2911, 1955.2591, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 305.6913, 1955.2591, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 312.0913, 1955.2591, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 318.4913, 1955.2591, 1062.8021, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19364, 325.0913, 1955.2591, 1062.8021, 0.0000, 0.0000, 0.0000); //
	santeTmpObj = CreateDynamicObject(18981, 315.7297, 1916.4215, 1060.5904, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	santeTmpObj = CreateDynamicObject(18981, 290.7387, 1916.4215, 1060.5904, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	santeTmpObj = CreateDynamicObject(18981, 315.7297, 1959.7098, 1060.5904, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	santeTmpObj = CreateDynamicObject(18981, 290.7387, 1959.7098, 1060.5904, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	santeTmpObj = CreateDynamicObject(18767, 319.8507, 1949.7131, 1060.6469, 0.0000, 0.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
	santeTmpObj = CreateDynamicObject(19545, 301.9389, 1956.5273, 1068.3322, 0.0000, 90.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(19545, 298.1463, 1957.8049, 1068.9200, 0.0000, 0.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	santeTmpObj = CreateDynamicObject(19545, 301.1976, 1918.0307, 1068.9200, 0.0000, 0.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	CreateDynamicObject(19364, 329.7944, 1933.2258, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 329.7944, 1939.6258, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 329.7944, 1946.0257, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 329.7944, 1926.8258, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 333.0061, 1946.0257, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 333.0061, 1939.6258, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 333.0061, 1933.2258, 1067.2790, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(19364, 333.0061, 1926.8258, 1067.2790, 0.0000, 0.0000, 90.0000); //
	santeTmpObj = CreateDynamicObject(19545, 334.5812, 1942.6992, 1068.2049, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(19545, 335.6705, 1938.7851, 1068.9200, 0.0000, 0.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(1216, 274.3392, 1933.7972, 1061.7281, 0.0000, 0.0000, 180.0000); //
	santeTmpObj = CreateDynamicObject(1969, 288.3955, 1946.4575, 1061.6031, 0.0000, 0.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 1, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	CreateDynamicObject(3657, 277.6306, 1939.6744, 1061.4753, 0.0000, 0.0000, -90.0000); //
	CreateDynamicObject(2172, 277.6856, 1943.7440, 1061.0349, 0.0000, 0.0000, -90.0000); //MED_OFFICE2_DESK_1
	CreateDynamicObject(955, 273.6963, 1949.6566, 1061.4498, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(1216, 276.0892, 1933.7972, 1061.7281, 0.0000, 0.0000, 180.0000); //
	CreateDynamicObject(18766, 272.3228, 1935.4908, 1061.1867, 0.0000, 0.0000, 90.0000); //Concrete10mx1mx5m
	CreateDynamicObject(3657, 277.6306, 1946.7170, 1061.4753, 0.0000, 0.0000, -90.0000); //
	santeTmpObj = CreateDynamicObject(19545, 281.3031, 1903.5670, 1068.0677, 0.0000, 90.0000, 1.9198); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(18762, 278.7538, 1934.4586, 1063.5052, 0.0000, 0.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(18762, 279.7510, 1934.4533, 1063.5052, 0.0000, 0.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(18762, 278.7538, 1936.9497, 1063.5052, 0.0000, 0.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(18762, 279.7510, 1936.9497, 1063.5052, 0.0000, 0.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(19545, 281.4898, 1968.6025, 1068.0677, 0.0000, 90.0000, -2.3399); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(18766, 278.6228, 1936.9038, 1068.6054, 0.0000, 90.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(18981, 315.7308, 1937.9787, 1069.4300, 0.0000, 90.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 16640, "a51", "ws_stationfloor", 0x00000000);
	santeTmpObj = CreateDynamicObject(982, 286.4959, 1928.8841, 1066.2069, 0.0000, 0.0000, 90.0000); //
	santeTmpObj = CreateDynamicObject(982, 312.1134, 1947.2336, 1066.2069, 0.0000, 0.0000, 90.0000); //
	santeTmpObj = CreateDynamicObject(982, 286.4959, 1947.2336, 1066.2069, 0.0000, 0.0000, 90.0000); //
	santeTmpObj = CreateDynamicObject(18766, 279.7556, 1934.9381, 1068.6054, 0.0000, 90.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(18767, 319.8507, 1933.4128, 1060.6469, 0.0000, 0.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
	santeTmpObj = CreateDynamicObject(984, 324.9625, 1937.9140, 1066.1805, 0.0000, 0.0000, 0.0000); //fenceshit2
	santeTmpObj = CreateDynamicObject(18767, 319.8508, 1932.4166, 1060.6469, 0.0000, 0.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
	santeTmpObj = CreateDynamicObject(18767, 319.8507, 1948.7109, 1060.6469, 0.0000, 0.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0x00000000);
	CreateDynamicObject(967, 281.0589, 1938.2413, 1061.0804, 0.0000, 0.0000, -92.3398); //
	CreateDynamicObject(2700, 280.6306, 1938.6297, 1062.8066, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19162, 280.6351, 1937.5057, 1062.4100, 0.0000, -90.0000, -114.8398); //
	CreateDynamicObject(2611, 280.3620, 1940.1285, 1062.6468, 0.0000, 0.0000, 87.6600); //
	CreateDynamicObject(2185, 281.0098, 1942.9145, 1061.0886, 0.0000, 0.0000, -92.3398); //
	CreateDynamicObject(19835, 280.9006, 1942.0909, 1061.9747, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(19835, 280.7361, 1942.2047, 1061.9747, 0.0000, 0.0000, 0.0000); //
	CreateDynamicObject(2342, 280.9132, 1942.7513, 1062.0080, 0.0000, 0.0000, 25.3798); //
	CreateDynamicObject(2412, 280.7807, 1935.2059, 1061.0905, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(2412, 280.7807, 1936.7878, 1061.0905, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(1715, 281.5549, 1941.2177, 1061.0699, 0.0000, 0.0000, -130.1399); //
	CreateDynamicObject(1715, 281.8471, 1943.0135, 1061.0699, 0.0000, 0.0000, -57.9599); //
	CreateDynamicObject(19942, 281.5632, 1937.4604, 1062.5089, 0.0000, 0.0000, -175.3195); //
	CreateDynamicObject(19942, 281.1169, 1941.9320, 1062.0074, 0.0000, 0.0000, 43.2000); //
	CreateDynamicObject(349, 280.2923, 1938.4129, 1061.9710, 0.0000, -40.0000, -83.1000); //
	CreateDynamicObject(2356, 281.5700, 1938.6705, 1061.0886, 0.0000, 0.0000, -204.4196); //
	CreateDynamicObject(2604, 281.0555, 1945.1447, 1061.8625, 0.0000, 0.0000, 87.6600); //
	CreateDynamicObject(11729, 280.9226, 1948.5394, 1061.0903, 0.0000, 0.0000, 87.6600); //
	CreateDynamicObject(19393, 297.7839, 1950.3603, 1062.8021, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(11729, 280.9812, 1949.8955, 1061.0903, 0.0000, 0.0000, 87.6600); //
	CreateDynamicObject(11729, 280.9558, 1949.2137, 1061.0903, 0.0000, 0.0000, 87.6600); //
	santeTmpObj = CreateDynamicObject(1969, 288.3955, 1940.6867, 1061.6031, 0.0000, 0.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 1, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(3578, 285.9841, 1945.1195, 1060.3155, 0.0000, 0.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(3578, 290.3969, 1945.1195, 1060.3155, 0.0000, 0.0000, 90.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 0, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(1969, 288.3955, 1943.6353, 1061.6031, 0.0000, 0.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 1, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	santeTmpObj = CreateDynamicObject(1969, 288.3955, 1949.4592, 1061.6031, 0.0000, 0.0000, 0.0000); //
	SetDynamicObjectMaterial(santeTmpObj, 1, 10756, "airportroads_sfse", "ws_white_wall1", 0xFFD3D3D3);
	CreateDynamicObject(982, 312.1325, 1928.8789, 1066.2069, 0.0000, 0.0000, 90.0000); //
	CreateDynamicObject(18766, 272.3228, 1945.4720, 1061.1867, 0.0000, 0.0000, 90.0000); //Concrete10mx1mx5m
	CreateObject(18036, 266.7094, 1941.6971, 1063.0777, 0.0000, 0.0000, 0.0000); //range_main (chão)
	CreateDynamicObject(19364, 329.79459, 1946.02588, 1067.27917,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19364, 333.00629, 1946.02588, 1062.80212,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19364, 329.79459, 1939.62585, 1062.80212,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19364, 333.00629, 1939.62585, 1062.80212,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19364, 333.00629, 1933.22583, 1062.80212,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19364, 329.79459, 1933.22583, 1062.80212,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19364, 329.79459, 1926.82581, 1062.70862,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(19364, 333.00629, 1926.82581, 1062.80212,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 285.70398, 1920.47876, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 281.42630, 1920.47876, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 286.95581, 1925.01257, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 287.22629, 1920.47876, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 292.10400, 1920.47876, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 293.35580, 1925.01257, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 293.62631, 1920.47876, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 298.50400, 1920.47876, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 299.75580, 1925.01257, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 300.02631, 1920.47876, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 304.90521, 1920.45044, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 306.15579, 1925.01257, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 306.42630, 1920.47876, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 311.30521, 1920.45044, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 312.55579, 1925.01257, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 312.82629, 1920.47876, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 317.70520, 1920.45044, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 318.95581, 1925.01257, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 319.22629, 1920.47876, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 324.10519, 1920.45044, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 285.70398, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 281.62619, 1955.17285, 1061.66772,   0.00000, 0.00000, -3.72000);
	CreateDynamicObject(1771, 287.22629, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 292.10400, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 293.62631, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 298.50400, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 300.02631, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 304.90521, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 306.42630, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 311.30521, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 312.82629, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 317.70520, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 319.22629, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 324.10519, 1955.17786, 1061.66772,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 280.95804, 1925.01257, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 306.15579, 1951.01245, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 318.95581, 1951.01245, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 312.55579, 1951.01245, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 299.75580, 1951.01245, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 293.35580, 1951.01245, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 286.95581, 1951.01245, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 280.95804, 1951.01245, 1061.54810,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 285.70398, 1920.47876, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 281.42630, 1920.47876, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 286.95581, 1925.01257, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 287.22629, 1920.47876, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 292.10400, 1920.47876, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 293.35580, 1925.01257, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 293.62631, 1920.47876, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 298.50400, 1920.47876, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 299.75580, 1925.01257, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 300.02631, 1920.47876, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 304.90521, 1920.45044, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 306.15579, 1925.01257, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 306.42630, 1920.47876, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 311.30521, 1920.45044, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 312.55579, 1925.01257, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 312.82629, 1920.47876, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 317.70520, 1920.45044, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 318.95581, 1925.01257, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 319.22629, 1920.47876, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 324.10519, 1920.45044, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 285.70398, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 281.62619, 1955.17285, 1066.08521,   0.00000, 0.00000, -3.72000);
	CreateDynamicObject(1771, 287.22629, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 292.10400, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 293.62631, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 298.50400, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 300.02631, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 304.90521, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 306.42630, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 311.30521, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 312.82629, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 317.70520, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 319.22629, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1771, 324.10519, 1955.17786, 1066.08521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2602, 280.95804, 1925.01257, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 306.15579, 1951.01245, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 318.95581, 1951.01245, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 312.55579, 1951.01245, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 299.75580, 1951.01245, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 293.35580, 1951.01245, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 286.95581, 1951.01245, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 280.95804, 1951.01245, 1066.07275,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1945.21948, 1061.58752,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1940.38306, 1061.58752,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1938.84241, 1061.58752,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1933.97949, 1061.58752,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1932.43823, 1061.58752,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1927.57214, 1061.58752,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1927.57214, 1066.13025,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1932.43823, 1066.13025,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1933.97949, 1066.13025,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1938.84241, 1066.13025,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1945.21948, 1066.13025,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1771, 333.22861, 1940.38306, 1066.13025,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(2602, 328.73788, 1940.07434, 1061.59863,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2602, 328.73792, 1933.70374, 1061.59863,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2602, 328.73792, 1927.27917, 1061.59863,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2602, 328.73792, 1927.27917, 1066.02478,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2602, 328.73792, 1933.70374, 1066.02478,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(2602, 328.73792, 1940.07434, 1066.02478,   0.00000, 0.00000, 180.00000);
	CreateDynamicObject(19364, 329.79459, 1946.02588, 1062.80212,   0.00000, 0.00000, 90.00000);

	// Lobby - La Sante by ChiLeZiNhO
	new LaSanteInt[86];
	LaSanteInt[0] = CreateObject(19403, 288.1592, -136.7461, 1004.6327, 0.0000, 0.0000, 0.0000); //wall051
	SetObjectMaterial(LaSanteInt[0], 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	LaSanteInt[1] = CreateObject(19389, 288.1495, -139.8671, 1004.6326, 0.0000, 0.0000, 0.0000); //wall037
	SetObjectMaterial(LaSanteInt[1], 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	LaSanteInt[2] = CreateObject(19451, 299.5127, -130.4629, 1004.6326, 0.0000, 0.0000, 0.0000); //wall091
	SetObjectMaterial(LaSanteInt[2], 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	LaSanteInt[3] = CreateObject(19449, 288.1423, -146.1846, 1004.6325, 0.0000, 0.0000, 0.0000); //wall089
	SetObjectMaterial(LaSanteInt[3], 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	LaSanteInt[4] = CreateObject(19451, 299.5127, -140.0628, 1004.6326, 0.0000, 0.0000, 0.0000); //wall091
	SetObjectMaterial(LaSanteInt[4], 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	LaSanteInt[5] = CreateObject(19452, 286.4780, -139.7309, 1003.0032, 0.0000, -90.1000, 0.0000); //wall092
	SetObjectMaterial(LaSanteInt[5], 0, 14652, "ab_trukstpa", "CJ_WOOD6", 0x00000000);
	LaSanteInt[6] = CreateObject(19451, 288.1526, -130.4727, 1004.6326, 0.0000, 0.0000, 0.0000); //wall091
	SetObjectMaterial(LaSanteInt[6], 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	LaSanteInt[7] = CreateObject(19451, 283.4299, -141.4552, 1004.6326, 0.0000, 0.0000, 91.0000); //wall091
	SetObjectMaterial(LaSanteInt[7], 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	LaSanteInt[8] = CreateObject(19451, 281.4756, -136.8545, 1004.6326, 0.0000, 0.0000, -178.4999); //wall091
	SetObjectMaterial(LaSanteInt[8], 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	LaSanteInt[9] = CreateObject(19451, 283.3161, -134.9362, 1004.6326, 0.0000, 0.0000, 91.0000); //wall091
	SetObjectMaterial(LaSanteInt[9], 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	LaSanteInt[10] = CreateObject(1649, 288.2167, -136.7483, 1005.7623, 0.0000, 0.0000, 89.5999); //wglasssmash
	SetObjectMaterial(LaSanteInt[10], 0, 3850, "carshowglass_sfsx", "ws_glass_balustrade_better", 0x00000000);
	LaSanteInt[11] = CreateObject(2949, 281.6833, -140.3401, 1003.0969, 0.0000, 0.0000, -178.1000); //kmb_lockeddoor
	LaSanteInt[12] = CreateObject(19452, 283.0179, -139.7309, 1002.9974, 0.0000, -90.1000, 0.0000); //wall092
	SetObjectMaterial(LaSanteInt[12], 0, 14652, "ab_trukstpa", "CJ_WOOD6", 0x00000000);
	LaSanteInt[13] = CreateObject(2162, 298.9212, -144.6989, 1003.0836, 0.0000, 0.0000, 179.9999); //MED_OFFICE_UNIT_1
	LaSanteInt[14] = CreateObject(2613, 288.2060, -140.1483, 1003.0921, 0.0000, 0.0000, 0.0000); //POLICE_WASTEBIN
	LaSanteInt[15] = CreateObject(2948, 299.4682, -128.1590, 1003.0936, 0.0000, 0.0000, -179.3000); //cr_door_02
	LaSanteInt[16] = CreateObject(1502, 288.1543, -139.0683, 1002.9031, 0.0000, 0.0000, -90.2000); //Gen_doorINT04
	SetObjectMaterial(LaSanteInt[16], 1, 1649, "wglass", "carshowwin2", 0x00000000);
	LaSanteInt[17] = CreateObject(2161, 297.1550, -144.6595, 1003.0306, 0.0000, 0.0000, -179.8998); //MED_OFFICE_UNIT_4
	LaSanteInt[18] = CreateObject(1706, 288.7530, -128.0055, 1003.0545, 0.0000, 0.0000, 89.5000); //kb_couch03
	LaSanteInt[19] = CreateObject(2258, 288.2478, -128.7765, 1004.9225, 0.0000, 0.0000, 89.9999); //Frame_Clip_5
	LaSanteInt[20] = CreateObject(2611, 288.3409, -134.5806, 1004.8523, 0.0000, 0.0000, 90.4999); //POLICE_NB1
	LaSanteInt[21] = CreateObject(1704, 290.4471, -126.2429, 1002.9859, 0.0000, 0.0000, -0.2000); //kb_chair03
	LaSanteInt[22] = CreateObject(1704, 291.7572, -126.2474, 1002.9859, 0.0000, 0.0000, -0.2000); //kb_chair03
	LaSanteInt[23] = CreateObject(1706, 288.7298, -130.6654, 1003.0545, 0.0000, 0.0000, 89.5000); //kb_couch03
	LaSanteInt[24] = CreateObject(1892, 298.8004, -127.1817, 1003.0535, 0.0000, 0.0000, -87.5999); //security_gatsh
	LaSanteInt[25] = CreateObject(2257, 297.2633, -125.7051, 1004.9324, 0.0000, 0.0000, 0.0000); //Frame_Clip_4
	LaSanteInt[26] = CreateObject(14898, 292.1838, -136.7580, 1008.0524, 0.0000, 0.0000, 0.0000); //int_policeA03a
	LaSanteInt[27] = CreateObject(2315, 291.3913, -128.6415, 1003.0537, 0.0000, 0.0000, -90.6000); //CJ_TV_TABLE4
	LaSanteInt[28] = CreateObject(2072, 288.6974, -126.1169, 1004.6515, 0.0000, 0.0000, -99.2000); //CJ_MLIGHT4
	LaSanteInt[29] = CreateObject(18637, 288.1735, -136.8858, 1003.6514, 91.7999, 94.5000, -3.7000); //PoliceShield1
	LaSanteInt[30] = CreateObject(2199, 281.6003, -135.9707, 1003.0404, 0.0000, 0.0000, 91.5000); //MED_OFFICE6_MC_1
	LaSanteInt[31] = CreateObject(2167, 281.6228, -136.8896, 1003.0628, 0.0000, 0.0000, 91.5999); //MED_OFFICE_UNIT_7
	LaSanteInt[32] = CreateObject(18646, 299.3372, -127.6982, 1005.8945, 0.0000, -86.4999, 0.0000); //PoliceLight1
	LaSanteInt[33] = CreateObject(2202, 282.8551, -135.4920, 1003.0390, 0.0000, 0.0000, 0.0000); //PHOTOCOPIER_2
	LaSanteInt[34] = CreateObject(2604, 287.5655, -136.7231, 1003.6712, 0.0000, 0.0000, -89.3999); //CJ_POLICE_COUNTER
	LaSanteInt[35] = CreateObject(19942, 287.2986, -135.7621, 1004.1195, 0.0000, 0.0000, -56.5000); //PoliceRadio1
	LaSanteInt[36] = CreateObject(1808, 294.6500, -125.9196, 1003.0551, 0.0000, 0.0000, 0.0000); //CJ_WATERCOOLER2
	LaSanteInt[37] = CreateObject(2356, 286.6448, -136.2058, 1003.0307, 0.0000, 0.0000, -109.7000); //police_OFF_CHAIR
	LaSanteInt[38] = CreateObject(2356, 286.6071, -137.8443, 1003.0307, 0.0000, 0.0000, -68.0000); //police_OFF_CHAIR
	LaSanteInt[39] = CreateObject(2002, 285.0459, -140.7798, 1003.0853, 0.0000, 0.0000, -177.5999); //water_coolnu
	LaSanteInt[40] = CreateObject(2197, 282.5556, -137.7369, 1003.0724, 0.0000, 0.0000, 90.9999); //FILLING_CABINET
	LaSanteInt[41] = CreateObject(2197, 282.5670, -138.3968, 1003.0724, 0.0000, 0.0000, 90.9999); //FILLING_CABINET
	LaSanteInt[42] = CreateObject(1721, 299.2377, -142.2649, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[43] = CreateObject(1721, 299.2431, -141.6550, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[44] = CreateObject(1721, 299.2485, -141.0350, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[45] = CreateObject(1721, 299.2538, -140.4251, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[46] = CreateObject(1721, 299.2592, -139.8151, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[47] = CreateObject(1721, 299.2645, -139.1951, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[48] = CreateObject(1721, 297.8177, -142.2526, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[49] = CreateObject(1721, 297.8233, -141.6226, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[50] = CreateObject(1721, 297.8287, -141.0027, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[51] = CreateObject(1721, 297.8342, -140.3826, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[52] = CreateObject(1721, 297.8398, -139.7527, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[53] = CreateObject(1721, 297.8454, -139.1327, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[54] = CreateObject(1721, 296.5754, -139.1217, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[55] = CreateObject(1721, 296.5700, -139.7416, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[56] = CreateObject(1721, 296.5645, -140.3716, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[57] = CreateObject(1721, 296.5592, -140.9816, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[58] = CreateObject(1721, 296.5539, -141.5915, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[59] = CreateObject(1721, 296.5485, -142.1915, 1003.0488, 0.0000, 0.0000, 89.5000); //est_chair1
	LaSanteInt[60] = CreateObject(11743, 281.9298, -138.0099, 1004.7387, 0.0000, 0.0000, 88.3999); //MCoffeeMachine1
	LaSanteInt[61] = CreateObject(19778, 288.2793, -136.6829, 1003.3891, 91.2000, 87.1999, 5.7999); //InsigniaDetective1
	LaSanteInt[62] = CreateObject(1247, 288.2504, -136.7363, 1005.8197, 0.0000, 0.0000, 91.0000); //bribe
	LaSanteInt[63] = CreateObject(19273, 281.6066, -140.7419, 1004.7125, 0.0000, 0.0000, 88.5000); //KeypadNonDynamic
	LaSanteInt[64] = CreateObject(2253, 291.4504, -129.4058, 1003.8453, 0.0000, 0.0000, 0.0000); //Plant_Pot_22
	LaSanteInt[65] = CreateObject(19464, 296.7577, -128.1191, 1002.9491, 0.0000, 89.9999, 88.2000); //wall104
	SetObjectMaterial(LaSanteInt[65], 0, 2755, "ab_dojowall", "mp_apt1_roomfloor", 0x00000000);
	LaSanteInt[66] = CreateObject(633, 288.9447, -131.8519, 1004.0317, 0.0000, 0.0000, -14.2999); //veg_palmkb10
	LaSanteInt[67] = CreateObject(19347, 288.2798, -136.6828, 1003.3494, 1.6999, 89.0000, 2.9999); //badge01
	LaSanteInt[68] = CreateObject(2631, 297.0694, -127.6821, 1003.0184, 0.0000, 0.0000, 0.0000); //gym_mat1
	LaSanteInt[69] = CreateObject(2811, 298.9403, -138.4976, 1003.0490, 0.0000, 0.0000, 63.9000); //GB_romanpot01
	LaSanteInt[70] = CreateObject(2001, 299.1334, -126.2376, 1003.0216, 0.0000, 0.0000, 0.0000); //nu_plant_ofc
	LaSanteInt[71] = CreateObject(2001, 299.1334, -129.1176, 1003.0216, 0.0000, 0.0000, 0.0000); //nu_plant_ofc
	LaSanteInt[72] = CreateObject(997, 288.1831, -138.3715, 1002.9078, 0.0000, 0.0000, -1.5999); //lhouse_barrier3
	LaSanteInt[73] = CreateObject(2811, 295.2804, -126.0076, 1002.9789, 0.0000, 0.0000, 0.0000); //GB_romanpot01
	LaSanteInt[74] = CreateObject(955, 298.9248, -132.3906, 1003.4355, 0.0000, 0.0000, -91.1999); //CJ_EXT_SPRUNK
	SetObjectMaterial(LaSanteInt[74], 0, -1, "none", "none", 0xFF800000);
	LaSanteInt[75] = CreateObject(19464, 290.7019, -133.0012, 1002.9491, 0.0000, 89.9999, 88.2000); //wall104
	SetObjectMaterial(LaSanteInt[75], 0, 2755, "ab_dojowall", "mp_apt1_roomfloor", 0x00000000);
	LaSanteInt[76] = CreateObject(19464, 296.5886, -133.1861, 1002.9491, 0.0000, 89.9999, 88.2000); //wall104
	SetObjectMaterial(LaSanteInt[76], 0, 2755, "ab_dojowall", "mp_apt1_roomfloor", 0x00000000);
	LaSanteInt[77] = CreateObject(19464, 296.4294, -138.2535, 1002.9491, 0.0000, 89.9999, 88.2000); //wall104
	SetObjectMaterial(LaSanteInt[77], 0, 2755, "ab_dojowall", "mp_apt1_roomfloor", 0x00000000);
	LaSanteInt[78] = CreateObject(19464, 296.2698, -143.3310, 1002.9491, 0.0000, 89.9999, 88.2000); //wall104
	SetObjectMaterial(LaSanteInt[78], 0, 2755, "ab_dojowall", "mp_apt1_roomfloor", 0x00000000);
	LaSanteInt[79] = CreateObject(19464, 290.8612, -127.9337, 1002.9491, 0.0000, 89.9999, 88.2000); //wall104
	SetObjectMaterial(LaSanteInt[79], 0, 2755, "ab_dojowall", "mp_apt1_roomfloor", 0x00000000);
	LaSanteInt[80] = CreateObject(19464, 290.5432, -138.0487, 1002.9491, 0.0000, 89.9999, 88.2000); //wall104
	SetObjectMaterial(LaSanteInt[80], 0, 2755, "ab_dojowall", "mp_apt1_roomfloor", 0x00000000);
	LaSanteInt[81] = CreateObject(19464, 290.3834, -143.1362, 1002.9491, 0.0000, 89.9999, 88.2000); //wall104
	SetObjectMaterial(LaSanteInt[81], 0, 2755, "ab_dojowall", "mp_apt1_roomfloor", 0x00000000);
	LaSanteInt[82] = CreateObject(2811, 288.6926, -144.3887, 1003.0490, 0.0000, 0.0000, 90.4000); //GB_romanpot01
	LaSanteInt[83] = CreateObject(1704, 292.9394, -144.1815, 1002.9859, -0.3000, 0.0000, 179.8000); //kb_chair03
	LaSanteInt[84] = CreateObject(1706, 288.6175, -143.5349, 1003.0545, 0.0000, 0.0000, 89.5000); //kb_couch03
	LaSanteInt[85] = CreateObject(1704, 291.7493, -144.1774, 1002.9859, -0.3000, 0.0000, 179.8000); //kb_chair03

    printf("[MAPA %d]: La Sante... Carregado com sucesso!", gm_count[COUNT_CREATEMAP]);
    gm_count[COUNT_CREATEMAP]++;
}