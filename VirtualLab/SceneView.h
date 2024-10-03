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
#include "WorldObject.h"

class CClassToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CSceneView : public CDockablePane
{
public:
	CSceneView();
	virtual ~CSceneView();

	void AdjustLayout();
	void OnChangeVisualStyle();

	///////////////////////////////////////
	//
	//Update scene view.
	void UpdateSceneView();
	//
	///////////////////////////////////////

protected:
	CClassToolBar m_wndToolBar;
	CViewTree m_wndSceneView;
	CImageList m_SceneViewImages;
	UINT m_nCurrSort;

	//Fill scene view.
	void FillSceneView();
	///////////////////////////////////////
	//
	//Fill environment.
	void FillEnvironment();
	//File light.
	void FillLight(HTREEITEM hRootItem);
	//Fill view port.
	void FillViewport(HTREEITEM hRootItem);
	//Fill background.
	void FillBackground(HTREEITEM hRootItem);
	//
	//Fill foreground.
	void FillForeground();
	void FillForeground(CWorldObject* object,HTREEITEM hRootItem);
	//
	///////////////////////////////////////

// Overrides
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnNewFolder();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()

	///////////////////////////////////////
	//
	//OnNotify
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//
	///////////////////////////////////////
};

