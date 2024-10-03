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
#include "ModelViewPort.h"
#include "PersonalViewPort.h"

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

//ViewPort
const LPCTSTR VIEWPORT_PROPERTIES[] =
{
	PROPERTY_GENERAL,
};

///////////////////////////////////////////////////////////////////////////////
//
// ShowProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ShowProperties(CViewPort* pViewPort)
{
#ifdef _DEBUG
	assert(pViewPort != NULL);
#endif
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL)
		{
			//Get focused.
			CD3DXObject* object = pDoc->application->getFocused();
			//Check result.
			if(object != pViewPort)
			{
				//Set focused object.
				pDoc->application->setFocused(pViewPort);
				//Set selected property page.
				nSelectedPropertyPage = 0;

				//Set window text.
				SetWindowTextW(L"�ӿ�");
				//Clear property handles.
				ClearHandles();
				//Remove all previous elements.
				m_wndPropList.RemoveAll();
				//Remove all selections.
				m_wndObjectCombo.ResetContent();
				//Add properties.
				for(int i = 0;i < sizeof(VIEWPORT_PROPERTIES) / sizeof(LPCTSTR);i ++)
				{
					//Add string.
					m_wndObjectCombo.AddString(VIEWPORT_PROPERTIES[i]);
				}
				//Set current selection.
				m_wndObjectCombo.SetCurSel(PROPERTY_GENERAL_SELECTION);

				//Fill properties.
				FillProperties(pViewPort);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// FillProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillProperties(CViewPort* pViewPort)
{
#ifdef _DEBUG
	assert(pViewPort != NULL);
#endif

	//Create property.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"����");
	//Check type.
	if(IS_MODEL_VIEWPORT_BASE(pViewPort))
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",L"ģ̬�ӿ�");
		//Set description.
		HANDLE_TYPE->SetDescription(L"ģ̬�ӿڣ�����ָ����������ϵ�����ġ�����Χ����������ϵ������ת�����š�");
	}
	else if(IS_PERSONAL_VIEWPORT_BASE(pViewPort))
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",L"�����ӿ�");
		//Set description.
		HANDLE_TYPE->SetDescription(L"�����ӿڣ��Ӹ�������Ƕ����۲����磬��������������ϵ���ƶ�����ת����");
	}
	//Add option.
	HANDLE_TYPE->AddOption(L"ģ̬�ӿ�");
	HANDLE_TYPE->AddOption(L"�����ӿ�");
	//Disable it.
	HANDLE_TYPE->Enable(FALSE);
	//Add item.
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_TYPE);

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_GROUP_CAMERA = new CMFCPropertyGridProperty(L"���������");
	//Set description.
	HANDLE_GROUP_CAMERA->SetDescription(L"�ӿ����������Ҫ������");

	{
		//Get eye at.
		C4DVector3 eyeAt = pViewPort->getEyeAt();

		//Create property.
		HANDLE_GROUP_CAMERA_POSITION = new CMFCPropertyGridProperty(L"����λ��");
		//Set description.
		HANDLE_GROUP_CAMERA_POSITION->SetDescription(L"����������ϵ�£����������άλ�ò�����");

		//Create property.
		HANDLE_GROUP_CAMERA_POSITION_X = new CMFCPropertyGridProperty(L"x����",
			(_variant_t) eyeAt.x(), L"����������ϵ�£������λ�õ�x������ֵ��");
		//Disable it.
		HANDLE_GROUP_CAMERA_POSITION_X->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_POSITION->AddSubItem(HANDLE_GROUP_CAMERA_POSITION_X);

		//Create property.
		HANDLE_GROUP_CAMERA_POSITION_Y = new CMFCPropertyGridProperty(L"y����",
			(_variant_t) eyeAt.y(), L"����������ϵ�£������λ�õ�y������ֵ��");
		//Disable it.
		HANDLE_GROUP_CAMERA_POSITION_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_POSITION->AddSubItem(HANDLE_GROUP_CAMERA_POSITION_Y);

		//Create property.
		HANDLE_GROUP_CAMERA_POSITION_Z = new CMFCPropertyGridProperty(L"z����",
			(_variant_t) eyeAt.z(), L"����������ϵ�£������λ�õ�z������ֵ��");
		//Disable it.
		HANDLE_GROUP_CAMERA_POSITION_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_POSITION->AddSubItem(HANDLE_GROUP_CAMERA_POSITION_Z);

		//Add item.
		HANDLE_GROUP_CAMERA->AddSubItem(HANDLE_GROUP_CAMERA_POSITION);
	}

	{
		//Get look at.
		C4DVector3 lookAt = pViewPort->getEyeLookAt();

		//Create property.
		HANDLE_GROUP_CAMERA_LOOKAT = new CMFCPropertyGridProperty(L"�ӵ�λ��");
		//Set description.
		HANDLE_GROUP_CAMERA_LOOKAT->SetDescription(L"����������ϵ�£�������ӵ����ά���ꡣ");

		//Create property.
		HANDLE_GROUP_CAMERA_LOOKAT_X = new CMFCPropertyGridProperty(L"x����",
			(_variant_t) lookAt.x(), L"����������ϵ�£�������ӵ��x������ֵ��");
		//Disable it.
		HANDLE_GROUP_CAMERA_LOOKAT_X->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_LOOKAT->AddSubItem(HANDLE_GROUP_CAMERA_LOOKAT_X);

		//Create property.
		HANDLE_GROUP_CAMERA_LOOKAT_Y = new CMFCPropertyGridProperty(L"y����",
			(_variant_t) lookAt.y(), L"����������ϵ�£�������ӵ��y������ֵ��");
		//Disable it.
		HANDLE_GROUP_CAMERA_LOOKAT_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_LOOKAT->AddSubItem(HANDLE_GROUP_CAMERA_LOOKAT_Y);

		//Create property.
		HANDLE_GROUP_CAMERA_LOOKAT_Z = new CMFCPropertyGridProperty(L"z����",
			(_variant_t) lookAt.z(), L"����������ϵ�£�������ӵ��z������ֵ��");
		//Disable it.
		HANDLE_GROUP_CAMERA_LOOKAT_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_LOOKAT->AddSubItem(HANDLE_GROUP_CAMERA_LOOKAT_Z);

		//Add item.
		HANDLE_GROUP_CAMERA->AddSubItem(HANDLE_GROUP_CAMERA_LOOKAT);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_CAMERA);

	//Create property.
	HANDLE_GROUP_CAMERA_PROJECTION = new CMFCPropertyGridProperty(L"ͶӰ����");
	//Set description.
	HANDLE_GROUP_CAMERA_PROJECTION->SetDescription(L"ͶӰ����άƽ������Ҫ���õ���ز�����");
	
	{
		//Create property.
		HANDLE_GROUP_CAMERA_PROJECTION_FOV = new CMFCPropertyGridProperty(L"�ӽǷ�Χ",
			(_variant_t) pViewPort->getFieldOfView(), L"��������ӽǷ�Χ��Field of View����");
		//Disable it.
		HANDLE_GROUP_CAMERA_PROJECTION_FOV->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_PROJECTION->AddSubItem(HANDLE_GROUP_CAMERA_PROJECTION_FOV);

		//Create property.
		HANDLE_GROUP_CAMERA_PROJECTION_ASPECT = new CMFCPropertyGridProperty(L"�ݺ����",
			(_variant_t) pViewPort->getFAspect(), L"��άͶӰƽ����ݺ������Aspect Ratio����");
		//Disable it.
		HANDLE_GROUP_CAMERA_PROJECTION_ASPECT->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_PROJECTION->AddSubItem(HANDLE_GROUP_CAMERA_PROJECTION_ASPECT);

		//Create property.
		HANDLE_GROUP_CAMERA_PROJECTION_ZFAR = new CMFCPropertyGridProperty(L"Զ�ü�����",
			(_variant_t) pViewPort->getFarClip(), L"����Զ�ü�����(Z Far Distance��������Ͳ���ʾ��");
		//Disable it.
		HANDLE_GROUP_CAMERA_PROJECTION_ZFAR->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_PROJECTION->AddSubItem(HANDLE_GROUP_CAMERA_PROJECTION_ZFAR);

		//Create property.
		HANDLE_GROUP_CAMERA_PROJECTION_ZNEAR = new CMFCPropertyGridProperty(L"���ü�����",
			(_variant_t) pViewPort->getNearClip(), L"С�ڽ��ü�����(Z Near Distance��������Ͳ���ʾ��");
		//Disable it.
		HANDLE_GROUP_CAMERA_PROJECTION_ZNEAR->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_PROJECTION->AddSubItem(HANDLE_GROUP_CAMERA_PROJECTION_ZNEAR);

	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_CAMERA_PROJECTION);

	//Create property.
	HANDLE_GROUP_MOUSE = new CMFCPropertyGridProperty(L"���λ��");
	//Set description.
	HANDLE_GROUP_MOUSE->SetDescription(L"ʵʱ��ʾ����ڴ����еĶ�ά����λ�á�");

	{
		//Create property.
		HANDLE_GROUP_MOUSE_SCREEN_X = new CMFCPropertyGridProperty(L"x����",
			(_variant_t) pViewPort->getMouseX(),L"�������Ļ�����е�x����λ�á�");
		//Disable it.
		HANDLE_GROUP_MOUSE_SCREEN_X->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_MOUSE->AddSubItem(HANDLE_GROUP_MOUSE_SCREEN_X);

		//Create property.
		HANDLE_GROUP_MOUSE_SCREEN_Y = new CMFCPropertyGridProperty(L"y����",
			(_variant_t) pViewPort->getMouseY(),L"�������Ļ�����е�y����λ�á�");
		//Disable it.
		HANDLE_GROUP_MOUSE_SCREEN_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_MOUSE->AddSubItem(HANDLE_GROUP_MOUSE_SCREEN_Y);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MOUSE);
}

