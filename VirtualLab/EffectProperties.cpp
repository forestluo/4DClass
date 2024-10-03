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

//Effect
const LPCTSTR EFFECT_PROPERTIES[] =
{
	PROPERTY_GENERAL,
};

///////////////////////////////////////////////////////////////////////////////
//
// ShowProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ShowProperties(CD3DXEffect* pEffect)
{
#ifdef _DEBUG
	assert(pEffect != NULL);
#endif
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL) pDoc->application->setFocused(pEffect);
	}

	//Set selected property page.
	nSelectedPropertyPage = 0;
	//Set windows text.
	SetWindowTextW(pEffect->getName().getCString());

	//Clear property handles.
	ClearHandles();
	//Remove all previous elements.
	m_wndPropList.RemoveAll();
	//Remove all selections.
	m_wndObjectCombo.ResetContent();
	//Add properties.
	for(int i = 0;i < sizeof(EFFECT_PROPERTIES) / sizeof(LPCTSTR);i ++)
	{
		//Add string.
		m_wndObjectCombo.AddString(EFFECT_PROPERTIES[i]);
	}
	//Set current selection.
	m_wndObjectCombo.SetCurSel(PROPERTY_GENERAL_SELECTION);

	//Fill properties.
	FillProperties(pEffect);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillProperties(CD3DXEffect* pEffect)
{
#ifdef _DEBUG
	assert(pEffect != NULL);
#endif

	//Create major.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"����");

	//Create property.
	HANDLE_NAME = new CMFCPropertyGridProperty(L"����",
		pEffect->getName().getCString(), L"�����ַ��ļ������ơ�");
	HANDLE_NAME->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_NAME);

	//Create property.
	HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",
		L"��Ч�ļ�", L"�����ַ��ļ������͡�");
	HANDLE_TYPE->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_TYPE);

	//Create property.
	HANDLE_FILE_NAME = new CMFCPropertyGridProperty(L"�ļ���",
		pEffect->getFileName().getCString(), L"�����ַ��ļ����ļ�����");
	HANDLE_FILE_NAME->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_FILE_NAME);

	//Create property.
	HANDLE_REFERENCED_COUNT = new CMFCPropertyGridProperty(L"�����ô���",
		(_variant_t) pEffect->countReference(), L"�����ַ��ļ��������õĴ�����");
	HANDLE_REFERENCED_COUNT->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_REFERENCED_COUNT);

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_GROUP_PARAMETER = new CMFCPropertyGridProperty(L"����");
	//Set description.
	HANDLE_GROUP_PARAMETER->SetDescription(L"�����ַ��ļ��и��ֲ���״̬��");

	//Matrix
	{
		//Create property.
		HANDLE_GROUP_MATRIX = new CMFCPropertyGridProperty(L"�������");
		//Set description.
		HANDLE_GROUP_MATRIX->SetDescription(L"�����ַ��ļ��о������״̬��");
		//Add item.
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_GROUP_MATRIX);

		//Create property.
		HANDLE_MATRIX_WORLD = new CMFCPropertyGridProperty(L"�������",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semWorld) != NULL) ? L"������" : L"��������"), L"�����ַ��ļ����Ƿ�����������World Matrix�������ӿڡ�");
		HANDLE_MATRIX_WORLD->Enable(FALSE);
		HANDLE_GROUP_MATRIX->AddSubItem(HANDLE_MATRIX_WORLD);

		//Create property.
		HANDLE_MATRIX_VIEW = new CMFCPropertyGridProperty(L"�Ӿ���",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semView) != NULL) ? L"������" : L"��������"), L"�����ַ��ļ����Ƿ�����Ӿ���View Matrix�������ӿڡ�");
		HANDLE_MATRIX_VIEW->Enable(FALSE);
		HANDLE_GROUP_MATRIX->AddSubItem(HANDLE_MATRIX_VIEW);

		//Create property.
		HANDLE_MATRIX_PROJECTION = new CMFCPropertyGridProperty(L"ͶӰ����",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semProjection) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ����ͶӰ����Projection Matrix�������ӿڡ�");
		HANDLE_MATRIX_PROJECTION->Enable(FALSE);
		HANDLE_GROUP_MATRIX->AddSubItem(HANDLE_MATRIX_PROJECTION);

		//Create property.
		HANDLE_MATRIX_VIEW_INVERSE = new CMFCPropertyGridProperty(L"���Ӿ���",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semViewInverse) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ�������Ӿ���Inverse View Matrix�������ӿڡ�");
		HANDLE_MATRIX_VIEW_INVERSE->Enable(FALSE);
		HANDLE_GROUP_MATRIX->AddSubItem(HANDLE_MATRIX_VIEW_INVERSE);

		//Create property.
		HANDLE_MATRIX_VIEW_PROJECTION = new CMFCPropertyGridProperty(L"��Ͷ����",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semViewProjection) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ������Ͷ����View and Projection Matrix�������ӿڡ�");
		HANDLE_MATRIX_VIEW_PROJECTION->Enable(FALSE);
		HANDLE_GROUP_MATRIX->AddSubItem(HANDLE_MATRIX_VIEW_PROJECTION);

		//Expand all.
		HANDLE_GROUP_MATRIX->Expand(TRUE);
	}
	//Material
	{
		//Create property.
		HANDLE_GROUP_MATERIAL = new CMFCPropertyGridProperty(L"���ϲ���");
		//Set description.
		HANDLE_GROUP_MATERIAL->SetDescription(L"�����ַ��ļ��в��ϲ���״̬��");
		//Add item.
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_GROUP_MATERIAL);

		//Create property.
		HANDLE_MATERIAL_POWER = new CMFCPropertyGridProperty(L"����",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialPower) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ���ڸ�����Power�������ӿڡ�");
		HANDLE_MATERIAL_POWER->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_POWER);

		//Create property.
		HANDLE_MATERIAL_DIFFUSE = new CMFCPropertyGridProperty(L"ɢ��",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialDiffuse) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ����ɢ�䣨Diffuse�������ӿڡ�");
		HANDLE_MATERIAL_DIFFUSE->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_DIFFUSE);

		//Create property.
		HANDLE_MATERIAL_SPECULAR = new CMFCPropertyGridProperty(L"����",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialSpecular) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ���ھ��棨Specular�������ӿڡ�");
		HANDLE_MATERIAL_SPECULAR->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_SPECULAR);

		//Create property.
		HANDLE_MATERIAL_AMBIENT = new CMFCPropertyGridProperty(L"����",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialAmbient) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ���ڻ�����Ambient�������ӿڡ�");
		HANDLE_MATERIAL_AMBIENT->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_AMBIENT);

		//Create property.
		HANDLE_MATERIAL_EMISSIVE = new CMFCPropertyGridProperty(L"��ɢ",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialAmbient) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ���ڷ�ɢ��Emissive�������ӿڡ�");
		HANDLE_MATERIAL_EMISSIVE->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_EMISSIVE);

		//Create property.
		HANDLE_MATERIAL_TEXTURE = new CMFCPropertyGridProperty(L"����",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialTexture) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ��������Texture�������ӿڡ�");
		HANDLE_MATERIAL_TEXTURE->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_TEXTURE);

		//Expand all.
		HANDLE_GROUP_MATERIAL->Expand(TRUE);
	}

	//Texture
	{
		//Create property.
		HANDLE_GROUP_TEXTURE = new CMFCPropertyGridProperty(L"�������");
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_GROUP_TEXTURE);

		//Create property.
		HANDLE_TEXTURE_SCENE = new CMFCPropertyGridProperty(L"����",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semSceneMap) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ���ڳ�������Texture�������ӿڡ�");
		HANDLE_TEXTURE_SCENE->Enable(FALSE);
		HANDLE_GROUP_TEXTURE->AddSubItem(HANDLE_TEXTURE_SCENE);

		//Create property.
		HANDLE_TEXTURE_ENVIRONMENT = new CMFCPropertyGridProperty(L"����",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semEnvironmentMap) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ���ڻ�������Texture�������ӿڡ�");
		HANDLE_TEXTURE_ENVIRONMENT->Enable(FALSE);
		HANDLE_GROUP_TEXTURE->AddSubItem(HANDLE_TEXTURE_ENVIRONMENT);
	}

	//Misc
	{
		//Create property.
		HANDLE_GROUP_MISC = new CMFCPropertyGridProperty(L"��������");
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_GROUP_MISC);

		//Create property.
		HANDLE_GLOBAL_COLOR = new CMFCPropertyGridProperty(L"ȫ����ɫ",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semObjectColor) != NULL) ? L"������" : L"��������"),L"�����ַ��ļ����Ƿ����ȫ����ɫ��Global Color�������ӿڡ�");
		HANDLE_GLOBAL_COLOR->Enable(FALSE);
		HANDLE_GROUP_MISC->AddSubItem(HANDLE_GLOBAL_COLOR);

		//Expand all.
		HANDLE_GROUP_MISC->Expand(TRUE);
	}
	//Expand all.
	HANDLE_GROUP_PARAMETER->Expand(TRUE);
	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_PARAMETER);
}