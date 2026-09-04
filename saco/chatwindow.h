
#pragma once

#define MAX_MESSAGES				100


#pragma pack(1)
typedef struct _CHAT_WINDOW_ENTRY
{
	char _gap0[252];
} CHAT_WINDOW_ENTRY;

class CChatWindow // size: 25578
{
public:

	int field_0;
	char _gap4[4];
	int field_8;
	char m_bTimestamp;
	int field_D;
	char field_11[261];
	CDXUTDialog			*m_pGameUI;
	int field_11A;
	CDXUTScrollBar		*m_pScrollBar;
	DWORD				m_dwChatTextColor;
	DWORD				m_dwChatInfoColor;
	DWORD				m_dwChatDebugColor;
	int field_12E;
	CHAT_WINDOW_ENTRY	m_ChatWindowEntries[MAX_MESSAGES];
	CFontRender			*m_pFontRender;
	ID3DXSprite			*field_63A6;
	ID3DXSprite			*field_63AA;
	IDirect3DDevice9	*m_pD3DDevice;
	int field_63B2;
	ID3DXRenderToSurface *field_63B6;
	IDirect3DTexture9* field_63BA;
	IDirect3DSurface9 *field_63BE;
	D3DDISPLAYMODE field_63C2;
	DWORD field_63D2;
	int field_63D6;
	int m_bRedraw;
	int field_63DE;
	int field_63E2;
	char _gap63E6[4];


	void CreateFonts(); // .text:100681D0

	int FUNC_10067120();

	void FUNC_10067200();

	void ReplaceControlChars(char *szString); // .text:10067420

	void FUNC_10067E00(); // .text:10067E00

	void FUNC_10067ED0(); // .text:10067ED0

public:

	int sub_10067BE0(int a1, char *a2, int a3, int a4, int a5); // .text:10067BE0

	void AddChatMessage(PCHAR szName, DWORD dwColor, PCHAR szText); // .text:10068020

	int AddDebugMessage(CHAR *szFormat, ...);

	int FUNC_10068020(char *szName, int iColor, char *szText); // .text:10068020

	void AddInfoMessage(CHAR *szFormat, ...); // .text:10068070

	void AddClientMessage(DWORD dwColor, CHAR *szMessage); // .text:10068170

	void SetPageSize(int iPageSize); // .text:100672A0

	void ResetDialogControls(CDXUTDialog *pGameUI);

	CChatWindow(IDirect3DDevice9 *pD3DDevice, CFontRender *pFontRender, CHAR *szChatLogFile);
};
