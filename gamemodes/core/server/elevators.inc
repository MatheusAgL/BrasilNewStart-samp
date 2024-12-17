// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Example Filterscript for the new LS BeachSide Building with Elevator
// --------------------------------------------------------------------
// Original elevator code by Zamaroht in 2010
//
// Updated by Kye in 2011
// * Added a sound effect for the elevator starting/stopping
//
// Edited by Matite in January 2015
// * Added code to remove the existing building, add the new building and
//   adapted the elevator code so it works in this new building
//
// Updated to v1.02 by Matite in February 2015
// * Added code for the new car park object and edited the elevator to
//   include the car park
//
// This script creates the new LS BeachSide building object, removes the
// existing GTASA building object, adds the new car park object and creates
// an elevator that can be used to travel between all levels.
//
// You can un-comment the OnPlayerCommandText callback below to enable a simple
// teleport command (/lsb) that teleports you to the LS BeachSide building.
//
// Warning...
// This script uses a total of:
// * 34 objects = 1 for the elevator, 2 for the elevator doors, 28 for the elevator
//   floor doors, 1 for the building (replacement LS BeachSide building), 1 for the
//   interior floors object and 1 for the underground car park object
// * 15 3D Text Labels = 14 on the floors and 1 in the elevator
// * 1 dialog (for the elevator - dialog ID 877)
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Includes necessárias
#include < YSI_Coding\y_hooks >

//-------------------------------------------------------

// Movement speed of the elevator
#define ELEVATOR_SPEED_B      (5.0)

// Movement speed of the doors
#define DOORS_SPEED_B         (5.0)

// Time in ms that the elevator will wait in each floor before continuing with the queue...
// be sure to give enough time for doors to open
#define ELEVATOR_WAIT_TIME_B  (5000)

// Dialog ID for the LS BeachSide elevator dialog
#define DIALOG_ID_B           (877)

#define X_DOOR_CLOSED       (1786.627685)
#define X_DOOR_R_OPENED     (1785.027685)
#define X_DOOR_L_OPENED     (1788.227685)
#define GROUND_Z_COORD      (14.511476)
#define ELEVATOR_OFFSET     (0.059523)

//-------------------------------------------------------
#define ELEVATOR_SPEED      (5.0)   // Movement speed of the elevator.
#define DOORS_SPEED         (5.0)   // Movement speed of the doors.
#define ELEVATOR_WAIT_TIME  (5000)  // Time in ms that the elevator will wait in each floor before continuing with the queue.
									// Be sure to give enough time for doors to open.
//-------------------------------------------------------

// Position defines
#define X_DOOR_R_OPENED_B     (289.542419)
#define X_DOOR_L_OPENED_B     (286.342407)
#define Y_DOOR_R_OPENED_B     (-1609.640991)
#define Y_DOOR_L_OPENED_B     (-1609.076049)

#define X_FDOOR_R_OPENED_B    (289.492431)
#define X_FDOOR_L_OPENED_B    (286.292419)
#define Y_FDOOR_R_OPENED_B    (-1609.870971)
#define Y_FDOOR_L_OPENED_B    (-1609.306030)

#define GROUND_Z_COORD_B      (18.755348)     // (33.825077)
#define X_ELEVATOR_POS_B      (287.942413)
#define Y_ELEVATOR_POS_B      (-1609.341064)

// Elevator state defines
#define ELEVATOR_STATE_IDLE_B     (0)
#define ELEVATOR_STATE_WAITING_B  (1)
#define ELEVATOR_STATE_MOVING_B   (2)

// Invalid floor define
#define INVALID_FLOOR_B           (-1)

// Used for chat text messages
#define COLOR_MESSAGE_YELLOW_B        0xFFDD00AA

// -----------------------------------------------------------------------------
//Elevador

/* ------------------
// Constants:
-------------------*/
static FloorNames[21][] =
{
	"Terraço",
	"Primeiro andar",
	"Segundo andar",
	"Terceiro andar",
	"Quarto andar",
	"Quinto andar",
	"Sexto andar",
	"Setimo andar",
	"Oitavo andar",
	"Nono andar",
	"Décimo andar",
	"Décimo primeiro andar",
	"Décimo segundo andar",
	"Décimo terceiro andar",
	"Décimo quarto andar",
	"Décimo quinto andar",
	"Décimo sexto andar",
	"Décimo setimo andar",
	"Décimo oitavo andar",
	"Décimo nono andar",
	"Ultimo andar"
};

//-------------------------------------------------------

