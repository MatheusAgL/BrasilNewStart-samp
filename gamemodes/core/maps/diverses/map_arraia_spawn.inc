#include <YSI_Coding\y_hooks>

hook OnCreateObject()
{
	new tmpobj;

	tmpobj = CreateDynamicObject(19362, 1681.8631, -2247.7712, 18.6467, 0.0000, 0.0000, -90.0000); //wall010
	SetDynamicObjectMaterialText(tmpobj, 0, "rr", OBJECT_MATERIAL_SIZE_256x128, "Arial", 130, 1, 0xFF00BFFF, 0x00000000, 1);
	CreateDynamicObject(19606, 1683.5361, -2247.7939, 19.8794, -11.0999, 0.0000, 0.0000); //EnExMarker4-3
	tmpobj = CreateDynamicObject(19362, 1680.8231, -2247.7712, 18.6967, 0.0000, 0.0000, -90.0000); //wall010
	SetDynamicObjectMaterialText(tmpobj, 0, "A", OBJECT_MATERIAL_SIZE_256x128, "Arial", 135, 1, 0xFF00FA9A, 0x00000000, 1);
	tmpobj = CreateDynamicObject(19362, 1682.8132, -2247.7712, 18.6467, 0.0000, 0.0000, -90.0000); //wall010
	SetDynamicObjectMaterialText(tmpobj, 0, "a", OBJECT_MATERIAL_SIZE_256x128, "Arial", 130, 1, 0xFF0000CD, 0x00000000, 1);
	tmpobj = CreateDynamicObject(19362, 1683.7631, -2247.7712, 18.6467, 0.0000, 0.0000, -90.0000); //wall010
	SetDynamicObjectMaterialText(tmpobj, 0, "ia", OBJECT_MATERIAL_SIZE_256x128, "Arial", 130, 1, 0xFFB22222, 0x00000000, 1);
	tmpobj = CreateDynamicObject(19362, 1685.2730, -2247.7712, 18.8067, 0.0000, 0.0000, -90.0000); //wall010
	SetDynamicObjectMaterialText(tmpobj, 0, "B", OBJECT_MATERIAL_SIZE_256x128, "Comic Sans MS", 150, 0, 0xFFA9A9A9, 0x00000000, 1);
	tmpobj = CreateDynamicObject(19362, 1686.0329, -2247.7712, 18.6467, 0.0000, 0.0000, -90.0000); //wall010
	SetDynamicObjectMaterialText(tmpobj, 0, "n", OBJECT_MATERIAL_SIZE_256x128, "Comic Sans MS", 135, 1, 0xFFFF4500, 0x00000000, 1);
	tmpobj = CreateDynamicObject(19362, 1686.6531, -2247.7712, 18.8067, 0.8999, 0.0000, -90.0000); //wall010
	SetDynamicObjectMaterialText(tmpobj, 0, "S", OBJECT_MATERIAL_SIZE_256x128, "Comic Sans MS", 150, 0, 0xFFA9A9A9, 0x00000000, 1);
	tmpobj = CreateDynamicObject(19362, 1686.7338, -2247.7712, 18.7580, 0.8999, 0.0000, -90.0000); //wall010
	SetDynamicObjectMaterialText(tmpobj, 0, "S", OBJECT_MATERIAL_SIZE_256x128, "Comic Sans MS", 150, 0, 0xFFA9A9A9, 0x00000000, 1);
	tmpobj = CreateDynamicObject(19362, 1685.3231, -2247.7712, 18.7267, 0.0000, 0.0000, -90.0000); //wall010
	SetDynamicObjectMaterialText(tmpobj, 0, "B", OBJECT_MATERIAL_SIZE_256x128, "Comic Sans MS", 150, 0, 0xFFA9A9A9, 0x00000000, 1);
	CreateDynamicObject(19605, 1680.3592, -2247.7338, 19.8801, 0.0000, -11.6999, 0.0000); //EnExMarker4-2
	CreateDynamicObject(19607, 1687.3814, -2247.7382, 19.8264, 4.5999, 10.6000, 0.0000); //EnExMarker4-4
	tmpobj = CreateDynamicObject(19134, 1679.4187, -2247.7961, 19.1525, -178.5999, 0.0000, -90.3999); //ArrowType5
	SetDynamicObjectMaterial(tmpobj, 0, -1, "none", "none", 0xFFFF0000);
 	CreateDynamicObject(19553, 1683.3739, -2247.8549, 19.7931, 38.7000, -103.8000, 2.6999); //StrawHat1
	tmpobj = CreateDynamicObject(19134, 1679.9284, -2247.7985, 19.1649, -178.5999, 0.0000, -90.3999); //ArrowType5
	SetDynamicObjectMaterial(tmpobj, 0, -1, "none", "none", 0xFF00008B);
	tmpobj = CreateDynamicObject(19134, 1688.2813, -2247.8566, 19.1390, -178.5999, 0.0000, -90.3999); //ArrowType5
	SetDynamicObjectMaterial(tmpobj, 0, -1, "none", "none", 0xFF00008B);
	tmpobj = CreateDynamicObject(18761, 1683.6831, -2237.5187, 12.3990, 0.0000, 0.0000, 0.0000); //RaceFinishLine1
	SetDynamicObjectMaterial(tmpobj, 0, -1, "none", "none", 0xFF00FF7F);
	tmpobj = CreateDynamicObject(18761, 1682.8027, -2253.7512, 17.4090, 0.0000, 0.0000, 0.0000); //RaceFinishLine1
	SetDynamicObjectMaterial(tmpobj, 0, -1, "none", "none", 0xFF00BFFF);
	tmpobj = CreateDynamicObject(18761, 1682.8027, -2263.7407, 17.4390, 0.0000, 0.0000, 0.0000); //RaceFinishLine1
	SetDynamicObjectMaterial(tmpobj, 0, -1, "none", "none", 0xFFFF0000);
	tmpobj = CreateDynamicObject(18761, 1682.6722, -2275.8090, 18.4090, 0.0000, 0.0000, 39.5999); //RaceFinishLine1
	SetDynamicObjectMaterial(tmpobj, 0, -1, "none", "none", 0xFFFFFF00);
	tmpobj = CreateDynamicObject(18761, 1682.7338, -2289.4111, 18.4090, 0.0000, 0.0000, -39.6000); //RaceFinishLine1
	SetDynamicObjectMaterial(tmpobj, 0, -1, "none", "none", 0xFF00FA9A);
	tmpobj = CreateDynamicObject(18761, 1682.8754, -2302.3593, 18.4090, 0.0000, 0.0000, 40.6999); //RaceFinishLine1
	SetDynamicObjectMaterial(tmpobj, 0, -1, "none", "none", 0xFFFF0000);
	/*tmpobj = CreateDynamicObject(19362, 1635.0069, -2286.5820, 24.2167, 0.0000, 0.0000, -179.8999); //wall010
	SetDynamicObjectMaterialText(tmpobj, 0, "LGBTQIAPN+", OBJECT_MATERIAL_SIZE_256x128, "Arial Black", 45, 1, 0xFF000000, 0x00000000, 1);
	tmpobj = CreateDynamicObject(19362, 1634.9569, -2286.6020, 24.6967, 0.0000, 0.0000, -179.8999); //wall010
	SetDynamicObjectMaterial(tmpobj, 0, 3853, "gay_xref", "ws_gayflag2", 0x00000000);
	tmpobj = CreateDynamicObject(19362, 1635.0069, -2286.5820, 25.2567, 0.0000, 0.0000, -179.8999); //wall010
	SetDynamicObjectMaterialText(tmpobj, 0, "Mes do Orgulho", OBJECT_MATERIAL_SIZE_256x128, "Arial", 30, 1, 0xFF000000, 0x00000000, 1);
	CreateDynamicObject(1240, 1635.0598, -2286.6574, 26.8006, 0.0000, 0.0000, -89.9999); //health
	CreateDynamicObject(1240, 1635.0598, -2286.6574, 22.6106, 0.0000, 0.0000, -89.9999); */
	tmpobj = CreateDynamicObject(19134, 1687.7612, -2247.8530, 19.1263, -178.5999, 0.0000, -90.3999); //ArrowType5
	SetDynamicObjectMaterial(tmpobj, 0, -1, "none", "none", 0xFFFF0000);
	CreateDynamicObject(19134, 1680.4177, -2247.8015, 19.1769, -178.5999, 0.0000, -90.3999); //ArrowType5
	CreateDynamicObject(19134, 1687.2513, -2247.8491, 19.1139, -178.5999, 0.0000, -90.3999); //ArrowType5
	CreateDynamicObject(19553, 1687.4987, -2247.8815, 18.1866, 99.4999, -103.7999, 0.6999); //StrawHat1
	CreateDynamicObject(19553, 1687.9964, -2248.0664, 18.5906, 99.4999, -103.7999, 0.6999); //StrawHat1
	CreateDynamicObject(19553, 1687.4710, -2247.9670, 18.7401, 99.4999, -103.7999, 0.6999); //StrawHat1
	CreateDynamicObject(19553, 1680.1247, -2247.8759, 18.6180, 99.4999, -103.7999, 0.6999); //StrawHat1
	CreateDynamicObject(19553, 1679.7215, -2247.8854, 18.6173, 99.4999, -103.7999, 0.6999); //StrawHat1
	CreateDynamicObject(19553, 1679.9378, -2247.8723, 18.0511, 99.4999, -103.7999, 0.6999); //StrawHat1

    printf("[MAPA %d]: Arraia Spawn loaded...", gm_count[COUNT_CREATEMAP]);
    gm_count[COUNT_CREATEMAP]++;
}