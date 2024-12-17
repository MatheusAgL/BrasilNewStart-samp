// Include
#include < YSI_Coding\y_hooks >

#define MAX_PRISON_CAMERAS 7

static const Float:PrisonCamerasPos[MAX_PRISON_CAMERAS][6] = {
    {1759.14380, -1592.96582, 16.60744,   25.50000, -90.00000, -93.84006},
    {1754.44275, -1582.94409, 15.25049,   0.00000, 0.00000, 0.00000},
    {1780.67603, -1537.77454, 12.28637,   13.50000, 0.00000, -35.50000},
    {1822.55078, -1541.70007, 16.12300,   150.00000, -0.50000, -66.41980},
    {1824.82288, -1533.93555, 16.12300,   150.00000, -0.50000, -149.51979},
    {1813.74011, -1533.30774, 16.17331,   150.00000, 0.00000, 121.13991},
    {1780.93359, -1531.15417, 12.41595,   150.00000, 0.00000, 121.13991}
};

static Timer:CameraAlertTimer[MAX_PLAYERS];

// Enumerador
enum PrisonCameras_enum {
    bool:cameraExists,
    bool:cameraDestroyed,
    Timer:cameraRegenTimer,
    cameraObject,
    Float:cameraHealth
};
new PrisonCamerasInfo[MAX_PRISON_CAMERAS][PrisonCameras_enum];


stock CreateActors_NewPrison() {
    new actorid;

    CreateDynamicActor(280, 3879.2175,-1703.3606,5216.7100,359.4778, true, 100.0, 99, 1);

    actorid = CreateDynamicActor(281, 3871.7900,-1697.8364,5216.7100,90.0744, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "PED","IDLE_CHAT", 4.1, true, true, true, 1, false);
    
    actorid = CreateDynamicActor(307, 3870.1772,-1697.8029,5216.7100,267.1133, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "PED","IDLE_CHAT", 4.1, true, true, true, 1, false);

    CreateDynamicActor(309, 3865.3242,-1689.6857,5216.7100,177.9874, true, 100.0, 99, 1);

    actorid = CreateDynamicActor(303, 3882.5879,-1696.4832,5216.7100,84.0758, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "PED", "SEAT_idle", 4.1, true, false, false, false, false);

    actorid = CreateDynamicActor(46, 3882.5427,-1699.3009,5216.7100,87.4102, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "PED", "SEAT_idle", 4.1, true, false, false, false, false);

    actorid = CreateDynamicActor(44, 3874.9470,-1687.6279,5216.7100,173.5272, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "PED", "SEAT_idle", 4.1, true, false, false, false, false);

    actorid = CreateDynamicActor(37, 3879.1230,-1687.6603,5216.7100,175.1194, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "PED", "SEAT_idle", 4.1, true, false, false, false, false);

    actorid = CreateDynamicActor(240, 3865.9973,-1694.2043,5217.3198,267.3513, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "INT_OFFICE","FF_Dam_Fwd", 4.1, false, true, true, 1, false);

    actorid = CreateDynamicActor(98, 3869.2134,-1692.2556,5217.3198,87.1816, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "INT_OFFICE","FF_Dam_Fwd", 4.1, false, true, true, 1, false);

    actorid = CreateDynamicActor(301, 3881.2720,-1706.7155,5217.2319,154.1740, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "INT_OFFICE","FF_Dam_Fwd", 4.1, false, true, true, 1, false);

    actorid = CreateDynamicActor(228, 3857.5439,-1709.1752,5217.1938,267.3468, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "INT_OFFICE","FF_Dam_Fwd", 4.1, false, true, true, 1, false);

    actorid = CreateDynamicActor(286, 3872.8591,-1701.4510,5216.7100,316.4881, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "DEALER", "DEALER_IDLE", 4.1, true, true, true, 1, false);

    actorid = CreateDynamicActor(223, 3860.1404,-1709.2277,5216.7129,88.5619, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "INT_SHOP","shop_out", 4.1, false, true, true, 1, false);

    actorid = CreateDynamicActor(281, 281.1917,1937.9968,1062.0924,178.8910, true, 100.0, 99, 1);
    ApplyDynamicActorAnimation(actorid, "DEALER", "DEALER_IDLE", 4.1, true, true, true, 1, false);

    actorid = CreateDynamicActor(281, 1751.8750,-1564.2821,9.9976,271.0099, true, 100.0, 0, 0);
    ApplyDynamicActorAnimation(actorid, "DEALER", "DEALER_IDLE", 4.1, true, true, true, 1, false);
}