static Float:FloorZOffsets[21] =
{
    0.0,		// 0.0,
    8.5479,		// 8.5479,
    13.99945,   // 8.5479 + (5.45155 * 1.0),
    19.45100,   // 8.5479 + (5.45155 * 2.0),
    24.90255,   // 8.5479 + (5.45155 * 3.0),
    30.35410,   // 8.5479 + (5.45155 * 4.0),
    35.80565,   // 8.5479 + (5.45155 * 5.0),
    41.25720,   // 8.5479 + (5.45155 * 6.0),
    46.70875,   // 8.5479 + (5.45155 * 7.0),
    52.16030,   // 8.5479 + (5.45155 * 8.0),
    57.61185,   // 8.5479 + (5.45155 * 9.0),
    63.06340,   // 8.5479 + (5.45155 * 10.0),
    68.51495,   // 8.5479 + (5.45155 * 11.0),
    73.96650,   // 8.5479 + (5.45155 * 12.0),
    79.41805,   // 8.5479 + (5.45155 * 13.0),
    84.86960,   // 8.5479 + (5.45155 * 14.0),
    90.32115,   // 8.5479 + (5.45155 * 15.0),
    95.77270,   // 8.5479 + (5.45155 * 16.0),
    101.22425,  // 8.5479 + (5.45155 * 17.0),
    106.67580,	// 8.5479 + (5.45155 * 18.0),
    112.12735	// 8.5479 + (5.45155 * 19.0)
};

// Defines
// -------

new Obj_Elevator, Obj_ElevatorDoors[2],
	Obj_FloorDoors[21][2];

new Text3D:Label_Elevator, Text3D:Label_Floors[21];
new PlayerText:textCBug[MAX_PLAYERS];

#define ELEVATOR_STATE_IDLE     (0)
#define ELEVATOR_STATE_WAITING  (1)
#define ELEVATOR_STATE_MOVING   (2)

new ElevatorState,
	ElevatorFloor;  // If Idle or Waiting, this is the current floor. If Moving, the floor it's moving to.

#define INVALID_FLOOR           (-1)

new ElevatorQueue[21],  	// Floors in queue.
	FloorRequestedBy[21];   // FloorRequestedBy[floor_id] = playerid; - Points out who requested which floor.

new ElevatorBoostTimer;     // Timer that makes the elevator move faster after players start surfing the object.


stock Float:GetElevatorZCoordForFloor(floorid)
    return (GROUND_Z_COORD + FloorZOffsets[floorid] + ELEVATOR_OFFSET); // A small offset for the elevator object itself.


stock Float:GetDoorsZCoordForFloor(floorid)
	return (GROUND_Z_COORD + FloorZOffsets[floorid]);

// -----------------------------------------------------------------------------
// Constants
// ---------

// Elevator floor names for the 3D text labels
new FloorNames_B[14][] =
{
	"Estacionamento",
	"Térreo",
	"Primeiro Andar",
	"Segundo Andar",
	"Terceiro Andar",
	"Quarto Andar",
	"Quinto Andar",
	"Sexto Andar",
	"Sétimo Andar",
	"Oitavo Andar",
	"Nono Andar",
	"Décimo Andar",
	"Décimo Primeiro Andar",
	"Décimo Segundo Andar"
};

// Elevator floor Z heights
static Float:FloorZOffsets_B[14] =
{
    0.0, 		// Car Park
    15.069729,  // Ground Floor
    29.130733,	// First Floor
    33.630733,  // Second Floor = 29.130733 + 4.5
    38.130733,  // Third Floor = 33.630733 + 4.5
    42.630733,  // Fourth Floor = 38.130733 + 4.5
    47.130733,  // Fifth Floor = 42.630733 + 4.5
    51.630733,  // Sixth Floor = 47.130733 + 4.5
    56.130733,  // Seventh Floor = 51.630733 + 4.5
    60.630733,  // Eighth Floor = 56.130733 + 4.5
    65.130733,  // Ninth Floor = 60.630733 + 4.5
    69.630733,  // Tenth Floor = 65.130733 + 4.5
    74.130733,  // Eleventh Floor = 69.630733 + 4.5
    78.630733,  // Twelfth Floor = 74.130733 + 4.5
};

// -----------------------------------------------------------------------------
// Variables
// ---------

// Stores the created object numbers of the elevator, the elevator doors and
// the elevator floor doors so they can be destroyed when the filterscript
// is unloaded
new Obj_Elevator_B, Obj_Elevator_BDoors_B[2], Obj_FloorDoors_B[14][2];

// Stores a reference to the 3D text labels used on each floor and inside the
// elevator itself so they can be detroyed when the filterscript is unloaded
new Text3D:Label_Elevator_B, Text3D:Label_Floors_B[14];

// Stores the current state of the elevator (ie ELEVATOR_STATE_IDLE_B,
// ELEVATOR_STATE_WAITING_B or ELEVATOR_STATE_MOVING_B)
new ElevatorState_B;

// Stores the current floor the elevator is on or heading to... if the value is
// ELEVATOR_STATE_IDLE_B or ELEVATOR_STATE_WAITING_B this is the current floor. If
// the value is ELEVATOR_STATE_MOVING_B then it is the floor it's moving to
new	ElevatorFloor_B;

// Stores the elevator queue for each floor
new ElevatorQueue_B[14];

// Stores who requested the floor for the elevator queue...
// FloorRequestedBy_B[floor_id] = playerid;  (stores who requested which floor)
new	FloorRequestedBy_B[14];

// Used for a timer that makes the elevator move faster after players start
// surfing the object
new ElevatorBoostTimer_B;

// -----------------------------------------------------------------------------
// Function Forwards
// -----------------

// Public:
forward CallElevator_B(playerid, floorid);    // You can use INVALID_PLAYER_ID too.
forward ShowElevatorDialog_B(playerid);

// Private:
forward Elevator_Initialize_B();
forward Elevator_Destroy_B();

