/////////////////////////////////////////////////////////////////////////////
// Name:        alchemediaExplorerView.h
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

#ifndef __ALCHEMEDIA_EXPLORER_VIEW_H__
#define __ALCHEMEDIA_EXPLORER_VIEW_H__

#include "ViewTree.h"

class alchemediaScene;


class alchemediaExplorerView : public CDockablePane
{
// Construction
public:

	class alchemediaExplorerToolBar : public CMFCToolBar
	{
		virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
		{
			CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
		}

		virtual BOOL AllowShowOnList() const { return FALSE; }
	};


	alchemediaExplorerView();

	void AdjustLayout();
	void OnChangeVisualStyle();

	void PopulateScene(alchemediaScene* scene);

// Attributes
protected:

	CViewTree m_explorer;
	CImageList m_iconList;
	alchemediaExplorerToolBar m_toolBar;

protected:
	void FillFileView();

// Implementation
public:
	virtual ~alchemediaExplorerView();

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

#endif