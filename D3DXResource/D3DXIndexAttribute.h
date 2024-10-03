///////////////////////////////////////////////////////////////////////////////
//
// D3DXIndexAttribute.h
//
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_INDEX_ATTRIBUTE_H_
#define _D3DX_INDEX_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"
#include "D3DXEvent.h"

#include "PickRay.h"
#include "PickIntersection.h"

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXIndexAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXIndexAttribute
{
public:
	//Max Index Count
	static const _INTEGER maxIndexCount;

private:
	/**
	 * Index buffer.
	 */
	LPDIRECT3DINDEXBUFFER9 indexBuffer;

public:
	CD3DXIndexAttribute(void);
	virtual ~CD3DXIndexAttribute(void);

public:

	/**
	 * Get index buffer.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Index buffer.</p>
	 */
	LPDIRECT3DINDEXBUFFER9 getIndexBuffer() const;

protected:

	/**
	 * Initialize index.
	 *
	 * @param indexBuffer Index buffer.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT initializeIndex(LPDIRECT3DINDEXBUFFER9 indexBuffer);
	
	/**
	 * Create index buffer.
	 *
	 * @param pd3dDevice D3DX device.
	 *     <p>Result of function.</p>
	 */
	virtual LPDIRECT3DINDEXBUFFER9 createIndexBuffer(IDirect3DDevice9* pd3dDevice);

protected:

	/**
	 * Copy index.
	 *
	 * @param attribute Renderable attribute.
	 * @param indexBuffer Index buffer.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT copyIndex(const CRenderableAttribute& attribute);

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
#endif //_D3DX_INDEX_ATTRIBUTE_H_
