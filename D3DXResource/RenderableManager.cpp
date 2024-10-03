///////////////////////////////////////////////////////////////////////////////
//
// RenderableManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ListNodeContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define RENDERABLES_INSTANCE(p)								((CListNodeContainer *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CRenderableManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CRenderableManager::CRenderableManager(void)
{
	//Create renderables.
	renderables = new CListNodeContainer();
#ifdef _DEBUG
	assert(renderables != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CRenderableManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CRenderableManager::~CRenderableManager(void)
{
	//Release all.
	releaseAll();
	//Check renderables.
	if(renderables != _NULL)
	{
		//Delete renderables.
		delete (CListNodeContainer *)renderables;
		//Clear renderables.
		renderables = (CListNodeContainer *)_NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// ReleaseAll
//
/////////////////////////////////////////////////////////////////////////////////

void CRenderableManager::releaseAll()
{
#ifdef _DEBUG
	assert(renderables != _NULL);
#endif

	//Get count.
	while(RENDERABLES_INSTANCE(renderables)->getCount() > 0)
	{
		//Remove head.
		_OBJECT object = RENDERABLES_INSTANCE(renderables)->removeHead();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Delete instance.
		delete (CD3DXRenderable *)object;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// ClearRenderables
//
/////////////////////////////////////////////////////////////////////////////////

void CRenderableManager::clearRenderables()
{
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(renderables != _NULL);
#endif

	//Get enumeration.
	RENDERABLES_INSTANCE(renderables)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get renderable.
		CD3DXRenderable* renderable = (CD3DXRenderable *)iterator.nextElement();
#ifdef _DEBUG
		assert(renderable != _NULL);
#endif
		//Check renderable.
		if(renderable->countReference() <= 0)
		{
			//Remove it from list.
			RENDERABLES_INSTANCE(renderables)->removeValue(renderable);
			//Delete renderable.
			delete (CD3DXRenderable *)renderable;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// DispatchMessage
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CRenderableManager::dispatchMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr = FALSE;
	//Enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(renderables != _NULL);
#endif

	//Get enumeration.
	RENDERABLES_INSTANCE(renderables)->getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get renderable.
		CD3DXRenderable* renderable = (CD3DXRenderable *)iterator.nextElement();
#ifdef _DEBUG
		assert(renderable != _NULL);
#endif
		//Handle message.
		if(FAILED(renderable->handleMessage(d3dxEvent))) hr = E_FAIL;
	}
	//Return result.
	return hr;
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreatePrimitive
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXPrimitive* CRenderableManager::createPrimitive(const CPrimitiveAttribute& attribute)
{
	//Event.
	D3DXEvent d3dxEvent;

#ifdef _DEBUG
	assert(attribute.getType() != CPrimitiveAttribute::nullPrimitive);
#endif
	//Creeate primitive.
	CD3DXPrimitive* primitive = new CD3DXPrimitive(attribute);
#ifdef _DEBUG
	assert(primitive != _NULL);
#endif
	///////////////////////////////////////
	//
	//Create it with device.
	//
	//Clear event.
	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9CreateDevice;
	d3dxEvent.d3dxCreateDevice9.pd3dDevice = getDevice();
	//Handle message.
	if(FAILED(primitive->handleMessage(d3dxEvent)))
	{
		//Delete primitive.
		delete primitive;
		//Return null.
		return (CD3DXPrimitive *)_NULL;
	}
	//
	///////////////////////////////////////
	//
	//Reset it with device.
	//
	//Clear event.
	ZeroMemory(&d3dxEvent,sizeof(D3DXEvent));
	//Set values.
	d3dxEvent.d3dxEventID = d3dxOnD3D9ResetDevice;
	d3dxEvent.d3dxResetDevice9.pd3dDevice = getDevice();
	//Handle message.
	if(FAILED(primitive->handleMessage(d3dxEvent)))
	{
		//Delete primitive.
		delete primitive;
		//Return null.
		return (CD3DXPrimitive *)_NULL;
	}
	//
	///////////////////////////////////////
	//Add reference.
	primitive->addReference();
#ifdef _DEBUG
	assert(renderables != _NULL);
#endif
	//Add it into list.
	RENDERABLES_INSTANCE(renderables)->addTail(primitive);
	//Return result.
	return primitive;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CRenderableManager::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//On frame move.
	case d3dxOnFrameMove:
		//Clear renderables.
		clearRenderables();
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Dispatch message.
		V_RETURN(dispatchMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != NULL);
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
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
	return CD3DXDeviceReference::handleMessage(d3dxEvent);
}
