/////////////////////////////////////////////////////////////////////////////
// Name:       alchemediaViewerToolBar.h
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


#ifndef __ALCHEMEDIA_VIEWER_TOOBAR_H__
#define __ALCHEMEDIA_VIEWER_TOOBAR_H__


// alchemediaViewerToolBar
class alchemediaView;

class alchemediaViewerToolBar : public CMFCToolBar
{
	DECLARE_DYNAMIC(alchemediaViewerToolBar)

public:
	alchemediaViewerToolBar();
	virtual ~alchemediaViewerToolBar();

	void CreateListBox(CComboBox& CComboBox , UINT index, UINT id, int width, int height);


protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

public:

	CComboBox m_axisSystem;
	CComboBox m_renderMode;
	CComboBox m_projectionModes;
	alchemediaView* m_viewPort;
	
};

#endif
