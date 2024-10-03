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
#include "SDKMesh.h"
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

const LPCTSTR FILEMESH_PROPERTIES[] =
{
	PROPERTY_GENERAL,
	PROPERTY_FENCE,
};

///////////////////////////////////////////////////////////////////////////////
//
// ShowProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ShowProperties(CD3DXFileMesh* pFileMesh)
{
#ifdef _DEBUG
	assert(pFileMesh != NULL);
#endif
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL) pDoc->application->setFocused(pFileMesh);
	}

	//Set selected property page.
	nSelectedPropertyPage = 0;
	//Set window text.
	SetWindowTextW(pFileMesh->getName().getCString());

	//Clear property handles.
	ClearHandles();
	//Remove all previous elements.
	m_wndPropList.RemoveAll();

	//Remove all selections.
	m_wndObjectCombo.ResetContent();
	//Add string.
	m_wndObjectCombo.AddString(FILEMESH_PROPERTIES[0]);
	//Set current selection.
	m_wndObjectCombo.SetCurSel(PROPERTY_GENERAL_SELECTION);
	//Add properties.
	for(int i = 1;i < sizeof(FILEMESH_PROPERTIES) / sizeof(LPCTSTR);i ++)
	{
		//Add string.
		m_wndObjectCombo.AddString(FILEMESH_PROPERTIES[i]);
	}
	//Fill properties.
	FillProperties(pFileMesh);
}

///////////////////////////////////////////////////////////////////////////////
//
// ChangePropertyPage
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ChangePropertyPage(CD3DXFileMesh* pFileMesh,int nSelected)
{
#ifdef _DEBUG
	assert(pFileMesh != NULL);
#endif

	//Clear property handles.
	ClearHandles();
	//Remove all previous elements.
	m_wndPropList.RemoveAll();
	//Check selected.
	if(nSelected == PROPERTY_GENERAL_SELECTION)
	{
		//Fill properties.
		FillProperties(pFileMesh);
	}
	else if(nSelected == PROPERTY_FENCE_SELECTION)
	{
		//Fill box properties.
		FillBoxProperties(pFileMesh);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// FillProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillProperties(CD3DXFileMesh* pFileMesh)
{
#ifdef _DEBUG
	assert(pFileMesh != NULL);
#endif

	//Create property.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"����");
	//Set descriptino.
	HANDLE_GROUP_MAJOR->SetDescription(L"�����ļ�������Ϣ��");

	//Create property.
	HANDLE_NAME = new CMFCPropertyGridProperty(L"����",
		pFileMesh->getName().getCString(), L"�����ļ����ڲ����ơ�");
	HANDLE_NAME->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_NAME);

	//Create property.
	HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",
		L"�����ļ�", L"�����ļ����ڲ����͡�");
	HANDLE_TYPE->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_TYPE);

	//Create property.
	HANDLE_FILE_NAME = new CMFCPropertyGridProperty(L"�ļ���",
		pFileMesh->getFileName().getCString(), L"�����ļ���ԭʼ�ļ�����");
	HANDLE_FILE_NAME->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_FILE_NAME);

	//Create property.
	HANDLE_REFERENCED_COUNT = new CMFCPropertyGridProperty(L"�����ô���",
		(_variant_t) pFileMesh->countReference(), L"�����ļ��������õĴ�����");
	HANDLE_REFERENCED_COUNT->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_REFERENCED_COUNT);

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Get mesh.
	CDXUTXFileMesh* pMesh = (CDXUTXFileMesh *)pFileMesh->getMesh();
#ifdef _DEBUG
	assert(pMesh != NULL);
#endif

	//Create property.
	HANDLE_GROUP_PARAMETER = new CMFCPropertyGridProperty(L"����");
	//Set descriptino.
	HANDLE_GROUP_PARAMETER->SetDescription(L"�����ļ���ز�����Ϣ��");

	//Basic
	{
		//Create property.
		HANDLE_MESH_BASIC = new CMFCPropertyGridProperty(L"����");
		//Set descriptino.
		HANDLE_MESH_BASIC->SetDescription(L"��ʾ�������ļ���������Ļ�����Ϣ��");
		//Add subitem.
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_MESH_BASIC);

		//Create property.
		HANDLE_MESH_BASIC_VERTEX_COUNT = new CMFCPropertyGridProperty(L"������",
			(_variant_t) pMesh->m_dwNumVertices, L"�������ļ��У�������Ķ��������");
		HANDLE_MESH_BASIC_VERTEX_COUNT->Enable(FALSE);
		HANDLE_MESH_BASIC->AddSubItem(HANDLE_MESH_BASIC_VERTEX_COUNT);

		//Create property.
		HANDLE_MESH_BASIC_TRIANGLE_COUNT = new CMFCPropertyGridProperty(L"����Ƭ��",
			(_variant_t) pMesh->m_dwNumFaces, L"�������ļ��У�������������θ�����");
		HANDLE_MESH_BASIC_TRIANGLE_COUNT->Enable(FALSE);
		HANDLE_MESH_BASIC->AddSubItem(HANDLE_MESH_BASIC_TRIANGLE_COUNT);

		//Create property.
		HANDLE_MESH_BASIC_VERTEX_SIZE = new CMFCPropertyGridProperty(L"�����ֽ���",
			(_variant_t) pMesh->m_dwBytesPerVertex, L"�������ļ��У�������������ռ�����������ֽڣ���");
		HANDLE_MESH_BASIC_VERTEX_SIZE->Enable(FALSE);
		HANDLE_MESH_BASIC->AddSubItem(HANDLE_MESH_BASIC_VERTEX_SIZE);

		//Expand all.
		HANDLE_MESH_BASIC->Expand(TRUE);
	}	
	//Material
	{
		//Create property.
		HANDLE_MESH_MATERIAL = new CMFCPropertyGridProperty(L"����");
		//Set descriptino.
		HANDLE_MESH_MATERIAL->SetDescription(L"��ʾ�������ļ���������Ĳ�����Ϣ��");
		//Add subitem.
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_MESH_MATERIAL);

		//Create property.
		HANDLE_MESH_MATERIAL_ENABLED = new CMFCPropertyGridProperty(L"����",
			(_variant_t) pMesh->m_bUseMaterials, L"�������ļ��У��Ƿ񱣴��в����ļ���");
		HANDLE_MESH_MATERIAL_ENABLED->Enable(FALSE);
		HANDLE_MESH_MATERIAL->AddSubItem(HANDLE_MESH_MATERIAL_ENABLED);

		//Create property.
		HANDLE_MESH_MATERIAL_COUNT = new CMFCPropertyGridProperty(L"�ļ���",
			(_variant_t) pMesh->m_dwNumMaterials, L"�������ļ��У�������Ĳ����ļ�����");
		HANDLE_MESH_MATERIAL_COUNT->Enable(FALSE);
		HANDLE_MESH_MATERIAL->AddSubItem(HANDLE_MESH_MATERIAL_COUNT);

		//Do while.
		for(UINT i = 0;i < pMesh->m_dwNumMaterials;i ++)
		{
			//Create property.
			CMFCPropertyGridProperty* pProperty = new CMFCPropertyGridProperty(L"�ļ���",
				CString(pMesh->m_strMaterials[i]), L"�������ļ��У�������Ĳ����ļ�����");
			pProperty->Enable(FALSE);
			HANDLE_MESH_MATERIAL->AddSubItem(pProperty);
		}

		//Expand all.
		HANDLE_MESH_MATERIAL->Expand(TRUE);
	}	

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_PARAMETER);
}