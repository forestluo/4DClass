///////////////////////////////////////////////////////////////////////////////
//
// EffectAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _EFFECT_ATTRIBUTE_H_
#define _EFFECT_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXEffect.h"
#include "ResourceManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// EffectAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CEffectAttribute : public CD3DXObject
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
	CEffectAttribute(void);
	virtual ~CEffectAttribute(void);

public:

	/**
	 * Clear effect.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Clear effect.</p>
	 */
	void clearEffect();

	/**
	 * Get effect.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Effect.</p>
	 */
	CD3DXEffect* getEffect() const;

public:

	/**
	 * Get effect name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Effect name.</p>
	 */
	const CNormalString& getEffectName() const;
	/**
	 * Select effect.
	 *
	 * @param resourceManager Resource manager.
	 * @param name Name of effect.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void selectEffect(CResourceManager* resourceManager,const CNormalString& name);

public:

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent Event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_EFFECT_ATTRIBUTE_H_