
#include "../main.h"
#include "../game/util.h"

extern CGame		 *pGame;

using namespace RakNet;
extern CNetGame* pNetGame;
extern CChatWindow *pChatWindow;

//----------------------------------------------------
// layout locks: a negative array size fails the build if any offset moves

typedef char CRemotePlayer_offsets[(
	offsetof(CRemotePlayer, field_C5) == 0xC5 &&
	offsetof(CRemotePlayer, field_C5.quat) == 0xD7 &&
	offsetof(CRemotePlayer, field_C5.vecOffset) == 0xF7 &&
	offsetof(CRemotePlayer, field_C5.wVehicleID) == 0x103 &&
	sizeof(((CRemotePlayer *)0)->field_C5) == 68 &&
	offsetof(CRemotePlayer, field_109) == 0x109 &&
	offsetof(CRemotePlayer, field_10A) == 0x10A &&
	offsetof(CRemotePlayer, field_10B) == 0x10B &&
	offsetof(CRemotePlayer, field_10C) == 0x10C &&
	offsetof(CRemotePlayer, field_17C) == 0x17C &&
	offsetof(CRemotePlayer, field_188) == 0x188 &&
	offsetof(CRemotePlayer, field_194) == 0x194 &&
	offsetof(CRemotePlayer, field_1A0) == 0x1A0 &&
	offsetof(CRemotePlayer, field_1AC) == 0x1AC &&
	offsetof(CRemotePlayer, field_1C5) == 0x1C5 &&
	offsetof(CRemotePlayer, field_1C9) == 0x1C9 &&
	offsetof(CRemotePlayer, m_pPlayerPed) == 0x1DD &&
	offsetof(CRemotePlayer, field_1E1) == 0x1E1 &&
	offsetof(CRemotePlayer, m_PlayerID) == 0x1E5 &&
	offsetof(CRemotePlayer, field_1E7) == 0x1E7 &&
	offsetof(CRemotePlayer, field_1F9) == 0x1F9) ? 1 : -1];

typedef char CNetPlayer_offsets[(offsetof(CNetPlayer, m_PlayerName) == 0x14) ? 1 : -1];
typedef char CPlayerPool_offsets[(offsetof(CPlayerPool, field_6) == 6 &&
	sizeof(std::string) == 0x1C) ? 1 : -1];


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
		m_pPlayerPed->ApplyCommandTask("FollowPedSA", 0, 1000, -1, &vec, 0, 0.1f, 500, 3, 0);
		field_1D9 = dwTick;
	}
}

//----------------------------------------------------

void CRemotePlayer::FUNC_100150D0(VECTOR *pPos, VECTOR *pMoveSpeed)
{
	field_17C.X = pPos->X;
	field_17C.Y = pPos->Y;
	field_17C.Z = pPos->Z;
	field_188.X = pMoveSpeed->X;
	field_188.Y = pMoveSpeed->Y;
	field_188.Z = pMoveSpeed->Z;
	m_pPlayerPed->SetMoveSpeedVector(field_188);
}

//----------------------------------------------------

void CRemotePlayer::FUNC_100155E0(int a1, VECTOR *pPos, VECTOR *pMoveSpeed)
{
	FUNC_100B5210(a1, &_gap16C);
	field_194 = *pPos;
	field_1A0 = *pMoveSpeed;
	field_1E1->SetMoveSpeedVector(*pMoveSpeed);
}

//----------------------------------------------------

float CRemotePlayer::FUNC_100160A0(CRemotePlayer *pOther)
{
	if(!m_pPlayerPed) return 10000.0f;

	MATRIX4X4 matThis, matOther;
	m_pPlayerPed->GetMatrix(&matThis);
	pOther->m_pPlayerPed->GetMatrix(&matOther);

	return sqrt((matThis.pos.X - matOther.pos.X) * (matThis.pos.X - matOther.pos.X) +
		(matThis.pos.Y - matOther.pos.Y) * (matThis.pos.Y - matOther.pos.Y) +
		(matThis.pos.Z - matOther.pos.Z) * (matThis.pos.Z - matOther.pos.Z));
}

//----------------------------------------------------

float CRemotePlayer::FUNC_10016120()
{
	CEntity *pEntity = m_pPlayerPed;
	if(!pEntity) return 10000.0f;

	if(field_10A == 19 && field_1E1) pEntity = field_1E1;

	return pEntity->FUNC_1009F0C0();
}

//----------------------------------------------------

int CRemotePlayer::FUNC_10016330()
{
	if(m_pPlayerPed && m_pPlayerPed->IsAdded() && !m_pPlayerPed->FUNC_100AC5D0() &&
		!m_pPlayerPed->FUNC_100AC640()) return field_1C5;

	return 0;
}

//----------------------------------------------------

void CRemotePlayer::FUNC_10017610(char *szText)
{
	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
	pChatWindow->FUNC_10068020(pPlayerPool->GetPlayerName(m_PlayerID),
		(TranslateColorCodeToRGBA(m_PlayerID) >> 8) | 0xFF000000, szText);
}

//----------------------------------------------------