forward Elevator_OpenDoors_B();
forward Elevator_CloseDoors_B();
forward Floor_OpenDoors_B(floorid);
forward Floor_CloseDoors_B(floorid);

forward Elevator_MoveToFloor_B(floorid);
forward Elevator_Boost_B(floorid);        	// Increases the elevator speed until it reaches 'floorid'.
forward Elevator_TurnToIdle_B();

forward ReadNextFloorInQueue_B();
forward RemoveFirstQueueFloor_B();
forward AddFloorToQueue_B(floorid);
forward IsFloorInQueue_B(floorid);
forward ResetElevatorQueue_B();

forward DidPlayerRequestElevator_B(playerid);

forward Float:GetElevatorZCoordForFloor_B(floorid);
forward Float:GetDoorsZCoordForFloor_B(floorid);

// -----------------------------------------------------------------------------
// Callbacks
// ---------

hook OnObjectMoved(objectid)
{
	// Create variables
    new Float:x, Float:y, Float:z;

    // Loop
	for(new i; i < sizeof(Obj_FloorDoors_B); i ++)
	{
	    // Check if the object that moved was one of the elevator floor doors
		if(objectid == Obj_FloorDoors_B[i][0])
		{
		    GetObjectPos(Obj_FloorDoors_B[i][0], x, y, z);

            // Some floor doors have shut, move the elevator to next floor in queue:
            if (y < Y_DOOR_L_OPENED_B - 0.5)
		    {
				Elevator_MoveToFloor_B(ElevatorQueue_B[0]);
				RemoveFirstQueueFloor_B();
			}
		}
	}

	if(objectid == Obj_Elevator)   // The elevator reached the specified floor.
	{
	    KillTimer(ElevatorBoostTimer);  // Kills the timer, in case the elevator reached the floor before boost.

	    FloorRequestedBy[ElevatorFloor] = INVALID_PLAYER_ID;

	    Elevator_OpenDoors();
	    Floor_OpenDoors(ElevatorFloor);

	    GetObjectPos(Obj_Elevator, x, y, z);
	    Label_Elevator	= Create3DTextLabel("{CCCCCC}Pressione '{FFFFFF}ENTER{CCCCCC}' para usar o elevador", 0xCCCCCCAA, 1784.9822, -1302.0426, z - 0.9, 10.0, 0);

	    ElevatorState 	= ELEVATOR_STATE_WAITING;
	    SetTimer("Elevator_TurnToIdle", ELEVATOR_WAIT_TIME, false);
	}

	if(objectid == Obj_Elevator_B)   // The elevator reached the specified floor.
	{
	    KillTimer(ElevatorBoostTimer_B);  // Kills the timer, in case the elevator reached the floor before boost.

	    FloorRequestedBy_B[ElevatorFloor_B] = INVALID_PLAYER_ID;

	    Elevator_OpenDoors_B();
	    Floor_OpenDoors_B(ElevatorFloor_B);

	    GetObjectPos(Obj_Elevator_B, x, y, z);
	    Label_Elevator_B	= Create3DTextLabel("{CCCCCC}Aperte '{FFFFFF}ENTER{CCCCCC}' para usar o elevador", 0xCCCCCCAA, X_ELEVATOR_POS_B + 1.6, Y_ELEVATOR_POS_B - 1.85, z - 0.4, 4.0, 0, true);

	    ElevatorState_B 	= ELEVATOR_STATE_WAITING_B;
	    SetTimer("Elevator_TurnToIdle_B", ELEVATOR_WAIT_TIME_B, false);
	}

	return 1;
}

// ------------------------ Functions ------------------------
stock Elevator_Initialize_B()
{
	// Create the elevator and elevator door objects
	Obj_Elevator_B 			= CreateObject(18755, X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, GROUND_Z_COORD_B, 0.000000, 0.000000, 80.000000);
	Obj_Elevator_BDoors_B[0] 	= CreateObject(18757, X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, GROUND_Z_COORD_B, 0.000000, 0.000000, 80.000000);
	Obj_Elevator_BDoors_B[1] 	= CreateObject(18756, X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, GROUND_Z_COORD_B, 0.000000, 0.000000, 80.000000);

	// Create the 3D text label for inside the elevator
	Label_Elevator_B = Create3DTextLabel("{CCCCCC}Aperte '{FFFFFF}ENTER{CCCCCC}' para usar o elevador", 0xCCCCCCAA, X_ELEVATOR_POS_B + 1.6, Y_ELEVATOR_POS_B - 1.85, GROUND_Z_COORD_B - 0.4, 4.0, 0, true);

	// Create variables
	new string[128], Float:z;

	// Loop
	for (new i; i < sizeof(Obj_FloorDoors_B); i ++)
	{
	    // Create elevator floor door objects
	    Obj_FloorDoors_B[i][0] 	= CreateObject(18757, X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B - 0.245, GetDoorsZCoordForFloor_B(i) + 0.05, 0.000000, 0.000000, 80.000000);
		Obj_FloorDoors_B[i][1] 	= CreateObject(18756, X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B - 0.245, GetDoorsZCoordForFloor_B(i) + 0.05, 0.000000, 0.000000, 80.000000);

        // Format string for the floor 3D text label
		format(string, sizeof(string), "{CCCCCC}[%s]\n{CCCCCC}Aperte '{FFFFFF}ENTER{CCCCCC}' para chamar", FloorNames_B[i]);

		// Get label Z position
		z = GetDoorsZCoordForFloor_B(i);

		// Create floor label
		Label_Floors_B[i] = Create3DTextLabel(string, 0xCCCCCCAA, X_ELEVATOR_POS_B + 2, Y_ELEVATOR_POS_B -3, z - 0.2, 10.5, 0, true);
	}

	// Open the car park floor doors and the elevator doors
	Floor_OpenDoors_B(0);
	Elevator_OpenDoors_B();

	// Exit here
	return 1;
}

