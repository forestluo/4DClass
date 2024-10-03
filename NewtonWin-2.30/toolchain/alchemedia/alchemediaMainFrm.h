/////////////////////////////////////////////////////////////////////////////
// Name:        alchemediaMainFrame.h
// Purpose:     
// Author:      Julio Jerez
// Modified by: 
// Created:     22/05/2010 08:02:08
// RCS-ID:      
// Copyright:   Copyright (c) <2010> <Newton Game Dynamics>
// License:     
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely
/////////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__


#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "alchemediaExplorerView.h"
#include "alchemediaSplitterViewports.h"

class alchemediaDoc;
class alchemediaView;

class alchemediaMainFrame : public CFrameWndEx
{
	protected: 

	class alchemdiaPluginDlls: public dList <HMODULE>
	{
	};


	alchemediaMainFrame();
	DECLARE_DYNCREATE(alchemediaMainFrame)

	public:
	virtual ~alchemediaMainFrame();
	virtual BOOL DestroyWindow();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	alchemediaSplitterViewports& GetSplitter();


	// Generated message map functions
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	afx_msg void OnImport(UINT nID);
	afx_msg void OnExport(UINT nID);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons();
	void CenterViewPorts(void);
	void RegisterAllPlugins(void);


	CMFCMenuBar m_mainMenuBar;
	CMFCToolBar m_mainToolbar;
	CMFCStatusBar m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	
	CClassView m_wndClassView;
	COutputWnd m_wndOutput;
	CPropertiesWnd m_wndProperties;

	alchemediaDoc* m_document;
	alchemediaView*	m_viewPort0;
	alchemediaView*	m_viewPort1;
	alchemediaView* m_viewPort2;
	alchemediaView* m_viewPort3;
	alchemediaExplorerView m_explorer;
	alchemediaSplitterViewports m_viewportSplitter;
	
	int m_importPluginCount;
	int m_exportPluginsCount;
	dImportPlugin** m_importPlugins;
	dExportPlugin** m_exportPlugins;
	alchemdiaPluginDlls m_allPlugins;

	
};


#endif