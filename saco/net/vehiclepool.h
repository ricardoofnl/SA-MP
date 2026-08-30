
#pragma once

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

	char _gapBD14[48000];

	int field_17894;

	int GetSlotState(unsigned short VehicleID) { if(VehicleID >= MAX_VEHICLES) return 0; return field_3074[VehicleID]; }
	int GetAt(unsigned short VehicleID) { if(!field_3074[VehicleID]) return 0; return field_1134[VehicleID]; }

	short FUNC_1001EB90(int a1); // .text:1001EB90

	int FUNC_10001120(unsigned short a1); // .text:10001120

	void FUNC_1001ED70(); // .text:1001ED70

	char FUNC_1001EE20(VECTOR *vecStart, VECTOR *vecEnd); // .text:1001EE20

	CVehiclePool();
};

//----------------------------------------------------