stock Elevator_Destroy_B()
{
	// Destroys the elevator.

	DestroyObject(Obj_Elevator_B);
	DestroyObject(Obj_Elevator_BDoors_B[0]);
	DestroyObject(Obj_Elevator_BDoors_B[1]);
	Delete3DTextLabel(Label_Elevator_B);

	for(new i; i < sizeof(Obj_FloorDoors_B); i ++)
	{
	    DestroyObject(Obj_FloorDoors_B[i][0]);
		DestroyObject(Obj_FloorDoors_B[i][1]);
		Delete3DTextLabel(Label_Floors_B[i]);
	}

	return 1;
}

stock Elevator_OpenDoors_B()
{
	// Opens the elevator's doors.

	new Float:x, Float:y, Float:z;

	GetObjectPos(Obj_Elevator_BDoors_B[0], x, y, z);
	MoveObject(Obj_Elevator_BDoors_B[0], X_DOOR_L_OPENED_B, Y_DOOR_L_OPENED_B, z, DOORS_SPEED_B);
	MoveObject(Obj_Elevator_BDoors_B[1], X_DOOR_R_OPENED_B, Y_DOOR_R_OPENED_B, z, DOORS_SPEED_B);

	return 1;
}

stock Elevator_CloseDoors_B()
{
    // Closes the elevator's doors.

    if(ElevatorState_B == ELEVATOR_STATE_MOVING_B)
	    return 0;

    new Float:x, Float:y, Float:z;

	GetObjectPos(Obj_Elevator_BDoors_B[0], x, y, z);
	MoveObject(Obj_Elevator_BDoors_B[0], X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, z, DOORS_SPEED_B);
	MoveObject(Obj_Elevator_BDoors_B[1], X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, z, DOORS_SPEED_B);

	return 1;
}

stock Floor_OpenDoors_B(floorid)
{
    // Opens the doors at the specified floor.

    MoveObject(Obj_FloorDoors_B[floorid][0], X_FDOOR_L_OPENED_B, Y_FDOOR_L_OPENED_B, GetDoorsZCoordForFloor_B(floorid) + 0.05, DOORS_SPEED_B);
	MoveObject(Obj_FloorDoors_B[floorid][1], X_FDOOR_R_OPENED_B, Y_FDOOR_R_OPENED_B, GetDoorsZCoordForFloor_B(floorid) + 0.05, DOORS_SPEED_B);

	PlaySoundForPlayersInRange(6401, 50.0, X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, GetDoorsZCoordForFloor_B(floorid) + 5.0);

	return 1;
}

stock Floor_CloseDoors_B(floorid)
{
    // Closes the doors at the specified floor.

    MoveObject(Obj_FloorDoors_B[floorid][0], X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B - 0.245, GetDoorsZCoordForFloor_B(floorid) + 0.05, DOORS_SPEED_B);
	MoveObject(Obj_FloorDoors_B[floorid][1], X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B - 0.245, GetDoorsZCoordForFloor_B(floorid) + 0.05, DOORS_SPEED_B);

	PlaySoundForPlayersInRange(6401, 50.0, X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, GetDoorsZCoordForFloor_B(floorid) + 5.0);

	return 1;
}

stock Elevator_MoveToFloor_B(floorid)
{
	// Moves the elevator to specified floor (doors are meant to be already closed).

	ElevatorState_B = ELEVATOR_STATE_MOVING_B;
	ElevatorFloor_B = floorid;

	// Move the elevator slowly, to give time to clients to sync the object surfing. Then, boost it up:
	MoveObject(Obj_Elevator_B, X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, GetElevatorZCoordForFloor_B(floorid), 0.25);
    MoveObject(Obj_Elevator_BDoors_B[0], X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, GetDoorsZCoordForFloor_B(floorid), 0.25);
    MoveObject(Obj_Elevator_BDoors_B[1], X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, GetDoorsZCoordForFloor_B(floorid), 0.25);
    Delete3DTextLabel(Label_Elevator_B);

	ElevatorBoostTimer_B = SetTimerEx("Elevator_Boost_B", 2000, false, "i", floorid);

	return 1;
}

