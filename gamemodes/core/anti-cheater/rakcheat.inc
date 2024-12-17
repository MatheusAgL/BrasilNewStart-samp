#if defined _rakcheat_included
	#endinput
#endif
#define _rakcheat_included

#include <a_samp>

#if !defined PAWNRAKNET_INC_
	#error You must have Pawn.RakNet include in order to use this one.
#endif

#if !defined RAK_DEBUG
	#define RAK_DEBUG
#endif

#if !defined RAK_MAX_QUAT_WARNINGS
	#define RAK_MAX_QUAT_WARNINGS		1
#endif

#if !defined RAK_MAX_SURF_WARNINGS
	#define RAK_MAX_SURF_WARNINGS		30
#endif

#if !defined RAK_MAX_SURF_DIST_WARNINGS
	#define RAK_MAX_SURF_DIST_WARNINGS	30
#endif

#if __Pawn >= 0x3A && defined __PawnBuild
	#if __Pawn > 0x3A || __PawnBuild >= 2
		#define static_enum static enum
	#endif
#endif
#if !defined static_enum
	#define static_enum enum
#endif

#if __Pawn >= 0x3A && defined __PawnBuild
	#if __Pawn > 0x3A || __PawnBuild >= 2
		#define static_const(%0) static enum { %0 }
	#endif
#endif
#if !defined static_const
	#define static_const(%0) static const %0
#endif

static_enum
{
	RAK_INVALID_POSITION = 1,
	RAK_INVALID_QUATERNION,
	RAK_INVALID_VELOCITY,
	RAK_INVALID_SURFING_OFFSETS,
	RAK_INVALID_SURFING,
	RAK_INVALID_ANIMATION_FLAGS,
	RAK_INVALID_HEALTH,
	RAK_INVALID_TRAIN_SPEED,
	RAK_INVALID_ROLL,
	RAK_INVALID_DIRECTION,
	RAK_INVALID_ANGULAR_VELOCITY,
	RAK_INVALID_ORIGIN,
	RAK_INVALID_HITPOS,
	RAK_INVALID_OFFSETS,
	RAK_INVALID_CAMFRONTVEC,
	RAK_INVALID_CAMPOS,
	RAK_INVALID_AIMZ,
	RAK_INVALID_SHOT
}

static_const(ID_PLAYER_SYNC = 207);
static_const(ID_VEHICLE_SYNC = 200);
static_const(ID_PASSENGER_SYNC = 211);
static_const(ID_UNOCCUPIED_SYNC = 209);
static_const(ID_TRAILER_SYNC = 210);
static_const(ID_SPECTATOR_SYNC = 212);
static_const(ID_BULLET_SYNC = 206);
static_const(ID_AIM_SYNC = 203);

#if defined OnRakcheatFilteredData
	forward OnRakcheatFilteredData(playerid, sync, type, subtype);
#endif

static_enum rakInfo
{
	rakQuatCount,
	rakSurfingCount,
	rakSurfingDistCount
}
static RAKInfo[MAX_PLAYERS][rakInfo];

#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

static CheckValidityData(Float:data)
{
	if(floatcmp(data, data) != 0 || floatcmp(data, Float:0x7F800000) == 0 || floatcmp(data, Float:0xFF800000) == 0) return 1;
	return 0;
}

static CheckOutputLimit(Float:data, Float:max, Float:min = 0.0, bool:check = false)
{
	if(floatcmp(floatabs(data), max) > 0 || check && floatcmp(data, min) < 0) return 1;
	return 0;
}

static KickWithCode(playerid, sync, type, subtype)
{
	if(!IsPlayerConnected(playerid)) return 0;
	#if defined RAK_DEBUG
		printf("[Rakcheat] Suspicious player ID %d. Reason code: %03d (%d)", playerid, type, subtype);
	#endif
	#if defined OnRakcheatFilteredData
		return OnRakcheatFilteredData(playerid, sync, type, subtype);
	#else
		#pragma unused sync
		Kick(playerid);
		return 0;
	#endif
}

