///////////////////////////////////////////////////////////////////////////////
//
// D3DXJointObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXJointObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "D3DXApplication.h"
#include "D3DXJointObjectProxy.h"

#include "D3DXCompoundObject.h"
#include "D3DXClassicBallJointObjectProxy.h"
#include "D3DXClassicHingeJointObjectProxy.h"
#include "D3DXClassicCorkscrewJointObjectProxy.h"
#include "D3DXClassicSliderJointObjectProxy.h"
#include "D3DXClassicUniversalJointObjectProxy.h"
#include "D3DXClassicUpVectorJointObjectProxy.h"

#include "D3DXCustom6DOFJointObjectProxy.h"
#include "D3DXCustomBallJointObjectProxy.h"
#include "D3DXCustomHingeJointObjectProxy.h"
#include "D3DXCustomSliderJointObjectProxy.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define	PROXY_INSTANCE(p)									((CD3DXJointObjectProxy *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXJointObject::base(L"CD3DXJointObject",L"CD3DXRenderableObject");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXJointObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXJointObject::CD3DXJointObject(_INTEGER jointType)
	: CWorldJointObject(jointType)
{
	//Set default value.
	initialized = _FALSE;
	//Disable scalable.
	CWorldObject::setScalable(_FALSE);
	//Disable rotatable.
	CWorldObject::setRotatable(_FALSE);

	//Set this.
	setThis(this);
	//Set type.
	CWorldObject::setObjectType(CWorldObject::jointObject);

#ifdef _DEBUG
	assert(jointType != CJointAttribute::nullJoint);
#endif
	//Check joint type.
	if(jointType == CJointAttribute::classicBallJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicBallJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::classicCorkscrewJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicCorkscrewJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::classicHingeJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicHingeJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::classicSliderJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicSliderJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::classicUniversalJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicUniversalJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::classicUpVectorJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicUpVectorJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::custom6DOFJoint)
	{
		//Create proxy.
		proxy = new CD3DXCustom6DOFJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::customBallJoint)
	{
		//Create proxy.
		proxy = new CD3DXCustomBallJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::customHingeJoint)
	{
		//Create proxy.
		proxy = new CD3DXCustomHingeJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::customSliderJoint)
	{
		//Create proxy.
		proxy = new CD3DXCustomSliderJointObjectProxy(this);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif

#ifdef _DEBUG
	assert(proxy != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXJointObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXJointObject::CD3DXJointObject(const CJointAttribute& attribute)
	: CWorldJointObject(attribute)
{
	//Set default value.
	initialized = _FALSE;
	//Disable scalable.
	CWorldObject::setScalable(_FALSE);
	//Disable rotatable.
	CWorldObject::setRotatable(_FALSE);

	//Set this.
	setThis(this);
	//Set type.
	CWorldObject::setObjectType(CWorldObject::jointObject);

	//Get joint type.
	_INTEGER jointType = attribute.getType();
#ifdef _DEBUG
	assert(jointType != CJointAttribute::nullJoint);
#endif
	//Check joint type.
	if(jointType == CJointAttribute::classicBallJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicBallJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::classicCorkscrewJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicCorkscrewJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::classicHingeJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicHingeJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::classicSliderJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicSliderJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::classicUniversalJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicUniversalJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::classicUpVectorJoint)
	{
		//Create proxy.
		proxy = new CD3DXClassicUpVectorJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::custom6DOFJoint)
	{
		//Create proxy.
		proxy = new CD3DXCustom6DOFJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::customBallJoint)
	{
		//Create proxy.
		proxy = new CD3DXCustomBallJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::customHingeJoint)
	{
		//Create proxy.
		proxy = new CD3DXCustomHingeJointObjectProxy(this);
	}
	else if(jointType == CJointAttribute::customSliderJoint)
	{
		//Create proxy.
		proxy = new CD3DXCustomSliderJointObjectProxy(this);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif

#ifdef _DEBUG
	assert(proxy != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXJointObject
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXJointObject::~CD3DXJointObject(void)
{
	//Check result.
	if(proxy != _NULL)
	{
		//Delete proxy.
		delete (CD3DXJointObjectProxy *)proxy;
		//Clear proxy.
		proxy = (CD3DXJointObjectProxy *)_NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// ClearTexture
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXJointObject::clearTexture(const CNormalString& name)
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
			//Clear texture.
			renderableObject->clearTexture(name);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// Pick
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CD3DXJointObject::pick(CPickRay& pickRay,CPickResult& result)
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
#ifdef _DEBUG
			assert(renderableObject != _NULL);
#endif
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

void CD3DXJointObject::createObjects(CResourceManager* resourceManager)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Set flag.
	initialized = _TRUE;

#ifndef _DEBUG
	//Initialize objects.
	initializeObjects(resourceManager);
#else
	//Initialize objects.
	assert(SUCCEEDED(initializeObjects(resourceManager)));
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXJointObject::initializeObjects(CResourceManager* resourceManager)
{
#ifdef _DEBUG
	assert(proxy != _NULL);
	assert(resourceManager != _NULL);
#endif
	//Return result.
	return PROXY_INSTANCE(proxy)->initializeObjects(resourceManager);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetViewPort
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXJointObject::setViewPort(CViewPort* viewPort)
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

HRESULT CD3DXJointObject::dispatchMessage(const D3DXEvent& d3dxEvent)
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

HRESULT CD3DXJointObject::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	case d3dxOnFrameMove:
#ifdef _DEBUG
		assert(proxy != _NULL);
#endif
		//Setup objects.
		PROXY_INSTANCE(proxy)->setupObjects();
		break;
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
			V_RETURN(initializeObjects(((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager()));
		}
		//
		///////////////////////////////////////
		break;
	}
	//Dispatch message to all its children.
	//You can controll children's action from settings.
	V_RETURN(dispatchMessage(d3dxEvent));
	//Return result.
	return CD3DXRenderableObject::handleMessage(d3dxEvent);
}