public Elevator_Boost_B(floorid)
{
	// Increases the elevator's speed until it reaches 'floorid'
	StopObject(Obj_Elevator_B);
	StopObject(Obj_Elevator_BDoors_B[0]);
	StopObject(Obj_Elevator_BDoors_B[1]);

	MoveObject(Obj_Elevator_B, X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, GetElevatorZCoordForFloor_B(floorid), ELEVATOR_SPEED_B);
    MoveObject(Obj_Elevator_BDoors_B[0], X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, GetDoorsZCoordForFloor_B(floorid), ELEVATOR_SPEED_B);
    MoveObject(Obj_Elevator_BDoors_B[1], X_ELEVATOR_POS_B, Y_ELEVATOR_POS_B, GetDoorsZCoordForFloor_B(floorid), ELEVATOR_SPEED_B);

	return 1;
}

public Elevator_TurnToIdle_B()
{
	ElevatorState_B = ELEVATOR_STATE_IDLE_B;
	ReadNextFloorInQueue_B();

	return 1;
}

stock RemoveFirstQueueFloor_B()
{
	// Removes the data in ElevatorQueue_B[0], and reorders the queue accordingly.

	for(new i; i < sizeof(ElevatorQueue_B) - 1; i ++)
	    ElevatorQueue_B[i] = ElevatorQueue_B[i + 1];

	ElevatorQueue_B[sizeof(ElevatorQueue_B) - 1] = INVALID_FLOOR_B;

	return 1;
}

stock AddFloorToQueue_B(floorid)
{
 	// Adds 'floorid' at the end of the queue.

	// Scan for the first empty space:
	new slot = -1;
	for(new i; i < sizeof(ElevatorQueue_B); i ++)
	{
	    if(ElevatorQueue_B[i] == INVALID_FLOOR_B)
	    {
	        slot = i;
	        break;
	    }
	}

	if(slot != -1)
	{
	    ElevatorQueue_B[slot] = floorid;

     	// If needed, move the elevator.
	    if(ElevatorState_B == ELEVATOR_STATE_IDLE_B)
	        ReadNextFloorInQueue_B();

	    return 1;
	}

	return 0;
}

stock ResetElevatorQueue_B()
{
	// Resets the queue.

	for(new i; i < sizeof(ElevatorQueue_B); i ++)
	{
	    ElevatorQueue_B[i] 	= INVALID_FLOOR_B;
	    FloorRequestedBy_B[i] = INVALID_PLAYER_ID;
	}

	return 1;
}

stock IsFloorInQueue_B(floorid)
{
	// Checks if the specified floor is currently part of the queue.

	for(new i; i < sizeof(ElevatorQueue_B); i ++)
	    if(ElevatorQueue_B[i] == floorid)
	        return 1;

	return 0;
}

stock ReadNextFloorInQueue_B()
{
	// Reads the next floor in the queue, closes doors, and goes to it.

	if(ElevatorState_B != ELEVATOR_STATE_IDLE_B || ElevatorQueue_B[0] == INVALID_FLOOR_B)
	    return 0;

	Elevator_CloseDoors_B();
	Floor_CloseDoors_B(ElevatorFloor_B);

	return 1;
}

stock DidPlayerRequestElevator_B(playerid)
{
	for(new i; i < sizeof(FloorRequestedBy_B); i ++)
	    if(FloorRequestedBy_B[i] == playerid)
	        return 1;

	return 0;
}

stock ShowElevatorDialog_B(playerid)
{
	new string[512];
	for(new i; i < sizeof(ElevatorQueue_B); i ++)
	{
	    if(FloorRequestedBy_B[i] != INVALID_PLAYER_ID)
	        strcat(string, "{FF0000}");

	    strcat(string, FloorNames_B[i]);
	    strcat(string, "\n");
	}

	ShowPlayerDialog(playerid, DIALOG_ID_B, DIALOG_STYLE_LIST, "Elevador...", string, "Selecionar", "Cancelar");

	return 1;
}

stock CallElevator_B(playerid, floorid)
{
	// Calls the elevator (also used with the elevator dialog).

	if(FloorRequestedBy_B[floorid] != INVALID_PLAYER_ID || IsFloorInQueue_B(floorid))
	    return 0;

	FloorRequestedBy_B[floorid] = playerid;
	AddFloorToQueue_B(floorid);

	return 1;
}

stock Float:GetElevatorZCoordForFloor_B(floorid)
{
	// Return Z height value
    return (GROUND_Z_COORD_B + FloorZOffsets_B[floorid]);
}

stock Float:GetDoorsZCoordForFloor_B(floorid)
{
    // Return Z height value
	return (GROUND_Z_COORD_B + FloorZOffsets_B[floorid]);
}