public OnPlayerConnect(playerid)
{
	RAKInfo[playerid][rakQuatCount] =
	RAKInfo[playerid][rakSurfingCount] =
	RAKInfo[playerid][rakSurfingDistCount] = 0;

	#if defined rak_OnPlayerConnect
		return rak_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect rak_OnPlayerConnect
#if defined rak_OnPlayerConnect
	forward rak_OnPlayerConnect(playerid);
#endif

IPacket:ID_PLAYER_SYNC(playerid, BitStream:bs)
{
	new onFootData[PR_OnFootSync];

	BS_IgnoreBits(bs, 8);
	BS_ReadOnFootSync(bs, onFootData);

	if(CheckValidityData(onFootData[PR_position][0]) || CheckValidityData(onFootData[PR_position][1]) || CheckValidityData(onFootData[PR_position][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_PLAYER_SYNC] Position x, y, z: %f, %f, %f",
			onFootData[PR_position][0], onFootData[PR_position][1], onFootData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_POSITION, 0);
	}

	if(CheckOutputLimit(onFootData[PR_position][0], 20000.0) || CheckOutputLimit(onFootData[PR_position][1], 20000.0) ||
	CheckOutputLimit(onFootData[PR_position][2], 20000.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_PLAYER_SYNC] Position x, y, z: %f, %f, %f",
			onFootData[PR_position][0], onFootData[PR_position][1], onFootData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_POSITION, 1);
	}

	if(CheckValidityData(onFootData[PR_quaternion][0]) || CheckValidityData(onFootData[PR_quaternion][1]) || CheckValidityData(onFootData[PR_quaternion][2]) ||
	CheckValidityData(onFootData[PR_quaternion][3]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_PLAYER_SYNC] Quaternion w, x, y, z: %f, %f, %f, %f",
			onFootData[PR_quaternion][0], onFootData[PR_quaternion][1], onFootData[PR_quaternion][2], onFootData[PR_quaternion][3]);
		#endif
		return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_QUATERNION, 0);
	}

	new Float:rak_ang = atan2(floatmul(2.0, floatadd(floatmul(onFootData[PR_quaternion][2], onFootData[PR_quaternion][3]),
	floatmul(onFootData[PR_quaternion][0], onFootData[PR_quaternion][1]))), floatadd(floatsub(floatsub(floatpower(onFootData[PR_quaternion][0], 2.0),
	floatpower(onFootData[PR_quaternion][1], 2.0)), floatpower(onFootData[PR_quaternion][2], 2.0)),
	floatpower(onFootData[PR_quaternion][3], 2.0)));
	if(floatabs(rak_ang) > 85.0 && onFootData[PR_specialAction] == SPECIAL_ACTION_NONE)
	{
		if(++RAKInfo[playerid][rakQuatCount] > RAK_MAX_QUAT_WARNINGS)
		{
			#if defined RAK_DEBUG
				printf("[Rakcheat debug] [ID_PLAYER_SYNC] Quaternion w, x, y, z: %f, %f, %f, %f, angle: %f",
				onFootData[PR_quaternion][0], onFootData[PR_quaternion][1], onFootData[PR_quaternion][2], onFootData[PR_quaternion][3], rak_ang);
			#endif
			return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_QUATERNION, 2);
		}
	}
	else RAKInfo[playerid][rakQuatCount] = 0;

	if(CheckValidityData(onFootData[PR_velocity][0]) || CheckValidityData(onFootData[PR_velocity][1]) || CheckValidityData(onFootData[PR_velocity][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_PLAYER_SYNC] Velocity x, y, z: %f, %f, %f",
			onFootData[PR_velocity][0], onFootData[PR_velocity][1], onFootData[PR_velocity][2]);
		#endif
		return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_VELOCITY, 0);
	}

	if(CheckOutputLimit(onFootData[PR_velocity][0], 100.0) || CheckOutputLimit(onFootData[PR_velocity][1], 100.0) || CheckOutputLimit(onFootData[PR_velocity][2], 100.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_PLAYER_SYNC] Velocity x, y, z: %f, %f, %f",
			onFootData[PR_velocity][0], onFootData[PR_velocity][1], onFootData[PR_velocity][2]);
		#endif
		return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_VELOCITY, 1);
	}

	if(CheckValidityData(onFootData[PR_surfingOffsets][0]) || CheckValidityData(onFootData[PR_surfingOffsets][1]) || CheckValidityData(onFootData[PR_surfingOffsets][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_PLAYER_SYNC] Surfing offsets x, y, z: %f, %f, %f",
			onFootData[PR_surfingOffsets][0], onFootData[PR_surfingOffsets][1], onFootData[PR_surfingOffsets][2]);
		#endif
		return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_SURFING_OFFSETS, 0);
	}

	if(CheckOutputLimit(onFootData[PR_surfingOffsets][0], 50.0) || CheckOutputLimit(onFootData[PR_surfingOffsets][1], 50.0) ||
	CheckOutputLimit(onFootData[PR_surfingOffsets][2], 50.0))
	{
		if(++RAKInfo[playerid][rakSurfingCount] > RAK_MAX_SURF_WARNINGS)
		{
			#if defined RAK_DEBUG
				printf("[Rakcheat debug] [ID_PLAYER_SYNC] Surfing offsets x, y, z: %f, %f, %f",
				onFootData[PR_surfingOffsets][0], onFootData[PR_surfingOffsets][1], onFootData[PR_surfingOffsets][2]);
			#endif
			return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_SURFING_OFFSETS, 1);
		}
	}
	else RAKInfo[playerid][rakSurfingCount] = 0;

	if(onFootData[PR_surfingVehicleId] != 0)
	{
		if(0 < onFootData[PR_surfingVehicleId] < MAX_VEHICLES)
		{
			new rak_model = GetVehicleModel(onFootData[PR_surfingVehicleId]);
			if(rak_model == 0)
			{
				#if defined RAK_DEBUG
					printf("[Rakcheat debug] [ID_PLAYER_SYNC] Veh model: %d, vehicleid: %d",
					rak_model, onFootData[PR_surfingVehicleId]);
				#endif
				return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_SURFING, 0);
			}
			else
			{
				new Float:rak_vX, Float:rak_vY, Float:rak_vZ;
				GetVehiclePos(onFootData[PR_surfingVehicleId], rak_vX, rak_vY, rak_vZ);
				rak_ang = VectorSize(floatsub(onFootData[PR_position][0], rak_vX), floatsub(onFootData[PR_position][1], rak_vY),
				floatsub(onFootData[PR_position][2], rak_vZ));
				if(floatcmp(rak_ang, 50.0) >= 0)
				{
					if(++RAKInfo[playerid][rakSurfingDistCount] > RAK_MAX_SURF_DIST_WARNINGS)
					{
						#if defined RAK_DEBUG
							printf("[Rakcheat debug] [ID_PLAYER_SYNC] Veh x, y, z: %f, %f, %f, player x, y, z: %f, %f, %f, distance: %f",
							rak_vX, rak_vY, rak_vZ, onFootData[PR_position][0], onFootData[PR_position][1], onFootData[PR_position][2], rak_ang);
						#endif
						return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_SURFING, 1);
					}
				}
				else RAKInfo[playerid][rakSurfingDistCount] = 0;
			}
		}
		else if(MAX_VEHICLES < onFootData[PR_surfingVehicleId] < MAX_VEHICLES + MAX_OBJECTS)
		{
			onFootData[PR_surfingVehicleId] -= MAX_VEHICLES;
			new rak_tmp = IsValidObject(onFootData[PR_surfingVehicleId]);
			if(!rak_tmp && !IsValidPlayerObject(playerid, onFootData[PR_surfingVehicleId]))
			{
				#if defined RAK_DEBUG
					printf("[Rakcheat debug] [ID_PLAYER_SYNC] Objectid: %d", onFootData[PR_surfingVehicleId]);
				#endif
				return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_SURFING, 2);
			}
			else
			{
				new Float:rak_vX, Float:rak_vY, Float:rak_vZ;
				if(rak_tmp) GetObjectPos(onFootData[PR_surfingVehicleId], rak_vX, rak_vY, rak_vZ);
				else GetPlayerObjectPos(playerid, onFootData[PR_surfingVehicleId], rak_vX, rak_vY, rak_vZ);
				rak_ang = VectorSize(floatsub(onFootData[PR_position][0], rak_vX), floatsub(onFootData[PR_position][1], rak_vY),
				floatsub(onFootData[PR_position][2], rak_vZ));
				if(floatcmp(rak_ang, 50.0) >= 0)
				{
					if(++RAKInfo[playerid][rakSurfingDistCount] > RAK_MAX_SURF_DIST_WARNINGS)
					{
						#if defined RAK_DEBUG
							printf("[Rakcheat debug] [ID_PLAYER_SYNC] Object x, y, z: %f, %f, %f, player x, y, z: %f, %f, %f, distance: %f",
							rak_vX, rak_vY, rak_vZ, onFootData[PR_position][0], onFootData[PR_position][1], onFootData[PR_position][2], rak_ang);
						#endif
						return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_SURFING, 3);
					}
				}
				else RAKInfo[playerid][rakSurfingDistCount] = 0;
			}
		}
		else if(onFootData[PR_surfingVehicleId] != INVALID_VEHICLE_ID)
		{
			#if defined RAK_DEBUG
				printf("[Rakcheat debug] [ID_PLAYER_SYNC] Surfing: %d", onFootData[PR_surfingVehicleId]);
			#endif
			return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_SURFING, 4);
		}
	}

	if(onFootData[PR_animationFlags] == 0)
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_PLAYER_SYNC] Animation flags: %d", onFootData[PR_animationFlags]);
		#endif
		return KickWithCode(playerid, ID_PLAYER_SYNC, RAK_INVALID_ANIMATION_FLAGS, 0);
	}
	return 1;
}

