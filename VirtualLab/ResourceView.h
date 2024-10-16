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

#pragma once

#include "ViewTree.h"

class CResourceViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CResourceView : public CDockablePane
{
// Construction
public:
	CResourceView();

	void AdjustLayout();
	void OnChangeVisualStyle();

	//Update source view.
	void UpdateResourceView();

// Attributes
protected:

	CViewTree m_wndResourceView;
	CImageList m_ResourceViewImages;
	CResourceViewToolBar m_wndToolBar;

protected:

	//Fill resource view.
	void FillResourceView();
	///////////////////////////////////////
	//
	//Fill devices.
	void FillDevices();
	//
	//File filters.
	void FillFilters();
	//
	//Fill effect files.
	void FillEffectFiles();
	//
	//Fill texture files.
	void FillTextureFiles();
	//
	//Fill renderable files.
	void FillRenderableFiles();
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	void FillDeviceItems(HTREEITEM hRoot);
	//
	///////////////////////////////////////

// Implementation
public:
	virtual ~CResourceView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

