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
// ChangePhysicsForceProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ChangePhysicsForceProperties(CPhysicsObject* pPhyscisObject)
{
#ifdef _DEBUG
	assert(pPhyscisObject != NULL);
#endif

	//Get force.
	C4DVector3 force = pPhyscisObject->getForce();
	//Check handle.
	if(HANDLE_PHYSICS_FORCE_X != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_FORCE_X->SetValue((_variant_t) force.x());
	}
	//Check handle.
	if(HANDLE_PHYSICS_FORCE_Y != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_FORCE_Y->SetValue((_variant_t) force.y());
	}
	//Check handle.
	if(HANDLE_PHYSICS_FORCE_Z != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_FORCE_Z->SetValue((_variant_t) force.z());
	}

	//Get torque.
	C4DVector3 torque = pPhyscisObject->getTorque();
	//Check handle.
	if(HANDLE_PHYSICS_TORQUE_X != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_TORQUE_X->SetValue((_variant_t) torque.x());
	}
	//Check handle.
	if(HANDLE_PHYSICS_TORQUE_Y != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_TORQUE_Y->SetValue((_variant_t) torque.y());
	}
	//Check handle.
	if(HANDLE_PHYSICS_TORQUE_Z != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_TORQUE_Z->SetValue((_variant_t) torque.z());
	}

	//Get omega.
	C4DVector3 omega = pPhyscisObject->getOmega();
	//Check handle.
	if(HANDLE_PHYSICS_OMEGA_X != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_OMEGA_X->SetValue((_variant_t) omega.x());
	}
	//Check handle.
	if(HANDLE_PHYSICS_OMEGA_Y != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_OMEGA_Y->SetValue((_variant_t) omega.y());
	}
	//Check handle.
	if(HANDLE_PHYSICS_OMEGA_Z != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_OMEGA_Z->SetValue((_variant_t) omega.z());
	}

	//Get velocity.
	C4DVector3 velocity = pPhyscisObject->getVelocity();
	//Check handle.
	if(HANDLE_PHYSICS_VELOCITY_X != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_VELOCITY_X->SetValue((_variant_t) velocity.x());
	}
	//Check handle.
	if(HANDLE_PHYSICS_VELOCITY_Y != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_VELOCITY_Y->SetValue((_variant_t) velocity.y());
	}
	//Check handle.
	if(HANDLE_PHYSICS_VELOCITY_Z != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_VELOCITY_Z->SetValue((_variant_t) velocity.z());
	}

	//Get acceleration.
	C4DVector3 acceleration = pPhyscisObject->getAcceleration();

	//Check handle.
	if(HANDLE_PHYSICS_ACCELERATION_X != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_ACCELERATION_X->SetValue((_variant_t) acceleration.x());
	}
	//Check handle.
	if(HANDLE_PHYSICS_ACCELERATION_Y != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_ACCELERATION_Y->SetValue((_variant_t) acceleration.y());
	}
	//Check handle.
	if(HANDLE_PHYSICS_ACCELERATION_Z != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_ACCELERATION_Z->SetValue((_variant_t) acceleration.z());
	}

	//Get alpha.
	C4DVector3 alpha = pPhyscisObject->getAlpha();
	//Check handle.
	if(HANDLE_PHYSICS_ALPHA_X != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_ALPHA_X->SetValue((_variant_t) alpha.x());
	}
	//Check handle.
	if(HANDLE_PHYSICS_ALPHA_Y != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_ALPHA_Y->SetValue((_variant_t) alpha.y());
	}
	//Check handle.
	if(HANDLE_PHYSICS_ALPHA_Z != NULL)
	{
		//Set value.
		HANDLE_PHYSICS_ALPHA_Z->SetValue((_variant_t) alpha.z());
	}
}