stock CreateCameras_NewPrison() {
    for(new i = 0; i < sizeof(PrisonCamerasPos); i++) {
        PrisonCamerasInfo[i][cameraObject] = CreateDynamicObject(
            1886, PrisonCamerasPos[i][0], PrisonCamerasPos[i][1], PrisonCamerasPos[i][2], PrisonCamerasPos[i][3], 
            PrisonCamerasPos[i][4], PrisonCamerasPos[i][5]);
        PrisonCamerasInfo[i][cameraDestroyed] = false;
        PrisonCamerasInfo[i][cameraExists] = true;
        PrisonCamerasInfo[i][cameraHealth] = 70.00;
    }
}

stock CreateMap_NewPrison() { // by LennyH
    CreateObject(18981, 3871.76611, -1698.85022, 5215.20996,   0.00000, 90.00000, 0.36000);
    CreateDynamicObject(19354, 3882.98779, -1687.70032, 5217.37793,   0.00000, 0.00000, 33.48000, 99, 1);
    CreateDynamicObject(1536, 3882.10229, -1686.51367, 5215.68311,   0.00000, 0.00000, -56.02012, 99, 1);
    CreateDynamicObject(1536, 3883.78882, -1688.97461, 5215.68311,   0.00000, 0.00000, 123.48000, 99, 1);
    CreateDynamicObject(19354, 3883.86450, -1690.64368, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3880.47534, -1686.36328, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19354, 3883.86450, -1693.84741, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3883.86450, -1697.05127, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3883.86450, -1700.25720, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3882.18457, -1701.90308, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19384, 3873.89966, -1701.90308, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19400, 3874.72144, -1706.74805, 5217.37793,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(19354, 3878.97754, -1701.90906, 5215.16553,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1649, 3878.93994, -1701.87415, 5219.12500,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3878.97754, -1701.90308, 5220.56494,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19354, 3876.32251, -1701.90234, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19354, 3877.26953, -1686.36328, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19354, 3874.07007, -1686.36328, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19354, 3872.37964, -1688.01306, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19384, 3872.37012, -1700.36914, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19384, 3874.72144, -1703.54382, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(18981, 3871.90405, -1723.86230, 5215.20996,   0.00000, 90.00000, 0.36000, 99, 1);
    CreateDynamicObject(19354, 3883.86450, -1703.56555, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3883.86450, -1706.77246, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3874.04883, -1711.00269, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19354, 3877.26074, -1711.00269, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1649, 3876.91846, -1712.68433, 5216.91016,   0.00000, 90.00000, 90.00000, 99, 1);
    CreateDynamicObject(1649, 3876.91846, -1715.97180, 5216.91016,   0.00000, 90.00000, 90.00000, 99, 1);
    CreateDynamicObject(9131, 3876.91846, -1714.25525, 5217.66016,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3872.37036, -1713.20483, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19384, 3872.37036, -1716.41504, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(9131, 3876.91846, -1712.43103, 5217.66016,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(9131, 3876.91846, -1716.08069, 5217.66016,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(18762, 3876.91846, -1714.55078, 5216.05420,   0.00000, 90.00000, 90.00000, 99, 1);
    CreateDynamicObject(18762, 3876.91748, -1711.58118, 5214.05566,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(18762, 3876.91748, -1717.46716, 5214.05566,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1649, 3878.93994, -1701.87415, 5219.12500,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(9131, 3876.91846, -1712.43103, 5219.93213,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(9131, 3876.91846, -1714.25525, 5219.93213,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(9131, 3876.91846, -1716.08069, 5219.93213,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1649, 3876.91846, -1712.68433, 5216.91016,   0.00000, 90.00000, -90.00000, 99, 1);
    CreateDynamicObject(1649, 3876.91846, -1715.97180, 5216.91016,   0.00000, 90.00000, -90.00000, 99, 1);
    CreateDynamicObject(19807, 3876.69092, -1711.34595, 5216.60254,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(19807, 3876.69092, -1713.04224, 5216.60254,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(19807, 3876.69092, -1714.91003, 5216.60254,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(19807, 3876.69092, -1716.72266, 5216.60254,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(19807, 3877.16846, -1717.30151, 5216.60254,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19807, 3877.16846, -1715.41626, 5216.60254,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19807, 3877.16846, -1713.60791, 5216.60254,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19807, 3877.20850, -1711.77124, 5216.60254,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1239, 3879.24438, -1701.88196, 5218.48633,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3870.68872, -1698.79724, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19384, 3867.48047, -1698.79724, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19384, 3861.06396, -1698.79724, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19446, 3872.37036, -1706.80444, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19446, 3879.44897, -1708.42578, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19446, 3881.96289, -1713.20862, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19395, 3861.06006, -1698.77075, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1523, 3860.28003, -1698.82642, 5215.60791,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19459, 3862.72119, -1693.91138, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19459, 3859.41309, -1693.91138, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19367, 3861.07251, -1692.37415, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19367, 3861.13647, -1694.02515, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1494, 3861.12036, -1695.55725, 5215.62646,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1494, 3859.53979, -1695.55725, 5215.62646,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19367, 3861.12402, -1695.55737, 5219.88232,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2514, 3861.95459, -1692.96619, 5215.70850,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2514, 3860.25977, -1692.98962, 5215.70850,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3864.27368, -1698.79724, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19446, 3867.49072, -1689.20105, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19446, 3862.88354, -1693.91455, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3867.48242, -1701.90308, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19384, 3864.67773, -1701.90515, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19384, 3870.68896, -1701.90308, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19354, 3859.42847, -1700.29871, 5217.37793,   0.00000, 0.00000, -4.32000, 99, 1);
    CreateDynamicObject(19446, 3872.36914, -1694.17993, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19385, 3870.68213, -1701.91003, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19447, 3872.35352, -1706.81726, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19355, 3869.00952, -1703.53064, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19385, 3869.00854, -1706.72754, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19446, 3856.42871, -1706.80408, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19384, 3863.41870, -1703.59192, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3863.41870, -1706.79297, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19384, 3863.41870, -1710.00000, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19446, 3861.23657, -1711.66882, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19385, 3865.97168, -1710.00537, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19355, 3865.97168, -1706.73425, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19355, 3865.97168, -1703.54004, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19355, 3867.49927, -1701.92493, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19355, 3869.03149, -1709.80176, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19355, 3865.97168, -1713.13281, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19446, 3858.53516, -1706.75061, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19378, 3858.08545, -1706.80505, 5215.62695,   0.00000, 90.00000, 0.00000, 99, 1);
    CreateDynamicObject(19355, 3867.48413, -1714.66492, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19385, 3870.66211, -1714.66492, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19355, 3872.35352, -1713.23145, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3865.96777, -1703.59277, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3865.96777, -1706.79736, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19384, 3865.96777, -1710.00696, 5217.37988,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19385, 3872.35352, -1716.42175, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19355, 3864.39966, -1711.76111, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19446, 3858.28369, -1701.90369, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19446, 3877.19409, -1717.62646, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19354, 3883.88062, -1697.03931, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3874.04883, -1711.00269, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19395, 3861.06006, -1698.77075, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19459, 3862.72119, -1693.91138, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2514, 3861.95459, -1692.96619, 5215.70850,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2514, 3860.25977, -1692.98962, 5215.70850,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19354, 3867.48242, -1701.90308, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19384, 3870.68896, -1701.90308, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19384, 3863.41870, -1703.59192, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19384, 3863.41870, -1710.00000, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19368, 3867.77710, 5217.37793, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19367, -1744.53125, 5217.37793, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1280, 3868.56104, -1703.36169, 5216.11523,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(14782, 3866.41577, -1705.10474, 5216.70557,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19355, 3869.00952, -1713.01074, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19428, 3865.97266, -1711.56165, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19428, 3865.97266, -1707.98706, 5217.37793,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2400, 3866.11304, -1714.03955, 5215.70898,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19428, 3866.69092, -1710.83044, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2398, 3866.31177, -1704.15369, 5217.21875,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19142, 3866.32031, -1713.88574, 5217.91846,   0.00000, -90.00000, -90.00000, 99, 1);
    CreateDynamicObject(19142, 3866.32031, -1713.28662, 5217.91846,   0.00000, -90.00000, -90.00000, 99, 1);
    CreateDynamicObject(19142, 3866.32031, -1712.68726, 5217.91846,   0.00000, -90.00000, -90.00000, 99, 1);
    CreateDynamicObject(19142, 3866.32031, -1712.06348, 5217.91846,   0.00000, -90.00000, -90.00000, 99, 1);
    CreateDynamicObject(19142, 3866.32031, -1711.44128, 5217.91846,   0.00000, -90.00000, -90.00000, 99, 1);
    CreateDynamicObject(356, 3866.53076, -1714.12390, 5217.37158,   0.00000, 3.00000, 90.00000, 99, 1);
    CreateDynamicObject(356, 3866.53076, -1712.93225, 5217.37158,   0.00000, 3.00000, 90.00000, 99, 1);
    CreateDynamicObject(356, 3866.53076, -1711.74976, 5217.37158,   0.00000, 3.00000, 90.00000, 99, 1);
    CreateDynamicObject(2475, 3868.42554, -1714.51685, 5216.20605,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(343, 3868.68628, -1714.34363, 5217.00391,   -180.00000, 90.00000, 34.44000, 99, 1);
    CreateDynamicObject(343, 3868.14551, -1714.34363, 5217.00391,   -180.00000, 90.00000, 34.44000, 99, 1);
    CreateDynamicObject(343, 3867.56201, -1714.34363, 5217.00391,   -180.00000, 90.00000, 34.44000, 99, 1);
    CreateDynamicObject(356, 3866.53076, -1714.12390, 5216.55176,   0.00000, 3.00000, 90.00000, 99, 1);
    CreateDynamicObject(356, 3866.53076, -1712.93225, 5216.55176,   0.00000, 3.00000, 90.00000, 99, 1);
    CreateDynamicObject(356, 3866.53076, -1711.74976, 5216.55176,   0.00000, 3.00000, 90.00000, 99, 1);
    CreateDynamicObject(2358, 3867.78906, -1714.26672, 5216.45410,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(2043, 3868.52417, -1714.15601, 5216.44141,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(2043, 3868.52417, -1714.33606, 5216.44141,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(3016, 3868.57544, -1714.34155, 5218.52783,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(3016, 3868.12524, -1714.34155, 5218.52783,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(3016, 3867.68481, -1714.35388, 5218.52783,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(18637, 3867.18628, -1714.62598, 5217.68359,   90.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(18637, 3867.18628, -1714.62598, 5216.62061,   90.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(348, 3868.82788, -1714.28821, 5217.75830,   -90.00000, 0.00000, -154.62010, 99, 1);
    CreateDynamicObject(348, 3868.19458, -1714.28821, 5217.75830,   -90.00000, 0.00000, -154.62010, 99, 1);
    CreateDynamicObject(348, 3867.74756, -1714.28821, 5217.75830,   -90.00000, 0.00000, -154.62010, 99, 1);
    CreateDynamicObject(1280, 3868.56104, -1704.62305, 5216.11670,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2172, 3867.16797, -1693.57300, 5215.70459,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(2172, 3867.16797, -1691.66284, 5215.70459,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(2172, 3867.16797, -1689.75281, 5215.70459,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(2172, 3868.08594, -1690.76270, 5215.70459,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2172, 3868.08594, -1692.67871, 5215.70459,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2172, 3868.08594, -1694.58276, 5215.70459,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2172, 3871.84595, -1689.73279, 5215.70459,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(2172, 3863.43433, -1690.74268, 5215.70459,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2172, 3863.43433, -1692.65845, 5215.70459,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2172, 3863.43433, -1694.57043, 5215.70459,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2172, 3863.43433, -1696.48999, 5215.70459,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2172, 3871.84595, -1691.64795, 5215.70459,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(2172, 3871.84595, -1693.56641, 5215.70459,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(2172, 3871.84595, -1695.48328, 5215.70459,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(1703, 3878.10034, -1686.96155, 5215.68604,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1823, 3872.84668, -1687.40637, 5215.70605,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1703, 3874.54175, -1686.96155, 5215.68604,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2811, 3877.31592, -1686.88098, 5215.67725,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1703, 3872.99243, -1690.05737, 5215.68604,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1703, 3872.99243, -1693.65186, 5215.68604,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2811, 3872.94702, -1690.84058, 5215.67725,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1703, 3883.25122, -1690.93250, 5215.68604,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(1823, 3883.84253, -1694.50183, 5215.70605,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1703, 3883.25122, -1695.03101, 5215.68604,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(1823, 3873.44067, -1695.21741, 5215.70605,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1703, 3872.99243, -1697.77441, 5215.68604,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2811, 3883.29297, -1697.97046, 5215.67725,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1703, 3883.25122, -1698.83826, 5215.68604,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(2604, 3879.77588, -1702.49536, 5216.50195,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2161, 3877.06543, -1702.00293, 5217.03076,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2164, 3875.30493, -1702.00293, 5215.67529,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2161, 3877.06543, -1702.00293, 5215.68262,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(19355, 3861.19458, -1711.76111, 5217.37793,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1806, 3864.87183, -1695.63843, 5215.82275,   0.00000, 0.00000, 116.34000, 99, 1);
    CreateDynamicObject(1502, 3866.70532, -1698.81580, 5215.62695,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1502, 3863.38989, -1702.81079, 5215.62695,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(1502, 3863.44019, -1710.74915, 5215.62695,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1502, 3865.41577, -1701.88184, 5215.62695,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(1502, 3874.69629, -1702.76184, 5215.62695,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(19805, 3869.10425, -1703.90942, 5217.21875,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1649, 3874.68652, -1706.43042, 5216.67041,   0.00000, 90.00000, 90.00000, 99, 1);
    CreateDynamicObject(1649, 3874.73901, -1706.43042, 5216.67041,   0.00000, 90.00000, -90.00000, 99, 1);
    CreateDynamicObject(1806, 3864.73584, -1694.07312, 5215.82275,   0.00000, 0.00000, 85.62000, 99, 1);
    CreateDynamicObject(1806, 3864.71143, -1692.00146, 5215.82275,   0.00000, 0.00000, 109.86000, 99, 1);
    CreateDynamicObject(1806, 3864.76123, -1690.44666, 5215.82275,   0.00000, 0.00000, 59.82006, 99, 1);
    CreateDynamicObject(1806, 3869.43628, -1692.27197, 5215.82275,   0.00000, 0.00000, 85.62001, 99, 1);
    CreateDynamicObject(1806, 3869.40381, -1694.30103, 5215.82275,   0.00000, 0.00000, 70.26000, 99, 1);
    CreateDynamicObject(1806, 3869.47876, -1690.24988, 5215.82275,   0.00000, 0.00000, 113.82000, 99, 1);
    CreateDynamicObject(1806, 3870.57153, -1694.29114, 5215.82275,   0.00000, 0.00000, -82.74000, 99, 1);
    CreateDynamicObject(1806, 3870.47168, -1692.10559, 5215.82275,   0.00000, 0.00000, -99.72004, 99, 1);
    CreateDynamicObject(1806, 3870.54321, -1690.48560, 5215.82275,   0.00000, 0.00000, -72.48003, 99, 1);
    CreateDynamicObject(1806, 3870.47705, -1695.77197, 5215.82275,   0.00000, 0.00000, -119.46000, 99, 1);
    CreateDynamicObject(1806, 3865.77124, -1694.21082, 5215.82275,   0.00000, 0.00000, -90.90000, 99, 1);
    CreateDynamicObject(1806, 3865.75928, -1692.35559, 5215.82275,   0.00000, 0.00000, -105.42010, 99, 1);
    CreateDynamicObject(1806, 3865.82251, -1690.26379, 5215.82275,   0.00000, 0.00000, -100.14007, 99, 1);
    CreateDynamicObject(2121, 3878.71411, -1716.99451, 5216.20850,   0.00000, 0.00000, -97.56000, 99, 1);
    CreateDynamicObject(1810, 3875.57617, -1714.91528, 5215.69922,   0.00000, 0.00000, 79.56000, 99, 1);
    CreateDynamicObject(2121, 3878.69263, -1715.20471, 5216.20850,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(2121, 3878.60889, -1713.40051, 5216.20850,   0.00000, 0.00000, -83.04003, 99, 1);
    CreateDynamicObject(2121, 3878.68726, -1711.71680, 5216.20850,   0.00000, 0.00000, -102.96004, 99, 1);
    CreateDynamicObject(1810, 3875.36255, -1711.39111, 5215.69922,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1810, 3875.44653, -1713.00977, 5215.69922,   0.00000, 0.00000, 94.02000, 99, 1);
    CreateDynamicObject(1810, 3875.42798, -1716.66138, 5215.69922,   0.00000, 0.00000, 93.54000, 99, 1);
    CreateDynamicObject(16378, 3858.28833, -1704.35791, 5216.46680,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(2191, 3858.54419, -1706.14551, 5215.58643,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(2164, 3860.92529, -1706.62500, 5215.70020,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(2257, 3856.55029, -1704.21814, 5217.58105,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2289, 3856.55615, -1710.60815, 5217.54102,   0.00000, 0.00000, 90.24000, 99, 1);
    CreateDynamicObject(2207, 3859.27124, -1710.16199, 5215.69336,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1714, 3857.31836, -1709.21411, 5215.68750,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2108, 3856.94458, -1707.25574, 5215.71436,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2244, 3862.99243, -1711.17603, 5215.96875,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2190, 3859.23950, -1708.29871, 5216.45947,   0.00000, 0.00000, -35.40000, 99, 1);
    CreateDynamicObject(19808, 3858.68457, -1708.71399, 5216.47754,   0.00000, 0.00000, -35.34000, 99, 1);
    CreateDynamicObject(2280, 3857.00659, -1707.67920, 5217.51563,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2267, 3856.55615, -1709.09729, 5217.99756,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1670, 3859.10596, -1708.92310, 5216.48975,   0.00000, 0.00000, 63.30000, 99, 1);
    CreateDynamicObject(1663, 3860.69214, -1709.92114, 5216.15479,   0.00000, 0.00000, -106.07995, 99, 1);
    CreateDynamicObject(1663, 3860.65308, -1708.45129, 5216.15479,   0.00000, 0.00000, -77.45990, 99, 1);
    CreateDynamicObject(2412, 3874.80420, -1706.59399, 5215.72168,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2412, 3872.99097, -1706.59399, 5215.72168,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1808, 3883.45801, -1708.01843, 5215.70020,   0.00000, 0.00000, -139.02000, 99, 1);
    CreateDynamicObject(2066, 3882.25488, -1702.49695, 5215.68408,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2066, 3883.15918, -1702.49695, 5215.68408,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1722, 3868.58105, -1701.72827, 5215.70801,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1722, 3867.91846, -1701.72827, 5215.70801,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1722, 3867.26709, -1701.72827, 5215.70801,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1722, 3866.61597, -1701.72827, 5215.70801,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2008, 3875.37695, -1707.23694, 5215.70605,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(2309, 3876.73608, -1706.51416, 5215.72119,   0.00000, 0.00000, 86.10000, 99, 1);
    CreateDynamicObject(2210, 3875.34619, -1708.02014, 5216.44385,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2167, 3877.98291, -1708.32080, 5215.69678,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(2167, 3878.88525, -1708.32080, 5215.69678,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(2165, 3881.58887, -1707.85962, 5215.70898,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(2309, 3881.36426, -1706.47986, 5215.72119,   0.00000, 0.00000, 156.36000, 99, 1);
    CreateDynamicObject(2309, 3880.96387, -1704.04834, 5215.72119,   0.00000, 0.00000, 4.68000, 99, 1);
    CreateDynamicObject(19302, 3873.96094, -1701.88953, 5216.92334,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(19302, 3869.00537, -1706.79321, 5216.92334,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19302, 3865.94946, -1710.06860, 5216.92334,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(19302, 3872.34839, -1716.47314, 5216.92334,   0.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1533, 3869.88672, -1714.57227, 5215.61328,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(2608, 3878.46704, -1708.14746, 5218.73633,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(2611, 3876.22290, -1701.77759, 5217.54736,   0.00000, 0.00000, 180.00000, 99, 1);
    CreateDynamicObject(2612, 3872.22144, -1709.14575, 5217.54736,   0.00000, 0.00000, -90.00000, 99, 1);
    CreateDynamicObject(16779, 3859.46826, -1704.13440, 5219.24756,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1886, 3862.83203, -1711.15833, 5219.23877,   15.00000, 0.00000, -115.49990, 99, 1);
    CreateDynamicObject(19378, 3858.12549, -1706.80505, 5219.16211,   0.00000, 90.00000, 0.00000, 99, 1);
    CreateDynamicObject(1886, 3862.83203, -1706.29834, 5219.23877,   15.00000, 0.00000, -115.49990, 99, 1);
    CreateDynamicObject(2253, 3863.01343, -1706.36475, 5215.98096,   0.00000, 0.00000, 0.00000, 99, 1);
    CreateDynamicObject(1886, 3860.03125, -1700.35498, 5219.23877,   15.00000, 0.00000, 90.00000, 99, 1);
    CreateDynamicObject(1886, 3863.42407, -1698.30151, 5219.23877,   15.00000, 0.00000, 134.15996, 99, 1);
    CreateDynamicObject(1886, 3871.94824, -1698.20447, 5219.23877,   15.00000, 0.00000, 214.97960, 99, 1);
    CreateDynamicObject(1886, 3882.50513, -1688.02234, 5219.23877,   15.00000, 0.00000, -56.16036, 99, 1);
    CreateDynamicObject(1886, 3883.40674, -1707.91504, 5219.23877,   15.00000, 0.00000, 220.97932, 99, 1);
    CreateDynamicObject(1886, 3881.52417, -1708.91223, 5219.23877,   15.00000, 0.00000, -36.66087, 99, 1);
    CreateDynamicObject(1886, 3872.77539, -1711.51624, 5219.23877,   15.00000, 0.00000, 36.59916, 99, 1);
    CreateDynamicObject(18981, 3871.76392, -1698.86401, 5219.59521,   0.00000, 90.00000, 0.00000, 99, 1);
    CreateDynamicObject(18981, 3847.74536, -1718.11047, 4219.59521,   0.00000, 90.00000, 0.00000, 99, 1);
    CreateDynamicObject(18981, 3872.74414, -1723.86230, 5219.59521,   0.00000, 90.00000, 0.00000, 99, 1);
    CreateDynamicObject(1886, 3871.84375, -1714.15295, 5219.09277,   20.02200, 0.00000, -156.05997, 99, 1);

    CreateDynamicObject(967, 1751.20618, -1564.26208, 9.02521,   0.00000, 0.00000, -90.53986);
    
    new tmpobj;
    tmpobj = CreateDynamicObject(19449, 1803.0480, -1576.1109, 17.9174, 0.0000, 0.0000, -10.3600);
    SetDynamicObjectMaterial(tmpobj, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF3A3A3A);
    tmpobj = CreateDynamicObject(19482, 1803.1831, -1576.0673, 17.0000, 0.0000, 0.0000, -11.0000);
    SetDynamicObjectMaterialText(tmpobj, 0, "Prisão La Sante", 130, "Arial", 80, 1, 0xFFFFFFFF, 0x00000000, 0);

    // Cameras
    //RemoveBuildingForPlayer(playerid, 4099, 1770.0469, -1549.4141, 10.4688, 0.25);
    CreateCameras_NewPrison();

    printf("[MAPA %d]: Nova Prisão... Carregado com sucesso!", gm_count[COUNT_CREATEMAP]);
    gm_count[COUNT_CREATEMAP]++;

    Create3DTextLabel("{FFFFFF}Prisão La Sante\n{FFFFFF}Aperte a tecla {FF7766}"_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para se entregar para a justiça\ne receber uma redução na sua penalidade", 0xFFFFFFFF, 289.3872,-136.8302,1004.0741, 15.0, 99);
    CreateDynamicPickup(1210, 23, 289.3872,-136.8302,1004.0741, 99, 1); //Entregar-se

    Create3DTextLabel("{FFFFFF}Menu de Advogados\n{FFFFFF}Aperte a tecla {FF7766}"_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para ajustar um preso", 0xFFFFFFFF, 282.3564,1944.4896,1062.0924, 15.0, 99);
    CreateDynamicPickup(1210, 23, 282.3564,1944.4896,1062.0924, 99, 1); //Menu de Advogados

    Create3DTextLabel("{FFFFFF}Área de Celas\n{FFFFFF}Aperte a tecla {FF7766}"_KEY_PATH_ENTER_INT_COLOR" {FFFFFF}para acessá-la", 0xFFFFFFFF, 282.5788,-139.5177,1004.0825, 10.0, 99);
    CreateDynamicPickup(11749, 23, 282.5788,-139.5177,1004.0825, 99, 1); //Menu de Advogados
    
    CreateActors_NewPrison();
}

timer NotifyCopOnCameraDestroying[5000](playerid, cameraid) {
    if(!PrisonCamerasInfo[cameraid][cameraDestroyed]) {
        static string[256];
        format(string, sizeof(string), "<< %s está tentando explodir as câmeras da prisão La Sante. >>", PlayerName[playerid]);
        SendCopMessage(COLOR_LIGHTRED, string);
        SetPlayerCriminal(playerid, 255, "Vandalismo");
        ShowPlayerBaloonInfo(playerid, "Os policiais foram notificados do seu ato de vandalismo, cuidado!", 5000);
    }
	return 1;
}

timer RestoreCamera[600000](cameraid) {
    PrisonCamerasInfo[cameraid][cameraObject] = CreateDynamicObject(
        1886, PrisonCamerasPos[cameraid][0], PrisonCamerasPos[cameraid][1], PrisonCamerasPos[cameraid][2], PrisonCamerasPos[cameraid][3], 
        PrisonCamerasPos[cameraid][4], PrisonCamerasPos[cameraid][5]);
    PrisonCamerasInfo[cameraid][cameraDestroyed] = false;
    PrisonCamerasInfo[cameraid][cameraHealth] = 70.00;
	return 1;
}

hook OnPlayerWeaponShot(playerid, WEAPON:weaponid, hittype, hitid, Float:x, Float:y, Float:z) {
    new Float:fOriginX, Float:fOriginY, Float:fOriginZ, Float:fHitPosX, Float:fHitPosY, Float:fHitPosZ;
    GetPlayerLastShotVectors(playerid, fOriginX, fOriginY, fOriginZ, fHitPosX, fHitPosY, fHitPosZ);

    for(new i = 0; i < sizeof(PrisonCamerasPos); i++) {
        if(!PrisonCamerasInfo[i][cameraDestroyed] && 
            GetDistanceBetweenPoints(PrisonCamerasPos[i][0], PrisonCamerasPos[i][1], PrisonCamerasPos[i][2], fHitPosX, fHitPosY, fHitPosZ) <= 1.5 &&
            !IsACop(i)
        ) {
            new Float:damage = GetWeaponDamage(weaponid);

            PrisonCamerasInfo[i][cameraHealth] -= damage;
            if(PrisonCamerasInfo[i][cameraHealth] <= 0.0) {
                CreateExplosion(PrisonCamerasPos[i][0], PrisonCamerasPos[i][1], PrisonCamerasPos[i][2] + 5, 1, 3);
                DestroyDynamicObject(PrisonCamerasInfo[i][cameraObject]);
                stop CameraAlertTimer[playerid];
                PrisonCamerasInfo[i][cameraRegenTimer] = defer RestoreCamera(i);
                PrisonCamerasInfo[i][cameraDestroyed] = true;
            }
            else {
                if(!Timer_IsRunning(CameraAlertTimer[playerid])) {
                    CameraAlertTimer[playerid] = defer NotifyCopOnCameraDestroying(playerid, i);
                }
            }
            break;
        }
    }
    return 1;
}