
#include "../main.h"
#include "../game/util.h"

//----------------------------------------------------

CVehiclePool::CVehiclePool()
{
	// loop through and initialize all vehicle properties to 0
	for(VEHICLEID VehicleID = 0; VehicleID < MAX_VEHICLES; VehicleID++) {
		field_3074[VehicleID] = 0;
		field_1134[VehicleID] = 0;
		field_4FB4[VehicleID] = 0;
		field_9DD4[VehicleID] = GetTickCount();
	}
	memset(field_FA4, 0, sizeof(field_FA4));
	field_0 = 0;
	field_17894 = 1;
}

//----------------------------------------------------

int CVehiclePool::FindGtaIDFromID(int VehicleID)
{
	if(field_4FB4[VehicleID]) return GamePool_Vehicle_GetIndex((VEHICLE_TYPE *)field_4FB4[VehicleID]);
	return INVALID_VEHICLE_ID;
}

//----------------------------------------------------

void CVehiclePool::FUNC_1001E9B0()
{
	int iHighest = 0;
	for(int i = 0; i < MAX_VEHICLES; i++) {
		if(field_3074[i]) iHighest = i;
	}
	field_0 = iHighest;
}

//----------------------------------------------------

int __stdcall FUNC_1001EBE0(VEHICLE_TYPE *pVehicle)
{
	if(pVehicle) return GamePool_Vehicle_GetIndex(pVehicle);
	return INVALID_VEHICLE_ID;
}

//----------------------------------------------------

short CVehiclePool::FUNC_1001EB90(int a1)
{
	for(int i = 1; i <= field_0; i++) {
		if(a1 == field_4FB4[i]) return i;
	}
	return -1;
}

//----------------------------------------------------

void CVehiclePool::FUNC_1001F060()
{
	for(VEHICLEID VehicleID = 0; VehicleID < MAX_VEHICLES; VehicleID++) {
		FUNC_1001EA80(VehicleID);
	}
}

//----------------------------------------------------

void CVehiclePool::FUNC_1001EDE0()
{
	for(VEHICLEID VehicleID = 0; VehicleID <= field_0; VehicleID++) {
		if(field_3074[VehicleID]) ((CVehicle *)field_1134[VehicleID])->FUNC_100B81F0();
	}
}

//----------------------------------------------------
