///////////////////////////////////////////////////////////////////////////////
//
// D3DXCompoundObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXCompoundObject.h"

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
const C4DBase CD3DXCompoundObject::base(L"CD3DXCompoundObject",L"CD3DXRenderableObject");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXCompoundObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXCompoundObject::CD3DXCompoundObject(void)
{
	//Set default value.
	initialized = _FALSE;
	//Disable scalable.
	CWorldObject::setScalable(_FALSE);

	//Set this.
	setThis(this);
	//Set object type.
	CWorldObject::setObjectType(CWorldObject::compoundObject);
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXCompoundObject
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXCompoundObject::~CD3DXCompoundObject(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// ClearTexture
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXCompoundObject::clearTexture(const CNormalString& name)
{
	//Enumeration.
	CListNodeEnumeration iterator;

	//Get enumeration.
	getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Check result.
		if(object->isRenderableObject())
		{
			//Get renderable object.
			CD3DXRenderableObject* renderableObject =
				(CD3DXRenderableObject *)object->getRenderable();
#ifdef _DEBUG
			assert(renderableObject != _NULL);
#endif
			//Clear reference.
			renderableObject->clearTexture(name);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// AddObject
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXCompoundObject::addObject(CD3DXRenderableObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
	//The joint object cannot be a child object.
	assert(object->getObjectType() != CTypeAttribute::jointObject);
#endif
	//Add object.
	CWorldObject::addObject(object);
}

/////////////////////////////////////////////////////////////////////////////////
//
// AddObject
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXPrimitiveObject* CD3DXCompoundObject::addObject(CResourceManager* resourceManager,const CNormalString& name)
{
#ifdef _DEBUG
	assert(name.length() > 0);
	assert(resourceManager != _NULL);
#endif

	//Create a object.
	CD3DXPrimitiveObject* object = new CD3DXPrimitiveObject();
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Select renderable.
	object->selectRenderable(resourceManager,name);
	//Add it into list.
	CWorldObject::addObject(object);
	//Return result.
	return object;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Pick
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CD3DXCompoundObject::pick(CPickRay& pickRay,CPickResult& result)
{
	//Flag.
	_BOOL flag = _FALSE;
	//Enumeration.
	CListNodeEnumeration iterator;

	//Get enumeration.
	getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Check result.
		if(object->isRenderableObject())
		{
			//Get renderable object.
			CD3DXRenderableObject* renderableObject =
				(CD3DXRenderableObject *)object->getRenderable();
			//Get pick.
			if(renderableObject->pick(pickRay,result)) flag = _TRUE;
		}
	}
	//Return result.
	return flag;
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateObjects
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CD3DXCompoundObject::createObjects(CResourceApplication* resourceApplication)
{
#ifdef _DEBUG
	assert(initialized == _FALSE);
	assert(resourceApplication != _NULL);
#endif
	//Set flag.
	initialized = _TRUE;
	//Initialize objects.
	return SUCCEEDED(initializeObjects(resourceApplication)) ? _TRUE : _FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXCompoundObject::initializeObjects(CResourceApplication* resourceApplication)
{
#ifdef _DEBUG
	assert(resourceApplication != _NULL);
#endif
	//Return OK.
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetViewPort
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXCompoundObject::setViewPort(CViewPort* viewPort)
{
	//Result.
	HRESULT hr = S_OK;
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(viewPort != _NULL);
#endif

	//Get enumeration.
	getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != NULL);
#endif
		//Check renderable.
		if(object->isRenderableObject())
		{
			//Get renderable object.
			CD3DXRenderableObject* renderableObject =
				(CD3DXRenderableObject *)object->getRenderable();
			//Check result.
			if(FAILED(renderableObject->setViewPort(viewPort))) hr = E_FAIL;
		}
	}
	//Set view port.
	if(FAILED(CD3DXRenderableObject::setViewPort(viewPort))) hr = E_FAIL;
	//Return result.
	return hr;
}

/////////////////////////////////////////////////////////////////////////////////
//
// DispatchMessage
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXCompoundObject::dispatchMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr = FALSE;
	//Enumeration.
	CListNodeEnumeration iterator;

	//Get enumeration.
	getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != NULL);
#endif
		//Check renderable.
		if(object->isRenderableObject())
		{
			//Get renderable object.
			CD3DXRenderableObject* renderableObject =
				(CD3DXRenderableObject *)object->getRenderable();
			//Get result.
			if(FAILED(renderableObject->handleMessage(d3dxEvent))) hr = E_FAIL;
		}
	}
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXCompoundObject::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != NULL);
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
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
			V_RETURN(initializeObjects((CD3DXApplication *)d3dxEvent.pUserContext));
		}
		//
		///////////////////////////////////////
		break;
	}
	//Dispatch message to all its children.
	//You can control children's action from settings.
	V_RETURN(dispatchMessage(d3dxEvent));
	//Return result.
	return CD3DXRenderableObject::handleMessage(d3dxEvent);
}
