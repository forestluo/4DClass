///////////////////////////////////////////////////////////////////////////////
//
// D3DXEffectAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXEffectAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXEffectAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXEffectAttribute::CD3DXEffectAttribute(void)
{
	effect = (CD3DXEffect *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXEffectAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXEffectAttribute::~CD3DXEffectAttribute(void)
{
	//Check effect.
	if(effect != _NULL)
	{
		//Release reference.
		effect->releaseReference();
		//Clear reference.
		effect = (CD3DXEffect *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetParameterHandle
//
///////////////////////////////////////////////////////////////////////////////

const D3DXHANDLE CD3DXEffectAttribute::getParameterHandle(_INTEGER type)
{
#ifdef _DEBUG
	assert(effect != _NULL);
#endif
	//Return result.
	return effect->getParameterHandle(type);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetEffect
//
///////////////////////////////////////////////////////////////////////////////

CD3DXEffect* CD3DXEffectAttribute::getEffect() const
{
#ifdef _DEBUG
	assert(effect != _NULL);
#endif
	//Return result.
	return effect;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetEffectName
//
///////////////////////////////////////////////////////////////////////////////

const CNormalString& CD3DXEffectAttribute::getEffectName() const
{
	//Return result.
	return effectName;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetColor
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffectAttribute::setColor(const D3DCOLOR& color)
{
#ifdef _DEBUG
	assert(effect != _NULL);
#endif
	//Return result.
	return effect->setColor(color);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetLightColor
//
///////////////////////////////////////////////////////////////////////////////

HRESULT	CD3DXEffectAttribute::setLightColor(const D3DXVECTOR4& lightColor)
{
#ifdef _DEBUG
	assert(effect != _NULL);
#endif
	//Return result.
	return effect->setLightColor(lightColor);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetWorldMatrix
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffectAttribute::setWorldMatrix(const C4DMatrix4& worldMatrix)
{
#ifdef _DEBUG
	assert(effect != NULL);
#endif
	//Return result.
	return effect->setWorldMatrix(worldMatrix);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetSceneMap
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffectAttribute::setSceneMap(const CD3DXTexture* sceneMap)
{
#ifdef _DEBUG
	assert(effect != NULL);
#endif
	//Return result.
	return effect->setSceneMap(sceneMap);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetViewPort
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffectAttribute::setViewPort(CViewPort* viewPort)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(viewPort != _NULL);
#endif

	//Get frame timestamp.
	_INTEGER frameStamp = viewPort->getFrameStamp();
	//View matrix.
	C4DMatrix4 viewMatrix = viewPort->getViewMatrix();
	//Projection matrix.
	C4DMatrix4 projectionMatrix = viewPort->getProjectionMatrix();

#ifdef _DEBUG
	assert(effect != _NULL);
#endif
	//Return result.
	V_RETURN(effect->setViewProjectionMatrix(viewMatrix,projectionMatrix,frameStamp));
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// SelectEffect
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXEffectAttribute::selectEffect(CResourceManager* resourceManager,const CNormalString& effectName)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
	assert(effectName.length() > 0);
#endif
	
	///////////////////////////////////////
	//
	// Clear previous effect.
	//
	//Check effect.
	if(effect != _NULL)
	{
		//Release reference.
		effect->releaseReference();
		//Clear effect.
		effect = (CD3DXEffect *)_NULL;
	}
	//
	///////////////////////////////////////

	//Set name.
	this->effectName = effectName;
	///////////////////////////////////////
	//
	// Select effect from resources.
	//
	//Get resouce.
	CD3DXResource* pResource = resourceManager->getResource(effectName);
#ifdef _DEBUG
	assert(pResource != _NULL);
	assert(IS_RESOURCE_BASE(pResource));
#endif
	//Add reference.
	pResource->addReference();
	//Set effect mesh.
	effect = (CD3DXEffect *)pResource;
	//
	///////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffectAttribute::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	//Do not dispatch any message to its effect or proerty.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		///////////////////////////////////////
		//
		//Check effect.
		if(effect != _NULL)
		{
			//Release reference.
			effect->releaseReference();
			//Clear effect.
			effect = (CD3DXEffect *)_NULL;
		}
		//
		///////////////////////////////////////
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Check user context.
		if(d3dxEvent.pUserContext != NULL)
		{
			///////////////////////////////////////
			//
			//Check effect.
			if(effect == _NULL)
			{
				//Check effect name and adjust it.
				if(effectName.length() <= 0) effectName = EFFECT_REFLECT;
				//Select effect.
				selectEffect(((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager(),effectName);
			}
			//
			///////////////////////////////////////
		}
		break;
	}
	//Return result.
	return FALSE;
}
