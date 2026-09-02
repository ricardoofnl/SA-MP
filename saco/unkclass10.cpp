
#include "main.h"

extern CGame *pGame;
extern D3DXMATRIX matView, matProj;

CUnkClass10::CUnkClass10(IDirect3DDevice9 *pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	field_7C = 0;
	field_113 = -1;
	field_80 = 0;
	field_84 = 0;
	field_78 = 0;
	field_A3 = 0;
	field_A4 = 0;
	field_A5 = 0;
	field_A6 = 0;
	field_A2 = 0;
	field_88 = -1;
	field_9E = GetTickCount();

	D3DXCreateLine(pD3DDevice, &m_pD3DLine);

	D3DXCreateFont(pD3DDevice, 22, 0, FW_NORMAL, 1, FALSE,
		SYMBOL_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "SAMPAUX3", &m_pD3DFont1);
	D3DXCreateFont(pD3DDevice, 28, 0, FW_NORMAL, 1, FALSE,
		SYMBOL_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "SAMPAUX3", &m_pD3DFont2);
}


float CUnkClass10::FUNC_10071C20(D3DXVECTOR3 *pPos, D3DXVECTOR2 *pOut)
{
	D3DXVECTOR3 In = *pPos;
	D3DVIEWPORT9 Viewport;
	D3DXVECTOR3 Out;
	D3DXMATRIX matIdent;

	m_pD3DDevice->GetViewport(&Viewport);

	D3DXMatrixIdentity(&matIdent);
	D3DXVec3Project(&Out, &In, &Viewport, &matProj, &matView, &matIdent);

	pOut->x = Out.x;
	pOut->y = Out.y;

	return Out.z;
}


// SAMPAUX3 glyph for the marker style in field_7C
PCHAR CUnkClass10::FUNC_10071FA0(int nIndex)
{
	if(nIndex == 0)
	{
		if(field_7C == 0) return "6";
		if(field_7C == 1) return "3";
		if(field_7C == 2) return "9";
	}
	else if(nIndex == 1)
	{
		if(field_7C == 0) return "7";
		if(field_7C == 1) return "4";
		if(field_7C == 2) return "A";
	}
	else if(nIndex == 2)
	{
		if(field_7C == 0) return "8";
		if(field_7C == 1) return "5";
		if(field_7C == 2) return "B";
	}

	return "0";
}


void CUnkClass10::FUNC_100721F0(int nStyle)
{
	if(field_78 == 1 && nStyle == 2)
		nStyle = 0;

	field_7C = nStyle;
}

BOOL CUnkClass10::FUNC_100723C0()
{
	RECT rect;
	GetClientRect(pGame->GetMainWindowHwnd(), &rect);

	field_A7 = (rect.right - rect.left) / 2;
	field_AB = (rect.bottom - rect.top) / 2;

	return SetCursorPos(field_A7, field_AB);
}
