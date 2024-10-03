///////////////////////////////////////////////////////////////////////////////
//
// HashListContainer.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _HASH_LIST_CONTAINER_H_
#define _HASH_LIST_CONTAINER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "HashTreeContainer.h"
#include "ListNodeEnumeration.h"

///////////////////////////////////////////////////////////////////////////////
//
// HashListContainer
//
///////////////////////////////////////////////////////////////////////////////

class CHashListContainer : public CHashTreeContainer
{
private:
	/**
	 * List container.
	 */
	_OBJECT list;

public:
	CHashListContainer(void);
	virtual ~CHashListContainer(void);

public:

	/**
	 * Get value.
	 *
	 * @param key Key value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	_OBJECT getValue(_LONG key);

	/**
	 * Set value.
	 *
	 * @param key Key value.
	 * @return
	 *     <p>Previous value.</p>
	 */
	_OBJECT setValue(_LONG key,_OBJECT value);

	/**
	 * Remove value.
	 *
	 * @param key Key value.
	 * @return
	 *     <p>Previous value.</p>
	 */
	_OBJECT removeValue(_LONG key);
	
	/**
	 * Get value by index.
	 *
	 * @param index Index of value.
	 * @return
	 *     <p>Indexed value of the list.</p>
	 */
	_OBJECT getIndexed(_INTEGER index);

	/**
	 * Clear all.
	 * 
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void clearAll();

	/**
	 * Get enumeration of container.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Enumeration of container.</p>
	 */
	void getEnumeration(CListNodeEnumeration* enumeration);

public:

	/**
	 * Main
	 *
	 * @param argc Count of arguments.
	 * @param argv Parameter of arguments.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void main(int argc,char* argv[]);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_HASH_LIST_CONTAINER_H_
