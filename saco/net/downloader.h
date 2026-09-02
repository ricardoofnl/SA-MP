#pragma once

//----------------------------------------------------

#define MAX_DOWNLOAD_SLOTS 6

//----------------------------------------------------

// one worker slot, 0x230 bytes; offsets pinned by 0x1000C010 and 0x1000C0C0
struct DOWNLOAD_SLOT
{
	DWORD dwSlotId;              // set to the 1-based slot index
	char  field_4;
	char  _gap5;
	char  field_6;               // slot live flag
	char  field_7;               // cancel flag
	DWORD dwThread;              // _beginthread handle, -1 when the spawn failed
	char  szPath[257];
	char  field_10D;
	DWORD field_10E;             // initialised to -1
	BYTE  Request[0x11E];        // the request block AddURLRequest copies in
};

//----------------------------------------------------

class CDownloadManager
{
public:

	char _gap0[0x1344];
	BYTE m_bSlotsReady;
	DOWNLOAD_SLOT m_Slots[MAX_DOWNLOAD_SLOTS];

	void FUNC_1000C0C0(); // .text:1000C0C0
};

//----------------------------------------------------
// EOF