// ------------------------ Functions ------------------------
stock Elevator_Initialize()
{
	// Initializes the elevator.

	Obj_Elevator 			= CreateObject(18755, 1786.678100, -1303.459472, GROUND_Z_COORD + ELEVATOR_OFFSET, 0.000000, 0.000000, 270.000000);
	Obj_ElevatorDoors[0] 	= CreateObject(18757, X_DOOR_CLOSED, -1303.459472, GROUND_Z_COORD, 0.000000, 0.000000, 270.000000);
	Obj_ElevatorDoors[1] 	= CreateObject(18756, X_DOOR_CLOSED, -1303.459472, GROUND_Z_COORD, 0.000000, 0.000000, 270.000000);

	Label_Elevator          = Create3DTextLabel("{CCCCCC}Pressione '{FFFFFF}ENTER{CCCCCC}' para usar o elevador", 0xCCCCCCAA, 1784.9822, -1302.0426, 13.6491, 10.0, 0);

	new string[256],
		Float:z;

	for(new i; i < sizeof(Obj_FloorDoors); i ++)
	{
	    Obj_FloorDoors[i][0] 	= CreateDynamicObject(18757, X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(i), 0.000000, 0.000000, 270.000000);
		Obj_FloorDoors[i][1] 	= CreateDynamicObject(18756, X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(i), 0.000000, 0.000000, 270.000000);

		format(string, sizeof(string), "{CCCCCC}[%s]\n{CCCCCC}Pressione '{FFFFFF}ENTER{CCCCCC}' para chamar o elevador", FloorNames[i]);

		if(i == 0)
		    z = 13.4713;
		else
		    z = 13.4713 + 8.7396 + ((i-1) * 5.45155);

		Label_Floors[i]         = Create3DTextLabel(string, 0xCCCCCCAA, 1783.9799, -1300.7660, z, 10.5, 0);
		CreateDynamicPickup(1318,23,1783.9799, -1300.7660, z, -1);
		// Label_Elevator, Text3D:Label_Floors[21];
	}

	// Open ground floor doors:
	Floor_OpenDoors(0);
	Elevator_OpenDoors();

	return 1;
}

stock Elevator_Destroy()
{
	// Destroys the elevator.

	DestroyObject(Obj_Elevator);
	DestroyObject(Obj_ElevatorDoors[0]);
	DestroyObject(Obj_ElevatorDoors[1]);
	Delete3DTextLabel(Label_Elevator);

	for(new i; i < sizeof(Obj_FloorDoors); i ++)
	{
	    DestroyDynamicObject(Obj_FloorDoors[i][0]);
		DestroyDynamicObject(Obj_FloorDoors[i][1]);
		Delete3DTextLabel(Label_Floors[i]);
	}

	return 1;
}

stock Elevator_OpenDoors()
{
	// Opens the elevator's doors.

	new Float:x, Float:y, Float:z;

	GetObjectPos(Obj_ElevatorDoors[0], x, y, z);
	MoveObject(Obj_ElevatorDoors[0], X_DOOR_L_OPENED, y, z, DOORS_SPEED);
	MoveObject(Obj_ElevatorDoors[1], X_DOOR_R_OPENED, y, z, DOORS_SPEED);

	return 1;
}

stock Elevator_CloseDoors()
{
    // Closes the elevator's doors.

    if(ElevatorState == ELEVATOR_STATE_MOVING)
	    return 0;

    new Float:x, Float:y, Float:z;

	GetObjectPos(Obj_ElevatorDoors[0], x, y, z);
	MoveObject(Obj_ElevatorDoors[0], X_DOOR_CLOSED, y, z, DOORS_SPEED);
	MoveObject(Obj_ElevatorDoors[1], X_DOOR_CLOSED, y, z, DOORS_SPEED);

	return 1;
}

stock Floor_OpenDoors(floorid)
{
    // Opens the doors at the specified floor.

    MoveDynamicObject(Obj_FloorDoors[floorid][0], X_DOOR_L_OPENED, -1303.171142, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);
	MoveDynamicObject(Obj_FloorDoors[floorid][1], X_DOOR_R_OPENED, -1303.171142, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);

	PlaySoundForPlayersInRange(6401, 50.0, X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(floorid) + 5.0);

	return 1;
}

stock Floor_CloseDoors(floorid)
{
    // Closes the doors at the specified floor.

    MoveDynamicObject(Obj_FloorDoors[floorid][0], X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);
	MoveDynamicObject(Obj_FloorDoors[floorid][1], X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);

	PlaySoundForPlayersInRange(6401, 50.0, X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(floorid) + 5.0);

	return 1;
}

stock Elevator_MoveToFloor(floorid)
{
	// Moves the elevator to specified floor (doors are meant to be already closed).

	ElevatorState = ELEVATOR_STATE_MOVING;
	ElevatorFloor = floorid;

	// Move the elevator slowly, to give time to clients to sync the object surfing. Then, boost it up:
	MoveObject(Obj_Elevator, 1786.678100, -1303.459472, GetElevatorZCoordForFloor(floorid), 0.25);
    MoveObject(Obj_ElevatorDoors[0], X_DOOR_CLOSED, -1303.459472, GetDoorsZCoordForFloor(floorid), 0.25);
    MoveObject(Obj_ElevatorDoors[1], X_DOOR_CLOSED, -1303.459472, GetDoorsZCoordForFloor(floorid), 0.25);
    Delete3DTextLabel(Label_Elevator);

	ElevatorBoostTimer = SetTimerEx("Elevator_Boost", 2000, false, "i", floorid);

	return 1;
}

CALLBACK:Elevator_Boost(floorid)
{
	// Increases the elevator's speed until it reaches 'floorid'
	StopObject(Obj_Elevator);
	StopObject(Obj_ElevatorDoors[0]);
	StopObject(Obj_ElevatorDoors[1]);

	MoveObject(Obj_Elevator, 1786.678100, -1303.459472, GetElevatorZCoordForFloor(floorid), ELEVATOR_SPEED);
    MoveObject(Obj_ElevatorDoors[0], X_DOOR_CLOSED, -1303.459472, GetDoorsZCoordForFloor(floorid), ELEVATOR_SPEED);
    MoveObject(Obj_ElevatorDoors[1], X_DOOR_CLOSED, -1303.459472, GetDoorsZCoordForFloor(floorid), ELEVATOR_SPEED);

	return 1;
}

