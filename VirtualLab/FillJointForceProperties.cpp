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
// FillJointForceProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillJointForceProperties(CPhysicsJointObject* pJointObject)
{
#ifdef _DEBUG
	assert(pJointObject != NULL);
#endif

	//Create property.
	HANDLE_PHYSICS_JOINT_FORCE = new CMFCPropertyGridProperty(L"��Ժ�����ţ�٣�");
	//Set description.
	HANDLE_PHYSICS_JOINT_FORCE->SetDescription(L"���������ܵ���Ժ�����ע����λΪţ�١�");

	{
		//Get force.
		C4DVector3 force = pJointObject->getJointForce();

		//Create property.
		HANDLE_PHYSICS_JOINT_FORCE_X = new CMFCPropertyGridProperty(L"F��x��",
			(_variant_t) force.x(), L"����������ϵ�У���x�᷽��ĺ�����ע����λΪţ�١�");
		//Disable.
		HANDLE_PHYSICS_JOINT_FORCE_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_FORCE->AddSubItem(HANDLE_PHYSICS_JOINT_FORCE_X);

		//Create property.
		HANDLE_PHYSICS_JOINT_FORCE_Y = new CMFCPropertyGridProperty(L"F��y��",
			(_variant_t) force.y(), L"����������ϵ�У���y�᷽��ĺ�����ע����λΪţ�١�");
		//Disable.
		HANDLE_PHYSICS_JOINT_FORCE_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_FORCE->AddSubItem(HANDLE_PHYSICS_JOINT_FORCE_Y);

		//Create property.
		HANDLE_PHYSICS_JOINT_FORCE_Z = new CMFCPropertyGridProperty(L"F��z��",
			(_variant_t) force.z(), L"����������ϵ�У���z�᷽��ĺ�����ע����λΪţ�١�");
		//Disable.
		HANDLE_PHYSICS_JOINT_FORCE_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_FORCE->AddSubItem(HANDLE_PHYSICS_JOINT_FORCE_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_JOINT_FORCE);

	//Create property.
	HANDLE_PHYSICS_JOINT_POSITION = new CMFCPropertyGridProperty(L"���λ�ã��ף�");
	//Set description.
	HANDLE_PHYSICS_JOINT_POSITION->SetDescription(L"������ĸ�����֮������λ�á�ע����λΪ�ס�");

	{
		//Get position.
		C4DVector3 position = pJointObject->getRelativePosition();

		//Create property.
		HANDLE_PHYSICS_JOINT_POSITION_X = new CMFCPropertyGridProperty(L"P��x��",
			(_variant_t) position.x(), L"�ھֲ�����ϵ�У���x�����Ծ��롣ע����λΪ�ס�");
		//Disable.
		HANDLE_PHYSICS_JOINT_POSITION_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_POSITION->AddSubItem(HANDLE_PHYSICS_JOINT_POSITION_X);

		//Create property.
		HANDLE_PHYSICS_JOINT_POSITION_Y = new CMFCPropertyGridProperty(L"P��y��",
			(_variant_t) position.y(), L"�ھֲ�����ϵ�У���y�����Ծ��롣ע����λΪ�ס�");
		//Disable.
		HANDLE_PHYSICS_JOINT_POSITION_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_POSITION->AddSubItem(HANDLE_PHYSICS_JOINT_POSITION_Y);

		//Create property.
		HANDLE_PHYSICS_JOINT_POSITION_Z = new CMFCPropertyGridProperty(L"P��z��",
			(_variant_t) position.z(), L"�ھֲ�����ϵ�У���z�����Ծ��롣ע����λΪ�ס�");
		//Disable.
		HANDLE_PHYSICS_JOINT_POSITION_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_POSITION->AddSubItem(HANDLE_PHYSICS_JOINT_POSITION_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_JOINT_POSITION);

	//Create property.
	HANDLE_PHYSICS_JOINT_VELOCITY = new CMFCPropertyGridProperty(L"����ٶȣ���/�룩");
	//Set description.
	HANDLE_PHYSICS_JOINT_VELOCITY->SetDescription(L"������ĸ�����֮�������ٶȡ�ע����λΪ��/�롣");

	{
		//Get velocity.
		C4DVector3 velocity = pJointObject->getRelativeVelocity();

		//Create property.
		HANDLE_PHYSICS_JOINT_VELOCITY_X = new CMFCPropertyGridProperty(L"V��x��",
			(_variant_t) velocity.x(), L"�ھֲ�����ϵ�У���z�������ٶȡ�ע����λΪ��/�롣");
		//Disable.
		HANDLE_PHYSICS_JOINT_VELOCITY_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_VELOCITY->AddSubItem(HANDLE_PHYSICS_JOINT_VELOCITY_X);

		//Create property.
		HANDLE_PHYSICS_JOINT_VELOCITY_Y = new CMFCPropertyGridProperty(L"V��y��",
			(_variant_t) velocity.y(), L"�ھֲ�����ϵ�У���y�������ٶȡ�ע����λΪ��/�롣");
		//Disable.
		HANDLE_PHYSICS_JOINT_VELOCITY_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_VELOCITY->AddSubItem(HANDLE_PHYSICS_JOINT_VELOCITY_Y);

		//Create property.
		HANDLE_PHYSICS_JOINT_VELOCITY_Z = new CMFCPropertyGridProperty(L"V��z��",
			(_variant_t) velocity.z(), L"�ھֲ�����ϵ�У���z�������ٶȡ�ע����λΪ��/�롣");
		//Disable.
		HANDLE_PHYSICS_JOINT_VELOCITY_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_VELOCITY->AddSubItem(HANDLE_PHYSICS_JOINT_VELOCITY_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_JOINT_VELOCITY);

	//Create property.
	HANDLE_PHYSICS_JOINT_ANGLE = new CMFCPropertyGridProperty(L"���ת�ǣ��Ƕȣ�");
	//Set description.
	HANDLE_PHYSICS_JOINT_ANGLE->SetDescription(L"������ĸ�����֮������ת�ǡ�ע����λΪ�Ƕȡ�");

	{
		//Get angle.
		C4DVector3 angle = pJointObject->getRelativeAngle();
		//Change it into eular angle.
		angle = angle * 180.0f / D3DX_PI;

		//Create property.
		HANDLE_PHYSICS_JOINT_ANGLE_X = new CMFCPropertyGridProperty(L"�գ�x��",
			(_variant_t) angle.x(), L"�ھֲ�����ϵ�У���x������ת�ǡ�ע����λΪ�Ƕȡ�");
		//Disable.
		HANDLE_PHYSICS_JOINT_ANGLE_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_ANGLE->AddSubItem(HANDLE_PHYSICS_JOINT_ANGLE_X);

		//Create property.
		HANDLE_PHYSICS_JOINT_ANGLE_Y = new CMFCPropertyGridProperty(L"�ȣ�y��",
			(_variant_t) angle.y(), L"�ھֲ�����ϵ�У���y������ת�ǡ�ע����λΪ�Ƕȡ�");
		//Disable.
		HANDLE_PHYSICS_JOINT_ANGLE_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_ANGLE->AddSubItem(HANDLE_PHYSICS_JOINT_ANGLE_Y);

		//Create property.
		HANDLE_PHYSICS_JOINT_ANGLE_Z = new CMFCPropertyGridProperty(L"�ף�z��",
			(_variant_t) angle.z(), L"�ھֲ�����ϵ�У���z������ת�ǡ�ע����λΪ�Ƕȡ�");
		//Disable.
		HANDLE_PHYSICS_JOINT_ANGLE_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_ANGLE->AddSubItem(HANDLE_PHYSICS_JOINT_ANGLE_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_JOINT_ANGLE);

	//Create property.
	HANDLE_PHYSICS_JOINT_OMEGA = new CMFCPropertyGridProperty(L"��Խ��ٶȣ��Ƕ�/�룩");
	//Set description.
	HANDLE_PHYSICS_JOINT_OMEGA->SetDescription(L"������ĸ�����֮�����Խ��ٶȡ�ע����λΪ�Ƕ�/�롣");

	{
		//Get omega.
		C4DVector3 omega = pJointObject->getRelativeOmega();
		//Change it into eular angle.
		omega = omega * 180.0f / D3DX_PI;

		//Create property.
		HANDLE_PHYSICS_JOINT_OMEGA_X = new CMFCPropertyGridProperty(L"�أ�x��",
			(_variant_t) omega.x(), L"�ھֲ�����ϵ�У���x�����Խ��ٶȡ�ע����λΪ�Ƕ�/�롣");
		//Disable.
		HANDLE_PHYSICS_JOINT_OMEGA_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_OMEGA->AddSubItem(HANDLE_PHYSICS_JOINT_OMEGA_X);

		//Create property.
		HANDLE_PHYSICS_JOINT_OMEGA_Y = new CMFCPropertyGridProperty(L"�أ�y��",
			(_variant_t) omega.y(), L"�ھֲ�����ϵ�У���y�����Խ��ٶȡ�ע����λΪ�Ƕ�/�롣");
		//Disable.
		HANDLE_PHYSICS_JOINT_OMEGA_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_OMEGA->AddSubItem(HANDLE_PHYSICS_JOINT_OMEGA_Y);

		//Create property.
		HANDLE_PHYSICS_JOINT_OMEGA_Z = new CMFCPropertyGridProperty(L"�أ�z��",
			(_variant_t) omega.z(), L"�ھֲ�����ϵ�У���z�����Խ��ٶȡ�ע����λΪ�Ƕ�/�롣");
		//Disable.
		HANDLE_PHYSICS_JOINT_OMEGA_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_OMEGA->AddSubItem(HANDLE_PHYSICS_JOINT_OMEGA_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_JOINT_OMEGA);
}
