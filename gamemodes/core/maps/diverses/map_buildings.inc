stock CreateMap_Buildings() // by Spose
{
    // Idlewood Buildings
    CreateDynamicObject(3866, 1913.98254, -1864.86975, 20.39250,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(5463, 1883.72412, -1859.30969, 37.01670,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(5644, 1884.75244, -1860.85754, 29.89640,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1383, 1912.64319, -1857.31787, 45.07800,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1384, 1912.59900, -1857.42285, 77.49180,   0.00000, 0.00000, 111.00000);
    CreateDynamicObject(10984, 1913.70056, -1867.87158, 13.50216,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(8885, 1926.22034, -1852.78992, 16.04042,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(3502, 1940.62573, -1862.32971, 14.38937,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(3502, 1944.74756, -1863.09070, 16.10950,   -25.00000, -18.00000, 282.00000);
    CreateDynamicObject(1358, 1925.79248, -1868.89111, 13.71490,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(1219, 1925.15173, -1863.56665, 12.53990,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1219, 1925.29907, -1862.10083, 12.95400,   0.00000, 11.00000, 91.00000);
    CreateDynamicObject(1425, 1950.93274, -1874.13855, 13.00110,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(1425, 1951.02356, -1868.38306, 13.00110,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(1425, 1951.06348, -1863.65173, 13.00110,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(1422, 1951.01355, -1871.35608, 13.15820,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(1422, 1951.12854, -1866.00830, 13.15820,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(1422, 1950.97913, -1877.08105, 13.15820,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(1422, 1951.25098, -1860.87903, 13.15820,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(1464, 1925.89722, -1872.81030, 13.62100,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(1631, 1933.18079, -1867.98975, 12.53422,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1490, 1905.49707, -1878.56763, 14.27347,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(8873, 1931.99646, -1859.56934, 18.61820,   0.00000, 0.00000, 260.00000);
    CreateDynamicObject(8874, 1926.49512, -1862.34705, 19.46460,   0.00000, 0.00000, 260.00000);
    CreateDynamicObject(10984, 1878.31274, -1849.05151, 13.07809,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1684, 1941.22754, -1876.87622, 14.09380,   0.00000, 0.00000, 180.00000);
    CreateDynamicObject(1684, 1931.31580, -1876.91919, 17.06780,   0.00000, 0.00000, 180.00000);
    CreateDynamicObject(1684, 1931.30273, -1876.91919, 14.09380,   0.00000, 0.00000, 180.00000);
    CreateDynamicObject(1684, 1941.36511, -1876.91919, 17.06780,   0.00000, 0.00000, 180.00000);
    CreateDynamicObject(8572, 1929.85291, -1873.88855, 14.41490,   0.00000, 0.00000, 180.00000);
    CreateDynamicObject(3504, 1942.62024, -1873.28418, 14.56777,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(12930, 1896.55750, -1856.01648, 13.45165,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(7017, 1904.74597, -1879.56921, 12.53440,   0.00000, 0.00000, 180.00000);

    printf("[MAPA %d]: Construções... Carregado com sucesso!", gm_count[COUNT_CREATEMAP]);
    gm_count[COUNT_CREATEMAP]++;
}


stock RemoveBuilding_MapBuildings(playerid)
{
	RemoveBuildingForPlayer(playerid, 4976, 1931.0000, -1871.3906, 15.8438, 0.25);
    RemoveBuildingForPlayer(playerid, 1413, 1879.9922, -1879.8906, 13.6797, 0.25);
    RemoveBuildingForPlayer(playerid, 1413, 1885.2578, -1879.8984, 13.6797, 0.25);
    RemoveBuildingForPlayer(playerid, 1413, 1869.4609, -1879.6641, 13.6797, 0.25);
    RemoveBuildingForPlayer(playerid, 1412, 1874.7344, -1879.6641, 13.6797, 0.25);
    RemoveBuildingForPlayer(playerid, 1412, 1890.5234, -1879.6641, 13.6797, 0.25);
    RemoveBuildingForPlayer(playerid, 1413, 1904.3750, -1879.7344, 13.6797, 0.25);
    RemoveBuildingForPlayer(playerid, 1413, 1909.6563, -1879.7344, 13.6797, 0.25);
    RemoveBuildingForPlayer(playerid, 1412, 1914.9297, -1879.7344, 13.6797, 0.25);
    RemoveBuildingForPlayer(playerid, 1413, 1920.1953, -1879.9531, 13.6797, 0.25);
    RemoveBuildingForPlayer(playerid, 1413, 1925.4609, -1879.9609, 13.6797, 0.25);
    RemoveBuildingForPlayer(playerid, 1412, 1930.7188, -1879.7344, 13.6797, 0.25);
    RemoveBuildingForPlayer(playerid, 4848, 1931.0000, -1871.3906, 15.8438, 0.25);
    RemoveBuildingForPlayer(playerid, 1226, 1931.8750, -1863.4609, 16.3203, 0.25);
    RemoveBuildingForPlayer(playerid, 1226, 1915.7422, -1863.4609, 16.3203, 0.25);
    return 1;
}