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
	HANDLE_PHYSICS_FORCE = new CMFCPropertyGridProperty(L"力（牛顿）");
	//Set description.
	HANDLE_PHYSICS_FORCE->SetDescription(L"物理物体的主要合外力属性参数。注：单位为牛顿。");

	{
		//Get force.
		C4DVector3 force = pPhysicsObject->getForce();

		//Create property.
		HANDLE_PHYSICS_FORCE_X = new CMFCPropertyGridProperty(L"F（x）",
			(_variant_t) force.x(), L"在全局坐标系中，沿x坐标轴方向的力。注：单位为牛顿。");
		//Disable.
		HANDLE_PHYSICS_FORCE_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_FORCE->AddSubItem(HANDLE_PHYSICS_FORCE_X);

		//Create property.
		HANDLE_PHYSICS_FORCE_Y = new CMFCPropertyGridProperty(L"F（y）",
			(_variant_t) force.y(), L"在全局坐标系中，沿y坐标轴方向的力。注：单位为牛顿。");
		//Disable.
		HANDLE_PHYSICS_FORCE_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_FORCE->AddSubItem(HANDLE_PHYSICS_FORCE_Y);

		//Create property.
		HANDLE_PHYSICS_FORCE_Z = new CMFCPropertyGridProperty(L"F（z）",
			(_variant_t) force.z(), L"在全局坐标系中，沿z坐标轴方向的力。注：单位为牛顿。");
		//Disable.
		HANDLE_PHYSICS_FORCE_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_FORCE->AddSubItem(HANDLE_PHYSICS_FORCE_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_FORCE);

	//Create property.
	HANDLE_PHYSICS_TORQUE = new CMFCPropertyGridProperty(L"力矩（牛顿·米）");
	//Set description.
	HANDLE_PHYSICS_TORQUE->SetDescription(L"物理物体的主要合外力矩属性参数。注：单位为牛顿·米。");

	{
		//Get torque.
		C4DVector3 torque = pPhysicsObject->getTorque();

		//Create property.
		HANDLE_PHYSICS_TORQUE_X = new CMFCPropertyGridProperty(L"τ（x）",
			(_variant_t) torque.x(), L"在全局坐标系中，绕x坐标轴方向的力矩。注：单位为牛顿·米。");
		//Disable.
		HANDLE_PHYSICS_TORQUE_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_TORQUE->AddSubItem(HANDLE_PHYSICS_TORQUE_X);

		//Create property.
		HANDLE_PHYSICS_TORQUE_Y = new CMFCPropertyGridProperty(L"τ（y）",
			(_variant_t) torque.y(), L"在全局坐标系中，绕y坐标轴方向的力矩。注：单位为牛顿·米。");
		//Disable.
		HANDLE_PHYSICS_TORQUE_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_TORQUE->AddSubItem(HANDLE_PHYSICS_TORQUE_Y);

		//Create property.
		HANDLE_PHYSICS_TORQUE_Z = new CMFCPropertyGridProperty(L"τ（z）",
			(_variant_t) torque.z(), L"在全局坐标系中，绕z坐标轴方向的力矩。注：单位为牛顿·米。");
		//Disable.
		HANDLE_PHYSICS_TORQUE_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_TORQUE->AddSubItem(HANDLE_PHYSICS_TORQUE_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_TORQUE);

	//Create property.
	HANDLE_PHYSICS_VELOCITY = new CMFCPropertyGridProperty(L"线速度（米/秒）");
	//Set description.
	HANDLE_PHYSICS_VELOCITY->SetDescription(L"物理物体的主要线速度属性参数。注：单位为米/秒。");

	{
		//Get velocity.
		C4DVector3 velocity = pPhysicsObject->getVelocity();

		//Create property.
		HANDLE_PHYSICS_VELOCITY_X = new CMFCPropertyGridProperty(L"V（x）",
			(_variant_t) velocity.x(), L"在全局坐标系中，沿x坐标轴方向的线速度。注：单位为米/秒。");
		//Disable.
		HANDLE_PHYSICS_VELOCITY_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_VELOCITY->AddSubItem(HANDLE_PHYSICS_VELOCITY_X);

		//Create property.
		HANDLE_PHYSICS_VELOCITY_Y = new CMFCPropertyGridProperty(L"V（y）",
			(_variant_t) velocity.y(), L"在全局坐标系中，沿y坐标轴方向的线速度。注：单位为米/秒。");
		//Disable.
		HANDLE_PHYSICS_VELOCITY_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_VELOCITY->AddSubItem(HANDLE_PHYSICS_VELOCITY_Y);

		//Create property.
		HANDLE_PHYSICS_VELOCITY_Z = new CMFCPropertyGridProperty(L"V（z）",
			(_variant_t) velocity.z(), L"在全局坐标系中，沿z坐标轴方向的线速度。注：单位为米/秒。");
		//Disable.
		HANDLE_PHYSICS_VELOCITY_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_VELOCITY->AddSubItem(HANDLE_PHYSICS_VELOCITY_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_VELOCITY);

	//Create property.
	HANDLE_PHYSICS_OMEGA = new CMFCPropertyGridProperty(L"角速度（弧度/秒）");
	//Set description.
	HANDLE_PHYSICS_OMEGA->SetDescription(L"物理物体的主要合角速度属性参数。注：单位为弧度/秒。");

	{
		//Get omega.
		C4DVector3 omega = pPhysicsObject->getOmega();

		//Create property.
		HANDLE_PHYSICS_OMEGA_X = new CMFCPropertyGridProperty(L"ω（x）",
			(_variant_t) omega.x(), L"在全局坐标系中，绕x坐标轴方向的角速度。注：单位为弧度/秒。");
		//Disable.
		HANDLE_PHYSICS_OMEGA_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_OMEGA->AddSubItem(HANDLE_PHYSICS_OMEGA_X);

		//Create property.
		HANDLE_PHYSICS_OMEGA_Y = new CMFCPropertyGridProperty(L"ω（y）",
			(_variant_t) omega.y(), L"在全局坐标系中，绕y坐标轴方向的角速度。注：单位为弧度/秒。");
		//Disable.
		HANDLE_PHYSICS_OMEGA_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_OMEGA->AddSubItem(HANDLE_PHYSICS_OMEGA_Y);

		//Create property.
		HANDLE_PHYSICS_OMEGA_Z = new CMFCPropertyGridProperty(L"ω（z）",
			(_variant_t) omega.z(), L"在全局坐标系中，绕z坐标轴方向的角速度。注：单位为弧度/秒。");
		//Disable.
		HANDLE_PHYSICS_OMEGA_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_OMEGA->AddSubItem(HANDLE_PHYSICS_OMEGA_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_OMEGA);

	//Create property.
	HANDLE_PHYSICS_ACCELERATION = new CMFCPropertyGridProperty(L"线加速度（米/平方秒）");
	//Set description.
	HANDLE_PHYSICS_ACCELERATION->SetDescription(L"物理物体的主要线加速度属性参数。注：单位为米/平方秒。");

	{
		//Get acceleration.
		C4DVector3 acceleration = pPhysicsObject->getAcceleration();

		//Create property.
		HANDLE_PHYSICS_ACCELERATION_X = new CMFCPropertyGridProperty(L"A（x）",
			(_variant_t) acceleration.x(), L"在全局坐标系中，沿x坐标轴方向的线速度。注：单位为米/平方秒。");
		//Disable.
		HANDLE_PHYSICS_ACCELERATION_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ACCELERATION->AddSubItem(HANDLE_PHYSICS_ACCELERATION_X);

		//Create property.
		HANDLE_PHYSICS_ACCELERATION_Y = new CMFCPropertyGridProperty(L"A（y）",
			(_variant_t) acceleration.y(), L"在全局坐标系中，沿y坐标轴方向的线速度。注：单位为米/平方秒。");
		//Disable.
		HANDLE_PHYSICS_ACCELERATION_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ACCELERATION->AddSubItem(HANDLE_PHYSICS_ACCELERATION_Y);

		//Create property.
		HANDLE_PHYSICS_ACCELERATION_Z = new CMFCPropertyGridProperty(L"A（z）",
			(_variant_t) acceleration.z(), L"在全局坐标系中，沿z坐标轴方向的线速度。注：单位为米/平方秒。");
		//Disable.
		HANDLE_PHYSICS_ACCELERATION_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ACCELERATION->AddSubItem(HANDLE_PHYSICS_ACCELERATION_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_ACCELERATION);

	//Create property.
	HANDLE_PHYSICS_ALPHA = new CMFCPropertyGridProperty(L"角加速度（弧度/平方秒）");
	//Set description.
	HANDLE_PHYSICS_ALPHA->SetDescription(L"物理物体的主要线加速度属性参数。注：单位为弧度/平方秒。");

	{
		//Get alpha.
		C4DVector3 alpha = pPhysicsObject->getAlpha();

		//Create property.
		HANDLE_PHYSICS_ALPHA_X = new CMFCPropertyGridProperty(L"α（x）",
			(_variant_t) alpha.x(), L"在全局坐标系中，绕x坐标轴方向的角速度。注：单位为弧度/平方秒。");
		//Disable.
		HANDLE_PHYSICS_ALPHA_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ALPHA->AddSubItem(HANDLE_PHYSICS_ALPHA_X);

		//Create property.
		HANDLE_PHYSICS_ALPHA_Y = new CMFCPropertyGridProperty(L"α（y）",
			(_variant_t) alpha.y(), L"在全局坐标系中，绕y坐标轴方向的角速度。注：单位为弧度/平方秒。");
		//Disable.
		HANDLE_PHYSICS_ALPHA_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ALPHA->AddSubItem(HANDLE_PHYSICS_ALPHA_Y);

		//Create property.
		HANDLE_PHYSICS_ALPHA_Z = new CMFCPropertyGridProperty(L"α（z）",
			(_variant_t) alpha.z(), L"在全局坐标系中，绕z坐标轴方向的角速度。注：单位为弧度/平方秒。");
		//Disable.
		HANDLE_PHYSICS_ALPHA_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_ALPHA->AddSubItem(HANDLE_PHYSICS_ALPHA_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_ALPHA);
}
