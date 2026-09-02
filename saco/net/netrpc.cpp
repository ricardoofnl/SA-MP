
#include "../main.h"

extern CNetGame*	pNetGame;
extern CGame * pGame;
extern CChatWindow *pChatWindow;

// MATCH
BYTE Checksum(BYTE *pData, WORD wLen)
{
	BYTE byteSum = 0;

	for(DWORD i = 0; i != wLen; i++)
		byteSum ^= pData[i] & 0xCC;

	return byteSum;
}

// MATCH
void LoadModelsThread(void *pParam)
{
	pGame->LoadRequestedModels();
	_endthread();
}

// TODO: these RPCs
void Unk22(RPCParameters *rpcParams) {}
void Unk24(RPCParameters *rpcParams) {}
// MATCH
void Unk3A(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	WORD wLabelID;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);

	CLabelPool *pLabelPool = pNetGame->GetLabelPool();
	if(!pLabelPool) return;

	bsData.Read(wLabelID);

	if(wLabelID < MAX_LABELS && pLabelPool->m_bLabelSlotState[wLabelID])
		pLabelPool->Delete(wLabelID);
}
void Unk3B(RPCParameters *rpcParams) {}
void Unk3D(RPCParameters *rpcParams) {}
void SetCheckpoint(RPCParameters *rpcParams) {}
// MATCH
void DisableCheckpoint(RPCParameters *rpcParams)
{
	pGame->m_bCheckpointsEnabled = FALSE;
}
void SetRaceCheckpoint(RPCParameters *rpcParams) {}
// MATCH
void DisableRaceCheckpoint(RPCParameters *rpcParams)
{
	pGame->m_bRaceCheckpointsEnabled = FALSE;
}
void UpdateScoresPingsIPs(RPCParameters *rpcParams) {}
void SvrStats(RPCParameters *rpcParams) {}
// MATCH
void GameModeRestart(RPCParameters *rpcParams)
{
	pNetGame->sub_1000A540();
}
void ConnectionRejected(RPCParameters *rpcParams) {}
// MATCH
void ClientMessage(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	DWORD dwColor;
	DWORD dwStrLen;
	char szMessage[256];

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);

	memset(szMessage,0,sizeof(szMessage));

	bsData.Read(dwColor);
	bsData.Read(dwStrLen);

	if(dwStrLen > 255) return;

	bsData.Read(szMessage,dwStrLen);
	szMessage[dwStrLen] = '\0';

	pChatWindow->AddClientMessage(dwColor,szMessage);
}
// MATCH
void WorldTime(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	BYTE byteWorldTime;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(byteWorldTime);

	pNetGame->SetWorldTime(byteWorldTime);
}
// MATCH
void Pickup(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	int iPickup;
	PICKUP Pickup;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(iPickup);
	bsData.Read((PCHAR)&Pickup,sizeof(PICKUP));

	CPickupPool *pPickupPool = pNetGame->GetPickupPool();
	if(pPickupPool)
		pPickupPool->sub_10013270(&Pickup,iPickup);
}
// MATCH
void DestroyPickup(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	int iPickup;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(iPickup);

	CPickupPool *pPickupPool = pNetGame->GetPickupPool();
	if(pPickupPool)
		pPickupPool->sub_10013320(iPickup);
}
// MATCH
void DestroyWeaponPickup(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	BYTE bytePickupIndex;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(bytePickupIndex);

	pNetGame->GetPickupPool()->sub_10013380(bytePickupIndex);
}
// MATCH
void ScmEvent(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	PLAYERID playerId;
	int iEvent;
	int iVehicle;
	int iArg1;
	int iArg2;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(playerId);
	bsData.Read(iEvent);
	bsData.Read(iVehicle);
	bsData.Read(iArg1);
	bsData.Read(iArg2);

	sub_10001A60(playerId,iEvent,iVehicle,iArg1,iArg2);
}
// MATCH
void Weather(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	BYTE byteWeather;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(byteWeather);

	pNetGame->SetWeather(byteWeather);
	pGame->SetWorldWeather(byteWeather);
}
// MATCH
void SetTimeEx(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	BYTE byteHour;
	BYTE byteMinute;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(byteHour);
	bsData.Read(byteMinute);

	pGame->SetWorldTime(byteHour,byteMinute);
	pNetGame->SetWorldTime(byteHour);
	pNetGame->SetWorldMinute(byteMinute);
}
void ToggleClock(RPCParameters *rpcParams) {}
// MATCH
void Unk3C(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);

	DWORD dwTime = 0;
	bsData.Read(dwTime);

	pGame->SetTimeInMilliseconds(dwTime);
}
void WorldPlayerAdd(RPCParameters *rpcParams) {}
// MATCH
void WorldPlayerDeath(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	PLAYERID playerId;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);

	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();

	bsData.Read(playerId);

	if(pPlayerPool)
	{
		CRemotePlayer *pRemotePlayer = pPlayerPool->GetAt(playerId);
		if(pRemotePlayer)
			pRemotePlayer->FUNC_10017570();
	}
}
// MATCH
void WorldPlayerRemove(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);

	PLAYERID playerId = 0;
	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();

	bsData.Read(playerId);

	if(pPlayerPool)
	{
		CRemotePlayer *pRemotePlayer = pNetGame->GetPlayerPool()->GetAt(playerId);
		if(pRemotePlayer)
			pRemotePlayer->FUNC_10017530();
	}
}
void WorldVehicleAdd(RPCParameters *rpcParams) {}
void WorldVehicleRemove(RPCParameters *rpcParams) {}
// MATCH
void DamageVehicle(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	VEHICLEID VehicleID;
	int iPanelDamage;
	int iDoorDamage;
	BYTE byteLightDamage;
	BYTE byteTyreDamage;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(VehicleID);
	bsData.Read(iPanelDamage);
	bsData.Read(iDoorDamage);
	bsData.Read(byteLightDamage);
	bsData.Read(byteTyreDamage);

	CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();

	if(pVehiclePool->GetSlotState(VehicleID))
	{
		CVehicle *pVehicle = (CVehicle *)pVehiclePool->GetAt(VehicleID);
		if(pVehicle)
		{
			pVehicle->sub_100B7AC0(iPanelDamage,iDoorDamage,byteLightDamage);
			pVehicle->sub_100B7940(byteTyreDamage);
		}
	}
}
void Unk18(RPCParameters *rpcParams) {}
// MATCH
void EnterVehicle(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);

	PLAYERID playerId;
	VEHICLEID VehicleID = 0;
	BYTE bytePassenger = 0;
	BOOL bPassenger = FALSE;

	bsData.Read(playerId);
	bsData.Read(VehicleID);
	bsData.Read(bytePassenger);

	if(bytePassenger) bPassenger = TRUE;

	CRemotePlayer *pRemotePlayer = pNetGame->GetPlayerPool()->GetAt(playerId);
	if(pRemotePlayer)
	{
		if(pRemotePlayer->FUNC_10016120() < 200.0f)
			pRemotePlayer->EnterVehicle(VehicleID,bPassenger);
	}
}
// MATCH
void ExitVehicle(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);

	PLAYERID playerId;
	VEHICLEID VehicleID = 0;

	bsData.Read(playerId);
	bsData.Read(VehicleID);

	CRemotePlayer *pRemotePlayer = pNetGame->GetPlayerPool()->GetAt(playerId);
	if(pRemotePlayer)
	{
		if(pRemotePlayer->FUNC_10016120() < 200.0f)
			pRemotePlayer->ExitVehicle();
	}
}
void ServerJoin(RPCParameters *rpcParams) {}
// MATCH
void ServerQuit(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	PLAYERID playerId;
	BYTE byteReason;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);

	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();

	bsData.Read(playerId);
	bsData.Read(byteReason);

	pPlayerPool->sub_10014090(playerId,byteReason);
}
void InitGame(RPCParameters *rpcParams) {}
void Chat(RPCParameters *rpcParams) {}
void RequestClass(RPCParameters *rpcParams) {}
// MATCH
void RequestSpawn(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	BYTE byteRequestOutcome = 0;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(byteRequestOutcome);

	CLocalPlayer *pLocalPlayer = pNetGame->GetPlayerPool()->GetLocalPlayer();

	if(byteRequestOutcome == 2 || (byteRequestOutcome && pLocalPlayer->field_302))
		pLocalPlayer->sub_10003C20();
	else
		pLocalPlayer->field_302 = 0;
}
void EditAttachedObject(RPCParameters *rpcParams) {}
void EditObject(RPCParameters *rpcParams) {}
void SelectObject(RPCParameters *rpcParams) {}
void Unk1C(RPCParameters *rpcParams) {}
void UnkAA(RPCParameters *rpcParams) {}
void ClientCheck(RPCParameters *rpcParams) {}
void UnkAB(RPCParameters *rpcParams) {}
// MATCH
void UnkAC(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	ACTORID ActorID;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);

	CActorPool *pActorPool = pNetGame->GetActorPool();
	if(!pActorPool) return;

	bsData.Read(ActorID);

	pActorPool->sub_100016F0(ActorID);
}

