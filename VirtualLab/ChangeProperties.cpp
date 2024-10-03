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
// ChangeProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ChangeProperties(CD3DXRenderableObject* pRenderableObject)
{
#ifdef _DEBUG
	assert(pRenderableObject != NULL);
#endif

	//Check selection.
	if(nSelectedPropertyPage == PROPERTY_GENERAL_SELECTION)
	{
		//Get scale.
		C4DVector3 scale = pRenderableObject->getScale();

		//Check result
		if(HANDLE_OBJECT_TRANSFORM_SCALE_X != NULL)
		{
			//Set value.
			HANDLE_OBJECT_TRANSFORM_SCALE_X->SetValue((_variant_t)scale.x());
		}
		//Check result.
		if(HANDLE_OBJECT_TRANSFORM_SCALE_Y != NULL)
		{
			//Set value.
			HANDLE_OBJECT_TRANSFORM_SCALE_Y->SetValue((_variant_t)scale.y());
		}
		//Check result.
		if(HANDLE_OBJECT_TRANSFORM_SCALE_Z != NULL)
		{
			//Set value.
			HANDLE_OBJECT_TRANSFORM_SCALE_Z->SetValue((_variant_t)scale.z());
		}

		//Get rotation.
		C4DVector3 eular = pRenderableObject->getRotation().eular();
		//Adjust.
		eular *= 180.0f / D3DX_PI;

		//Check result.
		if(HANDLE_OBJECT_TRANSFORM_ROTATE_X != NULL)
		{
			//Set value.
			HANDLE_OBJECT_TRANSFORM_ROTATE_X->SetValue((_variant_t)eular.x());
		}
		//Check result.
		if(HANDLE_OBJECT_TRANSFORM_ROTATE_Y != NULL)
		{
			//Set value.
			HANDLE_OBJECT_TRANSFORM_ROTATE_Y->SetValue((_variant_t)eular.y());
		}
		//Check result.
		if(HANDLE_OBJECT_TRANSFORM_ROTATE_Z != NULL)
		{
			//Set value.
			HANDLE_OBJECT_TRANSFORM_ROTATE_Z->SetValue((_variant_t)eular.z());
		}

		//Get position.
		C4DVector3 position = pRenderableObject->getPosition();

		//Check result.
		if(HANDLE_OBJECT_TRANSFORM_TRANSLATE_X != NULL)
		{
			//Set value.
			HANDLE_OBJECT_TRANSFORM_TRANSLATE_X->SetValue((_variant_t)position.x());
		}
		//Check result.
		if(HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y != NULL)
		{
			//Set value.
			HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y->SetValue((_variant_t)position.y());
		}
		//Check result.
		if(HANDLE_OBJECT_TRANSFORM_TRANSLATE_Z)
		{
			//Set value.
			HANDLE_OBJECT_TRANSFORM_TRANSLATE_Z->SetValue((_variant_t)position.z());
		}
	}
}
