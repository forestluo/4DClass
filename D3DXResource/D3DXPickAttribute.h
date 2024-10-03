///////////////////////////////////////////////////////////////////////////////
//
// D3DXPickAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_PICK_ATTRIBUTE_H_
#define _D3DX_PICK_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXUtility.h"

#include "PickRay.h"
#include "PickIntersection.h"

///////////////////////////////////////////////////////////////////////////////
//
// Renderable
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXPickAttribute
{
public:
	CD3DXPickAttribute(void);
	virtual ~CD3DXPickAttribute(void);

public:

	/**
	 * Pick.
	 *
	 * @param picyRay Ray of pick.
	 * @return
	 *     <p>Pick intersection.</p>
	 */
	virtual CPickIntersection* pick(CPickRay& pickRay);

public:

	/**
	 * Pick.
	 *
	 * <p>It pick object accoding to the vertex of object.
	 * Caculate the result for every three vertex strip.</p>
	 *
	 * @param vertexBuffer Vertex buffer.
	 * @param picyRay Ray of pick.
	 * @param count Count of vertex.
	 * @return
	 *     <p>Pick intersection.</p>
	 */
	static CPickIntersection* pick0(LPDIRECT3DVERTEXBUFFER9 vertexBuffer,CPickRay& pickRay,_INTEGER count);

	/**
	 * Pick.
	 *
	 * <p>It pick object accoding to the indexex of object.
	 * Caculate the result for every three index strip.</p>
	 *
	 * @param indexBuffer Index buffer.
	 * @param vertexBuffer Vertex buffer.
	 * @param picyRay Ray of pick.
	 * @param count Count of vertex.
	 * @return
	 *     <p>Pick intersection.</p>
	 */
	static CPickIntersection* pick0(LPDIRECT3DINDEXBUFFER9 indexBuffer,LPDIRECT3DVERTEXBUFFER9 vertexBuffer,CPickRay& pickRay,_INTEGER count);
	static CPickIntersection* pick3(LPDIRECT3DINDEXBUFFER9 indexBuffer,LPDIRECT3DVERTEXBUFFER9 vertexBuffer,CPickRay& pickRay,_INTEGER count);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_PICK_ATTRIBUTE_H_
