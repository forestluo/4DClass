///////////////////////////////////////////////////////////////////////////////
//
// ConeAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CONE_ATTRIBUTE_H_
#define _CONE_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// ConeAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CConeAttribute : public CRenderableAttribute
{
public:
	/**
	 * Cone0.
	 */
	static const CConeAttribute cone0;
	/**
	 * Cone3.
	 */
	static const CConeAttribute cone3;
	/**
	 * Cone4.
	 */
	static const CConeAttribute cone4;
	/**
	 * Cone6.
	 */
	static const CConeAttribute cone6;

private:
	/**
	 * Parameters.
	 */
	_FLOAT height,radius;

public:
	CConeAttribute(void);
	CConeAttribute(_INTEGER segments);
	virtual ~CConeAttribute(void);

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
	 * @param radius Radius.
	 * @param height Height.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initialize(_FLOAT radius,_FLOAT height);

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
#endif //_CONE_ATTRIBUTE_H_