//----------------------------------------------------

// MATCH
void RegisterRPCs(RakClientInterface * pRakClient)
{
	REGISTER_STATIC_RPC(pRakClient,Unk22);
	REGISTER_STATIC_RPC(pRakClient,Unk24);
	REGISTER_STATIC_RPC(pRakClient,Unk3A);
	REGISTER_STATIC_RPC(pRakClient,Unk3B);
	REGISTER_STATIC_RPC(pRakClient,Unk3D);
	REGISTER_STATIC_RPC(pRakClient,SetCheckpoint);
	REGISTER_STATIC_RPC(pRakClient,DisableCheckpoint);
	REGISTER_STATIC_RPC(pRakClient,SetRaceCheckpoint);
	REGISTER_STATIC_RPC(pRakClient,DisableRaceCheckpoint);
	REGISTER_STATIC_RPC(pRakClient,UpdateScoresPingsIPs);
	REGISTER_STATIC_RPC(pRakClient,SvrStats);
	REGISTER_STATIC_RPC(pRakClient,GameModeRestart);
	REGISTER_STATIC_RPC(pRakClient,ConnectionRejected);
	REGISTER_STATIC_RPC(pRakClient,ClientMessage);
	REGISTER_STATIC_RPC(pRakClient,WorldTime);
	REGISTER_STATIC_RPC(pRakClient,Pickup);
	REGISTER_STATIC_RPC(pRakClient,DestroyPickup);
	REGISTER_STATIC_RPC(pRakClient,DestroyWeaponPickup);
	REGISTER_STATIC_RPC(pRakClient,ScmEvent);
	REGISTER_STATIC_RPC(pRakClient,Weather);
	REGISTER_STATIC_RPC(pRakClient,SetTimeEx);
	REGISTER_STATIC_RPC(pRakClient,ToggleClock);
	REGISTER_STATIC_RPC(pRakClient,Unk3C);
	REGISTER_STATIC_RPC(pRakClient,WorldPlayerAdd);
	REGISTER_STATIC_RPC(pRakClient,WorldPlayerDeath);
	REGISTER_STATIC_RPC(pRakClient,WorldPlayerRemove);
	REGISTER_STATIC_RPC(pRakClient,WorldVehicleAdd);
	REGISTER_STATIC_RPC(pRakClient,WorldVehicleRemove);
	REGISTER_STATIC_RPC(pRakClient,DamageVehicle);
	REGISTER_STATIC_RPC(pRakClient,Unk18);
	REGISTER_STATIC_RPC(pRakClient,EnterVehicle);
	REGISTER_STATIC_RPC(pRakClient,ExitVehicle);
	REGISTER_STATIC_RPC(pRakClient,ServerJoin);
	REGISTER_STATIC_RPC(pRakClient,ServerQuit);
	REGISTER_STATIC_RPC(pRakClient,InitGame);
	REGISTER_STATIC_RPC(pRakClient,Chat);
	REGISTER_STATIC_RPC(pRakClient,RequestClass);
	REGISTER_STATIC_RPC(pRakClient,RequestSpawn);
	REGISTER_STATIC_RPC(pRakClient,EditAttachedObject);
	REGISTER_STATIC_RPC(pRakClient,EditObject);
	REGISTER_STATIC_RPC(pRakClient,SelectObject);
	REGISTER_STATIC_RPC(pRakClient,Unk1C);
	REGISTER_STATIC_RPC(pRakClient,UnkAA);
	REGISTER_STATIC_RPC(pRakClient,ClientCheck);
	REGISTER_STATIC_RPC(pRakClient,UnkAB);
	REGISTER_STATIC_RPC(pRakClient,UnkAC);
}

