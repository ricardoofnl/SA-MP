
#include "../main.h"

extern CNetGame*	pNetGame;
extern CGame * pGame;

// TODO: these RPCs
void Unk22(RPCParameters *rpcParams) {}
void Unk24(RPCParameters *rpcParams) {}
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
void DisableCheckpoint(RPCParameters *rpcParams)
{
	pGame->m_bCheckpointsEnabled = FALSE;
}
void SetRaceCheckpoint(RPCParameters *rpcParams) {}
void DisableRaceCheckpoint(RPCParameters *rpcParams)
{
	pGame->m_bRaceCheckpointsEnabled = FALSE;
}
void UpdateScoresPingsIPs(RPCParameters *rpcParams) {}
void SvrStats(RPCParameters *rpcParams) {}
void GameModeRestart(RPCParameters *rpcParams)
{
	pNetGame->sub_1000A540();
}
void ConnectionRejected(RPCParameters *rpcParams) {}
void ClientMessage(RPCParameters *rpcParams) {}
void WorldTime(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	BYTE byteWorldTime;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(byteWorldTime);

	pNetGame->SetWorldTime(byteWorldTime);
}
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
void DestroyWeaponPickup(RPCParameters *rpcParams)
{
	PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	BYTE bytePickupIndex;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(bytePickupIndex);

	pNetGame->GetPickupPool()->sub_10013380(bytePickupIndex);
}
void ScmEvent(RPCParameters *rpcParams) {}
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
void WorldPlayerDeath(RPCParameters *rpcParams) {}
void WorldPlayerRemove(RPCParameters *rpcParams) {}
void WorldVehicleAdd(RPCParameters *rpcParams) {}
void WorldVehicleRemove(RPCParameters *rpcParams) {}
void DamageVehicle(RPCParameters *rpcParams) {}
void Unk18(RPCParameters *rpcParams) {}
void EnterVehicle(RPCParameters *rpcParams) {}
void ExitVehicle(RPCParameters *rpcParams) {}
void ServerJoin(RPCParameters *rpcParams) {}
void ServerQuit(RPCParameters *rpcParams) {}
void InitGame(RPCParameters *rpcParams) {}
void Chat(RPCParameters *rpcParams) {}
void RequestClass(RPCParameters *rpcParams) {}
void RequestSpawn(RPCParameters *rpcParams) {}
void EditAttachedObject(RPCParameters *rpcParams) {}
void EditObject(RPCParameters *rpcParams) {}
void SelectObject(RPCParameters *rpcParams) {}
void Unk1C(RPCParameters *rpcParams) {}
void UnkAA(RPCParameters *rpcParams) {}
void ClientCheck(RPCParameters *rpcParams) {}
void UnkAB(RPCParameters *rpcParams) {}
void UnkAC(RPCParameters *rpcParams) {}

//----------------------------------------------------

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
