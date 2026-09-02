#include "../main.h"

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
