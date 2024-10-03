/////////////////////////////////////////////////////////////////////////////
// Name:        alchemediaView.h
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

// alchemediaView.h : interface of the alchemediaView class
//


#ifndef __ALCHEMEDIA_VIEWPORT_H__
#define __ALCHEMEDIA_VIEWPORT_H__

#include "alchemediaViewerToolBar.h"
#include "alchemediaCamera.h"

class alchemediaView : public CView
{
	// Attributes
public:

	enum alchemdiaRenderMode
	{
		m_wireframe,
		m_hiddenline,
		m_gouraud,
		m_shaded,
	};


	virtual ~alchemediaView();
	alchemediaDoc* GetDocument() const;
	
	void SetDefaultLight(void);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected: // create from serialization only
	alchemediaView();
	DECLARE_DYNCREATE(alchemediaView)

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	private:
	void InitGraphicsSystem(void);
	bool SelectPixelFormat(void);

//	CClientDC* m_deviceContext;
	HGLRC m_renderContext;
	CRect m_oldRect;

	int m_myCameraIndex;
	alchemdiaRenderMode m_renderMode;
	alchemediaCamera::ProjectionModes m_viewMode;

	alchemediaMainFrame* m_mainFrame;
	alchemediaViewerToolBar m_toolBar;
	
	friend class alchemediaMainFrame;

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewermenuMaximize();
	
	afx_msg void OnViewermenuSelect();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in alchemediaView.cpp
inline alchemediaDoc* alchemediaView::GetDocument() const
   { return reinterpret_cast<alchemediaDoc*>(m_pDocument); }
#endif


#endif