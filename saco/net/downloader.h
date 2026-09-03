#pragma once

//----------------------------------------------------

#define MAX_DOWNLOAD_SLOTS 6

//----------------------------------------------------

// the block AddURLRequest copies into a slot, 0x11E bytes
struct DOWNLOAD_REQUEST
{
	char  _gap0[0x11];
	DWORD dwCrc;
	char  _gap15[0x109];
};

//----------------------------------------------------

// one worker slot, 0x230 bytes; offsets pinned by 0x1000C010 and 0x1000C0C0
struct DOWNLOAD_SLOT
{
	DWORD dwSlotId;              // set to the 1-based slot index
	char  field_4;
	char  field_5;
	char  field_6;               // slot live flag
	char  field_7;               // cancel flag
	DWORD dwThread;              // _beginthread handle, -1 when the spawn failed
	char  szPath[257];
	char  field_10D;
	DWORD field_10E;             // initialised to -1
	DOWNLOAD_REQUEST Request;
};

//----------------------------------------------------

class CDownloadManager
{
public:

	char _gap0[0x1344];
	BYTE m_bSlotsReady;
	DOWNLOAD_SLOT m_Slots[MAX_DOWNLOAD_SLOTS];

	bool FUNC_1000C010(); // .text:1000C010
	void AddURLRequest(DOWNLOAD_REQUEST *pRequest, char *szUrl); // .text:1000C380
	void FUNC_1000C0C0(); // .text:1000C0C0
};

//----------------------------------------------------
// EOF
