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

#include "alchemediaStdafx.h"
#include "alchemediaDoc.h"
#include "alchemediaView.h"
#include "alchemediaSplitterViewports.h"



alchemediaSplitterViewports::alchemediaSplitterViewports()
	:CSplitterWnd()
	,m_splitterPosit_x(0.5f)
	,m_splitterPosit_y(0.5f)
	,m_splitterPositSave_x(0.5f)
	,m_splitterPositSave_y(0.5f)
	,m_currentMizimazed(NULL)
{
}

alchemediaSplitterViewports::~alchemediaSplitterViewports()
{

}

const CSplitterWnd::CRowColInfo* alchemediaSplitterViewports::GetColumInfoArray() const
{
	return m_pColInfo;
}
const CSplitterWnd::CRowColInfo* alchemediaSplitterViewports::GetRowInfoArray() const
{
	return m_pRowInfo;
}


void alchemediaSplitterViewports::CenterViewPorts(void)
{
	const CSplitterWnd::CRowColInfo* columnInfoArray = GetColumInfoArray();
	if (columnInfoArray) {
		int width = 0;
		for (int i = 0; i < GetColumnCount(); i ++) {
			width += columnInfoArray[i].nCurSize;
		}
		width = int (width * m_splitterPosit_x);
		for (int i = 0; i < GetColumnCount(); i ++) {
			SetColumnInfo(i, width, 0);
		}
	}
	
	const CSplitterWnd::CRowColInfo* rowInfoArray = GetRowInfoArray();
	if (rowInfoArray) {
		int height = 0;
		for (int i = 0; i < GetRowCount(); i ++) {
			height += rowInfoArray[i].nCurSize;
		}
		height = int (height * m_splitterPosit_y);

		for (int i = 0; i < GetRowCount(); i ++) {
			SetRowInfo(i, height, 0);
		}
	}
	if (rowInfoArray && columnInfoArray) {
		RecalcLayout();
	}
}

void alchemediaSplitterViewports::TrackColumnSize(int x, int col)
{
	//	int width = 0;
	int totalWidth = 0;

	CSplitterWnd::TrackColumnSize(x, col);

	const CSplitterWnd::CRowColInfo* columnInfoArray = GetColumInfoArray();
	for (int i = 0; i < GetColumnCount(); i ++) {
		totalWidth += columnInfoArray[i].nCurSize;
	}
	m_splitterPosit_x = float (x) / float (totalWidth);
}

void alchemediaSplitterViewports::TrackRowSize(int y, int row)
{
	//	int height = 0;
	int totalHeight = 0;

	CSplitterWnd::TrackRowSize(y, row);

	const CSplitterWnd::CRowColInfo* rowInfoArray = GetRowInfoArray();
	for (int i = 0; i < GetRowCount(); i ++) {
		totalHeight += rowInfoArray[i].nCurSize;
	}
	m_splitterPosit_y = float (y) / float (totalHeight);
}


void alchemediaSplitterViewports::ToggleViewPort(alchemediaView* viewPort)
{
	if (!m_currentMizimazed) {
		for (int y = 0; y < GetRowCount(); y ++) {
			for (int x = 0; x < GetColumnCount(); x ++) {
				if (GetPane(y, x) == viewPort) {
					m_currentMizimazed = viewPort;

					m_splitterPositSave_x = m_splitterPosit_x;
					m_splitterPositSave_y = m_splitterPosit_y;
					m_splitterPosit_x = x ? 0.0f : 1.0f;
					m_splitterPosit_y = y ? 0.0f : 1.0f;
					break;
				}
			}
		}
	} else {
		m_splitterPosit_x = m_splitterPositSave_x;
		m_splitterPosit_y = m_splitterPositSave_y;
		m_currentMizimazed = NULL;
		CenterViewPorts();
	}
	CenterViewPorts();
}
