///////////////////////////////////////////////////////////////////////////////
//
// CircleAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CIRCLE_ATTRIBUTE_H_
#define _CIRCLE_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// CircleAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CCircleAttribute : public CRenderableAttribute
{
public:
	/**
	 * circle0.
	 */
	static const CCircleAttribute circle0;
	/**
	 * circle3.
	 */
	static const CCircleAttribute circle3;
	/**
	 * circle4.
	 */
	static const CCircleAttribute circle4;
	/**
	 * circle5.
	 */
	static const CCircleAttribute circle5;
	/**
	 * circle6.
	 */
	static const CCircleAttribute circle6;

private:
	/**
	 * Parameters.
	 */
	_FLOAT radius;

public:
	CCircleAttribute(void);
	CCircleAttribute(_INTEGER segments);
	virtual ~CCircleAttribute(void);

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
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initialize(_FLOAT radius);

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
#endif //_CIRCLE_ATTRIBUTE_H_
