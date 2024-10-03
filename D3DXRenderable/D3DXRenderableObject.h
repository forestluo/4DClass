///////////////////////////////////////////////////////////////////////////////
//
// D3DXRenderableObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_RENDERABLE_OBJECT_H_
#define _D3DX_RENDERABLE_OBJECT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PickerAttribute.h"
#include "SketcherAttribute.h"
#include "ControllerAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXRenderableObject
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXRenderableObject :
	public CD3DXObject,
	public CPickerAttribute,
	public CSketcherAttribute,
	public CControllerAttribute
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

public:
	CD3DXRenderableObject(void);
	virtual ~CD3DXRenderableObject(void);

public:

	/**
	 * Clear texture.
	 *
	 * @param name Name of texture.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void clearTexture(const CNormalString& name) = 0;

public:

	/**
	 * Set picked.
	 *
	 * @param picked Picked status.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setPicked(_BOOL picked);

public:

	/**
	 * Set view port before rendering.
	 *
	 * @param viewPort View port.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT setViewPort(CViewPort* viewPort);

protected:

	/**
	 * Render
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

#define IS_RENDERABLEOBJECT_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXRenderableObject::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_RENDERABLE_OBJECT_H_