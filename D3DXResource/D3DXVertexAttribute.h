///////////////////////////////////////////////////////////////////////////////
//
// D3DXVertexAttribute.h
//
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_VERTEX_ATTRIBUTE_H_
#define _D3DX_VERTEX_ATTRIBUTE_H_

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
// D3DXVertexAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXVertexAttribute
{
public:
	//Max vertex count.
	static const _INTEGER maxVertexCount;

private:
	/**
	 * Vertex buffer.
	 */
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

public:
	CD3DXVertexAttribute(void);
	virtual ~CD3DXVertexAttribute(void);

public:

	/**
	 * Get vertex buffer.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Vertex buffer.</p>
	 */
	LPDIRECT3DVERTEXBUFFER9 getVertexBuffer() const;

protected:

	/**
	 * Initialize vertex.
	 *
	 * @param vertexBuffer Vertex buffer.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT initializeVertex(LPDIRECT3DVERTEXBUFFER9 pVertexBuffer);

	/**
	 * Create vertex buffer
	 *
	 * @param pd3dDevice D3DX device.
	 * @return
	 *     <p>Vertex buffer.</p>
	 */
	virtual LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(IDirect3DDevice9* pd3dDevice);

protected:

	/**
	 * Copy vertex.
	 *
	 * @param attribute Renderable attribute.
	 * @param vertexBuffer Vertex buffer.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT copyVertex(const CRenderableAttribute& attribute);

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
#endif //_D3DX_VERTEX_ATTRIBUTE_H_
