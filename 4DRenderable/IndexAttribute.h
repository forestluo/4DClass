///////////////////////////////////////////////////////////////////////////////
//
// IndexAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _INDEX_ATTRIBUTE_H_
#define _INDEX_ATTRIBUTE_H_

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
// IndexAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CIndexAttribute :
	public virtual CReferenceAttribute
{
public:

	/**
	 * All types.
	 */
	static const _INTEGER nullIndex;
	static const _INTEGER short3Index;
	static const _INTEGER integer3Index;

private:

	/**
	 * Type of attribute.
	 */
	_INTEGER type;
	/**
	 * Count of index.
	 */
	_INTEGER count;
	/**
	 * Data of index.
	 */
	union tagIndexData
	{
		struct tagShort3Index
		{
			_SHORT3* indices;

		} indexShort3;

		struct tagInteger3Index
		{
			_INTEGER3* indices;

		} indexInteger3;

	} indexData;


public:
	CIndexAttribute(void);
	virtual ~CIndexAttribute(void);

public:

	/**
	 * Copy.
	 *
	 * @param attribute Attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyIndex(const CIndexAttribute& attribute);
	/**
	 * Clone.
	 *
	 * @param attribute Attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void cloneIndex(const CIndexAttribute& attribute);

public:

	/**
	 * Get index type.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Type of index.</p>
	 */
	_INTEGER getIndexType() const;

	/**
	 * Set index type.
	 *
	 * @param type Type of index.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setIndexType(_INTEGER type);

public:

	/**
	 * Size of each index.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Size of index.</p>
	 */
	_INTEGER getIndexSize() const;

public:

	/**
	 * Clear all index.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearAllIndex();

public:

	/**
	 * Get count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of vertex.</p>
	 */
	_INTEGER getIndexCount() const;

	/**
	 * Get short3 index.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Short3 pointer.</p>
	 */
	_SHORT3* getShort3Index() const;
	/**
	 * Get integer3 index.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Integer3 pointer.</p>
	 */
	_INTEGER3* getInteger3Index() const;

public:

	/**
	 * Create short3 index.
	 *
	 * @param count Count of indices.
	 * @return
	 *     <p>Index pointer.</p>
	 */
	_SHORT3* createShort3Index(_INTEGER count);

	/**
	 * Create integer3 index.
	 *
	 * @param count Count of indices.
	 * @return
	 *     <p>Index pointer.</p>
	 */
	_INTEGER3* createInteger3Index(_INTEGER count);

public:

	/**
	 * Set short3 index.
	 *
	 * @param count Count of vertex.
	 * @param indices Short3 indices.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setShort3Index(_INTEGER count,_SHORT3* indices);

	/**
	 * Set integer3 index.
	 *
	 * @param count Count of vertex.
	 * @param indices Integer3 indices.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setInteger3Index(_INTEGER count,_INTEGER3* indices);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_INDEX_ATTRIBUTE_H_