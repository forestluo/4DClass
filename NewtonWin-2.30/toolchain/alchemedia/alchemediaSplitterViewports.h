/////////////////////////////////////////////////////////////////////////////
// Name:        alchemediaSplitterViewports.h
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

#ifndef __SPLITTER_VIEWPORTS_H__
#define __SPLITTER_VIEWPORTS_H__



class alchemediaView;

class alchemediaSplitterViewports:	public CSplitterWnd
{
public:
	alchemediaSplitterViewports(void);
	virtual ~alchemediaSplitterViewports(void);
	
	void CenterViewPorts();
	const CRowColInfo* GetRowInfoArray() const;
	const CRowColInfo* GetColumInfoArray() const;
	void TrackRowSize(int y, int row);
	void TrackColumnSize(int x, int col);

	void ToggleViewPort(alchemediaView* viewPort);

	float m_splitterPosit_x;
	float m_splitterPosit_y;
	float m_splitterPositSave_x;
	float m_splitterPositSave_y;
	alchemediaView* m_currentMizimazed;
};

#endif