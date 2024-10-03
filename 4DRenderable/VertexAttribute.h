///////////////////////////////////////////////////////////////////////////////
//
// VertexAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _VERTEX_ATTRIBUTE_H_
#define _VERTEX_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"
#include "ReferenceAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// VertexAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CVertexAttribute :
	public virtual CReferenceAttribute
{
public:

	/**
	 * All types.
	 */
	static const _INTEGER nullVertex;
	static const _INTEGER float3Vertex;

private:

	/**
	 * Type of attribute.
	 */
	_INTEGER type;
	/**
	 * Count of vertex.
	 */
	_INTEGER count;

	union tagVertexData
	{
		struct tagFloat3Vertex
		{
			_FLOAT3* vertices;

		} vertexFloat3;

	} vertexData;


public:
	CVertexAttribute(void);
	virtual ~CVertexAttribute(void);

public:

	/**
	 * Copy.
	 *
	 * @param attribute Attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyVertex(const CVertexAttribute& attribute);
	/**
	 * Clone.
	 *
	 * @param attribute Attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void cloneVertex(const CVertexAttribute& attribute);

public:

	/**
	 * Get vertex type.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Type of vertex.</p>
	 */
	_INTEGER getVertexType() const;

	/**
	 * Set vertex type.
	 *
	 * @param type Type of vertex.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setVertexType(_INTEGER type);

public:

	/**
	 * Size of vertex.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Size of vertex.</p>
	 */
	_INTEGER getVertexSize() const;

public:

	/**
	 * Clear all vertex.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearAllVertex();

public:

	/**
	 * Get vertex count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of vertex.</p>
	 */
	_INTEGER getVertexCount() const;

	/**
	 * Get float3 vertex.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Float3 pointer.</p>
	 */
	_FLOAT3* getFloat3Vertex() const;

public:

	/**
	 * Create float3 vertex.
	 *
	 * @param count Count of vertex.
	 * @return
	 *     <p>Vertex pointer.</p>
	 */
	_FLOAT3* createFloat3Vertex(_INTEGER count);

public:

	/**
	 * Set float3 vertex.
	 *
	 * @param count Count of vertex.
	 * @param vertices Float vertices.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setFloat3Vertex(_INTEGER count,_FLOAT3* vertices);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_VERTEX_ATTRIBUTE_H_