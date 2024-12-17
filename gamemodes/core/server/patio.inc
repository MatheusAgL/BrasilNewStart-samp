/**--------------------------------------------------------------------------**\
 ______ ______  ______     __  ______  ______  ______     ______  __  ______ __  __
/\  == /\  == \/\  __ \   /\ \/\  ___\/\  ___\/\__  _\   /\  ___\/\ \/\__  _/\ \_\ \
\ \  _-\ \  __<\ \ \/\ \ _\_\ \ \  __\\ \ \___\/_/\ \/   \ \ \___\ \ \/_/\ \\ \____ \
 \ \_\  \ \_\ \_\ \_____/\_____\ \_____\ \_____\ \ \_\    \ \_____\ \_\ \ \_\\/\_____\
  \/_/   \/_/ /_/\/_____\/_____/\/_____/\/_____/  \/_/     \/_____/\/_/  \/_/ \/_____/

						 ==========================
		                    Brasil Project City
                              ® 2012 - 2016
                             Módulo: Patio - detran
						 ==========================

\**--------------------------------------------------------------------------**/

new Float:vagasPatio[][] = {
	{2280.5815, -141.2901, 26.1175, 0.0000},
	{2280.3972, -133.6523, 26.1175, 0.0000},
	{2321.8333, -141.4491, 26.1175, 0.0000},
	{2318.4878, -141.4377, 26.1175, 0.0000},
	{2315.2317, -141.4265, 26.1175, 0.0000},
	{2311.8862, -141.4151, 26.1175, 0.0000},
	{2308.9614, -141.4050, 26.1175, 0.0000},
	{2305.6836, -141.3938, 26.1175, 0.0000},
	{2302.2046, -141.3819, 26.1175, 0.0000},
	{2298.8257, -141.3703, 26.1175, 0.0000},
	{2295.6782, -141.3595, 26.1175, 0.0000},
	{2292.5957, -141.3490, 26.1175, 0.0000},
	{2289.6428, -141.3388, 26.1175, 0.0000},
	{2286.6899, -141.3230, 26.1175, 0.0000},
	{2283.6074, -141.3064, 26.1175, 0.0000},
	{2325.1440, -141.3555, 26.1175, 0.0000},
	{2280.1519, -126.8601, 26.1175, 0.0000},
	{2325.3093, -133.5459, 26.1175, 0.0000},
	{2321.9236, -133.5698, 26.1175, 0.0000},
	{2318.5791, -133.5935, 26.1175, 0.0000},
	{2315.1001, -133.6181, 26.1175, 0.0000},
	{2311.7690, -133.6417, 26.1175, 0.0000},
	{2308.8154, -133.5626, 26.1175, 0.0000},
	{2305.6875, -133.5847, 26.1175, 0.0000},
	{2302.2419, -133.6091, 26.1175, 0.0000},
	{2298.6282, -133.6347, 26.1175, 0.0000},
	{2295.5457, -133.6565, 26.1175, 0.0000},
	{2292.3623, -133.5790, 26.1175, 0.0000},
	{2289.5376, -133.5990, 26.1175, 0.0000},
	{2286.5847, -133.6199, 26.1175, 0.0000},
	{2283.3394, -133.6429, 26.1175, 0.0000},
	{2328.5554, -133.6229, 26.1175, 0.0000},
	{2321.9346, -126.2702, 26.1175, 0.0000},
	{2318.5891, -126.3070, 26.1175, 0.0000},
	{2315.0754, -126.3456, 26.1175, 0.0000},
	{2311.7300, -126.3824, 26.1175, 0.0000},
	{2308.9568, -126.4034, 26.1175, 0.0000},
	{2305.7742, -126.4275, 26.1175, 0.0000},
	{2302.2275, -126.4543, 26.1175, 0.0000},
	{2298.8135, -126.4765, 26.1175, 0.0000},
	{2295.7861, -126.4549, 26.1175, 0.0000},
	{2292.5095, -126.5398, 26.1175, 0.0000},
	{2289.5576, -126.6163, 26.1175, 0.0000},
	{2286.4763, -126.6962, 26.1175, 0.0000},
	{2283.2642, -126.7794, 26.1175, 0.0000},
	{2328.5935, -126.1969, 26.1175, 0.0000},
	{2325.3801, -126.2323, 26.1175, 0.0000},
	{2280.0444, -119.4697, 26.1175, 180.4321},
	{2281.2612, -112.3538, 26.1175, 180.4321},
	{2321.9998, -119.5714, 26.1175, 180.4321},
	{2318.5530, -119.5623, 26.1175, 180.4321},
	{2315.2087, -119.6506, 26.1175, 180.4321},
	{2311.8645, -119.7389, 26.1175, 180.4321},
	{2308.9404, -119.6932, 26.1175, 180.4321},
	{2305.8882, -119.6455, 26.1175, 180.4321},
	{2302.2100, -119.5879, 26.1175, 180.4321},
	{2298.7319, -119.5335, 26.1175, 180.4321},
	{2295.6504, -119.4853, 26.1175, 180.4321},
	{2292.5688, -119.4371, 26.1175, 180.4321},
	{2289.4873, -119.3889, 26.1175, 180.4321},
	{2286.4048, -119.4153, 26.1175, 180.4321},
	{2283.1270, -119.4433, 26.1175, 180.4321},
	{2325.4128, -119.4812, 26.1175, 180.4321},
	{2326.0396, -112.3055, 26.1175, 180.4321},
	{2322.9553, -112.2921, 26.1175, 180.4321},
	{2319.6404, -112.2852, 26.1175, 180.4321},
	{2316.5281, -112.2799, 26.1175, 180.4321},
	{2313.3147, -112.2744, 26.1175, 180.4321},
	{2310.1274, -112.3016, 26.1175, 180.4321},
	{2306.7820, -112.3302, 26.1175, 180.4321},
	{2303.5994, -112.3574, 26.1175, 180.4321},
	{2300.3157, -112.3582, 26.1175, 180.4321},
	{2297.1023, -112.3590, 26.1175, 180.4321},
	{2294.0210, -112.2754, 26.1175, 180.4321},
	{2290.9648, -112.1926, 26.1175, 180.4321},
	{2287.6553, -112.2476, 26.1175, 180.4321},
	{2284.4736, -112.3004, 26.1175, 180.4321}
};

