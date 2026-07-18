
#include "main.h"

extern CChatWindow   *pChatWindow;
extern CCmdWindow	 *pCmdWindow;
extern CDeathWindow	 *pDeathWindow;
extern CNetGame		 *pNetGame;
extern GAME_SETTINGS tSettings;
extern CConfig		 *pConfig;

extern bool bShowDebugLabels;
extern bool bHudScaleFix;
extern bool bCameraTargetDebug;

void ShutdownGame(); // .text:100C3E80

void cmdDefaultCmdProc(PCHAR szCmd)
{
	if(pNetGame) {
		CLocalPlayer *pLocalPlayer;
		pLocalPlayer = pNetGame->GetPlayerPool()->GetLocalPlayer();
		pLocalPlayer->Say(szCmd);
	}
}

void cmdTestDeathWindow(PCHAR szCmd)
{
	if(pDeathWindow) {
		pDeathWindow->AddMessage("Pooper","Pooper333",0xFFFFFFFF,0xFFFFFFFF,1);
		pDeathWindow->AddMessage("Pooper","Pooper",0xFFFFFFFF,0xFFFFFFFF,5);
		pDeathWindow->AddMessage("Pooper","Pooper",0xFFFFFFFF,0xFFFFFFFF,15);
		pDeathWindow->AddMessage("Pooper","Pooper",0xFFFFFFFF,0xFFFFFFFF,14);
		pDeathWindow->AddMessage("Pooper","Pooper",0xFFFFFFFF,0xFFFFFFFF,2);
		pDeathWindow->AddMessage(0,"PooperPooperPooper0001",0xFFFFFFFF,0xFFFFFFFF,5);
		pDeathWindow->AddMessage(0,"Pooper",0xFFFFFFFF,0xFFFFFFFF,-1);
		pDeathWindow->AddMessage("Pooper","PooperPooperPooper0001",0xFFFFFFFF,0xFFFFFFFF,0);
	}
}

void cmdCameraTargetDebug(PCHAR szCmd)
{
	bCameraTargetDebug = !bCameraTargetDebug;
}

void cmdPageSize(PCHAR szCmd)
{
	int iPageSize;
	if(strlen(szCmd) && (iPageSize = atoi(szCmd)) >= 10 && iPageSize <= 20)
	{
		if(pChatWindow) pChatWindow->SetPageSize(iPageSize);
		if(pConfig) pConfig->SetIntVariable("pagesize", iPageSize);
	}
	else
	{
		if(pChatWindow) pChatWindow->AddDebugMessage("pagesize [10-20] (lines)");
	}
}

void cmdFontSize(PCHAR szCmd)
{
	// TODO: cmdFontSize .text:10068670
}

void cmdNameTagStatus(PCHAR szCmd)
{
	if(pNetGame) pNetGame->ToggleNameTagStatus();
}

void cmdTimestamp(PCHAR szCmd)
{
	CChatWindow *pChatWindow = ::pChatWindow;
	if(pChatWindow)
	{
		if(pChatWindow->m_bTimestamp)
		{
			pChatWindow->m_bTimestamp = 0;
			pChatWindow->m_bRedraw = 1;
			if(pConfig) pConfig->SetIntVariable("timestamp", 0);
		}
		else
		{
			pChatWindow->m_bTimestamp = 1;
			pChatWindow->m_bRedraw = 1;
			if(pConfig) pConfig->SetIntVariable("timestamp", 1);
		}
	}
}

void cmdAudioMsg(PCHAR szCmd)
{
	// TODO: cmdAudioMsg .text:10068790
}

void cmdLogUrls(PCHAR szCmd)
{
	// TODO: cmdLogUrls .text:10068800
}

void cmdHudScaleFix(PCHAR szCmd)
{
	if(bHudScaleFix)
	{
		bHudScaleFix = false;
		pConfig->SetIntVariable("nohudscalefix", 1);
	}
	else
	{
		bHudScaleFix = true;
		pConfig->SetIntVariable("nohudscalefix", 0);
	}
}

//----------------------------------------------------

void cmdMem(PCHAR szCmd)
{
	pChatWindow->AddDebugMessage("Memory: %u",*(DWORD *)0x8A5A80);
}

