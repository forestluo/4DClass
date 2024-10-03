///////////////////////////////////////////////////////////////////////////////
//
// CylinderAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _RENDERABLE_CYLINDER_H_
#define _RENDERABLE_CYLINDER_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// CylinderAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CCylinderAttribute : public CRenderableAttribute
{
public:
	/**
	 * Cylinder0.
	 */
	static const CCylinderAttribute cylinder0;
	/**
	 * Cylinder3.
	 */
	static const CCylinderAttribute cylinder3;
	/**
	 * Cylinder5.
	 */
	static const CCylinderAttribute cylinder5;
	/**
	 * Cylinder6.
	 */
	static const CCylinderAttribute cylinder6;

private:
	/**
	 * Parameters.
	 */
	_FLOAT height,radius;

public:
	CCylinderAttribute(void);
	CCylinderAttribute(_INTEGER segments);
	virtual ~CCylinderAttribute(void);

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
#endif //_RENDERABLE_CYLINDER_H_
