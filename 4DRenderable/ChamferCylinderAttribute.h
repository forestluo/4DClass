///////////////////////////////////////////////////////////////////////////////
//
// ChamferCylinderAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CHAMFER_CYLINDER_ATTRIBUTE_H_
#define _CHAMFER_CYLINDER_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// ChamferCylinderAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CChamferCylinderAttribute : public CRenderableAttribute
{
public:
	/**
	 * Chamfer cylinder.
	 */
	static const CChamferCylinderAttribute chamferCylinder0;

private:
	/**
	 * Parameters.
	 */
	_FLOAT radius,height;

public:
	CChamferCylinderAttribute(void);
	CChamferCylinderAttribute(_INTEGER rings,_INTEGER segments);
	virtual ~CChamferCylinderAttribute(void);

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
	 * Get attribute.
	 *
	 * @param attribute Box attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual CBoxAttribute getBoxAttribute() const;

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
#endif //_CHAMFER_CYLINDER_ATTRIBUTE_H_
