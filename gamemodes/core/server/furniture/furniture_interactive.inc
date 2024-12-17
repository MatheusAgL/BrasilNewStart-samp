enum {
	MODEL_TYPE_NONE,				// Nenhum
	MODEL_TYPE_STOVE,				// Fogão
	MODEL_TYPE_BED					// Cama
};

stock FurnitureInteractive_Check(modelid) {

	switch (modelid) {
		case 19915: return MODEL_TYPE_STOVE;
		case 1801: return MODEL_TYPE_BED;
		default: return 0;
	}
    return 0;
}