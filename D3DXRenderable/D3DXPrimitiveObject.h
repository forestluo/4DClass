///////////////////////////////////////////////////////////////////////////////
//
// D3DXPrimitiveObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_PRIMITIVE_OBJECT_H_
#define _D3DX_PRIMITIVE_OBJECT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXRenderable.h"

#include "ColorAttribute.h"
#include "EffectAttribute.h"
#include "ChartletAttribute.h"
#include "D3DXRenderableObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXPrimitiveObject
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXPrimitiveObject :
	public CColorAttribute,
	public CEffectAttribute,
	public CChartletAttribute,
	public CD3DXRenderableObject
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
	 * Name of renderable.
	 */
	CNormalString modelName;
	/**
	 * Renderable.
	 */
	CD3DXRenderable* renderable;

public:
	CD3DXPrimitiveObject(void);
	virtual ~CD3DXPrimitiveObject(void);

public:

	/**
	 * Clear texture.
	 *
	 * @param name Name of texture.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void clearTexture(const CNormalString& name);

public:

	/**
	 * Get renderable.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Renderable.</p>
	 */
	CD3DXRenderable* getRenderable() const;
	/**
	 * Set renderable.
	 *
	 * <p>Only accept the none-basic ones.</p>
	 *
	 * @param renderable Renderable of object.
	 * @return
	 *     <p>No results returned.</p.
	 */
	void setRenderable(CD3DXRenderable* renderable);

public:

	/**
	 * Get model name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Model name.</p>
	 */
	const CNormalString& getModelName() const;
	/**
	 * Select renderable.
	 *
	 * @param resourceManager Resource manager.
	 * @param name Name of renderable.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void selectRenderable(CResourceManager* resourceManager,const CNormalString& name);

public:

	/**
	 * Pick
	 *
	 * @param pickRay Pick ray.
	 * @param result Pick result.
	 * @return
	 *     <p>Return true, if it is picked.</p>
	 */
	virtual _BOOL pick(CPickRay& pickRay,CPickResult& result);

public:

	/**
	 * Set view port.
	 *
	 * @param viewPort View port.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT setViewPort(CViewPort* viewPort);

protected:

	/**
	 * Render.
	 *
	 * @param pd3dDevice Device.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT render(IDirect3DDevice9* pd3dDevice);

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
#endif //_D3DX_PRIMITIVE_OBJECT_H_