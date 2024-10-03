///////////////////////////////////////////////////////////////////////////////
//
// GridAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GRID_ATTRIBUTE_H_
#define _GRID_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// GridAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CGridAttribute : public CRenderableAttribute
{
public:
	/**
	 * Grid4x3.
	 */
	static const CGridAttribute grid4x3;
	/**
	 * Grid20x15.
	 */
	static const CGridAttribute grid20x15;

	/** 
	 * Ground80x60.
	 */
	static const CGridAttribute ground80x60;
	/** 
	 * Ground320x240.
	 */
	static const CGridAttribute ground320x240;
	/** 
	 * Ground640x480.
	 */
	static const CGridAttribute ground640x480;

protected:
	/**
	 * Parameters.
	 */
	//Width.
	//Width of quad.
	_FLOAT quadWidth;
	//Height.
	//Height of quad.
	_FLOAT quadHeight;

public:
	CGridAttribute(void);
	CGridAttribute(_INTEGER rings,_INTEGER segments);
	virtual ~CGridAttribute(void);

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
	 * @param quadWidth Width of quad.
	 * @param quadHeight height of quad.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initialize(_FLOAT quadWidth,_FLOAT quadHeight);

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
#endif //_GRID_ATTRIBUTE_H_
