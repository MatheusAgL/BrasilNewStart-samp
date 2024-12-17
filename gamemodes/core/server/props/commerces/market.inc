new marketShelf[2];

enum E_MARKET_SHELF 
{
	marketShelfType,
	marketItemType,

    Float:marketItem_PosX,
    Float:marketItem_PosY,
    Float:marketItem_PosZ,
};

new Shelf_Itens[][E_MARKET_SHELF] =
{
    // Type shelf       Item type           X -         + Y         + Z             - Y
	{0,                 1544,               2.3108,     0.2138,     1.1834             },                  // CJ_BEER_B_1        (Cerveja Koron)
    {0,                 1544,               2.3108,     -0.0765,    1.1834    }
    {0,                 1544,               2.1605,     0.2138,     1.1834     }
    {0,                 1544,               2.1605,     -0.0765,    1.1834    }
};

CMD:loadmap247(playerid) {

    LoadMap_Market();

    return 1;
}

stock LoadMap_Market() {

    // Base
    CreateObject(14665, 1848.8183, 1076.0985, -49.9672, 0.0000, 0.0000, 0.0000);        //int_7_11A40

    marketShelf[0] = CreateObject(1849, 1849.7413, 1080.9820, -51.9477, 0.0000, 0.0000, 0.0000); //shop_shelf09

    new Float:obj_x,
        Float:obj_y,
        Float:obj_z;

    GetObjectPos(marketShelf[0], obj_x, obj_y, obj_z);

    for (new i; i < 3; i++) {

        // CJ_BEER_B_1        (Cerveja Koron)
        CreateObject(
            Shelf_Itens[i][marketItemType], 
            obj_x - Shelf_Itens[i][marketItem_PosX], 
            obj_y + Shelf_Itens[i][marketItem_PosY], 
            obj_z + Shelf_Itens[i][marketItem_PosZ], 
            0.0000, 0.0000, 0.0000
        );      
    }
}
    /*SetPlayerCheckpoint(
        playerid, 
        PlayerCheckpoint[playerid][cpPos][0],
        PlayerCheckpoint[playerid][cpPos][1],
        PlayerCheckpoint[playerid][cpPos][2],
        PlayerCheckpoint[playerid][cpSize]
    );*/