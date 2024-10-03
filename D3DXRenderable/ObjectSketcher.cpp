///////////////////////////////////////////////////////////////////////////////
//
// ObjectSketcher.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ObjectSketcher.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "D3DXResource.h"

#include "Sketch0.h"
#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define SKETCH0_INSTANCE(p)									((CSketch0 *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CObjectSketcher::base(L"CObjectSketcher",L"CD3DXObject");

///////////////////////////////////////////////////////////////////////////////
//
// CObjectSketcher
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CObjectSketcher::CObjectSketcher(void)
{
	//Set default value.
	drawBox = _FALSE;
	drawAxis = _FALSE;
	drawSphere = _FALSE;
	intersected = _FALSE;

	//Set default value.
	sketch = (CSketch0 *)_NULL;
	owner = (CPhysicsObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CObjectSketcher
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CObjectSketcher::~CObjectSketcher(void)
{
	//Check result.
	if(sketch != _NULL)
	{
		//Release reference.
		SKETCH0_INSTANCE(sketch)->releaseReference();
		//Clear reference.
		sketch = (CSketch0 *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetOwner
//
///////////////////////////////////////////////////////////////////////////////

CWorldObject* CObjectSketcher::getOwner() const
{
	//Return result.
	return owner;
}

///////////////////////////////////////////////////////////////////////////////
//
// DetachObject
//
///////////////////////////////////////////////////////////////////////////////

void CObjectSketcher::detachObject()
{
	//Clear object.
	owner = (CWorldObject *)_NULL;
	//Detach sketch0.
	if(sketch != _NULL) detachSketch();
}

///////////////////////////////////////////////////////////////////////////////
//
// AttachObject
//
///////////////////////////////////////////////////////////////////////////////

void CObjectSketcher::attachObject(CWorldObject* owner)
{
#ifdef _DEBUG
	assert(owner != _NULL);
#endif
	//Set owner.
	this->owner = owner;
}

///////////////////////////////////////////////////////////////////////////////
//
// DetachSketch
//
///////////////////////////////////////////////////////////////////////////////

void CObjectSketcher::detachSketch()
{
#ifdef _DEBUG
	assert(sketch != _NULL);
#endif
	//Release reference.
	SKETCH0_INSTANCE(sketch)->releaseReference();
	//Clear reference.
	sketch = (CSketch0 *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// AttachSketch
//
///////////////////////////////////////////////////////////////////////////////

void CObjectSketcher::attachSketch(CResourceManager* resourceManager)
{
#ifdef _DEBUG
	assert(sketch == _NULL);
	assert(resourceManager != _NULL);
#endif

	///////////////////////////////////////
	//
	//Get sketch.
	CD3DXResource* resource = resourceManager->getResource(LINESTRIP_SKETCH0);
#ifdef _DEBUG
	assert(resource != _NULL);
	assert(resource->classCode() == CSketch0::getClassCode());
#endif
	//Add reference.
	resource->addReference();
	//Set sketch.
	sketch = (CSketch0 *)resource;
	//
	///////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetWorldBox
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CObjectSketcher::getWorldBox(CSimpleBox& box)
{
#ifdef _DEBUG
	assert(owner != _NULL);
#endif
	//Return result.
	return owner->getWorldBox(box);
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetWorldSphere
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CObjectSketcher::getWorldSphere(CSimpleSphere& sphere)
{
#ifdef _DEBUG
	assert(owner != _NULL);
#endif
	//Return result.
	return owner->getWorldSphere(sphere);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetViewPort
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CObjectSketcher::setViewPort(CViewPort* viewPort)
{
#ifdef _DEBUG
	assert(viewPort != _NULL && sketch != _NULL);
#endif
	//Return result.
	return SKETCH0_INSTANCE(sketch)->setViewPort(viewPort);
}

///////////////////////////////////////////////////////////////////////////////
//
// Render
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CObjectSketcher::render(IDirect3DDevice9* pd3dDevice)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(pd3dDevice != _NULL);
#endif

	//Matrix.
	C4DMatrix4 worldMatrix;

#ifdef _DEBUG
	assert(owner != _NULL);
#endif
	//Initialize matrix.
	owner->initializeMatrix(worldMatrix);

#ifdef _DEBUG
	assert(sketch != _NULL);
#endif
	//Set world matrix.
	V_RETURN(SKETCH0_INSTANCE(sketch)->setWorldMatrix(worldMatrix));

	//Attach sketcher.
	SKETCH0_INSTANCE(sketch)->attachSketcher(this);
	//Render it.
	V_RETURN(SKETCH0_INSTANCE(sketch)->CD3DXRenderable::render(pd3dDevice));
	//Dettach from it.
	SKETCH0_INSTANCE(sketch)->detachSketcher();
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CObjectSketcher::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	//Do not dispatch any message to its effect or proerty.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Detach.
		if(sketch != NULL) detachSketch();
		break;
	//Handle updates to the scene.
	case d3dxOnFrameMove:
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != NULL);
#endif
		//Attach sketch.
		if(sketch == NULL)
		{
			//Attach sketch.
			attachSketch(((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager());
		}
		break;
	//Render the scene using the D3D9 device.
	case d3dxOnD3D9FrameRender:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxFrameRender9.pd3dDevice != NULL);
#endif
		//Attach sketch.
		if(sketch == NULL)
		{
			//Attach sketch.
			attachSketch(((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager());
		}
		///////////////////////////////////////
		//
		//Render object.
		V_RETURN(render(d3dxEvent.d3dxFrameRender9.pd3dDevice));
		//
		///////////////////////////////////////
		break;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
