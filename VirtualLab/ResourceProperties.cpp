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
#include "D3DXTexture.h"
#include "D3DXFileMesh.h"
#include "D3DXLinestrip.h"

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
// ShowProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ShowProperties(CD3DXResource* pResource)
{
#ifdef _DEBUG
	assert(pResource != NULL);
#endif

	//Check type.
	if(IS_DEVICE_BASE(pResource))
	{
		//Show properties .
		ShowProperties((CD3DXDevice *)pResource);
	}
	else if(IS_FILTER_BASE(pResource))
	{
		//Show properties .
		ShowProperties((CD3DXFilter *)pResource);
	}
	else if(IS_TEXTURE_BASE(pResource))
	{
		//Show properties .
		ShowProperties((CD3DXTexture *)pResource);
	}
	else if(IS_EFFECT_BASE(pResource))
	{
		//Show properties.
		ShowProperties((CD3DXEffect *)pResource);
	}
	else if(IS_FILEMESH_BASE(pResource))
	{
		//Show properties.
		ShowProperties((CD3DXFileMesh *)pResource);
	}
	else if(IS_LINESTRIP_BASE(pResource))
	{
		//Show properties.
		ShowProperties((CD3DXLinestrip *)pResource);
	}
	else if(IS_PRIMITIVE_BASE(pResource))
	{
		//Show properties.
		ShowProperties((CD3DXPrimitive *)pResource);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// FillBoxProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillBoxProperties(CD3DXRenderable* pRenderable)
{
	//Format.
	CString strFormat;

#ifdef _DEBUG
	assert(pRenderable != NULL);
#endif

	//Create property.
	HANDLE_GROUP_BOX = new CMFCPropertyGridProperty(L"包围盒");
	//Set description.
	HANDLE_GROUP_BOX->SetDescription(L"可绘制物体的各种形式包围盒参数");

	{
		//Sphere.
		CSimpleSphere sphere;
#ifndef _DEBUG
		//Get sphere.
		pRenderable->getSphere(sphere);
#else
		//Get sphere.
		assert(pRenderable->getSphere(sphere));
#endif

		//Create property.
		HANDLE_BOX_BALL = new CMFCPropertyGridProperty(L"球体");
		//Set description.
		HANDLE_BOX_BALL->SetDescription(L"在世界坐标系下，可绘制物体的球体包围盒参数。");
		//Add subitem.
		HANDLE_GROUP_BOX->AddSubItem(HANDLE_BOX_BALL);

		{
			//Create property.
			HANDLE_BOX_BALL_CENTER = new CMFCPropertyGridProperty(L"中心点");
			//Set description.
			HANDLE_BOX_BALL_CENTER->SetDescription(L"在世界坐标系下，球体包围盒中心点坐标参数。");
			//Add subitem.
			HANDLE_BOX_BALL->AddSubItem(HANDLE_BOX_BALL_CENTER);

			//Create property.
			HANDLE_BOX_BALL_CENTER_X = new CMFCPropertyGridProperty(L"x坐标",
				(_variant_t) sphere.x(), L"在世界坐标系下，球心点x坐标参数。");
			//Disable editable.
			HANDLE_BOX_BALL_CENTER_X->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_BALL_CENTER->AddSubItem(HANDLE_BOX_BALL_CENTER_X);

			//Create property.
			HANDLE_BOX_BALL_CENTER_Y = new CMFCPropertyGridProperty(L"y坐标",
				(_variant_t) sphere.y(), L"在世界坐标系下，球心点y坐标参数。");
			//Disable editable.
			HANDLE_BOX_BALL_CENTER_Y->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_BALL_CENTER->AddSubItem(HANDLE_BOX_BALL_CENTER_Y);

			//Create property.
			HANDLE_BOX_BALL_CENTER_Z = new CMFCPropertyGridProperty(L"z坐标",
				(_variant_t) sphere.z(), L"在世界坐标系下，球心点z坐标参数。");
			//Disable editable.
			HANDLE_BOX_BALL_CENTER_Z->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_BALL_CENTER->AddSubItem(HANDLE_BOX_BALL_CENTER_Z);
		}

		{
			//Create property.
			HANDLE_BOX_BALL_EXTEND = new CMFCPropertyGridProperty(L"尺寸");
			//Set description.
			HANDLE_BOX_BALL_EXTEND->SetDescription(L"在世界坐标系下，矩形包围盒的尺寸参数。");
			//Add subitem.
			HANDLE_BOX_BALL->AddSubItem(HANDLE_BOX_BALL_EXTEND);

			//Create property.
			HANDLE_BOX_BALL_EXTEND_R = new CMFCPropertyGridProperty(L"球半径",
				(_variant_t) sphere.r(), L"在世界坐标系下，球体包围盒的半径长度。");
			//Disable editable.
			HANDLE_BOX_BALL_EXTEND_R->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_BALL_EXTEND->AddSubItem(HANDLE_BOX_BALL_EXTEND_R);
		}
	}

	{
		//Box.
		CSimpleBox box;
#ifndef _DEBUG
		//Get box.
		pRenderable->getBox(box);
#else
		//Get box.
		assert(pRenderable->getBox(box));
#endif

		//Create property.
		HANDLE_BOX_AABOX = new CMFCPropertyGridProperty(L"矩形体");
		//Set description.
		HANDLE_BOX_AABOX->SetDescription(L"可绘制物体的矩形体包围盒参数。");
		//Add subitem
		HANDLE_GROUP_BOX->AddSubItem(HANDLE_BOX_AABOX);

		{
			//Create property.
			HANDLE_BOX_AABOX_CENTER = new CMFCPropertyGridProperty(L"中心点");
			//Set description.
			HANDLE_BOX_AABOX_CENTER->SetDescription(L"在世界坐标系下，矩形体中心点的三维坐标参数。");
			//Add subitem.
			HANDLE_BOX_AABOX->AddSubItem(HANDLE_BOX_AABOX_CENTER);

			//Create property.
			HANDLE_BOX_AABOX_CENTER_X = new CMFCPropertyGridProperty(L"x坐标",
				(_variant_t) box.x(), L"在世界坐标系下的x坐标值。");
			//Disable editable.
			HANDLE_BOX_AABOX_CENTER_X->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_CENTER->AddSubItem(HANDLE_BOX_AABOX_CENTER_X);

			//Create property.
			HANDLE_BOX_AABOX_CENTER_Y = new CMFCPropertyGridProperty(L"y坐标",
				(_variant_t) box.y(), L"在世界坐标系下的y坐标值。");
			//Disable editable.
			HANDLE_BOX_AABOX_CENTER_Y->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_CENTER->AddSubItem(HANDLE_BOX_AABOX_CENTER_Y);

			//Create property.
			HANDLE_BOX_AABOX_CENTER_Z = new CMFCPropertyGridProperty(L"z坐标",
				(_variant_t) box.z(), L"在世界坐标系下的z坐标值。");
			//Disable editable.
			HANDLE_BOX_AABOX_CENTER_Z->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_CENTER->AddSubItem(HANDLE_BOX_AABOX_CENTER_Z);
		}

		{
			//Create property.
			HANDLE_BOX_AABOX_EXTEND = new CMFCPropertyGridProperty(L"尺寸");
			//Set description.
			HANDLE_BOX_AABOX_EXTEND->SetDescription(L"在世界坐标系下，矩形体在三个维度上的尺寸参数。");
			//Add subitem.
			HANDLE_BOX_AABOX->AddSubItem(HANDLE_BOX_AABOX_EXTEND);

			//Format.
			strFormat.Format(L"±%f",box.dx());
			//Create property.
			HANDLE_BOX_AABOX_EXTEND_X = new CMFCPropertyGridProperty(L"x轴尺寸",
				strFormat, L"在世界坐标系下，矩形体沿x轴双向延伸尺寸。");
			//Disable editable.
			HANDLE_BOX_AABOX_EXTEND_X->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_EXTEND->AddSubItem(HANDLE_BOX_AABOX_EXTEND_X);

			//Format.
			strFormat.Format(L"±%f",box.dy());
			//Create property.
			HANDLE_BOX_AABOX_EXTEND_Y = new CMFCPropertyGridProperty(L"y轴尺寸",
				strFormat, L"在世界坐标系下，矩形体沿y轴双向延伸尺寸。");
			//Disable editable.
			HANDLE_BOX_AABOX_EXTEND_Y->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_EXTEND->AddSubItem(HANDLE_BOX_AABOX_EXTEND_Y);

			//Format.
			strFormat.Format(L"±%f",box.dz());
			//Create property.
			HANDLE_BOX_AABOX_EXTEND_Z = new CMFCPropertyGridProperty(L"z轴尺寸",
				strFormat, L"在世界坐标系下，矩形体沿z轴双向延伸尺寸。");
			//Disable editable.
			HANDLE_BOX_AABOX_EXTEND_Z->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_EXTEND->AddSubItem(HANDLE_BOX_AABOX_EXTEND_Z);
		}
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_BOX);
}
