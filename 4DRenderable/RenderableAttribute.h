///////////////////////////////////////////////////////////////////////////////
//
// RenderableAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _RENDERABLE_ATTRIBUTE_H_
#define _RENDERABLE_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "IndexAttribute.h"
#include "VertexAttribute.h"
#include "NormalAttribute.h"
#include "TextureAttribute.h"

#include "BoxAttribute.h"
#include "PrimitiveAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// RenderableAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CRenderableAttribute :
	public CIndexAttribute,
	public CVertexAttribute,
	public CNormalAttribute,
	public CTextureAttribute
{
protected:
	/**
	 * Type of primitive.
	 */
	_INTEGER type;
	
protected:
	/**
	 * Rings of object.
	 */
	_INTEGER rings;
	/**
	 * Segments of object.
	 */
	_INTEGER segments;

public:
	CRenderableAttribute(void);
	CRenderableAttribute(const CRenderableAttribute& attribute);
	virtual ~CRenderableAttribute(void);

	CRenderableAttribute& operator = (const CRenderableAttribute& attribute);

public:

	/**
	 * Swap renderable.
	 *
	 * @param attribute Renderable attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void swapRenderable(CRenderableAttribute& attribute);
	/**
	 * Copy renderable.
	 *
	 * @param attribute Renderable attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyRenderable(const CRenderableAttribute& attribute);

public:

	/**
	 * Get rings.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Rings count.</p>
	 */
	_INTEGER getRings() const;

	/**
	 * Get segments.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Segments count.</p>
	 */
	_INTEGER getSegments() const;

public:

	/**
	 * Get attribute.
	 *
	 * @param attribute Box attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual CBoxAttribute getBoxAttribute() const;

	/**
	 * Get primitive attribute.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Primitive attribute.</p>
	 */
	virtual CPrimitiveAttribute getPrimitiveAttribute() const;

	/**
	 * Set primitive attribute
	 *
	 * @param attribute Primitive attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setPrimitiveAttribute(const CPrimitiveAttribute& attribute);

public:

	/**
	 * Create renderable attribute.
	 *
	 * @param attribute Primitive attribute.
	 * @return
	 *     <p>Renderable attribute.</p>
	 */
	static CRenderableAttribute* createRenderableAttribute(const CPrimitiveAttribute& attribute);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_RENDERABLE_ATTRIBUTE_H_
