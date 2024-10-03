///////////////////////////////////////////////////////////////////////////////
//
// D3DXRenderableObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXRenderableObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
/////////////////////////////////////////////////////////////////////////////////

#include "D3DXJointObject.h"
#include "D3DXCompoundObject.h"
#include "D3DXPrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXRenderableObject::base(L"CD3DXRenderableObject",L"CD3DXObject");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXRenderableObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXRenderableObject::CD3DXRenderableObject(void)
{
	//Set this.
	setThis(this);
	//Set renderable.
	CWorldObject::setRenderable(this);
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXRenderableObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXRenderableObject::~CD3DXRenderableObject(void)
{
	//Enumeration.
	CListNodeEnumeration iterator;
	//Get numeration.
	getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get world object.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Get this object.
		_OBJECT thisObject = object->getThis();
#ifdef _DEBUG
		assert(thisObject != _NULL);
#endif
		//Check result.
		if(object->isRenderableObject()
			&& !object->isPhysicsObject())
		{
			//Remove it from list.
			CWorldObject::removeObject(object);

			//Check type.
			if(object->isJointObject())
			{
				//Delete object.
				delete (CD3DXJointObject *)thisObject;
			}
			else if(object->isCompoundObject())
			{
				//Delete object.
				delete (CD3DXCompoundObject *)thisObject;
			}
			else if(object->isPrimitiveObject())
			{
				//Delete object.
				delete (CD3DXPrimitiveObject *)thisObject;
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif
		}
#ifdef _DEBUG
		//Check result.
		else if(object->isRenderableObject() && object->isPhysicsObject()) assert(_FALSE);
#endif
	}
}


/////////////////////////////////////////////////////////////////////////////////
//
// Pick
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXRenderableObject::setPicked(_BOOL picked)
{
	//Set picked.
	CControllerAttribute::setPicked(picked);
	//Check picked.
	if(!picked)
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
				//Clear picked flag of all children.
				((CD3DXRenderableObject *)object->getRenderable())->setPicked(picked);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetViewPort
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXRenderableObject::setViewPort(CViewPort* viewPort)
{
	//Result.
	HRESULT hr = S_OK;

	//Set view port.
	if(FAILED(CSketcherAttribute::setViewPort(viewPort))) hr = E_FAIL;
	//Set view port.
	if(FAILED(CControllerAttribute::setViewPort(viewPort))) hr = E_FAIL;
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// Render
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXRenderableObject::render(IDirect3DDevice9* pd3dDevice)
{
#ifdef _DEBUG
	assert(pd3dDevice != _NULL);
#endif
	//Return result.
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXRenderableObject::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr = S_OK;

	//Handle message.
	V_RETURN(CSketcherAttribute::handleMessage(d3dxEvent));
	//Handle message.
	V_RETURN(CControllerAttribute::handleMessage(d3dxEvent));
	//Do not dispatch any message to its effect or proerty.
	switch(d3dxEvent.d3dxEventID)
	{
	//Render the scene using the D3D9 device.
	case d3dxOnD3D9FrameRender:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxFrameRender9.pd3dDevice != NULL);
#endif
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
