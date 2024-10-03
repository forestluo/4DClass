///////////////////////////////////////////////////////////////////////////////
//
// FrustumAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _FRUSTUM_ATTRIBUTE_H_
#define _FRUSTUM_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// FrustumAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CFrustumAttribute : public CRenderableAttribute
{
public:
	/**
	 * Frustum0.
	 */
	static const CFrustumAttribute frustum0;
	/**
	 * Frustum3.
	 */
	static const CFrustumAttribute frustum3;
	/**
	 * Frustum4.
	 */
	static const CFrustumAttribute frustum4;
	/**
	 * Frustum6.
	 */
	static const CFrustumAttribute frustum6;

private:
	/**
	 * Parameters.
	 */
	_FLOAT height;
	_FLOAT topRadius,bottomRadius;

public:
	CFrustumAttribute(void);
	CFrustumAttribute(_INTEGER segments);
	virtual ~CFrustumAttribute(void);

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
	 * @param height Height.
	 * @param topRadius Top radius.
	 * @param bottomRadius Bottom radius.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initialize(_FLOAT topRadius,_FLOAT bottomRadius,_FLOAT height);

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
#endif //_FRUSTUM_ATTRIBUTE_H_
