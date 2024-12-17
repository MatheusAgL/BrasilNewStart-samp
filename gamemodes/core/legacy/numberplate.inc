
#define MAX_NUMBER_PLATE_NAME  (25)

static
	VehNumberPlate[ MAX_VEHICLES ][ MAX_NUMBER_PLATE_NAME ];
	
stock SetVehicleNumberPlate_(vehicleid, const numberplate[]) {

	if (vehicleid < 1 || vehicleid >= MAX_VEHICLES)
		return 0;

	format(VehNumberPlate[vehicleid], MAX_NUMBER_PLATE_NAME, numberplate);

	return SetVehicleNumberPlate(vehicleid, numberplate);
}

stock GetVehicleNumberPlate(vehicleid) {

	new vehiclePlate[MAX_NUMBER_PLATE_NAME] = "";

    if (vehicleid < 1 || vehicleid > MAX_VEHICLES) {
		strcat(vehiclePlate, " ");
	}
	else {
		strcat(vehiclePlate, VehNumberPlate[vehicleid]);
	}

	return vehiclePlate;
}

#if defined _ALS_SetVehicleNumberPlate
	#undef SetVehicleNumberPlate
#else
	#define _ALS_SetVehicleNumberPlate
#endif
#define SetVehicleNumberPlate SetVehicleNumberPlate_
