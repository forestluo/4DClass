///////////////////////////////////////////////////////////////////////////////
//
// SliceAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SLICE_ATTRIBUTE_H_
#define _SLICE_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "CuboidAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// SliceAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CSliceAttribute : public CCuboidAttribute
{
public:
	/**
	 * Floor0.
	 */
	static const CSliceAttribute floor0;

public:
	CSliceAttribute(void);
	virtual ~CSliceAttribute(void);

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
	 * @param depth Depth.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initialize(_FLOAT width,_FLOAT depth);

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
#endif //_SLICE_ATTRIBUTE_H_
