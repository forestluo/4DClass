///////////////////////////////////////////////////////////////////////////////
//
// SphereAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SPHERE_ATTRIBUTE_H_
#define _SPHERE_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// SphereAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CSphereAttribute : public CRenderableAttribute
{
public:
	/**
	 * Sphere0.
	 */
	static const CSphereAttribute sphere0;

private:
	/**
	 * Radius.
	 */
	_FLOAT radius;

public:
	CSphereAttribute(void);
	CSphereAttribute(_INTEGER rings,_INTEGER segments);
	virtual ~CSphereAttribute(void);

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
#endif //_SPHERE_ATTRIBUTE_H_
