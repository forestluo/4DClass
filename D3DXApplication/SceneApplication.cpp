///////////////////////////////////////////////////////////////////////////////
//
// SceneApplication.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "SceneApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// CSceneApplication
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CSceneApplication::CSceneApplication(void)
{
	//Set default value.
	background = (CBackgroundScene *)_NULL;
	foreground = (CForegroundScene *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CSceneApplication
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CSceneApplication::~CSceneApplication(void)
{
	//Check background.
	if(background != _NULL)
	{
		//Delete background.
		delete (CBackgroundScene *)background;
		//Clear background.
		background = (CBackgroundScene *)_NULL;
	}
	//Check foreground.
	if(foreground != _NULL)
	{
		//Delete foreground.
		delete (CForegroundScene *)foreground;
		//Clear foreground.
		foreground = (CForegroundScene *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearBackground 
//
///////////////////////////////////////////////////////////////////////////////

void CSceneApplication::clearBackground(IDirect3DDevice9* pd3dDevice)
{
	//Result value.
	HRESULT hr;

#ifdef _DEBUG
	assert(pd3dDevice != _NULL);
#endif
	//Clear the render target and the zbuffer. 
	V(pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_ARGB(0,45,50,170),1.0f,0));
}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeRenderState
//
// Set render state before rendering.
//
///////////////////////////////////////////////////////////////////////////////

void CSceneApplication::initializeRenderState(IDirect3DDevice9* pd3dDevice)
{
#ifdef _DEBUG
	assert(pd3dDevice != _NULL);
#endif
	//Turn on ambient lighting. 
    pd3dDevice->SetRenderState(D3DRS_AMBIENT,0xFFFFFFFF);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetForeground
//
///////////////////////////////////////////////////////////////////////////////

CForegroundScene* CSceneApplication::getForeground() const
{
	//Return result.
	return foreground;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetForeground
//
///////////////////////////////////////////////////////////////////////////////

void CSceneApplication::setForeground(CForegroundScene* foreground)
{
#ifdef _DEBUG
	assert(foreground != _NULL);
#endif
	//Set value.
	this->foreground = foreground;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetBackground
//
///////////////////////////////////////////////////////////////////////////////

CBackgroundScene* CSceneApplication::getBackground() const
{
	//Return result.
	return background;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetBackground
//
///////////////////////////////////////////////////////////////////////////////

void CSceneApplication::setBackground(CBackgroundScene* background)
{
#ifdef _DEBUG
	assert(background != _NULL);
#endif
	//Set value.
	this->background = background;
}

/////////////////////////////////////////////////////////////////////////////////
//
// ClearTexture
//
/////////////////////////////////////////////////////////////////////////////////

void CSceneApplication::clearTexture(const CNormalString& name)
{
#ifdef _DEBUG
	assert(foreground != _NULL);
#endif
	//Clear texture.
	foreground->clearTexture(name);

#ifdef _DEBUG
	assert(background != NULL);
#endif
	//Clear texture.
	background->clearTexture(name);
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CSceneApplication::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(background != _NULL && foreground != _NULL);
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
		if(background->handleMessage(d3dxEvent))
		{
			//Set flag.
			*d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing = true;
		}
		else if(foreground->handleMessage(d3dxEvent))
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
		V_RETURN(background->handleMessage(d3dxEvent));
		V_RETURN(foreground->handleMessage(d3dxEvent));
		break;
	//Render the scene using the D3D9 device.
	case d3dxOnD3D9FrameRender:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxFrameRender9.pd3dDevice != NULL);
		assert(d3dxEvent.pUserContext != NULL);
#endif
		//Initialize render state.
		initializeRenderState(d3dxEvent.d3dxCreateDevice9.pd3dDevice);
		//Clear backckground.
		clearBackground(d3dxEvent.d3dxFrameRender9.pd3dDevice);
		//Render the scene.
		if(SUCCEEDED(d3dxEvent.d3dxFrameRender9.pd3dDevice->BeginScene()))
		{
			//Get view port.
			CViewPort* viewPort = ((CD3DXApplication *)d3dxEvent.pUserContext)->getViewPort();
#ifdef _DEBUG
			assert(viewPort != _NULL);
#endif
			//Next timestamp.
			viewPort->nextFrameStamp();

			//Set view port.
			V_RETURN(background->setViewPort(viewPort));
			//Handle message.
			V_RETURN(background->handleMessage(d3dxEvent));

			//Set view port.
			V_RETURN(foreground->setViewPort(viewPort));
			//Handle message.
			V_RETURN(foreground->handleMessage(d3dxEvent));

			//End scence.
			V(d3dxEvent.d3dxFrameRender9.pd3dDevice->EndScene());
		}
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Handle message.
		V_RETURN(foreground->handleMessage(d3dxEvent));
		V_RETURN(background->handleMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		V_RETURN(background->handleMessage(d3dxEvent));
		V_RETURN(foreground->handleMessage(d3dxEvent));
		//break;
		break;
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Handle message.
		V_RETURN(foreground->handleMessage(d3dxEvent));
		V_RETURN(background->handleMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		V_RETURN(background->handleMessage(d3dxEvent));
		V_RETURN(foreground->handleMessage(d3dxEvent));
		//break.
		break;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
