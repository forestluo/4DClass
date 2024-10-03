///////////////////////////////////////////////////////////////////////////////
//
// D3DXFilter.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXFilter.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXFilter::base(L"CD3DXFilter",L"CD3DXResource");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXFilter
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXFilter::CD3DXFilter(void)
{
	//Set default value.
	device = (CD3DXDevice *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXFilter
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXFilter::~CD3DXFilter(void)
{
	//Check device.
	if(device != _NULL)
	{
		//Release device.
		device->releaseReference();
		//Clear device.
		device = (CD3DXDevice *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetDevice
//
///////////////////////////////////////////////////////////////////////////////

CD3DXDevice* CD3DXFilter::getDevice() const
{
	//Return result.
	return device;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetDeviceName
//
///////////////////////////////////////////////////////////////////////////////

const CNormalString& CD3DXFilter::getDeviceName() const
{
	//Return result.
	return deviceName;
}

///////////////////////////////////////////////////////////////////////////////
//
// SelectDevice
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CD3DXFilter::selectDevice(CResourceManager* resourceManager,const CNormalString& name)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL && name.length() > 0);
#endif
	//Check device.
	if(device != _NULL)
	{
		//Release device.
		device->releaseReference();
		//Clear device.
		device = (CD3DXDevice *)_NULL;
	}
	//Get resource.
	CD3DXResource* resource = resourceManager->getResource(name);
#ifdef _DEBUG
	assert(resource != _NULL && IS_DEVICE_BASE(resource));
#endif
	//Set name.
	deviceName = name;
	//Add reference.
	resource->addReference();
	//Set device.
	this->device = (CD3DXDevice *)resource;
	//Return true.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXFilter::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Check device.
		if(device != _NULL)
		{
			//Release device.
			device->releaseReference();
			//Clear device.
			device = (CD3DXDevice *)_NULL;
		}
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != _NULL);
#endif
		//Check device name.
		if(deviceName.length() > 0)
		{
			//Get resource manager.
			CResourceManager* resourceManager = ((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager();
#ifdef _DEBUG
			assert(resourceManager != _NULL);
#endif
			//Get resource.
			CD3DXResource* resource = resourceManager->getResource(deviceName);
#ifdef _DEBUG
			assert(resource != _NULL && IS_DEVICE_BASE(resource));
#endif
			//Add reference.
			resource->addReference();
#ifdef _DEBUG
			assert(this->device == _NULL);
#endif
			//Set device reference.
			this->device = (CD3DXDevice *)resource;
		}
		break;
	}
	//Return result.
	return CD3DXResource::handleMessage(d3dxEvent);
}
