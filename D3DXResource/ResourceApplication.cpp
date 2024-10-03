///////////////////////////////////////////////////////////////////////////////
//
// ResourceApplication.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// CResourceApplication
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CResourceApplication::CResourceApplication(void)
{
	//Create resource manager.
	resourceManager = new CResourceManager();
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Create renderable manager.
	renderableManager = new CRenderableManager();
#ifdef _DEBUG
	assert(renderableManager != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CResourceApplication
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CResourceApplication::~CResourceApplication(void)
{
	//Check renderable manager.
	if(renderableManager != _NULL)
	{
		//Delete resource manager.
		delete (CRenderableManager *)renderableManager;
		//Clear renderable manager.
		renderableManager = (CRenderableManager *)_NULL;
	}
	//Check resource manager.
	if(resourceManager != _NULL)
	{
		//Delete resource manager.
		delete (CResourceManager *)resourceManager;
		//Clear resource manager.
		resourceManager = (CResourceManager *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetResourceManager
//
///////////////////////////////////////////////////////////////////////////////

CResourceManager* CResourceApplication::getResourceManager() const
{
	//Return result.
	return resourceManager;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetRenderableManager
//
///////////////////////////////////////////////////////////////////////////////

CRenderableManager* CResourceApplication::getRenderableManager() const
{
	//Return result.
	return renderableManager;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetResource
//
///////////////////////////////////////////////////////////////////////////////

CD3DXResource* CResourceApplication::getResource(const CNormalString& name)
{
	//Resource.
	CD3DXResource* resource = (CD3DXResource *)_NULL;
	//Open lock.
	openLock();
	{
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Get primitive.
		if(resourceManager != _NULL) resource = resourceManager->getResource(name);
	}
	//Close lock.
	closeLock();
	//Return result.
	return resource;
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveResource
//
///////////////////////////////////////////////////////////////////////////////

CD3DXResource* CResourceApplication::removeResource(const CNormalString& name)
{
	//Resource.
	CD3DXResource* resource = (CD3DXResource *)_NULL;
	//Open lock.
	openLock();
	{
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Get primitive.
		if(resourceManager != _NULL) resource = resourceManager->removeResource(name);
	}
	//Close lock.
	closeLock();
	//Return result.
	return resource;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CResourceApplication::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(resourceManager != _NULL);
	assert(renderableManager != _NULL);
#endif

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Handle updates to the scene.
	case d3dxOnFrameMove:
		//Handle message.
		V_RETURN(resourceManager->handleMessage(d3dxEvent));
		//Handle message.
		V_RETURN(renderableManager->handleMessage(d3dxEvent));
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Handle message.
		V_RETURN(renderableManager->handleMessage(d3dxEvent));
		//Handle message.
		V_RETURN(resourceManager->handleMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		V_RETURN(resourceManager->handleMessage(d3dxEvent));
		//Handle message.
		V_RETURN(renderableManager->handleMessage(d3dxEvent));
		//break;
		break;
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Handle message.
		V_RETURN(renderableManager->handleMessage(d3dxEvent));
		//Handle message.
		V_RETURN(resourceManager->handleMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		V_RETURN(resourceManager->handleMessage(d3dxEvent));
		//Handle message.
		V_RETURN(renderableManager->handleMessage(d3dxEvent));
		//break.
		break;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
