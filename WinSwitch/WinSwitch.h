
// WinSwitch.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#define MY_WNDCLS_NAME _T("WinSwitchWndClass")

#define ADD_ITEM_TO_WINDOW_LIST (WM_APP + 0)
#define WM_SYSTRAYNOTIFY (WM_APP + 1)

// CWinSwitchApp:
// See WinSwitch.cpp for the implementation of this class
//

class CWinSwitchApp : public CWinApp
{
public:
	CWinSwitchApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWinSwitchApp theApp;