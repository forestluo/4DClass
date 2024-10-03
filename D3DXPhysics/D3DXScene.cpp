///////////////////////////////////////////////////////////////////////////////
//
// D3DXScene.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXScene::base(L"CD3DXScene",L"CD3DXObject");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXScene
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXScene::CD3DXScene(void)
{
	//Initialized.
	initialized = _FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXScene
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXScene::~CD3DXScene(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXScene::initializeObjects(CResourceManager* resourceManager)
{
	//Return ok.
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//
// AddObject
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXScene::addObject(CD3DXRenderableObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Add it into scene.
	CWorldGroup::addObject(object);
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXScene::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Handle key presses.
	case d3dxOnKeyboard:
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	//Handle key presses.
	case d3dxMsgProc:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing != NULL);
#endif
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
		assert(d3dxEvent.pUserContext != NULL);
#endif
		///////////////////////////////////////
		//
		// Initialize the scene only once.
		//
		//Check initialized flag.
		if(!initialized)
		{
			//Set flag.
			initialized = _TRUE;
			//Initialize objects.
			V_RETURN(initializeObjects(((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager()));
		}
		//
		///////////////////////////////////////
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	case d3dxOnFrameMove:
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	//Render the scene using the D3D9 device.
	case d3dxOnD3D9FrameRender:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxFrameRender9.pd3dDevice != NULL);
#endif
		//These events are to help PIX identify what the code is doing.
        DXUT_BeginPerfEvent(DXUT_PERFEVENTCOLOR,L"Scene"); 
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		//End performance event.
        DXUT_EndPerfEvent();
		break;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
