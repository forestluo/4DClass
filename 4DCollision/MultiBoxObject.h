///////////////////////////////////////////////////////////////////////////////
//
// MultiBoxObject.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _MULTI_BOX_OBJECT_H_
#define _MULTI_BOX_OBJECT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "BoxObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// MultiBoxObject
//
///////////////////////////////////////////////////////////////////////////////

class CMultiBoxObject : public CBoxObject
{
private:
	/**
	 * Child objects.
	 */
	_OBJECT objects;

public:
	CMultiBoxObject(void);
	virtual ~CMultiBoxObject(void);

public:

	/**
	 * Whether is single.
	 * 
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is single.</p>
	 */
	_BOOL isSingle();

	/**
	 * Clear all of object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearAll();

	/**
	 * Add object.
	 * 
	 * @param object Box object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addObject(CBoxObject* object);

	/**
	 * Get count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of object.</p>
	 */
	_INTEGER getCount();

	/**
	 * Get object.
	 *
	 * @param index Index of object.
	 * @return
	 *     <p>Box object.</p>
	 */
	CBoxObject* getObject(_INTEGER index);

	/**
	 * Get toal count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Total count of object.
	 *	   Including its children.</p>
	 */
	_INTEGER getTotalCount();

public:

	/**
	 * Recycle.
	 *
	 * <p>Recycle this sphere.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void recycle();

	/**
	 * Create.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Created object.</p>
	 */
	static CMultiBoxObject* create();
};

///////////////////////////////////////////////////////////////////////////////
#endif //_MULTI_BOX_OBJECT_H_
