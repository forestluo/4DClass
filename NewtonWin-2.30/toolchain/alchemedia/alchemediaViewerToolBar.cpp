/////////////////////////////////////////////////////////////////////////////
// Name:        alchemediaViewerToolBar.cpp
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

// alchemediaViewerToolBar.cpp : implementation file
//


#include "alchemediaStdafx.h"
#include "alchemedia.h"
#include "alchemediaViewerToolBar.h"


// alchemediaViewerToolBar

IMPLEMENT_DYNAMIC(alchemediaViewerToolBar, CMFCToolBar)

alchemediaViewerToolBar::alchemediaViewerToolBar()
	: m_viewPort(NULL)
{

}

alchemediaViewerToolBar::~alchemediaViewerToolBar()
{
}


BEGIN_MESSAGE_MAP(alchemediaViewerToolBar, CMFCToolBar)
END_MESSAGE_MAP()



void alchemediaViewerToolBar::CreateListBox(CComboBox& control, UINT nIndex, UINT id, int width, int height)
{
	// Create the combo box
	SetButtonInfo(nIndex, id, TBBS_SEPARATOR, width);

	CRect rect;
	GetItemRect(nIndex, &rect);
	//rect.top = 1;
	rect.bottom += height;
	//BOOL state = control.Create(CBS_DROPDOWN|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL, rect, this, id);
	BOOL state = control.Create(CBS_DROPDOWNLIST|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL, rect, this, id);
 
	_ASSERTE (state);
}


BOOL alchemediaViewerToolBar::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
_ASSERTE (0);
/*	
	int id = LOWORD(wParam);

	if( id == ID_VIEWERMENU_PROJECTION) {
		int notify = HIWORD(wParam);
		if (notify == CBN_SELCHANGE) {
			int index = m_projectionModes.GetCurSel();
			dCameraNodeInfo::ProjectionModes mode = dCameraNodeInfo::ProjectionModes (m_projectionModes.GetItemData(index));
			m_viewPort->SetProjectionMode (mode);
		}
	}

	if( id == ID_VIEWERMENU_RENDER){
		int notify = HIWORD(wParam);
		if (notify == CBN_SELCHANGE) {
			int index = m_renderMode.GetCurSel();
			alchemediaView::RenderMode mode = alchemediaView::RenderMode (m_renderMode.GetItemData(index));
			m_viewPort->SetRenderMode (mode);
		}
	}


	if( id == ID_VIEWERMENU_AXISSYSTEM){
		int notify = HIWORD(wParam);
		if (notify == CBN_SELCHANGE) {
			int index = m_axisSystem.GetCurSel();
			alchemediaView::AxisSystemMode mode = alchemediaView::AxisSystemMode (m_axisSystem.GetItemData(index));
			m_viewPort->SetRenderModeAxisSystemMode (mode);
		}
	}
*/
	return CMFCToolBar::OnCommand(wParam, lParam);
}