void CRemotePlayer::FUNC_10014540(short a1, short a2, short a3)
{
	field_1E9 = 1;

	if(field_1F9) {
		pGame->DisableMarker(field_1F9);
		field_1F9 = 0;
	}

	if(m_pPlayerPed) return;

	field_1F9 = pGame->FUNC_100A0D90(0, (float)a1, (float)a2, (float)a3, m_PlayerID, 0);
	field_1ED = a1;
	field_1F1 = a2;
	field_1F5 = a3;
}

//----------------------------------------------------

void CRemotePlayer::FUNC_10014650()
{
	if(field_10A != 17) return;
	if(!field_C5.wVehicleID) return;
	if(field_C5.wVehicleID == INVALID_VEHICLE_ID) return;
	if(field_C5.wVehicleID >= (MAX_VEHICLES + 1000)) return;

	CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();
	CObjectPool *pObjectPool = pNetGame->GetObjectPool();
	CEntity *pEntity;

	if(field_C5.wVehicleID < MAX_VEHICLES) {
		if(!pVehiclePool->field_3074[field_C5.wVehicleID]) return;
		pEntity = (CEntity *)pVehiclePool->field_1134[field_C5.wVehicleID];
	} else {
		WORD wObjectID = field_C5.wVehicleID - MAX_VEHICLES;
		if(wObjectID > MAX_OBJECTS) return;
		if(!pObjectPool->field_4[wObjectID]) return;
		pEntity = (CEntity *)pObjectPool->field_FA4[wObjectID];
	}

	if(!pEntity) return;

	if(field_C5.vecOffset.X > 100.0f) return;
	if(field_C5.vecOffset.X < -100.0f) return;
	if(field_C5.vecOffset.Y > 100.0f) return;
	if(field_C5.vecOffset.Y < -100.0f) return;
	if(field_C5.vecOffset.Z > 100.0f) return;
	if(field_C5.vecOffset.Z < -100.0f) return;

	MATRIX4X4 matEntity;
	MATRIX4X4 matPed;
	VECTOR vecMove;
	VECTOR vecTurn;
	VECTOR vecOut;

	pEntity->GetMatrix(&matEntity);
	pEntity->GetMoveSpeedVector(&vecMove);
	pEntity->GetTurnSpeedVector(&vecTurn);
	m_pPlayerPed->GetMatrix(&matPed);

	FUNC_100B4D10(&vecOut, &matEntity, &field_C5.vecOffset);
	matPed.pos = vecOut;
	m_pPlayerPed->SetMatrix(matPed);
}

//----------------------------------------------------

void CRemotePlayer::FUNC_10014800()
{
	CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();

	if(!m_pPlayerPed) return;
	if(m_pPlayerPed->IsInVehicle()) return;
	if(field_1E7 >= MAX_VEHICLES) return;
	if(!pVehiclePool->field_3074[field_1E7]) return;
	if(!pVehiclePool->field_1134[field_1E7]) return;

	BYTE byteWeapon;
	if(field_10B) byteWeapon = field_AD[3];
	else byteWeapon = field_19[54];
	byteWeapon &= 0x3F;

	if(m_pPlayerPed->GetCurrentWeapon() != byteWeapon) {
		m_pPlayerPed->SetArmedWeapon(byteWeapon, false);
		if(m_pPlayerPed->GetCurrentWeapon() != byteWeapon) {
			m_pPlayerPed->GiveWeapon(byteWeapon, 9999);
			m_pPlayerPed->SetArmedWeapon(byteWeapon, false);
		}
	}

	int iGtaVehicleID = pVehiclePool->FindGtaIDFromID(field_1E7);
	m_pPlayerPed->FUNC_100AC290(iGtaVehicleID, field_10B);
}

//----------------------------------------------------

void CRemotePlayer::FUNC_10014FF0()
{
	if(!m_pPlayerPed) return;

	MATRIX4X4 mat;
	float quatBlend[4];
	float quatCur[4];

	m_pPlayerPed->GetMatrix(&mat);
	FUNC_100B52B0(&mat, quatCur);
	FUNC_100B5480(quatBlend, field_C5.quat, quatCur, 0.75f);
	FUNC_100B6A80(quatBlend, &mat);
	m_pPlayerPed->SetMatrix(mat);

	float fAngle = atan2(-mat.up.X, mat.up.Y) * 57.2957764f;
	if(fAngle < 0.0f) fAngle += 360.0f;
	else if(fAngle >= 360.0f) fAngle -= 360.0f;
	m_pPlayerPed->FUNC_100ABF10(fAngle);
}

//----------------------------------------------------

void CRemotePlayer::FUNC_100148F0()
{
	if(m_pPlayerPed && m_pPlayerPed->IsInVehicle()) {
		MATRIX4X4 mat;
		m_pPlayerPed->GetMatrix(&mat);
		m_pPlayerPed->RemoveFromVehicleAndPutAt(mat.pos.X, mat.pos.Y, mat.pos.Z);
		field_1E1 = NULL;
	}
}

//----------------------------------------------------

void CRemotePlayer::FUNC_10014500(int a1)
{
	if(!a1) {
		if(field_1F9) {
			pGame->DisableMarker(field_1F9);
			field_1F9 = a1;
		}
	}
	field_1E9 = a1;
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
	if(pPlayerPed->IsAPassenger()) return;

	CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();
	if((WORD)pVehiclePool->FUNC_1001EB90((int)pPlayerPed->GetGtaVehicle()) == field_1E7) {
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
