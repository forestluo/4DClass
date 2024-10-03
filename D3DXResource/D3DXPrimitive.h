///////////////////////////////////////////////////////////////////////////////
//
// D3DXPrimitive.h
//
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _D3DX_PRIMITIVE_H_
#define _D3DX_PRIMITIVE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXRenderable.h"
#include "D3DXIndexAttribute.h"
#include "D3DXVertexAttribute.h"
#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXPrimitive
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXPrimitive :
	public CD3DXRenderable,
	public CD3DXIndexAttribute,
	public CD3DXVertexAttribute
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
	 * Renderable attribute.
	 */
	CPrimitiveAttribute attribute;

public:
	CD3DXPrimitive(void);
	CD3DXPrimitive(_INTEGER type);
	CD3DXPrimitive(const CPrimitiveAttribute& attribute);
	virtual ~CD3DXPrimitive(void);

public:

	/**
	 * Get size of index.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Bytes of index.</p>
	 */
	_INTEGER getIndexSize(void) const;

	/**
	 * Get size of vertex.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Bytes of vertex.</p>
	 */
	_INTEGER getVertexSize(void) const;

public:

	/**
	 * Get rings.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Rings.</p>
	 */
	_INTEGER getRingsCount() const;
	/**
	 * Get segments.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Segments.</p>
	 */
	_INTEGER getSegmentsCount() const;

public:

	/**
	 * Get number of indices.
	 *
	 * <p>A index is a reference of a triangle.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Number of Indices.</p>
	 */
	_INTEGER getIndexCount() const;
	/**
	 * Get number of vertexes.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Number of vertices.</p>
	 */
	_INTEGER getVertexCount() const;

public:

	/**
	 * Setup primitive attribute.
	 *
	 * @param type Primitive type.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPrimitiveAttribute(_INTEGER type);

	/**
	 * Get primitive attribute.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Primitive attribute.</p>
	 */
	CPrimitiveAttribute getPrimitiveAttribute() const;
	/**
	 * Setup primitive attribute.
	 *
	 * @param attribute Primitive attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPrimitiveAttribute(const CPrimitiveAttribute& attribute);

private:

	/**
	 * Initialize index buffer.
	 *
	 * @param indexBuffer Index buffer.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT initializeIndex(LPDIRECT3DINDEXBUFFER9 indexBuffer);
	/**
	 * Initialize vertex buffer.
	 *
	 * @param vertexBuffer Vertex buffer.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT initializeVertex(LPDIRECT3DVERTEXBUFFER9 vertexBuffer);

	/**
	 * Create index buffer.
	 *
	 * @param pd3dDevice D3DX device.
	 * @return
	 *     <p>Index buffer.</p>
	 */
	virtual LPDIRECT3DINDEXBUFFER9 createIndexBuffer(IDirect3DDevice9* pd3dDevice);
	/**
	 * Create vertex buffer.
	 *
	 * @param pd3dDevice D3DX device.
	 * @param maximum Maximum number.
	 * @return
	 *     <p>Vertex buffer.</p>
	 */
	virtual LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(IDirect3DDevice9* pd3dDevice);

public:

	/**
	 * Pick
	 *
	 * @param pickRay Pick ray.
	 * @return
	 *     <p>Pick intersection.</p>
	 */
	virtual CPickIntersection* pick(CPickRay& pickRay);

public:

	/**
	 * Render
	 *
	 * @param pd3dDevice D3DX device.
	 * @param effect Effect.
	 * @retrun
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT render(IDirect3DDevice9* pd3dDevice,CD3DXEffect* effect);

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

#define IS_PRIMITIVE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXPrimitive::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_PRIMITIVE_H_
