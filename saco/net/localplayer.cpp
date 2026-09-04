
#include "../main.h"
#include "../game/util.h"

extern CGame		 *pGame;
extern CNetGame		 *pNetGame;

//----------------------------------------------------------

CLocalPlayer::CLocalPlayer()
{
	field_147 = GetTickCount();
	field_137 = GetTickCount();
	field_13B = GetTickCount();
	m_bInRCMode = FALSE;
	field_2E2 = 0;
	field_2D6 = GetTickCount();
	field_2F6 = 0;
	m_pPlayerPed = pGame->FindPlayerPed();
	field_F0 = 0;
	field_F4 = 0;
	field_10D = 0;
	field_30A = 0;
	field_10F = GetTickCount();
	field_113 = GetTickCount();
	field_13F = GetTickCount();
	field_117 = field_10F;
	field_11B = field_10F;
	m_bIsSpectating = FALSE;
	field_30F = 0;
	field_310 = -1;
	field_306 = 0;

	ResetAllSyncAttributes();

	BYTE i;
	for (i = 0; i < 13; i++)
	{
		m_byteLastWeapon[i] = 0;
		m_dwLastAmmo[i] = 0;
	}

	m_byteTeam = NO_TEAM;
}

//----------------------------------------------------------

void CLocalPlayer::ResetAllSyncAttributes()
{
	field_17D = 0;
	m_bWantsAnotherClass = FALSE;
	field_302 = 0;
	field_2FE = 0;
	field_1CF = 0;
	field_FA = -1;
	m_bInRCMode = FALSE;
	field_318 = -1;
	field_11F = -1;
	field_121 = -1;
	field_123 = -1;
	memset(field_12B, 0, sizeof(field_12B));
	memset(field_3F, 0, sizeof(field_3F));
	memset(field_5E, 0, sizeof(field_5E));
	//field_92 = 0;
	memset(field_94, 0, sizeof(field_94));
	memset(field_0, 0, sizeof(field_0));
	//memset(field_3C, 0, sizeof(field_3C));
	memset(field_D8, 0, sizeof(field_D8));
	field_FC = 0;
	field_100 = 0;
	field_185 = -1;
	field_187 = -1;
	field_181 = GetTickCount();
	field_189 = 0;

	DWORD dwThisTick = GetTickCount();
	field_2DA = 0;
	field_2DE = 0;
	field_127 = dwThisTick;
}

//----------------------------------------------------------

void CLocalPlayer::Say(PCHAR szText)
{
	BYTE byteTextLength = strlen(szText);
	RakNet::BitStream bsSend;

	bsSend.Write(byteTextLength);
	bsSend.Write(szText, byteTextLength);
	pNetGame->GetRakClient()->RPC(RPC_Chat, &bsSend, HIGH_PRIORITY, RELIABLE, 0, FALSE);
}

//----------------------------------------------------------

void CLocalPlayer::SetPlayerColor(DWORD dwColor)
{
	SetRadarColor(pNetGame->GetPlayerPool()->GetLocalPlayerID(),dwColor);
}

//----------------------------------------------------

DWORD CLocalPlayer::GetPlayerColorAsRGBA()
{
	return TranslateColorCodeToRGBA(pNetGame->GetPlayerPool()->GetLocalPlayerID());
}

//----------------------------------------------------

DWORD CLocalPlayer::GetPlayerColorAsARGB()
{
	return (TranslateColorCodeToRGBA(pNetGame->GetPlayerPool()->GetLocalPlayerID()) >> 8) | 0xFF000000;
}

//----------------------------------------------------

//----------------------------------------------------

// the damage reports scale the amount down to a third before sending
void CLocalPlayer::FUNC_100068A0(WORD a1, float a2, int a3, int a4)
{
	a2 *= 0.33f;

	RakNet::BitStream bsSend;

	bsSend.Write1();
	bsSend.Write(a1);
	bsSend.Write(a2);
	bsSend.Write(a3);
	bsSend.Write(a4);
	pNetGame->GetRakClient()->RPC(RPC_PlayerDamage, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE);
}

//----------------------------------------------------

void CLocalPlayer::FUNC_100069B0(WORD a1, float a2, int a3, int a4)
{
	a2 *= 0.33f;

	RakNet::BitStream bsSend;

	bsSend.Write0();
	bsSend.Write(a1);
	bsSend.Write(a2);
	bsSend.Write(a3);
	bsSend.Write(a4);
	pNetGame->GetRakClient()->RPC(RPC_PlayerDamage, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE);
}

//----------------------------------------------------

void CLocalPlayer::FUNC_10006AC0(WORD a1, float a2, int a3, int a4)
{
	RakNet::BitStream bsSend;

	bsSend.Write0();
	bsSend.Write(a1);
	bsSend.Write(a2);
	bsSend.Write(a3);
	bsSend.Write(a4);
	pNetGame->GetRakClient()->RPC(RPC_ActorDamage, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE);
}
