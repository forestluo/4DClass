///////////////////////////////////////////////////////////////////////////////
//
// D3DXResourceGroup.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXResourceGroup.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXApplication.h"
#include "HashListContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define RESOURCES_INSTANCE(p)								((CHashListContainer *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

#pragma init_seg(".CRT$XCE")
//Set base of object.
const C4DBase CD3DXResourceGroup::base(L"CD3DXResourceGroup",L"CD3DXObject");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXResourceGroup
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXResourceGroup::CD3DXResourceGroup(void)
{
	//Create resources.
	resources = new CHashListContainer();
#ifdef _DEBUG
	assert(resources != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXResourceGroup
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXResourceGroup::~CD3DXResourceGroup(void)
{
	//Release all.
	releaseAll();
	//Check resources.
	if(resources != _NULL)
	{
		//Delete resources.
		delete (CHashListContainer *)resources;
		//Clear resources.
		resources = (CHashListContainer *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ReleaseResources
//
// Some resources need reload, some need not.
// Currently, just release all of it. And reload all from file again.
// Should be careful to the reference of these object. All the references should be updated.
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXResourceGroup::releaseResources()
{
	//Release all.
	releaseAll();
	//Return result.
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//
// ReleaseAll
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXResourceGroup::releaseAll()
{
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(resources != _NULL);
#endif

	//Get enumeration.
	RESOURCES_INSTANCE(resources)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get resources.
		CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
		assert(resource != _NULL);
		assert(resource->countReference() == 0);
#endif
		//Delete resource.
		delete (CD3DXResource *)resource;
	}
	//Clear members.
	RESOURCES_INSTANCE(resources)->clearAll();
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetCount.
//
/////////////////////////////////////////////////////////////////////////////////

_INTEGER CD3DXResourceGroup::getCount() const
{
#ifdef _DEBUG
	assert(resources != _NULL);
#endif
	//Return result.
	return RESOURCES_INSTANCE(resources)->getCount();
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetCount.
//
/////////////////////////////////////////////////////////////////////////////////

_INTEGER CD3DXResourceGroup::getCount(_LONG classCode)
{
	//Count.
	_INTEGER count = 0;
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(resources != _NULL);
#endif

	//Get enumeration.
	RESOURCES_INSTANCE(resources)->getEnumeration(&iterator);
	//Check result.
	while(iterator.hasMoreElements())
	{
		//Get next element.
		CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
		assert(resource != NULL);
#endif
		//Check result.
		if(resource->classCode() == classCode) count ++;
	}
	//Return result.
	return count;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetEnumeration.
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXResourceGroup::getEnumeration(CListNodeEnumeration& enumeration)
{
#ifdef _DEBUG
	assert(resources != _NULL);
#endif
	//Get enumeration.
	RESOURCES_INSTANCE(resources)->getEnumeration(&enumeration);
}

/////////////////////////////////////////////////////////////////////////////////
//
// AddResource
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXResourceGroup::addResource(CD3DXResource* resource)
{
#ifdef _DEBUG
	assert(resource != _NULL);
	assert(resource->getName().length() > 0);
#endif

#ifndef _DEBUG
	//Add it into map.
	RESOURCES_INSTANCE(resources)->setValue(C4DString::hashCode((_STRING)resource->getName().getCString()),(_OBJECT)resource);
#else
	//Add it into map.
	assert(RESOURCES_INSTANCE(resources)->setValue(C4DString::hashCode((_STRING)resource->getName().getCString()),(_OBJECT)resource) == _NULL);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetResource
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXResource* CD3DXResourceGroup::getResource(const CNormalString& name)
{
#ifdef _DEBUG
	assert(name.length() > 0);
	assert(resources != _NULL);
#endif
	//Get value.
	return (CD3DXResource *)RESOURCES_INSTANCE(resources)->getValue(C4DString::hashCode((_STRING)name.getCString()));
}

/////////////////////////////////////////////////////////////////////////////////
//
// RemoveResource
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXResource* CD3DXResourceGroup::removeResource(const CNormalString& name)
{
#ifdef _DEBUG
	assert(name.length() > 0);
	assert(resources != _NULL);
#endif
	//Get value.
	return (CD3DXResource *)RESOURCES_INSTANCE(resources)->removeValue(C4DString::hashCode((_STRING)name.getCString()));
}

/////////////////////////////////////////////////////////////////////////////////
//
// DispatchMessage
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXResourceGroup::dispatchMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr = FALSE;
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(resources != _NULL);
#endif

	//Get enumeration.
	RESOURCES_INSTANCE(resources)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get resource.
		CD3DXResource* resource = (CD3DXResource *)iterator.nextElement();
#ifdef _DEBUG
		assert(resource != _NULL);
#endif
		//Handle message.
		if(FAILED(resource->handleMessage(d3dxEvent))) hr = E_FAIL;
	}
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXResourceGroup::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//On frame move.
	case d3dxOnFrameMove:
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		//Release resources.
		V_RETURN(releaseResources());
		break;
		//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
		assert(d3dxEvent.pUserContext != NULL);
#endif
		//Create resources.
		V_RETURN(createResources(((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager()));
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
