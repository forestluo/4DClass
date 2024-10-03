///////////////////////////////////////////////////////////////////////////////
//
// D3DXDeviceReference.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXDeviceReference.h"

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXDeviceReference
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXDeviceReference::CD3DXDeviceReference(void)
{
	//Set default value.
	d3dxDevice = (IDirect3DDevice9*)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXDeviceReference
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXDeviceReference::~CD3DXDeviceReference(void)
{
	//Clear device.
	d3dxDevice = (IDirect3DDevice9*)_NULL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetDevice
//
/////////////////////////////////////////////////////////////////////////////////

IDirect3DDevice9* CD3DXDeviceReference::getDevice() const
{
	//Return result.
	return d3dxDevice;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXDeviceReference::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Clear device.
		d3dxDevice = (IDirect3DDevice9*)_NULL;
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != NULL);
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Set device.
		d3dxDevice = d3dxEvent.d3dxCreateDevice9.pd3dDevice;
		break;
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Clear device.
		d3dxDevice = (IDirect3DDevice9*)_NULL;
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Set device.
		d3dxDevice = d3dxEvent.d3dxCreateDevice9.pd3dDevice;
		break;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
