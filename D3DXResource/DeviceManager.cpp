///////////////////////////////////////////////////////////////////////////////
//
// DeviceManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "DeviceManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

#pragma init_seg(".CRT$XCE")
//Set base of object.
const C4DBase CDeviceManager::base(L"CDeviceManager",L"CD3DXResourceGroup");

///////////////////////////////////////////////////////////////////////////////
//
// CDeviceManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CDeviceManager::CDeviceManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CDeviceManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CDeviceManager::~CDeviceManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CreateResources
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CDeviceManager::createResources(_OBJECT resourceManager)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif
	//The device is created dynamically.
	//Normally it is not depended on other resources.
	//Return ok.
	return S_OK;
}