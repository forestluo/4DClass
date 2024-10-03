///////////////////////////////////////////////////////////////////////////////
//
// D3DXPrimitiveObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXPrimitiveObject.h"

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
const C4DBase CD3DXPrimitiveObject::base(L"CD3DXPrimitiveObject",L"CD3DXRenderableObject");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXPrimitiveObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXPrimitiveObject::CD3DXPrimitiveObject(void)
{
	//Set default value.
	renderable = (CD3DXRenderable *)_NULL;

	//Set this.
	setThis(this);
	//Set type.
	CWorldObject::setObjectType(CWorldObject::primitiveObject);
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXPrimitiveObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXPrimitiveObject::~CD3DXPrimitiveObject(void)
{
	//Check renderable.
	if(renderable != _NULL)
	{
		//Release reference.
		renderable->releaseReference();
		//Clear reference.
		renderable = (CD3DXRenderable *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearTexture
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXPrimitiveObject::clearTexture(const CNormalString& name)
{
	//Clear texture.
	CChartletAttribute::clearTexture(name);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetRenderable
//
///////////////////////////////////////////////////////////////////////////////

CD3DXRenderable* CD3DXPrimitiveObject::getRenderable() const
{
#ifdef _DEBUG
	assert(renderable != _NULL);
#endif
	//Return result.
	return renderable;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetRenderable
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXPrimitiveObject::setRenderable(CD3DXRenderable* renderable)
{
#ifdef _DEBUG
	assert(renderable != _NULL);
	assert(!renderable->isBasicResource());
#endif
	//Set renderable.
	this->renderable = renderable;

	///////////////////////////////////////
	//
	//Set the box, when renderable only.
	if(isRenderableObject() && !isPhysicsObject()) CWorldObject::copyBox(*renderable);
	//
	///////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////////////
//
// GetModelName
//
///////////////////////////////////////////////////////////////////////////////

const CNormalString& CD3DXPrimitiveObject::getModelName() const
{
	//Return result.
	return modelName;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SelectRenderable
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXPrimitiveObject::selectRenderable(CResourceManager* resourceManager,const CNormalString& name)
{
#ifdef _DEBUG
	assert(name.length() > 0);
	assert(resourceManager != _NULL);
#endif
	
	///////////////////////////////////////
	//
	// Clear previous renderable.
	//
	//Check renderable.
	if(renderable != _NULL)
	{
		//Release reference.
		renderable->releaseReference();
		//Clear renderable.
		renderable = (CD3DXRenderable *)_NULL;
	}
	//
	///////////////////////////////////////

	//Set name.
	modelName = name;
	///////////////////////////////////////
	//
	// Select renderable from resources.
	//
	//Get resource.
	CD3DXResource* resource = resourceManager->getResource(name);
#ifdef _DEBUG
	assert(resource != NULL);
	assert(IS_RENDERABLE_BASE(resource));
#endif
	//Add reference.
	resource->addReference();
	//Set renderable mesh.
	renderable = (CD3DXRenderable *)resource;
	//
	///////////////////////////////////////

	///////////////////////////////////////
	//
	//Set the box, when renderable only.
	if(isRenderableObject() && !isPhysicsObject()) CWorldObject::copyBox(*renderable);
	//
	///////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////////////
//
// Pick
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CD3DXPrimitiveObject::pick(CPickRay& pickRay,CPickResult& result)
{
	//Matrix.
	C4DMatrix4 worldMatrix;

#ifdef _DEBUG
	assert(renderable != _NULL);
#endif

	//Initialize matrix.
	initializeMatrix(worldMatrix);
	//Set world matrix.
	pickRay.setWorldMatrix(worldMatrix);

	///////////////////////////////////////
	//
	// Get result.
	//
	//Return result.
	CPickIntersection* pIntersection = renderable->pick(pickRay);
	//Check result.
	if(pIntersection != NULL)
	{
		//Set alias.
		pIntersection->setAlias(getAlias());
		//Add into tail.
		result.addIntersection(pIntersection);
	}
	//
	///////////////////////////////////////
	//Return result.
	return pIntersection != _NULL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetViewPort
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXPrimitiveObject::setViewPort(CViewPort* viewPort)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(viewPort != _NULL && renderable != _NULL);
#endif

	//Get effect.
	CD3DXEffect* effect = CEffectAttribute::getEffect();
	//Check result.
	if(effect == _NULL)
	{
		//Use default effect.
		renderable->setViewPort(viewPort);
	}
	else
	{
		//Get frame timestamp.
		_INTEGER frameStamp = viewPort->getFrameStamp();
		//View matrix.
		C4DMatrix4 viewMatrix = viewPort->getViewMatrix();
		//Projection matrix.
		C4DMatrix4 projectionMatrix = viewPort->getProjectionMatrix();
		//Return result.
		V_RETURN(effect->setViewProjectionMatrix(viewMatrix,projectionMatrix,frameStamp));
	}
	//Return result.
	return CD3DXRenderableObject::setViewPort(viewPort);
}

///////////////////////////////////////////////////////////////////////////////
//
// Render
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXPrimitiveObject::render(IDirect3DDevice9* pd3dDevice)
{
	//Result.
	HRESULT hr = S_OK;
	//Matrix.
	C4DMatrix4 worldMatrix;

#ifdef _DEBUG
	assert(pd3dDevice != _NULL && renderable != _NULL);
#endif

	//Initialize matrix.
	initializeMatrix(worldMatrix);

	//Get effect.
	CD3DXEffect* effect = CEffectAttribute::getEffect();
	//Check result.
	if(effect == NULL)
	{
		//Set color.
		if(FAILED(renderable->setColor(getColor()))) hr = E_FAIL;
		//Set light color.
		if(FAILED(renderable->setLightColor(getLightColor()))) hr = E_FAIL;
		//Set world matrix.
		if(FAILED(renderable->setWorldMatrix(worldMatrix))) hr = E_FAIL;
		//Set scene map.
		if(FAILED(renderable->setSceneMap(getSceneMap()))) hr = E_FAIL;
		//Render.
		if(FAILED(renderable->render(pd3dDevice))) hr = E_FAIL;
	}
	else
	{
		//Set color.
		if(FAILED(effect->setColor(getColor()))) hr = E_FAIL;
		//Set light color.
		if(FAILED(effect->setLightColor(getLightColor()))) hr = E_FAIL;
		//Set world matrix.
		if(FAILED(effect->setWorldMatrix(worldMatrix))) hr = E_FAIL;
		//Set scene map.
		if(FAILED(effect->setSceneMap(getSceneMap()))) hr = E_FAIL;
		//Render.
		if(FAILED(renderable->render(pd3dDevice,effect))) hr = E_FAIL;
	}
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXPrimitiveObject::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	//Do not dispatch any message to its effect or property.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Handle message.
		CEffectAttribute::handleMessage(d3dxEvent);
		//Handle message.
		CChartletAttribute::handleMessage(d3dxEvent);
		///////////////////////////////////////
		//
		//Check renderable.
		if(renderable != _NULL)
		{
			//Check renderable.
			if(renderable->isBasicResource())
			{
				//Release reference.
				renderable->releaseReference();
				//Clear effect.
				renderable = (CD3DXRenderable *)_NULL;
			}
		}
		//
		///////////////////////////////////////
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
		assert(d3dxEvent.pUserContext != NULL);
#endif
		///////////////////////////////////////
		//
		//Check renderable.
		if(renderable == _NULL)
		{
			//Handle message.
			CEffectAttribute::handleMessage(d3dxEvent);
			//Handle message.
			CChartletAttribute::handleMessage(d3dxEvent);
			//Select renderable.
			selectRenderable(((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager(),modelName);
		}
		//
		///////////////////////////////////////
		break;
	}
	//Return result.
	return CD3DXRenderableObject::handleMessage(d3dxEvent);
}
