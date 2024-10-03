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
// ChangePhysicsProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ChangePhysicsProperties(CPhysicsObject* physicsObject)
{
#ifdef _DEBUG
	assert(physicsObject != NULL);
#endif

	//Get inertia.
	C4DVector3 inertia = physicsObject->getInertia();
	//Check result.
	if(HANDLE_PHYSICS_GENERAL_INERTIA_IXX != NULL)
	{
		HANDLE_PHYSICS_GENERAL_INERTIA_IXX->SetValue((_variant_t) inertia.x());
	}
	//Check result.
	if(HANDLE_PHYSICS_GENERAL_INERTIA_IYY != NULL)
	{
		HANDLE_PHYSICS_GENERAL_INERTIA_IYY->SetValue((_variant_t) inertia.y());
	}
	//Check result.
	if(HANDLE_PHYSICS_GENERAL_INERTIA_IZZ != NULL)
	{
		HANDLE_PHYSICS_GENERAL_INERTIA_IZZ->SetValue((_variant_t) inertia.z());
	}
}