//----------------------------------------------------

// MATCH
void UnRegisterRPCs(RakClientInterface * pRakClient)
{
	UNREGISTER_STATIC_RPC(pRakClient,Unk3C);
	UNREGISTER_STATIC_RPC(pRakClient,WorldPlayerAdd);
	UNREGISTER_STATIC_RPC(pRakClient,WorldPlayerDeath);
	UNREGISTER_STATIC_RPC(pRakClient,WorldPlayerRemove);
	UNREGISTER_STATIC_RPC(pRakClient,WorldVehicleAdd);
	UNREGISTER_STATIC_RPC(pRakClient,WorldVehicleRemove);
	UNREGISTER_STATIC_RPC(pRakClient,Unk18);
	UNREGISTER_STATIC_RPC(pRakClient,RequestClass);
	UNREGISTER_STATIC_RPC(pRakClient,RequestSpawn);
	UNREGISTER_STATIC_RPC(pRakClient,DamageVehicle);
	UNREGISTER_STATIC_RPC(pRakClient,EnterVehicle);
	UNREGISTER_STATIC_RPC(pRakClient,ExitVehicle);
	UNREGISTER_STATIC_RPC(pRakClient,Unk22);
	UNREGISTER_STATIC_RPC(pRakClient,Unk24);
	UNREGISTER_STATIC_RPC(pRakClient,Unk3A);
	UNREGISTER_STATIC_RPC(pRakClient,Unk3B);
	UNREGISTER_STATIC_RPC(pRakClient,Unk3D);
	UNREGISTER_STATIC_RPC(pRakClient,ServerJoin);
	UNREGISTER_STATIC_RPC(pRakClient,ServerQuit);
	UNREGISTER_STATIC_RPC(pRakClient,InitGame);
	UNREGISTER_STATIC_RPC(pRakClient,Chat);
	UNREGISTER_STATIC_RPC(pRakClient,SetCheckpoint);
	UNREGISTER_STATIC_RPC(pRakClient,DisableCheckpoint);
	UNREGISTER_STATIC_RPC(pRakClient,SetRaceCheckpoint);
	UNREGISTER_STATIC_RPC(pRakClient,DisableRaceCheckpoint);
	UNREGISTER_STATIC_RPC(pRakClient,UpdateScoresPingsIPs);
	UNREGISTER_STATIC_RPC(pRakClient,SvrStats);
	UNREGISTER_STATIC_RPC(pRakClient,GameModeRestart);
	UNREGISTER_STATIC_RPC(pRakClient,ConnectionRejected);
	UNREGISTER_STATIC_RPC(pRakClient,ClientMessage);
	UNREGISTER_STATIC_RPC(pRakClient,WorldTime);
	UNREGISTER_STATIC_RPC(pRakClient,Pickup);
	UNREGISTER_STATIC_RPC(pRakClient,DestroyPickup);
	UNREGISTER_STATIC_RPC(pRakClient,DestroyWeaponPickup);
	UNREGISTER_STATIC_RPC(pRakClient,ScmEvent);
	UNREGISTER_STATIC_RPC(pRakClient,Weather);
	UNREGISTER_STATIC_RPC(pRakClient,SetTimeEx);
	UNREGISTER_STATIC_RPC(pRakClient,ToggleClock);
	UNREGISTER_STATIC_RPC(pRakClient,EditAttachedObject);
	UNREGISTER_STATIC_RPC(pRakClient,EditObject);
	UNREGISTER_STATIC_RPC(pRakClient,SelectObject);
	UNREGISTER_STATIC_RPC(pRakClient,Unk1C);
	UNREGISTER_STATIC_RPC(pRakClient,UnkAA);
	UNREGISTER_STATIC_RPC(pRakClient,ClientCheck);
	UNREGISTER_STATIC_RPC(pRakClient,UnkAB);
	UNREGISTER_STATIC_RPC(pRakClient,UnkAC);
}

//----------------------------------------------------