new Float: liberarCarro[][] = {

	{2240.8533,-104.7894,26.4783,269.0450},
	{2248.5640,-104.7528,26.4784,270.2723},
	{2255.7412,-104.7187,26.4784,270.2723},
	{2262.0034,-104.6890,26.4785,270.2723},
	{2234.7190,-90.6776,26.4844,266.2224},
	{2241.5803,-90.8655,26.4844,268.4315},
	{2250.7827,-90.7733,26.4844,268.1860},
	{2257.6084,-90.9164,26.4844,268.7996},
	{2264.3684,-91.0580,26.4844,268.7996},
	{2272.0100,-91.2182,26.4844,268.7996},
	{2279.0308,-90.9411,26.4844,268.7996},
	{2286.3652,-85.1975,26.4844,358.3877},
	{2286.5232,-79.5945,26.4844,358.3877}
};

enum PATIO_ENUM {
	patioPlaca[25],
	patioModelo,
}

new PatioInfo[sizeof(vagasPatio)][PATIO_ENUM];
new Iterator:IterPatio<sizeof(vagasPatio)>;

// stock ApreenderVehicle(vehicleid, const agente[] = "Ninguem")
// {
// 	new id = Iter_Free(IterPatio);

// 	if (id != INVALID_ITERATOR_SLOT)
// 	{
// 	    Iter_Add(IterPatio, id);
// 		new plate[25];		

// 		GetVehicleNumberPlate(vehicleid, plate);
// 	    format(PatioInfo[id][patioPlaca], 25, plate);
// 		PatioInfo[id][patioModelo] = GetVehicleModel(vehicleid);
// 	    SetVehiclePos(vehicleid, vagasPatio[id][0], vagasPatio[id][1], vagasPatio[id][2]);
// 	    SetVehicleZAngle(vehicleid, vagasPatio[id][3]);

