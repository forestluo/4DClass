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
// FillPhysicsProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillPhysicsProperties(CPhysicsObject* pPhysicsObject)
{
#ifdef _DEBUG
	assert(pPhysicsObject != NULL);
#endif

	//Create property.
	HANDLE_PHYSICS_GENERAL = new CMFCPropertyGridProperty(L"��Ҫ");
	//Set description.
	HANDLE_PHYSICS_GENERAL->SetDescription(L"�����������Ҫ���������");

	{
		//Mass.
		float mass = pPhysicsObject->getMass();

		//Create property.
		HANDLE_PHYSICS_GENERAL_MASS = new CMFCPropertyGridProperty(L"������ǧ�ˣ�",
			(_variant_t) mass, L"���������������ע����λΪǧ�ˡ�");
		//Enable editable.
		HANDLE_PHYSICS_GENERAL_MASS->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_GENERAL->AddSubItem(HANDLE_PHYSICS_GENERAL_MASS);

		//Create property.
		HANDLE_PHYSICS_GENERAL_VOLUMN = new CMFCPropertyGridProperty(L"����������ף�",
			(_variant_t) 1.0f, L"��������������ע����λΪ�����ס�");
		//Disable editable.
		HANDLE_PHYSICS_GENERAL_VOLUMN->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_GENERAL->AddSubItem(HANDLE_PHYSICS_GENERAL_VOLUMN);

		//Create property.
		HANDLE_PHYSICS_GENERAL_DENSITY = new CMFCPropertyGridProperty(L"�ܶȣ�ǧ��/�����ף�",
			(_variant_t) 1.0f, L"����������ܶȡ�ע����λΪǧ��/�����ס�");
		//Disable editable.
		HANDLE_PHYSICS_GENERAL_DENSITY->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_GENERAL->AddSubItem(HANDLE_PHYSICS_GENERAL_DENSITY);

	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_GENERAL);

	//Create property.
	HANDLE_PHYSICS_GENERAL_INERTIA = new CMFCPropertyGridProperty(L"ת��������ǧ�ˡ�ƽ���ף�");
	//Set description.
	HANDLE_PHYSICS_GENERAL_INERTIA->SetDescription(L"���������ת��������ע����λΪǧ�ˡ�ƽ���ס�");

	{
		//Get inertia.
		C4DVector3 inertia = pPhysicsObject->getInertia();

		//Create property.
		HANDLE_PHYSICS_GENERAL_INERTIA_IXX = new CMFCPropertyGridProperty(L"��xx",
			(_variant_t) inertia.x(), L"����������x����ת��ת��������ע����λΪǧ�ˡ�ƽ���ס�");
		//Enable editable.
		HANDLE_PHYSICS_GENERAL_INERTIA_IXX->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_GENERAL_INERTIA->AddSubItem(HANDLE_PHYSICS_GENERAL_INERTIA_IXX);

		//Create property.
		HANDLE_PHYSICS_GENERAL_INERTIA_IYY = new CMFCPropertyGridProperty(L"��yy",
			(_variant_t) inertia.y(), L"����������y����ת��ת��������ע����λΪǧ�ˡ�ƽ���ס�");
		//Disable editable.
		HANDLE_PHYSICS_GENERAL_INERTIA_IYY->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_GENERAL_INERTIA->AddSubItem(HANDLE_PHYSICS_GENERAL_INERTIA_IYY);

		//Create property.
		HANDLE_PHYSICS_GENERAL_INERTIA_IZZ = new CMFCPropertyGridProperty(L"��zz",
			(_variant_t) inertia.z(), L"����������z����ת��ת��������ע����λΪǧ�ˡ�ƽ���ס�");
		//Disable editable.
		HANDLE_PHYSICS_GENERAL_INERTIA_IZZ->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_GENERAL_INERTIA->AddSubItem(HANDLE_PHYSICS_GENERAL_INERTIA_IZZ);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_GENERAL_INERTIA);
}
