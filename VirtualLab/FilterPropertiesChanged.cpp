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

#include "HAARFilter.h"

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

void CPropertiesWnd::OnPropertyChanged(CD3DXFilter* pFilter,CMFCPropertyGridProperty *pProp)
{
#ifdef _DEBUG
	assert(pFilter != NULL && pProp != NULL);
#endif

	//Check instance.
	if(IS_HAARFILTER_BASE(pFilter))
	{
		//Get filter.
		CHAARFilter* pHAARFilter = (CHAARFilter *)pFilter;
		//Check property.
		if(pProp == HANDLE_HAAR_DETECTING)
		{
			//Check result.
			if(pProp->GetValue().boolVal)
			{
				//Enable detection.
				pHAARFilter->enableDetection();
				//Enable tracking.
				HANDLE_HAAR_TRACKING->Enable(TRUE);
			}
			else
			{
				//Disable detection.
				pHAARFilter->disableDetection();
				//Enable tracking.
				HANDLE_HAAR_TRACKING->Enable(FALSE);
			}
		}
		else if(pProp == HANDLE_HAAR_TRACKING)
		{
			//Check result.
			pHAARFilter->setFaceTracking(pProp->GetValue().boolVal ? _TRUE : _FALSE);
		}
	}
}