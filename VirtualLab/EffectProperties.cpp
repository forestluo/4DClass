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
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"常规");

	//Create property.
	HANDLE_NAME = new CMFCPropertyGridProperty(L"名称",
		pEffect->getName().getCString(), L"绘制手法文件的名称。");
	HANDLE_NAME->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_NAME);

	//Create property.
	HANDLE_TYPE = new CMFCPropertyGridProperty(L"类型",
		L"特效文件", L"绘制手法文件的类型。");
	HANDLE_TYPE->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_TYPE);

	//Create property.
	HANDLE_FILE_NAME = new CMFCPropertyGridProperty(L"文件名",
		pEffect->getFileName().getCString(), L"绘制手法文件的文件名。");
	HANDLE_FILE_NAME->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_FILE_NAME);

	//Create property.
	HANDLE_REFERENCED_COUNT = new CMFCPropertyGridProperty(L"被引用次数",
		(_variant_t) pEffect->countReference(), L"绘制手法文件对象被引用的次数。");
	HANDLE_REFERENCED_COUNT->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_REFERENCED_COUNT);

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_GROUP_PARAMETER = new CMFCPropertyGridProperty(L"参数");
	//Set description.
	HANDLE_GROUP_PARAMETER->SetDescription(L"绘制手法文件中各种参数状态。");

	//Matrix
	{
		//Create property.
		HANDLE_GROUP_MATRIX = new CMFCPropertyGridProperty(L"矩阵参数");
		//Set description.
		HANDLE_GROUP_MATRIX->SetDescription(L"绘制手法文件中矩阵参数状态。");
		//Add item.
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_GROUP_MATRIX);

		//Create property.
		HANDLE_MATRIX_WORLD = new CMFCPropertyGridProperty(L"世界矩阵",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semWorld) != NULL) ? L"可设置" : L"不可设置"), L"绘制手法文件中是否存在世界矩阵（World Matrix）参数接口。");
		HANDLE_MATRIX_WORLD->Enable(FALSE);
		HANDLE_GROUP_MATRIX->AddSubItem(HANDLE_MATRIX_WORLD);

		//Create property.
		HANDLE_MATRIX_VIEW = new CMFCPropertyGridProperty(L"视矩阵",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semView) != NULL) ? L"可设置" : L"不可设置"), L"绘制手法文件中是否存在视矩阵（View Matrix）参数接口。");
		HANDLE_MATRIX_VIEW->Enable(FALSE);
		HANDLE_GROUP_MATRIX->AddSubItem(HANDLE_MATRIX_VIEW);

		//Create property.
		HANDLE_MATRIX_PROJECTION = new CMFCPropertyGridProperty(L"投影矩阵",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semProjection) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在投影矩阵（Projection Matrix）参数接口。");
		HANDLE_MATRIX_PROJECTION->Enable(FALSE);
		HANDLE_GROUP_MATRIX->AddSubItem(HANDLE_MATRIX_PROJECTION);

		//Create property.
		HANDLE_MATRIX_VIEW_INVERSE = new CMFCPropertyGridProperty(L"逆视矩阵",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semViewInverse) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在逆视矩阵（Inverse View Matrix）参数接口。");
		HANDLE_MATRIX_VIEW_INVERSE->Enable(FALSE);
		HANDLE_GROUP_MATRIX->AddSubItem(HANDLE_MATRIX_VIEW_INVERSE);

		//Create property.
		HANDLE_MATRIX_VIEW_PROJECTION = new CMFCPropertyGridProperty(L"视投矩阵",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semViewProjection) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在视投矩阵（View and Projection Matrix）参数接口。");
		HANDLE_MATRIX_VIEW_PROJECTION->Enable(FALSE);
		HANDLE_GROUP_MATRIX->AddSubItem(HANDLE_MATRIX_VIEW_PROJECTION);

		//Expand all.
		HANDLE_GROUP_MATRIX->Expand(TRUE);
	}
	//Material
	{
		//Create property.
		HANDLE_GROUP_MATERIAL = new CMFCPropertyGridProperty(L"材料参数");
		//Set description.
		HANDLE_GROUP_MATERIAL->SetDescription(L"绘制手法文件中材料参数状态。");
		//Add item.
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_GROUP_MATERIAL);

		//Create property.
		HANDLE_MATERIAL_POWER = new CMFCPropertyGridProperty(L"高亮",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialPower) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在高亮（Power）参数接口。");
		HANDLE_MATERIAL_POWER->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_POWER);

		//Create property.
		HANDLE_MATERIAL_DIFFUSE = new CMFCPropertyGridProperty(L"散射",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialDiffuse) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在散射（Diffuse）参数接口。");
		HANDLE_MATERIAL_DIFFUSE->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_DIFFUSE);

		//Create property.
		HANDLE_MATERIAL_SPECULAR = new CMFCPropertyGridProperty(L"镜面",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialSpecular) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在镜面（Specular）参数接口。");
		HANDLE_MATERIAL_SPECULAR->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_SPECULAR);

		//Create property.
		HANDLE_MATERIAL_AMBIENT = new CMFCPropertyGridProperty(L"环境",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialAmbient) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在环境（Ambient）参数接口。");
		HANDLE_MATERIAL_AMBIENT->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_AMBIENT);

		//Create property.
		HANDLE_MATERIAL_EMISSIVE = new CMFCPropertyGridProperty(L"发散",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialAmbient) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在发散（Emissive）参数接口。");
		HANDLE_MATERIAL_EMISSIVE->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_EMISSIVE);

		//Create property.
		HANDLE_MATERIAL_TEXTURE = new CMFCPropertyGridProperty(L"纹理",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semMaterialTexture) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在纹理（Texture）参数接口。");
		HANDLE_MATERIAL_TEXTURE->Enable(FALSE);
		HANDLE_GROUP_MATERIAL->AddSubItem(HANDLE_MATERIAL_TEXTURE);

		//Expand all.
		HANDLE_GROUP_MATERIAL->Expand(TRUE);
	}

	//Texture
	{
		//Create property.
		HANDLE_GROUP_TEXTURE = new CMFCPropertyGridProperty(L"纹理参数");
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_GROUP_TEXTURE);

		//Create property.
		HANDLE_TEXTURE_SCENE = new CMFCPropertyGridProperty(L"场景",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semSceneMap) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在场景纹理（Texture）参数接口。");
		HANDLE_TEXTURE_SCENE->Enable(FALSE);
		HANDLE_GROUP_TEXTURE->AddSubItem(HANDLE_TEXTURE_SCENE);

		//Create property.
		HANDLE_TEXTURE_ENVIRONMENT = new CMFCPropertyGridProperty(L"环境",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semEnvironmentMap) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在环境纹理（Texture）参数接口。");
		HANDLE_TEXTURE_ENVIRONMENT->Enable(FALSE);
		HANDLE_GROUP_TEXTURE->AddSubItem(HANDLE_TEXTURE_ENVIRONMENT);
	}

	//Misc
	{
		//Create property.
		HANDLE_GROUP_MISC = new CMFCPropertyGridProperty(L"其他参数");
		HANDLE_GROUP_PARAMETER->AddSubItem(HANDLE_GROUP_MISC);

		//Create property.
		HANDLE_GLOBAL_COLOR = new CMFCPropertyGridProperty(L"全局颜色",
			(_variant_t) ((pEffect->getParameterHandle(CD3DXEffect::semObjectColor) != NULL) ? L"可设置" : L"不可设置"),L"绘制手法文件中是否存在全局颜色（Global Color）参数接口。");
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