
#include "main.h"
#include "bass.h"

extern CGame	*pGame;
extern CConfig	*pConfig;

// stream state (file scope)
HSTREAM	g_hStream = 0;
volatile BYTE	g_bPlaying = 0;
BYTE	g_bStopRequested = 0;
float	g_fPosX = 0.0f;
float	g_fPosY = 0.0f;
float	g_fPosZ = 0.0f;
float	g_fDistance = 0.0f;
BYTE	g_bIs3D = 0;
char	g_szUrl[257];
char	g_szMeta[257];
char	g_szName[257];
char	g_szUrlInfo[257];

int CAudioStream::Reset()
{
	g_hStream = 0;
	BASS_Free();
	if(BASS_Init(-1, 44100, 0, 0, 0))
	{
		BASS_SetConfigPtr(BASS_CONFIG_NET_AGENT, "SA-MP/0.3");
		BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, (DWORD)(pGame->m_pGameAudio->GetRadioVolume() * 7000.0f));
		BASS_SetConfig(BASS_CONFIG_NET_PLAYLIST, 1);
		BASS_SetConfig(BASS_CONFIG_NET_TIMEOUT, 10000);

		if(!pConfig->IsVariableExist("audioproxyoff"))
			pConfig->SetIntVariable("audioproxyoff", 0, 0);

		if(pConfig->GetIntVariable("audioproxyoff"))
			BASS_SetConfigPtr(BASS_CONFIG_NET_PROXY, 0);

		BASS_SetEAXParameters(-1, 0, -1.0f, -1.0f);
		field_0 = 1;
		return 1;
	}
	return 0;
}

void CAudioStream::Stop()
{
	// TODO: CAudioStream::sub_10066560 10066560
}

void CAudioStream::ConstructInfo()
{
	// TODO: CAudioStream::sub_100665C0 100665C0
}

void CAudioStream::SyncProc()
{
	// TODO: CAudioStream::sub_100666F0 100666F0
}

void CAudioStream::Process()
{
	// TODO: CAudioStream::sub_10066700 10066700
}

void CAudioStream::Play()
{
	// TODO: CAudioStream::sub_10066960 10066960
}

void CAudioStream::ControlGameRadio()
{
	if(field_0 && g_bPlaying)
	{
		pGame->m_pGameAudio->StartRadio(-1);
		pGame->m_pGameAudio->StopRadio();
	}
}

void CAudioStream::DrawInfo()
{
	// TODO: CAudioStream::sub_10066AB0 10066AB0
}