///////////////////////////////////////////////////////////////////////////////
//
// OnPropertyChanged
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::OnPropertyChanged(CViewPort* pViewPort,CMFCPropertyGridProperty *pProp)
{
#ifdef _DEBUG
	assert(pViewPort != NULL && pProp != NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// ChangeProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ChangeProperties(CViewPort* pViewPort)
{
#ifdef _DEBUG
	assert(pViewPort != NULL);
#endif
	//Check selection.
	if(nSelectedPropertyPage == PROPERTY_GENERAL_SELECTION)
	{
		//Get eye at.
		C4DVector3 eyeAt = pViewPort->getEyeAt();
		//Check result.
		if(HANDLE_GROUP_CAMERA_POSITION_X != NULL)
		{
			//Set value.
			HANDLE_GROUP_CAMERA_POSITION_X->SetValue((_variant_t)eyeAt.x());
		}
		//Check result.
		if(HANDLE_GROUP_CAMERA_POSITION_Y != NULL)
		{
			//Set value.
			HANDLE_GROUP_CAMERA_POSITION_Y->SetValue((_variant_t)eyeAt.y());
		}
		//Check result.
		if(HANDLE_GROUP_CAMERA_POSITION_Z != NULL)
		{
			//Set value.
			HANDLE_GROUP_CAMERA_POSITION_Z->SetValue((_variant_t)eyeAt.z());
		}

		//Get look at.
		C4DVector3 lookAt = pViewPort->getEyeLookAt();
		//Check result.
		if(HANDLE_GROUP_CAMERA_LOOKAT_X != NULL)
		{
			//Set value.
			HANDLE_GROUP_CAMERA_LOOKAT_X->SetValue((_variant_t)lookAt.x());
		}
		//Check result.
		if(HANDLE_GROUP_CAMERA_LOOKAT_Y != NULL)
		{
			//Set value.
			HANDLE_GROUP_CAMERA_LOOKAT_Y->SetValue((_variant_t)lookAt.y());
		}
		//Check result.
		if(HANDLE_GROUP_CAMERA_LOOKAT_Z != NULL)
		{
			//Set value.
			HANDLE_GROUP_CAMERA_LOOKAT_Z->SetValue((_variant_t)lookAt.z());
		}

		//Check result.
		if(HANDLE_GROUP_MOUSE_SCREEN_X != NULL)
		{
			//Set value.
			HANDLE_GROUP_MOUSE_SCREEN_X->SetValue((_variant_t)pViewPort->getMouseX());
		}
		//Check result.
		if(HANDLE_GROUP_MOUSE_SCREEN_Y != NULL)
		{
			//Set value.
			HANDLE_GROUP_MOUSE_SCREEN_Y->SetValue((_variant_t)pViewPort->getMouseY());
		}
	}
}