IPacket:ID_VEHICLE_SYNC(playerid, BitStream:bs)
{
	new inCarData[PR_InCarSync];

	BS_IgnoreBits(bs, 8);
	BS_ReadInCarSync(bs, inCarData);

	if(CheckValidityData(inCarData[PR_quaternion][0]) || CheckValidityData(inCarData[PR_quaternion][1]) || CheckValidityData(inCarData[PR_quaternion][2]) ||
	CheckValidityData(inCarData[PR_quaternion][3]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Quaternion w, x, y, z: %f, %f, %f, %f",
			inCarData[PR_quaternion][0], inCarData[PR_quaternion][1], inCarData[PR_quaternion][2], inCarData[PR_quaternion][3]);
		#endif
		return KickWithCode(playerid, ID_VEHICLE_SYNC, RAK_INVALID_QUATERNION, 0);
	}

	if(CheckValidityData(inCarData[PR_position][0]) || CheckValidityData(inCarData[PR_position][1]) || CheckValidityData(inCarData[PR_position][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Position x, y, z: %f, %f, %f",
			inCarData[PR_position][0], inCarData[PR_position][1], inCarData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_VEHICLE_SYNC, RAK_INVALID_POSITION, 0);
	}

	if(CheckOutputLimit(inCarData[PR_position][0], 20000.0) || CheckOutputLimit(inCarData[PR_position][1], 20000.0) ||
	CheckOutputLimit(inCarData[PR_position][2], 20000.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Position x, y, z: %f, %f, %f",
			inCarData[PR_position][0], inCarData[PR_position][1], inCarData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_VEHICLE_SYNC, RAK_INVALID_POSITION, 1);
	}

	if(CheckValidityData(inCarData[PR_velocity][0]) || CheckValidityData(inCarData[PR_velocity][1]) || CheckValidityData(inCarData[PR_velocity][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Velocity x, y, z: %f, %f, %f",
			inCarData[PR_velocity][0], inCarData[PR_velocity][1], inCarData[PR_velocity][2]);
		#endif
		return KickWithCode(playerid, ID_VEHICLE_SYNC, RAK_INVALID_VELOCITY, 0);
	}

	if(CheckOutputLimit(inCarData[PR_velocity][0], 100.0) || CheckOutputLimit(inCarData[PR_velocity][1], 100.0) || CheckOutputLimit(inCarData[PR_velocity][2], 100.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Velocity x, y, z: %f, %f, %f",
			inCarData[PR_velocity][0], inCarData[PR_velocity][1], inCarData[PR_velocity][2]);
		#endif
		return KickWithCode(playerid, ID_VEHICLE_SYNC, RAK_INVALID_VELOCITY, 1);
	}

	if(CheckValidityData(inCarData[PR_vehicleHealth]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Veh health: %f", inCarData[PR_vehicleHealth]);
		#endif
		return KickWithCode(playerid, ID_VEHICLE_SYNC, RAK_INVALID_HEALTH, 0);
	}

	if(CheckValidityData(inCarData[PR_trainSpeed]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_VEHICLE_SYNC] Train speed: %f", inCarData[PR_trainSpeed]);
		#endif
		return KickWithCode(playerid, ID_VEHICLE_SYNC, RAK_INVALID_TRAIN_SPEED, 0);
	}
	return 1;
}

IPacket:ID_PASSENGER_SYNC(playerid, BitStream:bs)
{
	new passengerData[PR_PassengerSync];

	BS_IgnoreBits(bs, 8);
	BS_ReadPassengerSync(bs, passengerData);

	if(CheckValidityData(passengerData[PR_position][0]) || CheckValidityData(passengerData[PR_position][1]) || CheckValidityData(passengerData[PR_position][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_PASSENGER_SYNC] Position x, y, z: %f, %f, %f",
			passengerData[PR_position][0], passengerData[PR_position][1], passengerData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_PASSENGER_SYNC, RAK_INVALID_POSITION, 0);
	}

	if(CheckOutputLimit(passengerData[PR_position][0], 20000.0) || CheckOutputLimit(passengerData[PR_position][1], 20000.0) ||
	CheckOutputLimit(passengerData[PR_position][2], 20000.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_PASSENGER_SYNC] Position x, y, z: %f, %f, %f",
			passengerData[PR_position][0], passengerData[PR_position][1], passengerData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_PASSENGER_SYNC, RAK_INVALID_POSITION, 1);
	}
	return 1;
}

IPacket:ID_UNOCCUPIED_SYNC(playerid, BitStream:bs)
{
	new unoccupiedData[PR_UnoccupiedSync];

	BS_IgnoreBits(bs, 8);
	BS_ReadUnoccupiedSync(bs, unoccupiedData);

	if(CheckValidityData(unoccupiedData[PR_roll][0]) || CheckValidityData(unoccupiedData[PR_roll][1]) || CheckValidityData(unoccupiedData[PR_roll][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Roll x, y, z: %f, %f, %f",
			unoccupiedData[PR_roll][0], unoccupiedData[PR_roll][1], unoccupiedData[PR_roll][2]);
		#endif
		return KickWithCode(playerid, ID_UNOCCUPIED_SYNC, RAK_INVALID_ROLL, 0);
	}

	if(CheckOutputLimit(unoccupiedData[PR_roll][0], 1.0) || CheckOutputLimit(unoccupiedData[PR_roll][1], 1.0) || CheckOutputLimit(unoccupiedData[PR_roll][2], 1.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Roll x, y, z: %f, %f, %f",
			unoccupiedData[PR_roll][0], unoccupiedData[PR_roll][1], unoccupiedData[PR_roll][2]);
		#endif
		return KickWithCode(playerid, ID_UNOCCUPIED_SYNC, RAK_INVALID_ROLL, 1);
	}

	if(CheckValidityData(unoccupiedData[PR_direction][0]) || CheckValidityData(unoccupiedData[PR_direction][1]) || CheckValidityData(unoccupiedData[PR_direction][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Direction x, y, z: %f, %f, %f",
			unoccupiedData[PR_direction][0], unoccupiedData[PR_direction][1], unoccupiedData[PR_direction][2]);
		#endif
		return KickWithCode(playerid, ID_UNOCCUPIED_SYNC, RAK_INVALID_DIRECTION, 0);
	}

	if(CheckOutputLimit(unoccupiedData[PR_direction][0], 1.0) || CheckOutputLimit(unoccupiedData[PR_direction][1], 1.0) ||
	CheckOutputLimit(unoccupiedData[PR_direction][2], 1.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Direction x, y, z: %f, %f, %f",
			unoccupiedData[PR_direction][0], unoccupiedData[PR_direction][1], unoccupiedData[PR_direction][2]);
		#endif
		return KickWithCode(playerid, ID_UNOCCUPIED_SYNC, RAK_INVALID_DIRECTION, 1);
	}

	if(CheckValidityData(unoccupiedData[PR_position][0]) || CheckValidityData(unoccupiedData[PR_position][1]) || CheckValidityData(unoccupiedData[PR_position][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Position x, y, z: %f, %f, %f",
			unoccupiedData[PR_position][0], unoccupiedData[PR_position][1], unoccupiedData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_UNOCCUPIED_SYNC, RAK_INVALID_POSITION, 0);
	}

	if(CheckOutputLimit(unoccupiedData[PR_position][0], 20000.0) || CheckOutputLimit(unoccupiedData[PR_position][1], 20000.0) ||
	CheckOutputLimit(unoccupiedData[PR_position][2], 20000.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Position x, y, z: %f, %f, %f",
			unoccupiedData[PR_position][0], unoccupiedData[PR_position][1], unoccupiedData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_UNOCCUPIED_SYNC, RAK_INVALID_POSITION, 1);
	}

	if(CheckValidityData(unoccupiedData[PR_velocity][0]) || CheckValidityData(unoccupiedData[PR_velocity][1]) || CheckValidityData(unoccupiedData[PR_velocity][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Velocity x, y, z: %f, %f, %f",
			unoccupiedData[PR_velocity][0], unoccupiedData[PR_velocity][1], unoccupiedData[PR_velocity][2]);
		#endif
		return KickWithCode(playerid, ID_UNOCCUPIED_SYNC, RAK_INVALID_VELOCITY, 0);
	}

	if(CheckOutputLimit(unoccupiedData[PR_velocity][0], 100.0) || CheckOutputLimit(unoccupiedData[PR_velocity][1], 100.0) ||
	CheckOutputLimit(unoccupiedData[PR_velocity][2], 100.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Velocity x, y, z: %f, %f, %f",
			unoccupiedData[PR_velocity][0], unoccupiedData[PR_velocity][1], unoccupiedData[PR_velocity][2]);
		#endif
		return KickWithCode(playerid, ID_UNOCCUPIED_SYNC, RAK_INVALID_VELOCITY, 1);
	}

	if(CheckValidityData(unoccupiedData[PR_angularVelocity][0]) || CheckValidityData(unoccupiedData[PR_angularVelocity][1]) ||
	CheckValidityData(unoccupiedData[PR_angularVelocity][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Angular velocity x, y, z: %f, %f, %f",
			unoccupiedData[PR_angularVelocity][0], unoccupiedData[PR_angularVelocity][1], unoccupiedData[PR_angularVelocity][2]);
		#endif
		return KickWithCode(playerid, ID_UNOCCUPIED_SYNC, RAK_INVALID_ANGULAR_VELOCITY, 0);
	}

	if(CheckOutputLimit(unoccupiedData[PR_angularVelocity][0], 1.0) || CheckOutputLimit(unoccupiedData[PR_angularVelocity][1], 1.0) ||
	CheckOutputLimit(unoccupiedData[PR_angularVelocity][2], 1.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Angular velocity x, y, z: %f, %f, %f",
			unoccupiedData[PR_angularVelocity][0], unoccupiedData[PR_angularVelocity][1], unoccupiedData[PR_angularVelocity][2]);
		#endif
		return KickWithCode(playerid, ID_UNOCCUPIED_SYNC, RAK_INVALID_ANGULAR_VELOCITY, 1);
	}

	if(CheckValidityData(unoccupiedData[PR_vehicleHealth]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_UNOCCUPIED_SYNC] Veh health: %f", unoccupiedData[PR_vehicleHealth]);
		#endif
		return KickWithCode(playerid, ID_UNOCCUPIED_SYNC, RAK_INVALID_HEALTH, 0);
	}
	return 1;
}

IPacket:ID_TRAILER_SYNC(playerid, BitStream:bs)
{
	new trailerData[PR_TrailerSync];

	BS_IgnoreBits(bs, 8);
	BS_ReadTrailerSync(bs, trailerData);

	if(CheckValidityData(trailerData[PR_position][0]) || CheckValidityData(trailerData[PR_position][1]) || CheckValidityData(trailerData[PR_position][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_TRAILER_SYNC] Position x, y, z: %f, %f, %f",
			trailerData[PR_position][0], trailerData[PR_position][1], trailerData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_TRAILER_SYNC, RAK_INVALID_POSITION, 0);
	}

	if(CheckOutputLimit(trailerData[PR_position][0], 20000.0) || CheckOutputLimit(trailerData[PR_position][1], 20000.0) ||
	CheckOutputLimit(trailerData[PR_position][2], 20000.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_TRAILER_SYNC] Position x, y, z: %f, %f, %f",
			trailerData[PR_position][0], trailerData[PR_position][1], trailerData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_TRAILER_SYNC, RAK_INVALID_POSITION, 1);
	}

	if(CheckValidityData(trailerData[PR_quaternion][0]) || CheckValidityData(trailerData[PR_quaternion][1]) || CheckValidityData(trailerData[PR_quaternion][2]) ||
	CheckValidityData(trailerData[PR_quaternion][3]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_TRAILER_SYNC] Quaternion w, x, y, z: %f, %f, %f, %f",
			trailerData[PR_quaternion][0], trailerData[PR_quaternion][1], trailerData[PR_quaternion][2], trailerData[PR_quaternion][3]);
		#endif
		return KickWithCode(playerid, ID_TRAILER_SYNC, RAK_INVALID_QUATERNION, 0);
	}

	if(CheckValidityData(trailerData[PR_velocity][0]) || CheckValidityData(trailerData[PR_velocity][1]) || CheckValidityData(trailerData[PR_velocity][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_TRAILER_SYNC] Velocity x, y, z: %f, %f, %f",
			trailerData[PR_velocity][0], trailerData[PR_velocity][1], trailerData[PR_velocity][2]);
		#endif
		return KickWithCode(playerid, ID_TRAILER_SYNC, RAK_INVALID_VELOCITY, 0);
	}

	if(CheckOutputLimit(trailerData[PR_velocity][0], 100.0) || CheckOutputLimit(trailerData[PR_velocity][1], 100.0) ||
	CheckOutputLimit(trailerData[PR_velocity][2], 100.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_TRAILER_SYNC] Velocity x, y, z: %f, %f, %f",
			trailerData[PR_velocity][0], trailerData[PR_velocity][1], trailerData[PR_velocity][2]);
		#endif
		return KickWithCode(playerid, ID_TRAILER_SYNC, RAK_INVALID_VELOCITY, 1);
	}

	if(CheckValidityData(trailerData[PR_angularVelocity][0]) || CheckValidityData(trailerData[PR_angularVelocity][1]) ||
	CheckValidityData(trailerData[PR_angularVelocity][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_TRAILER_SYNC] Angular velocity x, y, z: %f, %f, %f",
			trailerData[PR_angularVelocity][0], trailerData[PR_angularVelocity][1], trailerData[PR_angularVelocity][2]);
		#endif
		return KickWithCode(playerid, ID_TRAILER_SYNC, RAK_INVALID_ANGULAR_VELOCITY, 0);
	}

	if(CheckOutputLimit(trailerData[PR_angularVelocity][0], 1.0) || CheckOutputLimit(trailerData[PR_angularVelocity][1], 1.0) ||
	CheckOutputLimit(trailerData[PR_angularVelocity][2], 1.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_TRAILER_SYNC] Angular velocity x, y, z: %f, %f, %f",
			trailerData[PR_angularVelocity][0], trailerData[PR_angularVelocity][1], trailerData[PR_angularVelocity][2]);
		#endif
		return KickWithCode(playerid, ID_TRAILER_SYNC, RAK_INVALID_ANGULAR_VELOCITY, 1);
	}
	return 1;
}

IPacket:ID_SPECTATOR_SYNC(playerid, BitStream:bs)
{
	new spectatorData[PR_SpectatingSync];

	BS_IgnoreBits(bs, 8);
	BS_ReadSpectatingSync(bs, spectatorData);

	if(CheckValidityData(spectatorData[PR_position][0]) || CheckValidityData(spectatorData[PR_position][1]) || CheckValidityData(spectatorData[PR_position][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_SPECTATOR_SYNC] Position x, y, z: %f, %f, %f",
			spectatorData[PR_position][0], spectatorData[PR_position][1], spectatorData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_SPECTATOR_SYNC, RAK_INVALID_POSITION, 0);
	}

	if(CheckOutputLimit(spectatorData[PR_position][0], 20000.0) || CheckOutputLimit(spectatorData[PR_position][1], 20000.0) ||
	CheckOutputLimit(spectatorData[PR_position][2], 20000.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_SPECTATOR_SYNC] Position x, y, z: %f, %f, %f",
			spectatorData[PR_position][0], spectatorData[PR_position][1], spectatorData[PR_position][2]);
		#endif
		return KickWithCode(playerid, ID_SPECTATOR_SYNC, RAK_INVALID_POSITION, 1);
	}
	return 1;
}

IPacket:ID_BULLET_SYNC(playerid, BitStream:bs)
{
	new bulletData[PR_BulletSync];

	BS_IgnoreBits(bs, 8);
	BS_ReadBulletSync(bs, bulletData);

	if(CheckValidityData(bulletData[PR_origin][0]) || CheckValidityData(bulletData[PR_origin][1]) || CheckValidityData(bulletData[PR_origin][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_BULLET_SYNC] Origin x, y, z: %f, %f, %f",
			bulletData[PR_origin][0], bulletData[PR_origin][1], bulletData[PR_origin][2]);
		#endif
		return KickWithCode(playerid, ID_BULLET_SYNC, RAK_INVALID_ORIGIN, 0);
	}

	if(CheckOutputLimit(bulletData[PR_origin][0], 20000.0) || CheckOutputLimit(bulletData[PR_origin][1], 20000.0) || CheckOutputLimit(bulletData[PR_origin][2], 20000.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_BULLET_SYNC] Origin x, y, z: %f, %f, %f",
			bulletData[PR_origin][0], bulletData[PR_origin][1], bulletData[PR_origin][2]);
		#endif
		return KickWithCode(playerid, ID_BULLET_SYNC, RAK_INVALID_ORIGIN, 1);
	}

	if(CheckValidityData(bulletData[PR_hitPos][0]) || CheckValidityData(bulletData[PR_hitPos][1]) || CheckValidityData(bulletData[PR_hitPos][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_BULLET_SYNC] Hitpos x, y, z: %f, %f, %f",
			bulletData[PR_hitPos][0], bulletData[PR_hitPos][1], bulletData[PR_hitPos][2]);
		#endif
		return KickWithCode(playerid, ID_BULLET_SYNC, RAK_INVALID_HITPOS, 0);
	}

	if(CheckOutputLimit(bulletData[PR_hitPos][0], 20000.0) || CheckOutputLimit(bulletData[PR_hitPos][1], 20000.0) || CheckOutputLimit(bulletData[PR_hitPos][2], 20000.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_BULLET_SYNC] Hitpos x, y, z: %f, %f, %f",
			bulletData[PR_hitPos][0], bulletData[PR_hitPos][1], bulletData[PR_hitPos][2]);
		#endif
		return KickWithCode(playerid, ID_BULLET_SYNC, RAK_INVALID_HITPOS, 1);
	}

	if(CheckValidityData(bulletData[PR_offsets][0]) || CheckValidityData(bulletData[PR_offsets][1]) || CheckValidityData(bulletData[PR_offsets][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_BULLET_SYNC] Offsets x, y, z: %f, %f, %f",
			bulletData[PR_offsets][0], bulletData[PR_offsets][1], bulletData[PR_offsets][2]);
		#endif
		return KickWithCode(playerid, ID_BULLET_SYNC, RAK_INVALID_OFFSETS, 0);
	}

	#if defined RAK_ENABLED_SHOT
		if(bulletData[PR_hitType] != BULLET_HIT_TYPE_NONE)
		{
			new Float:rak_X, Float:rak_Y, Float:rak_Z;
			GetPlayerPos(playerid, rak_X, rak_Y, rak_Z);
			if(floatcmp(bulletData[PR_origin][0], rak_X) == 0 || floatcmp(bulletData[PR_origin][1], rak_Y) == 0 || floatcmp(bulletData[PR_origin][2], rak_Z) == 0)
			{
				#if defined RAK_DEBUG
					printf("[Rakcheat debug] [ID_BULLET_SYNC] Pos x, y, z: %f, %f, %f, sync x, y, z: %f, %f, %f",
					rak_X, rak_Y, rak_Z, bulletData[PR_origin][0], bulletData[PR_origin][1], bulletData[PR_origin][2]);
				#endif
				return KickWithCode(playerid, ID_BULLET_SYNC, RAK_INVALID_SHOT, 0);
			}
		}
	#endif

	switch(bulletData[PR_hitType])
	{
		case BULLET_HIT_TYPE_PLAYER:
		{
			if(CheckOutputLimit(bulletData[PR_offsets][0], 2.0) || CheckOutputLimit(bulletData[PR_offsets][1], 2.0) || CheckOutputLimit(bulletData[PR_offsets][2], 2.0))
			{
				#if defined RAK_DEBUG
					printf("[Rakcheat debug] [ID_BULLET_SYNC] Offsets x, y, z: %f, %f, %f",
					bulletData[PR_offsets][0], bulletData[PR_offsets][1], bulletData[PR_offsets][2]);
				#endif
				return KickWithCode(playerid, ID_BULLET_SYNC, RAK_INVALID_OFFSETS, 1);
			}

			#if defined RAK_ENABLED_SHOT
				if(bulletData[PR_hitId] != INVALID_PLAYER_ID)
				{
					new Float:rak_vX, Float:rak_vY, Float:rak_vZ;
					GetPlayerPos(bulletData[PR_hitId], rak_vX, rak_vY, rak_vZ);
					if(floatcmp(bulletData[PR_hitPos][0], rak_vX) == 0 || floatcmp(bulletData[PR_hitPos][1], rak_vY) == 0 ||
					floatcmp(bulletData[PR_hitPos][2], rak_vZ) == 0)
					{
						#if defined RAK_DEBUG
							printf("[Rakcheat debug] [ID_BULLET_SYNC] Pos x, y, z: %f, %f, %f, sync x, y, z: %f, %f, %f",
							rak_vX, rak_vY, rak_vZ, bulletData[PR_hitPos][0], bulletData[PR_hitPos][1], bulletData[PR_hitPos][2]);
						#endif
						return KickWithCode(playerid, ID_BULLET_SYNC, RAK_INVALID_SHOT, 1);
					}
				}
			#endif
		}
		case BULLET_HIT_TYPE_VEHICLE:
		{
			if(CheckOutputLimit(bulletData[PR_offsets][0], 300.0) || CheckOutputLimit(bulletData[PR_offsets][1], 300.0) ||
			CheckOutputLimit(bulletData[PR_offsets][2], 300.0))
			{
				#if defined RAK_DEBUG
					printf("[Rakcheat debug] [ID_BULLET_SYNC] Offsets x, y, z: %f, %f, %f",
					bulletData[PR_offsets][0], bulletData[PR_offsets][1], bulletData[PR_offsets][2]);
				#endif
				return KickWithCode(playerid, ID_BULLET_SYNC, RAK_INVALID_OFFSETS, 2);
			}

			#if defined RAK_ENABLED_SHOT
				if(bulletData[PR_hitId] != INVALID_VEHICLE_ID)
				{
					new Float:rak_vX, Float:rak_vY, Float:rak_vZ;
					GetVehiclePos(bulletData[PR_hitId], rak_vX, rak_vY, rak_vZ);
					if(floatcmp(bulletData[PR_hitPos][0], rak_vX) == 0 || floatcmp(bulletData[PR_hitPos][1], rak_vY) == 0 ||
					floatcmp(bulletData[PR_hitPos][2], rak_vZ) == 0)
					{
						#if defined RAK_DEBUG
							printf("[Rakcheat debug] [ID_BULLET_SYNC] Pos x, y, z: %f, %f, %f, sync x, y, z: %f, %f, %f",
							rak_vX, rak_vY, rak_vZ, bulletData[PR_hitPos][0], bulletData[PR_hitPos][1], bulletData[PR_hitPos][2]);
						#endif
						return KickWithCode(playerid, ID_BULLET_SYNC, RAK_INVALID_SHOT, 2);
					}
				}
			#endif
		}
		default:
		{
			if(CheckOutputLimit(bulletData[PR_offsets][0], 20000.0) || CheckOutputLimit(bulletData[PR_offsets][1], 20000.0) ||
			CheckOutputLimit(bulletData[PR_offsets][2], 20000.0))
			{
				#if defined RAK_DEBUG
					printf("[Rakcheat debug] [ID_BULLET_SYNC] Offsets x, y, z: %f, %f, %f",
					bulletData[PR_offsets][0], bulletData[PR_offsets][1], bulletData[PR_offsets][2]);
				#endif
				return KickWithCode(playerid, ID_BULLET_SYNC, RAK_INVALID_OFFSETS, 3);
			}
		}
	}
	return 1;
}

