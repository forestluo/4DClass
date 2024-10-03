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

#include "ObjectSketcher.h"
#include "JointObjectSketcher.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define MAINFRAME											((CMainFrame *)GetTopLevelFrame())

///////////////////////////////////////////////////////////////////////////////
//
// FillRenderProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillRenderProperties(CD3DXRenderableObject* pRenderableObject)
{
	//Color property.
	CMFCPropertyGridColorProperty* pColorProp;

#ifdef _DEBUG
	assert(pRenderableObject != NULL);
#endif

	//Create property.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"主要");

	{
		//Check instance.
		if(pRenderableObject->isPrimitiveObject())
		{
			//Get model name.
			CNormalString modelName = ((CD3DXPrimitiveObject *)pRenderableObject)->getModelName();
			//Create property.
			HANDLE_RENDER_MODEL_NAME = new CMFCPropertyGridProperty(L"模板名称",
				modelName.getCString(), L"可绘制基本几何体所使用的模板名称。");
			//Disable it.
			HANDLE_RENDER_MODEL_NAME->Enable(FALSE);
			HANDLE_RENDER_MODEL_NAME->AllowEdit(FALSE);
			//Add option.
			HANDLE_RENDER_MODEL_NAME->AddOption(modelName.getCString());
			//Add subitem.
			HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_RENDER_MODEL_NAME);

			//Get effect name.
			CNormalString effectName = ((CD3DXPrimitiveObject *)pRenderableObject)->getEffectName();
			//Create property.
			HANDLE_RENDER_EFFECT_NAME = new CMFCPropertyGridProperty(L"绘制手法",
				effectName.getCString(), L"可绘制基本几何体所使用的绘制手法名称。");
			//Add option.
			HANDLE_RENDER_EFFECT_NAME->AddOption(L"");
			//Check main frame.
			if(MAINFRAME != NULL)
			{
				//Get doc.
				CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
				//Check result.
				if(pDoc != NULL) pDoc->addEffectOptions(HANDLE_RENDER_EFFECT_NAME);
			}
			//Not editable.
			HANDLE_RENDER_EFFECT_NAME->AllowEdit(FALSE);
			//Add item.
			HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_RENDER_EFFECT_NAME);

			//Create property.
			HANDLE_RENDER_COLOR = new CMFCPropertyGridProperty(L"颜色");
			//Add property group.
			HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_RENDER_COLOR);

			{
				//Get color.
				D3DCOLOR color = ((CD3DXPrimitiveObject *)pRenderableObject)->getColor();
				//Create property.
				pColorProp = new CMFCPropertyGridColorProperty(L"基本颜色",
					color,NULL, L"可绘制基本几何体的基本颜色。");
				//Enable other button.
				pColorProp->EnableOtherButton(L"其他");
				//Enable automatic button.
				pColorProp->EnableAutomaticButton(L"缺省",::GetSysColor(COLOR_3DFACE));
				//Set property.
				HANDLE_RENDER_COLOR_GLOBAL = pColorProp;
				//Add subitem.
				HANDLE_RENDER_COLOR->AddSubItem(HANDLE_RENDER_COLOR_GLOBAL);

			}

			//Create property.
			HANDLE_RENDER_LIGHT = new CMFCPropertyGridProperty(L"光线");
			//Add property group.
			HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_RENDER_LIGHT);

			{
				//Get light color.
				D3DXVECTOR4 vLightColor = ((CD3DXPrimitiveObject *)pRenderableObject)->getLightColor();
				//Get color.
				D3DCOLOR color = D3DCOLOR_COLORVALUE(vLightColor.x,vLightColor.y,vLightColor.z,vLightColor.w);
				//Create property.
				pColorProp = new CMFCPropertyGridColorProperty(L"光线颜色",
					color,NULL, L"可绘制基本几何体的光线颜色。");
				//Enable other button.
				pColorProp->EnableOtherButton(L"其他");
				//Enable automatic button.
				pColorProp->EnableAutomaticButton(L"缺省",::GetSysColor(COLOR_3DFACE));
				//Set property.
				HANDLE_RENDER_LIGHT_COLOR = pColorProp;
				//Add subitem.
				HANDLE_RENDER_LIGHT->AddSubItem(HANDLE_RENDER_LIGHT_COLOR);
			}

			//Create property.
			HANDLE_RENDER_TEXTURE = new CMFCPropertyGridProperty(L"纹理");
			//Add property group.
			HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_RENDER_TEXTURE);

			{
				//Get scene map name.
				CNormalString sceneMapName = ((CD3DXPrimitiveObject *)pRenderableObject)->getSceneMapName();
				//Create property.
				HANDLE_RENDER_TEXTURE_SCENE = new CMFCPropertyGridProperty(L"场景图",
					sceneMapName.getCString(), L"可绘制基本几何体所使用的场景图名称。");
				//Add option.
				HANDLE_RENDER_TEXTURE_SCENE->AddOption(L"");
				//Check main frame.
				if(MAINFRAME != NULL)
				{
					//Get doc.
					CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
					//Check result.
					if(pDoc != NULL) pDoc->addTextureOptions(HANDLE_RENDER_TEXTURE_SCENE);
				}
				//Not editable.
				HANDLE_RENDER_TEXTURE_SCENE->AllowEdit(FALSE);
				//Add item.
				HANDLE_RENDER_TEXTURE->AddSubItem(HANDLE_RENDER_TEXTURE_SCENE);
			}
		}
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_RENDER_DEBUG = new CMFCPropertyGridProperty(L"调试");
	//Set description.
	HANDLE_RENDER_DEBUG->SetDescription(L"可绘制物体相关的调试选项。");

	{
		//Get sketcher.
		CObjectSketcher* pSketcher = pRenderableObject->getSketcher();

		//Get value.
		bool bDrawAxis  = pSketcher != NULL && pSketcher->drawAxis ? true : false;
		//Create property.
		HANDLE_RENDER_DEBUG_LOCAL_AXIS = new CMFCPropertyGridProperty(L"坐标架",
			(_variant_t) bDrawAxis, L"是否绘制可显示物体的本地坐标架。");
		//Add item.
		HANDLE_RENDER_DEBUG->AddSubItem(HANDLE_RENDER_DEBUG_LOCAL_AXIS);

		{
			//Create property.
			HANDLE_RENDER_DEBUG_BOX = new CMFCPropertyGridProperty(L"包围盒");
			//Set description.
			HANDLE_RENDER_DEBUG_BOX->SetDescription(L"是否绘制可显示物体的自身包围盒。");
			//Add item.
			HANDLE_RENDER_DEBUG->AddSubItem(HANDLE_RENDER_DEBUG_BOX);

			//Get value.
			bool bDrawBox = pSketcher != NULL && pSketcher->drawBox ? true : false;
			//Create property.
			HANDLE_RENDER_DEBUG_BOX_AABOX = new CMFCPropertyGridProperty(L"坐标包围盒",
				(_variant_t) bDrawBox, L"是否绘制可显示物体的坐标包围盒。");
			//Add subitem.
			HANDLE_RENDER_DEBUG_BOX->AddSubItem(HANDLE_RENDER_DEBUG_BOX_AABOX);

			//Get value.
			bool bDrawSphere = pSketcher != NULL && pSketcher->drawSphere ? true : false;
			//Create property.
			HANDLE_RENDER_DEBUG_BOX_SPHERE = new CMFCPropertyGridProperty(L"球形包围盒",
				(_variant_t) bDrawSphere, L"是否绘制可显示物体的球形包围盒。");
			//Add subitem.
			HANDLE_RENDER_DEBUG_BOX->AddSubItem(HANDLE_RENDER_DEBUG_BOX_SPHERE);
		}

		//Check base.
		if(IS_JOINTOBJECTSKETCHER_BASE(pSketcher))
		{
			//Create property.
			HANDLE_RENDER_DEBUG_JOINT = new CMFCPropertyGridProperty(L"链接");
			//Set description.
			HANDLE_RENDER_DEBUG_JOINT->SetDescription(L"有关链接体相关的调试参数。");
			//Add item.
			HANDLE_RENDER_DEBUG->AddSubItem(HANDLE_RENDER_DEBUG_JOINT);

			//Get value.
			bool bDrawSphere = pSketcher != NULL && ((CJointObjectSketcher *)pSketcher)->drawJointSphere ? true : false;
			//Create property.
			HANDLE_RENDER_DEBUG_JOINT_SPHERE = new CMFCPropertyGridProperty(L"球空间",
				(_variant_t) bDrawSphere, L"链接体最大可活动的球空间范围。");
			//Add subitem.
			HANDLE_RENDER_DEBUG_JOINT->AddSubItem(HANDLE_RENDER_DEBUG_JOINT_SPHERE);

			//Get value.
			bool bDrawPosition = pSketcher != NULL && ((CJointObjectSketcher *)pSketcher)->drawJointPosition ? true : false;
			//Create property.
			HANDLE_RENDER_DEBUG_JOINT_POSITION = new CMFCPropertyGridProperty(L"位置点",
				(_variant_t) bDrawPosition, L"绘制链接体所应当在的实际空间位置点。");
			//Add subitem.
			HANDLE_RENDER_DEBUG_JOINT->AddSubItem(HANDLE_RENDER_DEBUG_JOINT_POSITION);

			//Get value.
			bool bDrawDirection = pSketcher != NULL && ((CJointObjectSketcher *)pSketcher)->drawJointDirection ? true : false;
			//Create property.
			HANDLE_RENDER_DEBUG_JOINT_DIRECTION = new CMFCPropertyGridProperty(L"主矢方向",
				(_variant_t) bDrawDirection, L"绘制链接体所应当指向的实际空间主矢方向。");
			//Add subitem.
			HANDLE_RENDER_DEBUG_JOINT->AddSubItem(HANDLE_RENDER_DEBUG_JOINT_DIRECTION);
		}
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_RENDER_DEBUG);
}
