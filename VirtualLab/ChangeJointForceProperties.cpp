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
// ChangeJointForceProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ChangeJointForceProperties(CPhysicsJointObject* pJointObject)
{
#ifdef _DEBUG
	assert(pJointObject != NULL);
#endif

	//Get force.
	C4DVector3 force = pJointObject->getJointForce();
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_FORCE_X != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_FORCE_X->SetValue((_variant_t) force.x());
	}
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_FORCE_Y != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_FORCE_Y->SetValue((_variant_t) force.y());
	}
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_FORCE_Z != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_FORCE_Z->SetValue((_variant_t) force.z());
	}

	//Get omega.
	C4DVector3 omega = pJointObject->getRelativeOmega();
	//Change angle into eular angle.
	omega = omega * 180.0f / D3DX_PI;
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_OMEGA_X != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_OMEGA_X->SetValue((_variant_t) omega.x());
	}
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_OMEGA_Y != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_OMEGA_Y->SetValue((_variant_t) omega.y());
	}
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_OMEGA_Z != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_OMEGA_Z->SetValue((_variant_t) omega.z());
	}

	//Get angle.
	C4DVector3 angle = pJointObject->getRelativeAngle();
	//Change angle into eular angle.
	angle = angle * 180.0f / D3DX_PI;
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_ANGLE_X != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_ANGLE_X->SetValue((_variant_t) angle.x());
	}
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_ANGLE_Y != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_ANGLE_Y->SetValue((_variant_t) angle.y());
	}
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_ANGLE_Z != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_ANGLE_Z->SetValue((_variant_t) angle.z());
	}

	//Get position.
	C4DVector3 position = pJointObject->getRelativePosition();
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_POSITION_X != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_POSITION_X->SetValue((_variant_t) position.x());
	}
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_POSITION_Y != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_POSITION_Y->SetValue((_variant_t) position.y());
	}
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_POSITION_Z != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_POSITION_Z->SetValue((_variant_t) position.z());
	}

	//Get velocity.
	C4DVector3 velocity = pJointObject->getRelativeVelocity();
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_VELOCITY_X != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_VELOCITY_X->SetValue((_variant_t) velocity.x());
	}
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_VELOCITY_Y != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_VELOCITY_Y->SetValue((_variant_t) velocity.y());
	}
	//Check handle.
	if(HANDLE_PHYSICS_JOINT_VELOCITY_Z != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_JOINT_VELOCITY_Z->SetValue((_variant_t) velocity.z());
	}
}
