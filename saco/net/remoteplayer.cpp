
#include "../main.h"
#include "../game/util.h"

extern CGame		 *pGame;

using namespace RakNet;
extern CNetGame* pNetGame;

//----------------------------------------------------

CRemotePlayer::CRemotePlayer()
{
	field_1E7 = 0;
	field_10A = 0;
	m_PlayerID = INVALID_PLAYER_ID;
	m_pPlayerPed = NULL;
	field_1B8 = 0;
	field_109 = -1;
	field_4 = 1;
	field_0 = 0;
	field_8 = 0;
	field_1F9 = 0;
	field_C = 0;
	field_10C = 0;
	field_1C1 = 0;
	field_1D5 = GetTickCount();
	field_1D9 = GetTickCount();
	field_1B9 = GetTickCount();
	ResetAllSyncAttributes();
}

//----------------------------------------------------

void CRemotePlayer::ResetAllSyncAttributes()
{
	field_1E7 = 0;
	field_1B0 = 0;
	field_1AC = 0;
	field_1E1 = 0;
	field_10B = 0;
	field_110 = 0;
	field_1ED = 0;
	field_1F1 = 0;
	field_1F5 = 0;
	field_C = 0;
	field_1B4 = 0;
	field_1C5 = 2;
	memset(&field_C5, 0, sizeof(field_C5));
	memset(field_19, 0, sizeof(field_19));
	memset(field_AD, 0, sizeof(field_AD));
	memset(field_8E, 0, sizeof(field_8E));
	memset(&field_1C9, 0, sizeof(field_1C9));
	if(field_1F9)
	{
		pGame->DisableMarker(field_1F9);
		field_1F9 = 0;
	}
	field_1E9 = 0;
	if(pNetGame)
		field_1BD = pNetGame->GetTime();
}

//----------------------------------------------------

void CRemotePlayer::SetPlayerColor(DWORD dwColor)
{
	SetRadarColor(m_PlayerID,dwColor);
}

//----------------------------------------------------

DWORD CRemotePlayer::GetPlayerColorAsRGBA()
{
	return TranslateColorCodeToRGBA(m_PlayerID);
}

//----------------------------------------------------

DWORD CRemotePlayer::GetPlayerColorAsARGB()
{
	return (TranslateColorCodeToRGBA(m_PlayerID) >> 8) | 0xFF000000;
}

//----------------------------------------------------

void CRemotePlayer::EnterVehicle(VEHICLEID VehicleID, BOOL bPassenger)
{
	CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();
	CVehicle *pVehicle = (CVehicle *)pVehiclePool->GetAt(VehicleID);

	if(m_pPlayerPed && pVehicle && !m_pPlayerPed->IsInVehicle()) {
		int iGtaVehicleID = pVehiclePool->FindGtaIDFromID(VehicleID);
		if(iGtaVehicleID && iGtaVehicleID != INVALID_VEHICLE_ID) {
			m_pPlayerPed->SetKeys(0,0,0);
			m_pPlayerPed->EnterVehicle(iGtaVehicleID,bPassenger);
		}
	}
}

//----------------------------------------------------

void CRemotePlayer::FUNC_10017530()
{
	if(m_pPlayerPed) {
		ResetAllSyncAttributes();
		pGame->DeletePlayerPed((int)m_pPlayerPed);
		m_pPlayerPed = NULL;
	}
	field_10A = 0;
	field_4 = 1;
}

//----------------------------------------------------

void CRemotePlayer::FUNC_10017570()
{
	if(m_pPlayerPed) {
		m_pPlayerPed->SetKeys(0,0,0);
		m_pPlayerPed->FUNC_100AFFD0();
	}
	if(field_10A != 32) field_10A = 32;
	ResetAllSyncAttributes();
}

//----------------------------------------------------

