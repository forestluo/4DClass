///////////////////////////////////////////////////////////////////////////////
//
// ViewPortApplication.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ViewPortApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// CViewPortApplication
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CViewPortApplication::CViewPortApplication(void)
{
	//Set default value.
	viewPort = (CViewPort *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CViewPortApplication
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CViewPortApplication::~CViewPortApplication(void)
{
	//Delete view port.
	if(viewPort != _NULL)
	{
		//Delete view port.
		delete (CViewPort *)viewPort;
		//Clear view port.
		viewPort = (CViewPort *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetViewPort
//
///////////////////////////////////////////////////////////////////////////////

CViewPort* CViewPortApplication::getViewPort() const
{
	//Return result.
	return viewPort;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetViewPort
//
///////////////////////////////////////////////////////////////////////////////

void CViewPortApplication::setViewPort(CViewPort* viewPort)
{
#ifdef _DEBUG
	assert(viewPort != _NULL);
#endif
	//Set value.
	this->viewPort = viewPort;
}

///////////////////////////////////////////////////////////////////////////////
//
// ZAxisView
//
///////////////////////////////////////////////////////////////////////////////

void CViewPortApplication::zAxisView()
{
	C4DVector3 vEyeAt;
	C4DVector3 vEyeLookAt;
	C4DVector3 vDirection;

#ifdef _DEBUG
	assert(viewPort != _NULL);
#endif

	//Open lock.
	openLock();
	{
		//Get eye at.
		vEyeAt = viewPort->getEyeAt();
		//Get eye look at.
		vEyeLookAt = viewPort->getEyeLookAt();

		//Calculate distance.
		vDirection = vEyeAt - vEyeLookAt;
		//Get length.
		_FLOAT fLength = vDirection.length();

		//Set eye at.
		vEyeLookAt.x() = vEyeLookAt.y() = vEyeLookAt.z() = 0.0f;
		//Set at.
		vEyeAt.x() = vEyeAt.y() = 0.0f;	vEyeAt.z() = fLength > 0 ? -fLength : -1.0f;
		//Set look at.
		viewPort->setViewParameters(vEyeAt,vEyeLookAt);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// XAxisView
//
///////////////////////////////////////////////////////////////////////////////

void CViewPortApplication::xAxisView()
{
	C4DVector3 vEyeAt;
	C4DVector3 vEyeLookAt;
	C4DVector3 vDirection;

#ifdef _DEBUG
	assert(viewPort != _NULL);
#endif

	//Open lock.
	openLock();
	{
		//Get eye at.
		vEyeAt = viewPort->getEyeAt();
		//Get eye look at.
		vEyeLookAt = viewPort->getEyeLookAt();

		//Calculate distance.
		vDirection = vEyeAt - vEyeLookAt;
		//Get length.
		_FLOAT fLength = vDirection.length();

		//Set eye at.
		vEyeLookAt.x() = vEyeLookAt.y() = vEyeLookAt.z() = 0.0f;
		//Set at.
		vEyeAt.y() = vEyeAt.z() = 0.0f;	vEyeAt.x() = fLength > 0 ? -fLength : -1.0f;
		//Set look at.
		viewPort->setViewParameters(vEyeAt,vEyeLookAt);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// yAxisView
//
///////////////////////////////////////////////////////////////////////////////

void CViewPortApplication::yAxisView()
{
	C4DVector3 vEyeAt;
	C4DVector3 vEyeLookAt;
	C4DVector3 vDirection;

#ifdef _DEBUG
	assert(viewPort != _NULL);
#endif

	//Open lock.
	openLock();
	{
		//Get eye at.
		vEyeAt = viewPort->getEyeAt();
		//Get eye look at.
		vEyeLookAt = viewPort->getEyeLookAt();

		//Calculate distance.
		vDirection = vEyeAt - vEyeLookAt;
		//Get length.
		_FLOAT fLength = vDirection.length();

		//Set eye at.
		vEyeLookAt.x() = vEyeLookAt.y() = vEyeLookAt.z() = 0.0f;
		//Set at.
		vEyeAt.x() = vEyeAt.z() = 0.0f;	vEyeAt.y() = fLength > 0 ? -fLength : -1.0f;
		//Set look at.
		viewPort->setViewParameters(vEyeAt,vEyeLookAt);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CViewPortApplication::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(viewPort != _NULL);
#endif
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Handle key presses.
	case d3dxMsgProc:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing != NULL);
#endif
		//Handle message.
		if(viewPort->handleMessage(d3dxEvent))
		{
			//Set flag.
			*d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing = true;
		}
		break;
	//Message process.
	case d3dxOnKeyboard:
		break;
	//Handle updates to the scene.
	case d3dxOnFrameMove:
		//Handle message.
		V_RETURN(viewPort->handleMessage(d3dxEvent));
		break;
	//Render the scene using the D3D9 device.
	case d3dxOnD3D9FrameRender:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxFrameRender9.pd3dDevice != NULL);
#endif
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Handle message.
		V_RETURN(viewPort->handleMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		V_RETURN(viewPort->handleMessage(d3dxEvent));
		//break;
		break;
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Handle message.
		V_RETURN(viewPort->handleMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		V_RETURN(viewPort->handleMessage(d3dxEvent));
		//break.
		break;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
