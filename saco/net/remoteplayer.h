
#pragma once

//----------------------------------------------------

#pragma pack(1)
class CRemotePlayer
{
public:
	//char _gap0[509];
	int field_0;
	int field_4;
	int field_8;
	char field_C;

	char _gapD[12];

	char field_19[63];

	char _gap58[54];

	char field_8E[31];
	char field_AD[24];
	// one 68-byte block: ResetAllSyncAttributes memsets it whole
	struct {
		char _pad0[50];
		VECTOR vecOffset; // 0xF7
		WORD wVehicleID; // 0x103
		char _pad1[4];
	} field_C5;
	char field_109;
	BYTE field_10A;
	BYTE field_10B;
	int field_10C;
	int field_110;

	char _gap114[88];
	char _gap16C[16];
	VECTOR field_17C;
	VECTOR field_188;
	VECTOR field_194;
	VECTOR field_1A0;

	int field_1AC;
	int field_1B0;
	int field_1B4;
	char field_1B8;
	DWORD field_1B9;
	DWORD field_1BD;
	int field_1C1;
	int field_1C5;
	VECTOR field_1C9;
	DWORD field_1D5;
	DWORD field_1D9;
	CPlayerPed			*m_pPlayerPed;
	CVehicle *field_1E1;
	PLAYERID			m_PlayerID;
	WORD field_1E7;
	int field_1E9;
	int field_1ED;
	int field_1F1;
	int field_1F5;
	int field_1F9;

public:

	CRemotePlayer();

	void ResetAllSyncAttributes();

	void SetPlayerColor(DWORD dwColor);
	DWORD GetPlayerColorAsRGBA();
	DWORD GetPlayerColorAsARGB();

	BOOL FUNC_10001080() { return m_pPlayerPed && field_10A; }; // .text:10001080

	void EnterVehicle(VEHICLEID VehicleID, BOOL bPassenger);
	void ExitVehicle();

	void FUNC_100143A0(); // .text:100143A0
	void FUNC_10014500(int a1); // .text:10014500
	void FUNC_10014540(short a1, short a2, short a3); // .text:10014540
	void FUNC_10014650(); // .text:10014650
	void FUNC_100148F0(); // .text:100148F0
	void FUNC_10014800(); // .text:10014800
	void FUNC_10017610(char *szText); // .text:10017610
	void FUNC_100150D0(VECTOR *pPos, VECTOR *pMoveSpeed); // .text:100150D0
	void FUNC_100155E0(int a1, VECTOR *pPos, VECTOR *pMoveSpeed); // .text:100155E0
	void FUNC_10015760(char *pAimSync); // .text:10015760
	void FUNC_10015C90(char *pTrailerSync); // .text:10015C90
	void FUNC_10017440(char *pPassengerSync); // .text:10017440
	BOOL FUNC_100145F0(); // .text:100145F0
	void FUNC_10016270(BYTE byteNewState, BYTE byteOldState); // .text:10016270
	void FUNC_100165B0(BYTE byteNewState); // .text:100165B0
	BOOL FUNC_10014620(); // .text:10014620
	void FUNC_10016660(); // .text:10016660
	float FUNC_100160A0(CRemotePlayer *pOther); // .text:100160A0
	float FUNC_10016120(); // .text:10016120
	void sub_10017610(PCHAR szText); // .text:10017610
	void FUNC_10017530(); // .text:10017530
	void FUNC_10017570(); // .text:10017570
	int FUNC_10016330(); // .text:10016330
};

//----------------------------------------------------
