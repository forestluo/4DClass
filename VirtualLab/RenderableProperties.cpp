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
// Globals
//
///////////////////////////////////////////////////////////////////////////////

const LPCTSTR OBJECT_PROPERTIES[] =
{
	PROPERTY_GENERAL,
	PROPERTY_FENCE,
	PROPERTY_RENDER,
	PROPERTY_PHYSICS,
	PROPERTY_PHYSICS_FORCE,
};

const LPCTSTR JOINT_OBJECT_PROPERTIES[] =
{
	PROPERTY_GENERAL,
	PROPERTY_FENCE,
	PROPERTY_RENDER,
	PROPERTY_PHYSICS,
	PROPERTY_PHYSICS_FORCE,
	PROPERTY_JOINT,
	PROPERTY_JOINT_FORCE,
};

///////////////////////////////////////////////////////////////////////////////
//
// ShowProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ShowProperties(CD3DXRenderableObject* pRenderableObject)
{
#ifdef _DEBUG
	assert(pRenderableObject != NULL);
#endif
	//Check main frame.
	if(MAINFRAME != NULL)
	{
		//Get doc.
		CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
		//Check doc.
		if(pDoc == NULL || pDoc->application == NULL)
		{
			//Do nothing.
		}
		//Check object.
		else
		{
			//Get focused.
			CD3DXObject* object = pDoc->application->getFocused();
			//Check result.
			if(object != pRenderableObject)
			{
				//Set current.
				pDoc->application->setFocused(pRenderableObject);
				//Check current.
				if(object->classCode() == pRenderableObject->classCode())
				{
					//Set window text.
					SetWindowTextW(pRenderableObject->getAlias().getCString());
					//Change propterty page.
					ChangePropertyPage(pRenderableObject,nSelectedPropertyPage);
				}
				else
				{
					//Set selected property page.
					nSelectedPropertyPage = 0;
					//Set window text.
					SetWindowTextW(pRenderableObject->getAlias().getCString());

					//Clear property handles.
					ClearHandles();
					//Remove all previous elements.
					m_wndPropList.RemoveAll();
					//Remove all selections.
					m_wndObjectCombo.ResetContent();
					//Check object.
					if(pRenderableObject->isJointObject())
					{
						//Calculate size.
						int size = sizeof(JOINT_OBJECT_PROPERTIES) / sizeof(LPCTSTR);
						//Check object.
						if(!pRenderableObject->isPhysicsObject()) size -= 4;
						//Add properties.
						for(int i = 0;i < sizeof(JOINT_OBJECT_PROPERTIES) / sizeof(LPCTSTR);i ++)
						{
							//Add string.
							m_wndObjectCombo.AddString(JOINT_OBJECT_PROPERTIES[i]);
						}
					}
					else
					{
						//Calculate size.
						int size = sizeof(OBJECT_PROPERTIES) / sizeof(LPCTSTR);
						//Check object.
						if(!pRenderableObject->isPhysicsObject()) size -= 2;
						//Add properties.
						for(int i = 0;i < sizeof(OBJECT_PROPERTIES) / sizeof(LPCTSTR);i ++)
						{
							//Add string.
							m_wndObjectCombo.AddString(OBJECT_PROPERTIES[i]);
						}
					}
					//Set current selection.
					m_wndObjectCombo.SetCurSel(PROPERTY_GENERAL_SELECTION);

					//Fill properties.
					FillProperties(pRenderableObject);
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////
//
// ChangePropertyPage
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ChangePropertyPage(CD3DXRenderableObject* pRenderableObject,int nSelected)
{
#ifdef _DEBUG
	assert(pRenderableObject != NULL);
#endif

	//Clear property handles.
	ClearHandles();
	//Remove all previous elements.
	m_wndPropList.RemoveAll();
	//Check selected.
	if(nSelected == PROPERTY_GENERAL_SELECTION)
	{
		//Fill properties.
		FillProperties(pRenderableObject);
	}
	else if(nSelected == PROPERTY_FENCE_SELECTION)
	{
		//Fill properties.
		FillBoxProperties(pRenderableObject);
	}
	else if(nSelected == PROPERTY_RENDER_SELECTION)
	{
		//Fill properties.
		FillRenderProperties(pRenderableObject);
	}
	else if(nSelected == PROPERTY_PHYSICS_SELECTION)
	{
		//Check object.
		if(pRenderableObject->isPhysicsObject())
		{
			//Get physics object.
			_OBJECT physicsObject = pRenderableObject->getPhysics();
#ifdef _DEBUG
			assert(physicsObject != NULL);
#endif
			//Fill properties.
			FillPhysicsProperties((CPhysicsObject *)physicsObject);
		}
	}
	else if(nSelected == PROPERTY_PHYSICS_FORCE_SELECTION)
	{
		//Check object.
		if(pRenderableObject->isPhysicsObject())
		{
			//Get physics object.
			_OBJECT physicsObject = pRenderableObject->getPhysics();
#ifdef _DEBUG
			assert(physicsObject != NULL);
#endif
			//Fill properties.
			FillPhysicsForceProperties((CPhysicsObject *)physicsObject);
		}
	}
	//Check base.
	else if(pRenderableObject->isJointObject())
	{
		//Check object.
		if(pRenderableObject->isPhysicsObject())
		{
			//Get physics object.
			_OBJECT physicsObject = pRenderableObject->getPhysics();
#ifdef _DEBUG
			assert(physicsObject != NULL);
#endif
			//Check selection.
			if(nSelected == PROPERTY_JOINT_SELECTION)
			{
				//Fill properties.
				FillJointProperties((CPhysicsJointObject *)physicsObject);
			}
			else if(nSelected == PROPERTY_JOINT_FORCE_SELECTION)
			{
				//Fill properties.
				FillJointForceProperties((CPhysicsJointObject *)physicsObject);
			}
		}
	}
}
