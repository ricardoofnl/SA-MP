
#pragma once

#define GAMESTATE_CONNECTED		5

#define GAMESTATE_WAIT_CONNECT	1

struct struc_41
{
	bool bUseCJWalk;
	int field_1;
	float fWorldBoundryPX;
	float fWorldBoundryZX;
	float fWorldBoundryPY;
	float fWorldBoundryNY;
	char _gap15;
	float field_16;
	char field_1A;
	char _gap1B[4];
	char field_1F;
	char field_20;
	char field_21;
	char field_22;
	int field_23;
	float field_27;
	char _gap2B;
	BYTE field_2C;
	BYTE field_2D;
	char field_2E;
	char field_2F;
	char _gap30[8];
	BYTE field_38;
	char _gap39;
};

typedef struct _NETGAME_POOLS {
	CVehiclePool	*pVehiclePool;
	CPlayerPool		*pPlayerPool;
	CPickupPool		*pPickupPool;
	CObjectPool		*pObjectPool;
	CActorPool		*pActorPool;
	CGangZonePool	*pGangZonePool;
	CLabelPool		*pLabelPool;
	CTextDrawPool	*pTextDrawPool;
	CMenuPool		*pMenuPool;
} NETGAME_POOLS;

class CNetGame // size: 994
{
private:

	RakClientInterface	*m_pRakClient;

	void UpdateNetwork();

	char _gap4[44];
	char m_szHostOrIp[257];
	char m_szHostName[257];
	char field_232;
	char field_233;
public:
	BYTE field_234;
private:
	int m_iPort;
	int field_239;
	DWORD		m_dwMapIcon[100];
	int m_iGameState;
	int field_3D1;
	struc_41 *field_3D5;
	char field_3D9;
	char _gap3DA[4];
	NETGAME_POOLS* m_pPools;

public:

	CNetGame(PCHAR szHostOrIp,int iPort,PCHAR szPlayerName,PCHAR szPass);

	void Process();

	void InitPools();

	DWORD GetTime();
	int GetGameState() { return m_iGameState; };
	char GetField232() { return field_232; };
	void SetField232(char cValue) { field_232 = cValue; };
	BOOL GetWalkStyle() { return field_3D5->bUseCJWalk; };
	struc_41 * GetSettings() { return field_3D5; };
	void SetWorldTime(BYTE byteHour) { field_3D5->field_2C = byteHour; };
	void SetWorldMinute(BYTE byteMinute) { field_3D5->field_2D = byteMinute; };
	void SetWeather(BYTE byteWeather) { field_3D5->field_2E = byteWeather; };

	CVehiclePool * GetVehiclePool() { return m_pPools->pVehiclePool; };
	CVehiclePool * FUNC_10001180(); // .text:10001180, out of line copy of GetVehiclePool
	CPlayerPool * GetPlayerPool() { return m_pPools->pPlayerPool; };
	CPickupPool * GetPickupPool() { return m_pPools->pPickupPool; };
	CActorPool * GetActorPool() { return m_pPools->pActorPool; };
	CObjectPool * GetObjectPool() { return m_pPools->pObjectPool; };
	CObjectPool * FUNC_10002E10() { return m_pPools->pObjectPool; }; // .text:10002E10, out of line copy of GetObjectPool
	CGangZonePool * GetGangZonePool() { return m_pPools->pGangZonePool; };
	CLabelPool * GetLabelPool() { return m_pPools->pLabelPool; };
	CTextDrawPool * GetTextDrawPool() { return m_pPools->pTextDrawPool; };
	RakClientInterface * GetRakClient() { return m_pRakClient; };

	void  ResetMapIcons();
	void  SetMapIcon(BYTE byteIndex, float fX, float fY, float fZ, BYTE byteIcon, DWORD dwColor, int iStyle);
	void  DisableMapIcon(BYTE byteIndex);

	CMenuPool * GetMenuPool() { return m_pPools->pMenuPool; }; // .text:100084F0
	int ToggleNameTagStatus(); // .text:10008E90
	void sub_1000A540(); // .text:1000A540
};
