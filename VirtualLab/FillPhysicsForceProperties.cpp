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
// FillPhysicsForceProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillPhysicsForceProperties(CPhysicsObject* pPhysicsObject)
{
#ifdef _DEBUG
	assert(pPhysicsObject != NULL);
#endif

	//Create property.
	HANDLE_PHYSICS_FORCE = new CMFCPropertyGridProperty(L"����ţ�٣�");
	//Set description.
	HANDLE_PHYSICS_FORCE->SetDescription(L"�����������Ҫ���������Բ�����ע����λΪţ�١�");

	{
		//Get force.
		C4DVector3 force = pPhysicsObject->getForce();

		//Create property.
		HANDLE_PHYSICS_FORCE_X = new CMFCPropertyGridProperty(L"F��x��",
			(_variant_t) force.x(), L"��ȫ������ϵ�У���x�����᷽�������ע����λΪţ�١�");
		//Disable.
		HANDLE_PHYSICS_FORCE_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_FORCE->AddSubItem(HANDLE_PHYSICS_FORCE_X);

		//Create property.
		HANDLE_PHYSICS_FORCE_Y = new CMFCPropertyGridProperty(L"F��y��",
			(_variant_t) force.y(), L"��ȫ������ϵ�У���y�����᷽�������ע����λΪţ�١�");
		//Disable.
		HANDLE_PHYSICS_FORCE_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_FORCE->AddSubItem(HANDLE_PHYSICS_FORCE_Y);

		//Create property.
		HANDLE_PHYSICS_FORCE_Z = new CMFCPropertyGridProperty(L"F��z��",
			(_variant_t) force.z(), L"��ȫ������ϵ�У���z�����᷽�������ע����λΪţ�١�");
		//Disable.
		HANDLE_PHYSICS_FORCE_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_FORCE->AddSubItem(HANDLE_PHYSICS_FORCE_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_FORCE);

	//Create property.
	HANDLE_PHYSICS_TORQUE = new CMFCPropertyGridProperty(L"���أ�ţ�١��ף�");
	//Set description.
	HANDLE_PHYSICS_TORQUE->SetDescription(L"�����������Ҫ�����������Բ�����ע����λΪţ�١��ס�");

	{
		//Get torque.
		C4DVector3 torque = pPhysicsObject->getTorque();

		//Create property.
		HANDLE_PHYSICS_TORQUE_X = new CMFCPropertyGridProperty(L"�ӣ�x��",
			(_variant_t) torque.x(), L"��ȫ������ϵ�У���x�����᷽������ء�ע����λΪţ�١��ס�");
		//Disable.
		HANDLE_PHYSICS_TORQUE_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_TORQUE->AddSubItem(HANDLE_PHYSICS_TORQUE_X);

		//Create property.
		HANDLE_PHYSICS_TORQUE_Y = new CMFCPropertyGridProperty(L"�ӣ�y��",
			(_variant_t) torque.y(), L"��ȫ������ϵ�У���y�����᷽������ء�ע����λΪţ�١��ס�");
		//Disable.
		HANDLE_PHYSICS_TORQUE_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_TORQUE->AddSubItem(HANDLE_PHYSICS_TORQUE_Y);

		//Create property.
		HANDLE_PHYSICS_TORQUE_Z = new CMFCPropertyGridProperty(L"�ӣ�z��",
			(_variant_t) torque.z(), L"��ȫ������ϵ�У���z�����᷽������ء�ע����λΪţ�١��ס�");
		//Disable.
		HANDLE_PHYSICS_TORQUE_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_TORQUE->AddSubItem(HANDLE_PHYSICS_TORQUE_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_TORQUE);

	//Create property.
	HANDLE_PHYSICS_VELOCITY = new CMFCPropertyGridProperty(L"���ٶȣ���/�룩");
	//Set description.
	HANDLE_PHYSICS_VELOCITY->SetDescription(L"�����������Ҫ���ٶ����Բ�����ע����λΪ��/�롣");

	{
		//Get velocity.
		C4DVector3 velocity = pPhysicsObject->getVelocity();

		//Create property.
		HANDLE_PHYSICS_VELOCITY_X = new CMFCPropertyGridProperty(L"V��x��",
			(_variant_t) velocity.x(), L"��ȫ������ϵ�У���x�����᷽������ٶȡ�ע����λΪ��/�롣");
		//Disable.
		HANDLE_PHYSICS_VELOCITY_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_VELOCITY->AddSubItem(HANDLE_PHYSICS_VELOCITY_X);

		//Create property.
		HANDLE_PHYSICS_VELOCITY_Y = new CMFCPropertyGridProperty(L"V��y��",
			(_variant_t) velocity.y(), L"��ȫ������ϵ�У���y�����᷽������ٶȡ�ע����λΪ��/�롣");
		//Disable.
		HANDLE_PHYSICS_VELOCITY_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_VELOCITY->AddSubItem(HANDLE_PHYSICS_VELOCITY_Y);

		//Create property.
		HANDLE_PHYSICS_VELOCITY_Z = new CMFCPropertyGridProperty(L"V��z��",
			(_variant_t) velocity.z(), L"��ȫ������ϵ�У���z�����᷽������ٶȡ�ע����λΪ��/�롣");
		//Disable.
		HANDLE_PHYSICS_VELOCITY_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_VELOCITY->AddSubItem(HANDLE_PHYSICS_VELOCITY_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_VELOCITY);

	//Create property.
	HANDLE_PHYSICS_OMEGA = new CMFCPropertyGridProperty(L"���ٶȣ�����/�룩");
	//Set description.
	HANDLE_PHYSICS_OMEGA->SetDescription(L"�����������Ҫ�Ͻ��ٶ����Բ�����ע����λΪ����/�롣");

	{
		//Get omega.
		C4DVector3 omega = pPhysicsObject->getOmega();

		//Create property.
		HANDLE_PHYSICS_OMEGA_X = new CMFCPropertyGridProperty(L"�أ�x��",
			(_variant_t) omega.x(), L"��ȫ������ϵ�У���x�����᷽��Ľ��ٶȡ�ע����λΪ����/�롣");
		//Disable.
		HANDLE_PHYSICS_OMEGA_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_OMEGA->AddSubItem(HANDLE_PHYSICS_OMEGA_X);

		//Create property.
		HANDLE_PHYSICS_OMEGA_Y = new CMFCPropertyGridProperty(L"�أ�y��",
			(_variant_t) omega.y(), L"��ȫ������ϵ�У���y�����᷽��Ľ��ٶȡ�ע����λΪ����/�롣");
		//Disable.
		HANDLE_PHYSICS_OMEGA_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_OMEGA->AddSubItem(HANDLE_PHYSICS_OMEGA_Y);

		//Create property.
		HANDLE_PHYSICS_OMEGA_Z = new CMFCPropertyGridProperty(L"�أ�z��",
			(_variant_t) omega.z(), L"��ȫ������ϵ�У���z�����᷽��Ľ��ٶȡ�ע����λΪ����/�롣");
		//Disable.
		HANDLE_PHYSICS_OMEGA_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_OMEGA->AddSubItem(HANDLE_PHYSICS_OMEGA_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_OMEGA);

	//Create property.
	HANDLE_PHYSICS_ACCELERATION = new CMFCPropertyGridProperty(L"�߼��ٶȣ���/ƽ���룩");
	//Set description.
	HANDLE_PHYSICS_ACCELERATION->SetDescription(L"�����������Ҫ�߼��ٶ����Բ�����ע����λΪ��/ƽ���롣");

	{
		//Get acceleration.
		C4DVector3 acceleration = pPhysicsObject->getAcceleration();

		//Create property.
		HANDLE_PHYSICS_ACCELERATION_X = new CMFCPropertyGridProperty(L"A��x��",
			(_variant_t) acceleration.x(), L"��ȫ������ϵ�У���x�����᷽������ٶȡ�ע����λΪ��/ƽ���롣");
		//Disable.
		HANDLE_PHYSICS_ACCELERATION_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ACCELERATION->AddSubItem(HANDLE_PHYSICS_ACCELERATION_X);

		//Create property.
		HANDLE_PHYSICS_ACCELERATION_Y = new CMFCPropertyGridProperty(L"A��y��",
			(_variant_t) acceleration.y(), L"��ȫ������ϵ�У���y�����᷽������ٶȡ�ע����λΪ��/ƽ���롣");
		//Disable.
		HANDLE_PHYSICS_ACCELERATION_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ACCELERATION->AddSubItem(HANDLE_PHYSICS_ACCELERATION_Y);

		//Create property.
		HANDLE_PHYSICS_ACCELERATION_Z = new CMFCPropertyGridProperty(L"A��z��",
			(_variant_t) acceleration.z(), L"��ȫ������ϵ�У���z�����᷽������ٶȡ�ע����λΪ��/ƽ���롣");
		//Disable.
		HANDLE_PHYSICS_ACCELERATION_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ACCELERATION->AddSubItem(HANDLE_PHYSICS_ACCELERATION_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_ACCELERATION);

	//Create property.
	HANDLE_PHYSICS_ALPHA = new CMFCPropertyGridProperty(L"�Ǽ��ٶȣ�����/ƽ���룩");
	//Set description.
	HANDLE_PHYSICS_ALPHA->SetDescription(L"�����������Ҫ�߼��ٶ����Բ�����ע����λΪ����/ƽ���롣");

	{
		//Get alpha.
		C4DVector3 alpha = pPhysicsObject->getAlpha();

		//Create property.
		HANDLE_PHYSICS_ALPHA_X = new CMFCPropertyGridProperty(L"����x��",
			(_variant_t) alpha.x(), L"��ȫ������ϵ�У���x�����᷽��Ľ��ٶȡ�ע����λΪ����/ƽ���롣");
		//Disable.
		HANDLE_PHYSICS_ALPHA_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ALPHA->AddSubItem(HANDLE_PHYSICS_ALPHA_X);

		//Create property.
		HANDLE_PHYSICS_ALPHA_Y = new CMFCPropertyGridProperty(L"����y��",
			(_variant_t) alpha.y(), L"��ȫ������ϵ�У���y�����᷽��Ľ��ٶȡ�ע����λΪ����/ƽ���롣");
		//Disable.
		HANDLE_PHYSICS_ALPHA_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ALPHA->AddSubItem(HANDLE_PHYSICS_ALPHA_Y);

		//Create property.
		HANDLE_PHYSICS_ALPHA_Z = new CMFCPropertyGridProperty(L"����z��",
			(_variant_t) alpha.z(), L"��ȫ������ϵ�У���z�����᷽��Ľ��ٶȡ�ע����λΪ����/ƽ���롣");
		//Disable.
		HANDLE_PHYSICS_ALPHA_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ALPHA->AddSubItem(HANDLE_PHYSICS_ALPHA_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_ALPHA);
}