CALLBACK:Elevator_TurnToIdle()
{
	ElevatorState = ELEVATOR_STATE_IDLE;
	ReadNextFloorInQueue();

	return 1;
}

stock RemoveFirstQueueFloor()
{
	// Removes the data in ElevatorQueue[0], and reorders the queue accordingly.

	for(new i; i < sizeof(ElevatorQueue) - 1; i ++)
	    ElevatorQueue[i] = ElevatorQueue[i + 1];

	ElevatorQueue[sizeof(ElevatorQueue) - 1] = INVALID_FLOOR;

	return 1;
}

stock AddFloorToQueue(floorid)
{
 	// Adds 'floorid' at the end of the queue.

	// Scan for the first empty space:
	new slot = -1;
	for(new i; i < sizeof(ElevatorQueue); i ++)
	{
	    if(ElevatorQueue[i] == INVALID_FLOOR)
	    {
	        slot = i;
	        break;
	    }
	}

	if(slot != -1)
	{
	    ElevatorQueue[slot] = floorid;

     	// If needed, move the elevator.
	    if(ElevatorState == ELEVATOR_STATE_IDLE)
	        ReadNextFloorInQueue();

	    return 1;
	}

	return 0;
}

stock ResetElevatorQueue()
{
	// Resets the queue.

	for(new i; i < sizeof(ElevatorQueue); i ++)
	{
	    ElevatorQueue[i] 	= INVALID_FLOOR;
	    FloorRequestedBy[i] = INVALID_PLAYER_ID;
	}

	return 1;
}

stock IsFloorInQueue(floorid)
{
	// Checks if the specified floor is currently part of the queue.

	for(new i; i < sizeof(ElevatorQueue); i ++)
	    if(ElevatorQueue[i] == floorid)
	        return 1;

	return 0;
}

stock ReadNextFloorInQueue()
{
	// Reads the next floor in the queue, closes doors, and goes to it.

	if(ElevatorState != ELEVATOR_STATE_IDLE || ElevatorQueue[0] == INVALID_FLOOR)
	    return 0;

	Elevator_CloseDoors();
	Floor_CloseDoors(ElevatorFloor);

	return 1;
}

stock DidPlayerRequestElevator(playerid)
{
	for(new i; i < sizeof(FloorRequestedBy); i ++)
	    if (FloorRequestedBy[i] == playerid)
	        return true;

	return false;
}

stock ShowElevatorDialog(playerid)
{
	MEGAString[0] = EOS;

	for(new i; i < sizeof(ElevatorQueue); i ++)
	{
	    if (FloorRequestedBy[i] != INVALID_PLAYER_ID)
	        strcat(MEGAString, "{FF0000}");

	    strcat(MEGAString, FloorNames[i]);
	    strcat(MEGAString, "\n");
	}
	ShowPlayerDialog(playerid, 4785, DIALOG_STYLE_LIST, "Elevador", MEGAString, "Selecionar", "Cancelar");

	return true;
}

stock CallElevator(playerid, floorid)
{
	// Calls the elevator (also used with the elevator dialog).
	if (FloorRequestedBy[floorid] != INVALID_PLAYER_ID || IsFloorInQueue(floorid))
	    return false;

	FloorRequestedBy[floorid] = playerid;
	AddFloorToQueue(floorid);

	return true;
}

