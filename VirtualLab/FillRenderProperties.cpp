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
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"��Ҫ");

	{
		//Check instance.
		if(pRenderableObject->isPrimitiveObject())
		{
			//Get model name.
			CNormalString modelName = ((CD3DXPrimitiveObject *)pRenderableObject)->getModelName();
			//Create property.
			HANDLE_RENDER_MODEL_NAME = new CMFCPropertyGridProperty(L"ģ������",
				modelName.getCString(), L"�ɻ��ƻ�����������ʹ�õ�ģ�����ơ�");
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
			HANDLE_RENDER_EFFECT_NAME = new CMFCPropertyGridProperty(L"�����ַ�",
				effectName.getCString(), L"�ɻ��ƻ�����������ʹ�õĻ����ַ����ơ�");
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
			HANDLE_RENDER_COLOR = new CMFCPropertyGridProperty(L"��ɫ");
			//Add property group.
			HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_RENDER_COLOR);

			{
				//Get color.
				D3DCOLOR color = ((CD3DXPrimitiveObject *)pRenderableObject)->getColor();
				//Create property.
				pColorProp = new CMFCPropertyGridColorProperty(L"������ɫ",
					color,NULL, L"�ɻ��ƻ���������Ļ�����ɫ��");
				//Enable other button.
				pColorProp->EnableOtherButton(L"����");
				//Enable automatic button.
				pColorProp->EnableAutomaticButton(L"ȱʡ",::GetSysColor(COLOR_3DFACE));
				//Set property.
				HANDLE_RENDER_COLOR_GLOBAL = pColorProp;
				//Add subitem.
				HANDLE_RENDER_COLOR->AddSubItem(HANDLE_RENDER_COLOR_GLOBAL);

			}

			//Create property.
			HANDLE_RENDER_LIGHT = new CMFCPropertyGridProperty(L"����");
			//Add property group.
			HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_RENDER_LIGHT);

			{
				//Get light color.
				D3DXVECTOR4 vLightColor = ((CD3DXPrimitiveObject *)pRenderableObject)->getLightColor();
				//Get color.
				D3DCOLOR color = D3DCOLOR_COLORVALUE(vLightColor.x,vLightColor.y,vLightColor.z,vLightColor.w);
				//Create property.
				pColorProp = new CMFCPropertyGridColorProperty(L"������ɫ",
					color,NULL, L"�ɻ��ƻ���������Ĺ�����ɫ��");
				//Enable other button.
				pColorProp->EnableOtherButton(L"����");
				//Enable automatic button.
				pColorProp->EnableAutomaticButton(L"ȱʡ",::GetSysColor(COLOR_3DFACE));
				//Set property.
				HANDLE_RENDER_LIGHT_COLOR = pColorProp;
				//Add subitem.
				HANDLE_RENDER_LIGHT->AddSubItem(HANDLE_RENDER_LIGHT_COLOR);
			}

			//Create property.
			HANDLE_RENDER_TEXTURE = new CMFCPropertyGridProperty(L"����");
			//Add property group.
			HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_RENDER_TEXTURE);

			{
				//Get scene map name.
				CNormalString sceneMapName = ((CD3DXPrimitiveObject *)pRenderableObject)->getSceneMapName();
				//Create property.
				HANDLE_RENDER_TEXTURE_SCENE = new CMFCPropertyGridProperty(L"����ͼ",
					sceneMapName.getCString(), L"�ɻ��ƻ�����������ʹ�õĳ���ͼ���ơ�");
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
	HANDLE_RENDER_DEBUG = new CMFCPropertyGridProperty(L"����");
	//Set description.
	HANDLE_RENDER_DEBUG->SetDescription(L"�ɻ���������صĵ���ѡ�");

	{
		//Get sketcher.
		CObjectSketcher* pSketcher = pRenderableObject->getSketcher();

		//Get value.
		bool bDrawAxis  = pSketcher != NULL && pSketcher->drawAxis ? true : false;
		//Create property.
		HANDLE_RENDER_DEBUG_LOCAL_AXIS = new CMFCPropertyGridProperty(L"�����",
			(_variant_t) bDrawAxis, L"�Ƿ���ƿ���ʾ����ı�������ܡ�");
		//Add item.
		HANDLE_RENDER_DEBUG->AddSubItem(HANDLE_RENDER_DEBUG_LOCAL_AXIS);

		{
			//Create property.
			HANDLE_RENDER_DEBUG_BOX = new CMFCPropertyGridProperty(L"��Χ��");
			//Set description.
			HANDLE_RENDER_DEBUG_BOX->SetDescription(L"�Ƿ���ƿ���ʾ����������Χ�С�");
			//Add item.
			HANDLE_RENDER_DEBUG->AddSubItem(HANDLE_RENDER_DEBUG_BOX);

			//Get value.
			bool bDrawBox = pSketcher != NULL && pSketcher->drawBox ? true : false;
			//Create property.
			HANDLE_RENDER_DEBUG_BOX_AABOX = new CMFCPropertyGridProperty(L"�����Χ��",
				(_variant_t) bDrawBox, L"�Ƿ���ƿ���ʾ����������Χ�С�");
			//Add subitem.
			HANDLE_RENDER_DEBUG_BOX->AddSubItem(HANDLE_RENDER_DEBUG_BOX_AABOX);

			//Get value.
			bool bDrawSphere = pSketcher != NULL && pSketcher->drawSphere ? true : false;
			//Create property.
			HANDLE_RENDER_DEBUG_BOX_SPHERE = new CMFCPropertyGridProperty(L"���ΰ�Χ��",
				(_variant_t) bDrawSphere, L"�Ƿ���ƿ���ʾ��������ΰ�Χ�С�");
			//Add subitem.
			HANDLE_RENDER_DEBUG_BOX->AddSubItem(HANDLE_RENDER_DEBUG_BOX_SPHERE);
		}

		//Check base.
		if(IS_JOINTOBJECTSKETCHER_BASE(pSketcher))
		{
			//Create property.
			HANDLE_RENDER_DEBUG_JOINT = new CMFCPropertyGridProperty(L"����");
			//Set description.
			HANDLE_RENDER_DEBUG_JOINT->SetDescription(L"�й���������صĵ��Բ�����");
			//Add item.
			HANDLE_RENDER_DEBUG->AddSubItem(HANDLE_RENDER_DEBUG_JOINT);

			//Get value.
			bool bDrawSphere = pSketcher != NULL && ((CJointObjectSketcher *)pSketcher)->drawJointSphere ? true : false;
			//Create property.
			HANDLE_RENDER_DEBUG_JOINT_SPHERE = new CMFCPropertyGridProperty(L"��ռ�",
				(_variant_t) bDrawSphere, L"���������ɻ����ռ䷶Χ��");
			//Add subitem.
			HANDLE_RENDER_DEBUG_JOINT->AddSubItem(HANDLE_RENDER_DEBUG_JOINT_SPHERE);

			//Get value.
			bool bDrawPosition = pSketcher != NULL && ((CJointObjectSketcher *)pSketcher)->drawJointPosition ? true : false;
			//Create property.
			HANDLE_RENDER_DEBUG_JOINT_POSITION = new CMFCPropertyGridProperty(L"λ�õ�",
				(_variant_t) bDrawPosition, L"������������Ӧ���ڵ�ʵ�ʿռ�λ�õ㡣");
			//Add subitem.
			HANDLE_RENDER_DEBUG_JOINT->AddSubItem(HANDLE_RENDER_DEBUG_JOINT_POSITION);

			//Get value.
			bool bDrawDirection = pSketcher != NULL && ((CJointObjectSketcher *)pSketcher)->drawJointDirection ? true : false;
			//Create property.
			HANDLE_RENDER_DEBUG_JOINT_DIRECTION = new CMFCPropertyGridProperty(L"��ʸ����",
				(_variant_t) bDrawDirection, L"������������Ӧ��ָ���ʵ�ʿռ���ʸ����");
			//Add subitem.
			HANDLE_RENDER_DEBUG_JOINT->AddSubItem(HANDLE_RENDER_DEBUG_JOINT_DIRECTION);
		}
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_RENDER_DEBUG);
}
