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

#include "PSEyeDevice.h"
#include "CLEyeMulticam.h"

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
// OnPropertyChanged
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::OnPropertyChanged(CD3DXDevice* pDevice,CMFCPropertyGridProperty *pProp)
{
#ifdef _DEBUG
	assert(pDevice != NULL && pProp != NULL);
#endif

	//Check instance.
	if(IS_PSEYEDEVICE_BASE(pDevice))
	{
		//Get filter.
		CPSEyeDevice* pPSEyeDevice = (CPSEyeDevice *)pDevice;
		//Check result.
		if(pProp == HANDLE_PSEYE_SENSOR_GAIN)
		{
			//Set value.
			pPSEyeDevice->setValue(CLEYE_GAIN,pProp->GetValue().intVal);
		}
		else if(pProp == HANDLE_PSEYE_SENSOR_EXPOSURE)
		{
			//Set value.
			pPSEyeDevice->setValue(CLEYE_EXPOSURE,pProp->GetValue().intVal);
		}
		else if(pProp == HANDLE_PSEYE_LINEAR_ZOOM)
		{
			//Set value.
			pPSEyeDevice->setValue(CLEYE_ZOOM,pProp->GetValue().intVal);
		}
		else if(pProp == HANDLE_PSEYE_LINEAR_ROTATION)
		{
			//Set value.
			pPSEyeDevice->setValue(CLEYE_ROTATION,pProp->GetValue().intVal);
		}
	}
}