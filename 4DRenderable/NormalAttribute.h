///////////////////////////////////////////////////////////////////////////////
//
// NormalAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _NORMAL_ATTRIBUTE_H_
#define _NORMAL_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"
#include "ReferenceAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// NormalAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CNormalAttribute :
	public virtual CReferenceAttribute
{
public:

	/**
	 * All types.
	 */
	static const _INTEGER nullNormal;
	static const _INTEGER float3Normal;

private:

	/**
	 * Type of attribute.
	 */
	_INTEGER type;
	/**
	 * Count of normal.
	 */
	_INTEGER count;

	union tagNormalData
	{
		struct tagFloat3Normal
		{
			_FLOAT3* normals;

		} normalFloat3;

	} normalData;


public:
	CNormalAttribute(void);
	virtual ~CNormalAttribute(void);

public:

	/**
	 * Copy.
	 *
	 * @param attribute Attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyNormal(const CNormalAttribute& attribute);

public:

	/**
	 * Get normal type.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Type of normal.</p>
	 */
	_INTEGER getNormalType() const;

	/**
	 * Set normal type.
	 *
	 * @param type Type of normal.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setNormalType(_INTEGER type);

public:

	/**
	 * Size of normal.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Size of normal.</p>
	 */
	_INTEGER getNormalSize() const;

public:

	/**
	 * Clear all.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearAllNormal();

public:

	/**
	 * Get count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of normal.</p>
	 */
	_INTEGER getNormalCount() const;
	/**
	 * Get float3 normal.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Float3 pointer.</p>
	 */
	_FLOAT3* getFloat3Normal() const;

public:

	/**
	 * Create float3 normal.
	 *
	 * @param count Count of normal.
	 * @return
	 *     <p>Normal pointer.</p>
	 */
	_FLOAT3* createFloat3Normal(_INTEGER count);

public:

	/**
	 * Set float3 normal.
	 *
	 * @param count Count of normal.
	 * @param normals Float normals.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setFloat3Normal(_INTEGER count,_FLOAT3* normals);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_NORMAL_ATTRIBUTE_H_