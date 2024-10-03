///////////////////////////////////////////////////////////////////////////////
//
// D3DXObject.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXObject::base(L"CD3DXObject",L"CObject");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXObject::CD3DXObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXObject::~CD3DXObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXObject::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Handle key presses.
	case d3dxMsgProc:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing != NULL);
#endif
		break;
	//Message process.
	case d3dxOnKeyboard:
		break;
	//Handle updates to the scene.
	case d3dxOnFrameMove:
		break;
	//Render the scene using the D3D9 device.
	case d3dxOnD3D9FrameRender:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxFrameRender9.pd3dDevice != NULL);
#endif
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		break;
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		break;
	default:
#ifdef _DEBUG
		assert((d3dxEvent.d3dxEventID >= 0x01 && d3dxEvent.d3dxEventID <= 0x03) ||
			(d3dxEvent.d3dxEventID >= 0x0901 && d3dxEvent.d3dxEventID <= 0x0905));
#endif
		//Return failed.
		return E_FAIL;
	}
	//Return result.
	return FALSE;
}