IPacket:ID_AIM_SYNC(playerid, BitStream:bs)
{
	new aimData[PR_AimSync];

	BS_IgnoreBits(bs, 8);
	BS_ReadAimSync(bs, aimData);

	if(CheckValidityData(aimData[PR_camFrontVec][0]) || CheckValidityData(aimData[PR_camFrontVec][1]) || CheckValidityData(aimData[PR_camFrontVec][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_AIM_SYNC] Camfrontvec x, y, z: %f, %f, %f",
			aimData[PR_camFrontVec][0], aimData[PR_camFrontVec][1], aimData[PR_camFrontVec][2]);
		#endif
		return KickWithCode(playerid, ID_AIM_SYNC, RAK_INVALID_CAMFRONTVEC, 0);
	}

	if(CheckOutputLimit(aimData[PR_camFrontVec][0], 1.0) || CheckOutputLimit(aimData[PR_camFrontVec][1], 1.0) || CheckOutputLimit(aimData[PR_camFrontVec][2], 1.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_AIM_SYNC] Camfrontvec x, y, z: %f, %f, %f",
			aimData[PR_camFrontVec][0], aimData[PR_camFrontVec][1], aimData[PR_camFrontVec][2]);
		#endif
		return KickWithCode(playerid, ID_AIM_SYNC, RAK_INVALID_CAMFRONTVEC, 1);
	}

	if(CheckValidityData(aimData[PR_camPos][0]) || CheckValidityData(aimData[PR_camPos][1]) || CheckValidityData(aimData[PR_camPos][2]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_AIM_SYNC] Campos x, y, z: %f, %f, %f",
			aimData[PR_camPos][0], aimData[PR_camPos][1], aimData[PR_camPos][2]);
		#endif
		return KickWithCode(playerid, ID_AIM_SYNC, RAK_INVALID_CAMPOS, 0);
	}

	if(CheckOutputLimit(aimData[PR_camPos][0], 20000.0) || CheckOutputLimit(aimData[PR_camPos][1], 20000.0) || CheckOutputLimit(aimData[PR_camPos][2], 20000.0))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_AIM_SYNC] Campos x, y, z: %f, %f, %f",
			aimData[PR_camPos][0], aimData[PR_camPos][1], aimData[PR_camPos][2]);
		#endif
		return KickWithCode(playerid, ID_AIM_SYNC, RAK_INVALID_CAMPOS, 1);
	}

	if(CheckValidityData(aimData[PR_aimZ]))
	{
		#if defined RAK_DEBUG
			printf("[Rakcheat debug] [ID_AIM_SYNC] Aimz: %f", aimData[PR_aimZ]);
		#endif
		return KickWithCode(playerid, ID_AIM_SYNC, RAK_INVALID_AIMZ, 0);
	}
	return 1;
}
