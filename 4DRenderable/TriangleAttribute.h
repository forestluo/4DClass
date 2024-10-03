///////////////////////////////////////////////////////////////////////////////
//
// TriangleAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _TRIANGLE_ATTRIBUTE_H_
#define _TRIANGLE_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// TriangleAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CTriangleAttribute : public CRenderableAttribute
{
public:
	/**
	 * Triangle0
	 */
	static const CTriangleAttribute triangle0;

private:
	/**
	 * Point a, b, c.
	 */
	_FLOAT3 a, b, c;

public:
	CTriangleAttribute(void);
	virtual ~CTriangleAttribute(void);

private:

	/**
	 * Setup attribute.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setupAttribute();

	/**
	 * Create attribute.
	 *
	 * @param rings rings of attribute.
	 * @param segments Segments of attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void createAttribute(_INTEGER rings,_INTEGER segments);

public:

	/**
	 * Get primitive attribute.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Primitive attribute.</p>
	 */
	virtual CPrimitiveAttribute getPrimitiveAttribute() const;

public:

	/**
	 * Initialize default.
	 *
	 * <p>Initialize attribute with default parameters.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initializeDefault();

	/**
	 * Initialize.
	 *
	 * <p>Initialize attribute with specified parameters.</p>
	 *
	 * @param a Point a.
	 * @param b Point b.
	 * @param c Point c.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initialize(const _FLOAT3 a,const _FLOAT3 b,const _FLOAT3 c);

public:

	/**
	 * Set primitive attribute
	 *
	 * @param attribute Primitive attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setPrimitiveAttribute(const CPrimitiveAttribute& attribute);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_TRIANGLE_ATTRIBUTE_H_
