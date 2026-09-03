
#pragma once

#define INVALID_VEHICLE_ID 0xFFFF

//----------------------------------------------------

class CVehiclePool
{
public:
	int field_0;

	char _gap4[4000];

	char field_FA4[400];
	int field_1134[MAX_VEHICLES];
	int field_3074[MAX_VEHICLES];
	int field_4FB4[MAX_VEHICLES];

	char _gap6EF4[12000];

	DWORD field_9DD4[MAX_VEHICLES];

	int field_BD14[MAX_VEHICLES];
	int field_DC54[MAX_VEHICLES];
	int field_FB94[MAX_VEHICLES];
	VECTOR field_11AD4[MAX_VEHICLES];

	int field_17894;

	int GetSlotState(unsigned short VehicleID) { if(VehicleID >= MAX_VEHICLES) return 0; return field_3074[VehicleID]; }
	int GetAt(unsigned short VehicleID)
	{
		if(VehicleID < MAX_VEHICLES && field_3074[VehicleID]) return field_1134[VehicleID];
		return 0;
	}

	void FUNC_1001E9B0(); // .text:1001E9B0

	int FUNC_1001EA80(unsigned short VehicleID); // .text:1001EA80

	void FUNC_1001F060(); // .text:1001F060

	void FUNC_1001EB00(unsigned short VehicleID, int a2); // .text:1001EB00

	void FUNC_1001EDE0(); // .text:1001EDE0

	short FUNC_1001EB90(int a1); // .text:1001EB90

	int FindGtaIDFromID(int VehicleID); // .text:1001EBC0

	int FUNC_10001120(unsigned short a1); // .text:10001120

	void FUNC_1001ED70(); // .text:1001ED70

	char FUNC_1001EE20(VECTOR *vecStart, VECTOR *vecEnd); // .text:1001EE20

	CVehiclePool();
};

//----------------------------------------------------
