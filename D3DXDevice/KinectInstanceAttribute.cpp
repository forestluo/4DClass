///////////////////////////////////////////////////////////////////////////////
//
// KinectInstanceAttribute.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "KinectInstanceAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "MSR_NuiApi.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define NUI_INSTANCE(p)										((INuiInstance *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Resolution mode.
const _INTEGER CKinectInstanceAttribute::vgaResolution			= NUI_IMAGE_RESOLUTION_640x480;
const _INTEGER CKinectInstanceAttribute::qvgaResolution			= NUI_IMAGE_RESOLUTION_320x240;
const _INTEGER CKinectInstanceAttribute::qqvgaResolution		= NUI_IMAGE_RESOLUTION_80x60;

///////////////////////////////////////////////////////////////////////////////
//
// CKinectInstanceAttribute
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectInstanceAttribute::CKinectInstanceAttribute(void)
{
	//Set default value.
	index = 0;
	resolution = 0;
	instanceID = (BSTR)_NULL;
	nuiInstance = (INuiInstance *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CKinectInstanceAttribute
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectInstanceAttribute::~CKinectInstanceAttribute(void)
{
	//Destroy instance.
	destroyInstance();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetIndex
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CKinectInstanceAttribute::getIndex() const
{
	//Return result.
	return index;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetDevice
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CKinectInstanceAttribute::getDevice() const
{
	//Return result.
	return nuiInstance;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetResolution
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CKinectInstanceAttribute::getResolution() const
{
	//Return result.
	return resolution;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetResolutionWidth
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CKinectInstanceAttribute::getResolutionWidth() const
{
	//Check resolution.
	switch(resolution)
	{
	case NUI_IMAGE_RESOLUTION_640x480:
		return 640;
	case NUI_IMAGE_RESOLUTION_320x240:
		return 320;
	case NUI_IMAGE_RESOLUTION_80x60:
		return 80;
	default:
		break;
	}
#ifdef _DEBUG
	assert(_FALSE);
#endif
	//Return -1.
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetResolutionHeight
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CKinectInstanceAttribute::getResolutionHeight() const
{
	//Check mode.
	switch(resolution)
	{
	case NUI_IMAGE_RESOLUTION_640x480:
		return 480;
	case NUI_IMAGE_RESOLUTION_320x240:
		return 240;
	case NUI_IMAGE_RESOLUTION_80x60:
		return 60;
	default:
		break;
	}
#ifdef _DEBUG
	assert(_FALSE);
#endif
	//Return -1.
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
//
// DestroyInstance
//
///////////////////////////////////////////////////////////////////////////////

void CKinectInstanceAttribute::destroyInstance()
{
	//Check instance id.
	if(instanceID != _NULL)
	{
		//Free and clear string.
		::SysFreeString((BSTR)instanceID);
		//Clear system id.
		instanceID = (BSTR)_NULL;
	}
	//Check instance.
	if(nuiInstance != _NULL)
	{
		//Shutdown.
		NUI_INSTANCE(nuiInstance)->NuiShutdown();
		//Destroy instance.
		MSR_NuiDestroyInstance(NUI_INSTANCE(nuiInstance));
		//Clear instance.
		nuiInstance = (INuiInstance *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateInstance
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CKinectInstanceAttribute::createInstance(_INTEGER index,_INTEGER resolution)
{
#ifdef _DEBUG
	assert(index >= 0);
	assert(nuiInstance == _NULL);
	assert(resolution == vgaResolution || resolution == qvgaResolution || resolution == qqvgaResolution);
#endif
	//Create instance by index.
	if(FAILED(MSR_NuiCreateInstanceByIndex(index,(INuiInstance **)&nuiInstance))) return _FALSE;
#ifdef _DEBUG
	assert(instanceID == _NULL);
#endif
	//Set index.
	this->index = index;
	//Set mode.
	this->resolution = resolution;

	//Get instance id.
	instanceID = NUI_INSTANCE(nuiInstance)->NuiInstanceName();
#ifdef _DEBUG
	assert(instanceID != _NULL);
#endif
	//Initialize instance.
	return SUCCEEDED(NUI_INSTANCE(nuiInstance)->NuiInitialize(
														NUI_INITIALIZE_FLAG_USES_DEPTH |
														NUI_INITIALIZE_FLAG_USES_COLOR)) ? _TRUE : _FALSE;
}