void CRemotePlayer::FUNC_100143A0()
{
	if(!m_pPlayerPed) return;
	if(!m_pPlayerPed->IsAdded()) return;
	if(field_10C) return;
	if(pGame && !pGame->m_bHeadMove) return;
	if(m_pPlayerPed->FUNC_100ADC90()) return;

	MATRIX4X4 mat;
	m_pPlayerPed->GetMatrix(&mat);

	DWORD dwTick = GetTickCount();

	if((dwTick - field_1D5) > 1000) {
		CAMERA_AIM *pAim = GameGetRemotePlayerAim(m_pPlayerPed->m_bytePlayerNumber);
		VECTOR vecAim;
		vecAim.X = pAim->f1x * 20.0f + mat.pos.X;
		vecAim.Y = pAim->f1y * 20.0f + mat.pos.Y;
		vecAim.Z = pAim->f1z * 20.0f + mat.pos.Z;
		field_1D5 = dwTick;
		field_1C9.X = vecAim.X - mat.pos.X;
		field_1C9.Y = vecAim.Y - mat.pos.Y;
		field_1C9.Z = vecAim.Z - mat.pos.Z;
	}

	if((dwTick - field_1D9) > 200) {
		VECTOR vec;
		vec.X = mat.pos.X + field_1C9.X;
		vec.Y = mat.pos.Y + field_1C9.Y;
		vec.Z = mat.pos.Z + field_1C9.Z;
		m_pPlayerPed->FUNC_100ADFD0("FollowPedSA", 0, 1000, -1, &vec, 0, 0.1f, 500, 3, 0);
		field_1D9 = dwTick;
	}
}

//----------------------------------------------------

BOOL CRemotePlayer::FUNC_100145F0()
{
	if(field_10A == 17 && field_C5.wVehicleID && field_C5.wVehicleID != INVALID_VEHICLE_ID &&
		field_C5.wVehicleID < (MAX_VEHICLES + 1000)) return TRUE;

	return FALSE;
}

//----------------------------------------------------

BOOL CRemotePlayer::FUNC_10014620()
{
	if(field_10A == 17 && field_C5.wVehicleID && field_C5.wVehicleID != INVALID_VEHICLE_ID &&
		field_C5.wVehicleID >= MAX_VEHICLES && field_C5.wVehicleID < (MAX_VEHICLES + 1000)) return TRUE;

	return FALSE;
}

//----------------------------------------------------

void CRemotePlayer::FUNC_10016270(BYTE byteNewState, BYTE byteOldState)
{
	if(byteNewState != 19 || byteOldState != 17) return;

	CPlayerPed *pPlayerPed = pGame->FindPlayerPed();
	if(!pPlayerPed) return;
	if(!pPlayerPed->IsInVehicle()) return;
	if(pPlayerPed->sub_100ABFC0()) return;

	CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();
	if((WORD)pVehiclePool->FUNC_1001EB90(pPlayerPed->FUNC_100AC000()) == field_1E7) {
		MATRIX4X4 mat;
		pPlayerPed->GetMatrix(&mat);
		pPlayerPed->RemoveFromVehicleAndPutAt(mat.pos.X, mat.pos.Y, mat.pos.Z + 1.0f);
		pGame->DisplayGameText("~r~Car Jacked~w~!", 1000, 5);
	}
}

//----------------------------------------------------

void CRemotePlayer::FUNC_100165B0(BYTE byteNewState)
{
	if(byteNewState != field_10A) {
		FUNC_10016270(byteNewState, field_10A);
		field_10A = byteNewState;
	}
}

//----------------------------------------------------

void CRemotePlayer::FUNC_10016660()
{
	if(field_1F9) {
		pGame->DisableMarker(field_1F9);
		field_1F9 = 0;
	}
	field_1E9 = 0;
	if(m_pPlayerPed) {
		pGame->DeletePlayerPed((int)m_pPlayerPed);
		m_pPlayerPed = NULL;
	}
}

//----------------------------------------------------

void CRemotePlayer::ExitVehicle()
{
	if(m_pPlayerPed && m_pPlayerPed->IsInVehicle()) {
		m_pPlayerPed->SetKeys(0,0,0);
		m_pPlayerPed->ExitCurrentVehicle();
	}
}

//----------------------------------------------------
