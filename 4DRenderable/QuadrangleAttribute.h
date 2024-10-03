///////////////////////////////////////////////////////////////////////////////
//
// QuadrangleAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _QUADRANGLE_ATTRIBUTE_H_
#define _QUADRANGLE_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// QuadrangleAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CQuadrangleAttribute : public CRenderableAttribute
{
public:
	/**
	 * Quadrangle0
	 */
	static const CQuadrangleAttribute quadrangle0;

protected:
	/**
	 * Point a,b,c,d.
	 */
	_FLOAT2 a, b, c, d;

public:
	CQuadrangleAttribute(void);
	virtual ~CQuadrangleAttribute(void);

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
	 * @param d Point d.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initialize(const _FLOAT2 a,const _FLOAT2 b,const _FLOAT2 c,const _FLOAT2 d);

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
#endif //_QUADRANGLE_ATTRIBUTE_H_
