
// alchemedia.h : main header file for the alchemedia application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// alchemediaApp:
// See alchemedia.cpp for the implementation of this class
//

class alchemediaApp : public CWinAppEx
{
public:
	alchemediaApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern alchemediaApp theApp;
