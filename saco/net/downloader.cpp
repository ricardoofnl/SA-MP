#include "../main.h"

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
		memset(m_Slots[i].Request, 0, sizeof(m_Slots[i].Request));
	}

	m_bSlotsReady = 1;
	return true;
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
