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

#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "4DProperties.h"
#include "VirtualLabDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
///////////////////////////////////////////////////////////////////////////////

#define MAINFRAME											((CMainFrame *)GetTopLevelFrame())

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

const LPCTSTR LINESTRIP_PROPERTIES[] =
{
	PROPERTY_GENERAL,
};

///////////////////////////////////////////////////////////////////////////////
//
// ShowProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ShowProperties(CD3DXLinestrip* pLinestrip)
{
#ifdef _DEBUG
	assert(pLinestrip != NULL);
#endif
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL) pDoc->application->setFocused(pLinestrip);
	}
	//Set selected property page.
	nSelectedPropertyPage = 0;
	//Set window text.
	SetWindowTextW(pLinestrip->getName().getCString());

	//Clear property handles.
	ClearHandles();
	//Remove all previous elements.
	m_wndPropList.RemoveAll();
	//Remove all selections.
	m_wndObjectCombo.ResetContent();
	//Add properties.
	for(int i = 0;i < sizeof(LINESTRIP_PROPERTIES) / sizeof(LPCTSTR);i ++)
	{
		//Add string.
		m_wndObjectCombo.AddString(LINESTRIP_PROPERTIES[i]);
	}
	//Set current selection.
	m_wndObjectCombo.SetCurSel(PROPERTY_GENERAL_SELECTION);
	//Fill properties.
	FillProperties(pLinestrip);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillProperties(CD3DXLinestrip* pLinestrip)
{
#ifdef _DEBUG
	assert(pLinestrip != NULL);
#endif

	//Create property.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"常规");

	//Create property.
	HANDLE_NAME = new CMFCPropertyGridProperty(L"名称",
		pLinestrip->getName().getCString(), L"线框对象的内部名称。");
	HANDLE_NAME->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_NAME);

	//Create property.
	HANDLE_TYPE = new CMFCPropertyGridProperty(L"类型",
		L"线框", L"线框对象的内部类型。");
	HANDLE_TYPE->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_TYPE);

	//Create property.
	HANDLE_REFERENCED_COUNT = new CMFCPropertyGridProperty(L"被引用次数",
		(_variant_t) pLinestrip->countReference(), L"线框对象被引用的次数。");
	HANDLE_REFERENCED_COUNT->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_REFERENCED_COUNT);

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Fill box properties.
	FillBoxProperties(pLinestrip);
}