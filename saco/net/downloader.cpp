#include "../main.h"

extern CChatWindow *pChatWindow;
extern CConfig *pConfig;

CDownloadManager *dword_10118A24;

int __stdcall sub_1000C770(DWORD a1, DWORD dwCrc, DWORD a3, DWORD a4); // .text:1000C770

//----------------------------------------------------

// layout locks: every offset below came out of the disassembly, so a wrong one
// fails to compile instead of quietly mismatching
typedef char AssertSlotSize[sizeof(DOWNLOAD_SLOT) == 0x230 ? 1 : -1];
typedef char AssertSlotPath[offsetof(DOWNLOAD_SLOT, szPath) == 0xC ? 1 : -1];
typedef char AssertSlotRequest[offsetof(DOWNLOAD_SLOT, Request) == 0x112 ? 1 : -1];
typedef char AssertRequestSize[sizeof(DOWNLOAD_REQUEST) == 0x11E ? 1 : -1];
typedef char AssertRequestCrc[offsetof(DOWNLOAD_REQUEST, dwCrc) == 0x11 ? 1 : -1];
typedef char AssertReadyFlag[offsetof(CDownloadManager, m_bSlotsReady) == 0x1344 ? 1 : -1];
typedef char AssertSlotArray[offsetof(CDownloadManager, m_Slots) == 0x1345 ? 1 : -1];
typedef char AssertEntryCount[offsetof(CDownloadList, m_dwCount) == 4 ? 1 : -1];
typedef char AssertEntryState[offsetof(DOWNLOAD_ENTRY, field_7) == 7 ? 1 : -1];
typedef char AssertEntryCrc[offsetof(DOWNLOAD_ENTRY, dwCrc) == 0x10 ? 1 : -1];
typedef char AssertEntry46[offsetof(DOWNLOAD_ENTRY, field_46) == 0x46 ? 1 : -1];
typedef char AssertEntry58[offsetof(DOWNLOAD_ENTRY, field_58) == 0x58 ? 1 : -1];

//----------------------------------------------------

// retail spawns the workers on an empty body
void __cdecl DownloadThreadProc(void *pParam)
{
}

//----------------------------------------------------

// spawns a worker for every idle slot and clears its request block
bool CDownloadManager::FUNC_1000C010()
{
	for(int i = 0; i < MAX_DOWNLOAD_SLOTS; i++)
	{
		if(m_Slots[i].field_6)
			continue;

		m_Slots[i].dwThread = _beginthread(DownloadThreadProc, 0, &m_Slots[i]);
		if(m_Slots[i].dwThread == -1)
		{
			m_Slots[i].field_6 = 0;
			m_Slots[i].field_10D = 1;
			m_Slots[i].field_10E = -1;
			return false;
		}

		m_Slots[i].field_10E = -1;
		m_Slots[i].dwSlotId = i + 1;
		m_Slots[i].field_6 = 1;
		m_Slots[i].field_7 = 0;
		m_Slots[i].field_4 = 0;
		m_Slots[i].field_10D = 0;
		memset(m_Slots[i].szPath, 0, sizeof(m_Slots[i].szPath));
		memset(&m_Slots[i].Request, 0, sizeof(m_Slots[i].Request));
	}

	m_bSlotsReady = 1;
	return true;
}

//----------------------------------------------------

bool CDownloadList::FUNC_1000D110(DWORD dwCrc)
{
	for(DWORD i = 0; i != m_dwCount; i++)
	{
		DOWNLOAD_ENTRY *pEntry = GetAt(i);
		if(pEntry->dwCrc == dwCrc && pEntry->field_7 == 1)
			return true;
	}

	return false;
}

//----------------------------------------------------

bool CDownloadList::FUNC_1000D150(DWORD dwCrc)
{
	for(DWORD i = 0; i != m_dwCount; i++)
	{
		DOWNLOAD_ENTRY *pEntry = GetAt(i);
		if(pEntry->dwCrc == dwCrc && pEntry->field_7 == 2)
			return true;
	}

	return false;
}

//----------------------------------------------------

char CDownloadList::FUNC_1000D190(DWORD dwCrc)
{
	for(DWORD i = 0; i != m_dwCount; i++)
	{
		DOWNLOAD_ENTRY *pEntry = GetAt(i);
		if(pEntry->dwCrc == dwCrc)
			return pEntry->field_58;
	}

	return 0;
}

//----------------------------------------------------

// promotes a staged entry once its file checks out; any failed check gives up
// on the whole lookup rather than scanning on
int CDownloadList::FUNC_1000D320(DWORD dwCrc)
{
	for(DWORD i = 0; i != m_dwCount; i++)
	{
		DOWNLOAD_ENTRY *pEntry = GetAt(i);
		if(!pEntry)
			continue;
		if(pEntry->dwCrc != dwCrc || pEntry->field_7 != 2)
			continue;

		if(!pEntry->field_0)
			return 0;
		if(!pEntry->field_1)
			return 0;
		if(!sub_1000C770(pEntry->field_C, pEntry->dwCrc, pEntry->field_46, pEntry->field_4A))
			return 0;

		pEntry->field_59 = 0;
		pEntry->field_58 = 1;
		return 1;
	}

	return 0;
}

//----------------------------------------------------

// parks a request in the first live idle slot; the workers pick it up from there
void CDownloadManager::AddURLRequest(DOWNLOAD_REQUEST *pRequest, char *szUrl)
{
	if(pChatWindow && pConfig && pConfig->GetIntVariable("logurls"))
		pChatWindow->AddInfoMessage("[url 0x%X]: %s", pRequest->dwCrc, szUrl);

	dword_10118A24 = this;

	if(!m_bSlotsReady)
		FUNC_1000C010();

	for(int i = 0; i < MAX_DOWNLOAD_SLOTS; i++)
	{
		if(m_Slots[i].field_6 && !m_Slots[i].field_4)
		{
			memcpy(&m_Slots[i].Request, pRequest, sizeof(DOWNLOAD_REQUEST));
			strncpy(m_Slots[i].szPath, szUrl, sizeof(m_Slots[i].szPath) - 1);
			m_Slots[i].field_4 = 1;
			m_Slots[i].field_5 = 0;
			return;
		}
	}

	if(pChatWindow)
		pChatWindow->AddDebugMessage("[error] AddURLRequest: No free slots!");
}

//----------------------------------------------------

// flags every slot for cancellation and drops the ready bit so the next
// request re-spawns the workers
void CDownloadManager::FUNC_1000C0C0()
{
	for(int i = 0; i < MAX_DOWNLOAD_SLOTS; i++)
		m_Slots[i].field_7 = 1;

	m_bSlotsReady = 0;
}

//----------------------------------------------------
// EOF
