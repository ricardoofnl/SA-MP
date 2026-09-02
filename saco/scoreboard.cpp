
#include "main.h"

extern CGame* pGame;
extern CNetGame *pNetGame;

CScoreBoard::CScoreBoard(IDirect3DDevice9 *pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	m_pDialog = NULL;
	m_pListBox = NULL;
	field_3C = 0;
	field_40 = 0;
	field_4 = 0;

	if(pGame && pGame->GetScreenWidth() > 800)
	{
		field_14 = 800.0f;
		field_18 = 600.0f;
	}
	else
	{
		field_14 = 640.0f;
		field_18 = 480.0f;
	}
	field_1C = 60.0f;
	field_20 = 0;
	field_24 = 0.085f;
	field_28 = 0.265625f;
	field_2C = 0.437500f;

	FUNC_1006E930();

	field_0 = 0;
}

void CScoreBoard::FUNC_1006E930()
{
	RECT rect;

	GetClientRect(pGame->GetMainWindowHwnd(),&rect);

	field_10 = 1.0f;
	field_8 = rect.right * 0.5f - field_14 * 0.5f;
	field_C = rect.bottom * 0.5f - field_18 * 0.5f;
}

void CScoreBoard::ResetDialogControls(CDXUTDialog *pDialog)
{
	m_pDialog = pDialog;

	if(pDialog) {
		pDialog->SetSize(field_14, field_18);

		m_pListBox = new CDXUTListBox(m_pDialog);
		m_pDialog->AddControl(m_pListBox);
		m_pListBox->SetLocation(0, field_1C);
		m_pListBox->SetSize(field_14, field_18 - field_1C);
		m_pListBox->OnInit();
		m_pListBox->GetElement(0)->TextureColor.Init(D3DCOLOR_ARGB( 200, 255, 255, 255 ));
		m_pListBox->field_4D = 3;
		m_pListBox->field_51[0] = field_24 * field_14;
		m_pListBox->field_51[2] = field_28 * field_14;
		m_pListBox->field_51[1] = field_2C * field_14;
		m_pListBox->SetEnabled(false);
		m_pListBox->SetVisible(false);

		FUNC_1006E930();
	}
}

void CScoreBoard::GetRect(RECT *pRect)
{
	pRect->left = (int)field_8;
	pRect->right = pRect->left + (int)field_14;
	pRect->top = (int)field_C;
	pRect->bottom = pRect->top + (int)field_18;
}

void CScoreBoard::Hide(bool bResetInput)
{
	if(!field_0) return;
	if(!m_pDialog) return;

	m_pDialog->SetVisible(false);
	m_pListBox->SetEnabled(false);
	m_pListBox->SetVisible(false);

	if(bResetInput)
		pGame->ToggleKeyInputsDisabled(0, FALSE);

	field_0 = 0;
}

// stub: rebuilds the three player columns from the pool, not reconstructed yet
void CScoreBoard::FUNC_1006ED30()
{
}

void CScoreBoard::Show()
{
	if(field_0) return;
	if(!m_pDialog) return;

	m_pDialog->SetVisible(true);
	m_pListBox->SetEnabled(true);
	m_pListBox->UpdateRects();
	m_pListBox->SetVisible(true);

	FUNC_1006ED30();
	pGame->ToggleKeyInputsDisabled(3, FALSE);

	field_0 = 1;
}

void CScoreBoard::ClickPlayer()
{
	if(!field_0) return;
	if(!m_pDialog) return;

	DXUTListBoxItem *pItem = m_pListBox->GetSelectedItem();
	if(pItem)
	{
		PLAYERID playerId = (PLAYERID)atoi(pItem->strText);
		RakNet::BitStream bsSend;
		bsSend.Write(playerId);
		bsSend.Write((BYTE)0);
		pNetGame->GetRakClient()->RPC(RPC_ClickPlayer, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE);
	}

	if(!field_0) return;
	if(!m_pDialog) return;

	m_pDialog->SetVisible(false);
	m_pListBox->SetEnabled(false);
	m_pListBox->SetVisible(false);
	pGame->ToggleKeyInputsDisabled(0, FALSE);

	field_0 = 0;
}
