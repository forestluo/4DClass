// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "ViewPort.h"
#include "SceneView.h"
#include "ResourceView.h"
#include "PropertiesWnd.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	////////////////////////////////////////
	//
	//Enable properties.
	void EnableProperties(BOOL bEnable);
	//
	//Update scene view.
	void UpdateSceneView();
	//Update resource view.
	void UpdateResourceView();
	//Update property view.
	void UpdatePropertyView();
	//
	//Show properties.
	void ShowProperties(CViewPort* pViewPort);
	//Show properties.
	void ShowProperties(CD3DXResource* pResource);
	//Show properties.
	void ShowProperties(CD3DXRenderableObject* pRenderableObject);
	//
	////////////////////////////////////////

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	
	////////////////////////////////////////
	//
	//View of scene.
	CSceneView        m_wndSceneView;
	//Properties of object.
	CPropertiesWnd    m_wndProperties;
	//View of resource.
	CResourceView     m_wndResourceView;
	//
	////////////////////////////////////////

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
};


