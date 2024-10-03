///////////////////////////////////////////////////////////////////////////////
//
// PolygonAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _POLYGON_ATTRIBUTE_H_
#define _POLYGON_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// PolygonAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CPolygonAttribute : public CRenderableAttribute
{
public:
	/**
	 * polygon4.
	 */
	static const CPolygonAttribute polygon4;
	/**
	 * polygon6.
	 */
	static const CPolygonAttribute polygon6;
	/**
	 * polygon8.
	 */
	static const CPolygonAttribute polygon8;
	/**
	 * polygon12.
	 */
	static const CPolygonAttribute polygon12;
	/**
	 * polygon20.
	 */
	static const CPolygonAttribute polygon20;

private:
	/**
	 * Parameters.
	 */
	_FLOAT radius;

public:
	CPolygonAttribute(void);
	CPolygonAttribute(_INTEGER segments);
	virtual ~CPolygonAttribute(void);

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
#endif //_POLYGON_ATTRIBUTE_H_
