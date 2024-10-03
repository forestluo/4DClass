///////////////////////////////////////////////////////////////////////////////
//
// D3DXRenderable.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_RENDERABLE_H_
#define _D3DX_RENDERABLE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "BoxAttribute.h"

#include "D3DXPickAttribute.h"
#include "D3DXEffectAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Renderable
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXRenderable :
	public CD3DXResource,
	public CBoxAttribute,
	public CD3DXPickAttribute,
	public CD3DXEffectAttribute
{
private:
	//Base description.
	static const C4DBase base;

public:

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	static _LONG getClassCode() {return base.classCode();}

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	virtual _LONG classCode() const {return base.classCode();}

private:

	/**
	 * Basic resource.
	 *
	 * <p>The basic resource is created or loaded when system start.
	 * It is the minmum resource that system needed.
	 * Otherwise, it is created when system is running.</p>
	 */
	_BOOL basicResource;

public:
	CD3DXRenderable(void);
	virtual ~CD3DXRenderable(void);

public:

	/**
	 * Whether is basic resource.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is a basic resource.</p>
	 */
	_BOOL isBasicResource() const;
	/**
	 * Set basic resource.
	 *
	 * @param basicResource Whether is a basic resource.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setBasicResource(_BOOL basicResource);

public:

	/**
	 * Render.
	 *
	 * @param pd3dDevice D3DX device.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT render(IDirect3DDevice9* pd3dDevice);

	/**
	 * Render.
	 *
	 * @param pd3dDevice D3DX device.
	 * @param effect Effect.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT render(IDirect3DDevice9* pd3dDevice,CD3DXEffect* effect) = 0;

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

#define IS_RENDERABLE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXRenderable::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_RENDERABLE_H_
