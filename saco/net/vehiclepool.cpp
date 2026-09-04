
#include "../main.h"
#include "../game/util.h"

extern int dword_1026EBA0;

// the number plate renderer lives on a global, only its texture builder is needed here
class CPlateRenderer
{
public:
	int FUNC_1006D880(char *szPlate); // .text:1006D880
};

// layout locks: these fail to compile if a field offset or the size moves
typedef char chk_CVehiclePool_size[sizeof(CVehiclePool) == 0x17898 ? 1 : -1];
typedef char chk_field_FA4[offsetof(CVehiclePool, field_FA4) == 0xFA4 ? 1 : -1];
typedef char chk_field_1134[offsetof(CVehiclePool, field_1134) == 0x1134 ? 1 : -1];
typedef char chk_field_3074[offsetof(CVehiclePool, field_3074) == 0x3074 ? 1 : -1];
typedef char chk_field_4FB4[offsetof(CVehiclePool, field_4FB4) == 0x4FB4 ? 1 : -1];
typedef char chk_field_9DD4[offsetof(CVehiclePool, field_9DD4) == 0x9DD4 ? 1 : -1];
typedef char chk_field_BD14[offsetof(CVehiclePool, field_BD14) == 0xBD14 ? 1 : -1];
typedef char chk_field_DC54[offsetof(CVehiclePool, field_DC54) == 0xDC54 ? 1 : -1];
typedef char chk_field_FB94[offsetof(CVehiclePool, field_FB94) == 0xFB94 ? 1 : -1];
typedef char chk_field_11AD4[offsetof(CVehiclePool, field_11AD4) == 0x11AD4 ? 1 : -1];
typedef char chk_field_17894[offsetof(CVehiclePool, field_17894) == 0x17894 ? 1 : -1];
typedef char chk_CVehicle_field_64[offsetof(CVehicle, field_64) == 0x64 ? 1 : -1];
typedef char chk_CVehicle_field_65[offsetof(CVehicle, field_65) == 0x65 ? 1 : -1];
typedef char chk_CVehicle_field_71[offsetof(CVehicle, field_71) == 0x71 ? 1 : -1];

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

// MATCH
CVehiclePool::~CVehiclePool()
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

void CVehiclePool::FUNC_1001EB00(unsigned short VehicleID, int a2)
{
	if(field_3074[VehicleID]) ((CVehicle *)field_1134[VehicleID])->FUNC_100B7090(a2);
}

//----------------------------------------------------

int CVehiclePool::FUNC_1001EA80(unsigned short VehicleID)
{
	if(VehicleID < MAX_VEHICLES && field_3074[VehicleID] && field_1134[VehicleID]) {
		((CVehicle *)field_1134[VehicleID])->FUNC_100B81F0();
		field_3074[VehicleID] = 0;
		delete (CVehicle *)field_1134[VehicleID];
		field_1134[VehicleID] = 0;
		field_4FB4[VehicleID] = 0;
		FUNC_1001E9B0();
		return 1;
	}
	return 0;
}

//----------------------------------------------------

void CVehiclePool::FUNC_1001EB30(unsigned short VehicleID, char a2, BYTE a3)
{
	if(VehicleID < MAX_VEHICLES && field_3074[VehicleID] && field_1134[VehicleID] && field_BD14[VehicleID]) {
		CVehicle *pVehicle = (CVehicle *)field_1134[VehicleID];
		if(a2) {
			pVehicle->field_64 = 1;
			pVehicle->field_65 = 0;
		}
		pVehicle->FUNC_100B7840(a3);
	}
}

//----------------------------------------------------

int CVehiclePool::FUNC_1001EC00()
{
	float fClosestDistance = 10000.0f;
	VEHICLEID ClosestVehicleID = INVALID_VEHICLE_ID;

	for(VEHICLEID VehicleID = 0; VehicleID <= field_0; VehicleID++) {
		if(VehicleID < MAX_VEHICLES && field_3074[VehicleID] && field_BD14[VehicleID]) {
			float fDistance = ((CVehicle *)field_1134[VehicleID])->FUNC_1009F0C0();
			if(fDistance < fClosestDistance) {
				fClosestDistance = fDistance;
				ClosestVehicleID = VehicleID;
			}
		}
	}
	return ClosestVehicleID;
}

//----------------------------------------------------

void CVehiclePool::FUNC_1001ED70()
{
	if(!field_17894) return;

	if(dword_1026EBA0 && !*(DWORD *)(dword_1026EBA0 + 0x20))
		*(DWORD *)(dword_1026EBA0 + 0x20) = ((CPlateRenderer *)dword_1026EBA0)->FUNC_1006D880("XYZSR998");

	for(VEHICLEID VehicleID = 0; VehicleID <= field_0; VehicleID++) {
		if(field_3074[VehicleID]) ((CVehicle *)field_1134[VehicleID])->FUNC_100B81A0();
	}
}

//----------------------------------------------------

short CVehiclePool::FUNC_1001EEB0(int a1, VECTOR *vecOrigin, VECTOR *vecLine)
{
	char colPoint[52];
	DWORD dwHitEntity = 0;

	ProcessLineOfSight(vecOrigin, vecLine, (VECTOR *)colPoint, &dwHitEntity, 0, 1, 0, 0, 0, 0, 0, 0);
	if(!dwHitEntity) return -1;

	// the sentinel has to stay on the loop exit path, folding it into the return narrows it to 16 bits
	int iVehicleID;
	for(int i = 1; ; i++) {
		if(i > field_0) { iVehicleID = INVALID_VEHICLE_ID; break; }
		if(dwHitEntity == field_4FB4[i]) { iVehicleID = i; break; }
	}
	return iVehicleID;
}

//----------------------------------------------------

char CVehiclePool::FUNC_1001EE20(VECTOR *vecStart, VECTOR *vecEnd)
{
	for(int i = 0; i <= field_0; i++) {
		if(field_3074[i] && field_1134[i]) {
			CVehicle *pVehicle = (CVehicle *)field_1134[i];
			if(pVehicle->IsAdded() && pVehicle->FUNC_1009F190() < 300.0f
				&& !pVehicle->FUNC_1009FCE0()
				&& pVehicle->FUNC_1009FC00(vecStart, vecEnd, 1)) return 1;
		}
	}
	return 0;
}

//----------------------------------------------------

int CVehiclePool::FUNC_1001EC70(float fX, float fY, float fZ)
{
	float fClosestDistance = 20000.0f;
	VEHICLEID ClosestVehicleID = INVALID_VEHICLE_ID;

	for(VEHICLEID VehicleID = 0; VehicleID <= field_0; VehicleID++) {
		if(field_3074[VehicleID] && field_BD14[VehicleID]) {
			float fDistance = ((CVehicle *)field_1134[VehicleID])->GetDistanceFromPoint(fX, fY, fZ);
			if(fDistance < fClosestDistance) {
				fClosestDistance = fDistance;
				ClosestVehicleID = VehicleID;
			}
		}
	}
	return ClosestVehicleID;
}

//----------------------------------------------------
