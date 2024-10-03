///////////////////////////////////////////////////////////////////////////////
//
// D3DXEffectAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_EFFECT_ATTRIBUTE_H_
#define _D3DX_EFFECT_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ViewPort.h"
#include "D3DXEffect.h"
#include "ResourceManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Renderable
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXEffectAttribute
{
private:
	/**
	 * Effect.
	 */
	CD3DXEffect* effect;
	/**
	 * Name of effect.
	 */
	CNormalString effectName;

public:
	CD3DXEffectAttribute(void);
	virtual ~CD3DXEffectAttribute(void);

protected:

	/**
	 * Get parameter handle.
	 *
	 * @param semType Semantic type.
	 * @return
	 *     <p>Parameter handle.</p>
	 */
	const D3DXHANDLE getParameterHandle(_INTEGER semType);

public:

	/**
	 * Get effect.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Effect.</p>
	 */
	CD3DXEffect* getEffect() const;
	/**
	 * Get effect name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Effect name.</p>
	 */
	const CNormalString& getEffectName() const;

public:

	/**
	 * Set color.
	 *
	 * @param color Color.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT setColor(const D3DCOLOR& color);
	/**
	 * Set light color.
	 *
	 * @param lightColor Light color.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT	setLightColor(const D3DXVECTOR4& lightColor);
	/**
	 * Set world matrix.
	 *
	 * @param worldMatrix World matrix.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT setWorldMatrix(const C4DMatrix4& worldMatrix);

public:

	/**
	 * Set scene map.
	 *
	 * @param sceneMap Scene map.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT setSceneMap(const CD3DXTexture* sceneMap);

public:

	/**
	 * Set view port.
	 *
	 * @param viewPort View port.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT setViewPort(CViewPort* viewPort);

	/**
	 * Select effect from resources.
	 *
	 * @param resourceManager Resource manager.
	 * @param wsEffectName Name of effect.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void selectEffect(CResourceManager* resourceManager,const CNormalString& effectName);

public:

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent D3DX event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_EFFECT_ATTRIBUTE_H_