// 		VehicleInfo[vehicleid][vhArrested] = 1;

// 	    saveSlotPatio(id, agente);
// 		return id;
// 	}
// 	return -1;
// }

stock RemovePlaceFromPatio(const numberplate[])
{
	foreach(new id : IterPatio)
	{
		if (!strcmp(PatioInfo[id][patioPlaca], numberplate, true))
		{
		    Iter_Remove(IterPatio, id);

		    new vehicleid = GetVehicleIDByPlate(PatioInfo[id][patioPlaca]);

		    if (vehicleid != INVALID_VEHICLE_ID) {

				new rdon = random(sizeof liberarCarro);

				SetVehiclePos(vehicleid, liberarCarro[rdon][0],liberarCarro[rdon][1],liberarCarro[rdon][2]);
				SetVehicleZAngle(vehicleid, liberarCarro[rdon][3]);

				VehicleInfo[vehicleid][vhArrested] = 0;
		    }

	    	format(PatioInfo[id][patioPlaca], 25, "AAA-0000");
	    	PatioInfo[id][patioModelo] = -1;

            saveSlotPatio(id, "Ninguem");

		    return true;
	   	}
	}
	return false;
}

stock GetVehicleIDByPlate(const plateinfo[])
{
	#pragma unused plateinfo
	// new plate[25];
	// for(new vehicleid; vehicleid != MAX_VEHICLES; vehicleid++) {
	// 	GetVehicleNumberPlate(vehicleid, plate);
	//     if (!strcmp(plateinfo, plate, true) && IsValidVehicle(vehicleid)) {
	//         return vehicleid;
	//     }
	// }
	return INVALID_VEHICLE_ID;
}

stock IsVehicleInDetran(vehicleid)
{
	new Float:x,
		Float:y,
		Float:z
	;

	GetVehiclePos(vehicleid, x, y, z);

	if(x >= 2270.1895 && y >= -147.1010 && x <= 2333.2546 && y <= -105.7006) return true;

	else return false;
}

stock saveSlotPatio(id, const agente[]) 
{
    new query[255];

  	mysql_format(MySQL_Handle, query, sizeof query, "UPDATE `patio` SET `placa` = '%s',`data` = CURRENT_TIMESTAMP(),`agente` = '%s',`modelo` = '%d' WHERE `id` = '%d'",
	PatioInfo[id][patioPlaca], agente, PatioInfo[id][patioModelo], id);

   	mysql_tquery(MySQL_Handle, query);
}

stock loadSlotsPatio() {

	new string[75];
	mysql_format(MySQL_Handle, string, sizeof string, "SELECT * FROM `patio`");
	mysql_query(MySQL_Handle, string);

	new row_count;
    cache_get_row_count(row_count);

	if (row_count)
	{
		for(new patio; patio != sizeof (vagasPatio); patio++)
		{
			cache_get_value_name(patio, "placa", string);
	    	format(PatioInfo[patio][patioPlaca], 25, string);
	    	cache_get_value_name_int(patio, "modelo", PatioInfo[patio][patioModelo]);

	    	if (!strcmp(PatioInfo[patio][patioPlaca], "AAA-0000", true)) {
          		Iter_Remove(IterPatio, patio);
	    	} else {
          		Iter_Add(IterPatio, patio);

				new vehicleid = GetVehicleIDByPlate(PatioInfo[patio][patioPlaca]);
				if(vehicleid != INVALID_VEHICLE_ID) {
					SetVehiclePos(vehicleid, vagasPatio[patio][0], vagasPatio[patio][1], vagasPatio[patio][2]);
					SetVehicleZAngle(vehicleid, vagasPatio[patio][3]);
				}
	    	}
		}

		printf("[DETRAN]: %d vagas do pátio foram carregadas.", row_count);
	} else {
	    print("[DETRAN]: Nenhuma vaga do pátio foi carregada.");
	}
}

















