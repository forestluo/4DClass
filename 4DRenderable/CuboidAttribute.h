///////////////////////////////////////////////////////////////////////////////
//
// CuboidAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CUBOID_ATTRIBUTE_H_
#define _CUBOID_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// CuboidAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CCuboidAttribute : public CRenderableAttribute
{
public:
	/**
	 * Cuboid0.
	 */
	static const CCuboidAttribute cuboid0;

protected:
	/**
	 * Parameters.
	 */
	_FLOAT width,height,depth;

public:
	CCuboidAttribute(void);
	virtual ~CCuboidAttribute(void);

protected:

	/**
	 * Setup attribute.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setupAttribute();

private:

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
	 * @param width Width.
	 * @param height Height.
	 * @param depth Depth.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initialize(_FLOAT width,_FLOAT height,_FLOAT depth);

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
#endif //_CUBOID_ATTRIBUTE_H_
