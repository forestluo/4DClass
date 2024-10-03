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
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define MAINFRAME											((CMainFrame *)GetTopLevelFrame())

///////////////////////////////////////////////////////////////////////////////
//
// FillBoxProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillBoxProperties(CD3DXRenderableObject* pRenderableObject)
{
	//Format.
	CString strFormat;

#ifdef _DEBUG
	assert(pRenderableObject != NULL);
#endif

	//Create property.
	HANDLE_GROUP_BOX = new CMFCPropertyGridProperty(L"��Χ��");
	//Set description.
	HANDLE_GROUP_BOX->SetDescription(L"����������ϵ�£��ɻ�������ĸ��ְ�Χ�в�����");

	{
		//Get sphere.
		CSimpleSphere sphere;
#ifndef _DEBUG
		pRenderableObject->getWorldSphere(sphere);
#else
		assert(pRenderableObject->getWorldSphere(sphere));
#endif

		//Create property.
		HANDLE_BOX_BALL = new CMFCPropertyGridProperty(L"����");
		//Set description.
		HANDLE_BOX_BALL->SetDescription(L"����������ϵ�£��ɻ�������������Χ�в�����");
		//Add subitem.
		HANDLE_GROUP_BOX->AddSubItem(HANDLE_BOX_BALL);

		{
			//Create property.
			HANDLE_BOX_BALL_CENTER = new CMFCPropertyGridProperty(L"���ĵ�");
			//Set description.
			HANDLE_BOX_BALL_CENTER->SetDescription(L"����������ϵ�£������Χ�����ĵ����������");
			//Add subitem.
			HANDLE_BOX_BALL->AddSubItem(HANDLE_BOX_BALL_CENTER);

			//Create property.
			HANDLE_BOX_BALL_CENTER_X = new CMFCPropertyGridProperty(L"x����",
				(_variant_t) sphere.x(), L"����������ϵ�£����ĵ�x���������");
			//Disable editable.
			HANDLE_BOX_BALL_CENTER_X->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_BALL_CENTER->AddSubItem(HANDLE_BOX_BALL_CENTER_X);

			//Create property.
			HANDLE_BOX_BALL_CENTER_Y = new CMFCPropertyGridProperty(L"y����",
				(_variant_t) sphere.y(), L"����������ϵ�£����ĵ�y���������");
			//Disable editable.
			HANDLE_BOX_BALL_CENTER_Y->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_BALL_CENTER->AddSubItem(HANDLE_BOX_BALL_CENTER_Y);

			//Create property.
			HANDLE_BOX_BALL_CENTER_Z = new CMFCPropertyGridProperty(L"z����",
				(_variant_t) sphere.z(), L"����������ϵ�£����ĵ�z���������");
			//Disable editable.
			HANDLE_BOX_BALL_CENTER_Z->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_BALL_CENTER->AddSubItem(HANDLE_BOX_BALL_CENTER_Z);
		}

		{
			//Create property.
			HANDLE_BOX_BALL_EXTEND = new CMFCPropertyGridProperty(L"�ߴ�");
			//Set description.
			HANDLE_BOX_BALL_EXTEND->SetDescription(L"����������ϵ�£����ΰ�Χ�еĳߴ������");
			//Add subitem.
			HANDLE_BOX_BALL->AddSubItem(HANDLE_BOX_BALL_EXTEND);

			//Create property.
			HANDLE_BOX_BALL_EXTEND_R = new CMFCPropertyGridProperty(L"��뾶",
				(_variant_t) sphere.r(), L"����������ϵ�£������Χ�еİ뾶���ȡ�");
			//Disable editable.
			HANDLE_BOX_BALL_EXTEND_R->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_BALL_EXTEND->AddSubItem(HANDLE_BOX_BALL_EXTEND_R);
		}
	}

	{
		//Get box.
		CSimpleBox box;
#ifndef _DEBUG
		pRenderableObject->getWorldBox(box);
#else
		assert(pRenderableObject->getWorldBox(box));
#endif

		//Create property.
		HANDLE_BOX_AABOX = new CMFCPropertyGridProperty(L"������");
		//Set description.
		HANDLE_BOX_AABOX->SetDescription(L"����������ϵ�£��ɻ�������ľ��ΰ�Χ�в�����");
		//Add subitem
		HANDLE_GROUP_BOX->AddSubItem(HANDLE_BOX_AABOX);

		{
			//Create property.
			HANDLE_BOX_AABOX_CENTER = new CMFCPropertyGridProperty(L"���ĵ�");
			//Set description.
			HANDLE_BOX_AABOX_CENTER->SetDescription(L"����������ϵ�£����ΰ�Χ�����ĵ����������");
			//Add subitem.
			HANDLE_BOX_AABOX->AddSubItem(HANDLE_BOX_AABOX_CENTER);

			//Create property.
			HANDLE_BOX_AABOX_CENTER_X = new CMFCPropertyGridProperty(L"x����",
				(_variant_t) box.x(), L"����������ϵ�£����ΰ�Χ�����ĵ�x����ֵ��");
			//Disable editable.
			HANDLE_BOX_AABOX_CENTER_X->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_CENTER->AddSubItem(HANDLE_BOX_AABOX_CENTER_X);

			//Create property.
			HANDLE_BOX_AABOX_CENTER_Y = new CMFCPropertyGridProperty(L"y����",
				(_variant_t) box.y(), L"����������ϵ�£����ΰ�Χ�����ĵ�y����ֵ��");
			//Disable editable.
			HANDLE_BOX_AABOX_CENTER_Y->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_CENTER->AddSubItem(HANDLE_BOX_AABOX_CENTER_Y);

			//Create property.
			HANDLE_BOX_AABOX_CENTER_Z = new CMFCPropertyGridProperty(L"z����",
				(_variant_t) box.z(), L"����������ϵ�£����ΰ�Χ�����ĵ�z����ֵ��");
			//Disable editable.
			HANDLE_BOX_AABOX_CENTER_Z->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_CENTER->AddSubItem(HANDLE_BOX_AABOX_CENTER_Z);
		}

		{
			//Create property.
			HANDLE_BOX_AABOX_EXTEND = new CMFCPropertyGridProperty(L"�ߴ�");
			//Set description.
			HANDLE_BOX_AABOX_EXTEND->SetDescription(L"����������ϵ�£����ΰ�Χ�еĳߴ������");
			//Add subitem.
			HANDLE_BOX_AABOX->AddSubItem(HANDLE_BOX_AABOX_EXTEND);

			//Format.
			strFormat.Format(_FORMAT_FLOAT_,box.dx());
			//Create property.
			HANDLE_BOX_AABOX_EXTEND_X = new CMFCPropertyGridProperty(L"x��ߴ�",
				strFormat, L"����������ϵ�£����ΰ�Χ�е���x��ߴ�ֵ��");
			//Disable editable.
			HANDLE_BOX_AABOX_EXTEND_X->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_EXTEND->AddSubItem(HANDLE_BOX_AABOX_EXTEND_X);

			//Format.
			strFormat.Format(_FORMAT_FLOAT_,box.dy());
			//Create property.
			HANDLE_BOX_AABOX_EXTEND_Y = new CMFCPropertyGridProperty(L"y��ߴ�",
				strFormat, L"����������ϵ�£����ΰ�Χ�е���y��ߴ�ֵ��");
			//Disable editable.
			HANDLE_BOX_AABOX_EXTEND_Y->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_EXTEND->AddSubItem(HANDLE_BOX_AABOX_EXTEND_Y);

			//Format.
			strFormat.Format(_FORMAT_FLOAT_,box.dz());
			//Create property.
			HANDLE_BOX_AABOX_EXTEND_Z = new CMFCPropertyGridProperty(L"z��ߴ�",
				strFormat, L"����������ϵ�£����ΰ�Χ�е���z��ߴ�ֵ��");
			//Disable editable.
			HANDLE_BOX_AABOX_EXTEND_Z->Enable(FALSE);
			//Add subitem.
			HANDLE_BOX_AABOX_EXTEND->AddSubItem(HANDLE_BOX_AABOX_EXTEND_Z);
		}
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_BOX);
}