void cmdSetFrameLimit(PCHAR szCmd)
{
	// TODO: cmdSetFrameLimit .text:100688D0
}

void cmdHeadMove(PCHAR szCmd)
{
	// TODO: cmdSetFrameLimit .text:10068960
}

void cmdQuit(PCHAR szCmd)
{
	ShutdownGame();
}

void cmdCmpStat(PCHAR szCmd)
{
	// TODO: cmdCmpStat .text:100689F0
}

void cmdSavePos(PCHAR szCmd)
{
	// TODO: cmdSavePos .text:10068A00
}

void cmdRawSavePos(PCHAR szCmd)
{
	// TODO: cmdRawSavePos .text:10068B80
}

void cmdPlayerSkin(PCHAR szCmd)
{
	// TODO: cmdPlayerSkin .text:10068D00
}

void cmdCreateVehicle(PCHAR szCmd)
{
	// TODO: cmdCreateVehicle .text:10068D70
}

void cmdSelectVehicle(PCHAR szCmd)
{
	// TODO: cmdSelectVehicle .text:10068EB0
}

void cmdSetWeather(PCHAR szCmd)
{
	// TODO: cmdSetWeather .text:10068ED0
}

void cmdSetTime(PCHAR szCmd)
{
	// TODO: cmdSetTime .text:10068F20
}

void cmdShowInterior(PCHAR szCmd)
{
	// TODO: cmdShowInterior .text:10068FD0
}

void cmdToggleObjectLight(PCHAR szCmd)
{
	// TODO: cmdToggleObjectLight .text:10069000
}

void cmdDebugLabels(PCHAR szCmd)
{
	bShowDebugLabels = !bShowDebugLabels;
}

void cmdRcon(PCHAR szCmd)
{
	// TODO: cmdRcon .text:10069030
}

//----------------------------------------------------

void SetupCommands()
{
	// RELEASE COMMANDS
	pCmdWindow->AddDefaultCmdProc(cmdDefaultCmdProc);
	pCmdWindow->AddCmdProc("quit",cmdQuit);
	pCmdWindow->AddCmdProc("q",cmdQuit);
	pCmdWindow->AddCmdProc("save",cmdSavePos);
	pCmdWindow->AddCmdProc("rs",cmdRawSavePos);
	pCmdWindow->AddCmdProc("rcon",cmdRcon);
	pCmdWindow->AddCmdProc("mem",cmdMem);
	pCmdWindow->AddCmdProc("fpslimit",cmdSetFrameLimit);
	pCmdWindow->AddCmdProc("pagesize",cmdPageSize);
	pCmdWindow->AddCmdProc("fontsize",cmdFontSize);
	pCmdWindow->AddCmdProc("nametagstatus",cmdNameTagStatus);
	pCmdWindow->AddCmdProc("timestamp",cmdTimestamp);
	pCmdWindow->AddCmdProc("headmove",cmdHeadMove);
	pCmdWindow->AddCmdProc("hudscalefix",cmdHudScaleFix);
	pCmdWindow->AddCmdProc("testdw",cmdTestDeathWindow);

#ifndef _DEBUG
	if(tSettings.bDebug)
	{
#endif
	pCmdWindow->AddCmdProc("vsel",cmdSelectVehicle);
	pCmdWindow->AddCmdProc("v",cmdCreateVehicle);
	pCmdWindow->AddCmdProc("vehicle",cmdCreateVehicle);
	pCmdWindow->AddCmdProc("player_skin",cmdPlayerSkin);
	pCmdWindow->AddCmdProc("set_weather",cmdSetWeather);
	pCmdWindow->AddCmdProc("set_time",cmdSetTime);
#ifndef _DEBUG
	}
#endif

	pCmdWindow->AddCmdProc("interior",cmdShowInterior);
	pCmdWindow->AddCmdProc("togobjlight",cmdToggleObjectLight);
	pCmdWindow->AddCmdProc("cmpstat",cmdCmpStat);
	pCmdWindow->AddCmdProc("dl",cmdDebugLabels);
	pCmdWindow->AddCmdProc("ctd",cmdCameraTargetDebug);
	pCmdWindow->AddCmdProc("audiomsg",cmdAudioMsg);
	pCmdWindow->AddCmdProc("logurls",cmdLogUrls);
}

//----------------------------------------------------
