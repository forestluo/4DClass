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
				SetWindowTextW(L"视口");
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
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"常规");
	//Check type.
	if(IS_MODEL_VIEWPORT_BASE(pViewPort))
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"类型",L"模态视口");
		//Set description.
		HANDLE_TYPE->SetDescription(L"模态视口：视线指向世界坐标系的中心。可以围绕世界坐标系进行旋转和缩放。");
	}
	else if(IS_PERSONAL_VIEWPORT_BASE(pViewPort))
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"类型",L"个人视口");
		//Set description.
		HANDLE_TYPE->SetDescription(L"个人视口：从个人自身角度来观察世界，可以在世界坐标系中移动和旋转视向。");
	}
	//Add option.
	HANDLE_TYPE->AddOption(L"模态视口");
	HANDLE_TYPE->AddOption(L"个人视口");
	//Disable it.
	HANDLE_TYPE->Enable(FALSE);
	//Add item.
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_TYPE);

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_GROUP_CAMERA = new CMFCPropertyGridProperty(L"摄像机参数");
	//Set description.
	HANDLE_GROUP_CAMERA->SetDescription(L"视口摄像机的主要参数。");

	{
		//Get eye at.
		C4DVector3 eyeAt = pViewPort->getEyeAt();

		//Create property.
		HANDLE_GROUP_CAMERA_POSITION = new CMFCPropertyGridProperty(L"本机位置");
		//Set description.
		HANDLE_GROUP_CAMERA_POSITION->SetDescription(L"在世界坐标系下，摄像机的三维位置参数。");

		//Create property.
		HANDLE_GROUP_CAMERA_POSITION_X = new CMFCPropertyGridProperty(L"x坐标",
			(_variant_t) eyeAt.x(), L"在世界坐标系下，摄像机位置的x轴坐标值。");
		//Disable it.
		HANDLE_GROUP_CAMERA_POSITION_X->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_POSITION->AddSubItem(HANDLE_GROUP_CAMERA_POSITION_X);

		//Create property.
		HANDLE_GROUP_CAMERA_POSITION_Y = new CMFCPropertyGridProperty(L"y坐标",
			(_variant_t) eyeAt.y(), L"在世界坐标系下，摄像机位置的y轴坐标值。");
		//Disable it.
		HANDLE_GROUP_CAMERA_POSITION_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_POSITION->AddSubItem(HANDLE_GROUP_CAMERA_POSITION_Y);

		//Create property.
		HANDLE_GROUP_CAMERA_POSITION_Z = new CMFCPropertyGridProperty(L"z坐标",
			(_variant_t) eyeAt.z(), L"在世界坐标系下，摄像机位置的z轴坐标值。");
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
		HANDLE_GROUP_CAMERA_LOOKAT = new CMFCPropertyGridProperty(L"视点位置");
		//Set description.
		HANDLE_GROUP_CAMERA_LOOKAT->SetDescription(L"在世界坐标系下，摄像机视点的三维坐标。");

		//Create property.
		HANDLE_GROUP_CAMERA_LOOKAT_X = new CMFCPropertyGridProperty(L"x坐标",
			(_variant_t) lookAt.x(), L"在世界坐标系下，摄像机视点的x轴坐标值。");
		//Disable it.
		HANDLE_GROUP_CAMERA_LOOKAT_X->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_LOOKAT->AddSubItem(HANDLE_GROUP_CAMERA_LOOKAT_X);

		//Create property.
		HANDLE_GROUP_CAMERA_LOOKAT_Y = new CMFCPropertyGridProperty(L"y坐标",
			(_variant_t) lookAt.y(), L"在世界坐标系下，摄像机视点的y轴坐标值。");
		//Disable it.
		HANDLE_GROUP_CAMERA_LOOKAT_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_LOOKAT->AddSubItem(HANDLE_GROUP_CAMERA_LOOKAT_Y);

		//Create property.
		HANDLE_GROUP_CAMERA_LOOKAT_Z = new CMFCPropertyGridProperty(L"z坐标",
			(_variant_t) lookAt.z(), L"在世界坐标系下，摄像机视点的z轴坐标值。");
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
	HANDLE_GROUP_CAMERA_PROJECTION = new CMFCPropertyGridProperty(L"投影参数");
	//Set description.
	HANDLE_GROUP_CAMERA_PROJECTION->SetDescription(L"投影至二维平面所需要设置的相关参数。");
	
	{
		//Create property.
		HANDLE_GROUP_CAMERA_PROJECTION_FOV = new CMFCPropertyGridProperty(L"视角范围",
			(_variant_t) pViewPort->getFieldOfView(), L"摄像机的视角范围（Field of View）。");
		//Disable it.
		HANDLE_GROUP_CAMERA_PROJECTION_FOV->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_PROJECTION->AddSubItem(HANDLE_GROUP_CAMERA_PROJECTION_FOV);

		//Create property.
		HANDLE_GROUP_CAMERA_PROJECTION_ASPECT = new CMFCPropertyGridProperty(L"纵横比例",
			(_variant_t) pViewPort->getFAspect(), L"二维投影平面的纵横比例（Aspect Ratio）。");
		//Disable it.
		HANDLE_GROUP_CAMERA_PROJECTION_ASPECT->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_PROJECTION->AddSubItem(HANDLE_GROUP_CAMERA_PROJECTION_ASPECT);

		//Create property.
		HANDLE_GROUP_CAMERA_PROJECTION_ZFAR = new CMFCPropertyGridProperty(L"远裁剪距离",
			(_variant_t) pViewPort->getFarClip(), L"超过远裁剪距离(Z Far Distance）的物体就不显示。");
		//Disable it.
		HANDLE_GROUP_CAMERA_PROJECTION_ZFAR->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_PROJECTION->AddSubItem(HANDLE_GROUP_CAMERA_PROJECTION_ZFAR);

		//Create property.
		HANDLE_GROUP_CAMERA_PROJECTION_ZNEAR = new CMFCPropertyGridProperty(L"近裁剪距离",
			(_variant_t) pViewPort->getNearClip(), L"小于近裁剪距离(Z Near Distance）的物体就不显示。");
		//Disable it.
		HANDLE_GROUP_CAMERA_PROJECTION_ZNEAR->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_CAMERA_PROJECTION->AddSubItem(HANDLE_GROUP_CAMERA_PROJECTION_ZNEAR);

	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_CAMERA_PROJECTION);

	//Create property.
	HANDLE_GROUP_MOUSE = new CMFCPropertyGridProperty(L"鼠标位置");
	//Set description.
	HANDLE_GROUP_MOUSE->SetDescription(L"实时显示鼠标在窗口中的二维坐标位置。");

	{
		//Create property.
		HANDLE_GROUP_MOUSE_SCREEN_X = new CMFCPropertyGridProperty(L"x坐标",
			(_variant_t) pViewPort->getMouseX(),L"鼠标在屏幕窗口中的x坐标位置。");
		//Disable it.
		HANDLE_GROUP_MOUSE_SCREEN_X->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_MOUSE->AddSubItem(HANDLE_GROUP_MOUSE_SCREEN_X);

		//Create property.
		HANDLE_GROUP_MOUSE_SCREEN_Y = new CMFCPropertyGridProperty(L"y坐标",
			(_variant_t) pViewPort->getMouseY(),L"鼠标在屏幕窗口中的y坐标位置。");
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
