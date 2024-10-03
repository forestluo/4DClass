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

#include "HAARFilter.h"

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

//Filter
const LPCTSTR FILTER_PROPERTIES[] =
{
	PROPERTY_GENERAL
};

///////////////////////////////////////////////////////////////////////////////
//
// ShowProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ShowProperties(CD3DXFilter* pFilter)
{
#ifdef _DEBUG
	assert(pFilter != NULL);
#endif
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check result.
		if(pDoc != NULL && pDoc->application != NULL) pDoc->application->setFocused(pFilter);
	}
	//Set selected property page.
	nSelectedPropertyPage = 0;
	//Set window text.
	SetWindowTextW(pFilter->getName().getCString());

	//Clear property handles.
	ClearHandles();
	//Remove all previous elements.
	m_wndPropList.RemoveAll();
	//Remove all selections.
	m_wndObjectCombo.ResetContent();
	//Add properties.
	for(int i = 0;i < sizeof(FILTER_PROPERTIES) / sizeof(LPCTSTR);i ++)
	{
		//Add string.
		m_wndObjectCombo.AddString(FILTER_PROPERTIES[i]);
	}
	//Set current selection.
	m_wndObjectCombo.SetCurSel(PROPERTY_GENERAL_SELECTION);

	//Fill properties.
	FillProperties(pFilter);
	//Check instance.
	if(IS_HAARFILTER_BASE(pFilter))
	{
		//Fill properties.
		FillHAARProperties(pFilter);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// FillProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillProperties(CD3DXFilter* pFilter)
{
#ifdef _DEBUG
	assert(pFilter != NULL);
#endif

	//Create major.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"��Ҫ����");

	//Create property.
	HANDLE_NAME = new CMFCPropertyGridProperty(L"����",
		pFilter->getName().getCString(), L"�����豸���ڲ����ơ�");
	HANDLE_NAME->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_NAME);

	//Check type.
	if(IS_HAARFILTER_BASE(pFilter))
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",
			L"HAAR����ʶ��", L"�����豸���ڲ�����");
	}
	else
	{
		//Create property.
		HANDLE_TYPE = new CMFCPropertyGridProperty(L"����",
			L"δ֪�豸����", L"�����豸���ڲ�����");
	}
	HANDLE_TYPE->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_TYPE);

	//Create property.
	HANDLE_REFERENCED_COUNT = new CMFCPropertyGridProperty(L"���ô���",
		(_variant_t) pFilter->countReference(), L"������ͼ���ⲿ���õĴ�����");
	HANDLE_REFERENCED_COUNT->Enable(FALSE);
	HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_REFERENCED_COUNT);

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);
}

