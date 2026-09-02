
#pragma once

#include <string>

//----------------------------------------------------

class CNetPlayer
{
public:
	//char			_gap0[48];
	char			_gap0[4];
	int				field_4;
	BOOL			m_bIsNPC;
	int				field_C;
	CRemotePlayer	*m_pRemotePlayer;
	std::string		m_PlayerName;

	void SetPlayerName(PCHAR szName) { m_PlayerName = szName; };

	CNetPlayer(PCHAR szPlayerName, BOOL bIsNPC);
	~CNetPlayer();
};

//----------------------------------------------------
