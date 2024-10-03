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

#include "D3DXInputTexture.h"
#include "D3DXStaticTexture.h"
#include "D3DXDynamicTexture.h"

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

//Texture
const LPCTSTR TEXTURE_PROPERTIES[] =
{
	PROPERTY_GENERAL
};

///////////////////////////////////////////////////////////////////////////////
//
// ShowProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ShowProperties(CD3DXTexture* pTexture)
{
#ifdef _DEBUG
	assert(pTexture != NULL);
#endif
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL) pDoc->application->setFocused(pTexture);
	}
	//Set selected property page.
	nSelectedPropertyPage = 0;
	//Set window text.
	SetWindowTextW(pTexture->getName().getCString());

	//Clear property handles.
	ClearHandles();
	//Remove all previous elements.
	m_wndPropList.RemoveAll();
	//Remove all selections.
	m_wndObjectCombo.ResetContent();
	//Add properties.
	for(int i = 0;i < sizeof(TEXTURE_PROPERTIES) / sizeof(LPCTSTR);i ++)
	{
		//Add string.
		m_wndObjectCombo.AddString(TEXTURE_PROPERTIES[i]);
	}
	//Set current selection.
	m_wndObjectCombo.SetCurSel(PROPERTY_GENERAL_SELECTION);

	//Fill properties.
	FillProperties(pTexture);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillProperties(CD3DXTexture* pTexture)
{
#ifdef _DEBUG
	assert(pTexture != NULL);
#endif

	//Create major.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"��Ҫ����");

	//Create property.
	HANDLE_NAME = new CMFCPropertyGridProperty(L"����",
		pTexture->getName().getCString(), L"������ͼ���ڲ����ơ�");
	HANDLE_NAME->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_NAME);

	//Check type.
	if(IS_STATICTEXTURE_BASE(pTexture))
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",
			L"��̬����", L"������ͼ���ڲ�����");
	}
	else if(IS_DYNAMICTEXTURE_BASE(pTexture))
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",
			L"��̬����", L"������ͼ���ڲ�����");
	}
	else
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",
			L"δ֪����", L"������ͼ���ڲ�����");
	}
	HANDLE_TYPE->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_TYPE);

	//Check type.
	if(IS_STATICTEXTURE_BASE(pTexture))
	{
		//Create property.
		HANDLE_FILE_NAME = new CMFCPropertyGridProperty(L"�ļ���",
			((CD3DXStaticTexture *)pTexture)->getFileName().getCString(), L"������ͼ���ļ����ơ�");
		HANDLE_FILE_NAME->Enable(FALSE);
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_FILE_NAME);
	}
	else if(IS_INPUTTEXTURE_BASE(pTexture))
	{
		//Create property.
		HANDLE_SOURCE_NAME = new CMFCPropertyGridProperty(L"����Դ",
			((CD3DXInputTexture *)pTexture)->getSourceName().getCString(), L"ͼ�����ݵ�����Դ���ơ�");
		//Check main frame.
		if(MAINFRAME != NULL)
		{
			//Get doc.
			CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
			//Check result.
			if(pDoc != NULL && pDoc->application != NULL) pDoc->addDeviceOptions(HANDLE_SOURCE_NAME);
		}
		HANDLE_SOURCE_NAME->Enable(FALSE);
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_SOURCE_NAME);
	}

	//Create property.
	HANDLE_REFERENCED_COUNT = new CMFCPropertyGridProperty(L"���ô���",
		(_variant_t) pTexture->countReference(), L"������ͼ���ⲿ���õĴ�����");
	HANDLE_REFERENCED_COUNT->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_REFERENCED_COUNT);

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_TEXTURE_DIMENSION = new CMFCPropertyGridProperty(L"�ߴ�");
	//Set description.
	HANDLE_TEXTURE_DIMENSION->SetDescription(L"������ͼ�Ļ����ߴ硣");

	{
		//Create property.
		HANDLE_TEXTURE_DIMENSION_WIDTH = new CMFCPropertyGridProperty(L"��ȣ����أ�",
			(_variant_t) pTexture->getWidth(), L"������ͼ�Ŀ�ȡ�ע����λΪ���ص㡣");
		//Disable it.
		HANDLE_TEXTURE_DIMENSION_WIDTH->Enable(FALSE);
		//Add subitem.
		HANDLE_TEXTURE_DIMENSION->AddSubItem(HANDLE_TEXTURE_DIMENSION_WIDTH);

		//Create property.
		HANDLE_TEXTURE_DIMENSION_HEIGHT = new CMFCPropertyGridProperty(L"�߶ȣ����أ�",
			(_variant_t) pTexture->getHeight(), L"������ͼ�ĸ߶ȡ�ע����λΪ���ص㡣");
		//Disable it.
		HANDLE_TEXTURE_DIMENSION_HEIGHT->Enable(FALSE);
		//Add subitem.
		HANDLE_TEXTURE_DIMENSION->AddSubItem(HANDLE_TEXTURE_DIMENSION_HEIGHT);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_TEXTURE_DIMENSION);
}
