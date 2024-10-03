///////////////////////////////////////////////////////////////////////////////
//
// ObjectController.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ObjectController.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CObjectController::base(L"CObjectController",L"CObjectSketcher");

///////////////////////////////////////////////////////////////////////////////
//
// CObjectController
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CObjectController::CObjectController(void)
{
	//Set default value.
	drawBox = _TRUE;
	drawAxis = _TRUE;
	selected = _FALSE;
	//Set translation radius.
	ball.SetTranslationRadius(1.0f);
}

///////////////////////////////////////////////////////////////////////////////
//
// CObjectController
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CObjectController::~CObjectController(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// DetachObject
//
///////////////////////////////////////////////////////////////////////////////

void CObjectController::detachObject()
{
#ifdef _DEBUG
	assert(owner != _NULL);
#endif
	//Set rotation.
	owner->setRotation(C4DQuaternion(*ball.GetQuatNow()));
	//Detach object.
	CObjectSketcher::detachObject();
}

///////////////////////////////////////////////////////////////////////////////
//
// AttachObject
//
///////////////////////////////////////////////////////////////////////////////

void CObjectController::attachObject(CWorldObject* owner)
{
#ifdef _DEBUG
	assert(owner != _NULL);
#endif
	//Attach object.
	CObjectSketcher::attachObject(owner);
	//Set rotation.
	setRotation(owner->getRotation());
}

///////////////////////////////////////////////////////////////////////////////
//
// GetRotation
//
///////////////////////////////////////////////////////////////////////////////

C4DQuaternion CObjectController::getRotation() const
{
	//Return quaternion.
	return C4DQuaternion(*ball.GetQuatNow());
}

///////////////////////////////////////////////////////////////////////////////
//
// SetRotation
//
///////////////////////////////////////////////////////////////////////////////

void CObjectController::setRotation(const C4DQuaternion& rotation)
{
	//Set quaternion.
	ball.SetQuatNow(D3DXQUATERNION(rotation));
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CObjectController::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	//Do not dispatch any message to its effect or proerty.
	switch(d3dxEvent.d3dxEventID)
	{
	//On frame move.
	case d3dxOnFrameMove:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != NULL);
#endif
		//Do not handle message when simulation is running.
		if(((CD3DXApplication *)d3dxEvent.pUserContext)->isRunning())
		{
			//Synchronize the rotation of the owner.
			//The owner is controlled by physics engine.
			if(owner != _NULL) setRotation(owner->getRotation());
		}
		else
		{
			//The owner is controlled by controller.
			if(owner != _NULL) owner->setRotation(getRotation());
		}
		break;
	//Handle key presses.
	case d3dxMsgProc:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != NULL);
		assert(d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing != NULL);
#endif
		//Do not handle message when object is not rotatable.
		if(owner == _NULL || !owner->isRotatable()) break;
		//The control key must be set.
		if(!(d3dxEvent.d3dxMsgProc.wParam & MK_CONTROL)) break;
		//Do not handle message when simulation is running.
		if(!((CD3DXApplication *)d3dxEvent.pUserContext)->isRunning())
		{
			///////////////////////////////////////
			//
			// Let control ball handle message.
			//
			//Get view matrix.
			D3DXMATRIXA16 mViewRotate = (((CD3DXApplication *)d3dxEvent.pUserContext)->getViewPort())->getViewMatrix();
			//Clear some parameters.
			mViewRotate._41 = mViewRotate._42 = mViewRotate._43 = 0.0f;
			//Do inverse.
			D3DXMatrixInverse(&mViewRotate,NULL,&mViewRotate);
			//Handle message.
			ball.HandleMessages(d3dxEvent.d3dxMsgProc.hWnd,d3dxEvent.d3dxMsgProc.uMsg,
								d3dxEvent.d3dxMsgProc.wParam,d3dxEvent.d3dxMsgProc.lParam,&mViewRotate);
			//
			///////////////////////////////////////
		}
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Set window of ball.
		ball.SetWindow(GetBackBufferSurfaceWidth(d3dxEvent.d3dxResetDevice9),
					   GetBackBufferSurfaceHeight(d3dxEvent.d3dxResetDevice9));
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Set window of ball.
		ball.SetWindow(GetBackBufferSurfaceWidth(d3dxEvent.d3dxResetDevice9),
					   GetBackBufferSurfaceHeight(d3dxEvent.d3dxResetDevice9));
		break;
	}
	//Return result.
	return CObjectSketcher::handleMessage(d3dxEvent);
}
