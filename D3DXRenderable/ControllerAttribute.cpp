///////////////////////////////////////////////////////////////////////////////
//
// ControllerAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ControllerAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// CControllerAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CControllerAttribute::CControllerAttribute(void)
{
	//Set default value.
	controller = (CObjectController *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CControllerAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CControllerAttribute::~CControllerAttribute(void)
{
	//Check controller.
	if(controller != _NULL)
	{
		//Delete controller.
		delete (CObjectController *)controller;
		//Clear controller.
		controller = (CObjectController *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetController
//
///////////////////////////////////////////////////////////////////////////////

CObjectController* CControllerAttribute::getController()
{
	//Return result.
	return controller;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsPicked
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CControllerAttribute::isPicked() const
{
	//Set value.
	return controller != _NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPicked
//
///////////////////////////////////////////////////////////////////////////////

void CControllerAttribute::setPicked(_BOOL picked)
{
	//Controller.
	CObjectController* pController;

	//Check controller.
	if(controller != _NULL)
	{
		//Check picked.
		if(!picked)
		{
			//Get controller.
			pController = controller;
			//Clear controller.
			controller = (CObjectController *)_NULL;

			//Detach.
			pController->detachObject();
			//Delete controller.
			delete (CObjectController *)pController;
		}
	}
	else
	{
		//Check picked.
		if(picked)
		{
			//Create controller.
			pController = new CObjectController();
#ifdef _DEBUG
			assert(pController != _NULL);
#endif
			//Attach object.
			pController->attachObject(this);
			//Set controller.
			controller = pController;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetViewPort
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CControllerAttribute::setViewPort(CViewPort* viewPort)
{
	//Result.
	HRESULT hr = S_OK;

#ifdef _DEBUG
	assert(viewPort != _NULL);
#endif

	//Get controller.
	CObjectController* controller = (CObjectController *)getController();
	//Check controller.
	if(controller != _NULL) V_RETURN(controller->setViewPort(viewPort));
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CControllerAttribute::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr = FALSE;

	//Get controller.
	CObjectController* controller = (CObjectController *)getController();
	//Check controller.
	if(controller != _NULL) V_RETURN(controller->handleMessage(d3dxEvent));
	//Return result.
	return hr;
}