///////////////////////////////////////////////////////////////////////////////
//
// FillHAARProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillHAARProperties(CD3DXFilter* pFilter)
{
	//Get device.
	CHAARFilter* pHAARFilter = (CHAARFilter *)pFilter;
#ifdef _DEBUG
	assert(pFilter != NULL && IS_HAARFILTER_BASE(pFilter));
#endif

	//Create property.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"������");
	//Set description.
	HANDLE_GROUP_MAJOR->SetDescription(L"HAAR����������Ҫ������");

	{
		//Get device.
		CD3DXDevice* device = pHAARFilter->getDevice();

		//Create property.
		HANDLE_HAAR_DEVICE = new CMFCPropertyGridProperty(L"����Դ",
			(_variant_t) (device != _NULL ? device->getName().getCString() : L""), L"HAAR��������Դ�豸���ơ�");
		//Check main frame.
		if(MAINFRAME != NULL)
		{
			//Get doc.
			CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
			//Check result.
			if(pDoc != NULL) pDoc->addDeviceOptions(HANDLE_HAAR_DEVICE);
		}
		//Disable it.
		HANDLE_HAAR_DEVICE->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_HAAR_DEVICE);

		//Create property.
		HANDLE_HAAR_DETECTING = new CMFCPropertyGridProperty(L"���ڼ��",
			(_variant_t) (pHAARFilter->isDetecting() ? true : false), L"HAAR���������Ƿ����ڼ�⡣");
		//Disable it.
		HANDLE_HAAR_DETECTING->Enable(TRUE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_HAAR_DETECTING);

		//Create property.
		HANDLE_HAAR_TRACKING = new CMFCPropertyGridProperty(L"���ڸ���",
			(_variant_t) (pHAARFilter->isFaceTracking() ? true : false), L"HAAR���������Ƿ����ڸ��١�");
		//Disable it.
		HANDLE_HAAR_TRACKING->Enable(TRUE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_HAAR_TRACKING);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Create property.
	HANDLE_HAAR_FACE = new CMFCPropertyGridProperty(L"����");
	//Set description.
	HANDLE_HAAR_FACE->SetDescription(L"���屻��������Ҫ������");

	{
		//Create property.
		HANDLE_HAAR_FACE_CENTER = new CMFCPropertyGridProperty(L"�沿����");
		//Set description.
		HANDLE_HAAR_FACE_CENTER->SetDescription(L"���屻�������沿����λ�á�");
		//Add subitem.
		HANDLE_HAAR_FACE->AddSubItem(HANDLE_HAAR_FACE_CENTER);

		{
			//Center position.
			_INTEGER x = 0,y = 0;
			//Get center position.
			pHAARFilter->getFaceCenter(x,y);

			//Create property.
			HANDLE_HAAR_FACE_CENTER_X = new CMFCPropertyGridProperty(L"x���꣨���أ�",
				(_variant_t) x, L"���屻�������沿����x���ꡣע����λΪ���ء�");
			//Disable it.
			HANDLE_HAAR_FACE_CENTER_X->Enable(FALSE);
			//Add subitem.
			HANDLE_HAAR_FACE_CENTER->AddSubItem(HANDLE_HAAR_FACE_CENTER_X);

			//Create property.
			HANDLE_HAAR_FACE_CENTER_Y = new CMFCPropertyGridProperty(L"y���꣨���أ�",
				(_variant_t) y, L"���屻�������沿����y���ꡣע����λΪ���ء�");
			//Disable it.
			HANDLE_HAAR_FACE_CENTER_Y->Enable(FALSE);
			//Add subitem.
			HANDLE_HAAR_FACE_CENTER->AddSubItem(HANDLE_HAAR_FACE_CENTER_Y);
		}

	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_HAAR_FACE);

	//Create property.
	HANDLE_HAAR_BALL = new CMFCPropertyGridProperty(L"������");
	//Set description.
	HANDLE_HAAR_BALL->SetDescription(L"���������Ҫ������");

	{
		//Create property.
		HANDLE_HAAR_BALL_ROTATION = new CMFCPropertyGridProperty(L"��ת����");
		//Set description.
		HANDLE_HAAR_BALL_ROTATION->SetDescription(L"���������ת������");
		//Add subitem.
		HANDLE_HAAR_BALL->AddSubItem(HANDLE_HAAR_BALL_ROTATION);

		{
			//Get eular.
			C4DVector3 angle = pHAARFilter->getBallRotation().eular() * 180.0f / D3DX_PI;

			//Create property.
			HANDLE_HAAR_BALL_ROTATION_X = new CMFCPropertyGridProperty(L"x����ת�Ƕ�",
				(_variant_t) angle.x(), L"��������x����ת�ĽǶȡ�ע����λΪ�Ƕȡ�");
			//Disable it.
			HANDLE_HAAR_BALL_ROTATION_X->Enable(FALSE);
			//Add subitem.
			HANDLE_HAAR_BALL_ROTATION->AddSubItem(HANDLE_HAAR_BALL_ROTATION_X);

			//Create property.
			HANDLE_HAAR_BALL_ROTATION_Y = new CMFCPropertyGridProperty(L"y����ת�Ƕ�",
				(_variant_t) angle.y(), L"��������y����ת�ĽǶȡ�ע����λΪ�Ƕȡ�");
			//Disable it.
			HANDLE_HAAR_BALL_ROTATION_Y->Enable(FALSE);
			//Add subitem.
			HANDLE_HAAR_BALL_ROTATION->AddSubItem(HANDLE_HAAR_BALL_ROTATION_Y);

			//Create property.
			HANDLE_HAAR_BALL_ROTATION_Z = new CMFCPropertyGridProperty(L"z����ת�Ƕ�",
				(_variant_t) angle.z(), L"��������y����ת�ĽǶȡ�ע����λΪ�Ƕȡ�");
			//Disable it.
			HANDLE_HAAR_BALL_ROTATION_Z->Enable(FALSE);
			//Add subitem.
			HANDLE_HAAR_BALL_ROTATION->AddSubItem(HANDLE_HAAR_BALL_ROTATION_Z);
		}
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_HAAR_BALL);
}
