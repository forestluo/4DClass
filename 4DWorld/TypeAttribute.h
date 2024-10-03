///////////////////////////////////////////////////////////////////////////////
//
// TypeAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _TYPE_ATTRIBUTE_H_
#define _TYPE_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"

///////////////////////////////////////////////////////////////////////////////
//
// TypeAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CTypeAttribute
{
public:

	/**
	 * All object types.
	 */
	static const _INTEGER nullObject;
	static const _INTEGER jointObject;
	static const _INTEGER compoundObject;
	static const _INTEGER primitiveObject;

private:

	/**
	 * Type of primitive.
	 */
	_INTEGER objectType;

public:
	CTypeAttribute(void);
	virtual ~CTypeAttribute(void);

public:

	/**
	 * Get object type.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Type of object.</p>
	 */
	_INTEGER getObjectType() const;

protected:

	/**
	 * Set object type.
	 *
	 * @param objectType Type of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setObjectType(_INTEGER type);

public:

	/**
	 * Whether is joint object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is joint object.</p>
	 */
	_BOOL isJointObject() const;

	/**
	 * Whether is compound object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is compound object.</p>
	 */
	_BOOL isCompoundObject() const;

	/**
	 * Whether is primitive object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is compound object.</p>
	 */
	_BOOL isPrimitiveObject() const;

};

///////////////////////////////////////////////////////////////////////////////
#endif //_TYPE_ATTRIBUTE_H_
