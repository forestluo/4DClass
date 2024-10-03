///////////////////////////////////////////////////////////////////////////////
//
// ControlAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CONTROL_ATTRIBUTE_H_
#define _CONTROL_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"

///////////////////////////////////////////////////////////////////////////////
//
// ControlAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CControlAttribute
{
private:

	/**
	 * Movable.
	 */
	_BOOL movable;
	/**
	 * Scalable.
	 */
	_BOOL scalable;
	/**
	 * Rotatable.
	 */
	_BOOL rotatable;

public:
	CControlAttribute(void);
	CControlAttribute(const CControlAttribute& attribute);
	virtual ~CControlAttribute(void);

	CControlAttribute& operator = (const CControlAttribute& attribute);

public:

	/**
	 * Whether movable.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is movable.</p>
	 */
	_BOOL isMovable() const;
	/**
	 * Set movable.
	 *
	 * @param movable Movable.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setMovable(_BOOL movable);

	/**
	 * Whether scalable.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is scalable.</p>
	 */
	_BOOL isScalable() const;
	/**
	 * Set scalable.
	 *
	 * @param scalable Scalable.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setScalable(_BOOL scalable);

	/**
	 * Whether rotatable.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is rotateable.</p>
	 */
	_BOOL isRotatable() const;
	/**
	 * Set rotatable.
	 *
	 * @param rotatable Movable.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setRotatable(_BOOL rotatable);

};

////////////////////////////////////////////////////////////////////////////////
#endif //_CONTROL_ATTRIBUTE_H_