hook OnDynamicObjectMoved(objectid)
{
    new Float:x, Float:y, Float:z;
	for(new i; i < sizeof(Obj_FloorDoors); i ++)
	{
		if(objectid == Obj_FloorDoors[i][0])
		{
		    GetDynamicObjectPos(Obj_FloorDoors[i][0], x, y, z);

		    if(x < X_DOOR_L_OPENED - 0.5)   // Some floor doors have shut, move the elevator to next floor in queue:
		    {
				Elevator_MoveToFloor(ElevatorQueue[0]);
				RemoveFirstQueueFloor();
			}
		}
	}
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (newkeys & KEY_SECONDARY_ATTACK)
	{
		//Elevador
		new Float:pos[3];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

		if(pos[1] < -1301.4 && pos[1] > -1303.2417 && pos[0] < 1786.2131 && pos[0] > 1784.1555)    // He is using the elevator button
			ShowElevatorDialog(playerid);
		else    // Is he in a floor button?
		{
			if(pos[1] > -1301.4 && pos[1] < -1299.1447 && pos[0] < 1785.6147 && pos[0] > 1781.9902)
			{
				// He is most likely using it, check floor:
				new i=20;
				while(pos[2] < GetDoorsZCoordForFloor(i) + 3.5 && i > 0)
					i --;

				if(i == 0 && pos[2] < GetDoorsZCoordForFloor(0) + 2.0)
					i = -1;

				if(i <= 19)
				{
					if (ElevatorState != ELEVATOR_STATE_MOVING)
					{
						// Check if the elevator is already on the floor it was called from
						if (ElevatorFloor == i + 1)
						{
							// Display gametext message to the player
							GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~y~~h~Elevator~n~~y~~h~Ja neste andar...~n~~w~Va dentro dele~n~~w~E aperte 'ENTER'", 3500, 3);

							// Display chat text message to the player
							SendClientMessage(playerid, COLOR_MESSAGE_YELLOW_B, "* O elevator já está neste andar... vá dentro dele e aperte '{FFFFFF}ENTER{CCCCCC}'");

							// Exit here (return 1 so this callback is processed in other scripts)
							return 1;
						}
					}
					CallElevator(playerid, i + 1);
					GameTextForPlayer(playerid, "~r~Elevador chamado~n~~y~Aguarde...", 3500, 4);

					// Create variable for formatted message
					new strTempString[100];

					// Check if the elevator is moving
					if (ElevatorState == ELEVATOR_STATE_MOVING)
					{
						// Format chat text message
						format(strTempString, sizeof(strTempString), "* O elevator foi chamado... atualmente esta se movendo em direcao a %s.", FloorNames[ElevatorFloor]);
					}
					else
					{
						// Check if the floor is the car park
						if (ElevatorFloor == 0)
						{
							// Format chat text message
							format(strTempString, sizeof(strTempString), "* O elevador já foi chamado... ele está atualmente no %s.", FloorNames[ElevatorFloor]);
						}
						else
						{
							// Format chat text message
							format(strTempString, sizeof(strTempString), "* O elevador já foi chamado... ele está atualmente no %s.", FloorNames[ElevatorFloor]);
						}
					}

					// Display formatted chat text message to the player
					SendClientMessage(playerid, COLOR_MESSAGE_YELLOW_B, strTempString);
				}
			}
		}

		// Elevador - BeachSide
		if (pos[1] > (Y_ELEVATOR_POS_B - 1.8) && pos[1] < (Y_ELEVATOR_POS_B + 1.8) && pos[0] < (X_ELEVATOR_POS_B + 1.8) && pos[0] > (X_ELEVATOR_POS_B - 1.8))
		{
			// The player is using the button inside the elevator
			// --------------------------------------------------

			// Show the elevator dialog to the player
			ShowElevatorDialog_B(playerid);
		}
		else
		{
			// Check if the player is using the button on one of the floors
			if(pos[1] < (Y_ELEVATOR_POS_B - 1.81) && pos[1] > (Y_ELEVATOR_POS_B - 3.8) && pos[0] > (X_ELEVATOR_POS_B + 1.21) && pos[0] < (X_ELEVATOR_POS_B + 3.8))
			{
				// The player is most likely using an elevator floor button... check which floor
				// -----------------------------------------------------------------------------

				// Create variable with the number of floors to check (total floors minus 1)
				new i = 13;

				// Loop
				while(pos[2] < GetDoorsZCoordForFloor_B(i) + 3.5 && i > 0)
					i --;

				if(i == 0 && pos[2] < GetDoorsZCoordForFloor_B(0) + 2.0)
					i = -1;

				if (i <= 12)
				{
					// Check if the elevator is not moving (idle or waiting)
					if (ElevatorState_B != ELEVATOR_STATE_MOVING_B)
					{
						// Check if the elevator is already on the floor it was called from
						if (ElevatorFloor_B == i + 1)
						{
							// Display gametext message to the player
							GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~y~~h~Elevator~n~~y~~h~Ja neste andar...~n~~w~Va dentro dele~n~~w~E aperte 'ENTER'", 3500, 3);

							// Display chat text message to the player
							SendClientMessage(playerid, COLOR_MESSAGE_YELLOW_B, "* O elevator já está neste andar... vá dentro dele e aperte '{FFFFFF}ENTER{CCCCCC}'");

							// Exit here (return 1 so this callback is processed in other scripts)
							return 1;
						}
					}

					// Call function to call the elevator to the floor
					CallElevator_B(playerid, i + 1);

					// Display gametext message to the player
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~g~~h~Elevator~n~~g~~h~foi chamado...~n~~w~Aguarde", 3000, 3);

					// Create variable for formatted message
					new strTempString[100];

					// Check if the elevator is moving
					if (ElevatorState_B == ELEVATOR_STATE_MOVING_B)
					{
						// Format chat text message
						format(strTempString, sizeof(strTempString), "* O elevator foi chamado... atualmente esta se movendo em direcao a %s.", FloorNames_B[ElevatorFloor_B]);
					}
					else
					{
						// Check if the floor is the car park
						if (ElevatorFloor_B == 0)
						{
							// Format chat text message
							format(strTempString, sizeof(strTempString), "* O elevador já foi chamado... ele está atualmente no %s.", FloorNames_B[ElevatorFloor_B]);
						}
						else
						{
							// Format chat text message
							format(strTempString, sizeof(strTempString), "* O elevador já foi chamado... ele está atualmente no %s.", FloorNames_B[ElevatorFloor_B]);
						}
					}

					// Display formatted chat text message to the player
					SendClientMessage(playerid, COLOR_MESSAGE_YELLOW_B, strTempString);

					// Exit here (return 1 so this callback is processed in other scripts)
					return 1;
				}
			}
		}
	}
	return 1;
}