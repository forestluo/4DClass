///////////////////////////////////////////////////////////////////////////////
//
// RenderableManager.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _RENDERABLE_MANAGER_H_
#define _RENDERABLE_MANAGER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXPrimitive.h"
#include "D3DXDeviceReference.h"

///////////////////////////////////////////////////////////////////////////////
//
// RenderableManager
//
///////////////////////////////////////////////////////////////////////////////

class CRenderableManager : public CD3DXDeviceReference
{
private:
	/**
	 * Renderables.
	 */
	_OBJECT renderables;

public:
	CRenderableManager(void);
	virtual ~CRenderableManager(void);

protected:

	/**
	 * Release all.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void releaseAll();

	/**
	 * Clear renderables.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearRenderables();

public:

	/**
	 * Create primitive.
	 *
	 * <p>The data of primitive is not the standard one.</p>
	 *
	 * @param attribute Primitive attribute.
	 * @return
	 *     <p>Created primitive.</p>
	 */
	CD3DXPrimitive* createPrimitive(const CPrimitiveAttribute& attribute);

protected:

	/**
	 * Dispatch message.
	 *
	 * @param d3dxEvent D3DX event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT dispatchMessage(const D3DXEvent& d3dxEvent);

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
#endif //_RENDERABLE_MANAGER_H_
