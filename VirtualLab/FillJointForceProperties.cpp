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
	HANDLE_PHYSICS_JOINT_FORCE = new CMFCPropertyGridProperty(L"相对合力（牛顿）");
	//Set description.
	HANDLE_PHYSICS_JOINT_FORCE->SetDescription(L"链接体所受的相对合力。注：单位为牛顿。");

	{
		//Get force.
		C4DVector3 force = pJointObject->getJointForce();

		//Create property.
		HANDLE_PHYSICS_JOINT_FORCE_X = new CMFCPropertyGridProperty(L"F（x）",
			(_variant_t) force.x(), L"在世界坐标系中，沿x轴方向的合力。注：单位为牛顿。");
		//Disable.
		HANDLE_PHYSICS_JOINT_FORCE_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_FORCE->AddSubItem(HANDLE_PHYSICS_JOINT_FORCE_X);

		//Create property.
		HANDLE_PHYSICS_JOINT_FORCE_Y = new CMFCPropertyGridProperty(L"F（y）",
			(_variant_t) force.y(), L"在世界坐标系中，沿y轴方向的合力。注：单位为牛顿。");
		//Disable.
		HANDLE_PHYSICS_JOINT_FORCE_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_FORCE->AddSubItem(HANDLE_PHYSICS_JOINT_FORCE_Y);

		//Create property.
		HANDLE_PHYSICS_JOINT_FORCE_Z = new CMFCPropertyGridProperty(L"F（z）",
			(_variant_t) force.z(), L"在世界坐标系中，沿z轴方向的合力。注：单位为牛顿。");
		//Disable.
		HANDLE_PHYSICS_JOINT_FORCE_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_FORCE->AddSubItem(HANDLE_PHYSICS_JOINT_FORCE_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_JOINT_FORCE);

	//Create property.
	HANDLE_PHYSICS_JOINT_POSITION = new CMFCPropertyGridProperty(L"相对位置（米）");
	//Set description.
	HANDLE_PHYSICS_JOINT_POSITION->SetDescription(L"链接体的父子体之间的相对位置。注：单位为米。");

	{
		//Get position.
		C4DVector3 position = pJointObject->getRelativePosition();

		//Create property.
		HANDLE_PHYSICS_JOINT_POSITION_X = new CMFCPropertyGridProperty(L"P（x）",
			(_variant_t) position.x(), L"在局部坐标系中，沿x轴的相对距离。注：单位为米。");
		//Disable.
		HANDLE_PHYSICS_JOINT_POSITION_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_POSITION->AddSubItem(HANDLE_PHYSICS_JOINT_POSITION_X);

		//Create property.
		HANDLE_PHYSICS_JOINT_POSITION_Y = new CMFCPropertyGridProperty(L"P（y）",
			(_variant_t) position.y(), L"在局部坐标系中，沿y轴的相对距离。注：单位为米。");
		//Disable.
		HANDLE_PHYSICS_JOINT_POSITION_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_POSITION->AddSubItem(HANDLE_PHYSICS_JOINT_POSITION_Y);

		//Create property.
		HANDLE_PHYSICS_JOINT_POSITION_Z = new CMFCPropertyGridProperty(L"P（z）",
			(_variant_t) position.z(), L"在局部坐标系中，沿z轴的相对距离。注：单位为米。");
		//Disable.
		HANDLE_PHYSICS_JOINT_POSITION_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_POSITION->AddSubItem(HANDLE_PHYSICS_JOINT_POSITION_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_JOINT_POSITION);

	//Create property.
	HANDLE_PHYSICS_JOINT_VELOCITY = new CMFCPropertyGridProperty(L"相对速度（米/秒）");
	//Set description.
	HANDLE_PHYSICS_JOINT_VELOCITY->SetDescription(L"链接体的父子体之间的相对速度。注：单位为米/秒。");

	{
		//Get velocity.
		C4DVector3 velocity = pJointObject->getRelativeVelocity();

		//Create property.
		HANDLE_PHYSICS_JOINT_VELOCITY_X = new CMFCPropertyGridProperty(L"V（x）",
			(_variant_t) velocity.x(), L"在局部坐标系中，沿z轴的相对速度。注：单位为米/秒。");
		//Disable.
		HANDLE_PHYSICS_JOINT_VELOCITY_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_VELOCITY->AddSubItem(HANDLE_PHYSICS_JOINT_VELOCITY_X);

		//Create property.
		HANDLE_PHYSICS_JOINT_VELOCITY_Y = new CMFCPropertyGridProperty(L"V（y）",
			(_variant_t) velocity.y(), L"在局部坐标系中，沿y轴的相对速度。注：单位为米/秒。");
		//Disable.
		HANDLE_PHYSICS_JOINT_VELOCITY_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_VELOCITY->AddSubItem(HANDLE_PHYSICS_JOINT_VELOCITY_Y);

		//Create property.
		HANDLE_PHYSICS_JOINT_VELOCITY_Z = new CMFCPropertyGridProperty(L"V（z）",
			(_variant_t) velocity.z(), L"在局部坐标系中，沿z轴的相对速度。注：单位为米/秒。");
		//Disable.
		HANDLE_PHYSICS_JOINT_VELOCITY_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_VELOCITY->AddSubItem(HANDLE_PHYSICS_JOINT_VELOCITY_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_JOINT_VELOCITY);

	//Create property.
	HANDLE_PHYSICS_JOINT_ANGLE = new CMFCPropertyGridProperty(L"相对转角（角度）");
	//Set description.
	HANDLE_PHYSICS_JOINT_ANGLE->SetDescription(L"链接体的父子体之间的相对转角。注：单位为角度。");

	{
		//Get angle.
		C4DVector3 angle = pJointObject->getRelativeAngle();
		//Change it into eular angle.
		angle = angle * 180.0f / D3DX_PI;

		//Create property.
		HANDLE_PHYSICS_JOINT_ANGLE_X = new CMFCPropertyGridProperty(L"φ（x）",
			(_variant_t) angle.x(), L"在局部坐标系中，绕x轴的相对转角。注：单位为角度。");
		//Disable.
		HANDLE_PHYSICS_JOINT_ANGLE_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_ANGLE->AddSubItem(HANDLE_PHYSICS_JOINT_ANGLE_X);

		//Create property.
		HANDLE_PHYSICS_JOINT_ANGLE_Y = new CMFCPropertyGridProperty(L"θ（y）",
			(_variant_t) angle.y(), L"在局部坐标系中，绕y轴的相对转角。注：单位为角度。");
		//Disable.
		HANDLE_PHYSICS_JOINT_ANGLE_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_ANGLE->AddSubItem(HANDLE_PHYSICS_JOINT_ANGLE_Y);

		//Create property.
		HANDLE_PHYSICS_JOINT_ANGLE_Z = new CMFCPropertyGridProperty(L"ψ（z）",
			(_variant_t) angle.z(), L"在局部坐标系中，绕z轴的相对转角。注：单位为角度。");
		//Disable.
		HANDLE_PHYSICS_JOINT_ANGLE_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_ANGLE->AddSubItem(HANDLE_PHYSICS_JOINT_ANGLE_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_JOINT_ANGLE);

	//Create property.
	HANDLE_PHYSICS_JOINT_OMEGA = new CMFCPropertyGridProperty(L"相对角速度（角度/秒）");
	//Set description.
	HANDLE_PHYSICS_JOINT_OMEGA->SetDescription(L"链接体的父子体之间的相对角速度。注：单位为角度/秒。");

	{
		//Get omega.
		C4DVector3 omega = pJointObject->getRelativeOmega();
		//Change it into eular angle.
		omega = omega * 180.0f / D3DX_PI;

		//Create property.
		HANDLE_PHYSICS_JOINT_OMEGA_X = new CMFCPropertyGridProperty(L"ω（x）",
			(_variant_t) omega.x(), L"在局部坐标系中，绕x轴的相对角速度。注：单位为角度/秒。");
		//Disable.
		HANDLE_PHYSICS_JOINT_OMEGA_X->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_OMEGA->AddSubItem(HANDLE_PHYSICS_JOINT_OMEGA_X);

		//Create property.
		HANDLE_PHYSICS_JOINT_OMEGA_Y = new CMFCPropertyGridProperty(L"ω（y）",
			(_variant_t) omega.y(), L"在局部坐标系中，绕y轴的相对角速度。注：单位为角度/秒。");
		//Disable.
		HANDLE_PHYSICS_JOINT_OMEGA_Y->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_OMEGA->AddSubItem(HANDLE_PHYSICS_JOINT_OMEGA_Y);

		//Create property.
		HANDLE_PHYSICS_JOINT_OMEGA_Z = new CMFCPropertyGridProperty(L"ω（z）",
			(_variant_t) omega.z(), L"在局部坐标系中，绕z轴的相对角速度。注：单位为角度/秒。");
		//Disable.
		HANDLE_PHYSICS_JOINT_OMEGA_Z->Enable(FALSE);
		//Add subitem.
		HANDLE_PHYSICS_JOINT_OMEGA->AddSubItem(HANDLE_PHYSICS_JOINT_OMEGA_Z);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_PHYSICS_JOINT_OMEGA);
}
