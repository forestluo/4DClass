///////////////////////////////////////////////////////////////////////////////
//
// KinectManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "KinectManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <XnCppWrapper.h>

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define CONTEXT_INSTANCE(p)									((xn::Context *)(p))
#define DEVICELIST_INSTANCE(p)								((xn::NodeInfoList *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CKinectManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectManager::CKinectManager(void)
{
	//Create context.
	context = new xn::Context();
#ifdef _DEBUG
	assert(context != _NULL);
#endif
	//Create device list.
	deviceList = new xn::NodeInfoList();
#ifdef _DEBUG
	assert(deviceList != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CKinectManager
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectManager::~CKinectManager(void)
{
	//Check device list.
	if(deviceList != _NULL)
	{
		//Clear.
		DEVICELIST_INSTANCE(deviceList)->Clear();

		//Delete device list.
		delete (xn::NodeInfoList *)deviceList;
		//Clear device list.
		deviceList = (xn::NodeInfoList *)_NULL;
	}
	//Check context.
	if(context != _NULL)
	{
		//Release.
		CONTEXT_INSTANCE(context)->Release();

		//Delete context.
		delete (xn::Context *)context;
		//Clear context.
		context = (xn::Context *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// InitialzieDevices
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CKinectManager::initializeDevices()
{
	//Status.
	XnStatus result;

	//Initialize context.
	result = CONTEXT_INSTANCE(context)->Init();
	//Check result.
	if(result != XN_STATUS_OK) return _FALSE;
	//Enumerate devices.
	result = CONTEXT_INSTANCE(context)->EnumerateProductionTrees(XN_NODE_TYPE_DEVICE,NULL,*DEVICELIST_INSTANCE(deviceList));
	//Check result.
	if(result != XN_STATUS_OK) return _FALSE;
	//Return result.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CKinectManager::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
