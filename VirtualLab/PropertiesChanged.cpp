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
// OnPropertyChanged
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::OnPropertyChanged(CD3DXRenderableObject* pRenderableObject,CMFCPropertyGridProperty *pProp)
{
#ifdef _DEBUG
	assert(pRenderableObject != NULL && pProp != NULL);
#endif

	if(pProp == HANDLE_NAME)
	{
		//Name was changed.
		CNormalString alias(CString(pProp->GetValue()).GetBuffer());
		//Check name.
		if(alias == pRenderableObject->getAlias()) return;

		//Check result.
		if(alias.length() <= 0)
		{
			//Show message.
			AfxMessageBox(_T("对象名字不允许为空。\n\n系统将恢复对象原有名称。"), MB_OK | MB_ICONSTOP);
			//Recover its name.
			pProp->SetValue(pRenderableObject->getAlias().getCString());
		}
		else
		{
			//Check main frame.
			if(MAINFRAME != NULL)
			{
				//Get doc.
				CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
				//Check result.
				if(pDoc != NULL && pDoc->application != NULL && pDoc->application->getForeground() != NULL)
				{
					//Count by name.
					if(pDoc->application->getForeground()->getObject(alias) == NULL)
					{
						//Set name.
						pRenderableObject->setAlias(alias);
						//Update scene view.
						MAINFRAME->UpdateSceneView();
					}
					else
					{
						//Recover its name.
						pProp->SetValue(pRenderableObject->getAlias().getCString());
						//Show message.
						AfxMessageBox(_T("对象名已经存在，不允许重名。\n\n系统将恢复对象原有名称。"), MB_OK | MB_ICONSTOP);
					}
				}
			}
		}
	}
	else if(pProp == HANDLE_OBJECT_TRANSFORM_SCALE_X ||
		pProp == HANDLE_OBJECT_TRANSFORM_SCALE_Y ||
		pProp == HANDLE_OBJECT_TRANSFORM_SCALE_Z)
	{
		//Set scale.
		pRenderableObject->setScale(HANDLE_OBJECT_TRANSFORM_SCALE_X->GetValue().fltVal,
			HANDLE_OBJECT_TRANSFORM_SCALE_Y->GetValue().fltVal,
			HANDLE_OBJECT_TRANSFORM_SCALE_Z->GetValue().fltVal);
	}
	else if(pProp == HANDLE_OBJECT_TRANSFORM_ROTATE_X ||
		pProp == HANDLE_OBJECT_TRANSFORM_ROTATE_Y ||
		pProp == HANDLE_OBJECT_TRANSFORM_ROTATE_Z)
	{
		//Rotation.
		C4DQuaternion rotation(C4DVector3(HANDLE_OBJECT_TRANSFORM_ROTATE_X->GetValue().fltVal * D3DX_PI / 180.0f,
			HANDLE_OBJECT_TRANSFORM_ROTATE_Y->GetValue().fltVal * D3DX_PI / 180.0f,
			HANDLE_OBJECT_TRANSFORM_ROTATE_Z->GetValue().fltVal * D3DX_PI / 180.0f));

		//Get controller.
		CObjectController* pController = pRenderableObject->getController();
		//Check result.
		if(pController != NULL)
		{
			//Set rotation.
			pController->setRotation(rotation);
		}
		else
		{
			//Set eular rotation.
			pRenderableObject->setRotation(rotation);
		}

	}
	else if(pProp == HANDLE_OBJECT_TRANSFORM_TRANSLATE_X ||
		pProp == HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y ||
		pProp == HANDLE_OBJECT_TRANSFORM_TRANSLATE_Z)
	{
		//Set position.
		pRenderableObject->setPosition(HANDLE_OBJECT_TRANSFORM_TRANSLATE_X->GetValue().fltVal,
			HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y->GetValue().fltVal,
			HANDLE_OBJECT_TRANSFORM_TRANSLATE_Z->GetValue().fltVal);
	}
	else if(pProp == HANDLE_OBJECT_CONTROL_SCALABLE)
	{
		//Get value.
		_BOOL bScalable = HANDLE_OBJECT_CONTROL_SCALABLE->GetValue().boolVal ? _TRUE : _FALSE;
		//Set scalable.
		pRenderableObject->setScalable(bScalable);
		//Disable scalable.
		if(HANDLE_OBJECT_TRANSFORM_SCALE_X != NULL) HANDLE_OBJECT_TRANSFORM_SCALE_X->Enable(bScalable);
		if(HANDLE_OBJECT_TRANSFORM_SCALE_Y != NULL) HANDLE_OBJECT_TRANSFORM_SCALE_Y->Enable(bScalable);
		if(HANDLE_OBJECT_TRANSFORM_SCALE_Z != NULL) HANDLE_OBJECT_TRANSFORM_SCALE_Z->Enable(bScalable);
	}
	else if(pProp == HANDLE_OBJECT_CONTROL_ROTATABLE)
	{
		//Get value.
		_BOOL bRotatable = HANDLE_OBJECT_CONTROL_ROTATABLE->GetValue().boolVal ? _TRUE : _FALSE;
		//Set rotatable.
		pRenderableObject->setRotatable(bRotatable);
		//Disable scalable.
		if(HANDLE_OBJECT_TRANSFORM_ROTATE_X != NULL) HANDLE_OBJECT_TRANSFORM_ROTATE_X->Enable(bRotatable);
		if(HANDLE_OBJECT_TRANSFORM_ROTATE_Y != NULL) HANDLE_OBJECT_TRANSFORM_ROTATE_Y->Enable(bRotatable);
		if(HANDLE_OBJECT_TRANSFORM_ROTATE_Z != NULL) HANDLE_OBJECT_TRANSFORM_ROTATE_Z->Enable(bRotatable);
	}
	else if(pProp == HANDLE_OBJECT_CONTROL_MOVABLE)
	{
		//Get value.
		_BOOL bMovable = HANDLE_OBJECT_CONTROL_MOVABLE->GetValue().boolVal ? _TRUE : _FALSE;
		//Set movable.
		pRenderableObject->setMovable(bMovable);
		//Disable scalable.
		if(HANDLE_OBJECT_TRANSFORM_TRANSLATE_X != NULL) HANDLE_OBJECT_TRANSFORM_TRANSLATE_X->Enable(bMovable);
		if(HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y != NULL) HANDLE_OBJECT_TRANSFORM_TRANSLATE_Y->Enable(bMovable);
		if(HANDLE_OBJECT_TRANSFORM_TRANSLATE_Z != NULL) HANDLE_OBJECT_TRANSFORM_TRANSLATE_Z->Enable(bMovable);
	}
}
